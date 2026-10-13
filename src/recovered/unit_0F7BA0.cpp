// The path-node manager (include/game/pathnodes.h). The original file name
// is not in the image (it likely sits beside astarpathfinder.cpp, whose set-up
// this unit's sub_F7F60 calls), so it is named for its start address.

#include <math.h>
#include <xmmintrin.h>

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/bavector.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/astarpathfinder.h"
#include "game/pathnodes.h"
#include "types/AIData.h"
#include "types/asynchload.h"
#include "types/type_3CE1FC.h"
#include "types/type_3D3548.h"
#include "types/type_4E5D30.h"
#include "types/type_72810.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004C0150
type_4C00D0 dword_4C0150;
// 0x004C0154
#ifndef CODFH_PLAIN
RwUInt32 dword_4C0154;
#endif
// 0x004C0158
#ifndef CODFH_PLAIN
RwUInt32 dword_4C0158;
#endif
// 0x004C015C
#ifndef CODFH_PLAIN
RwUInt32 dword_4C015C;
#endif
// 0x004C09A0
RwUInt32 dword_4C09A0;
// 0x004C09A4
RwUInt32 dword_4C09A4;
// 0x003D947C (the frame time: an object's constants open with it)
extern const RwReal flt_3D947C = 16.666666f;
// 0x003D9480
extern const RwReal flt_3D9480 = 2000.0f;
// 0x003D9484
extern const RwReal flt_3D9484 = 1000.0f;
// 0x003D9488 (AIData reads it too, unit_022C80: external)
extern const RwReal flt_3D9488 = 500.0f;
#ifndef CODFH_SP // single player writes the literal (an immediate, SP 0xBE19A): 500.0f is followed by the x axis (SP 0x2E5940)
// 0x003D948C
extern const RwReal flt_3D948C = 7984.2104f;
#endif
// 0x003D9490
extern const RwV3d unk_3D9490 = { 1.0f, 0.0f, 0.0f };
// 0x003D949C
extern const RwV3d unk_3D949C = { 0.0f, 1.0f, 0.0f };
// 0x003D94A8
extern const RwV3d unk_3D94A8 = { 0.0f, 0.0f, 1.0f };
// 0x004C0198: the distance the AI search's rescoring (AIData::sub_23F60) keeps its results
// beyond, a copy of flt_3D9488 made when the program starts (the first of the unit's
// initializers; its .bss sits among the unit's).
RwReal flt_4C0198 = flt_3D9488;

// match: ?flt_3D947C@@3MB @ 0x003D947C
// match: ?flt_3D9480@@3MB @ 0x003D9480
// match: ?flt_3D9484@@3MB @ 0x003D9484
// match: ?flt_3D9488@@3MB @ 0x003D9488
// match: ?flt_3D948C@@3MB @ 0x003D948C
// match: ?unk_3D9490@@3URwV3d@@B @ 0x003D9490
// match: ?unk_3D949C@@3URwV3d@@B @ 0x003D949C
// match: ?unk_3D94A8@@3URwV3d@@B @ 0x003D94A8
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
alfahash dword_4C0164;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?sub_F7BA0@@YAHPAUAIData@@PAUtype_F8350@@_N@Z>1>8 @ 0x0041D0E4
// match: __ehhandler$?sub_F7BA0@@YAHPAUAIData@@PAUtype_F8350@@_N@Z>1 @ 0x0041D0EC
// match: __ehhandler$?sub_F8D30@@YAHHHPAUtype_154C0_1048@@HH@Z>1>8 @ 0x0041D108
// match: __ehhandler$?sub_F8D30@@YAHHHPAUtype_154C0_1048@@HH@Z>1 @ 0x0041D110
// match: __ehhandler$?sub_FA650@@YAPAUtype_F8350@@PAU1@@Z>1>8 @ 0x0041D12C
// match: __ehhandler$?sub_FA650@@YAPAUtype_F8350@@PAU1@@Z>1 @ 0x0041D134
// match: .CRT$XCU+0 @ 0x00427080
// match: .CRT$XCU+4 @ 0x00427084
// match: .CRT$XCU+8 @ 0x00427088

// match: _$E2 @ 0x0030B6E0
// match: _$E4 @ 0x0030B6F0
// match: _$E5 @ 0x0030E590
// match: _$E7 @ 0x0030B710
// match: _$E8 @ 0x0030E5A0
// sp-match: _$E8 @ 0x0021E930
// sp-match: _$E4 @ 0x0021D760
// sp-match: _$E7 @ 0x0021D780
// sp-match: _$E5 @ 0x0021E920

// The occupied alarm nodes (their dynamic initializer builds them with the
// out-of-line copy of the constructor; its exit function destroys them).
type_4C01A0 dword_4C01A0[OCCUPIED_NODES];

// match: ?sub_F7BA0@@YAHPAUAIData@@PAUtype_F8350@@_N@Z @ 0x000F7BA0
// match: __ehhandler$?sub_F7BA0@@YAHPAUAIData@@PAUtype_F8350@@_N@Z-0x8 @ 0x00301110
// match: __ehhandler$?sub_F7BA0@@YAHPAUAIData@@PAUtype_F8350@@_N@Z @ 0x00301118
// sp-match: ?sub_F7BA0@@YAHPAUAIData@@PAUtype_F8350@@_N@Z @ 0x000BDAB0
// Local names state their slots.
RwInt32 sub_F7BA0(AIData *arg_0, type_F8350 *arg_4, bool arg_8)
{
    type_4C01A0 *ebp_14;
    RwInt32 q28 = 1;
    type_3D3548 *lv_10 = 0;
    type_3D3548 *var2c = 0;
    type_4C01A0 frm_24;
    RwInt32 var30;

    frm_24.unk_00 = sub_FA920(arg_4);
    ebp_14 = (type_4C01A0 *)dword_4C0164.sub_67970(&frm_24);
    if (ebp_14)
    {
        lv_10 = ebp_14->unk_04.sub_D4910();
    }
    if (arg_0)
    {
        var2c = arg_0->unk_568;
        if (lv_10 && lv_10 != var2c)
        {
            return 0;
        }
        if (!lv_10 && !arg_8)
        {
            return 0;
        }
        frm_24.unk_04.sub_D48D0(var2c);
        if (ebp_14 && arg_8)
        {
            ebp_14->unk_04.sub_D48D0(var2c);
        }
        // A check compiled out of this build (it moves the registers one step).
        if (arg_0->unk_568)
        {
        }
    }
    else
    {
        frm_24.unk_04.sub_D48D0(0);
        if (ebp_14 && arg_8)
        {
            ebp_14->unk_04.sub_D48D0(0);
        }
    }
    if (ebp_14)
    {
    }
    arg_4->unk_00_2 = arg_8;
    if (ebp_14)
    {
        if (!arg_8)
        {
            dword_4C01A0[ebp_14->unk_0C].unk_08 = 0;
            dword_4C0164.sub_678C0(&dword_4C01A0[ebp_14->unk_0C]);
        }
    }
    else if (arg_8)
    {
        for (var30 = 0; var30 < OCCUPIED_NODES; var30++)
        {
            if (!dword_4C01A0[var30].unk_08)
            {
                frm_24.unk_0C = var30;
                frm_24.unk_08 = 1;
                dword_4C01A0[var30] = frm_24;
                break;
            }
        }
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
        // (the port's debug tools: a full table takes no more, as the image would write past it)
        if (var30 == OCCUPIED_NODES)
            return q28;
#endif
        dword_4C0164.sub_67850(&dword_4C01A0[var30]);
    }
    return q28;
}

