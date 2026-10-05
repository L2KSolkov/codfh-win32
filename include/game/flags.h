/*
 * The multiplayer game's flags (dword_4F6A7C, unit_1A4920): capture the
 * flag's two flags, each with its state (1 at home), its base trigger (the
 * AnimatedBGTrigger's commands 41 and 42 register it while the game type is
 * 4) and home position, and its flag entity; and whether the two homes are
 * swapped.
 */
#ifndef GAME_FLAGS_H
#define GAME_FLAGS_H

#include "rw/ostypes.h"
#include "rw/batypes.h"

struct type_3D3548;

struct type_4F6A7C_flag
{
    RwInt32 unk_00;             // its state (1 at home, 2 dropped)
    class Trigger *unk_04;      // its base
    type_3D3548 *unk_08;        // its flag entity
    RwV3d unk_0C;               // its home (the base's position)
    RwUInt8 unk_18;

    // Whether the point arg_0 is at the flag (within 80, 200 high) while
    // it is away from home.
    RwInt32 sub_1A5DA0(RwV3d *arg_0);
    // An inline accessor for unk_00, with no address and so no database
    // name; named for its field. Evidence: the network player's flag
    // checks (sub_1B81D0, sub_1B82F0) read it through a slot of their own.
    RwInt32 get_unk_00()
    {
        RwInt32 r = unk_00;
        return r;
    }
};

struct type_4F6A7C
{
    type_4F6A7C_flag unk_00[2];
    RwUInt8 unk_38;             // set while the homes are swapped

    type_4F6A7C();
    // The flag of the base at the trigger arg_0 (the other one while the
    // homes are swapped), or -1.
    RwInt32 sub_1A4920(class Trigger *arg_0);
    // Clears the flag entities' bits 4 and 5 where bit 1 is set.
    void sub_1A4980();
    // Sets flag arg_0's state to arg_4 (player arg_8, at arg_C), telling
    // the manager's flag part first (unk_4F7EB8.unk_384).
    void sub_1A4A20(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10);
    // Swaps the two homes (once), and swaps them back in capture the flag.
    void sub_1A4A90();
    void sub_1A4B00();
    void sub_1A4B40(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwV3d *arg_C, RwInt32 arg_10);
    // Resets the flags: all at home, the entities removed, the bases
    // forgotten; the second keeps the bases and removes the entities only
    // in capture the flag.
    void sub_1A57E0();
    void sub_1A5850();
    // Registers the trigger arg_4 as flag arg_0's base (AnimatedBGTrigger's
    // commands 41 and 42).
    void sub_1A58C0(RwInt32 arg_0, class Trigger *arg_4);
    // Whether the entity arg_4 is at flag arg_0.
    RwInt32 sub_1A5920(RwInt32 arg_0, type_3D3548 *arg_4);
    // The team count for four teams (arg_0) or two.
    RwInt32 sub_1A5950(RwInt32 arg_0);
    // Times out the rendering of the flag entity arg_0 ("FlagRenderTimeOut"):
    // a dropped flag goes home.
    void sub_1A5970(type_3D3548 *arg_0);
    // Sets the flags up for capture the flag: each base's objective, its
    // flag entity (falling at flt_3E1284) at home, pointing at the other
    // base, and the flag's state sent.
    void sub_1A59D0();
    // Puts flag arg_0's entity upright at the point arg_4.
    void sub_1A5C40(RwInt32 arg_0, RwV3d *arg_4);
    // Removes the flag entities.
    void sub_1A5D10();
    // Flag arg_0's entity (0 past the second).
    type_3D3548 *sub_1A5D70(RwInt32 arg_0);
};
extern type_4F6A7C dword_4F6A7C;
// A flag entity's fall rate (-5; .rdata, loaded at run time).
extern const RwReal flt_3E1284;

// A flag as the multiplayer manager's flag part keeps it (0x24 bytes): its
// state, the updates sent, the player who set it (-1 for none), where, the
// round, and a timer (30 on each change).
struct type_4F823C_flag
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    RwV3d unk_0C;
    RwReal unk_18;
    RwInt32 unk_1C;
    RwReal unk_20;
};

// The multiplayer manager's flag part (unk_4F7EB8 + 0x384): the two flags
// and the round. A flag's new state (sub_1B1B00: sent when hosting, else
// kept and sent on).
struct type_4F823C
{
    type_4F823C_flag unk_00[2];
    RwReal unk_48;              // the round's time

    // Empty and out of line: the multiplayer manager's constructor
    // (sub_1A8B20) calls it at sub_6FCD0, where /OPT:ICF folded it with the
    // other empty functions returning this (config/aliases.txt).
    type_4F823C();
    void sub_1B1B00(RwInt32 arg_0, RwInt32 arg_4, RwV3d *arg_8, RwInt32 arg_C, RwInt32 arg_10);
    // A flag's state from a peer (the handler sub_1AEBE0); only the width is
    // known.
    void sub_1B1DE0(struct type_3E0FB4 *arg_0);
    // Its part of the full game state, written and read.
    void sub_1B21A0(struct type_1F8560 *arg_0);
    void sub_1B2290(struct type_1F8560 *arg_0);
    // Drops what player arg_0 carries (the manager's leave, sub_1AC790);
    // only the width is known.
    void sub_1B24E0(RwInt32 arg_0);
    // Resets it (the manager's reset, sub_1A9440).
    void sub_1B1A30();
    // Whether player arg_0 carries a flag; the flag entity player arg_0 (by
    // its player number, or its entity) carries, 0 for none.
    RwInt32 sub_1B2480(RwInt32 arg_0);
    type_3D3548 *sub_1B2610(RwInt32 arg_0);
    type_3D3548 *sub_1B25E0(type_3D3548 *arg_0);
    // Its step by arg_0 frames and its second step (the manager's step):
    // in capture the flag the flag entities shown as carried or not by the
    // local player (vf_1A4), their performance for the key {0, 0xAB, 2}
    // played, and those not carried turned (sub_76960).
    void sub_1B23B0(RwReal arg_0);
    void sub_1B2670();
};
typedef RwChar type_4F823C_size_check[sizeof(type_4F823C) == 0x4C ? 1 : -1];

#endif
