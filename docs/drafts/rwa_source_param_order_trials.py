exec(open('docs/drafts/rwa_source_param_trials.py').read());v=VS['srcparam_5'][0][1];VS={}
import itertools
old='''        arg = (rwaDecoder *)obj->state.items;
        positions = obj->state.positions;
        count = obj->state.noItems;'''
for k,p in enumerate(itertools.permutations(old.splitlines())):
 for n in (0,1,4,5):
  u=v.replace(old,'\n'.join(p))
  if n&1:u=u.replace('    RwUInt32 count;', '    RwUInt32 count = 0;')
  if n&2:u=u.replace('    rwaQueueCallback *callback;', '').replace('        callback = &obj->state.callback;', '        rwaQueueCallback *callback = &obj->state.callback;')
  if n&4:u=u.replace('    RwUInt32 i;', '').replace('        for (i = 0;', '        { RwUInt32 i;\n        for (i = 0;').replace('        sub_2472E0(', '        }\n        sub_2472E0(')
  VS['srco_%d_%d'%(k,n)]=[(s,u)]
