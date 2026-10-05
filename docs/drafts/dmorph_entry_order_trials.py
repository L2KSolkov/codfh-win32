"""Parked delta-morph callback probes: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Run with pscore.py.
No candidate improves the saved 900-line baseline.
"""
from pathlib import Path
import re,itertools
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_guarded_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
inc=('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')
a=body.index('    RpAtomic                *atomic');b=body.index('    RwUInt32                dmorphLocked',a)
lines=body[a:b].strip().splitlines();z=body.index('    dmorphLockedSinceLastInst = 0;');e=body.index('    if (geometryData &&',z);zeros=body[z:e].strip().splitlines()
VS={'di_top_base':[(anchor,body+anchor),inc]}
for k,order in enumerate(itertools.permutations(range(2,5))):
 for j,zorder in enumerate(itertools.permutations(zeros)):
  for mode in range(3):
   lead='\n'.join('    '+lines[i].strip() for i in [0,1]+list(order))+'\n'
   if mode==1:lead=lead.replace('RPDMORPHGEOMETRYGETDATA(RpAtomicGetGeometry(atomic))','RPDMORPHGEOMETRYGETDATA(geometry)')
   if mode==2:lead=lead.replace('RpGeometryFlag          flags = (RpGeometryFlag)RpGeometryGetFlags(geometry)','RwUInt32 flags = RpGeometryGetFlags(geometry)')
   t=body[:a]+lead+body[b:z]+'\n'.join('    '+x.strip() for x in zorder)+'\n\n'+body[e:]
   VS['dt_%d_%d_%d'%(k,j,mode)]=[(anchor,t+anchor),inc]
