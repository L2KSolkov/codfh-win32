"""rowsat.py LO HI [OFFSET]: the code rows in [LO, HI) with where the M7 probe's map put them
(build/m7/game.map) and their shift from OFFSET (default 0x3EE6E0, the probe's usual .text one)."""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
lo, hi = int(sys.argv[1], 16), int(sys.argv[2], 16)
base = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0x3EE6E0
mp = {}
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
    q = l.split()
    if len(q) >= 3 and re.match(r'00[0-9a-f]{2}:[0-9a-f]{8}$', q[0]) and re.match(r'[0-9a-f]{8}$', q[2]):
        mp.setdefault(q[1], int(q[2], 16))
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and lo <= int(q[0], 16) < hi:
        a = int(q[0], 16)
        m = mp.get(q[2])
        print('0x%06X %-60s %-28s %s' % (a, q[2][:60], q[1].split('/')[-1][:28],
                                         '%+#x' % (m - a - base) if m else '-'))
