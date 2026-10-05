/*
 * The host's game options (game/hostoptions.h): the options read from the
 * front end's settings copy and written back, the checks the pages'
 * widgets make, and the selectors' members and map code this unit holds.
 * The settings' read (sub_201890) reserves 16 frame bytes fewer than we do
 * around its text temporary; it is not matched yet (docs/questions.md).
 */
#include "game/hostoptions.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E8330
extern const RwReal flt_3E8330 = 0.01f;
// 0x003E8334
extern const RwReal flt_3E8334 = 0.01f;
// 0x003E8338
extern const RwReal flt_3E8338 = 16.666666f;
// 0x003E833C
extern const RwReal flt_3E833C = 0.01f;
// 0x003E8340
extern const RwReal flt_3E8340 = 0.01f;
// 0x003E8344
extern const RwReal flt_3E8344 = 16.666666f;
// 0x005044E0
RwUInt8 byte_5044E0;
// End of its data definitions.


using namespace kujuUI;

extern RwInt32 dword_4FDAA4;

// The selectors' instances, their maps' code and the actions' this unit
// holds (the other instances' copies folded into them, config/aliases.txt).
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E8330@@3MB @ 0x003E8330
// match: ?flt_3E8334@@3MB @ 0x003E8334
// match: ?flt_3E8338@@3MB @ 0x003E8338
// match: ?flt_3E833C@@3MB @ 0x003E833C
// match: ?flt_3E8340@@3MB @ 0x003E8340
// match: ?flt_3E8344@@3MB @ 0x003E8344
// match: ??_C@_08DCFFGGKK@nametext?$AA@ @ 0x003E8348
// match: ??_C@_04MEMAJGDJ@name?$AA@ @ 0x003E8354
// match: ??_C@_0L@JOCMKPNP@?$CF1?5minutes?$AA@ @ 0x003E835C
// match: ??_C@_08GFGBMIFC@?5seconds?$AA@ @ 0x003E8368
// match: ??_7type_200B90@@6B@ @ 0x003E8374
// match: ??_7?$type_1FCDC0@W4type_212C70_value@@@@6B@ @ 0x003E8378
// match: ??_7?$type_1FCDC0@W4type_214C30_value@@@@6B@ @ 0x003E8390
// match: ??_7?$type_3E7264@Utype_200B90@@@kujuUI@@6B@ @ 0x003E83A8
// match: ??_7?$type_3E7CE8@Utype_200B90@@@kujuUI@@6B@ @ 0x003E83B8
// match: ??_7?$type_1FCDC0@I@@6B@ @ 0x003E83C8
// match: __ehhandler$??0type_200B90@@QAE@_N@Z>1>8 @ 0x004221B8
// match: __ehhandler$??0type_200B90@@QAE@_N@Z>1 @ 0x00422308
// match: __ehhandler$??1type_200B90@@QAE@XZ>1>8 @ 0x00422324
// match: __ehhandler$??1type_200B90@@QAE@XZ>1 @ 0x004223DC
// match: __ehhandler$?sub_2016A0@type_200B90@@QAEXXZ>1>8 @ 0x004223F8
// match: __ehhandler$?sub_2016A0@type_200B90@@QAEXXZ>1 @ 0x00422400
// match: __ehhandler$?sub_201890@type_200B90@@QAEXXZ>1>8 @ 0x0042241C
// match: __ehhandler$?sub_201890@type_200B90@@QAEXXZ>1 @ 0x0042242C
// match: __ehhandler$??1?$type_1FCDC0@W4type_214C30_value@@@@UAE@XZ>1>8 @ 0x00422448
// match: __ehhandler$??1?$type_1FCDC0@W4type_214C30_value@@@@UAE@XZ>1 @ 0x00422450
// match: __ehhandler$??1?$type_1FCDC0@I@@UAE@XZ>1>8 @ 0x0042246C
// match: __ehhandler$??1?$type_1FCDC0@I@@UAE@XZ>1 @ 0x00422474
// match: __ehhandler$??0?$type_1FCDC0@I@@QAE@PAIPAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00422490
// match: __ehhandler$??0?$type_1FCDC0@I@@QAE@PAIPAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00422498
// match: __ehhandler$??1?$type_1FCDC0@W4type_212C70_value@@@@UAE@XZ>1>8 @ 0x004224B4
// match: __ehhandler$??1?$type_1FCDC0@W4type_212C70_value@@@@UAE@XZ>1 @ 0x004224BC
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@I@@QAEXABIABUtype_1CB670@@@Z>1>8 @ 0x004224D8
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@I@@QAEXABIABUtype_1CB670@@@Z>1 @ 0x004224F0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x0042250C
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00422514
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@ABU?$pair@$$CBIUtype_1CB670@@@2@@Z>1>8 @ 0x00422530
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@ABU?$pair@$$CBIUtype_1CB670@@@2@@Z>1 @ 0x00422538
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIUtype_1CB670@@@2@D@Z>1>8 @ 0x00422554
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIUtype_1CB670@@@2@D@Z>1>16>16 @ 0x0042256C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIUtype_1CB670@@@2@D@Z>1>16 @ 0x0042257C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIUtype_1CB670@@@2@D@Z>1 @ 0x00422590
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x004225AC
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x004225B4
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x004225D0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x004225D8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@XZ>1>8 @ 0x004225F4
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@XZ>1>16>16 @ 0x00422604
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@XZ>1>16 @ 0x00422614
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@XZ>1 @ 0x00422628

