/*
 * The RpAtomicToEventHandler plugin's data, copied from RenderWare Studio's
 * game framework (framework/core/eventhandler/ceventhandler.cpp, where it is
 * private to that file). Only ceventhandler.cpp includes this: the data is
 * in an anonymous namespace. The image registers it as
 * MAKECHUNKID(rwVENDORID_CRITERIONRM, 0xFF) (0x7FF) with four bytes per
 * atomic.
 */
#ifndef RWS_ATOMICEVENTHANDLERPLUGIN_H
#define RWS_ATOMICEVENTHANDLERPLUGIN_H

#include "rw/ostypes.h"
#include "rws/ceventhandler.h"

namespace RWS
{
   namespace RpAtomicToEventHandler
   {
      namespace
      {
         // The Studio sources' PluginData (renamed here: the collision
         // properties plugin's data has that name too, and the name is in no
         // decorated name).
         struct EventHandlerPluginData
         {
            RWS::CEventHandler* m_pEventHandler;
         };
      }

      const RwUInt32 PluginID = 0xFF;
   }
}

#endif
