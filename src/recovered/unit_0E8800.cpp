// The movie player (include/game/movie.h). The original file name is not in
// the image, so it is named for its start address.

#include <stdio.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rw/bastream.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/frontend.h"
#include "game/movie.h"
#include "types/type_3D3548.h"
#include "types/soundbank.h"
#include "types/CShellLevelBehaviorClass.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D8CC0
extern const RwReal flt_3D8CC0 = 16.666666f;
// 0x004B88A8
bool byte_4B88A8;
// 0x004B892C
RwInt32 dword_4B892C;
// 0x004B8B58
type_19D580 unk_4B8B58;
// 0x004B8C70
type_19D580 unk_4B8C70;
// 0x004B8D88
type_19D580 unk_4B8D88;
// 0x004B8E9C
#ifndef CODFH_PLAIN
bool byte_4B8E9C;
#endif
// 0x004B8E9D
#ifndef CODFH_PLAIN
bool byte_4B8E9D;
#endif
// 0x004B8E9E
#ifndef CODFH_PLAIN
bool byte_4B8E9E;
#endif
#ifdef CODFH_SP // single player's own (sp_sub_B1A10, sp_sub_B1A50, sp_sub_B1D40): its front end movie's loop and frame flags
// SP 0x003B5817
bool sp_byte_3B5817;
// SP 0x003B5818
bool sp_byte_3B5818;
#endif
// 0x004B8EA1
bool byte_4B8EA1;
// 0x004B8EA4
RwInt32 dword_4B8EA4;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_3DF8D8_04 unk_4B8EA8;
type_3DF8D8_04 unk_4B8EB0;
// Six keys no code reads.
type_3DF8D8_04 unk_4B8EB8(0x36B9672C, 0x92246E84);
type_3DF8D8_04 unk_4B8EC0(0xFCB48EB0, 0xDCEECA9F);
type_3DF8D8_04 unk_4B8ED8(0x0A945161, 0xE39AFC4E);
type_3DF8D8_04 unk_4B8EE0(0xFCB48EA1, 0x08FB2FB7);
type_3DF8D8_04 unk_4B8EC8(0x1DD09976, 0xDB9AEF27);
type_3DF8D8_04 unk_4B8ED0(0x44371DFE, 0x028566AB);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D8CC0@@3MB @ 0x003D8CC0
// match: ??_C@_07KEJHJGKM@?$CFs?$CFs?2?$CFs?$AA@ @ 0x003D8CC4
// match: ??_C@_0O@KNADBNPM@SHELL?2MOVIES?2?$AA@ @ 0x003D8CCC
// match: ??_C@_0DE@HMCPHGBP@Failed?5to?5load?5movie?5for?5movie?5p@ @ 0x003D8CDC
// match: ??_C@_05INIGKNBD@d?3?2?$CFs?$AA@ @ 0x003D8D10
// match: .CRT$XCU+0 @ 0x0042702C
// match: .CRT$XCU+4 @ 0x00427030
// match: .CRT$XCU+8 @ 0x00427034
// match: .CRT$XCU+12 @ 0x00427038
// match: .CRT$XCU+16 @ 0x0042703C
// match: .CRT$XCU+20 @ 0x00427040
// match: .CRT$XCU+24 @ 0x00427044
// match: .CRT$XCU+28 @ 0x00427048

// match: _$E2 @ 0x0030B400
// match: _$E4 @ 0x0030B420
// match: _$E6 @ 0x0030B440
// match: _$E8 @ 0x0030B460
// match: _$E10 @ 0x0030B480
// match: _$E12 @ 0x0030B4A0
// match: _$E14 @ 0x0030B4C0
// match: _$E16 @ 0x0030B4E0
// match: ?sub_E8800@@YAXXZ @ 0x000E8800
// sp-match: ?sub_E8800@@YAXXZ @ 0x000B19B0

