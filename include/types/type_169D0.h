/*
 * type_169D0: an object embedded in AIData's members (built at +0x64 of the
 * members at +0x5BC, +0x734, +0x8AC, ...), anchored at its constructor
 * sub_169D0 (no vtable). The constructor zeroes every dword from +0x0 to
 * +0x48, +0x30 twice, and sets +0x28 to -1. Its destructor is inline and
 * empty: with it the path has two destructible members, and AIData's
 * destructor then keeps each path's address in a `this` temporary (a record
 * with one, type_154C0_12F4, gets none). In a path
 * (type_154C0_5BC) it describes the node list: AIData::sub_29FC0 points
 * unk_04 and unk_08 at the path's start and goal and unk_24 at its node
 * array (of unk_20 = 100 entries), and unk_2C is the node count.
 *
 * It is an A* search request (astarpathfinder.cpp, sub_F62F0): the
 * entity's handle (unk_00), the cost,
 * heuristic and filter functions (unk_10 to unk_18; sub_F6BB0, sub_F6BF0
 * and sub_F6C10 hand them out by index), the kind of search (unk_1C), the
 * path buffer and its size (unk_24, unk_20), the result (unk_28: 1 found,
 * -1 not) and length (unk_2C), the start and goal node indices (unk_38,
 * unk_40), the goal node (unk_3C) and whether to log the outcome (unk_44,
 * unk_48).
 */
#ifndef TYPE_169D0_H
#define TYPE_169D0_H

#include "rw/ostypes.h"
#include "rw/batypes.h"

struct type_169D0;
struct type_F6400;
struct type_F8350;

// An A* search's step cost from the record arg_0 to the node arg_4 (index
// arg_8; the goal's arg_C) for the request arg_10, with a second cost out
// in *arg_14.
typedef RwReal (*type_169D0_cost)(type_F6400 *arg_0, type_F8350 *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                                  type_169D0 *arg_10, RwReal *arg_14);
// Its estimate from the node arg_0 (index arg_4) to the goal node arg_8
// (index arg_C).
typedef RwReal (*type_169D0_heuristic)(type_F8350 *arg_0, RwInt32 arg_4, type_F8350 *arg_8, RwInt32 arg_C);
// Whether the node arg_0 may be crossed.
typedef RwInt32 (*type_169D0_filter)(type_F8350 *arg_0, type_169D0 *arg_4);

struct type_169D0
{
    RwInt32 unk_00;             // the entity's handle (a type_D48D0's id)
    RwV3d *unk_04;
    RwV3d *unk_08;
    RwReal unk_0C;              // the path's search radius (AIData::sub_31240 copies it)
    type_169D0_cost unk_10;
    type_169D0_heuristic unk_14;
    type_169D0_filter unk_18;
    RwInt32 unk_1C;
    RwInt32 unk_20;
    RwInt16 *unk_24;
    RwInt32 unk_28;
    RwInt32 unk_2C;
    RwInt32 unk_30;
    RwInt32 unk_34;
    RwInt32 unk_38;
    type_F8350 *unk_3C;
    RwInt32 unk_40;
    RwInt32 unk_44;
    RwInt32 unk_48;

    type_169D0();
    ~type_169D0()
    {
    }
};
typedef RwChar type_169D0_size_check[sizeof(type_169D0) == 0x4C ? 1 : -1];

#endif
