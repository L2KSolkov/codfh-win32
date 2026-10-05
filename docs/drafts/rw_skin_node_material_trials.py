"""Run with pscore.py: _XBoxSkinAtomicAllInOneNode 0x2D46F0
src/rw/plugin/skin2/xbox/skinplatform.c. These are unmatched experiments.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
from itertools import permutations
VS={}
a=body.index('            _rpSkinXboxSetMaterialColor(mesh->material')
b=body.index('            privateData->renderCallback',a)
for scope in range(3):
 chunk=body[a:b]
 names=['mesh','geomFlags','resEntryHeader'];types=['RxXboxInstanceData *mesh','RwUInt32 geomFlags','RxXboxResEntryHeader *resEntryHeader']
 if scope==1:
  chunk=chunk.replace('mesh->material','material');names[0]='mesh->material';types[0]='RpMaterial *material'
 if scope==2:
  chunk=chunk.replace('resEntryHeader->vertexAlpha','vertexAlpha');names[2]='resEntryHeader->vertexAlpha';types[2]='RwBool vertexAlpha'
 for k,order in enumerate(permutations(range(3))):
  fn='static __forceinline void SkinMaterialTrial('+', '.join(types[i] for i in order)+') {\n'+chunk+'}\n'
  call='SkinMaterialTrial('+', '.join(names[i] for i in order)+');\n'
  VS['nm_%d_%d'%(scope,k)]=[(old,fn+body[:a]+call+body[b:])]
