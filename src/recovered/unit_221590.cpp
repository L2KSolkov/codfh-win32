/*
 * A "use now" question (game/ingamepages.h): "yes" and "no" answering the
 * pause menu.
 */
#include "game/ingamepages.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_221590@@6B@ @ 0x003EA800
// match: ??_7?$type_3E7CE8@Utype_221590@@@kujuUI@@6B@ @ 0x003EA850
// match: __ehhandler$??0type_221590@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00425848
// match: __ehhandler$??0type_221590@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00425860
// match: __ehhandler$??1type_221590@@UAE@XZ>1>8 @ 0x0042587C
// match: __ehhandler$??1type_221590@@UAE@XZ>1 @ 0x0042588C

// match: ??0type_221590@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00221590
// match: __ehhandler$??0type_221590@@QAE@PBDPAUtype_21A5E0@@@Z-0x24 @ 0x003087E0
// match: __ehhandler$??0type_221590@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00308804

type_221590::type_221590(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_221590::sub_219E70), unk_160(this, &type_221590::sub_219E90)
{
    sub_204FC0("yes", &unk_154);
    sub_204FC0("no", &unk_160);
}

// match: ??_Gtype_221590@@UAEPAXI@Z @ 0x00221650
// match: ??1type_221590@@UAE@XZ @ 0x00221680
// match: __ehhandler$??1type_221590@@UAE@XZ-0x16 @ 0x00308810
// match: __ehhandler$??1type_221590@@UAE@XZ @ 0x00308826
type_221590::~type_221590()
{
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_221590@@@kujuUI@@QAE@PAUtype_221590@@P82@AEXXZ@Z @ 0x002216F0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_221590@@@kujuUI@@UAEPAXI@Z @ 0x00221750
// match: ??1?$type_3E7CE8@Utype_221590@@@kujuUI@@UAE@XZ @ 0x00221730
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_219E70@type_221590@@QAEXXZ (folded into 0x219E70)
void type_221590::sub_219E70()
{
    unk_130->sub_21C280(1);
}

// ?sub_219E90@type_221590@@QAEXXZ (folded into 0x219E90)
void type_221590::sub_219E90()
{
    unk_130->sub_21C280(0);
}
