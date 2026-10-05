"""piecenames.py [--apply]: name XDK stand-in pieces by the names their callers use (PLAN M7).

A stand-in code piece under a made-up name (_sub_ADDR) that our compiled callers reach by a real
name (their relocation at the image's call site names it) is linked under the wrong name: the
callers bind the member's own version (or nothing), and the piece, unreferenced, is dropped.
For every placed row's relocation whose image target starts such a piece, the name the
relocation uses is the piece's, when every site agrees, the name has no row of its own and is no
made-up name itself. Prints the plan; --apply renames the pieces (src/xdk/standin_*.asm: label,
PUBLIC, match line, references) and their config/compiled.txt rows."""
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
apply = '--apply' in sys.argv
img = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))

rows = []
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows.append((int(q[0], 16), q[1], q[2]))
rows.sort()
at = dict((a, (o, n)) for a, o, n in rows)
names = set(n for a, o, n in rows)
MADE = re.compile(r'^_(sub|unk|loc)_[0-9A-F]+$')
cands = collections.defaultdict(set)
alias_c = collections.defaultdict(set)
cache = {}
for a, o, n in rows:
    if a >= 0x3CD300 or re.search(r'(-0x|>[0-9])', n):
        continue
    if not (o.startswith('build/src/xdk/') or o.startswith('build/xdk/') or o.startswith('build/src/')):
        continue
    if o not in cache:
        try:
            cache[o] = Coff(os.path.join(ROOT, o))
        except Exception:
            cache[o] = None
    c = cache[o]
    if c is None:
        continue
    s = next((x for x in c.symbol_list if x['section'] > 0 and x['name'] == n), None)
    if s is None:
        continue
    try:
        code, rel = c.function_bytes(s)
    except Exception:
        continue
    for off, tn, rt in rel:
        if MADE.match(tn) or tn in names or tn.startswith('$') or tn.startswith('.') or tn.startswith('__imp_') or tn.startswith('__ehhandler$') or re.search(r'_[0-9]+$', tn) and tn.startswith('?') or 'cdz_' in tn:
            continue
        v = struct.unpack('<I', img.read(a + off, 4))[0]
        if rt == 20:
            t = (a + off + 4 + v) & 0xFFFFFFFF
        elif rt == 6:
            t = (v - struct.unpack_from('<I', code, off)[0]) & 0xFFFFFFFF
        else:
            continue
        if t in at:
            to, tnm = at[t]
            if to.startswith('build/src/xdk/standin_') and MADE.match(tnm):
                cands[tnm].add(tn)
            elif '--aliases' in sys.argv and to.startswith('build/xdk/') and not MADE.match(tnm):
                alias_c[tn].add(t)
if '--aliases' in sys.argv:
    # a name our callers use for a member row of another name (an identical body the image
    # folded into that row): config/aliases.txt gets it
    have = set()
    for l in open(os.path.join(ROOT, 'config', 'aliases.txt'), encoding='utf-8'):
        q = l.split()
        if q:
            have.add(q[0])
    # only a name whose own body (some member's) is the row's body, byte for byte with its
    # relocations' targets aside: a fold
    defs = {}
    for p_ in glob.glob(os.path.join(ROOT, 'build', 'xdk', '*', '*.obj')):
        try:
            c_ = Coff(p_)
        except Exception:
            continue
        for x in c_.symbol_list:
            if x['section'] > 0 and x['class'] == 2 and x['value'] == 0:
                s_ = c_.sections[x['section'] - 1]
                if s_['name'].startswith('.text') or s_['name'] in ('XNET', 'XONLINE', 'DSOUND', 'D3D', 'XGRPH', 'WMADEC', 'XPP'):
                    defs.setdefault(x['name'], s_)

    def same(a_, b_):
        if a_ is None or b_ is None or len(a_['data']) != len(b_['data']):
            return False
        ra = set(); rb = set()
        for va, si, ty in a_['relocs']:
            ra.update(range(va, va + 4))
        for va, si, ty in b_['relocs']:
            rb.update(range(va, va + 4))
        return ra == rb and all(a_['data'][i] == b_['data'][i] for i in range(len(a_['data'])) if i not in ra)
    new = [(k, next(iter(v))) for k, v in sorted(alias_c.items()) if len(v) == 1 and k not in have
           and same(defs.get(k), defs.get(at[next(iter(v))][1]))]
    for k, a in new:
        print('%s 0x%08X  %s' % (k, a, at[a][1]))
    print(len(new), 'aliases')
    if apply:
        with open(os.path.join(ROOT, 'config', 'aliases.txt'), 'a', encoding='utf-8') as f:
            for k, a in new:
                f.write('%s 0x%08X  folded into the member row %s (our callers name it so; piecenames.py --aliases)' % (k, a, at[a][1]) + chr(10))
    sys.exit(0)
plan = dict((k, next(iter(v))) for k, v in cands.items() if len(v) == 1 and len(next(iter(v))) < 240)
taken = collections.Counter(plan.values())
plan = dict((k, v) for k, v in plan.items() if taken[v] == 1)
for k, v in sorted(plan.items()):
    print('%s -> %s' % (k, v))
print(len(plan), 'pieces')
if not apply:
    sys.exit(0)
for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    t = raw.replace('\r\n', '\n')
    t0 = t
    for old, new in plan.items():
        if old in t:
            t = re.sub(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(old), lambda _m: new, t)
    if t != t0:
        defined = set(re.findall(r'^PUBLIC (\S+)$', t, re.M))
        t = '\n'.join(x for x in t.split('\n') if not (x.startswith('EXTERN ') and x.split()[1].split(':')[0] in defined))
        open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
path = os.path.join(ROOT, 'config', 'compiled.txt')
out = []
for l in open(path, encoding='utf-8').read().split('\n'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and q[1].startswith('build/src/xdk/standin_') and q[2] in plan:
        l = '%s %s %s' % (q[0], q[1], plan[q[2]])
    out.append(l)
open(path, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
