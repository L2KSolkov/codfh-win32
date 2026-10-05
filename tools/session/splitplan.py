"""splitplan.py [UNIT...]: object boundaries inside game units from .rdata start markers (PLAN M7).

Every game object starts its own .rdata with an unreferenced copy of a header constant,
16.666666 (startmarks.py); the literals after it, up to the next marker, are that object's
(a shared literal is the first defining object's). This walks the game's .rdata in address
order, cuts it at each marker row, and gives each literal row the function that defines it
first (the lowest-addressed function, in any game object, that references it). Per unit with
more than one block, it prints each block's marker and the code range of its defining
functions: an object boundary lies between one block's last function and the next one's first.
Markers inside another unit's block are flagged (the marker's row belongs to that unit)."""
import collections
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
only = set(sys.argv[1:])
rows = []
addr_of = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and (q[1].startswith('build/src/recovered/')
                                                  or q[1].startswith('build/src/Source/')):
        a = int(q[0], 16)
        rows.append((a, q[1], q[2]))
        addr_of[(q[1], q[2])] = a
# marker names: constants defined as 16.666666f
markers = set()
for f in glob.glob(os.path.join(ROOT, 'src', 'recovered', '*.cpp')) + \
        glob.glob(os.path.join(ROOT, 'src', 'Source', '**', '*.cpp'), recursive=True):
    for m in re.finditer(r'(\w+) = 16\.666666f;', open(f, encoding='utf-8', errors='replace').read()):
        markers.add(m.group(1))
# first user of each referenced name, over every game object's code
first_user = {}
for obj in sorted(set(o for _, o, _ in rows)):
    p = os.path.join(ROOT, obj)
    if not os.path.exists(p):
        continue
    c = Coff(p)
    for s in c.sections:
        if not (s['chars'] & 0x20):
            continue
        funcs = sorted((x['value'], x['name']) for x in c.symbol_list
                       if x['section'] == s['index'] and x['class'] in (2, 3) and x['type'] == 0x20)
        for v, si, t in s['relocs']:
            owner = None
            for fv, fn in funcs:
                if fv <= v:
                    owner = fn
            fa = addr_of.get((obj, owner))
            if fa is None:
                continue
            tgt = c.symbols[si]['name']
            if tgt not in first_user or fa < first_user[tgt][0]:
                first_user[tgt] = (fa, obj)
rd = sorted((a, o, n) for a, o, n in rows if 0x3CD300 <= a < 0x41A000)
blocks = []
for a, o, n in rd:
    is_marker = any(re.search(r'\b%s\b' % re.escape(m), n) for m in markers if m in n)
    if is_marker or not blocks:
        blocks.append({'marker': (a, o, n) if is_marker else None, 'users': []})
    if not is_marker and n in first_user:
        blocks[-1]['users'].append(first_user[n])
per_unit = collections.defaultdict(list)
for b in blocks:
    objs = collections.Counter(o for _, o in b['users'])
    if not objs:
        continue
    home = objs.most_common(1)[0][0]
    fs = sorted(fa for fa, o in b['users'] if o == home)
    per_unit[home].append((b['marker'], fs[0], fs[-1]))
for u, bl in sorted(per_unit.items(), key=lambda kv: kv[1][0][1]):
    name = os.path.basename(u)[:-4]
    if only and name not in only:
        continue
    flags = [m for m, _, _ in bl if m and m[1] != u]
    if len(bl) > 1 or flags:
        print('%s: %d blocks' % (name, len(bl)))
        for m, lo, hi in bl:
            ms = '%06X %s%s' % (m[0], m[2][:24], '' if m[1] == u else ' (row: %s)' % os.path.basename(m[1])) if m else '-'
            print('    marker %-48s code %06X..%06X' % (ms, lo, hi))
