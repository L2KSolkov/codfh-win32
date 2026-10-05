"""sectionhead.py [--apply] [SECTION...]: the rest of a member data section stand-in pieces hold
(PLAN M7). A member row placed partway into its section (strmdec_wma's _getMask, 0x50 bytes in,
after the WMA error constants every dsound WMA object carries; d3dbase's g_DefaultViewport,
before the KELVIN constants): when the image holds the whole section there (relocation fields
aside), the section's first unrowed symbol a stand-in piece covers becomes a row, cut from the
piece with cutpiece.py. Run until it cuts nothing. SECTION limits the member data sections looked
at (default all)."""
import bisect
import os
import subprocess
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
secs = [a for a in sys.argv[1:] if not a.startswith('--')]
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x'))
ad = [r[0] for r in rows]
named = set((r[1], r[2]) for r in rows)
plan = []
for k, (a, o, n) in enumerate(rows):
    if not o.startswith('build/xdk/'):
        continue
    try:
        c = Coff(os.path.join(ROOT, o))
    except Exception:
        continue
    y = next((s for s in c.symbol_list if s['section'] > 0 and s['name'] == n), None)
    if y is None:
        continue
    s = c.sections[y['section'] - 1]
    if secs and s['name'] not in secs or s['chars'] & 0xA0:
        continue
    head = a - y['value']
    # (the section's unrowed symbols, before the row or after it, that a stand-in piece holds)
    first = []
    for z in c.symbol_list:
        if z['section'] != y['section'] or z['name'] == s['name'] or (o, z['name']) in named:
            continue
        at = head + z['value']
        j = bisect.bisect_right(ad, at) - 1
        if j >= 0 and rows[j][1].startswith('build/src/xdk/standin') and rows[j + 1][0] > at:
            first.append((z['value'], z['name'], j))
    if not first:
        continue
    first.sort()
    at, j = head + first[0][0], first[0][2]
    pa, po, pn = rows[j]
    ra = set()
    for va, si, t in s['relocs']:
        ra.update(range(va, va + 4))
    d = bytes(s['data'])
    im = img.read(head, len(d))
    if all(d[q] == im[q] for q in range(len(d)) if q not in ra):
        plan.append((pa, at, o, first[0][1], pn))
plan = sorted(set(plan))
for pa, head, o, nm, pn in plan:
    print('0x%08X in %s: %s %s' % (head, pn, o.split('/')[-1], nm))
print(len(plan), 'heads')
if '--apply' in sys.argv:
    for pa, head, o, nm, pn in sorted(plan, key=lambda p: (p[0], -p[1])):
        r = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'cutpiece.py'),
                            '0x%X' % pa, '0x%X' % head, o, nm], capture_output=True, text=True)
        print(r.stdout.strip() or r.stderr.strip().splitlines()[-1])
