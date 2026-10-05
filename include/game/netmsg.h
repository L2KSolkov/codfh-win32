/*
 * A network message as the pulse zones' damage effect (sub_17DBD0) builds
 * one on its stack: a class of three levels (vtables off_3DA44C, all pure;
 * off_3DA440, its third slot sub_115460; off_3DA434, its first two
 * sub_1C5920 and sub_1C5970), each constructor inline. The multiplayer
 * manager (unk_4F7EB8) hands out what it is sent with (sub_1AEC70) and
 * sub_1ACBA0 sends it. Only the widths are known.
 */
#ifndef GAME_NETMSG_H
#define GAME_NETMSG_H

#include <string>

#include "rw/ostypes.h"
#include "types/type_1DDE20_mask.h"
#include "types/type_505188.h"
#include "types/type_10F710.h"
#include "types/type_3D32F8.h"
#include "types/type_3D94B8.h"
#include "game/netstate.h"
#include "game/netvec.h"
#include "game/netlisten.h"
#include "game/netscore.h"
#include "game/netqueue.h"

// The bit stream's words (big-endian, read and written through inline
// assembly that swaps their bytes, so they stay binary: docs/PLAN.md):
// arg_C bits at the bit arg_8 of the words at arg_0, read (sub_1F81E0) and
// written (sub_1F8300, the value arg_C in arg_10 bits); arg_4, the stream's
// size, is not used. How many
// bits arg_0 needs (sub_1F84A0, through the table unk_42D25C for the last
// four).
RwUInt32 sub_1F81E0(RwUInt32 *arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C);
void sub_1F8300(RwUInt32 *arg_0, RwUInt32 arg_4, RwUInt32 arg_8, RwUInt32 arg_C, RwUInt32 arg_10);
extern RwUInt8 unk_42D25C[16];
// A compiled-out check of the bit stream: no code, but its registers move
// on by the loads its condition would make (docs/toolchain.md). The
// conditions are not known; they are chosen for their loads.
#define BITSTREAM_CHECK(e) { if (!(e)) { } }

// The bit stream a message is written to and read from: a bit, a float, a
// value of arg_4 bits, a signed one, one in a range, a message number and
// bytes, each written and read (unit_1F81E0).
struct type_1F8560
{
    RwUInt8 *unk_00;            // the buffer
    RwUInt32 unk_04;            // its size in bits
    RwUInt32 unk_08;            // the bit position

    // Inline, with no addresses: empty, and over the buffer arg_0 of arg_4
    // bits. Evidence: the packet engine's in-order receive (sub_1D3770)
    // builds one over a kept message's data, the position cleared before
    // the size.
    type_1F8560()
    {
    }
    type_1F8560(RwUInt8 *arg_0, RwUInt32 arg_4)
    {
        if (!(arg_4 & 1))
        {
        }
        if (!(arg_4 & 1))
        {
        }
        unk_00 = arg_0;
        unk_08 = 0;
        unk_04 = arg_4;
    }
    // Inline, with no address: over the bytes arg_0 of arg_4 bits, with
    // room for the two words a read reaches past its bits. Evidence: the
    // bytes' write and read (sub_1F89D0, sub_1F8A40) store the padded size
    // last, with the size checks' register shift and no temporary.
    type_1F8560(const void *arg_0, RwUInt32 arg_4)
    {
        if (!(arg_4 & 1))
        {
        }
        if (!(arg_4 & 1))
        {
        }
        unk_00 = (RwUInt8 *)arg_0;
        unk_08 = 0;
        unk_04 = arg_4 + 64;
    }
    // An inline accessor for unk_00, with no address and so no database
    // name; named for its field. Evidence: the packet engine's addPacket
    // (sub_1D0F60) reads it through a slot of its own.
    RwUInt8 *get_unk_00()
    {
        return unk_00;
    }

    void sub_1F85F0(RwReal arg_0);
    RwReal sub_1F85A0();
    void sub_1F8860(RwUInt32 arg_0, RwInt32 arg_4);
    RwUInt32 sub_1F8810(RwInt32 arg_0);
    // The same for a signed value.
    void sub_1F87B0(RwInt32 arg_0, RwInt32 arg_4);
    RwInt32 sub_1F8750(RwInt32 arg_0);
    // A value from arg_4 to arg_8 in arg_C bits (sub_1F86D0), and read
    // back (sub_1F8640).
    void sub_1F86D0(RwReal arg_0, RwReal arg_4, RwReal arg_8, RwInt32 arg_C);
    RwReal sub_1F8640(RwReal arg_0, RwReal arg_4, RwInt32 arg_8);
    // A whole number from arg_4 to arg_8, written and read.
    void sub_1F8B90(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    RwInt32 sub_1F8B30(RwInt32 arg_0, RwInt32 arg_4);
    // A bit, written and read.
    void sub_1F8520(RwUInt32 arg_0);
    RwUInt32 sub_1F8560();
    // A number in as many nibbles as it needs (their count less one in
    // three bits first), and a signed one (its sign bit first), written
    // (the packet engine's builder, sub_1D21E0: a message number and a
    // delta).
    void sub_1F88A0(RwUInt32 arg_0);
    void sub_1F8AB0(RwInt32 arg_0);
    // The same read back (the packet engine's receive, sub_1D2CC0).
    RwInt32 sub_1F8950();
    RwInt32 sub_1F8AF0();
    // An inline accessor for unk_08, with no address and so no database
    // name; named for its field. Evidence: the packet engine's builder
    // (sub_1D21E0) reads the position through a slot of its own.
    RwUInt32 get_unk_08()
    {
        RwUInt32 r = unk_08;
        return r;
    }
    // arg_4 bits of the bytes at arg_0, written and read.
    void sub_1F89D0(const void *arg_0, RwInt32 arg_4);
    void sub_1F8A40(RwChar *arg_0, RwInt32 arg_4);
};

// A bit stream over a buffer of its own, BYTES long, of BITS bits: an inline
// class with no address. Evidence: the network game's messages
// (sNetGameEP.cpp) build one on the stack, the buffer after the stream and
// the position cleared before the size.
template <RwUInt32 BYTES, RwUInt32 BITS>
struct type_1F8560_buf : type_1F8560
{
    RwUInt32 unk_0C[BYTES / 4];

