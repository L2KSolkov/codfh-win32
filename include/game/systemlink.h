/*
 * The system link host search (CSystemLinkQuery, named by its trace
 * "CSystemLinkQuery::Query() : ..."): cXboxLive (types in game/voice.h) keeps
 * one at +0x18C4. It broadcasts a probe through the network system's socket
 * and keeps up to 25 of the hosts that answer with its nonce, handing out
 * their addresses, session ids and keys like an XOnline match search.
 *
 * Only the widths are known where no comment says more.
 */
#ifndef GAME_SYSTEMLINK_H
#define GAME_SYSTEMLINK_H

#include <xtl.h>
#include <xonline.h>

#include "rw/ostypes.h"
#include "types/type_1CCA10.h"

// The network system's datagram socket, cXboxSocket (named by its traces,
// "cXboxSocket::create()" and the rest; cXboxLive keeps two, at +0x2934 and
// +0x3370): the system link one (type 2) broadcasts on port 1001, the game
// one (VDP, type 1) sends a game message and a voice message in one packet
// (the game message's size first). Its destructor is empty and folded
// (/OPT:ICF) into sub_1E41C0.
struct cXboxSocket
{
    RwUInt32 unk_00;            // its type (1 VDP, 2 system link)
    SOCKET unk_04;              // INVALID_SOCKET while closed
    RwUInt16 unk_08;            // a packet: the game message's size,
    RwUInt8 unk_0A[0xA30];      // then the game and voice messages
    RwUInt8 unk_A3A[2];

    cXboxSocket();
    ~cXboxSocket();
    // Whether it is open: an inline with no address, named for what it
    // does. Evidence: the query (CSystemLinkQuery::Query) tests the
    // comparison as a value.
    RwInt32 is_open()
    {
        return unk_04 != INVALID_SOCKET;
    }
    // Opens it as the type arg_0 (0 when it fails), and closes it.
    RwInt32 create(RwUInt32 arg_0);
    void sub_1DC130();
    // Whether a datagram waits, and receives one: the game message into
    // arg_0 (arg_4 bytes at most), the voice message into arg_8 (arg_C
    // bytes), their sizes into arg_10 and arg_14 and the sender into arg_18;
    // 0 when it failed.
    RwInt32 incomingMessageWaiting();
    RwInt32 receiveMessage(RwUInt8 *arg_0, RwInt32 arg_4, RwUInt8 *arg_8, RwInt32 arg_C, RwInt32 *arg_10,
                           RwInt32 *arg_14, sockaddr_in *arg_18);
    // Broadcasts arg_4 bytes at arg_0 (0 when it fails).
    RwInt32 broadcast(const RwChar *arg_0, RwInt32 arg_4);
    // Sends the game message arg_0 (arg_4 bytes) and the voice message arg_8
    // (arg_C bytes) to arg_10 (0 when it fails).
    RwInt32 sendMessage(const void *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, const sockaddr_in *arg_10);
    // The last error's text, and the socket closed after the errors it
    // cannot recover from.
    const RwChar *sub_1DC5C0();
    void sub_1DC600();
};

// The Winsock errors' texts (unk_42CD30, ended by a code of 0).
struct type_42CD30
{
    RwInt32 unk_00;
    const RwChar *unk_04;
};

// The probe broadcast by the query (0x60 bytes): 0xFFFF, the query's nonce
// and five match attributes.
struct type_1D7DD0_probe
{
    RwUInt8 unk_00[2];
    RwUInt8 unk_02[8];          // the nonce
    RwUInt8 unk_0A[6];
    XONLINE_ATTRIBUTE unk_10[5];
};

#pragma pack(push, 1)

// A host's answer: the nonce it was sent, its session, and its attributes
// and name.
struct type_1D8140_reply
{
    RwUInt8 unk_00[2];
    RwUInt8 unk_02[8];          // the probe's nonce
    XNKID unk_0A;
    XNKEY unk_12;
    XNADDR unk_22;
    RwUInt8 unk_46[2];
    XONLINE_ATTRIBUTE unk_48[5];
    WCHAR unk_98[16];           // the host's name
    RwInt32 unk_B8;
    RwUInt8 unk_BC[4];
};

// A host found (0x9A bytes).
struct type_1D8140_host
{
    ULONGLONG unk_00;           // the reply's first attribute
    ULONGLONG unk_08;           // its second
    ULONGLONG unk_10;           // its fourth
    RwUInt8 unk_18[0x10];
    WCHAR unk_28[17];           // the host's name
    XNKID unk_4A;
    XNKEY unk_52;
    XNADDR unk_62;
    RwInt32 unk_86;             // the third attribute less unk_8E
    RwInt32 unk_8A;
    RwInt32 unk_8E;             // the reply's unk_B8
    RwInt32 unk_92;
    XNQOSINFO *unk_96;          // the host's QoS results once probed
};

#pragma pack(pop)

// A player's user id as cXboxLive's block list keeps it (16 of them,
// searched by sub_1DBED0): sub_1D8370 is whether its user id is arg_0's.
struct type_1D8370 : XUID
{
    bool sub_1D8370(const XUID *arg_0) const;
};

struct CSystemLinkQuery
{
    type_1D8140_host unk_000[25];
    RwInt32 unk_F0C;            // the hosts found
    XNADDR *unk_F10[25];        // each host's address, session id and key
    XNKID *unk_F74[25];
    XNKEY *unk_FD8[25];
    cXboxSocket *unk_103C;      // the socket it broadcasts through
    type_1CCA10 unk_1040;       // when it was sent
    RwUInt8 unk_1044[8];        // its nonce
    RwInt32 unk_104C;           // 0 idle, 1 waiting for answers, 2 done
    HRESULT unk_1050;           // what a finished poll gives (S_FALSE)

    CSystemLinkQuery();
    ~CSystemLinkQuery();
    // An inline accessor for unk_F0C, with no address and so no database
    // name; named for its field. Evidence: cXboxLive's sub_1D9270 reads it
    // through a slot of its own.
    RwInt32 get_unk_F0C()
    {
        return unk_F0C;
    }
    // Stops it, forgetting the hosts.
    void sub_1D7D60();
    void sub_1D7DB0();
    HRESULT Query(cXboxSocket *arg_0, LONGLONG arg_4, LONGLONG arg_C, LONGLONG arg_14, LONGLONG arg_1C,
                  LONGLONG arg_24);
    // XONLINETASK_S_SUCCESS once half a second has passed since the probe.
    HRESULT sub_1D8060();
    // Takes the datagram arg_0 (a host's answer) while it waits.
    HRESULT sub_1D80F0(const RwUInt8 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    void sub_1D8140(const RwUInt8 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
};

#endif
