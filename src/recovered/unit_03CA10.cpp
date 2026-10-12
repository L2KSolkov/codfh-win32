// type_3CE6D0's own methods (from its constructor sub_3CA10), then the
// AIManeuverManager: the pools the kinds are drawn from
// ("m_freeManeuversLarge", "m_freeManeuversNormal"), the kind factory
// sub_3CE20 and the handle table dword_4392A8. Its original file name is not
// in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/type_3CE6D0.h"
#include "types/type_3CE278.h"
#include "types/type_3CE4B4.h"
#include "types/type_3CE4F0.h"
#include "types/type_3CE5AC.h"
#include "types/type_3CE5E8.h"
#include "types/type_3CE854.h"
#include "types/type_365A0.h"
#include "types/type_3D3548.h"
#include "types/type_3DF30.h"

// The table's functions (in other units; sub_170ED0 is what several
// folded into).
RwInt32 sub_170ED0(RwInt32 arg_0);
RwInt32 sub_37220(RwInt32 arg_0, type_3D410 *arg_4);
RwInt32 sub_39AA0(RwInt32 arg_0, type_3D410 *arg_4);
RwInt32 sub_32700(RwInt32 arg_0, type_3D410 *arg_4);

#if !defined(CODFH_SP) || CODFH_SP_PART == 1 // single player: sub_3D3E0 alone in a second file (src/sp/units/sp_unit_03CA10_2.cpp)
// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE6CC
extern const RwReal flt_3CE6CC = 16.666666f;
// 0x00427628
type_427628 off_427628[7] = {
    { (RwInt32 (*)(RwInt32, type_3D410 *))(RwInt32 (*)(RwInt32))sub_170ED0, 32 },
    { sub_37220, 76 },
    { 0, 0 },
    { (RwInt32 (*)(RwInt32, type_3D410 *))(RwInt32 (*)(RwInt32))sub_170ED0, 32 },
    { (RwInt32 (*)(RwInt32, type_3D410 *))(RwInt32 (*)(RwInt32))sub_170ED0, 36 },
    { sub_39AA0, 1524 },
    { sub_32700, 52 },
};
// 0x004392A8
type_4392A8 dword_4392A8[64];
// 0x004395A8
RwInt32 dword_4395A8;
// 0x004395AC
RwInt32 dword_4395AC;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4395B0;
type_16C2A0 dword_4395D0;
#else
extern type_4392A8 dword_4392A8[64];
#endif
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE6CC@@3MB @ 0x003CE6CC
// match: ??_7type_3CE6D0@@6B@ @ 0x003CE6D0
// match: ??_C@_0BG@PJDOMJLI@m_freeManeuversNormal?$AA@ @ 0x003CE704
// match: ??_C@_0BF@FIBBKFFH@m_freeManeuversLarge?$AA@ @ 0x003CE71C
// match: ??_C@_0FD@CDHLGMJK@AIManeuverManager?3?5Some?5normal?5m@ @ 0x003CE738
// match: ??_C@_0FC@OMCIJCHD@AIManeuverManager?3?5Some?5large?5ma@ @ 0x003CE790
// match: __ehhandler$?sub_3CE20@@YA?ATtype_365A0@@H@Z>1>8 @ 0x0041B048
// match: __ehhandler$?sub_3CE20@@YA?ATtype_365A0@@H@Z>1 @ 0x0041B078
// match: .CRT$XCU+0 @ 0x00426D80
// match: .CRT$XCU+4 @ 0x00426D84
// match: ?off_427628@@3PAUtype_427628@@A @ 0x00427628

// match: _$E2 @ 0x00309830
// match: _$E3 @ 0x0030DCA0
// match: _$E5 @ 0x00309850
// match: _$E6 @ 0x0030DCB0
// sp-match: _$E6 @ 0x0021E0E0
// sp-match: _$E2 @ 0x0021C2B0
// sp-match: _$E5 @ 0x0021C2D0
// sp-match: _$E3 @ 0x0021E0D0

