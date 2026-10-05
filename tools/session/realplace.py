"""realplace.py [--apply] [LO HI]: place pooled float literals still uncovered (PLAN M5).

A `__real@` literal is a COMDAT the linker keeps once for the whole image, in the first object
(in link order) that has it, so an uncovered 4-byte (or 8-aligned 8-byte) value in .rdata is that
literal when an object placed around it has `__real@<its bytes>` and the name is placed nowhere
yet. Each value takes the first such address only; 16.666666f (0x41855555, a per-unit constant
with internal linkage) is left. With --apply the match lines go into the owning units (after
their last data match line below the address) and the ranges into config/splits.txt."""
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
rows = []
placed_names = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1]))
        placed_names.add(q[2])
for dp, _dn, fs in os.walk(os.path.join(ROOT, 'src')):
    for f in fs:
        if f.endswith(('.c', '.cpp')):
            for m in re.finditer(r'^// match: (__real@\w+) @ ', open(os.path.join(dp, f), encoding='utf-8',
                                                                      errors='replace').read(), re.M):
                placed_names.add(m.group(1))
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
coffs = {}


def has(obj, name):
    if obj not in coffs:
        path = os.path.join(ROOT, obj)
        coffs[obj] = set(s['name'] for s in Coff(path).symbol_list) if os.path.exists(path) else set()
    return name in coffs[obj]


import bisect  # noqa: E402
# where placed code's references to each literal point in the image: a name some code reads at
# another address (a constant of the same value, not the pooled literal) cannot be placed
targets = {}
code_rows = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x3C0000:
        code_rows.setdefault(q[1], []).append((int(q[0], 16), q[2]))
for obj, pieces in code_rows.items():
    path = os.path.join(ROOT, obj)
    if not os.path.exists(path):
        continue
    c = Coff(path)
    for addr, name in pieces:
        s = c.find_function(name)
        if s is None:
            continue
        _code, rel = c.function_bytes(s)
        for off, tgt, _r in rel:
            if tgt.startswith('__real@'):
                v = struct.unpack('<I', bytes(image.read(addr + off, 4)))[0]
                targets.setdefault(tgt, set()).add(v)
plan = []
taken = set()
for s, e in free:
    a = (s + 3) & ~3
    j = bisect.bisect_left(addrs, s)
    cands = []
    if j > 0:
        cands.append(rows[j - 1][1])
    if j < len(rows):
        cands.append(rows[j][1])
    while a + 4 <= e:
        v4 = struct.unpack('<I', bytes(image.read(a, 4)))[0]
        done = False
        if a % 8 == 0 and a + 8 <= e:
            v8 = struct.unpack('<Q', bytes(image.read(a, 8)))[0]
            n8 = '__real@%016x' % v8
            if n8 not in placed_names and n8 not in taken and targets.get(n8, {a}) == {a}:
                for o in cands:
                    if has(o, n8):
                        plan.append((a, a + 8, n8, o))
                        taken.add(n8)
                        a += 8
                        done = True
                        break
        if done:
            continue
        n4 = '__real@%08x' % v4
        if v4 not in (0, 0x41855555) and n4 not in placed_names and n4 not in taken and targets.get(n4, {a}) == {a}:
            for o in cands:
                if has(o, n4):
                    plan.append((a, a + 4, n4, o))
                    taken.add(n4)
                    break
        a += 4
for a, e, n, o in plan:
    print('0x%06X %s %s' % (a, n, o))
if not apply:
    sys.exit(0)
bysrc = {}
for a, e, n, o in plan:
    base = os.path.join(ROOT, o[len('build/'):-len('.obj')])
    src = next((base + x for x in ('.cpp', '.c') if os.path.exists(base + x)), None)
    if src:
        bysrc.setdefault(src, []).append((a, n))
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
