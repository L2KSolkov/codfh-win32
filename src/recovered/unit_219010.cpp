/*
 * The in-game Live options (game/ingamepages.h): the friends and players
 * lists, appearing offline and signing out, with their status texts.
 */
#include <stdio.h>
#include "game/liveservice.h"
#include "game/ingamepages.h"
#include "game/livemenu.h"
#include "game/startup.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E9D90
extern const RwReal flt_3E9D90 = 0.01f;
// 0x003E9D94
extern const RwReal flt_3E9D94 = 0.01f;
// 0x003E9D98
extern const RwReal flt_3E9D98 = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9D90@@3MB @ 0x003E9D90
// match: ?flt_3E9D94@@3MB @ 0x003E9D94
// match: ?flt_3E9D98@@3MB @ 0x003E9D98
// match: ??_C@_0O@MLBGJAOJ@SignOutStatus?$AA@ @ 0x003E9D9C
// match: ??_C@_0M@CIDJAKCL@PlayersList?$AA@ @ 0x003E9DAC
// match: ??_7type_219010@@6B@ @ 0x003E9DB8
// match: ??_C@_07EIKOHEBD@Sign?5In?$AA@ @ 0x003E9E08
// match: ??_C@_08PKLNEABF@Sign?5Out?$AA@ @ 0x003E9E10
// match: ??_C@_0L@DEIKHOBP@QUIT_GAME?$DP?$AA@ @ 0x003E9E1C
// match: ??_C@_0P@KFOANKOH@QUIT_GAME_HOST?$AA@ @ 0x003E9E28
// match: ??_C@_09FCMBMOFE@QUIT_GAME?$AA@ @ 0x003E9E38
// match: ??_7?$type_3E7264@Utype_219010@@@kujuUI@@6B@ @ 0x003E9E44
// match: ??_7?$type_3E7CE8@Utype_219010@@@kujuUI@@6B@ @ 0x003E9E54
// match: __ehhandler$??0type_219010@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00424990
// match: __ehhandler$??0type_219010@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x004249E0
// match: __ehhandler$??1type_219010@@UAE@XZ>1>8 @ 0x004249FC
// match: __ehhandler$??1type_219010@@UAE@XZ>1 @ 0x00424A44
// match: __ehhandler$?sub_219320@type_219010@@QAEXXZ>1>8 @ 0x00424A60
// match: __ehhandler$?sub_219320@type_219010@@QAEXXZ>1 @ 0x00424A80
// match: __ehhandler$?sub_219560@type_219010@@QAEXXZ>1>8 @ 0x00424A9C
// match: __ehhandler$?sub_219560@type_219010@@QAEXXZ>1 @ 0x00424ACC
// match: __ehhandler$?vf_014@type_219010@@UAEXM@Z>1>8 @ 0x00424AE8
// match: __ehhandler$?vf_014@type_219010@@UAEXM@Z>1 @ 0x00424AF0

// match: ??0type_219010@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00219010
// match: __ehhandler$??0type_219010@@QAE@PBDPAUtype_21A5E0@@@Z-0x86 @ 0x00307710
// match: __ehhandler$??0type_219010@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00307796

type_219010::type_219010(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_219010::sub_2194E0, &type_219010::sub_219AD0),
      unk_164(this, &type_219010::sub_219500, &type_219010::sub_219A80),
      unk_174(this, &type_219010::sub_219520, &type_219010::sub_219AD0),
      unk_184(this, &type_219010::sub_219560), unk_190(this, &type_219010::sub_219AA0),
      unk_19C(this, &type_219010::sub_1E41C0), unk_220(false)
{
    sub_204FC0("FriendsList", &unk_154);
    sub_204FC0("PlayersList", &unk_164);
    sub_204FC0("AppearOffline", &unk_174);
    sub_204FC0("SignOut", &unk_184);
    sub_204FC0("FriendsFlagText", &unk_1A8);
    sub_204FC0("AppearStatus", &unk_1D0);
    sub_204FC0("SignOutStatus", &unk_1F8);
    sub_219320();
}

// match: ??_Gtype_219010@@UAEPAXI@Z @ 0x00219200
// match: ??1type_219010@@UAE@XZ @ 0x00219230
// match: __ehhandler$??1type_219010@@UAE@XZ-0x78 @ 0x003077A0
// match: __ehhandler$??1type_219010@@UAE@XZ @ 0x00307818
type_219010::~type_219010()
{
}

// The texts: "Appear Offline" or "Appear Online" as the service appears,
// and "Sign Out" or "Sign In".
// match: ?sub_219320@type_219010@@QAEXXZ @ 0x00219320
// match: __ehhandler$?sub_219320@type_219010@@QAEXXZ-0x20 @ 0x00307830
// match: __ehhandler$?sub_219320@type_219010@@QAEXXZ @ 0x00307850
void type_219010::sub_219320()
{
    if (sub_227560()->get_unk_A0_direct())
        unk_1D0.sub_1F28C0(type_1CB670("Appear Offline", 0));
    else
        unk_1D0.sub_1F28C0(type_1CB670("Appear Online", 0));
    if (sub_227560()->sub_228100())
        unk_1F8.sub_1F28C0(type_1CB670("Sign Out", 0));
    else
        unk_1F8.sub_1F28C0(type_1CB670("Sign In", 0));
}

