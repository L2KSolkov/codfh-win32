"""Delta-morph initialization probes. Use pscore with
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. No exact match.
"""
from pathlib import Path
import re,itertools
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_pointer_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
inc=('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')
a=body.index('        const RpDMorphTarget *dMorphTarget =');b=body.index('        for (; remaining;',a);decl=body[a:b];lines=decl.strip().splitlines()
VS={'do_base':[(anchor,body+anchor),inc]}
for k,order in enumerate(itertools.permutations(lines)):
 t=body[:a]+'\n'.join('        '+x.strip() for x in order)+'\n'+body[b:]
 VS['do_%02d'%k]=[(anchor,t+anchor),inc]
end=body.index('    if (dmorphLockedSinceLastInst ||',b)
for k,order in enumerate(itertools.permutations(lines[:3])):
 for mode in range(2):
  loop=body[b:end];p=loop.rfind('    }');loop=loop[:p]+'        }\n'+loop[p:]
  if mode:
   loop=loop.replace('for (; remaining; --remaining, ++dMorphTarget, ++current, ++values)','do')
   p=loop.index('\n        }');loop=loop[:p]+ '\n            ++dMorphTarget; ++current; ++values;'+loop[p:]
   loop=loop.replace('\n        }','\n        } while (--remaining);',1)
  t=body[:a]+'        RwUInt32 remaining = geometryData->numDMorphTargets;\n        if (remaining)\n        {\n'+'\n'.join('        '+x.strip() for x in order)+'\n'+loop+body[end:]
  VS['dg_%d_%d'%(k,mode)]=[(anchor,t+anchor),inc]
