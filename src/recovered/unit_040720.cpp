// The Vision Scheduler ("Somebody forgot to unregister in the Vision
// Scheduler!", sub_408D0): registrations that have an object's entity look
// for targets and message it when it sees one or loses sight of one. Its
// setup (sub_40720), shutdowns (sub_407C0, sub_40840) and warning mirror the
// Distance Scheduler's (sub_34FA0 to sub_350D0), so this unit is taken to
// start at sub_40720; its handle table functions (sub_42870 to sub_42960)
// end it, before the action pool ("m_actionPool", sub_42990). Its original
// file name is not in the image, so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "rws/gftime.h"
#include "rw/rprandom.h"
#include "rw/bavector.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/rpcollis.h"
#include "rw/rpatomic.h"
#include "rw/rtquat.h"
#include "game/pathnodes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/alfasched.h"
#include "types/type_154C0_80.h"
#include "types/type_365A0.h"
#include "types/type_3D2E7C.h"
#include "types/type_3D3548.h"
#include "types/type_3DBC78.h"
#include "types/type_409A0.h"
#include "types/type_4B8600.h"
#include "types/type_4E5D30.h"
#include "types/type_67620.h"
#include "rws/csystemcommands.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE89C
extern const RwReal flt_3CE89C = 16.666666f;
// 0x0042767C
RwInt32 dword_42767C = 1;
// 0x00427680
RwReal flt_427680 = 4000000.0f;
// 0x00439618
type_439618 dword_439618[66];
// 0x00439828
RwInt32 dword_439828;
// 0x0043982C
RwReal dword_43982C;
// 0x00439830
RwInt32 dword_439830;
// 0x00439834
RwInt32 dword_439834;
// 0x00439838
RwInt32 dword_439838;
// 0x0043983C
RwReal dword_43983C;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
alfasched dword_439840;
alfasched dword_4398B0;
type_16C2A0 dword_43988C;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@3f666666 @ 0x003CDB74
// match: ?flt_3CE89C@@3MB @ 0x003CE89C
// match: ??_C@_0BD@FKCEOFJF@m_freeVisionParams?$AA@ @ 0x003CE8A0
// match: ??_C@_0DH@JKDCOIFO@Somebody?5forgot?5to?5unregister?5in@ @ 0x003CE8B4
// match: ??_C@_0BI@IBPOEDHP@CanPotentiallySeeTarget?$AA@ @ 0x003CE8EC
// match: ??_C@_0L@OJFFBMFH@TargetSeen?$AA@ @ 0x003CE904
// match: ??_C@_0BL@NONMKLCK@CannotPotentiallySeeTarget?$AA@ @ 0x003CE910
// match: ??_C@_0O@FBCDPBHJ@TargetLostLOS?$AA@ @ 0x003CE92C
// match: .CRT$XCU+0 @ 0x00426D8C
// match: .CRT$XCU+4 @ 0x00426D90
// match: .CRT$XCU+8 @ 0x00426D94
// match: ?dword_42767C@@3HA @ 0x0042767C
// match: ?flt_427680@@3MA @ 0x00427680

// match: _$E2 @ 0x00309890
// match: _$E3 @ 0x0030DCD0
// match: _$E5 @ 0x003098B0
// match: _$E6 @ 0x0030DCE0
// match: _$E8 @ 0x003098D0
// match: _$E9 @ 0x0030DCF0
// sp-match: _$E9 @ 0x0021E120
// sp-match: _$E2 @ 0x0021C310
// sp-match: _$E5 @ 0x0021C330
// sp-match: _$E8 @ 0x0021C350
// sp-match: _$E3 @ 0x0021E100
// sp-match: _$E6 @ 0x0021E110

