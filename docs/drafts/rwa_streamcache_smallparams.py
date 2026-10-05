from pathlib import Path
from itertools import permutations
s=Path('src/rwa/unit_2449C0.c').read_text();t=Path('docs/drafts/rwa_streamcache_clients_followup.c').read_text();VS={}
t=t.replace('sub_2449C0(void *file, rwaCacheClient *client, RwUInt32 bytes, RwInt32 status, RwInt32 event)', 'sub_2449C0(rwaCacheClient *client, void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event)').replace('sub_2449C0(file, client, bytes, status, event);', 'sub_2449C0(client, file, bytes, status, event);')
params=['rwaCacheClient *client','void *file','RwUInt32 bytes','RwInt32 status','RwInt32 event'];args=['client','file','bytes','status','event']
for n,p in enumerate(permutations(range(5))):
 u=t.replace('sub_2449C0('+', '.join(params)+')','sub_2449C0('+', '.join(params[i] for i in p)+')').replace('sub_2449C0('+', '.join(args)+');','sub_2449C0('+', '.join(args[i] for i in p)+');')
 VS['cp_%03d'%n]=[(s,s+'\n'+u)]
