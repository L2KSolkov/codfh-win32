// The camera's sway (type_4E5E50, unk_4E5E50): three effects from the table
// dword_429EB8 (a shake, a sway and a steady drift), noise on the view's
// angles, and the pad rumble that goes with them.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baframe.h"
#include "rw/bamatrix.h"
#include "rw/rtquat.h"
#include "game/functions.h"
#include "game/data.h"
#include "game/worldmgr.h"
#include "types/animkey.h"
#include "types/type_4E5E50.h"
#include <stdlib.h>
#include "game/gameloop.h"
#include "rw/bavector.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DDB7C
extern const RwReal flt_3DDB7C = 16.666666f;
// 0x00429EB8
type_429EB8 dword_429EB8[12] = {
    { 0, 1, 0.0f, 0.0f, 0.0f, 1.0f, 0, 0.0f, 0.0f },
    { 1, 2, 1.0f, 0.09f, 0.05f, 1.0f, 0, 0.0f, 0.0f },
    { 2, 1, 0.07f, 40.2f, 0.1f, 1.0f, 80, 0.05f, 0.0f },
    { 3, 1, 0.15f, 40.2f, 0.02f, 1.0f, 80, 0.05f, 0.0f },
    { 4, 0, 0.2f, 1.0f, 0.1f, 1.0f, 100, 0.0f, 0.0f },
    { 5, 0, 0.6f, 0.2f, 0.3f, 1.0f, 80, 0.0f, 0.0f },
    { 6, 0, 0.6f, 4.6f, 0.35f, 1.0f, 40, 0.0f, 0.0f },
    { 7, 0, 0.75f, 5.2f, 0.5f, 0.8f, 80, 0.0f, 0.0f },
    { 8, 0, 0.75f, 5.2f, 0.63f, 0.8f, 120, 0.0f, 0.0f },
    { 9, 1, 0.8f, 40.0f, 0.07f, 1.0f, 127, 0.0f, 0.0f },
    { 10, 1, 999.9f, 12.0f, 0.02f, 1.0f, 127, 0.0f, 0.0f },
    { -1, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0.0f, 0.0f },
};
// 0x0042A038
RwReal flt_42A038 = 10.0f;
// 0x0042A03C
RwReal flt_42A03C = 4.0f;
// 0x004E5F00
RwInt32 dword_4E5F00;
// End of its data definitions.


extern type_4E5E50 unk_4E5E50;   // unit_174950 defines it (its initializer is placed there)

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DDB7C@@3MB @ 0x003DDB7C
// match: __ehhandler$??0type_4E5E50@@QAE@XZ>1>8 @ 0x0041E380
// match: __ehhandler$??0type_4E5E50@@QAE@XZ>1 @ 0x0041E390
// match: __ehhandler$??1type_4E5E50@@QAE@XZ>1>8 @ 0x0041E3AC
// match: __ehhandler$??1type_4E5E50@@QAE@XZ>1 @ 0x0041E3B4
// match: ?dword_429EB8@@3PAUtype_429EB8@@A @ 0x00429EB8
// match: ?flt_42A038@@3MA @ 0x0042A038
// match: ?flt_42A03C@@3MA @ 0x0042A03C

// match: ??0type_4E5E50@@QAE@XZ @ 0x00175FC0
// match: __ehhandler$??0type_4E5E50@@QAE@XZ-0x2C @ 0x00302030
// match: __ehhandler$??0type_4E5E50@@QAE@XZ @ 0x0030205C

type_4E5E50::type_4E5E50()
{
    sub_176100();
}

// match: ??0type_176040@@QAE@XZ @ 0x00176040
type_176040::type_176040()
{
    unk_00 = (RwReal)(rand() % 16384);
    unk_04 = 3;
    unk_08 = 1.0f;
    unk_0C = 0;
}

// match: ??1type_4E5E50@@QAE@XZ @ 0x00176090
// match: __ehhandler$??1type_4E5E50@@QAE@XZ-0x16 @ 0x00302070
// match: __ehhandler$??1type_4E5E50@@QAE@XZ @ 0x00302086
type_4E5E50::~type_4E5E50()
{
}

// match: ?sub_176100@type_4E5E50@@QAEXXZ @ 0x00176100
// Stops every effect and clears the table's last-start times.
void type_4E5E50::sub_176100()
{
    RwInt32 var_4;

    unk_10 = 0;
    unk_14 = 0;
    unk_3C = 0;
    unk_40 = 0;
    unk_68 = 0;
    unk_04 = -1;
    var_4 = 0;
    while (dword_429EB8[var_4].unk_00 != -1)
    {
        dword_429EB8[var_4].unk_1C = -9999.9f;
        var_4++;
    }
}

