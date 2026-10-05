"""RwStreamSkip probes: _RwStreamSkip 0x2A7210 src/rw/src/plcore/bastream.c.
Run with pscore.py. No exact candidate; see questions.md.
"""
exec(open('docs/drafts/rw_stream_memory_block_trials.py').read())
VS={}
for init in range(2):
 for scope in range(2):
  for order in range(2):
   for mode in range(3):
    ts=['RwUInt32 *next','RwUInt32 increment'];ns=['&nextPosition','smpMem->position' if init else 'offset']
    if scope:ts[1]='const RwUInt32 *increment';ns[1]='&smpMem->position' if init else '&offset'
    if order:ts.reverse();ns.reverse()
    val='*increment' if scope else 'increment'
    expr=['*next += '+val+';','*next = '+val+' + *next;','RwUInt32 sum = *next + '+val+'; *next = sum;'][mode]
    h='static __forceinline void StreamAdvanceTrial('+', '.join(ts)+') { '+expr+' }\n'
    t=d.replace('RwStreamMemory     *smpMem = &stream->Type.memory;','RwStreamMemory *smpMem = &stream->Type.memory;\n                RwUInt32 nextPosition = '+('offset' if init else 'smpMem->position')+';\n                StreamAdvanceTrial('+', '.join(ns)+');')
    t=t.replace('smpMem->position + offset > smpMem->nSize','nextPosition > smpMem->nSize').replace('smpMem->position += offset;','smpMem->position = nextPosition;')
    VS['sa_%d_%d_%d_%d'%(init,scope,order,mode)]=[('RwStream *\n'+d,h+'RwStream *\n'+t)]
