exec(open('docs/drafts/rwa_source_param_order_trials.py').read());v=VS['srco_3_0'][0][1];VS={}
for n in range(8):
 h='static __forceinline void queueItems('+('rwaQueueItem *items, RwUInt32 count, rwaDecoder *obj' if n&1 else 'RwUInt32 count, rwaQueueItem *items, rwaDecoder *obj')+') { sub_2472E0(&obj->state.queue, items, count); }\n'
 u=v.replace('// match: _sub_241230',h+'// match: _sub_241230').replace('sub_2472E0(&obj->state.queue, (rwaQueueItem *)arg, count)', 'queueItems('+('(rwaQueueItem *)arg, count, obj' if n&1 else 'count, (rwaQueueItem *)arg, obj')+')')
 if n&2:u=u.replace('(rwaQueueItem *)arg, count, obj','(rwaQueueItem *)*(rwaDecoder *volatile *)&arg, count, obj').replace('count, (rwaQueueItem *)arg, obj','count, (rwaQueueItem *)*(rwaDecoder *volatile *)&arg, obj')
 if n&4:u=u.replace('count, obj)', '*(volatile RwUInt32 *)&count, obj)').replace('queueItems(count,','queueItems(*(volatile RwUInt32 *)&count,')
 VS['srcend_%d'%n]=[(s,u)]
