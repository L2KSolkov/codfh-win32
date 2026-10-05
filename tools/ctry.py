"""ctry.py COPY AS_SRC SYM ADDR: compile the scratch copy COPY with the flags
and include directory of the tree source AS_SRC (e.g. src/rw/plugin/uvanim/
rpuvanim.c) and diff SYM against the image at ADDR with rwd.py."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import fnmatch
import os
import subprocess
import sys

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
os.chdir(_REPO)
from build_probes import compile_unit  # noqa: E402

S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

copy, as_src, sym, addr = sys.argv[1:5]
rules = []
for l in open('config/flags.txt'):
    if ':' in l and not l.startswith('#'):
        pat, fl = l.split(':', 1)
        rules.append((pat.strip(), fl.split()))
fl = [f for p, f in rules if fnmatch.fnmatch(as_src, p)][0]
# the tree source's own directory first, as the real build finds its local
# headers (rpplugin.h and the like) there
i = next(k for k, f in enumerate(fl) if f.startswith('/I'))
fl = fl[:i] + ['/I' + os.path.abspath(os.path.dirname(as_src))] + fl[i:]
obj = os.path.join(W, 'ctry.obj')
out = []
ok = compile_unit(copy, obj, fl, out=out)
if not ok:
    print('COMPILE ERROR')
    print('\n'.join(l for l in '\n'.join(out).splitlines() if 'error' in l)[:4000])
    sys.exit(1)
r = subprocess.run([sys.executable, os.path.join(S, 'rwd.py'), obj, sym, addr], capture_output=True, text=True)
print(r.stdout + r.stderr)
