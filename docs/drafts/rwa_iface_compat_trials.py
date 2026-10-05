exec(open('docs/drafts/rwa_iface_trials.py').read());VS={}
for n in range(8):
 u=d[:d.index('// match: _sub_243E20')]
 if n&1:
  a=u.index('    count = def->noOutputs;');b=len(u);u=u[:a]+u[a:b].replace('for (i = 0; i < count; i++)','{ RwUInt32 k;\n    for (k = 0; k < count; k++)').replace('outputs[i]', 'outputs[k]').replace('    return compatible', '    }\n    return compatible')+u[b:]
 if n&2:u=u.replace('RwUInt32        j;', 'RwUInt32        j;\n    const RwaUUID *uuid;').replace('if (!RwaUUIDCompare(tables->inputs[j].uuid, def->inputs[i].uniqueID.uuid))','if (!(uuid = tables->inputs[j].uuid, RwaUUIDCompare(uuid, def->inputs[i].uniqueID.uuid)))').replace('if (!RwaUUIDCompare(tables->outputs[j].uuid, def->outputs[i].uniqueID.uuid))','if (!(uuid = tables->outputs[j].uuid, RwaUUIDCompare(uuid, def->outputs[i].uniqueID.uuid)))')
 if n&4:u=u.replace('RwUInt32        j;', 'RwInt32         j;')
 VS['ib_%d'%n]=[(s,s+'\n'+u)]

