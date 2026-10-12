// The Alfa objects' classes (types/alfaobject.h): the base type_3D2C88, the
// script host type_3D2C30 and the entity's script object type_3D2CD0. The
// file's original name is not recovered (M1), so it is named for its start
// address.

#include <stdlib.h>
#include <string.h>

#include "rw/ostypes.h"
#include "types/type_42AF0.h"
#include "types/alfaobject.h"
#include "types/animbank.h"
#include "rw/rtquat.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/AIData.h"
#include "types/scriptvm.h"
#include "types/alfamessman.h"
#include "types/type_3D2E7C.h"
#include "types/type_44350.h"
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D2C2C
extern const RwReal flt_3D2C2C = 16.666666f;
// 0x004493F8
RwInt32 *dword_4493F8;
// 0x004493FC
RwInt32 *dword_4493FC;
// 0x004498D0
RwInt32 unk_4498D0[1];
// 0x004498D4
#ifdef CODFH_PLAIN
// (plain builds: the message argument stack, dword_4493F8, grows up from here; the image
// lets it run over the library statics that follow, a plain link puts the stack pointer itself
// there, so it gets room of its own)
RwInt32 unk_4498D4[0x400];
#else
RwInt32 unk_4498D4[1];
#endif
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D2C2C@@3MB @ 0x003D2C2C
// match: ??_7type_3D2C30@@6B@ @ 0x003D2C30
// match: ??_7type_3D2C88@@6B@ @ 0x003D2C88
// match: ??_7type_3D2CD0@@6B@ @ 0x003D2CD0
// match: ??_C@_0FP@LMHDOILA@WARNING?3?5?5transition?5animation?5c@ @ 0x003D2D28
// match: ??_C@_0BI@NIDBJFND@CoverTransitionFinished?$AA@ @ 0x003D2D88
// match: ??_C@_0BE@DPOENAJE@PerformanceFinished?$AA@ @ 0x003D2DA0
// match: ??_7type_3D2DB8@@6B@ @ 0x003D2DB8
// match: ??_C@_0BB@FLKPGOFI@Message?5Recieved?$AA@ @ 0x003D2E0C
// match: ??_7type_3D2E20@@6B@ @ 0x003D2E20

// match: ?vf_038@type_3D2C88@@UAEXHHHH@Z @ 0x0006CA60
// sp-match: ?vf_038@type_3D2C88@@UAEXHHHH@Z @ 0x0005BA90

void type_3D2C88::vf_038(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    unk_10[unk_60].unk_00 = arg_0;
    unk_10[unk_60].unk_04 = arg_4;
    unk_10[unk_60].unk_08 = arg_8;
    unk_10[unk_60].unk_0C = arg_C;
    unk_60 = unk_60 + 1 >= 5 ? 0 : unk_60 + 1;
}

#ifdef CODFH_SP
// Single player expands type_3D2C88's constructor inline everywhere (SP 0x5BAE0, type_3D2C30's
// constructor, stores its own vtable 0x2E03F0 after the base's body; SP 0x5C970,
// type_3D2DB8's, has the body inline too) and has no out-of-line copy.
inline type_3D2C88::type_3D2C88()
{
    RwInt32 var_4;

    unk_08 = -1;
    unk_0C = 0;
    unk_60 = 0;
    for (var_4 = 0; var_4 < 5; var_4++) {
        unk_10[var_4].unk_00 = 0;
        unk_10[var_4].unk_08 = 0;
        unk_10[var_4].unk_04 = 0;
        unk_10[var_4].unk_0C = 0;
    }
}
#endif

// match: ??0type_3D2C30@@QAE@XZ @ 0x0006CAF0
// sp-match: ??0type_3D2C30@@QAE@XZ @ 0x0005BAE0
type_3D2C30::type_3D2C30()
{
    // A local the image reserves and never uses.
    RwInt32 unused_0;
}

// match: ?vf_03C@type_3D2C88@@UAEXHH@Z @ 0x0006CB20
// sp-match: ?vf_03C@type_3D2C88@@UAEXHH@Z @ 0x0005BA50
void type_3D2C88::vf_03C(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_08 = arg_0;
    unk_0C = arg_4;
}

// match: ?vf_044@type_3D2C88@@UAEHXZ @ 0x0006CB40
// sp-match: ?vf_044@type_3D2C88@@UAEHXZ @ 0x0005BA80
RwInt32 type_3D2C88::vf_044()
{
    return unk_0C;
}

#ifndef CODFH_SP
// match: ??0type_3D2C88@@QAE@XZ @ 0x0006CB60
type_3D2C88::type_3D2C88()
{
    RwInt32 var_4;

    unk_08 = -1;
    unk_0C = 0;
    unk_60 = 0;
    for (var_4 = 0; var_4 < 5; var_4++) {
        unk_10[var_4].unk_00 = 0;
        unk_10[var_4].unk_08 = 0;
        unk_10[var_4].unk_04 = 0;
        unk_10[var_4].unk_0C = 0;
    }
}
#endif

// match: ?vf_004@type_3D2C30@@UAEPAHXZ @ 0x0006CC00
// sp-match: ?vf_004@type_3D2C30@@UAEPAHXZ @ 0x0005BB50
RwInt32 *type_3D2C30::vf_004()
{
    return unk_6C;
}

// match: ?vf_01C@type_3D2C30@@UAEXPAH@Z @ 0x0006CC20
// sp-match: ?vf_01C@type_3D2C30@@UAEXPAH@Z @ 0x0005BB80
void type_3D2C30::vf_01C(RwInt32 *arg_0)
{
    unk_6C = arg_0;
}

// match: ?vf_020@type_3D2C30@@UAEXPAH@Z @ 0x0006CC40
// sp-match: ?vf_020@type_3D2C30@@UAEXPAH@Z @ 0x0005BB90
void type_3D2C30::vf_020(RwInt32 *arg_0)
{
    unk_70 = arg_0;
}

// match: ??_Gtype_3D2C30@@UAEPAXI@Z @ 0x0006CC60
// match: ??1type_3D2C30@@UAE@XZ @ 0x0006CC90
// sp-match: ??_Gtype_3D2C30@@UAEPAXI@Z @ 0x0005D890
// sp-match: ??1type_3D2C30@@UAE@XZ @ 0x0005BBA0
type_3D2C30::~type_3D2C30()
{
}

// match: ?vf_04C@type_3D2C30@@UAEXH@Z @ 0x0006CCB0
// sp-match: ?vf_04C@type_3D2C30@@UAEXH@Z @ 0x0005BBB0
void type_3D2C30::vf_04C(RwInt32 arg_0)
{
    unk_64 = arg_0;
    unk_68 = 0;
    unk_6C = 0;
    unk_74 = 0;
}

// Its placement new (every pooled class's shares this code through
// /OPT:ICF; config/aliases.txt).
// match: ??2type_3D2CD0@@SAPAXIPAX@Z @ 0x0006CCF0
// sp-match: ??2type_3D2CD0@@SAPAXIPAX@Z @ 0x00122FF0
void *type_3D2CD0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// match: ??0type_3D2CD0@@QAE@XZ @ 0x0006CD00
// sp-match: ??0type_3D2CD0@@QAE@XZ @ 0x0005BBD0
type_3D2CD0::type_3D2CD0()
{
}

// match: ?vf_00C@type_3D2CD0@@UAEHXZ @ 0x0006CD40
// sp-match: ?vf_00C@type_3D2CD0@@UAEHXZ @ 0x0005BBF0

// match: ??_Gtype_3D2CD0@@UAEPAXI@Z @ 0x0006CD60
// match: ??1type_3D2CD0@@UAE@XZ @ 0x0006CD80
// sp-match: ??_Gtype_3D2CD0@@UAEPAXI@Z @ 0x0005D8B0
// sp-match: ??1type_3D2CD0@@UAE@XZ @ 0x0005BC10
type_3D2CD0::~type_3D2CD0()
{
}

// match: ?sub_6CDA0@type_3D2CD0@@QAEXPAUtype_3D3548@@H@Z @ 0x0006CDA0
// sp-match: ?sub_6CDA0@type_3D2CD0@@QAEXPAUtype_3D3548@@H@Z @ 0x0005BC20
void type_3D2CD0::sub_6CDA0(type_3D3548 *arg_0, RwInt32 arg_4)
{
    unk_78.sub_D48D0(arg_0);
    unk_7C = arg_4;
    unk_128 = 1;
    unk_118 = 0;
    unk_11C = 0;
    unk_129 = 0;
    unk_124 = 0.0f;
    unk_148 = -1;
    unk_12B = 0;
    zero_v3d(&unk_12C);
    zero_v3d(&unk_138);
    unk_144 = 0;
    unk_14C = 0;
    unk_12A = 0;
}

// match: ?vf_054@type_3D2CD0@@UAEXHH@Z @ 0x0006CE90
// sp-match: ?vf_054@type_3D2CD0@@UAEXHH@Z @ 0x0005D8C0
void type_3D2CD0::vf_054(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_04 = 0;
    type_3D2C30::vf_04C(arg_0);
    unk_6C = unk_80;
    unk_114 = arg_4;
    unk_148 = -1;
    sub_6E390();
    sub_6E3B0();
}

// match: ?vf_050@type_3D2CD0@@UAEXXZ @ 0x0006CEF0
// sp-match: ?vf_050@type_3D2CD0@@UAEXXZ @ 0x0005BCB0
void type_3D2CD0::vf_050()
{
    unk_114 = -1;
    type_3D2C30::vf_050();
}

// match: ?vf_024@type_3D2CD0@@UAEPAUtype_3D2E7C@@XZ @ 0x0006CF10
// sp-match: ?vf_024@type_3D2CD0@@UAEPAUtype_3D2E7C@@XZ @ 0x0005BCC0
type_3D2E7C *type_3D2CD0::vf_024()
{
    type_3D3548 *var_4;

    var_4 = unk_78.sub_D4910();
    return var_4 != 0 ? var_4->vf_098() : 0;
}

// match: ?sub_6CF50@type_3D2CD0@@QAEHHPAUtype_6CF50_04@@PAH@Z @ 0x0006CF50
// sp-match: ?sub_6CF50@type_3D2CD0@@QAEHHPAUtype_6CF50_04@@PAH@Z @ 0x0005BCE0
RwInt32 type_3D2CD0::sub_6CF50(RwInt32 arg_0, type_6CF50_04 *arg_4, RwInt32 *arg_8)
{
    type_4B9304 *var_10;
    RwInt32 ebp_C;
    RwInt8 lv_6;
    RwInt8 local_5;
    RwInt32 var_4;

    var_4 = 0;
    if (arg_8 != 0)
        *arg_8 = 0;
    ebp_C = unk_78.sub_D4910()->sub_CDC30();
    lv_6 = (RwInt8)unk_78.sub_D4910()->vf_0AC();
    if (unk_78.sub_D4910()->vf_008() != 0)
        local_5 = (RwInt8)unk_78.sub_D4910()->vf_008()->unk_3E0.sub_15F0A0();
    else
        local_5 = -1;
    if (unk_74 != 0) {
        var_10 = dword_4B9304;
        if (ebp_C != 0 && (var_4 = var_10->sub_EE1A0(ebp_C, arg_0)) != 0) {
            if (arg_8 != 0)
                *arg_8 = 1;
        } else {
            var_4 = var_10->sub_EDFE0(unk_74->unk_04, arg_0);
            if (var_4 != 0) {
                if (arg_8 != 0)
                    *arg_8 = 2;
            } else if (arg_4 != 0) {
                var_4 = var_10->sub_EE360(lv_6, local_5, arg_4->unk_02);
                if (arg_8 != 0)
                    *arg_8 = 3;
            }
        }
    }
    return var_4;
}

