/*
 * type_3D3548: a base of the entity class family, anchored at its vtable
 * off_3D3548, which sub_73850 and sub_CC960 install. The derived vtables
 * traced (0x3D32F8, 0x3D5658, 0x3D9CB8, 0x3DAFC8, 0x3DBC78, 0x3DC9B0) reach
 * it through their constructor chains, and no base of it was found.
 *
 * Its vtable has 141 slots, +0x000 to +0x230 (a string follows it); +0x214
 * points at sub_D0760 (made a function in the database and split from
 * sub_D05C0's range in config/splits.txt when vf_210 was matched), and
 * sub_CCB70 at +0x22C registers the entity in the handle table.
 *
 * Virtual slots are declared in vtable order so a call compiles to the right
 * slot. A slot not yet established is named vf_<its byte offset in the
 * vtable> and declared `void ()`: its real signature is unknown. Folding
 * (/OPT:ICF) makes one body fill many slots (sub_1E4CB0 fills 31), so a slot
 * cannot be named after the function it points to.
 *
 * Fields: sub_CC960 uses offsets up to +0x35C and +0x384 belongs to this
 * class, so it ends between 0x388 and 0x3E0 (type_3DAFC8's first own field
 * is at or below +0x3E0). Only the fields below are established.
 */
#ifndef TYPE_3D3548_H
#define TYPE_3D3548_H

#include "rw/ostypes.h"
#include "rw/rphanim.h"
#include "rw/rtanim.h"
#include "rw/rpatomic.h"
#include "rw/rpmaterial.h"
#include "rw/rpcollis.h"
#include "rw/batypes.h"
#include "rw/baframe.h"
#include "rw/rtquat.h"
#include "types/type_8E670.h"
#include "game/vecutil.h"
#include "types/type_8A980.h"
#include "types/type_129_base.h"
#include "types/type_D48D0.h"
#include "types/type_3D96F0.h"

struct AIData;
struct type_3D2E7C;
struct type_3DAFC8;
struct type_3DAFC8_1DDC;
struct type_3DBC78;
struct type_10F710;
struct type_3DC048;

// type_6D380: an entity's performance player (type_3D3548::vf_090), named
// after its method sub_6D380, which plays the performance with id arg_0 (the
// rest only known by width).
struct type_6D380
{
    RwUInt8 unk_00[0x128];
    RwUInt8 unk_128;        // set to 1 by "StopCurrentPerformance"
    RwUInt8 unk_129[0x1B];
    RwInt32 unk_144;        // set to 2 by "PlayHitDeathAnim"; the last
                            // performance type played

    // An inline accessor for unk_144, with no address and so no database
    // name; named for its field. Evidence: "GetLastPerformanceTypePlayed"
    // reads it through a local placed after every check's.
    RwInt32 get_unk_144()
    {
        RwInt32 r = unk_144;
        return r;
    }
    // Likewise a setter. Evidence: the flag part's step (sub_1B2670) sets
    // it through a `this` temporary holding the entity's vf_090() result.
    void set_unk_144(RwInt32 arg_0)
    {
        unk_144 = arg_0;
    }

    // Advances the performance by the time step arg_0 (the entity's vf_03C).
    void sub_6D5A0(RwReal arg_0);
    // sub_47F90 passes its point and direction as arg_4 and arg_8.
    void sub_6D380(RwInt32 arg_0, RwV3d *arg_4, RwV3d *arg_8, RwInt32 arg_C,
                   RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C);
    // Stops the performance (sub_47F90 when none matches); only the widths
    // are known.
    void sub_6DDF0(RwInt32 arg_0, RwInt32 arg_4);
    // Starts performance arg_0 (the remote player's, sub_1BF5E0, when no
    // event is asked for); only the width is known.
    void sub_6D320(RwInt32 arg_0);
    // Whether performance arg_0 with the performance values arg_4 has a
    // transition ("DoesSceneHaveTranstion"); only the widths are known.
    RwInt32 sub_6CF50(RwInt32 arg_0, RwInt8 *arg_4, RwInt32 arg_8);
};

// type_5D4B0_2C: a copy of an entity's scene map entry (vf_0E0) with its two
// words replaced, a local of "DoesSceneHaveTranstion" (sub_5D4B0) at
// ebp-0x2C, named for it; it holds a byte array, so /GS guards it.
struct type_5D4B0_2C
{
    RwInt16 unk_00;
    RwInt16 unk_02;
    RwUInt8 unk_04[2];
};

// type_46840_30: a copy of an entity's twelve hit-death values (vf_0F0),
// a local of "PlayHitDeathAnimDefaultData" (sub_46840) at ebp-0x30, named
// for it; a byte array, so /GS guards it.
struct type_46840_30
{
    RwInt8 unk_00[0xC];
};

struct type_3DA6C0;
struct type_3DAC58;

// type_78AC0: what sub_78AC0 returns for an entity's unk_280, named after
// it; sub_48EE0 sets bit 0 of its flags unk_12. It is an animation player
// (the objects of CAnimObjectPool, unit_078AF0; type_7C8D0 is the same
// object as the entity's unk_284 sees it). Its queue of twelve 16-byte
// animation records at +0x34 is a ring from unk_20 (unk_24 of them).
struct type_78AC0_34
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwUInt32 unk_08;        // flags: bit 30 holds the animation
    RwInt32 unk_0C;
};

struct type_78AC0
{
    RwUInt8 unk_00[0x12];
    RwInt16 unk_12;
    RwUInt8 unk_14[0xC];
    RwInt32 unk_20;         // the ring's first record
    RwInt32 unk_24;         // the records in it
    RwUInt8 unk_28[0x4];
    RwUInt32 unk_2C;        // its tracks' count
    void *unk_30;           // its tracks
    type_78AC0_34 unk_34[12];

    // Sets or clears bit 0 of its flags: an inline with no address and so
    // no database name, named for the bit. Evidence: sub_6D5A0 and
    // sub_6DF90 clear it by normalising a zero held in a register to
    // 0 or 1 (`neg`/`sbb`/`neg`), which only a bool parameter gives; any
    // constant form folds.
    void set_unk_12_0(bool arg_0)
    {
        unk_12 = (RwInt16)((unk_12 & ~1) | (arg_0 ? 1 : 0));
    }
    // Releases the hold of its newest record (bit 30); returns true.
    bool sub_6DF40();
};
type_78AC0 *sub_78AC0(RwInt32 arg_0);

// type_7C8D0: an entity's animation (type_3D3548::unk_284 and unk_28C),
// named after its method sub_7C8D0, its duration; only a scale at +0x28 is
// known ("SetEntityScale", sub_45280, sets it).
// A track's interpolator (sub_80300 makes one): a 0x150-byte header, then
// its nodes' keyframes (0x720 bytes for the pool's) and after them its
// custom data.
struct type_80300_150
{
    RwUInt32 unk_00;
    void *unk_04;               // the interpolator's custom data
    RwV3d *unk_08;              // the clump's node vectors (sub_79270)
};
// Its callbacks (sub_808A0 sets one for a time, sub_80880 another) and its
// scheme's keyframe callbacks (copied from the RtAnimInterpolatorInfo; the
// one at +0x13C combines two interpolators' keyframes, sub_808D0).
typedef struct type_80300 *(*type_80300_cb)(struct type_80300 *arg_0, void *arg_4);
typedef void (*type_80300_kf)(type_80300_150 *arg_0, type_80300_150 *arg_4);
typedef void (*type_80300_blend)(type_80300_150 *arg_0, type_80300_150 *arg_4, type_80300_150 *arg_8,
                                 RwReal arg_C);
typedef void (*type_80300_decode)(type_80300_150 *arg_0, struct type_80300 *arg_4);
struct type_80300
{
    RtAnimAnimation *unk_00;    // the animation it plays
    RwInt16 unk_04[0x38];       // each node's current translation key
    RwInt16 unk_74[0x38];       // each node's current rotation key
    RwReal unk_E4;              // its time
    RwUInt16 unk_E8;
    RwInt8 unk_EA;              // bit 0: sub_7A580's arg_8 (sub_7F3C0 then
                                // poses identities)
    RwInt8 unk_EB;              // cleared when a procedural track starts
    void *unk_EC;               // the shared scratch keyframes (dword_44BA40)
    void *unk_F0;               // and their second half
    type_80300_cb unk_F4;
    void *unk_F8;
    RwReal unk_FC;              // unk_F4's time
    type_80300_cb unk_100;
    void *unk_104;
    RwInt32 unk_108;            // its keyframes' size
    RwV3d unk_10C;              // the root's position (sub_7C740 moves it)
    RtQuat unk_118;             // the root's rotation (sub_7A580 takes it out)
    void *unk_128;              // its animation's frames (or its own data)
    void *unk_12C;
    type_80300_blend unk_130;   // blends two interpolators' keyframes (sub_81170)
    void *unk_134;
    type_80300_decode unk_138;  // decodes its keys at its time (sub_80910)
    type_80300_kf unk_13C;
    void *unk_140;
    type_80300_150 *unk_144;    // its keyframes, just after it
    RwUInt8 unk_148[0x8];
};
typedef RwChar type_80300_size_check[sizeof(type_80300) == 0x150 ? 1 : -1];

// A track of a type_7C8D0 (0x2C bytes, following the player): the
// animation it plays, its flags, its data (released with sub_806E0) and its
// weight.
struct type_7C8D0_30
{
    RwInt32 unk_00;             // -1 when free
    RwInt16 unk_04;
    RwUInt8 unk_06[0x2];
    RwInt32 unk_08;             // the animation
    RwUInt16 unk_0C;            // flags (0x20: held on unload)
    RwUInt8 unk_0E[0x2];
    union
    {
        RtAnimAnimation *unk_10;    // its animation, or for a procedural
        void (*unk_10_cb)(struct type_7C8D0 *, struct type_80300 *, RwInt32,
                          bool);    // track (sub_79930) its callback (its
                                    // entity, and whether it starts:
                                    // sub_134320 reads a byte)
    };
    struct type_783F0 *unk_14;  // its events
    struct type_783F0_04 *unk_18;   // the next event
    struct type_80300 *unk_1C;  // active: its interpolator
    RwReal unk_20;
    RwReal unk_24;              // its weight (1 at first)
    RwInt32 unk_28;             // its start, in 100000ths of a second
};

// A queued animation of a type_7C8D0 (16 bytes, a ring of 12 at +0x34):
// its id and a flag in its third word.
struct type_7C8D0_34
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwInt32 unk_08_0 : 30;      // its id
    RwInt32 unk_08_30 : 1;      // sub_76920 tests it
    RwInt32 unk_08_31 : 1;
    RwInt32 unk_0C;
};

