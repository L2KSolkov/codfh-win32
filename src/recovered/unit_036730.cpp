// type_3CE5AC, the kind-1 object sub_3CE20 creates, which pairs two group
// members at a spot by the leader and ends by sending them to
// "AIAction_AttackStand". It follows the Distance Scheduler (which ends at
// 0x36723) and precedes the kind-5 object at 0x390D0. Its original file
// name and end boundary are not yet recovered (M1), so it is named for its
// start address.

#include "rw/rtquat.h"
#include "types/type_154C0_1048.h"
#include "types/type_154C0_F80.h"
#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/type_10F710.h"
#include "types/type_3CE6D0.h"
#include "types/type_3CE5AC.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DBC78.h"
#include "types/type_3DF30.h"
#include "types/type_F8350.h"
#include "types/type_3CE1FC.h"
#include "types/type_DC400.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE5A4
extern const RwReal flt_3CE5A4 = 16.666666f;
// 0x003CE5A8
extern const RwReal flt_3CE5A8 = 16.666666f;
// End of its data definitions.


// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE5A4@@3MB @ 0x003CE5A4
// match: ?flt_3CE5A8@@3MB @ 0x003CE5A8
// match: ??_7type_3CE5AC@@6B@ @ 0x003CE5AC
// match: __ehhandler$?sub_37490@type_3CE5AC@@QAEPAUtype_F8350@@PAUtype_3D410@@@Z>1>8 @ 0x0041AF74
// match: __ehhandler$?sub_37490@type_3CE5AC@@QAEPAUtype_F8350@@PAUtype_3D410@@@Z>1 @ 0x0041AF7C

// match: ??0type_3CE5AC@@QAE@XZ @ 0x00036730

// symbol: ??_7type_3CE5AC@@6B@ = 0x003CE5AC
type_3CE5AC::type_3CE5AC()
{
}

// match: ?vf_02C@type_3CE5AC@@UAEHXZ @ 0x00036780

// match: ??_Gtype_3CE5AC@@UAEPAXI@Z @ 0x00036790
// match: ??1type_3CE5AC@@UAE@XZ @ 0x000367B0
type_3CE5AC::~type_3CE5AC()
{
}

// match: ?vf_004@type_3CE5AC@@UAEXPAUtype_3DF30@@@Z @ 0x000367D0
void type_3CE5AC::vf_004(type_3DF30 *arg_0)
{
    unk_1C = 0;
    unk_48 = 0;
    unk_28 = 0;
    unk_2C = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_44 = 0.0f;
    unk_38 = 0;
    unk_3C = 0;
    type_3CE6D0::vf_004(arg_0);
}

// match: sub_36850 @ 0x00036850
// Gives up: clears the state and sends both members back to their group.
void type_3CE5AC::sub_36850(type_3D410 *arg_0)
{
    type_3D3548 *l4;
    type_3DF30 *var_8;
    AIData *fp_C;
    AIData *local_10;
    type_3DF30 *stk_14;
    type_3DF30 *loc18;

    unk_48 = 0;
    unk_38 = 0;
    unk_3C = 0;
    unk_1C = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = -1;
    unk_2C = -1;
    var_8 = arg_0->unk_00;
    l4 = var_8->unk_2BC.sub_D4910();
    if (l4 != 0 && l4->vf_00C() != 0)
        l4->vf_00C()->sub_10F7E0(8, 0);
    if (unk_30.sub_D4910() != 0) {
        fp_C = unk_30.sub_D4910()->vf_120();
        fp_C->unk_52C = 0;
        fp_C->unk_58 = 0;
        fp_C->sub_17AB0(0);
        stk_14 = fp_C->unk_56C;
        stk_14->sub_3E990(unk_30.sub_D4910(), 0);
    }
    if (unk_34.sub_D4910() != 0) {
        local_10 = unk_34.sub_D4910()->vf_120();
        local_10->unk_52C = 0;
        local_10->unk_58 = 0;
        local_10->sub_17AB0(0);
        loc18 = local_10->unk_56C;
        loc18->sub_3E990(unk_34.sub_D4910(), 0);
    }
}

