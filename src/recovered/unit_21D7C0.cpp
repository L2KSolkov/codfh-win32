// Split from unit_21D470.cpp at 0x21D7C0, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include "game/ingamepages.h"
#include "game/uiglue.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003EA428
extern const RwReal flt_3EA428 = 0.01f;
// 0x003EA42C
extern const RwReal flt_3EA42C = 0.01f;
// 0x003EA430
extern const RwReal flt_3EA430 = 16.666666f;

// match: ?flt_3EA428@@3MB @ 0x003EA428
// match: ?flt_3EA42C@@3MB @ 0x003EA42C
// match: ?flt_3EA430@@3MB @ 0x003EA430


using namespace kujuUI;

// match: __ehhandler$?_Incsize@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEXI@Z>1>8 @ 0x00425260
// match: __ehhandler$?_Incsize@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEXI@Z>1 @ 0x00425268
// match: __ehhandler$??0type_21D7C0@@QAE@XZ>1>8 @ 0x00425144
// match: __ehhandler$??0type_21D7C0@@QAE@XZ>1 @ 0x00425154
// match: __ehhandler$??1type_21D7C0@@UAE@XZ>1>8 @ 0x00425170
// match: __ehhandler$??1type_21D7C0@@UAE@XZ>1 @ 0x00425180
// match: __ehhandler$?sub_21D9F0@type_21D7C0@@QAEHHABUtype_1A5EA0@@HHH@Z>1>8 @ 0x0042519C
// match: __ehhandler$?sub_21D9F0@type_21D7C0@@QAEHHABUtype_1A5EA0@@HHH@Z>1 @ 0x004251A4
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@XZ>1>8 @ 0x004251C0
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@XZ>1>16>16 @ 0x004251D0
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@XZ>1>16 @ 0x004251E0
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@XZ>1 @ 0x004251F4
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@PAU342@0ABQAUtype_21D470@@@Z>1>8 @ 0x00425210
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@PAU342@0ABQAUtype_21D470@@@Z>1>16>16 @ 0x00425220
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@PAU342@0ABQAUtype_21D470@@@Z>1>16 @ 0x00425230
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@PAU342@0ABQAUtype_21D470@@@Z>1 @ 0x00425244
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@XZ @ 0x00308080
// match: __ehhandler$?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@PAU342@0ABQAUtype_21D470@@@Z @ 0x00308090
// match: ?_Insert@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@QAEXViterator@12@ABQAUtype_21D470@@@Z @ 0x0021DAF0
// match: ?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@XZ @ 0x0021DB50
// match: ?_Buynode@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@2@PAU342@0ABQAUtype_21D470@@@Z @ 0x0021DC30
// match: ??_Gtype_21DDC0@@UAEPAXI@Z @ 0x0021DE30
// match: ??1type_21DDC0@@UAE@XZ @ 0x0021D8A0
// match: ??_7type_21D7C0@@6B@ @ 0x003EA434
// match: ??_7type_21DDC0@@6B@ @ 0x003EA450

// match: ??0type_21D7C0@@QAE@XZ @ 0x0021D7C0
// match: __ehhandler$??0type_21D7C0@@QAE@XZ-0x13 @ 0x00308020
// match: __ehhandler$??0type_21D7C0@@QAE@XZ @ 0x00308033
type_21D7C0::type_21D7C0() : type_21DDC0(3)
{
    sub_1ECB60(0, 0xB4);
    sub_1ECB90(0, 0);
    sub_1ECB60(1, 0x1E);
    sub_1ECB60(2, 0x1C);
}
// match: ??_Gtype_21D7C0@@UAEPAXI@Z @ 0x0021D870
// match: ??1type_21D7C0@@UAE@XZ @ 0x0021D8C0
// match: __ehhandler$??1type_21D7C0@@UAE@XZ-0x13 @ 0x00308040
// match: __ehhandler$??1type_21D7C0@@UAE@XZ @ 0x00308053
type_21D7C0::~type_21D7C0()
{
    sub_21D950();
}
// match: ?sub_21D950@type_21D7C0@@QAEXXZ @ 0x0021D950
void type_21D7C0::sub_21D950()
{
    sub_1E3480()->sub_1EB160();
    for (std::list<type_21D470 *>::iterator var_4 = unk_10.begin(); var_4 != unk_10.end(); ++var_4)
        delete *var_4;
    unk_10.clear();
}
// match: ?sub_21D9F0@type_21D7C0@@QAEHHABUtype_1A5EA0@@HHH@Z @ 0x0021D9F0
// match: __ehhandler$?sub_21D9F0@type_21D7C0@@QAEHHABUtype_1A5EA0@@HHH@Z-0xB @ 0x00308060
// match: __ehhandler$?sub_21D9F0@type_21D7C0@@QAEHHABUtype_1A5EA0@@HHH@Z @ 0x0030806B
RwInt32 type_21D7C0::sub_21D9F0(RwInt32 arg_0, const type_1A5EA0 &arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    type_21D470 *lv_10 = new type_21D470(arg_0, arg_4, arg_8, arg_C, arg_10);

    unk_10.push_back(lv_10);
    RwInt32 var_14 = sub_21DDF0(lv_10);

    if (arg_0 == sub_1C42F0())
        sub_1E3480()->sub_1EB0B0(var_14);
    return var_14;
}
// match: ??0type_21DDC0@@QAE@I@Z @ 0x0021DDC0
type_21DDC0::type_21DDC0(RwUInt32 arg_0) : type_1ECA30(arg_0)
{
}
// match: ?sub_21DDF0@type_21DDC0@@QAEHPAUtype_21D470@@@Z @ 0x0021DDF0
RwInt32 type_21DDC0::sub_21DDF0(type_21D470 *arg_0)
{
    RwInt32 var_4 = sub_21DE60(arg_0);

    sub_1E3480()->sub_1EA980(arg_0, var_4);
    return var_4;
}
// match: ?sub_21DE60@type_21DDC0@@QAEHPAUtype_21D470@@@Z @ 0x0021DE60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_21DDC0::sub_21DE60(type_21D470 *arg_0)
{
    bool var_25;
    RwUInt32 var_24;
    type_21D470 *var_20;
    RwUInt32 l1C;
    bool x15;
    RwInt32 ebp_14;
    std::vector<type_3E74C0 *> *lv_10;
    type_21D470 *var_C;
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
        var_25 = arg_0->sub_21D760(*var_20);
        if (var_25)
            bp_8 = var_24;
        else
            bp_4 = var_24;
        l1C = bp_8 - bp_4;
    }
    var_C = sub_21DF90(bp_4);
    x15 = var_C->sub_21D760(*arg_0);
    ebp_14 = x15 ? bp_4 + 1 : bp_4;
    return ebp_14;
}
// match: ?sub_21DF90@type_21DDC0@@QAEPAUtype_21D470@@I@Z @ 0x0021DF90
type_21D470 *type_21DDC0::sub_21DF90(RwUInt32 arg_0)
{
    return (type_21D470 *)(*sub_1E3480()->sub_1EB070())[arg_0];
}

// The rows' list's size check (std::list's, throwing length_error).
// match: ?_Incsize@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEXI@Z @ 0x0021DCF0
// match: __ehhandler$?_Incsize@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEXI@Z-0x8 @ 0x003080A0
// match: __ehhandler$?_Incsize@?$list@PAUtype_21D470@@V?$allocator@PAUtype_21D470@@@std@@@std@@IAEXI@Z @ 0x003080A8

// The rows' list's insertion, reached through push_back.
template void std::list<type_21D470 *>::_Insert(std::list<type_21D470 *>::iterator, type_21D470 *const &);
