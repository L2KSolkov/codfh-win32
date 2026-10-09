// The CCESS pool manager: the trackers of the objects that take part and the
// slots that pick among them. The file's original name is not recovered
// (M1), so it is named for its start address.

#include <math.h>

#include "rw/ostypes.h"
#include "rw/rprandom.h"
#include "game/data.h"
#include "types/ccess.h"
#include "types/vec4.h"
#include "types/type_92430.h"
#include "types/type_3D32F8.h"
#include "game/functions.h"
#include "types/type_4E5D30.h"
#include "types/type_4AE70.h"
#include "game/gameloop.h"
#include "rw/rpcollis.h"
#include "types/type_3DAFC8_1DDC.h"
#include "types/AIData.h"
#include "types/type_10F710.h"
#include <xmmintrin.h>
#include "rw/bavector.h"
#include "types/type_3D3548.h"
#include "rws/csystemcommands.h"
#if !defined(CODFH_SP) || CODFH_SP_PART != 2 // single player compiles the rest in another file (src/sp/units/sp_unit_08AB60_2.cpp)

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D50D8
extern const RwReal flt_3D50D8 = 16.666666f;
// 0x00428E80
type_428E80 dword_428E80[13] = {
    { 200, 425, 9.0f, 9.0f, 0, 0 },
    { 140, 145, 4.0f, 4.0f, 1, 0 },
    { 240, 245, 4.0f, 4.0f, 1, 0 },
    { 145, 150, 4.5f, 4.5f, 7, 1 },
    { 245, 250, 4.5f, 4.5f, 8, 0 },
    { 250, 256, 2.0f, 2.7f, 8, 0 },
    { 150, 156, 2.0f, 2.0f, 7, 1 },
    { 111, 200, 15.0f, 10.0f, 1, 0 },
    { 110, 111, 15.0f, 10.0f, 2, 0 },
    { 2, 3, 7.0f, 7.0f, 3, 0 },
    { 3, 4, 5.5f, 5.5f, 6, 0 },
    { 6, 7, 7.0f, 7.0f, 4, 0 },
    { 7, 8, 5.5f, 5.5f, 5, 0 },
};
// 0x00428FB8
type_428E80 dword_428FB8[11] = {
    { 411, 408, 9.0f, 9.0f, 0, 0 },
    { 416, 417, 4.5f, 4.5f, 1, 0 },
    { 417, 419, 3.0f, 3.0f, 1, 0 },
    { 422, 423, 4.5f, 4.5f, 1, 0 },
    { 423, 498, 3.0f, 3.0f, 1, 0 },
    { 406, 408, 15.0f, 10.0f, 1, 0 },
    { 402, 499, 15.0f, 10.0f, 1, 0 },
    { 2, 3, 7.0f, 7.0f, 3, 0 },
    { 3, 5, 5.5f, 5.5f, 6, 0 },
    { 6, 7, 7.0f, 7.0f, 4, 0 },
    { 7, 9, 5.5f, 5.5f, 5, 0 },
};
// 0x004B2078
type_8AEB0 dword_4B2078[5];
// 0x004B20F0
type_8AEB0 dword_4B20F0[5];
// 0x004B2168
type_8AFF0_node *dword_4B2168;
// 0x004B216C
type_8AFF0_node *dword_4B216C;
// 0x004B2170
type_8B4C0_node *dword_4B2170;
// 0x004B2174
CCESSPoolTrigger *dword_4B2174;
// 0x004B2178
RwInt32 dword_4B2178;
// 0x004B217C
RwInt32 dword_4B217C;
// 0x004B2180
RwInt32 dword_4B2180;
// 0x004B2184
RwInt32 dword_4B2184;
// 0x004B21D0
type_4B21D0 dword_4B21D0;
#ifndef CODFH_SP // file-static in single player (unit_08E670)
// 0x004B25A0
RwV3d dword_4B25A0;
// 0x004B25AC
RwReal flt_4B25AC;
#endif
// 0x004B25B0
RwInt32 dword_4B25B0;
// 0x004B25B8
RwInt32 dword_4B25B8;
// 0x004B25BC
RwInt32 dword_4B25BC;
// 0x004B25C0
RwV3d dword_4B25C0[350 * 3];
// 0x004B56F8
RwV3d dword_4B56F8[350];
// 0x004B6760
RwInt32 dword_4B6760;
// 0x004B6764
RwInt32 dword_4B6764;
// 0x004B6768
RwV3d dword_4B6768[3];
// 0x004B678C
RwV3d dword_4B678C[3];
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4B2188;
type_16C2A0 dword_4B21A8;
type_8F300 dword_4B2550;
type_4B2560 dword_4B2560;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D50D8@@3MB @ 0x003D50D8
// match: ??_C@_0BM@FAJHHJMI@m_freeSpecialTriggerTracker?$AA@ @ 0x003D50DC
// match: ??_C@_0BF@GALCKJFO@m_freeTriggerTracker?$AA@ @ 0x003D50F8
// match: .CRT$XCU+0 @ 0x00426EC4
// match: .CRT$XCU+4 @ 0x00426EC8
// match: .CRT$XCU+8 @ 0x00426ECC
// match: .CRT$XCU+12 @ 0x00426ED0
// match: ?dword_428E80@@3PAUtype_428E80@@A @ 0x00428E80
// match: ?dword_428FB8@@3PAUtype_428E80@@A @ 0x00428FB8

// match: _$E2 @ 0x0030A3E0
// match: _$E3 @ 0x0030DEE0
// match: _$E5 @ 0x0030A400
// match: _$E6 @ 0x0030DEF0
// match: _$E8 @ 0x0030A420
// match: _$E9 @ 0x0030DF00
// match: _$E11 @ 0x0030A440
// sp-match: _$E2 @ 0x0021C780
// sp-match: _$E5 @ 0x0021C7A0
// sp-match: _$E8 @ 0x0021C7C0
// sp-match: _$E3 @ 0x0021E310
// sp-match: _$E6 @ 0x0021E320
// sp-match: _$E9 @ 0x0021E330

// Sets the two pools up and resets.
// match: ?sub_8AB60@@YAXXZ @ 0x0008AB60
// sp-match: ?sub_8AB60@@YAXXZ @ 0x0006F8F0
void sub_8AB60()
{
    dword_4B2188.sub_16C2C0(100, 16, "m_freeTriggerTracker", 4, 0);
    dword_4B21A8.sub_16C2C0(25, 16, "m_freeSpecialTriggerTracker", 4, 0);
    sub_8ABA0();
}

// Forgets the lists and the settings and empties the slots.
// match: ?sub_8ABA0@@YAXXZ @ 0x0008ABA0
// sp-match: ?sub_8ABA0@@YAXXZ @ 0x0006F240
void sub_8ABA0()
{
    RwInt32 var_4;

    dword_4B216C = 0;
    dword_4B2168 = 0;
    dword_4B2170 = 0;
    dword_4B2178 = 0;
    dword_4B217C = 0;
    dword_4B2180 = 0;
    dword_4B2184 = 0;
    dword_4B2174 = 0;
    for (var_4 = 0; var_4 < 5; var_4++)
    {
        dword_4B20F0[var_4].unk_00 = 0;
        dword_4B20F0[var_4].unk_0C = 0;
        dword_4B20F0[var_4].unk_04 = 1e37f;
        dword_4B20F0[var_4].unk_08 = 0;
        dword_4B20F0[var_4].unk_10 = var_4;
        dword_4B20F0[var_4].unk_14 = 0;
        dword_4B2078[var_4].unk_00 = 0;
        dword_4B2078[var_4].unk_0C = 0;
        dword_4B2078[var_4].unk_04 = 1e37f;
        dword_4B2078[var_4].unk_08 = 0;
        dword_4B2078[var_4].unk_10 = var_4;
        dword_4B2078[var_4].unk_14 = 1;
    }
}

// match: ?sub_8ACE0@@YAXXZ @ 0x0008ACE0
// sp-match: ?sub_8ACE0@@YAXXZ @ 0x0006F930
void sub_8ACE0()
{
    sub_8AD20();
}

// Frees the trackers and shuts the pools down.
// match: ?sub_8ACF0@@YAXXZ @ 0x0008ACF0
// sp-match: ?sub_8ACF0@@YAXXZ @ 0x0006F940
void sub_8ACF0()
{
    sub_8AD20();
    dword_4B2188.sub_16C4D0(1);
    dword_4B21A8.sub_16C4D0(1);
}