// match: ?find@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@ABW4type_214C30_value@@@Z @ 0x001FF1C0
// match: ??1type_20EC00@@UAE@XZ @ 0x00201330
// match: ??1type_212A80@@UAE@XZ @ 0x00201350
// match: ??1type_214A90@@UAE@XZ @ 0x00201370
// match: ??1?$type_1FCDC0@W4type_212C70_value@@@@UAE@XZ @ 0x00201E60
// match: __ehhandler$??1?$type_1FCDC0@W4type_212C70_value@@@@UAE@XZ-0x8 @ 0x00305510
// match: __ehhandler$??1?$type_1FCDC0@W4type_212C70_value@@@@UAE@XZ @ 0x00305518
// match: ?sub_201EC0@?$type_1FCDC0@W4type_214C30_value@@@@QAEXABW4type_214C30_value@@@Z @ 0x00201EC0
// match: ?vf_014@?$type_1FCDC0@W4type_212C70_value@@@@UAEXXZ @ 0x00201F10
// match: ??1?$type_1FCDC0@W4type_214C30_value@@@@UAE@XZ @ 0x00201F60
// match: ??0?$type_3E7264@Utype_200B90@@@kujuUI@@QAE@PAUtype_200B90@@P82@AEXXZP82@AE_NXZ@Z @ 0x00201FC0
// match: ??1?$type_3E7264@Utype_200B90@@@kujuUI@@UAE@XZ @ 0x00202010
// match: ??0?$type_3E7CE8@Utype_200B90@@@kujuUI@@QAE@PAUtype_200B90@@P82@AEXXZ@Z @ 0x00202030
// match: ??1?$type_3E7CE8@Utype_200B90@@@kujuUI@@UAE@XZ @ 0x00202070
// match: ?sub_202350@?$type_1FCDC0@I@@QAEXABI@Z @ 0x00202350
// match: ?sub_201EC0@?$type_1FCDC0@I@@QAEXABI@Z @ 0x002023E0
// match: ??0?$type_1FCDC0@I@@QAE@PAIPAUtype_1ED670_object@kujuUI@@@Z @ 0x00202090
// match: __ehhandler$??0?$type_1FCDC0@I@@QAE@PAIPAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x003054F0
// match: __ehhandler$??0?$type_1FCDC0@I@@QAE@PAIPAUtype_1ED670_object@kujuUI@@@Z @ 0x003054F8
// match: ??1?$type_1FCDC0@I@@UAE@XZ @ 0x00202120
// match: ?sub_1FCEB0@?$type_1FCDC0@I@@QAEXABIABUtype_1CB670@@@Z @ 0x002021D0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@I@@QAEXABIABUtype_1CB670@@@Z-0x18 @ 0x00305530
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@I@@QAEXABIABUtype_1CB670@@@Z @ 0x00305548
// match: ??_G?$type_1FCDC0@W4type_212C70_value@@@@UAEPAXI@Z @ 0x00202450
// match: ??_G?$type_1FCDC0@W4type_214C30_value@@@@UAEPAXI@Z @ 0x00202480
// match: ??_G?$type_3E7264@Utype_200B90@@@kujuUI@@UAEPAXI@Z @ 0x002024B0
// match: ??_G?$type_3E7CE8@Utype_200B90@@@kujuUI@@UAEPAXI@Z @ 0x002024E0
// match: ??_G?$type_1FCDC0@I@@UAEPAXI@Z @ 0x00202510
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00202800
// match: ?_Inc@const_iterator@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x00202880
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x00202910
// match: ?_Rrotate@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x00202CE0
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEXXZ @ 0x00202D90
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x00202E80
// match: ?_Lbound@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABW4type_214C30_value@@@Z @ 0x00202F50
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x00202FC0
// match: ?erase@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x00203090
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00203330
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x003055A0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x003055A8
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x002038C0
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x00203920
// match: ?clear@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@QAEXXZ @ 0x00203980
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x00203B00
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_214C30_value@@Utype_1CB670@@U?$less@W4type_214C30_value@@@std@@V?$allocator@U?$pair@$$CBW4type_214C30_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x00203B70
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@@Z @ 0x00203BE0
// match: ?sub_203CA0@?$type_1FCDC0@W4type_214C30_value@@@@QAE_NABW4type_214C30_value@@@Z @ 0x00203CA0
// match: ?sub_203CF0@?$type_1FCDC0@W4type_212C70_value@@@@QAE_NXZ @ 0x00203CF0
// match: ??$_Destroy@U_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@@std@@YAXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@0@@Z @ 0x00203D30
// match: ??1_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_212C70_value@@Utype_1CB670@@U?$less@W4type_212C70_value@@@std@@V?$allocator@U?$pair@$$CBW4type_212C70_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE@XZ @ 0x00203D50
// match: ?sub_203CA0@?$type_1FCDC0@I@@QAE_NABI@Z @ 0x00202180
// match: ?insert@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBIUtype_1CB670@@@2@@Z @ 0x002025E0
// match: ?find@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@QAE?AViterator@12@ABI@Z @ 0x00202770
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@ABU?$pair@$$CBIUtype_1CB670@@@2@@Z @ 0x00202990
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@ABU?$pair@$$CBIUtype_1CB670@@@2@@Z-0x8 @ 0x00305560
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@ABU?$pair@$$CBIUtype_1CB670@@@2@@Z @ 0x00305568
// match: ?_Init@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEXXZ @ 0x00203160
// match: ?_Lbound@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@ABI@Z @ 0x002031D0
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIUtype_1CB670@@@2@D@Z @ 0x00203240
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIUtype_1CB670@@@2@D@Z-0x11 @ 0x00305580
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBIUtype_1CB670@@@2@D@Z @ 0x00305591
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@XZ @ 0x002039E0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@IUtype_1CB670@@U?$less@I@std@@V?$allocator@U?$pair@$$CBIUtype_1CB670@@@std@@@3@$0A@@std@@@2@XZ @ 0x003055C0
// match: ?find@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@ABUtype_211860_key@@@Z @ 0x00202540
// match: ?_Lbound@?$_Tree@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@Utype_211860_key@@Utype_1CB670@@U?$less@Utype_211860_key@@@std@@V?$allocator@U?$pair@$$CBUtype_211860_key@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABUtype_211860_key@@@Z @ 0x00202E10
// match: ?sub_203CA0@?$type_1FCDC0@Utype_211860_key@@@@QAE_NABUtype_211860_key@@@Z @ 0x00203C50
// match: ?sub_201EC0@?$type_1FCDC0@Utype_211860_key@@@@QAEXABUtype_211860_key@@@Z @ 0x00201E10
// match: ??0type_200B90@@QAE@_N@Z @ 0x00200B90
// match: __ehhandler$??0type_200B90@@QAE@_N@Z-0x1FB @ 0x00305160
// match: __ehhandler$??0type_200B90@@QAE@_N@Z @ 0x0030535B

