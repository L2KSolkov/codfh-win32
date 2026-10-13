// The script VM (types/scriptvm.h): its set-up (sub_67B10), image loading
// (sub_67E00, sub_67E30 and the sorts sub_68190 and sub_68250), the run loop
// (sub_68310) and the opcode handlers. The file's original name is not
// recovered (M1), so it is named for its start address.

#include <stdlib.h>
#include <string.h>

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_44350.h"
#include "types/type_67620.h"
#include "types/type_3D2E7C.h"
#include "types/type_3D3548.h"
#include "types/type_42AF0.h"
#include "rw/rprandom.h"
#include "types/scriptvm.h"
#include "types/alfamessman.h"
#include "types/alfaobject.h"
#include "game/objectives.h"
#include <stdio.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x00428A34
const RwChar *Str2[5] = {
    "AllBurstsFinished",
    "SingleBurstFinished",
    "AttackPauseFinished",
    "OutOfAmmo",
    "Tick",
};
// 0x004491C0
void (*dword_4491C0[49])();
// 0x00449284
RwInt32 dword_449284;
// 0x00449288
RwInt32 dword_449288;
// 0x0044928C
RwInt32 dword_44928C;
// 0x00449290
void **dword_449290;
// 0x00449294
RwInt32 dword_449294;
// 0x00449298
RwUInt8 byte_449298[0x10];
// 0x004492A8
RwInt32 dword_4492A8;
// 0x004492AC
RwInt32 dword_4492AC;
// 0x004492B0
RwInt32 dword_4492B0;
// 0x004492B4
RwChar String[0x20];
// 0x004492D4
RwInt32 dword_4492D4;
// 0x004492D8
RwUInt8 byte_4492D8;
// 0x004492DC
RwChar *dword_4492DC;
// 0x004492E0
RwInt32 dword_4492E0;
// 0x004492E4
type_44350 *Base;
// 0x004492E8
RwInt32 NumOfElements;
// 0x004492EC
type_4492EC *dword_4492EC;
// 0x004492F0
RwInt32 dword_4492F0;
// 0x004492F4
type_42E00_00 *dword_4492F4;
// 0x004492F8
RwInt32 dword_4492F8;
// 0x004492FC
type_4492FC *dword_4492FC;
// 0x00449300
RwInt32 dword_449300;
// 0x00449304
RwInt32 dword_449304;
// 0x00449308
type_449308 *dword_449308;
// 0x0044930C
RwUInt8 byte_44930C;
// 0x00449310
RwInt32 dword_449310;
// 0x00449314
RwUInt8 byte_449314;
// 0x00449315
RwUInt8 byte_449315;
// 0x00449318
RwInt32 *dword_449318;
// 0x0044931C
RwInt32 *dword_44931C;
// 0x00449320
RwInt32 *dword_449320;
// 0x00449324
RwUInt8 byte_449324;
// 0x00449325
RwUInt8 byte_449325;
// 0x00449328
type_67620 *dword_449328;
// (Defined after the data: VC7.1 emits a unit's data definitions in reverse order, and
// the image has this constant before the table's texts.)
// 0x003D2788
extern const RwReal flt_3D2788 = 16.666666f;
// End of its data definitions.

// match: ?flt_3D2788@@3MB @ 0x003D2788




void sub_68190();
void sub_68250();
RwInt8 sub_6A7A0(RwInt8 arg_0, RwInt8 arg_4);
// The opcode handlers (below).
void sub_68450();
void sub_68470();
void sub_68530();
void sub_685F0();
void sub_686B0();
void sub_68780();
void sub_68810();
void sub_68840();
void sub_688D0();
void sub_68960();
void sub_68AD0();
void sub_68C40();
void sub_68D70();
void sub_68EA0();
void sub_68FD0();
void sub_69100();
void sub_69150();
void sub_691A0();
void sub_69200();
void sub_69250();
void sub_69270();
void sub_69320();
void sub_69330();
void sub_693A0();
void sub_69490();
void sub_69500();
void sub_69540();
void sub_695A0();
void sub_69620();
void sub_696D0();
void sub_69730();
void sub_69770();
void sub_698A0();
void sub_69930();
void sub_69A90();
void sub_69B70();
void sub_69BB0();
void sub_69C50();
void sub_69CF0();
void sub_69D50();
void sub_69DB0();
void sub_69F40();
void sub_69FB0();
void sub_6A080();
void sub_6A1A0();
void sub_6A4F0();
void sub_6A640();
void sub_6A6F0();

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BC@KANDKFPK@?$CIRelease?5Scripts?$CJ?$AA@ @ 0x003D27C0
// match: ??_C@_0FA@NPEBIMII@Could?5not?5play?5animation?4?5?5Look?5@ @ 0x003D27D8
// match: ??_C@_0DK@KKBKEGJ@ERROR?5Playing?5animation?5in?5scrip@ @ 0x003D2828
// match: ??_C@_0N@MGEHINJA@Line?5Changed?$AA@ @ 0x003D2864
// match: ??_C@_0M@HAEEKKJ@Anim?5Opcode?$AA@ @ 0x003D2874
// match: ??_C@_0CE@FDCOHDGC@Proximity?5Trigger?5at?5?$CF?41f?0?$CF?41f?0?$CF@ @ 0x003D2880
// match: ??_C@_06HBKBHOGJ@Engine?$AA@ @ 0x003D28A4
// match: ??_C@_0L@OAAHCNIF@?0?5Sender?3?5?$AA@ @ 0x003D28AC
// match: ??_C@_0BA@FJGPIPLE@Trigger?5Machine?$AA@ @ 0x003D28B8
// match: ??_C@_0M@FGPAADPF@Task?5Script?$AA@ @ 0x003D28C8
// match: ??_C@_0O@ODMGCCLJ@State?5Machine?$AA@ @ 0x003D28D4
// match: ??_C@_01CLKCMJKC@?5?$AA@ @ 0x003D28E4
// match: ??_C@_0BM@LPNJONB@Trigger?5at?5?$CF?41f?0?5?$CF?41f?0?5?$CF?41f?$AA@ @ 0x003D28E8
// match: ??_C@_03DHGAOEOO@?$CFi?0?$AA@ @ 0x003D2904
// match: ??_C@_05LEHMOKNM@?5ID?3?5?$AA@ @ 0x003D2908
// match: ??_C@_0L@BEHLKGD@Reciever?3?5?$AA@ @ 0x003D2910
// match: ??_C@_02IKAHHCAI@?$CFi?$AA@ @ 0x003D291C
// match: ??_C@_0M@CILBIJGO@MessageID?3?5?$AA@ @ 0x003D2920
// match: ??_C@_02KEGNLNML@?0?5?$AA@ @ 0x003D292C
// match: ??_C@_0CD@BLJBBAHG@?$CFs?$CI?$CFd?$CJ?3?5?$CFs?5ID?3?5?$CFd?0?5?$CFs?5at?5tick?3?5?$CF@ @ 0x003D2930
// match: ??_C@_0BN@JJFCNNBD@?$CFs?5?9?5ID?3?5?$CFd?0?5?$CFs?5at?5tick?3?5?$CFd?6?$AA@ @ 0x003D2954
// match: ??_C@_0CL@DKEMGEKG@?$CFs?$CI?$CFd?$CJ?3?5?$CFs?5Name?3?5?$CFs?0?5ID?3?5?$CFd?5?$CFs?5a@ @ 0x003D2974
// match: ??_C@_0CF@FDNHLLNK@?$CFs?5?9?5Name?3?5?$CFs?0?5ID?3?5?$CFd?5?$CFs?5at?5tick@ @ 0x003D29A0
// match: ??_C@_0BE@LBCEPPHE@Unknown?5Alfa?5Object?$AA@ @ 0x003D29C8
// match: ??_C@_0M@DJPEFIDI@Task?5Object?$AA@ @ 0x003D29DC
// match: ??_C@_0BF@INKHDFCC@State?5Machine?5Object?$AA@ @ 0x003D29E8
// match: ??_C@_0BD@LLHMDHGE@Performance?5Object?$AA@ @ 0x003D2A00
// match: ?Str2@@3PAPBDA @ 0x00428A34

// match: sub_67B10 @ 0x00067B10
// sp-match: sub_67B10 @ 0x0005A930