// Frees every tracker and resets.
// match: ?sub_8AD20@@YAXXZ @ 0x0008AD20
// sp-match: ?sub_8AD20@@YAXXZ @ 0x0006F3F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_8AD20()
{
    type_8B4C0_node *var_10;
    type_8B4C0_node *var_C;
    type_8AFF0_node *bp_8;
    type_8AFF0_node *bp_4;

    bp_4 = 0;
    bp_8 = dword_4B2168;
    while (bp_8)
    {
        bp_4 = bp_8->unk_0C;
        dword_4B2188.sub_16C710(bp_8);
        bp_8 = bp_4;
    }
    bp_8 = dword_4B216C;
    bp_4 = 0;
    while (bp_8)
    {
        bp_4 = bp_8->unk_0C;
        dword_4B2188.sub_16C710(bp_8);
        bp_8 = bp_4;
    }
    var_10 = 0;
    var_C = dword_4B2170;
    while (var_C)
    {
        var_10 = var_C->unk_0C;
        dword_4B21A8.sub_16C710(var_C);
        var_C = var_10;
    }
    sub_8ABA0();
}

// A round of arg_0 seconds: clears the trackers' marks and lets each slot
// pick.
// match: ?sub_8ADD0@@YAXM@Z @ 0x0008ADD0
// sp-match: ?sub_8ADD0@@YAXM@Z @ 0x0006FBA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_8ADD0(RwReal arg_0)
{
    RwInt32 var_C;
    type_8AFF0_node *bp_8;
    type_8AFF0_node *bp_4;

    if (!dword_4B2178 || !dword_4B2174)
    {
        return;
    }
    for (bp_4 = dword_4B2168; bp_4; bp_4 = bp_4->unk_0C)
    {
        bp_4->unk_08 = 0;
    }
    for (bp_8 = dword_4B216C; bp_8; bp_8 = bp_8->unk_0C)
    {
        bp_8->unk_08 = 0;
    }
    for (var_C = 0; var_C < 5; var_C++)
    {
        sub_8AEB0(&dword_4B20F0[var_C], dword_4B217C, dword_4B2168, arg_0);
        sub_8AEB0(&dword_4B2078[var_C], dword_4B2180, dword_4B216C, arg_0);
    }
}

// The slot arg_0's round: when its time runs out (and arg_4 trackers are
// there), a new delay, then up to its picks from the list arg_8.
// match: ?sub_8AEB0@@YAXPAUtype_8AEB0@@HPAUtype_8AFF0_node@@M@Z @ 0x0008AEB0
// sp-match: ?sub_8AEB0@@YAXPAUtype_8AEB0@@HPAUtype_8AFF0_node@@M@Z @ 0x0006F960
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_8AEB0(type_8AEB0 *arg_0, RwInt32 arg_4, type_8AFF0_node *arg_8, RwReal arg_C)
{
    RwInt32 var_10;
    RwInt32 var_C;
    type_4B2174_C0 *bp_8;
    RwInt32 bp_4;

    bp_4 = arg_0->unk_10;
    var_C = arg_0->unk_14;
    bp_8 = &dword_4B2174->unk_C0[var_C];
    arg_0->unk_04 += 1.0f;
    arg_0->unk_08 -= arg_C;
    if (arg_0->unk_08 < 0.0f && arg_4 > 0)
    {
        arg_0->unk_08 = 0.0f;
        if (bp_8->unk_28[bp_4])
        {
            arg_0->unk_08 = (RwReal)(RpRandom() % ((RwInt32)bp_8->unk_14[bp_4] + 1));
        }
        else
        {
            arg_0->unk_08 = bp_8->unk_14[bp_4];
        }
        for (var_10 = 0; var_10 < bp_8->unk_3C[bp_4]; var_10++)
        {
            if (arg_0->unk_0C >= bp_8->unk_00[bp_4])
            {
                break;
            }
            if (!sub_8AFF0(bp_4, arg_8, arg_0))
            {
                break;
            }
            arg_0->unk_0C++;
        }
    }
}

// match: ?sub_8AFF0@@YAHHPAUtype_8AFF0_node@@PAUtype_8AEB0@@@Z @ 0x0008AFF0
// sp-match: ?sub_8AFF0@@YAHHPAUtype_8AFF0_node@@PAUtype_8AEB0@@@Z @ 0x0006F460
// The pick of the slot arg_8 (answering the slot kind arg_0) among the
// trackers from arg_4: a random free one with room, or else the one it last
// picked if that has room; takes it (a round's use), marks its child entity
// picked and returns 1, or 0 when there is none or it has no child.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_8AFF0(RwInt32 arg_0, type_8AFF0_node *arg_4, type_8AEB0 *arg_8)
{
    type_3D3548 *o1AC;
    RwUInt32 z1A8;
    type_8AFF0_node *local_1A4;
    type_8AFF0_node *z1A0[100];
    type_8AFF0_node *var_C;
    type_8AFF0_node *bp_8;
    RwInt32 bp_4;

    var_C = 0;
    bp_8 = 0;
    bp_4 = 0;
    for (local_1A4 = arg_4; local_1A4 != 0; local_1A4 = local_1A4->unk_0C)
    {
        if (local_1A4->unk_00->vf_024() != arg_0)
            continue;
        if (local_1A4->unk_08 != 0)
            continue;
        if (local_1A4->unk_00 == arg_8->unk_00)
        {
            var_C = local_1A4;
            continue;
        }
        if (local_1A4->unk_00->vf_00C() > local_1A4->unk_04)
        {
            z1A0[bp_4] = local_1A4;
            bp_4++;
        }
    }
    if (bp_4 == 0)
    {
        if (var_C != 0 && var_C->unk_00->vf_00C() > var_C->unk_04)
            bp_8 = var_C;
    }
    else
    {
        // Keep the inclusive upper-bound/count expression: VC7.1
        // retains the original register load for this divisor.
        z1A8 = RpRandom() % (bp_4 - 1 + 1);
        bp_8 = z1A0[z1A8];
    }
    if (bp_8 != 0)
    {
        o1AC = bp_8->unk_00->vf_020();
        if (o1AC != 0)
        {
            bp_8->unk_04++;
            bp_8->unk_08 = 1;
            arg_8->unk_00 = bp_8->unk_00;
            o1AC->unk_88_8 = 1;
            return 1;
        }
    }
    return 0;
}

// Adds a tracker for arg_0 to its kind's list (none twice); returns it, or
// 0.
// match: ?sub_8B180@@YAPAUtype_8AFF0_node@@PAUtype_712B0@@@Z @ 0x0008B180
// sp-match: ?sub_8B180@@YAPAUtype_8AFF0_node@@PAUtype_712B0@@@Z @ 0x0006F540
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_8AFF0_node *sub_8B180(type_712B0 *arg_0)
{
    type_8AFF0_node *var_10;
    RwInt32 *var_C;
    type_8AFF0_node *bp_8;
    type_8AFF0_node **bp_4;

    if (arg_0->vf_018() == 1)
    {
        bp_4 = &dword_4B2168;
        var_C = &dword_4B217C;
    }
    else if (arg_0->vf_018() == 2)
    {
        bp_4 = &dword_4B216C;
        var_C = &dword_4B2180;
    }
    else
    {
        return 0;
    }
    for (var_10 = *bp_4; var_10; var_10 = var_10->unk_0C)
    {
        if (var_10->unk_00 == arg_0)
        {
            return 0;
        }
    }
    bp_8 = (type_8AFF0_node *)dword_4B2188.sub_16C5A0(0);
    bp_8->unk_00 = arg_0;
    bp_8->unk_04 = 0;
    bp_8->unk_08 = 0;
    bp_8->unk_0C = *bp_4;
    *bp_4 = bp_8;
    (*var_C)++;
    return bp_8;
}

// Removes the tracker of arg_0, and arg_0 from the slots that last picked
// it.
// match: ?sub_8B250@@YAXPAUtype_712B0@@@Z @ 0x0008B250
// sp-match: ?sub_8B250@@YAXPAUtype_712B0@@@Z @ 0x0006F5C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_8B250(type_712B0 *arg_0)
{
    RwInt32 var_18;
    RwInt32 *var_14;
    type_8AFF0_node **lv_10;
    type_8AFF0_node *var_C;
    type_8AFF0_node *bp_8;
    type_8AFF0_node *bp_4;

    if (arg_0->vf_018() == 1)
    {
        lv_10 = &dword_4B2168;
        var_14 = &dword_4B217C;
    }
    else if (arg_0->vf_018() == 2)
    {
        lv_10 = &dword_4B216C;
        var_14 = &dword_4B2180;
    }
    else
    {
        return;
    }
    var_C = *lv_10;
    bp_8 = 0;
    while (var_C)
    {
        bp_4 = var_C->unk_0C;
        if (var_C->unk_00 == arg_0)
        {
            if (bp_8)
            {
                bp_8->unk_0C = var_C->unk_0C;
            }
            else
            {
                *lv_10 = var_C->unk_0C;
            }
            for (var_18 = 0; var_18 < 5; var_18++)
            {
                if (arg_0 == dword_4B20F0[var_18].unk_00)
                {
                    dword_4B20F0[var_18].unk_00 = 0;
                }
                if (arg_0 == dword_4B2078[var_18].unk_00)
                {
                    dword_4B2078[var_18].unk_00 = 0;
                }
            }
            dword_4B2188.sub_16C710(var_C);
            (*var_14)--;
            return;
        }
        bp_8 = var_C;
        var_C = bp_4;
    }
}

