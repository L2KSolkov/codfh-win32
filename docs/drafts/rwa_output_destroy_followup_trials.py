from pathlib import Path
src=Path('src/rwa/xbox/unit_24DF20.c').read_text()
body=Path('docs/drafts/rwa_out_710_draft.c').read_text().replace('static void\n','void\n',1)
anchor='/* Applies what changed and lets DirectSound work. */'
VS={}
for form in range(5):
    b=body
    if form==1: b=b.replace('RwaV3d      zero;', 'volatile RwaV3d zero;')
    if form==2:
        b=b.replace('RwaV3d      zero;', 'volatile RwUInt32 zero[3];').replace('zero.x = 0.0f;', 'zero[0] = 0;').replace('zero.y = 0.0f;', 'zero[1] = 0;').replace('zero.z = 0.0f;', 'zero[2] = 0;')
    if form==3:
        b=b.replace('RwaV3d      zero;', 'volatile RwUInt32 a0, a1, a2;').replace('zero.x = 0.0f;', 'a0 = 0;').replace('zero.y = 0.0f;', 'a1 = 0;').replace('zero.z = 0.0f;', 'a2 = 0;')
    if form==4:
        b=b.replace('    RwaV3d      zero;\n', '').replace('    zero.x = 0.0f;\n    zero.y = 0.0f;\n    zero.z = 0.0f;', '    {\n    volatile RwaV3d zero = {0.0f, 0.0f, 0.0f};').replace('    sub_24DF00();','    sub_24DF00();\n    }')
    for callee in range(3):
        c=b
        if callee==1:
            c=c.replace('    sub_24E180(obj, NULL);', '    {\n    void (*set)(rwaXboxOutput *, rwaInstance *) = sub_24E180;\n    set(obj, NULL);\n    }')
        if callee==2:
            c=c.replace('    sub_24DF00();','    {\n    RwaUUID *(*clear)(void) = sub_24DF00;\n    clear();\n    }')
        VS['odf_%d_%d'%(form,callee)]=[(anchor,c+anchor)]
