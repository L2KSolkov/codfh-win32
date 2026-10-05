/*
 * frand: a random float in [0, 1). It has no address (every use is expanded
 * under /Ob1) and so no database name. Evidence for its shape: sub_33820
 * computes the scaled RpRandom() into a temporary of its own above `this`
 * before it loads and subtracts the range's bounds, which it does at run time
 * (sub_17AB0 scales into a local of its own the same way; so does
 * type_3D32F8's debris callback sub_75EC0).
 */
#ifndef GAME_FRAND_H
#define GAME_FRAND_H

#include "rw/ostypes.h"
#include "rw/rprandom.h"
#include <stdlib.h>

inline RwReal frand()
{
    RwReal r = RpRandom() * (1.0f / 2147483648.0f);
    return r;
}

// A random float between arg_0 and arg_4; named for what it does. Evidence:
// the triggered particles (sub_F5920, sub_F54E0) copy both bounds into
// temporaries (the upper first) and scale RpRandom() into one of their own.
inline RwReal frand_range(RwReal arg_0, RwReal arg_4)
{
    RwReal r = RpRandom() * (1.0f / 2147483648.0f);
    return (arg_4 - arg_0) * r + arg_0;
}

// The value arg_8 (0 to 1) of the way from arg_0 to arg_4; named for what it
// does. Evidence: sub_12B20 and sub_17AB0 scale RpRandom() into a local, then
// load both bounds from their literals and subtract them at run time: an
// inline's constant arguments are not folded under /Od, and the image has
// the bounds' literals in the reverse order of these references, among the
// function's own.
inline RwReal lerp(RwReal arg_0, RwReal arg_4, RwReal arg_8)
{
    return (arg_4 - arg_0) * arg_8 + arg_0;
}

// A random float in [0, 1] from the C library's rand(); it has no address
// and so no database name, and is named for what it does. Evidence: the
// mounted weapon's fire (type_3DA558::vf_018) stores the converted rand()
// into a local of its own, stores it again after dividing by 32767 and goes
// on from the FPU stack, as an inline that divides its local in place does.
inline RwReal crand()
{
    RwReal r = (RwReal)rand();
    r /= 32767.0f;
    return r;
}

#endif
