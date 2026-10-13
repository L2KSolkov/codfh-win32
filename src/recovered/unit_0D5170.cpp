// The entity manager (the image's GameEntityManager, from its warnings): the
// entity lists, the pools, the handles and the per-frame update. The
// original file name is not in the image, so it is named for its start
// address.

#include <stdio.h>

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_3D3548.h"
#include "types/type_D48D0.h"
#include "types/type_D4C80.h"
#include "types/type_4B83A0.h"
#include "types/type_4B85F8.h"
#include "types/type_3D32F8.h"
#ifdef CODFH_SP
#include "types/animbank.h" // get_pool (sub_D56D0)
#endif
#if !defined(CODFH_SP) || CODFH_SP_PART == 2 // single player: the data with the second of its two files (src/sp/units/sp_unit_0D5170_2.cpp)

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7120
extern const RwReal flt_3D7120 = 16.666666f;
#ifndef CODFH_SP // single player has neither 0.01f: its table follows 16.666666f's pad (SP 0x2E3510, 0x2E3518)
// 0x003D7124
extern const RwReal flt_3D7124 = 0.01f;
// 0x003D7128
extern const RwReal flt_3D7128 = 0.01f;
#endif
// 0x003D7130
extern const type_3D7130 dword_3D7130[9] =
{
#ifdef CODFH_SP // single player's sizes and counts (SP 0x2E3518, read at SP 0xA1945)
    { 0x3D0, 25 },
    { 0x420, 25 },
    { 0x460, 30 },
    { 0x5E0, 5 },
    { 0x790, 30 },
    { 0x9B0, 0 },
    { 0x2170, 15 },
    { 0x2260, 1 },
    { 0x29D0, 10 },
#else
    { 0x3E0, 32 },
    { 0x420, 25 },
    { 0x490, 10 },
    { 0x5E0, 5 },
    { 0x790, 0 },
    { 0x9B0, 0 },
    { 0x2240, 32 },
    { 0x22F0, 1 },
    { 0x29D0, 0 },
#endif
};
// 0x00429264
RwInt32 dword_429264 = 10;
// 0x00429268
RwInt32 dword_429268 = 1;
// 0x004B6A00
type_4B6A00 dword_4B6A00[768];
// 0x004B8200
RwInt32 dword_4B8200;
// 0x004B8204
struct type_3D3548 *dword_4B8204;
// 0x004B8208
RwInt32 dword_4B8208;
// 0x004B820C
struct type_3D3548 *dword_4B820C;
// 0x004B8210
RwInt32 dword_4B8210;
// 0x004B8214
RwInt32 dword_4B8214;
// 0x004B8218
RwInt32 dword_4B8218;
// 0x004B8600
#ifndef CODFH_PLAIN
type_4B8600 dword_4B8600[16];
#endif
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4B83A0 dword_4B83A0[9];
type_4B85F8 dword_4B85F8[16];
// 32 entity handles after the pools; no code refers to them.
type_D48D0 dword_4B8578[32];
// The debris states sub_D63A0 hands out.
type_76290 unk_4B8220[8];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D7120@@3MB @ 0x003D7120
// match: ?flt_3D7124@@3MB @ 0x003D7124
// match: ?flt_3D7128@@3MB @ 0x003D7128
// match: ?dword_3D7130@@3QBUtype_3D7130@@B @ 0x003D7130
// match: ??_C@_0EH@GGLFNACG@GameEntityManager?3?3Restart?5?9?5Han@ @ 0x003D7178
// match: ??_C@_0EI@MAHDIAFK@GameEntityManager?3?3Shutdown?5?9?5Ha@ @ 0x003D71C0
// match: ??_C@_0HD@JBHBJMMG@WARNING?3?5A?5priority?5spawn?5could?5@ @ 0x003D7208
// match: ??_C@_0BJ@PJBBKOOH@HitByBulletAssassination?$AA@ @ 0x003D727C
// match: ??_C@_0FG@EHHHNOFO@GameEntityManager?3?3NotificationO@ @ 0x003D7298
// match: ??_C@_0BD@KNFMLEAE@GameEntity?5Pool?5?$CFd?$AA@ @ 0x003D72F0
// match: ??_C@_0CO@DKGAACKE@GameEntityPool?3?3?5?$CFd?5was?5not?5empt@ @ 0x003D7304
// match: __ehhandler$??0type_4B83A0@@QAE@XZ>1>8 @ 0x0041CC50
// match: __ehhandler$??0type_4B83A0@@QAE@XZ>1 @ 0x0041CC58
// match: .CRT$XCU+0 @ 0x00426FE8
// match: .CRT$XCU+4 @ 0x00426FEC
// match: .CRT$XCU+8 @ 0x00426FF0
// match: .CRT$XCU+12 @ 0x00426FF4
// match: ?dword_429264@@3HA @ 0x00429264
// match: ?dword_429268@@3HA @ 0x00429268

