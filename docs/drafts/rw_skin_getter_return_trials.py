"""Skin-node probes: _XBoxSkinAtomicAllInOneNode 0x2D46F0, skinplatform.c. Best remains 16. No exact match.
Run through tools/session/pscore.py against the corresponding production unit.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
from itertools import permutations
VS={'ng_base':[(old,body)]}
needle='skin->skinSplitData.matrixRemapIndices[bone]'
for mode in range(4):
 for ret in ['RwUInt8','RwUInt32']:
  for order in range(2):
   ts=['const RwUInt8 *indices','RwUInt32 index'];ns=['skin->skinSplitData.matrixRemapIndices','bone']
   if mode&1:ts[0]='const RpSkin *skin';ns[0]='skin'
   if order:ts.reverse();ns.reverse()
   expr=('skin->skinSplitData.matrixRemapIndices' if mode&1 else 'indices')
   if mode&2:expr='((const volatile RwUInt8 *)'+expr+')'
   expr=expr+'[index]'
   h='static __forceinline '+ret+' SkinRemapTrial('+', '.join(ts)+') { return '+expr+'; }\n'
   VS['ng_%d_%s_%d'%(mode,ret,order)]=[(old,h+body.replace(needle,'SkinRemapTrial('+', '.join(ns)+')'))]
call='_rpSkinXboxSetMaterialColor(mesh->material, geomFlags & rpGEOMETRYMODULATEMATERIALCOLOR);'
for mode in range(3):
 ts=['RxXboxInstanceData *mesh','RwUInt32 geomFlags','RxXboxResEntryHeader *resEntryHeader'];ns=['mesh','geomFlags','resEntryHeader']
 if mode==1:ts[0]='RpMaterial *material';ns[0]='mesh->material'
 for k,order in enumerate(permutations(range(3))):
  h='static __forceinline RxXboxResEntryHeader *SkinMaterialHeaderTrial('+', '.join(ts[i] for i in order)+') { '+call.replace('mesh->material','material' if mode==1 else 'mesh->material')+' return resEntryHeader; }\n'
  new='resEntryHeader = SkinMaterialHeaderTrial('+', '.join(ns[i] for i in order)+');'
  t=body.replace(call,new)
  if mode==2:
   t=t.replace('            if (meshBatches)', '            RxXboxResEntryHeader *renderHeader;\n            if (meshBatches)').replace(new,'renderHeader = SkinMaterialHeaderTrial('+', '.join(ns[i] for i in order)+');').replace('if (resEntryHeader->vertexAlpha','if (renderHeader->vertexAlpha')
  VS['nh_%d_%d'%(mode,k)]=[(old,h+t)]
