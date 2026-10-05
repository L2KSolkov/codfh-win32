exec(open('docs/drafts/rwa_source_setup_shape_trials.py').read());v=VS['setshape_6'][0][1][len(s)+1:];VS={}
for n in range(8):
 u=v
 if n&1:u=u.replace('    state->bufferSize = params->values[10];\n','').replace('    state->unk154 = 0;', '    state->bufferSize = params->values[10];\n    state->unk154 = 0;')
 if n&2:u=u.replace('params->values[10]', '((volatile rwaStreamSourceParams *)params)->values[10]')
 if n&4:u=u.replace('state->bufferSize =', '((volatile rwaDecoderState *)state)->bufferSize =')
 VS['setload_%d'%n]=[(s,s+'\n'+u)]
