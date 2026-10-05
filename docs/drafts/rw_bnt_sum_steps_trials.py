"""Ordinary BNT follow-up. pscore: __rpXboxVtxFmtInstBNT 0x2DDB50
src/rw/world/pipe/p2/xbox/xbvtxfmt.c. Best four normalized lines, not exact.
"""
exec(open('docs/drafts/rw_bnt_load_trials.py').read())
VS={}
old='RwReal length2 = RwV3dDotProductMacro(currentBinormal, currentBinormal);'
for k,order in enumerate(__import__('itertools').permutations('xyz')):
 expr='RwReal length2 = currentBinormal->'+order[0]+' * currentBinormal->'+order[0]+';\n'+''.join('length2 += currentBinormal->'+c+' * currentBinormal->'+c+';\n' for c in order[1:])
 for mask in range(16):
  m=macro;z=m.index('    (o)->z =');q=m[z:]
  for j,(p,c) in enumerate([('a','x'),('b','y'),('a','y'),('b','x')]):
   if mask&(1<<j):q=q.replace('('+p+')->'+c,'((const volatile RwV3d *)('+p+'))->'+c)
  m=m[:z]+q
  t=body.replace('RwV3dCrossProduct(currentBinormal, currentTangent, currentNormal);','CrossLoadTrial(currentBinormal, currentTangent, currentNormal);').replace(old,expr)
  VS['bs_%d_%02d'%(k,mask)]=[(anchor,m+'\n'+t+anchor)]
