exec(open('docs/drafts/rwa_source_setup_shape_trials.py').read());v=VS['setshape_6'][0][1][len(s)+1:];VS={}
for k,field in enumerate(['unk154','unk158','region','unk15C','entry','unk14C']):
 for n in range(2):
  u=v.replace('    state->bufferSize = params->values[10];\n','').replace('    state->'+field+' = 0;', '    state->bufferSize = params->values[10];\n    state->'+field+' = 0;')
  if n:u=u.replace('state->'+field+' = 0;', '*(RwUInt32 *)&state->'+field+' = 0;')
  VS['setpos_%d_%d'%(k,n)]=[(s,s+'\n'+u)]
