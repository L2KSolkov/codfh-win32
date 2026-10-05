"""rwrank.py: rank the tracked src/rw near misses (rwmissed.py --near) by the
number of real diff lines rwd.py reports (relocation-only lines dropped)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os
import subprocess
import sys

S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

ROOT = _REPO
os.chdir(ROOT)
tracked = set(l.strip()[:-2] for l in subprocess.run(['git', 'ls-files', 'src/rw'], capture_output=True,
                                                         text=True).stdout.splitlines() if l.endswith('.c'))
out = subprocess.run([sys.executable, os.path.join(S, 'rwmissed.py'), '--near'], capture_output=True, text=True).stdout
res = []
for l in out.splitlines():
    p = l.split()
    if p[0] == 'NEAR':
        src, sym, addr = p[1], p[2], p[3]
    else:
        continue
    if src not in tracked:
        continue
    r = subprocess.run([sys.executable, os.path.join(S, 'rwd.py'), 'build/%s.obj' % src, sym, addr],
                       capture_output=True, text=True).stdout
    d = [x for x in r.splitlines() if x[:1] in '-+' and not x.startswith(('---', '+++'))
         and 'call   ;' not in x and '[0]' not in x and 'push 0  ;' not in x and '0x3' not in x.split(';')[0][-10:]]
    res.append((len(d), src, sym, addr, l.split('first diff')[1].strip() if 'first diff' in l else ''))
for n, src, sym, addr, info in sorted(res):
    print('%4d %-40s %-40s %s %s' % (n, src, sym, addr, info))
