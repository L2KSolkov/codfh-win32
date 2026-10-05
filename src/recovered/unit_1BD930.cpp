// The network game's pick-ups (type_4FBB20, dword_4FBB20; game/netmsg.h):
// their slots, spawning, removal, swapping and their network state. Its
// original file name is not in the image, so it is named for its start
// address.

#include <string.h>
#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "game/netmsg.h"
#include "game/functions.h"
#include "types/PickupTrigger.h"
#include "types/type_3D32F8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E2E24
extern const RwReal flt_3E2E24 = 0.01f;

// match: ?flt_3E2E24@@3MB @ 0x003E2E24


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4FBB20 dword_4FBB20;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0CN@HIDNNCPB@Swap?5pickup?5id?3?5?$CFd?6?5?5?5X?3?5?$CFf?5?5?5Y?3@ @ 0x003E2E28
// match: ??_C@_0DJ@CCKPIKLP@Did?5not?5find?5an?5empty?5slot?5for?5a@ @ 0x003E2E58
// match: .CRT$XCU+0 @ 0x004271EC

// match: _$E2 @ 0x0030C290
// match: ??0type_4FBB20@@QAE@XZ @ 0x001BD930

type_4FBB20::type_4FBB20()
{
    sub_1BD950();
}

// match: ?sub_1BD950@type_4FBB20@@QAEXXZ @ 0x001BD950
void type_4FBB20::sub_1BD950()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 0x20; var_4++)
    {
        if (unk_04[var_4])
            sub_1BDD20(var_4);
    }
    unk_00 = 0;
    memset(unk_04, 0, 0x80);
    unk_84 = 0;
    memset(unk_88, 0, 0x80);
    unk_108 = 0;
}

// match: ?sub_1BD9F0@type_4FBB20@@QAEXXZ @ 0x001BD9F0
void type_4FBB20::sub_1BD9F0()
{
    // The locals' names state their slots (docs/toolchain.md).
    type_3D3548 *bp_8;
    RwUInt32 bp_4;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_00)
    {
    }
    unk_108 = 1;
    for (bp_4 = 0; bp_4 < 0x20; bp_4++)
    {
        if (unk_04[bp_4])
            sub_1BDD20(bp_4);
    }
    unk_00 = 0;
    memset(unk_04, 0, 0x80);
    for (bp_4 = 0; bp_4 < unk_84; bp_4++)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_00)
        {
        }
        bp_8 = unk_88[bp_4]->vf_020();
        if (bp_8)
            sub_1BDFC0((type_1AE520 *)bp_8, unk_88[bp_4]);
    }
    unk_108 = 0;
}

// match: ?sub_1BDAD0@type_4FBB20@@QAEHXZ @ 0x001BDAD0
RwInt32 type_4FBB20::sub_1BDAD0()
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 0x20; var_4++)
    {
        if (!unk_04[var_4])
            return var_4;
    }
    return -1;
}

// match: ?sub_1BDB10@type_4FBB20@@QAEXPAUtype_1F8560@@@Z @ 0x001BDB10
void type_4FBB20::sub_1BDB10(type_1F8560 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwUInt32 frm_24;
    RwInt32 t20;
    RwUInt32 l1C;
    type_1AE520 *m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwUInt32 slot_C;
    RwReal *bp_8;
    RwInt32 bp_4;

    ebp_14 = 0;
    t20 = sub_1F84A0(0x20);
    arg_0->sub_1F8860(unk_00, t20);
    bp_4 = sub_1F84A0(0x6E);
    lv_10 = sub_1F84A0(1000000);
    for (slot_C = 0; slot_C < 0x20; slot_C++)
    {
        m_18 = unk_04[slot_C];
        if (m_18)
        {
            arg_0->sub_1F8860(slot_C, t20);
            l1C = m_18->unk_3B0.sub_FB710();
            arg_0->sub_1F8860(l1C, bp_4);
            frm_24 = m_18->unk_3B0.unk_04;
            // A compiled-out check (docs/toolchain.md): the registers after it are
            // one load on.
            if (!unk_00)
            {
            }
            arg_0->sub_1F8860(frm_24, lv_10);
            bp_8 = m_18->vf_0C4();
            arg_0->sub_1F85F0(bp_8[0]);
            arg_0->sub_1F85F0(bp_8[1]);
            arg_0->sub_1F85F0(bp_8[2]);
            ebp_14++;
        }
    }
}

