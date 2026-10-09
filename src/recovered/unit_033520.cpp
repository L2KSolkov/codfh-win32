// The unit after Source\GameCore\ai\astarscheduler.cpp: it starts at 0x33520
// with type_3CE4B4, the kind-0 object sub_3CE20 creates, followed by the
// kind-3 object type_3CE4F0 (from sub_348D0). Its original file name and end
// boundary are not yet recovered (M1), so it is named for its start address.

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
#include "types/type_3DBC78.h"
#include "types/type_3DF30.h"
#include "types/type_3D2E7C.h"
#include "types/type_67620.h"
#include "game/pooledconsts.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE4B0
extern const RwReal flt_3CE4B0 = 16.666666f;
// 0x00438E84
RwInt32 dword_438E84;
// End of its data definitions.


// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// match: ?flt_3CE4B0@@3MB @ 0x003CE4B0
// match: ??_7type_3CE4B4@@6B@ @ 0x003CE4B4

// match: ??0type_3CE4B4@@QAE@XZ @ 0x00033520
// sp-match: ??0type_3CE4B4@@QAE@XZ @ 0x000282E0
// symbol: ??_7type_3CE4B4@@6B@ = 0x003CE4B4
// symbol: ?vf_008@type_3CE6D0@@UAEXXZ = 0x001E41C0
type_3CE4B4::type_3CE4B4()
{
}

// match: ??_Gtype_3CE4B4@@UAEPAXI@Z @ 0x00033540
// match: ??1type_3CE4B4@@UAE@XZ @ 0x00033560
// sp-match: ??_Gtype_3CE4B4@@UAEPAXI@Z @ 0x00028590
// sp-match: ??1type_3CE4B4@@UAE@XZ @ 0x00028310
type_3CE4B4::~type_3CE4B4()
{
}

// match: ?vf_004@type_3CE4B4@@UAEXPAUtype_3DF30@@@Z @ 0x00033580
// sub_33580: also type_3CE4F0's slot +0x004, folded by /OPT:ICF.
void type_3CE4B4::vf_004(type_3DF30 *arg_0)
{
    unk_1C = 0;
    type_3CE6D0::vf_004(arg_0);
}

// match: ?vf_008@type_3CE4B4@@UAEXXZ @ 0x000335B0
// sp-match: ?vf_008@type_3CE4B4@@UAEXXZ @ 0x00028330
void type_3CE4B4::vf_008()
{
    type_3CE6D0::vf_008();
    dword_438E84 = 0;
}

// match: ?vf_00C@type_3CE4B4@@UAEHMPAUtype_3D410@@@Z @ 0x000335D0
// sp-match: ?vf_00C@type_3CE4B4@@UAEHMPAUtype_3D410@@@Z @ 0x00028ED0
RwInt32 type_3CE4B4::vf_00C(RwReal arg_0, type_3D410 *arg_4)
{
    type_3D3548 *var_4;
#ifndef CODFH_SP // shape: single player reads the AI data's field straight from the call, into a loop-scoped local (SP 0x28ED0)
    RwUInt32 v8;
#endif
    RwUInt32 stk_C;
#ifndef CODFH_SP // shape: single player reads the AI data's field straight from the call, into a loop-scoped local (SP 0x28ED0)
    AIData *var_10;
#endif

    for (var_4 = unk_08->unk_00; var_4 != 0; var_4 = var_4->vf_118()) {
#ifdef CODFH_SP // shape: single player reads the AI data's field straight from the call, into a loop-scoped local (SP 0x28ED0)
        RwUInt32 v8;
        v8 = var_4->vf_120()->unk_574;
#else
        var_10 = var_4->vf_120();
        v8 = var_10->unk_574;
#endif
        stk_C = unk_18;
        if (v8 == stk_C)
            sub_33820(static_cast<type_3DBC78 *>(var_4), arg_4);
    }
    return type_3CE6D0::vf_00C(arg_0, arg_4);
}

