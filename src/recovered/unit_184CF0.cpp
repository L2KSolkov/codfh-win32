// The performance display (type_4E73F0, game/debugmenu.h): the render
// timers as text and graphs, and its switches in the debug menu. A file of
// its own: its data is 8-aligned at 0x42A4F0, after the menu's at 0x42A4D4.

#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "types/animkey.h"
#include "game/functions.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/debugmenu.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "rw/rt2d.h"
#include "rw/badevice.h"
#include "types/type_DA580.h"
#include "game/profiler.h"
#include "rws/gftime.h"
#include "rw/baengine.h"
#include "types/type_DC400.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DE838
extern const RwReal flt_3DE838 = 16.666666f;
// 0x003DE83C
extern const RwReal flt_3DE83C = 16.666666f;
// 0x0042A4F0
type_42A4F0 dword_42A4F0[7] = {
    { 0, "General Types", 0 },
    { 1, "Logic", 0 },
    { 2, "Render Details", 0 },
    { 3, "Render Custom", 0 },
    { 4, "Entity Details", 0 },
    { 6, "Audio", 0 },
    { -1, "", 0 },
};
// 0x0042A598
type_42A598 dword_42A598[50] = {
    { 0, "TOTAL LOGIC          ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0 },
    { 0, "TOTAL RENDER         ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 0, "PAGEFLIP             ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711680, 0, 0, 0 },
    { 1, "SCRIPT               ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65535, 0, 0, 0 },
    { 1, "ENTITY UPDATE        ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16776960, 0, 0, 0 },
    { 1, "AUDIO                ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711935, 0, 0, 0 },
    { 1, "PROJECTILE UPDATE    ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 14522675, 0, 0, 0 },
    { 1, "AI                   ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 3381725, 0, 0, 0 },
    { 1, "PARTICLE UPDATE      ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0 },
    { 2, "CAMERA CLEAR         ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 2, "SKYBOX               ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711680, 0, 0, 0 },
    { 2, "SECTIONS             ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65535, 0, 0, 0 },
    { 2, "GAMEENTITY           ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16776960, 0, 0, 0 },
    { 2, "PROJECTILES          ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16750899, 0, 0, 0 },
    { 2, "RW-STUDIO            ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 3381759, 0, 0, 0 },
    { 2, "PARTICLES            ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0 },
    { 2, "PLAYER               ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 3, "ATOM RENDER          ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711680, 0, 0, 0 },
    { 3, "ATOM RENDER CBA      ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65535, 0, 0, 0 },
    { 3, "ATOM RENDER CBB      ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16776960, 0, 0, 0 },
    { 3, "ATOM RENDER CBC      ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711935, 0, 0, 0 },
    { 4, "ENTITY UPDATE        ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16750899, 0, 0, 0 },
    { 4, "ANIMATION            ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 3381759, 0, 0, 0 },
    { 4, "ANIMATION POST       ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0 },
    { 4, "ENTITY UPD: CLASSAI  ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 4, "ENTITY UPD: PHYSICS  ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711680, 0, 0, 0 },
    { 4, "ENTITY UPD: CLSN     ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 4, "ENTITY UPD: TRIGGER  ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711680, 0, 0, 0 },
    { 0, "SHELL                ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65535, 0, 0, 0 },
    { 0, "GAME LOOP            ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16777215, 0, 0, 0 },
    { 2, "SHADOWS              ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16748608, 0, 0, 0 },
    { 2, "SHRIMPS              ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0 },
    { 2, "DECALS               ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 0, "WORLD COLLIDE LINE   ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16750899, 0, 0, 0 },
    { 2, "CLONES               ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 6, "Audio Total          ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 6, "RwCoreUpdate         ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0 },
    { 6, "File Open SFX        ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16777215, 0, 0, 0 },
    { 6, "File Open Stream     ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16777215, 0, 0, 0 },
    { 6, "Asynch Loader        ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16748608, 0, 0, 0 },
    { 6, "Stream Updates       ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65535, 0, 0, 0 },
    { 6, "UnloadPreviousBanks  ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 255, 0, 0, 0 },
    { 6, "StartLoadingAWD      ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65280, 0, 0, 0 },
    { 6, "LoadingAWD           ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711680, 0, 0, 0 },
    { 6, "LoadingAWD_Chunk     ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 65535, 0, 0, 0 },
    { 6, "StartLoadingAGD      ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16711935, 0, 0, 0 },
    { 6, "LoadingAGD           ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16776960, 0, 0, 0 },
    { 6, "DoneLoadingAGD       ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 16777215, 0, 0, 0 },
    { 6, "DoneLoadingSoundBank ", 0, 0, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0, 8947848, 0, 0, 0 },
    { -1, "                     ", -1, -1, -1.0f, -1.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4E73F0 dword_4E73F0;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DE838@@3MB @ 0x003DE838
// match: ?flt_3DE83C@@3MB @ 0x003DE83C
// match: ??_C@_0BC@BPPJONIM@Display?5Highest?54?$AA@ @ 0x003DE840
// match: ??_C@_0BB@EDMBDFCA@Reset?5All?5Graphs?$AA@ @ 0x003DE854
// match: ??_C@_0BG@HFJONICB@FPS?3?5Graph?5Resolution?$AA@ @ 0x003DE868
// match: ??_C@_0BB@GFHANJLD@Performance?5Text?$AA@ @ 0x003DE880
// match: ??_C@_0BD@NIEGJEAC@Performance?5Graphs?$AA@ @ 0x003DE894
// match: ??_C@_0BH@ELMLAJEI@Performance?5Statistics?$AA@ @ 0x003DE8A8
// match: ??_C@_05KJDOJDAE@?$CF3?41f?$AA@ @ 0x003DE8C0
// match: ??_C@_0L@FJJNPEIF@FPS?3?5?$CF2?41f?$AA@ @ 0x003DE8C8
// match: __real@41600000 @ 0x003DE8D4
// match: ??_C@_08OKEDJHNF@?$CF3?41f?5?$CF?$CF?$AA@ @ 0x003DE8D8
// match: .CRT$XCU+0 @ 0x00427174
// match: ?dword_42A4F0@@3PAUtype_42A4F0@@A @ 0x0042A4F0
// match: ?dword_42A598@@3PAUtype_42A598@@A @ 0x0042A598

// match: _$E2 @ 0x0030BF90
// match: ?sub_184CF0@type_4E73F0@@QAEXXZ @ 0x00184CF0

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its switches under "Performance Statistics": a graph switch for each
// render timer in its group's submenu (made on first use), the text, the
// graphs' frame rate, reset and the highest four.
void type_4E73F0::sub_184CF0()
{
    type_4E73A8_14 *var_14;
    RwInt32 lv_10;
    type_4E73A8_14 *var_C;
    type_42A598 *bp_8;
    type_4E73A8_14 *bp_4;

    sub_184E40();
    var_C = unk_4E73A8.sub_183440(0, "Performance Statistics");
    sub_184F00();
    bp_4 = unk_4E73A8.sub_183440(var_C, "Performance Graphs");
    bp_8 = dword_42A598;
    while (bp_8->unk_00 != -1)
    {
        lv_10 = bp_8->unk_00;
        var_14 = dword_42A4F0[lv_10].unk_14;
        if (!var_14 || dword_42A4F0[lv_10].unk_00 == -1)
        {
            var_14 = unk_4E73A8.sub_183440(bp_4, dword_42A4F0[lv_10].unk_04);
            dword_42A4F0[lv_10].unk_14 = var_14;
        }
        unk_4E73A8.sub_183610(var_14, bp_8->unk_04, &bp_8->unk_40, 2);
        bp_8++;
    }
    unk_4E73A8.sub_183610(var_C, "Performance Text", &dword_4E73F0.unk_00, 2);
    unk_4E73A8.sub_183610(var_C, "FPS: Graph Resolution", &unk_04, 4);
    unk_4E73A8.sub_183610(var_C, "Reset All Graphs", &unk_08, 2);
    unk_4E73A8.sub_183610(var_C, "Display Highest 4", &unk_0C, 2);
}

// match: ?sub_184E40@type_4E73F0@@QAEXXZ @ 0x00184E40
// Forgets the groups' submenus and clears the statistics (building a
// fresh display on the stack it never uses).
void type_4E73F0::sub_184E40()
{
    type_42A4F0 *var_4;

    var_4 = dword_42A4F0;
    while (var_4->unk_00 != -1)
    {
        var_4->unk_14 = 0;
        var_4++;
    }
    type_4E73F0();
    sub_184F00();
}

// match: ??0type_4E73F0@@QAE@XZ @ 0x00184EA0
type_4E73F0::type_4E73F0()
{
    unk_08 = 1;
    unk_18 = 0;
    unk_00 = 0;
    unk_04 = 30.0f;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
}

// match: ?sub_184F00@type_4E73F0@@QAEXXZ @ 0x00184F00
void type_4E73F0::sub_184F00()
{
    type_42A598 *var_4;

    var_4 = dword_42A598;
    while (var_4->unk_00 != -1)
    {
        var_4->unk_20 = 0;
        var_4->unk_24 = 0;
        var_4->unk_28 = 0;
        var_4->unk_2C = 0;
        var_4->unk_30 = 0;
        var_4->unk_44 = 0;
        var_4->unk_40 = 0;
        var_4++;
    }
    unk_08 = 0;
    unk_0C = 0;
}

// match: ?sub_184F90@type_4E73F0@@QAEXXZ @ 0x00184F90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its step: closes the timers still open, then for each shown one (or all,
// with the text or the highest four) its time as a share of 180 of a frame
// at its rate, its most, sum and count and this sample; a reset clears it.
void type_4E73F0::sub_184F90()
{
    RwReal var_1C;
    RwInt32 var_18;
    RwReal var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    type_42A598 *bp_8;
    RwInt32 bp_4;

    if (unk_08)
        sub_184F00();
    else
    {
        bp_4 = 0;
        bp_8 = dword_42A598;
        while (bp_8->unk_00 != -1)
        {
            while (bp_8->unk_44 > 0)
            {
                if (dword_42A598[bp_4].unk_44 > 0)
                {
                    dword_42A598[bp_4].unk_20 += RWS::Time::GetTime();
                    dword_42A598[bp_4].unk_44--;
                }
            }
            bp_8->unk_44 = 0;
            if (bp_8->unk_38)
            {
                bp_8->unk_24 = 0;
                bp_8->unk_28 = 0;
                bp_8->unk_2C = 0;
                bp_8->unk_30 = 0;
                bp_8->unk_38 = 0;
                bp_8->unk_44 = 0;
            }
            else if (bp_8->unk_40 || unk_0C || unk_00)
            {
                var_14 = 1000.0f / unk_04;
                lv_10 = bp_8->unk_20;
                var_C = lv_10;
                if (bp_4 == 0x24 && var_C >= 0x10)
                    var_18 = 0;
                if (lv_10)
                    bp_8->unk_20 = (RwInt32)((var_1C = lv_10 / var_14) * 180.0f);
                else
                    bp_8->unk_20 = 0;
                bp_8->unk_24 = bp_8->unk_20;
                bp_8->unk_28 = (RwDouble)bp_8->unk_20 > bp_8->unk_28 ? (RwReal)bp_8->unk_20 : (RwReal)(RwDouble)bp_8->unk_28;
                bp_8->unk_2C = bp_8->unk_20 + bp_8->unk_2C;
                bp_8->unk_30++;
                unk_1C[bp_4][unk_18] = (RwReal)bp_8->unk_20;
            }
            bp_8->unk_20 = 0;
            bp_8++;
            bp_4++;
        }
        unk_18 = (unk_18 + 1) % 95;
        if (unk_0C)
            sub_1859A0(4);
    }
}

// match: ?sub_1851C0@type_4E73F0@@QAEXPAURwCamera@@@Z @ 0x001851C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its draw: the text when shown, the graphs when any is.
void type_4E73F0::sub_1851C0(RwCamera *arg_0)
{
    RwInt32 var_8;
    type_42A598 *l4;

    if (unk_00)
        sub_185220();
    var_8 = 0;
    l4 = dword_42A598;
    while (l4->unk_00 != -1)
    {
        var_8 |= l4->unk_40;
        l4++;
    }
    if (var_8)
        sub_185390(arg_0);
}

// match: ?sub_185220@type_4E73F0@@QAEXXZ @ 0x00185220
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The text: each render timer's name, its last frame's and its most time
// as a percentage of a frame, a line of 14 each from (360, 30).
void type_4E73F0::sub_185220()
{
    RwReal var_9C;
    RwReal s98;
    RwInt32 var94;
    RwInt32 var_90;
    RwInt32 l8C;
    RwChar var_88[0x80];
    type_42A598 *l4;

    var_90 = 14;
    var94 = 360;
    l8C = 30;
    l4 = dword_42A598;
    while (l4->unk_00 != -1)
    {
        sprintf(var_88, "%s", l4->unk_04);
        unk_4E73A8.sub_184C50(var_88, var94, l8C);
        s98 = l4->unk_24 / 180.0f * 100.0f;
        var_9C = l4->unk_28 / 180.0f * 100.0f;
        sprintf(var_88, "%3.1f", s98);
        unk_4E73A8.sub_184C50(var_88, var94 + 170, l8C);
        sprintf(var_88, "%3.1f", var_9C);
        unk_4E73A8.sub_184C50(var_88, var94 + 215, l8C);
        l8C += var_90;
        l4++;
    }
}

// match: ?sub_185390@type_4E73F0@@QAEXPAURwCamera@@@Z @ 0x00185390
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The graphs (their backdrop made once, sub_185B50): a white box, each
// shown timer's last 94 samples in its colour, its name and last share by
// its line, and the graphs' frame rate.
void type_4E73F0::sub_185390(RwCamera *arg_0)
{
    RwInt32 var_440;
    RwV2d *var_43C;
    RwRGBA x438;
    RwInt32 fp_434;
    RwRGBA lv_430;
    RwReal p42C;
    RwReal local_428;
    RwReal fp_424;
    RwChar stk_420[0x100];
    RwReal l318;
    RwReal fp_314;
    RwInt32 local_310;
    type_42A598 *q30C;
    RwReal z308;
    RwReal var304;
    RwV2d lv_300[0x5F];
    RwInt32 l4;

    l4 = Height;
    if (!unk_10)
    {
        sub_185B50();
        unk_10 = 1;
    }
    local_428 = 20.0f;
    fp_314 = 120.0f;
    z308 = 210.0f;
    var304 = fp_314 + 180.0f;
    lv_430.red = 255;
    lv_430.green = 255;
    lv_430.blue = 255;
    lv_430.alpha = 255;
    lv_300[0].x = local_428;
    lv_300[0].y = fp_314;
    lv_300[1].x = z308;
    lv_300[1].y = fp_314;
    lv_300[2].x = z308;
    lv_300[2].y = var304;
    lv_300[3].x = local_428;
    lv_300[3].y = var304;
    sub_185820(arg_0, lv_300, 4, 1, &lv_430, 0);
    q30C = dword_42A598;
    local_310 = 0;
    while (q30C->unk_00 != -1)
    {
        if (q30C->unk_40)
        {
            var_43C = lv_300;
            for (var_440 = 0; var_440 < 0x5E; var_440++)
            {
                var_43C->x = var_440 * 2 + local_428;
                var_43C->y = var304 - (unk_1C[local_310][unk_18]);
                unk_18 = (unk_18 + 1) % 95;
                var_43C++;
            }
            fp_434 = q30C->unk_3C;
            x438.red = fp_434 & 0xFF;
            x438.green = (fp_434 >> 8) & 0xFF;
            x438.blue = (fp_434 >> 16) & 0xFF;
            x438.alpha = 255;
            sub_185820(arg_0, lv_300, 0x5E, 0, &x438, 0);
            unk_18 = (unk_18 + 1) % 95;
        }
        q30C++;
        local_310++;
    }
    q30C = dword_42A598;
    while (q30C->unk_00 != -1)
    {
        if (q30C->unk_40)
        {
            sprintf(stk_420, "%s", q30C->unk_04);
            p42C = 212.0f;
            fp_424 = (RwUInt32)Height - var304;
            unk_4E73A8.sub_184C50(stk_420, (RwInt32)p42C, (RwInt32)(fp_424 = q30C->unk_24 + fp_424));
            sprintf(stk_420, "%3.1f %%", l318 = q30C->unk_24 / 180.0f * 100.0f);
            p42C = q30C->unk_48 + p42C;
            unk_4E73A8.sub_184C50(stk_420, (RwInt32)p42C, (RwInt32)fp_424);
        }
        q30C++;
    }
    p42C = 20.0f;
    fp_424 = (fp_424 = (RwUInt32)Height - var304) - 14.0f;
    sprintf(stk_420, "FPS: %2.1f", unk_04);
    unk_4E73A8.sub_184C50(stk_420, (RwInt32)p42C, (RwInt32)fp_424);
}

// match: ?sub_185820@type_4E73F0@@QAEXPAURwCamera@@PAURwV2d@@HHPAURwRGBA@@H@Z @ 0x00185820
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4E73F0::sub_185820(RwCamera *arg_0, RwV2d *arg_4, RwInt32 arg_8, RwInt32 arg_C, RwRGBA *arg_10,
                             RwInt32 arg_14)
{
    RwInt32 var_1790;
    RwReal loc178C;
    RwUInt16 frm_1788[0xCA];
    RwIm2DVertex *ebp_15E8;
    RwInt32 ebp_15E4;
    RwIm2DVertex var15E0[200];

    loc178C = 1.0f / (arg_0->nearPlane);
    ebp_15E8 = var15E0;
    for (var_1790 = 0; var_1790 < arg_8; var_1790++)
    {
        RwIm2DVertexSetScreenX(ebp_15E8, arg_4->x);
        RwIm2DVertexSetScreenY(ebp_15E8, arg_4->y);
        RwIm2DVertexSetScreenZ(ebp_15E8, RwIm2DGetNearScreenZ());
        RwIm2DVertexSetRecipCameraZ(ebp_15E8, loc178C);
        RwIm2DVertexSetIntRGBA(ebp_15E8, arg_10->red, arg_10->green, arg_10->blue, arg_10->alpha);
        frm_1788[var_1790] = (RwUInt16)var_1790;
        ebp_15E8++;
        arg_4++;
        if (arg_14)
            arg_10++;
    }
    ebp_15E4 = arg_8;
    if (arg_C)
    {
        frm_1788[arg_8] = 0;
        ebp_15E4++;
    }
    RwIm2DRenderIndexedPrimitive(rwPRIMTYPEPOLYLINE, var15E0, arg_8, frm_1788, ebp_15E4);
}

// match: ?sub_1859A0@type_4E73F0@@QAEXH@Z @ 0x001859A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Shows the graphs of the arg_0 timers with the most time last frame
// (an insertion into a list of indices), hiding the rest.
void type_4E73F0::sub_1859A0(RwInt32 arg_0)
{
    RwInt32 var_E0;
    RwInt32 var_DC;
    RwInt32 local_D8;
    RwInt32 local_D4;
    RwInt32 local_D0;
    type_42A598 *var_CC;
    RwInt32 var_C8[0x31];

    for (local_D4 = 0; local_D4 < arg_0; local_D4++)
        var_C8[local_D4] = -1;
    for (local_D4 = 0; local_D4 < 0x31; local_D4++)
    {
        local_D8 = local_D4;
        for (local_D0 = 0; local_D0 < arg_0; local_D0++)
        {
            var_DC = var_C8[local_D0];
            if (var_DC == -1)
            {
                var_C8[local_D0] = local_D8;
                break;
            }
            if (dword_42A598[local_D8].unk_24 > dword_42A598[var_DC].unk_24)
            {
                var_C8[local_D0] = local_D8;
                local_D8 = var_DC;
            }
        }
    }
    var_CC = dword_42A598;
    while (var_CC->unk_00 != -1)
    {
        var_CC->unk_40 = 0;
        var_CC++;
    }
    for (var_E0 = 0; var_E0 < arg_0; var_E0++)
    {
        local_D0 = var_C8[var_E0];
        dword_42A598[local_D0].unk_40 = 1;
    }
}

// match: ?sub_185B50@type_4E73F0@@QAEXXZ @ 0x00185B50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Each timer's label offset: the width of its name (trailing spaces after
// the fourth character dropped) in the menu's font, plus 25.
void type_4E73F0::sub_185B50()
{
    RwChar var_98[0x80];
    RwReal local_10;
    RwInt32 var_C;
    RwInt32 bp_8;
    type_42A598 *bp_4;

    bp_4 = dword_42A598;
    while (bp_4->unk_00 != -1)
    {
        bp_8 = 4;
        var_C = strlen(bp_4->unk_04);
        var_C--;
        while (var_C > bp_8 && bp_4->unk_04[var_C] == ' ')
            var_C--;
        strcpy(var_98, bp_4->unk_04);
        var_98[var_C] = 0;
        bp_4->unk_48 = (RwInt32)((local_10 = unk_4E73A8.unk_04->sub_DA7B0(var_98, 0)) + 25.0f);
        bp_4++;
    }
}
