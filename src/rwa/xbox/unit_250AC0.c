/*
 * codfh-match: RenderWare Audio's Xbox output interface (0x250AC0-0x250B20;
 * VC7.1): the interface the output definition (0x24EB50) registers, with
 * its seven set and seven get parameters.
 */
#include "rwa.h"
#include "rwaint.h"



extern void *sub_243E20(void *iface);
extern void RwaWaveDictAssignID(void *iface, const void *uuid, const void *textID);
extern void sub_243CD0(void *iface, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern RwBool sub_243EA0(void *iface);

extern RwUInt8 dword_507DE8[];      /* the output interface */
extern const RwUInt8 unk_3EDF88[];

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _off_430AB0 @ 0x00430AB0

// What its data definitions name.
extern RwUInt8 unk_3ED4FC[];
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED56C[];
extern RwUInt8 unk_3ED7B4[];
extern RwUInt8 unk_3ED7C4[];
extern RwUInt8 unk_3ED7D4[];
extern RwUInt8 unk_3ED7E4[];
extern RwUInt8 unk_3ED7F4[];
extern RwUInt8 unk_3ED804[];
extern RwUInt8 unk_3ED814[];
extern RwUInt8 unk_3ED824[];
extern RwUInt8 unk_3ED834[];
extern RwUInt8 unk_3ED844[];
extern RwUInt8 unk_3ED854[];
extern RwUInt8 unk_3EDF98[];
extern RwUInt8 unk_3EDFA8[];
extern RwUInt8 unk_3EDFB8[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x00430AB0
void *off_430AB0[36] =
{
    (void *)&unk_3EDFA8,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
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
    0,
};
// 0x00430B40
#ifdef CODFH_SP // ends with the two words multiplayer has after off_430EA0 (128, 1: SP 0x32D43C; tri.c's data follows at SP 0x32D444; table at SP 0x32D3B0)
void *off_430B40[37] =
#else
void *off_430B40[36] =
#endif
{
    (void *)&unk_3EDF98,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3EDFB8,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
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
#ifdef CODFH_SP
    (void *)0x80,
    (void *)0x1,
#else
    0,
#endif
};
// 0x00507DE8
RwUInt8 dword_507DE8[40];
// End of its data definitions.

// match: _off_430B40 @ 0x00430B40

// match: _sub_250AC0 @ 0x00250AC0
// sp-match: _sub_250AC0 @ 0x001660D0

void *
sub_250AC0(void)
{
    if (!sub_243E20(dword_507DE8))
    {
        return NULL;
    }

    RwaWaveDictAssignID(dword_507DE8, unk_3EDF88, NULL);
    sub_243CD0(dword_507DE8, off_430AB0, 7, off_430B40, 7);

    return dword_507DE8;
}

// match: _sub_250B10 @ 0x00250B10
// sp-match: _sub_250B10 @ 0x00166120
RwBool
sub_250B10(void)
{
    return sub_243EA0(dword_507DE8);
}