// match: ?sub_F7DC0@@YAXXZ @ 0x000F7DC0
// sp-match: ?sub_F7DC0@@YAXXZ @ 0x000BCA20
void sub_F7DC0()
{
    RwInt32 var_4;

    dword_4C0164.sub_67780();
    for (var_4 = 0; var_4 < OCCUPIED_NODES; var_4++)
    {
        dword_4C01A0[var_4].unk_04.sub_D48D0(0);
        dword_4C01A0[var_4].unk_00 = 0;
        dword_4C01A0[var_4].unk_08 = 0;
        dword_4C01A0[var_4].unk_0C = var_4;
    }
    dword_4C0164.sub_67730(OCCUPIED_NODES, 0x20, sub_F7E50, sub_F7E60);
}

// match: ?sub_F7E50@@YAIPAX@Z @ 0x000F7E50
// sp-match: ?sub_F7E50@@YAIPAX@Z @ 0x000BC9F0
RwUInt32 sub_F7E50(void *arg_0)
{
    return ((type_4C01A0 *)arg_0)->unk_00;
}

// match: ?sub_F7E60@@YA_NPAX0@Z @ 0x000F7E60
// sp-match: ?sub_F7E60@@YA_NPAX0@Z @ 0x000BCA00
bool sub_F7E60(void *arg_0, void *arg_4)
{
    return ((type_4C01A0 *)arg_0)->unk_00 == ((type_4C01A0 *)arg_4)->unk_00;
}

// match: ?sub_F7E80@@YAP6AHPAUtype_F8350@@HPAUtype_154C0_1048@@M@ZH@Z @ 0x000F7E80
// sp-match: ?sub_F7E80@@YAP6AHPAUtype_F8350@@HPAUtype_154C0_1048@@M@ZH@Z @ 0x000BE2D0
type_F93D0 sub_F7E80(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        return sub_F93D0;
    case 1:
        return sub_F9820;
    case 2:
        return sub_F9AA0;
    case 3:
        return sub_F9C80;
    case 4:
        return sub_FA260;
    case 5:
        return sub_FA440;
    case 14:
        return sub_FA470;
    case 6:
        return sub_FA570;
    case 7:
        return sub_F97F0;
    case 8:
        return sub_F9A70;
    case 9:
        return sub_F9440;
    case 10:
        return sub_F9780;
    case 11:
        return sub_F9710;
    case 12:
        return sub_F9750;
    case 13:
        return sub_FA330;
    case 15:
        return sub_FA5D0;
    case 16:
        return sub_F9DA0;
    }
    return 0;
}

// match: ?sub_F7F60@@YAXXZ @ 0x000F7F60
// sp-match: ?sub_F7F60@@YAXXZ @ 0x000BE390
void sub_F7F60()
{
    RwInt32 var_4;

    if (!unk_4C00E8.unk_60)
    {
        sub_F8160();
        sub_F5F10();
        unk_4C00E8.unk_60 = 1;
        for (var_4 = 0; var_4 < OCCUPIED_NODES; var_4++)
        {
            dword_4C01A0[var_4].unk_04.sub_D48D0(0);
            dword_4C01A0[var_4].unk_00 = 0;
            dword_4C01A0[var_4].unk_08 = 0;
            dword_4C01A0[var_4].unk_0C = var_4;
        }
        dword_4C0164.sub_67730(OCCUPIED_NODES, 0x20, sub_F7E50, sub_F7E60);
    }
}

// match: ?sub_F8010@@YAXXZ @ 0x000F8010
// sp-match: ?sub_F8010@@YAXXZ @ 0x000BCA80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F8010()
{
    type_F8350 *bp_8;
    RwUInt32 bp_4;

    if (unk_4C00E8.unk_60)
    {
        sub_F5FE0();
        if (unk_4C00E8.unk_64)
        {
            for (bp_4 = 1; bp_4 < unk_4C00E8.unk_08; bp_4++)
            {
                bp_8 = unk_4C00E8.unk_2C[bp_4];
                bp_8->unk_00_2 = 0;
                bp_8->unk_00_7 = 0;
                bp_8->unk_08 = 0;
                bp_8->unk_0C = 0;
                if (bp_8->unk_00_12 && (bp_8->unk_04 == 7 || bp_8->unk_04 == 4))
                {
                    bp_8->unk_04 = 7;
                    bp_8->unk_00_8 = 0;
                }
                else if (bp_8->unk_00_12 && (bp_8->unk_04 == 8 || bp_8->unk_04 == 3))
                {
                    bp_8->unk_04 = 8;
                    bp_8->unk_00_8 = 0;
                }
            }
            sub_F7DC0();
        }
    }
}

// match: ?sub_F8120@@YAXXZ @ 0x000F8120
// sp-match: ?sub_F8120@@YAXXZ @ 0x000BDC20
void sub_F8120()
{
    if (unk_4C00E8.unk_60)
    {
        sub_F6030();
        sub_F8270();
        dword_4C0164.sub_67780();
        unk_4C00E8.unk_60 = 0;
        unk_4C00E8.unk_64 = 0;
    }
}

// match: ?sub_F8160@@YAXXZ @ 0x000F8160
// sp-match: ?sub_F8160@@YAXXZ @ 0x000BDC60
void sub_F8160()
{
    sub_F8180();
    unk_4C00E8.unk_64 = 0;
}

// match: ?sub_F8180@@YAXXZ @ 0x000F8180
// sp-match: ?sub_F8180@@YAXXZ @ 0x000BCB30
void sub_F8180()
{
    unk_4C00E8.unk_04 = 0;
    unk_4C00E8.unk_08 = 0;
    unk_4C00E8.unk_18.x = 0.0f;
    unk_4C00E8.unk_18.y = 0.0f;
    unk_4C00E8.unk_18.z = 0.0f;
    unk_4C00E8.unk_0C = 0;
    unk_4C00E8.unk_10 = 0;
    unk_4C00E8.unk_14 = 0;
    unk_4C00E8.unk_24 = 0;
    unk_4C00E8.unk_28 = 0;
    unk_4C00E8.unk_2C = 0;
    unk_4C00E8.unk_30 = 0;
    unk_4C00E8.unk_34 = 0;
    unk_4C00E8.unk_38 = 0;
    unk_4C00E8.unk_3C = 0;
    unk_4C00E8.unk_40 = 0;
    unk_4C00E8.unk_44 = 0;
    unk_4C00E8.unk_48 = 0;
    unk_4C00E8.unk_4C = 0;
    unk_4C00E8.unk_50 = 0;
    unk_4C00E8.unk_54 = 0;
    unk_4C00E8.unk_58 = 0;
    unk_4C00E8.unk_5C = 0;
}

