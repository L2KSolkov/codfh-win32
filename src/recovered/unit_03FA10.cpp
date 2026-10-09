// The target scores: AIData::sub_3FA10 scores a target for its owner by
// the owner's kind, through sub_404A0, sub_3FAC0, sub_401B0 or sub_403F0.
// It follows the kind-4 object's unit and precedes the Vision Scheduler's
// (sub_40720). Its original file name is not in the image, so it is named
// for its start address.

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/type_154C0_80.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DBC78.h"
#include "types/type_3DF30.h"
#include "types/type_3DC9B0.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE888
extern const RwReal flt_3CE888 = 16.666666f;
// 0x003CE88C
extern const RwReal flt_3CE88C = 1000.0f;
// 0x00427678
RwReal flt_427678 = 240.0f;
// End of its data definitions.


// shape: single player passes the scores' arguments in registers
// (SP 0x30A33 eax/edi), the internal-linkage register convention.
#ifdef CODFH_SP
static RwInt32 sub_3FAC0(type_3D3548 *arg_0, type_3D3548 *arg_4);
static RwInt32 sub_401B0(type_3DBC78 *arg_0, type_3D3548 *arg_4);
static RwInt32 sub_403F0(type_3D3548 *arg_0, type_3D3548 *arg_4);
#else
RwInt32 sub_3FAC0(type_3D3548 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_401B0(type_3DBC78 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_403F0(type_3D3548 *arg_0, type_3D3548 *arg_4);
#endif

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE888@@3MB @ 0x003CE888
// match: ?flt_3CE88C@@3MB @ 0x003CE88C
// match: __real@45fa0000 @ 0x003CE890
// match: __real@457a0000 @ 0x003CE894
// match: __real@451c4000 @ 0x003CE898
// match: ?flt_427678@@3MA @ 0x00427678

// match: sub_3FA10 @ 0x0003FA10
// sp-match: sub_3FA10 @ 0x000309F0

RwInt32 AIData::sub_3FA10(type_3D3548 *arg_0)
{
    type_3D3548 *var_4;

    var_4 = unk_568;
    if (((var_4->unk_2C >> 5) & 1) != 0) {
        if (var_4->vf_008()->get_unk_61C() != 0)
            return sub_404A0(arg_0);
        return sub_3FAC0(var_4, arg_0);
    }
    if (((var_4->unk_2C >> 0x12) & 1) != 0)
        return sub_401B0(static_cast<type_3DBC78 *>(var_4), arg_0);
    if (((var_4->unk_2C >> 7) & 1) != 0)
        return sub_403F0(var_4, arg_0);
    return -2;
}

// match: sub_3FAC0 @ 0x0003FAC0
// sp-match: sub_3FAC0 @ 0x00030070
// The score for the target arg_4 of an entity with flag 0x20: 0 unless it
// is among the nearest the entity's squad targets, then by what it is and
// how near.
RwInt32 sub_3FAC0(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    type_3DAFC8 *v48;
    RwInt32 slot_44;
    type_3D3548 *l40;
    type_3D3548 *var_3C;
    type_154C0_80 *v38;
    RwInt32 v34;
    AIData *v30;
    RwReal var_2C;
    RwReal loc28;
    RwInt32 slot_24;
    RwReal v20;
    type_154C0_80 *slot_1C;
    RwInt32 local_18;
    RwInt32 local_14;
    RwInt32 local_10;
    RwInt32 fp_C;
    RwInt32 lv_8;
    RwReal var_4;

    lv_8 = 100000;
    v30 = arg_0->vf_120();
    if (((arg_4->unk_2C >> 4) & 1) != 0 && arg_4->vf_160() == 7)
        return -2;
    slot_1C = v30->sub_16ED0(arg_4, 0);
    v34 = arg_0->vf_160();
    if (v30->unk_1374.sub_D4910() != 0 && v30->get_unk_1378() < 60.0f) {
        v38 = v30->sub_16ED0(v30->unk_1374.sub_D4910(), 0);
        if (!(v38 != 0 && v38->unk_0C > 500.0f && slot_1C->unk_0C <= 500.0f)) {
            if (arg_4 == v30->unk_1374.sub_D4910())
                return 100000;
            return 0;
        }
    }
    local_18 = 0;
    var_4 = 0.0f;
    loc28 = 0.0f;
    v20 = 0.0f;
    for (var_3C = v30->get_unk_56C()->unk_00; var_3C != 0; var_3C = var_3C->vf_118()) {
        if (var_3C->vf_120()->get_unk_1374() == arg_4 && var_3C != arg_0) {
            local_18++;
            var_2C = var_3C->vf_120()->sub_16ED0(arg_4, 0)->unk_0C;
            if (var_2C >= var_4) {
                v20 = loc28;
                loc28 = var_4;
                var_4 = var_2C;
            } else if (var_2C >= loc28) {
                v20 = loc28;
                loc28 = var_2C;
            } else if (var_2C >= v20) {
                v20 = var_2C;
            }
        }
    }
    local_14 = 0;
    slot_24 = 0;
    local_10 = 0;
    if (v30->sub_238E0(0) != 0 && v30->get_unk_F60() != 0)
        local_14 = 1;
    if (local_14 != 0 && ((v30->unk_49C >> 9) & 1) == 0 && v30->sub_27370(arg_4) == 0) {
        slot_24 = 1;
        if (arg_4 == v30->unk_1390.sub_D4910())
            local_10 = 1;
    }
    fp_C = 1;
    if (arg_4->vf_120() != 0
            && (((arg_4->vf_120()->unk_49C >> 0xE) & 1) != 0
                || ((arg_4->vf_120()->unk_49C >> 3) & 1) == 0))
        fp_C = 0;
    if (((local_18 >= 3 && slot_1C->unk_0C > v20)
                || (fp_C == 0 && local_18 >= 2 && slot_1C->unk_0C > loc28))
            && (slot_1C->unk_0C > 700.0f || fp_C == 0)) {
        if (((arg_4->unk_2C >> 0x12) & 1) != 0 && v34 != 3)
            return -1;
        if (v30->unk_1374.sub_D4910() == arg_4)
            return 1500;
        if (local_10 == 0 && (arg_4->vf_00C() == 0 || (slot_1C->unk_04 & 1) == 0))
            return 0;
    }
    if (v30->unk_1374.sub_D4910() == arg_4
            && (((slot_1C->unk_04 >> 1) & 1) != 0 || slot_1C->unk_10 < flt_427678))
        lv_8 += 1500;
    if (v30->unk_1390.sub_D4910() == arg_4)
        lv_8 += 760;
    if (local_10 != 0)
        lv_8 += 5000;
    if ((slot_1C->unk_04 & 1) != 0) {
        if (v30->sub_238E0(0) != 0 && v30->get_unk_F60() != 0)
            lv_8 += 3000;
        else
            lv_8 += 1000;
    } else if (((slot_1C->unk_04 >> 1) & 1) != 0) {
        lv_8 += 750;
    }
    if (((arg_4->unk_2C >> 0x12) & 1) != 0) {
        l40 = sub_1745A0(0);
        if (v34 == 3)
            lv_8 += 20000;
        else if (l40 != 0 && l40->vf_200() == arg_4 && l40->vf_1E4() != 0)
            lv_8 -= 20000;
    }
    if (((arg_4->unk_2C >> 5) & 1) != 0 || ((arg_4->unk_2C >> 4) & 1) != 0) {
        slot_44 = arg_4->vf_160();
        v48 = arg_4->vf_008();
        if (v48 != 0 && v48->get_unk_61C() != 0)
            slot_44 = 6;
        if (slot_44 == 3) {
            if (((slot_1C->unk_04 >> 1) & 1) != 0)
                lv_8 += 3500;
            else
                lv_8 += 1250;
        } else if (slot_44 == 6) {
            lv_8 += 4000;
        } else if (slot_44 == 0 && slot_1C->unk_0C >= 0.0f && slot_1C->unk_0C <= 2500.0f) {
            lv_8 += 750;
        } else if (slot_44 == 2 && slot_1C->unk_0C >= 4000.0f && slot_1C->unk_0C <= 8000.0f) {
            lv_8 += 1250;
        } else if (slot_44 == 4 && slot_1C->unk_0C >= 4000.0f && slot_1C->unk_0C <= 8000.0f) {
            lv_8 += 3000;
        }
    }
    if (slot_1C->unk_0C < 900.0f
            && ((arg_4->unk_2C & 0x40080) == 0 // flags 0x40000 and 0x80: not an address
                || (v34 == 3 && ((arg_4->unk_2C >> 0x12) & 1) != 0))) {
        if (slot_1C->unk_0C <= 500.0f && ((slot_1C->unk_04 >> 1) & 1) != 0)
            lv_8 += (RwInt32)((500.0f - slot_1C->unk_0C + 1.0f) * flt_3CE88C);
        if (((arg_4->unk_2C >> 4) & 1) != 0)
            lv_8 += 33000;
        else if (v34 != 3)
            lv_8 += 25000;
    } else {
        lv_8 -= (RwInt32)slot_1C->unk_0C;
    }
    if (lv_8 < 0)
        lv_8 = 0;
    return lv_8;
}

// match: sub_401B0 @ 0x000401B0
// sp-match: sub_401B0 @ 0x00030600
// The score for the target arg_0 of an entity with flag 0x40000.
RwInt32 sub_401B0(type_3DBC78 *arg_0, type_3D3548 *arg_4)
{
    type_3D3548 *l14;
    RwInt32 var_10;
    type_3DBC78 *ebp_C;
    type_154C0_80 *v8;
    RwInt32 var_4;

    if (((arg_4->unk_2C >> 0x11) & 1) != 0)
        return -1;
    v8 = arg_0->vf_120()->sub_16ED0(arg_4, 0);
    var_4 = 100000;
    ebp_C = arg_0;
    if (ebp_C->vf_2F0(arg_4) == 0)
        return -2;
    if (arg_0->vf_120()->get_unk_1374() != 0 && arg_0->vf_120()->get_unk_1378() < 60.0f) {
        if (arg_4 == arg_0->vf_120()->get_unk_1374()) {
            var_4 += 5000;
        } else {
            var_10 = 0;
            for (l14 = arg_0->vf_120()->get_unk_56C()->unk_00; l14 != 0;
                    l14 = l14->vf_118()) {
                if (l14->vf_120()->get_unk_1374() == arg_4)
                    var_10++;
            }
            if (var_10 > 3)
                return 0;
        }
    }
    if ((v8->unk_04 & 1) != 0)
        var_4 += 3000;
    if (((arg_4->unk_2C >> 0x12) & 1) != 0
            || (((arg_4->unk_2C >> 4) & 1) != 0 && arg_4->vf_160() == 7))
        var_4 += 20000;
    if ((((arg_4->unk_2C >> 5) & 1) != 0 || ((arg_4->unk_2C >> 4) & 1) != 0)
            && arg_4->vf_160() == 3)
        var_4 += 7500;
    if (((arg_4->unk_2C >> 7) & 1) != 0)
        var_4 += 3000;
    if ((var_4 -= (RwInt32)v8->unk_0C) < 0)
        var_4 = 0;
    return var_4;
}

// match: sub_403F0 @ 0x000403F0
// sp-match: sub_403F0 @ 0x00030770
// The score for the target arg_0 of an entity with flag 0x80.
RwInt32 sub_403F0(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    type_154C0_80 *local_8;
    RwInt32 var_4;

    if (((arg_4->unk_2C >> 0x11) & 1) != 0)
        return -1;
    local_8 = arg_0->vf_120()->sub_16ED0(arg_4, 0);
    var_4 = 100000;
    if (arg_0->vf_120()->get_unk_1374() == arg_4)
        var_4 += 3000;
    if ((local_8->unk_04 & 1) != 0)
        var_4 += 1000;
    if ((var_4 -= (RwInt32)local_8->unk_0C) < 0)
        var_4 = 0;
    return var_4;
}

// match: sub_404A0 @ 0x000404A0
// sp-match: sub_404A0 @ 0x000307E0
// The score of the target arg_0 for a soldier on a mounted weapon: 0 unless
// the weapon's view holds it (while bit 9 of unk_49C is set); the current
// target, held under 60, or the recent enemy under 120, gain most; seen and
// in view it scores by nearness (less when unseen for over 300), in view
// alone less, otherwise 1; one near (under 800) out of view that is a player
// or sees this soldier gains most of all.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_404A0(type_3D3548 *arg_0)
{
    type_3D3548 *l4;
    type_3D3548 *var_8;
    RwInt32 fp_C;
    RwInt32 v10;
    RwBool local_14;
    RwInt32 var18;
    RwInt32 var_1C;
    type_3DAFC8 *l20;
    type_154C0_80 *fp_24;
    type_154C0_80 *fp_28;

    v10 = 0;
    l20 = unk_568->vf_008();
    l4 = l20->get_unk_618();
    if (!l4)
    {
        return 0;
    }
    fp_24 = sub_16ED0(arg_0, 0);
    var18 = ((type_3DC9B0 *)l4)->sub_16A990(arg_0->sub_CD550(), 0, 0);
    if (((unk_49C >> 9) & 1) && !var18)
    {
        return 0;
    }
    local_14 = sub_18E90(fp_24, 1);
    fp_C = fp_24->unk_10 > 300.0f ? 1 : 0;
    // The plain arm goes through the FPU (fld/fstp), which a float copy does
    // not give; a round trip through RwDouble does.
    var_1C = (RwInt32)(arg_0 == unk_1374.sub_D4910() ? fp_24->unk_0C - 100.0f
                                                     : (RwReal)(RwDouble)fp_24->unk_0C);
    var_8 = unk_1374.sub_D4910();
    if (unk_1378 < 60.0f)
    {
        if (arg_0 == var_8 && var18 && local_14)
        {
            v10 += 1000000;
        }
    }
    else if (arg_0 == unk_1390.sub_D4910() && unk_1394 < 120.0f)
    {
        if (var18 && local_14)
        {
            v10 += 900000;
        }
        else if (!var18)
        {
            v10 += 800000;
        }
    }
    if (var18 && local_14)
    {
        v10 += 50000 - var_1C;
        if (fp_C)
        {
            v10 -= 10000;
        }
    }
    else if (var18)
    {
        v10 += 10000 - var_1C;
#ifdef CODFH_SP
        // shape: SP 0x307E0 keeps the score in edi as well as its home slot.
        // Bind the clamped value by reference, then store only when it rises.
        // A direct assignment in the test spills the score for the whole function.
        {
            const RwInt32 &r = v10 < 2 ? 2 : v10;
            if (r > v10)
                v10 = r;
        }
#else
        // MP 0x404A0.
        if (v10 < 2)
        {
            v10 = 2;
        }
#endif
    }
    else
    {
        v10++;
    }
    if (var_1C < 800.0f && !var18 && sub_18E40(arg_0, 1))
    {
        fp_28 = arg_0->vf_120()->sub_16ED0(unk_568, 0);
        if ((fp_28 && (fp_28->unk_04 & 1)) || arg_0->vf_00C())
        {
            v10 += 20000000;
        }
    }
    return v10;
}