// How many records type_7C8D0's ring unk_34 holds: 12 in MP; 4 in single player (its
// constructor, SP 0x63390, sets up four and puts the tracks at +0x140 where MP's puts them at
// +0x1C0; MP's +0x100..+0x1B0 sit 0x80 lower).
#ifdef CODFH_SP // SP 0x63390
enum { type_7C8D0_ring_size = 4 };
#else // MP 0x78D60
enum { type_7C8D0_ring_size = 12 };
#endif
struct type_7C8D0
{
    // Destroyed through its vtable (CAnimObjectPool's sub_78CC0); pooled,
    // so its deleting destructor frees nothing.
    virtual ~type_7C8D0();

    RwUInt8 unk_04[0xC];
    RwInt16 unk_10;             // its pool
    RwInt16 unk_12;             // flags (type_78AC0's view)
    RwInt32 unk_14;
    RpHAnimHierarchy *unk_18;   // its bone hierarchy
                                // ("GetHierarchyPositionXFromAIObj")
    RwInt32 unk_1C;             // its entity (type_3D32F8's set-up), which
                                // the tracks' callbacks take as a word
    RwInt32 unk_20;             // the ring's first entry and count
    RwInt32 unk_24;
    RwReal unk_28;              // its scale
    RwUInt32 unk_2C;            // its tracks' count
    type_7C8D0_30 *unk_30;      // its tracks (just past it)
    type_7C8D0_34 unk_34[type_7C8D0_ring_size];
    RwUInt8 unk_F4[0xC];
    // Unaligned matrices: an aligned RwMatrix member would pad the vtable
    // pointer to 16 bytes and move every field (the image's player is 0x1C0
    // bytes with unk_04 at +4).
    RwMatrixTag unk_100;
    RwMatrixTag unk_140;
    RwUInt8 unk_180;
    RwUInt8 unk_181[0x3];
    RwInt32 unk_184;
    RwUInt8 unk_188;
    RwUInt8 unk_189[0x3];
    RwReal unk_18C;
    RwV3d unk_190;              // a direction (sub_7A100 turns it)
    union
    {
        RtQuat unk_19C_q;       // a rotation (sub_7A100 accumulates it)
        struct
        {
            RwReal unk_19C;
            RwReal unk_1A0;     // the turn, as the sine and
            RwReal unk_1A4;
            RwReal unk_1A8;     // cosine of half its angle ("GetTurnAmount")
        };
    };
    RwUInt8 unk_1AC;
    RwUInt8 unk_1AD[0x3];
    struct type_80300 *unk_1B0; // its pose's interpolator, released with sub_806E0
    RwUInt8 unk_1B4[0xC];       // (0x1C0 bytes, its tracks following)

    // Takes the hierarchy arg_0 and memory for its matrices (sub_80550,
    // sub_80740).
    void sub_79470(RpHAnimHierarchy *arg_0);
    // Built in a pool slot (sub_6CCF0) for arg_0 tracks (sub_78D60).
    type_7C8D0(RwInt32 arg_0);
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    // Pooled: out of line and empty (folded into sub_19A750), so its
    // deleting destructor frees nothing.
    static void operator delete(void *arg_0);
    RwReal sub_7C8D0();
    // The root's bounding box and rotation this frame (sub_7C1A0); taking
    // them into unk_190 and unk_19C (sub_7A100).
    RwReal sub_7C1A0(RwBBox *arg_0, RtQuat *arg_4);
    bool sub_7A100();
    // Updates flag 4 of unk_12 from its tracks, and settles unk_184 with
    // sub_7F3C0 (arg_4 picks the mode; arg_0 is unused).
    void sub_7C090(RwReal arg_0, bool arg_4);
    // The track after arg_4 (the first for 0) in the queue record arg_0.
    struct type_7C8D0_30 *sub_7C350(RwInt32 arg_0, struct type_7C8D0_30 *arg_4);
    // The serial of the track after the serial arg_4 (the first for 0) in
    // the record arg_0 before the newest, or 0.
    RwInt32 sub_7C3E0(RwInt32 arg_0, RwInt32 arg_4);
    // The track arg_0's first event at arg_4 with the id arg_8 (sub_78550).
    struct type_783F0_04 *sub_7C480(RwInt32 arg_0, RwReal arg_4, RwInt32 arg_8);
    // The animation of the newest record's first track; the tracks in use;
    // setting every track's weight to arg_0.
    RwInt32 sub_7C850();
    RwInt32 sub_7C940();
    bool sub_7C9D0(RwReal arg_0);
    // Whether the newest queued animation has its flag set.
#ifdef CODFH_SP // single player expands it inline over its four-record ring (SP 0xE6EE0, 0xE6800)
    bool sub_76920()
    {
        RwInt32 var_4;

        var_4 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
        return (bool)unk_34[var_4].unk_08_30;
    }
#else
    bool sub_76920();
#endif
    // The weight of the animation arg_0, and setting it (arg_4); only the
    // widths are known.
    RwReal sub_7C9A0(RwInt32 arg_0);
    bool sub_79C90(RwInt32 arg_0, RwReal arg_4);
    // Starts a procedural track run by the callback arg_0 (arg_4, weight
    // arg_8); stops the track arg_0; sets flag 2 of the track arg_0 to arg_4.
    RwInt32 sub_79930(void (*arg_0)(struct type_7C8D0 *, struct type_80300 *, RwInt32, bool),
                      RwReal arg_4, RwReal arg_8);
    bool sub_79BC0(RwInt32 arg_0);
    bool sub_79CE0(RwInt32 arg_0, bool arg_4);
    // Whether the queued animation arg_0 still plays; only the widths are
    // known.
#ifdef CODFH_SP // an inline in single player: VC keeps it out of line (SP 0xE43E0), but its
                // callers know its body (SP 0xE68B0 keeps unk_824 in a register across it)
    bool sub_76E00(RwInt32 arg_0)
    {
        RwInt32 var_4;
        RwInt32 local_8;

        local_8 = arg_0 & 0xFF;
        var_4 = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
        if (unk_30[local_8].unk_00 == arg_0)
            return unk_30[local_8].unk_04 == var_4;
        return false;
    }
#else
    bool sub_76E00(RwInt32 arg_0);
#endif
    // The id of the queued animation arg_0 before the newest: an inline
    // with no address and so no database name, named for its field.
    // Evidence: type_3D32F8's sub_76860 loads its constant 0 and adds 1
    // (xor, add) where sub_76920 folds the 1, through a `this` copy and a
    // local.
    // An inline setter for unk_28 (its scale), with no address and so no
    // database name; named for its field. Evidence: type_3DAFC8::sub_13C490
    // copies the value and the animation into temporaries before storing.
    void set_unk_28(RwReal arg_0)
    {
        unk_28 = arg_0;
    }
    // Likewise for the flags unk_12. Evidence: type_3DAFC8::sub_135430 sets
    // a bit through a word temporary (the parameter) before storing.
    void set_unk_12(RwInt16 arg_0)
    {
        unk_12 = arg_0;
    }
    RwInt16 get_unk_34_id(RwInt32 arg_0)
    {
        RwInt32 i = (unk_20 + unk_24 - (arg_0 + 1)) % type_7C8D0_ring_size;
        return (RwInt16)unk_34[i].unk_08_0;
    }
    // Clears the newest record's unk_08_30 (type_78AC0::sub_6DF40 does the
    // same out of line); an inline with no address and so no database
    // name, named for what it does. Evidence: the mounted weapon's fire
    // (type_3DC9B0::sub_169380) indexes the ring through a local of its own
    // after a copy of the player.
#ifdef CODFH_SP // SP drops this addressless helper after its callers inline it.
    __forceinline void clear_last_unk_08_30()
#else
    void clear_last_unk_08_30()
#endif
    {
        RwInt32 i = (unk_20 + unk_24 - 1) % type_7C8D0_ring_size;
        unk_34[i].unk_08_30 = 0;
    }
    // Turns towards the direction *arg_0 ("SetTurnMode"): sub_79D50 from
    // the root's parent frame's position; true.
    bool sub_7A0A0(RwV3d *arg_0);
    // Aims the root motion at the point arg_0 facing the direction arg_4:
    // unk_190 the way there in the frame's space, unk_19C_q the turn from
    // the frame to that heading; true.
    bool sub_79D50(RwV3d *arg_0, RwV3d *arg_4);
    // Blend time arg_0, then play the facial animation arg_0 of group arg_4
    // (sub_5AC50, "PlayFacialAnimation"); only the widths are known.
    bool sub_794C0(RwReal arg_0);
    // Advances the player by arg_0 ms, its root's movement into *arg_4
    // (none for 0); arg_8 only known by width.
    void sub_7A580(RwReal arg_0, RwV3d *arg_4, bool arg_8);
    RwInt32 sub_796A0(RtAnimAnimation *arg_0, RwInt32 arg_4, RwInt32 arg_8,
                      struct type_783F0 *arg_C, RwReal arg_10, RwReal arg_14, RwReal arg_18);

    // An inline accessor for unk_18, with no address and so no database
    // name; named for its field. Evidence: the HUD's render
    // (type_DC400::sub_DF000) reads the hierarchy through a result of its
    // own each time.
    RpHAnimHierarchy *get_unk_18()
    {
        RpHAnimHierarchy *r = unk_18;
        return r;
    }
    // Likewise for unk_24. Evidence: a vehicle's vf_170 compares it through
    // a result of its own after reading it plainly once.
    RwInt32 get_unk_24()
    {
        RwInt32 r = unk_24;
        return r;
    }
};
typedef RwChar type_7C8D0_size_check[sizeof(type_7C8D0) == 0x100 + 0x10 * type_7C8D0_ring_size ? 1 : -1];

typedef struct RpClump RpClump;

