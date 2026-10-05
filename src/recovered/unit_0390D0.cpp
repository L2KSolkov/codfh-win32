// type_3CE5E8, the kind-5 object sub_3CE20 creates: the fire-and-movement
// advance. It follows type_3CE5AC's unit and precedes the AIHearing class
// (from sub_3C1D0, "Somebody forgot to unregister in the AIHearing Class!").
// Its original file name and end boundary are not yet recovered (M1), so it
// is named for its start address.

#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/type_3CE6D0.h"
#include "types/type_3CE5E8.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DBC78.h"
#include "types/type_F8350.h"
#include "types/type_3DF30.h"
#include "types/type_143DC0.h"
#include "game/kujuui.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE5E0
extern const RwReal flt_3CE5E0 = 16.666666f;
// 0x003CE5E4
extern const RwReal flt_3CE5E4 = 16.666666f;
// End of its data definitions.


// The entity handle's constructor (inline in its class, emitted out of line
// here, where an array of handles is built), placed at the first object's copy
// (pCtor).
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE5E0@@3MB @ 0x003CE5E0
// match: ?flt_3CE5E4@@3MB @ 0x003CE5E4
// match: ??_7type_3CE5E8@@6B@ @ 0x003CE5E8
// match: ??_C@_0BI@HHNNEEAM@FireAndMovementFinished?$AA@ @ 0x003CE61C
// match: __real@442f0000 @ 0x003CE634
// match: ??_C@_0BH@HJLLGAPG@FireAndMovementCleared?$AA@ @ 0x003CE638
// match: __real@3f266666 @ 0x003CE650
// match: __real@453b8000 @ 0x003CE654
// match: __ehhandler$??1type_3CE5E8@@UAE@XZ>1>8 @ 0x0041AF98
// match: __ehhandler$??1type_3CE5E8@@UAE@XZ>1 @ 0x0041AFB0
// match: __ehhandler$??0type_3CE5E8@@QAE@XZ>1>8 @ 0x0041AFCC
// match: __ehhandler$??0type_3CE5E8@@QAE@XZ>1 @ 0x0041AFE4
// match: __ehhandler$?sub_39AA0@@YAHHPAUtype_3D410@@@Z>1>8 @ 0x0041B000
// match: __ehhandler$?sub_39AA0@@YAHHPAUtype_3D410@@@Z>1 @ 0x0041B008
// match: __ehhandler$?sub_3B7E0@type_3CE5E8@@QAEHXZ>1>8 @ 0x0041B024
// match: __ehhandler$?sub_3B7E0@type_3CE5E8@@QAEHXZ>1 @ 0x0041B02C

// match: ??0type_3CE5E8@@QAE@XZ @ 0x000390D0
// match: __ehhandler$??0type_3CE5E8@@QAE@XZ-0x36 @ 0x002FF5E0
// match: __ehhandler$??0type_3CE5E8@@QAE@XZ @ 0x002FF616

// The destructor's handler and funclets are the same bytes, folded by
// /OPT:ICF into these.
// symbol: ??_7type_3CE5E8@@6B@ = 0x003CE5E8
type_3CE5E8::type_3CE5E8()
{
}

// match: ?vf_02C@type_3CE5E8@@UAEHXZ @ 0x00039180

// match: ??_Gtype_3CE5E8@@UAEPAXI@Z @ 0x00039190
// match: ??1type_3CE5E8@@UAE@XZ @ 0x000391B0
type_3CE5E8::~type_3CE5E8()
{
}

// match: ?vf_004@type_3CE5E8@@UAEXPAUtype_3DF30@@@Z @ 0x00039250
void type_3CE5E8::vf_004(type_3DF30 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x20; var_4++) {
        unk_1C[var_4].unk_00.sub_D48D0(0);
        unk_1C[var_4].unk_04 = 0;
        unk_1C[var_4].unk_08 = 0;
        unk_1C[var_4].unk_0C = 0;
        unk_29C[var_4].unk_00.sub_D48D0(0);
        unk_29C[var_4].unk_04 = 0;
        unk_29C[var_4].unk_08 = 0;
        unk_29C[var_4].unk_0C = 0;
        unk_524[var_4].sub_D48D0(0);
    }
    unk_5A4 = unk_1C;
    unk_5A8 = unk_29C;
    unk_5B8 = 0;
    unk_5BC = 0;
    unk_5C0 = 0;
    unk_5C4 = 0;
    unk_51C = 0;
    unk_520 = 0;
    unk_5C8 = 0.0f;
    unk_5CC = 0.0f;
    unk_5D0 = 0;
    unk_5D4 = 1;
    unk_5D8 = 0.0f;
    unk_5DC = 1000.0f;
    unk_5E0 = 1000000.0f;
    unk_5E8 = 2250000.0f;
    unk_5E4 = 1500.0f;
    unk_5EC = 360;
    unk_5F0 = 480;
    type_3CE6D0::vf_004(arg_0);
}

// match: ?vf_008@type_3CE5E8@@UAEXXZ @ 0x00039440
// sub_39440: also type_3CE278's and type_3CE5AC's slot +0x008, folded by
// /OPT:ICF.
void type_3CE5E8::vf_008()
{
    type_3CE6D0::vf_008();
}

// ??1type_143D90@@QAE@XZ (folded into 0x39440)
type_143D90::~type_143D90()
{
}

