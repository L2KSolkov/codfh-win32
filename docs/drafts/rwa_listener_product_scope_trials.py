exec(open('docs/drafts/rwa_listener_current_trials.py').read())
import re
VS={}
for style in range(4):
    for mask in range(1,8):
        b=base
        for body in [up,at]:
            new=body
            matches=list(re.finditer(r'    listener->right\.([xyz]) = (.*?);',body))
            helpers=''
            for bit,m in reversed(list(enumerate(matches))):
                if not mask&(1<<bit): continue
                axis,expr=m.group(1,2)
                first,second=expr.split(' - ')
                if style==0: code='    { RwReal v = '+first+'; v -= '+second+'; listener->right.'+axis+' = v; }'
                if style==1: code='    { RwReal p = '+first+'; RwReal q = '+second+'; listener->right.'+axis+' = p - q; }'
                if style==2: code='    { RwReal v = '+expr+'; listener->right.'+axis+' = v; }'
                if style==3:
                    name='component_'+axis+('up' if body==up else 'at')
                    helpers+='static __forceinline RwReal '+name+'(const RwaV3d *a, const RwaV3d *b)\n{\n    return '+expr.replace('listener->up.','a->').replace('listener->at.','b->')+';\n}\n\n'
                    code='    listener->right.'+axis+' = '+name+'(&listener->up, &listener->at);'
                new=new[:m.start()]+code+new[m.end():]
            b=b.replace(body,helpers+new)
        VS['liss_%d_%d'%(style,mask)]=[(src,b)]
