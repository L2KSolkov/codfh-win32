/*
 * codfh-match: RenderWare Audio's stream cache (0x2449C0-0x245240; the
 * database's _rwaRwStreamCacheOpenModule): asynchronous reads queued under
 * a lock (0x507184) for one worker (the idle semaphore 0x507180), through
 * a one-sector cache (0x507194, 0x800 bytes) or straight into aligned
 * destinations, and the clients that open, read and seek stream files
 * through it.
 */
#include "rwa.h"
#include "rwaint.h"

#define rwaSECTORSIZE   0x800
#define rwaINFINITE     0xFFFFFFFF

void *hHandle;                          /* the cache lock */
void *dword_507180;                     /* the idle worker */
void *dword_507184;                     /* the queue lock */
rwaLink dword_507188;                   /* queued requests */
rwaCacheRequest *dword_507190;   /* the active request */
RwUInt8 unk_507194[rwaSECTORSIZE];      /* the cache */
rwaCacheRequest *lpPreviousCount;    /* the cache's owner */
void *dword_507998;
RwUInt32 dword_50799C;           /* the cached sector's offset */
RwUInt32 dword_5079A0;           /* the cached bytes */

extern RwUInt32 __stdcall WaitForSingleObject(void *handle, RwUInt32 milliseconds);
extern RwBool __stdcall ReleaseSemaphore(void *semaphore, RwInt32 count, RwInt32 *previous);
extern RwBool __stdcall CloseHandle(void *handle);
extern void **sub_2416D0(void **semaphore, RwInt32 initial, RwInt32 maximum);
extern RwBool sub_2416F0(void **semaphore);
extern RwInt32 RwFtell(void *file);
extern RwInt32 RwFseek(void *file, RwInt32 offset, RwInt32 origin);
extern RwUInt32 RwFread(void *buffer, RwUInt32 size, RwUInt32 count, void *file);
extern RwInt32 RwFclose(void *file);
extern void RwFAsyncCancel(void *file);
extern void *RtFSManagerFOpen(const RwChar *name, RwUInt32 flags, void *callback, void *data);
extern void *memcpy(void *dst, const void *src, RwUInt32 size);

extern void sub_244B40(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event,
                       rwaCacheClient *client);
extern void sub_245060(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event,
                rwaCacheClient *client);

// match: _sub_2449C0 @ 0x002449C0
static void
sub_2449C0(void *file, rwaCacheClient *client, RwUInt32 bytes, RwInt32 status, RwInt32 event)
{
    client->holder->file = file;
    client->callback(file, bytes, status, event, client->data);
}

// match: _sub_2449E0 @ 0x002449E0
void
sub_2449E0(rwaCacheClient *client, RwUInt32 offset, rwaCacheCallBack callback, void *data)
{
    client->callback = callback;
    client->request.offset = offset;
    client->data = data;
    client->mode = 3;
    RwFseek(client->holder->file, offset / rwaSECTORSIZE * rwaSECTORSIZE, 0);
}

// match: _sub_244A20 @ 0x00244A20
RwUInt32
sub_244A20(rwaCacheClient *client)
{
    return client->request.offset;
}

// match: __rwaRwStreamCacheOpenModule @ 0x00244A30
RwBool
_rwaRwStreamCacheOpenModule(void)
{
    lpPreviousCount = NULL;
    dword_507998 = NULL;
    dword_50799C = 0xFFFFFFFF;
    dword_5079A0 = 0;
    sub_2416D0(&hHandle, 1, 1);

    dword_507190 = NULL;
    dword_507188.next = &dword_507188;
    dword_507188.prev = &dword_507188;
    sub_2416D0(&dword_507184, 1, 1);
    sub_2416D0(&dword_507180, 1, 1);

    return TRUE;
}

// match: _sub_244AA0 @ 0x00244AA0
void
sub_244AA0(void)
{
    WaitForSingleObject(hHandle, rwaINFINITE);
    CloseHandle(hHandle);
    WaitForSingleObject(dword_507184, rwaINFINITE);
    WaitForSingleObject(dword_507180, rwaINFINITE);
    CloseHandle(dword_507184);
    CloseHandle(dword_507180);
}

// match: _sub_244AF0 @ 0x00244AF0
static RwUInt32
sub_244AF0(rwaCacheRequest *request)
{
    RwUInt32    start = request->offset - dword_50799C;
    RwUInt32    count = dword_5079A0 - start;

    if (count >= request->remaining)
    {
        count = request->remaining;
    }

    memcpy(request->dest, &unk_507194[start], count);
    request->dest += count;
    request->remaining -= count;

    return count;
}

