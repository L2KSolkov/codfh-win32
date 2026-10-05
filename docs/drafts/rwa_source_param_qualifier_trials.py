exec(open('docs/drafts/rwa_source_param_trials.py').read());v=VS['srcparam_5'][0][1];VS={}
for n in range(16):
 u=v
 if n&1:u=u.replace('arg = (rwaDecoder *)obj->state.items;', '*(rwaDecoder *volatile *)&arg = (rwaDecoder *)obj->state.items;')
 if n&2:u=u.replace('count = obj->state.noItems;', 'count = ((volatile rwaDecoder *)obj)->state.noItems;')
 if n&4:u=u.replace('arg = (rwaDecoder *)obj->state.items;', 'arg = (rwaDecoder *)((volatile rwaDecoder *)obj)->state.items;')
 if n&8:u=u.replace('        positions = obj->state.positions;', '        positions = ((volatile rwaDecoder *)obj)->state.positions;')
 VS['srcq_%d'%n]=[(s,u)]
