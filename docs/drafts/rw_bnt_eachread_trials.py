"""BNT component-read probes. Use pscore.py with __rpXboxVtxFmtInstBNT
0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. No exact candidate.
"""
exec(open('docs/drafts/rw_bnt_load_trials.py').read())
VS={}
for firstmask in range(256):
 for lastmask in [0,8]:
  mask=firstmask|(lastmask<<8);m=macro
  # Each component expression has four source reads; preserve macro parentheses.
  for ci in reversed(range(3)):
   a=m.index('    (o)->'+'xyz'[ci]+' =');b=m.index('    (o)->'+'xyz'[ci+1]+' =',a) if ci<2 else len(m)
   q=m[a:b]
   u,v=[('y','z'),('z','x'),('x','y')][ci]
   for j,(p,c) in enumerate([('a',u),('b',v),('a',v),('b',u)]):
    if mask&(1<<(ci*4+j)):q=q.replace('('+p+')->'+c,'((const volatile RwV3d *)('+p+'))->'+c)
   m=m[:a]+q+m[b:]
  t=body.replace('RwV3dCrossProduct(currentBinormal, currentTangent, currentNormal);','CrossLoadTrial(currentBinormal, currentTangent, currentNormal);')
  VS['be_%04d'%mask]=[(anchor,m+'\n'+t+anchor)]
