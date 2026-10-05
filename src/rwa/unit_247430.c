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

extern RwUInt8 dword_5079D4[];      /* the stream node interface */
extern RwUInt8 dword_5079FC[];      /* the stream source interface */
extern const RwUInt8 unk_3ED964[];
extern RwChar unk_42FB48[];   /* the stream file extensions */
extern RwChar aRws1[];

RwUInt8 *sub_247C50(rwaDecoderState *state, rwaStreamRegion **region);
void sub_247E00(rwaDecoderState *state, RwUInt8 *chunk);


/* Releases what the state holds once. */
/* Reads one available batch and publishes its regions before unlocking. */
static __forceinline RwInt32
rwaStreamReadBatch(rwaDecoderState *state, RwUInt32 chunkSize, RwUInt32 free)
{
    RwInt32 result = 1;
    RwUInt32 count = state->unk180;
    RwUInt32 bytes;
    RwUInt32 at;
    RwUInt32 first;
    RwUInt32 read;
    RwUInt32 rest;

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
        if (sub_24D510(&state->cache, at + state->buffer, first, 0, 0, 4))
        {
            read = first;
        }
        else
        {
            ReleaseSemaphore(state->semaphore, 1, NULL);
            return 2;
        }
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
    for (; read;)
    {
        rwaStreamRegion *region = &state->regions[state->unk14C];
        RwUInt32 next;

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
        RwUInt32 last = state->unk14C;

        if (last > 0)
        {
            --last;
        }
        else
        {
            last = state->noItems;
            --last;
        }
        /* Evidence: qualify the flags read at 0x2487E5 to reproduce this
         * update and the following EDX semaphore load at 0x2487F2.
         * This does not establish the original volatile declaration. */
        state->regions[last].flags =
            (*(const volatile RwUInt32 *)&state->regions[last].flags) | 0x10;
    }
    ReleaseSemaphore(state->semaphore, 1, NULL);
    return result;
}


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3EDA14 @ 0x003EDA14
// match: _unk_3EDA04 @ 0x003EDA04
// match: _unk_3ED9F4 @ 0x003ED9F4
// match: _unk_3ED9E4 @ 0x003ED9E4
// match: _unk_3ED9D4 @ 0x003ED9D4
// match: _unk_3ED9C4 @ 0x003ED9C4
// match: _unk_3ED9B4 @ 0x003ED9B4
// match: _unk_3ED9A4 @ 0x003ED9A4
// match: _unk_3ED994 @ 0x003ED994
// match: _unk_3ED984 @ 0x003ED984

