// The local player in a network game (type_17DBD0_player, game/netmsg.h):
// its spawn, constructor, destructor, the overrides of the player's step and
// its network part's slots, and its flag and bomb site handling. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/bavector.h"
#include "game/functions.h"
#include "types/type_3D32F8.h"
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "types/type_FC6F0.h"
#include "types/type_3DAFC8.h"
#include "types/type_4D1DB8.h"
#include "game/debugtext.h"
#include "game/worldmgr.h"
#include "types/type_4E5D30.h"
#include "rw/rpcollis.h"
#include "game/clumputil.h"
#include "rw/rphanim.h"

// The axis the second player's view turns about (y; .rdata, pvf_000; unit_1BAA90's).
extern const RwV3d stru_3E2918;
#include "game/data.h"
#include "game/gameloop.h"
#include "game/flags.h"
#include "game/bombsites.h"
#include "types/type_DC400.h"
#include "types/type_3DD948.h"
#include "types/soundbank.h"
#include "types/type_3D94B8.h"
#include "types/PickupTrigger.h"
#include "game/loc.h"
#include "game/mpgame.h"
#include "game/netscore.h"
#include <string.h>
#include <math.h>
#include "types/type_4C09B0.h"
#include "types/type_4C19C0.h"
#include "types/type_3DF8D8.h"
#include "game/textmanager.h"
#include "types/alfaobject.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E254C
extern const RwReal flt_3E254C = 16.666666f;
// 0x003E2550
extern const RwReal flt_3E2550 = 0.01f;
// 0x003E2554
extern const RwReal flt_3E2554 = 0.01f;
// 0x004FBB00
RpIntersection intersection;
// End of its data definitions.


// Its .data (PLAN M5), in the image's order.
RwInt32 dword_42CAE8 = 3;
RwReal flt_42CAEC = 0.08f;
RwReal flt_42CAF0 = 0.4f;
RwReal flt_42CAF4 = 500.0f;
RwReal flt_42CAF8 = 0.1f;
RwReal flt_42CAFC = 0.5f;
RwReal flt_42CB00 = 30.0f;
RwReal flt_42CB04 = 0.025f;
RwReal flt_42CB08 = 0.5f;
RwReal flt_42CB0C = 100.0f;
RwReal flt_42CB10 = -0.01f;
RwReal flt_42CB14 = -0.0125f;
RwReal flt_42CB18 = 0.0625f;
RwReal flt_42CB1C = 0.125f;
RwReal flt_42CB20 = -0.01f;
RwReal flt_42CB24 = -0.0125f;
RwReal flt_42CB28 = 0.0625f;
RwReal flt_42CB2C = 0.125f;
RwReal flt_42CB30 = 0.75f;
RwReal flt_42CB34 = 0.5f;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_10F710@@6B@ @ 0x003D9CB8
// match: ?flt_3E254C@@3MB @ 0x003E254C
// match: ?flt_3E2550@@3MB @ 0x003E2550
// match: ?flt_3E2554@@3MB @ 0x003E2554
// match: ??_7type_17DBD0_player@@6Btype_3E24E8@@@ @ 0x003E2558
// match: ??_7type_17DBD0_player@@6Btype_10F710@@@ @ 0x003E25A0
// match: ??_C@_0DA@GLGGNPK@Local?5player?5wounded?5by?5grenade?5@ @ 0x003E27FC
// match: ??_C@_0BF@PILNEOBL@MW_GEN_KILLS_YOUGREN?$AA@ @ 0x003E282C
// match: ??_C@_0BJ@HKFPJCO@MW_GEN_KILLS_YOUACCIDENT?$AA@ @ 0x003E2844
// match: ??_C@_0CP@MNCCGNIJ@Local?5player?5killed?5by?5grenade?5f@ @ 0x003E2860
// match: ??_C@_0BK@FINKOJDC@Picked?5up?5Grease?5Gun?5ammo?$AA@ @ 0x003E2890
// match: ??_C@_0CD@DGDFPHDL@Picked?5up?5Mosin?5Nagant?5Sniper?5am@ @ 0x003E28AC
// match: ??_C@_0BG@LNKBDCGO@Picked?5up?5Kar?598?5ammo?$AA@ @ 0x003E28D0
// match: ??_C@_0BD@JHJHFLFP@Picked?5up?5G43?5ammo?$AA@ @ 0x003E28E8
// match: ??_C@_0BH@ELBOGMHF@Picked?5up?5Enfield?5ammo?$AA@ @ 0x003E28FC
// match: __ehhandler$?sub_1B7B20@@YAPAUtype_17DBD0_player@@PAUtype_712B0@@@Z>1>8 @ 0x0041EFC8
// match: __ehhandler$?sub_1B7B20@@YAPAUtype_17DBD0_player@@PAUtype_712B0@@@Z>1 @ 0x0041EFD0
// match: __ehhandler$??0type_17DBD0_player@@QAE@PAUtype_712B0@@@Z>1>8 @ 0x0041EFEC
// match: __ehhandler$??0type_17DBD0_player@@QAE@PAUtype_712B0@@@Z>1 @ 0x0041EFFC
// match: __ehhandler$?vf_068@type_17DBD0_player@@UAEHPAUtype_758F0@@@Z>1>8 @ 0x0041F018
// match: __ehhandler$?vf_068@type_17DBD0_player@@UAEHPAUtype_758F0@@@Z>1 @ 0x0041F020
// match: ?dword_42CAE8@@3HA @ 0x0042CAE8
// match: ?flt_42CAEC@@3MA @ 0x0042CAEC
// match: ?flt_42CAF0@@3MA @ 0x0042CAF0
// match: ?flt_42CAF4@@3MA @ 0x0042CAF4
// match: ?flt_42CAF8@@3MA @ 0x0042CAF8
// match: ?flt_42CAFC@@3MA @ 0x0042CAFC
// match: ?flt_42CB00@@3MA @ 0x0042CB00
// match: ?flt_42CB04@@3MA @ 0x0042CB04
// match: ?flt_42CB08@@3MA @ 0x0042CB08
// match: ?flt_42CB0C@@3MA @ 0x0042CB0C
// match: ?flt_42CB10@@3MA @ 0x0042CB10
// match: ?flt_42CB14@@3MA @ 0x0042CB14
// match: ?flt_42CB18@@3MA @ 0x0042CB18
// match: ?flt_42CB1C@@3MA @ 0x0042CB1C
// match: ?flt_42CB20@@3MA @ 0x0042CB20
// match: ?flt_42CB24@@3MA @ 0x0042CB24
// match: ?flt_42CB28@@3MA @ 0x0042CB28
// match: ?flt_42CB2C@@3MA @ 0x0042CB2C
// match: ?flt_42CB30@@3MA @ 0x0042CB30
// match: ?flt_42CB34@@3MA @ 0x0042CB34

