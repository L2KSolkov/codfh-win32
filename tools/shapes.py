import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os
import sys, struct, re, subprocess
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from xbe import Xbe
x = Xbe(_os_repo.path.join(_REPO, r'orig\Game_XboxMultiplayer.xbe'))
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

FSTART, TBL, N, BIAS, END = [int(a, 0) for a in sys.argv[1:6]]
tbl = struct.unpack('<%dI' % N, x.read(TBL, 4 * N))
out = subprocess.run([sys.executable, S + r'\xdis.py', hex(FSTART), hex(TBL)], capture_output=True, text=True).stdout
lines = []
for l in out.splitlines():
    a, ins = l.split(None, 1)
    lines.append((int(a, 16), ins.strip()))
starts = sorted(set(tbl))
case_of = {}
for i, a in enumerate(tbl):
    case_of.setdefault(a, []).append(i + BIAS)
shapes = {}
for bi, st in enumerate(starts):
    en = starts[bi + 1] if bi + 1 < len(starts) else END
    blk = [ins for a, ins in lines if st <= a < en]
    norm = []
    for ins in blk:
        n = re.sub(r'0x[0-9a-f]+', 'N', ins)
        n = re.sub(r'\b\d+\b', 'N', n)
        n = re.sub(r'\be[a-d]x\b', 'R', n)
        n = re.sub(r'\b[a-d]x\b', 'R16', n)
        n = re.sub(r'\b[a-d]l\b', 'R8', n)
        norm.append(n)
    key = '\n'.join(norm)
    shapes.setdefault(key, []).append((hex(st), case_of[st]))
for k, v in sorted(shapes.items(), key=lambda kv: -len(kv[1])):
    print('=== %d blocks: %s' % (len(v), ' '.join('%s%s' % (a, c) for a, c in v[:6])))
    print(k)
