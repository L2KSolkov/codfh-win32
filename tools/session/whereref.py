"""whereref.py NAME...: the image addresses rowed code's relocations to NAME reach (PLAN M7: where
the image keeps a variable no row or map places). Prints each address with its vote count and
the row there."""
import bisect
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
want = set(sys.argv[1:])
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x'))
ad = [r[0] for r in rows]
byo = collections.defaultdict(list)
for a, o, n in rows:
    byo[o].append((a, n))
votes = collections.defaultdict(collections.Counter)
for o, rs in byo.items():
    try:
        c = Coff(os.path.join(ROOT, o))
    except Exception:
        continue
    byi = dict((y['index'], y) for y in c.symbol_list)
    by = {}
    for y in c.symbol_list:
        if y['section'] > 0:
            by.setdefault(y['name'], y)
    for a, n in rs:
        y = by.get(n)
        if y is None:
            continue
        s = c.sections[y['section'] - 1]
        for va, si, t in s['relocs']:
            z = byi.get(si)
            if z is None or z['name'] not in want or t not in (6, 20) or not s['data']:
                continue
            site = a + va - y['value']
            try:
                v = struct.unpack('<I', img.read(site, 4))[0]
            except Exception:
                continue
            add = struct.unpack_from('<i', s['data'], va)[0]
            tgt = (((site + 4 + v) if t == 20 else v) - add) & 0xFFFFFFFF
            votes[z['name']][tgt] += 1
for n in sorted(want):
    for t, k in votes[n].most_common(4):
        r = rows[bisect.bisect_right(ad, t) - 1]
        print('%s 0x%08X x%d  (row 0x%08X %s %s)' % (n[:50], t, k, r[0], os.path.basename(r[1]), r[2][:40]))
