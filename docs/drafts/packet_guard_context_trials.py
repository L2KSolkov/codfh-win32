from pathlib import Path
import sys
sys.path.insert(0,'tools')
from build_probes import compile_unit,flags_for,load_flags,MATCH_RE,aliases_in
from match import compare
from xbe import Xbe
from coff import Coff
src=Path('src/recovered/unit_1D0100.cpp').read_text()
decl='template RwInt32 type_1FA230_list<type_3E4E58>::sub_1D3F80(const type_3E4E58 &arg_0);\n'
header=Path('include/rws/clinearmemorymanager.h').read_text()
old='''      static CLinearMemoryManager * Instance()
      {
         static CLinearMemoryManager tCLinearMemoryManager;

         return &tCLinearMemoryManager;
      }'''
assert old in header
root=Path('build/tooltmp/packet_guard_context');root.mkdir(exist_ok=True)
cases={
 'first_member':('#include "game/netqueue.h"\n'+decl+'\n'+src,None),
 'first_class':('#include "game/netqueue.h"\ntemplate class type_1FA230_list<type_3E4E58>;\n'+src,None),
 'header_only':(src,header.replace(old,'      static CLinearMemoryManager * Instance();')),
}
x=Xbe('orig/Game_XboxMultiplayer.xbe')
for n,(s,h) in cases.items():
 d=root/n;d.mkdir(exist_ok=True)
 if h:
  (d/'rws').mkdir(exist_ok=True);(d/'rws/clinearmemorymanager.h').write_text(h)
 p=d/'trial.cpp';p.write_text(s);o=d/'trial.obj';msgs=[]
 flags=['/I'+str(d),'/Iinclude','/FAsc','/Fa'+str(d/'trial.asm')]+flags_for('src/recovered/unit_1D0100.cpp',load_flags())
 if not compile_unit(str(p),str(o),flags,msgs):print(n,msgs);continue
 c=Coff(str(o));print(n,compare(c,'??0type_3E4E58@@QAE@ABU0@@Z',0x1D4290,x,{})[1].splitlines()[0])
 fails=[]
 for sym,a in MATCH_RE.findall(src):
  ok,msg=compare(c,sym,int(a,16),x,aliases_in(src))
  if not ok:fails.append(msg.splitlines()[0])
 print('existing failures',len(fails),*fails,sep='\n')
