"""datarefs.py [MIN]: who references each binary data range (PLAN M5).

For every placed piece, each relocation whose image encoding lands in a binary (`-`) range of
.rdata/.data/library data sections is attributed to that range: prints, per range of at least MIN
bytes (default 0x100), the referencing objects and the target names they use, so the owner of the
data (a unit that should define it, a library member, a stand-in) shows."""
import bisect
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import match  # noqa: E402
from coff import Coff, IMAGE_REL_I386_DIR32, IMAGE_REL_I386_REL32  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
MIN = int(sys.argv[1], 16) if len(sys.argv) > 1 else 0x100
image = Xbe(match.ORIGINAL)
ranges = []
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x') and p[3] == '-' and not p[2].startswith('.text'):
        ranges.append((int(p[0], 16), int(p[1], 16), p[2]))
ranges.sort()
starts = [r[0] for r in ranges]
refs = collections.defaultdict(collections.Counter)
objs = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) < 3 or not q[0].startswith('0x'):
        continue
    addr, path, name = int(q[0], 16), q[1], q[2]
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
            refs[ranges[k]][(path.replace('build/', '').replace('\\', '/'), target)] += 1
for r in ranges:
    if r[1] - r[0] < MIN:
        continue
    print('%s 0x%06X-0x%06X 0x%X' % (r[2], r[0], r[1], r[1] - r[0]))
    for (p, t), n in refs[r].most_common(8):
        print('      %3d %s %s' % (n, p, t[:90]))
