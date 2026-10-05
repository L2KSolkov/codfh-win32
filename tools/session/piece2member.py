"""piece2member.py [--apply] [ADDR...]: stand-in pieces that are their member's own function
become member rows (PLAN M7).

Reads build/m7/piecebodies.txt (tools/session/piecebodies.py). A piece whose bytes are, at its
full length, the body of a function of the same name in an installed XDK member (one member;
copies of it under build/xdk/xdklib_* aside) is that function: its config/compiled.txt row
names the member's object, and the piece leaves src/xdk/standin_*.asm (its match block; a
segment left empty goes too). With ADDRs only those pieces. Prints the plan; --apply edits."""
import collections
import glob
import os
import re
import sys

MADE = re.compile(r'^_(sub|unk|loc)_[0-9A-F]+$')
ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
apply = '--apply' in sys.argv
only = set(int(x, 16) for x in sys.argv[1:] if x.startswith('0x'))
# P2M_SKIP: addresses (comma-separated) left as pieces (the placement link refused them)
skip = set(int(x, 16) for x in os.environ.get('P2M_SKIP', '').split(',') if x)

rownames = set()
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rownames.add(q[2])
plan = {}
for l in open(os.path.join(ROOT, 'build', 'm7', 'piecebodies.txt'), encoding='utf-8'):
    a, piece, _, rest = l.rstrip('\n').split(' ', 3)
    a = int(a, 16)
    if only and a not in only or a in skip:
        continue
    cands = []
    for c in rest.split(' | '):
        m = re.match(r'^(\S+) (\S+) \((\d+)\)$', c.strip())
        if m:
            cands.append(m.groups())
    # (P2M_MADEONLY=1: only the pieces under made-up names)
    if os.environ.get('P2M_MADEONLY') == '1' and not MADE.match(piece):
        continue
    same = [c for c in cands if c[1] == piece and '/xdklib_' not in c[0]]
    if not same and MADE.match(piece):
        # a piece under a made-up name: the one body (relocations checked, piecebodies.py)
        # names it
        # (identical bodies, XGRAPHICS' clear_node instances: the one no row names yet)
        mine = [c for c in cands if '/xdklib_' not in c[0]]
        if len(set((c[0], c[1]) for c in mine)) > 1:
            mine = [c for c in mine if c[1] not in rownames]
        if len(set((c[0], c[1]) for c in mine)) == 1:
            plan[a] = (piece, mine[0][0], mine[0][1])
        continue
    if not same:
        continue
    objs = set(c[0] for c in same)
    if len(objs) != 1:
        continue
    plan[a] = (piece, objs.pop(), piece)

taken = collections.Counter(new for piece, path, new in plan.values())
final = {}
for a, (piece, path, new) in sorted(plan.items()):
    if new != piece and (new in rownames or taken[new] > 1):
        continue
    final[a] = (piece, path, new)
    print('0x%08X %s -> %s %s' % (a, piece[:70], path, new[:60] if new != piece else ''))
print(len(final), 'pieces')
if not apply:
    sys.exit(0)

names = set(new for p, path, new in final.values())
renames = dict((p, new) for p, path, new in final.values() if new != p)
# the removed pieces' extents (config/splits.txt): a label of theirs another piece names
# ($L_ADDR, a `dd` or a jump) becomes the member function's name plus the offset
size = {}
for l in open(os.path.join(ROOT, 'config', 'splits.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 2 and q[0].startswith('0x') and q[1].startswith('0x'):
        size[int(q[0], 16)] = int(q[1], 16) - int(q[0], 16)
starts = sorted(final)


def label_target(addr):
    import bisect
    k = bisect.bisect_right(starts, addr) - 1
    if k < 0:
        return None
    s = starts[k]
    if addr >= s + size.get(s, 0):
        return None
    n = final[s][2]
    return n if addr == s else '%s+0%Xh' % (n, addr - s)


for p in sorted(glob.glob(os.path.join(ROOT, 'src', 'xdk', 'standin_*.asm'))):
    raw = open(p, 'rb').read().decode('utf-8')
    nl = '\r\n' if '\r\n' in raw else '\n'
    L = raw.replace('\r\n', '\n').split('\n')
    out = []
    i = 0
    changed = False
    while i < len(L):
        m = re.match(r'^; // match: (\S+) @ 0x([0-9A-F]{8})$', L[i])
        if m and int(m.group(2), 16) in final and final[int(m.group(2), 16)][0] == m.group(1):
            # drop the block up to the next match line or the segment's end
            j = i + 1
            while j < len(L) and not L[j].startswith('; // match: ') and not re.match(r'^\w+ ENDS$', L[j]):
                j += 1
            i = j
            changed = True
            continue
        out.append(L[i])
        i += 1
    if not changed and not any(old in raw for old in renames):
        continue
    # segments left empty
    t = '\n'.join(out)
    t = re.sub(r'\n(\w+) SEGMENT [^\n]*\n\s*\n\1 ENDS\n', '\n', t)
    t = re.sub(r'\n(\w+) SEGMENT [^\n]*\n\1 ENDS\n', '\n', t)
    defined = set(re.findall(r'^(\$L_[0-9a-f]+):', t, re.M))

    def relabel(m):
        if m.group(0) in defined:
            return m.group(0)
        r = label_target(int(m.group(1), 16))
        return r if r else m.group(0)
    t = re.sub(r'\$L_([0-9a-f]+)(?![\w@$?])', relabel, t)
    for old, new in renames.items():
        t = re.sub(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(old), lambda _m: new, t)
    # the removed names are now the members': PUBLIC lines go, references need an EXTERN
    for n in names:
        if re.search(r'^PUBLIC %s$' % re.escape(n), t, re.M):
            t = re.sub(r'^PUBLIC %s\n' % re.escape(n), '', t, flags=re.M)
        if re.search(r'(?<![\w@$?])%s(?![\w@$?])' % re.escape(n), t) and not re.search(r'^EXTERN %s:' % re.escape(n), t, re.M) \
                and not re.search(r'^%s:' % re.escape(n), t, re.M):
            first = re.search(r'^EXTERN ', t, re.M)
            pos = first.start() if first else t.index('\n') + 1
            t = t[:pos] + 'EXTERN %s:NEAR\n' % n + t[pos:]
    open(p, 'wb').write(t.replace('\n', nl).encode('utf-8'))
cp = os.path.join(ROOT, 'config', 'compiled.txt')
out = []
for l in open(cp, encoding='utf-8').read().split('\n'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x') and int(q[0], 16) in final and q[1].startswith('build/src/xdk/standin_') \
            and q[2] == final[int(q[0], 16)][0]:
        l = '%s %s %s' % (q[0], final[int(q[0], 16)][1], final[int(q[0], 16)][2])
    out.append(l)
open(cp, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
