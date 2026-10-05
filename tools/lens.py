import os as _os_repo
_REPO = _os_repo.path.dirname(_os_repo.path.dirname(_os_repo.path.abspath(__file__)))  # the repository root, from this file's location
import sys, os, capstone
sys.path.insert(0, _os_repo.path.join(_REPO, 'tools'))
from coff import Coff
S = os.path.dirname(os.path.abspath(__file__))
W = os.path.join(os.path.dirname(S), 'build', 'tooltmp')  # work files
os.makedirs(W, exist_ok=True)

c = Coff(_os_repo.path.join(_REPO, r'build\local_names\probe.obj'))
code, _ = c.function_bytes(c.find_function(sys.argv[1]))
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
ours=[(i.address,i.size,i.mnemonic) for i in md.disasm(bytes(code),0)]
base=int(sys.argv[2],16)
img=[]
for l in open(S+r'\x21e0.txt'):
    p=l.split()
    if len(p)>=2 and p[1]!='int3': img.append((int(p[0],16)-base,p[1]))
for k,(a,b) in enumerate(zip(ours,img)):
    if a[0]!=b[0]:
        print('first offset divergence at insn',k,'ours',hex(a[0]),a[2],'image',hex(b[0]),b[1]); 
        print('prev ours',ours[k-1],'image',img[k-1]); break
