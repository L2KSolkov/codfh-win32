"""Delta-morph traversal/RLE probes. pscore target
_XboxDmorphAtomicInstanceCallback 0x2F28D0
src/rw/plugin/dmorph/xbox/dmorphpipeg.c. Best remains 894.
"""
exec(open('docs/drafts/dmorph_target_address_trials.py').read())
VS={}
start=body.index('                const rpDMorphRLE *rle =');end=body.index('                if (dMorphTarget->flags & rpGEOMETRYPOSITIONS)',start);oldblock=body[start:end]
loopstart=oldblock.index('                for (j =');loop=oldblock[loopstart:]
for mode in range(6):
 for order in range(2):
  for counter in range(2):
   cond='count > 0' if mode%3==0 else 'count != 0' if mode%3==1 else 'rle->numCodeElements > 0'
   lead='const rpDMorphRLE *rle = &dMorphTarget->rle;\n'
   if mode<3:lead+='RwUInt32 count = rle->numCodeElements;\n'
   else:cond='rle->numCodeElements > 0' if mode%3==0 else 'rle->numCodeElements != 0'
   inner=('RwUInt32 count = rle->numCodeElements;\n' if mode>=3 else '')
   decl=['RwUInt32 j;','const RwUInt8 *code = rle->code;']
   if order:decl.reverse()
   inner+='\n'.join(decl)+'\n'+loop
   if counter:inner=inner.replace('for (j = 0; j < count; j++)','for (j = count; j > 0; --j, ++code)').replace('code[j]','code[0]')
   t=body[:start]+lead+'if ('+cond+') {\n'+inner+'}\n'+body[end:]
   VS['rg_%d_%d_%d'%(mode,order,counter)]=[(anchor,t+anchor),inc]
