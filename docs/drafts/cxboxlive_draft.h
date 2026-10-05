/*
 * cXboxLive (named by its traces, "cXboxLive::createSession()" and the
 * rest; unit_1D7CE0): the network system, one instance (sub_1D8810 gives
 * it, unk_4FED00). It starts the Xbox online library, creates and joins
 * sessions over Xbox Live or the system link, and keeps the peers'
 * connections, the block list and the voice peers.
 *
 * Only the widths are known where no comment says more.
 */
#ifndef GAME_XBOXLIVE_H
#define GAME_XBOXLIVE_H

#include <xtl.h>
#include <xonline.h>

#include "rw/ostypes.h"
#include "types/type_1CCA10.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_DC400.h"
#include "game/systemlink.h"

// The session's settings (0x100 bytes, at cXboxLive +0x778): match
// attributes, each set through its own setter (the value, then its changed
// flag).
struct type_1DC6C0
{
    RwInt32 unk_00;
    RwInt32 unk_04;             // the players (16)
    RwInt32 unk_08;
    RwInt32 unk_0C;
    RwUInt8 unk_10[0xF0];

    type_1DC6C0();
    ~type_1DC6C0();
    void sub_1DCF40(ULONGLONG arg_0);
    void sub_1DCF90(ULONGLONG arg_0);
    void sub_1DCFE0(ULONGLONG arg_0);
    void sub_1DD030(ULONGLONG arg_0);
    void sub_1DD0B0(ULONGLONG arg_0);
    void sub_1DD0E0(ULONGLONG arg_0);
    void sub_1DD130(ULONGLONG arg_0);
    // The session's name.
    void sub_1DD160(const WCHAR *arg_0);
};

// At cXboxLive +0x878 (0x104C bytes).
struct type_1DD330
{
    RwUInt8 unk_00[0x104C];

    type_1DD330();
    ~type_1DD330();
};

// The block list (0xC4 bytes, at cXboxLive +0x40DC): up to 16 user ids and
// their count; sub_1DBED0 is whether it holds arg_0's.
struct type_1DBE00
{
    type_1D8370 unk_00[16];
    RwUInt32 unk_C0;

    type_1DBE00();
    bool sub_1DBED0(const XUID *arg_0);
};

struct cXboxLive
{
    RwUInt8 unk_000[0x700];
    RwUInt8 unk_700[0x70];
    RwInt32 unk_770;
    RwInt32 unk_774;
    type_1DC6C0 unk_778;
    type_1DD330 unk_878;
    CSystemLinkQuery unk_18C4;
    RwInt32 unk_2918;           // its state (4 while the voice runs)
    RwInt32 unk_291C;           // the session's creation (0 failed, 2
                                // running; the Xbox game's
                                // stateServerTakeUp)
    RwInt32 unk_2920;
    RwInt32 unk_2924;
    RwInt32 unk_2928;
    type_1DDE20_mask unk_292C;  // the peers with voice
    type_1DDE20_mask unk_292E;
    type_1DDE20_mask unk_2930;
    type_1DDE20_mask unk_2932;
    type_1DBF70 unk_2934;
    type_1DBF70 unk_3370;
    RwUInt32 unk_3DAC;          // flags (bit 3: the online library started)
    type_4F8054 *unk_3DB0;      // the network game (the manager's set-up)
    RwUInt8 unk_3DB4[0x100];
    RwUInt8 unk_3EB4[0xC0];
    RwUInt8 unk_3F74[0xC0];
    type_1DDE20_mask unk_4034;
    RwInt32 unk_4038;           // the join's state (1 waiting, 3 failed)
    RwInt32 unk_403C;           // why it failed (2 and 3 have their own
                                // errors)
    RwUInt8 unk_4040[8];
    type_1CCA10 unk_4048[16];
    type_1CCA10 unk_4088[16];
    RwUInt32 unk_40C8;
    RwChar unk_40CC[16];        // the system link host's name
    type_1DBE00 unk_40DC;
    RwInt32 unk_41A0;
    type_1DDE20_mask unk_41A4;

    cXboxLive();
    ~cXboxLive();
    RwInt32 sub_1D9230();
    // Starts the Xbox online library (the multiplayer manager's set-up):
    // whether it did.
    BOOL sub_1D8880();
    // An inline setter for unk_3DB0, with no address and so no database
    // name; named for its field. Evidence: the set-up (sub_1A9580) stores
    // through a copy of the pointer, after its argument.
    void set_unk_3DB0(type_4F8054 *arg_0)
    {
        unk_3DB0 = arg_0;
    }
    RwInt32 sub_1DBD60(RwInt32 arg_0, XUID *arg_4, RwInt32 arg_8);
    // What the Xbox network game (types/cXboxLiveNetGame.h) calls; only the
    // widths are known. The session's settings (the map and options), its
    // creation over Xbox Live (sub_1D8C00) or the system link (sub_1D8E10,
    // for the name arg_0 of sub_1DB920), the host's socket (sub_1D9610,
    // arg_0 set for Xbox Live), the join (sub_1D9700), and the rest.
    void sub_1DB8C0(RwInt32 arg_0);
    void sub_1DB800(RwInt32 arg_0);
    void sub_1DB7C0(RwInt32 arg_0);
    void sub_1DB750(RwInt32 arg_0, RwInt32 arg_4);
    void sub_1DB840(RwInt32 arg_0);
    void sub_1DB880(RwInt32 arg_0);
    RwInt32 sub_1D8C00();
    RwInt32 sub_1D9610(RwInt32 arg_0);
    void sub_1DB920(const RwChar *arg_0);
    RwInt32 sub_1D8E10();
    RwInt32 sub_1D9700(XNADDR *arg_0, XNKID *arg_4, XNKEY *arg_8, const type_1CCA10 &arg_C, RwInt32 arg_10);
    void sub_1D9C30(RwInt32 arg_0, RwInt32 arg_4, const type_1CCA10 &arg_8);
    void sub_1DBA80(const type_1CCA10 &arg_0);
    void sub_1DA680(XUID arg_0);
    void sub_1D9DD0(RwInt32 arg_0);
    void sub_1D8B40(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    const RwChar *sub_1DA070();
    void sub_1DA170();
    void sub_1D8EE0(struct type_4F8054_4C *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    void sub_1D9100(struct type_4F8054_4C *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    void sub_1D9090();
    RwInt32 sub_1D91E0();
    RwInt32 sub_1D9270(RwInt32 arg_0);
    void sub_1DB900(RwInt32 arg_0);
    void sub_1D8900();
    void sub_1DBA40(RwInt32 arg_0, RwInt32 arg_4);
    // An inline accessor with no address and so no database name, named for
    // its field. Evidence: the voice manager's sub_1C6530 copies the mask
    // through a result local.
    type_1DDE20_mask get_unk_292C()
    {
        return unk_292C;
    }
    // Inline too, named for its field. Evidence: the multiplayer manager's
    // voice choice (sub_1AA380) reads it through a `this` copy and a slot.
    RwInt32 get_unk_2918()
    {
        return unk_2918;
    }
    // Inline too, named for their fields. Evidence: the Xbox network game's
    // stateServerTakeUp switches on unk_291C through a return slot left
    // unwritten, and its join (sub_1D55A0) reads unk_4038 and unk_403C
    // through `this` copies.
    RwInt32 get_unk_291C()
    {
        return unk_291C;
    }
    RwInt32 get_unk_4038()
    {
        return unk_4038;
    }
    RwInt32 get_unk_403C()
    {
        return unk_403C;
    }
};
cXboxLive *sub_1D8810();

#endif
