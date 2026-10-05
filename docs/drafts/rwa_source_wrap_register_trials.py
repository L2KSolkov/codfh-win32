exec(open('docs/drafts/rwa_source_wrap_shape_trials.py').read());v=VS['wraps_5'][0][1];VS={}
import itertools
old='''    RwUInt32    result = 0;
    RwUInt32    largest = 0;
    RwUInt32    track = 0;'''
for k,p in enumerate(itertools.permutations(old.splitlines())):
 for n in range(8):
  u=v.replace(old,'\n'.join(p))
  for j,var in enumerate(['result','largest','track']):
   if n&(1<<j):u=u.replace('RwUInt32    '+var,'register RwUInt32    '+var)
  VS['wrapr_%d_%d'%(k,n)]=[(s,u)]
