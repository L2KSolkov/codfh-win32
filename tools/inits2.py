"""inits2.py: from inits.txt, pick an owning unit per initializer (the first
referencing unit not before the previous owner, in link = address order) and
find each global's declaration (extern ... NAME_<addr> ... ;) in include/ or
src/recovered/."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import glob
import os
import re

S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

ROOT = _REPO
decls = {}
files = glob.glob(os.path.join(ROOT, 'include', '**', '*.h'), recursive=True) + \
    glob.glob(os.path.join(ROOT, 'src', 'recovered', '*.cpp'))
for f in files:
    for l in open(f, encoding='utf-8', errors='replace'):
        m = re.match(r'\s*extern\s+(?:"C"\s+)?(.*?)\b(\w+_([0-9A-F]{6}))\b(\s*\[[^\]]*\])*\s*;', l)
        if m:
            decls.setdefault(m.group(3), (l.strip(), os.path.relpath(f, ROOT)))
prev = 0
for l in open(os.path.join(W, 'inits.txt')):
    p = l.split()
    a, ex, g = p[0], p[1], p[2][2:]
    refs = l.split('refs=')[1].strip().split(',') if 'refs=' in l else []
    us = sorted(int(u[5:], 16) for u in refs if u.startswith('unit_'))
    own = [u for u in us if u >= prev]
    o = own[0] if own else (us[0] if us else 0)
    prev = o
    d = decls.get(g)
    print('%s %s %s unit_%06X %s' % (a, ex, g, o, (d[0] + '  [' + d[1] + ']') if d else 'NODECL'))
