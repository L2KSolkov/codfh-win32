"""Compressed BNT scratch probes; pscore target __rpXboxVtxFmtInstBNTComp
0x2DE0F0 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. Not matched source.
"""
exec(open('docs/drafts/rw_bntcomp_cached_dot_trials.py').read())
VS={}
for k,mapping in enumerate(permutations('xyz')):
 for j,order in enumerate(permutations('xyz')):
  for mask in range(8):
   sc=scale.replace('(a)->y','((const volatile RwV3d *)(a))->y')
   init='RwV3d dotValues;\n'+'\n'.join('dotValues.'+c+' = '+('((const volatile RwV3d *)currentTangent)->' if mask&(1<<'xyz'.index(c)) else 'currentTangent->')+mapping['xyz'.index(c)]+';' for c in order)
   expr='{ '+init+'\n { RwReal length2 = RwV3dDotProductMacro(&dotValues, &dotValues); rwInvSqrtMacro(&unused, length2); CompScaleTrial(currentTangent, currentTangent, unused); } }'
   t=body.replace('_rwV3dNormalizeMacro(unused, currentTangent, currentTangent);',expr)
   VS['cp_%d_%d_%d'%(k,j,mask)]=[(anchor,sc+'\n'+t+anchor)]
