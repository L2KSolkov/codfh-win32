exec(open('docs/drafts/rwa_cache_current.py').read())
a=d.index('    client->header[0] = 0;');b=d.index('\n}',a);tail=d[a:b]
VS={}
for n in range(4):
 u=d.replace('        client->mode = 0;\n    }\n    else', '        client->mode = 0;\n'+tail+'\n        return;\n    }\n    else',1)
 if n&1:u=u.replace('        if (position >= 0)\n        {', '        if (position < 0) {\n'+tail+'\n            return;\n        }\n        {',1);pos=u.rfind(tail);u=u[:pos]+u[pos:].replace(tail,'',1)
 if n&2:u=u.replace('        client->mode = 0;\n    client->header[0]', '        client->mode = 0;\n    status = 4;\n    client->header[0]',1).replace('client->holder->file, 0, 4, event','client->holder->file, 0, status, event',1)
 VS['cachedup_%d'%n]=[(s,base+'\n'+u)]