void sub_3CD10();
RwInt32 sub_3CD60();
RwInt32 sub_3CDB0();
// Creates an object of kind arg_0 in a pool
// slot (placement new) and registers it (sub_3D2E0); returns its handle.
type_365A0 sub_3CE20(RwInt32 arg_0);
// Runs the update test (vf_010) of the group arg_0's objects from the
// handle arg_8, dropping
// those that fail, and creates the best-scoring kind not masked by arg_C
// unless the group has one; returns its handle.
#ifdef CODFH_SP
// Single player passes and returns the handle by value (SP 0x2E770, 0x2E8A0).
type_365A0 sub_3D150(type_3DF30 *arg_0, type_3D410 *arg_4, type_365A0 arg_8, RwInt32 arg_C);
#else
RwUInt32 sub_3D150(type_3DF30 *arg_0, type_3D410 *arg_4, RwUInt32 arg_8, RwInt32 arg_C);
#endif
type_365A0 sub_3D2E0(type_3CE6D0 *arg_0, RwInt32 arg_4);
void sub_3D3A0(type_365A0 arg_0);

// Registers an object and stores its handle: an inline with no address,
// named for what it does. Evidence: sub_3CE20 places the registration
// return temporary at -0x50, after the pool-size getter at -0x4C. Keeping
// the call inside this inline allocates it during expansion in that order.
static inline void register_maneuver_handle(type_3CE6D0 *object, RwInt32 kind)
{
    object->unk_18_h = sub_3D2E0(object, kind);
}

#if !defined(CODFH_SP) || CODFH_SP_PART == 1
// match: ??0type_3CE6D0@@QAE@XZ @ 0x0003CA10
// sp-match: ??0type_3CE6D0@@QAE@XZ @ 0x0002E210
// symbol: ??_7type_3CE6D0@@6B@ = 0x003CE6D0
type_3CE6D0::type_3CE6D0()
{
    unk_08 = 0;
    unk_14 = 0;
}

// match: ??_Gtype_3CE6D0@@UAEPAXI@Z @ 0x0003CA40
// match: ??1type_3CE6D0@@UAE@XZ @ 0x0003CA60
// sp-match: ??1type_3CE6D0@@UAE@XZ @ 0x0002E230
// sp-match: ??_Gtype_3CE6D0@@UAEPAXI@Z @ 0x0002E310
type_3CE6D0::~type_3CE6D0()
{
    unk_08 = 0;
}

// match: ?vf_004@type_3CE6D0@@UAEXPAUtype_3DF30@@@Z @ 0x0003CA80
// sp-match: ?vf_004@type_3CE6D0@@UAEXPAUtype_3DF30@@@Z @ 0x0002E240
void type_3CE6D0::vf_004(type_3DF30 *arg_0)
{
    unk_08 = arg_0;
    unk_04 = 1;
    unk_10 = 0;
}

// match: ?vf_00C@type_3CE6D0@@UAEHMPAUtype_3D410@@@Z @ 0x0003CAB0
// sp-match: ?vf_00C@type_3CE6D0@@UAEHMPAUtype_3D410@@@Z @ 0x0002E260
RwInt32 type_3CE6D0::vf_00C(RwReal arg_0, type_3D410 *arg_4)
{
    if (unk_04 != 0)
        unk_04 = 0;
    return 1;
}

// match: ?vf_010@type_3CE6D0@@UAEHPAUtype_3D410@@@Z @ 0x0003CAE0
// sp-match: ?vf_010@type_3CE6D0@@UAEHPAUtype_3D410@@@Z @ 0x0002E280
RwInt32 type_3CE6D0::vf_010(type_3D410 *arg_0)
{
    return 0x7FFFFFF;
}