// match: _$E2 @ 0x0030B110
// match: _$E3 @ 0x0030E380
// match: _$E5 @ 0x0030B140
// match: _$E6 @ 0x0030E3A0
// match: _$E8 @ 0x0030B170
// match: _$E9 @ 0x0030E3C0
// match: _$E11 @ 0x0030B1A0
// sp-match: _$E2 @ 0x0021D4A0
// sp-match: _$E5 @ 0x0021D4D0
// sp-match: _$E3 @ 0x0021E7A0
// sp-match: _$E6 @ 0x0021E7C0
#endif
#if !defined(CODFH_SP) || CODFH_SP_PART == 1 // single player compiles type_4B85F8's members in a file of their own (sp_unit_0D5170_1.cpp, SP 0xA1410-0xA14FF)
// match: ??0type_4B85F8@@QAE@XZ @ 0x000D5170
// sp-match: ??0type_4B85F8@@QAE@XZ @ 0x000A14F0

type_4B85F8::type_4B85F8()
{
    sub_D5190();
}

// match: ?sub_D5190@type_4B85F8@@QAEXXZ @ 0x000D5190
// sp-match: ?sub_D5190@type_4B85F8@@QAEXXZ @ 0x000A1410
void type_4B85F8::sub_D5190()
{
    unk_00 = 0;
    unk_04 = 0x11;
    unk_08 = 0;
    unk_0C = 0;
}

// match: ?sub_D51D0@type_4B85F8@@QAEXH@Z @ 0x000D51D0
// sp-match: ?sub_D51D0@type_4B85F8@@QAEXH@Z @ 0x000A1430
void type_4B85F8::sub_D51D0(RwInt32 arg_0)
{
    sub_D5190();
    unk_04 = arg_0;
    unk_00 = 1;
}

// match: ?sub_D5200@type_4B85F8@@QAEXXZ @ 0x000D5200
// sp-match: ?sub_D5200@type_4B85F8@@QAEXXZ @ 0x000A1450
void type_4B85F8::sub_D5200()
{
    sub_D5190();
}

// match: ?sub_D5220@type_4B85F8@@QAEXPAUtype_3D3548@@@Z @ 0x000D5220
// sp-match: ?sub_D5220@type_4B85F8@@QAEXPAUtype_3D3548@@@Z @ 0x000A1460
void type_4B85F8::sub_D5220(type_3D3548 *arg_0)
{
    arg_0->unk_14 = 0;
    if (unk_08)
    {
        arg_0->unk_10 = unk_08;
        unk_08->unk_14 = arg_0;
        unk_08 = arg_0;
    }
    else
    {
        arg_0->unk_10 = 0;
        unk_08 = arg_0;
        unk_0C = arg_0;
    }
    arg_0->unk_24 = unk_04;
}

