/*
 * The vote over the level (game/ingamepages.h): the level picked and
 * "confirm" calling the vote.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"
#include "game/kujuui.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003EA9B0
extern const RwReal flt_3EA9B0 = 0.01f;
// 0x003EA9B4
extern const RwReal flt_3EA9B4 = 0.01f;
// 0x003EA9B8
extern const RwReal flt_3EA9B8 = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA9B0@@3MB @ 0x003EA9B0
// match: ?flt_3EA9B4@@3MB @ 0x003EA9B4
// match: ?flt_3EA9B8@@3MB @ 0x003EA9B8
// match: ??_7type_222350@@6B@ @ 0x003EA9C0
// match: ??_7?$type_3E7CE8@Utype_222350@@@kujuUI@@6B@ @ 0x003EAA10
// match: __ehhandler$??0type_222350@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x00425A0C
// match: __ehhandler$??0type_222350@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x00425A2C
// match: __ehhandler$??1type_222350@@UAE@XZ>1>8 @ 0x00425A48
// match: __ehhandler$??1type_222350@@UAE@XZ>1 @ 0x00425A60

// match: ??0type_222350@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x00222350
// match: __ehhandler$??0type_222350@@QAE@PBDPAUtype_21A5E0@@@Z-0x32 @ 0x003089C0
// match: __ehhandler$??0type_222350@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x003089F2

type_222350::type_222350(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), unk_154(this, &type_222350::sub_1E41C0), unk_160(this, &type_222350::sub_2224E0),
      unk_16C(0, &unk_154)
{
    sub_204FC0("Level", &unk_16C);
    sub_204FC0("confirm", &unk_160);
}

// match: ??_Gtype_222350@@UAEPAXI@Z @ 0x00222430
// match: ??1type_222350@@UAE@XZ @ 0x00222460
// match: __ehhandler$??1type_222350@@UAE@XZ-0x24 @ 0x00308A00
// match: __ehhandler$??1type_222350@@UAE@XZ @ 0x00308A24
type_222350::~type_222350()
{
}

// match: ?sub_2224E0@type_222350@@QAEXXZ @ 0x002224E0
void type_222350::sub_2224E0()
{
    sub_1C4C80(0, ((kujuUI::type_1EE900 *)unk_16C.sub_1FD030().get_unk_00())->sub_1EE9D0());
    // A compiled-out check on the pause menu (it shifts the registers).
    if (!unk_130)
    {
    }
    if (unk_130)
        unk_130->sub_21C200(0, 0);
}

// match: ?vf_024@type_222350@@UAEHXZ @ 0x00222540

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_222350@@@kujuUI@@QAE@PAUtype_222350@@P82@AEXXZ@Z @ 0x00222550
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_222350@@@kujuUI@@UAEPAXI@Z @ 0x002225B0
// match: ??1?$type_3E7CE8@Utype_222350@@@kujuUI@@UAE@XZ @ 0x00222590
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_222350@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_222350::sub_1E41C0()
{
}
