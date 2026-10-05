/*
 * The next round asked (game/ingamepages.h): "yes" and "no" answering the
 * pause menu.
 */
#include "game/ingamepages.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_219D10@@6B@ @ 0x003E9EB8
// match: ??_7?$type_3E7CE8@Utype_219D10@@@kujuUI@@6B@ @ 0x003E9F08
// match: __ehhandler$??0type_219D10@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00424B0C
// match: __ehhandler$??0type_219D10@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00424B24
// match: __ehhandler$??1type_219D10@@UAE@XZ>1>8 @ 0x00424B40
// match: __ehhandler$??1type_219D10@@UAE@XZ>1 @ 0x00424B50

// match: ??0type_219D10@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00219D10
// match: __ehhandler$??0type_219D10@@QAE@PBDPAUtype_21A5E0@@@Z-0x24 @ 0x003078C0
// match: __ehhandler$??0type_219D10@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x003078E4

type_219D10::type_219D10(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_219D10::sub_219E70), unk_160(this, &type_219D10::sub_219E90)
{
    sub_204FC0("yes", &unk_154);
    sub_204FC0("no", &unk_160);
}

// match: ??_Gtype_219D10@@UAEPAXI@Z @ 0x00219DD0
// match: ??1type_219D10@@UAE@XZ @ 0x00219E00
// match: __ehhandler$??1type_219D10@@UAE@XZ-0x16 @ 0x003078F0
// match: __ehhandler$??1type_219D10@@UAE@XZ @ 0x00307906
type_219D10::~type_219D10()
{
}

// match: ?sub_219E70@type_219D10@@QAEXXZ @ 0x00219E70
void type_219D10::sub_219E70()
{
    unk_130->sub_21C280(1);
}

// match: ?sub_219E90@type_219D10@@QAEXXZ @ 0x00219E90
void type_219D10::sub_219E90()
{
    unk_130->sub_21C280(0);
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_219D10@@@kujuUI@@QAE@PAUtype_219D10@@P82@AEXXZ@Z @ 0x00219EB0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_219D10@@@kujuUI@@UAEPAXI@Z @ 0x00219F30
// match: ??1?$type_3E7CE8@Utype_219D10@@@kujuUI@@UAE@XZ @ 0x00219EF0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

// match: ?pvf_008@?$type_3E7CE8@Utype_219D10@@@kujuUI@@UAEXXZ @ 0x00219F10
template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