// match: ?vf_00C@type_3CE5AC@@UAEHMPAUtype_3D410@@@Z @ 0x000369E0
RwInt32 type_3CE5AC::vf_00C(RwReal arg_0, type_3D410 *arg_4)
{
    AIData *local_8;
    AIData *var_4;

    if (unk_48 == 0) {
        unk_44 -= arg_0;
        if (unk_44 <= 0.0f) {
            unk_44 = 60.0f;
            if (sub_371F0(arg_4))
                unk_48 = 1;
            else
                return 1;
        } else {
            return 1;
        }
    }
    if (!sub_380F0(arg_4)) {
        sub_36850(arg_4);
        return 1;
    }
    if (sub_37FB0(arg_4) == 0) {
        sub_36850(arg_4);
        unk_44 = 120.0f;
        return 0;
    }
    if (sub_38050(arg_4) == 0) {
        sub_36850(arg_4);
        unk_44 = 120.0f;
        return 0;
    }
    sub_12070(static_cast<type_3DBC78 *>(unk_30.sub_D4910()), (RwInt32)arg_4);
    sub_12070(static_cast<type_3DBC78 *>(unk_34.sub_D4910()), (RwInt32)arg_4);
    local_8 = unk_30.sub_D4910()->vf_120();
    var_4 = unk_34.sub_D4910()->vf_120();
    switch (unk_48) {
    case 1: {
        RwInt32 var_10;
        RwInt32 var_C;

        var_10 = local_8->unk_5C == 5 && local_8->unk_58 == 4;
        var_C = var_4->unk_5C == 5 && var_4->unk_58 == 4;
        if (var_10 != 0)
            sub_12030(8, static_cast<type_3DBC78 *>(unk_30.sub_D4910()), (RwInt32)arg_4, (void *)1);
        if (var_C != 0)
            sub_12030(8, static_cast<type_3DBC78 *>(unk_34.sub_D4910()), (RwInt32)arg_4, 0);
        if ((var_10 != 0 || local_8->unk_5C == 8) && (var_C != 0 || var_4->unk_5C == 8)) {
            unk_48 = 2;
            unk_40 = 120.0f;
        }
        break;
    }
    case 2: {
        type_3D3548 *var_14;
        type_3DF30 *var_18;
        type_10F710 *var_1C;

        var_18 = arg_4->unk_00;
        var_14 = var_18->unk_2BC.sub_D4910();
        if (var_14 != 0 && var_14->vf_00C() != 0) {
            var_1C = var_14->vf_00C();
            if (var_1C->sub_10F710() == 8) {
                unk_40 = -1.0f;
                var_1C->unk_2240 = 0;
                var_14->vf_00C()->sub_10F7E0(8, 0);
            } else {
                var_14->vf_00C()->sub_10F7E0(8, 1);
                dword_4B9190->sub_E0410(4);
            }
        } else {
            unk_40 -= arg_0;
        }
        local_8->unk_558 = 600.0f;
        var_4->unk_558 = 600.0f;
        if (unk_40 <= 0.0f) {
            sub_12030(6, static_cast<type_3DBC78 *>(unk_30.sub_D4910()), (RwInt32)arg_4, 0);
            unk_48 = 3;
        }
        break;
    }
    case 3: {
        RwInt32 var_20;

        if (local_8->unk_58 == 0) {
            unk_48 = 1;
            break;
        }
        if (var_4->unk_58 == 0) {
            unk_48 = 1;
            break;
        }
        if (local_8->unk_5C == 6 && local_8->unk_58 == 4) {
            var_20 = 0;
            if (unk_34.sub_D4910()->vf_008() != 0)
                var_20 = unk_34.sub_D4910()->vf_008()->get_unk_5E0();
            if (var_20 == 0) {
                sub_12030(7, static_cast<type_3DBC78 *>(unk_30.sub_D4910()), (RwInt32)arg_4, (void *)1);
                sub_12030(7, static_cast<type_3DBC78 *>(unk_34.sub_D4910()), (RwInt32)arg_4, 0);
                unk_48 = 5;
            } else {
                sub_12030(0x1D, static_cast<type_3DBC78 *>(unk_30.sub_D4910()), (RwInt32)arg_4, 0);
                sub_12030(0x1D, static_cast<type_3DBC78 *>(unk_34.sub_D4910()), (RwInt32)arg_4, 0);
                unk_48 = 4;
            }
        }
        break;
    }
    case 4: {
        RwInt32 local_28;
        RwInt32 var_24;

        if (local_8->unk_58 == 2 || local_8->unk_58 == 0) {
            sub_36850(arg_4);
            return 1;
        }
        if (var_4->unk_58 == 2 || var_4->unk_58 == 0) {
            sub_36850(arg_4);
            return 1;
        }
        var_24 = 0;
        if (unk_34.sub_D4910()->vf_008() != 0)
            var_24 = unk_34.sub_D4910()->vf_008()->get_unk_5E0();
        local_28 = 0;
        if (var_4->unk_5C != 0x1D || local_8->unk_58 == 4)
            local_28 = 1;
        if (local_28 != 0) {
            sub_12030(7, static_cast<type_3DBC78 *>(unk_30.sub_D4910()), (RwInt32)arg_4, (void *)1);
            sub_12030(7, static_cast<type_3DBC78 *>(unk_34.sub_D4910()), (RwInt32)arg_4, 0);
            unk_48 = 5;
        }
        break;
    }
    case 5: {
        RwInt32 var_2C;

        var_2C = 0;
        if (local_8->unk_58 == 2 || local_8->unk_58 == 0 || local_8->unk_58 == 4) {
            unk_38 = 1;
            if (sub_38D80(unk_30.sub_D4910(), unk_20) != 0) {
                var_2C = 1;
                if (sub_12030(2, static_cast<type_3DBC78 *>(unk_30.sub_D4910()), (RwInt32)arg_4, 0) == 0) {
                    unk_30.sub_D4910()->vf_120()->unk_52C = 1;
                    sub_6B5F0("AIAction_AttackStand", (type_67620 *)(unk_34.sub_D4910()->vf_098()), 0, 0, 0, 0, 1, 0);
                }
            } else {
                sub_12030(4, static_cast<type_3DBC78 *>(unk_30.sub_D4910()), (RwInt32)arg_4, 0);
            }
        }
        if (var_4->unk_58 == 2 || var_4->unk_58 == 0 || var_4->unk_58 == 4) {
            unk_3C = 1;
            if (sub_38D80(unk_34.sub_D4910(), unk_24) != 0) {
                if (sub_12030(2, static_cast<type_3DBC78 *>(unk_34.sub_D4910()), (RwInt32)arg_4, 0) == 0) {
                    unk_34.sub_D4910()->vf_120()->unk_52C = 1;
                    sub_6B5F0("AIAction_AttackStand", (type_67620 *)(unk_34.sub_D4910()->vf_098()), 0, 0, 0, 0, 1, 0);
                }
            } else {
                sub_12030(4, static_cast<type_3DBC78 *>(unk_34.sub_D4910()), (RwInt32)arg_4, 0);
            }
        }
        if (unk_38 != 0 && unk_3C != 0) {
            unk_40 = 120.0f;
            unk_48 = 6;
            return 1;
        }
        break;
    }
    case 6:
        unk_40 -= arg_0;
        if (unk_40 <= 0.0f) {
            sub_36850(arg_4);
            return 1;
        }
        break;
    }
    return type_3CE6D0::vf_00C(arg_0, arg_4);
}

