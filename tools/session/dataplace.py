"""dataplace.py [--apply] [--xdk|--src] [--unit UNIT] [FIND]: place the data pieces
datafind.py verified (PLAN M5).

Reads FIND (default build/tooltmp/datafind.txt), keeps the `ok` rows, gives each address one
owner (the first object by path: pooled /GF literals, selectany statics and header tables are
defined by several objects), drops pieces that overlap a placed piece or each other, and for
source objects drops compiler-numbered labels ($T/$SG: they renumber when the unit changes).
With --apply:
- config/splits.txt: the piece's bytes become a range of their own, cut out of the binary
  range that held them;
- config/compiled.txt: a row per piece;
- for a source object, a block of `// match:` lines before the unit's first match line.
Prints what it placed per object."""
import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
CFG = os.path.join(ROOT, 'config')
args = sys.argv[1:]
apply = '--apply' in args
only_xdk = '--xdk' in args
only_src = '--src' in args
unit = None
if '--unit' in args:
    unit = args[args.index('--unit') + 1]
    del args[args.index('--unit'):args.index('--unit') + 2]
args = [a for a in args if not a.startswith('--')]
find = args[0] if args else os.path.join(ROOT, 'build', 'tooltmp', 'datafind.txt')

rows = []
addrs_of = collections.defaultdict(set)   # every address any object's references give a name
for l in open(find, encoding='utf-8'):
    p = l.split()
    if len(p) >= 5 and not p[2].startswith('$'):
        addrs_of[p[2]].add(int(p[0], 16))
        if p[4] == 'conflict':  # one object's references disagree: never place the name
            addrs_of[p[2]].add(-1)
for l in open(find, encoding='utf-8'):
    p = l.split()
    if len(p) >= 5 and p[4] == 'ok':
        rows.append((int(p[0], 16), p[1], p[2], int(p[3])))

compiled = [l.split() for l in open(os.path.join(CFG, 'compiled.txt'), encoding='utf-8')
            if l.startswith('0x')]
placed = {int(q[0], 16) for q in compiled}

by_addr = collections.defaultdict(list)
for r in rows:
    by_addr[r[0]].append(r)
picked = []
for a in sorted(by_addr):
    cands = sorted((r for r in by_addr[a] if '/probes/' not in r[1]), key=lambda r: (r[1], r[2]))
    if not cands:
        continue
    sizes = {r[3] for r in cands}
    r = cands[0]
    if len(sizes) != 1:
        r = max(cands, key=lambda r: r[3])
    picked.append(r)


def is_src(path):
    return not path.replace('\\', '/').startswith('build/xdk/')


def source_of(path):
    base = os.path.splitext(path.replace('\\', '/')[len('build/'):])[0]
    for ext in ('.cpp', '.c', '.asm'):
        if os.path.exists(os.path.join(ROOT, base + ext)):
            return base + ext
    return None


splits = []
for l in open(os.path.join(CFG, 'splits.txt'), encoding='utf-8'):
    p = l.split()
    if len(p) >= 4 and p[0].startswith('0x'):
        splits.append((int(p[0], 16), int(p[1], 16), p[2], p[3]))


def containing(a):
    for s in splits:
        if s[0] <= a < s[1]:
            return s
    return None


final = []
end = 0
placed_names = {q[2] for q in compiled}
batch_names = set()
for a, path, name, size in picked:
    # an external name (a pooled literal or __real@ constant) is placed once; the image's other
    # copies (from objects that keep their own) stay binary
    if not name.startswith('$') and (name in placed_names or name in batch_names
                                     or len(addrs_of[name]) > 1):
        continue
    if a in placed or size <= 0:
        continue
    if is_src(path) and re.match(r'^\$', name):
        continue
    if only_xdk and is_src(path) or only_src and not is_src(path):
        continue
    if unit and unit not in path:
        continue
    if is_src(path) and source_of(path) is None:
        continue
    if a < end:
        continue
    s = containing(a)
    if s is None or s[3] != '-' or a + size > s[1] or s[0] in placed:
        continue  # only cut binary ranges
    if any(a < p < a + size for p in placed):
        continue
    final.append((a, path, name, size))
    batch_names.add(name)
    end = a + size

per = collections.Counter(f[1] for f in final)
for p, n in sorted(per.items()):
    print('%5d %s' % (n, p))
print('pieces %d, bytes %d' % (len(final), sum(f[3] for f in final)))

if apply and final:
    cuts = {}
    for a, path, name, size in final:
        cuts[a] = (a + size, name)
    res = []
    lines = open(os.path.join(CFG, 'splits.txt'), encoding='utf-8').read().split('\n')
    for l in lines:
        p = l.split()
        if not (len(p) >= 4 and p[0].startswith('0x')) or p[3] != '-':
            res.append(l)
            continue
        lo, hi, sec = int(p[0], 16), int(p[1], 16), p[2]
        inner = sorted(a for a in cuts if lo <= a < hi)
        cur = lo
        for a in inner:
            e, name = cuts[a]
            if a > cur:
                res.append('0x%08X 0x%08X %-10s -' % (cur, a, sec))
            res.append('0x%08X 0x%08X %-10s %s' % (a, e, sec, name))
            cur = e
        if cur < hi:
            res.append('0x%08X 0x%08X %-10s -' % (cur, hi, sec))
    open(os.path.join(CFG, 'splits.txt'), 'w', encoding='utf-8', newline='\n').write('\n'.join(res))
    with open(os.path.join(CFG, 'compiled.txt'), 'a', encoding='utf-8', newline='\n') as f:
        for a, path, name, size in final:
            f.write('0x%08X %s %s\n' % (a, path, name))
    by_src = collections.defaultdict(list)
    for a, path, name, size in final:
        if is_src(path):
            by_src[source_of(path)].append((a, name))
    for src, items in by_src.items():
        full = os.path.join(ROOT, src)
        raw = open(full, 'rb').read()
        try:
            text, enc = raw.decode('utf-8'), 'utf-8'
        except UnicodeDecodeError:
            text, enc = raw.decode('cp1252'), 'cp1252'
        prefix = '; ' if src.endswith('.asm') else ''
        eol = '\r\n' if '\r\n' in text else '\n'
        block = prefix + '// Its data (PLAN M5): literals, constants and tables where the image has them.' + eol
        block += ''.join('%s// match: %s @ 0x%08X%s' % (prefix, n, a, eol) for a, n in sorted(items))
        m = re.search(r'^%s// match: ' % re.escape(prefix), text, re.M)
        if not m:
            text = text.rstrip('\r\n') + eol + eol + block
        else:
            text = text[:m.start()] + block + eol + text[m.start():]
        open(full, 'w', encoding=enc, newline='').write(text)
    import subprocess
    subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'session', 'datablocks.py')], cwd=ROOT)
