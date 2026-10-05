"""asmtest.py FILE: compile FILE (project flags, scratch inc first) with /FA and
print each function's listing, trimmed to the instructions."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, re, sys
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

src = sys.argv[1]
out = os.path.join(ROOT, 'build', 'local_names')
os.makedirs(out, exist_ok=True)
obj = os.path.join(out, 'asmtest.obj')
asm = os.path.join(out, 'asmtest.asm')
dst = os.path.join(ROOT, 'build', '_asmtest.cxx')
open(dst, 'w', encoding='utf-8').write(open(src, encoding='utf-8').read())
flags = ['/I' + os.path.join(W, 'inc')] + flags_for('src/recovered/unit_03FA10.cpp', load_flags()) + \
        ['/I' + os.path.join(ROOT, 'include'), '/FA', '/Fa' + asm]
compile_unit(dst, obj, flags)
cur = None
for l in open(asm, errors='replace'):
    m = re.match(r'^(\S+)\s+PROC', l)
    if m:
        cur = m.group(1)
        print('====', cur)
        continue
    if re.match(r'^\S+\s+ENDP', l):
        cur = None
        continue
    if cur and l.startswith('\t') and not l.strip().startswith(';'):
        print('   ', l.strip())