// Removes the trackers of the objects answering slot arg_0 (all when it
// is negative) from both lists.
// match: ?sub_8B380@@YAXH@Z @ 0x0008B380
// sp-match: ?sub_8B380@@YAXH@Z @ 0x0006FA30
void sub_8B380(RwInt32 arg_0)
{
    sub_8B3C0(arg_0, &dword_4B2168, &dword_4B217C);
    sub_8B3C0(arg_0, &dword_4B216C, &dword_4B2180);
}

// The same for the list arg_4, counted in arg_8.
// match: ?sub_8B3C0@@YAXHPAPAUtype_8AFF0_node@@PAH@Z @ 0x0008B3C0
// sp-match: ?sub_8B3C0@@YAXHPAPAUtype_8AFF0_node@@PAH@Z @ 0x0006F660
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_8B3C0(RwInt32 arg_0, type_8AFF0_node **arg_4, RwInt32 *arg_8)
{
    RwInt32 var_10;
    type_8AFF0_node *var_C;
    type_8AFF0_node *bp_8;
    type_8AFF0_node *bp_4;

    var_C = *arg_4;
    bp_8 = 0;
    while (var_C)
    {
        bp_4 = var_C->unk_0C;
        if (arg_0 < 0 || var_C->unk_00->vf_024() == arg_0)
        {
            if (bp_8)
            {
                bp_8->unk_0C = var_C->unk_0C;
            }
            else
            {
                *arg_4 = var_C->unk_0C;
            }
            for (var_10 = 0; var_10 < 5; var_10++)
            {
                if (var_C->unk_00 == dword_4B20F0[var_10].unk_00)
                {
                    dword_4B20F0[var_10].unk_00 = 0;
                }
                if (var_C->unk_00 == dword_4B2078[var_10].unk_00)
                {
                    dword_4B2078[var_10].unk_00 = 0;
                }
            }
            dword_4B2188.sub_16C710(var_C);
            (*arg_8)--;
        }
        else
        {
            bp_8 = var_C;
        }
        var_C = bp_4;
    }
}

// Adds a special tracker for arg_0, if its slot has room; with arg_4, hands
// back the entity of arg_0 (and gives up without one).
// match: ?sub_8B4C0@@YAPAUtype_8B4C0_node@@PAUtype_712B0@@PAPAUtype_3D3548@@@Z @ 0x0008B4C0
// sp-match: ?sub_8B4C0@@YAPAUtype_8B4C0_node@@PAUtype_712B0@@PAPAUtype_3D3548@@@Z @ 0x0006FA60
type_8B4C0_node *sub_8B4C0(type_712B0 *arg_0, type_3D3548 **arg_4)
{
    type_8B4C0_node *var_4;

    if (!dword_4B2174)
    {
        return 0;
    }
    var_4 = (type_8B4C0_node *)dword_4B21A8.sub_16C5A0(0);
    if (!var_4)
    {
        return 0;
    }
    if (arg_0->vf_018() == 1)
    {
        var_4->unk_00 = arg_0;
        var_4->unk_08 = 0;
        if (arg_0->vf_008() == 0x1F)
        {
            var_4->unk_04 = 2;
        }
        else
        {
            var_4->unk_04 = 0;
        }
        if (dword_4B20F0[var_4->unk_04].unk_0C >= dword_4B2174->unk_C0[var_4->unk_08].unk_00[var_4->unk_04])
        {
            dword_4B21A8.sub_16C710(var_4);
            return 0;
        }
        dword_4B20F0[var_4->unk_04].unk_0C++;
    }
    else if (arg_0->vf_018() == 2)
    {
        var_4->unk_00 = arg_0;
        var_4->unk_08 = 1;
        if (arg_0->vf_008() == 0x1F)
        {
            var_4->unk_04 = 2;
        }
        else
        {
            var_4->unk_04 = 0;
        }
        if (dword_4B2078[var_4->unk_04].unk_0C >= dword_4B2174->unk_C0[var_4->unk_08].unk_00[var_4->unk_04])
        {
            dword_4B21A8.sub_16C710(var_4);
            return 0;
        }
        dword_4B2078[var_4->unk_04].unk_0C++;
    }
    var_4->unk_0C = dword_4B2170;
    dword_4B2170 = var_4;
    dword_4B2184++;
    if (arg_4)
    {
        *arg_4 = arg_0->vf_020();
        if (!*arg_4)
        {
            sub_8B6B0(arg_0);
            return 0;
        }
    }
    return var_4;
}

// Removes the special tracker of arg_0.
// match: ?sub_8B6B0@@YAXPAUtype_712B0@@@Z @ 0x0008B6B0
// sp-match: ?sub_8B6B0@@YAXPAUtype_712B0@@@Z @ 0x0006F700
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_8B6B0(type_712B0 *arg_0)
{
    RwInt32 *var_C;
    type_8B4C0_node *bp_8;
    type_8B4C0_node *bp_4;

    var_C = 0;
    if (arg_0->vf_018() == 1)
    {
        var_C = &dword_4B20F0[0].unk_0C;
    }
    else if (arg_0->vf_018() == 2)
    {
        var_C = &dword_4B2078[0].unk_0C;
    }
    else
    {
        return;
    }
    bp_8 = dword_4B2170;
    bp_4 = 0;
    while (bp_8)
    {
        if (bp_8->unk_00 == arg_0)
        {
            if (bp_4)
            {
                bp_4->unk_0C = bp_8->unk_0C;
            }
            else
            {
                dword_4B2170 = bp_8->unk_0C;
            }
            dword_4B21A8.sub_16C710(bp_8);
            dword_4B2184--;
            (*var_C)--;
            return;
        }
        bp_4 = bp_8;
        bp_8 = bp_8->unk_0C;
    }
}

// Takes the settings arg_0 (arg_4 set) or lets them go.
// match: ?sub_8B770@@YAXPAUtype_712B0@@H@Z @ 0x0008B770
// sp-match: ?sub_8B770@@YAXPAUtype_712B0@@H@Z @ 0x0006F780
void sub_8B770(type_712B0 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    if (arg_4 && dword_4B2174 != (CCESSPoolTrigger *)arg_0)
    {
        dword_4B2174 = (CCESSPoolTrigger *)arg_0;
        for (var_4 = 0; var_4 < 5; var_4++)
        {
            if (arg_0 == dword_4B20F0[var_4].unk_00)
            {
                dword_4B20F0[var_4].unk_04 = 1e37f;
            }
            if (arg_0 == dword_4B2078[var_4].unk_00)
            {
                dword_4B2078[var_4].unk_04 = 1e37f;
            }
        }
    }
    else if (!arg_4 && dword_4B2174 == (CCESSPoolTrigger *)arg_0)
    {
        dword_4B2174 = 0;
    }
}

// Sets the most trackers for the index arg_0 of the kind arg_4.
// match: ?sub_8B810@@YAXHHH@Z @ 0x0008B810
// sp-match: ?sub_8B810@@YAXHHH@Z @ 0x0006F870
void sub_8B810(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_4B2174_C0 *var_4;

    var_4 = &dword_4B2174->unk_C0[arg_4];
    var_4->unk_00[arg_0] = arg_8;
}

// The entity arg_0 leaves the CCESS: a picked one frees its place in the
// slot its trigger answers, any other drops its trigger's special tracker.
// match: ?sub_8B840@@YAXPAUtype_3D3548@@@Z @ 0x0008B840
// sp-match: ?sub_8B840@@YAXPAUtype_3D3548@@@Z @ 0x0006F890
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_8B840(type_3D3548 *arg_0)
{
    type_712B0 *var_8;
    RwInt32 l4;

    l4 = -1;
    if (arg_0->unk_88_8)
    {
        if (arg_0->get_unk_34C())
        {
            l4 = arg_0->get_unk_34C()->vf_024();
        }
        if (l4 >= 0)
        {
            if ((arg_0->unk_2C & 7) == 1)
            {
                dword_4B20F0[l4].unk_0C--;
            }
            else if ((arg_0->unk_2C & 7) == 2)
            {
                dword_4B2078[l4].unk_0C--;
            }
        }
    }
    else
    {
        var_8 = arg_0->get_unk_34C();
        sub_8B6B0(var_8);
    }
}

// match: ?sub_8B920@@YA?AUtype_8BEC0@@PAU1@0@Z @ 0x0008B920
// sp-match: ?sub_8B920@@YA?AUtype_8BEC0@@PAU1@0@Z @ 0x0006FC30
type_8BEC0 sub_8B920(type_8BEC0 *arg_0, type_8BEC0 *arg_4)
{
    __declspec(align(16)) type_8BEC0 var_10;

    var_10.unk_00 = (arg_0->unk_04 * arg_4->unk_08) - (arg_0->unk_08 * arg_4->unk_04);
    var_10.unk_04 = (arg_0->unk_08 * arg_4->unk_00) - (arg_0->unk_00 * arg_4->unk_08);
    var_10.unk_08 = (arg_0->unk_00 * arg_4->unk_04) - (arg_0->unk_04 * arg_4->unk_00);
    var_10.unk_0C = arg_0->unk_0C;
    return var_10;
}

