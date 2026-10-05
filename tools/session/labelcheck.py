"""labelcheck.py [OBJ...]: relocations to a function's own labels (switch tables, a catch
block's address) that land elsewhere in the function than the image's (PLAN M7).

The placement link's match masks relocated fields, so two identical case blocks emitted in
another order (`case 1: x = 0; break; case 2: x = 0; break;`) pass it while the image's jump
table names them the other way round. For every config/compiled.txt row whose section holds
the row's symbol at offset 0, each DIR32/REL32 relocation to a symbol of that same section
is compared with the image's field. Prints the differing ones."""
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = collections.defaultdict(dict)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows[q[1]][q[2]] = int(q[0], 16)
want = set(a.replace(os.sep, '/') for a in sys.argv[1:])
found = 0
for o in sorted(rows):
    if want and o not in want:
        continue
    try:
        c = Coff(os.path.join(ROOT, o))
    except Exception:
        continue
    by = dict((y['index'], y) for y in c.symbol_list)
    for y in c.symbol_list:
        a = rows[o].get(y['name'])
        if a is None or y['section'] <= 0 or y['value'] != 0:
            continue
        s = c.sections[y['section'] - 1]
        if not s['chars'] & 0x20 or not s['data']:
            continue
        for va, si, t in s['relocs']:
            z = by.get(si)
            if z is None or z['section'] != y['section'] or t not in (6, 0x14):
                continue
            add = struct.unpack_from('<i', s['data'], va)[0]
            want_off = z['value'] + add
            try:
                v = struct.unpack('<i', img.read(a + va, 4))[0]
            except Exception:
                continue
            got = (a + va + 4 + v - a) if t == 0x14 else ((v & 0xFFFFFFFF) - a)
            if got != want_off:
                print('0x%08X %s +0x%X: ours +0x%X (%s), image +0x%X' % (a, y['name'][:60], va, want_off,
                                                                        z['name'], got))
                found += 1
print('%d label references differ' % found)
