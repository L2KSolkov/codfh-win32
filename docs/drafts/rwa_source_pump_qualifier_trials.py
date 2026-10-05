exec(open('docs/drafts/rwa_source_pump_trials.py').read());VS={}
for n in range(16):
 u=f
 if n&1:u=u.replace('state->unk174].unk0C', '((volatile rwaDecoderState *)state)->unk174].unk0C')
 if n&2:u=u.replace('entries[state->unk174].flags', '((volatile rwaStreamRegion *)entries)[state->unk174].flags')
 if n&4:u=u.replace('regions[state->unk154].flags', '((volatile rwaStreamRegion *)regions)[state->unk154].flags')
 if n&8:u=u.replace('regions[state->unk154].unk0C', '((volatile rwaStreamRegion *)regions)[state->unk154].unk0C')
 VS['srpq_%d'%n]=[(s,base+'\n'+prefix+h+u)]