// Fills the opcode table and clears the VM's state.
void sub_67B10()
{
    dword_4491C0[0] = sub_68450;
    dword_4491C0[1] = sub_68470;
    dword_4491C0[2] = sub_68530;
    dword_4491C0[3] = sub_685F0;
    dword_4491C0[4] = sub_686B0;
    dword_4491C0[5] = sub_68780;
    dword_4491C0[6] = sub_68840;
    dword_4491C0[7] = sub_688D0;
    dword_4491C0[8] = sub_68960;
    dword_4491C0[9] = sub_68AD0;
    dword_4491C0[10] = sub_68C40;
    dword_4491C0[11] = sub_68D70;
    dword_4491C0[12] = sub_68EA0;
    dword_4491C0[13] = sub_68FD0;
    dword_4491C0[14] = sub_69100;
    dword_4491C0[15] = sub_69150;
    dword_4491C0[16] = sub_691A0;
    dword_4491C0[17] = sub_69200;
    dword_4491C0[18] = sub_69250;
    dword_4491C0[19] = sub_69270;
    dword_4491C0[20] = sub_69320;
    dword_4491C0[21] = sub_69330;
    dword_4491C0[38] = sub_68810;
    dword_4491C0[22] = sub_693A0;
    dword_4491C0[23] = sub_69490;
    dword_4491C0[24] = sub_69500;
    dword_4491C0[25] = sub_69540;
    dword_4491C0[26] = sub_695A0;
    dword_4491C0[27] = sub_69620;
    dword_4491C0[28] = sub_696D0;
    dword_4491C0[36] = sub_69730;
    dword_4491C0[39] = sub_69770;
    dword_4491C0[40] = sub_698A0;
    dword_4491C0[47] = sub_69930;
    dword_4491C0[37] = sub_69A90;
    dword_4491C0[34] = sub_69BB0;
    dword_4491C0[32] = sub_69C50;
    dword_4491C0[35] = sub_69CF0;
    dword_4491C0[33] = sub_69D50;
    dword_4491C0[29] = sub_69B70;
    dword_4491C0[31] = sub_69DB0;
    dword_4491C0[41] = sub_69F40;
    dword_4491C0[42] = sub_6A1A0;
    dword_4491C0[43] = sub_69FB0;
    dword_4491C0[44] = sub_6A080;
    dword_4491C0[45] = sub_6A4F0;
    dword_4491C0[46] = sub_6A640;
    dword_4491C0[48] = sub_6A6F0;
    dword_4492DC = 0;
    Base = 0;
    NumOfElements = 0;
    dword_4492EC = 0;
    dword_4492F0 = 0;
    dword_4492F4 = 0;
    dword_4492F8 = 0;
    dword_449284 = 0;
    dword_4492AC = 0;
    dword_449288 = (RwInt32)"(Release Scripts)";
    dword_449290 = 0;
    dword_4492D4 = 0;
    dword_44928C = 0;
    dword_4492A8 = 0;
    dword_449294 = 0;
    dword_4492B0 = 0;
    String[0] = 0;
    byte_44930C = 0;
    dword_449310 = 0;
    byte_449314 = 0;
    byte_449315 = 0;
    dword_4492E0 = 0;
    dword_449320 = 0;
    dword_449318 = 0;
    dword_44931C = 0;
    byte_449324 = 0;
    byte_4492D8 = 1;
}

// match: sub_67E00 @ 0x00067E00
// sp-match: sub_67E00 @ 0x00057F60
// Frees the loaded image.
void sub_67E00()
{
    if (dword_4492DC != 0)
        sub_72B80(dword_4492DC);
    byte_4492D8 = 0;
}

// (SCRIPT_CHECK_SLOTS, type_44350.h's empty inline, kept out of line: the image's one
// empty body, which the empty functions single player calls fold into)
// sp-match: ?SCRIPT_CHECK_SLOTS@@YAXXZ @ 0x0005A260

// match: sub_67E30 @ 0x00067E30
// sp-match: sub_67E30 @ 0x0005A270
// Loads the image arg_0 (freeing the last): turns its offsets into
// pointers, binds its commands by name and sorts its tables.
void sub_67E30(RwChar *arg_0)
{
    type_4492DC_04 *local_8;
    RwInt32 var_4;

    if (dword_4492DC != 0)
        sub_72B80(dword_4492DC);
    dword_4492DC = arg_0;
    sub_72B30(dword_4492DC);
    local_8 = (type_4492DC_04 *)(dword_4492DC + 4);
    sub_72B60(&local_8->unk_14, local_8);
    sub_72B60(&local_8->unk_18, local_8);
    sub_72B60(&local_8->unk_1C, local_8);
    sub_72B60(&local_8->unk_20, local_8);
    sub_72B60(&local_8->unk_24, local_8);
    sub_72B60(&local_8->unk_2C, local_8);
    NumOfElements = local_8->unk_00;
    dword_4492F0 = local_8->unk_04;
    dword_4492F8 = local_8->unk_08;
    dword_449300 = local_8->unk_0C;
    dword_449304 = local_8->unk_10;
    dword_4492D4 = local_8->unk_28;
    Base = (type_44350 *)local_8->unk_14;
    dword_4492EC = (type_4492EC *)local_8->unk_18;
    dword_4492F4 = (type_42E00_00 *)local_8->unk_1C;
    dword_4492FC = (type_4492FC *)local_8->unk_20;
    dword_449308 = local_8->unk_24;
    dword_449290 = (void **)local_8->unk_2C;
    for (var_4 = 0; var_4 < NumOfElements; var_4++) {
        sub_72B60(&Base[var_4], Base);
        sub_72B60(&Base[var_4].unk_1C, Base);
    }
    for (var_4 = 0; var_4 < dword_4492F0; var_4++)
        sub_72B60(&dword_4492EC[var_4], dword_4492EC);
    for (var_4 = 0; var_4 < dword_4492F8; var_4++) {
        if (dword_4492F4[var_4].unk_00 != 0)
            sub_72B60(&dword_4492F4[var_4], dword_4492F4);
    }
    for (var_4 = 0; var_4 < dword_449300; var_4++) {
        if (dword_4492FC[var_4].unk_00 != 0)
            sub_72B60(&dword_4492FC[var_4], dword_4492FC);
    }
    for (var_4 = 0; var_4 < dword_4492D4; var_4++)
        sub_72B60(&dword_449290[var_4], dword_449290);
    for (var_4 = 0; var_4 < NumOfElements; var_4++)
        Base[var_4].unk_18 = sub_441B0(Base[var_4].unk_00);
    if (NumOfElements > 0)
        qsort(Base, NumOfElements, sizeof(type_44350), CompareFunction);
    if (dword_4492F0 > 0)
        qsort(dword_4492EC, dword_4492F0, sizeof(type_4492EC), CompareFunction);
    if (dword_4492F8 > 0)
        sub_68190();
    if (dword_449300 > 0)
        sub_68250();
}

// match: sub_68190 @ 0x00068190
// sp-match: sub_68190 @ 0x00057F80
// Puts each of dword_4492F4's entries at the index its unk_04 gives.
void sub_68190()
{
    type_42E00_00 var_1C;
    RwInt32 v8;
    RwInt32 var_4;

    for (var_4 = 0; var_4 < dword_4492F8; var_4++) {
        v8 = dword_4492F4[var_4].unk_04;
        if (v8 != var_4 && v8 != -1) {
            memcpy(&var_1C, &dword_4492F4[v8], sizeof(type_42E00_00));
            memcpy(&dword_4492F4[v8], &dword_4492F4[var_4], sizeof(type_42E00_00));
            memcpy(&dword_4492F4[var_4], &var_1C, sizeof(type_42E00_00));
            var_4--;
        }
    }
}

// match: sub_68250 @ 0x00068250
// sp-match: sub_68250 @ 0x00058040
// Likewise for dword_4492FC.
void sub_68250()
{
    type_4492FC loc18;
    RwInt32 v8;
    RwInt32 var_4;

    for (var_4 = 0; var_4 < dword_449300; var_4++) {
        v8 = dword_4492FC[var_4].unk_04;
        if (v8 != var_4 && v8 != -1) {
            memcpy(&loc18, &dword_4492FC[v8], sizeof(type_4492FC));
            memcpy(&dword_4492FC[v8], &dword_4492FC[var_4], sizeof(type_4492FC));
            memcpy(&dword_4492FC[var_4], &loc18, sizeof(type_4492FC));
            var_4--;
        }
    }
}

// match: sub_68310 @ 0x00068310
// sp-match: sub_68310 @ 0x0005A4F0
// Runs the script arg_0 until an opcode halts it, then stores its state
// back unless it ended; the VM's state is restored around it.
#ifdef CODFH_DRAW_TRIGGERS
// (port/src/debug/trigtools.cpp: the VM tab's snapshot of the script that halted last; the
// overlay draws between runs, when the VM's state is the idle one again)
void TrigWebVmSnapshot();
// (port/src/debug/scriptdbg.cpp: the script debugger's look before each instruction, while
// something needs it: a trace, the calls, breakpoints, a step)
extern RwBool g_bTrigScriptStep;
void TrigScriptStep();
#endif
void sub_68310(type_67620 *arg_0)
{
    type_67620 *stk_18;
    RwInt32 *l14;
    RwInt32 *var_10;
    RwUInt8 l9;
    RwInt32 v8;
    RwInt32 *var_4;

    l14 = dword_449320;
    var_4 = dword_449318;
    var_10 = dword_44931C;
    l9 = byte_449324;
    stk_18 = dword_449328;
    v8 = dword_4492E0;
    byte_449324 = 0;
    byte_449325 = 0;
    dword_449320 = arg_0->vf_000();
    dword_449318 = arg_0->vf_004();
    dword_44931C = arg_0->vf_008();
    dword_4492E0 = arg_0->vf_00C();
    dword_449328 = arg_0;
    while (byte_449324 == 0) {
#ifdef CODFH_DRAW_TRIGGERS
        if (g_bTrigScriptStep)
            TrigScriptStep();
#endif
        RwInt8 var_19 = (RwInt8)(*dword_449320 & 0xFF);
        void (*local_20)() = dword_4491C0[var_19];
        local_20();
    }
#ifdef CODFH_DRAW_TRIGGERS
    TrigWebVmSnapshot();
#endif
    if (byte_449325 == 0) {
        arg_0->vf_018(dword_449320);
        arg_0->vf_01C(dword_449318);
        arg_0->vf_020(dword_44931C);
    }
    dword_449320 = l14;
    dword_449318 = var_4;
    dword_44931C = var_10;
    byte_449324 = l9;
    dword_449328 = stk_18;
    dword_4492E0 = v8;
}

