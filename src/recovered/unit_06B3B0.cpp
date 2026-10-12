// alfamessman, the message manager (types/alfamessman.h): its set-up and
// shutdown, and sending messages to scripts. The file's original name is
// not recovered (M1), so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "game/functions.h"
#include "xbox/xboxkrnl.h"
#include "types/type_42AF0.h"
#include "types/type_439E78.h"
#include "types/type_3D2E7C.h"
#include "types/type_67620.h"
#include "types/type_44350.h"
#include "types/alfamessman.h"
#include "types/scriptvm.h"
#include "types/alfaobject.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D2A14
extern const RwReal flt_3D2A14 = 16.666666f;
// 0x0044932C
RwInt32 dword_44932C;
// 0x00449330
RwInt16 *dword_449330;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4493D4;
type_16C2A0 dword_4493B4;
type_16C2A0 dword_449394;
type_16C2A0 dword_449374;
type_16C2A0 dword_449354;
type_16C2A0 dword_449334;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D2A14@@3MB @ 0x003D2A14
// match: ??_C@_0BH@DMFOLBN@m_messageArgsLargePool?$AA@ @ 0x003D2A18
// match: ??_C@_0BH@OEGIPBJG@m_messageArgsSmallPool?$AA@ @ 0x003D2A30
// match: ??_C@_0BG@BCCKLLBK@m_filterListLargePool?$AA@ @ 0x003D2A48
// match: ??_C@_0BG@PFIHKBJB@m_filterListSmallPool?$AA@ @ 0x003D2A60
// match: ??_C@_0BD@FHECFFMM@m_registrationPool?$AA@ @ 0x003D2A78
// match: ??_C@_0BL@HLKMPFHM@alfamessman?3?3m_messagePool?$AA@ @ 0x003D2A8C
// match: ??_C@_0EP@PKPILKLP@Messages?5were?5not?5unregistered?5i@ @ 0x003D2AA8
// match: ??_C@_0EP@MDDFGMMA@Messages?5were?5not?5unregistered?5m@ @ 0x003D2AF8
// match: ??_C@_0EP@PJKGAPAJ@Messages?5were?5not?5unregistered?5m@ @ 0x003D2B48
// match: ??_C@_0EL@BLEGACPI@Messages?5were?5not?5unregistered?5m@ @ 0x003D2B98
// match: ??_C@_0DD@CJMJBNEH@Messages?5were?5not?5deleted?5during@ @ 0x003D2BE4
// match: ??_C@_0BB@LHGELPML@Recieved?5Message?$AA@ @ 0x003D2C18
// match: .CRT$XCU+0 @ 0x00426DA4
// match: .CRT$XCU+4 @ 0x00426DA8
// match: .CRT$XCU+8 @ 0x00426DAC
// match: .CRT$XCU+12 @ 0x00426DB0
// match: .CRT$XCU+16 @ 0x00426DB4
// match: .CRT$XCU+20 @ 0x00426DB8

// match: _$E2 @ 0x00309980
// match: _$E3 @ 0x0030DD20
// match: _$E5 @ 0x003099A0
// match: _$E6 @ 0x0030DD30
// match: _$E8 @ 0x003099C0
// match: _$E9 @ 0x0030DD40
// match: _$E11 @ 0x003099E0
// match: _$E12 @ 0x0030DD50
// match: _$E14 @ 0x00309A00
// match: _$E15 @ 0x0030DD60
// match: _$E17 @ 0x00309A20
// match: _$E18 @ 0x0030DD70
// sp-match: _$E18 @ 0x0021E1A0
// sp-match: _$E2 @ 0x0021C410
// sp-match: _$E5 @ 0x0021C430
// sp-match: _$E8 @ 0x0021C450
// sp-match: _$E11 @ 0x0021C470
// sp-match: _$E14 @ 0x0021C490
// sp-match: _$E17 @ 0x0021C4B0
// sp-match: _$E3 @ 0x0021E150
// sp-match: _$E6 @ 0x0021E160
// sp-match: _$E9 @ 0x0021E170
// sp-match: _$E12 @ 0x0021E180
// sp-match: _$E15 @ 0x0021E190

RwInt32 *sub_6B8E0(RwInt32 arg_0);
void sub_6B920(RwInt32 *arg_0);
type_6B960 *sub_6B960();
void sub_6BC00(type_6B960 *arg_0);
void sub_6BC40(type_6B960 *arg_0);
RwInt32 sub_6BE10(type_42E00 *arg_0);
RwInt32 sub_6BF60(type_42E00 *arg_0);
bool sub_6C0A0(type_67620 *arg_0, type_4CFE30 *arg_4, type_67620 *arg_8, type_6B960 *arg_C);
bool sub_6C1A0(type_3D2E7C *arg_0, type_4CFE30 *arg_4, type_6B960 *arg_8, RwInt8 arg_C,
               RwInt8 arg_10);
