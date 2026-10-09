// RenderWare Studio's maths toolkit (the game framework's
// framework/toolkits/math/maths.cpp): the one function the game keeps.

#include "rw/ostypes.h"
#include "rws/maths.h"

// match: ?DegAngDiff@RWS@@YAMMM@Z @ 0x001326C0
// sp-match: ?DegAngDiff@RWS@@YAMMM@Z @ 0x000E30D0
RwReal RWS::DegAngDiff(RwReal a0, RwReal a1)
   {
      RwReal a2;

      a2 = a1 - a0;

      while(a2 < 0.0f) a2 += 360.0f;
      while(a2 >= 360.0f) a2 -= 360.0f;

      if(a2 >= 180.0f) a2 -= 360.0f;

      return (a2);
   }