// A movement step as vf_210 adjusts it: its point, and a height at +0x48.
// The entity keeps one at +0xC0 (its fields there are declared flat).
struct type_D05C0
{
    RwV3d unk_00;               // its position
    RwV3d unk_0C;
    RwV3d unk_18;               // its velocity (vf_20C)
    RwV3d unk_24;
    RwV3d unk_30;               // its rate of turn (vf_20C)
    RwV3d unk_3C;
    RwReal unk_48;
    // The rest as vf_214 (sub_D0760) reads it (the entity's +0x10C on).
    RwV3d unk_4C;
    RwV3d unk_58;               // scales the push vf_214 adds
    RwV3d unk_64;               // the velocity's limits (each way)
    RwInt32 unk_70;             // set: vf_214 eases the velocity in
    RwV3d unk_74;
    RwV3d unk_80;
    RwInt32 unk_8C;
    RwInt32 unk_90;
    RwV3d unk_94;               // a velocity added for one step
    RwV3d unk_A0;               // a turn added for one step
    RwV3d unk_AC;               // the last step's move
    RwV3d unk_B8;               // the last step's turn
};
// type_3D3548_390: three words the entity clears when it registers and
// when it is taken down (sub_CCB70, sub_CCD30).
// type_93700: a collision query as sub_93700 and sub_97790 fill it; only
// the entity asking and its done flag are known.
struct type_93700
{
    RwUInt8 unk_00[0x4];
    struct type_3D3548 *unk_04;     // the searching entity
    struct type_3D3548 *unk_08;     // the atomic's entity (sub_D1990)
    RwUInt8 unk_0C[0x4];
    RpAtomic *unk_10;               // the atomic
    RwUInt8 unk_14[0x4];
    RwMatrix *unk_18;               // its frame's matrix, that matrix
    RwMatrix *unk_1C;               // orthonormalised and inverted (sub_D1990's
    RwMatrix *unk_20;               // locals)
    RwUInt8 unk_24[0x8];
    RwV3d unk_2C;                   // the sphere's centre
    RwUInt8 unk_38[0x24];
    RwInt32 unk_5C;
    RwInt32 unk_60;                 // set when a triangle is hit
    RwUInt8 unk_64[0x30];
    RwReal unk_94;                  // the nearest hit's distance squared
    RwV3d unk_98;                   // and its normal
};
// The sphere search vf_084 runs over its clump's atomics (sub_D1990): the
// sphere and the triangle search's state.
struct type_D1990
{
    RwSphere *unk_00;
    type_93700 *unk_04;
};
RpAtomic *sub_D1990(RpAtomic *arg_0, void *arg_4);
// Their triangle callbacks (16-aligned frames).
RpCollisionTriangle *sub_93700(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8,
                               void *arg_C);
RpCollisionTriangle *sub_97790(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8,
                               void *arg_C);

// A frame's plugin data (sub_FBC30 finds it at the offset dword_4C1930;
// types/type_3D96F0.h).
type_3D96F0 *sub_FBC30(RwFrame *arg_0);

// Take the clump or atomic arg_0 out of its world, if any; return the world.
RpWorld *sub_1735A0(RpClump *arg_0);
RpWorld *sub_173620(RpAtomic *arg_0);
// The clump's first atomic (the database's name).
RpAtomic *Clump_FindFirstAtomic(RpClump *arg_0);
// Detach the frame arg_0 (keeping its world matrix), or each child frame of
// the atomic arg_0's frame, when the entity owning it is not arg_4 (vf_228's
// callbacks); the database's names.
RwFrame *Frame_DetachWhenOwnerDiffers(RwFrame *arg_0, void *arg_4);
RpAtomic *Frame_DetachAtomicChildrenWhenOwnerDiffers(RpAtomic *arg_0, void *arg_4);

// type_D18C0: the nearest-hit search Collision_AccumulateNearestAtomicLineIntersection
// runs (vf_084): the line's two points, the nearest distance so far and
// where the hit's normal goes (or 0).
struct type_D18C0
{
    RwV3d *unk_00;
    RwReal *unk_04;
    RwV3d *unk_08;
};

struct type_3D3548_390
{
    union
    {
        struct
        {
            RwInt32 unk_00;
            RwInt32 unk_04;
            RwInt32 unk_08;
        };
        RwV3d v;            // as a vector (sub_D3FF0, sub_D41A0)
    };

    // Inline, with no address and so no database name; named for what it
    // does. Evidence: both callers clear the words through a `this`
    // temporary.
    void clear()
    {
        unk_00 = 0;
        unk_04 = 0;
        unk_08 = 0;
    }
};

// A prop event's data (type_3D3548::vf_170, the event 2201): the prop's
// slot (unk_0C) and whether it is shown again (unk_0D).
struct type_CE070_prop
{
    RwInt32 unk_00[3];
    RwInt8 unk_0C;
    RwInt8 unk_0D;
};
// The soldier's tracking event's data (the event 2300): its kind, whether
// it tracks and a time (type_3DAFC8::sub_1340D0).
struct type_CE070_track
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwReal unk_08;
};

// What an entity's trigger callback (type_3D3548::unk_388) is called as.
typedef void (*type_3D3548_388)(struct type_3D3548 *arg_0, RwReal arg_4);

struct type_3D3548
{
    // +0x000: whether it is in view; sets unk_28_13 and returns 1 (the test
    // of its bounding sphere against the six frustum planes after that is
    // unreachable). arg_0 is only known by width.
    virtual RwInt32 vf_000(void *arg_0);
    // +0x004: the destructor (the scalar deleting destructor fills the
    // slot). Defined here and not expanded: it takes the entity down
    // (vf_230), then the members' destructors run; its out-of-line copy is
    // sub_73850 (unit_073710), and every derived destructor reserves the
    // frame of its members' inline destructors (20 bytes).
    virtual ~type_3D3548()
    {
        vf_230();
    }

    // +0x008: a checked downcast. The base (sub_1E4CB0) returns 0; type_3DAFC8
    // and its descendants return this (sub_6FCD0).
    virtual type_3DAFC8 *vf_008();

    // +0x00C: a checked downcast to the player class type_10F710 (0 for
    // other entities); sub_136C0 calls its vf_200.
    virtual type_10F710 *vf_00C();

    // +0x010: another entity, of type_3DBC78's family: sub_126B0 calls its
    // vf_2C4, a type_3DBC78 slot.
    virtual type_3DBC78 *vf_010();

    // +0x014: a checked downcast. The base (sub_1E4CB0) returns 0; type_3DC048
    // and off_3DC378 return this (sub_6FCD0).
    virtual type_3DC048 *vf_014();
    // +0x018: another checked downcast, to the flak vehicle type_3DC378
    // (its slot returns this, sub_6FCD0); tested against zero by
    // AIData::sub_1C4F0.
    virtual struct type_3DC378 *vf_018();
    // +0x01C and +0x020: checked downcasts to type_3DA6C0 and type_3DAC58
    // (their slots return this, sub_6FCD0).
    virtual type_3DA6C0 *vf_01C();
    virtual type_3DAC58 *vf_020();
    // +0x024: a downcast like vf_008 (the base sub_1E4CB0 returns 0): the
    // entity itself when it is a type_3DDB98. Tested against zero by
    // AIData::sub_1E210; "SetEntityScale" (sub_45280) reads unk_28C through
    // it.
    virtual struct type_3DDB98 *vf_024();
    // +0x028: the mounted weapon of the entity the player's unk_210C holds
    // ("SetMyMMGYawAndPitch").
    virtual struct type_3DC9B0 *vf_028();
    // +0x02C: a downcast like vf_008: the entity itself when it is a
    // type_3DE0E0 (sub_6FCD0), else 0 (sub_1E4CB0); the script commands then
    // cast the entity ("SetMyTarget", "FireWeaponContinuous").
    virtual struct type_3DE0E0 *vf_02C();
    // +0x030: a checked downcast like vf_02C: type_3DE350 returns itself
    // (sub_6FCD0), the base 0 (sub_1E4CB0).
    virtual struct type_3DE350 *vf_030();
    // +0x034: another checked downcast, of an entity kind whose trigger
    // holds damage flags (type_712B0_034); only tested against zero here.
    virtual RwInt32 vf_034();
    // +0x038: only the width is known (type_3D5658's sub_9CE70 calls the
    // base's, sub_15FB30, first, and passes the value on to
    // AIData::sub_17190).
    virtual void vf_038(RwReal arg_0);
    // +0x03C: the per-frame update for the time step arg_0; type_3D3548's own
    // is sub_CF0E0.
    virtual void vf_03C(RwReal arg_0);
    // +0x040: moves it by the time step arg_0 (vf_20C, vf_210, vf_214; a
    // soldier's step is at most 4).
    virtual void vf_040(RwReal arg_0);
    virtual void vf_044(RwReal arg_0);
    // +0x048: pushes the player out of its bump radius (unk_380), then
    // updates it (vf_044) with arg_0.
    virtual void vf_048(RwReal arg_0);
    // +0x04C: only the width is known (type_3D5658's sub_9CF20 calls the
    // base's, sub_D0390, first and passes it on to AIData::sub_17A20).
    virtual void vf_04C(RwReal arg_0);
    // +0x050: updates its trigger volume (sub_144C80; arg_0 unused).
    virtual void vf_050(RwReal arg_0);
    // +0x054: only the width is known (type_3D51C0's sub_9B5F0 calls the
    // base's, sub_D2820).
    virtual void vf_054(RwInt32 arg_0);
    // +0x058: whether arg_0 is one of the entity's keys (type_3D32F8's
    // sub_75E40 matches its trigger's unk_C0 and unk_C8).
    // Pure (the vtable's slot is _purecall).
    virtual RwInt32 vf_058(struct type_3DF8D8_04 *arg_0) = 0;
#ifndef CODFH_SP // MP @ 0x3D3548 slot 0x05C; SP @ 0x2E08D0 has no such slot (0x05C is vf_060)
    virtual void vf_05C();
#endif
    // +0x060: a touch by the entity arg_0 (the player's sub_10EF70 pushes
    // itself out of it); 0.
    virtual RwInt32 vf_060(type_3D3548 *arg_0);
    // +0x064, +0x068: a bullet's and an explosion's hit; +0x06C: a
    // collision with the entity arg_0; +0x070: whether the explosion arg_0
    // reaches the entity (arg_4 and arg_8 only known by width). The handlers
    // return 0 (type_3D32F8's).
    virtual RwInt32 vf_064(struct type_75600 *arg_0);
    virtual RwInt32 vf_068(struct type_758F0 *arg_0);
    virtual RwInt32 vf_06C(type_3D3548 *arg_0);
    // vf_070 tests the explosion arg_0 against the entity with line tests
    // (sub_D2FC0) from it to the entity's position and eye point; *arg_8
    // (when given) is set once the first passes. arg_4 is only known by
    // width.
    virtual RwInt32 vf_070(struct type_758F0 *arg_0, RwInt32 arg_4, RwInt32 *arg_8);
    // +0x074: the atomic arg_0's triangles against the line arg_4, into the
    // query arg_8: through sub_97790 for a soldier's query, else sub_93700
    // (the database's name). Without geometry the query is marked done.
    virtual void Collision_DispatchAtomicIntersectionsBySelectorFlag(RpAtomic *arg_0,
                                                                     RpIntersection *arg_4,
                                                                     struct type_93700 *arg_8);
    virtual void vf_078();
    // +0x07C, +0x080, +0x084: intersect the line of arg_4 with the entity
    // (AIData's sub_2C9B0 passes 1, 1 or 3 in arg_0 and the distance to
    // update in arg_8); vf_07C returns -1 for a miss, the others are tested
    // against zero. The last arguments are only known by width.
    // (vf_07C's arg_0 is a char: type_3D5658's sub_9D620 tests it with
    // movsx.)
    virtual RwInt32 vf_07C(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwInt32 arg_C);
    virtual RwInt32 vf_080(RwInt32 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwReal arg_C);
    // vf_084: mode 3 is a line (the nearest hit along it into *arg_8 and its
    // normal into *arg_C); otherwise arg_4 is a type_D1990 sphere search.
    virtual RwInt32 vf_084(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwV3d *arg_C);
    // +0x088: sets the entity's performance kind (the script commands
    // "PlayCurrentPerformance" pass 0, "PlaySpecialIdlePerformance" 1);
    // only the width is known.
    virtual void vf_088(RwInt32 arg_0);
    // +0x08C: the entity's performance values (a byte array; the script
    // commands "SetPerformanceValue", "GetPerformanceValue" pass 0, 0,
    // "SetSpecialIdlePerformanceValue" 0, 1, "SetupAssassinationValues"
    // 1, 0); only the widths are known.
    virtual RwUInt8 *vf_08C(RwInt32 arg_0, RwInt32 arg_4);
    // +0x090: the entity's performance player (type_6D380).
    virtual struct type_6D380 *vf_090();
    // +0x094, +0x0A0: set the handles vf_090 and vf_098 resolve
    // (type_3D51C0's sub_9AF90 and sub_9AF30).
    virtual void vf_094(RwUInt32 arg_0);

