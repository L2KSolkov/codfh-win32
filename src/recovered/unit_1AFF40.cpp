// The log (game/startup.h, type_4F84B8): three channels of fifty lines, and
// what draws them. The one log is built at unk_4F84C0 by an initializer
// the database misses (0x30C220; its exit thunk is sub_30EAA0), which
// no unit places yet.

#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "game/startup.h"
#include "game/voice.h"
#include "game/netscore.h"
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "game/netqueue.h"
#include "game/debugtext.h"
#include "types/type_3D3548.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E1A60
extern const RwUInt32 dword_3E1A60[3] = { 4, 10, 29 };
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E1A6C
extern const RwReal flt_3E1A6C = 0.01f;
// 0x003E1A70
extern const RwReal flt_3E1A70 = 0.01f;
// 0x003E1A74
extern const RwReal flt_3E1A74 = 16.666666f;
#endif
// 0x004F84B8
type_4F84B8 *dword_4F84B8;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4F84B8 unk_4F84C0;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?dword_3E1A60@@3QBIB @ 0x003E1A60
// match: ?flt_3E1A6C@@3MB @ 0x003E1A6C
// match: ?flt_3E1A70@@3MB @ 0x003E1A70
// match: ?flt_3E1A74@@3MB @ 0x003E1A74
// match: ??_C@_0CC@BPNDFDJB@?$CF3d?5?5?$CF6d?5?5?$CF6s?5?5?$CF7d?5?5?$CF6s?5?5?$CF6s?5?5?$CF7@ @ 0x003E1A78
// match: ??_C@_06MHJDLBHA@ACTIVE?$AA@ @ 0x003E1A9C
// match: ??_C@_07KLOAJOF@AUDIBLE?$AA@ @ 0x003E1AA4
// match: ??_C@_04ECGLBLOI@?9?9?9?9?$AA@ @ 0x003E1AAC
// match: ??_C@_05BCIKCELF@?$DO5000?$AA@ @ 0x003E1AB4
// match: ??_C@_0CF@PNNHGBLE@NUM?5?5DECODE?5?5L?9TIME?5?5PENDING?5?5A?9@ @ 0x003E1ABC
// match: ??_C@_09OFEECKMB@RECEIVED?3?$AA@ @ 0x003E1AE4
// match: ??_C@_07CGOLGDBM@?$CI?$CFd?0?$CFd?$CJ?$AA@ @ 0x003E1AF0
// match: ??_C@_0M@BHCJNJLP@DISPATCHED?3?$AA@ @ 0x003E1AF8
// match: ??_C@_0DG@JNLPEGLC@PACKETS?5PENDING?5DISPATCH?5?5?5?5?3?55?5@ @ 0x003E1B04
// match: ??_C@_0DC@NMAIEHPL@PACKETS?5PENDING?5DISPATCH?5?5?5?5?3?54?5@ @ 0x003E1B3C
// match: ??_C@_0CO@NPMFJPEE@PACKETS?5PENDING?5DISPATCH?5?5?5?5?3?53?5@ @ 0x003E1B70
// match: ??_C@_0CK@PEIJNNGO@PACKETS?5PENDING?5DISPATCH?5?5?5?5?3?52?5@ @ 0x003E1BA0
// match: ??_C@_0CG@LEDJKKCM@PACKETS?5PENDING?5DISPATCH?5?5?5?5?3?51?5@ @ 0x003E1BCC
// match: ??_C@_0CA@NLLFDGLE@PACKETS?5PENDING?5DISPATCH?5?5?5?5?3?50?$AA@ @ 0x003E1BF4
// match: ??_C@_0CC@OJPOOKFG@SINCE?5LAST?5NETWORK?5DISPATCH?5?3?5?$CF5@ @ 0x003E1C14
// match: ??_C@_0CE@HKGNKBIE@SINCE?5LAST?5NETWORK?5DISPATCH?5?3?5?$DO5@ @ 0x003E1C38
// match: ??_C@_0BK@HBEMBIBH@SINCE?5LAST?5DISPATCH?5?3?5?$CF5d?$AA@ @ 0x003E1C5C
// match: ??_C@_0BM@MALMNEEC@SINCE?5LAST?5DISPATCH?5?3?5?$DO5000?$AA@ @ 0x003E1C78
// match: ??_C@_0BK@EOOJBNJG@SINCE?5LAST?5DECODE?5?5?5?3?5?$CF5d?$AA@ @ 0x003E1C94
// match: ??_C@_0BM@JCEOLGGC@SINCE?5LAST?5DECODE?5?5?5?3?5?$DO5000?$AA@ @ 0x003E1CB0
// match: ??_C@_0BF@OLMCDHA@MISSING?5PACKETS?3?5?$CF5d?$AA@ @ 0x003E1CCC
// match: ??_C@_0BK@COEKDBJO@PLAYBACK?5BYTES?5REMNG?3?5?$CF5d?$AA@ @ 0x003E1CE4
// match: ??_C@_0BK@KCNPNDLH@PLAYBACK?5OFFSET?5?5?5?5?5?3?5?$CF5d?$AA@ @ 0x003E1D00
// match: ??_C@_0BK@FBPEFJDH@DECODE?5DEST?5OFFSET?5?5?3?5?$CF5d?$AA@ @ 0x003E1D1C
// match: ??_C@_0BK@FGIGHCCF@PENDING?5PLAYBACK?5?5?5?5?3?5?$CF5d?$AA@ @ 0x003E1D38
// match: ??_C@_0BK@NMHNEPDG@PENDING?5DISPATCH?5?5?5?5?3?5?$CF5d?$AA@ @ 0x003E1D54
// match: ??_C@_0BK@LNJJDPGH@PENDING?5ENCODE?5?5?5?5?5?5?3?5?$CF5d?$AA@ @ 0x003E1D70
// match: ??_C@_0BK@FBNGJFHJ@ViewPos?3?5?$CF?40f?0?5?$CF?40f?0?5?$CF?40f?$AA@ @ 0x003E1D8C
// match: ??_C@_0DH@JBHJGNAE@Total?5?5?5?5?5?5?5?5?5?5n?3?$CFd?1?$CFd?5g?3?$CFd?1?$CFd?5t@ @ 0x003E1DA8
// match: ??_C@_0BI@IILGOAAE@?5?5Allies?3?$CFd?5?5Germans?3?$CFd?$AA@ @ 0x003E1DE0
// match: ??_C@_0BO@MFIIGMJA@?$CF02d?$CJ?5?$CFc?$CFc?5p?3?$CF02?43f?5k?3?$CFd?5d?3?$CFd?$AA@ @ 0x003E1DF8
// match: __ehhandler$?sub_1B00F0@type_4F84B8@@QAEXXZ>1>8 @ 0x0041EDD8
// match: __ehhandler$?sub_1B00F0@type_4F84B8@@QAEXXZ>1 @ 0x0041EDE0
// match: .CRT$XCU+0 @ 0x004271E0