// match: sub_6D0A0 @ 0x0006D0A0
// sp-match: sub_6D0A0 @ 0x0005BE10
// A transition's extent (game/functions.h): the loop of "GetTransitionDistance"
// (sub_5D050) as a function. The flag converts to bool implicitly (`cmp;
// setne` with no `xor` first, which `!= 0` adds).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool sub_6D0A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal *arg_C)
{
    RwV3d ebp_74;
    RwV3d var_68;
    RtQuat v5C;
    RtQuat lcl_4C;
#ifndef CODFH_SP
    RwInt32 local_3C;
    RwInt32 v38;
#endif
    RwInt32 v34;
#ifndef CODFH_SP
    RwV3d v30;
    RtQuat slot_24;
#endif
    RwInt32 stk_14;
    type_EDA50_item *l10;
    RwInt32 local_C;
    type_4B9304 *lv_8;
    RwReal var_4;

    var_4 = 0.0f;
    local_C = 0;
    lv_8 = dword_4B9304;
    l10 = (type_EDA50_item *)lv_8->sub_EE360((RwInt8)arg_4, (RwInt8)arg_0, (RwInt8)arg_8);
    if (l10 != 0) {
        stk_14 = 1;
#ifdef CODFH_SP // shape: initialized block locals (SP 0x5BE10 tests the count before the stores)
        RwV3d v30 = {0.0f, 0.0f, 0.0f};
        RtQuat slot_24 = {{0.0f, 0.0f, 0.0f}, 1.0f};
#else
        v30.x = 0.0f;
        v30.y = 0.0f;
        v30.z = 0.0f;
        slot_24.imag.x = 0.0f;
        slot_24.imag.y = 0.0f;
        slot_24.imag.z = 0.0f;
        slot_24.real = 1.0f;
#endif
        for (v34 = 0; v34 < l10->unk_00; v34++) {
#ifdef CODFH_SP // shape: block-scoped out-parameters (SP 0x5BE10 shares var_4's slot with v38)
            RwInt32 local_3C;
            RwInt32 v38;
#endif
            if (sub_77B70(l10->unk_04[v34], (void **)(&local_3C), (void **)(&v38)) != 0
                && ((type_783F0 *)v38)->sub_78550(0.0f, 3) != 0) {
                ebp_74 = ((type_783F0 *)v38)->sub_78550(0.0f, 3)->unk_08_v;
                lcl_4C = ((type_783F0 *)v38)->sub_78550(0.0f, 4)->unk_08_q;
                RtQuatTransformVectors(&var_68, &ebp_74, 1, &slot_24);
                RtQuatMultiplyMacro(&v5C, &slot_24, &lcl_4C);
                RwV3dAdd(&v30, &v30, &var_68);
                slot_24 = v5C;
            } else
                stk_14 = 0;
        }
        if (stk_14 != 0) {
            local_C = 1;
            var_4 = RwV3dLength((RwV3d *)&v30);
            if (var_4 > 0.0f)
                var_4 = var_4 + 33.0f;
        } else
            var_4 = 0.0f;
    }
    if (arg_C != 0)
        *arg_C = var_4;
    return local_C;
}

// match: ?sub_6D320@type_3D2CD0@@QAEXH@Z @ 0x0006D320
void type_3D2CD0::sub_6D320(RwInt32 arg_0)
{
    if (!unk_128 && unk_74 != 0 && arg_0 == unk_74->unk_04)
        unk_148 = -1;
    else {
        unk_14C = 0x80;
        unk_148 = arg_0;
    }
}

// match: ?sub_6D380@type_3D2CD0@@QAEXHPAURwV3d@@0HHHHH@Z @ 0x0006D380
// sp-match: ?sub_6D380@type_3D2CD0@@QAEXHPAURwV3d@@0HHHHH@Z @ 0x0005C0A0
void type_3D2CD0::sub_6D380(RwInt32 arg_0, RwV3d *arg_4, RwV3d *arg_8, RwInt32 arg_C,
                            RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C)
{
    if (unk_12A && arg_14 == 0)
        return;
    unk_12A = arg_14 != 0;
    if (!unk_128 && unk_74 != 0 && arg_0 == unk_74->unk_04 && arg_C == 0) {
        unk_148 = -1;
        return;
    }
    if (unk_78.sub_D4910()->vf_008() != 0)
        unk_78.sub_D4910()->vf_008()->sub_13F4F0();
    unk_14C = 0;
    if (arg_10)
        unk_14C |= 0x20;
    if (arg_C)
        unk_14C |= 4;
    if (arg_18) {
        unk_14C |= 0x40;
        unk_12C = *arg_4;
        unk_138 = *arg_8;
    } else if (arg_1C) {
        unk_14C |= 0x107;
        unk_12C = *arg_4;
        unk_138 = *arg_8;
    } else {
        if (arg_4 != 0) {
            unk_14C |= 0xD;
            unk_12C = *arg_4;
        }
        if (arg_8 != 0) {
            unk_14C |= 0xE;
            unk_138 = *arg_8;
        }
    }
    unk_148 = arg_0;
}

// sub_6A970 (the script VM's unit): the debugger's report of a delivery.
void sub_6A970(type_42E00 *arg_0, type_6B960 *arg_4, const RwChar *arg_8);
void sub_6BC40(type_6B960 *arg_0);
type_6B960 *sub_6BA60(type_67620 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt8 arg_C,
                      RwInt8 arg_10);
type_6B960 *sub_6B9A0(type_67620 *arg_0, RwInt32 arg_4, type_6B9A0_08 *arg_8, RwInt32 arg_C,
                      RwInt32 arg_10, RwInt8 arg_14, RwInt8 arg_18);
type_67620_74 *sub_72AC0(RwInt32 arg_0);
struct type_3D2E7C;
struct type_42E00_10;
struct type_67620;
void sub_6B5F0(const RwChar *arg_0, type_67620 *arg_4, type_42E00_10 *arg_8, type_3D2E7C *arg_C, RwInt32 *arg_10, RwInt32 arg_14, bool arg_18, bool arg_1C);

// match: ?sub_6D5A0@type_3D2CD0@@QAEXM@Z @ 0x0006D5A0
// sp-match: ?sub_6D5A0@type_3D2CD0@@QAEXM@Z @ 0x0005D900
// Advances the performance (the entity's vf_03C passes its time step
// arg_0, unused here): starts the requested performance's script (unk_148)
// unless a transition is running, then steps its transition (unk_118): a
// finished transition (flag 0x20) or an empty one ends it; otherwise its
// next animation plays, and one that cannot play ends it with a warning.
// Finally it applies the entity's performance values (vf_08C).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D2CD0::sub_6D5A0(RwReal arg_0)
{
    type_78AC0 *ebp_34;
    type_78AC0 *var_30;
    type_78AC0 *bp_2C;
    type_78AC0 *local_28;
    type_7C8D0 *local_24;
    type_7C8D0 *local_20;
    type_7C8D0 *var_1C;
    type_7C8D0 *var18;
    type_7C8D0 *stk_14;
    RwInt32 l10;
    type_6CF50_04 *local_C;
    RwInt32 lv_8;
    type_3D3548 *var_4;

    unk_12A = 0;
    if (unk_148 == -1 || (unk_14C & 0x10) != 0)
        return;
#ifndef CODFH_SP // SP 0x5D900 has no flag-0x80 test (test 0x10 only)
    if ((unk_14C & 0x80) != 0)
        return;
#endif
    unk_128 = 0;
    var_4 = unk_78.sub_D4910();
    local_C = (type_6CF50_04 *)var_4->vf_08C(1, 0);
    lv_8 = 0;
    if (unk_74 != 0)
        unk_118 = sub_6CF50(unk_148, local_C, &lv_8);
    l10 = 1;
    if ((unk_14C & 8) != 0) {
        if (unk_74 == 0) {
            if ((unk_14C & 2) != 0 || (unk_14C & 0x40) != 0)
                var_4->vf_0D8(&unk_138);
            if ((unk_14C & 1) != 0 || (unk_14C & 0x40) != 0)
                var_4->vf_0C0(&unk_12C);
            unk_14C = 0;
        } else {
            unk_14C |= 0x10;
            if ((unk_14C & 0x40) == 0 && (unk_14C & 0x100) == 0) {
                unk_68 = unk_74->unk_08;
                unk_6C = unk_80;
                unk_70 = unk_6C;
                l10 = 0;
            }
        }
    }
    if (l10 != 0) {
        unk_74 = sub_72AC0(unk_148);
        unk_120 = unk_148;
        unk_6C = unk_80;
        unk_70 = unk_6C;
        unk_68 = unk_74->unk_08;
        unk_148 = -1;
        sub_6E390();
        sub_6E3B0();
        unk_129 = true;
        unk_124 = 0.33333334f;
    }
    if ((unk_14C & 0x20) != 0) {
        unk_118 = 0;
        unk_12B = 0;
        local_28 = sub_78AC0(var_4->unk_280);
        if (local_28 != 0)
            local_28->set_unk_12_0(false);
        if (((unk_14C & 1) != 0 || (unk_14C & 2) != 0) && (unk_14C & 4) != 0 && var_4 != 0) {
            stk_14 = var_4->unk_284;
            if (stk_14 != 0)
                stk_14->sub_79D50(&unk_12C, &unk_138);
        }
        sub_6DD00(0, 0);
        sub_6DDD0();
    } else if (unk_118 != 0 && ((type_EDA50_item *)unk_118)->unk_00 == 0) {
        unk_129 = (((type_EDA50_item *)unk_118)->unk_03 & 1) == 0;
        unk_124 = (RwReal)(((type_EDA50_item *)unk_118)->unk_03 & 0x1C) / 30.0f;
        unk_118 = 0;
        unk_12B = 0;
        bp_2C = sub_78AC0(var_4->unk_280);
        if (bp_2C != 0)
            bp_2C->set_unk_12_0(false);
        if (((unk_14C & 1) != 0 || (unk_14C & 2) != 0) && (unk_14C & 4) != 0 && var_4 != 0) {
            var18 = var_4->unk_284;
            if (var18 != 0)
                var18->sub_79D50(&unk_12C, &unk_138);
        }
        sub_6DD00(0, 0);
        sub_6DDD0();
    } else if (unk_118 != 0) {
        unk_11C = 0;
        if ((((unk_14C & 1) != 0 && (unk_14C & 2) != 0) || (unk_14C & 0x40) != 0)
            && (unk_14C & 0x100) == 0) {
            unk_12B = 1;
            if (((type_EDA50_item *)unk_118)->unk_00 == 1 && var_4 != 0) {
                var_1C = var_4->unk_284;
                if (var_1C != 0)
                    var_1C->sub_79D50(&unk_12C, &unk_138);
            }
        } else
            unk_12B = 0;
        unk_129 = (((type_EDA50_item *)unk_118)->unk_03 & 1) == 0;
        unk_124 = (RwReal)(((type_EDA50_item *)unk_118)->unk_03 & 0x1C) / 30.0f;
#ifdef CODFH_SP // single player's sub_6DE40 has no speed (SP 0x5C340 ends ret 0x10)
        if (!sub_6DE40(1, &((type_EDA50_item *)unk_118)->unk_04[unk_11C],
                       ((type_EDA50_item *)unk_118)->unk_01 >> unk_11C, true)) {
#else
        if (!sub_6DE40(1, &((type_EDA50_item *)unk_118)->unk_04[unk_11C],
                       ((type_EDA50_item *)unk_118)->unk_01 >> unk_11C, true, 1.0f)) {
#endif
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0x5D900)
            sub_19A750("WARNING:  transition animation could not play.  ID: %x. Complain to the animation department!\n",
                       ((type_EDA50_item *)unk_118)->unk_04[unk_11C]);
#endif
            unk_118 = 0;
            unk_12B = 0;
            var_30 = sub_78AC0(var_4->unk_280);
            if (var_30 != 0)
                var_30->set_unk_12_0(false);
            if ((unk_14C & 1) != 0 && (unk_14C & 2) != 0 && (unk_14C & 0x100) != 0 && var_4 != 0) {
                local_20 = var_4->unk_284;
                if (local_20 != 0)
                    local_20->sub_79D50(&unk_12C, &unk_138);
            }
            sub_6DD00(0, 0);
            sub_6DDD0();
        }
    } else if (((unk_14C & 1) != 0 || (unk_14C & 2) != 0) && (unk_14C & 4) != 0) {
        if (var_4 != 0) {
            local_24 = var_4->unk_284;
            if (local_24 != 0)
                local_24->sub_79D50(&unk_12C, &unk_138);
        }
        unk_12B = 0;
        sub_6DDD0();
    } else {
        sub_6DD00(0, 0);
        unk_12B = 0;
        ebp_34 = sub_78AC0(var_4->unk_280);
        if (ebp_34 != 0)
            ebp_34->set_unk_12_0(false);
        sub_6DDD0();
    }
    if (local_C != 0) {
        var_4->vf_0B0((RwUInt8)local_C->unk_02, 2);
        var_4->vf_0B8(local_C->unk_03);
    }
}

