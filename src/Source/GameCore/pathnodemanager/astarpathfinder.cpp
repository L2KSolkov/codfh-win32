// Source\GameCore\pathnodemanager\astarpathfinder.cpp: the A* path finder
// (include/game/astarpathfinder.h). The path is the image's own (the
// outcome logs pass it as __FILE__). The unit starts at sub_F5F10: the
// triggered particles end just before it.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/astarpathfinder.h"
#include "types/AIData.h"
#include "types/type_3CE1FC.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/type_4C00E8.h"
#include "types/type_D48D0.h"

struct type_67620;

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D939C
extern const RwReal flt_3D939C = 16.666666f;
// 0x004296D8
RwInt32 dword_4296D8 = 400;
// 0x004296DC
RwReal flt_4296DC = 250000.0f;
// 0x004296E0
RwReal flt_4296E0 = 1000000.0f;
// 0x004296E4
RwReal flt_4296E4 = 1000000.0f;
// 0x004296E8
RwReal flt_4296E8 = 250000.0f;
// 0x004296EC
RwReal flt_4296EC = 3.0f;
// 0x004296F0
RwUInt32 dword_4296F0 = 10;
// 0x004296F4
RwInt32 dword_4296F4 = 66;
// 0x004296F8
RwInt32 dword_4296F8 = 1297519524;
// 0x004BFE18
RwInt32 dword_4BFE18;
// 0x004BFE1C
RwInt32 dword_4BFE1C;
// 0x004BFE20
RwInt32 dword_4BFE20;
// 0x004BFE24
RwInt32 dword_4BFE24;
// 0x004C00C8
RwUInt32 dword_4C00C8;
// 0x004C00CC
RwUInt32 dword_4C00CC;
// 0x004C00D0
type_4C00D0 dword_4C00D0;
// 0x004C00D4
#ifndef CODFH_PLAIN
RwUInt32 dword_4C00D4;
#endif
// 0x004C00D8
#ifndef CODFH_PLAIN
RwUInt32 dword_4C00D8;
#endif
// 0x004C00E8
type_4C00E8 unk_4C00E8;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@3fc00000 @ 0x003CDAFC
// match: __real@41f00000 @ 0x003CDB50
// match: __real@41200000 @ 0x003CDFF4
// match: __real@43160000 @ 0x003CE17C
// match: ??_7type_3CE1FC@@6B@ @ 0x003CE1FC
// match: __real@40800000 @ 0x003CE7F4
// match: __real@40400000 @ 0x003D7118
// match: ?flt_3D939C@@3MB @ 0x003D939C
// match: ??_C@_0BH@HJMONIBO@AStar?5Path?5?$CKNOT?$CK?5Found?$AA@ @ 0x003D93A0
// match: ??_C@_0BA@NNOIGNDO@AStar?5PathFound?$AA@ @ 0x003D93B8
// match: ??_C@_0BA@LADCMLAL@AStar_PathFound?$AA@ @ 0x003D93C8
// match: ??_C@_0CJ@OGOFPNFP@AStar?5PathNotFound?5b?1c?5max?5time?5@ @ 0x003D93D8
// match: ??_C@_0DE@GIAEHLBK@Source?2GameCore?2pathnodemanager?2@ @ 0x003D9404
// match: ??_C@_0ED@IIPONOCI@AStar?5PathNotFound?5b?1c?5max?5conne@ @ 0x003D9438
// match: __ehhandler$?sub_F7620@type_4BFED0@@QAEHPAUtype_F6400@@PAUtype_169D0@@@Z>1>8 @ 0x0041D0C0
// match: __ehhandler$?sub_F7620@type_4BFED0@@QAEHPAUtype_F6400@@PAUtype_169D0@@@Z>1 @ 0x0041D0C8
// match: ?dword_4296D8@@3HA @ 0x004296D8
// match: ?flt_4296DC@@3MA @ 0x004296DC
// match: ?flt_4296E0@@3MA @ 0x004296E0
// match: ?flt_4296E4@@3MA @ 0x004296E4
// match: ?flt_4296E8@@3MA @ 0x004296E8
// match: ?flt_4296EC@@3MA @ 0x004296EC
// match: ?dword_4296F0@@3IA @ 0x004296F0
// match: ?dword_4296F4@@3HA @ 0x004296F4
// match: ?dword_4296F8@@3HA @ 0x004296F8

// match: ?sub_F5F10@@YAXXZ @ 0x000F5F10
// sp-match: ?sub_F5F10@@YAXXZ @ 0x000BB850

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F5F10()
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!dword_4BFE24)
    {
        bp_4 = 0;
        for (bp_8 = 0; bp_8 < 3; bp_8++)
        {
            dword_4BFED0[bp_8].sub_F6510();
            if (bp_4 < 1)
            {
                dword_4BFED0[bp_8].unk_A4 = 2;
            }
            else
            {
                dword_4BFED0[bp_8].unk_A4 = 1;
            }
            bp_4++;
        }
        dword_4BFE28.sub_F6510();
        dword_4BFE28.unk_04 = 1;
        dword_4BFE24 = 1;
        dword_4BFE18 = 4;
        dword_4BFE1C = 4;
        dword_4BFE20 = 10;
        sub_19A750();
    }
}