    type_1F8560_buf()
    {
        unk_00 = (RwUInt8 *)unk_0C;
        unk_08 = 0;
        unk_04 = BITS;
    }
};

struct type_3DA440 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

// A damage message: its amount (sub_1C5A80) and the body part hit.
struct type_3DA434 : type_3DA440
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    void sub_1C5A80(RwReal arg_0);

    RwInt32 unk_04;
    RwUInt8 unk_08;             // (no padding array: /GS would guard it)
    RwReal unk_0C;              // its amount (sub_1C5A80)

    // An inline accessor with no address and so no database name, named for
    // its field. Evidence: the bullet hit's handler (sub_1ACAB0) reads it
    // through a slot of its own, twice.
    RwReal get_unk_0C()
    {
        RwReal r = unk_0C;
        return r;
    }
};



// The other messages the multiplayer manager decodes (unit_1A26F0's
// decoders, from the table at 0x42C850): each a class of three levels named
// after its vtables, the middle one giving the id. Only the widths are
// known.
struct type_3E0F60 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

// The one message with a destructor of its own (sub_1C5760): its decoder
// (sub_1A3020) clears its fields and has its instance destroyed at exit.
struct type_3E0F54 : type_3E0F60
{
    type_3E0F54()
    {
        unk_0C = 0;
        unk_08 = 0;
        unk_04 = 0;
    }
    ~type_3E0F54();
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;            // the player's communicator is in
    RwUInt32 unk_08;            // the player's voice goes to the speakers
    RwUInt32 unk_0C;            // the player is muted

    // Inline accessors with no address and so no database names, named for
    // their fields. Evidence: the voice chat's sub_1C7840 reads each field
    // of the message it takes through a result local.
    // Inline setters with no address and so no database names, named for
    // their fields. Evidence: the voice chat (sub_1C7680) widens each value
    // from a byte temporary, as a bool argument gives.
    void set_unk_04(bool arg_0)
    {
        unk_04 = arg_0;
    }
    void set_unk_08(bool arg_0)
    {
        unk_08 = arg_0;
    }
    void set_unk_0C(bool arg_0)
    {
        unk_0C = arg_0;
    }
    RwUInt32 get_unk_04()
    {
        RwUInt32 r = unk_04;
        return r;
    }
    RwUInt32 get_unk_08()
    {
        RwUInt32 r = unk_08;
        return r;
    }
    RwUInt32 get_unk_0C()
    {
        RwUInt32 r = unk_0C;
        return r;
    }
};

// A message carrying a string (its destructor, sub_1A88E0, is out of line).
struct type_3E1038 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E102C : type_3E1038
{
    ~type_3E102C();
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    type_1A5EA0 unk_04;
};

struct type_3E0F78 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E0F6C : type_3E0F78
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    // Sets its amount: identical to the damage message's and folded
    // (/OPT:ICF) with it at 0x1C5A80.
    void sub_1C5A80(RwReal arg_0);

    RwInt32 unk_04;
    RwUInt8 unk_08;
    RwUInt8 unk_09;             // the remote player hit
    RwReal unk_0C;

    // An inline accessor with no address and so no database name, named for
    // its field. Evidence: the remote bullet hit's handler (sub_1ACEB0) reads
    // it through a slot of its own, twice.
    RwReal get_unk_0C()
    {
        RwReal r = unk_0C;
        return r;
    }
};

struct type_3E0F90 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E0F84 : type_3E0F90
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
};

struct type_3E0FA8 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E0F9C : type_3E0FA8
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt16 unk_04;
    RwUInt16 unk_06;
    RwUInt16 unk_08;
    RwUInt16 unk_0A;
    RwUInt32 unk_0C;
    RwUInt32 unk_10[0x9D];
};

struct type_3E0FC0 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

// A message with a point: its site-like number (signed), a kind, the
// point, a player (-1 sent as 16), a count and a dword. Its copy
// constructor is compiler-made and out of line (sub_1B2100).
struct type_3E0FB4_data
{
    type_3E0FB4_data()
    {
    }
    type_3E0FB4_data(const type_3E0FB4_data &arg_0)
    {
    }
};
struct type_3E0FB4 : type_3E0FB4_data, type_3E0FC0
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwInt32 unk_04;
    RwUInt32 unk_08;
    RwV3d unk_0C;
    RwInt32 unk_18;
    RwUInt32 unk_1C;
    RwUInt32 unk_20;
};

