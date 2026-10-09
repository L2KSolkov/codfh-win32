// The pads' library (game/padlib.h): the controllers' XInput records, their
// bindings read into the pad manager's pads, and their rumble.

#include <string.h>

#include "game/padlib.h"
#include "game/data.h"
#include "game/waitscreen.h"
#ifdef CODFH_SP
#include "game/levels.h"
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E0614
extern const RwReal flt_3E0614 = 16.666666f;
// 0x0042C5D8
#ifdef CODFH_SP // single player's table has 20 entries, without multiplayer's 8, 9 and 18-21 (SP 0x3294C8-0x329607)
type_42C5D8 dword_42C5D8[20] = {
    { 0, 0, 1, -1 },
    { 1, 0, 2, -1 },
    { 2, 0, 4, -1 },
    { 3, 0, 8, -1 },
    { 4, 0, 16, -1 },
    { 5, 0, 32, -1 },
    { 6, 0, 64, -1 },
    { 7, 0, 128, -1 },
    { 8, 1, -1, 0 },
    { 9, 1, -1, 1 },
    { 10, 1, -1, 2 },
    { 11, 1, -1, 3 },
    { 12, 1, -1, 4 },
    { 13, 1, -1, 5 },
    { 14, 1, -1, 6 },
    { 15, 1, -1, 7 },
    { 16, 2, -1, -1 },
    { 17, 3, -1, -1 },
    { 18, 4, -1, -1 },
    { 19, 5, -1, -1 },
};
#else
type_42C5D8 dword_42C5D8[26] = {
    { 0, 0, 1, -1 },
    { 1, 0, 2, -1 },
    { 2, 0, 4, -1 },
    { 3, 0, 8, -1 },
    { 4, 0, 16, -1 },
    { 5, 0, 32, -1 },
    { 6, 0, 64, -1 },
    { 7, 0, 128, -1 },
    { 8, 0, 64, -1 },
    { 9, 0, 128, -1 },
    { 10, 1, -1, 0 },
    { 11, 1, -1, 1 },
    { 12, 1, -1, 2 },
    { 13, 1, -1, 3 },
    { 14, 1, -1, 4 },
    { 15, 1, -1, 5 },
    { 16, 1, -1, 6 },
    { 17, 1, -1, 7 },
    { 18, 1, -1, 7 },
    { 19, 1, -1, 7 },
    { 20, 1, -1, 7 },
    { 21, 1, -1, 7 },
    { 22, 2, -1, -1 },
    { 23, 3, -1, -1 },
    { 24, 4, -1, -1 },
    { 25, 5, -1, -1 },
};
#endif
// 0x0042C778
RwReal flt_42C778 = 0.0001f;
// 0x0042C77C
RwReal flt_42C77C = 0.32f;
// 0x004B9E50
#ifndef CODFH_PLAIN
RwInt32 dword_4B9E50;
#endif
// 0x004B9E5C
#ifndef CODFH_PLAIN
RwInt32 dword_4B9E5C;
#endif
// 0x004F4638
type_4F4638 dword_4F4638[4];
// 0x004F48A8
RwInt32 dword_4F48A8;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E0614@@3MB @ 0x003E0614
// match: __real@bf733333 @ 0x003E0618
// match: __real@46ffff00 @ 0x003E061C
// match: ?dword_42C5D8@@3PAUtype_42C5D8@@A @ 0x0042C5D8
// match: ?flt_42C778@@3MA @ 0x0042C778
// match: ?flt_42C77C@@3MA @ 0x0042C77C

// match: ?sub_19D920@@YAHPAUtype_4F4638@@@Z @ 0x0019D920
// sp-match: ?sub_19D920@@YAHPAUtype_4F4638@@@Z @ 0x0012CF10

// Keeps the last state and reads the new one: whether the controller is in.
RwInt32 sub_19D920(type_4F4638 *arg_0)
{
    arg_0->unk_16 = arg_0->unk_00;
    memset(&arg_0->unk_00, 0, 0x16);
    if (arg_0->unk_48)
    {
        XInputGetState(arg_0->unk_48, &arg_0->unk_00);
        return 1;
    }
    return 0;
}

