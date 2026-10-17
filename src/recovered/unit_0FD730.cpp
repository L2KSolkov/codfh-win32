// The player entity (types/type_10F710.h; "Player::Init()" in its set-up's
// messages): its constructor, set-up and overrides, after the game's line
// test and the aim pass (once unit_0FC6F0): one object from 0xFC6F0, its
// .rdata the line test's constants (16.666666 among them), then this file's,
// the weapon name tables' texts, and the aim pass's literals (PLAN M7). The
// original file name is not in the image, so it is named for the player's
// start address.

#include <math.h>
#include <string.h>
#include <stdio.h>

#include "rw/ostypes.h"
#ifdef CODFH_WIN32
// The port's mouse look (port/src/xpal_sys.cpp): the mouse's movement since the last call, in
// degrees, turned straight into the local player's view rather than through the pad's stick (its
// dead zone, rate cap and acceleration made the mouse lag and overshoot).
extern "C" RwReal port_mouse_yaw(void);
extern "C" RwReal port_mouse_pitch(void);
#endif
#include "types/type_3D3548.h"
#include "types/type_10F710.h"
#include "types/animobjpool.h"
#include "types/type_3DD948.h"
#include "types/type_3D2E7C.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DF8D8.h"
#include "types/alfaobject.h"
#include "types/animbank.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_3D51C0.h"
#include "types/type_3DF30.h"
#include "types/type_DA0A0.h"
#include "types/soundbank.h"
#include "types/type_DC400.h"
#include "types/type_92430.h"
#include "types/type_3D5658.h"
#include "types/type_3D94B8.h"
#include "types/RenderTrigger.h"
#include "types/type_3DBC78.h"
#include "types/type_3DC048.h"
#include "rw/badevice.h"
#include "types/musicplayer.h"
#include "types/SplinePath.h"
#include "game/clumpdata.h"
#include "types/CGlobalSounds.h"
#include "types/type_4E1B70.h"
#include "types/VehicleEnterExitTrigger.h"
#include "game/textmanager.h"
#include "types/LadderTrigger.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/baengine.h"
#include "game/gameloop.h"
#include "rw/rphanim.h"
#include "types/type_3D32F8.h"
#include "types/type_72810.h"
#include "types/type_4C19C0.h"
#include "types/type_4C09B0.h"
#include "types/PickupTrigger.h"
#include "game/savestate.h"
#include "types/PlayerTrigger.h"
#include "rws/camerahelper.h"
#include "game/vecutil.h"
#include "game/netmsg.h"
#include "game/mathutil.h"
#include "game/frand.h"
#include "rw/rtquat.h"
#include "types/animkey.h"
#include "xmmintrin.h"
#include "game/clumputil.h"
#include "types/type_4D1DB8.h"
#include "types/alfamessman.h"
#include "types/EndLevelTrigger.h"
#include "game/netplayer.h"
#include "game/weaponbank.h"
#include "types/type_FC6F0.h"
#include "types/type_4B85F8.h"
#include "types/type_3DC9B0.h"
#include "types/VehicleTrigger.h"
#include "rws/clumphelper.h"
#include "game/pooledconsts.h"
// The pad table (game/padlib.h) without Direct3D's and DirectSound's headers, whose
// declarations this unit makes its own.
#define NOD3D
#define NODSOUND
#include "game/padlib.h"
#include <xmmintrin.h>
#include "rw/rpcollis.h"
#include "types/type_4E5D30.h"

#ifdef CODFH_DRAW_TRIGGERS
// port/src/debug/trigdraw.cpp: noclip for the local player
extern RwBool g_bTrigDrawNoclip;
void TrigDrawNoclipMove(RwV3d *pvPos, RwReal fStep);
#endif
// match: __ehhandler$??0type_10F710@@QAE@PAUtype_712B0@@@Z>1>8 @ 0x0041D200
// match: __ehhandler$??0type_10F710@@QAE@PAUtype_712B0@@@Z>1 @ 0x0041D268
// match: __ehhandler$??1type_10F710@@UAE@XZ>1>8 @ 0x0041D284
// match: __ehhandler$??1type_10F710@@UAE@XZ>1 @ 0x0041D2F4

// Its data definitions (PLAN M5), in the image's address order.
// 0x00429700
RwUInt8 byte_429700 = 1;
// 0x00429704
RwInt32 dword_429704 = 150;
// 0x00429708
RwReal flt_429708 = 100.0f;
// 0x0042970C
RwReal flt_42970C = 0.08f;
// 0x00429710
RwReal flt_429710 = 0.4f;
// 0x00429714
RwReal flt_429714 = 500.0f;
// 0x00429718
RwReal flt_429718 = 20.0f;
// 0x0042971C
RwReal flt_42971C = 80.0f;
// 0x00429720
RwReal flt_429720 = 8.0f;
// 0x00429724
RwReal flt_429724 = 0.075f;
// 0x00429728
RwReal flt_429728 = 0.6f;
// 0x0042972C
RwReal flt_42972C = 50.0f;
// 0x00429730
RwReal flt_429730 = 1000.0f;
// 0x00429734
RwReal flt_429734 = 0.4f;
// 0x00429738
RwReal flt_429738 = 0.2f;
// 0x0042973C
RwReal flt_42973C = 1000.0f;
// 0x00429740
RwReal flt_429740 = 10.0f;
// 0x00429744
RwInt32 dword_429744 = 1;
// 0x00429748
RwReal flt_429748 = 0.075f;
// 0x0042974C
RwReal flt_42974C = 0.2f;
// 0x00429750
RwReal dword_429750 = 0.6f;
// 0x00429754
RwReal dword_429754 = 0.8f;
// 0x00429758
RwInt32 dword_429758 = 4;
// 0x0042975C
RwInt32 dword_42975C = 8;
// 0x00429760
RwInt32 dword_429760 = 2;
// 0x00429768
// The weapons' names in each language (39 each; dword_429A84 picks one).
const RwChar *off_429768[39] = {
    "Bazooka",
    "Panzerschreck",
    "BAR",
    "Bren",
    "DP",
    "M1919A6",
    "MG42",
    "MP40",
    "PPSH",
    "Sten",
    "Thompson",
    "Luger",
    "Enfield",
    "G43",
    "Mosin Nagant",
    "M1 Garand",
    "Kar98",
    "Nagant Sniper",
    "Springfield",
    "M8 Smoke",
    "Mark2 Frag",
    "RGD33",
    "Stielhandgrenate",
    "Browning 50cal",
    "M1919A4",
    "Maxim",
    "MG42 Mounted",
    "Flak38",
    "Flak88",
    "T34 Cannon",
    "T34 Coax",
    "ST74",
    "Mosin Ammo Clip",
    "Teller Mine",
    "KaiserBear Grenade",
    "Sherman Cannon",
    "Sherman Coax",
    "Grease Gun",
    "StickyBear Grenade",
};
// 0x00429808
const RwChar *off_429808[39] = {
    "Bazooka",
    "Panzerschreck",
    "BAR",
    "Bren",
    "DP",
    "M1919A6",
    "MG42",
    "MP40",
    "PPSh",
    "Sten",
    "Thompson",
    "Luger",
    "Enfield",
    "G43",
    "Mosin Nagant",
    "M1 Garand",
    "Kar98",
    "Nagant de pr\351cision",
    "Springfield",
    "M8 fumig\350nes",
    "Grenades Mark 2",
    "RGD33",
    "Stielhandgrenaten",
    "Browning cal. 50",
    "M1919A4",
    "Maxim",
    "MG42",
    "Flak38",
    "Flak88",
    "Canon T34",
    "T34 Coax.",
    "ST74",
    "Munitions Mosin",
    "Mines Teller",
    "Grenades KaiserBear",
    "canon Sherman",
    "Sherman Coax.",
    "Grease Gun",
    "Grenades StickyBear",
};
// 0x004298A8
const RwChar *off_4298A8[39] = {
    "Bazooka",
    "Panzerfaust",
    "BAR",
    "Bren",
    "DP",
    "M1919A6",
    "MG42",
    "MP40",
    "PPSH",
    "Sten",
    "Thompson",
    "Luger",
    "Enfield",
    "G43",
    "Mosin Nagant",
    "M1 Garand",
    "Kar98",
    "Nagant-Scharfs",
    "Springfield",
    "Rauchgranate",
    "Mark2",
    "RGD33",
    "Stielhandgranate",
    "Browning .50 Kal",
    "M1919A4",
    "Maxim",
    "MG42",
    "Flak38",
    "Flak88",
    "T34-Gesch\374tz",
    "T34",
    "ST74",
    "Mosin-Munition",
    "Tellermine",
    "Kaiserb\344r-Granate",
    "Sherman-Gesch\374tz",
    "Sherman",
    "MP",
    "Haftb\344r-Granate",
};
// 0x00429948
const RwChar *off_429948[39] = {
    "Bazooka",
    "Panzerschreck",
    "BAR",
    "Bren",
    "DP",
    "M1919A6",
    "MG42",
    "MP40",
    "PPSH",
    "Sten",
    "Thompson",
    "Luger",
    "Enfield",
    "G43",
    "Mosin Nagant",
    "M1 Garand",
    "Kar98",
    "Nagant da cecchino",
    "Springfield",
    "Granate fumogene",
    "Granate Mark2",
    "Granate RGD33",
    "Stielhandgrenaten",
    "Browning cal. 50",
    "M1919A4",
    "Maxim",
    "MG42",
    "Flak38",
    "Flak88",
    "Cannone T34",
    "Coassiale T34",
    "ST74",
    "Munizioni per Mosin",
    "Mina Teller",
    "Granata Kaiserbear",
    "Cannone Sherman",
    "Coassiale Sherman",
    "Grease Gun",
    "Granata adesiva",
};
// 0x004299E8
const RwChar *off_4299E8[39] = {
    "bazuca",
    "Panzerschreck",
    "BAR",
    "Bren",
    "DP",
    "M1919A6",
    "MG42",
    "MP40",
    "PPSH",
    "Sten",
    "Thompson",
    "Luger",
    "Enfield",
    "G43",
    "Mosin Nagant",
    "M1 Garand",
    "Kar98",
    "Nagant de francotirador",
    "Springfield",
    "Granadas de humo",
    "Granadas de Mark2",
    "Granadas de RGD33",
    "Granadas de palo",
    "Browning 50cal",
    "M1919A4",
    "Maxim",
    "MG42",
    "Flak38",
    "Flak88",
    "Ca\361\363n de T34",
    "Coax. de T34",
    "ST74",
    "Munici\363n de Mosin",
    "Minas Teller",
    "Granadas de oso Kaiser",
    "Ca\361on de Sherman",
    "Coax. de Sherman",
    "Pistola de engrase",
    "Granadas de oso pegajoso",
};
// 0x00429A84
// The weapons' names by language (sub_19B0A0).
const RwChar **dword_429A84[7] = {
    off_429768, off_4298A8, off_429808, off_4298A8, off_429808, off_429948, off_4299E8,
};
// 0x00429AA0
RwInt32 dword_429AA0 = 3;
// 0x00429AA4
RwReal flt_429AA4 = 90000.0f;
// 0x00429AA8
RwReal flt_429AA8 = 30625.0f;
// 0x00429AAC
RwReal flt_429AAC = 5.0f;
// 0x00429AB0
RwReal flt_429AB0 = 0.5f;
// 0x00429AB4
RwReal flt_429AB4 = 40.0f;
// 0x00429AB8
RwReal flt_429AB8 = 20.0f;
// 0x00429ABC
RwReal flt_429ABC = 15.0f;
// 0x00429AC0
RwReal flt_429AC0 = 0.5f;
// 0x00429AC4
RwReal flt_429AC4 = 0.5f;
// 0x00429AC8
RwReal flt_429AC8 = 0.1f;
// 0x00429ACC
RwReal flt_429ACC = 0.5f;
// 0x00429AD0
RwReal flt_429AD0 = 30.0f;
// 0x00429AD4
RwReal flt_429AD4 = 0.025f;
// 0x00429AD8
RwReal flt_429AD8 = 0.5f;
// 0x00429ADC
RwReal flt_429ADC = 100.0f;
// 0x00429AE0
RwReal flt_429AE0 = -0.01f;
// 0x00429AE4
RwReal flt_429AE4 = -0.0125f;
// 0x00429AE8
RwReal flt_429AE8 = 0.0625f;
// 0x00429AEC
RwReal flt_429AEC = 0.125f;
// 0x00429AF0
RwReal flt_429AF0 = -0.01f;
// 0x00429AF4
RwReal flt_429AF4 = -0.0125f;
// 0x00429AF8
RwReal flt_429AF8 = 0.0625f;
// 0x00429AFC
RwReal flt_429AFC = 0.125f;
// 0x00429B00
RwReal flt_429B00 = 0.75f;
// 0x00429B04
RwReal flt_429B04 = 0.5f;
// 0x00429B08
RwReal flt_429B08 = 20.0f;
// 0x00429B0C
RwReal flt_429B0C = 1.5f;
// 0x00429B10
RwReal flt_429B10[3] = { 38.0f, 38.0f, 19.0f };
// 0x00429B1C
RwReal flt_429B1C = 0.8f;
// 0x00429B20
RwReal flt_429B20 = 1.25f;
// 0x00429B24
RwReal flt_429B24 = 1.5f;
// 0x00429B28
RwReal flt_429B28[3] = { 25.0f, 20.0f, 10.0f };
// 0x00429B34
RwReal flt_429B34 = 2.0f;
// 0x00429B38
RwReal flt_429B38 = 120.0f;
// 0x00429B3C
RwInt32 dword_429B3C = 1;
// 0x004C1940
RwUInt8 byte_4C1940;
// (Defined after the data: VC7.1 emits a unit's data definitions in reverse order, and
// the image has these constants before the data's texts.)
// 0x003D9728
extern const RwReal flt_3D9728 = -5.0f;
// 0x003D972C
extern const RwReal flt_3D972C = 16.666666f;
// 0x003D9730
extern const RwV3d stru_3D9730 = { 1.0f, 0.0f, 0.0f };
// 0x003D973C
extern const RwV3d stru_3D973C = { 0.0f, 1.0f, 0.0f };
#ifndef CODFH_SP // single player has neither unreferenced 0.01f: 90000.0f follows the y axis (SP 0x2E5BFC)
// 0x003D9748
extern const RwReal flt_3D9748 = 0.01f;
// 0x003D974C
extern const RwReal flt_3D974C = 0.01f;
#endif
// 0x003D9750
extern const RwReal flt_3D9750 = 90000.0f;
// End of its data definitions.

// From 0xFC6F0: the game's line test (sub_FCAE0) and the player's aim pass over an atomic
// (sub_FCD90), the start of this object (its .rdata opens with their constants).


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D9728@@3MB @ 0x003D9728
// match: ?flt_3D972C@@3MB @ 0x003D972C
// match: ?stru_3D9730@@3URwV3d@@B @ 0x003D9730
// match: ?stru_3D973C@@3URwV3d@@B @ 0x003D973C
// match: ?flt_3D9748@@3MB @ 0x003D9748
// match: ?flt_3D974C@@3MB @ 0x003D974C
// match: __real@42652eed @ 0x003D9CAC
// match: __real@44fa0000 @ 0x003D9CB0
// match: __real@3f333333 @ 0x003D9CB4

// match: ?sub_FC6F0@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x000FC6F0
// sp-match: ?sub_FC6F0@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x000BFA70

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *sub_FC6F0(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8, void *arg_C)
{
    type_FC6F0 *fp_68;
    RwReal lv_64;
    RwV3d lcl_60[3];
    RwV3d ebp_3C;
    RwV3d frm_30[3];
    RwV3d slot_C;

    fp_68 = (type_FC6F0 *)arg_C;
    if (arg_8 >= fp_68->unk_04)
    {
        return arg_4;
    }
    static RwV3d *dword_4C1960[3] = { &frm_30[0], &frm_30[1], &frm_30[2] };
    slot_C = arg_0->t.line.start;
    lcl_60[0] = *arg_4->vertices[0];
    lcl_60[1] = *arg_4->vertices[1];
    lcl_60[2] = *arg_4->vertices[2];
    sub_141590(frm_30, lcl_60, 3, fp_68->unk_20);
    sub_141320(&ebp_3C, &arg_4->normal, fp_68->unk_24);
    fp_68->unk_00 = 1;
    fp_68->unk_08 = ebp_3C;
    fp_68->unk_04 = arg_8;
    RwV3dSub(&fp_68->unk_14, &arg_0->t.line.end, &arg_0->t.line.start);
    lv_64 = RwV3dLength(&fp_68->unk_14);
    if (lv_64 != 0.0f)
    {
        RwV3dScale(&fp_68->unk_14, &fp_68->unk_14, (lv_64 * arg_8) / lv_64);
        RwV3dAdd(&fp_68->unk_14, &fp_68->unk_14, &arg_0->t.line.start);
    }
    return arg_4;
}

// match: ?sub_FC8F0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000FC8F0
// sp-match: ?sub_FC8F0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000BFBF0
RpAtomic *sub_FC8F0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10)
{
    type_91F40 *var_4;
    type_FC6F0 var_2C;
    type_3D3548 *var_30;
    RwMatrix var_70;

    if (!arg_8->geometry)
    {
        return arg_8;
    }
    var_4 = (type_91F40 *)arg_10;
    var_2C.unk_00 = 0;
    var_2C.unk_04 = var_4->unk_04;
    var_30 = sub_FB960(arg_8);
    if (var_30)
    {
        if (!var_30->unk_28_2)
        {
            return arg_8;
        }
        var_2C.unk_20 = RwFrameGetLTM(RpAtomicGetFrame(arg_8));
        var_2C.unk_24 = &var_70;
        RwMatrixOrthoNormalize(var_2C.unk_24, var_2C.unk_20);
        RpAtomicForAllIntersections(arg_8, arg_0, sub_FC6F0, &var_2C);
        if (var_2C.unk_00)
        {
            var_4->unk_00 = 1;
            var_4->unk_08 = var_2C.unk_14;
            var_4->unk_14 = var_2C.unk_08;
            var_4->unk_04 = var_2C.unk_04;
        }
    }
    return arg_8;
}

// match: ?sub_FC9F0@@YAXPAURwV3d@@PAUtype_91F40@@PAHPAM00H@Z @ 0x000FC9F0
// sp-match: ?sub_FC9F0@@YAXPAURwV3d@@PAUtype_91F40@@PAHPAM00H@Z @ 0x000BFCB0
void sub_FC9F0(RwV3d *arg_0, type_91F40 *arg_4, RwInt32 *arg_8, RwReal *arg_C, RwV3d *arg_10, RwV3d *arg_14,
               RwInt32 arg_18)
{
    RwV3d var_10;
    RwReal var_4;

    if (arg_4->unk_00)
    {
        if (!arg_18)
        {
            RwV3dSub(&var_10, &arg_4->unk_08, arg_0);
            var_4 = RwV3dDotProduct(&arg_4->unk_14, &var_10);
            if (var_4 > 0.0f)
            {
                return;
            }
        }
        if (arg_10)
        {
            if (arg_4->unk_04 < *arg_C)
            {
                *arg_10 = arg_4->unk_08;
                *arg_C = arg_4->unk_04;
                *arg_8 = 1;
                if (arg_14)
                {
                    *arg_14 = arg_4->unk_14;
                }
            }
        }
        else
        {
            *arg_8 = 1;
        }
    }
}

// match: ?sub_FCAE0@@YAHPAURwV3d@@000HHH@Z @ 0x000FCAE0
// sp-match: ?sub_FCAE0@@YAHPAURwV3d@@000HHH@Z @ 0x000BFD60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_FCAE0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C, RwInt32 arg_10, RwInt32 arg_14,
                  RwInt32 arg_18)
{
    type_4E5D30 *stk_60;
    RwInt32 y5C;
    type_4E5D30 *slot_58;
    RwInt32 frm_54;
    type_91F40 s50;
    RwReal frm_24;
    RpIntersection t20;
    RwInt32 bp_4;

    t20.type = rpINTERSECTLINE;
    t20.t.line.start = *arg_0;
    t20.t.line.end = *arg_4;
    if ((arg_0->x - arg_4->x < 0.0f ? -(arg_0->x - arg_4->x) : arg_0->x - arg_4->x) < 0.1f
        && (arg_0->y - arg_4->y < 0.0f ? -(arg_0->y - arg_4->y) : arg_0->y - arg_4->y) < 0.1f
        && (arg_0->z - arg_4->z < 0.0f ? -(arg_0->z - arg_4->z) : arg_0->z - arg_4->z) < 0.1f)
    {
        return 0;
    }
    bp_4 = 0;
    frm_24 = 1e37f;
    s50.unk_00 = 0;
    s50.unk_04 = frm_24;
    for (frm_54 = 0; frm_54 < 4; frm_54++)
    {
        slot_58 = &dword_4E5D30[frm_54];
        if (slot_58->get_unk_00() && slot_58->get_unk_28())
        {
            sub_91F40(slot_58->get_unk_28(), &t20.t.line, &s50, 0, arg_10, 1);
            sub_FC9F0(&t20.t.line.start, &s50, &bp_4, &frm_24, arg_8, arg_C, arg_18);
        }
        if (!arg_8 && bp_4)
        {
            return bp_4;
        }
    }
    if (!arg_14)
    {
        return bp_4;
    }
    for (y5C = 0; y5C < 4; y5C++)
    {
        stk_60 = &dword_4E5D30[y5C];
        if (stk_60->get_unk_00() && stk_60->get_unk_28())
        {
            RpWorldForAllAtomicIntersections(stk_60->get_unk_28(), &t20, sub_FC8F0, &s50);
            sub_FC9F0(&t20.t.line.start, &s50, &bp_4, &frm_24, arg_8, arg_C, arg_18);
        }
        if (!arg_8 && bp_4)
        {
            return bp_4;
        }
    }
    return bp_4;
}

// match: ?sub_FCD90@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000FCD90
// sp-match: ?sub_FCD90@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000BFF50
// The player's aim pass over one atomic (arg_10 is the aim, a type_4C194C):
// a soldier or vehicle ahead of the camera, within its stance's height of
// the aim line where it passes and within the player trigger's sideways
// reach (wider for allies, growing with the distance), scores by how near
// along the ray it is. For an enemy the part hit (vf_07C) is kept and the
// hit must be real; for an ally the bearing to it is kept. Any other
// entity with vf_010 scores by its triangles (sub_FD700).
RpAtomic *sub_FCD90(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10)
{
    type_4C194C *var_4;
    type_10F710 *var_8;
    type_3D3548 *var_C;
    RwReal var_10;
    RwFrame *var_14;
    RwV3d var_20;
    RwMatrix *var_24;
    RwV3d *var_28;
    RwV3d var_34;
    RwV3d var_40;
    RwV3d var_4C;
    RwReal var_50;
    RwReal var_B4;
    RwReal var_B8;
    type_3D3548 *var_BC;
    type_3D3548 *var_C0;
    RwReal var_C4;
    RwReal var_C8;
    RwReal var_CC;
    RwReal var_D0;
    RwReal var_134;
    RwReal var_138;
    RwReal var_13C;
    RwReal var_144;
    type_712B0_10F710 *var_14C;
    RwReal var_150;
    RwReal var_154;
    RwReal var_158;
    RwInt32 var_15C;
    RwReal var_160;
    RwReal var_164;
    RwReal var_168;
    RwReal var_16C;
    RwReal var_188;
    RwReal var_18C;
#ifndef CODFH_SP
    type_FD700 var_194;
#endif
    RwReal var_198;

    var_4 = (type_4C194C *)arg_10;
    if (arg_C > 1.0f || arg_C < 0.0f)
    {
        return arg_8;
    }
    var_8 = (type_10F710 *)sub_1745A0(0);
    var_C = 0;
    if (!var_8)
    {
        return arg_8;
    }
    var_C = sub_FB960(arg_8);
    var_10 = 0.0f;
    if (var_C->vf_008() || var_C->vf_024())
    {
        var_14 = var_C->unk_338.unk_08;
        var_20 = RwFrameGetMatrix(var_14)->pos;
        var_24 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
        var_28 = &var_24->pos;
        var_34 = var_24->at;
        RwV3dNormalize(&var_34, &var_34);
        var_40 = var_24->right;
        var_4->unk_10 = -1;
        if (var_8->vf_248(var_C) && var_C->vf_008() && ((type_3DAFC8 *)var_C)->unk_62C[0])
        {
            dword_4B9190->sub_E84E0((type_3DAFC8 *)var_C);
        }
        RwV3dSubMacro(&var_4C, &var_20, var_28);
        var_50 = RwV3dDotProductMacro(&var_4C, &var_34);
        if (var_50 <= 0.0f)
        {
            return arg_8;
        }
        do
        {
            __m128 a = _mm_set_ss(var_34.x * var_34.x + var_34.z * var_34.z);
            __m128 b = _mm_sqrt_ss(a);
            _mm_store_ss(&var_B4, b);
        } while (0);
        if (var_B4 == 0.0f)
        {
            return arg_8;
        }
        var_B8 = 0.0f;
        if (var_C->vf_008())
        {
            var_BC = var_C;
            if (var_BC->vf_0BC() == 0)
            {
                var_B8 = var_BC->unk_48 * 2.0f;
            }
            else if (var_BC->vf_0BC() == 1)
            {
                var_B8 = var_BC->unk_48;
            }
            else if (var_BC->vf_0BC() == 2)
            {
                var_B8 = var_BC->unk_48 / 2.0f;
            }
            else
            {
                var_B8 = var_BC->unk_48 * 2.0f;
            }
        }
        else if (var_C->vf_024())
        {
            var_C0 = var_C;
            if (var_C0->vf_0BC() == 0)
            {
                var_B8 = var_C0->unk_48 * 2.0f;
            }
            else if (var_C0->vf_0BC() == 1)
            {
                var_B8 = var_C0->unk_48;
            }
            else if (var_C0->vf_0BC() == 2)
            {
                var_B8 = var_C0->unk_48 / 2.0f;
            }
            else
            {
                var_B8 = var_C0->unk_48 * 2.0f;
            }
        }
        var_C4 = var_20.y + var_B8;
        var_C8 = var_B8 * 0.7f;
        var_CC = var_C4;
        var_D0 = var_C4 - var_C8;
        do
        {
            __m128 a = _mm_set_ss(var_4C.x * var_4C.x + var_4C.z * var_4C.z);
            __m128 b = _mm_sqrt_ss(a);
            _mm_store_ss(&var_134, b);
        } while (0);
        var_13C = (var_138 = var_34.y / var_B4) * var_134 + var_28->y;
        if (var_13C > var_CC || var_13C < var_D0)
        {
            return arg_8;
        }
        var_144 = var_4C.x * var_40.x + var_4C.z * var_40.z < 0.0f ? -(var_4C.x * var_40.x + var_4C.z * var_40.z)
                                                                  : var_4C.x * var_40.x + var_4C.z * var_40.z;
        var_14C = (type_712B0_10F710 *)var_8->get_unk_34C();
        var_150 = 0.0f;
        if (var_8->vf_24C(var_C))
        {
            var_154 = var_14C->unk_330 - var_14C->unk_32C;
            var_158 = var_134;
            if (var_158 > 2000.0f)
            {
                var_158 = 2000.0f;
            }
            var_150 = var_134 * var_154 / 2000.0f;
            var_150 += var_14C->unk_32C;
        }
        else
        {
            var_150 = var_14C->unk_328;
        }
        if (var_144 > var_150)
        {
            return arg_8;
        }
        if (var_8->vf_248(var_C))
        {
            var_15C = var_C->vf_07C(1, arg_0, &arg_C, 1);
            if (var_15C == -1 || arg_C < 0.0f)
            {
                return arg_8;
            }
            var_4->unk_10 = var_15C;
        }
        var_160 = 1.0f - arg_C / var_4->unk_00;
        var_164 = 1.0f - var_144 / 100.0f;
        var_10 = var_160 * 1.0f + var_164 * 0.0f;
        if (var_10 > var_4->unk_04)
        {
            var_4->unk_04 = var_10;
            var_4->unk_08.sub_D48D0(var_C);
            if (var_8->vf_24C(var_C))
            {
                var_4C.y = 0.0f;
                var_34.y = 0.0f;
                var_50 = RwV3dDotProductMacro(&var_34, &var_4C);
                var_168 = RwV3dLength((RwV3d *)&var_34);
                var_16C = var_134 * var_168;
                if (var_16C == 0.0f)
                {
                    var_16C = 0.001f;
                }
                var_16C = (var_16C = var_50 / var_16C) > -1.0f ? var_16C : -1.0f;
                var_16C = var_16C > 1.0f ? 1.0f : var_16C;
                var_188 = acos(0.99999f > (var_16C > -0.99999f ? var_16C : -0.99999f)
                                   ? (var_16C > -0.99999f ? var_16C : -0.99999f)
                                   : 0.99999f);
                var_18C = RwV3dDotProductMacro(&var_4C, &var_40);
                if (var_18C < 0.0f)
                {
                    var_188 = -var_188;
                }
                var_4->unk_0C = 57.295826f * var_188;
            }
        }
    }
    else if (var_C->vf_010())
    {
        if (RpAtomicGetGeometry(arg_8))
        {
#ifdef CODFH_SP // shape: block-scoped (SP 0xBFF50's frame)
            type_FD700 var_194;

#endif
            var_194.unk_00 = false;
            var_194.unk_04 = 1.0e37f;
            RpAtomicForAllIntersections(arg_8, arg_0, sub_FD700, &var_194);
            if (var_194.unk_00)
            {
                var_198 = 1.0f - arg_C / var_4->unk_00;
                var_10 = var_198;
                if (var_10 > var_4->unk_04)
                {
                    var_4->unk_04 = var_10;
                    var_4->unk_08.sub_D48D0(var_C);
                }
            }
        }
        else
        {
            return arg_8;
        }
    }
    else
    {
        return arg_8;
    }
    return arg_8;
}

// match: ?sub_FD700@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x000FD700
// sp-match: ?sub_FD700@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x000BFF30
RpCollisionTriangle *sub_FD700(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8, void *arg_C)
{
    type_FD700 *var_4 = (type_FD700 *)arg_C;

    if (arg_8 < var_4->unk_04)
    {
        var_4->unk_04 = arg_8;
        var_4->unk_00 = true;
    }
    return 0;
}


// Clamps arg_0 to arg_4..arg_8: inline, with no address and so no database
// name; named for what it does. Evidence: sub_112DA0 stores its argument into
// a slot of its own (fst) and overwrites that slot with a bound, then copies
// it out: an inlined parameter assigned in place.
inline RwReal clamp_f(RwReal arg_0, RwReal arg_4, RwReal arg_8)
{
    if (arg_0 < arg_4)
    {
        arg_0 = arg_4;
    }
    else if (arg_0 > arg_8)
    {
        arg_0 = arg_8;
    }
    return arg_0;
}


// What the player's update aims at (the aim pass fills it). Defining it here
// emits its dynamic initializer, which runs the implicit constructor
// (out of line), and its exit function, which runs the destructor.
type_4C194C dword_4C194C;


// The player made for the trigger arg_0. Nothing calls it (the link drops it), but
// it is why this unit emits the class's inline constructor first, and with the
// constructor its vtable's inline functions, scalar deleting destructor and
// destructor: the image has them at the head of this unit (0xFD730-0xFDB30), ahead of
// the network player's unit (unit_1B7B20), the constructor's only caller.
#ifndef CODFH_SP // single player has the real builder, sp_sub_C85E0 (below)
type_10F710 *type_10F710_make(type_712B0 *arg_0)
{
    return new type_10F710(arg_0);
}
#endif

// The constructor, its vtable's inline functions (types/type_10F710.h), the scalar
// deleting destructor and the destructor, emitted after it.
// match: ??0type_10F710@@QAE@PAUtype_712B0@@@Z @ 0x000FD730
// match: __ehhandler$??0type_10F710@@QAE@PAUtype_712B0@@@Z-0xB0 @ 0x00301210
// match: __ehhandler$??0type_10F710@@QAE@PAUtype_712B0@@@Z @ 0x003012C0
// match: ?vf_09C@type_10F710@@UAEHXZ @ 0x000FD8C0
// match: ?vf_0A0@type_10F710@@UAEXI@Z @ 0x000FD8E0
// match: ?vf_138@type_10F710@@UAEHXZ @ 0x000FD900
// match: ?vf_118@type_10F710@@UAEPAUtype_3D3548@@XZ @ 0x000FD920
// match: ?vf_11C@type_10F710@@UAEXPAUtype_3D3548@@@Z @ 0x000FD940
// match: ?vf_120@type_10F710@@UAEPAUAIData@@XZ @ 0x000FD960
// match: ?vf_174@type_10F710@@UAEHXZ @ 0x000FD980
// match: ?vf_178@type_10F710@@UAEXH@Z @ 0x000FD9B0
// match: ?vf_180@type_10F710@@UAEXH@Z @ 0x000FD9D0
// match: ?vf_17C@type_10F710@@UAEMXZ @ 0x000FDA00
// match: ?vf_23C@type_10F710@@UAEXM@Z @ 0x000FDA20
// match: ?vf_10C@type_10F710@@UAEMXZ @ 0x000FDA40
// match: ?vf_0FC@type_10F710@@UAEMXZ @ 0x000FDA60
// match: ?vf_100@type_10F710@@UAEMXZ @ 0x000FDA80
// match: ?vf_0BC@type_10F710@@UAEHXZ @ 0x000FDAA0
// match: ?vf_1E4@type_10F710@@UAEHXZ @ 0x000FDAC0
// match: ??_Gtype_10F710@@UAEPAXI@Z @ 0x000FDB00
// match: ??1type_10F710@@UAE@XZ @ 0x000FDB30
// match: __ehhandler$??1type_10F710@@UAE@XZ-0xB8 @ 0x003012D0
// match: __ehhandler$??1type_10F710@@UAE@XZ @ 0x00301388
// sp-match: ?vf_09C@type_10F710@@UAEHXZ @ 0x000C84A0
// sp-match: ?vf_0A0@type_10F710@@UAEXI@Z @ 0x000C84B0
// sp-match: ?vf_118@type_10F710@@UAEPAUtype_3D3548@@XZ @ 0x000C84D0
// sp-match: ?vf_11C@type_10F710@@UAEXPAUtype_3D3548@@@Z @ 0x000C84E0
// sp-match: ?vf_120@type_10F710@@UAEPAUAIData@@XZ @ 0x000C84F0
// sp-match: ?vf_174@type_10F710@@UAEHXZ @ 0x000C8500
// sp-match: ?vf_178@type_10F710@@UAEXH@Z @ 0x000C8520
// sp-match: ?vf_180@type_10F710@@UAEXH@Z @ 0x000C8540
// sp-match: ?vf_17C@type_10F710@@UAEMXZ @ 0x000C8560
// sp-match: ?vf_23C@type_10F710@@UAEXM@Z @ 0x000C8570
// sp-match: ?vf_10C@type_10F710@@UAEMXZ @ 0x000C8580
// sp-match: ?vf_0FC@type_10F710@@UAEMXZ @ 0x000C8590
// sp-match: ?vf_100@type_10F710@@UAEMXZ @ 0x000C85A0
// sp-match: ?vf_0BC@type_10F710@@UAEHXZ @ 0x000C85B0
// sp-match: ?vf_1E4@type_10F710@@UAEHXZ @ 0x000C85C0
// sp-match: ??0type_10F710@@QAE@PAUtype_712B0@@@Z @ 0x000C83E0
// sp-match: ?vf_138@type_10F710@@UAEHXZ @ 0x000C84C0
// sp-match: ??1type_10F710@@UAE@XZ @ 0x000CE650
// sp-match: ??_Gtype_10F710@@UAEPAXI@Z @ 0x000CE630

#ifdef CODFH_SP
// Single player only: builds the player (a 0x2260-byte type_10F710) for the
// trigger arg_0 as sub_73710 builds an entity (PlayerTrigger::HandleEvents
// calls it, SP 0x862FE and 0x8641B; declared in unit_0A9980).
// sp-match: ?sp_sub_C85E0@@YAPAUtype_10F710@@PAVPlayerTrigger@@@Z @ 0x000C85E0
type_10F710 *sp_sub_C85E0(PlayerTrigger *arg_0)
{
    type_712B0 *trigger = (type_712B0 *)static_cast<Trigger *>(arg_0);
    type_10F710 *var_10;

    var_10 = (type_10F710 *)sub_D56D0(0x2260, trigger->unk_24_18, trigger->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_10F710(trigger);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
    return var_10;
}
#endif

// Its set-up ("Player::Init()"): its trigger (unk_344's, when a player
// trigger) gives its collision boxes, field of view, eye height and yaw
// scale; the inventory is emptied, then refilled with the health from the
// checkpoint when the trigger says so ("using player attribs from previous
// level or from memCard"); the states, the aim assist and the view are
// cleared; its frame, animation, collision atomic and weapons' names (by
// language) are made; the pad's buttons 29 and 30 are read; the HUD shows
// the health packs' count. 1.
// match: ?sub_FDC10@type_10F710@@QAEHPAUtype_712B0@@@Z @ 0x000FDC10
// sp-match: ?sub_FDC10@type_10F710@@QAEHPAUtype_712B0@@@Z @ 0x000C4AF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::sub_FDC10(type_712B0 *arg_0)
{
    RwInt32 v14 = 0;
    RwInt32 var_5C;
    RwInt32 bp_58;
    RwInt32 p54;
    RwInt32 var_50;
    type_D90B0 *m_4C;
    RwFrame *local_48;
    RwInt32 local_44;
    RpAtomic *local_40;
    RwChar p3C[32];
    type_7C8D0 *bp_18;
    type_712B0_10F710 *lv_10;
    RwV3d var_C;

    unk_2254 = 1;
    unk_2258 = 0;
    sub_CCCD0(arg_0);
    lv_10 = (type_712B0_10F710 *)unk_344.unk_08;
    if (lv_10 && lv_10->vf_008() != 1)
    {
        lv_10 = 0;
    }
    unk_28 = 0x2017C; // not an address: flags
    unk_2C = 0x11;
    unk_30 = 0x32FFFE7;
    unk_530 = 0.0f;
    unk_19D4 = 0;
    unk_10C = lv_10->unk_190;
    unk_134 = lv_10->unk_1A8;
    unk_130 = 0;
    unk_1AE8 = 0;
    unk_2134 = 2;
    unk_2138 = 1;
    unk_3D8 = 0;
    unk_3DC = dword_4F28F0->get_unk_1C();
    sub_FEFE0();
    unk_3E0 = 90.0f;
    unk_3D4 = -1;
    unk_48 = 100.5f;
    unk_4C = 90.0f;
    unk_50_r = 52.6f;
    unk_534 = lv_10->unk_F0;
    unk_538 = 1.0f;
    unk_53C = 0.0f;
    unk_540 = 0.0f;
    zero_v3d(&unk_3C_v);
    unk_108 = flt_3D9728;
    for (v14 = 0; v14 < 2; v14++)
        unk_1B30[v14] = -1;
    unk_21B4.sub_1154A0();
    if (lv_10->unk_254)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("NOTE: !!! Player::Init(): using player attribs from previous level or from memCard !!!\n");
#endif
        m_4C = &dword_4F28F0->unk_5C;
        for (var_50 = 0; var_50 < 13; var_50++)
        {
            if (m_4C->unk_18.unk_04[var_50])
            {
                switch (var_50)
                {
                case 2:
                case 5:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                    break;
                default:
                    unk_21B4.sub_116080(var_50, m_4C->unk_18.unk_04[var_50]);
                    unk_21B4.sub_115980(var_50);
                }
            }
        }
        unk_19E0 = m_4C->unk_50;
        unk_19DC = m_4C->unk_54;
    }
    else
    {
        unk_19E0 = 100;
        unk_19DC = 1.0f;
    }
    unk_3EC = 0.0f;
    unk_3F0 = 0.0f;
    unk_3F4 = 0.0f;
    unk_3F8 = 0.0f;
    unk_1A38 = 0.0f;
    unk_3FC = 0.0f;
    unk_400 = 0.0f;
    unk_404 = 0.0f;
    unk_408 = 0.0f;
    unk_414 = 0;
    unk_40C = 0.0f;
    unk_410 = 0.0f;
    unk_418 = 0.0f;
    unk_41C = 0.0f;
    unk_4F0 = 0.0f;
    unk_4F4 = 0.0f;
    unk_4F8 = 0;
    unk_51C = 0;
    unk_520 = 0;
    unk_420 = 0.0f;
    unk_424 = -3;
    unk_430 = 0;
    unk_428 = 0.0f;
    unk_42C = 0;
    unk_4FC = 0.0f;
    unk_500 = 0.0f;
    unk_504 = 0.0f;
    unk_508 = 0.0f;
    unk_50C = 0;
    unk_20CC = 0.0f;
    unk_20D0 = 0.0f;
    unk_20D4 = 0.0f;
    unk_20C8 = 0.0f;
    unk_20C4 = 0.0f;
    unk_20D8 = 0.0f;
    unk_20DC = dword_429744;
    unk_20E8 = 0;
    unk_20E0 = 0.0f;
    unk_20E4 = 0.0f;
    unk_1B20 = 0;
    unk_1B24 = 0;
    unk_510 = -1000000.0f;
    unk_518 = 0.0f;
    unk_514 = 0;
    unk_52C = 0.0f;
    unk_434.x = unk_434.y = unk_434.z = 0.0f;
    unk_440.x = unk_440.y = unk_440.z = 0.0f;
    unk_44C = dword_429750;
    unk_454 = 0;
    unk_46C = 0;
    unk_470 = lv_10->unk_1CC;
    unk_458 = 0;
    unk_45C = dword_429758;
    unk_460 = 0;
    unk_464 = 0.0f;
    unk_468 = 0.0f;
    unk_4D0 = 0;
    unk_4D4 = 2;
    unk_4D8 = 0;
    unk_4DC = 0.0f;
    unk_4E0 = unk_534;
    unk_4E4 = unk_534;
    unk_4E8 = 0.0f;
    unk_4EC = unk_534;
    unk_544 = 0.0f;
    unk_548 = 0.0f;
    unk_19D0 = 0;
    unk_19F8 = 0;
    unk_19FC = 0;
    unk_19F4 = 0;
    unk_19E4 = 0.0f;
    unk_19E8 = 0.0f;
    unk_19EC = 0.0f;
    unk_19F0 = 0.0f;
    unk_1A04 = 0;
    unk_1A08 = 0;
    unk_1A00 = lv_10->unk_144_a[0];
    unk_1A0C = 0;
    unk_1A10 = 0.0f;
    unk_1A18 = 0.0f;
    unk_19D8 = 0;
    unk_1A1C = 0;
    unk_1B28 = 0;
    unk_1B3C = 1;
    unk_1B40 = 1;
    unk_90.sub_CCC60();
    local_48 = RwFrameCreate();
    if (local_48)
    {
        RwFrameSetIdentity(local_48);
        unk_338.sub_129A70(local_48);
        unk_338.sub_129AE0(this);
    }
    var_5C = sub_78830(2);
    unk_280 = var_5C;
    bp_18 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = bp_18;
    bp_18->unk_1C = (RwInt32)this;
    sub_D5B80(this, 0xE);
    unk_1AE4 = 0;
    unk_1AEC = 0;
    unk_1AF4 = 0.0f;
    unk_1AF8.x = 0.0f;
    unk_1AF8.y = 0.0f;
    unk_1AF8.z = 0.0f;
    unk_1B04 = 0;
    unk_1B08 = 0;
    unk_1B0C = 0;
    unk_1B10 = 0;
    unk_1B14 = 0;
    unk_1B1C = 0;
    unk_1B2C = 0;
    unk_1B44 = 0;
    unk_20EC = 0;
    for (v14 = 0; v14 < 39; v14++)
        unk_1A48[v14] = 0;
    unk_2108.sub_D48D0(0);
    unk_210C.sub_D48D0(0);
    unk_2114.sub_D48D0(0);
    unk_1A34.sub_D48D0(0);
    unk_2180.sub_D48D0(0);
    unk_2184 = 0;
    unk_2188 = 0;
    unk_54C = 0;
    unk_550.sub_16BC0(this);
    unk_20FC = 0;
    var_C.x = 0.0f;
    var_C.y = 0.0f;
    var_C.z = 0.0f;
    local_40 = RpAtomicCreate();
    local_48 = RwFrameCreate();
    RwFrameSetIdentity(local_48);
    RpAtomicSetFrame(local_40, local_48);
    RwFrameAddChild(unk_338.get_unk_08(), local_48);
    local_40->boundingSphere.center = var_C;
    local_40->boundingSphere.radius = unk_4C;
    RpAtomicSetFlags(local_40, rpATOMICCOLLISIONTEST);
    sub_FB990(local_40, 4);
    sub_173320(local_40);
    unk_274.sub_129430(local_40);
    unk_274.sub_1294A0(this);
    unk_219C[0] = 75.0f;
    unk_219C[1] = 45.0f;
    unk_219C[2] = 25.0f;
    unk_21A8[0] = -45.0f;
    unk_21A8[1] = -15.0f;
    unk_21A8[2] = 20.0f;
    unk_58 = 0;
    unk_2100 = 0.0f;
    for (p54 = 0; p54 < 20; p54++)
        unk_21F0[p54] = 0;
    unk_2240 = 1;
    unk_1A30 = 1.0f;
    unk_2244 = 0;
    unk_2248 = unk_4B9308.sub_EED00(0x1D);
    unk_224C = unk_4B9308.sub_EED00(0x1E);
    unk_1B38 = 0;
    unk_2110.sub_D48D0(0);
    unk_2178 = 0;
    unk_2250 = 0;
    unk_2118.sub_D48D0(0);
    unk_213C.x = unk_213C.y = unk_213C.z = 0.0f;
    unk_2148 = 0.0f;
    unk_214C = 0.0f;
    unk_2150 = 0.0f;
    unk_2154 = 0;
    unk_2158 = 0.0f;
    unk_215C = 0;
    unk_2160 = 0;
    unk_1B48[0][0] = 60;
    unk_1B48[0][1] = 61;
    unk_1B48[0][2] = 62;
    unk_1B48[1][0] = 63;
    unk_1B48[1][1] = 64;
    unk_1B48[1][2] = 65;
    unk_1B48[2][0] = 33;
    unk_1B48[2][1] = 34;
    unk_1B48[2][2] = 35;
    unk_1B48[3][0] = 42;
    unk_1B48[3][1] = 43;
    unk_1B48[3][2] = 44;
    unk_1B48[4][0] = 36;
    unk_1B48[4][1] = 37;
    unk_1B48[4][2] = 38;
    unk_1B48[5][0] = 45;
    unk_1B48[5][1] = 46;
    unk_1B48[5][2] = 47;
    unk_1B48[6][0] = 39;
    unk_1B48[6][1] = 40;
    unk_1B48[6][2] = 41;
    unk_1B48[7][0] = 27;
    unk_1B48[7][1] = 28;
    unk_1B48[7][2] = 29;
    unk_1B48[8][0] = 21;
    unk_1B48[8][1] = 22;
    unk_1B48[8][2] = 23;
    unk_1B48[9][0] = 30;
    unk_1B48[9][1] = 31;
    unk_1B48[9][2] = 32;
    unk_1B48[10][0] = 24;
    unk_1B48[10][1] = 25;
    unk_1B48[10][2] = 26;
    unk_1B48[11][0] = 18;
    unk_1B48[11][1] = 19;
    unk_1B48[11][2] = 20;
    unk_1B48[12][0] = 94;
    unk_1B48[12][1] = 94;
    unk_1B48[12][2] = 93;
    unk_1B48[13][0] = 97;
    unk_1B48[13][1] = 97;
    unk_1B48[13][2] = 96;
    unk_1B48[14][0] = 48;
    unk_1B48[14][1] = 49;
    unk_1B48[14][2] = 50;
    unk_1B48[15][0] = 54;
    unk_1B48[15][1] = 55;
    unk_1B48[15][2] = 56;
    unk_1B48[16][0] = 100;
    unk_1B48[16][1] = 100;
    unk_1B48[16][2] = 99;
    unk_1B48[17][0] = 103;
    unk_1B48[17][1] = 103;
    unk_1B48[17][2] = 102;
    unk_1B48[18][0] = 57;
    unk_1B48[18][1] = 58;
    unk_1B48[18][2] = 59;
    unk_1B48[19][0] = -1;
    unk_1B48[19][1] = -1;
    unk_1B48[19][2] = -1;
    unk_1B48[20][0] = -1;
    unk_1B48[20][1] = -1;
    unk_1B48[20][2] = -1;
    unk_1B48[21][0] = -1;
    unk_1B48[21][1] = -1;
    unk_1B48[21][2] = -1;
    unk_1B48[22][0] = -1;
    unk_1B48[22][1] = -1;
    unk_1B48[22][2] = -1;
    unk_1B48[23][0] = 45;
    unk_1B48[23][1] = 46;
    unk_1B48[23][2] = 47;
    unk_1B48[24][0] = -1;
    unk_1B48[24][1] = -1;
    unk_1B48[24][2] = -1;
    unk_1B48[25][0] = -1;
    unk_1B48[25][1] = -1;
    unk_1B48[25][2] = -1;
    unk_1B48[26][0] = -1;
    unk_1B48[26][1] = -1;
    unk_1B48[26][2] = -1;
    unk_1B48[27][0] = -1;
    unk_1B48[27][1] = -1;
    unk_1B48[27][2] = -1;
    unk_1B48[28][0] = -1;
    unk_1B48[28][1] = -1;
    unk_1B48[28][2] = -1;
    unk_1B48[29][0] = -1;
    unk_1B48[29][1] = -1;
    unk_1B48[29][2] = -1;
    unk_1B48[30][0] = -1;
    unk_1B48[30][1] = -1;
    unk_1B48[30][2] = -1;
    unk_1B48[31][0] = -1;
    unk_1B48[31][1] = -1;
    unk_1B48[31][2] = -1;
    unk_1B48[32][0] = -1;
    unk_1B48[32][1] = -1;
    unk_1B48[32][2] = -1;
    unk_1B48[33][0] = -1;
    unk_1B48[33][1] = -1;
    unk_1B48[33][2] = -1;
    unk_1B48[34][0] = -1;
    unk_1B48[34][1] = -1;
    unk_1B48[34][2] = -1;
    unk_1B48[35][0] = -1;
    unk_1B48[35][1] = -1;
    unk_1B48[35][2] = -1;
    unk_1B48[36][0] = -1;
    unk_1B48[36][1] = -1;
    unk_1B48[36][2] = -1;
    unk_1B48[37][0] = 106;
    unk_1B48[37][1] = 106;
    unk_1B48[37][2] = 105;
    unk_1B48[38][0] = -1;
    unk_1B48[38][1] = -1;
    unk_1B48[38][2] = -1;
    local_44 = sub_19B0A0();
    for (bp_58 = 0; bp_58 < 39; bp_58++)
    {
        if (strlen(dword_429A84[local_44][bp_58]) >= 24)
        {
            strncpy(unk_1D1C[bp_58], dword_429A84[local_44][bp_58], 23);
            unk_1D1C[bp_58][23] = 0;
        }
        else
            strcpy(unk_1D1C[bp_58], dword_429A84[local_44][bp_58]);
    }
    ((PlayerTrigger *)arg_0)->sub_ACA70();
    unk_3DC = dword_4F28F0->get_unk_1C();
    sub_FEFE0();
    sub_108FF0(0);
    unk_2174.sub_D48D0(0);
    byte_4C1940 = 0;
    dword_4C19AC = 0;
    byte_429700 = 1;
    byte_4CF9AC = 0;
    flt_429C38 = 1.0f;
    sprintf(p3C, "%d", unk_21B4.sub_1E3BF0(1));
    sub_EAB80(p3C, 7);
    unk_20F0 = 1.0f;
    unk_20F4 = 0;
    ((PlayerTrigger *)arg_0)->unk_304 = dword_4F28F0->unk_181;
    return 1;
}

// match: ?sub_FEFE0@type_10F710@@QAEXXZ @ 0x000FEFE0
// sp-match: ?sub_FEFE0@type_10F710@@QAEXXZ @ 0x000C04A0
void type_10F710::sub_FEFE0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        dword_4F4638[var_4].unk_50 = dword_4F2AAC[unk_3DC];
    }
}

// match: ?sub_FF030@type_10F710@@QAEHXZ @ 0x000FF030
// sp-match: ?sub_FF030@type_10F710@@QAEHXZ @ 0x000C04F0
RwInt32 type_10F710::sub_FF030()
{
    RwFrame *var_C;
    RwMatrix *var_10;
#ifndef CODFH_SP
    RwMatrix var_50;
#endif
    RwMatrix var_90;

    var_C = get_unk_340();
    if (!var_C)
    {
        return 0;
    }
    var_10 = RwFrameGetMatrix(var_C);
    if (!var_10)
    {
        return 0;
    }
    if (var_10->up.y != 1.0f)
    {
#ifdef CODFH_SP // shape: block-scoped, so /O2 drops the identity's overwritten stores (SP 0xC04F0)
        RwMatrix var_50;

#endif
        RwMatrixSetIdentityMacro(&var_50);
        var_50.pos = var_10->pos;
        var_50.at.x = var_10->at.x;
        var_50.at.z = var_10->at.z;
        var_50.right.x = var_10->right.x;
        var_50.right.z = var_10->right.z;
        RwV3dNormalize(&var_50.at, &var_50.at);
        RwV3dNormalize(&var_50.right, &var_50.right);
        RwMatrixOrthoNormalize(&var_90, &var_50);
        *var_10 = var_90;
        RwFrameUpdateObjects(var_C);
    }
    else
    {
        return 1;
    }
    return 2;
}

// match: ?sub_FF1A0@type_10F710@@QAEXXZ @ 0x000FF1A0
// sp-match: ?sub_FF1A0@type_10F710@@QAEXXZ @ 0x000C05F0
void type_10F710::sub_FF1A0()
{
    RwV3d var_C;
    type_3DD948 *var_10;

    var_C.x = 0.0f;
    var_C.y = 10000.0f;
    var_C.z = 0.0f;
    var_10 = sub_174A70(&var_C, 60.0f, this);
    unk_2110.sub_D48D0(var_10);
    if (var_10)
    {
        var_10->unk_3C0 = get_unk_534();
    }
}

// match: ?sub_FF210@type_10F710@@QAEXXZ @ 0x000FF210
// sp-match: ?sub_FF210@type_10F710@@QAEXXZ @ 0x000C5760
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_FF210()
{
    RwUInt32 fp_2C;
    type_3DFEEC *q28;
    type_D90B0 *frm_24;
    RwInt32 t20;
    RwInt32 l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    type_3DF8D8 *lv_10;
    type_3D2E7C *slot_C;
    type_3DF30 *bp_8;
    type_712B0_10F710 *bp_4;

    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    sub_FF1A0();
    sub_83850(7, &unk_1C0, &unk_3B0);
    for (ebp_14 = 0; ebp_14 < 2; ebp_14++)
    {
        unk_1B30[ebp_14] = bp_4->unk_108[ebp_14];
    }
    sub_10C650();
    unk_1AE4 = bp_4->unk_13C;
    if (bp_4->unk_13C == unk_1B30[0])
    {
        unk_1AE8 = 0;
    }
    else
    {
        unk_1AE8 = 1;
    }
    sub_10D8A0();
    for (m_18 = 0; m_18 < 39; m_18++)
    {
        if (bp_4->unk_384[m_18] != -1)
        {
            l1C = -1;
            switch (m_18)
            {
            case 21:
                l1C = 2;
                break;
            case 33:
                l1C = 7;
                break;
            case 31:
                l1C = 5;
                break;
            case 20:
                l1C = 8;
                break;
            case 22:
                l1C = 9;
                break;
            case 19:
                l1C = 10;
                break;
            case 34:
                l1C = 11;
                break;
            case 38:
                l1C = 12;
                break;
            }
            if (l1C != -1)
            {
                if (bp_4->unk_384[m_18])
                {
                    unk_21B4.sub_116080(l1C, bp_4->unk_384[m_18]);
                    unk_21B4.sub_115980(l1C);
                }
            }
            else if (bp_4->unk_384[m_18] < unk_1A48[m_18]->unk_414)
            {
                unk_1A48[m_18]->unk_414 = bp_4->unk_384[m_18];
                unk_1A48[m_18]->unk_418 = 0;
            }
            else
            {
                if (bp_4->unk_254)
                {
                    t20 = bp_4->unk_384[m_18] % unk_1A48[m_18]->get_unk_448()->unk_C8;
                    if (t20)
                    {
                        unk_1A48[m_18]->unk_414 = t20;
                    }
                }
                unk_1A48[m_18]->unk_418 = bp_4->unk_384[m_18] - unk_1A48[m_18]->unk_414;
                if (unk_1A48[m_18]->unk_418 > unk_1A48[m_18]->get_unk_448()->unk_CC)
                {
                    unk_1A48[m_18]->unk_418 = unk_1A48[m_18]->get_unk_448()->unk_CC;
                }
            }
        }
    }
    unk_1A48[unk_1AE4]->sub_1170B0(1, 1);
    if (bp_4->unk_254)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("NOTE: !!! Player::SystemStartInit(): using player attribs from previous level or from memCard !!!\n");
#endif
        bp_4->unk_254 = 0;
        frm_24 = &dword_4F28F0->unk_5C;
        if (frm_24->unk_18.unk_00)
        {
            unk_21B4.sub_115980(frm_24->unk_18.unk_00);
        }
    }
    if (((type_712B0_10F710 *)get_unk_34C())->unk_244.unk_00)
    {
        q28 = (type_3DFEEC *)sub_198800(&((type_712B0_10F710 *)get_unk_34C())->unk_244);
        ((type_D48D0 *)&q28->unk_24_id)->sub_D48D0(this);
        q28->unk_10 = 10;
    }
    lv_10 = sub_198880("Scripts+ClassList+PlayerClass+Filename");
    fp_2C = sub_71870();
    unk_54C = fp_2C;
    slot_C = vf_098();
    slot_C->sub_70DF0(this, 2);
    slot_C->sub_70E10(lv_10->get_unk_18(), 1);
    sub_3EE10(this);
    bp_8 = unk_550.unk_56C;
    if (bp_8)
    {
        bp_8->sub_3E780(this);
    }
    sub_40A60(slot_C->sub_71340(), 2, 0, 1, 0);
    sub_35200(slot_C->sub_71340(), 0.0f, 1e37f, 6, 0, 0, 0, -1, -1);
    if (bp_4)
    {
        unk_1A20 = bp_4->unk_1F4;
        unk_1A24 = bp_4->unk_1F8;
        unk_1A28 = bp_4->unk_208;
    }
    unk_28 |= 0x20000; // not an address: a flag
}

// match: ?vf_230@type_10F710@@UAEXXZ @ 0x000FF740
// sp-match: ?vf_230@type_10F710@@UAEXXZ @ 0x000CD1B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::vf_230()
{
    type_3DFEEC *l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    type_3DC9B0 *lv_10;
    type_3D3548 *slot_C;
    type_3D2E7C *bp_8;
    type_712B0_10F710 *bp_4;

    if (unk_2254)
    {
        slot_C = vf_200();
        if (slot_C)
        {
            sub_10F810(0, 0);
        }
        if (unk_19D0 == 7)
        {
            lv_10 = (type_3DC9B0 *)unk_210C.sub_D4910();
            if (lv_10)
            {
                lv_10->sub_168A90(this);
            }
        }
        unk_550.sub_16C50();
        bp_8 = vf_098();
        if (bp_8)
        {
            sub_35330(bp_8->sub_71340());
            sub_40AE0(bp_8->sub_71340());
            sub_71970((type_3D2C88 *)bp_8);
            unk_54C = 0;
        }
        for (ebp_14 = 0; ebp_14 < 39; ebp_14++)
        {
            if (unk_1A48[ebp_14])
            {
                unk_1A48[ebp_14]->sub_117050();
            }
        }
        if (unk_1A3C.get_unk_08())
        {
            unk_1A3C.sub_129940(1);
        }
        for (m_18 = 0; m_18 < 39; m_18++)
        {
            if (unk_1A48[m_18])
            {
                delete unk_1A48[m_18];
            }
        }
        if (unk_338.get_unk_08())
        {
            unk_338.sub_129B10();
        }
        sub_78870(unk_280);
        unk_280 = 0;
        bp_4 = (type_712B0_10F710 *)get_unk_34C();
        if (bp_4->unk_244.unk_00)
        {
            l1C = (type_3DFEEC *)sub_198800(&bp_4->unk_244);
            ((type_D48D0 *)&l1C->unk_24_id)->sub_D48D0(0);
        }
        unk_21B4.sub_115500();
        unk_2254 = 0;
        unk_274.sub_1294D0();
    }
    sub_1745C0(this, unk_3D4);
}

// A magnitude: a macro with no name in the image, named for what it gives
// (as unit_073710's). Evidence: its other arm is a cast, evaluated rather
// than copied (fld, fstp for a plain field; the aim assist, sub_100AD0).
#define ABS(x) ((x) < 0 ? -x : (RwReal)(x))

// match: ?vf_038@type_10F710@@UAEXM@Z @ 0x000FF990
// sp-match: ?vf_038@type_10F710@@UAEXM@Z @ 0x000C0650
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::vf_038(RwReal arg_0)
{
    RwReal m_18;
    RwReal ebp_14;
    type_4C19C0 *lv_10;
    RwReal slot_C;
    type_712B0_10F710 *bp_8;
    RwReal bp_4;

    bp_8 = (type_712B0_10F710 *)unk_344.unk_08;
    unk_3E4 = 1e37f;
    unk_3E8 = -2.0f;
    sub_16D7F0(0x18);
    unk_550.sub_17190(arg_0);
    sub_16D850(0x18);
    bp_4 = 0.0f;
    ebp_14 = 0.0f;
    lv_10 = unk_1A48[unk_1AE4]->unk_448;
    if (unk_1B04)
    {
        slot_C = lv_10->unk_394_r[unk_1A04];
    }
    else
    {
        slot_C = lv_10->unk_2FC_r[unk_1A04];
    }
    if (unk_1A48[unk_1AE4]->unk_220 - lv_10->unk_BC > 2.0f)
    {
        if (unk_1A48[unk_1AE4]->unk_18 != 0.0f
            && (!unk_1B04 || !((RwReal)fabs((RwDouble)lv_10->unk_34C_r[unk_1A04]) <= 0.01f))
            && (unk_1B04 || !((RwReal)fabs((RwDouble)lv_10->unk_2B4_r[unk_1A04]) <= 0.01f)))
        {
            if (unk_1B04)
            {
                unk_1A48[unk_1AE4]->unk_18 = unk_1A48[unk_1AE4]->unk_18
                    - lv_10->unk_37C_r[unk_1A04] * (unk_1A48[unk_1AE4]->unk_18 / lv_10->unk_34C_r[unk_1A04]);
            }
            else
            {
                unk_1A48[unk_1AE4]->unk_18 = unk_1A48[unk_1AE4]->unk_18
                    - lv_10->unk_2E4_r[unk_1A04] * (unk_1A48[unk_1AE4]->unk_18 / lv_10->unk_2B4_r[unk_1A04]);
            }
            if (unk_1A48[unk_1AE4]->unk_18 < slot_C || unk_1B08)
            {
                unk_1A48[unk_1AE4]->unk_18 = 0.0f;
            }
        }
        if (unk_1A48[unk_1AE4]->unk_1C != 0.0f)
        {
            m_18 = unk_1A48[unk_1AE4]->unk_1C;
            if ((RwReal)fabs((RwDouble)m_18) < slot_C || unk_1B08)
            {
                bp_4 = unk_1A48[unk_1AE4]->unk_1C;
                unk_1A48[unk_1AE4]->unk_1C = 0.0f;
            }
            else if ((!unk_1B04 || !((RwReal)fabs((RwDouble)lv_10->unk_34C_r[unk_1A04]) <= 0.01f))
                     && (unk_1B04 || !((RwReal)fabs((RwDouble)lv_10->unk_2B4_r[unk_1A04]) <= 0.01f)))
            {
                if (unk_1B04)
                {
                    bp_4 = lv_10->unk_37C_r[unk_1A04] * (unk_1A48[unk_1AE4]->unk_1C / lv_10->unk_34C_r[unk_1A04]);
                }
                else
                {
                    bp_4 = lv_10->unk_2E4_r[unk_1A04] * (unk_1A48[unk_1AE4]->unk_1C / lv_10->unk_2B4_r[unk_1A04]);
                }
                unk_1A48[unk_1AE4]->unk_1C = unk_1A48[unk_1AE4]->unk_1C - bp_4;
                sub_170ED0(unk_1A48[unk_1AE4]->unk_1C);
            }
        }
        if (unk_1A48[unk_1AE4]->unk_20 != 0.0f)
        {
            if (unk_1A48[unk_1AE4]->unk_20 < slot_C || unk_1B08)
            {
                ebp_14 = unk_1A48[unk_1AE4]->unk_20;
                unk_1A48[unk_1AE4]->unk_20 = 0.0f;
            }
            else if ((!unk_1B04 || !((RwReal)fabs((RwDouble)lv_10->unk_34C_r[unk_1A04]) <= 0.01f))
                     && (unk_1B04 || !((RwReal)fabs((RwDouble)lv_10->unk_2B4_r[unk_1A04]) <= 0.01f)))
            {
                if (unk_1B04)
                {
                    ebp_14 = lv_10->unk_37C_r[unk_1A04] * (unk_1A48[unk_1AE4]->unk_20 / lv_10->unk_34C_r[unk_1A04]);
                }
                else
                {
                    ebp_14 = lv_10->unk_2E4_r[unk_1A04] * (unk_1A48[unk_1AE4]->unk_20 / lv_10->unk_2B4_r[unk_1A04]);
                }
                unk_1A48[unk_1AE4]->unk_20 = unk_1A48[unk_1AE4]->unk_20 - ebp_14;
                sub_170ED0(unk_1A48[unk_1AE4]->unk_20);
            }
        }
        unk_1A48[unk_1AE4]->unk_40 = 0;
        unk_1A48[unk_1AE4]->unk_3C = 0;
    }
    if (unk_1B04)
    {
        unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].x += ebp_14;
        unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].y -= bp_4;
    }
    else
    {
        unk_1A48[unk_1AE4]->unk_238_a[unk_1A04].x += ebp_14;
        unk_1A48[unk_1AE4]->unk_238_a[unk_1A04].y -= bp_4;
    }
    if (bp_8)
    {
        unk_1A20 = bp_8->unk_1F4;
        unk_1A24 = bp_8->unk_1F8;
        unk_1A28 = bp_8->unk_208;
    }
}

// match: ?sub_100200@type_10F710@@QAEXH@Z @ 0x00100200
// sp-match: ?sub_100200@type_10F710@@QAEXH@Z @ 0x000C5AB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_100200(RwInt32 arg_0)
{
    RwInt32 ebp_14;
    type_4C19C0 *lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (arg_0 == -1)
    {
        return;
    }
    slot_C = 0;
    lv_10 = unk_1A48[unk_1AE4]->unk_448;
    unk_20F8 = arg_0;
    if (unk_1AE4 == 0x20)
    {
        unk_1B30[unk_1AE8] = -1;
        unk_1A48[unk_1AE4]->unk_224 = 2;
        unk_1A48[unk_1AE4]->vf_030(1, 0, 0);
#ifdef CODFH_SP // shape: a block-scoped local, so /O2 puts it in arg_0's dead slot (SP 0xC5AB0's frame)
        RwInt32 v = 0;
        sub_6B5F0("PickedUpWeapon", 0, 0, 0, &v, 1, true, false);
#else
        ebp_14 = 0;
        sub_6B5F0("PickedUpWeapon", 0, 0, 0, &ebp_14, 1, true, false);
#endif
        return;
    }
    unk_1A48[unk_1AE4]->unk_12 = 0;
    unk_1A48[unk_1AE4]->unk_13 = 1;
    unk_1A48[unk_1AE4]->unk_11 = 0;
    unk_1A48[unk_1AE4]->unk_60 = 0;
    if (unk_1A48[unk_1AE4]->unk_46)
    {
        unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
        unk_1A48[unk_1AE4]->unk_21C = 0;
        unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
        unk_1A48[unk_1AE4]->unk_46 = 0;
    }
    if (!sub_77B70(lv_10->unk_34, (void **)(&bp_8), (void **)(&bp_4)) && unk_1A48[unk_1AE4]->get_unk_45C() != 2)
    {
        slot_C = 1;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("WeaponDef %d is missing deselect animation: 0x%x", unk_1B30[unk_1AE8], lv_10->unk_34);
#endif
    }
    lv_10 = unk_1A48[arg_0]->unk_448;
    if (!sub_77B70(lv_10->unk_38, (void **)(&bp_8), (void **)(&bp_4)) && unk_1A48[arg_0]->get_unk_45C() != 2)
    {
        slot_C = 1;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("WeaponDef %d is missing select animation: 0x%x", arg_0, lv_10->unk_38);
#endif
    }
    if (!slot_C)
    {
        if (!unk_1A48[unk_1AE4]->unk_224)
        {
            unk_1A48[unk_1AE4]->unk_224 = 1;
            unk_1A48[unk_1AE4]->vf_030(1, 0, 0);
        }
    }
    else
    {
        sub_100560();
    }
}

// match: ?sub_100560@type_10F710@@QAEXXZ @ 0x00100560
// sp-match: ?sub_100560@type_10F710@@QAEXXZ @ 0x000C0A90
void type_10F710::sub_100560()
{
#ifndef CODFH_SP // SP 0xC0A90 has no unk_19F8 check
    if (unk_19F8 > 0)
    {
        return;
    }
#endif
    if (unk_20F8 == -1)
    {
        return;
    }
    if (unk_20F8 == unk_1B30[!unk_1AE8])
    {
        unk_1AE8 = !unk_1AE8;
    }
    unk_1A48[unk_1AE4]->sub_117370();
    unk_1AE4 = unk_20F8;
    unk_1A48[unk_1AE4]->sub_1170B0(1, 1);
    if (vf_1E4())
    {
        unk_1AEC = unk_1AE4;
    }
}

// match: ?vf_220@type_10F710@@UAEXPAUtype_3D3548@@H@Z @ 0x00100640
// sp-match: ?vf_220@type_10F710@@UAEXPAUtype_3D3548@@H@Z @ 0x000C0B10
void type_10F710::vf_220(type_3D3548 *arg_0, RwInt32 arg_4)
{
    if (arg_4 && ((type_10F710_220 *)arg_4)->vf_058() != 5)
    {
        unk_2174.sub_D48D0(arg_0);
    }
}

// match: ?sub_100680@type_10F710@@QAEXXZ @ 0x00100680
// sp-match: ?sub_100680@type_10F710@@QAEXXZ @ 0x000C0B40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_100680()
{
    type_3DC9B0 *r7C;
    RwV3d frm_68;
    RwV3d r5C;
    RwMatrix ebp_50;
    RwInt32 slot_C;
    type_3DBC78 *bp_8;

    bp_8 = (type_3DBC78 *)vf_200();
    slot_C = 0;
    if (bp_8 && unk_4D0 == 2)
    {
        slot_C = 1;
    }
    if (slot_C)
    {
        bp_8->vf_2F4(0, &ebp_50);
        r5C.x = ebp_50.at.x * 1000.0f + ebp_50.pos.x;
        r5C.y = ebp_50.at.y * 1000.0f + ebp_50.pos.y;
        r5C.z = ebp_50.at.z * 1000.0f + ebp_50.pos.z;
        dword_4B9190->sub_DEC40(&r5C, &frm_68);
#ifdef CODFH_SP // SP 0xC0B40 sets HUD element 0x31 where MP sets 0x5A
        dword_4B9190->sub_E7050(0x31, frm_68.x - dword_4B9190->unk_54 / (RwReal)(RwUInt32)Width,
                                frm_68.y - dword_4B9190->unk_58 / (RwReal)(RwUInt32)Width);
#else
        dword_4B9190->sub_E7050(0x5A, frm_68.x - dword_4B9190->unk_54 / (RwReal)(RwUInt32)Width,
                                frm_68.y - dword_4B9190->unk_58 / (RwReal)(RwUInt32)Width);
#endif
    }
    else if (unk_19D0 == 7)
    {
        r7C = (type_3DC9B0 *)unk_210C.sub_D4910();
        if (r7C && r7C->unk_3B0 == 2)
        {
            if (r7C->unk_488)
            {
#ifdef CODFH_SP
                dword_4B9190->sub_E7050(0x31, dword_4B9190->unk_54 + -5.0f, dword_4B9190->unk_58 + 40.0f);
#else
                dword_4B9190->sub_E7050(0x5A, dword_4B9190->unk_54 + -5.0f, dword_4B9190->unk_58 + 40.0f);
#endif
            }
            else
            {
#ifdef CODFH_SP
                dword_4B9190->sub_E7050(0x31, dword_4B9190->unk_54 + 0.0f, dword_4B9190->unk_58 + -20.0f);
#else
                dword_4B9190->sub_E7050(0x5A, dword_4B9190->unk_54 + 0.0f, dword_4B9190->unk_58 + -20.0f);
#endif
            }
        }
        else
        {
#ifdef CODFH_SP
            dword_4B9190->sub_E7050(0x31, dword_4B9190->unk_54, dword_4B9190->unk_58);
#else
            dword_4B9190->sub_E7050(0x5A, dword_4B9190->unk_54, dword_4B9190->unk_58);
#endif
        }
    }
    else
    {
#ifdef CODFH_SP
        dword_4B9190->sub_E7050(0x31, dword_4B9190->unk_54, dword_4B9190->unk_58);
#else
        dword_4B9190->sub_E7050(0x5A, dword_4B9190->unk_54, dword_4B9190->unk_58);
#endif
    }
}

// match: ?sub_100880@@YAXPAUtype_10F710@@PAUtype_4C194C@@@Z @ 0x00100880
// sp-match: ?sub_100880@@YAXPAUtype_10F710@@PAUtype_4C194C@@@Z @ 0x000C0CA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_100880(type_10F710 *arg_0, type_4C194C *arg_4)
{
    RwReal fp_2C;
    RwReal q28;
    RwReal frm_24;
    RwReal t20;
#ifndef CODFH_SP
    RwV3d l1C;
#endif
    type_3D3548 *lv_10;
    type_3D3548 *slot_C;
    RwInt32 bp_8;
    type_3D3548 *bp_4;

    slot_C = arg_0->vf_200();
    bp_8 = 0;
    if (slot_C && arg_0->unk_4D0 == 2)
    {
        bp_8 = 1;
    }
    if (!bp_8)
    {
        arg_0->sub_100680();
    }
    if (arg_0->unk_2174.sub_D4910())
    {
        lv_10 = arg_0->unk_2174.sub_D4910();
#ifdef CODFH_SP // SP 0xC0CA0 has no dword_4FB9F8 test
        if (arg_0->vf_24C(lv_10))
#else
        if (arg_0->vf_24C(lv_10) || get_4FB9F8())
#endif
        {
            dword_4B9190->sub_DEEF0(1);
        }
    }
    bp_4 = arg_4->unk_08.sub_D4910();
    if (!bp_4)
    {
        return;
    }
    if (arg_0->vf_248(bp_4))
    {
#ifdef CODFH_SP // shape: block-scoped (SP 0xC0CA0)
        RwV3d l1C;

#endif
        dword_4B9190->sub_DEEB0(1);
        RwV3dSub(&l1C, (RwV3d *)bp_4->vf_0C4(), (RwV3d *)arg_0->vf_0C4());
        q28 = RwV3dLength(&l1C);
        fp_2C = 3000.0f;
        if (q28 > fp_2C)
        {
            q28 = fp_2C;
        }
        t20 = 1.0f - q28 / fp_2C;
        frm_24 = 0.7f;
        t20 = t20 * frm_24 + 0.3f;
#ifdef CODFH_SP // SP 0xC0CA0 sets HUD element 0x36 where MP sets 0x5F
        dword_4B9190->sub_E3B90(0x36, t20);
#else
        dword_4B9190->sub_E3B90(0x5F, t20);
#endif
    }
}

// match: ?sub_100A50@@YAHPAUtype_10F710@@@Z @ 0x00100A50
// sp-match: ?sub_100A50@@YAHPAUtype_10F710@@@Z @ 0x000C0DF0
RwInt32 sub_100A50(type_10F710 *arg_0)
{
    type_3D3548 *var_4;

    if (!arg_0)
    {
        return 0;
    }
    var_4 = arg_0->unk_1A34.sub_D4910();
    if (var_4 && (var_4->vf_008() || var_4->vf_010() || var_4->vf_024()) && arg_0->vf_248(var_4))
    {
        return 1;
    }
    return 0;
}

// match: ?sub_100AD0@@YAXPAUtype_10F710@@PAUtype_4C194C@@@Z @ 0x00100AD0
// sp-match: ?sub_100AD0@@YAXPAUtype_10F710@@PAUtype_4C194C@@@Z @ 0x000C0E50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_100AD0(type_10F710 *arg_0, type_4C194C *arg_4)
{
    RwFrame *var_64;
    type_712B0_10F710 *stk_60;
    RwReal y5C;
    RwMatrix *slot_58;
#ifndef CODFH_SP
    RwV3d l54;
#endif
    RwReal w48;
    RwReal loc44;
#ifndef CODFH_SP
    RwV3d fp_40;
#endif
    RwReal r34;
    RwReal lv_30;
    RwReal fp_2C;
    RwReal q28;
    RwReal frm_24;
    RwReal t20;
    type_3D3548 *l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;
    RwReal slot_C;
    type_712B0_10F710 *bp_8;
    RwReal bp_4;

    r34 = arg_4->unk_04;
    bp_4 = arg_4->unk_0C;
    l1C = arg_4->unk_08.sub_D4910();
    fp_2C = (ebp_14 = unk_4B9308.sub_EE8F0(arg_0->unk_3D8, 1)) < 0.0f ? -ebp_14 : ebp_14;
    lv_30 = 1.0f;
    q28 = 1.0f;
    m_18 = 1.0f;
    lv_10 = 1.0f;
    t20 = 1.0f;
    frm_24 = 0.0f;
    slot_C = 1.0f;
    bp_8 = (type_712B0_10F710 *)arg_0->get_unk_34C();
    arg_0->unk_1A38 = 0.0f;
    if (bp_8->unk_304 && l1C && arg_0->vf_24C(l1C) && !l1C->unk_28_9 && l1C->vf_174() > 0
        && l1C->vf_008())
    {
        if (arg_0->unk_1A34.sub_D4910() != l1C || (RwReal)fabs((RwDouble)arg_0->get_unk_3EC()) > bp_8->unk_35C)
        {
#ifdef CODFH_SP // shape: l54 block-scoped and the scale computed once (SP 0xC0E50)
            RwV3d l54;

            RwV3dSub(&l54, (RwV3d *)l1C->vf_0C4(), (RwV3d *)arg_0->vf_0C4());
            y5C = RwV3dLength(&l54) * bp_8->unk_34C;
            slot_58 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
            RwV3dScale(&l54, &slot_58->at, y5C);
#else
            RwV3dSub(&l54, (RwV3d *)l1C->vf_0C4(), (RwV3d *)arg_0->vf_0C4());
            y5C = RwV3dLength(&l54);
            slot_58 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
            RwV3dScale(&l54, &slot_58->at, y5C * bp_8->unk_34C);
#endif
            RwV3dAdd(&l54, (RwV3d *)arg_0->vf_0C4(), &l54);
            arg_0->unk_474.x = l54.x;
            arg_0->unk_474.y = l54.y;
            arg_0->unk_474.z = l54.z;
        }
#ifdef CODFH_SP // shape: block-scoped (SP 0xC0E50)
        RwV3d fp_40;

#endif
        RwV3dSub(&fp_40, (RwV3d *)l1C->vf_0C4(), (RwV3d *)arg_0->vf_0C4());
        frm_24 = RwV3dLength(&fp_40);
        w48 = bp_8->unk_364[arg_0->unk_1A04] - bp_8->unk_370[arg_0->unk_1A04];
        loc44 = (frm_24 * w48) / bp_8->unk_334;
        loc44 = loc44 + bp_8->unk_364[arg_0->unk_1A04];
        arg_0->unk_480 = loc44;
        arg_0->unk_454 = 1;
    }
    arg_0->unk_1A34.sub_D48D0(l1C);
    if (fp_2C >= bp_8->unk_33C)
    {
        if (ABS(arg_0->unk_464) < bp_8->unk_33C && arg_0->unk_454)
        {
            arg_0->unk_460 = bp_8->unk_340;
        }
        else if (!arg_0->unk_460 && bp_8->unk_338)
        {
            arg_0->unk_46C = 1;
        }
    }
    else
    {
        if (arg_0->unk_454)
        {
            arg_0->unk_470 = 0.0f;
        }
        else
        {
            stk_60 = (type_712B0_10F710 *)arg_0->get_unk_34C();
            arg_0->unk_470 = stk_60->unk_1CC;
        }
        arg_0->unk_46C = 0;
    }
    if (arg_0->unk_464 != 0.0f && ebp_14 == 0.0f)
    {
        if (fp_2C < flt_429748)
        {
            arg_0->unk_45C = dword_42975C;
            arg_0->unk_44C = dword_429750;
        }
        else if (fp_2C < flt_42974C)
        {
            arg_0->unk_45C = dword_429758;
            arg_0->unk_44C = dword_429750;
        }
        else
        {
            arg_0->unk_45C = dword_429760;
            arg_0->unk_44C = dword_429754;
        }
        arg_0->unk_468 = arg_0->unk_464;
    }
    arg_0->unk_464 = ebp_14;
    arg_0->unk_460--;
    if (arg_0->unk_460 < 0)
    {
        arg_0->unk_460 = 0;
    }
    if (arg_0->unk_454)
    {
        if (arg_0->unk_1B04)
        {
            lv_30 = arg_0->unk_1A24;
            t20 = bp_8->unk_F0 - arg_0->unk_534;
            lv_30 = lv_30 - t20 * bp_8->unk_31C;
        }
        else if (arg_0->unk_19D0 == 7)
        {
            lv_30 = arg_0->unk_1A28;
        }
        else
        {
            lv_30 = arg_0->unk_1A20;
        }
        if (l1C)
        {
            if (frm_24 > bp_8->unk_320)
            {
                frm_24 = bp_8->unk_320;
            }
            frm_24 = frm_24 / bp_8->unk_320;
            slot_C = (1.0f - frm_24) * bp_8->unk_324;
        }
        q28 = 1.0f - lv_30;
        m_18 = (1.0f - fp_2C) * bp_8->unk_308;
        lv_10 = lv_30 + slot_C + (1.0f - r34) * m_18 * q28;
        if (lv_10 > 1.0f)
        {
            lv_10 = 1.0f;
        }
        if (arg_0->unk_1A30 == 0.0f)
        {
            arg_0->unk_450++;
        }
        else if (!arg_0->unk_454)
        {
            arg_0->unk_450 = 0;
        }
        arg_0->unk_45C--;
        if (arg_0->unk_45C < 0)
        {
            arg_0->unk_45C = 0;
        }
        if (!((bp_4 > 0.0f && arg_0->unk_468 < 0.0f) || (bp_4 < 0.0f && arg_0->unk_468 > 0.0f))
            && bp_8->unk_30C && r34 >= 0.0f && bp_4 != 0.0f && !arg_0->unk_46C && arg_0->unk_45C)
        {
            if ((bp_4 < 0.0f ? -bp_4 : bp_4) > ABS(arg_0->unk_468) * arg_4->unk_0C * arg_0->unk_44C)
            {
#ifdef CODFH_SP // shape: unk_468 read as a fresh load (SP 0xC1406 loads it first, as in the test above)
                bp_4 = *(volatile RwReal *)&arg_0->unk_468 * arg_4->unk_0C * arg_0->unk_44C;
#else
                bp_4 = arg_4->unk_0C * arg_0->unk_468 * arg_0->unk_44C;
#endif
            }
            var_64 = arg_0->unk_338.get_unk_08();
            RwFrameRotate(var_64, &stru_3D973C, bp_4, rwCOMBINEPRECONCAT);
            RwFrameUpdateObjects(var_64);
            arg_0->unk_1A30 = 0.0f;
            arg_0->unk_3F4 = 0.0f;
            arg_0->unk_3EC = 0.0f;
        }
        arg_0->unk_1A30 = lv_10;
        if (!bp_8->unk_304)
        {
            arg_0->unk_1A30 = 1.0f;
        }
    }
}

// match: ?vf_248@type_10F710@@UAEHPAUtype_3D3548@@@Z @ 0x00101420
// sp-match: ?vf_248@type_10F710@@UAEHPAUtype_3D3548@@@Z @ 0x000C1470
RwInt32 type_10F710::vf_248(type_3D3548 *arg_0)
{
    type_3D3548 *var_4;

    if (!arg_0)
    {
        return 0;
    }
    var_4 = vf_200();
    if (arg_0 == var_4)
    {
        return 0;
    }
    return arg_0->unk_2C_0;
}

// match: ?vf_24C@type_10F710@@UAEHPAUtype_3D3548@@@Z @ 0x00101460
// sp-match: ?vf_24C@type_10F710@@UAEHPAUtype_3D3548@@@Z @ 0x000C14A0
RwInt32 type_10F710::vf_24C(type_3D3548 *arg_0)
{
    if (!arg_0)
    {
        return 0;
    }
    return arg_0->unk_2C_1;
}

// match: ?vf_238@type_10F710@@UAEXH@Z @ 0x00101490
// sp-match: ?vf_238@type_10F710@@UAEXH@Z @ 0x000C14C0
void type_10F710::vf_238(RwInt32 arg_0)
{
    unk_1A08 = unk_1A04;
    unk_1A04 = arg_0;
    unk_1A48[unk_1AE4]->sub_119830(unk_1A04, 0);
}

// match: ?sub_1014E0@@YAHXZ @ 0x001014E0
// sp-match: ?sub_1014E0@@YAHXZ @ 0x000C14F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_1014E0()
{
    RwInt32 slot_C;
    type_3DD948 *bp_8;
    type_10F710 *bp_4;

    bp_4 = (type_10F710 *)sub_1745A0(dword_429EB0);
    if (bp_4)
    {
        bp_8 = (type_3DD948 *)bp_4->unk_2110.sub_D4910();
        if (bp_8)
        {
            slot_C = bp_8->unk_414;
            if (slot_C)
            {
                return 0;
            }
        }
    }
    if (!bp_4->unk_1B3C)
    {
        return 0;
    }
    return 1;
}

// The step. The hurt flash's times run down. With its trigger: unless it
// is still (trigger unk_140), the listener is put behind the camera's view
// (3 units back along it, or along the head bone in camera mode) facing along
// it, its sounds follow it, at no health it dies (posture 10, the camera let
// go), the aim pass runs along the camera's (or its mounted weapon's) view
// over the section worlds, and the posture's step runs; while still, the
// pad moves and turns it. Then the weapons' times, a nearby vehicle's weapon
// (29 or 35) taken or put back, the inventory's count, its performance and
// AI, and the pad's weapon handling (fire, reload, the bipod, the second
// weapon, the stance, the soldier under the crosshair's health pack, the
// inventory), the sway (vf_258), aiming in or out and the inventory's next
// kind.
// match: ?vf_03C@type_10F710@@UAEXM@Z @ 0x00101550
// sp-match: ?vf_03C@type_10F710@@UAEXM@Z @ 0x000CE6F0
void type_10F710::vf_03C(RwReal arg_0)
{
    RwInt32 v_8;
    type_712B0_10F710 *v_C;

    v_8 = unk_1A48[unk_1AE4]->unk_458;
#ifndef CODFH_SP // MP only: single player's player has no unk_1B18 (SP 0xCE6F0, 0xC4AF0)
    unk_1B18 = 0;
#endif
    if (unk_19EC > 0.0f)
        unk_19EC -= arg_0;
    if (unk_19F0 > 0.0f)
        unk_19F0 -= arg_0;
    v_C = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_C && v_C->vf_008() != 1)
    {
        v_C = 0;
    }
    if (!v_C)
        return;
    if (!unk_1A48[unk_1AE4]->get_unk_41C())
        unk_1A48[unk_1AE4]->sub_1170B0(1, 0);
    if (!v_C->unk_140)
    {
        type_3DD948 *v_14;
        RpHAnimHierarchy *v_18;
        RwMatrix *v_1C;
        RwMatrix *v_20;
        RwV3d *v_2C;
        RwV3d v_3C;

        v_14 = (type_3DD948 *)((type_10F710 *)sub_1745A0(dword_429EB0))->unk_2110.sub_D4910();
        v_18 = v_14->unk_284->unk_18;
        v_1C = RpHAnimHierarchyGetMatrixArray(v_18);
        v_20 = &v_1C[RpHAnimIDGetIndex(v_18, 0x97)];
        if (!v_14->get_unk_414())
            v_2C = &RwFrameGetLTM(get_unk_340())->at;
        else
            v_2C = &v_20->at;
        if (!v_14->get_unk_414())
            v_3C = *sub_CD550();
        else
            v_3C = v_20->pos;
        v_3C.x -= v_2C->x * 3.0f;
        v_3C.y -= v_2C->y * 3.0f;
        v_3C.z -= v_2C->z * 3.0f;
        do
        {
            dword_44E8AC->unk_28 = v_3C;
            dword_44E8AC->unk_70 |= 1;
        } while (0);
        do
        {
            dword_44E8AC->unk_4C = *v_2C;
            RwV3dCrossProductMacro(&dword_44E8AC->unk_58, &dword_44E8AC->unk_40, &dword_44E8AC->unk_4C);
            dword_44E8AC->unk_70 |= 4;
        } while (0);
        if (!v_14->get_unk_414())
            unk_1C0.sub_89540(sub_CD550());
        else
        {
            unk_1C0.sub_89540(&v_20->pos);
            if (unk_1A48[unk_1AE4]->unk_21C && ((((type_44C4E8 *)unk_1A48[unk_1AE4]->unk_21C)->unk_34 & 2) != 0) != 0)
            {
                unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                unk_1A48[unk_1AE4]->unk_21C = 0;
            }
        }
        if (!unk_19F8 && unk_19DC <= 0.0f && !((dword_4B86F8 >> 6) & 1))
        {
            type_3DD948 *v_44;

            if (unk_19D0 == 5)
                sub_10FBF0();
            unk_19D0 = 0xA;
            unk_1A48[unk_1AE4]->unk_224 = 0;
            v_44 = (type_3DD948 *)unk_2110.sub_D4910();
            if (v_44)
                v_44->unk_3B0 = 0;
#ifndef CODFH_SP // SP 0xCE6F0 sets no dword_4FDA9C
            dword_4FDA9C = 1;
#endif
        }
        if (flt_4B8F2C != 0.0f)
        {
            RpIntersection v_60;
            type_3D3548 *v_64;
            RwMatrix v_B0;
            RwMatrix *v_B4;
            RwV3d v_C0;
            RwV3d v_CC;
            RwV3d v_D8;

#ifndef CODFH_SP
            sub_19A750();
#endif
            dword_4C194C.unk_00 = flt_4B8F2C;
            v_60.type = rpINTERSECTLINE;
            v_64 = vf_200();
            if (v_64 && unk_4D0 == 2)
            {
                ((type_3DBC78 *)v_64)->vf_2F4(0, &v_B0);
                v_B4 = &v_B0;
            }
            else
                v_B4 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
            v_60.t.line.start = v_B4->pos;
            v_60.t.line.end.x = v_B4->at.x * v_C->unk_334 + v_60.t.line.start.x;
            v_60.t.line.end.y = v_B4->at.y * v_C->unk_334 + v_60.t.line.start.y;
            v_60.t.line.end.z = v_B4->at.z * v_C->unk_334 + v_60.t.line.start.z;
            unk_1A30 = 1.0f;
            unk_454 = 0;
            dword_4C194C.unk_04 = -1.0f;
            dword_4C194C.unk_08.sub_D48D0(0);
            dword_4C194C.unk_0C = 0;
            if (sub_FCAE0(&v_60.t.line.start, &v_60.t.line.end, &v_C0, 0, 0x10000, 1, 1))
            {
                RwV3dSubMacro(&v_CC, &v_C0, &v_60.t.line.start);
                RwV3dNormalize(&v_D8, &v_CC);
                v_60.t.line.end.x = v_D8.x * 350.0f + v_C0.x;
                v_60.t.line.end.y = v_D8.y * 350.0f + v_C0.y;
                v_60.t.line.end.z = v_D8.z * 350.0f + v_C0.z;
            }
            if (v_60.t.line.start.x != v_60.t.line.end.x || v_60.t.line.start.y != v_60.t.line.end.y ||
                v_60.t.line.start.z != v_60.t.line.end.z)
            {
                for (RwInt32 v_DC = 0; v_DC < 4; v_DC++)
                {
                    type_4E5D30 *v_E0 = &dword_4E5D30[v_DC];

                    if (v_E0->get_unk_00() != 0 && v_E0->get_unk_28() != 0)
                        RpWorldForAllAtomicIntersections(v_E0->get_unk_28(), &v_60, sub_FCD90, &dword_4C194C);
                }
            }
            sub_100880(this, &dword_4C194C);
            sub_100AD0(this, &dword_4C194C);
        }
        switch (unk_19D0)
        {
        case 0:
#ifdef CODFH_SP // SP 0xCE6F0 has no dword_4B86F8 bit-4 test
            sub_10A9D0(arg_0);
#else
            if (!((dword_4B86F8 >> 4) & 1))
                sub_10A9D0(arg_0);
#endif
            break;
        case 1:
            sub_10AD70(arg_0);
            break;
        case 2:
            sub_10AEB0(arg_0);
            break;
        case 3:
            sub_10AFD0(arg_0);
            break;
        case 5:
            sub_10B120(arg_0);
            break;
        case 6:
            sub_10B2E0(arg_0);
            break;
        case 7:
            sub_10B410(arg_0);
            break;
        case 9:
            sub_10B6F0(arg_0);
            break;
        case 10:
            sub_10B790(arg_0);
            break;
        case 11:
            sub_10B930(arg_0);
            break;
        case 12:
            sub_10B560(arg_0);
            break;
        case 13:
            sub_114AA0(arg_0);
            break;
        case 14:
            sub_10BB30(arg_0);
            break;
#ifndef CODFH_SP // single player has no defuse and plant states (SP 0xCE6F0's switch ends at 14)
        case 16:
            vf_250(arg_0);
            break;
        case 17:
            vf_254(arg_0);
            break;
#endif
        }
    }
    else
    {
        RwReal v_F4;

        unk_28 &= ~0x2C;
        unk_28 |= 0x10;
        unk_10C.x = -0.5f;
        unk_10C.y = -0.5f;
        unk_10C.z = -0.5f;
        unk_134.x = -0.5f;
        unk_134.y = -0.5f;
        unk_134.z = -0.5f;
        unk_28 &= ~2;
        unk_DC *= 0.5f;
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 0);
        if (v_F4 != 0.0f)
        {
            if (v_F4 > 0.0f)
                unk_C0.z = v_F4 * v_C->unk_164[unk_1A04];
            else
                unk_C0.z = v_F4 * v_C->unk_170[unk_1A04];
        }
        dword_429498[3].unk_04 = 1;
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 3);
        if (v_F4 != 0.0f)
            unk_C0.y = v_F4 * v_C->unk_164[unk_1A04];
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 0xC);
        if (v_F4 != 0.0f)
            unk_C0.y = v_C->unk_164[unk_1A04] * -v_F4;
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 2);
        if (v_F4 != 0.0f)
            unk_C0.x = (RwDouble)v_C->unk_1E4[unk_1A04] * v_F4;
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 5);
        if (v_F4 != 0.0f)
        {
            RwReal v_F8;
            RwReal v_FC;
            RwReal v_100;

            v_F8 = v_F4 * v_C->unk_154;
            unk_530 += v_F8;
            v_FC = 90.0f;
            v_100 = -90.0f;
            unk_530 = sub_22C20(unk_530, v_100, v_FC);
        }
        v_F4 = unk_4B9308.sub_EE8F0(unk_3D8, 1);
        if (v_F4 != 0.0f)
        {
            unk_E8 = (RwDouble)v_C->unk_1B4 * v_F4 * flt_3CE7F4;
            sub_19B650(unk_E4);
        }
    }
    unk_1A48[unk_1AE4]->unk_220 += arg_0;
    {
        type_10F710_1A48 *v_104 = unk_1A48[unk_1AE4]->unk_460;

        if (v_104)
            v_104->unk_220 += arg_0;
    }
    if (unk_2188 && unk_2148 == 0.0f && unk_19F8 <= 0 && unk_19DC > 0.0f && !((dword_4B86F8 >> 6) & 1))
    {
        RwInt32 v_108 = 8;
        RwInt32 v_10C = unk_19D0;

        if (v_10C == 5)
        {
            sub_10F7E0(1, 0);
            sub_10F7E0(2, 1);
            v_108 = 9;
        }
        else
        {
            RwInt32 v_110 = 0x1D;
            RwInt32 v_114 = 0;
            type_3D3548 *v_118 = dword_4B85F8[1].unk_08;
            type_4C19C0 *v_128;
            RwInt32 v_12C;

            while (v_118 && !v_114)
            {
                VehicleTrigger *v_120 = (VehicleTrigger *)v_118->get_unk_34C();

                if (v_120->unk_EC == 3 || v_120->unk_EC == 2)
                {
                    v_114 = 1;
                    switch (v_120->unk_114)
                    {
                    case 1:
                        v_110 = 0x23;
                        break;
                    case 0:
                        v_110 = 0x1D;
                        break;
                    }
                }
                if (!v_114)
                    v_118 = v_118->unk_10;
            }
            v_128 = sub_119B70(v_110);
            v_12C = v_128->unk_24;
            if (!sub_10E8C0(v_110) && !sub_16F8A0(v_12C))
                sub_10DA70(v_110);
            if (sub_10E8C0(v_110))
            {
                if (!unk_1A48[v_110]->get_unk_41E())
                {
                    unk_1A48[v_110]->vf_008(this, unk_1A3C.get_unk_08(), v_110);
                    set_bank_state(unk_2134, 1, 1);
                }
                sub_10F7E0(1, 1);
                sub_10F7E0(2, 0);
                if (sub_10F710() == 1)
                    set_bank_state(sub_16F860(v_12C), v_110, 1);
            }
        }
        if (dword_4B9190)
            dword_4B9190->sub_E0410(v_108);
        if (sub_10F710() == 1 || sub_10F710() == 2)
        {
            ((VehicleEnterExitTrigger *)unk_2188)->sub_BF310(this);
            sub_10F8D0(0);
            unk_2240 = 0;
        }
    }
    else
    {
        sub_10F7E0(1, 0);
        sub_10F7E0(2, 0);
        if (get_bank_state(unk_2134) && dword_4E5518[unk_2134] >> 16 == 1)
            clear_bank_state(unk_2134, 1);
    }
    sub_1048E0();
    unk_21B4.sub_115520(arg_0);
    if (unk_284 && unk_88_9)
    {
        type_6D380 *v_148 = vf_090();

        if (v_148)
            ((type_3D2CD0 *)v_148)->sub_6D5A0(arg_0);
        vf_21C(arg_0);
    }
    sub_16D7F0(0x18);
    unk_550.sub_172F0(arg_0);
    sub_16D850(0x18);
#ifdef CODFH_SP // SP 0xCE6F0 tests no dword_4B86F8 bit 4 here or below
    if (0.0f == unk_4B9308.sub_EE8F0(0, 0xF))
#else
    if (!((dword_4B86F8 >> 4) & 1) && 0.0f == unk_4B9308.sub_EE8F0(0, 0xF))
#endif
        unk_2240 = 1;
    unk_1B20 = 0;
    if (0.0f == unk_4B9308.sub_EE8F0(unk_3D8, 3) || (RwUInt32)unk_1A48[unk_1AE4]->unk_414 <= 0)
    {
        unk_1B24 = 0;
        unk_20DC = dword_429744;
    }
    type_4C19C0 *v_14C = unk_1A48[unk_1AE4]->unk_448;

#ifdef CODFH_SP // the firing checks run only while alive and not in a vehicle (SP 0xCE6F0)
    if (unk_19F8 <= 0 && unk_19DC > 0.0f && !((dword_4B86F8 >> 6) & 1) && unk_2148 == 0.0f)
#else
    if ((dword_4B86F8 >> 4) & 1)
    {
        RwInt32 v_150 = unk_4B9308.sub_EE870(unk_3D8, 3);

        if ((v_150 || (RwUInt32)unk_1A48[unk_1AE4]->unk_414 <= 0) && unk_1A48[unk_1AE4]->unk_46)
        {
            unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
            unk_1A48[unk_1AE4]->unk_21C = 0;
            unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
            unk_1A48[unk_1AE4]->unk_46 = 0;
        }
    }
    else
#endif
    {
        RwInt32 v_158;

        v_158 = sub_100A50(this);
#ifndef CODFH_SP
        if (get_4FB9F8())
            v_158 = 0;
#endif
        if (unk_19D0 == 0xA || unk_19D0 == 9)
            unk_1A48[unk_1AE4]->vf_02C();
        else if (unk_19D0 == 7)
        {
            RwReal v_160;
            type_3DC9B0 *v_164;

            v_160 = unk_4B9308.sub_EE8F0(unk_3D8, 3);
            v_164 = (type_3DC9B0 *)unk_210C.sub_D4910();
            if (v_160 != 0.0f)
            {
                RwInt32 v_16C;

                if (unk_20F0 != 0.0f && !v_158)
                    unk_20F4 = 1;
                if (v_158 && !unk_20F4 && dword_4B9190->get_unk_1A020() == 1)
                    v_16C = 0;
                else
                    v_16C = 1;
                if (v_164 && v_16C)
                {
                    RwInt32 v_170 = v_164->sub_169380();

                    if (v_170)
                        unk_4B9308.sub_EED30(unk_3D8, 1, 0xDC, 4);
                }
            }
            else if (v_164)
            {
                if (v_164->unk_470)
                {
                    v_164->unk_470 = 0;
                    v_164->unk_474 = 1;
                }
                else if (v_164->unk_474)
                    v_164->unk_474 = 0;
            }
        }
        else if (v_8 == 0x20 && unk_1B3C)
        {
            if (0.0f != unk_4B9308.sub_EE8F0(unk_3D8, 3))
                unk_1A48[unk_1AE4]->vf_01C();
        }
        else if ((unk_1B3C || vf_160() == 7) && unk_2148 == 0.0f)
        {
            RwReal v_178;
            RwInt32 v_17C;

            switch (unk_1A48[unk_1AE4]->unk_48)
            {
            case 1:
            case 2:
                unk_4B9308.sub_EECD0(3, 0);
                break;
            default:
                unk_4B9308.sub_EECD0(3, 1);
            }
            unk_1A48[unk_1AE4]->vf_02C();
            v_178 = unk_4B9308.sub_EE8F0(unk_3D8, 3);
            v_17C = unk_4B9308.sub_EE870(unk_3D8, 3);
            if (v_17C || (RwUInt32)unk_1A48[unk_1AE4]->unk_414 <= 0)
            {
                if (unk_1A48[unk_1AE4]->unk_46)
                {
                    unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                    unk_1A48[unk_1AE4]->unk_21C = 0;
                    unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
                    unk_1A48[unk_1AE4]->unk_46 = 0;
                }
                v_17C = 1;
            }
            if (!unk_1B44 && unk_1A48[unk_1AE4]->vf_010())
                unk_1B44 = v_17C;
            if ((v_8 == 0 || v_8 == 1) && 0.0f == unk_4B9308.sub_EE8F0(unk_3D8, 3) && !unk_1B0C && !unk_1B04)
                unk_1B44 = 1;
            if (unk_1A48[unk_1AE4]->sub_117460() && unk_1A48[unk_1AE4]->vf_010() && !unk_1A48[unk_1AE4]->unk_12)
            {
                if (unk_1B44 || unk_1A48[unk_1AE4]->unk_4C)
                    unk_1A48[unk_1AE4]->vf_020();
                unk_1B44 = 0;
                unk_1A48[unk_1AE4]->unk_4C = 0;
            }
            else
            {
                type_10F710_1A48 *v_184;
                RwInt32 v_188;

                v_184 = unk_1A48[unk_1AE4];
                v_188 = 1;
                switch (v_8)
                {
                case 0:
                case 1:
                    if (unk_1B04 && !unk_1B0C && !v_184->unk_12 && v_184->sub_117460() && v_184->unk_414 &&
                        unk_1B14)
                        v_178 = 1.0f;
                    else
                    {
                        if (!unk_1B14 && unk_1B04)
                            v_188 = 1;
                        else
                            v_188 = 0;
                    }
                    break;
                }
                if (v_178 != 0.0f)
                {
                    type_4C19C0 *v_190;
                    RwInt32 v_19C;
                    RwInt32 v_1A0;

                    v_190 = unk_1A48[unk_1AE4]->get_unk_448();
                    if ((v_8 == 1 || v_8 == 0) && !unk_1B04 && !unk_1B14 && v_184->sub_117460() && v_184->unk_414)
                        unk_1B14 = 1;
                    if (unk_20F0 != 0.0f && !v_158)
                        unk_20F4 = 1;
                    if (v_158 && !unk_20F4 && dword_4B9190->get_unk_1A020() == 1)
                        v_188 = 0;
                    else if (unk_1A48[unk_1AE4]->get_unk_45C() != 3 || v_188)
                        v_188 = 1;
                    if (v_184->unk_60 && !unk_20EC && (RwUInt32)v_184->unk_414 > 0)
                    {
                        unk_20EC = 1;
                        v_184->unk_60 = 3;
                        if (sub_77B70(v_190->unk_8C, (void **)(&v_1A0), (void **)(&v_19C)))
                        {
                            unk_284->sub_794C0(0.06666667f);
                            unk_284->sub_796A0((RtAnimAnimation *)v_1A0, v_190->unk_8C, 0, (struct type_783F0 *)v_19C,
                                               0.0f, 1.0f, 1.0f);
                        }
                    }
                    if (v_184->sub_117460() && v_188 && !v_184->unk_12)
                    {
                        unk_1B20 = v_184->vf_018();
                        if (!unk_1B1C)
                            sub_114F50();
                        unk_1B1C = 1;
                        unk_20EC = 0;
                        if (unk_1B20)
                        {
#ifndef CODFH_SP // MP only: single player's player has no unk_1B18 (SP 0xCE6F0, 0xC4AF0)
                            unk_1B18 = 1;
#endif
                            unk_1B24 = dword_429AA0;
                            if (arg_0 < 2.0f)
                                unk_1B24++;
                        }
#ifndef CODFH_SP // SP 0xCE6F0 keeps unk_1B1C when the clip runs out
                        else if ((RwUInt32)v_184->unk_418 <= 0 && (RwUInt32)v_184->unk_414 <= 0)
                        {
                            unk_1B1C = 0;
#ifndef CODFH_SP // MP only: single player's player has no unk_1B18 (SP 0xCE6F0, 0xC4AF0)
                            unk_1B18 = 0;
#endif
                        }
#endif
                    }
                }
                {
                    type_3D3548 *v_1A4 = vf_200();

                    if (v_1A4)
#ifdef CODFH_SP // the control is 0x26 in single player (SP 0xCE6F0)
                        v_178 = unk_4B9308.sub_EE8F0(unk_3D8, 0x26);
#else
                        v_178 = unk_4B9308.sub_EE8F0(unk_3D8, 0x2A);
#endif
                    else
                        v_178 = unk_4B9308.sub_EE8F0(unk_3D8, 0xC);
                }
                if (v_178 != 0.0f && unk_1A48[unk_1AE4]->get_unk_448()->unk_D8 == 1)
                {
                    if (unk_1A48[unk_1AE4]->sub_117510())
                        unk_1A48[unk_1AE4]->sub_1190B0();
                }
                else if (v_178 != 0.0f && unk_1A48[unk_1AE4]->get_unk_448()->unk_D8 == 2 && unk_1A04 == 2)
                {
                    if (unk_1A48[unk_1AE4]->sub_117460() && !unk_1A48[unk_1AE4]->unk_12)
                    {
                        RwInt32 v_1B4;
                        RwInt32 v_1B8;

                        if (!unk_1A48[unk_1AE4]->unk_230 && !unk_1A48[unk_1AE4]->unk_228)
                        {
                            if (sub_77B70(unk_1A48[unk_1AE4]->get_unk_448()->unk_68, (void **)(&v_1B8), (void **)(&v_1B4)))
                            {
                                unk_284->sub_794C0(0.0f);
                                unk_284->sub_796A0((RtAnimAnimation *)v_1B8,
                                                   unk_1A48[unk_1AE4]->get_unk_448()->unk_68, 0,
                                                   (struct type_783F0 *)v_1B4, 0.0f, 1.0f, 1.0f);
                            }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                            else if (unk_1A48[unk_1AE4]->get_unk_448()->unk_68)
                                sub_19A750("WARNING: Missing a bipod deploy anim 0x%x.",
                                           unk_1A48[unk_1AE4]->get_unk_448()->unk_68);
#endif
                            unk_1A48[unk_1AE4]->unk_10 = 0;
                            unk_1A48[unk_1AE4]->unk_228 = 1;
                        }
                        else
                        {
                            unk_1A48[unk_1AE4]->unk_22C = 1;
                            unk_1A48[unk_1AE4]->unk_230 = 0;
                            unk_1A48[unk_1AE4]->unk_10 = 0;
                            if (sub_77B70(unk_1A48[unk_1AE4]->get_unk_448()->unk_6C, (void **)(&v_1B8), (void **)(&v_1B4)))
                            {
                                unk_284->sub_794C0(0.0f);
                                unk_284->sub_796A0((RtAnimAnimation *)v_1B8,
                                                   unk_1A48[unk_1AE4]->get_unk_448()->unk_6C, 0,
                                                   (struct type_783F0 *)v_1B4, 0.0f, 1.0f, 1.0f);
                            }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                            else if (unk_1A48[unk_1AE4]->get_unk_448()->unk_6C)
                                sub_19A750("WARNING: Missing a bipod undeploy anim 0x%x.",
                                           unk_1A48[unk_1AE4]->get_unk_448()->unk_6C);
#endif
                        }
                    }
                }
                else
                {
                    type_10F710_1A48 *v_1D8 = unk_1A48[unk_1AE4]->unk_460;

                    if (v_178 != 0.0f && v_1D8)
                    {
                        RwInt32 v_1DC;

                        if (unk_20F0 != 0.0f && !v_158)
                            unk_20F4 = 1;
                        v_1DC = 1;
                        if (v_158 && !unk_20F4)
                            v_1DC = 0;
                        if (v_1DC)
                        {
                            v_1D8->vf_018();
                            if (!unk_1B1C)
                                sub_114F50();
                            unk_1B1C = 1;
#ifndef CODFH_SP // MP only: single player's player has no unk_1B18 (SP 0xCE6F0, 0xC4AF0)
                            unk_1B18 = 1;
#endif
                        }
                    }
                }
                v_178 = unk_4B9308.sub_EE8F0(unk_3D8, 7);
                if (v_178 != 0.0f && unk_1A48[unk_1AE4]->vf_014())
                    unk_1A48[unk_1AE4]->vf_020();
            }
        }
        {
            RwReal v_1E0;
            RwReal v_1E4;
            RwReal v_1E8;
            RwInt32 v_1F8;
            type_3DAFC8 *v_1F4;

            unk_20F0 = unk_4B9308.sub_EE8F0(unk_3D8, 3);
#ifdef CODFH_SP // shape: operands swapped for /O2
            if (unk_20F0 == 0.0f)
#else
            if (0.0f == unk_20F0)
#endif
                unk_20F4 = 0;
            v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 8);
            v_1E4 = unk_4B9308.sub_EE8F0(unk_3D8, 9);
            v_1E8 = unk_4B9308.sub_EE8F0(unk_3D8, 0xA);
            if ((v_1E4 != 0.0f || v_1E8 != 0.0f) && unk_1A48[unk_1AE4]->sub_1175D0())
                sub_104480(v_1E4, v_1E8);
            if (unk_1A0C)
            {
                RwReal v_1EC = arg_0 * 0.5f;

                unk_1A10 += v_1EC * unk_1A18;
                if (unk_1A10 >= 1.0f)
                {
                    unk_1A0C = 0;
                    unk_1A08 = unk_1A04;
                }
            }
            if (0.0f != unk_4B9308.sub_EE8F0(unk_3D8, 6) || unk_1B04)
                v_1E0 = 0.0f;
            else
                v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 0xD);
            if (v_1E0 != 0.0f && unk_1AE4 != 0x1D && unk_1AE4 != 0x23 && unk_1A48[unk_1AE4]->unk_20 == 0.0f &&
                unk_1A48[unk_1AE4]->unk_1C == 0.0f && unk_19D0 != 7 && !unk_1B2C && unk_1B3C && unk_2148 == 0.0f &&
                !unk_2244 && !unk_1A48[unk_1AE4]->unk_11)
            {
                if (unk_1A48[unk_1AE4]->unk_46)
                {
                    unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                    unk_1A48[unk_1AE4]->unk_21C = 0;
                    unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
                    unk_1A48[unk_1AE4]->unk_46 = 0;
                }
                sub_100200(unk_1B30[unk_1AE8 == 0]);
            }
            unk_2118.sub_D48D0(0);
            v_1F4 = sub_108CC0(325.0f);
            if (v_1F4 && !((v_1F4->unk_28 >> 9) & 1) &&
                (!v_1F4->vf_008() || v_1F4->vf_008()->unk_64C) && dword_4B9190 &&
                unk_21B4.sub_1E3BF0(1) > 0)
            {
                sub_10F7E0(0xE, 1);
                unk_2118.sub_D48D0(v_1F4);
            }
            v_1F8 = 0;
            if (unk_2118.sub_D4910())
            {
#ifdef CODFH_SP // the control is 0x24 in single player (SP 0xCE6F0)
                v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 0x24);
#else
                v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 0x28);
#endif
                if (sub_10F790() == 0xE && v_1E0 != 0.0f)
                {
                    type_3DAFC8 *v_1FC = (type_3DAFC8 *)unk_2118.sub_D4910();

                    if (v_1F4)
                    {
                        v_1FC->sub_13F940(sub_104420() * 0.5f);
                        if (((type_4B8888 *)dword_4B8888)->unk_00_4)
                            v_1FC->sub_13C490(0);
                        dword_4B1E98.sub_8A980(&dword_4B1B38, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                        dword_4B1E98.sub_8A980(&dword_4B1E90, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                        unk_21B4.sub_116080(1, -1);
                        v_1F8 = 1;
                        sub_6B5F0("HealthFull", (type_67620 *)(v_1FC->vf_098()), 0, 0, 0, 0, 1, 0);
                    }
                }
            }
            else
                sub_10F7E0(0xE, 0);
            v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 0x10);
            if (v_1E0 != 0.0f && (unk_19D0 != 5 || unk_4D0 == 1) && unk_19D0 != 0xC && unk_1B40 &&
                unk_2148 == 0.0f && !unk_1B04 && !unk_1A48[unk_1AE4]->unk_11 && !v_1F8 &&
                !unk_1A48[unk_1AE4]->unk_224)
            {
                RwInt32 v_200 = 1;

                if (unk_19D0 == 7 && unk_21B4.get_unk_34() != 1)
                    v_200 = 0;
                if (v_200)
                {
                    unk_1A48[unk_1AE4]->unk_13 = 1;
                    unk_1A48[unk_1AE4]->unk_12 = 0;
                    unk_21B4.sub_115690(v_1E0, -1);
                }
            }
#ifdef CODFH_SP
            v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 0x24);
#else
            v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 0x28);
#endif
            if (v_1E0 != 0.0f && (unk_19D0 != 5 || unk_4D0 == 1) && unk_19D0 != 0xC && unk_1B40 &&
                unk_2148 == 0.0f && !unk_2118.sub_D4910())
            {
                unk_21B4.sub_115690(v_1E0, 1);
                dword_4B9190->sub_E07D0();
            }
#ifdef CODFH_SP // the control is 0x25 in single player (SP 0xCE6F0)
            v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 0x25);
#else
            v_1E0 = unk_4B9308.sub_EE8F0(unk_3D8, 0x29);
#endif
            if (v_1E0 != 0.0f && (unk_19D0 != 5 || unk_4D0 == 1) && unk_19D0 != 0xC)
                dword_4B9190->sub_E07D0();
        }
    }
    vf_258(arg_0);
    unk_538 = 1.0f;
#ifdef CODFH_SP // as above: only while alive and not in a vehicle (SP 0xCE6F0)
    if (unk_19F8 <= 0 && unk_19DC > 0.0f && !((dword_4B86F8 >> 6) & 1) && unk_2148 == 0.0f)
#else
    if (!((dword_4B86F8 >> 4) & 1))
#endif
    {
        RwReal v_208;

        v_208 = unk_4B9308.sub_EE8F0(unk_3D8, 6);
        if ((v_14C->unk_3A0 && v_208 != 0.0f || unk_1A48[unk_1AE4]->unk_230 || unk_1B14) &&
            !unk_1A48[unk_1AE4]->unk_12 && unk_19D0 != 7 && !unk_1B2C && unk_1B3C && v_8 != 0x20 &&
            unk_2148 == 0.0f && unk_1A48[unk_1AE4]->unk_13 && (unk_1A04 != 2 || !unk_19D8) &&
            !unk_1A48[unk_1AE4]->unk_224)
        {
            if (unk_1B04)
            {
                if (unk_1B10)
                {
                    unk_1A48[unk_1AE4]->sub_11D740(0);
                    unk_1B04 = 0;
                    unk_1B08 = 1;
                    unk_1A48[unk_1AE4]->unk_298 -= 1.0f;
                }
            }
            else if (!unk_1A48[unk_1AE4]->unk_12 && sub_1014E0())
            {
                unk_1A48[unk_1AE4]->sub_11D740(0);
                unk_1B04 = 1;
                unk_1B08 = 0;
                if (dword_4B9190)
                    dword_4B9190->sub_DEB80(1);
            }
            sub_104FF0(arg_0);
        }
        else if (unk_1B04)
        {
            unk_1A48[unk_1AE4]->sub_11D740(1);
            sub_1062A0();
            sub_104FF0(arg_0);
            if (dword_4B9190)
                dword_4B9190->sub_DEB80(0);
        }
        else
        {
            // A compiled-out check of a dword (docs/toolchain.md): the test's
            // registers are one load on.
            if (!unk_1B04)
            {
            }
            if (unk_1B08 || unk_1B04)
                sub_104FF0(arg_0);
        }
        v_208 = unk_4B9308.sub_EE8F0(unk_3D8, 0xE);
        if (v_208 != 0.0f && !unk_2244)
        {
            RwInt32 v_20C = unk_21B4.sub_115620();

            if (v_20C)
            {
                unk_21B4.sub_115980(v_20C);
                switch (v_20C)
                {
                case 2:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                    dword_4B1E98.sub_8A980(&dword_4B1C10, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                    break;
                case 5:
                    dword_4B1E98.sub_8A980(&dword_4B1C58, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                    break;
                case 7:
                    dword_4B1E98.sub_8A980(&dword_4AF028, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                    break;
                }
            }
            else
                dword_4B1E98.sub_8A980(&dword_4B1F44, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
        }
    }
    sub_10C7B0(arg_0);
    sub_D41A0();
    unk_2174.sub_D48D0(0);
}

#ifdef CODFH_SP
// Single player only: the difficulty's multipliers of flt_4F28E4 (SP
// 0xBF910; the player's damage taken, vf_064), flt_4F28A8 (SP 0xBF930) and
// flt_4F28B4 (SP 0xBF950), 1 outside 0 to 2, as sub_104420 reads
// flt_4F28CC (their debug prints compiled out).
// sp-match: ?sp_sub_BF910@@YAMXZ @ 0x000BF910
RwReal sp_sub_BF910()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F28E4[dword_42B714];
    }
    return 1.0f;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_BF930@@YAMXZ @ 0x000BF930
RwReal sp_sub_BF930()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F28A8[dword_42B714];
    }
    return 1.0f;
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_BF950@@YAMXZ @ 0x000BF950
RwReal sp_sub_BF950()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F28B4[dword_42B714];
    }
    return 1.0f;
}
#endif

#ifdef CODFH_SP
// The weapon in hand's sub_117370 (type_10F710.h), out of line in single player.
// sp-match: ?sp_sub_BF990@type_10F710@@QAEXXZ @ 0x000BF990
#endif

// match: ?sub_104420@@YAMXZ @ 0x00104420
// sp-match: ?sub_104420@@YAMXZ @ 0x000BF970
RwReal sub_104420()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("GameDiff:GetPlayerHealthPupMultiplier  m_eDifficulty=%d, pupMod=%f\n", dword_42B714,
               flt_4F28CC[dword_42B714]);
#endif
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F28CC[dword_42B714];
    }
    return 1.0f;
}

// match: ?sub_104480@type_10F710@@QAEXMM@Z @ 0x00104480
// sp-match: ?sub_104480@type_10F710@@QAEXMM@Z @ 0x000C5CE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_104480(RwReal arg_0, RwReal arg_4)
{
    // Two words the frame keeps unused (0x3C, 0x40), as unused locals;
    // what they held in the source is not known.
    RwInt32 fp_40;
    RwInt32 ebp_3C;
    RwInt32 lcl_38;
    RwInt32 r34;
    RwV3d lv_30;
    RwMatrix *frm_24;
    RwFrame *t20;
    RwV3d l1C;
    RwMatrix *lv_10;
    RwFrame *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = 0;
    bp_4 = 1;
    if (unk_1A04 == 2)
    {
        slot_C = unk_338.unk_08;
        if (!slot_C)
        {
            return;
        }
        lv_10 = RwFrameGetMatrix(slot_C);
        l1C = *RwMatrixGetPos(lv_10);
        l1C.y = l1C.y + 65.0f;
        if (sub_115230(&l1C, unk_4C * 0.75f))
        {
            return;
        }
    }
    if (unk_1A04 == 1 && arg_0 != 0.0f)
    {
        t20 = unk_338.unk_08;
        if (!t20)
        {
            return;
        }
        frm_24 = RwFrameGetMatrix(t20);
        lv_30 = *RwMatrixGetPos(frm_24);
        lv_30.y = lv_30.y + 85.0f;
        if (sub_115230(&lv_30, unk_4C * 0.75f))
        {
            return;
        }
    }
    if ((arg_0 != 0.0f || arg_4 != 0.0f) && unk_1A1C != 2)
    {
        unk_1A08 = unk_1A04;
        switch (unk_1A1C)
        {
        case 1:
            switch (unk_1A04)
            {
            case 0:
                unk_1A04 = 1;
                bp_8 = 1;
                break;
            case 1:
                if (arg_4 != 0.0f)
                {
                    unk_1A04 = 2;
                    bp_8 = 1;
                }
                else
                {
                    bp_4 = 0;
                }
                break;
            case 2:
                if (arg_0 != 0.0f)
                {
                    unk_1A04 = 1;
                    bp_8 = 0;
                }
                else
                {
                    bp_4 = 0;
                }
                break;
            }
            break;
        case 3:
            switch (unk_1A04)
            {
            case 0:
                if (arg_4 != 0.0f)
                {
                    unk_1A04 = 1;
                    bp_8 = 1;
                }
                else
                {
                    bp_4 = 0;
                }
                break;
            case 1:
                if (arg_0 != 0.0f)
                {
                    unk_1A04 = 0;
                    bp_8 = 0;
                }
                else
                {
                    bp_4 = 0;
                }
                break;
            case 2:
                unk_1A04 = 0;
                bp_8 = 1;
                break;
            }
            break;
        default:
            if (arg_4 != 0.0f)
            {
                bp_8 = 1;
                r34 = unk_1A04;
                r34++;
                unk_1A04 = r34;
                if (unk_1A04 > 2)
                {
                    unk_1A04 = 2;
                    bp_4 = 0;
                }
            }
            else
            {
                bp_8 = 0;
                lcl_38 = unk_1A04;
                lcl_38--;
                unk_1A04 = lcl_38;
                if (unk_1A04 < 0)
                {
                    unk_1A04 = 0;
                    bp_4 = 0;
                }
            }
            break;
        }
        if (bp_4)
        {
            unk_1A48[unk_1AE4]->sub_119830(unk_1A04, bp_8);
            unk_1A0C = 1;
            unk_1A10 = 0;
            unk_1AF4 = sub_104850(unk_1AF4);
        }
        unk_3E0 = 45.0f;
    }
}

// match: ?sub_104850@@YAMM@Z @ 0x00104850
// sp-match: ?sub_104850@@YAMM@Z @ 0x000BF9F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_104850(RwReal arg_0)
{
    RwReal bp_8;
    RwInt32 bp_4;

    if (arg_0 > -3.14159f && arg_0 < 3.14159f)
    {
        return arg_0;
    }
    bp_4 = (RwInt32)(bp_8 = arg_0 / 6.2831855f);
    arg_0 = arg_0 - bp_4 * 6.2831855f;
    if (arg_0 > 3.14159f)
    {
        arg_0 = arg_0 - 6.2831855f;
    }
    else if (arg_0 < -3.14159f)
    {
        arg_0 = arg_0 + 6.2831855f;
    }
    return arg_0;
}

// match: ?sub_1048E0@type_10F710@@QAEXXZ @ 0x001048E0
// sp-match: ?sub_1048E0@type_10F710@@QAEXXZ @ 0x000C5F70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_1048E0()
{
    RwV3d m_18;
    RwV3d *slot_C;
    RwV3d *bp_8;
    type_3D3548 *bp_4;

    if (get_unk_19D0_r() != 5 && unk_1A34.sub_D4910() && unk_1A34.sub_D4910()->vf_120()
        && sub_140C90(unk_1A34.sub_D4910()->sub_CD550(), sub_CD550()) < flt_3D9750
        && ((unk_1A34.sub_D4910()->unk_2C & 7) & (unk_2C & 7)))
    {
        if (sub_10F710() == 0xF)
        {
            bp_8 = unk_1A34.sub_D4910()->sub_CD550();
            if (unk_1A34.sub_D4910()->vf_120())
            {
                unk_1A34.sub_D4910()->vf_120()->sub_1A2E0();
            }
            bp_4 = dword_4B86A0;
            while (bp_4)
            {
                slot_C = 0;
                slot_C = (RwV3d *)bp_4->vf_0C4();
                if (slot_C && bp_4 != unk_1A34.sub_D4910())
                {
                    RwV3dSub(&m_18, slot_C, bp_8);
                    if (RwV3dDotProduct(&m_18, &m_18) < flt_429AA4 && bp_4->vf_120())
                    {
                        bp_4->vf_120()->sub_1A2E0();
                    }
                }
                bp_4 = bp_4->unk_10;
            }
        }
        if (unk_1A34.sub_D4910()->vf_120()->sub_1A1F0())
        {
            sub_10F7E0(0xF, 1);
        }
        else
        {
            sub_10F7E0(0xF, 0);
        }
    }
    else
    {
        sub_10F7E0(0xF, 0);
    }
}

// match: ?sub_104B30@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00104B30
// sp-match: ?sub_104B30@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000C1540
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *sub_104B30(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                                RwReal arg_C, void *arg_10)
{
    RwV3d w48;
    RwV3d ebp_3C;
    RwReal lv_30;
    type_93DF0 *fp_2C;
    RwInt32 q28;
    RwV3d frm_24;
    RwReal m_18;
    RwReal ebp_14;
    RwV3d *lv_10;
    RwV3d slot_C;

    fp_2C = (type_93DF0 *)arg_10;
    slot_C = arg_0->t.line.start;
    m_18 = sub_8F960(arg_8->vertices, &arg_8->normal, &slot_C);
    RwV3dSub(&ebp_3C, &arg_0->t.line.start, &slot_C);
    q28 = ebp_3C.y > 0.0f ? 1 : 0;
    fp_2C->unk_24 = m_18;
    fp_2C->unk_2C_v = slot_C;
    fp_2C->unk_60 = 1;
    lv_10 = RwMatrixGetUp(RwFrameGetMatrix(fp_2C->unk_04->get_unk_340()));
    ebp_14 = RwV3dDotProduct(lv_10, &arg_8->normal);
    if (q28 && ebp_14 > 0.342f)
    {
        fp_2C->unk_64 = 1;
        return arg_8;
    }
    RwV3dNegate(&w48, &arg_8->normal);
    RwV3dNormalize(&frm_24, RwMatrixGetAt(RwFrameGetMatrix(fp_2C->unk_04->get_unk_340())));
    lv_30 = RwV3dDotProduct(&frm_24, &w48);
    if (lv_30 < 0.0f)
    {
        return arg_8;
    }
    if (m_18 < fp_2C->unk_28 || fp_2C->unk_28 == 0.0f)
    {
        fp_2C->unk_28 = m_18;
    }
    return arg_8;
}

// match: ?sub_104D00@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00104D00
// sp-match: ?sub_104D00@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000C1680
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_104D00(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10)
{
    RwReal loc50;
    RwV3d x4C;
    RwReal fp_40;
    const RwSphere *ebp_3C;
    type_4C19C0 *local_38;
    RwReal local_34;
    type_10F710 *frm_30;
    RwReal stk_2C;
    RwV3d slot_28;
    RwV3d *l1C;
    RwV3d m_18;
    const RwSphere *slot_C;
    type_93DF0 *bp_8;
    type_3D3548 *bp_4;

    if (sub_FB9C0(arg_8) & 8)
    {
        return arg_8;
    }
    bp_8 = (type_93DF0 *)arg_10;
    bp_4 = sub_FB960(arg_8);
    if (bp_8->unk_04 && bp_4 && bp_8->unk_04 != bp_4)
    {
        frm_30 = (type_10F710 *)bp_8->unk_04;
        slot_C = RpAtomicGetWorldBoundingSphere(arg_8);
        l1C = RwMatrixGetPos(RwFrameGetMatrix(bp_8->unk_04->get_unk_340()));
        ebp_3C = slot_C;
        RwV3dSub(&m_18, &ebp_3C->center, l1C);
        fp_40 = RwV3dLength(&m_18) - slot_C->radius;
        if (bp_8->unk_08 && fp_40 * fp_40 > bp_8->unk_28 && bp_8->unk_28 != 0.0f)
        {
            return arg_8;
        }
        local_38 = frm_30->unk_1A48[frm_30->unk_1AE4]->unk_448;
        RwV3dNormalize(&x4C, RwMatrixGetAt(RwFrameGetMatrix(frm_30->get_unk_340())));
        RwV3dNormalize(&slot_28, &m_18);
        loc50 = RwV3dDotProduct(&x4C, &slot_28);
        local_34 = atan(slot_C->radius / RwV3dLength(&m_18))
                 + (70.0f / local_38->unk_3A4_r[frm_30->unk_1A04] * 0.5f) * 0.0174532924f;
        stk_2C = acos(0.99999f > (loc50 > -0.99999f ? loc50 : -0.99999f)
                          ? (loc50 > -0.99999f ? loc50 : -0.99999f)
                          : 0.99999f);
        if (stk_2C > local_34)
        {
            return arg_8;
        }
        bp_8->unk_08 = bp_4;
        bp_8->unk_10 = arg_8;
        bp_8->unk_28 = fp_40 * fp_40;
    }
    return arg_8;
}

// match: ?sub_104F70@type_10F710@@QAEXXZ @ 0x00104F70
// sp-match: ?sub_104F70@type_10F710@@QAEXXZ @ 0x000C1850
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_104F70()
{
    type_3DD948 *bp_8;
    type_712B0_10F710 *bp_4;

    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    unk_534 = bp_4->get_unk_F0();
    bp_8 = (type_3DD948 *)unk_2110.sub_D4910();
    if (bp_8)
    {
        bp_8->unk_3C0 = get_unk_534();
    }
}

// The aim's zoom (after the step's aiming). Zooming in (sub_1014E0 allows it
// and the weapon's zoom time is under its settings' bounds for the stance):
// the time runs on (back while leaving), the field of view and the scope's
// scale follow the settings' zoom by the fraction reached, and the weapon's
// sway offsets by it. Otherwise the zoom is left at once or, allowed, set to
// the settings' full zoom. Zoomed beyond 16, the near clip plane follows the
// nearest surface or entity in a sphere of 400 around the player (at least
// 10; 400 with none).
// match: ?sub_104FF0@type_10F710@@QAEXM@Z @ 0x00104FF0
// sp-match: ?sub_104FF0@type_10F710@@QAEXM@Z @ 0x000C6110
void type_10F710::sub_104FF0(RwReal arg_0)
{
    type_4C19C0 *v_8;
    type_712B0_10F710 *v_C;
    RwReal v_10;

    v_8 = unk_1A48[unk_1AE4]->unk_448;
    v_C = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_C && v_C->vf_008() != 1)
    {
        v_C = 0;
    }
    v_10 = v_C->get_unk_F0();
    if (sub_1014E0() && (unk_1A48[unk_1AE4]->unk_298 < v_8->unk_3B0_a[unk_1A04] ||
                         unk_1A48[unk_1AE4]->unk_298 < v_8->unk_410_a[unk_1A04]))
    {
        RwReal v_14;
        RwReal v_18;

        unk_1B0C = 1;
        if (unk_1B08)
            unk_1A48[unk_1AE4]->unk_298 -= arg_0;
        else
            unk_1A48[unk_1AE4]->unk_298 += arg_0;
        if (unk_1A48[unk_1AE4]->unk_298 < 0.0f)
        {
            unk_1A48[unk_1AE4]->unk_298 = 0.0f;
            unk_1B04 = 0;
            unk_1B08 = 0;
            unk_1B0C = 0;
            unk_1B10 = 0;
        }
        v_14 = unk_1A48[unk_1AE4]->unk_298;
        if (v_8->unk_3B0_a[unk_1A04] != 0.0f)
            v_18 = v_14 / v_8->unk_3B0_a[unk_1A04];
        else
            v_18 = 1.0f;
        if (v_18 > 1.0f)
            v_18 = 1.0f;
        unk_534 = (v_10 / v_8->unk_3A4_r[unk_1A04] - v_10) * v_18 + v_10;
        if (v_8->unk_410_a[unk_1A04] != 0.0f)
            v_18 = v_14 / v_8->unk_410_a[unk_1A04];
        else
            v_18 = 1.0f;
        if (v_18 > 1.0f)
            v_18 = 1.0f;
        unk_1A48[unk_1AE4]->unk_218 = v_18;
        unk_1A48[unk_1AE4]->unk_28C.x = v_18 * v_8->unk_3C8_a[unk_1A04].x;
        unk_1A48[unk_1AE4]->unk_28C.y = v_18 * v_8->unk_3C8_a[unk_1A04].y;
        unk_1A48[unk_1AE4]->unk_28C.z = v_18 * v_8->unk_3C8_a[unk_1A04].z;
        unk_1A48[unk_1AE4]->unk_280.x = v_18 * unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].x;
        unk_1A48[unk_1AE4]->unk_280.y = v_18 * unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].y;
        unk_1A48[unk_1AE4]->unk_280.z = v_18 * unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].z;
        unk_538 = (v_8->unk_3A4_r[unk_1A04] - 1.0f) * v_18 + 1.0f;
    }
    else
    {
        unk_1B0C = 0;
        if (unk_1B08)
        {
            unk_1B08 = 0;
            unk_1A48[unk_1AE4]->unk_28C.x = 0.0f;
            unk_1A48[unk_1AE4]->unk_28C.y = 0.0f;
            unk_1A48[unk_1AE4]->unk_28C.z = 0.0f;
            unk_1A48[unk_1AE4]->unk_298 = 0.0f;
        }
        else if (sub_1014E0())
        {
            if (v_8->unk_3B0_a[unk_1A04] > v_8->unk_410_a[unk_1A04])
                unk_1A48[unk_1AE4]->unk_298 = v_8->unk_3B0_a[unk_1A04];
            else
                unk_1A48[unk_1AE4]->unk_298 = v_8->unk_410_a[unk_1A04];
            if (unk_1A0C)
                unk_538 = sub_112F80(v_8->unk_3A4_r[unk_1A08], v_8->unk_3A4_r[unk_1A04], unk_1A10);
            else
                unk_538 = v_8->unk_3A4_r[unk_1A04];
            unk_534 = v_10 / unk_538;
            unk_1B04 = 1;
            unk_1A48[unk_1AE4]->unk_218 = 1.0f;
            unk_1A48[unk_1AE4]->unk_28C = v_8->unk_3C8_a[unk_1A04];
            unk_1A48[unk_1AE4]->unk_280 = unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04];
        }
    }
    if (v_8->unk_3A4_r[unk_1A04] > 16.0f)
    {
        RwV3d v_24;
        RwInt32 v_28;
        RwReal v_104;
        RwInt32 v_10C;

        v_24.x = 400.0f;
        v_24.y = 100.0f;
        v_24.z = 400.0f;
        v_28 = 0;
        type_93DF0 v_E0;
        RpIntersection v_FC;

        v_FC.type = rpINTERSECTSPHERE;
        v_FC.t.sphere.center = RwFrameGetLTM(get_unk_340())->pos;
        v_FC.t.sphere.radius = v_24.x;
        v_104 = v_FC.t.sphere.radius * v_FC.t.sphere.radius;
        v_E0.unk_6C = 0;
        v_E0.unk_24 = v_104;
        v_E0.unk_20 = 0;
        v_E0.unk_18 = 0;
        v_E0.unk_04 = this;
        v_E0.unk_14 = get_unk_340();
        v_E0.unk_0C = 0;
        v_E0.unk_08 = 0;
        v_E0.unk_60 = 0;
        v_E0.unk_64 = 0;
        v_E0.unk_7C = 0;
        v_E0.unk_28 = 0.0f;
        v_E0.unk_48 = unk_50_r;
        v_E0.unk_50 = &v_28;
        v_E0.unk_58 = 0;
        v_E0.unk_54 = 0;
        v_E0.unk_70 = sub_8F940();
        v_10C = 0;
        for (v_10C = 0; v_10C < 4; v_10C++)
        {
            type_4E5D30 *v_110 = &dword_4E5D30[v_10C];

            if (v_110->get_unk_00())
            {
                if (v_110->get_unk_20())
                    RpWorldForAllAtomicIntersections(v_110->get_unk_20(), &v_FC, sub_104D00, &v_E0);
                if (v_110->get_unk_28())
                    RpCollisionWorldForAllIntersections(v_110->get_unk_28(), &v_FC, sub_104B30, &v_E0);
            }
        }
        if (v_E0.unk_28 != 0.0f)
        {
            RwReal v_184;

            do
            {
                __m128 v_140 = _mm_set_ss(v_E0.unk_28);
                __m128 v_170 = _mm_sqrt_ss(v_140);
                _mm_store_ss(&v_184, v_170);
            } while (0);
            if (v_184 < 10.0f)
                v_184 = 10.0f;
            *(RwReal *)&dword_4CF540 = v_184;
        }
        else
            *(RwReal *)&dword_4CF540 = 400.0f;
    }
}

// match: ?vf_244@type_10F710@@UAEHXZ @ 0x00105A10
// sp-match: ?vf_244@type_10F710@@UAEHXZ @ 0x000C18A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::vf_244()
{
    RpHAnimHierarchy *m_18;
    RwFrame *ebp_14;
    RwMatrix *lv_10;
    RwMatrix *slot_C;
    type_3DD948 *bp_8;
    RwInt32 bp_4;

    ebp_14 = unk_338.unk_08;
    if (ebp_14)
    {
        bp_4 = 1;
        m_18 = unk_284->unk_18;
        slot_C = RpHAnimHierarchyGetMatrixArray(m_18);
        lv_10 = &slot_C[bp_4];
        sub_19B650(&slot_C[bp_4]);
        bp_8 = (type_3DD948 *)unk_2110.sub_D4910();
        if (bp_8)
        {
            if (unk_19D0 == 5 && (unk_1AE4 == 0x1D || unk_1AE4 == 0x23) && unk_4D0 == 2)
            {
                bp_8->sub_1752A0(&unk_490);
            }
            else
            {
                bp_8->sub_1752A0(lv_10);
            }
            bp_8->unk_3C0 = get_unk_534();
            return 1;
        }
    }
    return 0;
}

// The step after the others'. With its trigger: its animation advances, its
// frame is kept orthonormal every 64 frames, its eye height follows the
// stance (blended while it changes), its model and the weapon's hold the
// head bone's place 100 units away; alive and moving freely, the pickup it
// stands on is taken, the help text cleared, its mounted weapon, the action
// object and the performance maps it is in offer their actions (the level's
// end trigger ends the level); then a mounted weapon it no longer holds lets
// it go, and its AI's late step, its vf_1D0 and the ladder's step run.
// match: ?vf_04C@type_10F710@@UAEXM@Z @ 0x00105B00
// sp-match: ?vf_04C@type_10F710@@UAEXM@Z @ 0x000CD320
void type_10F710::vf_04C(RwReal arg_0)
{
    type_712B0_10F710 *v_8;
    RwReal v_14;
    RpHAnimHierarchy *v_18;
    RwMatrix *v_1C;
    RwMatrix v_60;
    RwV3d v_6C;
    type_3DC9B0 *v_78;

    v_8 = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_8 && v_8->vf_008() != 1)
    {
        v_8 = 0;
    }
    if (!v_8)
        return;
    sub_CDF40(arg_0);
    if ((dword_4B87D8 & 0x3F) == 0x3F)
    {
        RwMatrix *v_10 = RwFrameGetMatrix(get_unk_340());

        RwMatrixOrthoNormalize(v_10, v_10);
    }
    unk_3E0 += arg_0;
    unk_48 = v_8->unk_144_a[unk_1A04];
    if (unk_1A0C)
        unk_48 = sub_112F80(v_8->unk_144_a[unk_1A08], v_8->unk_144_a[unk_1A04], unk_1A10);
    v_14 = 100.0f;
    v_18 = unk_284->unk_18;
    v_1C = RpHAnimHierarchyGetMatrixArray(v_18);
    RwMatrixInvert(&v_60, RwFrameGetLTM(RpClumpGetFrame(unk_1A3C.get_unk_08())));
    sub_1414C0(&v_6C, &v_1C->pos, &v_60);
    v_6C.z += 50.0f;
    sub_16DFA0(unk_1A3C.get_unk_08(), &v_6C, v_14);
    sub_16DFA0(unk_1A48[unk_1AE4]->get_unk_428(), &v_6C, v_14);
    if (unk_19F8 <= 0 && unk_19DC > 0.0f && !((dword_4B86F8 >> 6) & 1) && unk_2148 == 0.0f)
    {
        type_144E80 *v_84;
        RwInt32 v_88;
        RwInt32 v_8C;
        RwInt32 v_90;

        if (!sub_106620((struct type_3D94B8 *)unk_2108.sub_D4910()))
            unk_2108.sub_D48D0(0);
        sub_EAB80("", 6);
        if (unk_2108.sub_D4910())
        {
            sub_106A60((type_3D94B8 *)unk_2108.sub_D4910());
            unk_2108.sub_D48D0(0);
        }
        else
        {
            sub_10F7E0(0xB, 0);
            sub_10F7E0(0xC, 0);
        }
        v_78 = (type_3DC9B0 *)unk_210C.sub_D4910();
        if (v_78 && v_78->sub_169190(this))
        {
            if (!unk_1B28)
            {
                sub_10F7E0(5, 1);
                sub_10F7E0(4, 0);
            }
            else
            {
                sub_10F7E0(5, 0);
                sub_10F7E0(4, 1);
            }
        }
        else
        {
            sub_10F7E0(5, 0);
            sub_10F7E0(4, 0);
        }
        if (unk_2114.sub_D4910())
        {
            sub_10F7E0(9, 1);
            if (sub_10F710() == 9)
            {
                if (((type_3D3548 *)unk_2114.sub_D4910())->vf_098())
                    sub_6B5F0("ActionItem", (type_67620 *)(((type_3D3548 *)unk_2114.sub_D4910())->vf_098()), 0, 0, 0, 0, 1, 0);
                sub_10F7E0(9, 0);
            }
        }
        else
            sub_10F7E0(9, 0);
        unk_2114.sub_D48D0(0);
        v_84 = (type_144E80 *)unk_24C;
        v_88 = unk_248;
        v_8C = 1;
        v_90 = sub_144E80(&v_84, &v_8C, -1);
        while (v_90 != -1)
        {
            if (v_8C & v_88)
            {
                RwInt32 v_94 = 1;
                Trigger *v_98 = (Trigger *)get_performance_map(v_90);

                if (v_98->vf_008() == 0x24)
                {
                    EndLevelTrigger *v_9C = (EndLevelTrigger *)v_98;

                    if (v_9C->unk_C4)
                    {
                        sub_10F7E0(0, 1);
                        v_94 = 0;
                        if (!sub_10F710())
                        {
                            RwInt32 v_A0;

                            if (dword_4B9190)
                                dword_4B9190->sub_E0410(4);
                            v_A0 = v_9C->sub_CC330();
                            if (v_A0)
                                sub_D8CC0(v_A0);
                            else
                                sub_D8C20();
                        }
                    }
                }
                else
                    sub_10F7E0(0, 0);
                if (v_94 && (v_98->unk_42 & 0xF))
                {
                    sub_10F7E0(9, 1);
                    if (sub_10F790() == 9)
                    {
                        if (dword_4B9190)
                            dword_4B9190->sub_E0410(v_98->unk_42 & 0xF);
                    }
                    else
                        sub_10F7E0(9, 0);
                    break;
                }
                if (sub_10F790() != 9)
                    sub_10F7E0(9, 0);
            }
            v_90 = sub_144E80(&v_84, &v_8C, (RwInt16)v_90);
        }
        if (sub_10F710() == 5 && !v_78->unk_47C)
        {
            v_78->sub_168820(this);
            sub_1090F0(7);
            if (dword_4B9190)
                dword_4B9190->sub_DEB80(2);
        }
        if (sub_10F710() == 4)
        {
            v_78 = (type_3DC9B0 *)unk_210C.sub_D4910();
            if (v_78 && unk_1B28 && v_78->sub_169350(1))
            {
                v_78->sub_168A90(this);
                sub_1090F0(0);
                if (dword_4B9190)
                    dword_4B9190->sub_DEB80(0);
            }
        }
    }
    v_78 = (type_3DC9B0 *)unk_210C.sub_D4910();
    if (v_78 && (unk_19D0 == 7 || unk_1B28) && v_78->vf_1F8(0) != this)
    {
        v_78->sub_168A90(this);
        sub_1090F0(0);
        if (dword_4B9190)
            dword_4B9190->sub_DEB80(0);
    }
    if (v_78)
        v_78->unk_47C = 0;
    if (!unk_1B28)
        unk_210C.sub_D48D0(0);
    sub_16D7F0(0x18);
    unk_550.sub_17A20(arg_0);
    sub_16D850(0x18);
    vf_1D0();
    unk_1A30 = 1.0f;
    if (unk_19D0 == 0xD)
        sub_114E70(arg_0);
}

// match: ?sub_1062A0@type_10F710@@QAEXXZ @ 0x001062A0
// sp-match: ?sub_1062A0@type_10F710@@QAEXXZ @ 0x000C1930
void type_10F710::sub_1062A0()
{
    type_712B0_10F710 *var_4;

    var_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (var_4 && var_4->vf_008() != 1)
    {
        var_4 = 0;
    }
    unk_534 = var_4->unk_F0;
    dword_4CF540 = dword_4CF468;
    unk_1B04 = 0;
    unk_1B08 = 1;
    unk_1A48[unk_1AE4]->unk_298 -= 1.0f;
    set_v3d(&unk_1A48[unk_1AE4]->unk_28C, 0.0f, 0.0f, 0.0f);
    set_v3d(&unk_1A48[unk_1AE4]->unk_280, 0.0f, 0.0f, 0.0f);
    unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].y -= unk_1A48[unk_1AE4]->unk_1C;
    unk_1A48[unk_1AE4]->unk_25C_a[unk_1A04].x += unk_1A48[unk_1AE4]->unk_20;
    unk_1A48[unk_1AE4]->unk_1C = 0.0f;
    unk_1A48[unk_1AE4]->unk_20 = 0.0f;
}

// match: ?sub_1064C0@type_10F710@@QAEHH@Z @ 0x001064C0
// sp-match: ?sub_1064C0@type_10F710@@QAEHH@Z @ 0x000C1A60
RwInt32 type_10F710::sub_1064C0(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 0:
        return 16;
    case 1:
        return 17;
    case 2:
        return 7;
    case 3:
        return 10;
    case 4:
        return 8;
    case 5:
        return 11;
    case 6:
        return 9;
    case 7:
        return 3;
    case 8:
        return 2;
    case 9:
        return 6;
    case 10:
        return 5;
    case 11:
        return 4;
    case 12:
        return 92;
    case 13:
        return 95;
    case 14:
        return 12;
    case 17:
        return 101;
    case 15:
        return 14;
    case 16:
        return 98;
    case 18:
        return 15;
    case 23:
        return 11;
    case 24:
        return 14;
    case 37:
        return 104;
    default:
        return 3;
    }
}

// match: ?sub_106620@type_10F710@@QAEHPAUtype_3D94B8@@@Z @ 0x00106620
// sp-match: ?sub_106620@type_10F710@@QAEHPAUtype_3D94B8@@@Z @ 0x000C6770
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::sub_106620(type_3D94B8 *arg_0)
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!arg_0)
    {
        return 0;
    }
    bp_8 = -1;
    switch (arg_0->unk_3B0.sub_FB710())
    {
    case 2:
        bp_8 = 8;
        break;
    case 3:
        bp_8 = 7;
        break;
    case 4:
        bp_8 = 11;
        break;
    case 5:
        bp_8 = 10;
        break;
    case 6:
        bp_8 = 9;
        break;
    case 7:
        bp_8 = 2;
        break;
    case 8:
        bp_8 = 4;
        break;
    case 9:
        bp_8 = 6;
        break;
    case 10:
        bp_8 = 3;
        break;
    case 11:
        bp_8 = 5;
        break;
    case 12:
        bp_8 = 14;
        break;
    case 14:
        bp_8 = 15;
        break;
    case 15:
        bp_8 = 18;
        break;
    case 16:
        bp_8 = 0;
        break;
    case 17:
        bp_8 = 1;
        break;
    case 92:
        bp_8 = 12;
        break;
    case 95:
        bp_8 = 13;
        break;
    case 13:
    case 98:
        bp_8 = 16;
        break;
    case 101:
        bp_8 = 17;
        break;
    case 104:
        bp_8 = 37;
        break;
    default:
        return 1;
    }
    if (bp_8 == -1)
    {
        return 0;
    }
    bp_4 = sub_10E8C0(bp_8);
    if (!bp_4)
    {
        sub_10DA70(bp_8);
    }
    return bp_4;
}

// match: ?sub_106830@type_10F710@@QAEHHH@Z @ 0x00106830
// sp-match: ?sub_106830@type_10F710@@QAEHHH@Z @ 0x000C1B70
RwInt32 type_10F710::sub_106830(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_4 > 0 && arg_4 < 39
        && (arg_0 == unk_1B48[arg_4][0] || arg_0 == unk_1B48[arg_4][1] || arg_0 == unk_1B48[arg_4][2]))
    {
        return 1;
    }
    return 0;
}

// match: ?sub_1068A0@type_10F710@@QAEHH@Z @ 0x001068A0
// sp-match: ?sub_1068A0@type_10F710@@QAEHH@Z @ 0x000C1BC0
RwInt32 type_10F710::sub_1068A0(RwInt32 arg_0)
{
    RwInt32 var_4;

    var_4 = -1;
    switch (arg_0)
    {
    case 2:
        var_4 = 8;
        break;
    case 3:
        var_4 = 7;
        break;
    case 4:
        var_4 = 11;
        break;
    case 5:
        var_4 = 10;
        break;
    case 6:
        var_4 = 9;
        break;
    case 7:
        var_4 = 2;
        break;
    case 8:
        var_4 = 4;
        break;
    case 9:
        var_4 = 6;
        break;
    case 10:
        var_4 = 3;
        break;
    case 11:
        var_4 = 5;
        break;
    case 12:
        var_4 = 14;
        break;
    case 14:
        var_4 = 15;
        break;
    case 15:
        var_4 = 18;
        break;
    case 16:
        var_4 = 0;
        break;
    case 17:
        var_4 = 1;
        break;
    case 92:
        var_4 = 12;
        break;
    case 95:
        var_4 = 13;
        break;
    case 13:
    case 98:
        var_4 = 16;
        break;
    case 101:
        var_4 = 17;
        break;
    case 104:
        var_4 = 37;
        break;
    }
    return var_4;
}

// Takes the pick-up arg_0 it touched. First by its settings index: a
// weapon (2 to 17, 92 to 104 by threes) sets flag 12, and is its own when
// it carries it (full: flag 18 instead), else its name is flashed (HUD 6);
// a weapon's rounds (18 to 65, 93 to 106 in pairs) can be taken when it
// carries that weapon (full: flag 18); a health pack (75, 76) unless its
// health is full or it is in state 10; the health packs for later (77)
// up to 6, 4 or 2 by the difficulty; the inventory kinds (78 to 89, 108,
// 109) always; the bears (90, 91) set flag 11 (HUD 5). With flag 11 or 18
// set (or rounds it can take) the pick-up's message is kept (or a "full"
// help message shown), the inventory takes it and, when it gave anything,
// the message and its sound play and its trigger respawns; with flag 12 or
// 18 set (or its own weapon) the weapon is taken into the hand it frees or
// swapped with the one in hand (the old one dropped with its rounds), or
// its rounds added, and the trigger respawns. Flag 11 is cleared after.
// match: ?sub_106A60@type_10F710@@QAEXPAUtype_3D94B8@@@Z @ 0x00106A60
// sp-match: ?sub_106A60@type_10F710@@QAEXPAUtype_3D94B8@@@Z @ 0x000C8680
void type_10F710::sub_106A60(type_3D94B8 *arg_0)
{
    type_712B0_10F710 *v_C;
    RwInt32 v_10;
    RwInt32 v_14;
    type_3DF8D8 *v_18;
    RwInt32 v_1C;
    RwInt32 v_20;
    RwInt32 v_24;
    RwInt32 v_28;
    RwInt32 v_2C;
#ifndef CODFH_SP
    RwChar v_88[64];
#endif
    RwInt32 v_144;

    v_C = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_C && v_C->vf_008() != 1)
    {
        v_C = 0;
    }
    v_10 = -1;
    v_14 = 0;
    v_18 = 0;
    v_1C = 0;
    v_20 = 1;
    v_24 = 0;
    v_28 = 0;
    v_2C = arg_0->unk_3B0.sub_FB710();
    switch (v_2C)
    {
    case 75:
    case 76:
        if (unk_19DC < flt_3CD8E0 && unk_19DC > flt_3CD84C && unk_19D0 != 10)
            v_14 = 1;
        else
            sub_10F7E0(18, 1);
        break;
    case 77:
    {
        RwInt32 v_34;

        v_34 = 0;
        switch (dword_42B714)
        {
        case 0:
            v_34 = 6;
            break;
        case 1:
            v_34 = 4;
            break;
        default:
            v_34 = 2;
        }
        if (unk_21B4.sub_1E3BF0(1) < v_34)
            v_14 = 1;
        else
        {
            sub_10F7E0(18, 1);
            v_24 = 1;
        }
        break;
    }
    case 90:
    case 91:
        sub_10F7E0(11, 1);
        if (sub_10F790() == 11 && dword_4B9190)
            dword_4B9190->sub_E0410(5);
        break;
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
    case 61:
    case 62:
    case 63:
    case 64:
    case 65:
    case 93:
    case 94:
    case 96:
    case 97:
    case 99:
    case 100:
    case 102:
    case 103:
    case 105:
    case 106:
    {
        RwInt32 v_3C;

        for (v_3C = 0; v_3C < 39; v_3C++)
        {
            if (sub_106830(v_2C, v_3C))
                break;
        }
        if (v_3C < 39)
        {
            if ((RwUInt32)unk_1A48[v_3C]->unk_418 < unk_1A48[v_3C]->get_unk_448()->unk_CC)
                v_14 = 1;
            else
            {
                sub_10F7E0(18, 1);
                v_28 = 1;
            }
        }
        break;
    }
    case 78:
    case 79:
    case 80:
    case 81:
    case 82:
    case 83:
    case 84:
    case 85:
    case 86:
    case 87:
    case 88:
    case 89:
    case 108:
    case 109:
        v_14 = 1;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 92:
    case 95:
    case 98:
    case 101:
    case 104:
    {
        RwInt32 v_44;

        sub_10F7E0(12, 1);
        v_44 = sub_1068A0(v_2C);
        if ((v_44 == unk_1B30[0] || v_44 == unk_1B30[1]) && !unk_1B2C)
        {
            if ((RwUInt32)unk_1A48[v_44]->unk_418 < unk_1A48[v_44]->get_unk_448()->unk_CC)
                v_1C = 1;
            else
            {
                sub_10F7E0(12, 0);
                sub_10F7E0(18, 1);
                v_28 = 1;
            }
        }
        else if (v_44 != -1 && sub_10F790() == 12)
        {
            if (dword_4B9190)
                dword_4B9190->sub_E0410(6);
            sub_EAB80(unk_1D1C[v_44], 6);
        }
    }
    }
    if (sub_10F710() == 11 || sub_10F710() == 18 || v_14)
    {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares its slot (SP 0xC8680's frame)
        RwChar v_88[64];

#endif
        v_88[0] = 0;
        if (!v_28)
        {
            v_18 = 0;
            switch (v_2C)
            {
            case 75:
            case 76:
                if (unk_19DC >= flt_3CD8E0 && unk_19DC > flt_3CD84C && unk_19D0 != 10)
                {
                    type_3DF8D8_04 v_94;
                    type_3DF8D8_04 *v_98;

                    sub_198A20("COD_HelpMessages+Generic+Error_HealthFull", &v_94);
                    v_98 = sub_17C630();
                    if (!v_98 || (v_98 && v_98->unk_00 != v_94.unk_00))
                    {
                        sub_17C6C0(0);
                        sub_17C500(&v_94, 1, 1);
                        dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                    }
                    v_20 = 0;
                }
                break;
            case 77:
                if (!v_24)
                {
                    v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FA4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                }
                else
                {
                    type_3DF8D8_04 v_A0;
                    type_3DF8D8_04 *v_A4;

                    sub_198A20("COD_HelpMessages+Generic+Error_InvItemFull", &v_A0);
                    v_A4 = sub_17C630();
                    if (!v_A4 || (v_A4 && v_A4->unk_00 != v_A0.unk_00))
                    {
                        sub_17C6C0(0);
                        sub_17C500(&v_A0, 1, 1);
                        dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                    }
                    v_20 = 0;
                }
                dword_4B9190->sub_E07D0();
                break;
            case 90:
            case 91:
            {
                RwInt32 v_A8;

                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9084);
                strcpy(v_88, v_18->sub_197550(0, 0));
                sub_6B5F0("PickedUpTeddyBear", (type_67620 *)(vf_098()), 0, 0, &v_A8, 1, true, false);
                break;
            }
            case 18:
            case 19:
            case 20:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FAC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 21:
            case 22:
            case 23:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FB4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 24:
            case 25:
            case 26:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FBC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 27:
            case 28:
            case 29:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FC4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 30:
            case 31:
            case 32:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FCC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 33:
            case 34:
            case 35:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FD4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 36:
            case 37:
            case 38:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FDC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 39:
            case 40:
            case 41:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FE4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 42:
            case 43:
            case 44:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FEC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 45:
            case 46:
            case 47:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FF4);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 93:
            case 94:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FFC);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 96:
            case 97:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9004);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 51:
            case 52:
            case 53:
            case 99:
            case 100:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B900C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 102:
            case 103:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9014);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 105:
            case 106:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9044);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 63:
            case 64:
            case 65:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B903C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 48:
            case 49:
            case 50:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9034);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 54:
            case 55:
            case 56:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B904C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 57:
            case 58:
            case 59:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9024);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 60:
            case 61:
            case 62:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B902C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 78:
            case 79:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9054);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 80:
            case 81:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B905C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 82:
            case 83:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9064);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 84:
            case 85:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B906C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 86:
            case 87:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9074);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 88:
            case 89:
                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B907C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                break;
            case 108:
            {
                RwInt32 v_AC;

                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B908C);
                strcpy(v_88, v_18->sub_197550(0, 0));
                sub_6B5F0("PickedUpKaiserBear", 0, 0, (type_3D2E7C *)((RwInt32)vf_098()), &v_AC, 1, true, false);
                break;
            }
            case 109:
            {
                RwInt32 v_B0;

                v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9094);
                strcpy(v_88, v_18->sub_197550(0, 0));
                sub_6B5F0("PickedUpStickyBear", 0, 0, (type_3D2E7C *)((RwInt32)vf_098()), &v_B0, 1, true, false);
                break;
            }
            }
        }
        else
        {
            type_3DF8D8_04 v_B8;
            type_3DF8D8_04 *v_BC;

            v_B8.unk_00 = 0x5F20A5E7; // not an address: a key
            v_B8.unk_04 = 0xCC486714; // not an address: a key
            v_BC = sub_17C630();
            if (!v_BC || (v_BC && v_BC->unk_00 != v_B8.unk_00))
            {
                sub_17C6C0(0);
                sub_17C500(&v_B8, 1, 1);
                dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
            }
            v_20 = 0;
        }
        if (v_20)
        {
            RwInt32 v_C0;

            v_C0 = unk_21B4.sub_1159C0(arg_0);
            sub_115390(unk_1A48[unk_1AE4]->unk_414, unk_1A48[unk_1AE4]->unk_418);
            if (v_C0 != -1)
            {
                type_4C09B0 *v_C4;
                PickupTrigger *v_CC;

                if (v_88[0])
                    sub_EACA0(v_88, 0, 0);
                v_C4 = sub_FB6C0(arg_0->unk_3B0.sub_FB710());
                if (v_C4->unk_1C.unk_00)
                    unk_1C0.sub_8A980(&v_C4->unk_1C, this, 1, sub_CD550(), 0, 0);
                v_CC = (PickupTrigger *)arg_0->unk_344.get_unk_08();
                if (v_CC)
                    v_CC->sub_A9910();
                sub_D5A60(arg_0, 0);
                sub_10F7E0(11, 0);
                unk_2240 = 0;
            }
            else
            {
                type_3DF8D8_04 v_D4;
                type_3DF8D8_04 *v_D8;

                v_D4.unk_00 = 0x2B312134; // not an address: a key
                v_D4.unk_04 = 0xB4335C07; // not an address: a key
                v_D8 = sub_17C630();
                if (!v_D8 || (v_D8 && v_D8->unk_00 != v_D4.unk_00))
                {
                    sub_17C6C0(0);
                    sub_17C500(&v_D4, 1, 1);
                    dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                }
            }
        }
    }
    else
    {
        if (sub_10F710() == 12 || sub_10F710() == 18 || v_1C)
        {
            if (!v_28)
            {
                type_4C09B0 *v_E0;
                PickupTrigger *v_180;

                switch (arg_0->unk_3B0.sub_FB710())
                {
                case 2:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FB4);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B909C);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 8;
                    break;
                case 4:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FAC);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90A4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 11;
                    break;
                case 5:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FBC);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90AC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 10;
                    break;
                case 3:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FC4);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90B4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 7;
                    break;
                case 6:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FCC);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90BC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 9;
                    break;
                case 7:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FD4);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90C4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 2;
                    break;
                case 8:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FDC);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90CC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 4;
                    break;
                case 9:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FE4);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90D4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 6;
                    break;
                case 10:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FEC);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90DC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 3;
                    break;
                case 11:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FF4);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90E4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 5;
                    break;
                case 12:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9034);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90EC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 14;
                    break;
                case 14:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B904C);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90FC);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 15;
                    break;
                case 15:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9024);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9104);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 18;
                    break;
                case 16:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B902C);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B910C);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 0;
                    break;
                case 17:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B903C);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9114);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 1;
                    break;
                case 92:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B8FFC);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B911C);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 12;
                    break;
                case 95:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9004);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9124);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 13;
                    break;
                case 13:
                case 98:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B900C);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B90F4);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 16;
                    break;
                case 104:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9044);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B912C);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 37;
                    break;
                case 101:
                    if (v_1C)
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9014);
                    else
                        v_18 = sub_198800((type_3DF8D8_04 *)&unk_4B9134);
                    sub_EACA0(v_18->sub_197550(0, 0), 0, 0);
                    v_10 = 17;
                    break;
                default:
                    v_10 = -1;
                }
                v_E0 = sub_FB6C0(arg_0->unk_3B0.sub_FB710());
                if (v_E0->unk_1C.unk_00)
                    unk_1C0.sub_8A980(&v_E0->unk_1C, this, 1, sub_CD550(), 0, 0);
                if (v_10 != -1)
                {
                    if (v_10 != unk_1AE4)
                    {
                        bool v_E1;
                        RwInt32 v_E8;

                        v_E1 = false;
                        v_E8 = unk_1AE8 == 0;
                        if (v_10 == unk_1B30[v_E8])
                            v_E1 = true;
                        if (!v_E1)
                        {
                            if (unk_1B30[v_E8] == -1)
                            {
                                unk_1B30[v_E8] = v_10;
                                unk_1A48[v_10]->vf_008(this, unk_1A3C.get_unk_08(), v_10);
                                sub_100200(unk_1B30[unk_1AE8 == 0]);
                            }
                            else if (unk_1B30[unk_1AE8] == -1)
                            {
                                unk_1B30[unk_1AE8] = v_10;
                                unk_1A48[v_10]->vf_008(this, unk_1A3C.get_unk_08(), v_10);
                            }
                            else
                            {
                                RwInt32 v_F4;
                                type_4C19C0 *v_150;
                                RwInt32 v_154;
                                RwInt32 v_158;

                                v_F4 = sub_1064C0(unk_1B30[unk_1AE8]);
                                if (v_F4 != -1)
                                {
                                    RwMatrix *v_FC;
                                    RwMatrix v_140;

                                    v_FC = RwFrameGetMatrix(arg_0->unk_338.get_unk_08());
                                    v_140 = *RwFrameGetMatrix(unk_338.get_unk_08());
                                    v_140.pos.x = v_FC->pos.x;
                                    v_140.pos.z = v_FC->pos.z;
                                    v_144 = unk_1A48[unk_1B30[unk_1AE8]]->unk_414;
                                    unk_1A48[unk_1B30[unk_1AE8]]->unk_414 = 0;
                                    sub_FABC0(v_F4, v_144, &v_140, 1.0f, 1, 0);
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
                                    unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(),
                                                      0, 0);
                                    unk_1A48[unk_1AE4]->unk_46 = 0;
                                }
#ifdef CODFH_SP // single player calls the inline out of line (SP 0xBF990, from SP 0xC8680)
                                sp_sub_BF990();
#else
                                unk_1A48[unk_1AE4]->sub_117370();
#endif
                                unk_1B30[unk_1AE8] = v_10;
                                unk_1AE4 = v_10;
                                unk_1A48[unk_1AE4]->vf_008(this, unk_1A3C.get_unk_08(), unk_1AE4);
                                v_150 = unk_1A48[unk_1AE4]->unk_448;
                                if (sub_77B70(v_150->unk_38, (void **)(&v_158), (void **)(&v_154)))
                                {
                                    unk_284->sub_794C0(0.0f);
                                    unk_284->sub_796A0((RtAnimAnimation *)v_158, v_150->unk_38, 0,
                                                       (struct type_783F0 *)v_154, 0.0f, 1.0f, 1.0f);
                                    unk_1A48[unk_1AE4]->unk_224 = 3;
                                }
                            }
                            v_144 = arg_0->unk_3B0.unk_04;
                            unk_1A48[unk_1B30[unk_1AE8]]->unk_414 = v_144;
                            if ((RwUInt32)unk_1A48[unk_1B30[unk_1AE8]]->unk_414 >
                                unk_1A48[unk_1B30[unk_1AE8]]->get_unk_448()->unk_C8)
                            {
                                v_144 = unk_1A48[unk_1B30[unk_1AE8]]->unk_414 -
                                        unk_1A48[unk_1B30[unk_1AE8]]->get_unk_448()->unk_C8;
                                unk_1A48[unk_1B30[unk_1AE8]]->unk_414 =
                                    unk_1A48[unk_1B30[unk_1AE8]]->get_unk_448()->unk_C8;
                            }
                            else
                                v_144 = 0;
                            unk_1A48[v_10]->unk_418 = unk_1A48[v_10]->unk_418 + v_144;
                            sub_108B60();
                            unk_2134 = sub_10E930();
                        }
                        else
                        {
                            unk_1A48[unk_1B30[v_E8]]->unk_418 =
                                unk_1A48[unk_1B30[v_E8]]->unk_418 + arg_0->unk_3B0.unk_04;
                            if ((RwUInt32)unk_1A48[unk_1B30[v_E8]]->unk_418 >
                                unk_1A48[unk_1B30[v_E8]]->get_unk_448()->unk_CC)
                                unk_1A48[unk_1B30[v_E8]]->unk_418 = unk_1A48[unk_1B30[v_E8]]->get_unk_448()->unk_CC;
                        }
                    }
                    else
                    {
                        unk_1A48[unk_1AE4]->unk_418 = unk_1A48[unk_1AE4]->unk_418 + arg_0->unk_3B0.unk_04;
                        if ((RwUInt32)unk_1A48[unk_1AE4]->unk_418 > unk_1A48[unk_1AE4]->get_unk_448()->unk_CC)
                            unk_1A48[unk_1AE4]->unk_418 = unk_1A48[unk_1AE4]->get_unk_448()->unk_CC;
                        if (!unk_1A48[unk_1AE4]->unk_414 && !unk_1A48[unk_1AE4]->unk_12)
                            unk_1A48[unk_1AE4]->vf_020();
                        sub_115390(unk_1A48[unk_1AE4]->unk_414, unk_1A48[unk_1AE4]->unk_418);
                        dword_4B9190->sub_E07A0(unk_1A48[unk_1AE4]->unk_414,
                                                unk_1A48[unk_1AE4]->get_unk_448()->unk_C8);
                    }
                }
                v_180 = (PickupTrigger *)arg_0->unk_344.get_unk_08();
                if (v_180)
                    v_180->sub_A9910();
                sub_D5A60(arg_0, 0);
                sub_10F7E0(12, 0);
                unk_2240 = 0;
            }
            else
            {
                type_3DF8D8_04 v_188;
                type_3DF8D8_04 *v_18C;

                v_188.unk_00 = 0x5F20A5E7; // not an address: a key
                v_188.unk_04 = 0xCC486714; // not an address: a key
                v_18C = sub_17C630();
                if (!v_18C || (v_18C && v_18C->unk_00 != v_188.unk_00))
                {
                    sub_17C6C0(0);
                    sub_17C500(&v_188, 1, 1);
                    dword_4B1E98.sub_8A980(&dword_4B1A18, 0, 0, (RwV3d *)vf_0C4(), 1, 0);
                }
                v_20 = 0;
            }
        }
        sub_10F7E0(11, 0);
    }
}

// match: ?sub_108B60@type_10F710@@QAEXXZ @ 0x00108B60
// sp-match: ?sub_108B60@type_10F710@@QAEXXZ @ 0x000C6920
void type_10F710::sub_108B60()
{
    if (unk_1A48[unk_1AE4])
    {
        sub_115390(unk_1A48[unk_1AE4]->unk_414, unk_1A48[unk_1AE4]->unk_418);
    }
}

// match: ?sub_108BC0@type_10F710@@QAEXHH@Z @ 0x00108BC0
// sp-match: ?sub_108BC0@type_10F710@@QAEXHH@Z @ 0x000C6960
void type_10F710::sub_108BC0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    switch (arg_0)
    {
    case 2:
        var_4 = 0x15;
        break;
    case 5:
        var_4 = 0x1F;
        break;
    case 7:
        var_4 = 0x21;
        break;
    case 8:
        var_4 = 0x14;
        break;
    case 9:
        var_4 = 0x16;
        break;
    case 10:
        var_4 = 0x13;
        break;
    case 11:
        var_4 = 0x22;
        break;
    case 12:
        var_4 = 0x26;
        break;
    default:
        var_4 = 0x15;
        break;
    }
    if (unk_1A48[var_4] && unk_1A48[var_4]->get_unk_41E())
    {
        unk_1AF0 = unk_1AE4;
        sub_100200(var_4);
    }
}

// The nearest entity of the two entity lists with under 0.4 of its health
// (vf_17C) within arg_0 of its eye point (its position raised by half its
// height) that is inside both its frame's and its turned view's cones,
// which narrow with the distance; 0 for none.
// match: ?sub_108CC0@type_10F710@@QAEPAUtype_3DAFC8@@M@Z @ 0x00108CC0
// sp-match: ?sub_108CC0@type_10F710@@QAEPAUtype_3DAFC8@@M@Z @ 0x000C1D40
type_3DAFC8 *type_10F710::sub_108CC0(RwReal arg_0)
{
    RwReal v_8;
    RwReal v_C;
    RwReal v_10;
    type_3DAFC8 *v_14;
    RwV3d *v_18;
    RwMatrix *v_20;
    RwV3d *v_24;
    RwMatrix v_70;
    RwV3d *v_74;
    RwInt32 v_78;
    type_3D3548 *v_7C;
    RwV3d *v_80;
    RwV3d v_8C;
    RwReal v_90;
    RwReal v_94;
    RwV3d v_A0;
    RwV3d v_AC;
    RwReal v_B0;
    RwReal v_B4;
    RwV3d v_C0;
    RwReal v_C4;
    RwReal v_C8;

    v_8 = 1.0e10f;
    v_C = arg_0 * arg_0;
    v_10 = unk_48 * 0.5f;
    v_14 = 0;
    v_18 = (RwV3d *)vf_0C4();
    v_20 = RwFrameGetMatrix(unk_338.get_unk_08());
    v_24 = &v_20->at;
    v_70 = *v_20;
    RwMatrixRotate(&v_70, &stru_3D9730, unk_530, rwCOMBINEPRECONCAT);
    v_74 = &v_70.at;
#ifdef CODFH_SP // SP 0xC1D40 searches the dword_4B86A0 list only
    {
        v_7C = dword_4B86A0;
#else
    for (v_78 = 0; v_78 < 2; v_78++)
    {
        v_7C = 0;
        if (v_78 == 0)
            v_7C = dword_4B86A0;
        else
            v_7C = dword_4B8690;
#endif
        while (v_7C)
        {
            v_80 = (RwV3d *)v_7C->vf_0C4();
            v_8C.x = v_80->x - v_18->x;
            v_8C.y = v_80->y - (v_18->y - v_10);
            v_8C.z = v_80->z - v_18->z;
            v_90 = v_8C.x * v_8C.x + v_8C.y * v_8C.y + v_8C.z * v_8C.z;
            v_94 = v_7C->vf_17C();
            if (v_90 < v_C && v_94 < 0.4f)
            {
                v_A0 = v_8C;
                v_A0.y = 0.0f;
                RwV3dNormalize(&v_AC, &v_A0);
                v_B0 = RwV3dDotProductMacro(&v_AC, v_24);
                v_B4 = 1.0f - (1.0f - v_90 / v_C) * 0.050000012f;
                v_C0 = v_8C;
                RwV3dNormalize(&v_AC, &v_C0);
                v_C4 = RwV3dDotProductMacro(&v_AC, v_74);
                v_C8 = 1.0f - (1.0f - v_90 / v_C) * 0.19999999f;
                if (v_B0 > v_B4 && v_C4 > v_C8 && v_90 < v_8)
                {
                    v_8 = v_90;
                    v_14 = (type_3DAFC8 *)v_7C;
                }
            }
            v_7C = v_7C->unk_10;
        }
    }
    return v_14;
}

// match: ?sub_108FF0@type_10F710@@QAEXH@Z @ 0x00108FF0
// sp-match: ?sub_108FF0@type_10F710@@QAEXH@Z @ 0x000C1F60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_108FF0(RwInt32 arg_0)
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (arg_0)
    {
        for (bp_4 = 0; bp_4 <= 22; bp_4++)
        {
            unk_4B9308.sub_EECA0(unk_3D8, bp_4, 1);
        }
        unk_4B9308.sub_EECA0(unk_3D8, 1, 0);
        unk_4B9308.sub_EECA0(unk_3D8, 5, 0);
#ifdef CODFH_SP // SP 0xC1F60: the control is 0x26 there
        unk_4B9308.sub_EECA0(unk_3D8, 0x26, 1);
#else
        unk_4B9308.sub_EECA0(unk_3D8, 0x2A, 1);
#endif
        unk_4B9308.sub_EECA0(unk_3D8, 0xB, 0);
    }
    else
    {
        for (bp_8 = 0; bp_8 <= 22; bp_8++)
        {
            unk_4B9308.sub_EECA0(unk_3D8, bp_8, 0);
        }
#ifdef CODFH_SP // SP 0xC1F60: the control is 0x26 there
        unk_4B9308.sub_EECA0(unk_3D8, 0x26, 0);
#else
        unk_4B9308.sub_EECA0(unk_3D8, 0x2A, 0);
#endif
    }
}

// match: ?sub_1090F0@type_10F710@@QAEXH@Z @ 0x001090F0
// sp-match: ?sub_1090F0@type_10F710@@QAEXH@Z @ 0x000C2020
void type_10F710::sub_1090F0(RwInt32 arg_0)
{
    unk_19D0 = arg_0;
}

// match: ?sub_109110@type_10F710@@QAEXMMM@Z @ 0x00109110
// sp-match: ?sub_109110@type_10F710@@QAEXMMM@Z @ 0x000C2030
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_109110(RwReal arg_0, RwReal arg_4, RwReal arg_8)
{
    RwInt32 t20;
    RwReal l1C;
    RwInt32 m_18;
    RwReal ebp_14;
    RwInt32 lv_10;
    RwInt32 slot_C;
    type_712B0_10F710 *bp_8;
    type_4C19C0 *bp_4;

    ebp_14 = unk_4B9308.sub_EE8F0(unk_3D8, 0);
    t20 = 1;
    bp_8 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_8 && bp_8->vf_008() != 1)
    {
        bp_8 = 0;
    }
    if (unk_2148 != 0.0f)
    {
        ebp_14 = unk_2150;
    }
    if ((dword_4B86F8 >> 6) & 1)
    {
        ebp_14 = 0.0f;
    }
    l1C = unk_4B9308.sub_EE8F0(unk_3D8, 3);
    if (unk_1A04 == 2
        && (l1C != 0.0f || unk_1B1C || unk_1A48[unk_1AE4]->unk_12 || unk_1A48[unk_1AE4]->unk_230
            || unk_1A48[unk_1AE4]->unk_228 || unk_1A48[unk_1AE4]->unk_22C || !unk_1A48[unk_1AE4]->unk_13
            || unk_1A48[unk_1AE4]->unk_11))
    {
        unk_19D8 = 0;
        t20 = 0;
    }
    if (ebp_14 != 0.0f && t20 && !unk_1A48[unk_1AE4]->unk_230)
    {
        if (ebp_14 > 0.0f)
        {
            unk_C0.z = arg_0 * ebp_14;
        }
        else
        {
            unk_C0.z = arg_4 * ebp_14;
        }
        if (unk_19F0 > 0.0f && ebp_14 > 0.0f)
        {
            unk_C0.z = 0.0f;
            return;
        }
        if (ebp_14 < 0.0f)
        {
            ebp_14 = -ebp_14;
        }
        if (unk_1A48[unk_1AE4]->sub_11D690() < ebp_14)
        {
            unk_1A48[unk_1AE4]->sub_11D650(ebp_14);
        }
        if (unk_1A04 == 2 && unk_1B04)
        {
            unk_1B04 = 0;
            unk_1B08 = 1;
            dword_4B9190->sub_DEB80(0);
            unk_1A48[unk_1AE4]->unk_298 -= 1.0f;
        }
    }
    else
    {
        unk_C0.z = 0.0f;
    }
    bp_4 = unk_1A48[unk_1AE4]->unk_448;
    m_18 = 0;
    if (unk_1A04 == 2 && t20)
    {
        if (ebp_14 > 0.0f)
        {
            if (unk_19D8 != 1 && unk_19D8 != 3)
            {
                m_18 = bp_4->unk_48;
                unk_19D8 = 3;
            }
            else
            {
                unk_19D8 = 1;
            }
        }
        else if (ebp_14 < 0.0f)
        {
            if (unk_19D8 != 2 && unk_19D8 != 4)
            {
                m_18 = bp_4->unk_48;
                unk_19D8 = 4;
            }
            else
            {
                unk_19D8 = 2;
            }
        }
        else
        {
            if (unk_19D8 != 0 && unk_19D8 != 5)
            {
                m_18 = bp_4->unk_44;
                unk_19D8 = 5;
            }
            else
            {
                unk_19D8 = 0;
            }
        }
        if (m_18)
        {
            if (sub_77B70(m_18, (void **)(&lv_10), (void **)(&slot_C)))
            {
                unk_284->sub_794C0(0.0f);
                unk_284->sub_796A0((RtAnimAnimation *)lv_10, m_18, 0, (type_783F0 *)slot_C, 0.0f, 1.0f, 1.0f);
            }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
            else if (m_18)
            {
                sub_19A750("WARNING: Missing start anim: 0x%x", m_18);
            }
#endif
        }
    }
    else if (unk_19D8)
    {
        if (sub_77B70(bp_4->unk_28, (void **)(&lv_10), (void **)(&slot_C)))
        {
            unk_284->sub_794C0(0.0f);
            unk_284->sub_796A0((RtAnimAnimation *)lv_10, bp_4->unk_28, 0, (type_783F0 *)slot_C, 0.0f, 1.0f,
                               1.0f);
        }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        else if (bp_4->unk_28)
        {
            sub_19A750("WARNING: Missing idle anim: 0x%x", bp_4->unk_28);
        }
#endif
        unk_19D8 = 0;
    }
}

// match: ?sub_109660@type_10F710@@QAEXMM@Z @ 0x00109660
// sp-match: ?sub_109660@type_10F710@@QAEXMM@Z @ 0x000C23D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_109660(RwReal arg_0, RwReal arg_4)
{
    RwInt32 bp_8;
    RwReal bp_4;

    bp_8 = 1;
    if (unk_1A04 == 2
        && (unk_1B1C || unk_1A48[unk_1AE4]->unk_12 || unk_1A48[unk_1AE4]->unk_230 || unk_1A48[unk_1AE4]->unk_228
            || unk_1A48[unk_1AE4]->unk_22C))
    {
        bp_8 = 0;
    }
    bp_4 = unk_4B9308.sub_EE8F0(unk_3D8, 2);
    if ((dword_4B86F8 >> 6) & 1)
    {
        bp_4 = 0.0f;
    }
    if (bp_4 != 0.0f && bp_8)
    {
        unk_C0.x = arg_0 * bp_4;
        if (bp_4 < 0.0f)
        {
            bp_4 = -bp_4;
        }
        if (unk_1A48[unk_1AE4]->sub_11D690() < bp_4)
        {
            unk_1A48[unk_1AE4]->sub_11D650(bp_4);
        }
    }
}

// match: ?sub_1097C0@type_10F710@@QAEXMM@Z @ 0x001097C0
// sp-match: ?sub_1097C0@type_10F710@@QAEXMM@Z @ 0x000C24C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_1097C0(RwReal arg_0, RwReal arg_4)
{
    RwV3d r34;
    RwMatrix *q28;
    RwV3d frm_24;
    RwReal m_18;
    RwCamera *ebp_14;
    type_712B0_10F710 *lv_10;
    RwInt32 slot_C;
    type_3D3548 *bp_8;
    RwReal bp_4;

    bp_8 = unk_1A34.sub_D4910();
    if (!bp_8)
    {
        return;
    }
    slot_C = 1;
    if (unk_1A04 == 2
        && (unk_1B1C || unk_1A48[unk_1AE4]->unk_12 || unk_1A48[unk_1AE4]->unk_230 || unk_1A48[unk_1AE4]->unk_228
            || unk_1A48[unk_1AE4]->unk_22C))
    {
        slot_C = 0;
    }
    bp_4 = unk_4B9308.sub_EE8F0(unk_3D8, 2);
    if ((dword_4B86F8 >> 6) & 1)
    {
        bp_4 = 0.0f;
    }
    if (bp_4 != 0.0f && slot_C)
    {
        ebp_14 = (RwCamera *)dword_4E5C74;
        q28 = RwFrameGetMatrix(RwCameraGetFrame(ebp_14));
        frm_24 = *RwMatrixGetAt(q28);
        frm_24.y = 0.0f;
        RwV3dNormalize(&frm_24, &frm_24);
        RwV3dSub(&r34, &unk_474, (RwV3d *)vf_0C4());
        r34.y = 0.0f;
        RwV3dNormalize(&r34, &r34);
        m_18 = sub_141240(&frm_24, &r34);
        if (m_18 > 180.0f)
        {
            m_18 = m_18 - 360.0f;
        }
        lv_10 = (type_712B0_10F710 *)unk_344.unk_08;
        if (lv_10 && lv_10->vf_008() != 1)
        {
            lv_10 = 0;
        }
        if (lv_10->unk_348)
        {
            unk_1A38 = m_18;
            if (unk_1A38 > lv_10->unk_350)
            {
                unk_1A38 = lv_10->unk_350;
            }
            if (-lv_10->unk_350 > unk_1A38)
            {
                unk_1A38 = -lv_10->unk_350;
            }
            unk_C0.x = arg_0 * bp_4;
        }
        else
        {
            sub_109660(arg_0, arg_4);
        }
        if (bp_4 < 0.0f)
        {
            bp_4 = -bp_4;
        }
        if (unk_1A48[unk_1AE4]->sub_11D690() < bp_4)
        {
            unk_1A48[unk_1AE4]->sub_11D650(bp_4);
        }
    }
}

inline RwReal clamp_real(RwReal arg_0, RwReal arg_4, RwReal arg_8);
#ifdef CODFH_SP
// Single player only (SP 0xBF9B0): half the time step kept within 0.5 and 4;
// an inline that VC keeps out of line in vf_040 and sub_109AE0.
// sp-match: ?sp_sub_BF9B0@@YAMM@Z @ 0x000BF9B0
inline RwReal sp_sub_BF9B0(RwReal arg_0)
{
    return clamp_real(arg_0 * 0.5f, 0.5f, 4.0f);
}
#endif
// match: ?sub_109AE0@type_10F710@@QAEXMM@Z @ 0x00109AE0
// sp-match: ?sub_109AE0@type_10F710@@QAEXMM@Z @ 0x000C9D90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_109AE0(RwReal arg_0, RwReal arg_4)
{
    RwReal slot_58;
    RwReal l54;
    RwReal loc50;
    RwInt32 x4C;
    RwReal w48;
    type_4C19C0 *loc44;
    RwReal fp_40;
    RwInt32 ebp_3C;
    type_712B0_10F710 *lcl_38;
    RwReal r34;
    RwReal lv_30;
    type_4E1B70 *fp_2C;
    type_3DC9B0 *q28;
    type_3DBC78 *frm_24;
    type_3DBC78 *t20;
    RwReal l1C;
    RwReal m_18;
    RwInt32 ebp_14;
    RwReal lv_10;
    RwReal slot_C;
    type_3DD948 *bp_8;
    type_712B0_10F710 *bp_4;

    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    ebp_14 = 1;
    m_18 = 0.0f;
    l1C = 0.0f;
    lv_10 = 1.0f;
    if (unk_1A04 == 2 && (unk_1A48[unk_1AE4]->unk_228 || unk_1A48[unk_1AE4]->unk_22C))
    {
        ebp_14 = 0;
    }
    slot_C = unk_4B9308.sub_EE8F0(unk_3D8, 1);
    if (unk_2148 != 0.0f)
    {
        slot_C = unk_214C;
    }
    if ((dword_4B86F8 >> 6) & 1)
    {
        slot_C = 0.0f;
    }
    bp_8 = (type_3DD948 *)unk_2110.sub_D4910();
    if (bp_8->get_unk_414() == 1)
    {
        unk_E8 = 0.0f;
        t20 = (type_3DBC78 *)unk_2180.sub_D4910();
        if (t20)
        {
            t20->vf_294(0.0f, 1.0f);
            t20->vf_298(0.0f, 1.0f);
        }
    }
    else if (unk_19D0 == 5)
    {
        unk_3EC = 0.0f;
        frm_24 = (type_3DBC78 *)unk_2180.sub_D4910();
        if (frm_24)
        {
            frm_24->vf_294(slot_C, arg_0);
        }
        unk_E8 = 0.0f;
    }
    else if (unk_19D0 == 7)
    {
        q28 = (type_3DC9B0 *)unk_210C.sub_D4910();
        fp_2C = sub_166990(q28->unk_3B0);
        if (q28)
        {
            lv_30 = fp_2C->unk_B8_r;
            lcl_38 = (type_712B0_10F710 *)q28->get_unk_34C();
            if (q28->unk_488)
            {
                lv_30 = fp_2C->unk_BC_r;
            }
            if (q28->unk_488)
            {
                if (q28->unk_498 == 1)
                {
                    if (lcl_38 && lcl_38->unk_1E4[0] != -1.0f)
                    {
                        lv_30 = lcl_38->unk_1E4[0];
                    }
                }
                else if (q28->unk_498 == 2)
                {
                    if (lcl_38 && lcl_38->unk_170[1] != -1.0f)
                    {
                        lv_30 = lcl_38->unk_170[1];
                    }
                }
            }
            else if (q28->unk_498 == 1)
            {
                if (lcl_38 && lcl_38->unk_1E0 != -1.0f)
                {
                    lv_30 = lcl_38->unk_1E0;
                }
            }
            else if (q28->unk_498 == 2)
            {
                if (lcl_38 && lcl_38->unk_170[0] != -1.0f)
                {
                    lv_30 = lcl_38->unk_170[0];
                }
            }
            if ((slot_C < 0.0f ? -slot_C : slot_C) < bp_4->unk_15C)
            {
                slot_C = 0.0f;
            }
            else
            {
                slot_C = (slot_C - bp_4->unk_15C) / (1.0f - bp_4->unk_15C);
            }
            m_18 = arg_0 * slot_C * (arg_4 * 0.5f);
            m_18 = m_18 * unk_1A30;
            unk_3F4 = unk_3F4 * unk_1A30;
            unk_3EC = unk_3EC * unk_1A30;
            if (m_18 == 0.0f)
            {
                for (ebp_3C = 0; ebp_3C < arg_4 * 0.5f; ebp_3C++)
                {
                    unk_3EC = unk_3EC * unk_134.y;
                }
                unk_3F4 = 0.0f;
            }
            else
            {
                sub_112DA0(&unk_3EC, m_18, &unk_3F4, bp_4->unk_22C, bp_4->unk_230, lv_30, arg_4);
            }
            q28->unk_3BC += unk_3EC;
#ifdef CODFH_WIN32
            // (the local player's mounted gun: the mouse's turn straight onto it, as on foot)
            if (unk_3D8 == 0)
                q28->unk_3BC += port_mouse_yaw();
#endif
            r34 = q28->sub_16A890();
            if (r34 != 180.0f)
            {
                if (-r34 > q28->unk_3BC)
                {
                    q28->unk_3BC = -r34;
                }
                else if (q28->unk_3BC > r34)
                {
                    q28->unk_3BC = r34;
                }
            }
        }
    }
    else if (ebp_14)
    {
        loc44 = unk_1A48[unk_1AE4]->unk_448;
        if (unk_1B04)
        {
            slot_C = slot_C * loc44->unk_3BC_r[unk_1A04];
        }
        if (unk_46C)
        {
            if (unk_470 < bp_4->unk_1CC)
            {
                unk_470 += bp_4->unk_344;
                if (unk_470 > bp_4->unk_1CC)
                {
                    unk_470 = bp_4->unk_1CC;
                }
            }
            m_18 = slot_C * unk_470;
        }
        else
        {
            w48 = unk_1A30;
            lv_10 = bp_4->unk_310 * bp_4->unk_360;
            m_18 = arg_0 * slot_C * w48;
            unk_3F4 *= w48;
            unk_3EC *= w48;
            l1C = unk_1A38;
            unk_400 *= lv_10;
            unk_3FC *= lv_10;
        }
#ifdef CODFH_SP // SP 0xC9D90 calls the out-of-line sp_sub_BF9B0
        fp_40 = sp_sub_BF9B0(arg_4);
#else
        fp_40 = clamp_real(arg_4 * 0.5f, 0.5f, 4.0f);
#endif
        m_18 = m_18 * fp_40;
        if (m_18 == 0.0f)
        {
            for (x4C = 0; x4C < arg_4 * 0.5f; x4C++)
            {
                unk_3EC = unk_3EC * unk_134.y;
            }
            unk_3F4 = 0.0f;
        }
        else
        {
            sub_112DA0(&unk_3EC, m_18, &unk_3F4, bp_4->unk_22C, bp_4->unk_230, flt_429708, arg_4);
        }
        if (l1C == 0.0f)
        {
            unk_400 = 0.0f;
        }
        else
        {
            sub_112DA0(&unk_3FC, l1C, &unk_400, bp_4->unk_354, bp_4->unk_358, flt_429708, arg_4);
        }
        if (unk_1A48[unk_1AE4]->unk_230)
        {
#ifdef CODFH_SP // shape: block-scoped, so /O2 puts them in the dead argument slots (SP 0xC9D90's frame)
            RwReal a;
            RwReal b;

            a = unk_548;
            a = a + unk_3EC;
            b = -loc44->unk_E8;
            a = sub_22C20(a, b, loc44->unk_E8);
            l54 = a - unk_548;
#else
            loc50 = unk_548;
            loc50 = loc50 + unk_3EC;
            slot_58 = -loc44->unk_E8;
            loc50 = sub_22C20(loc50, slot_58, loc44->unk_E8);
            l54 = loc50 - unk_548;
#endif
            unk_3EC = l54;
            unk_548 += l54;
        }
        unk_E8 = unk_3EC + unk_3FC;
#ifdef CODFH_WIN32
        // (the local player's: the mouse's turn, added to the stick's)
        if (unk_3D8 == 0)
            unk_E8 += port_mouse_yaw();
#endif
        sub_19B650(&unk_E4);
    }
}

// match: ?sub_10A330@type_10F710@@QAEXMM@Z @ 0x0010A330
// sp-match: ?sub_10A330@type_10F710@@QAEXMM@Z @ 0x000CA3A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10A330(RwReal arg_0, RwReal arg_4)
{
    RwReal loc50;
    RwReal x4C;
    RwReal w48;
    RwReal loc44;
    RwReal fp_40;
    RwInt32 ebp_3C;
    type_4C19C0 *lcl_38;
    RwReal r34;
    RwInt32 lv_30;
    RwReal fp_2C;
    type_712B0_10F710 *q28;
    RwReal frm_24;
    RwReal t20;
    type_4E1B70 *l1C;
    type_3DC9B0 *m_18;
    type_3DBC78 *ebp_14;
    RwInt32 lv_10;
    RwReal slot_C;
    type_3DD948 *bp_8;
    type_712B0_10F710 *bp_4;

    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    lv_10 = 1;
    if (unk_1A04 == 2 && (unk_1A48[unk_1AE4]->unk_228 || unk_1A48[unk_1AE4]->unk_22C))
    {
        lv_10 = 0;
    }
    slot_C = unk_4B9308.sub_EE8F0(unk_3D8, 5);
    if ((dword_4B86F8 >> 6) & 1)
    {
        slot_C = 0.0f;
    }
    if (dword_4F28F0->get_unk_22())
    {
        slot_C = slot_C * -1.0f;
    }
    if (unk_2148 != 0.0f)
    {
        slot_C = unk_2158;
    }
    bp_8 = (type_3DD948 *)unk_2110.sub_D4910();
    if (bp_8->get_unk_414() == 1)
    {
        return;
    }
    if (unk_19D0 == 5)
    {
        ebp_14 = (type_3DBC78 *)unk_2180.sub_D4910();
        if (ebp_14)
        {
            ebp_14->vf_298(slot_C, arg_0);
        }
        unk_530 = 0.0f;
    }
    else if (unk_19D0 == 7)
    {
        m_18 = (type_3DC9B0 *)unk_210C.sub_D4910();
        l1C = sub_166990(m_18->unk_3B0);
        if (m_18)
        {
            t20 = l1C->unk_B8_r;
            q28 = (type_712B0_10F710 *)m_18->get_unk_34C();
            if (m_18->unk_488)
            {
                t20 = l1C->unk_BC_r;
            }
            if (m_18->unk_488)
            {
                if (m_18->unk_498 == 1)
                {
                    if (q28 && q28->unk_1E4[0] != -1.0f)
                    {
                        t20 = q28->unk_1E4[0];
                    }
                }
                else if (m_18->unk_498 == 2)
                {
                    if (q28 && q28->unk_170[1] != -1.0f)
                    {
                        t20 = q28->unk_170[1];
                    }
                }
            }
            else if (m_18->unk_498 == 1)
            {
                if (q28 && q28->unk_1E0 != -1.0f)
                {
                    t20 = q28->unk_1E0;
                }
            }
            else if (m_18->unk_498 == 2)
            {
                if (q28 && q28->unk_170[0] != -1.0f)
                {
                    t20 = q28->unk_170[0];
                }
            }
            if ((slot_C < 0.0f ? -slot_C : slot_C) < bp_4->unk_15C)
            {
                slot_C = 0.0f;
            }
            else
            {
                slot_C = (slot_C - bp_4->unk_15C) / (1.0f - bp_4->unk_15C);
            }
            fp_2C = arg_0 * slot_C * (arg_4 * 0.5f);
            if (fp_2C == 0.0f)
            {
                for (lv_30 = 0; lv_30 < arg_4 * 0.5f; lv_30++)
                {
                    unk_3F0 = unk_3F0 * unk_134.z;
                }
                unk_3F8 = 0.0f;
            }
            else
            {
                sub_112DA0(&unk_3F0, fp_2C, &unk_3F8, bp_4->unk_22C, bp_4->unk_230, t20, arg_4);
            }
            m_18->unk_3B8 += unk_3F0;
#ifdef CODFH_WIN32
            if (unk_3D8 == 0)
                m_18->unk_3B8 += port_mouse_pitch();
#endif
            frm_24 = m_18->sub_16A790();
            if (frm_24 != 180.0f)
            {
                if (-frm_24 > m_18->unk_3B8)
                {
                    m_18->unk_3B8 = -frm_24;
                }
                else if (m_18->unk_3B8 > frm_24)
                {
                    m_18->unk_3B8 = frm_24;
                }
            }
        }
    }
    else if (lv_10)
    {
        lcl_38 = unk_1A48[unk_1AE4]->unk_448;
        if (unk_1B04)
        {
            slot_C = slot_C * lcl_38->unk_3BC_r[unk_1A04];
        }
        else if ((slot_C < 0.0f ? -slot_C : slot_C) < bp_4->unk_15C)
        {
            slot_C = 0.0f;
        }
        else
        {
            slot_C = (slot_C - bp_4->unk_15C) / (1.0f - bp_4->unk_15C);
        }
        r34 = arg_0 * slot_C * (arg_4 * 0.5f);
        if (r34 == 0.0f)
        {
            for (ebp_3C = 0; ebp_3C < arg_4 * 0.5f; ebp_3C++)
            {
                unk_3F0 = unk_3F0 * unk_134.z;
            }
            unk_3F8 = 0.0f;
        }
        else
        {
            sub_112DA0(&unk_3F0, r34, &unk_3F8, bp_4->unk_22C, bp_4->unk_230, flt_429708, arg_4);
        }
        if (unk_1A48[unk_1AE4]->unk_230)
        {
#ifdef CODFH_SP // shape: block-scoped, so /O2 puts them in the dead argument slots (SP 0xCA3A0's frame)
            RwReal a;
            RwReal b;

            a = unk_544;
            a = a + unk_3F0;
            b = -lcl_38->unk_E4;
            a = sub_22C20(a, b, lcl_38->unk_E4);
            fp_40 = a - unk_544;
#else
            loc44 = unk_544;
            loc44 = loc44 + unk_3F0;
            w48 = -lcl_38->unk_E4;
            loc44 = sub_22C20(loc44, w48, lcl_38->unk_E4);
            fp_40 = loc44 - unk_544;
#endif
            unk_3F0 = fp_40;
            unk_544 += fp_40;
        }
        unk_530 += unk_3F0;
#ifdef CODFH_WIN32
        if (unk_3D8 == 0)
            unk_530 += port_mouse_pitch();
#endif
#ifdef CODFH_SP // shape: the bounds in a block of their own (SP 0xCA3A0's frame)
        {
            RwReal hi;
            RwReal lo;

            hi = 89.0f;
            lo = -89.0f;
            unk_530 = sub_22C20(unk_530, lo, hi);
        }
#else
        x4C = 89.0f;
        loc50 = -89.0f;
        unk_530 = sub_22C20(unk_530, loc50, x4C);
#endif
    }
}

// match: ?sub_10A9D0@type_10F710@@QAEXM@Z @ 0x0010A9D0
// sp-match: ?sub_10A9D0@type_10F710@@QAEXM@Z @ 0x000CA8D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10A9D0(RwReal arg_0)
{
    type_4C19C0 *m_18;
    RwReal ebp_14;
    type_4E5E40 *lv_10;
    RwReal slot_C;
    type_4E5E40_08 *bp_8;
    type_712B0_10F710 *bp_4;

    lv_10 = &dword_4E5E40;
    bp_8 = lv_10->unk_08;
    ebp_14 = 1.0f;
    m_18 = unk_1A48[unk_1AE4]->unk_448;
    if (unk_1B04)
    {
        ebp_14 = m_18->unk_47C_r[unk_1A04];
    }
    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    if (!bp_4)
    {
        return;
    }
    unk_28 |= 0x3C;
    unk_10C = bp_4->unk_184;
    unk_134 = bp_4->unk_19C;
    sub_109110(ebp_14 * bp_4->unk_164[unk_1A04], ebp_14 * bp_4->unk_170[unk_1A04], arg_0);
    if (unk_454)
    {
        sub_1097C0(ebp_14 * unk_480, arg_0);
        sub_109AE0(bp_4->unk_37C, arg_0);
        sub_10A330(bp_4->unk_154, arg_0);
    }
    else
    {
        sub_109660(ebp_14 * bp_4->unk_1E4[unk_1A04], arg_0);
        sub_10A330(bp_4->unk_154, arg_0);
        sub_109AE0(bp_4->unk_1B4, arg_0);
    }
    unk_428 -= arg_0 * 0.5f;
    if (unk_428 < 0.0f)
    {
        unk_428 = 0.0f;
    }
    if (!((unk_28 >> 1) & 1))
    {
        sub_1090F0(2);
    }
    else if (unk_428 <= 0.0f)
    {
        slot_C = unk_4B9308.sub_EE8F0(unk_3D8, 4);
        if (slot_C != 0.0f && slot_C > 0.0f && unk_1A04 == 0)
        {
            if (unk_1A04 == 1 || unk_1A04 == 2)
            {
                if (unk_1A48[unk_1AE4]->sub_1175D0())
                {
                    sub_104480(1.0f, 0.0f);
                }
            }
            else
            {
                unk_C0.y = bp_4->unk_1D8;
            }
            unk_19D4 = 0;
            unk_28 &= ~2;
            sub_1090F0(1);
            unk_1C0.sub_8AA70(&dword_4B1B28, bp_8[unk_294].unk_00, this, 0, sub_CD550(), 0, 0);
        }
    }
    slot_C = unk_4B9308.sub_EE8F0(unk_3D8, 0xF);
    if (slot_C != 0.0f)
    {
        sub_145970(this, (type_145B40 *)(&unk_248));
    }
    sub_10C370(arg_0);
}

// match: ?sub_10AD70@type_10F710@@QAEXM@Z @ 0x0010AD70
// sp-match: ?sub_10AD70@type_10F710@@QAEXM@Z @ 0x000CAB50
void type_10F710::sub_10AD70(RwReal arg_0)
{
    type_712B0_10F710 *var_4;

    var_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (var_4 && var_4->vf_008() != 1)
    {
        var_4 = 0;
    }
    if (!var_4)
    {
        return;
    }
    unk_28 |= 0x3C;
    unk_10C = var_4->unk_190;
    unk_134 = var_4->unk_1A8;
    unk_19D4++;
    sub_109110(var_4->unk_17C, var_4->unk_180, arg_0);
    sub_109660(var_4->unk_1F0, arg_0);
    sub_10A330(var_4->unk_154, arg_0);
    sub_109AE0(var_4->unk_1B8, arg_0);
    if ((unk_28 >> 1) & 1)
    {
        sub_1090F0(3);
    }
    unk_1A48[unk_1AE4]->sub_11D650(1.0f);
}

// match: ?sub_10AEB0@type_10F710@@QAEXM@Z @ 0x0010AEB0
// sp-match: ?sub_10AEB0@type_10F710@@QAEXM@Z @ 0x000CAC30
void type_10F710::sub_10AEB0(RwReal arg_0)
{
    type_712B0_10F710 *var_4;

    var_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (var_4 && var_4->vf_008() != 1)
    {
        var_4 = 0;
    }
    if (!var_4)
    {
        return;
    }
    if (!unk_215C)
    {
        unk_28 |= 0x3C;
    }
    unk_10C = var_4->unk_190;
    unk_134 = var_4->unk_1A8;
    sub_109110(var_4->unk_17C, var_4->unk_180, arg_0);
    sub_109660(var_4->unk_1F0, arg_0);
    sub_10A330(var_4->unk_154, arg_0);
    sub_109AE0(var_4->unk_1B8, arg_0);
    if ((unk_28 >> 1) & 1)
    {
        sub_1090F0(3);
    }
}

// match: ?sub_10AFD0@type_10F710@@QAEXM@Z @ 0x0010AFD0
// sp-match: ?sub_10AFD0@type_10F710@@QAEXM@Z @ 0x000CAD00
void type_10F710::sub_10AFD0(RwReal arg_0)
{
    type_712B0_10F710 *var_4;

    var_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (var_4 && var_4->vf_008() != 1)
    {
        var_4 = 0;
    }
    if (!var_4)
    {
        return;
    }
    unk_28 |= 0x3C;
    unk_10C = var_4->unk_184;
    unk_134 = var_4->unk_19C;
    sub_109110(var_4->unk_164[unk_1A04], var_4->unk_170[unk_1A04], arg_0);
    sub_109660(var_4->unk_1E4[unk_1A04], arg_0);
    sub_10A330(var_4->unk_154, arg_0);
    sub_109AE0(var_4->unk_1B4, arg_0);
    if ((unk_28 >> 1) & 1)
    {
        if (unk_2148 != 0.0f)
        {
            sub_1090F0(0xE);
        }
        else
        {
            sub_1090F0(0);
        }
    }
}

// match: ?sub_10B120@type_10F710@@QAEXM@Z @ 0x0010B120
// sp-match: ?sub_10B120@type_10F710@@QAEXM@Z @ 0x000CADF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10B120(RwReal arg_0)
{
    type_3DBC78 *ebp_14;
    RwReal lv_10;
    RwReal slot_C;
    RwReal bp_8;
    type_712B0_10F710 *bp_4;

    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    if (!bp_4)
    {
        return;
    }
    ebp_14 = (type_3DBC78 *)unk_2180.sub_D4910();
    unk_28 &= 0xFFFFFF41;
    unk_28 |= 0x40;
    set_v3d(&unk_D8_v, 0.0f, 0.0f, 0.0f);
    lv_10 = unk_4B9308.sub_EE8F0(unk_3D8, 0);
    bp_8 = unk_4B9308.sub_EE8F0(unk_3D8, 2);
    if ((dword_4B86F8 >> 6) & 1)
    {
        lv_10 = 0.0f;
        bp_8 = 0.0f;
    }
    ebp_14->vf_280(lv_10);
    ebp_14->vf_28C(bp_8);
    sub_10A330(bp_4->unk_154, arg_0);
    sub_109AE0(bp_4->unk_1B4, arg_0);
    slot_C = unk_4B9308.sub_EE8F0(unk_3D8, 0xF);
    if (slot_C != 0.0f)
    {
        sub_145970(this, (type_145B40 *)(&unk_248));
    }
    slot_C = unk_4B9308.sub_EE8F0(unk_3D8, 0x12);
    if (slot_C != 0.0f)
    {
        ebp_14->vf_2B0();
    }
    dword_4D51C0.sub_15B720();
}

// match: ?sub_10B2E0@type_10F710@@QAEXM@Z @ 0x0010B2E0
// sp-match: ?sub_10B2E0@type_10F710@@QAEXM@Z @ 0x000CAF40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10B2E0(RwReal arg_0)
{
    RwReal slot_C;
    type_712B0_10F710 *bp_8;
    RwFrame *bp_4;

    bp_8 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_8 && bp_8->vf_008() != 1)
    {
        bp_8 = 0;
    }
    if (!bp_8)
    {
        return;
    }
    unk_28 &= 0xFFFFFF41;
    unk_28 |= 0x40;
    set_v3d(&unk_D8_v, 0.0f, 0.0f, 0.0f);
    sub_10A330(bp_8->unk_154, arg_0);
    sub_109AE0(bp_8->unk_1B4, arg_0);
    bp_4 = unk_338.unk_08;
    if (!bp_4)
    {
        return;
    }
    RwFrameRotate(bp_4, &stru_3D973C, unk_E8, rwCOMBINEPRECONCAT);
    slot_C = unk_4B9308.sub_EE8F0(unk_3D8, 0xF);
    if (slot_C != 0.0f)
    {
        sub_145970(this, (type_145B40 *)(&unk_248));
    }
}

// match: ?sub_10B410@type_10F710@@QAEXM@Z @ 0x0010B410
// sp-match: ?sub_10B410@type_10F710@@QAEXM@Z @ 0x000CB010
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10B410(RwReal arg_0)
{
    type_3DC9B0 *slot_C;
    RwReal bp_8;
    type_712B0_10F710 *bp_4;

    slot_C = (type_3DC9B0 *)unk_210C.sub_D4910();
    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    if (!bp_4)
    {
        return;
    }
    unk_28 &= 0xFFFFFF45;
    unk_28 |= 0x40;
    set_v3d(&unk_D8_v, 0.0f, 0.0f, 0.0f);
    sub_10A330(bp_4->unk_154, arg_0);
    sub_109AE0(bp_4->unk_1B4, arg_0);
    bp_8 = unk_4B9308.sub_EE8F0(unk_3D8, 6);
    if ((dword_4B86F8 >> 6) & 1)
    {
        bp_8 = 0.0f;
    }
    if (bp_8 != 0.0f)
    {
        if (slot_C && !slot_C->unk_488)
        {
            slot_C->sub_16A1D0(this, 1);
        }
    }
    else if (slot_C && slot_C->unk_488)
    {
        slot_C->sub_16A1D0(this, 0);
    }
}

// The vehicle seat state (state 12): it looks and turns by its trigger's
// speeds, and when it is in a vehicle's seat its frame is set to the seat's
// matrix (sub_EC2D0 on the vehicle's clump), raised by its height on an
// animated entity plus 35.
// match: ?sub_10B560@type_10F710@@QAEXM@Z @ 0x0010B560
// sp-match: ?sub_10B560@type_10F710@@QAEXM@Z @ 0x000CB100
void type_10F710::sub_10B560(RwReal arg_0)
{
    type_712B0_10F710 *v_8;
    type_3D3548 *v_10;
    RpClump *v_14;
    RwMatrix v_60;
    RwFrame *v_6C;

    v_8 = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_8 && v_8->vf_008() != 1)
    {
        v_8 = 0;
    }
    if (!v_8)
    {
        return;
    }
    unk_28 &= 0xFFFFFF51;
    unk_28 |= 0x50;
    zero_v3d(&unk_D8_v);
    sub_10A330(v_8->unk_154, arg_0);
    sub_109AE0(v_8->unk_1B4, arg_0);
    v_10 = unk_2180.sub_D4910();
    if (v_10 && unk_2184)
    {
        v_14 = v_10->unk_25C.unk_08;
        if (sub_EC2D0(v_14, (RwInt32)&v_60, unk_2184, 0, 1))
        {
            v_60.pos.y += ((type_712B0_10F710 *)unk_344.get_unk_08())->unk_148 + 35.0f;
            v_6C = unk_338.get_unk_08();
            RwFrameTransform(v_6C, &v_60, rwCOMBINEREPLACE);
            RwFrameUpdateObjects(v_6C);
            unk_160.y = unk_178.y;
        }
    }
}

// match: ?sub_10B6F0@type_10F710@@QAEXM@Z @ 0x0010B6F0
// sp-match: ?sub_10B6F0@type_10F710@@QAEXM@Z @ 0x000C2720
void type_10F710::sub_10B6F0(RwReal arg_0)
{
    type_712B0_10F710 *var_4;

    var_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (var_4 && var_4->vf_008() != 1)
    {
        var_4 = 0;
    }
    if (!var_4)
    {
        return;
    }
    if (!unk_19F8)
    {
        unk_19F8 = 1;
    }
    unk_10C = var_4->unk_184;
    unk_134 = var_4->unk_19C;
}

// match: ?sub_10B790@type_10F710@@QAEXM@Z @ 0x0010B790
// sp-match: ?sub_10B790@type_10F710@@QAEXM@Z @ 0x000C2790
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10B790(RwReal arg_0)
{
    RwInt32 bp_8;
    type_712B0_10F710 *bp_4;

    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    if (!bp_4)
    {
        return;
    }
    if (!unk_19F8)
    {
        if (unk_1B2C)
        {
            // Only a type_3DA5A0 has the field; the image stores it on any.
            ((type_3DA5A0 *)unk_1A48[unk_1AE4])->unk_470 = 0;
            unk_1A48[unk_1AE4]->sub_117370();
            bp_8 = unk_1AF0;
            unk_1AE4 = bp_8;
            unk_1A48[unk_1AE4]->sub_1170B0(1, 1);
            unk_1B2C = 0;
        }
        unk_1A48[unk_1AE4]->vf_028();
        unk_19F8 = 1;
        dword_44E898 = 0;
        dword_44E8A0 = 1;
        if (unk_1B04)
        {
            sub_1062A0();
        }
    }
    if (!unk_2180.sub_D4910())
    {
        unk_28 |= 0x3C;
    }
    unk_10C = bp_4->unk_184;
    unk_134 = bp_4->unk_19C;
}

// match: ?sub_10B930@type_10F710@@QAEXM@Z @ 0x0010B930
// sp-match: ?sub_10B930@type_10F710@@QAEXM@Z @ 0x000CB200
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10B930(RwReal arg_0)
{
    RwV3d local_38;
    RwV3d stk_2C;
    type_4C19C0 *t20;
    RwReal l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwV3d lv_10;
    type_712B0_10F710 *bp_4;

    m_18 = 1.0f;
    t20 = unk_1A48[unk_1AE4]->unk_448;
    if (unk_1B04)
    {
        m_18 = t20->unk_47C_r[unk_1A04];
    }
    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    if (!bp_4)
    {
        return;
    }
    unk_28 &= 0xFFFFFFC3;
    sub_10A330(bp_4->unk_154, arg_0);
    ebp_14 = unk_4B9308.sub_EE8F0(unk_3D8, 0xF);
    if (ebp_14 != 0.0f)
    {
        unk_19D0 = 0;
    }
    unk_2128->sub_BA990(unk_212C, &stk_2C, 0);
    unk_2128->sub_BA990(unk_212C + 0.001f, &lv_10, 0);
    RwV3dSub(&local_38, &lv_10, &stk_2C);
    unk_212C += 0.001f / (RwReal)sqrt((RwDouble)(l1C = RwV3dDotProduct(&local_38, &local_38)));
    if (unk_212C >= unk_2130)
    {
        vf_0C0(&unk_211C);
        unk_19D0 = 0;
    }
    else
    {
        unk_2128->sub_BA990(unk_212C, &stk_2C, 0);
        vf_0C0(&stk_2C);
    }
}

// The vehicle exit state (state 14): it turns towards the point it leaves
// the vehicle for (unk_213C) and walks there by its trigger's speeds (scaled
// by the weapon's while it is aiming), then, when the transition is
// running (unk_215C), follows it along the blend from unk_2168 by its time;
// it leaves the state (sub_10C290) past 600 or when it is there.
// match: ?sub_10BB30@type_10F710@@QAEXM@Z @ 0x0010BB30
// sp-match: ?sub_10BB30@type_10F710@@QAEXM@Z @ 0x000CD870
void type_10F710::sub_10BB30(RwReal arg_0)
{
    RwReal v_8;
    type_4C19C0 *v_C;
    RwInt32 v_14;
    RwMatrix *v_1C;
    RwV3d v_28;
    type_712B0_10F710 *v_2C;
    RwV3d v_38;
    RwReal v_3C;
    RwV3d v_48;
    RwReal v_4C;
    RwReal v_50;
    RwMatrix v_90;
    RwReal v_94;
    RwReal v_98;
    RwInt32 v_9C;
    RwReal v_A0;
    RwMatrix v_E0;
    RwReal v_E4;
#ifndef CODFH_SP
    RwReal v_E8;
    RwV3d v_F4;
#endif

    v_8 = 1.0f;
    v_C = unk_1A48[unk_1AE4]->unk_448;
    v_14 = unk_2148 == 2.0f;
    v_1C = RwFrameGetMatrix(unk_338.get_unk_08());
    v_28 = v_1C->pos;
    if (unk_1B04)
        v_8 = v_C->unk_47C_r[unk_1A04];
    v_2C = (type_712B0_10F710 *)unk_344.unk_08;
    if (v_2C && v_2C->vf_008() != 1)
    {
        v_2C = 0;
    }
    if (!v_2C)
    {
        return;
    }
    if (unk_215C)
        unk_28 |= 0x10;
    else
        unk_28 |= 0x3C;
    unk_10C = v_2C->unk_184;
    unk_134 = v_2C->unk_19C;
    v_38.x = unk_213C.x - v_28.x;
    v_38.y = unk_213C.y - (v_28.y - unk_48 / 2.0f);
    v_38.z = unk_213C.z - v_28.z;
    v_3C = v_38.x * v_38.x + v_38.y * v_38.y + v_38.z * v_38.z;
    v_38.y = 0.0f;
    RwV3dNormalize(&v_48, &v_38);
    v_4C = RwV3dDotProductMacro(&v_1C->at, &v_48);
    if (v_3C > 25000000.0f)
        v_50 = 0.96f;
    else
        v_50 = 1.0f - (1.0f - v_3C / 5000.0f * 5000.0f) * 0.04000002f;
    if (v_4C < v_50 && !v_14)
    {
        v_90 = *v_1C;
        RwMatrixRotate(&v_90, &stru_3D973C, 0.5f, rwCOMBINEPRECONCAT);
        v_94 = RwV3dDotProductMacro(&v_90.at, &v_48);
        if (v_94 < v_4C)
            unk_214C = -1.0f;
        else
            unk_214C = 1.0f;
        v_98 = 1.0f;
        if (v_4C > 0.9f)
            v_98 = 1.0f - v_4C;
        unk_214C *= v_98;
        sub_109AE0(v_2C->unk_1B4, arg_0);
    }
    else if (v_14 && v_4C < 0.95f)
        unk_2148 = 1.0f;
    else
    {
        unk_2148 = 2.0f;
        unk_215C = 2;
    }
    v_9C = 0;
    v_A0 = 1.0f;
    if (v_4C > 0.9f)
    {
        v_38.x = unk_213C.x - v_28.x;
        v_38.y = unk_213C.y - (v_28.y - unk_48);
        v_38.z = unk_213C.z - v_28.z;
        if (unk_215C)
            v_38.y = -75.0f;
        RwV3dNormalize(&v_48, &v_38);
        v_90 = *v_1C;
        RwMatrixRotate(&v_90, &stru_3D9730, unk_530, rwCOMBINEPRECONCAT);
        v_A0 = RwV3dDotProductMacro(&v_90.at, &v_48);
        if (v_A0 < 0.96f)
        {
            v_E0 = v_90;
            RwMatrixRotate(&v_E0, &stru_3D9730, 0.5f, rwCOMBINEPRECONCAT);
            v_94 = RwV3dDotProductMacro(&v_E0.at, &v_48);
            if (v_94 < v_A0)
                unk_2158 = -1.0f;
            else
                unk_2158 = 1.0f;
            v_E4 = 1.0f;
            if (v_A0 > 0.9f)
                v_E4 = v_A0;
            unk_2158 *= v_E4;
            v_9C = 0;
            if (unk_530 < 30.0f && unk_530 > -30.0f)
                sub_10A330(1.6f, arg_0);
        }
        else
            v_9C = 1;
    }
    if (unk_530 > 30.0f || unk_530 < -30.0f)
    {
        if (unk_530 > 30.0f)
            unk_2158 = -1.0f;
        else
            unk_2158 = 1.0f;
        sub_10A330(1.6f, arg_0);
    }
    if (!unk_215C)
    {
        if (v_3C > 10000.0f)
        {
            if (v_4C > 0.9f)
            {
                unk_2150 = 1.0f;
                sub_109110(v_8 * v_2C->unk_164[unk_1A04], v_8 * v_2C->unk_170[unk_1A04], arg_0);
            }
        }
        else if (v_9C)
            sub_10C290();
    }
    else
    {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares their slots with v_38 and v_48 (SP 0xCD870's frame)
        RwReal v_E8;
        RwV3d v_F4;

#endif
        unk_215C = 2;
        unk_2160 += arg_0;
        v_E8 = unk_2160 / unk_2164;
        if (v_E8 > 1.0f)
        {
            v_E8 = 1.0f;
            unk_2154 = 600.0f;
        }
        sub_112FC0(&v_F4, &unk_2168, &unk_213C, v_E8);
        vf_0C0(&v_F4);
    }
    unk_2154 += arg_0;
    if (unk_2154 > 600.0f)
        sub_10C290();
    if (!((unk_28 >> 1) & 1) && !unk_215C)
        sub_1090F0(2);
    sub_10C370(arg_0);
}

// match: ?sub_10C290@type_10F710@@QAEXXZ @ 0x0010C290
// sp-match: ?sub_10C290@type_10F710@@QAEXXZ @ 0x000CB350
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10C290()
{
    type_4C19C0 *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    unk_2148 = 0.0f;
    unk_214C = 0;
    unk_2150 = 0.0f;
    unk_2154 = 0;
    unk_2158 = 0;
    sub_1090F0(0);
    slot_C = unk_1A48[unk_1AE4]->unk_448;
    sub_10E750(1, 1);
    if (sub_77B70(slot_C->unk_38, (void **)(&bp_8), (void **)(&bp_4)))
    {
        unk_284->sub_794C0(0.0f);
        unk_284->sub_796A0((RtAnimAnimation *)bp_8, slot_C->unk_38, 0, (type_783F0 *)bp_4, 0.0f, 1.0f, 1.0f);
    }
}

// Keeps arg_0 within arg_4 and arg_8: an inline with no address and so no
// database name, named for what it does. Evidence: the player's yaw look
// (sub_109AE0) clamps its time step through a parameter slot, its bounds
// folded in.
inline RwReal clamp_real(RwReal arg_0, RwReal arg_4, RwReal arg_8)
{
    if (arg_0 < arg_4)
    {
        arg_0 = arg_4;
    }
    else if (arg_0 > arg_8)
    {
        arg_0 = arg_8;
    }
    return arg_0;
}

// match: ?sub_10C370@type_10F710@@QAEXM@Z @ 0x0010C370
// sp-match: ?sub_10C370@type_10F710@@QAEXM@Z @ 0x000C28B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10C370(RwReal arg_0)
{
    RwReal l1C;
    RwReal m_18;
    type_4E5E40 *ebp_14;
    RwV3d lv_10;
    type_4E5E40_08 *bp_4;

    lv_10.x = ABS(unk_4B9308.sub_EE8F0(unk_3D8, 2));
    lv_10.y = ABS(unk_4B9308.sub_EE8F0(unk_3D8, 0));
    lv_10.z = 0.0f;
    l1C = RwV3dLength(&lv_10);
    if (l1C > 1.0f)
    {
        l1C = 1.0f;
    }
    unk_2100 += arg_0 * l1C;
    if ((dword_4B86F8 >> 6) & 1)
    {
        lv_10.x = 0.0f;
        lv_10.y = 0.0f;
        lv_10.z = 0.0f;
    }
    ebp_14 = &dword_4E5E40;
    bp_4 = ebp_14->unk_08;
    m_18 = (&flt_44D490)[unk_1A04];
    if (unk_1B04)
    {
        m_18 = m_18 * 1.45f;
    }
    if (unk_2100 > m_18)
    {
        unk_2100 = 0.0f;
        if (unk_294 < 0)
        {
            if (dword_44E838)
            {
                type_3DF8D8_04 var_28;
                type_3D3548 *var_20;

                var_28.unk_00 = 0x9FAFD39B; // not an address: a key
                var_28.unk_04 = 0xAB43C2E3; // not an address: a key
                var_20 = sub_1745A0(0);
                dword_4B1E98.sub_8A980(&var_28, 0, 0, var_20->sub_CD550(), 1, 0);
            }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
            if (dword_44E860)
            {
                sub_19A750("Audio: WARNING! Player on non-tagged surface! Using 0 for Index Alias purposes");
            }
#endif
            unk_294 = 0;
        }
        unk_20FC = (type_44C4E8 *)unk_1C0.sub_8AA70(&dword_4B1F24[unk_1A04], bp_4[unk_294].unk_00, this, 1,
                                                    sub_CD550(), 0, 0);
        if (unk_20FC)
        {
            RwReal stk_2C;

            stk_2C = unk_20FC->unk_40;
            stk_2C = stk_2C * (&flt_44E814)[unk_1A04];
            sub_84C40("RwaVirtualVoiceSetGain((RwaVirtualVoice*)m_walkingSoundLoop, curVolume);");
            do
            {
                unk_20FC->unk_40 = stk_2C;
                if (unk_20FC->unk_30)
                {
                    RWA_SET_PARAM_REAL(unk_20FC->unk_30, 5, 1, stk_2C);
                }
            } while (0);
        }
    }
}

// match: ?sub_10C650@type_10F710@@QAEXXZ @ 0x0010C650
// sp-match: ?sub_10C650@type_10F710@@QAEXXZ @ 0x000C2AE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10C650()
{
    Trigger *l1C;
    type_3DF8D8 *m_18;
    type_712B0_10F710 *ebp_14;
    RwFrame *lv_10;
    RpClump *slot_C;
    RpHAnimHierarchy *bp_8;
    RpClump *bp_4;

    if (get_unk_34C())
    {
        l1C = unk_344.unk_08;
        if (l1C->vf_008() != 1)
        {
            return;
        }
        ebp_14 = (type_712B0_10F710 *)l1C;
        m_18 = sub_198800(&ebp_14->unk_CC);
        if (!m_18 || m_18->vf_008() != 3)
        {
            return;
        }
        slot_C = ((type_3DF9C4 *)(RpClump *)m_18)->sub_190A10();
        bp_4 = RpClumpClone(slot_C);
        sub_16D9A0(bp_4);
        unk_1A3C.sub_129940(0);
        unk_1A3C.sub_129620(bp_4);
        unk_1A3C.sub_129690(this);
        sub_79270(bp_4, 0);
        bp_8 = sub_16D970(bp_4);
        unk_284->sub_79470(bp_8);
        lv_10 = RpClumpGetFrame(bp_4);
        RwFrameAddChild(get_unk_340(), lv_10);
        RWS::ClumpHelper::SetCanCollide(*bp_4, 1);
        RpClumpForAllAtomics(bp_4, sub_1169B0, 0);
        sub_173180(bp_4);
    }
}

// Its pose's procedural part, on its animation's current keyframes: the eye
// height by stance (blended while it changes); node 1 (the root) raised to
// its trigger's height (while dying, by the eye height's change, crouched
// excepted), its view bob (vf_240) and lean (sub_1116A0), placed at the
// camera's while the camera follows it; the root turned about x by half the
// look's pitch. Node 2 (the spine) turned by the weapon's hold by stance (with
// the recoil while aiming, blended while the stance changes) about x, z and
// y, or for weapons with their own pose slerped into it with its offset;
// then the sway (unk_1AF8) added to its translation.
// match: ?sub_10C7B0@type_10F710@@QAEXM@Z @ 0x0010C7B0
// sp-match: ?sub_10C7B0@type_10F710@@QAEXM@Z @ 0x000CDE70
void type_10F710::sub_10C7B0(RwReal arg_0)
{
#ifndef CODFH_SP
    RtQuat fp_D0;
    RtQuat local_C0;
    RwV3d lB0;
#endif
    type_4C19C0 *lcl_A4;
    RwV3d pA0;
    RwV3d frm_94;
    type_7CBD0_t *t88;
    RtQuat ebp_84;
    RwV3d *lv_74;
    RtQuat *lcl_70;
    RwInt32 fp_6C;
    type_4C19C0 *fp_68;
    RtQuat lv_64;
    RwReal *frm_54;
    RtQuat s50;
    RwInt32 fp_40;
    RpHAnimHierarchy *ebp_3C;
    RtQuat lcl_38;
    type_7CBD0 *q28;
    type_7CBD0_hdr *frm_24;
    RtQuat t20;
    type_712B0_10F710 *lv_10;
    type_3DD948 *slot_C;
    RwReal bp_8;
    RwInt32 bp_4;

    lv_10 = (type_712B0_10F710 *)unk_344.unk_08;
    if (lv_10 && lv_10->vf_008() != 1)
    {
        lv_10 = 0;
    }
    fp_68 = unk_1A48[unk_1AE4]->unk_448;
    ebp_3C = unk_284->unk_18;
    if (!ebp_3C->currentAnim)
        return;
    q28 = (type_7CBD0 *)((type_80300 *)ebp_3C->currentAnim)->unk_144;
    frm_24 = q28->unk_04;
    t88 = (type_7CBD0_t *)&q28->unk_10[frm_24->unk_00];
    lcl_70 = q28->unk_10;
    fp_40 = 0;
    bp_4 = 1;
    fp_6C = 2;
    frm_54 = lv_10->unk_144_a;
    if (unk_1A0C)
        unk_1A00 = sub_112F80(frm_54[unk_1A08], frm_54[unk_1A04], unk_1A10);
    else
        unk_1A00 = frm_54[unk_1A04];
    if (unk_19D0 != 0xA)
        t88[bp_4].unk_00.y = lv_10->unk_150;
    else if (unk_1A04 != 2)
        t88[bp_4].unk_00.y += unk_1A00 + lv_10->unk_150 - unk_48;
    else
        t88[bp_4].unk_00.y = lv_10->unk_150;
    vf_240(&t88[bp_4].unk_00, arg_0);
    sub_1116A0(&lcl_70[bp_4], arg_0);
    slot_C = (type_3DD948 *)unk_2110.sub_D4910();
    if (slot_C->unk_3B0)
        t88[bp_4].unk_00 = RwFrameGetMatrix(slot_C->get_unk_340())->pos;
    ebp_84.real = (RwReal)cos(bp_8 = unk_530 * 0.5f * 0.017453292f);
    ebp_84.imag.x = (RwReal)sin(bp_8);
    ebp_84.imag.y = ebp_84.imag.z = 0.0f;
#ifdef CODFH_SP // shape: SP 0xCDE70 stages the first two scale-add components.
    lv_64.real = lcl_70[bp_4].real * ebp_84.real
                 - RwV3dDotProductMacro(&lcl_70[bp_4].imag, &ebp_84.imag);
    RwV3dCrossProductMacro(&lv_64.imag, &lcl_70[bp_4].imag, &ebp_84.imag);
    {
        RwReal v = lv_64.imag.x;
        lv_64.imag.x = v + ebp_84.imag.x * lcl_70[bp_4].real;
    }
    {
        RwReal v = lv_64.imag.y;
        lv_64.imag.y = v + ebp_84.imag.y * lcl_70[bp_4].real;
    }
    lv_64.imag.z += (ebp_84.imag.z * lcl_70[bp_4].real);
    RwV3dIncrementScaledMacro(&lv_64.imag, &lcl_70[bp_4].imag, ebp_84.real);
#else // MP 0x10C7B0
    RtQuatMultiplyMacro(&lv_64, &lcl_70[bp_4], &ebp_84);
#endif
    lcl_70[bp_4] = lv_64;
    if (!fp_68->unk_20)
    {
#ifdef CODFH_SP // shape: const views preserve SP 0xCDE70's branch and vector-add scheduling.
        const RwInt32 &q_69 = unk_1B04;
        if (q_69 || unk_1B08)
#else // MP 0x10C7B0
        if (unk_1B04 || unk_1B08)
#endif
        {
            pA0 = unk_1A48[unk_1AE4]->unk_238_a[unk_1A04];
#ifdef CODFH_SP // shape: SP 0xCDE70 keeps the position as a const input view.
            {
                const RwV3d &q = pA0;
                RwV3dAddMacro(&pA0, &unk_1A48[unk_1AE4]->unk_280, &q);
            }
#else // MP 0x10C7B0
            RwV3dAddMacro(&pA0, &unk_1A48[unk_1AE4]->unk_280, &pA0);
#endif
            lv_74 = &pA0;
        }
        else
        {
            pA0 = unk_1A48[unk_1AE4]->unk_238_a[unk_1A04];
            if (unk_1A0C)
            {
                lcl_A4 = unk_1A48[unk_1AE4]->unk_448;
                sub_112FC0(&pA0, &lcl_A4->unk_1C0_a[unk_1A08], &lcl_A4->unk_1C0_a[unk_1A04], unk_1A10);
            }
            lv_74 = &pA0;
        }
        frm_94.x = lv_74->x * 0.5f * 0.017453292f;
        frm_94.y = lv_74->y * 0.5f * 0.017453292f;
        frm_94.z = lv_74->z * 0.5f * 0.017453292f;
        t20.real = (RwReal)cos(frm_94.y);
        ebp_84.real = (RwReal)cos(frm_94.x);
        lcl_38.real = (RwReal)cos(frm_94.z);
        t20.imag.y = (RwReal)sin(frm_94.y);
        ebp_84.imag.x = (RwReal)sin(frm_94.x);
        lcl_38.imag.z = (RwReal)sin(frm_94.z);
        ebp_84.imag.y = ebp_84.imag.z = t20.imag.x = t20.imag.z = lcl_38.imag.x = lcl_38.imag.y = 0.0f;
        RtQuatMultiplyMacro(&lv_64, &lcl_70[fp_6C], &ebp_84);
        RtQuatMultiplyMacro(&s50, &lv_64, &lcl_38);
        RtQuatMultiplyMacro(&lcl_70[fp_6C], &s50, &t20);
        t88[fp_6C].unk_00.x = t88[fp_6C].unk_00.x + unk_1AF8.x;
        t88[fp_6C].unk_00.y = t88[fp_6C].unk_00.y + unk_1AF8.y;
        t88[fp_6C].unk_00.z = t88[fp_6C].unk_00.z + unk_1AF8.z;
    }
    else
    {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares their slots (SP 0xCDE70's frame)
        RtQuat fp_D0;
        RtQuat local_C0;
        RwV3d lB0;

#endif
        if (unk_1B04 || unk_1B08)
        {
            sub_13FBC0(&fp_D0, &unk_1A48[unk_1AE4]->unk_170[unk_1A04], &unk_1A48[unk_1AE4]->unk_1A0[unk_1A04],
                       unk_1A48[unk_1AE4]->unk_218);
            sub_112FC0(&lB0, &unk_1A48[unk_1AE4]->unk_1D0[unk_1A04], &unk_1A48[unk_1AE4]->unk_1F4[unk_1A04],
                       unk_1A48[unk_1AE4]->unk_218);
        }
        else if (unk_1A0C)
        {
            sub_13FBC0(&fp_D0, &unk_1A48[unk_1AE4]->unk_170[unk_1A08], &unk_1A48[unk_1AE4]->unk_170[unk_1A04],
                       unk_1A10);
            sub_112FC0(&lB0, &unk_1A48[unk_1AE4]->unk_1D0[unk_1A08], &unk_1A48[unk_1AE4]->unk_1D0[unk_1A04],
                       unk_1A10);
        }
        else
        {
            fp_D0 = unk_1A48[unk_1AE4]->unk_170[unk_1A04];
            lB0 = unk_1A48[unk_1AE4]->unk_1D0[unk_1A04];
        }
        RtQuatMultiplyMacro(&local_C0, &lcl_70[fp_6C], &fp_D0);
        lcl_70[fp_6C] = local_C0;
        t88[fp_6C].unk_00.x += lB0.x;
        t88[fp_6C].unk_00.y += lB0.y;
        t88[fp_6C].unk_00.z += lB0.z;
        t88[fp_6C].unk_00.x = t88[fp_6C].unk_00.x + unk_1AF8.x;
        t88[fp_6C].unk_00.y = t88[fp_6C].unk_00.y + unk_1AF8.y;
        t88[fp_6C].unk_00.z = t88[fp_6C].unk_00.z + unk_1AF8.z;
    }
}

// match: ?sub_10D8A0@type_10F710@@QAEXXZ @ 0x0010D8A0
// sp-match: ?sub_10D8A0@type_10F710@@QAEXXZ @ 0x000C2BC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10D8A0()
{
    RwInt32 lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    type_712B0_10F710 *bp_4;

    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    if (!bp_4)
    {
        return;
    }
    slot_C = 0;
    lv_10 = 0;
    for (bp_8 = 0; bp_8 < 0x27; bp_8++)
    {
        if (unk_1A48[bp_8])
        {
            unk_1A48[bp_8]->sub_116470();
            delete unk_1A48[bp_8];
            unk_1A48[bp_8] = 0;
        }
        slot_C = bp_4->unk_114[bp_8];
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        if (slot_C)
        {
            sub_19A750("Initializing geometery for weapon %d", bp_8);
        }
#endif
        unk_1A48[bp_8] = sub_116490(this, unk_1A3C.get_unk_08(), bp_8, slot_C);
        lv_10 += 0x470;
    }
    unk_1A48[30]->set_unk_464(1);
    unk_1A48[29]->set_unk_460(unk_1A48[30]);
    unk_1A48[36]->set_unk_464(1);
    unk_1A48[35]->set_unk_460(unk_1A48[36]);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Allocated %d bytes for %d CPlayerWeapon classes.", lv_10, 0x27);
#endif
}

// match: ?sub_10DA70@type_10F710@@QAEXH@Z @ 0x0010DA70
// sp-match: ?sub_10DA70@type_10F710@@QAEXH@Z @ 0x000C2C80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10DA70(RwInt32 arg_0)
{
    RwInt32 ebp_14;
    type_4C19C0 *lv_10;
    type_4C19C0 *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!unk_2138)
    {
        return;
    }
    slot_C = sub_119B70(arg_0);
    bp_4 = sub_16F860(slot_C->unk_24);
    if (bp_4 != -1)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("Requesting to stream weapon %d into slot %d IGNORED! Already detected in slot %d.", arg_0,
                   unk_2134, bp_4);
#endif
        return;
    }
    if (sub_16F8A0(slot_C->unk_24))
    {
        return;
    }
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Requesting to stream weapon %d into slot %d.  Clumps contained in wbank_%02d.bin.", arg_0,
               unk_2134, slot_C->unk_24);
#endif
    bp_8 = dword_4E54D0[unk_2134];
    if (sub_16F900(unk_2134, slot_C->unk_24) && bp_8 != -1)
    {
        for (ebp_14 = 0; ebp_14 < 0x27; ebp_14++)
        {
            lv_10 = sub_119B70(ebp_14);
            if (lv_10->unk_24 == bp_8)
            {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
                sub_19A750("\tUnInitializing geometry for weapon %d because it was in slot %d.  wbank_%02d.bin has "
                           "been unloaded",
                           ebp_14, unk_2134, lv_10->unk_24);
#endif
                unk_1A48[ebp_14]->vf_00C();
                return;
            }
        }
    }
}

// match: ?vf_258@type_10F710@@UAEXM@Z @ 0x0010DBD0
// sp-match: ?vf_258@type_10F710@@UAEXM@Z @ 0x000C6A10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::vf_258(RwReal arg_0)
{
    RwReal lcl_64;
    type_4C19C0 *l60;
    RwV3d fp_5C;
    RwV3d *loc50;
    RwV3d *x4C;
    RwV3d *w48;
    RwV3d *loc44;
    RwV3d *fp_40;
    RwV3d *ebp_3C;
    RwV3d local_38;
    RwV3d stk_2C;
    RwV3d t20;
    RwReal ebp_14;
    RwInt32 lv_10;
    type_712B0_10F710 *slot_C;
    RwFrame *bp_8;
    type_4C19C0 *bp_4;

    bp_8 = RpClumpGetFrame(unk_1A3C.get_unk_08());
    bp_4 = unk_1A48[unk_1AE4]->unk_448;
    if (bp_8)
    {
        slot_C = (type_712B0_10F710 *)unk_344.unk_08;
        if (slot_C && slot_C->vf_008() != 1)
        {
            slot_C = 0;
        }
        if (unk_1A48[unk_1AE4]->unk_220 > bp_4->unk_BC && !unk_1A48[unk_1AE4]->unk_48)
        {
            unk_1A48[unk_1AE4]->unk_45 = 0;
            unk_1B1C = 0;
#ifndef CODFH_SP // MP only: single player's player has no unk_1B18 (SP 0xCE6F0, 0xC4AF0)
            unk_1B18 = 0;
#endif
        }
#ifndef CODFH_SP // SP 0xC6A10 has no dword_4B86F8 bit-4 sound restart
        if (((dword_4B86F8 >> 4) & 1) && unk_1A48[unk_1AE4]->unk_46)
        {
            unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
            unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
            unk_1A48[unk_1AE4]->unk_46 = 0;
        }
#endif
        if (unk_1A48[unk_1AE4]->unk_48 == 1)
        {
            unk_1A48[unk_1AE4]->unk_45 = 0;
            unk_1B1C = 0;
        }
        if (!unk_1A48[unk_1AE4]->unk_12 && !unk_1A0C && unk_1A48[unk_1AE4]->unk_220 >= bp_4->unk_BC
            && !unk_1A48[unk_1AE4]->unk_11 && !unk_1A48[unk_1AE4]->unk_230 && !unk_1A48[unk_1AE4]->unk_228
            && !unk_1A48[unk_1AE4]->unk_22C && !unk_1A48[unk_1AE4]->unk_45)
        {
            unk_1A48[unk_1AE4]->unk_10 = 1;
        }
        if (unk_1A48[unk_1AE4]->unk_46 && !bp_4->unk_1C)
        {
            unk_1A48[unk_1AE4]->unk_46 = 0;
        }
        stk_2C = bp_4->unk_19C_a[unk_1A04];
        t20 = bp_4->unk_1E4_a[unk_1A04];
        local_38 = bp_4->unk_208_a[unk_1A04];
        if (unk_1B04)
        {
            stk_2C = bp_4->unk_19C_a[unk_1A04];
            t20 = bp_4->unk_238_a[unk_1A04];
            local_38 = bp_4->unk_25C_a[unk_1A04];
        }
        if (unk_1A0C)
        {
            loc50 = &bp_4->unk_19C_a[unk_1A04];
            x4C = &bp_4->unk_19C_a[unk_1A08];
            if (unk_1B04)
            {
                ebp_3C = &bp_4->unk_238_a[unk_1A04];
                loc44 = &bp_4->unk_238_a[unk_1A08];
                fp_40 = &bp_4->unk_25C_a[unk_1A04];
                w48 = &bp_4->unk_25C_a[unk_1A08];
            }
            else
            {
                ebp_3C = &bp_4->unk_1E4_a[unk_1A04];
                loc44 = &bp_4->unk_1E4_a[unk_1A08];
                fp_40 = &bp_4->unk_208_a[unk_1A04];
                w48 = &bp_4->unk_208_a[unk_1A08];
            }
            sub_112FC0(&stk_2C, x4C, loc50, unk_1A10);
            sub_112FC0(&t20, loc44, ebp_3C, unk_1A10);
            sub_112FC0(&local_38, w48, fp_40, unk_1A10);
        }
        unk_1AF8.z = 0.0f;
        unk_1AF8.y = 0.0f;
        unk_1AF8.x = 0.0f;
        if (!bp_4->unk_20)
        {
            if (unk_1A04 != 2 || !unk_1B1C)
            {
                RwV3dAdd(&unk_1AF8, &unk_1AF8, &stk_2C);
            }
            else
            {
                unk_1AF8 = stk_2C;
            }
            if (unk_1B04 || unk_1B08)
            {
                if (unk_1B0C && !unk_1A0C)
                {
                    RwV3dAdd(&unk_1AF8, &unk_1AF8, &unk_1A48[unk_1AE4]->unk_28C);
                }
                else
                {
                    l60 = unk_1A48[unk_1AE4]->unk_448;
                    sub_112FC0(&fp_5C, &l60->unk_3C8_a[unk_1A08], &l60->unk_3C8_a[unk_1A04], unk_1A10);
                    RwV3dAdd(&unk_1AF8, &unk_1AF8, &fp_5C);
                }
            }
        }
        lv_10 = unk_1A48[unk_1AE4]->unk_458;
        if (vf_1E4())
        {
            unk_1AF8.z = 0.0f;
            unk_1AF8.y = 0.0f;
            unk_1AF8.x = 0.0f;
        }
        else if ((lv_10 == 0x11 || lv_10 == 0xD || lv_10 == 0x12 || lv_10 == 0 ? 1 : 0) && unk_1B04 && !unk_1B0C)
        {
            unk_1AF8.z = 0.0f;
            unk_1AF8.y = 0.0f;
            unk_1AF8.x = 0.0f;
        }
        else
        {
            unk_1AF8.x += sin(local_38.x * unk_1AF4) * t20.x;
            unk_1AF8.y += sin(local_38.y * unk_1AF4) * t20.y;
            unk_1AF8.z += sin(local_38.z * unk_1AF4) * t20.z;
        }
        if (unk_1A48[unk_1AE4]->unk_18 > bp_4->unk_2B4_r[unk_1A04])
        {
            if (unk_1B04)
            {
                unk_1A48[unk_1AE4]->unk_18 = bp_4->unk_34C_r[unk_1A04];
            }
            else
            {
                unk_1A48[unk_1AE4]->unk_18 = bp_4->unk_2B4_r[unk_1A04];
            }
        }
        ebp_14 = 0.0f;
        if (unk_19D0 != 6 && unk_19D0 != 12 && !((dword_4B86F8 >> 6) & 1))
        {
#ifdef CODFH_SP // SP 0xC6A10 reads the stick without the dword_4B86F8 bit-4 test
            ebp_14 = ABS(unk_4B9308.sub_EE8F0(unk_3D8, 0));
#else
            if (!((dword_4B86F8 >> 4) & 1))
            {
                ebp_14 = ABS(unk_4B9308.sub_EE8F0(unk_3D8, 0));
            }
#endif
            if (unk_2148 != 0.0f)
            {
                ebp_14 = unk_2150;
            }
            lcl_64 = ABS(unk_4B9308.sub_EE8F0(unk_3D8, 2));
            if (lcl_64 > ebp_14)
            {
                ebp_14 = lcl_64;
            }
            if (unk_1A04 != 2 || !unk_1B1C)
            {
                unk_1AF4 += ebp_14 * bp_4->unk_22C_r[unk_1A04] * arg_0;
            }
            if (unk_1B04)
            {
                unk_1AF4 += arg_0 * bp_4->unk_280_r[unk_1A04];
            }
        }
        RwFrameSetIdentity(bp_8);
        RwFrameUpdateObjects(bp_8);
    }
}

// match: ?sub_10E750@type_10F710@@QAEXHH@Z @ 0x0010E750
// sp-match: ?sub_10E750@type_10F710@@QAEXHH@Z @ 0x000C7020
void type_10F710::sub_10E750(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0)
    {
        unk_1B3C = 1;
        unk_1B40 = 1;
        if (unk_19D0 == 5 && !unk_4D0 && vf_200() && vf_200()->vf_014())
        {
            vf_200()->vf_014()->sub_159910(0);
        }
    }
    else
    {
        unk_1B3C = arg_0;
        unk_1B40 = arg_4;
        if (unk_19D0 == 5 && vf_200() && vf_200()->vf_014())
        {
            vf_200()->vf_014()->sub_159910(1);
        }
    }
    sub_10E880(arg_0);
}

// match: ?sub_10E880@type_10F710@@QAEXH@Z @ 0x0010E880
// sp-match: ?sub_10E880@type_10F710@@QAEXH@Z @ 0x000C2D10
void type_10F710::sub_10E880(RwInt32 arg_0)
{
    if (dword_4B9190)
    {
        if (arg_0)
        {
            dword_4B9190->sub_DEB80(0);
        }
        else
        {
            dword_4B9190->sub_DEB80(3);
        }
    }
}

// match: ?sub_10E8C0@type_10F710@@QAEHH@Z @ 0x0010E8C0
// sp-match: ?sub_10E8C0@type_10F710@@QAEHH@Z @ 0x000C2D40
RwInt32 type_10F710::sub_10E8C0(RwInt32 arg_0)
{
    type_4C19C0 *var_4;

    var_4 = sub_119B70(arg_0);
    return sub_16F860(var_4->unk_24) != -1;
}

// match: ?sub_10E900@type_10F710@@QAEHH@Z @ 0x0010E900
// sp-match: ?sub_10E900@type_10F710@@QAEHH@Z @ 0x000C2D70
RwInt32 type_10F710::sub_10E900(RwInt32 arg_0)
{
    type_4C19C0 *var_4;

    var_4 = sub_119B70(arg_0);
    return sub_16F860(var_4->unk_24);
}

// match: ?sub_10E930@type_10F710@@QAEHXZ @ 0x0010E930
// sp-match: ?sub_10E930@type_10F710@@QAEHXZ @ 0x000C2D90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::sub_10E930()
{
    RwInt8 bp_8[3];
    RwInt32 bp_4;

    memset(bp_8, 0, 3);
    for (bp_4 = 0; bp_4 < 2; bp_4++)
    {
        if (unk_1B30[bp_4] != -1)
        {
            bp_8[sub_10E900(unk_1B30[bp_4])] = 1;
        }
    }
    for (bp_4 = 0; bp_4 < 3; bp_4++)
    {
        if (!bp_8[bp_4])
        {
            return bp_4;
        }
    }
    return 2;
}

// match: ?sub_10E9D0@type_10F710@@QAEXHHH@Z @ 0x0010E9D0
// sp-match: ?sub_10E9D0@type_10F710@@QAEXHHH@Z @ 0x000C70F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10E9D0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (arg_0 == -1 && arg_8 == 0 && arg_4 == 1)
    {
        unk_1B3C = 0;
        if (dword_4B9190)
        {
            dword_4B9190->sub_DEB80(3);
        }
        return;
    }
    if (arg_0 == -1 && arg_8 == 1 && arg_4 == 0)
    {
        arg_8 = !unk_1AE8;
        unk_1B30[arg_8] = -1;
        return;
    }
    unk_1B3C = 1;
    if (dword_4B9190)
    {
        if (arg_0 == 0x20)
        {
            dword_4B9190->sub_DEB80(3);
        }
        else
        {
            dword_4B9190->sub_DEB80(0);
        }
    }
    if (arg_0 == 0x20)
    {
        unk_1B40 = 1;
    }
    if (arg_8 == 0)
    {
        arg_8 = unk_1AE8;
    }
    else
    {
        arg_8 = !unk_1AE8;
    }
    bp_4 = -1;
    for (bp_8 = 0; bp_8 < 2 && bp_4 == -1; bp_8++)
    {
        if (arg_0 == unk_1B30[bp_8])
        {
            bp_4 = bp_8;
        }
    }
    if (bp_4 != -1)
    {
        if (bp_4 != arg_8)
        {
            slot_C = unk_1B30[0];
            unk_1B30[0] = unk_1B30[1];
            unk_1B30[1] = slot_C;
            unk_1AE8 = !unk_1AE8;
        }
        if (arg_4)
        {
            if (unk_1AE8 == arg_8)
            {
                if (arg_0 == 0x20)
                {
                    unk_1A48[unk_1B30[unk_1AE8]]->vf_01C();
                }
                return;
            }
            if (unk_1A48[unk_1AE4]->unk_46)
            {
                unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                unk_1A48[unk_1AE4]->unk_21C = 0;
                unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
                unk_1A48[unk_1AE4]->unk_46 = 0;
            }
            sub_100200(unk_1B30[!unk_1AE8]);
        }
    }
    else if (arg_4)
    {
        unk_2134 = sub_10E900(unk_1AE4);
        if (unk_1AE8 == arg_8)
        {
            unk_1A48[unk_1AE4]->sub_117370();
            unk_1B30[unk_1AE8] = arg_0;
            unk_1AE4 = unk_1B30[unk_1AE8];
            unk_1A48[unk_1AE4]->vf_008(this, unk_1A3C.get_unk_08(), unk_1AE4);
            unk_1A48[unk_1AE4]->sub_1170B0(1, 1);
        }
        else
        {
            lv_10 = !unk_1AE8;
            unk_1B30[lv_10] = arg_0;
            unk_1A48[arg_0]->vf_008(this, unk_1A3C.get_unk_08(), unk_1AE4);
            if (unk_1A48[unk_1AE4]->unk_46)
            {
                unk_1C0.sub_8A910(unk_1A48[unk_1AE4]->unk_21C);
                unk_1A48[unk_1AE4]->unk_21C = 0;
                unk_1C0.sub_8A980(&unk_1A48[unk_1AE4]->get_unk_448()->unk_14, this, 1, sub_CD550(), 0, 0);
                unk_1A48[unk_1AE4]->unk_46 = 0;
            }
            sub_100200(unk_1B30[!unk_1AE8]);
        }
    }
    else
    {
        unk_2134 = sub_10E900(unk_1B30[arg_8]);
        if (unk_1AE8 == arg_8)
        {
            ebp_14 = !unk_1AE8;
            unk_1B30[ebp_14] = unk_1B30[unk_1AE8];
            unk_1AE8 = ebp_14;
            unk_1B30[arg_8] = arg_0;
        }
        else
        {
            unk_1B30[arg_8] = arg_0;
        }
    }
}

#ifdef CODFH_SP
// Single player only: whether the line from arg_0's position (lowered by half
// its height) to arg_4's point, stopped short of arg_4 by the larger of its
// height and radius (but at least 1 along), is clear (sub_FCAE0); 0 for a
// missing one. vf_060 calls it (SP 0xCB637, 0xCB6C1, 0xCB716).
// sp-match: ?sp_sub_C2DF0@@YAHPAUtype_3D3548@@0@Z @ 0x000C2DF0
RwInt32 sp_sub_C2DF0(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    RpIntersection is;
    RwV3d d;
    RwV3d n;
    RwReal r;

    if (!arg_4 || !arg_0)
        return 0;
    is.type = rpINTERSECTLINE;
    is.t.line.start = *(RwV3d *)arg_0->vf_0C4();
    is.t.line.start.y -= arg_0->unk_48 * 0.5f;
    is.t.line.end = *arg_4->vf_0CC();
    r = arg_4->unk_48 > arg_4->unk_4C ? arg_4->unk_48 : arg_4->unk_4C;
    RwV3dSub(&d, &is.t.line.end, &is.t.line.start);
    r = RwV3dLength(&d) - r;
    if (r < 1.0f)
        r = 1.0f;
    RwV3dNormalize(&n, &d);
    RwV3dScale(&d, &n, r);
    RwV3dAdd(&is.t.line.end, &d, &is.t.line.start);
    return !sub_FCAE0(&is.t.line.start, &is.t.line.end, 0, 0, 0x410000, 1, 1); // not an address: flags
}
#endif

// match: ?vf_060@type_10F710@@UAEHPAUtype_3D3548@@@Z @ 0x0010EF70
// sp-match: ?vf_060@type_10F710@@UAEHPAUtype_3D3548@@@Z @ 0x000CB3F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::vf_060(type_3D3548 *arg_0)
{
#ifndef CODFH_SP
    RwInt32 q68;
#endif
    RwReal lcl_64;
#ifndef CODFH_SP
    RwV3d l60;
#endif
    RwMatrix *l54;
    RwV3d *loc50;
    RwReal x4C;
    RwReal w48;
    RwV3d *loc44;
    RwMatrix *fp_40;
    AIData *ebp_3C;
    type_7C8D0 *local_38;
#ifndef CODFH_SP
    RwV3d local_34;
    RwV3d slot_28;
    RwV3d l1C;
#endif
    RwReal lv_10;
    RwReal slot_C;
    RwV3d *bp_8;
    RwV3d *bp_4;

    if (arg_0)
    {
#ifdef CODFH_SP
        // Single player first looks for what to point the player at (SP 0xCB407): a
        // pickup in sight (kinds 0x4B..0x4D are taken through sub_106A60 at once,
        // the rest become unk_2108 when on the screen's scaled window and nearer its
        // centre than the last), or a mounted weapon it can use (unk_210C, and the
        // HUD's weapon item).
        if ((arg_0->unk_2C >> 14) & 1)
        {
            RwInt32 k = ((type_3D94B8 *)arg_0)->unk_3B0.sub_FB710();

            if (k == 0x4B || k == 0x4C || k == 0x4D)
            {
                if (sp_sub_C2DF0(this, arg_0))
                    sub_106A60((type_3D94B8 *)arg_0);
            }
            else
            {
                RwV3d pos = *arg_0->vf_0CC();
                RwCamera *cam = (RwCamera *)dword_4E5C74;
                RwReal scale = unk_538;
                RwReal nearP = cam->nearPlane;
                RwReal farP = cam->farPlane;
                RwInt32 w = cam->frameBuffer->width;
                RwInt32 h = cam->frameBuffer->height;
                RwInt32 sw = (RwInt32)(w * scale);
                RwInt32 sh = (RwInt32)(h * scale);
                RwInt32 ox = (RwInt32)((sw - w) * 0.5f);
                RwInt32 oy = (RwInt32)((sh - h) * 0.5f);
                RwV3d scr;

                sub_141590(&scr, &pos, 1, &cam->viewMatrix);
                if (scr.z > nearP && scr.z < farP)
                {
                    RwReal inv = 1.0f / scr.z;
                    RwReal sx;

                    scr.x = (sw * inv) * scr.x;
                    scr.y = sh - (sh * inv) * scr.y;
                    sx = scr.x;
                    if (!unk_2108.sub_D4910()
                        || (ox < sx && ox + w > sx && oy < scr.y && oy + h > scr.y))
                    {
                        RwV2d c;
                        RwV3d d;
                        RwReal len;
                        RwInt32 vis;

                        c.x = (RwReal)(RwUInt32)Width * 0.5f;
                        c.y = (RwReal)(RwUInt32)Height * 0.5f;
                        d.x = scr.x - c.x;
                        d.y = scr.y - c.y;
                        d.z = 0.0f;
                        len = RwV3dLength(&d);
                        vis = sp_sub_C2DF0(this, arg_0);
                        if (len < unk_3E4 && vis)
                        {
                            unk_2108.sub_D48D0(arg_0);
                            unk_3E4 = len;
                        }
                    }
                }
            }
        }
        else if (((arg_0->unk_2C >> 19) & 1) && unk_19D0 != 1 && unk_19D0 != 2 && unk_19D0 != 3 && dword_4B9190
                 && ((type_3DC9B0 *)arg_0)->sub_169190(this) && sp_sub_C2DF0(this, arg_0))
        {
            dword_4B9190->sp_sub_A9E00(((type_3DC9B0 *)arg_0)->unk_3B0);
            unk_210C.sub_D48D0(arg_0);
        }
#endif
        if (((arg_0->unk_2C >> 5) & 1) || ((arg_0->unk_2C >> 17) & 1) || ((arg_0->unk_2C >> 21) & 1)
            || ((arg_0->unk_2C >> 4) & 1) || (((arg_0->unk_2C >> 19) & 1) && arg_0->unk_268.get_unk_08()))
        {
            bp_8 = (RwV3d *)arg_0->vf_0C4();
            bp_4 = (RwV3d *)vf_0C4();
            if (!((arg_0->unk_28 >> 9) & 1) && !(arg_0->unk_28 & 1))
            {
#ifdef CODFH_SP // shape: block-scoped, sharing the target search's slots (SP frame 0x44)
                RwV3d local_34;
                RwV3d slot_28;
                RwV3d l1C;

#endif
                if (((arg_0->unk_2C >> 5) & 1) && ((arg_0->unk_28 >> 13) & 1))
                {
                    ebp_3C = arg_0->vf_120();
                    local_38 = arg_0->unk_284;
                    if (ebp_3C && local_38 && ebp_3C->sub_238E0(0))
                    {
                        fp_40 = RpHAnimHierarchyGetMatrixArray(local_38->get_unk_18());
                        slot_28 = fp_40[RpHAnimIDGetIndex(local_38->get_unk_18(), 1)].pos;
                        slot_28.y = bp_8->y;
                        bp_8 = &slot_28;
                    }
                }
                RwV3dSub(&local_34, bp_8, bp_4);
                local_34.y = 0.0f;
                lv_10 = RwV3dLength((RwV3d *)&local_34);
                RwV3dNormalize(&local_34, &local_34);
                slot_C = lv_10 - (unk_4C + arg_0->unk_4C) / 1.25f;
                if (slot_C < 0.0f)
                {
                    RwV3dScale(&local_34, &local_34, slot_C);
                    RwV3dAdd(&l1C, &local_34, bp_4);
                    if ((unk_2C >> 4) & 1)
                    {
                        loc44 = RwMatrixGetPos(RwFrameGetMatrix(get_unk_340()));
                        *loc44 = l1C;
                        RwFrameUpdateObjects(get_unk_340());
                    }
                    else
                    {
                        vf_0C0(&l1C);
                    }
                }
            }
            if (arg_0->vf_008())
            {
#ifdef CODFH_SP // shape: block-scoped (SP frame 0x44)
                RwV3d l60;

#endif
                RwV3dSub(&l60, bp_8, bp_4);
                l54 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
                loc50 = &l54->at;
                w48 = RwV3dLength((RwV3d *)&l60);
                RwV3dScale(&l60, &l60, 1.0f / w48);
                x4C = RwV3dDotProduct(&l60, loc50);
                if (x4C > 0.0f)
                {
                    lcl_64 = (flt_429AAC * x4C + flt_429AB0) * flt_429AB4;
                    if (w48 <= lcl_64)
                    {
#ifdef CODFH_SP // shape: block-scoped, in arg_0's slot (SP 0xCB999)
                        RwInt32 q68;

#endif
                        q68 = vf_09C();
                        sub_6B5F0("BlockingEntity", (type_67620 *)(arg_0->vf_098()), 0, 0, &q68, 1, true, false);
                    }
                }
            }
        }
        else if ((arg_0->unk_28 >> 16) & 1)
        {
            unk_2114.sub_D48D0(arg_0);
        }
    }
    return 0;
}

// match: ?vf_170@type_10F710@@UAEXHHHH@Z @ 0x0010F360
// sp-match: ?vf_170@type_10F710@@UAEXHHHH@Z @ 0x000C2F60
void type_10F710::vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    if (unk_1A48[unk_1AE4]->get_unk_45C() != 2)
    {
        unk_1A48[unk_1AE4]->vf_030(arg_0, arg_4, arg_8);
    }
    else
    {
        unk_1A48[unk_1AE4]->vf_030(arg_0, arg_4, arg_8);
    }
}

// match: ?vf_104@type_10F710@@UAEXPAURwMatrixTag@@@Z @ 0x0010F410
// sp-match: ?vf_104@type_10F710@@UAEXPAURwMatrixTag@@@Z @ 0x000C2FC0
void type_10F710::vf_104(RwMatrix *arg_0)
{
    RwFrame *var_4;

    var_4 = get_unk_340();
    *arg_0 = *RwFrameGetLTM(var_4);
}

// match: ?vf_108@type_10F710@@UAEXPAURwV3d@@@Z @ 0x0010F450
// sp-match: ?vf_108@type_10F710@@UAEXPAURwV3d@@@Z @ 0x000C2FF0
void type_10F710::vf_108(RwV3d *arg_0)
{
    *arg_0 = *sub_CD550();
    switch (unk_1A04)
    {
    case 2:
        arg_0->y += 10.0f;
        break;
    }
}

// match: ?vf_110@type_10F710@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x0010F4A0
// sp-match: ?vf_110@type_10F710@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x000C3030
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    RwMatrix *bp_8;
    RwFrame *bp_4;

    bp_4 = get_unk_340();
    bp_8 = RwFrameGetLTM(bp_4);
    *arg_0 = *RwMatrixGetPos(bp_8);
    if (arg_8)
    {
        switch (unk_1A04)
        {
        case 0:
            arg_0->y += flt_429AB8;
            break;
        case 2:
            arg_0->y += 30.0f;
            break;
        default:
            arg_0->y += 40.0f;
            break;
        }
    }
    else if (vf_1E4())
    {
        arg_0->y += flt_429ABC;
    }
    else
    {
        switch (unk_1A04)
        {
        case 0:
            arg_0->y -= 30.0f;
            break;
        case 2:
            arg_0->y += 25.0f;
            break;
        default:
            arg_0->y += 5.0f;
            break;
        }
    }
}

// match: ?vf_0AC@type_10F710@@UAEHXZ @ 0x0010F5C0
// sp-match: ?vf_0AC@type_10F710@@UAEHXZ @ 0x000C3100
RwInt32 type_10F710::vf_0AC()
{
    RwInt32 var_4;

    switch (unk_1A04)
    {
    case 0:
        var_4 = 0;
        break;
    case 2:
        var_4 = 8;
        break;
    default:
        var_4 = 0x12;
        break;
    }
    return var_4;
}

// match: ?vf_160@type_10F710@@UAEHXZ @ 0x0010F610
// sp-match: ?vf_160@type_10F710@@UAEHXZ @ 0x000C3120
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::vf_160()
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = unk_1A48[unk_1AE4]->unk_458;
    bp_4 = -1;
    switch (bp_8)
    {
    case 2:
    case 7:
    case 8:
    case 9:
    case 10:
    case 37:
        bp_4 = 0;
        break;
    case 0:
    case 1:
    case 27:
    case 28:
        bp_4 = 3;
        break;
    case 12:
    case 14:
    case 15:
    case 16:
        bp_4 = 2;
        break;
    case 11:
        bp_4 = 1;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
    case 23:
    case 24:
    case 25:
    case 26:
        bp_4 = 6;
        break;
    case 29:
    case 30:
    case 35:
    case 36:
        bp_4 = 7;
        break;
    case 13:
    case 17:
    case 18:
        bp_4 = 4;
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 31:
    case 33:
    case 34:
    case 38:
        bp_4 = 8;
        break;
    case 32:
        bp_4 = -1;
        break;
    default:
        bp_4 = -1;
        break;
    }
    return bp_4;
}

// match: ?sub_10F710@type_10F710@@QAEHXZ @ 0x0010F710
// sp-match: ?sub_10F710@type_10F710@@QAEHXZ @ 0x000C31D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::sub_10F710()
{
    RwInt32 bp_8;
    RwReal bp_4;

    if (unk_2240)
    {
        bp_4 = unk_4B9308.sub_EE8F0(unk_3D8, 0xF);
        if (bp_4 != 0.0f)
        {
            for (bp_8 = 0; bp_8 < 20; bp_8++)
            {
                if (unk_21F0[bp_8])
                {
                    return bp_8;
                }
            }
        }
    }
    return 0x13;
}

// match: ?sub_10F790@type_10F710@@QAEHXZ @ 0x0010F790
// sp-match: ?sub_10F790@type_10F710@@QAEHXZ @ 0x000C3220
RwInt32 type_10F710::sub_10F790()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 20; var_4++)
    {
        if (unk_21F0[var_4])
        {
            return var_4;
        }
    }
    return 0x13;
}

// match: ?sub_10F7E0@type_10F710@@QAEXHH@Z @ 0x0010F7E0
// sp-match: ?sub_10F7E0@type_10F710@@QAEXHH@Z @ 0x000C3240
void type_10F710::sub_10F7E0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (unk_1B2C)
    {
        arg_4 = 0;
    }
    unk_21F0[arg_0] = arg_4;
}

// match: ?sub_10F810@type_10F710@@QAEXPAUtype_3D3548@@H@Z @ 0x0010F810
// sp-match: ?sub_10F810@type_10F710@@QAEXPAUtype_3D3548@@H@Z @ 0x000CB9E0
void type_10F710::sub_10F810(type_3D3548 *arg_0, RwInt32 arg_4)
{
    type_3D3548 *var_4;

    if (arg_0)
    {
        sub_10F900(arg_0, arg_4);
    }
    else
    {
        var_4 = unk_2180.sub_D4910();
        if (var_4)
        {
            sub_10FBF0();
        }
    }
}

// match: ?vf_200@type_10F710@@UAEPAUtype_3D3548@@XZ @ 0x0010F860
// sp-match: ?vf_200@type_10F710@@UAEPAUtype_3D3548@@XZ @ 0x000C3270
type_3D3548 *type_10F710::vf_200()
{
    if (unk_2180.sub_D4910())
    {
        return unk_2180.sub_D4910()->vf_010();
    }
    return 0;
}

// match: ?sub_10F8A0@type_10F710@@QAEXPAUtype_3D3548@@H@Z @ 0x0010F8A0
// sp-match: ?sub_10F8A0@type_10F710@@QAEXPAUtype_3D3548@@H@Z @ 0x000C32A0
void type_10F710::sub_10F8A0(type_3D3548 *arg_0, RwInt32 arg_4)
{
    unk_2180.sub_D48D0(arg_0);
    unk_2184 = arg_4;
}

// match: ?sub_10F8D0@type_10F710@@QAEXPAUtype_4CFE30@@@Z @ 0x0010F8D0
// sp-match: ?sub_10F8D0@type_10F710@@QAEXPAUtype_4CFE30@@@Z @ 0x000C32D0
void type_10F710::sub_10F8D0(type_4CFE30 *arg_0)
{
    if (!arg_0 || ((VehicleEnterExitTrigger *)arg_0)->sub_BF470(this))
    {
        unk_2188 = arg_0;
    }
}

// match: ?sub_10F900@type_10F710@@QAEXPAUtype_3D3548@@H@Z @ 0x0010F900
// sp-match: ?sub_10F900@type_10F710@@QAEXPAUtype_3D3548@@H@Z @ 0x000C3300
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10F900(type_3D3548 *arg_0, RwInt32 arg_4)
{
    type_3DBC78 *slot_C;
    type_712B0 *bp_8;
    RwInt32 bp_4;

    unk_1AEC = unk_1AE4;
    unk_1A04 = 0;
    unk_218C = arg_4;
    switch (((type_3DBC78 *)arg_0)->get_unk_1188())
    {
    case 0:
        unk_28 &= ~0xAE;
        unk_28 |= 0x50;
        if (arg_4)
        {
            sub_1090F0(6);
        }
        else
        {
            sub_1090F0(5);
        }
        unk_2180.sub_D48D0(arg_0);
        break;
    case 1:
        unk_28 &= ~0xAE;
        unk_28 |= 0x50;
        unk_4D0 = 0;
        unk_4D8 = 0;
        unk_4DC = 0;
        unk_4E0 = unk_534;
        unk_4E4 = unk_534;
        unk_4EC = unk_534;
        unk_4E8 = 0;
        if (arg_4)
        {
            sub_1090F0(6);
            unk_2180.sub_D48D0(arg_0);
        }
        else
        {
            bp_4 = 0x1D;
            bp_8 = arg_0->get_unk_34C();
            switch (bp_8->unk_114)
            {
            case 1:
                bp_4 = 0x23;
                break;
            case 0:
                bp_4 = 0x1D;
                break;
            }
            if (unk_1A48[bp_4])
            {
                sub_1090F0(5);
                unk_1A48[unk_1AE4]->sub_117370();
                unk_1AE4 = bp_4;
                unk_1A48[unk_1AE4]->sub_1170B0(1, 1);
                unk_2180.sub_D48D0(arg_0);
                if (dword_4B9190)
                {
                    slot_C = (type_3DBC78 *)arg_0;
                    dword_4B9190->sub_E0B60(slot_C->unk_DD4, slot_C, unk_4D0);
                }
            }
            else
            {
                unk_2180.sub_D48D0(0);
            }
        }
        break;
    }
    dword_4D51C0.sub_15B5D0();
}

// match: ?sub_10FB70@type_10F710@@QAEHXZ @ 0x0010FB70
// sp-match: ?sub_10FB70@type_10F710@@QAEHXZ @ 0x000C3460
RwInt32 type_10F710::sub_10FB70()
{
    bool var_1;
    type_3DC9B0 *var_8;

    var_8 = (type_3DC9B0 *)unk_210C.sub_D4910();
    var_1 = false;
    if (var_8 && unk_1B28 && var_8->sub_169350(1))
    {
        var_8->sub_168A90(this);
        sub_1090F0(0);
        if (dword_4B9190)
        {
            dword_4B9190->sub_DEB80(0);
        }
        var_1 = true;
    }
    return var_1;
}

// match: ?sub_10FBF0@type_10F710@@QAEXXZ @ 0x0010FBF0
// sp-match: ?sub_10FBF0@type_10F710@@QAEXXZ @ 0x000C7480
// Leaves its vehicle: its frame off the vehicle's, 150 up in the world; back
// on foot (state 0) unless on a mounted weapon; out of a kind-1 vehicle its
// weapon in hand before it boarded (freeing the vehicle weapon's streaming
// slot, 0x1D or 0x23, when it may be selected).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_10FBF0()
{
    RwMatrix *l4;
    RwMatrix *var_8;
    type_3DBC78 *fp_C;
    RwFrame *local_10;
    RwFrame *stk_14;
    RwInt32 lcl_18;
    RwInt32 fp_1C;
    type_4C19C0 *ebp_20;

    fp_C = unk_2180.sub_D4910()->vf_010();
    local_10 = get_unk_340();
    stk_14 = fp_C->get_unk_340();
    if (!stk_14)
    {
        return;
    }
    if (stk_14)
    {
        RwFrameRemoveChild(local_10);
    }
    l4 = RwFrameGetMatrix(local_10);
    var_8 = RwFrameGetMatrix(stk_14);
    l4->pos.y += 150.0f;
    RwMatrixTransform(l4, var_8, rwCOMBINEPOSTCONCAT);
    if (unk_19D0 != 14)
    {
        sub_1090F0(0);
        unk_28 = 0x2017E; // not an address: flags
    }
    switch (fp_C->get_unk_1188())
    {
    case 1:
        if (unk_1AE4 == 0x1D || unk_1AE4 == 0x23)
        {
            lcl_18 = unk_1AE4;
            unk_1A48[unk_1AE4]->sub_117370();
            unk_1AE4 = get_unk_1AEC();
            unk_1A48[unk_1AE4]->sub_1170B0(1, 1);
            sub_10E750(1, 1);
            if (unk_1A48[lcl_18]->get_unk_41E())
            {
                ebp_20 = sub_119B70(lcl_18);
                fp_1C = sub_16F860(ebp_20->unk_24);
                if ((RwInt8)lcl_18 == dword_4E5518[fp_1C] >> 16)
                {
                    dword_4E5518[fp_1C] = 0;
                }
            }
        }
        break;
    }
    unk_2180.sub_D48D0(0);
    dword_4D51C0.pDtor();
}

// The line arg_4 against its ellipsoid (its radius and its stance's height,
// scaled by arg_C, around its bone 1 raised by the stance), the distance into
// *arg_8.
// match: ?vf_080@type_10F710@@UAEHHPAURpIntersection@@PAMM@Z @ 0x0010FDD0
// sp-match: ?vf_080@type_10F710@@UAEHHPAURpIntersection@@PAMM@Z @ 0x000C34D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::vf_080(RwInt32 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwReal arg_C)
{
    RpHAnimHierarchy *lv_30;
    RwMatrix *fp_2C;
    RwReal q28;
    RwReal frm_24;
    RwV3d t20;
    RpIntersection *ebp_14;
    RwV3d lv_10;
    RwInt32 bp_4;

    ebp_14 = arg_4;
    lv_30 = unk_284->unk_18;
    fp_2C = RpHAnimHierarchyGetMatrixArray(lv_30);
    t20 = *sub_CD550();
    bp_4 = 1;
    t20.y = fp_2C[bp_4].pos.y;
    t20.y = t20.y + unk_21A8[unk_1A04];
    q28 = arg_C * unk_4C;
    frm_24 = arg_C * unk_219C[unk_1A04];
    lv_10.x = 1.0f / (q28 * q28);
    lv_10.z = lv_10.x;
    lv_10.y = 1.0f / (frm_24 * frm_24);
    return sub_9A5F0(&t20, &lv_10, ebp_14, arg_8);
}

// The weapon's recoil scaled by the stance: unk_13C crouched, unk_140 prone,
// else 1; an inline with no address and so no database name, named for what
// it gives. Evidence: sub_1116A0 copies the stance into a temporary and
// then each branch's scale into the result's.
#ifdef CODFH_SP // the stance first: SP 0xC3C80 (out of line) reads it at [esp+4]
// sp-match: ?stance_recoil@@YAMHPAUtype_4C19C0@@@Z @ 0x000C3C80
inline RwReal stance_recoil(RwInt32 arg_4, type_4C19C0 *arg_0)
#else
inline RwReal stance_recoil(type_4C19C0 *arg_0, RwInt32 arg_4)
#endif
{
    if (arg_4 == 1)
        return arg_0->unk_13C;
    else if (arg_4 == 2)
        return arg_0->unk_140;
    return 1.0f;
}

// Adds arg_4 to arg_0 and bounds it by arg_8 (the lower bound sets arg_8
// too, as the image does); an inline with no address and so no database
// name. Evidence: sub_1116A0 keeps the target's address in a temporary of
// its own, and the bound in another when it is not a constant.
// sp-match: ?add_bounded@@YAXAAMMM@Z @ 0x000C3C40
inline void add_bounded(RwReal &arg_0, RwReal arg_4, RwReal arg_8)
{
    arg_0 += arg_4;
    if (arg_0 > arg_8)
        arg_0 = arg_8;
#ifdef CODFH_SP // shape: operands swapped for /O2 (SP 0xC3C40, out of line)
    else if (arg_0 < -arg_8)
#else
    else if (-arg_8 > arg_0)
#endif
        arg_0 = arg_8;
}

// Wraps the angle arg_0 into -180 to 180 degrees; an inline with no
// address. Evidence: sub_1116A0 keeps the angle's address in a temporary.
// sp-match: ?wrap_180@@YAXAAM@Z @ 0x000C3B70
inline void wrap_180(RwReal &arg_0)
{
    if (arg_0 > 180.0f)
        arg_0 -= 360.0f;
    else if (arg_0 < -180.0f)
        arg_0 += 360.0f;
}

// match: ?vf_064@type_10F710@@UAEHPAUtype_75600@@@Z @ 0x0010FEB0
// sp-match: ?vf_064@type_10F710@@UAEHPAUtype_75600@@@Z @ 0x000C3580
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::vf_064(type_75600 *arg_0)
{
    type_3D3548 *local_38;
    RwInt32 local_34;
    RwSphere frm_30;
    RpAtomic *t20;
    RwInt32 l1C;
    RwFrustumPlane *m_18;
    type_3D3548 *ebp_14;
    RwCamera *lv_10;
    RwReal slot_C;
    type_3D3548 *bp_8;
    RwInt32 bp_4;

    if (unk_19FC)
    {
        return 0;
    }
    if (unk_19EC <= 0.0f)
    {
        sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
        if (!byte_4F28F8 && get_unk_2110()->get_unk_414() != 1)
        {
#ifdef CODFH_SP // SP 0xC3580 scales the damage by the difficulty (sp_sub_BF910)
            slot_C = sp_sub_BF910() * arg_0->unk_2C;
#else
            slot_C = arg_0->unk_2C * 1.0f;
#endif
            if (unk_19DC > 0.0f && unk_19DC - slot_C / unk_19E0 <= 0.0f)
            {
                if (arg_0->unk_02_w == 0)
                {
                    dword_44E8B8 = unk_1C0.sub_8A980(&dword_4B1C80, this, 1, sub_CD550(), 0, 0);
                }
                else if (arg_0->unk_02_w == 1)
                {
                    dword_44E8B8 = unk_1C0.sub_8A980(&dword_4B1C18, this, 1, sub_CD550(), 0, 0);
                }
                else if (arg_0->unk_02_w == 2)
                {
                    dword_44E8B8 = unk_1C0.sub_8A980(&dword_4B1B40, this, 1, sub_CD550(), 0, 0);
                }
            }
            unk_19DC -= slot_C / unk_19E0;
            if (unk_19DC < 0.0f)
            {
                unk_19DC = 0.0f;
            }
        }
        if (unk_19DC > 0.0f)
        {
            if (arg_0->unk_02_w == 0)
            {
                unk_1C0.sub_8A980(&dword_4B1C50, this, 1, sub_CD550(), 0, 0);
            }
            else if (arg_0->unk_02_w == 1)
            {
                unk_1C0.sub_8A980(&dword_4B1C78, this, 1, sub_CD550(), 0, 0);
            }
            else if (arg_0->unk_02_w == 2)
            {
                unk_1C0.sub_8A980(&dword_4B1E88, this, 1, sub_CD550(), 0, 0);
            }
        }
        bp_4 = 0;
        if (arg_0->unk_0C)
        {
            l1C = 1;
            lv_10 = (RwCamera *)dword_4E5C74;
            m_18 = lv_10->frustumPlanes;
            ebp_14 = arg_0->unk_0C;
            t20 = ebp_14->unk_250.unk_08;
            if (t20)
            {
                frm_30 = *RpAtomicGetWorldBoundingSphere(t20);
            }
            else
            {
                frm_30.center = *ebp_14->sub_CD550();
                frm_30.radius = 500.0f;
            }
            for (local_34 = 0; local_34 < 6; local_34++, m_18++)
            {
                if (RwV3dDotProduct(&frm_30.center, &m_18->plane.normal) - m_18->plane.distance > frm_30.radius)
                {
                    l1C = 0;
                    local_34 = 6;
                }
            }
            if (l1C)
            {
                bp_4 = 1;
            }
        }
        if (bp_4)
        {
            unk_19EC = unk_19E4;
            unk_19F0 = unk_19E8;
            if (arg_0->unk_02_w & 1)
            {
                sub_128C20(dword_429704 * 4, 30.0f, 12.0f);
                local_38 = unk_2110.sub_D4910();
                if (local_38)
                {
                    ((type_3DD948 *)local_38)->sub_175E50(5.0f, 15.0f, 0.33333334f);
                }
            }
        }
        bp_8 = unk_2110.sub_D4910();
        if (bp_8)
        {
            ((type_3DD948 *)bp_8)->sub_175E50(2.0f, 4.0f, 0.5f);
        }
        if (dword_4B9190)
        {
            dword_4B9190->sub_DFB40(arg_0->unk_0C, 0);
        }
    }
    if (arg_0->unk_0C)
    {
        unk_550.sub_18DA0(arg_0->unk_0C);
    }
    return 0;
}

// match: ?vf_068@type_10F710@@UAEHPAUtype_758F0@@@Z @ 0x00110310
// sp-match: ?vf_068@type_10F710@@UAEHPAUtype_758F0@@@Z @ 0x000CBA20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_10F710::vf_068(type_758F0 *arg_0)
{
    RwReal lcl_38;
    type_3D3548 *r34;
    RwInt32 lv_30;
    RwReal fp_2C;
    type_114F90_50 *q28;
    RwReal frm_24;
    type_3D3548 *t20;
    RwReal l1C;
    RwReal m_18;
    RwV3d ebp_14;
    RwReal bp_8;
    RwInt32 bp_4;

    if (unk_19FC)
    {
        return 0;
    }
    bp_4 = 0;
    if (arg_0 && arg_0->unk_2C > 0.0f && vf_070(arg_0, 1, &bp_4))
    {
        RwV3dSub(&ebp_14, &arg_0->unk_0C->pos, sub_CD550());
        bp_8 = RwV3dLength((RwV3d *)&ebp_14);
        if (bp_8 > arg_0->unk_10)
        {
            return 1;
        }
        m_18 = 0.0f;
        if (arg_0->unk_10 <= 0.0f)
        {
            arg_0->unk_10 = 100.0f;
        }
        if (!arg_0->unk_30)
        {
#ifdef CODFH_SP // SP 0xCBA20 scales the blast damage by the difficulty (sp_sub_BF930)
            l1C = 1.0f - bp_8 / arg_0->unk_10;
            l1C = l1C * sp_sub_BF930() * arg_0->unk_2C;
#else
            l1C = bp_8 / arg_0->unk_10;
            l1C = (1.0f - l1C) * arg_0->unk_2C * 1.0f;
#endif
            m_18 = l1C / unk_19E0;
            if (arg_0->unk_10 / 2.0f > bp_8 && get_unk_19D0_r() != 5)
            {
                if (bp_4)
                {
                    sub_1109A0(5.0f * flt_429AC0, flt_429AC4);
                }
                else
                {
                    sub_1109A0(5.0f, 1.0f);
                }
            }
            else
            {
                frm_24 = (1.0f - bp_8 / arg_0->unk_10) * 10.0f;
                t20 = unk_2110.sub_D4910();
                if (t20)
                {
                    ((type_3DD948 *)t20)->sub_175E50(frm_24, frm_24 * 3.0f, frm_24 / (frm_24 * 3.0f));
                }
            }
        }
        else
        {
            q28 = &arg_0->unk_30->unk_50;
            lv_30 = vf_0BC();
            fp_2C = arg_0->unk_0C->pos.y - sub_CD550()->y;
            if (fp_2C > 145.0f)
            {
                lv_30 = 2;
            }
            else if (fp_2C > 90.0 && lv_30 == 0)
            {
                lv_30 = 1;
            }
            if (bp_8 < q28->unk_18)
            {
#ifdef CODFH_SP
                l1C = sp_sub_BF930() * arg_0->unk_2C;
#else
                l1C = arg_0->unk_2C * 1.0f;
#endif
                m_18 = l1C / unk_19E0;
            }
            else if (lv_30 == 0 || lv_30 == -1 || get_unk_19D0_r() == 5)
            {
#ifdef CODFH_SP
                l1C = 1.0f - (bp_8 - q28->unk_18) / (arg_0->unk_10 - q28->unk_18);
                l1C = l1C * sp_sub_BF930() * arg_0->unk_2C;
#else
                l1C = (bp_8 - q28->unk_18) / (arg_0->unk_10 - q28->unk_18);
                l1C = (1.0f - l1C) * arg_0->unk_2C * 1.0f;
#endif
                m_18 = l1C / unk_19E0;
            }
            else if (lv_30 == 1 && bp_8 < q28->unk_08)
            {
#ifdef CODFH_SP
                l1C = 1.0f - (bp_8 - q28->unk_18) / (q28->unk_08 - q28->unk_18);
                l1C = l1C * sp_sub_BF930() * arg_0->unk_2C;
#else
                l1C = (bp_8 - q28->unk_18) / (q28->unk_08 - q28->unk_18);
                l1C = (1.0f - l1C) * arg_0->unk_2C * 1.0f;
#endif
                m_18 = l1C / unk_19E0;
            }
            else if (lv_30 == 2 && bp_8 < q28->unk_0C)
            {
#ifdef CODFH_SP
                l1C = 1.0f - (bp_8 - q28->unk_18) / (q28->unk_0C - q28->unk_18);
                l1C = l1C * sp_sub_BF930() * arg_0->unk_2C;
#else
                l1C = (bp_8 - q28->unk_18) / (q28->unk_0C - q28->unk_18);
                l1C = (1.0f - l1C) * arg_0->unk_2C * 1.0f;
#endif
                m_18 = l1C / unk_19E0;
            }
            else
            {
                return 1;
            }
            sub_D2AD0(arg_0->unk_04.sub_D4910(), arg_0->unk_08);
            if ((bp_8 < q28->unk_1C || bp_8 < q28->unk_2C) && get_unk_19D0_r() != 5)
            {
                if (bp_4)
                {
                    sub_110900(bp_8, flt_429AC0 * q28->unk_30, q28->unk_2C, flt_429AC4, q28->unk_1C,
                               q28->unk_20, q28->unk_24, q28->unk_28);
                }
                else
                {
                    sub_110900(bp_8, q28->unk_30, q28->unk_2C, 1.0f, q28->unk_1C, q28->unk_20,
                               q28->unk_24, q28->unk_28);
                }
            }
            else
            {
                lcl_38 = (1.0f - bp_8 / arg_0->unk_10) * 10.0f;
                r34 = unk_2110.sub_D4910();
                if (r34)
                {
                    ((type_3DD948 *)r34)->sub_175E50(lcl_38, lcl_38 * 3.0f, lcl_38 / (lcl_38 * 3.0f));
                }
            }
        }
        if (!byte_4F28F8 && get_unk_2110()->get_unk_414() != 1)
        {
            if (m_18 < 0.0f)
            {
                m_18 = 0.0f;
            }
            unk_19DC = unk_19DC - m_18;
            unk_19EC = unk_19E4;
            unk_19F0 = unk_19E8;
            if (unk_19DC <= 0.0f)
            {
                dword_44E8B8 = unk_1C0.sub_8A980(&dword_4AF018, this, 1, sub_CD550(), 0, 0);
            }
        }
        if (dword_4B9190)
        {
            dword_4B9190->sub_DFB40(0, &arg_0->unk_0C->pos);
        }
    }
    return 0;
}

// match: ?sub_110900@type_10F710@@QAEXMMMMMMMM@Z @ 0x00110900
// sp-match: ?sub_110900@type_10F710@@QAEXMMMMMMMM@Z @ 0x000C38A0
void type_10F710::sub_110900(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                             RwReal arg_18, RwReal arg_1C)
{
    type_3D3548 *var_4;

    if (arg_0 < arg_10)
    {
        var_4 = unk_2110.sub_D4910();
        if (var_4)
        {
            ((type_3DD948 *)var_4)->sub_175E50(arg_C * arg_14, arg_18, arg_1C);
        }
    }
    if (arg_0 < arg_8)
    {
        arg_4 = ((arg_4 * 60.0f) * arg_C) / 5.0f;
        sub_128C20(dword_429704, arg_4, arg_1C);
        sub_D98D0(0.2f, arg_4);
    }
}

// match: ?sub_1109A0@type_10F710@@QAEXMM@Z @ 0x001109A0
// sp-match: ?sub_1109A0@type_10F710@@QAEXMM@Z @ 0x000C75A0
void type_10F710::sub_1109A0(RwReal arg_0, RwReal arg_4)
{
    RwReal var_4;

    var_4 = 20.0f * arg_4;
    sub_110A10(var_4);
    arg_0 = (arg_0 * 60.0f) / 5.0f;
    sub_128C20(dword_429704, arg_0, 12.0f);
    sub_D98D0(0.2f, arg_0);
}

// match: ?sub_110A10@type_10F710@@QAEXM@Z @ 0x00110A10
// sp-match: ?sub_110A10@type_10F710@@QAEXM@Z @ 0x000C3930
void type_10F710::sub_110A10(RwReal arg_0)
{
    type_3D3548 *var_4;

    var_4 = unk_2110.sub_D4910();
    if (var_4)
    {
        ((type_3DD948 *)var_4)->sub_175E50(arg_0, arg_0 * 3.0f, arg_0 / (arg_0 * 3.0f));
    }
}

// match: ?sub_110A60@type_10F710@@QAEXH@Z @ 0x00110A60
// sp-match: ?sub_110A60@type_10F710@@QAEXH@Z @ 0x000C75F0
void type_10F710::sub_110A60(RwInt32 arg_0)
{
    RwInt32 var_8;
    RpClump *var_C;
    RpHAnimHierarchy *var_14;
    RwMatrix *var_18;
    RwMatrix *var_1C;
    RwMatrix *var_20;
    RwMatrix var_60;
    RwMatrix var_A0;
    type_3D3548 *var_A4;
    type_8E670 *var_A8;
    RwInt32 var_AC;
    type_110EC0 var_BC;
    RpClump *var_C4;
    RwLLLink *var_C8;
    RwLLLink *var_CC;
    RpAtomic *var_D0;
    RwLLLink *var_D8;
    RwLLLink *var_DC;
    RpAtomic *var_E0;
    type_3DC9B0 *var_E4;

    var_8 = unk_1A48[unk_1AE4]->unk_458;
    var_C = unk_1A3C.get_unk_08();
    if (var_C && !unk_1B28 && unk_1A48[unk_1AE4]->get_unk_41C())
    {
        if (var_8 == 4 && !((dword_4B86F8 >> 4) & 1))
        {
            var_14 = unk_284->unk_18;
            var_18 = RpHAnimHierarchyGetMatrixArray(var_14);
            var_1C = &var_18[unk_1A48[unk_1AE4]->unk_58];
            var_20 = &var_18[unk_1A48[unk_1AE4]->unk_5C];
            RwMatrixInvert(&var_60, var_1C);
            RwMatrixRotate(var_1C, &stru_3D973C, unk_1A48[unk_1AE4]->unk_50, rwCOMBINEPRECONCAT);
            RwMatrixMultiply(&var_A0, var_20, &var_60);
            RwMatrixMultiply(var_20, &var_A0, var_1C);
        }
        dword_4CF7A4 = 0;
        dword_4CF7BC = 0;
        var_A4 = vf_200();
        if (var_A4 && (var_A4->unk_28 >> 17) & 1)
        {
            var_A8 = &var_A4->unk_90;
        }
        else
        {
            var_A8 = &unk_90;
        }
        var_AC = unk_1A48[unk_1AE4]->unk_458;
        var_BC.unk_00 = var_AC == 0x11 || var_AC == 0xD || var_AC == 0x12 || var_AC == 0;
        var_BC.unk_04 = unk_1B04 && !unk_1B0C;
        var_BC.unk_08 = 0;
        var_C4 = 0;
        if (var_8 != 0x1D && var_8 != 0x23 && (!var_BC.unk_00 || !var_BC.unk_04))
        {
            var_C4 = unk_1A3C.get_unk_08();
            if (var_C4)
            {
                var_C8 = rwLinkListGetFirstLLLink(&var_C4->atomicList);
                var_CC = rwLinkListGetTerminator(&var_C4->atomicList);
                var_D0 = 0;
                if (var_C8 != var_CC)
                {
                    var_D0 = rwLLLinkGetData(var_C8, RpAtomic, inClumpLink);
                }
                if (var_D0)
                {
                    sub_122820(var_D0, this, (RwInt32)var_A8);
                    RpClumpForAllAtomics(var_C4, sub_110EC0, 0);
                }
            }
        }
        var_C4 = unk_1A48[unk_1AE4]->get_unk_428();
        if (var_C4)
        {
            var_D8 = rwLinkListGetFirstLLLink(&var_C4->atomicList);
            var_DC = rwLinkListGetTerminator(&var_C4->atomicList);
            var_E0 = 0;
            if (var_D8 != var_DC)
            {
                var_E0 = rwLLLinkGetData(var_D8, RpAtomic, inClumpLink);
            }
            if (var_E0)
            {
                sub_122820(var_E0, this, (RwInt32)var_A8);
                RpClumpForAllAtomics(var_C4, sub_110EC0, &var_BC);
            }
        }
    }
    else if (unk_1B28)
    {
        dword_4CF7A4 = 0;
        dword_4CF7BC = 0;
        var_E4 = (type_3DC9B0 *)unk_210C.sub_D4910();
        if (var_E4)
        {
            var_E4->sub_1679C0(arg_0);
        }
    }
}

// match: ?sub_110EC0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x00110EC0
// sp-match: ?sub_110EC0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000C3970
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_110EC0(RpAtomic *arg_0, void *arg_4)
{
    const RwSphere *m_18;
    RwInt32 ebp_14;
    type_110EC0 *lv_10;
    RwInt32 slot_C;
    RwInt32 *bp_8;
    RwInt8 l1;

    lv_10 = 0;
    l1 = ((RwObject *)arg_0)->flags;
    l1 |= 4;
    ((RwObject *)arg_0)->flags = l1;
    if (arg_4)
    {
        lv_10 = (type_110EC0 *)arg_4;
        slot_C = lv_10->unk_00;
        ebp_14 = lv_10->unk_04;
        bp_8 = &lv_10->unk_08;
        if (slot_C)
        {
            if (ebp_14)
            {
                if (*bp_8 == 0)
                {
                    (*bp_8)++;
                    l1 &= ~4;
                    ((RwObject *)arg_0)->flags = l1;
                    return arg_0;
                }
            }
            else if (*bp_8 == 1)
            {
                (*bp_8)++;
                l1 &= ~4;
                ((RwObject *)arg_0)->flags = l1;
                return arg_0;
            }
        }
        (*bp_8)++;
    }
    if (arg_0->renderFrame != RWSRCGLOBAL(renderFrame))
    {
        m_18 = RpAtomicGetWorldBoundingSphere(arg_0);
        if (RwCameraFrustumTestSphere(RwCameraGetCurrentCamera(), m_18))
        {
            RpAtomicRender(arg_0);
        }
        arg_0->renderFrame = RWSRCGLOBAL(renderFrame);
    }
    l1 &= ~4;
    ((RwObject *)arg_0)->flags = l1;
    return arg_0;
}

// match: ?sub_111000@type_10F710@@QAEPAURpWorld@@XZ @ 0x00111000
// sp-match: ?sub_111000@type_10F710@@QAEPAURpWorld@@XZ @ 0x000C3A10
RpWorld *type_10F710::sub_111000()
{
    RpClump *var_4;

    var_4 = unk_1A48[unk_1AE4]->unk_420.unk_08;
    return RpClumpGetWorld(var_4);
}

// match: ?sub_111040@type_10F710@@QAEXPAUtype_D90B0@@@Z @ 0x00111040
// sp-match: ?sub_111040@type_10F710@@QAEXPAUtype_D90B0@@@Z @ 0x000C3A30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_111040(type_D90B0 *arg_0)
{
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    bp_8 = unk_19E0;
    arg_0->unk_50 = bp_8;
    arg_0->unk_54 = unk_19DC;
    arg_0->unk_58 = dword_4B8770;
    slot_C = unk_1AE4;
    arg_0->unk_00 = slot_C;
    if (unk_1A48[arg_0->unk_00]->get_unk_45C() == 2)
    {
        arg_0->unk_00 = unk_1B30[unk_1AE8];
    }
    arg_0->unk_04 = unk_1AE8;
    for (bp_4 = 0; bp_4 < 2; bp_4++)
    {
        arg_0->unk_08[bp_4] = unk_1B30[bp_4];
        arg_0->unk_10[bp_4] = unk_1A48[unk_1B30[bp_4]]->unk_414 + unk_1A48[unk_1B30[bp_4]]->unk_418;
    }
    unk_21B4.sub_1162C0(arg_0 ? &arg_0->unk_18 : 0);
}

// match: ?vf_098@type_10F710@@UAEPAUtype_3D2E7C@@XZ @ 0x00111180
// sp-match: ?vf_098@type_10F710@@UAEPAUtype_3D2E7C@@XZ @ 0x000C3AF0
type_3D2E7C *type_10F710::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_54C);
}

// match: ?vf_234@type_10F710@@UAEXPAUSplinePath@@PAURwV3d@@@Z @ 0x001111A0
// sp-match: ?vf_234@type_10F710@@UAEXPAUSplinePath@@PAURwV3d@@@Z @ 0x000C3B00
void type_10F710::vf_234(SplinePath *arg_0, RwV3d *arg_4)
{
    unk_19D0 = 0xB;
    unk_211C = *arg_4;
    unk_212C = arg_0->sub_BA450(sub_CD550(), 100.0f, 1.0f);
    unk_2130 = arg_0->sub_BA450(&unk_211C, 100.0f, 1.0f);
}

// match: ?sub_111220@@YAMMMMMPAMMM@Z @ 0x00111220
// sp-match: ?sub_111220@@YAMMMMMPAMMM@Z @ 0x000C3BB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_111220(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal *arg_10, RwReal arg_14,
                  RwReal arg_18)
{
    RwReal slot_C;
    RwReal bp_8;
    RwReal bp_4;

    slot_C = (arg_4 - arg_0) * arg_14 + arg_0;
    bp_8 = (arg_C - arg_8) * arg_14 + arg_8;
    bp_4 = sin(*arg_10) * slot_C;
    if (arg_14 == 0.0f)
    {
        *arg_10 *= 0.96f;
    }
    else
    {
        *arg_10 += bp_8 * arg_18;
    }
    if (*arg_10 > 3.14159f)
    {
        *arg_10 -= 6.28318f;
    }
    else if (*arg_10 < -3.14159f)
    {
        *arg_10 += 6.28318f;
    }
    return bp_4;
}

#ifdef CODFH_SP
// Single player only: steps the point *arg_8 along the frame arg_0's right
// vector by a quarter of arg_4, up to three times while sub_115230 finds room
// there; after a step it backs off 5 against the direction. 0 without a
// frame. vf_240 calls it (SP 0xCC2CE, 0xCC37D).
// sp-match: ?sp_sub_C7830@@YAHPAURwFrame@@MPAURwV3d@@@Z @ 0x000C7830
RwInt32 sp_sub_C7830(RwFrame *arg_0, RwReal arg_4, RwV3d *arg_8)
{
    RwMatrix *m;
    RwReal r;
    RwReal s;
    RwV3d step;
    RwV3d p;
    RwInt32 moved;
    RwInt32 i;

    if (arg_0)
    {
        m = RwFrameGetMatrix(arg_0);
        if (m)
        {
            moved = 0;
            r = (RwReal)fabs(s = arg_4 * 0.25f);
            RwV3dScale(&step, &m->right, s);
            RwV3dAdd(&p, &step, arg_8);
            for (i = 0; i < 3; i++)
            {
                if (sub_115230(&p, r))
                    break;
                *arg_8 = p;
                RwV3dAdd(&p, &step, arg_8);
                moved = 1;
            }
            if (moved)
            {
                if (s > 0.0f)
                    RwV3dScale(&step, &m->right, -5.0f);
                else
                    RwV3dScale(&step, &m->right, 5.0f);
                RwV3dAdd(arg_8, &step, arg_8);
            }
            return 1;
        }
    }
    return 0;
}
#endif

// match: ?vf_240@type_10F710@@UAEXPAURwV3d@@M@Z @ 0x001112F0
// sp-match: ?vf_240@type_10F710@@UAEXPAURwV3d@@M@Z @ 0x000CBE80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::vf_240(RwV3d *arg_0, RwReal arg_4)
{
    RwInt32 l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;
    RwReal slot_C;
    type_712B0_10F710 *bp_8;
    RwReal bp_4;

    if (unk_52C != 0.0f)
    {
        unk_52C -= arg_4 * 0.5f;
        if (unk_52C <= 0.0f)
        {
            dword_4B9190->sub_DFB40(0, 0);
            unk_52C = 0.0f;
        }
    }
    l1C = unk_19D0 == 0 || unk_19D0 == 1 || unk_19D0 == 2 || unk_19D0 == 3;
    sub_112DA0(&unk_404, 0.0f, &unk_408, flt_42970C, flt_429710, flt_429714, arg_4);
    arg_0->y = arg_0->y - unk_404;
    lv_10 = 0.0f;
    ebp_14 = 0.0f;
    m_18 = 0.0f;
    if (unk_19D0 == 0 && l1C)
    {
        lv_10 = (m_18 = unk_4B9308.sub_EE8F0(unk_3D8, 0)) < 0.0f ? -m_18 : m_18;
        ebp_14 = ABS(unk_4B9308.sub_EE8F0(unk_3D8, 2));
        if (ebp_14 > lv_10)
        {
            lv_10 = ebp_14;
        }
        if ((dword_4B86F8 >> 6) & 1)
        {
            lv_10 = 0.0f;
            m_18 = 0.0f;
        }
        if (unk_1A04 == 1)
        {
            lv_10 *= 0.8f;
        }
        else if (unk_1A04 == 2)
        {
            lv_10 *= 0.3f;
        }
    }
    if (unk_19D0 == 7)
    {
        unk_41C = 0.0f;
        unk_418 = 0.0f;
    }
    bp_8 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_8 && bp_8->vf_008() != 1)
    {
        bp_8 = 0;
    }
    bp_4 = arg_4 * 0.5f;
    arg_0->y += sub_111220(bp_8->unk_204, bp_8->unk_210, bp_8->unk_21C, bp_8->unk_220, &unk_40C, lv_10, bp_4);
    if (m_18 < 0.0f)
    {
        slot_C = 0.0f;
    }
    else
    {
        slot_C = flt_429AD0 * m_18;
    }
    sub_112DA0(&unk_418, slot_C, &unk_41C, flt_429AD4, flt_429AD8, 1000.0f, arg_4);
    arg_0->y = arg_0->y - unk_418;
    if (ebp_14 > 0.5f)
    {
        lv_10 = 0.0f;
    }
    arg_0->x += sub_111220(bp_8->unk_214, bp_8->unk_218, bp_8->unk_224, bp_8->unk_228, &unk_410, lv_10, bp_4);
#ifdef CODFH_SP
    // Single player leans (SP 0xCC161): on foot, not aiming, with button 6 (or
    // unk_1B04) it takes over buttons 29 and 30 (their settings kept in unk_2248
    // and unk_224C) and leans by flt_429ADC to the side held, when there is room
    // (sp_sub_C7830, the step kept in unk_4F8); otherwise, or when it gives the
    // buttons back, it steps back. The sway unk_4F0 follows the lean.
    lv_10 = 0.0f;
    if (l1C && !unk_1A48[unk_1AE4]->unk_230
        && (unk_4B9308.sub_EE8F0(unk_3D8, 6) != 0.0f || unk_1B04))
    {
        if (!unk_2244)
        {
            unk_2244 = 1;
            unk_2248 = unk_4B9308.sub_EED00(0x1D);
            unk_224C = unk_4B9308.sub_EED00(0x1E);
        }
        unk_4B9308.sub_EECD0(0x1D, 1);
        unk_4B9308.sub_EECD0(0x1E, 1);
        if (unk_19D0 != 2 && unk_19D0 != 3 && unk_19D0 != 1)
        {
            if (unk_4B9308.sub_EE8F0(unk_3D8, 0x1E) != 0.0f)
                lv_10 = -flt_429ADC;
            if (unk_4B9308.sub_EE8F0(unk_3D8, 0x1D) != 0.0f)
                lv_10 = flt_429ADC;
        }
        if (lv_10 != 0.0f)
        {
            if (unk_4F8 == 0.0f && sp_sub_C7830(get_unk_340(), lv_10, &unk_434))
                unk_4F8 = lv_10;
        }
        else if (unk_4F8 != 0.0f)
        {
            sp_sub_C7830(get_unk_340(), -unk_4F8, &unk_434);
            unk_4F8 = 0.0f;
        }
    }
    else
    {
        unk_4B9308.sub_EECD0(0x1D, unk_2248);
        unk_4B9308.sub_EECD0(0x1E, unk_224C);
        unk_2244 = 0;
        if (unk_4F8 != 0.0f)
        {
            sp_sub_C7830(get_unk_340(), -unk_4F8, &unk_434);
            unk_4F8 = 0.0f;
        }
    }
    sub_112DA0(&unk_4F0, lv_10, &unk_4F4, flt_429AC8, flt_429ACC, 1000.0f, arg_4);
#endif
}

// The lean and recoil on the root's rotation arg_0 (the pose, sub_10C7B0):
// on foot or on a mounted weapon (or while vf_1E4 allows), a fire records the
// look's pitch and the view's heading; after the burst the pitch returns
// there and the view turns back when it moved by more than 10 degrees. The
// weapon's recoil by kind (random, building up to 1000, or every so many
// fires up to its settings' bounds) springs into the pitch and yaw offsets
// (sub_112DA0) with the pad's rumble; aiming, the scope's sway (sines by the
// stance, blended while it changes) follows its settings, else decays. The
// sideways sway (unk_4F0) and the offsets then turn the rotation.
// match: ?sub_1116A0@type_10F710@@QAEXPAURtQuat@@M@Z @ 0x001116A0
// sp-match: ?sub_1116A0@type_10F710@@QAEXPAURtQuat@@M@Z @ 0x000CC3D0
void type_10F710::sub_1116A0(RtQuat *arg_0, RwReal arg_4)
{
    RwReal sFC;
    RwReal ebp_F8;
    RwReal wF4;
    RwReal var_F0;
    RwReal locEC;
    RwReal bp_E8;
    RtQuat lv_E4;
    RwReal frm_D4;
    RtQuat uD0;
    RwReal pC0;
    RtQuat frm_BC;
    RtQuat locAC;
    RwReal ebp_9C;
    RwReal p98;
    RwReal frm_94;
    RwReal q90;
    RwReal fp_8C;
    RtQuat t88;
    RtQuat fp_78;
    RwReal q68;
    RwReal var_64;
    RwReal stk_60;
    RwReal y5C;
    RwReal slot_58;
    RwReal l54;
    RwReal loc50;
    RwReal x4C;
    RwReal w48;
    RwReal loc44;
    RwReal fp_40;
    RwMatrix *ebp_3C;
    RwReal lcl_38;
    RwReal r34;
    RwFrame *lv_30;
    RwMatrix *fp_2C;
    RwFrame *q28;
    type_10F710_1A48 *frm_24;
    RwReal t20;
    RwReal l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwInt32 lv_10;
    type_4C19C0 *slot_C;
    RwReal bp_8;
    RwInt32 bp_4;

    if (unk_19D0 != 0 && unk_19D0 != 1 && unk_19D0 != 2 && unk_19D0 != 3 && unk_19D0 != 7 && !vf_1E4())
        return;
    bp_8 = 0.1f;
    l1C = 0.6f;
    frm_24 = unk_1A48[unk_1AE4];
    slot_C = frm_24->unk_448;
    ebp_14 = 1.0f;
    if (unk_1B04 && !unk_1B0C)
        ebp_14 = slot_C->unk_144;
    bp_4 = 0;
    if (unk_1B20)
    {
        bp_4 = 1;
        if (!unk_20E8)
        {
            unk_20E8 = 1;
            unk_20E0 = unk_530;
            q28 = unk_338.unk_08;
            if (q28 && (fp_2C = RwFrameGetMatrix(q28)) != 0)
            {
                if (fp_2C->at.x == 0.0f)
                    unk_20E4 = (RwReal)atan(bp_E8 = ratio(-fp_2C->up.z, -fp_2C->up.x));
                else
                    unk_20E4 = (RwReal)atan(locEC = fp_2C->at.z / fp_2C->at.x);
                unk_20E4 *= 57.295784f;
            }
        }
    }
    else if (!unk_1B24)
    {
        if (unk_20E8 == 1)
        {
            lcl_38 = (RwReal)fabs(var_F0 = unk_530 - unk_20E0);
            unk_20C8 = unk_20C8 - unk_530 + unk_20E0;
            unk_20D8 = 0.0f;
            unk_530 = unk_20E0;
            lv_30 = unk_338.unk_08;
            if (lv_30 && (ebp_3C = RwFrameGetMatrix(lv_30)) != 0)
            {
                if (ebp_3C->at.x == 0.0f)
                    r34 = (RwReal)atan(wF4 = ratio(-ebp_3C->up.z, -ebp_3C->up.x));
                else
                    r34 = (RwReal)atan(ebp_F8 = ebp_3C->at.z / ebp_3C->at.x);
                r34 *= 57.295784f;
                if ((RwReal)fabs(sFC = r34 - unk_20E4) > 10.0f || lcl_38 > 10.0f)
                {
                    RwFrameRotate(lv_30, &stru_3D973C, -unk_20CC, rwCOMBINEPRECONCAT);
                    unk_20CC = 0.0f;
                    unk_20D4 = 0.0f;
                }
            }
        }
        unk_20E8 = 0;
    }
    else if (unk_20E8)
        bp_4 = 1;
    if (bp_4)
    {
        fp_40 = unk_4B9308.sub_EE8F0(unk_3D8, 5);
        if (fp_40 != 0.0f)
        {
        }
    }
    lv_10 = frm_24->unk_458;
    if (unk_19D0 == 7)
        lv_10 = 3;
    switch (lv_10)
    {
    case 3:
    case 4:
    case 5:
    case 6:
    case 23:
        bp_8 = slot_C->unk_10C;
        l1C = slot_C->unk_110;
        if (unk_1B20)
        {
            loc44 = slot_C->unk_104;
            w48 = slot_C->unk_108;
#ifdef CODFH_SP // SP 0xCC3D0 scales the recoil by the difficulty (sp_sub_BF950)
            x4C = stance_recoil(unk_1A04, slot_C) * sp_sub_BF950() * ebp_14;
#else
            x4C = stance_recoil(slot_C, unk_1A04) * ebp_14 * 1.0f;
#endif
            if (frm_24->unk_230)
                x4C *= 0.1f;
            loc44 *= x4C;
            w48 *= x4C;
            unk_20C4 = frand_range(-loc44, loc44);
            unk_20D0 = frand_range(-w48, w48);
        }
        else if (!unk_1B24 || unk_20C4 == 0.0f)
        {
            unk_20C4 = 0.0f;
            unk_20D0 = 0.0f;
            bp_8 = slot_C->unk_114;
            l1C = slot_C->unk_118;
        }
        break;
    case 0:
    case 1:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        bp_8 = slot_C->unk_F4;
        l1C = slot_C->unk_F8;
        if (unk_1B20)
        {
            loc50 = slot_C->unk_EC;
            l54 = slot_C->unk_F0;
#ifdef CODFH_SP
            slot_58 = stance_recoil(unk_1A04, slot_C) * sp_sub_BF950() * ebp_14;
#else
            slot_58 = stance_recoil(slot_C, unk_1A04) * ebp_14 * 1.0f;
#endif
            loc50 *= slot_58;
            l54 *= slot_58;
            add_bounded(unk_20C4, loc50, 1000.0f);
            add_bounded(unk_20D0, l54, 1000.0f);
        }
        else if (!unk_1B24 || unk_20C4 == 0.0f)
        {
            unk_20C4 = 0.0f;
            unk_20D0 = 0.0f;
            bp_8 = slot_C->unk_FC;
            l1C = slot_C->unk_100;
        }
        break;
    case 2:
    case 7:
    case 8:
    case 9:
    case 10:
    case 24:
    case 37:
        bp_8 = slot_C->unk_12C;
        l1C = slot_C->unk_130;
        if (unk_1B20)
        {
            unk_20DC--;
            if (unk_20DC < 0)
            {
                unk_20DC = 0;
                y5C = slot_C->unk_11C;
                stk_60 = slot_C->unk_120;
#ifdef CODFH_SP
                var_64 = stance_recoil(unk_1A04, slot_C) * sp_sub_BF950() * ebp_14;
#else
                var_64 = stance_recoil(slot_C, unk_1A04) * ebp_14 * 1.0f;
#endif
                if (frm_24->unk_230)
                    var_64 *= 0.1f;
                y5C *= var_64;
                stk_60 *= var_64;
                add_bounded(unk_20C4, y5C, slot_C->unk_124);
                add_bounded(unk_20D0, stk_60, slot_C->unk_128);
            }
        }
        else if (!unk_1B24 || unk_20C4 == 0.0f)
        {
            unk_20C4 = 0.0f;
            unk_20D0 = 0.0f;
            bp_8 = slot_C->unk_134;
            l1C = slot_C->unk_138;
        }
        break;
    }
    sub_112DA0(&unk_20C8, unk_20C4, &unk_20D8, bp_8, l1C, 10000.0f, arg_4);
    sub_112DA0(&unk_20CC, unk_20D0, &unk_20D4, bp_8, l1C, 10000.0f, arg_4);
    if (unk_1B20)
        unk_4B9308.sub_EED30(unk_3D8, slot_C->unk_148, slot_C->unk_14C, slot_C->unk_14D);
    m_18 = 0.0f;
    t20 = 0.0f;
    if (unk_1B04 && !unk_1B0C && !unk_50C)
    {
        q68 = 1.0f;
        if (unk_1A0C)
        {
            if (!unk_1A08 && unk_1A04 == 1)
                q68 = (flt_429B00 - 1.0f) * unk_1A10 + 1.0f;
            else if (unk_1A08 == 1 && !unk_1A04)
                q68 = (1.0f - flt_429B00) * unk_1A10 + flt_429B00;
            else if (unk_1A08 == 1 && unk_1A04 == 2)
                q68 = (flt_429B04 - flt_429B00) * unk_1A10 + flt_429B00;
            else if (unk_1A08 == 2 && unk_1A04 == 1)
                q68 = (flt_429B00 - flt_429B04) * unk_1A10 + flt_429B04;
        }
        else if (unk_1A04 == 1)
            q68 = slot_C->unk_160;
        else if (unk_1A04 == 2)
            q68 = slot_C->unk_164;
        unk_4FC += slot_C->unk_154;
        wrap_180(unk_4FC);
        unk_500 += slot_C->unk_150;
        wrap_180(unk_500);
        unk_504 = q68 * slot_C->unk_15C * sin_ref(unk_4FC);
        m_18 = unk_504;
        unk_508 = q68 * slot_C->unk_158 * sin_ref(unk_500);
        t20 = unk_508;
    }
    else
    {
        unk_4FC = 0.0f;
        unk_500 = 0.0f;
        unk_504 *= 0.9f;
        if (ABS(unk_504) < 0.1f)
            unk_504 = 0.0f;
        unk_508 *= 0.9f;
        if (ABS(unk_508) < 0.1f)
            unk_508 = 0.0f;
        m_18 = unk_504;
        t20 = unk_508;
        if (unk_504 == 0.0f && unk_508 == 0.0f)
            unk_50C = 0;
        else
            unk_50C = 1;
    }
    if (unk_4F0 > 0.01 || unk_4F0 < -0.01f)
    {
        q90 = unk_4F0 / flt_429ADC;
        if (q90 > 1.0f)
            q90 = 1.0f;
        else if (q90 < -1.0f)
            q90 = -1.0f;
        fp_8C = -(((frm_94 = q90 * flt_429B0C) * 0.017453292f) * 0.5f);
        fp_78.imag.x = 0.0f;
        fp_78.imag.y = 0.0f;
        fp_78.imag.z = (RwReal)sin(fp_8C);
        fp_78.real = (RwReal)cos(fp_8C);
#ifdef CODFH_SP // shape: SP 0xCC3D0 spells the last z accumulation separately.
        do {
            (&t88)->real = (arg_0)->real * (&fp_78)->real
                - RwV3dDotProductMacro(&(arg_0)->imag, &(&fp_78)->imag);
            RwV3dCrossProductMacro(&(&t88)->imag, &(arg_0)->imag, &(&fp_78)->imag);
            RwV3dIncrementScaledMacro(&(&t88)->imag, &(&fp_78)->imag, (arg_0)->real);
            (&t88)->imag.x += (arg_0)->imag.x * (&fp_78)->real;
            (&t88)->imag.y += (arg_0)->imag.y * (&fp_78)->real;
            (&t88)->imag.z = (&t88)->imag.z + ((arg_0)->imag.z * (&fp_78)->real);
        } while (0);
#else // MP 0x1116A0
        RtQuatMultiplyMacro(&t88, arg_0, &fp_78);
#endif
        arg_0->imag.x = t88.imag.x;
        arg_0->imag.y = t88.imag.y;
        arg_0->imag.z = t88.imag.z;
        arg_0->real = t88.real;
    }
    if (m_18 != 0.0f || t20 != 0.0f || unk_20C8 != 0.0f || unk_20CC != 0.0f)
    {
        lv_E4.imag.x = (RwReal)sin(p98 = -(((ebp_9C = m_18 + unk_20C8) * 0.017453292f) * 0.5f));
        lv_E4.imag.y = 0.0f;
        lv_E4.imag.z = 0.0f;
        lv_E4.real = (RwReal)cos(p98);
        frm_D4 = -(((pC0 = t20 + unk_20CC) * 0.017453292f) * 0.5f);
        uD0.imag.x = 0.0f;
        uD0.imag.y = (RwReal)sin(frm_D4);
        uD0.imag.z = 0.0f;
        uD0.real = (RwReal)cos(frm_D4);
#ifdef CODFH_SP // shape: SP 0xCC3D0 shares the zero-axis product and retains product references.
        do {
            locAC.real = uD0.real * lv_E4.real - RwV3dDotProductMacro(&uD0.imag, &lv_E4.imag);
            RwV3dCrossProductMacro(&locAC.imag, &uD0.imag, &lv_E4.imag);
            RwV3dIncrementScaledMacro(&locAC.imag, &lv_E4.imag, uD0.real);
            // uD0's x and z components are both zero; keep their common product once.
            RwReal product = uD0.imag.x * lv_E4.real;
            locAC.imag.x += product;
            locAC.imag.y += uD0.imag.y * lv_E4.real;
            locAC.imag.z += product;
        } while (0);
        do {
            (&frm_BC)->real = (arg_0)->real * (&locAC)->real
                - RwV3dDotProductMacro(&(arg_0)->imag, &(&locAC)->imag);
            RwV3dCrossProductMacro(&(&frm_BC)->imag, &(arg_0)->imag, &(&locAC)->imag);
            {
                const RwReal &v = (&locAC)->imag.x * (arg_0)->real;
                (&frm_BC)->imag.x = (&frm_BC)->imag.x + v;
            }
            {
                const RwReal &v = (&locAC)->imag.y * (arg_0)->real;
                (&frm_BC)->imag.y = (&frm_BC)->imag.y + v;
            }
            {
                const RwReal &v = (&locAC)->imag.z * (arg_0)->real;
                (&frm_BC)->imag.z = (&frm_BC)->imag.z + v;
            }
            RwV3dIncrementScaledMacro(&(&frm_BC)->imag, &(arg_0)->imag, (&locAC)->real);
        } while (0);
#else // MP 0x1116A0
        RtQuatMultiplyMacro(&locAC, &uD0, &lv_E4);
        RtQuatMultiplyMacro(&frm_BC, arg_0, &locAC);
#endif
        arg_0->imag.x = frm_BC.imag.x;
        arg_0->imag.y = frm_BC.imag.y;
        arg_0->imag.z = frm_BC.imag.z;
        arg_0->real = frm_BC.real;
    }
}

// match: ?sub_112DA0@@YAXPAMM0MMMM@Z @ 0x00112DA0
// sp-match: ?sub_112DA0@@YAXPAMM0MMMM@Z @ 0x000C7980
// Runs the spring sub_112EB0 once per half frame of arg_18 (0.5 to 4 of them),
// the fraction left over as a partial step.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_112DA0(RwReal *arg_0, RwReal arg_4, RwReal *arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                RwReal arg_18)
{
    RwReal l4;
    RwReal var_8;
    RwInt32 fp_C;
    RwInt32 local_10;
    RwReal stk_14;
    RwReal lcl_18;
    RwInt32 fp_1C;

    l4 = clamp_f(arg_18 * 0.5f, 0.5f, 4.0f);
    fp_1C = (RwInt32)l4;
    fp_C = fp_1C;
    for (local_10 = 0; local_10 < fp_C; local_10++)
    {
        sub_112EB0(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
    }
    var_8 = l4 - fp_C;
    if (var_8 > 0.05f)
    {
        lcl_18 = *arg_0;
        stk_14 = *arg_8;
        sub_112EB0(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
        *arg_0 = (*arg_0 - lcl_18) * var_8 + lcl_18;
        *arg_8 = (*arg_8 - stk_14) * var_8 + stk_14;
    }
}

// match: ?sub_112EB0@@YAXPAMM0MMM@Z @ 0x00112EB0
// sp-match: ?sub_112EB0@@YAXPAMM0MMM@Z @ 0x000C3CB0
void sub_112EB0(RwReal *arg_0, RwReal arg_4, RwReal *arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14)
{
    RwReal var_4;

    *arg_8 = (var_4 = arg_4 - *arg_0) * arg_C + arg_10 * *arg_8;
    if (*arg_8 > arg_14)
    {
        *arg_8 = arg_14;
    }
#ifdef CODFH_SP
    // shape: operands swapped for /O2
    else if (*arg_8 < -arg_14)
#else
    else if (-arg_14 > *arg_8)
#endif
    {
        *arg_8 = -arg_14;
    }
    *arg_0 = *arg_0 + *arg_8;
}

// match: ?sub_112F20@@YAXPAURwV3d@@00M@Z @ 0x00112F20
#ifdef CODFH_SP
// SP expands it inside sub_112FC0 (0xC3D40)
inline
#endif
void sub_112F20(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C)
{
    arg_0->x = (((arg_8->x) - (arg_4->x)) * (arg_C)) + (arg_4->x);
    arg_0->y = (((arg_8->y) - (arg_4->y)) * (arg_C)) + (arg_4->y);
    arg_0->z = (((arg_8->z) - (arg_4->z)) * (arg_C)) + (arg_4->z);
}

// match: ?sub_112F80@@YAMMMM@Z @ 0x00112F80
// sp-match: ?sub_112F80@@YAMMMM@Z @ 0x000C3D10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_112F80(RwReal arg_0, RwReal arg_4, RwReal arg_8)
{
    RwReal bp_8;
    RwReal bp_4;

    bp_8 = arg_8 * arg_8;
#ifdef CODFH_SP
    // shape: the -2 product first, then += (SP keeps the fmul by -2)
    bp_4 = (bp_8 * arg_8) * -2.0f;
    bp_4 += bp_8 * 3.0f;
#else
    bp_4 = -2.0f * bp_8 * arg_8 + 3.0f * bp_8;
#endif
    return (arg_4 - arg_0) * bp_4 + arg_0;
}

// match: ?sub_112FC0@@YAXPAURwV3d@@00M@Z @ 0x00112FC0
// sp-match: ?sub_112FC0@@YAXPAURwV3d@@00M@Z @ 0x000C3D40
void sub_112FC0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C)
{
    RwReal bp_8;
    RwReal bp_4;

    bp_8 = arg_C * arg_C;
#ifdef CODFH_SP
    // shape: the -2 product first, then += (SP keeps the fmul by -2)
    bp_4 = (bp_8 * arg_C) * -2.0f;
    bp_4 += bp_8 * 3.0f;
#else
    bp_4 = -2.0f * bp_8 * arg_C + 3.0f * bp_8;
#endif
    sub_112F20(arg_0, arg_4, arg_8, bp_4);
}

// The collision step. From its last place (unk_440) towards the new one
// (unk_434), in two steps when the time is long or a wall is met (then the
// target is pulled 10 back from the wall), the eye height springs back
// (unk_524); each step moves the frame and collides it (sub_96EF0) with
// radii by its stance, keeping 0.01 off a wall. A pulse zone's charge dies
// on landing; the highest point of a fall is kept, a fall too long by its
// time kills it, and landing (from a jump or a fall) sets its jump's wait,
// its landing sound (by the surface) or its fall damage by the height (a
// damage message of 100 past the trigger's limit), and the surface under
// it. The frame then springs to the result (sub_112DA0 on each axis).
// match: ?vf_044@type_10F710@@UAEXM@Z @ 0x00113010
// sp-match: ?vf_044@type_10F710@@UAEXM@Z @ 0x000C7A80
void type_10F710::vf_044(RwReal arg_0)
{
    RwReal lcl_A4;
    RwReal lcl_A0;
    type_712B0_10F710 *ebp_9C;
#ifndef CODFH_SP
    RwV3d p98;
    RwReal fp_8C;
#endif
    RwInt32 t88;
    RwInt32 ebp_84;
#ifndef CODFH_SP
    RwV3d r80;
#endif
    RwInt32 frm_74;
    RwReal s70;
    RwInt32 m_6C;
#ifndef CODFH_SP
    RwV3d q68;
#endif
    RwInt32 y5C;
#ifndef CODFH_SP
    RwV3d slot_58;
    RwReal o4C;
#endif
    RwV3d *q48;
    RwInt32 v44;
    RwV3d stk_40;
    RwV3d local_34;
    RwV3d slot_28;
    RwV3d l1C;
    type_4E5E40 *lv_10;
    RwMatrix *slot_C;
    type_4E5E40_08 *bp_8;
    RwFrame *bp_4;

    lv_10 = &dword_4E5E40;
    bp_8 = lv_10->unk_08;
    bp_4 = unk_338.unk_08;
    if (!bp_4)
        return;
    if ((slot_C = RwFrameGetMatrix(bp_4)) == 0)
        return;
    q48 = &slot_C->pos;
#ifdef CODFH_DRAW_TRIGGERS
    // (the debug tools: noclip for the local player, port/src/debug/trigdraw.cpp; no collision,
    // no fall, the last and target places kept with the frame)
    if (g_bTrigDrawNoclip && (void *)this == (void *)sub_1745A0(0))
    {
        TrigDrawNoclipMove(q48, arg_0);
        unk_434 = *q48;
        unk_440 = *q48;
        unk_510 = -1000000.0f;
        unk_518 = 0.0f;
        RwFrameUpdateObjects(bp_4);
        return;
    }
#endif
    l1C = *q48;
    RwV3dSubMacro(&stk_40, &unk_434, &unk_440);
    if (arg_0 > 2.0f)
    {
        v44 = 2;
        RwV3dScaleMacro(&stk_40, &stk_40, 0.5f);
    }
    else
        v44 = 1;
    if (sub_FCAE0(&unk_440, &unk_434, &local_34, &slot_28, 0x10000, 1, 0))
    {
#ifdef CODFH_SP // shape: block-scoped locals here and below, so /O2 shares their slots (SP 0xC7A80's frame)
        RwV3d slot_58;
        RwReal o4C;

#endif
        RwV3dSubMacro(&slot_58, &unk_440, &local_34);
        o4C = RwV3dLength((RwV3d *)&slot_58);
        if (o4C != 0.0f)
        {
            RwV3dScaleMacro(&slot_58, &slot_58, 10.0f / o4C);
            RwV3dAddMacro(&unk_434, &local_34, &slot_58);
            if (v44 == 1)
            {
                v44 = 2;
                RwV3dScaleMacro(&stk_40, &stk_40, 0.5f);
            }
        }
    }
    sub_112DA0(&unk_524, 0.0f, &unk_528, flt_429724, flt_429728, flt_42972C, arg_0);
    *q48 = unk_440;
    for (y5C = 0; y5C < v44; y5C++)
    {
#ifdef CODFH_SP
        RwV3d r80;
        RwV3d q68;

#endif
        r80 = *q48;
        RwV3dAddMacro(q48, &stk_40, q48);
        RwFrameUpdateObjects(bp_4);
        frm_74 = 0;
        t88 = 0;
        ebp_84 = 0;
        m_6C = 0;
        q68.x = flt_429B1C * unk_4C;
        q68.y = unk_48 - unk_524;
        q68.z = q68.x;
        sub_96EF0(this, bp_4, &unk_3C_v, unk_420, &frm_74, &q68, &s70, &t88, &ebp_84, &m_6C, flt_429B10[unk_1A04],
                  flt_429B28[unk_1A04], 0);
        RwFrameUpdateObjects(bp_4);
        if (sub_FCAE0(&r80, q48, &local_34, 0, 0x10000, 1, 0))
        {
#ifdef CODFH_SP
            RwV3d p98;
            RwReal fp_8C;

#endif
            RwV3dSubMacro(&p98, &r80, &local_34);
            fp_8C = RwV3dLength((RwV3d *)&p98);
            if (fp_8C > 0.01f)
            {
                RwV3dScaleMacro(&p98, &p98, q68.x / fp_8C);
                RwV3dAddMacro(q48, &local_34, &p98);
                RwFrameUpdateObjects(bp_4);
            }
        }
        if (m_6C && unk_520)
        {
            if (vf_17C() > 0.0f)
                dword_44E8B8 = unk_1C0.sub_8A980(&dword_4AF000, this, 0, sub_CD550(), 0, 0);
            vf_178(0);
        }
        if (dword_429B3C && !((unk_28 >> 1) & 1) && unk_19D0 != 0xD)
        {
            if (q48->y > unk_510)
                unk_510 = q48->y;
        }
        else
            unk_510 = -1000000.0f;
        if (unk_19D0 == 2 || unk_19D0 == 3 || unk_19D0 == 1 && unk_DC < 0.0f)
        {
            unk_518 += clamp_f(arg_0 * 0.5f, 0.5f, 4.0f);
            if (unk_518 >= flt_429B38)
                vf_178(0);
        }
        else
            unk_518 = 0.0f;
        if ((unk_19D0 == 2 || unk_19D0 == 3 || unk_19D0 == 1 && unk_DC < 0.0f) && m_6C)
        {
            unk_518 = 0.0f;
            unk_28 |= 2;
            sub_1090F0(3);
            ebp_9C = (type_712B0_10F710 *)unk_344.unk_08;
            if (ebp_9C && ebp_9C->vf_008() != 1)
            {
                ebp_9C = 0;
            }
            if (!ebp_9C)
                unk_408 = flt_429718;
            else
            {
                lcl_A4 = (-unk_DC - ebp_9C->unk_1D8) * 0.03846154f;
                if (lcl_A4 > 1.0f)
                    lcl_A4 = 1.0f;
                else if (lcl_A4 < 0.0f)
                    lcl_A4 = 0.0f;
                unk_408 = (flt_42971C - flt_429718) * lcl_A4 + flt_429718;
            }
            lcl_A0 = unk_510 - q48->y;
            if (unk_514 && lcl_A0 > ebp_9C->unk_23C)
            {
                unk_52C = flt_429B34;
                if (lcl_A0 > ebp_9C->unk_240 || unk_520)
                {
                    if (vf_17C() > 0.0f)
                        dword_44E8B8 = unk_1C0.sub_8A980(&dword_4AF000, this, 0, sub_CD550(), 0, 0);
                    vf_178(0);
#ifndef CODFH_SP // SP 0xC7A80 sends no damage message
                    type_3DA434 msg_B4;

                    msg_B4.sub_1C5A80(100.0f);
                    msg_B4.unk_08 = 0;
                    msg_B4.unk_04 = 0;
                    sub_1ACBA0(unk_4F7EB8.sub_1AEC70(), &msg_B4);
#endif
                }
                else
                {
                    RwReal frm_C0;
                    RwReal uBC;
                    RwReal lcl_B8;

                    frm_C0 = (lcl_A0 - ebp_9C->unk_23C) / (ebp_9C->unk_240 - ebp_9C->unk_23C);
                    lcl_B8 = (uBC = vf_17C()) - frm_C0;
                    if (lcl_B8 < 0.0f)
                        lcl_B8 = 0.0f;
                    vf_23C(lcl_B8);
                    if (lcl_B8 > 0.0f)
                        unk_1C0.sub_8A980(&dword_4B1B10, this, 0, sub_CD550(), 0, 0);
                    else
                    {
                        dword_44E8B8 = unk_1C0.sub_8A980(&dword_4AF000, this, 0, sub_CD550(), 0, 0);
#ifndef CODFH_SP
                        type_3DA434 msg_D0;

                        msg_D0.sub_1C5A80(100.0f);
                        msg_D0.unk_08 = 0;
                        msg_D0.unk_04 = 0;
                        sub_1ACBA0(unk_4F7EB8.sub_1AEC70(), &msg_D0);
#endif
                    }
                }
            }
            else if (unk_514)
                unk_1C0.sub_8AA70(&dword_4AEFF8, bp_8[unk_294].unk_00, this, 0, sub_CD550(), 0, 0);
            unk_514++;
            unk_428 = flt_429740;
            unk_DC = 0.0f;
            unk_420 = s70;
        }
        else if (((unk_28 >> 1) & 1) && !m_6C && (unk_19D0 == 0 || unk_19D0 == 0xE && !unk_215C))
        {
            unk_28 &= ~2;
            sub_1090F0(2);
        }
        else if (((unk_28 >> 1) & 1) && m_6C)
            unk_420 = s70;
    }
    RwFrameUpdateObjects(bp_4);
    unk_434 = *q48;
    sub_112DA0(&l1C.x, unk_434.x, &unk_CC.x, flt_429724, flt_429728, flt_42972C, arg_0);
    sub_112DA0(&l1C.y, unk_434.y, &unk_CC.y, flt_429724, flt_429728, flt_42972C, arg_0);
    sub_112DA0(&l1C.z, unk_434.z, &unk_CC.z, flt_429724, flt_429728, flt_42972C, arg_0);
    *q48 = l1C;
    RwFrameUpdateObjects(bp_4);
    unk_440 = unk_434;
}

// match: ?vf_210@type_10F710@@UAEXPAUtype_D05C0@@@Z @ 0x00113D40
// sp-match: ?vf_210@type_10F710@@UAEXPAUtype_D05C0@@@Z @ 0x000C3DA0
void type_10F710::vf_210(type_D05C0 *arg_0)
{
    if (unk_28_3 && unk_28_5 && !unk_28_7)
    {
        arg_0->unk_00.y += arg_0->unk_48;
    }
}

// State 12's movement (vf_040): its turn velocity (unk_F0) takes its turn
// (unk_E4), its yaw rate kept within 80; past a thousandth it turns the
// frame arg_0 by it, and with an animation its two root matrices
// (unk_100, unk_140) turn with it about the second's position, the first
// placed again by the turned offset until it lies within 1e8 in height.
// arg_4 is unused.
// match: ?sub_113D90@type_10F710@@QAEXPAURwFrame@@M@Z @ 0x00113D90
// sp-match: ?sub_113D90@type_10F710@@QAEXPAURwFrame@@M@Z @ 0x000C3DC0
void type_10F710::sub_113D90(RwFrame *arg_0, RwReal arg_4)
{
    RwMatrix *v_8;
    RwMatrix *v_C;
    RwV3d v_18;
    RwInt32 v_1C;
    RwMatrix v_60;
    RwMatrix v_A0;
    RwMatrix v_E0;
    RwV3d v_F0;
    RwV3d v_FC;
    RwMatrix *v_100;

    v_8 = 0;
    v_C = 0;
    v_18.x = 0.0f;
    v_18.y = 0.0f;
    v_18.z = 0.0f;
    v_1C = 0;
    RwV3dAddMacro(&unk_F0_v, &unk_F0_v, &unk_E4_v);
    if (unk_F4 > 80.0f)
        unk_F4 = 80.0f;
    else if (unk_F4 < -80.0f)
        unk_F4 = -80.0f;
    if (unk_284)
    {
        v_8 = &v_60;
        v_C = &v_A0;
        RwMatrixSetIdentityMacro(&v_60);
        RwMatrixSetIdentityMacro(&v_A0);
        v_60 = *(RwMatrix *)&unk_284->unk_100;
        v_A0 = *(RwMatrix *)&unk_284->unk_140;
        v_18.x = v_8->pos.x - v_C->pos.x;
        v_18.y = v_8->pos.y - v_C->pos.y;
        v_18.z = v_8->pos.z - v_C->pos.z;
        RwMatrixSetIdentityMacro(&v_E0);
        v_E0.pos = v_C->pos;
        RwMatrixUpdate(&v_E0);
    }
    if (ABS(unk_F4) > 0.001f)
    {
        RwFrameRotate(arg_0, &stru_3D973C, unk_F4, rwCOMBINEPRECONCAT);
        if (v_8)
        {
            RwMatrixRotate(v_8, &stru_3D973C, unk_F4, rwCOMBINEPRECONCAT);
            RwMatrixRotate(v_C, &stru_3D973C, unk_F4, rwCOMBINEPRECONCAT);
            RwMatrixRotate(&v_E0, &stru_3D973C, unk_F4, rwCOMBINEPRECONCAT);
            v_1C = 1;
        }
    }
    if (v_1C && v_8)
    {
        v_F0 = v_18;
        while (1)
        {
            sub_1414C0(&v_FC, &v_18, &v_E0);
            v_8->pos = v_FC;
            RwMatrixUpdate(v_8);
            if (v_8->pos.y < -100000000.0f || v_8->pos.y > 100000000.0f)
                v_18 = v_F0;
            else
                break;
        }
    }
    if (v_8)
    {
        v_100 = (RwMatrix *)&unk_284->unk_100;
        *v_100 = *v_8;
        v_100 = (RwMatrix *)&unk_284->unk_140;
        *v_100 = *v_C;
    }
    RwFrameUpdateObjects(arg_0);
}

// match: ?vf_040@type_10F710@@UAEXM@Z @ 0x001142B0
// sp-match: ?vf_040@type_10F710@@UAEXM@Z @ 0x000C41D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::vf_040(RwReal arg_0)
{
    RwV3d *loc44;
#ifndef CODFH_SP
    RwV3d fp_40;
    RwV3d r34;
#endif
    RwReal q28;
    type_712B0_10F710 *frm_24;
    RwReal t20;
    RwReal l1C;
    RwV3d m_18;
    RwMatrix *slot_C;
    RwInt32 bp_8;
    RwFrame *bp_4;

    bp_4 = unk_338.unk_08;
    if (!bp_4)
    {
        return;
    }
    slot_C = RwFrameGetMatrix(bp_4);
    if (!slot_C)
    {
        return;
    }
    m_18 = slot_C->pos;
    bp_8 = dword_4B87D8;
    if (bp_8 - unk_424 > 2)
    {
        l1C = unk_1A00;
        unk_420 = m_18.y - l1C;
        unk_434 = m_18;
        set_v3d(&unk_CC, 0.0f, 0.0f, 0.0f);
        unk_440 = m_18;
        unk_524 = flt_429B10[unk_1A04];
        unk_528 = 0;
    }
    unk_424 = bp_8;
    if (unk_19D0 == 12 && unk_284)
    {
        if (!unk_430)
        {
            unk_430 = 1;
            unk_E0 = 0.0f;
            unk_DC = 0.0f;
            unk_D8 = 0.0f;
            unk_518 = 0;
        }
        sub_113D90(bp_4, arg_0);
        unk_420 = m_18.y;
        unk_434 = m_18;
        set_v3d(&unk_CC, 0.0f, 0.0f, 0.0f);
        unk_440 = m_18;
    }
    else
    {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares their slots with m_18 (SP 0xC41D0's frame)
        RwV3d r34;
        RwV3d fp_40;
#endif
        unk_430 = 0;
#ifdef CODFH_SP // SP 0xC41D0 calls the out-of-line sp_sub_BF9B0
        t20 = sp_sub_BF9B0(arg_0);
#else
        t20 = clamp_real(arg_0 * 0.5f, 0.5f, 4.0f);
#endif
        if (!unk_42C)
        {
            if (dword_4B87DC == 2)
            {
                unk_42C = 1;
                unk_DC *= t20;
            }
        }
        else if (dword_4B87DC != 2)
        {
            unk_42C = 0;
        }
        RwV3dScale(&r34, &unk_C0, t20);
        sub_141320(&fp_40, &r34, slot_C);
        unk_D8 = fp_40.x;
        unk_E0 = fp_40.z;
        unk_DC += r34.y;
        if (((unk_28 >> 3) & 1) && !((unk_28 >> 7) & 1) && !((unk_28 >> 1) & 1))
        {
            unk_DC += (t20 * t20) * unk_108;
            if (unk_DC < -60.0f)
            {
                unk_DC = -60.0f;
            }
        }
        unk_420 = unk_420 + unk_DC;
        unk_434.x = unk_434.x + unk_D8;
        unk_434.z = unk_434.z + unk_E0;
        q28 = unk_1A00;
        unk_434.y = q28 + unk_420 - unk_524;
        frm_24 = (type_712B0_10F710 *)unk_344.unk_08;
        if (frm_24 && frm_24->vf_008() != 1)
        {
            frm_24 = 0;
        }
        if (frm_24->unk_140)
        {
            loc44 = RwMatrixGetPos(slot_C);
            *loc44 = unk_434;
            unk_440 = *loc44;
            RwFrameUpdateObjects(bp_4);
        }
        RwFrameRotate(bp_4, &stru_3D973C, unk_E8, rwCOMBINEPRECONCAT);
    }
    unk_C0.z = 0.0f;
    unk_C0.y = 0.0f;
    unk_C0.x = 0.0f;
    unk_E4_v.z = 0.0f;
    unk_E4_v.y = 0.0f;
    unk_E4_v.x = 0.0f;
}

// match: ?vf_0C0@type_10F710@@UAEXPAURwV3d@@@Z @ 0x00114790
// sp-match: ?vf_0C0@type_10F710@@UAEXPAURwV3d@@@Z @ 0x000C4500
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::vf_0C0(RwV3d *arg_0)
{
    RwMatrix *l1C;
    RwV3d m_18;
    RwMatrix *slot_C;
    RwReal bp_8;
    RwV3d *bp_4;

    bp_4 = RwMatrixGetPos(RwFrameGetMatrix(get_unk_340()));
    if (unk_284)
    {
        m_18.x = arg_0->x - bp_4->x;
        m_18.y = arg_0->y - bp_4->y;
        m_18.z = arg_0->z - bp_4->z;
        l1C = &unk_284->unk_100;
        l1C->pos.x += m_18.x;
        l1C->pos.y += m_18.y;
        l1C->pos.z += m_18.z;
        slot_C = &unk_284->unk_140;
        slot_C->pos.x += m_18.x;
        slot_C->pos.y += m_18.y;
        slot_C->pos.z += m_18.z;
    }
    bp_8 = arg_0->y - bp_4->y;
    unk_420 += bp_8;
    *bp_4 = *arg_0;
    unk_434 = *bp_4;
    unk_440 = *bp_4;
    set_v3d(&unk_CC, 0.0f, 0.0f, 0.0f);
    RwFrameUpdateObjects(get_unk_340());
}

// match: ?sub_114920@type_10F710@@QAEXPAVLadderTrigger@@@Z @ 0x00114920
// sp-match: ?sub_114920@type_10F710@@QAEXPAVLadderTrigger@@@Z @ 0x000C4610
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_114920(LadderTrigger *arg_0)
{
    RwReal ebp_3C;
    RwMatrix *lcl_38;
    RwV3d *r34;
    RwV3d lv_30;
    RwReal frm_24;
    RwV3d loc20;
    bool loc11;
    RwV3d lv_10;
    RwReal bp_4;

    loc11 = false;
    lv_30.x = 0.0f;
    lv_30.y = arg_0->get_unk_4C();
    lv_30.z = 0.0f;
    sub_1414C0(&lv_30, &lv_30, (RwMatrix *)arg_0->unk_60);
    loc20.x = 0.0f;
    loc20.y = -arg_0->get_unk_4C();
    loc20.z = 0.0f;
    sub_1414C0(&loc20, &loc20, (RwMatrix *)arg_0->unk_60);
    r34 = (RwV3d *)vf_0C4();
    lv_10.x = r34->x;
    lv_10.y = r34->y - unk_48;
    lv_10.z = r34->z;
    bp_4 = sub_140C90(&lv_10, &lv_30);
    frm_24 = sub_140C90(&lv_10, &loc20);
    if (bp_4 < frm_24)
    {
        loc11 = true;
    }
    else
    {
        lcl_38 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
        ebp_3C = atan2(lcl_38->at.y, lcl_38->at.x) * 57.295776f;
        if (ebp_3C >= -15.0f)
        {
            loc11 = true;
        }
    }
    if (loc11)
    {
        sub_1090F0(0xD);
        unk_2178 = (type_10F710_2178 *)arg_0;
        unk_28 &= ~2;
        unk_51C = 0;
    }
}

// match: ?sub_114AA0@type_10F710@@QAEXM@Z @ 0x00114AA0
// sp-match: ?sub_114AA0@type_10F710@@QAEXM@Z @ 0x000CCEF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_114AA0(RwReal arg_0)
{
    RwV3d w48;
    RwV3d *ebp_3C;
    RwReal lcl_38;
    RwReal r34;
    RwV3d lv_30;
    RwMatrix *frm_24;
    RwMatrix *t20;
    type_4E5E40 *l1C;
    RwReal m_18;
    type_4E5E40_08 *ebp_14;
    RwV3d lv_10;
    type_712B0_10F710 *bp_4;

    l1C = &dword_4E5E40;
    ebp_14 = l1C->unk_08;
    bp_4 = (type_712B0_10F710 *)unk_344.unk_08;
    if (bp_4 && bp_4->vf_008() != 1)
    {
        bp_4 = 0;
    }
    unk_28 &= ~8;
    frm_24 = &unk_2178->unk_60;
    m_18 = unk_4B9308.sub_EE8F0(unk_3D8, 0);
    if ((dword_4B86F8 >> 6) & 1)
    {
        m_18 = 0.0f;
    }
    lcl_38 = m_18 * 100.0f * arg_0;
    t20 = RwFrameGetMatrix(RwCameraGetFrame((RwCamera *)dword_4E5C74));
    r34 = atan2(t20->at.y, t20->at.x) * 57.295776f;
    if (r34 < -15.0f)
    {
        lcl_38 = -lcl_38;
    }
    if (unk_2178->unk_D8 == 3 || (unk_2178->unk_D8 == 1 && lcl_38 < 0.0f)
        || (unk_2178->unk_D8 == 2 && lcl_38 > 0.0f))
    {
        lcl_38 = 0.0f;
    }
    ebp_3C = (RwV3d *)vf_0C4();
    RwV3dScale(&lv_30, &frm_24->up, lcl_38);
    w48.x = lv_30.x + frm_24->pos.x;
    w48.y = lv_30.y + ebp_3C->y;
    w48.z = lv_30.z + frm_24->pos.z;
    lv_10 = *ebp_3C;
    sub_112DA0(&lv_10.x, w48.x, (RwReal *)&unk_51C, 0.075f, 0.05f, 10.0f, arg_0);
    sub_112DA0(&lv_10.y, w48.y, (RwReal *)&unk_51C, 0.075f, 0.05f, 10.0f, arg_0);
    sub_112DA0(&lv_10.z, w48.z, (RwReal *)&unk_51C, 0.075f, 0.05f, 10.0f, arg_0);
    vf_0C0(&lv_10);
    set_v3d(&unk_D8_v, 0.0f, 0.0f, 0.0f);
    unk_134 = bp_4->unk_19C;
    sub_10A330(bp_4->unk_154, arg_0);
    sub_109AE0(bp_4->unk_1B4, arg_0);
    unk_294 = 0x12;
    sub_10C370(arg_0);
    m_18 = unk_4B9308.sub_EE8F0(unk_3D8, 4);
    if (m_18 != 0.0f && m_18 > 0.0f)
    {
        if (unk_1A04 == 1)
        {
            unk_C0.y = (m_18 * bp_4->unk_1E0);
        }
        else
        {
            unk_C0.y = (m_18 * bp_4->unk_1D8);
        }
        unk_19D4 = 0;
        unk_2178 = 0;
        sub_1090F0(1);
        unk_1C0.sub_8AA70(&dword_4B1B28, ebp_14[unk_294].unk_00, this, 0, sub_CD550(), 0, 0);
    }
}

// match: ?sub_114E70@type_10F710@@QAEXM@Z @ 0x00114E70
// sp-match: ?sub_114E70@type_10F710@@QAEXM@Z @ 0x000C4720
void type_10F710::sub_114E70(RwReal arg_0)
{
    RwV3d var_C;
    RwV3d *var_10;

    var_10 = (RwV3d *)vf_0C4();
    var_C.x = var_10->x;
    var_C.y = var_10->y - unk_48;
    var_C.z = var_10->z;
    if (!sub_144F20((RwV3d *)((RwReal *)&var_C), (Trigger *)((RwInt32)unk_2178)))
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("getting off the ladder because foot pos is not inside.\n");
#endif
        sub_1090F0(0);
        unk_2178 = 0;
    }
    else if ((unk_28 >> 1) & 1)
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("getting off the ladder because player is on ground.\n");
#endif
        set_v3d(&unk_D8_v, 0.0f, 0.0f, 0.0f);
        sub_1090F0(2);
        unk_2178 = 0;
    }
}

// match: ?sub_114F50@type_10F710@@QAEXXZ @ 0x00114F50
// sp-match: ?sub_114F50@type_10F710@@QAEXXZ @ 0x000C47B0
void type_10F710::sub_114F50()
{
    RwInt32 var_4;

    if (unk_2250)
    {
        var_4 = 0;
        sub_6B5F0("PlayerBlewStealth", 0, 0, 0, &var_4, 1, true, false);
    }
}

// match: ?sub_114F90@type_10F710@@QAEXPAUtype_114F90@@PAURwV3d@@@Z @ 0x00114F90
// sp-match: ?sub_114F90@type_10F710@@QAEXPAUtype_114F90@@PAURwV3d@@@Z @ 0x000C8300
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_10F710::sub_114F90(type_114F90 *arg_0, RwV3d *arg_4)
{
    RwReal q28;
    RwReal frm_24;
    RwReal t20;
    RwMatrix *l1C;
    type_3D3548 *m_18;
    RwReal ebp_14;
    type_114F90 *lv_10;
    RwV3d slot_C;

    lv_10 = arg_0;
    m_18 = unk_2110.sub_D4910();
    l1C = RwFrameGetMatrix(m_18->get_unk_340());
    RwV3dSub(&slot_C, arg_4, &l1C->pos);
    t20 = RwV3dLength(&slot_C);
    ebp_14 = lv_10->unk_6C;
    if (t20 < ebp_14)
    {
        frm_24 = 1.0f - t20 / ebp_14;
        ((type_3DD948 *)m_18)->sub_175E50(frm_24 * lv_10->unk_70, lv_10->unk_74, lv_10->unk_78);
    }
    ebp_14 = lv_10->unk_7C;
    if (t20 < ebp_14)
    {
        q28 = 1.0f - t20 / ebp_14;
        sub_1109A0(q28 * lv_10->unk_80, 1.0f);
    }
}

// match: ?sub_1150A0@type_10F710@@QAEXM@Z @ 0x001150A0
// sp-match: ?sub_1150A0@type_10F710@@QAEXM@Z @ 0x000C47F0
void type_10F710::sub_1150A0(RwReal arg_0)
{
    unk_19DC += arg_0;
    if (unk_19DC < 0.0f)
    {
        unk_19DC = 0.0f;
    }
    if (unk_19DC > 1.0f)
    {
        unk_19DC = 1.0f;
    }
}

// match: ?sub_115110@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x00115110
// sp-match: ?sub_115110@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x000C4840
RpCollisionTriangle *sub_115110(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8, void *arg_C)
{
    type_93DF0 *var_4;

    var_4 = (type_93DF0 *)arg_C;
    var_4->unk_60 = 1;
    return 0;
}

// match: ?sub_115130@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00115130
// sp-match: ?sub_115130@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000C4850
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_115130(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10)
{
    type_93DF0 *bp_8;
    type_3D3548 *bp_4;

    if (!arg_8->geometry)
    {
        return arg_8;
    }
    bp_8 = (type_93DF0 *)arg_10;
    bp_8->unk_60 = 0;
    bp_4 = sub_FB960(arg_8);
    if (bp_4)
    {
        if (!bp_4->unk_28_2)
        {
            return arg_8;
        }
        RpAtomicForAllIntersections(arg_8, arg_0, sub_115110, bp_8);
        if (bp_8->unk_60)
        {
            return 0;
        }
    }
    return arg_8;
}

// match: ?sub_1151B0@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x001151B0
// sp-match: ?sub_1151B0@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000C48B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *sub_1151B0(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                                RwReal arg_C, void *arg_10)
{
    type_93DF0 *lv_10;
    type_FC000 *slot_C;
    void *bp_8;
    RwUInt32 bp_4;

    lv_10 = (type_93DF0 *)arg_10;
    bp_8 = ((type_96E30 *)lv_10->unk_00)->unk_10[((type_92540 *)arg_4)->unk_80 +
                                                  ((type_92540 *)arg_4)->unk_04[arg_8->index].unk_06];
    slot_C = sub_FC000(bp_8);
    bp_4 = slot_C->unk_04 & 0xFFFF0000;
    if (lv_10->unk_74 & bp_4)
    {
        return arg_8;
    }
    lv_10->unk_60 = 1;
    return 0;
}

// match: ?sub_115230@@YAHPAURwV3d@@M@Z @ 0x00115230
// sp-match: ?sub_115230@@YAHPAURwV3d@@M@Z @ 0x000C4910
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_115230(RwV3d *arg_0, RwReal arg_4)
{
    type_4E5D30 *m_E0;
    type_4E5D30 *ebp_DC;
    RpIntersection t20;
    RwInt32 bp_4;

    t20.type = rpINTERSECTSPHERE;
    t20.t.sphere.center = *arg_0;
    t20.t.sphere.radius = arg_4;
    type_93DF0 lD8;
    lD8.unk_60 = 0;
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        ebp_DC = &dword_4E5D30[bp_4];
        if (ebp_DC->get_unk_00() && (lD8.unk_00 = ebp_DC->get_unk_28()))
        {
            RpCollisionWorldForAllIntersections(lD8.unk_00, &t20, sub_1151B0, &lD8);
        }
    }
    if (lD8.unk_60)
    {
        return 1;
    }
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        m_E0 = &dword_4E5D30[bp_4];
        if (m_E0->get_unk_00() && (lD8.unk_00 = m_E0->get_unk_28()))
        {
            RpWorldForAllAtomicIntersections(lD8.unk_00, &t20, sub_115130, &lD8);
        }
    }
    return lD8.unk_60;
}

// match: ?sub_115390@@YAXHH@Z @ 0x00115390
// sp-match: ?sub_115390@@YAXHH@Z @ 0x000C4A60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_115390(RwInt32 arg_0, RwInt32 arg_4)
{
    type_10F710 *stk_2C;
    RwChar slot_28[0x20];
    RwInt32 bp_4;

    stk_2C = (type_10F710 *)sub_1745A0(0);
    if (stk_2C && stk_2C->get_unk_1AE4() == 0x20)
    {
        arg_4 = 0;
        arg_0 = arg_4;
    }
    sprintf(slot_28, "%d", arg_0 > 99 ? 99 : arg_0);
    sub_EAB80(slot_28, 1);
#ifdef CODFH_SP // SP 0xC4A60 prints arg_4 unclamped
    sprintf(slot_28, "%d", arg_4);
#else
    bp_4 = arg_4;
    if (bp_4 > 999)
    {
        bp_4 = 999;
    }
    sprintf(slot_28, "%d", bp_4);
#endif
    sub_EAB80(slot_28, 2);
}
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@c0490fd0 @ 0x003D91BC
// match: __real@c1700000 @ 0x003D9308
// match: ?flt_3D9750@@3MB @ 0x003D9750
// match: ??_C@_0BJ@GCJOBHNE@Granadas?5de?5oso?5pegajoso?$AA@ @ 0x003D9754
// match: ??_C@_0BD@GODCHPLF@Pistola?5de?5engrase?$AA@ @ 0x003D9770
// match: ??_C@_0BB@GKPDMOGG@Coax?4?5de?5Sherman?$AA@ @ 0x003D9784
// match: ??_C@_0BB@POGGFADO@Ca?qon?5de?5Sherman?$AA@ @ 0x003D9798
// match: ??_C@_0BH@CKALKPGL@Granadas?5de?5oso?5Kaiser?$AA@ @ 0x003D97AC
// match: ??_C@_0N@ECIKMCAC@Minas?5Teller?$AA@ @ 0x003D97C4
// match: ??_C@_0BC@FAAOHLBJ@Munici?sn?5de?5Mosin?$AA@ @ 0x003D97D4
// match: ??_C@_0N@FCOCOJEC@Coax?4?5de?5T34?$AA@ @ 0x003D97E8
// match: ??_C@_0N@KCLDDKPJ@Ca?q?sn?5de?5T34?$AA@ @ 0x003D97F8
// match: ??_C@_0BB@KAGJJPJ@Granadas?5de?5palo?$AA@ @ 0x003D9808
// match: ??_C@_0BC@DEMFAHIN@Granadas?5de?5RGD33?$AA@ @ 0x003D981C
// match: ??_C@_0BC@CGDAIEFD@Granadas?5de?5Mark2?$AA@ @ 0x003D9830
// match: ??_C@_0BB@IECPOPEF@Granadas?5de?5humo?$AA@ @ 0x003D9844
// match: ??_C@_0BI@PGPLHJAC@Nagant?5de?5francotirador?$AA@ @ 0x003D9858
// match: ??_C@_06GEOGCGON@bazuca?$AA@ @ 0x003D9870
// match: ??_C@_0BA@CFEBLPPK@Granata?5adesiva?$AA@ @ 0x003D9878
// match: ??_C@_0BC@HNBCGJIO@Coassiale?5Sherman?$AA@ @ 0x003D9888
// match: ??_C@_0BA@HCMDHEDP@Cannone?5Sherman?$AA@ @ 0x003D989C
// match: ??_C@_0BD@PNIODFLB@Granata?5Kaiserbear?$AA@ @ 0x003D98AC
// match: ??_C@_0M@INLLHHEE@Mina?5Teller?$AA@ @ 0x003D98C0
// match: ??_C@_0BE@HHPDCGFB@Munizioni?5per?5Mosin?$AA@ @ 0x003D98CC
// match: ??_C@_0O@BDFBEBBK@Coassiale?5T34?$AA@ @ 0x003D98E0
// match: ??_C@_0M@JLNAHPBE@Cannone?5T34?$AA@ @ 0x003D98F0
// match: ??_C@_0O@MILEDJHN@Granate?5RGD33?$AA@ @ 0x003D98FC
// match: ??_C@_0O@NKEBLKKD@Granate?5Mark2?$AA@ @ 0x003D990C
// match: ??_C@_0BB@JAFFGHAL@Granate?5fumogene?$AA@ @ 0x003D991C
// match: ??_C@_0BD@KMHNJPNL@Nagant?5da?5cecchino?$AA@ @ 0x003D9930
// match: ??_C@_0BA@BMNEFDFH@Haftb?dr?9Granate?$AA@ @ 0x003D9944
// match: ??_C@_02MCEHGFCK@MP?$AA@ @ 0x003D9954
// match: ??_C@_07FJCBDDJH@Sherman?$AA@ @ 0x003D9958
// match: ??_C@_0BB@MPJMCLCO@Sherman?9Gesch?$PMtz?$AA@ @ 0x003D9960
// match: ??_C@_0BC@KNFKHGDI@Kaiserb?dr?9Granate?$AA@ @ 0x003D9974
// match: ??_C@_0L@LEOJFFPA@Tellermine?$AA@ @ 0x003D9988
// match: ??_C@_0P@DMCJLAH@Mosin?9Munition?$AA@ @ 0x003D9994
// match: ??_C@_03HNDBACI@T34?$AA@ @ 0x003D99A4
// match: ??_C@_0N@OKNNADKA@T34?9Gesch?$PMtz?$AA@ @ 0x003D99A8
// match: ??_C@_0BB@JDGKNKKL@Browning?5?450?5Kal?$AA@ @ 0x003D99B8
// match: ??_C@_0BB@HBIPIDKC@Stielhandgranate?$AA@ @ 0x003D99CC
// match: ??_C@_05DBGNABLE@Mark2?$AA@ @ 0x003D99E0
// match: ??_C@_0N@PECPMLCF@Rauchgranate?$AA@ @ 0x003D99E8
// match: ??_C@_0P@PIMDHECB@Nagant?9Scharfs?$AA@ @ 0x003D99F8
// match: ??_C@_0M@FLKOLANO@Panzerfaust?$AA@ @ 0x003D9A08
// match: ??_C@_0BE@DOBHCJHC@Grenades?5StickyBear?$AA@ @ 0x003D9A14
// match: ??_C@_0O@BCGNDIKJ@Sherman?5Coax?4?$AA@ @ 0x003D9A28
// match: ??_C@_0O@IBPBFHJI@canon?5Sherman?$AA@ @ 0x003D9A38
// match: ??_C@_0BE@KNOGPMOF@Grenades?5KaiserBear?$AA@ @ 0x003D9A48
// match: ??_C@_0N@ELGBGCHI@Mines?5Teller?$AA@ @ 0x003D9A5C
// match: ??_C@_0BA@PHCHJGPJ@Munitions?5Mosin?$AA@ @ 0x003D9A6C
// match: ??_C@_09DFNNBBEL@T34?5Coax?4?$AA@ @ 0x003D9A7C
// match: ??_C@_09LACIEBKN@Canon?5T34?$AA@ @ 0x003D9A88
// match: ??_C@_0BB@KDIIFCOI@Browning?5cal?4?550?$AA@ @ 0x003D9A94
// match: ??_C@_0BC@DHJICPHN@Stielhandgrenaten?$AA@ @ 0x003D9AA8
// match: ??_C@_0BA@JKGCGIGH@Grenades?5Mark?52?$AA@ @ 0x003D9ABC
// match: ??_C@_0N@DBDMNJEG@M8?5fumig?hnes?$AA@ @ 0x003D9ACC
// match: ??_C@_0BE@FDMNODOL@Nagant?5de?5pr?icision?$AA@ @ 0x003D9ADC
// match: ??_C@_04JBNLJMN@PPSh?$AA@ @ 0x003D9AF0
// match: ??_C@_0BD@LOGPPBKG@StickyBear?5Grenade?$AA@ @ 0x003D9AF8
// match: ??_C@_0L@HIPNIEFJ@Grease?5Gun?$AA@ @ 0x003D9B0C
// match: ??_C@_0N@GAHPEJG@Sherman?5Coax?$AA@ @ 0x003D9B18
// match: ??_C@_0P@OIBGCJEI@Sherman?5Cannon?$AA@ @ 0x003D9B28
// match: ??_C@_0BD@CKLJPHNA@KaiserBear?5Grenade?$AA@ @ 0x003D9B38
// match: ??_C@_0M@LDIGMDIF@Teller?5Mine?$AA@ @ 0x003D9B4C
// match: ??_C@_0BA@JBCDJFNI@Mosin?5Ammo?5Clip?$AA@ @ 0x003D9B58
// match: ??_C@_04JIAPCFOO@ST74?$AA@ @ 0x003D9B68
// match: ??_C@_08LEGPLMOH@T34?5Coax?$AA@ @ 0x003D9B70
// match: ??_C@_0L@KGDFBKDF@T34?5Cannon?$AA@ @ 0x003D9B7C
// match: ??_C@_06EPOMIJMP@Flak88?$AA@ @ 0x003D9B88
// match: ??_C@_06EDLJGGCO@Flak38?$AA@ @ 0x003D9B90
// match: ??_C@_0N@CBMONACC@MG42?5Mounted?$AA@ @ 0x003D9B98
// match: ??_C@_05GAHHHECF@Maxim?$AA@ @ 0x003D9BA8
// match: ??_C@_07NODEDNDE@M1919A4?$AA@ @ 0x003D9BB0
// match: ??_C@_0P@MKDLINEJ@Browning?550cal?$AA@ @ 0x003D9BB8
// match: ??_C@_0BB@OKBOMBLE@Stielhandgrenate?$AA@ @ 0x003D9BC8
// match: ??_C@_05CDJIICGK@RGD33?$AA@ @ 0x003D9BDC
// match: ??_C@_0L@KJCJAKMP@Mark2?5Frag?$AA@ @ 0x003D9BE4
// match: ??_C@_08HLELOLIG@M8?5Smoke?$AA@ @ 0x003D9BF0
// match: ??_C@_0M@LOMKCDIK@Springfield?$AA@ @ 0x003D9BFC
// match: ??_C@_0O@KNEPBFLO@Nagant?5Sniper?$AA@ @ 0x003D9C08
// match: ??_C@_05HCODPAPN@Kar98?$AA@ @ 0x003D9C18
// match: ??_C@_09LGFJFBBG@M1?5Garand?$AA@ @ 0x003D9C20
// match: ??_C@_0N@BAHCLMB@Mosin?5Nagant?$AA@ @ 0x003D9C2C
// match: ??_C@_03PHBGIBL@G43?$AA@ @ 0x003D9C3C
// match: ??_C@_07CGACLJAK@Enfield?$AA@ @ 0x003D9C40
// match: ??_C@_05PCHBCGPB@Luger?$AA@ @ 0x003D9C48
// match: ??_C@_08MEHPEFCE@Thompson?$AA@ @ 0x003D9C50
// match: ??_C@_04BHFBMFNA@Sten?$AA@ @ 0x003D9C5C
// match: ??_C@_04JMJJJNGP@PPSH?$AA@ @ 0x003D9C64
// match: ??_C@_04KOJHOAAH@MP40?$AA@ @ 0x003D9C6C
// match: ??_C@_04FBGPONKD@MG42?$AA@ @ 0x003D9C74
// match: ??_C@_07OMACFPLG@M1919A6?$AA@ @ 0x003D9C7C
// match: ??_C@_02MNJGFOKF@DP?$AA@ @ 0x003D9C84
// match: ??_C@_04GPLKCEDO@Bren?$AA@ @ 0x003D9C88
// match: ??_C@_03BGHDGIHE@BAR?$AA@ @ 0x003D9C90
// match: ??_C@_0O@NBALOBMP@Panzerschreck?$AA@ @ 0x003D9C94
// match: ??_C@_07DGFOPFBO@Bazooka?$AA@ @ 0x003D9CA4
// match: ??_C@_0FI@CNAPNLDK@NOTE?3?5?$CB?$CB?$CB?5Player?3?3Init?$CI?$CJ?3?5using?5@ @ 0x003D9F18
// match: ??_C@_0GD@FDKALMEF@NOTE?3?5?$CB?$CB?$CB?5Player?3?3SystemStartIni@ @ 0x003D9F70
// match: ??_C@_0CP@EFFNKGKF@WeaponDef?5?$CFd?5is?5missing?5select?5a@ @ 0x003D9FD4
// match: ??_C@_0DB@MGJMFPHA@WeaponDef?5?$CFd?5is?5missing?5deselect@ @ 0x003DA004
// match: ??_C@_0P@MKAOGAIJ@PickedUpWeapon?$AA@ @ 0x003DA038
// match: __real@c1a00000 @ 0x003DA048
// match: ??_C@_0L@PMDGMLDJ@HealthFull?$AA@ @ 0x003DA04C
// match: ??_C@_0CN@IJLGHBNA@WARNING?3?5Missing?5a?5bipod?5undeplo@ @ 0x003DA058
// match: ??_C@_0CL@BDBDOOLG@WARNING?3?5Missing?5a?5bipod?5deploy?5@ @ 0x003DA088
// match: __real@43af0000 @ 0x003DA0B4
// match: ??_C@_0EE@OBCPLLGH@GameDiff?3GetPlayerHealthPupMulti@ @ 0x003DA0B8
// match: __real@42aa0000 @ 0x003DA0FC
// match: __real@42820000 @ 0x003DA100
// match: ??_C@_0L@LLHEFNPC@ActionItem?$AA@ @ 0x003DA104
// match: ??_C@_0BD@JMKGJJHO@PickedUpStickyBear?$AA@ @ 0x003DA110
// match: ??_C@_0BD@PFHEMOJ@PickedUpKaiserBear?$AA@ @ 0x003DA124
// match: ??_C@_0BC@NFLNPFAO@PickedUpTeddyBear?$AA@ @ 0x003DA138
// match: ??_C@_0CL@KFOLFDPM@COD_HelpMessages?$CLGeneric?$CLError_I@ @ 0x003DA14C
// match: ??_C@_0CK@BOFNBPJC@COD_HelpMessages?$CLGeneric?$CLError_H@ @ 0x003DA178
// match: __real@3d4cccd0 @ 0x003DA1A4
// match: ??_C@_0CB@BPAFOFNM@WARNING?3?5Missing?5idle?5anim?3?50x?$CFx@ @ 0x003DA1A8
// match: ??_C@_0CC@LAJBKOOF@WARNING?3?5Missing?5start?5anim?3?50x?$CF@ @ 0x003DA1CC
// match: __real@c1f00000 @ 0x003DA1F0
// match: __real@3f75c28f @ 0x003DA1F4
// match: __real@3d23d710 @ 0x003DA1F8
// match: ??_C@_0EJ@HDKMLBNF@RwaVirtualVoiceSetGain?$CI?$CIRwaVirtu@ @ 0x003DA200
// match: ??_C@_0EP@HHDOEMCA@Audio?3?5WARNING?$CB?5Player?5on?5non?9ta@ @ 0x003DA250
// match: __real@3fb9999a @ 0x003DA2A0
// match: ??_C@_0DB@CNBFEFMM@Allocated?5?$CFd?5bytes?5for?5?$CFd?5CPlaye@ @ 0x003DA2A4
// match: ??_C@_0CF@MAIPEKMD@Initializing?5geometery?5for?5weapo@ @ 0x003DA2D8
// match: ??_C@_0GE@KGHLBCGF@?7UnInitializing?5geometry?5for?5wea@ @ 0x003DA300
// match: ??_C@_0FC@HIENKACG@Requesting?5to?5stream?5weapon?5?$CFd?5i@ @ 0x003DA368
// match: ??_C@_0FC@JPPLJGIG@Requesting?5to?5stream?5weapon?5?$CFd?5i@ @ 0x003DA3C0
// match: __real@3fa00000 @ 0x003DA414
// match: __real@4056800000000000 @ 0x003DA418
// match: __real@43110000 @ 0x003DA420
// match: __real@40c90fd0 @ 0x003DA424
// match: __real@3f847ae147ae147b @ 0x003DA428
// match: __real@c0000000 @ 0x003DA430
// match: ??_7type_3DA434@@6B@ @ 0x003DA434
// match: ??_7type_3DA440@@6B@ @ 0x003DA440
// match: ??_7type_3DA44C@@6B@ @ 0x003DA44C
// match: __real@3d1d89d9 @ 0x003DA458
// match: __real@c2a00000 @ 0x003DA45C
// match: __real@42a00000 @ 0x003DA460
// match: ??_C@_0DF@PHEINOLN@getting?5off?5the?5ladder?5because?5p@ @ 0x003DA464
// match: ??_C@_0DI@OAKEMDCG@getting?5off?5the?5ladder?5because?5f@ @ 0x003DA49C
// match: ??_C@_0BC@EKLFDPOC@PlayerBlewStealth?$AA@ @ 0x003DA4D4
// match: .CRT$XCU+0 @ 0x00427090
// match: ?byte_429700@@3EA @ 0x00429700
// match: ?dword_429704@@3HA @ 0x00429704
// match: ?flt_429708@@3MA @ 0x00429708
// match: ?flt_42970C@@3MA @ 0x0042970C
// match: ?flt_429710@@3MA @ 0x00429710
// match: ?flt_429714@@3MA @ 0x00429714
// match: ?flt_429718@@3MA @ 0x00429718
// match: ?flt_42971C@@3MA @ 0x0042971C
// match: ?flt_429720@@3MA @ 0x00429720
// match: ?flt_429724@@3MA @ 0x00429724
// match: ?flt_429728@@3MA @ 0x00429728
// match: ?flt_42972C@@3MA @ 0x0042972C
// match: ?flt_429730@@3MA @ 0x00429730
// match: ?flt_429734@@3MA @ 0x00429734
// match: ?flt_429738@@3MA @ 0x00429738
// match: ?flt_42973C@@3MA @ 0x0042973C
// match: ?flt_429740@@3MA @ 0x00429740
// match: ?dword_429744@@3HA @ 0x00429744
// match: ?flt_429748@@3MA @ 0x00429748
// match: ?flt_42974C@@3MA @ 0x0042974C
// match: ?dword_429750@@3MA @ 0x00429750
// match: ?dword_429754@@3MA @ 0x00429754
// match: ?dword_429758@@3HA @ 0x00429758
// match: ?dword_42975C@@3HA @ 0x0042975C
// match: ?dword_429760@@3HA @ 0x00429760
// match: ?off_429768@@3PAPBDA @ 0x00429768
// match: ?off_429808@@3PAPBDA @ 0x00429808
// match: ?off_4298A8@@3PAPBDA @ 0x004298A8
// match: ?off_429948@@3PAPBDA @ 0x00429948
// match: ?off_4299E8@@3PAPBDA @ 0x004299E8
// match: ?dword_429A84@@3PAPAPBDA @ 0x00429A84
// match: ?dword_429AA0@@3HA @ 0x00429AA0
// match: ?flt_429AA4@@3MA @ 0x00429AA4
// match: ?flt_429AA8@@3MA @ 0x00429AA8
// match: ?flt_429AAC@@3MA @ 0x00429AAC
// match: ?flt_429AB0@@3MA @ 0x00429AB0
// match: ?flt_429AB4@@3MA @ 0x00429AB4
// match: ?flt_429AB8@@3MA @ 0x00429AB8
// match: ?flt_429ABC@@3MA @ 0x00429ABC
// match: ?flt_429AC0@@3MA @ 0x00429AC0
// match: ?flt_429AC4@@3MA @ 0x00429AC4
// match: ?flt_429AC8@@3MA @ 0x00429AC8
// match: ?flt_429ACC@@3MA @ 0x00429ACC
// match: ?flt_429AD0@@3MA @ 0x00429AD0
// match: ?flt_429AD4@@3MA @ 0x00429AD4
// match: ?flt_429AD8@@3MA @ 0x00429AD8
// match: ?flt_429ADC@@3MA @ 0x00429ADC
// match: ?flt_429AE0@@3MA @ 0x00429AE0
// match: ?flt_429AE4@@3MA @ 0x00429AE4
// match: ?flt_429AE8@@3MA @ 0x00429AE8
// match: ?flt_429AEC@@3MA @ 0x00429AEC
// match: ?flt_429AF0@@3MA @ 0x00429AF0
// match: ?flt_429AF4@@3MA @ 0x00429AF4
// match: ?flt_429AF8@@3MA @ 0x00429AF8
// match: ?flt_429AFC@@3MA @ 0x00429AFC
// match: ?flt_429B00@@3MA @ 0x00429B00
// match: ?flt_429B04@@3MA @ 0x00429B04
// match: ?flt_429B08@@3MA @ 0x00429B08
// match: ?flt_429B0C@@3MA @ 0x00429B0C
// match: ?flt_429B10@@3PAMA @ 0x00429B10
// match: ?flt_429B1C@@3MA @ 0x00429B1C
// match: ?flt_429B20@@3MA @ 0x00429B20
// match: ?flt_429B24@@3MA @ 0x00429B24
// match: ?flt_429B28@@3PAMA @ 0x00429B28
// match: ?flt_429B34@@3MA @ 0x00429B34
// match: ?flt_429B38@@3MA @ 0x00429B38
// match: ?dword_429B3C@@3HA @ 0x00429B3C

// match: _$E3 @ 0x0030B770
// match: _$E4 @ 0x0030E5E0
// match: ??0type_4C194C@@QAE@XZ @ 0x00115470
// sp-match: ??0type_4C194C@@QAE@XZ @ 0x000BFF20

// The damage message's middle level's id (its vtable, off_3DA440, follows
// the player's; /OPT:ICF folds the other functions returning 1 into it).
// match: ?vf_008@type_3DA440@@UAEHXZ @ 0x00115460
// sp-match: ?vf_008@type_3DA440@@UAEHXZ @ 0x002168E0
RwInt32 type_3DA440::vf_008()
{
    return 1;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_250@type_10F710@@UAEXM@Z (folded into the empty body at 0x15FB30)
void type_10F710::vf_250(RwReal arg_0)
{
}

// ?vf_254@type_10F710@@UAEXM@Z (folded into the empty body at 0x15FB30)
void type_10F710::vf_254(RwReal arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_108BC0@type_10F710@@QAEXHM@Z (folded into 0x108BC0)
void type_10F710::sub_108BC0(RwInt32 arg_0, RwReal arg_4)
{
    RwInt32 var_4;

    switch (arg_0)
    {
    case 2:
        var_4 = 0x15;
        break;
    case 5:
        var_4 = 0x1F;
        break;
    case 7:
        var_4 = 0x21;
        break;
    case 8:
        var_4 = 0x14;
        break;
    case 9:
        var_4 = 0x16;
        break;
    case 10:
        var_4 = 0x13;
        break;
    case 11:
        var_4 = 0x22;
        break;
    case 12:
        var_4 = 0x26;
        break;
    default:
        var_4 = 0x15;
        break;
    }
    if (unk_1A48[var_4] && unk_1A48[var_4]->get_unk_41E())
    {
        unk_1AF0 = unk_1AE4;
        sub_100200(var_4);
    }
}
