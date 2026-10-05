"""rwatable.py ADDR: print the RenderWare Audio parameter table holding the
handler at ADDR (24-byte entries: parameter UUID*, 0, 0, type UUID*, 1,
handler), and which handlers config/symbols.txt is missing."""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import ncmp  # noqa: E402

x = ncmp._img()
d = [s for s in x.sections if s['name'] == '.data'][0]
data = x.data[d['raw']:d['raw'] + d['rsize']]


def rd(va):
    o = va - d['va']
    return struct.unpack('<I', data[o:o + 4])[0]


known = set()
for l in open(os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'config', 'symbols.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) > 2 and p[1] == 'function':
        known.add(int(p[0], 16))
target = int(sys.argv[1], 16)
m = re.search(re.escape(struct.pack('<I', target)), data)
va = d['va'] + m.start() - 20
# walk back to the table start
while rd(va - 24 + 16) == 1 and 0x230000 < rd(va - 24 + 20) < 0x260000:
    va -= 24
print('table', hex(va))
missing = []
while rd(va + 16) == 1 and 0x230000 < rd(va + 20) < 0x260000:
    h = rd(va + 20)
    print(hex(va), hex(rd(va)), hex(rd(va + 12)), hex(h), '' if h in known else 'MISSING')
    if h not in known:
        missing.append(h)
    va += 24
print('missing', ' '.join('0x%X' % h for h in sorted(set(missing))))
