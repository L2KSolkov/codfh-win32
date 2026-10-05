/*
 * The defect asked (game/ingamepages.h): "yes" and "no" answered to the
 * pause menu.
 */
#include "game/ingamepages.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_216760@@6B@ @ 0x003E97F0
// match: ??_7?$type_3E7CE8@Utype_216760@@@kujuUI@@6B@ @ 0x003E9840
// match: __ehhandler$??0type_216760@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x004243E8
// match: __ehhandler$??0type_216760@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00424400
// match: __ehhandler$??1type_216760@@UAE@XZ>1>8 @ 0x0042441C
// match: __ehhandler$??1type_216760@@UAE@XZ>1 @ 0x0042442C

// match: ??0type_216760@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00216760
// match: __ehhandler$??0type_216760@@QAE@PBDPAUtype_21A5E0@@@Z-0x24 @ 0x003071E0
// match: __ehhandler$??0type_216760@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00307204

type_216760::type_216760(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_216760::sub_2168C0), unk_160(this, &type_216760::sub_2168E0)
{
    sub_204FC0("yes", &unk_154);
    sub_204FC0("no", &unk_160);
}

// match: ??_Gtype_216760@@UAEPAXI@Z @ 0x00216820
// match: ??1type_216760@@UAE@XZ @ 0x00216850
// match: __ehhandler$??1type_216760@@UAE@XZ-0x16 @ 0x00307210
// match: __ehhandler$??1type_216760@@UAE@XZ @ 0x00307226
type_216760::~type_216760()
{
}

// match: ?sub_2168C0@type_216760@@QAEXXZ @ 0x002168C0
void type_216760::sub_2168C0()
{
    unk_130->sub_21C2D0(1);
}

// match: ?sub_2168E0@type_216760@@QAEXXZ @ 0x002168E0
void type_216760::sub_2168E0()
{
    unk_130->sub_21C2D0(0);
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_216760@@@kujuUI@@QAE@PAUtype_216760@@P82@AEXXZ@Z @ 0x00216900
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_216760@@@kujuUI@@UAEPAXI@Z @ 0x00216960
// match: ??1?$type_3E7CE8@Utype_216760@@@kujuUI@@UAE@XZ @ 0x00216940
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
