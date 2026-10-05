"""Delta-morph callback probes. pscore: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Unmatched drafts.
"""
from pathlib import Path
import re,itertools
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
a=body.index('    if (geometryData && atomicData->values)');b=body.index('    if (dmorphLockedSinceLastInst ||',a);chunk=body[a:b]
VS={'dc_base':[(anchor,body+anchor),('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')]}
names=['geometryData','atomicData','dmorphLockedSinceLastInst','dmorphFlags'];types=['rpDMorphGeometryData *geometryData','rpDMorphAtomicData *atomicData','RwUInt32 *locked','RwUInt32 *flags']
for k,order in enumerate(itertools.permutations(range(4))):
 for mode in range(2):
  c=chunk
  if mode==0:c=c.replace('dmorphLockedSinceLastInst','(*locked)').replace('dmorphFlags','(*flags)');decl='RwUInt32 i, numBlocks = 0;';tail='return numBlocks;'
  else:decl='RwUInt32 i, numBlocks = 0, dmorphFlags = 0, dmorphLockedSinceLastInst = 0;';tail='*locked = dmorphLockedSinceLastInst; *flags = dmorphFlags; return numBlocks;'
  fn='static __forceinline RwUInt32 DMorphCountTrial('+', '.join(types[i] for i in order)+') { '+decl+'\n'+c+tail+'\n}\n'
  call='    numBlocks = DMorphCountTrial('+', '.join(('&' if i>=2 else '')+names[i] for i in order)+');\n\n'
  t=fn+body[:a]+call+body[b:]
  VS['dc_%02d_%d'%(k,mode)]=[(anchor,t+anchor),VS['dc_base'][1]]