RwInt32 sub_40F00(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
RwInt32 sub_40FB0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
RwInt32 sub_41390(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
void sub_408D0();
RwUInt32 sub_42870(type_409A0 *arg_0);
void sub_42930(type_365A0 arg_0);
type_409A0 *sub_42960(type_365A0 arg_0);
void sub_40C60(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8);
void sub_40BD0(type_3D3548 *arg_0, type_409A0 *arg_4);
void sub_40EA0(type_3D3548 *arg_0, type_409A0 *arg_4, RwInt32 arg_8);
RwInt32 sub_41200(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8, RwInt32 *arg_C);
RwInt32 sub_41300(type_3D3548 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_413E0(type_3D3548 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_41420(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8);
RwInt32 sub_414F0(type_3D3548 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwReal *arg_C);
// sub_415E0: whether arg_4 lies within arg_0's view cone (its vf_0FC
// across, vf_100 up), by the projections onto its frame's rows.
RwInt32 sub_415E0(type_3D3548 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_41AD0(type_3D3548 *arg_0, type_3D3548 *arg_4);
// Whether arg_0 sees arg_4 from the node arg_8.
RwInt32 sub_41B20(type_3D3548 *arg_0, type_3D3548 *arg_4, type_F8350 *arg_8);
RwInt32 sub_421C0(type_3D3548 *arg_0, type_3D3548 *arg_4);
RwInt32 sub_42210(RwV3d *arg_0, RwV3d *arg_4, type_3D3548 *arg_8, type_3D3548 *arg_C);
RpAtomic *sub_42350(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10);
RpCollisionTriangle *sub_42580(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8,
                               void *arg_C);
void sub_425A0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8);
void sub_426E0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8, RwInt32 arg_C);

// match: sub_40720 @ 0x00040720
// sp-match: sub_40720 @ 0x00031F80
void sub_40720()
{
    dword_43983C = 0.0f;
    dword_43988C.sub_16C2C0(0x40, 0x20, "m_freeVisionParams", 4, 0);
    dword_439840.sub_71F20(0x20, 1, 1, 1, sub_40FB0, sub_41390);
    dword_4398B0.sub_71F20(0x20, 1, 1, 1, sub_40F00, sub_41390);
    memset(dword_439618, 0, sizeof(dword_439618));
    dword_439828 = 0;
    dword_439838 = 0;
    dword_439834 = 0;
    dword_439830 = 0;
}

// match: sub_407C0 @ 0x000407C0
// sp-match: sub_407C0 @ 0x000314F0
void sub_407C0()
{
    RwInt32 var_4;

    var_4 = dword_439840.sub_71FA0();
    if (var_4 != 0)
        sub_408D0();
    var_4 = dword_4398B0.sub_71FA0();
    if (var_4 != 0)
        sub_408D0();
    memset(dword_439618, 0, sizeof(dword_439618));
    dword_439828 = 0;
    dword_439838 = 0;
    dword_43983C = 0.0f;
    dword_439834 = 0;
    dword_439830 = 0;
}

// match: sub_40840 @ 0x00040840
// sp-match: sub_40840 @ 0x00031530
void sub_40840()
{
    RwInt32 var_4;

    var_4 = dword_439840.sub_71FC0();
    if (var_4 != 0)
        sub_408D0();
    var_4 = dword_4398B0.sub_71FC0();
    if (var_4 != 0)
        sub_408D0();
    dword_43988C.sub_16C4D0(1);
    memset(dword_439618, 0, sizeof(dword_439618));
    dword_439828 = 0;
    dword_439838 = 0;
    dword_43983C = 0.0f;
    dword_439834 = 0;
    dword_439830 = 0;
}

// match: sub_408D0 @ 0x000408D0
void sub_408D0()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0x31530 drops the calls)
    sub_19A750("Somebody forgot to unregister in the Vision Scheduler!");
#endif
}

// match: sub_408F0 @ 0x000408F0
// sp-match: sub_408F0 @ 0x00030A70
// The update, with the time step arg_0: runs dword_4398B0 until three looks
// were made (dword_439834) or each entry ran once, then dword_439840 until
// one was (dword_439830).
void sub_408F0(RwReal arg_0)
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    dword_43982C = arg_0;
    dword_439834 = 0;
    dword_439830 = 0;
    var_4 = 0;
    local_8 = dword_4398B0.sub_727D0();
    while (dword_439834 < 3 && var_4 < local_8) {
        dword_4398B0.sub_72560(arg_0);
        var_4++;
    }
    var_4 = 0;
    varC = dword_439840.sub_727D0();
    while (dword_439830 < 1 && var_4 < varC) {
        dword_439840.sub_72560(arg_0);
        var_4++;
    }
}

// match: sub_409A0 @ 0x000409A0
// sp-match: sub_409A0 @ 0x00031580
type_409A0 *sub_409A0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, type_3D2E7C *arg_C)
{
    type_409A0 *var_4;

    var_4 = (type_409A0 *)dword_43988C.sub_16C5A0(0);
    var_4->unk_04 = arg_0;
    var_4->unk_1C_0 = arg_4;
    var_4->unk_1C_1 = arg_8;
    var_4->unk_0C = 0;
    var_4->unk_18 = RpRandom() % (dword_42767C + 1);
    var_4->unk_14 = 0;
    if (arg_C != 0) {
        var_4->unk_0C = arg_C->get_unk_04();
        var_4->unk_10 = arg_C->get_unk_24();
    }
    var_4->unk_00.unk_00 = sub_42870(var_4);
    return var_4;
}

// match: sub_40A60 @ 0x00040A60
// sp-match: sub_40A60 @ 0x00031600
// Registers arg_0 with both schedules, a registration each (sub_409A0).
void sub_40A60(type_67620 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
               type_3D2E7C *arg_10)
{
    type_409A0 *var_4;

    var_4 = sub_409A0(arg_4, arg_8, arg_C, arg_10);
    dword_4398B0.sub_72050(arg_0, var_4->unk_00.unk_00, 0, 0);
    var_4 = sub_409A0(arg_4, arg_8, arg_C, arg_10);
    dword_439840.sub_72050(arg_0, var_4->unk_00.unk_00, 0, 0);
}

// match: sub_40AE0 @ 0x00040AE0
// sp-match: sub_40AE0 @ 0x00030B10
void sub_40AE0(type_67620 *arg_0)
{
    if (arg_0 != 0) {
        dword_439840.sub_72240(arg_0);
        dword_4398B0.sub_72240(arg_0);
    }
}

