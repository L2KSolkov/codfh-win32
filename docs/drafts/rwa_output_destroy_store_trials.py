exec(open('docs/drafts/rwa_output_destroy_followup_trials.py').read())
body=VS['odf_2_0'][0][1][:-len(anchor)]
VS={}
decl='    volatile RwUInt32 zero[3];'
stores='    zero[0] = 0;\n    zero[1] = 0;\n    zero[2] = 0;'
def add(n,b):VS['ods_'+n]=[(anchor,b+anchor)]
for name,st in [
    ('chain', '    zero[2] = zero[1] = zero[0] = 0;'),
    ('comma', '    (zero[0] = 0, zero[1] = 0, zero[2] = 0);'),
    ('ptr', '    p[0] = 0;\n    p[1] = 0;\n    p[2] = 0;'),
    ('deref', '    *zero = 0;\n    *(zero + 1) = 0;\n    *(zero + 2) = 0;'),
]:
    b=body.replace(stores,st)
    if name=='ptr':b=b.replace(decl,decl+'\n    volatile RwUInt32 *p = zero;')
    add(name,b)
for mode in range(4):
    b=body.replace(decl+'\n','').replace(stores,'    {\n'+decl+'\n'+stores)
    if mode==0:b=b.replace('    sub_24DF00();','    }\n    sub_24DF00();')
    if mode==1:b=b.replace('    sub_24DF00();','    sub_24DF00();\n    }')
    if mode==2:b=b[:b.rfind('\n}')]+ '\n    }'+b[b.rfind('\n}'):]
    if mode==3:
        b=b.replace('    {\n'+decl, '    switch (0)\n    {\n    case 0:\n    {\n'+decl).replace('    sub_24DF00();','    }\n    break;\n    }\n    sub_24DF00();')
    add('scope%d'%mode,b)
for kind in ['RwInt32', 'void *', 'RwUInt32 *']:
    # The pointer objects themselves are volatile.
    new = kind+'volatile ' if '*' in kind else 'volatile '+kind+' '
    b=body.replace('volatile RwUInt32 zero',new+'zero')
    add('type_'+kind.replace(' ','').replace('*','p'),b)
helper='''static __forceinline void zero_24E710(volatile RwUInt32 *zero)
{
    zero[0] = 0;
    zero[1] = 0;
    zero[2] = 0;
}

'''
add('inline',helper+body.replace(stores,'    zero_24E710(zero);'))
add('comma_call',body.replace('    sub_24E180(obj, NULL);\n    zero[0] = 0;', '    sub_24E180(obj, NULL), zero[0] = 0;'))
