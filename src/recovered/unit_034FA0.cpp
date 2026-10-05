// The Distance Scheduler ("Somebody forgot to unregister in the Distance
// Scheduler!", sub_350D0): registrations that watch the distance between an
// object's entity and a target, and message it when the target comes into or
// goes out of range. Its setup (sub_34FA0), shutdowns (sub_35020, sub_35080)
// and warning (sub_350D0) mirror astarscheduler.cpp's sub_32E50 to
// sub_32F50, which start that unit, so this unit is taken to start at
// sub_34FA0. Its original file name and end boundary are not yet recovered
// (M1), so it is named for its start address.

#include <xmmintrin.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/alfasched.h"
#include "types/type_35120.h"
#include "types/type_3D2E7C.h"
#include "types/type_3D3548.h"
#include "types/type_67620.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE524
extern const RwReal flt_3CE524 = 16.666666f;
// 0x003CE528
extern const RwReal flt_3CE528 = 16.666666f;
// 0x00438E88
type_365A0 *dword_438E88;
// 0x00438E90
type_438E90 dword_438E90[97];
// 0x00439198
RwInt32 dword_439198;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
alfasched dword_4391A0;
alfasched dword_439210;
type_16C2A0 dword_4391EC;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE524@@3MB @ 0x003CE524
// match: ?flt_3CE528@@3MB @ 0x003CE528
// match: ??_C@_0BF@GHBKOMBP@m_freeDistanceParams?$AA@ @ 0x003CE52C
// match: ??_C@_0DJ@OEJKGJJP@Somebody?5forgot?5to?5unregister?5in@ @ 0x003CE544
// match: ??_C@_0O@GODNNLFA@TargetInRange?$AA@ @ 0x003CE580
// match: ??_C@_0BB@GAMHPJME@TargetOutOfRange?$AA@ @ 0x003CE590
// match: .CRT$XCU+0 @ 0x00426D6C
// match: .CRT$XCU+4 @ 0x00426D70
// match: .CRT$XCU+8 @ 0x00426D74

// match: _$E2 @ 0x00309790
// match: _$E3 @ 0x0030DC50
// match: _$E5 @ 0x003097B0
// match: _$E6 @ 0x0030DC60
// match: _$E8 @ 0x003097D0
// match: _$E9 @ 0x0030DC70

RwInt32 sub_353A0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
RwInt32 sub_35A60(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
void sub_350D0();
// Whether the entity arg_4 is a target for arg_0's registration arg_8.
RwInt32 sub_35AA0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_35120 *arg_8);
// The target arg_4 is in range (sub_35FD0) or out of range (sub_362F0) of
// arg_0, at distance arg_C, for the registration arg_8: they message arg_0
// ("TargetInRange" / "TargetOutOfRange", through sub_35F60 / sub_36280) when
// the registration asks for that answer, or for a registration against
// every entity record the distance (1e37 when out of range) in arg_0's AI
// record of the target.
void sub_35FD0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_35120 *arg_8, RwReal arg_C);
void sub_362F0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_35120 *arg_8, RwReal arg_C);
// sub_35C20 and sub_35D90 (16-aligned frames, SSE square roots): each is 1 when the entities arg_0 and arg_4 lie between the squared
// distances arg_8 and arg_C (0x78 lower for one with flag 4 of unk_2C;
// sub_35D90 also bounds the height difference), storing the distance in
// *arg_10.
RwInt32 sub_35C20(type_3D3548 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwReal arg_C,
                  RwReal *arg_10);
RwInt32 sub_35D90(type_3D3548 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwReal arg_C,
                  RwReal *arg_10);
RwUInt32 sub_365A0(type_35120 *arg_0);
void sub_366D0(type_365A0 arg_0);
type_35120 *sub_36700(type_365A0 arg_0);

// match: sub_34FA0 @ 0x00034FA0
void sub_34FA0()
{
    dword_4391EC.sub_16C2C0(0x61, 0x24, "m_freeDistanceParams", 4, 0);
    dword_4391A0.sub_71F20(0x20, 1, 3, 0, sub_353A0, sub_35A60);
    dword_439210.sub_71F20(0x40, 1, 0x15, 0, sub_353A0, sub_35A60);
    memset(dword_438E90, 0, sizeof(dword_438E90));
    dword_438E88 = 0;
    dword_439198 = 0;
}

