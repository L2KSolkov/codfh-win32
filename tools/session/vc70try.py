import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import sys, subprocess
sys.path.insert(0, 'tools')
from build_probes import compile_unit, flags_for, load_flags
src, sym, addr = sys.argv[1], sys.argv[2], sys.argv[3]
fl = flags_for(src, load_flags())
for name, f in [('vc71', fl), ('vc70', ['/compiler:vc70'] + [x for x in fl if x != '/arch:SSE']), ('vc70sse', ['/compiler:vc70'] + fl)]:
    o = []
    ok = compile_unit(src, 'build/tooltmp/libtest/vt.obj', f, o)
    if not ok:
        print(name, 'compile error', o[:1]); continue
    r = subprocess.run([sys.executable, _os_repo.path.join(_REPO, 'tools/match.py'), 'build/tooltmp/libtest/vt.obj', sym, addr], capture_output=True, text=True)
    print(name, (r.stdout + r.stderr).strip()[:150])