type_200B90::type_200B90(bool arg_0)
    : unk_04(this, &type_200B90::sub_201590, &type_200B90::sub_201DF0),
      unk_14(this, &type_200B90::sub_1E41C0, &type_200B90::sub_201840),
      unk_24(this, &type_200B90::sub_1E41C0, &type_200B90::sub_2015D0),
      unk_34(this, &type_200B90::sub_1E41C0, &type_200B90::sub_2015E0),
      unk_44(this, &type_200B90::sub_1E41C0, &type_200B90::sub_201610),
      unk_54(this, &type_200B90::sub_1E41C0, &type_200B90::sub_201610),
      unk_64(this, &type_200B90::sub_1E41C0, &type_200B90::sub_201640),
      unk_74(this, &type_200B90::sub_2016A0),
      unk_80(this, &type_200B90::sub_1E41C0, &type_200B90::sub_201680),
      unk_B8(0, 0),
      unk_D8(0, &unk_80),
      unk_F8(0, 0, 0x10, 1, 1, 2, 1, type_1CB670("None", 0), type_1CB670(), type_1CB670(), &unk_04),
      unk_174(0, &unk_04),
      unk_194(0, 0),
      unk_1B4(0, 0, 100, 5, 10, 10, 0, 1, &unk_34),
      unk_230(0, 0, 120, 5, 10, 10, 0, type_1CB670("None", 0), type_1CB670(), type_1CB670(" seconds", 0), 0),
      unk_2AC(0),
      unk_2CC(0, (type_214C30_value)0, &unk_44),
      unk_2EC(0, (type_214C30_value)0, &unk_64),
      unk_30C(0, (type_214C30_value)0, &unk_54),
      unk_32C(0, &unk_74),
      unk_374(0),
      unk_378(0),
      unk_39C(true),
      unk_39D(arg_0)
{
    unk_194.sub_1FCEB0(0, type_1CB670("No limit", 0));
    unk_194.sub_1FCEB0(1, type_1CB670("1 minute", 0));
    for (RwUInt32 i = 2; i != 10; i++)
    {
        type_1CB670 n;

        n.sub_202430(i);
        {
            type_1CB670 text = sub_1CB7B0("%1 minutes", n.c_str(), 0);

            unk_194.sub_1FCEB0(i, text);
        }
    }
    for (RwUInt32 j = 10; j != 65; j += 5)
    {
        type_1CB670 n;

        n.sub_202430(j);
        {
            type_1CB670 text = sub_1CB7B0("%1 minutes", n.c_str(), 0);

            unk_194.sub_1FCEB0(j, text);
        }
    }
    unk_37C.sub_1EFCF0("name", &unk_374);
    unk_37C.sub_1EFCF0("nametext", &unk_378);
}

