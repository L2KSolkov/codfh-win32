// The mounted weapons (type_3DC9B0, their settings type_4E1B70).

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "types/type_4E1B70.h"
#include "types/type_3DC9B0.h"
#include "types/type_3D32F8.h"
#include "types/MountedWeaponTrigger.h"
#include "game/functions.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/vecutil.h"
#include "rw/rphanim.h"
#include <math.h>
#include "game/clumpdata.h"
#include "types/animbank.h"
#include "types/type_3D51C0.h"
#include "types/type_4B85F8.h"
#include "types/type_3D2E7C.h"
#include "types/alfaobject.h"
#include "types/type_10F710.h"
#include "types/animkey.h"
#include "types/type_3DD948.h"
#include "types/type_DC400.h"
#include "types/VehicleTrigger.h"
#include "types/AnimatedBGTrigger.h"
#include "types/type_3DC048.h"
#include "types/type_F2FF0.h"
#include "types/type_3DAFC8.h"
#include "game/frand.h"
#include "types/type_154C0_1048.h"
#include "types/type_F8350.h"
#include "types/type_1227C0.h"
#include "rw/rtquat.h"
#include <stdlib.h>
#include <string.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DC984
extern const RwV3d stru_3DC984 = { 1.0f, 0.0f, 0.0f };
// 0x003DC990
extern const RwV3d stru_3DC990 = { 0.0f, 1.0f, 0.0f };
// 0x003DC99C
extern const RwV3d stru_3DC99C = { 0.0f, 0.0f, 1.0f };
// 0x003DC9A8
extern const RwReal flt_3DC9A8 = 16.666666f;
// 0x003DC9AC
extern const RwReal flt_3DC9AC = 0.0f;
// 0x00429E94
RwReal flt_429E94 = 5.0f;
// 0x00429E98
RwReal flt_429E98 = 0.1f;
// 0x00429E9C
RwReal flt_429E9C = 7.0f;
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_09IDLBEKLP@OutOfAmmo?$AA@ @ 0x003D278C
// match: ?stru_3DC984@@3URwV3d@@B @ 0x003DC984
// match: ?stru_3DC990@@3URwV3d@@B @ 0x003DC990
// match: ?stru_3DC99C@@3URwV3d@@B @ 0x003DC99C
// match: ?flt_3DC9A8@@3MB @ 0x003DC9A8
// match: ?flt_3DC9AC@@3MB @ 0x003DC9AC
// match: ??_7type_3DC9B0@@6B@ @ 0x003DC9B0
// match: __real@3f12d57c @ 0x003DCBE4
// match: ??_C@_06IDDCOJOK@shield?$AA@ @ 0x003DCBE8
// match: ??_C@_05LEMOKIDC@mount?$AA@ @ 0x003DCBF0
// match: ??_C@_06GEPNGEJI@weapon?$AA@ @ 0x003DCBF8
// match: __real@bfefef9db22d0e56 @ 0x003DCC00
// match: __real@3fefef9db22d0e56 @ 0x003DCC08
// match: __real@c3870000 @ 0x003DCC10
// match: __real@c2b40000 @ 0x003DCC14
// match: __real@43870000 @ 0x003DCC18
// match: ??_C@_0BH@BAJDGKOJ@EntityAttachedToWeapon?$AA@ @ 0x003DCC1C
// match: ??_C@_0BJ@JAMNOOKH@EntityDetachedFromWeapon?$AA@ @ 0x003DCC34
// match: __real@41100000 @ 0x003DCC50
// match: __real@40e00000 @ 0x003DCC54
// match: ??_C@_0BI@OCLICOLA@StopFiringMountedWeapon?$AA@ @ 0x003DCC58
// match: ??_C@_0BG@MCLNNMJG@OKToFireMountedWeapon?$AA@ @ 0x003DCC70
// match: __ehhandler$?sub_166D40@@YAPAUtype_3D3548@@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z>1>8 @ 0x0041E150
// match: __ehhandler$?sub_166D40@@YAPAUtype_3D3548@@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z>1 @ 0x0041E158
// match: __ehhandler$??0type_3DC9B0@@QAE@PAUtype_712B0@@@Z>1>8 @ 0x0041E174
// match: __ehhandler$??0type_3DC9B0@@QAE@PAUtype_712B0@@@Z>1 @ 0x0041E194
// match: __ehhandler$??1type_3DC9B0@@UAE@XZ>1>8 @ 0x0041E1B0
// match: __ehhandler$??1type_3DC9B0@@UAE@XZ>1 @ 0x0041E1E0
// match: __ehhandler$?sub_1669B0@@YAPAUtype_3D3548@@PAUtype_712B0@@@Z>1>8 @ 0x0041E1FC
// match: __ehhandler$?sub_1669B0@@YAPAUtype_3D3548@@PAUtype_712B0@@@Z>1 @ 0x0041E204
// match: __ehhandler$??0type_3DC9B0@@QAE@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z>1>8 @ 0x0041E220
// match: __ehhandler$??0type_3DC9B0@@QAE@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z>1 @ 0x0041E240
// match: __ehhandler$?sub_169BC0@@YAHPAUtype_F2FF0@@@Z>1>8 @ 0x0041E25C
// match: __ehhandler$?sub_169BC0@@YAHPAUtype_F2FF0@@@Z>1 @ 0x0041E264
// match: .CRT$XCU+0 @ 0x00427130
// match: ?flt_429E94@@3MA @ 0x00429E94
// match: ?flt_429E98@@3MA @ 0x00429E98
// match: ?flt_429E9C@@3MA @ 0x00429E9C

// match: _$E2 @ 0x0030BC70

type_4E1B70 dword_4E1B70[7];

// match: ?sub_166990@@YAPAUtype_4E1B70@@H@Z @ 0x00166990
// sp-match: ?sub_166990@@YAPAUtype_4E1B70@@H@Z @ 0x00106B30
type_4E1B70 *sub_166990(RwInt32 arg_0)
{
    if (arg_0 < 7)
        return &dword_4E1B70[arg_0];
    return 0;
}

