"""Read-only RwStreamSkip compiler-option probes; scratch objects only.
No option fixes the +0x87 address-encoding mismatch. See questions.md.
"""
import sys
sys.path.insert(0,'tools')
from build_probes import compile_unit,flags_for,load_flags
from match import compare
from xbe import Xbe
src='src/rw/src/plcore/bastream.c';flags=flags_for(src,load_flags())+['/Isrc/rw/src/plcore','/Iinclude'];x=Xbe('orig/Game_XboxMultiplayer.xbe')
variants={'base':[],'G5':['/G5'],'G7':['/G7'],'GB':['/GB'],'Os':['/Os'],'Oa':['/Oa'],'Ow':['/Ow'],'Oi_off':['/Oi-'],'Ob1':['/Ob1'],'Og_off':['/Og-']}
for name,opts in variants.items():
 out=[];obj='build/tooltmp/stream_schedule_'+name+'.obj'
 if compile_unit(src,obj,flags+opts,out):print(name,compare(obj,'_RwStreamSkip',0x2A7210,x,{})[1].splitlines()[0])
 else:print(name,'compile error',str(out)[:180])
