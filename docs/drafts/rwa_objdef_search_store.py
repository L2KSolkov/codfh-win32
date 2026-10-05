exec(open('docs/drafts/rwa_objdef_search_slots.py').read())
base=VS['objsearchslot_3'][0][1];VS={}
for n in range(8):
 u=base
 if n&1:u=u.replace('    def = root;', '    *(rwaObjDef *volatile *)&def = root;')
 if n&2:u=u.replace('    self = (RwInt32)&def->children;', '    *(volatile RwInt32 *)&self = (RwInt32)&def->children;')
 if n&4:u=u.replace('    rwaObjDef *root = def;', '    rwaObjDef *root;\n    root = *(rwaObjDef *volatile *)&def;')
 VS['objsearchstore_%d'%n]=[(s,u)]
