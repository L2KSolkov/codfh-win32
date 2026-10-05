"""coveredpieces.py [--apply] [--padding]: stand-in pieces inside an XDK member section the image holds whole
(PLAN M7).

A member row places its symbol's section; when that section is longer than the row (a plain
section of several functions, libcmt's asin.obj: __CIasin, _asin and the body in one .text) and
the image holds all of it, the stand-in pieces M3 cut for its tail duplicate it in the link. For
every stand-in row inside such a section (its bytes match the image over the section's whole
length, relocation fields aside): a member symbol at the piece's address becomes the row (the
member's object, that name); a piece with none goes (its row and its block in
src/xdk/standin_*.asm). Prints the plan; --apply edits (block removal as piece2member.py)."""
import bisect
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
# (COVER_DATA=1: the data sections instead of the code)
DATA = os.environ.get('COVER_DATA') == '1'
# (COVER_ANY=1: any member section anywhere, a library's merged data in its code section too)
ANY = os.environ.get('COVER_ANY') == '1'
pieces = [(a, o, n) for a, o, n in rows if o.startswith('build/src/xdk/standin_') and (ANY or (a >= 0x3CD300) == DATA)]
paddr = [p[0] for p in pieces]
cache = {}


def coff(p):
    if p not in cache:
        try:
            cache[p] = Coff(os.path.join(ROOT, p))
        except Exception:
            cache[p] = None
    return cache[p]


plan = {}       # piece addr -> (piece name, None | (obj, name))
cover_row = {}  # piece addr -> the covering member row's address
for a, o, n in rows:
    if not o.startswith('build/xdk/') or not ANY and (a >= 0x3CD300) != DATA:
        continue
    c = coff(o)
    if c is None:
        continue
    x = next((s for s in c.symbol_list if s['section'] > 0 and s['name'] == n), None)
    if x is None:
        continue
    sec = c.sections[x['section'] - 1]
    if not ANY and bool(sec['chars'] & 0x20) == DATA or sec['chars'] & 0x80:
        continue
    start = a - x['value']
    d = bytes(sec['data'])
    lo = bisect.bisect_left(paddr, start)
    hi = bisect.bisect_left(paddr, start + len(d))
    if lo >= hi:
        continue
    ra = set()
    for va, si, t in sec['relocs']:
        ra.update(range(va, va + 4))
    try:
        i = img.read(start, len(d))
    except Exception:
        continue
    if any(d[k] != i[k] for k in range(len(d)) if k not in ra):
        continue
    at = {}
    for s in c.symbol_list:
        if s['section'] == x['section'] and s['class'] == 2:
            at.setdefault(start + s['value'], s['name'])
    for pa, po, pn in pieces[lo:hi]:
        plan[pa] = (pn, (o, at[pa]) if pa in at else None)
        cover_row[pa] = a
if '--padding' in sys.argv:
    # (--padding: also a short piece of int3 only before an aligned row, link.exe's own
    # alignment fill between two members' sections)
    allrows = [r[0] for r in rows]
    for pa, po, pn in pieces:
        k = bisect.bisect_right(allrows, pa)
        if k >= len(allrows):
            continue
        ln = allrows[k] - pa
        if 0 < ln < 16 and allrows[k] % 4 == 0 and all(b == 0xCC for b in img.read(pa, ln)):
            plan.setdefault(pa, (pn, None))
for pa, (pn, to) in sorted(plan.items()):
    print('0x%08X %s -> %s' % (pa, pn[:50], '%s %s' % (to[0].split('/')[-1], to[1][:50]) if to else 'drop'))
print(len(plan), 'pieces')
if not apply:
    sys.exit(0)
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    out = []
    i = 0
    changed = False
    while i < len(L):
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', L[i])
        if m and int(m.group(2), 16) in plan and plan[int(m.group(2), 16)][0] == m.group(1):
            j = i + 1
            while j < len(L) and not L[j].startswith('; // match: ') and not re.match(r'^\w+ ENDS$', L[j]):
                j += 1
            i = j
            changed = True
            continue
        out.append(L[i])
        i += 1
    if not changed:
        continue
    t = '\n'.join(out)
    t = re.sub(r'\n(\w+) SEGMENT [^\n]*\n\s*\n\1 ENDS\n', '\n', t)
    t = re.sub(r'\n(\w+) SEGMENT [^\n]*\n\1 ENDS\n', '\n', t)
    for pa, (pn, to) in plan.items():
        t = re.sub(r'^PUBLIC %s\n' % re.escape(pn), '', t, flags=re.M)
        new = to[1] if to else None
        if re.search(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(pn), t):
            if new is None:
                print('  still referenced:', pn, os.path.basename(p))
                continue
            t = re.sub(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(pn), lambda _m: new, t)
            if not re.search(r'^EXTERN %s:' % re.escape(new), t, re.M):
                first = re.search(r'^EXTERN ', t, re.M)
                pos = first.start() if first else t.index('\n') + 1
                t = t[:pos] + 'EXTERN %s:NEAR\n' % new + t[pos:]
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
cp = os.path.join(ROOT, 'config', 'compiled.txt')
out = []
for l in open(cp, encoding='utf-8').read().split('\n'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) in plan and q[1].startswith('build/src/xdk/standin_') \
            and q[2] == plan[int(q[0], 16)][0]:
        to = plan[int(q[0], 16)][1]
        if to is None:
            continue
        l = '%s %s %s' % (q[0], to[0], to[1])
    out.append(l)
open(cp, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
# config/splits.txt: a dropped piece's extent joins the entry before it (the member row's,
# whose section covers both)
sp = os.path.join(ROOT, 'config', 'splits.txt')
lines = open(sp, encoding='utf-8').read().split('\n')
idx = {}
for k, l in enumerate(lines):
    q = l.split()
    if len(q) >= 2 and q[0].startswith('0x') and q[1].startswith('0x'):
        idx[int(q[0], 16)] = k
drop = set()
for pa, (pn, to) in sorted(plan.items()):
    # (only a piece after its member's row: one before it, the start of the row's section,
    # keeps its extent, which the placement build fills from the image)
    if to is not None or pa not in idx or cover_row.get(pa, 0) > pa:
        continue
    k = idx[pa]
    q = lines[k].split()
    end = q[1]
    j = k - 1
    while j >= 0 and (j in drop or not lines[j].startswith('0x')):
        j -= 1
    pq = lines[j].split(None, 2)
    if int(pq[1], 16) == pa:
        lines[j] = '%s %s %s' % (pq[0], end, pq[2])
        drop.add(k)
open(sp, 'w', encoding='utf-8', newline='\n').write('\n'.join(l for k, l in enumerate(lines) if k not in drop))