void sub_E8800()
{
    byte_4B8E9C = false;
    byte_4B8E9D = false;
    unk_4B8B58.sub_19D580();
    unk_4B8D88.sub_19D580();
    byte_4B8E9E = true;
}

// match: ?sub_E8830@@YAXXZ @ 0x000E8830
// sp-match: ?sub_E8830@@YAXXZ @ 0x000B19E0
void sub_E8830()
{
    byte_4B8E9C = false;
    byte_4B8E9D = false;
    unk_4B8B58.sub_19D5E0();
    unk_4B8D88.sub_19D5E0();
    byte_4B8E9E = false;
}

#ifdef CODFH_SP
// Single player's front end plays its background movie on unk_4B8C70 (sp_sub_B1D40): whether
// it loops (sp_byte_3B5817), and set when a step showed no new frame (sp_byte_3B5818, cleared
// by its draw, sp_sub_B1A50).

// sp-match: ?sp_sub_B1A10@@YAXXZ @ 0x000B1A10
// Steps the front end's movie: closes it at its end unless it loops.
void sp_sub_B1A10()
{
    switch (unk_4B8C70.sub_19D720(sp_byte_3B5817))
    {
    case 1:
        if (!sp_byte_3B5817)
        {
            unk_4B8C70.sub_19D5E0();
        }
        break;
    case 2:
        sp_byte_3B5818 = true;
        break;
    }
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_B1A50@@YAXPAURwCamera@@@Z @ 0x000B1A50
// Draws the front end's movie on the camera arg_0 while it is open.
void sp_sub_B1A50(RwCamera *arg_0)
{
    if (unk_4B8C70.unk_10C)
    {
        RwCameraBeginUpdate(arg_0);
        unk_4B8C70.sub_19D810(arg_0, 1);
        RwCameraEndUpdate(arg_0);
    }
    sp_byte_3B5818 = false;
}
#endif

// match: ?sub_E8860@@YAX_N@Z @ 0x000E8860
// sp-match: ?sub_E8860@@YAX_N@Z @ 0x000B1A90
void sub_E8860(bool arg_0)
{
    byte_4B88A8 = false;
    sub_DA550(false);
    if (arg_0)
    {
        byte_4B8EA1 = true;
        unk_4B8C70.sub_19D890(byte_4B8EA1);
    }
    else
    {
        unk_4B8C70.sub_19D8E0(0, 0);
    }
}

// match: ?sub_E88B0@@YAX_N@Z @ 0x000E88B0
// sp-match: ?sub_E88B0@@YAX_N@Z @ 0x000B1AD0
void sub_E88B0(bool arg_0)
{
    byte_4B88A8 = true;
    sub_DA550(true);
    if (arg_0)
    {
        byte_4B8EA1 = false;
        unk_4B8C70.sub_19D890(byte_4B8EA1);
        while (unk_4B8C70.sub_19D8C0())
        {
        }
    }
    else
    {
        unk_4B8C70.sub_19D8E0(0, 1);
    }
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_B1B20@@YAXXZ @ 0x000B1B20
// Stops the front end's movie.
void sp_sub_B1B20()
{
    unk_4B8C70.sub_19D5E0();
}
#endif

// match: ?sub_E8910@@YAXXZ @ 0x000E8910
// sp-match: ?sub_E8910@@YAXXZ @ 0x000B1E00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_E8910()
{
    type_3DF8D8 *var_8C;
    RwChar var_88[0x80];
    RwCamera *l4;

    if (byte_4B8E9C)
    {
        var_8C = sub_198800(&unk_4B8EA8);
        if (sub_19B0A0() != 0 && sub_19B0A0() != 1)
        {
            sprintf(var_88, "%s%s\\%s", "SHELL\\MOVIES\\", dword_428E38[sub_19B0A0()], var_8C->unk_10_name);
        }
        else
        {
            sprintf(var_88, "%s%s", "SHELL\\MOVIES\\", var_8C->unk_10_name);
        }
        l4 = (RwCamera *)dword_4E5C74;
        sub_E8BA0(var_88, l4);
        sub_19BAC0(l4);
    }
}

// match: ?sub_E89E0@@YAXXZ @ 0x000E89E0
// sp-match: ?sub_E89E0@@YAXXZ @ 0x000B1EC0
void sub_E89E0()
{
    type_3DF8D8 *var_22C;
    RwChar var_228[0x200];
    RwChar var_24[0x20];

    if (byte_4B8E9D)
    {
        var_22C = sub_198800(&unk_4B8EB0);
        sprintf(var_24, "%s", dword_428E38[sub_19B0A0()]);
        strupr(var_24);
        sprintf(var_228, "%s%s\\%s", "SHELL\\MOVIES\\", var_24, var_22C->unk_10_name);
        if (!sub_E8EB0(var_228))
        {
            sprintf(var_228, "%s%s", "SHELL\\MOVIES\\", var_22C->unk_10_name);
        }
        sub_E8BA0(var_228, (RwCamera *)dword_4E5C74);
    }
}

// match: ?sub_E8AC0@@YAXPBDHHH@Z @ 0x000E8AC0
// sp-match: ?sub_E8AC0@@YAXPBDHHH@Z @ 0x000B1F90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_E8AC0(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RwChar var_B0[0x80];
    RwRGBA v2C;                 // a colour it clears and never uses
    RwChar var_28[0x20];
    RwCamera *l4;

    v2C.alpha = v2C.red = v2C.green = v2C.blue = 0;
    if (arg_4)
    {
        l4 = (RwCamera *)arg_4;
    }
    else
    {
        l4 = (RwCamera *)dword_4E5CBC;
    }
    sprintf(var_28, "%s", dword_428E38[sub_19B0A0()]);
    strupr(var_28);
    sprintf(var_B0, "%s%s\\%s", "SHELL\\MOVIES\\", var_28, arg_0);
    if (!sub_E8EB0(var_B0))
    {
        sprintf(var_B0, "%s%s", "SHELL\\MOVIES\\", arg_0);
    }
    sub_E8BA0(var_B0, l4);
}

// match: ?sub_E8BA0@@YAXPBDPAURwCamera@@@Z @ 0x000E8BA0
// sp-match: ?sub_E8BA0@@YAXPBDPAURwCamera@@@Z @ 0x000B1B30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_E8BA0(const RwChar *arg_0, RwCamera *arg_4)
{
    type_19D580 var_120;
    RwInt32 var130;
    RwInt32 v12C;
    RwReal var128;
    RwInt32 var124;

    sub_E8860(true);
    if (!var_120.sub_19D580())
    {
        return;
    }
    if (!var_120.sub_19D640(arg_0, 1))
    {
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
        sub_19A750("Failed to load movie for movie player. Bailing out!");
#endif
        var_120.sub_19D5E0();
        return;
    }
    dword_4B8EA4 = 0;
    var124 = 3;
    while (var124 != 1)
    {
        var124 = var_120.sub_19D720(0);
        v12C = 0;
        unk_4B9308.sub_EE6D0();
        if (dword_4B892C)
        {
            for (var130 = 0; var130 < 4; var130++)
            {
                var128 = unk_4B9308.sub_EE8F0(var130, 0x17);
                var128 += unk_4B9308.sub_EE8F0(var130, 0xB);
                if (var128 != 0.0f)
                {
                    v12C = 1;
                }
            }
        }
        var128 = unk_4B9308.sub_EE8F0(0, 0x17);
        var128 += unk_4B9308.sub_EE8F0(0, 0xB);
        if (var128 != 0.0f)
        {
            v12C = 1;
        }
        if (dword_4B8EA4)
        {
            v12C = 1;
        }
        if (v12C)
        {
            break;
        }
        if (var124 == 2)
        {
            continue;
        }
        RwCameraBeginUpdate(arg_4);
        var_120.sub_19D810(arg_4, 0);
        RwCameraEndUpdate(arg_4);
        RwCameraShowRaster(arg_4, 0, 1);
    }
    var_120.sub_19D5E0();
    sub_E88B0(true);
}

// match: ?sub_E8DB0@@YAXPAUTrigger_key@@@Z @ 0x000E8DB0
// sp-match: ?sub_E8DB0@@YAXPAUTrigger_key@@@Z @ 0x000B2050
void sub_E8DB0(Trigger_key *arg_0)
{
    if (arg_0 && arg_0->unk_00 && arg_0->unk_04)
    {
        unk_4B8EA8.unk_00 = arg_0->unk_00;
        unk_4B8EA8.unk_04 = arg_0->unk_04;
        byte_4B8E9C = true;
        sub_1252E0(sub_19A750, 0);
    }
    else
    {
        unk_4B8EA8.unk_00 = 0;
        unk_4B8EA8.unk_04 = 0;
        byte_4B8E9C = false;
        sub_1252E0(0, 0);
    }
}

// match: ?sub_E8E30@@YAXPAUTrigger_key@@@Z @ 0x000E8E30
// sp-match: ?sub_E8E30@@YAXPAUTrigger_key@@@Z @ 0x000B20B0
void sub_E8E30(Trigger_key *arg_0)
{
    if (arg_0 && arg_0->unk_00 && arg_0->unk_04)
    {
        unk_4B8EB0.unk_00 = arg_0->unk_00;
        unk_4B8EB0.unk_04 = arg_0->unk_04;
        byte_4B8E9D = true;
        sub_1252E0(sub_19A750, 1);
    }
    else
    {
        unk_4B8EB0.unk_00 = 0;
        unk_4B8EB0.unk_04 = 0;
        byte_4B8E9D = false;
        sub_1252E0(0, 1);
    }
}

// match: ?sub_E8EB0@@YA_NPBD@Z @ 0x000E8EB0
// sp-match: ?sub_E8EB0@@YA_NPBD@Z @ 0x000B1CB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool sub_E8EB0(const RwChar *arg_0)
{
    RwChar var_110[0x80];
    RwStream *l8C;
    RwChar var_88[0x80];

    l8C = 0;
    sub_D7F20(var_88, arg_0);
    sprintf(var_110, "d:\\%s", var_88);
    l8C = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, var_110);
    if (l8C)
    {
        RwStreamClose(l8C, 0);
        return true;
    }
    return false;
}