// match: sub_68450 @ 0x00068450
// sp-match: sub_68450 @ 0x000580E0
// Opcode 0: nothing.
void sub_68450()
{
    dword_449320++;
}

// match: sub_68470 @ 0x00068470
// sp-match: sub_68470 @ 0x000580F0
// Opcode 1, add: pops one, and adds to the top by it, by the operand types (byte 1):
// 0 ints, 1 an int and a float, 2 a float and an int, 3 floats.
void sub_68470()
{
    type_449318 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
        var_4.unk_00 = dword_449318[-1] + dword_449318[0];
        break;
    case 1:
        var_4.unk_00_f = dword_449318[-1] + *(RwReal *)&dword_449318[0];
        break;
    case 2:
        var_4.unk_00_f = *(RwReal *)&dword_449318[-1] + dword_449318[0];
        break;
    case 3:
        var_4.unk_00_f = *(RwReal *)&dword_449318[-1] + *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4.unk_00;
    dword_449320++;
}

// match: sub_68530 @ 0x00068530
// sp-match: sub_68530 @ 0x00058160
// Opcode 2, subtract: pops one, and subtracts from the top by it, by the operand types (byte 1):
// 0 ints, 1 an int and a float, 2 a float and an int, 3 floats.
void sub_68530()
{
    type_449318 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
        var_4.unk_00 = dword_449318[-1] - dword_449318[0];
        break;
    case 1:
        var_4.unk_00_f = dword_449318[-1] - *(RwReal *)&dword_449318[0];
        break;
    case 2:
        var_4.unk_00_f = *(RwReal *)&dword_449318[-1] - dword_449318[0];
        break;
    case 3:
        var_4.unk_00_f = *(RwReal *)&dword_449318[-1] - *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4.unk_00;
    dword_449320++;
}

// match: sub_685F0 @ 0x000685F0
// sp-match: sub_685F0 @ 0x000581D0
// Opcode 3, multiply: pops one, and multiplies the top by it, by the operand types (byte 1):
// 0 ints, 1 an int and a float, 2 a float and an int, 3 floats.
void sub_685F0()
{
    type_449318 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
        var_4.unk_00 = dword_449318[-1] * dword_449318[0];
        break;
    case 1:
        var_4.unk_00_f = dword_449318[-1] * *(RwReal *)&dword_449318[0];
        break;
    case 2:
        var_4.unk_00_f = *(RwReal *)&dword_449318[-1] * dword_449318[0];
        break;
    case 3:
        var_4.unk_00_f = *(RwReal *)&dword_449318[-1] * *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4.unk_00;
    dword_449320++;
}

// match: sub_686B0 @ 0x000686B0
// sp-match: sub_686B0 @ 0x00058240
// Opcode 4, divide: pops one and divides the top by it, as the other
// arithmetic opcodes (0 when dividing by an int zero).
void sub_686B0()
{
    type_449318 var_4;

    dword_449318--;
    if (dword_449318[0] != 0) {
        switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
        case 0:
            var_4.unk_00 = dword_449318[-1] / dword_449318[0];
            break;
        case 1:
            var_4.unk_00_f = dword_449318[-1] / *(RwReal *)&dword_449318[0];
            break;
        case 2:
            var_4.unk_00_f = *(RwReal *)&dword_449318[-1] / dword_449318[0];
            break;
        case 3:
            var_4.unk_00_f = *(RwReal *)&dword_449318[-1] / *(RwReal *)&dword_449318[0];
            break;
        }
    } else
        var_4.unk_00 = 0;
    dword_449318[-1] = var_4.unk_00;
    dword_449320++;
}

// match: sub_68780 @ 0x00068780
// sp-match: sub_68780 @ 0x000582D0
// Opcode 5, push: pushes the count (byte 1) of words following the
// instruction, then moves the stack pointer by the operand (the high half)
// and skips the words.
void sub_68780()
{
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    for (local_8 = 0; local_8 < var_4; local_8++)
        dword_449318[local_8] = dword_449320[local_8 + 1];
    dword_449318 += (RwInt16)(*dword_449320 >> 16);
    dword_449320 += var_4 + 1;
}

// match: sub_68810 @ 0x00068810
// sp-match: sub_68810 @ 0x00058330
// Opcode 38, pop: drops the operand's count of words.
void sub_68810()
{
    dword_449318 -= (RwInt16)(*dword_449320 >> 16);
    dword_449320++;
}

// match: sub_68840 @ 0x00068840
// sp-match: sub_68840 @ 0x00058360
// Opcode 6, load: pushes the count (byte 1) of words from the frame at the
// operand.
void sub_68840()
{
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    for (local_8 = 0; local_8 < var_4; local_8++)
        dword_449318[local_8] = (dword_44931C + (RwInt16)(*dword_449320 >> 16))[local_8];
    dword_449318 += var_4;
    dword_449320++;
}

// match: sub_688D0 @ 0x000688D0
// sp-match: sub_688D0 @ 0x000583E0
// Opcode 7, store: pops the count (byte 1) of words into the frame at the
// operand.
void sub_688D0()
{
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    for (local_8 = 0; local_8 < var_4; local_8++)
        (dword_44931C + (RwInt16)(*dword_449320 >> 16))[local_8] = (dword_449318 - var_4)[local_8];
    dword_449318 -= var_4;
    dword_449320++;
}

