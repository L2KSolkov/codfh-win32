// RenderWare Studio's spline resource handler (the game framework's
// framework/toolkits/rwsplineresource/rwsplineresource.cpp): loads and frees
// "rwID_SPLINE" assets. An asset with no data is a placeholder RwInt32 of -1.
// The constructor and destructor are the compiler's, out of line for the
// global instance (its dynamic initializer is left unplaced, like the other
// units' static initializers).

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/badevice.h"
#include "rw/baimage.h"
#include "rw/rpspline.h"
#include "rws/memoryhandler.h"
#include "rws/rwsplineresource.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7CRwSplineResource@RWS@@6B@ @ 0x003DAA18
// match: .CRT$XCU+0 @ 0x004270B8

// match: _$E1 @ 0x0030B8D0
// match: _$E2 @ 0x0030E6D0
// match: ?Load@CRwSplineResource@RWS@@UAEPAXPBD00PAURwStream@@IAAI@Z @ 0x001304B0
// sp-match: ?Load@CRwSplineResource@RWS@@UAEPAXPBD00PAURwStream@@IAAI@Z @ 0x000E1A60

void *RWS::CRwSplineResource::Load(const RwChar *psName,
                                 const RwChar *psType,
                                 const RwChar *psResourcePath,
                                 RwStream* pStream,
                                 RwUInt32 uiStreamSize,
                                 RwUInt32 &uiResourceSize)
   {
      void * pBuffer = 0;

      if (uiStreamSize > 0)
      {
         if (psResourcePath)
         {
            RwImageSetPath(psResourcePath);
         }

         RwChunkHeaderInfo _RwChunkHeaderInfo;

         RwStreamReadChunkHeaderInfo(pStream, &_RwChunkHeaderInfo);

         switch (_RwChunkHeaderInfo.type)
         {
            case rwID_SPLINE:
               pBuffer = RpSplineStreamRead(pStream);
               break;
         }
      }
      else
      {
         pBuffer = new(RWS_MEMORY_TYPE_RWS) RwInt32;

         *static_cast<RwInt32 *>(pBuffer) = -1;
      }

      uiResourceSize = uiStreamSize;

      return (pBuffer);
   }

// match: ?UnLoad@CRwSplineResource@RWS@@UAEHPBDPAX@Z @ 0x00130540
// sp-match: ?UnLoad@CRwSplineResource@RWS@@UAEHPBDPAX@Z @ 0x000E1AF0
RwBool RWS::CRwSplineResource::UnLoad(const RwChar *pStrType, void *pResource)
   {
      RwBool ret = FALSE;

      if (*reinterpret_cast<RwInt32 *>(pResource) == -1)
      {
         delete(reinterpret_cast<RwInt32 *>(pResource));

         ret = TRUE;
      }
      else
      {
         if (rwstrcmp(pStrType, "rwID_SPLINE") == 0)
         {
            RpSplineDestroy(reinterpret_cast<RpSpline *>(pResource));

            ret = TRUE;
         }
      }

      return (ret);
   }

// match: ?IsHandled@CRwSplineResource@RWS@@UAEHPBD@Z @ 0x001305B0
// sp-match: ?IsHandled@CRwSplineResource@RWS@@UAEHPBD@Z @ 0x000E1B50
RwBool RWS::CRwSplineResource::IsHandled(const RwChar *psType)
   {
      if (!rwstrcmp(psType, "rwID_SPLINE"))
      {
         return (TRUE);
      }

      return (FALSE);
   }

namespace RWS
{
   namespace
   {
      CRwSplineResource gCRwSplineResource;
   }
}

// The compiler's constructor and destructor (the global instance's).
// match: ??0CRwSplineResource@RWS@@QAE@XZ @ 0x001305E0
// match: ??1CRwSplineResource@RWS@@UAE@XZ @ 0x00130600
// sp-match: ??0CRwSplineResource@RWS@@QAE@XZ @ 0x000E1B70
// sp-match: ??1CRwSplineResource@RWS@@UAE@XZ @ 0x000DD920
