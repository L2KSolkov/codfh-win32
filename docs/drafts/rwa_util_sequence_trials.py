exec(open('docs/drafts/rwa_util_trials.py').read());VS={}
old='    *length = vector->x * vector->x + vector->y * vector->y + vector->z * vector->z;'
from itertools import permutations
for n,p in enumerate(permutations('xyz')):
 for m in range(4):
  stmt='    RwReal value = vector->%s;\n    RwReal total = value * value;\n    value = vector->%s;\n    total += value * value;\n    value = vector->%s;\n    *length = total + value * value;'%p
  if m&1:stmt=stmt.replace('RwReal total', 'double total')
  if m&2:stmt=stmt.replace('    value = vector->%s;\n    *length'%p[2], '    { RwReal last = vector->%s;\n    *length'%p[2]).replace('total + value * value;', 'total + last * last; }')
  VS['uq_%d_%d'%(n,m)]=[(s,s+'\n'+h+d.replace(old,stmt))]
