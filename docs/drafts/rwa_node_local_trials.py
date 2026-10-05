exec(open('docs/drafts/rwa_node_dispatch_trials.py').read());VS={}
for n in range(4):
 u=d
 if n&1:u=u.replace('rwaDecoder *obj,','rwaDecoder *arg,').replace('    rwaParamFunc *', '    rwaDecoder *obj = arg;\n    rwaParamFunc *')
 if n&2:
  for name in ['getter','setter']:
   u=u.replace('    '+name+'->func', '    RwUInt32 param = '+name+'->param;\n    '+name+'->func').replace(name+'->param, value','param, value')
 if n&4:u=u.replace('    setter->func','    return setter->func').replace('    getter->func','    return getter->func')
 VS['nl_%d'%n]=[(s,base+'\n'+u)]
