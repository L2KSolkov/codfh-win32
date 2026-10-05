/*
 * The respawn order selector's option selector instance over
 * type_212C70_value (game/hostoptions.h; the rest of its code sits with
 * the host options' unit): its constructor, its value added, and its map's
 * insertion; the respawn order selector's constructor and deleting
 * destructor; and the server name text (type_213610).
 */
#include "game/hostoptions.h"

using namespace kujuUI;

// "None", "Forwards", "Backwards" and "Random" (0 to 3); the hook arg_0.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_06BEOPDEGP@Random?$AA@ @ 0x003E942C
// match: ??_C@_09CCHICIOO@Backwards?$AA@ @ 0x003E9434
// match: ??_C@_08POMNKAJD@Forwards?$AA@ @ 0x003E9440
// match: ??_7type_212A80@@6B@ @ 0x003E944C
// match: ??_7type_213610@@6B@ @ 0x003E9464
// match: __ehhandler$??0type_212A80@@QAE@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00423D28
// match: __ehhandler$??0type_212A80@@QAE@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00423D50
// match: __ehhandler$??0?$type_1FCDC0@W4type_212C70_value@@@@QAE@PAW4type_212C70_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00423D6C
// match: __ehhandler$??0?$type_1FCDC0@W4type_212C70_value@@@@QAE@PAW4type_212C70_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00423D74
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_212C70_value@@@@QAEXABW4type_212C70_value@@ABUtype_1CB670@@@Z>1>8 @ 0x00423D90
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_212C70_value@@@@QAEXABW4type_212C70_value@@ABUtype_1CB670@@@Z>1 @ 0x00423DA8
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00423DC4
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@@Z>1 @ 0x00423DCC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00423DE8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00423E00
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00423E10
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00423E24
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00423E40
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00423E50
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00423E60
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00423E74

// match: ??0type_212A80@@QAE@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00212A80
// match: __ehhandler$??0type_212A80@@QAE@PAUtype_1ED670_object@kujuUI@@@Z-0x2E @ 0x00306CD0
// match: __ehhandler$??0type_212A80@@QAE@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306CFE

type_212A80::type_212A80(type_1ED670_object *arg_0) : type_1FCDC0<type_212C70_value>(0, arg_0)
{
    sub_1FCEB0((type_212C70_value)0, type_1CB670("None", 0));
    sub_1FCEB0((type_212C70_value)1, type_1CB670("Forwards", 0));
    sub_1FCEB0((type_212C70_value)2, type_1CB670("Backwards", 0));
    sub_1FCEB0((type_212C70_value)3, type_1CB670("Random", 0));
}

// Its deleting destructor, over the implicit destructor the host options'
// unit defines (0x201350).
// match: ??_Gtype_212A80@@UAEPAXI@Z @ 0x00212C40

// match: ?insert@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@@Z @ 0x00212EB0
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@@Z @ 0x00213040
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@@Z-0x8 @ 0x00306D60
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@@Z @ 0x00306D68
// match: ?_Init@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00213390
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@D@Z @ 0x00213400
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@D@Z-0x11 @ 0x00306D80
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@2@D@Z @ 0x00306D91
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x002134F0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00306DA0
// match: ??1?$pair@W4type_212C70_value@@Utype_1CB670@@@std@@QAE@XZ @ 0x00212E80

// match: ??0type_213610@@QAE@XZ @ 0x00213610
type_213610::type_213610()
{
}

// match: ??_Gtype_213610@@UAEPAXI@Z @ 0x00213630
// match: ??1type_213610@@UAE@XZ @ 0x00213660
type_213610::~type_213610()
{
}

// The selector template's members (game/options.h's unit defines them),
// repeated for this unit's instance.
// match: ??0?$type_1FCDC0@W4type_212C70_value@@@@QAE@PAW4type_212C70_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00212C70
// match: __ehhandler$??0?$type_1FCDC0@W4type_212C70_value@@@@QAE@PAW4type_212C70_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x00306D10
// match: __ehhandler$??0?$type_1FCDC0@W4type_212C70_value@@@@QAE@PAW4type_212C70_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306D18

// match: ?sub_1FCEB0@?$type_1FCDC0@W4type_212C70_value@@@@QAEXABW4type_212C70_value@@ABUtype_1CB670@@@Z @ 0x00212D00
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_212C70_value@@@@QAEXABW4type_212C70_value@@ABUtype_1CB670@@@Z-0x18 @ 0x00306D30
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_212C70_value@@@@QAEXABW4type_212C70_value@@ABUtype_1CB670@@@Z @ 0x00306D48