// match: ?sub_1669B0@@YAPAUtype_3D3548@@PAUtype_712B0@@@Z @ 0x001669B0
// match: __ehhandler$?sub_1669B0@@YAPAUtype_3D3548@@PAUtype_712B0@@@Z-0x11 @ 0x00301F80
// match: __ehhandler$?sub_1669B0@@YAPAUtype_3D3548@@PAUtype_712B0@@@Z @ 0x00301F91
// sp-match: ?sub_1669B0@@YAPAUtype_3D3548@@PAUtype_712B0@@@Z @ 0x00109F30
// Builds the mounted weapon for the trigger arg_0, or warns that there is
// no entity memory for it.
type_3D3548 *sub_1669B0(type_712B0 *arg_0)
{
    type_3DC9B0 *var_10;

    var_10 = (type_3DC9B0 *)sub_D56D0(0x5E0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0) {
        var_10 = new (var_10) type_3DC9B0(arg_0);
        if (var_10->unk_28 & 0x400000) { // not an address: entity flag
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
#ifndef CODFH_SP
    // Single player compiles the debug print out (SP 0x109F30).
    else
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
#endif
    return var_10;
}

// match: ??0type_3DC9B0@@QAE@PAUtype_712B0@@@Z @ 0x00166AC0
// match: __ehhandler$??0type_3DC9B0@@QAE@PAUtype_712B0@@@Z-0x32 @ 0x00301EF0
// match: __ehhandler$??0type_3DC9B0@@QAE@PAUtype_712B0@@@Z @ 0x00301F22
// sp-match: ??0type_3DC9B0@@QAE@PAUtype_712B0@@@Z @ 0x00109EB0
// (Defined in the class.)

// match: ?vf_1F8@type_3DC9B0@@UAEPAUtype_3D3548@@H@Z @ 0x00166B90
// sp-match: ?vf_1F8@type_3DC9B0@@UAEPAUtype_3D3548@@H@Z @ 0x00109B70

// match: ?vf_1FC@type_3DC9B0@@UAEXPAUtype_3D3548@@H@Z @ 0x00166BB0
// sp-match: ?vf_1FC@type_3DC9B0@@UAEXPAUtype_3D3548@@H@Z @ 0x00109B80

// match: ?vf_098@type_3DC9B0@@UAEPAUtype_3D2E7C@@XZ @ 0x00166BD0
// sp-match: ?vf_098@type_3DC9B0@@UAEPAUtype_3D2E7C@@XZ @ 0x00109BA0

// match: ?vf_09C@type_3DC9B0@@UAEHXZ @ 0x00166BF0
// sp-match: ?vf_09C@type_3DC9B0@@UAEHXZ @ 0x00109BB0

// match: ?vf_0A0@type_3DC9B0@@UAEXI@Z @ 0x00166C10
// sp-match: ?vf_0A0@type_3DC9B0@@UAEXI@Z @ 0x00109BC0

// match: ??_Gtype_3DC9B0@@UAEPAXI@Z @ 0x00166C30
// match: ??1type_3DC9B0@@UAE@XZ @ 0x00166C60
// match: __ehhandler$??1type_3DC9B0@@UAE@XZ-0x42 @ 0x00301F30
// match: __ehhandler$??1type_3DC9B0@@UAE@XZ @ 0x00301F72
// sp-match: ??1type_3DC9B0@@UAE@XZ @ 0x00109BF0
// sp-match: ??_Gtype_3DC9B0@@UAEPAXI@Z @ 0x00109BD0
// (Defined in the class: vf_230, called directly as in any destructor,
// then the members' destructors and the base's.)

// match: ?sub_166D40@@YAPAUtype_3D3548@@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z @ 0x00166D40
// match: __ehhandler$?sub_166D40@@YAPAUtype_3D3548@@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z @ 0x00301F91
// sp-match: ?sub_166D40@@YAPAUtype_3D3548@@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z @ 0x00109FD0
type_3D3548 *sub_166D40(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C, type_712B0 *arg_10,
                        RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C, RwInt32 arg_20, RwInt32 arg_24,
                        RwInt32 arg_28)
{
    type_3DC9B0 *var_10;

    var_10 = (type_3DC9B0 *)sub_D56D0(0x5E0, 0, 0x1B);
    if (var_10 != 0)
        var_10 = new (var_10) type_3DC9B0(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18, arg_1C, arg_20,
                                          arg_24, arg_28);
    return var_10;
}

// match: ??0type_3DC9B0@@QAE@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z @ 0x00166E00
// sp-match: ??0type_3DC9B0@@QAE@HHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z @ 0x00109AA0
type_3DC9B0::type_3DC9B0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C, type_712B0 *arg_10,
                         RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C, RwInt32 arg_20, RwInt32 arg_24,
                         RwInt32 arg_28)
{
    unk_344.sub_144940(0);
    unk_5D4 = 0;
    sub_166FA0(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18, arg_1C, arg_20, arg_24, arg_28);
}

// match: ?sub_166F20@type_3DC9B0@@QAEXPAUtype_712B0@@@Z @ 0x00166F20
// sp-match: ?sub_166F20@type_3DC9B0@@QAEXPAUtype_712B0@@@Z @ 0x00109C80
void type_3DC9B0::sub_166F20(type_712B0 *arg_0)
{
    MountedWeaponTrigger *var_4;

    sub_CCCD0(arg_0);
    var_4 = (MountedWeaponTrigger *)arg_0;
    sub_166FA0(var_4->unk_C0, var_4->unk_C4, &var_4->unk_60_m, 1, arg_0, 0, var_4->unk_EC, var_4->unk_F0,
               var_4->unk_F4, var_4->unk_E0, var_4->unk_CC);
}

// match: ?sub_166FA0@type_3DC9B0@@QAEHHHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z @ 0x00166FA0
// sp-match: ?sub_166FA0@type_3DC9B0@@QAEHHHPAURwMatrixTag@@HPAUtype_712B0@@HHHHHH@Z @ 0x00108C30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sets it up with the settings arg_0 (its settings index; arg_4 kept) for
// the trigger arg_10 (arg_14 its kind: 1 a vehicle's, 2 an animated
// background entity's, 0 its own trigger's), its parts "weapon", "mount"
// and "shield" shown by arg_18 to arg_20; its animation, script object and
// its pitch and yaw limits. Returns 1.
RwInt32 type_3DC9B0::sub_166FA0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C,
                                type_712B0 *arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                                RwInt32 arg_20, RwInt32 arg_24, RwInt32 arg_28)
{
    RwUInt32 ebp_34;
    RwUInt32 var_30;
    type_3DFEEC *var_2C;
    MountedWeaponTrigger *lcl_28;
    type_3DF8D8 *frm_24;
    type_4E1B70 *var_20;
    type_3D2E7C *l1C;
    type_3DF8D8 *m_18;
    RpAtomic *ebp_14;
    type_7C8D0 *lv_10;
    RwInt32 var_C;
    RpHAnimHierarchy *bp_8;
    RwInt32 bp_4;

    var_20 = sub_166990(arg_0);
    unk_88 |= 0x2000;
    unk_4F0 = 0;
    unk_4BC = 0;
    unk_48 = var_20->unk_C4_r;
    unk_4C = var_20->unk_C4_r;
    unk_50_r = var_20->unk_C4_r;
    zero_v3d(&unk_3C_v);
    sub_CCCD0(arg_10);
    unk_498 = arg_14;
    unk_4B8 = arg_24;
    unk_4C8 = mmg_difficulty_scale() * var_20->unk_18;
    unk_4CC = arg_28;
    if (!unk_498)
    {
        lcl_28 = (MountedWeaponTrigger *)arg_10;
        if (lcl_28->unk_E4.unk_00)
        {
            var_2C = (type_3DFEEC *)sub_198800(&lcl_28->unk_E4);
            ((type_D48D0 *)&var_2C->unk_24_id)->sub_D48D0(this);
            var_2C->unk_10 = 6;
        }
    }
    if (arg_C)
    {
        unk_28 = 4;
        unk_490 = 1;
    }
    else
    {
        unk_28 = 4;
        unk_490 = 0;
    }
    unk_2C = 0x80000; // not an address: entity kind bits
    unk_30 = 0x13;
    set_xyz(&unk_10C, -1.0f, -1.0f, -1.0f);
    set_xyz(&unk_134, -1.0f, -1.0f, -1.0f);
    zero_v3d(&unk_118);
    set_xyz(&unk_124, 1000.0f, 1000.0f, 1000.0f);
    unk_130 = 0;
    unk_3B0 = arg_0;
    unk_3B4 = arg_4;
    unk_428 = arg_4;
    m_18 = sub_198800(&var_20->unk_00);
    type_3D3548::vf_224(m_18, 0, &var_C);
    sub_D5B80(this, 0xD);
    ebp_14 = unk_274.unk_08;
    if (ebp_14)
    {
        ebp_14->boundingSphere.radius = 100.0f;
        ebp_14->object[2] = 1;
    }
    unk_4A8 = (RpAtomic *)sub_16D900(get_unk_264(), "weapon");
    unk_500 = *RwFrameGetMatrix(RpAtomicGetFrame(unk_4A8));
    unk_3D0 = unk_500;
    sub_16D8C0(get_unk_264(), "weapon", arg_18 != 0);
    sub_16D8C0(get_unk_264(), "mount", arg_1C != 0);
    sub_16D8C0(get_unk_264(), "shield", arg_20 != 0);
    var_30 = sub_78830(1);
    unk_280 = var_30;
    lv_10 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = lv_10;
    bp_8 = sub_16D970(get_unk_264());
    lv_10->sub_79470(bp_8);
    lv_10->unk_1C = (RwInt32)this;
    RpHAnimHierarchyAttach(bp_8);
    bp_4 = bp_8->flags;
    bp_4 |= rpHANIMHIERARCHYUPDATEMODELLINGMATRICES;
    bp_8->flags = bp_4;
    unk_5C0.sub_D48D0(0);
    unk_3C0 = 0;
    unk_3B8 = 0;
    unk_3C4 = 0;
    unk_3BC = 0;
    unk_4A4 = 0;
    unk_410 = 0;
    unk_470 = 0;
    unk_474 = 0;
    unk_4A0 = 0;
    unk_478 = 0;
    unk_484 = 0;
    unk_488 = 0;
    unk_424 = 0;
    unk_41C = 0;
    unk_420 = 70.0f;
    unk_48C = 1;
    unk_47C = 0;
    unk_480 = 0;
    unk_4E8 = 1;
    unk_414 = 0;
    unk_418 = 0;
    unk_49C = 0;
    RwMatrixSetIdentityMacro(&unk_430);
    unk_494 = 0;
    unk_4EC = sub_16A240();
    unk_4C0 = cos(sub_16A790() * 0.017453292f);
    unk_4C4 = cos(sub_16A890() * 0.017453292f);
    if (unk_4C0 < 0.57357f)
        unk_4C0 = 0.57357f;
    if (unk_4C4 < 0.57357f)
        unk_4C4 = 0.57357f;
    sub_169170(0);
    if (unk_498 == 1)
        frm_24 = sub_198800(&arg_10->unk_1C0);
    else if (unk_498 == 2)
        frm_24 = sub_198800(&arg_10->unk_150);
    else
        frm_24 = sub_198800(&((MountedWeaponTrigger *)arg_10)->unk_F8);
    ebp_34 = sub_71870();
    unk_5C4 = ebp_34;
    l1C = vf_098();
    l1C->sub_70DF0(this, 2);
    l1C->sub_70E10(frm_24->get_unk_18(), arg_14 == 0);
    if (arg_10)
    {
        if (!arg_10->unk_24_9)
            unk_28 |= 0x20000; // not an address: entity flag
    }
    else
    {
        unk_28 |= 0x20000; // not an address: entity flag
    }
    unk_5D4 = 1;
    unk_4D0 = 0;
    unk_4D4 = 0;
    unk_4D8 = 0;
    if (unk_3B0 == 4)
    {
        unk_4DC = RpHAnimIDGetIndex(bp_8, 1);
        unk_4E0 = RpHAnimIDGetIndex(bp_8, 2);
        unk_4E4 = RpHAnimIDGetIndex(bp_8, 3);
    }
    else
    {
        unk_4E4 = 0;
        unk_4E0 = 0;
        unk_4DC = 0;
    }
    return 1;
}

// match: ?vf_230@type_3DC9B0@@UAEXXZ @ 0x00167820
// sp-match: ?vf_230@type_3DC9B0@@UAEXXZ @ 0x00109140
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shuts it down: its user dismounted, its script object freed, its
// animation released, its trigger's script object let go, and its buffer.
void type_3DC9B0::vf_230()
{
    type_3DFEEC *var_C;
    MountedWeaponTrigger *bp_8;
    type_3D3548 *bp_4;

    if (unk_5D4)
    {
        bp_4 = unk_5C0.sub_D4910();
        if (bp_4 && bp_4->unk_2C_4)
            sub_168A90((type_10F710 *)bp_4);
        else
            sub_169000((type_3DAFC8 *)bp_4);
        if (vf_098())
        {
            sub_71970((type_3D2C88 *)vf_098());
            unk_5C4 = 0;
        }
        unk_5D4 = 0;
        vf_228();
        sub_78870(unk_280);
        unk_280 = 0;
        if (!unk_498)
        {
            bp_8 = (MountedWeaponTrigger *)get_unk_34C();
            if (bp_8->unk_E4.unk_00)
            {
                var_C = (type_3DFEEC *)sub_198800(&bp_8->unk_E4);
                ((type_D48D0 *)&var_C->unk_24_id)->sub_D48D0(0);
            }
        }
        if (unk_4D4)
        {
            RwFree((void *)unk_4D4);
            unk_4D4 = 0;
        }
    }
}

// match: ?vf_054@type_3DC9B0@@UAEXH@Z @ 0x00167970
// sp-match: ?vf_054@type_3DC9B0@@UAEXH@Z @ 0x00106B50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The base's (sub_D2820), unless the player is on it.
void type_3DC9B0::vf_054(RwInt32 arg_0)
{
    type_3D3548 *var_8;
    type_10F710 *l4;

    l4 = (type_10F710 *)sub_1745A0(0);
    if (l4->unk_1B28)
    {
        var_8 = l4->unk_210C.sub_D4910();
        if (var_8 == this)
            return;
    }
    type_3D3548::vf_054(arg_0);
}

// match: ?sub_1679C0@type_3DC9B0@@QAEXH@Z @ 0x001679C0
// sp-match: ?sub_1679C0@type_3DC9B0@@QAEXH@Z @ 0x00106B90
void type_3DC9B0::sub_1679C0(RwInt32 arg_0)
{
    RpAtomic *var_4;

    var_4 = unk_250.unk_08;
    if (var_4)
    {
        sub_D2B70(var_4);
        type_3D3548::vf_054(arg_0);
    }
}

// match: ?vf_1C4@type_3DC9B0@@UAEXH@Z @ 0x00167A00
// sp-match: ?vf_1C4@type_3DC9B0@@UAEXH@Z @ 0x00106BC0
void type_3DC9B0::vf_1C4(RwInt32 arg_0)
{
    set_xyz(&unk_10C, -1.0f, -1.0f, -1.0f);
    vf_18C(0);
}