// match: ?sub_F5FE0@@YAXXZ @ 0x000F5FE0
// sp-match: ?sub_F5FE0@@YAXXZ @ 0x000BB8D0
void sub_F5FE0()
{
    RwInt32 var_4;

    if (dword_4BFE24)
    {
        for (var_4 = 0; var_4 < 3; var_4++)
        {
            dword_4BFED0[var_4].sub_F65E0();
        }
        dword_4BFE28.sub_F65E0();
    }
}

// match: ?sub_F6030@@YAXXZ @ 0x000F6030
// sp-match: ?sub_F6030@@YAXXZ @ 0x000BB910
void sub_F6030()
{
    RwInt32 var_4;

    if (dword_4BFE24)
    {
        for (var_4 = 0; var_4 < 3; var_4++)
        {
            dword_4BFED0[var_4].sub_F6680();
        }
        dword_4BFE28.sub_F6680();
        sub_19A750();
        dword_4BFE24 = 0;
    }
}

// match: ?sub_F6090@@YAXXZ @ 0x000F6090
// sp-match: ?sub_F6090@@YAXXZ @ 0x000BB950
void sub_F6090()
{
    RwInt32 var_4;

    if (dword_4BFE24)
    {
        for (var_4 = 0; var_4 < 3; var_4++)
        {
            if (!dword_4BFED0[var_4].unk_00)
            {
                dword_4BFED0[var_4].sub_F6FC0();
            }
            dword_4BFED0[var_4].unk_00 = 0;
        }
    }
}

// match: ?sub_F6100@@YAHH@Z @ 0x000F6100
// sp-match: ?sub_F6100@@YAHH@Z @ 0x000BB990
RwInt32 sub_F6100(RwInt32 arg_0)
{
    RwInt32 var_4 = 0;

    if (arg_0 >= 0 && arg_0 < 3)
    {
        var_4 = dword_4BFED0[arg_0].unk_9C;
    }
    return var_4;
}

// match: ?sub_F6130@@YAHH@Z @ 0x000F6130
// sp-match: ?sub_F6130@@YAHH@Z @ 0x000BB9B0
RwInt32 sub_F6130(RwInt32 arg_0)
{
    RwInt32 var_4 = 0;

    if (arg_0 >= 0 && arg_0 < 3)
    {
        var_4 = dword_4BFED0[arg_0].unk_94;
    }
    return var_4;
}

// match: ?sub_F6160@@YAHHI@Z @ 0x000F6160
// sp-match: ?sub_F6160@@YAHHI@Z @ 0x000BB9D0
RwInt32 sub_F6160(RwInt32 arg_0, RwUInt32 arg_4)
{
    RwInt32 var_4 = 0;

    if (arg_0 >= 0 && arg_0 < 3)
    {
        var_4 = dword_4BFED0[arg_0].unk_A4 & arg_4;
    }
    return var_4;
}

// match: ?sub_F61A0@@YAHH@Z @ 0x000F61A0
// sp-match: ?sub_F61A0@@YAHH@Z @ 0x000BB9F0
RwInt32 sub_F61A0(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if (!sub_F6130(var_4) && !sub_F6100(var_4) && sub_F6160(var_4, arg_0))
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_F6200@@YAHH@Z @ 0x000F6200
// sp-match: ?sub_F6200@@YAHH@Z @ 0x000BBA30
RwInt32 sub_F6200(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if ((sub_F6130(var_4) || sub_F6100(var_4)) && dword_4BFED0[var_4].get_unk_A0() == arg_0)
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_F6270@@YAXH@Z @ 0x000F6270
// sp-match: ?sub_F6270@@YAXH@Z @ 0x000BBA80
void sub_F6270(RwInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 3; var_4++)
    {
        if ((sub_F6130(var_4) || sub_F6100(var_4)) && dword_4BFED0[var_4].get_unk_A0() == arg_0)
        {
            dword_4BFED0[var_4].sub_F6C50();
        }
    }
}

// match: ?sub_F62F0@@YAHPAUtype_169D0@@HIH@Z @ 0x000F62F0
// sp-match: ?sub_F62F0@@YAHPAUtype_169D0@@HIH@Z @ 0x000BBAD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F62F0(type_169D0 *arg_0, RwInt32 arg_4, RwUInt32 arg_8, RwInt32 arg_C)
{
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!unk_4C00E8.unk_64)
    {
        return -1;
    }
    bp_4 = -1;
    if (arg_C)
    {
        dword_4BFE28.unk_04 = 1;
        bp_4 = dword_4BFE28.sub_F6DE0(arg_0, dword_4BFE20);
    }
    else
    {
        for (bp_8 = 0; bp_8 < 3; bp_8++)
        {
            if (!dword_4BFED0[bp_8].get_unk_94() && !dword_4BFED0[bp_8].get_unk_9C() &&
                (dword_4BFED0[bp_8].unk_A4 & arg_8))
            {
                break;
            }
        }
        if (bp_8 != 3)
        {
            dword_4BFED0[bp_8].unk_A0 = arg_4;
            slot_C = arg_8 == 2 ? dword_4BFE1C : dword_4BFE18;
            bp_4 = dword_4BFED0[bp_8].sub_F6DE0(arg_0, slot_C);
        }
    }
    return bp_4;
}

