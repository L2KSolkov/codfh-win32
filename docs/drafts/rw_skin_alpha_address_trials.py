"""Skin-node probes: _XBoxSkinAtomicAllInOneNode 0x2D46F0.
Run pscore.py against src/rw/plugin/skin2/xbox/skinplatform.c.
No candidate improves the 16-line baseline; see questions.md.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
VS={}
call='            _rpSkinXboxSetMaterialColor(mesh->material, geomFlags & rpGEOMETRYMODULATEMATERIALCOLOR);'
loop='for (mesh = resEntryHeader->begin; mesh != resEntryHeader->end; mesh++)\n        {'
for place in range(3):
 for helper in range(3):
  for qual in ['', 'volatile ']:
   h='';expr='&resEntryHeader->vertexAlpha'
   if helper:
    h='static __forceinline '+qual+'RwBool *AlphaFieldTrial(RxXboxResEntryHeader *header) { return &header->vertexAlpha; }\n'
    expr='AlphaFieldTrial(resEntryHeader)'
   decl=qual+'RwBool *vertexAlpha;'
   t=body.replace(loop,loop+'\n            '+decl)
   assignment='vertexAlpha = '+expr+';'
   if place==0:t=t.replace(decl,decl+' '+assignment,1)
   if place==1:t=t.replace(call,'            '+assignment+'\n'+call)
   if place==2:t=t.replace(call,call+'\n            '+assignment)
   t=t.replace('if (resEntryHeader->vertexAlpha ||','if (*vertexAlpha ||')
   if helper==2:
    h+='static __forceinline RwBool AlphaReadTrial('+qual+'RwBool *p) { return *p; }\n'
    t=t.replace('if (*vertexAlpha ||','if (AlphaReadTrial(vertexAlpha) ||')
   VS['av_%d_%d_%d'%(place,helper,bool(qual))]=[(old,h+t)]