bool sub_6C2D0(type_3D2E7C *arg_0, type_4CFE30 *arg_4, type_6B960 *arg_8, RwInt8 arg_C,
               RwInt8 arg_10);
bool sub_6C410(type_3D2E7C *arg_0, type_6B960 *arg_4, RwInt8 arg_8, RwInt8 arg_C);
bool sub_6C4E0(type_3D2E7C *arg_0, type_4CFE30 *arg_4, type_6B960 *arg_8, RwInt8 arg_C,
               RwInt8 arg_10);
bool sub_6C5A0(type_3D2E7C *arg_0, type_4CFE30 *arg_4, type_6B960 *arg_8, RwInt8 arg_C,
               RwInt8 arg_10);
bool sub_6C6D0(type_71250 *arg_0, type_71250 *arg_4, RwUInt8 arg_8, RwInt8 arg_C);
void sub_6C810(RwInt32 arg_0);
void sub_6C8B0(type_42E00 *arg_0, type_6B960 *arg_4);
// sub_6A970 (the script VM's unit): the debugger's report of a delivery.
void sub_6A970(type_42E00 *arg_0, type_6B960 *arg_4, const RwChar *arg_8);
void sub_42E00(type_67620 *arg_0, RwInt32 arg_4);

// dword_44C048: the critical section the senders hold.
extern RTL_CRITICAL_SECTION dword_44C048;

// match: sub_6B3B0 @ 0x0006B3B0
// sp-match: sub_6B3B0 @ 0x0005ABB0
// Sets the pools and the registration array up.
void sub_6B3B0()
{
    dword_4493D4.sub_16C2C0(1000, 0x18, "alfamessman::m_messagePool", 4, 0);
    dword_4493B4.sub_16C2C0(4500, 0x1C, "m_registrationPool", 4, 0);
    dword_449330 = (RwInt16 *)RWSMalloc(0xA8C, 0x34255);    // not an address: an allocation tag
    memset(dword_449330, -1, 0xA8C);
    dword_449394.sub_16C2C0(1000, 0xE, "m_filterListSmallPool", 4, 0);
    dword_449374.sub_16C2C0(250, 0x2E, "m_filterListLargePool", 4, 0);
    dword_449354.sub_16C2C0(200, 0x10, "m_messageArgsSmallPool", 4, 0);
    dword_449334.sub_16C2C0(200, 0x28, "m_messageArgsLargePool", 4, 0);
    dword_44932C = -1;
}

// match: sub_6B490 @ 0x0006B490
// sp-match: sub_6B490 @ 0x0005B2E0
// Restart.
void sub_6B490()
{
    sub_6BD30();
    sub_6B510();
}

// match: sub_6B4A0 @ 0x0006B4A0
// sp-match: sub_6B4A0 @ 0x0005B2F0
// Shutdown: as a restart, then frees the array and shuts the pools down.
void sub_6B4A0()
{
    sub_6BD30();
    sub_6B510();
    operator delete(dword_449330);
    dword_4493D4.sub_16C4D0(1);
    dword_4493B4.sub_16C4D0(1);
    dword_449394.sub_16C4D0(1);
    dword_449374.sub_16C4D0(1);
    dword_449354.sub_16C4D0(1);
    dword_449334.sub_16C4D0(1);
}

// match: sub_6B510 @ 0x0006B510
// sp-match: sub_6B510 @ 0x0005AC80
// Warns of messages, registrations and arguments still out.
void sub_6B510()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    // Single player compiles the debug prints out (SP 0x5AC80 only resets the count).
    RwInt32 var_4;

    if (dword_4493D4.in_use())
        sub_19A750("Messages were not deleted during restart/shutdown!");
    if (dword_4493B4.in_use())
        sub_19A750("Messages were not unregistered m_registrationPool during restart/shutdown!");
    if (dword_449354.in_use())
        sub_19A750("Messages were not unregistered m_messageArgsSmallPool during restart/shutdown!");
    if (dword_449334.in_use())
        sub_19A750("Messages were not unregistered m_messageArgsLargePool during restart/shutdown!");
    for (var_4 = 0; var_4 < 0x546; var_4++) {
        if (dword_449330[var_4] != -1)
            sub_19A750("Messages were not unregistered in m_registrationArray during "
                       "restart/shutdown!");
    }
#endif
    dword_44932C = -1;
}

