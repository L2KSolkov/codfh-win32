/*
 * The front end's options page (game/options.h): its selectors' template
 * (six instances), the page's destruction and its settings read and
 * written, and its constructor (texts default-constructed out of line,
 * sub_E87E0).
 */
#include "game/options.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E7ED8
extern const RwReal flt_3E7ED8 = 0.01f;
// 0x003E7EDC
extern const RwReal flt_3E7EDC = 0.01f;
// 0x003E7EE0
extern const RwReal flt_3E7EE0 = 16.666666f;
// End of its data definitions.

using namespace kujuUI;

// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E7ED8@@3MB @ 0x003E7ED8
// match: ?flt_3E7EDC@@3MB @ 0x003E7EDC
// match: ?flt_3E7EE0@@3MB @ 0x003E7EE0
// match: ??_C@_0O@BDAFBCC@CTRL_COMMANDO?$AA@ @ 0x003E7EE4
// match: ??_C@_0N@GCMNIKGG@CTRL_SOLDIER?$AA@ @ 0x003E7EF4
// match: ??_C@_0M@PGPNCHFF@CTRL_HYBRID?$AA@ @ 0x003E7F04
// match: ??_C@_0L@MKBMEKHN@CTRL_LEFTY?$AA@ @ 0x003E7F10
// match: ??_C@_0O@KGMJLPNL@CTRL_STANDARD?$AA@ @ 0x003E7F1C
// match: ??_C@_02IAAGKKDJ@On?$AA@ @ 0x003E7F2C
// match: ??_C@_03GCDBBDDL@Off?$AA@ @ 0x003E7F30
// match: ??_C@_04HABAFPJG@Fast?$AA@ @ 0x003E7F34
// match: ??_C@_04BEGLJGGO@Slow?$AA@ @ 0x003E7F3C
// match: ??_C@_06EFAGIKOH@Normal?$AA@ @ 0x003E7F44
// match: ??_C@_04FKNHOCAN@Mono?$AA@ @ 0x003E7F4C
// match: ??_C@_06NMIAHCPF@Stereo?$AA@ @ 0x003E7F54
// match: ??_C@_0N@CLENAPJP@5?41?5Surround?$AA@ @ 0x003E7F5C
// match: ??_7?$type_1FCDC0@W4type_1FCDC0_value@@@@6B@ @ 0x003E7F6C
// match: ??_7?$type_1FCDC0@W4type_1FD050_value@@@@6B@ @ 0x003E7F84
// match: ??_7?$type_1FCDC0@W4type_1FD1C0_value@@@@6B@ @ 0x003E7F9C
// match: ??_7?$type_1FCDC0@W4type_1FD2B0_value@@@@6B@ @ 0x003E7FB4
// match: ??_7?$type_1FCDC0@W4type_1FD3A0_value@@@@6B@ @ 0x003E7FCC
// match: ??_7?$type_1FCDC0@W4type_1FD490_value@@@@6B@ @ 0x003E7FE4
// match: __ehhandler$??0type_1FC320@@QAE@PAUtype_1ED670_object@kujuUI@@000@Z>1>8 @ 0x004215D8
// match: __ehhandler$??0type_1FC320@@QAE@PAUtype_1ED670_object@kujuUI@@000@Z>1 @ 0x004216E0
// match: __ehhandler$??1type_1FC320@@QAE@XZ>1>8 @ 0x004216FC
// match: __ehhandler$??1type_1FC320@@QAE@XZ>1 @ 0x00421734
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD050_value@@@@QAE@PAW4type_1FD050_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00421750
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD050_value@@@@QAE@PAW4type_1FD050_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00421758
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD050_value@@@@UAE@XZ>1>8 @ 0x00421774
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD050_value@@@@UAE@XZ>1 @ 0x0042177C
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FCDC0_value@@@@QAEXABW4type_1FCDC0_value@@ABUtype_1CB670@@@Z>1>8 @ 0x00421798
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FCDC0_value@@@@QAEXABW4type_1FCDC0_value@@ABUtype_1CB670@@@Z>1 @ 0x004217B0
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD1C0_value@@@@QAE@PAW4type_1FD1C0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x004217CC
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD1C0_value@@@@QAE@PAW4type_1FD1C0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x004217D4
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD1C0_value@@@@UAE@XZ>1>8 @ 0x004217F0
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD1C0_value@@@@UAE@XZ>1 @ 0x004217F8
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD050_value@@@@QAEXABW4type_1FD050_value@@ABUtype_1CB670@@@Z>1>8 @ 0x00421814
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD050_value@@@@QAEXABW4type_1FD050_value@@ABUtype_1CB670@@@Z>1 @ 0x0042182C
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD3A0_value@@@@QAE@PAW4type_1FD3A0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00421848
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD3A0_value@@@@QAE@PAW4type_1FD3A0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00421850
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD2B0_value@@@@UAE@XZ>1>8 @ 0x0042186C
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD2B0_value@@@@UAE@XZ>1 @ 0x00421874
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD3A0_value@@@@QAEXABW4type_1FD3A0_value@@ABUtype_1CB670@@@Z>1>8 @ 0x00421890
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD3A0_value@@@@QAEXABW4type_1FD3A0_value@@ABUtype_1CB670@@@Z>1 @ 0x004218A8
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD490_value@@@@QAE@PAW4type_1FD490_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x004218C4
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD490_value@@@@QAE@PAW4type_1FD490_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x004218CC
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD490_value@@@@UAE@XZ>1>8 @ 0x004218E8
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD490_value@@@@UAE@XZ>1 @ 0x004218F0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD490_value@@@@QAEXABW4type_1FD490_value@@ABUtype_1CB670@@@Z>1>8 @ 0x0042190C
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD490_value@@@@QAEXABW4type_1FD490_value@@ABUtype_1CB670@@@Z>1 @ 0x00421924
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD2B0_value@@@@QAE@PAW4type_1FD2B0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x00421940
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FD2B0_value@@@@QAE@PAW4type_1FD2B0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x00421948
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD3A0_value@@@@UAE@XZ>1>8 @ 0x00421964
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FD3A0_value@@@@UAE@XZ>1 @ 0x0042196C
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD2B0_value@@@@QAEXABW4type_1FD2B0_value@@ABUtype_1CB670@@@Z>1>8 @ 0x00421988
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD2B0_value@@@@QAEXABW4type_1FD2B0_value@@ABUtype_1CB670@@@Z>1 @ 0x004219A0
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FCDC0_value@@@@QAE@PAW4type_1FCDC0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1>8 @ 0x004219BC
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FCDC0_value@@@@QAE@PAW4type_1FCDC0_value@@PAUtype_1ED670_object@kujuUI@@@Z>1 @ 0x004219C4
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FCDC0_value@@@@UAE@XZ>1>8 @ 0x004219E0
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FCDC0_value@@@@UAE@XZ>1 @ 0x004219E8
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD1C0_value@@@@QAEXABW4type_1FD1C0_value@@ABUtype_1CB670@@@Z>1>8 @ 0x00421A04
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FD1C0_value@@@@QAEXABW4type_1FD1C0_value@@ABUtype_1CB670@@@Z>1 @ 0x00421A1C
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00421A38
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@2@@Z>1 @ 0x00421A40
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00421A5C
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@2@@Z>1 @ 0x00421A64
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00421A80
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@2@@Z>1 @ 0x00421A88
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00421AA4
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@2@@Z>1 @ 0x00421AAC
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00421AC8
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@2@@Z>1 @ 0x00421AD0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@@Z>1>8 @ 0x00421AEC
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@@Z>1 @ 0x00421AF4
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00421B10
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00421B28
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00421B38
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00421B4C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00421B68
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00421B80
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00421B90
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00421BA4
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00421BC0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00421BD8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00421BE8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00421BFC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00421C18
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00421C30
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00421C40
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00421C54
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00421C70
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00421C88
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00421C98
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00421CAC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@2@D@Z>1>8 @ 0x00421CC8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@2@D@Z>1>16>16 @ 0x00421CE0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@2@D@Z>1>16 @ 0x00421CF0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@2@D@Z>1 @ 0x00421D04
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00421D20
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00421D28
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00421D44
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00421D54
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00421D64
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00421D78
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00421D94
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00421D9C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00421DB8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00421DC8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00421DD8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00421DEC
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00421E08
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00421E10
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00421E2C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00421E3C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00421E4C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00421E60
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00421E7C
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00421E84
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00421EA0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00421EB0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00421EC0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00421ED4
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00421EF0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00421EF8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00421F14
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00421F24
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00421F34
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00421F48
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x00421F64
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x00421F6C
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>8 @ 0x00421F88
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16>16 @ 0x00421F98
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1>16 @ 0x00421FA8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ>1 @ 0x00421FBC

