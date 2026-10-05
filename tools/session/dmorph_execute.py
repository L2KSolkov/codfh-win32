"""Original-vs-draft DMorph execution with deterministic graphics/allocation stubs.
The math, RLE traversal, block merge, and vertex conversion execute as x86.
This checks behavior for fixtures, not byte identity or real GPU integration.
Run from the repository root after dmorph_execution_build.py. Arguments:
optional object path, optional positive random-case count (default 100).
Fixtures use FLOAT vertex formats and finite weights; fresh cases always run.
"""
import sys,struct,random,json
from pathlib import Path
sys.path[:0]=['tools','build/tooltmp/emulation_deps']
from unicorn import Uc,UC_ARCH_X86,UC_MODE_32,UC_HOOK_CODE
from unicorn.x86_const import *
from coff import Coff
from xbe import Xbe
from match import resolve_name
BASE=0x2f28d0
image=Xbe('orig/Game_XboxMultiplayer.xbe')
obj=Coff(sys.argv[1] if len(sys.argv)>1 else 'build/tooltmp/dmorph_trace_baseline.obj')
symbol=obj.find_function('_XboxDmorphAtomicInstanceCallback')
code,relocs=obj.function_bytes(symbol)
compiled=bytearray(code)
for off,name,kind in relocs:
 local=next((s for s in obj.symbol_list if s['name']==name and s['section']==symbol['section']),None)
 target=BASE+local['value']-symbol['value'] if local else resolve_name(name,{})
 assert target is not None,name
 value=target+struct.unpack_from('<i',compiled,off)[0]
 if kind==0x14:value-=BASE+off+4
 else:assert kind==6
 struct.pack_into('<I',compiled,off,value&0xffffffff)
ATOMIC=0x1000000;GEOM=0x1001000;DATA=0x1002000;TARGETS=0x1003000
CURRENT=0x1004000;VALUES=0x1005000;FMT=0x1006000;HEADER=0x1007000
MORPH=0x1008000;POS=0x1009000;NORM=0x100a000;COLOR=0x100b000;TEX=0x100c000
VB=0x1010000;SVB=0x1011000;OUT=0x1020000;SOUT=0x1030000;BLOCKS=0x1040000
STOP=0x1090000;ALLOC=0x1090010;FREE=0x1090020
def run(case,candidate):
 u=Uc(UC_ARCH_X86,UC_MODE_32)
 u.mem_map(0x10000,0x900000)
 u.mem_map(0x1000000,0x100000)
 u.mem_map(0x2000000,0x20000)
 for section in image.sections:
  u.mem_write(section['va'],image.read(section['va'],section['rsize']))
 if candidate:u.mem_write(BASE,bytes(compiled))
 put=lambda addr,val:u.mem_write(addr,struct.pack('<I',val&0xffffffff))
 get=lambda addr:struct.unpack('<I',u.mem_read(addr,4))[0]
 real=lambda addr,val:u.mem_write(addr,struct.pack('<f',val))
 put(0x50f3f8,0x80);put(0x50f3fc,0x100)
 put(0x520214,ALLOC);put(0x520218,FREE)
 put(ATOMIC+0x18,GEOM);put(ATOMIC+0x80,VALUES);put(GEOM+0x100,DATA)
 put(GEOM+8,0x1e);put(GEOM+0xc,case['locked']);put(GEOM+0x1c,1)
 put(GEOM+0x30,COLOR);put(GEOM+0x34,TEX);put(GEOM+0x5c,MORPH)
 put(MORPH+0x14,POS);put(MORPH+0x18,NORM)
 put(FMT,0x01000555)
 put(DATA,len(case['targets']));put(DATA+4,TARGETS);put(DATA+8,CURRENT)
 dynamic=0
 for t in case['targets']:dynamic|=t['flags']
 static=0x1e&~dynamic
 stride=lambda flags:sum(size for bit,size in [(2,12),(16,12),(8,4),(4,8)] if flags&bit)
 put(DATA+0xc,SVB);put(DATA+0x10,stride(static));put(DATA+0x14,static)
 n=case['vertices'];put(HEADER+0xc,n);put(HEADER+0x10,stride(dynamic));put(HEADER+0x14,0 if case.get('fresh') else VB)
 put(VB+8,0);put(SVB+8,0)
 for j in range(n):
  for axis in range(3):
   real(POS+j*12+axis*4,(j+axis)*.125)
   real(NORM+j*12+axis*4,(j-axis)*.0625)
  u.mem_write(COLOR+j*4,bytes([100,110,120,200]))
  real(TEX+j*8,j*.125);real(TEX+j*8+4,j*.25)
 for i,t in enumerate(case['targets']):
  entry=TARGETS+i*0x40;packet=0x1050000+i*0x1000;dpos=packet+0x100;dnorm=packet+0x300;dcolor=packet+0x500;dtex=packet+0x700
  put(entry+8,t['flags']);put(entry+0x10,packet);put(entry+0x14,len(t['code']))
  put(entry+0x20,dpos);put(entry+0x24,dnorm);put(entry+0x28,dcolor);put(entry+0x2c,dtex)
  u.mem_write(packet,bytes(t['code']))
  real(CURRENT+i*4,t['old']);real(VALUES+i*4,t['new'])
  for j in range(n):
   for axis in range(3):
    real(dpos+j*12+axis*4,(i+j+axis+1)*.0625)
    real(dnorm+j*12+axis*4,(i-j+axis)*.03125)
   u.mem_write(dcolor+j*4,bytes([1,2,3,4]))
   real(dtex+j*8,(i+j)*.125);real(dtex+j*8+4,(i-j)*.25)
 sp=0x2010000
 for k,v in enumerate([STOP,ATOMIC,HEADER,case['reinstance']]):put(sp+k*4,v)
 u.reg_write(UC_X86_REG_ESP,sp)
 u.reg_write(UC_X86_REG_CR4,u.reg_read(UC_X86_REG_CR4)|0x600)
 events=[]
 def ret(value,cleanup=0):
  esp=u.reg_read(UC_X86_REG_ESP);target=get(esp)
  u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_ESP,esp+4+cleanup);u.reg_write(UC_X86_REG_EIP,target)
 fmtaddr=resolve_name('_RpXboxGeometryGetVtxFmt',{})
 lockaddr=resolve_name('_D3DVertexBuffer_Lock2@8',{})
 shaderaddr=resolve_name('_D3DDevice_CreateVertexShader@16',{})
 createaddr=resolve_name('_RwXbCreateVertexBuffer',{})
 releaseaddr=resolve_name('_RwXbReleaseVertexBuffer',{})
 created=[]
 def hook(uc,address,size,unused):
  esp=u.reg_read(UC_X86_REG_ESP)
  if address==STOP:uc.emu_stop()
  elif address==fmtaddr:events.append(('format',get(esp+4)));ret(FMT)
  elif address==lockaddr:
   vb=get(esp+4);assert vb in (VB,SVB),hex(vb)
   events.append(('lock',vb));ret(OUT if vb==VB else SOUT,8)
  elif address==ALLOC:events.append(('alloc',get(esp+4)));ret(BLOCKS)
  elif address==FREE:events.append(('free',get(esp+4)));ret(0)
  elif address==shaderaddr:
   declaration=[];ptr=get(esp+4)
   for i in range(256):
    value=get(ptr+i*4);declaration.append(value)
    if value==0xffffffff:break
   assert declaration[-1]==0xffffffff
   events.append(('shader',declaration));put(get(esp+12),0x777);ret(0,16)
  elif address==createaddr:
   target=VB if not created else SVB;created.append(target)
   events.append(('create',get(esp+4)));ret(target)
  elif address==releaseaddr:events.append(('release',get(esp+4)));ret(0)
 u.hook_add(UC_HOOK_CODE,hook)
 try:u.emu_start(BASE,STOP+1,count=1000000)
 except Exception as e:raise RuntimeError((candidate,hex(u.reg_read(UC_X86_REG_EIP)),str(e))) from e
 assert u.reg_read(UC_X86_REG_EIP)==STOP,'execution limit'
 result={'return':u.reg_read(UC_X86_REG_EAX),'events':events}
 for name,addr,size in [('positions',POS,n*12),('normals',NORM,n*12),('color',COLOR,n*4),('texcoords',TEX,n*8),('weights',CURRENT,len(case['targets'])*4),('buffer',OUT,n*36),('static_buffer',SOUT,n*36),('header',HEADER,0x24)]:
  result[name]=bytes(u.mem_read(addr,size)).hex()
 return result
