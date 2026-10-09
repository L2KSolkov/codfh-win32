// Split from unit_029ED0.cpp (now aidatapathing.cpp) at 0x032210, where the image starts
// another object: its .rdata begins at 0x3CE268 (the up axis, then its 16.666666 at 0x3CE274) with its own constants,
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
// 0x003CE268
extern const RwV3d stru_3CE268 = { 0.0f, 1.0f, 0.0f };
// 0x003CE274
extern const RwReal flt_3CE274 = 16.666666f;

// match: ?stru_3CE268@@3URwV3d@@B @ 0x003CE268
// match: ?flt_3CE274@@3MB @ 0x003CE274


// match: ??0type_3CE278@@QAE@XZ @ 0x00032210
// match: ??_7type_3CE278@@6B@ @ 0x003CE278
// match: ??_C@_0BE@IDLKJEIG@LTA_StartAlertStand?$AA@ @ 0x003CE2AC
// sp-match: ??0type_3CE278@@QAE@XZ @ 0x00027510
// symbol: ??0type_3CE6D0@@QAE@XZ = 0x0003CA10
// symbol: ??1type_3CE6D0@@UAE@XZ = 0x0003CA60
// symbol: ?vf_004@type_3CE6D0@@UAEXPAUtype_3DF30@@@Z = 0x0003CA80
// symbol: ?vf_00C@type_3CE6D0@@UAEHMPAUtype_3D410@@@Z = 0x0003CAB0
// symbol: ?vf_014@type_3CE6D0@@UAEXPAUtype_3D3548@@@Z = 0x0003CBB0
// symbol: ??_7type_3CE278@@6B@ = 0x003CE278
type_3CE278::type_3CE278()
{
}
#ifdef CODFH_SP // single player's copy of the folded body sits here, after the constructor (SP 0x27530)
// sp-match: ?vf_02C@type_3CE278@@UAEHXZ @ 0x00027530
RwInt32 type_3CE278::vf_02C()
{
    return 9;
}
#endif
// match: ?vf_010@type_3CE278@@UAEHPAUtype_3D410@@@Z @ 0x00032260
// match: ??_Gtype_3CE278@@UAEPAXI@Z @ 0x00032270
// match: ??1type_3CE278@@UAE@XZ @ 0x00032290
// sp-match: ??1type_3CE278@@UAE@XZ @ 0x00027540
// sp-match: ?vf_010@type_3CE278@@UAEHPAUtype_3D410@@@Z @ 0x0002A7C0
// sp-match: ??_Gtype_3CE278@@UAEPAXI@Z @ 0x000279C0
type_3CE278::~type_3CE278()
{
}
// match: ?vf_004@type_3CE278@@UAEXPAUtype_3DF30@@@Z @ 0x000322B0
// sp-match: ?vf_004@type_3CE278@@UAEXPAUtype_3DF30@@@Z @ 0x00027550
void type_3CE278::vf_004(type_3DF30 *arg_0)
{
    unk_1C = 0;
    unk_30 = 0;
    type_3CE6D0::vf_004(arg_0);
}
// match: sub_322E0 @ 0x000322E0
// sp-match: sub_322E0 @ 0x00027570
void type_3CE278::sub_322E0(type_3D410 *arg_0)
{
    AIData *var_4;
    type_3DF30 *local_8;

    unk_30 = 0;
    unk_1C = 0;
    unk_20.sub_D48D0(0);
    if (unk_24.sub_D4910() != 0) {
        var_4 = unk_24.sub_D4910()->vf_120();
        var_4->unk_58 = 0;
        var_4->sub_17AB0(0);
        local_8 = var_4->unk_56C;
        local_8->sub_3E990(unk_24.sub_D4910(), 0);
        unk_24.sub_D48D0(0);
    }
}
// match: ?vf_00C@type_3CE278@@UAEHMPAUtype_3D410@@@Z @ 0x00032390
// sp-match: ?vf_00C@type_3CE278@@UAEHMPAUtype_3D410@@@Z @ 0x00027B30
// The handlers' second argument carries the context here (their type says
// only its width), and the third a flag.
RwInt32 type_3CE278::vf_00C(RwReal arg_0, type_3D410 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    if (unk_30 == 0) {
        if (arg_4->unk_08 <= 0)
            return 1;
        unk_2C -= arg_0;
        if (unk_2C <= 0.0f) {
            unk_2C = 60.0f;
            if (sub_326D0(arg_4) != 0)
                unk_30 = 1;
            else
                return 1;
        } else {
            return 1;
        }
    }
    local_8 = 0;
    var_4 = 0;
    if (unk_30 != 3) {
        if (sub_32D30(arg_4) == 0) {
            sub_322E0(arg_4);
            return 1;
        }
        if (sub_32DD0(arg_4) == 0) {
            sub_322E0(arg_4);
            return 1;
        }
        local_8 = unk_24.sub_D4910();
        if (local_8 != 0) {
            var_4 = unk_24.sub_D4910()->vf_120();
            if (var_4 != 0)
                sub_12070(static_cast<type_3DBC78 *>(local_8), (RwInt32)arg_4);
        }
    }
    switch (unk_30) {
    case 1: {
        RwInt32 var_C;

        if (local_8 == 0) {
            sub_322E0(arg_4);
            break;
        }
        var_C = var_4->unk_5C == 5 && var_4->unk_58 == 4;
        if (var_C != 0) {
            unk_30 = 2;
            sub_12030(0x1E, static_cast<type_3DBC78 *>(unk_24.sub_D4910()), (RwInt32)arg_4,
                      (void *)1);
            sub_6B5F0("LTA_StartAlertStand", (type_67620 *)(unk_24.sub_D4910()->vf_098()), 0, 0, 0, 0, true, false);
        }
        break;
    }
    case 2: {
        RwInt32 var_10;

        var_10 = 0;
        if (local_8 != 0 && var_4 != 0)
            var_10 = (var_4->unk_5C == 0x1E && var_4->unk_58 == 4)
                    || (var_4->unk_5C == 0x1E && var_4->unk_58 == 2);
        else
            var_10 = 1;
        if (var_10 != 0) {
            unk_30 = 3;
            unk_28 = 300.0f;
            if (unk_24.sub_D4910() != 0) {
                type_3DF30 *var_18;
                AIData *var_14;

                var_14 = unk_24.sub_D4910()->vf_120();
                var_14->unk_58 = 0;
                var_14->sub_17AB0(0);
                var_18 = var_14->unk_56C;
                var_18->sub_3E990(unk_24.sub_D4910(), 0);
                unk_24.sub_D48D0(0);
            }
        }
        break;
    }
    case 3:
        unk_28 -= arg_0;
        if (unk_28 <= 0.0f) {
            sub_322E0(arg_4);
            return 1;
        }
        break;
    }
    return type_3CE6D0::vf_00C(arg_0, arg_4);
}
// match: sub_326D0 @ 0x000326D0
// sp-match: sub_326D0 @ 0x000279D0
RwInt32 type_3CE278::sub_326D0(type_3D410 *arg_0)
{
    unk_1C = sub_32750(arg_0);
    return unk_1C != 0;
}
// match: sub_32700 @ 0x00032700
// sp-match: sub_32700 @ 0x000275F0
// Reached only through the table at 0x427658 (the database had not made it a
// function). arg_0 is only known by width.
RwInt32 sub_32700(RwInt32 arg_0, type_3D410 *arg_4)
{
    type_3D3548 *var_4;
    type_3DF30 *local_8;

    local_8 = arg_4->unk_00;
    var_4 = local_8->unk_2BC.sub_D4910();
    if (var_4 != 0 && var_4->vf_00C() != 0)
        return -1;
    return 0x7FFFFFFF;
}
extern const RwV3d stru_3CE268;
#ifdef CODFH_PLAIN
extern type_3D3548 *&dword_4B8640;
#else
extern type_3D3548 *dword_4B8640;
#endif
// match: sub_32750 @ 0x00032750
// sp-match: sub_32750 @ 0x00027620
// A kind-15 node within 1500 of the group's leader (or its first entity);
// when an animated background entity in state 1 stands within 300 of it,
// the node takes that entity's "AT01" frame turned by 90 degrees (its
// orientation and point) and the entity is remembered in unk_20.
type_F8350 *type_3CE278::sub_32750(type_3D410 *arg_0)
{
    type_3DF30 *var_8;
    type_3D3548 *var_C;
    type_F8350 *var_74;
    RwReal var_78;
    type_3D32F8 *var_7C;
    type_3D3548 *var_80;
    type_3D32F8 *var_84;
    RwV3d var_94;
    RwReal var_98;
    RpClump *var_9C;
    RwInt32 var_A0;
    type_EC1F0 *var_A4;
    RwFrame *var_F4;

    var_8 = arg_0->unk_00;
    var_C = var_8->unk_2BC.sub_D4910();
    if (var_C == 0)
        var_C = var_8->unk_00;
    if (var_C == 0)
        return 0;
    type_154C0_1048 var_70;

    var_70.unk_04 = *var_C->sub_CD550();
    var_70.unk_10 = 1500.0f;
    var_70.unk_00 = 0;
    var_70.unk_18 = sub_F7E80(15);
    var_70.unk_1C = 0;
    sub_F8970(&var_70, 1, 0);
    var_74 = var_70.unk_34;
    if (var_74 == 0)
        return 0;
    var_78 = 1.0e37f;
    var_7C = 0;
    for (var_80 = dword_4B8640; var_80 != 0; var_80 = var_80->unk_10) {
        if (((var_80->unk_2C >> 8) & 1) != 0) {
            var_84 = static_cast<type_3D32F8 *>(var_80);
            if (var_84->get_unk_3D4() == 1) {
                var_94 = *var_84->sub_CD550();
                RwV3dSub(&var_94, &var_94, &var_74->unk_10);
                var_98 = RwV3dDotProduct(&var_94, &var_94);
                if (var_98 < var_78) {
                    var_78 = var_98;
                    var_7C = var_84;
                }
            }
        }
    }
    if (var_7C != 0 && var_78 < 90000.0f) {
        unk_20.sub_D48D0(var_7C);
        var_9C = var_7C->unk_25C.unk_08;
        if (var_9C != 0) {
            var_A0 = 0x41543031; // not an address: the frame's name, "AT01"
            var_A4 = sub_EC1F0(var_9C, var_A0);
            RwMatrix var_F0 = var_A4->unk_10;
            RwMatrixRotate(&var_F0, &stru_3CE268, 90.0f, rwCOMBINEPRECONCAT);
            RtQuatConvertFromMatrix(&var_74->unk_1C, &var_F0);
            var_F4 = RpClumpGetFrame(var_9C);
            RwMatrixTransform(&var_F0, RwFrameGetMatrix(var_F4), rwCOMBINEPOSTCONCAT);
            var_74->unk_10 = var_F0.pos;
        }
    }
    return var_74;
}
// match: sub_32A50 @ 0x00032A50
// sp-match: sub_32A50 @ 0x000279F0
type_3D3548 *type_3CE278::sub_32A50(type_F8350 *arg_0, RwInt32 arg_4, type_3D410 *arg_8)
{
    RwInt32 var_4;
    type_3DF30 *v8;
    type_32A50_20 l20;
    AIData *fp_24;

    v8 = arg_8->unk_00;
    l20.unk_00 = this;
    l20.unk_04 = &arg_0->unk_10;
    l20.unk_08 = 1.0e37f;
    l20.unk_0C = 0;
    l20.unk_10 = unk_24.sub_D4910();
    v8->sub_3E570(this, sub_32B40, 0x20, &l20);
    var_4 = 0;
    if (l20.unk_0C != 0) {
        l20.unk_0C->vf_120()->sub_22EF0(0);
        l20.unk_0C->vf_120()->sub_29380(0);
        fp_24 = l20.unk_0C->vf_120();
        fp_24->unk_5A8 = arg_0;
        fp_24->unk_5AC = arg_4;
        fp_24->unk_F5C = arg_0;
        var_4 = sub_12030(5, static_cast<type_3DBC78 *>(l20.unk_0C), (RwInt32)arg_8, 0);
    }
    if (var_4 != 0)
        return l20.unk_0C;
    return 0;
}
// match: sub_32B40 @ 0x00032B40
// sp-match: sub_32B40 @ 0x00027820
void sub_32B40(type_3D3548 *arg_0, void *arg_4)
{
    type_32A50_20 *var_4;
    RwReal v8;
    RwV3d l14;

    var_4 = (type_32A50_20 *)arg_4;
    if (arg_0 != var_4->unk_10) {
        l14 = *arg_0->sub_CD550();
        RwV3dSub(&l14, &l14, var_4->unk_04);
        v8 = RwV3dDotProduct(&l14, &l14);
        if (v8 < var_4->unk_08) {
            var_4->unk_08 = v8;
            var_4->unk_0C = arg_0;
        }
    }
}
// match: sub_32BF0 @ 0x00032BF0
// sp-match: sub_32BF0 @ 0x000278A0
RwInt32 type_3CE278::sub_32BF0(type_3D3548 *arg_0)
{
    AIData *var_1C;
    RwUInt32 var18;
    AIData *stk_14;
    RwUInt32 l10;
    RwUInt32 local_C;
    type_D48D0 *lv_8;
    type_3CE6D0 *var_4;

    lv_8 = 0;
    if (arg_0->vf_120()->unk_51C == 0 || (arg_0->unk_2C & 0x3FFFFF0) == 0x20000 // not an address: kind bits
            || ((arg_0->unk_2C >> 1) & 1) == 0)
        return 0;
    if (unk_24.sub_D4910() == 0)
        lv_8 = &unk_24;
    else
        return 0;
    stk_14 = arg_0->vf_120();
    local_C = stk_14->unk_574;
    var_4 = sub_3D3E0(local_C);
    if (var_4 != 0)
        var_4->vf_014(arg_0);
    var18 = l10 = unk_18;
    var_1C = arg_0->vf_120();
    var_1C->unk_574 = var18;
    lv_8->sub_D48D0(arg_0);
    return 1;
}
// match: ?vf_014@type_3CE278@@UAEXPAUtype_3D3548@@@Z @ 0x00032CF0
// sp-match: ?vf_014@type_3CE278@@UAEXPAUtype_3D3548@@@Z @ 0x00027940
void type_3CE278::vf_014(type_3D3548 *arg_0)
{
    if (unk_24.sub_D4910() == arg_0)
        unk_24.sub_D48D0(0);
    type_3CE6D0::vf_014(arg_0);
}
// match: sub_32D30 @ 0x00032D30
// sp-match: sub_32D30 @ 0x00027AC0
RwInt32 type_3CE278::sub_32D30(type_3D410 *arg_0)
{
    type_3D3548 *var_4;
    type_3D3548 *v8;
    type_3DF30 *varC;

    if (unk_24.sub_D4910() == 0) {
        unk_30 = 1;
        varC = arg_0->unk_00;
        var_4 = varC->unk_00;
        if (var_4 != 0 && var_4->vf_118() != 0) {
            v8 = sub_32A50(unk_1C, sub_FA920(unk_1C), arg_0);
            if (v8 != 0)
                sub_32BF0(v8);
            else
                return 0;
        }
    }
    return 1;
}
#ifdef CODFH_SP
// Single player compiles type_3CE6D0's sub_18F420 in this file: sub_32DD0's twin keeps edx
// (its argument) across the call (SP 0x27985), as VC does only for a callee in the same file.
// ?sub_18F420@type_3CE6D0@@QAEHPAUtype_F8350@@PAUtype_3D410@@@Z (folded into SP 0x61DA0)
RwInt32 type_3CE6D0::sub_18F420(struct type_F8350 * arg_0, struct type_3D410 * arg_4)
{
    return 1;
}
#endif

// match: sub_32DD0 @ 0x00032DD0
// sp-match: sub_32DD0 @ 0x00027970
RwInt32 type_3CE278::sub_32DD0(type_3D410 *arg_0)
{
    AIData *var_4;

    if (sub_18F420(unk_1C, arg_0) == 0)
        return 0;
    if (arg_0->unk_08 > 0)
        return 1;
    var_4 = unk_24.sub_D4910()->vf_120();
    if (unk_30 < 2 && var_4->unk_58 == 2)
        return 0;
    return 1;
}