// ??1type_1E37A0@kujuUI@@QAE@XZ (folded into 0x39440)
kujuUI::type_1E37A0::~type_1E37A0()
{
}

// match: ?vf_00C@type_3CE5E8@@UAEHMPAUtype_3D410@@@Z @ 0x00039460
RwInt32 type_3CE5E8::vf_00C(RwReal arg_0, type_3D410 *arg_4)
{
    type_3D3548 *l4;
    RwInt32 var_8;
    AIData *fp_C;
    RwReal local_10;
    AIData *stk_14;
    RwReal loc18;

    l4 = 0;
    if (unk_5D8 > 0.0f) {
        unk_5D8 -= arg_0;
        return type_3CE6D0::vf_00C(arg_0, arg_4);
    }
    if (unk_51C == 0 && unk_520 == 0)
        return type_3CE6D0::vf_00C(arg_0, arg_4);
    if (unk_5B8 != 0) {
        if (unk_5D4 == 0 && unk_5C4 == 0 && sub_3C070() == 0) {
            sub_3C110();
            unk_5D8 = 600.0f;
            unk_5D4 = 1;
            return type_3CE6D0::vf_00C(arg_0, arg_4);
        }
        unk_5D4 = 0;
        sub_3B7E0();
    }
    for (var_8 = 0; var_8 < 0x20; var_8++) {
        l4 = unk_5A4[var_8].unk_00.sub_D4910();
        if (l4 != 0) {
            if (((l4->unk_28 >> 9) & 1) != 0) {
                l4->vf_120()->get_unk_56C()->sub_3E990(l4, 0);
            } else {
                unk_5A4[var_8].unk_10 = sub_140C90(l4->sub_CD550(), &unk_5AC);
                fp_C = l4->vf_120();
                if (fp_C->sub_238E0(0) != 0)
                    local_10 = (unk_5DC + 700.0f) * (unk_5DC + 700.0f);
                else
                    local_10 = unk_5E0;
                if (unk_5A4[var_8].unk_10 < local_10) {
                    l4->vf_120()->set_unk_7C(600.0f);
                    sub_6B5F0("FireAndMovementFinished", (type_67620 *)(l4->vf_098()), 0, 0, 0, 0, 1, 0);
                    l4->vf_120()->get_unk_56C()->sub_3E990(l4, 0);
                } else {
                    sub_3A9C0(static_cast<type_3DBC78 *>(l4), &unk_5A4[var_8], arg_4);
                }
            }
        }
        l4 = unk_5A8[var_8].unk_00.sub_D4910();
        if (l4 != 0) {
            if (((l4->unk_28 >> 9) & 1) != 0) {
                l4->vf_120()->get_unk_56C()->sub_3E990(l4, 0);
            } else {
                unk_5A8[var_8].unk_10 = sub_140C90(l4->sub_CD550(), &unk_5AC);
                stk_14 = l4->vf_120();
                if (stk_14->sub_238E0(0) != 0)
                    loc18 = (unk_5DC + 700.0f) * (unk_5DC + 700.0f);
                else
                    loc18 = unk_5E0;
                if (unk_5A8[var_8].unk_10 < loc18) {
                    l4->vf_120()->set_unk_7C(600.0f);
                    sub_6B5F0("FireAndMovementFinished", (type_67620 *)(l4->vf_098()), 0, 0, 0, 0, 1, 0);
                    l4->vf_120()->get_unk_56C()->sub_3E990(l4, 0);
                } else if (unk_5BC == 0) {
                    sub_3AC40(static_cast<type_3DBC78 *>(l4), &unk_5A8[var_8], arg_4);
                } else {
                    sub_3A9C0(static_cast<type_3DBC78 *>(l4), &unk_5A8[var_8], arg_4);
                }
            }
        }
    }
    return type_3CE6D0::vf_00C(arg_0, arg_4);
}

// match: ?vf_010@type_3CE5E8@@UAEHPAUtype_3D410@@@Z @ 0x000398E0
RwInt32 type_3CE5E8::vf_010(type_3D410 *arg_0)
{
    RwInt32 var_4;
    type_3D3548 *v8;
    RwInt32 varC;

    if (unk_5D0 != 0)
        return -1;
    v8 = 0;
    for (v8 = arg_0->get_unk_00()->unk_00; v8 != 0; v8 = v8->vf_118())
        vf_018(v8);
    sub_3B680();
    var_4 = 0;
    if (unk_5C4 == 0) {
        if (unk_51C + unk_520 <= 1)
            var_4 = 1;
    } else if (unk_51C + unk_520 <= 0) {
        var_4 = 1;
    }
    if (unk_5B8 != 0 && unk_5C4 == 0) {
        if (sub_3B560(arg_0, unk_524))
            unk_5AC = sub_3B490(unk_524);
        else
            var_4 = 1;
    }
    if (var_4 != 0 && unk_5D8 <= 0.0f) {
        if (unk_5C4 != 0) {
            arg_0->get_unk_00()->sub_3EA20(vf_030(), 0);
            varC = arg_0->get_unk_00()->get_unk_2B0();
            sub_6B5F0("FireAndMovementCleared", 0, 0, 0, &varC, 1, 1, 0);
        }
        return -1;
    }
    return 15;
}

