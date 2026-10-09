/*
 * The game loop (the image's "GameLoop Init ..." messages): its set-up
 * (sub_D6640) and what it runs. Only what its functions use is declared.
 */
#ifndef GAME_GAMELOOP_H
#define GAME_GAMELOOP_H

#include "types/type_4E5D30.h"
#include "rws/cresourcemanager.h"
#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rws/streamhandler.h"
#include "types/type_3DF8D8.h"
#include "game/data.h"
#include "types/type_DA0A0.h"
#include "types/type_1CCA10.h"
#include "game/netstate.h"
#include "game/flags.h"
#include "game/netscore.h"
#include "game/bombsites.h"
#include "game/netlisten.h"
#include "game/netvec.h"
#include "types/type_D48D0.h"
#include "types/type_505188.h"
#include "game/loc.h"
#include "game/ingamescreens.h"

// The screen mode RWS::MainLoop::Open is given (the database's names).
extern RwInt32 Width;
extern RwInt32 Height;
extern RwInt32 ZDepth;

#include "rws/mainloop.h"

extern RwInt32 dword_4B8718;
typedef struct RwCamera RwCamera;
// The main camera (MainLoop::Open's, and the front end's).
extern RwCamera *dword_4B88B0;

// Sets the game loop up (sub_D6640): its messages, RenderWare Studio's main
// loop, then sub_D6820; nonzero when it came up.
RwInt32 sub_D6640();
RwInt32 sub_D6820(RwInt32 arg_0);
void sub_1A2D80();
RwInt32 sub_19CF10();
void sub_124E90();
// A function that returns 1 (sub_31DB0, folded by /OPT:ICF with others that
// do; the game loop calls it with no arguments).
RwInt32 sub_31DB0();

// The modules the game loop's set-up (sub_D6820) starts, in its order; only
// that they take no arguments is known.
void sub_D95A0();
void sub_16D3A0();
void sub_174950();
void sub_F25F0();
void sub_1446B0();
void sub_171DC0();
void sub_770C0();
void sub_198390();
void sub_F1190();
void sub_17E290();
void sub_F7F60();
void sub_143CE0();
void sub_144990();
void sub_122FB0();
void sub_F2920();
void sub_F47F0();
void sub_15C790();
void sub_116310();
void sub_AA3F0();
void sub_15F1B0();
void sub_122230();
void sub_786A0();
void sub_672F0();
void sub_67B10();
void sub_71360();
void sub_6B3B0();
void sub_42990();
void sub_73360();
void sub_32E50();
void sub_34FA0();
void sub_40720();
void sub_3C1D0();
void sub_3CBF0();
void sub_3EC40();
void sub_FB4F0();
void sub_141BB0();
RwInt32 sub_17D240();
void sub_16FF90();
void sub_17C430();
void sub_125A50();
void sub_16F160();
void sub_16FC80();
void sub_E8800();
void sub_186720();
void sub_19AAB0();
// The database's name for 0xEFBC0 (game code), which the set-up calls with no
// arguments between sub_144990 and sub_122FB0.
extern "C" void RpPrtStdEmitterCreatePTank();

#include "types/type_143DC0.h"
typedef struct RwTexDictionary RwTexDictionary;
// The animated textures' manager (unit_143CE0): its animations (a list of
// type_143DC0) and the texture dictionary their textures are found in by
// name. The set-up resets it (sub_144310), the shutdown destroys them
// (sub_144330), each frame steps them (sub_144420).
struct type_4E5CC8
{
    type_16B810 unk_00;
    RwTexDictionary *unk_0C;

    type_4E5CC8();
    void sub_144310();
    void sub_144330();
    void sub_144400(struct type_143DC0 *arg_0);
    void sub_144420();
    void sub_1444B0(RpMaterial *arg_0, RwInt32 arg_4);
    void sub_144590(RpMaterial *arg_0, RwInt32 arg_4);
    struct RwTexture *sub_144650(const RwChar *arg_0);
    void sub_144690(RwTexDictionary *arg_0);
};
// Set while the animations are held (sub_183130 sets it).
extern RwInt32 dword_4CFE24;
extern type_4E5CC8 unk_4E5CC8;
struct type_4F2B68
{
    // Empty: folded by /OPT:ICF into pDtor (0x1E41C0), whose database name
    // it takes.
    void pDtor();
};
extern type_4F2B68 unk_4F2B68;
#include "game/debugmenu.h"
extern RwInt32 dword_4E5CBC;
// Cleared by the set-up.
extern RwInt32 dword_4B86FC;
extern RwInt32 dword_4B8700;
extern RwInt32 dword_4B8704;
extern RwInt32 dword_4B8708;
extern RwInt32 dword_4B870C;
extern RwInt32 dword_4B8710;
extern RwInt32 dword_4B8714;
extern RwInt32 dword_4B8724;   // the time paused in all (sub_D7EE0)
extern RwInt32 dword_4B8728;   // when the pause began (sub_D7EA0)
extern RwInt32 dword_4B8734;
extern RwInt32 dword_4B8778;

