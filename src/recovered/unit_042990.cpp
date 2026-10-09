// The action queue ("m_actionPool", sub_42990): its setup, restart and
// shutdown, the records' pool, queueing (sub_42AF0), the tick that runs the
// queued actions (sub_42C50) and dropping a sender's actions (sub_42E00). It
// follows the Vision Scheduler's unit and precedes sub_42F40's. Its original
// file name is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/alfasched.h"
#include "types/type_3D2E7C.h"
#include "types/type_42AF0.h"
#include "types/type_67620.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004398FC
type_42AF0 *dword_4398FC;
// 0x00439900
type_42AF0 *dword_439900;
// 0x00439904
type_42AF0 *dword_439904;
// 0x00439908
RwUInt8 byte_439908;
// 0x0043990C
type_42AF0 *dword_43990C;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_439910;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0N@KAEPMLOM@m_actionPool?$AA@ @ 0x003CE93C
// match: ??_C@_04HOPIBOHF@Tick?$AA@ @ 0x003CE94C
// match: .CRT$XCU+0 @ 0x00426D98

// match: _$E1 @ 0x003098F0
// match: _$E2 @ 0x0030DD00
// sp-match: _$E2 @ 0x0021E130
// sp-match: _$E1 @ 0x0021C370

void sub_42A10();
type_42AF0 *sub_42AB0();
void sub_42AD0(type_42AF0 *arg_0);
void sub_42D40(type_42AF0 *arg_0);
void sub_42D70(type_42AF0 *arg_0);
void sub_42DA0(type_42AF0 *arg_0);
void sub_42DE0(type_42AF0 *arg_0);
// sub_6BDC0 runs the object arg_0 and sub_6B890 frees the handle arg_0
// (kind-16 actions, sub_42DA0 and sub_42DE0); only their widths are known.
struct type_42E00;
void sub_6BDC0(type_42E00 *arg_0);
void sub_6B890(RwUInt32 arg_0);

// match: sub_42990 @ 0x00042990
// sp-match: sub_42990 @ 0x000320B0
void sub_42990()
{
    dword_439910.sub_16C2C0(0x3E8, 0x10, "m_actionPool", 4, 0);
    dword_439904 = 0;
    dword_439900 = 0;
    dword_43990C = 0;
    dword_4398FC = 0;
    byte_439908 = 0;
}

// match: sub_429E0 @ 0x000429E0
// sp-match: sub_429E0 @ 0x00032440
void sub_429E0()
{
    sub_42A10();
}

// match: sub_429F0 @ 0x000429F0
// sp-match: sub_429F0 @ 0x00032450
void sub_429F0()
{
    sub_42A10();
    dword_439910.sub_16C4D0(1);
}

// match: sub_42A10 @ 0x00042A10
// sp-match: sub_42A10 @ 0x00032320
// Drops every queued action (sub_42D70) and empties the queue.
void sub_42A10()
{
    type_42AF0 *var_4;

    if (dword_439904 != 0) {
        dword_4398FC = dword_439904;
        dword_43990C = dword_439900;
        while (dword_4398FC != 0) {
            var_4 = dword_4398FC->unk_0C;
            sub_42D70(dword_4398FC);
            dword_4398FC->unk_0C = 0;
            sub_42AD0(dword_4398FC);
            dword_4398FC = var_4;
        }
    }
    byte_439908 = 0;
    dword_4398FC = 0;
    dword_43990C = 0;
    dword_439904 = 0;
    dword_439900 = 0;
}

// match: sub_42AB0 @ 0x00042AB0
// sp-match: sub_42AB0 @ 0x000320F0
type_42AF0 *sub_42AB0()
{
    type_42AF0 *var_4;

    var_4 = (type_42AF0 *)dword_439910.sub_16C5A0(0);
    return var_4;
}

// match: sub_42AD0 @ 0x00042AD0
// sp-match: sub_42AD0 @ 0x00032100
void sub_42AD0(type_42AF0 *arg_0)
{
    dword_439910.sub_16C710(arg_0);
}

// match: sub_42AF0 @ 0x00042AF0
// sp-match: sub_42AF0 @ 0x00032110
// Queues an action of kind arg_4 with the handle arg_8 from arg_0: while a
// tick runs and arg_C is set, behind the running action (arg_10) or at the
// tick's end; else at the head (arg_10) or the tail of the queue.
void sub_42AF0(type_3D2E7C *arg_0, RwInt32 arg_4, RwUInt32 arg_8, bool arg_C, bool arg_10)
{
    type_42AF0 *var_4;

    var_4 = sub_42AB0();
    var_4->unk_00 = arg_4;
    var_4->unk_04 = arg_0 != 0 ? arg_0->get_unk_04() : 0;
    var_4->unk_08 = arg_8;
    var_4->unk_0C = 0;
    if (arg_C != 0 && byte_439908 != 0) {
        if (arg_10 != 0) {
            if (dword_4398FC == dword_43990C) {
                if (dword_439900 == dword_43990C)
                    dword_439900 = var_4;
                dword_43990C = var_4;
            }
            var_4->unk_0C = dword_4398FC->unk_0C;
            dword_4398FC->unk_0C = var_4;
        } else {
            if (dword_439900 == dword_43990C)
                dword_439900 = var_4;
            var_4->unk_0C = dword_43990C->unk_0C;
            dword_43990C->unk_0C = var_4;
            dword_43990C = var_4;
        }
    } else if (arg_10 != 0) {
        var_4->unk_0C = dword_439904;
        dword_439904 = var_4;
        if (dword_439900 == 0)
            dword_439900 = var_4;
    } else {
        if (dword_439900 != 0)
            dword_439900->unk_0C = var_4;
        dword_439900 = var_4;
        if (dword_439904 == 0)
            dword_439904 = var_4;
    }
}

