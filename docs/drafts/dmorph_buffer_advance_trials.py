"""Unsigned-count delta-morph probes: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c via pscore.py.
Best remains 898 normalized lines. See questions.md.
"""
from pathlib import Path
import re
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_unsigned_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
inc=('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')
a=body.index('        if (positions)',body.index('        flagsStatic ='));b=body.index('        if (color)',a);chunk=body[a:b]
pattern=r'(currentVertexBuffer(?:Static)?) \+= (_rpXboxVtxFmt(?:InstV3d|GetSize)\([^;]+\));'
forms=list(re.finditer(pattern,chunk));assert len(forms)==8
VS={'va_base':[(anchor,body+anchor),inc]}
for mode in range(6):
 for mask in range(1,16):
  c=chunk
  for j,m in reversed(list(enumerate(forms))):
   if mask&(1<<(j//2)):
    ptr,call=m[1],m[2]
    dest='dstVertices' if j<4 else 'dstNormals'
    expr=[ptr+' = '+call+' + '+ptr+';',ptr+' = '+dest+' + '+call+';','{ RwUInt32 size = '+call+'; '+ptr+' += size; }','{ const RwUInt8 *start = '+ptr+'; RwUInt32 size = '+call+'; '+ptr+' = (RwUInt8 *)start + size; }',ptr+' = (RwUInt8 *)((RwUInt32)'+ptr+' + '+call+');',ptr+' = '+call+' + '+dest+';'][mode]
    c=c[:m.start()]+expr+c[m.end():]
  VS['va_%d_%02d'%(mode,mask)]=[(anchor,body[:a]+c+body[b:]+anchor),inc]
