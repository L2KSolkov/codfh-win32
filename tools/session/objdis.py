import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__))))  # the repository root, from this file's location
import sys, capstone
sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff
c = Coff(sys.argv[1]); code, rels = c.function_bytes(c.find_function(sys.argv[2]))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
for i in md.disasm(bytes(code), 0): print('%4x  %s %s' % (i.address, i.mnemonic, i.op_str))