// match: sub_6B5F0 @ 0x0006B5F0
// sp-match: sub_6B5F0 @ 0x0005B740
// Sends the message named arg_0 to the script arg_4 (all when 0) from
// arg_8, with the arg_C words at arg_10; queued (arg_18, arg_1C as
// sub_42AF0's).
#ifdef CODFH_DRAW_TRIGGERS
// (port/src/debug/trigdraw.cpp: the AI view notes the messages its entities raise)
void TrigDrawAiMessage(const RwChar *pszName, type_67620 *pScript);
#endif
void sub_6B5F0(const RwChar *arg_0, type_67620 *arg_4, type_42E00_10 *arg_8, type_3D2E7C *arg_C,
               RwInt32 *arg_10, RwInt32 arg_14, bool arg_18, bool arg_1C)
{
    type_439E78_00 varC;
    type_42E00_00 *local_8;
    RwInt32 var_4;

#ifdef CODFH_DRAW_TRIGGERS
    TrigDrawAiMessage(arg_0, arg_4);
#endif
    RtlEnterCriticalSection(&dword_44C048);
    local_8 = sub_6A7F0(arg_0);
    var_4 = arg_4 == 0;
    varC = sub_6B710(local_8->unk_04, arg_4, 0, arg_8, arg_C, var_4, arg_10, 0);
    sub_42AF0(0, 0x10, *(RwUInt32 *)&varC, arg_18, arg_1C);
    RtlLeaveCriticalSection(&dword_44C048);
}

// match: sub_6B680 @ 0x0006B680
// sp-match: sub_6B680 @ 0x0005B7B0
// Likewise for the message at index arg_0.
void sub_6B680(RwInt32 arg_0, type_67620 *arg_4, type_42E00_10 *arg_8, type_3D2E7C *arg_C,
               RwInt32 *arg_10, RwInt32 arg_14, bool arg_18, bool arg_1C)
{
    type_439E78_00 varC;
    type_42E00_00 *local_8;
    RwInt32 var_4;

    RtlEnterCriticalSection(&dword_44C048);
    local_8 = sub_6A7D0(arg_0);
    var_4 = arg_4 == 0;
    varC = sub_6B710(local_8->unk_04, arg_4, 0, arg_8, arg_C, var_4, arg_10, 0);
    sub_42AF0(0, 0x10, *(RwUInt32 *)&varC, arg_18, arg_1C);
    RtlLeaveCriticalSection(&dword_44C048);
}

// match: sub_6B710 @ 0x0006B710
// sp-match: sub_6B710 @ 0x0005B360
// A new message of kind arg_0 (m_messagePool, handle kind 6) for the script
// arg_4 (all when 0), from arg_8, with arg_C's unk_3C, arg_10 and arg_14;
// its arguments are the words ending at arg_18, in order when arg_1C is
// set. Returns its handle.
type_439E78_00 sub_6B710(RwInt32 arg_0, type_67620 *arg_4, type_3D2E7C *arg_8,
                         type_42E00_10 *arg_C, type_3D2E7C *arg_10, RwInt32 arg_14, RwInt32 *arg_18,
                         bool arg_1C)
{
    RwInt32 var_10;
    type_42E00 *ebp_C;
    RwUInt32 v8;
    RwInt32 var_4;

    ebp_C = (type_42E00 *)dword_4493D4.sub_16C5A0(0);
    v8 = sub_673C0((type_67620 *)ebp_C, 6);
    ebp_C->unk_00 = sub_6A7D0(arg_0);
    ebp_C->unk_04 = arg_4 != 0 ? arg_4->get_unk_04() : 0;
    ebp_C->unk_08 = arg_8 != 0 ? arg_8->get_unk_04() : 0;
    ebp_C->unk_10 = arg_C != 0 ? arg_C->unk_3C : -1;
    ebp_C->unk_12 = arg_14;
    ebp_C->unk_0C = arg_10 != 0 ? arg_10->get_unk_04() : 0;
    var_4 = ebp_C->unk_00->unk_10;
    if (ebp_C->unk_00->unk_10 == 0)
        ebp_C->unk_14 = 0;
    else {
        ebp_C->unk_14 = sub_6B8E0(ebp_C->unk_00->unk_10);
        if (arg_1C) {
            for (var_10 = 0; var_10 < var_4; var_10++)
                ebp_C->unk_14[var_10] = *(arg_18 - (var_4 - var_10));
        } else
            memcpy(ebp_C->unk_14, arg_18, var_4 * 4);
    }
    return *(type_439E78_00 *)&v8;
}

// match: sub_6B890 @ 0x0006B890
// sp-match: sub_6B890 @ 0x0005B450
// Deletes the message with the handle arg_0.
void sub_6B890(RwUInt32 arg_0)
{
    type_42E00 *var_4;

    var_4 = (type_42E00 *)sub_67620(arg_0);
    if (var_4->unk_14 != 0)
        sub_6B920(var_4->unk_14);
    sub_67520(arg_0);
    dword_4493D4.sub_16C710(var_4);
}