// match: ?sub_D5290@type_4B85F8@@QAEXPAUtype_3D3548@@@Z @ 0x000D5290
// sp-match: ?sub_D5290@type_4B85F8@@QAEXPAUtype_3D3548@@@Z @ 0x000A14A0
void type_4B85F8::sub_D5290(type_3D3548 *arg_0)
{
    if (arg_0->unk_14)
    {
        arg_0->unk_14->unk_10 = arg_0->unk_10;
    }
    if (arg_0->unk_10)
    {
        arg_0->unk_10->unk_14 = arg_0->unk_14;
    }
    if (arg_0 == unk_08)
    {
        unk_08 = arg_0->unk_10;
    }
    if (arg_0 == unk_0C)
    {
        unk_0C = arg_0->unk_14;
    }
    arg_0->unk_24 = 0x11;
    arg_0->unk_10 = 0;
    arg_0->unk_14 = 0;
}

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART == 2
// match: ?sub_D5320@@YAXPAH@Z @ 0x000D5320
// sp-match: ?sub_D5320@@YAXPAH@Z @ 0x000A1910
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D5320(RwInt32 *arg_0)
{
    RwInt32 var_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (dword_4B8200)
    {
        return;
    }
    dword_429264 = 10;
    dword_4B8204 = 0;
    var_C = 0;
    bp_8 = 0;
    bp_4 = 0;
    var_10 = 0;
    for (bp_4 = 0; bp_4 < 9; bp_4++)
    {
        bp_8 = dword_3D7130[bp_4].unk_00;
        if (arg_0)
        {
            var_10 = arg_0[bp_4];
        }
        else
        {
            var_10 = dword_3D7130[bp_4].unk_04;
        }
        dword_4B83A0[bp_4].sub_D64A0(bp_4, bp_8, var_10);
        var_C = dword_3D7130[bp_4].unk_00;
    }
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        dword_4B85F8[bp_4].sub_D51D0(bp_4);
    }
    for (bp_4 = 0; bp_4 < 0x300; bp_4++)
    {
        dword_4B6A00[bp_4].unk_00 = 0;
        dword_4B6A00[bp_4].unk_04 = 0;
    }
    dword_4B8200 = 1;
    dword_4B8208 = 0;
    dword_4B69F8 = 0;
    dword_429268 = 1;
    dword_4B820C = 0;
    sub_D6350();
}

// match: ?sub_D5480@@YAXXZ @ 0x000D5480
// sp-match: ?sub_D5480@@YAXXZ @ 0x000A2140
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D5480()
{
    RwInt32 var_8;
    RwInt32 l4;

    dword_429264 = 10;
    sub_D5650();
    l4 = 0;
    for (l4 = 0; l4 < 16; l4++)
    {
        dword_4B85F8[l4].pDtor();
    }
    for (l4 = 0; l4 < 9; l4++)
    {
        dword_4B83A0[l4].sub_D6550();
    }
    sub_D6350();
    dword_4B8208 = 0;
    dword_4B69F8 = 0;
    dword_429268 = 1;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
    for (var_8 = 0; var_8 < 0x300; var_8++)
    {
        if (dword_4B6A00[var_8].unk_00 || dword_4B6A00[var_8].unk_04)
        {
            sub_19A750("GameEntityManager::Restart - Handle array %d is not empty at restart!\n", var_8);
        }
    }
#endif
}

// match: ?sub_D5570@@YAXXZ @ 0x000D5570
// sp-match: ?sub_D5570@@YAXXZ @ 0x000A21A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D5570()
{
    RwInt32 var_8;
    RwInt32 l4;

    dword_429264 = 10;
    dword_4B8208 = 0;
    sub_D5650();
    l4 = 0;
    for (l4 = 0; l4 < 16; l4++)
    {
        dword_4B85F8[l4].sub_D5200();
    }
    for (l4 = 0; l4 < 9; l4++)
    {
        dword_4B83A0[l4].sub_D65A0();
    }
    dword_4B8200 = 0;
    sub_D6350();
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
    for (var_8 = 0; var_8 < 0x300; var_8++)
    {
        if (dword_4B6A00[var_8].unk_00 || dword_4B6A00[var_8].unk_04)
        {
            sub_19A750("GameEntityManager::Shutdown - Handle array %d is not empty at restart!\n", var_8);
        }
    }
#endif
}

// match: ?sub_D5650@@YAXXZ @ 0x000D5650
// sp-match: ?sub_D5650@@YAXXZ @ 0x000A20F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D5650()
{
    type_3D3548 *var_C;
    type_3D3548 *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        var_C = dword_4B85F8[bp_4].unk_08;
        bp_8 = 0;
        while (var_C)
        {
            bp_8 = var_C->unk_10;
            if (!(var_C->unk_28 & 1))
            {
                sub_D5A60(var_C, 2);
            }
            var_C = bp_8;
        }
    }
    sub_D5D20(1);
}

