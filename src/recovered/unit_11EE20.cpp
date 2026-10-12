// The projectile generators' base (type_1227C0, types/type_1227C0.h), their
// pool and id table, and the "PG_" helpers they share. The original file
// name is not in the image, so it is named for its start address.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/rprandom.h"
#include "types/type_1227C0.h"
#include "types/ProjectileGeneratorTrigger.h"
#include "types/type_3D3548.h"
#include "types/type_F2FF0.h"
#include "types/SplinePath.h"
#include "types/AIData.h"
#include "game/functions.h"
#include "game/clumpdata.h"
#include "game/data.h"
#include "game/frand.h"
#include "types/CGlobalSounds.h"
#include "types/type_10F710.h"
#include "types/alfasched.h"
#include "game/pooledconsts.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DA6E8
extern const RwReal flt_3DA6E8 = 16.666666f;
// 0x004CE8F0
RwInt32 dword_4CE8F0;
// 0x004CE8F8
type_1227C0 *dword_4CE8F8;
// 0x004CE900
type_4CE900 dword_4CE900[41];
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
struct type_16C2A0 dword_4CEA48;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DA6E8@@3MB @ 0x003DA6E8
// match: __real@3f7fbe77 @ 0x003DA6EC
// match: __real@bf666666 @ 0x003DA6F8
// match: ??_C@_0EE@BCBMMJDF@WARNING?3?5ProjectileGenerator?3?3Cl@ @ 0x003DA700
// match: __ehhandler$??0type_1227C0@@QAE@XZ>1>8 @ 0x0041D46C
// match: __ehhandler$??0type_1227C0@@QAE@XZ>1 @ 0x0041D494
// match: .CRT$XCU+0 @ 0x00427098

// match: _$E2 @ 0x0030B7D0
// match: _$E3 @ 0x0030E5F0
// match: ?sub_11EE20@@YAXPAUtype_3D3548@@PAUtype_1227C0@@H@Z @ 0x0011EE20
// sp-match: _$E2 @ 0x0021D830
// sp-match: _$E3 @ 0x0021E980
// sp-match: ?sub_11EE20@@YAXPAUtype_3D3548@@PAUtype_1227C0@@H@Z @ 0x000D7540

// Its turret's callback: turns the turret towards what it aims at (or back
// to its own facing without a line of sight once the wait is over) by its
// turn rate, and keeps it at its matrix, less the offset of the turret's
// 'ATMT' tag when it follows that.
void sub_11EE20(type_3D3548 *arg_0, type_1227C0 *arg_4, RwInt32 arg_8)
{
    type_1227C0 *var_4;
    type_3D3548 *var_8;
    RwMatrix var_50;
    RwMatrix var_A0;
    RwV3d var_AC;
    type_3D3548 *var_B0;
    RwInt32 var_B4;
    RwInt32 var_C4;
    RwV3d var_D0;
    RwReal var_D4;
    RwV3d var_E4;
    RwFrame *var_F8;
    RwMatrix *var_FC;

    var_4 = arg_4;
    var_8 = var_4->unk_E8.sub_D4910();
    var_50 = var_4->unk_70;
    if (var_8 != 0)
    {
        if ((RwInt32)(var_4->unk_FC == 2))
        {
            if (sub_EC2D0(var_8->get_unk_264(), (RwInt32)&var_A0, 0x41544D54, 0, 1))
            {
                RwV3dSubMacro(&var_AC, &var_A0.pos, (RwV3d *)var_8->vf_0C4());
                RwV3dSubMacro(&var_50.pos, &var_50.pos, &var_AC);
            }
        }
        if (var_4->vf_018())
        {
            RwV3d var_C0;

            var_B0 = var_4->unk_24.sub_D4910();
            var_B4 = 0;
            if (var_B0)
            {
                var_C0 = *var_B0->vf_0CC();
            }
            else
            {
                var_C0 = var_4->unk_B0;
            }
            var_C4 = var_4->sub_121100(&var_C0, &var_50);
            if (var_C4)
            {
                RwV3dSubMacro(&var_D0, &var_C0, &var_50.pos);
                RwV3dNormalize(&var_D0, &var_D0);
                var_D4 = RwV3dDotProductMacro(&var_4->unk_12C, &var_D0);
                if (var_D4 > 0.999f)
                {
                    var_4->unk_2C = 1;
                }
                else
                {
                    var_4->unk_2C = 0;
                    var_B4 = 1;
                }
                var_4->unk_13C = var_4->unk_138;
            }
            else
            {
                var_4->unk_2C = 0;
                if (!(var_4->unk_13C > 0.0f ? 1 : 0))
                {
                    var_D0 = var_50.at;
                    var_B4 = 1;
                }
            }
            if (var_B4)
            {
                RwV3dSubMacro(&var_E4, &var_D0, &var_4->unk_12C);
                RwV3dScaleMacro(&var_E4, &var_E4, var_4->get_turn_rate());
                RwV3dAddMacro(&var_4->unk_12C, &var_4->unk_12C, &var_E4);
                RwV3dNormalize(&var_4->unk_12C, &var_4->unk_12C);
                var_8->vf_0D8(&var_4->unk_12C);
            }
            var_F8 = var_8->get_unk_340();
            var_FC = RwFrameGetMatrix(var_F8);
            var_4->unk_12C = *RwMatrixGetAt(var_FC);
        }
        else
        {
            var_8->vf_0D8(&var_50.at);
        }
        var_8->vf_0C0(&var_50.pos);
    }
}

// match: ?sub_11F2B0@@YAXPAUtype_3D3548@@PAUtype_1227C0@@H@Z @ 0x0011F2B0
// sp-match: ?sub_11F2B0@@YAXPAUtype_3D3548@@PAUtype_1227C0@@H@Z @ 0x000D67A0
// Its barrel's callback: keeps the barrel at the turret's tagged matrix
// 'OPR0'+arg_8 (arg_8 0 to 9) or its frame's.
void sub_11F2B0(type_3D3548 *arg_0, type_1227C0 *arg_4, RwInt32 arg_8)
{
    type_1227C0 *var_4;
    type_3D3548 *var_8;
    type_3D3548 *var_C;
    RwInt32 var_10;
    RwMatrix var_60;
    RwFrame *var_68;

    var_4 = arg_4;
    var_8 = var_4->unk_E8.sub_D4910();
    var_C = var_4->unk_EC.sub_D4910();
    if (var_8 && var_C)
    {
        if ((RwInt32)(var_4->unk_F8 == 2))
        {
            var_10 = arg_8;
            if (arg_8 >= 0 && arg_8 <= 9)
            {
                var_10 = arg_8 % 10 + 0x4F505230;
            }
            sub_EC2D0(var_8->get_unk_264(), (RwInt32)&var_60, var_10, 0, 1);
        }
        else
        {
            var_68 = var_8->get_unk_340();
            if (var_68)
            {
                var_60 = *RwFrameGetLTM(var_68);
            }
        }
        var_C->vf_0C0(&var_60.pos);
        var_C->vf_0D8(&var_60.at);
    }
}