// match: sub_6B8E0 @ 0x0006B8E0
// sp-match: sub_6B8E0 @ 0x0005AC90
// Arguments for arg_0 words: from m_messageArgsSmallPool when they fit and
// it has room, else from m_messageArgsLargePool.
RwInt32 *sub_6B8E0(RwInt32 arg_0)
{
    if (arg_0 < 4 && !dword_449354.sub_16C7E0())
        return (RwInt32 *)dword_449354.sub_16C5A0(0);
    return (RwInt32 *)dword_449334.sub_16C5A0(0);
}

// match: sub_6B920 @ 0x0006B920
// sp-match: sub_6B920 @ 0x0005ACC0
// Frees the arguments arg_0 to their pool.
void sub_6B920(RwInt32 *arg_0)
{
    if (dword_449354.sub_16C770(arg_0))
        dword_449354.sub_16C710(arg_0);
    else
        dword_449334.sub_16C710(arg_0);
}

// match: sub_6B960 @ 0x0006B960
// sp-match: sub_6B960 @ 0x0005ACF0
// A new registration.
type_6B960 *sub_6B960()
{
    type_6B960 *var_4;

    var_4 = (type_6B960 *)dword_4493B4.sub_16C5A0(0);
    return var_4;
}

// match: sub_6B980 @ 0x0006B980
// sp-match: sub_6B980 @ 0x0005AD00
// Frees the registration arg_0.
void sub_6B980(type_6B960 *arg_0)
{
    dword_4493B4.sub_16C710(arg_0);
}

// match: sub_6B9A0 @ 0x0006B9A0
// sp-match: sub_6B9A0 @ 0x0005B490
// Registers the script arg_0 (with arg_4, arg_8, arg_10 the message kind
// and the flags arg_14 and arg_18) as kind 1; drops its queued messages of
// that kind when arg_8's flag is set.
type_6B960 *sub_6B9A0(type_67620 *arg_0, RwInt32 arg_4, type_6B9A0_08 *arg_8, RwInt32 arg_C,
                      RwInt32 arg_10, RwInt8 arg_14, RwInt8 arg_18)
{
    type_6B960 *var_4;

    var_4 = sub_6B960();
    var_4->unk_00_h = arg_0->get_unk_04_h();
    var_4->unk_04 = arg_4;
    var_4->unk_0E = -1;
    var_4->unk_0C = -1;
    var_4->unk_08 = arg_8;
    var_4->unk_1A = 0;
    var_4->unk_18 = arg_14;
    var_4->unk_19 = arg_18;
    var_4->unk_14 = arg_10;
    var_4->unk_1B = 1;
    var_4->unk_10 = -1;
    var_4->unk_12 = -1;
    if (arg_8 != 0 && arg_8->unk_06 != 0)
        sub_42E00((type_67620 *)arg_0->vf_024(), arg_10);
    sub_6BC00(var_4);
    return var_4;
}

// match: sub_6BA60 @ 0x0006BA60
// sp-match: sub_6BA60 @ 0x0005B510
// Registers arg_0 as kind 3 (arg_8 the message kind, flags arg_C and
// arg_10).
type_6B960 *sub_6BA60(type_67620 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt8 arg_C,
                      RwInt8 arg_10)
{
    type_6B960 *var_4;

    var_4 = sub_6B960();
    var_4->unk_00_h = arg_0->get_unk_04_h();
    var_4->unk_08_s = -1;
    var_4->unk_04 = 0;
    var_4->unk_1A = 0;
    var_4->unk_18 = arg_C;
    var_4->unk_19 = arg_10;
    var_4->unk_14 = arg_8;
    var_4->unk_1B = 3;
    var_4->unk_10 = -1;
    var_4->unk_12 = -1;
    sub_6BC00(var_4);
    return var_4;
}

// match: sub_6BAE0 @ 0x0006BAE0
// sp-match: sub_6BAE0 @ 0x0005B560
// Registers the handle arg_4 with arg_0 as kind 2 (arg_C the message kind,
// flags arg_10 and arg_14).
#ifdef CODFH_SP // arg_10 unsigned (its callers zero-extend it: SP 0x92410, 0x7CB31)
type_6B960 *sub_6BAE0(RwInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwUInt8 arg_10,
                      RwInt8 arg_14)
#else
type_6B960 *sub_6BAE0(RwInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt8 arg_10,
                      RwInt8 arg_14)
#endif
{
    type_6B960 *var_4;

    var_4 = sub_6B960();
    var_4->unk_04 = arg_0;
    var_4->unk_00 = arg_4;
    var_4->unk_1A = 0;
    var_4->unk_18 = arg_10;
    var_4->unk_19 = arg_14;
    var_4->unk_14 = arg_C;
    var_4->unk_1B = 2;
    sub_6BC00(var_4);
    return var_4;
}

