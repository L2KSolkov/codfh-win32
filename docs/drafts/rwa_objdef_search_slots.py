from pathlib import Path
s=Path('src/rwa/rwaobjdef.c').read_text();d=Path('docs/drafts/rwa_objdef_release_followup.c').read_text();d=d[:d.index('extern void sub_240C30')];VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('    rwaLink    *cur;', '    rwaLink    *cur;\n    rwaObjDef *root = def;').replace('    if (!def)\n    {\n        def = dword_516C60;\n    }', '    if (!root) root = dword_516C60;\n    def = root;')
 if n&2:u=u.replace('    for (cur = def->children.next; cur != &def->children; cur = cur->next)', '    self = (RwInt32)&def->children;\n    for (cur = ((rwaLink *)self)->next; cur != (rwaLink *)self; cur = cur->next)')
 if n&4:u=u.replace('sub_23D970(rwaObjDef *def,', 'sub_23D970(rwaObjDef *volatile def,')
 VS['objsearchslot_%d'%n]=[(s,s+'\n'+u)]
