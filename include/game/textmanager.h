/*
 * The text manager ("textmanager::console", sub_EAF30): the on-screen
 * messages over the HUD, their fonts and its console, as the shell manager
 * (types/type_4B8EF0.h) drives it. Only what the shell calls is declared.
 */
#ifndef GAME_TEXTMANAGER_H
#define GAME_TEXTMANAGER_H

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "types/alfasched.h"
#include "types/type_DA580.h"

// A console message (0x40-byte elements of the pool dword_4B92B0): its kind
// (0 standard, 1 high level, 2 low level), its time left in ms, its colour,
// whether it is fully typed out, whether typing it plays a sound, and its
// text. Named for its reset (sub_EB0A0).
struct type_EB0A0
{
    RwInt32 unk_00;
    RwReal unk_04;
    RwRGBA *unk_08;
    bool unk_0C;
    bool unk_0D;
    RwChar unk_0E[0x30];
    RwUInt8 unk_3E[0x2];
};
typedef RwChar type_EB0A0_size_check[sizeof(type_EB0A0) == 0x40 ? 1 : -1];

// The text manager's state: whether the queue is typing (byte_4B9220), the
// font and whether it owns it (dword_4B9228, byte_4B92AD), the characters
// typed of the queue's head (dword_4B922C), the pen (unk_4B9230), the typing
// interval and its timer in ms (dword_4B9238, dword_4B929C), the queue
// (dword_4B923C, its head dword_4B92A0 and count dword_4B92A8), the lines'
// origin (unk_4B9264), the shown lines (dword_4B926C) and the line being
// typed (dword_4B9298), the console font (dword_4B9294), whether it is on
// (byte_4B92AC), whether the console greets (byte_4B92AE) and its pool.
extern bool byte_4B9220;
extern RwInt32 dword_4B9224;
extern type_DA580 *dword_4B9228;
extern RwInt32 dword_4B922C;
extern RwV2d unk_4B9230;
extern RwReal dword_4B9238;
extern type_EB0A0 *dword_4B923C[8];
extern RwV2d unk_4B9264;
extern type_EB0A0 *dword_4B926C[8];
extern type_DA580 *dword_4B9294;
extern RwInt32 dword_4B9298;
extern RwReal dword_4B929C;
extern RwInt32 dword_4B92A0;
extern RwInt32 dword_4B92A4;
extern RwInt32 dword_4B92A8;
extern bool byte_4B92AC;
extern bool byte_4B92AD;
extern bool byte_4B92AE;
extern type_16C2A0 dword_4B92B0;
// The front end's settings for it: the lines' origin (unk_4B8EF4), the
// kinds' colours (unk_4B8EFC, unk_4B8F00, unk_4B8F04) and the typing
// interval in seconds (flt_4B8F08).
#ifdef CODFH_PLAIN
extern RwV2d &unk_4B8EF4;
#else
extern RwV2d unk_4B8EF4;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &unk_4B8EFC;
#else
extern RwRGBA unk_4B8EFC;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &unk_4B8F00;
#else
extern RwRGBA unk_4B8F00;
#endif
#ifdef CODFH_PLAIN
extern RwRGBA &unk_4B8F04;
#else
extern RwRGBA unk_4B8F04;
#endif
#ifdef CODFH_PLAIN
extern RwReal &flt_4B8F08;
#else
extern RwReal flt_4B8F08;
#endif
// Whether the console shows (.data, 1).
extern RwInt32 dword_42926C;
// The shell's fonts' path (the database's name).
#ifdef CODFH_PLAIN
extern RwChar (&path)[132];
#else
extern RwChar path[];
#endif

// Its set-up (sub_EAA60, from the shell's), its update (sub_EAAE0, with the
// frame's time), its restart (sub_EAB00), its shutdown (sub_EAB10), its
// font's load (sub_EAC60), its render (sub_EAF10, on the camera arg_0) and
// its console's set-up (sub_EAF30).
bool sub_EAA60();
void sub_EAAE0(RwReal arg_0);
void sub_EAB00();
void sub_EAB10();
void sub_EAC60();
void sub_EAF10(RwCamera *arg_0);
void sub_EAF30();
// Draws the text arg_0 at *arg_4 on the camera arg_0; the rest only known
// by width.
void sub_EBAE0(RwCamera *arg_0, const RwChar *arg_4, RwV2d *arg_8, type_DA580 *arg_C, RwReal arg_10,
               RwReal arg_14, RwReal arg_18);
// Shows the message arg_0 in the HUD's item for the kind arg_4; arg_8 is
// unused (every caller passes -1, its default).
void sub_EAB80(const RwChar *arg_0, RwInt32 arg_4, RwReal arg_8 = -1.0f);
// The internals: reset (sub_EB030), restart (sub_EB0D0), shutdown
// (sub_EB190), update (sub_EB2D0), render (sub_EB770), a message's reset
// (sub_EB0A0, sub_EBE20), queueing (sub_EBCD0: false when full), dequeueing
// (sub_EBD20), a message's kind's time and colour (sub_EBDB0) and a shown
// line's removal (sub_EBE40).
void sub_EB030();
void sub_EB0D0();
void sub_EB190();
void sub_EB2D0(RwReal arg_0);
void sub_EB770(RwCamera *arg_0);
void sub_EB0A0(type_EB0A0 *arg_0);
bool sub_EBCD0(type_EB0A0 *arg_0);
void sub_EBD20(RwInt32 arg_0);
void sub_EBDB0(type_EB0A0 *arg_0);
void sub_EBE20(type_EB0A0 *arg_0);
void sub_EBE40(RwInt32 arg_0);
// Whether another overlay has the screen (the text manager draws nothing
// then): the music playing, whose key the inventory's health pack compares
// (type_10F710_21B4::sub_115690).
struct type_3DF8D8_04 *sub_17C630();

// What the shell calls after the text manager's: the set-up (sub_17C4A0),
// the update (sub_17C750) and the render (sub_17C830) of the game's other
// overlay; only the widths are known.
void sub_17C4A0();
void sub_17C750(RwReal arg_0);
void sub_17C830(RwCamera *arg_0);
// Shows the camera arg_0's raster (after a loading screen's update).
void sub_126750(RwCamera *arg_0);

#endif
