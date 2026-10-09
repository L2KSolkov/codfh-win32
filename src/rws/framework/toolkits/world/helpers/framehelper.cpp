// RenderWare Studio's frame helper (the game framework's
// framework/toolkits/world/helpers/framehelper.cpp): destroys a frame no
// object uses, and detaches a child frame keeping its world position.

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rws/framehelper.h"

// match: ?FrameDestroy@FrameHelper@RWS@@YAHPAURwFrame@@@Z @ 0x00133040
// sp-match: ?FrameDestroy@FrameHelper@RWS@@YAHPAURwFrame@@@Z @ 0x000E3800
RwBool RWS::FrameHelper::FrameDestroy(RwFrame *pFrame)
      {
         if (reinterpret_cast<void*>(pFrame->objectList.link.next) == reinterpret_cast<void*>(&pFrame->objectList))
         {
            RwFrameDestroy(pFrame);

            return(TRUE);
         }

         return(FALSE);
      }

// match: ?RemoveChildFrame@FrameHelper@RWS@@YAPAURwFrame@@PAU3@PAX@Z @ 0x00133070
// sp-match: ?RemoveChildFrame@FrameHelper@RWS@@YAPAURwFrame@@PAU3@PAX@Z @ 0x000E3830
RwFrame* RWS::FrameHelper::RemoveChildFrame(RwFrame* pFrame, void*)
      {
         RwMatrixCopy( RwFrameGetMatrix(pFrame), RwFrameGetLTM(pFrame) );

         RwFrameRemoveChild(pFrame);

         return(pFrame);
      }
