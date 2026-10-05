"""fillscan.py [SECTION...] [--apply]: stand-in pieces that are only short zero fill (under 16
bytes, every byte zero) in the given image sections (all when none), the alignment the link
lays down itself between aligned member contributions; --apply drops them with droppiece.py."""
import os
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
want = [a for a in sys.argv[1:] if not a.startswith('--')]
ranges = [(s['va'], s['va'] + s['vsize']) for s in img.sections if not want or s['name'] in want]
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x'))
names = []
for k, (a, o, n) in enumerate(rows[:-1]):
    e = rows[k + 1][0]
    if o.startswith('build/src/xdk/standin') and e - a < 16 and any(lo <= a < hi for lo, hi in ranges):
        try:
            b = img.read(a, e - a)
        except ValueError:
            continue
        if not any(b):
            names.append(n)
print(len(names), 'zero-fill pieces')
if '--apply' in sys.argv and names:
    subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'droppiece.py')] + names, check=True)
