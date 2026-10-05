"""m7near.py ADDR [SPAN]: the real link's functions (build/m7/game.map) around an image address,
with each one's image address (config/compiled.txt) and the difference (PLAN M7)."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
BASE = 0x12000                      # .text's image address (the map gives section offsets)
img = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        img.setdefault(q[2], int(q[0], 16))
rows = []
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
    m = re.match(r'^\s*0001:([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8}) f\s+(?:i\s+)?(\S+)\s*$', l)
    if m:
        rows.append((int(m.group(1), 16) + BASE, m.group(2), m.group(4)))
rows.sort()
a0 = int(sys.argv[1], 16)
span = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x200
for a, n, o in rows:
    if a0 - span <= a <= a0 + span:
        ia = img.get(n)
        print('%06X %-24s %s %s' % (a, o[:24], '%06X %+5X' % (ia, a - ia) if ia else '------      ', n[:70]))
