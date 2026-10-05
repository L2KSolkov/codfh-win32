"""Skin-node probes: _XBoxSkinAtomicAllInOneNode 0x2D46F0.
Run pscore.py against src/rw/plugin/skin2/xbox/skinplatform.c.
No candidate improves the 16-line baseline; see questions.md.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
VS={}
start=body.index('                            D3DDevice_SetVertexShaderConstantFast(');end=body.index('                            bone++;',start)
chunk=body[start:end]
from itertools import permutations
items=[('RwUInt32 remappedBone = skin->skinSplitData.matrixRemapIndices[bone];','skin->skinSplitData.matrixRemapIndices[bone]','remappedBone'),('RwUInt32 mappedVertex = skin->platformData.vertexIndexMap[bone];','skin->platformData.vertexIndexMap[bone]','mappedVertex')]
for mask in range(1,4):
 for order in range(2):
  for typ in ['RwUInt32','RwInt32']:
   for scope in range(3):
    chosen=[i for j,i in enumerate(items) if mask&(1<<j)]
    if order:chosen.reverse()
    c=chunk
    for decl,oldexpr,newexpr in chosen:c=c.replace(oldexpr,newexpr)
    decls='\n'.join(i[0].replace('RwUInt32',typ) for i in chosen)
    if scope==0:c=decls+'\n'+c
    if scope==1:c='{ '+decls+'\n'+c+'}\n'
    if scope==2:
     c='\n'.join(typ+' '+i[2]+';' for i in chosen)+'\n'+'\n'.join(i[0].replace('RwUInt32 ','') for i in chosen)+'\n'+c
    VS['bl_%d_%d_%s_%d'%(mask,order,typ,scope)]=[(old,body[:start]+c+body[end:])]