// match: ?sub_F8270@@YAXXZ @ 0x000F8270
// sp-match: ?sub_F8270@@YAXXZ @ 0x000BCBB0
void sub_F8270()
{
    if (unk_4C00E8.unk_2C)
    {
        operator delete(unk_4C00E8.unk_2C);
        unk_4C00E8.unk_2C = 0;
    }
    if (unk_4C00E8.unk_34)
    {
        operator delete(unk_4C00E8.unk_34);
        unk_4C00E8.unk_34 = 0;
    }
    if (unk_4C00E8.unk_3C)
    {
        operator delete(unk_4C00E8.unk_3C);
        unk_4C00E8.unk_3C = 0;
    }
    if (unk_4C00E8.unk_48)
    {
        operator delete(unk_4C00E8.unk_48);
        unk_4C00E8.unk_48 = 0;
    }
    if (unk_4C00E8.unk_50)
    {
        operator delete(unk_4C00E8.unk_50);
        unk_4C00E8.unk_50 = 0;
    }
    if (unk_4C00E8.unk_58)
    {
        operator delete(unk_4C00E8.unk_58);
        unk_4C00E8.unk_58 = 0;
    }
    sub_F8180();
    unk_4C00E8.unk_64 = 0;
}

// match: ?sub_F8350@@YAXPAURwStream@@@Z @ 0x000F8350
// sp-match: ?sub_F8350@@YAXPAURwStream@@@Z @ 0x000BDC70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F8350(RwStream *arg_0)
{
    type_F8350 *w48;
    type_73050 loc44;
    RwInt32 ebp_3C;
    RwUInt32 lcl_38;
    RwUInt32 r34;
    RwUInt8 *lv_30;
    RwUInt32 **fp_2C;
    RwUInt32 *q28;
    RwUInt32 frm_24;
    type_F8350 *t20;
    RwUInt32 *l1C;
    RwUInt32 m_18;
    RwChunkHeaderInfo ebp_14;

    sub_F8270();
    RwStreamReadChunkHeaderInfo(arg_0, &ebp_14);
    if (ebp_14.type == 1)
    {
        RwStreamRead(arg_0, &unk_4C00E8, ebp_14.length);
    }
    RwStreamReadChunkHeaderInfo(arg_0, &ebp_14);
    if (ebp_14.type == 1)
    {
        unk_4C00E8.unk_2C = (type_F8350 **)RWSMalloc(ebp_14.length, 0x34250); // not an address: an allocation tag
        if (unk_4C00E8.unk_2C)
        {
            RwStreamRead(arg_0, unk_4C00E8.unk_2C, ebp_14.length);
        }
    }
    RwStreamReadChunkHeaderInfo(arg_0, &ebp_14);
    if (ebp_14.type == 1)
    {
        unk_4C00E8.unk_34 = (RwUInt8 *)RWSMalloc(ebp_14.length, 0x34250); // not an address: an allocation tag
        if (unk_4C00E8.unk_34)
        {
            RwStreamRead(arg_0, unk_4C00E8.unk_34, ebp_14.length);
        }
    }
    RwStreamReadChunkHeaderInfo(arg_0, &ebp_14);
    if (ebp_14.type == 1)
    {
        unk_4C00E8.unk_3C = (RwUInt16 *)RWSMalloc(ebp_14.length, 0x34250); // not an address: an allocation tag
        if (unk_4C00E8.unk_3C)
        {
            RwStreamRead(arg_0, unk_4C00E8.unk_3C, ebp_14.length);
        }
    }
    RwStreamReadChunkHeaderInfo(arg_0, &ebp_14);
    if (ebp_14.type == 1)
    {
        unk_4C00E8.unk_48 = (RwUInt32 **)RWSMalloc(ebp_14.length, 0x34250); // not an address: an allocation tag
        if (unk_4C00E8.unk_48)
        {
            RwStreamRead(arg_0, unk_4C00E8.unk_48, ebp_14.length);
        }
    }
    RwStreamReadChunkHeaderInfo(arg_0, &ebp_14);
    if (ebp_14.type == 1)
    {
        unk_4C00E8.unk_50 = (RwUInt8 *)RWSMalloc(ebp_14.length, 0x34250); // not an address: an allocation tag
        if (unk_4C00E8.unk_50)
        {
            RwStreamRead(arg_0, unk_4C00E8.unk_50, ebp_14.length);
        }
    }
    if (unk_4C00E8.unk_5C > 0)
    {
        RwStreamReadChunkHeaderInfo(arg_0, &ebp_14);
        if (unk_4C00E8.unk_5C && ebp_14.type == 1)
        {
            unk_4C00E8.unk_58 = (RwUInt8 *)RWSMalloc(ebp_14.length, 0x34250); // not an address: an allocation tag
            if (unk_4C00E8.unk_58)
            {
                RwStreamRead(arg_0, unk_4C00E8.unk_58, ebp_14.length);
            }
        }
    }
    unk_4C00E8.unk_2C[0] = 0;
    for (m_18 = 1; m_18 < unk_4C00E8.unk_08; m_18++)
    {
        unk_4C00E8.unk_2C[m_18] = (type_F8350 *)(unk_4C00E8.unk_34 + (RwUInt32)unk_4C00E8.unk_2C[m_18]);
        t20 = unk_4C00E8.unk_2C[m_18];
        l1C = t20->unk_1C_links;
        if (t20->unk_00 & 1)
        {
            l1C = t20->unk_2C;
        }
        if (t20->unk_04 == 0x11)
        {
            sub_F7BA0(0, t20, true);
        }
        t20->unk_08 = 0;
        t20->unk_0C = 0;
        t20->unk_00_2 = 0;
        t20->unk_00_7 = 0;
        while (1)
        {
            if (!(*l1C & 0xFFF) || !(*l1C >> 12 & 0xFFF))
            {
                break;
            }
            l1C++;
        }
    }
    for (frm_24 = 0; frm_24 < unk_4C00E8.unk_44; frm_24++)
    {
        fp_2C = &unk_4C00E8.unk_48[frm_24];
        *fp_2C = (RwUInt32 *)(unk_4C00E8.unk_50 + (RwUInt32)*fp_2C);
        q28 = *fp_2C;
        while (1)
        {
            if (!(*q28 & 0xFFF) || !(*q28 >> 12 & 0xFFF))
            {
                break;
            }
            q28++;
        }
    }
    if (unk_4C00E8.unk_5C > 0)
    {
        lv_30 = unk_4C00E8.unk_58;
        r34 = 0xC;
        for (lcl_38 = 0; lcl_38 < unk_4C00E8.unk_5C; lcl_38 += r34)
        {
#ifdef CODFH_SP
            // shape: the record copied into a loop-scoped local, so /O2 loads both
            // halves before storing them (SP 0xBDF35)
            type_73050 loc44 = *(type_73050 *)lv_30;
#else
            loc44 = *(type_73050 *)lv_30;
#endif
            lv_30 += 8;
            ebp_3C = *(RwInt32 *)lv_30;
            lv_30 += 4;
            w48 = unk_4C00E8.unk_2C[ebp_3C];
            sub_198900((type_3DF8D8_04 *)&loc44, 0x2E, (void (*)(RwInt32, RwInt32, RwInt32))sub_FA620, 0, (RwInt32)w48, 0);
        }
    }
    unk_4C00E8.unk_64 = 1;
}

// match: ?sub_F8770@@YAHPAURwV3d@@PAH1@Z @ 0x000F8770
// sp-match: ?sub_F8770@@YAHPAURwV3d@@PAH1@Z @ 0x000BCC50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F8770(RwV3d *arg_0, RwInt32 *arg_4, RwInt32 *arg_8)
{
    RwReal lv_10;
    RwInt32 slot_C;
    RwReal bp_8;
    RwInt32 bp_4;

    bp_8 = arg_0->x - unk_4C00E8.unk_18.x;
    lv_10 = arg_0->z - unk_4C00E8.unk_18.z;
    if (!unk_4C00E8.unk_04)
    {
        return -1;
    }
    slot_C = (RwInt32)bp_8 / unk_4C00E8.unk_04;
    bp_4 = (RwInt32)lv_10 / unk_4C00E8.unk_04;
    *arg_4 = slot_C;
    *arg_8 = bp_4;
    if (slot_C < 0 || slot_C >= unk_4C00E8.unk_24)
    {
        return -1;
    }
    if (bp_4 < 0 || bp_4 >= unk_4C00E8.unk_28)
    {
        return -1;
    }
    return bp_4 * unk_4C00E8.unk_24 + slot_C;
}