// match: ?sub_8B9C0@@YA?AUtype_8BEC0@@PAU1@PAM@Z @ 0x0008B9C0
// sp-match: ?sub_8B9C0@@YA?AUtype_8BEC0@@PAU1@PAM@Z @ 0x0006FCA0
type_8BEC0 sub_8B9C0(type_8BEC0 *arg_0, RwReal *arg_4)
{
    __declspec(align(16)) type_8BEC0 var_10;

    var_10.unk_00 = arg_0->unk_00 * *arg_4;
    var_10.unk_04 = arg_0->unk_04 * *arg_4;
    var_10.unk_08 = arg_0->unk_08 * *arg_4;
    var_10.unk_0C = arg_0->unk_0C;
    return var_10;
}

// match: ?sub_8BA30@@YA?AUtype_8BEC0@@PAMPAU1@@Z @ 0x0008BA30
// sp-match: ?sub_8BA30@@YA?AUtype_8BEC0@@PAMPAU1@@Z @ 0x0006FD00
type_8BEC0 sub_8BA30(RwReal *arg_0, type_8BEC0 *arg_4)
{
    __declspec(align(16)) type_8BEC0 var_10;

    var_10.unk_00 = arg_4->unk_00 * *arg_0;
    var_10.unk_04 = arg_4->unk_04 * *arg_0;
    var_10.unk_08 = arg_4->unk_08 * *arg_0;
    var_10.unk_0C = arg_4->unk_0C;
    return var_10;
}

// match: ?sub_8BAA0@@YA?AUtype_8BEC0@@PAU1@0@Z @ 0x0008BAA0
// sp-match: ?sub_8BAA0@@YA?AUtype_8BEC0@@PAU1@0@Z @ 0x0006FD60
type_8BEC0 sub_8BAA0(type_8BEC0 *arg_0, type_8BEC0 *arg_4)
{
    __declspec(align(16)) type_8BEC0 var_10;

    var_10.unk_00 = arg_0->unk_00 - arg_4->unk_00;
    var_10.unk_04 = arg_0->unk_04 - arg_4->unk_04;
    var_10.unk_08 = arg_0->unk_08 - arg_4->unk_08;
    var_10.unk_0C = 1.0f;
    return var_10;
}

// match: ?sub_8BB10@@YA?AUtype_8BEC0@@PAU1@0@Z @ 0x0008BB10
// sp-match: ?sub_8BB10@@YA?AUtype_8BEC0@@PAU1@0@Z @ 0x0006FDC0
type_8BEC0 sub_8BB10(type_8BEC0 *arg_0, type_8BEC0 *arg_4)
{
    __declspec(align(16)) type_8BEC0 var_10;

    var_10.unk_00 = arg_4->unk_00 + arg_0->unk_00;
    var_10.unk_04 = arg_4->unk_04 + arg_0->unk_04;
    var_10.unk_08 = arg_4->unk_08 + arg_0->unk_08;
    var_10.unk_0C = 1.0f;
    return var_10;
}

// match: ?sub_8BB80@@YA?AUtype_8BEC0@@PAURwV3d@@@Z @ 0x0008BB80
// sp-match: ?sub_8BB80@@YA?AUtype_8BEC0@@PAURwV3d@@@Z @ 0x0006FE20
type_8BEC0 sub_8BB80(RwV3d *arg_0)
{
    __declspec(align(16)) type_8BEC0 var_10;

    var_10.unk_00 = arg_0->x;
    var_10.unk_04 = arg_0->y;
    var_10.unk_08 = arg_0->z;
    var_10.unk_0C = 1.0f;
    return var_10;
}

// match: ?sub_8BBE0@@YA?AUtype_8BEC0@@MMMM@Z @ 0x0008BBE0
// sp-match: ?sub_8BBE0@@YA?AUtype_8BEC0@@MMMM@Z @ 0x0006FE70
type_8BEC0 sub_8BBE0(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    __declspec(align(16)) type_8BEC0 var_10;

    var_10.unk_00 = arg_0;
    var_10.unk_04 = arg_4;
    var_10.unk_08 = arg_8;
    var_10.unk_0C = arg_C;
    return var_10;
}

// match: ?sub_8BC40@@YAMPAUtype_8BEC0@@0@Z @ 0x0008BC40
// sp-match: ?sub_8BC40@@YAMPAUtype_8BEC0@@0@Z @ 0x0006FEC0
RwReal sub_8BC40(type_8BEC0 *arg_0, type_8BEC0 *arg_4)
{
    __declspec(align(16)) RwReal var_10;

    return var_10 = arg_0->unk_00 * arg_4->unk_00 + arg_0->unk_04 * arg_4->unk_04 + arg_0->unk_08 * arg_4->unk_08;
}

// match: ?sub_8BC90@@YA?AUtype_8BFA0@@PAMPAU1@@Z @ 0x0008BC90
// sp-match: ?sub_8BC90@@YA?AUtype_8BFA0@@PAMPAU1@@Z @ 0x0006FEF0
type_8BFA0 sub_8BC90(RwReal *arg_0, type_8BFA0 *arg_4)
{
    __declspec(align(16)) type_8BFA0 var_60;

    var_60.unk_00[0] = sub_8B9C0(&arg_4->unk_00[0], arg_0);
    var_60.unk_00[1] = sub_8B9C0(&arg_4->unk_00[1], arg_0);
    var_60.unk_00[2] = sub_8B9C0(&arg_4->unk_00[2], arg_0);
    var_60.unk_00[3] = sub_8B9C0(&var_60.unk_00[3], arg_0);
    return var_60;
}

// match: ?sub_8BE10@@YA?AUtype_8BEC0@@PAU1@@Z @ 0x0008BE10
// sp-match: ?sub_8BE10@@YA?AUtype_8BEC0@@PAU1@@Z @ 0x0006FFD0
type_8BEC0 sub_8BE10(type_8BEC0 *arg_0)
{
    RwReal var_C;
    __declspec(align(16)) type_8BEC0 var_20;

    var_C = 1.0f / sqrt(arg_0->unk_00 * arg_0->unk_00 + arg_0->unk_04 * arg_0->unk_04 + arg_0->unk_08 * arg_0->unk_08);
    var_20.unk_00 = var_C * arg_0->unk_00;
    var_20.unk_04 = var_C * arg_0->unk_04;
    var_20.unk_08 = var_C * arg_0->unk_08;
    var_20.unk_0C = arg_0->unk_0C;
    return var_20;
}

// match: ?sub_8BEC0@@YA?AUtype_8BEC0@@PAURwMatrixTag@@PAU1@@Z @ 0x0008BEC0
// sp-match: ?sub_8BEC0@@YA?AUtype_8BEC0@@PAURwMatrixTag@@PAU1@@Z @ 0x00070050
type_8BEC0 sub_8BEC0(RwMatrix *arg_0, type_8BEC0 *arg_4)
{
    __declspec(align(16)) type_8BEC0 var_10;

#ifdef CODFH_SP // shape: up and at terms grouped (SP 0x7005F sums at, up, then right)
    var_10.unk_00 = arg_0->right.x * arg_4->unk_00 + (arg_0->up.x * arg_4->unk_04 + arg_0->at.x * arg_4->unk_08) + arg_0->pos.x;
    var_10.unk_04 = arg_0->right.y * arg_4->unk_00 + (arg_0->up.y * arg_4->unk_04 + arg_0->at.y * arg_4->unk_08) + arg_0->pos.y;
    var_10.unk_08 = arg_0->right.z * arg_4->unk_00 + (arg_0->up.z * arg_4->unk_04 + arg_0->at.z * arg_4->unk_08) + arg_0->pos.z;
#else
    var_10.unk_00 = arg_0->right.x * arg_4->unk_00 + arg_0->up.x * arg_4->unk_04 + arg_0->at.x * arg_4->unk_08
                    + arg_0->pos.x;
    var_10.unk_04 = arg_0->right.y * arg_4->unk_00 + arg_0->up.y * arg_4->unk_04 + arg_0->at.y * arg_4->unk_08
                    + arg_0->pos.y;
    var_10.unk_08 = arg_0->right.z * arg_4->unk_00 + arg_0->up.z * arg_4->unk_04 + arg_0->at.z * arg_4->unk_08
                    + arg_0->pos.z;
#endif
    var_10.unk_0C = 0.0f;
    return var_10;
}

