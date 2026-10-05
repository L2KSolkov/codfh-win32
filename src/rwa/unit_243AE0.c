/*
 * codfh-match: RenderWare Audio's object interfaces (0x243AE0-0x244220;
 * the PS2 header's rwaobjinterface.h): a listener interface definition
 * (the database's RwaListenerInterfaceRegister_0), the interface
 * definitions' free list (0x50708C) and list (0x5070B0), their parameter
 * IDs, creation, destruction and lookup, and the interface instances an
 * object definition hands out, with their accessor tables.
 */
#include "rwa.h"
#include "rwaint.h"



#define rwaInterfaceDefFromLink(_link) ((RwaObjInterfaceDef *)((RwUInt8 *)(_link) - 0x20))
#define rwaInterfaceFromLink(_link) ((rwaObjInterface *)((RwUInt8 *)(_link) - 0x14))

static RwaObjInterfaceDef unk_507064;   /* the listener interface */


extern void *sub_242170(RwUInt32 size, RwUInt32 hint);
extern void sub_2421B0(void *mem);
extern void *sub_243670(void *freeList, RwUInt32 hint);
extern void sub_2437A0(void *freeList, void *item);
extern void sub_2438E0(void *freeList);
extern void *sub_243950(RwUInt32 size, RwUInt32 count, RwUInt32 align, RwInt32 a,
                        void *freeList, RwUInt32 hint);
extern RwaUniqueID *sub_240B40(RwaUniqueID *uniqueID);
extern RwaUniqueID *sub_240BF0(RwaUniqueID *uniqueID, const RwChar *name);
extern RwaUniqueID *sub_240C10(RwaUniqueID *uniqueID, const RwaUUID *uuid);
extern RwaUniqueID *sub_240C30(RwaUniqueID *uniqueID);
extern RwInt32 RwaUUIDCompare(const RwaUUID *uuid1, const RwaUUID *uuid2);
extern RwaParamTypeHandle *_rwaParamTypeHandleRefreshType(RwaParamTypeHandle *handle);
extern void *memset(void *dst, RwInt32 value, RwUInt32 size);

RwaObjInterfaceDef *sub_243CD0(RwaObjInterfaceDef *def, _rwaParamID *inputs, RwUInt32 noInputs,
                               _rwaParamID *outputs, RwUInt32 noOutputs);
RwaObjInterfaceDef *RwaWaveDictAssignID(RwaObjInterfaceDef *def, const RwaUUID *uuid,
                                        const RwChar *name);
RwaObjInterfaceDef *sub_243E20(RwaObjInterfaceDef *def);
RwBool sub_243EA0(RwaObjInterfaceDef *def);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED790 @ 0x003ED790
// match: _unk_3ED780 @ 0x003ED780
// match: _unk_3ED770 @ 0x003ED770
// match: _unk_3ED760 @ 0x003ED760
// match: _unk_3ED750 @ 0x003ED750
// match: _unk_3ED740 @ 0x003ED740
// match: _unk_3ED730 @ 0x003ED730
// match: _unk_3ED720 @ 0x003ED720
// match: _unk_3ED710 @ 0x003ED710
// match: _unk_3ED700 @ 0x003ED700
// match: _unk_3ED6F0 @ 0x003ED6F0
// match: _unk_3ED6E0 @ 0x003ED6E0
// match: _unk_3ED6D0 @ 0x003ED6D0
// match: _unk_3ED6C0 @ 0x003ED6C0
// match: _unk_3ED6B0 @ 0x003ED6B0
// match: _unk_3ED6A0 @ 0x003ED6A0
// match: _unk_3ED690 @ 0x003ED690
// match: _unk_3ED680 @ 0x003ED680

