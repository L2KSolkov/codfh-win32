"""staticfold.py: the file-local functions the image folds into another object's copy (PLAN M7).

Each XGRAPHICS object has its own static operator delete; the image keeps one body
(cd3dxstack's static operator delete[] at 0x3A4422) and every object's calls reach it. A
static has no name another object can bind, so M7FORCEFOLD's /ALTERNATENAME cannot send it
there, and link.exe keeps whichever copy it meets first. For every placed section of an
object (a row), each REL32/DIR32 relocation to a static function of the object is read in
the image: when the address it reaches is another section's row (another object's, or
another body of the same object), the static folds into that row. Writes
build/m7/staticfolds.txt: OBJECT STATIC TARGET_OBJECT TARGET_NAME (rows' objects)."""
import bisect
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402
import anonfix  # noqa: E402  (anonymous-namespace hashes of other checkouts)

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in anonfix.lines(
    os.path.join(ROOT, 'config', 'compiled.txt'))) if len(q) >= 3 and q[0].startswith('0x'))
at = {}
for a, o, n in rows:
    at.setdefault(a, (o, n))
byobj = collections.defaultdict(list)
for a, o, n in rows:
    byobj[o].append((a, n))
folds = {}
for o, rs in sorted(byobj.items()):
    if not o.endswith('.obj') or o.startswith('build/src/xdk/standin'):
        continue
    try:
        c = Coff(os.path.join(ROOT, o))
    except Exception:
        continue
    byname = {}
    for y in c.symbol_list:
        if y['section'] > 0:
            byname.setdefault(y['name'], y)
    byidx = dict((y['index'], y) for y in c.symbol_list)
    rowed = set(n for a, n in rs)
    for a, n in rs:
        y = byname.get(n)
        if y is None:
            continue
        s = c.sections[y['section'] - 1]
        base = a - y['value']
        for va, si, t in s['relocs']:
            z = byidx.get(si)
            if z is None or z['class'] != 3 or z['section'] <= 0 or z['name'] in rowed or t not in (6, 0x14):
                continue
            zs = c.sections[z['section'] - 1]
            if not (zs['chars'] & 0x20) or z['name'] == zs['name'] or z['name'].startswith(('$', '__ehhandler$')):
                continue
            try:
                v = struct.unpack('<I' if t == 6 else '<i', img.read(base + va, 4))[0]
            except Exception:
                continue
            dest = v
            if t == 0x14:
                dest = base + va + 4 + v
            # (the image's address of the static, minus its offset in its section, must be a row)
            dest -= z['value']
            if dest not in at:
                continue
            to = at[dest]
            if to == (o, z['name']):
                continue
            folds.setdefault((o, z['name']), set()).add(to)
out = os.path.join(ROOT, 'build', 'm7', 'staticfolds.txt')
with open(out, 'w', encoding='utf-8') as f:
    for (o, n), tos in sorted(folds.items()):
        if len(tos) == 1:
            to = next(iter(tos))
            f.write('%s %s %s %s\n' % (o, n, to[0], to[1]))
        else:
            print('ambiguous:', o, n, sorted(tos)[:3])
print(sum(1 for v in folds.values() if len(v) == 1), 'statics fold into another row ->', out)