// match: ?sub_6DD00@type_3D2CD0@@QAEX_NH@Z @ 0x0006DD00
// sp-match: ?sub_6DD00@type_3D2CD0@@QAEX_NH@Z @ 0x0005C260
void type_3D2CD0::sub_6DD00(bool arg_0, RwInt32 arg_4)
{
    type_F8350 *varC;
    AIData *local_8;
    type_3D3548 *var_4;

    if (unk_14C & 0x40) {
        var_4 = unk_78.sub_D4910();
        local_8 = var_4->vf_120();
        if (local_8 != 0) {
            varC = local_8->unk_F60;
            if (varC != 0) {
                if (!arg_0)
                    local_8->sub_26A30();
                var_4->vf_1A0(0);
                var_4->vf_18C(0);
            }
        }
        if (var_4->vf_098() != 0)
            sub_6B5F0("CoverTransitionFinished", (type_67620 *)var_4->vf_098(), 0, 0, 0, 0, 1, 0);
    }
}

// match: ?sub_6DDD0@type_3D2CD0@@QAEXXZ @ 0x0006DDD0
// sp-match: ?sub_6DDD0@type_3D2CD0@@QAEXXZ @ 0x0005C2F0
void type_3D2CD0::sub_6DDD0()
{
    sub_68310((type_67620 *)this);
}

// match: ?sub_6DDF0@type_3D2CD0@@QAEX_N0@Z @ 0x0006DDF0
// sp-match: ?sub_6DDF0@type_3D2CD0@@QAEX_N0@Z @ 0x0005C300
void type_3D2CD0::sub_6DDF0(bool arg_0, bool arg_4)
{
    if (vf_024() != 0)
        sub_6B5F0("PerformanceFinished", (type_67620 *)vf_024(), 0, 0, 0, 0, arg_0, arg_4);
    unk_128 = 1;
}

// match: ?sub_6DE40@type_3D2CD0@@QAE_NHPAHH_NM@Z @ 0x0006DE40
// sp-match: ?sub_6DE40@type_3D2CD0@@QAE_NHPAHH_NM@Z @ 0x0005C340
#ifdef CODFH_SP // single player's sub_6DE40 has no speed (SP 0x5C340 ends ret 0x10)
bool type_3D2CD0::sub_6DE40(RwInt32 arg_0, RwInt32 *arg_4, RwInt32 arg_8, bool arg_C)
#else
bool type_3D2CD0::sub_6DE40(RwInt32 arg_0, RwInt32 *arg_4, RwInt32 arg_8, bool arg_C, RwReal arg_10)
#endif
{
    type_78AC0 *l14;
    RwInt32 var_10;
    RwInt32 local_C;
    RwInt32 var_8;
    bool var_1;

    var_1 = false;
    var_8 = 1;
    for (local_C = 0; local_C < arg_0; local_C++) {
        var_10 = arg_8 & var_8;
        var_8 = var_8 << 1;
#ifdef CODFH_SP // SP 0x5C340 takes four arguments (ret 0x10) and passes 1.0f for the speed
        var_1 = unk_78.sub_D4910()->vf_208(arg_4[local_C], var_10, 0, unk_124, 1.0f, 1.0f, 0);
#else
        var_1 = unk_78.sub_D4910()->vf_208(arg_4[local_C], var_10, 0, unk_124, 1.0f, arg_10, 0);
#endif
        unk_129 = 0;
        unk_124 = 0.0f;
        if (!var_1)
            break;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    if (arg_C) {
        l14 = sub_78AC0(get_unk_78()->unk_280);
        if (l14 != 0)
#ifdef CODFH_SP // SP expands type_78AC0::sub_6DF40 here, over its 4-entry ring (SP 0x5C340: % 4)
            l14->unk_34[(l14->unk_20 + l14->unk_24 - 1) % type_7C8D0_ring_size].unk_08 &= 0xBFFFFFFF;
#else
            l14->sub_6DF40();
#endif
    }
    return var_1;
}

// match: ?sub_6DF40@type_78AC0@@QAE_NXZ @ 0x0006DF40
// sp-match: ?sub_6DF40@type_78AC0@@QAE_NXZ @ 0x0005BA20
bool type_78AC0::sub_6DF40()
{
    RwInt32 var_4;

    var_4 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
    unk_34[var_4].unk_08 &= 0xBFFFFFFF;     // not an address: clears bit 30
    return true;
}

// match: ?sub_6DF90@type_3D2CD0@@QAEXH_N@Z @ 0x0006DF90
// sp-match: ?sub_6DF90@type_3D2CD0@@QAEXH_N@Z @ 0x0005C420
// Its animation's end (reached through a callback, not by name): with
// arg_4 set the performance ends; otherwise a waiting requested performance
// starts (or reports "PerformanceFinished" when it is the running one), and
// a running transition (unk_118) plays its next animation, or at its end
// sets the entity's blend (unk_129, unk_124) and ends; the script then runs
// unless it was stopped.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D2CD0::sub_6DF90(RwInt32 arg_0, bool arg_4)
{
    type_7C8D0 *var_8;
    type_78AC0 *stk_14;
    type_7C8D0 *fp_C;
    type_7C8D0 *local_10;
    type_78AC0 *loc18;
    type_3D3548 *l4;

    if (arg_4) {
        sub_6DDF0(true, false);
        return;
    }
#ifdef CODFH_SP // SP 0x5C420 tests only flag 8 (test al, 8)
    if ((unk_14C & 8) != 0 && unk_148 != -1 && (unk_14C & 0x40) == 0) {
#else
    if (((unk_14C & 8) != 0 || (unk_14C & 0x80) != 0) && unk_148 != -1 && (unk_14C & 0x40) == 0) {
#endif
        if (unk_148 != unk_120)
            sub_6D380(unk_148, 0, 0, 0, 0, 0, 0, 0);
        else
            sub_6B5F0("PerformanceFinished", (type_67620 *)vf_024(), 0, 0, 0, 0, 1, 0);
        unk_128 = 1;
    }
    l4 = unk_78.sub_D4910();
    if (unk_118 != 0) {
        unk_129 = false;
        unk_124 = 0.0f;
        unk_11C++;
        if (unk_11C < ((type_EDA50_item *)unk_118)->unk_00) {
            if (unk_12B != 0 && unk_11C == ((type_EDA50_item *)unk_118)->unk_00 - 1 && l4 != 0) {
                var_8 = l4->unk_284;
                if (var_8 != 0)
                    var_8->sub_79D50(&unk_12C, &unk_138);
            }
#ifdef CODFH_SP // single player's sub_6DE40 has no speed (SP 0x5C340 ends ret 0x10)
            if (!sub_6DE40(1, &((type_EDA50_item *)unk_118)->unk_04[unk_11C],
                           ((type_EDA50_item *)unk_118)->unk_01 >> unk_11C, true)) {
#else
            if (!sub_6DE40(1, &((type_EDA50_item *)unk_118)->unk_04[unk_11C],
                           ((type_EDA50_item *)unk_118)->unk_01 >> unk_11C, true, 1.0f)) {
#endif
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0x5C420)
                sub_19A750("WARNING:  transition animation could not play.  ID: %x. Complain to the animation department!\n",
                           ((type_EDA50_item *)unk_118)->unk_04[unk_11C]);
#endif
                unk_118 = 0;
                stk_14 =sub_78AC0(l4->unk_280);
                if (stk_14 != 0)
                    stk_14->set_unk_12_0(false);
                sub_6DD00(false, 0);
                if ((unk_14C & 1) != 0 && (unk_14C & 2) != 0 && (unk_14C & 0x100) != 0 && l4 != 0) {
                    fp_C = l4->unk_284;
                    if (fp_C != 0)
                        fp_C->sub_79D50(&unk_12C, &unk_138);
                }
                if (unk_128 == 0)
                    sub_6DDD0();
            }
        } else {
            if ((unk_14C & 0x40) != 0)
                sub_6DD00(true, 1);
            unk_129 = (bool)(((type_EDA50_item *)unk_118)->unk_03 & 2);
            unk_124 = (RwReal)(((type_EDA50_item *)unk_118)->unk_03 & 0x1C) / 30.0f;
            if ((unk_14C & 1) != 0 && (unk_14C & 2) != 0 && (unk_14C & 0x100) != 0 && l4 != 0) {
                local_10 = l4->unk_284;
                if (local_10 != 0)
                    local_10->sub_79D50(&unk_12C, &unk_138);
            }
            unk_118 = 0;
            unk_12B = 0;
            loc18 = sub_78AC0(l4->unk_280);
            if (loc18 != 0)
                loc18->set_unk_12_0(false);
            if (unk_128 == 0)
                sub_6DDD0();
        }
    } else if (unk_128 == 0)
        sub_6DDD0();
}

// match: ?sub_6E390@type_3D2CD0@@QAEXXZ @ 0x0006E390
// sp-match: ?sub_6E390@type_3D2CD0@@QAEXXZ @ 0x0005C650
void type_3D2CD0::sub_6E390()
{
    memset(unk_B0, -1, sizeof(unk_B0));
}

// match: ?sub_6E3B0@type_3D2CD0@@QAEXXZ @ 0x0006E3B0
// sp-match: ?sub_6E3B0@type_3D2CD0@@QAEXXZ @ 0x0005C660
void type_3D2CD0::sub_6E3B0()
{
    RwInt32 var_4;

    memset(unk_B4, 0, sizeof(unk_B4));
    for (var_4 = 0; var_4 < 8; var_4++)
        unk_B4[var_4].unk_0B = -1;
}

// match: ?sub_6E400@type_3D2CD0@@QAE_NH@Z @ 0x0006E400
// sp-match: ?sub_6E400@type_3D2CD0@@QAE_NH@Z @ 0x0005C690
bool type_3D2CD0::sub_6E400(RwInt32 arg_0)
{
    return unk_B0[arg_0] != -1;
}

// match: ?sub_6E430@type_3D2CD0@@QAEXHC@Z @ 0x0006E430
// sp-match: ?sub_6E430@type_3D2CD0@@QAEXHC@Z @ 0x0005C6B0
void type_3D2CD0::sub_6E430(RwInt32 arg_0, RwInt8 arg_4)
{
    unk_B0[arg_0] = arg_4;
}

// match: ?sub_6E450@type_3D2CD0@@QAE_NH@Z @ 0x0006E450
// sp-match: ?sub_6E450@type_3D2CD0@@QAE_NH@Z @ 0x0005C6D0
bool type_3D2CD0::sub_6E450(RwInt32 arg_0)
{
    unk_B0[arg_0]--;
    return unk_B0[arg_0] != -1;
}

// match: ?sub_6E490@type_3D2CD0@@QAEHHHH@Z @ 0x0006E490
// sp-match: ?sub_6E490@type_3D2CD0@@QAEHHHH@Z @ 0x0005E580
RwInt32 type_3D2CD0::sub_6E490(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    if (arg_8 < -32768)
        arg_8 = -32768;
    if (arg_8 > 32767)
        arg_8 = 32767;
    switch (arg_4) {
    case 3:
        return sub_6E5B0(arg_0, arg_8);
    case 2:
        return sub_6E570(arg_0, arg_8);
    case 1:
        return sub_6E520(arg_0, arg_8);
    }
    return 0;
}

// match: ?sub_6E520@type_3D2CD0@@QAEHHH@Z @ 0x0006E520
// sp-match: ?sub_6E520@type_3D2CD0@@QAEHHH@Z @ 0x0005DCE0
// The handler whose range holds arg_4, else a random allowed one.
RwInt32 type_3D2CD0::sub_6E520(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    if (sub_6E6A0(arg_0, arg_4, &var_4))
        return var_4;
    sub_6E790(arg_0, arg_4, &var_4);
    return var_4;
}

// match: ?sub_6E570@type_3D2CD0@@QAEHHH@Z @ 0x0006E570
// sp-match: ?sub_6E570@type_3D2CD0@@QAEHHH@Z @ 0x0005DD20
// The handler whose range holds arg_4, or 0.
RwInt32 type_3D2CD0::sub_6E570(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    if (sub_6E6A0(arg_0, arg_4, &var_4))
        return var_4;
    return 0;
}

// match: ?sub_6E5B0@type_3D2CD0@@QAEHHH@Z @ 0x0006E5B0
// sp-match: ?sub_6E5B0@type_3D2CD0@@QAEHHH@Z @ 0x0005C700
// The first handler allowed to run (counting its run).
RwInt32 type_3D2CD0::sub_6E5B0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_1C;
    type_67620_74_h *var18;
    RwInt32 stk_14;
    RwInt32 l10;
    type_3D2CD0_B4 *local_C;
    RwInt32 lv_8;
    type_67620_74_e *var_4;

    var_4 = &unk_74->unk_10[arg_0];
    local_C = &unk_B4[arg_0];
    l10 = -1;
    lv_8 = -1;
    for (stk_14 = 0; stk_14 < var_4->unk_04; stk_14++) {
        var18 = &var_4->unk_00[stk_14];
        if (var18->unk_07 == 0 || local_C->unk_0B != stk_14) {
            if (var18->unk_06 == 0 || var18->unk_06 > local_C->unk_00[stk_14]) {
                var_1C = 1;
                if (var_1C > lv_8) {
                    lv_8 = var_1C;
                    l10 = stk_14;
                }
            }
        }
    }
    local_C->unk_00[l10]++;
    local_C->unk_0B = (RwInt8)l10;
    return var_4->unk_00[l10].unk_04;
}

// match: ?sub_6E6A0@type_3D2CD0@@QAE_NHHPAH@Z @ 0x0006E6A0
// sp-match: ?sub_6E6A0@type_3D2CD0@@QAE_NHHPAH@Z @ 0x0005C790
// The handler for event arg_0 whose range holds arg_4, when allowed (its
// code offset in *arg_8, counting its run); whether there is one.
bool type_3D2CD0::sub_6E6A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 *arg_8)
{
    type_67620_74_h *var_10;
    RwInt32 ebp_C;
    type_3D2CD0_B4 *v8;
    type_67620_74_e *var_4;

    var_4 = &unk_74->unk_10[arg_0];
    v8 = &unk_B4[arg_0];
    for (ebp_C = 0; ebp_C < var_4->unk_04; ebp_C++) {
        var_10 = &var_4->unk_00[ebp_C];
        if (arg_4 >= var_10->unk_00 && arg_4 <= var_10->unk_02) {
            if (var_10->unk_07 == 0 || v8->unk_0B != ebp_C) {
                if (var_10->unk_06 == 0 || var_10->unk_06 > v8->unk_00[ebp_C]) {
                    v8->unk_00[ebp_C]++;
                    v8->unk_0B = (RwInt8)ebp_C;
                    *arg_8 = var_10->unk_04;
                    return true;
                } else
                    return false;
            } else
                return false;
        }
    }
    return false;
}

