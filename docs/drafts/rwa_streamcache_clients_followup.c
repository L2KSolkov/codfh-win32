// match: _sub_2449C0 @ 0x002449C0
static void
sub_2449C0(void *file, rwaCacheClient *client, RwUInt32 bytes, RwInt32 status, RwInt32 event)
{
    client->holder->file = file;
    client->callback(file, bytes, status, event, client->data);
}

// match: _sub_244FA0 @ 0x00244FA0
static void
sub_244FA0(RwInt32 status, rwaCacheClient *client, RwInt32 event, void *file, RwUInt32 bytes)
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