// match: ?sub_1B7B20@@YAPAUtype_17DBD0_player@@PAUtype_712B0@@@Z @ 0x001B7B20
// match: __ehhandler$?sub_1B7B20@@YAPAUtype_17DBD0_player@@PAUtype_712B0@@@Z-0x11 @ 0x00302D70
// match: __ehhandler$?sub_1B7B20@@YAPAUtype_17DBD0_player@@PAUtype_712B0@@@Z @ 0x00302D81

type_17DBD0_player *sub_1B7B20(type_712B0 *arg_0)
{
    type_17DBD0_player *var_10;

    var_10 = (type_17DBD0_player *)sub_D56D0(0x22B0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_17DBD0_player(arg_0);
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

// match: ??0type_17DBD0_player@@QAE@PAUtype_712B0@@@Z @ 0x001B7C30
// match: __ehhandler$??0type_17DBD0_player@@QAE@PAUtype_712B0@@@Z-0x16 @ 0x00302D90
// match: __ehhandler$??0type_17DBD0_player@@QAE@PAUtype_712B0@@@Z @ 0x00302DA6
type_17DBD0_player::type_17DBD0_player(type_712B0 *arg_0) : type_10F710(arg_0)
{
    unk_2264.unk_08 = 0;
    unk_2264.unk_04 = 0;
    unk_2264.unk_00 = 0;
    unk_2270.unk_08 = 0;
    unk_2270.unk_04 = 0;
    unk_2270.unk_00 = 0;
    unk_227C = 0;
    unk_2288 = -1;
    unk_2290 = 0;
    unk_2294 = -1;
    unk_2298 = -1;
    unk_229C = 0;
    unk_22A0 = -1;
    if (unk_4F7EB8.sub_1AF280())
    {
        unk_2C = 0x12;
        unk_30 = 0x32FFFE7;
    }
    unk_217C = 0;
}

// match: ?pvf_040@type_17DBD0_player@@UAEXH@Z @ 0x001B7DF0
void type_17DBD0_player::pvf_040(RwInt32 arg_0)
{
    unk_2288 = arg_0;
}

// match: ??_Gtype_17DBD0_player@@UAEPAXI@Z @ 0x001B7E10

// match: ??1type_17DBD0_player@@UAE@XZ @ 0x001B7E40
type_17DBD0_player::~type_17DBD0_player()
{
    dword_44E8A0 = 3;
}

// match: ?vf_038@type_17DBD0_player@@UAEXM@Z @ 0x001B7E80
void type_17DBD0_player::vf_038(RwReal arg_0)
{
    type_10F710::vf_038(arg_0);
}

// Dead (no health left) and not holding off a weapon change: a defuse or a
// plant under way ends, a carried flag drops. Then the player's step, and
// while alive the bomb sites and the flags.
// match: ?vf_03C@type_17DBD0_player@@UAEXM@Z @ 0x001B7EA0
void type_17DBD0_player::vf_03C(RwReal arg_0)
{
    if (!unk_19F8 && unk_19DC <= 0.0f)
    {
        if (get_unk_19D0_r() == 0x10)
            sub_1B8630(0);
        else if (get_unk_19D0_r() == 0x11)
            sub_1B8740(3);
        else if (unk_229C)
            sub_1B8250(2, 0);
    }
    type_10F710::vf_03C(arg_0);
    if (unk_19DC > 0.0f)
    {
        sub_1B8440();
        sub_1B8380();
    }
}

// match: ?vf_04C@type_17DBD0_player@@UAEXM@Z @ 0x001B7F60
void type_17DBD0_player::vf_04C(RwReal arg_0)
{
    type_10F710::vf_04C(arg_0);
    if (!sub_106620((struct type_3D94B8 *)unk_228C.sub_D4910()))
        unk_228C.sub_D48D0(0);
    if (unk_228C.sub_D4910())
    {
        sub_1B91E0();
        unk_228C.sub_D48D0(0);
    }
    else
    {
        sub_10F7E0(0xB, 0);
        sub_10F7E0(0xC, 0);
    }
}

// Its state for the network: its position (at its feet), its velocity, its
// facing (the frame's turn about z, signed by the axis) and on a ladder the
// ladder's, and sub_1B90C0's.
// match: ?pvf_000@type_17DBD0_player@@UAEXH@Z @ 0x001B7FF0
void type_17DBD0_player::pvf_000(RwInt32 arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwV3d l1C;
    RwReal lv_10;
    RwV3d slot_C;

    unk_2264.unk_00 = vf_0C4()[0];
    unk_2264.unk_04 = vf_0C4()[1] - unk_48;
    unk_2264.unk_08 = vf_0C4()[2];
    unk_2270.unk_00 = unk_D8;
    unk_2270.unk_04 = unk_DC;
    unk_2270.unk_08 = unk_E0;
    l1C = *RwMatrixGetAt(RwFrameGetMatrix(get_unk_340()));
    l1C.x = 0;
    l1C.y = 0;
    l1C.z = 1.0f;
    slot_C.x = 0;
    slot_C.y = 0;
    slot_C.z = 0;
    RwMatrixQueryRotate(RwFrameGetMatrix(get_unk_340()), &l1C, &lv_10, &slot_C);
    if (l1C.y < 0.0)
        lv_10 = -lv_10;
    unk_227C = lv_10;
    if (unk_19D0 == 0xD && unk_2178)
    {
        l1C.x = 0;
        l1C.y = 0;
        l1C.z = 1.0f;
        slot_C.x = 0;
        slot_C.y = 0;
        slot_C.z = 0;
        RwMatrixQueryRotate(&unk_2178->unk_60, &l1C, &lv_10, &slot_C);
        if (l1C.y < 0.0)
            lv_10 = -lv_10;
        unk_2280 = lv_10;
    }
    unk_2284 = sub_1B90C0();
}

// match: ?sub_1B81D0@type_17DBD0_player@@QAEXXZ @ 0x001B81D0
void type_17DBD0_player::sub_1B81D0()
{
    RwInt32 var_4;

    if (unk_229C == 1)
        return;
    var_4 = 0;
    if (sub_1B8420() == 2)
        var_4 = 1;
    if (dword_4F6A7C.unk_00[var_4].get_unk_00() == 1)
        return;
    dword_4F6A7C.sub_1A4A20(var_4, 1, unk_4F7EB8.sub_1AEC70(), 0, 0);
    unk_229C = 1;
}

// match: ?sub_1B8250@type_17DBD0_player@@QAEXHH@Z @ 0x001B8250
void type_17DBD0_player::sub_1B8250(RwInt32 arg_0, RwInt32 arg_4)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 ebp_14;
    RwV3d *lv_10;
    RwV3d slot_C;

    ebp_14 = 0;
    if (sub_1B8420() == 2)
        ebp_14 = 1;
    lv_10 = 0;
    if (arg_0 == 2)
    {
        slot_C = *vf_0CC();
        slot_C.y -= unk_1A00;
        lv_10 = &slot_C;
    }
    dword_4F6A7C.sub_1A4A20(ebp_14, arg_0, unk_4F7EB8.sub_1AEC70(), lv_10, arg_4);
    unk_229C = 0;
}

// match: ?sub_1B82F0@type_17DBD0_player@@QAEXH@Z @ 0x001B82F0
void type_17DBD0_player::sub_1B82F0(RwInt32 arg_0)
{
    if (dword_4F6A7C.sub_1A5920(arg_0, this) == 1)
    {
        if (sub_1B8420() == dword_4F6A7C.sub_1A5950(arg_0))
        {
            if (dword_4F6A7C.unk_00[arg_0].get_unk_00() == 2)
                dword_4F6A7C.sub_1A4A20(arg_0, 0, unk_4F7EB8.sub_1AEC70(), 0, 0);
        }
        else
            sub_1B81D0();
    }
}

// match: ?sub_1B8380@type_17DBD0_player@@QAEXXZ @ 0x001B8380
void type_17DBD0_player::sub_1B8380()
{
    if (dword_4FB9E0.get_unk_08() != 4)
        return;
    sub_1B82F0(0);
    sub_1B82F0(1);
    if (unk_229C == 1 && unk_22A0 != -1 && sub_1B8420() == dword_4F6A7C.sub_1A5950(unk_22A0) &&
        dword_4F6A7C.unk_00[unk_22A0].get_unk_00() == 0)
        sub_1B8250(0, 1);
}

// match: ?sub_1B8420@type_17DBD0_player@@QAEHXZ @ 0x001B8420
RwInt32 type_17DBD0_player::sub_1B8420()
{
    RwInt32 r = unk_4F7EB8.unk_29C;
    return r;
}

// match: ?sub_1B8440@type_17DBD0_player@@QAEXXZ @ 0x001B8440
void type_17DBD0_player::sub_1B8440()
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 bp_4;
    bool lv_5;

    if (dword_4FB9E0.get_unk_08() != 8)
        return;
    lv_5 = false;
    if (sub_1B8420() == 2 && !dword_4FB9E0.get_unk_10C())
        lv_5 = true;
    if (sub_1B8420() == 4 && dword_4FB9E0.get_unk_10C())
        lv_5 = true;
    if (lv_5 && !get_unk_19D0_r() && unk_2294 != -1 && dword_4F6950.sub_1A4090(unk_2294) == 1)
    {
        if (dword_4B9190)
            dword_4B9190->sub_E0410(0xA);
        RwReal var_C = unk_4B9308.sub_EE8F0(unk_3D8, 0xF);
        if (var_C != 0.0f)
            sub_1B85C0();
    }
    if (!get_unk_19D0_r() && !lv_5)
    {
        bp_4 = dword_4F6950.sub_1A40C0(vf_0CC(), 0);
        if (bp_4 != -1)
        {
            if (dword_4B9190)
                dword_4B9190->sub_E0410(2);
            RwReal var_10 = unk_4B9308.sub_EE8F0(unk_3D8, 0xF);
            if (var_10 != 0.0f)
                sub_1B86D0(bp_4);
        }
    }
}