// match: ??1type_200B90@@QAE@XZ @ 0x00201390
// match: __ehhandler$??1type_200B90@@QAE@XZ-0x12A @ 0x00305370
// match: __ehhandler$??1type_200B90@@QAE@XZ @ 0x0030549A
type_200B90::~type_200B90()
{
}

// match: ?sub_201590@type_200B90@@QAEXXZ @ 0x00201590
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_200B90::sub_201590()
{
    RwInt32 var_8;
    RwInt32 l4;

    l4 = sub_2017E0();
    var_8 = unk_F8.unk_08;

    if (l4 < var_8)
        unk_F8.sub_1E7BB0(l4);
}

// match: ?sub_2015D0@type_200B90@@QAE_NXZ @ 0x002015D0
bool type_200B90::sub_2015D0()
{
    return true;
}

// match: ?sub_2015E0@type_200B90@@QAE_NXZ @ 0x002015E0
bool type_200B90::sub_2015E0()
{
    return unk_32C.sub_1FD030() != 8;
}

// match: ?sub_201610@type_200B90@@QAE_NXZ @ 0x00201610
bool type_200B90::sub_201610()
{
    switch (unk_32C.sub_1FD030())
    {
    case 1:
        return false;
    }
    return true;
}

// match: ?sub_201640@type_200B90@@QAE_NXZ @ 0x00201640
bool type_200B90::sub_201640()
{
    switch (unk_32C.sub_1FD030())
    {
    case 1:
    case 2:
        return false;
    }
    return true;
}