    // +0x098: the entity's type_3D2E7C (the entity classes resolve a handle
    // with sub_67620: sub_13F620, sub_155430); the base sub_1E4CB0 returns 0.
    virtual type_3D2E7C *vf_098();
    // +0x09C: AIData::sub_30A50 passes its result to sub_6B5F0 by address;
    // only its width is known.
    virtual RwInt32 vf_09C();
    virtual void vf_0A0(RwUInt32 arg_0);
    // +0x0A4: disables performances by arg_0 ("DisablePerformances"); only
    // the width is known.
    virtual void vf_0A4(RwInt32 arg_0);
    // +0x0A8: nonzero while the entity may not start a performance
    // (sub_47F90); only the width is known.
    virtual RwInt32 vf_0A8();
    // +0x0AC: a value "SetupAssassinationValues" copies into a byte of the
    // hit-death values; "WillTransitionPlay" passes it on as a dword, unextended.
    // It is also the entity's posture ("GetPosture"); +0x0B0 sets it with
    // arg_4 ("SetPosture" passes 1) and +0x0BC gives a player's
    // ("GetPlayerPosture").
    virtual RwInt32 vf_0AC();
    virtual void vf_0B0(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_0B4();
    // +0x0B8: sets the value +0x0B4 derives (type_3D5658's sub_9C4A0).
    virtual void vf_0B8(RwInt32 arg_0);
    virtual RwInt32 vf_0BC();
    // +0x0C0: moves the entity to arg_0 (sub_CD5F0 for type_3DAFC8 writes
    // its frame's position).
    virtual void vf_0C0(RwV3d *arg_0);
    // +0x0C4: the entity's trigger volume, for sub_144F20
    // ("IsNamedEntityInTrigger").
    virtual RwReal *vf_0C4();
    // +0x0C8: a vector AIData::sub_1A630 takes the length of (a velocity, by
    // its use as a speed) and dots with the facing (sub_CD5A0).
    virtual RwV3d *vf_0C8();
    // +0x0CC: a point AIData::sub_19780 hands to sub_17140 as the target.
    virtual RwV3d *vf_0CC();
    // +0x0D0: moves the entity to arg_0 ("SetMyOrientation", which adds
    // arguments to its position; only the width is known).
    virtual void vf_0D0(RwV3d *arg_0);
    // +0x0D4: orients the entity by the quaternion arg_0 (sub_CD790 for
    // type_3DAFC8).
    virtual void vf_0D4(RtQuat *arg_0);
    // +0x0D8: faces the entity along arg_0 ("TeleportToNamedObject" passes
    // a matrix's at vector).
    virtual void vf_0D8(RwV3d *arg_0);
    // +0x0DC: the destruction id ("GetDestructionID").
    virtual RwInt32 vf_0DC();
    // +0x0E0 to +0x0EC: the entity's scene: its map entry (sub_48EE0), the
    // message of action arg_0 ("GetSceneActionMsg"), the action count
    // ("GetSceneActionCount") and value arg_4 at index arg_0
    // ("SetSceneValue").
    virtual RwUInt8 *vf_0E0();
    virtual RwInt32 vf_0E4(RwInt32 arg_0);
    virtual RwInt32 vf_0E8();
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4);
    // +0x0F0: the entity's hit-death values (a byte array;
    // "SetHitDeathValue", "SetupAssassinationValues").
    virtual RwInt8 *vf_0F0();
    // +0x0F4: the entity's spline path ("HasDefaultSplinePath",
    // "GetClosestPositionOnSpline").
    virtual struct SplinePath *vf_0F4();
    // +0x0F8: its position on its spline path ("SetSplinePosition";
    // "DivorceSplinePath" passes 0).
    virtual void vf_0F8(RwReal arg_0);
    virtual RwReal vf_0FC();
    virtual RwReal vf_100();
    // +0x104: the entity's head matrix into arg_0 (type_3D5658's sub_9D370).
    virtual void vf_104(RwMatrix *arg_0);
    // +0x108: the entity's eye point into arg_0 (the Vision Scheduler's
    // sub_421C0 draws its line of sight from it).
    virtual void vf_108(RwV3d *arg_0);
    // +0x10C: the entity's view range (the Vision Scheduler squares it,
    // sub_40BD0).
    virtual RwReal vf_10C();
    // +0x110: its centre into arg_0: its bounding sphere's centre in its
    // frame, else its position (AIData::sub_228A0 passes its owner and 1 for
    // the rest, only known by width).
    virtual void vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);

    // +0x114: a float, compared with fcomp by sub_150F0; the preferred
    // attack range ("GetPreferredAttackRange").
    virtual RwReal vf_114();
    // +0x118: the next member of the entity's group (type_3DF30), 0 after
    // the last: the kinds' updates (sub_335D0, sub_34930) walk a group from
    // its leader with it. type_3CE278::sub_32D30 only sends a member to a
    // node when the leader has another.
    virtual type_3D3548 *vf_118();
    // +0x11C: sets the next entity in the group's list (vf_118 reads it;
    // type_3DF30::sub_3E650).
    virtual void vf_11C(type_3D3548 *arg_0);

    // +0x120: the entity's AI object. The base (sub_1E4CB0) returns 0;
    // overrides return an embedded AIData (sub_9C610: this + 0x520,
    // sub_FD960: + 0x550, sub_135110: + 0x8A0, sub_14CD40: + 0x11A0).
    virtual AIData *vf_120();
    // +0x124, +0x128: its spline increment ("SetSplineIncrement",
    // "GetSplineIncrement").
    virtual void vf_124(RwReal arg_0);
    virtual RwReal vf_128();
    // +0x12C: moves it along its spline by its animation or not
    // ("SetSplineMovementByAnimation").
    virtual void vf_12C(RwInt32 arg_0);
    // +0x130: the entity's hearing radius (AIHearing's sub_3C7D0 adds its
    // square to the sound's).
    virtual RwReal vf_130();
    // +0x134: sub_31C50 asks whether the entity can shoot arg_4 from the
    // offset arg_0 (with the AI's unk_548, 0 and -1); 0 means the path is
    // blocked, when *arg_14 says by what. *arg_10 is a flag. Only the widths
    // are known otherwise.
    virtual RwInt32 vf_134(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                           RwInt32 *arg_10, RwInt32 *arg_14, RwInt32 arg_18);
    // +0x138: a value only known by width (the player's is its unk_1B38).
    virtual RwInt32 vf_138();
    // +0x13C: whether the weapon is out of ammunition ("IsMyWeaponOutOfAmmo");
    // +0x140 reloads it ("ForceMyWeaponToReload").
    virtual RwInt32 vf_13C();
    virtual void vf_140();

    // +0x144 to +0x150: the weapon's ranges ("GetWeaponsMinMediumRange",
    // "GetWeaponsMinLongRange", "GetWeaponsTooCloseForComfortRange",
    // "GetWeaponsStandMeleeRange"). The base of vf_144 (sub_73BC0) returns
    // the constant flt_3CD84C; sub_14800 compares vf_144 with a record's
    // float, sub_12970 vf_14C.
    virtual RwReal vf_144();
    virtual RwReal vf_148();
    virtual RwReal vf_14C();
    virtual RwReal vf_150();
    // +0x154, +0x158: the lunge and run melee ranges
    // ("GetWeaponsLungeMeleeRange", "GetWeaponsRunMeleeRange").
    virtual RwReal vf_154();
    virtual RwReal vf_158();
    // +0x15C: whether the weapon is a bolt-action rifle
    // ("GetWeaponIsBoltActionRifle").
    virtual RwInt32 vf_15C();
    // +0x160: the weapon's group type ("GetMyWeaponGroupType"); AIData's
    // sub_23A10 compares it with 3.
    virtual RwInt32 vf_160();
    // +0x164, +0x168: floats (the base returns 0, sub_73BC0; the soldier its
    // unk_88C and unk_890).
    virtual RwReal vf_164();
    virtual RwReal vf_168();
    // +0x16C: sets AI parameter arg_0 to arg_4 ("SetAIParam": the script's
    // value, a float's bits); returns 1 (type_3D5658's sub_9D220).
    virtual RwInt32 vf_16C(RwInt32 arg_0, RwInt32 arg_4);
    // +0x170: type_3D3548's own is sub_CE070 (type_3D32F8's sub_75440 calls
    // it); only the widths of its four arguments are known.
    virtual void vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // +0x174: the hit points ("GetHitPoints"); "PlayHitDeathAnim" asks for
    // performance kind 7 while they are not positive, else 6.
    virtual RwInt32 vf_174();
    // +0x178: sets them ("SetHitPoints"; "SetupAssassinationValues" passes
    // -1).
    virtual void vf_178(RwInt32 arg_0);
    // +0x17C: a float; the HUD (type_DC400::sub_DFFC0) shows a buddy's as
    // the width of its health bar, so likely the hit points' fraction.
    virtual RwReal vf_17C();
    // +0x180: adds to them ("IncrementHitPoints").
    virtual void vf_180(RwInt32 arg_0);
    // +0x184, +0x188: the damage level ("GetDamageLevel", "SetDamageLevel").
    virtual RwInt32 vf_184();
    virtual void vf_188(RwInt32 arg_0);
    // +0x18C: gravity on or off ("SetGravity").
    virtual void vf_18C(RwInt32 arg_0);
    // +0x190: collision on or off ("SetCollision").
    virtual void vf_190(RwInt32 arg_0);
    // +0x194 to +0x19C: the environment, wall and ground collision
    // notifications ("SetEnvCollisionNotification" and the like;
    // "SetCollisionNotifyFlag" also sets +0x194).
    virtual void vf_194(RwInt32 arg_0);
    virtual void vf_198(RwInt32 arg_0);
    virtual void vf_19C(RwInt32 arg_0);
    // +0x1A0, +0x1A8: environment and entity collision on or off
    // ("SetEnvironmentCollision", "SetEntityCollision").
    virtual void vf_1A0(RwInt32 arg_0);
    // +0x1A4: rendering off or on ("SetNoRender").
    virtual void vf_1A4(RwInt32 arg_0);
    virtual void vf_1A8(RwInt32 arg_0);
    // +0x1AC: the entity's collision priority (the script command
    // "SetPriorityCollision", sub_451E0, passes its argument).
    virtual void vf_1AC(RwInt32 arg_0);
    // +0x1B0, +0x1B4: firing ("SetFiring", "AllowFiring").
    virtual void vf_1B0(RwInt32 arg_0);
    virtual void vf_1B4(RwInt32 arg_0);
    // +0x1B8: trigger collision on or off ("SetTriggerCollision").
    virtual void vf_1B8(RwInt32 arg_0);
    // +0x1BC: sets unk_88_13 (0x73CE0).
    virtual void vf_1BC(RwInt32 arg_0);
    // +0x1C0: the primary animation's bone matrices; the database's name.
    virtual RwMatrix *Animation_GetMatrixArray();
    // +0x1C4: hit the ground (arg_0 set) or a wall (type_3D5658's
    // sub_9DBB0).
    virtual void vf_1C4(RwInt32 arg_0);
    // The embedded type_3DAFC8_1DDC for a type_3DAFC8 (sub_1352C0), else 0
    // (sub_1E4CB0).
    virtual type_3DAFC8_1DDC *vf_1C8();
    // +0x1CC: the soldier drops its pickup (arg_0: floating); the base's
    // is empty (sub_15FB30).
    virtual void vf_1CC(RwInt32 arg_0);
    // +0x1D0: marks the path nodes within its radius (unk_4C) and less than
    // 75 below or 150 above it (their unk_08 set to the time dword_4B87C8
    // plus 30).
    virtual void vf_1D0();
    // +0x1D4: unk_290, the tag of the surface it stands on (0x73D10).
    virtual RwInt32 vf_1D4();
    // +0x1D8: its action item ("SetActionItem").
    virtual void vf_1D8(RwInt32 arg_0);
    virtual RwInt32 vf_1DC();
    virtual RwReal vf_1E0();
    // +0x1E4: nonzero lets type_3D410's sub_3DE00 accept an entity with
    // flag 4 of unk_2C whose vf_200 is set; only its width is known.
    virtual RwInt32 vf_1E4();
    // +0x1E8: whether it throbs ("SetThrobbing").
    virtual void vf_1E8(RwInt32 arg_0);
    // +0x1EC: advances the throb by arg_0 (unk_2A0 up to 30 and back to 0,
    // unk_88_11 giving the direction).
    virtual void vf_1EC(RwReal arg_0);
    // +0x1F0, +0x1F4: the damage and force of its blows (sub_D42D0).
    virtual RwReal vf_1F0();
    virtual RwReal vf_1F4();
    // +0x1F8: an entity the entity is attached to (the Vision Scheduler's
    // sub_42350 lets a line of sight pass through it); only the width of
    // arg_0 is known (0 is passed).
    virtual type_3D3548 *vf_1F8(RwInt32 arg_0);
    // +0x1FC: attaches the prop arg_0 (0 detaches it; "AttachProp",
    // "DetachProp"); both pass 0 for arg_4, only its width is known.
    virtual void vf_1FC(type_3D3548 *arg_0, RwInt32 arg_4);

    // +0x200: another entity (AIData::sub_29410 takes its position with
    // sub_CD550); tested against zero by sub_136C0.
    virtual type_3D3548 *vf_200();
    // +0x204: its update callback ("SetUpdateCallBack", with its three
    // arguments); only the widths are known.
    virtual void vf_204(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // +0x208: plays the animation arg_0 (flags arg_4; with the blend arg_C,
    // the speed arg_10 and arg_14; type_3D2CD0::sub_6DE40); whether it
    // could. Only the widths are known.
    virtual RwInt32 vf_208(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C,
                           RwReal arg_10, RwReal arg_14, RwInt32 arg_18);
    // +0x20C: integrates the motion arg_0 over arg_4 (arg_8, arg_C only
    // known by use: its unk_10C and unk_134).
    virtual void vf_20C(struct type_D05C0 *arg_0, RwReal arg_4, RwV3d *arg_8, RwV3d *arg_C);
    // +0x210: raises the step arg_0's point by its height (type_3D5658's
    // sub_9D010; the base's sub_D05C0 raises it along the entity's up).
    virtual void vf_210(struct type_D05C0 *arg_0);
    // +0x214: moves the frame arg_4 by the step arg_0 over arg_8 (sub_D0760).
    virtual void vf_214(struct type_D05C0 *arg_0, RwFrame *arg_4, RwReal arg_8);
    // +0x218: empty in the base, three arguments only known by width (its
    // slot holds the same `ret 0Ch` body as vf_204, sub_73D80).
    virtual void vf_218(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // +0x21C: advances its animations by the frame's time (their movement
    // into unk_154, divided by the step arg_0 while unk_130 is set).
    virtual void vf_21C(RwReal arg_0);
    // +0x220: told it hit the entity arg_0 (sub_D2AD0); arg_4 only known by
    // width.
    virtual void vf_220(type_3D3548 *arg_0, RwInt32 arg_4);
    // +0x224: sets the entity's model from the object arg_0 (kind 3);
    // arg_4 and arg_8 (a pointer, or 0) are only known by width.
    // +0x224: returns true (type_3D5658's sub_9D080: mov al, 1).
    virtual bool vf_224(struct type_3DF8D8 *arg_0, RwInt32 arg_4, RwInt32 *arg_8);
    // +0x228: takes its render parts down (the atomics off their frames and
    // out of the world, the frame and clumps released); returns true.
    virtual bool vf_228();
    // +0x22C: registers the entity in the handle table (sub_D5BE0) and
    // resets its state; returns 1. +0x230 takes it down again.
    virtual RwInt32 vf_22C();
    virtual void vf_230();

    RwUInt8 unk_04[0xC];
    type_3D3548 *unk_10;    // the next entity in its list (dword_4B85F8;
                            // AIData::sub_24BA0)
    type_3D3548 *unk_14;    // the previous one
    type_3D3548 *unk_18;    // the next in dword_4B820C's list (sub_D62D0)
    type_3D3548 *unk_1C;    // the next dying one (dword_4B8204, sub_D5A60)
    RwInt32 unk_20;         // its pool in dword_4B83A0: dword_429264 when it
                            // registered (sub_CCB70)
    RwInt32 unk_24;         // its list (0x11 for none); type_3CE4B4::sub_33820
                            // skips list 14
    union
    {
        RwUInt32 unk_28;    // flags: AIData::sub_1FCC0 skips bit 9
        struct
        {
            RwUInt32 unk_28_0 : 1;
            RwUInt32 unk_28_1 : 1;  // the player's eye height follows its steps
                                    // (sub_96680)
            RwUInt32 unk_28_2 : 1;  // hit by explosions (sub_9A860 checks it
                                    // as a bitfield)
            RwUInt32 unk_28_3 : 1;  // bits 3, 5 and 7: type_3D5658's vf_210
            RwUInt32 unk_28_4 : 1;  // raises the step only with 3 and 5 set
            RwUInt32 unk_28_5 : 1;  // and 7 clear (the base's sub_D05C0
            RwUInt32 unk_28_6 : 1;  // tests the same)
            RwUInt32 unk_28_7 : 1;
            RwUInt32 unk_28_8 : 1;  // set by "SetNoFallThroughWorld" as a
                                    // bitfield
            RwUInt32 unk_28_9 : 1;  // type_3D32F8's vf_03C stops following
                                    // its spline while set
            RwUInt32 unk_28_10 : 1; // with unk_28_11, a dying entity waits
            RwUInt32 unk_28_11 : 1; // while its pool has room (sub_D5D20)
            RwUInt32 unk_28_12 : 1; // cleared when a fade starts (sub_D3910)
            RwUInt32 unk_28_13 : 1; // type_3D5658's vf_04C takes its atomic's
                                    // height from a bone while set
            RwUInt32 unk_28_14 : 1; // cleared on reset (sub_CCDF0)
            RwUInt32 unk_28_15 : 1; // vf_194 sets it
            RwUInt32 unk_28_16 : 1; // vf_1D8 sets it
            RwUInt32 unk_28_17 : 1;
            RwUInt32 unk_28_18 : 1; // set while it fades (sub_D3910, sub_D39F0)
            RwUInt32 unk_28_19 : 1;
            RwUInt32 unk_28_20 : 1; // collides with entities that have
                                    // unk_28_15 set (sub_946B0)
            RwUInt32 unk_28_21 : 1; // set while hidden
                                    // ("VehicleShowMountedWeapon")
            RwUInt32 unk_28_22 : 1;
            RwUInt32 unk_28_23 : 1; // vf_198 sets it
            RwUInt32 unk_28_24 : 1; // vf_19C sets it
            RwUInt32 unk_28_25 : 1; // set while a moving vehicle touches it
                                    // (sub_14B570)
        };
    };
#ifdef CODFH_SP
    // Clears flag 2 of unk_28 when arg_0 holds, else sets it: single
    // player's inline, named for its address (SP 0xD5B40, its out-of-line
    // copy; the projectile generators sub_11DF00 and sub_11E850 expand it
    // for a constant and call it for a random argument).
    void sp_sub_D5B40(RwInt32 arg_0)
    {
        if (arg_0)
            unk_28 &= ~2;
        else
            unk_28 |= 2;
    }
#endif
    union
    {
        RwUInt32 unk_2C;    // sub_12170 tests (unk_2C & 0x3FFFFF0) == 0x20000
        struct
        {
            RwUInt32 unk_2C_0 : 1;  // an ally, an enemy (type_3D32F8's
            RwUInt32 unk_2C_1 : 1;  // vf_064 checks them as bitfields)
            RwUInt32 unk_2C_2 : 1;
            RwUInt32 unk_2C_3 : 1;  // the remote player's performance
                                    // (sub_1BF5E0) reads it as a bitfield
            RwUInt32 unk_2C_4 : 1;  // a player (type_3D32F8's vf_23C checks
                                    // it as a bitfield)
            RwUInt32 unk_2C_5 : 1;  // a soldier (type_3DAFC8); "SetPickup"
                                    // checks it as a bitfield
            RwUInt32 unk_2C_6 : 1;
            RwUInt32 unk_2C_7 : 1;  // sub_9A800 checks it as a bitfield
            RwUInt32 unk_2C_8 : 1;  // an animated background entity
                                    // (type_545C0); "SetAnimatedBGEntityType"
                                    // checks it as a bitfield
            RwUInt32 unk_2C_9 : 5;
            RwUInt32 unk_2C_14 : 1; // a pick-up (type_3D94B8): the network
                                    // player's vf_060 checks it as a
                                    // bitfield
            RwUInt32 unk_2C_15 : 1;
            RwUInt32 unk_2C_16 : 1; // an entity with a destroyed version
                                    // (type_9BB60; "SwapToDestroyedVersion")
            RwUInt32 unk_2C_17 : 1;
            RwUInt32 unk_2C_18 : 1; // "VehicleGetHatchState" checks it as a
                                    // bitfield (shr, and, push)
            RwUInt32 unk_2C_19 : 2;
            RwUInt32 unk_2C_21 : 1; // sub_9A800 checks it as a bitfield
            RwUInt32 unk_2C_22 : 2;
            RwUInt32 unk_2C_24 : 1; // with 7, 18 and 25: a projectile's hit
            RwUInt32 unk_2C_25 : 1; // takes its effects (type_3DC7F8::vf_014)
        };
    };
    RwUInt32 unk_30;        // what the entity collides with
                            // ("SetCollideWithFlags", "ClearCollideWithFlags")
    RwUInt32 unk_34;        // a kind mask: sub_3DE00 requires it to share a
                            // bit (under 0x3FFFFF0) with the target's unk_2C
    RwInt32 unk_38;
    union
    {
        struct
        {
            RwUInt8 unk_3C[0x4];    // passed to sub_950C0 (type_3D32F8's
                                    // sub_74A30)
            RwReal unk_40;          // a height sub_61700 raises the start
                                    // point by (plus 33)
            RwUInt8 unk_44[0x4];
        };
        RwV3d unk_3C_v;     // as a vector: type_3D51C0's set-up clears it
    };
    RwReal unk_48;          // a height: AIData::sub_21A90 raises the eye point by it
    RwReal unk_4C;          // a radius: AIData::sub_29FC0 tests a sphere of it
                            // around the owner against its path
    union
    {
        RwInt32 unk_50;     // passed to sub_950C0 (type_3D51C0's set-up
                            // stores the bits of 80.0f in it; sub_74A30
                            // passes it on as an integer)
        RwReal unk_50_r;    // as a float: sub_D2740 sets it from the
                            // atomic's radius
    };
    RwInt32 unk_54;         // the last collision search that tested it
                            // (sub_9A860 compares the search's id)
    RwInt32 unk_58;         // a mode: AIData's sub_2C9B0 tests the line
                            // with vf_084 in mode 2, vf_07C in mode 1,
                            // vf_080 otherwise
    RwV3d unk_5C;           // its collision sphere's centre (sub_948A0)
    union
    {
        struct
        {
            RwReal unk_68;  // a point type_3D32F8's sub_74A30 compares its
            RwReal unk_6C;  // frame's position with
            RwReal unk_70;
        };
        RwV3d unk_68_v;
    };
    RwUInt8 unk_74[0x4];
    RwInt32 unk_78;
    RwReal unk_7C;          // the ground height the last search found (vf_044)
    RwReal unk_80;          // the scale ("SetEntityScale", sub_45280)
    RwUInt8 unk_84;
    RwUInt8 unk_85[0x3];
    union
    {
        RwUInt32 unk_88;
        struct
        {
            RwUInt32 unk_88_0 : 1;
            RwUInt32 unk_88_1 : 1;  // type_3D5658's vf_07C misses while clear
            RwUInt32 unk_88_2 : 1;  // type_3D32F8's sub_74A30 skips
                                    // sub_950C0 while at rest and set
            RwUInt32 unk_88_3 : 1;
            RwUInt32 unk_88_4 : 1;
            RwUInt32 unk_88_5 : 1;
            RwUInt32 unk_88_6 : 1;
            RwUInt32 unk_88_7 : 1;
            RwUInt32 unk_88_8 : 1;  // picked by a CCESS slot (sub_8AFF0 sets
                                    // 0x100; sub_8B840 tests it as a bitfield)
            RwUInt32 unk_88_9 : 1;
            RwUInt32 unk_88_10 : 1;
            RwUInt32 unk_88_11 : 1;
            RwUInt32 unk_88_12 : 1;
            RwUInt32 unk_88_13 : 1; // type_3D32F8's sub_75440 skips its
                                    // base vf_170 while it is set
            RwUInt32 unk_88_14 : 1; // set while registered (vf_22C; vf_230
                                    // clears it)
        };
    };
    RwUInt8 unk_8C[0x4];
    type_8E670 unk_90;      // its zone (sub_94060)
    RwUInt8 unk_B4[0xC];
    RwV3d unk_C0;
    RwV3d unk_CC;
    union
    {
        struct
        {
            RwReal unk_D8;  // scale of the frame's right row (AIData::sub_19F90)
            RwReal unk_DC;  // scale of the frame's up row (AIData::sub_19F90)
            RwReal unk_E0;  // scale of the frame's at row (AIData::sub_19F90)
        };
        RwV3d unk_D8_v;
    };
    union
    {
        struct
        {
            RwUInt8 unk_E4[0x4];    // passed to sub_19B650 by AIData::sub_2E580
            RwReal unk_E8;          // a turn rate AIData::sub_2E580 sets
            RwUInt8 unk_EC[0x4];
        };
        RwV3d unk_E4_v;
    };
    union
    {
        struct
        {
            RwReal unk_F0;  // a velocity: type_3D32F8's sub_74A30 is at rest
            RwReal unk_F4;  // while all three are small
            RwReal unk_F8;
        };
        RwV3d unk_F0_v;
    };
    RwV3d unk_FC;
    RwReal unk_108;         // flt_3D6F48 on reset
    RwV3d unk_10C;          // type_3D5658's vf_1C4 sets it on landing and
                            // hitting a wall
    RwV3d unk_118;
    RwV3d unk_124;
    RwInt32 unk_130;        // type_3D5658's vf_1C4 clears it on landing
    RwV3d unk_134;
    RwV3d unk_140;
    RwInt32 unk_14C;
    RwInt32 unk_150;
    RwV3d unk_154;
    RwV3d unk_160;
    RwV3d unk_16C;
    RwV3d unk_178;
    RwInt32 unk_184;
    RwInt32 unk_188;
    RwInt32 unk_18C;
    RwInt32 unk_190;
    RwInt32 unk_194;
    RwInt32 unk_198;
    RwInt32 unk_19C;
    RwInt32 unk_1A0;
    RwV3d unk_1A4;
    RwInt32 unk_1B0;
    RwInt32 unk_1B4;
    struct type_D4C80 *unk_1B8; // its jiggle (sub_D4950), or 0
    RwInt32 unk_1BC;        // the jiggle reaction ("SetJiggleReactionOnEntity")
    type_8A980 unk_1C0;     // its sound emitter ("EfuncPlaySound")
    RwInt32 unk_244;        // a rank: the Vision Scheduler's sub_41200 lets
                            // the higher of two entities with the same view
                            // range see the other first
    RwInt32 unk_248;
    RwInt32 unk_24C;
    type_1294D0 unk_250;    // an atomic (+0x258) whose bounding sphere
                            // follows the entity's size ("SetEntityScale",
                            // sub_45280)
    type_129940 unk_25C;    // the clump (+0x264) whose render parts the
                            // script sets ("SetRenderPartState" and the like)
    type_129940 unk_268;    // the clump (+0x270): Clump_ResolvePrimaryAtomic
                            // takes its first atomic, else unk_274's (+0x27C)
    type_1294D0 unk_274;
    RwInt32 unk_280;        // passed to sub_78AC0 (sub_48EE0)
    type_7C8D0 *unk_284;    // the primary animation (sub_7C8D0 gives its
                            // duration; "SetEntityScale" sets its unk_28)
    RwInt32 unk_288;
    type_7C8D0 *unk_28C;    // another animation, of the vf_008 and vf_024
                            // subclasses
    RwInt32 unk_290;        // the tag of the surface it stands on and its
    RwInt32 unk_294;        // own tag, indices into the index-sound table
                            // (dword_4E5E40; -1 for none, "EfuncPlayIndexSound")
    RwInt32 unk_298;
    RwInt32 unk_29C;        // the render priority, 0 to 2 (the script
                            // command "SetRenderPriority", sub_450E0)
    RwReal unk_2A0;         // a fade, 0 to 30 (vf_054's alpha)
    RwReal unk_2A4;         // the fade's time left, in frames (sub_D3910)
    RwReal unk_2A8;         // the fade's rate, per frame (negative fading in)
    union
    {
        RwReal unk_2AC;     // the fade level, 0 to 1
        RwInt32 unk_2AC_i;  // as "SetFadeLevel" passes it (sub_D39F0)
    };
    RwTexture *unk_2B0[16]; // the textures vf_054 took off its materials
    RpMaterial *unk_2F0[16]; // (sub_D3D10) and those materials, restored by
    RwInt32 unk_330;        // sub_D3EB0; how many
    RwInt32 unk_334;
    type_129B10 unk_338;    // its frame (+0x340), passed to RwFrameGetLTM by
                            // sub_CD550 and sub_19CA0
    type_144940 unk_344;    // the trigger the entity is in (+0x34C; a
                            // vehicle's, "SoldierEntity_GetMyVehiclesName")
    RwInt32 unk_350;
    RwInt32 unk_354;        // sub_126B0 requires 0x12; a performance
                            // selector for sub_47F90 when unk_358 is 0
    RwInt32 unk_358;        // sub_47F90's first performance selector (the
                            // star status, "SetStarStatus")
    type_D48D0 unk_35C[2];  // built as an array (eh vector constructor
                            // iterator, with pCtor and pDtor)
    RwInt32 unk_364[2];     // "AttachProp" sets [0] to 400, "DetachProp" to
                            // -1 (-1 on reset)
    RwInt32 unk_36C[2];     // "AttachPropEx" sets [0] to its second argument,
                            // or -1 (-1 on reset)
    RwInt32 unk_374;        // the physics callback's two arguments
    RwInt32 unk_378;        // (sub_D3700)
    void (*unk_37C)(type_3D3548 *); // the physics callback
    union
    {
        RwInt32 unk_380;    // its bump radius ("SetPlayerBumpRadius", which
                            // stores the script's value unconverted)
        RwReal unk_380_r;   // as vf_048 reads it
    };
    union
    {
        RwInt32 unk_384;    // id in the handle table dword_4B6A00, given by
                            // sub_D5BE0 when sub_CCB70 registers the entity
        type_3D3548_384 unk_384_h;
    };
    void *unk_388;          // its trigger's callback (dword_429238)
    RwInt32 unk_38C;
    type_3D3548_390 unk_390;
    type_3D3548_390 unk_39C;

    // The position row (+0x30) of the entity's frame's world matrix
    // (RwFrameGetLTM of its +0x340 frame), or 0 without a frame.
    // Sets its handle table id (unk_384).
    void sub_CD530(RwInt32 arg_0);
    // Advances its primary animation by arg_0 frames without moving it.
    void sub_CDF40(RwReal arg_0);
    // Steers its velocity (unk_D8) towards the point arg_8 from arg_4 over
    // the time arg_0, in its frame, and zeroes the components under 0.1.
    void sub_D01B0(RwReal arg_0, RwV3d *arg_4, RwV3d *arg_8);
    RwV3d *sub_CD550();
    // Turns node arg_4 of the pose key arg_0 about the axis *arg_C by
    // arg_10 degrees (RtQuatRotate; arg_8 an optional point, arg_14 whether
    // to replace); the vehicles' procedural tracks (sub_150350) call it.
    // Only the widths are known.
    void sub_17FC00(struct type_7CBD0 *arg_0, RwInt32 arg_4, RwV3d *arg_8, RwV3d *arg_C, RwReal arg_10,
                    RwInt32 arg_14);
    // Resets its state from its trigger's settings (vf_22C calls it).
    void sub_CCDF0();
    // The base set-up from the trigger arg_0 (type_3D51C0's vf_234 calls it
    // first).
    void sub_CCCD0(class type_712B0 *arg_0);
    // Its own performance set (type_3D2CD0::sub_6CF50 looks performances up
    // in it first); only the width is known.
    RwInt32 sub_CDC30();
    // The clump's first atomic (Clump_FindFirstAtomic), else unk_27C; the
    // database's name.
    RpAtomic *Clump_ResolvePrimaryAtomic();
    // Fades the entity out ("SetFadeOut", sub_455A0, passes its argument and
    // 1) and sets its fade level ("SetFadeLevel", sub_45610); only the widths
    // are known.
    void sub_D3910(RwReal arg_0, RwInt32 arg_4);
    void sub_D39F0(RwInt32 arg_0);
    // Advances the fade by arg_0 frames (unk_2A4 down to 0, unk_2AC by the
    // rate within 0 to 1).
    void sub_D3A20(RwReal arg_0);
    // Shakes the camera entity: the script command "CameraShake" (sub_44AD0)
    // passes its first argument, its second in frames and its third per
    // frame; only the widths are known.
    void sub_175E50(RwReal arg_0, RwReal arg_4, RwReal arg_8);
    // The at row (+0x20) of the same matrix, or 0 without a frame.
    RwV3d *sub_CD5A0();
    // The up row (+0x10) of the same matrix, or 0 without a frame.
    RwV3d *sub_CDB90();
    // The right row (+0x00) of the same matrix, or 0 without a frame.
    RwV3d *sub_CDBE0();
    // The matrix itself (RwFrameGetLTM of unk_340's frame), or 0 without a
    // frame; the multiplayer manager's pickup drop (sub_1ADB80) reads its
    // right row.
    RwMatrix *sub_1C05B0();

    // An inline accessor for unk_340. It has no address (every use is
    // expanded under /Ob1), so it has no database name; it is named for the
    // field it returns. Evidence for its shape: callers load +0x340 into a
    // compiler temporary in the slot just above `this` and copy that into
    // their own local (sub_19CA0, sub_1FDF0, sub_21A90), which is what an
    // inline function holding its result in a local expands to
    // (docs/toolchain.md).
    // An inline setter for element arg_0 of unk_364, with no address and so
    // no database name; named for its field. Evidence: "AttachProp" and
    // "DetachProp" index with a constant 0 that is still loaded (xor ecx,
    // ecx; shl ecx, 2), which is what a constant argument of an inline
    // function expands to (docs/toolchain.md).
    void set_unk_364(RwInt32 arg_0, RwInt32 arg_4)
    {
        unk_364[arg_0] = arg_4;
    }
    // Likewise for unk_36C ("AttachPropEx").
    void set_unk_36C(RwInt32 arg_0, RwInt32 arg_4)
    {
        unk_36C[arg_0] = arg_4;
    }
    // Inline accessors for unk_358 and unk_354, with no address and so no
    // database name; named for their fields. Evidence: sub_47F90 tests each
    // through a compiler temporary (an inline's result local) and then reads
    // the field directly for the assignment.
    // An inline setter for bit 0 of the flags of the unk_280 object
    // (sub_78AC0), with no address and so no database name; named for the
    // field. Evidence: sub_48EE0 holds the object in its deepest slot, after
    // its checks' (an inline function's local), and converts the flag twice
    // (setnz, then neg/sbb/neg: a bool parameter compared again).
    void set_unk_280_bit0(bool arg_0)
    {
        type_78AC0 *p = sub_78AC0(unk_280);

        if (p != 0)
            p->unk_12 = (p->unk_12 & ~1) | (arg_0 != 0);
    }
    // An inline accessor for unk_264, likewise nameless and named for its
    // field. Evidence: "SetRenderPartState", "GetRenderPartState" and
    // "SetRenderPartStateByName" pass it through a compiler temporary.
    RpClump *get_unk_264()
    {
        RpClump *r = unk_25C.unk_08;
        return r;
    }
    // Sets the velocity to *arg_0 ("SetVelocity", "ScaleVelocity").
    void sub_D04D0(RwV3d *arg_0);
    // An inline setter for unk_380, with no address and so no database name;
    // named for its field. Evidence: "SetPlayerBumpRadius" passes the script
    // argument through a local placed after the check's (the parameter).
    void set_unk_380(RwInt32 arg_0)
    {
        unk_380 = arg_0;
    }
    // The handle id as its struct, with no result local: an inline with no
    // address and so no database name, named for its field. Evidence:
    // type_D48D0::sub_D48D0 copies it through a return temporary, loading it
    // before the handle's pointer.
    type_3D3548_384 get_unk_384_h()
    {
        return unk_384_h;
    }
    // The trigger callback as its function type, with a result local: an
    // inline with no address and so no database name, named for its field.
    // Evidence: the entity manager's update (sub_D5E20) tests it and calls
    // it each through a temporary of its own.
    type_3D3548_388 get_unk_388()
    {
        type_3D3548_388 r = (type_3D3548_388)unk_388;
        return r;
    }
    // Sets the dead flag to arg_0 ("SetDeadFlag"); only the width is known.
    void sub_D29C0(RwInt32 arg_0);
    // Releases the clump arg_0's render parts (type_3D5658's vf_054) unless
    // dword_4B69EC is set; returns arg_0. arg_4 only known by width.
    RpClump *sub_D2920(RpClump *arg_0, RwInt32 arg_4);
    // Sends "TargetDestroyed" to each entity in the list from arg_0 whose
    // AI target is this one (sub_D29C0).
    void sub_D2A40(type_3D3548 *arg_0);
    // The bounding sphere of its clump's first atomic, or 0 (vf_110).
    const RwSphere *sub_D2EF0();
    // Its collision sizes from its atomic's bounding sphere (unk_48, unk_4C,
    // unk_50, unk_40), or the defaults without one (vf_224 calls it).
    void sub_D2740();
    // Set the custom object and animated object arg_0 (from 0;
    // "Custom_SetObject", "Custom_SetAnimatedObject"); only the widths are
    // known.
    void sub_9B430(RwInt32 arg_0);
    void sub_9B2C0(RwInt32 arg_0);
    // An inline accessor for unk_34C, likewise nameless and named for its
    // field. Evidence: "SoldierEntity_GetMyVehiclesName" copies it through a
    // compiler temporary into its own local.
    class type_712B0 *get_unk_34C()
    {
        class type_712B0 *r = (class type_712B0 *)unk_344.unk_08;
        return r;
    }
    RwInt32 get_unk_358()
    {
        RwInt32 r = unk_358;
        return r;
    }
    RwInt32 get_unk_354()
    {
        RwInt32 r = unk_354;
        return r;
    }
    // The primary animation, through a local of its own: an inline accessor
    // with no address and so no database name; named for its field.
    // Evidence: "AttachRingMountGunToGunner" (sub_5A6C0) copies unk_284
    // into a temporary before reading its hierarchy through get_unk_18.
    type_7C8D0 *get_unk_284()
    {
        type_7C8D0 *a = unk_284;
        return a;
    }
    RwFrame *get_unk_340()
    {
        RwFrame *f = unk_338.unk_08;
        return f;
    }
    // Decrements +0x38C. AIData::sub_20C00 passes its owner; the argument
    // is unused.
    void sub_D4170(type_3D3548 *arg_0);
    // AIData::sub_20BA0 passes its owner when it starts using this entity
    // (the counterpart of sub_D4170). Only the width of the argument is
    // known beyond that.
    void sub_D3FF0(type_3D3548 *arg_0);
    // While in use (unk_38C), follows its movement: once it has moved over
    // dword_4275C8 across from unk_39C, unk_390 takes the direction and
    // unk_39C the position (sub_D3FF0 starts them).
    void sub_D41A0();
    // Strikes the nearest opposing entity within 200 in front of it
    // (sub_D45F0 picks it) with a blow of vf_1F0's damage (vf_170 calls it).
    void sub_D42D0();
    // Warns that the clump arg_8 for the arg_0 object was not loaded, unless
    // arg_4 is given.
    void sub_D3FB0(const RwChar *arg_0, void *arg_4, struct type_3DF8D8_04 *arg_8);
    // A line test from arg_0 to arg_4 (11 arguments, retn 0x2C): nonzero on a
    // hit, with *arg_C the fraction along the line. arg_8 is an entity
    // (AIData::sub_1C4F0 passes its target; sub_21A90 passes 0). sub_21A90
    // passes 0, 1, 0 or 1, 0 or 1, 1, 0x20000, 0, 0 for the rest and
    // sub_1C4F0 0, 0x3440080, 1, 0, 0x20000, 0 and the owner's side
    // (unk_2C & 7); only their widths are known.
    RwInt32 sub_D2FC0(RwV3d *arg_0, RwV3d *arg_4, type_3D3548 *arg_8, RwReal *arg_C,
                      RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                      RwInt32 arg_20, RwInt32 arg_24, RwInt32 arg_28);
    // Two points AIData::sub_212E0 copies (into its unk_13EC and unk_13F8).
    RwV3d *sub_D42B0();
    // Installs the physics callback arg_0 with arg_4 and arg_8 (type_3D32F8's
    // vf_204); only the widths are known.
    void sub_D3700(void (*arg_0)(type_3D3548 *), RwInt32 arg_4, RwInt32 arg_8);
    // Takes damage from the entity arg_0 (arg_4 only known by width).
    void sub_D2AD0(type_3D3548 *arg_0, RwInt32 arg_4);
    RwV3d *sub_D4290();

    // sub_CC960 installs off_3D3548.
    type_3D3548();
    // Built in entity memory: its operator delete is out of line and empty
    // (folded into sub_19A750), which its deleting destructor calls.
    static void operator delete(void *arg_0);
};

// Its fields as far as known end at 0x3A8; the derived classes' own start
// there (unk_3A8).
typedef RwChar type_3D3548_size_check[sizeof(type_3D3548) == 0x3A8 ? 1 : -1];

// The entities' callbacks by a trigger's unk_44 (sub_CC8A0), -1 ending
// the table.
struct type_429238
{
    RwInt32 unk_00;
    void *unk_04;
};
extern type_429238 dword_429238[];
// The speed of the entities' material UV animations (1/240; sub_CF060).
extern RwReal flt_429248;
// The value an entity's unk_108 starts at.
extern const RwReal flt_3D6F48;
// Milliseconds per frame (1000 / 60), this unit's copy.
extern const RwReal flt_3D6F70;
// The entities made so far (each takes the next as its unk_244).
extern RwInt32 dword_4B69F8;
// What the next entity to register takes as its unk_20 (10 after the first).
extern RwInt32 dword_429264;
// The ground's height under arg_0 (a line test from 150 above to 4000
// below), or its own height when nothing is hit.
RwReal sub_CC8E0(RwV3d *arg_0);
// Fills the entity arg_0's trigger volume (arg_4, its unk_248) from its
// frame; arg_8 only known by width (0x20).
void sub_144C80(type_3D3548 *arg_0, RwInt32 *arg_4, RwInt32 arg_8);
// Intersects the line arg_8 with the ellipsoid at arg_0 whose inverse
// squared radii are arg_4, the distance into *arg_C; whether it hits.
RwInt32 sub_9A5F0(RwV3d *arg_0, RwV3d *arg_4, RpIntersection *arg_8, RwReal *arg_C);
// The database's names for this unit's RenderWare callbacks.
RpAtomic *Collision_AccumulateNearestAtomicLineIntersection(RpAtomic *arg_0, void *arg_4);
RpCollisionTriangle *Collision_RecordNearestCollisionTriangleHit(RpIntersection *arg_0,
                                                                 RpCollisionTriangle *arg_4,
                                                                 RwReal arg_8, void *arg_C);
RpAtomic *RenderWare_ReturnObjectUnchanged(RpAtomic *arg_0, void *arg_4);
RpAtomic *Clump_CopyExpandedBoundingSphere(RpAtomic *arg_0, void *arg_4);
// What sub_D2FC0 hands its atomic callback sub_D31B0.
struct type_D31B0
{
    struct type_3D3548 *unk_00; // the entity testing (never hit)
    struct type_3D3548 *unk_04; // an entity to pass over, with what is
                                // attached to it
    RwReal unk_08;              // the nearest hit so far (1: none)
    RwUInt32 unk_0C;            // kinds to test (any of the target's unk_2C)
    RwUInt32 unk_10;            // bits the target's unk_2C must all have
    RwInt32 unk_14;             // the search's id (sub_8F940)
    RwUInt8 unk_18;             // whether anything was hit
};
// A new collision search id (types/vec4.h declares it too).
RwInt32 sub_8F940();
RpAtomic *sub_D31B0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10);
// The frame under arg_0 that holds objects: arg_0 itself when two or more
// of its children do, else that one child, else the first found deeper;
// into *(RwFrame **)arg_4 when given (sub_D37D0 counts the children).
RwFrame *sub_D3740(RwFrame *arg_0, void *arg_4);
RwFrame *sub_D37D0(RwFrame *arg_0, void *arg_4);
// What sub_D37D0 counts into: the last child with objects and how many.
struct type_D37D0
{
    RwFrame *unk_00;
    RwInt32 unk_04;
};
// Sets *arg_4 when the frame has an object (RwFrameForAllObjects' callback).
RpAtomic *sub_16E580(RpAtomic *arg_0, void *arg_4);
// The bounding sphere sub_D2EF0 finds (sub_D2EB0 stores the first atomic's).
extern const RwSphere *dword_4B6978;
RpAtomic *sub_D2EB0(RpAtomic *arg_0, void *arg_4);
// vf_054's material and atomic callbacks: sub_D3AD0, sub_D3C30 set a
// material's alpha or whole colour from arg_4 (an RwRGBA), saving the old
// components in the byte arrays (counting with dword_4B69E0), sub_D3BA0
// restores the alpha; sub_D3B30 saves an atomic's geometry flags (counting
// with dword_4B697C) and turns on material colours, sub_D3BE0 restores them.
RpMaterial *sub_D3AD0(RpMaterial *arg_0, void *arg_4);
RpAtomic *sub_D3B30(RpAtomic *arg_0, void *arg_4);
RpMaterial *sub_D3BA0(RpMaterial *arg_0, void *arg_4);
RpAtomic *sub_D3BE0(RpAtomic *arg_0, void *arg_4);
RpMaterial *sub_D3C30(RpMaterial *arg_0, void *arg_4);
RpMaterial *sub_D3E10(RpMaterial *arg_0, void *arg_4);
// sub_D42D0's atomic callback: keeps the nearest entity of another side (or
// a vf_024 one) whose sphere is within 35 degrees plus its own angular size
// of the searcher's facing.
RpAtomic *sub_D45F0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10);
// The sound of a blow landing (sub_D42D0).
extern struct type_3DF8D8_04 dword_4AF030;
extern RwUInt32 dword_4B6898[];
extern RwUInt8 byte_4B6918[];
extern RwUInt8 byte_4B6948[];
extern RwUInt8 byte_4B6980[];
extern RwUInt8 byte_4B69B0[];
// vf_054's atomic callbacks, each given the colour arg_4 (an RwRGBA).
RpAtomic *sub_D3D10(RpAtomic *arg_0, void *arg_4);
RpAtomic *sub_D3EB0(RpAtomic *arg_0, void *arg_4);
// Globals vf_054 clears before each pass over its clump.
extern RwInt32 dword_4B697C;
extern RwInt32 dword_4B69E0;
// Set while render parts stay (sub_D2920 skips sub_128E50).
extern RwInt32 dword_4B69EC;
void sub_128E50(RpClump *arg_0, RwInt32 arg_4);
// The atomic arg_0's entity is given it (sub_122820, with the clump's first
// atomic when it has a clump) and then its vf_054 (with dword_4E5C74).
RpAtomic *sub_D2B70(RpAtomic *arg_0);
void sub_122820(RpAtomic *arg_0, type_3D3548 *arg_4, RwInt32 arg_8);
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4E5C74;
#else
extern RwInt32 dword_4E5C74;
#endif
// The ratio of an atomic's bounding radius to an entity's size (sub_D2740).
extern RwReal flt_42924C;
// The scale Clump_CopyExpandedBoundingSphere applies (with 1 added first).
extern RwReal flt_429250;
// Registers the entity arg_0 in the handle table (its unk_384).
RwInt32 sub_D5BE0(type_3D3548 *arg_0);
// A line test from arg_0 to arg_4 against the collision worlds (flags
// arg_10), then with arg_14 against their atomics; the nearest hit's point
// and normal into *arg_8 and *arg_C (with no arg_8, the first hit ends it);
// whether it hit. Without arg_18, a hit on a surface facing away from
// arg_0 does not count (src/recovered/unit_0FD730.cpp).
RwInt32 sub_FCAE0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C, RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18);

