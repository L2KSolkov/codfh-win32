"""m7extra.py SECTION [N]: the M7 probe's link (build/m7/game.map) contributions in one output
section whose names no row of config/compiled.txt (nor an alias) gives, largest first: what
the link holds there that the image does not place (PLAN M7: a section larger than the image's
is stand-in data held twice, a member's data the image's version lacks, or code /OPT:REF kept).
Sizes run to the next symbol in the map."""
import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
want = sys.argv[1]
top = int(sys.argv[2]) if len(sys.argv) > 2 else 40
names = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        names.add(q[2])
        names.add('_' + q[2])
for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
    q = l.split()
    if q:
        names.add(q[0])
        names.add('_' + q[0])
# (a static the probe packaged under a name of its own: build/m7/ordernames.txt)
_on = os.path.join(ROOT, 'build', 'm7', 'ordernames.txt')
if os.path.exists(_on):
    for l in open(_on):
        q = l.split()
        if len(q) == 2:
            names.add(q[1])
            names.add('_' + q[1].lstrip('_'))
# the section's number and extent from the map's section table
secno, secsize = None, 0
groups = collections.OrderedDict()
ents = []
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
    m = re.match(r'^ ([0-9a-f]{4}):([0-9a-f]{8}) ([0-9a-f]{8})H (\S+)\s+(CODE|DATA)', l)
    if m:
        if m.group(4) == want or (secno is not None and m.group(1) == secno):
            secno = m.group(1)
            secsize = max(secsize, int(m.group(2), 16) + int(m.group(3), 16))
        continue
    q = l.split()
    if secno and len(q) >= 4 and q[0].startswith(secno + ':') and re.match(r'[0-9a-f]{8}$', q[2]):
        ents.append((int(q[0][5:], 16), q[1], q[-1]))
ents = sorted(set(ents))
out = []
for k, (off, n, o) in enumerate(ents):
    end = ents[k + 1][0] if k + 1 < len(ents) else secsize
    if n not in names:
        out.append((end - off, off, n, o))
tot = sum(x[0] for x in out)
for sz, off, n, o in sorted(out, reverse=True)[:top]:
    print('0x%06X +0x%06X %-60s %s' % (sz, off, n[:60], o))
print('%d unrowed symbols, 0x%X bytes (section 0x%X)' % (len(out), tot, secsize))
