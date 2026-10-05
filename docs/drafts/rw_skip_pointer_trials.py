from pathlib import Path
s=Path('src/rw/src/plcore/bastream.c').read_text();a=s.index('RwStreamSkip(RwStream *stream, RwUInt32 offset)');b=s.index('\n}\n',a)+3;d=s[a:b];VS={}
forms=['(RwUInt32)((RwUInt8 *)offset + smpMem->position)', '(RwUInt32)((RwUInt8 *)smpMem->position + offset)', '(RwUInt32)&((RwUInt8 *)offset)[smpMem->position]', '(RwUInt32)&((RwUInt8 *)smpMem->position)[offset]', '(RwUInt32)((char *)offset - (0 - smpMem->position))','(RwUInt32)((RwUInt64)offset + smpMem->position)', '(RwUInt32)((RwInt64)offset + smpMem->position)', '(RwUInt32)((RwInt32)offset + (RwInt32)smpMem->position)']
for n,expr in enumerate(forms):
 for k in range(2):
  u=d.replace('smpMem->position + offset',expr)
  if k:u=u.replace('smpMem->position += offset;', 'smpMem->position = '+expr+';')
  VS['skipp_%d_%d'%(n,k)]=[(d,u)]
