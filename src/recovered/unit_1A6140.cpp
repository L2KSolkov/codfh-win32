// The network players (game/netplayer.h).

#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "game/netplayer.h"
#include "game/bombsites.h"
#include "game/mpgame.h"
#include "types/type_DC400.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E134C
extern const RwReal flt_3E134C = 0.01f;
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E1350
extern const RwReal flt_3E1350 = 0.01f;
// 0x003E1354
extern const RwReal flt_3E1354 = 16.666666f;
#endif
// 0x004F6AF8
#ifndef CODFH_PLAIN
RwReal flt_4F6AF8;
#endif
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E134C@@3MB @ 0x003E134C
// match: ?flt_3E1350@@3MB @ 0x003E1350
// match: ?flt_3E1354@@3MB @ 0x003E1354
// match: ??_7type_4F6B00@@6Btype_3E137C@@@ @ 0x003E1358
// match: ??_7type_4F6B00@@6Btype_3E1388@@@ @ 0x003E1364
// match: __real@41f80000 @ 0x003E1368
// match: ??_7type_1A7AA0@@6Btype_3E137C@@@ @ 0x003E136C
// match: ??_7type_1A7AA0@@6Btype_3E1388@@@ @ 0x003E1378
// match: ??_7type_3E137C@@6B@ @ 0x003E137C
// match: ??_7type_3E1388@@6B@ @ 0x003E1388
// match: __ehhandler$?vf_004@type_3E102C@@UAEXPAUtype_1F8560@@@Z>1>8 @ 0x0041EB38
// match: __ehhandler$?vf_004@type_3E102C@@UAEXPAUtype_1F8560@@@Z>1 @ 0x0041EB40
// match: .CRT$XCU+0 @ 0x004271B0
// match: .CRT$XCU+4 @ 0x004271B4
// match: .CRT$XCU+8 @ 0x004271B8
// match: .CRT$XCU+12 @ 0x004271BC
// match: .CRT$XCU+16 @ 0x004271C0

// match: _$E4 @ 0x0030C150
// match: _$E6 @ 0x0030C160
// match: _$E8 @ 0x0030C170
// match: _$E10 @ 0x0030C180
// match: _$E12 @ 0x0030C190

// Its frame's four unused slots are the base constructor's expansion,
// reserved though it is not inlined (docs/toolchain.md).
// match: ??0type_4F6B00@@QAE@XZ @ 0x001A6140
type_4F6B00::type_4F6B00()
    : type_1A7AA0(0, 200, 0), unk_60(0), unk_68(-1), unk_11C(0), unk_120(0), unk_128(0), unk_12C(0),
      unk_134(0)
{
    sub_1A7320();
}

// match: ?sub_1A62D0@type_4F6B00@@QAEXH@Z @ 0x001A62D0
void type_4F6B00::sub_1A62D0(RwInt32 arg_0)
{
    unk_68 = arg_0;
}

// match: ?sub_1A62F0@type_4F6B00@@QAEXXZ @ 0x001A62F0
void type_4F6B00::sub_1A62F0()
{
    sub_1A7320();
}

// match: ?sub_1A6310@type_4F6B00@@QAEXPAUtype_3E24E8@@@Z @ 0x001A6310
void type_4F6B00::sub_1A6310(type_3E24E8 *arg_0)
{
    // Compiled-out checks: the registers after them are two loads on
    // (docs/toolchain.md).
    if (!unk_11C)
    {
    }
    if (!unk_11C)
    {
    }
    unk_11C = arg_0;
    unk_11C->pvf_040(unk_68);
    if (0)
    {
        sub_15FB30(1);
        pDtor();
    }
}

// match: ?sub_1A6360@type_4F6B00@@QAEXXZ @ 0x001A6360
void type_4F6B00::sub_1A6360()
{
    // Compiled-out checks: the registers after them are two loads on
    // (docs/toolchain.md).
    if (!unk_11C)
    {
    }
    if (!unk_11C)
    {
    }
    unk_11C->pvf_040(-1);
    unk_11C = 0;
}

// match: ?sub_1A63A0@type_4F6B00@@QAEXPAUtype_1BABA0@@@Z @ 0x001A63A0
void type_4F6B00::sub_1A63A0(type_1BABA0 *arg_0)
{
    unk_124 = arg_0;
    if (unk_120)
        unk_120->pvf_008();
}

// match: ?sub_1A63E0@type_4F6B00@@QAEXXZ @ 0x001A63E0
void type_4F6B00::sub_1A63E0()
{
    // A compiled-out check: the registers after it are one load on
    // (docs/toolchain.md).
    if (!unk_120)
    {
    }
    unk_124 = 0;
    if (unk_120)
        unk_120->pvf_004();
}

