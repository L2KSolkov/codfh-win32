from pathlib import Path
import re
s=Path('src/rwa/unit_243AE0.c').read_text()
production=s
s=re.sub(r'// match: _sub_243BC0 @.*?(?=// match: |\Z)', '',s,flags=re.S)
s=s.replace('// match: _RwaListenerInterfaceRegister_0 @','extern RwaObjInterfaceDef *sub_243BC0(RwaObjInterfaceDef *, rwaObjDef *, RwBool);\n// match: _RwaListenerInterfaceRegister_0 @',1)
d=Path('docs/drafts/rwa_iface_followup.c').read_text().split('// match: _sub_243E20')[0]
VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('tables->inputs[j].uuid', '(*(rwaParamDef *volatile *)&tables->inputs)[j].uuid')
 if n&2:u=u.replace('def->inputs[i].uniqueID.uuid', '(*(_rwaParamID *volatile *)&def->inputs)[i].uniqueID.uuid')
 if n&4:u=u.replace('    for (i = 0; i < count; i++)','    { RwUInt32 k;\n    for (k = 0; k < count; k++)',1).replace('inputs[i]', 'inputs[k]').replace(')[i].uniqueID.uuid', ')[k].uniqueID.uuid').replace('    count = def->noOutputs;', '    }\n    count = def->noOutputs;')
 VS['ica_%02d'%n]=[(production,s+'\n'+u)]
