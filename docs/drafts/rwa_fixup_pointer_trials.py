exec(open('docs/drafts/rwa_fixup_scope_trials.py').read());b=VS['fs_016'][0][1][len(s)+1:];VS={}
for n in range(8):
 u=b
 if n&1:u=u.replace('        rwaStreamTrack *track = &info->tracks[i];\n\n        if (track->format)\n        {\n            track->format = (rwaStreamFormat *)cursor;', '        rwaStreamFormat **entryFormat = &info->tracks[i].format;\n\n        if (*entryFormat)\n        {\n            *entryFormat = (rwaStreamFormat *)cursor;')
 if n&2:u=u.replace('        if (marker->name)', '        if (((volatile rwaStreamMarker *)marker)->name)')
 if n&4:u=u.replace('    RwUInt32    j;','').replace('        for (j = 0; j < marker->noCues; j++)', '        { RwUInt32 j;\n        for (j = 0; j < marker->noCues; j++)').replace('                cursor += sizeof(RwaUUID);\n            }\n        }','                cursor += sizeof(RwaUUID);\n            }\n        }\n        }').replace('                cursor += rwaNameSize((const RwChar *)cursor);\n            }\n        }','                cursor += rwaNameSize((const RwChar *)cursor);\n            }\n        }\n        }')
 VS['fp_%d'%n]=[(s,s+'\n'+u)]
