exec(open('docs/drafts/smallagent_baselines.py').read())
VS={}
tail='        sub_2472E0(&obj->state.queue, (rwaQueueItem *)arg, count);'
loopend='            positions[i].unit = 2;\n        }'
for k in range(32):
 b=body
 a='arg = *(rwaDecoder *volatile *)&arg;'
 c='count = *(volatile RwUInt32 *)&count;'
 if k&1: a='arg = *(rwaDecoder **)&arg;'
 if k&2: c='count = *(RwUInt32 *)&count;'
 insertion='\n        '+(c+'\n        '+a if k&4 else a+'\n        '+c)
 if k&8: b=b.replace(loopend,loopend+insertion)
 else: b=b.replace(tail,insertion+'\n'+tail)
 if k&16: b=b.replace('    RwUInt32 count;', '').replace('count = obj->state.noItems;', 'failed = obj->state.noItems;').replace('count','failed')
 VS['smallagent_srcreload_'+str(k)]=[(anchor,b+anchor),(old,proto)]
