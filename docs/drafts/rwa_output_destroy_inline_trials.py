exec(open('docs/drafts/rwa_output_destroy_store_trials.py').read())
VS={}
forms={
    'postinc': ('volatile RwUInt32 *zero', '*zero++ = 0; *zero++ = 0; *zero = 0;', 'zero'),
    'preinc': ('volatile RwUInt32 *zero', '*zero = 0; *++zero = 0; *++zero = 0;', 'zero'),
    'arrayptr': ('volatile RwUInt32 (*zero)[3]', '(*zero)[0] = 0; (*zero)[1] = 0; (*zero)[2] = 0;', '&zero'),
    'ptrptr': ('volatile RwUInt32 **zero', '(*zero)[0] = 0; (*zero)[1] = 0; (*zero)[2] = 0;', '&p'),
    'threeptrs': ('volatile RwUInt32 *a, volatile RwUInt32 *b, volatile RwUInt32 *c', '*a = 0; *b = 0; *c = 0;', 'zero, zero+1, zero+2'),
    'oneptr_offset': ('volatile RwUInt32 *zero, RwUInt32 offset', 'zero[offset] = 0; zero[offset+1] = 0; zero[offset+2] = 0;', 'zero, 0'),
    'for': ('volatile RwUInt32 *zero', 'RwUInt32 i; for (i=0; i<3; ++i) zero[i] = 0;', 'zero'),
    'single': ('volatile RwUInt32 *zero', '*zero = 0;', 'zero'),
    'value': ('volatile RwUInt32 *zero, RwUInt32 value', 'zero[0] = value; zero[1] = value; zero[2] = value;', 'zero, 0'),
}
for name,(args,code,callargs) in forms.items():
    helper = 'static __forceinline void zero_24E710('+args+')\n{\n    '+code+'\n}\n\n'
    invoke = '    zero_24E710('+callargs+');'
    if name=='single':invoke+='\n    zero_24E710(zero+1);\n    zero_24E710(zero+2);'
    b=body.replace(stores,invoke)
    if name=='ptrptr':b=b.replace(decl,decl+'\n    volatile RwUInt32 *p = zero;')
    VS['odi_'+name]=[(anchor,helper+b+anchor)]
    VS['odi_plain_'+name]=[(anchor,helper+b.replace(decl,decl.replace('volatile ',''))+anchor)]
