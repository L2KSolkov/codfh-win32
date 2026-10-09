// The objectives (game/objectives.h).

#include "rw/ostypes.h"
#include "game/objectives.h"
#include "types/type_3D3548.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/alfamessman.h"
#include "types/LevelScriptTrigger.h"
#include "types/asynchload.h"
#include <string.h>
#include <math.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DD4C4
extern const RwReal flt_3DD4C4 = 16.666666f;
// 0x004E5648
RwInt32 dword_4E5648;
// 0x004E564C
RwInt8 byte_4E564C;
// 0x004E564D
RwInt8 byte_4E564D;
// 0x004E5650
RwInt32 dword_4E5650;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DD4C4@@3MB @ 0x003DD4C4
// match: ??_C@_0FJ@IEBLFOCA@WARNING?3?5ObjectiveManager?5initia@ @ 0x003DD4C8
// match: __real@40100000 @ 0x003DD524
// match: __real@3ff4000000000000 @ 0x003DD528
// match: __ehhandler$?_Insert_n@?$vector@HV?$allocator@H@std@@@std@@IAEXViterator@12@IABH@Z>1>8 @ 0x0041E280
// match: __ehhandler$?_Insert_n@?$vector@HV?$allocator@H@std@@@std@@IAEXViterator@12@IABH@Z>1>16>16 @ 0x0041E2A0
// match: __ehhandler$?_Insert_n@?$vector@HV?$allocator@H@std@@@std@@IAEXViterator@12@IABH@Z>1>16>36 @ 0x0041E2B0
// match: __ehhandler$?_Insert_n@?$vector@HV?$allocator@H@std@@@std@@IAEXViterator@12@IABH@Z>1>16 @ 0x0041E2C0
// match: __ehhandler$?_Insert_n@?$vector@HV?$allocator@H@std@@@std@@IAEXViterator@12@IABH@Z>1 @ 0x0041E2E8
// match: .CRT$XCU+0 @ 0x0042713C
// match: .CRT$XCU+4 @ 0x00427140
// match: .CRT$XCU+8 @ 0x00427144

// match: _$E2 @ 0x0030BD50
// match: _$E3 @ 0x0030E8A0
// match: _$E5 @ 0x0030BD80
// match: _$E6 @ 0x0030E8C0
// match: _$E8 @ 0x0030BDB0
// match: _$E9 @ 0x0030E8E0
// sp-match: _$E9 @ 0x0021EC70
// sp-match: _$E5 @ 0x0021DCB0
// sp-match: _$E8 @ 0x0021DCE0
// sp-match: _$E3 @ 0x0021EC90
// sp-match: _$E6 @ 0x0021ECA0

type_144940 dword_4E5690;
type_4E56A0 dword_4E56A0[15];
// Initialized after the two above (its .CRT$XCU entry is their third).
type_D48D0 dword_4E5654[15];

// match: ?sub_16FF90@@YAXXZ @ 0x0016FF90
// sp-match: ?sub_16FF90@@YAXXZ @ 0x0010DE00
void sub_16FF90()
{
    sub_16FFF0();
    dword_4E5650 = 0;
}

// match: ?sub_16FFB0@@YAXPAVTrigger@@@Z @ 0x0016FFB0
// sp-match: ?sub_16FFB0@@YAXPAVTrigger@@@Z @ 0x0010DE10
void sub_16FFB0(Trigger *arg_0)
{
#ifndef CODFH_SP
    if (dword_4E5650)
        sub_19A750("WARNING: ObjectiveManager initialized twice! There might be 2 level scripts in the level");
#endif
    sub_16FFF0();
    dword_4E5650 = 1;
    dword_4E5690.sub_144940(arg_0);
}

// match: ?sub_16FFF0@@YAXXZ @ 0x0016FFF0
// sp-match: ?sub_16FFF0@@YAXXZ @ 0x0010CA70
// Clears every record and marker, and turns the target system on.
void sub_16FFF0()
{
    RwInt32 var_4;

    dword_4E5690.sub_144940(0);
    byte_4E564D = -1;
    byte_4E564C = -1;
    dword_4E5648 = 1;
    for (var_4 = 0; var_4 < 15; var_4++)
    {
        dword_4E56A0[var_4].unk_00 = 0;
        dword_4E56A0[var_4].unk_04 = 0;
        dword_4E56A0[var_4].unk_08 = 0;
        dword_4E56A0[var_4].unk_0C = 0;
        dword_4E56A0[var_4].unk_10 = 0;
        dword_4E56A0[var_4].unk_14 = 0;
        dword_4E56A0[var_4].unk_18 = 0;
        dword_4E56A0[var_4].unk_1C = 0;
        dword_4E56A0[var_4].unk_20 = 0;
        dword_4E56A0[var_4].unk_24 = 0;
        dword_4E56A0[var_4].unk_28 = 0;
        dword_4E56A0[var_4].unk_2C.sub_144940(0);
        dword_4E56A0[var_4].unk_38.sub_D48D0(0);
        dword_4E56A0[var_4].unk_3C = 0;
        dword_4E56A0[var_4].unk_40 = -1;
        dword_4E56A0[var_4].unk_44 = 0;
        dword_4E56A0[var_4].unk_48 = -1.0f;
        dword_4E56A0[var_4].unk_4C = -1.0f;
        dword_4E56A0[var_4].unk_50 = 0;
        dword_4E56A0[var_4].unk_54 = 0;
    }
    for (var_4 = 0; var_4 < 15; var_4++)
        dword_4E5654[var_4].sub_D48D0(0);
}