// The game's restart (sub_D6A50: "Game Restart BEGIN..."), and the restarts
// it runs, in its order; their names are in its messages ("Restart:
// CAnimObjectMgr::RestartClass()" before sub_78790 and so on). The empty
// ones were folded into sub_19A750 by /OPT:ICF.
void sub_D6A50();
void sub_1A2D50();
void sub_1A2D60();
void sub_125E00();
void sub_1701B0();
void sub_17C4C0();
void sub_17E2E0();
void sub_17D280();
void sub_FB530();
void sub_3EC80();
void sub_3CC80();
void sub_3C220();
void sub_407C0();
void sub_35020();
void sub_32EB0();
void sub_733A0();
void sub_429E0();
void sub_6B490();
void sub_714F0();
void sub_67340();
void sub_78790();
void sub_1222A0();
void sub_15F240();
void sub_16F1C0();
void sub_16FD10();
void sub_F4850();
void sub_EFF70();
void sub_F29F0();
void sub_F8010();
void sub_186950();
void sub_198570();
void sub_172210();
void sub_16D630();
void sub_D9610();
void sub_D8660();
// Whether the memory region arg_0 leaked, and its report (the restart's
// "MEMORY LEAK detected during shutdown!").
bool sub_12F080(RwInt32 arg_0);
void sub_12F060(RwInt32 arg_0);
// A pad's button (16 bytes): its mapping (from dword_429498), its value,
// its flags (1: ignored) and a counter read by sub_EE870.
struct type_4B9308_btn
{
    RwInt32 unk_00;
    RwReal unk_04;
    RwInt8 unk_08;
    RwUInt8 unk_09[0x3];
    RwInt32 unk_0C;
};
// A pad's rumble: its mode, its two motors' strengths (0 to 255) and
// whether it changed (sub_EED30, sub_EEE20, sub_EEF90).
struct type_EEF90
{
    RwInt32 unk_00;
    RwInt16 unk_04;
    RwInt16 unk_06;             // (a byte array here would draw a /GS cookie)
    RwReal unk_08;
    RwInt32 unk_0C;
};
// A pad (0x2D0 bytes): its 44 buttons and its rumble.
// How many buttons a pad record holds: 44 in MP; 40 in single player (its pad records are
// 0x290 bytes, the pads' block ends at +0xA40 where MP's ends at +0xB40, and its loops compare
// 0x28 where MP's compare 0x2C: SP 0xB6700, 0xB6A60).
#ifdef CODFH_SP // SP 0xB6700 and the other pad methods
enum { type_4B9308_btn_count = 40 };
#else // MP 0xEE540
enum { type_4B9308_btn_count = 44 };
#endif
struct type_4B9308_pad
{
    type_4B9308_btn unk_00[type_4B9308_btn_count];
    type_EEF90 unk_2C0;
};
// An input event (12 bytes; .data): its number (the pads' buttons map
// to it), its setting (sub_EECD0, sub_EED00) and its name ("ePE_FORWARD"
// and on, "ePE_INVALID" for the -1 entry that ends the table).
struct type_429498
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    const RwChar *unk_08;
};
extern type_429498 dword_429498[type_4B9308_btn_count + 1];   // (45 in MP; 41 in single player: SP 0x3219D8)
// Set while input is ignored (sub_EE8F0).
extern RwInt32 dword_4FDA9C;

// The pad manager (unk_4B9308): four pads, its
// set-up and shut-down, the pad the player uses when only one counts
// (unk_B48, with unk_B44 set), the stick dead zone and range.
struct type_4B9308
{
    type_4B9308_pad unk_00[4];
    RwInt32 unk_B40;            // set up
    RwInt32 unk_B44;            // one pad counts
    RwInt32 unk_B48;            // that pad (-1 for any)
    RwInt32 unk_B4C;
    RwInt32 unk_B50;            // the pad last read
    RwInt32 unk_B54;
    RwUInt8 unk_B58[0x4];
    RwReal unk_B5C;             // the sticks' dead zone
    RwReal unk_B60;             // and their range (255)

    type_4B9308();
    // Empty, folded (/OPT:ICF) into pDtor (0x1E41C0): its exit function
    // (0x30E4C0) calls it.
    ~type_4B9308();

    // Inline accessors, with no address and so no database names; named
    // for their fields. Evidence: the button reads and rumbles copy unk_B44
    // into a local of its own and test unk_B48 against -1 as a bool
    // (setne into a register) before using it.
    RwInt32 get_unk_B44()
    {
        RwInt32 r = unk_B44;
        return r;
    }
    RwInt32 get_unk_B48()
    {
        RwInt32 r = unk_B48;
        return r;
    }
    RwInt32 has_unk_B48()
    {
        return unk_B48 != -1;
    }
    // Whether the pad that counts was not taken out (the pads' library's
    // sub_19D990 tests it as a bool, sete).
    RwInt32 is_unk_B54_clear()
    {
        return unk_B54 == 0;
    }

