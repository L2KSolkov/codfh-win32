/*
 * The kick page (game/ingamepages.h): the other players listed by name, the
 * one picked kicked after a confirmation. The selection's handler (its
 * columns' slot 4, sub_2186C0) and the rows' list's _Incsize (sub_218AB0)
 * unwind strings through the library's out-of-line string destructor
 * (sub_43900) and are not matched (docs/questions.md).
 */
#include "game/ingamepages.h"
#include "game/uiglue.h"

using namespace kujuUI;

// The rows' list's members (std::list<type_21CE60 *>).
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
    type_1DDE20_mask var_10 = sub_1C48A0();
    var_10.unset(0);
    for (RwUInt32 var_14 = 0; var_14 < 16; var_14++)
    {
        if (var_10.test(var_14))
        {
            RwChar *var_1C = sub_1C4630(var_14);
            type_21CE60 *var_20 = new type_21CE60(var_14, var_1C);

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

            var_8.unset(0);
            if (var_8.test(var_4->sub_21D030()))
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

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// The rows' list's insertion, reached through push_back.
template void std::list<type_21CE60 *>::_Insert(std::list<type_21CE60 *>::iterator, type_21CE60 *const &);