// match: ?sub_1A6420@type_4F6B00@@QAEXPAUtype_4F6B00_120@@@Z @ 0x001A6420
void type_4F6B00::sub_1A6420(type_4F6B00_120 *arg_0)
{
    unk_120 = arg_0;
    unk_120->pvf_00C(unk_68);
    sub_1A7320();
}

// match: ?sub_1A6460@type_4F6B00@@QAEXXZ @ 0x001A6460
void type_4F6B00::sub_1A6460()
{
    unk_120->pvf_00C(-1);
    unk_120 = 0;
}

// match: ?sub_1A64A0@type_4F6B00@@QAEXABUtype_1CCA10@@@Z @ 0x001A64A0
void type_4F6B00::sub_1A64A0(const type_1CCA10 &arg_0)
{
    pDtor();
    if (is_driven())
    {
        sub_1A65B0(arg_0);
        return;
    }
    if (unk_20 && !unk_12C)
    {
        sub_1A7480(arg_0);
        if (is_shown())
            sub_1A6E80(arg_0);
        if (is_visible())
            sub_1A6F50();
    }
    if (0)
    {
        if (unk_128)
            sub_15FB30(arg_0);
        if (unk_12C)
            sub_15FB30(arg_0);
    }
    if (unk_134)
    {
        unk_4C &= ~1;
        unk_134 = 0;
    }
}

// match: ?sub_1A65B0@type_4F6B00@@QAEXABUtype_1CCA10@@@Z @ 0x001A65B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its step at the time arg_0 while driven: its interface steps; a jump in
// the height of the shared position marks it moved; a pending flag clears
// while its sent time is within the last 50 ms; unless moved and at rest with
// the state unchanged (angle, the two values, the facing and the seven
// flags), the state is copied in and taken (sub_1A7A60), else only once the
// resend time (dword_4F7E8C) is over; the sites' sections are kept (at most
// 31); then its position, velocity and facing are copied from the
// interface.
void type_4F6B00::sub_1A65B0(const type_1CCA10 &arg_0)
{
    RwUInt32 lv_10;
    RwReal var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    bp_8 = 0;
    // Compiled-out checks: the registers after them are two loads on
    // (docs/toolchain.md).
    if (!unk_11C)
    {
    }
    if (!unk_11C)
    {
    }
    unk_11C->pvf_000((RwInt32)&arg_0);
    var_C = flt_4F6AF8 - unk_11C->pvf_004()->unk_04;
    flt_4F6AF8 = unk_11C->pvf_004()->unk_04;
    if ((RwReal)fabs((RwDouble)var_C) > 0.02f)
        bp_8 = 1;
    if (unk_134)
    {
        RwInt32 ebp_14 = 50;
        type_1CCA10 y18 = arg_0 - ebp_14;

        if (unk_18 >= y18)
        {
            unk_4C &= ~1;
            unk_134 = 0;
        }
    }
    bp_4 = !(!bp_8 && unk_11C->pvf_008()->sub_1A6D70() && !(fabs(unk_11C->pvf_00C() - unk_3C) > 0.1f)
             && unk_11C->pvf_014() == unk_44 && unk_11C->pvf_018() == unk_48 && unk_11C->pvf_010() == unk_40
             && get_bit_4C(0) == unk_11C->pvf_01C() && get_bit_4C(1) == unk_11C->pvf_020()
             && get_bit_4C(2) == unk_11C->pvf_024() && get_bit_4C(3) == unk_11C->pvf_028()
             && get_bit_4C(4) == unk_11C->pvf_02C() && get_bit_4C(5) == unk_11C->pvf_030()
             && get_bit_4C(6) == unk_11C->pvf_034());
    if (bp_4)
    {
        unk_24 = *unk_11C->pvf_004();
        unk_30 = *unk_11C->pvf_008();
        unk_3C = unk_11C->pvf_00C();
        unk_40 = unk_11C->pvf_010();
        unk_44 = unk_11C->pvf_014();
        unk_48 = unk_11C->pvf_018();
        if ((unk_4C & 1) && !unk_11C->pvf_01C())
            unk_134 = 1;
        if (unk_11C->pvf_01C())
            set_bit_4C(0, 1);
        set_bit_4C(1, unk_11C->pvf_020());
        set_bit_4C(2, unk_11C->pvf_024());
        set_bit_4C(3, unk_11C->pvf_028());
        set_bit_4C(4, unk_11C->pvf_02C());
        set_bit_4C(5, unk_11C->pvf_030());
        set_bit_4C(6, unk_11C->pvf_034());
        sub_1A7A60(arg_0);
    }
    else
    {
        type_1CCA10 l1C = unk_64 + dword_4F7E8C;

        if (arg_0 > l1C)
            sub_1A7A60(arg_0);
    }
    for (lv_10 = 0; lv_10 < 4; lv_10++)
    {
        unk_50[lv_10] = dword_4E5D30[lv_10].get_unk_08();
        if (unk_50[lv_10] > 0x1F)
        {
            if (!unk_11C)
            {
            }
            unk_50[lv_10] = 0x1F;
        }
    }
    unk_D8 = *unk_11C->pvf_004();
    unk_E4 = *unk_11C->pvf_008();
    unk_F4 = unk_11C->pvf_00C();
    unk_F0_r = unk_11C->pvf_010();
}

