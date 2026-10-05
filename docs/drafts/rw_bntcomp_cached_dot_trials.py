"""Compressed BNT scratch probes; pscore target __rpXboxVtxFmtInstBNTComp
0x2DE0F0 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. Not matched source.
"""
exec(open('docs/drafts/rw_bntcomp_normalize_reads.py').read())
from itertools import permutations
VS={}
for dm in range(8):
 for k,order in enumerate(permutations('xyz')):
  for sm in [2,4]:
   sc=scale
   for j,c in enumerate('xyz'):
    if sm&(1<<j):sc=sc.replace('(a)->'+c,'((const volatile RwV3d *)(a))->'+c)
   init='RwV3d dotValues;\n'+'\n'.join('dotValues.'+c+' = '+('((const volatile RwV3d *)currentTangent)->' if dm&(1<<'xyz'.index(c)) else 'currentTangent->')+c+';' for c in order)
   expr='{ '+init+'\n { RwReal length2 = RwV3dDotProductMacro(&dotValues, &dotValues); rwInvSqrtMacro(&unused, length2); CompScaleTrial(currentTangent, currentTangent, unused); } }'
   t=body.replace('_rwV3dNormalizeMacro(unused, currentTangent, currentTangent);',expr)
   VS['cc_%d_%d_%d'%(dm,k,sm)]=[(anchor,sc+'\n'+t+anchor)]
