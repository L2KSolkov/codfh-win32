// Split from unit_033520.cpp at 0x0348D0, where the image ends that object (its deferred
// functions come before the next out-of-line one; PLAN M7).

#include "game/frand.h"
#include "rw/ostypes.h"
#include "rw/rprandom.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/type_3CE6D0.h"
#include "types/type_3CE4B4.h"
#include "types/type_3CE4F0.h"
#include "types/type_3D3548.h"
#include "sp/sp_target.h"   // sub_3DE00 in single player
#include "types/type_3DBC78.h"
#include "types/type_3DF30.h"
#include "types/type_3D2E7C.h"
#include "types/type_67620.h"
#include "game/pooledconsts.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE4EC
extern const RwReal flt_3CE4EC = 16.666666f;

// match: ?flt_3CE4EC@@3MB @ 0x003CE4EC


// match: ??0type_3CE4F0@@QAE@XZ @ 0x000348D0
// match: ??_7type_3CE4F0@@6B@ @ 0x003CE4F0
// sp-match: ??0type_3CE4F0@@QAE@XZ @ 0x00028FD0
// symbol: ??_7type_3CE4F0@@6B@ = 0x003CE4F0
type_3CE4F0::type_3CE4F0()
{
}
// match: ??_Gtype_3CE4F0@@UAEPAXI@Z @ 0x000348F0
// match: ??1type_3CE4F0@@UAE@XZ @ 0x00034910
// sp-match: ??_Gtype_3CE4F0@@UAEPAXI@Z @ 0x000291C0
// sp-match: ??1type_3CE4F0@@UAE@XZ @ 0x00029000
type_3CE4F0::~type_3CE4F0()
{
}
// match: ?vf_00C@type_3CE4F0@@UAEHMPAUtype_3D410@@@Z @ 0x00034930
// sp-match: ?vf_00C@type_3CE4F0@@UAEHMPAUtype_3D410@@@Z @ 0x00029340
RwInt32 type_3CE4F0::vf_00C(RwReal arg_0, type_3D410 *arg_4)
{
#ifndef CODFH_SP // shape: single player reads the AI data's field straight from the call and compares it with unk_18 directly (SP 0x29340)
    AIData *var_10;
    RwUInt32 ebp_C;
#endif
    RwUInt32 v8;
    type_3D3548 *var_4;

    for (var_4 = unk_08->unk_00; var_4 != 0; var_4 = var_4->vf_118()) {
        if (((var_4->unk_2C & 0x3FFFFF0) & 0x80) != 0) {
#ifdef CODFH_SP // shape: single player reads the AI data's field straight from the call and compares it with unk_18 directly (SP 0x29340)
            v8 = var_4->vf_120()->unk_574;
            if (!(v8 != unk_18))
#else
            var_10 = var_4->vf_120();
            v8 = var_10->unk_574;
            ebp_C = unk_18;
            if (v8 == ebp_C)
#endif
                sub_34A60(static_cast<type_3DBC78 *>(var_4), arg_4);
        }
    }
    return type_3CE6D0::vf_00C(arg_0, arg_4);
}
// match: ?vf_018@type_3CE4F0@@UAEHPAUtype_3D3548@@@Z @ 0x000349D0
// sp-match: ?vf_018@type_3CE4F0@@UAEHPAUtype_3D3548@@@Z @ 0x00029010
RwInt32 type_3CE4F0::vf_018(type_3D3548 *arg_0)
{
    AIData *stk_18;
    RwUInt32 l14;
    AIData *var_10;
    RwUInt32 ebp_C;
    RwUInt32 v8;
    type_3CE6D0 *var_4;

    if (((arg_0->unk_2C >> 7) & 1) == 0)
        return 0;
    var_10 = arg_0->vf_120();
    v8 = var_10->unk_574;
    var_4 = sub_3D3E0(v8);
    if (var_4 != 0)
        return 1;
    l14 = ebp_C = unk_18;
    stk_18 = arg_0->vf_120();
    stk_18->unk_574 = l14;
    return 1;
}
// match: sub_34A60 @ 0x00034A60
// sp-match: sub_34A60 @ 0x000291D0
void type_3CE4F0::sub_34A60(type_3DBC78 *arg_0, type_3D410 *arg_4)
{
    RwInt32 var_10;
    RwInt32 ebp_C;
    RwInt32 v8;
    AIData *var_4;

    if ((arg_0->unk_28 & 1) != 0)
        return;
    var_4 = arg_0->vf_120();
    if (var_4->unk_51C == 0)
        return;
    unk_1C = 1;
    if (var_4->unk_58 == 0)
        var_4->sub_17AB0(0);
    if (((var_4->unk_49C >> 5) & 1) != 0)
        sub_34C60(arg_0, arg_4);
    if (((var_4->unk_49C >> 4) & 1) == 0)
        return;
    switch (var_4->unk_5C) {
    default:
        var_4->sub_22EF0(0);
        var_4->sub_29380(1);
        v8 = sub_12070(arg_0, (RwInt32)arg_4);
        if (var_4->unk_5C == 9)
            v8 = 0;
        if (v8 == 0 && sub_12030(0xC, arg_0, (RwInt32)arg_4, 0) == 0
                && sub_12030(0xB, arg_0, (RwInt32)arg_4, 0) == 0 && var_4->unk_5C != 9)
            sub_12030(9, arg_0, (RwInt32)arg_4, 0);
        break;
    case 0xC:
        var_4->sub_29380(1);
        ebp_C = sub_12070(arg_0, (RwInt32)arg_4);
        if (ebp_C == 0 && sub_12030(0xB, arg_0, (RwInt32)arg_4, 0) == 0)
            sub_12030(9, arg_0, (RwInt32)arg_4, 0);
        break;
    case 0xB:
        var_4->sub_22EF0(0);
        var_4->sub_29380(0);
        if (sub_12030(0xC, arg_0, (RwInt32)arg_4, 0) == 0) {
            var_10 = sub_12070(arg_0, (RwInt32)arg_4);
            if (var_10 == 0) {
                var_4->sub_29360();
                sub_12030(9, arg_0, (RwInt32)arg_4, 0);
            }
        }
    }
}
// match: sub_34C60 @ 0x00034C60
// sp-match: sub_34C60 @ 0x00029060
void type_3CE4F0::sub_34C60(type_3DBC78 *arg_0, type_3D410 *arg_4)
{
    type_154C0_80 *local_24;
    type_3D3548 *local_20;
    RwInt32 var_1C;
    RwReal var18;
    type_3D3548 *stk_14;
    RwReal l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    AIData *var_4;

    local_C = 1;
    var_4 = arg_0->vf_120();
    l10 = 1.0e37f;
    var18 = 1.0e37f;
    lv_8 = 0;
    stk_14 = 0;
    for (var_1C = 0; var_1C < 0x20; var_1C++) {
        local_24 = &var_4->unk_80[var_1C];
        local_20 = local_24->unk_00.sub_D4910();
        if (local_20 != 0) {
            if (local_C != 0 && ((local_20->unk_2C >> 4) & 1) != 0 && xor_unk_2C(arg_0, local_20)) {
                var_4->sub_18BB0(local_20);
                return;
            }
            if (sub_3DE00(arg_0, local_20) != 0) {
                if (var_4->sub_18E90(local_24, 1) != 0 && local_24->unk_0C < var18) {
                    stk_14 = local_20;
                    var18 = local_24->unk_0C;
                }
                if (local_24->unk_0C < l10) {
                    lv_8 = local_20;
                    l10 = local_24->unk_0C;
                }
            }
        }
    }
    if (stk_14 != 0) {
        if (lv_8 != 0 && l10 < 150.0f && var18 > l10)
            var_4->sub_18BB0(lv_8);
        else
            var_4->sub_18BB0(stk_14);
    } else if (lv_8 != 0 && l10 <= 1000.0f) {
        var_4->sub_18BB0(lv_8);
    }
}
// match: sub_34E20 @ 0x00034E20
// sp-match: sub_34E20 @ 0x000293A0
// Registers an A* search of type 10 for arg_0, with 100 as its data.
void sub_34E20(type_67620 *arg_0)
{
    sub_32F70(arg_0, 10, 100.0f, 0);
}
// match: sub_34E40 @ 0x00034E40
// sp-match: sub_34E40 @ 0x000293C0
// Unregisters arg_0's A* search of type 10.
void sub_34E40(type_67620 *arg_0)
{
    sub_330E0(arg_0, 10);
}
#ifdef CODFH_SP
// sp-match: ?sp_sub_1CEF0@AIData@@QAEHXZ @ 0x0001CEF0
inline RwInt32 AIData::sp_sub_1CEF0()
{
    RwUInt32 h = unk_574;
    if (sub_3D3E0(h))
    {
        RwUInt32 h2 = unk_574;
        return sub_3D3E0(h2)->vf_030();
    }
    return -1;
}
#endif

