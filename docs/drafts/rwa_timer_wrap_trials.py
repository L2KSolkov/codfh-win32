from pathlib import Path
s=Path('src/rwa/rwatimer.c').read_text();d=Path('docs/drafts/rwa_timer_draft.c').read_text().replace('dword_507178','(RwUInt32)qword_507178');VS={'timer_base':[(s,s+'\n'+d)]}
for n in range(16):
 ty='RwUInt64' if n&1 else 'RwUInt32';ret='RwUInt64' if n&2 else 'RwUInt32'
 h='static __forceinline '+ret+' wrapTicks('+ty+' start) { return 0xFFFFFFFF - start; }\n'
 u=d.replace('0xFFFFFFFF - start','wrapTicks(start)')
 if n&4:u=u.replace('(now + (wrapTicks(start)))','((wrapTicks(start)) + now)')
 if n&8:h=h.replace('0xFFFFFFFF - start','~start')
 VS['timer_h%d'%n]=[(s,s+'\n'+h+u)]
