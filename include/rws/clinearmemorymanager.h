/*
 * RWS::CLinearMemoryManager, copied from RenderWare Studio's game framework
 * (Studio\console\game_framework\source\framework\core\attributehandler\
 * clinearmemorymanager.h): the singleton accessor Instance, with its
 * function-local static and the private constructor that reserves eight
 * pools (inline, so each translation unit that allocates with it emits them;
 * the image keeps CDebugScript's copies at 0x43010 and 0x43450), and the
 * static RequestMemory; CreateMemoryPool (inline, but emitted out of line
 * at 0x12D1B0 for the placement new chunk's handler), the chunk handler's
 * registration and the current pool; DestroyLinearMemoryManager (with
 * DestroyMemoryPool inlined), emitted for the main loop's Close. FreeMemory
 * is not in the image.
 */
#ifndef RWS_CLINEARMEMORYMANAGER_H
#define RWS_CLINEARMEMORYMANAGER_H

#include <vector>

#include "rw/ostypes.h"
#include "rws/cclassfactory.h"
#include "rws/memoryhandler.h"

namespace RWS
{
   class CLinearMemoryManager
   {
   private:
      struct LinearMemoryPool
      {
         RwUInt8 * m_pStorage;
         RwUInt8 * m_pStorageStart;
         RwUInt8 * m_pStorageNext;
         RwUInt8 * m_pStorageEnd;
         RwUInt32 m_uAllocCount;
      };

      typedef std::vector<LinearMemoryPool *> LinearMemoryPools;

   public:
      static void DestroyLinearMemoryManager(void)
      {
         LinearMemoryPools::iterator it = m_StoragePools.begin();

         while (it != m_StoragePools.end())
         {
            LinearMemoryPool * pPool = (*it);

            it = m_StoragePools.erase(it);

            DestroyMemoryPool(pPool);
         }
      }

      static CLinearMemoryManager * Instance()
      {
         static CLinearMemoryManager tCLinearMemoryManager;

         return &tCLinearMemoryManager;
      }

      static CLinearMemoryManager * CreateMemoryPool(size_t MemSize)
      {
         LinearMemoryPool * pNewPool;

         pNewPool = new(RWS_MEMORY_TYPE_RWS) LinearMemoryPool;

         pNewPool->m_pStorage = new(RWS_MEMORY_TYPE_RWS) RwUInt8[MemSize + CClassFactory::m_AlignmentSize];

         pNewPool->m_pStorageStart = pNewPool->m_pStorage;

         if ((reinterpret_cast<RwUInt32>(pNewPool->m_pStorageStart) % CClassFactory::m_AlignmentSize))
            pNewPool->m_pStorageStart += (CClassFactory::m_AlignmentSize - (reinterpret_cast<RwUInt32>(pNewPool->m_pStorageStart) % CClassFactory::m_AlignmentSize));

         pNewPool->m_pStorageNext = pNewPool->m_pStorageStart;
         pNewPool->m_pStorageEnd = pNewPool->m_pStorageStart + MemSize;
         pNewPool->m_uAllocCount = 0;

         m_StoragePools.push_back(pNewPool);

         m_pCurrentPool = pNewPool;

         return Instance();
      }

      static void * RequestMemory(size_t size);

      static void RegisterStreamChunkHandlers(void);

   private:
      static void DestroyMemoryPool(LinearMemoryPool * pPool)
      {
         delete [] pPool->m_pStorage;
         delete pPool;
      }

      CLinearMemoryManager()
      {
         m_StoragePools.reserve(8);
      };

      static LinearMemoryPools m_StoragePools;
      static LinearMemoryPool * m_pCurrentPool;
   };
}

#endif
