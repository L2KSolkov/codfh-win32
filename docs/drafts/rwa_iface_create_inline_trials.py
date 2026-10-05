exec(open('docs/drafts/rwa_iface_create_nested_trials.py').read())
VS={}
for n in range(8):
 u=d
 if n<4:
  helper='static __forceinline RwaObjInterfaceDef *prepareInterface(RwaObjInterfaceDef *def)\n{\n'+d[d.index('    if (!def)'):d.index('    def->noInputs')]+ '    return def;\n}\n'
  if n&1:helper=helper.replace('if (!def)\n    {', 'if (def) { def->flags = 2; return def; }\n    {',1).replace('    else\n    {\n        def->flags = 2;\n    }\n','')
  if n&2:helper=helper.replace('return NULL;', 'return def;')
  u=helper+pre+'    def = prepareInterface(def);\n    if (!def) return NULL;\n'+init+'    return def;\n}\n'
 else:
  helper='static __forceinline RwaObjInterfaceDef *initializeInterface(RwaObjInterfaceDef *def)\n{\n'+init+'    return def;\n}\n'
  if n==4:f='    if (!def) {\n'+alloc+'    if (!def) return NULL;\n    def->flags = 0;\n    return initializeInterface(def);\n    }\n    def->flags = 2;\n    return initializeInterface(def);\n'
  if n==5:f='    if (def) {\n    def->flags = 2;\n    return initializeInterface(def);\n    }\n'+alloc+'    if (!def) return NULL;\n    def->flags = 0;\n    return initializeInterface(def);\n'
  if n==6:f='    if (!def) {\n'+alloc+'    if (def) {def->flags = 0;\n    return initializeInterface(def);\n    } return NULL;\n    }\n    def->flags = 2;\n    return initializeInterface(def);\n'
  if n==7:f=d[d.index('    if (!def)'):d.index('    def->noInputs')]+'    return initializeInterface(def);\n'
  u=helper+pre+f+'}\n'
 VS['ifin_%02d'%n]=[(anchor,u+'\n'+anchor)]
for n in range(4):
 f='    switch ('+('def != NULL' if n&1 else 'def == NULL')+') {\n    case '+('0' if n&1 else '1')+':\n'+alloc+'    if (!def) return NULL;\n    def->flags = 0;\n    break;\n    default: def->flags = 2; break;\n    }\n'+init+'    return def;\n'
 if n&2:f=f.replace('if (!def) return NULL;', 'if (!def) goto failed;')+'failed:\n    return NULL;\n'
 VS['ifsw_%02d'%n]=[(anchor,pre+f+'}\n\n'+anchor)]

VS={name:[(production,s)]+edits for name,edits in VS.items()}
