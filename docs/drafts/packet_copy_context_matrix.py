from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import sys
sys.path.insert(0,'tools')
from build_probes import compile_unit,flags_for,load_flags,MATCH_RE,aliases_in
from match import compare
from xbe import Xbe
from coff import Coff
root=Path('build/tooltmp/packet_copy_context_matrix');root.mkdir(exist_ok=True)
full=Path('src/recovered/unit_1D0100.cpp').read_text(encoding='latin1')
hdr=Path('include/game/netqueue.h').read_text(encoding='latin1')
incs={'small':'#include "game/netqueue.h"\n',
      'full':'#include "types/type_DC400.h"\n#include "game/netmsg.h"\n'}
uses={
 'new':'void packet_copy_trial(void *p,const type_3E4E58 &s) { new(p) type_3E4E58(s); }',
 'globalnew':'void packet_copy_trial(void *p,const type_3E4E58 &s) { ::new(p) type_3E4E58(s); }',
 'return':'type_3E4E58 packet_copy_trial(const type_3E4E58 &s) { return s; }',
 'template':'template RwInt32 type_1FA230_list<type_3E4E58>::sub_1D3F80(const type_3E4E58 &arg_0);',
}
vs={k+'_'+n:(i+u,hdr) for k,i in incs.items() for n,u in uses.items()}
vs['fullunit_globalnew']=(full,hdr.replace('new (p) T(arg_0);','::new (p) T(arg_0);'))
vs['fullunit_earlycall']=(incs['full']+uses['new']+'\n'+full,hdr)
sym='??0type_3E4E58@@QAE@ABU0@@Z';x=Xbe('orig/Game_XboxMultiplayer.xbe')
def run(item):
 n,(s,h)=item;inc=root/n;(inc/'game').mkdir(parents=True,exist_ok=True)
 (inc/'game/netqueue.h').write_text(h,encoding='latin1')
 p=inc/'probe.cpp';p.write_text(s,encoding='latin1');o=inc/'probe.obj'
 flags=['/I'+str(inc),'/Iinclude','/FAsc','/Fa'+str(inc/'probe.asm')]+flags_for('src/recovered/unit_1D0100.cpp',load_flags())
 msgs=[]
 if not compile_unit(str(p),str(o),flags,msgs):return n,str(msgs)
 c=Coff(str(o));ok,msg=compare(c,sym,0x1D4290,x,{})
 fails=[]
 if n.startswith('fullunit'):
  for fs,a in MATCH_RE.findall(full):
   yes,m=compare(c,fs,int(a,16),x,aliases_in(full))
   if not yes:fails.append(m.splitlines()[0])
 return n,msg.splitlines()[0],fails
with ThreadPoolExecutor(4) as pool:
 for result in pool.map(run,vs.items()):print(*result,sep='\n')
