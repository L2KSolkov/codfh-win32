"""litgaps.py: string literals of compiled units with no row whose bytes the image holds once,
in .rdata, where no row is (PLAN M7: a literal another unit's pointer initializer names, such
as unit_1ECBD0's ".index", left out of the rows, which the link then puts elsewhere). Prints
`ADDR UNIT NAME` per literal; the unit's `// match:` line goes in by hand (cmf)."""
import bisect
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rd = [s for s in img.sections if s['name'] == '.rdata'][0]
data = img.read(rd['va'], rd['rsize'])
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x'))
ad = [r[0] for r in rows]
names = set(r[2] for r in rows)
ext = {}
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 4 and q[0].startswith('0x') and q[3] != '-':
        ext[int(q[0], 16)] = int(q[1], 16)
objs = sorted(set(r[1] for r in rows if r[1].startswith('build/src/')))
seen = set()
for o in objs:
    try:
        c = Coff(os.path.join(ROOT, o))
    except Exception:
        continue
    for y in c.symbol_list:
        n = y['name']
        if not n.startswith('??_C@') or y['section'] <= 0 or n in names or n in seen:
            continue
        b = bytes(c.sections[y['section'] - 1]['data'])
        hits = [m.start() for m in re.finditer(re.escape(b), data)]
        if len(hits) != 1:
            continue
        a = rd['va'] + hits[0]
        if a % 4:
            continue
        k = bisect.bisect_right(ad, a) - 1
        if k >= 0 and (ad[k] == a or a < ext.get(ad[k], ad[k] + 1)):
            continue
        seen.add(n)
        print('0x%08X %s %s' % (a, o.split('/')[-1], n))
