/*
 * Vector inlines of the game's own, with no addresses and so no database
 * names; each is named for what it does.
 */
#ifndef GAME_VECUTIL_H
#define GAME_VECUTIL_H

#include "rw/ostypes.h"
#include "rw/batypes.h"

// Zeroes a vector. Evidence: sub_6CDA0 clears its two vectors, and
// type_3D3548's reset (sub_CCDF0) its eighteen, each through a temporary
// holding its address (the inline's argument).
inline void zero_v3d(RwV3d *arg_0)
{
    arg_0->x = 0.0f;
    arg_0->y = 0.0f;
    arg_0->z = 0.0f;
}

// Sets a point's three components. Evidence: AIData::sub_17BF0 copies the
// point's address into an argument temporary, and arguments that are not
// constants into temporaries of their own, evaluated from the last to the
// first, before storing x, y and z in order.
inline void set_xyz(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    arg_0->x = arg_4;
    arg_0->y = arg_8;
    arg_0->z = arg_C;
}

// Whether two vectors are equal. Evidence: type_3D3548's vf_070 keeps the
// three comparisons' result in a byte-tested temporary of its own (an
// inline bool's result).
inline bool equal_v3d(const RwV3d *arg_0, const RwV3d *arg_4)
{
    return arg_0->x == arg_4->x && arg_0->y == arg_4->y && arg_0->z == arg_4->z;
}

#endif