// match: ?sub_1A6D70@type_1F8560_v@@QAEHXZ @ 0x001A6D70
RwInt32 type_1F8560_v::sub_1A6D70()
{
    return unk_00 < flt_3E134C && -flt_3E134C < unk_00 && unk_04 < flt_3E134C && -flt_3E134C < unk_04 &&
                   unk_08 < flt_3E134C && -flt_3E134C < unk_08
               ? 1
               : 0;
}

// match: ?sub_1A6E10@@YAMM@Z @ 0x001A6E10
RwReal sub_1A6E10(RwReal arg_0)
{
    RwReal var_4 = arg_0;

    if (var_4 < -180.0f || var_4 > 180.0f)
    {
        var_4 = var_4 + 180.0f;
        var_4 = (var_4 = (RwReal)fmod(var_4, 360.0f)) - 180.0f;
    }
    return var_4;
}

// match: ?sub_1A6E80@type_4F6B00@@QAEXABUtype_1CCA10@@@Z @ 0x001A6E80
void type_4F6B00::sub_1A6E80(const type_1CCA10 &arg_0)
{
    // Compiled-out checks: the registers after them are two loads on
    // (docs/toolchain.md).
    if (!unk_120)
    {
    }
    if (!unk_120)
    {
    }
    unk_120->pvf_000(&unk_D8, &unk_F4, &unk_E4, &unk_F0, &unk_44, &unk_48, &unk_4C, unk_50);
    if (0)
    {
        if (sub_1E4CB0())
            sub_1A7A90(&unk_D8, &unk_E4, unk_F4.unk_00, unk_F0, unk_44, unk_48, unk_4C, arg_0);
    }
}

// match: ?sub_1A6F50@type_4F6B00@@QAEXXZ @ 0x001A6F50
void type_4F6B00::sub_1A6F50()
{
    unk_124->pvf_000(&unk_D8, &unk_F4, &unk_E4, &unk_F0, &unk_44, &unk_48, &unk_4C, unk_50);
    unk_124->set_unk_1B3C(true);
}

// match: ?vf_000@type_4F6B00@@UAEXPAUtype_1F8560@@@Z @ 0x001A6FE0
void type_4F6B00::vf_000(type_1F8560 *arg_0)
{
    RwUInt32 var_4;

    arg_0->sub_1F85F0(unk_24.unk_00);
    arg_0->sub_1F85F0(unk_24.unk_04);
    arg_0->sub_1F85F0(unk_24.unk_08);
    arg_0->sub_1F85F0(unk_30.unk_00);
    arg_0->sub_1F85F0(unk_30.unk_04);
    arg_0->sub_1F85F0(unk_30.unk_08);
    arg_0->sub_1F85F0(unk_3C);
    arg_0->sub_1F85F0(unk_40);
    arg_0->sub_1F8860(unk_44, 8);
    arg_0->sub_1F8860(unk_48, 8);
    arg_0->sub_1F8860(unk_4C, 7);
    for (var_4 = 0; var_4 < 4; var_4++)
        arg_0->sub_1F8860(unk_50[var_4], 5);
}

// match: ?vf_004@type_4F6B00@@UAEXPAUtype_1F8560@@@Z @ 0x001A70D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F6B00::vf_004(type_1F8560 *arg_0)
{
    RwUInt32 var_8;
    RwUInt32 l4;

    unk_24.unk_00 = arg_0->sub_1F85A0();
    unk_24.unk_04 = arg_0->sub_1F85A0();
    unk_24.unk_08 = arg_0->sub_1F85A0();
    unk_30.unk_00 = arg_0->sub_1F85A0();
    unk_30.unk_04 = arg_0->sub_1F85A0();
    unk_30.unk_08 = arg_0->sub_1F85A0();
    unk_3C = arg_0->sub_1F85A0();
    unk_40 = arg_0->sub_1F85A0();
    unk_44 = arg_0->sub_1F8810(8);
    unk_48 = arg_0->sub_1F8810(8);
    l4 = arg_0->sub_1F8810(7);
    unk_4C = unk_4C & 1 | l4;
    if (unk_4C & 1 && !(l4 & 1))
        unk_134 = 1;
    for (var_8 = 0; var_8 < 4; var_8++)
        unk_50[var_8] = arg_0->sub_1F8810(5);
}

