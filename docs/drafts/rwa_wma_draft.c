/* The default creation parameters. */
// match: _sub_250C10 @ 0x00250C10
void *
sub_250C10(rwaWmaSource *obj, rwaWmaParams *params)
{
    RwaStreamNodeGetParams((rwaDecoder *)obj, (rwaStreamNodeParams *)params);
    params->unk00 = 0;
    params->unk34 = 0;
    params->unk38 = 0;
    params->unk24 = 0;
    params->unk1C = 0;
    params->unk20 = 0;
    params->file = NULL;
    params->unk28 = 0;
    params->unk4C = 0;
    params->unk54 = 0;
    params->unk50 = 0;
    params->unk48 = 0;
    params->yieldRate = 0;
    params->unk04 = 1;
    params->fileType = 1;
    params->minPackets = 2;
    params->noPackets = 4;
    params->lookahead = 0xF000;

    return obj;
}


/* The play position, in seconds or (unit 2) samples. */
// match: _sub_250D90 @ 0x00250D90
void
sub_250D90(rwaWmaSource *obj, rwaStreamPosition *position)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;
    RwReal      seconds;

    position->type = 3;
    position->value = 0;
    seconds = (RwReal)state->position * 0.001f;
    *(RwReal *)&position->pos = seconds;
    if (position->unit == 2)
    {
        position->pos = (RwUInt32)(state->format.sampleRate * seconds);
    }
}


/* The WMA thread: seeks, starts and stops the listed sources and decodes
 * into their free packets (looping, or ending the stream). */
// match: _sub_251210 @ 0x00251210
static RwUInt32
sub_251210(void *data)
{
    while (dword_507E10)
    {
        rwaLink    *cur;
        rwaLink    *next;

        WaitForSingleObject(dword_507E90, rwaINFINITE);
        for (cur = dword_507EB0.next; cur != &dword_507EB0; cur = next)
        {
            rwaWmaSource *obj = rwaWmaFromLink(cur);
            rwaWmaState *state = (rwaWmaState *)obj->inst.state;

            next = cur->next;
            if (state->flags & 2)
            {
                RwUInt32    actual;

                state->flags &= ~2;
                if (state->decoder->vtbl->seekToTime(state->decoder, state->seekTime,
                                                     &actual) >= 0)
                {
                    state->position = *state->marker.unk0C * actual
                                      / state->duration;
                }
            }

            switch (state->node.mode)
            {
            case 1:
                if (state->node.status != 3)
                {
                    sub_2470A0((rwaDecoder *)obj);
                    state->link.prev->next = state->link.next;
                    state->link.next->prev = state->link.prev;
                }
                break;
            case 2:
            case 3:
            {
                rwaWmaPacket *packet;
                RwBool      more;
                RwUInt32    newPosition;
                RwUInt32    status;

                WaitForSingleObject(state->semaphore, rwaINFINITE);
                packet = &state->packets[state->write];
                if (state->node.mode == 3)
                {
                    more = TRUE;
                    if (state->node.status != 5 && state->write == state->read
                        && state->packets[state->read].state)
                    {
                        sub_2470A0((rwaDecoder *)obj);
                    }
                }
                else
                {
                    RwUInt32    filled;

                    if (state->write == state->read)
                    {
                        filled = packet->state ? 0 : state->noPackets;
                    }
                    else if (state->write > state->read)
                    {
                        filled = state->write - state->read;
                    }
                    else
                    {
                        filled = state->noPackets - state->read + state->write;
                    }
                    more = state->minPackets < filled;
                    if (state->node.status != 6 && state->packets[state->read].state)
                    {
                        sub_2470A0((rwaDecoder *)obj);
                    }
                }
                ReleaseSemaphore(state->semaphore, 1, NULL);

                newPosition = 0;
                if (!packet->state && more
                    && state->decoder->vtbl->getStatus(state->decoder, &status) >= 0
                    && (status & 2))
                {
                    RwInt32     packetState = 1;
                    RwBool      ok = TRUE;
                    RwBool      looped = FALSE;
                    RwUInt32    loopedAt = 0;
                    RwUInt32    size = 0;

                    do
                    {
                        packet->header.size = state->packetSize - size;
                        packet->header.buffer = state->buffers
                                                + state->write * state->packetSize + size;
                        *packet->header.completed = 0;
                        *packet->header.status = 0;
                        if (state->decoder->vtbl->process(state->decoder, NULL,
                                                          &packet->header) < 0)
                        {
                            ok = FALSE;
                            break;
                        }
                        size += *packet->header.completed;
                        if (size >= state->packetSize)
                        {
                            break;
                        }
                        if (!(state->flags & 1))
                        {
                            rwaStreamPosition position;
                            rwaStreamSeek seek;

                            position.value = 0;
                            position.pos = 0;
                            seek.flush = FALSE;
                            position.type = 3;
                            position.unit = 2;
                            seek.position = &position;
                            sub_251130(obj, &seek);
                            packetState = 2;
                            goto filled;
                        }
                        {
                            RwUInt32    actual = 0;

                            if (state->decoder->vtbl->seekToTime(state->decoder, 0,
                                                                 &actual) >= 0)
                            {
                                newPosition = *state->marker.unk0C * actual
                                              / state->duration;
                                looped = TRUE;
                                loopedAt = size;
                            }
                        }
                    }
                    while (size < state->packetSize);
                    packet->header.buffer = state->buffers + state->write * state->packetSize;
                    *packet->header.completed = size;

                  filled:
                    packet->position = state->position;
                    if (looped)
                    {
                        state->position = newPosition - loopedAt + size;
                    }
                    else
                    {
                        state->position += size;
                    }
                    if (ok && !*packet->header.status)
                    {
                        WaitForSingleObject(state->semaphore, rwaINFINITE);
                        if (++state->write == state->noPackets)
                        {
                            state->write = 0;
                        }
                        packet->state = packetState;
                        ReleaseSemaphore(state->semaphore, 1, NULL);
                    }
                }
                if (state->node.status == 6 && state->write == state->read
                    && !state->packets[state->write].state)
                {
                    state->node.status = 7;
                }
                break;
            }
            }
        }
        ReleaseSemaphore(dword_507E90, 1, NULL);
        Sleep(34);
    }

    ReleaseSemaphore(dword_507E8C, 1, NULL);

    return 0;
}


