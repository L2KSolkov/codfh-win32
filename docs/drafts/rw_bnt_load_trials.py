"""Parked BNT load-order probes. Run pscore.py with
__rpXboxVtxFmtInstBNT 0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c.
Best remains 14 normalized lines; no candidate matches.
"""
from pathlib import Path
import re
s=Path('src/rw/world/pipe/p2/xbox/xbvtxfmt.c').read_text()
body=Path('docs/drafts/rw_xbvtxfmt_bnt_followup.c').read_text();body=body[body.index('#define SMALL_FLOAT'):]
anchor=re.search(r'// match: __rpXboxVtxFmtUnInstV3d[^\n]*',s)[0]
h=Path('include/rw/sdk/rwplcore.h').read_text();a=h.index('#define RwV3dCrossProductMacro');b=h.index('\n\n',a)
macro=h[a:b].replace('RwV3dCrossProductMacro','CrossLoadTrial')
VS={}
for mask in range(64):
 for reverse in range(2):
  m=macro
  for j,(p,c) in enumerate([('a','x'),('a','y'),('a','z'),('b','x'),('b','y'),('b','z')]):
   if mask&(1<<j):m=m.replace('('+p+')->'+c,'((const volatile RwV3d *)('+p+'))->'+c)
  t=body.replace('RwV3dCrossProduct(currentBinormal, currentTangent, currentNormal);','CrossLoadTrial(currentBinormal, currentTangent, currentNormal);')
  if reverse:t=t.replace('RwV3dDotProductMacro(currentBinormal, currentBinormal)','(currentBinormal->y * currentBinormal->y + currentBinormal->x * currentBinormal->x) + currentBinormal->z * currentBinormal->z')
  VS['bl_%02d_%d'%(mask,reverse)]=[(anchor,m+'\n'+t+anchor)]