// match: ?sub_1BDC30@type_4FBB20@@QAEXPAUtype_1F8560@@@Z @ 0x001BDC30
void type_4FBB20::sub_1BDC30(type_1F8560 *arg_0)
{
    // The locals' names state their slots (docs/toolchain.md).
    RwUInt32 fp_2C;
    RwInt32 q28;
    RwUInt32 frm_24;
    RwUInt32 t20;
    RwUInt32 l1C;
    RwInt32 m_18;
    RwUInt32 ebp_14;
    type_1F8560_v lv_10;
    RwInt32 bp_4;

    sub_1BD950();
    q28 = sub_1F84A0(0x20);
    frm_24 = arg_0->sub_1F8810(q28);
    bp_4 = sub_1F84A0(0x6E);
    m_18 = sub_1F84A0(1000000);
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_00)
    {
    }
    for (ebp_14 = 0; ebp_14 < frm_24; ebp_14++)
    {
        l1C = arg_0->sub_1F8810(q28);
        t20 = arg_0->sub_1F8810(bp_4);
        fp_2C = arg_0->sub_1F8810(m_18);
        lv_10.unk_00 = arg_0->sub_1F85A0();
        lv_10.unk_04 = arg_0->sub_1F85A0();
        lv_10.unk_08 = arg_0->sub_1F85A0();
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_00)
        {
        }
        sub_1BDD70(l1C, t20, fp_2C, &lv_10);
    }
}

// match: ?sub_1BDD20@type_4FBB20@@QAEXI@Z @ 0x001BDD20
void type_4FBB20::sub_1BDD20(RwUInt32 arg_0)
{
    type_1AE520 *var_4;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_00)
    {
    }
    var_4 = unk_04[arg_0];
    if (var_4)
    {
        unk_04[arg_0] = 0;
        sub_D5A60(var_4, 0);
        // A compiled-out check (docs/toolchain.md): the registers after it are
        // one load on.
        if (!unk_00)
        {
        }
        unk_00--;
    }
}

// match: ?sub_1BDD70@type_4FBB20@@QAEXIIIPAUtype_1F8560_v@@@Z @ 0x001BDD70
void type_4FBB20::sub_1BDD70(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8, type_1F8560_v *arg_C)
{
    RwMatrix var_50;

    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_00)
    {
    }
    if (!unk_04[arg_0])
    {
        RwMatrixSetIdentityMacro(&var_50);
        var_50.pos.x = arg_C->unk_00;
        var_50.pos.y = arg_C->unk_04;
        var_50.pos.z = arg_C->unk_08;
        unk_04[arg_0] = sub_1BD450(arg_4, arg_8, &var_50, 50.0f, 1, 0);
        if (unk_04[arg_0])
        {
            unk_04[arg_0]->sub_1BD680(arg_0);
            unk_00++;
        }
    }
}

// match: ?sub_1BDE70@type_4FBB20@@QAEXIII@Z @ 0x001BDE70
void type_4FBB20::sub_1BDE70(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8)
{
    type_1AE520 *var_8;
    RwV3d *var_C;
    RwMatrix var_50;

    var_8 = unk_04[arg_0];
    if (var_8)
    {
        var_C = var_8->sub_CD550();
        RwMatrixSetIdentityMacro(&var_50);
        var_50.pos.x = var_C->x;
        var_50.pos.y = var_C->y;
        var_50.pos.z = var_C->z;
        unk_04[arg_0] = 0;
        sub_D5A60(var_8, 0);
        unk_04[arg_0] = sub_1BD450(arg_4, arg_8, &var_50, 50.0f, 1, 0);
        if (unk_04[arg_0])
            unk_04[arg_0]->sub_1BD680(arg_0);
        if (0)
            sub_1C8A30("Swap pickup id: %d\n   X: %f   Y: %f   Z: %f\n", arg_0, var_50.pos.x, var_50.pos.y,
                       var_50.pos.z);
    }
}

// match: ?sub_1BDFC0@type_4FBB20@@QAEXPAUtype_1AE520@@PAVPickupTrigger@@@Z @ 0x001BDFC0
void type_4FBB20::sub_1BDFC0(type_1AE520 *arg_0, PickupTrigger *arg_4)
{
    RwUInt32 var_4;

    for (var_4 = 0; var_4 < 0x20; var_4++)
    {
        if (!unk_04[var_4])
        {
            unk_04[var_4] = arg_0;
            arg_0->sub_1BD680(var_4);
            unk_00++;
            if (!unk_108)
            {
                unk_88[var_4] = arg_4;
                unk_84++;
            }
            return;
        }
    }
    if (0)
        sub_1C8A30("Did not find an empty slot for a triggerd pickup on host");
}

// match: ?sub_1BE060@type_4FBB20@@QAEXPAUtype_1AE520@@@Z @ 0x001BE060
void type_4FBB20::sub_1BE060(type_1AE520 *arg_0)
{
    RwUInt32 var_4;

    if (!arg_0)
        return;
    for (var_4 = 0; var_4 < 0x20; var_4++)
    {
        if (unk_04[var_4] == arg_0)
        {
            unk_04[var_4] = 0;
            return;
        }
    }
}
