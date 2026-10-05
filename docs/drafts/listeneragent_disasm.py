import sys,capstone
sys.path.insert(0,'tools')
from xbe import Xbe
x=Xbe('orig/Game_XboxMultiplayer.xbe')
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
for addr,size in [(0x23CC70,0xd0),(0x23CD40,0x401),(0x23D2A0,0x60),(0x23D320,0x60)]:
    print('\nFUNCTION %06X'%addr)
    for i in md.disasm(bytes(x.read(addr,size)),addr):print('%06X %s %s'%(i.address,i.mnemonic,i.op_str))
