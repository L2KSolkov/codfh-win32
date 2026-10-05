/*
 * The host's options (game/ingamepages.h): the game settings and a
 * player's kick, from the pause menu.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E9A58
extern const RwReal flt_3E9A58 = 0.01f;
// 0x003E9A5C
extern const RwReal flt_3E9A5C = 0.01f;
// 0x003E9A60
extern const RwReal flt_3E9A60 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9A58@@3MB @ 0x003E9A58
// match: ?flt_3E9A5C@@3MB @ 0x003E9A5C
// match: ?flt_3E9A60@@3MB @ 0x003E9A60
// match: ??_C@_04FNIJDBCC@kick?$AA@ @ 0x003E9A64
// match: ??_C@_08MGBGGDON@settings?$AA@ @ 0x003E9A6C
// match: ??_7type_2179E0@@6B@ @ 0x003E9A78
// match: ??_7?$type_3E7CE8@Utype_2179E0@@@kujuUI@@6B@ @ 0x003E9AC8
// match: ??_7?$type_3E7264@Utype_2179E0@@@kujuUI@@6B@ @ 0x003E9AD8
// match: __ehhandler$??0type_2179E0@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00424654
// match: __ehhandler$??0type_2179E0@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x0042466C
// match: __ehhandler$??1type_2179E0@@UAE@XZ>1>8 @ 0x00424688
// match: __ehhandler$??1type_2179E0@@UAE@XZ>1 @ 0x00424698

// match: ??0type_2179E0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x002179E0
// match: __ehhandler$??0type_2179E0@@QAE@PBDPAUtype_21A5E0@@@Z-0x24 @ 0x00307480
// match: __ehhandler$??0type_2179E0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x003074A4

type_2179E0::type_2179E0(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_2179E0::sub_217B40),
      unk_160(this, &type_2179E0::sub_217B60, &type_2179E0::sub_217B80)
{
    sub_204FC0("settings", &unk_154);
    sub_204FC0("kick", &unk_160);
}

// match: ??_Gtype_2179E0@@UAEPAXI@Z @ 0x00217AA0
// match: ??1type_2179E0@@UAE@XZ @ 0x00217AD0
// match: __ehhandler$??1type_2179E0@@UAE@XZ-0x16 @ 0x003074B0
// match: __ehhandler$??1type_2179E0@@UAE@XZ @ 0x003074C6
type_2179E0::~type_2179E0()
{
}

// match: ?sub_217B40@type_2179E0@@QAEXXZ @ 0x00217B40
void type_2179E0::sub_217B40()
{
    unk_130->sub_21C200(0x10, 4);
}

// match: ?sub_217B60@type_2179E0@@QAEXXZ @ 0x00217B60
void type_2179E0::sub_217B60()
{
    unk_130->sub_21C200(0x11, 4);
}

// match: ?sub_217B80@type_2179E0@@QAE_NXZ @ 0x00217B80
bool type_2179E0::sub_217B80()
{
    return 1 < (RwUInt32)sub_1C45F0();
}

// The actions' members (game/kujuui.h's templates, their definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_2179E0@@@kujuUI@@QAE@PAUtype_2179E0@@P82@AEXXZ@Z @ 0x00217BA0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_2179E0@@@kujuUI@@UAEPAXI@Z @ 0x00217C70
// match: ??1?$type_3E7CE8@Utype_2179E0@@@kujuUI@@UAE@XZ @ 0x00217BE0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// match: ??0?$type_3E7264@Utype_2179E0@@@kujuUI@@QAE@PAUtype_2179E0@@P82@AEXXZP82@AE_NXZ@Z @ 0x00217C00
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ??_G?$type_3E7264@Utype_2179E0@@@kujuUI@@UAEPAXI@Z @ 0x00217CA0
// match: ??1?$type_3E7264@Utype_2179E0@@@kujuUI@@UAE@XZ @ 0x00217C50
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
