exec(open('docs/drafts/rwa_iface_instance_alloc_trials.py').read())
base=VS['iia_00'][0][1];VS={}
at=base.index('    n = ((rwaParamTables *)objDef->interfaces)->noOutputs;',base.index('// match: _sub_243FF0'))
end=base.index('    objInterface->link.next =',at)
out=base[at:end]
for n in range(10):
 u=out
 if n==0:u=u.replace('outputs[i]', 'outputs[(RwUInt32)i]')
 if n==1:u=u.replace('outputs[i]', 'outputs[(RwInt32)i]')
 if n==2:u=u.replace('outputs[i]', 'outputs[(i)]')
 if n in(3,4,5):
  u='{ '+('RwUInt16' if n!=5 else 'RwUInt32')+' k;\n'+u.replace('for (i = 0; i < count; i++)', 'for (k = 0; k < count; k++)').replace('outputs[i]', 'outputs[k]').replace('getters[i]', 'getters[k]')+'}\n'
  if n==4:u=u.replace('for (k = 0; k < count; k++)', 'k=0;\n    while(k<count)').replace('    }\n\n}', '        ++k;\n    }\n\n}')
 if n==6:u=u.replace('for (i = 0; i < count; i++)','for (i = 0; i != count; i++)')
 if n==7:u=u.replace('def->outputs[i].uniqueID.uuid', '((const _rwaParamID *)def->outputs)[i].uniqueID.uuid')
 if n==8:u=u.replace('def->outputs[i].uniqueID.uuid', '*(&def->outputs[i].uniqueID.uuid)')
 if n==9:u=u.replace('RwUInt16    j;', 'RwUInt16    j;\n        const RwaUUID *uuid;').replace('if (!RwaUUIDCompare(tables->outputs[j].uuid, def->outputs[i].uniqueID.uuid))','if (!(uuid = def->outputs[i].uniqueID.uuid, RwaUUIDCompare(tables->outputs[j].uuid, uuid)))')
 VS['iiidx_%02d'%n]=[(production,base[:at]+u+base[end:])]
call='RwaUUIDCompare(tables->outputs[j].uuid, def->outputs[i].uniqueID.uuid)'
forms=[
 ('const rwaParamDef *param, const _rwaParamID *id','tables->outputs+j, def->outputs+i','param->uuid, id->uniqueID.uuid'),
 ('const _rwaParamID *id, const rwaParamDef *param','def->outputs+i, tables->outputs+j','param->uuid, id->uniqueID.uuid'),
 ('const RwaUUID *uuid, const _rwaParamID *ids, RwUInt16 i','tables->outputs[j].uuid, def->outputs, i','uuid, ids[i].uniqueID.uuid'),
 ('const _rwaParamID *ids, RwUInt16 i, const RwaUUID *uuid','def->outputs, i, tables->outputs[j].uuid','uuid, ids[i].uniqueID.uuid'),
 ('RwUInt16 i, const _rwaParamID *ids, const RwaUUID *uuid','i, def->outputs, tables->outputs[j].uuid','uuid, ids[i].uniqueID.uuid'),
]
for n,(args,values,comparison) in enumerate(forms):
 h='static __forceinline RwInt32 compareInterfaceParameter('+args+') { return RwaUUIDCompare('+comparison+'); }\n'
 u=base.replace('// match: _sub_243FF0',h+'\n// match: _sub_243FF0').replace(call,'compareInterfaceParameter('+values+')')
 VS['iicmp_%02d'%n]=[(production,u)]