// match: ?sub_D56D0@@YAPAXH_NH@Z @ 0x000D56D0
// sp-match: ?sub_D56D0@@YAPAXH_NH@Z @ 0x000A1D90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void *sub_D56D0(RwInt32 arg_0, bool arg_4, RwInt32 arg_8)
{
    type_3D3548 *var_50;
    RwInt32 var_4C;
    RwInt32 frm_48;
    RwInt32 w44;
    RwV3d s40;
    type_712B0 *l34;
    RwInt32 var30;
    RwReal ebp_2C;
    RwInt32 lcl_28;
    RwInt32 frm_24;
    type_3D3548 *var_20;
    type_16C2A0 *l1C;
    RwUInt32 m_18;
    RwInt32 ebp_14;
    RwReal lv_10;
    RwInt32 var_C;
    void *bp_8;
    type_3D3548 *bp_4;

    bp_8 = 0;
    l34 = 0;
    frm_48 = 9;
    var30 = 1;
    frm_24 = 0;
    w44 = 1;
#ifdef CODFH_SP
    // SP 0xA1D9C: single player's sizes (0x3D0, 0x2170) and two more cases: a
    // 0x3D0 spawn of kind 0x18 takes pool 0 alone and may always sacrifice, and
    // a 0x2170 spawn takes pool 6 only while animation pool 2 has room.
    if (arg_0 == 0x3D0 && arg_8 == 0x18)
    {
        var30 = 0;
        frm_48 = 1;
        arg_4 = true;
        w44 = 0;
    }
    else if (arg_0 == 0x2170)
    {
        var30 = 6;
        frm_48 = 7;
        if (!get_pool(2).m_pool.unk_18)
        {
            frm_24 = 1;
        }
    }
    else if ((RwUInt32)arg_0 < 0x2170)
    {
        frm_48 = 6;
    }
#else
    if (arg_0 == 0x3E0)
    {
        var30 = 0;
    }
    m_18 = 0x21D0;
    if ((RwUInt32)arg_0 < m_18)
    {
        frm_48 = 6;
    }
#endif
    if (!frm_24)
    {
        for (ebp_14 = var30; ebp_14 < frm_48; ebp_14++)
        {
            if (dword_4B83A0[ebp_14].unk_00 >= arg_0 && (RwInt32)!dword_4B83A0[ebp_14].unk_14.sub_16C7E0())
            {
                bp_8 = dword_4B83A0[ebp_14].sub_D65C0();
                dword_429264 = ebp_14;
                break;
            }
        }
    }
    if (!bp_8 && arg_4)
    {
        lv_10 = -1000000.0f;
        var_20 = 0;
        var_C = -1;
        var_50 = sub_1745A0(0);
        for (ebp_14 = var30; ebp_14 < frm_48; ebp_14++)
        {
            if (dword_4B83A0[ebp_14].unk_00 >= arg_0)
            {
                l1C = &dword_4B83A0[ebp_14].unk_14;
                for (var_4C = 0; var_4C < dword_4B83A0[ebp_14].unk_14.get_unk_0C(); var_4C++)
                {
                    bp_4 = (type_3D3548 *)l1C->sub_16C6A0(var_4C);
                    if (bp_4)
                    {
                        lcl_28 = 0;
                        l34 = bp_4->get_unk_34C();
                        if (w44)
                        {
                            if (l34 && l34->vf_008() == arg_8 && l34->unk_24_19)
                            {
                                lcl_28 = 1;
                            }
                        }
                        else
                        {
                            lcl_28 = 1;
                        }
                        if (lcl_28)
                        {
                            RwV3dSub(&s40, (RwV3d *)var_50->vf_0C4(), (RwV3d *)bp_4->vf_0C4());
                            ebp_2C = RwV3dLength(&s40);
                            if (bp_4->unk_28 & 1)
                            {
                                ebp_2C += 10000.0f;
                            }
                            if ((var_50->unk_2C & 7) == (bp_4->unk_2C & 7))
                            {
                                ebp_2C -= 2500.0f;
                            }
                            if (l34)
                            {
                                ebp_2C -= 2500.0f;
                                if (l34->unk_24_18)
                                {
                                    ebp_2C -= 10000.0f;
                                }
                            }
                            if (ebp_2C > lv_10)
                            {
                                var_C = ebp_14;
                                var_20 = bp_4;
                                lv_10 = ebp_2C;
                            }
                        }
                    }
                }
            }
        }
        if (var_20 && var_C != -1)
        {
            var_20->unk_28 |= 1;
            sub_D5AD0(var_20);
            bp_8 = dword_4B83A0[var_C].sub_D65C0();
            dword_429264 = var_C;
        }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
        else
        {
            sub_19A750("WARNING: A priority spawn could not be created due to lack of sacficial lambs. "
                       "Trigger location(%6.2f,%6.2f,%6.2f)",
                       (RwDouble)l34->unk_90, (RwDouble)l34->unk_94, (RwDouble)l34->unk_98);
        }
#endif
    }
    return bp_8;
}

