// RenderWare Studio's image loader registration (the game framework's
// framework/startup/registerimageloaders.cpp) as the game has it: no image
// formats, only the Xbox's DDS texture reader, hooked in front of
// RenderWare's texture read callback.

#include "rw/ostypes.h"
#include "rw/batextur.h"
#include "rw/rwxbox.h"
#include "rws/startup.h"

namespace RWS
{
   namespace
   {
      RwTextureCallBackRead OldCB;
   }
}

// match: ?DDSTextureRead@?A0x1f0d7d45@RWS@@YAPAURwTexture@@PBD0@Z @ 0x00132610
namespace RWS
{
   namespace
   {
      RwTexture * DDSTextureRead(const RwChar * szName, const RwChar * szMaskName)
      {
         RwTexture * pTexture = 0;

         if (pTexture = RwXboxDDSTextureRead(szName, szMaskName))
         {
            return pTexture;
         }

         return OldCB(szName, szMaskName);
      }
   }
}

// match: ?HookDDSTextureRead@?A0x1f0d7d45@RWS@@YAXXZ @ 0x00132650
namespace RWS
{
   namespace
   {
      void HookDDSTextureRead(void)
      {
         OldCB = RwTextureGetReadCallBack();

         RwTextureSetReadCallBack(DDSTextureRead);
      }
   }
}

// The database's j_?DDSTextureRead@?A0x6064568b@RWS@@... (a thunk name that
// fits neither its arguments nor its body).
// match: ?RegisterImageLoaders@StartUp@RWS@@YAHXZ @ 0x00132670
RwBool RWS::StartUp::RegisterImageLoaders(void)
      {
         bool flag = true;

         HookDDSTextureRead();

         return (flag);
      }
