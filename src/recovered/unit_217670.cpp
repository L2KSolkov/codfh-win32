/*
 * The two-prompt dialog (game/ingamepages.h): a title, a prompt and two
 * options (and "Back") running the caller's actions, one instance shown
 * and hidden over the pad's widget stack.
 */
#include "game/ingamepages.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x005051D4
type_217670 *dword_5051D4;
// End of its data definitions.


using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0CE@DFBDEHFK@GenericTwoPromptIngameScreen?4lay@ @ 0x003E9998
// match: ??_C@_0BO@GCFMABNH@GenericTwoPromptScreen?4layout?$AA@ @ 0x003E99BC
// match: ??_C@_07EOOFCPBJ@Option2?$AA@ @ 0x003E99DC
// match: ??_C@_07GFMIHMNK@Option1?$AA@ @ 0x003E99E4
// match: ??_C@_0M@HMLHJJNG@Option2Text?$AA@ @ 0x003E99EC
// match: ??_C@_0M@PKCDOLHI@Option1Text?$AA@ @ 0x003E99F8
// match: ??_C@_06MKCAHOBM@Prompt?$AA@ @ 0x003E9A04
// match: ??_7type_217670@@6B@ @ 0x003E9A0C
// match: ??_7?$type_3E7264@Utype_217670@@@kujuUI@@6B@ @ 0x003E9A48
// match: __ehhandler$?sub_2173A0@@YAXXZ>1>8 @ 0x0042455C
// match: __ehhandler$?sub_2173A0@@YAXXZ>1 @ 0x00424564
// match: __ehhandler$?sub_2172F0@@YAXXZ>1>8 @ 0x00424580
// match: __ehhandler$?sub_2172F0@@YAXXZ>1 @ 0x00424588
// match: __ehhandler$??0type_217670@@QAE@PBD@Z>1>8 @ 0x004245A4
// match: __ehhandler$??0type_217670@@QAE@PBD@Z>1 @ 0x004245E4
// match: __ehhandler$??1type_217670@@UAE@XZ>1>8 @ 0x00424600
// match: __ehhandler$??1type_217670@@UAE@XZ>1 @ 0x00424638

// match: ?sub_2171F0@@YAXABUtype_1A5EA0@@00PAUtype_1ED670_object@kujuUI@@011@Z @ 0x002171F0

void sub_2171F0(const type_1A5EA0 &arg_0, const type_1A5EA0 &arg_4, const type_1A5EA0 &arg_8, type_1ED670_object *arg_C,
                const type_1A5EA0 &arg_10, type_1ED670_object *arg_14, type_1ED670_object *arg_18)
{
    dword_5051D4->unk_200 = arg_C;
    dword_5051D4->unk_204 = arg_14;
    dword_5051D4->unk_208 = arg_18;
    if (!dword_5051D4->sub_1F4790(arg_0))
        dword_5051D4->unk_160.sub_1F28C0(arg_0);
    dword_5051D4->unk_188.sub_1F28C0(arg_4);
    dword_5051D4->unk_1B0.sub_1F28C0(arg_8);
    dword_5051D4->unk_1D8.sub_1F28C0(arg_10);
    sub_1E7CF0()->sub_1E7D30(dword_5051D4);
}

// match: ?sub_2172A0@@YA_NXZ @ 0x002172A0
bool sub_2172A0()
{
    type_1E7CF0 *var_4 = sub_1E7CF0();

    if (dword_5051D4 && var_4->sub_1E7D00(dword_5051D4))
    {
        var_4->sub_1E7D90(dword_5051D4);
        return true;
    }
    return false;
}

// match: ?sub_2172F0@@YAXXZ @ 0x002172F0
// match: __ehhandler$?sub_2172F0@@YAXXZ-0xB @ 0x00307370
// match: __ehhandler$?sub_2172F0@@YAXXZ @ 0x0030737B
void sub_2172F0()
{
    delete dword_5051D4;
    dword_5051D4 = new type_217670("GenericTwoPromptIngameScreen.layout");
}

