exec(open('docs/drafts/rwa_source_read_control_trials.py').read());u=VS['rdctrl_13'][0][1][len(s+'\n'+prefix):];u=u[:u.rfind('\n}')+3];VS={}
a=u.index('        if (state->unkF8)');b=u.index('        ReleaseSemaphore(state->semaphore, 1, NULL);\n        if (!(state->flags',a);body=u[a:b];chunk=body[body.index('{')+1:body.rfind('}')]
u=u[:a]+'        if (state->unkF8) goto chunks;\n'+u[b:];u=u.replace('{\n    WaitForSingleObject','{\n    RwUInt32 chunkSize;\n    WaitForSingleObject',1).replace('        RwUInt32    chunkSize = state->info->unk20;', '').replace('        if (state->unk14C ==','        chunkSize = state->info->unk20;\n        if (state->unk14C ==',1)
# free must survive into the moved read block.
u=u.replace('    RwUInt32 chunkSize;', '    RwUInt32 chunkSize;\n    RwUInt32 free;').replace('        RwUInt32    free;','')
u=u.rstrip()[:-1]+'\nchunks:\n    {\n'+chunk+'    }\n}\n'
for n in range(4):
 v=u
 if n&1:v=v.replace('if (!last)', 'if (last <= 0)')
 if n&2:v=v.replace('read = 0;\n            rest = bytes - first;', 'rest = bytes - first;\n            read = 0;')
 VS['rdmove_%d'%n]=[(s,s+'\n'+prefix+v)]