// match: ??0type_1227C0@@QAE@XZ @ 0x0011F3D0
// match: __ehhandler$??0type_1227C0@@QAE@XZ-0x40 @ 0x00301510
// match: __ehhandler$??0type_1227C0@@QAE@XZ @ 0x00301550
// sp-match: ??0type_1227C0@@QAE@XZ @ 0x000D7810
type_1227C0::type_1227C0()
{
    unk_100 = 0;
}

// match: ??0type_F2880@@QAE@XZ @ 0x0011F4D0
// sp-match: ??0type_F2880@@QAE@XZ @ 0x000B8470
// (In its class: its out-of-line copy, emitted for the constructor's array
// of three.)

// match: ?vf_004@type_1227C0@@UAEXPAVProjectileGeneratorTrigger@@@Z @ 0x0011F500
// sp-match: ?vf_004@type_1227C0@@UAEXPAVProjectileGeneratorTrigger@@@Z @ 0x000D83C0
// Sets it up from its trigger arg_0: its burst, turret, sound and target
// settings, its path (the spline of the object under the trigger's unk_E8)
// and its named target point (unk_F0), then its first firing stage.
void type_1227C0::vf_004(ProjectileGeneratorTrigger *arg_0)
{
    type_3DF8D8 *var_4;

    unk_100 = 0;
    unk_18.sub_144940(arg_0);
    unk_44 = 0;
    unk_14 = 0;
    unk_50 = arg_0->unk_100;
    unk_48 = 1;
    unk_D4 = 1;
    unk_30 = 1;
    unk_38 = 0;
    unk_28 = 0;
    unk_104 = 0;
    unk_D8 = 0;
    unk_CC = 0;
    unk_D0 = arg_0->unk_FC_r;
    unk_DC = 0;
    unk_70 = arg_0->unk_60_m;
    unk_10 = 0;
    unk_4C = arg_0->unk_118;
    unk_138 = arg_0->unk_11C;
    unk_140 = arg_0->unk_21C;
    unk_148 = arg_0->unk_220;
    unk_144 = 0;
    unk_2C = 1;
    if (arg_0->unk_108 <= arg_0->unk_10C)
    {
        unk_40 = RpRandom() % (arg_0->unk_10C - arg_0->unk_108 + 1) + arg_0->unk_108;
    }
    else
    {
        unk_40 = RpRandom() % (arg_0->unk_108 - arg_0->unk_10C + 1) + arg_0->unk_10C;
    }
    if (arg_0->unk_E8.unk_00 || arg_0->unk_E8.unk_04)
    {
        var_4 = find_object(&arg_0->unk_E8);
        unk_DC = ((type_3DFEEC *)var_4)->unk_24;
        unk_38 = 3;
    }
    unk_60 = arg_0->unk_F8;
    if (arg_0->unk_F0.unk_00 || arg_0->unk_F0.unk_04)
    {
        sub_121910(&arg_0->unk_F0, unk_60);
    }
    sub_120310();
    unk_24.sub_D48D0(0);
    unk_E0.sub_D48D0(0);
    unk_E8.sub_D48D0(0);
    unk_EC.sub_D48D0(0);
    unk_E4 = arg_0->unk_C8;
    unk_F0 = 0;
    unk_F4 = 0;
    unk_F8 = 0;
    unk_FC = 0;
}

// match: ?vf_008@type_1227C0@@UAEXXZ @ 0x0011F7D0
// sp-match: ?vf_008@type_1227C0@@UAEXXZ @ 0x000D7B90
void type_1227C0::vf_008()
{
    RwInt32 var_4;
    type_F2FF0 *local_8;

    sub_121A50();
    if (unk_E8.sub_D4910())
    {
        unk_E8.sub_D4910()->sub_D3700(0, 0, 0);
        unk_E8.sub_D48D0(0);
    }
    if (unk_EC.sub_D4910())
    {
        unk_EC.sub_D4910()->sub_D3700(0, 0, 0);
        unk_EC.sub_D48D0(0);
    }
    unk_24.sub_D48D0(0);
    unk_E0.sub_D48D0(0);
    for (var_4 = 0; var_4 < 3; var_4++)
    {
        local_8 = unk_108[var_4].unk_08;
        if (local_8)
        {
            sub_F3300(local_8);
        }
    }
    if (get_trigger())
    {
        unk_18.sub_144940(0);
    }
}

