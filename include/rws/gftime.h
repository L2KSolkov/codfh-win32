/*
 * RWS::Time, after RenderWare Studio's game framework
 * (framework/toolkits/time/gftime.h): the time in milliseconds (the
 * database's sub_132B30), which the game times its effects, loads and AI
 * with.
 */
#ifndef RWS_GFTIME_H
#define RWS_GFTIME_H

#include "rw/ostypes.h"

namespace RWS
{
   namespace Time
   {
      RwUInt32 GetTime();
   }
}

#endif
