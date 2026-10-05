/*
 * The online settings (game/ingamepages.h): the host options pages' base
 * over "OnlineSettings.layout" with "SaveNow", which writes and sends the
 * options and leaves the pause menu.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

using namespace kujuUI;

// match: ??0type_217CD0@@QAE@PBD0PAUtype_21A5E0@@@Z @ 0x00217CD0
// match: __ehhandler$??0type_217CD0@@QAE@PBD0PAUtype_21A5E0@@@Z-0x16 @ 0x003074D0
// match: __ehhandler$??0type_217CD0@@QAE@PBD0PAUtype_21A5E0@@@Z @ 0x003074E6
type_217CD0::type_217CD0(const RwChar *arg_0, const RwChar *arg_4, type_21A5E0 *arg_8)
    : type_219FE0(arg_0, arg_4, arg_8, true), unk_6C0(this, &type_217CD0::sub_217E60)
{
    sub_204FC0("SaveNow", &unk_6C0);
}

// match: ??_Gtype_217CD0@@UAEPAXI@Z @ 0x00217D80
// match: ??1type_217CD0@@UAE@XZ @ 0x00217DB0
// match: __ehhandler$??1type_217CD0@@UAE@XZ-0x8 @ 0x003074F0
// match: __ehhandler$??1type_217CD0@@UAE@XZ @ 0x003074F8
type_217CD0::~type_217CD0()
{
}

// match: ?vf_008@type_217CD0@@UAEXXZ @ 0x00217E20
void type_217CD0::vf_008()
{
    type_21CB10::vf_008();
    sub_1C3D20();
    sub_201890();
    sub_2016A0();
}

// match: ?sub_217E60@type_217CD0@@QAEXXZ @ 0x00217E60
void type_217CD0::sub_217E60()
{
    sub_201A70();
    unk_130->sub_21C360();
    sub_1C3D60(1);
}

// The action's members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_217CD0@@@kujuUI@@QAE@PAUtype_217CD0@@P82@AEXXZ@Z @ 0x00217EA0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_217CD0@@@kujuUI@@UAEPAXI@Z @ 0x00217F10
// match: ??1?$type_3E7CE8@Utype_217CD0@@@kujuUI@@UAE@XZ @ 0x00217EF0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
