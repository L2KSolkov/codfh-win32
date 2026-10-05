"""Run with pscore.py, _XboxDmorphAtomicInstanceCallback 0x2F28D0,
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Exhaustive loop-scope subsets;
no match, best 1261 normalized differing lines. Byte comparison is final.
"""
from pathlib import Path
d=Path('docs/drafts/dmorph_instance_draft.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
anchor='// match: __rpDMorphPipelinesCreate @ 0x002F4040'
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text()
import re
anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
VS={'dm_base':[(anchor,body+anchor),('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')]}

import re
base=VS['dm_base'];body=base[0][1][:-len(anchor)];VS={}
loops=[]
for m in re.finditer(r'for \(i = 0;',body):
 a=m.start();start=body.index('{',a);depth=1;e=start+1
 while depth:
  if body[e]=='{':depth+=1
  if body[e]=='}':depth-=1
  e+=1
 loops.append((a,e))
for mask in range(1,16):
 t=body
 for j,(a,b) in reversed(list(enumerate(loops))):
  group=0 if j==0 else 1 if j<3 else 2 if j<len(loops)-1 else 3
  if mask&(1<<group):t=t[:a]+'{ RwUInt32 localIndex;\n'+re.sub(r'\bi\b','localIndex',t[a:b])+'\n}'+t[b:]
 VS['dm4_%02d'%mask]=[(anchor,t+anchor),base[1]]

VS={}
for mask in range(1,1<<len(loops)):
 t=body
 for j,(a,b) in reversed(list(enumerate(loops))):
  if mask&(1<<j):t=t[:a]+'{ RwUInt32 localIndex;\n'+re.sub(r'\bi\b','localIndex',t[a:b])+'\n}'+t[b:]
 VS['dm5_%03d'%mask]=[(anchor,t+anchor),base[1]]
