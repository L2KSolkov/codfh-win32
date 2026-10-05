exec(open('docs/drafts/rwa_listener_setup_current_trials.py').read())
from itertools import permutations
VS={}
first='    v.x = 0.0f;\n    v.y = 0.0f;\n    v.z = 0.0f;'
second='''    v.x = 0.0f;
    v.z = 0.0f;
    listener->at.x = 0.0f;
    listener->at.y = 0.0f;
    v.y = 1.0f;
    listener->up = v;
    listener->at.z = 1.0f;'''
for n in range(6):
    for literal in [False,True]:
        b=setup_unit
        if literal:b=b.replace('* flt_3CD84C','* 0.0f')
        variants=[
            second,
            second.replace('    v.x = 0.0f;\n    v.z = 0.0f;', '    v.z = v.x = 0.0f;'),
            '    v.x = v.z = 0.0f;\n    v.y = 1.0f;\n    listener->up = v;\n    v.x = v.y = 0.0f;\n    v.z = 1.0f;\n    listener->at = v;',
            '    v.x = v.z = 0.0f;\n    v.y = 1.0f;\n    listener->up = v;\n    listener->at.x = listener->at.y = 0.0f;\n    listener->at.z = 1.0f;',
            second.replace('    v.x = 0.0f;\n    v.z = 0.0f;', '    v.x = v.z = 0.0f;'),
            '    v.x = v.z = listener->at.x = listener->at.y = 0.0f;\n    v.y = listener->at.z = 1.0f;\n    listener->up = v;',
        ]
        b=b.replace(second,variants[n])
        VS['lsetv_%d_%d'%(n,literal)]=[(src,b)]