// match: ?sub_1A71E0@type_4F6B00@@QAEXXZ @ 0x001A71E0
void type_4F6B00::sub_1A71E0()
{
    if (!unk_20)
    {
        unk_D8 = unk_24;
        RwReal var_C = sub_1A6E10(unk_3C);

        unk_F4.unk_00 = var_C;
        // The frame keeps an unused slot below the blocks' locals (an
        // inline that expands to nothing; gameloop.h).
        unused_slot();
    }
    unk_20 = 1;
    type_1CCA10 var_4 = sub_1CCA10();
    const type_1CCA10 &local_8 = var_4;

    if (unk_60 > 0x20)
    {
        RwInt32 var_10 = local_8 - unk_58;

        unk_5C = (unk_5C * 31.0f + var_10 * 0.001f) / 32.0f;
    }
    else if (unk_60 > 0)
    {
        RwInt32 var_14 = local_8 - unk_58;

        unk_5C = (unk_60 * unk_5C + var_14 * 0.001f) / (unk_60 + 1);
    }
    unk_60++;
    unk_58 = local_8;
    unk_D4 = 2;
}

// match: ?sub_1A7320@type_4F6B00@@QAEXXZ @ 0x001A7320
void type_4F6B00::sub_1A7320()
{
    unk_20 = 0;
    unk_24 = type_1F8560_v();
    unk_30 = type_1F8560_v();
    unk_3C = 0;
    unk_40 = 0;
    unk_44 = 0;
    unk_48 = 0;
    unk_4C = 0;
    unk_D4 = 2;
    unk_D8 = type_1F8560_v();
    unk_E4 = type_1F8560_v();
    unk_F0 = 0;
    unk_58 = sub_1CCA10();
    unk_F8 = unk_58;
    unk_5C = dword_4F7E84 * 0.001f;
    unk_60 = 0;
}

// Follows the received motion curves and wraps the interpolated facing.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// match: ?sub_1A7480@type_4F6B00@@QAEXABUtype_1CCA10@@@Z @ 0x001A7480
void type_4F6B00::sub_1A7480(const type_1CCA10 &arg_0)
{
    type_4F6B00_F4 *var_C;
    RwReal r10;
    RwReal var_14;

    type_1CCA10 bp_18((RwInt32)(unk_5C * 1000.0f * 1.5f));
    type_1CCA10 bp_8 = unk_58 + bp_18;
    type_1CCA10 *bp_4 = &bp_8;
    type_1CCA10 t1C((RwInt32)(unk_5C * 1000.0f));
    type_1CCA10 fp_20 = *bp_4 + t1C;
    if (arg_0 > fp_20)
    {
        if (unk_D4 == 0 || unk_D4 == 1)
        {
            type_1F8560_v var_2C;

            unk_E4 = var_2C;
            unk_D4 = 2;
        }
    }
    else if (arg_0 > *bp_4)
    {
        unk_D4 = 2;
    }
    else if (unk_D4 == 1 || unk_D4 == 2)
    {
        RwReal var_30;

        unk_D4 = 0;
        unk_6C.sub_1FAF00(unk_D8, unk_E4, unk_F8.unk_00 * 0.001f, unk_24, unk_30, bp_4->unk_00 * 0.001f);
        var_30 = sub_1A6E10(unk_3C);
        var_14 = sub_1A6E10(unk_F4.delta(var_30));
        var_C = (type_4F6B00_F4 *)&var_14;
        r10 = unk_F4.get_unk_00() + var_C->get_unk_00();
        if (((RwReal)fabs(((RwReal)(r10 - unk_F4.get_unk_00())))) > 180.0f)
        {
            if (r10 > 0.0f)
            {
                RwReal var_34 = r10 - 360.0f;
                RwReal var_38 = unk_F4.get_unk_00();

                unk_FC.set(var_38, unk_F8.unk_00 * 0.001f, var_34, bp_4->unk_00 * 0.001f);
            }
            else
            {
                RwReal local_3C = r10 + 360.0f;
                RwReal bp_40 = unk_F4.get_unk_00();

                unk_FC.set(bp_40, unk_F8.unk_00 * 0.001f, local_3C, bp_4->unk_00 * 0.001f);
            }
        }
        else
        {
            RwReal bp_44 = unk_F4.get_unk_00();

            unk_FC.set(bp_44, unk_F8.unk_00 * 0.001f, r10, bp_4->unk_00 * 0.001f);
        }
        unk_10C.set(unk_F0_r, unk_F8.unk_00 * 0.001f, unk_40, bp_4->unk_00 * 0.001f);
    }
    switch (unk_D4)
    {
    case 0:
    case 1:
        {
            unk_D8 = unk_6C.sub_1FB250(arg_0.unk_00 * 0.001f);
            unk_E4 = unk_6C.sub_1FB2E0(arg_0.unk_00 * 0.001f);
            unk_F4 = unk_FC.sub_1A7B70(arg_0.unk_00 * 0.001f);
            unk_F0_r = unk_10C.sub_1A7B70(arg_0.unk_00 * 0.001f);
        }
        break;
    }
    unk_F8 = arg_0;
}

