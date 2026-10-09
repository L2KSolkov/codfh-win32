// The pad manager (type_4B9308, include/game/gameloop.h). The original file
// name is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/textmanager.h"
#include "game/particles.h"
#include "game/clones.h"
#include "types/type_F2FF0.h"
#include "types/type_F3130.h"
#include "game/frand.h"
#include "game/decals.h"
#include "game/functions.h"
#include "rw/bavector.h"
#include "rw/bamatrix.h"
#ifdef CODFH_SP
#include "game/levels.h"     // type_42B740 (sp_sub_12D360's records)
#include "game/xboxlive.h"   // dword_4F3130 (sub_EE6D0 calls its sp_sub_12C090)
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D9198
extern const RwReal flt_3D9198 = 16.666666f;
#ifndef CODFH_SP // MP only: single player has neither unreferenced 0.01f: its two 16.666666f follow the input event names (SP 0x2E5764, 0x2E5768)
// 0x003D919C
extern const RwReal flt_3D919C = 0.01f;
// 0x003D91A0
extern const RwReal flt_3D91A0 = 0.01f;
#endif
// 0x003D91A4
extern const RwReal flt_3D91A4 = 16.666666f;
// 0x00429498
// The input events (.data, PLAN M5): each one's number, its setting (sub_EECD0,
// sub_EED00) and its name; the -1 entry ends it.
#ifdef CODFH_SP // single player has no shoulder, action-release or popup events: 41 entries, renumbered (SP 0x3219D8, ePE_INVALID at 0x321BB8)
type_429498 dword_429498[41] = {
    { 0, 1, "ePE_FORWARD" },
    { 1, 1, "ePE_TURN" },
    { 2, 1, "ePE_STRAFE" },
    { 3, 1, "ePE_FIRE" },
    { 4, 0, "ePE_JUMP" },
    { 5, 1, "ePE_LOOKUP" },
    { 6, 1, "ePE_AIMMODE" },
    { 7, 0, "ePE_RELOAD" },
    { 8, 0, "ePE_POSTURE" },
    { 9, 0, "ePE_POSTUREUP" },
    { 10, 0, "ePE_POSTUREDOWN" },
    { 11, 0, "ePE_PAUSE" },
    { 12, 1, "ePE_ALTFIRE" },
    { 13, 0, "ePE_CYCLEWEAPON" },
    { 14, 0, "ePE_CYCLEEQUIPMENT" },
    { 15, 0, "ePE_ACTION" },
    { 16, 0, "ePE_USEEQUIPMENT" },
    { 17, 0, "ePE_QUIT" },
    { 18, 0, "ePE_RECENTER_VIEW" },
    { 19, 0, "ePE_UP" },
    { 20, 0, "ePE_DOWN" },
    { 21, 0, "ePE_LEFT" },
    { 22, 0, "ePE_RIGHT" },
    { 23, 0, "ePE_MENUSELECT" },
    { 24, 0, "ePE_MENUCANCEL" },
    { 25, 0, "ePE_MENUSAVE" },
    { 26, 0, "ePE_SCREENCAPTURE" },
    { 27, 0, "ePE_RUNSPEEDCHEAT" },
    { 28, 1, "ePE_LEAN" },
    { 29, 1, "ePE_LEANLEFT" },
    { 30, 1, "ePE_LEANRIGHT" },
    { 31, 1, "ePE_LEFT_REPEAT" },
    { 32, 1, "ePE_RIGHT_REPEAT" },
    { 33, 1, "ePE_UP_REPEAT" },
    { 34, 1, "ePE_DOWN_REPEAT" },
    { 35, 0, "ePE_OPTIONS" },
    { 36, 0, "ePE_HEALTH" },
    { 37, 0, "ePE_SHOWHUD" },
    { 38, 1, "ePE_FIRE_TANK_MG" },
    { 39, 0, "ePE_INSPECTOR_MENU_SELECT" },
    { -1, -1, "ePE_INVALID" },
};
#else
type_429498 dword_429498[45] = {
    { 0, 1, "ePE_FORWARD" },
    { 1, 1, "ePE_TURN" },
    { 2, 1, "ePE_STRAFE" },
    { 3, 1, "ePE_FIRE" },
    { 4, 0, "ePE_JUMP" },
    { 5, 1, "ePE_LOOKUP" },
    { 6, 1, "ePE_AIMMODE" },
    { 7, 0, "ePE_RELOAD" },
    { 8, 0, "ePE_POSTURE" },
    { 9, 0, "ePE_POSTUREUP" },
    { 10, 0, "ePE_POSTUREDOWN" },
    { 11, 0, "ePE_PAUSE" },
    { 12, 1, "ePE_ALTFIRE" },
    { 13, 0, "ePE_CYCLEWEAPON" },
    { 14, 0, "ePE_CYCLEEQUIPMENT" },
    { 15, 0, "ePE_ACTION" },
    { 16, 0, "ePE_USEEQUIPMENT" },
    { 17, 0, "ePE_QUIT" },
    { 18, 0, "ePE_RECENTER_VIEW" },
    { 19, 0, "ePE_UP" },
    { 20, 0, "ePE_DOWN" },
    { 21, 0, "ePE_LEFT" },
    { 22, 0, "ePE_RIGHT" },
    { 23, 0, "ePE_MENUSELECT" },
    { 24, 0, "ePE_MENUCANCEL" },
    { 25, 0, "ePE_MENUSAVE" },
    { 26, 0, "ePE_SCREENCAPTURE" },
    { 27, 0, "ePE_RUNSPEEDCHEAT" },
    { 28, 1, "ePE_LEAN" },
    { 29, 1, "ePE_LEANLEFT" },
    { 30, 1, "ePE_LEANRIGHT" },
    { 31, 1, "ePE_LEFT_REPEAT" },
    { 32, 1, "ePE_RIGHT_REPEAT" },
    { 33, 1, "ePE_UP_REPEAT" },
    { 34, 1, "ePE_DOWN_REPEAT" },
    { 35, 0, "ePE_SHOULDERLEFT" },
    { 36, 0, "ePE_SHOULDERRIGHT" },
    { 37, 2, "ePE_ACTION_RELEASE" },
    { 38, 1, "ePE_POPUP" },
    { 39, 0, "ePE_OPTIONS" },
    { 40, 0, "ePE_HEALTH" },
    { 41, 0, "ePE_SHOWHUD" },
    { 42, 1, "ePE_FIRE_TANK_MG" },
    { 43, 0, "ePE_INSPECTOR_MENU_SELECT" },
    { -1, -1, "ePE_INVALID" },
};
#endif
// 0x004296B4
type_4296B4 unk_4296B4 = { 20.1f, 0, 0 };
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4B9308 unk_4B9308;

