import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import sys; sys.path.insert(0, _os_repo.path.join(_REPO, r'tools'))
from xbe import Xbe
import capstone, re
sym={}
for l in open(_os_repo.path.join(_REPO, r'config\symbols.txt')):
    if l.startswith('0x'):
        p=l.split(); sym[int(p[0],16)]=p[-1]
x=Xbe(_os_repo.path.join(_REPO, r'orig\Game_XboxMultiplayer.xbe'))
a,b=int(sys.argv[1],16),int(sys.argv[2],16)
md=capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
for i in md.disasm(x.read(a,b-a),a):
    s='%s %s'%(i.mnemonic,i.op_str)
    s=re.sub(r'0x([0-9a-f]{5,6})\b', lambda m: sym.get(int(m.group(1),16), m.group(0)) if int(m.group(1),16) in sym else m.group(0), s)
    print('%x  %s'%(i.address,s))
