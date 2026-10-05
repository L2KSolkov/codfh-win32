"""Parked delta-morph callback probes: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Run with pscore.py.
No candidate improves the saved 900-line baseline.
"""
exec(open('docs/drafts/dmorph_entry_order_trials.py').read())
VS={}
for mode in range(6):
 for mask in range(8):
  t=body
  t=t.replace('        RwUInt32 remaining = geometryData->numDMorphTargets;\n        if (remaining > 0)\n        {','        if (geometryData->numDMorphTargets > 0)\n        {\n        RwUInt32 remaining;')
  needle='        for (; remaining; --remaining, ++dMorphTarget, ++current, ++values)'
  t=t.replace(needle,'        remaining = geometryData->numDMorphTargets;\n'+needle)
  if mode==1:t=t.replace('if (geometryData->numDMorphTargets > 0)','if (((volatile rpDMorphGeometryData *)geometryData)->numDMorphTargets > 0)')
  if mode==2:t=t.replace('remaining = geometryData->numDMorphTargets;','remaining = ((volatile rpDMorphGeometryData *)geometryData)->numDMorphTargets;')
  if mode==3:t=t.replace('RwUInt32 remaining;','RwUInt32 remaining = geometryData->numDMorphTargets;').replace('        remaining = geometryData->numDMorphTargets;\n','')
  if mode==4:t=t.replace('for (; remaining; --remaining, ++dMorphTarget, ++current, ++values)','for (; remaining > 0; --remaining, ++dMorphTarget, ++current, ++values)')
  if mode==5:t=t.replace('for (; remaining; --remaining, ++dMorphTarget, ++current, ++values)','for (i = 0; i < geometryData->numDMorphTargets; ++i, ++dMorphTarget, ++current, ++values)')
  for j,p in enumerate(['dMorphTargets','currValues']):
   if mask&(1<<j):t=t.replace('= geometryData->'+p+';','= ((volatile rpDMorphGeometryData *)geometryData)->'+p+';',1)
  if mask&4:t=t.replace('const RwReal *values = atomicData->values;','const RwReal *values = ((volatile rpDMorphAtomicData *)atomicData)->values;')
  VS['cg_%d_%d'%(mode,mask)]=[(anchor,t+anchor),inc]