// match: ?sub_167A50@@YAXPAURwMatrixTag@@PAM11@Z @ 0x00167A50
// sp-match: ?sub_167A50@@YAXPAURwMatrixTag@@PAM11@Z @ 0x00106BF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_167A50(RwMatrix *arg_0, RwReal *arg_4, RwReal *arg_8, RwReal *arg_C)
{
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    if (arg_0->up.x > 0.998)
    {
        var_C = atan2(arg_0->right.z, arg_0->at.z);
        bp_8 = 1.570795f;
        bp_4 = 0;
    }
    else if (arg_0->up.x < -0.998)
    {
        var_C = atan2(arg_0->right.z, arg_0->at.z);
        bp_8 = -1.570795f;
        bp_4 = 0;
    }
    else
    {
        var_C = atan2(-arg_0->at.x, arg_0->right.x);
        bp_4 = atan2(-arg_0->up.z, arg_0->up.y);
        bp_8 = asin(arg_0->up.x);
    }
    *arg_8 = var_C * 57.295826f;
    *arg_C = bp_4 * 57.295826f;
    *arg_4 = bp_8 * 57.295826f;
}

// match: ?sub_167BC0@type_3DC9B0@@QAEXXZ @ 0x00167BC0
// sp-match: ?sub_167BC0@type_3DC9B0@@QAEXXZ @ 0x00107D30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DC9B0::sub_167BC0()
{
    RwReal l40;
    RwReal var_3C;
    RwReal w38;
    RwReal ebp_34;
    RwReal var_30;
    RwReal v2C;
    RwReal lcl_28;
    RwReal frm_24;
    RwReal var_20;
    RwReal l1C;
    RwReal m_18;
    RwFrame *ebp_14;
    RwMatrix *lv_10;
    RwV3d var_C;

    if (unk_4A8)
    {
        ebp_14 = RpAtomicGetFrame(unk_4A8);
        lv_10 = RwFrameGetMatrix(ebp_14);
        var_C = lv_10->pos;
        if (unk_488 || unk_470)
        {
            RwFrameUpdateObjects(get_unk_340());
            sub_167A50(&unk_3D0, &l40, &v2C, &var_20);
            sub_167A50(RwFrameGetLTM(get_unk_340()), &l1C, &w38, &m_18);
            lcl_28 = l40 - l1C;
            frm_24 = v2C - w38;
            ebp_34 = var_20 - m_18;
            if (unk_3BC > 90.0f && unk_3BC < 270.0f || unk_3BC < -90.0f && unk_3BC > -270.0f)
                lcl_28 = lcl_28 * -1.0f;
            l40 = lcl_28 + unk_3B8;
            v2C = unk_3BC - frm_24;
            var_3C = sub_16A790();
            var_30 = sub_16A890();
#ifdef CODFH_SP
            // shape: the angles on the left, and the yaw's limit compared as a float
            // (SP 0x107EA5: fucompp with 180 and 360).
            if (l40 < -var_3C)
                l40 = -var_3C;
            else if (l40 > var_3C)
                l40 = var_3C;
            if (var_30 != 180.0f && var_30 != 360.0f)
            {
                if (v2C < -var_30)
                    v2C = -var_30;
                else if (v2C > var_30)
                    v2C = var_30;
            }
#else
            if (-var_3C > l40)
                l40 = -var_3C;
            else if (l40 > var_3C)
                l40 = var_3C;
            // The yaw's limit is compared by its bits (180 or 360: none).
            if (*(RwInt32 *)&var_30 != 0x43340000 && *(RwInt32 *)&var_30 != 0x43B40000)
            {
                if (-var_30 > v2C)
                    v2C = -var_30;
                else if (v2C > var_30)
                    v2C = var_30;
            }
#endif
            unk_3B8 = l40;
            unk_3BC = v2C;
            RwMatrixSetIdentityMacro(lv_10);
            RwMatrixRotate(lv_10, &stru_3DC99C, ebp_34, rwCOMBINEREPLACE);
        }
        if (unk_494)
        {
            RwMatrixRotate(lv_10, &stru_3DC990, unk_3BC, rwCOMBINEPRECONCAT);
            RwMatrixRotate(lv_10, &stru_3DC984, unk_3B8, rwCOMBINEPRECONCAT);
            if (unk_488 || unk_470)
                lv_10->pos = var_C;
        }
        else if (!unk_4F0)
        {
            RwMatrixRotate(lv_10, &stru_3DC990, unk_3BC, rwCOMBINEREPLACE);
            RwMatrixRotate(lv_10, &stru_3DC984, unk_3B8, rwCOMBINEPRECONCAT);
            lv_10->pos = var_C;
        }
        RwFrameUpdateObjects(ebp_14);
        unk_3D0 = *RwFrameGetLTM(get_unk_340());
    }
    unk_3C4 = unk_3BC;
    unk_3C0 = unk_3B8;
}

// match: ?vf_038@type_3DC9B0@@UAEXM@Z @ 0x00167FA0
// sp-match: ?vf_038@type_3DC9B0@@UAEXM@Z @ 0x00109220
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Kind 4 starts its animation and its procedural track (sub_16B0C0) once.
void type_3DC9B0::vf_038(RwReal arg_0)
{
    RtAnimAnimation *var_C;
    type_783F0 *bp_8;
    type_4E1B70 *bp_4;

    bp_4 = sub_166990(unk_3B0);
    if (unk_3B0 == 4 && !unk_4D0)
    {
        if (sub_77B70(bp_4->unk_C8->unk_34, (void **)((RwInt32 *)&var_C), (void **)((RwInt32 *)&bp_8)))
        {
            get_unk_284()->sub_794C0(0);
            unk_284->sub_796A0(var_C, bp_4->unk_C8->unk_34, 0, bp_8, 0, 1.0f, 1.0f);
            unk_4D0 = get_unk_284()->sub_79930(sub_16B0C0, 1.0f, 1.0f);
#ifdef CODFH_SP // SP expands type_78AC0::sub_6DF40 here (SP 0x1092CD: % 4 ring)
            get_unk_284()->clear_last_unk_08_30();
#else
            ((type_78AC0 *)get_unk_284())->sub_6DF40();
#endif
            // An unused slot below the temporaries (see unused_slot).
            unused_slot();
        }
    }
}

// match: ?vf_03C@type_3DC9B0@@UAEXM@Z @ 0x00168090
// sp-match: ?vf_03C@type_3DC9B0@@UAEXM@Z @ 0x00109CE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its step by arg_0: the base's; hidden from explosions while it has no
// unk_334; with the player on it, the player dismounted while changing
// weapon, else its yaw kept within a turn; its NPC's aim and firing, its
// performance, the firing sound stopped once it has not fired for its
// settings' time (plus two), and its time.
void type_3DC9B0::vf_03C(RwReal arg_0)
{
    type_3D3548 *var_18;
    type_6D380 *var_14;
    type_4E1B70 *lv_10;
    RwInt32 var_C;
    type_10F710 *bp_8;
    type_3D3548 *bp_4;

    lv_10 = sub_166990(unk_3B0);
    bp_4 = unk_5C0.sub_D4910();
    var_C = -1;
    bp_8 = 0;
    type_3D3548::vf_03C(arg_0);
    if (bp_4)
        var_C = ((type_3DF8D8 *)bp_4->get_unk_34C())->vf_008();
    if (var_C == 1)
        bp_8 = (type_10F710 *)bp_4;
    if (unk_334)
        unk_28 &= ~4;
    else
        unk_28 |= 4;
    if (bp_8)
    {
        if (bp_8->unk_19F8 > 0)
        {
            sub_168A90(bp_8);
            return;
        }
        if (unk_3BC > 360.0f)
            unk_3BC = unk_3BC - 360.0f;
        if (unk_3BC < -360.0f)
            unk_3BC = unk_3BC + 360.0f;
    }
    if (unk_4F0)
        sub_16AAE0();
    if (unk_4F4)
        sub_169380();
    if (unk_284 && unk_88_9)
    {
        var_14 = vf_090();
        if (var_14)
            ((type_3D2CD0 *)var_14)->sub_6D5A0(arg_0);
        vf_21C(arg_0);
    }
    if (unk_480 && unk_410 - unk_4C8 > 2.0f)
    {
        var_18 = unk_5C0.sub_D4910();
        if (var_18)
        {
            var_18->unk_1C0.sub_8A910(unk_49C);
            var_18->unk_1C0.sub_8A980(&lv_10->unk_64, this, 0, var_18->sub_CD550(), 0, 0);
            unk_480 = 0;
        }
    }
    unk_410 = arg_0 + unk_410;
    if (unk_4F0)
        unk_470 = 0;
}

// match: ?vf_04C@type_3DC9B0@@UAEXM@Z @ 0x00168300
// sp-match: ?vf_04C@type_3DC9B0@@UAEXM@Z @ 0x00108040
// Its update by arg_0: the base's, its aim (not kind 4), and with the player
// on it the player's camera: at the settings' view, blending towards the
// zoomed view while zooming in or out (and the field of view), turned with
// the aim, at the weapon's tag (kind 4: the hierarchy's bone 3); the
// player told it uses it.
void type_3DC9B0::vf_04C(RwReal arg_0)
{
    type_3D3548::vf_04C(arg_0);
    switch (unk_3B0)
    {
    case 4:
        pDtor();
        break;
    default:
        sub_167BC0();
        break;
    }
    type_4E1B70 *var_C = sub_166990(unk_3B0);
    type_3D3548 *var_10 = unk_5C0.sub_D4910();
    RwInt32 var_14 = -1;
    type_10F710 *var_18 = 0;

    if (var_10)
        var_14 = ((type_3DF8D8 *)var_10->get_unk_34C())->vf_008();
    if (var_14 == 1)
        var_18 = (type_10F710 *)var_10;
    if (var_14 == 1)
    {
        RwV3d var_2C = var_C->unk_74;
        RwV3d var_38 = var_C->unk_80;
        RwFrame *var_40 = var_18->get_unk_340();
        RwMatrix *var_44 = RwFrameGetMatrix(var_40);
        RwMatrix *var_74;

        if (unk_424)
        {
            if (unk_424 == 1)
            {
                unk_41C = arg_0 + unk_41C;
                if (unk_41C > var_C->unk_A8)
                {
                    unk_41C = var_C->unk_A8;
                    unk_424 = 0;
                }
            }
            else
            {
                unk_41C = unk_41C - arg_0;
                if (unk_41C < 0.0f)
                {
                    unk_41C = 0;
                    unk_424 = 0;
                }
            }
            RwReal var_48 = unk_41C / var_C->unk_A8;
            RwV3d var_54;
            RwV3d var_60;

            var_54.x = (var_C->unk_8C.x - var_C->unk_74.x) * var_48 + var_C->unk_74.x;
            var_54.y = (var_C->unk_8C.y - var_C->unk_74.y) * var_48 + var_C->unk_74.y;
            var_54.z = (var_C->unk_8C.z - var_C->unk_74.z) * var_48 + var_C->unk_74.z;
            var_60.x = (var_C->unk_98.x - var_C->unk_80.x) * var_48 + var_C->unk_80.x;
            var_60.y = (var_C->unk_98.y - var_C->unk_80.y) * var_48 + var_C->unk_80.y;
            var_60.z = (var_C->unk_98.z - var_C->unk_80.z) * var_48 + var_C->unk_80.z;
            var_2C = var_54;
            var_38 = var_60;
            var_18->unk_534 = (unk_420 / var_C->unk_AC_r - unk_420) * var_48 + unk_420;
        }
        else if (unk_488)
        {
            var_2C = var_C->unk_8C;
            var_38 = var_C->unk_98;
        }
        switch (unk_3B0)
        {
        case 4:
        {
            RwMatrixRotate(var_44, &stru_3DC99C, var_38.z, rwCOMBINEREPLACE);
            RwMatrixRotate(var_44, &stru_3DC990, var_38.y, rwCOMBINEPRECONCAT);
            RwMatrixRotate(var_44, &stru_3DC984, var_38.x, rwCOMBINEPRECONCAT);
            RwMatrixTranslate(var_44, &var_2C, rwCOMBINEPOSTCONCAT);
            var_18->vf_0C0(&var_44->pos);
            RpHAnimHierarchy *var_68 = unk_284->unk_18;

            var_74 = &var_68->pMatrixArray[bone_index(unk_284->unk_18, 3)];
            RwMatrixTransform(var_44, var_74, rwCOMBINEPOSTCONCAT);
            break;
        }
        default:
        {
            RwMatrix var_C0;

            RwMatrixRotate(var_44, &stru_3DC99C, var_38.z, rwCOMBINEREPLACE);
            RwMatrixRotate(var_44, &stru_3DC990, var_38.y, rwCOMBINEPRECONCAT);
            RwMatrixRotate(var_44, &stru_3DC984, var_38.x, rwCOMBINEPRECONCAT);
            RwMatrixTranslate(var_44, &var_2C, rwCOMBINEPOSTCONCAT);
            RwMatrixRotate(&var_C0, &stru_3DC990, unk_3BC, rwCOMBINEREPLACE);
            RwMatrixRotate(&var_C0, &stru_3DC984, unk_3B8, rwCOMBINEPRECONCAT);
            RwMatrixTransform(var_44, &var_C0, rwCOMBINEPOSTCONCAT);
            RwMatrixTranslate(var_44, &unk_500.pos, rwCOMBINEPOSTCONCAT);
            var_18->vf_0C0(&var_44->pos);
            var_74 = RwFrameGetMatrix(get_unk_340());
            RwMatrixTransform(var_44, var_74, rwCOMBINEPOSTCONCAT);
            break;
        }
        }
        if (var_14 == 1 && var_18)
            var_18->unk_210C.sub_D48D0(this);
    }
}

