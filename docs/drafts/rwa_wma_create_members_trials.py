exec(open('docs/drafts/rwa_wma_create_current_trials.py').read())
VS={}
for n in range(32):
 u=d
 if n&1:u=u.replace('state->packetSize = params->lookahead', '((volatile rwaWmaState *)state)->packetSize = params->lookahead')
 if n&2:u=u.replace('    state->callback.func =','    ((volatile rwaWmaState *)state)->callback.func =').replace('    state->callback.data =','    ((volatile rwaWmaState *)state)->callback.data =')
 if n&4:u=u.replace('state->noPackets;', '((volatile rwaWmaState *)state)->noPackets;')
 if n&8:
  u=u.replace('    desc.title = title;','    ((volatile rwaWmaContentDesc *)&desc)->title = title;').replace('    desc.description = description;','    ((volatile rwaWmaContentDesc *)&desc)->description = description;')
 if n&16:
  u=u.replace('    sub_24DA10(&state->track);','    {\n    rwaStreamTrack *track = &state->track;\n    sub_24DA10(track);')
  pos=u.index('    sub_24DA10(track);')
  u=u[:pos]+u[pos:].replace('state->track.', 'track->').replace('&state->track,', 'track,').replace('&state->track;', 'track;')
  u=u.replace('    RwaStreamNodeCreationComplete', '    }\n    RwaStreamNodeCreationComplete')
 VS['wmcm_%02d'%n]=[(anchor,u+anchor)]
