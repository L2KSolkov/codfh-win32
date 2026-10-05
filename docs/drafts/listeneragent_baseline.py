from pathlib import Path
src=Path('src/rwa/unit_23CC10.c').read_text()
draft=Path('docs/drafts/rwa_listener_current_followup.c').read_text()
draft=draft[draft.index('// match:'):]
base=src.replace('// match: _sub_23D150 @',draft+'\n// match: _sub_23D150 @')
base=base.replace('extern RwBool sub_23CC70(rwaInstance *obj, rwaInstance *parent, void *params, void *a, void *b);','extern rwaListener *sub_23CC70(rwaListener *listener);')
base=base.replace('def->create = sub_23CC70;', 'def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_23CC70;')
VS={'listeneragent_baseline':[(src,base)]}
