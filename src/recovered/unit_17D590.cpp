// The pulse zones (types/type_17DB90.h).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_3D3548.h"
#include "types/type_10F710.h"
#include "types/type_44350.h"
#include "types/type_17DB90.h"
#include "types/PulseZoneTrigger.h"
#include "types/type_F2880.h"
#include <string.h>
#include "game/netmsg.h"
#include "game/gameloop.h"
#include "types/type_3D32F8.h"
#include "rw/bavector.h"
#include "types/type_8A980.h"
#include "types/type_4AE70.h"
#include "types/type_92430.h"
#include "game/surfaceparticles.h"
#include "types/alfasched.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DE0A4
extern const RwReal flt_3DE0A4 = 16.666666f;
#ifndef CODFH_SP // MP only: single player has neither unreferenced 0.01f: type_17DB90's vtable follows 16.666666f (SP 0x2E9108)
// 0x003DE0A8
extern const RwReal flt_3DE0A8 = 0.01f;
// 0x003DE0AC
extern const RwReal flt_3DE0AC = 0.01f;
#endif
// 0x0042A4B4
void (*dword_42A4B4[4])(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8) = { sub_17DBD0, sub_17DD00, sub_17E200, 0 };
// 0x0042A4C4
void (*dword_42A4C4[4])(type_17DB90 *arg_0, type_3D3548 *arg_4) = { 0, 0, sub_17E260, 0 };
// 0x004E7268
type_4E7268 dword_4E7268[33];
// 0x004E7370
RwInt32 dword_4E7370;
// 0x004E7374
type_17DB90 *dword_4E7374;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_4E7378;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DE0A4@@3MB @ 0x003DE0A4
// match: ?flt_3DE0A8@@3MB @ 0x003DE0A8
// match: ?flt_3DE0AC@@3MB @ 0x003DE0AC
// match: ??_7type_17DB90@@6B@ @ 0x003DE0B0
// match: __ehhandler$??1type_17DB90@@UAE@XZ>1>8 @ 0x0041E4F8
// match: __ehhandler$??1type_17DB90@@UAE@XZ>1 @ 0x0041E500
// match: __ehhandler$?sub_17DE90@@YAXPAUtype_17DB90@@HH@Z>1>8 @ 0x0041E51C
// match: __ehhandler$?sub_17DE90@@YAXPAUtype_17DB90@@HH@Z>1 @ 0x0041E524
// match: .CRT$XCU+0 @ 0x0042716C
// match: ?dword_42A4B4@@3PAP6AXPAUtype_17DB90@@HH@ZA @ 0x0042A4B4
// match: ?dword_42A4C4@@3PAP6AXPAUtype_17DB90@@PAUtype_3D3548@@@ZA @ 0x0042A4C4

// match: _$E2 @ 0x0030BF60
// match: _$E3 @ 0x0030E990
// match: ??0type_17DB90@@QAE@XZ @ 0x0017D590
// sp-match: ??0type_17DB90@@QAE@XZ @ 0x00116670
// sp-match: _$E2 @ 0x0021DE30
// sp-match: _$E3 @ 0x0021ED50

type_17DB90::type_17DB90()
{
    unk_50 = 0;
}

// match: ??_Gtype_17DB90@@UAEPAXI@Z @ 0x0017D600
// match: ??1type_17DB90@@UAE@XZ @ 0x0017D630
// match: __ehhandler$??1type_17DB90@@UAE@XZ-0x16 @ 0x003021C0
// match: __ehhandler$??1type_17DB90@@UAE@XZ @ 0x003021D6
// sp-match: ??1type_17DB90@@UAE@XZ @ 0x001166D0
// sp-match: ??_Gtype_17DB90@@UAEPAXI@Z @ 0x001166B0
type_17DB90::~type_17DB90()
{
}