    // Its set-up and shut-down (the start-up, sub_D99F0 and sub_D9BC0).
    void sub_EE590();
    void sub_EE840();
    // Its update (the buttons' values cleared, then read; dword_42926C set
    // while a pad is in) and a second read.
    void sub_EE6D0();
    void sub_EE770();
    // Clears pad arg_0's rumble (keeping its state unless arg_4) and on all
    // pads.
    void sub_EEF90(RwInt32 arg_0, RwInt32 arg_4);
    void sub_EEF50(RwInt32 arg_0);
    // A pad's button arg_4's state (the pause takes 3 and 0xB): the sticks
    // (0, 1, 2 and 5) past the dead zone scaled to 255, the triggers raw,
    // the rest at least 1 in size; pad 0 is the player's, 1 the next.
    RwReal sub_EE9A0(RwInt32 arg_0, RwInt32 arg_4);
    RwReal sub_EEAC0(RwInt32 arg_0, RwInt32 arg_4);
    // The same while nothing else has the input (sub_EE8F0: the movie player
    // skips on 0x17 or 0xB) or while the other overlay is off (sub_EE950).
    RwReal sub_EE8F0(RwInt32 arg_0, RwInt32 arg_4);
    RwReal sub_EE950(RwInt32 arg_0, RwInt32 arg_4);
    // A button's counter (0 while it is ignored).
    RwInt32 sub_EE870(RwInt32 arg_0, RwInt32 arg_4);
    // The pad index for the pad arg_0 (0 the player's, 1 the next).
    RwInt32 sub_EEC50(RwInt32 arg_0);
    // Sets the player's pad.
    void sub_EEAA0(RwInt32 arg_0);
    // Sets pad arg_0's button arg_4's flags.
    void sub_EECA0(RwInt32 arg_0, RwInt32 arg_4, RwInt8 arg_8);
    // A button definition's setting (arg_4 below 3), and its read.
    void sub_EECD0(RwInt32 arg_0, RwInt32 arg_4);
    RwInt32 sub_EED00(RwInt32 arg_0);
    // Two button queries through the pad library (sub_19E200, sub_19E430)
    // for the button arg_0 of the pad arg_4; the second a texture number.
    RwInt32 sub_EE790(RwInt32 arg_0, RwInt32 arg_4);
    RwInt32 sub_EE7F0(RwInt32 arg_0, RwInt32 arg_4);
    // Rumbles pad arg_0 in mode arg_4 with the strengths arg_8 and arg_C
    // (up to 255; "ControllerShake"), or adds to its rumble (sub_EEE20),
    // while rumble is on and sounds are.
    void sub_EED30(RwInt32 arg_0, RwInt32 arg_4, RwInt16 arg_8, RwInt16 arg_C);
    void sub_EEE20(RwInt32 arg_0, RwInt32 arg_4, RwUInt8 arg_8, RwInt16 arg_C);
#ifdef CODFH_SP
    // Single player only (src/recovered/unit_0EE540.cpp): clears a button's value, selects a
    // pad and reads it, binds one record, and sets the default bindings (SP 0xB6890, 0xB6A10,
    // 0xB6C60, 0xB6DC0).
    void sp_sub_B6890(RwInt32 arg_0, RwInt32 arg_4);
    void sp_sub_B6A10(RwInt32 arg_0);
    void sp_sub_B6C60(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    void sp_sub_B6DC0();
#endif
};
extern type_4B9308 unk_4B9308;
// The pad library under it; only the widths are known.
void sub_19DF40();
RwInt32 sub_19DFE0(type_4B9308 *arg_0, RwReal arg_4);
void sub_19E0D0(type_4B9308 *arg_0, RwReal arg_4);
void sub_19E120();
RwInt32 sub_19E200(RwInt32 arg_0, RwInt32 arg_4, type_4B9308 *arg_8);
RwInt32 sub_19E430(RwInt32 arg_0, RwInt32 arg_4, type_4B9308 *arg_8);

// The game loop's shutdown (sub_D6EB0: "GameLoop Shutdown BEGIN....") and
// its module shutdown (sub_D7040), and what they call, in their order.
void sub_D6EB0();
void sub_D7040(RwInt32 arg_0);
void sub_1A2D40();
void sub_19D060();
void sub_172A80();
void sub_125E40();
void sub_1702F0();
void sub_17C4E0();
void sub_17D2B0();
void sub_17E310();
void sub_E8830();
void sub_141BD0();
void sub_FB570();
void sub_3ECA0();
void sub_3CCE0();
void sub_3C270();
void sub_40840();
void sub_35080();
void sub_32F00();
void sub_733B0();
void sub_429F0();
void sub_6B4A0();
void sub_71560();
void sub_67E00();
void sub_673A0();
void sub_787F0();
void sub_1222D0();
void sub_15F280();
void sub_15C7D0();
void sub_F4860();
void sub_F0000();
void sub_1230F0();
void sub_F2A30();
void sub_144A70();
void sub_143D40();
void sub_F8120();
void sub_1868E0();
void sub_16F1D0();
void sub_16FD60();
void sub_198580();
void sub_773A0();
void sub_F2630();
void sub_172230();
void sub_1446C0();
void sub_16D6A0();
#ifndef CODFH_SP
// Frees the index-sound table dword_4E5E40 (MP 0xD73C0); SP expands this at 0xA288D.
void sub_D73C0();
#endif
type_1CCA10 sub_1CCA10();
// The multiplayer manager (unk_4F7EB8): cNetController, named by its trace
// "cNetController::updateVoiceSubSystem()". Its two score messages sit at
// +4 and +0xD0 (unk_4F7EB8.unk_04 and unk_4F7EB8.unk_D0, types/type_DC400.h), the network
// game at +0x19C (dword_4F8054), the session at +0x1A0 (dword_4F8058), the
// voice manager at +0x2C8 (dword_4F8180), its bomb sites' part at +0x2CC
// (unk_4F8184) and its flags' part at +0x384 (unk_4F7EB8.unk_384); other code uses
// those globals. Only the widths are known where no comment says more.
struct type_4F8054;
// The multiplayer manager's part at +0x490 (unk_4F7EB8.unk_490): two strings at
// +0x1C and +0x4C, and what three of its handlers pass on. Only the widths
// are known.
struct type_4F8348
{
    RwInt32 unk_00;             // the vote's kind (-1 for none)
    RwInt32 unk_04;             // its argument
    RwUInt32 unk_08;            // the votes held so far (a vote's number)
    RwReal unk_0C;              // the time left to vote (60 at first)
    RwUInt32 unk_10;            // the votes for
    RwUInt32 unk_14;            // the votes against
    RwUInt32 unk_18;            // the voters (the manager's sub_1ACA70)
    type_1CB670 unk_1C;         // who called it
    RwInt32 unk_38;             // set once this machine has voted
    RwInt32 unk_3C;             // the last vote's kind, argument, votes for
    RwInt32 unk_40;             // and against, and caller (sub_1C3C40)
    RwUInt32 unk_44;
    RwUInt32 unk_48;
    type_1CB670 unk_4C;
    RwReal unk_68;              // the time a passed vote's result still
                                // counts (60 when it passes)

    // Defined here but not inlined (it is called at sub_1A8E10); the
    // manager's destructor (sub_1A8DA0) still reserves its expansion's slots
    // (docs/toolchain.md).
    ~type_4F8348()
    {
    }