// match: sub_35020 @ 0x00035020
void sub_35020()
{
    RwInt32 var_4;

    var_4 = dword_4391A0.sub_71FA0();
    if (var_4 != 0)
        sub_350D0();
    var_4 = dword_439210.sub_71FA0();
    if (var_4 != 0)
        sub_350D0();
    memset(dword_438E90, 0, sizeof(dword_438E90));
    dword_438E88 = 0;
    dword_439198 = 0;
}

// match: sub_35080 @ 0x00035080
void sub_35080()
{
    RwInt32 var_4;

    var_4 = dword_4391A0.sub_71FC0();
    if (var_4 != 0)
        sub_350D0();
    var_4 = dword_439210.sub_71FC0();
    if (var_4 != 0)
        sub_350D0();
    dword_4391EC.sub_16C4D0(1);
}

// match: sub_350D0 @ 0x000350D0
void sub_350D0()
{
    sub_19A750("Somebody forgot to unregister in the Distance Scheduler!");
}

// match: sub_350F0 @ 0x000350F0
void sub_350F0(RwReal arg_0)
{
    dword_4391A0.sub_72560(arg_0);
    dword_439210.sub_72560(arg_0);
}

// match: sub_35120 @ 0x00035120
type_35120 *sub_35120(RwReal arg_0, RwReal arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                      type_3D2E7C *arg_14, RwInt32 arg_18, RwInt32 arg_1C)
{
    type_35120 *var_4;

    var_4 = (type_35120 *)dword_4391EC.sub_16C5A0(0);
    var_4->unk_04 = arg_8;
    var_4->unk_20_0 = arg_C;
    var_4->unk_20_1 = arg_10;
    var_4->unk_0C = arg_4 * arg_4;
    var_4->unk_08 = arg_0 * arg_0;
    var_4->unk_10 = 0;
    var_4->unk_18 = arg_18;
    var_4->unk_1C = arg_1C;
    if (arg_14 != 0) {
        var_4->unk_10 = arg_14->get_unk_04();
        var_4->unk_14 = arg_14->get_unk_24();
    } else {
        var_4->unk_10 = 0;
        var_4->unk_14 = 0;
    }
    var_4->unk_00.unk_00 = sub_365A0(var_4);
    return var_4;
}

// match: sub_35200 @ 0x00035200
// Registers arg_0 for the test arg_C between the distances arg_4 and arg_8
// (see type_35120); test 6 registers both a test-6 entry on dword_4391A0
// and a test-5 one on dword_439210.
type_67620 *sub_35200(type_67620 *arg_0, RwReal arg_4, RwReal arg_8, RwInt32 arg_C,
                      RwInt32 arg_10, RwInt32 arg_14, type_3D2E7C *arg_18, RwInt32 arg_1C,
                      RwInt32 arg_20)
{
    type_67620 *var_4;
    type_35120 *v8;
    RwUInt32 varC;

    v8 = sub_35120(arg_4, arg_8, arg_C, arg_10, arg_14, arg_18, arg_1C, arg_20);
    if (arg_C == 3 || arg_C == 5 || arg_C == 9 || arg_C == 8 || arg_C == 7 || arg_C == 0xA) {
        varC = dword_439210.sub_72050(arg_0, v8->unk_00.unk_00, 0, 0).unk_00;
    } else if (arg_C == 6) {
        varC = dword_4391A0.sub_72050(arg_0, v8->unk_00.unk_00, 0, 0).unk_00;
        v8 = sub_35120(arg_4, arg_8, 5, arg_10, arg_14, arg_18, arg_1C, arg_20);
        varC = dword_439210.sub_72050(arg_0, v8->unk_00.unk_00, 0, 0).unk_00;
    } else {
        varC = dword_4391A0.sub_72050(arg_0, v8->unk_00.unk_00, 0, 0).unk_00;
    }
    var_4 = sub_67620(varC);
    return var_4;
}

// match: sub_35330 @ 0x00035330
void sub_35330(type_67620 *arg_0)
{
    if (arg_0 != 0) {
        dword_4391A0.sub_72240(arg_0);
        dword_439210.sub_72240(arg_0);
    }
}

// match: sub_35360 @ 0x00035360
void sub_35360(alfasched_entry *arg_0)
{
    if (arg_0 != 0) {
        if (dword_4391A0.sub_722E0(arg_0) != 0)
            dword_4391A0.sub_722B0(arg_0->unk_00);
        else
            dword_439210.sub_722B0(arg_0->unk_00);
    }
}

