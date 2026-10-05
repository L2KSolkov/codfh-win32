exec(open('docs/drafts/rwa_objdef_typed_trials.py').read());u=VS['ot_2'][0][1];VS={}
for n in range(6):
 v=u
 v=v.replace('          if (count) {\n            RwUInt32 i;\n            param += count;\n            i = count;\n            do { --param; sub_240C30(param); } while (--i);\n          }',[
'          { RwUInt32 i; for (i=count; i>0; i--) sub_240C30(&param[i-1]); }',
'          { RwUInt32 i; for (i=0; i<count; i++) sub_240C30(&param[count-i-1]); }',
'          if (count > 0) { RwUInt32 i = count; param += count; do { sub_240C30(--param); } while (--i > 0); }',
'          if (count > 0) { RwUInt32 i; param += count; for (i=count; i>0; i--) sub_240C30(--param); }',
'          { RwUInt32 i = count; param += count; while (i > 0) { sub_240C30(--param); i--; } }',
'          { RwUInt32 i; for(i=count; i>0; i--) { rwaParamDef *p = param+i; sub_240C30(p-1); } }'][n])
 VS['oi_%d'%n]=[(s,v)]
