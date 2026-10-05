/*
 * The network players (unit_1A6140): sixteen proxies (unk_4F6B00, 0x138
 * bytes each), each a networked object whose state goes out and comes in as
 * its own update message (the message part at +0x1C: written by vf_000,
 * read by vf_004, then applied by sub_1A71E0).
 *
 * The networked object is two levels: its interface (off_3E1388, one pure
 * method giving its message; its constructor, inline, takes the object's
 * rate and ids) and the object itself (off_3E1378, sub_1A7AA0), which is
 * also its update message (off_3E137C's level of type_3DA44C, at +0x1C).
 * Only the widths are known where no comment says more.
 */
#ifndef GAME_NETPLAYER_H
#define GAME_NETPLAYER_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "game/netmsg.h"
#include "game/gameloop.h"

// A word set from its constructor's argument.
struct type_3E1388_0C
{
    RwUInt16 unk_00;

    type_3E1388_0C(const RwUInt16 &arg_0)
    {
        // A compiled-out check: the registers after it are one load on
        // (docs/toolchain.md).
        if (!arg_0)
        {
        }
        unk_00 = arg_0;
    }
};

struct type_3E1388
{
    virtual type_3DA44C *vf_000() = 0;

    RwInt32 unk_04;             // the milliseconds between its updates
    RwInt32 unk_08;             // set when it has an update to send
    type_3E1388_0C unk_0C;      // the peers kind 2 sends to
    RwInt32 unk_10;             // whom it sends to (0 the peers, 1 the
                                // host, 2 unk_0C)
    RwInt32 unk_14;             // how (the session's sub_1DDDB0 or
                                // sub_1DDE90)
    type_1CCA10 unk_18;         // when it last sent (the session's
                                // sub_1DDFF0)

    // An inline accessor for unk_04, with no address and so no database
    // name; named for its field. Evidence: the session's update send
    // (sub_1DDFF0) reads it through a slot of its own.
    RwInt32 get_unk_04()
    {
        return unk_04;
    }

    type_3E1388(const RwInt32 &arg_0, RwInt32 arg_4, RwInt32 arg_8, const RwUInt16 &arg_C = 0)
        : unk_04(arg_4), unk_08(0), unk_0C(arg_C), unk_10(arg_0), unk_14(arg_8)
    {
    }
};

// The update message's middle level: its id (sub_1E4CB0, 0; folded).
struct type_3E137C : type_3DA44C
{
    virtual RwInt32 vf_008();
};

struct type_1A7AA0 : type_3E1388, type_3E137C
{
    // An inline defined in its unit (unit_1A6140, after sub_1A7A90) but not
    // inlined (it is called at sub_1A7AA0); its callers still reserve its
    // expansion's slots: the network player's constructor (sub_1A6140) has four
    // unused ones (docs/toolchain.md).
    type_1A7AA0(const RwInt32 &arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // Its message: itself, as the message part.
    virtual type_3DA44C *vf_000();
};

// A cubic curve (sub_1FA6E0 builds it, zeroed): its coefficients from t^3
// down (unk_00 to unk_24), set from a Bezier segment (the start arg_0, its
// control points arg_0 + arg_4 and arg_8 + arg_C, the end arg_8;
// sub_1FA780), its point at t (sub_1FAB10) and its derivative at t
// (sub_1FACC0).
struct type_1FA6E0
{
    type_1F8560_v unk_00;
    type_1F8560_v unk_0C;
    type_1F8560_v unk_18;
    type_1F8560_v unk_24;

    type_1FA6E0();
    void sub_1FA780(const type_1F8560_v &arg_0, const type_1F8560_v &arg_4, const type_1F8560_v &arg_8,
                    const type_1F8560_v &arg_C);
    type_1F8560_v sub_1FAB10(RwReal arg_0);
    type_1F8560_v sub_1FACC0(RwReal arg_0);
};

// A straight segment from unk_00 at the time unk_0C to unk_10 at unk_1C
// (zeroed by its inline constructor; set by an inline, named for what it
// does): its point at the time arg_0, held at the ends (sub_1FB3C0).
struct type_1FB3C0
{
    type_1F8560_v unk_00;
    RwReal unk_0C;
    type_1F8560_v unk_10;
    RwReal unk_1C;

