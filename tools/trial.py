"""trial.py SRC ADDR [NAME]: compile SRC (a variant of a unit, placed next to the
real one so includes resolve) with the unit's flags and compare function ADDR."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import os, re, sys, subprocess, shutil
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
from match import compare
from xbe import Xbe
src, addr = sys.argv[1], int(sys.argv[2], 16)
text = open(src, encoding='utf-8').read()
m = re.search(r'^// match: (\S+) @ 0x0*%X$' % addr, text, re.M)
name = m.group(1)
dst = os.path.join(ROOT, 'src', 'recovered', '_trial.cxx')
shutil.copy(src, dst)
obj = os.path.join(ROOT, 'build', '_trial.obj')
ok = compile_unit(dst, obj, flags_for('src/recovered/unit_03FA10.cpp', load_flags()) + ['/I' + os.path.join(ROOT, 'include')])
os.remove(dst)
if not ok: sys.exit(1)
image = Xbe(os.path.join(ROOT, 'orig', 'Game_XboxMultiplayer.xbe'))
r = compare(obj, name, addr, image)
print(r)
if len(sys.argv) > 3:
    import capstone
    from coff import Coff
    c = Coff(obj)
    code, _ = c.function_bytes(c.find_function(name))
    orig = image.read(addr, len(code) + 16)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    A = ['%s %s' % (x.mnemonic, x.op_str) for x in md.disasm(bytes(code), 0)]
    B = ['%s %s' % (x.mnemonic, x.op_str) for x in md.disasm(bytes(orig), 0)][:len(A) + 2]
    import difflib
    if sys.argv[3] == 'n':
        def norm(x):
            x = re.sub(r'\[ebp - 0x[0-9a-f]+\]|\[ebp - \d+\]', '[ebp-X]', x)
            x = re.sub(r'^(call|jmp|j[a-z]+) 0x[0-9a-f]+', r' T', x)
            return re.sub(r'\[0x[0-9a-f]+\]|\[0\]', '[G]', x)
        A = [norm(x) for x in A]; B = [norm(x) for x in B]
    for l in difflib.unified_diff(B, A, 'orig', 'ours', n=2, lineterm=''):
        print(l)
