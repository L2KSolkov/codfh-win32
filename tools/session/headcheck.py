"""headcheck.py: member rows of one object section that imply different section starts (PLAN M7).
Same-name statics (the WMA error constants every dsound WMA object carries) were given the
neighbouring row's object by piecescan; such a row's address minus its symbol's offset disagrees
with the section's other rows. Prints each section's starts and the rows behind them."""
import collections
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rows = [(int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x')]
cache = {}
heads = collections.defaultdict(lambda: collections.defaultdict(list))
for a, o, n in rows:
    if not o.startswith('build/xdk/'):
        continue
    if o not in cache:
        try:
            cache[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            cache[o] = None
    c = cache[o]
    if c is None:
        continue
    y = next((s for s in c.symbol_list if s['section'] > 0 and s['name'] == n), None)
    if y is None or c.sections[y['section'] - 1]['chars'] & 0x1000:  # (COMDAT: placed alone)
        continue
    heads[(o, y['section'])][a - y['value']].append((a, n))
bad = 0
for (o, sn), h in sorted(heads.items()):
    if len(h) > 1:
        bad += 1
        print(o.split('/')[-1], cache[o].sections[sn - 1]['name'])
        for hd, rs in sorted(h.items()):
            print('   head 0x%08X: %d rows, 0x%08X %s' % (hd, len(rs), rs[0][0], rs[0][1][:60]))
print(bad, 'sections')