#ifdef CODFH_SP // SP 0x700E0
// shape: this reference-bound negation keeps the reciprocal after the matrix argument setup.
static inline RwReal sp_negate_matrix_cofactor(const RwDouble &value)
{
    return -value;
}
#endif

// match: ?sub_8BFA0@@YA?AUtype_8BFA0@@PAURwMatrixTag@@@Z @ 0x0008BFA0
// sp-match: ?sub_8BFA0@@YA?AUtype_8BFA0@@PAURwMatrixTag@@@Z @ 0x000700E0
type_8BFA0 sub_8BFA0(RwMatrix *arg_0)
{
    RwReal var_4;
    __declspec(align(16)) type_8BFA0 var_50;
    RwReal var_54;

    var_4 = (arg_0->up.y * arg_0->at.z - (arg_0->up.z * arg_0->at.y)) * arg_0->right.x
            - (arg_0->right.y * arg_0->at.z - arg_0->right.z * arg_0->at.y) * arg_0->up.x
            + (arg_0->right.y * arg_0->up.z - arg_0->right.z * arg_0->up.y) * arg_0->at.x;
    var_50.unk_00[0].unk_00 = arg_0->up.y * arg_0->at.z - (arg_0->up.z * arg_0->at.y);
#ifdef CODFH_SP // SP 0x700E0
    // shape: the two additional negations cancel without adding x87 operations.
    var_50.unk_00[1].unk_00 = -sp_negate_matrix_cofactor(
        (-(arg_0->up.x * arg_0->at.z - arg_0->up.z * arg_0->at.x)));
#else // MP 0x8BFA0
    var_50.unk_00[1].unk_00 = -(arg_0->up.x * arg_0->at.z - arg_0->up.z * arg_0->at.x);
#endif
    var_50.unk_00[2].unk_00 = arg_0->up.x * arg_0->at.y - arg_0->up.y * arg_0->at.x;
    var_50.unk_00[3].unk_00 = 0.0f;
    var_50.unk_00[0].unk_04 = -(arg_0->right.y * arg_0->at.z - arg_0->right.z * arg_0->at.y);
    var_50.unk_00[1].unk_04 = arg_0->right.x * arg_0->at.z - arg_0->right.z * arg_0->at.x;
    var_50.unk_00[2].unk_04 = -(arg_0->right.x * arg_0->at.y - arg_0->right.y * arg_0->at.x);
    var_50.unk_00[3].unk_00 = 0.0f;
    var_50.unk_00[0].unk_08 = arg_0->right.y * arg_0->up.z - arg_0->right.z * arg_0->up.y;
    var_50.unk_00[1].unk_08 = -(arg_0->right.x * arg_0->up.z - arg_0->right.z * arg_0->up.x);
    var_50.unk_00[2].unk_08 = arg_0->right.x * arg_0->up.y - arg_0->right.y * arg_0->up.x;
    var_50.unk_00[3].unk_00 = 0.0f;
    var_50.unk_00[0].unk_0C = 0.0f;
    var_50.unk_00[1].unk_0C = 0.0f;
    var_50.unk_00[2].unk_0C = 0.0f;
    var_50.unk_00[3].unk_0C = 1.0f;
    var_54 = 1.0f / var_4;
    var_50 = sub_8BC90(&var_54, &var_50);
#ifdef CODFH_SP // SP 0x700E0
    // shape: equivalent branches and a separate result preserve the image's x87
    // and return-copy order. The compiled code contains no branch here.
    {
        RwDouble sum = var_50.unk_00[2].unk_00 * arg_0->pos.z;
        if (arg_0 != 0)
        {
            sum += (const RwDouble &)(var_50.unk_00[0].unk_00 * arg_0->pos.x);
        }
        else
        {
            sum += var_50.unk_00[0].unk_00 * arg_0->pos.x;
        }
        RwReal result = sum + (var_50.unk_00[1].unk_00 * arg_0->pos.y);
        var_50.unk_00[3].unk_00 = -result;
    }
#else // MP 0x8BFA0
    var_50.unk_00[3].unk_00 = -(var_50.unk_00[0].unk_00 * arg_0->pos.x + var_50.unk_00[1].unk_00 * arg_0->pos.y
                                + (var_50.unk_00[2].unk_00 * arg_0->pos.z));
#endif
    var_50.unk_00[3].unk_04 = -(var_50.unk_00[0].unk_04 * arg_0->pos.x + var_50.unk_00[1].unk_04 * arg_0->pos.y
                                + (var_50.unk_00[2].unk_04 * arg_0->pos.z));
    var_50.unk_00[3].unk_08 = -(var_50.unk_00[0].unk_08 * arg_0->pos.x + var_50.unk_00[1].unk_08 * arg_0->pos.y
                                + (var_50.unk_00[2].unk_08 * arg_0->pos.z));
    var_50.unk_00[3].unk_0C = 1.0f;
    return var_50;
}

// match: ?sub_8C230@@YAXPAUtype_8BEC0@@PAURwMatrixTag@@0@Z @ 0x0008C230
// sp-match: ?sub_8C230@@YAXPAUtype_8BEC0@@PAURwMatrixTag@@0@Z @ 0x00070280
void sub_8C230(type_8BEC0 *arg_0, RwMatrix *arg_4, type_8BEC0 *arg_8)
{
    RwInt32 var_4;

    arg_8[0].unk_00 = arg_0[0].unk_00;
    arg_8[0].unk_04 = arg_0[0].unk_04;
    arg_8[0].unk_08 = arg_0[0].unk_08;
    arg_8[0].unk_0C = 1.0f;
    arg_8[1].unk_00 = arg_0[1].unk_00;
    arg_8[1].unk_04 = arg_0[0].unk_04;
    arg_8[1].unk_08 = arg_0[0].unk_08;
    arg_8[1].unk_0C = 1.0f;
    arg_8[2].unk_00 = arg_0[0].unk_00;
    arg_8[2].unk_04 = arg_0[1].unk_04;
    arg_8[2].unk_08 = arg_0[0].unk_08;
    arg_8[2].unk_0C = 1.0f;
    arg_8[3].unk_00 = arg_0[0].unk_00;
    arg_8[3].unk_04 = arg_0[0].unk_04;
    arg_8[3].unk_08 = arg_0[1].unk_08;
    arg_8[3].unk_0C = 1.0f;
    arg_8[4].unk_00 = arg_0[1].unk_00;
    arg_8[4].unk_04 = arg_0[1].unk_04;
    arg_8[4].unk_08 = arg_0[0].unk_08;
    arg_8[4].unk_0C = 1.0f;
    arg_8[5].unk_00 = arg_0[1].unk_00;
    arg_8[5].unk_04 = arg_0[0].unk_04;
    arg_8[5].unk_08 = arg_0[1].unk_08;
    arg_8[5].unk_0C = 1.0f;
    arg_8[6].unk_00 = arg_0[0].unk_00;
    arg_8[6].unk_04 = arg_0[1].unk_04;
    arg_8[6].unk_08 = arg_0[1].unk_08;
    arg_8[6].unk_0C = 1.0f;
    arg_8[7].unk_00 = arg_0[1].unk_00;
    arg_8[7].unk_04 = arg_0[1].unk_04;
    arg_8[7].unk_08 = arg_0[1].unk_08;
    arg_8[7].unk_0C = 1.0f;
    for (var_4 = 0; var_4 < 8; var_4++)
    {
        arg_8[var_4] = sub_8BEC0(arg_4, &arg_8[var_4]);
    }
}

// match: ?sub_8C410@@YA?AUtype_8C410@@PAURwMatrixTag@@PAUtype_8BEC0@@@Z @ 0x0008C410
// sp-match: ?sub_8C410@@YA?AUtype_8C410@@PAURwMatrixTag@@PAUtype_8BEC0@@@Z @ 0x00070380
type_8C410 sub_8C410(RwMatrix *arg_0, type_8BEC0 *arg_4)
{
    type_8BEC0 var_80[8];
    __declspec(align(16)) type_8C410 var_C0;
    RwInt32 var_E4;

    sub_8C230(arg_4, arg_0, var_80);
    var_C0.unk_00 = sub_8BBE0(1e9f, 1e9f, 1e9f, 1.0f);
    var_C0.unk_10 = sub_8BBE0(-1e9f, -1e9f, -1e9f, 1.0f);
    for (var_E4 = 0; var_E4 < 8; var_E4++)
    {
        if (var_C0.unk_00.unk_00 > var_80[var_E4].unk_00)
        {
            var_C0.unk_00.unk_00 = var_80[var_E4].unk_00;
        }
        if (var_C0.unk_00.unk_04 > var_80[var_E4].unk_04)
        {
            var_C0.unk_00.unk_04 = var_80[var_E4].unk_04;
        }
        if (var_C0.unk_00.unk_08 > var_80[var_E4].unk_08)
        {
            var_C0.unk_00.unk_08 = var_80[var_E4].unk_08;
        }
        if (var_C0.unk_10.unk_00 < var_80[var_E4].unk_00)
        {
            var_C0.unk_10.unk_00 = var_80[var_E4].unk_00;
        }
        if (var_C0.unk_10.unk_04 < var_80[var_E4].unk_04)
        {
            var_C0.unk_10.unk_04 = var_80[var_E4].unk_04;
        }
        if (var_C0.unk_10.unk_08 < var_80[var_E4].unk_08)
        {
            var_C0.unk_10.unk_08 = var_80[var_E4].unk_08;
        }
    }
    return var_C0;
}

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART != 1 // single player: sp_unit_08AB60_2.cpp, the second file

