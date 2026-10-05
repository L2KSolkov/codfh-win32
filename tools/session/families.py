"""families.py [MIN]: the image's .text as runs of one family of objects (game, rws, rw/<dir>,
rwa, bink, xdk/<lib>, standin), with each run's address range and row count (PLAN M7: which
code the original linked as objects and which it pulled from libraries). Runs under MIN rows
(default 3) are folded into their neighbours' report as small runs."""
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MIN = int(sys.argv[1]) if len(sys.argv) > 1 else 3


def family(o):
    p = o.replace('\\', '/')
    if p.startswith('build/xdk/'):
        return 'xdk/' + p.split('/')[2]
    if p.startswith('build/src/xdk/'):
        return 'standin'
    if p.startswith('build/src/recovered/'):
        return 'game'
    if p.startswith('build/src/Source/'):
        return 'game(Source)'
    if p.startswith('build/src/rw/'):
        return 'rw/' + p.split('/')[3]
    if p.startswith('build/src/rws/'):
        return 'rws'
    if p.startswith('build/src/rwa/'):
        return 'rwa'
    if p.startswith('build/src/bink/'):
        return 'bink'
    return p.split('/')[2]


rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x2F0000:
        rows.append((int(q[0], 16), family(q[1])))
rows.sort()
runs = []
for a, f in rows:
    if runs and runs[-1][0] == f:
        runs[-1][2] = a
        runs[-1][3] += 1
    else:
        runs.append([f, a, a, 1])
small = []
for f, a, b, n in runs:
    if n >= MIN:
        if small:
            print('        (%s)' % ', '.join('%s %d' % s for s in small))
            small = []
        print('%06X-%06X %5d %s' % (a, b, n, f))
    else:
        small.append((f, n))
if small:
    print('        (%s)' % ', '.join('%s %d' % s for s in small))
