/*
 * The network game's message queue (dword_4F8054's unk_AC, type_1D0100):
 * the messages waiting to go out or for their acks, kept in pooled lists
 * (game/poollist.h), and per-peer lists of what came in. Only the widths are
 * known; the names are the database's or the vtables' addresses.
 */
#ifndef GAME_NETQUEUE_H
#define GAME_NETQUEUE_H

#include <new>
#include <string.h>

#include "rw/ostypes.h"
#include "game/pool.h"
#include "game/poollist.h"
#include "types/type_1CCA10.h"
#include "types/type_1DDE20_mask.h"

struct type_4F8054;
struct type_1F8560;

// A queued item (vtable 0x3E4E30): destroyed through its vtable.
struct type_3E4E30
{
    virtual ~type_3E4E30()
    {
    }
};

// A queued message (vtable 0x3E4E34): its handle, the peers it goes to and
// the highest and lowest of them, when it was queued, and two more values.
// Slot 1 takes the message's data (arg_0, arg_4 bytes; 0 when out of
// memory) and slot 2 lets it go.
struct type_3E4E34 : type_3E4E30
{
    RwUInt32 unk_04;
    type_1DDE20_mask unk_08;
    RwUInt8 unk_0A;
    RwUInt8 unk_0B;
    type_1CCA10 unk_0C;
    RwUInt8 *unk_10;            // the data (from a pool)
    RwInt32 unk_14;             // its length in bits

    type_3E4E34()
    {
        unk_10 = 0;
    }
    virtual ~type_3E4E34()
    {
    }
    virtual RwInt32 vf_004(const RwUInt8 *arg_0, RwInt32 arg_4) = 0;
    virtual void vf_008() = 0;
};

// The three kinds of message (vtables 0x3E4E4C, 0x3E4E40 and 0x3E4E58;
// their slots are at 0x1D7A50 on): the second keeps one value per peer, the
// third a time and a value per peer and a flag.
struct type_3E4E4C : type_3E4E34
{
    virtual RwInt32 vf_004(const RwUInt8 *arg_0, RwInt32 arg_4);
    virtual void vf_008();
};
struct type_3E4E40 : type_3E4E34
{
    RwInt32 unk_18[16];

    virtual RwInt32 vf_004(const RwUInt8 *arg_0, RwInt32 arg_4);
    virtual void vf_008();
};
struct type_3E4E58 : type_3E4E34
{
    type_1CCA10 unk_18[16];
    RwInt32 unk_58[16];
    RwUInt8 unk_98;

    virtual RwInt32 vf_004(const RwUInt8 *arg_0, RwInt32 arg_4);
    virtual void vf_008();
};

// An ack waiting to go out (vtable 0x3E4E84): its handle, two times, the
// peers and the highest and lowest of them.
struct type_3E4E84 : type_3E4E30
{
    RwUInt32 unk_04;
    type_1CCA10 unk_08;
    type_1CCA10 unk_0C;
    type_1DDE20_mask unk_10;
    RwUInt8 unk_12;
    RwUInt8 unk_13;
};

// What came in from a peer (0x10 bytes): the data and its length in bits.
// sub_1D7C30 takes a copy of arg_0's arg_4 bits (0 when out of memory);
// sub_1D7CA0 lets it go.
struct type_1D7CA0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwUInt8 *unk_08;
    RwInt32 unk_0C;

    RwInt32 sub_1D7C30(const RwUInt8 *arg_0, RwInt32 arg_4);
    void sub_1D7CA0();
};

// An unordered message seen early (8 bytes): the number before it and its
// own (the unordered receive, sub_1D3C80).
struct type_1D3C80
{
    RwUInt32 unk_00;
    RwUInt32 unk_04;
};

