"""Delta-morph probes: _XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c via pscore.py. See questions.md.
"""
exec(open('docs/drafts/dmorph_entry_order_trials.py').read())
a=body.index('        for (; remaining;');b=body.index('    if (dmorphLockedSinceLastInst ||',a);chunk=body[a:b]
VS={}
for mask in range(128):
 c=chunk;occ=[m.start() for m in re.finditer(r'dMorphTarget->flags',c)]
 for j,pos in reversed(list(enumerate(occ))):
  if mask&(1<<j):c=c[:pos]+'((const volatile RpDMorphTarget *)dMorphTarget)->flags'+c[pos+len('dMorphTarget->flags'):]
 if mask&32:c=c.replace('rle->numCodeElements','((const volatile rpDMorphRLE *)rle)->numCodeElements')
 if mask&64:c=c.replace('rle->code','((const volatile rpDMorphRLE *)rle)->code')
 VS['qr_%03d'%mask]=[(anchor,body[:a]+c+body[b:]+anchor),inc]