// match: sub_353A0 @ 0x000353A0
// The schedules' first callback: runs the registration arg_4 for the object
// arg_0, answering each target through sub_35FD0 (in range) or sub_362F0
// (out of range). Returns 0 to end a registration with flag 0 whose answer
// matched, else 1.
RwInt32 sub_353A0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    type_365A0 l14;
    type_35120 *var_10;
    RwInt32 ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    l14.unk_00 = arg_4;
    var_10 = sub_36700(l14);
    v8 = arg_0->vf_024()->sub_71300();
    var_4 = 0;
    if (var_10->unk_04 == 3 || var_10->unk_04 == 5 || var_10->unk_04 == 0xA) {
        RwInt32 local_28;
        RwReal local_24;
        AIData *local_20;
        type_3D3548 *var_1C;
        type_3D2E7C *var_18;

        var_1C = 0;
        var_18 = 0;
        if (var_10->unk_04 == 3 || var_10->unk_04 == 0xA) {
            var_18 = (type_3D2E7C *)sub_67620(var_10->unk_10);
            if (var_18 != 0 && var_18->get_unk_24() == var_10->unk_14)
                var_1C = var_18->sub_71300();
        } else if (var_10->unk_04 == 5) {
            local_20 = v8->vf_120();
            if (local_20 != 0) {
                var_1C = local_20->unk_1374.sub_D4910();
                if (var_1C != 0)
                    var_18 = var_1C->vf_098();
            }
        }
        if (var_1C != 0 && var_18 != 0) {
            if (var_10->unk_04 == 0xA)
                local_28 = sub_35D90(v8, var_1C, var_10->unk_08, var_10->unk_0C, &local_24);
            else
                local_28 = sub_35C20(v8, var_1C, var_10->unk_08, var_10->unk_0C, &local_24);
            if (local_28 != 0) {
                sub_35FD0(v8, var_1C, var_10, local_24);
                var_4 = var_10->unk_20_1;
            } else {
                sub_362F0(v8, var_1C, var_10, local_24);
                var_4 = !var_10->unk_20_1;
            }
        }
    } else if (var_10->unk_04 == 7 || var_10->unk_04 == 0xC) {
        RwInt32 ebp_34;
        RwReal var_30;
        AIData *var_2C;

        var_2C = v8->vf_120();
        if (var_2C != 0) {
            ebp_34 = 0;
            if (var_10->unk_04 == 0xC)
                ebp_34 = 1;
            var_30 = 0.0f;
            if (var_2C->sub_21610(var_10->unk_08, var_10->unk_0C, &var_30, v8, ebp_34)) {
                sub_35FD0(v8, var_2C->get_unk_13E8(), var_10, var_30);
                var_4 = var_10->unk_20_1;
            } else {
                sub_362F0(v8, var_2C->get_unk_13E8(), var_10, var_30);
                var_4 = !var_10->unk_20_1;
            }
        }
    } else if (var_10->unk_04 == 8) {
        RwReal var_3C;
        AIData *var_38;

        var_38 = v8->vf_120();
        if (var_38 != 0) {
            var_3C = 0.0f;
            if (var_38->sub_21910(var_10->unk_08, var_10->unk_0C, &var_3C)) {
                sub_35FD0(v8, var_38->get_unk_13E8(), var_10, var_3C);
                var_4 = 1;
            } else {
                sub_362F0(v8, var_38->get_unk_13E8(), var_10, var_3C);
            }
        }
    } else if (var_10->unk_04 == 9 || var_10->unk_04 == 0xB) {
        RwReal local_50;
        RwInt32 stk_4C;
        type_3D3548 *loc48;
        type_3D2E7C *var_44;
        AIData *var_40;

        var_40 = v8->vf_120();
        if (var_40 != 0) {
            loc48 = 0;
            var_44 = 0;
            if (var_10->unk_10 != 0) {
                var_44 = (type_3D2E7C *)sub_67620(var_10->unk_10);
                if (var_44 != 0 && var_44->get_unk_24() == var_10->unk_14)
                    loc48 = var_44->sub_71300();
            } else {
                loc48 = v8;
                var_44 = v8->vf_098();
            }
            if (loc48 != 0) {
                stk_4C = 0;
                if (var_10->unk_04 == 0xB)
                    stk_4C = 1;
                local_50 = 0.0f;
                if (var_40->sub_221E0(var_10->unk_08, var_10->unk_0C, &local_50, loc48, stk_4C)) {
                    sub_35FD0(v8, var_40->get_unk_13E8(), var_10, local_50);
                    var_4 = 1;
                } else {
                    sub_362F0(v8, var_40->get_unk_13E8(), var_10, local_50);
                }
            }
        }
    } else if (var_10->unk_04 == 0xD || var_10->unk_04 == 0xE) {
        RwInt32 v5C;
        RwReal var_58;
        AIData *var_54;

        var_54 = v8->vf_120();
        if (var_54 != 0) {
            v5C = 0;
            if (var_10->unk_04 == 0xE)
                v5C = 1;
            var_58 = 0.0f;
            if (var_54->sub_21790(var_10->unk_08, var_10->unk_0C, &var_58, v5C)) {
                sub_35FD0(v8, var_54->get_unk_13E8(), var_10, var_58);
                var_4 = var_10->unk_20_1;
            } else {
                sub_362F0(v8, var_54->get_unk_13E8(), var_10, var_58);
                var_4 = !var_10->unk_20_1;
            }
        }
    } else {
        RwReal var_68;
        type_3D3548 *local_64;
        RwInt32 local_60;

        for (local_60 = 0; local_60 < 0x10; local_60++) {
            for (local_64 = dword_4B8600[local_60].unk_00; local_64 != 0; local_64 = local_64->unk_10) {
                if (local_64 != v8 && sub_35AA0(v8, local_64, var_10) != 0) {
                    if (sub_35C20(v8, local_64, var_10->unk_08, var_10->unk_0C, &var_68) != 0) {
                        sub_35FD0(v8, local_64, var_10, var_68);
                        var_4 = var_10->unk_20_1;
                    } else {
                        sub_362F0(v8, local_64, var_10, var_68);
                        var_4 = !var_10->unk_20_1;
                    }
                }
            }
        }
    }
    ebp_C = 1;
    if (var_10->unk_20_0 && var_4 != 0)
        ebp_C = 0;
    return ebp_C;
}