// match: ??0type_1FC320@@QAE@PAUtype_1ED670_object@kujuUI@@000@Z @ 0x001FC320
// match: __ehhandler$??0type_1FC320@@QAE@PAUtype_1ED670_object@kujuUI@@000@Z-0x15A @ 0x00304C60
// match: __ehhandler$??0type_1FC320@@QAE@PAUtype_1ED670_object@kujuUI@@000@Z @ 0x00304DBA

type_1FC320::type_1FC320(type_1ED670_object *arg_0, type_1ED670_object *arg_4, type_1ED670_object *arg_8,
                         type_1ED670_object *arg_C)
    : unk_00(0x32, 0, 0x64, 5, 10, 10, 1, type_1CB670(), type_1CB670(), *sub_1CBAB0(), arg_4),
      unk_7C(0x32, 0, 0x64, 5, 10, 10, 1, type_1CB670(), type_1CB670(), *sub_1CBAB0(), arg_8),
      unk_F8(0, arg_0), unk_118(0, 0), unk_138(0, 0), unk_158(0, 0), unk_178(0, 0), unk_198(0, arg_C)
{
    unk_F8.sub_1FCEB0((type_1FCDC0_value)2, type_1CB670("5.1 Surround", 0));
    unk_F8.sub_1FCEB0((type_1FCDC0_value)1, type_1CB670("Stereo", 0));
    unk_F8.sub_1FCEB0((type_1FCDC0_value)0, type_1CB670("Mono", 0));
    unk_118.sub_1FCEB0((type_1FD050_value)0, type_1CB670("Normal", 0));
    unk_118.sub_1FCEB0((type_1FD050_value)1, type_1CB670("Slow", 0));
    unk_118.sub_1FCEB0((type_1FD050_value)2, type_1CB670("Fast", 0));
    unk_138.sub_1FCEB0((type_1FD1C0_value)0, type_1CB670("Off", 0));
    unk_138.sub_1FCEB0((type_1FD1C0_value)1, type_1CB670("On", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)0, type_1CB670("CTRL_STANDARD", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)1, type_1CB670("CTRL_LEFTY", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)2, type_1CB670("CTRL_HYBRID", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)3, type_1CB670("CTRL_SOLDIER", 0));
    unk_158.sub_1FCEB0((type_1FD2B0_value)4, type_1CB670("CTRL_COMMANDO", 0));
    unk_178.sub_1FCEB0((type_1FD3A0_value)0, type_1CB670("On", 0));
    unk_178.sub_1FCEB0((type_1FD3A0_value)1, type_1CB670("Off", 0));
    unk_198.sub_1FCEB0((type_1FD490_value)0, type_1CB670("On", 0));
    get_unk_198()->sub_1FCEB0((type_1FD490_value)1, type_1CB670("Off", 0));
}

