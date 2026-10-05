/*
 * type_3DAFC8_1DDC: the object type_3DAFC8 embeds at +0x1DDC, which its
 * vf_1C8 (sub_1352C0) returns; type_3D3548's own vf_1C8 (sub_1E4CB0) returns
 * 0. Nothing constructs it separately, so it is named after its container
 * and offset, as are its two record types.
 *
 *   +0x030 unk_30   the owner's at and right rows (with unk_3C), set by
 *                   AIData::sub_30B90, which copies the whole object
 *   +0x054 unk_54   eight 0x50-byte records; AIData::sub_2E580 reads the
 *                   first four (a flag, a distance and a direction), and
 *                   AIData::sub_21C90 tests the fifth's flag and copies the
 *                   other three
 *   +0x2D4 unk_2D4  four 0x24-byte records pairing a flag with an entity id
 *                   (AIData::sub_2E580)
 */
#ifndef TYPE_3DAFC8_1DDC_H
#define TYPE_3DAFC8_1DDC_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_D48D0.h"

struct type_3DAFC8_1DDC_54
{
    RwInt32 unk_00;         // set when the record holds a direction
    RwReal unk_04;          // the squared distance it was taken at
    RwV3d unk_08;           // AIData::sub_30B90 hands sub_992B0 these four
    RwV3d unk_14;           // the direction                 points and a
    RwV3d unk_20;           // triangle of the last three (type_30B90_48)
    RwV3d unk_2C;
    RwV3d unk_38;
    RwV3d unk_44;
};
typedef RwChar type_3DAFC8_1DDC_54_size_check[sizeof(type_3DAFC8_1DDC_54) == 0x50 ? 1 : -1];

struct type_3DAFC8_1DDC_2D4
{
    RwInt32 unk_00;         // set when unk_20 is to be followed
    RwReal unk_04;          // reset to 1e37 by AIData::sub_30B90
    RwV3d unk_08;           // two points AIData::sub_30B90 hands sub_9A2D0
    RwV3d unk_14;           // with the unk_20 entity
    RwInt32 unk_20;         // an entity id, assigned to a handle (type_D48D0)
};
typedef RwChar type_3DAFC8_1DDC_2D4_size_check[sizeof(type_3DAFC8_1DDC_2D4) == 0x24 ? 1 : -1];

struct type_3DAFC8_1DDC
{
    RwV3d unk_00;           // the search's radii (sub_948A0)
    RwV3d unk_0C;           // their inverse squares
    RwV3d unk_18;           // the wider radii (sub_985B0)
    RwV3d unk_24;           // the wider inverse squares (sub_97790)
    RwV3d unk_30;           // AIData::sub_30B90 copies the owner's facing (at)
    RwV3d unk_3C;           // and right rows here
    RwV3d unk_48;           // the search sphere's centre (sub_948A0)
    type_3DAFC8_1DDC_54 unk_54[8];
    type_3DAFC8_1DDC_2D4 unk_2D4[4];
};

// type_30B90_48: the triangle AIData::sub_30B90 hands sub_992B0, a local at
// ebp-0x48 there (its first instance), so named after that function and
// offset: a point and three vertex pointers, with four dwords between that
// start zeroed.
struct type_30B90_48
{
    RwV3d unk_00;
    RwInt32 unk_0C;
    RwInt32 unk_10;
    RwInt32 unk_14;
    RwInt32 unk_18;
    RwV3d *unk_1C;
    RwV3d *unk_20;
    RwV3d *unk_24;
};
typedef RwChar type_30B90_48_size_check[sizeof(type_30B90_48) == 0x28 ? 1 : -1];

#endif