// match: ?sub_1B85C0@type_17DBD0_player@@QAEXXZ @ 0x001B85C0
void type_17DBD0_player::sub_1B85C0()
{
    if (get_unk_19D0_r() == 0x10)
        return;
    unk_2290 = 0;
    sub_10E750(0, 1);
    dword_4F6950.sub_1A41C0(unk_2294, 2, unk_4F7EB8.sub_1AEC70(), 0);
    sub_1090F0(0x10);
}

// match: ?sub_1B8630@type_17DBD0_player@@QAEXH@Z @ 0x001B8630
void type_17DBD0_player::sub_1B8630(RwInt32 arg_0)
{
    if (get_unk_19D0_r() != 0x10)
        return;
    sub_10E750(1, 1);
    dword_4F6950.sub_1A41C0(unk_2294, arg_0, unk_4F7EB8.sub_1AEC70(), 0);
    sub_1090F0(0);
}

// match: ?sub_1B8690@type_17DBD0_player@@QAEXXZ @ 0x001B8690
void type_17DBD0_player::sub_1B8690()
{
    if (get_unk_19D0_r() != 0x10)
        return;
    sub_10E750(1, 1);
    sub_1090F0(0);
}

// match: ?sub_1B86D0@type_17DBD0_player@@QAEXH@Z @ 0x001B86D0
void type_17DBD0_player::sub_1B86D0(RwInt32 arg_0)
{
    if (get_unk_19D0_r() == 0x11)
        return;
    unk_2290 = 0;
    sub_10E750(0, 1);
    dword_4F6950.sub_1A41C0(arg_0, 4, unk_4F7EB8.sub_1AEC70(), 0);
    sub_1090F0(0x11);
    unk_2298 = arg_0;
}