// match: sub_6BB40 @ 0x0006BB40
// sp-match: sub_6BB40 @ 0x0005AD10
// Puts the registration at the pool index arg_0 at the head of its
// message kind's list.
void sub_6BB40(RwInt16 arg_0)
{
    type_6B960 *varC;
    RwInt32 local_8;
    type_6B960 *var_4;

    var_4 = get_registration(arg_0);
    local_8 = var_4->unk_14;
    if (dword_449330[local_8] != -1) {
        varC = get_registration(dword_449330[local_8]);
        varC->unk_12 = arg_0;
    }
    var_4->unk_10 = dword_449330[local_8];
    var_4->unk_12 = -1;
    dword_449330[local_8] = arg_0;
}

// match: sub_6BC00 @ 0x0006BC00
// sp-match: sub_6BC00 @ 0x0005AD80
// Puts the registration arg_0 at the head of its message kind's list.
void sub_6BC00(type_6B960 *arg_0)
{
    RwInt32 var_4;

    if (arg_0 != 0)
        var_4 = dword_4493B4.sub_16C650(arg_0);
    else
        var_4 = -1;
    sub_6BB40((RwInt16)var_4);
}

// match: sub_6BC40 @ 0x0006BC40
// sp-match: sub_6BC40 @ 0x0005ADB0
// Unlinks and frees the registration arg_0; while its kind is being sent,
// only marks it.
void sub_6BC40(type_6B960 *arg_0)
{
    type_6B960 *varC;
    type_6B960 *local_8;
    RwInt32 var_4;

    var_4 = arg_0->unk_14;
    if (dword_44932C == var_4) {
        arg_0->unk_1A |= 1;
        return;
    }
    if (arg_0->unk_12 != -1) {
        local_8 = get_registration(arg_0->unk_12);
        local_8->unk_10 = arg_0->unk_10;
    } else
        dword_449330[var_4] = arg_0->unk_10;
    if (arg_0->unk_10 != -1) {
        varC = get_registration(arg_0->unk_10);
        varC->unk_12 = arg_0->unk_12;
    }
    sub_6B980(arg_0);
}

// match: sub_6BD30 @ 0x0006BD30
// sp-match: sub_6BD30 @ 0x0005AE30
// Unregisters everything.
void sub_6BD30()
{
    type_6B960 *var_10;
    RwInt32 ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    dword_44932C = -1;
    for (var_4 = 0; var_4 < 0x546; var_4++) {
        v8 = dword_449330[var_4];
        ebp_C = -1;
        while (v8 != -1) {
            var_10 = get_registration((RwInt16)v8);
            ebp_C = var_10->unk_10;
            sub_6BC40(var_10);
            v8 = ebp_C;
        }
    }
}

// match: sub_6BDC0 @ 0x0006BDC0
// sp-match: sub_6BDC0 @ 0x0005B9F0
// Delivers the message arg_0: to its script, or to every registration of
// its kind.
void sub_6BDC0(type_42E00 *arg_0)
{
    RwInt32 var_4;

    var_4 = arg_0->unk_00->unk_04;
    if (arg_0->unk_12 == 0)
        sub_6BE10(arg_0);
    else if (dword_449330[var_4] != -1)
        sub_6BF60(arg_0);
}

// match: sub_6BE10 @ 0x0006BE10
// sp-match: sub_6BE10 @ 0x0005B5A0
// Delivers the message arg_0 to its script's object, and to the handlers
// registered for its kind by that object's scripts; whether any took it.
RwInt32 sub_6BE10(type_42E00 *arg_0)
{
    type_67620 *var_1C;
    RwInt32 var18;
    type_6B960 *stk_14;
    type_3D2E7C *l10;
    RwInt32 local_C;
    type_6B960 *lv_8;
    RwInt32 var_4;

    var_4 = 0;
    l10 = (type_3D2E7C *)sub_67620(arg_0->unk_04);
    if (l10 == 0)
        return var_4;
    local_C = arg_0->unk_00->unk_04;
    dword_44932C = local_C;
    lv_8 = 0;
    stk_14 = sub_6B960();
    stk_14->unk_1B = 1;
    l10->sub_710B0(arg_0, stk_14);
    sub_6B980(stk_14);
    if (l10->sub_71090() != 0) {
        for (var18 = dword_449330[local_C]; var18 != -1; var18 = lv_8->unk_10) {
            lv_8 = get_registration((RwInt16)var18);
            var_1C = 0;
            if (lv_8->unk_1B == 3)
                var_1C = sub_67620(lv_8->unk_00);
            if (var_1C != 0 && var_1C->vf_024() == l10 && (lv_8->unk_1A & 3) == 0) {
                var_4 = 1;
                sub_6C8B0(arg_0, lv_8);
            }
        }
    }
    dword_44932C = -1;
    sub_6C810(local_C);
    return var_4;
}

