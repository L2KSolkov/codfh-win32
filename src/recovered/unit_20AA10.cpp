/*
 * The multiplayer menu (in-game menu 13, game/livemenu.h): back to the
 * dashboard, playing on Xbox Live or over the system link, and the join
 * failure page.
 */
#include "game/liveservice.h"
#include "types/cXboxLive.h"
#include "types/cXboxLiveNetGame.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/startup.h"
#include "game/savestate.h"
#include "game/movie.h"
#include "game/profiles.h"
#include "game/voice.h"
#include "types/musicplayer.h"
#include "types/type_4B8EF0.h"
#include "game/waitscreen.h"
#include "rws/camerahelper.h"
#include <string.h>
#include <stdio.h>

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E8E8C
extern const RwReal flt_3E8E8C = 0.01f;
// 0x003E8E90
extern const RwReal flt_3E8E90 = 0.01f;
// 0x003E8E94
extern const RwReal flt_3E8E94 = 16.666666f;
#endif
// 0x0042D298
RwChar aDDefaultXbe[16] = "d:\\default.xbe";
// 0x00504580
type_4F45F8 unk_504580;
// End of its data definitions.


using namespace kujuUI;

// The controllers' flags written into the launch data (game/levels.h; its
// globals clash with the in-game menus').
struct type_19BE30;
RwInt32 sub_19BE30(type_19BE30 *arg_0);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8E8C@@3MB @ 0x003E8E8C
// match: ?flt_3E8E90@@3MB @ 0x003E8E90
// match: ?flt_3E8E94@@3MB @ 0x003E8E94
// match: ??_C@_08HONHICEK@PlayLive?$AA@ @ 0x003E8E98
// match: ??_C@_0M@BIGKGMHO@PlayLANGame?$AA@ @ 0x003E8EA4
// match: ??_C@_0L@BPIIFICC@PlayOnline?$AA@ @ 0x003E8EB0
// match: ??_7type_20AA10@@6B@ @ 0x003E8EC0
// match: ??_C@_0BH@NONDIBNH@MultiplayerMenu?4layout?$AA@ @ 0x003E8F04
// match: ??_C@_0BC@DEEFHFAA@Play?5on?5Xbox?5Live?$AA@ @ 0x003E8F1C
// match: ??_7?$type_3E7CE8@Utype_20AA10@@@kujuUI@@6B@ @ 0x003E8F30
// match: ??_7?$type_3E7264@Utype_20AA10@@@kujuUI@@6B@ @ 0x003E8F40
// match: __ehhandler$??0type_20AA10@@QAE@XZ>1>8 @ 0x004230C0
// match: __ehhandler$??0type_20AA10@@QAE@XZ>1 @ 0x00423110
// match: __ehhandler$??1type_20AA10@@UAE@XZ>1>8 @ 0x0042312C
// match: __ehhandler$??1type_20AA10@@UAE@XZ>1 @ 0x00423174
// match: __ehhandler$?vf_014@type_20AA10@@UAEXM@Z>1>8 @ 0x00423190
// match: __ehhandler$?vf_014@type_20AA10@@UAEXM@Z>1 @ 0x004231A8
// match: ?aDDefaultXbe@@3PADA @ 0x0042D298

// match: ??0type_20AA10@@QAE@XZ @ 0x0020AA10
// match: __ehhandler$??0type_20AA10@@QAE@XZ-0x86 @ 0x00306150
// match: __ehhandler$??0type_20AA10@@QAE@XZ @ 0x003061D6

type_20AA10::type_20AA10()
    : type_2049D0("MultiplayerMenu.layout", 0, false), unk_188("JoinFailed.layout", 0, false),
      unk_310(this, &type_20AA10::sub_20AD30),
      unk_31C(this, &type_20AA10::sub_20AE90, &type_20AA10::sub_2015D0),
      unk_32C(this, &type_20AA10::sub_20AF10, &type_20AA10::sub_2015D0),
      unk_33C(this, &type_20AA10::sub_20BE60)
{
    sub_204FC0("Back", &unk_310);
    sub_204FC0("PlayOnline", &unk_31C);
    sub_204FC0("PlayLANGame", &unk_32C);
    sub_204FC0("PlayLive", &unk_3C0);
    unk_188.sub_204FC0("Back", &unk_33C);
    unk_188.sub_204FC0("Reason", &unk_348);
    unk_188.sub_204FC0("FailHeader", &unk_370);
    while (!sub_2046E0())
        sub_204700();
}

// match: ??_Gtype_20AA10@@UAEPAXI@Z @ 0x0020AC10
// match: ??1type_20AA10@@UAE@XZ @ 0x0020AC40
// match: __ehhandler$??1type_20AA10@@UAE@XZ-0x78 @ 0x003061E0
// match: __ehhandler$??1type_20AA10@@UAE@XZ @ 0x00306258
type_20AA10::~type_20AA10()
{
}

