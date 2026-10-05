"""refsplit.py [--apply]: member functions the image holds inside a stand-in piece (PLAN M7).

A member's reference (a vtable slot, a call) to a function NAME that has no row of its own,
where the image's reference reaches into the middle of a stand-in code piece: the image's
version of NAME is that part of the piece (wmaxmo's CWMAXMediaObject::Release, 10 bytes into
the piece for WmaXmoThreadProc). The link pulls the installed member's NAME instead, a body the
image does not have. The piece is split there under NAME: a match block in
src/xdk/standin_*.asm at the instruction boundary, a config/compiled.txt row, the
config/splits.txt range cut in two. Prints the plan; --apply edits."""
import bisect
import collections
import glob
import os
import re
import struct
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from coff import Coff  # noqa: E402
from xbe import Xbe  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
rows = sorted((int(q[0], 16), q[1], q[2]) for q in (l.split() for l in open(
    os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8')) if len(q) >= 3 and q[0].startswith('0x'))
ad = [r[0] for r in rows]
rownames = set(r[2] for r in rows)
aliased = set(l.split()[0] for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8') if l.split())
plan = {}
cache = {}
for a, o, n in rows:
    if not o.startswith('build/xdk/'):
        continue
    if o not in cache:
        try:
            cache[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            cache[o] = None
    c = cache[o]
    if c is None:
        continue
    x = next((s for s in c.symbol_list if s['section'] > 0 and s['name'] == n), None)
    if x is None:
        continue
    try:
        code, rel = c.function_bytes(x)
    except Exception:
        continue
    for off, tn, ty in rel:
        if ty not in (6, 20) or tn in rownames or tn in aliased or tn.startswith('$') or len(tn) > 240:
            continue
        try:
            v = struct.unpack('<i', img.read(a + off, 4))[0]
        except Exception:
            continue
        add = struct.unpack_from('<i', code, off)[0]
        t = ((a + off + 4 + v) if ty == 20 else v) - add
        t &= 0xFFFFFFFF
        if t >= 0x3CD300:
            continue        # (a data piece: another version's data, not a function)
        k = bisect.bisect_right(ad, t) - 1
        if k < 0 or k + 1 >= len(rows) or not rows[k][1].startswith('build/src/xdk/standin') \
                or not ad[k] < t < ad[k + 1]:
            continue
        plan.setdefault(t, set()).add((tn, rows[k][2], ad[k], rows[k][1]))

ok = {}
for t, cands in sorted(plan.items()):
    names = set(c[0] for c in cands)
    if len(names) != 1:
        print('ambiguous 0x%08X: %s' % (t, ' '.join(sorted(names))[:200]))
        continue
    tn, pn, pa, po = next(iter(cands))
    ok[t] = (tn, pn, pa, po)
    print('0x%08X %s +0x%X -> %s' % (t, pn[:50], t - pa, tn[:80]))
print(len(ok), 'splits')
if '--apply' not in sys.argv:
    sys.exit(0)


def line_size(l):
    s = l.split(';')[0].strip()
    if not s or re.match(r'^[\w@$?]+:$', s) or s.startswith('PUBLIC ') or s.startswith('EXTERN '):
        return 0
    if s.startswith('db '):
        return len(s[3:].split(','))
    if s.startswith('dd '):
        return 4 * len(s[3:].split(','))
    if re.match(r'^(call|jmp) ', s):
        return 5
    return None


done = set()
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    want = collections.defaultdict(list)
    for t, (tn, pn, pa, po) in ok.items():
        want[pa].append((t - pa, tn, t))
    out = []
    cur = None
    pos = 0
    pend = []
    for l in L:
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', l)
        if m:
            cur = int(m.group(2), 16)
            pos = 0
            pend = sorted(want.get(cur, []))
        elif re.match(r'^\w+ (SEGMENT|ENDS)', l):
            cur, pend = None, []
        if re.match(r'^\w+ SEGMENT .*DATA', l):
            cur, pend = None, []
        if cur is not None and pend and pos == pend[0][0] and line_size(l) not in (None, 0):
            off, tn, t = pend.pop(0)
            # (a $L_ label just written stays with the new block's line)
            lab = []
            while out and re.match(r'^\$L_[0-9a-f]+:$', out[-1].strip()):
                lab.insert(0, out.pop())
            out += ['', '; // match: %s @ 0x%08X' % (tn, t), 'PUBLIC %s' % tn, '%s:' % tn] + lab
            done.add(t)
        sz = line_size(l) if cur is not None else 0
        if sz is None and cur is not None and pend:
            pend = []       # an instruction we cannot size: leave the piece
        pos += sz or 0
        out.append(l)
    t = '\n'.join(out)
    if t != raw.replace('\r\n', '\n'):
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
cp = os.path.join(ROOT, 'config', 'compiled.txt')
s = open(cp, encoding='utf-8').read().rstrip('\n').split('\n')
for t in sorted(done):
    tn, pn, pa, po = ok[t]
    s.append('0x%08X %s %s' % (t, po, tn))
open(cp, 'w', encoding='utf-8', newline='\n').write('\n'.join(s) + '\n')
sp = os.path.join(ROOT, 'config', 'splits.txt')
out = []
for l in open(sp, encoding='utf-8').read().split('\n'):
    q = l.split()
    if len(q) >= 4 and q[0].startswith('0x') and q[1].startswith('0x'):
        lo, hi = int(q[0], 16), int(q[1], 16)
        cuts = [t for t in sorted(done) if lo < t < hi]
        if cuts:
            pts = [lo] + cuts + [hi]
            for i, (x, y) in enumerate(zip(pts, pts[1:])):
                nm = q[3] if i == 0 else ok[x][0]
                out.append('0x%08X 0x%08X %-10s %s' % (x, y, q[2], nm))
            continue
    out.append(l)
open(sp, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
print(len(done), 'split')
