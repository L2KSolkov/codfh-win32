/*
 * type_154C0_1444: the three 20-byte records AIData holds at +0x1444, named
 * after that first container and offset (no constructor or method of their
 * own is known). AIData::sub_22780 records a node there and sub_22690 looks
 * one up by its node and position.
 *
 *   +0x00 unk_00  a path node: sub_22780 compares it with AIData's unk_F60
 *                 and unk_F54, sub_22690 with its arg_0
 *   +0x04 unk_04  a point sub_22690 measures against its arg_4
 *   +0x10 unk_10  stored by sub_22780; only its width is known
 */
#ifndef TYPE_154C0_1444_H
#define TYPE_154C0_1444_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_F8350.h"

struct type_154C0_1444
{
    type_F8350 *unk_00;
    RwV3d unk_04;
    RwInt32 unk_10;
};
typedef RwChar type_154C0_1444_size_check[sizeof(type_154C0_1444) == 0x14 ? 1 : -1];

#endif
