exec(open('docs/drafts/rwa_iface_instance_alloc_trials.py').read())
base=VS['iia_00'][0][1];VS={}
old='def->outputs[i].uniqueID.uuid'
forms=[old,'(def->outputs + i)->uniqueID.uuid','(i + def->outputs)->uniqueID.uuid','i[def->outputs].uniqueID.uuid','(&def->outputs[i])->uniqueID.uuid','((volatile _rwaParamID *)def->outputs)[i].uniqueID.uuid','(*( _rwaParamID *volatile *)&def->outputs)[i].uniqueID.uuid','((RwaUniqueID *)(def->outputs + i))->uuid']
for n,f in enumerate(forms):
 VS['iiu_%02d'%n]=[(production,base.replace(old,f))]
helpers=[
 ('static __forceinline const RwaUUID *interfaceUuid(_rwaParamID *params, RwUInt16 i) { return params[i].uniqueID.uuid; }\n','interfaceUuid(def->outputs, i)'),
 ('static __forceinline const RwaUUID *interfaceUuid(RwUInt16 i, _rwaParamID *params) { return params[i].uniqueID.uuid; }\n','interfaceUuid(i, def->outputs)'),
 ('static __forceinline const RwaUUID *interfaceUuid(RwaObjInterfaceDef *def, RwUInt16 i) { return def->outputs[i].uniqueID.uuid; }\n','interfaceUuid(def, i)'),
 ('static __forceinline const RwaUUID *interfaceUuid(RwUInt16 i, RwaObjInterfaceDef *def) { return def->outputs[i].uniqueID.uuid; }\n','interfaceUuid(i, def)'),
 ('static __forceinline _rwaParamID *interfaceParam(_rwaParamID *params, RwUInt16 i) { return &params[i]; }\n','interfaceParam(def->outputs, i)->uniqueID.uuid'),
 ('static __forceinline _rwaParamID *interfaceParam(RwUInt16 i, _rwaParamID *params) { return &params[i]; }\n','interfaceParam(i, def->outputs)->uniqueID.uuid'),
 ('static __forceinline const RwaUUID *interfaceUuid(RwaUniqueID *id) { return id->uuid; }\n','interfaceUuid(&def->outputs[i].uniqueID)'),
]
for n,(h,f) in enumerate(helpers):
 u=base.replace('// match: _sub_243FF0',h+'\n// match: _sub_243FF0').replace(old,f)
 VS['iiuh_%02d'%n]=[(production,u)]
