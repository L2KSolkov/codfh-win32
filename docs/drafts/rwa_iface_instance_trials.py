exec(open('docs/drafts/rwa_iface_trials.py').read());VS={}
a=d.index('// match: _sub_243FF0');prefix=d[:a];b=d[a:]
for mask in range(16):
 u=b
 if mask&1:u=u.replace('RwUInt32            count;', 'RwUInt16            count;')
 if mask&2:u=u.replace('RwUInt32            i;', 'RwUInt16            i;')
 if mask&4:u=u.replace('sub_243FF0(RwaObjInterfaceDef *def, rwaObjDef *objDef,','sub_243FF0(RwaObjInterfaceDef *def, rwaObjDef *definition,').replace('    rwaParamTables     *tables', '    rwaObjDef *objDef = definition;\n    rwaParamTables     *tables')
 if mask&8:
  pos=u.index('    n = ((rwaParamTables *)objDef->interfaces)->noOutputs;')
  u=u[:pos]+u[pos:].replace('    for (i = 0; i < count; i++)','    { RwUInt32 k;\n    for (k = 0; k < count; k++)',1).replace('outputs[i]', 'outputs[k]').replace('getters[i]', 'getters[k]').replace('    objInterface->link.prev = head;', '    }\n    objInterface->link.prev = head;')
 VS['ii_%d'%mask]=[(s,s+'\n'+prefix+u)]
