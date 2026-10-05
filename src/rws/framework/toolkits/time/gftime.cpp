// RenderWare Studio's time toolkit (the game framework's
// framework/toolkits/time/gftime.cpp): the Xbox's time, in milliseconds. The
// game's reads GetTickCount (the Studio sources' Xbox branch reads
// timeGetTime); its other functions are not in the image.

#include "rw/ostypes.h"
#include "xbox/xapi.h"
#include "rws/gftime.h"

// match: ?GetTime@Time@RWS@@YAIXZ @ 0x00132B30
RwUInt32 RWS::Time::GetTime()
      {
         RwUInt32 result = (RwUInt32) GetTickCount();

         return (result);
      }
