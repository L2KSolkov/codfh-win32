exec(open('docs/drafts/rwa_cache_current.py').read())
VS={}
old='    client->header[0] = 0;\n    client->header[1] = 0;\n    client->header[2] = 0;'
for n in range(8):
 body=old
 ret='client' if not n&1 else 'client->holder'
 typ='rwaCacheClient *' if not n&1 else 'rwaCacheFile *'
 helper='static __forceinline '+typ+'clearHeader(rwaCacheClient *client) {\n'+body+'\nreturn '+ret+';\n}\n'
 u=d.replace(old,'    client = clearHeader(client);' if not n&1 else '    { rwaCacheFile *holder = clearHeader(client);')
 if n&1:u=u.replace('client->callback(client->holder->file, 0, 4, event, client->data);','client->callback(holder->file, 0, 4, event, client->data); }')
 if n&2:helper=helper.replace('return '+ret+';', 'if (client) return '+ret+'; return NULL;')
 if n&4:helper=helper.replace('client->header[0] = 0;', 'RwUInt32 *header = client->header; header[0] = 0;')
 u=u.replace('// match: _sub_244FA0',helper+'\n// match: _sub_244FA0')
 VS['cacheclear_%d'%n]=[(s,base+'\n'+u)]
