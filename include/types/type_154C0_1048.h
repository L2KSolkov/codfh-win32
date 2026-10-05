/*
 * type_154C0_1048: a node search request for sub_F8970, 0x60 bytes. AIData
 * holds two, at +0x1048 and +0x1114, and AIData::sub_28470 builds one on the
 * stack; named after that first container and offset. Its inline
 * constructor zeroes +0x20, +0x4C, +0x1C and +0x18 in that order (expanded
 * in sub_154C0 for both members and in sub_28470). sub_F8970 clears the
 * result fields +0x34 to +0x58 itself. The size is 0x60, not the 0x64 the
 * gap to AIData's next members allows: sub_F8970 touches nothing past +0x5C,
 * and VC7.1 rounds a local struct up to 8 bytes, so a 0x64-byte request
 * leaves a hole in sub_28470's and sub_27EB0's frames that the image lacks.
 *
 *   +0x00 unk_00  the entity searching (AIData's owner)
 *   +0x04 unk_04  the point to search around
 *   +0x10 unk_10  the search radius (2500.0 from sub_27CC0, 1000.0 from
 *                 sub_28470)
 *   +0x18 unk_18  a filter: sub_F7E80 picks one by kind; sub_F8970 falls back
 *                 to sub_F93D0 when it is 0. It is called with four arguments,
 *                 the request last; the others are not established.
 *   +0x1C unk_1C  an option (0 or 1)
 *   +0x20 unk_20  the result array
 *   +0x24 unk_24  its capacity (25 for AIData's, 32 for sub_28470's)
 *   +0x34 unk_34  the best node found
 *   +0x38 unk_38  the best node's index, +0x3C its squared distance
 *   +0x4C unk_4C  the number of results
 *   +0x50 unk_50  a node AIData::sub_28F30 falls back to (it clears it, and
 *                 sets unk_54 to -1, before each search)
 */
#ifndef TYPE_154C0_1048_H
#define TYPE_154C0_1048_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_154C0_F80.h"
#include "types/type_F8350.h"

struct type_3D3548;

struct type_154C0_1048;

// The node filters sub_F7E80 hands out (sub_F93D0 and its kin): whether the
// node arg_0 (index arg_4) at the squared distance arg_C passes the search
// arg_8.
typedef RwInt32 (*type_F93D0)(type_F8350 *arg_0, RwInt32 arg_4, type_154C0_1048 *arg_8, RwReal arg_C);

struct type_154C0_1048
{
    type_154C0_1048()
    {
        unk_20 = 0;
        unk_4C = 0;
        unk_1C = 0;
        unk_18 = 0;
    }

    // The gaps are dword arrays, not byte arrays: a byte array would make /GS
    // treat sub_28470's local request as a string buffer and add a cookie
    // the image does not have.
    type_3D3548 *unk_00;
    RwV3d unk_04;
    RwReal unk_10;
    RwUInt32 unk_14;
    type_F93D0 unk_18;
    RwInt32 unk_1C;
    type_154C0_F80 *unk_20;
    RwInt32 unk_24;
    RwV3d unk_28;           // a facing the node filters test against
    type_F8350 *unk_34;
    RwInt32 unk_38;         // the result AIData::sub_244E0 settled on (a node index)
    RwReal unk_3C;          // and its score (sub_242B0)
    RwInt32 unk_40;         // the best node's grid column and row and cell
    RwInt32 unk_44;         // list
    RwInt32 unk_48;
    RwInt32 unk_4C;
    type_F8350 *unk_50;
    RwInt32 unk_54;
    RwReal unk_58;          // 1e18 at each search's start
    RwReal unk_5C;          // the radius squared
};
typedef RwChar type_154C0_1048_size_check[sizeof(type_154C0_1048) == 0x60 ? 1 : -1];

#endif