// match: ?sub_19D990@@YAXXZ @ 0x0019D990
// sp-match: ?sub_19D990@@YAXXZ @ 0x0012D5F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes the controllers taken out and put in (clearing the manager's
// removed flag when the player's comes back).
void sub_19D990()
{
    type_4F4638 *var_10;
    RwInt32 var_C;
    DWORD bp_8;
    DWORD bp_4;

    XGetDeviceChanges(XDEVICE_TYPE_GAMEPAD, &bp_4, &bp_8);
    for (var_C = 0; var_C < 4; var_C++)
    {
        var_10 = &dword_4F4638[var_C];
        if ((1 << var_C) & bp_8)
        {
            XInputClose(var_10->unk_48);
            var_10->unk_48 = 0;
        }
        var_10->unk_4C = 0;
        if ((1 << var_C) & bp_4)
        {
            if (!var_10->unk_48 && unk_4B9308.get_unk_B44() && !unk_4B9308.is_unk_B54_clear()
                && var_C == unk_4B9308.get_unk_B48())
                unk_4B9308.unk_B54 = 0;
            sub_19E180(var_C);
            var_10->unk_4C = 1;
        }
    }
}

// match: ?sub_19DA80@@YAMF@Z @ 0x0019DA80
// sp-match: ?sub_19DA80@@YAMF@Z @ 0x0012CF70
// A stick's horizontal axis from -1 to 1 (0 inside the dead zone, 1 or -1
// past 0.95).
RwReal sub_19DA80(RwInt16 arg_0)
{
    RwReal var_4;

    var_4 = 1.0f - (arg_0 + 32768.0f) / 32767.5f;
    if (-flt_42C77C < var_4 && var_4 < flt_42C77C)
        var_4 = 0;
    if (var_4 > 0.95f)
        var_4 = 1.0f;
    else if (var_4 < -0.95f)
        var_4 = -1.0f;
    return var_4;
}

// match: ?sub_19DB10@@YAMF@Z @ 0x0019DB10
// sp-match: ?sub_19DB10@@YAMF@Z @ 0x0012D000
// The same for a vertical axis.
RwReal sub_19DB10(RwInt16 arg_0)
{
    RwReal var_4;

    var_4 = (arg_0 + 32768.0f) / 32767.5f - 1.0f;
    if (-flt_42C77C < var_4 && var_4 < flt_42C77C)
        var_4 = 0;
    if (var_4 > 0.95f)
        var_4 = 1.0f;
    else if (var_4 < -0.95f)
        var_4 = -1.0f;
    return var_4;
}

// match: ?sub_19DBA0@@YAMPAUtype_4F4638@@HHH@Z @ 0x0019DBA0
// sp-match: ?sub_19DBA0@@YAMPAUtype_4F4638@@HHH@Z @ 0x0012D090
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The input arg_4 on the controller (arg_C: negated): arg_8 0 its value on
// being pressed, 1 while held, 2 its last value on being let go.
RwReal sub_19DBA0(type_4F4638 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RwReal var_10;
    type_42C5D8 *var_C;
    RwReal bp_8;
    RwReal bp_4;

    var_C = &dword_42C5D8[arg_4];
    bp_4 = 0;
    var_10 = 0;
    bp_8 = 0;
    switch (var_C->unk_04)
    {
    case 0:
        if (arg_0->unk_00.Gamepad.wButtons & var_C->unk_08)
            bp_8 = 1.0f;
        else
            bp_8 = 0;
        if (arg_0->unk_16.Gamepad.wButtons & var_C->unk_08)
            var_10 = 1.0f;
        else
            var_10 = 0;
        break;
    case 1:
        bp_8 = arg_0->unk_00.Gamepad.bAnalogButtons[var_C->unk_0C] / 255.0f;
        if (bp_8 < flt_42C778)
            bp_8 = 0;
        var_10 = arg_0->unk_16.Gamepad.bAnalogButtons[var_C->unk_0C] / 255.0f;
        if (var_10 < flt_42C778)
            var_10 = 0;
        break;
    case 2:
        bp_8 = sub_19DA80(arg_0->unk_00.Gamepad.sThumbLX);
        var_10 = sub_19DA80(arg_0->unk_16.Gamepad.sThumbLX);
        break;
    case 3:
        bp_8 = sub_19DB10(arg_0->unk_00.Gamepad.sThumbLY);
        var_10 = sub_19DB10(arg_0->unk_16.Gamepad.sThumbLY);
        break;
    case 4:
        bp_8 = sub_19DA80(arg_0->unk_00.Gamepad.sThumbRX);
        var_10 = sub_19DA80(arg_0->unk_16.Gamepad.sThumbRX);
        break;
    case 5:
        bp_8 = sub_19DB10(arg_0->unk_00.Gamepad.sThumbRY);
        var_10 = sub_19DB10(arg_0->unk_16.Gamepad.sThumbRY);
    }
    if (arg_C)
    {
        bp_8 = -bp_8;
        var_10 = -var_10;
    }
    switch (arg_8)
    {
    case 0:
        if (var_10 == 0.0f && bp_8 != 0.0f)
            bp_4 = bp_8;
        else
            bp_4 = 0;
        break;
    case 1:
        if (var_10 != 0.0f && bp_8 != 0.0f)
            bp_4 = bp_8;
        else
            bp_4 = 0;
        break;
    case 2:
        if (var_10 != 0.0f && bp_8 == 0.0f)
            bp_4 = var_10;
        else
            bp_4 = 0;
        break;
    }
    return bp_4;
}

