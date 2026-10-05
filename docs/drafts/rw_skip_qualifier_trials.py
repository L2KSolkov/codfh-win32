from pathlib import Path
s=Path('src/rw/src/plcore/bastream.c').read_text();a=s.index('RwStreamSkip(RwStream *stream, RwUInt32 offset)');b=s.index('\n}\n',a)+3;d=s[a:b];VS={}
for n in range(16):
 u=d
 if n&1:u=u.replace('if (smpMem->position + offset','if (((volatile RwStreamMemory *)smpMem)->position + offset')
 if n&2:u=u.replace('> smpMem->nSize)', '> ((volatile RwStreamMemory *)smpMem)->nSize)')
 if n&4:u=u.replace('smpMem->position += offset;', '((volatile RwStreamMemory *)smpMem)->position += offset;')
 if n&8:u=u.replace('if (smpMem->position + offset', 'if (smpMem->position + *(volatile RwUInt32 *)&offset').replace(')->position + offset',' )->position + *(volatile RwUInt32 *)&offset')
 VS['skipq_%d'%n]=[(d,u)]
