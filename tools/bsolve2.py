"""bsolve.py SOURCE ADDR SLOTS: pick names whose buckets rise with SLOTS (hex,
nearest ebp first), greedily, and print a rename map."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import sys, os
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from local_names import FORMS, name_buckets
from build_probes import ROOT, flags_for, load_flags
src, addr, slots = sys.argv[1], sys.argv[2], sys.argv[3].split(',')
rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
flags = flags_for(rel, load_flags())
out = os.path.join(ROOT, 'build', 'local_names')
os.makedirs(out, exist_ok=True)
extra = ['m_%s', 'p%s', 'r%s', 's%s', 't%s', 'x%s', 'y%s', 'z%s', 'q%s', 'w%s', 'o%s', 'u%s']
forms = FORMS + extra
cands = [f % s for s in slots for f in forms]
b = name_buckets(cands, flags, out)
prev = -1
STRICT = set(sys.argv[4].split(",")) if len(sys.argv) > 4 else set()
pick = []
for s in slots:
    opts = sorted((b[f % s], f % s) for f in forms if b[f % s] >= prev + (1 if s in STRICT else 0))
    if not opts:
        print('stuck at', s); sys.exit(1)
    prev, n = opts[0]
    pick.append(n)
print(' '.join('%s=%s' % (s, n) for s, n in zip(slots, pick)))
print('buckets', [b[n] for n in pick])
