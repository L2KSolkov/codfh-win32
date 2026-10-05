from pathlib import Path
import re
s=Path('src/rwa/unit_243AE0.c').read_text()
production=s
s=re.sub(r'// match: _sub_243E20 @.*?(?=// match: |\Z)', '',s,flags=re.S)
d=Path('docs/drafts/rwa_iface_followup.c').read_text()
d=d[d.index('// match: _sub_243E20'):d.index('// match: _sub_243FF0')]
anchor='// match: _sub_243EA0 @'
pre=d[:d.index('    if (!def)')]
init=d[d.index('    def->noInputs = 0;'):d.index('    return def;')]
alloc='    def = (RwaObjInterfaceDef *)sub_243670(unk_50708C, rwaMEMHINTDUR_EVENT | rwaID_80A);\n'
VS={'ifnest_00':[(anchor,d+anchor)]}
forms=[
 '    if (!def) {\n'+alloc+'    if (def) {\n    def->flags = 0;\ninitialize:\n'+init+'    return def;\n    }\n    return NULL;\n    }\n    def->flags = 2;\n    goto initialize;\n',
 '    if (!def) {\n'+alloc+'    if (!def) return NULL;\n    def->flags = 0;\ninitialize:\n'+init+'    return def;\n    }\n    else {\n    def->flags = 2;\n    goto initialize;\n    }\n',
 '    if (!def) {\n'+alloc+'    if (def) { def->flags = 0; goto initialize; }\n    return NULL;\n    } else { def->flags = 2; }\ninitialize:\n'+init+'    return def;\n',
 '    if (def) { def->flags = 2; } else {\n'+alloc+'    if (def) { def->flags = 0; } else return NULL;\n    }\n'+init+'    return def;\n',
 '    if (!def) {\n'+alloc+'    if (def) { def->flags = 0;\n'+init+'    return def;\n    }\n    } else {\n    def->flags = 2;\n'+init+'    return def;\n    }\n    return NULL;\n',
 '    if (def) { def->flags = 2;\n'+init+'    return def;\n    }\n'+alloc+'    if (def) { def->flags = 0;\n'+init+'    return def;\n    }\n    return NULL;\n',
]
for i,f in enumerate(forms):
 VS['ifnest_%02d'%(i+1)]=[(anchor,pre+f+'}\n\n'+anchor)]

VS={name:[(production,s)]+edits for name,edits in VS.items()}
