exec(open('docs/drafts/rwa_objdef_release_loop_current.py').read())
base=VS['objrelloop_0'][0][1];VS={}
for n in range(16):
 u=base
 if n&1:u=u.replace('sub_23DB90(rwaObjDef *def)', 'sub_23DB90(rwaObjDef *volatile input)').replace('    rwaLink    *list;', '    rwaObjDef *def = input;\n    rwaLink    *list;')
 if n&2:u=u.replace('list = (rwaLink *)((RwUInt8 *)def->interfaces + 4);', 'list = &((rwaParamTables *)def->interfaces)->interfaces;')
 if n&4:u=u.replace('    rwaLink    *list;','').replace('        list =', '        rwaLink *list =')
 if n&8:u=u.replace('def->interfaces + 4)', 'def->interfaces + 4)').replace('(rwaParamTables *)def->interfaces', '(rwaParamTables *)(*(void *volatile *)&def->interfaces)').replace('(RwUInt8 *)def->interfaces', '(RwUInt8 *)(*(void *volatile *)&def->interfaces)')
 VS['objrelscope_%d'%n]=[(s,u)]