// match: ?vf_01C@type_3CE6D0@@UAEHPAUtype_3D3548@@@Z @ 0x0003CB00
// sp-match: ?vf_01C@type_3CE6D0@@UAEHPAUtype_3D3548@@@Z @ 0x0002E290
// Takes the entity arg_0 on, from the object it served (vf_014).
RwInt32 type_3CE6D0::vf_01C(type_3D3548 *arg_0)
{
    AIData *var_1C;
    RwUInt32 var18;
    AIData *stk_14;
    RwUInt32 l10;
    RwUInt32 local_C;
    RwUInt32 lv_8;
    type_3CE6D0 *var_4;

    stk_14 = arg_0->vf_120();
    lv_8 = stk_14->unk_574;
    var_4 = sub_3D3E0(lv_8);
    if (var_4 != 0) {
        local_C = unk_18;
        if (var_4 == sub_3D3E0(local_C))
            return 1;
        var_4->vf_014(arg_0);
    }
    var18 = l10 = unk_18;
    var_1C = arg_0->vf_120();
    var_1C->unk_574 = var18;
    return 1;
}

// match: ?vf_014@type_3CE6D0@@UAEXPAUtype_3D3548@@@Z @ 0x0003CBB0
// sp-match: ?vf_014@type_3CE6D0@@UAEXPAUtype_3D3548@@@Z @ 0x0002E2F0
void type_3CE6D0::vf_014(type_3D3548 *arg_0)
{
    AIData *local_8;
    RwUInt32 var_4;

    var_4 = 0;
    local_8 = arg_0->vf_120();
    local_8->unk_574 = var_4;
}

