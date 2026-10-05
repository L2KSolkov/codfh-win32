/*
 * codfh-match: RenderWare Audio's waves and wave dictionaries (rwawave.c in
 * the library's PS2 header, docs/reference/rwacore_ps2.h, which gives the
 * public names): the wave state set-up, the dictionary file load's helpers,
 * the dictionary list and its open and close.
 */
#include <string.h>

#include "rwa.h"
#include "rwaint.h"


static RwUInt8 unk_506800[0x30];
static RwUInt32 dword_506834;
static RwUInt32 dword_506838;
static RwUInt32 dword_50683C;
static rwaWaveDict *dword_506840;
static rwaWaveDict *dword_506844;
static RwUInt8 unk_506848[0x10];
static RwUInt8 unk_516C80[0x28];
static rwaLink dword_516CA8;


extern RwUInt8 *sub_242180(RwUInt32 size, RwUInt32 hint);
extern void sub_2422A0(void *data);
extern RwUInt32 dword_42E484;
extern void *dword_506830;
extern const RwaUUID *dword_42E480;
extern rwaWaveDict *sub_23C770(rwaWaveDict *dict);
extern void sub_23C9A0(RwUInt32 size);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED248 @ 0x003ED248
// match: _unk_3ED258 @ 0x003ED258
// match: _unk_3ED268 @ 0x003ED268

// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED248
const RwaUUID unk_3ED248 = { 0x453A2D04, 0xE45F, 0x4BC8, { 0x81, 0xF0, 0xDF, 0x75, 0x8B, 0x01, 0xF2, 0x73 } };
// 0x003ED258
const RwaUUID unk_3ED258 = { 0xFD9D32D3, 0xE179, 0x426A, { 0x84, 0x24, 0x14, 0x72, 0x0A, 0xC7, 0xF6, 0x48 } };
// 0x003ED268
const RwaUUID unk_3ED268 = { 0x81271D58, 0xC9D7, 0x43A9, { 0x91, 0x17, 0x75, 0x87, 0x57, 0xC3, 0x1E, 0x04 } };
// 0x0042E480
const RwaUUID *dword_42E480 = &unk_3ED248;
// 0x0042E484
RwUInt32 dword_42E484 = 0x10000;
// 0x00506830
void *dword_506830;
// End of its data definitions.


// match: _dword_42E480 @ 0x0042E480


// match: _dword_42E484 @ 0x0042E484

// match: _sub_23BFE0 @ 0x0023BFE0

rwaVoiceState *
sub_23BFE0(rwaVoiceState *state)
{
    state->unk2C = 1;
    state->unk0C = 0;
    state->unk08 = 0;
    state->unk00 = 0;
    state->unk04 = 0;
    state->unk40 = 0;
    state->unk24 = 0;
    state->unk10 = 0;
    state->unk1C = 0;
    state->unk14 = 0;
    state->unk20 = 0;
    state->unk30 = 0;
    state->unk34 = 0;

    return state;
}

extern void sub_2421B0(rwaVoiceState *state);

// match: _sub_23C020 @ 0x0023C020
void
sub_23C020(rwaVoiceState *state)
{
    if (state->unk30 & 2)
    {
        sub_2421B0(state);
    }
}

extern void sub_242460(RwInt32 a, RwInt32 b, RwInt32 c, RwInt32 d, RwUInt32 flags, rwaVoiceState *state);

// match: _sub_23C040 @ 0x0023C040
void
sub_23C040(rwaVoiceState *state, const rwaVoiceParams *params)
{
    RwUInt32    flags;

    if (!params->unk00)
    {
        state->unk50 = 0;
    }

    flags = (params->unk04 & 1) ? params->unk04 : state->unk54;

    sub_242460(0, 0, 0, 0, flags & 2, state);
}

extern rwaVoiceState *sub_242170(RwInt32 size, RwUInt32 hint);

extern void sub_2409B0(RwaUUID *uuid);
extern void sub_241FD0(RwUInt8 **cursor, const void *src, RwInt32 size);
// match: _sub_23C080 @ 0x0023C080
void
sub_23C080(rwaWaveHeader *header)
{
    RwUInt8     buffer[sizeof(rwaWaveHeader)];
    RwUInt8    *cursor = buffer;

    sub_241FD0(&cursor, &header->unk00, 4);
    *cursor = header->unk04;
    *++cursor = header->unk05;
    *++cursor = header->unk06;
    *++cursor = header->unk07;
    cursor++;
    sub_241FD0(&cursor, &header->unk08, 4);
    sub_241FD0(&cursor, &header->unk0C, 4);
    sub_241FD0(&cursor, &header->unk10, 4);
    sub_241FD0(&cursor, &header->unk14, 4);
    sub_2409B0(&header->unk18);
    *(RwaUUID *)cursor = header->unk18;
    cursor += sizeof(RwaUUID);
    sub_241FD0(&cursor, &header->unk28, 4);

    memcpy(header, buffer, sizeof(rwaWaveHeader));
}

