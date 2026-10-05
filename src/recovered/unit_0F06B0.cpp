// The particle spawners (types/type_4B9E90.h). The original file name is
// not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "game/data.h"
#include "game/vecutil.h"
#include "game/functions.h"
#include "game/clumpdata.h"
#include "types/type_3D3548.h"
#include "types/type_4B9E90.h"

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4B9E90 dword_4B9E90[128];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$??0type_4B9E90@@QAE@XZ>1>8 @ 0x0041CF24
// match: __ehhandler$??0type_4B9E90@@QAE@XZ>1 @ 0x0041CF34
// match: __ehhandler$??1type_4B9E90@@QAE@XZ>1>8 @ 0x0041CF50
// match: __ehhandler$??1type_4B9E90@@QAE@XZ>1 @ 0x0041CF60
// match: .CRT$XCU+0 @ 0x00427058

// match: _$E1 @ 0x0030B560
// match: _$E2 @ 0x0030E4D0
// match: ??0type_4B9E90@@QAE@XZ @ 0x000F06B0
// match: __ehhandler$??0type_4B9E90@@QAE@XZ-0x16 @ 0x00300F50
// match: __ehhandler$??0type_4B9E90@@QAE@XZ @ 0x00300F66

type_4B9E90::type_4B9E90()
{
    sub_F07C0();
}

// match: ??1type_F2880@@QAE@XZ @ 0x000F0740
// (Defined in the struct, in type_F2880.h; out of line for the constructor's
// unwinding.)

// match: ??1type_4B9E90@@QAE@XZ @ 0x000F0760
// match: __ehhandler$??1type_4B9E90@@QAE@XZ-0x16 @ 0x00300F70
// match: __ehhandler$??1type_4B9E90@@QAE@XZ @ 0x00300F86
type_4B9E90::~type_4B9E90()
{
    sub_F07C0();
}

// match: ?sub_F07C0@type_4B9E90@@QAEXXZ @ 0x000F07C0
void type_4B9E90::sub_F07C0()
{
    unk_0C = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1C = 0;
    unk_20 = 0;
    unk_2C = 0;
    unk_3C = 0;
    unk_40 = 0;
    unk_50 = 0xFF;
    unk_28 = 0;
    zero_v3d(&unk_30);
    unk_24.sub_D48D0(0);
    unk_44.sub_F2880(0);
}

// match: ?sub_F0880@type_4B9E90@@QAEXHHMH@Z @ 0x000F0880
void type_4B9E90::sub_F0880(RwInt32 arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    sub_F07C0();
    unk_0C = arg_0;
    unk_18 = arg_8;
    unk_3C = 1;
    unk_40 = arg_C;
    unk_50 = 0xFF;
    unk_28 = 0;
    if (arg_C)
    {
        arg_4 = 0;
    }
    unk_10 = arg_4 == -1 ? 0x7FFFFFFF : arg_4;
}

// match: ?sub_F0900@type_4B9E90@@QAEXXZ @ 0x000F0900
void type_4B9E90::sub_F0900()
{
    if (unk_44.get_unk_08() && get_unk_40())
    {
        sub_F3300(unk_44.get_unk_08());
    }
    unk_20 = 0;
    unk_28 = 0;
}

// match: ?sub_F0960@type_4B9E90@@QAEPAXXZ @ 0x000F0960
void *type_4B9E90::sub_F0960()
{
    void *var_4 = 0;

    switch (unk_20)
    {
    case 1:
        var_4 = unk_24.sub_D4910();
        break;
    case 2:
        var_4 = unk_28;
        break;
    }
    return var_4;
}

// match: ?sub_F09B0@type_4B9E90@@QAEXPAUtype_3D3548@@@Z @ 0x000F09B0
void type_4B9E90::sub_F09B0(type_3D3548 *arg_0)
{
    unk_24.sub_D48D0(0);
    unk_28 = 0;
    switch (unk_20)
    {
    case 1:
        unk_24.sub_D48D0(arg_0);
        break;
    case 2:
        unk_28 = arg_0;
        break;
    }
}

// match: ?sub_F0A10@type_4B9E90@@QAEXPAUtype_3D3548@@HH@Z @ 0x000F0A10
void type_4B9E90::sub_F0A10(type_3D3548 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    if (arg_4 >= 0 && arg_4 <= 99)
    {
        // "PT" and the two digits, as a four-character tag.
        unk_1C = ((arg_4 / 10 + '0') << 8) + arg_4 % 10 + 0x50540030;
    }
    else if (arg_4 != -1)
    {
        unk_1C = arg_4;
    }
    else
    {
        unk_1C = 0;
    }
    unk_20 = arg_8;
    unk_3C = 1;
    sub_F09B0(arg_0);
}