    // Resets it (the manager's reset, sub_1A9440); its step by arg_0 frames
    // (the manager's step; its traces: "VOTE update (server only)").
    void sub_1C3120();
    void sub_1C31D0(RwReal arg_0);
    // The vote's parts, named by their traces: this machine calls vote
    // arg_0 with the argument arg_4 ("localVoteCall"); a vote called by
    // player arg_C ("remoteVoteCall"); this machine's vote arg_0
    // ("localVoteRespond"); another's ("remoteVoteRespond", for vote
    // arg_4); the host ends it ("localVoteEnd") and the result arrives
    // ("remoteVoteEnd", for vote arg_8).
    void sub_1C32B0(RwInt32 arg_0, RwInt32 arg_4);
    void sub_1C3520(RwInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C);
    void sub_1C37E0(RwInt32 arg_0);
    void sub_1C3900(RwUInt32 arg_0, RwUInt32 arg_4);
    void sub_1C3970();
    void sub_1C3B40(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8);
    // Keeps the vote as the last one and clears it.
    void sub_1C3C40();
    // Whether a passed vote's result still counts (never on a client), and
    // forgets it.
    RwInt32 sub_1C3CC0();
    void sub_1C3D00();
    // The last vote's caller (the front end's sub_1C4DD0).
    type_1CB670 sub_1C4E00();
    // Inline accessors, with no addresses and so no database names; named
    // for their fields. Evidence: the front end's vote queries (sub_1C4D00
    // and on) read each through a slot of its own.
    RwInt32 get_unk_00()
    {
        RwInt32 r = unk_00;
        return r;
    }
    RwInt32 get_unk_04()
    {
        RwInt32 r = unk_04;
        return r;
    }
    RwInt32 get_unk_38()
    {
        RwInt32 r = unk_38;
        return r;
    }
    RwInt32 get_unk_3C()
    {
        RwInt32 r = unk_3C;
        return r;
    }
    RwInt32 get_unk_40()
    {
        RwInt32 r = unk_40;
        return r;
    }
    // The console messages: "Vote called", the count, "Voting complete".
    static void sub_1C3740();
    static void sub_1C3A40(RwUInt32 arg_0, RwUInt32 arg_4);
    static void sub_1C3BA0();
};
// Two dwords the spawn table hands the respawn (sub_1B7910, sub_1B7970);
// only the widths are known.
struct type_1B7910
{
    RwUInt32 unk_00;
    RwUInt32 unk_04;
};
// What the multiplayer manager's unk_280 points at: the level's network
// settings (types/cNetLevelParams.h).
class cNetLevelParams;
struct type_17DBD0_player;
// Four level sections: sub_1AFAF0 makes them the starting sections
// (dword_4B6840, when any is set), sub_1AF850 streams a peer's in. Only the
// widths are known.
struct type_1AFAF0
{
    RwInt32 unk_00[4];
};
// What the multiplayer manager's unk_1F0 entries point at (the remote
// players, unit_1A8B20) and its unk_234 (the behaviour cNetStaticCamTrigger,
// types/cNetStaticCamTrigger.h, which registers itself, sub_1C23E0); the
// latter as the parts sub_1AF7E0 reads of it.
struct type_4F7EB8_1F0;

class cNetPlayerTrigger;
// What the multiplayer manager's unk_27C points at: vf_020 makes a remote
// player (sub_1ABC00). Only the width is known.
struct type_4F7EB8_27C
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual type_4F7EB8_1F0 *vf_020();

    RwUInt8 unk_04[0x5C];
    RwMatrixTag unk_60;         // where it makes the player (the respawn
                                // moves it up by 1 and down by 1000); the
                                // unaligned tag, as the fields after it sit
                                // at their image offsets only without the
                                // vtable pointer's padding
    RwUInt8 unk_A0[0x38];
    type_1B7910 unk_D8;         // the respawn's settings (sub_1AED80)
    RwUInt8 unk_E0[0x40];
    type_1B7910 unk_120;
    RwInt32 unk_128;
    RwInt32 unk_12C;
    RwInt32 unk_130;
    RwInt32 unk_134;
    RwUInt8 unk_138[0x3C];
    RwChar unk_174[0x18];       // the player's name
};
struct type_4F7EB8_234
{
    RwUInt8 unk_00[0x60];
    RwMatrix unk_60;            // where the second player's view goes
                                // (sub_1AB2C0)
    RwUInt8 unk_A0[0x20];
    type_1AFAF0 unk_C0;
};
struct type_3E3860;
// The network game's pick-up (game/netmsg.h), which the multiplayer
// manager's pickup sends take (sub_1AE520, sub_1AE750).
struct type_1AE520;
struct type_4F7EB8 : type_4F8054_A8
{
    type_3E1E3C unk_04;         // the scores (unk_4F7EB8.unk_04)
    type_3E1FC4 unk_D0;         // and the round's (unk_4F7EB8.unk_D0)
    type_4F8054 *unk_19C;       // the network game, once running
    struct type_4F8058 *unk_1A0; // the session (dword_4F8058)
    type_17DBD0_player *unk_1A4; // the local player (dword_4F805C: the bullet
                                 // hit, sub_1ACAB0, calls through its +0x2260)
    struct type_1BABA0 *unk_1A8; // a second player (its +0x2260 part also
                                 // takes the remote hits on unk_230's player)
    type_17DBD0_player *unk_1AC; // the local kill cam player
    struct type_3D3548 *unk_1B0[16];   // the kill cam players
    type_4F7EB8_1F0 *unk_1F0[16];
    RwInt32 unk_230;
    type_4F7EB8_234 *unk_234;
    struct type_3D3548 *unk_238[16];
    cNetPlayerTrigger *unk_278; // the local player's trigger (dword_4F8130):
                                // told of each view change (sub_1BE9B0) and
                                // respawns it (sub_1ABE30)
    struct type_4F7EB8_27C *unk_27C;   // makes the remote players (vf_020)
    cNetLevelParams *unk_280;
    RwInt32 unk_284;
    RwInt32 unk_288;
    type_1CCA10 unk_28C;        // when the respawn was asked for (sub_1ABE30);
                                // cleared by its inline constructor (a `this`
                                // temporary in the manager's, sub_1A8B20)
    RwInt32 unk_290;
    RwInt32 unk_294;
    RwInt32 unk_298;
    RwInt32 unk_29C;            // the local player's team (its sub_1B8420)
    RwInt32 unk_2A0;
    RwInt32 unk_2A4;
    RwInt32 unk_2A8;
    RwInt32 unk_2AC;
    RwInt32 unk_2B0;
    RwInt32 unk_2B4;
    RwInt32 unk_2B8;
    RwInt32 unk_2BC;
    RwInt32 unk_2C0;
    struct type_3E3860_10 *unk_2C4; // the message listener (game/voice.h)
    type_3E3860 *unk_2C8;       // the voice manager
    type_4F8184 unk_2CC;        // the bomb sites' part (unk_4F8184)
    type_4F823C unk_384;        // the flags' part (unk_4F7EB8.unk_384)
    type_4F8288 unk_3D0;        // the players' teams (dword_4F8288)
    type_4F8348 unk_490;        // (unk_4F7EB8.unk_490)
    RwInt32 unk_4FC;
    RwInt32 unk_500;
    RwInt32 unk_504;
    type_1F8560_v unk_508;
    type_1F8560_v unk_514;
    RwInt32 unk_520;            // (dword_4F83D8)
    RwInt32 unk_524;            // cleared while the local player or unk_2B8's
                                // network player has its debug hook set
    type_1CCA10 unk_528;        // when the voice's peers were last chosen
    RwUInt8 unk_52C[0xD4];

