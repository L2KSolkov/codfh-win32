"""fdiff.py FILE AS_SRC SYM:ADDR... [-v SYM]: compile FILE once with AS_SRC's
flags and print each SYM's real diff line count against ADDR (relocation
name lines dropped); -v SYM prints that symbol's full diff."""
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

args = sys.argv[1:]
verbose = None
if '-v' in args:
    i = args.index('-v')
    verbose = args[i + 1]
    del args[i:i + 2]
copy, as_src = args[0], args[1]
pairs = [a.split(':') for a in args[2:]]
rules = []
for l in open('config/flags.txt'):
    if ':' in l and not l.startswith('#'):
        pat, fl = l.split(':', 1)
        rules.append((pat.strip(), fl.split()))
fl = [f for p, f in rules if fnmatch.fnmatch(as_src, p)][0]
i = next(k for k, f in enumerate(fl) if f.startswith('/I'))
fl = fl[:i] + ['/I' + os.path.abspath(os.path.dirname(as_src))] + fl[i:]
obj = os.path.join(W, 'fdiff.obj')
out = []
if not compile_unit(copy, obj, fl, out=out):
    print('COMPILE ERROR')
    print('\n'.join(l for l in '\n'.join(out).splitlines() if 'error' in l)[:4000])
    sys.exit(1)
for sym, addr in pairs:
    r = subprocess.run([sys.executable, os.path.join(S, 'rwd.py'), obj, sym, addr], capture_output=True, text=True)
    txt = r.stdout + r.stderr
    lines = [l for l in txt.splitlines() if l[:1] in '-+' and not l.startswith(('---', '+++'))]
    minus = [l for l in lines if l[0] == '-']
    plus = [l for l in lines if l[0] == '+']
    mreloc = [l for l in minus if ' ; ' in l or l.rstrip().endswith(';')]
    d = [l for l in minus if l not in mreloc] + plus[len(mreloc):]
    if 'Traceback' in txt:
        print('%-40s NOT EMITTED' % sym)
    else:
        print('%-40s %d' % (sym, len(d)))
    if verbose == sym:
        print(txt)
