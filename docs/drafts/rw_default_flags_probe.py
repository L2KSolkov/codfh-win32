"""Parked default-instancer experiments; no exact candidate.
Target __rpXboxDefaultInstance 0x2DED60 in xbvtxfmt.c. See questions.md.
"""
from pathlib import Path
import sys,difflib
sys.path[:0]=['tools','tools/session']
from build_probes import compile_unit,flags_for,load_flags
from coff import Coff
from xbe import Xbe
from pscore import MD,norm
from match import compare
ns={};exec(Path('docs/drafts/rw_default_instance_trials.py').read_text(),ns)
src='src/rw/world/pipe/p2/xbox/xbvtxfmt.c';s=Path(src).read_text().replace(ns['anchor'],ns['body']+ns['anchor'],1)
p='build/tooltmp/default_flags_probe.c';Path(p).write_text(s)
f=flags_for(src,load_flags())+['/Isrc/rw/world/pipe/p2/xbox','/Iinclude'];x=Xbe('orig/Game_XboxMultiplayer.xbe')
for k,opt in enumerate([[],['/Oa'],['/Ow'],['/Oa','/Ow'],['/Os'],['/G5'],['/G7'],['/Ob1'],['/Og-'],['/Oi-'],['/TP']]):
 obj='build/tooltmp/default_flags_%d.obj'%k;out=[]
 if not compile_unit(p,obj,f+opt,out):print(opt,'compile error',str(out)[:120]);continue
 c=Coff(obj);code,_=c.function_bytes(c.find_function('__rpXboxDefaultInstance'))
 a=[norm(i) for i in MD.disasm(bytes(x.read(0x2DED60,len(code))),0x2DED60)];b=[norm(i) for i in MD.disasm(bytes(code),0)]
 diff=sum(i2-i1+j2-j1 for tag,i1,i2,j1,j2 in difflib.SequenceMatcher(None,a,b,autojunk=False).get_opcodes() if tag!='equal')
 print(opt,diff,compare(obj,'__rpXboxDefaultInstance',0x2DED60,x,{})[1].splitlines()[0])
