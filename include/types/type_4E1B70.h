/*
 * type_4E1B70: a mounted weapon's settings (0xFC bytes), seven of them at
 * dword_4E1B70; sub_166990 returns one by index (0 past the seventh).
 * CMountedWeaponBehavior's HandleAttributes (sub_A4B00) fills one from its
 * commands; only the fields it writes are known.
 */
#ifndef TYPE_4E1B70_H
#define TYPE_4E1B70_H

#include "rw/ostypes.h"
#include "types/type_3DF8D8.h"

// A mounted weapon's animation record: only its keys at +0x2C to +0x34
// are known (its fire, sub_169380, plays unk_2C, or unk_30 on alternate
// shots of kind 4).
struct type_4E1B70_C8
{
    RwUInt8 unk_00[0x2C];
    RwInt32 unk_2C;
    RwInt32 unk_30;
    RwInt32 unk_34;             // its animation's key (sub_77B70)
};

struct type_4E1B70
{
    type_3DF8D8_04 unk_00;      // its model's name
    type_3DF8D8_04 unk_08;      // another name vf_058 accepts
    RwReal unk_10;              // command 1: the tangent of half its angle
                                // (in degrees)
    union
    {
        RwInt32 unk_14;         // command 3
        RwReal unk_14_r;        // its projectiles' speed (sub_169380)
    };
    RwReal unk_18;              // command 4, in seconds (times 60)
    RwInt32 unk_1C;             // command 5
    RwInt32 unk_20;             // commands 7, 9 and 10
    union
    {
        RwInt32 unk_24;
        RwReal unk_24_r;        // its recoil's spread (sub_169380)
    };
    union
    {
        RwInt32 unk_28;
        RwReal unk_28_r;
    };
    RwV3d unk_2C;               // command 2
    union
    {
        RwInt32 unk_38;         // commands 11, 12 and 8
        RwReal unk_38_r;        // its camera shake when fired (sub_169380;
    };                          // unk_3C when unk_488 is set)
    union
    {
        RwInt32 unk_3C;
        RwReal unk_3C_r;
    };
    RwInt32 unk_40;
    type_3DF8D8_04 unk_44;      // commands 13 and 14
    type_3DF8D8_04 unk_4C;
    RwInt32 unk_54;             // commands 15 and 16
    RwInt32 unk_58;
    type_3DF8D8_04 unk_5C;      // commands 17 and 18
    type_3DF8D8_04 unk_64;
    type_3DF8D8_04 unk_6C;      // a name (its constructor clears it)
    RwV3d unk_74;               // commands 19 and 20
    RwV3d unk_80;
    RwV3d unk_8C;               // commands 22 and 23
    RwV3d unk_98;
    RwInt32 unk_A4;             // command 21
    RwReal unk_A8;              // command 24, in seconds (times 60)
    union
    {
        RwInt32 unk_AC;         // command 25
        RwReal unk_AC_r;        // the zoomed field of view's divisor
    };
    RwReal unk_B0;              // commands 26 and 27, halved
    RwReal unk_B4;
    union
    {
        RwInt32 unk_B8;         // commands 28, 29, 6 and 30
        RwReal unk_B8_r;        // the player's look spring (unzoomed)
    };
    union
    {
        RwInt32 unk_BC;
        RwReal unk_BC_r;        // likewise, zoomed
    };
    union
    {
        RwInt32 unk_C0;
        RwReal unk_C0_r;        // its aim's random spread (in degrees)
    };
    union
    {
        RwInt32 unk_C4;
        RwReal unk_C4_r;        // the weapon's height and radius
    };
    struct type_4E1B70_C8 *unk_C8;  // its animation (kind 4)
    RwInt32 unk_CC;             // commands 31 to 41
    RwInt32 unk_D0;
    RwInt32 unk_D4;
    RwInt32 unk_D8;
    RwInt32 unk_DC;
    RwInt32 unk_E0;
    RwInt32 unk_E4;
    union
    {
        RwInt32 unk_E8;
        RwReal unk_E8_r;        // the NPC gunner's burst length bounds
    };                          // (either order; sub_16B5C0, sub_16B620)
    union
    {
        RwInt32 unk_EC;
        RwReal unk_EC_r;
    };
    union
    {
        RwInt32 unk_F0;
        RwReal unk_F0_r;        // and its pause's (sub_16B680, sub_16B6E0)
    };
    union
    {
        RwInt32 unk_F4;
        RwReal unk_F4_r;
    };
    RwInt32 unk_F8;             // cleared by CMountedWeaponSelector's
                                // sub_CA9C0
};
typedef RwChar type_4E1B70_size_check[sizeof(type_4E1B70) == 0xFC ? 1 : -1];

// Mounted weapon settings arg_0 (0 when arg_0 is 7 or more).
type_4E1B70 *sub_166990(RwInt32 arg_0);

struct type_3D3548;
struct type_712B0;

// Spawns the mounted weapon of the trigger arg_0 (MountedWeaponTrigger's
// child, its vf_020).
type_3D3548 *sub_1669B0(type_712B0 *arg_0);

#endif