// match: ?sub_F6400@type_4BFED0@@QAEPAUtype_F6400@@XZ @ 0x000F6400
// sp-match: ?sub_F6400@type_4BFED0@@QAEPAUtype_F6400@@XZ @ 0x000BBB80
type_F6400 *type_4BFED0::sub_F6400()
{
    if (unk_88 >= 0x400)
    {
        return 0;
    }
    return &unk_84[unk_88++];
}

// match: ?sub_F6450@type_4BFED0@@QAEPAUtype_F6400@@H@Z @ 0x000F6450
// sp-match: ?sub_F6450@type_4BFED0@@QAEPAUtype_F6400@@H@Z @ 0x000BBBB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_F6400 *type_4BFED0::sub_F6450(RwInt32 arg_0)
{
    type_F6400 **bp_8 = &unk_80[arg_0 & 0x3FF];
    type_F6400 *bp_4 = 0;

    if (*bp_8)
    {
        bp_4 = sub_F6400();
        bp_4->unk_28 = *bp_8;
        *bp_8 = bp_4;
    }
    else
    {
        bp_4 = sub_F6400();
        *bp_8 = bp_4;
    }
    bp_4->unk_24 = 0;
    bp_4->unk_20 = 0;
    bp_4->unk_1C = 0;
    bp_4->unk_28 = 0;
    return bp_4;
}

// match: ??0type_4BFED0@@QAE@XZ @ 0x000F64F0
// sp-match: ??0type_4BFED0@@QAE@XZ @ 0x000BC0C0
type_4BFED0::type_4BFED0()
{
}

// match: ?sub_F6510@type_4BFED0@@QAEXXZ @ 0x000F6510
// sp-match: ?sub_F6510@type_4BFED0@@QAEXXZ @ 0x000BC4D0
void type_4BFED0::sub_F6510()
{
    unk_80 = (type_F6400 **)RWSMalloc(0x1000, 0x34254); // not an address: an allocation tag
    memset(unk_80, 0, 0x1000);
    unk_84 = (type_F6400 *)RWSMalloc(0xB000, 0x34254); // not an address: an allocation tag
    memset(unk_84, 0, 0xB000);
    unk_88 = 0;
    unk_9C = 0;
    unk_04 = 0;
    unk_A0 = 0;
    unk_74 = 0;
    unk_78 = 0;
    unk_7C = 0;
    sub_F6600();
}

// match: ?sub_F65E0@type_4BFED0@@QAEXXZ @ 0x000F65E0
// sp-match: ?sub_F65E0@type_4BFED0@@QAEXXZ @ 0x000BC540
void type_4BFED0::sub_F65E0()
{
    sub_F6600();
    unk_9C = 0;
}

// match: ?sub_F6600@type_4BFED0@@QAEXXZ @ 0x000F6600
// sp-match: ?sub_F6600@type_4BFED0@@QAEXXZ @ 0x000BC0D0
void type_4BFED0::sub_F6600()
{
    sub_F6700();
    unk_64 = 0;
    unk_68 = 0;
    unk_6C = 0;
    unk_70 = 0;
    unk_8C = 0;
    unk_90 = 0;
    unk_94 = 0;
    unk_98 = 0;
    unk_A0 = 0;
}

// match: ?sub_F6680@type_4BFED0@@QAEXXZ @ 0x000F6680
// sp-match: ?sub_F6680@type_4BFED0@@QAEXXZ @ 0x000BC110
void type_4BFED0::sub_F6680()
{
    sub_F6600();
    unk_9C = 0;
    if (unk_80)
    {
        operator delete(unk_80);
        unk_80 = 0;
    }
    if (unk_84)
    {
        operator delete(unk_84);
        unk_84 = 0;
    }
}

// match: ?sub_F6700@type_4BFED0@@QAEXXZ @ 0x000F6700
// sp-match: ?sub_F6700@type_4BFED0@@QAEXXZ @ 0x000BBC10
void type_4BFED0::sub_F6700()
{
    unk_74 = 0;
    unk_7C = 0;
    unk_78 = 0;
    unk_88 = 0;
    memset(unk_80, 0, 0x1000);
}

// The squared distance between two nodes' points.
#define NODE_DIST2(a, b)                                                    \
    (((a)->unk_10.x - (b)->unk_10.x) * ((a)->unk_10.x - (b)->unk_10.x) +    \
     ((a)->unk_10.y - (b)->unk_10.y) * ((a)->unk_10.y - (b)->unk_10.y) +    \
     ((a)->unk_10.z - (b)->unk_10.z) * ((a)->unk_10.z - (b)->unk_10.z))