// match: ?sub_2173A0@@YAXXZ @ 0x002173A0
void sub_2173A0()
{
    delete dword_5051D4;
    dword_5051D4 = new type_217670("GenericTwoPromptScreen.layout");
}

// match: ?sub_217450@@YAXXZ @ 0x00217450
void sub_217450()
{
    delete dword_5051D4;
    dword_5051D4 = 0;
}

// match: ?sub_217490@type_217670@@QAEXXZ @ 0x00217490
void type_217670::sub_217490()
{
    sub_1E7CF0()->sub_1E7D90(dword_5051D4);
    unk_200->pvf_008();
}

// match: ?sub_2174D0@type_217670@@QAE_NXZ @ 0x002174D0
bool type_217670::sub_2174D0()
{
    return unk_200->pvf_00C();
}

// match: ?sub_217500@type_217670@@QAEXXZ @ 0x00217500
void type_217670::sub_217500()
{
    sub_1E7CF0()->sub_1E7D90(dword_5051D4);
    unk_204->pvf_008();
}

// match: ?sub_217540@type_217670@@QAE_NXZ @ 0x00217540
bool type_217670::sub_217540()
{
    return unk_204->pvf_00C();
}

// match: ?sub_217570@type_217670@@QAEXXZ @ 0x00217570
void type_217670::sub_217570()
{
    if (unk_208)
    {
        sub_1E7CF0()->sub_1E7D90(dword_5051D4);
        unk_208->pvf_008();
    }
}

// match: ?sub_2175C0@type_217670@@QAE_NXZ @ 0x002175C0
bool type_217670::sub_2175C0()
{
    return unk_208 && unk_208->pvf_00C();
}

// match: ?vf_024@type_217670@@UAEHXZ @ 0x00217610
RwInt32 type_217670::vf_024()
{
    RwInt32 var_4 = 2;

    if (sub_2175C0())
        var_4 |= 8;
    if (sub_2174D0() && sub_217540())
        var_4 |= 0x10;
    return var_4;
}

// match: ??0type_217670@@QAE@PBD@Z @ 0x00217670
// match: __ehhandler$??0type_217670@@QAE@PBD@Z-0x6A @ 0x00307390
// match: __ehhandler$??0type_217670@@QAE@PBD@Z @ 0x003073FA
type_217670::type_217670(const RwChar *arg_0)
    : type_20E850(arg_0, 0), unk_130(this, &type_217670::sub_217490, &type_217670::sub_2174D0),
      unk_140(this, &type_217670::sub_217500, &type_217670::sub_217540),
      unk_150(this, &type_217670::sub_217570, &type_217670::sub_2175C0), unk_200(0), unk_204(0), unk_208(0)
{
    sub_204FC0("Title", &unk_160);
    sub_204FC0("Prompt", &unk_188);
    sub_204FC0("Option1Text", &unk_1B0);
    sub_204FC0("Option2Text", &unk_1D8);
    sub_204FC0("Option1", &unk_130);
    sub_204FC0("Option2", &unk_140);
    sub_204FC0("Back", &unk_150);
    sub_20EA40();
}

// match: ??_Gtype_217670@@UAEPAXI@Z @ 0x00217840
// match: ??1type_217670@@UAE@XZ @ 0x00217870
// match: __ehhandler$??1type_217670@@UAE@XZ-0x5C @ 0x00307410
// match: __ehhandler$??1type_217670@@UAE@XZ @ 0x0030746C
type_217670::~type_217670()
{
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7264@Utype_217670@@@kujuUI@@QAE@PAUtype_217670@@P82@AEXXZP82@AE_NXZ@Z @ 0x00217940
template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ??_G?$type_3E7264@Utype_217670@@@kujuUI@@UAEPAXI@Z @ 0x002179B0
// match: ??1?$type_3E7264@Utype_217670@@@kujuUI@@UAE@XZ @ 0x00217990
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
