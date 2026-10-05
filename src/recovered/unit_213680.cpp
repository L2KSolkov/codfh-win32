/*
 * The players selector (game/hostoptions.h, a member of the host options):
 * its destruction, and its option selector's instance over type_2138C0_value
 * with that instance's map code, and its constructor; and a text's number
 * appended (sub_214A70).
 */
#include "game/hostoptions.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_02KMALDIDP@16?$AA@ @ 0x003E946C
// match: ??_C@_01KJLJFBPL@8?$AA@ @ 0x003E9470
// match: ??_C@_01FAMBOPH@4?$AA@ @ 0x003E9474
// match: ??_7type_213680@@6B@ @ 0x003E9478
// match: ??_7?$type_1FCDC0@W4type_2138C0_value@@@@6B@ @ 0x003E9490
// match: __ehhandler$??0type_213680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00423E90
// match: __ehhandler$??0type_213680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00423EB8
// match: __ehhandler$??0?$type_1FCDC0@W4type_2138C0_value@@@@QAE@PAW4type_2138C0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00423ED4
// match: __ehhandler$??0?$type_1FCDC0@W4type_2138C0_value@@@@QAE@PAW4type_2138C0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00423EDC
// match: __ehhandler$??1?$type_1FCDC0@W4type_2138C0_value@@@@UAE@XZ>1>8 @ 0x00423EF8
// match: __ehhandler$??1?$type_1FCDC0@W4type_2138C0_value@@@@UAE@XZ>1 @ 0x00423F00
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_2138C0_value@@@@QAEXABW4type_2138C0_value@@ABUtype_1CB670@@@Z>1>8 @ 0x00423F1C
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_2138C0_value@@@@QAEXABW4type_2138C0_value@@ABUtype_1CB670@@@Z>1 @ 0x00423F34
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00423F50
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@@Z>1 @ 0x00423F58
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00423F74
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00423F8C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00423F9C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00423FB0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00423FCC
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00423FD4
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00423FF0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00424000
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00424010
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00424024

// match: ??_G?$type_1FCDC0@W4type_2138C0_value@@@@UAEPAXI@Z @ 0x00213B30
// match: ?insert@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@@Z @ 0x00213B60
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@@Z @ 0x00213CF0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@@Z-0x8 @ 0x00306E60
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@@Z @ 0x00306E68
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00214040
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x002140C0
// match: ?_Init@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00214190
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@D@Z @ 0x00214200
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@D@Z-0x11 @ 0x00306E80
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@2@D@Z @ 0x00306E91
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x002142F0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00306EA0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00306EA8
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x00214880
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x002148E0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00306EC0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_2138C0_value@@Utype_1CB670@@U?$less@W4type_2138C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_2138C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x00214A00

// "4", "8" and "16" players (1, 2 and 4), with "Any" (8, picked) when arg_0
// is 1; the hook arg_4.
// match: ??0type_213680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00213680
// match: __ehhandler$??0type_213680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z-0x2E @ 0x00306DB0
// match: __ehhandler$??0type_213680@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00306DDE
type_213680::type_213680(RwInt32 arg_0, type_1ED670_object *arg_4) : type_1FCDC0<type_2138C0_value>(0, arg_4)
{
    sub_1FCEB0((type_2138C0_value)1, sub_1CB720("4"));
    sub_1FCEB0((type_2138C0_value)2, sub_1CB720("8"));
    sub_1FCEB0((type_2138C0_value)4, sub_1CB720("16"));
    if (arg_0 == 1)
    {
        sub_1FCEB0((type_2138C0_value)8, type_1CB670("Any", 0));
        sub_201EC0((type_2138C0_value)8);
    }
}

// match: ??_Gtype_213680@@UAEPAXI@Z @ 0x00213870
// match: ??1type_213680@@UAE@XZ @ 0x002138A0
type_213680::~type_213680()
{
}

// The selector template's members (game/options.h's unit defines them),
// repeated for this unit's instance.
// match: ??0?$type_1FCDC0@W4type_2138C0_value@@@@QAE@PAW4type_2138C0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x002138C0
// match: __ehhandler$??0?$type_1FCDC0@W4type_2138C0_value@@@@QAE@PAW4type_2138C0_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x00306DF0
// match: __ehhandler$??0?$type_1FCDC0@W4type_2138C0_value@@@@QAE@PAW4type_2138C0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306DF8

// match: ??1?$type_1FCDC0@W4type_2138C0_value@@@@UAE@XZ @ 0x00213950
// match: __ehhandler$??1?$type_1FCDC0@W4type_2138C0_value@@@@UAE@XZ-0x8 @ 0x00306E10
// match: __ehhandler$??1?$type_1FCDC0@W4type_2138C0_value@@@@UAE@XZ @ 0x00306E18

// match: ?sub_1FCEB0@?$type_1FCDC0@W4type_2138C0_value@@@@QAEXABW4type_2138C0_value@@ABUtype_1CB670@@@Z @ 0x002139B0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_2138C0_value@@@@QAEXABW4type_2138C0_value@@ABUtype_1CB670@@@Z-0x18 @ 0x00306E30
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_2138C0_value@@@@QAEXABW4type_2138C0_value@@ABUtype_1CB670@@@Z @ 0x00306E48

// match: ?sub_214A70@type_1A5EA0@@QAEAAU1@H@Z @ 0x00214A70
type_1A5EA0 &type_1A5EA0::sub_214A70(RwInt32 arg_0)
{
    sub_1C8540(arg_0);
    return *this;
}
