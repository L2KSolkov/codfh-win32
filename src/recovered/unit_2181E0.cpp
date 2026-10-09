/*
 * The kick page (game/ingamepages.h): the other players listed by name, the
 * one picked kicked after a confirmation.
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E9BF8
extern const RwReal flt_3E9BF8 = 0.01f;
// 0x003E9BFC
extern const RwReal flt_3E9BFC = 0.01f;
// 0x003E9C00
extern const RwReal flt_3E9C00 = 16.666666f;
#endif
// End of its data definitions.


using namespace kujuUI;

// The rows' list's members (std::list<type_21CE60 *>).
// The rows' list's size check (std::list's, throwing length_error).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E9BF8@@3MB @ 0x003E9BF8
// match: ?flt_3E9BFC@@3MB @ 0x003E9BFC
// match: ?flt_3E9C00@@3MB @ 0x003E9C00
// match: ??_C@_0BC@BCIHPONB@KickPlayerConfirm?$AA@ @ 0x003E9C04
// match: ??_C@_0BJ@DGFGHKKG@KickPlayerConfirm?4layout?$AA@ @ 0x003E9C18
// match: ??_7type_2181E0@@6Btype_218B80@@@ @ 0x003E9C34
// match: ??_7type_2181E0@@6Btype_21CB10@@@ @ 0x003E9C50
// match: ??_7type_218B80@@6B@ @ 0x003E9CA0
// match: ??_7?$type_3E7CE8@Utype_2181E0@@@kujuUI@@6B@ @ 0x003E9CBC
// match: __ehhandler$??0type_2181E0@@QAE@PBDPAUtype_21A5E0@@@Z>1>8 @ 0x0042476C
// match: __ehhandler$??0type_2181E0@@QAE@PBDPAUtype_21A5E0@@@Z>1 @ 0x004247A4
// match: __ehhandler$??1type_2181E0@@UAE@XZ>1>8 @ 0x004247C0
// match: __ehhandler$??1type_2181E0@@UAE@XZ>1 @ 0x004247F8
// match: __ehhandler$?sub_2184D0@type_2181E0@@QAEXXZ>1>8 @ 0x00424814
// match: __ehhandler$?sub_2184D0@type_2181E0@@QAEXXZ>1 @ 0x0042481C
// match: __ehhandler$?pvf_010@type_2181E0@@UAEXXZ>1>8 @ 0x00424838
// match: __ehhandler$?pvf_010@type_2181E0@@UAEXXZ>1 @ 0x00424850
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@XZ>1>8 @ 0x0042486C
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@XZ>1>16>16 @ 0x0042487C
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@XZ>1>16 @ 0x0042488C
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@XZ>1 @ 0x004248A0
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@PAU342@0ABQAUtype_21CE60@@@Z>1>8 @ 0x004248BC
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@PAU342@0ABQAUtype_21CE60@@@Z>1>16>16 @ 0x004248CC
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@PAU342@0ABQAUtype_21CE60@@@Z>1>16 @ 0x004248DC
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@PAU342@0ABQAUtype_21CE60@@@Z>1 @ 0x004248F0
// match: __ehhandler$?_Incsize@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEXI@Z>1>8 @ 0x0042490C
// match: __ehhandler$?_Incsize@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEXI@Z>1 @ 0x00424914

// match: ?_Incsize@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEXI@Z @ 0x00218AB0
// match: __ehhandler$?_Incsize@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEXI@Z-0x8 @ 0x003076A0
// match: __ehhandler$?_Incsize@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEXI@Z @ 0x003076A8
// match: ?_Insert@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@QAEXViterator@12@ABQAUtype_21CE60@@@Z @ 0x002188B0
// match: ?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@XZ @ 0x00218910
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@XZ @ 0x00307680
// match: ?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@PAU342@0ABQAUtype_21CE60@@@Z @ 0x002189F0
// match: __ehhandler$?_Buynode@?$list@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21CE60@@V?$allocator@PAUtype_21CE60@@@std@@@2@PAU342@0ABQAUtype_21CE60@@@Z @ 0x00307690

// The this-adjusting thunk the columns' vtable (off_3E9C34) holds for the
// deleting destructor.
// match: ??_Etype_2181E0@@WBFE@AEPAXI@Z @ 0x00218DC0

// match: ??0type_2181E0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x002181E0
// match: __ehhandler$??0type_2181E0@@QAE@PBDPAUtype_21A5E0@@@Z-0x5C @ 0x00307540
// match: __ehhandler$??0type_2181E0@@QAE@PBDPAUtype_21A5E0@@@Z @ 0x0030759C
type_2181E0::type_2181E0(const RwChar *arg_0, type_21A5E0 *arg_4)
    : type_21CB10(arg_0, arg_4, 0), type_218B80(1), unk_170("KickPlayerConfirm.layout", 0, false),
      unk_320(this, &type_2181E0::sub_2187B0), unk_330(this, &type_2181E0::sub_2187E0)
{
    sub_204FC0("PlayerList", this);
    unk_170.sub_204FC0("KickPlayerConfirm", &unk_2F8);
    unk_170.sub_204FC0("Yes", &unk_320);
    unk_170.sub_204FC0("No", &unk_330);
}

// match: ??_Gtype_2181E0@@UAEPAXI@Z @ 0x00218390
// match: ??1type_2181E0@@UAE@XZ @ 0x002183C0
// match: __ehhandler$??1type_2181E0@@UAE@XZ-0x77 @ 0x003075B0
// match: __ehhandler$??1type_2181E0@@UAE@XZ @ 0x00307627
type_2181E0::~type_2181E0()
{
    sub_222C70();
}

// match: ?sub_2184D0@type_2181E0@@QAEXXZ @ 0x002184D0
// match: __ehhandler$?sub_2184D0@type_2181E0@@QAEXXZ-0xB @ 0x00307640
// match: __ehhandler$?sub_2184D0@type_2181E0@@QAEXXZ @ 0x0030764B
void type_2181E0::sub_2184D0()
{
    RwInt32 var_18 = 0;

    sub_222C70();
    type_1DDE20_mask lv_10 = sub_1C48A0();
    lv_10.unset(0);
    RwUInt32 var_14;
    for (var_14 = 0; var_14 < 16; var_14++)
    {
        if (lv_10.in(var_14))
        {
            type_21CE60 *var_20;
            RwChar *l1C = sub_1C4630(var_14);

            var_20 = new type_21CE60(var_14, l1C);

            unk_164.push_back(var_20);
            sub_218BB0(var_20);
            var_18++;
        }
    }
    if (var_18 > 0)
        type_1ECA30::sub_1E3480()->sub_1EB0B0(0);
    else
        vf_040();
}

// match: ?vf_038@type_2181E0@@UAEXXZ @ 0x00218680
void type_2181E0::vf_038()
{
    unk_170.sub_20EA40();
}

// match: ?vf_008@type_2181E0@@UAEXXZ @ 0x002186A0
void type_2181E0::vf_008()
{
    type_21CB10::vf_008();
    sub_2184D0();
}

// A player picked: the confirmation names the player and is pushed.
// match: ?pvf_010@type_2181E0@@UAEXXZ @ 0x002186C0
// match: __ehhandler$?pvf_010@type_2181E0@@UAEXXZ-0x10 @ 0x00307660
// match: __ehhandler$?pvf_010@type_2181E0@@UAEXXZ @ 0x00307670
void type_2181E0::pvf_010()
{
    if (sub_1ECB40())
    {
        type_1CB670 lv_2C = sub_1CB720(sub_20E520()->sub_21D050().c_str());
        unk_2F8.sub_1F28C0(lv_2C);
        sub_1E7CF0()->sub_1E7D30(&unk_170);
    }
}

// match: ?sub_2187B0@type_2181E0@@QAEXXZ @ 0x002187B0
void type_2181E0::sub_2187B0()
{
    sub_1E7CF0()->sub_1E7D90(&unk_170);
    sub_218800();
}

// match: ?sub_2187E0@type_2181E0@@QAEXXZ @ 0x002187E0
void type_2181E0::sub_2187E0()
{
    sub_1E7CF0()->sub_1E7D90(&unk_170);
}

// match: ?sub_218800@type_2181E0@@QAEXXZ @ 0x00218800
void type_2181E0::sub_218800()
{
    if (sub_1ECB40())
    {
        type_21CE60 *var_4 = sub_20E520();

        if (var_4)
        {
            type_1DDE20_mask var_8 = sub_1C48A0();

            var_8.reset(0);
            if (var_8.in(var_4->sub_21D030()))
            {
                sub_1C4560(var_4->sub_21D030());
                vf_040();
            }
            else
                sub_2184D0();
        }
    }
}

// match: ??0type_218B80@@QAE@I@Z @ 0x00218B80
type_218B80::type_218B80(RwUInt32 arg_0) : type_1ECA30(arg_0)
{
}

// match: ?sub_218BB0@type_218B80@@QAEHPAUtype_21CE60@@@Z @ 0x00218BB0
RwInt32 type_218B80::sub_218BB0(type_21CE60 *arg_0)
{
    RwInt32 var_4 = sub_218C90(arg_0);

    sub_1E3480()->sub_1EA980(arg_0, var_4);
    return var_4;
}

// The actions' members (game/kujuui.h's template, its definitions
// repeated here).
// match: ??0?$type_3E7CE8@Utype_2181E0@@@kujuUI@@QAE@PAUtype_2181E0@@P82@AEXXZ@Z @ 0x00218BF0
template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

// match: ??_G?$type_3E7CE8@Utype_2181E0@@@kujuUI@@UAEPAXI@Z @ 0x00218C60
// match: ??1?$type_3E7CE8@Utype_2181E0@@@kujuUI@@UAE@XZ @ 0x00218C40
template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

// match: ?sub_218C90@type_218B80@@QAEHPAUtype_21CE60@@@Z @ 0x00218C90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_218B80::sub_218C90(type_21CE60 *arg_0)
{
    bool var_25;
    RwUInt32 var_24;
    type_21CE60 *var_20;
    RwUInt32 l1C;
    bool x15;
    RwInt32 ebp_14;
    std::vector<type_3E74C0 *> *lv_10;
    type_21CE60 *var_C;
    RwUInt32 bp_8;
    RwUInt32 bp_4;

    lv_10 = sub_1E3480()->sub_1EB070();
    if (lv_10->size() == 0)
        return 0;
    bp_4 = 0;
    bp_8 = sub_1E3480()->sub_1EB070()->size();
    l1C = bp_8 - bp_4;
    while (l1C > 1)
    {
        var_24 = (bp_4 + bp_8) / 2;
        var_20 = sub_21DF90(var_24);
        var_25 = arg_0->sub_21D0A0(*var_20);
        if (var_25)
            bp_8 = var_24;
        else
            bp_4 = var_24;
        l1C = bp_8 - bp_4;
    }
    var_C = sub_21DF90(bp_4);
    x15 = var_C->sub_21D0A0(*arg_0);
    ebp_14 = x15 ? bp_4 + 1 : bp_4;
    return ebp_14;
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// The rows' list's insertion, reached through push_back.
#ifndef CODFH_WIN32
// (not on Win32: _Insert is VC7.1's list internals; the port's library has none)
template void std::list<type_21CE60 *>::_Insert(std::list<type_21CE60 *>::iterator, type_21CE60 *const &);
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_00C@type_2181E0@@UAEXXZ (folded into 0x222F20)
void type_2181E0::vf_00C()
{
    if (sub_1E7CF0()->sub_1E7D00(&unk_170))
        sub_1E7CF0()->sub_1E7D90(&unk_170);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_222C70@type_2181E0@@QAEXXZ (folded into 0x222C70)
void type_2181E0::sub_222C70()
{
    type_218B80::sub_1E3480()->sub_1EB160();
    for (std::list<type_21CE60 *>::iterator var_4 = unk_164.begin(); var_4 != unk_164.end(); ++var_4)
        delete *var_4;
    unk_164.clear();
}

// The pause pages' current page and their rows by index, as type_20E4F0's and
// type_21DDC0's: /OPT:ICF folded each with those (0x20E520, 0x21DF90).
type_21CE60 *type_218B80::sub_20E520()
{
    return (type_21CE60 *)type_1ECA30::sub_1E3480()->sub_1EB020();
}

type_21CE60 *type_218B80::sub_21DF90(RwUInt32 arg_0)
{
    return (type_21CE60 *)(*sub_1E3480()->sub_1EB070())[arg_0];
}
