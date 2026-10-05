"""siteref.py SITE...: for each image call/reference site (hex address), the symbol our compiled
object's relocation at that spot names (PLAN M7: a row the M7 link drops is one our callers reach
by another name). The caller is the code row of config/compiled.txt holding the site."""
import bisect
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x3CD300:
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
starts = [r[0] for r in rows]
cache = {}
for s in sys.argv[1:]:
    site = int(s, 16)
    i = bisect.bisect_right(starts, site) - 1
    a, obj, name = rows[i]
    if obj not in cache:
        cache[obj] = Coff(os.path.join(ROOT, obj))
    try:
        c = cache[obj]
        sym = next(x for x in c.symbol_list if x['section'] > 0 and x['name'] == name)
        code, rel = c.function_bytes(sym)
    except Exception as e:
        print('%s: %s in %s: %s' % (s, name, obj, e))
        continue
    hit = [tn for off, tn, rt in rel if site - a <= off < site - a + 7]
    print('%s: %s+0x%X -> %s' % (s, name[:50], site - a, hit))