// match: ?vf_010@type_3CE5AC@@UAEHPAUtype_3D410@@@Z @ 0x000371D0
RwInt32 type_3CE5AC::vf_010(type_3D410 *arg_0)
{
    return 0x7FFFFFFF;
}

// match: sub_371F0 @ 0x000371F0
// Looks for a spot (sub_37490), keeping it in unk_1C.
RwBool type_3CE5AC::sub_371F0(type_3D410 *arg_0)
{
    unk_1C = sub_37490(arg_0);
    return unk_1C != 0;
}

// match: sub_37220 @ 0x00037220
RwInt32 sub_37220(RwInt32 arg_0, type_3D410 *arg_4)
{
    type_3D3548 *var_4;
    type_3DF30 *local_8;

    local_8 = arg_4->unk_00;
    var_4 = local_8->unk_2BC.sub_D4910();
    if (var_4 == 0)
        return -1;
    if (var_4->vf_00C() == 0)
        return -1;
    return 0x7FFFFFFF;
}

// match: ?sub_37270@type_3CE5AC@@QAEPAUtype_F8350@@PAUtype_3D3548@@MM@Z @ 0x00037270
// The nearest kind-14 node within the radius arg_4 of arg_0 that lies ahead
// of it (the facing's dot product with the direction to it over arg_8).
type_F8350 *type_3CE5AC::sub_37270(type_3D3548 *arg_0, RwReal arg_4, RwReal arg_8)
{
    type_154C0_1048 var_68;
    type_154C0_F80 var_90[5];
    type_F8350 *var_94;
    RwReal var_98;
    RwInt32 var_9C;
    type_F8350 *var_A0;
    RwV3d var_B0;
    RwMatrix var_100;
    RwReal var_104;

    var_68.unk_04 = *arg_0->sub_CD550();
    var_68.unk_10 = arg_4;
    var_68.unk_00 = arg_0;
    var_68.unk_18 = sub_F7E80(0xE);
    var_68.unk_1C = 1;
    var_68.unk_24 = 5;
    var_68.unk_20 = var_90;
    sub_F8970(&var_68, 1, 0);
    var_94 = 0;
    var_98 = 1e37f;
    for (var_9C = 0; var_9C < var_68.unk_4C; var_9C++)
    {
        var_A0 = sub_FA980(var_68.unk_20[var_9C].unk_00);
        RwV3dSubMacro(&var_B0, &var_A0->unk_10, arg_0->sub_CD550());
        RwV3dNormalize(&var_B0, &var_B0);
        arg_0->vf_104(&var_100);
        var_104 = RwV3dDotProductMacro(&var_B0, &var_100.at);
        if (var_104 > arg_8 && var_68.unk_20[var_9C].unk_04 < var_98)
        {
            var_98 = var_68.unk_20[var_9C].unk_04;
            var_94 = var_A0;
        }
    }
    return var_94;
}