// Its names (.rdata string literals, in reverse order there).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0M@DOCDCLNF@ePE_INVALID?$AA@ @ 0x003D8EF4
// match: ??_C@_0BK@DJBIBPCN@ePE_INSPECTOR_MENU_SELECT?$AA@ @ 0x003D8F00
// match: ??_C@_0BB@MJJMHLJI@ePE_FIRE_TANK_MG?$AA@ @ 0x003D8F1C
// match: ??_C@_0M@OBKPMPDO@ePE_SHOWHUD?$AA@ @ 0x003D8F30
// match: ??_C@_0L@NLNJCANP@ePE_HEALTH?$AA@ @ 0x003D8F3C
// match: ??_C@_0M@KAGMBCPG@ePE_OPTIONS?$AA@ @ 0x003D8F48
// match: ??_C@_09CAOFDFNO@ePE_POPUP?$AA@ @ 0x003D8F54
// match: ??_C@_0BD@GAGIHKFG@ePE_ACTION_RELEASE?$AA@ @ 0x003D8F60
// match: ??_C@_0BC@MIPJKKPC@ePE_SHOULDERRIGHT?$AA@ @ 0x003D8F74
// match: ??_C@_0BB@DAEOEGOO@ePE_SHOULDERLEFT?$AA@ @ 0x003D8F88
// match: ??_C@_0BA@FCOHMFJL@ePE_DOWN_REPEAT?$AA@ @ 0x003D8F9C
// match: ??_C@_0O@BNNGCPDN@ePE_UP_REPEAT?$AA@ @ 0x003D8FAC
// match: ??_C@_0BB@DENCAJGI@ePE_RIGHT_REPEAT?$AA@ @ 0x003D8FBC
// match: ??_C@_0BA@EHMGMJNI@ePE_LEFT_REPEAT?$AA@ @ 0x003D8FD0
// match: ??_C@_0O@DPIOGDFG@ePE_LEANRIGHT?$AA@ @ 0x003D8FE0
// match: ??_C@_0N@CFNALPHK@ePE_LEANLEFT?$AA@ @ 0x003D8FF0
// match: ??_C@_08JPKEKELL@ePE_LEAN?$AA@ @ 0x003D9000
// match: ??_C@_0BC@KLBINMFH@ePE_RUNSPEEDCHEAT?$AA@ @ 0x003D900C
// match: ??_C@_0BC@IHNDHLJC@ePE_SCREENCAPTURE?$AA@ @ 0x003D9020
// match: ??_C@_0N@IPNPDOOM@ePE_MENUSAVE?$AA@ @ 0x003D9034
// match: ??_C@_0P@LBCHOOH@ePE_MENUCANCEL?$AA@ @ 0x003D9044
// match: ??_C@_0P@COGAEIGI@ePE_MENUSELECT?$AA@ @ 0x003D9054
// match: ??_C@_09FPDBPLHE@ePE_RIGHT?$AA@ @ 0x003D9064
// match: ??_C@_08CKMGEIOF@ePE_LEFT?$AA@ @ 0x003D9070
// match: ??_C@_08NIMCNANM@ePE_DOWN?$AA@ @ 0x003D907C
// match: ??_C@_06GECCDCPG@ePE_UP?$AA@ @ 0x003D9088
// match: ??_C@_0BC@IMBHJENC@ePE_RECENTER_VIEW?$AA@ @ 0x003D9090
// match: ??_C@_08OJPDALHE@ePE_QUIT?$AA@ @ 0x003D90A4
// match: ??_C@_0BB@HMKFCOEJ@ePE_USEEQUIPMENT?$AA@ @ 0x003D90B0
// match: ??_C@_0L@EBOPIFMG@ePE_ACTION?$AA@ @ 0x003D90C4
// match: ??_C@_0BD@LOHFOMGL@ePE_CYCLEEQUIPMENT?$AA@ @ 0x003D90D0
// match: ??_C@_0BA@FPDIOHIC@ePE_CYCLEWEAPON?$AA@ @ 0x003D90E4
// match: ??_C@_0M@LLAHNBLA@ePE_ALTFIRE?$AA@ @ 0x003D90F4
// match: ??_C@_09JLDDOBCL@ePE_PAUSE?$AA@ @ 0x003D9100
// match: ??_C@_0BA@KOGHJDHK@ePE_POSTUREDOWN?$AA@ @ 0x003D910C
// match: ??_C@_0O@LKKMNGPP@ePE_POSTUREUP?$AA@ @ 0x003D911C
// match: ??_C@_0M@CHBEOGOF@ePE_POSTURE?$AA@ @ 0x003D912C
// match: ??_C@_0L@EEAKKGJH@ePE_RELOAD?$AA@ @ 0x003D9138
// match: ??_C@_0M@IHPGBMEL@ePE_AIMMODE?$AA@ @ 0x003D9144
// match: ??_C@_0L@CPDDFDBM@ePE_LOOKUP?$AA@ @ 0x003D9150
// match: ??_C@_08JNKGMADP@ePE_JUMP?$AA@ @ 0x003D915C
// match: ??_C@_08GCFGMHEA@ePE_FIRE?$AA@ @ 0x003D9168
// match: ??_C@_0L@JKMAFAJ@ePE_STRAFE?$AA@ @ 0x003D9174
// match: ??_C@_08IBENDCEO@ePE_TURN?$AA@ @ 0x003D9180
// match: ??_C@_0M@NHFMIGLF@ePE_FORWARD?$AA@ @ 0x003D918C
// match: ?flt_3D9198@@3MB @ 0x003D9198
// match: ?flt_3D919C@@3MB @ 0x003D919C
// match: ?flt_3D91A0@@3MB @ 0x003D91A0
// match: ?flt_3D91A4@@3MB @ 0x003D91A4
// match: __real@40490fd0 @ 0x003D91A8
// match: __real@42855555 @ 0x003D91AC
// match: .CRT$XCU+0 @ 0x00427054
// match: ?dword_429498@@3PAUtype_429498@@A @ 0x00429498
// match: ?unk_4296B4@@3Utype_4296B4@@A @ 0x004296B4

