// alfasched: the scheduler that runs registered objects' callbacks a few at
// a time (named from the image's string "alfasched::m_freeList"). The file's
// original name is not recovered (M1), so it is named for its start address.

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/alfasched.h"
#include "types/type_439E78.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BG@HKFKICGF@alfasched?3?3m_freeList?$AA@ @ 0x003D30C8
// match: ??_C@_0IK@BHKMADDA@Some?5things?5are?5still?5registered@ @ 0x003D30E0

// match: ??0alfasched@@QAE@XZ @ 0x00071EC0
// sp-match: ??0alfasched@@QAE@XZ @ 0x0005F040

alfasched::alfasched()
{
    unk_3C = 0;
    unk_40 = 0;
    unk_00 = 0;
    unk_04 = 0;
}

// match: ??1alfasched@@QAE@XZ @ 0x00071F00
// sp-match: ??1alfasched@@QAE@XZ @ 0x0005F060
alfasched::~alfasched()
{
}

// match: ?sub_71F20@alfasched@@QAEXHHHHP6AHPAUtype_67620@@HMH@Z1@Z @ 0x00071F20
// sp-match: ?sub_71F20@alfasched@@QAEXHHHHP6AHPAUtype_67620@@HMH@Z1@Z @ 0x0005F070
void alfasched::sub_71F20(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                          alfasched_callback arg_10, alfasched_test arg_14)
{
    unk_2C = arg_0;
    unk_30 = arg_4;
    unk_34 = arg_8;
    unk_38 = arg_C;
    unk_3C = arg_10;
    unk_40 = arg_14;
    unk_44 = 0;
    unk_48 = 0;
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
    // (the port's debug tools: every scheduler room for the bots, port/src/debug/trigtools.cpp;
    // its entries are taken unchecked, sub_72050)
    m_freeList.sub_16C2C0(arg_0 * 4, 0x1C, "alfasched::m_freeList", 4, 0);
#else
    m_freeList.sub_16C2C0(arg_0, 0x1C, "alfasched::m_freeList", 4, 0);
#endif
}

// match: ?sub_71FA0@alfasched@@QAEHXZ @ 0x00071FA0
// sp-match: ?sub_71FA0@alfasched@@QAEHXZ @ 0x0005F5C0
RwInt32 alfasched::sub_71FA0()
{
    RwInt32 var_4;

    var_4 = sub_71FF0();
    return var_4;
}

// match: ?sub_71FC0@alfasched@@QAEHXZ @ 0x00071FC0
// sp-match: ?sub_71FC0@alfasched@@QAEHXZ @ 0x0005F5D0
RwInt32 alfasched::sub_71FC0()
{
    RwInt32 var_4;

    var_4 = sub_71FF0();
    m_freeList.sub_16C4D0(1);
    return var_4;
}

// match: ?sub_71FF0@alfasched@@QAEHXZ @ 0x00071FF0
// sp-match: ?sub_71FF0@alfasched@@QAEHXZ @ 0x0005F590
RwInt32 alfasched::sub_71FF0()
{
    RwInt32 var_4;
    alfasched_entry *v8;
    alfasched_entry *varC;

    var_4 = 0;
    if (unk_00 != 0) {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        // single player compiles the debug print out (SP 0x5F590)
        sub_19A750("Some things are still registered in the scheduler at restart/shutdown!  "
                   "But this might not be anybody's fault.  I'll clean it up for you\n");
#endif
        varC = unk_00;
        while (varC != 0) {
            v8 = varC->unk_18;
            sub_722B0(varC->unk_00);
            varC = v8;
        }
    }
    return var_4;
}

// match: ?sub_72050@alfasched@@QAE?AUtype_72050@@PAUtype_67620@@HMH@Z @ 0x00072050
// sp-match: ?sub_72050@alfasched@@QAE?AUtype_72050@@PAUtype_67620@@HMH@Z @ 0x0005F3C0
type_72050 alfasched::sub_72050(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    alfasched_entry *var_8;
    bool var_1;

    var_8 = 0;
    var_1 = false;
    if (unk_38 != 0) {
        var_8 = sub_72320(arg_0);
        var_1 = var_8 != 0;
    }
    if (var_8 == 0) {
        var_8 = (alfasched_entry *)m_freeList.sub_16C5A0(0);
        var_8->unk_00 = sub_673C0((type_67620 *)var_8, 5);
    }
    var_8->unk_04_h = arg_0->get_unk_04_h();
    var_8->unk_08 = arg_4;
    var_8->unk_0C = arg_8;
    var_8->unk_10 = arg_C;
    var_8->unk_14 = arg_0->vf_028();
    if (!var_1) {
        var_8->unk_18 = 0;
        sub_72410(var_8);
    }
    return *(type_72050 *)var_8;
}