// match: ?sub_11F8E0@type_1227C0@@QAEHXZ @ 0x0011F8E0
// sp-match: ?sub_11F8E0@type_1227C0@@QAEHXZ @ 0x000D6860
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1227C0::sub_11F8E0()
{
    type_3D3548 *var_4;
    type_3D3548 *v8;
    type_3D3548 *varC;

    if (unk_E0.get_id())
    {
        var_4 = unk_E0.sub_D4910();
        if (var_4)
        {
            if (var_4->unk_28_0 || var_4->unk_28_9)
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (unk_EC.get_id())
    {
        v8 = unk_EC.sub_D4910();
        if (v8)
        {
            if (v8->unk_28_0 || v8->unk_28_9)
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if (unk_E8.get_id())
    {
        varC = unk_E8.sub_D4910();
        if (varC)
        {
            if (varC->unk_28_0 || varC->unk_28_9)
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

// The tagged matrix 'PGN0'+arg_0 (arg_0 0 to 9), or arg_0 itself: an inline
// with no address and so no database name, named for what it returns.
// Evidence: sub_11F9E0 copies its argument into a temporary before the
// range check and keeps the result in another.
inline RwInt32 pgn_tag(RwInt32 arg_0)
{
    RwInt32 r;

    if (arg_0 >= 0 && arg_0 <= 9)
    {
        r = arg_0 % 10 + 0x50474E30;
    }
    else
    {
        r = arg_0;
    }
    return r;
}

// match: ?sub_11F9E0@type_1227C0@@QAEXXZ @ 0x0011F9E0
// sp-match: ?sub_11F9E0@type_1227C0@@QAEXXZ @ 0x000D68E0
void type_1227C0::sub_11F9E0()
{
    type_3D3548 *var_8;
    RwMatrix var_60;
    RwFrame *var_68;

    var_8 = unk_E0.sub_D4910();
    if (var_8)
    {
        if ((RwInt32)(unk_F0 == 2))
        {
            sub_EC2D0(var_8->get_unk_264(), (RwInt32)&var_60, pgn_tag(unk_E4), 0, 1);
        }
        else
        {
            var_68 = var_8->get_unk_340();
            if (var_68)
            {
                var_60 = *RwFrameGetLTM(var_68);
            }
        }
        unk_70 = var_60;
    }
}

// match: ?vf_010@type_1227C0@@UAEXM@Z @ 0x0011FAD0
// sp-match: ?vf_010@type_1227C0@@UAEXM@Z @ 0x000D8560
// Its update by arg_0 seconds: follows its parent, counts down its turret's
// wait and its sound's replay (restarting the delay when its turret or
// barrel changes kind), then, when a shot is due (or forced), aims at its
// target (the nearest or chosen entity, or along its path) and fires in its
// firing stage, stopping its sound when it cannot.
void type_1227C0::vf_010(RwReal arg_0)
{
    RwInt32 l4;
    ProjectileGeneratorTrigger *var_8;
    type_3D3548 *fp_C;
    type_3D3548 *v10;
    RwInt32 local_14;
    RwUInt32 var18;
    type_3D3548 *var_1C;
#ifndef CODFH_SP
    RwV3d bp_28;
    RwV3d lv_34;
#endif

    var_8 = unk_18.unk_08_pg;
    sub_11F9E0();
    if (unk_13C > 0.0f)
    {
        unk_13C -= arg_0;
        if (unk_13C < 0.0f)
        {
            unk_13C = 0;
        }
    }
    if (unk_140)
    {
        v10 = unk_EC.sub_D4910();
        var_1C = unk_E8.sub_D4910();
        local_14 = 0;
        var18 = 0;
        if (var_1C)
        {
            if (unk_14C >> 16 != var_1C->vf_174())
            {
                local_14 = 1;
            }
            var18 = var_1C->vf_174() << 16;
        }
        if (v10)
        {
            if ((unk_14C & 0xFFFF) != v10->vf_174())
            {
                local_14 = 1;
            }
            var18 += v10->vf_174();
        }
        if (local_14)
        {
            unk_144 = (RwReal)((unk_148 & 0xFFFF)
                               + RpRandom() % ((unk_148 >> 16) - (unk_148 & 0xFFFF) + 1));
        }
        unk_14C = var18;
    }
    if (unk_144 > 0.0f)
    {
        unk_144 -= arg_0;
        if (unk_144 < 0.0f)
        {
            unk_144 = 0;
        }
    }
    if (unk_14 != 2 && unk_28 == 0)
    {
        return;
    }
    unk_28 = 0;
    unk_44 -= arg_0;
    if (unk_44 > 0.0f)
    {
        return;
    }
    if (var_8->unk_E4 == 2)
    {
#ifdef CODFH_SP // shape: block-scoped vectors share a slot (SP 0xD8560 frame 0x14)
        RwV3d bp_28;
#endif
        RwV3dScaleMacro(&bp_28, &unk_70.at, 100.0f);
        RwV3dAddMacro(&bp_28, &unk_70.pos, &bp_28);
        sub_1218A0(&bp_28, unk_60);
        unk_C8 = 0;
    }
    fp_C = unk_24.sub_D4910();
    switch (unk_38)
    {
    case 0:
        if (!sub_120DE0())
        {
            sub_121A50();
            return;
        }
        if (fp_C != unk_24.sub_D4910())
        {
            sub_120310();
        }
        unk_24.sub_D4910()->vf_110(&unk_54, unk_E0.sub_D4910(), 0);
        if (unk_24.sub_D4910()->vf_00C() || vf_018())
        {
            unk_C8 = 0;
        }
        else
        {
            unk_C8 = -unk_24.sub_D4910()->unk_48;
        }
        break;
    case 1:
        if (fp_C == 0)
        {
            if (unk_DC)
            {
                unk_38 = 3;
            }
            else
            {
                unk_38 = 0;
            }
            return;
        }
        unk_24.sub_D4910()->vf_110(&unk_54, unk_E0.sub_D4910(), 0);
        if (unk_24.sub_D4910()->vf_00C())
        {
            unk_C8 = 0;
        }
        else
        {
            unk_C8 = -unk_24.sub_D4910()->unk_48;
        }
        break;
    case 3:
        if (unk_DC)
        {
#ifdef CODFH_SP // shape: block-scoped vectors share a slot (SP 0xD8560 frame 0x14)
            RwV3d lv_34;
#endif
            unk_DC->sub_BA990(unk_CC, &lv_34, 0);
            sub_1218A0(&lv_34, unk_60);
            unk_CC += unk_D0;
            if (unk_CC > 1.0f)
            {
                unk_CC = 1.0f;
            }
            else if (unk_CC < 0.0f)
            {
                unk_CC = 0;
            }
            if (unk_CC >= 1.0f || unk_CC <= 0.0f)
            {
                if (unk_DC->unk_1C_0 == 2)
                {
                    unk_D0 = -unk_D0;
                }
                else if (unk_DC->unk_1C_0 == 1)
                {
                    unk_CC = 0;
                }
                else
                {
                    unk_14 = 0;
                    unk_CC = 0;
                }
            }
        }
        break;
    }
    l4 = 0;
    switch (unk_34)
    {
    case 0:
        l4 = sub_120740(var_8->unk_160);
        break;
    case 1:
        l4 = sub_120740(var_8->unk_16C);
        break;
    case 2:
        l4 = sub_120740(var_8->unk_178);
        break;
    case 3:
        l4 = sub_1207A0();
        break;
    }
    if (l4 == 0 || unk_14 == 0)
    {
        sub_121A50();
        return;
    }
    if (unk_DC)
    {
        unk_38 = 3;
    }
    unk_50--;
    unk_40--;
    unk_44 = var_8->unk_128_r;
    sub_120170();
}

// match: ?sub_120150@type_1227C0@@QAEXXZ @ 0x00120150
// sp-match: ?sub_120150@type_1227C0@@QAEXXZ @ 0x000D6990
// Forces a shot now ("PG_ForcedFire").
void type_1227C0::sub_120150()
{
    unk_44 = 0;
    unk_28 = 1;
}

// match: ?sub_120170@type_1227C0@@QAEXXZ @ 0x00120170
// sp-match: ?sub_120170@type_1227C0@@QAEXXZ @ 0x000D7C50
// After a shot: at the burst's end, stops its sound, draws the next burst's
// shots and the pause before it, and moves to the next firing stage once
// its shots there are spent; after its bursts, the long pause.
void type_1227C0::sub_120170()
{
    ProjectileGeneratorTrigger *var_4;

    var_4 = unk_18.unk_08_pg;
    if (unk_40 <= 0)
    {
        sub_121A50();
        if (var_4->unk_108 <= var_4->unk_10C)
        {
            unk_40 = RpRandom() % (var_4->unk_10C - var_4->unk_108 + 1) + var_4->unk_108;
        }
        else
        {
            unk_40 = RpRandom() % (var_4->unk_108 - var_4->unk_10C + 1) + var_4->unk_10C;
        }
        if (var_4->unk_120_r <= var_4->unk_124_r)
        {
            unk_44 = frand_range(var_4->unk_120_r, var_4->unk_124_r);
        }
        else
        {
            unk_44 = frand_range(var_4->unk_124_r, var_4->unk_120_r);
        }
        unk_48 = 1;
        unk_3C--;
        if (unk_3C <= 0)
        {
            sub_1205C0();
        }
    }
    if (unk_50 <= 0)
    {
        unk_50 = var_4->unk_100;
        unk_44 = var_4->unk_114_r;
    }
}

// match: ?sub_120310@type_1227C0@@QAEXXZ @ 0x00120310
// sp-match: ?sub_120310@type_1227C0@@QAEXXZ @ 0x000D7D60
// Starts over: stops its sound, notes its turret's and barrel's kinds, and
// takes its first firing stage with shots (none for a point or path).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1227C0::sub_120310()
{
    ProjectileGeneratorTrigger *var_4;
    type_3D3548 *v8;
    RwUInt32 stk_C;
    type_3D3548 *var_10;

    var_4 = unk_18.unk_08_pg;
    sub_121A50();
    unk_48 = 1;
    unk_144 = 0;
    if (unk_140)
    {
        v8 = unk_EC.sub_D4910();
        var_10 = unk_E8.sub_D4910();
        stk_C = 0;
        if (var_10)
        {
            stk_C = var_10->vf_174() << 16;
        }
        if (v8)
        {
            stk_C += v8->vf_174();
        }
        unk_14C = stk_C;
    }
    if (unk_38 == 3 || unk_38 == 2)
    {
        unk_3C = 0x7FFFFFF;
        unk_34 = 3;
    }
    else if (var_4->unk_164 > 0 && unk_30)
    {
        if (var_4->unk_164 <= var_4->unk_168)
        {
            unk_3C = RpRandom() % (var_4->unk_168 - var_4->unk_164 + 1) + var_4->unk_164;
        }
        else
        {
            unk_3C = RpRandom() % (var_4->unk_164 - var_4->unk_168 + 1) + var_4->unk_168;
        }
        unk_34 = 0;
    }
    else if (var_4->unk_170 > 0 && unk_30)
    {
        if (var_4->unk_170 <= var_4->unk_174)
        {
            unk_3C = RpRandom() % (var_4->unk_174 - var_4->unk_170 + 1) + var_4->unk_170;
        }
        else
        {
            unk_3C = RpRandom() % (var_4->unk_170 - var_4->unk_174 + 1) + var_4->unk_174;
        }
        unk_34 = 1;
    }
    else if (var_4->unk_17C > 0 && unk_30)
    {
        if (var_4->unk_17C <= var_4->unk_180)
        {
            unk_3C = RpRandom() % (var_4->unk_180 - var_4->unk_17C + 1) + var_4->unk_17C;
        }
        else
        {
            unk_3C = RpRandom() % (var_4->unk_17C - var_4->unk_180 + 1) + var_4->unk_180;
        }
        unk_34 = 2;
    }
    else
    {
        unk_3C = 0x7FFFFFF;
        unk_34 = 3;
    }
}

// match: ?sub_1205C0@type_1227C0@@QAEXXZ @ 0x001205C0
// sp-match: ?sub_1205C0@type_1227C0@@QAEXXZ @ 0x000D69A0
// The next firing stage with shots after the current one, or none.
void type_1227C0::sub_1205C0()
{
    ProjectileGeneratorTrigger *var_4;

    var_4 = unk_18.unk_08_pg;
    if (var_4->unk_170 > 0 && unk_34 == 0 && unk_30)
    {
        if (var_4->unk_170 <= var_4->unk_174)
        {
            unk_3C = RpRandom() % (var_4->unk_174 - var_4->unk_170 + 1) + var_4->unk_170;
        }
        else
        {
            unk_3C = RpRandom() % (var_4->unk_170 - var_4->unk_174 + 1) + var_4->unk_174;
        }
        unk_34 = 1;
    }
    else if (var_4->unk_17C > 0 && unk_34 <= 1 && unk_30)
    {
        if (var_4->unk_17C <= var_4->unk_180)
        {
            unk_3C = RpRandom() % (var_4->unk_180 - var_4->unk_17C + 1) + var_4->unk_17C;
        }
        else
        {
            unk_3C = RpRandom() % (var_4->unk_17C - var_4->unk_180 + 1) + var_4->unk_180;
        }
        unk_34 = 2;
    }
    else
    {
        unk_3C = 0x7FFFFFF;
        unk_34 = 3;
    }
}

// match: ?sub_120740@type_1227C0@@QAEHM@Z @ 0x00120740
// sp-match: ?sub_120740@type_1227C0@@QAEHM@Z @ 0x000D7EF0
RwInt32 type_1227C0::sub_120740(RwReal arg_0)
{
    if (unk_48)
    {
        sub_120930(arg_0);
    }
    else
    {
        sub_120A70();
    }
    if (vf_024())
    {
        sub_121150();
        unk_48 = 0;
        return 1;
    }
    return 0;
}

// match: ?sub_1207A0@type_1227C0@@QAEHXZ @ 0x001207A0
// sp-match: ?sub_1207A0@type_1227C0@@QAEHXZ @ 0x000D7F40
// Fires at its target point (raised by the target's height offset), spread
// at random within unk_60 across for a point target; whether it fired.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1227C0::sub_1207A0()
{
    RwV3d var_C;
    RwReal local_10;
    RwV3d var_1C;

    unk_B0 = unk_54;
    unk_B0.y += unk_C8;
    if (unk_38 == 2 && unk_60_r != 0.0f)
    {
        local_10 = lerp(0.0f, 1.0f, frand());
        var_C.x = 0;
        var_C.y = 1.0f;
        var_C.z = 0;
        var_1C.x = 0;
        var_1C.y = 0;
        var_1C.z = local_10 * unk_60_r;
        sub_13FFA0(&var_1C, &var_C, lerp(-3.14159f, 3.14159f, frand()));
        unk_B0.x = var_1C.x + unk_B0.x;
        unk_B0.z = var_1C.z + unk_B0.z;
    }
    if (!vf_020(&unk_B0))
    {
        return 0;
    }
    if (vf_024())
    {
        sub_121150();
        unk_48 = 0;
        return 1;
    }
    return 0;
}

// match: ?sub_120930@type_1227C0@@QAEXM@Z @ 0x00120930
// sp-match: ?sub_120930@type_1227C0@@QAEXM@Z @ 0x000D6A70
// Its first shot at the target: aims at it, and starts the walk of the
// aim point from arg_0 off to one side at a random angle, the last point
// twice as far to the other.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1227C0::sub_120930(RwReal arg_0)
{
    RwReal var_4;
    RwReal v8;
    RwReal varC;

    unk_B0 = unk_54;
    unk_B0.y += unk_C8;
    unk_BC = unk_B0;
    v8 = sin(varC = lerp(-3.1415927f, 3.1415927f, frand()));
    var_4 = cos(varC);
    v8 *= arg_0;
    var_4 *= arg_0;
    unk_B0.x += var_4;
    unk_B0.z += v8;
    unk_BC.x += var_4 * 2.0f;
    unk_BC.z += v8 * 2.0f;
}

// match: ?sub_120A70@type_1227C0@@QAEXXZ @ 0x00120A70
// sp-match: ?sub_120A70@type_1227C0@@QAEXXZ @ 0x000D6B30
// Its next shot at the target: walks the aim point on from the last by a
// random step (the trigger's unk_184 to unk_188), turned about the vertical
// by a random angle within the trigger's unk_18C either way.
void type_1227C0::sub_120A70()
{
    ProjectileGeneratorTrigger *var_8;
    RwV3d var_14;
    RwReal var_38;
    RwMatrix var_90;
    RwReal var_A8;

    var_8 = unk_18.unk_08_pg;
    RwV3dSubMacro(&var_14, &unk_B0, &unk_BC);
    if (fabs(RwV3dDotProductMacro(&var_14, &var_14)) > 0.0001f)
    {
        RwV3dNormalize(&var_14, &var_14);
    }
    if (var_8->unk_184 <= var_8->unk_188)
    {
        var_38 = frand_range(var_8->unk_184, var_8->unk_188);
    }
    else
    {
        var_38 = frand_range(var_8->unk_188, var_8->unk_184);
    }
    RwV3dScaleMacro(&var_14, &var_14, var_38);
    RwMatrixSetIdentityMacro(&var_90);
    if (-var_8->unk_18C <= var_8->unk_18C)
    {
        var_A8 = frand_range(-var_8->unk_18C, var_8->unk_18C);
    }
    else
    {
        var_A8 = frand_range(var_8->unk_18C, -var_8->unk_18C);
    }
    RwMatrixRotate(&var_90, &var_90.up, var_A8, rwCOMBINEREPLACE);
    sub_141320(&var_14, &var_14, &var_90);
    RwV3dAddMacro(&var_14, &unk_B0, &var_14);
    unk_BC = unk_B0;
    unk_B0 = var_14;
}

// match: ?sub_120DE0@type_1227C0@@QAEHXZ @ 0x00120DE0
// sp-match: ?sub_120DE0@type_1227C0@@QAEHXZ @ 0x000D8070
// Picks its target by its trigger's unk_E4: the player (0), the nearest
// enemy (1) or none (2); whether it has one.
RwInt32 type_1227C0::sub_120DE0()
{
    ProjectileGeneratorTrigger *var_4;

    var_4 = unk_18.unk_08_pg;
    switch (var_4->unk_E4)
    {
    case 0:
        if (sub_1745A0(0))
        {
            unk_24.sub_D48D0(sub_1745A0(0));
        }
        else
        {
            unk_24.sub_D48D0(0);
        }
        break;
    case 1:
        unk_24.sub_D48D0(sub_120E80());
        break;
    case 2:
        unk_24.sub_D48D0(0);
        break;
    }
    return unk_24.sub_D4910() ? 1 : 0;
}

// match: ?sub_120E80@type_1227C0@@QAEPAUtype_3D3548@@XZ @ 0x00120E80
// sp-match: ?sub_120E80@type_1227C0@@QAEPAUtype_3D3548@@XZ @ 0x000D7890
// The nearest entity not on its trigger's side (unk_DC) nor dead: a player
// or an AI-controlled one flagged as a target (AIData::unk_49C_6), or any
// other vehicle or soldier kind (vf_024, vf_01C) but side 4.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *type_1227C0::sub_120E80()
{
    RwV3d *stk_4C;
    RwReal loc48;
    RwV3d var_44;
    RwV3d *v38;
    RwReal v34;
    RwV3d v30;
    AIData *slot_24;
    type_3D3548 *v20;
    RwInt32 slot_1C;
    RwV3d var_18;
    ProjectileGeneratorTrigger *fp_C;
    type_3D3548 *lv_8;
    RwReal var_4;

    fp_C = unk_18.unk_08_pg;
    var_4 = 1e37f;
    lv_8 = 0;
    sub_122150(&var_18);
    for (slot_1C = 0; slot_1C < 16; slot_1C++)
    {
        for (v20 = dword_4B8600[slot_1C].unk_00; v20; v20 = v20->unk_10)
        {
            if ((v20->unk_2C & 7) ^ fp_C->unk_DC && v20->unk_2C & 7 && !v20->unk_28_0)
            {
                slot_24 = v20->vf_120();
                if (slot_24 && slot_24->unk_51C && slot_24->unk_49C_6 || v20->unk_2C_4)
                {
                    v38 = &RwFrameGetLTM(v20->get_unk_340())->pos;
                    RwV3dSubMacro(&v30, &var_18, v38);
                    v34 = RwV3dDotProductMacro(&v30, &v30);
                    if (v34 <= var_4)
                    {
                        lv_8 = v20;
                        var_4 = v34;
                    }
                }
#ifdef CODFH_SP // shape: constant on the left (SP 0xD7926 and eax,7; cmp al,4)
                else if ((v20->vf_024() || v20->vf_01C()) && 4 != (v20->unk_2C & 7))
#else
                else if ((v20->vf_024() || v20->vf_01C()) && (v20->unk_2C & 7) != 4)
#endif
                {
                    stk_4C = &RwFrameGetLTM(v20->get_unk_340())->pos;
                    RwV3dSubMacro(&var_44, &var_18, stk_4C);
                    loc48 = RwV3dDotProductMacro(&var_44, &var_44);
                    if (loc48 <= var_4)
                    {
                        lv_8 = v20;
                        var_4 = loc48;
                    }
                }
            }
        }
    }
    return lv_8;
}

// match: ?sub_1210A0@type_1227C0@@QAEHPAURwV3d@@@Z @ 0x001210A0
// sp-match: ?sub_1210A0@type_1227C0@@QAEHPAURwV3d@@@Z @ 0x000D6DB0
// With its arc check on (unk_D4), whether *arg_0 lies within its firing
// arcs (the trigger's unk_134 and unk_138) from its matrix; 1 otherwise.
RwInt32 type_1227C0::sub_1210A0(RwV3d *arg_0)
{
    ProjectileGeneratorTrigger *var_4;

    if (unk_D4 == 0)
    {
        return 1;
    }
    var_4 = unk_18.unk_08_pg;
    return sub_1409C0(arg_0, &unk_70, var_4->unk_134, var_4->unk_138);
}

// match: ?sub_121100@type_1227C0@@QAEHPAURwV3d@@PAURwMatrixTag@@@Z @ 0x00121100
// sp-match: ?sub_121100@type_1227C0@@QAEHPAURwV3d@@PAURwMatrixTag@@@Z @ 0x000D6DF0
// Likewise from the matrix *arg_4.
RwInt32 type_1227C0::sub_121100(RwV3d *arg_0, RwMatrix *arg_4)
{
    ProjectileGeneratorTrigger *var_4;

    if (unk_D4 == 0)
    {
        return 1;
    }
    var_4 = unk_18.unk_08_pg;
    return sub_1409C0(arg_0, arg_4, var_4->unk_134, var_4->unk_138);
}

// match: ?sub_121150@type_1227C0@@QAEXXZ @ 0x00121150
// sp-match: ?sub_121150@type_1227C0@@QAEXXZ @ 0x000D79B0
// Starts its sound, unless it plays: the trigger's (unk_140), or by the
// trigger's unk_13C one of the global gun sounds.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1227C0::sub_121150()
{
    ProjectileGeneratorTrigger *local_C;
    RwV3d loc18;

    local_C = unk_18.unk_08_pg;
    type_3DF8D8_04 var_8;
    var_8.unk_00 = local_C->unk_140.unk_00;
    var_8.unk_04 = local_C->unk_140.unk_04;
    if (var_8.unk_00 == 0 && var_8.unk_04 == 0)
    {
        switch (local_C->unk_13C)
        {
        case 0:
            var_8.unk_00 = dword_4B1C40.unk_00;
            var_8.unk_04 = dword_4B1C40.unk_04;
            break;
        case 1:
            var_8.unk_00 = dword_4B1F3C.unk_00;
            var_8.unk_04 = dword_4B1F3C.unk_04;
            break;
        case 2:
            var_8.unk_00 = 0xB01B4798;
            var_8.unk_04 = 0xF75296A0;
            break;
        }
    }
    if (unk_10 == 0)
    {
        sub_122150(&loc18);
        unk_10 = dword_4B1E98.sub_8A980(&var_8, 0, 0x10, &loc18, 0, 0);
    }
}

// The spread multiplier for the difficulty dword_42B714, 1 outside 0 to 2:
// an inline with no address and so no database name, named for what it
// returns. Evidence: sub_121230 reads it through a temporary of its own at
// each use, with the range check of sub_104420 (the health pick-ups').
inline RwReal get_spread_multiplier()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F289C[dword_42B714];
    }
    return 1.0f;
}

// match: ?sub_121230@type_1227C0@@QAEXPAURwV3d@@PAURwMatrixTag@@@Z @ 0x00121230
// sp-match: ?sub_121230@type_1227C0@@QAEXPAURwV3d@@PAURwMatrixTag@@@Z @ 0x000D6E30
// Turns the matrix *arg_4 by a random angle within its trigger's spread
// (unk_12C about its up row, unk_130 about its right row), scaled by the
// difficulty, and leaves its at row in *arg_0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_1227C0::sub_121230(RwV3d *arg_0, RwMatrix *arg_4)
{
    ProjectileGeneratorTrigger *var_4;
    RwReal local_8;

    var_4 = unk_18.unk_08_pg;
    local_8 = frand_range(-var_4->unk_12C * get_spread_multiplier(),
                        get_spread_multiplier() * var_4->unk_12C);
    RwMatrixRotate(arg_4, &arg_4->up, local_8, rwCOMBINEPOSTCONCAT);
    local_8 = frand_range(-var_4->unk_130 * get_spread_multiplier(),
                        get_spread_multiplier() * var_4->unk_130);
    RwMatrixRotate(arg_4, &arg_4->right, local_8, rwCOMBINEPOSTCONCAT);
    *arg_0 = arg_4->at;
}

// match: ?sub_1213D0@@YAXPAURwV3d@@PAURwMatrixTag@@@Z @ 0x001213D0
// sp-match: ?sub_1213D0@@YAXPAURwV3d@@PAURwMatrixTag@@@Z @ 0x000D6F80
// Builds the rows of *arg_4 about the direction *arg_0 (its at row), upright
// unless it points nearly straight up or down; the identity for a direction
// too short.
void sub_1213D0(RwV3d *arg_0, RwMatrix *arg_4)
{
    RwV3d var_C;

    if (RwV3dDotProductMacro(arg_0, arg_0) < 0.01f)
    {
        RwMatrixSetIdentityMacro(arg_4);
    }
    else
    {
        arg_4->at = *arg_0;
        if (arg_0->y < 0.9f && arg_0->y > -0.9f)
        {
            var_C.x = var_C.z = 0.0f;
            var_C.y = 1.0f;
        }
        else
        {
            var_C.y = var_C.z = 0.0f;
            var_C.x = 1.0f;
        }
        RwV3dCrossProductMacro(&arg_4->right, &var_C, &arg_4->at);
        RwV3dNormalize(&arg_4->right, &arg_4->right);
        RwV3dCrossProductMacro(&arg_4->up, &arg_4->at, &arg_4->right);
    }
}

// match: ?sub_1215E0@@YAHPAURwV3d@@0MMHPAURwMatrixTag@@@Z @ 0x001215E0
// sp-match: ?sub_1215E0@@YAHPAURwV3d@@0MMHPAURwMatrixTag@@@Z @ 0x000D70C0
// The direction to lob a shell from *arg_0 to *arg_4 at the speed arg_8
// under the gravity arg_C (the high arc with arg_10), as the rows of
// *arg_14; whether it can reach.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_1215E0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8, RwReal arg_C, RwInt32 arg_10,
                   RwMatrix *arg_14)
{
    RwV3d stk_64;
    RwReal local_58;
    RwReal local_54;
    RwV3d local_50;
    RwReal slot_44;
    RwV3d l40;
    RwReal ebp_34;
    RwReal var_30;
    RwReal bp_2C;
    RwReal bp_28;
    RwReal l24;
    RwReal l20;
    RwReal fp_1C;
    RwV3d loc18;
    RwReal stk_C;
    RwReal v8;
    RwReal var_4;

    ebp_34 = arg_C;
    fp_1C = arg_8;
    RwV3dSubMacro(&l40, arg_4, arg_0);
    loc18.x = loc18.z = 0.0f;
    loc18.y = 1.0f;
    bp_28 = RwV3dDotProductMacro(&loc18, &l40);
    loc18 = l40;
    loc18.y = 0.0f;
    RwV3dNormalize(&loc18, &loc18);
    var_30 = RwV3dDotProductMacro(&l40, &loc18);
    if (fp_1C <= 0.0f)
    {
        return 0;
    }
    if (ebp_34 >= 0.0f || var_30 == 0.0f)
    {
        stk_64.x = stk_64.z = 0.0f;
        stk_64.y = 1.0f;
        sub_1213D0(&stk_64, arg_14);
    }
    stk_C = ebp_34 * var_30 / (fp_1C * fp_1C);
    bp_2C = 2.0f;
    local_54 = (ebp_34 * var_30 * var_30 - 2.0f * bp_28 * fp_1C * fp_1C)
             / (fp_1C * fp_1C * var_30);
    local_58 = bp_2C * bp_2C - 4.0f * stk_C * local_54;
    if (local_58 < 0.0f)
    {
        return 0;
    }
    local_58 = sqrt(local_58);
    slot_44 = (-bp_2C + local_58) / (2.0f * stk_C);
    var_4 = (-bp_2C - local_58) / (2.0f * stk_C);
    if (arg_10)
    {
        l24 = slot_44 > var_4 ? slot_44 : var_4;
    }
    else
    {
        l24 = slot_44 > var_4 ? var_4 : slot_44;
    }
    v8 = fp_1C / sqrt(l24 * l24 + 1.0f);
    l20 = l24 * v8;
    RwV3dScaleMacro(&local_50, &loc18, v8);
    local_50.y = l20;
    RwV3dNormalize(&local_50, &local_50);
    sub_1213D0(&local_50, arg_14);
    return 1;
}

// match: ?sub_121870@type_1227C0@@QAEXXZ @ 0x00121870
// sp-match: ?sub_121870@type_1227C0@@QAEXXZ @ 0x000D72C0
// "PG_TargetDefault": no entity, and the nearest from then on.
void type_1227C0::sub_121870()
{
    unk_24.sub_D48D0(0);
    unk_38 = 0;
}

// match: ?sub_1218A0@type_1227C0@@QAEXPAURwV3d@@H@Z @ 0x001218A0
// sp-match: ?sub_1218A0@type_1227C0@@QAEXPAURwV3d@@H@Z @ 0x000D72E0
// "PG_TargetPoint": the point *arg_0 with the spread arg_4, and no firing
// stages.
#ifdef CODFH_SP // the spread is a real in single player (include/types/type_1227C0.h)
void type_1227C0::sub_1218A0(RwV3d *arg_0, RwReal arg_4)
#else
void type_1227C0::sub_1218A0(RwV3d *arg_0, RwInt32 arg_4)
#endif
{
    unk_54 = *arg_0;
    unk_B0 = *arg_0;
    unk_C8 = 0;
    unk_38 = 2;
    unk_34 = 3;
    unk_60 = arg_4;
}

// match: ?sub_121910@type_1227C0@@QAEXPAUtype_3DF8D8_04@@H@Z @ 0x00121910
// sp-match: ?sub_121910@type_1227C0@@QAEXPAUtype_3DF8D8_04@@H@Z @ 0x000D7340
// "PG_TargetNamedPoint": the position of the object under the key *arg_0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
#ifdef CODFH_SP // the spread is a real in single player (include/types/type_1227C0.h)
void type_1227C0::sub_121910(type_3DF8D8_04 *arg_0, RwReal arg_4)
#else
void type_1227C0::sub_121910(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
#endif
{
    type_3DF8D8 *var_4;
    type_3DF8D8 *v8;
    RwV3d *varC;

    var_4 = sub_198800(arg_0);
    v8 = var_4;
    varC = v8->vf_00C();

    if (varC)
    {
        sub_1218A0(varC, arg_4);
    }
}

// match: ?sub_121960@type_1227C0@@QAEHPAUtype_3D3548@@@Z @ 0x00121960
// sp-match: ?sub_121960@type_1227C0@@QAEHPAUtype_3D3548@@@Z @ 0x000D7370
// "PG_TargetObjectByScript": the entity arg_0, if it is AI-controlled and
// flagged as a target, or on no side, or the generator on none; whether it
// took it.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_1227C0::sub_121960(type_3D3548 *arg_0)
{
    AIData *var_4;
    ProjectileGeneratorTrigger *local_8;

    if (arg_0)
    {
        local_8 = unk_18.unk_08_pg;
        var_4 = arg_0->vf_120();
        if (var_4 && var_4->unk_51C)
        {
            if (var_4->unk_49C_6)
            {
#ifdef CODFH_SP // SP 0xD7370
                // shape: the direct id store lets both take paths share their tail.
                unk_24.unk_00 = arg_0->get_unk_384_h().unk_00;
#else // MP 0x121960
                unk_24 = arg_0->get_unk_384_h().unk_00;
#endif
                unk_38 = 1;
                return 1;
            }
        }
        else if ((arg_0->unk_2C & 7) == 0 || local_8->unk_DC == 0)
        {
#ifdef CODFH_SP // SP 0xD7370
            // shape: as in the AI-controlled take path, copy the id directly.
            unk_24.unk_00 = arg_0->get_unk_384_h().unk_00;
#else // MP 0x121960
            unk_24 = arg_0->get_unk_384_h().unk_00;
#endif
            unk_38 = 1;
            return 1;
        }
    }
    return 0;
}

// match: ?sub_121A30@type_1227C0@@QAEXH@Z @ 0x00121A30
// sp-match: ?sub_121A30@type_1227C0@@QAEXH@Z @ 0x000D80D0
// "PG_EnableFiringStages".
void type_1227C0::sub_121A30(RwInt32 arg_0)
{
    unk_30 = arg_0;
    sub_120310();
}

// match: ?sub_121A50@type_1227C0@@QAEXXZ @ 0x00121A50
// sp-match: ?sub_121A50@type_1227C0@@QAEXXZ @ 0x000D7A70
// ClearSound: stops its sound, playing its trigger's end sound (unk_148,
// with unk_150) or the global one, at the point it fires from.
void type_1227C0::sub_121A50()
{
    ProjectileGeneratorTrigger *var_4;
    RwV3d var_10;

    if (unk_10)
    {
        SoundEmitter_Stop((type_44C4E8 *)unk_10, 0);
        var_4 = unk_18.unk_08_pg;
        if (var_4 == 0)
        {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0xD7A70)
            sub_19A750("WARNING: ProjectileGenerator::ClearSound(): Trigger not valid! -RJB");
#endif
            return;
        }
        sub_122150(&var_10);
        if (var_4->unk_148.unk_00 && var_4->unk_148.unk_04)
        {
            if (var_4->unk_150)
            {
                dword_4B1E98.sub_8A980(&var_4->unk_148, 0, 0x10, &var_10, 0, 0);
            }
        }
        else if (dword_44D4D4)
        {
            dword_4B1E98.sub_8A980(&dword_4AF010, 0, 0x10, &var_10, 0, 0);
        }
        sub_3C6C0(unk_10);
        unk_10 = 0;
    }
}

// match: ?sub_121B30@type_1227C0@@QAEXH@Z @ 0x00121B30
// sp-match: ?sub_121B30@type_1227C0@@QAEXH@Z @ 0x000D73D0
void type_1227C0::sub_121B30(RwInt32 arg_0)
{
    unk_104 = arg_0;
}

// match: ?sub_121B50@@YAHPAUtype_F2FF0@@@Z @ 0x00121B50
// sp-match: ?sub_121B50@@YAHPAUtype_F2FF0@@@Z @ 0x000D7B20
RwInt32 sub_121B50(type_F2FF0 *arg_0)
{
    type_1227C0 *var_4;

    var_4 = (type_1227C0 *)arg_0->unk_158;
    arg_0->unk_00 = var_4->unk_70;
    var_4->sub_122150(&arg_0->unk_00.pos);
    return 1;
}

// match: ?sub_121B90@type_1227C0@@QAEXPAUtype_F2FF0@@H@Z @ 0x00121B90
// sp-match: ?sub_121B90@type_1227C0@@QAEXPAUtype_F2FF0@@H@Z @ 0x000D7B50
void type_1227C0::sub_121B90(type_F2FF0 *arg_0, RwInt32 arg_4)
{
    unk_108[arg_4].sub_F2880(arg_0);
    if (arg_0)
    {
        arg_0->unk_154 = sub_121B50;
        arg_0->unk_158 = (RwInt32)this;
    }
}

// match: ?sub_121BE0@type_1227C0@@QAEPAUtype_F2FF0@@H@Z @ 0x00121BE0
// sp-match: ?sub_121BE0@type_1227C0@@QAEPAUtype_F2FF0@@H@Z @ 0x000D73E0
type_F2FF0 *type_1227C0::sub_121BE0(RwInt32 arg_0)
{
    return unk_108[arg_0].get_unk_08();
}

// match: ?sub_121C10@type_1227C0@@QAEPAUSplinePath@@XZ @ 0x00121C10
// sp-match: ?sub_121C10@type_1227C0@@QAEPAUSplinePath@@XZ @ 0x000D7400
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
SplinePath *type_1227C0::sub_121C10()
{
    ProjectileGeneratorTrigger *var_4;
    type_3DF8D8 *local_8;

    var_4 = unk_18.unk_08_pg;
    if (var_4->unk_E8.unk_00 || var_4->unk_E8.unk_04)
    {
        local_8 = find_object(&var_4->unk_E8);
        return ((type_3DFEEC *)local_8)->unk_24;
    }
    return 0;
}

// match: ?sub_121C70@type_1227C0@@QAEXPAUtype_3D3548@@H@Z @ 0x00121C70
// sp-match: ?sub_121C70@type_1227C0@@QAEXPAUtype_3D3548@@H@Z @ 0x000D7430
void type_1227C0::sub_121C70(type_3D3548 *arg_0, RwInt32 arg_4)
{
    RpClump *var_8;
    RwMatrix var_50;

    unk_E0.sub_D48D0(arg_0);
    unk_E4 = arg_4;
    unk_F0 = 0;
    if (arg_0)
    {
        var_8 = arg_0->unk_25C.unk_08;
        if (var_8)
        {
            unk_F0 = 1;
            if (sub_EC2D0(var_8, (RwInt32)&var_50, unk_E4, 0, 1))
            {
                unk_F0 = 2;
            }
        }
    }
}

// match: ?sub_121D20@type_1227C0@@QAEXH@Z @ 0x00121D20
// sp-match: ?sub_121D20@type_1227C0@@QAEXH@Z @ 0x000D80E0
// "PG_ManipulateProjectileGenerator": starts (arg_0 1) or stops firing. On
// starting, finds the entities under its trigger's keys that it has none
// for yet: its parent (unk_C0; at its tagged matrix 'PGN0'+unk_E4), its
// turret (unk_CC; turned by sub_11EE20, with its 'FIRE', 'OPR0' and 'ATMT'
// tags, and with the trigger's unk_110 its matrix taken from the turret)
// and its barrel (unk_D4; kept on the turret by sub_11F2B0).
void type_1227C0::sub_121D20(RwInt32 arg_0)
{
    ProjectileGeneratorTrigger *var_C;
    type_3DF8D8_BD900 *var_14;
    RwInt32 var_18;
    RpClump *var_20;
    RwMatrix var_60;
    type_3DF8D8_BD900 *var_68;
    type_3D3548 *var_70;
    RwMatrix var_B0;
    type_3DF8D8_BD900 *var_BC;

    if (arg_0)
    {
        unk_14 = 1;
    }
    else
    {
        unk_14 = 0;
    }
    sub_120310();
    if (arg_0)
    {
        var_C = get_trigger();
        if (!unk_E0.sub_D4910() && (var_C->unk_C0.unk_00 || var_C->unk_C0.unk_04))
        {
            var_14 = (type_3DF8D8_BD900 *)find_object(&var_C->unk_C0);
            if (var_14 && var_14->unk_24.sub_D4910())
            {
                unk_E0.sub_D48D0(var_14->unk_24.sub_D4910());
                var_18 = unk_E4 % 10 + 0x50474E30;
                var_20 = var_14->unk_24.sub_D4910()->unk_25C.get_unk_08();
                if (var_20)
                {
                    unk_F0 = 1;
                    if (sub_EC2D0(var_20, (RwInt32)&var_60, var_18, 0, 1))
                    {
                        unk_F0 = 2;
                    }
                }
            }
        }
        if (!unk_E8.sub_D4910() && (var_C->unk_CC.unk_00 || var_C->unk_CC.unk_04))
        {
            var_68 = (type_3DF8D8_BD900 *)find_object(&var_C->unk_CC);
            if (var_68 && var_68->unk_24.sub_D4910())
            {
                unk_E8.sub_D48D0(var_68->unk_24.sub_D4910());
                var_68->unk_24.sub_D4910()->sub_D3700((void (*)(type_3D3548 *))sub_11EE20,
                                                       (RwInt32)this, 0);
                var_20 = var_68->unk_24.sub_D4910()->unk_25C.get_unk_08();
                if (var_20)
                {
                    unk_F4 = 1;
                    unk_FC = 1;
                    unk_F8 = 1;
                    if (sub_EC2D0(var_20, (RwInt32)&var_60, 0x46495245, 0, 1))
                    {
                        unk_F4 = 2;
                    }
                    if (sub_EC2D0(var_20, (RwInt32)&var_60, 0x4F505230, 0, 1))
                    {
                        unk_F8 = 2;
                    }
                    if (sub_EC2D0(var_20, (RwInt32)&var_60, 0x41544D54, 0, 1))
                    {
                        unk_FC = 2;
                    }
                }
                var_70 = unk_E8.sub_D4910();
                if (var_C->unk_110)
                {
                    var_B0 = unk_70;
                    if ((RwInt32)(unk_FC == 2))
                    {
                        var_20 = var_70->unk_25C.unk_08;
                        if (sub_EC2D0(var_20, (RwInt32)&var_B0, 0x41544D54, 0, 1))
                        {
                            unk_70 = var_B0;
                        }
                    }
                    else
                    {
                        unk_70 = *RwFrameGetMatrix(var_70->get_unk_340());
                    }
                }
            }
        }
        if (!unk_EC.sub_D4910() && (var_C->unk_D4.unk_00 || var_C->unk_D4.unk_04))
        {
            var_BC = (type_3DF8D8_BD900 *)find_object(&var_C->unk_D4);
            if (var_BC && var_BC->unk_24.sub_D4910())
            {
                unk_EC.sub_D48D0(var_BC->unk_24.sub_D4910());
                var_BC->unk_24.sub_D4910()->sub_D3700((void (*)(type_3D3548 *))sub_11F2B0,
                                                       (RwInt32)this, 0);
            }
        }
    }
}

// match: ?sub_122150@type_1227C0@@QAEXPAURwV3d@@@Z @ 0x00122150
// sp-match: ?sub_122150@type_1227C0@@QAEXPAURwV3d@@@Z @ 0x000D74A0
// The point it fires from: its turret's 'FIRE' tag or frame, else its own
// position.
void type_1227C0::sub_122150(RwV3d *arg_0)
{
    type_3D3548 *var_8;
    RwMatrix var_50;
    RwFrame *var_58;

    *arg_0 = unk_70.pos;
    var_8 = unk_E8.sub_D4910();
    if (var_8)
    {
        if ((RwInt32)(unk_F4 == 2))
        {
            sub_EC2D0(var_8->get_unk_264(), (RwInt32)&var_50, 0x46495245, 0, 1);
        }
        else
        {
            var_58 = var_8->get_unk_340();
            if (var_58)
            {
                var_50 = *RwFrameGetLTM(var_58);
            }
        }
        *arg_0 = var_50.pos;
    }
}






// The list's head through a local of its own: an inline with no address
// and so no database name, named for what it returns. Evidence: the
// factories read dword_4CE8F8 into a temporary before linking it.
inline type_1227C0 *get_generator_list()
{
    type_1227C0 *head = dword_4CE8F8;
    return head;
}







