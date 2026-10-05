exec(open('docs/drafts/rwa_listener_current_trials.py').read())
import re
VS={}
expected_up=['at.z','at.y','up.z','up.x','at.y','at.x']
expected_at=['at.z','at.y','up.z','at.z','at.y','at.x']
for mask in range(64):
    b=base
    for body,expected in [(up,expected_up),(at,expected_at)]:
        expr=list(re.finditer(r'listener->\w+\.\w+ \* listener->\w+\.\w+',body))
        new=body
        for i,m in reversed(list(enumerate(expr))):
            if mask&(1<<i):
                term='listener->'+expected[i]
                assert term in m.group()
                text=m.group().replace(term,'*(const volatile RwReal *)&'+term)
                new=new[:m.start()]+text+new[m.end():]
        b=b.replace(body,new)
    VS['lisr_%02d'%mask]=[(src,b)]