// match: ?sub_1B8740@type_17DBD0_player@@QAEXH@Z @ 0x001B8740
void type_17DBD0_player::sub_1B8740(RwInt32 arg_0)
{
    if (get_unk_19D0_r() != 0x11 || unk_2298 == -1)
        sub_1090F0(0);
    else
    {
        sub_10E750(1, 1);
        dword_4F6950.sub_1A41C0(unk_2298, arg_0, unk_4F7EB8.sub_1AEC70(), 0);
        sub_1090F0(0);
        unk_2298 = -1;
    }
}

// match: ?sub_1B87D0@type_17DBD0_player@@QAEXXZ @ 0x001B87D0
void type_17DBD0_player::sub_1B87D0()
{
    if (get_unk_19D0_r() != 0x11)
        return;
    sub_10E750(1, 1);
    sub_1090F0(0);
    unk_2298 = -1;
}

// match: ?sub_1B8820@type_17DBD0_player@@QAEXXZ @ 0x001B8820
void type_17DBD0_player::sub_1B8820()
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 m_18 = unk_4F7EB8.sub_1AEC70();
    type_3DA434 ebp_14;
    type_3DD948 *bp_4;

    ebp_14.unk_08 = 1;
    ebp_14.sub_1C5A80(99.99f);
    ebp_14.unk_04 = unk_1AE4;
    sub_1ACBA0(m_18, &ebp_14);
    unk_19DC = 0;
    unk_19D0 = 0xA;
    bp_4 = (type_3DD948 *)unk_2110.sub_D4910();
    if (bp_4)
        bp_4->unk_3B0 = 0;
}

// match: ?pvf_008@type_17DBD0_player@@UAEPAUtype_1F8560_v@@XZ @ 0x001B88C0
type_1F8560_v *type_17DBD0_player::pvf_008()
{
    return &unk_2270;
}

// match: ?pvf_010@type_17DBD0_player@@UAEMXZ @ 0x001B88E0
RwReal type_17DBD0_player::pvf_010()
{
    return unk_530;
}

// match: ?pvf_014@type_17DBD0_player@@UAEHXZ @ 0x001B8900
RwInt32 type_17DBD0_player::pvf_014()
{
    return unk_2284;
}

// match: ?pvf_018@type_17DBD0_player@@UAEHXZ @ 0x001B8920
RwInt32 type_17DBD0_player::pvf_018()
{
    if (unk_1B2C)
        return unk_1AF0;
    return unk_1AE4;
}

// match: ?pvf_01C@type_17DBD0_player@@UAEHXZ @ 0x001B8950
RwInt32 type_17DBD0_player::pvf_01C()
{
    return unk_1B18 && !unk_1A48[unk_1AE4]->unk_11 ? 1 : 0;
}

// match: ?pvf_020@type_17DBD0_player@@UAEHXZ @ 0x001B89A0
RwInt32 type_17DBD0_player::pvf_020()
{
    return unk_1B04;
}

// match: ?pvf_024@type_17DBD0_player@@UAEHXZ @ 0x001B89C0
RwInt32 type_17DBD0_player::pvf_024()
{
    return unk_1A48[unk_1AE4]->unk_12;
}

// match: ?pvf_028@type_17DBD0_player@@UAEHXZ @ 0x001B89F0
RwInt32 type_17DBD0_player::pvf_028()
{
    return unk_1B2C;
}

// match: ?pvf_02C@type_17DBD0_player@@UAEHXZ @ 0x001B8A10
RwInt32 type_17DBD0_player::pvf_02C()
{
    return unk_19D0 == 1;
}

// match: ?pvf_030@type_17DBD0_player@@UAEHXZ @ 0x001B8A30
RwInt32 type_17DBD0_player::pvf_030()
{
    return unk_19D0 == 0xD;
}

// match: ?pvf_034@type_17DBD0_player@@UAEHXZ @ 0x001B8A50
RwInt32 type_17DBD0_player::pvf_034()
{
    return unk_1A48[unk_1AE4]->unk_11;
}

// match: ?pvf_038@type_17DBD0_player@@UAEHXZ @ 0x001B8A80
RwInt32 type_17DBD0_player::pvf_038()
{
    return unk_19D0 == 0;
}