// match: ?sub_39AA0@@YAHHPAUtype_3D410@@@Z @ 0x00039AA0
// match: __ehhandler$?sub_39AA0@@YAHHPAUtype_3D410@@@Z-0x16 @ 0x002FF620
// match: __ehhandler$?sub_39AA0@@YAHHPAUtype_3D410@@@Z @ 0x002FF636
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_39AA0(RwInt32 arg_0, type_3D410 *arg_4)
{
    type_F8350 *local_B8;
    RwV3d *local_B4;
    RwReal varB0;
    RwV3d ebp_AC;
    RwInt32 locA0;
    type_3CE6D0 *frm_9C;
    type_3D3548 *local_98;
    RwBool local_94;
    AIData *local_90;
    type_D48D0 stk_8C[32];

    local_94 = sub_3B560(arg_4, stk_8C);
    if (!local_94)
        return -1;
    ebp_AC = sub_3B490(stk_8C);
    locA0 = 0;
    local_98 = arg_4->get_unk_00()->unk_00;
    frm_9C = 0;
    local_90 = 0;
    while (local_98)
    {
        local_90 = local_98->vf_120();
        // The handle return supplies the parse-time temporary at -0xE0,
        // before the remaining inline getter locals at -0xEC..-0xFC.
        frm_9C = sub_3D3E0(local_90->get_unk_574_h().unk_00);
        if ((!frm_9C || !frm_9C->vf_030()) &&
            local_90->unk_51C && ((local_90->unk_49C >> 4) & 1) &&
            (((local_98->unk_2C >> 5) & 1) || ((local_98->unk_2C >> 4) & 1)) &&
            local_98->vf_160() != 3 &&
            !(local_90->unk_49C & 0x2000) && local_90->get_unk_520() &&
            local_90->get_unk_7C() <= 0.0f &&
            (!local_98->vf_008() ||
             (!local_98->vf_008()->get_unk_61C() && !local_98->vf_008()->unk_624.sub_D4910())))
        {
            if (local_90->sub_238E0(0))
            {
                local_B4 = local_98->sub_CD550();
                varB0 = 4840000.0f;
            }
            else if (local_90->sub_23930())
            {
                local_B8 = local_90->unk_F5C;
                local_B4 = &local_B8->unk_10;
                varB0 = 4840000.0f;
            }
            else
            {
                local_B4 = local_98->sub_CD550();
                varB0 = 2250000.0f;
            }
            if (sub_140C90(local_B4, &ebp_AC) > varB0)
                locA0++;
        }
        local_98 = local_98->vf_118();
    }
    if (locA0 <= 1)
        return -1;
    return 15;
}

// match: ?vf_018@type_3CE5E8@@UAEHPAUtype_3D3548@@@Z @ 0x00039EB0
// Takes the member arg_0 on when it can join the advance and is far enough
// from the point.
RwInt32 type_3CE5E8::vf_018(type_3D3548 *arg_0)
{
    AIData *l4;
    RwReal var_8;
    type_3CE6D0 *fp_C;
    RwV3d *local_10;
    type_F8350 *stk_14;
    RwUInt32 loc18;

    l4 = arg_0->vf_120();
    if ((unk_5D8 <= 0.0f) == 0)
        return 0;
    if ((l4->unk_49C & 0x2000) != 0 || l4->get_unk_520() == 0)
        return 0;
    if (arg_0->vf_008() != 0
            && (arg_0->vf_008()->get_unk_61C() != 0 || arg_0->vf_008()->unk_624.sub_D4910() != 0))
        return 0;
    if (((arg_0->unk_2C >> 5) & 1) == 0 && ((arg_0->unk_2C >> 4) & 1) == 0)
        return 0;
    if (((arg_0->unk_28 >> 9) & 1) != 0)
        return 0;
    if (arg_0->vf_160() == 3)
        return 0;
    if (arg_0->vf_120()->unk_51C == 0 || ((l4->unk_49C >> 4) & 1) == 0)
        return 0;
    if (l4->get_unk_7C() > 0.0f)
        return 0;
    if (l4->sub_238E0(0) != 0) {
        local_10 = arg_0->sub_CD550();
        var_8 = (unk_5E4 + 700.0f) * (unk_5E4 + 700.0f);
    } else if (l4->sub_23930() != 0) {
        stk_14 = l4->unk_F5C;
        local_10 = &stk_14->unk_10;
        var_8 = (unk_5E4 + 700.0f) * (unk_5E4 + 700.0f);
    } else {
        local_10 = arg_0->sub_CD550();
        var_8 = unk_5E8;
    }
    if (sub_140C90(local_10, &unk_5AC) < var_8)
        return 0;
    loc18 = l4->unk_574;
    fp_C = sub_3D3E0(loc18);
    if (fp_C != 0 && fp_C->vf_030() != 0)
        return 0;
    return sub_3A450(arg_0);
}

// match: ?vf_01C@type_3CE5E8@@UAEHPAUtype_3D3548@@@Z @ 0x0003A120
RwInt32 type_3CE5E8::vf_01C(type_3D3548 *arg_0)
{
    unk_5D8 = 0.0f;
    return sub_3A450(arg_0);
}

// match: ?vf_020@type_3CE5E8@@UAEXH@Z @ 0x0003A150
void type_3CE5E8::vf_020(RwInt32 arg_0)
{
    if (arg_0 != 0)
        unk_5D0 = 1;
}

