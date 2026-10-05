"""Final BNT cross-product probes. pscore target __rpXboxVtxFmtInstBNT
0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. Not exact.
"""
exec(open('docs/drafts/rw_bnt_z_steps_trials.py').read())
VS={}
for p in range(5):
 for q in range(5):
  for swap in range(4):
   first='(((a)->x) * ( (b)->y))' if not swap&1 else '(((b)->y) * ( (a)->x))'
   second='(((a)->y) * ( (b)->x))' if not swap&2 else '(((b)->x) * ( (a)->y))'
   first='('*p+first+')'*p;second='('*q+second+')'*q
   f='{ RwReal value = '+first+'; value -= '+second+'; (o)->z = value; }'
   t=body[:a]+'    '+f+' \\\n'+body[b:]
   VS['zg_%d_%d_%d'%(p,q,swap)]=[(anchor,t+anchor)]
