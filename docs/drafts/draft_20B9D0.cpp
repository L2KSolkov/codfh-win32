/*
 * The Xbox Live menu (in-game menu 6, game/livemenu.h): instant action,
 * finding or creating a session, the Live options, the options, back, and
 * the join failure page.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/frontend.h"

using namespace kujuUI;

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