// match: ?sub_37490@type_3CE5AC@@QAEPAUtype_F8350@@PAUtype_3D410@@@Z @ 0x00037490
// match: __ehhandler$?sub_37490@type_3CE5AC@@QAEPAUtype_F8350@@PAUtype_3D410@@@Z-8 @ 0x002FF5C0
// match: __ehhandler$?sub_37490@type_3CE5AC@@QAEPAUtype_F8350@@PAUtype_3D410@@@Z @ 0x002FF5C8
// The spot near the group's leader (the player): a door node within 800
// (sub_37270) whose linked kind-7 and kind-8 nodes nearest it that face the
// leader become the two members' nodes (unk_20 and unk_24, with their numbers);
// 0 unless both are found.
type_F8350 *type_3CE5AC::sub_37490(type_3D410 *arg_0)
{
    type_3DF30 *var_18;
    type_3D3548 *var_1C;
    type_F8350 *var_20;
    RwUInt32 *var_24;
    type_4C00E8 *var_3C;
    RwReal var_40;
    RwReal var_44;
    type_F8350 *var_4C;
    RwV3d var_58;
    RwReal var_5C;
    type_F8350 *var_60;
    RwMatrix var_E0;
    RwReal var_E4;
    RwMatrix var_170;
    RwReal var_174;

    var_18 = arg_0->unk_00;
    var_1C = var_18->unk_2BC.sub_D4910();
    if (!var_1C)
    {
        return 0;
    }
    if (!var_1C->vf_00C())
    {
        return 0;
    }
    var_20 = sub_37270(var_1C, 800.0f, 0.5f);
    if (!var_20)
    {
        return 0;
    }
    var_24 = 0;
    unk_20 = 0;
    unk_24 = 0;
    if (var_20->unk_00_7)
    {
        if (var_20->unk_00 & 1)
        {
            var_24 = var_20->unk_2C;
        }
        else
        {
            var_24 = var_20->unk_1C_links;
        }
        type_3CE1FC var_38(var_24);
        var_3C = &unk_4C00E8;
        var_40 = 1.0e37f;
        var_44 = 1.0e37f;
        while (!var_38.at_end())
        {
            var_4C = var_3C->unk_2C[var_38.get_unk_0C()];
            if (var_4C->unk_04 == 7 || var_4C->unk_04 == 8)
            {
                RwV3dSubMacro(&var_58, &var_20->unk_10, &var_4C->unk_10);
                var_5C = RwV3dDotProductMacro(&var_58, &var_58);
                var_60 = var_4C;
                if (var_4C->unk_04 == 7 && var_5C < var_40)
                {
                    RwV3dSubMacro(&var_58, &var_60->unk_10, var_1C->sub_CD550());
                    RtQuatConvertToMatrix(&var_60->unk_1C, &var_E0);
                    var_E4 = RwV3dDotProductMacro(&var_E0.at, &var_58);
                    if (var_E4 >= 0.0f)
                    {
                        var_40 = var_5C;
                        unk_20 = var_4C;
                        unk_28 = var_38.unk_0C;
                    }
                }
                else if (var_4C->unk_04 == 8 && var_5C < var_44)
                {
                    RwV3dSubMacro(&var_58, &var_60->unk_10, var_1C->sub_CD550());
                    RtQuatConvertToMatrix(&var_60->unk_1C, &var_170);
                    var_174 = RwV3dDotProductMacro(&var_170.at, &var_58);
                    if (var_174 >= 0.0f)
                    {
                        var_44 = var_5C;
                        unk_24 = var_4C;
                        unk_2C = var_38.unk_0C;
                    }
                }
            }
            var_38.sub_31A10();
        }
    }
    if (!unk_20 || !unk_24)
    {
        var_20 = 0;
    }
    return var_20;
}

