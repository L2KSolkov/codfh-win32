turn high + base;
    }
}

// match: _sub_247FE0 @ 0x00247FE0
RwBool
sub_247FE0(rwaDecoderState *state, RwUInt32 track, RwUInt32 position)
{
    rwaStreamTrack *t = &state->info->tracks[track];
    RwUInt32    unit = t->unk20;
    RwUInt32    chunk = position / unit;
    RwUInt32    skip;
    RwUInt32    channels;
    RwUInt32    block;
    rwaStreamInfo *info;
    RwUInt32    offset;
    RwUInt32 high, low;
    RwBool result = FALSE;

    sub_2420D0(chunk, unit, &high, &low);
    skip = position - low;
    track = skip;
    channels = 1;
    if (!(t->format->flags & 4))
    {
        channels = t->format->channels;
    }
    block = channels * t->unk1A;
    if (skip % block)
    {
        skip = channels * t->unk1A * ((block + skip - 1) / block);
    }
    skip /= channels * t->unk1A;
    sub_2420D0(skip, 0xFFFFFFFF / (t->unk20 / (channels * t->unk1A)), &high, &skip);
    if (skip & 0xFFFFFFFE)
    {
        skip++;
    }

    info = state->info;
    if (info->noTracks)
    {
        RwUInt16   *step = &info->tracks[0].unk1A;
        RwUInt32    n = info->noTracks;

        do
        {
            RwUInt32    b = channels * *step;

            if (track % b)
            {
                track = b * ((b + track - 1) / b);
            }
            step += sizeof(rwaStreamTrack) / sizeof(RwUInt16);
        }
        while (--n);
    }

    offset = info->unk24 + state->marker->unk1C + chunk * info->unk20;
    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
    if (!sub_24D510(&state->cache, NULL, 0, offset, 0, 1))
    {
        goto unlock;
    }
    if (state->current != state->marker)
    {
        state->current = state->marker;
        state->loops = sub_247F20(state);
    }
    state->unkF4 = skip;
    state->unk100 = state->current->unk18 / state->info->unk20;
    state->unkF8 = state->unk100 - chunk;
    state->unkFC = state->unk100 - chunk;
    result = TRUE;
unlock:
    ReleaseSemaphore(state->semaphore, 1, NULL);
    return result;
}

/* Stops reading: the pending reads finish, the chunks are free again. */