// match: ?sub_1701B0@@YAXXZ @ 0x001701B0
// sp-match: ?sub_1701B0@@YAXXZ @ 0x0010CB20
// Frees every record's messages, then clears them all.
void sub_1701B0()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if (dword_4E56A0[var_4].unk_18)
        {
            sub_6BC40(dword_4E56A0[var_4].unk_18);
            dword_4E56A0[var_4].unk_18 = 0;
        }
        if (dword_4E56A0[var_4].unk_1C)
        {
            sub_6BC40(dword_4E56A0[var_4].unk_1C);
            dword_4E56A0[var_4].unk_1C = 0;
        }
        if (dword_4E56A0[var_4].unk_20)
        {
            sub_6BC40(dword_4E56A0[var_4].unk_20);
            dword_4E56A0[var_4].unk_20 = 0;
        }
        if (dword_4E56A0[var_4].unk_24)
        {
            sub_6BC40(dword_4E56A0[var_4].unk_24);
            dword_4E56A0[var_4].unk_24 = 0;
        }
        if (dword_4E56A0[var_4].unk_28)
        {
            sub_6BC40(dword_4E56A0[var_4].unk_28);
            dword_4E56A0[var_4].unk_28 = 0;
        }
    }
    sub_16FFF0();
}

// match: ?sub_1702F0@@YAXXZ @ 0x001702F0
// sp-match: ?sub_1702F0@@YAXXZ @ 0x0010CBA0
void sub_1702F0()
{
    dword_4E5650 = 0;
    sub_1701B0();
}

// match: ?sub_170310@@YAXM@Z @ 0x00170310
// sp-match: ?sub_170310@@YAXM@Z @ 0x0010CBB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Runs the records' pulses down by arg_0 frames (in seconds), each
// restarting from 10 when it runs out.
void sub_170310(RwReal arg_0)
{
    RwInt32 var_8;
    RwReal l4;

    l4 = arg_0 / 60.0f;
#ifdef CODFH_SP
    // Single player's pulses just run out, and an active objective that is
    // neither done nor failed repeats its text when its nag timer runs out
    // (SP 0x10CBB0).
    RwChar buf[0x80];
    const RwChar *text;

    for (var_8 = 0; var_8 < 15; var_8++)
    {
        if (dword_4E56A0[var_8].unk_44 > 0.0f)
            dword_4E56A0[var_8].unk_44 = dword_4E56A0[var_8].unk_44 - l4;
        if (dword_4E56A0[var_8].unk_0C > 0.0f && (dword_4E56A0[var_8].unk_04 & 2)
            && !(dword_4E56A0[var_8].unk_04 & 0xC))
        {
            dword_4E56A0[var_8].unk_10 = dword_4E56A0[var_8].unk_10 - l4;
            if (dword_4E56A0[var_8].unk_10 <= 0.0f)
            {
                text = dword_4E56A0[var_8].unk_00->sub_197550(buf, dword_4E56A0[var_8].unk_08);
                if (text && !(dword_4E56A0[var_8].unk_04 & 0x80))
                    sub_EACA0(text, 0, 1);
                dword_4E56A0[var_8].unk_10 = dword_4E56A0[var_8].unk_0C;
            }
        }
    }
#else
    for (var_8 = 0; var_8 < 15; var_8++)
    {
        if (dword_4E56A0[var_8].unk_44 > 0.0f)
        {
            dword_4E56A0[var_8].unk_44 = dword_4E56A0[var_8].unk_44 - l4;
            if (dword_4E56A0[var_8].unk_44 <= 0.0f)
                dword_4E56A0[var_8].unk_44 = dword_4E56A0[var_8].unk_44 + 10.0f;
        }
    }
#endif
}

// match: ?sub_1703B0@@YAXPAUtype_3DF8D8_04@@HH@Z @ 0x001703B0
// sp-match: ?sub_1703B0@@YAXPAUtype_3DF8D8_04@@HH@Z @ 0x0010CC80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Adds the objective whose object has the key arg_0, with the flags arg_4
// and the counter arg_8, at the end of the list (nothing when no object
// has the key). The record taken is the loop's last index, free or not.
void sub_1703B0(type_3DF8D8_04 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_3DF8D8 *var_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    var_C = -1;
    var_10 = sub_198800(arg_0);
    if (!var_10)
        return;
    for (bp_8 = 0; bp_8 < 15; bp_8++)
    {
        if (!(dword_4E56A0[bp_8].unk_04 & 1))
        {
            var_C = bp_8;
            break;
        }
    }
    if (byte_4E564D == -1)
    {
        byte_4E564D = (RwInt8)bp_8;
    }
    else
    {
        bp_4 = byte_4E564D;
        while (dword_4E56A0[bp_4].unk_54 != -1)
            bp_4 = dword_4E56A0[bp_4].unk_54;
        dword_4E56A0[bp_4].unk_54 = (RwInt8)bp_8;
    }
    dword_4E56A0[bp_8].unk_00 = var_10;
    dword_4E56A0[bp_8].unk_04 = arg_4 | 1;
    dword_4E56A0[bp_8].unk_08 = arg_8;
    dword_4E56A0[bp_8].unk_54 = -1;
    if (dword_4E56A0[bp_8].unk_08)
        dword_4E56A0[bp_8].unk_04 |= 0x20;
    dword_4E56A0[bp_8].unk_0C = 60.0f;
    dword_4E56A0[bp_8].unk_10 = dword_4E56A0[bp_8].unk_0C;
}

