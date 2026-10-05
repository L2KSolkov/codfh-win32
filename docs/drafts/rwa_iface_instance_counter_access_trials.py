exec(open('docs/drafts/rwa_iface_instance_index_trials.py').read())
base=VS['iiidx_03'][0][1];VS={}
for n in range(8):
 u=base
 if n&1:u=u.replace('def->outputs[k].uniqueID.uuid', '(*(_rwaParamID *volatile *)&def->outputs)[k].uniqueID.uuid')
 if n&2:u=u.replace('tables->outputs[j].uuid', '(*(rwaParamDef *volatile *)&tables->outputs)[j].uuid')
 if n&4:u=u.replace('tables->outputs[j].handler', '(*(rwaParamDef *volatile *)&tables->outputs)[j].handler')
 VS['iicacc_%02d'%n]=[(production,u)]
