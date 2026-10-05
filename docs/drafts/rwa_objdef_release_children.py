exec(open('docs/drafts/rwa_objdef_release_loop_current.py').read())
base=VS['objrelloop_0'][0][1];VS={}
start=base.index('    rwaLink *child;',base.index('// match: _sub_23DB90'));end=base.index('    if (def->unregister)',start)
loops=[
'''    list = &def->children;
    while (list->next != list) {
        if (!sub_23DB90((rwaObjDef *)((RwUInt8 *)list->next - 0x18))) return FALSE;
    }
''',
'''    rwaLink *child = def->children.next;
    while (child != &def->children) {
        if (!sub_23DB90((rwaObjDef *)((RwUInt8 *)child - 0x18))) return FALSE;
        child = def->children.next;
    }
''',
'''    rwaObjDef *child = (rwaObjDef *)((RwUInt8 *)def->children.next - 0x18);
    while (&child->sibling != &def->children) {
        if (!sub_23DB90(child)) return FALSE;
        child = (rwaObjDef *)((RwUInt8 *)def->children.next - 0x18);
    }
''']
for k,loop in enumerate(loops):
 for n in range(4):
  u=base[:start]+loop+base[end:]
  a=u.index('// match: _sub_23DB90');head=u[:a];body=u[a:]
  if n&1:body=body.replace('return FALSE;', 'goto failed;').replace('    return TRUE;', '    return TRUE;\nfailed:\n    return FALSE;')
  if n&2:body=body.replace('list = (rwaLink *)((RwUInt8 *)def->interfaces + 4);', 'list = &((rwaParamTables *)def->interfaces)->interfaces;')
  VS['objrelchild_%d_%d'%(k,n)]=[(s,head+body)]