// match: ?sub_F0AA0@type_4B9E90@@QAEXM@Z @ 0x000F0AA0
void type_4B9E90::sub_F0AA0(RwReal arg_0)
{
    if (arg_0 > 1.0f)
    {
        arg_0 = 1.0f;
    }
    if (arg_0 < 0.0f)
    {
        arg_0 = 0.0f;
    }
    unk_50 = (RwUInt8)(255.0f * arg_0);
}

// match: ?sub_F0AF0@type_4B9E90@@QAEXXZ @ 0x000F0AF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4B9E90::sub_F0AF0()
{
    RwV3d frm_24;
    type_4B9E90_28 *m_18;
    type_3D3548 *ebp_14;
    RpClump *lv_10;
    RwInt32 slot_C;
    RwMatrix *bp_8;
    RwFrame *bp_4;

    bp_8 = (RwMatrix *)unk_44.get_unk_08();
    slot_C = 0;
    switch (unk_20)
    {
    case 1:
        ebp_14 = (type_3D3548 *)sub_F0960();
        if (ebp_14 && ebp_14->get_unk_264())
        {
            lv_10 = ebp_14->unk_25C.unk_08;
            if (unk_1C)
            {
                if (unk_1C)
                {
                    slot_C = sub_EC2D0(lv_10, (RwInt32)bp_8, unk_1C, 0, 1);
                }
                if (!slot_C)
                {
                    bp_4 = ebp_14->get_unk_340();
                    if (bp_4)
                    {
                        *bp_8 = *RwFrameGetLTM(bp_4);
                    }
                }
            }
        }
        break;
    case 2:
        m_18 = (type_4B9E90_28 *)sub_F0960();
        if (m_18 && m_18->get_unk_20() > 0.0f)
        {
            frm_24 = m_18->unk_10;
            RwV3dNormalize(&frm_24, &frm_24);
            sub_140CE0(bp_8, &m_18->unk_04, &frm_24);
        }
        break;
    }
}

// match: ?sub_F0C40@type_4B9E90@@QAEXMPAURwV3d@@@Z @ 0x000F0C40
// Counts down to the next emission; then, unless the emission chance
// (unk_50) fails, emits at the target (a kind-1 entity's tag or frame, a
// kind-2 object's position facing its direction, the kind-3 point unk_00),
// or at *arg_4 when given. With a spacing (unk_2C) it fills the way from the
// last emission with emissions that far apart (at most 1000; frees itself on
// a jump over 1000 spacings). Frees itself when the target is gone.
void type_4B9E90::sub_F0C40(RwReal arg_0, RwV3d *arg_4)
{
    RwInt32 var_8;
    RwInt32 var_10;
    type_3D3548 *var_18;
    RpClump *var_1C;
    RwMatrix var_60;
    RwFrame *var_68;
    type_4B9E90_28 *var_6C;
    RwV3d var_7C;
    RwV3d var_88;
    RwV3d var_94;
    RwReal var_98;
    RwV3d var_A4;
    RwV3d var_B0;
    RwInt32 var_B4;

    var_8 = 0;
    if (unk_44.get_unk_08() && unk_40)
    {
        sub_F0AF0();
    }
    unk_14 -= arg_0;
    if (unk_14 > 0.0f)
    {
        return;
    }
    if (unk_10 < 0)
    {
        return;
    }
    if (unk_50 != 0xFF)
    {
        var_10 = RpRandom() % 256;
        if (var_10 < unk_50)
        {
            unk_14 = unk_18;
            return;
        }
    }
    if (!unk_0C)
    {
        sub_F0900();
        return;
    }
    switch (unk_20)
    {
    case 1:
        if (!sub_F0960())
        {
            sub_F0900();
            return;
        }
        var_18 = (type_3D3548 *)sub_F0960();
        if (var_18->unk_28 & 1)
        {
            sub_F0900();
            return;
        }
        var_1C = var_18->unk_25C.unk_08;
        if (var_1C)
        {
            if (unk_1C)
            {
                var_8 = sub_EC2D0(var_1C, (RwInt32)&var_60, unk_1C, 0, 1);
            }
            if (!var_8)
            {
                var_68 = var_18->get_unk_340();
                if (var_68)
                {
                    var_60 = *RwFrameGetLTM(var_68);
                }
                else
                {
                    unk_20 = 0;
                    return;
                }
            }
        }
        else
        {
            unk_20 = 0;
            return;
        }
        break;
    case 2:
        if (!sub_F0960())
        {
            sub_F0900();
            return;
        }
        var_6C = (type_4B9E90_28 *)sub_F0960();
        if (var_6C && var_6C->get_unk_20() > 0.0f)
        {
            var_7C = var_6C->unk_10;
            RwV3dNormalize(&var_7C, &var_7C);
            sub_140CE0(&var_60, &var_6C->unk_04, &var_7C);
        }
        else
        {
            sub_F0900();
            return;
        }
        break;
    case 3:
        var_88.x = 0.0f;
        var_88.y = 1.0f;
        var_88.z = 0.0f;
        sub_140F00(&var_60, &unk_00, &var_88);
        break;
    default:
        sub_F0900();
        return;
    }
    if (arg_4)
    {
        var_60.pos = *arg_4;
    }
    if (unk_2C > 0.0f && !unk_3C)
    {
        RwV3dSubMacro(&var_94, &var_60.pos, &unk_30);
        var_98 = RwV3dLength((RwV3d *)&var_94);
        if (unk_2C * 1000.0f < var_98)
        {
            sub_F0900();
            return;
        }
        if (var_98 > unk_2C)
        {
            var_A4 = var_60.pos;
            var_60.pos = unk_30;
            RwV3dNormalize(&var_94, &var_94);
            RwV3dScaleMacro(&var_B0, &var_94, unk_2C);
            var_B4 = 1000;
            while (var_98 > unk_2C && var_B4)
            {
                var_B4--;
                var_98 -= unk_2C;
                RwV3dAddMacro(&var_60.pos, &var_60.pos, &var_B0);
                sub_F2FF0(unk_0C, &var_60, 0, 1, 0, 0);
            }
            if (!var_B4)
            {
                sub_F0900();
                return;
            }
            var_60.pos = var_A4;
        }
    }
    unk_44.sub_F2880((type_F2FF0 *)sub_F2FF0(unk_0C, &var_60, 0, 1, 0, 0));
    unk_30 = var_60.pos;
    unk_3C = 0;
    unk_10--;
    if (unk_10 <= 0)
    {
        if (!unk_40)
        {
            sub_F09B0(0);
            unk_20 = 0;
            unk_44.sub_F2880(0);
        }
    }
    else
    {
        unk_14 = unk_18;
    }
}