// match: ?sub_19DE30@@YAXPAUtype_4F4638@@PAUtype_4B9308_pad@@@Z @ 0x0019DE30
// sp-match: ?sub_19DE30@@YAXPAUtype_4F4638@@PAUtype_4B9308_pad@@@Z @ 0x0012D2A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads the controller's bindings into the pad's buttons: each one's value
// and whether it is held.
void sub_19DE30(type_4F4638 *arg_0, type_4B9308_pad *arg_4)
{
    RwInt32 var_14;
    type_42B740 *lv_10;
    RwReal var_C;
    RwInt32 bp_8;
    RwReal bp_4;

    lv_10 = arg_0->unk_50;
    if (!lv_10)
        return;
    bp_4 = 0;
    bp_8 = -1;
    while (lv_10->unk_00 != -1)
    {
        for (var_14 = 0; var_14 < lv_10->unk_04; var_14++)
        {
            bp_8 = lv_10->unk_08[var_14];
            if (bp_8 != -1)
            {
                bp_4 = sub_19DBA0(arg_0, lv_10->unk_00, dword_429498[bp_8].unk_04, lv_10->unk_1C);
                arg_4->unk_00[bp_8].unk_04 = bp_4;
                arg_4->unk_00[bp_8].unk_0C = (var_C = sub_19DBA0(arg_0, lv_10->unk_00, 2, lv_10->unk_1C)) > 0.0f ? 1 : 0;
            }
        }
        lv_10++;
    }
}

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sets the library up: the bindings' tables, and each controller that is in.
// match: ?sub_19DF40@@YAXXZ @ 0x0019DF40
// sp-match: ?sub_19DF40@@YAXXZ @ 0x0012D690
void sub_19DF40()
{
    RwUInt32 var_C;
    DWORD bp_8;
    RwInt32 bp_4;

    dword_4F48A8 = 1;
    sub_19B0F0();
    bp_8 = 0;
    bp_4 = 0;
    Sleep(100);
    bp_8 = XGetDevices(XDEVICE_TYPE_GAMEPAD);
    if (dword_4F48A8)
    {
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on. Its operands are all in memory, so it tests a
        // computed value to take a register.
        if (!(bp_8 & 1))
        {
        }
        for (var_C = 0; var_C < 4; var_C++)
        {
            memset(&dword_4F4638[var_C], 0, 0x9C);
            if ((1 << var_C) & bp_8)
                sub_19E180(var_C);
        }
    }
}