    type_1FB3C0()
    {
    }
    void set(const type_1F8560_v &arg_0, RwReal arg_4, const type_1F8560_v &arg_8, RwReal arg_C)
    {
        unk_00 = arg_0;
        unk_0C = arg_4;
        unk_10 = arg_8;
        unk_1C = arg_C;
    }
    type_1F8560_v sub_1FB3C0(RwReal arg_0);
};
inline type_1F8560_v type_1FB3C0::sub_1FB3C0(RwReal arg_0)
{
    if (arg_0 >= unk_1C)
        return unk_10;
    if (arg_0 <= unk_0C)
        return unk_00;
    type_1F8560_v local_14 = unk_10 - unk_00;
    const type_1F8560_v &loc8 = local_14;
    RwReal var_4 = unk_1C - unk_0C;
    const RwReal &var18 = var_4;
    return (arg_0 - unk_0C) / var18 * loc8 + unk_00;
}

// The network player's motion between two updates (at +0x6C; sub_1FAE60
// builds it, 0x68 bytes): from the position arg_0 and velocity arg_4 at the
// time arg_8 to the position arg_C and velocity arg_10 at arg_14
// (sub_1FAF00): a straight segment (unk_30, with the constant velocity
// unk_50; unk_5C 0) when the velocity along the way would not cover the
// distance, else a cubic (unk_00; unk_5C 1) over the time unk_64 from
// unk_60. Its position and velocity at a time (sub_1FB250, sub_1FB2E0).
struct type_1FAE60
{
    type_1FA6E0 unk_00;
    type_1FB3C0 unk_30;
    type_1F8560_v unk_50;
    RwInt32 unk_5C;
    RwReal unk_60;
    RwReal unk_64;

    type_1FAE60();
    void sub_1FAF00(const type_1F8560_v &arg_0, const type_1F8560_v &arg_4, RwReal arg_8,
                    const type_1F8560_v &arg_C, const type_1F8560_v &arg_10, RwReal arg_14);
    type_1F8560_v sub_1FB250(RwReal arg_0);
    type_1F8560_v sub_1FB2E0(RwReal arg_0);
};

// An angle in degrees wrapped to -180..180.
RwReal sub_1A6E10(RwReal arg_0);

// A clamped linear map: below unk_04 gives unk_00, above unk_0C gives
// unk_08, in between the line through them (sub_1A7B70).
struct type_1A7B70
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;

    RwReal sub_1A7B70(RwReal arg_0);
    // Sets its four values: an inline with no address, named for what it
    // does. Evidence: the update following (sub_1A7480) stores the four
    // through a `this` temporary; its start and end values (the first and
    // third) are read in place at the stores, as references, while the two
    // computed times go into temporaries of their own, last to first.
    void set(const RwReal &arg_0, RwReal arg_4, const RwReal &arg_8, RwReal arg_C)
    {
        unk_00 = arg_0;
        unk_04 = arg_4;
        unk_08 = arg_8;
        unk_0C = arg_C;
    }
};
// An angle in degrees, cleared by its constructor or set from a value.
struct type_4F6B00_F4
{
    RwReal unk_00;

