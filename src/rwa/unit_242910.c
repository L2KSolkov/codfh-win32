/*
 * codfh-match: RenderWare Audio's wave definitions (0x242910-0x243460; VC7.0): their pool,
 * format matching and conversion sizes, the codec table and definition creation, destruction
 * and lookup by UUID. Split from unit_2422B0.c, the waves, at an original object boundary: in
 * one unit VC7.0 defers the wave functions that call sub_2429D0, defined later, to the end
 * (docs/units.md; PLAN M7).
 */

#include "rwa.h"
#include "rwaint.h"

extern RwaUniqueID *sub_240BF0(RwaUniqueID *uniqueID, const RwChar *name);
extern RwaUniqueID *sub_240C10(RwaUniqueID *uniqueID, const RwaUUID *uuid);
extern RwBool RwaWaveDictUsingAllWaveDef(RwaWaveDef *waveDef, RwBool a);
#define rwaWaveDefFromLink(_link) ((RwaWaveDef *)((RwUInt8 *)(_link) - 0x50))
extern const RwaUUID *unk_42F7A0[9];    /* the codecs */
extern void sub_23D970(void *a, void *b,
                       RwBool (*callback)(rwaObjDef *parent, rwaObjDef *objDef, void *data),
                       void *data, RwBool recurse);

