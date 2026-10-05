/*
 * RWS::CRenderwareResource, after RenderWare Studio's game framework
 * (framework/toolkits/rwgfxresource/rwgfxresource.h): the resource handler
 * for RenderWare's own assets ("rwID_..." types). The game's loads only
 * texture dictionaries, so only their readers are declared; the image's
 * handlers have no Update.
 */
#ifndef RWS_RWGFXRESOURCE_H
#define RWS_RWGFXRESOURCE_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "rws/cresourcehandler.h"

namespace RWS
{
   class CRenderwareResource: public CResourceHandler
   {
      public:
         virtual void *Load(const RwChar *psName, const RwChar *psType, const RwChar *psResourcePath,
            RwStream* pStream, RwUInt32 uiStreamSize,RwUInt32 &uiResourceSize);
         virtual RwBool UnLoad(const RwChar *pStrType, void *pResource);
         virtual RwBool IsHandled(const RwChar *psType);

      private:
         RwTexDictionary* TexDictionaryStreamRead (RwStream *stream);
         RwTexDictionary* PiTexDictionaryStreamRead (RwStream *stream);
   };
}

#endif