// match: _$E2 @ 0x0030C220
// match: _$E3 @ 0x0030EAA0

// How many lines show for each setting of unk_00.

// match: ??0type_4F84B8@@QAE@XZ @ 0x001AFF40
type_4F84B8::type_4F84B8()
{
    RwUInt32 i;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_34F4)
    {
    }
    dword_4F84B8 = this;
    unk_34F4 = 0;
    memset(&unk_3498, 0, sizeof(unk_3498));
    for (i = 0; i < 16; i++)
    {
        memset(&unk_2F18[i], 0, sizeof(unk_2F18[i]));
        unk_2F18[i].unk_54 = 0;
    }
    unk_04 = 1;
    unk_00 = 1;
    for (i = 0; i < 3; i++)
    {
        unk_08[i] = 0;
        unk_14[i] = 0;
        unk_20[i] = 0;
    }
    unk_34F0 = false;
    unk_34F1 = 0;
    unk_34F8 = 1;
    unk_34FC = 0;
    unk_3500 = 0;
    unk_3504 = 0;
}

// match: ??1type_4F84B8@@QAE@XZ @ 0x001B0070
type_4F84B8::~type_4F84B8()
{
    dword_4F84B8 = 0;
}

// match: ?sub_1B0090@type_4F84B8@@QAEXPAUtype_4F8054@@@Z @ 0x001B0090
void type_4F84B8::sub_1B0090(type_4F8054 *arg_0)
{
    unk_34F4 = arg_0;
}

