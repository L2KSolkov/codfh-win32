from pathlib import Path
s=Path('src/rwa/rwaobjdef.c').read_text()
base=s
if '// match: _sub_23D8B0' in base:
 a=base.index('// match: _sub_23D8B0')
 b=base.index('// match: _sub_23D940',a)
 base=base[:a]+base[b:]
d=Path('docs/drafts/rwa_instance_free_draft.c').read_text();VS={}
for n in range(8):
 u=d
 if n&1:u=u.replace('    rwaObjDef *def = obj->def;', '    RwUInt32 flags = obj->flags;\n    rwaObjDef *def = obj->def;').replace('if (obj->flags & 8)', 'if (flags & 8)').replace('if (obj->flags & 0x10)', 'if (flags & 0x10)').replace('sub_23F300(def, obj->flags & 7,', 'sub_23F300(def, flags & 7,')
 if n&2:u=u.replace('if (def->instances && (!release || !(obj->flags & 0x20)))', 'if (!def->instances || (release && (obj->flags & 0x20)))\n    {\n        if (release) release(memory, data);\n        return;\n    }\n    else').replace('    else if (release)\n    {\n        release(memory, data);\n    }','')
 if n&4:u=u.replace('            sub_2437A0(def->instances, memory);', '            sub_2437A0(def->instances, memory);\n            return;').replace('            sub_2444A0(def->instances, memory);', '            sub_2444A0(def->instances, memory);\n            return;')
 VS['instfree_%d'%n]=[(s,base+'\n'+u)]