// match: sub_6BF60 @ 0x0006BF60
// sp-match: sub_6BF60 @ 0x0005B900
// Delivers the message arg_0 to every registration of its kind that
// accepts it (sub_6C0A0); whether any took it.
RwInt32 sub_6BF60(type_42E00 *arg_0)
{
    RwInt32 var_1C;
    type_67620 *var18;
    RwInt32 stk_14;
    type_6B960 *l10;
    RwInt32 local_C;
    type_67620 *lv_8;
    type_4CFE30 *var_4;

    local_C = 0;
    stk_14 = arg_0->unk_00->unk_04;
    dword_44932C = stk_14;
    var18 = sub_67620(arg_0->unk_08);
    lv_8 = sub_67620(arg_0->unk_0C);
    if (arg_0->unk_10 != -1)
        var_4 = get_performance_map(arg_0->unk_10);
    else
        var_4 = 0;
    l10 = 0;
    for (var_1C = dword_449330[stk_14]; var_1C != -1; var_1C = l10->unk_10) {
        l10 = get_registration((RwInt16)var_1C);
        if ((l10->unk_1A & 3) == 0 && sub_6C0A0(var18, var_4, lv_8, l10)) {
            sub_6C8B0(arg_0, l10);
            local_C = 1;
        }
    }
    dword_44932C = -1;
    sub_6C810(stk_14);
    return local_C;
}

// match: sub_6C0A0 @ 0x0006C0A0
// sp-match: sub_6C0A0 @ 0x0005B820
// Whether the registration arg_C accepts a message from arg_0 at arg_4 for
// arg_8, by its filter (the low nibble of unk_19): 1 all, 2 by filter
// lists, 3 and 4 by trigger, 5 by recipient, 6 by entity.
bool sub_6C0A0(type_67620 *arg_0, type_4CFE30 *arg_4, type_67620 *arg_8, type_6B960 *arg_C)
{
    RwInt8 var_2;
    RwInt8 var_1;

    var_2 = arg_C->unk_18;
    var_1 = arg_C->unk_19;
    switch (var_1 & 0xF) {
    case 1:
        return true;
    case 2:
        return sub_6C5A0((type_3D2E7C *)arg_0, arg_4, arg_C, var_2, var_1);
    case 3:
        return sub_6C1A0((type_3D2E7C *)arg_0, arg_4, arg_C, var_2, var_1);
    case 4:
        return sub_6C2D0((type_3D2E7C *)arg_0, arg_4, arg_C, var_2, var_1);
    case 5:
        return sub_6C410((type_3D2E7C *)arg_8, arg_C, var_2, var_1);
    case 6:
        return sub_6C4E0((type_3D2E7C *)arg_0, arg_4, arg_C, var_2, var_1);
    }
    return true;
}

// match: sub_6C1A0 @ 0x0006C1A0
// sp-match: sub_6C1A0 @ 0x0005AE90
// Filter 3: whether the registered object's trigger is the sender's (or
// arg_4), inverted when the high nibble of arg_10 is 2.
bool sub_6C1A0(type_3D2E7C *arg_0, type_4CFE30 *arg_4, type_6B960 *arg_8, RwInt8 arg_C,
               RwInt8 arg_10)
{
    type_3D2E7C *varC;
    type_712B0 *local_8;
    RwInt32 var_4;

    var_4 = arg_10 >> 4;
    varC = 0;
    switch (arg_8->unk_1B) {
    case 2:
        return var_4 != 2;
    case 1:
        varC = sub_67620(arg_8->unk_00)->vf_024();
        break;
    case 3:
        varC = sub_67620(arg_8->unk_00)->vf_024();
        break;
    }
    if ((arg_0 == 0 || arg_0->sub_712B0() == 0) && arg_4 == 0)
        return var_4 != 2;
    if (varC->get_unk_14() == 1)
        return var_4 != 2;
    if (arg_4 == 0 && arg_0->get_unk_14() != 1)
        return var_4 != 2;
    local_8 = arg_0 != 0 ? arg_0->sub_712B0() : (type_712B0 *)arg_4;
    if (varC->sub_712B0() == local_8)
        return var_4 == 2;
    return var_4 != 2;
}

