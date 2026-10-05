exec(open('docs/drafts/rwa_instance_free_trials.py').read())
VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('rwaInstance *input,', 'rwaInstance *volatile input,')
 if n&2:u=u.replace('!(obj->flags & 0x20)', '!(((volatile rwaInstance *)obj)->flags & 0x20)')
 if n&4:u=u.replace('    rwaInstance *obj = input;', '    rwaInstance *obj = input;\n    RwUInt32 offset;').replace('(RwUInt32 *)&input','&offset')
 VS['instfreeaccess_%d'%n]=[(s,base+'\n'+u)]