// match: ?vf_00C@type_17DB90@@UAEXPAVPulseZoneTrigger@@@Z @ 0x0017D6A0
// sp-match: ?vf_00C@type_17DB90@@UAEXPAVPulseZoneTrigger@@@Z @ 0x00116730
void type_17DB90::vf_00C(PulseZoneTrigger *arg_0)
{
    unk_C8 = arg_0->unk_C8;
    sub_17DA90(arg_0->unk_C4, arg_0->unk_D0, arg_0->unk_D4);
    sub_17DB50(arg_0->unk_C4, arg_0->unk_D0, arg_0->unk_D4);
}

// match: ?vf_004@type_17DB90@@UAEXPAVPulseZoneTrigger@@@Z @ 0x0017D710
// sp-match: ?vf_004@type_17DB90@@UAEXPAVPulseZoneTrigger@@@Z @ 0x001161C0
void type_17DB90::vf_004(PulseZoneTrigger *arg_0)
{
    unk_50 = 0;
    unk_5C.sub_144940(arg_0);
    unk_70 = ((type_712B0 *)arg_0)->unk_60_m;
    unk_54 = 1;
    unk_B0 = 0;
    unk_CC = 0;
    unk_58 = 0;
    unk_B4 = 0;
    unk_B8 = 0;
    memset(unk_10, 0, 0x40);
    vf_00C(arg_0);
}

// match: ?vf_008@type_17DB90@@UAEXXZ @ 0x0017D7C0
// sp-match: ?vf_008@type_17DB90@@UAEXXZ @ 0x00116230
void type_17DB90::vf_008()
{
    unk_5C.sub_144940(0);
}

// match: ?vf_010@type_17DB90@@UAEHM@Z @ 0x0017D7E0
// sp-match: ?vf_010@type_17DB90@@UAEHM@Z @ 0x00116780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_17DB90::vf_010(RwReal arg_0)
{
    RwReal var_10;
    PulseZoneTrigger *var_C;
    RwInt32 bp_8;
    type_3D3548 *bp_4;

    if (unk_58 > 0.0f)
    {
        unk_58 = unk_58 - arg_0;
        return 1;
    }
    bp_4 = 0;
    for (bp_8 = 0; bp_8 < 0x10; bp_8++)
    {
        bp_4 = unk_10[bp_8].sub_D4910();
        if (bp_4 && (bp_4->unk_28_9 || bp_4->unk_28_0))
            unk_10[bp_8].sub_D48D0(0);
    }
    var_C = (PulseZoneTrigger *)unk_5C.unk_08;
    var_10 = var_C->unk_CC;
    unk_58 = var_10;
    return sub_17D8B0();
}

// match: ?sub_17D8B0@type_17DB90@@QAEHXZ @ 0x0017D8B0
// sp-match: ?sub_17D8B0@type_17DB90@@QAEHXZ @ 0x00116240
RwInt32 type_17DB90::sub_17D8B0()
{
    if (unk_C8 > 0)
        unk_C8--;
    unk_B4(this, unk_C0, unk_C4);
    if (unk_C8 == 0)
        return 0;
    return 1;
}

// match: ?sub_17D920@type_17DB90@@QAEXH@Z @ 0x0017D920
// sp-match: ?sub_17D920@type_17DB90@@QAEXH@Z @ 0x00116280
void type_17DB90::sub_17D920(RwInt32 arg_0)
{
    unk_B0 = arg_0;
}

// match: ?sub_17D940@type_17DB90@@QAEXPAUtype_3D3548@@@Z @ 0x0017D940
// sp-match: ?sub_17D940@type_17DB90@@QAEXPAUtype_3D3548@@@Z @ 0x00116290
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_17DB90::sub_17D940(type_3D3548 *arg_0)
{
    PulseZoneTrigger *var_8;
    RwInt32 l4;

    var_8 = get_unk_64();
    if (var_8->unk_C0)
    {
        if (var_8->unk_C0 == 3)
        {
            if (!arg_0->unk_2C_4)
                return;
        }
        else if (var_8->unk_C0 != (arg_0->unk_2C & 7))
        {
            return;
        }
    }
    for (l4 = 0; l4 < 0x10; l4++)
    {
        if (unk_10[l4].sub_D4910() == arg_0)
            return;
    }
    for (l4 = 0; l4 < 0x10; l4++)
    {
        if (!unk_10[l4].sub_D4910())
        {
            unk_10[l4].sub_D48D0(arg_0);
            return;
        }
    }
}

