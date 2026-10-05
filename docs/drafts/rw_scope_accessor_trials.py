"""Reproduce the 2026-10-01 scope/accessor follow-up trials.
Set RW_TRIAL to node (default), ortho, or format, then run pscore.py with:
 node: _XBoxSkinAtomicAllInOneNode 0x2D46F0 src/rw/plugin/skin2/xbox/skinplatform.c
 ortho: _MatrixOrthoNormalize 0x2A48C0 src/rw/src/plcore/bamatrix.c
 format: __rpSkinXboxGetVertexFormatShader 0x2D4440 src/rw/plugin/skin2/xbox/skinxboxformat.c
No exact matches. Scores include relocation/padding artifacts.
"""
import os
mode = os.environ.get('RW_TRIAL', 'node')
if mode == 'node':
    from pathlib import Path
    src=Path('src/rw/plugin/skin2/xbox/skinplatform.c').read_text()
    d=Path('docs/drafts/rw_skinplatform_draft.c').read_text()
    body=d[d.index('// match: _XBoxSkinAtomicAllInOneNode'):d.index('// match: _XBoxSkinAtomicAllInOnePipelineInit')].replace('static RwBool','RwBool')
    a=src.index('/* The node body');b=src.index('// match: _XBoxSkinAtomicAllInOnePipelineInit',a)
    old=src[a:b]
    VS={'sn_base':[(old,body)]}
    VS={'ns_base':[(old,body)]}
    for mask in range(1,16):
     t=body
     if mask&1:t=t.replace('        for (mesh = resEntryHeader->begin;', '        { RxXboxInstanceData *mesh;\n        for (mesh = resEntryHeader->begin;').replace('        _rpSkinXboxTo96Constants();','        }\n        _rpSkinXboxTo96Constants();')
     if mask&2:t=t.replace('RwUInt32    bone = rle[0];','RwUInt32 bone;').replace('                        do\n                        {','                        bone = rle[0];\n                        do\n                        {')
     if mask&4:t=t.replace('RwUInt32        batchesLeft = rleCount;','RwUInt32 batchesLeft;\n                    batchesLeft = rleCount;')
     if mask&8:t=t.replace('RwUInt32    numBones = rle[1];','RwUInt32 numBones;\n                        numBones = rle[1];')
     VS['ns_%02d'%mask]=[(old,t)]

elif mode == 'ortho':
    from pathlib import Path
    s=Path('src/rw/src/plcore/bamatrix.c').read_text();a=s.index('static __declspec(noinline) RwMatrix *\nMatrixOrthoNormalize');b=s.index('\n}\n',a)+3;body=s[a:b];VS={'on_base':[]}
    from itertools import permutations
    for order in permutations(['o','a','b']):
     for mask in range(1,4):
      params=', '.join(('RwV3d *' if x=='o' else 'const RwV3d *')+x for x in order)
      h='static __forceinline void CrossTrial('+params+') { RwV3dCrossProductMacro(o, a, b); }\n'
      t=body
      for j,(out,aa,bb) in enumerate([('vpW','vpU','vpV'),('vpV','vpW','vpU')]):
       if mask&(1<<j):
        names=dict(o=out,a=aa,b=bb);t=t.replace('RwV3dCrossProductMacro('+out+', '+aa+', '+bb+');','CrossTrial('+', '.join(names[x] for x in order)+');')
      VS['on_'+''.join(order)+str(mask)]=[(body,h+t)]
    for mask in range(1,4):
     t=body
     for j,(o,aa,bb) in enumerate([('vpW','vpU','vpV'),('vpV','vpW','vpU')]):
      if mask&(1<<j):t=t.replace('RwV3dCrossProductMacro('+o+', '+aa+', '+bb+');','{ const RwV3d *first = '+aa+'; const RwV3d *second = '+bb+'; RwV3dCrossProductMacro('+o+', first, second); }')
     VS['on_local%d'%mask]=[(body,t)]

elif mode == 'format':
    from pathlib import Path
    src=Path('src/rw/plugin/skin2/xbox/skinxboxformat.c').read_text();d=Path('docs/drafts/rw_skinxboxformat_followup.c').read_text();d=d[d.index('/*\n * codfh-match:'):];VS={'ft_base':[(src,d)]}
    a=d.index('// match: __rpSkinXboxGetVertexFormatShader')
    for mask in range(1,8):
     h='';t=d
     if mask&1:
      h+='static __forceinline void StoreTrial(RwInt32 index, const _rpSkinXboxVtxFmt *desc) { rpXboxSkinVertexFormatArray[index].format = *desc; }\n'
      t=t.replace('rpXboxSkinVertexFormatArray[index].format = *desc;','StoreTrial(index, desc);')
     if mask&2:
      h+='static __forceinline DWORD *PointerTrial(RwInt32 index) { return &rpXboxSkinVertexFormatArray[index].handle; }\n'
      t=t.replace('&rpXboxSkinVertexFormatArray[index].handle, 0','PointerTrial(index), 0')
     if mask&4:
      h+='static __forceinline DWORD HandleTrial(RwInt32 index) { return rpXboxSkinVertexFormatArray[index].handle; }\n'
      t=t.replace('return rpXboxSkinVertexFormatArray[index].handle;','return HandleTrial(index);')
     t=t[:a]+h+t[a:]
     VS['ft_%d'%mask]=[(src,t)]