// match: ?sub_19DFE0@@YAHPAUtype_4B9308@@M@Z @ 0x0019DFE0
// sp-match: ?sub_19DFE0@@YAHPAUtype_4B9308@@M@Z @ 0x0012D750
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads every controller into the manager's pads, then rumbles them: 0
// while the one pad that counts is out (flagging it) or none is in.
RwInt32 sub_19DFE0(type_4B9308 *arg_0, RwReal arg_4)
{
    RwInt32 var_8;
    RwInt32 l4;

    if (!dword_4F48A8)
    {
        sub_19DF40();
        return 0;
    }
    sub_19D990();
    for (l4 = 0; l4 < 4; l4++)
    {
        sub_19D920(&dword_4F4638[l4]);
        sub_19DE30(&dword_4F4638[l4], &arg_0->unk_00[l4]);
    }
    if (unk_4B9308.get_unk_B44())
    {
        if (unk_4B9308.has_unk_B48())
        {
            var_8 = unk_4B9308.unk_B48;
            if (!dword_4F4638[var_8].unk_48)
            {
                unk_4B9308.unk_B54 = 1;
                return 0;
            }
        }
        else if (!sub_19E3E0())
            return 0;
    }
    sub_19E0D0(arg_0, arg_4);
    return 1;
}