// match: ?sub_F6750@@YAMPAUtype_F6400@@PAUtype_F8350@@HHPAUtype_169D0@@PAM@Z @ 0x000F6750
// sp-match: ?sub_F6750@@YAMPAUtype_F6400@@PAUtype_F8350@@HHPAUtype_169D0@@PAM@Z @ 0x000BBC40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_F6750(type_F6400 *arg_0, type_F8350 *arg_4, RwInt32 arg_8, RwInt32 arg_C, type_169D0 *arg_10,
                 RwReal *arg_14)
{
    RwReal bp_8;
    type_F8350 *bp_4;

    bp_4 = arg_0->unk_08;
    bp_8 = NODE_DIST2(bp_4, arg_4) + arg_0->unk_0C;
    if (arg_8 == arg_C)
    {
        return bp_8;
    }
    if (arg_4->unk_08 > dword_4B87C8)
    {
        bp_8 *= 4.0f;
    }
    if (arg_4->unk_00_2)
    {
        bp_8 *= 30.0f;
    }
    if (arg_4->unk_00_4)
    {
        bp_8 *= 1.5f;
    }
    if (arg_4->unk_00_w & 0x42)
    {
        bp_8 *= 4.0f;
    }
    return bp_8;
}

// match: ?sub_F6840@@YAMPAUtype_F6400@@PAUtype_F8350@@HHPAUtype_169D0@@PAM@Z @ 0x000F6840
// sp-match: ?sub_F6840@@YAMPAUtype_F6400@@PAUtype_F8350@@HHPAUtype_169D0@@PAM@Z @ 0x000BBCC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_F6840(type_F6400 *arg_0, type_F8350 *arg_4, RwInt32 arg_8, RwInt32 arg_C, type_169D0 *arg_10,
                 RwReal *arg_14)
{
    AIData *l1C;
    RwV3d m_18;
    type_3D3548 *slot_C;
    RwReal bp_8;
    RwReal bp_4;

    bp_8 = sub_F6750(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
    l1C = ((type_D48D0 *)&arg_10->unk_00)->sub_D4910()->vf_120();
    slot_C = l1C->unk_1374.sub_D4910();
    if (slot_C)
    {
        RwV3dSub(&m_18, slot_C->sub_CD550(), ((type_D48D0 *)&arg_10->unk_00)->sub_D4910()->sub_CD550());
        bp_4 = RwV3dDotProduct(&m_18, &m_18);
        if (bp_4 < flt_4296DC)
        {
            bp_8 *= 10.0f;
        }
        else if (bp_4 < flt_4296E0)
        {
            bp_8 *= 3.0f;
        }
    }
    return bp_8;
}

// match: ?sub_F6970@@YAMPAUtype_F6400@@PAUtype_F8350@@HHPAUtype_169D0@@PAM@Z @ 0x000F6970
// sp-match: ?sub_F6970@@YAMPAUtype_F6400@@PAUtype_F8350@@HHPAUtype_169D0@@PAM@Z @ 0x000BBDE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_F6970(type_F6400 *arg_0, type_F8350 *arg_4, RwInt32 arg_8, RwInt32 arg_C, type_169D0 *arg_10,
                 RwReal *arg_14)
{
    AIData *m_18;
    type_3D3548 *ebp_14;
    RwReal lv_10;
    RwReal slot_C;
    RwInt32 bp_8;
    type_F8350 *bp_4;

    bp_8 = 0x42;
    bp_4 = arg_0->unk_08;
    lv_10 = NODE_DIST2(bp_4, arg_4);
    slot_C = lv_10 + arg_0->unk_0C;
    *arg_14 = lv_10 + arg_0->unk_10;
    if (arg_4->unk_00_w & bp_8)
    {
        ebp_14 = ((type_D48D0 *)&arg_10->unk_00)->sub_D4910();
        if (ebp_14 && lv_10 < flt_4296E8)
        {
            m_18 = ebp_14->vf_120();
            if (m_18->sub_27550(arg_4, arg_10->unk_08, arg_10->unk_04) && *arg_14 > flt_4296E4)
            {
                *arg_14 = 0.0f;
            }
        }
    }
    if (!(arg_4->unk_00_w & bp_8) && *arg_14 > flt_4296E4 && arg_0->unk_10 > 1.0f)
    {
        slot_C *= flt_4296EC;
    }
    if (arg_8 != arg_C)
    {
        return slot_C;
    }
    if (arg_4->unk_08 > dword_4B87C8 || arg_4->unk_00_2)
    {
        slot_C *= 30.0f;
    }
    if (arg_4->unk_00_4)
    {
        slot_C *= 1.5f;
    }
    return slot_C;
}

// match: ?sub_F6B00@@YAMPAUtype_F8350@@H0H@Z @ 0x000F6B00
// sp-match: ?sub_F6B00@@YAMPAUtype_F8350@@H0H@Z @ 0x000BBF00
RwReal sub_F6B00(type_F8350 *arg_0, RwInt32 arg_4, type_F8350 *arg_8, RwInt32 arg_C)
{
    RwReal var_4 = NODE_DIST2(arg_0, arg_8);

    if (arg_4 == arg_C)
    {
        return var_4;
    }
    return var_4;
}

// match: ?sub_F6B70@@YAHPAUtype_F8350@@PAUtype_169D0@@@Z @ 0x000F6B70
// sp-match: ?sub_F6B70@@YAHPAUtype_F8350@@PAUtype_169D0@@@Z @ 0x000BBF40
RwInt32 sub_F6B70(type_F8350 *arg_0, type_169D0 *arg_4)
{
    return arg_0->unk_00_4;
}

