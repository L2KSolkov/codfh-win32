"""vtry.py VARS.py SYM ADDR [SRC]: VARS.py defines VS = {name: [(old, new), ...]};
apply each to SRC (default xbpipe.c) in a copy, compile with fdiff, print ncmp/rawcmp counts."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, subprocess, sys
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

varf, sym, addr = sys.argv[1:4]
src = sys.argv[4] if len(sys.argv) > 4 else 'src/rw/world/pipe/p2/xbox/xbpipe.c'
C = os.path.join(_REPO, src)
enc = 'utf-8'
try:
    t = open(C, encoding=enc).read()
except UnicodeDecodeError:
    enc = 'latin-1'
    t = open(C, encoding=enc).read()
g = {}
exec(open(varf, encoding='utf-8').read(), g)
for name, reps in g['VS'].items():
    tt = t
    ok = True
    for o, n in reps:
        if o not in tt:
            print(name, 'MISSING', repr(o[:60]))
            ok = False
            break
        tt = tt.replace(o, n, 1)
    if not ok:
        continue
    p = os.path.join(W, 'vtry_%s%s' % (name, os.path.splitext(src)[1]))
    open(p, 'w', encoding=enc).write(tt)
    r = subprocess.run([sys.executable, os.path.join(S, 'fdiff.py'), p, src, '%s:%s' % (sym, addr)],
                       capture_output=True, text=True, cwd=_REPO)
    if 'COMPILE ERROR' in r.stdout:
        print(name, 'COMPILE ERROR', r.stdout[-300:])
        continue
    obj = os.path.join(W, 'fdiff.obj')
    n1 = subprocess.run([sys.executable, os.path.join(S, 'ncmp.py'), obj, sym, addr], capture_output=True, text=True).stdout.strip().splitlines()[-1]
    n2 = subprocess.run([sys.executable, os.path.join(S, 'rawcmp.py'), obj, sym, addr], capture_output=True, text=True).stdout.strip().splitlines()[-1]
    print(name, n1, '|', n2)
