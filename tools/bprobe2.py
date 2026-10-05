"""bprobe2.py SLOTS: bucket probe in batches of 80 names (small enough that
the probe's buckets stay distinct), then pick names per slot (hex, nearest
ebp first) with non-decreasing buckets; declare them farthest slot first.
Prints the rename map (slot=name) for applyb.py."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, sys
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from local_names import name_buckets, FORMS
from build_probes import ROOT, flags_for, load_flags

slots = sys.argv[1].split(',')
flags = flags_for('src/recovered/unit_03FA10.cpp', load_flags())
out = os.path.join(ROOT, 'build', 'fastnames')
os.makedirs(out, exist_ok=True)
extra = ['m_%s', 'p%s', 'r%s', 's%s', 't%s', 'x%s', 'y%s', 'z%s', 'q%s', 'w%s', 'o%s', 'u%s']
forms = FORMS + extra
names = [f % s for s in slots for f in forms]
B = {}
step = 80
for i in range(0, len(names), step):
    part = names[i:i + step]
    b = name_buckets(part, flags, out)
    if b is None or max(b.values()) < 15:
        print('batch', i, 'incomplete', b and max(b.values()), file=sys.stderr)
    print("batch", i, b and max(b.values()), file=sys.stderr)
    B.update(b or {})
prev = -1
pick = []
for s in slots:
    opts = sorted((B[f % s], f % s) for f in forms if f % s in B and B[f % s] >= prev)
    if not opts:
        sys.exit('stuck at %s' % s)
    prev, n = opts[0]
    pick.append(n)
print(' '.join('%s=%s' % (s, n) for s, n in zip(slots, pick)))
print('buckets', [B[n] for n in pick])
