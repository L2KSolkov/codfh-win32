from pathlib import Path
s=Path('src/rwa/unit_249490.c').read_text();d=Path('docs/drafts/rwa_adpcm_draft.c').read_text();a=d.index('// match: _sub_24BC50');b=d.index('\n}\n',a)+3;body=d[a:b];prefix='extern const RwInt32 unk_42FCB0[][2];\n';VS={}
for n in range(8):
 u=body
 if n&1:u=u.replace('    RwInt32     k0;', '    RwUInt32 remaining = blocks;').replace('while (blocks--)', 'while (remaining--)').replace('k0 = unk_42FCB0[filter][0];', 'blocks = unk_42FCB0[filter][0];').replace('s1 * k0', 's1 * (RwInt32)blocks')
 if n&2:u=u.replace('        k0 = unk_42FCB0[filter][0];\n        k1 = unk_42FCB0[filter][1];', '        k1 = unk_42FCB0[filter][1];\n        k0 = unk_42FCB0[filter][0];').replace('        blocks = unk_42FCB0[filter][0];\n        k1 = unk_42FCB0[filter][1];', '        k1 = unk_42FCB0[filter][1];\n        blocks = unk_42FCB0[filter][0];')
 if n&4:u=u.replace('for (i = 0; i < 14; i++)','for (i = 14; i > 0; i--)')
 VS['adpcmblock_%d'%n]=[(s,s+'\n'+prefix+u)]