// match: sub_3A170 @ 0x0003A170
// Moves the advance to the point arg_0 (none: 0): members with a node give
// it up when the point moves more than sqrt(10).
void type_3CE5E8::sub_3A170(RwV3d *arg_0)
{
    RwV3d var_C;
    RwInt32 var_10;
    type_3D3548 *lv_14;

    unk_5D4 = 1;
    unk_5D8 = 0.0f;
    if (arg_0 != 0) {
        RwV3dSub(&var_C, arg_0, &unk_5AC);
        if (RwV3dDotProduct(&var_C, &var_C) > 10.0f) {
            for (var_10 = 0; var_10 < 0x20; var_10++) {
                lv_14 = unk_5A8[var_10].unk_00.sub_D4910();
                if (lv_14 != 0 && lv_14->vf_120() != 0) {
                    if (unk_5A8[var_10].unk_08 != 0 && lv_14->vf_120()->sub_238E0(0) == 0)
                        lv_14->vf_120()->sub_238B0();
                    lv_14->vf_120()->sub_17AB0(0);
                    lv_14->vf_120()->set_unk_DD8(1);
                    unk_5A8[var_10].unk_08 = 0;
                    unk_5A8[var_10].unk_04 = 0;
                    unk_5A8[var_10].unk_0C = 0;
                }
                lv_14 = unk_5A4[var_10].unk_00.sub_D4910();
                if (lv_14 != 0 && lv_14->vf_120() != 0) {
                    if (unk_5A4[var_10].unk_08 != 0 && lv_14->vf_120()->sub_238E0(0) == 0)
                        lv_14->vf_120()->sub_238B0();
                    lv_14->vf_120()->sub_17AB0(0);
                    lv_14->vf_120()->set_unk_DD8(1);
                    unk_5A4[var_10].unk_08 = 0;
                    unk_5A4[var_10].unk_04 = 0;
                    unk_5A4[var_10].unk_0C = 0;
                }
            }
        }
        unk_5AC = *arg_0;
        unk_5C4 = 1;
    } else {
        unk_5C4 = 0;
    }
}

// match: ?sub_3A450@type_3CE5E8@@QAEHPAUtype_3D3548@@@Z @ 0x0003A450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3CE5E8::sub_3A450(type_3D3548 *arg_0)
{
    // Keep the handle copies and receiver pointers as named locals;
    // their interleaved slots are visible in sub_3A450's frame.
    type_D48D0 *var38;
    RwInt32 r34;
    type_D48D0 *lv_30;
    RwInt32 fp_2C;
    AIData *q28;
    AIData *frm_24;
    AIData *var_20;
    RwUInt32 l1C;
    AIData *m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwUInt32 var_C;
    RwUInt32 bp_8;
    type_3CE6D0 *bp_4;

    m_18 = arg_0->vf_120();
    bp_8 = m_18->unk_574;
    bp_4 = sub_3D3E0(bp_8);
    if (bp_4)
    {
        if (bp_4 == this)
        {
            if ((arg_0->unk_28 >> 9) & 1)
            {
                bp_4->vf_014(arg_0);
                return 0;
            }
            return 1;
        }
        bp_4->vf_014(arg_0);
    }
    arg_0->vf_120()->sub_23CD0(1, 1);
    var_C = unk_18;
    l1C = var_C;
    var_20 = arg_0->vf_120();
    var_20->unk_574 = l1C;
    if (arg_0->vf_120()->sub_238E0(0))
    {
        arg_0->vf_120()->sub_17AB0(0x17);
        frm_24 = arg_0->vf_120();
        frm_24->unk_DD8 = 0;
    }
    else
    {
        q28 = arg_0->vf_120();
        q28->unk_DD8 = 1;
    }
    if (unk_51C <= unk_520)
    {
        lv_10 = arg_0->unk_384;
        fp_2C = lv_10;
        lv_30 = &unk_1C[arg_0->vf_120()->unk_518].unk_00;
        lv_30->unk_00 = fp_2C;
        unk_1C[arg_0->vf_120()->unk_518].unk_04 = 0;
        unk_1C[arg_0->vf_120()->unk_518].unk_08 = 0;
        unk_1C[arg_0->vf_120()->unk_518].unk_0C = 0;
        unk_1C[arg_0->vf_120()->unk_518].unk_10 = sub_140C90(arg_0->sub_CD550(), &unk_5AC);
        unk_51C++;
    }
    else
    {
        ebp_14 = arg_0->unk_384;
        r34 = ebp_14;
        var38 = &unk_29C[arg_0->vf_120()->unk_518].unk_00;
        var38->unk_00 = r34;
        unk_29C[arg_0->vf_120()->unk_518].unk_04 = 0;
        unk_29C[arg_0->vf_120()->unk_518].unk_08 = 0;
        unk_29C[arg_0->vf_120()->unk_518].unk_0C = 0;
        // The original also writes the distance into unk_1C in this branch.
        unk_1C[arg_0->vf_120()->unk_518].unk_10 = sub_140C90(arg_0->sub_CD550(), &unk_5AC);
        unk_520++;
    }
    return 1;
}

