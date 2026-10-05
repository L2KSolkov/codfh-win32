exec(open('docs/drafts/rwa_source_setup_shape_trials.py').read());v=VS['setshape_6'][0][1][len(s)+1:];VS={}
a=v.index('    state->unk154 = 0;');ends=['    state->bufferSize = params->values[10];','    state->unk14C = 0;','    state->regions = NULL;','    state->unk174 = 0;','    state->loops = 0;']
for k,end in enumerate(ends):
 b=v.index(end,a)+len(end);chunk=v[a:b].replace('params->values[10]', 'bufferSize')
 for n in range(2):
  h='static __forceinline void setupRing('+('RwUInt32 bufferSize, rwaDecoderState *state' if n else 'rwaDecoderState *state, RwUInt32 bufferSize')+') {\n'+chunk+'\n}\n'
  u=h+v[:a]+'    setupRing('+('params->values[10], state' if n else 'state, params->values[10]')+');'+v[b:]
  VS['sethelp_%d_%d'%(k,n)]=[(s,s+'\n'+u)]
