"""Parked default-instancer experiments; no exact candidate.
Target __rpXboxDefaultInstance 0x2DED60 in xbvtxfmt.c. See questions.md.
"""
exec(open('docs/drafts/rw_default_position_block_trials.py').read())
VS={}
for extent,marker in enumerate(['    if (packedNormals)','    if (color)','    for (i = 0; i < numTexCoordSets; i++)']):
 a=body.index('    if (positions)');b=body.index(marker,a);chunk=body[a:b]
 names=['positions','normals','packedNormals','color','lockedSinceLastInst','fmt','lockedVertexBuffer','numVertices','instancedHeader']
 types=['const RwV3d *positions','const RwV3d *normals','const RpVertexNormal *packedNormals','const RwRGBA *color','RwUInt32 lockedSinceLastInst','const RpXboxVtxFmt *fmt','RwUInt8 *lockedVertexBuffer','RwInt32 numVertices','RxXboxResEntryHeader *instancedHeader']
 if extent==0:
  names=names[:2]+names[4:];types=types[:2]+types[4:]
 elif extent==1:
  names=names[:3]+names[4:];types=types[:3]+types[4:]
 for mode in range(2):
  for k in range(len(names)*2):
   order=list(range(len(names)));order=order[k%len(names):]+order[:k%len(names)]
   if k>=len(names):order.reverse()
   ts=types[:];ns=names[:];c=chunk;tail='return lockedVertexBuffer;';ret='RwUInt8 *'
   if mode:
    j=names.index('lockedVertexBuffer');ts[j]='RwUInt8 **buffer';ns[j]='&lockedVertexBuffer';c=c.replace('lockedVertexBuffer','(*buffer)');tail='';ret='void'
   h='static __forceinline '+ret+' AttributeBlockTrial('+', '.join(ts[i] for i in order)+') { RwUInt32 size;\n'+c+tail+' }\n'
   call='    '+('lockedVertexBuffer = ' if not mode else '')+'AttributeBlockTrial('+', '.join(ns[i] for i in order)+');\n'
   VS['ab_%d_%d_%d'%(extent,mode,k)]=[(anchor,h+body[:a]+call+body[b:]+anchor)]
