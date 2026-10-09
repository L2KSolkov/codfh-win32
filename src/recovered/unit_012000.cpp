// The first game object in link order: its code starts the image's .text at
// 0x12000. Its original file name and end boundary are not yet recovered (M1),
// so it is named for its start address.
//
// 0x12000 is the compiler-generated `vector constructor iterator'
// (??_H@YGXPAXIHP6EPAX0@Z@Z), which VC7.1 emits byte-identically into any
// object that builds an array of constructed objects; this unit's object
// emits it, and it is placed from here (only XDK library code calls it in
// the image: XnInit, the XHV voice engine, CLogonScreen).

#include "game/clumpdata.h"
#include "types/type_3D32F8.h"
#include <xmmintrin.h>
#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
// (RenderWare's Xbox header, with D3D8.h: the first object holds the copies of D3D8.h's
// selectany state tables the image keeps, 0x3CD5A0-0x3CD6A8, before its own texts.)
#include "rw/rwxbox.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "game/frand.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/vecutil.h"
#include "game/astarpathfinder.h"
#include "game/pathnodes.h"
#include "types/AIData.h"
#include "types/type_10F710.h"
#include "types/type_169D0.h"
#include "types/type_3CE6D0.h"
#include "types/type_3CE278.h"
#include "types/type_3CE5E8.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DAFC8_1DDC.h"
#include "types/type_3DBC78.h"
#include "types/type_3D2E7C.h"
#include "types/type_3DC048.h"
#include "types/type_3DC9B0.h"
#include "types/type_2CE90_50.h"
#include "types/type_3CE1FC.h"
#include "types/type_3DF30.h"
#include "types/type_427408.h"
#include "types/type_92430.h"
#include "rws/csystemcommands.h"
#include "rws/maths.h"
#include "game/pooledconsts.h"

