/*
 * The debug text (unit_16BA60): strings queued with their screen positions
 * in a buffer (sub_16BB00) and drawn in one go with RenderWare's Atari
 * charset (sub_16BBA0); and the debug printf (sub_16C220).
 */
#ifndef GAME_DEBUGTEXT_H
#define GAME_DEBUGTEXT_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/badevice.h"
#include "rw/rtcharse.h"

// A queued string: its position, its length and its text (padded to 4).
struct type_16BB00
{
    RwUInt16 unk_00;            // x
    RwUInt16 unk_02;            // y
    RwUInt16 unk_04;            // its length
    RwChar unk_06[1];
};

extern RwInt32 dword_4E2290;    // strings queued
extern RwUInt8 *dword_4E2294;   // the buffer
extern RwUInt8 *dword_4E2298;   // its end
extern RwUInt32 dword_4E229C;   // its size
extern RtCharset *charSet;      // the database's names
extern RwRGBA foreGround;
extern RwRGBA backGround;

// Sets it up with a buffer of arg_0 bytes, and shuts it down.
void sub_16BA60(RwUInt32 arg_0);
void sub_16BAC0();
// Queues the string arg_0 at (arg_4, arg_8); false when the buffer is full.
bool sub_16BB00(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8);
// Draws the queued strings and empties the queue.
void sub_16BBA0();
// Fills arg_0 (room for arg_4 vertices) with the glyphs of *arg_8 from the
// pen (*arg_C, *arg_10); returns the vertices written.
RwInt32 sub_16BE20(RwIm2DVertex *arg_0, RwInt32 arg_4, const RwChar **arg_8, RwInt32 *arg_C, RwInt32 *arg_10);
// The debug printf: formats into a buffer and prints it with a newline.
void sub_16C220(const RwChar *arg_0, ...);

#endif
