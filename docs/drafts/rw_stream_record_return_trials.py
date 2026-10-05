"""RwStreamSkip struct-return probes: _RwStreamSkip 0x2A7210
src/rw/src/plcore/bastream.c with pscore.py. No exact candidate.
"""
exec(open('docs/drafts/rw_stream_memory_block_trials.py').read())
VS={}
for order in range(2):
 for mode in range(4):
  for scope in range(2):
   ts=['RwUInt32 offset','RwUInt32 position'];ns=['offset','smpMem->position']
   if scope:ts[1]='const RwStreamMemory *memory';ns[1]='smpMem'
   pos='memory->position' if scope else 'position'
   if order:ts.reverse();ns.reverse()
   expr=['r.position = offset + '+pos+';','r.position = '+pos+'; r.position += offset;','r.position = offset; r.position += '+pos+';','r.position = '+pos+' + offset;'][mode]
   fn='typedef struct StreamPositionTrial { RwUInt32 position; } StreamPositionTrial;\nstatic __forceinline StreamPositionTrial StreamSumTrial('+', '.join(ts)+') { StreamPositionTrial r; '+expr+' return r; }\n'
   call='StreamSumTrial('+', '.join(ns)+').position'
   t=d.replace('smpMem->position + offset',call)
   VS['sr_%d_%d_%d'%(order,mode,scope)]=[('RwStream *\n'+d,fn+'RwStream *\n'+t)]