// match: ?sub_168820@type_3DC9B0@@QAEXPAUtype_10F710@@@Z @ 0x00168820
// sp-match: ?sub_168820@type_3DC9B0@@QAEXPAUtype_10F710@@@Z @ 0x00106CC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Mounts the player arg_0 (not without its weapon part): its aim from the
// player's frame, the HUD's weapon display and the look reset, the mount
// sound and rumble, the player's weapon's state cleared, its field of view
// from its trigger (and the camera's); then its trigger's script told
// "EntityAttachedToWeapon".
void type_3DC9B0::sub_168820(type_10F710 *arg_0)
{
    type_4E1B70 *var_14;
    RwMatrix *lv_10;
    type_3DD948 *var_C;
    RwFrame *bp_8;
    type_712B0 *bp_4;

    if (unk_4A8)
    {
        var_14 = sub_166990(unk_3B0);
        bp_8 = arg_0->get_unk_340();
        lv_10 = RwFrameGetMatrix(bp_8);
        unk_430 = *lv_10;
        arg_0->unk_1A04 = 0;
        if (!unk_4B8 && dword_4B9190)
            dword_4B9190->sub_E0800(0x17);
        arg_0->unk_530 = 0;
        arg_0->unk_1C0.sub_8A980(&var_14->unk_44, this, 1, arg_0->sub_CD550(), 0, 0);
        unk_4B9308.sub_EECD0(3, 1);
        unk_5C0.sub_D48D0(arg_0);
        arg_0->unk_1B28 = 1;
        arg_0->unk_3F0 = 0;
        arg_0->unk_3F8 = 0;
        arg_0->unk_3EC = 0;
        arg_0->unk_3F4 = 0;
        arg_0->unk_1A48[arg_0->unk_1AE4]->unk_298 = 0;
        arg_0->unk_534 = ((type_712B0_10F710 *)arg_0->get_unk_34C())->unk_F0;
        var_C = (type_3DD948 *)arg_0->unk_2110.sub_D4910();
        if (var_C)
            var_C->unk_3C0 = arg_0->get_unk_534();
        arg_0->unk_1B04 = 0;
        arg_0->unk_1B14 = 0;
        arg_0->unk_1B08 = 0;
        arg_0->unk_1A48[arg_0->unk_1AE4]->unk_228 = 0;
        arg_0->unk_1A48[arg_0->unk_1AE4]->unk_230 = 0;
        arg_0->unk_1A48[arg_0->unk_1AE4]->unk_22C = 0;
        unk_420 = arg_0->unk_534;
    }
    else
    {
        return;
    }
    bp_4 = get_unk_34C();
    if (bp_4)
        sub_6B5F0("EntityAttachedToWeapon", (type_67620 *)(bp_4->sub_BDF50()), 0, (type_3D2E7C *)((RwInt32)arg_0->vf_098()), 0, 0, 1, 0);
}

// match: ?sub_168A90@type_3DC9B0@@QAEXPAUtype_10F710@@@Z @ 0x00168A90
// sp-match: ?sub_168A90@type_3DC9B0@@QAEXPAUtype_10F710@@@Z @ 0x001083C0
// Dismounts the player arg_0: the player's frame at the way off
// (sub_16A030), the HUD's weapon display back, its firing sound stopped,
// the dismount sound, the player's weapon taken up again, its trigger's
// script told "EntityDetachedFromWeapon", its user and zoom cleared, the
// player's look, field of view and weapon state reset.
void type_3DC9B0::sub_168A90(type_10F710 *arg_0)
{
    type_4E1B70 *var_8;
    RwFrame *var_10;
    RwMatrix *var_14;

    if (unk_4A8)
    {
        var_8 = sub_166990(unk_3B0);
        var_10 = arg_0->get_unk_340();
        var_14 = RwFrameGetMatrix(var_10);
        RwMatrix var_60;

        sub_16A030(&var_60);

        *var_14 = var_60;
        if (dword_4B9190)
            dword_4B9190->sub_E0800(arg_0->unk_1A48[arg_0->unk_1AE4]->get_unk_458());
        if (unk_480)
        {
            type_3D3548 *var_68 = unk_5C0.sub_D4910();

            var_68->unk_1C0.sub_8A910(unk_49C);
            var_68->unk_1C0.sub_8A980(&var_8->unk_64, this, 0, var_68->sub_CD550(), 0, 0);
            unk_480 = 0;
        }
        arg_0->unk_1C0.sub_8A980(&var_8->unk_4C, this, 1, arg_0->sub_CD550(), 0, 0);
        if (!arg_0->unk_19F8)
            arg_0->unk_1A48[arg_0->unk_1AE4]->sub_1170B0(1, 1);
        arg_0->sub_FF030();
        type_712B0 *var_70 = get_unk_34C();
        if (var_70)
            sub_6B5F0("EntityDetachedFromWeapon", (type_67620 *)(var_70->sub_BDF50()), 0, (type_3D2E7C *)((RwInt32)arg_0->vf_098()), 0, 0, 1, 0);
        unk_5C0.sub_D48D0(0);
        arg_0->unk_1B28 = 0;
        unk_47C = 1;
        unk_470 = 0;
        unk_474 = 0;
        unk_424 = 0;
        unk_488 = 0;
        unk_41C = 0;
        unk_424 = 0;
        if (!arg_0->unk_19F8)
            arg_0->sub_1090F0(0);
        arg_0->unk_534 = unk_420;
        arg_0->unk_3F0 = 0;
        arg_0->unk_3F8 = 0;
        arg_0->unk_3EC = 0;
        arg_0->unk_3F4 = 0;
        arg_0->unk_1A48[arg_0->unk_1AE4]->unk_298 = 0;
        arg_0->unk_534 = ((type_712B0_10F710 *)arg_0->get_unk_34C())->unk_F0;
        type_3DD948 *var_78 = (type_3DD948 *)arg_0->unk_2110.sub_D4910();
        if (var_78)
            var_78->unk_3C0 = arg_0->get_unk_534();
        arg_0->unk_1B04 = 0;
        arg_0->unk_1B14 = 0;
        arg_0->unk_1B08 = 0;
        arg_0->unk_1A48[arg_0->unk_1AE4]->unk_228 = 0;
        arg_0->unk_1A48[arg_0->unk_1AE4]->unk_230 = 0;
        arg_0->unk_1A48[arg_0->unk_1AE4]->unk_22C = 0;
    }
}

// match: ?sub_168E10@type_3DC9B0@@QAEHPAUtype_3DAFC8@@@Z @ 0x00168E10
// sp-match: ?sub_168E10@type_3DC9B0@@QAEHPAUtype_3DAFC8@@@Z @ 0x00108610
// Mounts the soldier arg_0 (0 when someone else uses it): its aim zeroed
// and reset, its trigger's reload setting, and its trigger's script told
// "EntityAttachedToWeapon".
RwInt32 type_3DC9B0::sub_168E10(type_3DAFC8 *arg_0)
{
    type_712B0 *var_4;

    unk_3C0 = 0;
    unk_3B8 = 0;
    unk_3C4 = 0;
    unk_3BC = 0;
    if (unk_5C0.sub_D4910() && unk_5C0.sub_D4910() != (type_3D3548 *)arg_0)
        return 0;
    if (get_unk_34C() && !unk_498)
        unk_3B4 = ((MountedWeaponTrigger *)get_unk_34C())->unk_C8;
    unk_4F0 = 1;
    unk_5C0.sub_D48D0((type_3D3548 *)arg_0);
    sub_168F40();
    var_4 = get_unk_34C();
    if (var_4 && arg_0)
        sub_6B5F0("EntityAttachedToWeapon", (type_67620 *)(var_4->sub_BDF50()), 0, (type_3D2E7C *)((RwInt32)arg_0->vf_098()), 0, 0, 1, 0);
    return 1;
}

// match: ?sub_168F40@type_3DC9B0@@QAEXXZ @ 0x00168F40
// sp-match: ?sub_168F40@type_3DC9B0@@QAEXXZ @ 0x00106E60
void type_3DC9B0::sub_168F40()
{
    RwFrame *var_4;
    RwV3d var_10;

    var_4 = RpClumpGetFrame(get_unk_264());
    unk_540 = *RwFrameGetMatrix(var_4);
    var_10 = unk_540.pos;
    RwV3dIncrementScaledMacro(&var_10, &unk_540.at, 1000.0f);
    unk_540.pos.x = unk_540.pos.y = unk_540.pos.z = 0.0f;
}

