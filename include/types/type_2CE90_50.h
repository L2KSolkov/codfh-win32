/*
 * type_2CE90_50: the data AIData::sub_2CE90 hands to its atomic intersection
 * callback sub_2C9B0, kept on its stack at ebp-0x50 (its first instance), so
 * named after that function and offset. 0x30 bytes. AIData::sub_29FC0 sets
 * one up the same way (and in the same order) but uses only its unk_00, as
 * the flag its line test sets.
 *
 *   +0x04 unk_04  the owner (whose position the line starts at)
 *   +0x08 unk_08  the entity the path follows (unk_8AC's unk_50), skipped
 *   +0x0C unk_0C  the nearest blocking entity found
 *   +0x10 unk_10  the entity unk_14 was measured for
 *   +0x14 unk_14  its squared distance from the owner
 *   +0x18 unk_18  the atomic of the entity found
 *   +0x1C unk_1C  the distance along the line of the entity found (1e37)
 *   +0x20 unk_20  whether the unk_10 entity lies ahead
 *   +0x24 unk_24  the direction of the line
 *   +0x2C unk_2C  the owner's flag 25: only entities that also block
 */
#ifndef TYPE_2CE90_50_H
#define TYPE_2CE90_50_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/rpcollis.h"

struct type_3D3548;

struct type_2CE90_50
{
    RwInt32 unk_00;
    type_3D3548 *unk_04;
    type_3D3548 *unk_08;
    type_3D3548 *unk_0C;
    type_3D3548 *unk_10;
    RwReal unk_14;
    RpAtomic *unk_18;
    RwReal unk_1C;
    RwInt32 unk_20;
    RwV3d *unk_24;
    RwInt32 unk_28;
    RwInt32 unk_2C;
};
typedef RwChar type_2CE90_50_size_check[sizeof(type_2CE90_50) == 0x30 ? 1 : -1];

#endif
