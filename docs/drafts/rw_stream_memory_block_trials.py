"""RwStreamSkip probes: pscore _RwStreamSkip 0x2A7210
src/rw/src/plcore/bastream.c. No exact match.
"""
from pathlib import Path
from itertools import permutations
s=Path('src/rw/src/plcore/bastream.c').read_text()
a=s.index('RwStreamSkip(RwStream *stream, RwUInt32 offset)');b=s.index('\n}\n',a)+3;d=s[a:b]
a=d.index('                RwStreamMemory     *smpMem');b=d.index('\n            }',a);chunk=d[a:b]
VS={'sm_base':[]}
for scope in range(2):
 names=['stream','offset'];types=['RwStream *stream','RwUInt32 offset'];c=chunk
 if scope:
  names.append('&stream->Type.memory');types.append('RwStreamMemory *smpMem');c=c.replace('                RwStreamMemory     *smpMem = &stream->Type.memory;','')
 for k,order in enumerate(permutations(range(len(names)))):
  fn='static __forceinline RwStream *StreamMemorySkipTrial('+', '.join(types[i] for i in order)+')\n{\n'+c+'\n}\n'
  call='                return StreamMemorySkipTrial('+', '.join(names[i] for i in order)+');'
  VS['sm_%d_%d'%(scope,k)]=[('RwStream *\n'+d,fn+'RwStream *\n'+d[:a]+call+d[b:])]
