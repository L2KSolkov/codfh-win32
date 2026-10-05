/*
 * Time in frames (the game runs at 60 a second).
 */
#ifndef GAME_FRAMES_H
#define GAME_FRAMES_H

#include "rw/ostypes.h"

// Seconds as frames (at 60 a second): an inline with no address and so no
// database name, named for what it does. Evidence: the charge effect
// multiplies its constant 3 by 60 at run time, which a substituted
// argument does and a folded constant would not; so do the debris'
// particle durations (0.1, 0.5), the shells' generator (3) and others,
// each with the literals among its function's own in the image.
inline RwReal seconds_to_frames(RwReal arg_0)
{
    return arg_0 * 60.0f;
}

#endif
