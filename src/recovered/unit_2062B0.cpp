/*
 * The find session page (in-game menu 1, game/livemenu.h): its search
 * settings reset, the search started with them, and the minimum players
 * kept below the players picked.
 */
#include "game/livemenu.h"
#include "game/ingamemenu.h"
#include "game/kujuui.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E876C
extern const RwReal flt_3E876C = 0.01f;
// 0x003E8770
extern const RwReal flt_3E8770 = 0.01f;
// 0x003E8774
extern const RwReal flt_3E8774 = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// The actions' destructors.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$??1_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE@XZ>1 @ 0x00422A9C
// match: __ehhandler$??1_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE@XZ>1>8 @ 0x00422A94
// match: ?flt_3E876C@@3MB @ 0x003E876C
// match: ?flt_3E8770@@3MB @ 0x003E8770
// match: ?flt_3E8774@@3MB @ 0x003E8774
// match: ??_C@_0M@BNCCBCJC@TeamBalance?$AA@ @ 0x003E8778
// match: ??_C@_0M@BFLNJOGP@GameSubtype?$AA@ @ 0x003E8784
// match: ??_C@_08JKMDOHNJ@GameType?$AA@ @ 0x003E8790
// match: ??_C@_0L@EBDCHFFL@MinPlayers?$AA@ @ 0x003E879C
// match: ??_C@_0O@CLBJKGMG@ResetSettings?$AA@ @ 0x003E87A8
// match: ??_C@_04OLJIFFAL@Find?$AA@ @ 0x003E87B8
// match: ??_7type_2062B0@@6B@ @ 0x003E87C0
// match: ??_C@_0BD@IEFCBHBB@FindSession?4layout?$AA@ @ 0x003E8804
// match: ??_7?$type_3E7CE8@Utype_2062B0@@@kujuUI@@6B@ @ 0x003E8818
// match: __ehhandler$??0type_2062B0@@QAE@XZ>1>8 @ 0x00422928
// match: __ehhandler$??0type_2062B0@@QAE@XZ>1 @ 0x004229C8
// match: __ehhandler$??1type_2062B0@@UAE@XZ>1>8 @ 0x004229E4
// match: __ehhandler$??1type_2062B0@@UAE@XZ>1 @ 0x00422A4C
// match: __ehhandler$?sub_206850@type_2062B0@@QAEXXZ>1>8 @ 0x00422A68
// match: __ehhandler$?sub_206850@type_2062B0@@QAEXXZ>1 @ 0x00422A78

// match: ??0?$type_3E7CE8@Utype_2062B0@@@kujuUI@@QAE@PAUtype_2062B0@@P82@AEXXZ@Z @ 0x00206B50
// match: ??1?$type_3E7CE8@Utype_2062B0@@@kujuUI@@UAE@XZ @ 0x00206B90
// match: ??_G?$type_3E7CE8@Utype_2062B0@@@kujuUI@@UAEPAXI@Z @ 0x00206BB0
// match: ??0type_2062B0@@QAE@XZ @ 0x002062B0
// match: __ehhandler$??0type_2062B0@@QAE@XZ-0x100 @ 0x00305910
// match: __ehhandler$??0type_2062B0@@QAE@XZ @ 0x00305A10

type_2062B0::type_2062B0()
    : type_2049D0("FindSession.layout", &unk_304, true), unk_188(0),
      unk_18C(this, &type_2062B0::sub_206960), unk_198(this, &type_2062B0::sub_206FC0),
      unk_1A4(this, &type_2062B0::sub_206850), unk_1B0(this, &type_2062B0::sub_206AE0),
      unk_1BC(this, &type_2062B0::sub_1E41C0), unk_1C8(1, 0), unk_1E8(1, 0), unk_208(1, &unk_1B0),
      unk_228(0, 0, 15, 1, 2, 2, 0, type_1CB670("Any", 0), sub_1CB720(""), sub_1CB720(""), &unk_1BC),
      unk_2A4(1, (type_214C30_value)2, 0), unk_2C4(1, (type_214C30_value)2, 0), unk_2E4(1, (type_214C30_value)2, 0)
{
    sub_204FC0("Find", &unk_18C);
    sub_204FC0("ResetSettings", &unk_1A4);
    sub_204FC0("MaxPlayers", &unk_208);
    sub_204FC0("MinPlayers", &unk_228);
    sub_204FC0("Level", &unk_1E8);
    sub_204FC0("GameType", &unk_1C8);
    sub_204FC0("GameSubtype", &unk_2A4);
    sub_204FC0("TeamBalance", &unk_2C4);
    sub_204FC0("FriendlyFire", &unk_2E4);
    sub_204FC0("Back", &unk_198);
    unk_188 = 1;
}

