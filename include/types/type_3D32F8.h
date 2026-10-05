/*
 * type_3D32F8: the animated background entity (vtable off_3D32F8; the
 * string "AnimatedBGEntity" is used by its set-up sub_740B0), 0x490 bytes,
 * built in entity memory by sub_73710 for its trigger.
 */
#ifndef TYPE_3D32F8_H
#define TYPE_3D32F8_H

#include "rw/ostypes.h"
#include "types/type_3D3548.h"
#include "types/type_44350.h"
#include "types/SplinePath.h"
#include "types/type_3DF8D8.h"
#include "types/type_D48D0.h"

// What a bullet's hit's unk_04 points at, named after it: a direction at
// +0x10 (type_3DAFC8::vf_064 normalises it when it is longer than 0.01).
struct type_75600_04
{
    RwUInt8 unk_00[0x10];
    RwV3d unk_10;
};

// A bullet's hit (type_3D3548::vf_064): the shooter and the damage.
struct type_75600
{
    union
    {
        RwInt32 unk_00;
        struct
        {
            RwInt16 unk_00_w;   // 0 and 1 for a blow (type_3D3548's
            RwUInt16 unk_02_w;  // sub_D42D0); the player's vf_064 picks
                                // its hurt sound by it
        };
    };
    union
    {
        RwInt32 unk_04;         // passed to sub_D2AD0
        struct type_75600_04 *unk_04_p; // the soldier's vf_064 reads a
                                        // direction through it
    };
    RwInt32 unk_08;             // 0x200 plus the side for a blow
    type_3D3548 *unk_0C;        // the shooter
    RwUInt32 unk_10;            // the shooter's kind (unk_2C)
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwV3d *unk_20;              // where it hit (a vehicle's vf_064 turns it
                                // into its own axes)
    RwInt32 unk_24;             // -1: type_3D5658's vf_064 ignores the hit
    RwReal unk_28;              // the damage
    RwReal unk_2C;
};

// What an explosion's unk_08 points at: its kind (vf_058: kinds 3, 4 and 6
// reach only as far as the radius) and where it is (type_3D3548's vf_070).
struct type_758F0_08
{
    virtual void vf_000();
    virtual void vf_004();
    virtual void vf_008();
    virtual void vf_00C();
    virtual void vf_010();
    virtual void vf_014();
    virtual void vf_018();
    virtual void vf_01C();
    virtual void vf_020();
    virtual void vf_024();
    virtual void vf_028();
    virtual void vf_02C();
    virtual void vf_030();
    virtual void vf_034();
    virtual void vf_038();
    virtual void vf_03C();
    virtual void vf_040();
    virtual void vf_044();
    virtual void vf_048();
    virtual void vf_04C();
    virtual void vf_050();
    virtual void vf_054();
    virtual RwInt32 vf_058();
    virtual void vf_05C();
    virtual void vf_060();
    // Its kind of weapon (a vehicle's vf_068 scales the damage of kinds 20
    // to 22 from a player's kind-5 weapon).
    virtual RwUInt32 vf_064();

    RwV3d unk_04;
};

// An explosion's hit (type_3D3548::vf_068): its instigator, where it is and
// its damage.
struct type_758F0
{
    RwInt32 unk_00;
    type_D48D0 unk_04;          // the instigator
    union
    {
        RwInt32 unk_08;         // passed to sub_D2AD0
        type_758F0_08 *unk_08_p;
    };
    RwMatrix *unk_0C;           // where it is
    RwReal unk_10;              // its radius (type_3D3548's vf_070)
    RwReal unk_14;              // passed on to the script (as a float:
                                // type_3D5658's vf_06C hands it 1.0)
    RwUInt8 unk_18[0x14];
    RwReal unk_2C;              // the damage
    struct type_114F90 *unk_30; // its settings (the player's vf_068 takes
                                // its zones, unk_50)
};

// What "HitByExplosion" hands the script: where the explosion was, its
// unk_14, and whether it was behind the entity.
struct type_758F0_14
{
    RwReal unk_00;
    RwReal unk_04;
    RwReal unk_08;
    RwReal unk_0C;
    RwInt32 unk_10;
};

