/*
 * The game type selector (game/hostoptions.h, a member of the host options):
 * its destruction, and its option selector's instance over type_210430_value
 * with that instance's map code and the selectors' shared slot 2
 * (0x2106A0), and its constructor.
 */
#include "game/hostoptions.h"
#include "game/mpgame.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E93B4
extern const RwReal flt_3E93B4 = 0.01f;
// 0x003E93B8
extern const RwReal flt_3E93B8 = 0.01f;
// 0x003E93BC
extern const RwReal flt_3E93BC = 16.666666f;
// End of its data definitions.

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E93B4@@3MB @ 0x003E93B4
// match: ?flt_3E93B8@@3MB @ 0x003E93B8
// match: ?flt_3E93BC@@3MB @ 0x003E93BC
// match: ??_7type_210180@@6B@ @ 0x003E93C0
// match: ??_7?$type_1FCDC0@W4type_210430_value@@@@6B@ @ 0x003E93D8
// match: __ehhandler$??0type_210180@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00423940
// match: __ehhandler$??0type_210180@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00423970
// match: __ehhandler$??0?$type_1FCDC0@W4type_210430_value@@@@QAE@PAW4type_210430_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x0042398C
// match: __ehhandler$??0?$type_1FCDC0@W4type_210430_value@@@@QAE@PAW4type_210430_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00423994
// match: __ehhandler$??1?$type_1FCDC0@W4type_210430_value@@@@UAE@XZ>1>8 @ 0x004239B0
// match: __ehhandler$??1?$type_1FCDC0@W4type_210430_value@@@@UAE@XZ>1 @ 0x004239B8
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_210430_value@@@@QAEXABW4type_210430_value@@ABUtype_1CB670@@@Z>1>8 @ 0x004239D4
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_210430_value@@@@QAEXABW4type_210430_value@@ABUtype_1CB670@@@Z>1 @ 0x004239EC
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00423A08
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@@Z>1 @ 0x00423A10
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00423A2C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00423A44
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00423A54
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00423A68
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00423A84
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00423A8C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00423AA8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00423AB8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00423AC8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00423ADC

// match: ??_G?$type_1FCDC0@W4type_210430_value@@@@UAEPAXI@Z @ 0x00210740
// match: ?insert@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@@Z @ 0x00210770
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@@Z @ 0x00210900
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@@Z-0x8 @ 0x00306AF0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@@Z @ 0x00306AF8
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00210C50
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x00210CD0
// match: ?_Init@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00210DA0
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@D@Z @ 0x00210E10
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@D@Z-0x11 @ 0x00306B10
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@2@D@Z @ 0x00306B21
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00210F00
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00306B30
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00306B38
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x00211490
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x002114F0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00306B50
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_210430_value@@Utype_1CB670@@U?$less@W4type_210430_value@@@std@@V?$allocator@U?$pair@$$CBW4type_210430_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x00211610

// The game types (1, 2, 4 and 8) by name, with 0x20 (picked) when arg_0 is
// 1; the hook arg_4.
// match: ??0type_210180@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00210180
// match: __ehhandler$??0type_210180@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z-0x39 @ 0x00306A30
// match: __ehhandler$??0type_210180@@QAE@HPAUtype_1ED670_object@kujuUI@@@Z @ 0x00306A69
type_210180::type_210180(RwInt32 arg_0, type_1ED670_object *arg_4) : type_1FCDC0<type_210430_value>(0, arg_4)
{
    sub_1FCEB0((type_210430_value)1, type_1CB670(sub_1C4E60(1), 0));
    sub_1FCEB0((type_210430_value)2, type_1CB670(sub_1C4E60(2), 0));
    sub_1FCEB0((type_210430_value)4, type_1CB670(sub_1C4E60(4), 0));
    sub_1FCEB0((type_210430_value)8, type_1CB670(sub_1C4E60(8), 0));
    if (arg_0 == 1)
    {
        sub_1FCEB0((type_210430_value)0x20, type_1CB670(sub_1C4E60(0x20), 0));
        sub_201EC0((type_210430_value)0x20);
    }
}

// match: ??_Gtype_210180@@UAEPAXI@Z @ 0x002103E0
// match: ??1type_210180@@UAE@XZ @ 0x00210410
type_210180::~type_210180()
{
}

// The selector template's members (game/options.h's unit defines them),
// repeated for this unit's instance.
// match: ??0?$type_1FCDC0@W4type_210430_value@@@@QAE@PAW4type_210430_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00210430
// match: __ehhandler$??0?$type_1FCDC0@W4type_210430_value@@@@QAE@PAW4type_210430_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x00306A80
// match: __ehhandler$??0?$type_1FCDC0@W4type_210430_value@@@@QAE@PAW4type_210430_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306A88

// match: ??1?$type_1FCDC0@W4type_210430_value@@@@UAE@XZ @ 0x002104C0
// match: __ehhandler$??1?$type_1FCDC0@W4type_210430_value@@@@UAE@XZ-0x8 @ 0x00306AA0
// match: __ehhandler$??1?$type_1FCDC0@W4type_210430_value@@@@UAE@XZ @ 0x00306AA8

// match: ?sub_1FCEB0@?$type_1FCDC0@W4type_210430_value@@@@QAEXABW4type_210430_value@@ABUtype_1CB670@@@Z @ 0x00210520
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_210430_value@@@@QAEXABW4type_210430_value@@ABUtype_1CB670@@@Z-0x18 @ 0x00306AC0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_210430_value@@@@QAEXABW4type_210430_value@@ABUtype_1CB670@@@Z @ 0x00306AD8

// match: ?vf_008@?$type_1FCDC0@W4type_210430_value@@@@UAEXI@Z @ 0x002106A0

