// The AIHearing class ("Somebody forgot to unregister in the AIHearing
// Class!", sub_3C290): its setup (sub_3C1D0), flush and shutdown, like the
// schedulers' before it, then the sound and listener lists. It follows the
// kind-5 object's unit and precedes type_3CE6D0's own methods (from
// sub_3CA10). Its original file name is not in the image, so it is named
// for its start address.

#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/alfasched.h"
#include "types/type_3C540.h"
#include "types/type_3D2E7C.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/type_10F710.h"
#ifdef CODFH_DRAW_TRIGGERS
// (port/src/debug/trigdraw.cpp: the debug tools' hearing view)
void TrigDrawNoiseMade(const RwV3d *pv, RwInt32 nKind, RwInt32 nClass, RwReal fRange, RwInt32 bLasting);
void TrigDrawNoiseHeard(const void *pHearer, const RwV3d *pvFrom, RwInt32 nKind);
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE658
extern const RwReal flt_3CE658 = 16.666666f;
// 0x0043925C
type_3C720 *dword_43925C;
// 0x00439260
type_3C540 *dword_439260;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_439264;
type_16C2A0 dword_439284;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE658@@3MB @ 0x003CE658
// match: ??_C@_0BA@MEPGJLLC@m_freeLongSound?$AA@ @ 0x003CE65C
// match: ??_C@_0BE@KMCEKBIA@m_freeHearingParams?$AA@ @ 0x003CE66C
// match: ??_C@_0DG@OJBJNDPI@Somebody?5forgot?5to?5unregister?5in@ @ 0x003CE680
// match: ??_C@_0BD@OIJJJDOM@AIAction_HearSound?$AA@ @ 0x003CE6B8
// match: .CRT$XCU+0 @ 0x00426D78
// match: .CRT$XCU+4 @ 0x00426D7C

// match: _$E2 @ 0x003097F0
// match: _$E3 @ 0x0030DC80
// match: _$E5 @ 0x00309810
// match: _$E6 @ 0x0030DC90
// sp-match: _$E6 @ 0x0021E0C0
// sp-match: _$E2 @ 0x0021C270
// sp-match: _$E5 @ 0x0021C290
// sp-match: _$E3 @ 0x0021E0B0

void sub_3C290();
void sub_3C540(type_3D3548 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10,
               RwReal arg_14, RwInt32 arg_18, RwReal arg_1C);
void sub_3C7D0(type_3C720 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
               RwInt32 arg_10, RwReal arg_14, RwInt32 arg_18);
RwInt32 sub_3C980(type_3D3548 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwInt32 arg_C);

// match: sub_3C1D0 @ 0x0003C1D0
// sp-match: sub_3C1D0 @ 0x0002DBF0
void sub_3C1D0()
{
#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
    // (the port's debug tools: room for the bots' listeners, port/src/debug/trigtools.cpp)
    dword_439264.sub_16C2C0(96, 0xC, "m_freeHearingParams", 4, 0);
#else
    dword_439264.sub_16C2C0(0x19, 0xC, "m_freeHearingParams", 4, 0);
#endif
    dword_439284.sub_16C2C0(0xA, 0x24, "m_freeLongSound", 4, 0);
    dword_43925C = 0;
    dword_439260 = 0;
}

// match: sub_3C220 @ 0x0003C220
// sp-match: sub_3C220 @ 0x0002DD60
// Frees the lasting sounds, warning first unless every listener was
// unregistered.
void sub_3C220()
{
    type_3C540 *var_4;
    type_3C540 *local_8;

#if defined(CODFH_DRAW_TRIGGERS) && !defined(CODFH_SP)
    if (dword_439264.get_unk_18() != 96)
#else
    if (dword_439264.get_unk_18() != 0x19)
#endif
        sub_3C290();
    var_4 = dword_439260;
    while (var_4 != 0) {
        local_8 = var_4->unk_20;
        dword_439284.sub_16C710(var_4);
        var_4 = local_8;
    }
}

// match: sub_3C270 @ 0x0003C270
// sp-match: sub_3C270 @ 0x0002DC40
void sub_3C270()
{
    dword_439264.sub_16C4D0(1);
    dword_439284.sub_16C4D0(1);
}

// match: sub_3C290 @ 0x0003C290
void sub_3C290()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out (SP 0x2DD60 drops the call)
    sub_19A750("Somebody forgot to unregister in the AIHearing Class!");
#endif
}

