/* Parked WMA source creator 2516E0. Insert before sub_251CE0 in
 * src/rwa/xbox/unit_250B20.c. Current VC7.1 baseline 246 normalized diff
 * lines; explicit track local gives 211. The 0x354 frame is correct.
 * Cleanup sharing, local slots, and scheduling still differ.
 * Reproduce: rwa_wma_create_members_trials.py, wmcm_16.
 * This body is not a match and must remain outside production sources. */
// match: _sub_2516E0 @ 0x002516E0
rwaWmaSource *
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
    {
    rwaStreamTrack *track = &state->track;
    sub_24DA10(track);
    sub_24D9F0(&state->marker);
    state->info.markers = &state->marker;
    state->info.unk0C = 1;
    state->info.noTracks = 1;
    state->info.unk20 = state->packetSize;
    state->info.tracks = track;
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
    sub_240BF0((RwaUniqueID *)track, state->description);
    track->format = (rwaStreamFormat *)&state->format;
    track->unk1A = (RwUInt16)sub_242A30(&state->format);
    track->unk18 = track->unk1A;
    track->unk20 = state->info.unk20;
    track->unk1C = (RwUInt16)(track->unk20 / track->unk18);
    track->unk0C = sub_242E30(&state->format);
    track->unk10 = track->unk20;
    *state->marker.unk0C = wfx.channels * state->duration * wfx.samplesPerSec
                           / track->unk0C * track->unk1A / 1000;
    }
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

