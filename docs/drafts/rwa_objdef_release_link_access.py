exec(open('docs/drafts/rwa_objdef_release_loop_current.py').read())
base=VS['objrelloop_0'][0][1];VS={}
for n in range(8):
 a=base.index('// match: _sub_23DB90');u=base[a:]
 if n&1:u=u.replace('child = def->children.next', 'child = *(rwaLink *volatile *)&def->children.next')
 if n&2:u=u.replace('list->next', '(*(rwaLink *volatile *)&list->next)')
 if n&4:u=u.replace('    sub_23DB30(def);', '    { void (*release)(rwaObjDef *) = sub_23DB30; release(def); }')
 VS['objrellink_%d'%n]=[(s,base[:a]+u)]
