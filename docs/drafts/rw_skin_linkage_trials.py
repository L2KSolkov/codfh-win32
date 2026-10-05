"""Skin-node context probes: _XBoxSkinAtomicAllInOneNode 0x2D46F0
against src/rw/plugin/skin2/xbox/skinplatform.c with pscore.py.
No exact match; see questions.md.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
VS={}
for mask in range(16):
 t=body;h=''
 if mask&1:t=t.replace('RwBool\nXBoxSkinAtomicAllInOneNode','static RwBool\nXBoxSkinAtomicAllInOneNode',1)
 if mask&2:h+='extern void RwXboxLightsEnable(RwUInt32 lights, RwBool enable);\n'
 if mask&4:h+='extern DWORD RwXboxGetCurrentVertexShader(void);\n'
 if mask&8:
  decl='static ' if mask&1 else 'extern '
  h+=decl+'RwBool XBoxSkinAtomicAllInOneNode(RxPipelineNode *, const RxPipelineNodeParam *);\n'
 VS['lc_%02d'%mask]=[(old,h+t)]