// match: ?sub_6E790@type_3D2CD0@@QAE_NHHPAH@Z @ 0x0006E790
// sp-match: ?sub_6E790@type_3D2CD0@@QAE_NHHPAH@Z @ 0x0005C810
// A handler for event arg_0 picked among the allowed ones by their ranges'
// widths, arg_4 per cent into their total (its code offset in *arg_8,
// counting its run); whether there is one.
bool type_3D2CD0::sub_6E790(RwInt32 arg_0, RwInt32 arg_4, RwInt32 *arg_8)
{
    RwUInt8 bp_2C[12];
    RwInt32 var_1C;
    RwInt32 var18;
    type_3D2CD0_B4 *stk_14;
    RwInt32 l10;
    RwInt32 local_C;
    type_67620_74_e *lv_8;
    RwInt32 var_4;

    lv_8 = &unk_74->unk_10[arg_0];
    stk_14 = &unk_B4[arg_0];
    for (l10 = 0; l10 < lv_8->unk_04; l10++) {
        if ((stk_14->unk_00[l10] < lv_8->unk_00[l10].unk_06 || lv_8->unk_00[l10].unk_06 == 0)
            && (stk_14->unk_0B != l10 || lv_8->unk_00[l10].unk_07 == 0))
            bp_2C[l10] = 1;
        else
            bp_2C[l10] = 0;
    }
    var18 = 0;
    for (l10 = 0; l10 < lv_8->unk_04; l10++) {
        if (bp_2C[l10])
            var18 += lv_8->unk_00[l10].unk_02 - lv_8->unk_00[l10].unk_00 + 1;
    }
    local_C = (RwInt32)(var18 * (arg_4 * 0.01f));
    local_C = local_C < 1 ? 1 : local_C;
    local_C = local_C > var18 ? var18 : local_C;
    var_4 = 1;
    for (l10 = 0; l10 < lv_8->unk_04; l10++) {
        if (bp_2C[l10]) {
            var_1C = lv_8->unk_00[l10].unk_02 - lv_8->unk_00[l10].unk_00 + var_4;
            if (local_C >= var_4 && local_C <= var_1C) {
                stk_14->unk_00[l10]++;
                stk_14->unk_0B = (RwInt8)l10;
                *arg_8 = lv_8->unk_00[l10].unk_04;
                return true;
            }
            var_4 = var_1C + 1;
        }
    }
    return false;
}

// match: ??0type_3D2DB8@@QAE@XZ @ 0x0006E9A0
// sp-match: ??0type_3D2DB8@@QAE@XZ @ 0x0005C970
type_3D2DB8::type_3D2DB8()
{
    // A local the image reserves and never uses.
    RwInt32 unused_0;

    unk_74 = 0;
    unk_78 = 0;
    unk_70 = -1;
    unk_84 = 0;
    unk_88 = 0;
    unk_7C = 0;
    unk_80 = 0;
    unk_9C = 0;
    unk_92 = -1;
}

// match: ?vf_028@type_3D2DB8@@UAEHXZ @ 0x0006EA30
// sp-match: ?vf_028@type_3D2DB8@@UAEHXZ @ 0x0005BB60

// match: ?vf_000@type_3D2DB8@@UAEPAHXZ @ 0x0006EA50
// sp-match: ?vf_000@type_3D2DB8@@UAEPAHXZ @ 0x0005BB40

// match: ?vf_004@type_3D2DB8@@UAEPAHXZ @ 0x0006EA70
// sp-match: ?vf_004@type_3D2DB8@@UAEPAHXZ @ 0x0005CA00

// match: ?vf_008@type_3D2DB8@@UAEPAHXZ @ 0x0006EA80
// sp-match: ?vf_008@type_3D2DB8@@UAEPAHXZ @ 0x0005CA10

// (alfaobject.h's inlines this file emits, between their neighbours in the image)
// sp-match: ?vf_014@type_3D2C30@@UAEHXZ @ 0x0005BB70
// sp-match: ?vf_018@type_3D2DB8@@UAEXPAH@Z @ 0x0005CA20
// sp-match: ?sub_1E7540@type_3D2E7C@@QAEXI@Z @ 0x0005D210

// match: ?vf_01C@type_3D2DB8@@UAEXPAH@Z @ 0x0006EA90
// sp-match: ?vf_01C@type_3D2DB8@@UAEXPAH@Z @ 0x0005CA30

// match: ?vf_020@type_3D2DB8@@UAEXPAH@Z @ 0x0006EAB0
// sp-match: ?vf_020@type_3D2DB8@@UAEXPAH@Z @ 0x0005CA40

// match: ??_Gtype_3D2DB8@@UAEPAXI@Z @ 0x0006EAD0
// match: ??1type_3D2DB8@@UAE@XZ @ 0x0006EAF0
// sp-match: ??_Gtype_3D2DB8@@UAEPAXI@Z @ 0x0005DD50
// sp-match: ??1type_3D2DB8@@UAE@XZ @ 0x0005CA50
type_3D2DB8::~type_3D2DB8()
{
}

// match: ?vf_04C@type_3D2DB8@@UAEXHH@Z @ 0x0006EB10
// sp-match: ?vf_04C@type_3D2DB8@@UAEXHH@Z @ 0x0005CA60
void type_3D2DB8::vf_04C(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_04 = 0;
    unk_64 = arg_0;
    unk_70 = arg_4;
    unk_68 = 0;
    unk_6C = 0;
    unk_98 &= ~1;
    unk_98 &= ~2;
    unk_90 = -1;
}

// match: ?vf_050@type_3D2DB8@@UAEXXZ @ 0x0006EB90
// sp-match: ?vf_050@type_3D2DB8@@UAEXXZ @ 0x0005E5E0
void type_3D2DB8::vf_050()
{
    type_3D2DB8_6C *varC;
    type_3D2DB8 *local_8;
    type_3D2DB8 *var_4;

    unk_70 = -1;
    sub_73470(this);
    var_4 = (type_3D2DB8 *)sub_67620(unk_84);
    if (var_4 != 0) {
        var_4->sub_70B70();
        unk_84 = 0;
    }
    local_8 = (type_3D2DB8 *)sub_67620(unk_80.unk_00);
    if (local_8 != 0) {
        local_8->sub_70B70();
        unk_80 = 0;
    }
    if (unk_74 != 0) {
        sub_71D50(unk_74);
        unk_74 = 0;
    }
    for (varC = unk_6C; varC != 0; varC = varC->unk_00)
        sub_6F760(varC->unk_10);
}

// match: ?sub_6EC60@type_3D2DB8@@QAEXHPAUtype_3D2DB8_6C@@HHPAUtype_3D2E7C@@HHH@Z @ 0x0006EC60
// sp-match: ?sub_6EC60@type_3D2DB8@@QAEXHPAUtype_3D2DB8_6C@@HHPAUtype_3D2E7C@@HHH@Z @ 0x0005ED60
void type_3D2DB8::sub_6EC60(RwInt32 arg_0, type_3D2DB8_6C *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                            type_3D2E7C *arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C)
{
    unk_8C = arg_4;
    sub_6EEF0();
    unk_90 = -1;
    if (arg_C > 0) {
        unk_74 = sub_71CE0(arg_C);
        unk_78 = arg_C;
    }
    unk_94 = (RwInt16)arg_18;
    unk_96 = (RwUInt8)arg_8;
    sub_6FBB0(arg_10);
    if (arg_1C)
        sub_6EF10();
}

// match: ?sub_6ECF0@type_3D2DB8@@QAEPAU1@H@Z @ 0x0006ECF0
// sp-match: ?sub_6ECF0@type_3D2DB8@@QAEPAU1@H@Z @ 0x0005CAA0
type_3D2DB8 *type_3D2DB8::sub_6ECF0(RwInt32 arg_0)
{
    RwUInt32 local_8;
    type_3D2DB8 *var_4;

    var_4 = (type_3D2DB8 *)sub_67620(unk_84);
    while (var_4 != 0) {
        if (var_4->unk_96 == arg_0)
            return var_4;
        local_8 = var_4->unk_80.unk_00;
        var_4 = (type_3D2DB8 *)sub_67620(local_8);
    }
    return 0;
}

