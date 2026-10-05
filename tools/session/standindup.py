"""standindup.py [SECTION...]: stand-in data pieces that are a library object's own data (PLAN M7).

A stand-in piece (src/xdk/standin_*.asm, src/xbe) holds image bytes no row placed when it was
cut. When a library object (build/xdk/<lib>/*.obj) the M7 link loads has an initialized data
section none of whose symbols has a row, the link emits that section a second time at its
section's end (data_layout's $zzzzzzzz): libcmt's type_info vtable was _unk_4175FE's, its
87cdisp table _unk_417864's. For each such section (default .data and .rdata), prints the
stand-in rows whose image bytes at the row equal the section's bytes, the section starting at
the row or at the stand-in's offset where the bytes sit: ADDR PIECE OBJECT SECTION SYMBOLS."""
import bisect
import collections
import glob
import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
want = sys.argv[1:] or ['.data', '.rdata']
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x'))
addrs = [r[0] for r in rows]
rowname = set(r[2] for r in rows)
standin = [(a, o, n) for a, o, n in rows if '/standin' in o.replace(os.sep, '/')]
sec_of = {}
for s in img.sections:
    if s['name'] in want:
        sec_of[s['name']] = (s['va'], s['va'] + s['rsize'])


def piece_end(a):
    i = bisect.bisect_right(addrs, a)
    return addrs[i] if i < len(addrs) else a + 4


for p in sorted(glob.glob(os.path.join(ROOT, 'build', 'xdk', '*', '*.obj'))):
    try:
        c = Coff(p)
    except Exception:
        continue
    for i, s in enumerate(c.sections):
        nm = s['name'].split('$')[0]
        if nm not in want or s['chars'] & 0x1080 or not s['data']:
            continue
        syms = [v['name'] for v in c.symbols.values() if v['section'] == i + 1 and v['class'] in (2, 3)
                and v['name'] != s['name']]
        if any(x in rowname or x.lstrip('_') in rowname for x in syms):
            continue
        d = bytes(s['data'])
        if len(d) < 4 or d.count(0) == len(d):
            continue
        lo, hi = sec_of[nm]
        for a, o, n in standin:
            if not lo <= a < hi:
                continue
            e = piece_end(a)
            blob = img.read(a, e - a)
            k = blob.find(d)
            if k >= 0 and (k + len(d) <= len(blob)):
                print('0x%08X %s+%d %s %s %s' % (a + k, n, k, os.path.relpath(p, ROOT).replace(os.sep, '/'),
                                                 s['name'], ','.join(syms[:4])))
