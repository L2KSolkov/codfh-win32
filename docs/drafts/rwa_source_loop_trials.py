from pathlib import Path
import itertools
s=Path('src/rwa/rwastreamsourceobj.c').read_text();d=Path('docs/drafts/rwa_streamsource_followup.c').read_text();a=d.index('        for (');b=d.index('        sub_2472E0');loop=d[a:b];VS={}
for n in range(16):
 args=['state','obj','arg','positions','count','callback'];types=['rwaDecoderState *state','rwaDecoder *obj','rwaDecoder *arg','rwaStreamPosition *positions','RwUInt32 count','rwaQueueCallback *callback']
 if n&1:args.reverse();types.reverse()
 h='static __forceinline rwaDecoder *initItems('+', '.join(types)+') { RwUInt32 i;\n'+loop+'return arg;\n}\n'
 u=d[:a]+'        arg = initItems('+', '.join(args)+');\n'+d[b:]
 if n&2:h=h.replace('return arg;', 'return (rwaDecoder *)count;');u=u.replace('arg = initItems(', 'count = (RwUInt32)initItems(')
 if n&4:h=h.replace('i < count', 'i != count')
 if n&8:h=h.replace('RwUInt32 i;', 'RwInt32 i;')
 VS['srloop_%d'%n]=[(s,s+'\n'+h+u)]