// match: sub_3C2B0 @ 0x0003C2B0
// sp-match: sub_3C2B0 @ 0x0002DEF0
// The update, with the time step arg_0: loud sounds reach every listener
// first, then timed ones run down and untimed ones end (sub_8A950), and the
// rest reach the listeners that have not heard a loud one.
void sub_3C2B0(RwReal arg_0)
{
    type_3C540 *var_4;
    type_3C540 **v8;
    type_3C540 *stk_C;
    type_3C720 *var_10;

    var_4 = dword_439260;
    v8 = &dword_439260;
    for (var_10 = dword_43925C; var_10 != 0; var_10 = var_10->unk_08)
        var_10->unk_04 = 0;
    while (var_4 != 0) {
        stk_C = var_4->unk_20;
        if (var_4->unk_1C_1) {
            for (var_10 = dword_43925C; var_10 != 0; var_10 = var_10->unk_08)
                sub_3C7D0(var_10, var_4->unk_0C.sub_D4910(), var_4->unk_10, var_4->unk_08,
                          var_4->unk_14, var_4->unk_18, var_4->unk_1C_1);
        }
        if (var_4->unk_1C_0) {
            var_4->unk_04 -= arg_0;
            if (var_4->unk_04 <= 0.0f) {
                *v8 = stk_C;
                dword_439284.sub_16C710(var_4);
            }
        } else if (var_4->unk_1C_2 && type_8A980::sub_8A950(var_4->unk_00) == 0) {
            *v8 = stk_C;
            dword_439284.sub_16C710(var_4);
        } else {
            var_4->unk_1C_2 = !var_4->unk_1C_0;
            v8 = &var_4->unk_20;
        }
        var_4 = stk_C;
    }
    for (var_4 = dword_439260; var_4 != 0; var_4 = var_4->unk_20) {
        if (!var_4->unk_1C_1) {
            for (var_10 = dword_43925C; var_10 != 0; var_10 = var_10->unk_08)
                sub_3C7D0(var_10, var_4->unk_0C.sub_D4910(), var_4->unk_10, var_4->unk_08,
                          var_4->unk_14, var_4->unk_18, var_4->unk_1C_1);
        }
    }
}