// What the collision notifications hand the script: the other entity's
// vf_09C and how its at and right rows line up with the entity's.
struct type_75770_0C
{
    RwInt32 unk_00;
    RwReal unk_04;
    RwReal unk_08;
};

// The debris state of a breaking entity (type_3D32F8::unk_458; sub_D63A0
// hands one out, sub_761F0 resets it): whether it is live, its
// direction and spin axis, and how it tumbles.
struct type_76290
{
    RwUInt8 unk_00;             // live (cleared on shutdown)
    RwUInt8 unk_01;             // type_3D32F8's vf_244
    RwInt16 unk_02;
    RwV3d unk_04;               // its direction away from what broke it
    RwV3d unk_10;               // the axis it spins about
    RwReal unk_1C;              // how far it has tipped (degrees)
    RwReal unk_20;              // its tip rate (at most 8)
    RwReal unk_24;              // the tip rate's growth, by the breaker's size
    RwReal unk_28;              // its spin about its up row
    RwInt32 unk_2C;             // the bounces left

    // Inline: the debris pool's initializer (0x30B1A0) expands it.
    type_76290()
    {
        unk_00 = 0;
        unk_02 = -1;
        unk_01 = 0;
        sub_761F0();
    }
    void sub_761F0();
};

// An entity's bounding box at +0x574, as type_3D32F8's vf_204 reads it from
// its breaker's vf_010.
struct type_76290_574
{
    RwUInt8 unk_00[0x574];
    RwBBox unk_574;
};

// A particle effect (sub_F1230 hands one out): started with an id, a count
// and a duration (sub_F0880), then attached to node arg_4 of an entity
// (sub_F0A10); the rest only known by width.
struct type_F1230
{
    RwUInt8 unk_00[0x2C];
    RwInt32 unk_2C;             // a projectile's effect's value
                                // (type_439A48_08::unk_10)

    // An inline setter for unk_2C, with no address and so no database name;
    // named for its field. Evidence: type_3DC7F8::vf_000 copies the value
    // into an argument temporary before storing it.
    void set_unk_2C(RwInt32 arg_0)
    {
        unk_2C = arg_0;
    }
    void sub_F0880(RwUInt32 arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
    void sub_F0A10(type_3D3548 *arg_0, RwInt32 arg_4, RwInt32 arg_8);
};
struct type_4B9E90;
type_4B9E90 *sub_F1230();
// sub_D63A0: a debris state from the pool arg_0 (arg_4 only known by width).
type_76290 *sub_D63A0(void *arg_0, RwInt32 arg_4);
extern type_76290 unk_4B8220[8];
// The debris callback sub_D3700 installs for a breaking type_3D32F8.
void sub_75EC0(type_3D3548 *arg_0);

struct type_3D32F8 : type_3D3548
{
    // Overrides (out of line in unit_073710).
    // +0x03C: follows its spline at unk_440 per second (unk_444 its end),
    // telling its script "IHaveArrived" at an end.
    virtual void vf_03C(RwReal arg_0);
    // +0x04C: the base's update, then its mounted weapon (unk_454) placed
    // at its tag (sub_751A0).
    virtual void vf_04C(RwReal arg_0);
    // Hit by a bullet, an explosion; collided with.
    virtual RwInt32 vf_064(type_75600 *arg_0);
    virtual RwInt32 vf_068(type_758F0 *arg_0);
    virtual RwInt32 vf_06C(type_3D3548 *arg_0);
    virtual RwInt32 vf_058(type_3DF8D8_04 *arg_0);
    virtual type_6D380 *vf_090();
    virtual type_3D2E7C *vf_098();
    virtual RwInt32 vf_0E4(RwInt32 arg_0);
    virtual RwInt32 vf_0E8();
    virtual void vf_0EC(RwInt32 arg_0, RwInt32 arg_4);
    virtual void vf_0F8(RwReal arg_0);
    virtual void vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C);
    // Inline accessors (out of line at 0x73DD0 to 0x74000): its script and
    // AI handles, its trigger values, its spline speed and spline, and a
    // count unk_430 with its limit unk_434.
    virtual void vf_094(RwUInt32 arg_0);
    virtual RwInt32 vf_09C();
    virtual void vf_0A0(RwUInt32 arg_0);
    virtual RwUInt8 *vf_0E0();
    virtual void vf_124(RwReal arg_0);
    virtual RwReal vf_128();
    virtual struct SplinePath *vf_0F4();
    virtual RwInt32 vf_174();
    virtual void vf_178(RwInt32 arg_0);
    virtual void vf_180(RwInt32 arg_0);
    virtual RwReal vf_17C();
    // +0x230: shuts the entity down (its destructor calls it too).
    virtual void vf_230();
    // Its destructor: takes it down, then the base's (not expanded). Out of
    // line at sub_74050, with its scalar deleting destructor at sub_74020.
    ~type_3D32F8()
    {
        vf_230();
    }
    // Its own slots: +0x234 (inline, 0x73EB0: its own entity, unk_454), and
    // +0x238 and +0x23C, which mount the player arg_0 on its weapon and take
    // the player off it.
    virtual type_3D3548 *vf_234();
    virtual void vf_238(struct type_10F710 *arg_0);
    virtual void vf_23C();
    // +0x240 to +0x24C (inline, 0x73ED0 to 0x73F50): unk_43C, unk_458's
    // unk_01, and unk_458 itself.
    virtual void vf_240(bool arg_0);
    virtual RwInt32 vf_244();
    virtual void vf_248(type_76290 *arg_0);
    virtual type_76290 *vf_24C();
    // +0x204: breaks apart when arg_0 is 1 (the breaker's AI object is
    // arg_8), else stops its physics callback.
    virtual void vf_204(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8);
    // +0x208: plays an animation (type_3D3548's own, sub_CDC70), first
    // settling unk_45C's wait.
    virtual RwInt32 vf_208(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C,
                           RwReal arg_10, RwReal arg_14, RwInt32 arg_18);