/* Creates a source: its packets and queue items, the decoder, the file's
 * strings and the stream description. */
// match: _sub_2516E0 @ 0x002516E0
static rwaWmaSource *
sub_2516E0(rwaWmaSource *obj, rwaInstance *parent, rwaWmaParams *params, void *a, void *b)
{
    rwaWmaState *state = (rwaWmaState *)obj->inst.state;
    rwaWmaPosition *positions;
    RwUInt32    i;
    const RwChar *fileName;
    void       *file;
    rwaWaveFormatEx wfx;
    rwaWmaFileHeader header;
    rwaWmaContentDesc desc;
    RwUInt16    title[128];
    RwUInt16    author[128];
    RwUInt16    description[128];

    if (!sub_246FD0((rwaDecoder *)obj, parent, (rwaStreamNodeParams *)params, a, b))
    {
        return NULL;
    }

    obj->state.objInterface = sub_243FF0(sub_243F40(unk_3ED9C4), obj->inst.def, params->unk14,
                                         params->unk18);
    state->noPackets = params->noPackets;
    state->flags = 0;
    if (!params->lookahead)
    {
        params->lookahead = params->noPackets * 0x3C00;
    }
    if (!sub_251630())
    {
        sub_243B80(obj->state.objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }

    state->packetSize = params->lookahead / params->noPackets;
    state->minPackets = params->minPackets;
    state->items = (rwaQueueItem *)sub_242170(state->noPackets * (state->packetSize + 80) + 4,
                                              rwaMEMHINTDUR_EVENT | rwaID_80B);
    if (!state->items)
    {
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }

    positions = (rwaWmaPosition *)(state->items + state->noPackets);
    state->packets = (rwaWmaPacket *)(positions + state->noPackets);
    state->buffers = (RwUInt8 *)(state->packets + state->noPackets);
    state->marker.unk0C = (RwUInt32 *)(state->buffers + state->packetSize * state->noPackets);
    state->write = 0;
    state->read = 0;
    memset(state->packets, 0, state->noPackets * sizeof(rwaWmaPacket));
    state->callback.func = (void (*)(rwaQueueItem *, rwaDecoder *))sub_2510D0;
    state->callback.data = (rwaDecoder *)obj;
    for (i = 0; i < state->noPackets; i++)
    {
        state->items[i].flags = 0;
        state->items[i].unk04 = (RwUInt8 *)obj;
        state->items[i].callback = &state->callback;
        state->items[i].unk08 = state->packetSize;
        state->items[i].position = &positions[i].position;
        positions[i].position.value = 0;
        positions[i].position.type = 3;
        positions[i].position.unit = 2;
        positions[i].position.pos = 0;
        state->packets[i].header.status = &state->packets[i].status;
        state->packets[i].header.completed = &state->packets[i].completed;
    }
    sub_2472E0(&state->queue, state->items, state->noPackets);

    fileName = NULL;
    file = NULL;
    if (!sub_2416D0(&state->semaphore, 1, 1))
    {
        sub_2421B0(state->items);
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }
    switch (params->fileType)
    {
        case 1:
            fileName = (const RwChar *)params->file;
            break;
        case 2:
            file = (void *)params->file;
            break;
    }
    if (WmaCreateDecoderEx(fileName, file, FALSE, params->lookahead * params->noPackets,
                           params->noPackets, params->yieldRate, &wfx, &state->decoder) < 0)
    {
        CloseHandle(state->semaphore);
        sub_2421B0(state->items);
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }

    desc.title = title;
    desc.description = description;
    desc.titleLength = 128;
    desc.authorLength = 128;
    desc.descriptionLength = 128;
    state->title[0] = '\0';
    state->author[0] = '\0';
    state->description[0] = '\0';
    desc.author = author;
    desc.copyright = NULL;
    desc.copyrightLength = 0;
    desc.rating = NULL;
    desc.ratingLength = 0;
    if (state->decoder->vtbl->getFileContentDescription(state->decoder, &desc) >= 0)
    {
        WideCharToMultiByte(0, 0, desc.title, desc.titleLength, state->title, 128, NULL, NULL);
        WideCharToMultiByte(0, 0, desc.author, desc.authorLength, state->author, 128, NULL,
                            NULL);
        WideCharToMultiByte(0, 0, desc.description, desc.authorLength, state->description,
                            128, NULL, NULL);
    }
    if (state->decoder->vtbl->getFileHeader(state->decoder, &header) < 0)
    {
        state->decoder->vtbl->release(state->decoder);
        CloseHandle(state->semaphore);
        sub_2421B0(state->items);
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }
    state->duration = header.duration;
    state->bitrate = header.bitrate;
    state->position = 0;
    state->seekTime = 0;
    if (state->decoder->vtbl->getLength(state->decoder, &state->length) < 0)
    {
        state->decoder->vtbl->release(state->decoder);
        CloseHandle(state->semaphore);
        sub_2421B0(state->items);
        sub_250B30();
        sub_243B80(state->objInterface);
        sub_247120((rwaDecoder *)obj, NULL, NULL);
        return NULL;
    }

    sub_24DA40(&state->info);
    sub_24DA10(&state->track);
    sub_24D9F0(&state->marker);
    state->info.markers = &state->marker;
    state->info.unk0C = 1;
    state->info.noTracks = 1;
    state->info.unk20 = state->packetSize;
    state->info.tracks = &state->track;
    state->info.unk24 = 0;
    state->info.unk1C = 2048;
    sub_240BF0((RwaUniqueID *)&state->info, state->title);
    sub_240BF0((RwaUniqueID *)&state->marker, state->author);
    rwaWaveFormatInit(&state->format);
    state->format.bitDepth = (RwUInt8)wfx.bitsPerSample;
    state->format.dataType = &unk_3ED5CC;
    state->format.length = state->length;
    state->format.noChannels = (RwUInt8)wfx.channels;
    state->format.sampleRate = wfx.samplesPerSec;
    sub_240BF0((RwaUniqueID *)&state->track, state->description);
    state->track.format = (rwaStreamFormat *)&state->format;
    state->track.unk1A = (RwUInt16)sub_242A30(&state->format);
    state->track.unk18 = state->track.unk1A;
    state->track.unk20 = state->info.unk20;
    state->track.unk1C = (RwUInt16)(state->track.unk20 / state->track.unk18);
    state->track.unk0C = sub_242E30(&state->format);
    state->track.unk10 = state->track.unk20;
    *state->marker.unk0C = wfx.channels * state->duration * wfx.samplesPerSec
                           / state->track.unk0C * state->track.unk1A / 1000;
    RwaStreamNodeCreationComplete((rwaDecoder *)obj);
    if (obj->inst.subObjLink.next)
    {
        obj->inst.subObjLink.prev->next = obj->inst.subObjLink.next;
        obj->inst.subObjLink.next->prev = obj->inst.subObjLink.prev;
        obj->inst.subObjLink.prev = NULL;
        obj->inst.subObjLink.next = NULL;
    }
    state->link.prev = NULL;
    state->link.next = NULL;

    return obj;
}

