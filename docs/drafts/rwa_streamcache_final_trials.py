exec(open('docs/drafts/rwa_streamcache_smallparams.py').read())
b=VS['cp_024'][0][1][len(s)+1:];VS={}
for n in range(12):
 u=b
 if n==0:u=u.replace('    client->header[0] = 0;', '    status = 4;\n    client->header[0] = 0;').replace('client->holder->file, 0, 4, event','client->holder->file, 0, status, event')
 if n==1:u=u.replace('    client->header[0] = 0;', '    { RwInt32 error = 4;\n    client->header[0] = 0;').replace('client->holder->file, 0, 4, event, client->data);','client->holder->file, 0, error, event, client->data); }')
 if n in (2,3,4):
  k=n-2;u=u.replace('    client->header[%d] = 0;'%k,'    { RwUInt32 *header = client->header; header[%d] = 0; }'%k)
 if n==5:u=u.replace('    client->header[0] = 0;', '    file = client->holder->file;\n    client->header[0] = 0;').replace('client->callback(client->holder->file, 0, 4, event','client->callback(file, 0, 4, event')
 if n==6:u=u.replace('    client->header[0] = 0;', '    bytes = 0;\n    client->header[0] = 0;').replace('client->holder->file, 0, 4, event','client->holder->file, bytes, 4, event')
 if n==7:u=u.replace('    client->header[0] = 0;', '    { rwaCacheClient *finished = client;\n    client->header[0] = 0;').replace('client->callback(client->holder->file, 0, 4, event, client->data);','finished->callback(finished->holder->file, 0, 4, event, finished->data); }')
 if n>=8:
  decl=['void *data = client->data;','rwaCacheFile *holder = client->holder;','rwaCacheCallBack cb = client->callback;','void *file = client->holder->file;'][n-8]
  old='client->callback(client->holder->file, 0, 4, event, client->data);'
  new=['client->callback(client->holder->file, 0, 4, event, data);','client->callback(holder->file, 0, 4, event, client->data);','cb(client->holder->file, 0, 4, event, client->data);','client->callback(file, 0, 4, event, client->data);'][n-8]
  u=u.replace(old,'{ '+decl+' '+new+' }')
 VS['hf_%d'%n]=[(s,s+'\n'+u)]