// match: ?sub_8C690@@YAXHPAURpHAnimHierarchy@@@Z @ 0x0008C690
// sp-match: ?sub_8C690@@YAXHPAURpHAnimHierarchy@@@Z @ 0x00070990
// Sets up the six axis directions, then for each entry of the kind arg_0's
// table (0 and 1: 13 boxes, the first scaled by 0.75 or 1.1; else 11) the
// box between its two bones of the hierarchy arg_4: a frame along the bone
// (or its reverse), the box's corners in it, and the two bones' indices.
void sub_8C690(RwInt32 arg_0, RpHAnimHierarchy *arg_4)
{
    type_428E80 *lv_4;
    type_4B21D0_60 *lv_8;
    RwInt32 lv_c;
    RwMatrix *lv_10;
    RwReal lv_14;
    RwReal lv_18;
    RwReal lv_dc;
    RwInt32 lv_e0;
    RwInt32 lv_e4;
    RwInt32 lv_e8;
    RwMatrix *lv_ec;
    RwMatrix *lv_f0;
    type_8BFA0 lv_150;
#ifndef CODFH_SP // single player: in the loop
    RwV3d lv_17c;
#endif
    RwReal lv_1a4;
    RwReal lv_1a8;
    RwReal lv_1b0;

    lv_4 = 0;
    lv_8 = 0;
    lv_c = 0;
    lv_10 = RpHAnimHierarchyGetMatrixArray(arg_4);
    lv_14 = 1.0f;
    lv_18 = 1.0f;
    dword_4B21D0.unk_00[0] = sub_8BBE0(-1.0f, 0.0f, 0.0f, 0.0f);
    dword_4B21D0.unk_00[1] = sub_8BBE0(1.0f, 0.0f, 0.0f, 0.0f);
    dword_4B21D0.unk_00[2] = sub_8BBE0(0.0f, 1.0f, 0.0f, 0.0f);
    dword_4B21D0.unk_00[3] = sub_8BBE0(0.0f, -1.0f, 0.0f, 0.0f);
    dword_4B21D0.unk_00[4] = sub_8BBE0(0.0f, 0.0f, 1.0f, 0.0f);
    dword_4B21D0.unk_00[5] = sub_8BBE0(0.0f, 0.0f, -1.0f, 0.0f);
    if (arg_0 == 0) {
        lv_4 = dword_428E80;
        lv_c = 13;
        lv_8 = dword_4B21D0.unk_60;
        lv_14 = 0.75f;
    } else if (arg_0 == 1) {
        lv_4 = dword_428E80;
        lv_c = 13;
        lv_8 = dword_4B21D0.unk_60;
#ifndef CODFH_SP // single player does not grow kind 1's first bone (SP 0x70B42)
        lv_18 = 1.1f;
#endif
    } else {
        lv_4 = dword_428FB8;
        lv_c = 11;
        lv_8 = dword_4B21D0.unk_1E0;
    }
    lv_dc = lv_18;
    for (lv_e0 = 0; lv_e0 < lv_c; lv_e0++) {
        lv_e4 = RpHAnimIDGetIndex(arg_4, lv_4[lv_e0].unk_00);
        lv_e8 = RpHAnimIDGetIndex(arg_4, lv_4[lv_e0].unk_04);
        lv_ec = &lv_10[lv_e4];
        lv_f0 = &lv_10[lv_e8];
        lv_150.unk_00[1] = sub_8BB80(&lv_f0->pos);
        lv_150.unk_00[1] = sub_8BAA0(&lv_150.unk_00[1], (type_8BEC0 *)&lv_ec->pos);
        lv_150.unk_00[1].unk_0C = 0.0f;
#ifdef CODFH_SP // single player always builds the frame across the bone and sizes the box from the entry's unk_08 and unk_0C before the bone's length replaces its height (SP 0x70C7F, 0x70DEB)
        lv_150.unk_00[1] = sub_8BE10(&lv_150.unk_00[1]);
        lv_150.unk_00[2] = sub_8BBE0(0.0f, 0.0f, 1.0f, 0.0f);
        lv_150.unk_00[0] = sub_8B920(&lv_150.unk_00[2], &lv_150.unk_00[1]);
        lv_150.unk_00[0] = sub_8BE10(&lv_150.unk_00[0]);
        lv_150.unk_00[2] = sub_8B920(&lv_150.unk_00[0], &lv_150.unk_00[1]);
        lv_150.unk_00[2] = sub_8BE10(&lv_150.unk_00[2]);
        lv_150.unk_00[2] = sub_8BBE0(-lv_150.unk_00[2].unk_00, -lv_150.unk_00[2].unk_04,
                                     -lv_150.unk_00[2].unk_08, 0.0f);
        lv_150.unk_00[3] = sub_8BBE0(0.0f, 0.0f, 0.0f, 1.0f);
        lv_dc = (lv_e0 == 0) ? lv_18 : lv_14;
        lv_8[lv_e0].unk_00 = -(lv_dc * lv_4[lv_e0].unk_08);
        lv_8[lv_e0].unk_04 = -(lv_dc * lv_4[lv_e0].unk_0C);
        lv_8[lv_e0].unk_08 = -(lv_dc * lv_4[lv_e0].unk_08);
        lv_8[lv_e0].unk_0C = 1.0f;
        lv_8[lv_e0].unk_10 = lv_dc * lv_4[lv_e0].unk_08;
        lv_8[lv_e0].unk_14 = lv_dc * lv_4[lv_e0].unk_0C;
        lv_8[lv_e0].unk_18 = lv_dc * lv_4[lv_e0].unk_08;
        lv_8[lv_e0].unk_1C = 1.0f;
        RwV3d lv_17c;
        RwV3dSub(&lv_17c, &lv_ec->pos, &lv_f0->pos);
        lv_8[lv_e0].unk_04 = 0.0f;
        lv_8[lv_e0].unk_14 = RwV3dLength((RwV3d *)&lv_17c);
        *(type_8C410 *)&lv_8[lv_e0] = sub_8C410((RwMatrix *)&lv_150, (type_8BEC0 *)&lv_8[lv_e0]);
        lv_8[lv_e0].unk_0C = (RwReal)lv_e4;
        lv_8[lv_e0].unk_1C = (RwReal)lv_e8;
    }
#else
        RwV3dSub(&lv_17c, &lv_ec->pos, &lv_f0->pos);
        lv_150.unk_00[1] = sub_8BE10(&lv_150.unk_00[1]);
        lv_1a4 = lv_150.unk_00[1].unk_08;
        lv_1a8 = lv_150.unk_00[1].unk_04;
        lv_1b0 = ((RwReal)fabs(lv_1a8));
        if (((RwReal)fabs(lv_1a4)) > lv_1b0) {
            if (lv_4[lv_e0].unk_14)
                lv_150.unk_00[2] = lv_150.unk_00[1];
            else
                lv_150.unk_00[2] = sub_8BBE0(-lv_150.unk_00[1].unk_00, -lv_150.unk_00[1].unk_04,
                                             -lv_150.unk_00[1].unk_08, 0.0f);
            lv_150.unk_00[1] = sub_8BBE0(0.0f, -1.0f, 0.0f, 0.0f);
            lv_150.unk_00[0] = sub_8B920(&lv_150.unk_00[2], &lv_150.unk_00[1]);
            lv_150.unk_00[0] = sub_8BE10(&lv_150.unk_00[0]);
            lv_150.unk_00[1] = sub_8B920(&lv_150.unk_00[0], &lv_150.unk_00[2]);
            lv_150.unk_00[1] = sub_8BE10(&lv_150.unk_00[1]);
            lv_150.unk_00[3] = sub_8BBE0(0.0f, 0.0f, 0.0f, 1.0f);
            lv_8[lv_e0].unk_08 = -lv_4[lv_e0].unk_08 * lv_dc;
            lv_8[lv_e0].unk_00 = 0.0f;
            lv_8[lv_e0].unk_04 = -lv_4[lv_e0].unk_08 * lv_dc;
            lv_8[lv_e0].unk_0C = 1.0f;
            lv_8[lv_e0].unk_18 = lv_dc * lv_4[lv_e0].unk_08;
            lv_8[lv_e0].unk_10 = RwV3dLength((RwV3d *)&lv_17c);
            lv_8[lv_e0].unk_14 = lv_dc * lv_4[lv_e0].unk_08;
            lv_8[lv_e0].unk_1C = 1.0f;
            *(type_8C410 *)&lv_8[lv_e0] = sub_8C410((RwMatrix *)&lv_150, (type_8BEC0 *)&lv_8[lv_e0]);
            lv_8[lv_e0].unk_0C = (RwReal)lv_e4;
            lv_8[lv_e0].unk_1C = (RwReal)lv_e8;
        } else {
            lv_150.unk_00[2] = sub_8BBE0(0.0f, 0.0f, 1.0f, 0.0f);
            lv_150.unk_00[0] = sub_8B920(&lv_150.unk_00[2], &lv_150.unk_00[1]);
            lv_150.unk_00[0] = sub_8BE10(&lv_150.unk_00[0]);
            lv_150.unk_00[2] = sub_8B920(&lv_150.unk_00[1], &lv_150.unk_00[0]);
            lv_150.unk_00[2] = sub_8BE10(&lv_150.unk_00[2]);
            lv_150.unk_00[2] = sub_8BBE0(-lv_150.unk_00[2].unk_00, -lv_150.unk_00[2].unk_04,
                                         -lv_150.unk_00[2].unk_08, 0.0f);
            lv_150.unk_00[3] = sub_8BBE0(0.0f, 0.0f, 0.0f, 1.0f);
            lv_8[lv_e0].unk_00 = -lv_4[lv_e0].unk_08 * lv_dc;
            lv_8[lv_e0].unk_08 = -lv_4[lv_e0].unk_08 * lv_dc;
            lv_8[lv_e0].unk_0C = 1.0f;
            lv_8[lv_e0].unk_10 = lv_dc * lv_4[lv_e0].unk_08;
            lv_8[lv_e0].unk_18 = lv_dc * lv_4[lv_e0].unk_08;
            lv_8[lv_e0].unk_04 = 0.0f;
            lv_8[lv_e0].unk_14 = RwV3dLength((RwV3d *)&lv_17c);
            lv_8[lv_e0].unk_1C = 1.0f;
            *(type_8C410 *)&lv_8[lv_e0] = sub_8C410((RwMatrix *)&lv_150, (type_8BEC0 *)&lv_8[lv_e0]);
            lv_8[lv_e0].unk_0C = (RwReal)lv_e4;
            lv_8[lv_e0].unk_1C = (RwReal)lv_e8;
        }
        lv_dc = lv_14;
    }