struct type_3E0FD8 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

// A bomb site's new state (the sites' part of the manager sends it,
// type_4F8184::sub_1A7D80): the site, the state, the bomb's position, the
// player and the site's update count. Its copy constructor is compiler-made
// and out of line (sub_1A8400; the sites' sub_1A80B0 sends a copy on).
struct type_3E0FCC_data
{
    type_3E0FCC_data()
    {
    }
    type_3E0FCC_data(const type_3E0FCC_data &arg_0)
    {
    }
};
struct type_3E0FCC : type_3E0FCC_data, type_3E0FD8
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwInt32 unk_04;
    RwUInt32 unk_08;
    RwV3d unk_0C;
    RwUInt32 unk_18;
    RwUInt32 unk_1C;
};

struct type_3E0FF0 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E0FE4_data
{
    type_3E0FE4_data()
    {
    }
    type_3E0FE4_data(const type_3E0FE4_data &arg_0)
    {
    }
};
struct type_3E0FE4 : type_3E0FE4_data, type_3E0FF0
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwInt32 unk_04;
    RwUInt32 unk_08;
    RwUInt32 unk_0C;
    RwUInt32 unk_10;
};

struct type_3E1008 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E0FFC_data
{
    type_3E0FFC_data()
    {
    }
    type_3E0FFC_data(const type_3E0FFC_data &arg_0)
    {
    }
};
struct type_3E0FFC : type_3E0FFC_data, type_3E1008
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
    RwUInt32 unk_08;
};

struct type_3E1020 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E1014_data
{
    type_3E1014_data()
    {
    }
    type_3E1014_data(const type_3E1014_data &arg_0)
    {
    }
};
struct type_3E1014 : type_3E1014_data, type_3E1020
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
    RwUInt32 unk_08;
    RwUInt32 unk_0C;
};

struct type_3E1050 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E1044_data
{
    type_3E1044_data()
    {
    }
    type_3E1044_data(const type_3E1044_data &arg_0)
    {
    }
};
struct type_3E1044 : type_3E1044_data, type_3E1050
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
};

struct type_3E0EC4 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E0EB8_data
{
    type_3E0EB8_data()
    {
    }
    type_3E0EB8_data(const type_3E0EB8_data &arg_0)
    {
    }
};
struct type_3E0EB8 : type_3E0EB8_data, type_3E0EC4
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
};

struct type_3E1068 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E105C : type_3E1068
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
};

struct type_3E1080 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

// A message has an empty base of its own (X_data, with inline constructors)
// declared before its vtable's base, which still sits at +0: a copy
// converts to it through a null check before the vtable stores, then copies
// the fields (the handlers' copies, sub_1AF320, sub_1AF570; out of line for
// the larger ones, sub_1AF4F0, sub_1AF600).
struct type_3E1074_data
{
    type_3E1074_data()
    {
    }
    type_3E1074_data(const type_3E1074_data &arg_0)
    {
    }
};
struct type_3E1074 : type_3E1074_data, type_3E1080
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
};

struct type_3E1098 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E108C : type_3E1098
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
};

struct type_3E10B0 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E10A4 : type_3E10B0
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
};

struct type_3E10C8 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E10BC : type_3E10C8
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
};

struct type_3E10E0 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E10D4 : type_3E10E0
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
};

struct type_3E10F8 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E10EC : type_3E10F8
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
    RwUInt32 unk_08;
};

struct type_3E1110 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E1104_data
{
    type_3E1104_data()
    {
    }
    type_3E1104_data(const type_3E1104_data &arg_0)
    {
    }
};
struct type_3E1104 : type_3E1104_data, type_3E1110
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
};

struct type_3E1128 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E111C_data
{
    type_3E111C_data()
    {
    }
    type_3E111C_data(const type_3E111C_data &arg_0)
    {
    }
};
struct type_3E111C : type_3E111C_data, type_3E1128
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
    RwUInt32 unk_08;
    RwUInt32 unk_0C;
    type_1F8560_v unk_10;
};

struct type_3E1140 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E1134_data
{
    type_3E1134_data()
    {
    }
    type_3E1134_data(const type_3E1134_data &arg_0)
    {
    }
};
struct type_3E1134 : type_3E1134_data, type_3E1140
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
    RwUInt32 unk_08;
    RwUInt32 unk_0C;
};

struct type_3E1158 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E114C : type_3E1158
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwReal unk_04;
    RwInt32 unk_08;
    RwUInt8 unk_0C;
    RwUInt8 unk_0D;
    RwUInt32 unk_10;
};

struct type_3E1170 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E1164 : type_3E1170
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwReal unk_04;
    type_1F8560_v unk_08;
    RwReal unk_14;
    RwUInt8 unk_18;
    RwUInt32 unk_1C;
};

struct type_3E1188 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E117C : type_3E1188
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwUInt32 unk_04;
    RwUInt32 unk_08;
};

struct type_3E11A0 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E1194 : type_3E11A0
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    RwReal unk_04;
    type_1F8560_v unk_08;
    RwReal unk_14;
};

struct type_3E11B8 : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_3E11AC : type_3E11B8
{
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);

    type_1F8560_v unk_04;
    type_1F8560_v unk_10;
    RwUInt32 unk_1C;
    RwUInt32 unk_20;
};

