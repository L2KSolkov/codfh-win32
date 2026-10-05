/*
 * The Live menus' base (game/livemenu.h): built over a layout with its
 * objects by name and the "LiveMenu" action, loaded to the end on demand.
 */
#include "game/livemenu.h"
#include "game/frontend.h"
#include "types/cXboxLive.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E92D4
extern const RwReal flt_3E92D4 = 0.01f;
// 0x003E92D8
extern const RwReal flt_3E92D8 = 0.01f;
// 0x003E92DC
extern const RwReal flt_3E92DC = 16.666666f;
// 0x003E92E0
extern const RwReal flt_3E92E0 = 0.01f;
// 0x003E92E4
extern const RwReal flt_3E92E4 = 0.01f;
// 0x003E92E8
extern const RwReal flt_3E92E8 = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// The async loader's work suspended (types/asynchload.h; its Windows
// headers clash with the Live types').
void sub_822A0();

// The page's deleting destructor, its objects' map's destructor (an
// inline copy, for the constructor's unwinding) and the action's members.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E92D4@@3MB @ 0x003E92D4
// match: ?flt_3E92D8@@3MB @ 0x003E92D8
// match: ?flt_3E92DC@@3MB @ 0x003E92DC
// match: ?flt_3E92E0@@3MB @ 0x003E92E0
// match: ?flt_3E92E4@@3MB @ 0x003E92E4
// match: ?flt_3E92E8@@3MB @ 0x003E92E8
// match: ??_C@_08IFOPCLHK@LiveMenu?$AA@ @ 0x003E92EC
// match: ??_7type_20E850@@6B@ @ 0x003E92F8
// match: ??_7?$type_3E7CE8@Utype_20E850@@@kujuUI@@6B@ @ 0x003E9334
// match: __ehhandler$??0type_20E850@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z>1>8 @ 0x004236A8
// match: __ehhandler$??0type_20E850@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z>1 @ 0x004236C0
// match: __ehhandler$??1type_20E850@@UAE@XZ>1>8 @ 0x004236DC
// match: __ehhandler$??1type_20E850@@UAE@XZ>1 @ 0x004236EC

// match: ??_Gtype_20E850@@UAEPAXI@Z @ 0x0020E910
// match: ??1?$type_1EFCF0@Utype_3E70B0@kujuUI@@@kujuUI@@QAE@XZ @ 0x0020E940
// match: ??0?$type_3E7CE8@Utype_20E850@@@kujuUI@@QAE@PAUtype_20E850@@P82@AEXXZ@Z @ 0x0020EAA0
// match: ??1?$type_3E7CE8@Utype_20E850@@@kujuUI@@UAE@XZ @ 0x0020EAE0
// match: ??_G?$type_3E7CE8@Utype_20E850@@@kujuUI@@UAEPAXI@Z @ 0x0020EB00
// match: ??0type_20E850@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z @ 0x0020E850
// match: __ehhandler$??0type_20E850@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z-0x24 @ 0x00306830
// match: __ehhandler$??0type_20E850@@QAE@PBDPAU?$type_1EFCF0@PAUtype_3E7D08@kujuUI@@@kujuUI@@@Z @ 0x00306854

type_20E850::type_20E850(const RwChar *arg_0, type_1EFCF0<type_3E7D08 *> *arg_4) : unk_124(this, &type_20E850::sub_20EA00)
{
    if (*arg_0)
        sub_1F44C0(arg_0, (type_1ED670 *)&unk_118, arg_4);
    sub_204FC0("LiveMenu", &unk_124);
}

// match: ??1type_20E850@@UAE@XZ @ 0x0020E960
// match: __ehhandler$??1type_20E850@@UAE@XZ-0x16 @ 0x00306860
// match: __ehhandler$??1type_20E850@@UAE@XZ @ 0x00306876
type_20E850::~type_20E850()
{
}

// match: ?vf_014@type_20E850@@UAEXM@Z @ 0x0020E9E0
void type_20E850::vf_014(RwReal arg_0)
{
    cLayoutPage::vf_014(arg_0);
}

// match: ?sub_20EA00@type_20E850@@QAEXXZ @ 0x0020EA00
void type_20E850::sub_20EA00()
{
    if (sub_1D8810()->get_unk_2918() == 4)
        ((type_2049D0 *)sub_20A540())->sub_20A520();
}

// match: ?sub_20EA40@type_20E850@@QAEXXZ @ 0x0020EA40
void type_20E850::sub_20EA40()
{
    bool var_1 = true;

    while (sub_15FC40() != 0 && sub_15FC40() != 5 && sub_15FC40() != 6)
    {
        if (var_1)
        {
            var_1 = false;
            sub_822A0();
        }
        sub_1F4450();
    }
}

// The "LiveMenu" action's instance (game/kujuui.h's template, its
// definitions repeated here).
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