// match: sub_68960 @ 0x00068960
// sp-match: sub_68960 @ 0x00058450
// Opcode 8, and: pops one and replaces the top with the result, by
// the operand types (byte 1): 0, 4, 5, 8 and 9 ints, 1 and 7 an int and a
// float, 2 and 6 a float and an int, 3 floats.
void sub_68960()
{
    RwInt32 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
    case 4:
    case 5:
    case 8:
    case 9:
        var_4 = dword_449318[-1] && dword_449318[0];
        break;
    case 1:
    case 7:
        var_4 = dword_449318[-1] && *(RwReal *)&dword_449318[0];
        break;
    case 2:
    case 6:
        var_4 = *(RwReal *)&dword_449318[-1] && dword_449318[0];
        break;
    case 3:
        var_4 = *(RwReal *)&dword_449318[-1] && *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_68AD0 @ 0x00068AD0
// sp-match: sub_68AD0 @ 0x00058560
// Opcode 9, or: pops one and replaces the top with the result, by
// the operand types (byte 1): 0, 4, 5, 8 and 9 ints, 1 and 7 an int and a
// float, 2 and 6 a float and an int, 3 floats.
void sub_68AD0()
{
    RwInt32 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
    case 4:
    case 5:
    case 8:
    case 9:
        var_4 = dword_449318[-1] || dword_449318[0];
        break;
    case 1:
    case 7:
        var_4 = dword_449318[-1] || *(RwReal *)&dword_449318[0];
        break;
    case 2:
    case 6:
        var_4 = *(RwReal *)&dword_449318[-1] || dword_449318[0];
        break;
    case 3:
        var_4 = *(RwReal *)&dword_449318[-1] || *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_68C40 @ 0x00068C40
// sp-match: sub_68C40 @ 0x00058660
// Opcode 10, less than: pops one and replaces the top with the result, by
// the operand types (byte 1): 0, 4, 5, 8 and 9 ints, 1 and 7 an int and a
// float, 2 and 6 a float and an int, 3 floats.
void sub_68C40()
{
    RwInt32 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
    case 4:
    case 5:
    case 8:
    case 9:
        var_4 = dword_449318[-1] < dword_449318[0];
        break;
    case 1:
    case 7:
        var_4 = dword_449318[-1] < *(RwReal *)&dword_449318[0];
        break;
    case 2:
    case 6:
        var_4 = *(RwReal *)&dword_449318[-1] < dword_449318[0];
        break;
    case 3:
        var_4 = *(RwReal *)&dword_449318[-1] < *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_68D70 @ 0x00068D70
// sp-match: sub_68D70 @ 0x00058720
// Opcode 11, greater than: pops one and replaces the top with the result, by
// the operand types (byte 1): 0, 4, 5, 8 and 9 ints, 1 and 7 an int and a
// float, 2 and 6 a float and an int, 3 floats.
void sub_68D70()
{
    RwInt32 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
    case 4:
    case 5:
    case 8:
    case 9:
        var_4 = dword_449318[-1] > dword_449318[0];
        break;
    case 1:
    case 7:
        var_4 = dword_449318[-1] > *(RwReal *)&dword_449318[0];
        break;
    case 2:
    case 6:
        var_4 = *(RwReal *)&dword_449318[-1] > dword_449318[0];
        break;
    case 3:
        var_4 = *(RwReal *)&dword_449318[-1] > *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_68EA0 @ 0x00068EA0
// sp-match: sub_68EA0 @ 0x000587E0
// Opcode 12, at most: pops one and replaces the top with the result, by
// the operand types (byte 1): 0, 4, 5, 8 and 9 ints, 1 and 7 an int and a
// float, 2 and 6 a float and an int, 3 floats.
void sub_68EA0()
{
    RwInt32 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
    case 4:
    case 5:
    case 8:
    case 9:
        var_4 = dword_449318[-1] <= dword_449318[0];
        break;
    case 1:
    case 7:
        var_4 = dword_449318[-1] <= *(RwReal *)&dword_449318[0];
        break;
    case 2:
    case 6:
        var_4 = *(RwReal *)&dword_449318[-1] <= dword_449318[0];
        break;
    case 3:
        var_4 = *(RwReal *)&dword_449318[-1] <= *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_68FD0 @ 0x00068FD0
// sp-match: sub_68FD0 @ 0x000588A0
// Opcode 13, at least: pops one and replaces the top with the result, by
// the operand types (byte 1): 0, 4, 5, 8 and 9 ints, 1 and 7 an int and a
// float, 2 and 6 a float and an int, 3 floats.
void sub_68FD0()
{
    RwInt32 var_4;

    dword_449318--;
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 0:
    case 4:
    case 5:
    case 8:
    case 9:
        var_4 = dword_449318[-1] >= dword_449318[0];
        break;
    case 1:
    case 7:
        var_4 = dword_449318[-1] >= *(RwReal *)&dword_449318[0];
        break;
    case 2:
    case 6:
        var_4 = *(RwReal *)&dword_449318[-1] >= dword_449318[0];
        break;
    case 3:
        var_4 = *(RwReal *)&dword_449318[-1] >= *(RwReal *)&dword_449318[0];
        break;
    }
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_69100 @ 0x00069100
// sp-match: sub_69100 @ 0x00058960
// Opcode 14, equal: pops one and replaces the top with whether they are
// equal (as ints).
void sub_69100()
{
    RwInt32 var_4;

    dword_449318--;
    var_4 = !(dword_449318[-1] - dword_449318[0]);
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_69150 @ 0x00069150
// sp-match: sub_69150 @ 0x00058990
// Opcode 15, not equal: likewise, whether they differ.
void sub_69150()
{
    RwInt32 var_4;

    dword_449318--;
    var_4 = dword_449318[-1] != dword_449318[0];
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_691A0 @ 0x000691A0
// sp-match: sub_691A0 @ 0x000589C0
// Opcode 16, convert: the top to a float (byte 1 is 1) or to an int (2).
void sub_691A0()
{
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 1:
        *(RwReal *)&dword_449318[-1] = (RwReal)dword_449318[-1];
        break;
    case 2:
        dword_449318[-1] = (RwInt32)*(RwReal *)&dword_449318[-1];
        break;
    }
    dword_449320++;
}

// match: sub_69200 @ 0x00069200
// sp-match: sub_69200 @ 0x00058A10
// Opcode 17, jump if false: pops one and, when it is 0, jumps by the
// operand.
void sub_69200()
{
    dword_449318--;
    if (dword_449318[0] == 0)
        dword_449320 += (RwInt16)(*dword_449320 >> 16);
    else
        dword_449320++;
}

// match: sub_69250 @ 0x00069250
// sp-match: sub_69250 @ 0x00058A40
// Opcode 18, jump: by the operand.
void sub_69250()
{
    dword_449320 += (RwInt16)(*dword_449320 >> 16);
}

// match: sub_69270 @ 0x00069270
// sp-match: sub_69270 @ 0x00058A60
// Opcode 19, switch: pops one and jumps by the offset paired with it in the
// (value, offset) pairs following the instruction (byte 1 counts them and
// the default's offset, which ends them).
void sub_69270()
{
    RwInt32 var_10;
    RwInt32 ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    ebp_C = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    dword_449318--;
    var_4 = ebp_C - 1;
    v8 = 1;
    for (var_10 = 0; var_10 < var_4; var_10++) {
        if (dword_449318[0] == dword_449320[v8]) {
            dword_449320 += dword_449320[v8 + 1];
            return;
        }
        v8 += 2;
    }
    dword_449320 += dword_449320[v8 + 1];
}

// match: sub_69320 @ 0x00069320
// sp-match: sub_69320 @ 0x00058AD0
// Opcode 20, halt.
void sub_69320()
{
    byte_449324 = 1;
}

// match: sub_69330 @ 0x00069330
// sp-match: sub_69330 @ 0x00058AE0
// Opcode 21, call: the command at the operand's index in Base, when bound,
// with the running script's handle.
void sub_69330()
{
    RwUInt32 local_8;
    RwInt32 var_4;

    var_4 = (RwInt16)(*dword_449320 >> 16);
    if (Base[var_4].unk_18 != 0) {
#ifdef CODFH_SP
        // shape: the handle as its struct through get_unk_04_h()'s return
        // temporary, loaded before &Base[var_4] is pushed (SP 0x58B01); the
        // command takes the handle by value.
        typedef void (*type_4276E0_fn_h)(type_439E78_00 arg_0, type_44350 *arg_4);
        ((type_4276E0_fn_h)Base[var_4].unk_18)(dword_449328->get_unk_04_h(), &Base[var_4]);
#else
        local_8 = dword_449328->unk_04;
        Base[var_4].unk_18(local_8, &Base[var_4]);
#endif
    }
    dword_449320++;
}

// match: sub_693A0 @ 0x000693A0
// sp-match: sub_693A0 @ 0x00058B20
// Opcode 22, play animation: while the top counts down from a positive
// value, plays the animation the count (byte 1) of words following the
// instruction describe and halts (for good when it cannot); at 0, pops it
// and skips the words.
void sub_693A0()
{
    bool ebp_9;
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    local_8 = (RwInt16)(*dword_449320 >> 16);
    if (dword_449318[-1] > 0) {
#ifdef CODFH_SP // single player's sub_6DE40 has no speed (SP 0x5C340 ends ret 0x10)
        ebp_9 = ((type_3D2CD0 *)dword_449328)->sub_6DE40(var_4 + 1, dword_449320 + 1, local_8, 1);
#else
        ebp_9 = ((type_3D2CD0 *)dword_449328)->sub_6DE40(var_4 + 1, dword_449320 + 1, local_8, 1, 1.0f);
#endif
        if (!ebp_9) {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
            sub_19A750("ERROR Playing animation in script file: %s, line no.: %d\n", dword_449288,
                       dword_449284);
            sub_19A750("Could not play animation.  Look above this messaage for possibly more "
                       "details.\n");
#endif
            ((type_3D2CD0 *)dword_449328)->sub_6DDF0(1, 0);
            ebp_9 = true;
        }
        dword_449318[-1]--;
        byte_449324 = ebp_9;
    } else {
        dword_449318--;
        dword_449320 += var_4 + 2;
    }
}

// match: sub_69490 @ 0x00069490
// sp-match: sub_69490 @ 0x00058BA0
// Opcode 23, start animation: plays the animation the count (byte 1) of
// words following the instruction describe, without halting.
void sub_69490()
{
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    local_8 = (RwInt16)(*dword_449320 >> 16);
#ifdef CODFH_SP // single player's sub_6DE40 has no speed (SP 0x5C340 ends ret 0x10)
    ((type_3D2CD0 *)dword_449328)->sub_6DE40(var_4, dword_449320 + 1, local_8, 0);
#else
    ((type_3D2CD0 *)dword_449328)->sub_6DE40(var_4, dword_449320 + 1, local_8, 0, 1.0f);
#endif
    dword_449320 += var_4 + 1;
}

// match: sub_69500 @ 0x00069500
// sp-match: sub_69500 @ 0x00058BE0
// Opcode 24, wait: the script waits (the operand) and the VM leaves it
// without storing its state.
void sub_69500()
{
    ((type_3D2CD0 *)dword_449328)->sub_6D380((RwInt16)(*dword_449320 >> 16), 0, 0, 0, 0, 0, 0, 0);
    byte_449325 = 1;
    byte_449324 = 1;
}

// match: sub_69540 @ 0x00069540
// sp-match: sub_69540 @ 0x00058C10
// Opcode 25: ends the script and halts (byte 1 is 1) or resumes it (2).
void sub_69540()
{
    switch ((RwInt8)((*dword_449320 & 0xFF00) >> 8)) {
    case 1:
        ((type_3D2CD0 *)dword_449328)->sub_6DDF0(1, 0);
        byte_449324 = 1;
        return;
    case 2:
        ((type_3D2CD0 *)dword_449328)->sub_6E390();
        break;
    }
    dword_449320++;
}

// match: sub_695A0 @ 0x000695A0
// sp-match: sub_695A0 @ 0x00058C50
// Opcode 26, event: pops one and jumps to the script's handler for it (by
// bytes 1 and 2).
void sub_695A0()
{
    RwInt32 *local_8;
    RwInt32 var_4;

    dword_449318--;
    var_4 = ((type_3D2CD0 *)dword_449328)->sub_6E490((RwInt8)((*dword_449320 & 0xFF00) >> 8),
                                    (RwInt8)((*dword_449320 & 0xFF0000) >> 16), dword_449318[0]);
    local_8 = dword_449328->unk_74->unk_08;
    dword_449320 = local_8 + var_4;
}

// match: sub_69620 @ 0x00069620
// sp-match: sub_69620 @ 0x0005A600
// Opcode 27: sets the script's flag (byte 1) to sub_6A7A0 of bytes 2 and 3
// when clear, then jumps by the next word when it is set, else skips it.
void sub_69620()
{
    RwInt8 local_5;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    if (!((type_3D2CD0 *)dword_449328)->sub_6E400(var_4)) {
        local_5 = sub_6A7A0((*dword_449320 & 0xFF0000) >> 16, *dword_449320 >> 24);
        ((type_3D2CD0 *)dword_449328)->sub_6E430(var_4, local_5);
    }
    if (((type_3D2CD0 *)dword_449328)->sub_6E450(var_4))
        dword_449320 += dword_449320[1];
    else
        dword_449320 += 2;
}

// match: sub_696D0 @ 0x000696D0
// sp-match: sub_696D0 @ 0x0005A680
// Opcode 28: pushes sub_6A7A0 of bytes 2 and 3.
void sub_696D0()
{
    RwInt8 var_2;
    RwInt8 var_1;

    var_1 = (RwInt8)((*dword_449320 & 0xFF0000) >> 16);
    var_2 = (RwInt8)(*dword_449320 >> 24);
    *dword_449318 = sub_6A7A0(var_1, var_2);
    dword_449318++;
    dword_449320++;
}

// match: sub_69730 @ 0x00069730
// sp-match: sub_69730 @ 0x00058CA0
// Opcode 36: replaces the top with sub_72900 of it.
void sub_69730()
{
    RwInt32 var_4;

    var_4 = sub_72900(dword_449318[-1]);
    dword_449318[-1] = var_4;
    dword_449320++;
}

// match: sub_69770 @ 0x00069770
// sp-match: sub_69770 @ 0x00058CD0
// Opcode 39, call: the running task (kind 3) calls, by the flags (byte 1):
// 2 a function (sub_6FFD0) or 1 a script (sub_6FF20) with the popped word,
// bytes 2 and 3 and flag 4; neither, sub_6FF00.
void sub_69770()
{
    RwInt32 var_1C;
    type_46120 *var18;
    RwInt32 stk_14;
    RwInt32 l10;
    RwInt32 local_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    SCRIPT_CHECK(dword_449328->vf_014() == 3);
    var18 = (type_46120 *)dword_449328;
    local_C = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    l10 = (RwInt8)((*dword_449320 & 0xFF0000) >> 16);
    lv_8 = (RwInt8)(*dword_449320 >> 24);
    var_1C = test_flag(local_C, 1);
    var_4 = test_flag(local_C, 2);
    stk_14 = test_flag(local_C, 4);
    dword_449320++;
    if (var_4 != 0) {
        ((type_3D2E20 *)var18)->sub_6FFD0(dword_449318[-1], l10, lv_8, stk_14 != 0);
        dword_449318--;
    } else if (var_1C != 0) {
        ((type_3D2E20 *)var18)->sub_6FF20(dword_449318[-1], l10, lv_8, stk_14 != 0);
        dword_449318--;
    } else
        ((type_3D2E20 *)var18)->sub_6FF00();
}

// match: sub_698A0 @ 0x000698A0
// sp-match: sub_698A0 @ 0x00058DD0
// Opcode 40: sets the running task's call flag (byte 2), continues it at
// the next instruction and halts.
void sub_698A0()
{
    type_46120 *local_8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF0000) >> 16);
    SCRIPT_CHECK(dword_449328->vf_014() == 3);
    local_8 = (type_46120 *)dword_449328;
    local_8->unk_118->unk_14_0 = var_4;
    dword_449320++;
    ((type_3D2E20 *)local_8)->sub_70080(dword_449320);
    byte_449324 = 1;
}

// match: sub_69930 @ 0x00069930
// sp-match: sub_69930 @ 0x00058E60
// Opcode 47: sets the running task's call flag and byte (bytes 2 and 3),
// continues it at the halt (opcode 18) that follows, past a pop (38), and
// pushes its result.
void sub_69930()
{
    RwInt32 varC;
    type_46120 *local_8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF0000) >> 16);
    varC = (RwInt8)(*dword_449320 >> 24);
    SCRIPT_CHECK(dword_449328->vf_014() == 3);
    local_8 = (type_46120 *)dword_449328;
    local_8->unk_118->unk_14_0 = var_4;
    local_8->unk_118->unk_10 = (RwInt8)varC;
    dword_449320++;
    SCRIPT_CHECK((RwInt8)(*dword_449320 & 0xFF) == 0x12 || (RwInt8)(*dword_449320 & 0xFF) == 0x26);
    if ((RwInt8)(*dword_449320 & 0xFF) == 0x12)
        ((type_3D2E20 *)local_8)->sub_70080(dword_449320 + 1);
    else {
        SCRIPT_CHECK((RwInt8)(dword_449320[1] & 0xFF) == 0x12);
        ((type_3D2E20 *)local_8)->sub_70080(dword_449320 + 2);
    }
    *dword_449318 = ((type_3D2E20 *)local_8)->sub_700A0();
    dword_449318++;
}

// match: sub_69A90 @ 0x00069A90
// sp-match: sub_69A90 @ 0x0005A6E0
// Opcode 37, return: from the running task's call (flag 2 of byte 1, with
// the top word), or from a function (the operand's record), keeping its
// arguments in byte_449298 (flag 1); halts.
void sub_69A90()
{
    type_4492EC *stk_18;
    RwInt32 l14;
    type_46120 *var_10;
    bool local_9;
    RwInt32 var_8;
    bool var_1;

    var_8 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    var_1 = test_flag(var_8, 1);
    local_9 = test_flag(var_8, 2);
    if (local_9) {
        var_10 = (type_46120 *)dword_449328;
        SCRIPT_CHECK(var_10->vf_014() == 3);
        ((type_3D2E20 *)var_10)->sub_70850(dword_449318[-1]);
        ((type_3D2C88 *)var_10)->sub_70B70();
    } else {
        l14 = (RwInt16)(*dword_449320 >> 16);
        stk_18 = sub_6A950(l14);
        if (var_1)
            memcpy(byte_449298, dword_449318 - stk_18->unk_10, stk_18->unk_10 * 4);
    }
    byte_449324 = 1;
}

// match: sub_69B70 @ 0x00069B70
// sp-match: sub_69B70 @ 0x00058FC0
// Opcode 29, sleep: the running script sleeps (the operand) and halts.
void sub_69B70()
{
    RwInt32 local_8;
    type_67620 *var_4;

    var_4 = dword_449328;
    local_8 = (RwInt16)(*dword_449320 >> 16);
    ((type_3D2DB8 *)var_4)->sub_6F500((RwInt16)local_8);
    byte_449324 = 1;
}

// match: sub_69BB0 @ 0x00069BB0
// sp-match: sub_69BB0 @ 0x00058FE0
// Opcode 34, load global: pushes the count (byte 1) of words from the
// running script's data (unk_74) at the operand.
void sub_69BB0()
{
    RwInt32 var_10;
    type_67620 *ebp_C;
    RwInt32 v8;
    RwInt32 *var_4;

    ebp_C = dword_449328;
    v8 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    var_4 = (RwInt32 *)ebp_C->unk_74;
    for (var_10 = 0; var_10 < v8; var_10++)
        dword_449318[var_10] = (var_4 + (RwInt16)(*dword_449320 >> 16))[var_10];
    dword_449318 += v8;
    dword_449320++;
}

// match: sub_69C50 @ 0x00069C50
// sp-match: sub_69C50 @ 0x00059060
// Opcode 32, store global: pops the count (byte 1) of words into the
// running script's data at the operand.
void sub_69C50()
{
    RwInt32 var_10;
    type_67620 *ebp_C;
    RwInt32 v8;
    RwInt32 *var_4;

    ebp_C = dword_449328;
    v8 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    var_4 = (RwInt32 *)ebp_C->unk_74;
    for (var_10 = 0; var_10 < v8; var_10++)
        (var_4 + (RwInt16)(*dword_449320 >> 16))[var_10] = (dword_449318 - v8)[var_10];
    dword_449318 -= v8;
    dword_449320++;
}

// match: sub_69CF0 @ 0x00069CF0
// sp-match: sub_69CF0 @ 0x000590E0
// Opcode 35: pushes the running script's local at the operand.
void sub_69CF0()
{
    type_67620 *var_4;

    var_4 = dword_449328;
    *dword_449318 = ((RwInt32 *)((type_3D2DB8 *)var_4)->sub_6FB50())[get_operand()];
    dword_449318++;
    dword_449320++;
}

// match: sub_69D50 @ 0x00069D50
// sp-match: sub_69D50 @ 0x00059130
// Opcode 33: pops into the running script's local at the operand.
void sub_69D50()
{
    type_67620 *var_4;

    var_4 = dword_449328;
    dword_449318--;
    ((RwInt32 *)((type_3D2DB8 *)var_4)->sub_6FB50())[get_operand()] = *dword_449318;
    dword_449320++;
}

// match: sub_69DB0 @ 0x00069DB0
// sp-match: sub_69DB0 @ 0x0005A7B0
// Opcode 31, call function: calls the function record at the operand in
// the script the popped handle names (flag 1 of byte 1), or in the script
// of the object it names, passing the arguments on the stack; pops them
// and pushes its results, or zeros when it did not run.
void sub_69DB0()
{
    type_4492EC *stk_18;
    RwInt32 l14;
    bool local_D;
    RwInt32 stk_C;
    RwInt32 v8;
    type_67620 *var_4;

    v8 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    l14 = (RwInt16)(*dword_449320 >> 16);
    local_D = test_flag(v8, 1);
    stk_C = 0;
    dword_449320++;
    stk_18 = sub_6A950(l14);
    var_4 = 0;
    dword_449318--;
    if (local_D) {
        RwInt32 var_1C = *dword_449318;
        var_4 = sub_67620(var_1C);
    } else {
        RwInt32 var_24 = *dword_449318;
        type_3D2E7C *var_20 = (type_3D2E7C *)sub_67620(var_24);
        if (var_20 != 0)
            var_4 = var_20->sub_71340();
    }
    if (var_4 != 0) {
        if (dword_449328->vf_014() == 2)
#ifdef CODFH_SP // shape: SP 0x5A7B0 calls type_3D2DB8's copy (0x5CD20); this unit's folded type_67620 stand-in would let /O2 keep edx across the call
            ((type_3D2DB8 *)dword_449328)->sub_6F460(dword_449318);
#else
            dword_449328->sub_6F460(dword_449318);
#endif
        stk_C = ((type_3D2DB8 *)var_4)->sub_6F340(stk_18, dword_449318);
    }
    dword_449318 -= stk_18->unk_08;
    if (stk_18->unk_0C != 0) {
        if (stk_C)
            memcpy(dword_449318, byte_449298, stk_18->unk_10 * 4);
        else
            memset(dword_449318, 0, stk_18->unk_10 * 4);
        dword_449318 += stk_18->unk_10;
    }
}

// match: sub_69F40 @ 0x00069F40
// sp-match: sub_69F40 @ 0x00059170
// Opcode 41, wake: wakes the task the popped handle names, if it waits.
void sub_69F40()
{
    bool ebp_9;
    RwInt32 local_8;
    type_46120 *var_4;

    dword_449318--;
    local_8 = *dword_449318;
    var_4 = (type_46120 *)sub_67620(local_8);
    dword_449320++;
    ebp_9 = var_4->unk_10C;
    if (ebp_9)
        ((type_3D2E20 *)var_4)->sub_70590(0, 0, 0);
}

// match: sub_69FB0 @ 0x00069FB0
// sp-match: sub_69FB0 @ 0x000591B0
// Opcode 43, kill: ends the task of the object the popped handle names
// (byte 1 set) or of the running script's own; when that is the running
// task, it ends and the VM leaves it.
void sub_69FB0()
{
    bool local_9;
    type_3D2E7C *var_8;
    bool var_1;

    local_9 = (bool)(RwInt8)((*dword_449320 & 0xFF00) >> 8);
    var_8 = 0;
    if (local_9) {
        dword_449318--;
        RwInt32 var_10 = *dword_449318;
        var_8 = (type_3D2E7C *)sub_67620(var_10);
    } else
        var_8 = dword_449328->vf_024();
    var_1 = dword_449328->vf_024() == var_8;
    var_8->sub_70DB0();
    dword_449320++;
    if (dword_449328->vf_014() == 3 && var_1) {
        byte_449325 = 1;
        byte_449324 = 1;
    }
}

// match: sub_6A080 @ 0x0006A080
// sp-match: sub_6A080 @ 0x00059230
// Opcode 44, spawn: replaces the task of the object the popped handle names
// (byte 1 set) or of the running script's own with a new one at the
// function the operand gives; as the kill opcode when it is the running
// task.
void sub_6A080()
{
    bool v11;
    type_46120 *l10;
    type_3D2E7C *local_C;
    bool var5;
    RwInt32 var_4;

    v11 = (bool)(RwInt8)((*dword_449320 & 0xFF00) >> 8);
    local_C = 0;
    if (v11) {
        dword_449318--;
        RwInt32 var_18 = *dword_449318;
        local_C = (type_3D2E7C *)sub_67620(var_18);
    } else
        local_C = dword_449328->vf_024();
    var5 = dword_449328->vf_024() == local_C;
    var_4 = (RwInt16)(*dword_449320 >> 16);
    l10 = sub_71B90();
    ((type_3D2E20 *)l10)->sub_6FE00(var_4);
    local_C->sub_70DB0();
    local_C->sub_71220(l10);
    ((type_3D2E20 *)l10)->sub_70310();
    ((type_3D2E20 *)l10)->sub_70590(0, 0, 0);
    dword_449320++;
    if (dword_449328->vf_014() == 3 && var5) {
        byte_449325 = 1;
        byte_449324 = 1;
    }
}

// match: sub_6A1A0 @ 0x0006A1A0
// sp-match: sub_6A1A0 @ 0x000592F0
// Opcode 42, thread: starts a new task at the function the operand gives
// (popped when flag 8 of byte 1 is set, else the next word) on the object
// the popped handle names (flag 1) or the running script's own, below its
// current thread's task (flags 2 and 4 its interrupt flags) or as its first
// task; yields when the task to run changes.
void sub_6A1A0()
{
    bool bp_21;
    type_46120 *t20;
    type_3D2E7C *s1c;
    bool local_16;
    bool x15;
    type_46120 *ebp_14;
    RwInt32 lv_10;
    bool w9;
    RwInt32 bp_8;
    type_46120 *bp_4;

    bp_8 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    bp_21 = test_flag(bp_8, 1);
    x15 = test_flag(bp_8, 2);
    local_16 = test_flag(bp_8, 4);
    w9 = true;
    if (test_flag(bp_8, 8)) {
        dword_449318--;
        lv_10 = *dword_449318;
    } else
        lv_10 = dword_449320[1];
    bp_4 = 0;
    t20 = 0;
    ebp_14 = 0;
    s1c = 0;
    t20 = sub_71B90();
    ((type_3D2E20 *)t20)->sub_6FE00(lv_10);
    if (bp_21) {
        dword_449318--;
        RwInt32 var_2C = *dword_449318;
        type_3D2E7C *var_28 = (type_3D2E7C *)sub_67620(var_2C);
        SCRIPT_CHECK(var_28 != 0);
        if (var_28 == 0) {
            dword_449320 += 2;
            return;
        }
        s1c = var_28;
        if (dword_449328->vf_024() != var_28) {
            w9 = false;
            if (var_28->sub_71090() != 0)
                bp_4 = (type_46120 *)sub_67620(var_28->sub_71090()->get_unk_114()->unk_00);
        } else
            bp_4 = var_28->sub_71090();
    } else if (dword_449328->vf_014() == 3) {
        bp_4 = (type_46120 *)dword_449328;
        s1c = dword_449328->vf_024();
    } else {
        s1c = dword_449328->vf_024();
        bp_4 = s1c->sub_71090();
    }
    if (bp_4 == 0) {
        s1c->sub_71220(t20);
        ebp_14 = t20;
    } else
        ebp_14 = ((type_46120 *)((type_3D2E20 *)bp_4)->sub_70930((type_3D2E20 *)t20, x15, local_16));
    dword_449320 += 2;
    if (ebp_14 != bp_4) {
        if (dword_449328->vf_014() == 3) {
            type_46120 *var_30 = (type_46120 *)dword_449328;
            dword_449328->vf_018(dword_449320);
            dword_449328->vf_01C(dword_449318);
            dword_449328->vf_020(dword_44931C);
            ((type_3D2E20 *)ebp_14)->sub_70310();
            ((type_3D2E20 *)ebp_14)->sub_70590(0, 0, 0);
            if (!w9 && var_30->get_unk_114()->unk_04 == var_30->get_unk_04_h())
                byte_449325 = 0;
            else
                byte_449325 = 1;
            if (var_30->get_unk_114() == 0)
                byte_449324 = 1;
            else if (var_30->get_unk_114()->unk_04 != var_30->get_unk_04_h())
                byte_449324 = 1;
            else if (var_30->get_unk_10C())
                byte_449324 = 1;
        } else {
            ((type_3D2E20 *)ebp_14)->sub_70310();
            ((type_3D2E20 *)ebp_14)->sub_70590(0, 0, 0);
        }
    }
}

// match: sub_6A4F0 @ 0x0006A4F0
// sp-match: sub_6A4F0 @ 0x00059530
// Opcode 45, action: queues the action of the script the handle (popped,
// flag 2 of byte 1, or the next word) names on the object the popped handle
// names (byte 2 is 0) with the stack's arguments; pops them.
void sub_6A4F0()
{
    type_439E78_00 l20;
    type_67620 *fp_1C;
    RwInt32 loc18;
    bool l11;
    type_42E00 *var10;
    bool bp_9;
    RwInt32 v8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    bp_9 = test_flag(var_4, 1);
    l11 = test_flag(var_4, 2);
    v8 = (RwInt8)((*dword_449320 & 0xFF0000) >> 16);
    if (l11) {
        dword_449318--;
        loc18 = *dword_449318;
    } else
        loc18 = dword_449320[1];
    fp_1C = 0;
    if (v8 == 0) {
        dword_449318--;
        RwInt32 var_24 = *dword_449318;
        fp_1C = sub_67620(var_24);
    }
    l20 = sub_6B710(loc18, fp_1C, dword_449328->vf_024(), 0, 0, v8, dword_449318, 1);
    var10 = (type_42E00 *)sub_67620(*(RwInt32 *)&l20);
    dword_449318 -= var10->unk_00->unk_10;
    sub_42AF0((type_3D2E7C *)dword_449328, 0x10, *(RwUInt32 *)&l20, bp_9, 0);
    dword_449320 += 2;
}

// match: sub_6A640 @ 0x0006A640
// sp-match: sub_6A640 @ 0x00059600
// Opcode 46, sound: plays the sound under the key in the next two words
// from the running script's entity (byte 1 is 2) or player 0.
void sub_6A640()
{
    type_3D3548 *v8;
    RwInt32 var_4;

    var_4 = (RwInt8)((*dword_449320 & 0xFF00) >> 8);
    type_3DF8D8_04 var_10;
    var_10.unk_00 = dword_449320[1];
    var_10.unk_04 = dword_449320[2];
    if (var_4 == 2)
        v8 = dword_449328->vf_024()->sub_71300();
    else
        v8 = sub_1745A0(0);
    v8->unk_1C0.sub_8A980(&var_10, v8, 0, v8->sub_CD550(), 0, 0);
    dword_449320 += 3;
}

// match: sub_6A6F0 @ 0x0006A6F0
// sp-match: sub_6A6F0 @ 0x0005A8B0
// Opcode 48, line: the running line and file (the next word's halves; the
// file's name from dword_449290), reported to the debugger when the line
// changes and to the script.
void sub_6A6F0()
{
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = dword_449320[1];
    local_8 = dword_449284;
    dword_449284 = var_4 & 0xFFFF;
    dword_4492AC = var_4 >> 16;
    if (dword_449290[dword_4492AC] != 0)
        dword_449288 = (RwInt32)dword_449290[dword_4492AC];
    if (local_8 != dword_449284)
        sub_6B060(dword_449328, "Line Changed", 0);
    dword_449328->vf_03C(dword_449284, dword_449288);
    dword_449320 += 2;
}

// match: sub_6A7A0 @ 0x0006A7A0
// sp-match: sub_6A7A0 @ 0x00059680
// A random number from arg_0 to arg_4.
RwInt8 sub_6A7A0(RwInt8 arg_0, RwInt8 arg_4)
{
    RwInt32 var_4;

    var_4 = RpRandom();
    return (RwInt8)(var_4 % (arg_4 - arg_0 + 1) + arg_0);
}

// match: sub_6A7D0 @ 0x0006A7D0
// sp-match: sub_6A7D0 @ 0x000596A0
type_42E00_00 *sub_6A7D0(RwInt32 arg_0)
{
    return &dword_4492F4[arg_0];
}

// match: sub_6A7F0 @ 0x0006A7F0
// sp-match: sub_6A7F0 @ 0x000596C0
// dword_4492F4's record named arg_0 (in any case), or 0.
type_42E00_00 *sub_6A7F0(const RwChar *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < dword_4492F8; var_4++) {
        if (dword_4492F4[var_4].unk_00 != 0 && _strcmpi(arg_0, dword_4492F4[var_4].unk_00) == 0)
            return &dword_4492F4[var_4];
    }
    return 0;
}

// match: sub_6A860 @ 0x0006A860
// sp-match: sub_6A860 @ 0x00059720
// The unk_04 of dword_4492F4's record with unk_08 arg_0 and unk_0C arg_4,
// or -1.
RwInt32 sub_6A860(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < dword_4492F8; var_4++) {
        if (dword_4492F4[var_4].unk_00 != 0 && dword_4492F4[var_4].unk_08 == arg_0
            && dword_4492F4[var_4].unk_0C == arg_4)
            return dword_4492F4[var_4].unk_04;
    }
    return -1;
}

