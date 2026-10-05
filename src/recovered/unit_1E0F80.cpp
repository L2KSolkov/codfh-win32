/*
 * kujuUI's name map (game/kujuui.h): objects by name, a std::map keyed by
 * type_1C8A60 (whose operator< orders it); its instantiations follow it.
 */
#include "game/kujuui.h"

namespace kujuUI {

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7out_of_range@std@@6B@ @ 0x003DA954
// match: ??_C@_0BM@PAPJHAGI@invalid?5map?1set?$DMT?$DO?5iterator?$AA@ @ 0x003DA95C
// match: ??_C@_0BE@JONHPENG@map?1set?$DMT?$DO?5too?5long?$AA@ @ 0x003DA978
// match: __CT??_R0?AVout_of_range@std@@@8??0out_of_range@std@@QAE@ABV01@@Z40 @ 0x0041D51C
// match: __CTA3?AVout_of_range@std@@ @ 0x0041D538
// match: __TI3?AVout_of_range@std@@ @ 0x0041D548
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@@Z>1>8 @ 0x0041FD28
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@@Z>1 @ 0x0041FD30
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@D@Z>1>8 @ 0x0041FD4C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@D@Z>1>16>16 @ 0x0041FD64
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@D@Z>1>16 @ 0x0041FD74
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@D@Z>1 @ 0x0041FD88
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x0041FDA4
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x0041FDAC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@XZ>1>8 @ 0x0041FDC8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@XZ>1>16>16 @ 0x0041FDD8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@XZ>1>16 @ 0x0041FDE8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@XZ>1 @ 0x0041FDFC
// match: ??_R0?AVout_of_range@std@@@8 @ 0x00429C0C

// match: ??0type_1E0F80@kujuUI@@QAE@XZ @ 0x001E0F80

type_1E0F80::type_1E0F80()
{
}

// match: ??1type_1E0F80@kujuUI@@QAE@XZ @ 0x001E0FA0
type_1E0F80::~type_1E0F80()
{
}

// match: ?sub_1E0FC0@type_1E0F80@kujuUI@@QAEPAUtype_1ED670_object@2@PBD@Z @ 0x001E0FC0
type_1ED670_object *type_1E0F80::sub_1E0FC0(const RwChar *arg_0)
{
    type_1ED670_object *var_8 = 0;
    type_1C8A60 var_4(arg_0);
    type_1E0F80_map::iterator var_C = unk_00.find(var_4);

    if (var_C != unk_00.end())
        var_8 = var_C->second;
    return var_8;
}

// match: ?sub_1E1030@type_1E0F80@kujuUI@@QAEHPBDPAUtype_1ED670_object@2@@Z @ 0x001E1030
RwInt32 type_1E0F80::sub_1E1030(const RwChar *arg_0, type_1ED670_object *arg_4)
{
    type_1C8A60 var_10(arg_0);
    type_1E0F80_map::value_type var_4(var_10, arg_4);

    RwInt32 var_C = unk_00.insert(var_4).second ? 1 : 0;

    return var_C;
}

// match: ?sub_1E1080@type_1E0F80@kujuUI@@QAEXXZ @ 0x001E1080
void type_1E0F80::sub_1E1080()
{
    unk_00.clear();
}

// match: ?sub_1E10A0@type_1E0F80@kujuUI@@QAEIXZ @ 0x001E10A0
RwUInt32 type_1E0F80::sub_1E10A0()
{
    return unk_00.size();
}

// The name map's instantiations.
// match: ?insert@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@@Z @ 0x001E10C0
// match: ?clear@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAEXXZ @ 0x001E1250
// match: ?find@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAE?AViterator@12@ABUtype_1C8A60@@@Z @ 0x001E12B0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@@Z @ 0x001E1350
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@@Z @ 0x001E13A0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@@Z-0x8 @ 0x003037E0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@@Z @ 0x003037E8
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEXXZ @ 0x001E16F0
// match: ?erase@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001E1770
// match: ?_Init@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEXXZ @ 0x001E1840
// match: ?_Lbound@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@ABUtype_1C8A60@@@Z @ 0x001E18B0
// match: ?_Rrotate@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@@Z @ 0x001E1920
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@D@Z @ 0x001E19D0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@D@Z-0x11 @ 0x00303800
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@2@D@Z @ 0x00303811
// match: ?erase@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x001E1AC0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00303820
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00303828
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@XZ @ 0x001E2040
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_1C8A60@@PAUtype_1ED670_object@kujuUI@@U?$less@Utype_1C8A60@@@std@@V?$allocator@U?$pair@$$CBUtype_1C8A60@@PAUtype_1ED670_object@kujuUI@@@std@@@5@$0A@@std@@@2@XZ @ 0x00303840
}