// match: sub_3CBF0 @ 0x0003CBF0
// sp-match: sub_3CBF0 @ 0x0002E4D0
// Sets the pools up (sized for the largest kind and the next largest) and
// clears the handle table.
void sub_3CBF0()
{
    RwInt32 var_10;
    type_365A0 ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = sub_3CD60();
    var_4 = sub_3CDB0();
#ifdef CODFH_SP
    // Single player's pools hold 5 large and 15 normal maneuvers (SP 0x2E4D0).
    dword_4395B0.sub_16C2C0(5, v8, "m_freeManeuversLarge", 4, 0);
    dword_4395D0.sub_16C2C0(15, var_4, "m_freeManeuversNormal", 4, 0);
#else
    dword_4395B0.sub_16C2C0(0x20, v8, "m_freeManeuversLarge", 4, 0);
    dword_4395D0.sub_16C2C0(0x20, var_4, "m_freeManeuversNormal", 4, 0);
#endif
#ifdef CODFH_SP
    // single player's handle table has 20 entries (SP 0x2E4D0, 0x2E540, 0x2E400)
    for (var_10 = 0; var_10 < 20; var_10++) {
#else
    for (var_10 = 0; var_10 < 0x40; var_10++) {
#endif
        ebp_C.unk_00_lo = var_10;
        sub_3D3A0(ebp_C);
    }
    dword_4395A8 = 0;
    dword_4395AC = 0;
}

// match: sub_3CC80 @ 0x0003CC80
// sp-match: sub_3CC80 @ 0x0002E540
void sub_3CC80()
{
    RwInt32 local_8;
    type_365A0 var_4;

    sub_3CD10();
#ifdef CODFH_SP
    // single player's handle table has 20 entries (SP 0x2E4D0, 0x2E540, 0x2E400)
    for (local_8 = 0; local_8 < 20; local_8++) {
#else
    for (local_8 = 0; local_8 < 0x40; local_8++) {
#endif
        var_4.unk_00_lo = local_8;
        sub_3D3A0(var_4);
    }
    dword_4395A8 = 0;
    dword_4395AC = 0;
}

// match: sub_3CCE0 @ 0x0003CCE0
// sp-match: sub_3CCE0 @ 0x0002E580
void sub_3CCE0()
{
    sub_3CD10();
    dword_4395B0.sub_16C4D0(1);
    dword_4395D0.sub_16C4D0(1);
}

// match: sub_3CD10 @ 0x0003CD10
void sub_3CD10()
{
    if (dword_4395B0.in_use()) {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        // single player compiles the warnings out (their texts are not in default.xbe; its
        // callers call an empty function, SP 0x2E541, 0x2E580)
        sub_19A750("AIManeuverManager: Some large maneuvers were not deleted during restart/shutdown!");
#endif
    }
    if (dword_4395D0.in_use()) {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
        sub_19A750("AIManeuverManager: Some normal maneuvers were not deleted during restart/shutdown!");
#endif
    }
}

// match: sub_3CD60 @ 0x0003CD60
// sp-match: sub_3CD60 @ 0x0002E320
// The largest kind's size.
RwInt32 sub_3CD60()
{
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = 0;
    for (local_8 = 0; local_8 < 7; local_8++) {
        if (off_427628[local_8].unk_04 > var_4)
            var_4 = off_427628[local_8].unk_04;
    }
    return var_4;
}

// match: sub_3CDB0 @ 0x0003CDB0
// sp-match: sub_3CDB0 @ 0x0002E380
// The next largest size.
RwInt32 sub_3CDB0()
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = sub_3CD60();
    local_8 = 0;
    for (varC = 0; varC < 7; varC++) {
        if (off_427628[varC].unk_04 > local_8 && off_427628[varC].unk_04 < var_4)
            local_8 = off_427628[varC].unk_04;
    }
    return local_8;
}

// match: ?sub_3CE20@@YA?ATtype_365A0@@H@Z @ 0x0003CE20
// match: __ehhandler$?sub_3CE20@@YA?ATtype_365A0@@H@Z-0x66 @ 0x002FF660
// match: __ehhandler$?sub_3CE20@@YA?ATtype_365A0@@H@Z @ 0x002FF6C6
// sp-match: ?sub_3CE20@@YA?ATtype_365A0@@H@Z @ 0x0002E5A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_365A0 sub_3CE20(RwInt32 arg_0)
{
    RwInt32 ebp_14;
    type_3CE6D0 *lv_10;

    ebp_14 = off_427628[arg_0].unk_04;
    lv_10 = 0;
    if (ebp_14 <= dword_4395D0.get_unk_10())
        lv_10 = (type_3CE6D0 *)dword_4395D0.sub_16C5A0(0);
    else
        lv_10 = (type_3CE6D0 *)dword_4395B0.sub_16C5A0(0);
    switch (arg_0)
    {
    case 0: lv_10 = new (lv_10) type_3CE4B4; break;
    case 1: lv_10 = new (lv_10) type_3CE5AC; break;
    case 3: lv_10 = new (lv_10) type_3CE4F0; break;
    case 4: lv_10 = new (lv_10) type_3CE854; break;
    case 5: lv_10 = new (lv_10) type_3CE5E8; break;
    case 6: lv_10 = new (lv_10) type_3CE278; break;
    }
    register_maneuver_handle(lv_10, arg_0);
    return lv_10->get_unk_18();
}

// match: sub_3D0B0 @ 0x0003D0B0
// sp-match: sub_3D0B0 @ 0x0002E720
// Destroys the object with handle arg_0: its vf_008, back to its pool, and
// its handle freed.
void sub_3D0B0(type_365A0 arg_0)
{
    type_3CE6D0 *var_4;

    var_4 = sub_3D3E0(arg_0.unk_00);
    var_4->vf_008();
    if (dword_4395B0.sub_16C770(var_4))
        dword_4395B0.sub_16C710(var_4);
    else
        dword_4395D0.sub_16C710(var_4);
    sub_3D3A0(arg_0);
}

// match: sub_3D120 @ 0x0003D120
// sp-match: sub_3D120 @ 0x0002E8A0
RwUInt32 sub_3D120(type_3DF30 *arg_0, type_3D410 *arg_4, RwInt32 arg_8)
{
#ifdef CODFH_SP
    // the null handle by value (SP 0x2E8A0)
    type_365A0 var_4;
#else
    RwUInt32 var_4;
#endif
    RwUInt32 local_8;

#ifdef CODFH_SP
    var_4.unk_00 = 0;
#else
    var_4 = 0;
#endif
#ifdef CODFH_SP
    // SP 0x2E8A0 receives the handle returned by value.
    local_8 = sub_3D150(arg_0, arg_4, var_4, arg_8).unk_00;
#else
    // MP 0x3D120 receives the scalar handle (no union-return temporary).
    local_8 = sub_3D150(arg_0, arg_4, var_4, arg_8);
#endif
    return local_8;
}

// match: ?sub_3D150@@YAIPAUtype_3DF30@@PAUtype_3D410@@IH@Z @ 0x0003D150
// sp-match: ?sub_3D150@@YAIPAUtype_3DF30@@PAUtype_3D410@@IH@Z @ 0x0002E770
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
#ifdef CODFH_SP
// The parameter and return value are handles by value (SP 0x2E770).
type_365A0 sub_3D150(type_3DF30 *arg_0, type_3D410 *arg_4, type_365A0 arg_8, RwInt32 arg_C)
#else
// MP 0x3D150 passes and returns scalar handle bits.
RwUInt32 sub_3D150(type_3DF30 *arg_0, type_3D410 *arg_4, RwUInt32 arg_8, RwInt32 arg_C)
#endif
{
    // Named handle copies precede the factory's union-return temporary
    // at -0x64; the original receiver and score slots remain above them.
    RwUInt32 stk_60;
    RwUInt32 y5C;
    RwInt32 stk_58;
    RwInt32 l54;
    RwInt32 var50;
    RwInt32 x4C;
    type_3CE6D0 *w48;
    type_3CE6D0 *loc44;
#ifdef CODFH_SP
    // SP 0x2E770 returns the null handle or the factory's handle directly.
    type_365A0 fp_40;
#else
    // MP 0x3D150.
    RwUInt32 fp_40;
#endif
    RwInt32 l3C[7];
    RwInt32 var_20[7];
    type_3CE6D0 *bp_4;

#ifdef CODFH_SP
    fp_40.unk_00 = 0;
    bp_4 = sub_3D3E0(arg_8.unk_00);
#else
    fp_40 = 0;
    bp_4 = sub_3D3E0(arg_8);
#endif
    x4C = -1;
    var50 = -1;
    for (l54 = 0; l54 < 7; l54++)
    {
        l3C[l54] = -1;
        var_20[l54] = 0;
    }
    loc44 = bp_4;
    while (loc44)
    {
        y5C = loc44->unk_14;
        w48 = sub_3D3E0(y5C);
        l3C[loc44->vf_030()] = loc44->vf_010(arg_4);
        if (l3C[loc44->vf_030()] == -1)
        {
#ifdef CODFH_SP
            arg_0->sub_3E3B0(loc44->get_unk_18());
#else
            stk_60 = loc44->unk_18;
            arg_0->sub_3E3B0(stk_60);
#endif
        }
        else
            var_20[loc44->vf_030()] = 1;
        loc44 = w48;
    }
    for (stk_58 = 0; stk_58 < 7; stk_58++)
    {
        if (!(arg_C & (1 << stk_58)))
        {
            if (l3C[stk_58] == -1 && off_427628[stk_58].unk_00)
                l3C[stk_58] = off_427628[stk_58].unk_00(stk_58, arg_4);
            if (l3C[stk_58] > x4C)
            {
                x4C = l3C[stk_58];
                var50 = stk_58;
            }
        }
    }
    if (var_20[var50])
        return fp_40;
#ifdef CODFH_SP
    // SP 0x2E770 preserves the factory's union return.
    return sub_3CE20(var50);
#else
    // MP 0x3D150.
    return sub_3CE20(var50).unk_00;
#endif
}

// match: sub_3D2E0 @ 0x0003D2E0
// sp-match: sub_3D2E0 @ 0x0002E400
// Gives the object arg_0 (of kind arg_4) the first free handle, with a new
// serial.
type_365A0 sub_3D2E0(type_3CE6D0 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;
    type_365A0 v8;
    RwInt32 varC;

    var_4 = 0;
    if (dword_4395A8 == 0)
        dword_4395A8 = 1;
#ifdef CODFH_SP
    // single player's handle table has 20 entries (SP 0x2E4D0, 0x2E540, 0x2E400)
    for (varC = 1; varC < 20; varC++) {
#else
    for (varC = 1; varC < 0x40; varC++) {
#endif
        if (dword_4392A8[varC].unk_00.unk_00 == 0 && dword_4392A8[varC].unk_08 == 0) {
            v8.unk_00_lo = varC;
            v8.unk_02 = dword_4395A8;
#ifdef CODFH_SP // shape: the handle copied as its dword (SP 0x2E400 stores the entry's object before its handle)
            dword_4392A8[v8.unk_00_lo].unk_00.unk_00 = v8.unk_00;
#else
            dword_4392A8[v8.unk_00_lo].unk_00 = v8;
#endif
            dword_4392A8[v8.unk_00_lo].unk_08 = arg_0;
            dword_4392A8[v8.unk_00_lo].unk_04 = arg_4;
            var_4 = 1;
            dword_4395A8++;
            break;
        }
    }
    return v8;
}

// match: sub_3D3A0 @ 0x0003D3A0
// sp-match: sub_3D3A0 @ 0x0002E480
void sub_3D3A0(type_365A0 arg_0)
{
    dword_4392A8[arg_0.unk_00_lo].unk_00.unk_00 = 0;
    dword_4392A8[arg_0.unk_00_lo].unk_08 = 0;
    dword_4392A8[arg_0.unk_00_lo].unk_04 = -1;
}

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART == 2 // single player compiles sub_3D3E0 in another file (sp_unit_03CA10_2.cpp)
// match: sub_3D3E0 @ 0x0003D3E0
// sp-match: sub_3D3E0 @ 0x0002E4B0
type_3CE6D0 *sub_3D3E0(RwUInt32 arg_0)
{
    if (dword_4392A8[(RwUInt16)arg_0].unk_00.unk_00 == arg_0)
        return dword_4392A8[(RwUInt16)arg_0].unk_08;
    return 0;
}

#endif
#if !defined(CODFH_SP) || CODFH_SP_PART == 1
// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_008@type_3CE6D0@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3CE6D0::vf_008()
{
}

// ?vf_018@type_3CE6D0@@UAEHPAUtype_3D3548@@@Z (folded into `return 0` at 0x32260)
RwInt32 type_3CE6D0::vf_018(type_3D3548 *arg_0)
{
    return 0;
}

// ?vf_020@type_3CE6D0@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3CE6D0::vf_020(RwInt32 arg_0)
{
}

// ?vf_024@type_3CE6D0@@UAEHPAUtype_3D3548@@@Z (folded into `return 0` at 0x32260)
RwInt32 type_3CE6D0::vf_024(type_3D3548 *arg_0)
{
    return 0;
}

// ?vf_028@type_3CE6D0@@UAEXPAUtype_3D3548@@@Z (folded into the empty body at 0x15FB30)
void type_3CE6D0::vf_028(type_3D3548 *arg_0)
{
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_3CE6D0@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_3CE6D0::operator delete(void *arg_0, void *arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3CE6D0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3CE6D0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?vf_02C@type_3CE6D0@@UAEHXZ (folded into 0x9DFF0)
RwInt32 type_3CE6D0::vf_02C()
{
    return 0x7FFFFFFF;
}

// ?vf_030@type_3CE6D0@@UAEHXZ (folded into 0x9E030)
RwInt32 type_3CE6D0::vf_030()
{
    return -1;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

#ifndef CODFH_SP
// (single player defines it in unit_032210.cpp, beside its caller sub_32DD0)
// ?sub_18F420@type_3CE6D0@@QAEHPAUtype_F8350@@PAUtype_3D410@@@Z (folded into 0x18F420)
RwInt32 type_3CE6D0::sub_18F420(struct type_F8350 * arg_0, struct type_3D410 * arg_4)
{
    return 1;
}
#endif
#endif