// match: ?sub_F8820@@YAHPAURwV3d@@MPAHH@Z @ 0x000F8820
// sp-match: ?sub_F8820@@YAHPAURwV3d@@MPAHH@Z @ 0x000BCCC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F8820(RwV3d *arg_0, RwReal arg_4, RwInt32 *arg_8, RwInt32 arg_C)
{
    RwInt32 frm_30;
    RwV3d stk_2C;
    RwInt32 t20;
    RwInt32 l1C;
    RwV3d m_18;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    t20 = unk_4C00E8.unk_24;
    bp_8 = unk_4C00E8.unk_28;
    if (t20 <= 0 || bp_8 <= 0)
    {
        return 0;
    }
    m_18.x = arg_0->x - arg_4;
    m_18.y = arg_0->y;
    m_18.z = arg_0->z - arg_4;
    stk_2C.x = arg_4 + arg_0->x;
    stk_2C.y = arg_0->y;
    stk_2C.z = arg_4 + arg_0->z;
    sub_F8770(&m_18, &slot_C, &frm_30);
    sub_F8770(&stk_2C, &l1C, &bp_4);
    arg_8[0] = slot_C;
    arg_8[1] = frm_30;
    arg_8[2] = l1C;
    arg_8[3] = bp_4;
    if (l1C < 0 || slot_C >= t20)
    {
        return 0;
    }
    if (bp_4 < 0 || frm_30 >= bp_8)
    {
        return 0;
    }
    if (!arg_C)
    {
        if (slot_C < 0)
        {
            slot_C = 0;
        }
        if (l1C >= t20)
        {
            l1C = t20 - 1;
        }
        if (frm_30 < 0)
        {
            frm_30 = 0;
        }
        if (bp_4 >= bp_8)
        {
            bp_4 = bp_8 - 1;
        }
    }
    arg_8[0] = slot_C;
    arg_8[1] = frm_30;
    arg_8[2] = l1C;
    arg_8[3] = bp_4;
    return 1;
}

// match: ?sub_F8970@@YAPAUtype_F8350@@PAUtype_154C0_1048@@HH@Z @ 0x000F8970
// sp-match: ?sub_F8970@@YAPAUtype_F8350@@PAUtype_154C0_1048@@HH@Z @ 0x000BE400
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_F8350 *sub_F8970(type_154C0_1048 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 lcl_50;
    RwInt32 var_4C;
    RwInt32 frm_48;
    RwInt32 w44;
    RwInt32 s40;
    RwInt32 w3C;
    RwInt32 var_38;
    RwInt32 l34;
    RwInt32 o30;
    RwInt32 ebp_2C;
    RwReal lcl_28;
    RwInt32 w24;
    RwInt32 loc20[4];
    RwReal lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    dword_4C0154++;
    if (dword_4C0154 > dword_4C0158)
    {
        dword_4C0158 = dword_4C0154;
    }
    arg_0->unk_34 = 0;
    arg_0->unk_58 = 1e18f;
    arg_0->unk_3C = 1e18f;
    arg_0->unk_38 = 0;
    arg_0->unk_4C = 0;
    arg_0->unk_50 = 0;
    arg_0->unk_54 = 0;
    if (!unk_4C00E8.unk_64)
    {
        return 0;
    }
    dword_4C09A4 = RWS::Time::GetTime();
    lcl_28 = (RwReal)(RwUInt32)unk_4C00E8.unk_04;
    ebp_2C = unk_4C00E8.unk_24;
    w24 = unk_4C00E8.unk_28;
    lv_10 = arg_0->unk_10;
    slot_C = 0;
    arg_0->unk_5C = arg_0->unk_10 * arg_0->unk_10;
    if (!arg_0->unk_18)
    {
        arg_0->unk_18 = sub_F93D0;
    }
    if (lv_10 < lcl_28)
    {
        lv_10 = lcl_28;
    }
    sub_F8770(&arg_0->unk_04, &bp_8, &bp_4);
    sub_F8820(&arg_0->unk_04, lv_10, loc20, 1);
    if (loc20[1] < 0)
    {
        loc20[1] = 0;
    }
    if (loc20[3] >= w24)
    {
        loc20[3] = w24 - 1;
    }
    if (loc20[0] < 0)
    {
        loc20[0] = 0;
    }
    if (loc20[2] >= ebp_2C)
    {
        loc20[2] = ebp_2C - 1;
    }
    o30 = 0;
    while (arg_0->unk_1C || !arg_0->unk_34 || arg_0->unk_34 && o30 < 2)
    {
        var_38 = bp_8 - slot_C;
        s40 = bp_4 - slot_C;
        w3C = bp_8 + slot_C;
        l34 = bp_4 + slot_C;
        if (s40 < loc20[1] && l34 > loc20[3] && var_38 < loc20[0] && w3C > loc20[2])
        {
            break;
        }
        if (s40 >= loc20[1] && l34 <= loc20[3])
        {
            for (w44 = -slot_C; w44 <= slot_C; w44++)
            {
                frm_48 = bp_8 + w44;
                if (frm_48 <= loc20[2] && frm_48 >= loc20[0])
                {
                    if (s40 >= loc20[1] && !sub_F8D30(frm_48, s40, arg_0, arg_4, arg_8))
                    {
                        return arg_0->unk_34;
                    }
                    if (s40 != l34 && l34 <= loc20[3] && !sub_F8D30(frm_48, l34, arg_0, arg_4, arg_8))
                    {
                        return arg_0->unk_34;
                    }
                }
            }
        }
        if (var_38 >= loc20[0] && w3C <= loc20[2])
        {
            for (var_4C = -slot_C + 1; var_4C <= slot_C - 1; var_4C++)
            {
                lcl_50 = bp_4 + var_4C;
                if (lcl_50 <= loc20[3] && lcl_50 >= loc20[1])
                {
                    if (var_38 >= loc20[0] && !sub_F8D30(var_38, lcl_50, arg_0, arg_4, arg_8))
                    {
                        return arg_0->unk_34;
                    }
                    if (var_38 != w3C && w3C <= loc20[2] && !sub_F8D30(w3C, lcl_50, arg_0, arg_4, arg_8))
                    {
                        return arg_0->unk_34;
                    }
                }
            }
        }
        if (arg_0->unk_34)
        {
            o30++;
        }
        slot_C++;
    }
    dword_4C09A0 = RWS::Time::GetTime() - dword_4C09A4;
    dword_4C015C += dword_4C09A0;
    return arg_0->unk_34;
}

