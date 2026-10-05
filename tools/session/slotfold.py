"""slotfold.py [--apply]: functions only vtables (or other data) point at that the image folds
into another function (PLAN M7): for every placed data row's DIR32 relocation naming a function
that has no row nor alias, the image's dword there is the function's address; the row there
(another function's) is what the image folded it into. Plans `NAME 0xADDR  folded ...` lines
for config/aliases.txt (--apply appends them), so the placement build and the M7 probe's forced
folds (M7FORCEFOLD) put it there: XHV's CBaseMode virtuals, deleting destructors, adjustor
thunks the link left at .text's end."""
import os
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
code = [(s['va'], s['va'] + s['vsize']) for s in img.sections if s['va'] < 0x3CD300]
rows, at = {}, {}
objrows = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        a = int(q[0], 16)
        rows.setdefault(q[2], a)
        at.setdefault(a, q[2])
        objrows.setdefault(q[1], []).append((a, q[2]))
aliased = set(l.split()[0] for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8') if l.split())
plan = {}
for o, rs in objrows.items():
    try:
        c = Coff(os.path.join(ROOT, o))
    except Exception:
        continue
    by = {}
    for y in c.symbol_list:
        if y['section'] > 0:
            by.setdefault(y['name'], y)
    for a, n in rs:
        if any(lo <= a < hi for lo, hi in code):
            continue        # (data rows only)
        y = by.get(n) or by.get('_' + n)
        if y is None:
            continue
        s = c.sections[y['section'] - 1]
        if s['chars'] & 0x20:
            continue
        later = sorted(z['value'] for z in c.symbol_list if z['section'] == y['section'] and z['value'] > y['value'])
        end = later[0] if later else s['size']
        for va, si, t in s['relocs']:
            if t != 6 or not y['value'] <= va < end:
                continue
            ts = c.symbols.get(si)
            if ts is None or ts['class'] != 2:
                continue
            tn = ts['name']
            if tn in rows or tn in aliased:
                continue
            try:
                v = struct.unpack('<I', img.read(a + va - y['value'], 4))[0]
            except ValueError:
                continue
            if v in at and any(lo <= v < hi for lo, hi in code) and at[v] != tn:
                plan.setdefault(tn, (v, at[v]))
for n, (v, t) in sorted(plan.items()):
    print('%s -> %s 0x%08X' % (n[:80], t[:60], v))
print(len(plan), 'folds')
if '--apply' in sys.argv and plan:
    with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for n, (v, t) in sorted(plan.items()):
            f.write('%-29s 0x%08X  folded (/OPT:ICF) into %s (a placed table points there; slotfold.py)\n' % (n, v, t))
