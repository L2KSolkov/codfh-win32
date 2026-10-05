/*
 * RWS::CRwSplineResource, copied from RenderWare Studio's game framework
 * (framework/toolkits/rwsplineresource/rwsplineresource.h): the resource
 * handler for splines. The image's handlers have no Update.
 */
#ifndef RWS_RWSPLINERESOURCE_H
#define RWS_RWSPLINERESOURCE_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rws/cresourcehandler.h"

namespace RWS
{
   class CRwSplineResource: public CResourceHandler
   {
      public:
         virtual void *Load(const RwChar *psName, const RwChar *psType, const RwChar *psResourcePath,
            RwStream* pStream, RwUInt32 uiStreamSize,RwUInt32 &uiResourceSize);
         virtual RwBool UnLoad(const RwChar *pStrType, void *pResource);
         virtual RwBool IsHandled(const RwChar *psType);
   };
}

#endif
