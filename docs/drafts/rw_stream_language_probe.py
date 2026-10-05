"""Read-only C/C++ compiler-mode comparison for the parked RwStreamSkip.
Both modes retain the +0x87 SIB difference. Writes scratch objects only.
"""
import sys
from pathlib import Path
sys.path.insert(0,'tools')
from build_probes import compile_unit, flags_for, load_flags
from match import compare
from xbe import Xbe
src='src/rw/src/plcore/bastream.c';f=flags_for(src,load_flags())+['/Isrc/rw/src/plcore','/Iinclude']
x=Xbe('orig/Game_XboxMultiplayer.xbe')
for mode in ['TC','TP']:
 obj='build/tooltmp/stream_language_'+mode+'.obj';out=[]
 ok=compile_unit(src,obj,[v for v in f if v not in ['/TC','/TP']]+['/'+mode],out)
 if ok:print(mode,compare(obj,'_RwStreamSkip',0x2A7210,x,{}))
 else:print(mode, '\n'.join(out)[:2500])
