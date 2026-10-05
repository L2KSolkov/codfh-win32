exec(open('docs/drafts/rwa_objexec_trials.py').read());VS={}
a=d.index('    if (ok)');b=d.index('    cur = obj->subObjs.next;',a)
old=d[a:b]
new='''    if (!ok)
    {
        if (obj->def->unk2C) status = obj->def->unk2C(obj);
        else status = (RwBool)obj;
        if (!status) result = NULL;
    }
    else status = (RwBool)obj;

'''
b=d[:d.index('// match: _sub_23F140')].replace(old,new)
for n in range(8):
 u=b
 if n&1:u=u.replace('RwBool          status;', 'rwaInstance *status;').replace('status = obj->def->unk2C(obj);','status = (rwaInstance *)obj->def->unk2C(obj);').replace('status = sub->def->unk2C(sub);','status = (rwaInstance *)sub->def->unk2C(sub);').replace('(RwBool)obj','obj')
 if n&2:u=u.replace('sub_23F0D0(rwaInstance *obj,','sub_23F0D0(rwaInstance *arg,').replace('    rwaInstance    *result = obj;', '    rwaInstance *obj = arg;\n    rwaInstance    *result = obj;')
 if n&4:u=u.replace('    else status = '+('obj' if n&1 else '(RwBool)obj')+';', '    else { status = '+('obj' if n&1 else '(RwBool)obj')+'; }')
 VS['of_%d'%n]=[(s,s+'\n'+u)]
