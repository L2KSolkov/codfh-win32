exec(open('docs/drafts/rwa_source_setup_trials.py').read());VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('    RwChar     *c;', '    RwChar *c;\n    RwUInt32 bufferSize;').replace('    state->unk154 = 0;', '    bufferSize = params->values[10];\n    state->unk154 = 0;').replace('state->bufferSize = params->values[10];','state->bufferSize = bufferSize;')
 if n&2:u=u.replace('state->buffer = (RwUInt8 *)params->values[11];','((volatile rwaDecoderState *)state)->buffer = (RwUInt8 *)params->values[11];')
 if n&4:u=u.replace('    if (params->values[5] != 1)\n    {\n        return FALSE;\n    }','    switch (params->values[5]) { case 1: break; default: return FALSE; }')
 VS['setshape_%d'%n]=[(s,s+'\n'+u)]