// match: sub_35A60 @ 0x00035A60
// The schedules' second callback: ends the registration arg_4.
RwInt32 sub_35A60(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    type_35120 *var_4;
    type_365A0 local_8;

    local_8.unk_00 = arg_4;
    var_4 = sub_36700(local_8);
    sub_366D0(local_8);
    dword_4391EC.sub_16C710(var_4);
    return 1;
}

// match: ?sub_35AA0@@YAHPAUtype_3D3548@@0PAUtype_35120@@@Z @ 0x00035AA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_35AA0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_35120 *arg_8)
{
    // Named handle values precede the serial getters' inline locals.
    // The comma expressions preserve the short-circuit read order.
    RwUInt32 var_20;
    RwUInt32 l1C;
    RwUInt32 m_18;
    type_3D3548 *ebp_14;
    type_3D2E7C *lv_10;
    type_3D2E7C *var_C;
    AIData *bp_8;
    type_3D2E7C *bp_4;

    switch (arg_8->unk_04)
    {
    case 3:
    case 10:
        bp_4 = arg_4->vf_098();
        return bp_4 &&
            (m_18 = bp_4->unk_04, m_18 == arg_8->unk_10) &&
            bp_4->get_unk_24() == arg_8->unk_14 ? 1 : 0;
    case 5:
        lv_10 = arg_4->vf_098();
        var_C = 0;
        bp_8 = arg_0->vf_120();
        if (bp_8)
        {
            ebp_14 = bp_8->unk_1374.sub_D4910();
            if (ebp_14)
                var_C = ebp_14->vf_098();
        }
        return lv_10 && var_C &&
            (l1C = lv_10->unk_04, var_20 = var_C->unk_04, l1C == var_20) &&
            lv_10->get_unk_24() == var_C->get_unk_24() ? 1 : 0;
    case 4:
        return arg_4->unk_2C_4;
    case 6:
        return arg_4->unk_2C & 7;
    default:
        return 1;
    }
}

