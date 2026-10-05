exec(open('docs/drafts/rwa_iface_trials.py').read());VS={}
a=d.index('    if (!def)',d.index('sub_243E20('));b=d.index('    def->noInputs = 0;',a);end=d.index('// match: _sub_243FF0')
old=d[a:b]
for n in range(6):
 u=d
 if n==0:u=u[:a]+old.replace('return NULL;', 'goto failed;')+u[b:end].replace('    return def;', '    return def;\nfailed:\n    return NULL;')+u[end:]
 if n==1:u=u[:a]+old.replace('return NULL;', 'goto failed;')+u[b:end].replace('    return def;', 'failed:\n    return def;')+u[end:]
 if n>=2:
  block='''    if (def) goto existing;
    def = (RwaObjInterfaceDef *)sub_243670(unk_50708C, rwaMEMHINTDUR_EVENT | rwaID_80A);
    if (!def) goto failed;
    def->flags = 0;
initialize:
'''
  tail='''    return def;
existing:
    def->flags = 2;
    goto initialize;
failed:
    return NULL;'''
  if n&1:tail=tail.replace('failed:\n    return NULL;', 'failed:\n    return def;')
  if n>=4:block=block.replace('    if (def) goto existing;', '    if (!def) goto allocate;\n    goto existing;\nallocate:')
  u=u[:a]+block+u[b:end].replace('    return def;',tail)+u[end:]
 VS['ic_%d'%n]=[(s,s+'\n'+u)]
