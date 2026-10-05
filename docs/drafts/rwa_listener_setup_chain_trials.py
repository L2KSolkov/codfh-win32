exec(open('docs/drafts/rwa_listener_setup_values_trials.py').read())
VS={}
for n,order in enumerate(permutations(['v.x','v.z','listener->at.x','listener->at.y'])):
    for one in range(2):
        b=setup_unit.replace('* flt_3CD84C','* 0.0f')
        ones = ['v.y = listener->at.z', 'listener->at.z = v.y'][one]
        new='    '+' = '.join(order)+' = 0.0f;\n    '+ones+' = 1.0f;\n    listener->up = v;'
        b=b.replace(second,new)
        VS['lsetc_%02d_%d'%(n,one)]=[(src,b)]
