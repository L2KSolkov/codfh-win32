exec(open('docs/drafts/rwa_chunk_trials.py').read());VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('    rwaStreamInfo *info = state->info;', '    rwaStreamMarker *marker = state->current;\n    rwaStreamInfo *info = state->info;').replace('    rwaStreamMarker *marker = state->current;\n    RwUInt32   *chunk;', '    RwUInt32   *chunk;')
 if n&2:u=u.replace('    if (!info->noTracks)\n    {\n        return result;\n    }\n\n','').replace('    do\n    {\n        RwUInt32    size = marker', '    for (; track < state->info->noTracks; )\n    {\n        RwUInt32    size = marker').replace('    while (track < state->info->noTracks);','')
 if n&4:u=u.replace('            RwUInt32    high;\n            RwUInt32    count;', '            RwUInt32    count;\n            RwUInt32    high;')
 VS['cf_%d'%n]=[(s,base+'\n'+u)]