// match: ?sub_170500@@YAHPAUtype_3DF8D8_04@@@Z @ 0x00170500
// sp-match: ?sub_170500@@YAHPAUtype_3DF8D8_04@@@Z @ 0x0010CD50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Removes the objective of the key arg_0 from the list (its messages
// freed but the first); 0 when there is none.
RwInt32 sub_170500(type_3DF8D8_04 *arg_0)
{
    RwInt32 var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_8 = -1;
    bp_4 = byte_4E564D;
    while (bp_4 != -1)
    {
        if (dword_4E56A0[bp_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[bp_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
        {
            var_C = dword_4E56A0[bp_4].unk_54;
            if (dword_4E56A0[bp_4].unk_1C)
            {
                sub_6BC40(dword_4E56A0[bp_4].unk_1C);
                dword_4E56A0[bp_4].unk_1C = 0;
            }
            if (dword_4E56A0[bp_4].unk_20)
            {
                sub_6BC40(dword_4E56A0[bp_4].unk_20);
                dword_4E56A0[bp_4].unk_20 = 0;
            }
            if (dword_4E56A0[bp_4].unk_24)
            {
                sub_6BC40(dword_4E56A0[bp_4].unk_24);
                dword_4E56A0[bp_4].unk_24 = 0;
            }
            if (dword_4E56A0[bp_4].unk_28)
            {
                sub_6BC40(dword_4E56A0[bp_4].unk_28);
                dword_4E56A0[bp_4].unk_28 = 0;
            }
            memset(&dword_4E56A0[bp_4], 0, sizeof(dword_4E56A0[bp_4]));
            if (bp_8 == -1)
                byte_4E564D = (RwInt8)var_C;
            else
                dword_4E56A0[bp_8].unk_54 = (RwInt8)var_C;
            return 1;
        }
        bp_8 = bp_4;
        bp_4 = dword_4E56A0[bp_4].unk_54;
    }
    return 0;
}

// match: ?sub_1706A0@@YAHPAUtype_3DF8D8_04@@@Z @ 0x001706A0
// sp-match: ?sub_1706A0@@YAHPAUtype_3DF8D8_04@@@Z @ 0x0010CE50
RwInt32 sub_1706A0(type_3DF8D8_04 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            return dword_4E56A0[var_4].unk_04;
    }
    return 0;
}

// match: ?sub_170710@@YAXPAUtype_3DF8D8_04@@H@Z @ 0x00170710
// sp-match: ?sub_170710@@YAXPAUtype_3DF8D8_04@@H@Z @ 0x0010CEA0
#ifdef CODFH_SP
// Single player also shows the objective's text (SP 0x10CEFB): its complete text for
// flag 4 unless it had it, else the objectives text object's name for flags 2/4/8 with
// flag 0x40; neither with flag 0x80.
void sub_170710(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    RwChar var_80[0x80];
    const RwChar *var_t;
    type_3DF8D8 *var_o;
    RwInt32 var_i;

    for (var_i = 0; var_i < 15; var_i++)
    {
        if ((dword_4E56A0[var_i].unk_04 & 1) && dword_4E56A0[var_i].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_i].unk_00->unk_04.unk_04 == arg_0->unk_04)
        {
            if ((arg_4 & 4) && !(dword_4E56A0[var_i].unk_04 & 4)
                && (var_t = dword_4E56A0[var_i].unk_00->sp_sub_1252B0(var_80, dword_4E56A0[var_i].unk_08)) != 0)
            {
                if (!(dword_4E56A0[var_i].unk_04 & 0x80))
                    sub_EACA0(var_t, 0, 1);
            }
            else if ((dword_4E56A0[var_i].unk_04 & 0x40) && (arg_4 & 0xE))
            {
                var_o = sub_198800((type_3DF8D8_04 *)&dword_4B913C);
                if (!(dword_4E56A0[var_i].unk_04 & 0x80))
                    sub_EACA0(var_o->sub_197550(0, 0), 0, 1);
            }
            dword_4E56A0[var_i].unk_04 |= arg_4;
            return;
        }
    }
}
#else
void sub_170710(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
        {
            dword_4E56A0[var_4].unk_04 |= arg_4;
            break;
        }
    }
}
#endif

// match: ?sub_170790@@YAXPAUtype_3DF8D8_04@@H@Z @ 0x00170790
// sp-match: ?sub_170790@@YAXPAUtype_3DF8D8_04@@H@Z @ 0x0010CFB0
void sub_170790(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
        {
            dword_4E56A0[var_4].unk_04 &= ~arg_4;
            break;
        }
    }
}

// match: ?sub_170810@@YAHPAUtype_3DF8D8_04@@@Z @ 0x00170810
// sp-match: ?sub_170810@@YAHPAUtype_3DF8D8_04@@@Z @ 0x0010D010
RwInt32 sub_170810(type_3DF8D8_04 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            return dword_4E56A0[var_4].unk_08;
    }
    return -1;
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_10D060@@YAXPAUtype_3DF8D8_04@@H@Z @ 0x0010D060
// Single player only (SP 0x10D060; "SetObjectiveCounter", SP 0x4EB80): sets the counter
// unk_08 of the objective keyed arg_0 to arg_4 and shows its counter text (or the
// objectives text object's name with flag 0x40), unless flag 0x80; flag 0x20 says
// whether the counter is set.
void sp_sub_10D060(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    RwChar var_80[0x80];
    const RwChar *var_t;
    type_3DF8D8 *var_o;
    RwInt32 var_i;

    for (var_i = 0; var_i < 15; var_i++)
    {
        if ((dword_4E56A0[var_i].unk_04 & 1) && dword_4E56A0[var_i].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_i].unk_00->unk_04.unk_04 == arg_0->unk_04)
        {
            dword_4E56A0[var_i].unk_08 = (RwInt8)arg_4;
            var_t = dword_4E56A0[var_i].unk_00->sp_sub_125370(var_80, dword_4E56A0[var_i].unk_08);
            if (var_t)
            {
                if (!(dword_4E56A0[var_i].unk_04 & 0x80))
                    sub_EACA0(var_t, 0, 1);
            }
            else if (dword_4E56A0[var_i].unk_04 & 0x40)
            {
                var_o = sub_198800((type_3DF8D8_04 *)&dword_4B913C);
                if (!(dword_4E56A0[var_i].unk_04 & 0x80))
                    sub_EACA0(var_o->sub_197550(0, 0), 0, 1);
            }
            if (arg_4)
                dword_4E56A0[var_i].unk_04 |= 0x20;
            else
                dword_4E56A0[var_i].unk_04 &= ~0x20;
            return;
        }
    }
}

