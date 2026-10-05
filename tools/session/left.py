"""left.py [LO HI]: unplaced .text/BINK functions (splits ranges with no compiled piece), by 64K bucket."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import collections, sys
R = _os_repo.path.join(_REPO, 'config/')
placed = set(int(l.split()[0], 16) for l in open(R + 'compiled.txt', encoding='utf-8') if l.startswith('0x'))
lo = int(sys.argv[1], 16) if len(sys.argv) > 1 else 0
hi = int(sys.argv[2], 16) if len(sys.argv) > 2 else 1 << 32
b = collections.Counter()
rows = []
for l in open(R + 'splits.txt', encoding='utf-8'):
    p = l.split()
    if len(p) < 4 or not p[0].startswith('0x'):
        continue
    a, e, sec, name = int(p[0], 16), int(p[1], 16), p[2], p[3]
    if sec not in ('.text', 'BINK') and not sec.startswith('BINK'):
        continue
    if a in placed or not (lo <= a < hi):
        continue
    b[a >> 16] += 1
    rows.append((a, e, sec, name))
if len(sys.argv) > 1:
    for r in rows:
        print('0x%06X 0x%06X %-6s %s' % r)
else:
    for k in sorted(b):
        print('0x%02X0000 %d' % (k, b[k]))
    print('total', sum(b.values()))
