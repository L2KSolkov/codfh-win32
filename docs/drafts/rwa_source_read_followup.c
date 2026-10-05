// match: _sub_248520 @ 0x00248520
RwInt32
sub_248520(rwaDecoderState *state)
{
    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
    while (state->regions[state->unk14C].flags == 1)
    {
        RwUInt32    chunkSize = state->info->unk20;
        RwUInt32    free;

        if (state->unk14C == state->unk154)
        {
            free = state->noItems;
        }
        else if (state->unk14C > state->unk154)
        {
            free = state->unk154 + state->noItems - state->unk14C;
        }
        else
        {
            free = state->unk154 - state->unk14C;
        }
        if (free < state->noItems - state->unk184)
        {
            break;
        }

        if (!state->unkF8)
        {
        ReleaseSemaphore(state->semaphore, 1, NULL);
        if (!(state->flags & 0x4000))
        {
            return 4;
        }
        if (!sub_247FE0(state, 0, 0))
        {
            return 0;
        }
        WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
            continue;
        }
        {

            RwInt32     result = 1;
            RwUInt32    count = state->unk180;
            RwUInt32    bytes;
            RwUInt32    at;
            RwUInt32    first;
            RwUInt32    read;
            RwUInt32    rest;

            if (count > free)
            {
                count = free;
            }
            if (count > state->unkF8)
            {
                count = state->unkF8;
            }
            bytes = chunkSize * count;
            at = chunkSize * state->unk14C;
            first = state->bufferSize - at;
            if (first > bytes)
            {
                first = bytes;
            }
            read = 0;
            rest = bytes - first;
            if (first)
            {
                if (!sub_24D510(&state->cache, at + state->buffer, first, 0, 0, 4))
                {
                    ReleaseSemaphore(state->semaphore, 1, NULL);
                    return 2;
                }
                read = first;
            }
            if (rest)
            {
                if (sub_24D510(&state->cache, state->buffer, rest, 0, 0, 4))
                {
                    read += rest;
                }
                else
                {
                    result = 2;
                }
            }
            for (; read; )
            {
                rwaStreamRegion *region = &state->regions[state->unk14C];
                RwUInt32    next;

                region->unk04 = state->unk100 - state->unkF8;
                region->marker = state->current;
                region->flags = 8;
                if (state->unkF0 != state->unkF4)
                {
                    region->unk0C = state->unkF4;
                    state->unkF0 = state->unkF4;
                }
                else
                {
                    region->unk0C = 0;
                }
                region->unk08 = state->unkF0;
                read -= chunkSize;
                state->unkF8--;
                next = state->unk14C + 1;
                if (next == state->noItems)
                {
                    next = 0;
                }
                state->unk14C = next;
            }
            if (!state->unkF8 && state->loops != -1 && (state->flags & 0x4000))
            {
                RwUInt32    last = state->unk14C;

                if (!last)
                {
                    last = state->noItems;
                }
                --last;
                state->regions[last].flags |= 0x10;
            }
            ReleaseSemaphore(state->semaphore, 1, NULL);
            return result;
                }

    }
    ReleaseSemaphore(state->semaphore, 1, NULL);
    return 3;
}