// An explosion's hit: the player's own hit (vf_068), then the health lost
// (a percentage, at most 100) sent to the other peers. Killed: the kill
// message, logged and shown ("MW_GEN_KILLS_YOUACCIDENT" for its own grenade,
// else "MW_GEN_KILLS_YOUGREN" with the thrower's name, who is told), counted,
// and when not hosting scored and its pickups dropped. Wounded: the wound
// message, logged. The peers go straight to the sends through the checked
// accessors (types/type_DC400.h), as in sub_1ACBA0.
// match: ?vf_068@type_17DBD0_player@@UAEHPAUtype_758F0@@@Z @ 0x001B8AA0
// match: __ehhandler$?vf_068@type_17DBD0_player@@UAEHPAUtype_758F0@@@Z-0xB @ 0x00302DB0
// match: __ehhandler$?vf_068@type_17DBD0_player@@UAEHPAUtype_758F0@@@Z @ 0x00302DBB
RwInt32 type_17DBD0_player::vf_068(type_758F0 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    if (unk_19DC > 0.0f)
    {
        RwReal var_10 = unk_19DC;

        type_10F710::vf_068(arg_0);
        RwReal lv_14 = (var_10 - unk_19DC) * unk_19E0;
        lv_14 = sub_22C20(lv_14, 0.0f, 100.0f);
        if (unk_19DC <= 0.0f)
        {
            RwChar fp_11C[0x100];
            type_3E1164 var_13C;
            RwInt32 var_140;

            var_13C.unk_04 = lv_14;
            var_13C.unk_08.unk_00 = arg_0->unk_0C->pos.x;
            var_13C.unk_08.unk_04 = arg_0->unk_0C->pos.y;
            var_13C.unk_08.unk_08 = arg_0->unk_0C->pos.z;
            var_13C.unk_14 = arg_0->unk_10;
            var_140 = unk_4F7EB8.sub_1AF1B0(arg_0->unk_04.sub_D4910());
            if (var_140 == -1)
                var_13C.unk_18 = (RwUInt8)unk_4F7EB8.sub_1AEC70();
            else
                var_13C.unk_18 = (RwUInt8)var_140;
            var_13C.unk_1C = unk_4F7EB8.sub_1AD730();
            // Two compiled-out checks (docs/toolchain.md): the registers
            // after them are two loads on.
            if (!unk_2288)
            {
            }
            if (!unk_2288)
            {
            }
            type_4F8058::get()->sub_1DDDB0(&var_13C, type_4F8054::get()->get_unk_B0_checked()->others_checked());
            sub_1A8A70(&unk_4F7EB8, "Local player killed by grenade from player %d\n", var_13C.unk_18);
            if (var_13C.unk_18 == unk_4F7EB8.sub_1AEC70())
            {
                strcpy(fp_11C, sub_E3970("MW_GEN_KILLS_YOUACCIDENT", 1).c_str());
            }
            else
            {
                sub_1CB000(fp_11C, sub_E3970("MW_GEN_KILLS_YOUGREN", 1).c_str(),
                           type_4F8054::get()->get_unk_B0()->unk_90[var_13C.unk_18].unk_00);
                unk_4F7EB8.sub_1ADB40(var_13C.unk_18);
            }
            sub_EACA0(fp_11C, 0, 0);
            dword_4F8288.sub_1C28F0(unk_4F7EB8.sub_1AEC70(), 1, 1);
            if (!unk_4F61F8.unk_104)
            {
                unk_4F7EB8.unk_04.sub_1B2D00(unk_2288, unk_4F7EB8.sub_1AF1B0(arg_0->unk_04.sub_D4910()), 1);
                unk_4F7EB8.sub_1ADB80(var_13C.unk_1C, 0);
            }
        }
        else
        {
            type_1DDE20_mask var_144 = type_4F8054::get()->get_unk_B0_checked()->others_checked();
            type_3E1194 lv_15C;

            lv_15C.unk_04 = lv_14;
            lv_15C.unk_08.unk_00 = arg_0->unk_0C->pos.x;
            lv_15C.unk_08.unk_04 = arg_0->unk_0C->pos.y;
            lv_15C.unk_08.unk_08 = arg_0->unk_0C->pos.z;
            lv_15C.unk_14 = arg_0->unk_10;
            type_4F8058::get()->sub_1DDE90(&lv_15C, var_144);
            sub_1A8A70(&unk_4F7EB8, "Local player wounded by grenade from player %d\n",
                       unk_4F7EB8.sub_1AF1B0(arg_0->unk_04.sub_D4910()));
        }
    }
    return 0;
}

// A bullet's hit on the part: while alive, the player's hit; 1 when it
// killed it.
// match: ?pvf_03C@type_17DBD0_player@@UAEHPAUtype_75600@@@Z @ 0x001B9060
RwInt32 type_17DBD0_player::pvf_03C(type_75600 *arg_0)
{
    if (unk_19DC > 0.0f)
    {
        type_10F710::vf_064(arg_0);
        if (unk_19DC <= 0.0f)
            return 1;
    }
    return 0;
}

// By the stance (unk_1A04): 0 for 0, 8 for 2, else 7.
// match: ?sub_1B90C0@type_17DBD0_player@@QAEHXZ @ 0x001B90C0
RwInt32 type_17DBD0_player::sub_1B90C0()
{
    RwInt32 r;

    switch (unk_1A04)
    {
    case 0:
        r = 0;
        break;
    case 2:
        r = 8;
        break;
    default:
        r = 7;
    }
    return r;
}

// match: ?vf_060@type_17DBD0_player@@UAEHPAUtype_3D3548@@@Z @ 0x001B9110
RwInt32 type_17DBD0_player::vf_060(type_3D3548 *arg_0)
{
    type_3D94B8 *var_4;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_2288)
    {
    }
    type_10F710::vf_060(arg_0);
    unk_2108.sub_D48D0(0);
    unk_228C.sub_D48D0(0);
    if (arg_0 && arg_0->unk_2C_14)
    {
        var_4 = (type_3D94B8 *)arg_0;
        unk_228C.sub_D48D0(var_4);
        RwInt32 var_8 = var_4->unk_3B0.sub_FB710();
        if (var_8 == 0x4B || var_8 == 0x4C || var_8 == 0x4D)
            sub_1B91E0();
    }
    return 0;
}

// match: ?sub_1B91B0@type_17DBD0_player@@QAEHXZ @ 0x001B91B0
RwInt32 type_17DBD0_player::sub_1B91B0()
{
    return sub_1064C0(unk_1B30[unk_1AE8]);
}

