from pathlib import Path
s=Path('src/rwa/unit_247430.c').read_text();d=Path('docs/drafts/rwa_source_setup_followup.c').read_text();VS={}
for n in range(8):
 u=d.replace('    state->unk154 = 0;', '    { RwUInt32 bufferSize = params->values[10];\n    state->unk154 = 0;').replace('    state->bufferSize = params->values[10];', '    state->bufferSize = bufferSize;\n    }')
 if n&1:u=u.replace('state->noEntries = params->values[12];', 'state->noEntries = ((volatile rwaStreamSourceParams *)params)->values[12];')
 if n&2:u=u.replace('    state->bufferSize = bufferSize;\n    }', '    state->bufferSize = bufferSize;').replace('    state->loops = 0;', '    state->loops = 0;\n    }')
 if n&4:u=u.replace('state->noEntries =', '((volatile rwaDecoderState *)state)->noEntries =')
 VS['setscope_%d'%n]=[(s,s+'\n'+u)]