// match: _$E1 @ 0x0030B540
// match: _$E2 @ 0x0030E4C0
// match: ??0type_4B9308@@QAE@XZ @ 0x000EE540
// sp-match: ??0type_4B9308@@QAE@XZ @ 0x000B6700

type_4B9308::type_4B9308()
{
    unk_B40 = 0;
    unk_B4C = 1;
    unk_B48 = -1;
    unk_B54 = 0;
    unk_B44 = 1;
}

// match: ?sub_EE590@type_4B9308@@QAEXXZ @ 0x000EE590
// sp-match: ?sub_EE590@type_4B9308@@QAEXXZ @ 0x000B6730
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4B9308::sub_EE590()
{
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (unk_B40)
    {
        return;
    }
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        for (bp_8 = 0; bp_8 < type_4B9308_btn_count; bp_8++)
        {
            unk_00[bp_4].unk_00[bp_8].unk_00 = dword_429498[bp_8].unk_00;
            unk_00[bp_4].unk_00[bp_8].unk_04 = 0;
            unk_00[bp_4].unk_00[bp_8].unk_08 = 0;
        }
        unk_00[bp_4].unk_2C0.unk_00 = 0;
        unk_00[bp_4].unk_2C0.unk_04 = 0;
        unk_00[bp_4].unk_2C0.unk_08 = 0;
        unk_00[bp_4].unk_2C0.unk_0C = 0;
    }
    sub_19DF40();
    unk_B40 = 1;
    unk_B5C = 0;
    unk_B60 = 255.0f;
}

// match: ?sub_EE6D0@type_4B9308@@QAEXXZ @ 0x000EE6D0
// sp-match: ?sub_EE6D0@type_4B9308@@QAEXXZ @ 0x000B67C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4B9308::sub_EE6D0()
{
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (!unk_B40)
    {
        return;
    }
    for (bp_8 = 0; bp_8 < 4; bp_8++)
    {
        for (slot_C = 0; slot_C < type_4B9308_btn_count; slot_C++)
        {
            unk_00[bp_8].unk_00[slot_C].unk_04 = 0;
        }
    }
    bp_4 = sub_19DFE0(this, deltaTime);
    if (!bp_4)
    {
        dword_42926C = 0;
    }
    else
    {
        dword_42926C = 1;
    }
#ifdef CODFH_SP
    // single player then lets the live state follow the pads (SP 0xB6826).
    dword_4F3130.sp_sub_12C090();
#endif
}

