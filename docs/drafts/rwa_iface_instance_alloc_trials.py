from pathlib import Path
import re
from itertools import permutations
s=Path('src/rwa/unit_243AE0.c').read_text()
production=s
s=re.sub(r'// match: _sub_243FF0 @.*?(?=// match: |\Z)', '',s,flags=re.S)
d=Path('docs/drafts/rwa_iface_followup.c').read_text()
d=d[d.index('// match: _sub_243FF0'):]
proto='extern RwaObjInterfaceDef *sub_243BC0(RwaObjInterfaceDef *def, rwaObjDef *objDef, RwBool a);\n'
VS={'iia_base':[(production,s+'\n'+proto+d)]}
a=d.index('    if (allocFunc)');b=d.index('    objInterface->setters',a)
block=d[a:b].replace('goto fail;', 'return NULL;')
params=['RwUInt32 size','void *(*allocFunc)(RwUInt32 size, void *data)','void *data']
args=['size','allocFunc','data']
for n,p in enumerate(permutations(range(3))):
 helper='static __forceinline rwaObjInterface *allocateInterface('+', '.join(params[i] for i in p)+')\n{\n    rwaObjInterface *objInterface;\n'+block+'    return objInterface;\n}\n'
 call='    objInterface = allocateInterface('+', '.join(args[i] for i in p)+');\n    if (!objInterface) goto fail;\n\n'
 u=d[:a]+call+d[b:]
 VS['iia_%02d'%n]=[(production,s+'\n'+proto+helper+u)]
