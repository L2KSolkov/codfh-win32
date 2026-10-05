"""Run with pscore.py: _XBoxSkinAtomicAllInOneNode 0x2D46F0
src/rw/plugin/skin2/xbox/skinplatform.c. These are unmatched experiments.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
from itertools import permutations
VS={'nb_base':[(old,body)]}
for scope in range(3):
 if scope==0:
  a=body.index('                            D3DDevice_SetVertexShaderConstantFast(');b=body.index('                            bone++;',a)
  names=['skin','baseConstant','bone'];types=['RpSkin *skin','RwUInt32 baseConstant','RwUInt32 bone']
 elif scope==1:
  a=body.index('                        RwUInt32    bone = rle[0];');b=body.index('                        rle += 2;',a)
  names=['skin','baseConstant','rle'];types=['RpSkin *skin','RwUInt32 baseConstant','const RwUInt8 *rle']
 else:
  a=body.index('                RwUInt32    rleStart = meshBatches[0];');b=body.index('\n            }',a)
  names=['skin','baseConstant','meshBatches','boneBatches'];types=['RpSkin *skin','RwUInt32 baseConstant','const RwUInt8 *meshBatches','const RwUInt8 *boneBatches']
 chunk=body[a:b]
 if scope==2:chunk=chunk.replace('                meshBatches += 2;','')
 for k,order in enumerate(permutations(range(len(names)))):
  fn='static __forceinline void SkinBatchTrial('+', '.join(types[i] for i in order)+') {\n'+chunk+'}\n'
  call='SkinBatchTrial('+', '.join(names[i] for i in order)+');\n'+('meshBatches += 2;\n' if scope==2 else '')
  VS['nb_%d_%d'%(scope,k)]=[(old,fn+body[:a]+call+body[b:])]
