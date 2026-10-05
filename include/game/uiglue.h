/*
 * The front end's link to the network game (src/recovered/unit_1C3D20.cpp;
 * its one trace names it cUIInterface): its globals, the objects it reaches
 * that are not yet matched, and its functions.
 */
#ifndef GAME_UIGLUE_H
#define GAME_UIGLUE_H

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/loc.h"
#include "game/kujuui.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_505188.h"

// This unit's globals: the settings copy the front end edits (its unk_28
// the level), the level list (dword_4FD974, dword_4FD970 entries), the
// lobby's players (names, teams and three scores each), this machine's
// peer, the server name, the screen asked for, the pending message and a
// flag set while the options are applied.
extern type_4FB9E0_08 unk_4FDBB0;
// Inline accessors for the settings copy's fields, with no address; named
// for their fields. Evidence: the host options' read (sub_201890) has no
// room in its frame for the text's inline-destructor leftovers, which the
// compiler only skips once these inlines have spent its budget (member
// accessors leave leftovers of their own).
inline RwInt32 get_4FDBB0_unk_00() { return unk_4FDBB0.unk_00; }
inline RwInt32 get_4FDBB0_unk_08() { return unk_4FDBB0.unk_08; }
inline RwInt32 get_4FDBB0_unk_0C() { return unk_4FDBB0.unk_0C; }
inline RwInt32 get_4FDBB0_unk_10() { return unk_4FDBB0.unk_10; }
inline RwReal get_4FDBB0_unk_14() { return unk_4FDBB0.unk_14; }
inline RwInt32 get_4FDBB0_unk_18() { return unk_4FDBB0.unk_18; }
inline RwInt32 get_4FDBB0_unk_24() { return unk_4FDBB0.unk_24; }
inline RwReal get_4FDBB0_unk_2C() { return unk_4FDBB0.unk_2C; }
// The voice setting the host's start sends (type_4F7EB8::sub_1A9A70; the
// host options set it, sub_200B90).
extern RwInt32 dword_4FDAA4;
// The focus stack the front end installs (sub_1E7CE0).
extern kujuUI::type_1E7CF0 unk_4FDBE4;
extern RwUInt32 dword_4FD970;
extern type_505188 *dword_4FD974;
extern RwInt32 dword_4FD6F0[16];
extern RwInt32 dword_4FD730[16];
extern RwInt32 dword_4FD770[16];
extern RwInt32 dword_4FD7B0[16];
extern RwChar byte_4FD7F0[16][0x18];
extern RwInt32 dword_4FD978;
extern RwUInt8 unk_4FD97C;
extern RwInt32 dword_4FD98C;
extern RwChar byte_4FD990[0x100];
extern bool byte_4FDA90;
extern RwInt32 dword_4FDA94;
extern kujuUI::type_1E3DB0 *dword_4FDA98;
extern RwUInt8 byte_4FDAA8;
extern RwChar byte_4FDAB0[0x100];
// The sound settings the front end resets (sub_1C40F0).
#ifdef CODFH_PLAIN
extern RwInt32 (&dword_44E720)[8];
#else
extern RwInt32 dword_44E720[8];
#endif
extern RwInt32 dword_44E834;
// The objective key "winfo_N_W" (.data) and the letters put into it: the
// game type's ("eurg") and the team's ("mrsh").
extern RwChar byte_42CBBC[];
extern RwChar byte_42CBC8[];
extern RwChar byte_42CBB4[];

// Not yet matched; only the widths are known.
bool sub_215A90();

