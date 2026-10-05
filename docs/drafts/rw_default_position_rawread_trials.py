"""Default-instancer format-access probes. No exact match.
Target __rpXboxDefaultInstance 0x2DED60, xbvtxfmt.c. See questions.md.
"""
exec(open('docs/drafts/rw_default_instance_trials.py').read())
VS={};a=body.index('    if (positions)');b=body.index('    if (normals)',a);chunk=body[a:b]
forms=['(*(const RwUInt8 *)fmt & 0xF)','(((const RwUInt8 *)fmt)[0] & 15)','(*(const RwUInt32 *)fmt & 15)','((RwUInt8)*(const RwUInt32 *)fmt & 15)','(((const RwUInt8 *)fmt)[0] % 16)','((RwUInt32)((const RwUInt8 *)fmt)[0] & 15)']
for k,expr in enumerate(forms):
 for scope in range(3):
  c=chunk
  if scope==0:c=c.replace('fmt->pos',expr)
  if scope==1:c=c.replace('_rpXboxVtxFmtGetSize((RpXboxCompType)fmt->pos','_rpXboxVtxFmtGetSize((RpXboxCompType)'+expr)
  if scope==2:c=c.replace('_rpXboxVtxFmtInstV3d((RpXboxCompType)fmt->pos','_rpXboxVtxFmtInstV3d((RpXboxCompType)'+expr)
  VS['pr_%d_%d'%(k,scope)]=[(anchor,body[:a]+c+body[b:]+anchor)]
