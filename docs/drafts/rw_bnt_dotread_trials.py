"""BNT component-read probes. Use pscore.py with __rpXboxVtxFmtInstBNT
0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. No exact candidate.
"""
exec(open('docs/drafts/rw_bnt_load_trials.py').read())
VS={}
a=h.index('#define RwV3dDotProductMacro');b=h.index('\n\n',a);dot=h[a:b].replace('RwV3dDotProductMacro','DotReadTrial')
for crossmask in range(16):
 m=macro;z=m.index('    (o)->z =');tail=m[z:]
 for j,(p,c) in enumerate([('a','x'),('b','y'),('a','y'),('b','x')]):
  if crossmask&(1<<j):tail=tail.replace('('+p+')->'+c,'((const volatile RwV3d *)('+p+'))->'+c)
 m=m[:z]+tail
 for dm in range(8):
  for reverse in range(2):
   d=dot
   for j,c in enumerate('xyz'):
    if dm&(1<<j):d=d.replace('(a)->'+c,'((const volatile RwV3d *)(a))->'+c)
   if reverse:d=d.replace('->x','->X').replace('->y','->x').replace('->X','->y')
   t=body.replace('RwV3dCrossProduct(currentBinormal, currentTangent, currentNormal);','CrossLoadTrial(currentBinormal, currentTangent, currentNormal);').replace('RwV3dDotProductMacro(currentBinormal, currentBinormal)','DotReadTrial(currentBinormal, currentBinormal)')
   VS['bd_%02d_%d_%d'%(crossmask,dm,reverse)]=[(anchor,m+'\n'+d+'\n'+t+anchor)]
