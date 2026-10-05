/*
 * RWS::CResourceHandler, copied from RenderWare Studio's game framework
 * (Studio\console\game_framework\source\framework\core\resourcemanager\
 * cresourcehandler.h).
 *
 * The image's version has no Update: a handler's vtable (the Alfa files',
 * off_3DA848) holds Open, Close (both empty inlines, folded by /OPT:ICF into
 * pDtor, 0x1E41C0), IsHandled, Load, UnLoad and the scalar deleting
 * destructor. Its only data is the vtable (4 bytes). The constructor adds
 * the handler to the handlers' list (cresourcehandler.cpp).
 */
#ifndef RWS_CRESOURCEHANDLER_H
#define RWS_CRESOURCEHANDLER_H

#include "rw/ostypes.h"
#include "rw/bastream.h"

namespace RWS
{
   class CResourceHandler
   {
      public:

         virtual void Open(void) {};
         virtual void Close(void) {};
         virtual RwBool IsHandled(const RwChar *psType) = 0;
         virtual void *Load(const RwChar *psName,
            const RwChar *psType,
            const RwChar *psResourcePath,
            RwStream* pStream,
            RwUInt32 uiStreamSize,
            RwUInt32 &uiResourceSize) = 0;
         virtual RwBool UnLoad(const RwChar *pStrType, void *pResource) = 0;

         CResourceHandler(void);

         virtual ~CResourceHandler(void);

         // The handler for the resource type psType (0 when none handles
         // it), and every handler's Open and Close.
         static CResourceHandler *FindHandler(const RwChar * const psType);
         static void OpenAll(void);
         static void CloseAll(void);

      private:

         CResourceHandler(const CResourceHandler& rhs);               // Disable copy constructor
         CResourceHandler &operator = (const CResourceHandler& rhs);  // Disable copy operator,
   };
}

#endif