// match: ?sub_1A7A60@type_4F6B00@@QAEXABUtype_1CCA10@@@Z @ 0x001A7A60
void type_4F6B00::sub_1A7A60(const type_1CCA10 &arg_0)
{
    unk_64 = arg_0;
    unk_08 = 1;
}

// match: ?sub_1A7A90@type_4F6B00@@QAEXPAUtype_1F8560_v@@0MHHHIUtype_1CCA10@@@Z @ 0x001A7A90
void type_4F6B00::sub_1A7A90(type_1F8560_v *arg_0, type_1F8560_v *arg_4, RwReal arg_8, RwInt32 arg_C,
                             RwInt32 arg_10, RwInt32 arg_14, RwUInt32 arg_18, type_1CCA10 arg_1C)
{
}

// An inline defined here, not inlined: emitted at its definition, with its vtables
// (the image has them after sub_1A71E0's literals).
// match: ??0type_1A7AA0@@QAE@ABHHH@Z @ 0x001A7AA0
inline type_1A7AA0::type_1A7AA0(const RwInt32 &arg_0, RwInt32 arg_4, RwInt32 arg_8) : type_3E1388(arg_0, arg_4, arg_8)
{
}

// match: ?vf_000@type_1A7AA0@@UAEPAUtype_3DA44C@@XZ @ 0x001A7B40
type_3DA44C *type_1A7AA0::vf_000()
{
    return this;
}

// Inline in this unit: each call in sub_1A7480 retains four unused words
// for the two reference bindings, although VC7.1 keeps the call out of line.
// match: ?sub_1A7B70@type_1A7B70@@QAEMM@Z @ 0x001A7B70
inline RwReal type_1A7B70::sub_1A7B70(RwReal arg_0)
{
    if (arg_0 >= unk_0C)
        return unk_08;
    if (arg_0 <= unk_04)
        return unk_00;
    const RwReal &var_8 = unk_08 - unk_00;
    const RwReal &var_10 = unk_0C - unk_04;

    return (arg_0 - unk_04) / var_10 * var_8 + unk_00;
}

// match: ?vf_000@type_3E0FCC@@UAEXPAUtype_1F8560@@@Z @ 0x001A7BF0
void type_3E0FCC::vf_000(type_1F8560 *arg_0)
{
    arg_0->sub_1F87B0(unk_04, 8);
    arg_0->sub_1F8860(unk_08, 8);
    arg_0->sub_1F85F0(unk_0C.x);
    arg_0->sub_1F85F0(unk_0C.y);
    arg_0->sub_1F85F0(unk_0C.z);
    arg_0->sub_1F8860(unk_18, 8);
    arg_0->sub_1F8860(unk_1C, 8);
}

// match: ?vf_004@type_3E0FCC@@UAEXPAUtype_1F8560@@@Z @ 0x001A7C70
void type_3E0FCC::vf_004(type_1F8560 *arg_0)
{
    unk_04 = arg_0->sub_1F8750(8);
    unk_08 = arg_0->sub_1F8810(8);
    unk_0C.x = arg_0->sub_1F85A0();
    unk_0C.y = arg_0->sub_1F85A0();
    unk_0C.z = arg_0->sub_1F85A0();
    unk_18 = arg_0->sub_1F8810(8);
    unk_1C = arg_0->sub_1F8810(8);
}

// match: ?sub_1A7CF0@type_4F8184@@QAEXXZ @ 0x001A7CF0
void type_4F8184::sub_1A7CF0()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
    {
        unk_00[var_4].unk_00 = 0;
        unk_00[var_4].unk_04 = 0;
        unk_00[var_4].unk_10 = 0;
        unk_00[var_4].unk_0C = 0;
        unk_00[var_4].unk_08 = 0;
    }
    unk_B4 = 0;
}

