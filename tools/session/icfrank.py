"""icfrank.py: for every /OPT:ICF group in build/m7/game.map (several symbols at one .text
address), which member object hosts the survivor (the object of the function placed just
before it), and its rank among the members' objects in link order (build/m7/link.rsp).
Prints a histogram of (rank, members) and the groups; PLAN M7 layout."""
import collections
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
order = {}
for i, l in enumerate(open(os.path.join(ROOT, 'build', 'm7', 'link.rsp'))):
    l = l.strip().strip('"')
    if l.endswith('.obj'):
        order[os.path.basename(l).lower()] = i
rows = []
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
    m = re.match(r'^\s*0001:([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(.*)$', l)
    if m:
        rows.append((int(m.group(3), 16), m.group(2), m.group(4).split()[-1].lower()))
rows.sort()
by = collections.defaultdict(list)
for a, n, o in rows:
    by[a].append((n, o))
addrs = sorted(by)
hist = collections.Counter()
verbose = os.environ.get('V')
for i, a in enumerate(addrs):
    mem = by[a]
    objs = sorted(set(o for n, o in mem if o in order), key=lambda o: order[o])
    if len(objs) < 2 or i == 0:
        continue
    prev = by[addrs[i - 1]]
    host = [o for n, o in prev if o in objs]
    if len(host) != 1:
        continue
    r = objs.index(host[0])
    kind = 'first' if r == 0 else 'last' if r == len(objs) - 1 else 'mid'
    hist[kind] += 1
    if verbose and (kind == 'mid' or verbose == 'all'):
        print('0x%X %s %d/%d host %s: %s' % (a, kind, r, len(objs), host[0], ' '.join(objs)))
print(dict(hist))
