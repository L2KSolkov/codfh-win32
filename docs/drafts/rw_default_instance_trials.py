"""Parked default-instance probes. pscore target: __rpXboxDefaultInstance
0x2DED60 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. No candidate matches.
"""
from pathlib import Path
d=Path('docs/drafts/rw_xbvtxfmt_definst_draft.c').read_text()
a=d.index('// match: __rpXboxDefaultInstance');b=d.index('// match: _rxXboxVtxFmtGeometryRead',a)
body=d[a:b]
anchor='// match: _rxXboxVtxFmtGeometryRead @ 0x002DF000'
VS={'di_base':[(anchor,body+anchor)]}
old='lockedVertexBuffer += _rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos, 3);'
exprs=[
'if (fmt->pos == rpNORMALIZEDPACKED) { lockedVertexBuffer += 4; } else { lockedVertexBuffer += RpXboxCompSize[fmt->pos] * 3; }',
'if (fmt->pos != rpNORMALIZEDPACKED) { lockedVertexBuffer += RpXboxCompSize[fmt->pos] * 3; } else { lockedVertexBuffer += 4; }',
'switch (fmt->pos) { case rpNORMALIZEDPACKED: lockedVertexBuffer += 4; break; default: lockedVertexBuffer += RpXboxCompSize[fmt->pos] * 3; break; }',
'lockedVertexBuffer = (fmt->pos == rpNORMALIZEDPACKED) ? lockedVertexBuffer + 4 : lockedVertexBuffer + RpXboxCompSize[fmt->pos] * 3;',
]
for i,expr in enumerate(exprs):VS['di_expr%d'%i]=[(anchor,body.replace(old,expr)+anchor)]
for typ in ['RwUInt8','RwUInt32','RpXboxCompType']:
 for place in range(3):
  t=body
  if place==0:t=t.replace('    RwInt32             i;', '    RwInt32 i;\n    '+typ+' posType;').replace('    if (positions)\n    {','    if (positions)\n    {\n        posType = ('+typ+')fmt->pos;')
  if place==1:t=t.replace('    if (positions)\n    {','    if (positions)\n    {\n        '+typ+' posType = ('+typ+')fmt->pos;')
  if place==2:t=t.replace(old,typ+' posType = ('+typ+')fmt->pos;\n            '+old)
  first=t.index('    if (positions)');last=t.index('    if (normals)',first)
  area=t[first:last]
  area=area.replace('(RpXboxCompType)fmt->pos','(RpXboxCompType)posType') if typ!='RpXboxCompType' else area
  if typ=='RpXboxCompType':area=area.replace(old,'lockedVertexBuffer += _rpXboxVtxFmtGetSize(posType, 3);')
  if place==2:area=area.replace('_rpXboxVtxFmtInstV3d((RpXboxCompType)posType','_rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos')
  t=t[:first]+area+t[last:]
  VS['di_local_'+typ+str(place)]=[(anchor,t+anchor)]
