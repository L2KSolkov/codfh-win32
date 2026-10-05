exec(open('docs/drafts/rwa_source_callback_trials.py').read());VS={}
a=d.index('        if (status != 4)');b=d.index('    if (state->flags & 0x40)',a);block=d[a:b];start=block.index('{')+1;end=block.index('        if (state->notify)');success=block[start:block.rfind('        }',0,end)];failure=block[end:block.rfind('    }')]
for n in range(8):
 u=d[:a]+'        if (status == 4)\n        {\n'+failure+'        }\n'+success+'    }\n\n'+d[b:]
 if n&1:u=u.replace('state->regions[state->region].flags |= 4;', '((volatile rwaStreamRegion *)state->regions)[state->region].flags |= 4;')
 if n&2:u=u.replace('        RwUInt32    chunkSize = state->info->unk20;\n\n        state->flags &= ~8;', '        RwUInt32 chunkSize;\n        state->flags &= ~8;\n        chunkSize = state->info->unk20;')
 if n&4:u=u.replace('for (; bytes; bytes -= chunkSize)', 'for (; bytes > 0; bytes -= chunkSize)')
 VS['cbshape_%d'%n]=[(s,s+'\n'+prefix+u)]