// match: ?sub_176180@type_4E5E50@@QAEXHPAURwV3d@@MM@Z @ 0x00176180
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Starts the effect arg_0 at the point arg_4 (0: at full strength) with
// the size arg_8 (and the time arg_C, 0 for the table's), unless a higher
// one of its kind is running or it ran too recently. A shake fades with
// the distance from the render camera and rumbles the pad.
void type_4E5E50::sub_176180(RwInt32 arg_0, RwV3d *arg_4, RwReal arg_8, RwReal arg_C)
{
    RwReal ebp_34;
    RwInt32 var_30;
    RwReal var_2C;
    RwInt32 lcl_28;
    RwMatrix *frm_24;
    RwCamera *var_20;
    RwReal l1C;
    RwReal m_18;
    RwV3d ebp_14;
    type_429EB8 *bp_8;
    RwReal bp_4;

    bp_8 = sub_176420(arg_0);
    if (bp_8->unk_02 == 0 && bp_8->unk_00 < unk_10)
        return;
    if (bp_8->unk_02 != 0 && bp_8->unk_00 < unk_3C)
        return;
    bp_4 = dword_4B87C8 * flt_3DDB7C / 1000.0f;
    if (bp_4 - bp_8->unk_1C < bp_8->unk_18)
        return;
    bp_8->unk_1C = bp_4;
    sub_176470(arg_0, arg_C);
    if (bp_8->unk_02 == 0)
    {
        if (!arg_4)
        {
            l1C = 200.0f;
        }
        else
        {
            var_20 = (RwCamera *)dword_4E5C74;
            if (!var_20)
                return;
            frm_24 = RwFrameGetMatrix(RwCameraGetFrame(var_20));
            ebp_14.x = frm_24->pos.x - arg_4->x;
            ebp_14.y = frm_24->pos.y - arg_4->y;
            ebp_14.z = frm_24->pos.z - arg_4->z;
            l1C = RwV3dLength((RwV3d *)&ebp_14);
            l1C = l1C * bp_8->unk_10;
            if (l1C < 200.0f)
                l1C = 200.0f;
        }
        if (l1C != 0.0f)
            m_18 = 100.0f / l1C;
        else
            m_18 = 100.0f;
        unk_10 = arg_0;
        unk_18 = arg_8;
        unk_00 = m_18;
        unk_0C = 0;
        if (!dword_4E5F00 && bp_8->unk_14)
        {
            lcl_28 = (RwInt32)((arg_8 * m_18) * ((RwReal)bp_8->unk_14) * (RwDouble)flt_42A038);
            if (lcl_28 > 255)
                lcl_28 = 255;
            var_30 = (RwInt32)(var_2C = flt_42A03C * unk_14);
            var_30 = var_30 < 1 ? 1 : var_30;
            unk_4B9308.sub_EEE20(0, 0, (RwUInt8)lcl_28, (RwInt16)var_30);
        }
    }
    else if (bp_8->unk_02 == 1)
    {
        unk_3C = arg_0;
        unk_44 = arg_8;
        unk_08 = 0;
        if (!dword_4E5F00 && bp_8->unk_14)
            unk_4B9308.sub_EED30(0, 0, (RwInt16)bp_8->unk_14, (RwInt32)(ebp_34 = flt_42A03C * unk_40));
    }
    else
    {
        unk_68 = arg_0;
        unk_6C = arg_8;
        unk_08 = 0;
    }
}

// match: ?sub_176420@type_4E5E50@@QAEPAUtype_429EB8@@H@Z @ 0x00176420
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The table's effect arg_0.
type_429EB8 *type_4E5E50::sub_176420(RwInt32 arg_0)
{
    type_429EB8 *var_8;
    RwInt32 l4;

    l4 = 0;
    while (1)
    {
        var_8 = &dword_429EB8[l4];
        if (var_8->unk_00 == arg_0)
            return var_8;
        l4++;
    }
    return 0;
}

// match: ?sub_176470@type_4E5E50@@QAEPAUtype_429EB8@@HM@Z @ 0x00176470
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Seeds the noise of the effect arg_0's kind with its speed and size, and
// its time left (arg_4, or the table's).
type_429EB8 *type_4E5E50::sub_176470(RwInt32 arg_0, RwReal arg_4)
{
    type_429EB8 *var_10;
    type_176040 *var_C;
    RwInt32 bp_8;
    RwReal *bp_4;

    bp_8 = 0;
    while (1)
    {
        var_10 = &dword_429EB8[bp_8];
        if (var_10->unk_00 == arg_0)
            break;
        bp_8++;
    }
    if (var_10->unk_02 == 0)
    {
        bp_4 = &unk_14;
        var_C = unk_1C;
    }
    else
    {
        bp_4 = &unk_40;
        var_C = unk_48;
    }
    var_C->reset();
    var_C[0].unk_0C = var_10->get_unk_0C();
    var_C[0].unk_08 = var_10->get_unk_08();
    var_C[1].reset();
    var_C[1].unk_08 = var_10->get_unk_08();
    var_C[1].unk_0C = var_10->get_unk_0C();
    if (arg_4 != 0.0f)
        *bp_4 = arg_4;
    else
        *bp_4 = var_10->unk_04;
    return var_10;
}

