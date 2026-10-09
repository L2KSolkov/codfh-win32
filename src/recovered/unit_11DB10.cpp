// The projectile generators' bullet kind (type_11DB10, types/type_1227C0.h).
// The original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "types/type_1227C0.h"
#include "types/ProjectileGeneratorTrigger.h"
#include "types/type_3D3548.h"
#include "types/type_F2FF0.h"
#include "types/type_495F0.h"
#include "game/functions.h"
#include "types/type_3DF8D8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DA650
extern const RwReal flt_3DA650 = 16.666666f;
// End of its data definitions.


// Sets or clears flag 2 of a projectile's flags: clears it when arg_2 holds.
#ifdef CODFH_SP // single player's inline member (SP 0xD5B40; expanded for a constant argument)
#define PG_FLAG2(p, on) ((p)->sp_sub_D5B40(on))
// (its out-of-line copy, which vf_024 and sub_11E850 call for a random argument)
// sp-match: ?sp_sub_D5B40@type_3D3548@@QAEXH@Z @ 0x000D5B40
#else
#define PG_FLAG2(p, on) ((on) ? ((p)->unk_28 &= ~2) : ((p)->unk_28 |= 2))
#endif

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DA650@@3MB @ 0x003DA650
// match: ??_7type_11DB10@@6B@ @ 0x003DA654
// match: ??_7type_1227C0@@6B@ @ 0x003DA67C
// match: ??_C@_0BI@ICILHIFD@ProjectileGeneratorFire?$AA@ @ 0x003DA6A4
// match: __ehhandler$??0type_11DB10@@QAE@XZ>1>8 @ 0x0041D3E0
// match: __ehhandler$??0type_11DB10@@QAE@XZ>1 @ 0x0041D3E8
// match: __ehhandler$??1type_1227C0@@UAE@XZ>1>8 @ 0x0041D404
// match: __ehhandler$??1type_1227C0@@UAE@XZ>1 @ 0x0041D42C

// match: ??0type_11DB10@@QAE@XZ @ 0x0011DB10
// match: __ehhandler$??0type_11DB10@@QAE@XZ-0x8 @ 0x00301480
// match: __ehhandler$??0type_11DB10@@QAE@XZ @ 0x00301488
// sp-match: ??0type_11DB10@@QAE@XZ @ 0x000D6100

type_11DB10::type_11DB10()
{
}

// match: ??1type_1227C0@@UAE@XZ @ 0x0011DBA0
// match: __ehhandler$??1type_1227C0@@UAE@XZ-0x40 @ 0x003014A0
// match: __ehhandler$??1type_1227C0@@UAE@XZ @ 0x003014E0
// sp-match: ??1type_1227C0@@UAE@XZ @ 0x000D6060
// (In the class.)

// match: ??_Gtype_1227C0@@UAEPAXI@Z @ 0x0011DC20
// sp-match: ??_Gtype_1227C0@@UAEPAXI@Z @ 0x000D60E0
// (Its scalar deleting destructor, compiler-written.)

// match: ?vf_014@type_11DB10@@UAEXH@Z @ 0x0011DC50
// sp-match: ?vf_014@type_11DB10@@UAEXH@Z @ 0x000D6190
// Turns its line-of-sight check on or off.
void type_11DB10::vf_014(RwInt32 arg_0)
{
    unk_20C = arg_0;
}

// match: ?vf_004@type_11DB10@@UAEXPAVProjectileGeneratorTrigger@@@Z @ 0x0011DC70
// sp-match: ?vf_004@type_11DB10@@UAEXPAVProjectileGeneratorTrigger@@@Z @ 0x000D5B60
// Sets it up from its trigger, which then holds it.
void type_11DB10::vf_004(ProjectileGeneratorTrigger *arg_0)
{
    type_1227C0::vf_004(arg_0);
    unk_20C = 0;
    arg_0->unk_224 = this;
    vf_00C(arg_0);
}

// match: ?vf_008@type_11DB10@@UAEXXZ @ 0x0011DCC0
// sp-match: ?vf_008@type_11DB10@@UAEXXZ @ 0x000D5B90
void type_11DB10::vf_008()
{
    type_1227C0::vf_008();
}

