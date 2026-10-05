/*
 * cXboxLive (named by its traces, "cXboxLive::createSession()" and the
 * rest; unit_1D7CE0): the network system, one instance (sub_1D8810 gives
 * it, unk_4FED00). It starts the Xbox online library, creates and joins
 * sessions over Xbox Live or the system link, and keeps the peers'
 * connections, the block list and the voice peers.
 *
 * Only the widths are known where no comment says more.
 */
#ifndef TYPES_CXBOXLIVE_H
#define TYPES_CXBOXLIVE_H

#include <xtl.h>
#include <xonline.h>

#include "rw/ostypes.h"
#include "types/type_1CCA10.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_DC400.h"
#include "game/systemlink.h"

// A blob attribute (the MatchSim sample's CBlob, as match.h declares it):
// its length and data.
class CBlob
{
public:
    CBlob() : m_wLength(0), m_pvData(NULL)
    {
    }
    __declspec(property(get = GetData)) const PVOID Data;
    const PVOID GetData() const
    {
        return m_pvData;
    }
    __declspec(property(get = GetLength)) WORD Length;
    WORD GetLength() const
    {
        return m_wLength;
    }

private:
    WORD m_wLength;
    PVOID m_pvData;
};

// The Xbox Live session, CSession (0x100 bytes, at cXboxLive +0x778): the
// XDK's MatchSim generates it (the sample SimpleConnect's match.h and
// match.cpp hold the same class, member for member, with one attribute; the
// names are the sample's). The game's has nine attributes and a sixth state
// (a session that failed to be created). The attributes' accessors keep
// their addresses' names: MatchSim names them after the title's attributes,
// which the image does not give.
struct CSession
{
    CSession();
    ~CSession();

    HRESULT Create();
    HRESULT Update();
    HRESULT Delete();
    HRESULT Process();

    void Reset();

    DWORD PublicFilled;
    DWORD PublicOpen;
    DWORD PrivateFilled;
    DWORD PrivateOpen;
    XNKEY KeyExchangeKey;
    XNKID SessionID;

    BOOL IsUpdating() const
    {
        return m_State == STATE_UPDATING;
    }
    BOOL Exists() const
    {
        return m_State == STATE_ACTIVE || IsUpdating();
    }

    void Listen(BOOL bEnable = TRUE, DWORD dwBitsPerSec = 0);
    static const DWORD NO_WAIT = 1;

    // The integer attributes (1 to 8; 6 and 7 have no getters) and the
    // name (attribute 9, a string).
    ULONGLONG sub_1DCF20();
    void sub_1DCF40(ULONGLONG arg_0);
    ULONGLONG sub_1DCF70();
    void sub_1DCF90(ULONGLONG arg_0);
    ULONGLONG sub_1DCFC0();
    void sub_1DCFE0(ULONGLONG arg_0);
    ULONGLONG sub_1DD010();
    void sub_1DD030(ULONGLONG arg_0);
    ULONGLONG sub_1DD060();
    void sub_1DD080(ULONGLONG arg_0);
    void sub_1DD0B0(ULONGLONG arg_0);
    void sub_1DD0E0(ULONGLONG arg_0);
    ULONGLONG sub_1DD110();
    void sub_1DD130(ULONGLONG arg_0);
    void SetName(const WCHAR *Value);

    // The session ids still answering QoS probes (with "go away") after
    // the session stopped listening.
    struct QosQEntry
    {
        XNKID SessionID;
        DWORD dwStartTick;
        QosQEntry *pNext;
    };
    struct CSessionQosQ
    {
        CSessionQosQ();
        void Add(XNKID &SessionID, DWORD dwStartTick);
        void Remove(XNKID &SessionID);
        void Dequeue();
        const QosQEntry *Head() const
        {
            return m_pHead;
        }

        QosQEntry *m_pHead;
        QosQEntry *m_pTail;
    };

    XONLINE_ATTRIBUTE m_Attributes[9];
    WCHAR m_strName[18];
    CSessionQosQ m_SessionQosQ;
    BOOL m_bListening;
    CBlob m_QosResponse;

    void PurgeSessionQ(BOOL fRemoveAll = FALSE);
    void PurgeSessionQHead();

    HRESULT ProcessStateCreateSession();
    HRESULT ProcessStateUpdateSession();
    HRESULT ProcessStateDeleteSession();
    HRESULT ProcessStateActiveSession();

    void Close();
    void SetupAttributes();

    XONLINETASK_HANDLE m_hSessionTask;

