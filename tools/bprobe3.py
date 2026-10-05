"""bprobe3.py SLOTS: like bprobe2, but each probe holds only two forms per
slot (one consistent bucket numbering), trying form pairs until the names'
buckets rise with the slots (hex, nearest ebp first)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import itertools, os, sys
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from local_names import name_buckets, FORMS
from build_probes import ROOT, flags_for, load_flags

slots = sys.argv[1].split(',')
flags = flags_for('src/recovered/unit_03FA10.cpp', load_flags())
out = os.path.join(ROOT, 'build', 'fastnames')
os.makedirs(out, exist_ok=True)
extra = ['m_%s', 'p%s', 'r%s', 's%s', 't%s', 'x%s', 'y%s', 'z%s', 'q%s', 'w%s', 'o%s', 'u%s']
forms = FORMS + extra
per = max(1, 78 // len(slots))
for combo in itertools.combinations(forms, per):
    names = [f % s for s in slots for f in combo]
    b = name_buckets(names, flags, out)
    if b is None:
        continue
    prev = -1
    pick = []
    for s in slots:
        opts = sorted((b[f % s], f % s) for f in combo if b[f % s] >= prev)
        if not opts:
            break
        prev, n = opts[0]
        pick.append(n)
    else:
        print(' '.join('%s=%s' % (s, n) for s, n in zip(slots, pick)))
        print('buckets', [b[n] for n in pick])
        sys.exit(0)
print('none')
