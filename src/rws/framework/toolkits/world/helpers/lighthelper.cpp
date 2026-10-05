// RenderWare Studio's light helper (the game framework's
// framework/toolkits/world/helpers/lighthelper.cpp): the one function the
// game keeps, which applies an entity's matrix command to its light's frame
// (WorldLight's attributes, unit_0C5380).

#include "rw/ostypes.h"
#include "rw/baframe.h"
#include "rw/rplight.h"
#include "rws/cattributehandler.h"
#include "rws/csystemcommands.h"
#include "rws/lighthelper.h"

// match: ?HandleSystemCommands@LightHelper@RWS@@YAXAAURpLight@@ABVCAttributePacket@2@@Z @ 0x001330B0
void RWS::LightHelper::HandleSystemCommands(RpLight& rLight, const CAttributePacket& rAttr)
      {
         CAttributeCommandIterator attrIt(rAttr, RWS_CLASSID_OF(CSystemCommands));

         while (!attrIt.IsFinished())
         {
            if (attrIt->GetCommandId() == CSystemCommands::CMD_LoadMatrix)
            {
               RwFrame* pFrame = RpLightGetFrame(&rLight);

               if (pFrame) CSystemCommands::UpdateFrame(*pFrame, *attrIt.operator->());
            }

            ++attrIt;
         }
      }