// match: sub_34E60 @ 0x00034E60
// sp-match: sub_34E60 @ 0x000293D0
// The type-10 A* search's completion (astarscheduler's sub_332D0 calls it):
// has the owner's AI object pick a cover node of the kind its state asks
// for.
RwInt32 sub_34E60(type_67620 *arg_0, RwInt32 arg_4)
{
    RwInt32 l14;
    RwUInt32 var_10;
    RwUInt32 ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    v8 = arg_0->vf_024()->sub_71300();
    var_4 = v8->vf_120();
    if (v8 != 0 && var_4 != 0) {
        if (v8->vf_010() != 0) {
            var_4->sub_244E0(0, 0xA, 0, arg_4);
        } else {
            if (v8->vf_008() != 0) {
#ifdef CODFH_SP // single player calls the inline out of line (SP 0x2942A calls SP 0x1CEF0)
                l14 = var_4->sp_sub_1CEF0();
#else
                ebp_C = var_4->unk_574;
                if (sub_3D3E0(ebp_C) != 0) {
                    var_10 = var_4->unk_574;
                    l14 = sub_3D3E0(var_10)->vf_030();
                } else {
                    l14 = -1;
                }
#endif
                if (l14 == 5 || (var_4->unk_1430 != -1) != 0) {
                    var_4->sub_244E0(0, 0xD, 1, arg_4);
                    goto done;
                }
            }
            if (var_4->get_unk_DD0() == 2)
                var_4->sub_25180(0, 0x10, 2, arg_4);
            else
                var_4->sub_244E0(0, 3, 0, arg_4);
        }
    }
done:
    return 1;
}
