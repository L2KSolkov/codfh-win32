/*
 * type_154C0_80: the 32-byte records AIData holds at +0x80 (32 of them,
 * built by sub_154C0 with the compiler's `eh vector constructor iterator').
 * Its constructor, pCtor (0x22C60, zeroes +0x0), is folded with other types'
 * identical constructors, so the type is named after its container and
 * offset. sub_16ED0 claims and resets a record; sub_18E90 tests one.
 *
 *   +0x00 unk_00  handle to the entity the record is about
 *   +0x04 unk_04  flags: sub_16ED0 clears bits 0 and 1; sub_18E90 tests bit 0,
 *                 sub_140D0 bit 1. Bit 0 is set while the entity is seen and
 *                 bit 1 while it could be (the Vision Scheduler's sub_425A0
 *                 and sub_426E0, which stores bit 1 as a bitfield, hence the
 *                 union)
 *   +0x08 unk_08  set to 1 by sub_16ED0
 *   +0x0C unk_0C  a float: set to 0x7CF0BDC2 (1e37) by sub_16ED0, compared
 *                 with fcomp by sub_150F0
 *   +0x10 unk_10  a float: set to 0 by sub_16ED0, compared with 2700.0 by
 *                 sub_140D0
 *   +0x14 unk_14  a point: sub_16ED0 zeroes it, sub_18F80 subtracts it from
 *                 the entity's position with RwV3dSub
 */
#ifndef TYPE_154C0_80_H
#define TYPE_154C0_80_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_D48D0.h"

struct type_154C0_80
{
    type_D48D0 unk_00;
    union
    {
        RwUInt32 unk_04;
        struct
        {
            RwUInt32 unk_04_0 : 1;
            RwUInt32 unk_04_1 : 1;
        };
    };
    RwInt32 unk_08;
    RwReal unk_0C;
    RwReal unk_10;
    RwV3d unk_14;

    // Declared, and defined inline in AIData's file just before sub_22C80:
    // VC7.1 emits it where the definition comes (pCtor, 0x22C60), after the
    // functions that need it, not after AIData's constructor (PLAN M7).
    type_154C0_80();
};
typedef RwChar type_154C0_80_size_check[sizeof(type_154C0_80) == 0x20 ? 1 : -1];

#endif
