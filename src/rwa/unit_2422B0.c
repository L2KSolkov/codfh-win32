/*
 * codfh-match: RenderWare Audio's waves and wave definitions (0x2422B0-
 * 0x243160; the PS2 header's rwawave.h): the wave free list (0x506FD4) and
 * definition free list (0x507004), wave creation, set-up for a definition,
 * destruction, the upload with format conversion and byte swapping, and
 * the definitions' formats, codecs, creation and destruction.
 */
#include "rwa.h"
#include "rwaint.h"



static RwUInt8 unk_506FD4[0x24];    /* waves */
static RwUInt32 dword_506FF8;
extern RwaWave *dword_506FFC; /* upload wave, stores at 2428CE */
extern RwUInt32 dword_507000; /* upload offset, store at 2428D4 */

extern const RwaUUID unk_3EDF4C;    /* the default wave definition */
extern rwaObjDef *dword_516C60;

extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void *sub_242180(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void sub_2422A0(void *mem);
extern void *sub_243670(void *freeList, RwUInt32 hint);
extern void sub_2437A0(void *freeList, void *item);
extern void sub_2438E0(void *freeList);
extern void *sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a,
                        void *freeList, RwUInt32 hint);
extern RwaUniqueID *sub_240B40(RwaUniqueID *uniqueID);
extern RwaUniqueID *sub_240C30(RwaUniqueID *uniqueID);
extern const RwaUUID *sub_240B50(const RwaUUID *uuid, RwaUUID *copy, RwBool swap);
extern void sub_240A30(RwaV3d *vector);
extern void sub_241FD0(RwUInt8 **cursor, const void *src, RwInt32 size);
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern void sub_23F090(RwBool (*callback)(rwaInstance *obj, void *data), void *data);
extern RwBool sub_23F070(rwaInstance *obj, rwaInstFind *find);
RwBool sub_242D80(RwaWaveDef *waveDef, const RwaWaveFormat *format);
RwBool sub_2429D0(const RwaWaveFormat *format1, const RwaWaveFormat *format2);
void sub_242C60(const rwaWaveFormatDesc *desc, RwaWaveFormat *format, RwBool init);
void sub_242B30(RwaWaveFormat *format);
void sub_242FA0(RwaWaveFormat *format);
RwaWaveDef *sub_243130(const RwaUUID *uuid);
extern RwUInt32 sub_249900(const RwaWaveFormat *format, RwUInt32 a, const RwaWaveFormat *target);
extern RwUInt32 sub_2498D0(const RwaWaveFormat *format, void *buffer, RwUInt32 offset,
                           const RwaWaveFormat *target);
extern RwBool sub_249920(const RwaWaveFormat *format, void *buffer, RwUInt32 a,
                         const RwaWaveFormat *target, void *converted);
extern void *RwaWaveDictGetWorking(void);
extern void RwaWaveDictAddWave(void *dict, RwaWave *wave);
extern void RwaWaveDictRemoveAllWave(RwaWave *wave);
extern RwUInt32 RwaWaveDictGetCount(void);
extern rwaWaveDict *RwaWaveDictFindByIndex(RwUInt32 index);
extern void *memcpy(void *dst, const void *src, RwUInt32 size);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED5BC @ 0x003ED5BC
// match: _unk_3ED5CC @ 0x003ED5CC
// match: _unk_3ED5DC @ 0x003ED5DC
// match: _unk_3ED5EC @ 0x003ED5EC
// match: _unk_3ED5FC @ 0x003ED5FC
// match: _unk_3ED60C @ 0x003ED60C
// match: _unk_3ED61C @ 0x003ED61C
// match: _unk_3ED62C @ 0x003ED62C
// match: _unk_3ED63C @ 0x003ED63C
// match: _unk_3ED64C @ 0x003ED64C

// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED5BC
const RwaUUID unk_3ED5BC = { 0xD9EA9798, 0xBBBC, 0x447B, { 0x96, 0xB2, 0x65, 0x47, 0x59, 0x10, 0x2E, 0x16 } };
// 0x003ED5CC
const RwaUUID unk_3ED5CC = { 0xD01BD217, 0x3587, 0x4EED, { 0xB9, 0xD9, 0xB8, 0xE8, 0x6E, 0xA9, 0xB9, 0x95 } };
// 0x003ED5DC
const RwaUUID unk_3ED5DC = { 0xDA1E4382, 0x2C99, 0x4C61, { 0xAD, 0x99, 0x7F, 0x36, 0x4B, 0x21, 0x15, 0x37 } };
// 0x003ED5EC
const RwaUUID unk_3ED5EC = { 0xF86215B0, 0x31D5, 0x4C29, { 0xBD, 0x37, 0xCD, 0xBF, 0x9B, 0xD1, 0x0C, 0x53 } };
// 0x003ED5FC
const RwaUUID unk_3ED5FC = { 0x632FA22B, 0x11DD, 0x458F, { 0xAA, 0x27, 0xA5, 0xC3, 0x46, 0xE9, 0x79, 0x0E } };
// 0x003ED60C
const RwaUUID unk_3ED60C = { 0x3F1D8147, 0xB7C4, 0x41E6, { 0xA6, 0x9B, 0x3C, 0xC0, 0x02, 0x5B, 0x33, 0xC7 } };
// 0x003ED61C
const RwaUUID unk_3ED61C = { 0xBACFB36E, 0x529D, 0x4692, { 0xBF, 0x53, 0x32, 0x42, 0x56, 0xB0, 0x73, 0x4F } };
// 0x003ED62C
const RwaUUID unk_3ED62C = { 0x34D09A54, 0x57D3, 0x409E, { 0xA6, 0xAD, 0x2B, 0xC8, 0x45, 0xAE, 0xC3, 0x39 } };
// 0x003ED63C
const RwaUUID unk_3ED63C = { 0x04C15BA7, 0xF907, 0x40AB, { 0xA4, 0x9F, 0xEE, 0xFE, 0xF8, 0xC4, 0xD2, 0x96 } };
// 0x003ED64C
const RwaUUID unk_3ED64C = { 0xA30DB390, 0x58A9, 0x43C4, { 0xB9, 0xD2, 0x55, 0xD8, 0x4D, 0x3A, 0xE7, 0x54 } };
// 0x003ED65C
const RwaUUID unk_3ED65C = { 0xEF386593, 0xB611, 0x432D, { 0x95, 0x7F, 0xA7, 0x1A, 0xDE, 0x44, 0x22, 0x7A } };
// 0x0042F7A0
const RwaUUID *unk_42F7A0[9] = {
    &unk_3ED5BC,
    &unk_3ED5CC,
    &unk_3ED5DC,
    &unk_3ED5EC,
    &unk_3ED5FC,
    &unk_3ED64C,
    &unk_3ED60C,
    &unk_3ED61C,
    &unk_3ED65C,
};
// 0x0042F7C4
/* Not referenced by name (the codecs' table ends at nine). */
RwUInt32 unk_42F7C4[5] = { 0x200 };
// 0x00506FFC
RwaWave *dword_506FFC;
// 0x00507000
RwUInt32 dword_507000;
// End of its data definitions.

// match: _unk_3ED65C @ 0x003ED65C




// match: _unk_42F7A0 @ 0x0042F7A0
// match: _unk_42F7C4 @ 0x0042F7C4

// match: _sub_2422B0 @ 0x002422B0

RwBool
sub_2422B0(void)
{
    if (sub_243950(sizeof(RwaWave), 0x10, 8, 0, unk_506FD4, rwaMEMHINTDUR_GLOBAL | rwaID_806))
    {
        dword_506FF8 = TRUE;

        return TRUE;
    }

    return FALSE;
}

// match: _sub_2422E0 @ 0x002422E0
void
sub_2422E0(void)
{
    sub_2438E0(unk_506FD4);
    dword_506FF8 = 0;
}

// match: _sub_242300 @ 0x00242300
static void
sub_242300(RwaWave *wave)
{
    if (wave->flags & 8)
    {
        sub_2421B0(wave->data);
    }

    if (wave->flags & 1)
    {
        if (wave->waveDef->instances)
        {
            sub_2437A0(wave->waveDef->instances, wave);
        }
        else
        {
            sub_2437A0(unk_506FD4, wave);
        }
    }
    else if (!(wave->flags & 4))
    {
        sub_2421B0(wave);
    }
}

