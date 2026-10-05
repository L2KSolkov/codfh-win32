/*
 * codfh-match: RenderWare Audio's stream source reader (0x247430-0x249490):
 * a stream source's node state reading its stream file through the stream
 * cache: the open and header state machine (the cache callback), the
 * marker and track lookups, the rings of chunks the reads fill and the
 * play queue empties, the interleaved track copy, and the stream node and
 * stream source interface registrations.
 */
#include "rwa.h"
#include "rwaint.h"

extern RwUInt32 __stdcall WaitForSingleObject(void *handle, RwUInt32 milliseconds);
extern RwBool __stdcall ReleaseSemaphore(void *semaphore, RwInt32 count, RwInt32 *previous);
extern RwBool __stdcall CloseHandle(void *handle);

extern void *sub_242180(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void sub_2422A0(void *mem);
extern void sub_2420D0(RwUInt32 a, RwUInt32 b, RwUInt32 *resultHigh, RwUInt32 *resultLow);
extern RwUInt32 sub_2433C0(const RwaWaveFormat *format, RwUInt32 size);
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern RwaUniqueID *sub_240B40(RwaUniqueID *uniqueID);
extern RwaUniqueID *sub_240BF0(RwaUniqueID *uniqueID, const RwChar *name);
extern RwaUniqueID *sub_240C10(RwaUniqueID *uniqueID, const RwaUUID *uuid);
extern void **sub_2416D0(void **semaphore, RwInt32 initial, RwInt32 maximum);
extern void sub_2449E0(rwaCacheClient *client, RwUInt32 offset, rwaCacheCallBack callback,
                       void *data);
extern RwUInt32 sub_244A20(rwaCacheClient *client);
extern void sub_244F60(rwaCacheClient *client);
extern void sub_244F70(rwaCacheClient *client, void *dest, RwUInt32 size,
                       rwaCacheCallBack callback, void *data);
extern void sub_245130(rwaCacheClient *client);
extern void sub_245160(rwaCacheFile *holder, rwaCacheClient *client, RwUInt32 unk4C,
                       RwUInt32 *header, rwaCacheCallBack callback, void *data);
extern void sub_2451B0(rwaCacheClient *client, void *dest, rwaCacheCallBack callback,
                       void *data);
extern const RwChar *sub_245210(const RwChar *path);
extern RwBool sub_2450C0(rwaCacheFile **holder, rwaCacheClient *client, RwInt32 type,
                         RwInt32 mode, const RwChar *path, rwaCacheCallBack callback,
                         void *data);
extern RwInt32 RwFtell(void *file);
extern RwBool sub_24D4C0(rwaReadCache *cache, void *data, RwInt32 count);
extern void sub_24D500(rwaReadCache *cache);
extern RwBool sub_24D510(rwaReadCache *cache, void *dest, RwUInt32 size, RwUInt32 offset,
                         RwUInt32 e, RwInt32 kind);
extern RwBool sub_24D5B0(rwaReadCache *cache, RwUInt32 *out);
extern void sub_24D640(rwaReadCache *cache);
extern void *sub_24D670(rwaStreamInfo *info);
extern void *sub_246FC0(void *mem, RwUInt32 unused);
extern void *sub_2473D0(RwUInt32 size, RwUInt32 unused);
extern void *sub_243E20(void *iface);
extern void RwaWaveDictAssignID(void *iface, const void *uuid, const void *textID);
extern void sub_243CD0(void *iface, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern RwBool sub_243EA0(void *iface);

extern RwUInt32 ourGlobals[];
#define rwstrcmp(_a, _b)                                                   \
    (((RwInt32 (*)(const RwChar *, const RwChar *))ourGlobals[0x114 / 4])((_a), (_b)))
#define rwstricmp(_a, _b)                                                  \
    (((RwInt32 (*)(const RwChar *, const RwChar *))ourGlobals[0x11C / 4])((_a), (_b)))

extern RwUInt8 dword_5079D4[];      /* the stream node interface */
extern RwUInt8 dword_5079FC[];      /* the stream source interface */
extern const RwUInt8 unk_3ED964[];
extern const RwUInt8 unk_3ED9C4[];
extern RwUInt8 off_42FB54[];
extern RwUInt8 off_42FB90[];
extern RwUInt8 off_42FBB8[];
extern RwUInt8 off_42FC20[];
extern const RwChar unk_42FB48[];   /* the stream file extensions */
extern const RwChar aRws1[];

static void sub_248810(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event,
                       rwaDecoderState *state);
RwInt32 sub_247F20(rwaDecoderState *state);
void sub_247660(rwaDecoderState *state);

#define rwaChunk(_ring, _index) (&(_ring)[(_index)])

/* Releases what the state holds once. */
// match: _sub_247430 @ 0x00247430
static void
sub_247430(rwaDecoderState *state)
{
    if (state->flags & 0x1000)
    {
        return;
    }

    if (state->flags & 4)
    {
        sub_245130(&state->client);
    }
    if (state->buffer && !(state->flags & 1))
    {
        sub_2422A0(state->buffer);
        state->buffer = NULL;
    }
    if (state->aheadBuffer && !(state->flags & 2))
    {
        sub_2422A0(state->aheadBuffer);
        state->aheadBuffer = NULL;
    }
    if (state->info)
    {
        state->free(state->info, state->allocData);
        state->info = NULL;
    }
    if (state->semaphore)
    {
        CloseHandle(state->semaphore);
    }
    sub_24D500(&state->cache);
    state->flags |= 0x1000;
}

// match: _sub_247500 @ 0x00247500
void
sub_247500(rwaDecoderState *state)
{
    sub_247430(state);
}

/* The marker with the UUID. */
// match: _sub_247510 @ 0x00247510
RwUInt32
sub_247510(rwaDecoderState *state, const RwaUUID *uuid)
{
    RwUInt32    i;

    for (i = 0; i < state->info->unk0C; i++)
    {
        const RwaUUID *markerUUID = (const RwaUUID *)state->info->markers[i].unk00;

        if (markerUUID && !RwaUUIDCompare(markerUUID, uuid))
        {
            return i;
        }
    }

    return 0;
}

/* The marker with the name. */
// match: _sub_247570 @ 0x00247570
RwUInt32
sub_247570(rwaDecoderState *state, const RwChar *name)
{
    RwUInt32    i;

    for (i = 0; i < state->info->unk0C; i++)
    {
        const RwChar *markerName = (const RwChar *)state->info->markers[i].unk04;

        if (markerName && !rwstrcmp(markerName, name))
        {
            return i;
        }
    }

    return 0;
}

/* Starts the read the requests ask for. */
// match: _sub_2475D0 @ 0x002475D0
static void
sub_2475D0(rwaDecoderState *state)
{
    if (!(state->flags & 0x2FF8))
    {
        RwUInt32    requests = state->requests;

        if (requests & 4)
        {
            state->requests = requests & ~4;
            state->flags |= 8;
            sub_244F70(&state->client, (void *)state->unkDC, state->unkE0,
                       (rwaCacheCallBack)sub_248810, state);
        }
        else if (requests & 1)
        {
            state->requests = requests & ~1;
            state->flags |= 0x20;
            sub_2449E0(&state->client, state->unkE4, (rwaCacheCallBack)sub_248810, state);
        }
    }
}

/* Copies the look-ahead chunks into the playing chunks, track by track and
 * channel by channel (the samples of a track's channels are interleaved in
 * units of its channel step), until a playing chunk is filled. */
// match: _sub_247660 @ 0x00247660
void
sub_247660(rwaDecoderState *state)
{
    rwaStreamInfo *info = state->info;
    RwUInt32    chunkSize = info->unk20;
    RwUInt32    noTracks = info->noTracks;
    RwBool      done = FALSE;

    do
    {
        rwaStreamRegion *from;
        rwaStreamRegion *to;
        RwUInt8    *src;
        RwUInt8    *dst;
        RwUInt32    srcBytes;
        RwUInt32    dstBytes;
        RwUInt32    track;
        RwUInt32    offset;
        RwBool      dstFull;
        RwBool      srcEmpty;

        if (!(state->regions[state->unk15C].flags & 2))
        {
            break;
        }
        dst = state->buffer + chunkSize * state->unk15C;
        src = state->aheadBuffer + chunkSize * state->unk174;
        to = &state->regions[state->unk15C];
        from = &state->entries[state->unk174];
        srcBytes = from->unk0C;
        dstBytes = to->unk0C;

        for (track = 0, offset = 0; track < noTracks; track++, offset += sizeof(rwaStreamTrack))
        {
            rwaStreamTrack *t = (rwaStreamTrack *)((RwUInt8 *)info->tracks + offset);
            RwUInt8     channels = t->format->channels;
            RwUInt16    step = t->unk1A;
            RwUInt32    unitSize = t->unk18;
            RwUInt32    size = unitSize * t->unk1C;
            RwUInt32    kind;
            RwUInt32    count;
            RwUInt32    dstAt;
            RwUInt32    srcAt;
            RwUInt32    end;
            RwUInt32    bytes;
            RwUInt32    remainder;
            RwUInt8    *s;
            RwUInt8    *d;
            RwUInt32    c;

            if (step & 1)
            {
                if (step & 3)
                {
                    if (step & 7)
                    {
                        if (step & 0xF)
                        {
                            kind = 1;
                            count = step;
                        }
                        else
                        {
                            kind = 5;
                            count = step >> 4;
                        }
                    }
                    else
                    {
                        kind = 4;
                        count = step >> 3;
                    }
                }
                else
                {
                    kind = 3;
                    count = step >> 2;
                }
            }
            else
            {
                kind = 2;
                count = step >> 1;
            }

            sub_2420D0(dstBytes, size, &dstAt, &remainder);
            sub_2420D0(srcBytes, size, &srcAt, &remainder);
            if (to->flags & 0x10)
            {
                sub_2420D0(state->loops, size, &end, &remainder);
                end = step * ((end + step - 1) / step);
            }
            else
            {
                end = size;
            }
            dstAt = t->unk1A * ((t->unk1A + dstAt - 1) / t->unk1A);
            srcAt = t->unk1A * ((srcAt + t->unk1A - 1) / t->unk1A);
            bytes = size - srcAt;
            if (end - dstAt <= size - srcAt)
            {
                bytes = end - dstAt;
            }
            if (track == noTracks - 1)
            {
                dstFull = (end == dstAt + bytes);
                srcEmpty = (size == srcAt + bytes);
            }

            s = src + srcAt % unitSize + t->unk24 + unitSize * channels * (srcAt / unitSize);
            d = dst + dstAt % unitSize + t->unk24 + unitSize * (dstAt / unitSize) * channels;
            for (c = 0; c < channels; c++)
            {
                RwUInt8    *sp = s;
                RwUInt8    *dp = d;
                RwUInt32    sLeft = unitSize - dstAt % unitSize;
                RwUInt32    dLeft = unitSize - srcAt % unitSize;
                RwUInt32    left = bytes;

                while (left)
                {
                    RwUInt32    n;

                    if (!sLeft)
                    {
                        sLeft = unitSize;
                        sp += unitSize * (channels - 1);
                    }
                    if (!dLeft)
                    {
                        dLeft = unitSize;
                        dp += unitSize * (channels - 1);
                    }
                    switch (kind)
                    {
                    case 1:
                        for (n = 0; n < count; n++)
                        {
                            *dp++ = *sp++;
                        }
                        break;
                    case 2:
                        for (n = 0; n < count; n++)
                        {
                            *(RwUInt16 *)dp = *(RwUInt16 *)sp;
                            sp += 2;
                            dp += 2;
                        }
                        break;
                    case 3:
                        for (n = 0; n < count; n++)
                        {
                            *(RwUInt32 *)dp = *(RwUInt32 *)sp;
                            sp += 4;
                            dp += 4;
                        }
                        break;
                    case 4:
                        for (n = 0; n < count; n++)
                        {
                            ((RwUInt32 *)dp)[0] = ((RwUInt32 *)sp)[0];
                            ((RwUInt32 *)dp)[1] = ((RwUInt32 *)sp)[1];
                            sp += 8;
                            dp += 8;
                        }
                        break;
                    case 5:
                        for (n = 0; n < count; n++)
                        {
                            ((RwUInt32 *)dp)[0] = ((RwUInt32 *)sp)[0];
                            ((RwUInt32 *)dp)[1] = ((RwUInt32 *)sp)[1];
                            ((RwUInt32 *)dp)[2] = ((RwUInt32 *)sp)[2];
                            ((RwUInt32 *)dp)[3] = ((RwUInt32 *)sp)[3];
                            sp += 16;
                            dp += 16;
                        }
                        break;
                    }
                    dLeft -= step;
                    sLeft -= step;
                    left -= step;
                }
                if (step <= unitSize)
                {
                    s += unitSize;
                    d += unitSize;
                }
                else
                {
                    s += bytes;
                    d += bytes;
                }
            }

            if (track == noTracks - 1)
            {
                from->marker = to->marker;
                from->unk04 = to->unk04;
                from->unk08 = state->unkF0;
                if (srcEmpty)
                {
                    from->unk0C = 0;
                    from->flags = 2;
                    state->unk174++;
                    done = TRUE;
                    if (state->unk174 == state->noEntries)
                    {
                        state->unk174 = 0;
                    }
                }
                else
                {
                    sub_2420D0(srcAt + bytes, 0xFFFFFFFF / size, &remainder, &from->unk0C);
                    from->unk0C++;
                }
                if (dstFull)
                {
                    RwUInt32    next;

                    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
                    to->unk0C = 0;
                    to->flags = 1;
                    next = state->unk15C + 1;
                    if (next == state->noItems)
                    {
                        next = 0;
                    }
                    if (state->unk154 == state->unk15C)
                    {
                        state->unk154 = next;
                        state->unk158 = next;
                    }
                    state->unk15C = next;
                    ReleaseSemaphore(state->semaphore, 1, NULL);
                }
                else
                {
                    sub_2420D0(dstAt + bytes, 0xFFFFFFFF / size, &remainder, &to->unk0C);
                    to->unk0C++;
                }
            }
        }
    }
    while (!done);
}

/* The next chunk ready to play (marked playing, 4), and its region in
 * *region; NULL when none is. */
// match: _sub_247C50 @ 0x00247C50
RwUInt8 *
sub_247C50(rwaDecoderState *state, rwaStreamRegion **region)
{
    RwUInt8    *chunk;
    RwUInt32    chunkSize;

    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
    chunkSize = state->info->unk20;

    if (!(state->flags & 0x10000))
    {
        rwaStreamRegion *regions = state->regions;
        RwUInt32    flags = regions[state->unk158].flags;
        RwUInt32    index;
        RwUInt32    next;

        if (state->flags & 0x2000)
        {
            if (!(flags & 2))
            {
                goto none;
            }
        }
        else if (!(flags & 2) || (flags & 4))
        {
            goto none;
        }
        chunk = state->buffer + chunkSize * state->unk158;
        *region = &regions[state->unk158];
        state->regions[state->unk158].flags = 4;
        index = state->unk158;
        next = index + 1;
        if (index + 1 == state->noItems)
        {
            next = 0;
        }
        state->unk158 = next;
        if (state->unk15C == index)
        {
            state->unk15C = next;
        }
    }
    else
    {
        rwaStreamRegion *entries = state->entries;
        RwUInt32    flags = entries[state->entry].flags;
        RwUInt32    next;

        if (!(state->flags & 0x2000))
        {
            if (!(flags & 2) || (flags & 4))
            {
                goto none;
            }
        }
        else if (!(flags & 2))
        {
            goto none;
        }
        chunk = state->aheadBuffer + chunkSize * state->entry;
        *region = &entries[state->entry];
        state->entries[state->entry].flags = 4;
        next = state->entry + 1;
        if (next == state->noEntries)
        {
            next = 0;
        }
        state->entry = next;
    }

    state->unkFC--;
    ReleaseSemaphore(state->semaphore, 1, NULL);
    return chunk;

none:
    ReleaseSemaphore(state->semaphore, 1, NULL);
    return NULL;
}

/* A chunk has been played: free again (1), and the next one to fill. */
// match: _sub_247E00 @ 0x00247E00
void
sub_247E00(rwaDecoderState *state, RwUInt8 *chunk)
{
    RwUInt32    chunkSize;

    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
    chunkSize = state->info->unk20;
    if (chunk < state->buffer || chunk >= state->buffer + state->bufferSize)
    {
        state->entries[(RwUInt32)(chunk - state->aheadBuffer) / chunkSize].flags = 1;
        ReleaseSemaphore(state->semaphore, 1, NULL);
        return;
    }
    else
    {
        RwUInt32    index = (RwUInt32)(chunk - state->buffer) / chunkSize;
        RwUInt32    noItems;
        RwUInt32    next;

        state->regions[index].flags = 1;
        noItems = state->noItems;
        next = index + 1;
        if (next == noItems)
        {
            next = 0;
        }
        if (next == state->unk158)
        {
            state->unk154 = state->unk15C;
            state->unk158 = state->unk154;
        }
        else
        {
            RwUInt32    i = state->unk154;
            RwBool      first = TRUE;

            while (state->regions[i].flags & 1)
            {
                if (++i == noItems)
                {
                    i = 0;
                    if (!first)
                    {
                        break;
                    }
                    first = FALSE;
                }
            }
            state->unk154 = i;
        }
        ReleaseSemaphore(state->semaphore, 1, NULL);
    }
}

/* How many times the largest track's chunks wrap past the current marker:
 * -1 for once. */
// match: _sub_247F20 @ 0x00247F20
RwInt32
sub_247F20(rwaDecoderState *state)
{
    rwaStreamInfo *info = state->info;
    RwUInt32    result = 0;
    RwUInt32    largest = 0;
    RwUInt32    track = 0;
    rwaStreamMarker *marker = state->current;
    RwUInt32   *chunk;

    if (!info->noTracks)
    {
        return result;
    }

    chunk = &info->tracks[0].unk20;
    do
    {
        RwUInt32    size = marker->unk0C[track];

        if (size > largest)
        {
            RwUInt32    unit = *chunk;
            RwUInt32    high;
            RwUInt32    count;

            largest = size;
            count = size % unit;
            sub_2420D0(size % unit, 0xFFFFFFFF / unit, &high, &count);
            if (++count > result)
            {
                result = count;
            }
        }
        track++;
        chunk += sizeof(rwaStreamTrack) / sizeof(RwUInt32);
    }
    while (track < state->info->noTracks);

    if (result == 1)
    {
        return -1;
    }
    return result;
}

/* Seeks to a position (in track's bytes) within the marker: a read from
 * the chunk holding it, the chunks to play from it and the chunks before
 * the marker's end. */
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

    sub_2420D0(chunk, unit, &position, &track);
    skip = position - track;
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
    sub_2420D0(skip, 0xFFFFFFFF / (t->unk20 / (channels * t->unk1A)), &position, &skip);
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
        ReleaseSemaphore(state->semaphore, 1, NULL);
        return FALSE;
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
    ReleaseSemaphore(state->semaphore, 1, NULL);
    return TRUE;
}

/* Stops reading: the pending reads finish, the chunks are free again. */
// match: _sub_2481E0 @ 0x002481E0
void
sub_2481E0(rwaDecoderState *state)
{
    rwaStreamRegion *region;
    RwUInt8    *chunk;

    if (!(state->flags & 0x8000))
    {
        return;
    }

    sub_24D640(&state->cache);
    sub_244F60(&state->client);
    state->flags &= ~0x28;
    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
    state->flags |= 0x2000;
    while (state->regions[state->region].flags & 8)
    {
        state->regions[state->region].flags = 1;
        state->region++;
        if (state->region == state->noItems)
        {
            state->region = 0;
        }
    }
    ReleaseSemaphore(state->semaphore, 1, NULL);

    do
    {
        chunk = sub_247C50(state, &region);
        if (chunk)
        {
            sub_247E00(state, chunk);
        }
    }
    while (chunk);

    if (state->flags & 0x10000)
    {
        RwUInt32    i;

        for (i = 0; i < state->noItems; i++)
        {
            state->regions[i].flags = 1;
        }
    }
    if (state->entries)
    {
        state->entries[state->unk174].unk0C = 0;
    }
    state->unk154 = 0;
    state->unk158 = 0;
    state->region = 0;
    state->unk15C = 0;
    state->unk14C = 0;
    state->flags &= ~0x2000;
}

/* The track's position in a region. */
// match: _sub_248360 @ 0x00248360
RwUInt32
sub_248360(rwaDecoderState *state, rwaStreamRegion *region, RwUInt32 track)
{
    RwUInt32    size = sub_2433C0((const RwaWaveFormat *)state->info->tracks[track].format,
                                  state->info->tracks[track].unk20);
    RwUInt32    base = size * region->unk04;

    sub_2420D0(region->unk08, size, (RwUInt32 *)&state, &track);
    return base + (RwUInt32)state;
}

// match: _sub_2483B0 @ 0x002483B0
void
sub_2483B0(rwaDecoderState *state, const RwaUUID *uuid)
{
    state->marker = &state->info->markers[sub_247510(state, uuid)];
}

// match: _sub_2483E0 @ 0x002483E0
void
sub_2483E0(rwaDecoderState *state, const RwChar *name)
{
    state->marker = &state->info->markers[sub_247570(state, name)];
}

/* Keeps the reads and the look-ahead copy going. */
// match: _sub_248410 @ 0x00248410
void
sub_248410(rwaDecoderState *state)
{
    rwaStreamRegion *regions;

    if ((state->cache.unk06 != state->cache.unk08 || state->cache.unk0A)
        && !(state->flags & 0x22FF8)
        && sub_24D5B0(&state->cache, &state->unkD8))
    {
        sub_2475D0(state);
    }

    regions = state->regions;
    if (!(regions[state->unk15C].flags & 1) && state->aheadBuffer)
    {
        rwaStreamRegion *entries = state->entries;

        if (!(entries[state->unk174].flags & 6))
        {
            if (regions[state->unk154].unk0C || entries[state->unk174].unk0C
                || ((regions[state->unk154].flags & 0x10) && state->loops != -1))
            {
                state->flags |= 0x10000;
                sub_247660(state);
            }
            else if (entries[state->entry].flags == 1)
            {
                state->flags &= ~0x10000;
            }
        }
    }
}

/* Reads the next chunks from the file into the free playing chunks. */
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
        else if (state->unk14C <= state->unk154)
        {
            free = state->unk154 - state->unk14C;
        }
        else
        {
            free = state->unk154 + state->noItems - state->unk14C;
        }
        if (free < state->noItems - state->unk184)
        {
            break;
        }

        if (state->unkF8)
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
                if (state->unkF0 == state->unkF4)
                {
                    region->unk0C = 0;
                }
                else
                {
                    region->unk0C = state->unkF4;
                    state->unkF0 = state->unkF4;
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
                state->regions[last - 1].flags |= 0x10;
            }
            ReleaseSemaphore(state->semaphore, 1, NULL);
            return result;
        }

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
    }
    ReleaseSemaphore(state->semaphore, 1, NULL);
    return 3;
}

