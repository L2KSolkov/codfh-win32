exec(open('docs/drafts/rwa_source_read_control_trials.py').read());base=VS['rdctrl_13'][0][1][len(s+'\n'+prefix):];VS={}
a=base.index('        if (state->unkF8)');b=base.index('        ReleaseSemaphore(state->semaphore, 1, NULL);\n        if (!(state->flags',a);c=base.index('        WaitForSingleObject(state->semaphore, 0xFFFFFFFF);',b)+len('        WaitForSingleObject(state->semaphore, 0xFFFFFFFF);');read=base[a:b];empty=base[b:c];read=read[read.index('{')+1:read.rfind('}')]
for n in range(8):
 u=base[:a]+'        if (!state->unkF8)\n        {\n'+empty+'\n            continue;\n        }\n        {\n'+read+'        }\n'+base[c:]
 if n&1:u=u.replace('rwaStreamRegion *region = &state->regions[state->unk14C];','rwaStreamRegion *region = &((volatile rwaDecoderState *)state)->regions[state->unk14C];')
 if n&2:u=u.replace('            RwInt32     result = 1;', '            RwUInt32 result = 1;')
 if n&4:u=u.replace('            read = 0;\n            rest = bytes - first;', '            rest = bytes - first;\n            read = 0;')
 VS['rdouter_%d'%n]=[(s,s+'\n'+prefix+u)]