    type_4F6B00_F4()
    {
        unk_00 = 0;
    }
    // Normalization has the same out-of-line body as sub_1A6E10.
    // Evidence: sub_1A7480 calls that body from this conversion and keeps
    // one unused local for the inline expansion VC7.1 declines.
    static RwReal normalize(RwReal arg_0)
    {
        RwReal var_4 = arg_0;
        if (var_4 < -180.0f || var_4 > 180.0f)
        {
            var_4 = var_4 + 180.0f;
            var_4 = (var_4 = (RwReal)fmod(var_4, 360.0f)) - 180.0f;
        }
        return var_4;
    }
    // The reference keeps the computed input after the angle temporary.
    // Evidence: sub_1A7480 uses slots 0x60 (angle) and 0x64 (input), after
    // the two returned vectors, before assigning the complete angle.
    type_4F6B00_F4(const RwReal &arg_0)
    {
        unk_00 = normalize(arg_0);
    }
    // An inline accessor for unk_00, with no address and so no database
    // name; named for its field. Evidence: the remote player's state
    // (sub_1BF0C0) reads the facing through a slot of its own before the
    // other arguments of each turn.
    RwReal get_unk_00()
    {
        RwReal r = unk_00;
        return r;
    }
    // The angle arg_0 less this one: an inline with no address, named for
    // what it gives. Evidence: the update following (sub_1A7480) subtracts
    // the facing straight from the field into a temporary of its own, which
    // it then passes on.
    RwReal delta(RwReal arg_0)
    {
        RwReal r = arg_0 - unk_00;
        return r;
    }
};

// What a player drives (+0x11C: the local player's network part,
// type_3E24E8 in game/netmsg.h, told its id or -1 through pvf_040) and
// what shows it (+0x120: a remote player's network part, game/netsoldier.h;
// told its id through pvf_00C, shown by pvf_008 and hidden by pvf_004).
// Its vtable (off_3E2BBC) is all _purecall. Its slots are named pvf_ for
// the part's vtable, as the entity's own vf_ names (vf_008, vf_024) would
// collide in the classes deriving from both; +0x02C is the exception: the
// second player's (type_1BABA0) is its entity slot +0x05C reached through a
// this-adjusting thunk (sub_1BD330), so the two share a name.
struct type_4F6B00_120
{
    // Its state for the network.
    virtual void pvf_000(type_1F8560_v *arg_0, type_4F6B00_F4 *arg_4, type_1F8560_v *arg_8, RwInt32 *arg_C,
                         RwInt32 *arg_10, RwInt32 *arg_14, RwUInt32 *arg_18, RwUInt16 *arg_1C) = 0;
    virtual void pvf_004() = 0;
    virtual void pvf_008() = 0;
    virtual void pvf_00C(RwInt32 arg_0) = 0;
    // Told the session (the multiplayer manager's unk_1A0; sub_1ABC00).
    virtual void pvf_010(type_4F8058 *arg_0) = 0;
    // Takes a remote player's bullet and grenade hits (sub_1ACEB0,
    // sub_1AD0F0).
    virtual void pvf_014(type_75600 *arg_0) = 0;
    // Takes its death from a bullet (the died handler, sub_1AD750).
    virtual void pvf_018(type_75600 *arg_0) = 0;
    virtual void pvf_01C(struct type_4AE70 *arg_0) = 0;
    // Takes its death from a grenade's blast (the grenade death handler,
    // sub_1ADD90).
    virtual void pvf_020(struct type_4AE70 *arg_0) = 0;
    virtual void pvf_024() = 0;
    // Told a death's hit-death values *arg_0 and its hit points arg_4 (the
    // remote player's; only their widths are known).
    virtual void pvf_028(RwV3d *arg_0, RwInt32 arg_4) = 0;
    virtual void vf_05C() = 0;
};

