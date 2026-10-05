"""addmember.py LIB MEMBER...: extracts installed XDK library members (C:\\XDK\\xbox\\lib\\LIB, member
obj\\i386\\MEMBER) to build/xdk/<lib>/obj_i386_<member> and registers them in
config/xdk_members.txt (PLAN M7: a member the original link pulled for its data, whose data the
image holds in stand-in pieces until piecescan.py cuts it out)."""
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from lib import Library  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
B = chr(92)
lib, members = sys.argv[1], sys.argv[2:]
L = Library(os.path.join(os.environ.get('XDK', r'C:\XDK'), 'xbox', 'lib', lib))
data = dict(L.members)
known = set(l.split()[0] for l in open(os.path.join(ROOT, 'config', 'xdk_members.txt'), encoding='utf-8') if l.split())
lines = []
for m in members:
    full = 'obj' + B + 'i386' + B + m
    out = 'build/xdk/%s/obj_i386_%s' % (lib[:-4], m)
    if out in known:
        print('registered already', out)
        continue
    os.makedirs(os.path.join(ROOT, os.path.dirname(out)), exist_ok=True)
    open(os.path.join(ROOT, out), 'wb').write(data[full])
    lines.append('%s %s %s' % (out, lib, full))
    print(out)
with open(os.path.join(ROOT, 'config', 'xdk_members.txt'), 'a', encoding='utf-8', newline='\n') as f:
    for l in lines:
        f.write(l + '\n')