// A pooled list of T. The out-of-line members are shared by every T they
// compile to the same bytes for (/OPT:ICF): destroying every element
// (sub_1D44B0; sub_1D4440 for a T without a virtual destructor), the next
// element (sub_1D0E70), destroying the cursor's element and moving on
// (sub_1D4100), and appending a copy of arg_0 (sub_1D3F80, sub_1D4070,
// sub_1D4150, sub_1D41E0; 0 when out of memory).
template <class T> struct type_1FA230_list : type_1FA230
{
    // From the pool sub_1CBC30 gives (its operator delete is folded by
    // /OPT:ICF into 0x1A9940).
    static void *operator new(size_t arg_0)
    {
        return sub_1CBC30()->sub_1F8BF0(arg_0);
    }
    static void operator delete(void *arg_0)
    {
        sub_1CBC30()->sub_1F8C30(arg_0);
    }
    type_1FA230_list(type_1F8BF0 *arg_0) : type_1FA230(arg_0)
    {
    }
    // It keeps an unused local: the out-of-line copies (sub_1D0AD0,
    // sub_1D4010) have a frame slot no instruction touches.
    ~type_1FA230_list()
    {
        T *p;

        sub_1D44B0();
        sub_1FA2A0();
        sub_1FA5B0();
    }
    T *first()
    {
        unk_08 = unk_00;
        return unk_00 ? (T *)(unk_00 + 1) : 0;
    }
    T *last()
    {
        unk_08 = unk_04;
        return unk_04 ? (T *)(unk_04 + 1) : 0;
    }
    T *current()
    {
        return unk_08 ? (T *)(unk_08 + 1) : 0;
    }
    RwInt32 count()
    {
        return sub_191D80();
    }
    // sub_1D0E70 through an inline, with no address; named for what it
    // does. Evidence: the in-order receive (sub_1D3770) calls it through a
    // `this` slot of its own.
    T *next()
    {
        return sub_1D0E70();
    }
    // sub_1D3F80's body as an inline, with no address; named for what it
    // does. Evidence: the in-order receive (sub_1D3770) appends through a
    // `this` slot with the placement new expanded in place.
    RwInt32 add(const T &arg_0)
    {
        void *p = sub_1FA310(sizeof(T));

        if (p)
        {
            new (p) T(arg_0);
            return 1;
        }
        return 0;
    }
    void empty()
    {
        sub_1D44B0();
        sub_1FA2A0();
    }
    void release()
    {
        sub_1FA5B0();
    }
    T *sub_1D4100()
    {
        current()->~T();
        return (T *)sub_1FA4A0();
    }
    // The node holding the element arg_0: an inline with no address, named
    // for what it gives. Evidence: the packet builder (sub_1D21E0) keeps the
    // element and the node in slots of their own before moving the cursor.
    static type_1FA180_node *node(T *arg_0)
    {
        type_1FA180_node *n;
        T *e = arg_0;

        n = (type_1FA180_node *)e - 1;
        return n;
    }
    void sub_1D44B0();
    T *sub_1D0E70();
    RwInt32 sub_1D3F80(const T &arg_0);
};
// The destructor for the list of type_3E4E40 has no unused local: the
// packet engine's destructor (sub_1D0390), which destroys that list first,
// has no frame slot for it where the other three lists' copies have one.
template <> inline type_1FA230_list<type_3E4E40>::~type_1FA230_list()
{
    sub_1D44B0();
    sub_1FA2A0();
    sub_1FA5B0();
}
// The list of type_1D7CA0's is specialized too (the generic body): the image emits its
// out-of-line copy (sub_1D0AD0) and its EH handler right after its first user,
// type_1D0100::sub_1D07A0, as an ordinary inline function, not with the template
// instances the unit's end collects.
template <> inline type_1FA230_list<type_1D7CA0>::~type_1FA230_list()
{
    type_1D7CA0 *p;

    sub_1D44B0();
    sub_1FA2A0();
    sub_1FA5B0();
}

template <class T> void type_1FA230_list<T>::sub_1D44B0()
{
    first();
    while (sub_1FA590())
    {
        current()->~T();
        sub_1D0E70();
    }
}