// match: ?sub_D5A60@@YAXPAUtype_3D3548@@H@Z @ 0x000D5A60
// sp-match: ?sub_D5A60@@YAXPAUtype_3D3548@@H@Z @ 0x000A2050
void sub_D5A60(type_3D3548 *arg_0, RwInt32 arg_4)
{
    if (!(arg_0->unk_28 & 1))
    {
        arg_0->unk_28 |= 1;
        if (arg_4 > 0)
        {
            if (dword_4B8204)
            {
                arg_0->unk_1C = dword_4B8204;
                dword_4B8204 = arg_0;
            }
            else
            {
                arg_0->unk_1C = 0;
                dword_4B8204 = arg_0;
            }
            arg_0->unk_38 = arg_4;
        }
        else
        {
            sub_D5AD0(arg_0);
        }
    }
}

// match: ?sub_D5AD0@@YAXPAUtype_3D3548@@@Z @ 0x000D5AD0
// sp-match: ?sub_D5AD0@@YAXPAUtype_3D3548@@@Z @ 0x000A19D0
void sub_D5AD0(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    if (arg_0->unk_1B8)
    {
        operator delete(arg_0->unk_1B8);
        arg_0->unk_1B8 = 0;
    }
    sub_F12A0(arg_0, 0);
    sub_D5BA0(arg_0);
    var_4 = arg_0->unk_384;
    delete (type_D5AD0 *)arg_0;
    if (var_4)
    {
        sub_D5CC0(var_4);
    }
    dword_4B83A0[arg_0->unk_20].sub_D6600(arg_0);
}

// match: ?sub_D5B80@@YAXPAUtype_3D3548@@H@Z @ 0x000D5B80
// sp-match: ?sub_D5B80@@YAXPAUtype_3D3548@@H@Z @ 0x000A1500
void sub_D5B80(type_3D3548 *arg_0, RwInt32 arg_4)
{
    dword_4B85F8[arg_4].sub_D5220(arg_0);
}

// match: ?sub_D5BA0@@YAXPAUtype_3D3548@@@Z @ 0x000D5BA0
// sp-match: ?sub_D5BA0@@YAXPAUtype_3D3548@@@Z @ 0x000A1520
void sub_D5BA0(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    var_4 = arg_0->unk_24;
    if (var_4 != 0x11 && var_4 >= 0 && var_4 < 16)
    {
        dword_4B85F8[arg_0->unk_24].sub_D5290(arg_0);
    }
}

// match: ?sub_D5BE0@@YAHPAUtype_3D3548@@@Z @ 0x000D5BE0
// sp-match: ?sub_D5BE0@@YAHPAUtype_3D3548@@@Z @ 0x000A1550
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D5BE0(type_3D3548 *arg_0)
{
    RwInt32 var_C;
    type_3D3548_384 bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    bp_8.unk_00 = arg_0->unk_384;
    for (var_C = 1; var_C < 0x300; var_C++)
    {
        if (!dword_4B6A00[var_C].unk_00 && !dword_4B6A00[var_C].unk_04)
        {
            if (!dword_429268)
            {
                dword_429268 = 1;
            }
            dword_4B6A00[var_C].unk_00_w = (RwInt16)var_C;
            bp_8.unk_00_w = (RwInt16)var_C;
            dword_4B6A00[var_C].unk_02_w = (RwInt16)dword_429268;
            bp_8.unk_02_w = (RwInt16)dword_429268;
            dword_429268++;
            dword_4B6A00[var_C].unk_04 = arg_0;
            arg_0->sub_CD530(bp_8.unk_00);
            bp_4 = 1;
            break;
        }
    }
    return bp_4;
}

// match: ?sub_D5CC0@@YAXH@Z @ 0x000D5CC0
// sp-match: ?sub_D5CC0@@YAXH@Z @ 0x000A15E0
void sub_D5CC0(RwInt32 arg_0)
{
    dword_4B6A00[(RwInt16)arg_0].unk_00 = 0;
    dword_4B6A00[(RwInt16)arg_0].unk_04 = 0;
}

