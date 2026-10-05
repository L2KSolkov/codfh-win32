"""Delta-morph traversal/RLE probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Best remains 894.
"""
from pathlib import Path
import re
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_distance_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
inc=('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')
a=body.index('        const RwReal *current =');b=body.index('    if (dmorphLockedSinceLastInst ||',a);chunk=body[a:b]
VS={'ta_base':[(anchor,body+anchor),inc]}
for typ in ['RwUInt32','const RwUInt8 *','const void *']:
 for scope in range(2):
  for mode in range(3):
   c=chunk.replace('const RpDMorphTarget *dMorphTarget = geometryData->dMorphTargets;',typ+' targetAddress = ('+typ+')geometryData->dMorphTargets;')
   step='targetAddress = ('+typ+')((RwUInt32)targetAddress + sizeof(RpDMorphTarget))'
   if mode==1:step='targetAddress = ('+typ+')((const RwUInt8 *)targetAddress + sizeof(RpDMorphTarget))'
   if mode==2:step='targetAddress = ('+typ+')(((const RpDMorphTarget *)targetAddress) + 1)'
   c=c.replace('++dMorphTarget',step)
   if scope:c=c.replace('            dmorphFlags |=','            const RpDMorphTarget *dMorphTarget = (const RpDMorphTarget *)targetAddress;\n            dmorphFlags |=',1)
   else:c=c.replace('dMorphTarget->','((const RpDMorphTarget *)targetAddress)->')
   VS['ta_%d_%d_%d'%(['RwUInt32','const RwUInt8 *','const void *'].index(typ),scope,mode)]=[(anchor,body[:a]+c+body[b:]+anchor),inc]
