"""Run with pscore.py: _XBoxSkinAtomicAllInOneNode 0x2D46F0
src/rw/plugin/skin2/xbox/skinplatform.c. These are unmatched experiments.
"""
from pathlib import Path
src=Path('src/rw/plugin/skin2/xbox/skinplatform.c').read_text()
d=Path('docs/drafts/rw_skinplatform_draft.c').read_text()
body=d[d.index('// match: _XBoxSkinAtomicAllInOneNode'):d.index('// match: _XBoxSkinAtomicAllInOnePipelineInit')].replace('static RwBool','RwBool')
a=src.index('/* The node body');b=src.index('// match: _XBoxSkinAtomicAllInOnePipelineInit',a)
old=src[a:b]
VS={'sn_base':[(old,body)]}
for i,expr in enumerate(['*(bone + skin->skinSplitData.matrixRemapIndices)', '*(skin->skinSplitData.matrixRemapIndices + bone)', 'skin->skinSplitData.matrixRemapIndices[(RwInt32)bone]']):
 VS['sn_remap%d'%i]=[(old,body.replace('skin->skinSplitData.matrixRemapIndices[bone]',expr))]
for typ in ['RwInt32','RwUInt16','RwUInt8']:
 VS['sn_bone_'+typ]=[(old,body.replace('RwUInt32    bone = rle[0];',typ+' bone = rle[0];'))]
for i,loop in enumerate(['for (mesh = resEntryHeader->begin; resEntryHeader->end != mesh; ++mesh)',
 'for (mesh = resEntryHeader->begin; mesh < resEntryHeader->end; mesh++)',
 'for (mesh = resEntryHeader->begin; mesh != ((RxXboxResEntryHeader *)(resEntry + 1))->end; mesh++)']):
 VS['sn_loop%d'%i]=[(old,body.replace('for (mesh = resEntryHeader->begin; mesh != resEntryHeader->end; mesh++)',loop))]
