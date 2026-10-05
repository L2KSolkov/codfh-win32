"""dataowners.py [SECTION]: each binary data range with the units whose placed data surround it and
the names placed code references inside it (PLAN M5). A unit's data is contiguous in link order,
so the owner is a unit between the two neighbours (often one of them, or the referencing unit)."""
import bisect
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
want = sys.argv[1] if len(sys.argv) > 1 else '.data'
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
placed = {r[0] for r in rows}
ranges = []
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and p[2] == want and int(p[0], 16) not in placed:
        ranges.append((int(p[0], 16), int(p[1], 16)))
starts = [r[0] for r in ranges]
refs = collections.defaultdict(collections.Counter)
objs = {}
for addr, path, name in rows:
    try:
        c = objs.get(path) or Coff(os.path.join(ROOT, path))
        objs[path] = c
        code, relocs = c.function_bytes(c.find_function(name))
    except Exception:
        continue
    original = image.read(addr, len(code))
    for off, target, rtype in relocs:
        if rtype not in (IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32):
            continue
        field = struct.unpack_from('<I', original, off)[0]
        enc = addr + off + 4 + struct.unpack('<i', struct.pack('<I', field))[0] \
            if rtype == IMAGE_REL_I386_REL32 else field
        k = bisect.bisect_right(starts, enc) - 1
        if k >= 0 and ranges[k][0] <= enc < ranges[k][1]:
            refs[ranges[k]][(os.path.basename(path), target, enc)] += 1
addrs = [r[0] for r in rows]
for lo, hi in ranges:
    i = bisect.bisect_left(addrs, lo) - 1
    j = bisect.bisect_left(addrs, hi)
    before = os.path.basename(rows[i][1]) if i >= 0 else '-'
    after = os.path.basename(rows[j][1]) if j < len(rows) else '-'
    print('0x%06X-0x%06X 0x%X  after %s  before %s' % (lo, hi, hi - lo, before, after))
    for (p, t, enc), n in sorted(refs[(lo, hi)].items(), key=lambda kv: kv[0][2]):
        print('      0x%06X %-22s %s (%d)' % (enc, p, t[:70], n))
