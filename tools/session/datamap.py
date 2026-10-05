"""datamap.py: the image address of initialized data no row places (PLAN M7), from the placed
pieces' relocations, written to build/m7/datamap.txt as `ADDR OBJECT NAME` lines.

A library's variable without a row (libcmt's __amblksiz, xapilib's XapiTlsAllocBitmap) goes to
the end of its section in the M7 probe (data_layout's `$zzzzzzzz`). Every config/compiled.txt
row whose code or data relocates against a symbol of an initialized data section with no row
of its own reads the image's field there (minus the addend; a REL32's target computed): that
is the symbol's address. The probe keys such sections by it like rows. A symbol's votes must
agree; the address must lie in a data section of the image and hold no other row."""
import collections
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
DATA_SECS = [(s['va'], s['va'] + s['rsize']) for s in img.sections
             if s['name'] in ('.rdata', '.data', 'XON_RD', '.data1', 'BINKDATA', 'DOLBY', 'XPP')]
rows = collections.defaultdict(list)
rowname = set()
rowaddr = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows[q[1]].append((int(q[0], 16), q[2]))
        rowname.add(q[2])
        rowaddr.add(int(q[0], 16))
cache = {}


def coff(o):
    if o not in cache:
        try:
            cache[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            cache[o] = None
    return cache[o]


def in_data(a):
    return any(lo <= a < hi for lo, hi in DATA_SECS)


# every unrowed symbol of an initialized data section: (object or None for an external, name)
cands = {}
for o in rows:
    c = coff(o)
    if c is None:
        continue
    for y in c.symbol_list:
        if y['section'] <= 0 or y['class'] not in (2, 3) or y['name'] in rowname:
            continue
        s = c.sections[y['section'] - 1]
        if y['name'] == s['name'] or s['chars'] & 0x20 or s['chars'] & 0x80 or not s['chars'] & 0x40:
            continue
        cands[(o if y['class'] == 3 else None, y['name'])] = True
votes = collections.defaultdict(collections.Counter)
for o, rs in rows.items():
    c = coff(o)
    if c is None:
        continue
    by = {}
    for y in c.symbol_list:
        if y['section'] > 0:
            by.setdefault(y['name'], y)
    for a, n in rs:
        y = by.get(n)
        if y is None:
            continue
        s = c.sections[y['section'] - 1]
        later = sorted(z['value'] for z in c.symbol_list if z['section'] == y['section'] and z['value'] > y['value']
                       and z['class'] in (2, 3, 6))
        end = later[0] if later else len(s['data'])
        for va, si, t in s['relocs']:
            if not y['value'] <= va < end or t not in (6, 20):
                continue
            z = c.symbols.get(si)
            if z is None:
                continue
            key = (o if z['class'] == 3 else None, z['name'])
            # (an external another object defines, a member no row names: libcmt's __amblksiz)
            if key not in cands and not (z['class'] == 2 and z['section'] == 0 and z['value'] == 0
                                         and z['name'] not in rowname and not z['name'].startswith('__imp_')):
                continue
            site = a + va - y['value']
            try:
                v = struct.unpack('<I', img.read(site, 4))[0]
            except ValueError:
                continue
            add = struct.unpack_from('<i', s['data'], va)[0] if s['data'] else 0
            tgt = ((site + 4 + v) if t == 20 else v) - add
            tgt &= 0xFFFFFFFF
            if in_data(tgt):
                votes[key][tgt] += 1
out = []
for (o, n), cnt in votes.items():
    if len(cnt) != 1:
        continue
    a = next(iter(cnt))
    if a in rowaddr:
        continue
    out.append((a, o or '-', n))
out.sort()
with open(os.path.join(ROOT, 'build', 'm7', 'datamap.txt'), 'w') as f:
    for a, o, n in out:
        f.write('0x%08X %s %s\n' % (a, o, n))
print('%d unrowed data symbols placed (of %d)' % (len(out), len(cands)))