// match: ?vf_014@type_3CE5E8@@UAEXPAUtype_3D3548@@@Z @ 0x0003A7B0
void type_3CE5E8::vf_014(type_3D3548 *arg_0)
{
    type_3D3548 *var_4;

    var_4 = 0;
    if (unk_1C[arg_0->vf_120()->unk_518].unk_00.sub_D4910() != 0) {
        if (unk_1C[arg_0->vf_120()->unk_518].unk_08 != 0 && arg_0->vf_120()->sub_238E0(0) == 0)
            arg_0->vf_120()->sub_238B0();
        unk_51C--;
        unk_1C[arg_0->vf_120()->unk_518].unk_00.sub_D48D0(0);
    } else if (unk_29C[arg_0->vf_120()->unk_518].unk_00.sub_D4910() != 0) {
        if (unk_29C[arg_0->vf_120()->unk_518].unk_08 != 0 && arg_0->vf_120()->sub_238E0(0) == 0)
            arg_0->vf_120()->sub_238B0();
        unk_520--;
        unk_29C[arg_0->vf_120()->unk_518].unk_00.sub_D48D0(0);
    }
    if (arg_0->vf_120()->get_unk_578() == 6)
        arg_0->vf_120()->sub_17AB0(1);
    arg_0->vf_120()->set_unk_DD8(1);
    arg_0->vf_120()->sub_23CD0(0, 1);
    type_3CE6D0::vf_014(arg_0);
}

// match: sub_3A9C0 @ 0x0003A9C0
// Drives the member arg_0 (slot arg_4) of the team that holds: to a node
// near it, then through its action handlers.
void type_3CE5E8::sub_3A9C0(type_3DBC78 *arg_0, type_39250_14 *arg_4, type_3D410 *arg_8)
{
    AIData *var_4;
    RwInt32 v8;
    type_F8350 *varC;

    if (arg_0->unk_24 == 0xE || (arg_0->unk_28 & 1) != 0)
        return;
    var_4 = arg_0->vf_120();
    if (var_4->unk_51C == 0)
        return;
    if (((var_4->unk_49C >> 4) & 1) == 0 || (var_4->unk_49C & 0x2000) != 0) {
        var_4->get_unk_56C()->sub_3E990(arg_0, 0);
        return;
    }
    if (var_4->unk_58 == 0)
        var_4->sub_17AB0(0);
    if (((var_4->unk_49C >> 5) & 1) != 0)
        sub_34720(arg_0, arg_8);
    if (var_4->unk_530 != 0 && var_4->unk_58 == 3)
        return;
    if ((var_4->unk_1430 != -1) != 0) {
        var_4->sub_1A5A0(3);
        if (var_4->unk_5C == 2)
            var_4->sub_17AB0(0);
        sub_3AC40(arg_0, arg_4, arg_8);
        return;
    }
    var_4->sub_29380(0);
    v8 = 0;
    if (var_4->get_unk_DD4() != 0)
        arg_4->unk_08 = 0;
    v8 = sub_15370(arg_0, (RwInt32)arg_8, 0);
    if (v8 == 0 && arg_4->unk_08 == 0 && (var_4->unk_5C != 0x17 || var_4->sub_238E0(0) != 0)) {
        varC = var_4->sub_23B60();
        if (varC != 0 && ((varC->unk_00 >> 2) & 1) == 0) {
            arg_4->unk_08 = 1;
            sub_F7BA0(var_4, varC, true);
            var_4->sub_23670();
            var_4->sub_22EF0(0);
        } else {
            if (var_4->get_unk_DD0() != 1)
                var_4->sub_23CD0(1, 1);
            var_4->sub_22EF0(1);
        }
    }
    if (v8 == 0 && (var_4->unk_5C == 2 || var_4->unk_5C == 0x17))
        v8 = sub_12070(arg_0, (RwInt32)arg_8);
    if (v8 == 0 && sub_12030(2, arg_0, (RwInt32)arg_8, 0) == 0) {
        if (var_4->unk_5C == 4)
            sub_12070(arg_0, (RwInt32)arg_8);
        else
            sub_12030(4, arg_0, (RwInt32)arg_8, 0);
    }
}