// match: ?sub_1765E0@type_4E5E50@@QAEPAURwMatrixTag@@PAU2@@Z @ 0x001765E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Turns the matrix arg_0 by the effects' noise (once a frame each is
// advanced, and one whose time is up stopped) and returns it.
RwMatrix *type_4E5E50::sub_1765E0(RwMatrix *arg_0)
{
    RtQuat var_30;
    RwV3d var_20;
    RwReal ebp_14;
    RtQuat lv_10;

    if (dword_4B86F8 & 0x10)
        return arg_0;
    if (!unk_3C && !unk_10 && !unk_68)
        return arg_0;
    static RwReal s_step = deltaTime * flt_3DDB7C / 1000.0f;
    if (unk_04 != dword_4B87D8)
    {
        unk_04 = dword_4B87D8;
        if (unk_3C)
        {
            if (unk_08 != 0.0f)
                unk_44 += s_step * unk_08;
            unk_40 -= s_step;
            if (unk_40 <= 0.0f)
                sub_176A10();
        }
        if (unk_10)
        {
            if (unk_0C != 0.0f)
                unk_18 += s_step * unk_0C;
            unk_14 -= s_step;
            if (unk_14 <= 0.0f)
                sub_176A90();
        }
    }
    var_20.x = var_20.y = var_20.z = 0;
    if (unk_3C)
    {
        ebp_14 = unk_44;
        if (unk_40 < 0.1f)
            ebp_14 = unk_40 / 0.1f * ebp_14;
        sub_176AB0(unk_48, unk_40, ebp_14, 0, &var_20, 0);
    }
    else if (unk_68)
    {
        sub_176AB0(unk_48, 1.0f, unk_6C, 0, &var_20, 0);
    }
    if (unk_10)
    {
        ebp_14 = unk_18;
        if (unk_14 < 0.1f)
            ebp_14 = unk_14 / 0.1f * ebp_14;
        sub_176AB0(unk_1C, unk_14, ebp_14, unk_00, &var_20, 1);
    }
    sub_13FDA0(&var_20, &lv_10);
    RtQuatConvertFromMatrix(&var_30, arg_0);
    sub_13FE90(&var_30, &lv_10, &var_30);
    RtQuatConvertToMatrix(&var_30, &unk_70);
    unk_70.pos = arg_0->pos;
    sub_19B650(&unk_70);
    *arg_0 = unk_70;
    return arg_0;
}

// match: ?sub_176A10@type_4E5E50@@QAEXXZ @ 0x00176A10
// Stops the sway (and its rumble), and goes back to the drift.
void type_4E5E50::sub_176A10()
{
    if (!dword_4E5F00 && (RwReal)dword_429EB8[unk_3C].get_unk_14() > 0.0f)
        unk_4B9308.sub_EED30(0, 0, 0, 1);
    unk_40 = 0;
    sub_176470(0, 0);
    unk_3C = 0;
    sub_176470(unk_68, 0);
}

// match: ?sub_176A90@type_4E5E50@@QAEXXZ @ 0x00176A90
// Stops the shake.
void type_4E5E50::sub_176A90()
{
    unk_14 = 0;
    unk_10 = 0;
}

// match: ?sub_176AB0@type_4E5E50@@QAEXPAUtype_176040@@MMMPAURwV3d@@H@Z @ 0x00176AB0
// Adds the two noises arg_0 by the time arg_4 and size arg_8 (by the scale
// arg_C too, when arg_14 is set) to the angles *arg_10.
void type_4E5E50::sub_176AB0(type_176040 *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwV3d *arg_10,
                             RwInt32 arg_14)
{
    if (arg_14)
    {
        arg_10->x += arg_0[0].sub_176D70() * arg_8 * arg_4 * arg_C;
        arg_10->y += arg_0[1].sub_176D70() * arg_8 * arg_4 * arg_C;
    }
    else
    {
        arg_10->x += arg_0[0].sub_176D70() * arg_8;
        arg_10->y += arg_0[1].sub_176D70() * arg_8;
    }
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1type_176040@@QAE@XZ (folded into 0x1E41C0)
type_176040::~type_176040()
{
}