// match: _sub_242350 @ 0x00242350
static void
sub_242350(RwaWave *wave, const RwaWaveFormat *format, RwaWaveFormat *target)
{
    RwaWaveDef     *waveDef = wave->waveDef;
    RwaWaveFormat   converted;
    rwaWaveFormatDesc *desc;

    if (target && target->dataType && waveDef->noFormats > 0)
    {
        if (!sub_242D80(waveDef, target))
        {
            return;
        }
    }
    else
    {
        desc = waveDef->formats ? waveDef->formats[waveDef->format] : NULL;
        if (!desc)
        {
            if (!target)
            {
                target = (RwaWaveFormat *)format;
            }
        }
        else
        {
            sub_242C60(desc, &converted, TRUE);
            converted.sampleRate = format->sampleRate;
            converted.extra = format->extra;
            converted.extraSize = format->extraSize;
            target = &converted;
        }
    }

    if (sub_2429D0(format, target))
    {
        target->extra = format->extra;
        target->extraSize = format->extraSize;
    }

    target->length = sub_249900(format, 0, target);

    rwaWaveFormatInit(&wave->deviceFormat);
    wave->deviceFormat = *target;

    if (target->extra && target->extraSize > 0)
    {
        wave->deviceFormat.extra = sub_242170(target->extraSize, rwaMEMHINTDUR_EVENT | rwaID_806);
        if (wave->deviceFormat.extra)
        {
            memcpy(wave->deviceFormat.extra, target->extra, target->extraSize);
        }
    }
}

// match: _sub_242460 @ 0x00242460
RwaWave *
sub_242460(RwaWaveDef *waveDef, rwaInstance *state, void *a, void *b, RwBool mono,
           RwaWave *wave)
{
    if (!waveDef)
    {
        waveDef = sub_243130(&unk_3EDF4C);
    }

    if (!state)
    {
        rwaInstFind find;

        find.found = NULL;
        find.def = waveDef->objDef;
        sub_23F090((RwBool (*)(rwaInstance *, void *))sub_23F070, &find);
        state = find.found;
    }

    if (waveDef->dataSize && !wave->data)
    {
        wave->data = sub_242170(waveDef->dataSize, rwaMEMHINTDUR_EVENT | rwaID_806);
        wave->flags |= 8;
    }

    wave->waveDef = waveDef;
    wave->state = state;

    if (!sub_242D80(waveDef, &wave->deviceFormat))
    {
        sub_242350(wave, &wave->format, NULL);
    }

    if (mono && wave->deviceFormat.noChannels == 1)
    {
        wave->flags |= 2;
    }

    return wave;
}

// match: _sub_242510 @ 0x00242510
void
sub_242510(RwaWave *wave)
{
    if (wave->waveDef->destroy)
    {
        wave->waveDef->destroy(wave);
    }

    sub_242B30(&wave->format);
    sub_242B30(&wave->deviceFormat);
    RwaWaveDictRemoveAllWave(wave);
    sub_240C30(&wave->uniqueID);
    sub_242300(wave);
}

// match: _sub_242550 @ 0x00242550
void
sub_242550(RwaWave *wave, RwBool set)
{
    if (set)
    {
        wave->flags |= 0x10;
    }
    else
    {
        wave->flags &= ~0x10;
    }
}

// match: _sub_242570 @ 0x00242570
RwBool
sub_242570(RwaWave *wave)
{
    /* The device-wide callback takes no wave: RwaWaveDefUploadBusyFunc in
     * docs/reference/rwacore_ps2.h; the image tail-calls it without arguments. */
    RwBool    (*busy)(void) = wave->waveDef->busy;

    if (!busy)
    {
        return FALSE;
    }

    return busy();
}

// match: _sub_242590 @ 0x00242590
void
sub_242590(RwaWave *wave)
{
    RwUInt8    *cursor;
    RwaWave     swapped;

    cursor = (RwUInt8 *)&swapped;

    sub_240A30((RwaV3d *)&wave->uniqueID);
    *(RwaUniqueID *)cursor = wave->uniqueID;
    cursor += sizeof(RwaUniqueID);
    *(RwaWaveDef **)cursor = wave->waveDef;
    cursor += sizeof(RwaWaveDef *);

    sub_242FA0(&wave->format);
    *(RwaWaveFormat *)cursor = wave->format;
    cursor += sizeof(RwaWaveFormat);

    sub_242FA0(&wave->deviceFormat);
    *(RwaWaveFormat *)cursor = wave->deviceFormat;
    cursor += sizeof(RwaWaveFormat);

    sub_241FD0(&cursor, &wave->unk48, sizeof(wave->unk48));
    sub_241FD0(&cursor, &wave->buffer, sizeof(wave->buffer));
    sub_241FD0(&cursor, &wave->data, sizeof(wave->data));
    sub_241FD0(&cursor, &wave->flags, sizeof(wave->flags));
    *(void **)cursor = wave->state;

    *wave = swapped;
}

