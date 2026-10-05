"""img2asm.py START END [NAME=SYMBOL ...] [RAW=ADDR,...]: transcribe an image function as the
body of an MSVC `__asm` block (for the `__declspec(naked)` transcriptions the
owner allows in src/bink, docs/questions.md).

Jump targets inside the range become labels (L_xxxxxx). Absolute operands
(memory and immediates) that config/symbols.txt or config/aliases.txt name
are written as C identifiers (the decoration stripped: `_Name@N` -> Name,
`_name` -> name), with `offset` for immediates and `+N` for an offset into
a named object; call targets the same way. NAME=SYMBOL arguments override the
identifier used for a symbol (e.g. a static's alias); RAW lists instructions
to emit as `_emit` bytes, for the encodings the inline assembler would choose
differently (the 7-byte `lea esp, [esp]` fill and the like). Unnamed absolute
operands are left as numbers and reported on stderr."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import re
import struct
import sys

import capstone

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from xbe import Xbe  # noqa: E402

ROOT = _REPO


def names():
    out = {}
    for path in ('config/symbols.txt', 'config/aliases.txt'):
        for l in open(ROOT + '/' + path, encoding='utf-8'):
            p = l.split()
            if not p or p[0].startswith('#'):
                continue
            if path.endswith('symbols.txt') and p[0].startswith('0x') and len(p) >= 5:
                out.setdefault(int(p[0], 16), (p[-1], int(p[2], 16) if p[2].startswith('0x') else 4))
            elif path.endswith('aliases.txt') and len(p) >= 2 and p[1].startswith('0x'):
                out[int(p[1], 16)] = (p[0], 4)
    return out


def ident(sym, over):
    if sym in over:
        return over[sym]
    s = sym
    if s.startswith('_'):
        s = s[1:]
    s = re.sub(r'@\d+$', '', s)
    return s


def main():
    lo, hi = int(sys.argv[1], 16), int(sys.argv[2], 16)
    over = dict(a.split('=', 1) for a in sys.argv[3:] if not a.startswith('RAW='))
    raw = set()
    for a in sys.argv[3:]:
        if a.startswith('RAW='):
            raw |= set(int(x, 16) for x in a[4:].split(',') if x)
    img = Xbe(ROOT + r'\orig\Game_XboxMultiplayer.xbe')
    code = img.read(lo, hi - lo)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    ins = list(md.disasm(bytes(code), lo))
    tab = names()
    sorted_addrs = sorted(tab)

    def lookup(v):
        if v in tab:
            return ident(tab[v][0], over), 0
        # inside a named object
        import bisect
        k = bisect.bisect_right(sorted_addrs, v) - 1
        if k >= 0:
            a = sorted_addrs[k]
            name, size = tab[a]
            if 0 < v - a < max(size, 0x40) and not name.startswith('sub_') and 'function' not in name:
                return ident(name, over), v - a
        return None, 0

    targets = set()
    for i in ins:
        if i.mnemonic.startswith('j') or i.mnemonic == 'loop':
            try:
                targets.add(int(i.op_str, 16))
            except ValueError:
                pass
    out = []
    for i in ins:
        if i.address in targets:
            out.append('  L_%06x:' % i.address)
        ops = i.op_str
        if (i.mnemonic.startswith('j') or i.mnemonic == 'loop') and re.match(r'^0x[0-9a-f]+$', ops):
            t = int(ops, 16)
            if lo <= t < hi:
                ops = 'L_%06x' % t
            else:
                n, off = lookup(t)
                ops = n if n and not off else ops
                if not n:
                    sys.stderr.write('0x%x: jump out to 0x%x\n' % (i.address, t))
        elif i.mnemonic == 'call' and re.match(r'^0x[0-9a-f]+$', ops):
            t = int(ops, 16)
            n, off = lookup(t)
            if n and not off:
                ops = n
            else:
                sys.stderr.write('0x%x: call to unnamed 0x%x\n' % (i.address, t))
        else:
            def sub(m):
                v = int(m.group(0), 16)
                if v < 0x10000:
                    h = '%Xh' % v
                    return ('0' + h if h[0].isalpha() else h) if v > 9 else str(v)
                n, off = lookup(v)
                if n:
                    return n + ('+%d' % off if off else '')
                sys.stderr.write('0x%x: unnamed 0x%x\n' % (i.address, v))
                return '0%Xh' % v
            named = []

            def sub2(m):
                r = sub(m)
                if re.match(r'^[A-Za-z_]', r):
                    named.append(r)
                return r
            ops2 = re.sub(r'0x[0-9a-f]+', sub2, ops)
            # an immediate that names something is its address
            if named and '[' not in ops2.split(',')[-1] and re.search(r'[A-Za-z_]', ops2.split(',')[-1]) \
                    and not re.match(r'^\s*[0-9A-F]+h$', ops2.split(',')[-1].strip()):
                parts = ops2.rsplit(',', 1) if ',' in ops2 else ['', ops2]
                last = parts[-1].strip()
                if not re.match(r'^[a-z]{2,3}$', last):
                    ops2 = (parts[0] + ', ' if parts[0] else '') + 'offset ' + last
            ops = ops2
        mn = i.mnemonic
        if i.address in raw:
            out.append('    // %s %s' % (i.mnemonic, i.op_str))
            out += ['    _emit 0x%02X' % b for b in i.bytes]
            continue
        if re.match(r'^(rep[a-z]* )?(stos|movs|lods|scas|cmps)[bwd]$', mn):
            ops = ''
        elif mn in ('faddp', 'fsubp', 'fsubrp', 'fmulp', 'fdivp', 'fdivrp') and re.match(r'^st\(\d\)$', ops):
            ops = ops + ', st'
        out.append(('    %s %s' % (mn, ops)).rstrip())
    print('\n'.join(out))


if __name__ == '__main__':
    main()
