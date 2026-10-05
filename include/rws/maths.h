/*
 * RWS::DegAngDiff, copied from RenderWare Studio's game framework
 * (framework/toolkits/math/maths.h): the difference a1 - a0 between two
 * angles in degrees, in -180 to 180 (the AI's turns, sub_2E580, and the
 * trackers of unit_0441B0).
 */
#ifndef RWS_MATHS_H
#define RWS_MATHS_H

#include "rw/ostypes.h"

namespace RWS
{
   RwReal DegAngDiff(RwReal a0, RwReal a1);
}

#endif