// match: ?sub_6ED50@type_3D2DB8@@QAEXPAU1@@Z @ 0x0006ED50
// sp-match: ?sub_6ED50@type_3D2DB8@@QAEXPAU1@@Z @ 0x0005CAF0
void type_3D2DB8::sub_6ED50(type_3D2DB8 *arg_0)
{
    arg_0->unk_80 = unk_84_h;
    unk_84_h = arg_0->get_unk_04_h();
    arg_0->unk_88 = get_unk_04_h();
}

// match: ?sub_6EDB0@type_3D2DB8@@QAEXPAU1@@Z @ 0x0006EDB0
// sp-match: ?sub_6EDB0@type_3D2DB8@@QAEXPAU1@@Z @ 0x0005CB20
void type_3D2DB8::sub_6EDB0(type_3D2DB8 *arg_0)
{
    RwUInt32 varC;
    type_3D2DB8 *local_8;
    type_3D2DB8 *var_4;

    var_4 = 0;
    local_8 = (type_3D2DB8 *)sub_67620(unk_84);
    while (local_8 != arg_0) {
        var_4 = local_8;
        varC = local_8->unk_80.unk_00;
        local_8 = (type_3D2DB8 *)sub_67620(varC);
    }
    if (var_4 != 0)
        var_4->unk_80 = local_8->unk_80.get_h();
    else
        unk_84_h = local_8->unk_80.get_h();
}

// match: ?sub_6EE50@type_3D2DB8@@QAEPAU1@HH@Z @ 0x0006EE50
// sp-match: ?sub_6EE50@type_3D2DB8@@QAEPAU1@HH@Z @ 0x0005EDD0
type_3D2DB8 *type_3D2DB8::sub_6EE50(RwInt32 arg_0, RwInt32 arg_4)
{
    type_72990 *local_8;
    type_3D2DB8 *var_4;

    local_8 = sub_72990(arg_0);
    var_4 = sub_6ECF0(arg_4);
    if (var_4 != 0) {
        sub_6EDB0(var_4);
        var_4->sub_70B70();
    }
    var_4 = sub_71A90();
    sub_6ED50(var_4);
    var_4->sub_6EC60(local_8->unk_0C, local_8->unk_08, arg_4, local_8->unk_0E * 4, vf_024(), local_8->unk_18,
                     arg_0, 1);
    return var_4;
}

// match: ?sub_6EEF0@type_3D2DB8@@QAEXXZ @ 0x0006EEF0
// sp-match: ?sub_6EEF0@type_3D2DB8@@QAEXXZ @ 0x0005CB80
void type_3D2DB8::sub_6EEF0()
{
    dword_4493F8 = unk_4498D4;
    dword_4493FC = dword_4493F8;
}

// match: ?sub_6EF10@type_3D2DB8@@QAEXXZ @ 0x0006EF10
// sp-match: ?sub_6EF10@type_3D2DB8@@QAEXXZ @ 0x0005EAC0
void type_3D2DB8::sub_6EF10()
{
    unk_90 = 0;
    sub_6F690(0);
    unk_6C = &unk_8C[unk_90];
    if (unk_6C->unk_12 != -1) {
        unk_68 = unk_6C->unk_04 + unk_6C->unk_12;
        sub_68310((type_67620 *)this);
        sub_6F490();
    }
}

// match: ?sub_6EF90@@YAHPBX0@Z @ 0x0006EF90
// sp-match: ?sub_6EF90@@YAHPBX0@Z @ 0x0005CB90
// bsearch's order of two message handlers by their id.
RwInt32 sub_6EF90(const void *arg_0, const void *arg_4)
{
    if (*(RwUInt16 *)arg_0 > *(RwUInt16 *)arg_4)
        return 1;
    if (*(RwUInt16 *)arg_0 == *(RwUInt16 *)arg_4)
        return 0;
    return -1;
}

#ifdef CODFH_SP
// Single player's sub_6EFD0 finds the handler through an inline with an 8-byte key record
// (SP 0x5EE50: 0xC-byte frame, the id stored as the argument is evaluated).
inline void *sub_6EFD0_find(type_3D2DB8_6C *list, RwUInt16 id)
{
    struct { RwUInt16 unk_00; RwUInt16 unk_02; RwInt32 unk_04; } key;
    key.unk_00 = id;
    return bsearch(&key, list->unk_0C, list->unk_1B, 8, sub_6EF90);
}
#endif

// match: ?sub_6EFD0@type_3D2DB8@@QAEXPAUtype_42E00@@PAUtype_6B960@@@Z @ 0x0006EFD0
// sp-match: ?sub_6EFD0@type_3D2DB8@@QAEXPAUtype_42E00@@PAUtype_6B960@@@Z @ 0x0005EE50
void type_3D2DB8::sub_6EFD0(type_42E00 *arg_0, type_6B960 *arg_4)
{
    void *stk_18;
    type_6B960 *l14;
    type_3D2DB8_6C *var_10;
    RwUInt16 ebp_C;
    type_3D2DB8 *v8;
    RwInt32 var_4;

    l14 = arg_4;
    ebp_C = (RwUInt16)arg_0->unk_00->unk_04;
    var_10 = unk_6C;
    var_4 = 0;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    while (var_10 != 0 && var_4 == 0) {
#ifdef CODFH_SP // shape: the search through an inline (SP 0x5EE50)
        stk_18 = sub_6EFD0_find(var_10, ebp_C);
#else
        RwUInt16 var_20 = ebp_C;
        stk_18 = bsearch(&var_20, var_10->unk_0C, var_10->unk_1B, 8, sub_6EF90);
#endif
        if (stk_18 != 0) {
            l14->unk_00_h = get_unk_04_h();
            l14->unk_08 = (type_6B9A0_08 *)stk_18;
            l14->unk_04 = (RwInt32)var_10;
            l14->unk_0C = -1;
            l14->unk_0E = -1;
            sub_6F110(arg_0, l14);
            sub_6A970(arg_0, arg_4, "Message Recieved");
            var_4 = 1;
        }
        var_10 = var_10->unk_00;
    }
    v8 = (type_3D2DB8 *)sub_67620(unk_84_h);
    while (v8 != 0) {
        v8->sub_6EFD0(arg_0, arg_4);
        v8 = (type_3D2DB8 *)sub_67620(v8->unk_80.unk_00_h);
    }
}

// match: ?sub_6F110@type_3D2DB8@@QAEXPAUtype_42E00@@PAUtype_6B960@@@Z @ 0x0006F110
// sp-match: ?sub_6F110@type_3D2DB8@@QAEXPAUtype_42E00@@PAUtype_6B960@@@Z @ 0x0005EB20
void type_3D2DB8::sub_6F110(type_42E00 *arg_0, type_6B960 *arg_4)
{
    RwInt32 local_24;
    RwUInt32 local_20;
    RwUInt32 var_1C;
    RwUInt32 var18;
    type_3D2E7C *stk_14;
    RwInt32 l10;
    type_3D2E7C *local_C;
    type_4CFE30 *lv_8;
    type_3D2E7C *var_4;

    local_24 = arg_0->unk_10;
    if (local_24 >= 0 && local_24 < 2000)
        lv_8 = dword_4CFE30[local_24];
    else
        lv_8 = 0;
    local_C = (type_3D2E7C *)sub_67620(arg_0->unk_08);
    var_4 = (type_3D2E7C *)sub_67620(arg_0->unk_0C);
    if (arg_4->unk_08->unk_02 != 0xFFFF) {
        sub_6EEF0();
        dword_4493FC[0] = arg_0->unk_10;
        dword_4493FC[1] = 0;
        dword_4493FC[2] = 0;
#ifdef CODFH_SP // shape: the handles copied through the inline handle getter (SP 0x5EB20)
        if (local_C != 0)
            *(type_439E78_00 *)&dword_4493FC[1] = local_C->get_unk_04_h();
        else if (lv_8 != 0) {
            stk_14 = ((type_712B0 *)lv_8)->sub_BDF50();
            if (stk_14 != 0)
                *(type_439E78_00 *)&dword_4493FC[1] = stk_14->get_unk_04_h();
        }
        if (var_4 != 0)
            *(type_439E78_00 *)&dword_4493FC[2] = var_4->get_unk_04_h();
#else
        if (local_C != 0) {
            var18 = local_C->unk_04;
            dword_4493FC[1] = var18;
        } else if (lv_8 != 0) {
            stk_14 = ((type_712B0 *)lv_8)->sub_BDF50();
            if (stk_14 != 0) {
                var_1C = stk_14->unk_04;
                dword_4493FC[1] = var_1C;
            }
        }
        if (var_4 != 0) {
            local_20 = var_4->unk_04;
            dword_4493FC[2] = local_20;
        }
#endif
        l10 = arg_0->unk_00->unk_10;
        memcpy(dword_4493FC + 3, arg_0->unk_14, l10 * 4);
        dword_4493F8 = dword_4493F8 + l10 + 3;
        unk_68 = ((type_3D2DB8_6C *)arg_4->unk_04)->unk_04 + arg_4->unk_08->unk_02;
        sub_68310((type_67620 *)this);
        sub_6F490();
    }
}

// match: ?sub_6F290@type_3D2DB8@@QAE_NHPAPAUtype_3D2DB8_6C_08@@PAPAH@Z @ 0x0006F290
// sp-match: ?sub_6F290@type_3D2DB8@@QAE_NHPAPAUtype_3D2DB8_6C_08@@PAPAH@Z @ 0x0005CBC0
bool type_3D2DB8::sub_6F290(RwInt32 arg_0, type_3D2DB8_6C_08 **arg_4, RwInt32 **arg_8)
{
    RwInt32 var_10;
    RwInt32 local_C;
    type_3D2DB8_6C *var_8;
    bool var_1;

    var_1 = false;
    *arg_4 = 0;
    *arg_8 = 0;
    var_8 = unk_6C;
    while (var_8 != 0 && !var_1) {
        for (local_C = 0; local_C < var_8->unk_1A; local_C++) {
            var_10 = var_8->unk_08[local_C].unk_00;
            if (var_10 == arg_0) {
                *arg_8 = var_8->unk_04;
                *arg_4 = &var_8->unk_08[local_C];
                var_1 = true;
                break;
            }
            if (var_10 > arg_0)
                break;
        }
        var_8 = var_8->unk_00;
    }
    return var_1;
}

// match: ?sub_6F340@type_3D2DB8@@QAE_NPAUtype_4492EC@@PAH@Z @ 0x0006F340
// sp-match: ?sub_6F340@type_3D2DB8@@QAE_NPAUtype_4492EC@@PAH@Z @ 0x0005CC30
bool type_3D2DB8::sub_6F340(type_4492EC *arg_0, RwInt32 *arg_4)
{
    RwInt32 stk_18;
    RwInt32 *l14;
    RwInt32 *var_10;
    RwInt32 *ebp_C;
    RwInt32 *v8;
    type_3D2DB8_6C_08 *var_4;

    var_4 = 0;
    l14 = 0;
    if (!sub_6F290(arg_0->unk_04, &var_4, &l14))
        return false;
    v8 = unk_68;
    var_10 = dword_4493F8;
    ebp_C = dword_4493FC;
    dword_4493FC = dword_4493F8;
    for (stk_18 = 0; stk_18 < arg_0->unk_08; stk_18++)
        dword_4493F8[stk_18] = *(arg_4 - (arg_0->unk_08 - stk_18));
    dword_4493F8 += arg_0->unk_08;
    unk_68 = l14 + var_4->unk_02;
    unk_98 |= 1;
    sub_68310((type_67620 *)this);
    unk_98 &= ~1;
    unk_68 = v8;
    dword_4493F8 = var_10;
    dword_4493FC = ebp_C;
    return true;
}

// match: ?sub_6F460@type_3D2DB8@@QAEXPAH@Z @ 0x0006F460
// sp-match: ?sub_6F460@type_3D2DB8@@QAEXPAH@Z @ 0x0005CD20
void type_3D2DB8::sub_6F460(RwInt32 *arg_0)
{
    dword_4493F8 = arg_0;
    dword_4493FC = dword_4493F8;
}

