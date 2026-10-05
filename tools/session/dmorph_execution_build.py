"""Build the production DMorph unit for differential execution.
The historical draft fallback also supports the pre-placement source tree.
"""
import sys,re
from pathlib import Path
sys.path.insert(0,'tools')
from build_probes import compile_unit,flags_for,load_flags
from match import compare
from xbe import Xbe
src='src/rw/plugin/dmorph/xbox/dmorphpipeg.c'
s=Path(src).read_text()
if '// match: _XboxDmorphAtomicInstanceCallback' not in s:
 anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
 d=Path('docs/drafts/dmorph_instance_reference_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
 s=s.replace('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"').replace(anchor,body+anchor)
p='build/tooltmp/dmorph_trace_baseline.c';Path(p).write_text(s)
flags=flags_for(src,load_flags())+['/Isrc/rw/plugin/dmorph/xbox','/Iinclude']
obj=p[:-2]+'.obj'
if not compile_unit(p,obj,flags):raise SystemExit(1)
print(obj)
print(compare(obj,'_XboxDMorphAddBlock',0x2f2860,Xbe('orig/Game_XboxMultiplayer.xbe'),{}))
print(compare(obj,'_XboxDmorphAtomicInstanceCallback',0x2f28d0,Xbe('orig/Game_XboxMultiplayer.xbe'),{}))