struct type_4F6B00 : type_1A7AA0
{
    RwInt32 unk_20;
    type_1F8560_v unk_24;       // the position
    type_1F8560_v unk_30;       // the velocity
    RwReal unk_3C;
    RwReal unk_40;
    RwInt32 unk_44;             // 8 bits
    RwInt32 unk_48;             // 8 bits
    RwUInt32 unk_4C;            // 7 bits: bit 0 ...
    RwUInt16 unk_50[4];         // 5 bits each
    type_1CCA10 unk_58;         // the update's time
    RwReal unk_5C;
    RwUInt32 unk_60;            // the updates taken
    type_1CCA10 unk_64;
    RwInt32 unk_68;             // the player's id (-1)
    type_1FAE60 unk_6C;
    RwInt32 unk_D4;             // 2 on reset
    type_1F8560_v unk_D8;
    type_1F8560_v unk_E4;
    union
    {
        RwInt32 unk_F0;
        RwReal unk_F0_r;        // as the update following sets it (sub_1A7480)
    };
    type_4F6B00_F4 unk_F4;      // the facing (sub_1A6E10 of unk_3C)
    type_1CCA10 unk_F8;         // the last step's time
    type_1A7B70 unk_FC;         // the facing's easing over the update's time
    type_1A7B70 unk_10C;        // unk_F0's easing
    type_3E24E8 *unk_11C;
    type_4F6B00_120 *unk_120;
    struct type_1BABA0 *unk_124; // the second player showing it (in view)
    RwInt32 unk_128;
    RwInt32 unk_12C;
    RwInt32 unk_130;
    RwInt32 unk_134;

    type_4F6B00();
    // Takes the message arg_0 (the handler sub_1AEC30): 0, identical to
    // other methods and folded (/OPT:ICF) into sub_32260.
    RwInt32 sub_32260(struct type_3E0F9C *arg_0);
    // Writes and reads its update (the message part's vf_000 and vf_004).
    virtual void vf_000(type_1F8560 *arg_0);
    virtual void vf_004(type_1F8560 *arg_0);
    // Applies the update read.
    void sub_1A71E0();
    // Resets its state.
    void sub_1A7320();
    // Sets its id; resets it; attaches and detaches what it drives and what
    // shows it; shows and hides the latter.
    void sub_1A62D0(RwInt32 arg_0);
    void sub_1A62F0();
    void sub_1A6310(type_3E24E8 *arg_0);
    void sub_1A6360();
    // Told a remote player's hit-death values arg_0 and hit points arg_4:
    // empty, identical to other methods and folded (/OPT:ICF) into
    // sub_73D90; the remote player's sub_1BFFD0 calls it.
    void sub_73D90(RwInt8 *arg_0, RwInt32 arg_4);
    void sub_1A63A0(struct type_1BABA0 *arg_0);
    void sub_1A63E0();
    void sub_1A6420(type_4F6B00_120 *arg_0);
    void sub_1A6460();
    // Takes the time arg_0 (and marks its interface's unk_08).
    void sub_1A7A60(const type_1CCA10 &arg_0);
    // Its step at the time arg_0: driven (sub_1A65B0) or following its
    // updates (sub_1A7480, then what shows it).
    void sub_1A64A0(const type_1CCA10 &arg_0);
    // Bit accessors with no addresses, named for the field they access.
    // Evidence: sub_1A65B0 shifts a literal 1 by each inline index, returns
    // the masked value unchanged, and clears through 0xFFFF - (1 << index).
    RwUInt32 get_bit_4C(RwInt32 arg_0)
    {
        return unk_4C & (1 << arg_0);
    }
    void set_bit_4C(RwInt32 arg_0, RwInt32 arg_4)
    {
        if (arg_4)
            unk_4C |= 1 << arg_0;
        else
            unk_4C &= 0xFFFF - (1 << arg_0);
    }
    void sub_1A65B0(const type_1CCA10 &arg_0);
    void sub_1A7480(const type_1CCA10 &arg_0);
    void sub_1A6E80(const type_1CCA10 &arg_0);
    void sub_1A6F50();
    // A debug hook (empty; sub_1E4CB0, 0, folded) and a debug trace
    // (empty, with its eight arguments).
    RwInt32 sub_1E4CB0();
    void sub_1A7A90(type_1F8560_v *arg_0, type_1F8560_v *arg_4, RwReal arg_8, RwInt32 arg_C, RwInt32 arg_10,
                    RwInt32 arg_14, RwUInt32 arg_18, type_1CCA10 arg_1C);
    // Whether it is driven, shown, and shown in view: inlines with no
    // address, named for what they test. Evidence: sub_1A64A0 tests each
    // as a value made by setne (an int, not widened) before branching.
    RwInt32 is_driven()
    {
        return unk_11C != 0;
    }
    RwInt32 is_shown()
    {
        return unk_120 != 0;
    }
    RwInt32 is_visible()
    {
        return unk_124 != 0;
    }
    // An inline accessor for unk_130, with no address and so no database
    // name; named for its field. Evidence: the scores' checks (sub_1B2BC0,
    // sub_1B2C60) read it through a slot of their own.
    RwInt32 get_unk_130()
    {
        RwInt32 r = unk_130;
        return r;
    }
    // Debug hooks, empty in this build (folded by /OPT:ICF into sub_15FB30
    // and pDtor, 0x1E41C0).
    void sub_15FB30(RwInt32 arg_0);
    void sub_15FB30(type_1CCA10 arg_0);
    void pDtor();
};
extern RwUInt32 dword_4F6AB8[];
// The network timings (milliseconds; their dynamic initializers set 1000,
// 500, 100 and 500).
extern RwInt32 dword_4F7E80;
extern RwInt32 dword_4F7E84;
extern RwInt32 dword_4F7E88;
extern RwInt32 dword_4F7E8C;
// Previous sampled height, shared by the driven update (sub_1A65B0).
// IDA names the float at 0x4F6AF8 flt_4F6AF8.
#ifdef CODFH_PLAIN
extern RwReal &flt_4F6AF8;
#else
extern RwReal flt_4F6AF8;
#endif
extern type_4F6B00 unk_4F6B00[16];
// The indexed network player: an inline with no address, named for what
// it returns. Evidence: sub_1AED80 and sub_1ABC00 advance the register
// rotation between their derived-to-base conversion and argument push. The compiled-out
// range check supplies that load (docs/toolchain.md), with no extra slot.
inline type_4F6B00 &network_player(RwInt32 arg_0)
{
    if (arg_0 & ~15)
    {
    }
    return unk_4F6B00[arg_0];
}

