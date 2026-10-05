from pathlib import Path
s=Path('src/rwa/rwastreamsourceobj.c').read_text();d=Path('docs/drafts/rwa_streamsource_draft.c').read_text();VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('rwaDecoder *obj)','rwaDecoder *arg)').replace('    RwUInt32            count;', '    rwaDecoder *obj = arg;\n    RwUInt32 count;').replace('    rwaQueueItem       *items;','').replace('items = obj->state.items;', 'arg = (rwaDecoder *)obj->state.items;').replace('items[i]','((rwaQueueItem *)arg)[i]').replace('queue, items, count','queue, (rwaQueueItem *)arg, count')
 if n&2:u=u.replace('    RwUInt32            count;','').replace('    RwUInt32 count;','').replace('count = obj->state.noItems;', 'failed = obj->state.noItems;').replace('i < count','i < (RwUInt32)failed').replace(', count);', ', (RwUInt32)failed);')
 if n&4:u=u.replace('    RwUInt32            i;', '    RwUInt32 i;\n    rwaQueueCallback *callback;').replace('        obj->state.callback.func', '        callback = &obj->state.callback;\n        callback->func').replace('obj->state.callback.data','callback->data').replace('= &obj->state.callback;\n            ', '= callback;\n            ')
 VS['srcparam_%d'%n]=[(s,s+'\n'+u)]
