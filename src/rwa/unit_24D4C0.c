/*
 * codfh-match: RenderWare Audio's read request ring (0x24D4C0-0x24D670): the
 * stream source reader's cache (unit_247430.c) queues its file reads here
 * under a semaphore and the reads are taken off in order.
 */
#include "rwa.h"
#include "rwaint.h"

extern RwUInt32 __stdcall WaitForSingleObject(void *handle, RwUInt32 milliseconds);
extern RwBool __stdcall ReleaseSemaphore(void *semaphore, RwInt32 count, RwInt32 *previous);
extern RwBool __stdcall CloseHandle(void *handle);
extern void **sub_2416D0(void **semaphore, RwInt32 initial, RwInt32 maximum);

#define rwaINFINITE 0xFFFFFFFF

// match: _sub_24D4C0 @ 0x0024D4C0
rwaReadCache *
sub_24D4C0(rwaReadCache *cache, rwaReadRequest *requests, RwUInt16 size)
{
    cache->requests = requests;
    cache->size = size;
    cache->unk06 = 0;
    cache->unk08 = 0;
    cache->unk0A = 0;

    return sub_2416D0(&cache->semaphore, 1, 1) ? cache : NULL;
}

// match: _sub_24D500 @ 0x0024D500
void
sub_24D500(rwaReadCache *cache)
{
    CloseHandle(cache->semaphore);
}

/* Queues a read (FALSE when the ring is full). */
// match: _sub_24D510 @ 0x0024D510
RwBool
sub_24D510(rwaReadCache *cache, void *dest, RwUInt32 size, RwUInt32 offset, RwUInt32 e,
           RwInt32 kind)
{
    rwaReadRequest *request;
    RwUInt32    next;

    WaitForSingleObject(cache->semaphore, rwaINFINITE);
    if (cache->unk06 == cache->unk08 && cache->unk0A)
    {
        ReleaseSemaphore(cache->semaphore, 1, NULL);
        return FALSE;
    }

    request = &cache->requests[cache->unk06];
    request->dest = dest;
    request->size = size;
    request->kind = kind;
    request->offset = offset;
    request->e = e;
    next = cache->unk06 + 1;
    if (next == cache->size)
    {
        next = 0;
    }
    if (next == cache->unk08)
    {
        cache->unk0A = 1;
    }
    cache->unk06 = (RwUInt16)next;
    ReleaseSemaphore(cache->semaphore, 1, NULL);

    return TRUE;
}

/* Takes the next read off (FALSE when there is none). */
// match: _sub_24D5B0 @ 0x0024D5B0
RwBool
sub_24D5B0(rwaReadCache *cache, rwaReadRequest *out)
{
    rwaReadRequest *request;
    RwUInt32    next;

    WaitForSingleObject(cache->semaphore, rwaINFINITE);
    if (cache->unk06 == cache->unk08 && !cache->unk0A)
    {
        ReleaseSemaphore(cache->semaphore, 1, NULL);
        return FALSE;
    }

    request = &cache->requests[cache->unk08];
    out->dest = request->dest;
    out->e = request->e;
    out->kind = request->kind;
    out->offset = request->offset;
    out->size = request->size;
    next = cache->unk08 + 1;
    cache->unk0A = 0;
    if (next == cache->size)
    {
        next = 0;
    }
    cache->unk08 = (RwUInt16)next;
    ReleaseSemaphore(cache->semaphore, 1, NULL);

    return TRUE;
}

/* Drops the queued reads. */
// match: _sub_24D640 @ 0x0024D640
void
sub_24D640(rwaReadCache *cache)
{
    WaitForSingleObject(cache->semaphore, rwaINFINITE);
    cache->unk08 = cache->unk06;
    cache->unk0A = 0;
    ReleaseSemaphore(cache->semaphore, 1, NULL);
}
