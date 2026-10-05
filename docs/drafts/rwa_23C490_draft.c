// match: _sub_23C490 @ 0x0023C490
rwaVoiceState *
sub_23C490(void *file, RwUInt8 *buffer, RwUInt32 bufferSize, RwUInt32 flags,
           rwaVoiceState *state)
{
    RwBool          swapped = FALSE;
    RwUInt8         type;
    rwaWaveHeader  *header;
    rwaWaveDict    *dict;

    if (!state)
    {
        state = sub_23C450(NULL);
    }

    if (!buffer)
    {
        buffer = sub_242180(0x800, rwaMEMHINTDUR_EVENT | rwaID_808);
        bufferSize = 0x800;
        type = 0x10;
    }
    else
    {
        if (bufferSize < 0x800)
        {
            state->unk2C = 0x2000;

            return state;
        }

        type = 0x20;
    }

    RwFread(buffer, 1, 0x800, file);

    header = (rwaWaveHeader *)buffer;
    if (header->unk04)
    {
        sub_23C080(header);
        swapped = TRUE;
    }

    if (header->unk00 != 0x809)
    {
        state->unk2C = 0x4000;

        return state;
    }

    if (header->unk08 > bufferSize)
    {
        if (type & 0x20)
        {
            state->unk2C = 0x2000;

            return state;
        }

        {
            RwUInt8    *newBuffer = sub_242180(header->unk08, rwaMEMHINTDUR_EVENT | rwaID_808);

            memcpy(newBuffer, buffer, bufferSize);
            sub_2422A0(buffer);
            buffer = newBuffer;
            header = (rwaWaveHeader *)newBuffer;
        }
    }

    if (header->unk08 > 0x800)
    {
        RwFread(buffer + 0x800, 1, header->unk08 - 0x800, file);
    }

    state->unk08 = header->unk08;
    state->unk0C = header->unk14;
    state->unk28 = header->unk14;
    state->unk38 = 0;
    state->unk3C = 0;

    dict = (rwaWaveDict *)(buffer + header->unk0C);
    state->unk00 = (RwUInt32)dict;

    {
        rwaLink    *next, *prev;
        RwUInt32    unk14;
        RwUInt32    unk00, unk04;

        unk04 = dict->unk04;
        unk00 = dict->unk00;
        prev = dict->waves.prev;
        unk14 = dict->unk14;
        next = dict->waves.next;

        sub_23C770(dict);

        dict->type = type;
        dict->unk14 = unk14;
        dict->waves.prev = prev;
        dict->waves.next = next;
        dict->unk04 = unk04;
        dict->unk00 = unk00;
        dict->data = buffer;
    }

    sub_23C320((rwaDict *)dict, (RwUInt32)buffer, swapped);

    {
        rwaVoiceParams  params;

        params.unk00 = !RwaUUIDCompare(dword_42E480, &header->unk18);
        params.unk04 = flags;
        sub_23C840((rwaObj *)dict, (rwaObj *(*)(rwaObj *, void *))sub_23C040, &params);
    }
    sub_23C840((rwaObj *)dict, (rwaObj *(*)(rwaObj *, void *))sub_23C290, NULL);
    state->unk2C = 0x10;

    dict->flags |= 1;
    dict->type |= 0x40;

    if (!dword_506830)
    {
        sub_23C9A0(0x10000);
        dword_506834 = 1;
    }

    {
        rwaReadParams   read;

        read.file = file;
        read.buffer = dword_506830;
        read.bufferSize = dword_42E484;
        sub_23C840((rwaObj *)dict, (rwaObj *(*)(rwaObj *, void *))sub_23C170, &read);
    }
    state->unk2C = 0x100;

    return state;
}
