"""vtvotes.py: for every virtual function name a compiled vtable slot names, the image addresses
that slot holds across all vtables (placed or not) (PLAN M5).

A name with one address everywhere is settled. A name with several is a base virtual that some
derived classes override without their recovered class declaring it: the base's own address is the
one the base's vtable (and the derived classes that really inherit it) hold; each other address is
an override missing from a derived class. Prints the contested names with each address's
vtables, the current alias/placement, and the base class's own vtable's address when known."""
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff, IMAGE_REL_I386_DIR32  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
image = Xbe(match.ORIGINAL)
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
placed_name = {}
for a, o, n in rows:
    placed_name.setdefault(n, a)

# every vtable address referenced or placed: (vtable name, image address, obj)
vts = {}
for a, o, n in rows:
    if n.startswith('??_7') and 'build/src/' in o:
        vts[(n, a)] = o
objs = {}
for a, o, n in rows:
    if 'build/src/' not in o or o.startswith('build/src/xdk'):
        continue
    try:
        c = objs.get(o) or Coff(os.path.join(ROOT, o))
        objs[o] = c
        code, relocs = c.function_bytes(c.find_function(n))
    except Exception:
        continue
    orig = image.read(a, len(code))
    for off, t, rt in relocs:
        if t.startswith('??_7') and rt == IMAGE_REL_I386_DIR32:
            enc = struct.unpack_from('<I', orig, off)[0] - struct.unpack_from('<i', code, off)[0]
            vts.setdefault((t, enc), o)
votes = collections.defaultdict(lambda: collections.defaultdict(list))
for (vt, addr), o in vts.items():
    c = objs.get(o) or Coff(os.path.join(ROOT, o))
    objs[o] = c
    s = c.find_function(vt)
    if s is None:
        continue
    code, relocs = c.function_bytes(s)
    img = image.read(addr, len(code))
    for off, t, rt in relocs:
        v = struct.unpack_from('<I', img, off)[0] - struct.unpack_from('<i', code, off)[0]
        votes[t][v].append(vt)
out = []
for t, by in votes.items():
    if len(by) < 2:
        continue
    cls = re.match(r'^\?\w+@(\w+)@@', t)
    own = '??_7%s@@6B@' % cls.group(1) if cls else None
    base = [v for v, l in by.items() if own in l]
    cur = match.resolve_name(t, {}) or placed_name.get(t)
    out.append((t, cur, base, by))
for t, cur, base, by in sorted(out):
    print('%s  now=%s  base=%s' % (t, hex(cur) if cur else None, [hex(b) for b in base]))
    for v, l in sorted(by.items(), key=lambda kv: -len(kv[1])):
        print('    0x%06X x%d  %s' % (v, len(l), ' '.join(sorted(set(x[4:].split('@')[0] for x in l)))[:150]))