// match: ?sub_169000@type_3DC9B0@@QAEXPAUtype_3DAFC8@@@Z @ 0x00169000
// sp-match: ?sub_169000@type_3DC9B0@@QAEXPAUtype_3DAFC8@@@Z @ 0x001086D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Dismounts the soldier arg_0 (when it is its user): its trigger's script
// told "EntityDetachedFromWeapon", its firing sound stopped, its firing
// and NPC aim ended, its user cleared, and its trigger's reload setting.
void type_3DC9B0::sub_169000(type_3DAFC8 *arg_0)
{
    type_4E1B70 *var_10;
    type_3D3548 *var_C;
    type_712B0 *bp_8;
    type_3D3548 *bp_4;

    bp_4 = unk_5C0.sub_D4910();
    if ((type_3D3548 *)arg_0 == bp_4)
    {
        bp_8 = get_unk_34C();
        if (bp_8 && bp_4)
            sub_6B5F0("EntityDetachedFromWeapon", (type_67620 *)(bp_8->sub_BDF50()), 0, (type_3D2E7C *)((RwInt32)bp_4->vf_098()), 0, 0, 1, 0);
        if (unk_480)
        {
            var_10 = sub_166990(unk_3B0);
            var_C = unk_5C0.sub_D4910();
            var_C->unk_1C0.sub_8A910(unk_49C);
            var_C->unk_1C0.sub_8A980(&var_10->unk_64, this, 0, var_C->sub_CD550(), 0, 0);
            unk_480 = 0;
        }
        sub_169170(0);
        unk_4F0 = 0;
        unk_4BC = 0;
        unk_5C0.sub_D48D0(0);
        sub_16A620();
        if (get_unk_34C() && !unk_498)
            unk_3B4 = ((MountedWeaponTrigger *)get_unk_34C())->unk_C8;
    }
}

// match: ?sub_169170@type_3DC9B0@@QAEXH@Z @ 0x00169170
// sp-match: ?sub_169170@type_3DC9B0@@QAEXH@Z @ 0x00106EA0
void type_3DC9B0::sub_169170(RwInt32 arg_0)
{
    unk_4F4 = arg_0;
}

// match: ?sub_169190@type_3DC9B0@@QAEHPAUtype_3D3548@@@Z @ 0x00169190
// sp-match: ?sub_169190@type_3DC9B0@@QAEHPAUtype_3D3548@@@Z @ 0x00106EB0
RwInt32 type_3DC9B0::sub_169190(type_3D3548 *arg_0)
{
    Trigger *var_4;

    var_4 = unk_344.unk_08;
    if (arg_0->vf_00C())
    {
        if (unk_498 == 1)
            return !unk_4F0 && unk_490 && ((VehicleTrigger *)var_4)->vf_030();
        if (unk_498 == 2)
            return !unk_4F0 && unk_490 && ((AnimatedBGTrigger *)var_4)->vf_030();
        return !unk_4F0 && unk_490 && (((MountedWeaponTrigger *)var_4)->unk_CC & 1);
    }
    if (!unk_5C0.sub_D4910() || unk_5C0.sub_D4910() == arg_0)
    {
        if (arg_0->unk_2C_0)
        {
            if (unk_498 == 1)
                return ((VehicleTrigger *)var_4)->vf_034();
            if (unk_498 == 2)
                return ((AnimatedBGTrigger *)var_4)->vf_034();
            return ((MountedWeaponTrigger *)var_4)->unk_CC & 2;
        }
        if (unk_498 == 1)
            return ((VehicleTrigger *)var_4)->vf_038();
        if (unk_498 == 2)
            return ((AnimatedBGTrigger *)var_4)->vf_038();
        return ((MountedWeaponTrigger *)var_4)->unk_CC & 4;
    }
    return 0;
}

// match: ?sub_169350@type_3DC9B0@@QAEHH@Z @ 0x00169350
// sp-match: ?sub_169350@type_3DC9B0@@QAEHH@Z @ 0x00106FF0
RwInt32 type_3DC9B0::sub_169350(RwInt32 arg_0)
{
    if (arg_0)
        return unk_48C;
    return 1;
}

// match: ?sub_169380@type_3DC9B0@@QAEHXZ @ 0x00169380
// sp-match: ?sub_169380@type_3DC9B0@@QAEHXZ @ 0x00109310
// Fires it for its user (none: 0): its firing sound, a projectile (kind 4
// two, from its tags 1 and 2 or 3 and 4 by turns) along its muzzle's matrix
// turned by a random spread, one round of its trigger's ammunition ("OutOfAmmo"
// on the last), its recoil, and for a player the camera shake and its fire
// animation. 1 when it fired (sub_169B70), else 0.
RwInt32 type_3DC9B0::sub_169380()
{
    type_4E1B70 *var_8 = sub_166990(unk_3B0);
    static type_10F710_1A48_29C var_4E2254;
    RwInt32 var_C = 0;
    type_3D3548 *var_10 = unk_5C0.sub_D4910();

    if (!var_10)
        return var_C;
    if (sub_169B70())
    {
        unk_470 = 1;
        if (var_8->unk_54)
        {
            if (var_8->unk_58)
            {
                if (!unk_480)
                {
                    type_3D3548 *var_14 = unk_5C0.sub_D4910();

                    unk_49C = var_14->unk_1C0.sub_8A980(&var_8->unk_5C, this, 0, var_14->sub_CD550(), 0, 0);
                }
                unk_480 = 1;
            }
            else
            {
                type_3D3548 *var_18 = unk_5C0.sub_D4910();

                var_18->unk_1C0.sub_8A980(&var_8->unk_5C, this, 0, var_18->sub_CD550(), 0, 0);
            }
        }
        RwInt32 var_1C = 0x201; // not an address: projectile kind flags
        if (var_10->unk_2C_1)
            var_1C = 0x202; // not an address: projectile kind flags
        memset(&var_4E2254, 0, sizeof(var_4E2254));
        var_4E2254.unk_00 = 0;
        var_4E2254.unk_04_r = (RwReal)var_8->unk_1C;
        if (unk_4F0 && get_unk_34C() && !unk_498
            && (RwReal)((MountedWeaponTrigger *)get_unk_34C())->unk_D0 != -1.0f)
            var_4E2254.unk_04_r = (RwReal)((MountedWeaponTrigger *)get_unk_34C())->unk_D0;
        RwMatrix var_80;
        RwMatrix var_C0;
        switch (unk_3B0)
        {
        case 4:
        {
            RwInt32 var_30;
            RwInt32 var_34;

            if (unk_4E8)
            {
                var_30 = 1;
                var_34 = 2;
            }
            else
            {
                var_30 = 3;
                var_34 = 4;
            }
            sub_169F30(&var_80, var_30);
            sub_169F30(&var_C0, var_34);
            break;
        }
        default:
            sub_169F30(&var_80, -1);
            break;
        }
        RwReal var_D8 = frand_range(-var_8->unk_C0_r, var_8->unk_C0_r);
        RwReal var_F0 = frand_range(-var_8->unk_C0_r, var_8->unk_C0_r);
        RwMatrixRotate(&var_80, &stru_3DC984, var_D8, rwCOMBINEPRECONCAT);
        RwMatrixRotate(&var_80, &stru_3DC990, var_F0, rwCOMBINEPRECONCAT);
        RwV3d var_FC;
        RwV3dScaleMacro(&var_FC, &var_80.at, var_8->unk_14_r);
        sub_15F2C0(var_1C, (RwInt32)var_10, &var_80, &var_FC, unk_4A0, (type_439A48 *)&var_4E2254, (RwInt32)&var_8->unk_CC);
        if (unk_3B0 == 4)
            sub_15F2C0(var_1C, (RwInt32)var_10, &var_C0, &var_FC, unk_4A0, (type_439A48 *)&var_4E2254, (RwInt32)&var_8->unk_CC);
        unk_410 = 0;
        if (unk_4F0)
        {
            unk_3B4--;
            if (!unk_3B4 && unk_4F0)
            {
                unk_4F4 = 0;
                sub_6B5F0("OutOfAmmo", (type_67620 *)(var_10->vf_098()), 0, 0, 0, 0, 1, 0);
                sub_16A660();
            }
        }
        RwReal var_104;
        unk_414 = ((var_104 = (RwReal)rand()) /= 32767.0f) * 2.0f * var_8->unk_24_r - var_8->unk_24_r;
        RwReal var_10C;
        unk_418 = ((var_10C = (RwReal)rand()) /= 32767.0f) * 2.0f * var_8->unk_28_r + 1.0f - var_8->unk_28_r;
        if (unk_4A4)
            unk_4A4 = 0;
        else
            unk_4A4 = 1;
        RwReal var_110;
        if (unk_488)
            var_110 = var_8->unk_3C_r;
        else
            var_110 = var_8->unk_38_r;
        if (var_10->vf_00C())
        {
            type_3D3548 *var_114 = ((type_10F710 *)var_10)->unk_2110.sub_D4910();

            if (var_114)
                ((type_3DD948 *)var_114)->sub_175E50(9.0f * var_110, 7.0f * var_110, 1.0f * var_110);
            RwInt32 var_118;
            RwInt32 var_11C;
            if (sub_77B70(var_8->unk_C8->unk_2C, (void **)(&var_11C), (void **)(&var_118))
                && (!unk_484 || unk_3B0 == 4))
            {
                unk_284->sub_794C0(0);
                if (unk_3B0 == 4)
                {
                    if (unk_4E8 && sub_77B70(var_8->unk_C8->unk_30, (void **)(&var_11C), (void **)(&var_118)))
                        unk_284->sub_796A0((RtAnimAnimation *)var_11C, var_8->unk_C8->unk_30, 0,
                                           (type_783F0 *)var_118, 0, 1.0f, 1.0f);
                    else
                        unk_284->sub_796A0((RtAnimAnimation *)var_11C, var_8->unk_C8->unk_2C, 0,
                                           (type_783F0 *)var_118, 0, 1.0f, 1.0f);
                    get_unk_284()->sub_79930(sub_16B0C0, 1.0f, 1.0f);
                }
                else
                {
                    unk_284->sub_796A0((RtAnimAnimation *)var_11C, var_8->unk_C8->unk_2C, 0,
                                       (type_783F0 *)var_118, 0, 1.0f, 1.0f);
                }
#ifdef CODFH_SP
                ((type_78AC0 *)get_unk_284())->sub_6DF40();
#else
                get_unk_284()->clear_last_unk_08_30();
#endif
                unk_484 = 1;
                unk_494 = 1;
            }
        }
        unk_4E8 = !unk_4E8;
        var_C = 1;
    }
    return var_C;
}

