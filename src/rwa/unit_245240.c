/*
 * codfh-match: RenderWare Audio's stream cache interface (0x245240-0x2452A0),
 * a static interface definition registered with its parameter tables and
 * unregistered at close, as the interfaces in unit_2417C0.c are. The
 * database missed the registration (docs/units.md).
 */
#include "rwa.h"
#include "rwaint.h"



extern RwUInt8 unk_5079AC[];        /* the interface */

extern RwBool sub_243E20(void *iface);
extern void RwaWaveDictAssignID(void *iface, const void *uuid, const void *textID);
extern void sub_243CD0(void *iface, void *sets, RwInt32 noSets, void *gets, RwInt32 noGets);
extern RwBool sub_243EA0(void *iface);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _unk_3ED954 @ 0x003ED954
// match: _unk_3ED944 @ 0x003ED944
// match: _unk_3ED934 @ 0x003ED934
// match: _unk_3ED924 @ 0x003ED924
// match: _unk_3ED914 @ 0x003ED914
// match: _unk_3ED904 @ 0x003ED904
// match: _unk_3ED8F4 @ 0x003ED8F4
// match: _unk_3ED8E4 @ 0x003ED8E4
// match: _unk_3ED8D4 @ 0x003ED8D4
// match: _unk_3ED8C4 @ 0x003ED8C4
// match: _unk_3ED8B4 @ 0x003ED8B4
// match: _unk_3ED8A4 @ 0x003ED8A4
// match: _unk_3ED894 @ 0x003ED894
// match: _unk_3ED884 @ 0x003ED884
// match: _unk_3ED874 @ 0x003ED874

