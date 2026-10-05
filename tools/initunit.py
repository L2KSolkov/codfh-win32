"""initunit.py UNIT [INIT_ADDR...]: define the unit's constructed globals
(rows of inits2.txt owned by UNIT with a declaration, or the listed
initializers) after its includes, build, map the object's $E symbols to the
initializer/exit addresses in definition order, and add the match lines.
Prints the addresses to hand to cmf.py; changes nothing if the counts
disagree."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os
import re
import subprocess
import sys

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff

S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

ROOT = _REPO
unit = sys.argv[1]
only = set(a.upper() for a in sys.argv[2:])
rows = []
INCS = []
for l in open(os.path.join(W, 'inits2.txt')):
    p = l.split(None, 4)
    if (only and p[0] in only) or (not only and p[3] == unit):
        if p[4].startswith('NODECL'):
            print('skip (no declaration)', l.strip())
            continue
        rows.append((p[0], p[1], p[2], p[4].split('  [')[0]))
        m = re.search(r'\[include[\\/](.+?)\]', p[4])
        if m:
            INCS.append(m.group(1).replace('\\', '/'))
if not rows:
    sys.exit('nothing to do')
src = os.path.join(ROOT, 'src', 'recovered', unit + '.cpp')
t = open(src, encoding='utf-8', newline='').read()
nl = '\r\n' if '\r\n' in t else '\n'
defs = []
for a, ex, g, d in rows:
    d2 = re.sub(r'^\s*extern\s+(?:"C"\s+)?', '', d)
    d2 = re.sub(r'\s*//.*$', '', d2)
    if any(l.strip() == d2 for l in t.split(nl)):
        continue
    defs.append(d2)
# after the last #include (and any using/pragma lines right after it)
lines = t.split(nl)
k = max(i for i, l in enumerate(lines) if l.startswith('#include'))
incl = ['#include "%s"' % h for h in dict.fromkeys(INCS) if '#include "%s"' % h not in t]
block = incl + ['', '// Globals with constructors defined here (their initializers and exit',
         '// functions at the end of .text).'] + defs
lines[k + 1:k + 1] = block
open(src, 'w', encoding='utf-8', newline='').write(nl.join(lines))
r = subprocess.run([sys.executable, os.path.join(S, 'ibuild.py')], cwd=ROOT, capture_output=True, text=True)
out = r.stdout + r.stderr
if 'error C' in out or 'FAIL src/recovered/' + unit in out:
    print('\n'.join(l for l in out.splitlines() if 'error' in l or 'FAIL' in l)[:3000])
    open(src, 'w', encoding='utf-8', newline='').write(t)
    sys.exit('compile failed; reverted')
r = subprocess.run([sys.executable, os.path.join(S, 'emap.py'), unit, '--remap'], cwd=ROOT,
                   capture_output=True, text=True)
print(r.stdout + r.stderr)
