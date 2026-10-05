from pathlib import Path
s=Path('src/rwa/unit_23FAD0.c').read_text()
base=s
if '// match: _sub_23FC00' in base:
 start=base.index('// match: _sub_23FC00')
 end=base.find('// match:',start+10)
 base=base[:start]+(base[end:] if end>=0 else '')
d=Path('docs/drafts/rwa_stream_draft.c').read_text().split('// match: _sub_23FEE0')[0]
h='extern void sub_245E90(rwaStreamPlayer *player, const void *unusedSet);\n'
VS={}
for n in range(16):
 u=d
 if n&1:u=u.replace('dword_506B38--;', '(*(volatile RwInt32 *)&dword_506B38)--;')
 if n&2:u=u.replace('WaitForSingleObject(hSemaphore,', 'WaitForSingleObject(*(void *volatile *)&hSemaphore,')
 if n&4:u=u.replace('    dword_506B38--;', '    RwInt32 count = dword_506B38;\n    count--;\n    dword_506B38 = count;').replace('    (*(volatile RwInt32 *)&dword_506B38)--;', '    RwInt32 count = *(volatile RwInt32 *)&dword_506B38;\n    count--;\n    *(volatile RwInt32 *)&dword_506B38 = count;')
 if n&8:u=u.replace('sub_23FC00(rwaStream *stream)', 'sub_23FC00(rwaStream *volatile input)').replace('{\n', '{\n    rwaStream *stream;\n',1).replace('    WaitForSingleObject', '    stream = input;\n    WaitForSingleObject',1)
 VS['unlinkaccess_%d'%n]=[(s,base+'\n'+h+u)]