// match: ?sub_D5CF0@@YAPAUtype_3D3548@@H@Z @ 0x000D5CF0
// sp-match: ?sub_D5CF0@@YAPAUtype_3D3548@@H@Z @ 0x000A1600
type_3D3548 *sub_D5CF0(RwInt32 arg_0)
{
    if (dword_4B6A00[(RwInt16)arg_0].unk_00 == arg_0)
    {
        return dword_4B6A00[(RwInt16)arg_0].unk_04;
    }
    return 0;
}

// match: ?sub_D5D20@@YAXH@Z @ 0x000D5D20
// sp-match: ?sub_D5D20@@YAXH@Z @ 0x000A1A40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D5D20(RwInt32 arg_0)
{
    type_3D3548 *var_C;
    type_3D3548 *bp_8;
    type_3D3548 *bp_4;

    if (!dword_4B8200)
    {
        return;
    }
    var_C = dword_4B8204;
    bp_4 = 0;
    bp_8 = 0;
    while (var_C)
    {
        bp_4 = var_C->unk_1C;
        if (!arg_0 && var_C->unk_38 > 0)
        {
            var_C->unk_38--;
            bp_8 = var_C;
        }
        else if (!arg_0 && var_C->unk_28_11 && var_C->unk_28_10 &&
                 dword_4B83A0[var_C->unk_20].unk_14.get_unk_18() && var_C->unk_38 > -240)
        {
            var_C->unk_38--;
            bp_8 = var_C;
        }
        else
        {
            if (!bp_8)
            {
                dword_4B8204 = bp_4;
            }
            else
            {
                bp_8->unk_1C = bp_4;
            }
            sub_D5AD0(var_C);
        }
        var_C = bp_4;
    }
}

// match: ?sub_D5E20@@YAXXZ @ 0x000D5E20
// sp-match: ?sub_D5E20@@YAXXZ @ 0x000A1AD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D5E20()
{
#ifndef CODFH_SP // single player scopes its block locals (SP 0xA1AD0)
    type_712B0 *var_2C;
#endif
    RwFrame *var_28;
#ifndef CODFH_SP // single player scopes its block locals (SP 0xA1AD0)
    RwInt32 ebp_24;
    RwV3d var_20;
    RwReal ebp_14;
#endif
    type_3D3548 *lv_10;
    RwReal var_C;
    type_3D3548 *bp_8;
    RwInt32 bp_4;

    if (!dword_4B8200)
    {
        return;
    }
    lv_10 = sub_1745A0(0);
    var_C = deltaTime;
    dword_4B8214 = 0;
    dword_4B8218 = 0;
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        bp_8 = dword_4B85F8[bp_4].unk_08;
        while (bp_8)
        {
            if (!(bp_8->unk_28 & 1))
            {
                if (bp_8->unk_88_10 && (bp_8->unk_244 & 0x3F) == (dword_4B87D8 & 0x3F))
                {
#ifdef CODFH_SP
                    type_712B0 *var_2C;
                    RwInt32 ebp_24;
                    RwV3d var_20;
                    RwReal ebp_14;
#endif
                    RwV3dSub(&var_20, (RwV3d *)lv_10->vf_0C4(), (RwV3d *)bp_8->vf_0C4());
                    ebp_14 = RwV3dLength(&var_20);
                    var_2C = (type_712B0 *)bp_8->unk_344.unk_08;
                    if (ebp_14 > var_2C->unk_54)
                    {
                        ebp_24 = 0;
                        sub_6B5F0("HitByBulletAssassination", (type_67620 *)(bp_8->vf_098()), 0, 0, &ebp_24, 1, true, false);
                        bp_8->unk_88 &= ~0x400;
                    }
                }
                if (bp_8->get_unk_388())
                {
                    bp_8->get_unk_388()(bp_8, var_C);
                }
                else
                {
                    sub_16D7F0(0x15);
                    bp_8->vf_038(var_C);
                    bp_8->vf_03C(var_C);
                    sub_16D850(0x15);
                    sub_16D7F0(0x19);
                    if (bp_8->unk_28_4)
                    {
                        bp_8->vf_040(var_C);
                    }
                    sub_16D850(0x19);
                    sub_16D7F0(0x1A);
                    if (bp_8->unk_28_4 && bp_8->unk_28_5)
                    {
                        bp_8->vf_044(var_C);
                    }
                    if (bp_8->unk_28_5)
                    {
                        bp_8->vf_048(var_C);
                    }
                    sub_16D850(0x1A);
                    sub_16D7F0(0x15);
                    bp_8->vf_04C(var_C);
                    sub_16D850(0x15);
                }
                sub_16D7F0(0x1A);
                if (!dword_4B8210 && (bp_8->unk_28 & 0x20000)) // not an address: a flag
                {
                    sub_94060(bp_8);
                }
                sub_16D850(0x1A);
                sub_16D7F0(0x1B);
                if (bp_8->unk_28_6)
                {
                    bp_8->vf_050(var_C);
                }
                sub_16D850(0x1B);
                sub_D49E0(bp_8);
            }
            else
            {
                var_28 = bp_8->get_unk_340();
                if (var_28)
                {
                    RwFrameUpdateObjects(var_28);
                }
            }
            bp_8 = bp_8->unk_10;
        }
    }
    sub_D5D20(0);
    for (bp_4 = 0; bp_4 < 16; bp_4++)
    {
        bp_8 = dword_4B85F8[bp_4].unk_08;
        while (bp_8)
        {
            bp_8->unk_28 &= ~0x400;
            bp_8 = bp_8->unk_10;
        }
    }
}

