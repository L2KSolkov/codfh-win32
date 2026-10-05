"""bsolve_decl.py SOURCE SLOTS DECL: names for slots (hex, nearest ebp first)
whose buckets order them, given each slot's declaration index DECL (comma
list, same order; a later declaration sits nearer ebp within a bucket).
Consecutive slots may share a bucket only when the nearer one is declared
later than every farther one sharing it."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, sys
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from local_names import FORMS, name_buckets
from build_probes import ROOT, flags_for, load_flags
src, slots, decl = sys.argv[1], sys.argv[2].split(','), [int(x) for x in sys.argv[3].split(',')]
rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
flags = flags_for(rel, load_flags())
out = os.path.join(ROOT, 'build', 'local_names')
os.makedirs(out, exist_ok=True)
extra = ['m_%s', 'p%s', 'r%s', 's%s', 't%s', 'x%s', 'y%s', 'z%s', 'q%s', 'w%s', 'o%s', 'u%s']
forms = FORMS + extra
cands = [f % s for s in slots for f in forms]
b = name_buckets(cands, flags, out)
prev = -1
group_min_decl = None
pick = []
for s, d in zip(slots, decl):
    same_ok = group_min_decl is not None and d < group_min_decl
    opts = sorted((b[f % s], f % s) for f in forms if b[f % s] > prev or (b[f % s] == prev and same_ok))
    if not opts:
        print('stuck at', s); sys.exit(1)
    bk, n = opts[0]
    if bk == prev:
        group_min_decl = d
    else:
        group_min_decl = d
    prev = bk
    pick.append(n)
print(' '.join('%s=%s' % (s, n) for s, n in zip(slots, pick)))
print('buckets', [b[n] for n in pick])