#endif
}

// match: ?sub_8D580@@YAXPAURpHAnimHierarchy@@H@Z @ 0x0008D580
// sp-match: ?sub_8D580@@YAXPAURpHAnimHierarchy@@H@Z @ 0x00070ED0
void sub_8D580(RpHAnimHierarchy *arg_0, RwInt32 arg_4)
{
    sub_8C690(arg_4, arg_0);
}

// match: ?sub_8D5A0@@YAHPAUtype_8BEC0@@0@Z @ 0x0008D5A0
// sp-match: ?sub_8D5A0@@YAHPAUtype_8BEC0@@0@Z @ 0x00070EF0
RwInt32 sub_8D5A0(type_8BEC0 *arg_0, type_8BEC0 *arg_4)
{
    RwInt32 var_4;

    var_4 = 0;
    if (arg_0->unk_00 < arg_4[0].unk_00)
    {
        var_4 |= 1;
    }
    if (arg_0->unk_00 > arg_4[1].unk_00)
    {
        var_4 |= 2;
    }
    if (arg_0->unk_04 < arg_4[0].unk_04)
    {
        var_4 |= 4;
    }
    if (arg_0->unk_04 > arg_4[1].unk_04)
    {
        var_4 |= 8;
    }
    if (arg_0->unk_08 < arg_4[0].unk_08)
    {
        var_4 |= 0x10;
    }
    if (arg_0->unk_08 > arg_4[1].unk_08)
    {
        var_4 |= 0x20;
    }
    return var_4;
}

// match: ?sub_8D660@@YAHHPAURpHAnimHierarchy@@PAURpIntersection@@HPAUtype_4B21D0_60@@@Z @ 0x0008D660
// sp-match: ?sub_8D660@@YAHHPAURpHAnimHierarchy@@PAURpIntersection@@HPAUtype_4B21D0_60@@@Z @ 0x00071560
// The line variant: arg_8 is read as an RwLine. Each of the first arg_0 bone
// boxes (as sub_8E330 picks them) goes into its bone's space (sub_8C410,
// into dword_4B21D0's unk_360); a line wholly inside one gives that box's
// part at once, else the nearest face it crosses within the box gives the
// part (the y and z faces are both tested on the upper outcode bit, 8 and
// 0x20: 4 and 0x10 are never looked at). -1 for a miss.
RwInt32 sub_8D660(RwInt32 arg_0, RpHAnimHierarchy *arg_4, RpIntersection *arg_8, RwInt32 arg_C,
                  type_4B21D0_60 *arg_10)
{
    RwReal var_4;
    RwInt32 var_8;
    RwMatrix *var_C;
    RwReal var_10;
    RwReal var_14;
    type_4B21D0 *var_18;
    type_4B21D0_60 *var_1C;
    type_428E80 *var_20;
    type_8C410 *var_24;
    RwInt32 var_28;
    RwInt32 var_2C;
    type_8BFA0 var_70;
    RwReal var_74;
    __declspec(align(16)) type_8C410 var_A0;
    __declspec(align(16)) type_8BEC0 var_110;
    __declspec(align(16)) type_8BEC0 var_140;
    RwInt32 var_144;
    RwInt32 var_148;
    RwReal var_14C;
    __declspec(align(16)) type_8BEC0 var_1C0;

    var_4 = 1.0f;
    var_8 = -1;
    var_C = RpHAnimHierarchyGetMatrixArray(arg_4);
    var_10 = 1.0f;
    var_14 = 1.0f;
#ifndef CODFH_SP // single player compiles the empty debug call out (SP 0x71588)
    sub_19A750();
#endif
    var_18 = &dword_4B21D0;
    if (arg_10)
    {
        var_1C = arg_10;
        var_20 = dword_428E80;
    }
    else if (arg_C == 0)
    {
        var_1C = var_18->unk_60;
        var_20 = dword_428E80;
        var_10 = 0.75f;
    }
    else if (arg_C == 1)
    {
        var_1C = var_18->unk_60;
        var_20 = dword_428E80;
#ifndef CODFH_SP // single player does not grow kind 1's first bone (SP 0x715B9)
        var_14 = 1.1f;
#endif
    }
    else
    {
        var_1C = var_18->unk_1E0;
        var_20 = dword_428FB8;
    }
    var_24 = &var_18->unk_360;
    for (var_28 = 0; var_28 < arg_0; var_28++, var_1C++)
    {
        var_2C = (RwInt32)var_1C->unk_0C;
        var_70 = *(type_8BFA0 *)&var_C[var_2C];
        var_70.unk_00[0].unk_0C = 0.0f;
        var_70.unk_00[1].unk_0C = 0.0f;
        var_70.unk_00[2].unk_0C = 0.0f;
        var_70.unk_00[3].unk_0C = 1.0f;
        if (var_28 == 0)
        {
            var_74 = var_14;
        }
        else
        {
            var_74 = var_10;
        }
        var_A0.unk_10.unk_00 = var_74 * var_1C->unk_10;
        var_A0.unk_10.unk_04 = var_74 * var_1C->unk_14;
        var_A0.unk_10.unk_08 = var_74 * var_1C->unk_18;
        var_A0.unk_00.unk_00 = var_74 * var_1C->unk_00;
        var_A0.unk_00.unk_04 = var_74 * var_1C->unk_04;
        var_A0.unk_00.unk_08 = var_74 * var_1C->unk_08;
        *var_24 = sub_8C410((RwMatrix *)&var_70, &var_A0.unk_00);
        var_110 = sub_8BB80(&((RwLine *)arg_8)->start);
        var_140 = sub_8BB80(&((RwLine *)arg_8)->end);
        var_144 = sub_8D5A0(&var_110, &var_24->unk_00);
        var_148 = sub_8D5A0(&var_140, &var_24->unk_00);
        if (var_144 & var_148)
        {
            continue;
        }
        if (!(var_144 | var_148))
        {
            return var_20[var_28].unk_10;
        }
        if ((var_144 & 0x1) || (var_148 & 0x1))
        {
            var_14C = (var_24->unk_00.unk_00 - var_110.unk_00) / (var_140.unk_00 - var_110.unk_00);
            var_1C0 = sub_8BB10(&var_110, &sub_8BA30(&var_14C, &sub_8BAA0(&var_140, &var_110)));
            if (var_1C0.unk_04 >= var_24->unk_00.unk_04 && var_1C0.unk_04 <= var_24->unk_10.unk_04
                && var_1C0.unk_08 >= var_24->unk_00.unk_08 && var_1C0.unk_08 <= var_24->unk_10.unk_08)
            {
                if (var_14C < var_4)
                {
                    var_4 = var_14C;
                    var_8 = var_28;
                }
                continue;
            }
        }
        if ((var_144 & 0x2) || (var_148 & 0x2))
        {
            var_14C = (var_24->unk_10.unk_00 - var_110.unk_00) / (var_140.unk_00 - var_110.unk_00);
            var_1C0 = sub_8BB10(&var_110, &sub_8BA30(&var_14C, &sub_8BAA0(&var_140, &var_110)));
            if (var_1C0.unk_04 >= var_24->unk_00.unk_04 && var_1C0.unk_04 <= var_24->unk_10.unk_04
                && var_1C0.unk_08 >= var_24->unk_00.unk_08 && var_1C0.unk_08 <= var_24->unk_10.unk_08)
            {
                if (var_14C < var_4)
                {
                    var_4 = var_14C;
                    var_8 = var_28;
                }
                continue;
            }
        }
        if ((var_144 & 0x8) || (var_148 & 0x8))
        {
            var_14C = (var_24->unk_00.unk_04 - var_110.unk_04) / (var_140.unk_04 - var_110.unk_04);
            var_1C0 = sub_8BB10(&var_110, &sub_8BA30(&var_14C, &sub_8BAA0(&var_140, &var_110)));
            if (var_1C0.unk_00 >= var_24->unk_00.unk_00 && var_1C0.unk_00 <= var_24->unk_10.unk_00
                && var_1C0.unk_08 >= var_24->unk_00.unk_08 && var_1C0.unk_08 <= var_24->unk_10.unk_08)
            {
                if (var_14C < var_4)
                {
                    var_4 = var_14C;
                    var_8 = var_28;
                }
                continue;
            }
        }
        if ((var_144 & 0x8) || (var_148 & 0x8))
        {
            var_14C = (var_24->unk_10.unk_04 - var_110.unk_04) / (var_140.unk_04 - var_110.unk_04);
            var_1C0 = sub_8BB10(&var_110, &sub_8BA30(&var_14C, &sub_8BAA0(&var_140, &var_110)));
            if (var_1C0.unk_00 >= var_24->unk_00.unk_00 && var_1C0.unk_00 <= var_24->unk_10.unk_00
                && var_1C0.unk_08 >= var_24->unk_00.unk_08 && var_1C0.unk_08 <= var_24->unk_10.unk_08)
            {
                if (var_14C < var_4)
                {
                    var_4 = var_14C;
                    var_8 = var_28;
                }
                continue;
            }
        }
        if ((var_144 & 0x20) || (var_148 & 0x20))
        {
            var_14C = (var_24->unk_00.unk_08 - var_110.unk_08) / (var_140.unk_08 - var_110.unk_08);
            var_1C0 = sub_8BB10(&var_110, &sub_8BA30(&var_14C, &sub_8BAA0(&var_140, &var_110)));
            if (var_1C0.unk_00 >= var_24->unk_00.unk_00 && var_1C0.unk_00 <= var_24->unk_10.unk_00
                && var_1C0.unk_04 >= var_24->unk_00.unk_04 && var_1C0.unk_04 <= var_24->unk_10.unk_04)
            {
                if (var_14C < var_4)
                {
                    var_4 = var_14C;
                    var_8 = var_28;
                }
                continue;
            }
        }
        if ((var_144 & 0x20) || (var_148 & 0x20))
        {
            var_14C = (var_24->unk_10.unk_08 - var_110.unk_08) / (var_140.unk_08 - var_110.unk_08);
            var_1C0 = sub_8BB10(&var_110, &sub_8BA30(&var_14C, &sub_8BAA0(&var_140, &var_110)));
            if (var_1C0.unk_00 >= var_24->unk_00.unk_00 && var_1C0.unk_00 <= var_24->unk_10.unk_00
                && var_1C0.unk_04 >= var_24->unk_00.unk_04 && var_1C0.unk_04 <= var_24->unk_10.unk_04)
            {
                if (var_14C < var_4)
                {
                    var_4 = var_14C;
                    var_8 = var_28;
                }
                continue;
            }
        }
    }
    if (var_8 != -1)
    {
        return var_20[var_8].unk_10;
    }
    return -1;
}

