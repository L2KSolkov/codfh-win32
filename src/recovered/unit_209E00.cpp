// Split from unit_209D00.cpp at 0x209E00, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include <stdio.h>
#include "game/liveservice.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/frontend.h"
#include "game/startup.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E8CA4
extern const RwReal flt_3E8CA4 = 0.01f;
// 0x003E8CA8
extern const RwReal flt_3E8CA8 = 0.01f;
// 0x003E8CAC
extern const RwReal flt_3E8CAC = 16.666666f;
#endif

// match: ?flt_3E8CA4@@3MB @ 0x003E8CA4
// match: ?flt_3E8CA8@@3MB @ 0x003E8CA8
// match: ?flt_3E8CAC@@3MB @ 0x003E8CAC


using namespace kujuUI;

// match: __ehhandler$??0type_209E00@@QAE@XZ>1>8 @ 0x00422F2C
// match: __ehhandler$??0type_209E00@@QAE@XZ>1 @ 0x00422F74
// match: __ehhandler$??1type_209E00@@UAE@XZ>1>8 @ 0x00422F90
// match: __ehhandler$??1type_209E00@@UAE@XZ>1 @ 0x00422FD0
// match: __ehhandler$?sub_20A0E0@type_209E00@@QAEXXZ>1>8 @ 0x00422FEC
// match: __ehhandler$?sub_20A0E0@type_209E00@@QAEXXZ>1 @ 0x00422FFC
// match: __ehhandler$?vf_014@type_209E00@@UAEXM@Z>1>8 @ 0x00423018
// match: __ehhandler$?vf_014@type_209E00@@UAEXM@Z>1 @ 0x00423020
// match: __ehhandler$?sub_20A540@@YAPAUtype_3E7D08@kujuUI@@XZ>1>8 @ 0x0042303C
// match: __ehhandler$?sub_20A540@@YAPAUtype_3E7D08@kujuUI@@XZ>1 @ 0x00423044
// match: ??_C@_0N@EMPCLLCP@AppearStatus?$AA@ @ 0x003E8CB0
// match: ??_C@_0BA@PBAGBHA@FriendsFlagText?$AA@ @ 0x003E8CC0
// match: ??_C@_07LGLHHFGJ@SignOut?$AA@ @ 0x003E8CD0
// match: ??_C@_0O@CLOGMNHM@AppearOffline?$AA@ @ 0x003E8CD8
// match: ??_C@_0L@IGLHMACH@PlayerList?$AA@ @ 0x003E8CE8
// match: ??_C@_0M@DHNLOJMJ@FriendsList?$AA@ @ 0x003E8CF4
// match: ??_7type_209E00@@6B@ @ 0x003E8D00
// match: ??_C@_0BD@IEEMCICD@LiveOptions?4layout?$AA@ @ 0x003E8D44
// match: ??_C@_0O@JEFLIBEJ@Appear?5Online?$AA@ @ 0x003E8D58
// match: ??_C@_0P@NMAIAIHO@Appear?5Offline?$AA@ @ 0x003E8D68
// match: ??_C@_04ELCMMFEH@?$LN?5?$CFs?$AA@ @ 0x003E8D78
// match: ??_C@_04HGEMOMPH@?$LM?5?$CFs?$AA@ @ 0x003E8D80
// match: ??_C@_06PABLMNMG@?$LM?5?$LN?5?$CFs?$AA@ @ 0x003E8D88
// match: ??_C@_0N@OFCANDCE@Friends?5List?$AA@ @ 0x003E8D90
// match: ??_7?$type_3E7CE8@Utype_209E00@@@kujuUI@@6B@ @ 0x003E8DA0

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// match: ??0type_209E00@@QAE@XZ @ 0x00209E00
// match: __ehhandler$??0type_209E00@@QAE@XZ-0x78 @ 0x00305F90
// match: __ehhandler$??0type_209E00@@QAE@XZ @ 0x00306008
type_209E00::type_209E00()
    : type_2049D0("LiveOptions.layout", 0, true), unk_188(this, &type_209E00::sub_20A1B0),
      unk_194(this, &type_209E00::sub_20A1D0), unk_1A0(this, &type_209E00::sub_1E41C0),
      unk_1AC(this, &type_209E00::sub_20A1F0), unk_1B8(this, &type_209E00::sub_20A240)
{
    sub_204FC0("Back", &unk_188);
    sub_204FC0("FriendsList", &unk_194);
    sub_204FC0("PlayerList", &unk_1A0);
    sub_204FC0("AppearOffline", &unk_1AC);
    sub_204FC0("SignOut", &unk_1B8);
    sub_204FC0("FriendsFlagText", &unk_350);
    sub_204FC0("AppearStatus", &unk_378);
    dword_504578 = this;
    sub_20EA40();
    sub_20A0E0();
}
// match: ??_Gtype_209E00@@UAEPAXI@Z @ 0x00209FD0
// match: ??1type_209E00@@UAE@XZ @ 0x0020A000
// match: __ehhandler$??1type_209E00@@UAE@XZ-0x6A @ 0x00306020
// match: __ehhandler$??1type_209E00@@UAE@XZ @ 0x0030608A
type_209E00::~type_209E00()
{
    dword_504578 = 0;
}
// "AppearStatus" shows "Appear Offline" or "Appear Online" as the service
// appears.
// match: ?sub_20A0E0@type_209E00@@QAEXXZ @ 0x0020A0E0
// match: __ehhandler$?sub_20A0E0@type_209E00@@QAEXXZ-0x10 @ 0x003060A0
// match: __ehhandler$?sub_20A0E0@type_209E00@@QAEXXZ @ 0x003060B0
void type_209E00::sub_20A0E0()
{
    if (sub_227560()->get_unk_A0_direct())
        unk_378.sub_1F28C0(type_1CB670("Appear Offline", 0));
    else
        unk_378.sub_1F28C0(type_1CB670("Appear Online", 0));
}
// match: ?sub_20A1B0@type_209E00@@QAEXXZ @ 0x0020A1B0
void type_209E00::sub_20A1B0()
{
    sub_1E7CF0()->sub_1E7D90(this);
}
// match: ?sub_20A1D0@type_209E00@@QAEXXZ @ 0x0020A1D0
void type_209E00::sub_20A1D0()
{
    unk_1C4.sub_20A520();
}
// match: ?sub_20A1F0@type_209E00@@QAEXXZ @ 0x0020A1F0
void type_209E00::sub_20A1F0()
{
    if (sub_227560()->get_unk_A0())
        sub_227560()->sub_227B80(0);
    else
        sub_227560()->sub_227B80(1);
    sub_20A0E0();
}
// match: ?sub_20A240@type_209E00@@QAEXXZ @ 0x0020A240
void type_209E00::sub_20A240()
{
    sub_227560()->sub_2278C0();
    sub_1E7CF0()->sub_1E7D90(this);
    dword_504568 = 1;
}
// The update: the Live options' text marked with the pending friend
// requests and game invitations.
// match: ?vf_014@type_209E00@@UAEXM@Z @ 0x0020A280
// match: __ehhandler$?vf_014@type_209E00@@UAEXM@Z-0xB @ 0x003060C0
// match: __ehhandler$?vf_014@type_209E00@@UAEXM@Z @ 0x003060CB
void type_209E00::vf_014(RwReal arg_0)
{
    RwInt32 lv_10;
    RwChar lv_114[256];

    type_2049D0::vf_014(arg_0);
    lv_10 = sub_227560()->sub_227950();
    if ((lv_10 & 3) == 3)
        sprintf(lv_114, "\xbc \xbd %s", type_1CB670("Friends List", 0).c_str());
    else if (lv_10 & 1)
        sprintf(lv_114, "\xbc %s", type_1CB670("Friends List", 0).c_str());
    else if (lv_10 & 2)
        sprintf(lv_114, "\xbd %s", type_1CB670("Friends List", 0).c_str());
    else
        sprintf(lv_114, "%s", type_1CB670("Friends List", 0).c_str());
    unk_350.sub_1F28C0(sub_1CB720(lv_114));
}
// match: ?sub_20A520@type_2049D0@@QAEXXZ @ 0x0020A520
void type_2049D0::sub_20A520()
{
    sub_1E7CF0()->sub_1E7D30(this);
}
// match: ?sub_20A540@@YAPAUtype_3E7D08@kujuUI@@XZ @ 0x0020A540
// match: __ehhandler$?sub_20A540@@YAPAUtype_3E7D08@kujuUI@@XZ-0xB @ 0x003060E0
// match: __ehhandler$?sub_20A540@@YAPAUtype_3E7D08@kujuUI@@XZ @ 0x003060EB
type_3E7D08 *sub_20A540()
{
    if (!dword_504578)
        dword_504578 = new type_209E00();
    return dword_504578;
}
// match: ?vf_018@type_209E00@@UAEXPAUtype_1E4130@kujuUI@@@Z @ 0x0020A5C0
void type_209E00::vf_018(type_1E4130 *arg_0)
{
    type_2049D0::vf_018(arg_0);
}
// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_209E00@@@kujuUI@@QAE@PAUtype_209E00@@P82@AEXXZ@Z @ 0x0020A5E0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}
// match: ??_G?$type_3E7CE8@Utype_209E00@@@kujuUI@@UAEPAXI@Z @ 0x0020A640
// match: ??1?$type_3E7CE8@Utype_209E00@@@kujuUI@@UAE@XZ @ 0x0020A620
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}