// match: ?sub_1B00B0@type_4F84B8@@QAEXXZ @ 0x001B00B0
void type_4F84B8::sub_1B00B0()
{
    // Unused locals; their names state their slots (docs/toolchain.md).
    RwInt32 lcl_8;
    bool l1 = false;
    bool fp_2 = false;
    bool loc3 = false;
    bool slot_4 = false;

    if (unk_34F8)
    {
        unk_34F8 = 0;
    }
}

// The debug display, returning at once in this build: the log's lines
// in the chosen channel; with a network game, each player's traffic (its
// running averages in unk_2F18) with its latency, kills and deaths, the
// totals (averaged in unk_3498) and the view position; and with unk_34F1
// set, the voice chat's state.
// match: ?sub_1B00F0@type_4F84B8@@QAEXXZ @ 0x001B00F0
// match: __ehhandler$?sub_1B00F0@type_4F84B8@@QAEXXZ-0x8 @ 0x00302C00
// match: __ehhandler$?sub_1B00F0@type_4F84B8@@QAEXXZ @ 0x00302C08
void type_4F84B8::sub_1B00F0()
{
    // The locals' names state their slots (docs/toolchain.md).
    RwReal *frm_1B4;
    RwUInt32 frm_1B0;
    RwReal stk_1AC;
    type_1D02A0 *local_1A8;
    RwUInt32 x1A4;
    RwUInt32 bp_1A0;
    RwInt32 var198;
    RwUInt32 t194[10];
    RwUInt32 slot_16C;
    RwReal z168;
    RwChar frm_164[256];
    type_4F8054_B0 *y5C;
    RwUInt32 slot_58;
    cTimeKeeper *frm_54;
    RwUInt32 s50[10];
    type_1D02A0 *q28;
    RwUInt32 ebp_14;
    RwUInt32 lv_10;

    if (!unk_34F4)
    {
    }
    if (!unk_34F4)
    {
    }
    return;
    for (ebp_14 = 0; ebp_14 < dword_3E1A60[unk_00] && ebp_14 < unk_14[unk_04]; ebp_14++)
    {
        x1A4 = (ebp_14 + unk_20[unk_04]) % 50;
        switch (unk_00)
        {
        case 0:
        case 1:
            sub_16BB00(unk_2C[unk_04][x1A4], 300, ebp_14 * 15 + 10);
            break;
        case 2:
            sub_16BB00(unk_2C[unk_04][x1A4], 10, ebp_14 * 15 + 10);
            break;
        }
    }
    if (!unk_34F4)
    {
        sub_16BBA0();
        return;
    }
    memset(s50, 0, sizeof(s50));
    y5C = unk_34F4->unk_B0;
    if (!unk_34F4->get_unk_B8() && y5C->get_unk_310() != 7)
    {
        sub_16BBA0();
        return;
    }
    if (!unk_34F4->get_unk_04() || unk_34F4->get_unk_04() == 3)
        return;
    frm_54 = unk_34F4->unk_B4;
    if (!unk_34F4)
    {
    }
    type_1DDE20_mask var_19C = y5C->unk_0C;
    var198 = y5C->sub_1CFF90();
    std::vector<RwUInt32> frm_24;
    unk_4F7EB8.unk_04.sub_1B3480(frm_24);
    for (slot_58 = 0; slot_58 < frm_24.size(); slot_58++)
    {
        ebp_14 = frm_24[slot_58];
        local_1A8 = &unk_34F4->get_unk_AC()->unk_4C4;
        if (var198 != ebp_14 && local_1A8->unk_50[ebp_14])
        {
            t194[0] = local_1A8->unk_D0[ebp_14];
            t194[1] = local_1A8->unk_1D0[ebp_14];
            t194[2] = local_1A8->unk_110[ebp_14];
            t194[3] = local_1A8->unk_210[ebp_14];
            t194[4] = local_1A8->unk_150[ebp_14];
            t194[5] = local_1A8->unk_250[ebp_14];
            t194[6] = local_1A8->unk_190[ebp_14];
            t194[7] = local_1A8->unk_290[ebp_14];
            t194[8] = t194[0] + t194[2] + t194[4] + t194[6];
            t194[9] = t194[1] + t194[3] + t194[5] + t194[7];
            for (bp_1A0 = 0; bp_1A0 < 10; bp_1A0++)
                s50[bp_1A0] += t194[bp_1A0];
            frm_1B0 = sub_1CCA10().since(local_1A8->unk_90[ebp_14]).get_unk_00();
            stk_1AC = (RwReal)(frm_1B0 - unk_2F18[ebp_14].unk_50) / 1000.0f;
            if (unk_2F18[ebp_14].unk_54)
            {
                for (bp_1A0 = 0; bp_1A0 < 10; bp_1A0++)
                    unk_2F18[ebp_14].unk_28[bp_1A0] = unk_2F18[ebp_14].unk_28[bp_1A0] * 0.99f
                        + (RwReal)(t194[bp_1A0] - unk_2F18[ebp_14].unk_00[bp_1A0]) / stk_1AC * 0.01f;
            }
            else
            {
                for (bp_1A0 = 0; bp_1A0 < 10; bp_1A0++)
                    unk_2F18[ebp_14].unk_28[bp_1A0] = (RwReal)t194[bp_1A0] * 1000.0f / (RwReal)frm_1B0;
                unk_2F18[ebp_14].unk_54 = 1;
            }
            memcpy(unk_2F18[ebp_14].unk_00, t194, sizeof(t194));
            unk_2F18[ebp_14].unk_50 = frm_1B0;
            sprintf(frm_164, "%02d) %c%c p:%02.3f k:%d d:%d", ebp_14, (RwChar)(var_19C.bit(ebp_14) ? 'F' : 'E'),
                    ebp_14 == var198 ? '*' : ' ', (RwReal)frm_54->get_unk_61C(ebp_14).get_unk_00() / 1000.0f,
                    unk_4F7EB8.unk_04.sub_1B3380(ebp_14), unk_4F7EB8.unk_04.sub_1B33A0(ebp_14));
            if (slot_58 == 15)
            {
                sprintf(&frm_164[strlen(frm_164)], "  Allies:%d  Germans:%d", unk_4F7EB8.unk_04.sub_1B33C0(2),
                        unk_4F7EB8.unk_04.sub_1B33C0(4));
            }
        }
        else
        {
            unk_2F18[ebp_14].unk_54 = 0;
            sprintf(frm_164, "%02d) %c%c p:%02.3f k:%d d:%d", ebp_14, (RwChar)(var_19C.bit(ebp_14) ? 'F' : 'E'),
                    ebp_14 == var198 ? '*' : ' ', (RwReal)frm_54->get_unk_61C(ebp_14).get_unk_00() / 1000.0f,
                    unk_4F7EB8.unk_04.sub_1B3380(ebp_14), unk_4F7EB8.unk_04.sub_1B33A0(ebp_14));
            if (slot_58 == 15)
            {
                sprintf(&frm_164[strlen(frm_164)], "  Allies:%d  Germans:%d", unk_4F7EB8.unk_04.sub_1B33C0(2),
                        unk_4F7EB8.unk_04.sub_1B33C0(4));
            }
            for (bp_1A0 = 0; bp_1A0 < 10; bp_1A0++)
                s50[bp_1A0] += unk_2F18[ebp_14].unk_00[bp_1A0];
        }
        show(frm_164, 0, slot_58 * 15 + 150);
    }
    q28 = &unk_34F4->get_unk_AC()->unk_4C4;
    slot_16C = sub_1CCA10().since(q28->unk_90[ebp_14]).get_unk_00();
    z168 = (RwReal)(slot_16C - unk_3498.unk_50) / 1000.0f;
    for (bp_1A0 = 0; bp_1A0 < 10; bp_1A0++)
        unk_3498.unk_28[bp_1A0] = unk_3498.unk_28[bp_1A0] * 0.99f
            + (RwReal)(s50[bp_1A0] - unk_3498.unk_00[bp_1A0]) / z168 * 0.01f;
    memcpy(unk_3498.unk_00, s50, sizeof(s50));
    unk_3498.unk_50 = slot_16C;
    sprintf(frm_164, "Total          n:%d/%d g:%d/%d t:%d/%d h:%d/%d o:%d/%d", (RwInt32)(unk_3498.unk_28[0] / 8.0f),
            (RwInt32)(unk_3498.unk_28[1] / 8.0f), (RwInt32)(unk_3498.unk_28[2] / 8.0f),
            (RwInt32)(unk_3498.unk_28[3] / 8.0f), (RwInt32)(unk_3498.unk_28[4] / 8.0f),
            (RwInt32)(unk_3498.unk_28[5] / 8.0f), (RwInt32)(unk_3498.unk_28[6] / 8.0f),
            (RwInt32)(unk_3498.unk_28[7] / 8.0f), (RwInt32)(unk_3498.unk_28[8] / 8.0f),
            (RwInt32)(unk_3498.unk_28[9] / 8.0f));
    show(frm_164, 0, 405);
    if (unk_4F7EB8.sub_1AECA0(unk_4F7EB8.sub_1AEC70(), 0))
    {
        frm_1B4 = unk_4F7EB8.sub_1AECA0(unk_4F7EB8.sub_1AEC70(), 0)->vf_0C4();
        sprintf(frm_164, "ViewPos: %.0f, %.0f, %.0f", frm_1B4[0], frm_1B4[1], frm_1B4[2]);
        show(frm_164, 10, 10);
    }
    if (unk_34F1)
    {
        type_1C6900 lv_3EC;
        RwChar var304[32];
        RwChar ebp_2E4[32];
        type_1DF990 t2C4;

        type_1DDE20_mask var_308 = type_4F8054::get()->get_unk_B0_checked()->others_checked();
        get_dword_4F8180()->sub_1C6900(&lv_3EC, sub_1CCA10());
        get_dword_4F8180()->unk_14.sub_1DF990(&t2C4, sub_1CCA10());
        lv_10 = 50;
        sprintf(frm_164, "PENDING ENCODE      : %5d", lv_3EC.unk_00);
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        sprintf(frm_164, "PENDING DISPATCH    : %5d", lv_3EC.unk_04);
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        sprintf(frm_164, "PENDING PLAYBACK    : %5d", lv_3EC.unk_48);
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        sprintf(frm_164, "DECODE DEST OFFSET  : %5d", lv_3EC.unk_D4);
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        sprintf(frm_164, "PLAYBACK OFFSET     : %5d", lv_3EC.unk_D8);
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        sprintf(frm_164, "PLAYBACK BYTES REMNG: %5d", lv_3EC.unk_DC);
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        sprintf(frm_164, "MISSING PACKETS: %5d", t2C4.unk_108);
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        if (lv_3EC.unk_4C.get_unk_00() > 5000)
            sprintf(frm_164, "SINCE LAST DECODE   : >5000");
        else
            sprintf(frm_164, "SINCE LAST DECODE   : %5d", lv_3EC.unk_4C.get_unk_00());
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        if (lv_3EC.unk_50.get_unk_00() > 5000)
            sprintf(frm_164, "SINCE LAST DISPATCH : >5000");
        else
            sprintf(frm_164, "SINCE LAST DISPATCH : %5d", lv_3EC.unk_50.get_unk_00());
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        if (t2C4.unk_D8.get_unk_00() > 5000)
            sprintf(frm_164, "SINCE LAST NETWORK DISPATCH : >5000");
        else
            sprintf(frm_164, "SINCE LAST NETWORK DISPATCH : %5d", t2C4.unk_D8.get_unk_00());
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        switch (t2C4.unk_40)
        {
        case 0:
            sprintf(frm_164, "PACKETS PENDING DISPATCH    : 0");
            break;
        case 1:
            sprintf(frm_164, "PACKETS PENDING DISPATCH    : 1 (%2d)", t2C4.unk_44[0]);
            break;
        case 2:
            sprintf(frm_164, "PACKETS PENDING DISPATCH    : 2 (%2d %2d)", t2C4.unk_44[0], t2C4.unk_44[1]);
            break;
        case 3:
            sprintf(frm_164, "PACKETS PENDING DISPATCH    : 3 (%2d %2d %2d)", t2C4.unk_44[0], t2C4.unk_44[1],
                    t2C4.unk_44[2]);
            break;
        case 4:
            sprintf(frm_164, "PACKETS PENDING DISPATCH    : 4 (%2d %2d %2d %2d)", t2C4.unk_44[0], t2C4.unk_44[1],
                    t2C4.unk_44[2], t2C4.unk_44[3]);
            break;
        case 5:
            sprintf(frm_164, "PACKETS PENDING DISPATCH    : 5 (%2d %2d %2d %2d %2d)", t2C4.unk_44[0],
                    t2C4.unk_44[1], t2C4.unk_44[2], t2C4.unk_44[3], t2C4.unk_44[4]);
            break;
        }
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        sprintf(frm_164, "DISPATCHED:");
        bp_1A0 = t2C4.unk_105 + 1;
        bp_1A0 = bp_1A0 < 10 ? bp_1A0 : 0;
        for (ebp_14 = 0; ebp_14 < 10; ebp_14++)
        {
            if (t2C4.unk_F0[bp_1A0] != 16 && t2C4.unk_FA[bp_1A0] != 16)
            {
                sprintf(ebp_2E4, "(%d,%d)", t2C4.unk_F0[bp_1A0], t2C4.unk_FA[bp_1A0]);
                strcat(frm_164, ebp_2E4);
            }
            bp_1A0++;
            bp_1A0 = bp_1A0 < 10 ? bp_1A0 : 0;
        }
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        sprintf(frm_164, "RECEIVED:");
        bp_1A0 = t2C4.unk_104 + 1;
        bp_1A0 = bp_1A0 < 10 ? bp_1A0 : 0;
        for (ebp_14 = 0; ebp_14 < 10; ebp_14++)
        {
            if (t2C4.unk_DC[bp_1A0] != 16 && t2C4.unk_E6[bp_1A0] != 16)
            {
                sprintf(ebp_2E4, "(%d,%d)", t2C4.unk_DC[bp_1A0], t2C4.unk_E6[bp_1A0]);
                strcat(frm_164, ebp_2E4);
            }
            bp_1A0++;
            bp_1A0 = bp_1A0 < 10 ? bp_1A0 : 0;
        }
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        lv_10 += 15;
        sprintf(frm_164, "NUM  DECODE  L-TIME  PENDING  A-TIME");
        sub_16BB00(frm_164, 50, lv_10);
        lv_10 += 15;
        for (ebp_14 = 0; ebp_14 < 16; ebp_14++)
        {
            if (var_308.bit(ebp_14))
            {
                if (lv_3EC.unk_54[ebp_14].get_unk_00() > 5000)
                    sprintf(ebp_2E4, ">5000");
                else
                    sprintf(ebp_2E4, "%d", lv_3EC.unk_54[ebp_14].get_unk_00());
                if (t2C4.unk_58[ebp_14])
                    sprintf(var304, "%d", t2C4.unk_98[ebp_14].get_unk_00());
                else
                    sprintf(var304, "----");
                sprintf(frm_164, "%3d  %6d  %6s  %7d  %6s  %6s  %7s", ebp_14, lv_3EC.unk_08[ebp_14], ebp_2E4,
                        t2C4.unk_00[ebp_14], var304, (lv_3EC.unk_94[ebp_14] & 1) ? "ACTIVE" : "",
                        (lv_3EC.unk_94[ebp_14] & 2) ? "AUDIBLE" : "");
                sub_16BB00(frm_164, 50, lv_10);
                lv_10 += 15;
            }
        }
    }
    sub_16BBA0();
}

