exec(open('docs/drafts/rwa_cache_open_current.py').read())
VS={}
for n in range(16):
 u=d
 if n&1:u=u.replace('rwaCacheCallBack callback,', 'rwaCacheCallBack volatile callback,')
 if n&2:u=u.replace('void *data)', 'void *volatile data)')
 if n&4:u=u.replace('const RwChar *name,', 'const RwChar *volatile name,')
 if n&8:u=u.replace('rwaCacheClient *client,', 'rwaCacheClient *volatile input,').replace('    holder->type = type;', '    rwaCacheClient *client = input;\n    holder->type = type;')
 VS['cacheopenaccess_%d'%n]=[(s,s+'\n'+u)]
