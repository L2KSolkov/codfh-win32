exec(open('docs/drafts/rwa_fixup_pointer_trials.py').read());b=VS['fp_1'][0][1][len(s)+1:];VS={}
for n in range(8):
 u=b
 if n&1:u=u.replace('    RwUInt32    i;\n    RwUInt32    j;', '    RwUInt32    j;\n    RwUInt32    i;')
 if n&2:u=u.replace('    RwUInt32    j;', '    RwInt32     j;')
 if n&4:u=u.replace('    { RwUInt32 i;', '    { RwInt32 i;')
 VS['fc_%d'%n]=[(s,s+'\n'+u)]
