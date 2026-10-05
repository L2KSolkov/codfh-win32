from pathlib import Path
s=Path('src/rwa/unit_24CC50.c').read_text();d=Path('docs/drafts/rwa_splitter_draft.c').read_text();d=d[:d.index('/* A track')].replace('static rwaSplitter *','rwaSplitter *'); VS={}
import re
for n in range(128):
 count=[0]
 def sub(m):
  i=count[0];count[0]+=1
  return m[0].replace('obj->state.node.status','((volatile rwaSplitter *)obj)->state.node.status') if n&(1<<i) else m[0]
 u=re.sub(r'obj->state.node.status = [0-9];',sub,d)
 VS['st_%d'%n]=[(s,s+'\n'+u)]