#ifdef CODFH_SP // SP 0x71EE0
// shape: the two inline negations in sub_8E330 cancel, while retaining the
// image's load of the sphere pointer before the plane-distance addition.
static inline RwReal sp_negate_plane_distance(RwReal value)
{
    return -value;
}
#endif

// match: ?sub_8E330@@YAHHPAURpHAnimHierarchy@@PAURpIntersection@@HPAUtype_4B21D0_60@@@Z @ 0x0008E330
// sp-match: ?sub_8E330@@YAHHPAURpHAnimHierarchy@@PAURpIntersection@@HPAUtype_4B21D0_60@@@Z @ 0x00071EE0
// The sphere variant: for each of the first arg_0 bones' boxes (the table
// arg_10, else the kind arg_C's in dword_4B21D0, kind 0 shrunk to 0.75 and
// kind 1 grown to 1.1 at the first bone), the sphere's centre (arg_8 is read
// as an RwSphere) in the bone's space against the six axis planes; the
// nearest plane within the radius, or -1.
RwInt32 sub_8E330(RwInt32 arg_0, RpHAnimHierarchy *arg_4, RpIntersection *arg_8, RwInt32 arg_C,
                  type_4B21D0_60 *arg_10)
{
    RwMatrix *var_4;
    RwReal var_8;
    RwInt32 var_C;
    RwReal var_10;
    RwReal var_14;
    type_4B21D0 *var_18;
    type_8BEC0 *var_1C;
    type_4B21D0_60 *var_20;
    RwInt32 var_24;
    bool var_25;
    RwInt32 var_2C;
    type_8BFA0 var_70;
    type_8BFA0 var_130;
    __declspec(align(16)) type_8BEC0 var_160;
    RwReal var_184;
    RwInt32 var_188;
    RwReal var_18C;

    var_4 = RpHAnimHierarchyGetMatrixArray(arg_4);
    var_8 = 1.0e9f;
    var_C = -1;
    var_10 = 1.0f;
    var_14 = 1.0f;
#ifndef CODFH_SP // single player compiles the empty debug call out (SP 0x71EF8)
    sub_19A750();
#endif
    var_18 = &dword_4B21D0;
    var_1C = var_18->unk_00;
    if (arg_10)
    {
        var_20 = arg_10;
    }
    else if (arg_C == 0)
    {
        var_20 = var_18->unk_60;
        var_10 = 0.75f;
    }
    else if (arg_C == 1)
    {
        var_20 = var_18->unk_60;
#ifndef CODFH_SP // single player does not grow kind 1's first bone (SP 0x71F36)
        var_14 = 1.1f;
#endif
    }
    else
    {
        var_20 = var_18->unk_1E0;
    }
    for (var_24 = 0; var_24 < arg_0; var_24++, var_20++)
    {
        var_25 = true;
        var_2C = (RwInt32)var_20->unk_0C;
        var_70 = *(type_8BFA0 *)&var_4[var_2C];
        var_70.unk_00[0].unk_0C = 0.0f;
        var_70.unk_00[1].unk_0C = 0.0f;
        var_70.unk_00[2].unk_0C = 0.0f;
        var_70.unk_00[3].unk_0C = 1.0f;
        var_130 = sub_8BFA0((RwMatrix *)&var_70);
        var_160 = sub_8BB80((RwV3d *)arg_8);
        var_160 = sub_8BEC0((RwMatrix *)&var_130, &var_160);
        if (var_24 == 0)
        {
            var_184 = var_14;
        }
        else
        {
            var_184 = var_10;
        }
        var_1C[0].unk_0C = var_184 * var_20->unk_00;
        var_1C[1].unk_0C = var_184 * var_20->unk_00;
        var_1C[2].unk_0C = var_184 * var_20->unk_04;
        var_1C[3].unk_0C = var_184 * var_20->unk_04;
        var_1C[4].unk_0C = var_184 * var_20->unk_08;
        var_1C[5].unk_0C = var_184 * var_20->unk_08;
        for (var_188 = 0; var_188 < 6; var_188++)
        {
#ifdef CODFH_SP // SP 0x71EE0
            // shape: preserve VC7.1's pointer-load order without changing the sum.
            var_18C = sp_negate_plane_distance(sp_negate_plane_distance(
                (sub_8BC40(&var_1C[var_188], &var_160)))) + var_1C[var_188].unk_0C;
#else // MP 0x8E330
            var_18C = sub_8BC40(&var_1C[var_188], &var_160) + var_1C[var_188].unk_0C;
#endif
            if (var_18C <= ((RwSphere *)arg_8)->radius && var_18C < var_8)
            {
                var_8 = var_18C;
                var_C = var_188;
            }
        }
    }
    return var_C;
}






















































#endif
