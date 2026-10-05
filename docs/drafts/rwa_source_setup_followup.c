// match: _sub_249160 @ 0x00249160
RwBool
sub_249160(rwaDecoderState *state, rwaStreamSourceParams *params)
{
    const RwChar *ext;
    RwChar     *c;

    state->flags = 0;
    state->unk00 = 0;
    state->unkF0 = 0;
    state->unkF4 = 0;
    state->unkF8 = 0;
    state->unkFC = 0;
    state->info = NULL;
    state->alloc = (void *(*)(RwUInt32, void *))params->values[0];
    state->free = (void (*)(void *, void *))params->values[1];
    state->allocData = (void *)params->values[2];
    state->notify = (void (*)(rwaDecoderState *, RwInt32, void *))params->callback;
    state->notifyData = params->data;
    state->unk184 = params->values[8];
    state->unk180 = params->values[9];
    sub_240B40(&state->id);
    sub_240BF0(&state->id, (const RwChar *)params->values[7]);
    sub_240C10(&state->id, (const RwaUUID *)params->values[6]);
    state->aheadBuffer = (RwUInt8 *)params->values[14];
    state->aheadSize = params->values[13];
    ((volatile rwaDecoderState *)state)->buffer = (RwUInt8 *)params->values[11];
    state->unk154 = 0;
    state->unk158 = 0;
    state->region = 0;
    state->unk15C = 0;
    state->entry = 0;
    state->bufferSize = params->values[10];
    state->unk14C = 0;
    state->regions = NULL;
    state->unk174 = 0;
    state->loops = 0;
    state->noEntries = params->values[12];
    state->entries = NULL;
    if (!params->values[0])
    {
        params->values[0] = (RwUInt32)sub_2473D0;
    }
    if (!params->values[1])
    {
        params->values[1] = (RwUInt32)sub_246FC0;
    }

    if (!sub_24D4C0(&state->cache, state->cache.unk10, 3))
    {
        return FALSE;
    }

    if (state->buffer)
    {
        state->flags |= 1;
    }
    else if (state->bufferSize)
    {
        state->buffer = (RwUInt8 *)sub_242180(state->bufferSize, rwaMEMHINTDUR_EVENT | rwaID_80E);
        if (!state->buffer)
        {
            goto failed;
        }
    }
    if (state->aheadBuffer)
    {
        state->flags |= 2;
    }
    else if (state->aheadSize)
    {
        state->aheadBuffer = (RwUInt8 *)sub_242180(state->aheadSize,
                                                   rwaMEMHINTDUR_EVENT | rwaID_80E);
        if (!state->aheadBuffer)
        {
            goto failed;
        }
    }
    if (!sub_2416D0(&state->semaphore, 1, 1))
    {
failed:
        sub_247430(state);
        return FALSE;
    }

    switch (params->values[5]) { case 1: break; default: return FALSE; }
    ext = sub_245210((const RwChar *)params->values[4]);
    state->flags |= 0x10;
    state->header = 2061;
    for (c = (RwChar *)params->values[4]; *c; c++)
    {
        if (*c == '/')
        {
            *c = '\\';
        }
    }
    if (rwstricmp(ext, unk_42FB48) && rwstricmp(ext, aRws1))
    {
        return FALSE;
    }
    sub_2450C0(&state->file, &state->client, 2, 1, (const RwChar *)params->values[4],
               (rwaCacheCallBack)sub_248810, state);
    return TRUE;
}

