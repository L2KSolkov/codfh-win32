exec(open('docs/drafts/rwa_dispatch_set_helpers.py').read());VS={}
for n in range(32):
 u=d
 if n&1:u=u.replace('void *data)','void *volatile data)')
 if n&2:u=u.replace('RwUInt32 index,','volatile RwUInt32 index,')
 if n&4:u=u.replace('RwaObjHandle *handle,','RwaObjHandle *volatile handle,')
 if n&8:u=u.replace('    return setter->func','    RwUInt32 param = setter->param;\n    return setter->func').replace('setter->param, data','param, data')
 if n&16:u=u.replace('setter->func(', '((volatile rwaParamFunc *)setter)->func(')
 VS['dsq_%d'%n]=[(s,s+'\n'+u)]
