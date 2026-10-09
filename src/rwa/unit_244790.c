/*
 * codfh-match: RenderWare Audio's memory wave definition (0x244790-
 * 0x244930): waves whose data is a block in memory (+0x4C), with the
 * definition's create, destroy, upload and download callbacks, its
 * registration and unregistration, and an interface definition's
 * registration (the definition at 0x50714C). The database missed most of
 * these functions.
 */
#include "rwa.h"
#include "rwaint.h"



extern RwaWaveDef unk_5070F0;           /* the memory wave definition */
extern RwaObjInterfaceDef unk_50714C;

extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern RwBool sub_242B90(RwaWaveDef *waveDef);
extern RwaWaveDef *sub_243090(rwaObjDef *objDef, RwaWaveDef *waveDef);
extern RwaWaveDef *RwaWaveDefAssignID(RwaWaveDef *waveDef, const RwaUUID *uuid,
                                      const RwChar *name);
extern RwaObjInterfaceDef *sub_243E20(RwaObjInterfaceDef *def);
extern RwBool sub_243EA0(RwaObjInterfaceDef *def);
extern RwaObjInterfaceDef *RwaWaveDictAssignID(RwaObjInterfaceDef *def, const RwaUUID *uuid,
                                               const RwChar *name);
extern RwaObjInterfaceDef *sub_243CD0(RwaObjInterfaceDef *def, void *inputs, RwUInt32 noInputs,
                                      void *outputs, RwUInt32 noOutputs);
extern void *memcpy(void *dst, const void *src, RwUInt32 size);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED854 @ 0x003ED854
// match: _unk_3ED844 @ 0x003ED844
// match: _unk_3ED834 @ 0x003ED834
// match: _unk_3ED824 @ 0x003ED824
// match: _unk_3ED814 @ 0x003ED814
// match: _unk_3ED804 @ 0x003ED804
// match: _unk_3ED7F4 @ 0x003ED7F4
// match: _unk_3ED7E4 @ 0x003ED7E4
// match: _unk_3ED7D4 @ 0x003ED7D4
// match: _unk_3ED7C4 @ 0x003ED7C4
// match: _unk_3ED7B4 @ 0x003ED7B4
// match: _unk_3ED7A4 @ 0x003ED7A4

// What its data definitions name.
extern RwUInt8 unk_3ED4FC[];
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED56C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED794
const RwaUUID unk_3ED794 = { 0xCA5E5BE6, 0xB366, 0x4739, { 0x8F, 0xA5, 0xF3, 0xC8, 0xBB, 0xD5, 0xE5, 0x29 } };
// 0x003ED7A4
const RwaUUID unk_3ED7A4 = { 0x03C7994D, 0xF302, 0x414F, { 0xB3, 0x6A, 0x74, 0xE3, 0x51, 0x43, 0x01, 0xEB } };
// 0x003ED7B4
const RwaUUID unk_3ED7B4 = { 0xD54AC4A0, 0x5D8F, 0x4D3B, { 0x90, 0x1E, 0x02, 0x1E, 0x8F, 0x5D, 0x05, 0x76 } };
// 0x003ED7C4
const RwaUUID unk_3ED7C4 = { 0x0DA9CCD8, 0xB5A3, 0x4323, { 0x91, 0x7E, 0x27, 0xA0, 0x2C, 0xD4, 0x2D, 0x07 } };
// 0x003ED7D4
const RwaUUID unk_3ED7D4 = { 0xE26C926F, 0x7D39, 0x4A83, { 0x83, 0x0B, 0x74, 0x57, 0xF3, 0x11, 0x3D, 0x8B } };
// 0x003ED7E4
const RwaUUID unk_3ED7E4 = { 0x84448C49, 0x55E3, 0x44D5, { 0x8C, 0xE8, 0x66, 0xFE, 0xFE, 0x43, 0x29, 0xBC } };
// 0x003ED7F4
const RwaUUID unk_3ED7F4 = { 0x955A46C4, 0x6D1C, 0x436D, { 0xAE, 0x39, 0x24, 0xD5, 0xE3, 0x97, 0xF3, 0xD9 } };
// 0x003ED804
const RwaUUID unk_3ED804 = { 0x64D0BEC0, 0x622C, 0x4FCA, { 0x98, 0x62, 0x68, 0x2C, 0x9E, 0x38, 0x9D, 0x55 } };
// 0x003ED814
const RwaUUID unk_3ED814 = { 0x1E0342F6, 0x6F95, 0x438D, { 0x8F, 0xCF, 0x1A, 0x80, 0xAD, 0x59, 0x56, 0xC8 } };
// 0x003ED824
const RwaUUID unk_3ED824 = { 0x99983CAB, 0x6F41, 0x475F, { 0xAD, 0x4F, 0x82, 0xF5, 0x2C, 0xD1, 0x1A, 0xF1 } };
// 0x003ED834
const RwaUUID unk_3ED834 = { 0xEC1C3CF8, 0x7410, 0x4865, { 0x8E, 0x3A, 0xC6, 0x1B, 0xC3, 0xB9, 0xE8, 0xA4 } };
// 0x003ED844
const RwaUUID unk_3ED844 = { 0xFC94F894, 0x672F, 0x4DB2, { 0xA4, 0xB2, 0xBA, 0x8B, 0xE9, 0x5C, 0xAB, 0x59 } };
// 0x003ED854
const RwaUUID unk_3ED854 = { 0x81F44747, 0xB3F3, 0x438F, { 0x94, 0xE4, 0x7B, 0x90, 0x20, 0x23, 0x94, 0xD4 } };
// 0x0042F930
void *unk_42F930[30] =
{
    (void *)&unk_3ED7B4,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED7D4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED7F4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED814,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)&unk_3ED834,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED844,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
};
// 0x0042F9A8
#ifdef CODFH_SP // no trailing word: unit_2422B0's unk_42F7A0 follows at SP 0x32BC4C (table at SP 0x32BBE8)
void *unk_42F9A8[25] =
#else
void *unk_42F9A8[26] =
#endif
{
    (void *)&unk_3ED7C4,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED7E4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED804,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED824,
    0,
    0,
    (void *)&unk_3ED4FC,
    (void *)0x1,
    (void *)&unk_3ED854,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
#ifndef CODFH_SP
    0,
#endif
};
// 0x005070F0
RwaWaveDef unk_5070F0;
// 0x0050714C
RwaObjInterfaceDef unk_50714C;
// End of its data definitions.

