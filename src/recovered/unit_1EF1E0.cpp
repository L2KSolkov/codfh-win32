/*
 * kujuUI's looks' libraries (game/kujuui.h): the image libraries' validator,
 * the image libraries in use and the looks built from their scopes; the
 * array, list and name map instances they use follow.
 */
#include <string.h>
#include "game/kujuui.h"
#include "game/parsedfile.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00504374
namespace kujuUI { type_1EF260 *dword_504374; }
// 0x00504378
struct type_3E83F4 *dword_504378;
// End of its data definitions.


using namespace kujuUI;

namespace kujuUI {
extern type_1EF260 *dword_504374;
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@MOGOBHAF@list?$DMT?$DO?5too?5long?$AA@ @ 0x003DAA04
// match: ??_C@_06IAHKIHIK@images?$AA@ @ 0x003E75FC
// match: ??_C@_0BK@NJFKIPII@Image?5?$CFs?5failed?5to?5load?4?6?$AA@ @ 0x003E7604
// match: ??_C@_0CG@JMGPLMIN@State?5?$CFs?5in?5component?5?$CFs?5is?5inva@ @ 0x003E7620
// match: ??_C@_0CF@BNEDFLN@Image?5?$CFs?5in?5component?5?$CFs?5not?5fou@ @ 0x003E7648
// match: ??_C@_0CK@FIMKDBLI@Image?5?$CFs?5not?5found?5in?5any?5loaded@ @ 0x003E7670
// match: __ehhandler$?sub_1EF1E0@kujuUI@@YAPAUtype_1EF260@1@XZ>1>8 @ 0x0042096C
// match: __ehhandler$?sub_1EF1E0@kujuUI@@YAPAUtype_1EF260@1@XZ>1 @ 0x00420974
// match: __ehhandler$??0type_1EF260@kujuUI@@QAE@XZ>1>8 @ 0x00420990
// match: __ehhandler$??0type_1EF260@kujuUI@@QAE@XZ>1 @ 0x004209A0
// match: __ehhandler$??1type_1EF260@kujuUI@@QAE@XZ>1>8 @ 0x004209BC
// match: __ehhandler$??1type_1EF260@kujuUI@@QAE@XZ>1 @ 0x004209C4
// match: __ehhandler$??1type_1EF3A0@kujuUI@@QAE@XZ>1>8 @ 0x004209E0
// match: __ehhandler$??1type_1EF3A0@kujuUI@@QAE@XZ>1 @ 0x004209E8
// match: __ehhandler$?sub_1EF460@type_1EF3A0@kujuUI@@QAE_NPBD@Z>1>8 @ 0x00420A04
// match: __ehhandler$?sub_1EF460@type_1EF3A0@kujuUI@@QAE_NPBD@Z>1 @ 0x00420A24
// match: __ehhandler$?sub_1EF560@type_1EF3A0@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E3BA0@kujuUI@@@2@@Z>1>8 @ 0x00420A40
// match: __ehhandler$?sub_1EF560@type_1EF3A0@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E3BA0@kujuUI@@@2@@Z>1 @ 0x00420A48
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@XZ>1>8 @ 0x00420A64
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@XZ>1>16>16 @ 0x00420A74
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@XZ>1>16 @ 0x00420A84
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@XZ>1 @ 0x00420A98
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@PAU342@0ABUtype_1E3BA0@kujuUI@@@Z>1>8 @ 0x00420AB4
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@PAU342@0ABUtype_1E3BA0@kujuUI@@@Z>1>16>16 @ 0x00420AC4
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@PAU342@0ABUtype_1E3BA0@kujuUI@@@Z>1>16 @ 0x00420AD4
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@PAU342@0ABUtype_1E3BA0@kujuUI@@@Z>1 @ 0x00420AE8
// match: __ehhandler$?_Incsize@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEXI@Z>1>8 @ 0x00420B04
// match: __ehhandler$?_Incsize@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEXI@Z>1 @ 0x00420B0C

// match: ?sub_1EF1E0@kujuUI@@YAPAUtype_1EF260@1@XZ @ 0x001EF1E0
// match: __ehhandler$?sub_1EF1E0@kujuUI@@YAPAUtype_1EF260@1@XZ-0xB @ 0x003040B0
// match: __ehhandler$?sub_1EF1E0@kujuUI@@YAPAUtype_1EF260@1@XZ @ 0x003040BB

type_1EF260 *kujuUI::sub_1EF1E0()
{
    if (!dword_504374)
        dword_504374 = new type_1EF260;
    return dword_504374;
}

// match: ??0type_1EF260@kujuUI@@QAE@XZ @ 0x001EF260
// match: __ehhandler$??0type_1EF260@kujuUI@@QAE@XZ-0x16 @ 0x003040D0
// match: __ehhandler$??0type_1EF260@kujuUI@@QAE@XZ @ 0x003040E6
type_1EF260::type_1EF260() : unk_118("images", 1, 0, 0, 0, 0, 0, 0, 0)
{
    sub_1C9F50(&unk_118);
    sub_1C9F70(const_cast<cScopeValidator *>(sub_1E3CD0()));
}

// match: ??1type_1EF260@kujuUI@@QAE@XZ @ 0x001EF2F0
// match: __ehhandler$??1type_1EF260@kujuUI@@QAE@XZ-0x8 @ 0x003040F0
// match: __ehhandler$??1type_1EF260@kujuUI@@QAE@XZ @ 0x003040F8
type_1EF260::~type_1EF260()
{
}

// match: ?sub_1EF340@kujuUI@@YAXXZ @ 0x001EF340
void kujuUI::sub_1EF340()
{
    delete dword_504374;
    dword_504374 = 0;
}

// match: ??0type_1EF3A0@kujuUI@@QAE@XZ @ 0x001EF3A0
type_1EF3A0::type_1EF3A0()
{
}

// match: ??1type_1EF3A0@kujuUI@@QAE@XZ @ 0x001EF3E0
// match: __ehhandler$??1type_1EF3A0@kujuUI@@QAE@XZ-0xB @ 0x00304110
// match: __ehhandler$??1type_1EF3A0@kujuUI@@QAE@XZ @ 0x0030411B
type_1EF3A0::~type_1EF3A0()
{
    unk_00.clear();
}

// match: ?sub_1EF460@type_1EF3A0@kujuUI@@QAE_NPBD@Z @ 0x001EF460
// match: __ehhandler$?sub_1EF460@type_1EF3A0@kujuUI@@QAE_NPBD@Z-0x1B @ 0x00304130
// match: __ehhandler$?sub_1EF460@type_1EF3A0@kujuUI@@QAE_NPBD@Z @ 0x0030414B
bool type_1EF3A0::sub_1EF460(const RwChar *arg_0)
{
    type_E8780<type_1ECCE0> var_10(sub_1ED040(arg_0));
    if (!var_10.sub_E87C0())
        unk_00.take(new type_E8780<type_1ECCE0>(var_10));
    else if (0)
        sub_1C8A30("Image %s failed to load.\n", arg_0);
    return !var_10.sub_E87C0();
}

// match: ?sub_1EF560@type_1EF3A0@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E3BA0@kujuUI@@@2@@Z @ 0x001EF560
// match: __ehhandler$?sub_1EF560@type_1EF3A0@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E3BA0@kujuUI@@@2@@Z-0x8 @ 0x00304160
// match: __ehhandler$?sub_1EF560@type_1EF3A0@kujuUI@@QAE_NPAUtype_1C8DF0@2@PAU?$type_1EFCF0@Utype_1E3BA0@kujuUI@@@2@@Z @ 0x00304168
bool type_1EF3A0::sub_1EF560(type_1C8DF0 *arg_0, type_1EFCF0<type_1E3BA0> *arg_4)
{
    type_1E3BA0_state *frm_24[6];
    memset(frm_24, 0, sizeof(frm_24));
    bool bp_29 = true;
    RwUInt32 s34 = 0;
    const RwChar *var_30 = arg_0->sub_1C8FC0();
    RwInt32 lcl_28 = 0;
    for (; s34 != arg_0->sub_1C9120(); ++s34)
    {
        type_1C8DF0_104 *var_38 = arg_0->sub_1C9140(s34);
        if (var_38->get_unk_44() == sub_1E3D60())
            lcl_28 = 1;
        else
        {
            const RwChar *var_40 = var_38->sub_1C9870();
            const RwChar *l3C = (const RwChar *)var_38->sub_1C9890(0)->sub_1E3480();
            RwInt32 var_44 = sub_1F8120(var_40);
            bp_29 = false;
            if (var_44 != 6)
            {
                type_1E7410 *var_48 = sub_1EF780(l3C);
                if (var_48)
                {
                    frm_24[var_44] = (type_1E3BA0_state *)var_48;
                    bp_29 = true;
                }
                else if (0)
                    sub_1C8A30("Image %s in component %s not found.\n", l3C, arg_0->sub_1C8FC0());
            }
            else if (0)
                sub_1C8A30("State %s in component %s is invalid.\n", l3C, arg_0->sub_1C8FC0());
        }
    }
    if (bp_29 && var_30)
    {
        sub_1E3C10(frm_24);
        std::list<type_1E3BA0>::iterator var_4C = unk_44.insert(unk_44.begin(), type_1E3BA0(frm_24, lcl_28));
        arg_4->sub_1EFCF0(var_30, &*var_4C);
    }
    return bp_29;
}

// match: ?sub_1EF780@type_1EF3A0@kujuUI@@QAEPAUtype_1E7410@2@PBD@Z @ 0x001EF780
type_1E7410 *type_1EF3A0::sub_1EF780(const RwChar *arg_0)
{
    for (type_1E61A0_it<type_E8780<type_1ECCE0>, 16> var_8 = unk_00.begin(), var_10 = unk_00.end(); var_8.ne(var_10);
         var_8.inc())
    {
        type_1E7410 *var_14 = (*var_8.get())->sub_1ED630(arg_0);
        if (var_14)
            return var_14;
    }
    if (0)
        sub_1C8A30("Image %s not found in any loaded images.\n", arg_0);
    return 0;
}

// match: ?sub_1EF810@kujuUI@@YAPBVcScopeValidator@1@XZ @ 0x001EF810
const cScopeValidator *kujuUI::sub_1EF810()
{
    const cScopeValidator *var_4 = sub_1EF1E0();
    return var_4;
}

// match: ?sub_1EF830@kujuUI@@YAPAUtype_1C9590@1@XZ @ 0x001EF830
type_1C9590 *kujuUI::sub_1EF830()
{
    type_1EF260 *var_4 = sub_1EF1E0();
    return &var_4->unk_118;
}

// match: ?sub_1EF850@kujuUI@@YAXXZ @ 0x001EF850
void kujuUI::sub_1EF850()
{
    sub_1EF340();
}

// The array's, its iterator's and std::list<type_1E3BA0>'s instances.
// match: ??1?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@QAE@XZ @ 0x001EF860
// match: ?_Insert@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@QAEXViterator@12@ABUtype_1E3BA0@kujuUI@@@Z @ 0x001EF8A0
// match: ?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@XZ @ 0x001EF900
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@XZ @ 0x00304180
// match: ?clear@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@QAEXXZ @ 0x001EF9E0
// match: ?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@PAU342@0ABUtype_1E3BA0@kujuUI@@@Z @ 0x001EFA70
// match: __ehhandler$?_Buynode@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEPAU_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@2@PAU342@0ABUtype_1E3BA0@kujuUI@@@Z @ 0x00304190
// match: ?_Incsize@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEXI@Z @ 0x001EFB30
// match: __ehhandler$?_Incsize@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEXI@Z-0x8 @ 0x003041A0
// match: __ehhandler$?_Incsize@?$list@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@IAEXI@Z @ 0x003041A8
// match: ??0?$type_1E61A0@U?$type_E8780@Utype_1ECCE0@kujuUI@@@@$0BA@@@QAE@XZ @ 0x001EFC00
// match: ?take@?$type_1E61A0@U?$type_E8780@Utype_1ECCE0@kujuUI@@@@$0BA@@@QAEXPAU?$type_E8780@Utype_1ECCE0@kujuUI@@@@@Z @ 0x001EFC20
// match: ?end@?$type_1E61A0@U?$type_E8780@Utype_1ECCE0@kujuUI@@@@$0BA@@@QAE?AU?$type_1E61A0_it@U?$type_E8780@Utype_1ECCE0@kujuUI@@@@$0BA@@@XZ @ 0x001EFC60
// match: ?clear@?$type_1E61A0@U?$type_E8780@Utype_1ECCE0@kujuUI@@@@$0BA@@@QAEXXZ @ 0x001EFC90
// match: ??1_Node@?$_List_nod@Utype_1E3BA0@kujuUI@@V?$allocator@Utype_1E3BA0@kujuUI@@@std@@@std@@QAE@XZ @ 0x001EFD10
// match: ?next@?$type_1E61A0@U?$type_E8780@Utype_1ECCE0@kujuUI@@@@$0BA@@@QAEPAU?$type_E8780@Utype_1ECCE0@kujuUI@@@@XZ @ 0x001EFD30
// match: ??0?$type_1E61A0_it@U?$type_E8780@Utype_1ECCE0@kujuUI@@@@$0BA@@@QAE@PAU?$type_E8780@Utype_1ECCE0@kujuUI@@@@PBU?$type_1E61A0@U?$type_E8780@Utype_1ECCE0@kujuUI@@@@$0BA@@@@Z @ 0x001EFD70

// match: ?sub_1EFCF0@?$type_1EFCF0@Utype_1E3BA0@kujuUI@@@kujuUI@@QAEHPBDPAUtype_1E3BA0@2@@Z @ 0x001EFCF0

// ??1type_1E4130@kujuUI@@QAE@XZ (folded into 0x1EFD10)
kujuUI::type_1E4130::~type_1E4130()
{
}
