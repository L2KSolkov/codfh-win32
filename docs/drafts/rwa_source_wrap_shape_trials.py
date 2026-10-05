exec(open('docs/drafts/rwa_source_wrap_trials.py').read());VS={}
for n in range(16):
 u=d
 if n&1:u=u.replace('    if (!info->noTracks)\n    {\n        return result;\n    }\n\n    chunk', '    if (info->noTracks > 0)\n    {\n    chunk').replace('    return result;\n}', '    }\n    return result;\n}')
 if n&2:u=u.replace('        RwUInt32    size = marker->unk0C[track];', '        RwUInt32 *sizePtr = &marker->unk0C[track];\n        RwUInt32 size = *sizePtr;').replace('largest = size;', 'largest = *sizePtr;')
 if n&4:u=u.replace('    rwaStreamInfo *info = state->info;', '    rwaStreamMarker *marker = state->current;\n    rwaStreamInfo *info = state->info;').replace('    rwaStreamMarker *marker = state->current;\n    RwUInt32   *chunk;', '    RwUInt32 *chunk;')
 if n&8:u=u.replace('RwUInt32   *chunk;', 'RwUInt32 *volatile chunk;').replace('RwUInt32 *chunk;', 'RwUInt32 *volatile chunk;')
 VS['wraps_%d'%n]=[(s,s+'\n'+u)]
