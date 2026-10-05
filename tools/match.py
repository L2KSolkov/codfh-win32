"""match.py OBJ SYMBOL ADDRESS

Compares one compiled function with the original bytes at ADDRESS.

Every byte outside a relocation field must be identical. Every relocation is
then resolved and checked against the address the original encodes there:

- a target named with an IDA address suffix (`sub_67970`, `dword_449B0C`,
  including the first component of a decorated name) must resolve to exactly
  that address;
- a target whose name is in config/symbols.txt (the IDA database's names) or
  in a `// symbol: NAME = 0xADDRESS` annotation must resolve to that address;
- a target defined in the object itself (string literals, EH tables, labels)
  must land in the matching kind of original section (.text, .rdata, .data,
  or the .data BSS tail);
- anything else is reported as unverified.

The original must also end where the compiled function ends (followed by
0xCC fill, a 16-byte boundary, or the next piece packed in the same compiled
section). Exit status 0 means identical."""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from coff import (Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32,  # noqa: E402
                  RELOC_WIDTH)
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ORIGINAL = os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe')
ADDRESS_NAME = re.compile(
    r'^(?:sub|loc|j_sub|dword|byte|word|qword|flt|dbl|off|unk|stru|asc|xmmword|tbyte)'
    r'_([0-9A-Fa-f]{5,8})$')

_symbols = None
_sizes = None
_aliases = None


def symbol_table():
    """IDA database names from config/symbols.txt: name -> address."""
    global _symbols, _sizes
    if _symbols is None:
        _symbols = {}
        _sizes = {}
        path = os.path.join(ROOT, 'config', 'symbols.txt')
        if os.path.exists(path):
            for line in open(path):
                if line.startswith('#') or not line.strip():
                    continue
                parts = line.split(None, 4)
                if len(parts) == 5:
                    address = int(parts[0], 16)
                    _symbols[parts[4].strip()] = address
                    if parts[1] == 'function':
                        _sizes[address] = int(parts[2], 16)
    return _symbols


_split_starts = None


def split_starts():
    """Range starts in config/splits.txt: the placement linker's boundaries."""
    global _split_starts
    if _split_starts is None:
        _split_starts = set()
        # and the compiled pieces' addresses (a piece may start inside a range)
        for name in ('splits.txt', 'compiled.txt'):
            path = os.path.join(ROOT, 'config', name)
            if os.path.exists(path):
                for line in open(path):
                    parts = line.split()
                    if parts and parts[0].startswith('0x'):
                        _split_starts.add(int(parts[0], 16))
    return _split_starts


def function_size(address):
    """The size the IDA database records for the function at ADDRESS."""
    symbol_table()
    return _sizes.get(address)


def link_aliases():
    """Proven library public names from config/aliases.txt: name -> address."""
    global _aliases
    if _aliases is None:
        _aliases = {}
        path = os.path.join(ROOT, 'config', 'aliases.txt')
        if os.path.exists(path):
            for line in open(path):
                parts = line.split('#', 1)[0].split()
                if len(parts) >= 2:
                    _aliases[parts[0]] = int(parts[1], 16)
    return _aliases


def resolve_name(name, aliases):
    """Address a compiled symbol name denotes, or None if it cannot be told."""
    if name in aliases:
        return aliases[name]
    if name in link_aliases():
        return link_aliases()[name]
    candidates = [name]
    if name.startswith('?') and not name.startswith('??'):
        candidates.append(name[1:].split('@', 1)[0])
    if name.startswith('_'):
        candidates.append(name[1:])
    table = symbol_table()
    for candidate in candidates:
        m = ADDRESS_NAME.match(candidate)
        if m:
            return int(m.group(1), 16)
    for candidate in candidates:
        if candidate in table:
            return table[candidate]
    return None