// match: _sub_242670 @ 0x00242670
RwaWave *
sub_242670(RwaWaveDef *waveDef, void *params, const RwaWaveFormat *format,
           RwaWaveFormat *target, RwBool mono, RwaWave *wave)
{
    if (wave)
    {
        wave->flags = 4;
    }
    else
    {
        RwaWave    *allocated;

        if (!waveDef->dataSize)
        {
            allocated = (RwaWave *)sub_243670(unk_506FD4, rwaMEMHINTDUR_EVENT | rwaID_806);
        }
        else
        {
            if (!waveDef->instances)
            {
                waveDef->instances = sub_243950(sizeof(RwaWave), 8, 1, 1, NULL,
                                                rwaMEMHINTDUR_EVENT | rwaID_806);
                if (!waveDef->instances)
                {
                    goto fail;
                }
            }

            allocated = (RwaWave *)sub_243670(waveDef->instances, rwaMEMHINTDUR_EVENT | rwaID_806);
        }

        if (!allocated)
        {
            goto fail;
        }

        allocated->flags = 1;
        wave = allocated;
    }

    sub_240B40(&wave->uniqueID);
    wave->buffer = NULL;
    wave->unk48 = 0;
    rwaWaveFormatInit(&wave->format);
    wave->waveDef = waveDef;
    wave->state = params;
    wave->format = *format;

    if (format->extra && format->extraSize > 0)
    {
        wave->format.extra = sub_242170(format->extraSize, rwaMEMHINTDUR_EVENT | rwaID_806);
        if (!wave->format.extra)
        {
            goto fail;
        }

        memcpy(wave->format.extra, format->extra, format->extraSize);
    }

    sub_242350(wave, format, target);

    if (wave->deviceFormat.noChannels == 1)
    {
        wave->flags |= mono ? 2 : 0;
    }

    if (wave->waveDef->dataSize)
    {
        wave->data = sub_242170(waveDef->dataSize, rwaMEMHINTDUR_EVENT | rwaID_806);
        wave->flags |= 8;
    }
    else
    {
        wave->data = NULL;
    }

    if (wave->waveDef->create && !wave->waveDef->create(wave, params))
    {
        sub_242300(wave);
        goto fail;
    }

    RwaWaveDictAddWave(RwaWaveDictGetWorking(), wave);

    return wave;

  fail:
    return NULL;
}

// match: _sub_242810 @ 0x00242810
RwaWave *
sub_242810(RwaWave *wave, RwUInt32 offset, void *buffer, RwUInt32 size)
{
    RwaWave      *(*upload)(RwaWave *wave, RwUInt32 offset, void *buffer, RwUInt32 size);
    RwaWaveFormat  *source = &wave->format;
    RwaWaveFormat  *target = &wave->deviceFormat;
    void           *converted = NULL;

    upload = (RwaWave *(*)(RwaWave *, RwUInt32, void *, RwUInt32))wave->waveDef->unk14;

    if (upload)
    {
        RwaWave    *result;
        RwUInt32   uploadOffset;

        if (!sub_2429D0(source, target))
        {
            RwaWaveFormat   format = *source;

            uploadOffset = sub_2498D0(&format, buffer, offset, target);
            format.length = size;
            size = sub_249900(&format, (RwUInt32)buffer, target);
            converted = sub_242180(size, rwaMEMHINTDUR_EVENT | rwaID_806);
            if (!converted)
            {
                return NULL;
            }

            if (!sub_249920(&format, buffer, 0, target, converted))
            {
                sub_2422A0(converted);

                return NULL;
            }

            buffer = converted;
        }
        else
        {
            uploadOffset = offset;
        }

        dword_506FFC = wave;
        dword_507000 = uploadOffset;
        result = upload(wave, uploadOffset, buffer, size);
        sub_242550(result, TRUE);

        if (converted)
        {
            while (sub_242570(result))
            {
            }

            sub_2422A0(converted);
        }

        return result;
    }

    return NULL;
}
