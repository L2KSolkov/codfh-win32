/*
 * The voice chat (unit_1C60A0): the voice manager (type_3E3860, 0x3160
 * bytes; dword_4F8180 and the multiplayer manager's +0x2C8 hold it) that
 * buffers this machine's microphone data and sends it to the peers through
 * its channel (type_3E3870, at +0x14), and the XHV engine's owner
 * (type_3E3884, at +0x3060) that plays the peers' voices and tells the
 * peers which players have headsets, speak or are muted (type_3E0F54
 * messages).
 *
 * Only the widths are known where no comment says more.
 */
#ifndef GAME_VOICE_H
#define GAME_VOICE_H

#include <xtl.h>
#include <xonline.h>
#include <xhv.h>

#include "rw/ostypes.h"
#include "types/type_1CCA10.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_DC400.h"
#include "game/netmsg.h"
#include "types/cXboxLive.h"

// The network system is cXboxLive (types/cXboxLive.h).
// Whether the game is running (the voice chat sends its status each second
// then).
bool sub_1C4C00();

// The receivers the voice manager is built as: a peer's voice data
// (arg_0 the peer, arg_4 and arg_8 the data and its size) and this
// machine's microphone data. Their own bodies are empty (folded by
// /OPT:ICF into sub_73D80 and sub_73D90).
struct type_3E386C
{
    virtual void vf_000(RwInt32 arg_0, void *arg_4, RwUInt32 arg_8)
    {
    }
};
struct type_3E3868
{
    virtual void vf_000(RwUInt8 *arg_4, RwUInt32 arg_8)
    {
    }
};

// What the voice manager's channel belongs to: its unk_08 is the channel
// while the voice manager runs. It is the network game's message listener
// (cNetGame's unk_A4; unit_1DDBE0), passing the messages on to the
// channel; the multiplayer manager's set-up builds it and its shutdown
// deletes it.
struct type_3E3870;
struct type_3E3860_10 : type_4F8054_A4
{
    type_4F8054 *unk_04;        // the network game
    type_3E3870 *unk_08;

    type_3E3860_10(type_4F8054 *arg_0);
    virtual void vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    virtual ~type_3E3860_10()
    {
    }
    // An inline accessor for unk_04, with no address and so no database
    // name; named for its field. Evidence: the voice channel (sub_1DE900,
    // sub_1DEE60) reads the network game through a slot of its own.
    type_4F8054 *get_unk_04()
    {
        return unk_04;
    }
    // Sends the message arg_0 (arg_4 passed on) to the peers arg_8 (the
    // channel's send, sub_1DF2A0).
    RwInt32 sub_1DDC50(type_1F8560 *arg_0, RwInt32 arg_4, const type_1DDE20_mask &arg_8);
};

// The voice manager's channel to the peers (its constructor, sub_1DE280,
// takes the owner; its destructor is empty). The base's level (off_3E66D4)
// is only known by its one method (sub_1DE900).
struct type_3E3860;
struct type_3E66D4
{
    virtual void vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
    {
    }
};
// A voice packet that came in (0x118 bytes; the channel keeps 24): its
// data, the number of the sender's packet before it for this machine, its
// own number, its size in bytes, when it came in, and its neighbours in
// the free list or its sender's queue (kept in number order).
struct type_3E3870_in
{
    RwUInt8 unk_000[0x100];
    RwUInt32 unk_100;
    RwUInt32 unk_104;
    RwUInt32 unk_108;
    type_1CCA10 unk_10C;
    type_3E3870_in *unk_110;
    type_3E3870_in *unk_114;
};

// A voice packet going out (0x15C bytes; the channel keeps 5): its data,
// this machine's peer, the peers it came from and goes to, the number of
// the packet each peer was last sent, its own number, its size in bytes,
// when it was queued, and its neighbours.
struct type_3E3870_out
{
    RwUInt8 unk_000[0x100];
    RwUInt8 unk_100;
    type_1DDE20_mask unk_102;
    type_1DDE20_mask unk_104;
    RwUInt32 unk_108[16];
    RwUInt32 unk_148;
    RwUInt32 unk_14C;
    type_1CCA10 unk_150;
    type_3E3870_out *unk_154;
    type_3E3870_out *unk_158;
};

// The voice channel's state for a debug display (0x10C bytes; the
// multiplayer manager's sub_1B00F0 asks for it): each peer's packets
// waiting, the outgoing packets and their origins, whether each peer is
// heard and for how long, the time since the last send, the last ten
// packets in and out, where the next of each goes, and the late packets.
// The voice manager's status for a debug display (0xE0 bytes; the log's
// sub_1B00F0 asks for it, and sub_1C6900 clears it in this build).
struct type_1C6900
{
    RwInt32 unk_00;             // packets pending encode
    RwInt32 unk_04;             // pending dispatch
    RwInt32 unk_08[16];         // each peer's decodes
    RwInt32 unk_48;             // pending playback
    type_1CCA10 unk_4C;         // since the last decode
    type_1CCA10 unk_50;         // since the last dispatch
    type_1CCA10 unk_54[16];
    RwInt32 unk_94[16];         // 1: active, 2: audible
    RwInt32 unk_D4;             // the decode's destination offset
    RwInt32 unk_D8;             // the playback offset
    RwInt32 unk_DC;             // the playback bytes remaining
};