// match: ?sub_35C20@@YAHPAUtype_3D3548@@0MMPAM@Z @ 0x00035C20
RwInt32 sub_35C20(type_3D3548 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwReal arg_C, RwReal *arg_10)
{
    RwV3d *var_10;
    RwV3d *var_18;
    RwV3d var_24;
    RwReal var_28;

    if (!arg_0->get_unk_340() || !arg_4->get_unk_340())
    {
        return 0;
    }
    var_10 = RwMatrixGetPos(RwFrameGetLTM(arg_0->get_unk_340()));
    var_18 = RwMatrixGetPos(RwFrameGetLTM(arg_4->get_unk_340()));
    RwV3dSubMacro(&var_24, var_10, var_18);
    if (((arg_0->unk_2C >> 4) & 1) || ((arg_4->unk_2C >> 4) & 1))
    {
        var_24.y -= 120.0f;
    }
    var_28 = RwV3dDotProductMacro(&var_24, &var_24);
    if (var_28 <= arg_C && var_28 >= arg_8)
    {
        do
        {
            __m128 var_40 = _mm_set_ss(var_28);
            __m128 var_70 = _mm_sqrt_ss(var_40);
            _mm_store_ss(arg_10, var_70);
        } while (0);
        return 1;
    }
    return 0;
}

// match: ?sub_35D90@@YAHPAUtype_3D3548@@0MMPAM@Z @ 0x00035D90
RwInt32 sub_35D90(type_3D3548 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwReal arg_C, RwReal *arg_10)
{
    RwV3d var_18;
    RwV3d var_28;
    RwV3d var_34;
    RwReal var_38;
    RwReal var_3C;
    RwReal var_40;

    if (!arg_0->get_unk_340() || !arg_4->get_unk_340())
    {
        return 0;
    }
    var_18 = *RwMatrixGetPos(RwFrameGetLTM(arg_0->get_unk_340()));
    var_28 = *RwMatrixGetPos(RwFrameGetLTM(arg_4->get_unk_340()));
    if ((arg_0->unk_2C >> 4) & 1)
    {
        var_18.y -= 120.0f;
    }
    if ((arg_4->unk_2C >> 4) & 1)
    {
        var_28.y -= 120.0f;
    }
    RwV3dSubMacro(&var_34, &var_28, &var_18);
    var_38 = var_28.y + 200.0f;
    var_3C = var_28.y - 125.0f;
    if (var_18.y < var_3C || var_18.y > var_38)
    {
        return 0;
    }
    var_40 = RwV3dDotProductMacro(&var_34, &var_34);
    if (var_40 <= arg_C && var_40 >= arg_8)
    {
        do
        {
            __m128 var_60 = _mm_set_ss(var_40);
            __m128 var_90 = _mm_sqrt_ss(var_60);
            _mm_store_ss(arg_10, var_90);
        } while (0);
        return 1;
    }
    return 0;
}

// match: sub_35F60 @ 0x00035F60
// Sends arg_0's "in range" message for the registration arg_4 (its unk_18,
// or "TargetInRange"), with the arg_C dwords at arg_8.
void sub_35F60(type_3D3548 *arg_0, type_35120 *arg_4, type_35FD0 *arg_8, RwInt32 arg_C)
{
    if (arg_4->unk_18 != -1)
        sub_6B680(arg_4->unk_18, (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)arg_8, arg_C, 1, 0);
    else
        sub_6B5F0("TargetInRange", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)arg_8, arg_C, 1, 0);
}