// match: sub_3AC40 @ 0x0003AC40
// Likewise for the member arg_0 of the team that moves up to the point.
void type_3CE5E8::sub_3AC40(type_3DBC78 *arg_0, type_39250_14 *arg_4, type_3D410 *arg_8)
{
    bool local_5;
    AIData *var_4;
    RwInt32 stk_C;
    type_F8350 *var_10;

    if (arg_0->unk_24 == 0xE || (arg_0->unk_28 & 1) != 0)
        return;
    var_4 = arg_0->vf_120();
    if (var_4->unk_51C == 0)
        return;
    if (((var_4->unk_49C >> 4) & 1) == 0 || (var_4->unk_49C & 0x2000) != 0) {
        var_4->get_unk_56C()->sub_3E990(arg_0, 0);
        return;
    }
    if (var_4->unk_5C == 0x16 && var_4->unk_58 == 2)
        arg_4->unk_0C = 1;
    if (var_4->unk_58 == 0 || var_4->unk_58 == 2)
        var_4->sub_17AB0(0);
    if (((var_4->unk_49C >> 5) & 1) != 0)
        sub_34720(arg_0, arg_8);
    if (var_4->unk_530 != 0 && var_4->unk_58 == 3)
        return;
    local_5 = false;
    if (var_4->unk_70 != 0) {
        var_4->unk_58 = 2;
        var_4->unk_70 = 0;
    }
    if (var_4->get_unk_DD4() != 0)
        arg_4->unk_08 = 0;
    local_5 = sub_15370(arg_0, (RwInt32)arg_8, 0) ? true : false;
    if (!local_5 && arg_4->unk_08 == 0 && (var_4->unk_5C != 0x17 || var_4->sub_238E0(0) != 0)) {
        var_10 = var_4->sub_23B60();
        if (var_10 != 0 && ((var_10->unk_00 >> 2) & 1) == 0) {
            arg_4->unk_08 = 1;
            sub_F7BA0(var_4, var_10, true);
            var_4->sub_23670();
            var_4->sub_22EF0(0);
        } else {
            if (var_4->get_unk_DD0() != 1)
                var_4->sub_23CD0(1, 1);
            var_4->sub_22EF0(1);
        }
    }
    var_4->sub_29380(0);
    stk_C = 0;
    if (!local_5) {
        switch (var_4->unk_5C) {
        case 0x17:
            if (sub_12070(arg_0, (RwInt32)arg_8) == 0
                    && sub_12030(0x16, arg_0, (RwInt32)arg_8, &unk_5AC) == 0
                    && sub_12030(2, arg_0, (RwInt32)arg_8, 0) == 0)
                sub_12030(4, arg_0, (RwInt32)arg_8, 0);
            break;
        case 0x16:
            if (arg_4->unk_08 != 0) {
                stk_C = sub_12030(0x17, arg_0, (RwInt32)arg_8, &unk_5AC);
                arg_4->unk_08 = 0;
            }
            if (stk_C == 0 && sub_12070(arg_0, (RwInt32)arg_8) == 0
                    && sub_12030(2, arg_0, (RwInt32)arg_8, 0) == 0)
                sub_12030(4, arg_0, (RwInt32)arg_8, 0);
            break;
        case 2:
            if (arg_4->unk_08 != 0) {
                stk_C = sub_12030(0x17, arg_0, (RwInt32)arg_8, &unk_5AC);
                arg_4->unk_08 = 0;
            }
            if (stk_C == 0 && sub_12070(arg_0, (RwInt32)arg_8) == 0)
                sub_12030(4, arg_0, (RwInt32)arg_8, 0);
            break;
        default:
            if (arg_4->unk_08 != 0) {
                stk_C = sub_12030(0x17, arg_0, (RwInt32)arg_8, &unk_5AC);
                arg_4->unk_08 = 0;
            }
            if (stk_C == 0 && sub_12030(0x16, arg_0, (RwInt32)arg_8, &unk_5AC) == 0
                    && sub_12030(2, arg_0, (RwInt32)arg_8, 0) == 0) {
                if (var_4->unk_5C == 4)
                    sub_12070(arg_0, (RwInt32)arg_8);
                else
                    sub_12030(4, arg_0, (RwInt32)arg_8, 0);
            }
        }
    }
}

// match: ?vf_024@type_3CE5E8@@UAEHPAUtype_3D3548@@@Z @ 0x0003B060
RwInt32 type_3CE5E8::vf_024(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    var_4 = arg_0->vf_120()->unk_5C;
    if (var_4 == 0 || var_4 == 4 || var_4 == 2)
        return 1;
    return 0;
}

// match: sub_3B0A0 @ 0x0003B0A0
// Keeps in the 32 handles at arg_0 only the candidates near (within 3000,
// by their AI records) at least 65% of the others that are themselves that
// well connected; 1 when any is left. arg_4 is not read.
RwBool sub_3B0A0(type_D48D0 *arg_0, type_3D410 *arg_4)
{
    RwInt32 ebp_10A8;
    RwInt32 ebp_10A4;
    RwInt32 lv_10A0;
    RwInt32 bp_109C;
    AIData *lcl_1098;
    RwInt32 lcl_1094;
    type_3B0A0_84 v1090[32];
    type_154C0_80 *slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    lcl_1098 = 0;
    lcl_1094 = 0;
    for (bp_109C = 0; bp_109C < 0x20; bp_109C++) {
        v1090[bp_109C].unk_00 = 0;
        if (arg_0[bp_109C].sub_D4910() != 0 && arg_0[bp_109C].sub_D4910()->vf_120() != 0
                && ((arg_0[bp_109C].sub_D4910()->vf_120()->unk_49C >> 6) & 1) != 0) {
            lcl_1098 = arg_0[bp_109C].sub_D4910()->vf_120();
            lcl_1094++;
            for (lv_10A0 = 0; lv_10A0 < 0x20; lv_10A0++) {
                v1090[bp_109C].unk_04[lv_10A0] = 0;
                if (bp_109C != lv_10A0) {
                    slot_C = lcl_1098->sub_16ED0(arg_0[lv_10A0].sub_D4910(), 0);
                    if (slot_C != 0 && slot_C->unk_0C < 3000.0f) {
                        v1090[bp_109C].unk_04[lv_10A0] = 1;
                        v1090[bp_109C].unk_00++;
                    }
                }
            }
        }
    }
    bp_8 = 0;
    for (ebp_10A4 = 0; ebp_10A4 < 0x20; ebp_10A4++) {
        if (arg_0[ebp_10A4].sub_D4910() == 0 || arg_0[ebp_10A4].sub_D4910()->vf_120() == 0
                || v1090[ebp_10A4].unk_00 < (lcl_1094 - 1) * 0.65f) {
            arg_0[ebp_10A4].sub_D48D0(0);
        } else {
            bp_4 = 0;
            lcl_1098 = arg_0[ebp_10A4].sub_D4910()->vf_120();
            for (ebp_10A8 = 0; ebp_10A8 < 0x20; ebp_10A8++) {
                if (v1090[ebp_10A4].unk_04[ebp_10A8] != 0
                        && v1090[ebp_10A8].unk_00 >= (lcl_1094 - 1) * 0.65f)
                    bp_4++;
            }
            if (bp_4 < (lcl_1094 - 1) * 0.65f)
                arg_0[ebp_10A4].sub_D48D0(0);
            else
                bp_8++;
        }
    }
    return bp_8 > 0;
}

