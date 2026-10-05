// match: _sub_2449C0 @ 0x002449C0
static void
sub_2449C0(rwaCacheClient *client, void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event)
{
    client->holder->file = file;
    client->callback(file, bytes, status, event, client->data);
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

                    ReleaseSemaphore(hHandle, 1, NULL);

                    return;
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

// match: _sub_244FA0 @ 0x00244FA0
static void
sub_244FA0(rwaCacheClient *client, RwInt32 status, RwInt32 event, void *file, RwUInt32 bytes)
{
    if (status == 4)
    {
        client->mode = 0;
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
        if (position >= 0)
        {
            RwFseek(client->holder->file, client->header[1] + position, 0);

            return;
        }
    }

    client->header[0] = 0;
    client->header[1] = 0;
    client->header[2] = 0;
    client->callback(client->holder->file, 0, 4, event, client->data);
}

// match: _sub_245060 @ 0x00245060
void
sub_245060(void *file, RwUInt32 bytes, RwInt32 status, RwInt32 event, rwaCacheClient *client)
{
    switch (client->mode)
    {
        case 1:
            sub_2449C0(client, file, bytes, status, event);
            break;

        case 2:
            sub_244FA0(client, status, event, file, bytes);
            break;

        case 3:
            client->callback(file, bytes, status, event, client->data);
            break;
    }
}

// match: _sub_2450C0 @ 0x002450C0
rwaCacheFile *
sub_2450C0(rwaCacheFile *holder, rwaCacheClient *client, RwInt32 type, RwUInt32 unk04,
           const RwChar *name, rwaCacheCallBack callback, void *data)
{
    holder->type = type;
    holder->unk08 = 0;
    holder->unk04 = unk04;

    switch (type)
    {
        case 2:
            client->request.link.prev = NULL;
            client->request.link.next = NULL;
            client->request.offset = 0;
            client->request.unk20 = 0;
            client->request.state = 1;
            client->mode = 1;
            client->callback = callback;
            client->request.callback = (rwaCacheCallBack)sub_245060;
            client->request.data = client;
            client->holder = holder;
            client->data = data;
            _RtFSManagerFOpen(name, 0x11, sub_244B40, client);
            break;
    }

    return holder;
}