// match: ?sub_169B70@type_3DC9B0@@QAEHXZ @ 0x00169B70
// sp-match: ?sub_169B70@type_3DC9B0@@QAEHXZ @ 0x00107010
// Whether it can fire: not held off (unk_478), its reload time passed and
// ammunition left.
RwInt32 type_3DC9B0::sub_169B70()
{
    if (!unk_478 && unk_410 > unk_4C8 && unk_3B4 > 0)
        return 1;
    return 0;
}

// match: ?sub_169BC0@@YAHPAUtype_F2FF0@@@Z @ 0x00169BC0
// match: __ehhandler$?sub_169BC0@@YAHPAUtype_F2FF0@@@Z-0x8 @ 0x00301FA0
// match: __ehhandler$?sub_169BC0@@YAHPAUtype_F2FF0@@@Z @ 0x00301FA8
// sp-match: ?sub_169BC0@@YAHPAUtype_F2FF0@@@Z @ 0x00107040
RwInt32 sub_169BC0(type_F2FF0 *arg_0)
{
    RwInt32 var_14 = 1;
    type_D48D0 var_18;

    var_18 = arg_0->unk_150;
    type_3D3548 *var_20 = var_18.sub_D4910();
    if (var_20)
    {
        type_3DC9B0 *var_24 = (type_3DC9B0 *)var_20;
        RpHAnimHierarchy *var_28 = var_24->unk_284->unk_18;
        RpClump *var_2C = var_24->unk_25C.unk_08;
        RwMatrix var_70;

        sub_EC310(var_2C, var_28, &var_70, arg_0->unk_158, 0, 1);
        arg_0->unk_00 = var_70;
    }
    else if (arg_0->unk_44->unk_20 == 0.0f)
    {
        var_14 = 0;
    }
    return var_14;
}

// match: ?vf_170@type_3DC9B0@@UAEXHHHH@Z @ 0x00169CC0
// sp-match: ?vf_170@type_3DC9B0@@UAEXHHHH@Z @ 0x00109890
// Its handler for the message arg_0 with the data arg_4: 1 (its animation
// ended) replays the fire animation while it keeps firing, else ends it
// (kind 4 plays its unk_34 and releases the hold); 0x516 spawns the
// particle system *arg_4 at its bone, following it (sub_169BC0).
void type_3DC9B0::vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_4E1B70 *var_8 = sub_166990(unk_3B0);
#ifdef CODFH_SP
    // shape: the animation lookups' outputs at function scope, so they keep
    // their own slots (SP 0x109979, 0x1099F2: frame 0x58).
    RwInt32 var_10;
    RwInt32 var_14;
    RwInt32 var_18;
    RwInt32 var_1C;
#endif

    switch (arg_0)
    {
    case 1:
        if (unk_484 && unk_470 && unk_410 - unk_4C8 < 3.0f)
        {
#ifndef CODFH_SP
            RwInt32 var_10;
            RwInt32 var_14;

#endif
            if (sub_77B70(var_8->unk_C8->unk_2C, (void **)(&var_14), (void **)(&var_10)))
            {
                unk_284->sub_794C0(0);
                unk_284->sub_796A0((RtAnimAnimation *)var_14, var_8->unk_C8->unk_2C, 0, (type_783F0 *)var_10, 0,
                                   1.0f, 1.0f);
                unk_484 = 1;
            }
        }
        else
        {
            if (unk_3B0 == 4)
            {
#ifndef CODFH_SP
                RwInt32 var_18;
                RwInt32 var_1C;

#endif
                if (sub_77B70(var_8->unk_C8->unk_34, (void **)(&var_1C), (void **)(&var_18)))
                {
                    unk_284->sub_794C0(0);
                    unk_284->sub_796A0((RtAnimAnimation *)var_1C, var_8->unk_C8->unk_34, 0, (type_783F0 *)var_18,
                                       0, 1.0f, 1.0f);
                    get_unk_284()->sub_79930(sub_16B0C0, 1.0f, 1.0f);
#ifdef CODFH_SP // SP expands the clear helper here (SP 0x109A60)
                    get_unk_284()->clear_last_unk_08_30();
#else
                    ((type_78AC0 *)get_unk_284())->sub_6DF40();
#endif
                }
            }
            unk_484 = 0;
        }
        break;
    case 0x516:
    {
        type_13AE40_msg *var_28 = (type_13AE40_msg *)arg_4;
        RpHAnimHierarchy *var_2C = unk_284->unk_18;
        RpClump *var_30 = unk_25C.unk_08;
        RwMatrix var_70;

        if (sub_EC310(var_30, var_2C, &var_70, var_28->unk_00, 0, 1))
        {
            type_F2FF0 *var_74 = (type_F2FF0 *)sub_F2FF0(var_28->unk_0C, &var_70, 0, 0, 0, 0);

            if (var_74)
            {
                var_74->unk_40 |= 0x40;
                var_74->unk_150_h = unk_384_h;
                var_74->unk_158 = var_28->unk_00;
                var_74->unk_154 = sub_169BC0;
            }
        }
        break;
    }
    }
}

// match: ?sub_169F30@type_3DC9B0@@QAEXPAURwMatrixTag@@H@Z @ 0x00169F30
// sp-match: ?sub_169F30@type_3DC9B0@@QAEXPAURwMatrixTag@@H@Z @ 0x001070D0
// The matrix of its muzzle (-1: the weapon's frame moved by its settings'
// offset) or of its bone "FR01" to "FR04" (1 to 3, else 4) into *arg_0.
void type_3DC9B0::sub_169F30(RwMatrix *arg_0, RwInt32 arg_4)
{
    type_4E1B70 *var_4 = sub_166990(unk_3B0);

    if (arg_4 == -1)
    {
        *arg_0 = *RwFrameGetLTM(RpAtomicGetFrame(unk_4A8));
        RwMatrixTranslate(arg_0, &var_4->unk_2C, rwCOMBINEPRECONCAT);
    }
    else
    {
        RpClump *var_8 = unk_25C.unk_08;

        switch (arg_4)
        {
        case 1:
            sub_EC2D0(var_8, (RwInt32)arg_0, 0x46523031, 0, 1); // not an address: the tag 'FR01'
            break;
        case 2:
            sub_EC2D0(var_8, (RwInt32)arg_0, 0x46523032, 0, 1); // not an address: 'FR02'
            break;
        case 3:
            sub_EC2D0(var_8, (RwInt32)arg_0, 0x46523033, 0, 1); // not an address: 'FR03'
            break;
        default:
            sub_EC2D0(var_8, (RwInt32)arg_0, 0x46523034, 0, 1); // not an address: 'FR04'
            break;
        }
    }
}

// match: ?sub_16A030@type_3DC9B0@@QAEXPAURwMatrixTag@@@Z @ 0x0016A030
// sp-match: ?sub_16A030@type_3DC9B0@@QAEXPAURwMatrixTag@@@Z @ 0x00107190
// Its seat's matrix into *arg_0: its mount frame's (unk_340) raised 120
// and moved by its settings' unk_74, through the frame's parents to world
// space; then turns the weapon's frame to its pitch and yaw in place.
void type_3DC9B0::sub_16A030(RwMatrix *arg_0)
{
    RwV3d var_10;
    type_4E1B70 *var_14;
    RwFrame *var_1C;
    RwFrame *var_20;

    var_10.x = 0;
    var_10.y = 120.0f;
    var_10.z = 0;
    var_14 = sub_166990(unk_3B0);
    var_1C = get_unk_340();
    var_20 = RwFrameGetParent(var_1C);
    *arg_0 = *RwFrameGetMatrix(var_1C);
    RwMatrixTranslate(arg_0, &var_14->unk_74, rwCOMBINEPRECONCAT);
    RwMatrixTranslate(arg_0, &var_10, rwCOMBINEPRECONCAT);
    while (var_20)
    {
        RwMatrix var_60 = *RwFrameGetMatrix(var_20);
        RwMatrix var_A0;

        RwMatrixMultiply(&var_A0, arg_0, &var_60);
        *arg_0 = var_A0;
        var_20 = RwFrameGetParent(var_20);
    }
    if (unk_4A8)
    {
        RwFrame *var_A4 = RpAtomicGetFrame(unk_4A8);
        RwMatrix *var_A8 = RwFrameGetMatrix(var_A4);
        RwV3d var_B4 = var_A8->pos;

        RwFrameRotate(var_A4, &stru_3DC990, unk_3BC, rwCOMBINEREPLACE);
        RwFrameRotate(var_A4, &stru_3DC984, unk_3B8, rwCOMBINEPRECONCAT);
        RwFrameTranslate(var_A4, &var_B4, rwCOMBINEPOSTCONCAT);
    }
}

// match: ?sub_16A1D0@type_3DC9B0@@QAEXPAUtype_10F710@@H@Z @ 0x0016A1D0
// sp-match: ?sub_16A1D0@type_3DC9B0@@QAEXPAUtype_10F710@@H@Z @ 0x001072B0
// Zooms it in (arg_4, when its settings allow it, unk_A4) or out for the
// player arg_0.
void type_3DC9B0::sub_16A1D0(type_10F710 *arg_0, RwInt32 arg_4)
{
    type_4E1B70 *var_4 = sub_166990(unk_3B0);

    if (arg_4 && var_4->unk_A4)
    {
        unk_424 = 1;
        unk_488 = 1;
    }
    else
    {
        unk_424 = 2;
        unk_488 = 0;
    }
}

// match: ?sub_16A240@type_3DC9B0@@QAEHXZ @ 0x0016A240
// sp-match: ?sub_16A240@type_3DC9B0@@QAEHXZ @ 0x001087D0
// Its key: the path node of kind 0xC nearest it (within 500), turned to its
// "MONA" bone's matrix (sub_16A3B0) and taken as its node (sub_F7BA0); the
// node's index, or -1 with none.
RwInt32 type_3DC9B0::sub_16A240()
{
    type_154C0_1048 var_68;

    var_68.unk_04 = *sub_CD550();
    var_68.unk_10 = 500.0f;
    var_68.unk_00 = 0;
    var_68.unk_18 = sub_F7E80(0xC);
    var_68.unk_1C = 0;
    sub_F8970(&var_68, 1, 0);
    type_F8350 *var_6C = var_68.unk_34;
    if (var_6C)
    {
        RwMatrix var_B0;

        sub_16A3B0(&var_B0, 1, 0);
        var_6C->unk_10 = var_B0.pos;
        RtQuatConvertFromMatrix(&var_6C->unk_1C, &var_B0);
        sub_F7BA0(0, var_6C, 0);
        return sub_FA920(var_6C);
    }
    return -1;
}

