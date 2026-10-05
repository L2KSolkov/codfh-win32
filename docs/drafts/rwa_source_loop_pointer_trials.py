from pathlib import Path
s=Path('src/rwa/rwastreamsourceobj.c').read_text();d=Path('docs/drafts/rwa_streamsource_followup.c').read_text();VS={}
for n in range(16):
 u=d.replace('    RwUInt32 i;', '    RwUInt32 i;\n    rwaQueueItem *item;')
 u=u.replace('        for (i = 0; i < count; i++)', '        item = (rwaQueueItem *)arg;\n        for (i = count; i > 0; i--, item++, positions++)').replace('((rwaQueueItem *)arg)[i].','item->').replace('&positions[i]','positions').replace('positions[i].','positions->')
 if n&1:u=u.replace('for (i = count; i > 0; i--, item++, positions++)', 'for (i = count; i != 0; i--, item++, positions++)')
 if n&2:u=u.replace('count = obj->state.noItems;', 'count = obj->state.noItems;\n        failed = count;').replace('i = count;', 'count = failed;').replace('i > 0; i--', 'count > 0; count--').replace('i != 0; i--', 'count != 0; count--').replace('(rwaQueueItem *)arg, count);', '(rwaQueueItem *)arg, (RwUInt32)failed);')
 if n&4:u=u.replace('item++, positions++','positions++, item++')
 if n&8:u=u.replace('        item = (rwaQueueItem *)arg;', '        item = (rwaQueueItem *)arg;').replace('RwUInt32 i;', 'RwInt32 i;')
 VS['srcptr_%d'%n]=[(s,s+'\n'+u)]