// match: sub_6A8E0 @ 0x0006A8E0
// sp-match: sub_6A8E0 @ 0x00059770
// dword_4492FC's record named arg_0 (in any case), or 0.
type_4492FC *sub_6A8E0(const RwChar *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < dword_449300; var_4++) {
        if (dword_4492FC[var_4].unk_00 != 0 && _strcmpi(arg_0, dword_4492FC[var_4].unk_00) == 0)
            return &dword_4492FC[var_4];
    }
    return 0;
}

// match: sub_6A950 @ 0x0006A950
// sp-match: sub_6A950 @ 0x000597D0
type_4492EC *sub_6A950(RwInt32 arg_0)
{
    return &dword_4492EC[arg_0];
}

// The messages the debugger never reports (AllBurstsFinished and the like).
extern const RwChar *Str2[5];
#ifdef CODFH_DRAW_TRIGGERS
// (port/src/debug/trigtools.cpp: the VM tab's log of the debugger's reports, whose
// prints the release build compiled out; pszWhat the report's caption or 0)
void TrigWebScriptReport(const RwChar *pszWhat, const RwChar *pszLine);
#endif

// match: sub_6A970 @ 0x0006A970
// sp-match: sub_6A970 @ 0x000597F0
// The debugger's report of the message arg_0 delivered to the registration
// arg_4 (arg_8 its caption): unless the debugger ignores it (not watching,
// one of Str2's messages, not the watched object or sender), builds "name,
// Reciever: ..., ID: ..., kind, Sender: ..." in a buffer; the print that
// used it is compiled out.
void sub_6A970(type_42E00 *arg_0, type_6B960 *arg_4, const RwChar *arg_8)
{
#ifdef CODFH_SP // shape: SP 0x597F0 formats every part in one 0x80 buffer (sub esp, 0x28C)
    RwChar part[0x80];
    RwChar (&t4C8)[0x80] = part;
    RwChar (&w448)[0x80] = part;
    RwV3d *bp_3C4;
    type_67620 *r3C0;
    type_4CFE30 *lcl_3BC;
    RwChar (&fp_3B8)[0x80] = part;
    RwV3d *bp_334;
    RwChar (&var_330)[0x80] = part;
    RwChar (&local_2B0)[0x80] = part;
#else
    RwChar t4C8[0x80];
    RwChar w448[0x80];
    RwV3d *bp_3C4;
    type_67620 *r3C0;
    type_4CFE30 *lcl_3BC;
    RwChar fp_3B8[0x80];
    RwV3d *bp_334;
    RwChar var_330[0x80];
    RwChar local_2B0[0x80];
#endif
    type_3DF8D8 *loc22C;
    type_3DF8D8_04 *s228;
    type_3DF8D8 *s224;
    type_3DF8D8_04 *bp_220;
    RwInt32 local_21C;
    type_3D2E7C *frm_218;
    type_3DF8D8 *frm_214;
    type_67620 *bp_210;
    type_3DF8D8 *bp_20C;
    RwChar lcl_208[0x200];

    if (dword_449294 == 0 && (dword_4492B0 == 0 || dword_4492B0 != 0 && arg_0->unk_00->unk_10 != 1))
        return;
    for (local_21C = 0; local_21C < 5; local_21C++) {
        if (strcmp(arg_0->unk_00->unk_00, Str2[local_21C]) == 0)
            return;
    }
    bp_210 = 0;
    if (arg_4->unk_1B == 1)
        bp_210 = sub_67620(arg_4->unk_00);
    else if (arg_4->unk_1B == 3)
        bp_210 = sub_67620(arg_4->unk_00);
    frm_218 = (type_3D2E7C *)sub_67620(arg_0->unk_08);
    bp_20C = 0;
    if (bp_210 != 0 && bp_210->vf_024() != 0 && bp_210->vf_024()->sub_712B0() != 0) {
        bp_220 = bp_210->vf_024()->sub_712B0()->vf_01C();
        if (bp_220 != 0 && bp_220->unk_00 != 0 && bp_220->unk_04 != 0)
        {
            s224 = sub_198800(bp_220);
            bp_20C = s224;
        }
    }
    if (dword_449310 != 0 && bp_20C == 0)
        return;
    if (byte_44930C != 0) {
        if (bp_210 != 0 && bp_210->vf_024()->get_unk_24_d() != atoi(String))
            return;
    } else if (String[0] != 0 && (bp_20C == 0 || bp_20C != 0 && strcmp((const RwChar *)bp_20C->unk_14, String) != 0)) {
        return;
    }
    frm_214 = 0;
    if (frm_218 != 0 && frm_218->sub_712B0() != 0) {
        s228 = frm_218->sub_712B0()->vf_01C();
        if (s228 != 0 && s228->unk_00 != 0 && s228->unk_04 != 0)
        {
            loc22C = sub_198800(s228);
            frm_214 = loc22C;
        }
        else
            s228 = 0;
    }
    strcpy(lcl_208, "");
    if (arg_0->unk_00->unk_00 != 0) {
        strcat(lcl_208, arg_0->unk_00->unk_00);
        strcat(lcl_208, ", ");
    } else {
        strcat(lcl_208, "MessageID: ");
        sprintf(local_2B0, "%i", arg_0->unk_00->unk_04);
        strcat(lcl_208, local_2B0);
        strcat(lcl_208, ", ");
    }
    if (bp_20C != 0) {
        strcat(lcl_208, "Reciever: ");
        strcat(lcl_208, (const RwChar *)bp_20C->unk_14);
    }
    if (bp_210 != 0 && bp_210->vf_024() != 0) {
        strcat(lcl_208, " ID: ");
        sprintf(var_330, "%i,", bp_210->vf_024()->get_unk_24_d());
        strcat(lcl_208, var_330);
    } else if (arg_4->unk_1B == 2 && arg_4->unk_04 != 0) {
        bp_334 = &((type_4E56A0_34 *)arg_4->unk_04)->unk_90;
        sprintf(fp_3B8, "Trigger at %.1f, %.1f, %.1f", bp_334->x, bp_334->y, bp_334->z);
        strcat(lcl_208, fp_3B8);
    }
    strcat(lcl_208, " ");
    if (bp_210 != 0) {
        if (bp_210->vf_014() == 2)
            strcat(lcl_208, "State Machine");
        else
            strcat(lcl_208, "Task Script");
    } else {
        strcat(lcl_208, "Trigger Machine");
    }
    strcat(lcl_208, ", Sender: ");
    if (frm_214 != 0) {
        strcat(lcl_208, (const RwChar *)frm_214->unk_14);
#ifdef CODFH_DRAW_TRIGGERS
        TrigWebScriptReport(arg_8, lcl_208);
#endif
        return;
    }
    lcl_3BC = get_performance_map(arg_0->unk_10);
    if (lcl_3BC == 0) {
        strcat(lcl_208, "Engine");
#ifdef CODFH_DRAW_TRIGGERS
        TrigWebScriptReport(arg_8, lcl_208);
#endif
        return;
    }
    if (frm_218 == 0) {
        r3C0 = sub_67620(arg_0->unk_0C);
        if (r3C0 != 0) {
            bp_3C4 = (RwV3d *)&lcl_3BC->unk_60[0x30];
            sprintf(w448, "Proximity Trigger at %.1f,%.1f,%.1f", bp_3C4->x, bp_3C4->y, bp_3C4->z);
            strcat(lcl_208, w448);
        } else {
            strcat(lcl_208, "Anim Opcode");
        }
#ifdef CODFH_DRAW_TRIGGERS
        TrigWebScriptReport(arg_8, lcl_208);
#endif
        return;
    }
    sprintf(t4C8, "%i", frm_218->get_unk_24());
    strcat(lcl_208, t4C8);
#ifdef CODFH_DRAW_TRIGGERS
    TrigWebScriptReport(arg_8, lcl_208);
#endif
}

