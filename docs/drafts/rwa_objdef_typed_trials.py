exec(open('docs/drafts/rwa_objdef_trials.py').read());VS={}
a=d.index('        rwaParamTables *tables');b=d.index('        if (!(def->flags0C & 1))',a)
for n in range(8):
 block=''
 for field in ['Inputs','Outputs']:
  typ='RwUInt16' if not n&1 else 'RwUInt32'
  block+='''        { rwaParamTables *tables = (rwaParamTables *)def->interfaces;
          rwaParamDef *param = tables->FIELD;
          TYPE count = tables->noCAP;
          if (count) {
            RwUInt32 i = count;
            param += count;
            do { --param; sub_240C30(param); } while (--i);
          }
        }
'''.replace('FIELD',field.lower()).replace('CAP',field).replace('TYPE',typ)
 if n&2:block=block.replace('            RwUInt32 i = count;','            RwUInt32 i;').replace('            param += count;','            param += count;\n            i = count;')
 if n&4:block=block.replace('do { --param; sub_240C30(param); } while (--i);','while (i) { --param; sub_240C30(param); --i; }')
 VS['ot_%d'%n]=[(s,s+'\n'+d[:a]+block+d[b:])]
