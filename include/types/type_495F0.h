/*
 * type_495F0: a grenade's weapon definition (a keyed object of kind 5, as
 * type_3DF8D8::vf_008 gives it), named after "DropGrenadeAtLocationXYZ"
 * (sub_495F0), the first command known to use it; only what that command
 * reads is known.
 *
 * type_439A48: a projectile's settings as sub_15F2C0 is given them (0x84
 * bytes), the element of dword_439A48, a ring of eight that
 * "DropGrenadeAtLocationXYZ" takes the next of (dword_439940) and fills.
 */
#ifndef TYPE_495F0_H
#define TYPE_495F0_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"

struct RwMatrixTag;
typedef struct RwMatrixTag RwMatrix;

// A reference to another keyed object: its key at +4 (sub_18F800 looks it
// up with sub_198800).
struct type_18F800
{
    RwUInt8 unk_00[0x4];
    type_3DF8D8_04 unk_04;
};

struct type_495F0 : type_3DF8D8
{
    type_18F800 unk_20;         // its model (the weapon copies' vf_008)
    RwUInt8 unk_2C[0xC];
    type_18F800 unk_38;         // the object its projectile spawns

    // The value (sub_190A10) of the keyed object arg_0 names; `this` is not
    // read.
    RwInt32 sub_18F800(type_18F800 *arg_0);
};

// A projectile's particle effect as its settings give it (two, at +0x08
// and +0x20): whether it has one, the effect's id, count and duration, a
// value for the effect's +0x2C and the node it follows
// (type_3DC7F8::vf_000).
struct type_439A48_08
{
    RwInt32 unk_00;
    RwUInt32 unk_04;
    RwInt32 unk_08;
    RwReal unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
};

struct type_439A48
{
    RwUInt16 unk_00;            // the table sub_15F2C0 picks (2 for these)
    RwUInt8 unk_02[0x2];
    RwReal unk_04;              // arg 5 of "DropGrenadeAtLocationXYZ"
    type_439A48_08 unk_08[2];
    RwInt32 unk_38;             // the weapon's sub_18F800 value
    RwInt32 unk_3C;
    RwReal unk_40;
    RwReal unk_44;
    RwReal unk_48;
    RwReal unk_4C;
    RwReal unk_50;              // arg 6, x60 (per second to per frame)
    RwReal unk_54;
    RwReal unk_58;
    RwReal unk_5C;
    RwReal unk_60;
    RwReal unk_64;
    RwReal unk_68;
    RwReal unk_6C;
    RwReal unk_70;
    RwReal unk_74;
    RwReal unk_78;
    RwReal unk_7C;
    RwReal unk_80;

    // Its constructor is type_67260's code (sub_67260): the grenade ring's
    // initializer calls it for each 0x84-byte element, which begins with a
    // type_67260's fields (type_10F710 likewise keeps two of them 0x84
    // apart); aliased to it.
    type_439A48();
};

// The longer settings some projectiles read (kinds 7 and 8: their
// start, type_3DC738::vf_000 and type_3DC6D8::vf_000); the grenade drop's
// ring keeps only the 0x84 bytes above.
struct type_439A48_84 : type_439A48
{
    RwInt32 unk_84;
    RwReal unk_88;
    RwReal unk_8C;
    RwInt32 unk_90;
    RwReal unk_94;              // its time (x60)
    RwReal unk_98;
    RwReal unk_9C;              // kind 8: the distance its sound changes at
    RwReal unk_A0;
    RwV3d unk_A4;
};

// The object a projectile definition's projectile spawns (the value
// sub_18F800 finds for its reference at +0x38): an inline with no address
// and so no database name, named for what it returns. Evidence: the
// grenade handler (sub_1AE8F0) copies sub_198800's result into an argument
// slot before it calls through it.
inline RwInt32 projectile_object(type_3DF8D8 *arg_0)
{
    return ((type_495F0 *)arg_0)->sub_18F800(&((type_495F0 *)arg_0)->unk_38);
}

extern RwInt32 dword_439940;
extern type_439A48 dword_439A48[8];

// sub_15F2C0: spawns the effect arg_0 (with the flags arg_4) at *arg_8 with
// the velocity *arg_C and the settings *arg_14, through the table
// arg_14->unk_00 selects (sub_15F590); for effect flag 0x200 with no arg_18
// it passes the player's +0x420. Only the widths are known.
RwInt32 sub_15F2C0(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwV3d *arg_C, RwInt32 arg_10,
                   type_439A48 *arg_14, RwInt32 arg_18);

#endif
