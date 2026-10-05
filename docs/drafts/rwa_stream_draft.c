// match: _sub_23FC00 @ 0x0023FC00
void
sub_23FC00(rwaStream *stream)
{
    dword_506B38--;
    WaitForSingleObject(hSemaphore, rwaINFINITE);

    sub_245E90(&stream->player, stream->unk148);

    if (stream->inst.subObjLink.next)
    {
        stream->inst.subObjLink.prev->next = stream->inst.subObjLink.next;
        stream->inst.subObjLink.next->prev = stream->inst.subObjLink.prev;
        stream->inst.subObjLink.prev = NULL;
        stream->inst.subObjLink.next = NULL;
    }

    ReleaseSemaphore(hSemaphore, 1, NULL);
}

// match: _sub_23FEE0 @ 0x0023FEE0
void
sub_23FEE0(rwaStream *stream, rwaStreamPosition *out)
{
    rwaStreamPosition  *cur;
    rwaDecoderState    *state;

    WaitForSingleObject(hSemaphore, rwaINFINITE);

    cur = sub_245D90(&stream->player, stream->unk148);
    if (!cur)
    {
        out->pos = 0;
        out->value = 0;
        ReleaseSemaphore(hSemaphore, 1, NULL);

        return;
    }

    ReleaseSemaphore(hSemaphore, 1, NULL);

    state = &stream->player.decoder->state;

    switch (out->unit)
    {
        case 1:
            *(RwReal *)&out->pos = (RwReal)cur->pos /
                                   (RwReal)stream->player.info->tracks->format->rate;
            break;
        case 2:
            out->pos = cur->pos;
            break;
    }

    switch (out->type)
    {
        case 1:
            out->value = state->info->markers[cur->value].unk04;
            break;
        case 2:
            out->value = state->info->markers[cur->value].unk00;
            break;
        case 3:
            out->value = cur->value;
            break;
    }
}

