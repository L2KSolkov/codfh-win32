/*
 * codfh-match: RenderWare Audio's Xbox streamed wave definition
 * (0x24DA70-0x24DF80), built with VC7.1 like the rest of the Xbox layer
 * (int3 fill): waves whose data live in the streamed waves' memory, 144-byte
 * units of the allocation bitmap at 0x51DE60 (or the application's
 * allocator, when it set one), loaded straight from the file.
 */
#include "rwa.h"
#include "rwaint.h"



extern RwaWave *sub_242670(RwaWaveDef *waveDef, void *params, const RwaWaveFormat *format,
                           RwaWaveFormat *target, RwBool mono, RwaWave *wave);
extern void sub_242510(RwaWave *wave);
extern RwaWaveDef *sub_243090(rwaObjDef *objDef, RwaWaveDef *waveDef);
extern void RwaWaveDefAssignID(RwaWaveDef *waveDef, const RwaUUID *uuid, const RwChar *name);
extern void sub_242D20(RwaWaveDef *waveDef, rwaWaveFormatDesc **formats, RwUInt32 noFormats);
extern RwaUUID *sub_242950(const RwaUUID *uuid, RwBool (*callback)(RwaWave *wave, void *data),
                           void *data);
extern rwaObjDef *sub_23DCA0(rwaObjDef *root, const void *uuid, rwaObjDef **parentOut);
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern void *memcpy(void *dst, const void *src, RwUInt32 size);
extern RwUInt32 RwFread(void *buffer, RwUInt32 size, RwUInt32 count, void *file);
extern RwaAllocBitmap *sub_2FD5D0(RwUInt32 numUnits, RwaAllocBitmap *bitmap, RwUInt8 *bits);
extern RwUInt32 sub_2FD7A0(RwaAllocBitmap *bitmap);
extern RwUInt32 *sub_2FD800(RwaAllocBitmap *bitmap, RwUInt32 *handle, RwUInt32 a3,
                            RwUInt32 a4, RwUInt32 a5, RwUInt32 *out);
extern RwUInt32 sub_2FD850(RwaAllocBitmap *bitmap, RwUInt32 handle0, RwUInt32 handle1);
extern RwBool sub_2FD880(RwaAllocBitmap *bitmap, RwUInt32 count, RwUInt32 *handle);
extern void sub_2FDAC0(RwaAllocBitmap *bitmap, RwUInt32 *handle);
extern void rwaAllocBitmapDestroy(RwaAllocBitmap *bitmap);
extern RwBool sub_242B90(RwaWaveDef *waveDef);

extern RwaWaveDef dword_507C78;     /* the streamed wave definition */
extern RwUInt32 (*dword_507CD4)(RwUInt32 size);     /* the application's allocator */
extern void (*dword_507CD8)(RwUInt32 handle);
extern RwUInt32 (*dword_507CDC)(void);
extern RwBool dword_507CE0;         /* a load is pending */
extern RwaAllocBitmap dword_51DE60; /* the streamed waves' memory */
extern RwUInt8 unk_516CC0[];        /* its bits */
extern const RwaUUID unk_3ED5CC;    /* PCM */
extern const RwaUUID unk_3ED5FC;    /* Xbox ADPCM */
extern const RwaUUID unk_3EDF5C;
extern const RwaUUID unk_41AB64;
extern const RwaUUID unk_3EDF4C;    /* the streamed wave definition (unit_24EC60.c's) */
extern rwaWaveFormatDesc *off_4302A0[8];

#define rwaSTREAMEDUNIT 144

RwaWave *sub_24DBA0(RwaWave *wave, rwaInstance *obj);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3EDBDC @ 0x003EDBDC
// match: _unk_3EDBC8 @ 0x003EDBC8
// match: _unk_3EDBB4 @ 0x003EDBB4
// match: _unk_3EDBA0 @ 0x003EDBA0
// match: _unk_3EDB8C @ 0x003EDB8C
// match: _unk_3EDB78 @ 0x003EDB78
// match: _unk_3EDB64 @ 0x003EDB64
// match: _unk_3EDB50 @ 0x003EDB50
// match: _unk_3EDB3C @ 0x003EDB3C
// match: _unk_3EDB28 @ 0x003EDB28
// match: _unk_3EDB14 @ 0x003EDB14
// match: _unk_3EDB00 @ 0x003EDB00
// match: _unk_3EDAEC @ 0x003EDAEC
// match: _unk_3EDAD8 @ 0x003EDAD8
// match: _unk_3EDAC4 @ 0x003EDAC4
// match: _unk_3EDAB0 @ 0x003EDAB0
// match: _unk_3EDA9C @ 0x003EDA9C
// match: _unk_3EDA88 @ 0x003EDA88
// match: _unk_3EDA74 @ 0x003EDA74
// match: _unk_3EDA60 @ 0x003EDA60
// match: _unk_3EDA4C @ 0x003EDA4C
// match: _unk_3EDA38 @ 0x003EDA38