// match: ?sub_F6B80@@YAHPAUtype_F8350@@PAUtype_169D0@@@Z @ 0x000F6B80
// sp-match: ?sub_F6B80@@YAHPAUtype_F8350@@PAUtype_169D0@@@Z @ 0x000BBF50
RwInt32 sub_F6B80(type_F8350 *arg_0, type_169D0 *arg_4)
{
    if (arg_0->unk_00_2)
    {
        return 0;
    }
    return sub_F6B70(arg_0, arg_4);
}

// match: ?sub_F6BB0@@YAP6AMPAUtype_F6400@@PAUtype_F8350@@HHPAUtype_169D0@@PAM@ZH@Z @ 0x000F6BB0
// sp-match: ?sub_F6BB0@@YAP6AMPAUtype_F6400@@PAUtype_F8350@@HHPAUtype_169D0@@PAM@ZH@Z @ 0x000BBF70
type_169D0_cost sub_F6BB0(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        return sub_F6750;
    case 1:
        return sub_F6840;
    case 2:
        return sub_F6970;
    }
    return 0;
}

// match: ?sub_F6BF0@@YAP6AMPAUtype_F8350@@H0H@ZH@Z @ 0x000F6BF0
// sp-match: ?sub_F6BF0@@YAP6AMPAUtype_F8350@@H0H@ZH@Z @ 0x000BBFA0
type_169D0_heuristic sub_F6BF0(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        return sub_F6B00;
    }
    return 0;
}

// match: ?sub_F6C10@@YAP6AHPAUtype_F8350@@PAUtype_169D0@@@ZH@Z @ 0x000F6C10
// sp-match: ?sub_F6C10@@YAP6AHPAUtype_F8350@@PAUtype_169D0@@@ZH@Z @ 0x000BBFC0
type_169D0_filter sub_F6C10(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        return 0;
    case 1:
        return sub_F6B70;
    case 2:
        return sub_F6B80;
    }
    return 0;
}

// match: ?sub_F6C50@type_4BFED0@@QAEXXZ @ 0x000F6C50
// sp-match: ?sub_F6C50@type_4BFED0@@QAEXXZ @ 0x000BBFE0
void type_4BFED0::sub_F6C50()
{
    unk_94 = 0;
    unk_A0 = 0;
    sub_F6700();
}

// match: ?sub_F6C80@type_4BFED0@@QAEXPAUtype_F6400@@@Z @ 0x000F6C80
// sp-match: ?sub_F6C80@type_4BFED0@@QAEXPAUtype_F6400@@@Z @ 0x000BC000
void type_4BFED0::sub_F6C80(type_F6400 *arg_0)
{
    arg_0->unk_00 &= ~2;
    arg_0->unk_00 |= 1;
    if (!unk_78)
    {
        unk_78 = arg_0;
        unk_78->unk_1C = 0;
        unk_78->unk_20 = 0;
    }
    else if (arg_0->unk_18 > unk_78->unk_18)
    {
        arg_0->unk_20 = unk_78;
        arg_0->unk_1C = unk_78->unk_1C;
        unk_78->unk_1C = arg_0;
        if (arg_0->unk_1C)
        {
            arg_0->unk_1C->unk_20 = arg_0;
        }
    }
    else
    {
        arg_0->unk_20 = 0;
        arg_0->unk_1C = unk_78;
        unk_78->unk_20 = arg_0;
        unk_78 = arg_0;
    }
}

// match: ?sub_F6D60@type_4BFED0@@QAEXPAUtype_F6400@@@Z @ 0x000F6D60
// sp-match: ?sub_F6D60@type_4BFED0@@QAEXPAUtype_F6400@@@Z @ 0x000BC070
void type_4BFED0::sub_F6D60(type_F6400 *arg_0)
{
    type_F6400 *var_4;

    var_4 = arg_0->unk_20;
    if (var_4)
    {
        var_4->unk_1C = arg_0->unk_1C;
    }
    var_4 = arg_0->unk_1C;
    if (var_4)
    {
        var_4->unk_20 = arg_0->unk_20;
    }
    if (arg_0 == unk_78)
    {
        unk_78 = arg_0->unk_1C;
    }
    arg_0->unk_1C = 0;
    arg_0->unk_20 = 0;
    arg_0->unk_00 &= ~1;
}

