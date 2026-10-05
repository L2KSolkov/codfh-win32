// The multiplayer manager's remote players (type_4F7EB8_1F0,
// game/netsoldier.h): a soldier with a network part that takes the remote
// player's state and hits and sends its own. Its original file name is not
// in the image, so it is named for its start address.

#include <math.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "game/netsoldier.h"
#include "types/animbank.h"
#include "types/cNetSoldierTrigger.h"
#include "rws/cclassfactory.h"
#include "game/netmsg.h"
#include "game/functions.h"
#include "types/type_3D32F8.h"
#include "types/type_4AE70.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/flags.h"
#include "game/bombsites.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "types/type_DC400.h"
#include "types/alfaobject.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E2FA8
extern const RwReal flt_3E2FA8 = 16.666666f;
// 0x003E2FAC
extern const RwReal flt_3E2FAC = 0.01f;
// 0x003E2FB0
extern const RwReal flt_3E2FB0 = 0.01f;
// 0x003E2FB4
extern const RwReal flt_3E2FB4 = 16.666666f;
// 0x003E2FB8
extern const RwV3d stru_3E2FB8 = { 1.0f, 0.0f, 0.0f };
// 0x003E2FC4
extern const RwV3d stru_3E2FC4 = { 0.0f, 1.0f, 0.0f };
// 0x003E2FD0
extern const RwReal flt_3E2FD0 = 0.01f;
// 0x003E2FD4
extern const RwReal flt_3E2FD4 = 0.01f;
// 0x0042CB40
RwReal flt_42CB40[4][5] = {
    { 0.0f, 60.0f, 60.0f, 140.0f, 120.0f },
    { 0.0f, 520.0f, 520.0f, 560.0f, 400.0f },
    { 0.0f, 100.0f, 100.0f, 250.0f, 100.0f },
    { 0.0f, 70.0f, 70.0f, 50.0f, 60.0f },
};
// 0x0042CB90
RwReal flt_42CB90 = 100.0f;
// 0x0042CB94
RwUInt8 byte_42CB94[2] = { 0x9B, 0x2 };
// 0x0042CB96
RwUInt8 byte_42CB96 = 171;
// 0x0042CB97
RwUInt8 byte_42CB97 = 2;
// 0x004F8134
#ifndef CODFH_PLAIN
cNetSoldierTrigger *dword_4F8134;
#endif
// 0x004FBC30
RwInt32 dword_4FBC30;
// 0x004FBC34
RwInt32 dword_4FBC34;
// 0x004FBC38
struct type_7C8D0 *dword_4FBC38;
// 0x004FBC3C
RwInt32 dword_4FBC3C;
// 0x004FBC40
RwUInt8 byte_4FBC40;
// 0x004FBC44
RwInt32 dword_4FBC44;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E2FA8@@3MB @ 0x003E2FA8
// match: ?flt_3E2FAC@@3MB @ 0x003E2FAC
// match: ?flt_3E2FB0@@3MB @ 0x003E2FB0
// match: ?flt_3E2FB4@@3MB @ 0x003E2FB4
// match: ?stru_3E2FB8@@3URwV3d@@B @ 0x003E2FB8
// match: ?stru_3E2FC4@@3URwV3d@@B @ 0x003E2FC4
// match: ?flt_3E2FD0@@3MB @ 0x003E2FD0
// match: ?flt_3E2FD4@@3MB @ 0x003E2FD4
// match: ??_7type_4F7EB8_1F0@@6Btype_4F6B00_120@@@ @ 0x003E2FD8
// match: ??_7type_4F7EB8_1F0@@6Btype_3DAFC8@@@ @ 0x003E3008
// match: ??_C@_0BN@KFDBPKHN@Local?5player?5shot?5player?5?$CFd?6?$AA@ @ 0x003E326C
// match: __real@435c0000 @ 0x003E328C
// match: ??_C@_0N@MLACFFFG@MPAnimAction?$AA@ @ 0x003E3290
// match: __ehhandler$?sub_1BEBB0@@YAPAUtype_4F7EB8_1F0@@PAUtype_712B0@@@Z>1>8 @ 0x0041F1A8
// match: __ehhandler$?sub_1BEBB0@@YAPAUtype_4F7EB8_1F0@@PAUtype_712B0@@@Z>1 @ 0x0041F1B0
// match: __ehhandler$??0type_4F7EB8_1F0@@QAE@PAVSoldierTrigger@@@Z>1>8 @ 0x0041F1CC
// match: __ehhandler$??0type_4F7EB8_1F0@@QAE@PAVSoldierTrigger@@@Z>1 @ 0x0041F1D4
// match: __ehhandler$??1type_4F7EB8_1F0@@UAE@XZ>1>8 @ 0x0041F1F0
// match: __ehhandler$??1type_4F7EB8_1F0@@UAE@XZ>1 @ 0x0041F1F8
// match: ?flt_42CB40@@3PAY04MA @ 0x0042CB40
// match: ?flt_42CB90@@3MA @ 0x0042CB90
// match: ?byte_42CB94@@3PAEA @ 0x0042CB94
// match: ?byte_42CB96@@3EA @ 0x0042CB96
// match: ?byte_42CB97@@3EA @ 0x0042CB97

