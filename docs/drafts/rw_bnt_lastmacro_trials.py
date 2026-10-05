"""Parked BNT load-order probes. Run pscore.py with
__rpXboxVtxFmtInstBNT 0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c.
Best remains 14 normalized lines; no candidate matches.
"""
exec(open('docs/drafts/rw_bnt_load_trials.py').read())
import itertools
VS={}
a=h.index('#define RwV3dDotProductMacro');b=h.index('\n\n',a);dot=h[a:b].replace('RwV3dDotProductMacro','DotLoadTrial')
for mask in range(16):
 for order in itertools.permutations('xyz'):
  m=macro
  z=m.index('    (o)->z =');tail=m[z:]
  for j,(p,c) in enumerate([('a','x'),('a','y'),('b','x'),('b','y')]):
   if mask&(1<<j):tail=tail.replace('('+p+')->'+c,'((const volatile RwV3d *)('+p+'))->'+c)
  m=m[:z]+tail
  d=dot
  for c,n in zip('xyz','XYZ'):d=d.replace('->'+c,'->'+n)
  for c,n in zip('XYZ',order):d=d.replace('->'+c,'->'+n)
  t=body.replace('RwV3dCrossProduct(currentBinormal, currentTangent, currentNormal);','CrossLoadTrial(currentBinormal, currentTangent, currentNormal);').replace('RwV3dDotProductMacro(currentBinormal, currentBinormal)','DotLoadTrial(currentBinormal, currentBinormal)')
  VS['bp_%02d_%s'%(mask,''.join(order))]=[(anchor,m+'\n'+d+'\n'+t+anchor)]