    enum STATE
    {
        STATE_IDLE,
        STATE_CREATING,
        STATE_UPDATING,
        STATE_DELETING,
        STATE_ACTIVE,
        STATE_5                 // the game's: creating it failed
    };

    STATE m_State;
    BOOL m_bKeyRegistered;
    BOOL m_bUpdate;
};

// The Xbox Live match search's results (the MatchSim sample's
// CQuickmatchQueryResults): up to 25 sessions and their count.
struct CQuickmatchQueryResults
{
    CQuickmatchQueryResults()
    {
        m_dwSize = 0;
    }
    DWORD Size()
    {
        return m_dwSize;
    }
    type_1D8140_host &operator[](DWORD i)
    {
        return v[i];
    }
    void Clear()
    {
        m_dwSize = 0;
    }
    void Remove(DWORD i);
    void SetSize(DWORD dwSize)
    {
        m_dwSize = dwSize;
    }

    type_1D8140_host v[25];
    DWORD m_dwSize;
};

// The Xbox Live match search, CQuickmatchQuery (0x104C bytes, at cXboxLive
// +0x878): the MatchSim sample's class (SimpleConnect's match.h), its
// names; the game's query takes eight integer arguments and returns five
// integer attributes before the name.
struct CQuickmatchQuery
{
    CQuickmatchQuery();
    ~CQuickmatchQuery();
    CQuickmatchQueryResults Results;

    HRESULT Process();
    void Cancel();
    void Clear();
    HRESULT Query(ULONGLONG arg_0, ULONGLONG arg_8, ULONGLONG arg_10, ULONGLONG arg_18, ULONGLONG arg_20,
                  ULONGLONG arg_28, ULONGLONG arg_30, ULONGLONG arg_38);

    const XNADDR *m_rgpXnAddr[25];
    const XNKID *m_rgpXnKid[25];
    const XNKEY *m_rgpXnKey[25];
    XNQOS *m_pXnQos;
    enum STATE
    {
        STATE_IDLE,
        STATE_RUNNING,
        STATE_PROBING_CONNECTIVITY,
        STATE_PROBING_BANDWIDTH,
        STATE_DONE
    };

    STATE m_State;
    HRESULT m_hrQuery;
    XONLINETASK_HANDLE m_hSearchTask;
};

// The block list (0xC8 bytes, at cXboxLive +0x40DC): up to 16 user ids, a
// ring (the newest replaces the oldest), their count and the next slot;
// sub_1DBED0 is whether it holds arg_0's.
struct type_1DBE00
{
    type_1D8370 unk_00[16];
    RwUInt32 unk_C0;            // the user ids held
    RwUInt32 unk_C4;            // the slot the next one takes

    type_1DBE00();
    // Empties it, and adds arg_0.
    void sub_1DBF20();
    void sub_1DBE30(const XUID *arg_0);
    bool sub_1DBED0(const XUID *arg_0);
};

// A player to connect to, as the network game gives it: its name and its
// address (the bytes of its IP address and its port).
struct type_1D9C30_peer
{
    RwChar unk_00[0x18];        // its name
    RwUInt8 unk_18[4];          // its IP address, a byte each
    RwUInt8 unk_1C[4];
    RwUInt16 unk_20;            // its port
};

// A session found, as the game gets it (0x74 bytes, sub_1D9270).
// The session's +0x30: a dword whose constructor zeroes it. Evidence: the
// late service's constructor (sub_2261C0) builds its session (unk_04)
// through two inline constructors' `this` slots, the inner one at +0x30
// storing 0.
struct type_1D9270_session_30
{
    RwInt32 unk_00;

    type_1D9270_session_30()
    {
        unk_00 = 0;
    }
};

struct type_1D9270_session
{
    RwUInt32 unk_00;            // its size
    RwUInt8 unk_04[0xC];
    RwChar unk_10[0x18];        // the host's name
    RwUInt8 unk_28;
    RwUInt8 unk_29;
    RwUInt8 unk_2A;
    RwUInt8 unk_2B;
    RwUInt8 unk_2C;
    RwUInt8 unk_2D[3];
    type_1D9270_session_30 unk_30; // what the instant action's score falls with
    RwUInt8 unk_34;             // set: it can be joined
    RwUInt8 unk_35[3];
    XNADDR unk_38;
    XNKID unk_5C;
    XNKEY unk_64;
};

// Takes peer arg_4 out of the mask arg_0: an inline with no address, named
// for what it does. Evidence: cXboxLive's sub_1DA4D0 keeps the peer and the
// mask in slots allocated with the inlines' (after an operator's local),
// the peer stored first.
inline void mask_remove(type_1DDE20_mask *arg_0, RwInt32 arg_4)
{
    RwInt32 i = arg_4;
    type_1DDE20_mask *m = arg_0;

    // Two compiled-out checks (docs/toolchain.md).
    if (!m->unk_00)
    {
    }
    if (!m->unk_00)
    {
    }
    m->unk_00 &= ~(1 << i);
}

