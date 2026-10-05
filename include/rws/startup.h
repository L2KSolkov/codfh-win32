/*
 * RWS::StartUp, after RenderWare Studio's game framework
 * (framework/startup/startup.h): the plugin attachment and the image loader
 * registration the game's start-up (sub_D99F0) calls.
 */
#ifndef RWS_STARTUP_H
#define RWS_STARTUP_H

#include "rw/ostypes.h"

namespace RWS
{
   namespace StartUp
   {
      bool AttachPlugins(void);
      // Hooks the Xbox's DDS texture reader in front of RenderWare's and
      // returns TRUE (the game's registers no image formats; the database
      // calls it j_?DDSTextureRead@...).
      RwBool RegisterImageLoaders(void);
   }
}

#endif
