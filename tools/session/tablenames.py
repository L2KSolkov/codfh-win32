"""tablenames.py OBJ SYMBOL IMGADDR [--apply]: name XDK stand-in code by a member's pointer table (PLAN M7).

A library member's table of function pointers (OBJ's data symbol SYMBOL, its relocations naming
the functions) and the image's copy of it at IMGADDR say where the image's version of each
function starts. Each such address that starts a stand-in piece under a made-up name (_sub_)
gives that row the function's name; one inside a stand-in piece splits the piece there (at a
line boundary of its source, after a ret). Names with rows of their own, or several names at one
address (folded copies), are left alone. Prints the plan; with --apply edits config/compiled.txt
and the stand-in sources (src/xdk/standin_*.asm: label, PUBLIC, match line, references)."""
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
args = [a for a in sys.argv[1:] if not a.startswith('--')]
apply = '--apply' in sys.argv
obj, symbol, imgaddr = args[0], args[1], int(args[2], 16)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
c = Coff(os.path.join(ROOT, obj))
s = next(x for x in c.symbol_list if x['name'] == symbol and x['section'] > 0)
sec = c.sections[s['section'] - 1]
data = image.read(imgaddr, len(sec['data']) - s['value'])
img_secs = [(x['va'], x['va'] + x['vsize'], x['name']) for x in image.sections]
MERGE = {'.XPPCODE': 'XPP', '.XPPCINIT': 'XPP'}


def img_sec(a):
    return next((n for lo, hi, n in img_secs if lo <= a < hi), None)


by_addr = collections.defaultdict(set)
for va, si, t in sec['relocs']:
    off = va - s['value']
    if 0 <= off < len(data) and t == 6:
        tgt = struct.unpack_from('<I', data, off)[0]
        sym = c.symbols[si]
        # only an external the object defines (a weak or undefined name may be another
        # function; a static is reached through the object's own symbol, never by name)
        if sym['section'] <= 0 or sym['class'] != 2:
            continue
        # the target must be in the image section the function's own code goes to
        if sym['section'] > 0:
            want = c.sections[sym['section'] - 1]['name']
            want = MERGE.get(want, '.text' if want.startswith('.text') else want)
            if img_sec(tgt) != want:
                continue
        by_addr[tgt].add(sym['name'])
rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) < 0x3CD300:
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
starts = [r[0] for r in rows]
names = {r[2] for r in rows}
# the table is the image's version only when every entry whose function has a row of its own
# points at that row
row_at = collections.defaultdict(set)
for r in rows:
    row_at[r[2]].add(r[0])
for va, si, t in sec['relocs']:
    off = va - s['value']
    if 0 <= off < len(data) and t == 6:
        known = row_at.get(c.symbols[si]['name'])
        if known and struct.unpack_from('<I', data, off)[0] not in known:
            print('table differs at +0x%X (%s)' % (off, c.symbols[si]['name']))
            sys.exit(0)
rename, splits = {}, collections.defaultdict(list)
for a, ns in sorted(by_addr.items()):
    if len(ns) != 1:
        continue
    n = next(iter(ns))
    if n in names or len(n) >= 240:
        continue
    i = bisect.bisect_right(starts, a) - 1
    if i < 0 or not rows[i][1].startswith('build/src/xdk/standin_'):
        continue
    r0, o, old = rows[i]
    if a == r0:
        if old.startswith('_sub_'):
            rename[old] = n
    else:
        # (the table, consistent with every placed entry, says where the function starts: no
        # ret need end the one before, which may end in a jump)
        splits[old].append((a - r0, n, a))
# every reference a placed row makes to a new name must reach, in the image, that address
target = dict((v, by_old) for by_old, v in [])
for old, n in rename.items():
    target[n] = rows[bisect.bisect_left(starts, int(old[5:], 16))][0] if old.startswith('_sub_') else None
for old, v in splits.items():
    for o_, n, a in v:
        target[n] = a
target = dict((k, v) for k, v in target.items() if v is not None)
wrong = set()
cache = {}
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) < 3 or not q[0].startswith('0x') or q[1].startswith('build/src/xdk/standin'):
        continue
    if q[1] not in cache:
        try:
            cache[q[1]] = Coff(os.path.join(ROOT, q[1]))
        except Exception:
            cache[q[1]] = None
    cc = cache[q[1]]
    if cc is None:
        continue
    ss = next((x for x in cc.symbol_list if x['section'] > 0 and x['name'] == q[2]), None)
    if ss is None:
        continue
    try:
        code, rel = cc.function_bytes(ss)
    except Exception:
        continue
    a0 = int(q[0], 16)
    for off, tn, rt in rel:
        if tn in target:
            v = int.from_bytes(image.read(a0 + off, 4), 'little')
            if rt == 20:
                v = (a0 + off + 4 + v) & 0xFFFFFFFF
            add = int.from_bytes(code[off:off + 4], 'little') if rt == 6 else 0
            if v != target[tn] + add:
                wrong.add(tn)
rename = dict((k, v) for k, v in rename.items() if v not in wrong)
for k in list(splits):
    splits[k] = [x for x in splits[k] if x[1] not in wrong]
for k, v in rename.items():
    print('rename %s -> %s' % (k, v))
for k, v in splits.items():
    print('split %s: %s' % (k, ', '.join('+0x%X %s' % x[:2] for x in v)))
if not apply:
    sys.exit(0)
LINE_BYTES = re.compile(r'^\s*(db|dd|dw)\s+(.*?)\s*(;.*)?$')


def line_size(l):
    m = LINE_BYTES.match(l)
    if m:
        return len([x for x in m.group(2).split(',') if x.strip()]) * {'db': 1, 'dw': 2, 'dd': 4}[m.group(1)]
    w = l.split(';')[0].split()
    if w and w[0] in ('call', 'jmp'):
        return 5
    if w and w[0].startswith('j'):
        return 6
    return 0


done = set()
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    out, cur, off, pending = [], None, 0, []
    for l in L:
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', l)
        if m:
            cur, off, pending = m.group(1), 0, sorted(splits.get(m.group(1), []))
        elif cur and pending and line_size(l) and off == pending[0][0]:
            o_, nm, a = pending.pop(0)
            out += ['; // match: %s @ 0x%08X' % (nm, a), 'PUBLIC %s' % nm, '%s:' % nm]
            done.add((cur, nm))
        if cur and pending and off > pending[0][0]:
            print('%s: no line boundary at +0x%X in %s' % (os.path.basename(p), pending[0][0], cur))
            pending.pop(0)
        out.append(l)
        if cur:
            off += line_size(l)
    t = '\n'.join(out)
    for old, new in rename.items():
        t = re.sub(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(old), lambda _m: new, t)
    defined = set(re.findall(r'^PUBLIC (\S+)$', t, re.M))
    t = '\n'.join(x for x in t.split('\n') if not (x.startswith('EXTERN ') and x.split()[1].split(':')[0] in defined))
    if t != raw.replace('\r\n', '\n'):
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
path = os.path.join(ROOT, 'config', 'compiled.txt')
out = []
for l in open(path, encoding='utf-8').read().split('\n'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/xdk/standin_'):
        old = q[2]
        if old in rename:
            l = '%s %s %s' % (q[0], q[1], rename[old])
        for o_, nm, a in splits.get(old, []):
            if (old, nm) in done:
                l += '\n0x%08X %s %s' % (a, q[1], nm)
    out.append(l)
open(path, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