// What its data definitions name.
extern RwUInt8 unk_3ED5BC[];
extern RwUInt8 unk_3ED5DC[];
extern RwUInt8 unk_3ED5EC[];
extern RwUInt8 unk_3ED61C[];
extern RwUInt8 unk_3ED64C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003EDA24
void *const unk_3EDA24[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x108,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x1,
};
// 0x003EDA38
void *const unk_3EDA38[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x108,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    0,
};
// 0x003EDA4C
void *const unk_3EDA4C[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x208,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x1,
};
// 0x003EDA60
void *const unk_3EDA60[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x208,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    0,
};
// 0x003EDA74
void *const unk_3EDA74[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x110,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x1,
};
// 0x003EDA88
void *const unk_3EDA88[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x110,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    0,
};
// 0x003EDA9C
void *const unk_3EDA9C[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x210,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x1,
};
// 0x003EDAB0
void *const unk_3EDAB0[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x210,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    0,
};
// 0x003EDAC4
void *const unk_3EDAC4[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x410,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    0,
};
// 0x003EDAD8
void *const unk_3EDAD8[5] =
{
    (void *)&unk_3ED5CC,
    (void *)0x610,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    0,
};
// 0x003EDAEC
void *const unk_3EDAEC[5] =
{
    (void *)&unk_3ED5DC,
    (void *)0x120,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDB00
void *const unk_3EDB00[5] =
{
    (void *)&unk_3ED5BC,
    (void *)0x104,
    (void *)0x1,
    (void *)192000,
    (void *)0x2,
};
// 0x003EDB14
void *const unk_3EDB14[5] =
{
    (void *)&unk_3ED5BC,
    (void *)0x204,
    (void *)0x1,
    (void *)192000,
    (void *)0x2,
};
// 0x003EDB28
void *const unk_3EDB28[5] =
{
    (void *)&unk_3ED5FC,
    (void *)0x104,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDB3C
void *const unk_3EDB3C[5] =
{
    (void *)&unk_3ED5FC,
    (void *)0x204,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDB50
void *const unk_3EDB50[5] =
{
    (void *)&unk_3ED5FC,
    (void *)0x404,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDB64
void *const unk_3EDB64[5] =
{
    (void *)&unk_3ED5FC,
    (void *)0x604,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDB78
void *const unk_3EDB78[5] =
{
    (void *)&unk_3ED64C,
    (void *)0x110,
    (void *)0x7D00,
    (void *)0xBB80,
    (void *)0x2,
};
// 0x003EDB8C
void *const unk_3EDB8C[5] =
{
    (void *)&unk_3ED5EC,
    (void *)0x104,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDBA0
void *const unk_3EDBA0[5] =
{
    (void *)&unk_3ED5EC,
    (void *)0x204,
    (void *)0x1,
    (void *)0xFFFFFFFF,
    (void *)0x2,
};
// 0x003EDBB4
void *const unk_3EDBB4[5] =
{
    (void *)&unk_3ED61C,
    (void *)0x110,
    (void *)0x3E80,
    (void *)0xBB80,
    (void *)0x6,
};
// 0x003EDBC8
void *const unk_3EDBC8[5] =
{
    (void *)&unk_3ED61C,
    (void *)0x210,
    (void *)0x3E80,
    (void *)0xBB80,
    (void *)0x6,
};
// 0x003EDBDC
void *const unk_3EDBDC[5] =
{
    (void *)&unk_3ED64C,
    (void *)0x610,
    (void *)0x7D00,
    (void *)0xBB80,
    (void *)0x6,
};
// 0x004302A0
rwaWaveFormatDesc *off_4302A0[8] = {
    &unk_3EDA88,
    &unk_3EDAB0,
    &unk_3EDB28,
    &unk_3EDB3C,
    &unk_3EDA24,
    &unk_3EDA4C,
    &unk_3EDAD8,
    &unk_3EDAC4,
};
// 0x00507C78
RwaWaveDef dword_507C78;
// 0x00507CD4
RwUInt32 (*dword_507CD4)(RwUInt32 size);
// 0x00507CD8
void (*dword_507CD8)(RwUInt32 handle);
// 0x00507CDC
RwUInt32 (*dword_507CDC)(void);
// 0x00507CE0
RwBool dword_507CE0;
// 0x00516CC0
RwUInt8 unk_516CC0[29088];
// 0x0051DE60
RwaAllocBitmap dword_51DE60;
// End of its data definitions.

// match: _unk_3EDA24 @ 0x003EDA24


// match: _off_4302A0 @ 0x004302A0

// match: _sub_24DA70 @ 0x0024DA70

RwaWave *
sub_24DA70(void *params, const RwaWaveFormat *format, RwaWaveFormat *target, RwBool mono,
           RwaWave *wave)
{
    return sub_242670(&dword_507C78, params, format, target, mono, wave);
}

// match: _sub_24DAA0 @ 0x0024DAA0
void
sub_24DAA0(RwaWave *wave)
{
    sub_242510(wave);
}

/* Releases the streamed waves' memory and the definition. */
// match: _sub_24DAB0 @ 0x0024DAB0
RwBool
sub_24DAB0(void)
{
    rwaAllocBitmapDestroy(&dword_51DE60);
    return sub_242B90(&dword_507C78) ? TRUE : FALSE;
}

// match: _sub_24DAD0 @ 0x0024DAD0
static RwUInt32
sub_24DAD0(RwUInt32 size)
{
    RwUInt32    handle;

    if (dword_507CD4)
    {
        return dword_507CD4(size);
    }
    sub_2FD880(&dword_51DE60, (size + rwaSTREAMEDUNIT - 1) / rwaSTREAMEDUNIT, &handle);
    return handle;
}

// match: _sub_24DB10 @ 0x0024DB10
void
sub_24DB10(RwUInt32 handle)
{
    if (dword_507CD8)
    {
        dword_507CD8(handle);
    }
    else
    {
        sub_2FDAC0(&dword_51DE60, &handle);
    }
}

/* The free streamed wave memory. */
// match: _sub_24DB40 @ 0x0024DB40
RwUInt32
sub_24DB40(void)
{
    if (dword_507CDC)
    {
        return dword_507CDC();
    }
    return sub_2FD7A0(&dword_51DE60) * rwaSTREAMEDUNIT;
}

/* The address of a handle's memory. */
// match: _sub_24DB60 @ 0x0024DB60
RwUInt8 *
sub_24DB60(RwUInt32 handle)
{
    if (dword_507CD4)
    {
        return (RwUInt8 *)handle;
    }
    return (RwUInt8 *)dword_51DE60.base
           + rwaSTREAMEDUNIT * (handle & ((1 << dword_51DE60.shift) - 1));
}

// match: _sub_24DBA0 @ 0x0024DBA0
RwaWave *
sub_24DBA0(RwaWave *volatile input, rwaInstance *obj)
{
    /* The qualified input read preserves the early wave save at 24DBA5.
     * The length reads preserve the reload at 24DC31 after the unk48 store.
     * These reproduce the observed accesses; the original qualifiers are unknown. */
    RwaWave *wave = input;
    rwaStreamedMemory *memory = (rwaStreamedMemory *)obj->state;

    if (!dword_51DE60.size
        && sub_2FD5D0(memory->size / rwaSTREAMEDUNIT, &dword_51DE60, unk_516CC0))
    {
        dword_51DE60.base = memory->base;
        dword_51DE60.size = memory->size;
        dword_51DE60.unitSize = rwaSTREAMEDUNIT;
    }

    if (!RwaUUIDCompare(wave->deviceFormat.dataType, &unk_3ED5CC))
    {
        wave->unk48 = ((volatile RwaWave *)wave)->deviceFormat.length;
    }
    else if (!RwaUUIDCompare(wave->deviceFormat.dataType, &unk_3ED5FC))
    {
        wave->unk48 = (7 * ((volatile RwaWave *)wave)->deviceFormat.length) >> 1;
    }
    else
    {
        return NULL;
    }

    wave->buffer = (RwUInt8 *)sub_24DAD0((((volatile RwaWave *)wave)->deviceFormat.length + 255) & ~255);
    return wave->buffer ? wave : NULL;
}

// match: _sub_24DC60 @ 0x0024DC60
void
sub_24DC60(RwaWave *wave)
{
    sub_24DB10((RwUInt32)wave->buffer);
}

/* Writes size bytes at offset of the wave's data. */
// match: _sub_24DC70 @ 0x0024DC70
RwaWave *
sub_24DC70(RwaWave *wave, RwUInt32 offset, const void *src, RwUInt32 size)
{
    memcpy(sub_24DB60((RwUInt32)wave->buffer) + offset, src, size);
    return wave;
}

/* Reads the wave's data from offset. */
// match: _sub_24DCB0 @ 0x0024DCB0
RwaWave *
sub_24DCB0(RwaWave *wave, void *unused, RwUInt32 offset, void *dest)
{
    memcpy(dest, sub_24DB60((RwUInt32)wave->buffer) + offset, wave->deviceFormat.length);
    return wave;
}

// match: _sub_24DCF0 @ 0x0024DCF0
RwUInt8 *
sub_24DCF0(RwaWave *wave)
{
    if (sub_24DBA0(wave, (rwaInstance *)wave->state))
    {
        return wave->buffer;
    }
    return NULL;
}

/* Grows (add) or shrinks the wave's memory by size. */
// match: _sub_24DD10 @ 0x0024DD10
void
sub_24DD10(RwaWave *wave, RwUInt32 size, RwBool add)
{
    RwUInt32    handle = size;
    RwBool      bitmap = !dword_507CD4;
    RwUInt32    out;

    if (add)
    {
        if (bitmap)
        {
            sub_2FD800(&dword_51DE60, &handle, (RwUInt32)wave->buffer, wave->format.length,
                       rwaSTREAMEDUNIT, &out);
            wave->buffer = (RwUInt8 *)out;
        }
        else
        {
            wave->buffer += size;
        }
    }
    else if (bitmap)
    {
        wave->buffer = (RwUInt8 *)sub_2FD850(&dword_51DE60, size, (RwUInt32)wave->buffer);
    }
    else
    {
        wave->buffer -= size;
    }
}

// match: _sub_24DDA0 @ 0x0024DDA0
void
sub_24DDA0(RwaWave *wave)
{
    sub_24DC60(wave);
}

/* Loads size bytes of the file into the wave's memory (whole sectors). */
// match: _sub_24DDB0 @ 0x0024DDB0
RwUInt32
sub_24DDB0(void *file, RwUInt32 handle, RwUInt32 offset, RwUInt32 size)
{
    if (dword_507CE0)
    {
        if (((rwaRtFile *)file)->status == 2)
        {
            dword_507CE0 = FALSE;
            return size;
        }
    }
    else
    {
        RwFread(sub_24DB60(handle) + offset, 1, (size + 2047) / 2048 * 2048, file);
        dword_507CE0 = TRUE;
    }
    return 0;
}

// match: _sub_24DE20 @ 0x0024DE20
RwaWave *
sub_24DE20(RwaWave *wave)
{
    if (wave->buffer)
    {
        sub_24DB10((RwUInt32)wave->buffer);
        wave->buffer = NULL;
    }
    return wave;
}

/* Registers the streamed wave definition. */
// match: _sub_24DE40 @ 0x0024DE40
RwaWaveDef *
sub_24DE40(void)
{
    RwaWaveDef *waveDef = sub_243090(sub_23DCA0(NULL, &unk_3EDF5C, NULL), &dword_507C78);
    rwaObjDef  *def;

    if (!waveDef)
    {
        return waveDef;
    }
    {

        RwaWaveDefAssignID(waveDef, &unk_3EDF4C, NULL);
        waveDef->create = (RwBool (*)(RwaWave *, void *))sub_24DBA0;
        waveDef->destroy = sub_24DC60;
        waveDef->unk14 = sub_24DC70;
        waveDef->unk18 = sub_24DCB0;
        waveDef->unk20 = sub_24DCF0;
        waveDef->unk2C = sub_24DD10;
        waveDef->unk24 = sub_24DDA0;
        waveDef->unk28 = sub_24DDB0;
        waveDef->dataSize = 4;
        waveDef->unk48 = 8;
        sub_242D20(waveDef, off_4302A0, 8);
        def = sub_23DCA0(NULL, &unk_41AB64, NULL);
        if (def)
        {
            rwaCodecInfo *codec = (rwaCodecInfo *)def->unk54;

            codec->entries = (void **)off_4302A0;
            codec->numEntries = 8;
        }
    }

    return waveDef;
}

// match: _sub_24DF00 @ 0x0024DF00
RwaUUID *
sub_24DF00(void)
{
    return sub_242950(&unk_3EDF4C, (RwBool (*)(RwaWave *, void *))sub_24DE20, NULL);
}