// Takes the pick-up touched (unk_228C) while alive. First by its settings
// index: 0x4B to 0x4D always; a weapon's rounds (0x12 to 0x2C, and 0x5D to
// 0x6A in pairs) when it carries that weapon, else a "no room" flash (flag
// 0xB, HUD 5); 0x4E to 0x5B the same flash; a weapon (2 to 0x11, 0x5C to
// 0x68 by threes) flag 0xC (HUD 6) and its name flashed, marked as its own
// when it carries it. With flag 0xB set (or rounds it can take) the
// message for it is shown, the rounds taken, its sound played and the
// manager told; with flag 0xC set (or its own weapon) the weapon is taken
// into the hand it frees or swapped with the one in hand (the old one's
// rounds dropped for the manager), or its rounds added, and the HUD told.
// match: ?sub_1B91E0@type_17DBD0_player@@QAEXXZ @ 0x001B91E0
void type_17DBD0_player::sub_1B91E0()
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 t20;
    RwInt32 l1C;
    RwInt32 m_18;
    type_3DF8D8 *ebp_14;
    bool bp_D;
    type_3D94B8 *slot_C;
    type_712B0 *bp_8;
    RwInt32 bp_4;
    type_4C09B0 *fp_2C;
    type_4C09B0 *q28;
    RwInt32 frm_24;
    RwInt32 var_40;
    RwInt32 stk_3C;
    RwInt32 ebp_38;
    RwUInt32 fp_34;
    bool stk_2D;

    bp_8 = (type_712B0 *)unk_344.unk_08;
    if (bp_8 && bp_8->vf_008() != 1)
        bp_8 = 0;
    t20 = -1;
    l1C = 0;
    ebp_14 = 0;
    bp_4 = 0;
    bp_D = false;
    if (unk_19DC <= 0.0f)
        return;
    slot_C = (type_3D94B8 *)unk_228C.sub_D4910();
    m_18 = slot_C->unk_3B0.sub_FB710();
    switch (m_18)
    {
    case 0x4B:
    case 0x4C:
    case 0x4D:
        l1C = 1;
        break;
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 0x1E:
    case 0x1F:
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2A:
    case 0x2B:
    case 0x2C:
    case 0x5D:
    case 0x5E:
    case 0x60:
    case 0x61:
    case 0x63:
    case 0x64:
    case 0x66:
    case 0x67:
    case 0x69:
    case 0x6A:
        if (sub_106830(m_18, unk_1B30[0]) || sub_106830(m_18, unk_1B30[1]))
            l1C = 1;
        else
        {
            sub_10F7E0(0xB, 1);
            if (dword_4B9190)
                dword_4B9190->sub_E0410(5);
        }
        break;
    case 0x4E:
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x5B:
        sub_10F7E0(0xB, 1);
        if (dword_4B9190)
            dword_4B9190->sub_E0410(5);
        break;
    case 0x2:
    case 0x3:
    case 0x4:
    case 0x5:
    case 0x6:
    case 0x7:
    case 0x8:
    case 0x9:
    case 0xA:
    case 0xB:
    case 0xC:
    case 0xD:
    case 0xE:
    case 0xF:
    case 0x10:
    case 0x11:
    case 0x5C:
    case 0x5F:
    case 0x62:
    case 0x65:
    case 0x68:
        sub_10F7E0(0xC, 1);
        if (dword_4B9190)
            dword_4B9190->sub_E0410(6);
        frm_24 = sub_1068A0(m_18);
        if ((frm_24 == unk_1B30[0] || frm_24 == unk_1B30[1]) && !unk_1B2C)
            bp_4 = 1;
        if (frm_24 != -1)
            sub_EAB80(unk_1D1C[frm_24], 6);
    }
    if (sub_10F710() == 0xB || l1C)
    {
        switch (slot_C->unk_3B0.sub_FB710())
        {
        case 0x4B:
        case 0x4C:
        case 0x4D:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FA4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x12:
        case 0x13:
        case 0x14:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FAC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x15:
        case 0x16:
        case 0x17:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FB4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x18:
        case 0x19:
        case 0x1A:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FBC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x1B:
        case 0x1C:
        case 0x1D:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FC4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x1E:
        case 0x1F:
        case 0x20:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FCC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x21:
        case 0x22:
        case 0x23:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FD4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x24:
        case 0x25:
        case 0x26:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FDC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x27:
        case 0x28:
        case 0x29:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FE4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x2A:
        case 0x2B:
        case 0x2C:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B8FEC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x5D:
        case 0x5E:
            sub_EACA0("Picked up Enfield ammo", 0, 0);
            break;
        case 0x60:
        case 0x61:
            sub_EACA0("Picked up G43 ammo", 0, 0);
            break;
        case 0x63:
        case 0x64:
            sub_EACA0("Picked up Kar 98 ammo", 0, 0);
            break;
        case 0x66:
        case 0x67:
            sub_EACA0("Picked up Mosin Nagant Sniper ammo", 0, 0);
            break;
        case 0x69:
        case 0x6A:
            sub_EACA0("Picked up Grease Gun ammo", 0, 0);
            break;
        case 0x4E:
        case 0x4F:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B9054);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x50:
        case 0x51:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B905C);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x52:
        case 0x53:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B9064);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x54:
        case 0x55:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B906C);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x56:
        case 0x57:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B9074);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x58:
        case 0x59:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B907C);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            break;
        case 0x5A:
        case 0x5B:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B9084);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
        }
        unk_21B4.sub_1159C0(slot_C);
        q28 = sub_FB6C0(slot_C->unk_3B0.sub_FB710());
        if (q28->unk_1C.unk_00)
            unk_1C0.sub_8A980(&q28->unk_1C, this, 1, sub_CD550(), 0, 0);
        unk_4F7EB8.sub_1AE520((type_1AE520 *)slot_C);
        sub_10F7E0(0xB, 0);
        unk_2240 = 0;
        return;
    }
    if (sub_10F710() == 0xC || bp_4)
    {
        switch (slot_C->unk_3B0.sub_FB710())
        {
        case 0x2:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B909C);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 8;
            break;
        case 0x4:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90A4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0xB;
            break;
        case 0x5:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90AC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0xA;
            break;
        case 0x3:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90B4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 7;
            break;
        case 0x6:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90BC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 9;
            break;
        case 0x7:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90C4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 2;
            break;
        case 0x8:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90CC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 4;
            break;
        case 0x9:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90D4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 6;
            break;
        case 0xA:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90DC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 3;
            break;
        case 0xB:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90E4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 5;
            break;
        case 0xC:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90EC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0xE;
            break;
        case 0xE:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90FC);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0xF;
            break;
        case 0xF:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B9104);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0x12;
            break;
        case 0x10:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B910C);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0;
            break;
        case 0x11:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B9114);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 1;
            break;
        case 0x5C:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B911C);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0xC;
            break;
        case 0x5F:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B9124);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0xD;
            break;
        case 0xD:
        case 0x62:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B90F4);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0x10;
            break;
        case 0x68:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B912C);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0x25;
            break;
        case 0x65:
            ebp_14 = sub_198800((type_3DF8D8_04 *)&unk_4B9134);
            sub_EACA0(ebp_14->sub_197550(0, 0), 0, 0);
            t20 = 0x11;
            break;
        default:
            t20 = -1;
        }
        fp_2C = sub_FB6C0(slot_C->unk_3B0.sub_FB710());
        if (fp_2C->unk_1C.unk_00)
            unk_1C0.sub_8A980(&fp_2C->unk_1C, this, 1, sub_CD550(), 0, 0);
        if (t20 != -1)
        {
            if (t20 != unk_1AE4)
            {
                stk_2D = false;
                ebp_38 = unk_1AE8 == 0;
                if (t20 == unk_1B30[ebp_38])
                    stk_2D = true;
                if (!stk_2D)
                {
                    fp_34 = slot_C->unk_3B0.unk_04;
                    if (unk_1B30[ebp_38] == -1)
                    {
                        unk_1B30[ebp_38] = t20;
                        unk_1A48[t20]->vf_008(this, unk_1A3C.get_unk_08(), t20);
                        sub_100200(unk_1B30[unk_1AE8 == 0]);
                    }
                    else if (unk_1B30[unk_1AE8] == -1)
                    {
                        unk_1B30[unk_1AE8] = t20;
                        unk_1A48[t20]->vf_008(this, unk_1A3C.get_unk_08(), t20);
                    }
                    else
                    {
                        stk_3C = sub_1064C0(unk_1B30[unk_1AE8]);
                        if (stk_3C != -1)
                        {
                            var_40 = unk_1A48[unk_1B30[unk_1AE8]]->unk_414 + unk_1A48[unk_1B30[unk_1AE8]]->unk_418;
                            unk_1A48[unk_1B30[unk_1AE8]]->unk_418 = 0;
                            unk_1A48[unk_1B30[unk_1AE8]]->unk_414 = 0;
                            unk_4F7EB8.sub_1AE750((type_1AE520 *)slot_C, stk_3C, var_40);
                            bp_D = true;
                        }
                        if (unk_1A48[unk_1AE4]->unk_21C)
                        {
                            unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                            unk_1A48[unk_1AE4]->unk_21C = 0;
                        }
                        if (unk_1A48[unk_1AE4]->unk_46)
                        {
                            unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                            unk_1A48[unk_1AE4]->unk_21C = 0;
                            unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
                            unk_1A48[unk_1AE4]->unk_46 = 0;
                        }
                        unk_1A48[unk_1AE4]->sub_117370();
                        unk_1B30[unk_1AE8] = t20;
                        unk_1AE4 = t20;
                        unk_1A48[unk_1AE4]->vf_008(this, unk_1A3C.get_unk_08(), unk_1AE4);
                        unk_1A48[unk_1AE4]->sub_1170B0(1, 1);
                    }
                    unk_1A48[t20]->unk_414 = fp_34;
                    if (unk_1A48[t20]->unk_414 > unk_1A48[t20]->get_unk_448()->unk_C8)
                    {
                        fp_34 = unk_1A48[t20]->unk_414 - unk_1A48[t20]->get_unk_448()->unk_C8;
                        unk_1A48[t20]->unk_414 = unk_1A48[t20]->get_unk_448()->unk_C8;
                    }
                    else
                        fp_34 = 0;
                    unk_1A48[t20]->unk_418 = fp_34;
                    sub_108B60();
                    unk_2134 = sub_10E930();
                }
                else
                {
                    unk_1A48[t20]->unk_418 = unk_1A48[t20]->unk_418 + slot_C->unk_3B0.unk_04;
                    if (unk_1A48[t20]->unk_418 > unk_1A48[t20]->get_unk_448()->unk_CC)
                        unk_1A48[t20]->unk_418 = unk_1A48[t20]->get_unk_448()->unk_CC;
                }
            }
            else
            {
                unk_1A48[unk_1AE4]->unk_418 = unk_1A48[unk_1AE4]->unk_418 + slot_C->unk_3B0.unk_04;
                if (unk_1A48[unk_1AE4]->unk_418 > unk_1A48[unk_1AE4]->get_unk_448()->unk_CC)
                    unk_1A48[unk_1AE4]->unk_418 = unk_1A48[unk_1AE4]->get_unk_448()->unk_CC;
                if (!unk_1A48[unk_1AE4]->unk_414 && !unk_1A48[unk_1AE4]->unk_12)
                    unk_1A48[unk_1AE4]->vf_020();
                sub_115390(unk_1A48[unk_1AE4]->unk_414, unk_1A48[unk_1AE4]->unk_418);
                dword_4B9190->sub_E07A0(unk_1A48[unk_1AE4]->unk_414, unk_1A48[unk_1AE4]->get_unk_448()->unk_C8);
            }
        }
        if (!bp_D)
            unk_4F7EB8.sub_1AE520((type_1AE520 *)slot_C);
        sub_10F7E0(0xC, 0);
        unk_2240 = 0;
    }
}