// match: ?sub_201680@type_200B90@@QAE_NXZ @ 0x00201680
bool type_200B90::sub_201680()
{
    return unk_39D;
}

// The time limit's choices follow the game type: with 8 picked, "No limit"
// (0) goes (5 picked instead when it was picked, remembered in
// byte_5044E0); otherwise it comes back (picked again when it went with the
// pick). Then the options are told.
// match: ?sub_2016A0@type_200B90@@QAEXXZ @ 0x002016A0
// match: __ehhandler$?sub_2016A0@type_200B90@@QAEXXZ-0x8 @ 0x003054B0
// match: __ehhandler$?sub_2016A0@type_200B90@@QAEXXZ @ 0x003054B8
void type_200B90::sub_2016A0()
{
    if (unk_32C.sub_1FD030() == 8)
    {
        if (unk_194.sub_1FD030() == 0)
        {
            unk_194.sub_201EC0(5);
            byte_5044E0 = 1;
        }
        unk_194.sub_202350(0);
    }
    else
    {
        if (!unk_194.sub_203CA0(0))
        {
            unk_194.sub_1FCEB0(0, type_1CB670("No limit", 0));
            if (byte_5044E0)
            {
                unk_194.sub_201EC0(0);
                byte_5044E0 = 0;
            }
        }
    }
    vf_00();
}

// match: ?sub_2017E0@type_200B90@@QAEHXZ @ 0x002017E0
RwInt32 type_200B90::sub_2017E0()
{
    RwInt32 var_4 = 0;

    switch (unk_174.sub_1FD030())
    {
    case 1:
        var_4 = 4;
        break;
    case 2:
        var_4 = 8;
        break;
    case 4:
        var_4 = 0x10;
        break;
    }
    return var_4;
}

// match: ?sub_201840@type_200B90@@QAE_NXZ @ 0x00201840
bool type_200B90::sub_201840()
{
    return unk_32C.sub_1FD030() != 1 && sub_201DF0();
}

// match: ?sub_201890@type_200B90@@QAEXXZ @ 0x00201890
// match: __ehhandler$?sub_201890@type_200B90@@QAEXXZ-0x10 @ 0x003054D0
// match: __ehhandler$?sub_201890@type_200B90@@QAEXXZ @ 0x003054E0
void type_200B90::sub_201890()
{
    type_211860_key var_10(picked_level());

    unk_D8.sub_201EC0(var_10);
    unk_90.sub_1F28C0(sub_1CB720(sub_1C4320()));
    unk_32C.sub_201EC0((type_210430_value)get_4FDBB0_unk_00());
    unk_174.sub_201EC0((type_2138C0_value)dword_4F6300);
    unk_194.sub_201EC0((RwUInt32)(get_4FDBB0_unk_14() / 60.0f));
    RwUInt32 lv_14 = get_4FDBB0_unk_18();
    if (lv_14 > 100)
        lv_14 = 0;
    unk_1B4.sub_1E7BB0(lv_14);
    unk_2AC.sub_201EC0((type_212C70_value)get_4FDBB0_unk_24());
    unk_2EC.sub_201EC0((type_214C30_value)(get_4FDBB0_unk_08() != 0));
    unk_30C.sub_201EC0((type_214C30_value)(get_4FDBB0_unk_0C() != 0));
    unk_230.sub_1E7BB0((RwInt32)get_4FDBB0_unk_2C());
    unk_2CC.sub_201EC0((type_214C30_value)(get_4FDBB0_unk_10() != 0));
    unk_F8.sub_1E7BB0(dword_4FDAA4);
}