// match: ?sub_19E0D0@@YAXPAUtype_4B9308@@M@Z @ 0x0019E0D0
// sp-match: ?sub_19E0D0@@YAXPAUtype_4B9308@@M@Z @ 0x0012D710
void sub_19E0D0(type_4B9308 *arg_0, RwReal arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
        sub_19E250(&dword_4F4638[var_4], &arg_0->unk_00[var_4], arg_4);
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_12D360@@YAHPAUtype_42B740@@HH@Z @ 0x0012D360
// Adds the button arg_4 to the binding arg_0 (up to five; arg_8: it becomes
// the only one); whether it is there (single player's binding changes,
// SP 0xB6C9A, 0x81D9D).
RwInt32 sp_sub_12D360(type_42B740 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 var_8;
    RwInt32 l4;

    if (arg_8)
    {
        arg_0->unk_04 = 1;
        arg_0->unk_08[0] = arg_4;
    }
    else
    {
        l4 = arg_0->unk_04;
        if (l4 >= 5)
            return 0;
        for (var_8 = 0; var_8 < arg_0->unk_04; var_8++)
        {
            if (arg_0->unk_08[var_8] == arg_4)
                return 1;
        }
        arg_0->unk_08[l4] = arg_4;
        arg_0->unk_04++;
    }
    return 1;
}
#endif

// match: ?sub_19E120@@YAXXZ @ 0x0019E120
void sub_19E120()
{
    RwUInt32 var_4;

    if (!dword_4F48A8)
        return;
    for (var_4 = 0; var_4 < 4; var_4++)
    {
        if (dword_4F4638[var_4].unk_48)
            XInputClose(dword_4F4638[var_4].unk_48);
    }
}

// match: ?sub_19E180@@YAXH@Z @ 0x0019E180
// sp-match: ?sub_19E180@@YAXH@Z @ 0x0012D3C0
// Opens controller arg_0, with the control set's bindings.
void sub_19E180(RwInt32 arg_0)
{
    dword_4F4638[arg_0].unk_48 = XInputOpen(XDEVICE_TYPE_GAMEPAD, arg_0, 0, 0);
    XInputGetCapabilities(dword_4F4638[arg_0].unk_48, &dword_4F4638[arg_0].unk_2C);
    dword_4F4638[arg_0].unk_50 = sub_19B1E0(dword_4F28F0->get_unk_1C());
}

// match: ?sub_19E200@@YAHHHPAUtype_4B9308@@@Z @ 0x0019E200
// sp-match: ?sub_19E200@@YAHHHPAUtype_4B9308@@@Z @ 0x0012D410
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The first action bound to the input arg_0 on controller arg_4, or -1.
RwInt32 sub_19E200(RwInt32 arg_0, RwInt32 arg_4, type_4B9308 *arg_8)
{
    type_42B740 *var_8;
    type_4F4638 *l4;

    l4 = &dword_4F4638[arg_4];
    var_8 = l4->unk_50;
    while (var_8->unk_00 != -1)
    {
        if (var_8->unk_00 == arg_0)
            return var_8->unk_08[0];
        var_8++;
    }
    return -1;
}

// match: ?sub_19E250@@YAXPAUtype_4F4638@@PAUtype_4B9308_pad@@M@Z @ 0x0019E250
// sp-match: ?sub_19E250@@YAXPAUtype_4F4638@@PAUtype_4B9308_pad@@M@Z @ 0x0012D450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Rumbles the controller as the pad asks (its strength scaled up, the
// right motor full or off), or runs the rumble's time down by half of
// arg_8 and stops it.
void sub_19E250(type_4F4638 *arg_0, type_4B9308_pad *arg_4, RwReal arg_8)
{
    RwInt32 var_C;
    RwInt32 bp_8;
    type_EEF90 *bp_4;

    if (!arg_0->unk_48)
        return;
    bp_4 = &arg_4->unk_2C0;
    if (bp_4->unk_0C)
    {
        if (arg_0->unk_54.Header.dwStatus != ERROR_IO_PENDING)
        {
            bp_4->unk_0C = 0;
            var_C = bp_4->unk_04 << 9;
            var_C = var_C > 0xFFFF ? 0xFFFF : var_C;
            var_C = var_C > 0 ? var_C : 0;
            if (!bp_4->unk_00)
                bp_8 = 0;
            else
                bp_8 = 0xFFFF;
            arg_0->unk_54.Rumble.wLeftMotorSpeed = var_C;
            arg_0->unk_54.Rumble.wRightMotorSpeed = bp_8;
            if (arg_0->unk_48)
                XInputSetState(arg_0->unk_48, &arg_0->unk_54);
        }
    }
    else if (bp_4->unk_08 != 0.0f)
    {
        bp_4->unk_08 = bp_4->unk_08 - arg_8 * 0.5f;
        if (bp_4->unk_08 <= 0.0f)
        {
            if (arg_0->unk_54.Header.dwStatus != ERROR_IO_PENDING)
            {
                arg_0->unk_54.Rumble.wLeftMotorSpeed = 0;
                arg_0->unk_54.Rumble.wRightMotorSpeed = 0;
                if (arg_0->unk_48)
                    XInputSetState(arg_0->unk_48, &arg_0->unk_54);
                bp_4->unk_08 = 0;
                bp_4->unk_00 = 0;
                bp_4->unk_04 = 0;
            }
            else
                bp_4->unk_08 = 0.001f;
        }
    }
}

// match: ?sub_19E3E0@@YAHXZ @ 0x0019E3E0
// sp-match: ?sub_19E3E0@@YAHXZ @ 0x0012D560
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// How many controllers are in.
RwInt32 sub_19E3E0()
{
    RwInt32 var_8;
    RwInt32 l4;

    l4 = 0;
    for (var_8 = 0; var_8 < 4; var_8++)
    {
        if (dword_4F4638[var_8].unk_48)
            l4++;
    }
    return l4;
}

// match: ?sub_19E430@@YAHHHPAUtype_4B9308@@@Z @ 0x0019E430
// sp-match: ?sub_19E430@@YAHHHPAUtype_4B9308@@@Z @ 0x0012D5A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The input the action arg_0 is bound to on controller arg_4 (the first
// control set without bindings), or -1.
RwInt32 sub_19E430(RwInt32 arg_0, RwInt32 arg_4, type_4B9308 *arg_8)
{
    RwInt32 var_C;
    type_42B740 *bp_8;
    type_4F4638 *bp_4;

    bp_4 = &dword_4F4638[arg_4];
    bp_8 = bp_4->unk_50;
    if (!bp_8)
        bp_8 = dword_42B740;
    while (bp_8->unk_00 != -1)
    {
        for (var_C = 0; var_C < 5; var_C++)
        {
            if (bp_8->unk_08[var_C] == arg_0)
                return bp_8->unk_00;
        }
        bp_8++;
    }
    return -1;
}

// match: ?sub_19E4B0@@YAPAUtype_4F4638@@XZ @ 0x0019E4B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The controller that counts (the first without one), if it is in.
type_4F4638 *sub_19E4B0()
{
    RwInt32 var_8;
    type_4F4638 *l4;

    var_8 = 0;
    if (unk_4B9308.has_unk_B48())
        var_8 = unk_4B9308.unk_B48;
    l4 = &dword_4F4638[var_8];
    if (l4->unk_48)
        return l4;
    return 0;
}
