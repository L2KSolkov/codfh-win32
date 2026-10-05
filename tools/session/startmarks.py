"""startmarks.py: units whose 16.666666 constants (the unreferenced header constant every game
object starts its own .rdata with; PLAN M7) are not where the unit's .rdata begins, so the
unit is several original objects, one starting at each such constant (reported when the
unit's literals come before one)."""
import collections
import glob
import os
import re

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
rows = collections.defaultdict(list)
for l in open(os.path.join(ROOT, 'config', 'compiled.txt'), encoding='utf-8'):
    q = l.split()
    if len(q) >= 3 and q[0].startswith('0x'):
        rows[q[1]].append((int(q[0], 16), q[2]))
files = glob.glob(os.path.join(ROOT, 'src', 'recovered', '*.cpp')) + \
    glob.glob(os.path.join(ROOT, 'src', 'Source', '**', '*.cpp'), recursive=True)
for f in sorted(files):
    rel = os.path.relpath(f, ROOT).replace(os.sep, '/')
    t = open(f, encoding='utf-8', errors='replace').read()
    obj = 'build/' + rel[:-len('.cpp')] + '.obj'
    rd = sorted(a for a, x in rows[obj] if 0x3CD300 <= a < 0x426D40)
    for m in re.finditer(r'(\w+) = 16\.666666f;', t):
        n = m.group(1)
        mine = sorted(a for a, x in rows[obj] if re.search(r'\b%s\b' % n, x))
        before = [x for a, x in rows[obj] if rd and rd[0] <= a < (mine[0] if mine else 0)
                  and (x.startswith('??_C@') or x.startswith('__real@'))]
        # (a global initializer's literals come first, RWS_IMPLEMENT_CLASSID's class name)
        if mine and rd and (len(before) > 1 or [x for x in before if x.startswith('__real@')]):
            print('%-48s %-14s @%06X  .rdata %06X..%06X' % (rel, n, mine[0], rd[0], rd[-1]))