// match: ?vf_018@type_3CE4B4@@UAEHPAUtype_3D3548@@@Z @ 0x00033660
// sp-match: ?vf_018@type_3CE4B4@@UAEHPAUtype_3D3548@@@Z @ 0x000285A0
RwInt32 type_3CE4B4::vf_018(type_3D3548 *arg_0)
{
    if (((arg_0->unk_2C >> 18) & 1) != 0 || ((arg_0->unk_2C >> 7) & 1) != 0)
        return 0;
    return sub_336C0(arg_0);
}

// match: ?vf_01C@type_3CE4B4@@UAEHPAUtype_3D3548@@@Z @ 0x000336A0
// sp-match: ?vf_01C@type_3CE4B4@@UAEHPAUtype_3D3548@@@Z @ 0x000285C0
RwInt32 type_3CE4B4::vf_01C(type_3D3548 *arg_0)
{
    return sub_336C0(arg_0);
}

// match: sub_336C0 @ 0x000336C0
// sp-match: sub_336C0 @ 0x00028340
RwInt32 type_3CE4B4::sub_336C0(type_3D3548 *arg_0)
{
    AIData *l4;
    type_3CE6D0 *var_8;
    type_3D3548 *fp_C;
    type_F8350 *local_10;
    RwUInt32 stk_14;
    RwUInt32 lcl_18;
    RwUInt32 fp_1C;

    l4 = arg_0->vf_120();
    stk_14 = l4->unk_574;
    var_8 = sub_3D3E0(stk_14);
    if (var_8 != 0) {
        if (var_8 == this)
            return 1;
        var_8->vf_014(arg_0);
    }
    fp_1C = lcl_18 = unk_18;
    l4->unk_574 = fp_1C;
    l4->unk_DD8 = 1;
    switch (l4->unk_5C) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 0x15:
    case 0x18:
    case 0x20:
        break;
    case 0x17:
        if (l4->sub_238E0(0) != 0 || l4->sub_23930() != 0) {
            fp_C = l4->unk_1374.sub_D4910();
            local_10 = l4->unk_F60;
            if (fp_C != 0 && local_10 != 0 && l4->sub_26A80(local_10, fp_C, 1, 0) != 0) {
                l4->sub_17AB0(1);
                break;
            }
        }
    default:
        l4->sub_17AB0(0);
    }
    return 1;
}

