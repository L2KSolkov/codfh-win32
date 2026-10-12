// The squads (type_3DF30, "m_freeSquadList"): a squad's own methods (from
// its constructor sub_3DF30), then the squad list: its pool setup, restart
// and shutdown, the AI update sub_3ED10 that runs every squad, and the
// placing of an entity in a squad (sub_3EE10). It follows type_3D410's unit
// and precedes the kind-4 object's (sub_3F120). Its original file name is
// not in the image, so it is named for its start address.

// Evidence: sub_3EEE0 calls the global placement new at 0x6CCF0,
// and its cleanup calls placement delete at 0x19A750. This unit needs
// declarations only; the transitive XDK <new> include supplies inline
// definitions otherwise (and removes both original calls).
#ifdef CODFH_WIN32
// (Win32: <new>'s inline placement forms, which the port's library emits in every unit using them)
#include <new>
#include "rw/ostypes.h"
#else
#define __PLACEMENT_NEW_INLINE
#include "rw/ostypes.h"
void *operator new(RwUInt32, void *) throw();
inline void operator delete(void *, void *) throw();
#endif
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/alfasched.h"
#include "types/type_365A0.h"
#include "types/type_3CE5E8.h"
#include "types/type_3CE6D0.h"
#include "types/type_3D3548.h"
#include "types/type_3D410.h"
#include "types/type_3DF30.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE7F8
extern const RwReal flt_3CE7F8 = 16.666666f;
// 0x003CE7FC
extern const RwReal flt_3CE7FC = 16.666666f;
// 0x004395F0
type_3DF30 *dword_4395F0;
// 0x004395F4
RwInt32 dword_4395F4;
// End of its data definitions.


// Inline with no address or database name. Evidence: sub_3EEE0 copies
// the list head through -0x20 before assigning the new squad's link;
// this inline local precedes the constructor and post-increment spills.
static inline type_3DF30 *get_squad_list()
{
    type_3DF30 *head = dword_4395F0;
    return head;
}

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4395F8;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE7F8@@3MB @ 0x003CE7F8
// match: ?flt_3CE7FC@@3MB @ 0x003CE7FC
// match: ??_C@_0BA@OPLNGIOH@m_freeSquadList?$AA@ @ 0x003CE800
// match: ??_C@_0EA@CJOIDEGM@An?5entity?5was?5not?5removed?5from?5a@ @ 0x003CE810
// match: __ehhandler$?sub_3EEE0@@YAPAUtype_3DF30@@XZ>1>8 @ 0x0041B0B8
// match: __ehhandler$?sub_3EEE0@@YAPAUtype_3DF30@@XZ>1 @ 0x0041B0C0
// match: .CRT$XCU+0 @ 0x00426D88

// match: _$E2 @ 0x00309870
// match: _$E3 @ 0x0030DCC0
// sp-match: _$E3 @ 0x0021E0F0
// sp-match: _$E2 @ 0x0021C2F0

// In the AIManeuverManager's unit (unit_03CA10.cpp).
type_365A0 sub_3CE20(RwInt32 arg_0);
void sub_3D0B0(type_365A0 arg_0);
RwUInt32 sub_3D120(type_3DF30 *arg_0, type_3D410 *arg_4, RwInt32 arg_8);
#ifdef CODFH_SP
// Single player passes and returns the handle by value (SP 0x2E770).
type_365A0 sub_3D150(type_3DF30 *arg_0, type_3D410 *arg_4, type_365A0 arg_8, RwInt32 arg_C);
#else
RwUInt32 sub_3D150(type_3DF30 *arg_0, type_3D410 *arg_4, RwUInt32 arg_8, RwInt32 arg_C);
#endif
// The other updates sub_3ED10 runs: the AIHearing class's (sub_3C2B0), the
// Distance Scheduler's (sub_350F0), and two whose owners are not known.
void sub_3C2B0(RwReal arg_0);
void sub_350F0(RwReal arg_0);
void sub_331F0(RwReal arg_0);
void sub_408F0(RwReal arg_0);