// match: sub_3B490 @ 0x0003B490
// The mean position of the members held in the 32 handles at arg_0.
RwV3d sub_3B490(type_D48D0 *arg_0)
{
    RwV3d var_C;
    type_3D3548 *local_10;
    RwInt32 stk_14;
    RwInt32 loc18;

    var_C.x = var_C.y = var_C.z = 0.0f;
    stk_14 = 0;
    local_10 = 0;
    for (loc18 = 0; loc18 < 0x20; loc18++) {
        local_10 = arg_0[loc18].sub_D4910();
        if (local_10 != 0) {
            stk_14++;
            RwV3dAdd(&var_C, local_10->sub_CD550(), &var_C);
        }
    }
    var_C.x = var_C.x / stk_14;
    var_C.y = var_C.y / stk_14;
    var_C.z = var_C.z / stk_14;
    return var_C;
}

// Whether an entity of kind (unk_2C & 7) arg_4's is on another nonzero side
// than arg_0. It has no address (sub_3B560's one use is expanded under /Ob1)
// and so no database name; named for the field it compares. Evidence for
// its shape: sub_3B560 computes the && chain into a temporary before
// testing it, and compares the sides with xor.
inline RwInt32 xor_side(RwInt32 arg_0, type_3D3548 *arg_4)
{
    return ((arg_4->unk_2C & 7) ^ arg_0) != 0 && (arg_4->unk_2C & 7) != 0 && arg_0 != 0;
}

// match: sub_3B560 @ 0x0003B560
// Copies into the 32 handles at arg_4 the context's candidates of another
// side that can join the advance, then keeps those close enough together
// (sub_3B0A0).
RwBool sub_3B560(type_3D410 *arg_0, type_D48D0 *arg_4)
{
    type_3D3548 *var_4;
    RwInt32 local_8;

    var_4 = 0;
    for (local_8 = 0; local_8 < 0x20; local_8++) {
        var_4 = arg_0->unk_11C[local_8].unk_00.sub_D4910();
        if (var_4 != 0 && xor_side(arg_0->get_unk_00()->get_unk_2B0(), var_4)
                && ((var_4->unk_28 >> 9) & 1) == 0 && ((var_4->vf_120()->unk_49C >> 6) & 1) != 0
                && (((var_4->unk_2C >> 5) & 1) != 0 || ((var_4->unk_2C >> 4) & 1) != 0))
            arg_4[local_8] = arg_0->unk_11C[local_8].unk_00;
        else
            arg_4[local_8].sub_D48D0(0);
    }
    return sub_3B0A0(arg_4, arg_0);
}

// match: sub_3B680 @ 0x0003B680
// Recounts the teams and decides whether it is time to swap them.
RwInt32 type_3CE5E8::sub_3B680()
{
    RwInt32 var_4;

    unk_51C = 0;
    unk_520 = 0;
    unk_5B8 = 0;
    unk_5BC = 0;
    unk_5C8 = deltaTime + unk_5C8;
    for (var_4 = 0; var_4 < 0x20; var_4++) {
        if (unk_1C[var_4].unk_00.sub_D4910() != 0)
            unk_51C++;
        if (unk_29C[var_4].unk_00.sub_D4910() != 0)
            unk_520++;
        if (unk_1C[var_4].unk_04 != 0 || unk_29C[var_4].unk_04 != 0)
            unk_5B8 = 1;
    }
    if (unk_5C8 >= unk_5CC)
        unk_5B8 = 1;
    if (unk_5CC - 30.0f <= unk_5C8)
        unk_5BC = 1;
    return 1;
}

