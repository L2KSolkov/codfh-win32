"""bprobe4.py SLOTS: absolute name buckets (every probe batch padded until all
16 buckets show, so their numbering agrees), then names whose buckets never
fall with the slots (hex, nearest ebp first), preferring the lowest bucket;
declare them farthest slot first (applyb.py)."""
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
filler = ['pad_%d' % i for i in range(64)]
B = {}
step = 60
for i in range(0, len(names), step):
    part = names[i:i + step]
    k = 0
    while True:
        b = name_buckets(part + filler[:k], flags, out)
        if b is not None and max(b.values()) == 15:
            break
        k += 4
        if k > len(filler):
            sys.exit('cannot fill batch %d' % i)
    B.update({n: b[n] for n in part})
# DP: minimal lexicographic path with non-decreasing buckets
best = {-1: []}
for s in slots:
    nb = {}
    for pb, path in sorted(best.items()):
        for f in forms:
            n = f % s
            if B[n] >= pb and B[n] not in nb:
                nb[B[n]] = path + [n]
    best = nb
    if not best:
        sys.exit('stuck at %s' % s)
path = best[min(best)]
print(' '.join('%s=%s' % (s, n) for s, n in zip(slots, path)))
print('buckets', [B[n] for n in path])
