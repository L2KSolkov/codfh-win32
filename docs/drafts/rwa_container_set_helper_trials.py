from pathlib import Path
s=Path('src/rwa/unit_2452A0.c').read_text();a=s.index('// Not yet matched: sub_246ED0');b=s.index('// match: _sub_246F80',a);d=s[a:b];VS={}
import itertools
args={'entry':'rwaNodeSetEntry *entry','index':'RwInt32 index','value':'RwReal value'}
old='''            command->entries[i].value = value;
            command->entries[i].track = index | 0x80000000;'''
for k,p in enumerate(itertools.permutations(args)):
 for n in range(4):
  body='entry->value = value; entry->track = index | 0x80000000;'
  if n&1:body='entry->track = index | 0x80000000; entry->value = value;'
  if n&2:body=body.replace('entry->value = value;', '*(RwUInt32 *)&entry->value = *(RwUInt32 *)&value;')
  h='static __forceinline void setEntry('+', '.join(args[x] for x in p)+') { '+body+' }\n'
  vals={'entry':'&command->entries[i]','index':'index','value':'value'}
  u=d.replace(old,'            setEntry('+', '.join(vals[x] for x in p)+');').replace('if (index < 0)', 'if (index & 0x80000000)')
  VS['cmdhelp_%d_%d'%(k,n)]=[(s,s[:a]+h+u+s[b:])]
