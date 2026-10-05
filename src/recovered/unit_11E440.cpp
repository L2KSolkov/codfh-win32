// The projectile generators' shell kind (type_11E440, types/type_1227C0.h).
// The original file name is not in the image, so it is named for its start
// address.

#include <math.h>
#include <string.h>

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
#include "game/data.h"
#include "game/pooledconsts.h"
#include "types/type_3DF8D8.h"
#include "game/frames.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DA6BC
extern const RwReal flt_3DA6BC = 16.666666f;
// End of its data definitions.


// As the bullets' kind's (unit_11DB10): clears flag 2 when arg_2 holds.
#define PG_FLAG2(p, on) ((on) ? ((p)->unk_28 &= ~2) : ((p)->unk_28 |= 2))

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DA6BC@@3MB @ 0x003DA6BC
// match: ??_7type_11E440@@6B@ @ 0x003DA6C0
// match: __ehhandler$??0type_11E440@@QAE@XZ>1>8 @ 0x0041D448
// match: __ehhandler$??0type_11E440@@QAE@XZ>1 @ 0x0041D450

// match: ??0type_11E440@@QAE@XZ @ 0x0011E440
// match: __ehhandler$??0type_11E440@@QAE@XZ-0x8 @ 0x003014F0
// match: __ehhandler$??0type_11E440@@QAE@XZ @ 0x003014F8

type_11E440::type_11E440()
{
}

// match: ??0type_11E4A0@@QAE@XZ @ 0x0011E4A0
// A shell's settings: kind 2, the rest clear.
type_11E4A0::type_11E4A0()
{
    unk_00 = 2;
    unk_84 = 0;
    unk_88 = 0;
    unk_8C = 0;
    unk_94 = 0;
    unk_98 = 0;
    unk_9C = 0;
    unk_A0 = 0;
    unk_A4.x = 0;
    unk_A4.y = 0;
    unk_A4.z = 0;
}

// match: ??_Gtype_11E440@@UAEPAXI@Z @ 0x0011E540
// (Its scalar deleting destructor, compiler-written; the bullets' kind's,
// identical, folds into this one.)

// match: ??1type_11E440@@UAE@XZ @ 0x0011E560
// (Its destructor, compiler-written; the bullets' kind's, identical, folds
// into this one.)

// match: ?vf_004@type_11E440@@UAEXPAVProjectileGeneratorTrigger@@@Z @ 0x0011E580
// Sets it up from its trigger, which then holds it.
void type_11E440::vf_004(ProjectileGeneratorTrigger *arg_0)
{
    type_1227C0::vf_004(arg_0);
    unk_150.unk_3C = 1;
    unk_150.unk_44 = 0;
    unk_150.unk_48 = 0;
    vf_00C(arg_0);
    arg_0->unk_224 = this;
}

// match: ?vf_008@type_11E440@@UAEXXZ @ 0x0011E5E0
// Stops it, and its trigger lets it go.
void type_11E440::vf_008()
{
    ProjectileGeneratorTrigger *var_4;

    var_4 = unk_18.unk_08_pg;
    if (var_4)
    {
        var_4->unk_224 = 0;
    }
    type_1227C0::vf_008();
}

// match: ?vf_00C@type_11E440@@UAEXPAVProjectileGeneratorTrigger@@@Z @ 0x0011E620
// Its shells' settings from its trigger: kind 7, or with the trigger's
// unk_1CC set kind 8, whose object is the trigger's unk_1D0.
void type_11E440::vf_00C(ProjectileGeneratorTrigger *arg_0)
{
    type_3DF8D8 *var_4;

    unk_150.unk_04 = arg_0->unk_154;
    unk_150.unk_4C_r = arg_0->unk_194;
    unk_150.unk_40_r = arg_0->unk_204;
    unk_150.unk_88 = arg_0->unk_208;
    unk_150.unk_8C = arg_0->unk_20C;
    unk_150.unk_90 = arg_0->unk_210;
    unk_150.unk_94 = arg_0->unk_214;
    unk_150.unk_84 = arg_0->unk_190;
    unk_150.unk_50 = arg_0->unk_198;
    unk_150.unk_54 = arg_0->unk_154;
    unk_150.unk_58 = arg_0->unk_1A0;
    unk_150.unk_60 = arg_0->unk_1A8;
    unk_150.unk_5C = arg_0->unk_1A4;
    unk_150.unk_64 = arg_0->unk_1AC;
    unk_150.unk_68 = arg_0->unk_1B0;
    unk_150.unk_6C = arg_0->unk_1B4;
    unk_150.unk_70 = arg_0->unk_1B8;
    unk_150.unk_74 = arg_0->unk_1C8;
    unk_150.unk_78 = arg_0->unk_1C0;
    unk_150.unk_7C = arg_0->unk_1C4;
    unk_150.unk_80 = arg_0->unk_1C8;
    unk_D0 = arg_0->unk_FC_r;
    memcpy(unk_150.unk_08, &arg_0->unk_244, 0x30);
    if (arg_0->unk_1CC == 0)
    {
        unk_150.unk_00 = 7;
    }
    else
    {
        var_4 = find_object(&arg_0->unk_1D0);
        unk_150.unk_38 = ((RwInt32)((type_3DF9C4 *)var_4)->sub_190A10());
        unk_150.unk_00 = 8;
    }
}

