exec(open('docs/drafts/rwa_objdef_release_access.py').read())
base=VS['objrelaccess_3'][0][1];VS={}
for n in range(8):
 u=base
 u=u.replace('    while (def->children.next != &def->children)', '    rwaLink *child;\n\n    while ((child = def->children.next) != &def->children)').replace('(RwUInt8 *)def->children.next - 0x18', '(RwUInt8 *)child - 0x18')
 if n&1:u=u.replace('    rwaLink *child;', '    rwaLink *child;\n    rwaLink *head = &def->children;').replace('(child = def->children.next) != &def->children', '(child = head->next) != head')
 if n&2:u=u.replace('list = (rwaLink *)((RwUInt8 *)def->interfaces + 4);', 'list = &((rwaParamTables *)def->interfaces)->interfaces;')
 if n&4:u=u.replace('sub_23DB90(rwaObjDef *def)', 'sub_23DB90(rwaObjDef *input)').replace('    rwaLink    *list;', '    rwaObjDef *def = input;\n    rwaLink    *list;')
 VS['objrelloop_%d'%n]=[(s,u)]