// match: ?sub_1BEBB0@@YAPAUtype_4F7EB8_1F0@@PAUtype_712B0@@@Z @ 0x001BEBB0
// match: __ehhandler$?sub_1BEBB0@@YAPAUtype_4F7EB8_1F0@@PAUtype_712B0@@@Z-0x11 @ 0x00302EC0
// match: __ehhandler$?sub_1BEBB0@@YAPAUtype_4F7EB8_1F0@@PAUtype_712B0@@@Z @ 0x00302ED1

type_4F7EB8_1F0 *sub_1BEBB0(type_712B0 *arg_0)
{
    type_4F7EB8_1F0 *var_10;

    var_10 = (type_4F7EB8_1F0 *)sub_D56D0(0x21D0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_4F7EB8_1F0((SoldierTrigger *)arg_0);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    } else
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
    return var_10;
}

// match: ??0type_4F7EB8_1F0@@QAE@PAVSoldierTrigger@@@Z @ 0x001BECC0
// match: __ehhandler$??0type_4F7EB8_1F0@@QAE@PAVSoldierTrigger@@@Z-0x8 @ 0x00302EE0
// match: __ehhandler$??0type_4F7EB8_1F0@@QAE@PAVSoldierTrigger@@@Z @ 0x00302EE8
type_4F7EB8_1F0::type_4F7EB8_1F0(SoldierTrigger *arg_0) : type_3DAFC8(arg_0)
{
    RwUInt32 var_10;

    unk_2174 = 0;
    unk_2180 = 0.2f;
    unk_217C = 0;
    unk_2184.sub_1C5A80(0);
    unk_2194.sub_1C5A80(0);
    unk_2178 = -1;
    unk_21A8 = 0;
    for (var_10 = 0; var_10 < 4; var_10++)
        unk_21AC.unk_00[var_10] = 0;
    for (var_10 = 0; var_10 < 6; var_10++)
    {
        unk_21C4[var_10] = 0xFF;
        unk_21CA[var_10] = 1;
        unk_84C[var_10] = 0xFF;
        unk_84C[var_10 + 6] = 1;
    }
    unk_21BC = 0;
    unk_21C0 = 0;
}

// match: ??_Gtype_4F7EB8_1F0@@UAEPAXI@Z @ 0x001BEE80

// match: ??1type_4F7EB8_1F0@@UAE@XZ @ 0x001BEEB0
// match: __ehhandler$??1type_4F7EB8_1F0@@UAE@XZ-0x8 @ 0x00302F00
// match: __ehhandler$??1type_4F7EB8_1F0@@UAE@XZ @ 0x00302F08
type_4F7EB8_1F0::~type_4F7EB8_1F0()
{
    unk_4F7EB8.sub_15FB30(this);
}

