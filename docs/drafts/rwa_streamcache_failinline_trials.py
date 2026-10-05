exec(open('docs/drafts/rwa_streamcache_smallparams.py').read())
b=VS['cp_024'][0][1][len(s)+1:];VS={}
a=b.index('    client->header[0] = 0;');e=b.index('\n}',a);tail=b[a:e]
for n,p in enumerate(permutations(range(3))):
 params=['rwaCacheClient *client','RwInt32 event','RwInt32 status'];args=['client','event','4']
 helper='static __forceinline void CacheFailed('+', '.join(params[i] for i in p)+') {\n'+tail.replace(', 0, 4, event',', 0, status, event')+'\n}\n'
 u=helper+b[:a]+'    CacheFailed('+', '.join(args[i] for i in p)+');'+b[e:]
 VS['hi_%d'%n]=[(s,s+'\n'+u)]
