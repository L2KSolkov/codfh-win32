"""Guarded delta-morph loop probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. No exact match.
"""
from pathlib import Path
import re
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_guarded_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
inc=('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')
loops=[]
for m in re.finditer(r'for \((i|localIndex) = 0; \1 < geometryData->numDMorphTargets; \1\+\+\)',body):
 a=m.start();start=body.index('{',a);depth=1;e=start+1
 while depth:
  if body[e]=='{':depth+=1
  if body[e]=='}':depth-=1
  e+=1
 if 'const RpDMorphTarget *dMorphTarget =' in body[start:e]:loops.append((a,start,e,m[1]))
assert len(loops)==4,len(loops)
VS={}
for mask in range(16):
 t=body
 for j,(a,start,e,idx) in reversed(list(enumerate(loops))):
  if mask&(1<<j):
   c=body[start:e]
   c=c.replace('const RpDMorphTarget *dMorphTarget = &geometryData->dMorphTargets['+idx+'];','')
   c=c.replace('atomicData->values['+idx+']','(*values)').replace('geometryData->currValues['+idx+']','(*current)')
   head='{ const RpDMorphTarget *dMorphTarget = geometryData->dMorphTargets; const RwReal *values = atomicData->values; const RwReal *current = geometryData->currValues; RwUInt32 remaining = geometryData->numDMorphTargets;\nfor (; remaining; --remaining, ++dMorphTarget, ++values, ++current)\n'
   t=t[:a]+head+c+'\n}'+t[e:]
 VS['dt_%02d'%mask]=[(anchor,t+anchor),inc]