struct type_1DF990
{
    RwUInt32 unk_00[16];
    RwUInt32 unk_40;
    RwUInt32 unk_44[5];
    RwInt32 unk_58[16];
    type_1CCA10 unk_98[16];
    type_1CCA10 unk_D8;
    RwUInt8 unk_DC[10];
    RwUInt8 unk_E6[10];
    RwUInt8 unk_F0[10];
    RwUInt8 unk_FA[10];
    RwUInt8 unk_104;
    RwUInt8 unk_105;
    RwInt32 unk_108;
};

struct type_3E3870 : type_3E66D4
{
    type_3E3860_10 *unk_04;
    type_1CCA10 unk_08;
    type_3E3860 *unk_0C;        // the voice manager while it runs
    type_3E3870_in unk_10[24];
    type_3E3870_in *unk_1A50;   // the free packets
    type_3E3870_in *unk_1A54[16]; // each peer's packets waiting
    RwUInt32 unk_1A94[16];      // each peer's packet last played (-1)
    type_3E3870_out unk_1AD4[5];
    type_3E3870_out *unk_21A0;  // the free packets
    type_3E3870_out *unk_21A4;  // the packets waiting to go out
    type_1DDE20_mask unk_21A8;
    type_1CCA10 unk_21AC[16];
    type_1CCA10 unk_21EC;       // when the packets were last sent
    RwUInt32 unk_21F0[16];      // the packet each peer was last sent
    RwUInt32 unk_2230;          // the next packet's number
    RwReal unk_2234[16][16];    // the squared distances between the peers
                                // (the multiplayer manager's sub_1AA380)
    RwInt32 unk_2634;
    RwUInt8 unk_2638[10];       // the last ten packets in: their senders
    RwUInt8 unk_2642[10];       // and the peers they came through
    RwUInt8 unk_264C[10];       // the last ten out: their origins
    RwUInt8 unk_2656[10];       // and the peers they went to
    RwUInt8 unk_2660;           // where the next of each goes
    RwUInt8 unk_2661;
    RwInt32 unk_2664;           // the packets played late

    type_3E3870(type_3E3860_10 *arg_0);
    // A compiled-out check (docs/toolchain.md), as an inline with no
    // address: the channel's methods load their registers one on after
    // each, in the places its calls stand (their asserts, compiled out).
    void check()
    {
        if (!unk_04)
        {
        }
    }
    virtual ~type_3E3870()
    {
    }
    // A voice packet from peer arg_8 in the stream arg_C (arg_10 bits).
    virtual void vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    // Starts it; drops peer arg_0; sends the data arg_4 (arg_8 bytes) to
    // the peers arg_0; takes the time arg_0.
    void sub_1DE450();
    void sub_1DE770(RwInt32 arg_0);
    void sub_1DEE60(type_1DDE20_mask arg_0, RwUInt8 *arg_4, RwUInt32 arg_8);
    void sub_1DF970(const type_1CCA10 &arg_0);
    // The incoming packets: a free one (the oldest waiting played out when
    // there is none), queued for peer arg_4, whether peer arg_4's packet
    // arg_0 is queued, and peer arg_0's first packets played (arg_4 set:
    // dropped) and freed.
    type_3E3870_in *sub_1DEB60();
    void sub_1DEC50(type_3E3870_in *arg_0, RwInt32 arg_4);
    RwInt32 sub_1DED00(RwUInt32 arg_0, RwInt32 arg_4);
    void sub_1DED60(RwInt32 arg_0, RwInt32 arg_4);
    // The outgoing packets: a free one (the last waiting dropped when there
    // is none), queued, and freed.
    type_3E3870_out *sub_1DEFD0();
    void sub_1DF080(type_3E3870_out *arg_0);
    void sub_1DF0E0(type_3E3870_out *arg_0);
    // The peers in *arg_0 (but arg_8) reached directly move to *arg_4.
    void sub_1DF1E0(type_1DDE20_mask *arg_0, type_1DDE20_mask *arg_4, RwInt32 arg_8);
    // Sends arg_0 to peer arg_4.
    void sub_1DF2A0(type_3E3870_out *arg_0, RwInt32 arg_4);
    // Plays out the packets waiting too long by the time arg_0.
    void sub_1DF4A0(const type_1CCA10 &arg_0);
    // The routing table's entry for arg_0 peers: from arg_4 towards arg_8
    // (the table unk_42CE38); the peer to send through from arg_0 to arg_4.
    RwUInt8 sub_1DF5A0(RwUInt8 arg_0, RwUInt8 arg_4, RwUInt8 arg_8);
    RwUInt8 sub_1DF5E0(RwUInt8 arg_0, RwUInt8 arg_4);
    // Sends arg_4 to peer arg_8; sends each waiting packet to its next
    // peer; drops the old ones and sends every 100 milliseconds.
    void sub_1DF6D0(const type_1CCA10 &arg_0, type_3E3870_out *arg_4, RwUInt8 arg_8);
    void sub_1DF740(const type_1CCA10 &arg_0, type_1DDE20_mask *arg_4, RwInt32 *arg_8);
    void sub_1DF7D0(const type_1CCA10 &arg_0);
    void sub_1DF940(const type_1CCA10 &arg_0);
    // Its state at the time arg_4, into arg_0.
    void sub_1DF990(type_1DF990 *arg_0, const type_1CCA10 &arg_4);
    // A debug hook, empty in this build (folded by /OPT:ICF into pDtor,
    // 0x1E41C0).
    void pDtor();
};

