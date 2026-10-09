/*
 * The votes' choice (game/ingamepages.h): a player, the map or the game
 * type to vote on.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003EAA20
extern const RwReal flt_3EAA20 = 0.01f;
// 0x003EAA24
extern const RwReal flt_3EAA24 = 0.01f;
// 0x003EAA28
extern const RwReal flt_3EAA28 = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EAA20@@3MB @ 0x003EAA20
// match: ?flt_3EAA24@@3MB @ 0x003EAA24
// match: ?flt_3EAA28@@3MB @ 0x003EAA28
// match: ??_C@_04MJNAPEEI@game?$AA@ @ 0x003EAA2C
// match: ??_C@_06BALNJMNP@player?$AA@ @ 0x003EAA34
// match: ??_7type_2225E0@@6B@ @ 0x003EAA40
// match: ??_7?$type_3E7264@Utype_2225E0@@@kujuUI@@6B@ @ 0x003EAA90
// match: ??_7?$type_3E7CE8@Utype_2225E0@@@kujuUI@@6B@ @ 0x003EAAA0
// match: __ehhandler$??0type_2225E0@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00425A7C
// match: __ehhandler$??0type_2225E0@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00425A9C
// match: __ehhandler$??1type_2225E0@@UAE@XZ>1>8 @ 0x00425AB8
// match: __ehhandler$??1type_2225E0@@UAE@XZ>1 @ 0x00425AD0

// match: ??0type_2225E0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x002225E0
// match: __ehhandler$??0type_2225E0@@QAE@PBDPAUtype_21A5E0@@@Z-0x32 @ 0x00308A30
// match: __ehhandler$??0type_2225E0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00308A62

type_2225E0::type_2225E0(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_2225E0::sub_222790, &type_2225E0::sub_2227F0),
      unk_164(this, &type_2225E0::sub_2227B0), unk_170(this, &type_2225E0::sub_2227D0)
{
    sub_204FC0("player", &unk_154);
    sub_204FC0("map", &unk_164);
    sub_204FC0("game", &unk_170);
}

// match: ??_Gtype_2225E0@@UAEPAXI@Z @ 0x002226E0
// match: ??1type_2225E0@@UAE@XZ @ 0x00222710
// match: __ehhandler$??1type_2225E0@@UAE@XZ-0x24 @ 0x00308A70
// match: __ehhandler$??1type_2225E0@@UAE@XZ @ 0x00308A94
type_2225E0::~type_2225E0()
{
}

// match: ?sub_222790@type_2225E0@@QAEXXZ @ 0x00222790
void type_2225E0::sub_222790()
{
    unk_130->sub_21C200(9, 8);
}

// match: ?sub_2227B0@type_2225E0@@QAEXXZ @ 0x002227B0
void type_2225E0::sub_2227B0()
{
    unk_130->sub_21C200(0xA, 8);
}

// match: ?sub_2227D0@type_2225E0@@QAEXXZ @ 0x002227D0
void type_2225E0::sub_2227D0()
{
    unk_130->sub_21C200(0xB, 8);
}

// match: ?sub_2227F0@type_2225E0@@QAE_NXZ @ 0x002227F0
bool type_2225E0::sub_2227F0()
{
    return (RwUInt32)sub_1C45F0() > 2 || (RwUInt32)sub_1C45F0() > 1 && sub_1C4BE0();
}

// The actions' members (game/kujuui.h's templates, their definitions
// repeated here).
// match: ??0?$type_3E7264@Utype_2225E0@@@kujuUI@@QAE@PAUtype_2225E0@@P82@AEXXZP82@AE_NXZ@Z @ 0x00222830
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ??_G?$type_3E7264@Utype_2225E0@@@kujuUI@@UAEPAXI@Z @ 0x00222900
// match: ??1?$type_3E7264@Utype_2225E0@@@kujuUI@@UAE@XZ @ 0x00222880
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

// match: ??0?$type_3E7CE8@Utype_2225E0@@@kujuUI@@QAE@PAUtype_2225E0@@P82@AEXXZ@Z @ 0x002228A0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_2225E0@@@kujuUI@@UAEPAXI@Z @ 0x00222930
// match: ??1?$type_3E7CE8@Utype_2225E0@@@kujuUI@@UAE@XZ @ 0x002228E0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
