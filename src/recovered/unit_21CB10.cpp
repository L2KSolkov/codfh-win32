/*
 * The in-game pages' base (game/ingamepages.h): a Live menus' page over a
 * layout with "Back" and "Options" into the pause menu, and whether it is
 * shown.
 */
#include "game/ingamepages.h"
#include "game/data.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003EA338
extern const RwReal flt_3EA338 = 16.666666f;
// 0x003EA33C
extern const RwReal flt_3EA33C = 0.01f;
// 0x003EA340
extern const RwReal flt_3EA340 = 0.01f;
// 0x003EA344
extern const RwReal flt_3EA344 = 0.0f;
#endif
// End of its data definitions.


using namespace kujuUI;

// The actions' targets: the compiler's thunks calling slots 16 and 17.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA338@@3MB @ 0x003EA338
// match: ?flt_3EA33C@@3MB @ 0x003EA33C
// match: ?flt_3EA340@@3MB @ 0x003EA340
// match: ?flt_3EA344@@3MB @ 0x003EA344
// match: ??_7type_21CB10@@6B@ @ 0x003EA348
// match: ??_7?$type_3E7CE8@Utype_21CB10@@@kujuUI@@6B@ @ 0x003EA398
// match: __ehhandler$??0type_21CB10@@QAE@PBDPAUtype_21A5E0@@PAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z>1>8 @ 0x00424F58
// match: __ehhandler$??0type_21CB10@@QAE@PBDPAUtype_21A5E0@@PAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z>1 @ 0x00424F70
// match: __ehhandler$??1type_21CB10@@UAE@XZ>1>8 @ 0x00424F8C
// match: __ehhandler$??1type_21CB10@@UAE@XZ>1 @ 0x00424F9C

// match: ??_9@$BEA@AE @ 0x0021CE40
// match: ??_9@$BEE@AE @ 0x0021CE50
// match: ??0type_21CB10@@QAE@PBDPAUtype_21A5E0@@PAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z @ 0x0021CB10
// match: __ehhandler$??0type_21CB10@@QAE@PBDPAUtype_21A5E0@@PAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z-0x24 @ 0x00307E70
// match: __ehhandler$??0type_21CB10@@QAE@PBDPAUtype_21A5E0@@PAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z @ 0x00307E94

type_21CB10::type_21CB10(const RwChar *arg_0, type_21A5E0 *arg_4, type_1EFCF0<type_3E7D08 *> *arg_8)
    : type_20E850(arg_0, arg_8), unk_130(arg_4), unk_134(-1), unk_138(this, &type_21CB10::vf_040),
      unk_144(this, &type_21CB10::vf_044), unk_150(false)
{
    sub_204FC0("Back", &unk_138);
    sub_204FC0("Options", &unk_144);
}

// match: ??_Gtype_21CB10@@UAEPAXI@Z @ 0x0021CBF0
// match: ??1type_21CB10@@UAE@XZ @ 0x0021CC20
// match: __ehhandler$??1type_21CB10@@UAE@XZ-0x16 @ 0x00307EA0
// match: __ehhandler$??1type_21CB10@@UAE@XZ @ 0x00307EB6
type_21CB10::~type_21CB10()
{
}

// match: ?vf_040@type_21CB10@@UAEXXZ @ 0x0021CC90
void type_21CB10::vf_040()
{
    if (unk_130)
    {
        RwInt32 var_4 = unk_134;

        unk_130->sub_21C200(var_4, 0);
    }
}

// match: ?vf_044@type_21CB10@@UAEXXZ @ 0x0021CCD0
void type_21CB10::vf_044()
{
    if (unk_130)
        unk_130->sub_21C200(0x16, unk_130->sub_21ABF0());
}

// match: ?vf_008@type_21CB10@@UAEXXZ @ 0x0021CD10
void type_21CB10::vf_008()
{
    sub_20EA40();
    type_20E850::vf_008();
    unk_150 = true;
    byte_4B8974 = 1;
}

// match: ?vf_00C@type_21CB10@@UAEXXZ @ 0x0021CD40
void type_21CB10::vf_00C()
{
    unk_150 = false;
    if (!dword_4FB9E0.get_unk_0C() || !unk_4F7EB8.get_unk_500())
        byte_4B8974 = 0;
    type_20E850::vf_00C();
}

// match: ?vf_048@type_21CB10@@UAE_NXZ @ 0x0021CD90
bool type_21CB10::vf_048()
{
    return unk_150;
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_21CB10@@@kujuUI@@QAE@PAUtype_21CB10@@P82@AEXXZ@Z @ 0x0021CDB0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_21CB10@@@kujuUI@@UAEPAXI@Z @ 0x0021CE10
// match: ??1?$type_3E7CE8@Utype_21CB10@@@kujuUI@@UAE@XZ @ 0x0021CDF0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_03C@type_21CB10@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_21CB10::vf_03C()
{
}

// ?vf_04C@type_21CB10@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_21CB10::vf_04C()
{
}