// The handlers in the table below (defined below; the last two entries' is
// sub_170ED0, which they folded into).
RwInt32 sub_120D0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12130(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12170(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12290(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12420(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_125B0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_126B0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_127D0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12970(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12B20(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12DC0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12E50(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12EF0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_12FA0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13050(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_130F0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13150(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_131C0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13260(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13320(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13380(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_133E0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13450(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13510(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_135D0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_136C0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13830(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13900(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_139C0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13A60(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13B20(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13C20(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13DC0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13EC0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_13F60(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8);
RwInt32 sub_14020(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_140D0(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_141E0(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14340(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_143E0(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14480(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14520(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14570(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14600(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14650(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_146E0(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14770(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14800(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14930(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_149D0(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14AA0(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14C10(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_14C80(type_3DBC78 *arg_0, RwInt32 arg_4);
RwInt32 sub_170ED0(RwInt32 arg_0);

// Its data definitions (PLAN M5), in the image's address order.
// 0x00427400
RwReal flt_427400 = 90.0f;
// 0x00427408
type_427408 unk_427408[36] = {
    { 0, 0, 0 },
    { 1, sub_12290, sub_140D0 },
    { 2, sub_12970, sub_143E0 },
    { 3, sub_12B20, sub_14480 },
    { 4, sub_120D0, sub_14600 },
    { 5, sub_12DC0, sub_14C10 },
    { 6, sub_12E50, sub_14C10 },
    { 7, sub_12EF0, sub_14C10 },
    { 8, sub_12FA0, sub_14C10 },
    { 9, sub_130F0, sub_14600 },
    { 10, sub_13150, sub_14520 },
    { 11, sub_131C0, sub_14600 },
    { 12, sub_13260, sub_14570 },
    { 13, sub_13320, sub_14600 },
    { 14, sub_13380, sub_14600 },
    { 15, sub_133E0, sub_14520 },
    { 16, sub_13450, sub_14600 },
    { 17, sub_13510, sub_14650 },
    { 18, sub_135D0, sub_146E0 },
    { 19, sub_136C0, sub_14770 },
    { 20, sub_12130, sub_14600 },
    { 21, sub_13830, sub_14800 },
    { 22, sub_13900, sub_14C10 },
    { 23, sub_139C0, sub_14340 },
    { 24, sub_127D0, sub_14340 },
    { 25, sub_13C20, sub_14AA0 },
    { 26, sub_13DC0, sub_14C80 },
    { 27, sub_13B20, sub_149D0 },
    { 28, sub_13A60, sub_14930 },
    { 29, sub_13050, sub_14C10 },
    { 30, sub_13EC0, sub_14C10 },
    { 31, sub_12420, sub_141E0 },
    { 32, sub_126B0, sub_14600 },
    { 33, sub_13F60, sub_14020 },
    { 34, sub_12170, (RwInt32 (*)(type_3DBC78 *, RwInt32))(RwInt32 (*)(RwInt32))sub_170ED0 },
    { 35, sub_125B0, (RwInt32 (*)(type_3DBC78 *, RwInt32))(RwInt32 (*)(RwInt32))sub_170ED0 },
};
// 0x00438CA0
RwInt32 dword_438CA0;
// 0x00438D28
RwReal dword_438D28;
// 0x00438D2C
RwReal flt_438D2C;
// 0x00438D30
RwReal flt_438D30;
// 0x00438D34
RwReal flt_438D34;
// 0x004B8640
#ifndef CODFH_PLAIN
type_3D3548 *dword_4B8640;
#endif
// End of its data definitions.


// The unit's globals with constructors: the entity handle table (built with
// the vector constructor) and the four schedulers.
type_D48D0 unk_438CA8[32];
alfasched flt_438D38;
alfasched flt_438D88;
alfasched dword_438DE8;
alfasched dword_438E38;
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _D3DDIRTYFROMRENDERSTATE @ 0x003CD5F8
// match: _D3DSIMPLERENDERSTATEENCODE @ 0x003CD6A8
// match: _D3DDIRTYFROMTEXTURESTATE @ 0x003CD5A0
// match: ??_C@_0O@DCACNKAA@AIAction_Idle?$AA@ @ 0x003CD818
// match: ??_C@_08JCFIKFEN@StopTask?$AA@ @ 0x003CD828
// match: ??_C@_0BF@KBCLEMA@AIAction_AttackCover?$AA@ @ 0x003CD834
// match: ??_C@_0BP@PHKHHJBN@AIAction_GotoVehicleCoverPoint?$AA@ @ 0x003CD850
// match: ??_C@_0BO@HPNKNAHM@AIAction_AttackFromVehicleMMG?$AA@ @ 0x003CD870
// match: ??_C@_0BJ@OIDPCGJ@AIAction_AttackFromCover?$AA@ @ 0x003CD890
// match: ??_C@_0BF@MDPHCFNI@AIAction_AttackStand?$AA@ @ 0x003CD8AC
// match: ??_C@_0BG@PNCEPFBH@AIAction_PursueTarget?$AA@ @ 0x003CD8C4
// match: __real@42700000 @ 0x003CD8DC
// match: __real@3f800000 @ 0x003CD8E0
// match: __real@40a00000 @ 0x003CD8E4
// match: __real@30000000 @ 0x003CD8E8
// match: __real@c32f0000 @ 0x003CD8EC
// match: ??_C@_0BG@FALIGOCA@AIAction_GotoPathNode?$AA@ @ 0x003CD8F0
// match: ??_C@_0BE@DOIFOFBH@AIAction_KickDoorIn?$AA@ @ 0x003CD908
// match: ??_C@_0BD@HDPFNHKP@AIAction_EnterRoom?$AA@ @ 0x003CD91C
// match: ??_C@_0BF@NBFNOPAP@AIAction_AlertAtDoor?$AA@ @ 0x003CD930
// match: ??_C@_0BM@BNMFIAC@AIAction_ThrowGrenadeAtDoor?$AA@ @ 0x003CD948
// match: ??_C@_0BF@DBDBEKMK@AIAction_VehicleIdle?$AA@ @ 0x003CD964
// match: ??_C@_0BN@JBFIEMDA@AIAction_VehicleGotoPathNode?$AA@ @ 0x003CD97C
// match: ??_C@_0BH@HNMCLKKB@AIAction_VehiclePursue?$AA@ @ 0x003CD99C
// match: ??_C@_0BH@IEEPGGIG@AIAction_VehicleAttack?$AA@ @ 0x003CD9B4
// match: ??_C@_0BC@HKOFKPDF@AIAction_TankIdle?$AA@ @ 0x003CD9CC
// match: ??_C@_0BI@BLHKJBCL@AIAction_TankLookAround?$AA@ @ 0x003CD9E0
// match: ??_C@_0BK@EAAHPEAH@AIAction_TankGotoPathNode?$AA@ @ 0x003CD9F8
// match: ??_C@_0BE@DOIGBKPA@AIAction_TankPursue?$AA@ @ 0x003CDA14
// match: ??_C@_0BE@MHALMGNH@AIAction_TankAttack?$AA@ @ 0x003CDA28
// match: ??_C@_0BJ@GPPCMJFK@AIAction_TankAttackCover?$AA@ @ 0x003CDA3C
// match: ??_C@_0BF@EDMLFDMB@AIAction_TankRunDown?$AA@ @ 0x003CDA58
// match: ??_C@_0BL@FANIBOIN@AIAction_RetreatFromTarget?$AA@ @ 0x003CDA70
// match: ??_C@_0BI@GEOLECAJ@AIAction_AdvanceToPoint?$AA@ @ 0x003CDA8C
// match: ??_C@_0BI@LDNMDNJC@AIAction_AdvanceToCover?$AA@ @ 0x003CDAA4
// match: ??_C@_0BH@BJGEMCCN@AIAction_SoundTheAlarm?$AA@ @ 0x003CDABC
// match: ??_C@_0BN@NJLEMMCA@AIAction_GotoDefendAreaPoint?$AA@ @ 0x003CDAD4
// match: __real@4528c000 @ 0x003CDAF4
// match: __real@c2c80000 @ 0x003CDAF8
// match: .CRT$XCU+0 @ 0x00426D58
// match: .CRT$XCU+4 @ 0x00426D5C
// match: .CRT$XCU+8 @ 0x00426D60
// match: .CRT$XCU+12 @ 0x00426D64
// match: .CRT$XCU+16 @ 0x00426D68
// match: ?flt_427400@@3MA @ 0x00427400
// match: ?unk_427408@@3PAUtype_427408@@A @ 0x00427408
extern const RwReal flt_3D9488;   // astarpathfinder.cpp

extern const RwReal flt_3D9480;   // astarpathfinder.cpp


// match: _$E2 @ 0x003096E0
// match: _$E3 @ 0x0030DBF0
// match: _$E5 @ 0x00309710
// match: _$E6 @ 0x0030DC10
// match: _$E8 @ 0x00309730
// match: _$E9 @ 0x0030DC20
// match: _$E11 @ 0x00309750
// match: _$E12 @ 0x0030DC30
// match: _$E14 @ 0x00309770
// match: _$E15 @ 0x0030DC40
// match: ??_H@YGXPAXIHP6EPAX0@Z@Z @ 0x00012000
// match: sub_12030 @ 0x00012030
// sp-match: sub_12030 @ 0x000110B0
// sp-match: ??_H@YGXPAXIHP6EPAX0@Z@Z @ 0x00011050
// sp-match: _$E2 @ 0x0021C160
// sp-match: _$E5 @ 0x0021C190
// sp-match: _$E8 @ 0x0021C1B0
// sp-match: _$E11 @ 0x0021C1D0
// sp-match: _$E14 @ 0x0021C1F0
// sp-match: _$E3 @ 0x0021E020
// sp-match: _$E6 @ 0x0021E040
// sp-match: _$E9 @ 0x0021E050
// sp-match: _$E12 @ 0x0021E060
// sp-match: _$E15 @ 0x0021E070

RwInt32 sub_12030(RwInt32 arg_0, type_3DBC78 *arg_4, RwInt32 arg_8, void *arg_C)
{
    RwInt32 var_4;

    if (unk_427408[arg_0].unk_04 != 0) {
        var_4 = unk_427408[arg_0].unk_04(arg_4, arg_8, arg_C);
        return var_4;
    }
    return 0;
}

// match: sub_12070 @ 0x00012070
// sp-match: sub_12070 @ 0x000110E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_12070(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    RwInt32 local_8;

    var_4 = arg_0->vf_120();
    if (unk_427408[var_4->unk_5C].unk_08 != 0) {
        local_8 = unk_427408[var_4->unk_5C].unk_08(arg_0, arg_4);
        return local_8;
    }
    return 0;
}

// match: sub_120D0 @ 0x000120D0
// sp-match: sub_120D0 @ 0x00011120
// Record 4's first handler in unk_427408; only reached through the table.
RwInt32 sub_120D0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    sub_6B5F0("AIAction_Idle", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(4);
    return 1;
}

// match: sub_12130 @ 0x00012130
// sp-match: sub_12130 @ 0x00011170
// Record 20's first handler in unk_427408; only reached through the table.
RwInt32 sub_12130(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    var_4->unk_58 = 1;
    var_4->sub_17AB0(20);
    return 1;
}

// match: sub_12170 @ 0x00012170
// sp-match: sub_12170 @ 0x000111A0
// Record 34's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_12170(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_3D3548 *v8;
    type_F8350 *varC;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    v8 = var_4->unk_1374.sub_D4910();
    if (v8 != 0 && (var_4->sub_238E0(v8) != 0 || var_4->sub_23930() != 0)
            && var_4->sub_18E40(v8, 1) != 0) {
        varC = var_4->unk_F60;
        if (varC != 0 && var_4->sub_26A80(varC, v8, 1, 0) != 0) {
            sub_6B5F0("StopTask", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
            var_4->unk_58 = 3;
            var_4->sub_17AB0(1);
            return 1;
        }
    }
    return 0;
}

// match: sub_12290 @ 0x00012290
// sp-match: sub_12290 @ 0x00011280
// Record 1's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_12290(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *l4;
    type_3D3548 *var8;
    type_F8350 *lC;
    RwInt32 v10;
    type_3DAFC8 *local_14;
    RwReal var18;

    l4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (arg_0->vf_008() != 0) {
        local_14 = arg_0->vf_008();
        if ((local_14->unk_4E0.sub_15EF80() == 8 && (v10 = local_14->unk_4E0.unk_00) != 0) != 0)
            return 0;
    }
    var18 = l4->unk_74;
    if (var18 > 0.0f)
        return 0;
    var8 = l4->unk_1374.sub_D4910();
    if (var8 != 0) {
        lC = 0;
        lC = l4->sub_23B60();
        if (lC != 0 && ((lC->unk_00 >> 2) & 1) == 0) {
            sub_F7BA0(l4, lC, true);
            l4->sub_23670();
            l4->sub_22EF0(0);
            sub_6B5F0("AIAction_AttackCover", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
            l4->unk_58 = 1;
            l4->sub_17AB0(1);
            return 1;
        }
    }
    return 0;
}

// match: sub_12420 @ 0x00012420
// sp-match: sub_12420 @ 0x00011390
// Record 31's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_12420(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *l4;
    type_3D3548 *var8;
    type_154C0_12F4 *lC;
    type_14D180 *v10;
    RwInt32 local_14;
    type_3DAFC8 *var18;
    RwReal var_1C;

    l4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (arg_0->vf_008() != 0) {
        var18 = arg_0->vf_008();
        if ((var18->unk_4E0.sub_15EF80() == 8 && (local_14 = var18->unk_4E0.unk_00) != 0) != 0)
            return 0;
    }
    var_1C = l4->unk_74;
    if (var_1C > 0.0f)
        return 0;
    var8 = l4->unk_1374.sub_D4910();
    if (var8 != 0) {
        lC = l4->sub_23BE0();
        if (lC != 0) {
            v10 = l4->sub_23050(lC);
            if (v10 != 0) {
                l4->sub_23760();
                l4->sub_22EF0(1);
                l4->sub_22F30(0);
                sub_6B5F0("AIAction_GotoVehicleCoverPoint", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
                l4->unk_58 = 1;
                l4->sub_17AB0(31);
                return 1;
            }
        }
    }
    return 0;
}

// match: sub_125B0 @ 0x000125B0
// sp-match: sub_125B0 @ 0x000114A0
// Record 35's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_125B0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_3D3548 *v8;
    type_154C0_12F4 *varC;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    v8 = var_4->unk_1374.sub_D4910();
    if (v8 != 0 && var_4->sub_23980() != 0 && (varC = &var_4->unk_12F4) != 0
            && var_4->sub_279B0(varC, v8, 0) != 0) {
        sub_6B5F0("StopTask", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
        var_4->unk_58 = 3;
        var_4->sub_17AB0(31);
        return 1;
    }
    return 0;
}

// match: sub_126B0 @ 0x000126B0
// sp-match: sub_126B0 @ 0x00011570
// Record 32's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_126B0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *l4;
    type_3D3548 *var8;
    type_154C0_80 *lC;
    type_3D3548 *v10;
    type_3DAFC8 *local_14;
    RwInt32 var18;

    l4 = arg_0->vf_120();
    local_14 = arg_0->vf_008();
    if (local_14 == 0)
        return 0;
    var8 = local_14->unk_624.sub_D4910();
    if (var8 == 0 || var8->vf_010() == 0 || var8->vf_010()->vf_2C4() == 0)
        return 0;
    if ((var18 = local_14->unk_354) != 0x12)
        return 0;
    v10 = l4->unk_1374.sub_D4910();
    lC = l4->sub_16ED0(v10, 0);
    if (lC == 0)
        return 0;
    if (l4->sub_18E90(lC, 1) == 0)
        return 0;
    sub_6B5F0("AIAction_AttackFromVehicleMMG", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    l4->unk_58 = 1;
    l4->sub_17AB0(32);
    return 1;
}

// match: sub_127D0 @ 0x000127D0
// sp-match: sub_127D0 @ 0x00011650
// Record 24's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_127D0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_154C0_80 *loc8;
    type_3D3548 *local_C;
    type_F8350 *var_10;
    RwReal lv_14;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    lv_14 = var_4->unk_74;
    if (lv_14 > 0.0f)
        return 0;
    local_C = var_4->unk_1374.sub_D4910();
    loc8 = var_4->sub_16ED0(local_C, 0);
    if (loc8 == 0)
        return 0;
    if (var_4->sub_18E90(loc8, 1) == 0)
        return 0;
    var_10 = var_4->unk_F60;
    if (var_10 == 0)
        return 0;
    if ((var_4->unk_49C & 0x2000) != 0 && var_4->sub_205E0(&var_10->unk_10, 0.0f) == 0)
        return 0;
    if (var_4->sub_26A80(var_10, local_C, 0, 0) == 0)
        return 0;
    sub_F7BA0(var_4, var_10, true);
    var_4->sub_236F0(var_10);
    var_4->sub_22EF0(0);
    sub_6B5F0("AIAction_AttackFromCover", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(24);
    return 1;
}

// match: sub_12970 @ 0x00012970
// sp-match: sub_12970 @ 0x00011780
// Record 2's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_12970(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_154C0_80 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (local_8 == 0)
        return 0;
    if (var_4->unk_5C == 3 && var_4->sub_18E90(local_8, 0) == 0)
        return 0;
    if (var_4->sub_18F00(local_8, 1) == 0)
        return 0;
    if (arg_0->vf_114() < local_8->unk_0C && var_4->unk_5C == 3)
        return 0;
    if (var_4->unk_544 == 1 || (var_4->unk_5C == 3 && var_4->unk_544 == 0)) {
        if (arg_0->vf_14C() < local_8->unk_0C)
            return 0;
    }
    if (var_4->unk_5C == 3 && arg_0->vf_14C() < local_8->unk_0C
            && ((local_8->unk_04 >> 1) & 1) != 0 && var_4->unk_00 < flt_427400)
        return 0;
    sub_6B5F0("AIAction_AttackStand", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(2);
    return 1;
}

// match: sub_12B20 @ 0x00012B20
// sp-match: sub_12B20 @ 0x000118C0
// Record 3's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_12B20(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwReal var_2C;
    RwReal loc28;
    RwReal slot_24;
    RwReal v20;
    type_3D3548 *slot_1C;
    type_154C0_80 *local_18;
    type_154C0_12F4 *local_14;
    RwReal local_10;
    RwReal lC;
    type_3D3548 *var_8;
    AIData *l4;

    l4 = arg_0->vf_120();
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    var_8 = l4->unk_1374.sub_D4910();
    if (var_8 == 0)
        return 0;
    v20 = l4->unk_74;
    if (v20 > 0.0f)
        return 0;
    if (l4->sub_19ED0() == 0)
        return 0;
    if ((l4->unk_49C & 0x2000) != 0) {
        slot_24 = l4->unk_13E0;
        if (slot_24 > 0.0f)
            return 0;
        if (l4->sub_205E0(var_8->sub_CD550(), 0.0f) == 0) {
            lC = l4->sub_20570(arg_0->sub_CD550());
            loc28 = l4->unk_13B4;
#ifdef CODFH_SP // shape: single player compares the other way round (SP 0x118C0)
            if (lC > loc28 + -175.0f)
#else
            if (loc28 + -175.0f < lC)
#endif
                return 0;
            if (l4->sub_228A0() == 0) {
#ifdef CODFH_SP // single player calls frand_range out of line (SP 0x118C0 calls SP 0x11080)
                local_10 = frand_range(1.0f, 5.0f) * 60.0f;
#else
                var_2C = RpRandom() * (1.0f / 2147483648.0f);
                local_10 = lerp(1.0f, 5.0f, var_2C) * 60.0f;
#endif
                l4->unk_13E0 = local_10;
                return 0;
            }
        }
    }
    if (l4->sub_23980() != 0 && (local_14 = &l4->unk_12F4) != 0
            && l4->sub_279B0(local_14, var_8, 0) != 0
            && l4->sub_28890(var_8, local_14) != 0
            && (local_18 = l4->sub_16ED0(var_8, 0)) != 0
            && (slot_1C = local_14->unk_08.sub_D4910()) != 0) {
        l4->unk_58 = 3;
        l4->sub_17AB0(31);
        sub_6B5F0("StopTask", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
        return 1;
    }
    l4->sub_29380(0);
    sub_6B5F0("AIAction_PursueTarget", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    l4->unk_58 = 1;
    l4->sub_17AB0(3);
    l4->unk_00 = 0;
    return 1;
}

// match: sub_12DC0 @ 0x00012DC0
// sp-match: sub_12DC0 @ 0x00011AA0
// Record 5's first handler in unk_427408; only reached through the table.
RwInt32 sub_12DC0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    sub_6B5F0("AIAction_GotoPathNode", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(5);
    return 1;
}

// match: sub_12E50 @ 0x00012E50
// sp-match: sub_12E50 @ 0x00011B20
// Record 6's first handler in unk_427408; only reached through the table.
RwInt32 sub_12E50(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    sub_6B5F0("AIAction_KickDoorIn", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(6);
    return 1;
}

// match: sub_12EF0 @ 0x00012EF0
// sp-match: sub_12EF0 @ 0x00011BB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Record 7's first handler in unk_427408; only reached through the table.
RwInt32 sub_12EF0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    void *local_8;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    local_8 = arg_8;
    sub_6B5F0("AIAction_EnterRoom", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)(&local_8), 1, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(7);
    return 1;
}

// match: sub_12FA0 @ 0x00012FA0
// sp-match: sub_12FA0 @ 0x00011C50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Record 8's first handler in unk_427408; only reached through the table.
RwInt32 sub_12FA0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    void *local_8;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    local_8 = arg_8;
    sub_6B5F0("AIAction_AlertAtDoor", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)(&local_8), 1, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(8);
    return 1;
}

// match: sub_13050 @ 0x00013050
// sp-match: sub_13050 @ 0x00011CF0
// Record 29's first handler in unk_427408; only reached through the table.
RwInt32 sub_13050(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    sub_6B5F0("AIAction_ThrowGrenadeAtDoor", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(29);
    return 1;
}

// match: sub_130F0 @ 0x000130F0
// sp-match: sub_130F0 @ 0x00011D80
// Record 9's first handler in unk_427408; only reached through the table.
RwInt32 sub_130F0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    sub_6B5F0("AIAction_VehicleIdle", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(9);
    return 1;
}

// match: sub_13150 @ 0x00013150
// sp-match: sub_13150 @ 0x00011DD0
// Record 10's first handler in unk_427408; only reached through the table.
RwInt32 sub_13150(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (arg_0->vf_2DC() != 0)
        return 0;
    sub_6B5F0("AIAction_VehicleGotoPathNode", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(10);
    return 1;
}

// match: sub_131C0 @ 0x000131C0
// sp-match: sub_131C0 @ 0x00011E40
// Record 11's first handler in unk_427408; only reached through the table.
RwInt32 sub_131C0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (arg_0->vf_2DC() != 0)
        return 0;
    if (var_4->unk_1374.sub_D4910() == 0)
        return 0;
    if (var_4->sub_19ED0() == 0)
        return 0;
    var_4->sub_29380(0);
    sub_6B5F0("AIAction_VehiclePursue", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(11);
    return 1;
}

// match: sub_13260 @ 0x00013260
// sp-match: sub_13260 @ 0x00011ED0
// Record 12's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_13260(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_154C0_80 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
    if (local_8 == 0)
        return 0;
    if (var_4->sub_18E90(local_8, 1) == 0)
        return 0;
    if (arg_0->vf_114() < local_8->unk_0C)
        return 0;
    sub_6B5F0("AIAction_VehicleAttack", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(12);
    return 1;
}

// match: sub_13320 @ 0x00013320
// sp-match: sub_13320 @ 0x00011F70
// Record 13's first handler in unk_427408; only reached through the table.
RwInt32 sub_13320(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    sub_6B5F0("AIAction_TankIdle", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(13);
    return 1;
}

// match: sub_13380 @ 0x00013380
// sp-match: sub_13380 @ 0x00011FC0
// Record 14's first handler in unk_427408; only reached through the table.
RwInt32 sub_13380(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    sub_6B5F0("AIAction_TankLookAround", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(14);
    return 1;
}

// match: sub_133E0 @ 0x000133E0
// sp-match: sub_133E0 @ 0x00012010
// Record 15's first handler in unk_427408; only reached through the table.
RwInt32 sub_133E0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (arg_0->vf_2DC() != 0)
        return 0;
    sub_6B5F0("AIAction_TankGotoPathNode", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(15);
    return 1;
}

// match: sub_13450 @ 0x00013450
// sp-match: sub_13450 @ 0x00012080
// Record 16's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_13450(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_154C0_80 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
    if (arg_0->vf_2DC() != 0)
        return 0;
    if (local_8 == 0)
        return 0;
    if (var_4->sub_18E90(local_8, 1) == 0)
        return 0;
    var_4->sub_29380(0);
    sub_6B5F0("AIAction_TankPursue", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(16);
    return 1;
}

// match: sub_13510 @ 0x00013510
// sp-match: sub_13510 @ 0x00012120
// Record 17's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_13510(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_154C0_80 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
    if (local_8 == 0)
        return 0;
    if (var_4->sub_18E90(local_8, 1) == 0)
        return 0;
    if (arg_0->vf_114() < local_8->unk_0C)
        return 0;
    sub_6B5F0("AIAction_TankAttack", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(17);
    return 1;
}

// match: sub_135D0 @ 0x000135D0
// sp-match: sub_135D0 @ 0x000121C0
// Record 18's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_135D0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_F8350 *v8;
    type_3D3548 *varC;

    var_4 = arg_0->vf_120();
    if (((arg_0->unk_2C >> 18) & 1) == 0)
        return 0;
    varC = var_4->unk_1374.sub_D4910();
    if (varC == 0)
        return 0;
    if (arg_0->vf_2DC() != 0)
        return 0;
    v8 = 0;
    v8 = var_4->sub_23B60();
    if (v8 == 0)
        return 0;
    sub_F7BA0(var_4, v8, true);
    var_4->sub_23670();
    var_4->sub_22EF0(0);
    sub_6B5F0("AIAction_TankAttackCover", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(18);
    return 1;
}

// match: sub_136C0 @ 0x000136C0
// sp-match: sub_136C0 @ 0x00012260
// Record 19's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_136C0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *l4;
    type_3DC048 *var8;
    type_154C0_80 *lC;
    type_3D3548 *v10;
    type_3D3548 *local_14;
    type_3D3548 *var18;

    l4 = arg_0->vf_120();
    var8 = arg_0->vf_014();
    lC = l4->sub_16ED0(l4->unk_1374.sub_D4910(), 0);
    if (arg_0->vf_2DC() != 0)
        return 0;
    if (var8->unk_DC0 == 0)
        return 0;
    if (lC == 0)
        return 0;
    if (l4->sub_18E90(lC, 1) == 0)
        return 0;
    if ((v10 = l4->unk_1374.sub_D4910())->vf_010() != 0
            || ((local_14 = l4->unk_1374.sub_D4910())->vf_00C() != 0
                && (var18 = l4->unk_1374.sub_D4910())->vf_00C()->vf_200() != 0))
        return 0;
    if (var8->vf_258() < lC->unk_0C)
        return 0;
    sub_6B5F0("AIAction_TankRunDown", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    l4->unk_58 = 1;
    l4->sub_17AB0(19);
    return 1;
}

// match: sub_13830 @ 0x00013830
// sp-match: sub_13830 @ 0x00012380
// Record 21's first handler in unk_427408; only reached through the table.
RwInt32 sub_13830(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (var_4->unk_68 == 0)
        return 0;
    var_4->unk_68 = 0;
    if (var_4->unk_1374.sub_D4910() == 0)
        return 0;
    if (var_4->sub_19F30() == 0)
        return 0;
    sub_6B5F0("AIAction_RetreatFromTarget", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(21);
    return 1;
}

// match: sub_13900 @ 0x00013900
// sp-match: sub_13900 @ 0x00012420
// Record 22's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its third argument points at the point to advance to.
RwInt32 sub_13900(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwInt32 var_4;
    AIData *v8;
    RwV3d *varC;

    varC = (RwV3d *)arg_8;
    v8 = arg_0->vf_120();
    v8->unk_5B0 = *varC;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    var_4 = 0;
    sub_6B5F0("AIAction_AdvanceToPoint", (type_67620 *)(arg_0->vf_098()), 0, 0, &var_4, 1, true, false);
    v8->unk_58 = 1;
    v8->sub_17AB0(22);
    return 1;
}

// match: sub_139C0 @ 0x000139C0
// sp-match: sub_139C0 @ 0x000124C0
// Record 23's first handler in unk_427408; only reached through the table.
RwInt32 sub_139C0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    sub_6B5F0("AIAction_AdvanceToCover", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(23);
    return 1;
}

// match: sub_13A60 @ 0x00013A60
// sp-match: sub_13A60 @ 0x00012550
// Record 28's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its third argument points at the point to advance to.
RwInt32 sub_13A60(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    RwInt32 var_4;
    AIData *v8;
    RwV3d *varC;

    varC = (RwV3d *)arg_8;
    v8 = arg_0->vf_120();
    v8->unk_5B0 = *varC;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    var_4 = 1;
    sub_6B5F0("AIAction_AdvanceToPoint", (type_67620 *)(arg_0->vf_098()), 0, 0, &var_4, 1, true, false);
    v8->unk_58 = 1;
    v8->sub_17AB0(28);
    return 1;
}

// match: sub_13B20 @ 0x00013B20
// sp-match: sub_13B20 @ 0x000125F0
// Record 27's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_13B20(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;
    type_F8350 *local_8;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    local_8 = 0;
    local_8 = var_4->sub_23B60();
    if (local_8 != 0 && ((local_8->unk_00 >> 2) & 1) == 0) {
        sub_F7BA0(var_4, local_8, true);
        var_4->sub_23670();
        var_4->sub_22EF0(0);
        sub_6B5F0("AIAction_AdvanceToCover", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
        var_4->unk_58 = 1;
        var_4->sub_17AB0(27);
        return 1;
    }
    return 0;
}

// match: sub_13C20 @ 0x00013C20
// sp-match: sub_13C20 @ 0x000126B0
// Record 25's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_13C20(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *l4;
    type_154C0_80 *var8;
    type_3D3548 *lC;
    type_F8350 *v10;
    type_F8350 *local_14;
    RwInt32 var18;
    RwInt32 var_1C;
    RwInt32 l20;

    l4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    lC = l4->unk_1374.sub_D4910();
    var8 = l4->sub_16ED0(lC, 0);
    if (var8 == 0)
        return 0;
    if (l4->sub_18E90(var8, 1) == 0)
        return 0;
    if ((v10 = l4->unk_F60) != 0
            && ((var18 = l4->unk_578) == 6 || (var_1C = l4->unk_578) == 0x26
                || (l20 = l4->unk_578) == 0x2A)) {
        if (l4->sub_26A80(v10, lC, 1, 0) == 0)
            return 0;
        local_14 = l4->unk_F60;
        sub_F7BA0(l4, local_14, true);
        l4->sub_236F0(local_14);
        l4->sub_22EF0(0);
        sub_6B5F0("AIAction_AttackFromCover", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
        l4->unk_58 = 1;
        l4->sub_17AB0(25);
        return 1;
    }
    return 0;
}

// match: sub_13DC0 @ 0x00013DC0
// sp-match: sub_13DC0 @ 0x000127D0
// Record 26's first handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_13DC0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *l4;
    type_F8350 *var8;
    RwInt32 lC;
    RwInt32 v10;
    RwInt32 local_14;
    type_F8350 *var18;

    l4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if ((var8 = l4->unk_F60) != 0
            && ((lC = l4->unk_578) == 6 || (v10 = l4->unk_578) == 0x26
                || (local_14 = l4->unk_578) == 0x2A)) {
        sub_6B5F0("AIAction_Idle", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
        l4->unk_58 = 1;
        l4->sub_17AB0(26);
        return 1;
    }
    var18 = l4->unk_F60;
    return 0;
}

// match: sub_13EC0 @ 0x00013EC0
// sp-match: sub_13EC0 @ 0x00012880
// Record 30's first handler in unk_427408; only reached through the table.
RwInt32 sub_13EC0(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if ((arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: entity kind bits
        return 0;
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    sub_6B5F0("AIAction_SoundTheAlarm", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(30);
    return 1;
}

// match: sub_13F60 @ 0x00013F60
// sp-match: sub_13F60 @ 0x00012910
// Record 33's first handler in unk_427408; only reached through the table.
RwInt32 sub_13F60(type_3DBC78 *arg_0, RwInt32 arg_4, void *arg_8)
{
    AIData *var_4;

    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    var_4 = arg_0->vf_120();
    if ((var_4->unk_49C & 0x2000) == 0)
        return 0;
    if (var_4->sub_205E0(arg_0->sub_CD550(), 0.0f) != 0)
        return 0;
    sub_6B5F0("AIAction_GotoDefendAreaPoint", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, true, false);
    var_4->unk_58 = 1;
    var_4->sub_17AB0(33);
    return 1;
}

// match: sub_14020 @ 0x00014020
// sp-match: sub_14020 @ 0x000129B0
// Record 33's second handler in unk_427408; only reached through the table.
RwInt32 sub_14020(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if ((var_4->unk_49C & 0x2000) == 0)
        return 0;
    if (var_4->sub_205E0(arg_0->sub_CD550(), -175.0f) != 0)
        return 0;
    return 1;
}

// match: sub_140D0 @ 0x000140D0
// sp-match: sub_140D0 @ 0x00013390
// Record 1's second handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_140D0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_3D3548 *v8;
    type_154C0_80 *varC;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (var_4->unk_58 == 3) {
        if (sub_14CC0(arg_0, arg_4) == 0) {
            var_4->unk_58 = 0;
            return 0;
        }
        v8 = var_4->unk_1374.sub_D4910();
        if (v8 != 0 && var_4->sub_238E0(v8) != 0) {
            varC = var_4->sub_16ED0(v8, 0);
            if (((varC->unk_04 >> 1) & 1) == 0 && varC->unk_10 > 2700.0f)
                return 0;
        }
    }
    return 1;
}

// (type_3DAFC8::has_grenade_in_hand, an inline single player keeps out of line: sub_141E0 and
// sub_14AA0 call it, SP 0x12A98 and 0x12D68)
// sp-match: ?has_grenade_in_hand@type_3DAFC8@@QAEHXZ @ 0x00011020
// match: sub_141E0 @ 0x000141E0
// sp-match: sub_141E0 @ 0x00012A30
// Record 31's second handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_141E0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *l4;
    type_154C0_12F4 *var8;
    type_154C0_80 *lC;
    type_3D3548 *v10;
    RwInt32 local_14;
    type_3DAFC8 *var18;

    l4 = arg_0->vf_120();
    if (l4->unk_58 == 2 || l4->unk_58 == 4) {
        if (1) {
            l4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (l4->unk_58 == 3) {
#ifdef CODFH_SP // shape: single player calls has_grenade_in_hand out of line (SP 0x12A30 calls SP 0x11020)
        if (arg_0->vf_008() != 0 && arg_0->vf_008()->has_grenade_in_hand())
            return 1;
#else
        if (arg_0->vf_008() != 0) {
            var18 = arg_0->vf_008();
            if ((var18->unk_4E0.sub_15EF80() == 8 && (local_14 = var18->unk_4E0.unk_00) != 0) != 0)
                return 1;
        }
#endif
        if ((var8 = &l4->unk_12F4) != 0
                && l4->sub_279B0(var8, l4->unk_1374.sub_D4910(), 0) != 0) {
            v10 = l4->unk_1374.sub_D4910();
            lC = l4->sub_16ED0(v10, 0);
            if (lC != 0)
                return 1;
        }
        l4->unk_58 = 0;
        return 0;
    }
    return 1;
}

// match: sub_14340 @ 0x00014340
// sp-match: sub_14340 @ 0x000136B0
// Record 24's second handler in unk_427408; only reached through the table.
RwInt32 sub_14340(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (var_4->unk_58 == 3 && sub_14CC0(arg_0, arg_4) == 0) {
        var_4->unk_58 = 0;
        return 0;
    }
    return 1;
}

// match: sub_143E0 @ 0x000143E0
// sp-match: sub_143E0 @ 0x00013450
// Record 2's second handler in unk_427408; only reached through the table.
RwInt32 sub_143E0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (sub_14DF0(arg_0, arg_4) == 0) {
        var_4->unk_58 = 0;
        return 0;
    }
    return 1;
}

// match: sub_14480 @ 0x00014480
// sp-match: sub_14480 @ 0x000134C0
// Record 3's second handler in unk_427408; only reached through the table.
RwInt32 sub_14480(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (sub_14EA0(arg_0, arg_4) == 0) {
        var_4->unk_58 = 0;
        return 0;
    }
    return 1;
}


// match: sub_14520 @ 0x00014520
// sp-match: sub_14520 @ 0x00012B90
// Record 15's second handler in unk_427408; only reached through the table.
RwInt32 sub_14520(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (0) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    return 1;
}

// match: sub_14570 @ 0x00014570
// sp-match: sub_14570 @ 0x00013530
// Record 12's second handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_14570(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_3D3548 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = arg_0->vf_010();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (var_4->unk_58 == 3 && sub_150F0(local_8, arg_4) == 0) {
        var_4->unk_58 = 0;
        return 0;
    }
    return 1;
}

// match: sub_14600 @ 0x00014600
// sp-match: sub_14600 @ 0x00012B60
// Record 32's second handler in unk_427408; only reached through the table.
RwInt32 sub_14600(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    return 1;
}

// match: sub_14650 @ 0x00014650
// sp-match: sub_14650 @ 0x00013590
// Record 17's second handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_14650(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_3DC048 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = arg_0->vf_014();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (var_4->unk_58 == 3 && sub_150F0(local_8, arg_4) == 0) {
        var_4->unk_58 = 0;
        return 0;
    }
    return 1;
}

// match: sub_146E0 @ 0x000146E0
// sp-match: sub_146E0 @ 0x000135F0
// Record 18's second handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_146E0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_3DC048 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = arg_0->vf_014();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (var_4->unk_58 == 3 && sub_15190(local_8, arg_4) == 0) {
        var_4->unk_58 = 0;
        return 0;
    }
    return 1;
}

// match: sub_14770 @ 0x00014770
// sp-match: sub_14770 @ 0x00013650
// Record 19's second handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_14770(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_3DC048 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = arg_0->vf_014();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (var_4->unk_58 == 3 && sub_152A0(local_8, arg_4) == 0) {
        var_4->unk_58 = 0;
        return 0;
    }
    return 1;
}

// match: sub_14800 @ 0x00014800
// sp-match: sub_14800 @ 0x00012BC0
// Record 21's second handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_14800(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_154C0_80 *v8;
    type_3D3548 *varC;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    varC = var_4->unk_1374.sub_D4910();
    if (varC != 0) {
        if (varC != var_4->unk_A24.unk_50.sub_D4910()) {
            var_4->unk_58 = 0;
            return 0;
        }
    } else {
        var_4->unk_58 = 0;
        return 0;
    }
    v8 = var_4->sub_16ED0(varC, 0);
    if (v8 == 0) {
        var_4->unk_58 = 0;
        return 0;
    }
    if (arg_0->vf_114() < v8->unk_0C || arg_0->vf_144() < v8->unk_0C) {
        var_4->unk_58 = 0;
        return 0;
    }
    return 1;
}

// match: sub_14930 @ 0x00014930
// sp-match: sub_14930 @ 0x00012C90
// Record 28's second handler in unk_427408; only reached through the table.
RwInt32 sub_14930(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (0) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if ((var_4->unk_1430 != -1) == 0) {
        var_4->sub_17AB0(2);
        return 0;
    }
    return 1;
}

// match: sub_149D0 @ 0x000149D0
// sp-match: sub_149D0 @ 0x00013720
// Record 27's second handler in unk_427408; only reached through the table.
RwInt32 sub_149D0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (var_4->unk_58 == 3) {
        if (sub_14CC0(arg_0, arg_4) == 0) {
            var_4->unk_58 = 0;
            return 0;
        }
        if ((var_4->unk_1430 != -1) == 0) {
            var_4->sub_17AB0(1);
            return 0;
        }
    }
    return 1;
}

// match: sub_14AA0 @ 0x00014AA0
// sp-match: sub_14AA0 @ 0x00012D00
// Record 25's second handler in unk_427408; only reached through the table.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_14AA0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_F8350 *loc8;
    RwInt32 local_C;
    type_3DAFC8 *var_10;
    type_3DAFC8 *lv_14;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (1) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    if (var_4->unk_58 == 3) {
#ifdef CODFH_SP // shape: single player calls has_grenade_in_hand out of line (SP 0x12D00 calls SP 0x11020)
        if (arg_0->vf_008() != 0 && arg_0->vf_008()->has_grenade_in_hand())
            return 1;
#else
        if (arg_0->vf_008() != 0) {
            var_10 = arg_0->vf_008();
            if ((var_10->unk_4E0.sub_15EF80() == 8 && (local_C = var_10->unk_4E0.unk_00) != 0) != 0)
                return 1;
        }
#endif
        loc8 = var_4->unk_F60;
        if (loc8 != 0) {
            if (loc8->unk_04 == 0x11 && arg_0->vf_008() != 0) {
                lv_14 = arg_0->vf_008();
                if (lv_14->unk_618.sub_D4910() == 0)
                    return 0;
            }
            if (var_4->sub_26A80(loc8, var_4->unk_1374.sub_D4910(), 1, 0) != 0)
                return 1;
        }
        return 0;
    }
    return 1;
}

// match: sub_14C10 @ 0x00014C10
// sp-match: sub_14C10 @ 0x00012B10
// Record 30's second handler in unk_427408; only reached through the table.
RwInt32 sub_14C10(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4->unk_58 == 2 || var_4->unk_58 == 4) {
        if (0) {
            var_4->unk_58 = 0;
        }
        return 0;
    }
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    return 1;
}

// match: sub_14C80 @ 0x00014C80
// sp-match: sub_14C80 @ 0x00012DF0
// Record 26's second handler in unk_427408; only reached through the table.
RwInt32 sub_14C80(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    if (arg_0->vf_008() != 0 && arg_0->vf_008()->unk_624.sub_D4910() != 0)
        return 0;
    return 1;
}
// match: sub_14CC0 @ 0x00014CC0
// sp-match: sub_14CC0 @ 0x00012E30
// Called by sub_140D0, sub_14340 and sub_149D0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_14CC0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_F8350 *loc8;
    RwInt32 local_C;
    type_3DAFC8 *var_10;
    type_3DAFC8 *lv_14;

    var_4 = arg_0->vf_120();
    if (arg_0->vf_008() != 0) {
        var_10 = arg_0->vf_008();
        if ((var_10->unk_4E0.sub_15EF80() == 8 && (local_C = var_10->unk_4E0.unk_00) != 0) != 0)
            return 1;
    }
    loc8 = var_4->unk_F60;
    if (loc8 != 0) {
        if (loc8->unk_04 == 0x11 && arg_0->vf_008() != 0) {
            lv_14 = arg_0->vf_008();
            if (lv_14->unk_618.sub_D4910() == 0)
                return 0;
        }
        if ((var_4->unk_49C & 0x2000) != 0 && var_4->sub_205E0(&loc8->unk_10, 0.0f) == 0)
            return 0;
        if (var_4->sub_26A80(loc8, var_4->unk_1374.sub_D4910(), 1, 0) != 0)
            return 1;
    }
    return 0;
}

// match: sub_14DF0 @ 0x00014DF0
// sp-match: sub_14DF0 @ 0x00012EF0
// Called by sub_143E0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_14DF0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    RwInt32 v8;
    type_3DAFC8 *varC;

    var_4 = arg_0->vf_120();
    if (arg_0->vf_008() != 0) {
        varC = arg_0->vf_008();
        if ((varC->unk_4E0.sub_15EF80() == 8 && (v8 = varC->unk_4E0.unk_00) != 0) != 0)
            return 1;
    }
    if (var_4->unk_52C != 0 || var_4->sub_18E40(var_4->unk_1374.sub_D4910(), 1) != 0)
        return 1;
    return 0;
}

// match: sub_14EA0 @ 0x00014EA0
// sp-match: sub_14EA0 @ 0x00012F60
// Called by sub_14480.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_14EA0(type_3DBC78 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_154C0_80 *loc8;
    type_3D3548 *local_C;
    RwReal var_10;
    RwReal lv_14;

    var_4 = arg_0->vf_120();
    local_C = var_4->unk_1374.sub_D4910();
    if (local_C != 0) {
        if (local_C != var_4->unk_A24.unk_50.sub_D4910())
            return 0;
    } else {
        return 0;
    }
    loc8 = var_4->sub_16ED0(local_C, 0);
    if (loc8 == 0)
        return 0;
    if ((var_4->unk_49C & 0x2000) != 0) {
        var_10 = var_4->sub_20570(arg_0->sub_CD550());
        lv_14 = var_4->unk_13B4;
        if (var_10 > lv_14 + -100.0f && var_4->sub_205E0(local_C->sub_CD550(), 0.0f) == 0) {
            var_4->unk_13E0 = 2700.0f;
            return 0;
        }
    }
    if (var_4->sub_18E90(loc8, 0) == 0) {
        if (var_4->sub_28840(local_C) != 0)
            sub_12030(0x1F, arg_0, arg_4, 0);
        return 1;
    }
    if (arg_0->vf_114() < loc8->unk_0C) {
        if (var_4->sub_28840(local_C) != 0)
            sub_12030(0x1F, arg_0, arg_4, 0);
        return 1;
    }
    if (var_4->unk_544 == 1 || var_4->unk_544 == 0) {
        if (arg_0->vf_14C() < loc8->unk_0C) {
            if (var_4->sub_28840(local_C) != 0)
                sub_12030(0x1F, arg_0, arg_4, 0);
            return 1;
        }
    }
    if (arg_0->vf_14C() < loc8->unk_0C) {
        if (((loc8->unk_04 >> 1) & 1) != 0) {
            var_4->unk_00 = deltaTime + var_4->unk_00;
            if (var_4->unk_00 < flt_427400) {
                if (var_4->sub_28840(local_C) != 0)
                    sub_12030(0x1F, arg_0, arg_4, 0);
                return 1;
            }
        } else {
            var_4->unk_00 = 0;
        }
    }
    return 0;
}

// match: sub_150F0 @ 0x000150F0
// sp-match: sub_150F0 @ 0x000130E0
// Called by sub_14570 and sub_14650 with the entity's vf_010 entity.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_150F0(type_3D3548 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_154C0_80 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = 0;
    if (var_4->unk_1374.sub_D4910() == 0)
        return 0;
    local_8 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
    if (local_8 == 0)
        return 0;
    if (var_4->sub_18E90(local_8, 1) == 0)
        return 0;
    if (arg_0->vf_114() < local_8->unk_0C)
        return 0;
    return 1;
}
// match: sub_15190 @ 0x00015190
// sp-match: sub_15190 @ 0x00013150
// Called by sub_146E0 with the entity's vf_014 entity.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_15190(type_3DC048 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_154C0_80 *loc8;
    type_F8350 *local_C;
    type_F8350 *var_10;

    var_4 = arg_0->vf_120();
    loc8 = 0;
    if (arg_0->vf_2DC() != 0)
        return 0;
    if (var_4->unk_1374.sub_D4910() == 0)
        return 0;
    loc8 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
    if (loc8 == 0)
        return 0;
    if (var_4->sub_18E90(loc8, 1) == 0)
        return 0;
    if (arg_0->vf_114() * 1.5f < loc8->unk_0C)
        return 0;
    local_C = var_4->unk_F60;
    if (local_C != 0) {
        var_10 = var_4->unk_F60;
        if (var_4->sub_26A80(var_10, var_4->unk_1374.sub_D4910(), 1, 0) != 0)
            return 1;
    }
    return 0;
}

// match: sub_152A0 @ 0x000152A0
// sp-match: sub_152A0 @ 0x00013210
// Called by sub_14770 with the entity's vf_014 entity.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_152A0(type_3DC048 *arg_0, RwInt32 arg_4)
{
    AIData *var_4;
    type_154C0_80 *local_8;

    var_4 = arg_0->vf_120();
    local_8 = 0;
    if (arg_0->vf_2DC() != 0)
        return 0;
    if (var_4->unk_1374.sub_D4910() == 0)
        return 0;
    if (arg_0->unk_DC0 == 0)
        return 0;
    local_8 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
    if (local_8 == 0)
        return 0;
    if (var_4->sub_18E90(local_8, 1) == 0)
        return 0;
    if (arg_0->vf_258() * 1.5f < local_8->unk_0C)
        return 0;
    return 1;
}
// match: sub_15370 @ 0x00015370
// sp-match: sub_15370 @ 0x000132A0
// Called from other units (sub_33820, sub_3A9C0, sub_3AC40), which pass a
// third argument (0) that the body never reads.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwBool sub_15370(type_3DBC78 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    bool var_1;
    AIData *var8;
    type_F8350 *lC;
    RwInt32 v10;
    RwInt32 local_14;
    RwInt32 var18;

    var_1 = false;
    var8 = arg_0->vf_120();
    if ((var8->unk_49C >> 9) & 1) {
        if (var8->unk_5C != 0x19 && var8->unk_5C != 0x1A
                && (lC = var8->unk_F60) != 0
                && ((v10 = var8->unk_578) == 6 || (local_14 = var8->unk_578) == 0x26
                    || (var18 = var8->unk_578) == 0x2A))
            sub_12030(0x1A, arg_0, arg_4, 0);
    } else if (var8->unk_5C == 0x19 || var8->unk_5C == 0x1A) {
        var8->unk_58 = 3;
        var8->sub_17AB0(1);
    }
    if (var8->unk_5C == 0x19) {
        if (sub_12070(arg_0, arg_4) == 0 && sub_12030(0x1A, arg_0, arg_4, 0) == 0)
            sub_12030(4, arg_0, arg_4, 0);
        var_1 = true;
    } else if (var8->unk_5C == 0x1A) {
        if (sub_12030(0x19, arg_0, arg_4, 0) == 0)
            sub_12070(arg_0, arg_4);
        var_1 = true;
    }
    return var_1;
}






















// An inline function with an empty body, standing for whatever statement
// states 6, 38 and 42 of AIData::sub_17BF0 held (a trace compiled out,
// perhaps). Evidence: those cases get a `jmp` of their own out of the switch;
// an empty case, `{}` or `;` is folded into the switch's exit instead, and a
// call to an empty inline function is what keeps the case's own label.
inline void empty_inline()
{
}


























































































// The y axis (0, 1, 0), .rdata; the cover point's turn (sub_22C80).
extern const RwV3d stru_3CDE0C;


































// A distance (.data, 0 in the image) the search results' rescoring keeps
// them beyond (sub_23F60).
extern RwReal flt_4C0198;













// Places the owner at the cover node arg_0: its frame, taken off its
// parent, set to the node's cover orientation (sub_22C80's) at the node's
// point, with the owner's three motion vectors cleared.
// The two sides' common bits: an inline with no address, named for what it
// does. Evidence: sub_26000 ands the two side values in the order an
// inline's arguments are evaluated (right to left, into the first's register).
inline RwInt32 and_sides(RwInt32 arg_0, RwInt32 arg_4)
{
    return arg_0 & arg_4;
}













































extern RwReal flt_438D34;














// The walker's destructor, emitted with the walk above.

























// The first entity of the list sub_32750 walks (their unk_10 links it), and
// the up axis it turns a frame about.
#ifdef CODFH_PLAIN
extern type_3D3548 *&dword_4B8640;
#else
extern type_3D3548 *dword_4B8640;
#endif
