"""Unsigned-count delta-morph probes: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c via pscore.py.
Best remains 898 normalized lines. See questions.md.
"""
exec(open('docs/drafts/dmorph_buffer_advance_trials.py').read())
a=body.index('        const RpDMorphTarget *dMorphTarget =');b=body.index('    if (dmorphLockedSinceLastInst ||',a);chunk=body[a:b]
VS={}
for mask in range(8):
 for mode in range(3):
  c=chunk;incparts=[];decls=[]
  if mask&1:
   c=c.replace('const RpDMorphTarget *dMorphTarget = geometryData->dMorphTargets;','const RpDMorphTarget *targets = geometryData->dMorphTargets;')
   decls.append('const RpDMorphTarget *dMorphTarget = &targets[i];')
  else:incparts.append('++dMorphTarget')
  if mask&2:c=c.replace('*values != *current','*values != current[i]')
  else:incparts.append('++current')
  if mask&4:c=c.replace('*values !=','values[i] !=')
  else:incparts.append('++values')
  oldloop='for (; remaining; --remaining, ++dMorphTarget, ++current, ++values)'
  step=', '.join((['--remaining','++i'] if mode==0 else ['++i'])+incparts)
  cond=['remaining','i < remaining','i < geometryData->numDMorphTargets'][mode]
  c=c.replace(oldloop,'for (i = 0; '+cond+'; '+step+')')
  c=c.replace('            dmorphFlags |=','            '+' '.join(decls)+'\n            dmorphFlags |=',1)
  VS['mx_%d_%d'%(mask,mode)]=[(anchor,body[:a]+c+body[b:]+anchor),inc]
