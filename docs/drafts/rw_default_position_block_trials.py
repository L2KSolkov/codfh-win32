"""Parked default-instance probes. pscore target: __rpXboxDefaultInstance
0x2DED60 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. No candidate matches.
"""
exec(open('docs/drafts/rw_default_instance_trials.py').read())
VS={'dp_base':[(anchor,body+anchor)]}
names=['positions','lockedSinceLastInst','fmt','lockedVertexBuffer','numVertices','instancedHeader']
types=['const RwV3d *positions','RwUInt32 lockedSinceLastInst','const RpXboxVtxFmt *fmt','RwUInt8 *lockedVertexBuffer','RwInt32 numVertices','RxXboxResEntryHeader *instancedHeader']
a=body.index('    if (positions)');b=body.index('    if (normals)',a)
chunk=body[a:b]
for mode in range(3):
 for k in range(12):
  order=list(range(6));order=order[k%6:]+order[:k%6]
  if k>=6:order.reverse()
  c=chunk
  if mode==1:c=c.replace('lockedVertexBuffer += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);','if (fmt->pos == rpNORMALIZEDPACKED) return lockedVertexBuffer + 4;\n            return lockedVertexBuffer + RpXboxCompSize[fmt->pos] * 3;')
  if mode==2:c=c.replace('lockedVertexBuffer += _rpXboxVtxFmtInstV3d','return lockedVertexBuffer + _rpXboxVtxFmtInstV3d').replace('lockedVertexBuffer += _rpXboxVtxFmtGetSize','return lockedVertexBuffer + _rpXboxVtxFmtGetSize')
  h='static __forceinline RwUInt8 *PositionTrial('+', '.join(types[i] for i in order)+') {\n'+c+'    return lockedVertexBuffer;\n}\n'
  call='    lockedVertexBuffer = PositionTrial('+', '.join(names[i] for i in order)+');\n'
  VS['dp_%d_%02d'%(mode,k)]=[(anchor,h+body[:a]+call+body[b:]+anchor)]
