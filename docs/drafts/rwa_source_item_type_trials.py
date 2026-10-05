from pathlib import Path
s=Path('src/rwa/rwastreamsourceobj.c').read_text();d=Path('docs/drafts/rwa_streamsource_followup.c').read_text();VS={}
for n,ty in enumerate(['void','RwUInt8','rwaQueueItem']):
 u=d.replace('rwaDecoder *arg)',ty+' *arg)').replace('rwaDecoder *obj = arg;', 'rwaDecoder *obj = (rwaDecoder *)arg;').replace('arg = (rwaDecoder *)obj->state.items;', 'arg = ('+ty+' *)obj->state.items;')
 base=s.replace('extern void sub_241230(rwaDecoderState *state, RwBool failed, rwaDecoder *obj);', 'extern void sub_241230(rwaDecoderState *state, RwBool failed, '+ty+' *obj);')
 VS['itemtype_%d'%n]=[(s,base+'\n'+u)]
