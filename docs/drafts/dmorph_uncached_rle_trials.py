"""Delta-morph RLE cache probes: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c with pscore.py.
The 893-line rc_12 is not promoted: pointer-bias/alignment tradeoff.
"""
exec(open('docs/drafts/dmorph_target_address_trials.py').read())
a=body.index('        for (; remaining;');b=body.index('    if (dmorphLockedSinceLastInst ||',a);chunk=body[a:b]
VS={}
for mask in range(16):
 c=chunk
 if mask&1:
  c=c.replace(' RwUInt32 count = rle->numCodeElements;','').replace('j < count','j < rle->numCodeElements')
 if mask&2:
  c=c.replace(' const RwUInt8 *code = rle->code;','').replace('code[j]','rle->code[j]')
 if mask&4:
  c=c.replace('const rpDMorphRLE *rle = &dMorphTarget->rle;', '').replace('rle->','dMorphTarget->rle.')
 if mask&8:
  c=c.replace('            dmorphFlags |= dMorphTarget->flags;','            RwUInt32 targetFlags = dMorphTarget->flags;\n            dmorphFlags |= targetFlags;').replace('if (dMorphTarget->flags &','if (targetFlags &')
 VS['rc_%02d'%mask]=[(anchor,body[:a]+c+body[b:]+anchor),inc]
