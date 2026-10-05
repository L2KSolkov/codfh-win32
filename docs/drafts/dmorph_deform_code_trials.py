"""Parked delta-morph callback probes: _XboxDmorphAtomicInstanceCallback
0x2F28D0 src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Run with pscore.py.
No candidate improves the saved 900-line baseline.
"""
exec(open('docs/drafts/dmorph_entry_order_trials.py').read())
VS={}
needle='RwUInt32    maxl = rle->code[j] & 0x7F;'
for typ in ['RwUInt8','RwUInt32','RwInt8']:
 for mask in range(16):
  t=body;start=0
  for j in range(4):
   a=t.index(needle,start);b=t.index('if (rle->code[j] & 0x80)',a)+len('if (rle->code[j] & 0x80)')
   if mask&(1<<j):
    c=t[a:b].replace(needle,typ+' code = rle->code[j]; RwUInt32 maxl = code & 0x7F;').replace('if (rle->code[j] & 0x80)','if (code & 0x80)')
    t=t[:a]+c+t[b:];start=a+len(c)
   else:start=b
  VS['dr_%s_%02d'%(typ,mask)]=[(anchor,t+anchor),inc]