// match: ?sub_17DA20@type_17DB90@@QAEXPAUtype_3D3548@@@Z @ 0x0017DA20
// sp-match: ?sub_17DA20@type_17DB90@@QAEXPAUtype_3D3548@@@Z @ 0x00116320
void type_17DB90::sub_17DA20(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 0x10; var_4++)
    {
        if (unk_10[var_4].sub_D4910() == arg_0)
        {
            if (unk_B8)
                unk_B8(this, arg_0);
            unk_10[var_4].sub_D48D0(0);
        }
    }
}

// match: ?sub_17DA90@type_17DB90@@QAEXHHH@Z @ 0x0017DA90
// sp-match: ?sub_17DA90@type_17DB90@@QAEXHHH@Z @ 0x00116370
// Its kind arg_0 (0 to 3) and the effect's arguments; its effect by kind.
void type_17DB90::sub_17DA90(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    unk_BC = arg_0;
    unk_C0 = arg_4;
    unk_C4 = arg_8;
    if (unk_BC > 3)
        unk_BC = 3;
    else if (unk_BC < 0)
        unk_BC = 0;
    unk_B4 = dword_42A4B4[unk_BC];
}

// match: ?sub_17DB10@type_17DB90@@QAEXP6AXPAU1@HH@ZHH@Z @ 0x0017DB10
// sp-match: ?sub_17DB10@type_17DB90@@QAEXP6AXPAU1@HH@ZHH@Z @ 0x001163D0
void type_17DB90::sub_17DB10(void (*arg_0)(type_17DB90 *, RwInt32, RwInt32), RwInt32 arg_4, RwInt32 arg_8)
{
    unk_C0 = arg_4;
    unk_C4 = arg_8;
    unk_B4 = arg_0;
}

// match: ?sub_17DB50@type_17DB90@@QAEXHHH@Z @ 0x0017DB50
// sp-match: ?sub_17DB50@type_17DB90@@QAEXHHH@Z @ 0x00116400
// Its exit effect by the kind arg_0 (0 to 3).
void type_17DB90::sub_17DB50(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    if (arg_0 > 3)
        arg_0 = 3;
    else if (arg_0 < 0)
        arg_0 = 0;
    unk_B8 = dword_42A4C4[arg_0];
}

// match: ?sub_17DB90@type_17DB90@@QAEXH@Z @ 0x0017DB90
// sp-match: ?sub_17DB90@type_17DB90@@QAEXH@Z @ 0x00116440
void type_17DB90::sub_17DB90(RwInt32 arg_0)
{
    if (unk_CC)
        sub_F3300((type_F2FF0 *)unk_CC);
    unk_CC = arg_0;
}

// match: ?sub_17DBD0@@YAXPAUtype_17DB90@@HH@Z @ 0x0017DBD0
// sp-match: ?sub_17DBD0@@YAXPAUtype_17DB90@@HH@Z @ 0x00116480
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Kind 0's effect: arg_4 damage to each entity in it, as a blow from the
// zone; the local player first lets its hit filter see it and, when it
// passes, the multiplayer manager is sent the damage.
void sub_17DBD0(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_17DBD0_player *var_3C;
    type_75600 var_38;
    type_3D3548 *var_8;
    RwInt32 l4;

    memset(&var_38, 0, 0x30);
    var_38.unk_02_w = 2;
    var_38.unk_28 = (RwReal)arg_4;
    var_38.unk_2C = (RwReal)arg_4;
    var_38.unk_1C = (RwInt32)&arg_0->unk_70;
    var_38.unk_14 = (RwInt32)&arg_0->unk_70.pos;
    for (l4 = 0; l4 < 0x10; l4++)
    {
        var_8 = arg_0->unk_10[l4].sub_D4910();
        if (var_8 && !var_8->unk_28_9 && !var_8->unk_28_0)
        {
#ifndef CODFH_SP // single player has no local player check or multiplayer message (SP 0x1164CB)
            if (var_8 == sub_1745A0(0))
            {
                var_3C = (type_17DBD0_player *)var_8;
                if (var_3C->pvf_03C(&var_38))
                {
                    type_3DA434 var_4C;

                    var_4C.sub_1C5A80(var_38.unk_28);
                    var_4C.unk_08 = (RwUInt8)var_38.unk_24;
                    var_4C.unk_04 = 0;
                    sub_1ACBA0(unk_4F7EB8.sub_1AEC70(), &var_4C);
                }
            }
#endif
            var_8->vf_064(&var_38);
        }
    }
}

