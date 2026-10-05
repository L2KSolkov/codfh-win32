from pathlib import Path
s=Path('src/rwa/unit_24CC50.c').read_text();d=Path('docs/drafts/rwa_splitter_draft.c').read_text();f=d[d.index('// match: _sub_24CD50'):d.index('// match: _sub_24CFF0')];VS={}
for n in range(16):
 helper='static __forceinline rwaQueueItem *splitFail(rwaSplitter *obj) { obj->state.starved = TRUE; return NULL; }\n'
 u=f.replace('            obj->state.starved = TRUE;\n            return NULL;', '            return splitFail(obj);')
 if n&1:u=u.replace('            return splitFail(obj);','            item = splitFail(obj);\n            goto done;').replace('    return item;', 'done:\n    return item;')
 if n&2:u=u.replace('    rwaQueueItem *item;', '    rwaQueueItem *item = NULL;')
 if n&4:helper=helper.replace('rwaSplitter *obj', 'rwaSplitterState *state').replace('obj->state.starved','state->starved');u=u.replace('splitFail(obj)','splitFail(&obj->state)')
 if n&8:helper=helper.replace('return NULL;', 'return (rwaQueueItem *)(obj->state.starved - 1);' if not n&4 else 'return (rwaQueueItem *)(state->starved - 1);')
 VS['srh_%d'%n]=[(s,s+'\n'+helper+u)]