template <class T> T *type_1FA230_list<T>::sub_1D0E70()
{
    if (unk_08)
    {
        unk_08 = unk_08->unk_04;
        return unk_08 ? (T *)(unk_08 + 1) : 0;
    }
    return 0;
}

template <class T> RwInt32 type_1FA230_list<T>::sub_1D3F80(const T &arg_0)
{
    void *p;

    p = sub_1FA310(sizeof(T));
    if (p)
    {
        new (p) T(arg_0);
        return 1;
    }
    return 0;
}

// Takes the peers arg_4 out of every message in the list arg_0, destroying
// the messages left with none (their slot 2 first).
// The empty `if (!arg_0->unk_10)` blocks are compiled-out checks; each
// moves the registers after it on by one load (docs/toolchain.md).
template <class T> void sub_1D4530(type_1FA230_list<T> *arg_0, const type_1DDE20_mask &arg_4)
{
    RwInt32 n;
    T *p;

    n = arg_0->sub_191D80();
    if (!n)
        return;
    p = arg_0->first();
    while (n--)
    {
        if (!arg_0->unk_10)
        {
        }
        type_1DDE20_mask m = p->unk_08;

        if (!arg_0->unk_10)
        {
        }
        if (m.overlaps(arg_4))
        {
            if (!arg_0->unk_10)
            {
            }
            m.unk_00 &= ~arg_4.unk_00;
            if (m.empty())
            {
                p->vf_008();
                p = arg_0->sub_1D4100();
                continue;
            }
            p->unk_08 = m;
            p->unk_0B = p->unk_08.sub_1D4900();
            p->unk_0A = p->unk_08.sub_1D48E0();
        }
        p = arg_0->sub_1D0E70();
    }
}

// Sorts the messages in the list arg_0 by peer: arg_4[p] gets up to arg_C
// of the messages for peer p, arg_8[p] their count. sub_1D4770 does the same
// for the acks. Local names state their slots; plain var_N names reorder
// them (docs/toolchain.md).
template <class T> void sub_1D4630(type_1FA230_list<T> *arg_0, T **arg_4[16], RwInt32 *arg_8, RwInt32 arg_C)
{
    RwInt32 stk_40[16];
    RwUInt32 loc44;
    RwUInt32 var_48;
    RwUInt32 loc4c;
    T *lcl_50;
    RwUInt32 y54;
    RwUInt32 u58;

    var_48 = arg_0->sub_191D80();
    memset(stk_40, 0, sizeof(stk_40));
    if (var_48)
    {
        lcl_50 = arg_0->first();
        for (loc4c = 0; loc4c < var_48; loc4c++)
        {
            if (lcl_50)
            {
                y54 = lcl_50->unk_0A;
                u58 = lcl_50->unk_0B;
                for (loc44 = u58; loc44 <= y54; loc44++)
                {
                    if (stk_40[loc44] == arg_C)
                        continue;
                    if (lcl_50->unk_08.test(loc44))
                    {
                        arg_4[loc44][stk_40[loc44]] = lcl_50;
                        stk_40[loc44]++;
                    }
                }
            }
            lcl_50 = arg_0->sub_1D0E70();
        }
    }
    for (loc44 = 0; loc44 < 0x10; loc44++)
        arg_8[loc44] = stk_40[loc44];
}
void sub_1D4770(type_1FA230_list<type_3E4E84> *arg_0, type_3E4E84 **arg_4[16], RwInt32 *arg_8, RwInt32 arg_C);