// match: ?sub_F8D30@@YAHHHPAUtype_154C0_1048@@HH@Z @ 0x000F8D30
// match: __ehhandler$?sub_F8D30@@YAHHHPAUtype_154C0_1048@@HH@Z-0x8 @ 0x00301130
// match: __ehhandler$?sub_F8D30@@YAHHHPAUtype_154C0_1048@@HH@Z @ 0x00301138
// sp-match: ?sub_F8D30@@YAHHHPAUtype_154C0_1048@@HH@Z @ 0x000BDFA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F8D30(RwInt32 arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    RwV3d frm_24;
    RwReal m_18;
    RwInt32 ebp_14;
    RwUInt16 lv_10;

    ebp_14 = arg_4 * unk_4C00E8.unk_24 + arg_0;
    lv_10 = unk_4C00E8.unk_3C[ebp_14];
    if (lv_10 != 0xFFFF)
    {
        RwInt32 w48;
        type_F8350 *loc44;
        RwUInt32 **fp_40;
        RwUInt32 *ebp_3C;

        fp_40 = &unk_4C00E8.unk_48[lv_10];
        ebp_3C = *fp_40;
        type_3CE1FC lcl_38(ebp_3C);
        while (!lcl_38.at_end())
        {
            loc44 = unk_4C00E8.unk_2C[lcl_38.unk_0C];
            if (loc44)
            {
                w48 = 1;
                RwV3dSub(&frm_24, &arg_8->unk_04, &loc44->unk_10);
#ifdef CODFH_SP // shape: the squared distance summed from z down to x
                m_18 = frm_24.z * frm_24.z + frm_24.y * frm_24.y + frm_24.x * frm_24.x;
#else
                m_18 = RwV3dDotProduct(&frm_24, &frm_24);
#endif
                if (arg_8->unk_18)
                {
                    w48 = arg_8->unk_18(loc44, lcl_38.unk_0C, arg_8, m_18);
                }
                if (w48)
                {
                    if (m_18 < arg_8->unk_3C)
                    {
                        arg_8->unk_34 = loc44;
                        arg_8->unk_3C = m_18;
                        arg_8->unk_38 = lcl_38.unk_0C;
                        arg_8->unk_40 = arg_0;
                        arg_8->unk_44 = arg_4;
                        arg_8->unk_48 = lv_10;
                    }
                    if (arg_8->unk_20)
                    {
                        if (arg_8->unk_4C < arg_8->unk_24)
                        {
                            arg_8->unk_20[arg_8->unk_4C].unk_00 = lcl_38.unk_0C;
                            arg_8->unk_20[arg_8->unk_4C].unk_02 = 0;
                            arg_8->unk_20[arg_8->unk_4C].unk_04 = m_18;
                            arg_8->unk_4C++;
                        }
                        else if (!arg_C)
                        {
                            return 0;
                        }
                        else
                        {
                            return 1;
                        }
                    }
                }
            }
            lcl_38.sub_31A10();
        }
    }
    return 1;
}

// match: ?sub_F8FA0@@YAHPAUtype_F8350@@@Z @ 0x000F8FA0
// sp-match: ?sub_F8FA0@@YAHPAUtype_F8350@@@Z @ 0x000BCDD0
RwInt32 sub_F8FA0(type_F8350 *arg_0)
{
    RwInt32 var_4 = arg_0->unk_00_w & 0xF42;

    return var_4;
}

// match: ?sub_F8FC0@@YAHPAUtype_F8350@@@Z @ 0x000F8FC0
// sp-match: ?sub_F8FC0@@YAHPAUtype_F8350@@@Z @ 0x000BCDE0
RwInt32 sub_F8FC0(type_F8350 *arg_0)
{
    RwInt32 var_4 = arg_0->unk_04;

    return var_4;
}

// match: ?sub_F8FE0@@YAXPAUtype_F8350@@PAURwV3d@@1@Z @ 0x000F8FE0
// sp-match: ?sub_F8FE0@@YAXPAUtype_F8350@@PAURwV3d@@1@Z @ 0x000BCDF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F8FE0(type_F8350 *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = sub_F8FA0(arg_0);
    bp_8 = sub_F8FC0(arg_0);
    arg_4->x = 0.0f;
    arg_4->y = 0.0f;
    arg_4->z = 0.0f;
    if (arg_8)
    {
        arg_8->x = 0.0f;
        arg_8->y = 0.0f;
        arg_8->z = 0.0f;
    }
    if (bp_4 & 0x40)
    {
        if (bp_8 == 3 && arg_0->unk_00_8)
        {
            arg_4->x = 188.9f;
            arg_4->y = 130.0f;
            if (arg_8)
            {
                arg_8->y = -45.0f;
            }
        }
        else if (bp_8 == 4 && arg_0->unk_00_8)
        {
            arg_4->x = -188.9f;
            arg_4->y = 130.0f;
            if (arg_8)
            {
                arg_8->y = 45.0f;
            }
        }
    }
    else if ((bp_8 == 3 && arg_0->unk_00_8) || bp_8 == 8)
    {
        arg_4->x = 100.0f;
        arg_4->y = 130.0f;
        if (arg_8)
        {
            arg_8->y = -45.0f;
        }
    }
    else if ((bp_8 == 4 && arg_0->unk_00_8) || bp_8 == 7)
    {
        arg_4->x = -100.0f;
        arg_4->y = 130.0f;
        if (arg_8)
        {
            arg_8->y = 45.0f;
        }
    }
    else if (bp_8 == 3 && arg_0->unk_00_10)
    {
        arg_4->x = 100.0f;
        arg_4->y = 125.0f;
        if (arg_8)
        {
            arg_8->y = -45.0f;
        }
    }
    else if (bp_8 == 4 && arg_0->unk_00_10)
    {
        arg_4->x = -100.0f;
        arg_4->y = 125.0f;
        if (arg_8)
        {
            arg_8->y = 45.0f;
        }
    }
    else if (bp_8 == 5 && arg_0->unk_00_8)
    {
        arg_4->y = 200.0f;
        if (arg_8)
        {
            arg_8->y = 180.0f;
        }
    }
    else if (bp_8 == 5 && arg_0->unk_00_10)
    {
        arg_4->y = 150.0f;
        if (arg_8)
        {
            arg_8->y = 90.0f;
        }
    }
    else if (bp_8 == 5 && arg_0->unk_00_11)
    {
        arg_4->y = 125.0f;
        if (arg_8)
        {
            arg_8->y = 90.0f;
        }
    }
    else if (bp_8 == 9 && arg_0->unk_00_8)
    {
        arg_4->y = 200.0f;
        if (arg_8)
        {
            arg_8->y = 180.0f;
        }
    }
    else if (bp_8 == 9 && arg_0->unk_00_9)
    {
        arg_4->y = 200.0f;
        if (arg_8)
        {
            arg_8->y = 90.0f;
        }
    }
    else if (bp_8 == 9 && arg_0->unk_00_10)
    {
        arg_4->y = 200.0f;
        if (arg_8)
        {
            arg_8->y = 180.0f;
        }
    }
    else if (bp_8 == 11)
    {
        arg_4->y = 100.0f;
        if (arg_8)
        {
            arg_8->y = 180.0f;
        }
    }
    else if (bp_8 == 0x13)
    {
        arg_4->y = 100.0f;
        if (arg_8)
        {
            arg_8->y = 180.0f;
        }
    }
    else if (bp_8 == 0xD)
    {
        arg_4->y = 188.0f;
        if (arg_8)
        {
            arg_8->y = 180.0f;
        }
    }
    else if (bp_8 == 0xC)
    {
        arg_4->y = 200.0f;
        if (arg_8)
        {
            arg_8->y = 180.0f;
        }
    }
    else if (bp_8 == 0xE)
    {
        arg_4->y = 175.0f;
    }
    else if (bp_8 == 0x11)
    {
        arg_4->y = 125.0f;
        if (arg_8)
        {
            arg_8->y = 180.0f;
        }
    }
    else
    {
        arg_4->x = 100.0f;
        arg_4->y = 150.0f;
        if (arg_8)
        {
            arg_8->y = -45.0f;
        }
    }
}