    // Inline accessors with no address and so no database names, named for
    // their fields. Evidence: sub_1ACA70 reads unk_19C through a slot of its
    // own.
    type_4F8054 *get_unk_19C()
    {
        type_4F8054 *r = unk_19C;
        return r;
    }
    void sub_1AAB30();
    RwInt32 sub_1AF280();
    RwInt32 sub_1AED50();
    void sub_1AED30();
    void sub_1AC950(RwInt32 arg_0);
    RwInt32 sub_1AD730();
    void sub_1ADB40(RwInt32 arg_0);

    void sub_1AF750(const type_1CCA10 &arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Called when the pause button is first pressed (sub_D7C20).
    void sub_1AF250();
    // What the pulse zones' damage message is sent with (sub_17DBD0); only
    // the width is known.
    RwInt32 sub_1AEC70();
    // sub_1AEC70 through a result local: an inline with no address and so
    // no database name, named for the function it wraps. Evidence: the
    // local player's change (sub_1AF0F0) indexes the network players by a
    // slot holding its result, taken after the call's argument.
    RwInt32 get_1AEC70()
    {
        RwInt32 r = sub_1AEC70();
        // A compiled-out check (docs/toolchain.md): the registers after it
        // are one load on.
        if (!unk_4FC)
        {
        }
        return r;
    }
    // The outer loop's (sub_D9C00): whether to run the game, and a reset.
    RwInt32 sub_1AF670();
    void sub_1AF6F0();
    void sub_1AF7E0();
    void sub_1AF810(RwInt32 arg_0);
    void sub_1AC990(RwInt32 arg_0);
    // The listener's slots (its vtable off_3E13E8): a peer joined
    // (sub_1AC5D0), a peer left (sub_1AC790), joining failed (sub_1A8D60).
    virtual void vf_000(RwInt32 arg_0);
    virtual void vf_004(RwInt32 arg_0);
    virtual void vf_008();
    type_4F7EB8();
    ~type_4F7EB8();
    void sub_1A9440();
    void sub_1AAB50(RwReal arg_0);
    void sub_1AB440();
    void sub_1ABE30();
    // Named by its trace ("cNetController::updateVoiceSubSystem()").
    void updateVoiceSubSystem();
    void sub_1AADF0();
    void sub_1AAF40();
    // An inline accessor for unk_2C4, with no address and so no database
    // name; named for its field. Evidence: the set-up (sub_1A9580) reads it
    // through a slot of its own.
    struct type_3E3860_10 *get_unk_2C4()
    {
        struct type_3E3860_10 *r = unk_2C4;
        return r;
    }
    // An inline accessor for unk_500, with no address and so no database
    // name; named for its field. Evidence: the in-game pages' focus lost
    // (sub_21CD40) reads it through a slot of its own.
    RwInt32 get_unk_500()
    {
        RwInt32 r = unk_500;
        return r;
    }
    // An inline accessor for unk_2C8, with no address and so no database
    // name; named for its field. Evidence: the shutdown (sub_1A9960)
    // reaches the voice manager through a slot of its own each time.
    type_3E3860 *get_unk_2C8()
    {
        type_3E3860 *r = unk_2C8;
        return r;
    }
    // More inline accessors, named for their fields: unk_1A4 through a
    // slot of its own, and unk_1A4 and unk_19C returned directly. Evidence:
    // the front end's sub_1C44F0 reads the local player through a slot each
    // time, its sub_1C4520 and sub_1C4560 call through a return slot left
    // unwritten.
    type_17DBD0_player *get_unk_1A4()
    {
        type_17DBD0_player *r = unk_1A4;
        return r;
    }
    type_17DBD0_player *get_unk_1A4_direct()
    {
        return unk_1A4;
    }
    type_4F8054 *get_unk_19C_direct()
    {
        return unk_19C;
    }
    // Inline accessors for unk_2BC and unk_2C0, with no addresses and so
    // no database names; named for their fields. Evidence: the front end's
    // sub_1C43A0 and sub_1C4360 read each through a slot of its own.
    RwInt32 get_unk_2BC()
    {
        RwInt32 r = unk_2BC;
        return r;
    }
    RwInt32 get_unk_2C0()
    {
        RwInt32 r = unk_2C0;
        return r;
    }
    // Starts a game as the host (the front end's startServer, sub_1C4240):
    // the level arg_0, arg_4 players, the name arg_8, over the internet
    // (arg_C) or the system link; only the widths are known.
    void sub_1A9A70(RwInt32 arg_0, RwInt32 arg_4, const RwChar *arg_8, bool arg_C);
    // Joins the game arg_0 at the host arg_4 (voice with arg_C); false with
    // the reason in *arg_8 when it fails.
    bool sub_1A9CE0(const struct type_1CC1F0 *arg_0, const struct type_1CC3C0 *arg_4, RwInt32 *arg_8,
                    bool arg_C);
    void sub_1A94F0();
    // Empty, identical to other methods with two arguments and folded
    // (/OPT:ICF) into sub_73D90; the died handler (sub_1AD750) calls it.
    void sub_73D90(RwInt32 arg_0, RwInt32 arg_4);
    // Told a remote player is going (its destructor, sub_1BEEB0): empty,
    // identical to other methods and folded (/OPT:ICF) into sub_15FB30.
    void sub_15FB30(type_4F7EB8_1F0 *arg_0);
    // An inline accessor for unk_1A0, with no address and so no database
    // name; named for its field. Evidence: the join (sub_1AC5D0) reads it
    // through a slot of its own for each send.
    struct type_4F8058 *get_unk_1A0()
    {
        struct type_4F8058 *r = unk_1A0;
        return r;
    }
    void sub_1ABC00();
    void sub_1AF0F0(type_17DBD0_player *arg_0);
    RwInt32 sub_1AF1B0(struct type_3D3548 *arg_0);
    void sub_1AB070();
    void sub_1AB140();
    void sub_1AB200();
    void sub_1ADB80(RwInt32 arg_0, RwInt32 arg_4);
    // The spawn points for the team arg_0; only the widths are known.
    RwInt32 sub_1AC4E0(RwInt32 arg_0);
    void sub_1AFAF0(const type_1AFAF0 *arg_0);
    void sub_1AF850(RwInt32 arg_0);
    void sub_1AFB70();
    void sub_1AFB90(RwInt32 arg_0);
    void sub_1AFBB0();
    void sub_1AE520(type_1AE520 *arg_0);
    void sub_1AE750(type_1AE520 *arg_0, RwUInt32 arg_4, RwUInt32 arg_8);
    void sub_1AED80(RwInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8);
    void sub_1AFF20(RwInt32 arg_0);
    // How many lines the HUD's scoreboard shows, and whether the player
    // arg_0 is listed on it (type_DC400::sub_E7EF0); only the widths are
    // known.
    RwUInt32 sub_1ACA70();
    // Player arg_0's entity: the local player, a remote one, or with arg_4
    // set unk_238's while its unk_28 bit 0 is clear; 0 for none.
    struct type_3D3548 *sub_1AECA0(RwUInt32 arg_0, RwInt32 arg_4);
    // A count for arg_0 (2 from the HUD's radar, type_DC400::sub_E4030,
    // which picks an objective's icon by it: 0, 1 or more); -1 without
    // its +0x280 object. Only the widths are known.
    RwInt32 sub_1AF2F0(RwInt32 arg_0);
    // What the player's death fade calls (sub_119480); only the widths are
    // known.
    void sub_1AB2C0();
    void sub_1AB400(RwInt32 arg_0);
    void sub_1AB420(RwInt32 arg_0);
    // Its set-up and start, which the start-up (sub_1A2910) calls around
    // the text's language; only the widths are known.
    void sub_1A9580();
    void sub_1AA320();
    // What the game loop's wrappers call (sub_1A2D20 at shutdown, with the
    // debug text's; sub_1A2D40 and sub_1A2D50); only the widths are known.
    void sub_1A9960();
    void sub_1A8E80();
    void sub_1A9160();
};
extern type_4F7EB8 unk_4F7EB8;
// Cleared by the manager's constructor (sub_1A8B20); only the width is
// known.
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4FBA18;
#else
extern RwInt32 dword_4FBA18;
#endif
// Prints a game event (arg_4, formatted) with the game's time.
void sub_1A8A70(type_4F7EB8 *arg_0, const RwChar *arg_4, ...);

// An inline that expands to nothing but keeps a local of its own: no
// address and so no database name; named for what it leaves. Evidence: the
// module shutdown (sub_D7040) keeps three slots below its temporaries that
// no code uses, which three expansions of an empty inline with a local give
// (named locals, even unused ones, sort above the temporaries).
inline void unused_slot()
{
    RwInt32 r;
}

// The main loop (sub_D7410): runs while dword_4B86F8's bit 0 is set and bit
// 2 clear, taking restarts (bit 3), resets (bit 1) and bit 5's request only
// when nothing is loading (can_change); sub_D9490(1, 0) after it.
void sub_D7410();
RwInt32 sub_D7570();
void sub_D7880();
void sub_D8D20();
void sub_D8E30();
void sub_D9490(RwInt32 arg_0, RwInt32 arg_4);
// The loading screen's text (sub_D9490): its position in 512 by 448 units
// and its colour (the three words sub_E9BE0 takes last).
extern RwReal flt_429270;
extern RwReal flt_429274;
extern RwReal flt_429278;
extern RwReal flt_42927C;
extern RwReal flt_429280;
// sub_125ED0 as the loading screen calls it, with a second argument it does
// not read (render.h declares the one-argument form).
void sub_125ED0(RwCamera *arg_0, RwInt32 arg_4);
// Also declared in game/render.h and game/worldmgr.h, which bring in DSound
// and the Windows headers.
void sub_126750(RwCamera *arg_0);
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4E5C74;
#else
extern RwInt32 dword_4E5C74;
#endif
RwInt32 sub_19D020();
void sub_19D040();
extern RwInt32 dword_4F26D0;
extern RwUInt8 byte_4C1941;

// The three tests the main loop makes before a restart, a reset or bit 5's
// request: inlines with no address and so no database names, named for
// what they test. Evidence: each term is computed into a register (sete,
// setle, a constant 1) and tested, as an expanded inline's return is.
inline RwInt32 is_4F26D0_clear()
{
    return dword_4F26D0 == 0;
}
inline RwInt32 is_4B86FC_clear()
{
    return dword_4B86FC <= 0;
}
inline RwInt32 always_true()
{
    return 1;
}

// The level-start steps sub_D7570 takes one per frame (dword_4B8700 to
// dword_4B8714), and what they call.
// Sets up the alfa object manager's pools (types/alfaobjman.h).
void sub_713E0();
void sub_144B80();
void sub_198610();
void sub_E8910();
void sub_12F090();
void sub_1A2D70();
RwReal sub_198650();
// Two words sub_D7570 hands sub_198660 (both 0).
struct type_198660
{
    RwInt32 unk_00;
    RwInt32 unk_04;
};
void sub_198660(type_198660 *arg_0);
extern RwInt32 dword_4B871C;
extern RwUInt32 dword_4B8730;
extern RwInt32 dword_4B8760;
// The global section (game/worldmgr.h), whose first field the database calls
// dword_4E5CD8 and its collision world (+0x28) dword_4E5D00; the accessor for
// that world has no address, so it is named for the database's variable.
// Evidence: the blast (sub_9A960) reads it through a result local twice, as
// get_4E5D30 records' worlds.
extern type_4E5D30 unk_4E5CD8;
inline RpWorld *get_4E5D00()
{
    RpWorld *r = unk_4E5CD8.unk_28;
    return r;
}

// The frame (sub_D7880): the modules' updates between the profiler's
// timing sections (sub_16D7F0/sub_16D850), each given the frame's time.
void sub_D9620();
void sub_16D730();
void sub_16D740();
void sub_187B30();
void sub_D7C20();
void sub_1A2A80(RwReal arg_0);
void sub_73650(RwReal arg_0);
void sub_42C50(RwReal arg_0);
void sub_15F350(RwReal arg_0);
void sub_17D370(RwReal arg_0);
void sub_F11D0(RwReal arg_0);
void sub_17E330(RwReal arg_0);
void sub_173750();
void sub_F6090();
void sub_3ED10(RwReal arg_0);
void sub_170310(RwReal arg_0);
void sub_F4890(RwReal arg_0);
void sub_F3410();
void sub_1222F0(RwReal arg_0);
void sub_F00C0();
void sub_124F70(RwReal arg_0);
void sub_857B0(RwReal arg_0);
void sub_125F20(RwInt32 arg_0);
extern RwInt32 dword_4CFA00;
// A flag with a getter and a setter (sub_D7C00, sub_D7C10).
extern bool byte_4B8740;
bool sub_D7C00();
void sub_D7C10(bool arg_0);

// The pause (sub_D7C20): bit 4 of dword_4B86F8 while paused, flt_4B8984
// the paused time, byte_4B8764 the state the pad asks for; sub_D7EA0 and
// sub_D7EE0 enter and leave it (dword_4B8728 when it began, dword_4B8724
// the time paused in all).
void sub_D7EA0();
void sub_D7EE0();
extern RwReal flt_4B8984;
// dword_4B86F8's bits as the pause stores them (a bitfield store: the value
// first, then the word masked with an imm32).
struct type_4B86F8
{
    RwUInt32 unk_00_0 : 4;
    RwUInt32 unk_00_4 : 1;      // paused
    RwUInt32 unk_00_5 : 27;
};
extern bool byte_4B8764;
extern RwInt32 dword_4EBCD8;
extern RwInt32 dword_4B872C;
void sub_85D60();
void sub_860E0();
// The level path helpers (sub_D7F20, sub_D7F40) and the section loader
// (sub_D7F70: "SECTIONS\\S_%d.RWS" under the level's directory).
void sub_D7F20(RwChar *arg_0, const RwChar *arg_4);
void sub_D7F40(RwChar *arg_0, const RwChar *arg_4);
void sub_D7F70(RwInt32 arg_0);
RwInt32 sub_19B050();
const RwChar *sub_19B060(RwInt32 arg_0);
// What sub_D7F70 hands the section reader sub_142F70: a kind (0x13), the
// section, and more only known by width.
struct type_142F70_0C
{
    RwInt32 unk_00;
    type_3DF8D8_04 unk_04;
    RwInt32 unk_0C;
};
struct type_142F70
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;
    type_142F70_0C unk_0C;
};
struct type_141C10;
RwInt32 sub_142F70(RwStream *arg_0, type_141C10 *arg_4);