// match: ?sub_6F490@type_3D2DB8@@QAEXXZ @ 0x0006F490
// sp-match: ?sub_6F490@type_3D2DB8@@QAEXXZ @ 0x0005E850
void type_3D2DB8::sub_6F490()
{
    RwInt16 var_4;

    while (unk_92 != -1) {
        var_4 = unk_92;
        unk_92 = -1;
        if (!sub_6FB10(var_4))
            sub_6FA30(var_4);
        sub_6F520(var_4);
    }
}

// match: ?sub_6F500@type_3D2DB8@@QAEXF@Z @ 0x0006F500
// sp-match: ?sub_6F500@type_3D2DB8@@QAEXF@Z @ 0x0005CD40
void type_3D2DB8::sub_6F500(RwInt16 arg_0)
{
    unk_92 = arg_0;
}

// match: ?sub_6F520@type_3D2DB8@@QAEXF@Z @ 0x0006F520
// sp-match: ?sub_6F520@type_3D2DB8@@QAEXF@Z @ 0x0005E670
void type_3D2DB8::sub_6F520(RwInt16 arg_0)
{
    RwInt32 l14;
    type_3D2DB8_6C *var_10;
    type_3D2DB8_6C *ebp_C;
    RwInt32 v8;
    RwInt32 *var_4;

    if (sub_6FB10(arg_0))
        sub_6F690(arg_0);
    else if (arg_0 != unk_90) {
        ebp_C = &unk_8C[arg_0];
        var_10 = unk_6C;
        while (var_10 != ebp_C->unk_00 && var_10 != ebp_C) {
            sub_6F760(var_10->unk_10);
            var_10 = var_10->unk_00;
        }
        if (var_10 == ebp_C->unk_00)
            sub_6F690(arg_0);
    }
    unk_90 = arg_0;
    unk_6C = &unk_8C[arg_0];
    var_4 = dword_4493F8;
    sub_6EEF0();
    v8 = unk_6C->unk_16;
    for (l14 = 0; l14 < unk_6C->unk_1C; l14++)
        unk_74[v8 + l14] = *(var_4 - (unk_6C->unk_1C - l14));
    if (unk_6C->unk_12 != -1) {
        unk_68 = unk_6C->unk_04 + unk_6C->unk_12;
        sub_68310((type_67620 *)this);
    }
}

// match: ?sub_6F690@type_3D2DB8@@QAEXH@Z @ 0x0006F690
// sp-match: ?sub_6F690@type_3D2DB8@@QAEXH@Z @ 0x0005DD60
void type_3D2DB8::sub_6F690(RwInt32 arg_0)
{
    type_6B960 *var_10;
    type_42E00_00 *ebp_C;
    RwInt32 v8;
    type_3D2DB8_6C *var_4;

    var_4 = &unk_8C[arg_0];
    for (v8 = 0; v8 < var_4->unk_1B; v8++) {
        ebp_C = sub_6A7D0(var_4->unk_0C[v8].unk_00);
        if (ebp_C->unk_12 != 2) {
            var_10 = sub_6B9A0((type_67620 *)this, (RwInt32)var_4, &var_4->unk_0C[v8], unk_70,
                               var_4->unk_0C[v8].unk_00, var_4->unk_0C[v8].unk_04[0],
                               var_4->unk_0C[v8].unk_04[1]);
            sub_6F7E0(var_10);
        }
    }
}

// match: ?sub_6F760@type_3D2DB8@@QAEXH@Z @ 0x0006F760
// sp-match: ?sub_6F760@type_3D2DB8@@QAEXH@Z @ 0x0005DDE0
void type_3D2DB8::sub_6F760(RwInt32 arg_0)
{
    type_6B960 *local_8;
    type_6B960 *var_4;

    var_4 = unk_9C;
    while (var_4 != 0 && ((type_3D2DB8_6C *)var_4->unk_04)->unk_10 == arg_0) {
        local_8 = get_registration(var_4->unk_0C);
        sub_6F910(var_4);
        sub_6BC40(var_4);
        var_4 = local_8;
    }
}

// match: ?sub_6F7E0@type_3D2DB8@@QAEXPAUtype_6B960@@@Z @ 0x0006F7E0
// sp-match: ?sub_6F7E0@type_3D2DB8@@QAEXPAUtype_6B960@@@Z @ 0x0005CD50
void type_3D2DB8::sub_6F7E0(type_6B960 *arg_0)
{
    type_6B960 *varC;
    type_6B960 *local_8;
    type_6B960 *var_4;

    var_4 = arg_0;
    for (local_8 = unk_9C; local_8 != 0; local_8 = get_registration(local_8->unk_0C)) {
        varC = local_8;
        if (varC->unk_08->unk_00 == var_4->unk_08->unk_00 && (local_8->unk_1A & 1) == 0) {
            if (local_8->unk_1A & 4)
                local_8->unk_1A ^= 4;
            else
                local_8->unk_1A |= 2;
            var_4->unk_0E = (RwInt16)get_registration_index(local_8);
            break;
        }
    }
    var_4->unk_0C = (RwInt16)get_registration_index(unk_9C);
    unk_9C = arg_0;
}

// match: ?sub_6F910@type_3D2DB8@@QAEXPAUtype_6B960@@@Z @ 0x0006F910
// sp-match: ?sub_6F910@type_3D2DB8@@QAEXPAUtype_6B960@@@Z @ 0x0005CDF0
void type_3D2DB8::sub_6F910(type_6B960 *arg_0)
{
    type_6B960 *var_4;

    var_4 = arg_0;
    if (var_4->unk_0E != -1) {
        if (dword_44932C == var_4->unk_08->unk_00)
            get_registration(var_4->unk_0E)->unk_1A |= 4;
        else
            get_registration(var_4->unk_0E)->unk_1A ^= 2;
        var_4->unk_0E = -1;
    }
    unk_9C = get_registration(var_4->unk_0C);
    var_4->unk_0C = -1;
}

// match: ?sub_6FA30@type_3D2DB8@@QAEXH@Z @ 0x0006FA30
// sp-match: ?sub_6FA30@type_3D2DB8@@QAEXH@Z @ 0x0005CE80
void type_3D2DB8::sub_6FA30(RwInt32 arg_0)
{
    RwInt32 *var_10;
    RwInt32 *ebp_C;
    type_3D2DB8_6C *v8;
    type_3D2DB8_6C *var_4;

    v8 = unk_8C[arg_0].unk_00;
    var_4 = unk_6C;
    while (var_4 != 0 && var_4 != v8) {
        if (var_4->unk_14 != -1) {
            ebp_C = dword_4493FC;
            var_10 = dword_4493F8;
            sub_6F460(dword_4493F8);
            unk_68 = var_4->unk_04 + var_4->unk_14;
            unk_98 |= 2;
            sub_68310((type_67620 *)this);
            unk_98 &= ~2;
            dword_4493F8 = var_10;
            dword_4493FC = ebp_C;
        }
        var_4 = var_4->unk_00;
    }
}

// match: ?sub_6FB10@type_3D2DB8@@QAE_NH@Z @ 0x0006FB10
// sp-match: ?sub_6FB10@type_3D2DB8@@QAE_NH@Z @ 0x0005CF20
bool type_3D2DB8::sub_6FB10(RwInt32 arg_0)
{
    return unk_8C[arg_0].unk_00 == unk_6C;
}

// match: ?vf_00C@type_3D2DB8@@UAEHXZ @ 0x0006FB40
// sp-match: ?vf_00C@type_3D2DB8@@UAEHXZ @ 0x0005CF40
RwInt32 type_3D2DB8::vf_00C()
{
    return (RwInt32)unk_4498D0;
}

// match: ?sub_6FB50@type_3D2DB8@@QAEHXZ @ 0x0006FB50
// sp-match: ?sub_6FB50@type_3D2DB8@@QAEHXZ @ 0x0005CF50
RwInt32 type_3D2DB8::sub_6FB50()
{
    type_3D2E7C *var_4;

    var_4 = (type_3D2E7C *)sub_67620(unk_7C);
    if (var_4 != 0)
        return var_4->get_unk_0C();
    return 0;
}

// match: ?vf_024@type_3D2DB8@@UAEPAUtype_3D2E7C@@XZ @ 0x0006FB90
// sp-match: ?vf_024@type_3D2DB8@@UAEPAUtype_3D2E7C@@XZ @ 0x0005CF70
type_3D2E7C *type_3D2DB8::vf_024()
{
    return (type_3D2E7C *)sub_67620(unk_7C);
}

// match: ?sub_6FBB0@type_3D2DB8@@QAEXPAUtype_3D2E7C@@@Z @ 0x0006FBB0
// sp-match: ?sub_6FBB0@type_3D2DB8@@QAEXPAUtype_3D2E7C@@@Z @ 0x0005CF80
void type_3D2DB8::sub_6FBB0(type_3D2E7C *arg_0)
{
    if (arg_0 != 0)
        unk_7C_h = arg_0->get_unk_04_h();
    else
        unk_7C = 0;
}

// match: ??0type_3D2E20@@QAE@XZ @ 0x0006FBF0
// sp-match: ??0type_3D2E20@@QAE@XZ @ 0x0005CFA0
type_3D2E20::type_3D2E20()
{
    unk_F8 = 0;
    unk_FC = 0;
    unk_100 = 0;
    unk_104 = 0;
    unk_108 = 0;
    unk_114 = 0;
    unk_110 = -1;
    unk_120 = 0;
}

// match: ?vf_00C@type_3D2E20@@UAEHXZ @ 0x0006FC80
// sp-match: ?vf_00C@type_3D2E20@@UAEHXZ @ 0x0005CFF0

// match: ?vf_010@type_3D2E20@@UAEHXZ @ 0x0006FCA0
// sp-match: ?vf_010@type_3D2E20@@UAEHXZ @ 0x0005C9F0

// match: ?vf_028@type_3D2E20@@UAEHXZ @ 0x0006FCB0
// sp-match: ?vf_028@type_3D2E20@@UAEHXZ @ 0x0005D000

// match: ?vf_034@type_3D2E20@@UAEPAU1@XZ @ 0x0006FCD0
// sp-match: ?vf_034@type_3D2E20@@UAEPAU1@XZ @ 0x000D6180

// match: ??_Gtype_3D2E20@@UAEPAXI@Z @ 0x0006FCE0
// match: ??1type_3D2E20@@UAE@XZ @ 0x0006FD00
// sp-match: ??_Gtype_3D2E20@@UAEPAXI@Z @ 0x0005DE40
// sp-match: ??1type_3D2E20@@UAE@XZ @ 0x0005D010
type_3D2E20::~type_3D2E20()
{
}

// match: ?vf_054@type_3D2E20@@UAEXHH@Z @ 0x0006FD20
// sp-match: ?vf_054@type_3D2E20@@UAEXHH@Z @ 0x0005D020
void type_3D2E20::vf_054(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_04 = 0;
    type_3D2C30::vf_04C(arg_0);
    unk_110 = arg_4;
    unk_10C = true;
    unk_10D = 0;
    unk_118 = 0;
}

// match: ?vf_050@type_3D2E20@@UAEXXZ @ 0x0006FD70
// sp-match: ?vf_050@type_3D2E20@@UAEXXZ @ 0x0005E8A0
void type_3D2E20::vf_050()
{
    sub_73470(this);
    sub_6FDB0();
    unk_110 = -1;
    type_3D2C30::vf_050();
}

// match: ?sub_6FDB0@type_3D2E20@@QAEXXZ @ 0x0006FDB0
// sp-match: ?sub_6FDB0@type_3D2E20@@QAEXXZ @ 0x0005E760
void type_3D2E20::sub_6FDB0()
{
    type_3D2E20_118 *local_8;
    type_3D2E20_118 *var_4;

    local_8 = unk_118;
    var_4 = 0;
    while (local_8 != 0) {
        var_4 = local_8->unk_04;
        sub_70290(local_8);
        sub_70220(local_8);
        local_8 = var_4;
    }
}

