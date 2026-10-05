exec(open('docs/drafts/rwa_container_set_helper_trials.py').read());VS={}
lo=d.index('        RwInt32     index =');hi=d.index('\n    }\n\n    command->flags',lo);chunk=d[lo:hi].replace('command->entries[i].','entry->')
args={'entry':'rwaNodeSetEntry *entry','trackStart':'RwInt32 trackStart','trackEnd':'RwInt32 trackEnd','kindStart':'RwInt32 kindStart','kindEnd':'RwInt32 kindEnd','channel':'RwInt32 channel','value':'RwReal value'}
orders=[list(args),list(reversed(args)),['entry','channel','value','trackStart','trackEnd','kindStart','kindEnd'],['trackStart','trackEnd','kindStart','kindEnd','channel','value','entry']]
for k,p in enumerate(orders):
 for n in range(4):
  h='static __forceinline void updateEntry('+', '.join(args[x] for x in p)+') {\n'+chunk+'\n}\n'
  if n&1:h=h.replace('if (index < 0)', 'if (index & 0x80000000)')
  if n&2:h=h.replace('entry->value = value;', '*(RwUInt32 *)&entry->value = *(RwUInt32 *)&value;')
  vals={x:x for x in args};vals['entry']='&command->entries[i]'
  u=d[:lo]+'        updateEntry('+', '.join(vals[x] for x in p)+');'+d[hi:]
  VS['cmdrange_%d_%d'%(k,n)]=[(s,s[:a]+h+u+s[b:])]
