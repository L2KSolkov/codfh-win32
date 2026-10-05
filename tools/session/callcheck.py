"""callcheck.py [PREFIX]: calls our link binds to another function than the image's (PLAN M7).

For every config/compiled.txt row whose object is linked (build/m7/game.map), each REL32
relocation's target name is looked up in the map; the image's call target address is read from
the image and its row found. When the row there is a different function and the map puts the
name somewhere else than that row's own map address, the call binds wrongly in a real link
(a database name the source copied: RpHAnimHierarchyAttachFrameIndex for Attach). Prints
`ROW +OFF: NAME (map 0x...) -> image ROW_THERE (map 0x...)`. PREFIX limits the rows' objects;
CC_DIR32=1 adds absolute references (vtable slots)."""
import bisect
import collections
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
only = sys.argv[1] if len(sys.argv) > 1 else 'build/src/'
# (CC_DIR32=1: absolute references too, data rows included: a vtable slot the image fills with
# another function's address)
DIR32 = os.environ.get('CC_DIR32') == '1'
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
mp = {}
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), encoding='utf-8', errors='replace'):
    q = l.split()
    if len(q) >= 3 and re.match(r'^[0-9a-f]{4}:[0-9a-f]{8}$', q[0]) and re.match(r'^[0-9a-f]{8}$', q[2]):
        mp.setdefault(q[1], int(q[2], 16))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
ad = [r[0] for r in rows]
cache = {}
n = 0
for a, o, nm in rows:
    if not o.startswith(only) or (a >= 0x3CD300 and not DIR32):
        continue
    if o not in cache:
        try:
            cache[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            cache[o] = None
    c = cache[o]
    if c is None:
        continue
    x = next((s for s in c.symbol_list if s['section'] > 0 and s['name'] == nm), None)
    if x is None:
        continue
    try:
        code, rel = c.function_bytes(x)
    except Exception:
        continue
    for off, tn, ty in rel:
        if ty not in ((20, 6) if DIR32 else (20,)) or tn.startswith('$') or tn not in mp:
            continue
        v = struct.unpack('<i', img.read(a + off, 4))[0]
        if ty == 6:
            t = (v - struct.unpack_from('<i', code, off)[0]) & 0xFFFFFFFF
        else:
            t = (a + off + 4 + v - struct.unpack_from('<i', code, off)[0]) & 0xFFFFFFFF
        k = bisect.bisect_right(ad, t) - 1
        if k < 0 or ad[k] != t:
            continue
        there = rows[k][2]
        if there == tn or there not in mp or mp[there] == mp[tn]:
            continue
        print('0x%08X %s +0x%X: %s (map 0x%X) -> image %s (map 0x%X)' % (a, nm[:50], off, tn, mp[tn], there, mp[there]))
        n += 1
print(n, 'calls')