void sub_1ACBA0(RwInt32 arg_0, type_3DA434 *arg_4);

// The local player's network part (vtable off_3E24E8, all _purecall; the
// constructor stores it first, the base's inline constructor): the
// network player it drives calls it (type_4F6B00::unk_11C). Its slots are
// named pvf_ for the part's vtable, as the entity's own vf_ names (vf_030,
// vf_034) would collide.
struct type_3E24E8
{
    virtual void pvf_000(RwInt32 arg_0) = 0;
    virtual type_1F8560_v *pvf_004() = 0;
    virtual type_1F8560_v *pvf_008() = 0;
    virtual RwReal pvf_00C() = 0;
    virtual RwReal pvf_010() = 0;
    virtual RwInt32 pvf_014() = 0;
    virtual RwInt32 pvf_018() = 0;
    virtual RwInt32 pvf_01C() = 0;
    virtual RwInt32 pvf_020() = 0;
    virtual RwInt32 pvf_024() = 0;
    virtual RwInt32 pvf_028() = 0;
    virtual RwInt32 pvf_02C() = 0;
    virtual RwInt32 pvf_030() = 0;
    virtual RwInt32 pvf_034() = 0;
    virtual RwInt32 pvf_038() = 0;
    virtual RwInt32 pvf_03C(type_75600 *arg_0) = 0;
    virtual void pvf_040(RwInt32 arg_0) = 0;
};
// Not in the image: a stand-in class on the interface, whose constructor
// (unit_3E24C0, unreferenced) emits the interface's vtable where the image has
// it, in an object whose code the link dropped.
struct dropped_3E24E8 : type_3E24E8
{
    dropped_3E24E8();
};

// The local player in a network game (0x22B0 bytes, built in entity memory
// by sub_1B7B20 for its trigger; vtables off_3E25A0 and, for the network
// part at +0x2260, off_3E2558). Named for the pulse zones' damage
// (sub_17DBD0), which casts the local player to it.
struct type_17DBD0_player : type_10F710, type_3E24E8
{
    type_17DBD0_player(type_712B0 *arg_0);
    ~type_17DBD0_player();
    // The placement pair sub_1B7B20 builds it in entity memory with, as
    // type_3D32F8's (sub_6CCF0 and the empty sub_19A750), and its plain
    // operator delete for its deleting destructor (the placement one hides
    // the base's; also folded into sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);

    // Overrides of the player's slots.
    virtual void vf_038(RwReal arg_0);
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_04C(RwReal arg_0);
    // Touching an entity: the player's own (vf_060), its pick-up handles
    // cleared; a pick-up touched is kept, and settings 0x4B to 0x4D taken
    // at once (sub_1B91E0).
    virtual RwInt32 vf_060(type_3D3548 *arg_0);
    virtual RwInt32 vf_068(struct type_758F0 *arg_0);
    // Its health set (a fraction); an ally and an enemy; the defuse and the
    // plant for the time step.
    virtual void vf_23C(RwReal arg_0);
    virtual RwInt32 vf_248(type_3D3548 *arg_0);
    virtual RwInt32 vf_24C(type_3D3548 *arg_0);
    virtual void vf_250(RwReal arg_0);
    virtual void vf_254(RwReal arg_0);
    // A bullet's hit: none (the manager deals them). Returns 0: identical
    // to other methods and folded (/OPT:ICF) into sub_32260.
    virtual RwInt32 vf_064(struct type_75600 *arg_0)
    {
        return 0;
    }

    // The network part's slots: its state for the network (position, the
    // look, the facing), its position and velocity, its facing, its look's
    // pitch, the weapon and posture queries.
    virtual void pvf_000(RwInt32 arg_0);
    // Returns its position: identical to another method and folded
    // (/OPT:ICF) into sub_1A5F60.
    virtual type_1F8560_v *pvf_004()
    {
        return &unk_2264;
    }
    virtual type_1F8560_v *pvf_008();
    // Returns its facing: identical to another method and folded
    // (/OPT:ICF) into sub_15FB60.
    virtual RwReal pvf_00C()
    {
        return unk_227C;
    }
    virtual RwReal pvf_010();
    virtual RwInt32 pvf_014();
    virtual RwInt32 pvf_018();
    virtual RwInt32 pvf_01C();
    virtual RwInt32 pvf_020();
    virtual RwInt32 pvf_024();
    virtual RwInt32 pvf_028();
    virtual RwInt32 pvf_02C();
    virtual RwInt32 pvf_030();
    virtual RwInt32 pvf_034();
    virtual RwInt32 pvf_038();
    virtual RwInt32 pvf_03C(type_75600 *arg_0);
    virtual void pvf_040(RwInt32 arg_0);