// match: ?sub_20AD30@type_20AA10@@QAEXXZ @ 0x0020AD30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_20AA10::sub_20AD30()
{
    strcpy(byte_4B1F68, aDDefaultXbe);
    sub_885B0(0);
    type_4F45F8 *var_8 = &unk_504580;
    memset(var_8, 0, 0x6A0);
    var_8->unk_00 = 1;
    var_8->unk_24 = get_dword_4B9E50();
    var_8->unk_10 = 1;
    var_8->unk_18 = 0;
    var_8->unk_14 = dword_4F45F8->unk_14;
    var_8->unk_394 = dword_4F45F8->unk_394;
    RwCamera *l4 = RWS::CameraHelper::CreateMainRasterCamera(Width, Height, ZDepth);
    sub_19BAC0(l4);
    sub_EA560(l4);
    RWS::CameraHelper::Destroy(l4);
    sub_19BE30((type_19BE30 *)var_8);
    sub_1A2650(var_8);
    if (XOnlineSaveLogonState((PXONLINE_LOGON_STATE)var_8->unk_48A) == 0 && sub_227560()->sub_228100() &&
        !sub_227560()->get_unk_1124())
        var_8->unk_40 = 1;
    else
        var_8->unk_40 = 0;
    D3DDevice_PersistDisplay();
    XLaunchNewImage(aDDefaultXbe, (PLAUNCH_DATA)&unk_504580);
}

// match: ?sub_20AE90@type_20AA10@@QAEXXZ @ 0x0020AE90
void type_20AA10::sub_20AE90()
{
    if (sub_1D8810()->unk_2918_is_1() == true)
        return;
    type_1FBDA0_menu *var_4 = 0;
    if (sub_1D8810()->voice_running())
        var_4 = sub_2046C0(6);
    else
        var_4 = sub_2046C0(12);
    sub_1FC310()->sub_1FBDA0(var_4);
}

// match: ?sub_20AF10@type_20AA10@@QAEXXZ @ 0x0020AF10
void type_20AA10::sub_20AF10()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(10));
    unk_4F7EB8.get_unk_19C_direct()->vf_058(1);
}

// match: ?vf_03C@type_20AA10@@UAEXXZ @ 0x0020AF50
void type_20AA10::vf_03C()
{
    type_2049D0::vf_03C();
    dword_5044DC = 1;
    unk_4F7EB8.get_unk_19C_direct()->vf_058(0);
    get_dword_4F8180()->unk_3060.sub_1C71D0();
}

// match: ?vf_040@type_20AA10@@UAEXXZ @ 0x0020AFB0
void type_20AA10::vf_040()
{
    type_1E7CF0 *var_4 = sub_1E7CF0();

    if (var_4->sub_1E7D00(&unk_188))
        var_4->sub_1E7D90(&unk_188);
}

// The update: the base's; a join that failed since (the service's unk_A4)
// shows "Join Failed" and why; then "Friends List" marked with the
// service's two flags.
// match: ?vf_014@type_20AA10@@UAEXM@Z @ 0x0020AFF0
// match: __ehhandler$?vf_014@type_20AA10@@UAEXM@Z-0x21 @ 0x00306270
// match: __ehhandler$?vf_014@type_20AA10@@UAEXM@Z @ 0x00306291
void type_20AA10::vf_014(RwReal arg_0)
{
    RwInt32 lv_10;
    RwChar lv_114[256];

    type_2049D0::vf_014(arg_0);
    if (sub_227560()->get_unk_A4())
    {
        sub_1E7CF0()->sub_1E7D30(&unk_188);
        unk_370.sub_1F28C0(type_1CB670("Join Failed", 0));
        unk_348.sub_1F28C0(type_1CB670("GAME_SESSION_UNAVAILABLE", 0));
        sub_227560()->set_unk_A4(0);
    }
    lv_10 = sub_227560()->sub_227950();
    if ((lv_10 & 3) == 3)
        sprintf(lv_114, "\xbc \xbd %s", sub_20B3A0().c_str());
    else if (lv_10 & 1)
        sprintf(lv_114, "\xbc %s", sub_20B3A0().c_str());
    else if (lv_10 & 2)
        sprintf(lv_114, "\xbd %s", sub_20B3A0().c_str());
    else
        sprintf(lv_114, "%s", sub_20B3A0().c_str());
    unk_3C0.sub_1F28C0(sub_1CB720(lv_114));
}

// match: ?sub_20B3A0@@YA?AUtype_1A5EA0@@XZ @ 0x0020B3A0
type_1A5EA0 sub_20B3A0()
{
    if (sub_1D8810()->unk_2918_is_1())
        return type_1A5EA0(dword_42D278[1], 0);
    return type_1A5EA0("Play on Xbox Live", 0);
}

// match: ?sub_20B410@@YA_NXZ @ 0x0020B410
bool sub_20B410()
{
    return sub_1D8810()->is_system_link();
}

// The actions' members (game/kujuui.h's templates, their definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_20AA10@@@kujuUI@@QAE@PAUtype_20AA10@@P82@AEXXZ@Z @ 0x0020B440
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_20AA10@@@kujuUI@@UAEPAXI@Z @ 0x0020B510
// match: ??1?$type_3E7CE8@Utype_20AA10@@@kujuUI@@UAE@XZ @ 0x0020B480
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// match: ??0?$type_3E7264@Utype_20AA10@@@kujuUI@@QAE@PAUtype_20AA10@@P82@AEXXZP82@AE_NXZ@Z @ 0x0020B4A0
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ??_G?$type_3E7264@Utype_20AA10@@@kujuUI@@UAEPAXI@Z @ 0x0020B540
// match: ??1?$type_3E7264@Utype_20AA10@@@kujuUI@@UAE@XZ @ 0x0020B4F0
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

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_20BE60@type_20AA10@@QAEXXZ (folded into 0x20BE60)
void type_20AA10::sub_20BE60()
{
    sub_1E7CF0()->sub_1E7D90(&unk_188);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_2015D0@type_20AA10@@QAE_NXZ (folded into 0x2015D0)
bool type_20AA10::sub_2015D0()
{
    return true;
}
