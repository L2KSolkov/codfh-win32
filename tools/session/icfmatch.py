"""icfmatch.py OBJ [PREFIX...]: the rowed function each unrowed packaged function of OBJ (an XDK
member or its stand-in) is identical to (PLAN M7): same bytes, same relocation targets (a
reference to itself counting as one to the other's self). The original link folded such a
function into that body (/OPT:ICF); config/aliases.txt lines make the probe fold it too
(M7FORCEFOLD). Default (no PREFIX): every unrowed function in a COMDAT code section."""
import collections
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rows = [(int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x')]
rowname = {}
for a, o, n in rows:
    rowname.setdefault(n, a)
aliased = set(l.split()[0] for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8') if l.split())


def bodies(path):
    c = Coff(path)
    byi = dict((y['index'], y) for y in c.symbol_list)
    out = {}
    for sn, s in enumerate(c.sections, 1):
        if not (s['chars'] & 0x20) or not (s['chars'] & 0x1000):
            continue
        mine = [y for y in c.symbol_list if y['section'] == sn and y['class'] == 2]
        if len(mine) != 1:
            continue
        me = mine[0]['name']
        rel = tuple(sorted((va, t, 'SELF' if byi[si]['name'] == me else byi[si]['name']) for va, si, t in s['relocs']))
        out[me] = (bytes(s['data']), rel)
    return out


obj = sys.argv[1]
want = set(sys.argv[2:])
mine = bodies(obj)
index = collections.defaultdict(list)
objs = set(o for a, o, n in rows if o.startswith('build/xdk/') or o.startswith('build/m7/'))
objs.add(obj)
for o in sorted(objs):
    try:
        b = bodies(os.path.join(ROOT, o))
    except Exception:
        continue
    for n, k in b.items():
        if n in rowname:
            index[k].append(n)
for n, k in sorted(mine.items()):
    if n in rowname or n in aliased or (want and not any(n.startswith(w) for w in want)):
        continue
    hits = sorted(set(index.get(k, [])))
    if hits:
        print('%s 0x%08X  folded (/OPT:ICF) into %s (identical body; icfmatch.py)%s' % (
            n, rowname[hits[0]], hits[0], '' if len(hits) == 1 else '  # also ' + ' '.join(hits[1:3])))