#ifdef CODFH_SP
// sp-match: ?sp_sub_B1D40@@YAXPBD_N@Z @ 0x000B1D40
// Opens the movie arg_0 (in the language's folder when it has one) as the front end's
// background, looping when arg_4 is set (SP 0xA53C9: "fend.bik").
void sp_sub_B1D40(const RwChar *arg_0, bool arg_4)
{
    RwChar var_A0[0x20];
    RwChar var_80[0x80];

    sprintf(var_A0, "%s", dword_428E38[sub_19B0A0()]);
    strupr(var_A0);
    sprintf(var_80, "%s%s\\%s", "SHELL\\MOVIES\\", var_A0, arg_0);
    if (!sub_E8EB0(var_80))
    {
        sprintf(var_80, "%s%s", "SHELL\\MOVIES\\", arg_0);
    }
    unk_4B8C70.sub_19D640(var_80, 0);
    sub_E8860(false);
    sp_byte_3B5817 = arg_4;
}
#endif


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004B8E9C: unk_4B8D88 + 0x114
bool &byte_4B8E9C = *(bool *)((RwUInt8 *)&unk_4B8D88 + 0x114);
// 0x004B8E9D: unk_4B8D88 + 0x115
bool &byte_4B8E9D = *(bool *)((RwUInt8 *)&unk_4B8D88 + 0x115);
// 0x004B8E9E: unk_4B8D88 + 0x116
bool &byte_4B8E9E = *(bool *)((RwUInt8 *)&unk_4B8D88 + 0x116);
#endif