// match: ??1type_1FC320@@QAE@XZ @ 0x001FCBC0
// match: __ehhandler$??1type_1FC320@@QAE@XZ-0x59 @ 0x00304DD0
// match: __ehhandler$??1type_1FC320@@QAE@XZ @ 0x00304E29
type_1FC320::~type_1FC320()
{
}

// match: ?sub_1FCC80@type_1FC320@@QAEXXZ @ 0x001FCC80
void type_1FC320::sub_1FCC80()
{
    unk_F8.sub_201EC0((type_1FCDC0_value)sub_1C4F30());
    unk_138.sub_201EC0((type_1FD1C0_value)sub_1C4FF0());
    unk_118.sub_201EC0((type_1FD050_value)sub_1C5040());
    unk_158.sub_201EC0((type_1FD2B0_value)sub_1C5100());
    unk_178.sub_201EC0((type_1FD3A0_value)sub_1C5160());
}

// match: ?sub_1FCD10@type_1FC320@@QAEXXZ @ 0x001FCD10
void type_1FC320::sub_1FCD10()
{
    sub_1C4F70(unk_F8.sub_1FD030());
    sub_1C5020(unk_138.sub_1FD030());
    sub_1C5080(unk_118.sub_1FD030());
    sub_1C5120(unk_158.sub_1FD030());
    sub_1C5180(unk_178.sub_1FD030());
    sub_1C51D0(unk_198.sub_1FD030());
    byte_4FDAA8 = 1;
}

