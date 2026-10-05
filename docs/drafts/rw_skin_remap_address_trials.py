"""Skin-node probes: _XBoxSkinAtomicAllInOneNode 0x2D46F0, skinplatform.c. Best remains 16. No exact match.
Run through tools/session/pscore.py against the corresponding production unit.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
VS={}
needle='skin->skinSplitData.matrixRemapIndices[bone]'
for typ in ['RwUInt32','RwInt32','size_t']:
 for order in range(2):
  expr=('('+typ+')skin->skinSplitData.matrixRemapIndices + ('+typ+')bone') if order else '(('+typ+')bone + ('+typ+')skin->skinSplitData.matrixRemapIndices)'
  for kind in range(3):
   q='*(const RwUInt8 *)('+expr+')'
   if kind==1:q='*(const RwUInt8 *)(('+typ+')skin->skinSplitData.matrixRemapIndices - -('+typ+')bone)'
   if kind==2:q='*(const RwUInt8 *)(('+typ+')bone - -('+typ+')skin->skinSplitData.matrixRemapIndices)'
   VS['na_%s_%d_%d'%(typ,order,kind)]=[(old,body.replace(needle,q))]
for typ in ['RwUInt32','RwInt32']:
 for order in range(2):
  for expr in ['address + index','index + address','address - -index','index - -address']:
   ts=[typ+' address',typ+' index'];ns=['('+typ+')skin->skinSplitData.matrixRemapIndices','('+typ+')bone']
   if order:ts.reverse();ns.reverse()
   h='static __forceinline RwUInt32 RemapAddressTrial('+', '.join(ts)+') { return *(const RwUInt8 *)('+expr+'); }\n'
   VS['nah_%s_%d_%d'%(typ,order,len(VS))]=[(old,h+body.replace(needle,'RemapAddressTrial('+', '.join(ns)+')'))]
