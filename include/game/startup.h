/*
 * The game's start-up (unit_0D99F0): RenderWare's start and stop
 * (sub_D99F0, sub_D9BC0) and the game's outer loop (sub_D9C00), which runs
 * the game loop (sub_D99B0) between the front end's screens.
 */
#ifndef GAME_STARTUP_H
#define GAME_STARTUP_H

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "game/gameloop.h"
#include "rws/camerahelper.h"
#include "game/cheats.h"

// Direct3D's push buffer size (the XDK's d3d8.h, declared here where that
// header is not included).
#ifndef _D3D8_H_
extern "C" RwInt32 __stdcall Direct3D_SetPushBufferSize(RwUInt32 PushBufferSize,
                                                       RwUInt32 KickOffSize);
#endif

#include "rws/startup.h"
#include "game/debugtext.h"


// An empty test that /OPT:ICF shares (0 here: the start-up then uses its
// own memory functions, off_4292A0).
RwMemoryFunctions *sub_170ED0();
extern RwMemoryFunctions off_4292A0;
extern RwReal dword_4B8970;
extern void *dword_4B87FC;
extern RwUInt32 dword_4F4628;
RwInt32 sub_19CD50();
// The systems started after RenderWare (unit_1A26F0): the log callback
// the library prints through (sub_1D5DB0 stores it in dword_4FECF8), and
// the log (sub_1B18D0's dword_4F84B8: fifty lines to a channel,
// sub_1B1780 adding line arg_0 to channel arg_4). Only the widths are
// known.
void sub_1A2910();
void sub_1A2A60(RwChar *arg_0);
void sub_1D5DB0(void (*arg_0)(const RwChar *arg_0));
// The log's 0x58-byte entries at +0x2F18 (sixteen) and +0x3498; only the
// widths are known.
struct type_4F84B8_2F18
{
    RwUInt32 unk_00[10];        // the last counts
    RwReal unk_28[10];          // their running rates
    RwUInt32 unk_50;            // when they were taken
    RwInt32 unk_54;             // set: the rates have started
};
// The log (unit_1AFF40, built at unk_4F84C0 by an initializer the database
// misses, 0x30C220): three channels of fifty 80-character lines in rings,
// each with its first line (unk_08), its count (unk_14) and the first line
// shown (unk_20); unk_00 picks how many lines show (dword_3E1A60).
struct type_4F84B8
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwUInt32 unk_08[3];
    RwUInt32 unk_14[3];
    RwUInt32 unk_20[3];
    RwChar unk_2C[3][50][80];
    RwUInt8 unk_2F0C[0xC];
    type_4F84B8_2F18 unk_2F18[16];
    type_4F84B8_2F18 unk_3498;
    bool unk_34F0;              // shown (toggled by the multiplayer manager's sub_1AF250)
    RwUInt8 unk_34F1;
    // Shows the line arg_0 at (arg_4, arg_8) while the display is on and
    // not paused, outside game type 2: an inline with no address, named
    // for what it does. Evidence: the debug display (sub_1B00F0) tests the
    // three flags before each of its three optional lines.
    void show(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8)
    {
        if (unk_34F0 && !unk_34F1 && unk_00 != 2)
            sub_16BB00(arg_0, arg_4, arg_8);
    }
    struct type_4F8054 *unk_34F4; // the network game (the manager's set-up)
    RwInt32 unk_34F8;
    RwInt32 unk_34FC;
    RwInt32 unk_3500;
    RwInt32 unk_3504;

    type_4F84B8();
    ~type_4F84B8();
    // Set by the multiplayer manager (sub_1A9580, sub_1A9960).
    void sub_1B0090(struct type_4F8054 *arg_0);
    void sub_1B00B0();
    void sub_1B1780(RwChar *arg_0, RwInt32 arg_4);
    // Drawn by the render's wrapper (sub_1A2D00).
    void sub_1B00F0();
};
type_4F84B8 *sub_1B18D0();
extern type_4F84B8 *dword_4F84B8;
struct type_1CCA10;
// The late service (game/liveservice.h, which units that call it include),
// built on first use by sub_227560.
struct type_5051E8;
type_5051E8 *sub_227560();
void sub_1A2D20();
RwInt32 sub_82F50();
RwInt32 sub_83100();
void sub_831D0();

// The outer loop's state: the cheat flags (dword_4B8888, at dword_4B8884 +
// 0x2C when that is set, else at dword_4B888C), the front end's exits
// (byte_4F61F0, byte_4F61F1) and its run flag (dword_4FBAA8).
void sub_D9C00();
extern RwUInt8 *dword_4B8884;
extern RwUInt8 dword_4B888C[];
extern bool byte_4F61F0;
extern bool byte_4F61F1;
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4FBAA8;
#else
extern RwInt32 dword_4FBAA8;
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4FBA9C;
#else
extern RwInt32 dword_4FBA9C;
#endif
void sub_DA290();
void sub_1B6F90();

#endif
