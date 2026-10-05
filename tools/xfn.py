"""xfn.py ADDR...: disassemble whole functions by their symbols.txt sizes."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import subprocess, sys, os
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

sz = {}
for l in open(_os_repo.path.join(_REPO, r'config\symbols.txt')):
    p = l.split()
    if len(p) >= 5 and p[1] == 'function' and p[0].startswith('0x'):
        sz[int(p[0], 16)] = (int(p[2], 16), p[-1])
for a in sys.argv[1:]:
    a = int(a, 16)
    n, name = sz[a]
    print('=== %s %X' % (name, a))
    sys.stdout.write(subprocess.run([sys.executable, os.path.join(S, 'xdis.py'), '%X' % a, '%X' % (a + n)],
                                    capture_output=True, text=True).stdout)