// match: ?sub_6FE00@type_3D2E20@@QAEXH@Z @ 0x0006FE00
// sp-match: ?sub_6FE00@type_3D2E20@@QAEXH@Z @ 0x0005EC40
void type_3D2E20::sub_6FE00(RwInt32 arg_0)
{
    unk_74 = sub_72A30(arg_0);
    unk_108 = arg_0;
    sub_6FE40();
}

// match: ?sub_6FE40@type_3D2E20@@QAEXXZ @ 0x0006FE40
// sp-match: ?sub_6FE40@type_3D2E20@@QAEXXZ @ 0x0005E8C0
void type_3D2E20::sub_6FE40()
{
    type_3D2E20 *var_4;

    sub_6FEC0();
    unk_68 = unk_74->unk_08;
    var_4 = (type_3D2E20 *)sub_67620(unk_100.unk_00);
    if (var_4 != 0) {
        var_4->sub_70BA0();
        var_4->sub_70AF0();
        unk_100 = 0;
    }
    sub_6FDB0();
    unk_10D = 0;
    unk_10C = true;
}

// match: ?sub_6FEC0@type_3D2E20@@QAEXXZ @ 0x0006FEC0
// sp-match: ?sub_6FEC0@type_3D2E20@@QAEXXZ @ 0x0005D050
void type_3D2E20::sub_6FEC0()
{
    unk_6C = unk_78;
    unk_70 = unk_6C;
    unk_6C += 3;
}

// match: ?sub_6FF00@type_3D2E20@@QAEXXZ @ 0x0006FF00
// sp-match: ?sub_6FF00@type_3D2E20@@QAEXXZ @ 0x0005D060
void type_3D2E20::sub_6FF00()
{
    unk_10C = true;
    unk_10D = 0;
}

// match: ?sub_6FF20@type_3D2E20@@QAEXHHH_N@Z @ 0x0006FF20
// sp-match: ?sub_6FF20@type_3D2E20@@QAEXHHH_N@Z @ 0x0005E920
void type_3D2E20::sub_6FF20(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, bool arg_C)
{
    type_3D2E20_118 *local_8;
    type_6B960 *var_4;

    unk_10C = true;
    unk_10D = 1;
    var_4 = sub_6BA60((type_67620 *)this, unk_110, arg_0, arg_4, arg_8);
    local_8 = sub_700C0(1, arg_C);
    var_4->unk_04 = (RwInt32)local_8;
    var_4->unk_08_s = (RwInt16)get_registration_index(local_8->unk_00);
    local_8->unk_00 = var_4;
    local_8->unk_0C = 0;
}

// match: ?sub_6FFD0@type_3D2E20@@QAEXHHH_N@Z @ 0x0006FFD0
// sp-match: ?sub_6FFD0@type_3D2E20@@QAEXHHH_N@Z @ 0x0005E9A0
void type_3D2E20::sub_6FFD0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, bool arg_C)
{
    type_3D2E20_118 *local_8;
    type_6B960 *var_4;

    var_4 = sub_6BA60((type_67620 *)this, unk_110, arg_0, arg_4, arg_8);
    local_8 = sub_700C0(2, arg_C);
    var_4->unk_04 = (RwInt32)local_8;
    var_4->unk_08_s = (RwInt16)get_registration_index(local_8->unk_00);
    local_8->unk_00 = var_4;
    local_8->unk_0C = next_interrupt_id();
}

// match: ?sub_70080@type_3D2E20@@QAEXPAH@Z @ 0x00070080
// sp-match: ?sub_70080@type_3D2E20@@QAEXPAH@Z @ 0x0005D070
void type_3D2E20::sub_70080(RwInt32 *arg_0)
{
    unk_118->unk_08 = arg_0;
}

// match: ?sub_700A0@type_3D2E20@@QAEHXZ @ 0x000700A0
// sp-match: ?sub_700A0@type_3D2E20@@QAEHXZ @ 0x0005D080
RwInt32 type_3D2E20::sub_700A0()
{
    return unk_118->unk_0C;
}

// match: ?sub_700C0@type_3D2E20@@QAEPAUtype_3D2E20_118@@H_N@Z @ 0x000700C0
// sp-match: ?sub_700C0@type_3D2E20@@QAEPAUtype_3D2E20_118@@H_N@Z @ 0x0005E790
type_3D2E20_118 *type_3D2E20::sub_700C0(RwInt32 arg_0, bool arg_4)
{
    type_3D2E20_118 *var_4;

    var_4 = 0;
    if (arg_4) {
        var_4 = sub_70130();
        var_4->unk_14_1 = arg_0;
        var_4->unk_14_0 = 0;
    } else
        var_4 = unk_118;
    return var_4;
}

// match: ?sub_70130@type_3D2E20@@QAEPAUtype_3D2E20_118@@XZ @ 0x00070130
// sp-match: ?sub_70130@type_3D2E20@@QAEPAUtype_3D2E20_118@@XZ @ 0x0005DE50
type_3D2E20_118 *type_3D2E20::sub_70130()
{
    type_3D2E20_118 *var_4;

    var_4 = sub_71820();
    var_4->unk_04 = unk_118;
    unk_118 = var_4;
    return var_4;
}

// match: ?sub_70170@type_3D2E20@@QAEXH@Z @ 0x00070170
// sp-match: ?sub_70170@type_3D2E20@@QAEXH@Z @ 0x0005DE70
void type_3D2E20::sub_70170(RwInt32 arg_0)
{
    RwInt32 varC;
    type_3D2E20_118 *local_8;
    type_3D2E20_118 *var_4;

    var_4 = 0;
    local_8 = unk_118;
    varC = 0;
    while (local_8 != 0) {
        if (local_8->unk_0C == arg_0 && local_8->unk_14_1 == 2) {
            varC = 1;
            break;
        }
        var_4 = local_8;
        local_8 = local_8->unk_04;
    }
    if (!varC)
        return;
    if (var_4 != 0)
        var_4->unk_04 = local_8->unk_04;
    else
        unk_118 = local_8->unk_04;
    sub_70290(local_8);
    sub_71850(local_8);
}

// match: ?sub_70220@type_3D2E20@@QAEXPAUtype_3D2E20_118@@@Z @ 0x00070220
// sp-match: ?sub_70220@type_3D2E20@@QAEXPAUtype_3D2E20_118@@@Z @ 0x0005DEE0
void type_3D2E20::sub_70220(type_3D2E20_118 *arg_0)
{
    type_3D2E20_118 *local_8;
    type_3D2E20_118 *var_4;

    var_4 = 0;
    local_8 = unk_118;
    while (local_8 != 0 && local_8 != arg_0) {
        var_4 = local_8;
        local_8 = local_8->unk_04;
    }
    if (var_4 != 0)
        var_4->unk_04 = arg_0->unk_04;
    else
        unk_118 = local_8->unk_04;
    sub_71850(arg_0);
}

// match: ?sub_70290@type_3D2E20@@QAEXPAUtype_3D2E20_118@@@Z @ 0x00070290
// sp-match: ?sub_70290@type_3D2E20@@QAEXPAUtype_3D2E20_118@@@Z @ 0x0005D090
void type_3D2E20::sub_70290(type_3D2E20_118 *arg_0)
{
    type_6B960 *local_8;
    type_6B960 *var_4;

    if (arg_0 != 0) {
        local_8 = arg_0->unk_00;
        var_4 = 0;
        while (local_8 != 0) {
            var_4 = get_registration(local_8->unk_08_s);
            local_8->unk_08_s = -1;
            sub_6BC40(local_8);
            local_8 = var_4;
        }
        arg_0->unk_00 = 0;
    }
}

// match: ?sub_70310@type_3D2E20@@QAEXXZ @ 0x00070310
// sp-match: ?sub_70310@type_3D2E20@@QAEXXZ @ 0x0005DF30
void type_3D2E20::sub_70310()
{
    unk_114->unk_04_h = get_unk_04_h();
    if (vf_024() != 0)
        vf_024()->sub_71050(this);
}

// match: ?sub_70360@type_3D2E20@@QAEXXZ @ 0x00070360
// sp-match: ?sub_70360@type_3D2E20@@QAEXXZ @ 0x0005DF60
void type_3D2E20::sub_70360()
{
    unk_114 = sub_71CA0();
    unk_114->unk_00_h = get_unk_04_h();
    unk_114->unk_04_h = get_unk_04_h();
    unk_114->unk_08 = 1;
}

// match: ?sub_703C0@type_3D2E20@@QAEXXZ @ 0x000703C0
// sp-match: ?sub_703C0@type_3D2E20@@QAEXXZ @ 0x0005DF90
void type_3D2E20::sub_703C0()
{
    unk_114->unk_08--;
    if (unk_114->unk_08 == 0)
        sub_71CC0(unk_114);
    unk_114 = 0;
}

// match: ?sub_70420@type_3D2E20@@QAEHPAUtype_3D2E20_118@@PAUtype_42E00@@@Z @ 0x00070420
// sp-match: ?sub_70420@type_3D2E20@@QAEHPAUtype_3D2E20_118@@PAUtype_42E00@@@Z @ 0x0005D0F0
RwInt32 type_3D2E20::sub_70420(type_3D2E20_118 *arg_0, type_42E00 *arg_4)
{
    type_6B960 *varC;
    type_6B960 *local_8;
    type_6B960 *var_4;

    if (arg_0->unk_14_0)
        return 1;
    varC = arg_0->unk_00;
    local_8 = 0;
    while (varC != 0) {
        var_4 = get_registration(varC->unk_08_s);
        if (varC->unk_14 == arg_4->unk_00->unk_04) {
            if (local_8 != 0)
                local_8->unk_08_s = varC->unk_08_s;
            else
                arg_0->unk_00 = var_4;
            varC->unk_08_s = -1;
            sub_6BC40(varC);
            break;
        }
        local_8 = varC;
        varC = var_4;
    }
    return arg_0->unk_00 == 0;
}

// match: ?sub_704F0@type_3D2E20@@QAEHHH@Z @ 0x000704F0
// sp-match: ?sub_704F0@type_3D2E20@@QAEHHH@Z @ 0x0005D180
RwInt32 type_3D2E20::sub_704F0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwUInt32 local_8;
    type_3D2E20 *var_4;

    if (is_current())
        return 1;
    var_4 = (type_3D2E20 *)sub_67620(unk_100.unk_00);
    while (var_4 != 0) {
        if (var_4->is_current())
            return 1;
        local_8 = var_4->unk_100.unk_00;
        var_4 = (type_3D2E20 *)sub_67620(local_8);
    }
    return 0;
}