// Loads the file arg_0 into memory (pData) and runs arg_4 on it as a memory
// stream with a kind 0x13 record for arg_8, the result into *arg_C; 0 when
// it will not open.
RwInt32 sub_D80C0(const RwChar *arg_0, RwInt32 (*arg_4)(RwStream *, type_142F70 *), RwInt32 arg_8,
                  RwInt32 *arg_C);
// The section arg_0 through sub_D80C0 (sub_D8230), and the level's
// GODDATA.DFF through RenderWare Studio's stream handler (sub_D8310).
void sub_D8230(RwInt32 arg_0);
RwInt32 sub_D8310();
// Collision-world record arg_0: an inline with no address and so no
// database name, named for its array. Evidence: sub_D8230 stores through a
// temporary holding each record's address (the result local), where
// sub_D7F70's plain subscripts store directly.
inline type_4E5D30 *get_4E5D30(RwInt32 arg_0)
{
    type_4E5D30 *r = &dword_4E5D30[arg_0];
    return r;
}
// The file size of the file handle arg_0.
RwUInt32 sub_16D200(void *arg_0);
// The file sub_D80C0 holds in memory while it reads it (the database's
// name).
extern void *pData;


// Loads the level: GLOBAL.DFF and LEVEL.DFF through RenderWare Studio's
// stream handler, then LEVEL.RWS through the section reader, between the
// main loop's system messages (sub_D83C0).
RwInt32 sub_D83C0();

