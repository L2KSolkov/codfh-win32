"""gpattern.py: classes whose ??_G objorder.py finds misplaced while the image has, between the
class's constructor and its ??_G, only the class's own virtual functions: candidates for
inlinevfs.py (PLAN M7 layout). Prints OBJ CLASS and the functions in image order."""
import collections
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x2F0000:
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
out = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'objorder.py')] + sys.argv[1:],
                     capture_output=True, text=True).stdout
objs = [l.split()[-1] for l in out.splitlines() if 'recovered' in l and ' of ' in l]
for obj in objs:
    det = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'objorder.py'), obj],
                         capture_output=True, text=True).stdout
    for l in det.splitlines():
        m = re.match(r'\s+\*\s+0x([0-9A-F]+) \?\?_G(\w+)@@', l)
        if not m:
            continue
        cls, ga = m.group(2), int(m.group(1), 16)
        ctor = [a for a, o, n in rows if o == obj and n.startswith('??0%s@@' % cls)]
        if not ctor:
            continue
        mid = [(a, n) for a, o, n in rows if ctor[0] < a < ga]
        if mid and all(re.match(r'\?vf_[0-9A-F]+@\w+@@', n) for a, n in mid):
            # by owning class (a base's inline virtuals the derived vtable emits come too)
            own = collections.OrderedDict()
            for a, n in mid:
                m2 = re.match(r'\?(vf_[0-9A-F]+)@(\w+)@@', n)
                own.setdefault(m2.group(2), []).append(m2.group(1))
            for c2, v in own.items():
                print(obj, c2, ' '.join(v), '' if c2 == cls else '(base of %s)' % cls)
