exec(open('docs/drafts/rwa_streamsource_scope_trials.py').read())
from itertools import permutations
b=VS['src_m2'][0][1][len(s)+1:];VS={}
decls=['    RwUInt32            count;','    rwaQueueItem       *items;','    rwaStreamPosition  *positions;','    RwUInt32            i;']
loads=['        items = obj->state.items;','        positions = obj->state.positions;','        count = obj->state.noItems;']
for n,p in enumerate(permutations(decls)):
 for m,q in enumerate(permutations(loads)):
  u=b.replace('\n'.join(decls),'\n'.join(p)).replace('\n'.join(loads),'\n'.join(q))
  VS['sd_%d_%d'%(n,m)]=[(s,s+'\n'+u)]