// match: ?sub_72120@alfasched@@QAE?AUtype_72050@@PAUtype_67620@@HMH@Z @ 0x00072120
// sp-match: ?sub_72120@alfasched@@QAE?AUtype_72050@@PAUtype_67620@@HMH@Z @ 0x0005F450
type_72050 alfasched::sub_72120(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    alfasched_entry *var_8;
    bool var_1;

    var_8 = 0;
    var_1 = false;
    if (unk_38 != 0) {
        var_8 = sub_72320(arg_0);
        var_1 = var_8 != 0;
    }
    if (var_8 == 0) {
        var_8 = (alfasched_entry *)m_freeList.sub_16C5A0(0);
        var_8->unk_00 = sub_673C0((type_67620 *)var_8, 5);
    }
    var_8->unk_04_h = arg_0->get_unk_04_h();
    var_8->unk_08 = arg_4;
    var_8->unk_0C = arg_8;
    var_8->unk_10 = arg_C;
    var_8->unk_14 = arg_0->vf_028();
    if (var_1) {
        alfasched_entry *var_10;
        alfasched_entry *var_C;

        var_10 = unk_00;
        var_C = 0;
        do {
            if (var_10 == var_8 || var_10 == 0)
                break;
            var_C = var_10;
            var_10 = var_10->unk_18;
        } while (var_10 != 0);
        if (var_C != 0)
            var_C->unk_18 = var_8->unk_18;
        else
            unk_00 = var_8->unk_18;
    }
    sub_72380(var_8);
    return *(type_72050 *)var_8;
}

// match: ?sub_72240@alfasched@@QAEXPAUtype_67620@@@Z @ 0x00072240
// sp-match: ?sub_72240@alfasched@@QAEXPAUtype_67620@@@Z @ 0x0005F500
void alfasched::sub_72240(type_67620 *arg_0)
{
    alfasched_entry *stk_C;
    alfasched_entry *var_4;
    alfasched_entry *v8;
    RwUInt32 var_10;

    stk_C = unk_00;
    var_4 = 0;
    v8 = 0;
    var_10 = arg_0->get_unk_04();
    while (stk_C != 0) {
        var_4 = stk_C->unk_18;
        if (stk_C->unk_04 == var_10)
            sub_724B0(v8, stk_C);
        else
            v8 = stk_C;
        stk_C = var_4;
    }
}

// match: ?sub_722B0@alfasched@@QAEXI@Z @ 0x000722B0
// sp-match: ?sub_722B0@alfasched@@QAEXI@Z @ 0x0005F570
void alfasched::sub_722B0(RwUInt32 arg_0)
{
    alfasched_entry *var_4;

    var_4 = (alfasched_entry *)sub_67620(arg_0);
    sub_72450(var_4);
}

// match: ?sub_722E0@alfasched@@QAEHPAUalfasched_entry@@@Z @ 0x000722E0
// sp-match: ?sub_722E0@alfasched@@QAEHPAUalfasched_entry@@@Z @ 0x0005F0C0
RwInt32 alfasched::sub_722E0(alfasched_entry *arg_0)
{
    alfasched_entry *var_4;

    for (var_4 = unk_00; var_4 != 0; var_4 = var_4->unk_18) {
        if (var_4 == arg_0)
            return 1;
    }
    return 0;
}

// match: ?sub_72320@alfasched@@QAEPAUalfasched_entry@@PAUtype_67620@@@Z @ 0x00072320
// sp-match: ?sub_72320@alfasched@@QAEPAUalfasched_entry@@PAUtype_67620@@@Z @ 0x0005F0F0
alfasched_entry *alfasched::sub_72320(type_67620 *arg_0)
{
    alfasched_entry *var_4;

    for (var_4 = unk_00; var_4 != 0; var_4 = var_4->unk_18) {
#ifdef CODFH_SP
        // shape: the argument's handle read through its struct getter (SP 0x5F0F0)
        if (var_4->unk_04 == arg_0->get_unk_04_h() && var_4->unk_14 == arg_0->vf_028())
#else
        if (var_4->unk_04 == arg_0->get_unk_04() && var_4->unk_14 == arg_0->vf_028())
#endif
            return var_4;
    }
    return 0;
}

// match: ?sub_72380@alfasched@@QAEXPAUalfasched_entry@@@Z @ 0x00072380
// sp-match: ?sub_72380@alfasched@@QAEXPAUalfasched_entry@@@Z @ 0x0005F130
void alfasched::sub_72380(alfasched_entry *arg_0)
{
    arg_0->unk_18 = 0;
    if (unk_08 != 0) {
        arg_0->unk_18 = unk_08->unk_18;
        unk_08->unk_18 = arg_0;
        if (unk_08 == unk_04)
            unk_04 = arg_0;
    } else if (unk_04 == 0) {
        unk_00 = arg_0;
        unk_04 = arg_0;
    } else {
        arg_0->unk_18 = unk_00;
        unk_00 = arg_0;
    }
}

// match: ?sub_72410@alfasched@@QAEXPAUalfasched_entry@@@Z @ 0x00072410
// sp-match: ?sub_72410@alfasched@@QAEXPAUalfasched_entry@@@Z @ 0x0005F180
void alfasched::sub_72410(alfasched_entry *arg_0)
{
    if (unk_04 != 0) {
        unk_04->unk_18 = arg_0;
        unk_04 = arg_0;
    } else {
        unk_00 = arg_0;
        unk_04 = arg_0;
    }
}