// What its data definitions name.
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED55C[];
extern RwUInt8 unk_3ED56C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED974
const RwaUUID unk_3ED974 = { 0x529307C9, 0xFF22, 0x4BBE, { 0xB0, 0x92, 0x2E, 0x8C, 0x10, 0x7A, 0x91, 0x57 } };
// 0x003ED984
const RwaUUID unk_3ED984 = { 0xA35774AE, 0x4D48, 0x4594, { 0xA5, 0x6D, 0xA7, 0xDE, 0xA9, 0xB7, 0xEE, 0x49 } };
// 0x003ED994
const RwaUUID unk_3ED994 = { 0xE7AB3C4D, 0x4F7E, 0x402C, { 0xAB, 0xC4, 0x56, 0x25, 0x9B, 0x74, 0x43, 0x83 } };
// 0x003ED9A4
const RwaUUID unk_3ED9A4 = { 0x8D164F4B, 0xD7C8, 0x48FB, { 0x9E, 0x71, 0x80, 0xFD, 0xD8, 0xDE, 0xE9, 0x07 } };
// 0x003ED9B4
const RwaUUID unk_3ED9B4 = { 0x75979B67, 0xBD1C, 0x4DC4, { 0xBF, 0x4F, 0xBD, 0x00, 0x8A, 0xFB, 0xD1, 0xAB } };
// 0x003ED9C4
const RwaUUID unk_3ED9C4 = { 0x2D2C990F, 0x083A, 0x4F3B, { 0xA2, 0xE8, 0x05, 0xD3, 0xF3, 0x00, 0x82, 0x06 } };
// 0x003ED9D4
const RwaUUID unk_3ED9D4 = { 0x3D23255E, 0x2D66, 0x441F, { 0xBC, 0x4C, 0x54, 0x16, 0x85, 0x49, 0x9A, 0x58 } };
// 0x003ED9E4
const RwaUUID unk_3ED9E4 = { 0x441D82F5, 0x86CA, 0x485D, { 0x84, 0xA6, 0xEB, 0x57, 0xCA, 0xD6, 0x4B, 0x9B } };
// 0x003ED9F4
const RwaUUID unk_3ED9F4 = { 0x7C839741, 0x3391, 0x41CE, { 0xAB, 0x84, 0x02, 0x7D, 0xC9, 0x6D, 0x52, 0xD0 } };
// 0x003EDA04
const RwaUUID unk_3EDA04 = { 0x822E06F1, 0xE5B2, 0x4C3E, { 0xAD, 0x4C, 0x9C, 0x79, 0xA6, 0xC6, 0x93, 0x9F } };
// 0x003EDA14
const RwaUUID unk_3EDA14 = { 0x4312D242, 0x793A, 0x4B79, { 0x98, 0xCE, 0xD0, 0xA8, 0x1D, 0x64, 0x40, 0x29 } };
// 0x0042FB48
RwChar unk_42FB48[4] = "rws";
// 0x0042FB4C
RwChar aRws1[8] = "rws;1";
// 0x0042FB54
void *off_42FB54[15] =
{
    (void *)&unk_3ED974,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED984,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED9B4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
};
// 0x0042FB90
void *off_42FB90[10] =
{
    (void *)&unk_3ED994,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED9A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
};
// 0x0042FBB8
void *off_42FBB8[26] =
{
    (void *)&unk_3ED9D4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED9F4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED974,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED984,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED9B4,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    0,
};
// 0x0042FC20
void *off_42FC20[26] =
{
    (void *)&unk_3ED9E4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3EDA04,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3EDA14,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED994,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED9A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    0,
};
// 0x005079D4
RwUInt8 dword_5079D4[40];
// 0x005079FC
RwUInt8 dword_5079FC[424];
// End of its data definitions.

// match: _unk_3ED974 @ 0x003ED974


// match: _unk_42FB48 @ 0x0042FB48


// match: _aRws1 @ 0x0042FB4C


// match: _off_42FB54 @ 0x0042FB54


// match: _off_42FB90 @ 0x0042FB90


// match: _off_42FBB8 @ 0x0042FBB8


// match: _off_42FC20 @ 0x0042FC20

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
        const RwaUUID *markerUUID = state->info->markers[i].uuid;

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
        const RwChar *markerName = state->info->markers[i].name;

        if (markerName && !rwstrcmp(markerName, name))
        {
            return i;
        }
    }

    return 0;
}
void sub_248810(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event, void *data);
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

/* Reference: rwad.dll 0x100B6FE1 names this
 * _RwaStreamSourceReinterleave in rwastreamsourcecommon.c. It returns
 * the completed interleave buffer pointer. Narrow counters and the
 * two 64-bit copies follow the debug routine.
 * The unk174 access qualifiers preserve the observed repeated reads
 * at 0x2476F6 and 0x247B24; original declarations remain unestablished. */
