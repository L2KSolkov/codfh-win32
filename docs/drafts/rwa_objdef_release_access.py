exec(open('docs/drafts/rwa_objdef_loop_trials.py').read())
base=VS['ol_3'][0][1];VS={}
for n in range(8):
 u=base
 if n&1:u=u.replace('param = tables->inputs;', 'param = *(rwaParamDef *volatile *)&tables->inputs;')
 if n&2:u=u.replace('param = tables->outputs;', 'param = *(rwaParamDef *volatile *)&tables->outputs;')
 if n&4:u=u.replace('RwUInt16 count = tables->noInputs;', 'RwUInt16 count = *(volatile RwUInt16 *)&tables->noInputs;').replace('RwUInt16 count = tables->noOutputs;', 'RwUInt16 count = *(volatile RwUInt16 *)&tables->noOutputs;')
 VS['objrelaccess_%d'%n]=[(s,u)]