// match: ?sub_F93D0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F93D0
// sp-match: ?sub_F93D0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD030
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F93D0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    RwReal bp_4;

    if (!within_height(bp_4 = (RwReal)fabs(arg_0->unk_10.y - arg_8->unk_04.y)))
    {
        return 0;
    }
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_F9440@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9440
// sp-match: ?sub_F9440@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD070
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F9440(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    RwReal var_4C;
    type_4E5D30 *frm_48;
#ifdef CODFH_SP // shape: the line test's line and the flag after it are one object (the flag's store stays)
    struct
    {
        RwLine line;
        RwInt32 flag;
    } line_flag;
    RwLine &w44 = line_flag.line;
    RwInt32 &ebp_2C = line_flag.flag;
#else
    RwLine w44;
    RwInt32 ebp_2C;
#endif
    RwInt32 l28;
    type_3D3548 *ebp_24;
    RwV3d w20;
    RwV3d u14;
    RwReal bp_8;
    RwReal bp_4;

    if (!within_height(var_4C = (RwReal)fabs(arg_0->unk_10.y - arg_8->unk_04.y)))
    {
        return 0;
    }
    bp_4 = arg_8->unk_00->vf_14C() + 100.0f;
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (arg_C < bp_4 * bp_4)
    {
        return 0;
    }
    if (arg_0->unk_00_2)
    {
        return 0;
    }
    if (arg_0->unk_00_7)
    {
        return 0;
    }
    RwV3dSub(&u14, &arg_8->unk_04, arg_8->unk_00->sub_CD550());
    RwV3dNormalize(&u14, &u14);
    RwV3dSub(&w20, &arg_0->unk_10, arg_8->unk_00->sub_CD550());
    RwV3dNormalize(&w20, &w20);
    bp_8 = RwV3dDotProduct(&u14, &w20);
    if (bp_8 > 0.0f)
    {
        return 0;
    }
    ebp_24 = arg_8->unk_00->vf_120()->get_unk_1374();
    if (ebp_24)
    {
        ebp_2C = 1;
        w44.start = *ebp_24->sub_CD550();
        w44.start.y += 50.0f;
        w44.end = arg_0->unk_10;
        w44.end.y += 50.0f;
        for (l28 = 0; l28 < 4; l28++)
        {
            frm_48 = &dword_4E5D30[l28];
            if (frm_48->get_unk_00() && frm_48->get_unk_28() &&
                sub_91F40(frm_48->get_unk_28(), &w44, 0, 0x400000, 0x10000, 1)) // not an address: line-test flags
            {
                return 0;
            }
        }
    }
    return 1;
}

// match: ?sub_F9710@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9710
// sp-match: ?sub_F9710@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD260
RwInt32 sub_F9710(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_0->unk_04 != 0x10 && arg_0->unk_04 != 0xF)
    {
        return 0;
    }
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_F9750@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9750
// sp-match: ?sub_F9750@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD290
RwInt32 sub_F9750(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (arg_0->unk_04 != 0x11)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_F9780@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9780
// sp-match: ?sub_F9780@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD2C0
RwInt32 sub_F9780(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (arg_0->unk_08 >= dword_4B87C8)
    {
        return 0;
    }
    if (arg_0->unk_00_2)
    {
        return 0;
    }
    if (!arg_0->unk_00_1 || !arg_0->unk_00_4)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_F97F0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F97F0
// sp-match: ?sub_F97F0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BE150
RwInt32 sub_F97F0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (!arg_0->unk_00_4)
    {
        return 0;
    }
    return sub_F9820(arg_0, arg_4, arg_8, arg_C);
}

// match: ?sub_F9820@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9820
// sp-match: ?sub_F9820@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD300
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F9820(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    RwReal loc54;
    RwV3d u50;
    RwReal loc44;
    type_4E5D30 *fp_40;
    RwInt32 ebp_3C;
    type_3D3548 *lcl_38;
    RwV3d *r34;
    RwReal lv_30;
    RwInt32 fp_2C;
    RwInt32 q28;
    RwInt32 frm_24;
#ifdef CODFH_SP // shape: the line test's line and the flag after it are one object (the flag's store stays)
    struct
    {
        RwLine line;
        RwInt32 flag;
    } line_flag;
    RwLine &loc20 = line_flag.line;
    RwInt32 &bp_8 = line_flag.flag;
#else
    RwLine loc20;
    RwInt32 bp_8;
#endif
    RwInt32 bp_4;

    if (!within_height(loc54 = (RwReal)fabs(arg_0->unk_10.y - arg_8->unk_04.y)))
    {
        return 0;
    }
    if (arg_8->unk_14 && arg_0->unk_00_2)
    {
        return 0;
    }
    if (arg_0->unk_00_7)
    {
        return 0;
    }
    fp_2C = 0;
    frm_24 = 0;
    q28 = 0;
    ebp_3C = 0;
    if (arg_8->unk_00)
    {
        lcl_38 = arg_8->unk_00;
        lv_30 = arg_8->unk_00->unk_4C * arg_8->unk_00->unk_4C;
        r34 = &arg_8->unk_04;
    }
    bp_8 = 1;
    loc20.start = arg_8->unk_04;
    loc20.start.y += 50.0f;
    loc20.end = arg_0->unk_10;
    loc20.end.y += 50.0f;
    for (bp_4 = 0; bp_4 < 4 && !ebp_3C; bp_4++)
    {
        fp_40 = &dword_4E5D30[bp_4];
        if (fp_40->get_unk_00() && !ebp_3C && fp_40->get_unk_28() &&
            sub_91F40(fp_40->get_unk_28(), &loc20, 0, 0x20000, 0x10000, 1)) // not an address: line-test flags
        {
            ebp_3C = 1;
        }
    }
    if (!ebp_3C)
    {
        if (arg_C < arg_8->unk_58)
        {
            arg_8->unk_58 = arg_C;
            arg_8->unk_50 = arg_0;
            arg_8->unk_54 = arg_4;
        }
        u50.x = arg_0->unk_10.x - arg_8->unk_04.x;
        u50.y = arg_0->unk_10.y - arg_8->unk_04.y;
        u50.z = arg_0->unk_10.z - arg_8->unk_04.z;
        loc44 = RwV3dDotProduct(&arg_8->unk_28, &u50);
        if (loc44 > 0.0f && !(arg_0->unk_0C > dword_4B87C8))
        {
            return 1;
        }
    }
    return 0;
}

// match: ?sub_F9A70@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9A70
// sp-match: ?sub_F9A70@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BE170
RwInt32 sub_F9A70(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (!arg_0->unk_00_4)
    {
        return 0;
    }
    return sub_F9AA0(arg_0, arg_4, arg_8, arg_C);
}

// match: ?sub_F9AA0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9AA0
// sp-match: ?sub_F9AA0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD460
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_F9AA0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    RwReal loc44;
    type_4E5D30 *fp_40;
    RwInt32 ebp_3C;
    type_3D3548 *lcl_38;        // (unused: sub_F9820's entity, radius and point)
    RwV3d *r34;
    RwReal lv_30;
    RwInt32 fp_2C;
    RwInt32 q28;
    RwInt32 frm_24;
#ifdef CODFH_SP // shape: the line test's line and the flag after it are one object (the flag's store stays)
    struct
    {
        RwLine line;
        RwInt32 flag;
    } line_flag;
    RwLine &loc20 = line_flag.line;
    RwInt32 &bp_8 = line_flag.flag;
#else
    RwLine loc20;
    RwInt32 bp_8;
#endif
    RwInt32 bp_4;

    if (!within_height(loc44 = (RwReal)fabs(arg_0->unk_10.y - arg_8->unk_04.y)))
    {
        return 0;
    }
    if (arg_8->unk_14 && arg_0->unk_00_2)
    {
        return 0;
    }
    if (arg_0->unk_0C > dword_4B87C8)
    {
        return 0;
    }
    if (arg_0->unk_00_7)
    {
        return 0;
    }
    fp_2C = 0;
    frm_24 = 0;
    q28 = 0;
    ebp_3C = 0;
    bp_8 = 1;
    loc20.start = arg_8->unk_04;
    loc20.start.y += 50.0f;
    loc20.end = arg_0->unk_10;
    loc20.end.y += 50.0f;
    for (bp_4 = 0; bp_4 < 4 && !ebp_3C; bp_4++)
    {
        fp_40 = &dword_4E5D30[bp_4];
        if (fp_40->get_unk_00() && !ebp_3C && fp_40->get_unk_28() &&
            sub_91F40(fp_40->get_unk_28(), &loc20, 0, 0x20000, 0x10000, 1)) // not an address: line-test flags
        {
            ebp_3C = 1;
        }
    }
    if (arg_C < arg_8->unk_58)
    {
        arg_8->unk_58 = arg_C;
        arg_8->unk_50 = arg_0;
        arg_8->unk_54 = arg_4;
    }
    if (!ebp_3C && !(arg_0->unk_0C > dword_4B87C8))
    {
        return 1;
    }
    return 0;
}

