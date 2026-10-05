"""pnames.py SRC ADDR OLD1,OLD2,... SLOT1,SLOT2,...: try name forms for each
listed local (all combinations), compiling in parallel copies; print the
combinations whose frame slots match (first differing offset moves past
FIRSTOFF) and stop at the first full match."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import itertools, os, re, shutil, subprocess, sys
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
from match import compare
from xbe import Xbe
from local_names import FORMS
src, addr = sys.argv[1], int(sys.argv[2], 16)
olds = sys.argv[3].split(','); slots = sys.argv[4].split(',')
text = open(src, encoding='utf-8').read()
m = re.search(r'^// match: (\S+) @ 0x0*%X$' % addr, text, re.M)
name = m.group(1)
flags = ['/I' + os.path.join(os.path.dirname(os.path.abspath(__file__)), 'inc')] + flags_for('src/recovered/unit_03FA10.cpp', load_flags()) + ['/I' + os.path.join(ROOT, 'include')]
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
out = os.path.join(ROOT, 'build', 'pnames'); os.makedirs(out, exist_ok=True)
combos = list(itertools.product(*[[f % s for f in FORMS] for s in slots]))
def run(k):
    combo = combos[k]
    t = text
    for o, n in zip(olds, combo):
        t = re.sub(r'\b%s\b' % re.escape(o), n, t)
    cx = os.path.join(out, 'p%d.cxx' % k); ob = os.path.join(out, 'p%d.obj' % k)
    open(cx, 'w', encoding='utf-8').write(t)
    if not compile_unit(cx, ob, flags, out=[]):
        return combo, None
    r = compare(ob, name, addr, image)
    for f in (cx, ob, os.path.splitext(ob)[0] + '.pdb'):
        try: os.remove(f)
        except OSError: pass
    return combo, r
best = 0
with ThreadPoolExecutor(10) as ex:
    for combo, r in ex.map(run, range(len(combos))):
        if r is None: continue
        ok, msg = r
        if ok:
            print('MATCH', combo); break
        mm = re.search(r'differs at \+0x([0-9A-F]+)', msg)
        off = int(mm.group(1), 16) if mm else 0
        if off > best:
            best = off; print('best', hex(off), combo)
