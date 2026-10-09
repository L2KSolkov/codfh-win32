// RenderWare Studio's linear memory manager (the game framework's
// framework/core/attributehandler/clinearmemorymanager.cpp): the pools the
// behaviours are placement-allocated from, sized by the stream's placement
// new chunk. FreeMemory is not in the image (unreferenced).

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/badevice.h"
#include "rws/cclassfactory.h"
#include "rws/clinearmemorymanager.h"
#include "rws/memoryhandler.h"
#include "rws/strfunc.h"
#include "game/gameloop.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?_Insert_n@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXViterator@12@IABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z>1>8 @ 0x0041D770
// match: __ehhandler$?_Insert_n@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXViterator@12@IABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z>1>16>16 @ 0x0041D790
// match: __ehhandler$?_Insert_n@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXViterator@12@IABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z>1>16>36 @ 0x0041D7A0
// match: __ehhandler$?_Insert_n@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXViterator@12@IABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z>1>16 @ 0x0041D7B0
// match: __ehhandler$?_Insert_n@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXViterator@12@IABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z>1 @ 0x0041D7D8
// match: .CRT$XCU+0 @ 0x004270A4

// match: _$E2 @ 0x0030B830
// match: _$E3 @ 0x0030E630
// sp-match: _$E2 @ 0x0021D890
// sp-match: _$E3 @ 0x0021E9C0
// STL templates single player calls out of line from _Insert_n (MP expands them):
// sp-match: ??$fill@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@PAU123@@std@@YAXPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@0ABQAU123@@Z @ 0x000DFDE0
// sp-match: ??$copy_backward@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@PAPAU123@@std@@YAPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@PAPAU123@00@Z @ 0x000DFE00
// sp-match: ??$_Ucopy@PAPAULinearMemoryPool@CLinearMemoryManager@RWS@@@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@PAPAU234@00@Z @ 0x000DFE30
// sp-match: ?_Ufill@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEPAPAULinearMemoryPool@CLinearMemoryManager@RWS@@PAPAU345@IABQAU345@@Z @ 0x000DFE60
// sp-match: _$E2 @ 0x0021D890

namespace RWS
{
   CLinearMemoryManager::LinearMemoryPools CLinearMemoryManager::m_StoragePools;
   CLinearMemoryManager::LinearMemoryPool * CLinearMemoryManager::m_pCurrentPool = 0;
}

// match: ?SetupPlacementNewInfo@?A0x27aea8e5@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x0012D0A0
// sp-match: ?SetupPlacementNewInfo@?A0x27aea8e5@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000E0120
namespace RWS
{
   namespace
   {
      void SetupPlacementNewInfo (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         RwChar *buffer = static_cast<RwChar*>(::RWS_OP_NEW(rChunkHeader.length) );
         RwChar *pbuffer = buffer;

         RwStreamRead(pStream, buffer, rChunkHeader.length);

         RwInt32 count = *reinterpret_cast<RwInt32 *>(pbuffer);

         pbuffer += sizeof(RwInt32);

         size_t TotalStorage = 0;

         for (RwInt32 i = 0; i < count; i++)
         {
            RwChar *tString;
            RwInt32 stringLength;
            RwInt32 entityCount;

            tString = pbuffer;

            stringLength = rwstrlen(tString) + 1;
            pbuffer += stringLength;

            stringLength = stringLength%4;
            if (stringLength)
               pbuffer += 4 - (stringLength);

            entityCount = *reinterpret_cast<RwInt32 *>(pbuffer);

            pbuffer += sizeof(RwInt32);

            size_t size = RWS::CClassFactory::GetRegisteredClassSize(tString);

            TotalStorage += size * entityCount;
         }

         CLinearMemoryManager::Instance()->CreateMemoryPool(TotalStorage);

         operator delete (buffer);
      }
   }
}

// match: ?RegisterStreamChunkHandlers@CLinearMemoryManager@RWS@@SAXXZ @ 0x0012D270
// sp-match: ?RegisterStreamChunkHandlers@CLinearMemoryManager@RWS@@SAXXZ @ 0x000E01D0
void RWS::CLinearMemoryManager::RegisterStreamChunkHandlers(void)
   {
      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
           strfunc_PlacementNew), SetupPlacementNewInfo);
   }

// match: ?RequestMemory@CLinearMemoryManager@RWS@@SAPAXI@Z @ 0x0012D290
// sp-match: ?RequestMemory@CLinearMemoryManager@RWS@@SAPAXI@Z @ 0x000DFDA0
void * RWS::CLinearMemoryManager::RequestMemory(size_t size)
   {
      if (!m_pCurrentPool)
      {
         return (0);
      }

      void *ret = m_pCurrentPool->m_pStorageNext;

      if ((m_pCurrentPool->m_pStorageNext + size ) > m_pCurrentPool->m_pStorageEnd)
      {
         return (0);
      }

      if ((size % CClassFactory::m_AlignmentSize) != 0)
      {
         return (0);
      }

      m_pCurrentPool->m_pStorageNext += size;
      m_pCurrentPool->m_uAllocCount++;

      return (ret);
   }

// CreateMemoryPool (inline in the header) and the pool vector's
// instantiations (the XDK's Dinkumware <vector>), in the image's order.
// Instance, reserve and _Xlen are the copies placed with CDebugScript's
// unit (0x43010); the pointer range's _Uninit_copy is identical to another
// vector's (/OPT:ICF) and is aliased there. The static vector's initializer
// (0x30B830) is left unplaced, like the other units' static initializers.
// match: ?CreateMemoryPool@CLinearMemoryManager@RWS@@SAPAV12@I@Z @ 0x0012D1B0
// match: ?push_back@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@QAEXABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z @ 0x0012D310
// match: ?insert@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@QAE?AViterator@12@V312@ABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z @ 0x0012D3F0
// match: ?_Insert_n@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXViterator@12@IABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z @ 0x0012D4A0
// match: __ehhandler$?_Insert_n@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXViterator@12@IABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z @ 0x003016A0
// match: ?_Buy@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAE_NI@Z @ 0x0012DB10
// match: ?_Tidy@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXXZ @ 0x0012DBB0
// sp-match: ?CreateMemoryPool@CLinearMemoryManager@RWS@@SAPAV12@I@Z @ 0x000E0070
// sp-match: ?_Insert_n@?$vector@PAULinearMemoryPool@CLinearMemoryManager@RWS@@V?$allocator@PAULinearMemoryPool@CLinearMemoryManager@RWS@@@std@@@std@@IAEXViterator@12@IABQAULinearMemoryPool@CLinearMemoryManager@RWS@@@Z @ 0x000DFE90