// match: ?sub_201A70@type_200B90@@QAEXXZ @ 0x00201A70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_200B90::sub_201A70()
{
    type_505188 *var_14;
    type_505188 *lv_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwUInt32 bp_4;

    var_C = 0;
    bp_8 = -1;
    bp_4 = dword_4FD970;
    for (; var_C != bp_4; var_C++)
    {
        LEVELS_CHECK(var_C);
        LEVELS_CHECK(var_C);
        lv_10 = &dword_4FD974[var_C];
        var_14 = unk_D8.sub_1FD030().get_unk_00();
        if (lv_10->sub_1A5FC0(*unk_D8.sub_1FD030().get_unk_00()))
        {
            bp_8 = var_C;
            break;
        }
    }
    sub_1C4300(unk_90.unk_08.c_str());
    unk_4FDBB0.unk_00 = unk_32C.get_value();
    sub_1C3D80(bp_8);
    dword_4F6300 = unk_174.get_value();
    unk_4FDBB0.set_unk_14((RwUInt32)(unk_194.sub_1FD030() * 60.0f));
    unk_4FDBB0.unk_18 = unk_1B4.get_unk_08();
    unk_4FDBB0.unk_24 = unk_2AC.get_value();
    unk_4FDBB0.unk_08 = unk_2EC.get_value();
    unk_4FDBB0.unk_0C = unk_30C.get_value();
    unk_4FDBB0.unk_2C = (RwReal)unk_230.get_unk_08();
    unk_4FDBB0.unk_10 = unk_2CC.get_value();
    dword_4FDAA4 = unk_F8.get_unk_08();
}

// match: ?sub_201C70@type_200B90@@QAEXXZ @ 0x00201C70
void type_200B90::sub_201C70()
{
    if (unk_374 && unk_378)
        ((cStaticText *)unk_378)->pvf_004(unk_374->sub_1F7720() ? 1 : 0);
}

// match: ?sub_201CD0@type_200B90@@QAEXXZ @ 0x00201CD0
void type_200B90::sub_201CD0()
{
    unk_388 = unk_2EC.sub_1FD030();
    unk_38C = unk_30C.sub_1FD030();
    unk_390 = unk_2CC.sub_1FD030();
    unk_394 = unk_230.get_unk_08();
    unk_398 = unk_F8.get_unk_08();
}

// match: ?sub_201D60@type_200B90@@QAEXXZ @ 0x00201D60
void type_200B90::sub_201D60()
{
    unk_2EC.sub_201EC0((const type_214C30_value &)unk_388);
    unk_30C.sub_201EC0((const type_214C30_value &)unk_38C);
    unk_2CC.sub_201EC0((const type_214C30_value &)unk_390);
    unk_230.sub_1E7BB0(unk_394);
    unk_F8.sub_1E7BB0(unk_398);
}

// match: ?sub_201DF0@type_200B90@@QAE_NXZ @ 0x00201DF0
bool type_200B90::sub_201DF0()
{
    return unk_39C;
}

// The selectors' members this unit holds (their instances here, several
// shared through /OPT:ICF with the other selectors'), and the members
// game/options.h's unit defines, repeated for this unit's instances.
// match: ??0?$type_1FCDC0@I@@QAE@PAIPAUtype_1ED670_object@kujuUI@@@Z @ 0x00202090









template <class T> type_3E7264<T>::type_3E7264(T *arg_0, void (T::*arg_4)(), bool (T::*arg_C)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
    unk_10 = arg_C;
}

// match: ?sub_202430@type_1A5EA0@@QAEAAU1@H@Z @ 0x00202430
type_1A5EA0 &type_1A5EA0::sub_202430(RwInt32 arg_0)
{
    sub_1C85D0(arg_0);
    return *this;
}

template <class T> type_3E7264<T>::~type_3E7264()
{
}

template <class T> void type_3E7264<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

template <class T> bool type_3E7264<T>::pvf_00C()
{
    return (unk_04->*unk_10)();
}

template <class T> type_3E7CE8<T>::type_3E7CE8(T *arg_0, void (T::*arg_4)())
{
    unk_04 = arg_0;
    unk_08 = arg_4;
}

template <class T> type_3E7CE8<T>::~type_3E7CE8()
{
}

template <class T> void type_3E7CE8<T>::pvf_008()
{
    (unk_04->*unk_08)();
}

// The host options' two actions (their constructors are out of line: the
// options' constructor, sub_200B90, builds them).
template struct kujuUI::type_3E7264<type_200B90>;
template struct kujuUI::type_3E7CE8<type_200B90>;

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_1E41C0@type_200B90@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_200B90::sub_1E41C0()
{
}

// ?vf_00@type_200B90@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_200B90::vf_00()
{
}