// The locals' names state their slots (docs/toolchain.md).
// match: ?sub_1A7D80@type_4F8184@@QAEXHHPAURwV3d@@@Z @ 0x001A7D80
void type_4F8184::sub_1A7D80(RwInt32 arg_0, RwInt32 arg_4, RwV3d *arg_8)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwV3d var_C;

    if (arg_8)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_00[0].unk_00)
        {
        }
        var_C = *arg_8;
    }
    else
        var_C.x = var_C.y = var_C.z = 0;
    if (unk_4F61F8.unk_104)
    {
        type_3E0FCC var_30;

        var_30.unk_04 = arg_0;
        var_30.unk_08 = arg_4;
        var_30.unk_0C = var_C;
        var_30.unk_18 = unk_4F7EB8.sub_1AEC70();
        var_30.unk_1C = 0;
        type_1DDE20_mask var_10;

        // Two compiled-out checks (docs/toolchain.md): the registers after
        // them are two loads on.
        if (!unk_00[0].unk_00)
        {
        }
        if (!unk_00[0].unk_00)
        {
        }
        var_10.put(0);
        type_4F8058::get()->sub_1DDE20(&var_30, var_10);
    }
    else if (arg_4 != unk_00[arg_0].unk_00)
    {
        type_4F8184_site lv_54 = unk_00[arg_0];

        unk_00[arg_0].unk_00 = arg_4;
        if (arg_4 == 5)
            unk_00[arg_0].unk_0C = unk_00[arg_0].unk_14;
        else
            unk_00[arg_0].unk_0C = unk_4F7EB8.sub_1AEC70();
        unk_00[arg_0].unk_08 = unk_B4;
        unk_00[arg_0].unk_18 = var_C;
        if (arg_4 == 3 && lv_54.unk_00 != 4 && lv_54.unk_00 != 5 && lv_54.unk_00 != 6)
            unk_00[arg_0].unk_14 = unk_4F7EB8.sub_1AEC70();
        type_3E0FCC lv_74;

        lv_74.unk_04 = arg_0;
        lv_74.unk_08 = arg_4;
        lv_74.unk_0C = var_C;
        if (arg_4 == 5)
            lv_74.unk_18 = unk_00[arg_0].unk_14;
        else
            lv_74.unk_18 = unk_4F7EB8.sub_1AEC70();
        lv_74.unk_1C = ++unk_00[arg_0].unk_04;
        unk_4F7EB8.unk_04.sub_1B3190(arg_0, &lv_54, &unk_00[arg_0]);
        type_4F8058::get()->sub_1DDE20(&lv_74, type_4F8054::get()->get_unk_B0()->sub_1A8050());
    }
}

// Defined in its class (types/type_DC400.h), not inlined.
// match: ?sub_1A8050@type_4F8054_B0@@QAE?AUtype_1DDE20_mask@@XZ @ 0x001A8050

// A site's state from a peer (the handler sub_1AEB90). The host takes a
// newer one (its update count, unk_1C, above the site's): the state, the
// count, the player and the bomb's position, the bomb taken away when it
// is defused, and, unless it is its own, the site's state set without
// telling the manager (sub_1A4200) and its own defusing or planting there
// stopped. A client takes a changed state, like sub_1A7D80, and sends it on
// as its own copy.
// match: ?sub_1A80B0@type_4F8184@@QAEXPAUtype_3E0FCC@@@Z @ 0x001A80B0
void type_4F8184::sub_1A80B0(type_3E0FCC *arg_0)
{
    if (unk_4F61F8.unk_104)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_00[0].unk_00)
        {
        }
        if (arg_0->unk_1C > unk_00[arg_0->unk_04].unk_04)
        {
            unk_00[arg_0->unk_04].unk_00 = arg_0->unk_08;
            unk_00[arg_0->unk_04].unk_04 = arg_0->unk_1C;
            unk_00[arg_0->unk_04].unk_0C = arg_0->unk_18;
            unk_00[arg_0->unk_04].unk_18 = arg_0->unk_0C;
            if (arg_0->unk_08 == 5)
                dword_4F6950.sub_1A3E30(arg_0->unk_04);
            if (arg_0->unk_18 != unk_4F7EB8.sub_1AEC70())
            {
                dword_4F6950.sub_1A4200(arg_0->unk_04, arg_0->unk_08, arg_0->unk_18, &arg_0->unk_0C);
                if (unk_4F7EB8.get_unk_1A4())
                {
                    if (arg_0->unk_08 == 2)
                    {
                        if (unk_4F7EB8.get_unk_1A4()->defusing_at(arg_0->unk_04))
                            unk_4F7EB8.get_unk_1A4()->sub_1B8690();
                    }
                    if (arg_0->unk_08 == 4)
                    {
                        if (unk_4F7EB8.get_unk_1A4()->planting_at(arg_0->unk_04))
                            unk_4F7EB8.get_unk_1A4()->sub_1B87D0();
                    }
                }
            }
        }
    }
    else if (arg_0->unk_08 != unk_00[arg_0->unk_04].unk_00)
    {
        type_4F8184_site var_24 = unk_00[arg_0->unk_04];

        unk_00[arg_0->unk_04].unk_00 = arg_0->unk_08;
        unk_00[arg_0->unk_04].unk_0C = arg_0->unk_18;
        unk_00[arg_0->unk_04].unk_08 = unk_B4;
        unk_00[arg_0->unk_04].unk_18 = arg_0->unk_0C;
        if (arg_0->unk_08 == 3 && var_24.unk_00 != 4 && var_24.unk_00 != 5 && var_24.unk_00 != 6)
            unk_00[arg_0->unk_04].unk_14 = arg_0->unk_18;
        type_3E0FCC var_44(*arg_0);

        var_44.unk_1C = ++unk_00[arg_0->unk_04].unk_04;
        unk_4F7EB8.unk_04.sub_1B3190(arg_0->unk_04, &var_24, &unk_00[arg_0->unk_04]);
        type_4F8058::get()->sub_1DDE20(&var_44, type_4F8054::get()->get_unk_B0()->sub_1A8050());
        dword_4F6950.sub_1A4200(arg_0->unk_04, arg_0->unk_08, arg_0->unk_18, &arg_0->unk_0C);
    }
}