/* The stream cache's callback: the steps of opening the stream (its file
 * header, the stream's header and information, the chunk buffers), then
 * each completed read. A failed step (event 4) notifies and releases. */
// match: _sub_248810 @ 0x00248810
static void
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
                    state->regions[state->region].flags |= 4;
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
        if (status != 4)
        {
            state->flags |= 4;
            state->flags |= 0x40;
            sub_245160(state->client.holder, &state->client, state->header, &state->header,
                       (rwaCacheCallBack)sub_248810, state);
            return;
        }
        if (state->notify)
        {
            state->notify(state, 6, state->notifyData);
        }
        sub_247430(state);
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

/* Sets up a stream source's node state from its creation parameters, and
 * opens a named stream file. */
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
    state->buffer = (RwUInt8 *)params->values[11];
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

    if (params->values[5] != 1)
    {
        return FALSE;
    }
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

// match: _RwaStreamNodeInterfaceRegister @ 0x002493D0
void *
RwaStreamNodeInterfaceRegister(void)
{
    if (!sub_243E20(dword_5079D4))
    {
        return NULL;
    }

    RwaWaveDictAssignID(dword_5079D4, unk_3ED964, NULL);
    sub_243CD0(dword_5079D4, off_42FB54, 3, off_42FB90, 2);

    return dword_5079D4;
}

// match: _sub_249420 @ 0x00249420
RwBool
sub_249420(void)
{
    return sub_243EA0(dword_5079D4);
}

// match: _RwaStreamSourceInterfaceRegister @ 0x00249430
void *
RwaStreamSourceInterfaceRegister(void)
{
    if (!sub_243E20(dword_5079FC))
    {
        return NULL;
    }

    RwaWaveDictAssignID(dword_5079FC, unk_3ED9C4, NULL);
    sub_243CD0(dword_5079FC, off_42FBB8, 5, off_42FC20, 5);

    return dword_5079FC;
}

// match: _sub_249480 @ 0x00249480
RwBool
sub_249480(void)
{
    return sub_243EA0(dword_5079FC);
}
