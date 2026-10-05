"""ranks.py SOURCE REF SLOT...: bucket ranks of every name form for each SLOT,
beside REF (a given name), from one probe; prints the forms at or above REF's
bucket, lowest bucket first."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import sys, os, string
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from local_names import FORMS, name_buckets
from build_probes import ROOT, flags_for, load_flags
src, ref, slots = sys.argv[1], sys.argv[2], sys.argv[3:]
rel = os.path.relpath(src, ROOT).replace(os.sep, '/')
flags = flags_for(rel, load_flags())
out = os.path.join(ROOT, 'build', 'local_names')
os.makedirs(out, exist_ok=True)
extra = ['m_%s', 'p%s', 'r%s', 's%s', 't%s', 'x%s', 'y%s', 'z%s', 'q%s', 'w%s', 'o%s', 'u%s']
forms = FORMS + extra + [c + '%s' for c in string.ascii_lowercase if c + '%s' not in FORMS + extra]
cands = [ref] + sorted(set(f % s for s in slots for f in forms))
b = name_buckets(cands, flags, out)
print(ref, b[ref])
for s in slots:
    ok = sorted((b[f % s], f % s) for f in forms if b[f % s] >= b[ref])
    print(s, ok[:12])
