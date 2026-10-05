exec(open('docs/drafts/rwa_objexec_flag_trials.py').read());base=VS['of_0'][0][1][len(s)+1:];VS={}
for n in range(6):
 u=base;helper=''
 if n<4:
  helper='static __forceinline RwBool RunObject(rwaInstance *obj) { if (obj->def->unk2C) return obj->def->unk2C(obj); return (RwBool)obj; }\n'
  u=u.replace('        if (obj->def->unk2C) status = obj->def->unk2C(obj);\n        else status = (RwBool)obj;', '        status = RunObject(obj);')
  if n&1:helper=helper.replace('rwaInstance *obj)', 'rwaInstance *arg)').replace('{ if (obj','{ rwaInstance *obj = arg; if (obj')
  if n&2:helper=helper.replace('return (RwBool)obj;', 'return (RwBool)'+('arg' if n&1 else 'obj')+';')
 else:
  u=u.replace('RwBool          status;', 'RwBool          status = (RwBool)obj;').replace('        else status = (RwBool)obj;','').replace('    else status = (RwBool)obj;','')
  if n==5:u=u.replace('    if (!ok)', '    if (ok) goto children;\n    if (!ok)').replace('    cur = obj->subObjs.next;', 'children:\n    cur = obj->subObjs.next;')
 VS['ox_%d'%n]=[(s,s+'\n'+helper+u)]
