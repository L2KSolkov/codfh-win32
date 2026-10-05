"""odiff.py OBJ SYM ADDR: aligned diff of an object's function against the image (operands normalized)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import sys, re, difflib, capstone
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff
from xbe import Xbe
c = Coff(sys.argv[1]); code, _ = c.function_bytes(c.find_function(sys.argv[2]))
addr = int(sys.argv[3], 16)
x = Xbe(_os_repo.path.join(_REPO, r'orig\Game_XboxMultiplayer.xbe'))
orig = x.read(addr, len(code) + 64)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def norm(i):
    s = '%s %s' % (i.mnemonic, i.op_str)
    s = re.sub(r'^(call|jmp|j\w+) .*', r'\1 X', s)
    s = re.sub(r'0x[0-9a-f]{5,}', 'A', s)
    s = re.sub(r'dword ptr \[0\]', 'dword ptr [A]', s)
    s = re.sub(r'(push|, ) ?0$', r'\1 A', s)
    return s


u = [(i.address, norm(i)) for i in md.disasm(bytes(code), 0)]
o = []
for i in md.disasm(bytes(orig), addr):
    if i.address >= addr + len(code) + 16:
        break
    o.append((i.address, norm(i)))
sm = difflib.SequenceMatcher(None, [a[1] for a in o], [a[1] for a in u], autojunk=False)
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal':
        continue
    print('== %s' % tag)
    for k in range(i1, i2):
        print(' - %06x %s' % o[k])
    for k in range(j1, j2):
        print(' + %4x %s' % u[k])
