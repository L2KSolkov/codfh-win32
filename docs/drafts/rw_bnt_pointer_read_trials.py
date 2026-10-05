"""Historical ordinary-BNT trials against source at cc3f31efa.
zp_ab_1_12 is exact: 1425 bytes, 10 relocations. See questions.md.
"""
exec(open('docs/drafts/rw_bnt_z_steps_trials.py').read())
import itertools
VS={}
exprs=['(( (((a)->x) * ( (b)->y))) - ( (((a)->y) * ( (b)->x))))','(a)->x * (b)->y - (b)->x * (a)->y','(b)->y * (a)->x - (b)->x * (a)->y']
for order in itertools.permutations('ab'):
 for k,expr in enumerate(exprs):
  for mask in range(16):
   q=expr
   for j,(p,c) in enumerate([('a','x'),('a','y'),('b','x'),('b','y')]):
    if mask&(1<<j): q=q.replace('('+p+')->'+c,'((const volatile RwV3d *)('+p+'))->'+c)
   fn='static __forceinline RwReal CrossZPointerTrial('+', '.join('const RwV3d *'+p for p in order)+') { return '+q+'; }\n'
   t=fn+body[:a]+'    (o)->z = CrossZPointerTrial('+', '.join('('+p+')' for p in order)+'); \\\n'+body[b:]
   VS['zp_%s_%d_%d'%(''.join(order),k,mask)]=[(anchor,t+anchor)]
for k,expr in enumerate(exprs):
 for mask in range(16):
  q=expr
  for j,(p,c) in enumerate([('a','x'),('a','y'),('b','x'),('b','y')]):
   if mask&(1<<j):q=q.replace('('+p+')->'+c,'CrossReadTrial(&('+p+')->'+c+')')
  for typ in ['const RwReal','const volatile RwReal']:
   fn='static __forceinline RwReal CrossReadTrial('+typ+' *p) { return *p; }\n'
   t=fn+body[:a]+'    (o)->z = '+q+'; \\\n'+body[b:]
   VS['zr_%d_%d_%d'%(k,mask,'volatile' in typ)]=[(anchor,t+anchor)]
