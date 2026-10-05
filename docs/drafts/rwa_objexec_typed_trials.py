from pathlib import Path
import re
src=Path('src/rwa/rwaobj.c').read_text()
base=src
for addr in ('23F0D0','23F140'):
 src=re.sub(r'// match: _sub_'+addr+r' @.*?(?=// match: |\Z)', '',src,flags=re.S)
draft=Path('docs/drafts/rwa_obj_exec_followup.c').read_text()
overlay=Path('build/tooltmp/rwa_objexec_typed_include');overlay.mkdir(exist_ok=True)
h=Path('src/rwa/rwaint.h').read_text()
for member in ('unk2C','unk30'):
 h=h.replace('RwBool        (*'+member+')(rwaInstance *obj);', 'rwaInstance * (*'+member+')(rwaInstance *obj);')
(overlay/'rwaint.h').write_text(h,encoding='utf-8')
draft=draft.replace('RwBool          status;', 'rwaInstance    *status;').replace('(RwBool)obj','obj')
VS={}
for n in range(4):
 d=draft
 if n==1:d=d.replace('else status = obj;', 'else status = *(rwaInstance *volatile *)&obj;')
 if n==2:d=d.replace('rwaInstance *obj, RwBool ok)', 'rwaInstance *volatile input, RwBool ok)').replace('    rwaInstance    *result = obj;', '    rwaInstance    *obj = input;\n    rwaInstance    *result = obj;').replace('else status = obj;', 'else status = input;')
 if n==3:d=d.replace('rwaInstance *obj, RwBool ok)', 'rwaInstance *input, RwBool ok)').replace('    rwaInstance    *result = obj;', '    rwaInstance    *obj = input;\n    rwaInstance    *result = obj;').replace('else status = obj;', 'else status = input;')
 VS['oet_%02d'%n]=[(base,src+'\n'+d)]
