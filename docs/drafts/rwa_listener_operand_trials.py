exec(open('docs/drafts/rwa_listener_current_trials.py').read())
import re
VS={}
for mask in range(64):
    b=base
    for body in [up,at]:
        expressions=list(re.finditer(r'listener->\w+\.\w+ \* listener->\w+\.\w+',body))
        assert len(expressions)==6
        new=body
        for i,m in reversed(list(enumerate(expressions))):
            if mask & (1<<i):
                operands=m.group().split(' * ')
                new=new[:m.start()]+operands[1]+' * '+operands[0]+new[m.end():]
        b=b.replace(body,new)
    VS['liso_%02d'%mask]=[(src,b)]
