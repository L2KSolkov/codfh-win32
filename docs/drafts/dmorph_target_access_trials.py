"""Parked delta-morph callback probes: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Run with pscore.py.
No candidate improves the saved 900-line baseline.
"""
exec(open('docs/drafts/dmorph_entry_order_trials.py').read())
a=body.index('    if (geometryData && atomicData->values)');b=body.index('    if (dmorphLockedSinceLastInst ||',a)
VS={}
for scope in range(2):
 for mask in range(1,32):
  t=body[a:b] if not scope else body;h=''
  if mask&1:
   h+='static __forceinline RwUInt32 TargetFlagsTrial(const RpDMorphTarget *t) { return t->flags; }\n'
   t=t.replace('dMorphTarget->flags','TargetFlagsTrial(dMorphTarget)')
  if mask&2:
   h+='static __forceinline const rpDMorphRLE *TargetRLETrial(const RpDMorphTarget *t) { return &t->rle; }\n'
   t=t.replace('&dMorphTarget->rle','TargetRLETrial(dMorphTarget)')
  if mask&4:
   h+='static __forceinline const RpDMorphTarget *TargetNextTrial(const RpDMorphTarget *t) { return t + 1; }\n'
   t=t.replace('++dMorphTarget','dMorphTarget = TargetNextTrial(dMorphTarget)')
  if mask&8:
   h+='static __forceinline RwUInt32 RLECountTrial(const rpDMorphRLE *r) { return r->numCodeElements; }\n'
   t=t.replace('rle->numCodeElements','RLECountTrial(rle)')
  if mask&16:
   h+='static __forceinline const RwUInt8 *RLECodeTrial(const rpDMorphRLE *r) { return r->code; }\n'
   t=t.replace('rle->code','RLECodeTrial(rle)')
  if not scope:t=body[:a]+t+body[b:]
  VS['tg_%d_%02d'%(scope,mask)]=[(anchor,h+t+anchor),inc]