// match: _sub_247660 @ 0x00247660
RwUInt8 *
sub_247660(rwaDecoderState *state)
{
    RwUInt8 *result = NULL;
    rwaStreamInfo *info = state->info;
    RwUInt32    chunkSize = info->unk20;
    RwUInt32    noTracks = info->noTracks;

    while (!result && (state->regions[state->unk15C].flags & 2))
    {
        rwaStreamRegion *from;
        rwaStreamRegion *to;
        RwUInt8    *src;
        RwUInt8    *dst;
        RwUInt32    srcBytes;
        RwUInt32    dstBytes;
        RwUInt32    track;
        RwBool      dstFull;
        RwBool      srcEmpty;

        dst = state->buffer + chunkSize * state->unk15C;
        src = state->aheadBuffer + chunkSize * state->unk174;
        to = &state->regions[state->unk15C];
        from = &state->entries[state->unk174];
        dstBytes = to->unk0C;
        srcBytes = from->unk0C;

        for (track = 0; track < noTracks; track++)
        {
            rwaStreamTrack *t = &info->tracks[track];
            RwUInt16 unitCount = t->unk1C;
            RwUInt16 unitSize = t->unk18;
            RwUInt8 channels = t->format->channels;
            RwUInt16 step = t->unk1A;
            RwUInt32 size;
            RwUInt32    kind;
            RwUInt32    count;
            RwUInt32    dstAt;
            RwUInt32    srcAt;
            RwUInt32    end;
            RwUInt32    bytes;
            RwUInt32    remainder;
            RwUInt8    *s;
            RwUInt8    *d;
            RwUInt8 c;
            RwUInt16 sBlock, dBlock;
            RwUInt32 sOffset, dOffset, skip;
            RwUInt32 dstRemaining, srcRemaining;

            if (!(step & 1)) { kind = 2; count = step >> 1; }
            else if (!(step & 3)) { kind = 3; count = step >> 2; }
            else if (!(step & 7)) { kind = 4; count = step >> 3; }
            else if (!(step & 15)) { kind = 5; count = step >> 4; }
            else { kind = 1; count = step; }
            size = unitCount * unitSize;
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
            dstRemaining = end - dstAt;
            srcRemaining = size - srcAt;
            bytes = dstRemaining > srcRemaining ? srcRemaining : dstRemaining;
            if (noTracks - 1 == track)
            {
                dstFull = (end == dstAt + bytes);
                srcEmpty = (size == srcAt + bytes);
            }

            sBlock = (RwUInt16)(dstAt / unitSize);
            sOffset = (RwUInt16)(dstAt - sBlock * unitSize);
            dBlock = (RwUInt16)(srcAt / unitSize);
            dOffset = srcAt - dBlock * unitSize;
            skip = unitSize * (channels - 1);
            s = dst + t->unk24 + sOffset + sBlock * unitSize * channels;
            d = src + t->unk24 + dOffset + dBlock * unitSize * channels;
            for (c = 0; c < channels; c++)
            {
                RwUInt8    *sp = s;
                RwUInt8    *dp = d;
                RwUInt16 sLeft = (RwUInt16)(unitSize - sOffset);
                RwUInt16 dLeft = (RwUInt16)(unitSize - dOffset);
                RwUInt16 left = (RwUInt16)bytes;

                while (left)
                {
                    RwUInt16 n;

                    if (!sLeft)
                    {
                        sLeft = unitSize;
                        sp += skip;
                    }
                    if (!dLeft)
                    {
                        dLeft = unitSize;
                        dp += skip;
                    }
                    switch (kind)
                    {
                    case 1:
                        for (n = 0; n < count; n++)
                        {
                            *dp = *sp;
                            sp++;
                            dp++;
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
                        for (n = 0; n < count; n++) {
                            *(RwUInt64 *)dp = *(RwUInt64 *)sp;
                            sp += 8;
                            dp += 8;
                        }
                        break;
                    case 5:
                        for (n = 0; n < count; n++) {
                            *(RwUInt64 *)dp = *(RwUInt64 *)sp;
                            sp += 8;
                            dp += 8;
                            *(RwUInt64 *)dp = *(RwUInt64 *)sp;
                            sp += 8;
                            dp += 8;
                        }
                        break;
                    }
                    sLeft -= step;
                    dLeft -= step;
                    left -= step;
                }
                if (step > unitSize)
                {
                    s += bytes;
                    d += bytes;
                }
                else
                {
                    s += unitSize;
                    d += unitSize;
                }
            }

            if (noTracks - 1 == track)
            {
                from->marker = to->marker;
                from->unk04 = to->unk04;
                from->unk08 = state->unkF0;
                if (srcEmpty)
                {
                    from->unk0C = 0;
                    from->flags = 2;
                    result = src;
                    state->unk174++;
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
                    RwUInt32 previous, next;

                    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
                    to->unk0C = 0;
                    to->flags = 1;
                    previous = state->unk15C;
                    next = previous + 1;
                    if (next == state->noItems)
                    {
                        next = 0;
                    }
                    state->unk15C = next;
                    if (state->unk154 == previous)
                    {
                        state->unk154 = next;
                        state->unk158 = next;
                    }
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
    return result;
}

// match: _sub_247C50 @ 0x00247C50
RwUInt8 *
sub_247C50(rwaDecoderState *state, rwaStreamRegion **region)
{
    RwUInt8    *chunk;
    RwUInt32    chunkSize;

    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
    chunkSize = state->info->unk20;

    if (state->flags & 0x10000)
    {
        rwaStreamRegion *entries = state->entries;
        RwUInt32    flags = ((volatile rwaStreamRegion *)entries)[state->entry].flags;
        RwUInt32    next;

        if (state->flags & 0x2000) { if (!(flags & 2)) { ReleaseSemaphore(state->semaphore, 1, NULL); return NULL; } }
        else if (!(flags & 2) || (flags & 4)) { ReleaseSemaphore(state->semaphore, 1, NULL); return NULL; }
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
    else
    {
        rwaStreamRegion *regions = state->regions;
        RwUInt32    flags = ((volatile rwaStreamRegion *)regions)[state->unk158].flags;
        RwUInt32    index;
        RwUInt32    next;

        if (state->flags & 0x2000)
        {
            if (!(flags & 2))
            {
                { ReleaseSemaphore(state->semaphore, 1, NULL); return NULL; }
            }
        }
        else if (!(flags & 2) || (flags & 4))
        {
            { ReleaseSemaphore(state->semaphore, 1, NULL); return NULL; }
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
        goto unlock;
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
    }
unlock:
    ReleaseSemaphore(state->semaphore, 1, NULL);
}

/* Stops reading: the pending reads finish, the chunks are free again. */
/* Returns the wrap count for the current marker, or -1 for once. */
// match: _sub_247F20 @ 0x00247F20
RwInt32
sub_247F20(rwaDecoderState *state)
{
    rwaStreamMarker *marker = state->current;
    rwaStreamInfo *info = state->info;
    RwUInt32 count;
    RwUInt32 result = 0;
    RwUInt32 largest = 0;
    RwUInt32 track = 0;
    rwaStreamTrack *tracks = info->tracks;

    if (info->noTracks > 0)
    {
        do
        {
            RwUInt32 size = marker->unk0C[track];

            if (size > largest)
            {
                RwUInt32 *sizePtr = &marker->unk0C[track];
                RwUInt32 unit = tracks->unk20;
                RwUInt32 high;

                largest = *sizePtr;
                count = largest % unit;
                sub_2420D0(count, 0xFFFFFFFF / unit, &high, &count);
                if (++count > result)
                {
                    result = count;
                }
            }
            track++;
            tracks++;
        }
        while (track < state->info->noTracks);

        if (result == 1)
        {
            result = -1;
        }
    }
    return result;
}

/* Seeks to a byte position in one track of the selected marker. */
// match: _sub_247FE0 @ 0x00247FE0
RwBool
sub_247FE0(rwaDecoderState *state, RwUInt32 track, RwUInt32 position)
{
    rwaStreamTrack *t = &state->info->tracks[track];
    RwUInt32 unit = t->unk20;
    RwUInt32 chunk = position / unit;
    RwUInt32 skip;
    RwUInt32 channels;
    rwaStreamInfo *info;
    RwUInt32 offset;

    {
        RwUInt32 high, low;
        sub_2420D0(chunk, unit, &high, &low);
        skip = position - low;
    }
    track = skip;
    channels = 1;
    if (!(t->format->flags & 4))
    {
        channels = t->format->channels;
    }
    if (skip % (channels * t->unk1A))
    {
        skip = channels * t->unk1A
            * (((channels * t->unk1A) + skip - 1) / (channels * t->unk1A));
    }
    skip /= channels * t->unk1A;
    {
        RwUInt32 high;
        sub_2420D0(skip, 0xFFFFFFFF / (t->unk20 / (channels * t->unk1A)), &high, &skip);
    }
    if (skip & 0xFFFFFFFE)
    {
        skip++;
    }

    info = state->info;
    if (info->noTracks > 0)
    {
        RwUInt16 *step = &info->tracks[0].unk1A;
        RwUInt32 n = info->noTracks;

        do
        {
            RwUInt32 b = channels * *step;

            if (track % b)
            {
                track = b * ((b + track - 1) / b);
            }
            step += sizeof(rwaStreamTrack) / sizeof(RwUInt16);
        }
        while (--n);
    }

    offset = chunk * info->unk20;
    offset += state->marker->unk1C;
    /* Evidence: 0x248118 reads info+0x24 after the marker offset. Qualify
     * this access to preserve that order; the original declaration is unknown. */
    offset += ((const volatile rwaStreamInfo *)info)->unk24;
    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
    if (sub_24D510(&state->cache, NULL, 0, offset, 0, 1))
    {
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
    else
    {
        ReleaseSemaphore(state->semaphore, 1, NULL);
        return FALSE;
    }
}

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

/* How many times the largest track's chunks wrap past the current marker:
 * -1 for once. */

// match: _sub_248360 @ 0x00248360
RwUInt32
sub_248360(rwaDecoderState *state, rwaStreamRegion *region, RwUInt32 track)
{
    RwUInt32    size = sub_2433C0((const RwaWaveFormat *)state->info->tracks[track].format,
                                  state->info->tracks[track].unk20);
    RwUInt32    base = size * region->unk04;

    {
        RwUInt32 high, low;

        sub_2420D0(region->unk08, size, &high, &low);
        return high + base;
    }
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

/* Copies the look-ahead chunks into the playing chunks, track by track and
 * channel by channel (the samples of a track's channels are interleaved in
 * units of its channel step), until a playing chunk is filled. */
// match: _sub_248410 @ 0x00248410
void
sub_248410(rwaDecoderState *state)
{
    rwaStreamRegion *regions;

    if ((state->cache.unk06 != state->cache.unk08 || state->cache.unk0A)
        && !(state->flags & 0x22FF8) /* flag mask, not an address */
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
            /* Evidence: 0x2484AC reloads the look-ahead index after the
             * preceding flag test. Qualify this access to preserve that
             * reload; this does not establish the original declaration. */
            if (regions[state->unk154].unk0C || entries[((volatile rwaDecoderState *)state)->unk174].unk0C
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

/* Waits for an available region, seeking to the marker again when needed. */
// match: _sub_248520 @ 0x00248520
RwInt32
sub_248520(rwaDecoderState *state)
{
    WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
    for (;;)
    {
        if (!(state->regions[state->unk14C].flags == 1))
        {
            ReleaseSemaphore(state->semaphore, 1, NULL);
            return 3;
        }
        {
            RwUInt32 chunkSize = state->info->unk20;
            RwUInt32 free;

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
                ReleaseSemaphore(state->semaphore, 1, NULL);
                return 3;
            }

            if (!state->unkF8)
            {
                ReleaseSemaphore(state->semaphore, 1, NULL);
                if (state->flags & 0x4000)
                {
                    if (sub_247FE0(state, 0, 0))
                    {
                        WaitForSingleObject(state->semaphore, 0xFFFFFFFF);
                        continue;
                    }
                    return 0;
                }
                return 4;
            }
            {
                return rwaStreamReadBatch(state, chunkSize, free);
            }
        }
    }
}

extern void sub_248810(void *, RwUInt32, RwInt32, RwInt32, void *);
extern RwUInt8 *sub_247660(rwaDecoderState *);

/* Reference: rwad.dll 0x100B3434 names this
* _RwaStreamSourceFileOpCallback, in rwastreamsourcecommon.c.
* Its data argument is copied into a typed state local. */
// match: _sub_248810 @ 0x00248810
void
sub_248810(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event, void *data)
{
    rwaDecoderState *state = (rwaDecoderState *)data;
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
                    /* Evidence: the 0x2488E9 update uses separate load/OR/store.
                    * This access qualifier does not establish the original declaration. */
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
        if (state->notify) { status |= 1; state->notify(state, status, state->notifyData); }
        sub_247430(state);
        return;
    }

    if (state->flags & 0x80)
    {
        RwUInt32    size = 0;

        state->flags &= ~0x80;
        if (status == 4)
        {
            if (state->notify) { state->notify(state, 5, state->notifyData); }
            sub_247430(state);
            return;
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
        if (state->notify) { status |= 1; state->notify(state, status, state->notifyData); }
        sub_247430(state);
        return;
    }

    if (state->flags & 0x800)
    {
        const RwaUUID *uuid = NULL;
        const RwChar *name = NULL;
        RwBool      found = FALSE;

        state->flags &= ~0x800;
        if (status == 4)
        {
            state->free(state->info, state->allocData);
            state->info = NULL;
            if (state->notify) { state->notify(state, 5, state->notifyData); }
            sub_247430(state);
            return;
        }
        if (state->uuidSize)
        {
            uuid = (const RwaUUID *)state->info;
        }
        if (state->nameSize)
        {
            const RwChar *idData = (const RwChar *)state->info;
            name = idData + state->uuidSize;
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
            if (state->notify) { state->notify(state, 5, state->notifyData); }
            sub_247430(state);
            return;
        }
        if (!sub_24D670(state->info))
        {
            state->free(state->info, state->allocData);
            state->info = NULL;
            if (state->notify) { status |= 1; state->notify(state, status, state->notifyData); }
            sub_247430(state);
            return;
        }

        state->flags |= 0x200;
        sub_2449E0(&state->client,
        sub_244A20(&state->client) + state->unk84 - state->infoSize - 20,
        (rwaCacheCallBack)sub_248810, state);
        return;
    }

    if (state->flags & 0x200)
    {
        state->flags &= ~0x200;
        if (status == 4)
        {
            state->free(state->info, state->allocData);
            state->info = NULL;
            if (state->notify) { state->notify(state, 5, state->notifyData); }
            sub_247430(state);
            return;
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
            if (state->notify) { status |= 1; state->notify(state, status, state->notifyData); }
            sub_247430(state);
            return;
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
                if (state->notify) { status |= 1; state->notify(state, status, state->notifyData); }
                sub_247430(state);
                return;
            }
            state->bufferSize = size;
        }
        if (!state->aheadSize && state->noEntries > 0)
        {
            RwUInt32    size = state->noEntries * (chunkSize + 20);

            state->aheadBuffer = (RwUInt8 *)sub_242180(size, rwaMEMHINTDUR_EVENT | rwaID_80E);
            if (!state->aheadBuffer)
            {
                if (state->notify) { status |= 1; state->notify(state, status, state->notifyData); }
                sub_247430(state);
                return;
            }
            state->aheadSize = size;
        }

        state->noItems = state->bufferSize / (chunkSize + 56);
        state->noEntries = state->aheadSize / (chunkSize + 20);
        state->bufferSize = state->noItems * chunkSize;
        state->regions = (rwaStreamRegion *)(state->buffer + state->bufferSize);
        state->positions = (rwaStreamPosition *)(sizeof(rwaStreamRegion) * state->noItems + (RwUInt8 *)state->regions);
        state->items = (rwaQueueItem *)(sizeof(rwaStreamPosition) * state->noItems + (RwUInt8 *)state->positions);
        state->aheadSize = state->noEntries * chunkSize;
        if (!state->aheadSize)
        {
            if (!(state->flags & 2) && state->aheadBuffer)
            {
                sub_2421B0(state->aheadBuffer);
            }
            state->aheadBuffer = NULL;
        }
        state->entries = (rwaStreamRegion *)(state->aheadBuffer + state->aheadSize);

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
            state->unk180 = state->unk180 ? state->unk180 : 1;
        }
        if (state->unk180 >= state->noItems)
        {
            state->unk180 = state->noItems;
        }

        n = state->noEntries;
        for (i = 0; i < n; i++)
        {
            state->entries[i].unk0C = 0;
            state->entries[i].flags = 1;
        }
        n = state->noItems;
        for (i = 0; i < n; i++)
        {
            state->items[i].flags = 0;
            state->regions[i].unk0C = 0;
            state->regions[i].flags = 1;
        }

        state->current = state->info->markers;
        state->marker = state->current;
        state->loops = sub_247F20(state);
        state->flags |= 0x8000;
        sub_247FE0(state, 0, 0);
        sub_248410(state);
        if (state->notify)
        {
            state->notify(state, status == 4, state->notifyData);
        }
        return;
    }

reads:
    if (state->flags & (1u << 17))
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

}

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
    state->allocData = params->unk08;
    state->notify = (void (*)(rwaDecoderState *, RwInt32, void *))params->callback;
    state->notifyData = params->data;
    state->unk184 = params->values[8];
    state->unk180 = params->values[9];
    sub_240B40(&state->id);
    sub_240BF0(&state->id, params->unk1C);
    sub_240C10(&state->id, (const RwaUUID *)params->values[6]);
    state->aheadBuffer = params->unk38;
    state->aheadSize = params->values[13];
    state->buffer = params->unk2C;
    state->bufferSize = params->values[10];
    state->unk154 = 0;
    state->unk158 = 0;
    state->region = 0;
    state->unk14C = 0;
    state->unk15C = 0;
    state->regions = NULL;
    state->entry = 0;
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
    ext = sub_245210(params->unk10);
    state->flags |= 0x10;
    state->header = 2061;
    for (c = params->unk10; *c; c++)
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
    sub_2450C0(&state->file, &state->client, 2, 1, params->unk10,
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

    RwaWaveDictAssignID(dword_5079FC, &unk_3ED9C4, NULL);
    sub_243CD0(dword_5079FC, off_42FBB8, 5, off_42FC20, 5);

    return dword_5079FC;
}

// match: _sub_249480 @ 0x00249480
RwBool
sub_249480(void)
{
    return sub_243EA0(dword_5079FC);
}
