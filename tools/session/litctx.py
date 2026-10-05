"""litctx.py UNIT [N]: the literals of build/src/recovered/UNIT.obj in section order around each
descent against the image, with the image address and the functions using each (PLAN M7: where
an object's literal order departs from the image's, and whose they are)."""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
u = sys.argv[1]
N = int(sys.argv[2]) if len(sys.argv) > 2 else 4
p = os.path.join(ROOT, 'build', 'src', 'recovered', u + '.obj')
c = Coff(p)
img = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[1].endswith('/' + u + '.obj'):
        img[q[2]] = int(q[0], 16)
users = {}
for s in c.symbol_list:
    if s['type'] == 0x20 and s['section'] > 0 and s['name'] in img:
        try:
            d, rel = c.function_bytes(s)
        except Exception:
            continue
        for off, t, ty in rel:
            users.setdefault(t, set()).add(img[s['name']])
secs = {}
for s in c.symbol_list:
    n = s['name']
    if s['section'] > 0 and (n.startswith('??_C@') or n.startswith('__real@')):
        secs.setdefault(s['section'], n)
seq = [secs[k] for k in sorted(secs) if secs[k] in img]
for i in range(1, len(seq)):
    if img[seq[i]] < img[seq[i - 1]]:
        print('== descent at %d' % i)
        for j in range(max(0, i - N), min(len(seq), i + N)):
            n = seq[j]
            print('  %s0x%06X %-42s %s' % ('>' if j == i else ' ', img[n], n[:42],
                                         ' '.join('%X' % a for a in sorted(users.get(n, ())))))