// The selectors' deleting destructors and their maps' instantiations.
// match: ??_G?$type_1FCDC0@W4type_1FCDC0_value@@@@UAEPAXI@Z @ 0x001FD580
// match: ??_G?$type_1FCDC0@W4type_1FD050_value@@@@UAEPAXI@Z @ 0x001FD5B0
// match: ??_G?$type_1FCDC0@W4type_1FD1C0_value@@@@UAEPAXI@Z @ 0x001FD5E0
// match: ??_G?$type_1FCDC0@W4type_1FD2B0_value@@@@UAEPAXI@Z @ 0x001FD610
// match: ??_G?$type_1FCDC0@W4type_1FD3A0_value@@@@UAEPAXI@Z @ 0x001FD640
// match: ??_G?$type_1FCDC0@W4type_1FD490_value@@@@UAEPAXI@Z @ 0x001FD670
// match: ?insert@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@@Z @ 0x001FD6A0
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001FD830
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@@Z @ 0x001FD8B0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@@Z-0x8 @ 0x00304EB0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@@Z @ 0x00304EB8
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001FDC00
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001FDC80
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001FDD00
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001FDD80
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001FDE00
// match: ?_Dec@const_iterator@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001FDE80
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001FDF40
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001FE010
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001FE0E0
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001FE1B0
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001FE280
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x001FE350
// match: ?_Init@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXXZ @ 0x001FE420
// match: ?_Lrotate@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x001FE490
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@D@Z @ 0x001FE540
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@D@Z-0x11 @ 0x00304ED0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@2@D@Z @ 0x00304EE1
// match: ?erase@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x001FE630
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00304F00
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00304F08
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001FEBC0
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001FEC20
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001FEC80
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001FECE0
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001FED40
// match: ?clear@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@QAEXXZ @ 0x001FEDA0
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x001FEE00
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@XZ @ 0x00304EF0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FCDC0_value@@Utype_1CB670@@U?$less@W4type_1FCDC0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FCDC0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x001FEF20
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD050_value@@Utype_1CB670@@U?$less@W4type_1FD050_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD050_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x001FEF90
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD1C0_value@@Utype_1CB670@@U?$less@W4type_1FD1C0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD1C0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x001FF000
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD2B0_value@@Utype_1CB670@@U?$less@W4type_1FD2B0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD2B0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x001FF070
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD3A0_value@@Utype_1CB670@@U?$less@W4type_1FD3A0_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD3A0_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x001FF0E0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@W4type_1FD490_value@@Utype_1CB670@@U?$less@W4type_1FD490_value@@@std@@V?$allocator@U?$pair@$$CBW4type_1FD490_value@@Utype_1CB670@@@std@@@4@$0A@@std@@@2@@Z @ 0x001FF150

// match: ??0?$type_1FCDC0@W4type_1FCDC0_value@@@@QAE@PAW4type_1FCDC0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x001FCDC0
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FCDC0_value@@@@QAE@PAW4type_1FCDC0_value@@PAUtype_1ED670_object@kujuUI@@@Z-0x8 @ 0x00304E70
// match: __ehhandler$??0?$type_1FCDC0@W4type_1FCDC0_value@@@@QAE@PAW4type_1FCDC0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x00304E78
// match: ??0?$type_1FCDC0@W4type_1FD050_value@@@@QAE@PAW4type_1FD050_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x001FD050
// match: ??0?$type_1FCDC0@W4type_1FD1C0_value@@@@QAE@PAW4type_1FD1C0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x001FD1C0
// match: ??0?$type_1FCDC0@W4type_1FD2B0_value@@@@QAE@PAW4type_1FD2B0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x001FD2B0
// match: ??0?$type_1FCDC0@W4type_1FD3A0_value@@@@QAE@PAW4type_1FD3A0_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x001FD3A0
// match: ??0?$type_1FCDC0@W4type_1FD490_value@@@@QAE@PAW4type_1FD490_value@@PAUtype_1ED670_object@kujuUI@@@Z @ 0x001FD490

// match: ??1?$type_1FCDC0@W4type_1FCDC0_value@@@@UAE@XZ @ 0x001FCE50
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FCDC0_value@@@@UAE@XZ-0x8 @ 0x00304E90
// match: __ehhandler$??1?$type_1FCDC0@W4type_1FCDC0_value@@@@UAE@XZ @ 0x00304E98
// match: ??1?$type_1FCDC0@W4type_1FD050_value@@@@UAE@XZ @ 0x001FD0E0
// match: ??1?$type_1FCDC0@W4type_1FD1C0_value@@@@UAE@XZ @ 0x001FD250
// match: ??1?$type_1FCDC0@W4type_1FD2B0_value@@@@UAE@XZ @ 0x001FD340
// match: ??1?$type_1FCDC0@W4type_1FD3A0_value@@@@UAE@XZ @ 0x001FD430
// match: ??1?$type_1FCDC0@W4type_1FD490_value@@@@UAE@XZ @ 0x001FD520

// match: ?sub_1FCEB0@?$type_1FCDC0@W4type_1FCDC0_value@@@@QAEXABW4type_1FCDC0_value@@ABUtype_1CB670@@@Z @ 0x001FCEB0
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FCDC0_value@@@@QAEXABW4type_1FCDC0_value@@ABUtype_1CB670@@@Z-0x18 @ 0x00304E40
// match: __ehhandler$?sub_1FCEB0@?$type_1FCDC0@W4type_1FCDC0_value@@@@QAEXABW4type_1FCDC0_value@@ABUtype_1CB670@@@Z @ 0x00304E58

// match: ?sub_1FD030@?$type_1FCDC0@W4type_1FCDC0_value@@@@QAEABW4type_1FCDC0_value@@XZ @ 0x001FD030

// match: ?vf_010@?$type_1FCDC0@W4type_1FCDC0_value@@@@UAE_NXZ @ 0x001FD140

