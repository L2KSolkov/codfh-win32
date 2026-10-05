exec(open('docs/drafts/rwa_streamcache_clients.py').read())
from itertools import permutations
VS={}
params=['rwaCacheClient *client','RwInt32 status','RwInt32 event','void *file','RwUInt32 bytes']
args=['client','status','event','file','bytes']
for idx,p in enumerate(permutations(range(5))):
 u=t.replace('sub_244FA0('+', '.join(params)+')','sub_244FA0('+', '.join(params[i] for i in p)+')').replace('sub_244FA0('+', '.join(args)+');','sub_244FA0('+', '.join(args[i] for i in p)+');')
 VS['sp_%03d'%idx]=[(s,s+'\n'+u)]