// Its step: the send timer runs down; once due, a hit waiting on another
// peer's player (not this machine's) is sent to that peer (the damage) and
// to the others (the hit), both cleared; then the soldier's step.
// match: ?vf_038@type_4F7EB8_1F0@@UAEXM@Z @ 0x001BEF20
void type_4F7EB8_1F0::vf_038(RwReal arg_0)
{
    unk_2180 -= arg_0;
    if (unk_2178 != -1 && unk_2180 <= 0.0f && unk_217C && unk_2178 != unk_4F7EB8.sub_1AEC70())
    {
        type_1DDE20_mask bp_8;

        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_2178)
        {
        }
        bp_8.add(unk_2178);
        unk_2174->sub_1DDDB0(&unk_2184, bp_8);
        unk_2184.sub_1C5A80(0);
        sub_1A8A70(&unk_4F7EB8, "Local player shot player %d\n", unk_2178);
        type_1DDE20_mask bp_4 = type_4F8054::get()->get_unk_B0()->sub_1A8050();
        bp_4.clear(unk_2178);
        unk_2194.unk_09 = (RwUInt8)unk_2178;
        unk_2174->sub_1DDE90(&unk_2194, bp_4);
        unk_2194.sub_1C5A80(0);
        unk_2180 = 0.2f;
        unk_217C = 0;
    }
    unk_28 &= ~0x100;
    type_3DAFC8::vf_038(arg_0);
}

// The remote player's state from its network player: its direction of
// travel (the velocity *arg_8, normalised), its lean *arg_C, its frame
// placed at *arg_0 turned by the facing *arg_4, its aim (the facing and
// the lean) and weapon *arg_14, its crouch and flags *arg_18, the angle
// between its facing and its travel (mode 1's), its performance
// (sub_1BF5E0) and its sections *arg_1C.
// match: ?pvf_000@type_4F7EB8_1F0@@UAEXPAUtype_1F8560_v@@PAUtype_4F6B00_F4@@0PAH22PAIPAG@Z @ 0x001BF0C0
void type_4F7EB8_1F0::pvf_000(type_1F8560_v *arg_0, type_4F6B00_F4 *arg_4, type_1F8560_v *arg_8, RwInt32 *arg_C,
                              RwInt32 *arg_10, RwInt32 *arg_14, RwUInt32 *arg_18, RwUInt16 *arg_1C)
{
    type_1F8560_v var_10;
    type_1F8560_v var_1C;
    RwMatrix var_80;
    RwMatrix var_D0;
    RwReal var_F0;
    RwUInt32 var_F4;

    if (arg_8->sub_1BF590() == 0.0f)
        var_10 = *arg_8;
    else
        var_10 = arg_8->normal();
    vf_18C(0);
    unk_21A4 = *(RwReal *)arg_C;
    var_80.flags = 2;
    var_80.pad1 = 0;
    var_80.pad2 = 0;
    var_80.pad3 = 0;
    RwMatrixSetIdentityMacro(&var_80);
    RwMatrixRotate(&var_80, &stru_3E2FC4, arg_4->get_unk_00(), rwCOMBINEPRECONCAT);
    var_80.pos.x = arg_0->unk_00;
    var_80.pos.y = arg_0->unk_04;
    var_80.pos.z = arg_0->unk_08;
    RwFrameTransform(get_unk_340(), &var_80, rwCOMBINEREPLACE);
    RwFrameUpdateObjects(get_unk_340());
    RwMatrixSetIdentityMacro(&var_D0);
    RwMatrixRotate(&var_D0, &stru_3E2FC4, arg_4->get_unk_00(), rwCOMBINEPRECONCAT);
    RwMatrixRotate(&var_D0, &stru_3E2FB8, unk_21A4, rwCOMBINEPRECONCAT);
    sub_136DA0(sub_1C5800(*arg_14));
    if (RwMatrixGetAt(&var_D0))
        unk_818_v = *RwMatrixGetAt(&var_D0);
    if (unk_21BC != (*arg_18 & 1))
    {
        vf_1B0(*arg_18 & 1);
        unk_21BC = *arg_18 & 1;
    }
    if (*arg_18 & 8)
        pvf_024();
    var_1C.unk_00 = (RwReal)sin(arg_4->get_unk_00() * 0.017453292f);
    var_1C.unk_04 = 0;
    var_F0 = (RwReal)acos(var_1C.unk_00 * var_10.unk_00 + var_1C.unk_04 * var_10.unk_04 +
                          (var_1C.unk_08 = (RwReal)cos(arg_4->get_unk_00() * 0.017453292f)) * var_10.unk_08);
    if (var_1C.unk_00 * var_10.unk_08 - var_1C.unk_08 * var_10.unk_00 < 0.0f)
        var_F0 = -var_F0;
    var_F0 += 1.5707964f;
    unk_1DC0 = var_F0;
    sub_1BF5E0(arg_4, arg_8, arg_C, arg_10, arg_18);
    for (var_F4 = 0; var_F4 < 4; var_F4++)
        unk_21AC.unk_00[var_F4] = arg_1C[var_F4];
}

