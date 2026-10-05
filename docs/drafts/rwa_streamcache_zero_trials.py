exec(open('docs/drafts/rwa_streamcache_smallparams.py').read())
b=VS['cp_024'][0][1][len(s)+1:];VS={}
old='    client->header[0] = 0;\n    client->header[1] = 0;\n    client->header[2] = 0;'
forms=['    { RwInt32 i; for(i=0;i<3;i++) client->header[i]=0; }','    { RwUInt32 i; for(i=0;i<3;i++) client->header[i]=0; }','    *(client->header) = 0;\n    *(client->header+1) = 0;\n    *(client->header+2) = 0;','    client->header[0] = FALSE;\n    client->header[1] = FALSE;\n    client->header[2] = FALSE;']
for n,f in enumerate(forms):VS['hz_%d'%n]=[(s,s+'\n'+b.replace(old,f))]
for n in range(8):
 u=b
 if n&1:u=u.replace('    if (status == 4)','    switch (status)\n    {\n    case 4:',1).replace('    else\n    {','    default:\n    {',1).replace(old,'    }\n'+old,1).replace('        client->mode = 0;\n    }','        client->mode = 0;\n        break;\n    }',1)
 if n&2:u=u.replace('        RwInt32     position;','').replace('    if (status == 4)','    RwInt32 position;\n    if (status == 4)',1) if not n&1 else u.replace('        RwInt32     position;','').replace('    switch (status)','    RwInt32 position;\n    switch (status)',1)
 if n&4:u=u.replace('if (position >= 0)','if (position != -1)')
 VS['hc_%d'%n]=[(s,s+'\n'+u)]
