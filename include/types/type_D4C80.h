/*
 * type_D4C80: an entity's jiggle (type_3D3548::unk_1B8), 0x60 bytes, named
 * after the function that makes it (sub_D4C80: RWSMalloc, zeroed, then
 * filled). It holds the frame's matrix as it was, a random axis, a size and
 * a height; sub_D4D00 steps it on the frame each update and returns 0 once
 * it has died down (the entity then frees it).
 */
#ifndef TYPE_D4C80_H
#define TYPE_D4C80_H

#include <stdlib.h>

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"

struct type_3D3548;

struct type_D4C80
{
    RwMatrix unk_00;            // the frame's matrix when it started
    RwV3d unk_40;               // its rotation (angles for sub_141080), which
                                // unk_4C turns each step
    RwV3d unk_4C;               // a random axis
    RwReal unk_58;              // its size (the strength doubled, times 150)
    RwReal unk_5C;              // the frame's height when it started

    // Steps the jiggle on arg_4 from arg_0 (the entity passes its frame's
    // matrix as both); 0 once it is over.
    RwInt32 sub_D4D00(RwMatrix *arg_0, RwMatrix *arg_4);
};
typedef RwChar type_D4C80_size_check[sizeof(type_D4C80) == 0x60 ? 1 : -1];

// A jiggle of the matrix arg_0 about the axis arg_4 with the strength arg_8
// (arg_C the height).
type_D4C80 *sub_D4C80(RwMatrix *arg_0, RwV3d *arg_4, RwReal arg_8, RwReal arg_C);
// A jiggle with a random axis and a strength of arg_4 scaled by 0.6 to 1.4,
// at least arg_8.
type_D4C80 *sub_D4B70(RwMatrix *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C);
// Whether the entity arg_0 can jiggle: its reaction is set (unk_1BC), its
// kind is not one of seven, and its frame stands upright (cos above 0.85).
RwInt32 sub_D4A60(struct type_3D3548 *arg_0);
// Starts the entity arg_0 jiggling if it can and is not already.
void sub_D4950(struct type_3D3548 *arg_0);
// Steps the entity arg_0's jiggle, freeing it when it is over.
void sub_D49E0(struct type_3D3548 *arg_0);
// The jiggle's tuning (.data): flt_429254 damps its turning each step (1.0),
// flt_429258 scales it (sub_D4B70) and bounds the random turn on a bounce,
// flt_42925C over the bounce time gives the new turning (at most 3), and
// flt_429260 keeps that much of the speed on a bounce (sub_D4D00).
extern RwReal flt_429254;
extern RwReal flt_429258;
extern RwReal flt_42925C;
extern RwReal flt_429260;

// A random float from lo to hi in steps of a thousandth. A macro, not an
// inline: the image folds (hi - lo) when both are constants (sub_D4950's
// 0.19999999, sub_D4B70's 0.79999995), which an inline's arguments are not.
// lo comes first: a computed one is spilled across the rand() call and
// added last (sub_D4B70's three axis components).
#define RAND_RANGE(lo, hi) ((lo) + (rand() % 1000) * ((hi) - (lo)) * 0.001f)

#endif