// The length of the vector: an out-of-line method (the remote player's
// state, sub_1BF0C0, scales its velocity by it).
// match: ?sub_1BF590@type_1F8560_v@@QAEMXZ @ 0x001BF590
RwReal type_1F8560_v::sub_1BF590()
{
    return (RwReal)sqrt((RwReal)(unk_00 * unk_00 + unk_04 * unk_04 + unk_08 * unk_08));
}

// Its performance from the remote player's state: the posture by its speed
// (still, walking 8, running 9 past 220 and from 250), its stance's action
// and the run's rates by its stance *arg_8 (0, 7 crouched, 8 prone), the
// action by its flag carrying, grenade, bomb site and weapon flags *arg_10
// (the lean *arg_4's y turning it), the debug override (dword_4FBC3C); a
// new performance is looked up and started (as an event when the flags ask
// for one), its script told; its weapon shown or hidden, the flag it
// carries turned, its aim's side-step rates for mode 1, and the animation
// state kept for the debug display.
// match: ?sub_1BF5E0@type_4F7EB8_1F0@@QAEXPAUtype_4F6B00_F4@@PAUtype_1F8560_v@@PAH2PAI@Z @ 0x001BF5E0
void type_4F7EB8_1F0::sub_1BF5E0(type_4F6B00_F4 *arg_0, type_1F8560_v *arg_4, RwInt32 *arg_8, RwInt32 *arg_C,
                                 RwUInt32 *arg_10)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwUInt8 w48[0xC];
    RwReal lcl_38[5];
    RwInt32 frm_24;
    type_7C8D0 *t20;
    RwInt32 l1C;
    RwReal m_18;
    const RwChar *ebp_14;
    RwUInt32 lv_10;

    ebp_14 = "MPAnimAction";
    for (lv_10 = 0; lv_10 < 6; lv_10++)
        w48[lv_10 + 6] = 1;
    frm_24 = 0;
    type_1F8560_v slot_C = *arg_4;
    slot_C.unk_04 = 0;
    m_18 = slot_C.sub_1BF590();
    if (m_18 < 10.0f)
        w48[0] = 0;
    else if (m_18 < 220.0f)
        w48[0] = 8;
    else if (m_18 < 250.0f)
    {
        if (unk_84C[0] == 8)
            w48[0] = 8;
        else
            w48[0] = 9;
    }
    else
        w48[0] = 9;
    switch (*arg_C)
    {
    case 0:
        if (w48[0] == 8)
        {
            w48[2] = 5;
            for (lv_10 = 0; lv_10 < 5; lv_10++)
                lcl_38[lv_10] = m_18 / flt_42CB40[0][lv_10];
        }
        else if (w48[0] == 9)
        {
            w48[2] = 5;
            for (lv_10 = 0; lv_10 < 5; lv_10++)
                lcl_38[lv_10] = m_18 / flt_42CB40[1][lv_10];
        }
        else
        {
            w48[2] = 2;
            for (lv_10 = 0; lv_10 < 5; lv_10++)
                lcl_38[lv_10] = 1.0f;
        }
        break;
    case 7:
        w48[2] = 0x2A;
        if (w48[0] == 8 || w48[0] == 9)
        {
            for (lv_10 = 0; lv_10 < 5; lv_10++)
                lcl_38[lv_10] = m_18 / flt_42CB40[2][lv_10];
        }
        else
        {
            for (lv_10 = 0; lv_10 < 5; lv_10++)
                lcl_38[lv_10] = 1.0f;
        }
        break;
    case 8:
        w48[2] = 0x2B;
        if (w48[0] == 8 || w48[0] == 9)
        {
            for (lv_10 = 0; lv_10 < 5; lv_10++)
                lcl_38[lv_10] = m_18 / flt_42CB40[3][lv_10];
        }
        else
        {
            for (lv_10 = 0; lv_10 < 5; lv_10++)
                lcl_38[lv_10] = 1.0f;
        }
    }
    if (unk_4F7EB8.unk_384.sub_1B2480(unk_2178))
    {
        if (*arg_10 & 0x10)
            w48[1] = 0xAE;
        else
            w48[1] = 0xA4;
    }
    else if (unk_21C0)
    {
        frm_24 = 1;
        w48[1] = 0xA1;
        ebp_14 = "MaybeThrowAGrenade";
    }
    else if (unk_4F8184.sub_1A8620(unk_2178) || unk_4F8184.sub_1A8680(unk_2178))
        w48[1] = 0xA8;
    else if (*arg_10 & 0x20)
    {
        frm_24 = 1;
        if (arg_4->unk_04 >= 0.0f)
        {
            w48[1] = 0xA9;
            unk_284->sub_7C9D0(arg_4->unk_04 / flt_42CB90);
        }
        else
        {
            w48[1] = 0xAA;
            unk_284->sub_7C9D0(-arg_4->unk_04 / flt_42CB90);
        }
    }
    else if (*arg_10 & 0x40)
    {
        frm_24 = 1;
        w48[1] = 0x9F;
    }
    else if (*arg_10 & 0x10)
    {
        frm_24 = 1;
        w48[1] = 0xA0;
    }
    else if (*arg_10 & 4)
    {
        frm_24 = 1;
        w48[1] = 0x9E;
        ebp_14 = "OutOfAmmo";
    }
    else if (*arg_10 & 1)
    {
        frm_24 = 1;
        w48[1] = 0x9C;
    }
    else if (*arg_10 & 2)
    {
        frm_24 = 1;
        w48[1] = 0x9D;
    }
    else
        w48[1] = 0x9B;
    w48[3] = 0;
    w48[4] = 0;
    w48[5] = 0;
    if (dword_4FBC3C)
    {
        switch (dword_4FBC44)
        {
        case 1:
            w48[0] = 0xA;
            w48[2] = 0x5B;
            w48[1] = 0xA5;
            break;
        case 2:
            w48[0] = 0xA;
            w48[2] = 0x5B;
            w48[1] = 0xA6;
            break;
        case 3:
            w48[0] = 0xA;
            w48[2] = 0x5B;
            w48[1] = 0xA7;
            break;
        default:
            w48[0] = byte_4FBC40;
            w48[2] = byte_42CB94[1];
            w48[1] = byte_42CB94[0];
        }
    }
    for (lv_10 = 0; lv_10 < 5; lv_10++)
        lcl_38[lv_10] = 1.0f;
    l1C = 0;
    if ((w48[0] != unk_84C[0] || w48[2] != unk_84C[2] || w48[1] != unk_84C[1]) && unk_8A0.unk_51C)
    {
        type_ED340 *y5C;
        type_6D380 *slot_58;
        RwInt16 lv_54;
        RwInt32 ebp_50;

        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_2178)
        {
        }
        memcpy(unk_84C, w48, 6);
        if (vf_0AC() != unk_84C[2])
        {
            vf_0B0(unk_84C[2], 2);
            ((type_3D2CD0 *)vf_090())->sub_6DDF0(1, 0);
        }
        y5C = dword_4B92FC;
        slot_58 = vf_090();
        ebp_50 = unk_2C_3 * 8 + unk_2C_0 * 4 + unk_3E0.sub_15EE90();
        lv_54 = y5C->sub_ED340(this, unk_84C, ebp_50, 0);
        if (lv_54 != -1)
        {
            if (frm_24)
                ((type_3D2CD0 *)slot_58)->sub_6D380(lv_54, 0, 0, 0, 0, 0, 0, 0);
            else
                ((type_3D2CD0 *)slot_58)->sub_6D320(lv_54);
            slot_58->unk_144 = 1;
            l1C = 1;
        }
        sub_6B5F0(ebp_14, (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
    type_3D32F8 *var_4C = (type_3D32F8 *)unk_4F7EB8.unk_384.sub_1B2610(unk_2178);
    if (unk_21A8 || (RwInt8)w48[1] == (RwInt8)0xA4)
    {
        sub_13F660(0, 0);
        sub_13F660(1, 0);
    }
    else
    {
        sub_13F660(0, 1);
        sub_13F660(1, 1);
    }
    if (var_4C)
    {
        RwReal var_60;

        if (m_18 != 0.0f)
        {
            var_60 = m_18 / 100.0f;
            if (var_60 > 1.0f)
                var_60 = 1.0f;
        }
        else
            var_60 = 0;
        var_4C->unk_478 = get_unk_1DC0();
        var_4C->unk_480 = var_60;
        var_4C->sub_76960();
    }
    else
        vf_05C();
    if ((unk_824 & 2) && unk_1DAC[0])
    {
        RwReal m_6C;
        RwReal q68;
        RwReal var_64;
        // Never used: the image keeps a slot for it after the others.
        RwReal var_70;

        m_6C = 0;
        q68 = (RwReal)cos(get_unk_1DC0());
        var_64 = (RwReal)sin(get_unk_1DC0());
        if (q68 > 0.0f)
            m_6C += lcl_38[1] * q68;
        else if (q68 < 0.0f)
            m_6C -= lcl_38[2] * q68;
        if (var_64 > 0.0f)
            m_6C += lcl_38[3] * var_64;
        else if (var_64 < 0.0f)
            m_6C -= lcl_38[4] * var_64;
        unk_284->sub_7C9D0(m_6C);
    }
    unk_21C0 = 0;
    t20 = unk_284;
    if (t20)
    {
        dword_4FBC34 = t20->get_unk_24();
        dword_4FBC30 = t20->sub_7C940();
        dword_4FBC38 = t20;
    }
}

// Its lean: 100 up, swayed by unk_21A4 degrees.
// match: ?vf_244@type_4F7EB8_1F0@@UAEPAURwV3d@@PAU2@@Z @ 0x001BFEC0
RwV3d *type_4F7EB8_1F0::vf_244(RwV3d *arg_0)
{
    RwV3d var_C;

    var_C.x = 0;
    var_C.y = -((RwReal)sin((RwReal)(unk_21A4 * 0.017453292f)) * 100.0f);
    var_C.z = 100.0f;
    *arg_0 = var_C;
    return arg_0;
}

// match: ?pvf_014@type_4F7EB8_1F0@@UAEXPAUtype_75600@@@Z @ 0x001BFF30
void type_4F7EB8_1F0::pvf_014(type_75600 *arg_0)
{
    sub_1C0020(arg_0);
}

// match: ?pvf_018@type_4F7EB8_1F0@@UAEXPAUtype_75600@@@Z @ 0x001BFF50
void type_4F7EB8_1F0::pvf_018(type_75600 *arg_0)
{
    unk_1D20 = 0;
    sub_1C0020(arg_0);
}

// match: ?pvf_01C@type_4F7EB8_1F0@@UAEXPAUtype_4AE70@@@Z @ 0x001BFF80
void type_4F7EB8_1F0::pvf_01C(type_4AE70 *arg_0)
{
    sub_1C0200(arg_0);
}

// match: ?pvf_020@type_4F7EB8_1F0@@UAEXPAUtype_4AE70@@@Z @ 0x001BFFA0
void type_4F7EB8_1F0::pvf_020(type_4AE70 *arg_0)
{
    unk_1D20 = 0;
    sub_1C0200(arg_0);
}

// match: ?sub_1BFFD0@type_4F7EB8_1F0@@QAEXXZ @ 0x001BFFD0
void type_4F7EB8_1F0::sub_1BFFD0()
{
    RwInt32 var_4;

    var_4 = unk_2178;
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_2178)
    {
    }
    unk_4F6B00[var_4].sub_73D90((RwInt8 *)unk_1D38, unk_1D20);
}

