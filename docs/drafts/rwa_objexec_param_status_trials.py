from pathlib import Path
import re
s=Path('src/rwa/rwaobj.c').read_text()
base=s
for addr in ('23F0D0','23F140'):
 s=re.sub(r'// match: _sub_'+addr+r' @.*?(?=// match: |\Z)', '',s,flags=re.S)
d=Path('docs/drafts/rwa_obj_exec_followup.c').read_text().split('// match: _sub_23F140')[0]
d=d.replace('RwBool          status;', 'rwaInstance    *status;').replace('(RwBool)obj','obj')
VS={'oeps_00':[(base,s+'\n'+d)]}
for n in range(1,7):
 u=d
 u=u.replace('sub_23F0D0(rwaInstance *obj,', 'sub_23F0D0(rwaInstance *status,').replace('    rwaInstance    *result = obj;', '    rwaInstance    *obj = status;\n    rwaInstance    *result = obj;').replace('    rwaInstance    *status;\n','')
 u=u.replace('        else status = obj;\n','').replace('    else status = obj;\n','')
 if n in(2,4,6):u=u.replace('obj->def->unk2C', 'status->def->unk2C').replace('unk2C(obj)', 'unk2C(status)')
 if n in(3,4):u=u.replace('    if (!ok)', '    if (ok) {}\n    else')
 if n in(5,6):u=u.replace('        if (!status) result = NULL;', '        result = status ? result : NULL;')
 VS['oeps_%02d'%n]=[(base,s+'\n'+u)]
