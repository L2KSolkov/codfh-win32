"""Delta-morph callback probes. pscore: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Unmatched drafts.
"""
exec(open('docs/drafts/dmorph_count_block_trials.py').read())
VS={'dl_base':VS['dc_base']}
start=chunk.index('        for (i = 0;');end=chunk.index('            dmorphFlags |=',start)
head=chunk[start:end]
for mode in range(8):
 c=chunk
 decl='        const RpDMorphTarget *dMorphTarget = geometryData->dMorphTargets;\n        const RwReal *current = geometryData->currValues;\n        const RwReal *values = atomicData->values;\n'
 if mode&1:
  decl+='        RwUInt32 remaining = geometryData->numDMorphTargets;\n'
  loop='        for (; remaining; --remaining, ++dMorphTarget, ++current, ++values)\n        {\n'
 else:loop='        for (i = 0; i < geometryData->numDMorphTargets; ++i, ++dMorphTarget, ++current, ++values)\n        {\n'
 c=c.replace(head,decl+loop).replace('atomicData->values[i] != geometryData->currValues[i]','*values != *current')
 if mode&2:
  c=c.replace('const RwReal *values = atomicData->values;','const RwReal *values = atomicData->values;')
  c=c.replace('RwUInt32            j;','RwUInt32 j; const RwUInt8 *code = rle->code;').replace('rle->code[j]','code[j]')
 if mode&4:
  c=c.replace('const rpDMorphRLE   *rle = &dMorphTarget->rle;','const rpDMorphRLE *rle = &dMorphTarget->rle; RwUInt32 count = rle->numCodeElements;').replace('j < rle->numCodeElements','j < count')
 t=body[:a]+c+body[b:]
 VS['dl_%d'%mode]=[(anchor,t+anchor),VS['dl_base'][1]]