// A bullet from the network: its hit-death values (with a performance value
// from the shooter's distance), its scripts told, its network player told.
// match: ?sub_1C0020@type_4F7EB8_1F0@@QAEXPAUtype_75600@@@Z @ 0x001C0020
void type_4F7EB8_1F0::sub_1C0020(type_75600 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 m_18;
    RwV3d ebp_14;
    type_EC880 *bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    if (arg_0->unk_0C)
    {
        bp_8 = (type_EC880 *)dword_4B92D4;
        RwV3dSubMacro(&ebp_14, sub_CD550(), arg_0->unk_0C->sub_CD550());
        bp_4 = bp_8->sub_EC880((type_EC880_00 *)arg_0, RwV3dLength((RwV3d *)&ebp_14));
    }
    unk_1D38[0] = unk_84C[3];
    unk_1D38[1] = unk_864;
    unk_1D38[2] = arg_0->unk_24;
    unk_1D38[3] = unk_3E0.sub_15F0A0();
    unk_1D38[4] = bp_4;
    unk_1D38[5] = bp_4;
    for (m_18 = 0; m_18 < 6; m_18++)
        unk_1D38[m_18 + 6] = 1;
    sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    sub_1BFFD0();
}

// match: ?pvf_028@type_4F7EB8_1F0@@UAEXPAURwV3d@@H@Z @ 0x001C0190
void type_4F7EB8_1F0::pvf_028(RwV3d *arg_0, RwInt32 arg_4)
{
    unk_1D20 = arg_4;
    *(RwV3d *)unk_1D38 = *arg_0;
    sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
}