// match: sub_33820 @ 0x00033820
// sp-match: sub_33820 @ 0x000285D0
// Runs the member arg_0 through its action handlers (sub_12030, sub_12070)
// by its current action unk_5C, then its unk_1430 order (vf_034).
void type_3CE4B4::sub_33820(type_3DBC78 *arg_0, type_3D410 *arg_4)
{
    bool local_5;
    AIData *var_4;

    if (arg_0->unk_24 == 0xE)
        return;
    if ((arg_0->unk_28 & 1) != 0)
        return;
    var_4 = arg_0->vf_120();
    if (var_4->unk_51C == 0)
        return;
    unk_1C = 1;
    if (var_4->unk_58 == 0)
        var_4->sub_17AB0(0);
    if (((var_4->unk_49C >> 5) & 1) != 0)
        sub_34720(arg_0, arg_4);
    if (var_4->unk_530 != 0 && var_4->unk_58 == 3)
        return;
    if (((var_4->unk_49C >> 4) & 1) == 0)
        return;
    local_5 = false;
    if (var_4->unk_70 != 0) {
        var_4->unk_58 = 2;
        var_4->unk_70 = 0;
    }
    local_5 = sub_15370(arg_0, (RwInt32)arg_4, 0) ? true : false;
    if (!local_5) {
        switch (var_4->unk_5C) {
        // Cases 0 and 4 have jump-table entries of their own that lead to
        // the default's code; labels written right before `default:` are
        // folded into it, so a statement stands between them.
        case 0:
        case 4:
            ;
        default: {
            type_154C0_80 *var_10;
            RwInt32 var_C;

            var_4->sub_29380(1);
            var_C = 0;
            if (var_4->unk_4E0 != 0) {
                if (sub_12030(0x20, arg_0, (RwInt32)arg_4, 0) == 0 && var_C == 0)
                    sub_12030(0x14, arg_0, (RwInt32)arg_4, 0);
                if ((var_4->unk_49C & 0x2000) != 0)
                    var_4->sub_204E0();
            } else if (var_C == 0 && sub_12030(0x22, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(0x23, arg_0, (RwInt32)arg_4, 0) == 0) {
                var_10 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
                if (var_10 != 0 && arg_0->vf_114() < var_10->unk_0C) {
                    if (sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0
                            && sub_12030(1, arg_0, (RwInt32)arg_4, 0) == 0
                            && sub_12030(0x1F, arg_0, (RwInt32)arg_4, 0) == 0
                            && sub_12030(2, arg_0, (RwInt32)arg_4, 0) == 0
                            && (var_4->unk_1374.sub_D4910() == 0
                                || sub_12030(0x21, arg_0, (RwInt32)arg_4, 0) == 0)) {
                        if (var_4->unk_5C == 4 && sub_12070(arg_0, (RwInt32)arg_4) == 0)
                            var_4->sub_17AB0(0);
                        if (var_4->unk_5C != 4)
                            sub_12030(4, arg_0, (RwInt32)arg_4, 0);
                    }
                } else if (sub_12030(1, arg_0, (RwInt32)arg_4, 0) == 0
                        && sub_12030(0x1F, arg_0, (RwInt32)arg_4, 0) == 0
                        && sub_12030(2, arg_0, (RwInt32)arg_4, 0) == 0
                        && sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0
                        && (var_4->unk_1374.sub_D4910() == 0
                            || sub_12030(0x21, arg_0, (RwInt32)arg_4, 0) == 0)) {
                    if (var_4->unk_5C == 4 && sub_12070(arg_0, (RwInt32)arg_4) == 0)
                        var_4->sub_17AB0(0);
                    if (var_4->unk_5C != 4)
                        sub_12030(4, arg_0, (RwInt32)arg_4, 0);
                }
            }
            break;
        }
        case 0x15: {
            RwInt32 var_14;

            var_4->sub_22EF0(1);
            var_4->sub_29380(1);
            if (sub_12030(0x22, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(1, arg_0, (RwInt32)arg_4, 0) == 0
                    && (var_14 = sub_12070(arg_0, (RwInt32)arg_4)) == 0
                    && sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0)
                sub_12030(4, arg_0, (RwInt32)arg_4, 0);
            break;
        }
        case 0x14:
            if (sub_12030(0x20, arg_0, (RwInt32)arg_4, 0) == 0 && var_4->unk_4E0 == 0)
                sub_12030(4, arg_0, (RwInt32)arg_4, 0);
            break;
        case 0x20: {
            RwInt32 var_18;

            var_18 = sub_12070(arg_0, (RwInt32)arg_4);
            if (var_18 == 0 && sub_12030(0x20, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(0x14, arg_0, (RwInt32)arg_4, 0) == 0 && var_4->unk_4E0 == 0)
                sub_12030(4, arg_0, (RwInt32)arg_4, 0);
            break;
        }
        case 2: {
            RwInt32 local_28;
            type_154C0_80 *local_24;
            RwInt32 local_20;
            RwInt32 var_1C;

            var_4->sub_22EF0(1);
            var_4->sub_29380(1);
            var_1C = 1;
            if (sub_12030(0x22, arg_0, (RwInt32)arg_4, 0) != 0
                    || sub_12030(1, arg_0, (RwInt32)arg_4, 0) != 0
                    || sub_12030(0x1F, arg_0, (RwInt32)arg_4, 0) != 0)
                var_1C = 0;
            if (var_4->sub_17B40() > 30.0f && var_1C != 0
                    && sub_12030(0x21, arg_0, (RwInt32)arg_4, 0) != 0)
                var_1C = 0;
            if (var_1C != 0 && sub_12030(0x15, arg_0, (RwInt32)arg_4, 0) == 0) {
                local_28 = sub_12070(arg_0, (RwInt32)arg_4);
                local_20 = var_4->unk_6C;
                var_4->unk_6C = 0;
                local_24 = var_4->sub_16ED0(var_4->unk_1374.sub_D4910(), 0);
                if (local_24 != 0 && arg_0->vf_114() + 200.0f < local_24->unk_0C) {
                    if (sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0 && local_28 == 0)
                        sub_12030(4, arg_0, (RwInt32)arg_4, 0);
                } else if ((local_28 == 0 || local_20 != 0)
                        && sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0 && local_28 == 0) {
                    sub_12030(4, arg_0, (RwInt32)arg_4, 0);
                }
            }
            break;
        }
        case 3: {
            RwInt32 var_2C;

            var_4->sub_22EF0(1);
            var_4->sub_29380(0);
            if (sub_12030(0x22, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(0x18, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(1, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(2, arg_0, (RwInt32)arg_4, 0) == 0
                    && (var_2C = sub_12070(arg_0, (RwInt32)arg_4)) == 0)
                sub_12030(4, arg_0, (RwInt32)arg_4, 0);
            break;
        }
        case 0x1B:
            var_4->sub_22EF0(0);
            var_4->sub_29380(0);
            if ((var_4->unk_1430 != -1) == 0 || sub_12070(arg_0, (RwInt32)arg_4) == 0) {
                var_4->sub_1A5A0(-1);
                var_4->sub_17AB0(0);
            }
            break;
        case 0x1C:
            var_4->sub_29380(0);
            if ((var_4->unk_1430 != -1) == 0 || sub_12070(arg_0, (RwInt32)arg_4) == 0) {
                var_4->sub_1A5A0(-1);
                var_4->sub_17AB0(0);
            }
            break;
        case 1: {
            type_154C0_80 *local_50;
            RwInt32 stk_4C;
            type_3D3548 *loc48;
            RwInt32 var_44;
            RwInt32 ebp_40;
            RwInt32 local_3C;
            type_F8350 *var_38;
            type_3D3548 *var_34;
            RwInt32 local_30;

            var_4->sub_29380(1);
            local_30 = sub_12070(arg_0, (RwInt32)arg_4);
            if (local_30 != 0) {
                var_34 = var_4->unk_1374.sub_D4910();
                if (var_34 != 0 && var_4->sub_238E0(var_34) != 0) {
                    var_38 = var_4->unk_F60;
                    if (var_38 != 0) {
                        local_3C = var_38->unk_04;
                        if (local_3C == 0xE) {
                            if (var_4->get_unk_57C() > 360.0f) {
                                ebp_40 = 0;
                                if (var_38 != var_4->get_unk_F54())
                                    ebp_40 = sub_12030(1, arg_0, (RwInt32)arg_4, 0);
                                if (ebp_40 == 0)
                                    ebp_40 = sub_12030(3, arg_0, (RwInt32)arg_4, 0);
                            }
                        } else if (local_3C == 0x13 || local_3C == 0xB) {
#ifdef CODFH_SP // shape: frand_range kept out of line (SP 0x11080)
                            if (var_38 != var_4->get_unk_F54()
                                    && var_4->get_unk_57C() > (RwReal)(frand_range(5.0f, 15.0f) * 60.0f))
#else
                            if (var_38 != var_4->get_unk_F54()
                                    && var_4->get_unk_57C() > lerp(5.0f, 15.0f, frand()) * 60.0f)
#endif
                                sub_12030(1, arg_0, (RwInt32)arg_4, 0);
                        } else if (var_38 != var_4->get_unk_F54()) {
                            if (var_4->get_unk_1178() <= 0.0f)
#ifdef CODFH_SP // shape: frand_range kept out of line (SP 0x11080)
                                var_4->unk_1178 = frand_range(30.0f, 120.0f) * 60.0f;
#else
                                var_4->unk_1178 = lerp(30.0f, 120.0f, frand()) * 60.0f;
#endif
                            if (var_4->get_unk_57C() > var_4->get_unk_1178())
                                sub_12030(1, arg_0, (RwInt32)arg_4, 0);
                        }
                    }
                }
            } else {
                stk_4C = 0;
                var_44 = 0;
                loc48 = var_4->unk_1374.sub_D4910();
                if (loc48 != 0 && var_4->sub_238E0(loc48) != 0) {
                    local_50 = var_4->sub_16ED0(loc48, 0);
                    if (((local_50->unk_04 >> 1) & 1) == 0 && local_50->unk_10 > 2700.0f) {
                        local_50->unk_10 = 0.0f;
                        var_44 = 1;
                    }
                }
                if (var_44 == 0 && var_4->get_unk_F60() != var_4->get_unk_F54())
                    stk_4C = sub_12030(1, arg_0, (RwInt32)arg_4, 0);
                if (stk_4C == 0 && sub_12030(0x21, arg_0, (RwInt32)arg_4, 0) == 0) {
                    if (var_44 != 0) {
                        if (sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0
                                && sub_12030(2, arg_0, (RwInt32)arg_4, 0) == 0)
                            sub_12030(4, arg_0, (RwInt32)arg_4, 0);
                    } else if (sub_12030(2, arg_0, (RwInt32)arg_4, 0) == 0
                            && sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0) {
                        sub_12030(4, arg_0, (RwInt32)arg_4, 0);
                    }
                }
            }
            break;
        }
        case 0x18: {
            RwInt32 var_54;

            var_4->sub_29380(1);
            var_54 = sub_12070(arg_0, (RwInt32)arg_4);
            if (var_54 == 0 && sub_12030(2, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0)
                sub_12030(4, arg_0, (RwInt32)arg_4, 0);
            break;
        }
        case 0x1F: {
            RwInt32 v5C;
            RwInt32 var_58;

            var_4->sub_29380(1);
            var_4->sub_22EF0(1);
            var_4->sub_22F30(0);
            v5C = sub_12070(arg_0, (RwInt32)arg_4);
            var_58 = 0;
            if (v5C != 0 && var_4->get_unk_578() == 0x25 && var_4->get_unk_57C() > 180.0f)
                var_58 = sub_12030(1, arg_0, (RwInt32)arg_4, 0);
            if (v5C == 0 && var_58 == 0 && sub_12030(1, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(2, arg_0, (RwInt32)arg_4, 0) == 0
                    && sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0)
                sub_12030(4, arg_0, (RwInt32)arg_4, 0);
            break;
        }
        case 0x21: {
            RwInt32 var_68;
            RwInt32 local_64;
            RwInt32 local_60;

            var_4->sub_29380(1);
            var_4->sub_22EF0(1);
            local_60 = 1;
            if (sub_12030(0x22, arg_0, (RwInt32)arg_4, 0) != 0)
                local_60 = 0;
            if (local_60 != 0 && var_4->sub_17B40() > 30.0f) {
                local_64 = 0;
                if (sub_12030(1, arg_0, (RwInt32)arg_4, 0) == 0
                        && sub_12030(0x1F, arg_0, (RwInt32)arg_4, 0) == 0
                        && sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0)
                    local_64 = 1;
            }
            if (local_60 != 0) {
                var_68 = sub_12070(arg_0, (RwInt32)arg_4);
                if (var_68 == 0 && sub_12030(1, arg_0, (RwInt32)arg_4, 0) == 0
                        && sub_12030(0x1F, arg_0, (RwInt32)arg_4, 0) == 0
                        && sub_12030(2, arg_0, (RwInt32)arg_4, 0) == 0
                        && sub_12030(3, arg_0, (RwInt32)arg_4, 0) == 0)
                    sub_12030(4, arg_0, (RwInt32)arg_4, 0);
            }
            break;
        }
        }
    }
    vf_034(arg_0, arg_4);
    var_4->unk_6C = 0;
}

// match: sub_34720 @ 0x00034720
// sp-match: sub_34720 @ 0x0002C3F0
RwInt32 type_3CE6D0::sub_34720(type_3DBC78 *arg_0, type_3D410 *arg_4)
{
    return arg_4->sub_3DCD0(arg_0);
}

// match: ?vf_034@type_3CE4B4@@UAEHPAUtype_3DBC78@@PAUtype_3D410@@@Z @ 0x00034740
// sp-match: ?vf_034@type_3CE4B4@@UAEHPAUtype_3DBC78@@PAUtype_3D410@@@Z @ 0x00028440
RwInt32 type_3CE4B4::vf_034(type_3DBC78 *arg_0, type_3D410 *arg_4)
{
    RwReal l14;
    RwReal var_10;
    RwV3d *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if ((var_4->unk_1430 != -1) != 0) {
        v8 = var_4->unk_1430;
        if (v8 == 0) {
            var_4->sub_22EF0(1);
            ebp_C = var_4->sub_27EB0(arg_0->sub_CD550(), sub_1745A0(dword_429EB0)->sub_CD5A0());
            if (ebp_C == 0 || sub_12030(0x1C, arg_0, (RwInt32)arg_4, ebp_C) == 0)
                var_4->sub_1A5A0(-1);
            else
                var_4->sub_1A5A0(1);
        } else if (v8 == 1 || v8 == 2) {
            if (sub_12030(0x1B, arg_0, (RwInt32)arg_4, 0) != 0) {
                var_4->sub_1A5A0(3);
            } else {
                var_10 = dword_4B87C8;
                l14 = var_4->unk_1434;
                if (l14 + 60.0f < var_10) {
                    if (v8 == 2) {
                        var_4->sub_22EF0(0);
                        var_4->sub_1A5A0(3);
                        sub_6B5F0("AIAction_GoGoGoToPoint", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, 1, 0);
                    } else {
                        var_4->unk_F58 = 0;
                        var_4->sub_17AB0(0);
                        var_4->sub_1A5A0(-1);
                    }
                }
            }
        }
        return 1;
    }
    return 0;
}










// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_010@type_3CE4B4@@UAEHPAUtype_3D410@@@Z (folded into `return 0` at 0x32260)
RwInt32 type_3CE4B4::vf_010(type_3D410 *arg_0)
{
    return 0;
}

// ?vf_010@type_3CE4F0@@UAEHPAUtype_3D410@@@Z (folded into `return 0` at 0x32260)
RwInt32 type_3CE4F0::vf_010(type_3D410 *arg_0)
{
    return 0;
}

// ?vf_024@type_3CE4B4@@UAEHPAUtype_3D3548@@@Z (folded into `return 1` at 0x1F5A00)
RwInt32 type_3CE4B4::vf_024(type_3D3548 *arg_0)
{
    return 1;
}

// ?vf_030@type_3CE4B4@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3CE4B4::vf_030()
{
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_004@type_3CE4F0@@UAEXPAUtype_3DF30@@@Z (folded into 0x33580)
// sp-match: ?vf_004@type_3CE4F0@@UAEXPAUtype_3DF30@@@Z @ 0x00028320
void type_3CE4F0::vf_004(struct type_3DF30 *arg_0)
{
    unk_1C = 0;
    type_3CE6D0::vf_004(arg_0);
}

// ?vf_008@type_3CE4F0@@UAEXXZ (folded into 0x39440)
void type_3CE4F0::vf_008()
{
    type_3CE6D0::vf_008();
}

// ?vf_030@type_3CE4F0@@UAEHXZ (folded into 0xC5540)
RwInt32 type_3CE4F0::vf_030()
{
    return 3;
}