// match: ?sub_70590@type_3D2E20@@QAEX_NPAUtype_3D2E20_118@@PAUtype_42E00@@@Z @ 0x00070590
// sp-match: ?sub_70590@type_3D2E20@@QAEX_NPAUtype_3D2E20_118@@PAUtype_42E00@@@Z @ 0x0005DFC0
void type_3D2E20::sub_70590(bool arg_0, type_3D2E20_118 *arg_4, type_42E00 *arg_8)
{
    RwInt32 ebp_34;
    RwUInt32 var_30;
    RwUInt32 bp_2C;
    RwUInt32 local_28;
    type_3D2E7C *local_24;
    type_3D2E7C *local_20;
    type_3D2E7C *var_1C;
    type_4CFE30 *var18;
    RwInt32 stk_14;
    RwInt32 l10;
    RwInt32 *local_C;
    RwInt32 *lv_8;
    RwInt32 *var_4;

    if ((!arg_0 && unk_10D != 0) || unk_110 == -1)
        return;
    l10 = 0;
    var_4 = unk_68;
    local_C = unk_6C;
    lv_8 = unk_70;
    stk_14 = unk_110;
    if (arg_4 != 0) {
        if (arg_4->unk_14_1 == 2) {
            l10 = 1;
            if (!sub_704F0((RwInt32)arg_4, (RwInt32)arg_8))
                return;
        } else if (!is_current())
            return;
        if (!sub_70420(arg_4, arg_8))
            return;
        unk_68 = arg_4->unk_08;
        if (l10 == 0 || arg_4->unk_10 == 1) {
            sub_70290(arg_4);
            sub_70220(arg_4);
        } else if (arg_4->unk_10 != 0)
            arg_4->unk_10--;
    }
    if (l10 == 0) {
        unk_10C = false;
        unk_10D = 0;
        if (vf_024() != 0)
            vf_024()->sub_71050(this);
    }
    if (arg_8 != 0) {
        local_20 = (type_3D2E7C *)sub_67620(arg_8->unk_08);
        var_1C = (type_3D2E7C *)sub_67620(arg_8->unk_0C);
        ebp_34 = arg_8->unk_10;
        if (ebp_34 >= 0 && ebp_34 < 2000)
            var18 = dword_4CFE30[ebp_34];
        else
            var18 = 0;
        unk_11C = arg_8->unk_00->unk_04;
        unk_70[0] = arg_8->unk_10;
        unk_70[1] = 0;
        unk_70[2] = 0;
#ifdef CODFH_SP // shape: the handles copied through the inline handle getter (SP 0x5DFC0)
        if (local_20 != 0)
            *(type_439E78_00 *)&unk_70[1] = local_20->get_unk_04_h();
        else if (var18 != 0) {
            local_24 = ((type_712B0 *)var18)->sub_BDF50();
            if (local_24 != 0)
                *(type_439E78_00 *)&unk_70[1] = local_24->get_unk_04_h();
        }
        if (var_1C != 0)
            *(type_439E78_00 *)&unk_70[2] = var_1C->get_unk_04_h();
#else
        if (local_20 != 0) {
            local_28 = local_20->unk_04;
            unk_70[1] = local_28;
        } else if (var18 != 0) {
            local_24 = ((type_712B0 *)var18)->sub_BDF50();
            if (local_24 != 0) {
                bp_2C = local_24->unk_04;
                unk_70[1] = bp_2C;
            }
        }
        if (var_1C != 0) {
            var_30 = var_1C->unk_04;
            unk_70[2] = var_30;
        }
#endif
    } else
        unk_11C = -1;
    sub_68310((type_67620 *)this);
    if (l10 != 0 && unk_110 == stk_14) {
        unk_68 = var_4;
        unk_6C = local_C;
        unk_70 = lv_8;
    }
}

// match: ?sub_70850@type_3D2E20@@QAEXH@Z @ 0x00070850
// sp-match: ?sub_70850@type_3D2E20@@QAEXH@Z @ 0x0005EC70
void type_3D2E20::sub_70850(RwInt32 arg_0)
{
    type_3D2E20 *var_4;

    var_4 = sub_70C40();
    sub_70BA0();
    if (var_4 != 0) {
        var_4->sub_70310();
        var_4->unk_120 = arg_0;
        var_4->sub_70590(0, 0, 0);
    } else {
        sub_703C0();
        if (vf_024() != 0)
            vf_024()->sub_71050(0);
    }
}

// match: ?vf_024@type_3D2E20@@UAEPAUtype_3D2E7C@@XZ @ 0x000708D0
// sp-match: ?vf_024@type_3D2E20@@UAEPAUtype_3D2E7C@@XZ @ 0x0005D1D0
type_3D2E7C *type_3D2E20::vf_024()
{
    return (type_3D2E7C *)sub_67620(unk_104);
}

// match: ?sub_708F0@type_3D2E20@@QAEXPAUtype_3D2E7C@@@Z @ 0x000708F0
// sp-match: ?sub_708F0@type_3D2E20@@QAEXPAUtype_3D2E7C@@@Z @ 0x0005D1E0
void type_3D2E20::sub_708F0(type_3D2E7C *arg_0)
{
    if (arg_0 != 0)
        unk_104_h = arg_0->get_unk_04_h();
    else
        unk_104 = 0;
}

// match: ?sub_70930@type_3D2E20@@QAEPAU1@PAU1@_N1@Z @ 0x00070930
// sp-match: ?sub_70930@type_3D2E20@@QAEPAU1@PAU1@_N1@Z @ 0x0005E1A0
type_3D2E20 *type_3D2E20::sub_70930(type_3D2E20 *arg_0, bool arg_4, bool arg_8)
{
    type_3D2E20 *varC;
    type_3D2E20 *local_8;
    type_3D2E20 *var_4;

    arg_0->sub_708F0(vf_024());
    arg_0->set_unk_114(unk_114);
    arg_0->unk_114->unk_08++;
    if (arg_4) {
        unk_100.unk_00_h = arg_0->get_unk_04_h();
        arg_0->unk_F8 = get_unk_04_h();
        return arg_0;
    }
    arg_0->unk_F8 = unk_F8.unk_00_h;
    if (arg_8) {
        var_4 = (type_3D2E20 *)sub_67620(unk_F8.unk_00);
        if (var_4 != 0) {
            arg_0->unk_FC = var_4->unk_100.get_h();
            var_4->unk_100 = arg_0->get_unk_04_h();
        } else {
            arg_0->unk_FC = unk_114->unk_00_h;
            unk_114->unk_00_h = arg_0->get_unk_04_h();
            vf_024()->sub_71010(arg_0);
        }
        return arg_0;
    }
    varC = this;
    local_8 = (type_3D2E20 *)sub_67620(unk_FC.unk_00);
    while (local_8 != 0) {
        varC = local_8;
        local_8 = (type_3D2E20 *)sub_67620(local_8->unk_FC.get_h());
    }
    varC->unk_FC = arg_0->get_unk_04_h();
    return this;
}

// match: ?sub_70AF0@type_3D2E20@@QAEXXZ @ 0x00070AF0
// sp-match: ?sub_70AF0@type_3D2E20@@QAEXXZ @ 0x0005E7C0
void type_3D2E20::sub_70AF0()
{
    type_3D2E20 *local_8;
    type_3D2E20 *var_4;

    var_4 = (type_3D2E20 *)sub_67620(unk_100.unk_00);
    local_8 = (type_3D2E20 *)sub_67620(unk_FC.unk_00);
    if (var_4 != 0) {
        var_4->sub_70AF0();
        unk_100 = 0;
    }
    if (local_8 != 0) {
        local_8->sub_70AF0();
        unk_FC = 0;
    }
    sub_70B70();
}

// match: ?sub_70B70@type_3D2C88@@QAEXXZ @ 0x00070B70
// sp-match: ?sub_70B70@type_3D2C88@@QAEXXZ @ 0x0005E2A0
void type_3D2C88::sub_70B70()
{
    sub_71970(this);
    unk_04 = 0;
}

// match: ?sub_70BA0@type_3D2E20@@QAEXXZ @ 0x00070BA0
// sp-match: ?sub_70BA0@type_3D2E20@@QAEXXZ @ 0x0005E2C0
void type_3D2E20::sub_70BA0()
{
    RwUInt32 local_8;
    type_3D2E20 *var_4;

    var_4 = (type_3D2E20 *)sub_67620(unk_F8.unk_00);
    if (var_4 != 0)
        var_4->unk_100 = unk_FC.unk_00_h;
    else {
        vf_024()->sub_70FF0(unk_FC.unk_00);
#ifdef CODFH_SP // shape: the handles compared as words (SP 0x5E2C0: cmp [thread], ecx)
        if (unk_114->unk_00_h == get_unk_04_h())
            unk_114->unk_00_h = unk_FC.unk_00_h;
#else
        local_8 = unk_04;
        if (unk_114->unk_00 == local_8)
            unk_114->unk_00_h = unk_FC.unk_00_h;
#endif
    }
    unk_FC = 0;
}

// match: ?sub_70C40@type_3D2E20@@QAEPAU1@XZ @ 0x00070C40
// sp-match: ?sub_70C40@type_3D2E20@@QAEPAU1@XZ @ 0x0005EA10
type_3D2E20 *type_3D2E20::sub_70C40()
{
    type_3D2E20 *local_8;
    type_3D2E20 *var_4;

    var_4 = (type_3D2E20 *)sub_67620(unk_FC.unk_00);
    local_8 = 0;
    if (var_4 != 0) {
        local_8 = var_4;
        var_4->sub_6FE40();
    } else
        local_8 = (type_3D2E20 *)sub_67620(unk_F8.unk_00);
    return local_8;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_000@type_3D2C88@@UAEPAHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 *type_3D2C88::vf_000()
{
    return 0;
}

// ?vf_004@type_3D2C88@@UAEPAHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 *type_3D2C88::vf_004()
{
    return 0;
}

// ?vf_008@type_3D2C88@@UAEPAHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 *type_3D2C88::vf_008()
{
    return 0;
}

// ?vf_00C@type_3D2C88@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D2C88::vf_00C()
{
    return 0;
}

// ?vf_010@type_3D2C88@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D2C88::vf_010()
{
    return 0;
}

// ?vf_014@type_3D2C88@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D2C88::vf_014()
{
    return 0;
}

// ?vf_018@type_3D2C88@@UAEXPAH@Z (folded into the empty body at 0x15FB30)
void type_3D2C88::vf_018(RwInt32 *arg_0)
{
}

// ?vf_01C@type_3D2C88@@UAEXPAH@Z (folded into the empty body at 0x15FB30)
void type_3D2C88::vf_01C(RwInt32 *arg_0)
{
}

// ?vf_020@type_3D2C88@@UAEXPAH@Z (folded into the empty body at 0x15FB30)
void type_3D2C88::vf_020(RwInt32 *arg_0)
{
}

// ?vf_024@type_3D2C88@@UAEPAUtype_3D2E7C@@XZ (folded into `return 0` at 0x1E4CB0)
type_3D2E7C *type_3D2C88::vf_024()
{
    return 0;
}

// ?vf_028@type_3D2C88@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D2C88::vf_028()
{
    return 0;
}

// ?vf_02C@type_3D2C88@@UAEPAUtype_3D2CD0@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_3D2CD0 *type_3D2C88::vf_02C()
{
    return 0;
}

// ?vf_030@type_3D2C88@@UAEPAUtype_3D2DB8@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_3D2DB8 *type_3D2C88::vf_030()
{
    return 0;
}

// ?vf_034@type_3D2C88@@UAEPAUtype_3D2E20@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_3D2E20 *type_3D2C88::vf_034()
{
    return 0;
}

// ?vf_050@type_3D2C30@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3D2C30::vf_050()
{
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_3D2CD0@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_3D2CD0::operator delete(void *arg_0, void *arg_4)
{
}

// ??3type_3D2DB8@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_3D2DB8::operator delete(void *arg_0, void *arg_4)
{
}

// ??3type_3D2E20@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_3D2E20::operator delete(void *arg_0, void *arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3D2DB8@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D2DB8::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ??2type_3D2E20@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D2E20::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?vf_010@type_3D2DB8@@UAEHXZ (folded into 0x6FCA0)
RwInt32 type_3D2DB8::vf_010()
{
    return 0x20;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E7540@type_3D2C88@@QAEXI@Z (folded into 0x1E7540)
void type_3D2C88::sub_1E7540(RwUInt32 arg_0)
{
    unk_04 = arg_0;
}

// The current line (slot +0x40), folded by /OPT:ICF into type_FB6E0's getter of
// +8 (0xFB710).
RwInt32 type_3D2C88::vf_040()
{
    return unk_08;
}

// Not in the image: a stand-in for a function the original object held after the others,
// which nothing called, so the link's /OPT:REF dropped it. It was the first to use the text
// "%s " (the image keeps it, 0x3D2E78, after this object's last vtable, type_3D2E20's, though
// its only surviving user is XGRAPHICS' InstructionDisassembler::Disassemble). Its body is
// unknown: this one only prints the text.
// match: ??_C@_03IKGEINEE@?$CFs?5?$AA@ @ 0x003D2E78
void dropped_3D2E78(const RwChar *arg_0)
{
    sub_19A750("%s ", arg_0);
}
