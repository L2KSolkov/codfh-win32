/*
 * RWS::CameraHelper, after RenderWare Studio's game framework
 * (framework/toolkits/world/helpers/camerahelper.h): the cameras the main
 * loop and the front end make and destroy.
 */
#ifndef RWS_CAMERAHELPER_H
#define RWS_CAMERAHELPER_H

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/baengine.h"

// The field of view's switches (the game's): dword_4CF9A8 widens it by 1.33
// (the HUD toggles it, type_DC400.h), byte_4CF9AC scales it by flt_429C38.
#ifdef CODFH_PLAIN
extern RwInt32 &dword_4CF9A8;
#else
extern RwInt32 dword_4CF9A8;
#endif
#ifdef CODFH_PLAIN
extern bool &byte_4CF9AC;
#else
extern bool byte_4CF9AC;
#endif
extern RwReal flt_429C38;

namespace RWS
{
   namespace CameraHelper
   {
      RwCamera *CreateMainRasterCamera(RwUInt32 Width, RwUInt32 Height, RwUInt32 ZDepth);
      // A camera drawing to a sub-raster of the main camera's (the main
      // loop's second camera, for Rt2d).
      RwCamera *CreateSubRasterCamera(RwRect &rRect);
      RwInt32 Destroy(RwCamera *pCamera);
      // Sets pCamera's field of view to fov (degrees; the HUD, with the
      // player's, type_DC400::sub_DF000).
      void SetFieldOfView(RwReal fov, RwCamera *pCamera);
   }
}

#endif
