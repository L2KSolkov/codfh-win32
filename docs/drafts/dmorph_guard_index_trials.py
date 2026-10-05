"""Delta-morph initialization probes. Use pscore with
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. No exact match.
"""
exec(open('docs/drafts/dmorph_initial_order_trials.py').read())
t=VS['dg_0_0'][0][1][:-len(anchor)];VS={'di_guard':[(anchor,t+anchor),inc]}
old='for (; remaining; --remaining, ++dMorphTarget, ++current, ++values)'
for n in range(16):
 u=t
 if n&1:u=u.replace('if (remaining)','if (remaining > 0)')
 if n&2:
  u=u.replace(old,'for (i = 0; i < remaining; ++i, ++dMorphTarget, ++current, ++values)')
 if n&4:
  u=u.replace('RwUInt32 remaining = geometryData->numDMorphTargets;','RwUInt32 remaining = geometryData->numDMorphTargets; RwUInt32 targetIndex;')
  u=u.replace('for (i = 0; i < remaining; ++i,','for (targetIndex = 0; targetIndex < remaining; ++targetIndex,')
 if n&8:
  u=u.replace('RwUInt32 count = rle->numCodeElements;','RwUInt32 count;').replace('for (j = 0; j < count; j++)','count = rle->numCodeElements;\n                for (j = 0; j < count; j++)')
 VS['di_%02d'%n]=[(anchor,u+anchor),inc]