// match: sub_6C2D0 @ 0x0006C2D0
// sp-match: sub_6C2D0 @ 0x0005AF40
// Filter 4: likewise, for kind-2 registrations by their unk_04.
bool sub_6C2D0(type_3D2E7C *arg_0, type_4CFE30 *arg_4, type_6B960 *arg_8, RwInt8 arg_C,
               RwInt8 arg_10)
{
    type_3D2E7C *var_10;
    type_712B0 *ebp_C;
    RwInt32 v8;
    type_712B0 *var_4;

    v8 = arg_10 >> 4;
    if ((arg_0 == 0 || arg_0->sub_712B0() == 0) && arg_4 == 0)
        return v8 != 2;
    var_10 = 0;
    if (arg_8->unk_1B == 1)
        var_10 = sub_67620(arg_8->unk_00)->vf_024();
    else if (arg_8->unk_1B == 3)
        var_10 = sub_67620(arg_8->unk_00)->vf_024();
    if (arg_8->unk_1B != 2 && var_10->get_unk_14() != 1)
        return v8 != 2;
    if (arg_4 != 0 || arg_0->get_unk_14() == 1)
        return v8 != 2;
    ebp_C = arg_0 != 0 ? arg_0->sub_712B0() : (type_712B0 *)arg_4;
    if (arg_8->unk_1B != 2)
        var_4 = var_10->sub_712B0();
    else
        var_4 = (type_712B0 *)arg_8->unk_04;
    if (var_4 == ebp_C)
        return v8 == 2;
    return v8 != 2;
}

// match: sub_6C410 @ 0x0006C410
// sp-match: sub_6C410 @ 0x0005AFF0
// Filter 5: whether the registered object is the message's recipient
// arg_0.
bool sub_6C410(type_3D2E7C *arg_0, type_6B960 *arg_4, RwInt8 arg_8, RwInt8 arg_C)
{
    type_3D2E7C *local_8;
    RwInt32 var_4;

    var_4 = arg_C >> 4;
    if (arg_4->unk_1B == 2)
        return var_4 != 2;
    local_8 = 0;
    switch (arg_4->unk_1B) {
    case 2:
        return var_4 != 2;
    case 1:
        local_8 = sub_67620(arg_4->unk_00)->vf_024();
        break;
    case 3:
        local_8 = sub_67620(arg_4->unk_00)->vf_024();
        break;
    }
    if (arg_0 == 0)
        return var_4 != 2;
    if (local_8 == arg_0)
        return var_4 == 2;
    return var_4 != 2;
}

// match: sub_6C4E0 @ 0x0006C4E0
// sp-match: sub_6C4E0 @ 0x0005B050
// Filter 6: whether the registered object is the sender, or its entity is
// arg_4.
bool sub_6C4E0(type_3D2E7C *arg_0, type_4CFE30 *arg_4, type_6B960 *arg_8, RwInt8 arg_C,
               RwInt8 arg_10)
{
    type_3D2E7C *local_8;
    RwInt32 var_4;

    var_4 = arg_10 >> 4;
    local_8 = 0;
    if (arg_8->unk_1B == 1)
        local_8 = sub_67620(arg_8->unk_00)->vf_024();
    else if (arg_8->unk_1B == 3)
        local_8 = sub_67620(arg_8->unk_00)->vf_024();
    if (arg_0 != 0) {
        if (arg_0 == local_8)
            return var_4 == 2;
    } else if (arg_4 != 0 && local_8->get_unk_10() == (type_3D3548 *)arg_4)
        return var_4 == 2;
    return var_4 != 2;
}

// match: sub_6C5A0 @ 0x0006C5A0
// sp-match: sub_6C5A0 @ 0x0005B690
// Filter 2: compares the sender's (or arg_4's) filter list with the
// registered object's (sub_6C6D0).
bool sub_6C5A0(type_3D2E7C *arg_0, type_4CFE30 *arg_4, type_6B960 *arg_8, RwInt8 arg_C,
               RwInt8 arg_10)
{
    type_71250 *var_10;
    type_3D2E7C *ebp_C;
    RwInt32 v8;
    type_71250 *var_4;

    v8 = arg_10 >> 4;
    if ((arg_0 == 0 || arg_0->sub_71250() == 0) && arg_4 == 0)
        return v8 != 2;
    var_10 = arg_0 != 0 ? arg_0->sub_71250() : arg_4->get_unk_AC();
    ebp_C = 0;
    if (arg_8->unk_1B == 1)
        ebp_C = sub_67620(arg_8->unk_00)->vf_024();
    else if (arg_8->unk_1B == 3)
        ebp_C = sub_67620(arg_8->unk_00)->vf_024();
    if (var_10 == 0)
        return v8 != 2;
    if (arg_8->unk_1B != 2)
        var_4 = ebp_C->sub_71250();
    else
        var_4 = ((type_4CFE30 *)arg_8->unk_04)->unk_AC;
    if (var_4 == 0)
        return v8 != 2;
    return sub_6C6D0(var_10, var_4, arg_C, arg_10);
}

