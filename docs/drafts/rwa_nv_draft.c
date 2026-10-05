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

extern RwaWaveDef dword_507C78;     /* the streamed wave definition */
extern RwUInt32 (*dword_507CD4)(RwUInt32 size);     /* the application's allocator */
extern void (*dword_507CD8)(RwUInt32 handle);
extern RwUInt32 (*dword_507CDC)(void);
extern RwBool dword_507CE0;         /* a load is pending */
extern RwaAllocBitmap dword_51DE60; /* the streamed waves' memory */
extern RwUInt8 unk_516CC0[];        /* its bits */
extern const RwaUUID unk_3ED5CC;    /* PCM */
extern const RwaUUID unk_3ED5FC;    /* Xbox ADPCM */
extern const RwaUUID dword_3EDF5C;
extern const RwaUUID dword_41AB64;
extern const RwaUUID aNv;           /* the streamed wave definition */
extern rwaWaveFormatDesc *off_4302A0[8];

#define rwaSTREAMEDUNIT 144

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

/* Allocates size bytes of streamed wave memory: a handle. */
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

/* Creates a wave: the streamed waves' memory on first use, then the wave's
 * (PCM, or Xbox ADPCM's 3.5 bytes a sample). */
// match: _sub_24DBA0 @ 0x0024DBA0
RwaWave *
sub_24DBA0(RwaWave *wave, rwaInstance *obj)
{
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
        wave->unk48 = wave->deviceFormat.length;
    }
    else if (!RwaUUIDCompare(wave->deviceFormat.dataType, &unk_3ED5FC))
    {
        wave->unk48 = (7 * wave->deviceFormat.length) >> 1;
    }
    else
    {
        return NULL;
    }

    wave->buffer = (RwUInt8 *)sub_24DAD0((wave->deviceFormat.length + 255) & ~255);
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
    RwaWaveDef *waveDef = sub_243090(sub_23DCA0(NULL, &dword_3EDF5C, NULL), &dword_507C78);
    rwaObjDef  *def;

    if (!waveDef)
    {
        return waveDef;
    }
    {

        RwaWaveDefAssignID(waveDef, &aNv, NULL);
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
        def = sub_23DCA0(NULL, &dword_41AB64, NULL);
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
    return sub_242950(&aNv, (RwBool (*)(RwaWave *, void *))sub_24DE20, NULL);
}