// Whether the entities arg_0 and arg_4 are of different sides: both present,
// with different nonzero kinds (unk_2C & 7), neither of them 4. It has no
// address (every use is expanded under /Ob1: AIData::sub_21C90, and
// AIData::sub_279B0's loop) and so no database name; it is named for the
// field it compares. Evidence for its shape: callers copy an argument that is
// an expression into a temporary and assign 0 directly on the null path,
// which is what an inline function with an early return expands to.
#ifdef CODFH_SP // static in single player: where VC keeps it out of line, it is a static copy
                // with its arguments in registers (SP 0x210B0, eax/ecx; called from SP 0x9E3E0, 0xE5100, 0xE7F10)
static
#endif
inline RwInt32 cmp_unk_2C(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    RwInt32 k0;
    RwInt32 k4;

    if (arg_0 == 0 || arg_4 == 0)
        return 0;
    k0 = arg_0->unk_2C & 7;
    k4 = arg_4->unk_2C & 7;
    return k0 != k4 && k0 != 0 && k4 != 0 && k0 != 4 && k4 != 4;
}

// Whether the entities arg_0 and arg_4 are of different nonzero sides
// (unk_2C & 7). It has no address (its uses, in type_3CE4F0::sub_34C60 and
// sub_3DE00, are expanded under /Ob1) and so no database name; it is named
// for the field it compares. Evidence for its shape: both compute the &&
// chain into a temporary before testing it, and compare the sides with xor.
inline RwInt32 xor_unk_2C(type_3D3548 *arg_0, type_3D3548 *arg_4)
{
    return ((arg_0->unk_2C & 7) ^ (arg_4->unk_2C & 7)) != 0 && (arg_0->unk_2C & 7) != 0
        && (arg_4->unk_2C & 7) != 0;
}

// The entity arg_0's side (unk_2C & 7), through a direct-return inline with
// no address. Evidence: the projectiles' step (type_3DC7F8::vf_014) loads its
// own side first but compares the entity's first, which is how the inline's
// expansion on the left of == is evaluated.
inline RwInt32 get_unk_2C_side(type_3D3548 *arg_0)
{
    return arg_0->unk_2C & 7;
}

#endif