// match: ?sub_F6DE0@type_4BFED0@@QAEHPAUtype_169D0@@H@Z @ 0x000F6DE0
// sp-match: ?sub_F6DE0@type_4BFED0@@QAEHPAUtype_169D0@@H@Z @ 0x000BC8D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4BFED0::sub_F6DE0(type_169D0 *arg_0, RwInt32 arg_4)
{
    type_4C00E8 *slot_C;
    RwInt32 bp_8;
    type_F6400 *bp_4;

    unk_5C = arg_4;
    dword_4C00D4++;
    if (dword_4C00D4 > dword_4C00D8)
    {
        dword_4C00D8 = dword_4C00D4;
    }
    bp_8 = -1;
    arg_0->unk_28 = -1;
    arg_0->unk_2C = 0;
    unk_64 = arg_0->unk_38;
    unk_68 = arg_0->unk_40;
    unk_6C = arg_0->unk_34;
    unk_70 = arg_0->unk_3C;
    sub_F6700();
    unk_8C = 0;
    unk_90 = 0;
    unk_94 = 1;
    unk_60 = 0;
    bp_4 = sub_F6450(arg_0->unk_38);
    if (bp_4)
    {
        sub_F6C80(bp_4);
        unk_8C++;
        slot_C = &unk_4C00E8;
        bp_4->unk_08 = slot_C->unk_2C[arg_0->unk_38];
        bp_4->unk_04 = arg_0->unk_38;
        bp_4->unk_00 |= 1;
        bp_4->unk_00 &= ~2;
        bp_4->unk_0C = 0.0f;
        bp_4->unk_10 = 0.0f;
        bp_4->unk_14 = arg_0->unk_14(bp_4->unk_08, arg_0->unk_38, unk_70, unk_68);
        bp_4->unk_18 = bp_4->unk_0C + bp_4->unk_14 + flt_4296EC * bp_4->unk_10;
        unk_58 = arg_0;
        unk_0C = *arg_0;
        unk_60 = 0;
        bp_8 = sub_F6FC0();
    }
    return bp_8;
}

// match: ?sub_F6FC0@type_4BFED0@@QAEHXZ @ 0x000F6FC0
// sp-match: ?sub_F6FC0@type_4BFED0@@QAEHXZ @ 0x000BC640
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4BFED0::sub_F6FC0()
{
    type_F6400 *l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    type_3D3548 *lv_10;
    RwInt32 slot_C;
    type_3D3548 *bp_8;
    RwInt32 bp_4;

    unk_00 = 1;
    if (!unk_94)
    {
        return 0;
    }
    unk_08 = 0;
    bp_4 = 0;
    while (!bp_4)
    {
        bp_4 = sub_F7470(&unk_0C);
        if (bp_4 < 0)
        {
            bp_4 = 0;
            break;
        }
    }
    unk_60++;
    if (unk_60 > dword_4296F0)
    {
        bp_8 = ((type_D48D0 *)&unk_58->unk_00)->sub_D4910();
#line 909 "Source\\GameCore\\pathnodemanager\\astarpathfinder.cpp"
        sub_F7B90(bp_8, unk_A0, unk_58, "AStar PathNotFound b/c max time reached!", __FILE__, __LINE__);
        if (!bp_4)
        {
            bp_4 = -1;
        }
    }
    if (bp_4 == 1 && unk_60 > dword_4C00C8)
    {
        dword_4C00C8 = unk_60;
    }
    else if (bp_4 == -1 && unk_60 > dword_4C00CC)
    {
        dword_4C00CC = unk_60;
    }
    if (bp_4)
    {
        unk_58->unk_28 = bp_4;
        slot_C = unk_7C && unk_58->unk_24 ? 1 : 0;
        if (slot_C)
        {
            lv_10 = ((type_D48D0 *)&unk_58->unk_00)->sub_D4910();
            ebp_14 = 0;
            switch (unk_58->unk_1C)
            {
            case 0:
            case 4:
            case 5:
            case 6:
                if (bp_4 == 1)
                {
                    ebp_14 = 1;
                }
                break;
            case 1:
                if (bp_4 == -1)
                {
                    ebp_14 = 1;
                }
                break;
            case 2:
                ebp_14 = 1;
                break;
            case 3:
                ebp_14 = 0;
                break;
            }
            if (ebp_14)
            {
                m_18 = 0;
                l1C = unk_7C;
                while (l1C)
                {
                    unk_58->unk_24[m_18] = l1C->unk_04;
                    m_18++;
                    l1C = l1C->unk_24;
                    if (m_18 >= unk_58->unk_20)
                    {
                        bp_4 = -1;
                        break;
                    }
                }
                unk_58->unk_2C = m_18;
            }
            switch (unk_58->unk_1C)
            {
            case 0:
                if (bp_4 == -1)
                {
                    unk_58->unk_2C = 0;
                }
                break;
            case 1:
                if (bp_4 == 1)
                {
                    unk_58->unk_2C = 0;
                }
                break;
            case 4:
                if (bp_4 == 1)
                {
                    if (lv_10)
                    {
                        lv_10->vf_120()->sub_23530(unk_58->unk_3C);
                    }
                }
                else
                {
                    unk_58->unk_2C = 0;
                }
                break;
            case 5:
                if (bp_4 == 1)
                {
                    if (lv_10)
                    {
                        type_3DAFC8 *var_24 = lv_10->vf_008();
                        AIData *var_20 = var_24->vf_120();

                        var_20->sub_23550(0);
                        if ((var_20->unk_49C >> 22) & 1)
                        {
                            var_20->sub_23230();
                        }
                    }
                }
                else
                {
                    unk_58->unk_2C = 0;
                }
                break;
            case 6:
                if (bp_4 == 1)
                {
                    if (lv_10)
                    {
                        type_3DAFC8 *var_2C = lv_10->vf_008();
                        AIData *var_28 = var_2C->vf_120();

                        var_28->sub_23530(unk_58->unk_3C);
                        var_28->sub_23320();
                    }
                }
                else
                {
                    unk_58->unk_2C = 0;
                }
            }
            if (lv_10)
            {
                if (unk_58->unk_44 && bp_4 == 1 && unk_58->unk_2C > 0)
                {
                    sub_6B5F0("AStar_PathFound", (type_67620 *)lv_10->vf_098(), 0, 0, 0, 0, true, false);
#line 1099 "Source\\GameCore\\pathnodemanager\\astarpathfinder.cpp"
                    sub_F7B90(lv_10, unk_A0, unk_58, "AStar PathFound", __FILE__, __LINE__);
                }
                else if (unk_58->unk_48 && bp_4 == -1)
                {
                    sub_6B5F0("AStar_PathNotFound", (type_67620 *)lv_10->vf_098(), 0, 0, 0, 0, true, false);
#line 1104 "Source\\GameCore\\pathnodemanager\\astarpathfinder.cpp"
                    sub_F7B90(lv_10, unk_A0, unk_58, "AStar Path *NOT* Found", __FILE__, __LINE__);
                }
            }
        }
        unk_94 = 0;
        if (!unk_9C)
        {
            unk_A0 = 0;
            sub_F6700();
        }
    }
    return bp_4;
}

