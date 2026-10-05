exec(open('docs/drafts/rwa_source_setup_load_trials.py').read());v=VS['setload_1'][0][1][len(s)+1:];VS={}
for mask in range(32):
 u=v
 for j,field in enumerate(['unk154','unk158','region','unk15C','entry']):
  if mask&(1<<j):u=u.replace('state->'+field+' = 0;', '*(RwUInt32 *)&state->'+field+' = 0;')
 VS['setvol_%d'%mask]=[(s,s+'\n'+u)]