// match: ?sub_EE770@type_4B9308@@QAEXXZ @ 0x000EE770
// sp-match: ?sub_EE770@type_4B9308@@QAEXXZ @ 0x000B6830
void type_4B9308::sub_EE770()
{
    sub_19E0D0(this, deltaTime);
}

// match: ?sub_EE790@type_4B9308@@QAEHHH@Z @ 0x000EE790
// sp-match: ?sub_EE790@type_4B9308@@QAEHHH@Z @ 0x000B6CC0
RwInt32 type_4B9308::sub_EE790(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    if (unk_B44)
    {
        arg_4 = sub_EEC50(arg_4);
        if (arg_4 == -1)
        {
            arg_4 = 0;
        }
    }
    var_4 = sub_19E200(arg_0, arg_4, this);
    return var_4;
}

// match: ?sub_EE7F0@type_4B9308@@QAEHHH@Z @ 0x000EE7F0
// sp-match: ?sub_EE7F0@type_4B9308@@QAEHHH@Z @ 0x000B6CF0
RwInt32 type_4B9308::sub_EE7F0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (unk_B44)
    {
        arg_4 = sub_EEC50(arg_4);
        if (arg_4 == -1)
        {
            arg_4 = 0;
        }
    }
    return sub_19E430(arg_0, arg_4, this);
}

// match: ?sub_EE840@type_4B9308@@QAEXXZ @ 0x000EE840
void type_4B9308::sub_EE840()
{
    if (!unk_B40)
    {
        return;
    }
    sub_19E120();
    unk_B40 = 0;
}

// match: ?sub_EE870@type_4B9308@@QAEHHH@Z @ 0x000EE870
// sp-match: ?sub_EE870@type_4B9308@@QAEHHH@Z @ 0x000B6840
RwInt32 type_4B9308::sub_EE870(RwInt32 arg_0, RwInt32 arg_4)
{
    if (get_unk_B44() && arg_0 == 0 && has_unk_B48())
    {
        arg_0 = unk_B48;
    }
    if (unk_00[arg_0].unk_00[arg_4].unk_08 & 1)
    {
        return 0;
    }
    return unk_00[arg_0].unk_00[arg_4].unk_0C;
}

// match: ?sub_EE8F0@type_4B9308@@QAEMHH@Z @ 0x000EE8F0
RwReal type_4B9308::sub_EE8F0(RwInt32 arg_0, RwInt32 arg_4)
{
#ifdef CODFH_SP // single player has no input-ignore test: every call reaches sub_EE9A0's body (SP 0x11E23F -> 0xB6D20; config/sp/handaliases.txt folds this name there)
    return sub_EE9A0(arg_0, arg_4);
#else
    if (dword_4FDA9C
        || sub_1FF250() && (sub_1FF250()->sub_1EF160() || sub_1FF250()->sub_200780()))
    {
        return 0.0f;
    }
    return sub_EE9A0(arg_0, arg_4);
#endif
}

#ifndef CODFH_SP // MP only: no caller or twin of sub_EE950 in single player (config/sp/shared.txt)
// match: ?sub_EE950@type_4B9308@@QAEMHH@Z @ 0x000EE950
RwReal type_4B9308::sub_EE950(RwInt32 arg_0, RwInt32 arg_4)
{
    if (sub_1FF250() && sub_1FF250()->sub_1EF160())
    {
        return 0.0f;
    }
    return sub_EE9A0(arg_0, arg_4);
}
#endif

// match: ?sub_EE9A0@type_4B9308@@QAEMHH@Z @ 0x000EE9A0
// sp-match: ?sub_EE9A0@type_4B9308@@QAEMHH@Z @ 0x000B6D20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal type_4B9308::sub_EE9A0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 lv_10;
    RwReal slot_C;
    RwInt32 bp_8;
    RwReal bp_4;

#ifndef CODFH_SP // single player reads the pad state without this test (SP 0xB6D20)
    if (!dword_42926C)
    {
        return 0.0f;
    }
#endif
    if (get_unk_B44())
    {
        if (arg_0 == 0)
        {
            if (has_unk_B48())
            {
                arg_0 = unk_B48;
                unk_B50 = arg_0;
            }
            else
            {
                for (bp_8 = 0; bp_8 < 4; bp_8++)
                {
                    slot_C = sub_EEAC0(bp_8, arg_4);
                    if (slot_C != 0.0f)
                    {
                        unk_B50 = bp_8;
                        return slot_C;
                    }
                }
            }
        }
        else if (arg_0 == 1)
        {
            lv_10 = get_unk_B48() + 1;
            if (lv_10 >= 4)
            {
                lv_10 = 0;
            }
            arg_0 = lv_10;
        }
    }
    return bp_4 = sub_EEAC0(arg_0, arg_4);
}

// match: ?sub_EEAA0@type_4B9308@@QAEXH@Z @ 0x000EEAA0
// sp-match: ?sub_EEAA0@type_4B9308@@QAEXH@Z @ 0x000B6880
void type_4B9308::sub_EEAA0(RwInt32 arg_0)
{
    unk_B48 = arg_0;
}