// match: sub_42C50 @ 0x00042C50
// sp-match: sub_42C50 @ 0x00032390
// The tick, arg_0 its time: sends "Tick" when dword_4B8710 is set, then runs
// the actions queued before it (sub_42D40), freeing each.
void sub_42C50(RwReal arg_0)
{
    type_42AF0 *local_C;
    RwReal var_8;
    RwUInt8 var_1;

    if (dword_4B8710 != 0) {
        var_8 = arg_0;
        sub_6B5F0("Tick", 0, 0, 0, (RwInt32 *)&var_8, 1, true, false);
    }
    if (dword_439904 == 0)
        return;
    byte_439908 = 1;
    dword_4398FC = dword_439904;
    dword_43990C = dword_439900;
    var_1 = 0;
    while (var_1 == 0) {
        sub_42D40(dword_4398FC);
        local_C = dword_4398FC->unk_0C;
        sub_42AD0(dword_4398FC);
        if (dword_4398FC == dword_43990C) {
            dword_439904 = local_C;
            var_1 = 1;
        } else {
            dword_4398FC = local_C;
        }
    }
    if (dword_439900 == dword_43990C)
        dword_439900 = 0;
    byte_439908 = 0;
    dword_4398FC = 0;
    dword_43990C = 0;
}

// match: sub_42D40 @ 0x00042D40
// sp-match: sub_42D40 @ 0x00032230
// Runs the action arg_0.
void sub_42D40(type_42AF0 *arg_0)
{
    switch (arg_0->unk_00) {
    case 0x10:
        sub_42DA0(arg_0);
    }
}

// match: sub_42D70 @ 0x00042D70
// sp-match: sub_42D70 @ 0x00032250
// Drops the action arg_0.
void sub_42D70(type_42AF0 *arg_0)
{
    switch (arg_0->unk_00) {
    case 0x10:
        sub_42DE0(arg_0);
    }
}

// match: sub_42DA0 @ 0x00042DA0
// sp-match: sub_42DA0 @ 0x00032200
void sub_42DA0(type_42AF0 *arg_0)
{
    type_67620 *var_4;
    RwUInt32 local_8;

    local_8 = arg_0->unk_08;
    var_4 = sub_67620(local_8);
    sub_6BDC0((type_42E00 *)var_4);
    sub_6B890(local_8);
}

// match: sub_42DE0 @ 0x00042DE0
// sp-match: sub_42DE0 @ 0x00032220
void sub_42DE0(type_42AF0 *arg_0)
{
    RwUInt32 var_4;

    var_4 = arg_0->unk_08;
#ifdef CODFH_SP
    // shape: retain the target's second field read before releasing the handle.
    if (var_4 == arg_0->unk_08)
#endif
    sub_6B890(var_4);
}

// match: sub_42E00 @ 0x00042E00
// sp-match: sub_42E00 @ 0x00032270
// Drops the kind-16 actions not yet run whose object is for arg_0 with the
// id arg_4 (and has unk_12 clear).
void sub_42E00(type_67620 *arg_0, RwInt32 arg_4)
{
    type_42AF0 *var_1C;
    RwUInt32 var18;
    type_67620 *stk_14;
    type_42E00 *l10;
    type_42AF0 *local_C;
    type_42AF0 *lv_8;
    type_42AF0 **var_4;

    local_C = 0;
    if (dword_439904 == 0)
        return;
    if (byte_439908 != 0) {
        var_4 = &dword_4398FC->unk_0C;
        lv_8 = dword_4398FC->unk_0C;
        local_C = dword_4398FC;
    } else {
        var_4 = &dword_439904;
        lv_8 = dword_439904;
    }
    while (lv_8 != 0) {
        if (lv_8->unk_00 == 0x10) {
            var18 = lv_8->unk_08;
            l10 = (type_42E00 *)sub_67620(var18);
            stk_14 = sub_67620(l10->unk_04);
            if (l10->unk_12 == 0 && stk_14 == arg_0 && l10->unk_00->unk_04 == arg_4) {
                *var_4 = lv_8->unk_0C;
                if (lv_8 == dword_439900)
                    dword_439900 = local_C;
                if (lv_8 == dword_43990C)
                    dword_43990C = local_C;
                var_1C = lv_8->unk_0C;
                sub_42D70(lv_8);
                sub_42AD0(lv_8);
                lv_8 = var_1C;
            } else {
                var_4 = &lv_8->unk_0C;
                local_C = lv_8;
                lv_8 = lv_8->unk_0C;
            }
        }
    }
}
