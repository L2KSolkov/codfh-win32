/*
 * A scoreboard (game/ingamepages.h): the scoreboards' base with its options
 * page shown, updated, drawn and given the pad's events first, and
 * "continue" leaving the front end's screens.
 */
#include "game/ingamepages.h"
#include "game/data.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EA704
extern const RwReal flt_3EA704 = 0.01f;
// 0x003EA708
extern const RwReal flt_3EA708 = 0.01f;
// 0x003EA70C
extern const RwReal flt_3EA70C = 16.666666f;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3EA704@@3MB @ 0x003EA704
// match: ?flt_3EA708@@3MB @ 0x003EA708
// match: ?flt_3EA70C@@3MB @ 0x003EA70C
// match: ??_7type_2207A0@@6B@ @ 0x003EA710
// match: ??_7?$type_3E7CE8@Utype_2207A0@@@kujuUI@@6B@ @ 0x003EA760
// match: __ehhandler$??0type_2207A0@@QAE@HPBD0PAUtype_21A5E0@@@Z>1>8 @ 0x004256F4
// match: __ehhandler$??0type_2207A0@@QAE@HPBD0PAUtype_21A5E0@@@Z>1 @ 0x0042570C
// match: __ehhandler$??1type_2207A0@@UAE@XZ>1>8 @ 0x00425728
// match: __ehhandler$??1type_2207A0@@UAE@XZ>1 @ 0x00425738

// match: ??0type_2207A0@@QAE@HPBD0PAUtype_21A5E0@@@Z @ 0x002207A0
// match: __ehhandler$??0type_2207A0@@QAE@HPBD0PAUtype_21A5E0@@@Z-0x21 @ 0x00308660
// match: __ehhandler$??0type_2207A0@@QAE@HPBD0PAUtype_21A5E0@@@Z @ 0x00308681

type_2207A0::type_2207A0(RwInt32 arg_0, const RwChar *arg_4, const RwChar *arg_8, type_21A5E0 *arg_C)
    : type_21EB30(dword_4FB9E0.get_unk_08() != 1, arg_0, arg_4, arg_C), unk_3A8(this, &type_2207A0::sub_220A80),
      unk_3B4(0)
{
    sub_204FC0("continue", &unk_3A8);
    if (arg_8)
    {
        unk_3B4 = new type_21DFE0(arg_0, arg_8, arg_C);
        unk_3B4->sub_20EA40();
    }
    sub_20EA40();
}

// match: ??_Gtype_2207A0@@UAEPAXI@Z @ 0x002208C0
// match: ??1type_2207A0@@UAE@XZ @ 0x002208F0
// match: __ehhandler$??1type_2207A0@@UAE@XZ-0x16 @ 0x00308690
// match: __ehhandler$??1type_2207A0@@UAE@XZ @ 0x003086A6
type_2207A0::~type_2207A0()
{
    delete unk_3B4;
}

// match: ?vf_018@type_2207A0@@UAEXPAUtype_1E4130@kujuUI@@@Z @ 0x00220980
void type_2207A0::vf_018(type_1E4130 *arg_0)
{
    type_21EB30::vf_018(arg_0);
    if (unk_3B4)
        unk_3B4->vf_018(arg_0);
}

// match: ?processEvent@type_2207A0@@UAE?AW4eEventWasHandled@kujuUI@@ABVcStateChange@3@@Z @ 0x002209D0
eEventWasHandled type_2207A0::processEvent(const cStateChange &arg_0)
{
    eEventWasHandled var_4 = (eEventWasHandled)1;

    if (unk_3B4)
    {
        var_4 = unk_3B4->processEvent(arg_0);
        if (var_4 == 0)
            return var_4;
    }
    return cTopLayoutPage::processEvent(arg_0);
}

// match: ?vf_014@type_2207A0@@UAEXM@Z @ 0x00220A30
void type_2207A0::vf_014(RwReal arg_0)
{
    type_21EB30::vf_014(arg_0);
    if (unk_3B4)
        unk_3B4->vf_014(arg_0);
}

// match: ?sub_220A80@type_2207A0@@QAEXXZ @ 0x00220A80
void type_2207A0::sub_220A80()
{
    sub_1C4B10();
}

// match: ?vf_008@type_2207A0@@UAEXXZ @ 0x00220A90
void type_2207A0::vf_008()
{
    type_21EB30::vf_008();
    if (unk_3B4)
    {
        unk_3B4->sub_21E3B0();
        unk_3B4->vf_008();
        unk_3B4->sub_1F7790();
    }
}

// match: ?vf_00C@type_2207A0@@UAEXXZ @ 0x00220AF0
void type_2207A0::vf_00C()
{
    if (unk_3B4)
    {
        unk_3B4->sub_1F77B0();
        unk_3B4->vf_00C();
    }
    type_21EB30::vf_00C();
}

// match: ?vf_04C@type_2207A0@@UAEXXZ @ 0x00220B40
void type_2207A0::vf_04C()
{
    if (unk_3B4)
        unk_3B4->vf_04C();
}

// match: ?vf_024@type_2207A0@@UAEHXZ @ 0x00220B70
RwInt32 type_2207A0::vf_024()
{
    if (unk_3B4)
        return unk_3B4->vf_024();
    return 0;
}

// The action's members (game/kujuui.h's template, its definitions repeated
// here).
// match: ??0?$type_3E7CE8@Utype_2207A0@@@kujuUI@@QAE@PAUtype_2207A0@@P82@AEXXZ@Z @ 0x00220BB0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_2207A0@@@kujuUI@@UAEPAXI@Z @ 0x00220C10
// match: ??1?$type_3E7CE8@Utype_2207A0@@@kujuUI@@UAE@XZ @ 0x00220BF0
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}
