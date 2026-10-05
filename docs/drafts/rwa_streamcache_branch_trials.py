exec(open('docs/drafts/rwa_streamcache_smallparams.py').read())
b=VS['cp_024'][0][1][len(s)+1:];VS={}
start=b.index('    if (status == 4)');stop=b.index('    client->header[0] = 0;',start)
mid=b[b.index('        RwInt32     position;',start):stop];mid=mid[:mid.rfind('    }')]
for n in range(4):
 if n==0:block='    if (status != 4)\n    {\n'+mid+'    }\n    else client->mode = 0;\n'
 if n==1:block='    if (status == 4) { client->mode = 0; goto failed; }\n    {\n'+mid+'    }\n  failed:\n'
 if n==2:block='    if (status != 4) goto normal;\n    client->mode = 0;\n    goto failed;\n  normal:\n    {\n'+mid+'    }\n  failed:\n'
 if n==3:block='    if (status == 4) goto error;\n    {\n'+mid+'    }\n    goto failed;\n  error:\n    client->mode = 0;\n  failed:\n'
 u=b[:start]+block+b[stop:];VS['hb_%d'%n]=[(s,s+'\n'+u)]