// A grenade from the network: its hit-death values (with a performance
// value from the distance), its network player told, and its scripts told
// where it came from and whether from behind.
// match: ?sub_1C0200@type_4F7EB8_1F0@@QAEXPAUtype_4AE70@@@Z @ 0x001C0200
void type_4F7EB8_1F0::sub_1C0200(type_4AE70 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 loc44;
    RwV3d *fp_40;
    RwFrame *ebp_3C;
    RwV3d local_38;
    RwV3d stk_2C;
    RwMatrix *t20;
    type_EC880 *l1C;
    type_758F0_14 m_18;
    RwInt32 bp_4;

    fp_40 = &arg_0->unk_0C->pos;
    RwV3dSubMacro(&stk_2C, sub_CD550(), fp_40);
    l1C = (type_EC880 *)dword_4B92D4;
    bp_4 = l1C->sub_EC970((type_EC880_00 *)arg_0, RwV3dLength((RwV3d *)&stk_2C));
    unk_1D38[0] = vf_08C(1, 0)[3];
    unk_1D38[1] = unk_864;
    unk_1D38[2] = (RwInt8)(RpRandom() % 9);
    unk_1D38[3] = unk_3E0.sub_15F0A0();
    unk_1D38[4] = bp_4;
    unk_1D38[5] = bp_4;
    for (loc44 = 0; loc44 < 6; loc44++)
        unk_1D38[loc44 + 6] = 1;
    ebp_3C = unk_338.unk_08;
    t20 = RwFrameGetLTM(ebp_3C);
    local_38 = *RwMatrixGetPos(t20);
    RwV3dSubMacro(&local_38, &local_38, fp_40);
    m_18.unk_00 = fp_40->x;
    m_18.unk_04 = fp_40->y;
    m_18.unk_08 = fp_40->z;
    m_18.unk_0C = arg_0->unk_14;
    m_18.unk_10 = RwV3dDotProductMacro(&t20->at, &local_38) <= 0 ? 1 : 0;
    sub_1BFFD0();
    sub_6B5F0("HitByExplosion", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&m_18), 5, 1, 0);
}