// match: sub_37C20 @ 0x00037C20
// Whether the spot arg_0 can still be used: flag 7 of its unk_00 or a state
// from 3 on.
RwInt32 type_3CE5AC::sub_37C20(type_F8350 *arg_0, type_3D410 *arg_4)
{
    return ((arg_0->unk_00 >> 7) & 1) != 0 || unk_48 >= 3;
}

// match: sub_37C60 @ 0x00037C60
// Finds the group member nearest the node arg_0 (sub_37D80), and when the
// node suits it (sub_38AD0) sends it there (action 5); returns the member.
type_3D3548 *type_3CE5AC::sub_37C60(type_F8350 *arg_0, RwInt32 arg_4, type_3D410 *arg_8)
{
    type_3DF30 *var_4;
    type_37C60_1C var_1C;
    AIData *l20;

    var_4 = arg_8->unk_00;
    var_1C.unk_00 = this;
    var_1C.unk_04 = &arg_0->unk_10;
    var_1C.unk_08 = 1.0e37f;
    var_1C.unk_0C = 0;
    var_1C.unk_10 = unk_30.sub_D4910();
    var_1C.unk_14 = unk_34.sub_D4910();
    var_4->sub_3E570(this, sub_37D80, 0x20, &var_1C);
    if (var_1C.unk_0C != 0) {
        if (sub_38AD0(var_1C.unk_0C, arg_0) == 0)
            return 0;
        var_1C.unk_0C->vf_120()->sub_22EF0(0);
        var_1C.unk_0C->vf_120()->sub_29380(0);
        l20 = var_1C.unk_0C->vf_120();
        l20->unk_5A8 = arg_0;
        l20->unk_5AC = arg_4;
        l20->unk_F5C = arg_0;
        var_1C.unk_0C->vf_120()->sub_236F0(arg_0);
        sub_12030(5, static_cast<type_3DBC78 *>(var_1C.unk_0C), (RwInt32)arg_8, 0);
    }
    return var_1C.unk_0C;
}