// match: ?sub_16A340@@YAPAUtype_3DC9B0@@H@Z @ 0x0016A340
// sp-match: ?sub_16A340@@YAPAUtype_3DC9B0@@H@Z @ 0x00107300
// The mounted weapon (list 13) whose key (unk_4EC) is arg_0, or 0.
type_3DC9B0 *sub_16A340(RwInt32 arg_0)
{
    type_3D3548 *var_4;

    var_4 = dword_4B8600[13].unk_00;
    while (var_4)
    {
        type_3DC9B0 *var_8 = (type_3DC9B0 *)var_4;

        if (var_8->unk_4EC == arg_0)
            return var_8;
        var_4 = var_4->unk_10;
    }
    return 0;
}

// match: ?sub_16A380@@YAPAUtype_3DC9B0@@PAUtype_F8350@@@Z @ 0x0016A380
// sp-match: ?sub_16A380@@YAPAUtype_3DC9B0@@PAUtype_F8350@@@Z @ 0x00107330
type_3DC9B0 *sub_16A380(type_F8350 *arg_0)
{
    RwInt32 var_4 = sub_FA920(arg_0);

    return sub_16A340(var_4);
}

// match: ?sub_16A3B0@type_3DC9B0@@QAEHPAURwMatrixTag@@HH@Z @ 0x0016A3B0
// sp-match: ?sub_16A3B0@type_3DC9B0@@QAEHPAURwMatrixTag@@HH@Z @ 0x00107350
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The matrix of its bone "MONA" (arg_4) or "ATMT" into *arg_0, in world
// space unless arg_8; 0 without a clump.
RwInt32 type_3DC9B0::sub_16A3B0(RwMatrix *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RpClump *var_4 = unk_25C.unk_08;

    if (var_4)
    {
        RwInt32 var_C = arg_4 ? 0x4D4F4E41 : 0x41544D54; // not addresses: the tags 'MONA' and 'ATMT'
        type_EC1F0 *bp_8 = sub_EC1F0(var_4, var_C);

        *arg_0 = bp_8->unk_10;
        if (!arg_8)
        {
            RwFrame *var_10 = RpClumpGetFrame(var_4);

            RwMatrixTransform(arg_0, RwFrameGetMatrix(var_10), rwCOMBINEPOSTCONCAT);
        }
        return 1;
    }
    return 0;
}

// match: ?sub_16A440@type_3DC9B0@@QAEXPAURwMatrixTag@@@Z @ 0x0016A440
// sp-match: ?sub_16A440@type_3DC9B0@@QAEXPAURwMatrixTag@@@Z @ 0x001073C0
// Turns the weapon's frame to the world matrix *arg_0 (its rotation only,
// relative to its mount frame's), keeping its position.
void type_3DC9B0::sub_16A440(RwMatrix *arg_0)
{
    RwFrame *var_8 = RpAtomicGetFrame(unk_4A8);
    RwMatrix *var_C = RwFrameGetMatrix(var_8);
    RwMatrix var_50 = *arg_0;
    RwMatrix var_A0 = *RwFrameGetLTM(get_unk_340());

    RwMatrixOrthoNormalize(&var_50, &var_50);
    var_A0.pos.x = 0;
    var_A0.pos.y = 0;
    var_A0.pos.z = 0;
    var_50.pos.x = 0;
    var_50.pos.y = 0;
    var_50.pos.z = 0;
    RwMatrix var_E0;
    RwMatrixInvert(&var_E0, &var_A0);
    RwMatrixTransform(&var_E0, &var_50, rwCOMBINEPRECONCAT);
    RwV3d var_EC = var_C->pos;
    *var_C = var_E0;
    var_C->pos = var_EC;
    RwFrameUpdateObjects(var_8);
}

// match: ?sub_16A580@type_3DC9B0@@QAEXPAURwV3d@@@Z @ 0x0016A580
// sp-match: ?sub_16A580@type_3DC9B0@@QAEXPAURwV3d@@@Z @ 0x001074C0
// The point it aims at into *arg_0: 1000 along its aim from its muzzle.
void type_3DC9B0::sub_16A580(RwV3d *arg_0)
{
    RwMatrix var_50;

    sub_169F30(&var_50, -1);
    *arg_0 = var_50.pos;
    RwV3dIncrementScaledMacro(arg_0, &unk_540.at, 1000.0f);
}

// match: ?sub_16A620@type_3DC9B0@@QAEXXZ @ 0x0016A620
// sp-match: ?sub_16A620@type_3DC9B0@@QAEXXZ @ 0x00107530
// Puts the weapon's frame back to its rest matrix (unk_500).
void type_3DC9B0::sub_16A620()
{
    RwMatrix *var_4 = RwFrameGetMatrix(RpAtomicGetFrame(unk_4A8));

    *var_4 = unk_500;
}

// match: ?sub_16A660@type_3DC9B0@@QAEXXZ @ 0x0016A660
// sp-match: ?sub_16A660@type_3DC9B0@@QAEXXZ @ 0x001088A0
void type_3DC9B0::sub_16A660()
{
    unk_3B4 = sub_16A680();
}

// match: ?sub_16A680@type_3DC9B0@@QAEHXZ @ 0x0016A680
// sp-match: ?sub_16A680@type_3DC9B0@@QAEHXZ @ 0x00107550
RwInt32 type_3DC9B0::sub_16A680()
{
    type_4E1B70 *var_4 = sub_166990(unk_3B0);

    if (get_unk_34C())
    {
        if (unk_498 == 1 && (RwReal)((VehicleTrigger *)get_unk_34C())->unk_1DC != -1.0f)
            return ((VehicleTrigger *)get_unk_34C())->unk_1DC;
        if (unk_498 == 2 && (RwReal)((AnimatedBGTrigger *)get_unk_34C())->unk_16C != -1.0f)
            return ((AnimatedBGTrigger *)get_unk_34C())->unk_16C;
        if ((RwReal)((MountedWeaponTrigger *)get_unk_34C())->unk_DC != -1.0f)
            return ((MountedWeaponTrigger *)get_unk_34C())->unk_DC;
    }
    return var_4->unk_40;
}

// match: ?sub_16A790@type_3DC9B0@@QAEMXZ @ 0x0016A790
// sp-match: ?sub_16A790@type_3DC9B0@@QAEMXZ @ 0x001075F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The pitch's limit (in degrees): its trigger's (by kind) unless -1, else
// its settings' unk_B0.
RwReal type_3DC9B0::sub_16A790()
{
    type_4E1B70 *var_8 = sub_166990(unk_3B0);
    Trigger *l4 = unk_344.unk_08;

    if (l4)
    {
        if (!unk_498)
        {
            if (((MountedWeaponTrigger *)l4)->unk_D4 != -1.0f)
                return ((MountedWeaponTrigger *)l4)->unk_D4;
        }
        else if (unk_498 == 2)
        {
            if (((AnimatedBGTrigger *)l4)->unk_164 != -1.0f)
                return ((AnimatedBGTrigger *)l4)->unk_164;
        }
        else if (unk_498 == 1)
        {
            if (((VehicleTrigger *)l4)->unk_1D4 != -1.0f)
                return ((VehicleTrigger *)l4)->unk_1D4;
        }
    }
    if (var_8 && var_8->unk_B0 != -1.0f)
        return var_8->unk_B0;
    return var_8->unk_B0;
}

// match: ?sub_16A890@type_3DC9B0@@QAEMXZ @ 0x0016A890
// sp-match: ?sub_16A890@type_3DC9B0@@QAEMXZ @ 0x00107670
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise the yaw's (unk_D8, unk_168, unk_1D8 and unk_B4).
RwReal type_3DC9B0::sub_16A890()
{
    type_4E1B70 *var_8 = sub_166990(unk_3B0);
    Trigger *l4 = unk_344.unk_08;

    if (l4)
    {
        if (!unk_498)
        {
            if (((MountedWeaponTrigger *)l4)->unk_D8 != -1.0f)
                return ((MountedWeaponTrigger *)l4)->unk_D8;
        }
        else if (unk_498 == 2)
        {
            if (((AnimatedBGTrigger *)l4)->unk_168 != -1.0f)
                return ((AnimatedBGTrigger *)l4)->unk_168;
        }
        else if (unk_498 == 1)
        {
            if (((VehicleTrigger *)l4)->unk_1D8 != -1.0f)
                return ((VehicleTrigger *)l4)->unk_1D8;
        }
    }
    if (var_8 && var_8->unk_B4 != -1.0f)
        return var_8->unk_B4;
    return var_8->unk_B4;
}

// match: ?sub_16A990@type_3DC9B0@@QAEHPAURwV3d@@MM@Z @ 0x0016A990
// sp-match: ?sub_16A990@type_3DC9B0@@QAEHPAURwV3d@@MM@Z @ 0x001076F0
RwInt32 type_3DC9B0::sub_16A990(RwV3d *arg_0, RwReal arg_4, RwReal arg_8)
{
    RpClump *var_4 = unk_25C.unk_08;

    if (var_4)
    {
        RwFrame *var_8 = RpClumpGetFrame(var_4);

        return sub_1409C0(arg_0, RwFrameGetMatrix(var_8), arg_4 + unk_4C0, arg_8 + unk_4C4);
    }
    return 0;
}

// match: ?vf_058@type_3DC9B0@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x0016AA00
// sp-match: ?vf_058@type_3DC9B0@@UAEHPAUtype_3DF8D8_04@@@Z @ 0x00107740
RwInt32 type_3DC9B0::vf_058(type_3DF8D8_04 *arg_0)
{
    type_4E1B70 *var_4 = 0;

    if (unk_498 == 1)
        var_4 = sub_166990(((VehicleTrigger *)get_unk_34C())->unk_1B0);
    else if (unk_498 == 2)
        var_4 = sub_166990(((AnimatedBGTrigger *)get_unk_34C())->unk_140);
    else
        var_4 = sub_166990(((MountedWeaponTrigger *)get_unk_34C())->unk_C0);
    if (arg_0->unk_00 == var_4->unk_00.unk_00 && arg_0->unk_04 == var_4->unk_00.unk_04)
        return 1;
    if (arg_0->unk_00 == var_4->unk_08.unk_00 && arg_0->unk_04 == var_4->unk_08.unk_04)
        return 1;
    return 0;
}

