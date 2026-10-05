exec(open('docs/drafts/rwa_wma_create_current_trials.py').read())
import itertools,re
VS={}
for n,names in enumerate(itertools.permutations(['title','author','description'])):
 mp=dict(zip(['title','author','description'],names))
 u=re.sub(r'(?<![.>])\b(title|author|description)\b',lambda m:mp[m[0]],d)
 VS['wmcl_a%d'%n]=[(anchor,u+anchor)]
for n,names in enumerate(itertools.permutations(['positions','desc','fileName','file'])):
 mp=dict(zip(['positions','desc','fileName','file'],names))
 u=re.sub(r'(?<![.>])\b(positions|desc|fileName|file)\b',lambda m:mp[m[0]],d)
 VS['wmcl_b%02d'%n]=[(anchor,u+anchor)]
decls=['    rwaWmaPosition *positions;','    const RwChar *fileName;','    void       *file;','    rwaWmaContentDesc desc;']
for n,order in enumerate(itertools.permutations(decls)):
 u=d
 for a in decls:u=u.replace(a+'\n','')
 u=u.replace('    RwUInt32    i;', '\n'.join(order)+'\n    RwUInt32    i;')
 VS['wmcl_d%02d'%n]=[(anchor,u+anchor)]
