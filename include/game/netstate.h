/*
 * A part of the full game state (dword_4F8288), inside the multiplayer
 * manager's flags' part (game/gameloop.h, its +0x3D0): the players' teams
 * and what the manager's handlers pass on. Its own header so the manager's
 * layout can hold it; only the widths are known.
 */
#ifndef GAME_NETSTATE_H
#define GAME_NETSTATE_H

#include "rw/ostypes.h"

struct type_1F8560;
// A player's entry: its team (1 none, 2 blue, 4 red), its state (0 when it
// has to respawn; written with the table) and whether its team was taken.
struct type_4F8288_00
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
};
struct type_4F8288
{
    void sub_1C2970(type_1F8560 *arg_0);
    void sub_1C29D0(type_1F8560 *arg_0);
    // What the multiplayer manager keeps at its +0x2BC (sub_1AFB70); only
    // the width is known.
    RwInt32 sub_1C2440();
    // Takes the team arg_4 of player arg_0 (the respawn request, sub_1AD260);
    // only the widths are known.
    void sub_1C2600(RwInt32 arg_0, RwInt32 arg_4);
    // Player arg_0's team; only the widths are known.
    RwInt32 sub_1C2A90(RwInt32 arg_0);
    // The players in team arg_0 (the game data's team balance, sub_1B5F90);
    // only the width is known.
    RwInt32 sub_1C2500(RwInt32 arg_0);
    // What the respawn handler passes on (sub_1AE250); only the widths are
    // known.
    void sub_1C28F0(RwInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8);
    // Forgets player arg_0 (the manager's leave, sub_1AC790); only the width
    // is known.
    void sub_1C2940(RwInt32 arg_0);
    // Resets it (the manager's reset, sub_1A9440).
    void sub_1C25A0();

    type_4F8288_00 unk_00[16];
};
typedef RwChar type_4F8288_size_check[sizeof(type_4F8288) == 0xC0 ? 1 : -1];
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern type_4F8288 &dword_4F8288;
#else
extern type_4F8288 dword_4F8288;
#endif

// Player arg_4 takes the team arg_8 (and its team is taken): a free inline
// with no address. Evidence: the team change (sub_1C2600) ends with it, and
// its frame holds the leftovers of that one expansion.
inline void set_team(type_4F8288 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    arg_0->unk_00[arg_4].unk_00 = arg_8;
    arg_0->unk_00[arg_4].unk_08 = 1;
}

#endif
