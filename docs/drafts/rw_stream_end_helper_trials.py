"""RwStreamSkip probes: _RwStreamSkip 0x2A7210 src/rw/src/plcore/bastream.c.
Run with pscore.py. No exact candidate; see questions.md.
"""
exec(open('docs/drafts/rw_stream_memory_block_trials.py').read())
VS={'se_base':[]}
cond='smpMem->position + offset > smpMem->nSize'
for scope in range(3):
 names=['smpMem','offset'];types=['const RwStreamMemory *memory','RwUInt32 offset'];expr='memory->position + offset > memory->nSize'
 if scope==1:names=['smpMem->position','offset','smpMem->nSize'];types=['RwUInt32 position','RwUInt32 offset','RwUInt32 size'];expr='position + offset > size'
 if scope==2:names=['&smpMem->position','offset','&smpMem->nSize'];types=['const RwUInt32 *position','RwUInt32 offset','const RwUInt32 *size'];expr='*position + offset > *size'
 for k,order in enumerate(permutations(range(len(names)))):
  for form in range(4):
   c='return '+expr+';'
   if form==1:c='RwUInt32 next = '+expr.split(' > ')[0]+'; return next > '+expr.split(' > ')[1]+';'
   if form==2:c='if ('+expr+') return TRUE; return FALSE;'
   if form==3:c='return !('+expr.replace(' > ',' <= ')+');'
   fn='static __forceinline RwBool StreamEndTrial('+', '.join(types[i] for i in order)+') { '+c+' }\n'
   call='StreamEndTrial('+', '.join(names[i] for i in order)+')'
   VS['se_%d_%d_%d'%(scope,k,form)]=[('RwStream *\n'+d,fn+'RwStream *\n'+d.replace(cond,call))]
