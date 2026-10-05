/*
 * type_154C0_5BC: a path, 0x178 bytes. AIData holds five of them, one after
 * another, at +0x5BC, +0x734, +0x8AC, +0xA24 and +0xB9C (0x178 apart, ending
 * where unk_D14 starts). sub_154C0 builds each inline (only the +0x50 handle
 * is constructed) and destroys them with pDtor, which is folded with other
 * types' empty destructors, so the type is named after its first container
 * and offset. sub_31240 plans one (it sets +0x00 to -1, clears +0x30, +0x31
 * and +0x33 and fills fields up to +0x8C); sub_2B740 follows one; the
 * AIData path requests (sub_29540, sub_29780, sub_29870) fill +0x14 to +0x60.
 *
 *   +0x00 unk_00  set to -1 by sub_154C0
 *   +0x04 unk_04  a count: sub_2B740 returns 1 when it is not positive,
 *                 AIData::sub_192D0 requires it positive
 *   +0x08 unk_08  a direction: sub_2B740 passes it to sub_2AC00 as the
 *                 heading at the point unk_38
 *   +0x14 unk_14  the start point of a request (the owner's position)
 *   +0x20 unk_20  the goal: sub_2B740 subtracts the owner's position from it
 *   +0x2C unk_2C  a search radius (1500.0 from sub_31240 and sub_29780)
 *   +0x31 unk_31  a signed byte AIData::sub_192D0 tests
 *   +0x32 unk_32  a signed byte: AIData::sub_1DB60 checks the path's last
 *                 leg against the owner's facing when it is set
 *   +0x33 unk_33  a signed byte sub_2B740 tests
 *   +0x34 unk_34  a distance sub_2B740 compares with
 *   +0x38 unk_38  a point sub_2B740 copies to unk_44, then overwrites
 *   +0x50 unk_50  handle to an entity (sub_2B740; AIData's +0xA74 is the
 *                 fourth path's)
 *   +0x54..+0x60  request parameters (sub_29540, sub_29780, sub_29870)
 *   +0x64 unk_64  a type_169D0 describing the node list unk_B0 (its unk_2C,
 *                 path +0x90, is the number of nodes)
 *   +0x90 (unk_64.unk_2C) the number of nodes in unk_B0; AIData::sub_19ED0 (fourth
 *                 path) and sub_19F30 (second path) require it nonzero
 *   +0xB0 unk_B0  the path's node indices into the node graph's unk_2C
 *                 (AIData::sub_228A0 walks them from the last)
 */
#ifndef TYPE_154C0_5BC_H
#define TYPE_154C0_5BC_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "types/type_D48D0.h"
#include "types/type_169D0.h"

struct type_154C0_5BC
{
    RwInt32 unk_00;
    RwInt32 unk_04;
    RwV3d unk_08;
    RwV3d unk_14;
    RwV3d unk_20;
    RwReal unk_2C;
    RwInt8 unk_30;
    RwInt8 unk_31;
    RwInt8 unk_32;
    RwInt8 unk_33;
    RwReal unk_34;
    RwV3d unk_38;
    RwV3d unk_44;
    type_D48D0 unk_50;
    RwInt32 unk_54;
    RwInt32 unk_58;
    RwInt32 unk_5C;
    RwInt32 unk_60;
    type_169D0 unk_64;
    RwInt16 unk_B0[0x64];
};
typedef RwChar type_154C0_5BC_size_check[sizeof(type_154C0_5BC) == 0x178 ? 1 : -1];

#endif
