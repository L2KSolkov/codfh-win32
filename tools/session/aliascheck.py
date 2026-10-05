"""aliascheck.py: check config/aliases.txt against the compiled objects (PLAN M5/M7).

An alias says a name lives at an address the image holds: an ICF fold, a function placed under
another name. When some compiled object defines that name as a function, its bytes (relocations
masked, the image's encodings checked as tools/match.py does) must be the image's at the alias's
address. Prints each alias whose compiled body differs, with the address where an identical copy
(placed elsewhere under another name) exists when one does."""
import glob
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
image = Xbe(match.ORIGINAL)
aliases = []
for k, l in enumerate(open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8')):
    q = l.split('#', 1)[0].split()
    if len(q) >= 2 and q[1].startswith('0x') and q[0].startswith('?'):
        aliases.append((k + 1, q[0], int(q[1], 16)))
want = {n for _, n, _ in aliases}
where = {}
for o in glob.glob(os.path.join(ROOT, 'build', 'src', '**', '*.obj'), recursive=True):
    if os.sep + 'xdk' + os.sep in o:
        continue
    try:
        c = Coff(o)
    except Exception:
        continue
    for s in c.symbol_list:
        if s['name'] in want and s['section'] > 0 and (s['type'] >> 4) == 2 and s['name'] not in where:
            where[s['name']] = c
bad = 0
for line, name, addr in aliases:
    c = where.get(name)
    if c is None:
        continue
    try:
        ok, msg = match.compare(c, name, addr, image, {})
    except Exception as e:
        ok, msg = False, str(e)
    if not ok:
        bad += 1
        print('line %d: %s @ 0x%X: %s' % (line, name, addr, msg.split('\n')[0][-100:]))
print('%d of %d checked aliases differ' % (bad, sum(1 for _, n, _ in aliases if n in where)))
