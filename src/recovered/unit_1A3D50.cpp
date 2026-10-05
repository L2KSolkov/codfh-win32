// The multiplayer game's bomb sites (game/bombsites.h).

#include <stdio.h>
#include <string.h>

#include "rw/bamatrix.h"
#include "game/bombsites.h"
#include "game/objectives.h"
#include "types/type_4AE70.h"
#include "types/type_DC400.h"
#include "types/type_44350.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_10F710.h"
#include "types/type_3DF8D8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E1200
extern const RwReal flt_3E1200 = 16.666666f;
// 0x003E1204
extern const RwReal flt_3E1204 = 0.01f;
// 0x003E1208
extern const RwReal flt_3E1208 = 0.01f;
// End of its data definitions.


// The sites themselves, built by their dynamic initializer.
type_4F6950 dword_4F6950;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E1200@@3MB @ 0x003E1200
// match: ?flt_3E1204@@3MB @ 0x003E1204
// match: ?flt_3E1208@@3MB @ 0x003E1208
// match: ??_C@_0BD@EOLCMBLF@MW_OBJ_COMPLETE_?$CFc?$AA@ @ 0x003E120C
// match: ??_C@_0M@FMKMEEMM@ExplodeBomb?$AA@ @ 0x003E1220
// match: ??_C@_0BE@GIHCMIJ@MW_OBJ_BOMBPLANT_?$CFc?$AA@ @ 0x003E122C
// match: ??_C@_0BD@EKNKEPKM@MW_OBJ_BOMBDIFF_?$CFc?$AA@ @ 0x003E1240
// match: ??_C@_0CA@FKGONHG@DestroyChildrenAndAllowRecreate?$AA@ @ 0x003E1254
// match: ??_C@_0BA@GNGMLIPD@CreateBombAtPos?$AA@ @ 0x003E1274
// match: __ehhandler$?sub_1A3E60@type_4F6950@@QAEXH@Z>1>8 @ 0x0041EA44
// match: __ehhandler$?sub_1A3E60@type_4F6950@@QAEXH@Z>1 @ 0x0041EA4C
// match: __ehhandler$?sub_1A4200@type_4F6950@@QAEXHHHPAURwV3d@@@Z>1>8 @ 0x0041EA68
// match: __ehhandler$?sub_1A4200@type_4F6950@@QAEXHHHPAURwV3d@@@Z>1 @ 0x0041EA78
// match: .CRT$XCU+0 @ 0x004271A8

// match: _$E2 @ 0x0030C130
// match: ?sub_1A3D50@type_4F6950@@QAEHH@Z @ 0x001A3D50

RwInt32 type_4F6950::sub_1A3D50(RwInt32 arg_0)
{
    if (unk_00[arg_0].unk_04 == 0 && type_4F805C::get()->sub_1B8420() != dword_4FB9E0.get_team_count())
        return 1;
    if (unk_00[arg_0].unk_04 == 5 && type_4F805C::get()->sub_1B8420() != dword_4FB9E0.get_team_count())
        return 6;
    return unk_00[arg_0].unk_04;
}

// match: ?sub_1A3E00@type_4F6950@@QAEXH@Z @ 0x001A3E00
void type_4F6950::sub_1A3E00(RwInt32 arg_0)
{
    sub_1A3E60(arg_0);
    sub_1A41C0(arg_0, 5, -1, 0);
}

// match: ?sub_1A3E30@type_4F6950@@QAEXH@Z @ 0x001A3E30
void type_4F6950::sub_1A3E30(RwInt32 arg_0)
{
    sub_1A3E60(arg_0);
    sub_1A4200(arg_0, 5, -1, 0);
}