    // Its flag in capture the flag: taken (sub_1B81D0), dropped (arg_0 2,
    // at its feet) or returned (sub_1B8250), touched (sub_1B82F0), and
    // checked each step (sub_1B8380).
    void sub_1B81D0();
    void sub_1B8250(RwInt32 arg_0, RwInt32 arg_4);
    void sub_1B82F0(RwInt32 arg_0);
    void sub_1B8380();
    // Its team (the manager's unk_29C).
    RwInt32 sub_1B8420();
    // The bomb sites: checked each step (sub_1B8440); defusing started,
    // ended and stopped (sub_1B85C0, sub_1B8630, sub_1B8690), planting
    // likewise (sub_1B86D0, sub_1B8740, sub_1B87D0).
    void sub_1B8440();
    void sub_1B85C0();
    void sub_1B8630(RwInt32 arg_0);
    void sub_1B8690();
    void sub_1B86D0(RwInt32 arg_0);
    void sub_1B8740(RwInt32 arg_0);
    void sub_1B87D0();
    // Kills it: the damage message sent, its health 0, posture 10.
    void sub_1B8820();
    RwInt32 sub_1B90C0();
    // What the multiplayer manager hands on from it (sub_1AD730; the kill
    // message carries it, sub_1ACBA0); only the width is known.
    RwInt32 sub_1B91B0();
    void sub_1B91E0();
    // The turns while defusing or planting; entering and leaving a bomb
    // site's trigger and a flag base's.
    void sub_1BA5F0(RwReal arg_0);
    void sub_1BA910(class type_712B0 *arg_0, bool arg_4);
    void sub_1BA980(class Trigger *arg_0, bool arg_4);
    // Whether it is defusing (posture 16) or planting (17) at site arg_0:
    // inlines with no addresses and so no database names, named for what
    // they test. Evidence: the sites' sub_1A80B0 tests each through the
    // manager's getter's slot, a posture slot and a bool temporary.
    bool defusing_at(RwInt32 arg_0)
    {
        return (bool)(get_unk_19D0_r() == 16 && unk_2294 == arg_0);
    }
    bool planting_at(RwInt32 arg_0)
    {
        return (bool)(get_unk_19D0_r() == 17 && unk_2298 == arg_0);
    }

    type_1F8560_v unk_2264;     // its position (pvf_000)
    type_1F8560_v unk_2270;     // its velocity
    RwReal unk_227C;            // its facing
    RwReal unk_2280;            // its facing on a ladder
    RwInt32 unk_2284;           // sub_1B90C0's
    RwInt32 unk_2288;           // the id of the network player driven by it
    type_D48D0 unk_228C;        // the pick-up touched (vf_060)
    RwReal unk_2290;            // the defuse's or plant's time, in frames
    RwInt32 unk_2294;           // its bomb site
    RwInt32 unk_2298;           // the site it plants at
    RwInt32 unk_229C;           // while set it has the flag
    RwInt32 unk_22A0;
    RwUInt8 unk_22A4[0xC];
};
typedef RwChar type_17DBD0_player_size_check[sizeof(type_17DBD0_player) == 0x22B0 ? 1 : -1];

// Built in entity memory for the trigger arg_0, or a warning that there is
// no entity memory for it.
type_17DBD0_player *sub_1B7B20(type_712B0 *arg_0);

// The keys of the messages the pick-ups show (the network player's
// sub_1B91E0; the player's sub_106A60 uses them too): for rounds, then for
// weapons.
struct type_3DF8D8_04_data;
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FA4;
#else
extern type_3DF8D8_04_data unk_4B8FA4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FAC;
#else
extern type_3DF8D8_04_data unk_4B8FAC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FB4;
#else
extern type_3DF8D8_04_data unk_4B8FB4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FBC;
#else
extern type_3DF8D8_04_data unk_4B8FBC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FC4;
#else
extern type_3DF8D8_04_data unk_4B8FC4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FCC;
#else
extern type_3DF8D8_04_data unk_4B8FCC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FD4;
#else
extern type_3DF8D8_04_data unk_4B8FD4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FDC;
#else
extern type_3DF8D8_04_data unk_4B8FDC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FE4;
#else
extern type_3DF8D8_04_data unk_4B8FE4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FEC;
#else
extern type_3DF8D8_04_data unk_4B8FEC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FF4;
#else
extern type_3DF8D8_04_data unk_4B8FF4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B8FFC;
#else
extern type_3DF8D8_04_data unk_4B8FFC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9004;
#else
extern type_3DF8D8_04_data unk_4B9004;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B900C;
#else
extern type_3DF8D8_04_data unk_4B900C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9014;
#else
extern type_3DF8D8_04_data unk_4B9014;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9024;
#else
extern type_3DF8D8_04_data unk_4B9024;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B902C;
#else
extern type_3DF8D8_04_data unk_4B902C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9034;
#else
extern type_3DF8D8_04_data unk_4B9034;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B903C;
#else
extern type_3DF8D8_04_data unk_4B903C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9044;
#else
extern type_3DF8D8_04_data unk_4B9044;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B904C;
#else
extern type_3DF8D8_04_data unk_4B904C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9054;
#else
extern type_3DF8D8_04_data unk_4B9054;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B905C;
#else
extern type_3DF8D8_04_data unk_4B905C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9064;
#else
extern type_3DF8D8_04_data unk_4B9064;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B906C;
#else
extern type_3DF8D8_04_data unk_4B906C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9074;
#else
extern type_3DF8D8_04_data unk_4B9074;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B907C;
#else
extern type_3DF8D8_04_data unk_4B907C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9084;
#else
extern type_3DF8D8_04_data unk_4B9084;
#endif
// The bears' messages (the player's sub_106A60).
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B908C;
#else
extern type_3DF8D8_04_data unk_4B908C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9094;
#else
extern type_3DF8D8_04_data unk_4B9094;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B909C;
#else
extern type_3DF8D8_04_data unk_4B909C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90A4;
#else
extern type_3DF8D8_04_data unk_4B90A4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90AC;
#else
extern type_3DF8D8_04_data unk_4B90AC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90B4;
#else
extern type_3DF8D8_04_data unk_4B90B4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90BC;
#else
extern type_3DF8D8_04_data unk_4B90BC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90C4;
#else
extern type_3DF8D8_04_data unk_4B90C4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90CC;
#else
extern type_3DF8D8_04_data unk_4B90CC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90D4;
#else
extern type_3DF8D8_04_data unk_4B90D4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90DC;
#else
extern type_3DF8D8_04_data unk_4B90DC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90E4;
#else
extern type_3DF8D8_04_data unk_4B90E4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90EC;
#else
extern type_3DF8D8_04_data unk_4B90EC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90F4;
#else
extern type_3DF8D8_04_data unk_4B90F4;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B90FC;
#else
extern type_3DF8D8_04_data unk_4B90FC;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9104;
#else
extern type_3DF8D8_04_data unk_4B9104;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B910C;
#else
extern type_3DF8D8_04_data unk_4B910C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9114;
#else
extern type_3DF8D8_04_data unk_4B9114;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B911C;
#else
extern type_3DF8D8_04_data unk_4B911C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9124;
#else
extern type_3DF8D8_04_data unk_4B9124;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B912C;
#else
extern type_3DF8D8_04_data unk_4B912C;
#endif
#ifdef CODFH_PLAIN
extern type_3DF8D8_04_data &unk_4B9134;
#else
extern type_3DF8D8_04_data unk_4B9134;
#endif

