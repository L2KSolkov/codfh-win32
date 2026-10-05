exec(open('docs/drafts/rwa_streamcache_clients.py').read())
VS={}
for mask in range(1,8):
 u=t
 if mask&1:u=u.replace('        client->mode = 0;\n    }\n    else','        client->mode = 0;\n        goto failed;\n    }\n    else',1)
 if mask&2:u=u.replace('        if (position >= 0)\n        {','        if (position < 0) goto failed;\n        {',1)
 if mask&4:u=u.replace('    client->header[0] = 0;', '    { RwUInt32 *header = client->header; header[0] = 0; }',1)
 u=u.replace('    client->header[0] = 0;', '  failed:\n    client->header[0] = 0;',1) if not mask&4 else u.replace('    { RwUInt32 *header', '  failed:\n    { RwUInt32 *header',1)
 VS['sf_%d'%mask]=[(s,s+'\n'+u)]