    // unk_3D4 through a local of its own: an inline with no address, named
    // for its field. Evidence: type_3CE278::sub_32750 compares it with 1
    // through a slot of its own.
    RwInt32 get_unk_3D4()
    {
        RwInt32 r = unk_3D4;
        return r;
    }

    RwUInt8 unk_3A8[0x8];
    RwInt32 *unk_3B0;           // its sounds' state (sub_83850)
    RwUInt8 unk_3B4[0x20];
    RwInt32 unk_3D4;            // -1 at first
    RwUInt32 unk_3D8;           // its AI object's handle (vf_098)
    RwUInt32 unk_3DC;           // its script object's handle (vf_090)
    RwReal unk_3E0;             // how far along its spline (vf_0F8)
    RwUInt8 unk_3E4[0xC];
    RwMatrix unk_3F0;           // where on its spline
    RwInt32 unk_430;
    RwInt32 unk_434;
    RwInt32 unk_438;
    RwInt32 unk_43C;            // it turns to face along its spline while set
    RwReal unk_440;             // its speed along its spline
    RwReal unk_444;             // where along it to stop
    struct SplinePath *unk_448;    // its spline
    RwInt16 unk_44C[0x3];       // from its trigger's unk_104 (vf_0EC sets them)
    RwUInt8 unk_452[0x2];
    type_D48D0 unk_454;         // its own entity
    type_76290 *unk_458;        // its debris state (vf_248, vf_24C)
    RwInt32 unk_45C;            // sub_76860's flag
    RwInt16 unk_460;            // the animation it waits on (-1 for none)
    RwUInt8 unk_462[0x2];
    RwInt32 unk_464[5];
    RwReal unk_478;             // the five-way blend's target angle and
    RwReal unk_47C;             // its current one (sub_76960), with their
    RwReal unk_480;             // magnitudes
    RwReal unk_484;
    RwInt32 unk_488;            // set while it is up (vf_230)
    RwUInt8 unk_48C[0x4];

