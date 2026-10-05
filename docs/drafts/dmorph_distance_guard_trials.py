"""Delta-morph address-distance probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Best 894; not exact.
"""
exec(open('docs/drafts/dmorph_value_distance_trials.py').read())
body=VS['vd_RwUInt32_0_0_1'][0][1][:-len(anchor)]
from itertools import permutations
VS={}
a=body.index('        const RpDMorphTarget *dMorphTarget =');b=body.index('        for (; remaining;',a)
head=body[a:b]
for direct in range(2):
 lines=['const RpDMorphTarget *dMorphTarget = geometryData->dMorphTargets;','const RwReal *current = geometryData->currValues;','RwUInt32 valueOffset = (RwUInt32)atomicData->values - (RwUInt32)'+('geometryData->currValues' if direct else 'current')+';']
 for k,order in enumerate(permutations(range(3))):
  if not direct and order.index(2)<order.index(1):continue
  for mode in range(4):
   h='\n'.join('        '+lines[j] for j in order)+'\n'
   t=body[:a]+h+body[b:]
   if mode:
    t=t.replace('        RwUInt32 remaining = geometryData->numDMorphTargets;\n        if (remaining > 0)\n        {','        if (geometryData->numDMorphTargets > 0)\n        {\n        RwUInt32 remaining;')
    assign='        remaining = '+('((volatile rpDMorphGeometryData *)geometryData)->numDMorphTargets' if mode==3 else 'geometryData->numDMorphTargets')+';\n'
    if mode==1:t=t.replace('        RwUInt32 remaining;', '        RwUInt32 remaining = geometryData->numDMorphTargets;',1)
    else:t=t.replace('        for (; remaining;',assign+'        for (; remaining;',1)
   VS['vg_%d_%d_%d'%(direct,k,mode)]=[(anchor,t+anchor),inc]
