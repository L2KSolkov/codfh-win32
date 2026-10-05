from pathlib import Path
import re
s=Path('src/rwa/xbox/unit_24DA70.c').read_text()
base=s
for addr in ('24DAD0','24DBA0'):
 s=re.sub(r'// match: _sub_'+addr+r' @.*?(?=// match: |\Z)', '', s, flags=re.S)
d=Path('docs/drafts/rwa_nv_followup.c').read_text()
VS={'nvl_00':[(base,s+'\n'+d)]}
for n in range(1,13):
 u=d
 if n==1:u=u.replace('rwaInstance *obj)', 'rwaInstance *volatile obj)')
 if n==2:u=u.replace('RwaWave *wave, rwaInstance *obj)', 'RwaWave *volatile input, rwaInstance *obj)').replace('    rwaStreamedMemory *memory', '    RwaWave *wave = input;\n    rwaStreamedMemory *memory')
 if n==3:u=u.replace('rwaInstance *obj)', 'rwaInstance *input)').replace('    rwaStreamedMemory *memory', '    rwaInstance *obj = input;\n    rwaStreamedMemory *memory')
 if n==4:u=u.replace('(rwaStreamedMemory *)obj->state', '(rwaStreamedMemory *)((volatile rwaInstance *)obj)->state')
 if n==5:u=u.replace('rwaStreamedMemory *memory = (rwaStreamedMemory *)obj->state;', 'rwaStreamedMemory *memory;\n    obj = (rwaInstance *)obj->state;\n    memory = (rwaStreamedMemory *)obj;')
 if n==6:u=u.replace('rwaStreamedMemory *memory = (rwaStreamedMemory *)obj->state;', 'rwaStreamedMemory *memory;\n    wave = wave;\n    memory = (rwaStreamedMemory *)obj->state;')
 if n==7:u=u.replace('RwaWave *wave, rwaInstance *obj)', 'RwaWave *arg, rwaInstance *obj)').replace('    rwaStreamedMemory *memory', '    register RwaWave *wave = arg;\n    rwaStreamedMemory *memory')
 if n==8:u=u.replace('rwaStreamedMemory *memory = (rwaStreamedMemory *)obj->state;', 'rwaStreamedMemory *memory;\n    memory = (rwaStreamedMemory *)obj->state;\n    obj = NULL;')
 if n==9:u=u.replace('    return wave->buffer ? wave : NULL;', '    if (wave->buffer) { return wave; }\n    else { return NULL; }')
 if n==10:u=u.replace('    return wave->buffer ? wave : NULL;', '    return wave->buffer != NULL ? wave : NULL;')
 if n==11:u=u.replace('if (!dword_51DE60.size\n        && sub_2FD5D0', 'if (!dword_51DE60.size)\n    if (sub_2FD5D0')
 if n==12:u=u.replace('    rwaStreamedMemory *memory = (rwaStreamedMemory *)obj->state;', '    rwaStreamedMemory *memory;\n    RwaWave *ret = wave;\n    memory = (rwaStreamedMemory *)obj->state;').replace('    return wave->buffer ? wave : NULL;', '    return wave->buffer ? ret : NULL;')
 VS['nvl_%02d'%n]=[(base,s+'\n'+u)]