// match: ?sub_17DD00@@YAXPAUtype_17DB90@@HH@Z @ 0x0017DD00
// sp-match: ?sub_17DD00@@YAXPAUtype_17DB90@@HH@Z @ 0x00116500
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Kind 1's effect: once something is in it, it charges for three seconds
// (its next effect the explosion, sub_17DE90), with the charge's sound, near
// or far by the local player's distance.
void sub_17DD00(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
#ifndef CODFH_SP
    RwV3d local_28;
#endif
    RwReal var_1C;
    RwInt32 var_18;
    RwInt32 var_14;
    RwInt32 lv_10;
    type_3D3548 *var_C;
    type_3D3548 *bp_8;
    RwInt32 bp_4;

    lv_10 = 1;
    for (var_18 = 0; var_18 < 0x10; var_18++)
    {
        var_C = arg_0->unk_10[var_18].sub_D4910();
        if (var_C)
        {
            lv_10 = 0;
            break;
        }
    }
    if (lv_10)
        return;
    var_14 = arg_0->unk_C0;
    bp_4 = arg_0->unk_C4;
    arg_0->unk_58 = seconds_to_frames(3.0f);
    arg_0->sub_17DB10(sub_17DE90, var_14, bp_4);
    bp_8 = sub_1745A0(0);
    if (bp_8)
    {
        type_3DF8D8_04 var_30;
#ifdef CODFH_SP
        // shape: the difference is a block local, so /O2 schedules each
        // vtable load before the component's store (SP 0x116585).
        RwV3d local_28;
#endif

        RwV3dSubMacro(&local_28, &arg_0->unk_70.pos, (RwV3d *)bp_8->vf_0C4());
        var_1C = RwV3dLength((RwV3d *)&local_28);
        if (var_1C < 10000.0f)
        {
            var_30.unk_00 = 0x72A6FBE6; // not an address: a sound's key
            var_30.unk_04 = 0xBCF6B65A; // not an address: a sound's key
        }
        else
        {
            var_30.unk_00 = 0x72A6FBE6; // not an address: a sound's key
            var_30.unk_04 = 0xBCF6B659; // not an address: a sound's key
        }
        dword_4B1E98.sub_8A980(&var_30, 0, 0, &arg_0->unk_70.pos, 0, 0);
    }
}

