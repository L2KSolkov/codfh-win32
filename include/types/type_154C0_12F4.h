/*
 * type_154C0_12F4: the 24-byte structs AIData holds at +0x12F4, +0x130C,
 * +0x1324, +0x133C and +0x1354. sub_154C0 zeroes each one's handle inline and
 * destroys them with pDtor, which is folded with other types' empty
 * destructors, so the type is named after its first container and offset.
 *
 *   +0x00 unk_00  an index into type_3DBC78's unk_263C records (sub_155340)
 *   +0x08 unk_08  handle to the type_3DBC78 whose record it indexes
 */
#ifndef TYPE_154C0_12F4_H
#define TYPE_154C0_12F4_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_D48D0.h"

struct type_154C0_12F4
{
    RwInt32 unk_00;
    RwInt32 unk_04;         // compared and copied with unk_00 (sub_23E50, sub_23DF0)
    type_D48D0 unk_08;
    RwV3d unk_0C;           // a point: sub_23EA0 subtracts two records' points;
                            // sub_23D90 zeroes it through a pointer local
};
typedef RwChar type_154C0_12F4_size_check[sizeof(type_154C0_12F4) == 0x18 ? 1 : -1];

#endif
