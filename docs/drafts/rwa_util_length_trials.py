exec(open('docs/drafts/rwa_util_trials.py').read());VS={}
old='    *length = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;'
from itertools import permutations
for n,p in enumerate(permutations('xyz')):
 for m in range(5):
  helper=''
  if m==0:expr=' + '.join('vector->%s * vector->%s'%(c,c) for c in p);stmt='    *length = '+expr+';'
  if m==1:
   helper='static __forceinline RwReal Square(RwReal x) { return x*x; }\n';stmt='    *length = '+' + '.join('Square(vector->%s)'%c for c in p)+';'
  if m==2:stmt='    RwReal '+', '.join('%s = vector->%s * vector->%s'%(c,c,c) for c in p)+';\n    *length = x+y+z;'
  if m==3:stmt='    RwReal '+', '.join('%s = vector->%s'%(c,c) for c in p)+';\n    *length = x*x+y*y+z*z;'
  if m==4:
   helper='static __forceinline RwReal Dot(RwReal x, RwReal y, RwReal z) { return x*x+y*y+z*z; }\n';stmt='    *length = Dot('+', '.join('vector->%s'%c for c in p)+');'
  VS['ul_%d_%d'%(n,m)]=[(s,s+'\n'+h+helper+d.replace(old,stmt))]
