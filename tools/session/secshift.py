"""secshift.py SECTION [STEP]: where the M7 XBE (build/m7/game.xbe) section's bytes fall
behind or run ahead of the image's (PLAN M7): samples 32-byte windows of the image section
every STEP bytes (default 0x100) and finds the nearest copy in ours; prints the offset
changes (the image's address, the delta)."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
name = sys.argv[1]
step = int(sys.argv[2], 16) if len(sys.argv) > 2 else 0x100
a = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
b = Xbe(os.path.join(ROOT, 'build', 'm7', 'game.xbe'))
sa = [s for s in a.sections if s['name'] == name][0]
sb = [s for s in b.sections if s['name'] == name][0]
da = a.read(sa['va'], sa['rsize'])
db = b.read(sb['va'], sb['rsize'])
prev = None
for i in range(0, len(da) - 16, step):
    w = da[i:i + 32]
    if w.count(0) > 16 or w.count(0xCC) > 16:
        continue
    # (the nearest occurrence: code repeats)
    best = None
    j = db.find(w, max(0, i - 0x4000), i + 0x4000)
    while j >= 0:
        if best is None or abs(j - i) < abs(best - i):
            best = j
        j = db.find(w, j + 1, i + 0x4000)
    if best is None:
        continue
    d = best - i
    if d != prev:
        print('0x%08X %+d' % (sa['va'] + i, d))
        prev = d