// match: sub_40B10 @ 0x00040B10
// sp-match: sub_40B10 @ 0x00032010
// Has arg_0 look at arg_4 at once (AIData::sub_18BB0, on a new target):
// a test-3 look through a registration on the stack.
void sub_40B10(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    RwInt32 var_30;
    RwUInt32 bp_2C;
    type_67620 *local_28;
    type_3D2E7C *var_24;
    type_409A0 var_20;

    local_28 = arg_0->vf_098()->sub_71340();
    var_24 = arg_4->vf_098();
    if (local_28 == 0 || var_24 == 0)
        return;
    var_20.unk_00.unk_00 = 0;
    var_30 = var_24->unk_24;
    var_20.unk_10 = var_30;
    bp_2C = var_24->unk_04;
    var_20.unk_0C = bp_2C;
    var_20.unk_04 = 3;
    var_20.unk_1C_0 = 0;
    var_20.unk_1C_1 = 1;
    var_20.unk_18 = 0;
    var_20.unk_14 = -1;
    var_20.unk_08 = (var_20.unk_08 = arg_0->vf_10C()) * var_20.unk_08;
    sub_40C60(arg_0, arg_4, &var_20);
}

// match: sub_40BD0 @ 0x00040BD0
// sp-match: sub_40BD0 @ 0x00030B40
// Before a look for the registration arg_4: the time since its last look
// (in 60ths of a second) into dword_43983C, and arg_0's squared view range
// into its unk_08.
void sub_40BD0(type_3D3548 *arg_0, type_409A0 *arg_4)
{
    RwUInt32 local_8;
    RwUInt32 var_4;

    if (arg_4->unk_14 != -1) {
        if (arg_4->unk_14 == 0) {
            dword_43983C = dword_43982C;
        } else {
            local_8 = RWS::Time::GetTime();
            if ((var_4 = local_8 - arg_4->unk_14) != 0)
                dword_43983C = var_4 / flt_3CE89C;
            else
                dword_43983C = dword_43982C;
        }
    }
    arg_4->unk_08 = arg_0->vf_10C();
    arg_4->unk_08 = arg_4->unk_08 * arg_4->unk_08;
}

// match: sub_40C60 @ 0x00040C60
// sp-match: sub_40C60 @ 0x00031BF0
// arg_0 looks at arg_4 for the registration arg_8: when it may (sub_41420)
// and arg_4 is in range (sub_414F0), it sees it (sub_425A0) or not
// (sub_426E0, told whether only the second test ran); a look put off adds
// the time step to the target record's unk_10.
void sub_40C60(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8)
{
    type_154C0_80 *local_20;
    AIData *var_1C;
    RwInt32 var18;
    RwReal stk_14;
    RwInt32 l10;
    RwInt32 local_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    local_C = 0;
    lv_8 = 0;
    var_4 = 0;
    if (arg_4 != arg_0) {
        l10 = arg_4 == arg_0->vf_120()->get_unk_1374();
        if (sub_41420(arg_0, arg_4, arg_8) != 0) {
            if (sub_414F0(arg_0, arg_4, arg_8->unk_08, &stk_14) != 0) {
                var18 = 0;
                if (l10 != 0 || sub_41200(arg_0, arg_4, arg_8, &var18) != 0) {
                    if (l10 != 0 || stk_14 < flt_427680 || arg_8->unk_18 == 0) {
                        if (sub_41300(arg_0, arg_4) != 0) {
                            if (sub_413E0(arg_0, arg_4) != 0) {
                                if (sub_41AD0(arg_0, arg_4) != 0)
                                    local_C = 1;
                            } else if (sub_421C0(arg_0, arg_4) != 0) {
                                var_4 = 1;
                                if (sub_415E0(arg_0, arg_4) != 0)
                                    local_C = 1;
                            }
                        } else {
                            lv_8 = 1;
                        }
                    } else {
                        lv_8 = 1;
                    }
                } else if (var18 != 0) {
                    if (sub_413E0(arg_0, arg_4) != 0) {
                        local_C = 1;
                    } else {
                        var_4 = 1;
                        if (sub_415E0(arg_0, arg_4) != 0)
                            local_C = 1;
                    }
                }
            }
            if (lv_8 == 0) {
                if (local_C != 0)
                    sub_425A0(arg_0, arg_4, arg_8);
                else
                    sub_426E0(arg_0, arg_4, arg_8, var_4);
            } else {
                var_1C = arg_0->vf_120();
                local_20 = var_1C->sub_16ED0(arg_4, 0);
                if (local_20 != 0 && (local_20->unk_04 & 1) == 0)
                    local_20->unk_10 = dword_43983C + local_20->unk_10;
            }
        }
    }
}