// match: ?pvf_024@type_4F7EB8_1F0@@UAEXXZ @ 0x001C0410
void type_4F7EB8_1F0::pvf_024()
{
    unk_21C0 = 1;
}

// A bullet from this machine's player: its damage (by the part hit) added
// to both messages to send, and the entity's hit.
// match: ?vf_064@type_4F7EB8_1F0@@UAEHPAUtype_75600@@@Z @ 0x001C0430
RwInt32 type_4F7EB8_1F0::vf_064(type_75600 *arg_0)
{
    RwReal var_4;

    if (unk_2178 == -1)
        return 0;
    if (arg_0->unk_0C != (type_3D3548 *)type_4F805C::get())
        return 0;
    if (arg_0->unk_24 != -1)
    {
        sub_1C0020(arg_0);
        var_4 = part_damage_multiplier(arg_0->unk_24) * arg_0->unk_28;
        unk_2184.sub_1C5A80(unk_2184.get_unk_0C() + var_4);
        unk_2184.unk_04 = unk_3E0.unk_04;
        unk_2184.unk_08 = arg_0->unk_24;
        unk_2194.sub_1C5A80(unk_2194.get_unk_0C() + var_4);
        unk_2194.unk_04 = unk_3E0.unk_04;
        unk_2194.unk_08 = arg_0->unk_24;
        unk_217C = 1;
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
    }
    return 0;
}

