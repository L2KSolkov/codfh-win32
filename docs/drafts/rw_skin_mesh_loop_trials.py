"""Skin-node context probes: _XBoxSkinAtomicAllInOneNode 0x2D46F0
against src/rw/plugin/skin2/xbox/skinplatform.c with pscore.py.
No exact match; see questions.md.
"""
exec(open('docs/drafts/rw_skin_node_trials.py').read())
VS={}
needle='for (mesh = resEntryHeader->begin; mesh != resEntryHeader->end; mesh++)'
a=body.index(needle);start=body.index('{',a);depth=1;b=start+1
while depth:
 if body[b]=='{':depth+=1
 if body[b]=='}':depth-=1
 b+=1
chunk=body[start+1:b-1]
forms=[
'mesh = resEntryHeader->begin; while (mesh != resEntryHeader->end) {'+chunk+' ++mesh; }',
'mesh = resEntryHeader->begin; if (mesh != resEntryHeader->end) { do {'+chunk+' ++mesh; } while (mesh != resEntryHeader->end); }',
'mesh = resEntryHeader->begin; if (mesh == resEntryHeader->end) {} else { do {'+chunk+' mesh++; } while (mesh != resEntryHeader->end); }',
'for (mesh = resEntryHeader->begin; ; mesh++) { if (mesh == resEntryHeader->end) break; '+chunk+' }',
'mesh = resEntryHeader->begin; for (;;) { if (mesh == resEntryHeader->end) break; '+chunk+' mesh++; }']
for k,f in enumerate(forms):
 VS['ml_%d'%k]=[(old,body[:a]+f+body[b:])]