// match: sub_3C4B0 @ 0x0003C4B0
// sp-match: sub_3C4B0 @ 0x0002E190
// Makes a sound: a lasting one (sub_3C540) when arg_14 (loud) is set, else
// heard by the listeners at once.
void sub_3C4B0(type_3D3548 *arg_0, RwInt32 arg_4, RwV3d *arg_8, RwInt32 arg_C, RwReal arg_10,
               RwInt32 arg_14, RwReal arg_18)
{
    type_3C720 *var_4;

    if (((dword_4B86F8 >> 4) & 1) != 0)
        return;
#ifdef CODFH_DRAW_TRIGGERS
    if (arg_14 == 0)
        TrigDrawNoiseMade(arg_8, arg_4, arg_C, arg_10, 0);
#endif
    if (arg_14 != 0) {
        sub_3C540(arg_0, arg_4, 0, arg_8, arg_C, arg_10, arg_14, arg_18);
    } else {
        for (var_4 = dword_43925C; var_4 != 0; var_4 = var_4->unk_08)
            sub_3C7D0(var_4, arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
    }
}

// match: sub_3C540 @ 0x0003C540
// sp-match: sub_3C540 @ 0x0002E070
// Registers a lasting sound (id arg_8), after the listeners hear it once.
void sub_3C540(type_3D3548 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10,
               RwReal arg_14, RwInt32 arg_18, RwReal arg_1C)
{
    type_3C540 *var_4;
    type_3C720 *v8;
    RwInt32 varC;
#ifdef CODFH_DRAW_TRIGGERS
    TrigDrawNoiseMade(arg_C, arg_4, arg_10, arg_14, 1);
#endif

    for (v8 = dword_43925C; v8 != 0; v8 = v8->unk_08)
        sub_3C7D0(v8, arg_0, arg_4, arg_C, arg_10, arg_14, arg_18);
    var_4 = (type_3C540 *)dword_439284.sub_16C5A0(0);
    if (var_4 == 0)
        return;
    var_4->unk_1C_1 = arg_18;
    var_4->unk_1C_0 = arg_1C > 0.0f;
    var_4->unk_08 = arg_C;
    var_4->unk_00 = arg_8;
    var_4->unk_04 = arg_1C;
    var_4->unk_14 = arg_10;
    var_4->unk_18 = arg_14;
    if (arg_4 == 0) {
        if (arg_0 != 0) {
            if (arg_0->vf_00C() != 0)
                var_4->unk_10 = 1;
            else if (arg_0->vf_008() != 0)
                var_4->unk_10 = 2;
        }
    } else {
        var_4->unk_10 = arg_4;
    }
    if (arg_0 != 0) {
        var_4->unk_0C.sub_D48D0(arg_0);
    } else {
        varC = 0;
        var_4->unk_0C = varC;
    }
    var_4->unk_1C_2 = 0;
    var_4->unk_20 = dword_439260;
    dword_439260 = var_4;
}

// match: sub_3C6C0 @ 0x0003C6C0
// sp-match: sub_3C6C0 @ 0x0002DC60
// Ends the lasting sound with id arg_0.
void sub_3C6C0(RwInt32 arg_0)
{
    type_3C540 *var_4;
    type_3C540 **local_8;

    var_4 = dword_439260;
    local_8 = &dword_439260;
    while (var_4 != 0) {
        if (var_4->unk_00 == arg_0) {
            *local_8 = var_4->unk_20;
            dword_439284.sub_16C710(var_4);
            return;
        }
        local_8 = &var_4->unk_20;
        var_4 = var_4->unk_20;
    }
}

// match: sub_3C720 @ 0x0003C720
// sp-match: sub_3C720 @ 0x0002DCA0
// Registers the entity arg_0 as a listener.
void sub_3C720(type_3D3548 *arg_0)
{
    type_3C720 *var_4;

    var_4 = (type_3C720 *)dword_439264.sub_16C5A0(0);
    var_4->unk_00 = arg_0;
    var_4->unk_08 = dword_43925C;
    dword_43925C = var_4;
}

// match: sub_3C760 @ 0x0003C760
// sp-match: sub_3C760 @ 0x0002DCD0
// Unregisters the listener entity arg_0.
void sub_3C760(type_3D3548 *arg_0)
{
    type_3C720 *var_4;
    type_3C720 **local_8;

    var_4 = dword_43925C;
    local_8 = &dword_43925C;
    while (var_4 != 0) {
        if (var_4->unk_00 == arg_0) {
            *local_8 = var_4->unk_08;
            var_4->unk_08 = 0;
            dword_439264.sub_16C710(var_4);
            return;
        }
        local_8 = &var_4->unk_08;
        var_4 = var_4->unk_08;
    }
}

// match: sub_3C7D0 @ 0x0003C7D0
// sp-match: sub_3C7D0 @ 0x0002DD90
// The listener arg_0 hears the sound (source arg_4, kind arg_8, point
// arg_C, class arg_10, range arg_14) when it listens for it (sub_3C980) and
// is within its range plus its own hearing radius; arg_18 (loud) marks it as
// having heard this update.
void sub_3C7D0(type_3C720 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C,
               RwInt32 arg_10, RwReal arg_14, RwInt32 arg_18)
{
    type_3D2E7C *var_3C;
    RwV3d l38;
    RwReal lcl_2C;
    RwInt32 local_28;
    RwUInt32 local_24;
    RwReal local_20;
    type_3C7D0_1C var_1C;

    if (arg_0->unk_04 != 0)
        return;
    if (arg_18 != 0)
        arg_0->unk_04 = 1;
    if (sub_3C980(arg_0->unk_00, arg_4, arg_8, arg_10) == 0)
        return;
    RwV3dSub(&l38, arg_C, arg_0->unk_00->sub_CD550());
    lcl_2C = RwV3dDotProduct(&l38, &l38);
    local_20 = arg_0->unk_00->vf_130() * arg_0->unk_00->vf_130() + arg_14 * arg_14;
    if (lcl_2C > local_20)
        return;
    var_1C.unk_00 = arg_10;
    var_1C.unk_04 = arg_8;
    local_28 = 0;
    local_24 = 0;
    if (arg_4 != 0) {
        local_28 = arg_4->unk_2C & 7;
        var_3C = arg_4->vf_098();
        if (var_3C != 0)
            local_24 = var_3C->get_unk_04();
    }
    var_1C.unk_08 = local_28;
    var_1C.unk_0C = local_24;
    var_1C.unk_10.x = arg_C->x;
    var_1C.unk_10.y = arg_C->y;
    var_1C.unk_10.z = arg_C->z;
#ifdef CODFH_DRAW_TRIGGERS
    TrigDrawNoiseHeard(arg_0->unk_00, arg_C, arg_8);
#endif
    sub_6B5F0("AIAction_HearSound", (type_67620 *)(arg_0->unk_00->vf_098()), 0, 0, (RwInt32 *)(&var_1C), 7, 1, 0);
}

// match: sub_3C980 @ 0x0003C980
// sp-match: sub_3C980 @ 0x0002DD10
// Whether the entity arg_0 listens for a sound of class arg_C and kind arg_8
// from arg_4 (its AI object's masks unk_538, unk_53C and sides unk_540).
RwInt32 sub_3C980(type_3D3548 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if ((arg_C & var_4->unk_538) == 0)
        return 0;
    if ((arg_8 & var_4->unk_53C) == 0)
        return 0;
    if (var_4->unk_540 != 0) {
        if (arg_4 != 0) {
            if (((arg_4->unk_2C & 7) & var_4->unk_540) != 0)
                return 1;
        } else if (arg_C == 1) {
            return 1;
        }
        return 0;
    }
    return 1;
}
