/*
 * The instant action page (in-game menu 2, game/livemenu.h): a game of the
 * type picked found at once (the in-game menu 3 then), or back to the Live
 * menu.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"

using namespace kujuUI;

// match: ??0type_206D10@@QAE@XZ @ 0x00206D10
type_206D10::type_206D10()
    : type_2049D0("InstantAction.layout", 0, true), unk_188(this, &type_206D10::sub_206F90, 0x20),
      unk_198(this, &type_206D10::sub_206F90, 1), unk_1A8(this, &type_206D10::sub_206F90, 2),
      unk_1B8(this, &type_206D10::sub_206F90, 4), unk_1C8(this, &type_206D10::sub_206F90, 8),
      unk_1D8(this, &type_206D10::sub_206FC0)
{
    sub_204FC0("Any", &unk_188);
    sub_204FC0("Deathmatch", &unk_198);
    sub_204FC0("TeamDeathmatch", &unk_1A8);
    sub_204FC0("CaptureTheFlag", &unk_1B8);
    sub_204FC0("SearchAndDestroy", &unk_1C8);
    sub_204FC0("Back", &unk_1D8);
}

// match: ??_Gtype_206D10@@UAEPAXI@Z @ 0x00206EA0
// match: ??1type_206D10@@UAE@XZ @ 0x00206ED0
type_206D10::~type_206D10()
{
}

// match: ?sub_206F90@type_206D10@@QAEXH@Z @ 0x00206F90
void type_206D10::sub_206F90(RwInt32 arg_0)
{
    sub_208990(arg_0);
    sub_1FC310()->sub_1FBDA0(sub_2046C0(3));
}

// match: ?sub_206FC0@type_206D10@@QAEXXZ @ 0x00206FC0
void type_206D10::sub_206FC0()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(6));
}

// The actions' instances (game/kujuui.h's templates, their definitions
// repeated here).
template <class T> type_3E88C4<T>::type_3E88C4(T *arg_0, void (T::*arg_4)(RwInt32), RwInt32 arg_8)
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_0C = arg_8;
}

template <class T> type_3E88C4<T>::~type_3E88C4()
{
}

template <class T> void type_3E88C4<T>::pvf_008()
{
    (unk_04->*unk_08)(unk_0C);
}

template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