// A pick-up in a network game (0x3E0 bytes, vtable off_3E2BF0; sub_1BD340
// builds one for its trigger, sub_1BD450 from settings): the pick-up list
// (dword_4FBB20) forgets it as it goes, and it carries its network id
// (unk_3D0, sub_1BD680).
struct type_1AE520 : type_3D94B8
{
    type_1AE520(PickupTrigger *arg_0);
    type_1AE520(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10, RwInt32 arg_14);
    ~type_1AE520();
    // The placement pair it is built in entity memory with, as
    // type_3D94B8's, and its plain operator delete (all folded).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);

    void sub_1BD680(RwUInt32 arg_0);
    // An inline accessor with no address and so no database name, named for
    // its field. Evidence: the manager's sends read it through a slot of
    // its own.
    RwUInt32 get_unk_3D0()
    {
        RwUInt32 r = unk_3D0;
        return r;
    }

    RwUInt32 unk_3D0;
    RwUInt8 unk_3D4[0xC];
};
typedef RwChar type_1AE520_size_check[sizeof(type_1AE520) == 0x3E0 ? 1 : -1];

// Its spawns: for the trigger arg_0, and from settings.
type_1AE520 *sub_1BD340(PickupTrigger *arg_0);
type_1AE520 *sub_1BD450(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10,
                        RwInt32 arg_14);

