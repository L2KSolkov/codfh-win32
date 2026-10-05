exec(open('docs/drafts/smallagent_baselines.py').read())
VS = {}
for atype in ['void *', 'rwaQueueItem *', 'RwUInt8 *', 'RwUInt32 *', 'rwaInstance *', 'rwaDecoder *']:
 for ctype in ['RwUInt32', 'RwUInt8', 'RwUInt16', 'RwInt32']:
  b = body.replace('rwaDecoder *arg)', atype+'arg)').replace('rwaDecoder *obj = arg;', 'rwaDecoder *obj = (rwaDecoder *)arg;').replace('arg = (rwaDecoder *)obj->state.items;', 'arg = ('+atype+')obj->state.items;').replace('RwUInt32 count;', ctype+' count;')
  n = 'smallagent_srctype_' + atype.replace(' ', '').replace('*','') + '_' + ctype
  VS[n] = [(anchor,b+anchor),(old,proto),('extern void sub_241230(rwaDecoderState *state, RwBool failed, rwaDecoder *obj);','extern void sub_241230(rwaDecoderState *state, RwBool failed, '+atype+'obj);')]
for k in range(16):
 b=body
 if k&1: b=b.replace('((rwaQueueItem *)arg)[i].', '(((rwaQueueItem *)arg)+i)->')
 if k&2: b=b.replace('    RwUInt32 count;', '    const RwUInt32 countDummy = 0;\n    RwUInt32 count;')
 if k&4: b=b.replace('for (i = 0; i < count; i++)', 'for (i = count; i > 0; i--)').replace('[i]', '[count-i]')
 if k&8: b=b.replace('RwUInt32 i;', 'RwInt32 i;')
 VS['smallagent_srcshape_'+str(k)] = [(anchor,b+anchor),(old,proto)]