#ifdef CODFH_SP
// Single player only: clears the value of button arg_4 on pad arg_0 (the
// player's pad for 0 when one pad counts); sp_sub_12C090 calls it (SP 0x12C1CA).
// sp-match: ?sp_sub_B6890@type_4B9308@@QAEXHH@Z @ 0x000B6890
void type_4B9308::sp_sub_B6890(RwInt32 arg_0, RwInt32 arg_4)
{
    if (get_unk_B44() && arg_0 == 0 && has_unk_B48())
    {
        arg_0 = unk_B48;
    }
    unk_00[arg_0].unk_00[arg_4].unk_04 = 0;
}
#endif

// match: ?sub_EEAC0@type_4B9308@@QAEMHH@Z @ 0x000EEAC0
// sp-match: ?sub_EEAC0@type_4B9308@@QAEMHH@Z @ 0x000B68D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal type_4B9308::sub_EEAC0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwReal bp_8;
    RwReal bp_4;

    bp_4 = 0;
    if (unk_00[arg_0].unk_00[arg_4].unk_08 & 1)
    {
        return 0.0f;
    }
    bp_4 = unk_00[arg_0].unk_00[arg_4].unk_04;
    switch (arg_4)
    {
    case 0:
    case 1:
    case 2:
    case 5:
        bp_8 = bp_4 < 0.0f ? -bp_4 : bp_4;
        if (bp_8 > unk_B5C)
        {
            bp_4 < 0.0f ? (bp_4 = bp_4 + unk_B5C) : (bp_4 = bp_4 - unk_B5C);
#ifdef CODFH_SP // shape: SP 0xB692F scales before dividing (fmul 255, fdiv)
            return bp_4 = (RwReal)(bp_4 * 255.0f) / unk_B60;
#else
            return bp_4 = 255.0f * bp_4 / unk_B60;
#endif
        }
        return 0.0f;
    case 16:
    case 31:
    case 32:
    case 33:
    case 34:
        return bp_4;
    default:
        if (bp_4 > 0.0f && bp_4 < 1.0f)
        {
            return 1.0f;
        }
        if (bp_4 < 0.0f && bp_4 > -1.0f)
        {
            return -1.0f;
        }
        return bp_4;
    }
}

// match: ?sub_EEC50@type_4B9308@@QAEHH@Z @ 0x000EEC50
// sp-match: ?sub_EEC50@type_4B9308@@QAEHH@Z @ 0x000B69E0
RwInt32 type_4B9308::sub_EEC50(RwInt32 arg_0)
{
    RwInt32 var_4;

    if (arg_0 == 0)
    {
        arg_0 = unk_B48;
    }
    else if (arg_0 == 1)
    {
        var_4 = unk_B48 + 1;
        if (var_4 >= 4)
        {
            var_4 = 0;
        }
        arg_0 = var_4;
    }
    return arg_0;
}

#ifdef CODFH_SP
// Single player only: makes arg_0 the pad that counts (sub_EEAA0), clears
// unk_B54, sets unk_B4C and reads the pads (sub_EE6D0); sp_sub_A59D0 calls it
// (SP 0xA5C69).
// sp-match: ?sp_sub_B6A10@type_4B9308@@QAEXH@Z @ 0x000B6A10
void type_4B9308::sp_sub_B6A10(RwInt32 arg_0)
{
    sub_EEAA0(arg_0);
    unk_B54 = 0;
    unk_B4C = 1;
    sub_EE6D0();
}
#endif

// match: ?sub_EECA0@type_4B9308@@QAEXHHC@Z @ 0x000EECA0
// sp-match: ?sub_EECA0@type_4B9308@@QAEXHHC@Z @ 0x000B6A40
void type_4B9308::sub_EECA0(RwInt32 arg_0, RwInt32 arg_4, RwInt8 arg_8)
{
    unk_00[arg_0].unk_00[arg_4].unk_08 = arg_8;
}

// match: ?sub_EECD0@type_4B9308@@QAEXHH@Z @ 0x000EECD0
// sp-match: ?sub_EECD0@type_4B9308@@QAEXHH@Z @ 0x000B6A60
void type_4B9308::sub_EECD0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0 < type_4B9308_btn_count && arg_4 < 3)
    {
        dword_429498[arg_0].unk_04 = arg_4;
    }
}

// match: ?sub_EED00@type_4B9308@@QAEHH@Z @ 0x000EED00
// sp-match: ?sub_EED00@type_4B9308@@QAEHH@Z @ 0x000B6A80
RwInt32 type_4B9308::sub_EED00(RwInt32 arg_0)
{
    if (arg_0 < type_4B9308_btn_count)
    {
        return dword_429498[arg_0].unk_04;
    }
    return -1;
}

