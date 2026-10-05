import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import sys,re
sys.path.insert(0,_os_repo.path.join(_REPO, r'tools'))
from coff import Coff
import capstone
obj,addr=sys.argv[1],int(sys.argv[2],16)
c=Coff(obj)
raw=open(obj,'rb').read().decode('latin-1')
n=sys.argv[3] if len(sys.argv)>3 else re.search(r"\?sub_%X@[\x21-\x7e]*"%addr,raw).group(0)
b,_=c.function_bytes(c.find_function(n))
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
for x in md.disasm(b,0): print('%4x  %s %s'%(x.address,x.mnemonic,x.op_str))
