exec(open('docs/drafts/rwa_listener_current_trials.py').read())
import re
VS={}
for which,body,expected in [('up',up,['at.z','at.y','up.z','up.x','at.y','at.x']),('at',at,['at.z','at.y','up.z','at.z','at.y','at.x'])]:
    lines=body.splitlines()
    dirty=next(l for l in lines if 'dirty' in l)
    for pos in range(5):
        for mask in range(64):
            b=body
            expr=list(re.finditer(r'listener->\w+\.\w+ \* listener->\w+\.\w+',b))
            for i,m in reversed(list(enumerate(expr))):
                if mask&(1<<i):
                    term='listener->'+expected[i]
                    b=b[:m.start()]+m.group().replace(term,'*(const volatile RwReal *)&'+term)+b[m.end():]
            b=b.replace(dirty+'\n','')
            if pos<4:
                target=['    listener->'+which+' = *value;', '    listener->right.x =', '    listener->right.y =', '    listener->right.z ='][pos]
                idx=b.index(target)
                b=b[:idx]+dirty+'\n'+b[idx:]
            else:b=b.replace('    return listener;',dirty+'\n    return listener;')
            VS['listeneragent_'+which+'_%d_%02d'%(pos,mask)]=[(src,base.replace(body,b))]
