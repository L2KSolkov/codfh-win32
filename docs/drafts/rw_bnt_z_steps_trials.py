"""Final BNT cross-product probes. pscore target __rpXboxVtxFmtInstBNT
0x2DDB50 src/rw/world/pipe/p2/xbox/xbvtxfmt.c. Not exact.
"""
from pathlib import Path
import re
s=Path('src/rw/world/pipe/p2/xbox/xbvtxfmt.c').read_text();anchor=re.search(r'// match: __rpXboxVtxFmtUnInstV3d[^\n]*',s)[0]
d=Path('docs/drafts/rw_xbvtxfmt_bnt_sum_followup.c').read_text();body=d[d.index('#define CrossLoadTrial'):]
a=body.index('    (o)->z =');b=body.index('} ',a);old=body[a:b]
forms=[
'{ RwReal value = (a)->x * (b)->y; value -= (a)->y * (b)->x; (o)->z = value; }',
'{ RwReal value = (b)->y * (a)->x; value -= (b)->x * (a)->y; (o)->z = value; }',
'{ RwReal first = (a)->x * (b)->y; RwReal second = (b)->x * (a)->y; (o)->z = first - second; }',
'{ RwReal second = (b)->x * (a)->y; RwReal first = (a)->x * (b)->y; (o)->z = first - second; }',
'{ RwReal nx = (b)->x; RwReal ty = (a)->y; (o)->z = (a)->x * (b)->y - nx * ty; }',
'{ RwReal ty = (a)->y; RwReal nx = (b)->x; (o)->z = (a)->x * (b)->y - nx * ty; }',
'(o)->z = (a)->x * (b)->y; (o)->z -= (b)->x * (a)->y;',
'{ RwReal value; value = (a)->x * (b)->y; value = value - (b)->x * (a)->y; (o)->z = value; }']
VS={'bz_base':[(anchor,body+anchor)]}
for k,f in enumerate(forms):
 for mask in range(16):
  q=f
  for j,(p,c) in enumerate([('a','x'),('a','y'),('b','x'),('b','y')]):
   if mask&(1<<j):q=q.replace('('+p+')->'+c,'((const volatile RwV3d *)('+p+'))->'+c)
  t=body[:a]+'    '+q+' \\\n'+body[b:]
  VS['bz_%d_%02d'%(k,mask)]=[(anchor,t+anchor)]