// match: sub_40EA0 @ 0x00040EA0
// sp-match: sub_40EA0 @ 0x00030BB0
// After a look for the registration arg_4: counts its countdown down
// (wrapping to dword_42767C), with arg_8 has arg_0's AI object update
// (sub_213B0), and stamps the time.
void sub_40EA0(type_3D3548 *arg_0, type_409A0 *arg_4, RwInt32 arg_8)
{
    AIData *var_4;

    arg_4->unk_18--;
    if (arg_4->unk_18 < 0)
        arg_4->unk_18 = (RwInt8)dword_42767C;
    if (arg_8 != 0) {
        var_4 = arg_0->vf_120();
        if (var_4 != 0)
            var_4->sub_213B0(0);
    }
    arg_4->unk_14 = RWS::Time::GetTime();
}

// match: sub_40F00 @ 0x00040F00
// sp-match: sub_40F00 @ 0x00031D80
// dword_4398B0's first callback: the registration arg_4's entity looks at
// its tracked entity.
RwInt32 sub_40F00(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    type_365A0 l14;
    type_409A0 *var_10;
    type_3D3548 *ebp_C;
    type_3D2E7C *v8;
    type_3D3548 *var_4;

    l14.unk_00 = arg_4;
    var_10 = sub_42960(l14);
    v8 = arg_0->vf_024();
    var_4 = v8->sub_71300();
    sub_40BD0(var_4, var_10);
    ebp_C = var_4->vf_120()->get_unk_1374();
    if (ebp_C != 0) {
        dword_439834++;
        sub_40C60(var_4, ebp_C, var_10);
    }
    sub_40EA0(var_4, var_10, 0);
    return 1;
}

// match: sub_40FB0 @ 0x00040FB0
// sp-match: sub_40FB0 @ 0x00031E00
// dword_439840's first callback: the registration arg_4's entity, when its
// AI object has flag 5 of unk_49C, looks at every entity of the lists its
// sides (unk_2C bits 0 and 1) watch.
RwInt32 sub_40FB0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    type_3D3548 *bp_2C;
    type_3D3548 *local_28;
    type_3D3548 *local_24;
    type_3D3548 *local_20;
    type_3D3548 *var_1C;
    type_365A0 var18;
    type_409A0 *stk_14;
    type_3D3548 *l10;
    type_3D2E7C *local_C;
    type_3D3548 *lv_8;
    AIData *var_4;

    var18.unk_00 = arg_4;
    stk_14 = sub_42960(var18);
    local_C = arg_0->vf_024();
    lv_8 = local_C->sub_71300();
    sub_40BD0(lv_8, stk_14);
    l10 = lv_8->vf_120()->get_unk_1374();
    var_4 = lv_8->vf_120();
    if (((var_4->unk_49C >> 5) & 1) != 0) {
        dword_439830++;
        for (var_1C = dword_4B8600[14].unk_00; var_1C != 0; var_1C = var_1C->unk_10) {
            if (l10 != var_1C && var_1C->vf_120() != 0)
                sub_40C60(lv_8, var_1C, stk_14);
        }
        if ((lv_8->unk_2C & 1) != 0) {
            for (local_20 = dword_4B8600[9].unk_00; local_20 != 0; local_20 = local_20->unk_10) {
                if (l10 != local_20 && local_20->vf_120() != 0)
                    sub_40C60(lv_8, local_20, stk_14);
            }
            for (local_24 = dword_4B8600[0].unk_00; local_24 != 0; local_24 = local_24->unk_10) {
                if (l10 != local_24 && local_24->vf_120() != 0)
                    sub_40C60(lv_8, local_24, stk_14);
            }
        }
        if (((lv_8->unk_2C >> 1) & 1) != 0) {
            for (local_28 = dword_4B8600[10].unk_00; local_28 != 0; local_28 = local_28->unk_10) {
                if (l10 != local_28 && local_28->vf_120() != 0)
                    sub_40C60(lv_8, local_28, stk_14);
            }
            for (bp_2C = dword_4B8600[1].unk_00; bp_2C != 0; bp_2C = bp_2C->unk_10) {
                if (l10 != bp_2C && bp_2C->vf_120() != 0)
                    sub_40C60(lv_8, bp_2C, stk_14);
            }
        }
    }
    sub_40EA0(lv_8, stk_14, 1);
    return 1;
}

// match: sub_41200 @ 0x00041200
// sp-match: sub_41200 @ 0x00030BF0
// Whether arg_0 looks at arg_4 now: 0 when arg_4 sees further, or as far
// with a lower rank (unk_244), storing whether arg_4 sees arg_0 in *arg_C.
RwInt32 sub_41200(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8, RwInt32 *arg_C)
{
    RwReal varC;
    type_154C0_80 *local_8;

    varC = arg_0->vf_10C();
    RwReal var_4 = arg_4->vf_10C();
    if (!(arg_8->unk_04 != 3))
        return 1;
    if (arg_4->vf_120() == 0 || arg_4->vf_00C() != 0)
        return 1;
    local_8 = arg_4->vf_120()->sub_16ED0(arg_0, 0);
    if (local_8 == 0)
        return 1;
    if (varC < var_4) {
        *arg_C = (local_8->unk_04 >> 1) & 1;
        return 0;
    }
    if (varC > var_4)
        return 1;
    else
    {
        if (!(arg_0->unk_244 <= arg_4->unk_244)) {
            *arg_C = (local_8->unk_04 >> 1) & 1;
            return 0;
        }
        return 1;
    }
}

