/*
 * The help messages (unit_17C3E0): a list of up to 32 messages
 * (dword_4E6F38) keyed by their text objects, the first shown (dword_4E6F28)
 * in the HUD's font (dword_4E6F30) until it is killed and fades out. The
 * script shows, kills and clears them (sub_17C500, sub_17C640,
 * sub_17C6C0, game/functions.h); the game loop sets the list up and shuts
 * it down (sub_17C4C0, sub_17C4E0); the shell updates and draws it
 * (game/textmanager.h).
 */
#ifndef GAME_HELPMESSAGES_H
#define GAME_HELPMESSAGES_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_3DF8D8.h"
#include "types/type_DA580.h"

// A message (24 bytes).
struct type_4E6F38
{
    type_3DF8D8_04 unk_00;      // its text object's key
    RwReal unk_08;              // how long it has been fading
    RwReal unk_0C;              // its opacity
    RwInt32 unk_10;             // killed: it fades out
    type_4E6F38 *unk_14;        // the next

    // Clears it (opaque, unlinked).
    void sub_17C3E0();
};
extern type_4E6F38 dword_4E6F38[32];
extern type_4E6F38 *dword_4E6F28;  // the first, shown
extern RwInt32 dword_4E6F2C;        // how many are live
extern type_DA580 *dword_4E6F30;    // the HUD's font
extern RwInt32 dword_4E6F34;        // set up

// Its place and size (fractions of the screen), colour, and its fade
// (.data): the fade's length and the time before it starts.
#ifdef CODFH_PLAIN
extern RwRGBA &dword_4B8F64;
#else
extern RwRGBA dword_4B8F64;
#endif
#ifdef CODFH_PLAIN
extern RwV2d &dword_4B8F68;
#else
extern RwV2d dword_4B8F68;
#endif
#ifdef CODFH_PLAIN
extern RwV3d &dword_4B8F70;
#else
extern RwV3d dword_4B8F70;
#endif
#ifdef CODFH_PLAIN
extern RwReal &dword_4B8F80;
#else
extern RwReal dword_4B8F80;
#endif
#ifdef CODFH_PLAIN
extern RwReal &dword_4B8F84;
#else
extern RwReal dword_4B8F84;
#endif

#endif
