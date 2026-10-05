exec(open('docs/drafts/rwa_dispatch_trials.py').read());VS={}
from itertools import permutations
for n,p in enumerate(permutations(range(3))):
 for m in range(3):
  params=['rwaParamFunc *access','rwaInstance *obj','void *data'];args=['getter','handle->obj','data']
  helper='static __forceinline '+['RwBool','void *','RwInt32'][m]+' CallParam('+', '.join(params[i] for i in p)+') { return '+('' if m==1 else '(RwBool)')+'access->func(obj, access->param, data); }\n'
  u=d.replace('getter->func(handle->obj, getter->param, data)', 'CallParam('+', '.join(args[i] for i in p)+')')
  VS['di_%d_%d'%(n,m)]=[(s,base+'\n'+helper+u)]
for n in range(6):
 u=d
 if n==0:u=u.replace('    return getter->func(handle->obj, getter->param, data)', '    RwUInt32 param = getter->param;\n    return getter->func(handle->obj, param, data)')
 if n==1:u=u.replace('    return getter->func(handle->obj, getter->param, data)', '    RwUInt16 param = getter->param;\n    return getter->func(handle->obj, param, data)')
 if n==2:u=u.replace('sub_23F8E0(RwaObjHandle *handle,','sub_23F8E0(RwaObjHandle *arg,').replace('    rwaParamFunc   *getter', '    RwaObjHandle *handle = arg;\n    rwaParamFunc   *getter')
 if n==3:u=u.replace('    return getter->func(handle->obj, getter->param, data) ? handle : NULL;', '    if (!getter->func(handle->obj, getter->param, data)) return NULL;\n    return handle;')
 if n==4:u=u.replace('    return getter->func(handle->obj, getter->param, data)', '    rwaParamFunc access = *getter;\n    return access.func(handle->obj, access.param, data)')
 if n==5:u=u.replace('    return getter->func(handle->obj, getter->param, data)', '    void *obj = handle->obj;\n    return getter->func(obj, getter->param, data)')
 VS['dl_%d'%n]=[(s,base+'\n'+u)]