// Adds the line arg_0 to channel arg_4 (and to channel 1 as well), keeping
// the view on the newest lines.
// match: ?sub_1B1780@type_4F84B8@@QAEXPADH@Z @ 0x001B1780
void type_4F84B8::sub_1B1780(RwChar *arg_0, RwInt32 arg_4)
{
    RwUInt32 line;

    if (arg_4 != 1)
    {
        sub_1B1780(arg_0, 1);
    }
    if (unk_14[arg_4] == 50)
    {
        if (unk_20[arg_4] == unk_08[arg_4])
        {
            unk_20[arg_4] = (unk_20[arg_4] + 1) % 50;
        }
        unk_08[arg_4] = (unk_08[arg_4] + 1) % 50;
    }
    else
    {
        unk_14[arg_4]++;
    }
    line = (unk_08[arg_4] + unk_14[arg_4] - 1) % 50;
    strncpy(unk_2C[arg_4][line], arg_0, 80);
    line = (line + 49) % 50;
    if (line == (unk_20[arg_4] + dword_3E1A60[unk_00] - 1) % 50)
    {
        unk_20[arg_4] = (unk_20[arg_4] + 1) % 50;
    }
}

// match: ?sub_1B18D0@@YAPAUtype_4F84B8@@XZ @ 0x001B18D0
type_4F84B8 *sub_1B18D0()
{
    return dword_4F84B8;
}
