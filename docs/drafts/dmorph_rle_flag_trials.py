"""Guarded delta-morph follow-up probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. No exact candidate.
"""
from pathlib import Path
import re
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_guarded_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
inc=('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')
a=body.index('        for (; remaining;');b=body.index('    if (dmorphLockedSinceLastInst ||',a);chunk=body[a:b]
VS={'rf_base':[(anchor,body+anchor),inc]}
for mask in range(32):
 c=chunk
 if mask&1:c=c.replace('            dmorphFlags |= dMorphTarget->flags;','            RwUInt32 targetFlags = dMorphTarget->flags;\n            dmorphFlags |= targetFlags;').replace('if (dMorphTarget->flags &','if (targetFlags &')
 if mask&2:
  c=c.replace('                if (dMorphTarget->flags & rpGEOMETRYPOSITIONS)','                { RwUInt32 changedFlags = dMorphTarget->flags;\n                if (changedFlags & rpGEOMETRYPOSITIONS)').replace('                if (targetFlags & rpGEOMETRYPOSITIONS)','                { RwUInt32 changedFlags = dMorphTarget->flags;\n                if (changedFlags & rpGEOMETRYPOSITIONS)')
  for f in ['NORMALS','PRELIT','TEXTURED']:c=c.replace('if (dMorphTarget->flags & rpGEOMETRY'+f+')','if (changedFlags & rpGEOMETRY'+f+')').replace('if (targetFlags & rpGEOMETRY'+f+')','if (changedFlags & rpGEOMETRY'+f+')')
  c=c.replace('dmorphLockedSinceLastInst |= rpGEOMETRYLOCKTEXCOORDS1;\n                }','dmorphLockedSinceLastInst |= rpGEOMETRYLOCKTEXCOORDS1;\n                }\n                }')
 if mask&4:c=c.replace('if ((code[j] & 0x7F) && (code[j] & 0x80))','RwUInt8 value = code[j];\n                    if ((value & 0x7F) && (value & 0x80))')
 if mask&8:c=c.replace('j < count; j++','j < count; ++j').replace('for (j = 0; j < count; ++j)','for (j = count; j > 0; --j, ++code)').replace('code[j]','code[0]')
 if mask&16:c=c.replace('const RwUInt8 *code = rle->code;','const RwUInt8 *code;').replace('                for (j =','                code = rle->code;\n                for (j =')
 VS['rf_%02d'%mask]=[(anchor,body[:a]+c+body[b:]+anchor),inc]