// match: ?sub_F9C80@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9C80
// sp-match: ?sub_F9C80@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD5A0
RwInt32 sub_F9C80(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (!arg_0->unk_00_1)
    {
        return 0;
    }
    if (arg_0->unk_00_3)
    {
        return 0;
    }
    if (arg_0->unk_00_7)
    {
        return 0;
    }
    if (!(arg_0->unk_04 == 7 || arg_0->unk_04 == 8 || arg_0->unk_00_1 || arg_0->unk_00_6 || arg_0->unk_04 == 3 ||
          arg_0->unk_04 == 4 || arg_0->unk_04 == 5 || arg_0->unk_04 == 9 || arg_0->unk_04 == 0xB ||
          arg_0->unk_04 == 0x13 || arg_0->unk_04 == 0xC || arg_0->unk_04 == 0xE || arg_0->unk_04 == 0xD ||
          arg_0->unk_04 == 0x11))
    {
        return 0;
    }
    return 1;
}

// A door node in reach (as sub_F9C80) that the trigger arg_8 sees: the line
// from its point (raised by 50) to the node's door-offset point (sub_F8FE0,
// turned by the node's orientation) crosses none of the collision worlds.
// match: ?sub_F9DA0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000F9DA0
// sp-match: ?sub_F9DA0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD5D0
RwInt32 sub_F9DA0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
#ifdef CODFH_SP // shape: the line test's line and the flag after it are one object (the flag's store stays)
    struct
    {
        RwLine line;
        RwInt32 flag;
    } line_flag;
    RwInt32 &var_4 = line_flag.flag;
    RwLine &var_1C = line_flag.line;
#else
    RwInt32 var_4;
    RwLine var_1C;
#endif
    type_F8350 *var_20;
    RwV3d var_2C;
    RwMatrix var_70;
    RwV3d var_B0;
    RwInt32 var_B4;
    RwInt32 var_B8;
    type_4E5D30 *var_BC;

    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (!arg_0->unk_00_1)
    {
        return 0;
    }
    if (arg_0->unk_00_3)
    {
        return 0;
    }
    if (arg_0->unk_00_7)
    {
        return 0;
    }
    if (!(arg_0->unk_04 == 7 || arg_0->unk_04 == 8 || arg_0->unk_00_1 || arg_0->unk_00_6 || arg_0->unk_04 == 3 ||
          arg_0->unk_04 == 4 || arg_0->unk_04 == 5 || arg_0->unk_04 == 9 || arg_0->unk_04 == 0xB ||
          arg_0->unk_04 == 0x13 || arg_0->unk_04 == 0xC || arg_0->unk_04 == 0xE || arg_0->unk_04 == 0xD ||
          arg_0->unk_04 == 0x11))
    {
        return 0;
    }
    var_4 = 1;
    var_1C.start = arg_8->unk_04;
    var_1C.start.y += 50.0f;
    var_20 = arg_0;
    var_2C.x = 0.0f;
    var_2C.y = 0.0f;
    var_2C.z = 0.0f;
    RwMatrixSetIdentityMacro(&var_70);
    sub_F8FE0(var_20, &var_2C, 0);
    RtQuatConvertToMatrix(&var_20->unk_1C, &var_70);
    var_70.pos = var_20->unk_10;
    sub_1414C0(&var_B0, &var_2C, &var_70);
    var_1C.end = var_B0;
    var_B4 = 0;
    for (var_B8 = 0; var_B8 < 4 && !var_B4; var_B8++)
    {
        var_BC = &dword_4E5D30[var_B8];
        if (var_BC->get_unk_00() && !var_B4 && var_BC->get_unk_28() &&
            sub_91F40(var_BC->get_unk_28(), &var_1C, 0, 0x20000, 0x10000, 1)) // not an address: line-test flags
        {
            var_B4 = 1;
        }
    }
    if (var_B4)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_FA260@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000FA260
// sp-match: ?sub_FA260@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD840
RwInt32 sub_FA260(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (!arg_0->unk_00_1)
    {
        return 0;
    }
    if (!(arg_0->unk_00_1 || arg_0->unk_00_6 || arg_0->unk_04 == 3 || arg_0->unk_04 == 4 || arg_0->unk_04 == 5 ||
          arg_0->unk_04 == 9 || arg_0->unk_04 == 0xB || arg_0->unk_04 == 0x13 || arg_0->unk_04 == 0xC ||
          arg_0->unk_04 == 0xE || arg_0->unk_04 == 0xD || arg_0->unk_04 == 0x11))
    {
        return 0;
    }
    return 1;
}

