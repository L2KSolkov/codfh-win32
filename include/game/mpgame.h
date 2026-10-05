/*
 * The multiplayer game's settings and names (unit_1A3BE0): the session's
 * settings (unk_4F61F8: the port, 2000 by default, and whether this machine
 * hosts), and the game types' names (1 deathmatch, 2 team deathmatch, 4
 * capture the flag, 8 search and destroy, 16 supremacy, 32 any).
 */
#ifndef GAME_MPGAME_H
#define GAME_MPGAME_H

#include "rw/ostypes.h"

// Named after its address; only the widths are known.
struct type_4F61F8
{
    RwUInt32 unk_00[0x40];
    RwUInt16 unk_100;           // the port (2000)
    RwInt32 unk_104;            // set when this machine hosts (read as
                                // dword_4F62FC by the multiplayer manager)
    RwInt32 unk_108;            // 4 after the manager's set-up

    type_4F61F8();
};
extern type_4F61F8 unk_4F61F8;
// Whether this machine hosts: an inline with no address and so no database
// name, named for what it reads. Evidence: as show_message (functions.h),
// the kill messages' frames (sub_1ACBA0, sub_1AD750).
inline RwInt32 hosting()
{
    return unk_4F61F8.unk_104;
}

// The game type arg_0's name ("Deathmatch") and short name ("DM"); "" for
// none.
const RwChar *sub_1A3C10(RwInt32 arg_0);
const RwChar *sub_1A3CB0(RwInt32 arg_0);
// The game type arg_0's name again (sub_1A3C10's result; the game type
// selector's labels, sub_210180, are keyed by it).
const RwChar *sub_1C4E60(RwInt32 arg_0);

#endif