// match: ?sub_35FD0@@YAXPAUtype_3D3548@@0PAUtype_35120@@M@Z @ 0x00035FD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_35FD0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_35120 *arg_8, RwReal arg_C)
{
    // Named getter values and receivers retain the original grouped slots.
    type_3D2E7C *stk_58;
    type_3D2E7C *l54;
    type_3D2E7C *var50;
    RwUInt32 x4C;
    RwUInt32 w48;
    RwUInt32 loc44;
    RwUInt32 fp_40;
    type_154C0_80 *l3C;
    AIData *var38;
    type_35FD0 r34;
    type_35FD0 fp_2C;
    type_3D2E7C *frm_24;
    type_3D3548 *var_20;
    AIData *l1C;
    type_35FD0 m_18;
    type_35FD0 lv_10;
    type_35FD0 bp_8;

    if (arg_8->unk_04 == 7 || arg_8->unk_04 == 12)
    {
        if (arg_8->unk_20_1)
        {
            if (arg_4 && arg_4->vf_098())
            {
                var50 = arg_4->vf_098();
                fp_40 = var50->unk_04;
                bp_8.unk_00 = fp_40;
            }
            else
                bp_8.unk_00 = 0;
            bp_8.unk_04 = arg_C;
            sub_35F60(arg_0, arg_8, &bp_8, 2);
        }
    }
    else if (arg_8->unk_04 == 8 || arg_8->unk_04 == 9 || arg_8->unk_04 == 11 ||
             arg_8->unk_04 == 13 || arg_8->unk_04 == 14)
    {
        if (arg_8->unk_20_1)
        {
            lv_10.unk_00 = 0;
            lv_10.unk_04 = arg_C;
            sub_35F60(arg_0, arg_8, &lv_10, 2);
        }
    }
    else if (arg_8->unk_04 == 3 || arg_8->unk_04 == 10)
    {
        if (arg_8->unk_20_1 && arg_8->unk_10)
        {
            if (arg_4->vf_098())
            {
                l54 = arg_4->vf_098();
                loc44 = l54->unk_04;
                m_18.unk_00 = loc44;
            }
            else
                m_18.unk_00 = 0;
            m_18.unk_04 = arg_C;
            sub_35F60(arg_0, arg_8, &m_18, 2);
        }
    }
    else if (arg_8->unk_04 == 5)
    {
        if (arg_8->unk_20_1)
        {
            l1C = arg_0->vf_120();
            if (l1C)
            {
                var_20 = l1C->unk_1374.sub_D4910();
                if (var_20)
                {
                    frm_24 = var_20->vf_098();
                    if (frm_24)
                    {
                        w48 = frm_24->unk_04;
                        fp_2C.unk_00 = w48;
                        fp_2C.unk_04 = arg_C;
                        sub_35F60(arg_0, arg_8, &fp_2C, 2);
                    }
                }
            }
        }
    }
    else if (arg_8->unk_04 == 4)
    {
        if (arg_8->unk_20_1)
        {
            if (arg_4->vf_098())
            {
                stk_58 = arg_4->vf_098();
                x4C = stk_58->unk_04;
                r34.unk_00 = x4C;
            }
            else
                r34.unk_00 = 0;
            r34.unk_04 = arg_C;
            sub_35F60(arg_0, arg_8, &r34, 2);
        }
    }
    else
    {
        var38 = arg_0->vf_120();
        l3C = var38->sub_16ED0(arg_4, 0);
        if (!l3C)
            return;
        l3C->unk_0C = arg_C;
    }
}

// match: sub_36280 @ 0x00036280
// Sends arg_0's "out of range" message for the registration arg_4 (its
// unk_1C, or "TargetOutOfRange"), with the arg_C dwords at arg_8.
void sub_36280(type_3D3548 *arg_0, type_35120 *arg_4, type_35FD0 *arg_8, RwInt32 arg_C)
{
    if (arg_4->unk_1C != -1)
        sub_6B680(arg_4->unk_1C, (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)arg_8, arg_C, 1, 0);
    else
        sub_6B5F0("TargetOutOfRange", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)arg_8, arg_C, 1, 0);
}

