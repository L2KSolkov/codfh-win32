// The multiplayer game's flags (game/flags.h).

#include "game/flags.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/bombsites.h"
#include "types/type_3D3548.h"
#include "types/type_3D32F8.h"
#include "types/type_44350.h"
#include <string.h>
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "game/netstate.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E1284
extern const RwReal flt_3E1284 = -5.0f;
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E1288
extern const RwReal flt_3E1288 = 16.666666f;
// 0x003E128C
extern const RwReal flt_3E128C = 0.01f;
// 0x003E1290
extern const RwReal flt_3E1290 = 0.01f;
#endif
// End of its data definitions.


// The flags themselves, built by their dynamic initializer.
type_4F6A7C dword_4F6A7C;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E1284@@3MB @ 0x003E1284
// match: ?flt_3E1288@@3MB @ 0x003E1288
// match: ?flt_3E128C@@3MB @ 0x003E128C
// match: ?flt_3E1290@@3MB @ 0x003E1290
// match: ??_C@_0P@JPPAAFGO@MW_CTF_DROPRED?$AA@ @ 0x003E1294
// match: ??_C@_0O@NLLKPLL@MW_CTF_GOTRED?$AA@ @ 0x003E12A4
// match: ??_C@_0O@DGHOEMBI@MW_CTF_CAPRED?$AA@ @ 0x003E12B4
// match: ??_C@_0BB@PKAKANOD@MW_CTF_RETURNRED?$AA@ @ 0x003E12C4
// match: ??_C@_0BA@CHJHBGFF@MW_CTF_DROPBLUE?$AA@ @ 0x003E12D8
// match: ??_C@_0P@NBLMHLKE@MW_CTF_GOTBLUE?$AA@ @ 0x003E12E8
// match: ??_C@_0P@JOFIEMBF@MW_CTF_CAPBLUE?$AA@ @ 0x003E12F8
// match: ??_C@_0BC@LEPLBDMA@MW_CTF_RETURNBLUE?$AA@ @ 0x003E1308
// match: ??_C@_0BG@GBGAINO@MW_CTF_RETURNRED_AUTO?$AA@ @ 0x003E131C
// match: ??_C@_0BH@OKENAGMK@MW_CTF_RETURNBLUE_AUTO?$AA@ @ 0x003E1334
// match: __ehhandler$?sub_1A4B40@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z>1>8 @ 0x0041EA94
// match: __ehhandler$?sub_1A4B40@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z>1 @ 0x0041EAD4
// match: .CRT$XCU+0 @ 0x004271AC

// match: _$E2 @ 0x0030C140
// match: ?sub_1A4920@type_4F6A7C@@QAEHPAVTrigger@@@Z @ 0x001A4920

RwInt32 type_4F6A7C::sub_1A4920(class Trigger *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        if (unk_00[var_4].unk_04 == arg_0)
        {
            if (unk_38)
                return var_4 ^ 1;
            return var_4;
        }
    }
    return -1;
}

// match: ?sub_1A4980@type_4F6A7C@@QAEXXZ @ 0x001A4980
void type_4F6A7C::sub_1A4980()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        if (unk_00[var_4].unk_08 && unk_00[var_4].unk_08->unk_28_1)
        {
            unk_00[var_4].unk_08->unk_28_4 = 0;
            unk_00[var_4].unk_08->unk_28_5 = 0;
        }
    }
}

// match: ?sub_1A4A20@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z @ 0x001A4A20
void type_4F6A7C::sub_1A4A20(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10)
{
    if (arg_8 == -1)
        unk_4F7EB8.unk_384.sub_1B1B00(arg_0, arg_4, arg_C, arg_10, 1);
    else
        unk_4F7EB8.unk_384.sub_1B1B00(arg_0, arg_4, arg_C, arg_10, 0);
    sub_1A4B40(arg_0, arg_4, arg_8, arg_C, 0);
}

// match: ?sub_1A4A90@type_4F6A7C@@QAEXXZ @ 0x001A4A90
void type_4F6A7C::sub_1A4A90()
{
    RwV3d var_C;

    if (unk_38 == 1)
        return;
    var_C = unk_00[1].unk_0C;
    unk_00[1].unk_0C = unk_00[0].unk_0C;
    unk_00[0].unk_0C = var_C;
    unk_38 = 1;
}

// match: ?sub_1A4B00@type_4F6A7C@@QAEXXZ @ 0x001A4B00
void type_4F6A7C::sub_1A4B00()
{
    if (dword_4FB9E0.get_unk_08() != 4)
        return;
    if (unk_38 == 1)
    {
        unk_38 = 0;
        sub_1A4A90();
        unk_38 = 0;
    }
}

