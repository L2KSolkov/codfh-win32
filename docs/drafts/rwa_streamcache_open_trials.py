exec(open('docs/drafts/rwa_streamcache_clients.py').read())
VS={}
a=t.index('            client->request.link.prev = NULL;');b=t.index('            _RtFSManagerFOpen',a)
init=t[a:b]
from itertools import permutations
params=['rwaCacheClient *client','rwaCacheFile *holder','rwaCacheCallBack callback','void *data']
args=['client','holder','callback','data']
for n,p in enumerate(permutations(range(4))):
 helper='static __forceinline void ClientInit('+', '.join(params[i] for i in p)+') {\n'+init+'}\n'
 u=helper+t[:a]+'            ClientInit('+', '.join(args[i] for i in p)+');\n'+t[b:]
 VS['so_%d'%n]=[(s,s+'\n'+u)]