void sub_1C4720(RwUInt32 arg_0);
RwInt32 sub_1C47A0(RwUInt32 arg_0);
// The side arg_0's round score.
RwInt32 sub_1C47E0(RwInt32 arg_0);
RwInt32 sub_1C4800(RwUInt32 arg_0);
RwInt32 sub_1C4840(RwUInt32 arg_0);
RwInt32 sub_1C4880(RwInt32 arg_0);
type_1DDE20_mask sub_1C48D0();
void sub_1C4A90(const RwChar *arg_0);
bool sub_1C4C00();
bool sub_1C4CB0();
// The front end's unk_4F7EB8.unk_490.sub_1C3CC0(): non-zero while a vote is to be
// confirmed (the pause menu's update, sub_21BA50, keeps it in unk_3E1).
RwInt32 sub_1C4E40();
// The pending message shown once the screen allows (the in-game screens'
// frame passes its time, unused); unk_4F61F8.unk_104 clear (the
// scoreboards then offer the host's options); the pad's event source, made
// on first use and deleted.
void sub_1C40B0(RwReal arg_0);
// The level picked (the settings copy's unk_28: given, sub_1C4BC0, and
// set, sub_1C3D80) and the server's name (set, sub_1C4300, and given,
// sub_1C4320).
RwInt32 sub_1C4BC0();
// Starts the game as the host (over Xbox Live when arg_0 is set).
void startServer(bool arg_0);
void sub_1C3D80(RwInt32 arg_0);
void sub_1C4300(const RwChar *arg_0);
RwChar *sub_1C4320();
// The player's name (dword_4F28F0's unk_183).
RwChar *sub_1C42E0();
bool sub_1C4BE0();
kujuUI::type_1E3DB0 *sub_1C4EA0();
void sub_1C4ED0();
RwInt32 sub_1C4D00();
// The search's name filter (unk_4FD97C; the Live search's start, sub_20CB70).
RwUInt8 *sub_1C4330();
// The last vote's kind and value (unk_4F7EB8.unk_490's unk_3C and unk_40), its votes
// for and against (unk_44, unk_48) and its caller (sub_1C4E00): a vote's
// confirmation's question (sub_221A80) asks them.
RwInt32 sub_1C4D60();
RwInt32 sub_1C4D80();
void sub_1C4DA0(RwUInt32 *arg_0, RwUInt32 *arg_4);
type_1CB670 sub_1C4DD0();
// The weapon class arg_4's text for the team arg_0 ("winfo_N_W"; unit_1C3D20),
// and the grenades it carries (the multiplayer manager's sub_1AF2C0).
type_1CB670 sub_1C43C0(RwInt32 arg_0, RwInt32 arg_4);
RwUInt8 sub_1AF2C0(RwInt32 arg_0);
// The vote's value (unk_4F7EB8.unk_490's unk_04: the game type, level or player
// voted on) and a level's name (sub_19B060 of arg_0 + 1).
RwInt32 sub_1C4D20();
const RwChar *sub_1C4590(RwInt32 arg_0);
void sub_1C5230();
void sub_1C52E0();
RwReal sub_1C45E0();
// The in-game debug menu's actions: the player killed (sub_1C44F0), the
// round reset (sub_1C4520) and its time added to (sub_1C45B0).
void sub_1C44F0();
void sub_1C4520();
void sub_1C45B0(RwReal arg_0);
// The game settings' copy (unk_4FDBB0) refreshed from the game data
// (sub_1C3D20) and sent with the flag arg_0 (sub_1C3D60).
void sub_1C3D20();
void sub_1C3D60(RwInt32 arg_0);
// The team arg_0 joined (sub_1C4380), and the front end's screens left
// (sub_1C4B10).
void sub_1C4380(RwInt32 arg_0);
void sub_1C4B10();
// The players in the session (sub_1C48A0, as a mask), a player's name
// (sub_1C4630) and a player kicked (sub_1C4560).
type_1DDE20_mask sub_1C48A0();
RwChar *sub_1C4630(RwUInt32 arg_0);
void sub_1C4560(RwInt32 arg_0);
// The session's players' count.
RwInt32 sub_1C45F0();
void sub_1C45D0(RwReal arg_0);
void sub_1C46D0();
RwInt32 sub_1C4480(RwInt32 arg_0);
RwInt32 sub_1C43A0();
// Whether the player may vote (sub_1C4CC0) and a vote answered (sub_1C4D40).
bool sub_1C4CC0();
void sub_1C4D40(RwInt32 arg_0);
// The player index a scoreboard selects its own row by (dword_4FD98C,
// after sub_1C46D0).
RwInt32 sub_1C42F0();
// The game data's unk_E4 set (sub_1C4B90) and its sub_1B5B50 given arg_0
// (sub_1C4BA0).
void sub_1C4B90();
void sub_1C4BA0(RwInt32 arg_0);
// A flag (byte_4FDA90): given (sub_1C4C20) and set (sub_1C4C30).
bool sub_1C4C20();
void sub_1C4C30(bool arg_0);
// The last vote forgotten (unk_4F7EB8.unk_490's sub_1C3D00).
void sub_1C4E50();
// A vote called on arg_0 (0 the level, 1 the game type) for the value
// arg_4, when none is running.
void sub_1C4C80(RwInt32 arg_0, RwInt32 arg_4);
// The weapon class set (sub_1C4340) and given (sub_1C4360), and the
// multiplayer manager's sub_1AFB70 (sub_1C5210).
void sub_1C4340(RwInt32 arg_0);
RwInt32 sub_1C4360();
void sub_1C5210();
// What the in-game Live options' sign-out passes on to the game data
// (sub_1B5BC0).
void sub_1C44A0();


#endif
