"""Parked default-instancer experiments; no exact candidate.
Target __rpXboxDefaultInstance 0x2DED60 in xbvtxfmt.c. See questions.md.
"""
exec(open('docs/drafts/rw_default_instance_trials.py').read())
VS={}
for typ in ['RpXboxCompType','RwUInt32','RwInt32']:
 for ret in ['RwUInt32','RwInt32']:
  for qual in ['','__inline','__forceinline']:
   for mode in range(4):
    params=typ+' type, RwUInt32 count';args='('+typ+')fmt->pos, 3'
    if mode==1:params='RwUInt32 count, '+typ+' type';args='3, ('+typ+')fmt->pos'
    if mode==2:params=typ+' type';args='('+typ+')fmt->pos'
    expr='if (type == rpNORMALIZEDPACKED) return 4; return RpXboxCompSize[type] * '+('3' if mode==2 else 'count')+';'
    if mode==3:expr='RwUInt32 result; if (type == rpNORMALIZEDPACKED) result = 4; else result = RpXboxCompSize[type] * count; return result;'
    fn='static '+qual+' '+ret+' PositionSizeTrial('+params+') { '+expr+' }\n'
    t=body.replace(old,'lockedVertexBuffer += PositionSizeTrial('+args+');')
    VS['st_%s_%s_%s_%d'%(typ,ret,qual,mode)]=[(anchor,fn+t+anchor)]