// match: _unk_3ED794 @ 0x003ED794


// match: _unk_42F930 @ 0x0042F930


// match: _unk_42F9A8 @ 0x0042F9A8

// match: _sub_244790 @ 0x00244790
// sp-match: _sub_244790 @ 0x001562B0

RwBool
sub_244790(void)
{
    return sub_242B90(&unk_5070F0) != FALSE;
}

// match: _sub_2447B0 @ 0x002447B0
// sp-match: _sub_2447B0 @ 0x001562D0
RwaWave *
sub_2447B0(RwaWave *wave)
{
    wave->data = NULL;
    wave->buffer = (RwUInt8 *)sub_242170(wave->deviceFormat.length,
                                         rwaMEMHINTDUR_EVENT | rwaID_807);
    if (!wave->buffer)
    {
        return NULL;
    }

    if (!wave->deviceFormat.dataType)
    {
        wave->deviceFormat = wave->format;
    }

    return wave;
}

// match: _sub_244800 @ 0x00244800
// sp-match: _sub_244800 @ 0x00156320
void
sub_244800(RwaWave *wave)
{
    if (wave->buffer)
    {
        sub_2421B0(wave->buffer);
    }
}

// match: _sub_244820 @ 0x00244820
// sp-match: _sub_244820 @ 0x00156340
RwaWave *
sub_244820(RwaWave *wave, RwUInt32 offset, const void *block, RwUInt32 size)
{
    memcpy(wave->buffer + offset, block, size);

    return wave;
}

// match: _sub_244850 @ 0x00244850
// sp-match: _sub_244850 @ 0x00156370
RwaWave *
sub_244850(RwaWave *wave, const RwaWaveFormat *format, RwUInt32 offset, void *block)
{
    memcpy(block, wave->buffer + offset, format->length);

    return wave;
}

// match: _sub_244880 @ 0x00244880
// sp-match: _sub_244880 @ 0x001563A0
RwaWaveDef *
sub_244880(void)
{
    RwaWaveDef *waveDef = sub_243090(NULL, &unk_5070F0);

    if (!waveDef)
    {
        return NULL;
    }

    RwaWaveDefAssignID(waveDef, &unk_3ED794, NULL);
    waveDef->create = (RwBool (*)(RwaWave *, void *))sub_2447B0;
    waveDef->destroy = sub_244800;
    waveDef->unk14 = sub_244820;
    waveDef->unk18 = sub_244850;

    return waveDef;
}

// match: _sub_2448D0 @ 0x002448D0
// sp-match: _sub_2448D0 @ 0x001563F0
RwaObjInterfaceDef *
sub_2448D0(void)
{
    if (!sub_243E20(&unk_50714C))
    {
        return NULL;
    }

    RwaWaveDictAssignID(&unk_50714C, &unk_3ED7A4, NULL);
    sub_243CD0(&unk_50714C, unk_42F930, 6, unk_42F9A8, 5);

    return &unk_50714C;
}

// match: _sub_244920 @ 0x00244920
// sp-match: _sub_244920 @ 0x00156440
RwBool
sub_244920(void)
{
    return sub_243EA0(&unk_50714C);
}
