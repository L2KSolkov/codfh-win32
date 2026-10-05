from pathlib import Path
import re
s=Path('src/rwa/unit_2422B0.c').read_text()
base=s
s=re.sub(r'// match: _sub_242810 @.*?(?=// match: |\Z)', '', s, flags=re.S)
d=Path('docs/drafts/rwa_wave_draft.c').read_text()
d=d[d.index('// match: _sub_242810'):]
head='RwaWave *dword_506FFC;\nRwUInt32 dword_507000;\n'
VS={'upcur_00':[(base,s+'\n'+head+d)]}
for n in range(1,9):
 u=d
 if n in (1,2,3,4):
  u=u.replace('        RwaWave    *result;', '        RwaWave    *result;\n        RwUInt32 uploadOffset;')
  u=u.replace('            offset = sub_2498D0', '            uploadOffset = sub_2498D0')
  e='\n        else { uploadOffset = '+('*(volatile RwUInt32 *)&offset' if n in (2,4) else 'offset')+'; }\n'
  u=u.replace('\n        dword_506FFC = wave;',e+'\n        dword_506FFC = wave;')
  u=u.replace('dword_507000 = offset;', 'dword_507000 = uploadOffset;').replace('upload(wave, offset, buffer, size)', 'upload(wave, uploadOffset, buffer, size)')
  if n in(3,4):u=u.replace('        RwUInt32 uploadOffset;', '        RwUInt32 uploadOffset;\n        void *uploadBuffer;').replace('            buffer = converted;', '            uploadBuffer = converted;').replace('; }\n\n        dword_506FFC', '; uploadBuffer = buffer; }\n\n        dword_506FFC').replace('upload(wave, uploadOffset, buffer, size)', 'upload(wave, uploadOffset, uploadBuffer, size)')
 if n==5:u=u.replace('        dword_506FFC = wave;', '        else { offset = *(volatile RwUInt32 *)&offset; }\n\n        dword_506FFC = wave;')
 if n==6:u=u.replace('RwUInt32 offset, void *buffer, RwUInt32 size)\n{','RwUInt32 volatile offset, void *buffer, RwUInt32 size)\n{',1)
 if n==7:u=u.replace('        dword_506FFC = wave;', '        else { buffer = *(void *volatile *)&buffer; }\n\n        dword_506FFC = wave;')
 if n==8:u=u.replace('RwUInt32 offset, void *buffer, RwUInt32 size)\n{','RwUInt32 offset, void *volatile buffer, RwUInt32 size)\n{',1)
 VS['upcur_%02d'%n]=[(base,s+'\n'+head+u)]