// match: ??_Gtype_2062B0@@UAEPAXI@Z @ 0x002066B0
// match: ??1type_2062B0@@UAE@XZ @ 0x002066E0
// match: __ehhandler$??1type_2062B0@@UAE@XZ-0xB0 @ 0x00305A20
// match: __ehhandler$??1type_2062B0@@UAE@XZ @ 0x00305AD0
type_2062B0::~type_2062B0()
{
}

// match: ?vf_03C@type_2062B0@@UAEXXZ @ 0x00206830
void type_2062B0::vf_03C()
{
    type_2049D0::vf_03C();
    sub_206850();
}

// Resets the search settings (the "ResetSettings" action, also run when the
// page is shown): any level, game type 0x20, 8 players, a minimum of 0 and
// the subtype, team balance and friendly fire at 2 (any).
// match: ?sub_206850@type_2062B0@@QAEXXZ @ 0x00206850
// match: __ehhandler$?sub_206850@type_2062B0@@QAEXXZ-0x10 @ 0x00305AE0
// match: __ehhandler$?sub_206850@type_2062B0@@QAEXXZ @ 0x00305AF0
void type_2062B0::sub_206850()
{
    type_505188 lv_54;
    type_211860_key lv_10(&lv_54);

    unk_1E8.sub_201EC0(lv_10);
    unk_1C8.sub_201EC0((type_210430_value)0x20);
    unk_208.sub_201EC0((type_2138C0_value)8);
    unk_228.sub_1E7BB0(0);
    unk_2A4.sub_201EC0((type_214C30_value)2);
    unk_2C4.sub_201EC0((type_214C30_value)2);
    unk_2E4.sub_201EC0((type_214C30_value)2);
}

// match: ?sub_206960@type_2062B0@@QAEXXZ @ 0x00206960
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_2062B0::sub_206960()
{
    type_505188 *l4 = unk_1E8.sub_1FD030().get_unk_00();

    sub_1C3D80(l4->sub_1A5FF0() ? -1 : ((kujuUI::type_1EE900 *)l4)->sub_1EE9D0());
    unk_4FDBB0.unk_00 = unk_1C8.get_value();
    dword_4F6300 = unk_208.get_value();
    dword_4FDAA0 = unk_228.get_unk_08();
    RwInt32 var_10 = 4;
    RwInt32 frm_8 = unk_2A4.sub_1FD030();
    if (frm_8 == 1)
        var_10 = 2;
    else if (frm_8 == 0)
        var_10 = 0;
    dword_42CBA8 = var_10;
    RwInt32 lv_14 = 4;
    frm_8 = unk_2C4.sub_1FD030();
    if (frm_8 == 1)
        lv_14 = 2;
    else if (frm_8 == 0)
        lv_14 = 1;
    dword_42CBAC = lv_14;
    RwInt32 qC = 4;
    frm_8 = unk_2E4.sub_1FD030();
    if (frm_8 == 1)
        qC = 2;
    else if (frm_8 == 0)
        qC = 1;
    dword_42CBB0 = qC;
    sub_1FC310()->sub_1FBDA0(sub_2046C0(7));
}

// match: ?sub_206AE0@type_2062B0@@QAEXXZ @ 0x00206AE0
void type_2062B0::sub_206AE0()
{
    if (unk_188)
    {
        RwInt32 var_4;

        switch (unk_208.sub_1FD030())
        {
        case 1:
            var_4 = 4;
            break;
        case 2:
            var_4 = 8;
            break;
        default:
            var_4 = 0x10;
        }
        unk_228.sub_1E7BD0(var_4 - 1);
    }
}

// The actions' instance (game/kujuui.h's template, its definitions repeated
// here).
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

// The page's action (its constructor is out of line: the page's constructor
// builds it).
template struct kujuUI::type_3E7CE8<type_2062B0>;

// The key map's clear, erase and node destructor, which the stand-in below instantiates.
// match: ?clear@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x00206BE0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x00206C40
// match: ??1_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE@XZ @ 0x00206CB0
// match: __ehhandler$??1_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE@XZ-0x8 @ 0x00305B00
// match: __ehhandler$??1_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE@XZ @ 0x00305B08

// Not in the image: a stand-in for a function the original object held about here, which
// nothing called, so the link's /OPT:REF dropped it. It was the first to clear the level
// selector's key map (unk_1E8): the image has that map's clear (folded into 0x206BE0), _Erase
// (0x206C40) and node destructor (0x206CB0, its EH thunk at 0x305B08) among this object's,
// though their first surviving users are in unit_211680. Its body is unknown: this one only
// clears the map.
void dropped_206C40(type_2062B0 *arg_0)
{
    arg_0->unk_1E8.unk_08.clear();
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_2062B0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_2062B0::sub_1E41C0()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_206FC0@type_2062B0@@QAEXXZ (folded into 0x206FC0)
void type_2062B0::sub_206FC0()
{
    sub_1FC310()->sub_1FBDA0(sub_2046C0(6));
}