// The base's update: identical to the shells' kind's, into which /OPT:ICF
// folds it (0x11E830; config/aliases.txt), so it is not placed here.
void type_11DB10::vf_010(RwReal arg_0)
{
    type_1227C0::vf_010(arg_0);
}

// match: ?vf_00C@type_11DB10@@UAEXPAVProjectileGeneratorTrigger@@@Z @ 0x0011DCE0
// sp-match: ?vf_00C@type_11DB10@@UAEXPAVProjectileGeneratorTrigger@@@Z @ 0x000D5BA0
// Its projectile's settings from its trigger: a bullet (unk_150), or with
// the trigger's unk_1CC set a projectile (unk_188, kind 3 for 1, else 2)
// whose object is the trigger's unk_1D0.
void type_11DB10::vf_00C(ProjectileGeneratorTrigger *arg_0)
{
    type_3DF8D8 *var_4;

    if (arg_0->unk_1CC == 0)
    {
        unk_150.unk_04 = arg_0->unk_154;
        unk_150.unk_00 = 0;
    }
    else
    {
        unk_188.unk_3C = 0;
        unk_188.unk_44 = 0;
        unk_188.unk_48 = 0;
        unk_188.unk_04 = arg_0->unk_154;
        unk_188.unk_4C_r = arg_0->unk_194;
        unk_1D8 = arg_0->unk_198;
        unk_1DC = arg_0->unk_154;
        unk_1E0 = arg_0->unk_1A0;
        unk_1E8 = arg_0->unk_1A8;
        unk_1E4 = arg_0->unk_1A4;
        unk_1EC = arg_0->unk_1AC;
        unk_1F0 = arg_0->unk_1B0;
        unk_1F4 = arg_0->unk_1B4;
        unk_1F8 = arg_0->unk_1B8;
        unk_1FC = arg_0->unk_1C8;
        unk_200 = arg_0->unk_1C0;
        unk_204 = arg_0->unk_1C4;
        unk_208 = arg_0->unk_1C8;
        unk_D0 = arg_0->unk_FC_r;
        var_4 = find_object(&arg_0->unk_1D0);
        unk_188.unk_38 = ((RwInt32)((type_3DF9C4 *)var_4)->sub_190A10());
        unk_188.unk_40 = 0;
        memcpy(unk_188.unk_08, &arg_0->unk_244, 0x30);
        if (arg_0->unk_1CC == 1)
        {
            unk_188.unk_00 = 3;
        }
        else
        {
            unk_188.unk_00 = 2;
        }
    }
    vf_014(arg_0->unk_1FC);
}

