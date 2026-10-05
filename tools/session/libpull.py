"""libpull.py LIB: a library's members in the image's order, in the M7 link's order
(build/m7/game.map) and in the archive's order (PLAN M7: library members come out in the
order link.exe pulls them)."""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
lib = sys.argv[1]
stem = os.path.splitext(lib)[0]
first = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and (q[1].startswith('build/xdk/%s/' % stem) or q[1].startswith('build/xdk/xdklib_%s/' % stem) or (stem == 'binkxbox' and q[1].startswith('build/src/bink/'))):
        a = int(q[0], 16)
        if a < 0x3C0000:
            o = os.path.basename(q[1])[:-4]
            o = o[len('obj_i386_'):] if o.startswith('obj_i386_') else o
            first[o] = min(first.get(o, 1 << 32), a)
img = [o for o, a in sorted(first.items(), key=lambda x: x[1])]
ours = {}
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), errors='replace'):
    m = re.match(r'^\s*[0-9a-f]{4}:([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(.*)$', l)
    if m and (stem + ':') in m.group(4):
        o = m.group(4).split(':')[-1].strip().replace('\\', '/')
        o = os.path.basename(o)[:-4]
        ours.setdefault(o, int(m.group(3), 16))
our = [o for o, a in sorted(ours.items(), key=lambda x: x[1])]
path = os.path.join(ROOT, 'build', 'm7', 'lib', lib)
if not os.path.exists(path):
    path = os.path.join(r'C:\XDK\xbox\lib', lib)
r = subprocess.run([r'C:\XDK\xbox\bin\vc71\lib.exe', '/nologo', '/LIST', path], capture_output=True, text=True)
arc = [os.path.basename(l.strip().replace('\\', '/'))[:-4] for l in r.stdout.splitlines() if l.strip()]
print('image  :', ' '.join(img))
print('ours   :', ' '.join(o for o in our if o in first))
print('archive:', ' '.join(o for o in arc if o in first))