void sub_3ECC0();
void sub_3EFB0(type_3DF30 *arg_0);
void sub_3F040();
// sub_3EEE0: a new squad with the next id
// (dword_4395F4), built in a pool slot with the global placement operator
// new, at the head of the list.
type_3DF30 *sub_3EEE0();
type_3DF30 *sub_3F080(RwInt32 arg_0);

// match: ??0type_3DF30@@QAE@XZ @ 0x0003DF30
// sp-match: ??0type_3DF30@@QAE@XZ @ 0x0002EF30
type_3DF30::type_3DF30()
{
    unk_00 = 0;
    unk_2AC = 0;
    unk_2A8 = 0;
}

// match: sub_3DF90 @ 0x0003DF90
// sp-match: sub_3DF90 @ 0x0002F640
void type_3DF30::sub_3DF90(RwInt32 arg_0)
{
    RwInt32 var_4;

    unk_2B4 = arg_0;
    unk_2A8 = 0;
    unk_2AC = 0;
    unk_00 = 0;
    unk_2B0 = 0;
    unk_2B8 = 0;
    unk_2DC = 0;
    unk_04.sub_3D4C0(this);
    for (var_4 = 0; var_4 < 7; var_4++)
        unk_2C0[var_4] = 0;
    sub_3E2C0(sub_3CE20(0));
    sub_3E2C0(sub_3CE20(6));
    sub_3E2C0(sub_3CE20(4));
    sub_3E2C0(sub_3CE20(3));
}

// match: sub_3E0A0 @ 0x0003E0A0
// sp-match: sub_3E0A0 @ 0x0002EF60
void type_3DF30::sub_3E0A0()
{
    type_365A0 stk_18;
    RwUInt32 l14;
    AIData *var_10;
    type_3D3548 *ebp_C;
    type_3CE6D0 *v8;
    type_3CE6D0 *var_4;

    for (ebp_C = unk_00; ebp_C != 0; ebp_C = ebp_C->vf_118()) {
        var_10 = ebp_C->vf_120();
        if (var_10 != 0)
            var_10->sub_17030(0);
        ebp_C->vf_11C(0);
    }
    unk_00 = 0;
    v8 = sub_3D3E0(unk_2A8);
    while (v8 != 0) {
        l14 = v8->unk_14;
        var_4 = sub_3D3E0(l14);
        stk_18.unk_00 = v8->unk_18;
        sub_3D0B0(stk_18);
        v8 = var_4;
    }
    unk_2A8 = 0;
    unk_04.sub_1E41C0();
}

// match: sub_3E180 @ 0x0003E180
// sp-match: sub_3E180 @ 0x0002F6F0
void type_3DF30::sub_3E180(RwReal arg_0)
{
    RwUInt32 var_1C;
    RwUInt32 var18;
    RwUInt32 stk_14;
    RwUInt32 l10;
    type_365A0 local_C;
    type_3CE6D0 *lv_8;
    type_3CE6D0 *var_4;

    unk_04.sub_3D5F0(arg_0);
    if (unk_2A8 == 0) {
        l10 = sub_3D120(this, &unk_04, unk_2DC);
        unk_2A8 = l10;
        sub_3D3E0(unk_2A8)->vf_004(this);
    }
#ifdef CODFH_SP
    // the handle by value (SP 0x2F739)
    stk_14 = sub_3D150(this, &unk_04, *(type_365A0 *)&unk_2A8, unk_2DC).unk_00;
#else
    stk_14 = sub_3D150(this, &unk_04, unk_2A8, unk_2DC);
#endif
    local_C.unk_00 = stk_14;
    if (local_C.unk_00 != 0)
        sub_3E2C0(local_C);
    lv_8 = sub_3D3E0(unk_2A8);
    while (lv_8 != 0) {
        var18 = lv_8->unk_14;
        var_4 = sub_3D3E0(var18);
        if (lv_8->vf_00C(arg_0, &unk_04) == 0) {
#ifdef CODFH_SP
            // the handle struct through get_unk_18() (SP 0x2F78F loads it over lv_8's register).
            sub_3E3B0(lv_8->get_unk_18());
#else
            var_1C = lv_8->unk_18;
            sub_3E3B0(var_1C);
#endif
        }
        lv_8 = var_4;
    }
    unk_04.sub_3D6B0(arg_0);
}

