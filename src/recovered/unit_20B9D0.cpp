/*
 * The Xbox Live menu (in-game menu 6, game/livemenu.h): instant action,
 * finding or creating a session, the Live options, the options, back, and
 * the join failure page.
 */
#include <stdio.h>
#include "game/liveservice.h"
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/frontend.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E9024
extern const RwReal flt_3E9024 = 0.01f;
// 0x003E9028
extern const RwReal flt_3E9028 = 0.01f;
// 0x003E902C
extern const RwReal flt_3E902C = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9024@@3MB @ 0x003E9024
// match: ?flt_3E9028@@3MB @ 0x003E9028
// match: ?flt_3E902C@@3MB @ 0x003E902C
// match: ??_C@_0BA@LGABJBPG@XboxLiveOptions?$AA@ @ 0x003E9030
// match: ??_C@_0O@DEJKLHIL@InstantAction?$AA@ @ 0x003E9040
// match: ??_7type_20B9D0@@6B@ @ 0x003E9050
// match: ??_C@_0BC@NMLPOHBN@PlayOnline?4layout?$AA@ @ 0x003E9094
// match: ??_C@_0BC@DGGCLGE@Xbox?5Live?5Options?$AA@ @ 0x003E90A8
// match: ??_7?$type_3E7CE8@Utype_20B9D0@@@kujuUI@@6B@ @ 0x003E90BC
// match: __ehhandler$??0type_20B9D0@@QAE@XZ>1>8 @ 0x00423234
// match: __ehhandler$??0type_20B9D0@@QAE@XZ>1 @ 0x00423294
// match: __ehhandler$??1type_20B9D0@@UAE@XZ>1>8 @ 0x004232B0
// match: __ehhandler$??1type_20B9D0@@UAE@XZ>1 @ 0x00423308
// match: __ehhandler$?vf_014@type_20B9D0@@UAEXM@Z>1>8 @ 0x00423324
// match: __ehhandler$?vf_014@type_20B9D0@@UAEXM@Z>1 @ 0x0042333C

// match: ??0type_20B9D0@@QAE@XZ @ 0x0020B9D0
// match: __ehhandler$??0type_20B9D0@@QAE@XZ-0xA2 @ 0x00306330
// match: __ehhandler$??0type_20B9D0@@QAE@XZ @ 0x003063D2

type_20B9D0::type_20B9D0()
    : type_2049D0("PlayOnline.layout", 0, true), unk_188("JoinFailed.layout", 0, true),
      unk_310(this, &type_20B9D0::sub_20BD70), unk_31C(this, &type_20B9D0::sub_20C390),
      unk_328(this, &type_20B9D0::sub_20BDA0), unk_334(this, &type_20B9D0::sub_20BE00),
      unk_340(this, &type_20B9D0::sub_20BDD0), unk_34C(this, &type_20B9D0::sub_20BE30),
      unk_358(this, &type_20B9D0::sub_20BE60)
{
    sub_204FC0("InstantAction", &unk_310);
    sub_204FC0("FindSession", &unk_31C);
    sub_204FC0("CreateSession", &unk_328);
    sub_204FC0("XboxLiveOptions", &unk_334);
    sub_204FC0("Options", &unk_340);
    sub_204FC0("Back", &unk_34C);
    sub_204FC0("PlayLive", &unk_3B4);
    unk_188.sub_204FC0("Back", &unk_358);
    unk_188.sub_204FC0("Reason", &unk_364);
    unk_188.sub_204FC0("FailHeader", &unk_38C);
}

// match: ??_Gtype_20B9D0@@UAEPAXI@Z @ 0x0020BC30
// match: ??1type_20B9D0@@UAE@XZ @ 0x0020BC60
// match: __ehhandler$??1type_20B9D0@@UAE@XZ-0x94 @ 0x003063E0
// match: __ehhandler$??1type_20B9D0@@UAE@XZ @ 0x00306474
type_20B9D0::~type_20B9D0()
{
}