// match: ?sub_EED30@type_4B9308@@QAEXHHFF@Z @ 0x000EED30
// sp-match: ?sub_EED30@type_4B9308@@QAEXHHFF@Z @ 0x000B6AA0
void type_4B9308::sub_EED30(RwInt32 arg_0, RwInt32 arg_4, RwInt16 arg_8, RwInt16 arg_C)
{
    type_EEF90 *var_4;

#ifdef CODFH_SP // single player has no rumble-off flag test here (SP 0xB6AA0)
    if (dword_4F28F0->get_unk_20())
#else
    if (dword_4F28F0->get_unk_20() && !(dword_4B86F8 >> 4 & 1))
#endif
    {
        if (get_unk_B44() && arg_0 == 0 && has_unk_B48())
        {
            arg_0 = unk_B48;
        }
        var_4 = &unk_00[arg_0].unk_2C0;
        var_4->unk_0C = 1;
        var_4->unk_00 = arg_4;
        var_4->unk_04 = arg_8 < 255 ? arg_8 : 255;
        var_4->unk_08 = (RwReal)(arg_C < 255 ? arg_C : 255);
    }
}

// match: ?sub_EEE20@type_4B9308@@QAEXHHEF@Z @ 0x000EEE20
// sp-match: ?sub_EEE20@type_4B9308@@QAEXHHEF@Z @ 0x000B6B30
void type_4B9308::sub_EEE20(RwInt32 arg_0, RwInt32 arg_4, RwUInt8 arg_8, RwInt16 arg_C)
{
    type_EEF90 *var_4;

#ifdef CODFH_SP // single player has no rumble-off flag test here (SP 0xB6B30)
    if (dword_4F28F0->get_unk_20())
#else
    if (dword_4F28F0->get_unk_20() && !(dword_4B86F8 >> 4 & 1))
#endif
    {
        if (get_unk_B44() && arg_0 == 0 && has_unk_B48())
        {
            arg_0 = unk_B48;
        }
        var_4 = &unk_00[arg_0].unk_2C0;
        var_4->unk_0C = 1;
        if (!var_4->unk_00)
        {
            var_4->unk_00 = arg_4;
        }
        var_4->unk_04 += arg_8;
        var_4->unk_04 = var_4->unk_04 < 255 ? var_4->unk_04 : 255;
        var_4->unk_08 += arg_C;
#ifdef CODFH_SP // shape: SP 0xB6BB1 compares the limit with the sum
        var_4->unk_08 = 255.0f > var_4->unk_08 ? (RwReal)(var_4->unk_08) : 255.0f;
#else
        var_4->unk_08 = var_4->unk_08 < 255.0f ? (RwReal)(var_4->unk_08) : 255.0f;
#endif
    }
}

// match: ?sub_EEF50@type_4B9308@@QAEXH@Z @ 0x000EEF50
void type_4B9308::sub_EEF50(RwInt32 arg_0)
{
    RwInt32 var_4 = 0;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        sub_EEF90(var_4, arg_0);
    }
}

// match: ?sub_EEF90@type_4B9308@@QAEXHH@Z @ 0x000EEF90
// sp-match: ?sub_EEF90@type_4B9308@@QAEXHH@Z @ 0x000B6BD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4B9308::sub_EEF90(RwInt32 arg_0, RwInt32 arg_4)
{
    type_EEF90 *ebp_14 = &unk_00[arg_0].unk_2C0;
    type_EEF90 lv_10;

    if (!arg_4)
    {
        lv_10 = *ebp_14;
    }
    ebp_14->unk_0C = 1;
    ebp_14->unk_00 = 0;
    ebp_14->unk_04 = 0;
    ebp_14->unk_08 = 0;
    sub_19E0D0(this, deltaTime);
    if (!arg_4)
    {
        *ebp_14 = lv_10;
        ebp_14->unk_0C = 1;
    }
}

#ifdef CODFH_SP
// Single player only: the binding table of set arg_0 (0x20-byte records, an id
// first, -1 ending it; sub_19B1E0, SP 0x1295B0) and its record update (sp_sub_12D360),
// both in single player's own code (the records are game/levels.h's type_42B740).
type_42B740 *sub_19B1E0(RwInt32 arg_0);
RwInt32 sp_sub_12D360(type_42B740 *arg_0, RwInt32 arg_4, RwInt32 arg_8);

// Single player only: in set arg_0, binds the first record with the id arg_4
// to arg_8 (0x28: to -1, with the flag); sp_sub_B6DC0 calls it.
// sp-match: ?sp_sub_B6C60@type_4B9308@@QAEXHHH@Z @ 0x000B6C60
void type_4B9308::sp_sub_B6C60(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_42B740 *p = sub_19B1E0(arg_0);
    RwInt32 done = 0;

    for (; p->unk_00 != -1; p++)
    {
        if (done)
            break;
        if (p->unk_00 == arg_4)
        {
            if (arg_8 == 0x28)
                sp_sub_12D360(p, -1, 1);
            else
                sp_sub_12D360(p, arg_8, 0);
            done = 1;
        }
    }
}
#endif

#ifdef CODFH_SP
// Single player only: the default bindings of buttons 8, 9, 10 and 0 to 3
// (0x17 to 0x19, 0x13 to 0x16) in the five sets; sp_sub_A59D0 calls it
// (SP 0xA5ADF).
// sp-match: ?sp_sub_B6DC0@type_4B9308@@QAEXXZ @ 0x000B6DC0
void type_4B9308::sp_sub_B6DC0()
{
    RwInt32 i;

    for (i = 0; i < 5; i++)
    {
        sp_sub_B6C60(i, 8, 0x17);
        sp_sub_B6C60(i, 9, 0x18);
        sp_sub_B6C60(i, 10, 0x19);
        sp_sub_B6C60(i, 0, 0x13);
        sp_sub_B6C60(i, 1, 0x14);
        sp_sub_B6C60(i, 2, 0x15);
        sp_sub_B6C60(i, 3, 0x16);
    }
}
#endif