// The look and strafe turns for the time arg_0 while defusing or planting,
// from its trigger's crouched settings (the stance's recoil scale is read
// but not used).
// match: ?sub_1BA5F0@type_17DBD0_player@@QAEXM@Z @ 0x001BA5F0
void type_17DBD0_player::sub_1BA5F0(RwReal arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_4C19C0 *slot_C;
    RwReal bp_8;
    type_712B0_10F710 *bp_4;

    bp_8 = 1.0f;
    slot_C = unk_1A48[unk_1AE4]->unk_448;
    if (unk_1B04)
        bp_8 = slot_C->unk_47C_r[unk_1A04];
    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
        bp_4 = 0;
    if (!bp_4)
        return;
    unk_28 |= 0x3C;
    unk_10C = bp_4->unk_184;
    unk_134 = bp_4->unk_19C;
    sub_10A330(bp_4->unk_154, arg_0);
    sub_109AE0(bp_4->unk_1B4, arg_0);
}

// Defusing for the time arg_0 (a site to defuse, else it stops): done after
// 4.0f seconds, the site told (state 3, at its feet); stopped when
// the button is let go.
// match: ?vf_250@type_17DBD0_player@@UAEXM@Z @ 0x001BA700
void type_17DBD0_player::vf_250(RwReal arg_0)
{
    RwV3d var_10;
    RwReal var_4;

    if (unk_2294 == -1)
        sub_1B8630(0);
    else
    {
        unk_2290 += arg_0 / 60.0f;
        if (unk_2290 >= 4.0f)
        {
            var_10 = *vf_0CC();
            var_10.y -= unk_1A00;
            sub_10E750(1, 1);
            dword_4F6950.sub_1A41C0(unk_2294, 3, unk_4F7EB8.sub_1AEC70(), &var_10);
            sub_1090F0(0);
        }
        sub_1BA5F0(arg_0);
        var_4 = unk_4B9308.sub_EE8F0(unk_3D8, 0x25);
        if (var_4 != 0.0f)
            sub_1B8630(0);
    }
}