// A player the spawn points keep away from: where it is (zeroed by its
// inline constructor) and its team.
struct type_4FBC50_player
{
    type_1F8560_v unk_00;
    RwInt32 unk_0C;
};
// A list of spawn points (cNetSpawnPoint, 0x268 bytes): what it serves (1
// every point, else a team bit, 2 or 4) and its group (-1 for any), the
// points, and the last one handed out in turn. Its picks for the arg_0
// players arg_4, never the point arg_8 (the last pick): in turn (rule 0);
// farthest from the nearest player (1, the default); nearest the players'
// middle that is 120 away from all (2); by the count of players, as far as
// a distance (3); away from enemies of team arg_10 (4); at random, 120 from
// all (5, 6). Each gives the point's index among all points.
class cNetSpawnPoint;
struct type_1C0F60
{
    // Out of line: the lists' constructor (sub_1C1BA0) builds each with it.
    type_1C0F60();
    // Forgets its points (sub_1C1C10).
    void sub_1C0FA0();
    // Takes the point arg_0 in.
    void sub_1C0FE0(cNetSpawnPoint *arg_0);
    RwInt32 sub_1C1010(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);
    RwInt32 sub_1C1140(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8);
    // The rule 3 pick for a distance arg_C.
    RwInt32 sub_1C1210(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwReal arg_C);
    // Whether any of the arg_0 players arg_4 is on team arg_8.
    RwInt32 sub_1C1350(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8);
    // A point at random.
    RwInt32 sub_1C13A0();
    RwInt32 sub_1C13C0(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    RwInt32 sub_1C1560(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    RwInt32 sub_1C1630(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8, RwInt32 arg_C);
    RwInt32 sub_1C1660();
    RwInt32 sub_1C16B0(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8);
    RwInt32 sub_1C1820(RwUInt32 arg_0, type_4FBC50_player *arg_4, RwInt32 arg_8);
    // The distance from *arg_8 to the nearest of the arg_0 players arg_4
    // not on team arg_C (8 for none: all), into *arg_10; it returns the
    // nearest team mate's (or that).
    RwReal sub_1C1A40(RwUInt32 arg_0, type_4FBC50_player *arg_4, type_1F8560_v *arg_8, RwInt32 arg_C,
                      RwReal *arg_10);
    // Point arg_0's commands 5 to 8 and its matrix.
    RwUInt32 *sub_1C1B60(RwInt32 arg_0);
    struct RwMatrixTag *sub_1C1B80(RwInt32 arg_0);

    // Inline accessors, with no addresses and so no database names; named
    // for their fields. Evidence: the lists' search (sub_1C2050) reads each
    // through a slot of its own, and their sorting (sub_1C1CE0) sets them
    // through `this` slots.
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
    void set_unk_00(RwInt32 arg_0)
    {
        unk_00 = arg_0;
    }
    void set_unk_04(RwInt32 arg_0)
    {
        unk_04 = arg_0;
    }

    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;             // the points held
    cNetSpawnPoint *unk_0C[150];
    RwInt32 unk_264;            // the last one handed out in turn
};
typedef RwChar type_1C0F60_size_check[sizeof(type_1C0F60) == 0x268 ? 1 : -1];

// The spawn points (unk_4FBC50, 0x1A80 bytes): all of them, and the lists
// the game type sorts them into (one for the deathmatch, type 1; one per
// team for types 2 and 4; one per team and group for types 8 and 16).
struct type_4FBC50
{
    // Out of line (sub_1C1BA0) for unk_4FBC50's dynamic initializer.
    type_4FBC50();
    // The first list serving team bit arg_0 and group arg_4 (-1 for any),
    // or -1.
    RwInt32 sub_1C2050(RwInt32 arg_0, RwInt32 arg_4);
    // The point list arg_0 picks for the arg_4 players arg_8 by the rule
    // arg_C (for team arg_10), kept as the last pick.
    RwInt32 sub_1C1C80(RwInt32 arg_0, RwUInt32 arg_4, type_4FBC50_player *arg_8, RwInt32 arg_C, RwInt32 arg_10);
    // Forgets the points (the manager's clean-up, sub_1A8E80).
    void sub_1C1C10();
    // Takes the point arg_0 in at the game's start (its HandleEvents).
    void sub_1C1CE0(cNetSpawnPoint *arg_0);
    // Point arg_0's commands 5 to 8 and its matrix (sub_1ABE30).
    RwUInt32 *sub_1C20D0(RwInt32 arg_0);
    struct RwMatrixTag *sub_1C20F0(RwInt32 arg_0);
    // An inline, with no address and so no database name, named for what
    // it gives. Evidence: the sorting (sub_1C1CE0) tests the teams a point
    // spawns through a slot holding the team's bit, 2 or 4.
    RwUInt32 get_mask(RwUInt32 arg_0)
    {
        RwUInt32 r = arg_0;
        return r;
    }

    type_1C0F60 unk_00;         // every point
    RwUInt32 unk_268;           // the lists in use
    type_1C0F60 unk_26C[10];
    RwInt32 unk_1A7C;           // the last pick
};
typedef RwChar type_4FBC50_size_check[sizeof(type_4FBC50) == 0x1A80 ? 1 : -1];
extern type_4FBC50 unk_4FBC50;

// Two more parts of the full game state (dword_4FBB20 and dword_4F8288);
// only the widths are known.
struct PickupTrigger;
// The network game's pick-ups (dword_4FBB20, 0x10C bytes): 32 slots, each
// a network pick-up whose id is its slot, their count; and on the host the
// triggers that spawned them (respawned at a level load, sub_1BD9F0).
struct type_4FBB20
{
    // Out of line (sub_1BD930) for dword_4FBB20's dynamic initializer: it
    // forgets them.
    type_4FBB20();
    // Writes them to the stream arg_0 (the count, then each one's id,
    // settings, rounds and position) and reads them back, spawning each.
    void sub_1BDB10(type_1F8560 *arg_0);
    void sub_1BDC30(type_1F8560 *arg_0);
    // A free slot, or -1 (the pickup drop, sub_1ADB80).
    RwInt32 sub_1BDAD0();
    // Forgets the pickups (the manager's clean-up, sub_1A8E80; a client's
    // level load, sub_1B52D0), and the host's counterpart at a level load
    // (sub_1BD9F0) respawning them from their triggers.
    void sub_1BD950();
    void sub_1BD9F0();
    // Takes the pick-up arg_0, spawned by the trigger arg_4, into the first
    // free slot (the trigger kept unless loading).
    void sub_1BDFC0(type_1AE520 *arg_0, PickupTrigger *arg_4);
    // Forgets the pick-up arg_0 (its destructor, sub_1BD5F0).
    void sub_1BE060(type_1AE520 *arg_0);
    // What the multiplayer manager's pickup handlers pass on (sub_1AE5C0,
    // sub_1AE650, sub_1AE810): slot arg_0 removed; spawned with the settings
    // arg_4 and rounds arg_8 at *arg_C; its pick-up replaced by one with the
    // settings arg_4 and rounds arg_8 where it stood.
    void sub_1BDD20(RwUInt32 arg_0);
    void sub_1BDD70(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8, type_1F8560_v *arg_C);
    void sub_1BDE70(RwUInt32 arg_0, RwUInt32 arg_4, RwUInt32 arg_8);

    RwInt32 unk_00;             // the pick-ups held
    type_1AE520 *unk_04[32];
    RwUInt32 unk_84;            // the triggers kept
    PickupTrigger *unk_88[32];
    RwInt32 unk_108;            // set while respawning (sub_1BD9F0)
};
typedef RwChar type_4FBB20_size_check[sizeof(type_4FBB20) == 0x10C ? 1 : -1];
extern type_4FBB20 dword_4FBB20;

// The id maps between the game's numbering and the network's (sub_1C5800
// and back, sub_1C5860): direct tables once built (byte_4FE4B8), else a
// search of the 38 pairs.
struct type_4FE4C0
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08;

    // Inline: the table's dynamic initializer (0x30C410) stores each
    // entry's three values in order.
    type_4FE4C0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
    {
        unk_00 = arg_0;
        unk_04 = arg_4;
        unk_08 = arg_8;
    }
};
extern bool byte_4FE4B8;
extern RwInt32 dword_4FDC08[];
extern RwInt32 dword_4FE2B8[];
extern type_4FE4C0 dword_4FE4C0[0x26];
RwInt32 sub_1C5800(RwInt32 arg_0);
RwInt32 sub_1C5860(RwInt32 arg_0);
// Clears the five dwords at dword_4FE688.
extern RwInt32 dword_4FE688[5];
void sub_1C6050();

// The bits a value up to arg_0 needs (sub_1F84A0).
RwInt32 sub_1F84A0(RwUInt32 arg_0);

// A message handler (0x14 bytes; the table unk_42C848, dword_42CAB4 of
// them): its kind, the message id it takes, and its functions: kind 0 reads
// the message (unk_08) and then takes what that gave (unk_0C), kind 1 takes
// the stream (unk_10).
struct type_42C848
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    struct type_3DA44C *(*unk_08)(type_1F8560 *arg_0);
    void (*unk_0C)(RwInt32 arg_0, RwInt32 arg_4, struct type_3DA44C *arg_8);
    void (*unk_10)(RwUInt32 arg_0, RwInt32 arg_4, type_1F8560 *arg_8);
};
extern type_42C848 unk_42C848[];
extern RwUInt32 dword_42CAB4;