// Streams the level's sections into the four collision-world records: the
// starting sections' slots (dword_4B6830, dword_4B6840) when sections are
// set up (sub_B0140), else the starting sections (dword_4B6850) or 1 to 4;
// a section that goes is dropped (sub_174060) and one that is not loaded
// yet (sub_174640) is read (sub_D7F70). Each step refreshes the loading
// screen unless byte_4B8E9C is set.
void sub_D8660();
void sub_174060(type_4E5D30 *arg_0, RwInt32 arg_4);
RwInt32 sub_174640(RwUInt16 arg_0);
#ifdef CODFH_PLAIN
extern bool &byte_4B8E9C;
#else
extern bool byte_4B8E9C;
#endif

// Loads the game's global data (sub_D8A40): its asset lists by name
// through sub_1989D0 (with their kinds), counting dword_4B86FC up as it
// goes; nonzero when done.
RwInt32 sub_D8A40();
struct type_1989D0;
type_1989D0 *sub_1989D0(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                         RwInt32 arg_10);
void sub_F2680();
void sub_186980();
// The front end's set-up (sub_D8B90): the shell (sub_E9CA0), then the
// level (sub_D83C0).
RwInt32 sub_D8B90();
// Queue the game's quit (sub_D8BC0, whose callback sub_D8C00 sets bit 2 of
// dword_4B86F8) or sub_D8C60 (sub_D8C20) behind a one-second fade, once
// (bit 6).
void sub_D8BC0();
void sub_D8C00();
void sub_D8C20();
void sub_D8C60();
void sub_1252E0(void (*arg_0)(), RwInt32 arg_4);
void sub_19B000(RwInt32 arg_0);