// match: sub_41300 @ 0x00041300
// sp-match: sub_41300 @ 0x00030CA0
// Whether arg_0 looks at arg_4 this time: always at its tracked entity or at
// one it does not see; else every other time (the record's unk_08).
RwInt32 sub_41300(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    type_154C0_80 *varC;
    RwInt32 local_8;
    AIData *var_4;

    var_4 = arg_0->vf_120();
    varC = var_4->sub_16ED0(arg_4, 0);
    if (varC == 0 || ((varC->unk_04 >> 1) & 1) == 0)
        return 1;
    if (arg_4 == var_4->unk_1374.sub_D4910())
        return 1;
    local_8 = varC->unk_08 == 0;
    varC->unk_08 = varC->unk_08 == 0;
    return local_8;
}

// match: sub_41390 @ 0x00041390
// sp-match: sub_41390 @ 0x00031670
// The schedules' second callback: ends the registration arg_4.
RwInt32 sub_41390(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    type_409A0 *var_4;
    type_365A0 local_8;

    local_8.unk_00 = arg_4;
    var_4 = sub_42960(local_8);
    if (var_4 != 0) {
        sub_42930(local_8);
        dword_43988C.sub_16C710(var_4);
    }
    return 1;
}

// match: sub_413E0 @ 0x000413E0
// sp-match: sub_413E0 @ 0x00030D00
RwInt32 sub_413E0(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    AIData *local_8;
    RwInt32 var_4;

    var_4 = 0;
    local_8 = arg_0->vf_120();
    if (local_8 != 0)
        var_4 = local_8->sub_238E0(arg_4);
    return var_4;
}

// match: sub_41420 @ 0x00041420
// sp-match: sub_41420 @ 0x00030D30
// Whether the registration arg_8 lets arg_0 look at arg_4: test 2 for an
// entity of another side, test 3 for the registration's own object.
RwInt32 sub_41420(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8)
{
    type_3D2E7C *varC;
    RwUInt32 local_8;
    RwUInt32 var_4;

    switch (arg_8->unk_04) {
    case 2:
        var_4 = arg_0->unk_2C & 7;
        local_8 = arg_4->unk_2C & 7;
        return ((var_4 | 4) ^ (local_8 | 4)) != 0 && local_8 != 0 && local_8 != 4;
    case 3:
        varC = arg_4->vf_098();
        // The handle through its struct's conversion: single player (SP 0x30D58)
        // then reuses ecx for the serial.
        return varC != 0 && varC->get_unk_04_h() == arg_8->unk_0C
            && varC->get_unk_24() == arg_8->unk_10;
    }
    return 1;
}

// match: sub_414F0 @ 0x000414F0
// sp-match: sub_414F0 @ 0x00030DA0
// Whether arg_4 is within the squared distance arg_8 of arg_0, storing the
// squared distance in *arg_C; 0 when either has no frame.
RwInt32 sub_414F0(type_3D3548 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwReal *arg_C)
{
    RwV3d *stk_18;
    RwReal l14;
    RwV3d var_10;
    RwV3d *var_4;

    if (arg_0->get_unk_340() == 0 || arg_4->get_unk_340() == 0)
        return 0;
    var_4 = RwMatrixGetPos(RwFrameGetLTM(arg_0->get_unk_340()));
    stk_18 = RwMatrixGetPos(RwFrameGetLTM(arg_4->get_unk_340()));
    RwV3dSub(&var_10, var_4, stk_18);
    l14 = RwV3dDotProduct(&var_10, &var_10);
    *arg_C = l14;
    return l14 <= arg_8;
}

// match: ?sub_415E0@@YAHPAUtype_3D3548@@0@Z @ 0x000415E0
// sp-match: ?sub_415E0@@YAHPAUtype_3D3548@@0@Z @ 0x00030E30
RwInt32 sub_415E0(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    RwMatrix var_40;
    RwMatrix var_80;
    RwV3d *var_84;
    RwV3d *var_88;
    RwV3d *var_8C;
    RwV3d var_98;
    RwV3d var_A4;
    RwV3d var_B0;
    RwV3d var_BC;
    RwReal var_C0;
    RwV3d *var_C4;

    arg_0->vf_104(&var_40);
    arg_4->vf_104(&var_80);
    var_84 = &var_40.at;
    var_88 = &var_40.right;
    var_8C = &var_40.pos;
    var_98 = var_80.pos;
    RwV3dSubMacro(&var_A4, &var_98, var_8C);
    RwV3dScaleMacro(&var_B0, var_88, RwV3dDotProductMacro(&var_A4, var_88));
    RwV3dScaleMacro(&var_BC, var_84, RwV3dDotProductMacro(&var_A4, var_84));
#ifdef CODFH_SP // shape: the length test sums z first (SP 0x30F33 fst/fmul of z)
    RwV3dAddMacro(&var_B0, &var_B0, &var_BC);
    if (var_B0.z * var_B0.z + var_B0.x * var_B0.x + var_B0.y * var_B0.y == 0.0f)
#else
    RwV3dAddMacro(&var_B0, &var_B0, &var_BC);
    // An empty first branch gives the image's jp-to-else test.
    if (RwV3dDotProductMacro(&var_B0, &var_B0) == 0.0f)
#endif
    {
    }
    else
    {
        RwV3dNormalize(&var_B0, &var_B0);
    }
    var_C0 = RwV3dDotProductMacro(&var_B0, var_84);
    if (arg_0->vf_0FC() > var_C0)
    {
        return 0;
    }
    var_C4 = &var_40.up;
    RwV3dScaleMacro(&var_B0, var_C4, RwV3dDotProductMacro(&var_A4, var_C4));
    RwV3dAddMacro(&var_B0, &var_B0, &var_BC);
    RwV3dNormalize(&var_B0, &var_B0);
    var_C0 = (var_C0 = RwV3dDotProductMacro(&var_B0, var_84)) < 0.0f ? -var_C0 : var_C0;
    var_C0 = var_C0; // the image copies it onto itself
    if (arg_0->vf_100() > var_C0)
    {
        return 0;
    }
    return 1;
}

