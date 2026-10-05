"""objdis.py OBJ SYM [FROM TO]: disassemble SYM from an object (hex offsets)."""
import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import sys

import capstone

sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from coff import Coff  # noqa: E402

c = Coff(sys.argv[1])
s = [v for v in c.symbols.values() if v['name'] == sys.argv[2] and v.get('section', 0) > 0][0]
code, rels = c.function_bytes(s)
lo = int(sys.argv[3], 16) if len(sys.argv) > 3 else 0
hi = int(sys.argv[4], 16) if len(sys.argv) > 4 else len(code)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
for i in md.disasm(bytes(code), 0):
    if lo <= i.address < hi:
        print('%4x  %s %s' % (i.address, i.mnemonic, i.op_str))