// match: ?vf_010@type_11E440@@UAEXM@Z @ 0x0011E830
// The base's update; the bullets' kind's, identical, folds into this one.
void type_11E440::vf_010(RwReal arg_0)
{
    type_1227C0::vf_010(arg_0);
}

// match: ?vf_024@type_11E440@@UAEHXZ @ 0x0011E850
// Lobs a shell (0x1001, or 0x1002 for the trigger's unk_DC 2) from its
// barrel, turret or parent onto the point it aims at, keeping its flight
// time (unk_150.unk_98), with its muzzle particle systems, and tells its
// script ("ProjectileGeneratorFire"); whether it fired.
RwInt32 type_11E440::vf_024()
{
    ProjectileGeneratorTrigger *var_8;
    RwV3d var_14;
    RwMatrix var_60;
    RwV3d var_6C;
    RwV3d var_78;
    RwReal var_84;
    RwReal var_88;
    RwReal var_8C;
    RwV3d var_98;
    RwReal var_9C;
    RwInt32 var_A0;
    type_3D3548 *var_A4;
    type_3D3548 *var_A8;
    type_3D3548 *var_AC;
    type_3D3548 *var_B0;
    type_3D3548 *var_B4;
    RwInt32 var_BC;
    type_F2FF0 *var_C4;
    type_F2FF0 *var_C8;
    type_F2FF0 *var_CC;

    if (!sub_1210A0(&unk_B0))
    {
        return 0;
    }
    var_8 = unk_18.unk_08_pg;
    sub_122150(&var_14);
    if (!sub_1215E0(&var_14, &unk_B0, var_8->unk_158_r, var_8->unk_204, var_8->unk_200, &var_60))
    {
        return 0;
    }
    var_6C = var_60.at;
    unk_150.unk_9C = var_8->unk_15C;
    unk_150.unk_A4 = unk_B0;
    RwV3dScaleMacro(&var_78, &var_6C, var_8->unk_158_r);
    sub_122150(&var_14);
    var_88 = (var_84 = fabs(unk_B0.y - var_14.y)) / var_78.y;
    var_78.y = 0.0f;
    var_8C = RwV3dLength((RwV3d *)&var_78);
    RwV3dSubMacro(&var_98, &var_14, &unk_B0);
    var_98.y = 0.0f;
    unk_150.unk_98 = (var_9C = RwV3dLength((RwV3d *)&var_98)) / var_8C + var_88;
    unk_150.unk_A0 = unk_150.unk_98 - seconds_to_frames(3.0f);
    if (unk_34 == 3)
    {
        sub_121230(&var_6C, &var_60);
    }
    RwV3dScaleMacro(&var_6C, &var_6C, var_8->unk_158_r);
    sub_122150(&var_60.pos);
    if (var_8->unk_DC == 2)
    {
        var_A0 = 0x1002;
    }
    else
    {
        var_A0 = 0x1001;
    }
    var_A4 = unk_E0.sub_D4910();
    var_A8 = unk_E8.sub_D4910();
    var_AC = unk_EC.sub_D4910();
    var_B0 = var_AC;
    if (var_B0 == 0)
    {
        var_B0 = var_A8;
    }
    if (var_B0 == 0)
    {
        var_B0 = var_A4;
    }
    var_B4 = (type_3D3548 *)sub_15F2C0(var_A0, (RwInt32)var_B0, &var_60, &var_6C, unk_D8,
                                       (type_439A48 *)&unk_150, (RwInt32)&var_8->unk_228);
    if (var_B4)
    {
        if (var_8->unk_104 == 0)
        {
            PG_FLAG2(var_B4, 0);
        }
        else if (var_8->unk_104 < 100)
        {
            PG_FLAG2(var_B4, (var_BC = var_8->unk_104 >= RpRandom() % 101));
        }
    }
    if (var_8->unk_1E4)
    {
        if (var_8->unk_1D8)
        {
            var_C4 = sub_121BE0(0);
            if (var_C4 == 0 || !(var_C4->unk_40 & 1))
            {
                var_C4 = (type_F2FF0 *)sub_F2FF0(var_8->unk_1D8, &var_60, 0, 1, 0, 0);
                if (var_8->unk_1F0)
                {
                    sub_121B90(var_C4, 0);
                }
            }
        }
        if (var_8->unk_1DC && var_8->unk_1E8)
        {
            var_C8 = sub_121BE0(1);
            if (var_C8 == 0 || !(var_C8->unk_40 & 1))
            {
                var_C8 = (type_F2FF0 *)sub_F2FF0(var_8->unk_1DC, &var_60, 0, 1, 0, 0);
                if (var_8->unk_1F4)
                {
                    sub_121B90(var_C8, 1);
                }
            }
        }
        if (var_8->unk_1E0 && var_8->unk_1EC)
        {
            var_CC = sub_121BE0(2);
            if (var_CC == 0 || !(var_CC->unk_40 & 1))
            {
                var_CC = (type_F2FF0 *)sub_F2FF0(var_8->unk_1E0, &var_60, 0, 1, 0, 0);
                if (var_8->unk_1F8)
                {
                    sub_121B90(var_CC, 2);
                }
            }
        }
    }
    sub_6B5F0("ProjectileGeneratorFire", (type_67620 *)(get_trigger()->sub_BDF50()), (type_42E00_10 *)((RwInt32)get_trigger()), 0, 0, 0, 1, 0);
    return 1;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_11E440@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_11E440::operator delete(void *arg_0, void *arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_11E440@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_11E440::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}
