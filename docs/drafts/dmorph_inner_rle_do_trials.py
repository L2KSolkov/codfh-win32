"""Delta-morph traversal/RLE probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Best remains 894.
"""
exec(open('docs/drafts/dmorph_inner_rle_guard_trials.py').read())
VS={}
loopbody=loop[loop.index('{')+1:loop.rfind('}')]
for mode in range(3):
 for place in range(3):
  for guard in ['count > 0','count != 0']:
   lead='const rpDMorphRLE *rle = &dMorphTarget->rle;\nRwUInt32 count = rle->numCodeElements;\nRwUInt32 j;\n'
   inner='const RwUInt8 *code = rle->code;\n'
   if place==0:lead+='j = 0;\n'
   if place==1:inner+='j = 0;\n'
   if place==2:lead=lead.replace('RwUInt32 j;','RwUInt32 j = 0;')
   step='++j;';cond='j < count'
   if mode==1:step='j++;'
   if mode==2:step='++j; ++code;';loopb=loopbody.replace('code[j]','code[0]')
   else:loopb=loopbody
   inner+='do {\n'+loopb+step+'\n} while ('+cond+');\n'
   t=body[:start]+lead+'if ('+guard+') {\n'+inner+'}\n'+body[end:]
   VS['rd_%d_%d_%d'%(mode,place,guard=='count > 0')]=[(anchor,t+anchor),inc]