// match: _sub_244B40 @ 0x00244B40
void
sub_244B40(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event, rwaCacheClient *client)
{
    rwaCacheRequest *request = &client->request;
    RwInt32         result = status;
    RwUInt32        offset;
    RwUInt32        sector;
    RwUInt32        size;

    switch (event)
    {
        case 1:
        case 5:
          lock:
            WaitForSingleObject(hHandle, rwaINFINITE);

            do
            {
                if (request->state == 4)
                {
                    request->state = 3;

                    if (result == 4 || bytes != request->readSize)
                    {
                        goto complete;
                    }

                    if (request->readBuffer == unk_507194)
                    {
                        dword_5079A0 = bytes;
                        lpPreviousCount = request;
                        dword_507998 = file;
                        dword_50799C = request->readOffset;
                    }
                    else
                    {
                        request->dest += bytes;
                        request->offset += bytes;
                        request->remaining -= bytes;
                    }
                }

                offset = request->offset;
                sector = offset / rwaSECTORSIZE * rwaSECTORSIZE;
                if (lpPreviousCount == request && dword_50799C == sector)
                {
                    RwUInt32    count = sub_244AF0(request);

                    request->offset += count;
                    offset += count;
                    sector = offset / rwaSECTORSIZE * rwaSECTORSIZE;
                    result = 2;
                }

                if (request->remaining)
                {
                    if (!((RwUInt32)request->dest & 3) && offset == sector &&
                        request->remaining >= rwaSECTORSIZE)
                    {
                        size = request->remaining / rwaSECTORSIZE * rwaSECTORSIZE;
                        request->readBuffer = request->dest;
                        if (request == lpPreviousCount)
                        {
                            lpPreviousCount = NULL;
                            dword_507998 = NULL;
                        }
                    }
                    else
                    {
                        lpPreviousCount = NULL;
                        dword_507998 = NULL;
                        dword_50799C = 0xFFFFFFFF;
                        size = rwaSECTORSIZE;
                        request->readBuffer = unk_507194;
                    }

                    if (RwFtell(request->file) == (RwInt32)sector)
                    {
                        request->state = 4;
                        request->readOffset = sector;
                        request->readSize = size;
                        RwFread(request->readBuffer, 1, size, request->file);
                    }
                    else
                    {
                        request->state = 5;
                        RwFseek(request->file, sector, 0);
                    }

                    goto unlock;
                }

              complete:
                request->state = 1;
                request->callback(request->file, request->size, result, event, request->data);

                request = NULL;
                WaitForSingleObject(dword_507184, rwaINFINITE);

                if (dword_507188.next != &dword_507188)
                {
                    rwaLink    *next = dword_507188.next;

                    request = lpPreviousCount;
                    if (request && request->link.next)
                    {
                        next = &request->link;
                    }
                    else
                    {
                        request = (rwaCacheRequest *)next;
                    }

                    next->prev->next = next->next;
                    next->next->prev = next->prev;
                    next->next = NULL;
                    request->state = 3;
                }
                else
                {
                    ReleaseSemaphore(dword_507180, 1, NULL);
                }

                ReleaseSemaphore(dword_507184, 1, NULL);
                dword_507190 = request;
            }
            while (request);
          unlock:

            ReleaseSemaphore(hHandle, 1, NULL);

            return;

        case 2:
            request->unk24 = bytes;

            /* fall through */

        default:
            if (request->state == 5)
            {
                request->state = 3;
                goto lock;
            }

            request->callback(file, bytes, status, event, request->data);

            return;
    }
}

// match: _sub_244DC0 @ 0x00244DC0
static void
sub_244DC0(rwaCacheClient *client, RwUInt32 size, void *dest, rwaCacheCallBack callback,
           void *data)
{
    rwaCacheRequest *request = &client->request;

    request->state = 3;
    request->file = client->holder->file;
    request->size = size;
    request->remaining = size;
    request->dest = (RwUInt8 *)dest;
    request->callback = callback;
    request->data = data;

    WaitForSingleObject(dword_507184, rwaINFINITE);

    if (sub_2416F0(&dword_507180))
    {
        dword_507190 = request;
        ReleaseSemaphore(dword_507184, 1, NULL);
        sub_244B40(request->file, request->size, 0, 1, client);

        return;
    }

    request->link.next = dword_507188.next;
    request->link.prev = &dword_507188;
    dword_507188.next->prev = &request->link;
    dword_507188.next = &request->link;
    request->state = 2;

    ReleaseSemaphore(dword_507184, 1, NULL);
}

// match: _sub_244E70 @ 0x00244E70
void
sub_244E70(rwaCacheClient *client)
{
    RwBool          cancelled = FALSE;
    rwaCacheRequest *request = &client->request;

    WaitForSingleObject(hHandle, rwaINFINITE);
    WaitForSingleObject(dword_507184, rwaINFINITE);

    if (!sub_2416F0(&dword_507180))
    {
        if (dword_507190 == request)
        {
            RwFAsyncCancel(request->file);
            cancelled = TRUE;
            request->state = 3;
            request->remaining = 0;
        }

        if (lpPreviousCount == request)
        {
            lpPreviousCount = NULL;
            dword_507998 = NULL;
        }
    }
    else
    {
        ReleaseSemaphore(dword_507180, 1, NULL);
    }

    if (request->link.next)
    {
        request->link.prev->next = request->link.next;
        request->link.next->prev = request->link.prev;
        request->link.next = NULL;
        request->state = 1;
    }

    ReleaseSemaphore(dword_507184, 1, NULL);
    ReleaseSemaphore(hHandle, 1, NULL);

    if (cancelled)
    {
        sub_244B40(request->file, 0, 2, 1, client);
    }
}