XDK_MERGES = [('.XAPI', '.data'), ('.CRT', '.data'), ('.XPPCODE', 'XPP'), ('.XPPRDATA', 'XPP'), ('.XPPCINIT', None), ('.XPP', 'XPP'), ('.XID', 'XPP')]
# the libraries' own /merge: directives (.drectve): their data sections join their code section
XDK_MERGES += [(s, s.rsplit('_', 1)[0]) for s in (
    'XGRPH_RD', 'XGRPH_RW', 'D3DX_RD', 'D3DX_RW', 'D3D_RD', 'D3D_RW', 'D3D_URW',
    'DSOUND_RD', 'DSOUND_RW', 'DSOUND_URW', 'WMADEC_RD', 'WMADEC_RW', 'XNET_RD')]


def section_kind(compiled_name):
    if compiled_name.startswith('.text'):
        return '.text'
    if compiled_name.startswith('.rdata') or compiled_name.startswith('.xdata'):
        return '.rdata'
    if compiled_name == '.data1' or compiled_name.startswith('.data1$'):
        # (the image keeps a .data1 of its own: IPP's constant tables)
        return '.data1'
    if compiled_name.startswith('.data'):
        return '.data'
    if compiled_name.startswith('.bss'):
        return '.bss'
    # XDK library sections the linker merges into the image's (M3)
    for prefix, kind in XDK_MERGES:
        if compiled_name.startswith(prefix):
            return kind
    if compiled_name and not compiled_name.startswith('.'):
        # a named code section (Bink's `#pragma code_seg("BINK")`): its
        # switch tables land in the image section of that name
        return compiled_name.split('$')[0]
    return None


def original_kind(image, va):
    section = image.section_at(va)
    if section is None:
        return None
    if section['name'] == '.data' and va - section['va'] >= section['rsize']:
        return '.bss'
    return section['name']


