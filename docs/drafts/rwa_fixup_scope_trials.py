exec(open('docs/drafts/rwa_fixup_trials.py').read());VS={}
import re
loops=[]
for m in re.finditer(r'^    for \(i =',d,re.M):
 a=d.index('{',m.start());level=0
 for end in range(a,len(d)):
  level+=(d[end]=='{')-(d[end]=='}')
  if level==0:break
 loops.append((m.start(),end+1))
for mask in range(1<<len(loops)):
 u=d
 for k,(a,b) in reversed(list(enumerate(loops))):
  if mask&(1<<k):u=u[:a]+'    { RwUInt32 i;\n'+u[a:b]+'\n    }'+u[b:]
 VS['fs_%03d'%mask]=[(s,s+'\n'+u)]