static RwUInt8 unk_507004[0x24];    /* wave definitions */
static RwUInt32 dword_507028;
// match: _sub_242910 @ 0x00242910
// match: __real@40e38e39 @ 0x003ED66C
RwBool
sub_242910(void)
{
    dword_507028 = 1;

    if (sub_243950(sizeof(RwaWaveDef), 8, 8, 0, unk_507004, rwaMEMHINTDUR_GLOBAL | rwaID_805))
    {
        return TRUE;
    }

    dword_507028 = 0;

    return FALSE;
}
// match: _sub_242950 @ 0x00242950
const RwaUUID *
sub_242950(const RwaUUID *uuid, RwBool (*callback)(RwaWave *wave, void *data), void *data)
{
    RwUInt32    count = RwaWaveDictGetCount();
    RwUInt32    i;

    for (i = 0; i < count; i++)
    {
        rwaWaveDict    *dict = RwaWaveDictFindByIndex(i);
        rwaWaveNode    *node;

        for (node = (rwaWaveNode *)dict->waves.prev;
             node != (rwaWaveNode *)&dict->waves;
             )
        {
            RwaWave    *wave = (RwaWave *)node->item;

            node = node->next;
            if (!RwaUUIDCompare(wave->waveDef->uniqueID.uuid, uuid) && !callback(wave, data))
            {
                break;
            }
        }
    }

    return uuid;
}
// match: _sub_2429D0 @ 0x002429D0
RwBool
sub_2429D0(const RwaWaveFormat *format1, const RwaWaveFormat *format2)
{
    if (!RwaUUIDCompare(format1->dataType, format2->dataType) &&
        format1->sampleRate == format2->sampleRate &&
        format1->bitDepth == format2->bitDepth &&
        format1->noChannels == format2->noChannels &&
        !((format1->flags ^ format2->flags) & ~2))
    {
        return TRUE;
    }

    return FALSE;
}
extern const RwaUUID unk_3ED61C;
extern const RwaUUID unk_3ED65C;
extern const RwaUUID unk_3ED5FC;
extern const RwaUUID unk_3ED5EC;
extern const RwaUUID unk_3ED5DC;
extern const RwaUUID unk_3ED5BC;
extern const RwaUUID unk_3ED5CC;
// match: _sub_242A30 @ 0x00242A30
RwUInt32
sub_242A30(const RwaWaveFormat *format)
{
    if (!RwaUUIDCompare(format->dataType, &unk_3ED5CC))
    {
        return format->bitDepth >> 3;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED5BC))
    {
        return 16;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED5DC))
    {
        return 4;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED5EC))
    {
        return 8;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED5FC) ||
        !RwaUUIDCompare(format->dataType, &unk_3ED65C))
    {
        return format->noChannels == 1 ? 0x24 : 4;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED61C))
    {
        RwUInt32    rate = format->extra ? *(RwUInt32 *)format->extra : 128000;
        RwUInt32    sampleRate = format->sampleRate ? format->sampleRate : 48000;

        return rate * 144 / sampleRate;
    }

    return 0;
}
// match: _sub_242B30 @ 0x00242B30
void
sub_242B30(RwaWaveFormat *format)
{
    if (!(format->flags & 2) && format->extra)
    {
        sub_2421B0(format->extra);
    }

    format->extra = NULL;
    format->extraSize = 0;
}
// match: _RwaWaveDefAssignID @ 0x00242B60
RwaWaveDef *
RwaWaveDefAssignID(RwaWaveDef *waveDef, const RwaUUID *uuid, const RwChar *name)
{
    if (!sub_240C10(&waveDef->uniqueID, uuid))
    {
        return NULL;
    }

    return sub_240BF0(&waveDef->uniqueID, name) ? waveDef : NULL;
}
// match: _sub_242B90 @ 0x00242B90
RwBool
sub_242B90(RwaWaveDef *waveDef)
{
    if (RwaWaveDictUsingAllWaveDef(waveDef, TRUE))
    {
        return FALSE;
    }

    if (waveDef->unregister)
    {
        waveDef->unregister(waveDef);
    }

    if (waveDef->instances)
    {
        sub_2438E0(waveDef->instances);
    }

    if (waveDef->flags & 1)
    {
        sub_2421B0(waveDef->formats);
    }

    waveDef->link.prev->next = waveDef->link.next;
    waveDef->link.next->prev = waveDef->link.prev;
    sub_240C30(&waveDef->uniqueID);

    if (waveDef->flags & 2)
    {
        sub_2437A0(unk_507004, waveDef);
    }

    return TRUE;
}
// match: _sub_242C10 @ 0x00242C10
RwBool
sub_242C10(rwaObjDef *parent, rwaObjDef *objDef, rwaWaveDefFind *find)
{
    rwaLink    *cur;

    for (cur = objDef->waveDefs.next; cur != &objDef->waveDefs; cur = cur->next)
    {
        RwaWaveDef *waveDef = rwaWaveDefFromLink(cur);

        if (!RwaUUIDCompare(waveDef->uniqueID.uuid, find->uuid))
        {
            find->found = waveDef;

            return TRUE;
        }
    }

    return FALSE;
}
// match: _sub_242C60 @ 0x00242C60
void
sub_242C60(const rwaWaveFormatDesc *desc, RwaWaveFormat *format, RwBool init)
{
    if (init)
    {
        rwaWaveFormatInit(format);
    }

    format->bitDepth = desc->bitDepth;
    format->dataType = desc->dataType;
    format->noChannels = desc->noChannels;
    format->flags = 0;

    if (desc->flags & 1)
    {
        format->flags = 1;
    }

    if (desc->flags & 4)
    {
        format->flags |= 4;
    }
}
// match: _sub_242CC0 @ 0x00242CC0
RwBool
sub_242CC0(const rwaWaveFormatDesc *desc, const RwaWaveFormat *format)
{
    if (format->noChannels == desc->noChannels &&
        format->bitDepth == desc->bitDepth &&
        format->sampleRate >= desc->minRate &&
        format->sampleRate <= desc->maxRate &&
        !RwaUUIDCompare(format->dataType, desc->dataType) &&
        !((desc->flags ^ format->flags) & 1))
    {
        return TRUE;
    }

    return FALSE;
}
// match: _sub_242D20 @ 0x00242D20
void
sub_242D20(RwaWaveDef *waveDef, rwaWaveFormatDesc **formats, RwUInt32 noFormats)
{
    if (waveDef->flags & 1)
    {
        if (waveDef->formats)
        {
            sub_2421B0(waveDef->formats);
        }

        waveDef->flags &= ~1;
    }

    waveDef->formats = formats;
    waveDef->noFormats = noFormats;
    waveDef->format = 0;
}
// match: _sub_242D60 @ 0x00242D60
RwUInt32
sub_242D60(const RwaWaveFormat *format)
{
    RwUInt32    size = 0x1C;

    if (format->dataType)
    {
        size = 0x2C;
    }

    if (format->extra)
    {
        size += format->extraSize;
    }

    return size;
}
// match: _sub_242D80 @ 0x00242D80
RwBool
sub_242D80(RwaWaveDef *waveDef, const RwaWaveFormat *format)
{
    RwUInt32    noFormats = waveDef->noFormats;
    RwBool      found = FALSE;

    if (noFormats)
    {
        rwaWaveFormatDesc **formats = waveDef->formats;
        RwUInt32            i;

        for (i = 0; i < noFormats; i++)
        {
            if (sub_242CC0(formats[i], format))
            {
                found = TRUE;
                break;
            }
        }
    }
    else
    {
        found = TRUE;
    }

    return found;
}
extern const RwaUUID *unk_42F7A0[9];
// match: _sub_242DE0 @ 0x00242DE0
const RwaUUID *
sub_242DE0(const RwaUUID *uuid)
{
    RwUInt32    i;

    for (i = 0; i < 9; i++)
    {
        if (!RwaUUIDCompare(unk_42F7A0[i], uuid))
        {
            return unk_42F7A0[i];
        }
    }

    return NULL;
}
// match: _sub_242E20 @ 0x00242E20
const RwaUUID *
sub_242E20(RwUInt32 index)
{
    return unk_42F7A0[index];
}
extern const RwaUUID unk_3ED63C;
extern const RwaUUID unk_3ED62C;
extern const RwaUUID unk_3ED64C;
// match: _sub_242E30 @ 0x00242E30
RwUInt32
sub_242E30(const RwaWaveFormat *format)
{
    if (!RwaUUIDCompare(format->dataType, &unk_3ED5CC))
    {
        return 1;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED5BC))
    {
        return 0x1C;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED5DC))
    {
        return 1;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED64C))
    {
        return 0x600;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED5EC))
    {
        return 0xE;
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED5FC) ||
        !RwaUUIDCompare(format->dataType, &unk_3ED65C))
    {
        RwaWaveFormat   mono;

        if (format->noChannels == 1)
        {
            return 0x40;
        }

        mono = *format;
        mono.noChannels = 1;

        return sub_242E30(&mono) / (sub_242A30(&mono) / sub_242A30(format));
    }

    if (!RwaUUIDCompare(format->dataType, &unk_3ED61C) ||
        !RwaUUIDCompare(format->dataType, &unk_3ED62C))
    {
        return 0x480;
    }

    return RwaUUIDCompare(format->dataType, &unk_3ED63C) ? 0x180 : 0;
}
// match: _sub_242FA0 @ 0x00242FA0
void
sub_242FA0(RwaWaveFormat *format)
{
    RwUInt8        *cursor;
    RwaWaveFormat   swapped;

    cursor = (RwUInt8 *)&swapped;
    sub_241FD0(&cursor, &format->sampleRate, sizeof(format->sampleRate));
    sub_241FD0(&cursor, &format->dataType, sizeof(format->dataType));
    sub_241FD0(&cursor, &format->length, sizeof(format->length));
    *cursor++ = format->bitDepth;
    *cursor++ = format->noChannels;
    *cursor++ = format->unk0E;
    *cursor++ = format->unk0F;
    sub_241FD0(&cursor, &format->extra, sizeof(format->extra));
    sub_241FD0(&cursor, &format->extraSize, sizeof(format->extraSize));
    *cursor = format->flags;

    *format = swapped;
    format->unk19 = 0;
}
// match: _sub_243060 @ 0x00243060
RwBool
sub_243060(rwaObjDef *parent, rwaObjDef *objDef)
{
    rwaLink    *cur = objDef->waveDefs.next;

    while (cur != &objDef->waveDefs)
    {
        rwaLink    *next = cur->next;

        sub_242B90(rwaWaveDefFromLink(cur));
        cur = next;
    }

    return FALSE;
}
extern rwaObjDef *dword_516C60;
// match: _sub_243090 @ 0x00243090
RwaWaveDef *
sub_243090(rwaObjDef *objDef, RwaWaveDef *waveDef)
{
    if (!waveDef)
    {
        waveDef = (RwaWaveDef *)sub_243670(unk_507004, rwaMEMHINTDUR_EVENT | rwaID_805);
        if (!waveDef)
        {
            return NULL;
        }

        waveDef->flags = 2;
    }
    else
    {
        waveDef->flags = 0;
    }

    sub_240B40(&waveDef->uniqueID);
    waveDef->create = NULL;
    waveDef->destroy = NULL;
    waveDef->unk14 = NULL;
    waveDef->busy = NULL;
    waveDef->unk20 = NULL;
    waveDef->unk24 = NULL;
    waveDef->unk18 = NULL;
    waveDef->unregister = NULL;
    waveDef->dataSize = 0;
    waveDef->unk48 = 8;
    waveDef->instances = NULL;
    sub_242D20(waveDef, NULL, 0);

    waveDef->link.prev = NULL;
    waveDef->link.next = NULL;

    if (!objDef)
    {
        objDef = dword_516C60;
    }

    waveDef->objDef = objDef;
    waveDef->link.next = objDef->waveDefs.next;
    waveDef->link.prev = &objDef->waveDefs;
    objDef->waveDefs.next->prev = &waveDef->link;
    objDef->waveDefs.next = &waveDef->link;

    return waveDef;
}
// match: _sub_243130 @ 0x00243130
RwaWaveDef *
sub_243130(const RwaUUID *uuid)
{
    rwaWaveDefFind  find;

    find.uuid = uuid;
    find.found = NULL;
    sub_23D970(NULL, NULL, (RwBool (*)(rwaObjDef *, rwaObjDef *, void *))sub_242C10, &find,
               TRUE);

    return find.found;
}
// match: _sub_243160 @ 0x00243160
RwaWaveFormat *
sub_243160(RwaWaveFormat *format, RwUInt8 *buffer, RwBool write, RwBool swap)
{
    if (write)
    {
        RwUInt8    *cursor = buffer;

        if (swap)
        {
            RwUInt32    hasType = format->dataType != NULL;

            sub_241FD0(&cursor, &format->sampleRate, 4);
            sub_241FD0(&cursor, &hasType, 4);
            sub_241FD0(&cursor, &format->length, 4);
            sub_241FD0(&cursor, &format->bitDepth, 1);
            sub_241FD0(&cursor, &format->noChannels, 1);
            *(RwUInt16 *)cursor = 0;
            cursor += 2;
            sub_241FD0(&cursor, &format->extra, 4);
            sub_241FD0(&cursor, &format->extraSize, 4);
            sub_241FD0(&cursor, &format->flags, 1);
            sub_241FD0(&cursor, &format->unk19, 1);
            *(RwUInt16 *)cursor = 0;
            cursor += 2;
        }
        else
        {
            *(RwaWaveFormat *)cursor = *format;
            cursor += sizeof(RwaWaveFormat);
        }

        if (format->dataType)
        {
            sub_240B50(format->dataType, (RwaUUID *)cursor, swap);
            cursor += sizeof(RwaUUID);
        }

        if (format->extra)
        {
            memcpy(cursor, format->extra, format->extraSize);
        }

        return format;
    }
    else
    {
        RwUInt8    *src;

        if (swap)
        {
            RwUInt8    *cursor = (RwUInt8 *)format;

            src = buffer;
            sub_241FD0(&cursor, src, 4);
            src += 4;
            sub_241FD0(&cursor, src, 4);
            src += 4;
            sub_241FD0(&cursor, src, 4);
            src += 4;
            sub_241FD0(&cursor, src, 1);
            src++;
            sub_241FD0(&cursor, src, 1);
            *(RwUInt16 *)cursor = 0;
            src += 3;
            cursor += 2;
            sub_241FD0(&cursor, src, 4);
            src += 4;
            sub_241FD0(&cursor, src, 4);
            src += 4;
            sub_241FD0(&cursor, src, 1);
            src++;
            sub_241FD0(&cursor, src, 1);
            *(RwUInt16 *)cursor = 0;
            src += 3;
        }
        else
        {
            *format = *(RwaWaveFormat *)buffer;
            src = buffer + sizeof(RwaWaveFormat);
        }

        if (format->dataType)
        {
            sub_240B50((RwaUUID *)src, (RwaUUID *)src, swap);
            format->dataType = sub_242DE0((RwaUUID *)src);
            if (!format->dataType)
            {
                return NULL;
            }

            src += sizeof(RwaUUID);
        }

        if (format->extra)
        {
            format->extra = src;
        }

        return format;
    }
}
// match: _sub_2433C0 @ 0x002433C0
RwUInt32
sub_2433C0(const RwaWaveFormat *format, RwUInt32 size)
{
    RwUInt32    align = sub_242E30(format);
    RwUInt32    bytes = sub_242A30(format);
    RwUInt32    samples;

    if ((!RwaUUIDCompare(format->dataType, &unk_3ED5FC) ||
         !RwaUUIDCompare(format->dataType, &unk_3ED65C)) &&
        format->noChannels == 2)
    {
        samples = (RwUInt32)((RwReal)size / (RwReal)bytes * (64.0f / 9.0f));
    }
    else
    {
        samples = size / bytes * align;
    }

    return samples / ((format->flags & 4) ? 1 : format->noChannels);
}
// match: __rwaWaveDefCloseModule @ 0x00243460
void
_rwaWaveDefCloseModule(void)
{
    sub_23D970(NULL, NULL, (RwBool (*)(rwaObjDef *, rwaObjDef *, void *))sub_243060, NULL,
               TRUE);
    sub_2438E0(unk_507004);
    dword_507028 = 0;
}