// The credits (sub_D8C60: after the quit's fade, plays Credits.bik when
// dword_4B918C allows, then quits) and the level change (sub_D8CC0 queues
// the level arg_0 behind a two-second fade, once, remembering the one
// left in dword_4B8770; sub_D8D20 picks the next level from its table;
// sub_D8DC0 runs after the fade, sub_D8E30 on the next frame).
void sub_D8CC0(RwInt32 arg_0);
void sub_D8D20();
void sub_D8DC0();
void sub_D8E30();
void sub_E89E0();
void sub_E8AC0(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
void sub_D93F0();
void sub_D8F60();
void sub_D8F80();
// Loads the front end's message text (arg_0 set keeps it resident);
// whether it loaded.
#ifdef CODFH_SP // single player's returns an int (SP 0x11BCD0)
RwInt32 sub_186880(RwInt32 arg_0);
#else
bool sub_186880(RwInt32 arg_0);
#endif
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4B918C;
#else
extern RwInt32 dword_4B918C;
#endif
extern RwInt32 dword_4B8770;
extern RwInt32 dword_4B877C;
extern RwInt32 dword_4B8890;
// Draws the memory card message (sub_D8E80) through the shell's text
// (sub_E9BE0).
void sub_D8E80();



// The checkpoint (sub_D9320 takes it, sub_D93F0 restores it): the register
// dword_4B8780 and the 0x48 bytes after it, the four starting sections
// (dword_4B8788) and the animation pack selector's six keys
// (unk_4B8798).
extern RwUInt8 byte_4B8784;
extern RwInt32 dword_4B8788[4];
extern type_3DF8D8_04 unk_4B8798[6];
void sub_D93F0();

// The checkpoint save (sub_D8F80): the player's state (sub_111040, checked
// and cleared when out of range), then the save record, into the save
// state dword_4F28F0.
void sub_D8F80();
// The save itself: sub_1866E0 (game/waitscreen.h).
// Its camera: the frontend's (game/frontend.h).
extern struct type_D9CF0 unk_4B8744;

// The loading screen's refresh (sub_D9450: during a restart, counts
// dword_4B8734 up and draws it with sub_D9490, whose drawing is unreachable
// in the image).

// The tick (the restart's "Restart: Tick::Restart()", sub_D9610, resets it
// through sub_D95A0): deltaTime is the frame's time in 60ths of a second
// (flt_429288 before the cap of 5), dword_4B87C8 the time in all and
// dword_4B87D8 the frame count; dword_4B87DC picks how the frame is timed
// (1 a fixed flt_429294, 2 scaled by flt_429290 for dword_42928C frames,
// 0 and 6 scaled by flt_429298, 3 and 4 once and back to 0, 5 one frame
// then stopped).
void sub_D95A0();
void sub_D98D0(RwReal arg_0, RwReal arg_4);
// The tick's milliseconds per frame (1000 / 60) and cap (5 frames), as
// constants of their own: the cap is copied into deltaTime through a
// register, as a const variable is.
extern const RwReal flt_3D7E20;
extern const RwReal flt_3D7E24;
extern RwReal flt_429290;
extern RwReal flt_429294;
extern RwReal flt_429298;
extern bool byte_42929C;
extern RwUInt32 dword_4B87CC;
extern RwUInt32 dword_4B87D0;
extern RwUInt32 dword_4B87D4;
extern RwInt32 dword_4B87E0;

// The game's start (sub_D9950: the video mode to sub_D99F0), run
// (sub_D99B0) and end (sub_D99D0).
struct type_D9950
{
    RwInt32 unk_00;             // Width
    RwInt32 unk_04;             // Height
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
};
RwInt32 sub_D9950();
void sub_D99B0();
void sub_D99D0();
RwInt32 sub_D99F0(type_D9950 *arg_0);
RwInt32 sub_19D290();
void sub_D9BC0();
void sub_19D2D0();
extern RwInt32 dword_4B87F0;
extern RwInt32 dword_4B87F4;

#endif