// match: ?sub_F7470@type_4BFED0@@QAEHPAUtype_169D0@@@Z @ 0x000F7470
// sp-match: ?sub_F7470@type_4BFED0@@QAEHPAUtype_169D0@@@Z @ 0x000BC560
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4BFED0::sub_F7470(type_169D0 *arg_0)
{
    type_F6400 *ebp_14;
    type_F6400 *lv_10;
    type_F6400 *slot_C;
    type_F6400 *bp_8;
    RwInt32 bp_4;

    bp_4 = -1;
    if (unk_78)
    {
        unk_74 = unk_78;
        unk_78 = unk_74->unk_1C;
        if (unk_78)
        {
            unk_78->unk_20 = 0;
            lv_10 = unk_78;
            slot_C = lv_10;
            lv_10 = lv_10->unk_1C;
            while (lv_10)
            {
                if (lv_10->unk_18 < slot_C->unk_18)
                {
                    slot_C = lv_10;
                }
                lv_10 = lv_10->unk_1C;
            }
            if (slot_C != unk_78)
            {
                ebp_14 = slot_C->unk_20;
                slot_C->unk_20->unk_1C = slot_C->unk_1C;
                if (slot_C->unk_1C)
                {
                    slot_C->unk_1C->unk_20 = ebp_14;
                }
                slot_C->unk_1C = unk_78;
                slot_C->unk_20 = 0;
                unk_78->unk_20 = slot_C;
                unk_78 = slot_C;
            }
        }
        bp_8 = unk_7C;
        unk_7C = unk_74;
        unk_7C->unk_20 = 0;
        unk_7C->unk_1C = bp_8;
        if (bp_8)
        {
            bp_8->unk_20 = unk_7C;
        }
        unk_90++;
        unk_74->unk_00 &= ~1;
        unk_74->unk_00 |= 2;
        if (unk_74->unk_04 == (RwInt16)arg_0->unk_40)
        {
            return 1;
        }
        return sub_F7620(unk_74, arg_0);
    }
    return bp_4;
}

