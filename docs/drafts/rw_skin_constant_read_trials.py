"""Skin-node context probes: _XBoxSkinAtomicAllInOneNode 0x2D46F0
against src/rw/plugin/skin2/xbox/skinplatform.c with pscore.py.
No exact match; see questions.md.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
a=body.index('                            D3DDevice_SetVertexShaderConstantFast(');b=body.index('                            bone++;',a);chunk=body[a:b]
VS={}
for mask in range(16):
 c=chunk
 remap='skin->skinSplitData.matrixRemapIndices';vertex='skin->platformData.vertexIndexMap'
 if mask&1:remap='((volatile RpSkin *)skin)->skinSplitData.matrixRemapIndices'
 if mask&2:remap='((const volatile RwUInt8 *)('+remap+'))'
 if mask&4:vertex='((volatile RpSkin *)skin)->platformData.vertexIndexMap'
 if mask&8:vertex='((const volatile RwUInt32 *)('+vertex+'))'
 c=c.replace('skin->skinSplitData.matrixRemapIndices',remap).replace('skin->platformData.vertexIndexMap',vertex)
 VS['cv_%02d'%mask]=[(old,body[:a]+c+body[b:])]
