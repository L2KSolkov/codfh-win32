"""Run with pscore.py: _XBoxSkinAtomicAllInOneNode 0x2D46F0
src/rw/plugin/skin2/xbox/skinplatform.c. These are unmatched experiments.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
VS={}
for k,lookup in enumerate(['((const volatile RwUInt8 *)skin->skinSplitData.matrixRemapIndices)[bone]','((volatile RpSkin *)skin)->skinSplitData.matrixRemapIndices[bone]','((const RwUInt8 * volatile *) &skin->skinSplitData.matrixRemapIndices)[0][bone]','skin->skinSplitData.matrixRemapIndices[bone]']):
 for m in range(4):
  t=body.replace('skin->skinSplitData.matrixRemapIndices[bone]',lookup)
  if m&1:t=t.replace('resEntryHeader->vertexAlpha','((volatile RxXboxResEntryHeader *)resEntryHeader)->vertexAlpha')
  if m&2:t=t.replace('geomFlags & rpGEOMETRYMODULATEMATERIALCOLOR','(geomFlags & rpGEOMETRYMODULATEMATERIALCOLOR) != 0')
  VS['nq_%d_%d'%(k,m)]=[(old,t)]
