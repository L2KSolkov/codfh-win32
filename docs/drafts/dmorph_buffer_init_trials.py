"""Delta-morph buffer setup probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Unmatched.
"""
from pathlib import Path
import re
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_guarded_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
inc=('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')
names=['lockedVertexBuffer','lockedVertexBufferStatic','dstVertices','dstNormals','dstPreLightColors','dstTexCoords']
VS={'bi_base':[(anchor,body+anchor),inc]}
for pos in range(2):
 for mask in range(1,64):
  t=body;assign=[]
  for i,n in enumerate(names):
   if mask&(1<<i):t=t.replace('*'+n+' = NULL;','*'+n+';');assign.append('        '+n+' = NULL;')
  if pos==0:t=t.replace('        fmt = RpXboxGeometryGetVtxFmt(geometry);','        fmt = RpXboxGeometryGetVtxFmt(geometry);\n'+'\n'.join(assign),1)
  else:t=t.replace('        if (instancedHeader->vertexBuffer == NULL)','\n'.join(assign)+'\n        if (instancedHeader->vertexBuffer == NULL)',1)
  VS['bi_%d_%02d'%(pos,mask)]=[(anchor,t+anchor),inc]