// The network session (dword_4F8058; unit_1DDBE0): the network game's
// peer listener (cNetGame's unk_A0). It sends the messages arg_0 to the
// peers arg_4 (sub_1DDDB0, sub_1DDE20, sub_1DDE90: through the stream
// unk_502EF0, the message's id first), hands a message that came in to its
// handler (the table unk_42C848), and keeps the networked objects (unk_08)
// whose updates it sends when they are due.
struct type_4F8054;
struct type_4F6B00;
struct type_3E1388;
struct type_4F8058 : type_4F8054_A0
{
    type_4F8054 *unk_04;        // the network game
    type_1FA230_list<type_3E1388 *> unk_08;

    // Built by the multiplayer manager's set-up (sub_1A9580) for the
    // network game arg_0.
    type_4F8058(type_4F8054 *arg_0);
    virtual ~type_4F8058();
    virtual void vf_000(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                        RwInt32 arg_14);
    // The message in arg_8 from peer arg_0 to its handler.
    void sub_1DDF00(RwInt32 arg_0, RwInt32 arg_4, type_1F8560 *arg_8);
    // Sends the networked objects' updates due by the time arg_0.
    void sub_1DDFF0(const type_1CCA10 &arg_0);
    // Takes the network player arg_0 (the set-up, for each of the sixteen).
    void sub_1DE1A0(type_4F6B00 *arg_0);
    // sub_1DE1A0 for each of the sixteen network players: an inline with no
    // address and so no database name, named for the function it calls
    // (defined in game/netplayer.h). Evidence: the set-up (sub_1A9580)
    // keeps a `this` copy and a counter in slots after all its others.
    void sub_1DE1A0_16();
    void sub_1DDE20(type_3DA44C *arg_0, const type_1DDE20_mask &arg_4);
    void sub_1DDDB0(type_3DA44C *arg_0, const type_1DDE20_mask &arg_4);
    // Another send to the peers in arg_4 (the local player's wound, sub_1B8AA0);
    // only the width is known.
    void sub_1DDE90(type_3DA44C *arg_0, const type_1DDE20_mask &arg_4);
    // What the multiplayer manager's leave passes on (sub_1AF750); only the
    // width is known.
    void sub_1DDFD0(const type_1CCA10 &arg_0);
    static type_4F8058 *get();
};
#ifdef CODFH_PLAIN
// (plain builds: a field of the multiplayer manager unk_4F7EB8; see unit_1A8B20)
extern type_4F8058 *&dword_4F8058;
#else
extern type_4F8058 *dword_4F8058;
#endif
// An inline accessor with no address and so no database name, named for
// what it returns. Evidence: the bomb sites' sync (sub_1A7D80) copies
// dword_4F8058 into a local of its own before calling through it.
inline type_4F8058 *type_4F8058::get()
{
    type_4F8058 *r = dword_4F8058;
    return r;
}

// A debug print (vsprintf into OutputString, then OutputDebugStringA).
void sub_1C8A30(const RwChar *arg_0, ...);
// Prints the collision-world sections still loading (the print compiled
// out), then sub_821C0.
void sub_1C58C0();
// Sends the local player's grenade throw (type_3E11AC: the two vectors and
// the two values) to the other players ("Local player threw a grenade").
void sub_1C5CA0(const type_1F8560_v &arg_0, const type_1F8560_v &arg_4, RwUInt32 arg_8, RwUInt32 arg_C);

#endif