// match: sub_6B060 @ 0x0006B060
// sp-match: sub_6B060 @ 0x00059EF0
// The debugger's report line for the object arg_0 (arg_4 what happened,
// arg_8 the short form): unless the debugger ignores the object, builds
// "kind(file line): Name: ..., ID: ..., what at tick: ..." in a buffer (the
// print is compiled out); whether it would have printed.
bool sub_6B060(type_67620 *arg_0, const RwChar *arg_4, bool arg_8)
{
#ifndef CODFH_SP // shape: SP 0x59EF0 reserves one 0x800 buffer (sub esp, 0x844): both formats print into fp_858
    RwChar m_1058[0x800];
#endif
    RwChar fp_858[0x800];
    type_3DF8D8 *lv_54;
    type_3DF8D8_04 *ebp_50;
    type_3DF8D8 *o4C;
    RwChar q48[0x40];

    ebp_50 = arg_0->vf_024()->sub_712B0()->vf_01C();
    o4C = 0;
    if (ebp_50 != 0 && ebp_50->unk_00 != 0 && ebp_50->unk_04 != 0) {
        lv_54 = sub_198800(ebp_50);
        o4C = lv_54;
    } else if (dword_449310 != 0) {
        return false;
    }
    if (byte_44930C != 0) {
        if (arg_0->vf_024()->get_unk_24_d() != atoi(String))
            return false;
    } else if (String[0] != 0 && (o4C == 0 || o4C != 0 && strcmp((const RwChar *)o4C->unk_14, String) != 0)) {
        return false;
    }
    if (dword_44928C != 0) {
        switch (arg_0->vf_014()) {
        case 1:
            strcpy(q48, "Performance Object");
            break;
        case 2:
            strcpy(q48, "State Machine Object");
            break;
        case 3:
            strcpy(q48, "Task Object");
            break;
        case 0:
            strcpy(q48, "Unknown Alfa Object");
            break;
        }
    } else if (dword_4492A8 != 0) {
        if (arg_0->vf_014() == 3)
            strcpy(q48, "Task Object");
        else
            return false;
    } else {
        return false;
    }
    if (o4C != 0) {
        if (arg_8)
            sprintf(fp_858, "%s - Name: %s, ID: %d %s at tick: %d", q48, (const RwChar *)o4C->unk_14,
                    arg_0->vf_024()->get_unk_24_d(), arg_4, dword_4B87D8);
        else {
            sprintf(fp_858, "%s(%d): %s Name: %s, ID: %d %s at tick: %d", dword_449288, dword_449284, q48,
                    (const RwChar *)o4C->unk_14, arg_0->vf_024()->get_unk_24_d(), arg_4, dword_4B87D8);
            // A compiled-out check (it moves the registers one step).
            if (0) {
            }
        }
    } else {
#ifdef CODFH_SP // shape: one buffer (see m_1058)
        if (arg_8)
            sprintf(fp_858, "%s - ID: %d, %s at tick: %d\n", q48, arg_0->vf_024()->get_unk_24_d(), arg_4,
                    dword_4B87D8);
        else
            sprintf(fp_858, "%s(%d): %s ID: %d, %s at tick: %d\n", dword_449288, dword_449284, q48,
                    arg_0->vf_024()->get_unk_24_d(), arg_4, dword_4B87D8);
#else
        if (arg_8)
            sprintf(m_1058, "%s - ID: %d, %s at tick: %d\n", q48, arg_0->vf_024()->get_unk_24_d(), arg_4,
                    dword_4B87D8);
        else
            sprintf(m_1058, "%s(%d): %s ID: %d, %s at tick: %d\n", dword_449288, dword_449284, q48,
                    arg_0->vf_024()->get_unk_24_d(), arg_4, dword_4B87D8);
#endif
    }
#ifdef CODFH_DRAW_TRIGGERS
#ifdef CODFH_SP
    TrigWebScriptReport(0, fp_858);
#else
    TrigWebScriptReport(0, o4C != 0 ? fp_858 : m_1058);
#endif
#endif
    return true;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_6F460@type_67620@@QAEXPAH@Z (folded into 0x6F460)
void type_67620::sub_6F460(RwInt32 * arg_0)
{
    dword_4493F8 = arg_0;
    dword_4493FC = dword_4493F8;
}

#ifdef CODFH_SP
// Single player's empty and trivial functions whose own files call them: a body there would
// let /O2 drop or inline those calls, which default.xbe keeps (each file only declares them,
// see its comments), and the link folds them into the bodies below. Defined here for the
// authentic link (PLAN_SP SP6): the M7 link folds each into the row config/sp/aliases.txt
// gives it (the empty body SCRIPT_CHECK_SLOTS at 0x5A260 is this file's).
#include "game/astarpathfinder.h"
#include "game/gameloop.h"
#include "types/type_10F710.h"
#include "types/type_141C10.h"
#include "types/type_143DC0.h"
#include "types/type_3D32F8.h"
#include "types/type_3D51C0.h"
#include "types/type_3D94B8.h"
#include "types/type_3D96F0.h"
#include "types/type_3DAC58.h"
#include "types/type_3DC9B0.h"
#include "types/type_3DD948.h"
#include "types/type_3DDB98.h"
#include "types/type_3DDE70.h"
#include "types/type_3DE0E0.h"
#include "types/type_4B83A0.h"
#include "types/type_4B85F8.h"
#include "types/type_4E5D30.h"
#include "types/type_D48D0.h"

// the empty body (SP 0x5A260)
void sub_19A750() {}
void sub_19A750(RwReal arg_0) {}
void sub_19A750(void *arg_0) {}
void sub_19A750(RwInt16 *arg_0) {}
void sub_19A750(struct RwStream *arg_0) {}
void sub_19A750(struct RwStream *arg_0, struct type_141C10 *arg_4) {}
#ifndef CODFH_SP_LOGS // (CODFH_SP_LOGS: unit_0441B0's, the port's sound log)
void sub_19A750(struct type_3D3548 *arg_0, RwInt32 arg_4, struct type_3DF8D8_04 arg_8, RwInt32 arg_C) {}
#endif
void sub_141C10_kind15(struct RwStream *arg_0, struct type_141C10 *arg_4) {}
void sub_141C10_kind30(struct RwStream *arg_0, struct type_141C10 *arg_4) {}
#ifndef CODFH_SP_LOGS // (CODFH_SP_LOGS: unit_144940's, with multiplayer's warnings)
void sub_144AD0() {}
#endif
type_4BFED0::~type_4BFED0() {}
type_4E5D30::~type_4E5D30() {}
type_FB6E0::~type_FB6E0() {}
void type_4B85F8::pDtor() {}
void type_4F2B68::pDtor() {}
#ifndef CODFH_SP_LOGS // (CODFH_SP_LOGS: unit_0D5170's, with multiplayer's warning)
void type_4B83A0::sub_D6550() {}
#endif
void type_10F710::operator delete(void *arg_0, void *arg_4) {}
void type_10F710::operator delete(void *arg_0) {}
void type_3D32F8::operator delete(void *arg_0) {}
void type_3D51C0::operator delete(void *arg_0) {}
void type_3D94B8::operator delete(void *arg_0) {}
void type_3D96F0::operator delete(void *arg_0) {}
void type_3DAC58::operator delete(void *arg_0) {}
void type_3DC9B0::operator delete(void *arg_0) {}
void type_3DD948::operator delete(void *arg_0) {}
void type_3DDB98::operator delete(void *arg_0) {}
void type_3DDE70::operator delete(void *arg_0) {}
void type_3DE0E0::operator delete(void *arg_0) {}
void type_3DE350::operator delete(void *arg_0) {}

// the entities' placement new (SP 0x122FF0)
void *type_10F710::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// `return 0` (SP 0x6CEB0)
RwInt32 sub_170ED0(RwReal *arg_0)
{
    return 0;
}

// the material getter (SP 0x5BA70)
struct RpMaterial *type_143D90::sub_FB710()
{
    return unk_08;
}

// the handle table's lookup (SP 0xA0E70, type_D48D0's)
struct type_3D3548 *type_3D96F0_14::sub_D4910()
{
    type_3D3548 *var_4;

    var_4 = 0;
    if (dword_4B6A00[(RwInt16)unk_00].unk_00 == unk_00)
    {
        var_4 = dword_4B6A00[(RwInt16)unk_00].unk_04;
    }
    return var_4;
}

// the leak check's `return false` (SP 0xD5A00, sub_12F080's)
bool sub_12EE80(RwInt32 arg_0)
{
    return false;
}
#endif
