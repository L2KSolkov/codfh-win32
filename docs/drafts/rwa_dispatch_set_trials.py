exec(open('docs/drafts/rwa_dispatch_trials.py').read());VS={}
for n in range(12):
 u=d[:d.index('// match: _sub_23F8E0')]
 if n&1:u=u.replace('    return setter->func(handle->obj, setter->param, data)', '    RwUInt32 param = setter->param;\n    return setter->func(handle->obj, param, data)')
 if n&2:u=u.replace('    rwaParamFunc   *setter', '    void *value = data;\n    rwaParamFunc   *setter').replace('setter->param, data)', 'setter->param, value)').replace('param, data)', 'param, value)')
 if n&4:u=u.replace('Behavior_DispatchCallback(RwaObjHandle *handle,','Behavior_DispatchCallback(RwaObjHandle *arg,').replace('    rwaParamFunc   *setter', '    RwaObjHandle *handle = arg;\n    rwaParamFunc   *setter')
 if n&8:u=u.replace('    rwaParamFunc   *setter = &handle->objInterface->setters[index];', '    rwaObjInterface *iface = handle->objInterface;\n    rwaParamFunc *table = iface->setters;\n    rwaParamFunc *setter = &table[index];')
 VS['ds_%d'%n]=[(s,base+'\n'+u)]