// match: _sub_244F60 @ 0x00244F60
void
sub_244F60(rwaCacheClient *client)
{
    sub_244E70(client);
}

// match: _sub_244F70 @ 0x00244F70
void
sub_244F70(rwaCacheClient *client, void *dest, RwUInt32 size, rwaCacheCallBack callback,
           void *data)
{
    client->callback = callback;
    client->data = data;
    client->mode = 3;
    sub_244DC0(client, size, dest, callback, data);
}

// match: _sub_244FA0 @ 0x00244FA0
static void
sub_244FA0(RwInt32 status, rwaCacheClient *client, RwInt32 event, void *file, RwUInt32 bytes)
{
    if (status == 4)
    {
        client->mode = 0;
        client->header[0] = 0;
        client->header[1] = 0;
        client->header[2] = 0;
        client->callback(client->holder->file, 0, 4, event, client->data);
        return;
    }
    else
    {
        RwInt32     position;

        if (client->seeking)
        {
            client->seeking = FALSE;
            sub_244DC0(client, 0xC, client->header, (rwaCacheCallBack)sub_245060, client);

            return;
        }

        if (client->header[0] == client->unk4C)
        {
            client->mode = 0;
            client->callback(client->holder->file, 0xC, status, event, client->data);

            return;
        }

        client->seeking = TRUE;
        position = RwFtell(client->holder->file);
        if (position < 0)
        {
            client->header[0] = 0;
            client->header[1] = 0;
            client->header[2] = 0;
            client->callback(client->holder->file, 0, 4, event, client->data);
            return;
        }
        {
            RwFseek(client->holder->file, client->header[1] + position, 0);

            return;
        }
    }
}

// match: _sub_245060 @ 0x00245060
void
sub_245060(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event, rwaCacheClient *client)
{
    switch (client->mode)
    {
        case 1:
            sub_2449C0(file, client, bytes, status, event);
            break;

        case 2:
            sub_244FA0(status, client, event, file, bytes);
            break;

        case 3:
            client->callback(file, bytes, status, event, client->data);
            break;
    }
}

// match: _sub_2450C0 @ 0x002450C0
rwaCacheFile *
sub_2450C0(rwaCacheFile *holder, rwaCacheClient *client, RwInt32 type, RwUInt32 unk04,
           const RwChar *name, rwaCacheCallBack volatile callback, void *data)
{
    holder->type = type;
    holder->unk08 = 0;
    holder->unk04 = unk04;

    switch (type)
    {
        case 2:
        {
            rwaCacheCallBack notify;

            client->request.link.prev = NULL;
            client->request.link.next = NULL;
            client->request.state = 1;
            client->request.offset = 0;
            client->request.unk20 = 0;
            /* The image reads the callback argument here. Its original
             * qualification is unknown; use the normal local afterward. */
            notify = callback;
            client->mode = 1;
            client->callback = notify;
            client->request.callback = (rwaCacheCallBack)sub_245060;
            client->request.data = client;
            client->holder = holder;
            client->data = data;
            RtFSManagerFOpen(name, 0x11, sub_244B40, client);
            break;
        }
    }

    return holder;
}

// match: _sub_245130 @ 0x00245130
void
sub_245130(rwaCacheClient *client)
{
    sub_244F60(client);

    if (client->holder->type == 2)
    {
        RwFclose(client->holder->file);
    }
}

// match: _sub_245160 @ 0x00245160
void
sub_245160(rwaCacheFile *holder, rwaCacheClient *client, RwUInt32 unk4C, RwUInt32 *header,
           rwaCacheCallBack callback, void *data)
{
    client->holder = holder;
    client->unk4C = unk4C;
    client->header = header;
    client->seeking = FALSE;
    client->callback = callback;
    client->data = data;
    client->mode = 2;
    sub_244DC0(client, 0xC, header, (rwaCacheCallBack)sub_245060, client);
}

// match: _sub_2451B0 @ 0x002451B0
void
sub_2451B0(rwaCacheClient *client, void *dest, rwaCacheCallBack callback, void *data)
{
    client->callback = callback;
    client->data = data;
    client->mode = 3;
    sub_244DC0(client, 0xC, dest, (rwaCacheCallBack)sub_245060, client);
}

// match: _sub_2451F0 @ 0x002451F0
RwBool
sub_2451F0(void)
{
    return TRUE;
}

// match: _nullsub_6 @ 0x00245200
void
nullsub_6(void)
{
}

// match: _sub_245210 @ 0x00245210
const RwChar *
sub_245210(const RwChar *path)
{
    const RwChar   *start = path;

    if (*path)
    {
        while (*++path)
        {
        }
    }

    while (*path != '.')
    {
        path--;
        if (path == start)
        {
            return start;
        }
    }

    return path + 1;
}
