"""flagtry.py SRC SYM ADDR 'FLAGS' ['FLAGS' ...]: compile SRC with each
complete flag set (space-separated, /compiler: pseudo-flag allowed) and
print SYM's ncmp score against ADDR for each, to test whether a unit was
built with other options."""
import os
import subprocess
import sys

S = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(S)
sys.path.insert(0, S)
from build_probes import compile_unit  # noqa: E402

src, sym, addr = sys.argv[1:4]
for i, fl in enumerate(sys.argv[4:]):
    obj = os.path.join(ROOT, 'build', 'tooltmp', 'flagtry%d.obj' % i)
    out = []
    if not compile_unit(src, obj, fl.split(), out):
        print('ERR', fl)
        continue
    r = subprocess.run([sys.executable, os.path.join(S, 'ncmp.py'), obj, sym, addr],
                       capture_output=True, text=True).stdout.split('\n')[0].strip()
    print(r, fl)
