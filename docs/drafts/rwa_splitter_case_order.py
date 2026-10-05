exec(open('docs/drafts/rwa_splitter_forward_tail.py').read())
from itertools import permutations
VS={}
start=d.index('            case 3:');end=d.index('\n        }',start)
starts=[d.index('            case %d:'%k) for k in [3,4,7,8]]+[end]
cases=[d[starts[i]:starts[i+1]] for i in range(4)]
for k,p in enumerate(permutations(range(4))):
 for n in range(2):
  u=d[:start]+''.join(cases[i] for i in p)+d[end:]
  if n:u=u.replace('                    break;\n                }\n                if (mode == 1)', '                }\n                if (mode == 1)')
  VS['splitorder_%d_%d'%(k,n)]=[(s,s+'\n'+u)]