// match: ?pvf_010@type_4F7EB8_1F0@@UAEXPAUtype_4F8058@@@Z @ 0x001C0570
void type_4F7EB8_1F0::pvf_010(type_4F8058 *arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_2178)
    {
    }
    unk_2174 = arg_0;
}

// match: ?pvf_00C@type_4F7EB8_1F0@@UAEXH@Z @ 0x001C0590
void type_4F7EB8_1F0::pvf_00C(RwInt32 arg_0)
{
    unk_2178 = arg_0;
}

// match: ?sub_1C05B0@type_3D3548@@QAEPAURwMatrixTag@@XZ @ 0x001C05B0
RwMatrix *type_3D3548::sub_1C05B0()
{
    // The locals' names state their slots (docs/toolchain.md).
    RwMatrix *bp_8;
    RwFrame *bp_4;

    bp_8 = 0;
    bp_4 = unk_338.unk_08;
    if (bp_4)
        bp_8 = RwFrameGetLTM(bp_4);
    return bp_8;
}

// match: ?vf_054@type_4F7EB8_1F0@@UAEXH@Z @ 0x001C05F0
void type_4F7EB8_1F0::vf_054(RwInt32 arg_0)
{
    if (!unk_21A8)
        type_3DAFC8::vf_054(arg_0);
}

// match: ?pvf_004@type_4F7EB8_1F0@@UAEXXZ @ 0x001C0620
void type_4F7EB8_1F0::pvf_004()
{
    unk_21A8 = 0;
    sub_13F660(0, 1);
    sub_13F660(1, 1);
}

// match: ?pvf_008@type_4F7EB8_1F0@@UAEXXZ @ 0x001C0660
void type_4F7EB8_1F0::pvf_008()
{
    unk_21A8 = 1;
    sub_13F660(0, 0);
    sub_13F660(1, 0);
}
// match: ?vf_05C@type_3DAFC8@@UAEXXZ @ 0x001C06A0
// match: ?vf_05C@type_4F7EB8_1F0@@WCBHA@AEXXZ @ 0x001C06D0

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.


// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_4F7EB8_1F0@@SAXPAX@Z (folded into 0x19A750)
void type_4F7EB8_1F0::operator delete(void * arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_4F7EB8_1F0@@SAXPAX0@Z (folded into 0x19A750)
void type_4F7EB8_1F0::operator delete(void * arg_0, void * arg_4)
{
}
