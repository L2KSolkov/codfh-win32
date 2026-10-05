exec(open('docs/drafts/rwa_voice_wave_shape_trials.py').read())
unit = VS['vws_12'][0][1]
VS = {}
fn_start = unit.index('// match: _sub_24F410 @')
fn_end = unit.index('// match: _sub_24F7E0 @',fn_start)
flow = unit[fn_start:fn_end]
flow = flow.replace(null, '    if (!wave) goto no_wave;\n')
close = flow.rfind('\n}')
flow = flow[:close]+'''\n    return;
no_wave:
    sub_24EDC0(state->buffer, (RwUInt32)-1);
'''+flow[close:]
base = unit[:fn_start]+flow+unit[fn_end:]
VS['vwf_goto'] = [(src,base)]
for n,old,new in [
    ('register_wave','RwaWave *wave)','register RwaWave *wave)'),
    ('register_3d','RwBool      is3D;','register RwBool is3D;'),
    ('uint_3d','RwBool      is3D;','RwUInt32 is3D;'),
    ('uint_created','RwBool      created;','RwUInt32 created;'),
    ('flag_after_created','    is3D = (wave->flags >> 1) & 1;\n    created = FALSE;', '    created = FALSE;\n    is3D = (wave->flags >> 1) & 1;'),
    ('3d_mask','is3D = (wave->flags >> 1) & 1;', 'is3D = (wave->flags & 2) >> 1;'),
    ('wave_volatile', 'RwaWave *wave)', 'volatile RwaWave *wave)'),
    ('wave_pointer_volatile', 'RwaWave *wave)', 'RwaWave *volatile wave)'),
]:
    b = base[:fn_start]+base[fn_start:].replace(old,new,1)
    VS['vwf_'+n]=[(src,b)]
for i in [0,1,2]:
    if i == 0:
        b = base.replace('    is3D = (wave->flags >> 1) & 1;', '    {\n    is3D = (wave->flags >> 1) & 1;').replace('no_wave:', '    }\nno_wave:')
    elif i == 1:
        b = base.replace('    RwBool      created;\n', '').replace('    is3D = (wave->flags >> 1) & 1;', '    {\n    RwBool created;\n    is3D = (wave->flags >> 1) & 1;').replace('no_wave:', '    }\nno_wave:')
    else:
        b = base.replace('    RwBool      is3D;\n', '').replace('    is3D = (wave->flags >> 1) & 1;', '    {\n    RwBool is3D = (wave->flags >> 1) & 1;').replace('no_wave:', '    }\nno_wave:')
    VS['vwf_block_%d'%i]=[(src,b)]