// match: ?sub_17DE90@@YAXPAUtype_17DB90@@HH@Z @ 0x0017DE90
// match: __ehhandler$?sub_17DE90@@YAXPAUtype_17DB90@@HH@Z-0xB @ 0x003021E0
// match: __ehhandler$?sub_17DE90@@YAXPAUtype_17DB90@@HH@Z @ 0x003021EB
// sp-match: ?sub_17DE90@@YAXPAUtype_17DB90@@HH@Z @ 0x001167F0
// Kind 1's second effect: the charge (sub_17DD00) goes off. With something
// in it, an explosion's sound, particles and a blast (sub_9A960) on the
// ground under its trigger, and the local player's view shakes by arg_4
// when within arg_8.
void sub_17DE90(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwReal var_18;
    type_3D3548 *var_1C;
    RwInt32 var_20;
    Trigger *var_2C;
    RwV3d var_38;
    type_92430 var_64;
    RwMatrix var_B0;
    RwV3d *var_B4;
    type_10F710 *var_EC;
    RwV3d var_F8;
    RwReal var_FC;

    var_18 = arg_0->get_unk_64()->unk_CC;
    arg_0->unk_58 = var_18;
    arg_0->sub_17DB10(sub_17DD00, arg_4, arg_8);
    var_1C = 0;
    for (var_20 = 0; var_20 < 0x10; var_20++)
    {
        var_1C = arg_0->unk_10[var_20].sub_D4910();
        if (var_1C)
            break;
    }
    if (!var_1C)
        return;
#ifdef CODFH_SP
    // shape: the sound key at function scope, between var_38 and the
    // distance vector (SP 0x116854).
    type_3DF8D8_04 var_28;
#endif
    {
#ifndef CODFH_SP
        type_3DF8D8_04 var_28;
#endif

        var_28.unk_00 = 0xB01B4798; // not an address: a sound's key
        var_28.unk_04 = 0xF75296A0; // not an address: a sound's key
        dword_4B1E98.sub_8A980(&var_28, 0, 0, &arg_0->unk_70.pos, 0, 0);
    }
    var_2C = (Trigger *)arg_0->unk_5C.unk_08;
    var_2C->sub_BDF70(&var_38);
    var_38.y = ((RwV3d *)var_1C->vf_0C4())->y + 500.0f;
    sub_92430(&var_38, &var_64, 100.0f);
    if (var_64.unk_20)
        var_38.y = var_64.unk_08.y;
    RwMatrixSetIdentityMacro(&var_B0);
    var_B4 = &var_B0.up;
    var_B4->x = 0.0f;
    var_B4->y = 1.0f;
    var_B4->z = 0.0f;
    var_B0.pos = var_38;
    sub_F2750(2, 0, &var_B0, 0);
    {
        type_4AE70 var_E8;

        var_E8.unk_00 = 0x804;
        var_E8.unk_08 = 0;
        var_E8.unk_0C = &var_B0;
        var_E8.unk_10 = 1000.0f;
        var_E8.unk_14 = 1000.0f;
        var_E8.unk_18 = 1000.0f;
        var_E8.unk_2C = 200.0f;
        sub_9A960(&var_E8);
        var_EC = (type_10F710 *)sub_1745A0(0);
        if (var_EC)
        {
#ifdef CODFH_SP
            // shape: a block-local difference and the length compared as it
            // returns (SP 0x1169F7 fild after the call, fcompp).
            RwV3d d;
            RwV3dSubMacro(&d, &var_B0.pos, (RwV3d *)var_EC->vf_0C4());
            if (RwV3dLength(&d) < (RwReal)arg_8)
#else
            RwV3dSubMacro(&var_F8, &var_B0.pos, (RwV3d *)var_EC->vf_0C4());
            var_FC = RwV3dLength((RwV3d *)&var_F8);
            if ((RwReal)arg_8 > var_FC)
#endif
                var_EC->sub_1109A0((RwReal)arg_4, 1.0f);
        }
    }
}

// match: ?sub_17E200@@YAXPAUtype_17DB90@@HH@Z @ 0x0017E200
// sp-match: ?sub_17E200@@YAXPAUtype_17DB90@@HH@Z @ 0x00116610
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Kind 2's effect: holds the players in it.
void sub_17E200(type_17DB90 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 var_8;
    type_3D3548 *l4;

    l4 = 0;
    for (var_8 = 0; var_8 < 0x10; var_8++)
    {
        l4 = arg_0->unk_10[var_8].sub_D4910();
        if (l4 && l4->vf_00C())
            ((type_10F710 *)l4)->set_unk_520(true);
    }
}

// match: ?sub_17E260@@YAXPAUtype_17DB90@@PAUtype_3D3548@@@Z @ 0x0017E260
// sp-match: ?sub_17E260@@YAXPAUtype_17DB90@@PAUtype_3D3548@@@Z @ 0x00116650
// Kind 2's exit effect: lets the player arg_4 go.
void sub_17E260(type_17DB90 *arg_0, type_3D3548 *arg_4)
{
    if (!arg_4)
        return;
    if (arg_4->vf_00C())
        ((type_10F710 *)arg_4)->set_unk_520(false);
}











// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_17DB90@@SAXPAX0@Z (folded into 0x19A750)
void type_17DB90::operator delete(void * arg_0, void * arg_4)
{
}
