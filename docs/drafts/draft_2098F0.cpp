/*
 * The system link's menu (in-game menu 10, game/livemenu.h): finding a
 * session, creating one, the options, or back.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

using namespace kujuUI;

// match: ??0type_2098F0@@QAE@XZ @ 0x002098F0
type_2098F0::type_2098F0()
    : type_2049D0("XboxSysLink.layout", 0, true), unk_188(this, &type_2098F0::sub_209AD0),
      unk_194(this, &type_2098F0::sub_209B00), unk_1A0(this, &type_2098F0::sub_20BE30),
      unk_1AC(this, &type_2098F0::sub_209B30)
{
    sub_204FC0("FindSession", &unk_188);
    sub_204FC0("CreateSession", &unk_194);
    sub_204FC0("Back", &unk_1A0);
    sub_204FC0("Options", &unk_1AC);
}

// match: ??_Gtype_2098F0@@UAEPAXI@Z @ 0x00209A10
// match: ??1type_2098F0@@UAE@XZ @ 0x00209A40
type_2098F0::~type_2098F0()
{
}

// match: ?sub_209AD0@type_2098F0@@QAEXXZ @ 0x00209AD0
void type_2098F0::sub_209AD0()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(9));
}

// match: ?sub_209B00@type_2098F0@@QAEXXZ @ 0x00209B00
void type_2098F0::sub_209B00()
{
    type_2053C0::sub_205BF0(0);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(8));
}

// match: ?sub_209B30@type_2098F0@@QAEXXZ @ 0x00209B30
void type_2098F0::sub_209B30()
{
    sub_20B920(1);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(5));
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_2098F0@@@kujuUI@@QAE@PAUtype_2098F0@@P82@AEXXZ@Z @ 0x00209B60
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_2098F0@@@kujuUI@@UAEPAXI@Z @ 0x00209BC0
// match: ??1?$type_3E7CE8@Utype_2098F0@@@kujuUI@@UAE@XZ @ 0x00209BA0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
