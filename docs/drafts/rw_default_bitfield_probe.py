"""Default-instancer format-access probes. No exact match.
Target __rpXboxDefaultInstance 0x2DED60, xbvtxfmt.c. See questions.md.
"""
from pathlib import Path
import sys,re
sys.path.insert(0,'tools')
from build_probes import compile_unit,flags_for,load_flags
from match import compare
from xbe import Xbe
ns={};exec(Path('docs/drafts/rw_default_instance_trials.py').read_text(),ns)
src='src/rw/world/pipe/p2/xbox/xbvtxfmt.c';s=Path(src).read_text().replace(ns['anchor'],ns['body']+ns['anchor'],1)
header=Path('src/rw/world/pipe/p2/xbox/xbvtxfmt.h').read_text();start=header.index('struct RpXboxVtxFmt\n{');end=header.index('\n};',start)+3
fields=[('pos',4),('norm',4),('texCoord',16),('prelit',1),('bnt',3),('reserved',4)]
x=Xbe('orig/Game_XboxMultiplayer.xbe')
for name,typ in [('base',None),('word','RwUInt32'),('uint','unsigned int')]:
 overlay=Path('build/tooltmp/default_bitfield_'+name);overlay.mkdir(exist_ok=True)
 h=header if typ is None else header[:start]+'struct RpXboxVtxFmt\n{\n'+''.join('    '+typ+' '+field+' : '+str(bits)+';\n' for field,bits in fields)+'};'+header[end:]
 (overlay/'xbvtxfmt.h').write_text(h)
 p=overlay/'probe.c';p.write_text(s+'\ntypedef char CheckFormatSize[sizeof(RpXboxVtxFmt)==4 ? 1 : -1];\n')
 f=['/I'+str(overlay)]+flags_for(src,load_flags())+['/Isrc/rw/world/pipe/p2/xbox','/Iinclude'];obj=str(overlay/'probe.obj');out=[]
 if compile_unit(str(p),obj,f,out):print(name,compare(obj,'__rpXboxDefaultInstance',0x2DED60,x,{})[1].splitlines()[0])
 else:print(name,'compile error',str(out)[:500])
