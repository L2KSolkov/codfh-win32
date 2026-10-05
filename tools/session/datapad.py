"""datapad.py: give all-zero binary gaps after placed data pieces to the piece before them (M5).

The linker's alignment fill after a data piece is zeros (xbelink generates it), so an all-zero
`-` range that directly follows a placed piece's range in the same data section is merged into
that range."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CFG = os.path.join(ROOT, 'config')
DATA = {'.rdata', '.data', '.data1', 'DOLBY', 'BINKDATA', 'XON_RD'}
x = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
placed = {int(l.split()[0], 16) for l in open(os.path.join(CFG, 'compiled.txt'), encoding='utf-8')
          if l.startswith('0x')}
out, merged, nbytes = [], 0, 0
for l in open(os.path.join(CFG, 'splits.txt'), encoding='utf-8').read().split('\n'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and p[2] in DATA and out:
        a, e = int(p[0], 16), int(p[1], 16)
        q = out[-1].split()
        if len(q) >= 4 and q[0].startswith('0x') and int(q[1], 16) == a and int(q[0], 16) in placed \
                and q[2] == p[2] and a not in placed:
            try:
                zero = not any(bytes(x.read(a, e - a)))
            except ValueError:
                zero = False
            if zero:
                out[-1] = '0x%08X 0x%08X %-10s %s' % (int(q[0], 16), e, q[2], q[3])
                merged += 1
                nbytes += e - a
                continue
    out.append(l)
open(os.path.join(CFG, 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
print('merged %d gaps, 0x%X bytes' % (merged, nbytes))
