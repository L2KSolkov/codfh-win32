"""ourdis.py SOURCE ADDR: disassemble our compiled function."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import sys, os, shutil, re, capstone
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from build_probes import ROOT, compile_unit, flags_for, load_flags
from coff import Coff
src, addr = sys.argv[1], int(sys.argv[2], 16)
text = open(src, encoding='utf-8').read()
name = re.search(r'^// match: (\S+) @ 0x0*%X$' % addr, text, re.M).group(1)
dst = os.path.join(ROOT, 'src', 'recovered', '_trial.cxx'); shutil.copy(src, dst)
obj = os.path.join(ROOT, 'build', '_trial.obj')
compile_unit(dst, obj, flags_for('src/recovered/unit_03FA10.cpp', load_flags()) + ['/I' + os.path.join(ROOT, 'include')])
os.remove(dst)
c = Coff(obj); code, _ = c.function_bytes(c.find_function(name))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
for i in md.disasm(bytes(code), 0): print('%4x  %s %s' % (i.address, i.mnemonic, i.op_str))
