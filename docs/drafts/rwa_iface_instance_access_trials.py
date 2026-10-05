exec(open('docs/drafts/rwa_iface_instance_index_trials.py').read())
best0=VS['iiidx_00'][0][1]
best1=VS['iiidx_03'][0][1]
VS={}
for k,base in enumerate((best0,best1)):
 for n in range(8):
  u=base
  if n&1:u=u.replace('tables->outputs[j].uuid', '(*(rwaParamDef *volatile *)&tables->outputs)[j].uuid')
  if n&2:u=u.replace('tables->outputs[j].handler', '(*(rwaParamDef *volatile *)&tables->outputs)[j].handler')
  if n&4:u=u.replace('RwUInt16    j;\n\n        for (j = 0; j < n; j++)', 'RwUInt32    j;\n\n        for (j = 0; j < n; j++)')
  VS['iiacc_%d_%d'%(k,n)]=[(production,u)]