// match: ?sub_1A3E60@type_4F6950@@QAEXH@Z @ 0x001A3E60
// match: __ehhandler$?sub_1A3E60@type_4F6950@@QAEXH@Z-8 @ 0x00302880
// match: __ehhandler$?sub_1A3E60@type_4F6950@@QAEXH@Z @ 0x00302888
// Explodes the bomb planted at site arg_0: tells its planter
// ("ExplodeBomb"), sets off a blast (0x804, 1550 wide) at the site, and
// shows the site's "MW_OBJ_COMPLETE_<letter>" text.
void type_4F6950::sub_1A3E60(RwInt32 arg_0)
{
    RwInt32 var_1C;
    RwMatrix var_90;
    RwChar var_D0[0x40];
    RwChar var_1F8[0x100];

    if (!unk_00[arg_0].unk_14 || unk_00[arg_0].unk_04 != 3)
        return;
    var_1C = 0;
    sub_6B5F0("ExplodeBomb", (type_67620 *)unk_00[arg_0].unk_14, 0, 0, 0, 0, 1, 0);
    type_4AE70 var_50;
    RwMatrixSetIdentityMacro(&var_90);
    var_90.pos = unk_00[arg_0].unk_08;
    var_50.unk_08 = 0;
    var_50.unk_0C = &var_90;
    var_50.unk_10 = 1550.0f;
    var_50.unk_14 = 1550.0f;
    var_50.unk_18 = 1550.0f;
    var_50.unk_2C = 240.0f;
    var_50.unk_00 = 0x804;
    sub_9A960(&var_50);
    sprintf(var_D0, "MW_OBJ_COMPLETE_%c", arg_0 + 'A');
    strcpy(var_1F8, sub_E3970(var_D0, 1).c_str());
    sub_EACA0(var_1F8, 0, 0);
}

// match: ?sub_1A4090@type_4F6950@@QAEHH@Z @ 0x001A4090
RwInt32 type_4F6950::sub_1A4090(RwInt32 arg_0)
{
    if (unk_00[arg_0].unk_04 == 0)
        return 1;
    return 0;
}

// match: ?sub_1A40C0@type_4F6950@@QAEHPAURwV3d@@H@Z @ 0x001A40C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_4F6950::sub_1A40C0(RwV3d *arg_0, RwInt32 arg_4)
{
    RwInt32 var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 5; l4++)
    {
        if (!arg_4 && unk_00[l4].unk_04 != 3)
            continue;
        var_8 = sub_92860(arg_0, &unk_00[l4].unk_08, 100.0f, 200.0f);
        if (var_8 == 1)
            return l4;
    }
    return -1;
}

// match: ?sub_1A4140@type_4F6950@@QAEHH@Z @ 0x001A4140
RwInt32 type_4F6950::sub_1A4140(RwInt32 arg_0)
{
    if (arg_0 == 3 || arg_0 == 4)
        return 1;
    return 0;
}

// match: ?sub_1A4170@type_4F6950@@QAEHPAUtype_712B0@@@Z @ 0x001A4170
RwInt32 type_4F6950::sub_1A4170(class type_712B0 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
    {
        if (unk_00[var_4].unk_00 == arg_0)
            return var_4;
    }
    return -1;
}

// match: ?sub_1A41C0@type_4F6950@@QAEXHHHPAURwV3d@@@Z @ 0x001A41C0
void type_4F6950::sub_1A41C0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C)
{
    unk_4F8184.sub_1A7D80(arg_0, arg_4, arg_C);
    sub_1A4200(arg_0, arg_4, arg_8, arg_C);
}

