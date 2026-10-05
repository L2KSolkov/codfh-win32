/*
 * The respawn selector (game/hostoptions.h, a member of the host options):
 * its destruction, and its option selector's instance over
 * type_20EFD0_value with that instance's map code, and its constructor.
 */
#include "game/hostoptions.h"

using namespace kujuUI;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BC@EHADLDNJ@Last?5Man?5Standing?$AA@ @ 0x003E9368
// match: ??_C@_07JGOIAFF@Respawn?$AA@ @ 0x003E937C
// match: ??_7type_20EE00@@6B@ @ 0x003E9384
// match: ??_7?$type_1FCDC0@W4type_20EFD0_value@@@@6B@ @ 0x003E939C
// match: __ehhandler$??0type_20EE00@@QAE@HH@Z>1>8 @ 0x00423798
// match: __ehhandler$??0type_20EE00@@QAE@HH@Z>1 @ 0x004237B8
// match: __ehhandler$??0?$type_1FCDC0@W4type_20EFD0_value@@@@QAE@PAW4type_20EFD0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x004237D4
// match: __ehhandler$??0?$type_1FCDC0@W4type_20EFD0_value@@@@QAE@PAW4type_20EFD0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x004237DC
// match: __ehhandler$??1?$type_1FCDC0@W4type_20EFD0_value@@@@UAE@XZ>1>8 @ 0x004237F8
// match: __ehhandler$??1?$type_1FCDC0@W4type_20EFD0_value@@@@UAE@XZ>1 @ 0x00423800
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_20EFD0_value@@@@QAEXABW4type_20EFD0_value@@ABUtype_1CB670@@@Z>1>8 @ 0x0042381C
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_20EFD0_value@@@@QAEXABW4type_20EFD0_value@@ABUtype_1CB670@@@Z>1 @ 0x00423834
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00423850
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@@Z>1 @ 0x00423858
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00423874
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x0042388C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x0042389C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@D@Z>1 @ 0x004238B0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x004238CC
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x004238D4
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x004238F0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00423900
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00423910
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00423924

// match: ??_G?$type_1FCDC0@W4type_20EFD0_value@@@@UAEPAXI@Z @ 0x0020F240
// match: ?insert@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@@Z @ 0x0020F270
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@@Z @ 0x0020F400
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@@Z-0x8 @ 0x003069C0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@@Z @ 0x003069C8
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x0020F750
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x0020F7D0
// match: ?_Init@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x0020F8A0
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@D@Z @ 0x0020F910
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@D@Z-0x11 @ 0x003069E0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@2@D@Z @ 0x003069F1
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x0020FA00
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00306A00
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00306A08
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x0020FF90
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x0020FFF0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00306A20
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_20EFD0_value@@Utype_1CB670@@U?$less@W4type_20EFD0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_20EFD0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x00210110

// "Respawn" and "Last Man Standing", with "Any" (picked) when arg_0 is 1;
// the hook arg_4.
// match: ??0type_20EE00@@QAE@HH@Z @ 0x0020EE00
// match: __ehhandler$??0type_20EE00@@QAE@HH@Z-0x23 @ 0x00306920
// match: __ehhandler$??0type_20EE00@@QAE@HH@Z @ 0x00306943
type_20EE00::type_20EE00(RwInt32 arg_0, RwInt32 arg_4) : type_1FCDC0<type_20EFD0_value>(0, (type_1ED670_object *)arg_4)
{
    sub_1FCEB0((type_20EFD0_value)1, type_1CB670("Respawn", 0));
    sub_1FCEB0((type_20EFD0_value)2, type_1CB670("Last Man Standing", 0));
    if (arg_0 == 1)
    {
        sub_1FCEB0((type_20EFD0_value)4, type_1CB670("Any", 0));
        sub_201EC0((type_20EFD0_value)4);
    }
}

// match: ??_Gtype_20EE00@@UAEPAXI@Z @ 0x0020EF80
// match: ??1type_20EE00@@UAE@XZ @ 0x0020EFB0
type_20EE00::~type_20EE00()
{
}

// The selector template's members (game/options.h's unit defines them),
// repeated for this unit's instance.
// match: ??0?$type_1FCDC0@W4type_20EFD0_value@@@@QAE@PAW4type_20EFD0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x0020EFD0
// match: __ehhandler$??0?$type_1FCDC0@W4type_20EFD0_value@@@@QAE@PAW4type_20EFD0_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x00306950
// match: __ehhandler$??0?$type_1FCDC0@W4type_20EFD0_value@@@@QAE@PAW4type_20EFD0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00306958

// match: ??1?$type_1FCDC0@W4type_20EFD0_value@@@@UAE@XZ @ 0x0020F060
// match: __ehhandler$??1?$type_1FCDC0@W4type_20EFD0_value@@@@UAE@XZ-0x8 @ 0x00306970
// match: __ehhandler$??1?$type_1FCDC0@W4type_20EFD0_value@@@@UAE@XZ @ 0x00306978

// match: ?sub_1FCEB0@?$type_1FCDC0@W4type_20EFD0_value@@@@QAEXABW4type_20EFD0_value@@ABUtype_1CB670@@@Z @ 0x0020F0C0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_20EFD0_value@@@@QAEXABW4type_20EFD0_value@@ABUtype_1CB670@@@Z-0x18 @ 0x00306990
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_20EFD0_value@@@@QAEXABW4type_20EFD0_value@@ABUtype_1CB670@@@Z @ 0x003069A8