// match: ?sub_72450@alfasched@@QAEXPAUalfasched_entry@@@Z @ 0x00072450
// sp-match: ?sub_72450@alfasched@@QAEXPAUalfasched_entry@@@Z @ 0x0005F540
void alfasched::sub_72450(alfasched_entry *arg_0)
{
    alfasched_entry *v8;
    alfasched_entry *var_4;
    RwInt32 varC;

    v8 = unk_00;
    var_4 = 0;
    varC = 0;
    do {
        if (v8 == arg_0) {
            sub_724B0(var_4, arg_0);
            varC = 1;
        }
        var_4 = v8;
        v8 = v8->unk_18;
    } while (v8 != 0);
}

// match: ?sub_724B0@alfasched@@QAEXPAUalfasched_entry@@0@Z @ 0x000724B0
// sp-match: ?sub_724B0@alfasched@@QAEXPAUalfasched_entry@@0@Z @ 0x0005F1A0
void alfasched::sub_724B0(alfasched_entry *arg_0, alfasched_entry *arg_4)
{
    if (unk_40 != 0)
        unk_40(sub_67620(arg_4->unk_04), arg_4->unk_08, arg_4->unk_0C, arg_4->unk_10);
    if (arg_0 != 0)
        arg_0->unk_18 = arg_4->unk_18;
    else
        unk_00 = arg_4->unk_18;
    if (arg_4 == unk_04)
        unk_04 = arg_0;
    sub_67520(arg_4->unk_00);
    arg_4->unk_18 = 0;
    arg_4->unk_00 = 0;
    m_freeList.sub_16C710(arg_4);
}

// match: ?sub_72560@alfasched@@QAEXM@Z @ 0x00072560
// sp-match: ?sub_72560@alfasched@@QAEXM@Z @ 0x0005F220
void alfasched::sub_72560(RwReal arg_0)
{
    alfasched_entry *var_10;
    alfasched_entry *v8;
    alfasched_entry *ebp_C;
    RwInt32 var_4;

    unk_48 = 0;
    unk_44 = arg_0 + unk_44;
#ifdef CODFH_SP
    // shape: the clock tested from its own side (SP 0x5F220)
    if (unk_44 < unk_30 || unk_00 == 0)
#else
    if (unk_30 > unk_44 || unk_00 == 0)
#endif
        return;
    var_10 = unk_00;
    v8 = 0;
    ebp_C = 0;
    var_4 = 0;
    while (var_10 != 0 && var_4 < unk_34) {
        RwInt32 var_18;
        type_67620 *var_14;

        var_18 = 0;
        var_14 = sub_67620(var_10->unk_04);
        if (var_14 != 0 && var_14->vf_028() == var_10->unk_14) {
            unk_08 = var_10;
            var_18 = unk_3C(var_14, var_10->unk_08, var_10->unk_0C, var_10->unk_10);
            unk_08 = 0;
        }
        v8 = var_10->unk_18;
        if (var_18 == 0 || unk_48 != 0)
            sub_724B0(ebp_C, var_10);
        else
            ebp_C = var_10;
        var_10 = v8;
        unk_48 = 0;
        var_4++;
    }
    if (ebp_C != 0 && v8 != 0) {
        unk_04->unk_18 = unk_00;
        unk_00 = v8;
        unk_04 = ebp_C;
        unk_04->unk_18 = 0;
    }
    unk_44 -= unk_30;
}

// match: ?sub_726E0@alfasched@@QAEXP6AHPAUtype_67620@@HMH@Z@Z @ 0x000726E0
// sp-match: ?sub_726E0@alfasched@@QAEXP6AHPAUtype_67620@@HMH@Z@Z @ 0x0005F310
void alfasched::sub_726E0(alfasched_callback arg_0)
{
    alfasched_entry *var_10;
    alfasched_entry *v8;
    alfasched_entry *ebp_C;
    RwInt32 var_4;

    var_10 = unk_00;
    v8 = 0;
    ebp_C = 0;
    var_4 = 0;
    while (var_10 != 0) {
        RwInt32 var_18;
        type_67620 *var_14;

        var_18 = 0;
        var_14 = sub_67620(var_10->unk_04);
        if (var_14 != 0 && var_14->vf_028() == var_10->unk_14)
            var_18 = arg_0(var_14, var_10->unk_08, var_10->unk_0C, var_10->unk_10);
        v8 = var_10->unk_18;
        if (var_18 == 0) {
            if (var_10 == unk_08) {
                unk_48 = 1;
                var_10->unk_14 = -1;
            } else
                sub_724B0(ebp_C, var_10);
        } else
            ebp_C = var_10;
        var_10 = v8;
        var_4++;
    }
}

// match: ?sub_727D0@alfasched@@QAEHXZ @ 0x000727D0
// sp-match: ?sub_727D0@alfasched@@QAEHXZ @ 0x0005F3A0
RwInt32 alfasched::sub_727D0()
{
    RwInt32 var_4;
    alfasched_entry *local_8;

    var_4 = 0;
    for (local_8 = unk_00; local_8 != 0; local_8 = local_8->unk_18)
        var_4++;
    return var_4;
}
