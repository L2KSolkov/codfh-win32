"""Compressed BNT scratch probes; pscore target __rpXboxVtxFmtInstBNTComp
0x2DE0F0 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. Not matched source.
"""
from pathlib import Path
import re
s=Path('src/rw/world/pipe/p2/xbox/xbvtxfmt.c').read_text();d=Path('docs/drafts/rw_xbvtxfmt_bntcomp_draft.c').read_text();body=d[d.index('#define SMALL_FLOAT'):]
anchor=re.search(r'// match: __rpXboxVtxFmtUnInstV3d[^\n]*',s)[0]
h=Path('include/rw/sdk/rwplcore.h').read_text()
def get(name,new):
 a=h.index('#define '+name);b=h.index('\n\n',a);return h[a:b].replace(name,new)
dot=get('RwV3dDotProductMacro','CompDotTrial');scale=get('RwV3dScaleMacro','CompScaleTrial');norm=get('_rwV3dNormalizeMacro','CompNormalizeTrial').replace('RwV3dDotProductMacro','CompDotTrial').replace('RwV3dScaleMacro','CompScaleTrial')
VS={}
for dm in range(64):
 d=dot
 for j,(p,c) in enumerate([(p,c) for p in ['a','b'] for c in 'xyz']):
  if dm&(1<<j):d=d.replace('('+p+')->'+c,'((const volatile RwV3d *)('+p+'))->'+c)
 for sm in range(8):
  sc=scale
  for j,c in enumerate('xyz'):
   if sm&(1<<j):sc=sc.replace('(a)->'+c,'((const volatile RwV3d *)(a))->'+c)
  t=body.replace('_rwV3dNormalizeMacro(unused, currentTangent, currentTangent);','CompNormalizeTrial(unused, currentTangent, currentTangent);')
  VS['cn_%02d_%d'%(dm,sm)]=[(anchor,d+'\n'+sc+'\n'+norm+'\n'+t+anchor)]
