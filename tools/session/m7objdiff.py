"""m7objdiff.py [OBJ...]: what the real link's .text has per object that the image does not (PLAN M7).

From build/m7/game.map (m7probe.py): every function symbol the map places in .text, by object,
with its size up to the next symbol. A function the map gives an address no other symbol shares
and that config/compiled.txt does not place for that object is extra code: bytes the authentic
link would add (an inline the original expanded, a template it never instantiated there, a
copy /OPT:ICF should have folded). Prints, per object in map order, its extra functions and
bytes, and the running total, so the first drift of m7layout.py has its cause.

    m7objdiff.py          objects with extra code, in map order
    m7objdiff.py OBJ...   those objects' extra functions"""
import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
placed = collections.defaultdict(set)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        placed[os.path.basename(q[1])].add(q[2])
syms = []
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
    m = re.match(r'^\s*0001:([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8}) f\s+(?:i\s+)?(\S+)\s*$', l)
    if m:
        syms.append((int(m.group(1), 16), m.group(2), m.group(4)))
syms.sort()
count = collections.Counter(a for a, _n, _o in syms)
addrs = sorted(set(a for a, _n, _o in syms))
nxt = dict(zip(addrs, addrs[1:] + [addrs[-1]]))
extra = collections.OrderedDict()
for a, n, o in syms:
    if count[a] > 1 or n in placed.get(o, ()) or n.startswith(('$L', '__ehhandler$', '__unwindfunclet$')):
        continue
    extra.setdefault(o, []).append((a, n, nxt[a] - a))
want = [a.replace('\\', '/').split('/')[-1] for a in sys.argv[1:]]
total = 0
for o, items in extra.items():
    size = sum(s for _a, _n, s in items)
    total += size
    if want and o not in want:
        continue
    print('%-40s %3d extra, 0x%05X bytes (running 0x%06X)' % (o, len(items), size, total))
    if want:
        for a, n, s in items:
            print('    0001:%08X %5X %s' % (a, s, n[:100]))