// match: ?sub_F1190@@YAXXZ @ 0x000F1190
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F1190()
{
    RwInt32 bp_8;
    type_4B9E90 *bp_4;

    for (bp_4 = dword_4B9E90, bp_8 = 0; bp_8 < 0x80; bp_8++, bp_4++)
    {
        bp_4->sub_F07C0();
    }
}

// match: ?sub_F11D0@@YAXM@Z @ 0x000F11D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F11D0(RwReal arg_0)
{
    RwReal slot_C;
    type_4B9E90 *bp_8;
    RwInt32 bp_4;

    bp_8 = dword_4B9E90;
    slot_C = arg_0;
    for (bp_4 = 0; bp_4 < 0x80; bp_4++, bp_8++)
    {
        if (bp_8->get_unk_20())
        {
            bp_8->sub_F0C40(slot_C, 0);
        }
    }
}

// match: ?sub_F1230@@YAPAUtype_4B9E90@@XZ @ 0x000F1230
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_4B9E90 *sub_F1230()
{
    RwInt32 bp_8;
    type_4B9E90 *bp_4;

    for (bp_4 = dword_4B9E90, bp_8 = 0; bp_8 < 0x80; bp_8++, bp_4++)
    {
        if (!bp_4->get_unk_20())
        {
            return bp_4;
        }
    }
    bp_4 = dword_4B9E90;
    bp_4->sub_F0C40(deltaTime, 0);
    bp_4->sub_F0900();
    return bp_4;
}

// match: ?sub_F12A0@@YAXPAUtype_3D3548@@PAURwV3d@@@Z @ 0x000F12A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_F12A0(type_3D3548 *arg_0, RwV3d *arg_4)
{
    void *slot_C;
    RwInt32 bp_8;
    type_4B9E90 *bp_4;

    if (!arg_0)
    {
        return;
    }
    for (bp_4 = dword_4B9E90, bp_8 = 0; bp_8 < 0x80; bp_8++, bp_4++)
    {
        slot_C = bp_4->sub_F0960();
        if (slot_C && slot_C == arg_0)
        {
            bp_4->sub_F0C40(deltaTime, arg_4);
            bp_4->sub_F0900();
        }
    }
}