// The XHV engine's owner: the engine (unk_0C) for the local talker on port
// unk_E8, the peers' user ids (unk_28, one per peer) and masks of the
// peers registered (unk_14), talking (unk_16), muted by this player
// (unk_18), muting this player (unk_1A), with headsets (unk_1C) and with
// speakers (unk_1E).
struct type_3E3884 : ITitleXHV
{
    DSEFFECTIMAGEDESC *unk_04;
    LPDIRECTSOUND8 unk_08;
    XHVEngine *unk_0C;
    RwInt32 unk_10;             // loopback: the local voice is played back
    type_1DDE20_mask unk_14;
    type_1DDE20_mask unk_16;
    type_1DDE20_mask unk_18;
    type_1DDE20_mask unk_1A;
    type_1DDE20_mask unk_1C;
    type_1DDE20_mask unk_1E;
    RwUInt32 unk_20;            // the peers talking (at most 4)
    type_3E3868 *unk_24;        // where the microphone data goes
    XUID unk_28[16];
    RwUInt32 unk_E8;
    RwInt32 unk_EC;             // whether the local communicator is in
    RwInt32 unk_F0;             // whether the voice goes to the speakers
    RwInt32 unk_F4;             // whether any peer talks
    type_1CCA10 unk_F8;         // when the status was last sent

    type_3E3884();
    ~type_3E3884();
    // An inline accessor for unk_F0, with no address and so no database
    // name; named for its field. Evidence: the front end's speaker query
    // (sub_1C51A0) reads it through a slot of its own.
    RwInt32 get_unk_F0()
    {
        RwInt32 r = unk_F0;
        return r;
    }
    STDMETHOD(LocalChatDataReady)(DWORD dwLocalPort, DWORD dwSize, VOID *pData);
    STDMETHOD(CommunicatorStatusUpdate)(DWORD dwLocalPort, XHV_VOICE_COMMUNICATOR_STATUS communicatorStatus);
    STDMETHOD(SpeechRecognized)(DWORD dwLocalPort, XHV_SR_ITEM *pSRArray, DWORD dwSRItemsCount);
    STDMETHOD(VoiceMailDataReady)(DWORD dwLocalPort, DWORD dwDuration, DWORD dwSize);
    STDMETHOD(VoiceMailStopped)(DWORD dwLocalPort);

