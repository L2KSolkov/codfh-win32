"""asmgen.py LIBOBJ SECTION IMGLO [IMGHI]: draft a MASM unit for one of
Bink's hand-written assembly members (PLAN M6) from the image's bytes and the
library member's symbols.

The library member's SECTION (e.g. BINK32) is disassembled beside the image
from IMGLO; the two must be the same instruction sequence (the image's copy
of RAD's code). Code labels come from the member's symbols (globals become
PUBLIC PROCs, statics plain labels) and from jump targets; every operand the
member relocates is written as SYMBOL+offset, and each symbol's image address
is printed (for config/aliases.txt). MASM 6.15's alignment fill becomes
ALIGN16 (masm6.inc). Prints the draft to stdout and the address map to
stderr."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os
import struct
import sys

import capstone

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

FILL = {
    b'\x8d\xa4\x24\x00\x00\x00\x00', b'\x8d\x9b\x00\x00\x00\x00', b'\x05\x00\x00\x00\x00',
    b'\x8d\x64\x24\x00', b'\x8d\x40\x00', b'\x8b\xc0', b'\x90', b'\x8b\xff', b'\x8d\x49\x00',
}


def hexify(s):
    """capstone's 0x.. numbers as MASM ..h."""
    out = []
    i = 0
    while i < len(s):
        if s.startswith('0x', i):
            j = i + 2
            while j < len(s) and s[j] in '0123456789abcdefABCDEF':
                j += 1
            v = s[i + 2:j]
            out.append(('0' + v if v[0] in 'abcdefABCDEF' else v) + 'h')
            i = j
        else:
            out.append(s[i])
            i += 1
    return ''.join(out)


def rewrite(ops, txt, sym):
    """Put sym in place of the displacement or immediate txt in ops."""
    import re
    # inside a memory operand: [txt] / [... + txt] / [txt + ...]
    m = re.search(r'\[([^\]]*)\]', ops)
    if m:
        inner = m.group(1)
        parts = [p.strip() for p in re.split(r'(\+|-)', inner)]
        for k, p in enumerate(parts):
            if p == txt:
                parts[k] = sym
                new = ' '.join(parts).replace('+ -', '-')
                return ops[:m.start(1)] + new + ops[m.end(1):]
        if txt == '0':  # capstone leaves out a zero displacement
            return ops[:m.start(1)] + sym + ' + ' + inner + ops[m.end(1):]
    # an immediate: the last operand
    head, sep, tail = ops.rpartition(', ')
    if tail.strip() == txt:
        return head + sep + 'offset ' + sym
    if ops.strip() == txt:
        return 'offset ' + sym
    return ops + ' ; ?? ' + sym


def main():
    libobj, secname, lo = sys.argv[1], sys.argv[2], int(sys.argv[3], 16)
    c = Coff(libobj)
    sidx = next(k for k, s in enumerate(c.sections) if s['name'] == secname)
    outseg = os.environ.get('ASMSEG', secname)
    sec = c.sections[sidx]
    lcode = sec['data']
    hi = int(sys.argv[4], 16) if len(sys.argv) > 4 else lo + len(lcode)
    img = Xbe(_os_repo.path.join(_REPO, r'orig\Game_XboxMultiplayer.xbe'))
    icode = img.read(lo, hi - lo)
    rels = [(v, c.symbols[s]['name'], typ) for v, s, typ in sec['relocs']]
    syms = [s for s in c.symbol_list if s['section'] == sidx + 1 and s['name'][0] in '_?$']
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    li = list(md.disasm(bytes(lcode), 0))
    ii = list(md.disasm(bytes(icode), lo))
    if len(li) != len(ii) or any(a.mnemonic != b.mnemonic for a, b in zip(li, ii)):
        n = next((k for k, (a, b) in enumerate(zip(li, ii)) if a.mnemonic != b.mnemonic), min(len(li), len(ii)))
        sys.stderr.write('sequences differ at instruction %d (lib +0x%X, image 0x%X)\n'
                         % (n, li[n].address if n < len(li) else -1, ii[n].address if n < len(ii) else -1))
    labels = {}
    for s in syms:
        labels[s['value']] = (s['name'], s['class'] == 2)
    for a in li:
        if a.mnemonic.startswith('j') or a.mnemonic.startswith('loop'):
            try:
                t = int(a.op_str, 16)
            except ValueError:
                continue
            labels.setdefault(t, ('L%04X' % t, False))
    addrs = {}
    out = []
    openproc = None
    # alignment fill: a run of MASM 6 no-ops that ends on a 16-byte boundary
    fills = set()
    k = 0
    while k < len(li):
        j = k
        while j < len(li) and bytes(li[j].bytes) in FILL and (j == k or li[j].address not in labels):
            j += 1
        end = li[j].address if j < len(li) else len(lcode)
        if j > k and end % 16 == 0 and end - li[k].address < 16:
            fills.update(range(k, j))
        k = max(j, k + 1)
    for idx, (a, b) in enumerate(zip(li, ii)):
        if a.address in labels:
            name, glob = labels[a.address]
            if glob:
                if openproc:
                    out.append('%s ENDP\n' % openproc)
                out.append('; // match: %s @ 0x%08X' % (name, b.address))
                out.append('%s PROC PUBLIC' % name)
                openproc = name
            else:
                out.append('%s:' % name)
        if idx in fills:
            if not out or out[-1] != '        ALIGN16 segstart':
                out.append('        ALIGN16 segstart')
            continue
        ops = a.op_str
        mine = [(off, name, t) for off, name, t in rels if a.address <= off < a.address + a.size]
        for off, name, t in mine:
            add = struct.unpack_from('<i', lcode, off)[0]
            ival = struct.unpack_from('<I', bytes(b.bytes), off - a.address)[0]
            base = ival - add
            if t == 0x14:  # rel32 call/jmp to another symbol
                ops = name
                continue
            addrs.setdefault(name, base)
            if add:
                h = '%Xh' % add
                sym = name + '+' + ('0' + h if h[0].isalpha() else h)
            else:
                sym = name
            # capstone prints values under 10 in decimal, the rest as 0x..
            txt = ('%d' % add) if 0 <= add < 10 else ('0x%x' % (add & 0xFFFFFFFF))
            ops = rewrite(ops, txt, sym)
        if a.mnemonic.startswith('j') or a.mnemonic.startswith('loop'):
            try:
                ops = labels[int(a.op_str, 16)][0]
            except (ValueError, KeyError):
                pass
        out.append('        %s %s' % (a.mnemonic, hexify(ops) if not (a.mnemonic.startswith('j') or a.mnemonic.startswith('loop')) else ops))
    if openproc:
        out.append('%s ENDP' % openproc)
    defined = set(n for n, g in labels.values())
    ext = sorted(set(n for _, n, typ in rels if n not in defined))
    head = ['        .586', '        .mmx', '        .model flat', '        INCLUDE masm6.inc', '']
    for n in ext:
        calls = any(n == nm and typ == 0x14 for _, nm, typ in rels)
        head.append('EXTERN %s:%s' % (n, 'NEAR' if calls else 'DWORD'))
    head += ['', "%s SEGMENT PARA PUBLIC 'CODE'" % outseg, 'segstart:', '']
    print('\n'.join(head + out + ['', '%s ENDS' % outseg, '        END']))
    for name, base in sorted(addrs.items()):
        sys.stderr.write('%-24s 0x%08X\n' % (name, base))


if __name__ == '__main__':
    main()