def compare(obj_path, name, address, image=None, aliases=None):
    # obj_path may be a Coff already read (build_sources reads each object once).
    image = image or Xbe(ORIGINAL)
    aliases = aliases or {}
    obj = obj_path if isinstance(obj_path, Coff) else Coff(obj_path)
    obj_path = obj.path
    symbol = obj.find_function(name)
    if symbol is None:
        return False, '%s: no function symbol for %s' % (obj_path, name)
    code, relocs = obj.function_bytes(symbol)
    original = image.read(address, len(code) + 1)
    label = symbol['name']
    mask = [False] * len(code)
    for offset, _target, rtype in relocs:
        for k in range(RELOC_WIDTH.get(rtype, 4)):
            if offset + k < len(mask):
                mask[offset + k] = True
    for i in range(len(code)):
        if not mask[i] and code[i] != original[i]:
            lo = max(0, i - 8)
            return False, ('%s @ 0x%08X differs at +0x%X\n  compiled %s\n  original %s'
                           % (label, address, i, code[lo:i + 8].hex(' '),
                              original[lo:i + 8].hex(' ')))

    unverified = []
    for offset, target, rtype in relocs:
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32):
            unverified.append('%s (type 0x%X)' % (target, rtype))
            continue
        addend = struct.unpack_from('<i', code, offset)[0]
        field = struct.unpack_from('<I', original, offset)[0]
        if rtype == IMAGE_REL_I386_REL32:
            encoded = (address + offset + 4 + struct.unpack('<i', struct.pack('<I', field))[0])
        else:
            encoded = field
        encoded = (encoded - addend) & 0xFFFFFFFF
        # a library member's own static (folded by /OPT:ICF anywhere): object-local, see xbelink
        local_static = obj_path.replace('\\', '/').split('build/xdk/')[-1] != obj_path.replace('\\', '/') \
            and any(s['name'] == target and s['section'] > 0 and s['class'] == 3 for s in obj.symbol_list)
        expected = None if local_static else resolve_name(target, aliases)
        if expected is not None:
            if expected != encoded:
                return False, ('%s @ 0x%08X: relocation at +0x%X to %s resolves to 0x%08X, '
                               'but the original encodes 0x%08X'
                               % (label, address, offset, target, expected, encoded))
            continue
        defined = [s for s in obj.symbol_list if s['name'] == target and s['section'] > 0]
        if defined:
            kind = section_kind(obj.sections[defined[0]['section'] - 1]['name'])
            actual = original_kind(image, encoded)
            if kind is not None and kind != actual:
                return False, ('%s @ 0x%08X: relocation at +0x%X to %s is %s data, but the '
                               'original points into %s (0x%08X)'
                               % (label, address, offset, target, kind, actual, encoded))
            # A literal the piece defines itself (a /GF string or __real@
            # constant) must also hold the bytes the original's target does.
            if target.startswith(('??_C@', '__real@')):
                section = obj.sections[defined[0]['section'] - 1]
                value = section['data'][defined[0]['value']:]
                if image.read(encoded, len(value)) != value:
                    return False, ('%s @ 0x%08X: relocation at +0x%X to %s: the literal is %r, '
                                   'but the original at 0x%08X holds %r'
                                   % (label, address, offset, target, value, encoded,
                                      image.read(encoded, len(value))))
            if kind is not None:
                continue
        unverified.append(target)

    # The original must end where the compiled function ends. The IDA
    # database's recorded size is the authority where there is one; otherwise
    # a function that ends its compiled section must be followed by 0xCC fill
    # or a 16-byte boundary (pieces packed after it in the same section, like
    # EH funclets, are checked by their own annotations).
    size = function_size(address)
    tables = 0
    data_piece = section_kind(obj.sections[symbol['section'] - 1]['name']) in ('.rdata', '.data')
    if data_piece:
        # Data (M5): a vtable, table or initialized global is packed against
        # its neighbours; its extent is its own placement range in
        # config/splits.txt, which the link checks.
        pass
    elif size:
        # A switch's jump tables follow its code in the same section; IDA
        # counts only the code. The table bytes were compared above like the
        # rest, so a longer piece is accepted when no other function starts
        # inside the extra bytes.
        later = [a for a in _sizes if address < a < address + len(code)]
        section = obj.sections[symbol['section'] - 1]
        end = symbol['value'] + len(code)
        if len(code) > size and not later:
            tables = len(code) - size
        elif len(code) < size and any(
                s['section'] == symbol['section'] and s['value'] == end and (s['type'] >> 4) != 2
                and not s['name'].startswith(('$', '.')) for s in obj.symbol_list):
            pass  # an assembler label inside the function ends this piece; the next one starts there
        elif len(code) < size and (symbol['type'] >> 4) != 2 and address + len(code) in split_starts():
            pass  # a label piece (an XDK stand-in) ending at a placement range boundary
        elif size != len(code):
            return False, ('%s @ 0x%08X: compiled %d bytes, the original function is %d'
                           % (label, address, len(code), size))
    else:
        section = obj.sections[symbol['section'] - 1]
        ends_section = symbol['value'] + len(code) >= section['size']
        tail = original[len(code)]
        end = address + len(code)
        # MASM units (Bink's hand-written assembly) sit in sections the
        # linker pads with zeros up to the next 16-byte boundary.
        try:
            zero_fill = tail == 0 and not any(image.read(end, (16 - end % 16) % 16))
        except ValueError:  # the section's raw data ends there
            zero_fill = tail == 0
        # an assembler member's last label piece, packed against the next
        # function (functions themselves must end at fill or a boundary)
        # (an EH handler thunk is packed against the next object's funclets in .text$x)
        packed = (end in _sizes or end in split_starts()) and (
            (symbol['type'] >> 4) != 2 or symbol['name'].startswith('__ehhandler$'))
        if ends_section and end % 16 != 0 and tail != 0xCC and not zero_fill and not packed:
            return False, ('%s @ 0x%08X: compiled %d bytes but the original continues '
                           '(next byte 0x%02X)' % (label, address, len(code), tail))
    note = ''
    if tables:
        note += '; %d bytes of jump tables' % tables
    if unverified:
        note += '; unverified: ' + ', '.join(unverified)
    return True, '%s @ 0x%08X identical (%d bytes, %d relocations%s)' % (
        label, address, len(code), len(relocs), note)


def main(argv):
    if len(argv) != 4:
        print(__doc__)
        return 2
    ok, message = compare(argv[1], argv[2], int(argv[3], 16))
    print(('OK   ' if ok else 'DIFF ') + message)
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main(sys.argv))