    // Starts the engine for port arg_0 (arg_4: loopback); stops it; its
    // step; adds and drops peer arg_0 as a talker; drops them all.
    void sub_1C6C00(RwUInt32 arg_0, RwInt32 arg_4);
    void sub_1C6E70();
    void sub_1C6EC0();
    void sub_1C70D0(RwInt32 arg_0);
    void sub_1C71D0();
    void sub_1C7230(RwInt32 arg_0);
    // Plays peer arg_0's voice data (arg_4, arg_8 bytes).
    void sub_1C7330(RwInt32 arg_0, RwUInt8 *arg_4, RwUInt32 arg_8);
    // Whether the local communicator is in (never while only watching).
    RwInt32 sub_1C73F0();
    // Sets whether the voice goes to the speakers.
    void sub_1C7420(RwInt32 arg_0);
    // Sets peer arg_0's playback priority.
    void sub_1C74A0(RwInt32 arg_0);
    // Takes peer arg_0's status (arg_4; arg_8: send it on); mutes or unmutes
    // peer arg_0 (arg_4); whether peer arg_0 is heard talking.
    bool sub_1C7840(RwInt32 arg_0, type_3E0F54 *arg_4, RwInt32 arg_8);
    bool sub_1C7C70(RwInt32 arg_0, bool arg_4);
    RwInt32 sub_1C7E30(RwInt32 arg_0);
    // Whether peer arg_0 is heard with nothing muting it, and whether it is
    // muted by this machine only: inlines kept out of line by the Live
    // engine's players (their voice status, sub_22AFE0); the tests go
    // through peer_in (types/type_1DDE20_mask.h).
    RwInt32 sub_22B040(RwInt32 arg_0)
    {
        return peer_in(&unk_1C, arg_0) && !peer_in(&unk_1E, arg_0) &&
               !peer_in(&unk_18, arg_0) && !peer_in(&unk_1A, arg_0);
    }
    RwInt32 sub_22B0C0(RwInt32 arg_0)
    {
        return peer_in(&unk_1E, arg_0) && !peer_in(&unk_18, arg_0) && !peer_in(&unk_1A, arg_0);
    }
    // Sets where the microphone data goes: an inline with no address, named
    // for its field. Evidence: the voice manager's sub_1C6920 converts its
    // `this` into a slot below the pad's result local, as an inline's
    // argument gives.
    void set_unk_24(type_3E3868 *arg_0)
    {
        unk_24 = arg_0;
    }
    // An inline accessor with no address and so no database name, named for
    // its field. Evidence: the voice manager's sub_1C6530 copies the mask
    // through a result local.
    type_1DDE20_mask get_unk_14()
    {
        return unk_14;
    }
};

// The voice manager: receives the peers' voice data (vf_000 of the first
// level) and this machine's microphone data (of the second level, kept in
// the ring buffer unk_2688 at unk_304C) and sends the latter every 100
// milliseconds to the peers it hears (unk_267C).
struct type_3E3860 : type_3E386C, type_3E3868
{
    RwInt32 unk_08;             // whether it runs
    type_4F8054 *unk_0C;
    type_3E3860_10 *unk_10;
    type_3E3870 unk_14;
    type_1DDE20_mask unk_267C;  // the peers to send to
    // An inline accessor for unk_267C returned by value, with no address and
    // so no database name; named for its field. Evidence: the send
    // (sub_1C6700) copies it into its argument one register on, as a
    // compiled-out check (docs/toolchain.md) inside the accessor gives.
    type_1DDE20_mask get_unk_267C()
    {
        if (!unk_08)
        {
        }
        return unk_267C;
    }
    type_1DDE20_mask unk_267E;  // the peers in the game
    type_1CCA10 unk_2680;       // when the data was last sent
    type_1CCA10 unk_2684;
    RwUInt8 unk_2688[0x9C4];
    RwUInt32 unk_304C;          // where the microphone data is written
    RwUInt32 unk_3050;          // where it is sent from
    RwUInt32 unk_3054;
    RwUInt32 unk_3058;
    type_1CCA10 unk_305C;
    type_3E3884 unk_3060;
    RwInt32 unk_315C;           // whether the engine runs

    type_3E3860(type_4F8054 *arg_0, type_3E3860_10 *arg_4);
    virtual void vf_000(RwInt32 arg_0, void *arg_4, RwUInt32 arg_8);
    virtual ~type_3E3860();
    virtual void vf_000(RwUInt8 *arg_4, RwUInt32 arg_8);

    // Starts and stops it; its step.
    void sub_1C62B0();
    void sub_1C6300();
    // An inline accessor for unk_08, with no address and so no database
    // name; named for its field. Evidence: the multiplayer manager's
    // shutdown (sub_1A9960) reads it through a slot of its own.
    RwInt32 get_unk_08()
    {
        RwInt32 r = unk_08;
        return r;
    }
    void sub_1C6350();
    void sub_1C6420(const type_1CCA10 &arg_0);
    // Sets the peers to send to.
    void sub_1C6440(const type_1DDE20_mask &arg_0);
    void sub_1C64B0();
    // Follows the peers in the game; sends the microphone data.
    void sub_1C6530();
    void sub_1C6700();
    // Clears the status arg_0 (0xE0 bytes) for the time arg_4.
    void sub_1C6900(struct type_1C6900 *arg_0, const type_1CCA10 &arg_4);
    // Starts and stops the engine (arg_0: loopback).
    void sub_1C6920(RwInt32 arg_0);
    void sub_1C69A0();
    // A debug hook, empty in this build (folded by /OPT:ICF into pDtor,
    // 0x1E41C0).
    void pDtor();
};
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern type_3E3860 *&dword_4F8180;
#else
extern type_3E3860 *dword_4F8180;
#endif
// An accessor for it with no address and so no database name. Evidence:
// the multiplayer menu's slot 15 (sub_20AF50) reads it through a result
// local placed after an earlier inline's.
inline type_3E3860 *get_dword_4F8180()
{
    type_3E3860 *r = dword_4F8180;
    return r;
}

#endif