// A mutable coordinate reference: an inline with no address. Evidence:
// sub_1AED80 keeps each matrix coordinate's address in a late temporary
// after the interface conversion, then loads and stores through it.
inline RwReal &position_component(RwReal &arg_0)
{
    return arg_0;
}
inline void type_4F8058::sub_1DE1A0_16()
{
    for (RwUInt32 i = 0; i < 16; i++)
    {
        sub_1DE1A0(&unk_4F6B00[i]);
    }
}

// The second player of a network game (0x22F0 bytes; vtables off_3E2960
// and, for its network part at +0x2260, off_3E292C): the multiplayer
// manager's unk_1A8, placed at a view (sub_1BD1C0) and taking a remote
// player's hits through its part; sub_1BAA90 builds it for its trigger.
// Named for its constructor.
struct type_1BABA0 : type_10F710, type_4F6B00_120
{
    type_1BABA0(type_712B0 *arg_0);
    // No destructor of its own: the compiler's (sub_1BADD0) calls the
    // player's with no vtable stores.
    // The placement pair it is built in entity memory with, as the local
    // player's, and its plain operator delete (all folded).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    static void operator delete(void *arg_0);

    // Overrides of the player's slots. The empty ones and those returning
    // 0 are folded (/OPT:ICF) into sub_15FB30, pDtor (0x1E41C0) and
    // sub_32260.
    virtual void vf_038(RwReal arg_0);
    virtual void vf_03C(RwReal arg_0);
    virtual void vf_044(RwReal arg_0)
    {
    }
    virtual void vf_04C(RwReal arg_0);
    virtual void vf_05C()
    {
    }
    virtual RwInt32 vf_060(type_3D3548 *arg_0)
    {
        return 0;
    }
    virtual RwInt32 vf_064(struct type_75600 *arg_0)
    {
        return 0;
    }
    virtual RwInt32 vf_068(struct type_758F0 *arg_0)
    {
        return 0;
    }
    virtual void vf_240(RwV3d *arg_0, RwReal arg_4);
    virtual RwInt32 vf_244();
    virtual void vf_258(RwReal arg_0);

