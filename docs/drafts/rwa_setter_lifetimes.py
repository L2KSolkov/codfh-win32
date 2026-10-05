from pathlib import Path
import itertools
s=Path('src/rwa/rwaobject.c').read_text()
base=s
if '// match: _Behavior_DispatchCallback' in base:
 start=base.index('// match: _Behavior_DispatchCallback')
 end=base.index('// match: _sub_23F8E0', start)
 base=base[:start]+base[end:]
d=Path('docs/drafts/rwa_object_dispatch_draft.c').read_text().split('// match: _sub_23F8E0')[0]
VS={}
for k,p in enumerate(itertools.permutations(['obj','setter','value'])):
 for n in range(4):
  decl={'obj':'rwaInstance *obj = handle->obj;', 'setter':'rwaParamFunc *setter = &handle->objInterface->setters[index];', 'value':'void *value = data;'}
  body='\n'.join(decl[x] for x in p)
  if n&1:body+='\nRwUInt32 param = setter->param;'
  body+='\nreturn setter->func(obj, '+('param' if n&1 else 'setter->param')+', value) ? handle : NULL;'
  u=d[:d.index('{')+1]+'\n'+body+'\n}\n'
  if n&2:u=u.replace('void *data)', 'void *volatile data)')
  VS['setlife_%d_%d'%(k,n)]=[(s,base+'\n'+u)]
