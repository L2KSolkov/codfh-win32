from pathlib import Path
import re
s=Path('src/rwa/rwaobj.c').read_text()
base=s
for addr in ('23F0D0','23F140'):
 s=re.sub(r'// match: _sub_'+addr+r' @.*?(?=// match: |\Z)', '',s,flags=re.S)
d=Path('docs/drafts/rwa_obj_exec_followup.c').read_text().split('// match: _sub_23F140')[0]
VS={}
for n in range(10):
 u=d
 if n==1:u=u.replace('(RwBool)obj', '(RwBool)*(rwaInstance *volatile *)&obj')
 if n==2:u=u.replace('rwaInstance *obj,', 'rwaInstance *volatile arg,').replace('    rwaInstance    *result', '    rwaInstance *obj = arg;\n    rwaInstance    *result').replace('(RwBool)obj', '(RwBool)arg')
 if n==3:u=u.replace('rwaInstance *obj,', 'rwaInstance *volatile obj,')
 if n==4:u=u.replace('rwaInstance *obj,', 'rwaInstance *arg,').replace('    rwaInstance    *result', '    rwaInstance *obj = arg;\n    rwaInstance    *result').replace('(RwBool)obj', '(RwBool)*(rwaInstance *volatile *)&arg')
 if n in(5,6):
  u=u.replace('RwBool          status;', 'rwaInstance *status;').replace('(RwBool)obj','obj').replace('status = obj->def->unk2C(obj);','status = (rwaInstance *)obj->def->unk2C(obj);').replace('status = sub->def->unk2C(sub);','status = (rwaInstance *)sub->def->unk2C(sub);')
  if n==6:u=u.replace('else status = obj;', 'else status = *(rwaInstance *volatile *)&obj;')
 if n==7:u=u.replace('        else status = (RwBool)obj;', '        else status = (RwBool)*(rwaInstance *volatile *)&obj;')
 if n==8:u=u.replace('    else status = (RwBool)obj;', '    else status = (RwBool)*(rwaInstance *volatile *)&obj;',1)
 if n==9:u=u.replace('    else status = (RwBool)obj;', '    else status = (RwBool)*(rwaInstance *volatile *)&obj;')
 VS['oer_%02d'%n]=[(base,s+'\n'+u)]