inline type_3DF8D8_04 *site_objective(type_4F6950 *arg_0, RwInt32 arg_4);
// match: ?sub_1A4200@type_4F6950@@QAEXHHHPAURwV3d@@@Z @ 0x001A4200
// match: __ehhandler$?sub_1A4200@type_4F6950@@QAEXHHHPAURwV3d@@@Z-0x16 @ 0x003028A0
// match: __ehhandler$?sub_1A4200@type_4F6950@@QAEXHHHPAURwV3d@@@Z @ 0x003028B6
void type_4F6950::sub_1A4200(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C)
{
    RwChar l54[0x40];
    RwInt32 stk_58;
    RwChar var_15C[0x100];
    RwV3d var_168;

    stk_58 = 0;
    if ((bool)sub_1A4140(arg_4) && !(bool)sub_1A4140(unk_00[arg_0].unk_04) && unk_00[arg_0].unk_00 && arg_C)
    {
        var_168.x = arg_C->x;
        var_168.y = arg_C->y;
        var_168.z = arg_C->z;
        unk_00[arg_0].unk_08 = *arg_C;
        sub_6B5F0("CreateBombAtPos", (type_67620 *)(unk_00[arg_0].unk_00->sub_BDF50()), 0, 0, (RwInt32 *)(&var_168), 3, 1, 0);
    }
    if (!sub_1A4140(arg_4) && sub_1A4140(unk_00[arg_0].unk_04) == 1)
    {
        if (unk_00[arg_0].unk_00)
            sub_6B5F0("DestroyChildrenAndAllowRecreate", (type_67620 *)(unk_00[arg_0].unk_00->sub_BDF50()), 0, 0, &stk_58, 1, 1, 0);
        unk_00[arg_0].unk_14 = 0;
    }
    sub_170790(&unk_00[arg_0].unk_00->unk_28, -2);
    sub_171480(&unk_00[arg_0].unk_00->unk_28, 0);
    switch (arg_4)
    {
    case 0:
        if (arg_8 != -1 && unk_00[arg_0].unk_04 == 4)
        {
            sprintf(l54, "MW_OBJ_BOMBDIFF_%c", arg_0 + 'A');
            sub_1CB000(var_15C, sub_E3970(l54, 1).c_str(), type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
            sub_EACA0(var_15C, 0, 0);
        }
        break;
    case 1:
        break;
    case 2:
        sub_170710(&unk_00[arg_0].unk_00->unk_28, 2);
        sub_171480(&unk_00[arg_0].unk_00->unk_28, 1);
        break;
    case 3:
        if (arg_8 != -1 && unk_00[arg_0].unk_04 == 2)
        {
            sprintf(l54, "MW_OBJ_BOMBPLANT_%c", arg_0 + 'A');
            sub_1CB000(var_15C, sub_E3970(l54, 1).c_str(), type_4F8054::get()->get_unk_B0()->unk_90[arg_8].unk_00);
            sub_EACA0(var_15C, 0, 0);
        }
        sub_170710(&unk_00[arg_0].unk_00->unk_28, 0x80);
        sub_171480(&unk_00[arg_0].unk_00->unk_28, 1);
        break;
    case 4:
        sub_170710(site_objective(this, arg_0), 0x80);
        sub_170710(site_objective(this, arg_0), 2);
        sub_171480(site_objective(this, arg_0), 1);
        break;
    case 5:
        sub_170710(site_objective(this, arg_0), 4);
    }
    unk_00[arg_0].unk_04 = arg_4;
    sub_170790(site_objective(this, arg_0), -2);
    if (arg_4 == 3 || arg_4 == 4)
        sub_170710(site_objective(this, arg_0), 2);
    if (arg_4 == 5)
        sub_170710(site_objective(this, arg_0), 4);
}

// match: ?sub_1A47B0@type_4F6950@@QAEXPAUtype_3D2E7C@@HH@Z @ 0x001A47B0
void type_4F6950::sub_1A47B0(struct type_3D2E7C *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    unk_00[arg_4].unk_14 = arg_0;
    unk_00[arg_4].unk_18 = arg_8;
    unk_4F8184.sub_1A84A0(arg_4, arg_8);
}

// match: ??0type_4F6950@@QAE@XZ @ 0x001A47F0
type_4F6950::type_4F6950()
{
    sub_1A4850();
}

// match: ?sub_1A4850@type_4F6950@@QAEXXZ @ 0x001A4850
void type_4F6950::sub_1A4850()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
    {
        unk_00[var_4].unk_00 = 0;
        unk_00[var_4].unk_04 = 0;
        unk_00[var_4].unk_14 = 0;
    }
}

// The objective of the site arg_4's trigger (its unk_28): a free inline with
// no address. Evidence: the state change (sub_1A4200) reaches it from its
// fourth state on, and its frame holds the leftovers of one expansion per
// use.
inline type_3DF8D8_04 *site_objective(type_4F6950 *arg_0, RwInt32 arg_4)
{
    return &arg_0->unk_00[arg_4].unk_00->unk_28;
}

// match: ?sub_1A48B0@type_4F6950@@QAEXHPAUtype_712B0@@@Z @ 0x001A48B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4F6950::sub_1A48B0(RwInt32 arg_0, class type_712B0 *arg_4)
{
    RwInt32 var_C;
    RwInt32 bp_8;
    type_3DF8D8_04 *bp_4;

    if (dword_4FB9E0.get_unk_08() != 8)
        return;
    unk_00[arg_0].unk_00 = arg_4;
    bp_4 = &arg_4->unk_28;
    var_C = 1;
    bp_8 = 0;
    sub_1703B0(bp_4, var_C, bp_8);
    sub_171070(bp_4, arg_4);
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1B8420@type_4F805C@@QAEHXZ (folded into 0x1B8420)
RwInt32 type_4F805C::sub_1B8420()
{
    RwInt32 r = unk_4F7EB8.unk_29C;
    return r;
}
