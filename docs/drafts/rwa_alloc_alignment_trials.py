exec(open('docs/drafts/rwa_alloc_pointer_trials.py').read())
prior=VS;VS={}
helper='static __forceinline RwUInt32 rwaFreeListBlockData(rwaFreeListBlock *block, RwUInt32 size, RwUInt32 alignment) { return ((RwUInt32)block + 8 + size + alignment - 1) & ~(alignment - 1); }\n'
for name, edits in prior.items():
 u=edits[0][1].replace('// match: _sub_243670', helper+'\n// match: _sub_243670')
 VS[name.replace('flalloc','flalign')]=[(s,u)]
