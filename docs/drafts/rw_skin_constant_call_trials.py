"""Skin-node context probes: _XBoxSkinAtomicAllInOneNode 0x2D46F0
against src/rw/plugin/skin2/xbox/skinplatform.c with pscore.py.
No exact match; see questions.md.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
a=body.index('                            D3DDevice_SetVertexShaderConstantFast(');b=body.index('                            bone++;',a);chunk=body[a:b]
VS={'cf_base':[(old,body)]}
for mode in range(4):
 for fmt in range(4):
  c=chunk
  if mode&1:c=c.replace('D3DDevice_SetVertexShaderConstantFast','D3DDevice_SetVertexShaderConstantNotInlineFast').replace('[bone] - 96,','[bone],').replace('                                3);','                                12);')
  if mode&2:c=c.replace('baseConstant + 3 * skin->skinSplitData.matrixRemapIndices[bone]','3 * skin->skinSplitData.matrixRemapIndices[bone] + baseConstant')
  if fmt==1:c=c.replace('skin->skinSplitData.matrixRemapIndices[bone]','(RwInt32)skin->skinSplitData.matrixRemapIndices[bone]')
  if fmt==2:c=c.replace('baseConstant','(RwInt32)baseConstant')
  if fmt==3:c=c.replace('3 * skin->skinSplitData.matrixRemapIndices[bone]','(skin->skinSplitData.matrixRemapIndices[bone] * 3)')
  VS['cf_%d_%d'%(mode,fmt)]=[(old,body[:a]+c+body[b:])]
