from pathlib import Path
s=Path('src/rwa/unit_249490.c').read_text();d=Path('docs/drafts/rwa_adpcm_draft.c').read_text();a=d.index('RwUInt8\nsub_24BD30(');b=d.index('\n}\n',a)+3;body=d[a:b];VS={}
for n in range(16):
 u=body
 if n&1:u=u.replace('*predicted = s - step + diff;', 's -= step;\n        s += diff;\n        *predicted = s;')
 if n&2:u=u.replace('*predicted = step - diff + s;', 'step -= diff;\n        step += s;\n        *predicted = step;')
 if n&4:u=u.replace('step = word_42FD38[*index]', 'step = *(const volatile RwInt16 *)&word_42FD38[*index]')
 if n&8:u=u.replace('diff = s - *predicted;', 'diff = s - *(volatile RwInt32 *)predicted;')
 VS['imaupdate_%d'%n]=[(s,s+'\n'+u)]