    // The network part's slots: the remote player's state, its hits (a
    // bullet's, one that kills: health 0 and posture 10), and a death.
    virtual void pvf_000(type_1F8560_v *arg_0, type_4F6B00_F4 *arg_4, type_1F8560_v *arg_8, RwInt32 *arg_C,
                         RwInt32 *arg_10, RwInt32 *arg_14, RwUInt32 *arg_18, RwUInt16 *arg_1C);
    virtual void pvf_004()
    {
    }
    virtual void pvf_008()
    {
    }
    virtual void pvf_00C(RwInt32 arg_0)
    {
    }
    virtual void pvf_010(type_4F8058 *arg_0)
    {
    }
    virtual void pvf_014(type_75600 *arg_0);
    virtual void pvf_018(type_75600 *arg_0);
    virtual void pvf_01C(struct type_4AE70 *arg_0)
    {
    }
    virtual void pvf_020(struct type_4AE70 *arg_0);
    virtual void pvf_024()
    {
    }
    virtual void pvf_028(RwV3d *arg_0, RwInt32 arg_4)
    {
    }

    // Puts it at the view arg_0, still (the manager's sub_1AB2C0 and
    // sub_1AAF40).
    void sub_1BD1C0(RwMatrix *arg_0);

    type_1F8560_v unk_2264;
    type_1F8560_v unk_2270;     // its velocity (0.1 each at a view)
    RwUInt8 unk_227C[0x8];
    RwInt32 unk_2284;
    RwInt32 unk_2288;
    RwInt32 unk_228C;
    RwInt32 unk_2290;
    RwInt32 unk_2294;
    RwInt32 unk_2298;
    RwInt32 unk_229C;
    RwInt32 unk_22A0;
    RwInt32 unk_22A4;
    RwUInt8 unk_22A8[0x8];
    RwMatrix unk_22B0;          // its view (sub_1BD1C0), its frame's each step
};
typedef RwChar type_1BABA0_size_check[sizeof(type_1BABA0) == 0x22F0 ? 1 : -1];

// Built in entity memory for the trigger arg_0, or a warning that there is
// no entity memory for it.
type_1BABA0 *sub_1BAA90(type_712B0 *arg_0);

// What the second player's step hands the aim pass (sub_FCD90) as its data:
// only its layout is known (the ray's length first, then the ray).
struct type_1BAE40_58
{
    RwReal unk_00;
    RwV3d unk_04;
    RwV3d unk_10;
    RwReal unk_1C;
    RwInt32 unk_20;
    RwReal unk_24;
    RwInt32 unk_28;
};
// The line the second player's step tests (a .data RpIntersection), the
// aim ray's length (a script setting) and the rounds a fire counts.
extern RpIntersection intersection;
#ifdef CODFH_PLAIN
extern RwReal &flt_4B8F2C;
#else
extern RwReal flt_4B8F2C;
#endif
extern RwInt32 dword_42CAE8;
// The second player's view bob settings (vf_240), as the player's
// flt_42970C on: its lift's (a scale, a damping and a limit), its dip's and
// its sway's.
extern RwReal flt_42CAEC;
extern RwReal flt_42CAF0;
extern RwReal flt_42CAF4;
extern RwReal flt_42CAF8;
extern RwReal flt_42CAFC;
extern RwReal flt_42CB00;
extern RwReal flt_42CB04;
extern RwReal flt_42CB08;

#endif
