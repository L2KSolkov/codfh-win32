exec(open('docs/drafts/rwa_cache_current.py').read())
VS={}
for n in range(16):
 u=d
 for i in range(3):
  if n&(1<<i):u=u.replace('client->header[%d] = 0;'%i, '(*(RwUInt32 *volatile *)&client->header)[%d] = 0;'%i)
 if n&8:u=u.replace('client->callback(client->holder->file, 0, 4, event, client->data);', '((volatile rwaCacheClient *)client)->callback(client->holder->file, 0, 4, event, client->data);')
 VS['cacheaccess_%d'%n]=[(s,base+'\n'+u)]
