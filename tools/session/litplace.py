"""litplace.py [--apply] [LO HI]: place pooled literals (strings and floats) still uncovered (PLAN M5).

A literal COMDAT (`??_C@` string, `__real@` float) is kept once for the whole image. For each
uncovered .rdata run, the objects placed just around it are searched for literal symbols placed
nowhere yet whose bytes occur in the run at a 4-aligned address; a name is placed only when every
placed code reference to it (in any object) reads that address, since a value some code reads
elsewhere is another object's constant. 16.666666f (a per-unit constant) is left. With --apply
the match lines go into the owning units and the ranges into config/splits.txt."""
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
LIT = ('??_C@', '__real@')
rows, placed_names, code_rows = [], set(), {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        a = int(q[0], 16)
        rows.append((a, q[1]))
        placed_names.add(q[2])
        if a < 0x3C0000:
            code_rows.setdefault(q[1], []).append((a, q[2]))
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
    for f in fs:
        if f.endswith(('.c', '.cpp')):
            for m in re.finditer(r'^// match: (\S+) @ ', open(os.path.join(dp, f), encoding='utf-8',
                                                              errors='replace').read(), re.M):
                if m.group(1).startswith(LIT):
                    placed_names.add(m.group(1))
rows.sort()
addrs = [a for a, o in rows]
coffs = {}


def coff(obj):
    if obj not in coffs:
        p = os.path.join(ROOT, obj)
        coffs[obj] = Coff(p) if os.path.exists(p) else None
    return coffs[obj]


# where placed code reads each literal
targets = {}
for obj, pieces in code_rows.items():
    c = coff(obj)
    if c is None:
        continue
    for addr, name in pieces:
        s = c.find_function(name)
        if s is None:
            continue
        _code, rel = c.function_bytes(s)
        for off, tgt, _r in rel:
            if tgt.startswith(LIT):
                targets.setdefault(tgt, set()).add(struct.unpack('<I', bytes(image.read(addr + off, 4)))[0])
splits = open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8').read().split('\n')
free = []
for l in splits:
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[2] == '.rdata' and p[3] == '-':
        s, e = int(p[0], 16), int(p[1], 16)
        if LO <= s < HI:
            free.append((s, e))
plan, taken = [], set()
for s, e in free:
    j = bisect.bisect_left(addrs, s)
    cands = [rows[j - 1][1]] if j > 0 else []
    if j < len(rows) and rows[j][1] not in cands:
        cands.append(rows[j][1])
    blob = bytes(image.read(s, e - s))
    used = bytearray(e - s)
    for o in cands:
        c = coff(o)
        if c is None:
            continue
        for sym in c.symbol_list:
            n = sym['name']
            if not n.startswith(LIT) or n in placed_names or n in taken or sym.get('section', 0) <= 0:
                continue
            if n == '__real@41855555':
                continue
            data, _rel = c.function_bytes(sym)
            if not data:
                continue
            k = blob.find(data)
            while k >= 0:
                a = s + k
                if a % 4 == 0 and not any(used[k:k + len(data)]) and targets.get(n, {a}) == {a}:
                    plan.append((a, a + len(data), n, o))
                    taken.add(n)
                    used[k:k + len(data)] = b'\1' * len(data)
                    break
                k = blob.find(data, k + 1)
for a, e, n, o in sorted(plan):
    print('0x%06X-0x%06X %s %s' % (a, e, n[:60], o))
if not apply:
    sys.exit(0)
bysrc = {}
for a, e, n, o in plan:
    base = os.path.join(ROOT, o[len('build/'):-len('.obj')])
    src = next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)
    if src:
        bysrc.setdefault(src, []).append((a, n))
    elif o.startswith('build/xdk/'):
        # an installed library's object (no source): its row directly
        with open(os.path.join(ROOT, 'config', 'compiled.txt'), 'a', encoding='utf-8', newline='\n') as f:
            f.write('0x%08X %s %s\n' % (a, o, n))
for src, items in bysrc.items():
    raw = open(src, 'rb').read()
    nl = '\r\n' if b'\r\n' in raw else '\n'
    t = raw.decode('latin-1').replace('\r\n', '\n')
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
    open(src, 'wb').write(t.replace('\n', nl).encode('latin-1'))
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
