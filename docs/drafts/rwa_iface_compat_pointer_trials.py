exec(open('docs/drafts/rwa_iface_compat_access_trials.py').read())
base=VS['ica_04'][0][1];VS={}
old='def->inputs[k].uniqueID.uuid'
forms=[
 '(def->inputs+k)->uniqueID.uuid',
 '(k+def->inputs)->uniqueID.uuid',
 'k[def->inputs].uniqueID.uuid',
 '((const _rwaParamID *)def->inputs)[k].uniqueID.uuid',
]
for n,f in enumerate(forms):VS['icp_%02d'%n]=[(production,base.replace(old,f))]
for n in range(4):
 u=base
 if n<2:
  u=u.replace('            if (!RwaUUIDCompare(tables->inputs[j].uuid, '+old+'))', '            '+('const ' if n==1 else '')+'_rwaParamID *input = def->inputs;\n            if (!RwaUUIDCompare(tables->inputs[j].uuid, input[k].uniqueID.uuid))')
 else:
  h='static __forceinline _rwaParamID *getInterfaceInputs(RwaObjInterfaceDef *def) { return def->inputs; }\n'
  if n==3:h=h.replace('return def->inputs;', '_rwaParamID *params = def->inputs; return params;')
  u=u.replace('// match: _sub_243BC0',h+'\n// match: _sub_243BC0').replace(old,'getInterfaceInputs(def)[k].uniqueID.uuid')
 VS['icpl_%02d'%n]=[(production,u)]
