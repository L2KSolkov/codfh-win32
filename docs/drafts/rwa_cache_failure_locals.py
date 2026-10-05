exec(open('docs/drafts/rwa_cache_current.py').read())
from itertools import permutations
VS={}
old='    client->callback(client->holder->file, 0, 4, event, client->data);'
for k,p in enumerate(permutations(['data','holder','file'])):
 for n in range(4):
  decl={'data':'void *data = client->data;', 'holder':'rwaCacheFile *holder = client->holder;', 'file':'void *file = client->holder->file;'}
  block='{\n'+''.join('        '+decl[x]+'\n' for x in p)
  block+='        client->callback('+('holder->file' if n&1 else 'file')+', 0, 4, event, data);\n    }'
  u=d.replace(old,'    '+block)
  if n&2:u=u.replace('    client->header[0] = 0;', '    { RwUInt32 *header = client->header;\n    header[0] = 0; }')
  VS['cachelocal_%d_%d'%(k,n)]=[(s,base+'\n'+u)]