// Planting for the time arg_0 at the site within reach (none: it stops, 3;
// a site not free: stops with its state): done after 4.0f seconds;
// stopped when the button is let go.
// match: ?vf_254@type_17DBD0_player@@UAEXM@Z @ 0x001BA810
void type_17DBD0_player::vf_254(RwReal arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwReal bp_4;

    bp_8 = dword_4F6950.sub_1A40C0(vf_0CC(), 1);
    if (bp_8 == -1)
        sub_1B8740(3);
    else if (dword_4F6950.sub_1A3D50(bp_8) != 4)
        sub_1B8740(dword_4F6950.sub_1A3D50(bp_8));
    else
    {
        unk_2290 += arg_0 / 60.0f;
        if (unk_2290 >= 4.0f)
        {
            slot_C = 0;
            sub_1B8740(0);
        }
        sub_1BA5F0(arg_0);
        bp_4 = unk_4B9308.sub_EE8F0(unk_3D8, 0x25);
        if (bp_4 != 0.0f)
            sub_1B8740(3);
    }
}

// Entering (arg_4 1) or leaving the bomb site trigger arg_0 in the bomb
// game: its site kept, or forgotten (a defuse under way stops).
// match: ?sub_1BA910@type_17DBD0_player@@QAEXPAUtype_712B0@@_N@Z @ 0x001BA910
void type_17DBD0_player::sub_1BA910(class type_712B0 *arg_0, bool arg_4)
{
    RwInt32 var_4;

    if (dword_4FB9E0.get_unk_08() != 8)
        return;
    var_4 = dword_4F6950.sub_1A4170(arg_0);
    if (arg_4 == 1)
        unk_2294 = var_4;
    else
    {
        if (get_unk_19D0_r() == 0x10)
            sub_1B8630(0);
        unk_2294 = -1;
    }
}

// Entering (arg_4 1) or leaving the flag base trigger arg_0: its flag kept
// or forgotten.
// match: ?sub_1BA980@type_17DBD0_player@@QAEXPAVTrigger@@_N@Z @ 0x001BA980
void type_17DBD0_player::sub_1BA980(class Trigger *arg_0, bool arg_4)
{
    RwInt32 var_4;

    var_4 = dword_4F6A7C.sub_1A4920(arg_0);
    if (arg_4 == 1)
        unk_22A0 = var_4;
    else
        unk_22A0 = -1;
}

// An ally and an enemy by the entity's flags, swapped when the manager's
// sub_1AF280 says so.
// match: ?vf_248@type_17DBD0_player@@UAEHPAUtype_3D3548@@@Z @ 0x001BA9D0
RwInt32 type_17DBD0_player::vf_248(type_3D3548 *arg_0)
{
    if (unk_4F7EB8.sub_1AF280())
        return arg_0->unk_2C_1;
    return arg_0->unk_2C_0;
}

// match: ?vf_24C@type_17DBD0_player@@UAEHPAUtype_3D3548@@@Z @ 0x001BAA10
RwInt32 type_17DBD0_player::vf_24C(type_3D3548 *arg_0)
{
    if (unk_4F7EB8.sub_1AF280())
        return arg_0->unk_2C_0;
    return arg_0->unk_2C_1;
}

// Its health set to arg_0; at none it dies (sub_1B8820).
// match: ?vf_23C@type_17DBD0_player@@UAEXM@Z @ 0x001BAA50
void type_17DBD0_player::vf_23C(RwReal arg_0)
{
    unk_19DC = arg_0;
    if (arg_0 <= 0.0)
        sub_1B8820();
}




// (Compiler-written.)







// Its part's +0x02C: the this-adjusting thunk (sub ecx, 0x2260) to its
// vf_05C.













// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_17DBD0_player@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_17DBD0_player::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ??2type_1AE520@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_1AE520::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ??2type_1BABA0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_1BABA0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?vf_008@type_3E1170@@UAEHXZ (folded into 0x39180)
RwInt32 type_3E1170::vf_008()
{
    return 11;
}

// ?vf_008@type_3E11A0@@UAEHXZ (folded into 0xC5540)
RwInt32 type_3E11A0::vf_008()
{
    return 3;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_17DBD0_player@@SAXPAX@Z (folded into 0x19A750)
void type_17DBD0_player::operator delete(void * arg_0)
{
}

// ??3type_1AE520@@SAXPAX@Z (folded into 0x19A750)
void type_1AE520::operator delete(void * arg_0)
{
}

// ??3type_1BABA0@@SAXPAX@Z (folded into 0x19A750)
void type_1BABA0::operator delete(void * arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_17DBD0_player@@SAXPAX0@Z (folded into 0x19A750)
void type_17DBD0_player::operator delete(void * arg_0, void * arg_4)
{
}

// ??3type_1AE520@@SAXPAX0@Z (folded into 0x19A750)
void type_1AE520::operator delete(void * arg_0, void * arg_4)
{
}

// ??3type_1BABA0@@SAXPAX0@Z (folded into 0x19A750)
void type_1BABA0::operator delete(void * arg_0, void * arg_4)
{
}
