"""ehrowcheck.py [--fix]: EH table rows named after the wrong handler (PLAN M7).

A funcinfo row `__ehhandler$F>1` names the table the handler of F loads. The placement link
compares the tables' bytes with relocations masked, so two tables of one unit with the same
shape can carry each other's names unnoticed; the M7 link keys tables by these names, so a
swap moves them. For each funcinfo row, the image's handler that loads it (`mov eax, offset
funcinfo` in .text$x) is found and its row name compared. With --fix, the rows of a
mislabelled table (`>1` and every `>1>N` below it) are renamed after the handler that loads
them, when that handler's own table rows are swapped the same way (a pure swap)."""
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
CFG = os.path.join(ROOT, 'config', 'compiled.txt')
lines = open(CFG, encoding='utf-8').read().split('\n')
rows = []
for i, l in enumerate(lines):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2], i))
handler_at = {}
for a, o, n, i in rows:
    if n.startswith('__ehhandler$') and '>' not in n and not re.search(r'-0x[0-9A-Fa-f]+$', n):
        handler_at[a] = n
# the funcinfo each handler loads
loads = {}
for a, n in handler_at.items():
    try:
        b = img.read(a, 5)
    except Exception:
        continue
    if b[:1] == b'\xb8':
        loads.setdefault(struct.unpack_from('<I', b, 1)[0], []).append(n)
bad = []
for a, o, n, i in rows:
    if n.startswith('__ehhandler$') and n.endswith('>1'):
        hs = loads.get(a, [])
        want = n[:-2]
        if hs and want not in hs:
            bad.append((a, o, want, hs))
for a, o, want, hs in bad:
    print('0x%08X %s: row %s, loaded by %s' % (a, o.split('/')[-1], want[12:90], ', '.join(h[12:90] for h in hs)))
print('%d funcinfo rows named after another handler' % len(bad))
if '--fix' in sys.argv[1:]:
    ren = {}
    for a, o, want, hs in bad:
        if len(hs) == 1:
            ren[(o, want)] = hs[0]
    done = 0
    for a, o, n, i in rows:
        m = re.match(r'^(__ehhandler\$.*?)(>1(?:>\d+)*)$', n)
        if m and (o, m.group(1)) in ren:
            lines[i] = lines[i].replace(n, ren[(o, m.group(1))] + m.group(2), 1)
            done += 1
    open(CFG, 'w', encoding='utf-8', newline='\n').write('\n'.join(lines))
    print('%d rows renamed' % done)