// match: ?sub_16AAE0@type_3DC9B0@@QAEXXZ @ 0x0016AAE0
// sp-match: ?sub_16AAE0@type_3DC9B0@@QAEXXZ @ 0x001077C0
// Its NPC user's aim and firing: with a target, turns its aim matrix
// (unk_540) towards the target's aim point by at most flt_429E94 degrees
// (kept when the aim stays in its limits, sub_16A990); then tells the
// user's script "OKToFireMountedWeapon" when on target (within
// flt_429E9C degrees) and the AI allows it, else "StopFiringMountedWeapon"
// (with whether it has tracked the target under ten seconds).
void type_3DC9B0::sub_16AAE0()
{
    type_3D3548 *var_8 = unk_5C0.sub_D4910();

    if (var_8)
    {
        RwInt32 var_C = 0;
        AIData *var_10 = var_8->vf_120();
        type_3D3548 *var_14 = var_10->unk_1374.sub_D4910();
        if (var_14)
        {
            RwMatrix var_60;
            RwV3d var_6C;
            RwV3d var_78;
            RwMatrix var_C0;
            RwV3d var_CC;

            sub_169F30(&var_60, -1);
            var_14->vf_110(&var_6C, var_8, 0);
            var_78 = var_60.pos;
            RwV3dSubMacro(&var_78, &var_6C, &var_78);
            RwV3dNormalize(&var_78, &var_78);
            sub_1213D0(&var_78, &var_C0);
            RwV3dCrossProductMacro(&var_CC, &var_60.at, &var_C0.at);
            if (RwV3dDotProductMacro(&var_CC, &var_CC) > 0.0001f)
            {
                RwReal var_D0;

                RwV3dNormalize(&var_CC, &var_CC);
                RwReal var_E4 = acos(0.99999f > ((var_D0 = RwV3dDotProductMacro(&var_60.at, &var_C0.at)) > -0.99999f
                                                     ? var_D0 : -0.99999f)
                                         ? (var_D0 > -0.99999f ? var_D0 : -0.99999f)
                                         : 0.99999f)
                                * 57.29577637f;
                if (var_E4 < flt_429E9C)
                    var_C = 1;
                RwReal var_EC = var_E4 < flt_429E94 ? var_E4 : flt_429E94;
                RwMatrixOrthoNormalize(&unk_540, &unk_540);
                RwMatrix var_130 = unk_540;
                RwMatrixRotate(&var_130, &var_CC, var_EC, rwCOMBINEPOSTCONCAT);
                RwFrame *var_138 = RpClumpGetFrame(get_unk_264());
                RwMatrix var_180 = *RwFrameGetMatrix(var_138);
                RwReal var_184 = RwV3dDotProductMacro(&var_180.at, &var_130.at);
                RwReal var_188 = RwV3dDotProductMacro(&unk_540.at, &var_180.at);
                if (var_184 > flt_429E98 || var_184 > var_188)
                {
                    RwV3d var_194 = var_180.pos;

                    RwV3dIncrementScaledMacro(&var_194, &var_130.at, 1000.0f);
                    if (sub_16A990(&var_194, -0.15f, -0.15f))
                        unk_540 = var_130;
                }
            }
            else
            {
                var_C = 1;
            }
        }
        RwBool var_198 = var_8->vf_120()->sub_18DF0(var_14, 0);
        RwBool var_19C = var_8->vf_120()->sub_18DF0(var_14, 1);
        if (var_C && (var_198 || unk_4BC))
        {
            sub_6B5F0("OKToFireMountedWeapon", (type_67620 *)(var_8->vf_098()), 0, 0, 0, 0, 1, 0);
        }
        else if (var_19C)
        {
            RwInt32 var_1A4[2];

            var_1A4[0] = 1;
            var_1A4[1] = var_8->vf_120()->get_unk_1378() < 10.0f;
            sub_6B5F0("StopFiringMountedWeapon", (type_67620 *)(var_8->vf_098()), 0, 0, var_1A4, 2, 1, 0);
        }
        else
        {
            RwInt32 var_1B8[2];

            var_1B8[0] = 0;
            var_1B8[1] = 0;
            sub_6B5F0("StopFiringMountedWeapon", (type_67620 *)(var_8->vf_098()), 0, 0, var_1B8, 2, 1, 0);
        }
    }
}

// match: ?sub_16B0C0@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x0016B0C0
// sp-match: ?sub_16B0C0@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x001088B0
// Kind 4's animation callback (the weapon arg_8): on its first start it
// bakes a pose key of its hierarchy's rest pose (bones 1 to 3 masked
// in), on later starts restores it; between starts it turns its bones 1 to
// 3 by its yaw and pitch (sub_17FC00).
void sub_16B0C0(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C)
{
    type_3DC9B0 *var_4;
    type_7CBD0 *var_8;
    RwFrame *var_10;
    RpHAnimHierarchy *var_18;
    RwMatrix *var_1C;
    RtQuat *var_20;
    type_7CBD0_hdr *var_24;
    type_7CBD0_t *var_28;
    RwMatrix var_70;
    RwInt32 var_74;
    RwMatrix var_C0;
    RwInt32 var_C4;
    RtQuat *var_C8;
    RpHAnimHierarchy *var_D4;
    RtQuat *var_D8;
    RtQuat *var_DC;
    RwV3d var_EC;
    RwV3d var_F8;

    var_4 = (type_3DC9B0 *)arg_8;
    var_8 = (type_7CBD0 *)arg_4->unk_144;
    if (arg_C && !var_4->unk_4D4)
    {
        var_10 = var_4->get_unk_340();
        var_18 = var_4->get_unk_284()->unk_18;
        var_1C = RpHAnimHierarchyGetMatrixArray(var_18);
        var_4->unk_4D8 = var_18->numNodes * sizeof(RtQuat) + sizeof(type_7CBD0_hdr);
        var_4->unk_4D4 = (type_7CBD0_hdr *)RwMalloc(var_4->unk_4D8, 0x34251); // not an address: a memory hint
        memset(var_4->unk_4D4, 0, var_4->unk_4D8);
        var_4->unk_4D4->unk_00 = var_18->numNodes;
        var_4->unk_4D4->unk_01 = var_18->numNodes;
        var_4->unk_4D4->unk_02 = 1;
        var_4->unk_4D4->unk_08 = 0;
        var_4->unk_4D4->unk_08 |= 1 << var_4->unk_4DC;
        var_4->unk_4D4->unk_08 |= 1 << var_4->unk_4E0;
        var_4->unk_4D4->unk_08 |= 1 << var_4->unk_4E4;
        var_4->unk_4D4->unk_10 = 0;
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_4D4);
        var_20 = var_8->unk_10;
        var_24 = var_4->unk_4D4;
        var_28 = (type_7CBD0_t *)&var_8->unk_10[var_24->unk_00];
        RwMatrixInvert(&var_70, RwFrameGetLTM(var_10));
        for (var_74 = 0; var_74 < var_18->numNodes; var_74++)
        {
            var_C0 = var_70;
            var_C4 = RpHAnimIDGetIndex(var_18, var_18->pNodeInfo[var_74].nodeID);
            RwMatrixTransform(&var_C0, &var_1C[var_C4], rwCOMBINEPRECONCAT);
            RtQuatConvertFromMatrix(&var_20[var_74], &var_C0);
        }
        for (var_74 = 0; var_74 < var_4->unk_4D4->unk_02; var_74++)
        {
            var_28[var_74].unk_00.z = 0.0f;
            var_28[var_74].unk_00.y = 0.0f;
            var_28[var_74].unk_00.x = 0.0f;
        }
        var_C8 = (RtQuat *)(var_4->unk_4D4 + 1);
        memcpy(var_C8, var_20, var_18->numNodes * sizeof(RtQuat));
        var_8->unk_04 = var_4->unk_4D4;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else if (arg_C && var_4->unk_4D4)
    {
        var_D4 = var_4->get_unk_284()->unk_18;
        var_D8 = (RtQuat *)(var_4->unk_4D4 + 1);
        var_DC = var_8->unk_10;
        memcpy(var_DC, var_D8, var_D4->numNodes * sizeof(RtQuat));
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_4D4);
        var_8->unk_04 = var_4->unk_4D4;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else
    {
        var_EC = stru_3DC990;
        var_F8 = stru_3DC984;
        var_4->sub_17FC00(var_8, var_4->unk_4DC, 0, &var_EC, var_4->unk_3BC, 1);
        var_4->sub_17FC00(var_8, var_4->unk_4E0, 0, &var_F8, var_4->unk_3B8, 1);
        var_4->sub_17FC00(var_8, var_4->unk_4E4, 0, &var_F8, var_4->unk_3B8, 1);
    }
}

// match: ?sub_16B5C0@type_3DC9B0@@QAEMXZ @ 0x0016B5C0
// sp-match: ?sub_16B5C0@type_3DC9B0@@QAEMXZ @ 0x00107C30
// The shorter of its burst bounds (sub_16B620 the longer; sub_16B680 and
// sub_16B6E0 likewise its pause's). The picked bound goes through the FPU
// into the conditional's temporary (the double round trip), where a plain
// float operand is copied with integer moves.
RwReal type_3DC9B0::sub_16B5C0()
{
    type_4E1B70 *var_4 = sub_166990(unk_3B0);

    return var_4->unk_E8_r < var_4->unk_EC_r ? (RwReal)(RwDouble)var_4->unk_E8_r : (RwReal)(RwDouble)var_4->unk_EC_r;
}

// match: ?sub_16B620@type_3DC9B0@@QAEMXZ @ 0x0016B620
// sp-match: ?sub_16B620@type_3DC9B0@@QAEMXZ @ 0x00107C70
RwReal type_3DC9B0::sub_16B620()
{
    type_4E1B70 *var_4 = sub_166990(unk_3B0);

    return var_4->unk_E8_r > var_4->unk_EC_r ? (RwReal)(RwDouble)var_4->unk_E8_r : (RwReal)(RwDouble)var_4->unk_EC_r;
}

// match: ?sub_16B680@type_3DC9B0@@QAEMXZ @ 0x0016B680
// sp-match: ?sub_16B680@type_3DC9B0@@QAEMXZ @ 0x00107CB0
RwReal type_3DC9B0::sub_16B680()
{
    type_4E1B70 *var_4 = sub_166990(unk_3B0);

    return var_4->unk_F0_r < var_4->unk_F4_r ? (RwReal)(RwDouble)var_4->unk_F0_r : (RwReal)(RwDouble)var_4->unk_F4_r;
}

// match: ?sub_16B6E0@type_3DC9B0@@QAEMXZ @ 0x0016B6E0
// sp-match: ?sub_16B6E0@type_3DC9B0@@QAEMXZ @ 0x00107CF0
RwReal type_3DC9B0::sub_16B6E0()
{
    type_4E1B70 *var_4 = sub_166990(unk_3B0);

    return var_4->unk_F0_r > var_4->unk_F4_r ? (RwReal)(RwDouble)var_4->unk_F0_r : (RwReal)(RwDouble)var_4->unk_F4_r;
}

// match: ??0type_4E1B70@@QAE@XZ @ 0x0016B740
// The settings' implicit default constructor (its names' constructors),
// emitted after the unit's functions for the array dword_4E1B70.

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_3DC9B0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_3DC9B0::pDtor()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DC9B0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DC9B0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DC9B0@@SAXPAX@Z (folded into 0x19A750)
#ifndef CODFH_SP
// Single player keeps the deleting destructor's call (SP 0x109BE0), so the empty body is
// not in this file there.
void type_3DC9B0::operator delete(void * arg_0)
{
}
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DC9B0@@SAXPAX0@Z (folded into 0x19A750)
void type_3DC9B0::operator delete(void * arg_0, void * arg_4)
{
}
