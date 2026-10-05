/*
 * RWS::CClassFactory, copied from RenderWare Studio's game framework
 * (Studio/console/game_framework/source/framework/core/attributehandler/
 * cclassfactory.h). In the image's version it is a namespace, not a class:
 * its functions are free (?MakeNew@CClassFactory@RWS@@YAPAVCAttributeHandler@2@
 * PBDABVCAttributePacket@2@@Z). m_AlignmentSize is what the linear
 * allocation policy rounds sizes up to; the registrar is what a behaviour's
 * RWS_REGISTERCLASS defines (the image names its constructor
 * ??0CRegistrar@CClassFactory@RWS@@QAE@PBDP6APAVCAttributeHandler@2@
 * ABVCAttributePacket@2@@ZIH@Z).
 */
#ifndef RWS_CCLASSFACTORY_H
#define RWS_CCLASSFACTORY_H

#include <stddef.h>

#include "rw/ostypes.h"

namespace RWS
{
   class CAttributeHandler;
   class CAttributePacket;

   namespace CClassFactory
   {
      const RwUInt32 m_AlignmentSize = sizeof(RwUInt8) * 64;

      typedef CAttributeHandler* (*MakeNewPtr)(const CAttributePacket&);

      class CRegistrar
      {
         public:
            ~CRegistrar();
            CRegistrar(const RwChar* pClassName, MakeNewPtr makeNewFn, size_t size, RwBool UseLinearMemoryManager);
      };

      // The size a registered class's instances take in the linear
      // allocator (0 when it does not use it or is not registered).
      size_t GetRegisteredClassSize(const RwChar *pClassName);

      void RegisterClass(const RwChar *pClassName, MakeNewPtr makeNewFn, size_t size, RwBool UseLinearMemoryManager);

      // Makes an instance of the class pClassName from the packet attr.
      CAttributeHandler *MakeNew(const RwChar *pClassName, const CAttributePacket &attr);
   }

   #define RWS_REGISTERCLASS(className) RWS::CClassFactory::CRegistrar className##Registrar(#className, className::MakeNew, sizeof(className), className::UseLinearMemory())
}

#endif
