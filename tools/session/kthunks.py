"""kthunks.py: the image's kernel thunk table against the M7 probe's imports (PLAN M7).

imagebld turns the link's xboxkrnl import address table (.idata$5) into the XBE's kernel thunk
table (0x3CD300: one ordinal|0x80000000 per import, in the table's order, then a zero). Reads
the ordinals and names from xboxkrnl.lib's short import members, the image's table, and the
probe's map (build/m7/game.map, `__imp_` symbols in .idata$5); prints the imports the image has
and the link lacks, those the link has and the image lacks, and whether the shared ones are in
the image's order. Writes build/m7/kthunks.txt: the image's table as names, in order."""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
XDK = os.environ.get('XDK', r'C:\xdk')
lib = open(os.path.join(XDK, 'xbox', 'lib', 'xboxkrnl.lib'), 'rb').read()
by_ord = {}
pos = 8
while pos + 60 <= len(lib):
    size = int(lib[pos + 48:pos + 58].decode().strip())
    body = lib[pos + 60:pos + 60 + size]
    if body[:4] == b'\0\0\xff\xff':
        # short import: sig1 sig2 version machine timestamp size ordinal/hint type, then names
        ordhint, typ = struct.unpack_from('<HH', body, 16)
        name = body[20:body.index(b'\0', 20)].decode('latin-1')
        if (typ & 3) == 0 or True:
            by_ord.setdefault(ordhint, name)
    pos += 60 + size + (size & 1)
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
table = []
a = 0x3CD300
while True:
    v = struct.unpack('<I', img.read(a, 4))[0]
    if not v:
        break
    table.append(v & 0xFFFF)
    a += 4
names = [by_ord.get(o, '#%d' % o) for o in table]
ours = []
for l in open(os.path.join(ROOT, 'build', 'm7', 'game.map'), encoding='utf-8', errors='replace'):
    m = re.match(r'\s*[0-9a-f]{4}:([0-9a-f]{8})\s+__imp_(\S+)\s', l)
    if m:
        ours.append((int(m.group(1), 16), m.group(2)))
seen, order = set(), []
for off, n in sorted(ours):
    if off not in seen:
        seen.add(off)
        order.append(n)
oset, iset = set(order), set(names)
print('image %d imports, link %d' % (len(names), len(order)))
print('missing from the link:', ' '.join(n for n in names if n not in oset))
print('extra in the link:', ' '.join(n for n in order if n not in iset))
shared_i = [n for n in names if n in oset]
shared_o = [n for n in order if n in iset]
print('shared in the same order:', shared_i == shared_o)
open(os.path.join(ROOT, 'build', 'm7', 'kthunks.txt'), 'w').write('\n'.join(names) + '\n')
