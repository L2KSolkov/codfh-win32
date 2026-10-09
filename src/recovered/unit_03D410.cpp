// type_3D410, the context a group (type_3DF30) embeds at +0x4 (from its
// constructor sub_3D410): the targets and candidates its members see, and
// the periodic updates it runs. It follows the AIManeuverManager's unit. Its
// original file name and end boundary are not yet recovered (M1), so it is
// named for its start address.

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/type_3D410.h"
#include "types/type_3D3548.h"
#include "sp/sp_target.h"   // sub_3DE00 in single player
#include "types/type_10F710.h"
#include "types/type_3DF30.h"

// The functions its tables name (defined below or in other units).
void sub_3D7D0(RwInt32 arg_0, type_3D410 *arg_4);
void sub_3DB40(RwInt32 arg_0, type_3D410 *arg_4);

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE7E4
extern const RwReal flt_3CE7E4 = 16.666666f;
// 0x003CE7E8
extern const RwReal flt_3CE7E8 = 5000.0f;
// 0x003CE7EC
extern const RwReal flt_3CE7EC = 250.0f;
// 0x003CE7F0
extern const RwReal flt_3CE7F0 = 900.0f;
// 0x00427660
type_427660 dword_427660[2] = {
    { 0, sub_3D7D0, 4, 0, 0 },
    { 1, sub_3DB40, 60, 0, 0 },
};
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE7E4@@3MB @ 0x003CE7E4
// match: ?flt_3CE7E8@@3MB @ 0x003CE7E8
// match: ?flt_3CE7EC@@3MB @ 0x003CE7EC
// match: ?flt_3CE7F0@@3MB @ 0x003CE7F0
// match: __ehhandler$??0type_3D410@@QAE@XZ>1>8 @ 0x0041B094
// match: __ehhandler$??0type_3D410@@QAE@XZ>1 @ 0x0041B09C
// match: ?dword_427660@@3PAUtype_427660@@A @ 0x00427660

// match: ??0type_3D410@@QAE@XZ @ 0x0003D410
// match: __ehhandler$??0type_3D410@@QAE@XZ-0x16 @ 0x002FF6D0
// match: __ehhandler$??0type_3D410@@QAE@XZ @ 0x002FF6E6
// sp-match: ??0type_3D410@@QAE@XZ @ 0x0002ECF0

type_3D410::type_3D410()
{
    RwInt32 var_10;

    for (var_10 = 0; var_10 < 2; var_10++)
        unk_14[var_10] = 0.0f;
    unk_00 = 0;
}

// match: sub_3D4C0 @ 0x0003D4C0
// sp-match: sub_3D4C0 @ 0x0002E8C0
void type_3D410::sub_3D4C0(type_3DF30 *arg_0)
{
    RwInt32 local_8;
    RwInt32 var_4;

    unk_00 = arg_0;
    for (var_4 = 0; var_4 < 2; var_4++) {
        if (dword_427660[var_4].unk_08 > 0)
            unk_14[var_4] = 1.0f;
    }
    unk_04 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_29C = 10000.0f;
    unk_2A0 = 0.0f;
    for (local_8 = 0; local_8 < 0x20; local_8++) {
        unk_1C[local_8].unk_04_0 = 0;
        unk_1C[local_8].unk_00.sub_D48D0(0);
        unk_11C[local_8].unk_04 = 0;
        unk_11C[local_8].unk_08 = 0;
        unk_11C[local_8].unk_09 = 0;
        unk_11C[local_8].unk_00.sub_D48D0(0);
    }
}

// match: sub_3D5F0 @ 0x0003D5F0
// sp-match: sub_3D5F0 @ 0x0002ED70
void type_3D410::sub_3D5F0(RwReal arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 2; var_4++) {
        if (unk_14[var_4] <= 0.0f && dword_427660[var_4].unk_08 > 0) {
            unk_14[var_4] = dword_427660[var_4].unk_08 + unk_14[var_4];
            sub_3D700(dword_427660[var_4].unk_00, this);
        } else {
            unk_14[var_4] -= arg_0;
        }
    }
}

// match: sub_3D6B0 @ 0x0003D6B0
// sp-match: sub_3D6B0 @ 0x0002EF00
void type_3D410::sub_3D6B0(RwReal arg_0)
{
    type_3D410_11C *local_8;
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x20; var_4++) {
        local_8 = sub_3D720(var_4);
        if (local_8 != 0 && local_8->unk_09 != 0)
            local_8->unk_08 = 0;
    }
}

// match: sub_3D700 @ 0x0003D700
// sp-match: sub_3D700 @ 0x0002E950
// Runs the periodic update arg_0 on the context arg_4.
void sub_3D700(RwInt32 arg_0, type_3D410 *arg_4)
{
    dword_427660[arg_0].unk_04(arg_0, arg_4);
}

