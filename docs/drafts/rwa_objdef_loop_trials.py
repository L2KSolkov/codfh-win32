exec(open('docs/drafts/rwa_objdef_typed_trials.py').read())
u=VS['ot_2'][0][1];VS={}
for n in range(12):
 v=u
 if n<4:
  v=v.replace('if (count) {','if (count > 0) {').replace('do { --param; sub_240C30(param); } while (--i);', ['for (i = 0; i < count; i++) { --param; sub_240C30(param); }','for (i = count; i > 0; i--) { --param; sub_240C30(param); }','while (i > 0) { --param; sub_240C30(param); --i; }','do { --param; sub_240C30(param); } while (--i > 0);'][n])
 else:
  params='rwaParamDef *param, RwUInt16 count' if not n&1 else 'RwUInt16 count, rwaParamDef *param'
  loop='for (i = 0; i < count; i++)' if not n&2 else 'for (i = count; i > 0; i--)'
  helper='static __forceinline void ReleaseParams('+params+') { RwUInt32 i; param += count; '+loop+' { --param; sub_240C30(param); } }\n'
  start=v.index('        { rwaParamTables *tables');end=v.index('        if (!(def->flags0C & 1))',start)
  calls=''
  for f in ['Inputs','Outputs']:
   args='((rwaParamTables *)def->interfaces)->'+f.lower()+', ((rwaParamTables *)def->interfaces)->no'+f
   if n&1:args=', '.join(args.split(', ')[::-1])
   calls+='        ReleaseParams('+args+');\n'
  v=v[:start]+calls+v[end:];v=v.replace('// match: _sub_23DAA0',helper+'\n// match: _sub_23DAA0')
 VS['ol_%d'%n]=[(s,v)]