def main():
 rng=random.Random(0x2f28d0)
 count=int(sys.argv[2]) if len(sys.argv)>2 else 100
 if count<1:raise SystemExit('random-case count must be positive')
 for i in range(count):
  n=rng.randrange(1,25);targets=[]
  for j in range(rng.randrange(1,5)):
   packets=[];remaining=n
   while remaining:
    count=rng.randrange(1,remaining+1);remaining-=count;packets.append(count|rng.choice([0,128]))
   targets.append(dict(flags=rng.choice([2,4,8,16,0x1e]),old=rng.choice([0,.5,1]),new=rng.choice([0,.5,1]),code=packets))
  case=dict(vertices=n,targets=targets,locked=rng.choice([0,2,4,8,16,0xfff]),reinstance=rng.randrange(2))
  a=run(case,False);b=run(case,True)
  if a!=b:
   Path('build/tooltmp/dmorph_callback_failure.json').write_text(json.dumps(dict(case=case,original=a,compiled=b),indent=2))
   raise AssertionError((i,[k for k in a if a[k]!=b[k]]))
  if (i+1)%25==0:print(f'Checked {i+1}/{count} existing-buffer cases',flush=True)
 print(f'PASS: {i+1} complete callback executions with existing vertex buffers; positions, normals, colors, texture coordinates, updated weights, buffer bytes, vertex alpha, and external stub events agree.')
 print('Excluded from random cases: new-buffer creation (checked separately), pending fences, allocation failures, real GPU behavior. Byte matching remains required.')
def check_fresh():
 for flags in [2,4,8,16,0x1e]:
  for reinstance in [0,1]:
   case=dict(vertices=8,targets=[dict(flags=flags,old=0,new=.5,code=[0x83,2,0x83])],locked=0,reinstance=reinstance,fresh=True)
   a=run(case,False);b=run(case,True)
   assert a==b,(flags,reinstance,[k for k in a if a[k]!=b[k]])
 print('PASS: 10 fresh-buffer cases, including shader declarations and static/dynamic splits.')

if __name__=='__main__':
 main()
 check_fresh()
