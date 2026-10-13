// Split from unit_0D6640.cpp at 0x0D95A0, where the image starts another object (the frame timing; its .data from deltaTime, 0x429284):
// its .rdata begins at 0x3D7E20 with its own 16.666666, the unreferenced constant every game
// object starts its constants with (PLAN M7).

#include <stdio.h>
#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "rws/ceventhandler.h"
#include "rws/cattributehandler.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/waitscreen.h"
#include "types/asynchload.h"
#include "types/soundbank.h"
#include "types/LevelInfo.h"
#include "types/StartingSections.h"
#include "types/SectionInfo.h"
#include "types/type_72810.h"
#include "types/ccess.h"
#include "types/type_4B8EF0.h"
#include "types/vec4.h"
#include "types/CAnimPackSelector.h"
#include "types/type_4B85F8.h"
#include "types/musicplayer.h"
#include "types/type_3D3548.h"
#include "types/CShellLevelBehaviorClass.h"
#include "types/type_10F710.h"
#include "types/type_DC400.h"
#include <string.h>
#include "rw/baraster.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7E20
extern const RwReal flt_3D7E20 = 16.666666f;
// 0x003D7E24
extern const RwReal flt_3D7E24 = 5.0f;
// 0x00429284
RwReal deltaTime = 1.0f;
// 0x00429288
RwReal flt_429288 = 1.0f;
// 0x0042928C
RwReal dword_42928C = -1.0f;
// 0x00429290
RwReal flt_429290 = 1.0f;
// 0x00429294
RwReal flt_429294 = 0.2f;
// 0x00429298
RwReal flt_429298 = 1.0f;
// 0x0042929C
bool byte_42929C = true;

// match: ?flt_3D7E20@@3MB @ 0x003D7E20
// match: ?flt_3D7E24@@3MB @ 0x003D7E24
// match: ?deltaTime@@3MA @ 0x00429284
// match: ?flt_429288@@3MA @ 0x00429288
// match: ?dword_42928C@@3MA @ 0x0042928C
// match: ?flt_429290@@3MA @ 0x00429290
// match: ?flt_429294@@3MA @ 0x00429294
// match: ?flt_429298@@3MA @ 0x00429298
// match: ?byte_42929C@@3_NA @ 0x0042929C