// match: sub_37D80 @ 0x00037D80
void sub_37D80(type_3D3548 *arg_0, void *arg_4)
{
    type_37C60_1C *var_4;
    RwReal v8;
    RwV3d l14;

    var_4 = (type_37C60_1C *)arg_4;
    if (arg_0 != var_4->unk_10 && arg_0 != var_4->unk_14 && ((arg_0->unk_2C >> 4) & 1) == 0) {
        l14 = *arg_0->sub_CD550();
        RwV3dSub(&l14, &l14, var_4->unk_04);
        v8 = RwV3dDotProduct(&l14, &l14);
        if (v8 < var_4->unk_08) {
            var_4->unk_08 = v8;
            var_4->unk_0C = arg_0;
        }
    }
}

// match: sub_37E50 @ 0x00037E50
// Takes the entity arg_0 on as the first or second member (whichever is
// free), taking it from the object it served (vf_014).
RwInt32 type_3CE5AC::sub_37E50(type_3D3548 *arg_0)
{
    type_3CE6D0 *l4;
    type_D48D0 *var_8;
    RwUInt32 fp_C;
    RwUInt32 local_10;
    AIData *stk_14;
    RwUInt32 lcl_18;
    AIData *fp_1C;

    var_8 = 0;
    if (arg_0->vf_120()->unk_51C == 0 || (arg_0->unk_2C & 0x3FFFFF0) == 0x20000) // not an address: kind bits
        return 0;
    if (unk_30.sub_D4910() == 0)
        var_8 = &unk_30;
    else if (unk_34.sub_D4910() == 0)
        var_8 = &unk_34;
    else
        return 0;
    stk_14 = arg_0->vf_120();
    fp_C = stk_14->unk_574;
    l4 = sub_3D3E0(fp_C);
    if (l4 != 0)
        l4->vf_014(arg_0);
    lcl_18 = local_10 = unk_18;
    fp_1C = arg_0->vf_120();
    fp_1C->unk_574 = lcl_18;
    var_8->sub_D48D0(arg_0);
    return 1;
}

// match: ?vf_014@type_3CE5AC@@UAEXPAUtype_3D3548@@@Z @ 0x00037F50
void type_3CE5AC::vf_014(type_3D3548 *arg_0)
{
    if (unk_30.sub_D4910() == arg_0)
        unk_30.sub_D48D0(0);
    else if (unk_34.sub_D4910() == arg_0)
        unk_34.sub_D48D0(0);
    type_3CE6D0::vf_014(arg_0);
}

// match: sub_37FB0 @ 0x00037FB0
// Gets the first member to its node: 0 while it is not there yet.
RwInt32 type_3CE5AC::sub_37FB0(type_3D410 *arg_0)
{
    type_3D3548 *var_4;

    if (unk_30.sub_D4910() == 0) {
        unk_48 = 1;
        var_4 = sub_37C60(unk_20, unk_28, arg_0);
        if (var_4 != 0)
            sub_37E50(var_4);
        else
            return 0;
    } else if (((unk_30.sub_D4910()->vf_120()->unk_49C >> 4) & 1) == 0) {
        return 0;
    }
    return 1;
}

// match: sub_38050 @ 0x00038050
// Likewise for the second member.
RwInt32 type_3CE5AC::sub_38050(type_3D410 *arg_0)
{
    type_3D3548 *var_4;

    if (unk_34.sub_D4910() == 0) {
        unk_48 = 1;
        var_4 = sub_37C60(unk_24, unk_2C, arg_0);
        if (var_4 != 0)
            sub_37E50(var_4);
        else
            return 0;
    } else if (((unk_34.sub_D4910()->vf_120()->unk_49C >> 4) & 1) == 0) {
        return 0;
    }
    return 1;
}

