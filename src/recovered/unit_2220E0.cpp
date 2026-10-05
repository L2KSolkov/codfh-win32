/*
 * The vote over the game type (game/ingamepages.h): the type picked and
 * "confirm" calling the vote.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EA93C
extern const RwReal flt_3EA93C = 0.01f;
// 0x003EA940
extern const RwReal flt_3EA940 = 0.01f;
// 0x003EA944
extern const RwReal flt_3EA944 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA93C@@3MB @ 0x003EA93C
// match: ?flt_3EA940@@3MB @ 0x003EA940
// match: ?flt_3EA944@@3MB @ 0x003EA944
// match: ??_C@_07FMMDEGFI@confirm?$AA@ @ 0x003EA948
// match: ??_7type_2220E0@@6B@ @ 0x003EA950
// match: ??_7?$type_3E7CE8@Utype_2220E0@@@kujuUI@@6B@ @ 0x003EA9A0
// match: __ehhandler$??0type_2220E0@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x0042599C
// match: __ehhandler$??0type_2220E0@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x004259BC
// match: __ehhandler$??1type_2220E0@@UAE@XZ>1>8 @ 0x004259D8
// match: __ehhandler$??1type_2220E0@@UAE@XZ>1 @ 0x004259F0

// match: ??0type_2220E0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x002220E0
// match: __ehhandler$??0type_2220E0@@QAE@PBDPAUtype_21A5E0@@@Z-0x32 @ 0x00308950
// match: __ehhandler$??0type_2220E0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00308982

type_2220E0::type_2220E0(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_2220E0::sub_1E41C0), unk_160(this, &type_2220E0::sub_222270),
      unk_16C(0, &unk_154)
{
    sub_204FC0("MapType", &unk_16C);
    sub_204FC0("confirm", &unk_160);
}

// match: ??_Gtype_2220E0@@UAEPAXI@Z @ 0x002221C0
// match: ??1type_2220E0@@UAE@XZ @ 0x002221F0
// match: __ehhandler$??1type_2220E0@@UAE@XZ-0x24 @ 0x00308990
// match: __ehhandler$??1type_2220E0@@UAE@XZ @ 0x003089B4
type_2220E0::~type_2220E0()
{
}

// match: ?sub_222270@type_2220E0@@QAEXXZ @ 0x00222270
void type_2220E0::sub_222270()
{
    sub_1C4C80(1, unk_16C.sub_1FD030());
    // A compiled-out check on the pause menu (it shifts the registers).
    if (!unk_130)
    {
    }
    if (unk_130)
        unk_130->sub_21C200(0, 0);
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_2220E0@@@kujuUI@@QAE@PAUtype_2220E0@@P82@AEXXZ@Z @ 0x002222C0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_2220E0@@@kujuUI@@UAEPAXI@Z @ 0x00222320
// match: ??1?$type_3E7CE8@Utype_2220E0@@@kujuUI@@UAE@XZ @ 0x00222300
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_2220E0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_2220E0::sub_1E41C0()
{
}
