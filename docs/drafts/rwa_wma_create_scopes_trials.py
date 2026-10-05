exec(open('docs/drafts/rwa_wma_create_members_trials.py').read())
d=VS['wmcm_16'][0][1].removesuffix(anchor)
VS={}
for n in range(16):
 u=d
 if n&1:
  u=u.replace('    rwaWmaPosition *positions;\n','')
  u=u.replace('    positions =', '    {\n    rwaWmaPosition *positions;\n    positions =',1)
  u=u.replace('    fileName = NULL;', '    }\n    fileName = NULL;')
 if n&2:
  u=u.replace('    rwaWmaContentDesc desc;\n','')
  u=u.replace('    desc.title =', '    {\n    rwaWmaContentDesc desc;\n    desc.title =',1)
  u=u.replace('    if (state->decoder->vtbl->getFileHeader', '    }\n    if (state->decoder->vtbl->getFileHeader',1)
 if n&4:
  for line in ['    RwUInt16    title[128];\n','    RwUInt16    author[128];\n','    RwUInt16    description[128];\n']:
   u=u.replace(line,'')
  u=u.replace('    desc.title =', '    {\n    RwUInt16 title[128], author[128], description[128];\n    desc.title =',1)
  u=u.replace('    if (state->decoder->vtbl->getFileHeader', '    }\n    if (state->decoder->vtbl->getFileHeader',1)
 if n&8:
  u=u.replace('    const RwChar *fileName;\n','').replace('    void       *file;\n','')
  u=u.replace('    fileName = NULL;','    {\n    const RwChar *fileName;\n    void *file;\n    fileName = NULL;')
  u=u.replace('    desc.title =', '    }\n    desc.title =',1) if not n&6 else u.replace('    {\n    '+('rwaWmaContentDesc' if n&2 else 'RwUInt16'), '    }\n    {\n    '+('rwaWmaContentDesc' if n&2 else 'RwUInt16'),1)
 VS['wmcs_%02d'%n]=[(anchor,u+anchor)]