// match: ?sub_D61F0@@YAXPAUtype_3DF8D8_04@@@Z @ 0x000D61F0
// sp-match: ?sub_D61F0@@YAXPAUtype_3DF8D8_04@@@Z @ 0x000A20A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D61F0(type_3DF8D8_04 *arg_0)
{
    RwUInt32 var_10;
    RwInt32 var_C;
    type_4B6A00 *bp_8;
    type_3D3548 *bp_4;

#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
    if (!dword_4B8200)
    {
        for (var_C = 0; var_C < 0x300; var_C++)
        {
            if (dword_4B6A00[var_C].unk_00 || dword_4B6A00[var_C].unk_04)
            {
                sub_19A750("GameEntityManager::NotificationOfGodAssetTermination - Handle array %d is not empty!\n",
                           var_C);
            }
        }
    }
#endif
    bp_8 = dword_4B6A00;
    for (var_10 = 0; var_10 < 0x300; var_10++, bp_8++)
    {
        if (!bp_8->unk_04)
        {
            continue;
        }
        bp_4 = bp_8->unk_04;
        if (bp_4->unk_24 == 0x11)
        {
            continue;
        }
        if (bp_4->vf_058(arg_0))
        {
            sub_D5A60(bp_4, 2);
        }
    }
    sub_D5D20(1);
}

// match: ?sub_D62D0@@YAXPAX@Z @ 0x000D62D0
// sp-match: ?sub_D62D0@@YAXPAX@Z @ 0x000A1620
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D62D0(void *arg_0)
{
    type_3D3548 *var_8;
    RwInt32 l4;

    dword_4B820C = 0;
    for (l4 = 0; l4 < 16; l4++)
    {
        if (l4 == 14)
        {
            continue;
        }
        var_8 = dword_4B85F8[l4].unk_08;
        while (var_8)
        {
            if (var_8->vf_000(arg_0))
            {
                var_8->unk_18 = dword_4B820C;
                dword_4B820C = var_8;
            }
            var_8 = var_8->unk_10;
        }
    }
}

// match: ?sub_D6350@@YAXXZ @ 0x000D6350
// sp-match: ?sub_D6350@@YAXXZ @ 0x000A1680
void sub_D6350()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 8; var_4++)
    {
        unk_4B8220[var_4].sub_761F0();
        unk_4B8220[var_4].unk_02 = (RwUInt8)var_4;
    }
}

// match: ?sub_D63A0@@YAPAUtype_76290@@PAXH@Z @ 0x000D63A0
// sp-match: ?sub_D63A0@@YAPAUtype_76290@@PAXH@Z @ 0x000A18E0
type_76290 *sub_D63A0(void *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < arg_4; var_4++)
    {
        if (!((type_D63A0 *)arg_0)[var_4].unk_00)
        {
            ((type_D63A0 *)arg_0)[var_4].unk_00 = 1;
            return (type_76290 *)&((type_D63A0 *)arg_0)[var_4];
        }
    }
    return 0;
}

// match: ??0type_4B83A0@@QAE@XZ @ 0x000D63F0
// match: __ehhandler$??0type_4B83A0@@QAE@XZ-0xB @ 0x00300CB0
// match: __ehhandler$??0type_4B83A0@@QAE@XZ @ 0x00300CBB
// sp-match: ??0type_4B83A0@@QAE@XZ @ 0x000A2320
type_4B83A0::type_4B83A0()
{
    sub_D6460();
}