// match: ?vf_024@type_11DB10@@UAEHXZ @ 0x0011DF00
// sp-match: ?vf_024@type_11DB10@@UAEHXZ @ 0x000D5D20
// Fires a bullet (0x201, or 0x202 for the trigger's unk_DC 2) or a
// projectile from its barrel, turret or parent at the point it aims at,
// with its muzzle particle systems, and tells its script
// ("ProjectileGeneratorFire"); whether it fired.
RwInt32 type_11DB10::vf_024()
{
    ProjectileGeneratorTrigger *var_C;
    RwV3d var_18;
    RwV3d var_24;
    RwMatrix var_70;
    type_439A48 *var_74;
    RwInt32 var_78;
    type_3D3548 *var_7C;
    type_3D3548 *var_80;
    type_3D3548 *var_84;
    type_3D3548 *var_88;
    type_3D3548 *var_8C;
    RwInt32 var_94;
    type_F2FF0 *var_9C;
    type_F2FF0 *var_A0;
    type_F2FF0 *var_A4;

    if ((unk_144 == 0.0f ? unk_2C : 0) == 0)
    {
        return 0;
    }
    if (!sub_1210A0(&unk_B0))
    {
        return 0;
    }
    var_C = unk_18.unk_08_pg;
    sub_122150(&var_18);
    RwV3dSubMacro(&var_24, &unk_B0, &var_18);
    RwV3dNormalize(&var_24, &var_24);
    sub_1213D0(&var_24, &var_70);
    if (unk_34 == 3)
    {
        sub_121230(&var_24, &var_70);
    }
    RwV3dScaleMacro(&var_24, &var_24, var_C->unk_158_r);
    sub_122150(&var_70.pos);
    if (var_C->unk_1CC == 0)
    {
        var_74 = (type_439A48 *)&unk_150;
    }
    else
    {
        var_74 = (type_439A48 *)&unk_188;
    }
    if (var_C->unk_DC == 2)
    {
        var_78 = 0x202;
    }
    else
    {
        var_78 = 0x201;
    }
    var_7C = unk_E0.sub_D4910();
    var_80 = unk_E8.sub_D4910();
    var_84 = unk_EC.sub_D4910();
    var_88 = var_84;
    if (var_88 == 0)
    {
        var_88 = var_80;
    }
    if (var_88 == 0)
    {
        var_88 = var_7C;
    }
    var_8C = (type_3D3548 *)sub_15F2C0(var_78, (RwInt32)var_88, &var_70, &var_24, unk_D8, var_74,
                                       (RwInt32)&var_C->unk_228);
    if (var_8C)
    {
        if (var_C->unk_104 == 0)
        {
            PG_FLAG2(var_8C, 0);
        }
        else if (var_C->unk_104 < 100)
        {
#ifdef CODFH_SP // shape: no copy in var_94 (SP 0xD5D20 computes the argument in edx)
            PG_FLAG2(var_8C, var_C->unk_104 >= RpRandom() % 101);
#else
            PG_FLAG2(var_8C, (var_94 = var_C->unk_104 >= RpRandom() % 101));
#endif
        }
    }
    if (var_C->unk_1E4)
    {
        if (var_C->unk_1D8)
        {
            var_9C = sub_121BE0(0);
            if (var_9C == 0 || !(var_9C->unk_40 & 1))
            {
                var_9C = (type_F2FF0 *)sub_F2FF0(var_C->unk_1D8, &var_70, 0, 1, 0, 0);
                if (var_C->unk_1F0)
                {
                    sub_121B90(var_9C, 0);
                }
            }
        }
        if (var_C->unk_1DC && var_C->unk_1E8)
        {
            var_A0 = sub_121BE0(1);
            if (var_A0 == 0 || !(var_A0->unk_40 & 1))
            {
                var_A0 = (type_F2FF0 *)sub_F2FF0(var_C->unk_1DC, &var_70, 0, 1, 0, 0);
                if (var_C->unk_1F4)
                {
                    sub_121B90(var_A0, 1);
                }
            }
        }
        if (var_C->unk_1E0 && var_C->unk_1EC)
        {
            var_A4 = sub_121BE0(2);
            if (var_A4 == 0 || !(var_A4->unk_40 & 1))
            {
                var_A4 = (type_F2FF0 *)sub_F2FF0(var_C->unk_1E0, &var_70, 0, 1, 0, 0);
                if (var_C->unk_1F8)
                {
                    sub_121B90(var_A4, 2);
                }
            }
        }
    }
    sub_6B5F0("ProjectileGeneratorFire", (type_67620 *)(get_trigger()->sub_BDF50()), (type_42E00_10 *)((RwInt32)get_trigger()), 0, 0, 0, 1, 0);
    return 1;
}

// match: ?vf_020@type_11DB10@@UAEHPAURwV3d@@@Z @ 0x0011E3D0
// sp-match: ?vf_020@type_11DB10@@UAEHPAURwV3d@@@Z @ 0x000D6010
// With its line-of-sight check on, whether the target can be seen from its
// trigger's position to arg_0 (sub_42210); 1 otherwise.
RwInt32 type_11DB10::vf_020(RwV3d *arg_0)
{
    ProjectileGeneratorTrigger *var_4;
    RwV3d *v8;
    type_3D3548 *varC;

    if (unk_20C == 0)
    {
        return 1;
    }
    var_4 = unk_18.unk_08_pg;
    varC = unk_24.sub_D4910();
    v8 = &var_4->unk_60_m.pos;
    if (varC)
    {
        return sub_42210(v8, arg_0, 0, varC);
    }
    return 1;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_11DB10@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_11DB10::operator delete(void *arg_0, void *arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_11DB10@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_11DB10::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}