// match: sub_41AD0 @ 0x00041AD0
// sp-match: sub_41AD0 @ 0x00031B70
// Whether arg_0 sees arg_4 from its AI object's node (unk_F60, sub_41B20).
RwInt32 sub_41AD0(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4 != 0)
        return sub_41B20(arg_0, arg_4, var_4->get_unk_F60());
    return 0;
}

// match: sub_41B20 @ 0x00041B20
// sp-match: sub_41B20 @ 0x000316A0
// Whether arg_0 sees arg_4 from the node arg_8: the line from the node's
// eye point (sub_F8FE0, through the node's orientation and position) to
// arg_4's aim point (vf_110) is blocked by no collision world's line test
// (sub_91F40) nor atomic (sub_42350). For a target that is a player
// (vf_00C) every blocker is measured: the nearest distance goes to the AI
// object's unk_139C, and unk_534 is set when it is beyond 0.9.
RwInt32 sub_41B20(type_3D3548 *arg_0, type_3D3548 *arg_4, type_F8350 *arg_8)
{
    RwInt32 var_4;
    AIData *var_8;
    RwV3d var_14;
    RwMatrix var_60;
    RwV3d var_6C;
    RwMatrix var_B0;
    RwV3d var_F0;
    RpIntersection var_10C;
    type_42210 var_11C;
    RwReal var_120;
    RwV3d var_12C;
    RwInt32 var_130;
    type_4E5D30 *var_134;
    type_91F40 var_16C;
    RwInt32 var_170;
    type_4E5D30 *var_174;

    var_4 = 0;
    var_8 = arg_0->vf_120();
    if (var_8)
    {
        var_14.x = 0.0f;
        var_14.y = 0.0f;
        var_14.z = 0.0f;
        arg_0->vf_104(&var_60);
        arg_4->vf_110(&var_6C, arg_0, 1);
        sub_F8FE0(arg_8, &var_14, 0);
        RwMatrixSetIdentityMacro(&var_B0);
        RtQuatConvertToMatrix(&arg_8->unk_1C, &var_B0);
        var_B0.pos = arg_8->unk_10;
        sub_1414C0(&var_F0, &var_14, &var_B0);
        var_10C.type = rpINTERSECTLINE;
        var_10C.t.line.start = var_F0;
        var_10C.t.line.end = var_6C;
        var_11C.unk_00 = arg_0;
        var_11C.unk_04 = arg_4;
        var_11C.unk_0C = 0;
        var_11C.unk_0D = arg_4->vf_00C() ? 1 : 0;
        var_11C.unk_08 = 1.0e37f;
        var_120 = 1.0e37f;
        var_4 = 1;
        RwV3dSubMacro(&var_12C, &var_10C.t.line.end, &var_10C.t.line.start);
        if (RwV3dDotProductMacro(&var_12C, &var_12C) > 0.001f)
        {
            for (var_130 = 0; var_130 < 4; var_130++)
            {
                var_134 = &dword_4E5D30[var_130];
                if (var_134->get_unk_00() != 0 && var_134->get_unk_28() != 0
                    && sub_91F40(var_134->get_unk_28(), &var_10C.t.line, &var_16C, var_11C.unk_0D, 0x420000, 1)) // not an address: line-test flags
                {
                    var_4 = 0;
                    if (var_11C.unk_0D)
                    {
                        if (var_16C.unk_00 && var_16C.unk_04 < var_120)
                        {
                            var_120 = var_16C.unk_04;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if (var_4 || var_11C.unk_0D)
            {
                for (var_170 = 0; var_170 < 4; var_170++)
                {
                    var_174 = &dword_4E5D30[var_170];
                    if (var_174->get_unk_00() != 0 && var_174->get_unk_28() != 0)
                    {
                        RpWorldForAllAtomicIntersections(var_174->get_unk_28(), &var_10C, sub_42350, &var_11C);
                        if (var_11C.unk_0C)
                        {
                            var_4 = 0;
                            if (var_11C.unk_0D)
                            {
                                if (var_11C.unk_08 < var_120)
                                {
                                    var_120 = var_11C.unk_08;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if (var_11C.unk_0D)
            {
                var_8->unk_139C = var_120;
                var_8->unk_534 = var_120 > 0.9f ? 1 : 0;
            }
        }
    }
    return var_4;
}

// match: sub_421C0 @ 0x000421C0
// sp-match: sub_421C0 @ 0x00031BA0
// Whether nothing blocks the line from arg_0's eye point to arg_4's point
// for it (sub_42210).
RwInt32 sub_421C0(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    RwV3d var_18;
    RwV3d var_C;

    arg_0->vf_108(&var_18);
    arg_4->vf_110(&var_C, arg_0, 1);
    return sub_42210(&var_18, &var_C, arg_0, arg_4);
}

// match: sub_42210 @ 0x00042210
// sp-match: sub_42210 @ 0x00031A80
// Whether nothing blocks the line from arg_0 to arg_4: no line test hit in a
// live collision world (sub_91F40), then no atomic other than the entities
// arg_8's and arg_C's (sub_42350).
RwInt32 sub_42210(RwV3d *arg_0, RwV3d *arg_4, type_3D3548 *arg_8, type_3D3548 *arg_C)
{
    type_4E5D30 *var_3C;
    RwInt32 v38;
    type_4E5D30 *v34;
    RwInt32 v30;
    RpIntersection var_2C;
    type_42210 local_10;

    var_2C.type = rpINTERSECTLINE;
    var_2C.t.line.start = *arg_0;
    var_2C.t.line.end = *arg_4;
    local_10.unk_00 = arg_8;
    local_10.unk_04 = arg_C;
    local_10.unk_0C = 0;
    local_10.unk_0D = 0;
    for (v30 = 0; v30 < 4; v30++) {
        v34 = &dword_4E5D30[v30];
        if (v34->get_unk_00() != 0 && v34->get_unk_28() != 0
                && sub_91F40(v34->get_unk_28(), &var_2C.t.line, 0, 0, 0x420000, 1) != 0) // not an address: line-test flags
            return 0;
    }
    for (v38 = 0; v38 < 4; v38++) {
        var_3C = &dword_4E5D30[v38];
        if (var_3C->get_unk_00() != 0 && var_3C->get_unk_28() != 0) {
            RpWorldForAllAtomicIntersections(var_3C->get_unk_28(), &var_2C, sub_42350, &local_10);
            if (local_10.unk_0C != 0)
                return 0;
        }
    }
    return 1;
}

// match: sub_42350 @ 0x00042350
// sp-match: sub_42350 @ 0x00031090
// sub_42210's atomic callback: an atomic blocks unless it belongs to either
// entity, to one they are attached to (vf_1F8) or share with (vf_200,
// vf_010), or to an entity without flag 2 of unk_28; its triangles decide
// (sub_42580).
RpAtomic *sub_42350(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10)
{
    type_42210 *local_8;
    type_3D3548 *var_4;

    local_8 = (type_42210 *)arg_10;
    var_4 = sub_FB960(arg_8);
    if (!RWS::RpAtomicCollisionProperties::GetIsSolid(*arg_8))
        return arg_8;
    if ((sub_FB9C0(arg_8) & 8) != 0)
        return arg_8;
    if (var_4 != 0) {
        if (var_4 == local_8->unk_00 || var_4 == local_8->unk_04)
            return arg_8;
        if (((var_4->unk_28 >> 2) & 1) == 0)
            return arg_8;
        if (local_8->unk_04 != 0) {
            if (var_4->vf_1F8(0) == local_8->unk_04)
                return arg_8;
            if (local_8->unk_04->vf_1F8(0) == var_4)
                return arg_8;
            if (local_8->unk_04->vf_200() != 0 && local_8->unk_04->vf_200() == var_4->vf_010())
                return arg_8;
            if (var_4->vf_200() != 0 && var_4->vf_200() == local_8->unk_04->vf_010())
                return arg_8;
        }
        if (RpAtomicGetGeometry(arg_8) != 0) {
            RpAtomicForAllIntersections(arg_8, arg_0, sub_42580, arg_10);
            if (local_8->unk_0C != 0) {
                if (arg_C < local_8->unk_08)
                    local_8->unk_08 = arg_C;
                return local_8->unk_0D != 0 ? arg_8 : 0;
            }
            return arg_8;
        }
        return arg_8;
    }
    if (RpAtomicGetGeometry(arg_8) != 0
            && (RpAtomicForAllIntersections(arg_8, arg_0, sub_42580, arg_10), local_8->unk_0C != 0)) {
        if (arg_C < local_8->unk_08)
            local_8->unk_08 = arg_C;
        return local_8->unk_0D != 0 ? arg_8 : 0;
    }
    return arg_8;
}

// match: sub_42580 @ 0x00042580
// sp-match: sub_42580 @ 0x00031080
// sub_42350's triangle callback: a hit.
RpCollisionTriangle *sub_42580(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8,
                               void *arg_C)
{
    type_42210 *var_4;

    var_4 = (type_42210 *)arg_C;
    var_4->unk_0C = 1;
    return 0;
}

// match: sub_425A0 @ 0x000425A0
// sp-match: sub_425A0 @ 0x00031210
// arg_0 sees arg_4: tells it ("TargetSeen" the first time for its tracked
// entity, "CanPotentiallySeeTarget"), and marks the record seen at arg_4's
// position.
void sub_425A0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8)
{
    type_3D2E7C *var_10;
    RwUInt32 ebp_C;
    type_154C0_80 *v8;
    AIData *var_4;

    var_4 = arg_0->vf_120();
    v8 = var_4->sub_16ED0(arg_4, 0);
    if (v8 == 0)
        return;
    if (var_4->unk_1374.sub_D4910() == arg_4) {
        var_10 = arg_4->vf_098();
        if (var_10 != 0)
            ebp_C = var_10->get_unk_04();
        else
            ebp_C = 0;
        if ((v8->unk_04 & 1) == 0) {
            var_4->unk_520 = 1;
            sub_6B5F0("TargetSeen", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)(&ebp_C), 1, true, false);
        }
        if (((v8->unk_04 >> 1) & 1) == 0)
            sub_6B5F0("CanPotentiallySeeTarget", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)(&ebp_C), 1, true, false);
    }
    v8->unk_04 |= 1;
    v8->unk_04 |= 2;
    v8->unk_10 = 0.0f;
    v8->unk_14 = *arg_4->sub_CD550();
}

// match: sub_426E0 @ 0x000426E0
// sp-match: sub_426E0 @ 0x00031310
// arg_0 does not see arg_4 (arg_C: it could): tells it about its tracked
// entity ("TargetLostLOS", "CanPotentiallySeeTarget",
// "CannotPotentiallySeeTarget") and counts the time on the record.
void sub_426E0(type_3D3548 *arg_0, type_3D3548 *arg_4, type_409A0 *arg_8, RwInt32 arg_C)
{
    RwBool stk_18;
    type_3D2E7C *l14;
    RwUInt32 var_10;
    type_154C0_80 *ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    var_4 = arg_0->vf_120();
    ebp_C = var_4->sub_16ED0(arg_4, 0);
    if (ebp_C == 0)
        return;
    v8 = var_4->unk_1374.sub_D4910();
    if (v8 == arg_4) {
        l14 = arg_4->vf_098();
        if (l14 != 0)
            var_10 = l14->get_unk_04();
        else
            var_10 = 0;
        stk_18 = var_4->sub_18F80(arg_4, ebp_C);
        if ((ebp_C->unk_04 & 1) != 0 && stk_18 == 0)
            sub_6B5F0("TargetLostLOS", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)(&var_10), 1, true, false);
        if (((ebp_C->unk_04 >> 1) & 1) == 0 && arg_C != 0)
            sub_6B5F0("CanPotentiallySeeTarget", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)(&var_10), 1, true, false);
        if (((ebp_C->unk_04 >> 1) & 1) != 0 && arg_C == 0 && stk_18 == 0)
            sub_6B5F0("CannotPotentiallySeeTarget", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)(&var_10), 1, true, false);
    }
    ebp_C->unk_04_1 = arg_C;
    ebp_C->unk_04_0 = 0;
    ebp_C->unk_10 = dword_43983C + ebp_C->unk_10;
}

// match: sub_42870 @ 0x00042870
// sp-match: sub_42870 @ 0x00031440
// Gives the registration arg_0 the first free entry of dword_439618, with a
// new serial.
RwUInt32 sub_42870(type_409A0 *arg_0)
{
    RwInt32 var_4;
    RwInt32 v8;
    type_365A0 varC;

    v8 = 0;
    for (var_4 = 1; var_4 < 0x42; var_4++) {
        if (dword_439618[var_4].unk_00.unk_00 == 0 && dword_439618[var_4].unk_04 == 0) {
            if (dword_439838 == 0)
                dword_439838 = 1;
            dword_439618[var_4].unk_00.unk_00_lo = var_4;
            varC.unk_00_lo = var_4;
            dword_439618[var_4].unk_00.unk_02 = dword_439838;
            varC.unk_02 = dword_439838;
            dword_439618[var_4].unk_04 = arg_0;
            v8 = 1;
            dword_439838++;
            break;
        }
    }
    return varC.unk_00;
}

// match: sub_42930 @ 0x00042930
// sp-match: sub_42930 @ 0x000314B0
// Frees the handle arg_0's entry.
void sub_42930(type_365A0 arg_0)
{
    dword_439618[arg_0.unk_00_lo].unk_00.unk_00 = 0;
    dword_439618[arg_0.unk_00_lo].unk_04 = 0;
}

// match: sub_42960 @ 0x00042960
// sp-match: sub_42960 @ 0x000314D0
// The registration of the handle arg_0, 0 when it is stale.
type_409A0 *sub_42960(type_365A0 arg_0)
{
    if (dword_439618[arg_0.unk_00_lo].unk_00.unk_00 == arg_0.unk_00)
        return dword_439618[arg_0.unk_00_lo].unk_04;
    return 0;
}