extern void sub_241FD0(RwUInt8 **cursor, const void *src, RwInt32 size);
extern void sub_2409B0(RwaUUID *uuid);

extern rwaStreamObj *sub_242810(rwaStreamObj *obj, RwUInt32 offset, void *buffer, RwUInt32 size);
extern const RwaUUID unk_3ED5FC;
extern const RwaUUID unk_3ED5EC;
extern const RwaUUID unk_3ED5BC;
// match: _sub_23C170 @ 0x0023C170
rwaStreamObj *
sub_23C170(rwaStreamObj *obj, const rwaReadParams *params)
{
    RwUInt32    offset;
    void       *buffer;
    void       *file;
    RwUInt32    remaining;

    offset = 0;
    file = params->file;
    buffer = params->buffer;
    remaining = obj->size;

    if (remaining)
    {
        do
        {
            RwUInt32    chunk;
            RwUInt32    size;

            if (!RwaUUIDCompare(obj->format, &unk_3ED5BC))
            {
                chunk = ((remaining + 0x7F) / 128) * 128;
            }
            else if (!RwaUUIDCompare(obj->format, &unk_3ED5EC))
            {
                chunk = ((remaining + 0x1FF) / 512) * 512;
            }
            else if (!RwaUUIDCompare(obj->format, &unk_3ED5FC))
            {
                chunk = ((obj->size + 0x8F) / 0x90) * 0x90 - obj->size + remaining;
            }
            else
            {
                chunk = remaining;
            }

            if (chunk > params->bufferSize)
            {
                chunk = params->bufferSize;
                remaining -= chunk;
                size = chunk;
            }
            else
            {
                size = remaining;
                remaining = 0;
            }

            RwFread(buffer, 1, chunk, file);

            obj = sub_242810(obj, offset, buffer, size);
            while (sub_242570(obj))
            {
            }

            offset += chunk;
        }
        while (remaining);
    }

    return obj;
}

// match: _sub_23C290 @ 0x0023C290
rwaObj *
sub_23C290(rwaObj *obj)
{
    return obj->objClass->unk20(obj) ? obj : NULL;
}

// match: _sub_23C2B0 @ 0x0023C2B0
rwaObj *
sub_23C2B0(rwaObj *obj)
{
    obj->objClass->unk24(obj);

    return obj;
}

extern void sub_242550(rwaObj *obj, RwInt32 a);

// match: _sub_23C2D0 @ 0x0023C2D0
rwaObj *
sub_23C2D0(rwaObj *obj, void *data)
{
    obj->objClass->unk2C(obj, data, 0);
    sub_242550(obj, 0);

    return obj;
}

extern void sub_23C840(rwaObj *obj, rwaObj *(*callback)(rwaObj *, void *), void *list);

// match: _sub_23C300 @ 0x0023C300
void
sub_23C300(rwaObj *obj)
{
    sub_23C840(obj, sub_23C2D0, obj->unk28);
    obj->unk28 = NULL;
}

extern void sub_240A30(void *data);
extern void sub_242590(rwaDictWave *wave);
extern RwUInt32 sub_242E20(RwUInt32 value);

#define rwaFixUp(_field, _base)                                         \
    if (_field)                                                         \
    {                                                                   \
        _field += (_base);                                              \
    }

// match: _sub_23C320 @ 0x0023C320
void
sub_23C320(rwaDict *dict, RwUInt32 base, RwBool swap)
{
    rwaDictNode    *node;
    rwaDictNode    *last;
    rwaDictNode    *cur;

    if (swap)
    {
        sub_240A30(dict);
        sub_240A30(&dict->unk0C);
    }

    rwaFixUp(dict->unk00, base);
    rwaFixUp(dict->unk04, base);
    rwaFixUp(dict->unk0C, base);
    rwaFixUp(dict->unk10, base);
    rwaFixUp(dict->unk14, base);

    last = (rwaDictNode *)dict->unk0C;
    node = (rwaDictNode *)dict->unk10;

    do
    {
        rwaDictWave    *wave;

        cur = node;

        if (swap)
        {
            sub_240A30(node);
        }

        rwaFixUp(node->unk08, base);
        rwaFixUp(node->unk04, base);
        rwaFixUp(node->unk00, base);

        node = (rwaDictNode *)node->unk04;
        wave = (rwaDictWave *)cur->unk08;

        if (swap)
        {
            sub_242590(wave);
        }

        rwaFixUp(wave->unk00, base);
        rwaFixUp(wave->unk04, base);
        rwaFixUp(wave->unk50, base);
        rwaFixUp(wave->unk20, base);
        rwaFixUp(wave->unk3C, base);

        wave->unk14 = sub_242E20(wave->unk14);
        wave->unk30 = sub_242E20(wave->unk30);
    }
    while (cur != last);
}