// match: ?sub_D95A0@@YAXXZ @ 0x000D95A0
// sp-match: ?sub_D95A0@@YAXXZ @ 0x000A4440
void sub_D95A0()
{
    deltaTime = 1.0f;
    flt_429288 = 1.0f;
    dword_4B87C8 = 0.0f;
    dword_4B87CC = 0;
    dword_4B87D0 = 0;
    dword_4B87DC = 0;
    dword_4B87D8 = 0;
    dword_42928C = -1.0f;
    flt_429290 = 1.0f;
    dword_4B87E0 = 0;
    byte_42929C = true;
}
// match: ?sub_D9610@@YAXXZ @ 0x000D9610
// sp-match: ?sub_D9610@@YAXXZ @ 0x000A44A0
#ifdef CODFH_DRAW_TRIGGERS
// (the port's debug tools, port/src/debug/trigrng.cpp: a restart for the random numbers)
void TrigRngOnRestart();
#endif
void sub_D9610()
{
    sub_D95A0();
#ifdef CODFH_DRAW_TRIGGERS
    TrigRngOnRestart();
#endif
}
// match: ?sub_D9620@@YAXXZ @ 0x000D9620
// sp-match: ?sub_D9620@@YAXXZ @ 0x000A44B0
void sub_D9620()
{
    if (!dword_4B87CC && !dword_4B87D0)
    {
        deltaTime = 1.0f;
        flt_429288 = 1.0f;
    }
    else
    {
        dword_4B87D0 = RWS::Time::GetTime();
        dword_4B87D4 = dword_4B87D0 - dword_4B87CC;
        if (dword_4B87DC == 1)
        {
            deltaTime = flt_429294;
            flt_429288 = flt_429294;
        }
        else if (dword_4B87DC == 2)
        {
            flt_429288 = dword_4B87D4 / flt_3D7E20 * flt_429290;
            if (flt_429288 > flt_3D7E24)
            {
                deltaTime = flt_3D7E24;
            }
            else
            {
                deltaTime = flt_429288;
            }
        }
        else if (dword_4B87DC == 0 || dword_4B87DC == 6)
        {
            flt_429288 = dword_4B87D4 / flt_3D7E20;
            flt_429288 *= flt_429298;
            if (flt_429288 > flt_3D7E24)
            {
                deltaTime = flt_3D7E24;
            }
            else
            {
                deltaTime = flt_429288;
            }
        }
        else if (dword_4B87DC == 3 || dword_4B87DC == 4)
        {
            dword_4B87DC = 0;
            flt_429288 = dword_4B87D4 / flt_3D7E20;
            if (flt_429288 > flt_3D7E24)
            {
                deltaTime = flt_3D7E24;
            }
            else
            {
                deltaTime = flt_429288;
            }
        }
        else if (dword_4B87DC == 5)
        {
            if (byte_42929C)
            {
                deltaTime = 1.0f;
                flt_429288 = 1.0f;
                byte_42929C = false;
            }
            else
            {
                deltaTime = 0.0f;
                flt_429288 = deltaTime;
            }
        }
    }
    if (dword_42928C > 0.0f)
    {
        switch (dword_4B87DC)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            dword_42928C -= deltaTime;
            if (dword_42928C <= 0.0f)
            {
                dword_42928C = -1.0f;
                if (dword_4B87DC == 2)
                {
                    dword_44E898 = 3;
                }
                dword_4B87DC = 0;
            }
            break;
        }
    }
    else if (dword_4B87DC == 3)
    {
        dword_4B87DC = 0;
    }
    dword_4B87C8 += deltaTime;
    dword_4B87D8++;
    dword_4B87CC = RWS::Time::GetTime();
}
// match: ?sub_D98D0@@YAXMM@Z @ 0x000D98D0
// sp-match: ?sub_D98D0@@YAXMM@Z @ 0x000A46D0
void sub_D98D0(RwReal arg_0, RwReal arg_4)
{
    if (dword_4B87DC != 3 && dword_4B87DC != 4)
    {
        if (dword_4B87DC != 3)
        {
            dword_4B87DC = 2;
        }
        if (!dword_44E8A0)
        {
            dword_44E898 = 1;
        }
        if (dword_4B87DC != 3 && dword_4B87DC != 4)
        {
            flt_429290 = arg_0;
        }
        if (dword_4B87DC != 3 && dword_4B87DC != 4)
        {
            dword_42928C = arg_4;
        }
    }
}
// match: ?sub_D9950@@YAHXZ @ 0x000D9950
// sp-match: ?sub_D9950@@YAHXZ @ 0x000A4710
RwInt32 sub_D9950()
{
    RwInt32 var_4;
    type_D9950 var_1C;

    var_4 = 0;
    sub_82390();
    if (sub_19D290())
    {
        var_1C.unk_00 = Width;
        var_1C.unk_04 = Height;
        var_1C.unk_08 = dword_4B87F0;
        var_1C.unk_0C = dword_4B87F4;
        var_4 = sub_D99F0(&var_1C);
    }
    return var_4;
}
// match: ?sub_D99B0@@YAXXZ @ 0x000D99B0
// sp-match: ?sub_D99B0@@YAXXZ @ 0x000A4770
void sub_D99B0()
{
    if (sub_D6640())
    {
        sub_D7410();
        sub_D6EB0();
    }
}
#ifndef CODFH_SP // MP only: multiplayer's game-loop exit (single player's loop, SP 0xA4930, never leaves); no twin in config/sp/shared.txt
// match: ?sub_D99D0@@YAXXZ @ 0x000D99D0
void sub_D99D0()
{
    sub_D9BC0();
    sub_19D2D0();
    sub_19A750();
}
#endif
