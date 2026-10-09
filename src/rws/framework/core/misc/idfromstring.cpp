// RenderWare Studio's string ids (the game framework's
// framework/core/misc/idfromstring.cpp).

#include "rw/ostypes.h"
#include "rws/idfromstring.h"

// match: ?GenerateUIntIdFromString@RWS@@YAIPBD@Z @ 0x0012F1B0
// sp-match: ?GenerateUIntIdFromString@RWS@@YAIPBD@Z @ 0x000E0FB0
RwUInt32 RWS::GenerateUIntIdFromString(const RwChar *cptr)
   {
      if (!cptr) return (0);

      RwChar *ptr = const_cast<RwChar*>(cptr);
      RwUInt32 id = 0;

      while (*ptr != 0)
      {
         id = (id<<1) ^ (static_cast<RwUInt32>(*ptr));
         ptr ++;
      };

      return (id);
   }