// The message's compiler-made copy constructor, out of line (sub_1A80B0
// sends its copy through it).
// match: ??0type_3E0FCC@@QAE@ABU0@@Z @ 0x001A8400

// match: ?sub_1A84A0@type_4F8184@@QAEXHH@Z @ 0x001A84A0
void type_4F8184::sub_1A84A0(RwInt32 arg_0, RwInt32 arg_4)
{
    // A compiled-out check: the registers after it are two loads on
    // (docs/toolchain.md).
    if (!unk_00[arg_0].unk_00)
    {
    }
    unk_00[arg_0].unk_10 = 30.0f;
}

// The bomb sites' step by arg_0 frames: unk_B4 counts the time in seconds;
// on a client each site in state 3 runs its timer down (sub_1A3E00 when it
// reaches 0), and a site in state 2 or 4 more than 30 after its unk_08 is
// set to state 0 or 3 (sub_1A41C0).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// match: ?sub_1A84C0@type_4F8184@@QAEXM@Z @ 0x001A84C0
void type_4F8184::sub_1A84C0(RwReal arg_0)
{
    RwInt32 var_8;
    RwReal l4;

    l4 = arg_0 / 60.0f;
    unk_B4 += l4;
    if (!unk_4F61F8.unk_104)
    {
        for (var_8 = 0; var_8 < 5; var_8++)
        {
            if (unk_00[var_8].unk_00 == 3 && unk_00[var_8].unk_10 > 0.0f)
            {
                unk_00[var_8].unk_10 = unk_00[var_8].unk_10 - l4;
                if (unk_00[var_8].unk_10 <= 0.0f)
                    dword_4F6950.sub_1A3E00(var_8);
            }
            if (unk_00[var_8].unk_00 == 2 || unk_00[var_8].unk_00 == 4)
            {
                // Two compiled-out checks (docs/toolchain.md): the registers
                // after them are two loads on.
                if (!unk_00[0].unk_00)
                {
                }
                if (!unk_00[0].unk_00)
                {
                }
                if (unk_B4 - unk_00[var_8].unk_08 > 30.0f)
                {
                    if (unk_00[var_8].unk_00 == 2)
                        dword_4F6950.sub_1A41C0(var_8, 0, -1, 0);
                    else if (unk_00[var_8].unk_00 == 4)
                        dword_4F6950.sub_1A41C0(var_8, 3, -1, 0);
                }
            }
        }
    }
}

// match: ?sub_1A8620@type_4F8184@@QAEHI@Z @ 0x001A8620
RwInt32 type_4F8184::sub_1A8620(RwUInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
    {
        if (unk_00[var_4].unk_0C == arg_0 && unk_00[var_4].unk_00 == 2)
            return 1;
    }
    return 0;
}

// match: ?sub_1A8680@type_4F8184@@QAEHI@Z @ 0x001A8680
RwInt32 type_4F8184::sub_1A8680(RwUInt32 arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
    {
        if (unk_00[var_4].unk_0C == arg_0 && unk_00[var_4].unk_00 == 4)
            return 1;
    }
    return 0;
}

// match: ?sub_1A86E0@type_4F8184@@QAEHI@Z @ 0x001A86E0
RwInt32 type_4F8184::sub_1A86E0(RwUInt32 arg_0)
{
    return sub_1A8620(arg_0) || sub_1A8680(arg_0);
}

// match: ?sub_1A8730@type_4F8184@@QAEXPAUtype_1F8560@@@Z @ 0x001A8730
void type_4F8184::sub_1A8730(type_1F8560 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
    {
        arg_0->sub_1F8860(unk_00[var_4].unk_04, 8);
        arg_0->sub_1F8860(unk_00[var_4].unk_00, 8);
        arg_0->sub_1F8860(unk_00[var_4].unk_0C, 8);
        arg_0->sub_1F85F0(unk_00[var_4].unk_18.x);
        arg_0->sub_1F85F0(unk_00[var_4].unk_18.y);
        arg_0->sub_1F85F0(unk_00[var_4].unk_18.z);
    }
}