// match: ?sub_2194E0@type_219010@@QAEXXZ @ 0x002194E0
void type_219010::sub_2194E0()
{
    unk_130->sub_21C200(0x16, 0x15);
}

// match: ?sub_219500@type_219010@@QAEXXZ @ 0x00219500
void type_219010::sub_219500()
{
    unk_130->sub_21C200(0x17, 0x15);
}

// match: ?sub_219520@type_219010@@QAEXXZ @ 0x00219520
void type_219010::sub_219520()
{
    type_5051E8 *var_4 = sub_227560();

    sub_227560()->sub_227B80(var_4->get_unk_A0() == 0);
    sub_219320();
}

// "SignOut": in a game, asks whether to quit it ("yes" running unk_190);
// otherwise signs out or in and sets the texts.
// match: ?sub_219560@type_219010@@QAEXXZ @ 0x00219560
// match: __ehhandler$?sub_219560@type_219010@@QAEXXZ-0x36 @ 0x00307860
// match: __ehhandler$?sub_219560@type_219010@@QAEXXZ @ 0x00307896
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_219010::sub_219560()
{
    if (sub_219A80())
    {
        type_1CB670 var_2C("QUIT_GAME", 0);
        type_1CB670 local_80;

        if (sub_1C4BE0())
            local_80 = type_1CB670("QUIT_GAME_HOST", 0);
        else
            local_80 = type_1CB670("QUIT_GAME?", 0);
        type_1CB670 loc64("Yes", 0);
        type_1CB670 local_48("No", 0);

        sub_2171F0(var_2C, local_80, loc64, &unk_190, local_48, &unk_19C, &unk_19C);
    }
    else
    {
        if (sub_227560()->sub_228100())
        {
            sub_227560()->sub_2278C0();
            unk_220 = false;
        }
        else
        {
            sub_227560()->sub_2270E0(1);
            unk_220 = true;
        }
        sub_219320();
    }
}

// The update: the base's, then "Friends List" marked with the service's two
// flags, and the texts again when the sign-in has changed.
// match: ?vf_014@type_219010@@UAEXM@Z @ 0x00219790
// match: __ehhandler$?vf_014@type_219010@@UAEXM@Z-0xB @ 0x003078A0
// match: __ehhandler$?vf_014@type_219010@@UAEXM@Z @ 0x003078AB
void type_219010::vf_014(RwReal arg_0)
{
    RwInt32 lv_10;
    RwChar lv_114[256];

    type_21CB10::vf_014(arg_0);
    lv_10 = sub_227560()->sub_227950();
    if ((lv_10 & 3) == 3)
        sprintf(lv_114, "\xbc \xbd %s", type_1CB670("Friends List", 0).c_str());
    else if (lv_10 & 1)
        sprintf(lv_114, "\xbc %s", type_1CB670("Friends List", 0).c_str());
    else if (lv_10 & 2)
        sprintf(lv_114, "\xbd %s", type_1CB670("Friends List", 0).c_str());
    else
        sprintf(lv_114, "%s", type_1CB670("Friends List", 0).c_str());
    unk_1A8.sub_1F28C0(sub_1CB720(lv_114));
    if (unk_220 != sub_219AD0())
    {
        sub_219320();
        unk_220 = sub_219AD0();
    }
}

// match: ?sub_219A80@type_219010@@QAE_NXZ @ 0x00219A80
bool type_219010::sub_219A80()
{
    return !sub_20B410();
}

// match: ?sub_219AA0@type_219010@@QAEXXZ @ 0x00219AA0
void type_219010::sub_219AA0()
{
    sub_227560()->sub_2278C0();
    sub_1C44A0();
    vf_040();
}

// match: ?sub_219AD0@type_219010@@QAE_NXZ @ 0x00219AD0
bool type_219010::sub_219AD0()
{
    return sub_227560()->sub_228100();
}

// The actions' members (game/kujuui.h's templates, their definitions
// repeated here).
// match: ??0?$type_3E7264@Utype_219010@@@kujuUI@@QAE@PAUtype_219010@@P82@AEXXZP82@AE_NXZ@Z @ 0x00219AF0
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ??_G?$type_3E7264@Utype_219010@@@kujuUI@@UAEPAXI@Z @ 0x00219BC0
// match: ??1?$type_3E7264@Utype_219010@@@kujuUI@@UAE@XZ @ 0x00219B40
template <class T> type_3E7264<T>::~type_3E7264()
{
}

template <class T> void type_3E7264<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

template <class T> bool type_3E7264<T>::pvf_00C()
{
    return (unk_04->*unk_10)();
}

// match: ??0?$type_3E7CE8@Utype_219010@@@kujuUI@@QAE@PAUtype_219010@@P82@AEXXZ@Z @ 0x00219B60
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_219010@@@kujuUI@@UAEPAXI@Z @ 0x00219BF0
// match: ??1?$type_3E7CE8@Utype_219010@@@kujuUI@@UAE@XZ @ 0x00219BA0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_219010@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_219010::sub_1E41C0()
{
}
