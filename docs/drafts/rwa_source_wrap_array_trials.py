exec(open('docs/drafts/rwa_source_wrap_shape_trials.py').read());v=VS['wraps_5'][0][1][len(s)+1:];VS={}
for n in range(4):
 u=v.replace('RwUInt32    unit = *chunk;', 'RwUInt32 unit = info->tracks[track].unk20;').replace('    chunk = &info->tracks[0].unk20;', '').replace('        chunk += sizeof(rwaStreamTrack) / sizeof(RwUInt32);','')
 if n&1:u=u.replace('info->tracks[track].unk20', 'state->info->tracks[track].unk20')
 if n&2:u=u.replace('RwUInt32    size = marker->unk0C[track];', 'RwUInt32 *sizePtr = &marker->unk0C[track];\n        RwUInt32 size = *sizePtr;').replace('largest = size;', 'largest = *sizePtr;')
 VS['wrapa_%d'%n]=[(s,s+'\n'+u)]
