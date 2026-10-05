// RenderWare Studio's camera helper (the game framework's
// framework/toolkits/world/helpers/camerahelper.cpp) as the game has it: a
// near clip plane of 30, and a field of view that is widened by 1.33 while
// dword_4CF9A8 is set (the HUD toggles it) and scaled by flt_429C38 while
// byte_4CF9AC is set. HandleSystemCommands is not in the image.

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baengine.h"
#include "rw/baframe.h"
#include "rw/baraster.h"
#include "rw/rpworld.h"
#include "rws/camerahelper.h"
#include "rws/framehelper.h"
#include "rws/mainloop.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DAC18
extern const RwReal flt_3DAC18 = 16.666666f;
// 0x00429C38
RwReal flt_429C38 = 1.0f;
// 0x004CF9A8
#ifndef CODFH_PLAIN
RwInt32 dword_4CF9A8;
#endif
// 0x004CF9AC
#ifndef CODFH_PLAIN
bool byte_4CF9AC;
#endif
// End of its data definitions.


namespace RWS
{
   namespace CameraHelper
   {
      namespace
      {
         const RwReal DefaultCameraViewAngle = rwPI * ((60.0f) / 180.0f);
         const RwReal DefaultFarClipPlane = 5000.0f;
         const RwReal DefaultNearClipPlane = 30.0f;
         const RwCameraProjection DefaultCameraProjection = rwPERSPECTIVE;

         // The widescreen view's widening (not an address).
         const RwReal WideViewWindowScale = 1.33f;
      }
   }
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DAC18@@3MB @ 0x003DAC18
// match: _DefaultCameraViewAngle @ 0x003DAC1C
// match: _DefaultFarClipPlane @ 0x003DAC20
// match: _DefaultNearClipPlane @ 0x003DAC24
// match: _WideViewWindowScale @ 0x003DAC28
// match: ?flt_429C38@@3MA @ 0x00429C38

// match: ?Destroy@CameraHelper@RWS@@YAHPAURwCamera@@@Z @ 0x00132BD0

RwBool RWS::CameraHelper::Destroy(RwCamera *pCamera)
      {
         RwFrame* pFrame = RwCameraGetFrame(pCamera);

         if (pFrame)
         {
            RwFrameForAllChildren(pFrame, FrameHelper::RemoveChildFrame, 0);

            if (RwFrameGetParent(pFrame)) RwFrameRemoveChild(pFrame);

            RwCameraSetFrame(pCamera, 0);

            FrameHelper::FrameDestroy(pFrame);
         }

         RpWorld* pWorld = RwCameraGetWorld (pCamera);

         if (pWorld) RpWorldRemoveCamera(pWorld, pCamera);

         if (RwCameraGetRaster(pCamera))
         {
            RwRaster* pRaster = RwCameraGetRaster(pCamera);

            if (pRaster)
            {
               RwRasterDestroy(pRaster);
               RwCameraSetRaster(pCamera, 0);
            }
         }

         if (RwCameraGetZRaster(pCamera))
         {
               RwRaster *pRaster = RwCameraGetZRaster(pCamera);

               if (pRaster)
               {
                  RwRasterDestroy(pRaster);
                  RwCameraSetZRaster(pCamera, 0);
               }
         }

         RwBool ret = RwCameraDestroy(pCamera);

         return(ret);
      }

// match: ?CreateMainRasterCamera@CameraHelper@RWS@@YAPAURwCamera@@III@Z @ 0x00132CC0
RwCamera *RWS::CameraHelper::CreateMainRasterCamera(RwUInt32 Width, RwUInt32 Height, RwUInt32 ZDepth)
      {
         RwCamera *_camera = RwCameraCreate();

         RwRaster *_raster = RwRasterCreate(Width, Height, 0, rwRASTERTYPECAMERA);

         RwCameraSetRaster (_camera, _raster);

         RwRaster *_rasterZ = RwRasterCreate(Width, Height, ZDepth, rwRASTERTYPEZBUFFER);

         RwCameraSetZRaster (_camera, _rasterZ);

         RwFrame *_frame = RwFrameCreate();

         RwFrameSetIdentity(_frame);

         RwCameraSetFrame (_camera, _frame);

         RwCameraSetProjection (_camera, DefaultCameraProjection);
         RwCameraSetNearClipPlane (_camera, DefaultNearClipPlane);
         RwCameraSetFarClipPlane (_camera, DefaultFarClipPlane);

         RwReal _aspect;

         if (Height != 0)
         {
            _aspect = (RwReal)Width / (RwReal)Height;

            RwV2d  _viewwindow;

            _viewwindow.x = static_cast<RwReal>(RwTan (DefaultCameraViewAngle * 0.5f));
            _viewwindow.y = _viewwindow.x / _aspect;

            RwCameraSetViewWindow (_camera, &_viewwindow);
         }

         return(_camera);
      }

// match: ?CreateSubRasterCamera@CameraHelper@RWS@@YAPAURwCamera@@AAURwRect@@@Z @ 0x00132DE0
RwCamera *RWS::CameraHelper::CreateSubRasterCamera(RwRect &rRect)
      {
         RwUInt32 width = rRect.w;
         RwUInt32 height = rRect.h;

         RwCamera *main_camera = MainLoop::Render::GetCamera();

         RwCamera *_camera = CreateMainRasterCamera(0, 0, 0);

         RwRasterSubRaster(RwCameraGetRaster(_camera), RwCameraGetRaster(main_camera), &rRect);
         RwRasterSubRaster(RwCameraGetZRaster(_camera), RwCameraGetZRaster(main_camera), &rRect);

         RwReal _aspect = (RwReal)width / (RwReal)height;

         RwV2d  _viewwindow;

         _viewwindow.x = static_cast<RwReal>(RwTan (DefaultCameraViewAngle * 0.5f));
         _viewwindow.y = _viewwindow.x / _aspect;

         RwCameraSetViewWindow (_camera, &_viewwindow);

         return(_camera);
      }

// match: ?SetFieldOfView@CameraHelper@RWS@@YAXMPAURwCamera@@@Z @ 0x00132EB0
void RWS::CameraHelper::SetFieldOfView(RwReal rViewWindow, RwCamera *pCamera)
      {
         RwVideoMode videoMode;

         RwEngineGetVideoModeInfo(&videoMode, RwEngineGetCurrentVideoMode());

         RwRect rect;
         RwV2d vw;

         rect.x = 0;
         rect.y = 0;
         rect.w = RwRasterGetWidth(RwCameraGetRaster(pCamera));
         rect.h = RwRasterGetHeight(RwCameraGetRaster(pCamera));

         if (videoMode.flags & rwVIDEOMODEFFINTERLACE) rect.h *= 2;

         vw.x = rViewWindow;

         if (dword_4CF9A8) vw.x *= WideViewWindowScale;

         vw.y = (rect.h * rViewWindow) / rect.w;

         if (byte_4CF9AC)
         {
            vw.x *= flt_429C38;
            vw.y *= flt_429C38;
         }

         RwCameraSetViewWindow(pCamera, &vw);
      }
