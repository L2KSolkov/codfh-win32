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

type_144940 dword_4E5690;
type_4E56A0 dword_4E56A0[15];
// Initialized after the two above (its .CRT$XCU entry is their third).
type_D48D0 dword_4E5654[15];

// match: ?sub_16FF90@@YAXXZ @ 0x0016FF90
void sub_16FF90()
{
    sub_16FFF0();
    dword_4E5650 = 0;
}

// match: ?sub_16FFB0@@YAXPAVTrigger@@@Z @ 0x0016FFB0
void sub_16FFB0(Trigger *arg_0)
{
    if (dword_4E5650)
        sub_19A750("WARNING: ObjectiveManager initialized twice! There might be 2 level scripts in the level");
    sub_16FFF0();
    dword_4E5650 = 1;
    dword_4E5690.sub_144940(arg_0);
}

// match: ?sub_16FFF0@@YAXXZ @ 0x0016FFF0
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
void sub_1702F0()
{
    dword_4E5650 = 0;
    sub_1701B0();
}

// match: ?sub_170310@@YAXM@Z @ 0x00170310
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Runs the records' pulses down by arg_0 frames (in seconds), each
// restarting from 10 when it runs out.
void sub_170310(RwReal arg_0)
{
    RwInt32 var_8;
    RwReal l4;

    l4 = arg_0 / 60.0f;
    for (var_8 = 0; var_8 < 15; var_8++)
    {
        if (dword_4E56A0[var_8].unk_44 > 0.0f)
        {
            dword_4E56A0[var_8].unk_44 = dword_4E56A0[var_8].unk_44 - l4;
            if (dword_4E56A0[var_8].unk_44 <= 0.0f)
                dword_4E56A0[var_8].unk_44 = dword_4E56A0[var_8].unk_44 + 10.0f;
        }
    }
}

// match: ?sub_1703B0@@YAXPAUtype_3DF8D8_04@@HH@Z @ 0x001703B0
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

// match: ?sub_170790@@YAXPAUtype_3DF8D8_04@@H@Z @ 0x00170790
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

// match: ?sub_170890@@YACC@Z @ 0x00170890
RwInt8 sub_170890(RwInt8 arg_0)
{
    return dword_4E56A0[arg_0].unk_54;
}

// match: ?sub_1708B0@@YAPAUtype_4E56A0@@C@Z @ 0x001708B0
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
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_18 = sub_6BAE0((RwInt32)var_C, (RwUInt32)sub_170DF0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
    return 1;
}

// match: ?sub_170A30@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170A30
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
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_1C = sub_6BAE0((RwInt32)var_C, (RwUInt32)(RwInt32 (*)(RwInt32))sub_170ED0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
    return 1;
}

// match: ?sub_170B20@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170B20
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
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_20 = sub_6BAE0((RwInt32)var_C, (RwUInt32)sub_170EE0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
    return 1;
}

// match: ?sub_170C10@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170C10
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
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_24 = sub_6BAE0((RwInt32)var_C, (RwUInt32)(RwInt32 (*)())sub_31DB0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
    return 1;
}

// match: ?sub_170D00@@YAHPAUtype_3DF8D8_04@@H@Z @ 0x00170D00
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
    bp_8 = dword_4E5690.unk_08;
    var_C = dword_4E5690.unk_08;
    dword_4E56A0[bp_4].unk_28 = sub_6BAE0((RwInt32)var_C, (RwUInt32)(RwInt32 (*)())sub_31DB0, (RwInt32)bp_8, arg_4, 0,
                                           msg_flags(2, 1));
    return 1;
}

// match: ?sub_170DF0@@YAHHPAUtype_170DF0@@@Z @ 0x00170DF0
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

// match: ?sub_170FD0@@YAHPAUtype_3DF8D8_04@@M@Z @ 0x00170FD0
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
    byte_4E564C = (RwInt8)var_4;
}

// match: ?sub_171110@@YAXPAUtype_3DF8D8_04@@PAUtype_3D3548@@@Z @ 0x00171110
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
    byte_4E564C = (RwInt8)var_4;
}

// match: ?sub_1711B0@@YAXPAUtype_3DF8D8_04@@PAUSplinePath@@@Z @ 0x001711B0
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

// match: ?sub_1712C0@@YAHPAUtype_4E56A0@@PAM1@Z @ 0x001712C0
RwInt32 sub_1712C0(type_4E56A0 *arg_0, RwReal *arg_4, RwReal *arg_8)
{
    if (arg_0->unk_44 <= 0.0f)
        return 0;
    *arg_4 = 2.25f - (RwReal)fmod((RwDouble)arg_0->unk_44, 1.25) / 1.25f * 2.25f;
    *arg_8 = 1.25f - (*arg_4 - 0.0f) / 2.25f * 1.2f;
    return 1;
}

// match: ?sub_171340@@YAPAURwV3d@@H@Z @ 0x00171340
RwV3d *sub_171340(RwInt32 arg_0)
{
    type_3D3548 *var_4;

    var_4 = dword_4E5654[arg_0].sub_D4910();
    if (var_4 && !var_4->unk_28_9)
        return var_4->sub_CD550();
    return 0;
}

// match: ?sub_171380@@YAHPAUtype_3D3548@@@Z @ 0x00171380
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