// match: sub_3E2C0 @ 0x0003E2C0
// sp-match: sub_3E2C0 @ 0x0002F000
void type_3DF30::sub_3E2C0(type_365A0 arg_0)
{
    type_3CE6D0 *bp_4 = sub_3D3E0(arg_0.unk_00);

    bp_4->vf_004(this);
    type_3CE6D0 *rC = sub_3D3E0(unk_2A8);
    type_3CE6D0 *x8 = 0;

    while (rC && rC->vf_02C() < bp_4->vf_02C())
    {
        x8 = rC;
        rC = sub_3D3E0(rC->get_unk_14().unk_00);
    }
    if (x8)
    {
        bp_4->set_unk_14(x8->get_unk_14());
        x8->set_unk_14(bp_4->get_unk_18());
    }
    else
    {
        bp_4->set_unk_14(unk_2A8_h);
        unk_2A8_h = bp_4->get_unk_18();
    }
}

// match: sub_3E3B0 @ 0x0003E3B0
// sp-match: sub_3E3B0 @ 0x0002F0A0
#ifdef CODFH_SP
void type_3DF30::sub_3E3B0(type_365A0 arg_0)
{
    type_3CE6D0 *bp_4 = sub_3D3E0(arg_0.unk_00);
#else
void type_3DF30::sub_3E3B0(RwUInt32 arg_0)
{
    type_3CE6D0 *bp_4 = sub_3D3E0(arg_0);
#endif

    if (bp_4 && unk_2C0[bp_4->vf_030()])
        return;
    type_3CE6D0 *rC = sub_3D3E0(unk_2A8);
    type_3CE6D0 *x8 = 0;

    while (rC && rC != bp_4)
    {
        x8 = rC;
        rC = sub_3D3E0(rC->get_unk_14().unk_00);
    }
    if (x8)
        x8->set_unk_14(rC->get_unk_14());
    else
        unk_2A8_h = sub_3D3E0(unk_2A8)->get_unk_14();
    for (type_3D3548 *var_10 = unk_00; var_10; var_10 = var_10->vf_118())
    {
        if (var_10->vf_120())
        {
            if (sub_3D3E0(var_10->vf_120()->get_unk_574_h().unk_00) == bp_4)
            {
                bp_4->vf_014(var_10);
                rC = sub_3D3E0(unk_2A8);
                while (rC)
                {
                    if (rC->vf_018(var_10))
                        break;
                    rC = sub_3D3E0(rC->get_unk_14().unk_00);
                }
            }
        }
    }
    sub_3D0B0(bp_4->get_unk_18());
}

// match: sub_3E570 @ 0x0003E570
// sp-match: sub_3E570 @ 0x0002F1C0
void type_3DF30::sub_3E570(type_3CE6D0 *arg_0, void (*arg_4)(type_3D3548 *, void *),
                           RwInt32 arg_8, void *arg_C)
{
#ifndef CODFH_SP
    AIData *var_10;
    RwUInt32 ebp_C;
#endif
    type_3CE6D0 *v8;
    type_3D3548 *var_4;

    for (var_4 = unk_00; var_4 != 0; var_4 = var_4->vf_118()) {
#ifdef CODFH_SP // shape: the handle straight from the getter (SP 0x2F1E0 pushes it from eax, no locals kept)
        v8 = sub_3D3E0(var_4->vf_120()->get_unk_574());
#else
        var_10 = var_4->vf_120();
        ebp_C = var_10->unk_574;
        v8 = sub_3D3E0(ebp_C);
#endif
        if (!((v8 == 0 || v8->vf_02C() >= arg_0->vf_02C())
                && var_4->vf_120()->unk_51C != 0 && (var_4->unk_2C & 0x3FFFFF0 & arg_8) != 0
                && ((var_4->vf_120()->unk_49C >> 4) & 1) != 0))
            continue;
        arg_4(var_4, arg_C);
    }
}

// match: sub_3E650 @ 0x0003E650
// sp-match: sub_3E650 @ 0x0002F260
void type_3DF30::sub_3E650(type_3D3548 *arg_0, RwInt32 arg_4)
{
    RwUInt32 varC;
    type_3CE6D0 *local_8;
    AIData *var_4;

    if (unk_00 == 0)
        unk_2B0 = arg_0->unk_2C & 7;
    arg_0->vf_11C(unk_00);
    unk_00 = arg_0;
    var_4 = arg_0->vf_120();
    if (var_4 != 0)
        var_4->sub_17030(this);
    if (arg_4 != 0) {
        local_8 = sub_3D3E0(unk_2A8);
        while (local_8 != 0) {
            if (local_8->vf_018(arg_0))
                break;
            varC = local_8->unk_14;
            local_8 = sub_3D3E0(varC);
        }
    }
}

// match: sub_3E710 @ 0x0003E710
// sp-match: sub_3E710 @ 0x0002F2F0
RwInt32 type_3DF30::sub_3E710(type_3D3548 *arg_0)
{
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = 0;
    local_8 = unk_2B0;
    if ((((arg_0->unk_2C & 7) ^ local_8) != 0 && (arg_0->unk_2C & 7) != 0 && local_8 != 0) != 0)
        return -1;
    var_4++;
    return var_4;
}

// match: sub_3E780 @ 0x0003E780
// sp-match: sub_3E780 @ 0x0002F320
void type_3DF30::sub_3E780(type_3D3548 *arg_0)
{
    if (arg_0 != 0)
        unk_2BC.sub_D48D0(arg_0);
    else
        unk_2BC.sub_D48D0(0);
}

// match: sub_3E7C0 @ 0x0003E7C0
// sp-match: sub_3E7C0 @ 0x0002F340
void type_3DF30::sub_3E7C0(type_3D3548 *arg_0)
{
    AIData *local_20;
    AIData *var_1C;
    RwUInt32 var18;
    RwUInt32 stk_14;
    type_3D3548 *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    AIData *var_4;

    var_4 = arg_0->vf_120();
    if (var_4 != 0) {
        l10 = unk_00;
        lv_8 = 0;
        local_C = 0;
        while (l10 != 0) {
            if (l10 == arg_0) {
                local_C = 1;
                var_1C = arg_0->vf_120();
                stk_14 = var_1C->unk_574;
                if (stk_14 != 0) {
                    local_20 = arg_0->vf_120();
                    var18 = local_20->unk_574;
                    sub_3D3E0(var18)->vf_014(arg_0);
                }
                if (lv_8 != 0)
                    lv_8->vf_11C(arg_0->vf_118());
                else
                    unk_00 = arg_0->vf_118();
                break;
            }
            lv_8 = l10;
            l10 = l10->vf_118();
        }
        arg_0->vf_11C(0);
    }
}

// match: sub_3E8F0 @ 0x0003E8F0
// sp-match: sub_3E8F0 @ 0x0002F410
void type_3DF30::sub_3E8F0(RwInt32 arg_0)
{
    RwUInt32 var_10;
    type_3CE6D0 *ebp_C;
    type_365A0 v8;
    type_3CE6D0 *var_4;

    for (ebp_C = sub_3D3E0(unk_2A8); ebp_C != 0; var_10 = ebp_C->unk_14, ebp_C = sub_3D3E0(var_10)) {
        if (ebp_C->vf_030() == arg_0)
            return;
    }
    v8 = sub_3CE20(arg_0);
    var_4 = sub_3D3E0(unk_2A8);
    var_4->unk_10 = 1;
    sub_3E2C0(v8);
}

// match: sub_3E990 @ 0x0003E990
// sp-match: sub_3E990 @ 0x0002F480
void type_3DF30::sub_3E990(type_3D3548 *arg_0, RwInt32 arg_4)
{
    RwUInt32 local_8;
    type_3CE6D0 *var_4;

    sub_3E8F0(arg_4);
    var_4 = 0;
    for (var_4 = sub_3D3E0(unk_2A8); var_4 != 0; local_8 = var_4->unk_14, var_4 = sub_3D3E0(local_8)) {
        if (var_4->vf_030() == arg_4)
            break;
    }
    if (var_4 == 0)
        return;
    var_4->vf_01C(arg_0);
}

// match: sub_3EA20 @ 0x0003EA20
// sp-match: sub_3EA20 @ 0x0002F4E0
void type_3DF30::sub_3EA20(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_2C0[arg_0] = arg_4;
    if (arg_4 != 0)
        sub_3E8F0(arg_0);
}

// match: sub_3EA50 @ 0x0003EA50
// sp-match: sub_3EA50 @ 0x0002F500
void type_3DF30::sub_3EA50(RwV3d *arg_0)
{
    RwUInt32 local_8;
    type_3CE6D0 *var_4;

    var_4 = 0;
    for (var_4 = sub_3D3E0(unk_2A8); var_4 != 0; local_8 = var_4->unk_14, var_4 = sub_3D3E0(local_8)) {
        if (var_4->vf_030() == 5)
            break;
    }
    if (var_4 == 0)
        return;
    static_cast<type_3CE5E8 *>(var_4)->sub_3A170(arg_0);
}

// match: sub_3EAD0 @ 0x0003EAD0
// sp-match: sub_3EAD0 @ 0x0002F550
void type_3DF30::sub_3EAD0(RwReal arg_0)
{
    RwUInt32 local_8;
    type_3CE6D0 *var_4;

    var_4 = 0;
    for (var_4 = sub_3D3E0(unk_2A8); var_4 != 0; local_8 = var_4->unk_14, var_4 = sub_3D3E0(local_8)) {
        if (var_4->vf_030() == 5)
            break;
    }
    if (var_4 == 0)
        return;
    static_cast<type_3CE5E8 *>(var_4)->unk_5DC = arg_0;
    static_cast<type_3CE5E8 *>(var_4)->unk_5E0 = arg_0 * arg_0;
    static_cast<type_3CE5E8 *>(var_4)->unk_5E4 = arg_0 + 500.0f;
    static_cast<type_3CE5E8 *>(var_4)->unk_5E8 =
        static_cast<type_3CE5E8 *>(var_4)->unk_5E4 * static_cast<type_3CE5E8 *>(var_4)->unk_5E4;
}

// match: sub_3EB80 @ 0x0003EB80
// sp-match: sub_3EB80 @ 0x0002F5C0
void type_3DF30::sub_3EB80(RwInt32 arg_0, RwInt32 arg_4)
{
    RwUInt32 local_8;
    type_3CE6D0 *var_4;

    if (arg_0 != 0)
        unk_2DC |= 1 << arg_4;
    else
        unk_2DC &= ~(1 << arg_4);
    var_4 = 0;
    for (var_4 = sub_3D3E0(unk_2A8); var_4 != 0; local_8 = var_4->unk_14, var_4 = sub_3D3E0(local_8)) {
        if (var_4->vf_030() == arg_4)
            break;
    }
    if (var_4 == 0)
        return;
    var_4->vf_020(arg_0);
}

// match: sub_3EC40 @ 0x0003EC40
// sp-match: sub_3EC40 @ 0x0002F7C0
void sub_3EC40()
{
#ifdef CODFH_SP
    // Single player's squad pool has 5 slots, not 25 (SP 0x2F7C9).
    dword_4395F8.sub_16C2C0(5, 0x2E0, "m_freeSquadList", 4, 0);
#else
    dword_4395F8.sub_16C2C0(0x19, 0x2E0, "m_freeSquadList", 4, 0);
#endif
    dword_4395F4 = 1;
    dword_4395F0 = 0;
}

// match: sub_3EC80 @ 0x0003EC80
// sp-match: sub_3EC80 @ 0x0002FA40
// The restart: the squads go, and ids start again from 1.
void sub_3EC80()
{
    sub_3ECC0();
    sub_3F040();
    dword_4395F4 = 1;
}

// match: sub_3ECA0 @ 0x0003ECA0
// sp-match: sub_3ECA0 @ 0x0002FA60
// The shutdown: the squads go, and so does their pool.
void sub_3ECA0()
{
    sub_3ECC0();
    sub_3F040();
    dword_4395F8.sub_16C4D0(1);
}

// match: sub_3ECC0 @ 0x0003ECC0
// sp-match: sub_3ECC0 @ 0x0002F7F0
// Warns about each squad that still has an entity.
void sub_3ECC0()
{
    type_3D3548 *varC;
    type_3DF30 *local_8;
    type_3DF30 *var_4;

    local_8 = dword_4395F0;
    var_4 = 0;
    while (local_8 != 0) {
        var_4 = local_8->unk_2AC;
        varC = local_8->unk_00;
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        // Single player compiles the debug print out (SP 0x2F7F0 only walks the list).
        if (varC != 0)
            sub_19A750("An entity was not removed from a squad during restart/shutdown!");
#endif
        local_8 = var_4;
    }
}

// match: sub_3ED10 @ 0x0003ED10
// sp-match: sub_3ED10 @ 0x0002F810
// The AI update, with the time step arg_0: the other schedulers, every
// squad, then the per-frame counts.
void sub_3ED10(RwReal arg_0)
{
    type_3DF30 *var_4;

    sub_3C2B0(arg_0);
    sub_408F0(arg_0);
    sub_350F0(arg_0);
    sub_19A750(arg_0);
    sub_331F0(arg_0);
    for (var_4 = dword_4395F0; var_4 != 0; var_4 = var_4->unk_2AC)
        var_4->sub_3E180(arg_0);
    if (dword_4C00D0.unk_00 != dword_4B87D8) {
        dword_4C00D0.unk_00 = dword_4B87D8;
        if (dword_4C00D0.unk_0C > dword_4C00D0.unk_10)
            dword_4C00D0.unk_10 = dword_4C00D0.unk_0C;
        dword_4C00D0.unk_04 = 0;
        dword_4C00D0.unk_0C = 0;
    }
    if (dword_4C0150.unk_00 != dword_4B87D8) {
        dword_4C0150.unk_00 = dword_4B87D8;
        if (dword_4C0150.unk_0C > dword_4C0150.unk_10)
            dword_4C0150.unk_10 = dword_4C0150.unk_0C;
        dword_4C0150.unk_04 = 0;
        dword_4C0150.unk_0C = 0;
    }
}

// match: sub_3EE10 @ 0x0003EE10
// sp-match: sub_3EE10 @ 0x0002FA80
// Puts the entity arg_0 in a squad: the one whose id its AI object keeps,
// else the best fit (sub_3E710), else a new one.
void sub_3EE10(type_3D3548 *arg_0)
{
    RwInt32 var_1C;
    RwInt32 var18;
    RwInt32 stk_14;
    type_3DF30 *l10;
    type_3DF30 *local_C;
    AIData *lv_8;
    RwInt32 var_4;

    var_4 = -1;
    local_C = 0;
    lv_8 = arg_0->vf_120();
    if (lv_8 != 0) {
        var18 = lv_8->unk_570;
        if (var18 != 0) {
            var_1C = lv_8->unk_570;
            local_C = sub_3F080(var_1C);
            if (local_C != 0) {
                local_C->sub_3E650(arg_0, 1);
                return;
            }
        }
    }
    for (l10 = dword_4395F0; l10 != 0; l10 = l10->unk_2AC) {
        stk_14 = l10->sub_3E710(arg_0);
        if (stk_14 > var_4) {
            var_4 = stk_14;
            local_C = l10;
        }
    }
    if (local_C == 0)
        local_C = sub_3EEE0();
    local_C->sub_3E650(arg_0, 1);
}

// match: ?sub_3EEE0@@YAPAUtype_3DF30@@XZ @ 0x0003EEE0
// match: __ehhandler$?sub_3EEE0@@YAPAUtype_3DF30@@XZ-0x11 @ 0x002FF6F0
// match: __ehhandler$?sub_3EEE0@@YAPAUtype_3DF30@@XZ @ 0x002FF701
// sp-match: ?sub_3EEE0@@YAPAUtype_3DF30@@XZ @ 0x0002F8C0
// Builds a squad in its pool slot, assigns the next id and links it first.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3DF30 *sub_3EEE0()
{
    type_3DF30 *var_14;
    void *lv_10;

    lv_10 = dword_4395F8.sub_16C5A0(0);
    var_14 = new (lv_10) type_3DF30;
    var_14->sub_3DF90(dword_4395F4++);
    var_14->unk_2AC = get_squad_list();
    dword_4395F0 = var_14;
    return var_14;
}

// match: sub_3EFB0 @ 0x0003EFB0
// sp-match: sub_3EFB0 @ 0x0002F950
// Takes the squad arg_0 off the list, destroys it and frees its slot.
void sub_3EFB0(type_3DF30 *arg_0)
{
    type_3DF30 *var_10;
    type_3DF30 *ebp_C;
    type_3DF30 *v8;
    type_3DF30 *var_4;

    for (var_4 = dword_4395F0; var_4 != 0; var_4 = var_4->unk_2AC) {
        v8 = var_4->unk_2AC;
        if (v8 == arg_0)
            break;
    }
    if (var_4 != 0) {
        ebp_C = arg_0->unk_2AC;
        var_4->unk_2AC = ebp_C;
    } else {
        var_10 = arg_0->unk_2AC;
        dword_4395F0 = var_10;
    }
    arg_0->sub_3E0A0();
    dword_4395F8.sub_16C710(arg_0);
}

// match: sub_3F040 @ 0x0003F040
// sp-match: sub_3F040 @ 0x0002F9B0
void sub_3F040()
{
    type_3DF30 *local_8;
    type_3DF30 *var_4;

    local_8 = dword_4395F0;
    var_4 = 0;
    while (local_8 != 0) {
        var_4 = local_8->unk_2AC;
        sub_3EFB0(local_8);
        local_8 = var_4;
    }
}

// match: sub_3F080 @ 0x0003F080
// sp-match: sub_3F080 @ 0x0002F9E0
// The squad with the id arg_0, else 0.
type_3DF30 *sub_3F080(RwInt32 arg_0)
{
    type_3DF30 *var_4;

    var_4 = dword_4395F0;
    while (var_4 != 0) {
        if (var_4->get_unk_2B4() == arg_0)
            return var_4;
        var_4 = var_4->unk_2AC;
    }
    return 0;
}

// match: sub_3F0D0 @ 0x0003F0D0
// sp-match: sub_3F0D0 @ 0x0002FA10
// The squad on the side arg_0, else 0.
type_3DF30 *sub_3F0D0(RwInt32 arg_0)
{
    type_3DF30 *var_4;

    var_4 = dword_4395F0;
    while (var_4 != 0) {
        if (var_4->get_unk_2B0() == arg_0)
            return var_4;
        var_4 = var_4->unk_2AC;
    }
    return 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_19A750@@YAXM@Z (folded into 0x19A750)
#ifndef CODFH_SP
// Single player keeps sub_3ED10's call (SP 0x2F82B), so the empty body is not in this file there.
void sub_19A750(RwReal arg_0)
{
}
#endif

// ??2@YAPAXIPAX@Z (folded into 0x6CCF0): the global placement new sub_3EEE0 calls out of
// line (defined here for the authentic link, so no library's copy comes in)
#ifndef CODFH_WIN32
void *operator new(RwUInt32 arg_0, void *arg_4) throw()
{
    return arg_4;
}
#endif

// ??3@YAXPAX0@Z (folded into 0x19A750): the global placement delete its cleanup calls
// (inline, as the XDK <new> defines it: the units that emit <new>'s copy share it; the body
// after its callers keeps their calls out of line)
#ifndef CODFH_WIN32
inline void operator delete(void *arg_0, void *arg_4) throw()
{
}
#endif