// match: sub_3D720 @ 0x0003D720
// sp-match: sub_3D720 @ 0x0002EDE0
type_3D410_11C *type_3D410::sub_3D720(RwInt32 arg_0)
{
    type_3D3548 *var_4;

    var_4 = unk_438CA8[arg_0].sub_D4910();
    if (var_4 != 0)
        return sub_3D760(var_4, arg_0);
    return 0;
}

// match: sub_3D760 @ 0x0003D760
// sp-match: sub_3D760 @ 0x0002E970
// The candidate record arg_4, cleared unless it already holds arg_0.
type_3D410_11C *type_3D410::sub_3D760(type_3D3548 *arg_0, RwInt32 arg_4)
{
    if (arg_0 != unk_11C[arg_4].unk_00.sub_D4910()) {
        unk_11C[arg_4].unk_04 = 0;
        unk_11C[arg_4].unk_00.sub_D48D0(0);
    }
    return &unk_11C[arg_4];
}

// match: sub_3D7D0 @ 0x0003D7D0
// sp-match: sub_3D7D0 @ 0x0002E9B0
// Periodic update 0: rebuilds the context arg_4's target records from each
// member's AI records it can see (sub_18F00), its unk_1390 entity and, for a
// player, the player's target of another side; counts the seen targets
// (unk_04, the previous count in unk_10) and times how long none has been
// seen (unk_2A0; unk_29C back to 10000 past 900).
void sub_3D7D0(RwInt32 arg_0, type_3D410 *arg_4)
{
    RwInt32 l40;
    RwInt32 var_3C;
    type_3D3548 *v38;
    RwInt32 v34;
    AIData *v30;
    RwInt32 var_2C;
    AIData *loc28;
    type_3D3548 *slot_24;
    RwInt32 v20;
    type_3D3548 *slot_1C;
    RwInt32 local_18;
    AIData *local_14;
    type_3D3548 *local_10;
    RwInt32 fp_C;
    type_3DF30 *lv_8;
    RwInt32 var_4;

    lv_8 = arg_4->unk_00;
    var_4 = 0;
    arg_4->unk_0C = 0;
    for (fp_C = 0; fp_C < 0x20; fp_C++) {
        arg_4->unk_1C[fp_C].unk_00.sub_D48D0(0);
        arg_4->unk_1C[fp_C].unk_04_0 = 0;
    }
    for (local_10 = lv_8->unk_00; local_10 != 0; local_10 = local_10->vf_118()) {
        local_18 = 0;
        local_14 = local_10->vf_120();
        for (v20 = 0; v20 < 0x20; v20++) {
            slot_24 = local_14->unk_80[v20].unk_00.sub_D4910();
            if (slot_24 != 0 && local_14->sub_18F00(&local_14->unk_80[v20], !((local_10->unk_2C >> 4) & 1)) != 0) {
                loc28 = slot_24->vf_120();
                var_2C = loc28->unk_518;
                arg_4->unk_1C[var_2C].unk_00.sub_D48D0(slot_24);
                arg_4->unk_1C[var_2C].unk_04_0 = 1;
                local_18 = 1;
            }
        }
        if (local_18 != 0)
            arg_4->unk_0C++;
        slot_1C = local_14->unk_1390.sub_D4910();
        if (slot_1C != 0) {
            v30 = slot_1C->vf_120();
            v34 = v30->unk_518;
            arg_4->unk_1C[v34].unk_00.sub_D48D0(slot_1C);
        }
        if (local_10->vf_00C() != 0) {
            v38 = local_10->vf_00C()->unk_1A34.sub_D4910();
            if (v38 != 0 && v38->vf_120() != 0 && cmp_unk_2C(local_10, v38)) {
                var_3C = v38->vf_120()->unk_518;
                arg_4->unk_1C[var_3C].unk_00.sub_D48D0(v38);
                arg_4->unk_1C[var_3C].unk_04_0 = 1;
            }
        }
    }
    for (l40 = 0; l40 < 0x20; l40++) {
        if (arg_4->unk_1C[l40].unk_00.sub_D4910() != 0 && arg_4->unk_1C[l40].unk_04_0)
            var_4++;
    }
    arg_4->unk_10 = arg_4->unk_04;
    arg_4->unk_04 = var_4;
    arg_4->unk_29C += 4.0f;
    if (var_4 == 0) {
        arg_4->unk_2A0 += 4.0f;
        if (arg_4->unk_2A0 > flt_3CE7F0)
            arg_4->unk_29C = 10000.0f;
    }
}

