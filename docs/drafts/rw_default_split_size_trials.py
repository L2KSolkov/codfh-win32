"""Default-instance probes: __rpXboxDefaultInstance 0x2DED60, xbvtxfmt.c. Best remains 15. No exact match.
Run through tools/session/pscore.py against the corresponding production unit.
"""
exec(open('docs/drafts/rw_default_instance_trials.py').read())
VS={'ds_base':[(anchor,body+anchor)]}
packed=['lockedVertexBuffer += 4;', 'lockedVertexBuffer += fmt->pos;', 'lockedVertexBuffer = (RwUInt8 *)((RwUInt32)lockedVertexBuffer + 4);', 'lockedVertexBuffer = (RwUInt8 *)((RwUInt32 *)lockedVertexBuffer + 1);']
unpacked=['lockedVertexBuffer += RpXboxCompSize[fmt->pos] * 3;', 'lockedVertexBuffer = (RwUInt8 *)((RwUInt32)lockedVertexBuffer + RpXboxCompSize[fmt->pos] * 3);', 'lockedVertexBuffer += RpXboxCompSize[fmt->pos]; lockedVertexBuffer += 2 * RpXboxCompSize[fmt->pos];', 'lockedVertexBuffer += ((const volatile RwUInt32 *)RpXboxCompSize)[fmt->pos] * 3;', 'RwUInt32 size = RpXboxCompSize[fmt->pos]; lockedVertexBuffer += size + size + size;']
for a,p in enumerate(packed):
 for b,q in enumerate(unpacked):
  for c in range(4):
   expr='if (fmt->pos == rpNORMALIZEDPACKED) { '+p+' } else { '+q+' }'
   if c==1:expr='if (fmt->pos != rpNORMALIZEDPACKED) { '+q+' } else { '+p+' }'
   if c==2:expr='do { if (fmt->pos == rpNORMALIZEDPACKED) { '+p+' break; } '+q+' } while (0);'
   if c==3:expr='switch (fmt->pos) { case rpNORMALIZEDPACKED: '+p+' break; default: { '+q+' } break; }'
   VS['ds_%d_%d_%d'%(a,b,c)]=[(anchor,body.replace(old,expr)+anchor)]
