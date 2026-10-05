exec(open('docs/drafts/rwa_listener_current_trials.py').read())
setup_unit=src.replace('// match: _sub_23D150 @',setup+'// match: _sub_23D150 @')
setup_unit=setup_unit.replace('extern RwBool sub_23CC70(rwaInstance *obj, rwaInstance *parent, void *params, void *a, void *b);', 'extern rwaListener *sub_23CC70(rwaListener *listener);')
setup_unit=setup_unit.replace('def->create = sub_23CC70;', 'def->create = (RwBool (*)(rwaInstance *, rwaInstance *, void *, void *, void *))sub_23CC70;')
VS={'lisset_base':[(src,setup_unit)]}