// match: ??1type_4B83A0@@QAE@XZ @ 0x000D6440
// sp-match: ??1type_4B83A0@@QAE@XZ @ 0x000A2200
type_4B83A0::~type_4B83A0()
{
}

// match: ?sub_D6460@type_4B83A0@@QAEXXZ @ 0x000D6460
// sp-match: ?sub_D6460@type_4B83A0@@QAEXXZ @ 0x000A2210
void type_4B83A0::sub_D6460()
{
    unk_08 = 0;
    unk_00 = 0;
    unk_04 = 0;
    unk_0C = 10;
}

// match: ?sub_D64A0@type_4B83A0@@QAEHHHH@Z @ 0x000D64A0
// sp-match: ?sub_D64A0@type_4B83A0@@QAEHHHH@Z @ 0x000A2230
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4B83A0::sub_D64A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 var_28;
    RwChar ebp_24[0x20];

    var_28 = 0;
    sub_D6460();
    sprintf(ebp_24, "GameEntity Pool %d", arg_0);
    if (arg_8)
    {
        unk_14.sub_16C2C0(arg_8, arg_4, ebp_24, 0x10, 0);
    }
    else
    {
        unk_14.sub_16C3E0();
    }
    unk_00 = arg_4;
    unk_04 = arg_8;
    unk_10 = 0;
    unk_0C = arg_0;
    var_28 = 1;
    unk_08 = var_28;
    return var_28;
}

// match: ?sub_D6550@type_4B83A0@@QAEXXZ @ 0x000D6550
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out: the body is empty and folded elsewhere (SP 0xA2172 calls the shared empty function)
void type_4B83A0::sub_D6550()
{
    if (unk_14.in_use())
    {
        sub_19A750("GameEntityPool:: %d was not empty at restart!", unk_0C);
    }
}
#endif

// match: ?sub_D65A0@type_4B83A0@@QAEXXZ @ 0x000D65A0
// sp-match: ?sub_D65A0@type_4B83A0@@QAEXXZ @ 0x000A22C0
void type_4B83A0::sub_D65A0()
{
    unk_14.sub_16C4D0(1);
    sub_D6460();
}

// match: ?sub_D65C0@type_4B83A0@@QAEPAXXZ @ 0x000D65C0
// sp-match: ?sub_D65C0@type_4B83A0@@QAEPAXXZ @ 0x000A22E0
void *type_4B83A0::sub_D65C0()
{
    void *var_4;

    var_4 = 0;
    var_4 = unk_14.sub_16C5A0(0);
    if (var_4)
    {
        unk_10++;
    }
    return var_4;
}

// match: ?sub_D6600@type_4B83A0@@QAEXPAX@Z @ 0x000D6600
// sp-match: ?sub_D6600@type_4B83A0@@QAEXPAX@Z @ 0x000A2300
void type_4B83A0::sub_D6600(void *arg_0)
{
    if (arg_0)
    {
        unk_14.sub_16C710(arg_0);
        unk_10--;
    }
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_4B85F8@@QAEXXZ (folded into the empty body at 0x1E41C0)
#ifndef CODFH_SP // single player keeps the calls (SP 0xA2157): the empty body is not in this object
void type_4B85F8::pDtor()
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_4B85F8@@QAE@XZ (folded into 0x1E41C0)
type_4B85F8::~type_4B85F8()
{
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
struct type_3D3548;
struct type_4B8600;
// 0x004B8600: dword_4B85F8 + 0x8
type_4B8600 (&dword_4B8600)[16] = *(type_4B8600 (*)[16])((RwUInt8 *)&dword_4B85F8 + 0x8);
// 0x004B8640: dword_4B85F8 + 0x48
type_3D3548 *&dword_4B8640 = *(type_3D3548 * *)((RwUInt8 *)&dword_4B85F8 + 0x48);
// 0x004B8690: dword_4B85F8 + 0x98
type_3D3548 *&dword_4B8690 = *(type_3D3548 * *)((RwUInt8 *)&dword_4B85F8 + 0x98);
// 0x004B86A0: dword_4B85F8 + 0xA8
type_3D3548 *&dword_4B86A0 = *(type_3D3548 * *)((RwUInt8 *)&dword_4B85F8 + 0xA8);
#endif
#endif