// match: sub_6C6D0 @ 0x0006C6D0
// sp-match: sub_6C6D0 @ 0x0005B0C0
// Whether the filter lists arg_0 and arg_4 both hold the channel arg_8 with
// the same rank (inverted when the high nibble of arg_C is 2).
bool sub_6C6D0(type_71250 *arg_0, type_71250 *arg_4, RwUInt8 arg_8, RwInt8 arg_C)
{
    type_71250_02 *l14;
    type_71250_02 *var_10;
    type_71250_02 *ebp_C;
    RwInt32 v8;
    type_71250_02 *var_4;

    v8 = arg_C >> 4;
    l14 = arg_0->unk_02;
    var_10 = arg_4->unk_02;
    var_4 = &arg_0->unk_02[arg_0->unk_00 - 1];
    ebp_C = &arg_4->unk_02[arg_4->unk_00 - 1];
    while (l14->unk_00 != arg_8) {
        l14++;
        if (l14 > var_4)
            return v8 != 2;
    }
    while (var_10->unk_00 != arg_8) {
        var_10++;
        if (var_10 > ebp_C)
            return v8 != 2;
    }
    while (var_10->unk_00 == arg_8 && l14->unk_00 == arg_8) {
        if (var_10->unk_02 > l14->unk_02) {
            l14++;
            if (l14 > var_4)
                return v8 != 2;
        } else if (var_10->unk_02 < l14->unk_02) {
            var_10++;
            if (var_10 > ebp_C)
                return v8 != 2;
        } else
            return v8 == 2;
    }
    return v8 != 2;
}

// match: sub_6C810 @ 0x0006C810
// sp-match: sub_6C810 @ 0x0005B160
// After a send of the message kind arg_0: frees the registrations
// unregistered meanwhile and flips the pending ones' flags.
void sub_6C810(RwInt32 arg_0)
{
    RwInt32 varC;
    type_6B960 *local_8;
    RwInt32 var_4;

    var_4 = dword_449330[arg_0];
    while (var_4 != -1) {
        local_8 = get_registration((RwInt16)var_4);
        varC = local_8->unk_10;
        if (local_8->unk_1A & 1)
            sub_6BC40(local_8);
        else if (local_8->unk_1A & 4) {
            local_8->unk_1A ^= 4;
            local_8->unk_1A ^= 2;
        }
        var_4 = varC;
    }
}

// match: sub_6C8B0 @ 0x0006C8B0
// sp-match: sub_6C8B0 @ 0x0005B1C0
// Delivers the message arg_0 through the registration arg_4: to its script
// (kind 1), waking its task with the first argument as its return register
// (kind 3), or to its callback (kind 2, unregistered when that returns 0).
void sub_6C8B0(type_42E00 *arg_0, type_6B960 *arg_4)
{
    RwInt32 l14;
    type_6BAE0 *var_10;
    type_46120 *ebp_C;
    type_67620 *v8;
    type_67620 *var_4;

    if (arg_4->unk_1B == 1) {
        v8 = sub_67620(arg_4->unk_00);
        if (v8 == 0)
            return;
        sub_6A970(arg_0, arg_4, "Recieved Message");
        var_4 = v8;
        ((type_3D2DB8 *)var_4)->sub_6F110(arg_0, arg_4);
    } else if (arg_4->unk_1B == 3) {
        ebp_C = (type_46120 *)sub_67620(arg_4->unk_00);
        if (ebp_C == 0)
            return;
        sub_6A970(arg_0, arg_4, "Recieved Message");
        if (arg_0->unk_14 != 0) {
            l14 = *arg_0->unk_14;
            ebp_C->unk_120 = l14;
        }
        ((type_3D2E20 *)ebp_C)->sub_70590(1, (type_3D2E20_118 *)arg_4->unk_04, (type_42E00 *)((RwInt32)arg_0));
    } else {
        sub_6A970(arg_0, arg_4, "Recieved Message");
        var_10 = (type_6BAE0 *)arg_4;
        if (!var_10->unk_00(var_10->unk_04, arg_0))
            sub_6BC40(arg_4);
    }
}

// match: sub_6C9D0 @ 0x0006C9D0
// sp-match: sub_6C9D0 @ 0x0005B280
// A filter list for arg_0 entries: from m_filterListSmallPool when they fit
// and it has room, else from m_filterListLargePool.
type_71250 *sub_6C9D0(RwInt32 arg_0)
{
    type_71250 *var_4;

    var_4 = 0;
    if (arg_0 <= 3 && !dword_449394.sub_16C7E0())
        var_4 = (type_71250 *)dword_449394.sub_16C5A0(0);
    else
        var_4 = (type_71250 *)dword_449374.sub_16C5A0(0);
    return var_4;
}

// match: sub_6CA20 @ 0x0006CA20
// sp-match: sub_6CA20 @ 0x0005B2B0
// Frees the filter list arg_0 to its pool.
void sub_6CA20(type_71250 *arg_0)
{
    if (dword_449394.sub_16C770(arg_0))
        dword_449394.sub_16C710(arg_0);
    else
        dword_449374.sub_16C710(arg_0);
}
