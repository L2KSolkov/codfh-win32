exec(open('docs/drafts/rwa_voice_wave_shape_trials.py').read())
bases = {n:VS['vws_%02d'%n][0][1] for n in [12,13]}
VS = {}
for baseid,unit in bases.items():
    for kind in range(5):
        b = unit
        if kind in [1,2]:
            declaration = '    RwUInt8 *data;'
            assignment = '    data = sub_24DB60((RwUInt32)wave->buffer);\n'
            if kind == 2:
                assignment += '    data -= (RwUInt32)state->output->memory;\n'
            b = b.replace('    rwaBufferDesc desc;', '    rwaBufferDesc desc;\n'+declaration)
            value = 'data - (RwUInt8 *)state->output->memory' if kind==1 else 'data'
            b = b.replace(call, assignment+'    if (IDirectSoundBuffer_SetPlayRegion(state->buffer, '+value+',\n                                         wave->deviceFormat.length) >= 0')
        elif kind in [3,4]:
            b = b.replace('    rwaBufferDesc desc;', '    rwaBufferDesc desc;\n    const RwaWaveFormat *tailFormat;\n    RwUInt8 *data;')
            assignment = '    data = sub_24DB60((RwUInt32)wave->buffer);\n    tailFormat = &wave->deviceFormat;\n'
            if kind == 4: assignment = '    tailFormat = &wave->deviceFormat;\n    data = sub_24DB60((RwUInt32)wave->buffer);\n'
            b = b.replace(call, assignment+'    if (IDirectSoundBuffer_SetPlayRegion(state->buffer, data - (RwUInt8 *)state->output->memory,\n                                         tailFormat->length) >= 0')
            b = b.replace('IDirectSoundBuffer_SetLoopRegion(state->buffer, 0, wave->deviceFormat.length)', 'IDirectSoundBuffer_SetLoopRegion(state->buffer, 0, tailFormat->length)')
        for decl in range(4):
            c = b
            if decl & 1:
                c = c.replace('    RwBool      created;\n    RwBool      is3D;', '    RwBool      is3D;\n    RwBool      created;')
            if decl & 2:
                begin = c.index('// match: _sub_24F410 @')
                end = c.index('// match: _sub_24F7E0 @',begin)
                part = c[begin:end].replace('rwaXboxVoice *obj, RwaWave *wave)', 'rwaXboxVoice *obj, RwaWave *arg)').replace('    rwaXboxVoiceState *state =', '    RwaWave *wave = arg;\n    rwaXboxVoiceState *state =')
                c = c[:begin]+part+c[end:]
            VS['vwp_%d_%d_%d'%(baseid,kind,decl)] = [(src,c)]
