exec(open('docs/drafts/rwa_objdef_trials.py').read());VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('    rwaLink    *cur;','    rwaLink    *cur;\n    rwaLink *head;').replace('    for (cur = def->children.next; cur != &def->children; cur = cur->next)','    head = &def->children;\n    for (cur = head->next; cur != head; cur = cur->next)')
 if n&2:u=u.replace('sub_23D970(rwaObjDef *def,','sub_23D970(rwaObjDef *root,',1).replace('    rwaLink    *cur;','    rwaObjDef *def = root;\n    rwaLink    *cur;',1)
 if n&4:u=u.replace('    if (!def)\n    {\n        def = dword_516C60;\n    }','    def = def ? def : dword_516C60;')
 VS['os_%d'%n]=[(s,s+'\n'+u)]
