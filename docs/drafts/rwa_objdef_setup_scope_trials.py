exec(open('docs/drafts/rwa_objdef_setup_trials.py').read());VS={}
for n in range(16):
 t=d
 if n&1:
  a=t.index('    for (i = 0; i < noOutputs; i++)');t=t[:a]+t[a:].replace('for (i = 0; i < noOutputs; i++)','{ RwUInt16 j;\n    for (j = 0; j < noOutputs; j++)',1).replace('&outputs[i]','&outputs[j]',1).replace('    def->flags0C |= 1;','    }\n    def->flags0C |= 1;')
 if n&2:
  t=t.replace('    RwUInt16    i;','    RwUInt16    i;\n    RwUInt16 count;')
  a=t.index('    for (i = 0; i < noInputs; i++)');t=t[:a]+'    count = noInputs;\n'+t[a:].replace('noInputs','count')
  a=t.index('    for (',t.index('->noInputs') if '->noInputs' in t else t.index('->count')) if False else 0
  # restore field spelling and introduce output count before output loop scope
  t=t.replace('->count','->noInputs')
  mark='    { RwUInt16 j;' if n&1 else '    for (i = 0; i < noOutputs; i++)'
  pos=t.index(mark);t=t[:pos]+'    count = noOutputs;\n'+t[pos:].replace('noOutputs','count');t=t.replace('->count','->noOutputs')
 if n&4:t=t.replace('            return NULL;','            goto failed;').replace('    return def;\n}', '    return def;\n failed:\n    return NULL;\n}')
 if n&8:t=t.replace('    RwUInt16    i;','    RwUInt32    i;').replace('RwUInt16 j;','RwUInt32 j;')
 VS['ps_%d'%n]=[(s,base+'\n'+t)]
