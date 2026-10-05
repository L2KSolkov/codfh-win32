exec(open('docs/drafts/rwa_listener_current_trials.py').read())
import re
VS={}
def products(s):return '\n'.join(l for l in s.splitlines() if 'listener->right.' in l)+'\n'
for form in range(5):
    b=base
    for body in [up,at]:
        old=products(body)
        fields=old.replace('listener->right.','o->').replace('listener->up.','a->').replace('listener->at.','b->')
        if form==0:
            new='    {\n    RwaV3d *o = &listener->right;\n    const RwaV3d *a = &listener->up, *b = &listener->at;\n'+fields+'    }\n'
        else:
            name='cross_'+('up' if body==up else 'at')
            decl='__inline' if form==1 else '__forceinline'
            args='RwaV3d *o, const RwaV3d *a, const RwaV3d *b'
            callargs='&listener->right, &listener->up, &listener->at'
            if form==3:
                args='const RwaV3d *a, const RwaV3d *b, RwaV3d *o'
                callargs='&listener->up, &listener->at, &listener->right'
            if form==4:
                args='RwaV3d *o, RwaV3d a, RwaV3d b'
                fields=fields.replace('a->','a.').replace('b->','b.')
                callargs='&listener->right, listener->up, listener->at'
            helper='static '+decl+' void '+name+'('+args+')\n{\n'+fields+'}\n\n'
            new='    '+name+'('+callargs+');\n'
            b=b.replace(body,helper+body)
        b=b.replace(old,new,1)
    VS['lisc_%d'%form]=[(src,b)]
for mask in range(16):
    b=base
    for body in [up,at]:
        old=products(body);new=old
        # The six source reads which are first in the original x87 products.
        targets=[('at','z'),('up','z'),('at','y'),('at','x')]
        for bit,(v,axis) in enumerate(targets):
            if mask&(1<<bit):
                new=new.replace('listener->'+v+'.'+axis, '*(const volatile RwReal *)&listener->'+v+'.'+axis)
        b=b.replace(old,new,1)
    VS['lisc_v%02d'%mask]=[(src,b)]