// sp-match: ?sp_sub_10D160@@YAXPAUtype_3DF8D8_04@@H@Z @ 0x0010D160
// Single player only (SP 0x10D160; "ModifyObjectiveCounter", SP 0x4EBD0): adds arg_4 to
// the counter of the objective keyed arg_0; above 0 it shows the counter text as
// sp_sub_10D060 does, else the objective completes (flag 4, counter off) with its
// complete text unless it already had.
void sp_sub_10D160(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    RwChar var_80[0x80];
    const RwChar *var_t;
    type_3DF8D8 *var_o;
    RwInt32 var_i;

    for (var_i = 0; var_i < 15; var_i++)
    {
        if ((dword_4E56A0[var_i].unk_04 & 1) && dword_4E56A0[var_i].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_i].unk_00->unk_04.unk_04 == arg_0->unk_04)
        {
            dword_4E56A0[var_i].unk_08 += (RwInt8)arg_4;
            if (dword_4E56A0[var_i].unk_08 <= 0)
            {
                if (!(dword_4E56A0[var_i].unk_04 & 4))
                {
                    var_t = dword_4E56A0[var_i].unk_00->sp_sub_1252B0(var_80, dword_4E56A0[var_i].unk_08);
                    if (var_t && !(dword_4E56A0[var_i].unk_04 & 0x80))
                        sub_EACA0(var_t, 0, 1);
                }
                dword_4E56A0[var_i].unk_04 = (dword_4E56A0[var_i].unk_04 & ~0x20) | 4;
            }
            else
            {
                var_t = dword_4E56A0[var_i].unk_00->sp_sub_125370(var_80, dword_4E56A0[var_i].unk_08);
                if (var_t)
                {
                    if (!(dword_4E56A0[var_i].unk_04 & 0x80))
                        sub_EACA0(var_t, 0, 1);
                }
                else if (dword_4E56A0[var_i].unk_04 & 0x40)
                {
                    var_o = sub_198800((type_3DF8D8_04 *)&dword_4B913C);
                    if (!(dword_4E56A0[var_i].unk_04 & 0x80))
                        sub_EACA0(var_o->sub_197550(0, 0), 0, 1);
                }
            }
            return;
        }
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_10D2B0@@YAXPAUtype_3DF8D8_04@@@Z @ 0x0010D2B0
// Single player only (SP 0x10D2B0; "PrintObjective", SP 0x4EF60, where multiplayer has an
// empty print): shows the text of every objective keyed arg_0, unless flag 0x80.
void sp_sub_10D2B0(type_3DF8D8_04 *arg_0)
{
    RwChar var_80[0x80];
    const RwChar *var_t;
    RwInt32 var_i;

    for (var_i = 0; var_i < 15; var_i++)
    {
        if ((dword_4E56A0[var_i].unk_04 & 1) && dword_4E56A0[var_i].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_i].unk_00->unk_04.unk_04 == arg_0->unk_04)
        {
            var_t = dword_4E56A0[var_i].unk_00->sub_197550(var_80, dword_4E56A0[var_i].unk_08);
            if (var_t && !(dword_4E56A0[var_i].unk_04 & 0x80))
                sub_EACA0(var_t, 0, 1);
        }
    }
}
#endif

// match: ?sub_170890@@YACC@Z @ 0x00170890
// sp-match: ?sub_170890@@YACC@Z @ 0x0010D330
RwInt8 sub_170890(RwInt8 arg_0)
{
    return dword_4E56A0[arg_0].unk_54;
}

// match: ?sub_1708B0@@YAPAUtype_4E56A0@@C@Z @ 0x001708B0
// sp-match: ?sub_1708B0@@YAPAUtype_4E56A0@@C@Z @ 0x0010D340
type_4E56A0 *sub_1708B0(RwInt8 arg_0)
{
    if (dword_4E5650 && arg_0 != -1)
        return &dword_4E56A0[arg_0];
    return 0;
}

// match: ?sub_1708E0@@YAXPAV?$vector@HV?$allocator@H@std@@@std@@@Z @ 0x001708E0
void sub_1708E0(std::vector<RwInt32> *arg_0)
{
    RwInt8 var_1;
    RwInt32 var_8;

    var_1 = byte_4E564D;
    var_8 = 0;
    var_8 = (RwInt32)sub_1708B0(var_1);
    while (var_8)
    {
        arg_0->push_back(var_8);
        var_1 = sub_170890(var_1);
        var_8 = (RwInt32)sub_1708B0(var_1);
    }
}