// match: sub_3B7E0 @ 0x0003B7E0
// match: __ehhandler$?sub_3B7E0@type_3CE5E8@@QAEHXZ-0x16 @ 0x002FF640
// match: __ehhandler$?sub_3B7E0@type_3CE5E8@@QAEHXZ @ 0x002FF656
// Swaps roles: regroups every member held, the nearer half of the point
// (a quickselect on the distances unk_10) into the first team, the rest
// into the second, and draws the next swap time (unk_5EC to unk_5F0).
RwInt32 type_3CE5E8::sub_3B7E0()
{
    RwInt32 lv_10 = 0;
    RwInt32 var350;
    type_3D3548 *lv_34C;
    RwInt32 slot_348;
    RwInt32 stk_344;
    RwInt32 slot_340;
    RwInt32 v33C;
    RwReal l338;
    RwInt32 l334;
    type_3D3548 *l330;
    RwInt32 var_32C;
    RwInt32 local_328;
    RwInt32 var_324;
    RwReal v320;
    type_39250_14 lv_31C[32];
    RwInt32 v9C;
    RwInt32 l98;
    RwInt32 var94[32];
    RwInt32 var_14;

    for (var_32C = 0; var_32C < 0x20; var_32C++) {
        l330 = unk_1C[var_32C].unk_00.sub_D4910();
        if (l330 != 0) {
            lv_31C[lv_10] = unk_1C[var_32C];
            unk_1C[var_32C].unk_00.sub_D48D0(0);
            lv_10++;
        }
        l330 = unk_29C[var_32C].unk_00.sub_D4910();
        if (l330 != 0) {
            lv_31C[lv_10] = unk_29C[var_32C];
            unk_29C[var_32C].unk_00.sub_D48D0(0);
            lv_10++;
        }
        var94[var_32C] = var_32C;
    }
    v9C = lv_10 - 1;
    l98 = 0;
    var_14 = lv_10 / 2;
    var_324 = 0;
    while (var_324 == 0) {
        if (l98 != v9C) {
            v33C = v9C;
            l334 = l98;
            l338 = lv_31C[var94[l98]].unk_10;
            slot_340 = 0;
            while (slot_340 == 0) {
                while (lv_31C[var94[v33C]].unk_10 > l338)
                    v33C--;
                while (lv_31C[var94[l334]].unk_10 < l338)
                    l334++;
                if (l334 < v33C) {
                    local_328 = var94[l334];
                    var94[l334] = var94[v33C];
                    var94[v33C] = local_328;
                    v33C--;
                    l334++;
                } else {
                    slot_340 = 1;
                    stk_344 = v33C - l98 + 1;
                    if (var_14 < stk_344) {
                        v9C = v33C;
                    } else {
                        l98 = v33C + 1;
                        var_14 = var_14 - stk_344;
                    }
                }
            }
        } else {
            var_324 = 1;
        }
    }
    unk_51C = 0;
    unk_520 = 0;
    v320 = lv_31C[var94[l98]].unk_10;
    for (slot_348 = 0; slot_348 < lv_10; slot_348++) {
        lv_34C = lv_31C[slot_348].unk_00.sub_D4910();
        if (lv_31C[slot_348].unk_10 < v320) {
            unk_1C[lv_34C->vf_120()->unk_518] = lv_31C[slot_348];
            unk_51C++;
        } else {
            unk_29C[lv_34C->vf_120()->unk_518] = lv_31C[slot_348];
            unk_520++;
        }
    }
    unk_5A4 = unk_1C;
    unk_5A8 = unk_29C;
    unk_5B8 = 0;
    unk_5BC = 0;
    unk_5C8 = 0.0f;
    unk_5CC = unk_5EC + RpRandom() % (unk_5F0 - unk_5EC + 1);
    for (var350 = 0; var350 < 0x20; var350++) {
        unk_5A8[var350].unk_04 = 0;
        unk_5A8[var350].unk_0C = 0;
        unk_5A4[var350].unk_04 = 0;
        unk_5A4[var350].unk_0C = 0;
        if (unk_5A8[var350].unk_00.sub_D4910() != 0
                && unk_5A8[var350].unk_00.sub_D4910()->vf_120() != 0)
            unk_5A8[var350].unk_00.sub_D4910()->vf_120()->sub_17AB0(0);
        if (unk_5A4[var350].unk_00.sub_D4910() != 0
                && unk_5A4[var350].unk_00.sub_D4910()->vf_120() != 0) {
            if (unk_5A4[var350].unk_00.sub_D4910()->vf_120()->has_unk_1430())
                unk_5A4[var350].unk_00.sub_D4910()->vf_120()->clear_unk_1430();
            if (unk_5A4[var350].unk_00.sub_D4910()->vf_120()->unk_5C != 0x17)
                unk_5A4[var350].unk_00.sub_D4910()->vf_120()->sub_17AB0(0);
        }
    }
    return 1;
}

// match: sub_3C070 @ 0x0003C070
// Whether the moving team has (nearly) all reached cover: none of up to
// two members, or at most one of more, still flagged in unk_0C.
RwInt32 type_3CE5E8::sub_3C070()
{
    RwInt32 var_4;
    type_3D3548 *v8;
    RwInt32 stk_C;
    RwInt32 var_10;

    var_4 = 0;
    stk_C = 0;
    for (var_10 = 0; var_10 < 0x20; var_10++) {
        v8 = unk_5A8[var_10].unk_00.sub_D4910();
        if (v8 != 0) {
            var_4++;
            if (unk_5A8[var_10].unk_0C != 0)
                stk_C++;
        }
    }
    if (var_4 > 2)
        return stk_C <= 1;
    return stk_C == 0;
}

// match: sub_3C110 @ 0x0003C110
// Sends every member of both teams back to its group.
void type_3CE5E8::sub_3C110()
{
    type_3D3548 *var_4;
    RwInt32 local_8;

    for (local_8 = 0; local_8 < 0x20; local_8++) {
        var_4 = unk_5A8[local_8].unk_00.sub_D4910();
        if (var_4 != 0)
            var_4->vf_120()->get_unk_56C()->sub_3E990(var_4, 0);
        var_4 = unk_5A4[local_8].unk_00.sub_D4910();
        if (var_4 != 0)
            var_4->vf_120()->get_unk_56C()->sub_3E990(var_4, 0);
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_030@type_3CE5E8@@UAEHXZ (folded into 0xA17A0)
RwInt32 type_3CE5E8::vf_030()
{
    return 5;
}