// match: ?sub_362F0@@YAXPAUtype_3D3548@@0PAUtype_35120@@M@Z @ 0x000362F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_362F0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_35120 *arg_8, RwReal arg_C)
{
    // Named getter values and receivers retain the original grouped slots.
    type_3D2E7C *stk_58;
    type_3D2E7C *l54;
    type_3D2E7C *var50;
    RwUInt32 x4C;
    RwUInt32 w48;
    RwUInt32 loc44;
    RwUInt32 fp_40;
    type_154C0_80 *l3C;
    AIData *var38;
    type_35FD0 r34;
    type_35FD0 fp_2C;
    type_3D2E7C *frm_24;
    type_3D3548 *var_20;
    AIData *l1C;
    type_35FD0 m_18;
    type_35FD0 lv_10;
    type_35FD0 bp_8;

    if (arg_8->unk_04 == 7 || arg_8->unk_04 == 12)
    {
        if (!arg_8->unk_20_1)
        {
            if (arg_4 && arg_4->vf_098())
            {
                var50 = arg_4->vf_098();
                fp_40 = var50->unk_04;
                bp_8.unk_00 = fp_40;
            }
            else
                bp_8.unk_00 = 0;
            bp_8.unk_04 = arg_C;
            sub_36280(arg_0, arg_8, &bp_8, 2);
        }
    }
    else if (arg_8->unk_04 == 8 || arg_8->unk_04 == 9 || arg_8->unk_04 == 11 ||
             arg_8->unk_04 == 13 || arg_8->unk_04 == 14)
    {
        if (!arg_8->unk_20_1)
        {
            lv_10.unk_00 = 0;
            lv_10.unk_04 = arg_C;
            sub_36280(arg_0, arg_8, &lv_10, 2);
        }
    }
    else if (arg_8->unk_04 == 3 || arg_8->unk_04 == 10)
    {
        if (!arg_8->unk_20_1 && arg_8->unk_10)
        {
            if (arg_4->vf_098())
            {
                l54 = arg_4->vf_098();
                loc44 = l54->unk_04;
                m_18.unk_00 = loc44;
            }
            else
                m_18.unk_00 = 0;
            m_18.unk_04 = arg_C;
            sub_36280(arg_0, arg_8, &m_18, 2);
        }
    }
    else if (arg_8->unk_04 == 5)
    {
        if (!arg_8->unk_20_1)
        {
            l1C = arg_0->vf_120();
            if (l1C)
            {
                var_20 = l1C->unk_1374.sub_D4910();
                if (var_20)
                {
                    frm_24 = var_20->vf_098();
                    if (frm_24)
                    {
                        w48 = frm_24->unk_04;
                        fp_2C.unk_00 = w48;
                        fp_2C.unk_04 = arg_C;
                        sub_36280(arg_0, arg_8, &fp_2C, 2);
                    }
                }
            }
        }
    }
    else if (arg_8->unk_04 == 4)
    {
        if (!arg_8->unk_20_1)
        {
            if (arg_4->vf_098())
            {
                stk_58 = arg_4->vf_098();
                x4C = stk_58->unk_04;
                r34.unk_00 = x4C;
            }
            else
                r34.unk_00 = 0;
            r34.unk_04 = arg_C;
            sub_36280(arg_0, arg_8, &r34, 2);
        }
    }
    else
    {
        var38 = arg_0->vf_120();
        l3C = var38->sub_16ED0(arg_4, 0);
        if (!l3C)
            return;
        l3C->unk_0C = 1.0e37f;
    }
}

// match: sub_365A0 @ 0x000365A0
// Gives the registration arg_0 a handle: the pending one in dword_438E88 if
// set, else the first free entry of dword_438E90 with a new serial.
RwUInt32 sub_365A0(type_35120 *arg_0)
{
    RwInt32 var_4;
    RwInt32 v8;
    type_365A0 varC;

    v8 = 0;
    if (dword_438E88 != 0) {
        var_4 = dword_438E88->unk_00_lo;
        varC.unk_00_lo = dword_438E90[var_4].unk_00.unk_00_lo = var_4;
        dword_438E90[var_4].unk_00.unk_02 = dword_438E88->unk_02;
        varC.unk_02 = dword_438E90[var_4].unk_00.unk_02;
        dword_438E90[var_4].unk_04 = arg_0;
        v8 = 1;
        dword_438E88 = 0;
    } else {
        for (var_4 = 1; var_4 < 0x61; var_4++) {
            if (dword_438E90[var_4].unk_00.unk_00 == 0 && dword_438E90[var_4].unk_04 == 0) {
                if (dword_439198 == 0)
                    dword_439198 = 1;
                varC.unk_00_lo = dword_438E90[var_4].unk_00.unk_00_lo = var_4;
                varC.unk_02 = dword_438E90[var_4].unk_00.unk_02 = dword_439198;
                dword_438E90[var_4].unk_04 = arg_0;
                v8 = 1;
                dword_439198++;
                break;
            }
        }
    }
    return varC.unk_00;
}

// match: sub_366D0 @ 0x000366D0
// Frees the handle arg_0's entry.
void sub_366D0(type_365A0 arg_0)
{
    dword_438E90[arg_0.unk_00_lo].unk_00.unk_00 = 0;
    dword_438E90[arg_0.unk_00_lo].unk_04 = 0;
}

// match: sub_36700 @ 0x00036700
// The registration of the handle arg_0, 0 when it is stale.
type_35120 *sub_36700(type_365A0 arg_0)
{
    if (dword_438E90[arg_0.unk_00_lo].unk_00.unk_00 == arg_0.unk_00)
        return dword_438E90[arg_0.unk_00_lo].unk_04;
    return 0;
}
