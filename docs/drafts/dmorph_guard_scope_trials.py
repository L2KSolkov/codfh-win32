"""Guarded delta-morph loop probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. No exact match.
"""
from pathlib import Path
import re
s=Path('src/rw/plugin/dmorph/xbox/dmorphpipeg.c').read_text();anchor=re.search(r'// match: __rpDMorphPipelinesCreate[^\n]*',s)[0]
d=Path('docs/drafts/dmorph_instance_guarded_followup.c').read_text();body=d[d.index('typedef struct _BlockInfo'):]
inc=('#include "xbpipe.h"','#include "xbpipe.h"\n#include "xbvtxfmt.h"')
VS={'sg_saved':[(anchor,body+anchor),inc]}
while '{ RwUInt32 localIndex;' in body:
 a=body.index('{ RwUInt32 localIndex;');depth=1;e=a+1
 while depth:
  if body[e]=='{':depth+=1
  if body[e]=='}':depth-=1
  e+=1
 c=body[a+len('{ RwUInt32 localIndex;'):e-1]
 body=body[:a]+re.sub(r'\blocalIndex\b','i',c)+body[e:]
loops=[]
for m in re.finditer(r'for \(i = 0;',body):
 a=m.start();start=body.index('{',a);depth=1;e=start+1
 while depth:
  if body[e]=='{':depth+=1
  if body[e]=='}':depth-=1
  e+=1
 loops.append((a,e))
for mask in range(1<<len(loops)):
 t=body
 for j,(a,b) in reversed(list(enumerate(loops))):
  if mask&(1<<j):t=t[:a]+'{ RwUInt32 localIndex;\n'+re.sub(r'\bi\b','localIndex',t[a:b])+'\n}'+t[b:]
 VS['sg_%03d'%mask]=[(anchor,t+anchor),inc]