// match: ?sub_380F0@type_3CE5AC@@QAEHPAUtype_3D410@@@Z @ 0x000380F0
// Whether the spot unk_1C still holds: it passes sub_37C20, the leader is the
// player and near it (the spot sub_37270 finds, or within 900 ahead, 500
// otherwise); before the members move (state 3 or less) neither the player's
// target nor its AI object's enemy (for under 180) is behind the first
// member's node; and each member still suits its node (sub_38AD0), none of
// them fleeing (unk_58 2) before then.
RwBool type_3CE5AC::sub_380F0(type_3D410 *arg_0)
{
    type_3DF30 *var_8;
    type_3D3548 *var_C;
    type_F8350 *var_10;
    RwV3d var_20;
    RwReal var_2C;
    RwMatrix var_70;
    RwReal var_74;
    RwReal var_78;
    type_F8350 *var_7C;
    RwInt32 var_80;
    type_3D3548 *var_84;
    RwMatrix var_110;
    RwV3d var_11C;
    AIData *var_120;
    type_3D3548 *var_124;
    AIData *var_128;
    RwReal var_12C;
    RwV3d var_16C;
    type_3D3548 *var_170;
    AIData *var_174;
    type_3D3548 *var_178;
    AIData *var_17C;

    if (!sub_37C20(unk_1C, arg_0))
    {
        return 0;
    }
    var_8 = arg_0->unk_00;
    var_C = var_8->unk_2BC.sub_D4910();
    if (!var_C || !var_C->vf_00C())
    {
        return 0;
    }
    var_10 = sub_37270(var_C, 500.0f, 0.9f);
    if (var_10 && var_10 != unk_1C)
    {
        return 0;
    }
    if (!var_10)
    {
        RwV3dSubMacro(&var_20, &unk_1C->unk_10, var_C->sub_CD550());
        var_2C = RwV3dDotProductMacro(&var_20, &var_20);
        RwV3dNormalize(&var_20, &var_20);
        var_C->vf_104(&var_70);
        var_74 = RwV3dDotProductMacro(&var_20, &var_70.at);
        if (var_74 > 0.5f)
        {
            var_78 = 810000.0f;
        }
        else
        {
            var_78 = 250000.0f;
        }
        if (var_2C > var_78)
        {
            return 0;
        }
    }
    if (unk_48 <= 3 && var_C->vf_00C())
    {
        var_7C = unk_20;
        var_80 = 0;
        var_84 = 0;
        if (var_C->vf_00C()->unk_1A34.sub_D4910())
        {
            var_84 = var_C->vf_00C()->unk_1A34.sub_D4910();
        }
        if (var_84 && var_84->vf_120())
        {
            if (cmp_unk_2C(var_C, var_84) && !var_84->unk_28_9 && !(var_84->unk_28 & 1))
            {
                if (!var_80)
                {
                    RtQuatConvertToMatrix(&var_7C->unk_1C, &var_110);
                    var_80 = 1;
                }
                RwV3dSubMacro(&var_11C, var_84->sub_CD550(), &var_7C->unk_10);
                if (RwV3dDotProductMacro(&var_110.at, &var_11C) < 0.0f)
                {
                    return 0;
                }
            }
        }
        var_120 = var_C->vf_120();
        var_124 = var_120->unk_1390.sub_D4910();
        if (var_124 && !var_124->unk_28_9 && !(var_124->unk_28 & 1))
        {
            var_128 = var_C->vf_120();
            var_12C = var_128->unk_1394;
            if (var_12C < 180.0f)
            {
                if (!var_80)
                {
                    RtQuatConvertToMatrix(&var_7C->unk_1C, &var_110);
                    var_80 = 1;
                }
                RwV3dSubMacro(&var_16C, var_124->sub_CD550(), &var_7C->unk_10);
                if (RwV3dDotProductMacro(&var_110.at, &var_16C) < 0.0f)
                {
                    return 0;
                }
            }
        }
    }
    if (unk_30.sub_D4910())
    {
        var_170 = unk_30.sub_D4910();
        var_174 = var_170->vf_120();
        if (unk_48 <= 3 && var_174->unk_58 == 2)
        {
            return 0;
        }
        if (!sub_38AD0(unk_30.sub_D4910(), unk_20))
        {
            return 0;
        }
    }
    if (unk_34.sub_D4910())
    {
        var_178 = unk_34.sub_D4910();
        var_17C = var_178->vf_120();
        if (unk_48 <= 3 && var_17C->unk_58 == 2)
        {
            return 0;
        }
        if (!sub_38AD0(unk_34.sub_D4910(), unk_24))
        {
            return 0;
        }
    }
    return 1;
}