// match: ?sub_170940@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170940
// sp-match: ?sub_170940@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x0010DE30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sets the objective arg_0's activate message to arg_4 (sub_170DF0 handles
// it); 0 when there is no such objective.
RwInt32 sub_170940(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    Trigger *var_C;
    Trigger *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 15; bp_4++)
    {
        if ((dword_4E56A0[bp_4].unk_04 & 1) && dword_4E56A0[bp_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[bp_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (bp_4 >= 15)
        return 0;
    if (dword_4E56A0[bp_4].unk_18)
    {
        sub_6BC40(dword_4E56A0[bp_4].unk_18);
        dword_4E56A0[bp_4].unk_18 = 0;
    }
#ifdef CODFH_SP // shape: the trigger read twice, no locals (SP 0x10DE30)
    dword_4E56A0[bp_4].unk_18 = sub_6BAE0((RwInt32)dword_4E5690.unk_08, (RwUInt32)sub_170DF0,
                                           (RwInt32)dword_4E5690.unk_08, arg_4, 0, msg_flags(2, 1));
#else
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_18 = sub_6BAE0((RwInt32)var_C, (RwUInt32)sub_170DF0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
#endif
    return 1;
}

#ifdef CODFH_SP
// Single player's message handlers and target pick, defined further on.
RwInt32 sp_sub_10D490(RwInt32 arg_0, type_170DF0 *arg_4);
RwInt32 sp_sub_10D580(RwInt32 arg_0, type_170DF0 *arg_4);
RwInt8 sp_sub_10DBA0();

// sp-match: ?sp_sub_10E2B0@@YAHHPAUtype_170DF0@@@Z @ 0x0010E2B0
// Single player only (SP 0x10E2B0; sub_170A30 registers it where multiplayer has the
// empty sub_170ED0): the complete message's handler: an active objective whose message
// it is completes (flag 4) and ends its registration (the target system moves on, the
// next one pulsing for 10 seconds, when it was the current one); then its complete
// text shows (or the objectives text object's name with flag 0x40) unless flag 0x80
// (0). One not yet active stays registered (1).
RwInt32 sp_sub_10E2B0(RwInt32 arg_0, type_170DF0 *arg_4)
{
    RwChar var_80[0x80];
    const RwChar *var_t;
    type_3DF8D8 *var_o;
    RwInt32 var_i;

    for (var_i = 0; var_i < 15; var_i++)
    {
        if (dword_4E56A0[var_i].unk_1C && dword_4E56A0[var_i].unk_1C->unk_14 == arg_4->unk_00->unk_04)
        {
            if (dword_4E56A0[var_i].unk_04 & 2)
            {
                dword_4E56A0[var_i].unk_04 |= 4;
                dword_4E56A0[var_i].unk_1C = 0;
                if (byte_4E564C == var_i)
                {
                    byte_4E564C = sp_sub_10DBA0();
                    if (byte_4E564C != -1)
                        dword_4E56A0[byte_4E564C].unk_44 = 10.0f;
                }
            }
            else
            {
                return 1;
            }
            break;
        }
    }
    var_t = dword_4E56A0[var_i].unk_00->sp_sub_1252B0(var_80, dword_4E56A0[var_i].unk_08);
    if (var_t)
    {
        if (!(dword_4E56A0[var_i].unk_04 & 0x80))
            sub_EACA0(var_t, 0, 1);
    }
    else if (dword_4E56A0[var_i].unk_04 & 0x40)
    {
        var_o = sub_198800((type_3DF8D8_04 *)&dword_4B913C);
        if (!(dword_4E56A0[var_i].unk_04 & 0x80))
            sub_EACA0(var_o->sub_197550(0, 0), 0, 1);
    }
    return 0;
}
#endif

// match: ?sub_170A30@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170A30
// sp-match: ?sub_170A30@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x0010E3F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise its complete message (sub_170ED0).
RwInt32 sub_170A30(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    Trigger *var_C;
    Trigger *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 15; bp_4++)
    {
        if ((dword_4E56A0[bp_4].unk_04 & 1) && dword_4E56A0[bp_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[bp_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (bp_4 >= 15)
        return 0;
    if (dword_4E56A0[bp_4].unk_1C)
    {
        sub_6BC40(dword_4E56A0[bp_4].unk_1C);
        dword_4E56A0[bp_4].unk_1C = 0;
    }
#ifdef CODFH_SP // single player registers its own handler sp_sub_10E2B0 (SP 0x10E3F0); shape: the trigger read twice
    dword_4E56A0[bp_4].unk_1C = sub_6BAE0((RwInt32)dword_4E5690.unk_08, (RwUInt32)sp_sub_10E2B0,
                                           (RwInt32)dword_4E5690.unk_08, arg_4, 0, msg_flags(2, 1));
#else
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_1C = sub_6BAE0((RwInt32)var_C, (RwUInt32)(RwInt32 (*)(RwInt32))sub_170ED0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
#endif
    return 1;
}

// match: ?sub_170B20@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170B20
// sp-match: ?sub_170B20@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x0010DF50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise its fail message (sub_170EE0), for an active objective (flag 2).
RwInt32 sub_170B20(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    Trigger *var_C;
    Trigger *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 15; bp_4++)
    {
        if ((dword_4E56A0[bp_4].unk_04 & 2) && dword_4E56A0[bp_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[bp_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (bp_4 >= 15)
        return 0;
    if (dword_4E56A0[bp_4].unk_20)
    {
        sub_6BC40(dword_4E56A0[bp_4].unk_20);
        dword_4E56A0[bp_4].unk_20 = 0;
    }
#ifdef CODFH_SP // shape: the trigger read twice, no locals (SP 0x10DF50)
    dword_4E56A0[bp_4].unk_20 = sub_6BAE0((RwInt32)dword_4E5690.unk_08, (RwUInt32)sub_170EE0,
                                           (RwInt32)dword_4E5690.unk_08, arg_4, 0, msg_flags(2, 1));
#else
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_20 = sub_6BAE0((RwInt32)var_C, (RwUInt32)sub_170EE0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
#endif
    return 1;
}

// match: ?sub_170C10@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170C10
// sp-match: ?sub_170C10@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x0010E070
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise its counter-up message (sub_31DB0), for an active objective.
RwInt32 sub_170C10(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    Trigger *var_C;
    Trigger *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 15; bp_4++)
    {
        if ((dword_4E56A0[bp_4].unk_04 & 2) && dword_4E56A0[bp_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[bp_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (bp_4 >= 15)
        return 0;
    if (dword_4E56A0[bp_4].unk_24)
    {
        sub_6BC40(dword_4E56A0[bp_4].unk_24);
        dword_4E56A0[bp_4].unk_24 = 0;
    }
#ifdef CODFH_SP // single player registers its own handler sp_sub_10D490 (SP 0x10E070); shape: the trigger read twice
    dword_4E56A0[bp_4].unk_24 = sub_6BAE0((RwInt32)dword_4E5690.unk_08, (RwUInt32)sp_sub_10D490,
                                           (RwInt32)dword_4E5690.unk_08, arg_4, 0, msg_flags(2, 1));
#else
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_24 = sub_6BAE0((RwInt32)var_C, (RwUInt32)(RwInt32 (*)())sub_31DB0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
#endif
    return 1;
}

// match: ?sub_170D00@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170D00
// sp-match: ?sub_170D00@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x0010E190
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Likewise its counter-down message (sub_31DB0), for an active objective.
RwInt32 sub_170D00(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    Trigger *var_C;
    Trigger *bp_8;
    RwInt32 bp_4;

    for (bp_4 = 0; bp_4 < 15; bp_4++)
    {
        if ((dword_4E56A0[bp_4].unk_04 & 2) && dword_4E56A0[bp_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[bp_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (bp_4 >= 15)
        return 0;
    if (dword_4E56A0[bp_4].unk_28)
    {
        sub_6BC40(dword_4E56A0[bp_4].unk_28);
        dword_4E56A0[bp_4].unk_28 = 0;
    }
#ifdef CODFH_SP // single player registers its own handler sp_sub_10D580 (SP 0x10E190); shape: the trigger read twice
    dword_4E56A0[bp_4].unk_28 = sub_6BAE0((RwInt32)dword_4E5690.unk_08, (RwUInt32)sp_sub_10D580,
                                           (RwInt32)dword_4E5690.unk_08, arg_4, 0, msg_flags(2, 1));
#else
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_28 = sub_6BAE0((RwInt32)var_C, (RwUInt32)(RwInt32 (*)())sub_31DB0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
#endif
    return 1;
}

// match: ?sub_170DF0@@YAHHPAUtype_170DF0@@@Z @ 0x00170DF0
// sp-match: ?sub_170DF0@@YAHHPAUtype_170DF0@@@Z @ 0x0010D360
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The activate message's handler: marks the objective whose message it is
// active (flag 2) and ends its registration; then, when that record (or
// the one past the last) has flag 0x40 and not 0x80, shows the objectives
// text object's name.
RwInt32 sub_170DF0(RwInt32 arg_0, type_170DF0 *arg_4)
{
    type_3DF8D8 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 15; l4++)
    {
        if ((dword_4E56A0[l4].unk_04 & 1) && dword_4E56A0[l4].unk_18
            && dword_4E56A0[l4].unk_18->unk_14 == arg_4->unk_00->unk_04)
        {
            dword_4E56A0[l4].unk_04 |= 2;
            dword_4E56A0[l4].unk_18 = 0;
            break;
        }
    }
    if (dword_4E56A0[l4].unk_04 & 0x40)
    {
        var_8 = sub_198800((type_3DF8D8_04 *)&dword_4B913C);
        if (!(dword_4E56A0[l4].unk_04 & 0x80))
            sub_EACA0(var_8->sub_197550(0, 0), 0, 1);
    }
    return 0;
}

// match: ?sub_170ED0@@YAHH@Z @ 0x00170ED0
// sp-match: ?sub_170ED0@@YAHH@Z @ 0x0006CEB0
// The complete message's handler: nothing (0). /OPT:ICF shares it with
// the image's other empty tests returning 0.
RwInt32 sub_170ED0(RwInt32 arg_0)
{
    return 0;
}

// The heading's call in type_7C8D0::sub_79D50: a float's empty test, defined
// here with the body it shares (PLAN M7).
// ?sub_170ED0@@YAHM@Z (folded into 0x170ED0)
RwInt32 sub_170ED0(RwReal arg_0)
{
    return 0;
}

// match: ?sub_170EE0@@YAHHPAUtype_170DF0@@@Z @ 0x00170EE0
// sp-match: ?sub_170EE0@@YAHHPAUtype_170DF0@@@Z @ 0x0010D3F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The fail message's handler: an active objective whose message it is
// fails (flag 8) and ends its registration; one not yet active stays
// registered (1).
RwInt32 sub_170EE0(RwInt32 arg_0, type_170DF0 *arg_4)
{
    type_3DF8D8 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 15; l4++)
    {
        if (dword_4E56A0[l4].unk_20 && dword_4E56A0[l4].unk_20->unk_14 == arg_4->unk_00->unk_04)
        {
            if (dword_4E56A0[l4].unk_04 & 2)
            {
                dword_4E56A0[l4].unk_04 |= 8;
                dword_4E56A0[l4].unk_20 = 0;
            }
            else
            {
                return 1;
            }
            break;
        }
    }
    if (dword_4E56A0[l4].unk_04 & 0x40)
    {
        var_8 = sub_198800((type_3DF8D8_04 *)&dword_4B913C);
        if (!(dword_4E56A0[l4].unk_04 & 0x80))
            sub_EACA0(var_8->sub_197550(0, 0), 0, 1);
    }
    return 0;
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_10D490@@YAHHPAUtype_170DF0@@@Z @ 0x0010D490
// Single player only (SP 0x10D490; sp_sub_10E070 registers it where multiplayer's
// counter-up message has the empty sub_31DB0): counts the counted active objective whose
// message it is up and shows its counter text as sp_sub_10D060 does; 1 (stays
// registered).
RwInt32 sp_sub_10D490(RwInt32 arg_0, type_170DF0 *arg_4)
{
    RwChar var_80[0x80];
    const RwChar *var_t;
    type_3DF8D8 *var_o;
    RwInt32 var_i;

    for (var_i = 0; var_i < 15; var_i++)
    {
        if ((dword_4E56A0[var_i].unk_04 & 2) && (dword_4E56A0[var_i].unk_04 & 0x20) && dword_4E56A0[var_i].unk_24
            && dword_4E56A0[var_i].unk_24->unk_14 == arg_4->unk_00->unk_04)
        {
            dword_4E56A0[var_i].unk_08++;
            break;
        }
    }
    var_t = dword_4E56A0[var_i].unk_00->sp_sub_125370(var_80, dword_4E56A0[var_i].unk_08);
    if (var_t)
    {
        if (!(dword_4E56A0[var_i].unk_04 & 0x80))
            sub_EACA0(var_t, 0, 1);
    }
    else if (dword_4E56A0[var_i].unk_04 & 0x40)
    {
        var_o = sub_198800((type_3DF8D8_04 *)&dword_4B913C);
        if (!(dword_4E56A0[var_i].unk_04 & 0x80))
            sub_EACA0(var_o->sub_197550(0, 0), 0, 1);
    }
    return 1;
}

// sp-match: ?sp_sub_10D580@@YAHHPAUtype_170DF0@@@Z @ 0x0010D580
// Single player only (SP 0x10D580; the counter-down message's handler sp_sub_10E190
// registers): counts the objective down; at 0 it completes (flag 4, counter off), ends
// its registration and shows its complete text (0); else its counter text (1).
RwInt32 sp_sub_10D580(RwInt32 arg_0, type_170DF0 *arg_4)
{
    RwChar var_80[0x80];
    const RwChar *var_t;
    type_3DF8D8 *var_o;
    RwInt32 var_i;

    for (var_i = 0; var_i < 15; var_i++)
    {
        if ((dword_4E56A0[var_i].unk_04 & 2) && (dword_4E56A0[var_i].unk_04 & 0x20) && dword_4E56A0[var_i].unk_28
            && dword_4E56A0[var_i].unk_28->unk_14 == arg_4->unk_00->unk_04)
        {
            if (--dword_4E56A0[var_i].unk_08 <= 0)
            {
                dword_4E56A0[var_i].unk_04 = (dword_4E56A0[var_i].unk_04 & ~0x20) | 4;
                dword_4E56A0[var_i].unk_28 = 0;
                var_t = dword_4E56A0[var_i].unk_00->sp_sub_1252B0(var_80, dword_4E56A0[var_i].unk_08);
                if (var_t && !(dword_4E56A0[var_i].unk_04 & 0x80))
                    sub_EACA0(var_t, 0, 1);
                return 0;
            }
            break;
        }
    }
    var_t = dword_4E56A0[var_i].unk_00->sp_sub_125370(var_80, dword_4E56A0[var_i].unk_08);
    if (var_t)
    {
        if (!(dword_4E56A0[var_i].unk_04 & 0x80))
            sub_EACA0(var_t, 0, 1);
    }
    else if (dword_4E56A0[var_i].unk_04 & 0x40)
    {
        var_o = sub_198800((type_3DF8D8_04 *)&dword_4B913C);
        if (!(dword_4E56A0[var_i].unk_04 & 0x80))
            sub_EACA0(var_o->sub_197550(0, 0), 0, 1);
    }
    return 1;
}
#endif

// match: ?sub_170FD0@@YAHPAUtype_3DF8D8_04@@M@Z @ 0x00170FD0
// sp-match: ?sub_170FD0@@YAHPAUtype_3DF8D8_04@@M@Z @ 0x0010D6E0
// Sets the objective arg_0's nag timer (and its reload) to arg_4.
RwInt32 sub_170FD0(type_3DF8D8_04 *arg_0, RwReal arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (var_4 >= 15)
        return 0;
    dword_4E56A0[var_4].unk_0C = arg_4;
    dword_4E56A0[var_4].unk_10 = dword_4E56A0[var_4].unk_0C;
    return 1;
}

// match: ?sub_171070@@YAXPAUtype_3DF8D8_04@@PAUtype_712B0@@@Z @ 0x00171070
// sp-match: ?sub_171070@@YAXPAUtype_3DF8D8_04@@PAUtype_712B0@@@Z @ 0x0010D7D0
// Targets the objective arg_0 at the trigger arg_4 (and makes it the
// current one).
void sub_171070(type_3DF8D8_04 *arg_0, type_712B0 *arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (var_4 >= 15)
        return;
    dword_4E56A0[var_4].unk_2C.sub_144940((Trigger *)arg_4);
    dword_4E56A0[var_4].unk_40 = 0;
#ifdef CODFH_SP
    // Single player restarts its pulse at 10 (SP 0x10D8B7).
    dword_4E56A0[var_4].unk_44 = 10.0f;
#endif
    byte_4E564C = (RwInt8)var_4;
}

// match: ?sub_171110@@YAXPAUtype_3DF8D8_04@@PAUtype_3D3548@@@Z @ 0x00171110
// sp-match: ?sub_171110@@YAXPAUtype_3DF8D8_04@@PAUtype_3D3548@@@Z @ 0x0010D8D0
// Likewise at the entity arg_4.
void sub_171110(type_3DF8D8_04 *arg_0, type_3D3548 *arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (var_4 >= 15)
        return;
    dword_4E56A0[var_4].unk_38.sub_D48D0(arg_4);
    dword_4E56A0[var_4].unk_40 = 1;
#ifdef CODFH_SP
    // Single player restarts its pulse at 10 (SP 0x10D9B7).
    dword_4E56A0[var_4].unk_44 = 10.0f;
#endif
    byte_4E564C = (RwInt8)var_4;
}

// match: ?sub_1711B0@@YAXPAUtype_3DF8D8_04@@PAUSplinePath@@@Z @ 0x001711B0
// sp-match: ?sub_1711B0@@YAXPAUtype_3DF8D8_04@@PAUSplinePath@@@Z @ 0x0010D9D0
void sub_1711B0(type_3DF8D8_04 *arg_0, SplinePath *arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (var_4 >= 15)
        return;
    dword_4E56A0[var_4].unk_3C = arg_4;
}

// match: ?sub_171230@@YAXPAUtype_3DF8D8_04@@M@Z @ 0x00171230
// sp-match: ?sub_171230@@YAXPAUtype_3DF8D8_04@@M@Z @ 0x0010DAB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sets the objective arg_0's lookahead distance to arg_4 (in metres; kept
// squared, in centimetres).
void sub_171230(type_3DF8D8_04 *arg_0, RwReal arg_4)
{
    RwInt32 var_8;
    RwReal l4;

    for (var_8 = 0; var_8 < 15; var_8++)
    {
        if ((dword_4E56A0[var_8].unk_04 & 1) && dword_4E56A0[var_8].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_8].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (var_8 >= 15)
        return;
    dword_4E56A0[var_8].unk_48 = (l4 = arg_4 * 100.0f) * l4;
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_10DBA0@@YACXZ @ 0x0010DBA0
// Single player only (SP 0x10DBA0; the HUD (SP 0xAC0CA) and sp_sub_10E2B0 call it): the
// objective the target system points at: none (-1) while it is off; the current one
// (byte_4E564C) while it is in use, active and neither complete nor failed; else the
// first such in the list that marks a live entity (unk_40 1) or an object (unk_40 0).
RwInt8 sp_sub_10DBA0()
{
    RwInt8 var_id;
    RwUInt32 var_f;

    if (!dword_4E5648)
        return -1;
    if (byte_4E564C != -1)
    {
        var_f = dword_4E56A0[byte_4E564C].unk_04;
        if ((var_f & 1) && (var_f & 2) && !(var_f & 0xC))
            return byte_4E564C;
    }
    for (var_id = byte_4E564D; var_id != -1; var_id = sub_170890(var_id))
    {
        var_f = dword_4E56A0[var_id].unk_04;
        if ((var_f & 1) && (var_f & 2) && !(var_f & 0xC))
        {
            if (dword_4E56A0[var_id].unk_40 == 1 && dword_4E56A0[var_id].unk_38.sub_D4910())
                return var_id;
            if (dword_4E56A0[var_id].unk_40 == 0 && dword_4E56A0[var_id].unk_2C.unk_08)
                return var_id;
        }
    }
    return -1;
}
#endif

// match: ?sub_1712C0@@YAHPAUtype_4E56A0@@PAM1@Z @ 0x001712C0
// sp-match: ?sub_1712C0@@YAHPAUtype_4E56A0@@PAM1@Z @ 0x0010DC50
RwInt32 sub_1712C0(type_4E56A0 *arg_0, RwReal *arg_4, RwReal *arg_8)
{
    if (arg_0->unk_44 <= 0.0f)
        return 0;
#ifdef CODFH_SP // single player (SP 0x10DC50) scales by 1.75 in the last 1.25 of 10 seconds
    // shape: SP 0x10DC50 scales the phase in steps and captures the last product in its store.
    RwReal t = (RwReal)fmod((RwDouble)arg_0->unk_44, 1.25);
    t /= 1.25f;
    t *= 2.25f;
    *arg_4 = 2.25f - t;
    RwReal u = *arg_4 / 2.25f;
    *arg_8 = (u *= 1.2f, 1.25f - u);
    if (10.0f - arg_0->unk_44 <= 1.25f)
        *arg_4 *= 1.75f;
#else
    *arg_4 = 2.25f - (RwReal)fmod((RwDouble)arg_0->unk_44, 1.25) / 1.25f * 2.25f;
    *arg_8 = 1.25f - (*arg_4 - 0.0f) / 2.25f * 1.2f;
#endif
    return 1;
}

// match: ?sub_171340@@YAPAURwV3d@@H@Z @ 0x00171340
// sp-match: ?sub_171340@@YAPAURwV3d@@H@Z @ 0x0010DCD0
RwV3d *sub_171340(RwInt32 arg_0)
{
    type_3D3548 *var_4;

    var_4 = dword_4E5654[arg_0].sub_D4910();
    if (var_4 && !var_4->unk_28_9)
        return var_4->sub_CD550();
    return 0;
}

// match: ?sub_171380@@YAHPAUtype_3D3548@@@Z @ 0x00171380
// sp-match: ?sub_171380@@YAHPAUtype_3D3548@@@Z @ 0x0010DD00
// Marks the entity arg_0 in the first free marker; 0 when all are taken.
RwInt32 sub_171380(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if (!dword_4E5654[var_4].sub_D4910() || dword_4E5654[var_4].sub_D4910()->unk_28_9)
        {
            dword_4E5654[var_4].sub_D48D0(arg_0);
            return 1;
        }
    }
    return 0;
}

// match: ?sub_1713F0@@YAHPAUtype_3D3548@@@Z @ 0x001713F0
// sp-match: ?sub_1713F0@@YAHPAUtype_3D3548@@@Z @ 0x0010DD60
RwInt32 sub_1713F0(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if (dword_4E5654[var_4].sub_D4910() == arg_0)
        {
            dword_4E5654[var_4].sub_D48D0(0);
            return 1;
        }
    }
    return 0;
}

// match: ?sub_171440@@YAXXZ @ 0x00171440
// sp-match: ?sub_171440@@YAXXZ @ 0x0010DDB0
void sub_171440()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
        dword_4E5654[var_4].sub_D48D0(0);
}

// match: ?sub_171480@@YAXPAUtype_3DF8D8_04@@H@Z @ 0x00171480
// Starts (arg_4) or stops the objective arg_0's pulse.
void sub_171480(type_3DF8D8_04 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 15; var_4++)
    {
        if ((dword_4E56A0[var_4].unk_04 & 1) && dword_4E56A0[var_4].unk_00->unk_04.unk_00 == arg_0->unk_00
            && dword_4E56A0[var_4].unk_00->unk_04.unk_04 == arg_0->unk_04)
            break;
    }
    if (var_4 >= 15)
        return;
    if (arg_4 && dword_4E56A0[var_4].unk_44 <= 0.0f)
        dword_4E56A0[var_4].unk_44 = 10.0f;
    else if (!arg_4 && dword_4E56A0[var_4].unk_44 > 0.0f)
        dword_4E56A0[var_4].unk_44 = 0;
}

// The Dinkumware STL functions sub_1708E0 instantiates (the XDK's headers,
// compiled here at /Od): std::vector<RwInt32>'s push_back, insert and
// _Insert_n (with its handler; _Xlen and _Uninit_copy are kept from earlier
// objects), then the records' implicit constructor and destructor, which
// the array dword_4E56A0's initializer runs.
// match: ?push_back@?$vector@HV?$allocator@H@std@@@std@@QAEXABH@Z @ 0x00171550
// match: ?insert@?$vector@HV?$allocator@H@std@@@std@@QAE?AViterator@12@V312@ABH@Z @ 0x00171630
// match: ?_Insert_n@?$vector@HV?$allocator@H@std@@@std@@IAEXViterator@12@IABH@Z @ 0x001716E0
// match: __ehhandler$?_Insert_n@?$vector@HV?$allocator@H@std@@@std@@IAEXViterator@12@IABH@Z @ 0x00301FC0
// match: ??0type_4E56A0@@QAE@XZ @ 0x00171D50
// match: ??1type_4E56A0@@QAE@XZ @ 0x00171DA0
// sp-match: ??1type_4E56A0@@QAE@XZ @ 0x0010DDF0
// sp-match: ??0type_4E56A0@@QAE@XZ @ 0x0010DDD0
