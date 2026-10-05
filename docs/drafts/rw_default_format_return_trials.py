"""Default-instance probes: __rpXboxDefaultInstance 0x2DED60, xbvtxfmt.c. Best remains 15. No exact match.
Run through tools/session/pscore.py against the corresponding production unit.
"""
exec(open('docs/drafts/rw_default_position_block_trials.py').read())
VS={}
for scope in range(2):
 for mode in range(3):
  for k in range(12):
   order=list(range(6));order=order[k%6:]+order[:k%6]
   if k>=6:order.reverse()
   ts=types[:];ts[2]='RpXboxVtxFmt *fmt';ts[3]='RwUInt8 **buffer'
   ns=names[:];ns[3]='&lockedVertexBuffer'
   c=chunk if not scope else '    '+old+'\n'
   c=c.replace('lockedVertexBuffer','(*buffer)')
   if mode==1:c=c.replace('_rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3)','(fmt->pos == rpNORMALIZEDPACKED ? 4 : RpXboxCompSize[fmt->pos] * 3)')
   if mode==2:c=c.replace('(*buffer) += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);','if (fmt->pos == rpNORMALIZEDPACKED) { (*buffer) += 4; return fmt; } (*buffer) += RpXboxCompSize[fmt->pos] * 3;')
   h='static __forceinline RpXboxVtxFmt *PositionFormatTrial('+', '.join(ts[i] for i in order)+') {\n'+c+' return fmt; }\n'
   call='fmt = PositionFormatTrial('+', '.join(ns[i] for i in order)+');'
   t=body[:a]+call+body[b:] if not scope else body.replace(old,call)
   VS['df_%d_%d_%02d'%(scope,mode,k)]=[(anchor,h+t+anchor)]