// The implicit constructor of type_1D0100's unk_4C4 (out of line: its
// members have constructors). Only the widths are known.
struct type_1D02A0
{
    RwInt32 unk_00[4];
    type_1CCA10 unk_10;
    type_1CCA10 unk_14;
    RwInt32 unk_18[5];
    type_1CCA10 unk_2C;
    type_1CCA10 unk_30;
    type_1CCA10 unk_34;
    type_1CCA10 unk_38;
    type_1CCA10 unk_3C;
    RwInt32 unk_40;
    type_1CCA10 unk_44;
    type_1CCA10 unk_48;
    RwInt32 unk_4C;
    RwInt32 unk_50[16];
    type_1CCA10 unk_90[16];
    RwInt32 unk_D0[16];
    RwInt32 unk_110[16];
    RwInt32 unk_150[16];
    RwInt32 unk_190[16];
    RwInt32 unk_1D0[16];
    RwInt32 unk_210[16];
    RwInt32 unk_250[16];
    RwInt32 unk_290[16];
};

// A compiled-out check that kept three locals of its own: the packet
// engine's receive (sub_1D2CC0) has six slots no instruction touches after
// its ack's constructor temporaries, and its registers move on by a load at
// each of the ack block's two checks; addPacket (sub_1D0F60) has twelve
// (docs/toolchain.md). Neither has an
// address or database name; they are named for what they are.
inline void NETQUEUE_CHECK_SLOTS()
{
    RwInt32 check_0;
    RwInt32 check_1;
    RwInt32 check_2;
}
#define NETQUEUE_CHECK(e) \
    { \
        if (!(e)) \
        { \
        } \
        NETQUEUE_CHECK_SLOTS(); \
    }

// A packet's 9-byte check (cleared by its inline constructor); computing it
// over arg_4 bytes at arg_0 is empty in this build (folded by /OPT:ICF into
// sub_73D90).
struct type_1D2CC0_check
{
    RwUInt8 unk_00[9];

    type_1D2CC0_check()
    {
        RwInt32 i;

        for (i = 0; i < 9; i++)
            unk_00[i] = 0;
    }
    void sub_73D90(const RwUInt8 *arg_0, RwUInt32 arg_4);
    // Comparing with arg_0 gives 1 in this build (folded by /OPT:ICF into
    // sub_1F5A00).
    RwInt32 sub_1F5A00(const type_1D2CC0_check *arg_0);
    // Whether it differs from arg_0: an inline with no address, named for
    // what it does. Evidence: the packet engine's receive (sub_1D2CC0)
    // tests the negated comparison straight from its flags.
    RwInt32 operator!=(const type_1D2CC0_check &arg_0)
    {
        return !sub_1F5A00(&arg_0);
    }
};

// The network game's first part (0x7A0 bytes, from the pool sub_1CBC30
// gives): the four lists of queued messages and acks, what came in from each
// peer, the buffers messages are built in, and the peers' times.
struct type_1D0100
{
    type_1FA230_list<type_3E4E4C> unk_04;
    type_1FA230_list<type_3E4E58> unk_1C;
    type_1FA230_list<type_3E4E84> unk_34;
    type_1FA230_list<type_3E4E40> unk_4C;
    type_1FA230_list<type_1D7CA0> *unk_64[16];
    RwInt32 unk_A4[16];
    type_1FA230_list<type_1D3C80> *unk_E4[16];
    RwInt32 unk_124[16];
    RwUInt8 *unk_164;           // the packet buffers
    RwUInt8 *unk_168;
    RwInt32 unk_16C;
    RwInt32 unk_170;
    RwInt32 unk_174;
    RwInt32 unk_178;
    RwInt32 unk_17C;
    type_3E4E4C **unk_180[16];
    RwInt32 unk_1C0[16];
    type_3E4E58 **unk_200[16];
    RwInt32 unk_240[16];
    type_3E4E84 **unk_280[16];
    RwInt32 unk_2C0[16];
    type_3E4E40 **unk_300[16];
    RwInt32 unk_340[16];
    RwInt32 unk_380[16];
    RwInt32 unk_3C0[16];
    RwInt32 unk_400[16];
    type_1CCA10 unk_440[16];
    type_1CCA10 unk_480[16];    // when each peer was last heard from
    type_1CCA10 unk_4C0;
    type_1D02A0 unk_4C4;
    RwInt32 unk_794;
    type_1DDE20_mask unk_798;
    type_4F8054 *unk_79C;