// What its data definitions name.
extern void sub_246FB0(void);
extern void sub_246FC0(void);
extern RwUInt8 unk_3ED4EC[];
extern RwUInt8 unk_3ED52C[];
extern RwUInt8 unk_3ED55C[];
extern RwUInt8 unk_3ED56C[];
// Its data definitions (PLAN M5), in the image's address order.
// 0x003ED864
const RwaUUID unk_3ED864 = { 0x8C852CAD, 0x64A1, 0x479A, { 0xB4, 0x45, 0x5E, 0xBB, 0x6D, 0x57, 0xCB, 0x27 } };
// 0x003ED874
const RwaUUID unk_3ED874 = { 0xD977492F, 0x88AC, 0x4433, { 0xB8, 0x74, 0xBC, 0x76, 0xD6, 0x1E, 0x67, 0x21 } };
// 0x003ED884
const RwaUUID unk_3ED884 = { 0x48745DC3, 0x084D, 0x4D52, { 0xA2, 0xB8, 0xAE, 0xA5, 0xEF, 0x2E, 0xDB, 0x3A } };
// 0x003ED894
const RwaUUID unk_3ED894 = { 0x862C4BC4, 0x14B7, 0x406A, { 0xA2, 0x18, 0xDC, 0x97, 0xF6, 0x12, 0x27, 0x98 } };
// 0x003ED8A4
const RwaUUID unk_3ED8A4 = { 0xF28A8B56, 0x8737, 0x4E25, { 0x84, 0xDF, 0xCA, 0x3E, 0x5D, 0x93, 0x62, 0x7B } };
// 0x003ED8B4
const RwaUUID unk_3ED8B4 = { 0x761C441C, 0x1D76, 0x4AC7, { 0xBB, 0x69, 0xE1, 0x9A, 0x24, 0x8A, 0xE7, 0x5D } };
// 0x003ED8C4
const RwaUUID unk_3ED8C4 = { 0x59B3E5B6, 0xD217, 0x47FA, { 0x89, 0xCD, 0x9A, 0xEE, 0xAF, 0x21, 0xB9, 0xCE } };
// 0x003ED8D4
const RwaUUID unk_3ED8D4 = { 0x3EAA3E29, 0x043D, 0x4DA5, { 0xAE, 0xD8, 0xEE, 0xB4, 0xE2, 0xE2, 0x2C, 0x4B } };
// 0x003ED8E4
const RwaUUID unk_3ED8E4 = { 0x37BADCD3, 0x686E, 0x4F95, { 0xB4, 0xF9, 0x7D, 0x91, 0xCC, 0x00, 0xBD, 0x80 } };
// 0x003ED8F4
const RwaUUID unk_3ED8F4 = { 0x7B342036, 0x070E, 0x4FA5, { 0x98, 0xB5, 0xC5, 0xD4, 0x0D, 0x65, 0xC3, 0xC1 } };
// 0x003ED904
const RwaUUID unk_3ED904 = { 0xA36818E9, 0xC1E1, 0x4C12, { 0xB5, 0x91, 0xB6, 0x3B, 0x24, 0xBA, 0xCA, 0x0F } };
// 0x003ED914
const RwaUUID unk_3ED914 = { 0x4F03DA53, 0x7F08, 0x4644, { 0x84, 0xE5, 0x44, 0x23, 0xDA, 0xCE, 0x2D, 0x1B } };
// 0x003ED924
const RwaUUID unk_3ED924 = { 0x205A79BC, 0x1BEA, 0x4573, { 0xA8, 0xA3, 0x68, 0x8D, 0xF7, 0x33, 0x45, 0x03 } };
// 0x003ED934
const RwaUUID unk_3ED934 = { 0xD6C75799, 0x880A, 0x4D14, { 0xB5, 0x5A, 0xDB, 0xE5, 0x26, 0x8B, 0xAC, 0x8F } };
// 0x003ED944
const RwaUUID unk_3ED944 = { 0x31BEED52, 0xBE26, 0x44ED, { 0x83, 0x71, 0x62, 0x01, 0xE7, 0x02, 0xA6, 0x6E } };
// 0x003ED954
const RwaUUID unk_3ED954 = { 0xF578249D, 0xD7C8, 0x488C, { 0x8A, 0xB7, 0xBC, 0x51, 0xAC, 0x40, 0x0E, 0xD3 } };
// 0x0042FA10
void *unk_42FA10[30] =
{
    (void *)&unk_3ED874,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED894,
    0,
    0,
    (void *)&unk_3ED55C,
    (void *)0x1,
    (void *)&unk_3ED8A4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED8B4,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED8F4,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED914,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
};
// 0x0042FA88
void *unk_42FA88[45] =
{
    (void *)&unk_3ED884,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED8C4,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED8D4,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED8E4,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED904,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED924,
    0,
    0,
    (void *)&unk_3ED52C,
    (void *)0x1,
    (void *)&unk_3ED934,
    0,
    0,
    (void *)&unk_3ED4EC,
    (void *)0x1,
    (void *)&unk_3ED944,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
    (void *)&unk_3ED954,
    0,
    0,
    (void *)&unk_3ED56C,
    (void *)0x1,
};
// 0x0042FB3C
void *off_42FB3C[3] =
{
    (void *)sub_246FB0,
    (void *)sub_246FC0,
    0,
};
// 0x005079AC
RwUInt8 unk_5079AC[40];
// End of its data definitions.

// match: _unk_3ED864 @ 0x003ED864


// match: _unk_42FA10 @ 0x0042FA10


// match: _unk_42FA88 @ 0x0042FA88


// match: _off_42FB3C @ 0x0042FB3C

// match: _sub_245240 @ 0x00245240

void *
sub_245240(void)
{
    if (!sub_243E20(unk_5079AC))
    {
        return NULL;
    }

    RwaWaveDictAssignID(unk_5079AC, &unk_3ED864, NULL);
    sub_243CD0(unk_5079AC, unk_42FA10, 6, unk_42FA88, 9);

    return unk_5079AC;
}

// match: _sub_245290 @ 0x00245290
RwBool
sub_245290(void)
{
    return sub_243EA0(unk_5079AC);
}
