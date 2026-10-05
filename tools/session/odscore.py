"""odscore.py SYM ADDR [glob]: rank ptry variant objects by odiff changed-line count."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import glob
import os
import subprocess
import sys

sym, addr = sys.argv[1], sys.argv[2]
pat = sys.argv[3] if len(sys.argv) > 3 else 'p_*.obj'
here = os.path.dirname(os.path.abspath(__file__))
res = []
for f in glob.glob(os.path.join(_os_repo.path.join(_REPO, r'build\tooltmp\ptry'), pat)):
    out = subprocess.run([sys.executable, os.path.join(here, 'odiff.py'), f, sym, addr],
                         capture_output=True, text=True).stdout
    n = sum(1 for l in out.split('\n') if l.startswith(' -') or l.startswith(' +'))
    res.append((n, os.path.basename(f)))
for n, f in sorted(res)[:8]:
    print(n, f)
