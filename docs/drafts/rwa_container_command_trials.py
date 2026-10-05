from pathlib import Path
s=Path('src/rwa/unit_2452A0.c').read_text();a=s.index('// Not yet matched: sub_246ED0');b=s.index('// match: _sub_246F80',a);d=s[a:b];VS={'cmd_base':[(s,s)]}
for n in range(8):
 u=d
 if n&1:u=u.replace('const rwaNodeSet *set,', 'const rwaNodeSet *arg,').replace('    RwInt32     trackEnd = set->numNodes;', '    const rwaNodeSet *set = arg;\n').replace('    if (track != -1)', '    arg = (const rwaNodeSet *)set->numNodes;\n    if (track != -1)').replace('trackEnd = track + 1;', 'arg = (const rwaNodeSet *)(track + 1);').replace('index < trackEnd', 'index < (RwInt32)arg')
 if n&2:u=u.replace('    RwUInt32    i = 0;', '    RwInt32    i = 0;')
 if n&4:u=u.replace('command->entries[i].value = value;', '*(RwUInt32 *)&command->entries[i].value = *(RwUInt32 *)&value;')
 VS['cmd_%d'%n]=[(s,s[:a]+u+s[b:])]
