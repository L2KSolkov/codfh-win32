/*
 * The yes-or-no rules' selectors' option selector instance over
 * type_214C30_value (game/hostoptions.h; the rest of its code sits with
 * the host options' unit): its constructor, its value added, and its map's
 * insertion; and the yes-or-no selector's constructor and deleting
 * destructor.
 */
#include "game/hostoptions.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E94A8
extern const RwReal flt_3E94A8 = 0.01f;
// 0x003E94AC
extern const RwReal flt_3E94AC = 0.01f;
// 0x003E94B0
extern const RwReal flt_3E94B0 = 16.666666f;
// End of its data definitions.

using namespace kujuUI;

// "Yes" (1) and "No" (0), with "Any" (2) when arg_0 is 1; picks arg_4; the
// hook arg_8.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E94A8@@3MB @ 0x003E94A8
// match: ?flt_3E94AC@@3MB @ 0x003E94AC
// match: ?flt_3E94B0@@3MB @ 0x003E94B0
// match: ??_7type_214A90@@6B@ @ 0x003E94B4
// match: __ehhandler$??0type_214A90@@QAE@HW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00424040
// match: __ehhandler$??0type_214A90@@QAE@HW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00424060
// match: __ehhandler$??0?$type_1FCDC0@W4type_214C30_value@@@@QAE@PAW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x0042407C
// match: __ehhandler$??0?$type_1FCDC0@W4type_214C30_value@@@@QAE@PAW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00424084
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_214C30_value@@@@QAEXABW4type_214C30_value@@ABUtype_1CB670@@@Z>1>8 @ 0x004240A0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_214C30_value@@@@QAEXABW4type_214C30_value@@ABUtype_1CB670@@@Z>1 @ 0x004240B8
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x004240D4
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@@Z>1 @ 0x004240DC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x004240F8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00424110
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00424120
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00424134
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00424150
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00424160
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00424170
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00424184

// match: ??0type_214A90@@QAE@HW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00214A90
// match: __ehhandler$??0type_214A90@@QAE@HW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x23 @ 0x00306ED0
// match: __ehhandler$??0type_214A90@@QAE@HW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306EF3

type_214A90::type_214A90(RwInt32 arg_0, type_214C30_value arg_4, type_1ED670_object *arg_8) : type_1FCDC0<type_214C30_value>(0, arg_8)
{
    sub_1FCEB0((type_214C30_value)1, type_1CB670("Yes", 0));
    sub_1FCEB0((type_214C30_value)0, type_1CB670("No", 0));
    if (arg_0 == 1)
        sub_1FCEB0((type_214C30_value)2, type_1CB670("Any", 0));
    sub_201EC0(arg_4);
}

// Its deleting destructor, over the implicit destructor the host options'
// unit defines (0x201370).
// match: ??_Gtype_214A90@@UAEPAXI@Z @ 0x00214C00

// match: ?insert@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@@Z @ 0x00214E40
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@@Z @ 0x00214FD0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@@Z-0x8 @ 0x00306F50
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@@Z @ 0x00306F58
// match: ?_Init@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00215320
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@D@Z @ 0x00215390
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@D@Z-0x11 @ 0x00306F70
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@2@D@Z @ 0x00306F81
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00215480
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00306F90

// The selector template's members (game/options.h's unit defines them),
// repeated for this unit's instance.
// match: ??0?$type_1FCDC0@W4type_214C30_value@@@@QAE@PAW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00214C30
// match: __ehhandler$??0?$type_1FCDC0@W4type_214C30_value@@@@QAE@PAW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x00306F00
// match: __ehhandler$??0?$type_1FCDC0@W4type_214C30_value@@@@QAE@PAW4type_214C30_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306F08

// match: ?sub_1FCEB0@?$type_1FCDC0@W4type_214C30_value@@@@QAEXABW4type_214C30_value@@ABUtype_1CB670@@@Z @ 0x00214CC0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_214C30_value@@@@QAEXABW4type_214C30_value@@ABUtype_1CB670@@@Z-0x18 @ 0x00306F20
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_214C30_value@@@@QAEXABW4type_214C30_value@@ABUtype_1CB670@@@Z @ 0x00306F38

