from pathlib import Path
s=Path('src/rwa/unit_247430.c').read_text();d=Path('docs/drafts/rwa_source_setup_followup.c').read_text();VS={}
for n in range(4):
 name='params' if not n&1 else 'state';ty='rwaStreamSourceParams' if not n&1 else 'rwaDecoderState'
 u=d.replace(ty+' *'+name+')',ty+' *arg)').replace(ty+' *'+name+',',ty+' *arg,').replace('    const RwChar *ext;', '    '+ty+' *'+name+' = arg;\n    const RwChar *ext;').replace('    state->unk154 = 0;', '    arg = ('+ty+' *)params->values[10];\n    state->unk154 = 0;').replace('state->bufferSize = params->values[10];', 'state->bufferSize = (RwUInt32)arg;')
 if n&2:u=u.replace('    state->unk154 = 0;', '    state->unk154 = 0;').replace('((volatile rwaDecoderState *)state)->buffer','state->buffer')
 VS['setarg_%d'%n]=[(s,s+'\n'+u)]