    type_3D32F8(type_712B0 *arg_0)
    {
        sub_740B0(arg_0);
    }
    // An inline accessor with no address and so no database name, named for
    // its field. Evidence: the flag part's step (sub_1B2670) passes the value
    // through a slot of its own.
    void set_unk_480(RwReal arg_0)
    {
        unk_480 = arg_0;
    }
    // Updates its physics unless it is at rest; the argument is unused.
    void sub_74A30(RwReal arg_0);
    // Takes its model from its trigger's unk_C8 (unless that is its unk_C0).
    void sub_75530();
    // Takes the player off the entity when it rides it (posture 12).
    void sub_75CB0();
    // Sets the flag unk_45C (the script's; only its width is known), and
    // with it the animation to wait on.
    void sub_76860(bool arg_0);
    // Steps the five-way blend towards unk_478/unk_480 (by unk_428BE0.unk_04),
    // starting its five animations after unk_460 when none run, and blends
    // them by the weights (sub_76E70); stops when the first has ended.
    void sub_76960();
    // Blends the five animations arg_0 towards the layered weights arg_4
    // (the last on top) by arg_8.
    void sub_76E70(RwInt32 *arg_0, RwReal *arg_4, RwReal arg_8);
    // Sets the entity up from its trigger; 0 when its model is missing.
    RwInt32 sub_740B0(type_712B0 *arg_0);
    // The placement pair sub_73710 builds it in entity memory with, as
    // type_3D2CD0's (sub_6CCF0 and the empty sub_19A750).
    static void *operator new(RwUInt32 arg_0, void *arg_4);
    static void operator delete(void *arg_0, void *arg_4);
    // Its plain operator delete, for its deleting destructor (sub_74020):
    // empty and out of line like the base's (the placement one above hides
    // the base's), folded into sub_19A750.
    static void operator delete(void *arg_0);
    // vf_01C, as the image's vtable has it (a trivial body, folded into
    // sub_6FCD0 with every other copy).
    virtual type_3DA6C0 *vf_01C()
    {
        return (type_3DA6C0 *)this;
    }
    // vf_060, as the image's vtable has it: a collision passed on to vf_06C
    // (the same body as type_3DBC78's, folded into sub_14FA40).
    virtual RwInt32 vf_060(type_3D3548 *arg_0)
    {
        return vf_06C(arg_0);
    }
};
typedef RwChar type_3D32F8_size_check[sizeof(type_3D32F8) == 0x490 ? 1 : -1];

// sub_78870 releases the animation object sub_78830 made (type_3D3548's
// unk_280); sub_8B840 takes the entity out of the CCESS pool (types/ccess.h).
void sub_78870(RwInt32 arg_0);
// The state sub_74A30 hands the physics step sub_950C0, one 48-byte local
// (its members are passed one by one; a frame of separate locals would leave
// the 12-byte vectors a hole each).
struct type_74A30
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwV3d unk_08;               // the frame's position
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwInt32 unk_1C;
    RwV3d unk_20;               // the entity's radius, height and radius
    RwInt32 unk_2C;
};

// sub_950C0: the entity's physics step (unit_08AB60, its definition's
// prototype).
struct type_3DAFC8_1DDC;
void sub_950C0(type_3D3548 *arg_0, RwFrame *arg_4, RwV3d *arg_8, RwReal arg_C, RwInt32 *arg_10,
               RwV3d *arg_14, RwReal *arg_18, RwInt32 *arg_1C, RwInt32 *arg_20, RwInt32 *arg_24,
               type_3DAFC8_1DDC *arg_28);
void sub_8B840(type_3D3548 *arg_0);
// sub_D56D0: entity memory of arg_0 bytes (arg_4 and arg_8 only known by
// width), 0 when there is none; sub_D5A60 ends the entity arg_0.
void *sub_D56D0(RwInt32 arg_0, bool arg_4, RwInt32 arg_8);
void sub_D5A60(type_3D3548 *arg_0, RwInt32 arg_4);

// Builds the animated background entity for the trigger arg_0, or warns
// that there is no entity memory for it (unit_073710).
type_3D32F8 *sub_73710(type_712B0 *arg_0);

#endif
