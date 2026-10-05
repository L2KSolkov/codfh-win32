exec(open('docs/drafts/rwa_voice_wave_shape_trials.py').read())
bases = {n:VS['vws_%02d'%n][0][1] for n in [12,13]}
VS = {}
for number, unit in bases.items():
    for form in range(6):
        helper = ''
        b = unit
        if form < 4:
            helper = '''static __forceinline const RwaWaveFormat *
format_24F410(RwaWave *wave)
{
    return &wave->deviceFormat;
}

'''
            start = b.index('// match: _sub_24F410 @')
            end = b.index('// match: _sub_24F7E0 @',start)
            f = b[start:end]
            if form == 0: f = f.replace('&wave->deviceFormat', 'format_24F410(wave)')
            elif form == 1: f = f.replace('sub_24F350(&state->format, &wave->deviceFormat)', 'sub_24F350(&state->format, format_24F410(wave))')
            elif form == 2: f = f.replace('const RwaWaveFormat *format = &wave->deviceFormat;', 'const RwaWaveFormat *format = format_24F410(wave);')
            else: f = f.replace('wave->deviceFormat.length', 'format_24F410(wave)->length')
            b = b[:start]+f+b[end:]
        else:
            helper = '''static __forceinline RwInt32
region_24F410(rwaXboxVoiceState *state, RwaWave *wave)
{
    RwUInt8 *data = sub_24DB60((RwUInt32)wave->buffer);
    return IDirectSoundBuffer_SetPlayRegion(state->buffer,
                data - (RwUInt8 *)state->output->memory, wave->deviceFormat.length);
}

'''
            if form == 5:
                helper = helper.replace('    RwUInt8 *data = sub_24DB60((RwUInt32)wave->buffer);\n', '').replace('data - (RwUInt8 *)state->output->memory', 'sub_24DB60((RwUInt32)wave->buffer) - (RwUInt8 *)state->output->memory')
            b = b.replace(call, '    if (region_24F410(state, wave) >= 0')
        b = b.replace('/* Plays wave (NULL:', helper+'/* Plays wave (NULL:')
        VS['vwi_%d_%d'%(number,form)] = [(src,b)]