// match: ?sub_FA330@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000FA330
// sp-match: ?sub_FA330@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD870
RwInt32 sub_FA330(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (!arg_0->unk_00_1)
    {
        return 0;
    }
    if (arg_0->unk_00_3)
    {
        return 0;
    }
    if (arg_0->unk_00_7)
    {
        return 0;
    }
    if (!(arg_0->unk_00_1 || arg_0->unk_00_6 || arg_0->unk_04 == 3 || arg_0->unk_04 == 4 || arg_0->unk_04 == 5 ||
          arg_0->unk_04 == 9 || arg_0->unk_04 == 0xB || arg_0->unk_04 == 0x13 || arg_0->unk_04 == 0xC ||
          arg_0->unk_04 == 0xE || arg_0->unk_04 == 0xD || arg_0->unk_04 == 0x11))
    {
        return 0;
    }
    if (arg_C < flt_3D9484 * flt_3D9484)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_FA440@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000FA440
// sp-match: ?sub_FA440@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD8B0
RwInt32 sub_FA440(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (arg_0->unk_04 != 2)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_FA470@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000FA470
// sp-match: ?sub_FA470@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD8E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_FA470(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    type_4E5D30 *frm_24;
#ifdef CODFH_SP // shape: the line test's line and the flag after it are one object (the flag's store stays)
    struct
    {
        RwLine line;
        RwInt32 flag;
    } line_flag;
    RwLine &loc20 = line_flag.line;
    RwInt32 &bp_8 = line_flag.flag;
#else
    RwLine loc20;
    RwInt32 bp_8;
#endif
    RwInt32 bp_4;

    if (!sub_FA440(arg_0, arg_4, arg_8, arg_C))
    {
        return 0;
    }
    bp_8 = 1;
    loc20.start = arg_8->unk_04;
    loc20.start.y += 50.0f;
    loc20.end = arg_0->unk_10;
    loc20.end.y += 50.0f;
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        frm_24 = &dword_4E5D30[bp_4];
        if (frm_24->get_unk_00() && frm_24->get_unk_28() &&
            sub_91F40(frm_24->get_unk_28(), &loc20, 0, 0x20000, 0x10000, 1)) // not an address: line-test flags
        {
            return 0;
        }
    }
    return 1;
}

// match: ?sub_FA570@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000FA570
// sp-match: ?sub_FA570@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD9B0
RwInt32 sub_FA570(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (!arg_0->unk_00_4)
    {
        return 0;
    }
    if (arg_8->unk_14 && arg_0->unk_00_2)
    {
        return 0;
    }
    if (arg_0->unk_00_7)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_FA5D0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000FA5D0
// sp-match: ?sub_FA5D0@@YAHPAUtype_F8350@@HPAUtype_154C0_1048@@M@Z @ 0x000BD9F0
RwInt32 sub_FA5D0(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C)
{
    if (arg_C > arg_8->unk_5C)
    {
        return 0;
    }
    if (arg_0->unk_04 != 0x12)
    {
        return 0;
    }
    if (arg_8->unk_14 && arg_0->unk_00_2)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_FA620@@YAHHHH@Z @ 0x000FA620
// sp-match: ?sub_FA620@@YAHHHH@Z @ 0x000BDA30
RwInt32 sub_FA620(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_FA620 *var_4 = (type_FA620 *)arg_0;

    var_4->unk_24 = arg_8;
    var_4->unk_10 = 0x10;
    return 1;
}

// flt_3D948C (7984.2, .rdata): the square of a cover corner's expected
// diagonal size (its root, about 89.4, is taken).
#ifndef CODFH_SP
extern const RwReal flt_3D948C;
#endif

// The corner connected to the cover point arg_0: the first linked node of the
// same kind and flags (bits 2 and 6 aside) on the other side (bit 6), whose
// diagonal size from it is within 5 of the root of flt_3D948C; 0 without
// one (or when arg_0 is not a cover point, bit 1).
// match: ?sub_FA650@@YAPAUtype_F8350@@PAU1@@Z @ 0x000FA650
// match: __ehhandler$?sub_FA650@@YAPAUtype_F8350@@PAU1@@Z-0xB @ 0x00301150
// match: __ehhandler$?sub_FA650@@YAPAUtype_F8350@@PAU1@@Z @ 0x0030115B
// sp-match: ?sub_FA650@@YAPAUtype_F8350@@PAU1@@Z @ 0x000BE190
type_F8350 *sub_FA650(type_F8350 *arg_0)
{
    RwUInt32 *var_14;
    RwReal var_74;
    RwInt32 var_8C;
    type_F8350 *var_94;
    RwInt32 var_98;
    RwInt32 var_9C;
    RwInt32 var_A0;
    RwV3d var_AC;
    RwReal var_B0;
    RwReal var_B4;
    RwReal var_BC;

    var_14 = 0;
    do
    {
#ifdef CODFH_SP // a literal: default.xbe has no flt_3D948C (SP 0xBE19A stores 0x45F981AF)
        __m128 var_30 = _mm_set_ss(7984.2104f);
#else
        __m128 var_30 = _mm_set_ss(flt_3D948C);
#endif
        __m128 var_60 = _mm_sqrt_ss(var_30);
        _mm_store_ss(&var_74, var_60);
    } while (0);
    if (!arg_0->unk_00_1)
    {
        return 0;
    }
    if (arg_0->unk_00_0)
    {
        var_14 = arg_0->unk_2C;
    }
    else
    {
        var_14 = arg_0->unk_1C_links;
    }
    type_3CE1FC var_88(var_14);
    var_8C = arg_0->unk_04;
    while (!var_88.at_end())
    {
        var_94 = 0;
        var_94 = sub_FA980(var_88.unk_0C);
        if (var_94)
        {
            var_98 = arg_0->unk_00_w & ~0x44;
            var_9C = var_94->unk_00_w & ~0x44;
            var_A0 = var_94->unk_04;
            if (var_98 == var_9C && arg_0->unk_00_6 != var_94->unk_00_6 && var_8C == var_A0)
            {
                RwV3dSubMacro(&var_AC, &var_94->unk_10, &arg_0->unk_10);
                var_BC = ((RwReal)fabs(var_B4 = (var_B0 = RwV3dLength((RwV3d *)&var_AC)) - var_74));
                if (var_BC < 5.0f)
                {
                    return var_94;
                }
            }
        }
        var_88.sub_31A10();
    }
    return 0;
}

// match: ?sub_FA920@@YAHPAUtype_F8350@@@Z @ 0x000FA920
// sp-match: ?sub_FA920@@YAHPAUtype_F8350@@@Z @ 0x000BDA50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_FA920(type_F8350 *arg_0)
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = -1;
    if (arg_0)
    {
        for (bp_8 = 0; bp_8 < unk_4C00E8.unk_08; bp_8++)
        {
            if (unk_4C00E8.unk_2C[bp_8] == arg_0)
            {
                bp_4 = bp_8;
                break;
            }
        }
    }
    return bp_4;
}

// match: ?sub_FA980@@YAPAUtype_F8350@@H@Z @ 0x000FA980
// sp-match: ?sub_FA980@@YAPAUtype_F8350@@H@Z @ 0x000BDA90
type_F8350 *sub_FA980(RwInt32 arg_0)
{
    if (arg_0 >= 0 && arg_0 < unk_4C00E8.unk_08)
    {
        return unk_4C00E8.unk_2C[arg_0];
    }
    return 0;
}

// match: ??0type_4C01A0@@QAE@XZ @ 0x000FA9B0
// sp-match: ??0type_4C01A0@@QAE@XZ @ 0x000BC9E0
// (Defined in the class, in game/pathnodes.h.)


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004C0154: dword_4C0150 + 0x4
RwUInt32 &dword_4C0154 = *(RwUInt32 *)((RwUInt8 *)&dword_4C0150 + 0x4);
// 0x004C0158: dword_4C0150 + 0x8
RwUInt32 &dword_4C0158 = *(RwUInt32 *)((RwUInt8 *)&dword_4C0150 + 0x8);
// 0x004C015C: dword_4C0150 + 0xC
RwUInt32 &dword_4C015C = *(RwUInt32 *)((RwUInt8 *)&dword_4C0150 + 0xC);
#endif