// match: ?sub_1A87F0@type_4F8184@@QAEXPAUtype_1F8560@@@Z @ 0x001A87F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F8184::sub_1A87F0(type_1F8560 *arg_0)
{
    RwV3d var_1C;
    RwInt32 local_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    for (local_10 = 0; local_10 < 5; local_10++)
    {
        bp_4 = arg_0->sub_1F8810(8);
        var_C = arg_0->sub_1F8810(8);
        bp_8 = arg_0->sub_1F8810(8);
        var_1C.x = arg_0->sub_1F85A0();
        var_1C.y = arg_0->sub_1F85A0();
        var_1C.z = arg_0->sub_1F85A0();
        if (unk_00[local_10].unk_04 < bp_4)
        {
            unk_00[local_10].unk_04 = bp_4;
            unk_00[local_10].unk_00 = var_C;
            unk_00[local_10].unk_18 = var_1C;
            // A compiled-out check: the registers after it are two loads on
            // (docs/toolchain.md).
            if (!unk_00[local_10].unk_00)
            {
            }
            dword_4F6950.sub_1A4200(local_10, var_C, bp_8, &var_1C);
        }
    }
}

// match: ??1type_3E102C@@QAE@XZ @ 0x001A88E0
type_3E102C::~type_3E102C()
{
}

// match: ?vf_000@type_3E102C@@UAEXPAUtype_1F8560@@@Z @ 0x001A8910
void type_3E102C::vf_000(type_1F8560 *arg_0)
{
    RwInt32 var_4 = unk_04.size();

    if (var_4 > 0x80)
        var_4 = 0x80;
    arg_0->sub_1F8860(var_4, 8);
    arg_0->sub_1F89D0(unk_04.c_str(), var_4 << 3);
}

// Decodes the text through the original 128-byte buffer. VC7.1 rounds
// the array to eight-byte alignment; a 132-byte buffer enlarges the frame.
// match: ?vf_004@type_3E102C@@UAEXPAUtype_1F8560@@@Z @ 0x001A8990
// match: __ehhandler$?vf_004@type_3E102C@@UAEXPAUtype_1F8560@@@Z-0xB @ 0x00302970
// match: __ehhandler$?vf_004@type_3E102C@@UAEXPAUtype_1F8560@@@Z @ 0x0030297B
void type_3E102C::vf_004(type_1F8560 *arg_0)
{
    RwChar var_94[0x80];

    // Its length is block-scoped: it sits below the /GS array
    // (docs/toolchain.md).
    {
        RwUInt32 var_98 = arg_0->sub_1F8810(8);

        var_94[var_98] = 0;
        arg_0->sub_1F8A40(var_94, var_98 << 3);
    }
    unk_04 = var_94;
}

// The network timings (milliseconds). They have dynamic initializers, so
// their values come through an inline function, not constant expressions.
inline RwInt32 network_timing(RwInt32 arg_0)
{
    return arg_0;
}
RwInt32 dword_4F7E80 = network_timing(1000);
RwInt32 dword_4F7E84 = network_timing(500);
RwInt32 dword_4F7E8C = network_timing(500);
RwInt32 dword_4F7E88 = network_timing(100);

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_4F6B00@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_4F6B00::pDtor()
{
}

// ?sub_32260@type_4F6B00@@QAEHPAUtype_3E0F9C@@@Z (folded into `return 0` at 0x32260)
RwInt32 type_4F6B00::sub_32260(struct type_3E0F9C *arg_0)
{
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_73D90@type_4F6B00@@QAEXPACH@Z (folded into 0x73D90)
void type_4F6B00::sub_73D90(RwInt8 *arg_0, RwInt32 arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_15FB30@type_4F6B00@@QAEXH@Z (folded into 0x15FB30)
void type_4F6B00::sub_15FB30(RwInt32 arg_0)
{
}

// ?sub_15FB30@type_4F6B00@@QAEXUtype_1CCA10@@@Z (folded into 0x15FB30)
void type_4F6B00::sub_15FB30(struct type_1CCA10 arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E4CB0@type_4F6B00@@QAEHXZ (folded into 0x1E4CB0)
RwInt32 type_4F6B00::sub_1E4CB0()
{
        return 0;
    }

// ?vf_008@type_3E137C@@UAEHXZ (folded into 0x1E4CB0)
RwInt32 type_3E137C::vf_008()
{
        return 0;
    }

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text): the image's initializer list has this
// array's after this unit's other four (defined last, so initialized last).
type_4F6B00 unk_4F6B00[16];
