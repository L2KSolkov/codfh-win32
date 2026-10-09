// Split from unit_029ED0.cpp (now aidatapathing.cpp) at 0x031B90, where the image starts
// another object: its .rdata begins at 0x3CE200 with its own constants,
// the unreferenced 16.666666 every game object has among them (PLAN M7).

#include "game/clumpdata.h"
#include "types/type_3D32F8.h"
#include <xmmintrin.h>
#include <math.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
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

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE200
extern const RwReal flt_3CE200 = 16.666666f;

// match: ?flt_3CE200@@3MB @ 0x003CE200


// match: sub_31B90 @ 0x00031B90
// match: ??_C@_0DJ@PIKCDEIP@Somebody?5forgot?5to?5unregister?5in@ @ 0x003CE204
// match: ??_C@_0BD@NDDLKFNK@MaybeThrowAGrenade?$AA@ @ 0x003CE240
// match: ??_C@_0BE@FBJCJHLP@ShootingPathBlocked?$AA@ @ 0x003CE254
void sub_31B90()
{
    sub_19A750("Somebody forgot to unregister in the CanShoot Scheduler!");
}
// match: sub_31BB0 @ 0x00031BB0
// sp-match: sub_31BB0 @ 0x000270A0
void sub_31BB0(RwReal arg_0)
{
    flt_438D38.sub_72560(arg_0);
    flt_438D88.sub_72560(arg_0);
}
// match: sub_31BE0 @ 0x00031BE0
// sp-match: sub_31BE0 @ 0x000274D0
void sub_31BE0(type_3D2E7C *arg_0)
{
    if (arg_0 != 0) {
        flt_438D38.sub_72050(arg_0->sub_71340(), 0, 0, 0);
        sub_31C50(arg_0->sub_71340(), 0, 0.0f, 0);
    }
}
// match: sub_31C30 @ 0x00031C30
// sp-match: sub_31C30 @ 0x000270C0
void sub_31C30(type_3D2E7C *arg_0)
{
    if (arg_0 != 0)
        flt_438D38.sub_72240(arg_0->sub_71340());
}
// match: sub_31C50 @ 0x00031C50
// sp-match: sub_31C50 @ 0x000270E0
RwInt32 sub_31C50(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    type_3D3548 *local_24;
    AIData *local_20;
    RwInt32 var_1C;
    RwInt32 local_18;
    type_3D3548 *local_14;
    RwInt32 local_10;
    RwV3d var_C;

    local_14 = arg_0->vf_024()->sub_71300();
    var_C.x = 0.0f;
    var_C.y = 0.0f;
    var_C.z = dword_4275F0;
    local_20 = local_14->vf_120();
    local_24 = local_20->unk_1374.sub_D4910();
    if (local_14->vf_134(&var_C, local_24, local_14->vf_120()->unk_548, 0, &local_10, &local_18, -1) == 0) {
        var_1C = local_18;
        sub_6B5F0("ShootingPathBlocked", (type_67620 *)(local_14->vf_098()), 0, 0, &var_1C, 1, true, false);
        local_14->vf_120()->unk_544 = 1;
    } else {
        if (local_10 != 0 && local_14->vf_008() != 0 && local_14->vf_008()->get_unk_5E0() != 0)
            sub_6B5F0("MaybeThrowAGrenade", (type_67620 *)(local_14->vf_098()), 0, 0, 0, 0, true, false);
        local_14->vf_120()->unk_544 = 2;
    }
    return 1;
}
// match: ?sub_31DB0@@YAHPAUtype_67620@@HMH@Z @ 0x00031DB0
// sp-match: ?sub_31DB0@@YAHPAUtype_67620@@HMH@Z @ 0x002168E0
RwInt32 sub_31DB0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    return 1;
}
// match: sub_31DC0 @ 0x00031DC0
// sp-match: sub_31DC0 @ 0x00027210
void sub_31DC0(type_3D2E7C *arg_0)
{
    // The negation is an int before it is tested (neg; sbb; inc), as in an
    // RwBool-returning wrapper.
    if ((RwInt32)!flt_438D88.m_freeList.sub_16C7E0())
        flt_438D88.sub_72050(arg_0->sub_71340(), 0, 0, 0);
}
// match: sub_31E00 @ 0x00031E00
// sp-match: sub_31E00 @ 0x00027240
void sub_31E00(type_3D2E7C *arg_0)
{
    if (arg_0 != 0)
        flt_438D88.sub_72240(arg_0->sub_71340());
}
// match: sub_31E20 @ 0x00031E20
// sp-match: sub_31E20 @ 0x00027260
// The second scheduler's callback: finds up to three nodes of kind 11
// within 1000 of the entity and records them in its AI (their points in
// unk_04, their facings in unk_28, the kind-15 ones in the bits of unk_4C,
// their count in unk_50).
RwInt32 sub_31E20(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    type_3D3548 *var_4;
    AIData *var_8;
    type_4C00E8 *var_C;
    type_154C0_F80 var_88[3];
    RwInt32 var_8C;
    type_F8350 *var_90;
    RwMatrix var_110;

    var_4 = arg_0->vf_024()->sub_71300();
    var_8 = var_4->vf_120();
    var_C = &unk_4C00E8;
    type_154C0_1048 var_70;

    var_70.unk_04 = *var_4->sub_CD550();
    var_70.unk_10 = 1000.0f;
    var_70.unk_00 = 0;
    var_70.unk_18 = sub_F7E80(11);
    var_70.unk_1C = 1;
    var_70.unk_20 = var_88;
    var_70.unk_24 = 3;
    sub_F8970(&var_70, 0, 0);
    var_8->unk_50 = var_70.unk_4C;
    var_8->unk_4C = 0;
    for (var_8C = 0; var_8C < var_70.unk_4C; var_8C++) {
        var_90 = var_C->unk_2C[var_88[var_8C].unk_00];
        if (var_90->unk_04 == 0x0F)
            var_8->unk_4C |= 1 << var_8C;
        var_8->unk_04[var_8C] = var_90->unk_10;
        RtQuatConvertToMatrix(&var_90->unk_1C, &var_110);
        var_8->unk_28[var_8C] = var_110.at;
    }
    return 1;
}
