exec(open('docs/drafts/rwa_source_setup_shape_trials.py').read());v=VS['setshape_6'][0][1][len(s)+1:];VS={}
for n,name in enumerate(['ext','c']):
 u=v.replace('    state->unk154 = 0;', '    '+name+' = ('+('const RwChar *' if name=='ext' else 'RwChar *')+')params->values[10];\n    state->unk154 = 0;').replace('state->bufferSize = params->values[10];', 'state->bufferSize = (RwUInt32)'+name+';')
 VS['setreuse_%d'%n]=[(s,s+'\n'+u)]
