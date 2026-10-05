/*
 * RWS::LinearAllocationPolicy, copied from RenderWare Studio's game
 * framework (Studio\console\game_framework\source\framework\core\
 * attributehandler\Allocation Policies\linearallocationpolicy.h), the
 * RWS_DISABLE_MEMORY_CHECKING, non-RWS_DESIGN build the image has:
 * operator new takes the size and a memory type (CDebugScript::MakeNew
 * passes 0x24 and RWS_MEMORY_TYPE_RWS, 2) and rounds the size up to
 * CClassFactory::m_AlignmentSize (64). Its matching operator delete is empty
 * in that build; it is declared here rather than defined, as /OPT:ICF folded
 * it into the empty sub_19A750 (config/aliases.txt). The array forms are
 * left out until something needs them.
 */
#ifndef RWS_LINEARALLOCATIONPOLICY_H
#define RWS_LINEARALLOCATIONPOLICY_H

#include "rw/ostypes.h"
#include "rws/cclassfactory.h"
#include "rws/clinearmemorymanager.h"
#include "rws/memoryhandler.h"

namespace RWS
{
   class LinearAllocationPolicy
   {
   public:
      static RwBool UseLinearMemory() {return true;}

      void * operator new(size_t size, const RwUInt32 Type)
      {
         if (size % CClassFactory::m_AlignmentSize)
         {
            size += CClassFactory::m_AlignmentSize - (size % CClassFactory::m_AlignmentSize );
         }

         void *ptr = CLinearMemoryManager::Instance()->RequestMemory(size);

         return ptr;
      }

      void operator delete(void * pObj)
      {
      }

      void operator delete(void * pObj, const RwUInt32 Type);
   };
}

#define RWS_NEW new(RWS::RWS_MEMORY_TYPE_RWS)

// RenderWare Studio defines MakeNew in the class (RWS_MAKENEWCLASS). Referenced only by
// the registrar's dynamic initializer, VC7.1 would then emit it after the initializers,
// at the end of the object; the image has every behaviour's MakeNew first, before its
// constructor (76 of 76), so the game's build declares it in the class and defines it at
// the top of the behaviour's file (RWS_DEFINE_MAKENEW), with the same body (PLAN M7).
#define RWS_MAKENEWCLASS(classname) static RWS::CAttributeHandler* MakeNew(const RWS::CAttributePacket& attr);
#define RWS_DEFINE_MAKENEW(classname) RWS::CAttributeHandler* classname::MakeNew(const RWS::CAttributePacket& attr){RWS::CAttributeHandler *ptr = static_cast<RWS::CAttributeHandler*>(RWS_NEW classname(attr));return ptr;}

#endif