// match: ?sub_20BD70@type_20B9D0@@QAEXXZ @ 0x0020BD70
void type_20B9D0::sub_20BD70()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(2));
}

// match: ?sub_20BDA0@type_20B9D0@@QAEXXZ @ 0x0020BDA0
void type_20B9D0::sub_20BDA0()
{
    type_2053C0::sub_205BF0(0);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(0));
}

// match: ?sub_20BDD0@type_20B9D0@@QAEXXZ @ 0x0020BDD0
void type_20B9D0::sub_20BDD0()
{
    sub_20B920(0);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(5));
}

// match: ?sub_20BE00@type_20B9D0@@QAEXXZ @ 0x0020BE00
void type_20B9D0::sub_20BE00()
{
    sub_20B920(0);
    ((type_2049D0 *)sub_20A540())->sub_20A520();
}

// match: ?sub_20BE30@type_20B9D0@@QAEXXZ @ 0x0020BE30
void type_20B9D0::sub_20BE30()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(13));
}

// match: ?sub_20BE60@type_20B9D0@@QAEXXZ @ 0x0020BE60
void type_20B9D0::sub_20BE60()
{
    sub_1E7CF0()->sub_1E7D90(&unk_188);
}

// The update: joins a session waiting to be joined, shows the join failure
// page when a join failed, and marks the Live options with the pending
// friend requests and game invitations.
// match: ?vf_014@type_20B9D0@@UAEXM@Z @ 0x0020BE80
// match: __ehhandler$?vf_014@type_20B9D0@@UAEXM@Z-0x21 @ 0x00306480
// match: __ehhandler$?vf_014@type_20B9D0@@UAEXM@Z @ 0x003064A1
void type_20B9D0::vf_014(RwReal arg_0)
{
    RwInt32 lv_10;
    RwChar lv_114[256];

    type_2049D0::vf_014(arg_0);
    if (sub_227560()->get_unk_144())
        sub_227560()->sub_227F30();
    if (sub_227560()->get_unk_A4())
    {
        sub_1E7CF0()->sub_1E7D30(&unk_188);
        unk_38C.sub_1F28C0(type_1CB670("Join Failed", 0));
        unk_364.sub_1F28C0(type_1CB670("GAME_SESSION_UNAVAILABLE", 0));
        sub_227560()->set_unk_A4(0);
    }
    lv_10 = sub_227560()->sub_227950();
    if ((lv_10 & 3) == 3)
        sprintf(lv_114, "\xbc \xbd %s", type_1CB670("Xbox Live Options", 0).c_str());
    else if (lv_10 & 1)
        sprintf(lv_114, "\xbc %s", type_1CB670("Xbox Live Options", 0).c_str());
    else if (lv_10 & 2)
        sprintf(lv_114, "\xbd %s", type_1CB670("Xbox Live Options", 0).c_str());
    else
        sprintf(lv_114, "%s", type_1CB670("Xbox Live Options", 0).c_str());
    unk_3B4.sub_1F28C0(sub_1CB720(lv_114));
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_20B9D0@@@kujuUI@@QAE@PAUtype_20B9D0@@P82@AEXXZ@Z @ 0x0020C260
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_20B9D0@@@kujuUI@@UAEPAXI@Z @ 0x0020C2C0
// match: ??1?$type_3E7CE8@Utype_20B9D0@@@kujuUI@@UAE@XZ @ 0x0020C2A0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_040@type_20B9D0@@UAEXXZ (folded into 0x20AFB0)
void type_20B9D0::vf_040()
{
    type_1E7CF0 *var_4 = sub_1E7CF0();

    if (var_4->sub_1E7D00(&unk_188))
        var_4->sub_1E7D90(&unk_188);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_20C390@type_20B9D0@@QAEXXZ (folded into 0x20C390)
void type_20B9D0::sub_20C390()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(1));
}
