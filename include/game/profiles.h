/*
 * The profiles' save files (unit_1A16D0): four slots (dword_4F5DC0), each
 * saved as "DANTE%d.dat" in its own save game named "Profile <n>: <name>"
 * on the hard disk ("u:\"), behind a 0x18-byte header (its size and its
 * signature), with "saveimage.xbx" copied in as the save's image. Also the
 * damaged-profile message box.
 */
#ifndef GAME_PROFILES_H
#define GAME_PROFILES_H

#include <xtl.h>

#include "rw/ostypes.h"
#include "types/type_DA0A0.h"
#include "game/waitscreen.h"
#include "game/gameloop.h"

// Sets the save paths up and clears the slots when it is built; the global
// (unk_4F6170) has no members. Named after its address.
struct type_4F6170
{
    type_4F6170();
};

// A profile file's header: the record's size and its signature (an
// XCALCSIG_SIGNATURE, kept as dwords: a byte array would give the frame a
// buffer of its own).
struct type_1A1820
{
    DWORD unk_00;
    DWORD unk_04[5];
};

extern RwChar byte_4F6110[4];           // the drive, "u:\"
extern HANDLE dword_4F6114;             // the save games' search
extern RwChar byte_4F6118[0x40];        // the image's source, "d:\saveimage.xbx"
extern RwChar byte_4F5A38[0x40];        // and its name in the save, "saveimage.xbx"
extern XGAME_FIND_DATA unk_4F5A78;      // the save game found
extern RwInt32 dword_4F6168;            // the damaged profile (sub_1A2580)
// "Profile" and the damaged-profile text, by language (sub_1A2580).
extern const RwChar *off_42C82C[7];
extern const RwChar *off_42C810[7];
// The box's accept button: set when it is to be checked afresh, and while
// it is still held from before (sub_1A24D0).
extern RwInt32 dword_4F2B74;
extern RwInt32 dword_4F3078;

// Clears the slots.
void sub_1A1720();
// Finds the first save game (ten tries while the drive is busy); with
// arg_0 the search is closed again.
RwInt32 sub_1A1790(RwInt32 arg_0);
// The signature of arg_4 bytes at arg_0 into arg_8.
bool sub_1A2000(void *arg_0, DWORD arg_4, XCALCSIG_SIGNATURE *arg_8);
// A save game's name narrowed into arg_4 (returned); the wide copy of arg_0
// into arg_4.
RwChar *sub_1A2060(WCHAR *arg_0, RwChar *arg_4);
void sub_1A20C0(const RwChar *arg_0, WCHAR *arg_4);
// One wide character narrowed.
RwChar sub_1A2110(WCHAR arg_0);
// The damaged-profile message box: its update and its opener (in the
// messages' table, off_42B518, as message 0x2D).
void sub_1A24D0(type_4EBE00 *arg_0, RwInt32 arg_4);
void sub_1A2580(type_4EBE00 *arg_0, RwInt32 arg_4);
// The slots copied into and out of the launch data (type_4F45F8, as void).
void sub_1A2650(void *arg_0);
void sub_1A2680(void *arg_0);

#endif
