/*
 * The atomic collision properties plugin's data, copied from RenderWare
 * Studio's game framework (framework/core/attributehandler/
 * csystemcommands.cpp, where it is private to that file). Only
 * csystemcommands.cpp includes this: the data is in an anonymous namespace.
 * The image registers it as MAKECHUNKID(rwVENDORID_CRITERIONRM, 0xFE)
 * (0x7FE) with four bytes per atomic.
 */
#ifndef RWS_ATOMICCOLLISIONPLUGIN_H
#define RWS_ATOMICCOLLISIONPLUGIN_H

#include "rw/ostypes.h"

namespace RWS
{
   namespace RpAtomicCollisionProperties
   {
      namespace
      {
         struct PluginData
         {
            RwUInt32 m_isSolid:1;
         };
      }

      const RwUInt32 PluginID = 0xFE;
   }
}

#endif
