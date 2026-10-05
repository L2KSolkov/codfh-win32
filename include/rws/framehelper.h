/*
 * RWS::FrameHelper's frame functions the object holders call, copied from
 * RenderWare Studio's game framework
 * (Studio/console/game_framework/source/framework/toolkits/world/helpers/
 * framehelper.h).
 */
#ifndef RWS_FRAMEHELPER_H
#define RWS_FRAMEHELPER_H

#include "rw/ostypes.h"
#include "rw/baframe.h"

namespace RWS
{
   namespace FrameHelper
   {
      RwBool FrameDestroy(RwFrame *pFrame);
      RwFrame* RemoveChildFrame(RwFrame* pFrame, void*);
   }
}

#endif
