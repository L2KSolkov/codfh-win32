/*
 * RWS::LightHelper, after RenderWare Studio's game framework
 * (framework/toolkits/world/helpers/lighthelper.h): the system commands of a
 * light (the database's sub_1330B0).
 */
#ifndef RWS_LIGHTHELPER_H
#define RWS_LIGHTHELPER_H

#include "rw/rplight.h"
#include "rws/cattributehandler.h"

namespace RWS
{
   namespace LightHelper
   {
      // Applies the packet's system commands to rLight (CMD_LoadMatrix to
      // its frame).
      void HandleSystemCommands(RpLight& rLight, const CAttributePacket& rAttr);
   }
}

#endif