    type_1D0100();
    virtual ~type_1D0100();
    static void *operator new(size_t arg_0)
    {
        return sub_1CBC30()->sub_1F8BF0(arg_0);
    }
    static void operator delete(void *arg_0)
    {
        sub_1CBC30()->sub_1F8C30(arg_0);
    }
    void sub_1D04B0(type_4F8054 *arg_0);
    // An inline returning 0 through a local, with no address; named for
    // what it returns. Evidence: the queue's init (sub_1D04B0) shifts by a
    // 0 kept in a slot among the inlines' locals.
    RwInt32 zero()
    {
        RwInt32 r = 0;
        return r;
    }
    void sub_1D07A0();
    // What the message with the handle arg_0 is still waiting on, and the
    // same while dropping it (the players' join steps).
    type_1DDE20_mask sub_1D17B0(RwInt32 arg_0);
    type_1DDE20_mask sub_1D18E0(RwInt32 arg_0);
    // Inline, named for its field: when peer arg_0 was last heard from
    // (handlePossibleDisconnections reads it through a slot of its own).
    type_1CCA10 get_unk_480(RwInt32 arg_0)
    {
        return unk_480[arg_0];
    }
    // Drops the peers arg_0 (the players' sub_1CFC20).
    void sub_1D0B30(const type_1DDE20_mask &arg_0);
    void sub_1D0EC0();
    // The ack with the handle arg_0 that still goes to peer arg_4 (0 for
    // none); peer arg_4 has the timed message arg_0, which is dropped once
    // every peer has it.
    type_3E4E84 *sub_1D1A30(RwInt32 arg_0, RwInt32 arg_4);
    void sub_1D1AE0(RwInt32 arg_0, RwInt32 arg_4);
    // Its step at the time arg_0, and each peer's (sub_1D1C30).
    void sub_1D3610(const type_1CCA10 &arg_0);
    void sub_1D1C30(RwInt32 arg_0, const type_1CCA10 &arg_4);
    // Peer arg_8's message number arg_0 (arg_4 its first) of arg_10 bits in
    // the stream arg_C, handed on in order (its trace: "receive in order").
    void sub_1D3770(RwUInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10);
    // The same for an unordered message (its trace: "receive unordered").
    void sub_1D3C80(RwUInt32 arg_0, RwUInt32 arg_4, RwInt32 arg_8, type_1F8560 *arg_C, RwInt32 arg_10);
    // Peer arg_0's packet of arg_8 bytes at arg_4 (and arg_C when arg_10 is
    // set): its check, its acks, its guaranteed, unreliable and extra
    // messages; 0 when it is dropped.
    RwInt32 sub_1D2CC0(RwInt32 arg_0, RwUInt8 *arg_4, RwUInt32 arg_8, RwUInt8 *arg_C, RwInt32 arg_10);
    // Builds and sends peer arg_0's packet from its due messages (plain,
    // timed resends, acks and per-peer ones, each with a count) at the time
    // arg_34.
    void sub_1D21E0(RwInt32 arg_0, RwInt32 arg_4, type_3E4E4C **arg_8, RwInt32 arg_C, RwInt32 arg_10,
                    type_3E4E58 **arg_14, RwUInt32 arg_18, RwInt32 arg_1C, type_3E4E84 **arg_20, RwInt32 arg_24,
                    RwInt32 arg_28, type_3E4E40 **arg_2C, RwInt32 arg_30, const type_1CCA10 &arg_34);
    RwInt32 sub_1D0F60(const type_1DDE20_mask &arg_0, type_1F8560 *arg_4, RwInt32 arg_8, const type_1CCA10 &arg_C,
                       RwInt32 arg_10);
};

#endif