// What its data definitions name.
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED54C[];
extern RwUInt8 unk_3ED57C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED670
const RwaUUID unk_3ED670 = { 0x09D1A6D5, 0x3810, 0x4D0D, { 0xAC, 0xAC, 0x9B, 0x0A, 0x5A, 0x92, 0xA8, 0xA1 } };
// 0x003ED680
const RwaUUID unk_3ED680 = { 0x4AF771E8, 0xD1B9, 0x4E3A, { 0x95, 0xFB, 0x87, 0x26, 0x6C, 0x61, 0x50, 0xCD } };
// 0x003ED690
const RwaUUID unk_3ED690 = { 0xD407C0B4, 0x1784, 0x4F55, { 0x8D, 0xBD, 0x71, 0xCC, 0x84, 0x2F, 0xDD, 0x53 } };
// 0x003ED6A0
const RwaUUID unk_3ED6A0 = { 0x79A9835C, 0x8D5D, 0x47A3, { 0x98, 0x3C, 0xEE, 0x09, 0xDA, 0x38, 0xC2, 0x75 } };
// 0x003ED6B0
const RwaUUID unk_3ED6B0 = { 0xC60F2888, 0x94B8, 0x43EC, { 0xAD, 0x99, 0x46, 0x22, 0x49, 0x58, 0xA1, 0xB6 } };
// 0x003ED6C0
const RwaUUID unk_3ED6C0 = { 0xDD5CF3F9, 0x9DD5, 0x48E9, { 0x88, 0x0D, 0x07, 0xB2, 0xC9, 0xC5, 0xD0, 0x57 } };
// 0x003ED6D0
const RwaUUID unk_3ED6D0 = { 0x5B2E5671, 0x1DA3, 0x4E66, { 0xA1, 0xF5, 0x36, 0xD9, 0x30, 0x1E, 0x60, 0x61 } };
// 0x003ED6E0
const RwaUUID unk_3ED6E0 = { 0xD5F11407, 0x4E7E, 0x4322, { 0xBB, 0x17, 0x40, 0x37, 0xFB, 0xC1, 0x74, 0x3B } };
// 0x003ED6F0
const RwaUUID unk_3ED6F0 = { 0x023AF853, 0xC395, 0x45B6, { 0xB3, 0x6A, 0xC9, 0xF7, 0xBE, 0xFA, 0xAF, 0x77 } };
// 0x003ED700
const RwaUUID unk_3ED700 = { 0x01F7B058, 0x04A0, 0x4201, { 0x9A, 0xB5, 0x1E, 0xED, 0x6D, 0x48, 0x3E, 0x3E } };
// 0x003ED710
const RwaUUID unk_3ED710 = { 0x8076E921, 0x8060, 0x45BC, { 0x8D, 0xE6, 0x45, 0x48, 0xFF, 0xFB, 0x39, 0x2B } };
// 0x003ED720
const RwaUUID unk_3ED720 = { 0x531112B2, 0x5F0A, 0x4D0B, { 0xB6, 0xC5, 0x61, 0x12, 0xFA, 0x26, 0xAC, 0x00 } };
// 0x003ED730
const RwaUUID unk_3ED730 = { 0x4EDAB42F, 0xCCF5, 0x4539, { 0x95, 0xCD, 0x54, 0x7E, 0x13, 0x24, 0x12, 0xBE } };
// 0x003ED740
const RwaUUID unk_3ED740 = { 0xAC3ACD41, 0xDD01, 0x4F82, { 0xA9, 0xEF, 0x10, 0xA8, 0xE2, 0x32, 0x99, 0x5D } };
// 0x003ED750
const RwaUUID unk_3ED750 = { 0xFE2F807F, 0x3DAF, 0x4A90, { 0x85, 0xA3, 0x36, 0x4D, 0x7D, 0x00, 0xDC, 0x4C } };
// 0x003ED760
const RwaUUID unk_3ED760 = { 0xA2CF6B85, 0xF92C, 0x4180, { 0x88, 0x64, 0xBB, 0x4B, 0x23, 0xC5, 0x0F, 0x65 } };
// 0x003ED770
const RwaUUID unk_3ED770 = { 0x57674FA8, 0x6D69, 0x4333, { 0xBA, 0x2B, 0xF5, 0xCF, 0x9E, 0x5E, 0x54, 0x8F } };
// 0x003ED780
const RwaUUID unk_3ED780 = { 0xFA669EFC, 0xEFD0, 0x459F, { 0x86, 0x6B, 0xEF, 0x8C, 0xAA, 0xCA, 0xD6, 0xD3 } };
// 0x003ED790
void *const unk_3ED790[1] =
{
    0,
};
// 0x0042F7D8
void *unk_42F7D8[40] =
{
    (void *)&unk_3ED680,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED6A0,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED6C0,
    0,
    0,
    (void *)&unk_3ED57C,
    (void *)0x1,
    (void *)&unk_3ED6E0,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED700,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED730,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED750,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED770,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
};
// 0x0042F878
void *unk_42F878[46] =
{
    (void *)&unk_3ED690,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED6B0,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED6D0,
    0,
    0,
    (void *)&unk_3ED57C,
    (void *)0x1,
    (void *)&unk_3ED6F0,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED710,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED720,
    0,
    0,
    (void *)&unk_3ED54C,
    (void *)0x1,
    (void *)&unk_3ED740,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED760,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED780,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    0,
};
// End of its data definitions.

// match: _unk_3ED670 @ 0x003ED670


// match: _unk_42F7D8 @ 0x0042F7D8


// match: _unk_42F878 @ 0x0042F878

// match: _RwaListenerInterfaceRegister_0 @ 0x00243AE0

RwaObjInterfaceDef *
RwaListenerInterfaceRegister_0(void)
{
    if (!sub_243E20(&unk_507064))
    {
        return NULL;
    }

    RwaWaveDictAssignID(&unk_507064, &unk_3ED670, NULL);
    sub_243CD0(&unk_507064, (_rwaParamID *)unk_42F7D8, 8, (_rwaParamID *)unk_42F878, 9);

    return &unk_507064;
}

// match: _sub_243B30 @ 0x00243B30
RwBool
sub_243B30(void)
{
    return sub_243EA0(&unk_507064);
}