// match: ?sub_38AD0@type_3CE5AC@@QAEHPAUtype_3D3548@@PAUtype_F8350@@@Z @ 0x00038AD0
RwInt32 type_3CE5AC::sub_38AD0(type_3D3548 *arg_0, type_F8350 *arg_4)
{
    AIData *var_8;
    RwMatrix var_80;
    RwInt32 var_84;
    type_3D3548 *var_88;
    RwV3d var_94;

    var_8 = arg_0->vf_120();
    RtQuatConvertToMatrix(&arg_4->unk_1C, &var_80);
    for (var_84 = 0; var_84 < 0x20; var_84++)
    {
        var_88 = var_8->unk_80[var_84].unk_00.sub_D4910();
        if (var_88 && sub_3DE00(arg_0, var_88) && ((var_8->unk_80[var_84].unk_04 >> 1) & 1))
        {
            RwV3dSubMacro(&var_94, var_88->sub_CD550(), &arg_4->unk_10);
            if (RwV3dDotProductMacro(&var_80.at, &var_94) < 0.0f)
            {
                return 0;
            }
        }
    }
    return 1;
}

// match: ?sub_38D80@type_3CE5AC@@QAEHPAUtype_3D3548@@PAUtype_F8350@@@Z @ 0x00038D80
RwInt32 type_3CE5AC::sub_38D80(type_3D3548 *arg_0, type_F8350 *arg_4)
{
    AIData *var_8;
    RwMatrix var_80;
    type_3D3548 *var_84;
    RwReal var_88;
    RwInt32 var_8C;
    type_3D3548 *var_90;
    RwV3d var_9C;
    RwReal var_A0;

    if (!arg_0)
    {
        return 0;
    }
    var_8 = arg_0->vf_120();
    RtQuatConvertToMatrix(&arg_4->unk_1C, &var_80);
    var_84 = 0;
    var_88 = 1e37f;
    for (var_8C = 0; var_8C < 0x20; var_8C++)
    {
        var_90 = var_8->unk_80[var_8C].unk_00.sub_D4910();
        if (var_90 && sub_3DE00(arg_0, var_90) && ((var_8->unk_80[var_8C].unk_04 >> 1) & 1))
        {
            RwV3dSubMacro(&var_9C, var_90->sub_CD550(), &arg_4->unk_10);
            if (RwV3dDotProductMacro(&var_80.at, &var_9C) > 0.0f)
            {
                var_A0 = RwV3dDotProductMacro(&var_9C, &var_9C);
                if (var_A0 < var_88)
                {
                    var_84 = var_90;
                    var_88 = var_A0;
                }
            }
        }
    }
    if (var_84)
    {
        arg_0->vf_120()->sub_18BB0(var_84);
        return 1;
    }
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@type_3CE5AC@@UAEXXZ (folded into 0x39440)
void type_3CE5AC::vf_008()
{
    type_3CE6D0::vf_008();
}

// ?vf_030@type_3CE5AC@@UAEHXZ (folded into 0x115460)
RwInt32 type_3CE5AC::vf_030()
{
    return 1;
}