// match: sub_3DB40 @ 0x0003DB40
// sp-match: sub_3DB40 @ 0x0002EBC0
// Periodic update 1: carries the targets over into the candidate records
// (a new one flagged in unk_08; one no longer seen dropped after 8 updates)
// and counts in unk_08 the candidates in a group other than this one's
// (unk_2B4).
void sub_3DB40(RwInt32 arg_0, type_3D410 *arg_4)
{
    type_3D410_11C *stk_18;
    type_3D410_1C *l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    type_3D3548 *var_4;

    v8 = 0;
    ebp_C = 0;
    var_4 = 0;
    for (var_10 = 0; var_10 < 0x20; var_10++) {
        l14 = &arg_4->unk_1C[var_10];
        stk_18 = &arg_4->unk_11C[var_10];
        ebp_C = l14->unk_00.sub_D4910();
        var_4 = stk_18->unk_00.sub_D4910();
        stk_18->unk_09 = 0;
        if (ebp_C != 0) {
            if (ebp_C == var_4) {
                stk_18->unk_04 = 0;
                stk_18->unk_08 = 0;
            } else {
                stk_18->unk_00 = l14->unk_00;
                stk_18->unk_04 = 0;
                stk_18->unk_08 = 1;
            }
        } else if (var_4 != 0) {
            stk_18->unk_04++;
            if (stk_18->unk_04 >= 8) {
                stk_18->unk_00.sub_D48D0(0);
                stk_18->unk_04 = 0;
            }
        } else {
            stk_18->unk_00.sub_D48D0(0);
            stk_18->unk_04 = 0;
        }
        if (var_4 != 0 && stk_18->unk_08 == 0 && var_4->vf_120()->get_unk_56C() != 0
                && arg_4->get_unk_00()->get_unk_2B4() != var_4->vf_120()->get_unk_56C()->get_unk_2B4())
            v8++;
    }
    arg_4->unk_08 = v8;
}

// match: sub_3DCD0 @ 0x0003DCD0
// sp-match: sub_3DCD0 @ 0x0002EE10
RwInt32 type_3D410::sub_3DCD0(type_3D3548 *arg_0)
{
    RwInt32 var_1C;
    type_3D3548 *var18;
    RwInt32 stk_14;
    type_3D3548 *l10;
    type_3D3548 *local_C;
    RwInt32 lv_8;
    AIData *var_4;

    var_4 = arg_0->vf_120();
    local_C = var_4->unk_1374.sub_D4910();
    lv_8 = -1;
    l10 = 0;
    for (stk_14 = 0; stk_14 < 0x20; stk_14++) {
        var18 = 0;
        if (sub_3D720(stk_14) != 0)
            var18 = sub_3D720(stk_14)->unk_00.sub_D4910();
        if (sub_3DE00(arg_0, var18) != 0) {
            var_1C = var_4->sub_3FA10(var18);
            if (var_1C >= lv_8) {
                l10 = var18;
                lv_8 = var_1C;
            }
        }
    }
    if (l10 != 0) {
        var_4->sub_18BB0(l10);
    } else if (local_C != 0 && (local_C->unk_28 & 0x201) == 0
            && (local_C->vf_120() == 0 || ((local_C->vf_120()->unk_49C >> 6) & 1) != 0)) {
        // Keeps the tracked target (the branch compiles to nothing, as a
        // debug-only statement would).
    } else {
        var_4->sub_18BB0(0);
    }
    return 0;
}

#ifndef CODFH_SP // single player's is a static inline (sp/sp_target.h; SP 0x28F30)
// match: sub_3DE00 @ 0x0003DE00
// sp-match: sub_3DE00 @ 0x00028F30
RwInt32 sub_3DE00(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    if (byte_4C1940 != 0 && arg_4 != 0 && ((arg_4->unk_2C >> 4) & 1) != 0)
        return 0;
    if (arg_0 != 0 && arg_4 != 0 && xor_unk_2C(arg_0, arg_4) && ((arg_4->unk_28 >> 9) & 1) == 0
            && (arg_4->unk_28 & 1) == 0
            && ((arg_4->unk_2C & 0x3FFFFF0) & (arg_0->unk_34 & 0x3FFFFF0)) != 0 // not an address: kind bits
            && arg_4->vf_120() != 0 && ((arg_4->vf_120()->unk_49C >> 6) & 1) != 0
            && (((arg_4->unk_2C >> 4) & 1) == 0 || arg_4->vf_200() == 0 || arg_4->vf_1E4() != 0))
        return 1;
    return 0;
}
#endif

// Functions /OPT:ICF folded into the shared empty body (pDtor, 0x1E41C0) and
// into its caller (0x39440); defined for the authentic link (PLAN M7).

void type_3D410::sub_1E41C0()
{
}
