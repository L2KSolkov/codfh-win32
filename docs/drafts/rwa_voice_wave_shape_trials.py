exec(open('docs/drafts/rwa_voice_wave_trials.py').read())
VS = {}
null = '''    if (!wave)
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
        return;
    }
'''
call = '''    if (IDirectSoundBuffer_SetPlayRegion(state->buffer,
                                         sub_24DB60((RwUInt32)wave->buffer)
                                         - (RwUInt8 *)state->output->memory,
                                         wave->deviceFormat.length) >= 0'''
changed = '''    changed = sub_24F350(&state->format, &wave->deviceFormat);
    if (changed && !created)
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
    }
    if (changed || created)
    {'''
for bits in range(16):
    b = body
    if bits & 1:
        b = b.replace(null, '    if (wave)\n    {\n')
        close = b.rfind('\n}')
        b = b[:close]+'''\n    }
    else
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
    }
'''+b[close:]
    if bits & 2:
        b = b.replace('    rwaBufferDesc desc;', '    rwaBufferDesc desc;\n    RwUInt32 offset;')
        b = b.replace(call, '''    offset = sub_24DB60((RwUInt32)wave->buffer) - (RwUInt8 *)state->output->memory;
    if (IDirectSoundBuffer_SetPlayRegion(state->buffer, offset,
                                         wave->deviceFormat.length) >= 0''')
    if bits & 4:
        b = b.replace('        state->flags &= ~0x4000;\n        state->wave = NULL;', '        RwUInt32 flags = state->flags & ~0x4000;\n        state->wave = NULL;\n        state->flags = flags;')
    if bits & 8:
        b = b.replace(changed, '''    changed = sub_24F350(&state->format, &wave->deviceFormat);
    if (!changed)
    {
        if (!created) goto set_region;
    }
    else if (!created)
    {
        sub_24EDC0(state->buffer, (RwUInt32)-1);
    }
    {''')
        marker = '    offset = sub_24DB60' if bits & 2 else '    if (IDirectSoundBuffer_SetPlayRegion'
        b = b.replace(marker, 'set_region:\n'+marker)
    unit = base.replace(body,b)
    VS['vws_%02d' % bits] = [(src,unit)]
