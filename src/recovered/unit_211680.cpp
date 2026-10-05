/*
 * The level selector (game/hostoptions.h, a member of the host options): its
 * destruction, and its option selector's instance over the level key with
 * that instance's map code, the key pair's destructor and the selectors'
 * shared slot 3 (0x211AE0), and its constructor.
 */
#include "game/hostoptions.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E93F0
extern const RwReal flt_3E93F0 = 0.01f;
// 0x003E93F4
extern const RwReal flt_3E93F4 = 0.01f;
// 0x003E93F8
extern const RwReal flt_3E93F8 = 16.666666f;
// End of its data definitions.

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_505188 unk_505188;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E93F0@@3MB @ 0x003E93F0
// match: ?flt_3E93F4@@3MB @ 0x003E93F4
// match: ?flt_3E93F8@@3MB @ 0x003E93F8
// match: ??_7type_211680@@6B@ @ 0x003E93FC
// match: ??_7?$type_1FCDC0@Utype_211860_key@@@@6B@ @ 0x003E9414
// match: __ehhandler$??0type_211680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00423AF8
// match: __ehhandler$??0type_211680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00423B28
// match: __ehhandler$??0?$type_1FCDC0@Utype_211860_key@@@@QAE@PAUtype_211860_key@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00423B44
// match: __ehhandler$??0?$type_1FCDC0@Utype_211860_key@@@@QAE@PAUtype_211860_key@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00423B4C
// match: __ehhandler$??1?$type_1FCDC0@Utype_211860_key@@@@UAE@XZ>1>8 @ 0x00423B68
// match: __ehhandler$??1?$type_1FCDC0@Utype_211860_key@@@@UAE@XZ>1 @ 0x00423B70
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@Utype_211860_key@@@@QAEXABUtype_211860_key@@ABUtype_1CB670@@@Z>1>8 @ 0x00423B8C
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@Utype_211860_key@@@@QAEXABUtype_211860_key@@ABUtype_1CB670@@@Z>1 @ 0x00423BCC
// match: __ehhandler$??1?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@QAE@XZ>1>8 @ 0x00423BE8
// match: __ehhandler$??1?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@QAE@XZ>1 @ 0x00423BF0
// match: __ehhandler$??1?$pair@Utype_211860_key@@Utype_1CB670@@@std@@QAE@XZ>1>8 @ 0x00423C0C
// match: __ehhandler$??1?$pair@Utype_211860_key@@Utype_1CB670@@@std@@QAE@XZ>1 @ 0x00423C14
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@@Z>1>8 @ 0x00423C30
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@@Z>1 @ 0x00423C38
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00423C54
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00423C74
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00423C84
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@D@Z>1 @ 0x00423C98
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00423CB4
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00423CBC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00423CD8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00423CE8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00423CF8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00423D0C
// match: .CRT$XCU+0 @ 0x00427368

// match: _$E1 @ 0x0030DB00
// match: _$E2 @ 0x0030F060

using namespace kujuUI;

// match: ??_G?$type_1FCDC0@Utype_211860_key@@@@UAEPAXI@Z @ 0x00211B80
// match: ?insert@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@@Z @ 0x00211C00
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@@Z @ 0x00211DA0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@@Z-0x8 @ 0x00306C50
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@@Z @ 0x00306C58
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x002120F0
// match: ?erase@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x00212170
// match: ?_Init@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00212240
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@D@Z @ 0x002122B0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@D@Z-0x19 @ 0x00306C70
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@2@D@Z @ 0x00306C89
// match: ?erase@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x002123B0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00306CA0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00306CA8
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00212940
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00306CC0
// match: ??$_Destroy@U_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@@std@@YAXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@0@@Z @ 0x00212A60
// match: ??1?$pair@Utype_211860_key@@Utype_1CB670@@@std@@QAE@XZ @ 0x00211BB0
// match: __ehhandler$??1?$pair@Utype_211860_key@@Utype_1CB670@@@std@@QAE@XZ-0x8 @ 0x00306C30
// match: __ehhandler$??1?$pair@Utype_211860_key@@Utype_1CB670@@@std@@QAE@XZ @ 0x00306C38

// The levels in the level list by name, with "Any" (unk_505188, picked)
// when arg_0 is 1; the hook arg_4.
// match: ??0type_211680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00211680
// match: __ehhandler$??0type_211680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z-0x30 @ 0x00306B60
// match: __ehhandler$??0type_211680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00306B90
type_211680::type_211680(RwInt32 arg_0, type_1ED670_object *arg_4) : type_1FCDC0<type_211860_key>(0, arg_4)
{
    RwUInt32 lv_10;
    RwInt32 lv_14;

    lv_10 = dword_4FD970;
    for (lv_14 = 0; lv_14 != lv_10; lv_14++)
    {
        LEVELS_CHECK(lv_14);
        LEVELS_CHECK(lv_14);
        type_505188 *lv_18 = &dword_4FD974[lv_14];
        sub_1FCEB0(lv_18, type_1CB670(lv_18->sub_1A5F60().c_str(), 0));
    }
    if (arg_0 == 1)
    {
        sub_1FCEB0(&unk_505188, type_1CB670("Any", 0));
        sub_201EC0(&unk_505188);
    }
}

// match: ??_Gtype_211680@@UAEPAXI@Z @ 0x00211810
// match: ??1type_211680@@UAE@XZ @ 0x00211840
type_211680::~type_211680()
{
}

// The selector template's members (game/options.h's unit defines them),
// repeated for this unit's instance.
// match: ??0?$type_1FCDC0@Utype_211860_key@@@@QAE@PAUtype_211860_key@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00211860
// match: __ehhandler$??0?$type_1FCDC0@Utype_211860_key@@@@QAE@PAUtype_211860_key@@PAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x00306BA0
// match: __ehhandler$??0?$type_1FCDC0@Utype_211860_key@@@@QAE@PAUtype_211860_key@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306BA8

// match: ??1?$type_1FCDC0@Utype_211860_key@@@@UAE@XZ @ 0x002118F0
// match: __ehhandler$??1?$type_1FCDC0@Utype_211860_key@@@@UAE@XZ-0x8 @ 0x00306BC0
// match: __ehhandler$??1?$type_1FCDC0@Utype_211860_key@@@@UAE@XZ @ 0x00306BC8

// match: ?sub_1FCEB0@?$type_1FCDC0@Utype_211860_key@@@@QAEXABUtype_211860_key@@ABUtype_1CB670@@@Z @ 0x00211950
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@Utype_211860_key@@@@QAEXABUtype_211860_key@@ABUtype_1CB670@@@Z-0x40 @ 0x00306BE0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@Utype_211860_key@@@@QAEXABUtype_211860_key@@ABUtype_1CB670@@@Z @ 0x00306C20

// match: ?vf_00C@?$type_1FCDC0@Utype_211860_key@@@@UAEXI@Z @ 0x00211AE0

