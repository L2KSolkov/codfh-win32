from pathlib import Path
s=Path('src/rwa/rwaobjdef.c').read_text();d=Path('docs/drafts/rwa_objdef_draft.c').read_text();d=d[d.index('extern RwBool _rwaParamTypeHandleRefreshType'):d.index('extern RwUInt32 dword_5069A4;')]
base=s
if '// match: __rwaObjDefSetupParams' in base:
 a=base.index('// match: __rwaObjDefSetupParams');b=base.index('\n}\n',a)+3
 base=base[:a]+base[b:]
d=d.replace('->inputs + noInputs * sizeof(rwaParamDef)', '->inputs + noInputs').replace('= (RwUInt8 *)inputs;', '= inputs;').replace('= (RwUInt8 *)outputs;', '= outputs;')
d=d.replace('extern RwBool _rwaParamTypeHandleRefreshType(void *handle);','extern RwaParamTypeHandle *_rwaParamTypeHandleRefreshType(RwaParamTypeHandle *handle);').replace('_rwaParamTypeHandleRefreshType(&param->type)','_rwaParamTypeHandleRefreshType((RwaParamTypeHandle *)&param->type)')
VS={'op_base':[(s,base+'\n'+d)]}
