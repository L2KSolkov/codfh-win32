/*
 * The network messages' base (type_3DA44C) and the multiplayer manager's two
 * score messages (its +4 and +0xD0, unk_4F7EBC and unk_4F7F88): their own
 * header, with no includes of the game's, so the manager's layout
 * (game/gameloop.h) can hold them and the HUD (types/type_DC400.h) use them.
 * The other messages are in game/netmsg.h.
 */
#ifndef GAME_NETSCORE_H
#define GAME_NETSCORE_H

#include <vector>

#include "rw/ostypes.h"

struct type_1F8560;
struct type_4F8184_site;
struct type_4F823C_flag;

// A message: written (vf_000) and read (vf_004) through the bit stream,
// and its id (vf_008). The base's methods are all pure.
struct type_3DA44C
{
    virtual void vf_000(type_1F8560 *arg_0) = 0;
    virtual void vf_004(type_1F8560 *arg_0) = 0;
    virtual RwInt32 vf_008() = 0;
};

// Two messages whose constructors and destructors are out of line
// (sub_1B2A90 and sub_1B2AD0; sub_1B37C0 and sub_1B3800), sharing one read
// and write (sub_1B32E0, sub_1B3B20) and differing in their ids: the
// multiplayer manager's score messages (its +4 and +0xD0, unk_4F7EB8.unk_04 and
// unk_4F7EB8.unk_D0; game/netscore.h). The manager's destructor (sub_1A8DA0) calls
// their destructors.
struct type_3E1E48 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E1E3C : type_3E1E48
{
    RwInt32 unk_04[16];         // each player's score
    RwInt32 unk_44[16];         // kills
    RwInt32 unk_84[16];         // deaths
    RwInt32 unk_C4[2];          // the two teams' captures

    type_3E1E3C();
    ~type_3E1E3C();
    // Clears it (shared with type_3E1FC4 by /OPT:ICF).
    void sub_1B3820();
    // Written (sub_1B3B20) and read (sub_1B32E0) with the full game state.
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
    // Copies every field but the vtable (sub_1AE340; unk_4F7EB8.unk_D0's is the
    // same code, /OPT:ICF).
    type_3E1E3C &operator=(const type_3E1E3C &arg_0);
    // Of RwUInt32, not RwInt32: its vector's _Insert_n (sub_1B3DC0) is a
    // copy of std::vector<RwInt32>'s (sub_1716E0), kept apart by its own
    // name.
    void sub_1B3480(std::vector<RwUInt32> &arg_0);
    // Takes site arg_0's change from arg_4 to arg_8 (the sites' sync,
    // sub_1A7D80).
    void sub_1B3190(RwInt32 arg_0, type_4F8184_site *arg_4, type_4F8184_site *arg_8);
    // Drops player arg_0 (the multiplayer manager's sub_1AC990); only the
    // width is known.
    void sub_1B3270(RwInt32 arg_0);
    // Counts a kill of arg_4 by arg_0 (the manager's leave passes the
    // leaving player as both, sub_1AC790); only the widths are known.
    void sub_1B2D00(RwInt32 arg_0, RwInt32 arg_4, bool arg_8);
    // Takes flag arg_0's change from arg_4 to arg_8, and a capture by team
    // arg_0 (the flag part's sub_1B1B00); only the widths are known.
    void sub_1B3030(RwInt32 arg_0, struct type_4F823C_flag *arg_4, struct type_4F823C_flag *arg_8);
    // Player arg_0's rank in team arg_4 (the players in it scoring more, or
    // as much with a higher number); whether every other player in the game
    // (every one of team arg_0) has its network player's unk_130 set.
    RwInt32 sub_1B2AF0(RwUInt32 arg_0, RwInt32 arg_4);
    // Player arg_0's score, kills and deaths (the three sixteen-entry
    // arrays); team arg_0's (2 or 4) captures; sends the scores to the
    // peers when hosting.
    RwInt32 sub_1B3360(RwInt32 arg_0);
    RwInt32 sub_1B3380(RwInt32 arg_0);
    RwInt32 sub_1B33A0(RwInt32 arg_0);
    RwInt32 sub_1B33C0(RwInt32 arg_0);
    void sub_1B3400();
    RwInt32 sub_1B2BC0(RwInt32 arg_0);
    RwInt32 sub_1B2C60(RwInt32 arg_0);
    void sub_1B2FD0(RwInt32 arg_0);
};

struct type_3E1FD0 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E1FC4 : type_3E1FD0
{
    RwInt32 unk_04[16];         // each player's score
    RwInt32 unk_44[16];         // kills
    RwInt32 unk_84[16];         // deaths
    RwInt32 unk_C4[2];          // the two teams' captures

    type_3E1FC4();
    ~type_3E1FC4();
    // Resets it (the multiplayer manager's reset, sub_1A9440).
    void sub_1B3820();
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
    // The same code as type_3E1E3C's (sub_1AE340, /OPT:ICF).
    type_3E1FC4 &operator=(const type_3E1FC4 &arg_0);
    // Drops player arg_0 (the scores' sub_1B3270), and sends it to the peers
    // when hosting ("(SERVER) Game score updated").
    void sub_1B3890(RwInt32 arg_0);
    void sub_1B3BA0();
    // Adds the round's scores (unk_4F7EB8.unk_04) into it, and a win to the team
    // the round goes to; sent on (sub_1B3BA0). Only on a client.
    void sub_1B38E0();
    RwInt32 sub_1B3380(RwInt32 arg_0);
};


#endif