// match: ?sub_F7620@type_4BFED0@@QAEHPAUtype_F6400@@PAUtype_169D0@@@Z @ 0x000F7620
// match: __ehhandler$?sub_F7620@type_4BFED0@@QAEHPAUtype_F6400@@PAUtype_169D0@@@Z-0x8 @ 0x003010F0
// match: __ehhandler$?sub_F7620@type_4BFED0@@QAEHPAUtype_F6400@@PAUtype_169D0@@@Z @ 0x003010F8
// sp-match: ?sub_F7620@type_4BFED0@@QAEHPAUtype_F6400@@PAUtype_169D0@@@Z @ 0x000BC160
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4BFED0::sub_F7620(type_F6400 *arg_0, type_169D0 *arg_4)
{
    type_3D3548 *s70;
    type_F6400 *m_6C;
    type_F6400 *q68;
    type_F6400 *var_64;
    RwReal stk_60;
    RwReal y5C;
    RwInt32 slot_58;
    type_F8350 *l54;
    type_F6400 *loc50;
    type_F8350 *x4C;
    RwInt32 w48;
    type_169D0_cost loc44;
    RwReal fp_40;
    type_169D0_heuristic ebp_3C;
    RwInt32 lcl_38;
    type_F8350 *r34;
    type_169D0_filter lv_30;
    RwUInt32 *fp_2C;
    RwInt32 q28;
    type_4C00E8 *frm_24;

    frm_24 = &unk_4C00E8;
    x4C = arg_0->unk_08;
    loc50 = arg_0->unk_24;
    if (x4C->unk_00_0)
    {
        fp_2C = x4C->unk_2C;
    }
    else
    {
        fp_2C = x4C->unk_1C_links;
    }
    type_3CE1FC var_20(fp_2C);
    lcl_38 = arg_4->unk_40;
    r34 = arg_4->unk_3C;
    lv_30 = arg_4->unk_18;
    loc44 = arg_4->unk_10;
    ebp_3C = arg_4->unk_14;
    w48 = x4C->unk_04 == 6;
    q28 = x4C->unk_04 == 10;
    fp_40 = x4C->unk_10.y;
    while (!var_20.at_end())
    {
        slot_58 = var_20.unk_0C;
        l54 = frm_24->unk_2C[slot_58];
        if (!var_20.unk_10 && !l54->unk_00_7 && (!loc50 || loc50->unk_08 != l54) &&
            (!lv_30 || lv_30(l54, arg_4)))
        {
            if ((l54->unk_04 == 6 && w48) || (l54->unk_04 == 10 && q28) ||
                (RwReal)fabs(l54->unk_10.y - fp_40) < 150.0f)
            {
                stk_60 = 0.0f;
                y5C = loc44(arg_0, l54, slot_58, lcl_38, arg_4, &stk_60);
                var_64 = unk_80[slot_58 & 0x3FF];
                while (var_64)
                {
                    if (var_64->unk_04 == (RwInt16)slot_58)
                    {
                        break;
                    }
                    var_64 = var_64->unk_28;
                }
                if (var_64)
                {
                    if (!(var_64->unk_00 >> 1 & 1) && var_64->unk_0C > y5C)
                    {
                        var_64->unk_0C = y5C;
                        var_64->unk_10 = stk_60;
                        var_64->unk_18 = var_64->unk_0C + var_64->unk_14;
                        var_64->unk_24 = arg_0;
                        if (var_64->unk_00 & 1)
                        {
                            sub_F6D60(var_64);
                            sub_F6C80(var_64);
                        }
                    }
                }
                else
                {
                    q68 = sub_F6450(slot_58);
                    if (q68)
                    {
                        q68->unk_04 = slot_58;
                        q68->unk_08 = l54;
                        q68->unk_24 = arg_0;
                        q68->unk_0C = y5C;
                        q68->unk_10 = stk_60;
                        if (q68->unk_04 == (RwInt16)lcl_38)
                        {
                            m_6C = unk_7C;
                            unk_7C = q68;
                            unk_7C->unk_20 = 0;
                            unk_7C->unk_1C = m_6C;
                            if (m_6C)
                            {
                                m_6C->unk_20 = unk_7C;
                            }
                            unk_90++;
                            q68->unk_00 &= ~1;
                            q68->unk_00 |= 2;
                            q68->unk_14 = 0.0f;
                            q68->unk_18 = q68->unk_0C + q68->unk_14;
                            return 1;
                        }
                        q68->unk_14 = ebp_3C(q68->unk_08, q68->unk_04, r34, lcl_38);
                        q68->unk_18 = q68->unk_0C + q68->unk_14;
                        sub_F6C80(q68);
                        unk_8C++;
                    }
                }
            }
        }
        unk_08++;
        if (unk_08 > dword_4296D8)
        {
            s70 = ((type_D48D0 *)&arg_4->unk_00)->sub_D4910();
            if (s70)
            {
#line 1328 "Source\\GameCore\\pathnodemanager\\astarpathfinder.cpp"
                sub_F7B90(s70, unk_A0, arg_4, "AStar PathNotFound b/c max connections visited per update reached!",
                          __FILE__, __LINE__);
            }
            return -1;
        }
        var_20.sub_F7B00();
    }
    return 0;
}

// match: ?sub_F7B00@type_3CE1FC@@QAEXXZ @ 0x000F7B00
#ifdef CODFH_SP // single player expands it in sub_F7620 (SP 0xBC3F0)
inline
#endif
void type_3CE1FC::sub_F7B00()
{
    if (unk_08)
    {
        unk_04++;
        unk_08 = 0;
        unk_0C = *unk_04 & 0xFFF;
        unk_10 = *unk_04 >> 24 & 1;
    }
    else
    {
        unk_08++;
        unk_0C = *unk_04 >> 12 & 0xFFF;
        unk_10 = *unk_04 >> 25 & 1;
    }
}

#ifdef CODFH_WIN32
extern "C" void port_debug_print(const RwChar *arg_0, ...);
#endif

// match: ?sub_F7B90@type_4BFED0@@QAEXPAUtype_3D3548@@HPAUtype_169D0@@PBD2H@Z @ 0x000F7B90
void type_4BFED0::sub_F7B90(type_3D3548 *arg_0, RwInt32 arg_4, type_169D0 *arg_8, const RwChar *arg_C,
                            const RwChar *arg_10, RwInt32 arg_14)
{
#ifdef CODFH_WIN32
    // The path finder's debug log (the entity, a value, the path, the message, where): the port
    // prints it.
    port_debug_print("%s (entity %p, %d, path %p; %s:%d)", arg_C, arg_0, arg_4, arg_8, arg_10, arg_14);
#endif
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004C00D4: dword_4C00D0 + 0x4
RwUInt32 &dword_4C00D4 = *(RwUInt32 *)((RwUInt8 *)&dword_4C00D0 + 0x4);
// 0x004C00D8: dword_4C00D0 + 0x8
RwUInt32 &dword_4C00D8 = *(RwUInt32 *)((RwUInt8 *)&dword_4C00D0 + 0x8);
#endif