#pragma pack(push, 1)

// A host's address, session id and key, packed (at cXboxLive +0x41A6).
struct type_1D8900_host
{
    XNADDR unk_00;
    XNKID unk_24;
    XNKEY unk_2C;
};

#pragma pack(pop)

struct cXboxLive
{
    XONLINE_USER unk_000[16];   // the players
    XONLINE_USER unk_700;       // this machine's player (sub_1DBD40)
    RwInt32 unk_770;
    XONLINETASK_HANDLE unk_774; // the logon task
    CSession unk_778;
    CQuickmatchQuery unk_878;
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
    cXboxSocket unk_2934;
    cXboxSocket unk_3370;
    RwUInt32 unk_3DAC;          // flags (bit 3: the online library started)
    type_4F8054 *unk_3DB0;      // the network game (the manager's set-up)
    sockaddr_in unk_3DB4[16];   // each peer's address
    XUID unk_3EB4[16];          // the players' user ids
    XUID unk_3F74[16];          // the user ids of the players who left
    type_1DDE20_mask unk_4034;
    RwInt32 unk_4038;           // the join's state (1 waiting, 3 failed)
    RwInt32 unk_403C;           // why it failed (2 and 3 have their own
                                // errors)
    XNKID unk_4040;             // the session's id (its key registered while
                                // unk_3DAC bit 2 is set)
    type_1CCA10 unk_4048[16];
    type_1CCA10 unk_4088[16];
    RwUInt32 unk_40C8;
    RwChar unk_40CC[16];        // the system link host's name
    type_1DBE00 unk_40DC;
    type_1DDE20_mask unk_41A4;
    type_1D8900_host unk_41A6;

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
    // createSession (its trace): the session takes a public slot, or else a
    // private one, and this machine's gamertag as its name; whether it was
    // created.
    RwInt32 sub_1D8C00();
    RwInt32 sub_1D9610(bool arg_0);
    void sub_1DB920(const RwChar *arg_0);
    RwInt32 sub_1D8E10();
    // joinServer (its traces): the host at arg_0 with the session arg_4 and
    // key arg_8, at the time arg_C (arg_10 set for a private slot); 1 when
    // the join request went out.
    RwInt32 sub_1D9700(XNADDR *arg_0, XNKID *arg_4, XNKEY *arg_8, const type_1CCA10 &arg_C, RwInt32 arg_10);
    // peerConnectToNewPlayer (its trace): asks the player arg_4 at the
    // time arg_8 to connect as peer arg_0; 0 when the request failed.
    RwInt32 sub_1D9C30(RwInt32 arg_0, type_1D9C30_peer *arg_4, const type_1CCA10 &arg_8);
    // Its step at the time arg_0: the sockets and the connection attempts,
    // then the logon, the session's creation or end, and the search.
    void sub_1DBA80(const type_1CCA10 &arg_0);
    // A join request from arg_8 (the message arg_0): the host accepts it
    // into a free peer slot (a private one when asked and open), or
    // rejects it (2 blocked, 1 full).
    void sub_1DA6D0(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8);
    // The host's accept (sub_1DAA60: this machine joins as the peer the
    // message names) and reject (sub_1DABA0: the join fails for the reason
    // it gives) as a peer gets them from arg_8.
    void sub_1DAA60(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8);
    void sub_1DABA0(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8);
    // Another peer's connection request (sub_1DACB0), accept (sub_1DAF00)
    // and reject (sub_1DB060), as a peer gets them from arg_8.
    void sub_1DACB0(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8);
    void sub_1DAF00(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8);
    void sub_1DB060(const RwUInt8 *arg_0, RwInt32 arg_4, const sockaddr_in *arg_8);
    // Blocks the player arg_0 (its trace).
    void sub_1DA680(XUID arg_0);
    // disconnectPlayer (its trace): peer arg_0's connection and slot freed.
    void sub_1D9DD0(RwInt32 arg_0);
    void sub_1D8B40(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    void sub_1DA170();
    // The search for sessions matching arg_0 over Xbox Live (sub_1D8EE0; a
    // field of -1 matches anything) or the system link (sub_1D9100), for up
    // to arg_8 bytes of results at arg_4 (sub_1D9270); whether it started.
    RwInt32 sub_1D8EE0(struct type_4F8054_4C *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    RwInt32 sub_1D9100(struct type_4F8054_4C *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Stops the search.
    RwInt32 sub_1D9090();
    RwInt32 sub_1D91E0();
    // The sessions the search found, copied into the buffer the search was
    // given (as many as fit; their count into arg_0).
    type_1D9270_session *sub_1D9270(RwUInt32 *arg_0);
    void sub_1DB900(RwInt32 arg_0);
    // Its state set to 0, 1, 2 and 3 (sub_1DB950, sub_1DB970, sub_1DBA00,
    // sub_1DBA20), and to 4 with this machine's player taken from the first
    // signed-in user (sub_1DB990).
    void sub_1DB950();
    void sub_1DB970();
    void sub_1DBA00();
    void sub_1DBA20();
    void sub_1DB990();
    // Leaves the session: everything about it forgotten.
    void sub_1D8900();
    void sub_1DBA40(RwInt32 arg_0, RwInt32 arg_4);
    // The connection attempts at the time arg_0: one unanswered for 10
    // seconds times out (the join fails, or the peer is dropped), one
    // unanswered for 750 ms is sent again.
    void sub_1DA4D0(const type_1CCA10 &arg_0);
    // The connection is lost: the session left, the player forgotten and
    // the network game's error 7 set (sub_1DA230); peer arg_0 is lost
    // (sub_1DA1D0).
    void sub_1DA230();
    void sub_1DA1D0(RwUInt32 arg_0);
    XONLINE_USER *sub_1DBD40();
    // The connected peer at the address arg_0 (16 when there is none).
    RwUInt32 sub_1D9970(const sockaddr_in *arg_0);
    // Takes in what the sockets received: the system link socket's datagrams
    // (sub_1DB250), and the game socket's handshakes (0xFF first, sub_1DB180)
    // and peers' packets (the packet engine's receive).
    void sub_1D9A10();
    void sub_1DB250(RwUInt8 *arg_0, RwInt32 arg_4, sockaddr_in *arg_8);
    void sub_1DB180(RwUInt8 *arg_0, RwInt32 arg_4, sockaddr_in *arg_8);
    // The session key's text (sub_1DA070: 16 random characters, made once,
    // "2357111317192329" until then); an IP address's bytes to an XNADDR and
    // back (sub_1DA0C0, sub_1DA110); ends the session unless it is being
    // made (sub_1DA170).
    const RwChar *sub_1DA070();
    RwInt32 sub_1DA0C0(const RwUInt8 *arg_0, XNADDR *arg_4);
    RwInt32 sub_1DA110(const XNADDR *arg_0, RwUInt8 *arg_4);
    // The handshake messages to the peer at arg_0 (0xFF first; 0 when they
    // could not be sent): the join request (sub_1DA270, arg_4 set) or the
    // host's reply, the accept (sub_1DA350) and the reject (sub_1DA430, a
    // reason arg_4).
    RwInt32 sub_1DA270(const sockaddr_in *arg_0, RwInt32 arg_4, RwInt32 arg_8);
    RwInt32 sub_1DA350(const sockaddr_in *arg_0, RwInt32 arg_4);
    RwInt32 sub_1DA430(const sockaddr_in *arg_0, RwInt32 arg_4);
    // Whether the session is over the system link and whether the voice
    // runs: inlines with no address, named for what they give. Evidence:
    // the search's stop and poll (sub_1D9090, sub_1D91E0) test each as a
    // bool.
    bool is_system_link()
    {
        return (unk_3DAC & 0x20) ? 1 : 0;
    }
    bool voice_running()
    {
        return unk_2918 == 4;
    }
    // Likewise for state 1, named for its field. Evidence: in-game menu 12's
    // update (sub_20A700) tests it as a bool beside voice_running().
    bool unk_2918_is_1()
    {
        return unk_2918 == 1;
    }
    // A compiled-out check (docs/toolchain.md) as an inline, with no address,
    // named for what it is. Evidence: the send (sub_1D8B40) moves the
    // registers on by a load between the two halves of its peer test.
    void check()
    {
        if (!unk_3DAC)
        {
        }
    }
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
    // Inline too, named for its field. Evidence: the late service's frame,
    // notification state and join (sub_2266D0, sub_227AC0, sub_227D70) copy
    // the session's id out through a `this` copy.
    XNKID get_unk_4040()
    {
        return unk_4040;
    }
    // Inline too, named for its field. Evidence: the late service's
    // notification state (sub_227AC0) reads the flags through a `this` copy.
    RwUInt32 get_unk_3DAC()
    {
        return unk_3DAC;
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
