"""Delta-morph address-distance probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Best 894; not exact.
"""
exec(open('docs/drafts/dmorph_buffer_advance_trials.py').read())
a=body.index('        const RpDMorphTarget *dMorphTarget =');b=body.index('    if (dmorphLockedSinceLastInst ||',a);chunk=body[a:b]
VS={'vd_base':[(anchor,body+anchor),inc]}
for typ in ['RwUInt32','RwInt32']:
 for reverse in range(2):
  for form in range(4):
   for init in range(2):
    base='values' if reverse else 'current';other='current' if reverse else 'values'
    c=chunk
    c=c.replace('const RwReal *'+other+' = '+('geometryData->currValues' if reverse else 'atomicData->values')+';',typ+' valueOffset;')
    statement='valueOffset = ('+typ+')'+('geometryData->currValues' if reverse else 'atomicData->values')+' - ('+typ+')'+base+';'
    if init:c=c.replace('        for (; remaining;', '        '+statement+'\n        for (; remaining;')
    else:
     needle='const RwReal *'+base+' = '+('atomicData->values' if reverse else 'geometryData->currValues')+';'
     c=c.replace(needle,needle+'\n        '+statement)
     # C89: declare offset before the base initialization when needed.
     c=c.replace(typ+' valueOffset;','')
     c=typ+' valueOffset;\n'+c
    c=c.replace(', ++'+other,'')
    address=['(RwUInt32)'+base+' + valueOffset','valueOffset + (RwUInt32)'+base,'(RwUInt32)((const RwUInt8 *)'+base+' + valueOffset)','(RwUInt32)'+base+' - -valueOffset'][form]
    c=c.replace('*'+other+' !=' if not reverse else '!= *'+other,('*(const RwReal *)('+address+') !=') if not reverse else '!= *(const RwReal *)('+address+')')
    VS['vd_%s_%d_%d_%d'%(typ,reverse,form,init)]=[(anchor,body[:a]+c+body[b:]+anchor),inc]