// The objective of the flag arg_4's base (its trigger's unk_28): a free inline with
// no address. Evidence: the state change (sub_1A4B40) keeps it in a result
// slot where it is passed beside a call, and its frame holds the leftovers of
// one expansion per use.
inline type_3DF8D8_04 *flag_objective(type_4F6A7C *arg_0, RwInt32 arg_4)
{
    return &arg_0->unk_00[arg_4].unk_04->unk_28;
}

// A real's size as the state change tests it: a ternary that copies either
// branch into a temporary.
#define ABS_REAL(x) ((x) < 0.0f ? -(x) : (x))

// match: ?sub_1A4B40@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z @ 0x001A4B40
// match: __ehhandler$?sub_1A4B40@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z-0x58 @ 0x003028C0
// match: __ehhandler$?sub_1A4B40@type_4F6A7C@@QAEXHHHPAURwV3d@@H@Z @ 0x00302918
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The flag arg_0's state arg_4 (0 at home, 1 carried, 2 dropped) through
// the player arg_8 (-1: none), dropped at arg_C: with both bases set, the
// homes swapped for four teams (else put back); the carrier's flag state
// (vf_05C) and the flag put at its home or where it was dropped; unless
// arg_10, the change's text ("MW_CTF_..." with the player's name) on the
// HUD; then the state kept and the base's objective markers updated.
void type_4F6A7C::sub_1A4B40(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10)
{
    RwChar loc11C[0x100];
    type_3D3548 *m_18;
    type_3D3548 *ebp_14;
    RwInt32 lv_10;

    lv_10 = 0;
    if (unk_00[0].unk_04 && unk_00[1].unk_04)
    {
        if (dword_4FB9E0.get_unk_10C())
            sub_1A4A90();
        else
            sub_1A4B00();
    }
    switch (arg_4)
    {
    case 0:
        if (arg_8 != -1)
        {
            ebp_14 = unk_4F7EB8.sub_1AECA0(arg_8, 1);
            if (ebp_14)
                ebp_14->vf_05C();
        }
        sub_1A5C40(arg_0, &unk_00[arg_0].unk_0C);
        break;
    case 1:
        break;
    case 2:
        if (arg_8 != -1)
        {
            m_18 = unk_4F7EB8.sub_1AECA0(arg_8, 1);
            if (m_18)
                m_18->vf_05C();
        }
        if (!arg_C || ABS_REAL(arg_C->x) < 0.001f && ABS_REAL(arg_C->y) < 0.001f && ABS_REAL(arg_C->z) < 0.001f)
            sub_1A5C40(arg_0, &unk_00[arg_0].unk_0C);
        else
            sub_1A5C40(arg_0, arg_C);
        break;
    default:
        return;
    }
    if (!arg_10 && arg_4 != unk_00[arg_0].unk_00)
    {
        if (arg_8 == -1)
        {
            if (arg_0 == 0)
            {
                switch (arg_4)
                {
                case 0:
                    strcpy(loc11C, sub_E3970("MW_CTF_RETURNBLUE_AUTO", 1).c_str());
                }
            }
            else
            {
                switch (arg_4)
                {
                case 0:
                    strcpy(loc11C, sub_E3970("MW_CTF_RETURNRED_AUTO", 1).c_str());
                }
            }
        }
        else if (arg_0 == 0)
        {
            switch (arg_4)
            {
            case 0:
                if (dword_4F8288.sub_1C2A90(arg_8) == 2)
                    sub_1CB000(loc11C, sub_E3970("MW_CTF_RETURNBLUE", 1).c_str(),
                               type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                else
                    sub_1CB000(loc11C, sub_E3970("MW_CTF_CAPBLUE", 1).c_str(),
                               type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            case 1:
                sub_1CB000(loc11C, sub_E3970("MW_CTF_GOTBLUE", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            case 2:
                sub_1CB000(loc11C, sub_E3970("MW_CTF_DROPBLUE", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            }
        }
        else
        {
            switch (arg_4)
            {
            case 0:
                if (dword_4F8288.sub_1C2A90(arg_8) == 4)
                    sub_1CB000(loc11C, sub_E3970("MW_CTF_RETURNRED", 1).c_str(),
                               type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                else
                    sub_1CB000(loc11C, sub_E3970("MW_CTF_CAPRED", 1).c_str(),
                               type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            case 1:
                sub_1CB000(loc11C, sub_E3970("MW_CTF_GOTRED", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            case 2:
                sub_1CB000(loc11C, sub_E3970("MW_CTF_DROPRED", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
                break;
            }
        }
        sub_EACA0(loc11C, 0, 0);
    }
    unk_00[arg_0].unk_00 = arg_4;
    if (!unk_00[arg_0].unk_04)
        return;
    sub_170790(&unk_00[arg_0].unk_04->unk_28, -2);
    switch (arg_4)
    {
    case 0:
        if (unk_38)
            sub_171070(flag_objective(this, arg_0), (type_712B0 *)unk_00[arg_0 ^ 1].unk_04);
        else
            sub_171070(flag_objective(this, arg_0), (type_712B0 *)unk_00[arg_0].unk_04);
        sub_171480(flag_objective(this, arg_0), 0);
        break;
    case 1:
        if (arg_8 != -1)
        {
            if (unk_4F7EB8.sub_1AECA0(arg_8, 0))
                sub_171110(flag_objective(this, arg_0), unk_4F7EB8.sub_1AECA0(arg_8, 0));
            else
                sub_171110(flag_objective(this, arg_0), unk_00[arg_0].unk_08);
            sub_171480(flag_objective(this, arg_0), 1);
        }
        break;
    case 2:
        if (unk_00[arg_0].unk_08)
        {
            sub_171110(flag_objective(this, arg_0), unk_00[arg_0].unk_08);
            unk_00[arg_0].unk_08->unk_28_4 = 1;
            unk_00[arg_0].unk_08->unk_28_5 = 1;
        }
        sub_171480(flag_objective(this, arg_0), 1);
        break;
    }
}

// match: ??0type_4F6A7C@@QAE@XZ @ 0x001A57C0
type_4F6A7C::type_4F6A7C()
{
    unk_38 = 0;
    sub_1A57E0();
}

// match: ?sub_1A57E0@type_4F6A7C@@QAEXXZ @ 0x001A57E0
void type_4F6A7C::sub_1A57E0()
{
    RwInt32 var_4;

    unk_38 = 0;
    for (var_4 = 0; var_4 < 2; var_4++)
    {
        unk_00[var_4].unk_00 = 1;
        unk_00[var_4].unk_18 = 1;
    }
    sub_1A5D10();
    unk_00[0].unk_04 = 0;
    unk_00[1].unk_04 = 0;
}

// match: ?sub_1A5850@type_4F6A7C@@QAEXXZ @ 0x001A5850
void type_4F6A7C::sub_1A5850()
{
    RwInt32 var_4;

    unk_38 = 0;
    for (var_4 = 0; var_4 < 2; var_4++)
    {
        unk_00[var_4].unk_00 = 1;
        unk_00[var_4].unk_18 = 1;
    }
    if (dword_4FB9E0.get_unk_08() == 4)
        sub_1A5D10();
}

// match: ?sub_1A58C0@type_4F6A7C@@QAEXHPAVTrigger@@@Z @ 0x001A58C0
void type_4F6A7C::sub_1A58C0(RwInt32 arg_0, class Trigger *arg_4)
{
    if (dword_4FB9E0.get_unk_08() != 4)
        return;
    unk_00[arg_0].unk_04 = arg_4;
    unk_00[arg_0].unk_0C = *(RwV3d *)&arg_4->unk_90;
}

// match: ?sub_1A5920@type_4F6A7C@@QAEHHPAUtype_3D3548@@@Z @ 0x001A5920
RwInt32 type_4F6A7C::sub_1A5920(RwInt32 arg_0, type_3D3548 *arg_4)
{
    return unk_00[arg_0].sub_1A5DA0(arg_4->vf_0CC());
}

// match: ?sub_1A5950@type_4F6A7C@@QAEHH@Z @ 0x001A5950
RwInt32 type_4F6A7C::sub_1A5950(RwInt32 arg_0)
{
    if (!arg_0)
        return 2;
    return 4;
}

// match: ?sub_1A5970@type_4F6A7C@@QAEXPAUtype_3D3548@@@Z @ 0x001A5970
void type_4F6A7C::sub_1A5970(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++)
    {
        if (unk_00[var_4].unk_08 == arg_0 && unk_00[var_4].unk_00 == 2)
        {
            sub_1A4A20(var_4, 0, -1, 0, 0);
            break;
        }
    }
}

// match: ?sub_1A59D0@type_4F6A7C@@QAEXXZ @ 0x001A59D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F6A7C::sub_1A59D0()
{
    RwInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    type_3DF8D8_04 *bp_8;
    RwInt32 bp_4;

    if (dword_4FB9E0.get_unk_08() != 4)
        return;
    for (bp_4 = 0; bp_4 < 2; bp_4++)
    {
        if (unk_00[bp_4].unk_04)
        {
            bp_8 = &unk_00[bp_4].unk_04->unk_28;
            var_14 = 1;
            var_C = 0;
            sub_1703B0(bp_8, var_14, var_C);
            sub_171070(bp_8, (type_712B0 *)unk_00[bp_4].unk_04);
            unk_00[bp_4].unk_08 = unk_00[bp_4].unk_04->vf_020();
            unk_00[bp_4].unk_08->unk_28_4 = 1;
            unk_00[bp_4].unk_08->unk_130 = 0;
            unk_00[bp_4].unk_08->unk_108 = flt_3E1284;
            unk_00[bp_4].unk_08->unk_10C.x = -0.5f;
            unk_00[bp_4].unk_08->unk_10C.y = -0.5f;
            unk_00[bp_4].unk_08->unk_10C.z = -0.5f;
            unk_00[bp_4].unk_08->unk_134.x = -0.5f;
            unk_00[bp_4].unk_08->unk_134.y = -0.5f;
            unk_00[bp_4].unk_08->unk_134.z = -0.5f;
            sub_1A5C40(bp_4, &unk_00[bp_4].unk_0C);
            lv_10 = sub_1A4920(unk_00[bp_4].unk_04);
            sub_171070(&unk_00[bp_4].unk_04->unk_28, (type_712B0 *)unk_00[lv_10].unk_04);
            if (unk_00[bp_4].unk_00 == 2)
            {
                sub_170710(&unk_00[bp_4].unk_04->unk_28, 2);
                // A compiled-out check: the registers after it are one load
                // on (docs/toolchain.md).
                if (!unk_00[0].unk_08)
                {
                }
                sub_171110(&unk_00[bp_4].unk_04->unk_28, unk_00[bp_4].unk_08);
            }
            sub_1A4B40(bp_4, 0, -1, 0, 1);
        }
    }
}

// match: ?sub_1A5C40@type_4F6A7C@@QAEXHPAURwV3d@@@Z @ 0x001A5C40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F6A7C::sub_1A5C40(RwInt32 arg_0, RwV3d *arg_4)
{
    RwFrame *var_8;
    RwMatrix *l4;

    if (!unk_00[arg_0].unk_08)
        return;
    var_8 = unk_00[arg_0].unk_08->unk_338.unk_08;
    l4 = RwFrameGetMatrix(var_8);
    l4->at.z = 1.0f;
    l4->up.y = 1.0f;
    l4->right.x = 1.0f;
    l4->up.x = 0;
    l4->right.z = 0;
    l4->right.y = 0;
    l4->at.y = 0;
    l4->at.x = 0;
    l4->up.z = 0;
    unk_00[arg_0].unk_08->vf_0C0(arg_4);
}

// match: ?sub_1A5D10@type_4F6A7C@@QAEXXZ @ 0x001A5D10
void type_4F6A7C::sub_1A5D10()
{
    if (unk_00[0].unk_08)
        sub_D5A60(unk_00[0].unk_08, 0);
    if (unk_00[1].unk_08)
        sub_D5A60(unk_00[1].unk_08, 0);
    unk_00[0].unk_08 = 0;
    unk_00[1].unk_08 = 0;
}

// match: ?sub_1A5D70@type_4F6A7C@@QAEPAUtype_3D3548@@H@Z @ 0x001A5D70
type_3D3548 *type_4F6A7C::sub_1A5D70(RwInt32 arg_0)
{
    if (arg_0 < 2)
        return unk_00[arg_0].unk_08;
    return 0;
}

// match: ?sub_1A5DA0@type_4F6A7C_flag@@QAEHPAURwV3d@@@Z @ 0x001A5DA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4F6A7C_flag::sub_1A5DA0(RwV3d *arg_0)
{
    RwInt32 var_10;
    RwReal var_C;
    RwV3d *bp_8;
    RwReal bp_4;

    if (unk_00 == 1)
        return 0;
    var_C = 200.0f;
    bp_4 = 80.0f;
    if (!unk_08)
        return 0;
    bp_8 = unk_08->vf_0CC();
    var_10 = sub_92860(arg_0, bp_8, bp_4, var_C);
    return var_10;
}