// Updates the mesh particle system arg_0 by arg_4 frames; 0 once its
// duration and its particles' life have run out. While it emits (flag 1)
// its rate (unk_18, a second) gives the new particles due. Each new one
// starts at the system's matrix scaled by unk_CC and offset by up to half of
// unk_0C..unk_14 (turned with it), with a velocity of unk_40..unk_48 give or
// take half of unk_4C..unk_54 (times unk_2C x 10) and, with unk_A4, a random
// spin axis and rate. The live ones age, fall by unk_34..unk_3C and move and
// spin, and die at the age unk_24; with unk_F0 they start the system unk_D0
// at their places (one a particle, following it, when the trails' rate unk_F4
// is 0).
// match: ?sub_EF040@@YAHPAUtype_F2FF0@@M@Z @ 0x000EF040
// sp-match: ?sub_EF040@@YAHPAUtype_F2FF0@@M@Z @ 0x000B6E30
RwInt32 sub_EF040(type_F2FF0 *arg_0, RwReal arg_4)
{
    RwInt32 v_4;
    RwInt32 v_8;
    RwInt32 v_C;
    RwReal v_10;
    RwReal v_14;
    RwInt32 v_18;
    type_F2FF0_60_04 *v_1C;
    RwMatrix *v_20;

    v_4 = 1;
    arg_0->unk_60.unk_08 += arg_4;
    v_8 = 0;
    v_C = 0;
    if (arg_0->unk_60.unk_14 & 1)
    {
        v_8 = (RwInt32)(v_10 = arg_0->unk_44->unk_18 * (arg_0->unk_60.unk_08 - arg_0->unk_60.unk_0C) * 66.666664f);
        if (v_8 > 0)
        {
            arg_0->unk_60.unk_0C = arg_0->unk_60.unk_08;
        }
    }
    v_C = (RwInt32)(v_14 = arg_0->unk_44->unk_F4_f * (arg_0->unk_60.unk_08 - arg_0->unk_60.unk_10) * 66.666664f);
    if (v_C > 0)
    {
        arg_0->unk_60.unk_10 = arg_0->unk_60.unk_08;
    }
    for (v_18 = 0; v_18 < arg_0->unk_60.unk_1C; v_18++)
    {
        v_1C = &arg_0->unk_60.unk_04[v_18];
        v_20 = &arg_0->unk_00;
        if (v_1C->unk_00 < 0.0f && v_8 > 0)
        {
            v_1C->unk_10.z = 0;
            v_1C->unk_10.y = 0;
            v_1C->unk_10.x = 0;
            v_1C->unk_00 = 0;
            v_1C->unk_20 = 0;
            arg_0->unk_60.unk_00[v_18] = *v_20;
            v_1C->unk_04.x = arg_0->unk_44->unk_40 + frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_4C;
            v_1C->unk_04.y = arg_0->unk_44->unk_44 + frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_50;
            v_1C->unk_04.z = arg_0->unk_44->unk_48 + frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_54;
            RwV3dScale(&v_1C->unk_04, &v_1C->unk_04, arg_0->unk_44->unk_2C * 10.0f);
            sub_141320(&v_1C->unk_04, &v_1C->unk_04, &arg_0->unk_60.unk_00[v_18]);
            if (arg_0->unk_44->unk_A4)
            {
                v_1C->unk_10.x = frand_range(-1.0f, 1.0f);
                v_1C->unk_10.y = frand_range(-1.0f, 1.0f);
                v_1C->unk_10.z = frand_range(-1.0f, 1.0f);
                RwV3dNormalize(&v_1C->unk_10, &v_1C->unk_10);
                v_1C->unk_1C = frand_range(0.0f, arg_0->unk_44->unk_A4 * 3.14159f);
            }
            RwV3d v_A8;

            v_A8.x = frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_0C;
            v_A8.y = frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_10;
            v_A8.z = frand_range(-0.5f, 0.5f) * arg_0->unk_44->unk_14;
            sub_141320(&v_A8, &v_A8, &arg_0->unk_60.unk_00[v_18]);
            RwV3dAdd(&arg_0->unk_60.unk_00[v_18].pos, &arg_0->unk_60.unk_00[v_18].pos, &v_A8);
            RwV3dScale(&arg_0->unk_60.unk_00[v_18].right, &arg_0->unk_60.unk_00[v_18].right, arg_0->unk_44->unk_CC);
            RwV3dScale(&arg_0->unk_60.unk_00[v_18].up, &arg_0->unk_60.unk_00[v_18].up, arg_0->unk_44->unk_CC);
            RwV3dScale(&arg_0->unk_60.unk_00[v_18].at, &arg_0->unk_60.unk_00[v_18].at, arg_0->unk_44->unk_CC);
            arg_0->unk_60.unk_18++;
            v_8--;
        }
        else if (v_1C->unk_00 >= 0.0f)
        {
            RwV3d *v_C8;

            v_1C->unk_00 += arg_4;
            v_1C->unk_04.x += arg_4 * arg_0->unk_44->unk_34 * 20.0f;
            v_1C->unk_04.y += arg_4 * arg_0->unk_44->unk_38 * 20.0f;
            v_1C->unk_04.z += arg_4 * arg_0->unk_44->unk_3C * 20.0f;
            v_C8 = &arg_0->unk_60.unk_00[v_18].pos;
            v_C8->x += arg_4 * v_1C->unk_04.x;
            v_C8->y += arg_4 * v_1C->unk_04.y;
            v_C8->z += arg_4 * v_1C->unk_04.z;
            if (arg_0->unk_44->unk_A4)
            {
                sub_140440(&arg_0->unk_60.unk_00[v_18], &v_1C->unk_10, arg_4 * v_1C->unk_1C);
            }
            if (v_1C->unk_00 >= arg_0->unk_44->unk_24)
            {
                v_1C->unk_00 = -1.0f;
                arg_0->unk_60.unk_18--;
                arg_0->unk_60.unk_00[v_18].pos.z = 10000000.0f;
            }
            if (arg_0->unk_44->unk_F0)
            {
                if (v_C || arg_0->unk_44->unk_F4_f == 0.0f)
                {
                    if (v_1C->unk_00 >= 0.0f)
                    {
                        RwMatrix v_110;

                        arg_0->unk_60.unk_14 |= 4;
                        RwMatrixSetIdentity(&v_110);
                        v_110.pos = arg_0->unk_60.unk_00[v_18].pos;
                        if (arg_0->unk_44->unk_F4_f != 0.0f)
                        {
                            sub_F3070(arg_0->unk_44->unk_D0, &v_110, 0, 1, false, false);
                        }
                        else if (!v_1C->unk_20)
                        {
                            type_F2FF0 *v_114;

                            v_114 = sub_F3070(arg_0->unk_44->unk_D0, &v_110, 0, 1, false, false);
                            if (v_114)
                            {
                                RwV3d v_120;

                                sub_19E9B0((type_19E9B0 *)&v_114->unk_60, &v_1C->unk_04);
                                v_120.x = unk_4296B4.unk_00 * arg_0->unk_44->unk_34;
                                v_120.y = unk_4296B4.unk_00 * arg_0->unk_44->unk_38;
                                v_120.z = unk_4296B4.unk_00 * arg_0->unk_44->unk_3C;
                                sub_19E9E0((type_19E9B0 *)&v_114->unk_60, &v_120);
                                v_1C->unk_20 = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    if (arg_0->unk_44->unk_20 > 0.0f)
    {
        RwReal v_124;
        RwReal v_128;

        v_124 = arg_0->unk_44->unk_20;
        v_128 = arg_0->unk_44->unk_24;
        if (arg_0->unk_60.unk_08 > v_124)
        {
            arg_0->unk_60.unk_14 &= ~1;
        }
#ifdef CODFH_SP // shape: SP 0xB74CB compares the time with the sum
        if (arg_0->unk_60.unk_08 > v_124 + v_128)
#else
        if (v_124 + v_128 < arg_0->unk_60.unk_08)
#endif
        {
            v_4 = 0;
        }
    }
    return v_4;
}

// Draws a mesh particle system (type_F2FF0::sub_F43B0 with flag 0x10): its
// mesh lit as a clone, then once per particle at its matrices.
// match: ?sub_EFB70@@YAXPAUtype_F2FF0@@@Z @ 0x000EFB70
// sp-match: ?sub_EFB70@@YAXPAUtype_F2FF0@@@Z @ 0x000B7510
void sub_EFB70(type_F2FF0 *arg_0)
{
    if (arg_0->unk_60.unk_20)
    {
        sub_123AF0(arg_0->unk_60.unk_20, 1, 0, 0, 0, 0);
        sub_123FE0((type_1243F0 *)arg_0->unk_60.unk_00, arg_0->unk_60.unk_1C, 0);
        sub_124D70();
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_4B9308@@QAE@XZ (folded into 0x1E41C0)
type_4B9308::~type_4B9308()
{
}


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004B9E48: unk_4B9308 + 0xB40
RwInt32 &dword_4B9E48 = *(RwInt32 *)((RwUInt8 *)&unk_4B9308 + 0xB40);
// 0x004B9E50: unk_4B9308 + 0xB48
RwInt32 &dword_4B9E50 = *(RwInt32 *)((RwUInt8 *)&unk_4B9308 + 0xB48);
// 0x004B9E54: unk_4B9308 + 0xB4C
RwInt32 &dword_4B9E54 = *(RwInt32 *)((RwUInt8 *)&unk_4B9308 + 0xB4C);
// 0x004B9E5C: unk_4B9308 + 0xB54
RwInt32 &dword_4B9E5C = *(RwInt32 *)((RwUInt8 *)&unk_4B9308 + 0xB54);
#endif
