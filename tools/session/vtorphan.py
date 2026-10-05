"""vtorphan.py [--apply] [LO HI]: place vtables nothing references (PLAN M5).

A class whose constructor /OPT:ICF folded into an identical one leaves its vtable in the image,
referenced by nothing (like the EH tables of ehorphan.py). For each uncovered .rdata run, the
objects placed around it are searched for `??_7` vtables placed nowhere whose every slot
(relocation) resolves, through config/compiled.txt and config/aliases.txt, to the image's dword
there, and whose other bytes match. With --apply the match lines go into the units' sources and
the ranges into config/splits.txt."""
import bisect
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = sys.argv[1:]
apply = '--apply' in args
args = [a for a in args if a != '--apply']
LO, HI = (int(args[0], 16), int(args[1], 16)) if args else (0x3C0000, 0x426000)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows, where = [], {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        a = int(q[0], 16)
        rows.append((a, q[1]))
        where.setdefault(q[2], a)
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and not l.startswith('#') and q[1].startswith('0x'):
        where.setdefault(q[0], int(q[1], 16))
placed = set(where)
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
    for f in fs:
        if f.endswith(('.c', '.cpp')):
            for m in re.finditer(r'^// match: (\S+) @ 0x([0-9A-F]+)', open(os.path.join(dp, f), encoding='utf-8',
                                                                         errors='replace').read(), re.M):
                placed.add(m.group(1))
                where.setdefault(m.group(1), int(m.group(2), 16))
rows.sort()
addrs = [a for a, o in rows]
splits = open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n')
free = []
for l in splits:
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[2] == '.rdata' and p[3] == '-':
        s, e = int(p[0], 16), int(p[1], 16)
        if LO <= s < HI:
            free.append((s, e))


def resolve(c, name):
    if name in where:
        return where[name]
    m = re.match(r'^\?(\w+)@', name)
    if m and m.group(1) in where:
        return where[m.group(1)]
    m = re.match(r'^_?(sub|unk|off|dword|flt)_([0-9A-F]{5,6})$', name)
    if m:
        return int(m.group(2), 16)
    return None


plan, taken = [], set()
for s, e in free:
    j = bisect.bisect_left(addrs, s)
    cands = [rows[j - 1][1]] if j > 0 else []
    if j < len(rows) and rows[j][1] not in cands:
        cands.append(rows[j][1])
    at = (s + 3) & ~3
    for o in cands:
        p = os.path.join(ROOT, o)
        if not os.path.exists(p):
            continue
        c = Coff(p)
        for sym in c.symbol_list:
            n = sym['name']
            if not n.startswith('??_7') or n in placed or n in taken or sym.get('section', 0) <= 0:
                continue
            data, rel = c.function_bytes(sym)
            for a in range(at, e - len(data) + 1, 4):
                img = bytes(image.read(a, len(data)))
                ok = True
                mine, theirs = bytearray(data), bytearray(img)
                for off, tgt, _r in rel:
                    v = resolve(c, tgt)
                    if v is None or v != struct.unpack_from('<I', img, off)[0]:
                        ok = False
                        break
                    mine[off:off + 4] = theirs[off:off + 4] = b'\0\0\0\0'
                if ok and bytes(mine) == bytes(theirs) and not any(x0 < a + len(data) and a < x1 for x0, x1, _n, _o in plan):
                    plan.append((a, a + len(data), n, o))
                    taken.add(n)
                    break
for a, e, n, o in sorted(plan):
    print('0x%06X-0x%06X %s %s' % (a, e, n[:70], o))
if not apply:
    sys.exit(0)
bysrc = {}
for a, e, n, o in plan:
    base = os.path.join(ROOT, o[len('build/'):-len('.obj')])
    src = next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)
    if src:
        bysrc.setdefault(src, []).append((a, n))
for src, items in bysrc.items():
    t = open(src, encoding='utf-8').read()
    for a, n in sorted(items):
        ml = '// match: %s @ 0x%08X\n' % (n, a)
        best = None
        for m in re.finditer(r'^// match: \S+ @ 0x([0-9A-F]+)\n', t, re.M):
            v = int(m.group(1), 16)
            if 0x3C0000 <= v < a and (best is None or v > best[0]):
                best = (v, m.end())
        if best:
            t = t[:best[1]] + ml + t[best[1]:]
        else:
            m = re.search(r'^// match: ', t, re.M)
            t = t[:m.start()] + ml + t[m.start():]
    open(src, 'w', encoding='utf-8', newline='\n').write(t)
for a, e, n, o in sorted(plan):
    res = []
    for l in splits:
        p = l.split()
        if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and int(p[0], 16) <= a < int(p[1], 16):
            s0, e0, sc = int(p[0], 16), int(p[1], 16), p[2]
            if a > s0:
                res.append('0x%08X 0x%08X %-10s -' % (s0, a, sc))
            res.append('0x%08X 0x%08X %-10s %s' % (a, e, sc, n))
            if e < e0:
                res.append('0x%08X 0x%08X %-10s -' % (e, e0, sc))
        else:
            res.append(l)
    splits = res
open(os.path.join(ROOT, 'config', 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(splits))
print('applied', len(plan))
