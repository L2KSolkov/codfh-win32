"""vva.py UNIT BLK ADDR VARIANTS.py: for each (name, [(old, new), ...]) in
VARIANTS.py's `variants` dict, apply the replacements to BLK, insert it into
UNIT (into _ln.cxx) and print diffall's last line."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, subprocess, sys
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

R = _REPO
src = R + r'\src\recovered\_ln.cxx'
unit, blk, addr, vfile = sys.argv[1:5]
base = open(blk, encoding='utf-8').read()
ns = {}
exec(open(vfile, encoding='utf-8').read(), ns)
for n, reps in ns['variants'].items():
    b = base
    ok = True
    for o, nw in reps:
        if o not in b:
            print(n, '| missing', repr(o[:60]), flush=True)
            ok = False
            break
        b = b.replace(o, nw, 1)
    if not ok:
        continue
    t = os.path.join(W, '_vva_t.cpp')
    open(t, 'w', encoding='utf-8').write(b)
    subprocess.run([sys.executable, S + r'\insfn.py', unit, t, src], capture_output=True, stdin=subprocess.DEVNULL)
    r = subprocess.run([sys.executable, S + os.sep + os.environ.get('VTOOL', 'diffall.py'), src, addr, '0' if os.environ.get('VTOOL') else '400'], capture_output=True, text=True,
                       stdin=subprocess.DEVNULL)
    out = (r.stdout + r.stderr).strip().split('\n')
    print(n, '|', out[-1], [l for l in out if 'sub esp' in l][:1], flush=True)
