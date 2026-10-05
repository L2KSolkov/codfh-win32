"""Minimal reader for the i386 COFF objects CL 13.10 emits: sections,
symbols, relocations."""
import bisect
import re
import struct

IMAGE_REL_I386_DIR32 = 0x06
IMAGE_REL_I386_DIR32NB = 0x07
IMAGE_REL_I386_SECTION = 0x0A
IMAGE_REL_I386_SECREL = 0x0B
IMAGE_REL_I386_REL32 = 0x14

IMAGE_SCN_LNK_COMDAT = 0x00001000
IMAGE_SCN_CNT_CODE = 0x00000020

# Bytes each relocation type patches.
RELOC_WIDTH = {
    IMAGE_REL_I386_DIR32: 4,
    IMAGE_REL_I386_DIR32NB: 4,
    IMAGE_REL_I386_SECTION: 2,
    IMAGE_REL_I386_SECREL: 4,
    IMAGE_REL_I386_REL32: 4,
}


class Coff(object):
    def __init__(self, path, data=None):
        self.path = path
        d = data if data is not None else open(path, 'rb').read()
        self.data = d
        (machine, nsections, _stamp, symptr, nsyms, optsize,
         _chars) = struct.unpack_from('<HHIIIHH', d, 0)
        if machine != 0x14C:
            raise ValueError('%s: not an i386 object (machine 0x%X)' % (path, machine))
        strtab = symptr + nsyms * 18
        self._strtab = d[strtab:]
        self.sections = []
        offset = 20 + optsize
        for i in range(nsections):
            (raw_name, _vsize, _va, rawsize, rawptr, relptr, _lnptr, nrel,
             _nln, chars) = struct.unpack_from('<8sIIIIIIHHI', d, offset + i * 40)
            relocs = []
            for r in range(nrel):
                vaddr, symindex, rtype = struct.unpack_from('<IIH', d, relptr + r * 10)
                relocs.append((vaddr, symindex, rtype))
            name = raw_name.rstrip(b'\0').decode('latin1')
            if name.startswith('/') and name[1:].isdigit():
                # Long section names live in the string table ("/offset").
                start = int(name[1:])
                name = self._strtab[start:self._strtab.index(b'\0', start)].decode('latin1')
            self.sections.append({
                'index': i + 1, 'name': name, 'size': rawsize,
                'data': d[rawptr:rawptr + rawsize] if rawptr else b'\0' * rawsize,
                'relocs': relocs, 'chars': chars,
            })
        self.symbols = {}
        self.symbol_list = []
        i = 0
        while i < nsyms:
            (raw_name, value, secnum, stype, sclass,
             naux) = struct.unpack_from('<8sIhHBB', d, symptr + i * 18)
            symbol = {'index': i, 'name': self._name(raw_name), 'value': value,
                      'section': secnum, 'type': stype, 'class': sclass}
            self.symbol_list.append(symbol)
            self.symbols[i] = symbol
            i += 1 + naux
        self._by_name = None
        self._by_anon = None
        self._sections_index = {}

    def _defined(self):
        """name -> the first defined symbol of that name."""
        if self._by_name is None:
            self._by_name = {}
            for symbol in self.symbol_list:
                if symbol['section'] > 0:
                    self._by_name.setdefault(symbol['name'], symbol)
        return self._by_name

    _ANON = re.compile(r'\?A0x[0-9a-f]{8}')

    def _lookup(self, name):
        """The defined symbol NAME, or else the one whose name differs from it only in its
        anonymous-namespace hash (`?A0x1234abcd`): VC7.1 hashes the source file's absolute path
        into it, so a checkout in another directory compiles the names the configs list
        (made in the codfh-match checkout) with other hashes. Within one object every anonymous
        namespace is the one file's, so the match is unambiguous."""
        symbol = self._defined().get(name)
        if symbol is not None or '?A0x' not in name:
            return symbol
        if self._by_anon is None:
            self._by_anon = {}
            for nm, sym in self._defined().items():
                if '?A0x' in nm:
                    self._by_anon.setdefault(self._ANON.sub('?A0x', nm), sym)
        return self._by_anon.get(self._ANON.sub('?A0x', name))

    def _section_index(self, number):
        """A section's symbols that can end a piece (by value) and its relocations (by address)."""
        if not self._sections_index:
            buckets = {}
            for s in self.symbol_list:
                if s['section'] > 0 and s['class'] in (2, 3, 6) \
                        and s['name'] != self.sections[s['section'] - 1]['name']:
                    buckets.setdefault(s['section'], []).append((s['value'], s['name']))
            for k, section in enumerate(self.sections):
                ends = sorted(buckets.get(k + 1, []))
                rsorted = sorted(section['relocs'], key=lambda r: r[0])
                self._sections_index[k + 1] = ([v for v, _ in ends], [n for _, n in ends],
                                               [r[0] for r in rsorted], rsorted)
        return self._sections_index[number]

    def _name(self, raw):
        if raw[:4] == b'\0\0\0\0':
            offset = struct.unpack_from('<I', raw, 4)[0]
            end = self._strtab.index(b'\0', offset)
            return self._strtab[offset:end].decode('latin1')
        return raw.rstrip(b'\0').decode('latin1')

    def find_function(self, name):
        """A defined symbol named exactly NAME (decorated names, EH funclets
        and handler thunks are given in full), or else a function whose
        decorated name's first component is NAME (?NAME@...). A NAME of the
        form `.section+OFFSET` addresses code by position instead: VC7.1 gives
        EH unwind funclets compiler-numbered local labels ($L301), so the
        funclet is found by its offset in .text$x. That names the first such
        section, so in an object with several EH functions (each gets a
        .text$x of its own) a funclet is instead named `SYMBOL-OFFSET`: OFFSET
        bytes before a symbol of its section, normally the function's
        `__ehhandler$` thunk.

        `BASE>OFFSET` names the symbol that the relocation at OFFSET inside the
        piece BASE targets (chained: `A>1>8`). Compiler-numbered data labels
        ($T EH tables) renumber whenever their unit changes; reached from a
        stable name (`__ehhandler$F>1` is F's EH function info) they do not."""
        m = re.match(r'^(.+)>(0x[0-9A-Fa-f]+|\d+)$', name)
        if m:
            base = self.find_function(m.group(1))
            if base is None:
                return None
            _code, relocs = self.function_bytes(base)
            for offset, target, _rtype in relocs:
                if offset == int(m.group(2), 0):
                    return self._defined().get(target)
            return None
        m = re.match(r'^(\.[\w$]+)\+(0x[0-9A-Fa-f]+|\d+)$', name)
        if m:
            for section in self.sections:
                if section['name'] == m.group(1):
                    return {'index': -1, 'name': name, 'value': int(m.group(2), 0),
                            'section': section['index'], 'type': 0x20, 'class': 3}
            return None
        m = re.match(r'^(.+)-(0x[0-9A-Fa-f]+|\d+)$', name)
        if m:
            symbol = self._lookup(m.group(1))
            if symbol is not None:
                return {'index': -1, 'name': name,
                        'value': symbol['value'] - int(m.group(2), 0),
                        'section': symbol['section'], 'type': 0x20, 'class': 3}
            return None
        symbol = self._lookup(name)
        if symbol is not None:
            return symbol
        for symbol in self.symbol_list:
            if symbol['section'] <= 0 or (symbol['type'] >> 4) != 2:
                continue
            if symbol['name'] == name or symbol['name'].startswith('?' + name + '@') \
                    or symbol['name'] == '_' + name:
                return symbol
        return None

    def function_bytes(self, symbol):
        """(bytes, relocations) of one function. /Gy gives each function its
        own section; otherwise it runs to the next symbol in the section."""
        section = self.sections[symbol['section'] - 1]
        start = symbol['value']
        end = section['size']
        # in code, $L labels are jump targets inside a function; in data, $T/$SG labels start
        # tables of their own (VC7.1's EH tables share one .xdata$x section)
        data = not section['chars'] & 0x20
        values, names, rvaddrs, rsorted = self._section_index(symbol['section'])
        k = bisect.bisect_right(values, start)
        while k < len(values) and values[k] < end:
            if data or not names[k].startswith('$'):
                end = values[k]
                break
            k += 1
        lo, hi = bisect.bisect_left(rvaddrs, start), bisect.bisect_left(rvaddrs, end)
        relocs = [(v - start, self.symbols[s]['name'], t) for (v, s, t) in rsorted[lo:hi]]
        return section['data'][start:end], relocs