extern const RwaUUID unk_3ED5BC;
extern const RwaUUID unk_3ED5EC;
extern const RwaUUID unk_3ED5FC;
extern RwInt32 RwaUUIDCompare(const RwaUUID *a, const RwaUUID *b);
extern RwUInt32 RwFread(void *buffer, RwUInt32 size, RwUInt32 count, void *file);
extern rwaStreamObj *sub_242810(rwaStreamObj *obj, RwUInt32 offset, void *buffer, RwUInt32 size);
extern RwBool sub_242570(rwaStreamObj *obj);

// match: _sub_23C450 @ 0x0023C450
rwaVoiceState *
sub_23C450(rwaVoiceState *state)
{
    if (!state)
    {
        state = sub_242170(0x48, rwaMEMHINTDUR_EVENT | rwaID_808);
        state->unk30 = 2;
    }
    else
    {
        state->unk30 = 1;
    }

    sub_23BFE0(state);

    return state;
}

extern rwaWaveDict *sub_243670(void *freeList, RwUInt32 hint);
extern void sub_240B40(rwaWaveDict *dict);

// match: _sub_23C490 @ 0x0023C490
rwaVoiceState *
sub_23C490(void *file, RwUInt8 *buffer, RwUInt32 bufferSize, RwUInt32 flags,
           rwaVoiceState *state)
{
    rwaVoiceParams params;
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

    state->unk00 = (RwUInt32)(buffer + header->unk0C);
    dict = (rwaWaveDict *)state->unk00;

    {
        /* RwaWaveDict.waveListHead in rwacore_ps2.h is a three-word
         * RwaLLNode. The existing Xbox fields retain their offset names. */
        RwaLLNode saved;
        RwUInt32 unk00, unk04;
        saved.prev = (RwaLLNode *)dict->waves.next;
        saved.next = (RwaLLNode *)dict->waves.prev;
        saved.data = (void *)dict->unk14;
        unk00 = dict->unk00;
        unk04 = dict->unk04;
        sub_23C770(dict);
        dict->type = type;
        dict->waves.next = (rwaLink *)saved.prev;
        dict->waves.prev = (rwaLink *)saved.next;
        dict->unk14 = (RwUInt32)saved.data;
        dict->unk04 = unk04;
        dict->unk00 = unk00;
        dict->data = buffer;
    }
    sub_23C320((rwaDict *)dict, (RwUInt32)buffer, swapped);

    {
        params.unk00 = !RwaUUIDCompare(dword_42E480, &header->unk18);
        params.unk04 = flags;
        sub_23C840((rwaObj *)dict, (rwaObj *(*)(rwaObj *, void *))sub_23C040, &params);
    }
    state->unk2C = 0x10;
    sub_23C840((rwaObj *)dict, (rwaObj *(*)(rwaObj *, void *))sub_23C290, NULL);

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

rwaObj * RwaWaveDictFindWaveByIndex(rwaWaveDict *dict, RwInt32 index);
// match: _sub_23C700 @ 0x0023C700
void
sub_23C700(rwaWaveDict *dict)
{
    rwaDictRelease  release;
    rwaObj         *obj;

    if (dict->flags & 1)
    {
        sub_23C840((rwaObj *)dict, (rwaObj *(*)(rwaObj *, void *))sub_23C2B0, NULL);

        return;
    }

    obj = RwaWaveDictFindWaveByIndex(dict, 0);
    release.unk4C = dict->unk28;
    release.unk34 = dict->unk2C;
    release.unk29 = 0;
    release.unk50 = 0;
    sub_23C300((rwaObj *)dict);
    ((void (*)(rwaDictRelease *))obj->objClass->unk24)(&release);

    dict->unk28 = 0;
    dict->unk2C = 0;
}

extern rwaObj *RwaWaveDictFindWaveByIndex(rwaWaveDict *dict, RwInt32 index);

// match: _sub_23C770 @ 0x0023C770
rwaWaveDict *
sub_23C770(rwaWaveDict *dict)
{
    if (dict)
    {
        dict->type = 4;
    }
    else
    {
        dict = sub_243670(unk_516C80, rwaMEMHINTDUR_EVENT | rwaID_808);
        if (!dict)
        {
            return NULL;
        }

        dict->type = 1;
    }

    sub_240B40(dict);

    dict->link.next = NULL;
    dict->link.prev = NULL;
    dict->link.next = dword_516CA8.next;
    dict->link.prev = &dword_516CA8;
    dword_516CA8.next->prev = &dict->link;
    dword_516CA8.next = &dict->link;

    dict->waves.prev = &dict->waves;
    dict->waves.next = &dict->waves;
    dict->unk14 = 0;
    dict->data = NULL;
    dict->unk28 = 0;
    dict->unk2C = 0;
    dict->flags = 0;

    return dict;
}


#define rwaDictFromLink(_link) ((rwaWaveDict *)((RwUInt8 *)(_link) - 0x1C))

// match: _RwaWaveDictFindByIndex @ 0x0023C7F0
rwaWaveDict *
RwaWaveDictFindByIndex(RwInt32 index)
{
    rwaLink    *cur;
    RwInt32     i = 0;

    for (cur = dword_516CA8.next; cur != &dword_516CA8; cur = cur->next)
    {
        rwaWaveDict    *dict = rwaDictFromLink(cur);

        if (i == index)
        {
            return dict;
        }

        i++;
    }

    return NULL;
}

// match: _RwaWaveDictGetCount @ 0x0023C820
RwInt32
RwaWaveDictGetCount(void)
{
    rwaLink    *cur;
    RwInt32     count = 0;

    for (cur = dword_516CA8.next; cur != &dword_516CA8; cur = cur->next)
    {
        count++;
    }

    return count;
}

// match: _sub_23C840 @ 0x0023C840
void
sub_23C840(rwaObj *obj, rwaObj *(*callback)(rwaObj *, void *), void *data)
{
    rwaWaveDict    *dict = (rwaWaveDict *)obj;
    rwaWaveNode    *node = (rwaWaveNode *)dict->waves.prev;

    if (node != (rwaWaveNode *)&dict->waves)
    {
        do
        {
            void   *item = node->item;

            node = node->next;
            if (!callback((rwaObj *)item, data))
            {
                break;
            }
        }
        while (node != (rwaWaveNode *)&dict->waves);
    }
}

extern RwInt32 sub_243540(rwaLink *list, void *item);

// match: _RwaWaveDictContainsWave @ 0x0023C880
rwaWaveDict *
RwaWaveDictContainsWave(rwaWaveDict *dict, void *item)
{
    return (sub_243540(&dict->waves, item) != -1) ? dict : NULL;
}

// match: _RwaWaveDictUsingAllWaveDef @ 0x0023C8A0
RwUInt32
RwaWaveDictUsingAllWaveDef(RwUInt32 id)
{
    rwaLink    *cur;

    for (cur = dword_516CA8.next; cur != &dword_516CA8; cur = cur->next)
    {
        rwaWaveDict    *dict = rwaDictFromLink(cur);
        rwaWaveNode    *node;

        for (node = (rwaWaveNode *)dict->waves.prev;
             node != (rwaWaveNode *)&dict->waves;
             node = node->next)
        {
            rwaWaveItem    *item = (rwaWaveItem *)node->item;

            if (item->id == id)
            {
                return id;
            }
        }
    }

    return 0;
}

extern rwaObj *sub_243570(rwaLink *list, RwInt32 index);

// match: _RwaWaveDictFindWaveByIndex @ 0x0023C8E0
rwaObj *
RwaWaveDictFindWaveByIndex(rwaWaveDict *dict, RwInt32 index)
{
    return sub_243570(&dict->waves, index);
}

extern RwBool sub_2434E0(rwaLink *list, void *item);

// match: _RwaWaveDictAddWave @ 0x0023C8F0
rwaWaveDict *
RwaWaveDictAddWave(rwaWaveDict *dict, void *item)
{
    if (RwaWaveDictContainsWave(dict, item))
    {
        return dict;
    }

    return sub_2434E0(&dict->waves, item) ? dict : NULL;
}


// match: _RwaWaveDictGetWorking @ 0x0023C930
rwaWaveDict *
RwaWaveDictGetWorking(void)
{
    return dword_506844;
}

extern void sub_243640(rwaLink *list, void *data);

// match: _RwaWaveDictRemoveAllWave @ 0x0023C940
void
RwaWaveDictRemoveAllWave(void *data)
{
    rwaLink    *cur;

    for (cur = dword_516CA8.next; cur != &dword_516CA8; cur = cur->next)
    {
        sub_243640(&rwaDictFromLink(cur)->waves, data);
    }
}

extern void sub_240C30(rwaWaveDict *dict);
extern void sub_2437A0(void *freeList, rwaWaveDict *dict);

// match: _sub_23C970 @ 0x0023C970
static void
sub_23C970(rwaWaveDict *dict)
{
    sub_240C30(dict);

    if (dict->type & 1)
    {
        sub_2437A0(unk_516C80, dict);
    }
    else if (!(dict->type & 4))
    {
        sub_2421B0((rwaVoiceState *)dict);
    }
}

// match: _sub_23C9A0 @ 0x0023C9A0
void
sub_23C9A0(RwUInt32 size)
{
    void   *buffer = sub_242180(size, rwaMEMHINTDUR_EVENT | rwaID_808);

    if (buffer)
    {
        dword_42E484 = size;
        dword_506830 = buffer;
    }
    else
    {
        dword_506830 = NULL;
        dword_42E484 = 0;
    }
}

// match: _sub_23C9E0 @ 0x0023C9E0
void
sub_23C9E0(void)
{
    sub_2422A0(dword_506830);
    dword_506830 = NULL;
    dword_42E484 = 0;
}

extern RwBool sub_243950(RwInt32 size, RwInt32 a, RwInt32 b, RwInt32 c, void *freeList, RwUInt32 hint);
extern void sub_2438E0(void *freeList);
extern void RwaWaveDictAssignID(rwaWaveDict *dict, const void *id, void *name);

// match: _sub_23CA00 @ 0x0023CA00
RwBool
sub_23CA00(void)
{
    dword_516CA8.next = &dword_516CA8;
    dword_516CA8.prev = &dword_516CA8;
    dword_506838 = 1;

    if (sub_243950(0x30, 8, 8, 0, unk_516C80, rwaMEMHINTDUR_GLOBAL | rwaID_808))
    {
        rwaWaveDict    *dict = sub_23C770((rwaWaveDict *)unk_506800);

        dword_506844 = dict;
        dword_506840 = dict;

        if (dict)
        {
            RwaWaveDictAssignID(dict, &unk_3ED268, unk_506848);

            return TRUE;
        }

        sub_2438E0(unk_516C80);
    }

    dword_506840 = NULL;
    dword_506844 = NULL;
    dword_506838 = 0;

    return FALSE;
}


extern void sub_242510(void *item);
extern void sub_2435D0(rwaLink *list);

// match: _RwaWaveDictDestroy @ 0x0023CAA0
void
RwaWaveDictDestroy(rwaWaveDict *dict)
{
    dict->link.prev->next = dict->link.next;
    dict->link.next->prev = dict->link.prev;

    if (dict == dword_506844)
    {
        dword_506844 = dword_506840;
    }

    if ((dict->type & 0x40) && (dict->unk28 || (dict->flags & 1)))
    {
        sub_23C700(dict);
    }

    if (dict->type & 0x20)
    {
        return;
    }

    if (dict->type & 0x10)
    {
        sub_2422A0(dict->data);

        return;
    }

    {
        rwaWaveNode    *node;

        for (node = (rwaWaveNode *)dict->waves.prev;
             node != (rwaWaveNode *)&dict->waves;
             node = node->next)
        {
            void       *item = node->item;
            rwaLink    *cur = dword_516CA8.next;

            /* The library releases an unused wave twice when there are
             * no dictionaries. */
            if (cur == &dword_516CA8)
            {
                sub_242510(item);
            }

            {
                RwBool  found = FALSE;

                for (; cur != &dword_516CA8; cur = cur->next)
                {
                    if (RwaWaveDictContainsWave(rwaDictFromLink(cur), item))
                    {
                        found = TRUE;
                        break;
                    }
                }

                if (!found)
                {
                    sub_242510(item);
                }
            }
        }
    }

    sub_2435D0(&dict->waves);
    sub_23C970(dict);
}


// match: _sub_23CB80 @ 0x0023CB80
void
sub_23CB80(void)
{
    dword_50683C = 1;

    while (dword_516CA8.next != &dword_516CA8)
    {
        RwaWaveDictDestroy(rwaDictFromLink(dword_516CA8.next));
    }

    sub_2438E0(unk_516C80);
    dword_516CA8.next = &dword_516CA8;
    dword_516CA8.prev = &dword_516CA8;

    if (dword_506830 && dword_506834 == 1)
    {
        sub_23C9E0();
        dword_506834 = 0;
    }

    dword_506840 = NULL;
    dword_506844 = NULL;
    dword_506838 = 0;
    dword_50683C = 0;
}
