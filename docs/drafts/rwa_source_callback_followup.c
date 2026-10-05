// match: _sub_248810 @ 0x00248810
void
sub_248810(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event, rwaDecoderState *state)
{
    if (status == 4)
    {
        state->unk00 = ((rwaCacheClient *)file)->request.unk20;
    }

    if (state->flags & 8)
    {
        RwUInt32    chunkSize = state->info->unk20;

        state->flags &= ~8;
        WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
        if (state->flags & 0x2000)
        {
            ReleaseSemaphore(state->semaphore, 1, NULL);
            return;
        }
        for (; bytes; bytes -= chunkSize)
        {
            RwUInt32    next;

            if (state->regions[state->region].flags & 0x10)
            {
                state->regions[state->region].flags = 0x12;
                if (state->aheadBuffer && state->loops != -1)
                {
                    ((volatile rwaStreamRegion *)state->regions)[state->region].flags |= 4;
                }
            }
            else
            {
                state->regions[state->region].flags = 2;
            }
            next = state->region + 1;
            if (next == state->noItems)
            {
                next = 0;
            }
            state->region = next;
        }
        ReleaseSemaphore(state->semaphore, 1, NULL);
        goto reads;
    }

    if (state->flags & 0x20)
    {
        state->flags &= ~0x20;
        goto reads;
    }

    if (state->flags & 0x10)
    {
        state->flags &= ~0x10;
        if (status == 4)
        {
        if (state->notify)
        {
            state->notify(state, 6, state->notifyData);
        }
        sub_247430(state);
        return;
        }

            state->flags |= 4;
            state->flags |= 0x40;
            sub_245160(state->client.holder, &state->client, state->header, &state->header,
                       (rwaCacheCallBack)sub_248810, state);
            return;
    }

    if (state->flags & 0x40)
    {
        state->flags &= ~0x40;
        if (status != 4 && (state->header == 2062 || state->header == 2061))
        {
            if (state->header == 2061)
            {
                state->flags |= 0x40;
                sub_245160(state->client.holder, &state->client, 2062, &state->header,
                           (rwaCacheCallBack)sub_248810, state);
            }
            else
            {
                state->flags |= 0x80;
                sub_244F70(&state->client, &state->infoSize, 20, (rwaCacheCallBack)sub_248810,
                           state);
            }
            return;
        }
        goto failed;
    }

    if (state->flags & 0x80)
    {
        RwUInt32    size = 0;

        state->flags &= ~0x80;
        if (status == 4)
        {
            goto notifyFailed;
        }
        if (state->id.name || state->id.uuid)
        {
            if (state->uuidSize)
            {
                size = 16;
            }
            if (state->nameSize)
            {
                size += state->nameSize;
            }
            state->flags |= 0x800;
        }
        else
        {
            size = state->infoSize;
            state->flags |= 0x100;
        }
        state->info = (rwaStreamInfo *)state->alloc(size, state->allocData);
        if (state->info)
        {
            sub_244F70(&state->client, state->info, size, (rwaCacheCallBack)sub_248810, state);
            return;
        }
        goto failed;
    }

    if (state->flags & 0x800)
    {
        const RwaUUID *uuid = NULL;
        const RwChar *name = NULL;
        RwBool      found = FALSE;

        state->flags &= ~0x800;
        if (status == 4)
        {
            goto freeFailed;
        }
        if (state->uuidSize)
        {
            uuid = (const RwaUUID *)state->info;
        }
        if (state->nameSize)
        {
            name = (const RwChar *)state->info + state->uuidSize;
        }
        if (uuid && state->id.uuid && !RwaUUIDCompare(uuid, state->id.uuid))
        {
            found = TRUE;
        }
        if (name && state->id.name && !rwstrcmp(name, state->id.name))
        {
            found = TRUE;
        }
        state->free(state->info, state->allocData);
        state->info = NULL;
        if (found)
        {
            state->flags |= 0x80;
            sub_240B40(&state->id);
            sub_2449E0(&state->client,
                       sub_244A20(&state->client) - state->nameSize - state->uuidSize,
                       (rwaCacheCallBack)sub_248810, state);
        }
        else
        {
            state->flags |= 0x10;
            state->header = 2061;
            sub_2449E0(&state->client,
                       sub_244A20(&state->client) + state->unk84 - state->nameSize
                           - state->uuidSize - 20,
                       (rwaCacheCallBack)sub_248810, state);
        }
        return;
    }

    if (state->flags & 0x100)
    {
        state->flags &= ~0x100;
        if (status == 4)
        {
            goto notifyFailed;
        }
        if (sub_24D670(state->info))
        {
            state->flags |= 0x200;
            sub_2449E0(&state->client,
                       sub_244A20(&state->client) + state->unk84 - state->infoSize - 20,
                       (rwaCacheCallBack)sub_248810, state);
            return;
        }
        state->free(state->info, state->allocData);
        state->info = NULL;
        goto failed;
    }

    if (state->flags & 0x200)
    {
        state->flags &= ~0x200;
        if (status == 4)
        {
            goto freeFailed;
        }
        state->flags |= 0x400;
        sub_2451B0(&state->client, &state->header, (rwaCacheCallBack)sub_248810, state);
        return;
    }

    if (state->flags & 0x400)
    {
        RwUInt32    chunkSize = state->info->unk20;
        RwUInt32    n;
        RwUInt32    i;

        state->flags &= ~0x400;
        if (status == 4 || state->header != 2063)
        {
            state->free(state->info, state->allocData);
            state->info = NULL;
            goto failed;
        }
        if (!state->bufferSize)
        {
            RwUInt32    count = state->unk180;
            RwUInt32    size;

            if (!count)
            {
                count = 2;
            }
            size = count * (chunkSize + 56);
            state->buffer = (RwUInt8 *)sub_242180(size, rwaMEMHINTDUR_EVENT | rwaID_80E);
            if (!state->buffer)
            {
                goto failed;
            }
            state->bufferSize = size;
        }
        if (!state->aheadSize && state->noEntries)
        {
            RwUInt32    size = state->noEntries * (chunkSize + 20);

            state->aheadBuffer = (RwUInt8 *)sub_242180(size, rwaMEMHINTDUR_EVENT | rwaID_80E);
            if (!state->aheadBuffer)
            {
                goto failed2;
            }
            state->aheadSize = size;
        }

        n = state->bufferSize / (chunkSize + 56);
        state->noItems = n;
        state->bufferSize = chunkSize * n;
        state->regions = (rwaStreamRegion *)(state->buffer + chunkSize * n);
        state->positions = (rwaStreamPosition *)((RwUInt8 *)state->regions
                                                 + sizeof(rwaStreamRegion) * state->noItems);
        state->items = (rwaQueueItem *)((RwUInt8 *)state->positions
                                        + sizeof(rwaStreamPosition) * state->noItems);
        state->noEntries = state->aheadSize / (chunkSize + 20);
        state->aheadSize = chunkSize * state->noEntries;
        if (!state->aheadSize)
        {
            if (!(state->flags & 2) && state->aheadBuffer)
            {
                sub_2421B0(state->aheadBuffer);
            }
            state->aheadBuffer = NULL;
        }
        state->entries = (rwaStreamRegion *)(state->aheadSize + state->aheadBuffer);

        if (!state->unk184)
        {
            state->unk184 = state->noItems >> 1;
            if (!state->unk184)
            {
                state->unk184 = 1;
            }
        }
        if (state->unk184 >= state->noItems)
        {
            state->unk184 = state->noItems;
        }
        if (!state->unk180)
        {
            state->unk180 = state->noItems >> 1;
            if (!state->unk180)
            {
                state->unk180 = 1;
            }
            if (!state->unk180)
            {
                state->unk180 = 1;
            }
        }
        if (state->unk180 >= state->noItems)
        {
            state->unk180 = state->noItems;
        }

        for (i = 0; i < state->noEntries; i++)
        {
            state->entries[i].unk0C = 0;
            state->entries[i].flags = 1;
        }
        for (i = 0; i < state->noItems; i++)
        {
            state->items[i].flags = 0;
            state->regions[i].unk0C = 0;
            state->regions[i].flags = 1;
        }

        state->current = state->info->markers;
        state->marker = state->info->markers;
        state->loops = sub_247F20(state);
        state->flags |= 0x8000;
        sub_247FE0(state, 0, 0);
        sub_248410(state);
        if (state->notify)
        {
            state->notify(state, 0, state->notifyData);
        }
        return;
    }

reads:
    if (state->flags & 0x20000)
    {
        state->unk190 = RwFtell(state->client.holder->file);
    }
    else if (state->cache.unk06 != state->cache.unk08 || state->cache.unk0A || state->requests)
    {
        if (state->requests || sub_24D5B0(&state->cache, &state->unkD8))
        {
            sub_2475D0(state);
        }
    }
    return;

failed2:
failed:
    if (state->notify)
    {
        state->notify(state, status | 1, state->notifyData);
    }
    sub_247430(state);
    return;

freeFailed:
    state->free(state->info, state->allocData);
    state->info = NULL;
notifyFailed:
    if (state->notify)
    {
        state->notify(state, 5, state->notifyData);
    }
    sub_247430(state);
}
