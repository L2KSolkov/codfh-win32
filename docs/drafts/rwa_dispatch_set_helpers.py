from pathlib import Path
import itertools
s=Path('src/rwa/rwaobject.c').read_text();d=Path('docs/drafts/rwa_object_dispatch_draft.c').read_text().split('// match: _sub_23F8E0')[0];VS={}
args={'handle':'RwaObjHandle *handle','setter':'rwaParamFunc *setter','data':'void *data'}
for k,p in enumerate(itertools.permutations(args)):
 for n in range(8):
  body='return setter->func(handle->obj, setter->param, data) ? handle : NULL;'
  if n&1:body=body.replace('return ', 'RwUInt32 param = setter->param; return ').replace('setter->param, data','param, data')
  helper='static __forceinline RwaObjHandle *dispatchSet('+', '.join(args[x] for x in p)+') { '+body+' }\n'
  u=d.replace('return setter->func(handle->obj, setter->param, data) ? handle : NULL;', 'return dispatchSet('+', '.join(p)+');')
  if n&2:u=u.replace('    rwaParamFunc   *setter', '    void *value = data;\n    rwaParamFunc   *setter').replace('dispatchSet('+', '.join(p)+')','dispatchSet('+', '.join('value' if x=='data' else x for x in p)+')')
  if n&4:helper=helper.replace('RwaObjHandle *dispatchSet','RwBool dispatchSet').replace(' ? handle : NULL','');u=u.replace(');\n}', ') ? handle : NULL;\n}')
  VS['dsh_%d_%d'%(k,n)]=[(s,s+'\n'+helper+u)]
