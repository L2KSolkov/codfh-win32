exec(open('docs/drafts/rwa_streamsource_scope_trials.py').read())
b=VS['src_m2'][0][1][len(s)+1:];VS={}
for n in range(8):
 t=b
 if n&1:t=t.replace('    RwUInt32            count;','').replace('        count = obj->state.noItems;','        failed = obj->state.noItems;').replace('i < count','i < (RwUInt32)failed').replace('items, count','items, (RwUInt32)failed')
 if n&2:
  t=t.replace('        for (i = 0; i < '+('(RwUInt32)failed' if n&1 else 'count')+'; i++)','        for (i = '+('(RwUInt32)failed' if n&1 else 'count')+'; i; i--)').replace('items[i]','item[0]').replace('positions[i]','position[0]').replace('        { rwaQueueCallback','        rwaQueueItem *item; rwaStreamPosition *position;\n        item = items; position = positions;\n        { rwaQueueCallback').replace('            position[0].unit = 2;','            position[0].unit = 2;\n            item++; position++;')
  # declarations must precede statements in C
  t=t.replace('        rwaQueueItem *item; rwaStreamPosition *position;\n','').replace('    RwUInt32            i;','    RwUInt32            i;\n    rwaQueueItem *item; rwaStreamPosition *position;')
 if n&4:t=t.replace('    RwUInt32            i;', '    RwInt32             i;')
 VS['sl_%d'%n]=[(s,s+'\n'+t)]
