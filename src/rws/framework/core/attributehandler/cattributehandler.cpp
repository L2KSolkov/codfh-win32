// RenderWare Studio's attribute handler (the game framework's
// framework/core/attributehandler/cattributehandler.cpp): the attribute
// packet's chunk iterators and the registry of attribute handlers by
// instance id. The game's version keeps the handlers in the map alone (the
// Studio sources' creation-order list is not in the image): Purge and
// PurgeAll walk the map, and PurgeAll deletes from its front until it is
// empty (each handler's destructor removes itself). The function-trace and
// assert macros are compiled out (no RWS_FUNCTION calls in the image).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/badevice.h"
#include "rws/rwsguid.h"
#include "rws/cattributehandler.h"
#include "rws/attributehandlermap.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004CF7D8
RWS::NewAttributeHandlerCallBack RWS::CAttributeHandler::pNewAttributeHandlerCallBack;
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x0041D558
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x0041D560
// match: __ehhandler$??1out_of_range@std@@UAE@XZ>1>8 @ 0x0041D57C
// match: __ehhandler$??1out_of_range@std@@UAE@XZ>1 @ 0x0041D584
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@@Z>1>8 @ 0x0041D5A0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@@Z>1 @ 0x0041D5A8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@D@Z>1>8 @ 0x0041D5C4
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@D@Z>1>16>16 @ 0x0041D5D4
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@D@Z>1>16 @ 0x0041D5E4
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@D@Z>1 @ 0x0041D5F8
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@XZ>1>8 @ 0x0041D614
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@XZ>1>16>16 @ 0x0041D624
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@XZ>1>16 @ 0x0041D634
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@XZ>1 @ 0x0041D648
// match: .CRT$XCU+0 @ 0x004270A0

// match: _$E1 @ 0x0030B810
// match: _$E2 @ 0x0030E610

namespace RWS
{
   namespace
   {
      Id2AttributeHandler_Map theMap;
   }

   enum ChunkType {
      CLASSID = 0x80000000,
      INSTANCEID = 0x40000000,
      CREATECLASSID = 0x20000000
   };
}

   // Folded (/OPT:ICF) into the kujuUI pointer's test sub_E87C0.
// sp-match: ?IsEndChunk@CAttributeDataChunk@RWS@@ABE_NXZ @ 0x000DE3B0
bool RWS::CAttributeDataChunk::IsEndChunk() const
   {
      return ( 0 == size_ );
   }

// STL template members single player calls out of line (MP expands them):
// sp-match: ?_Max@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@KAPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@@Z @ 0x000DE4F0
// sp-match: ?_Min@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@KAPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@@Z @ 0x000DE510

// match: ?pNextChunk@CAttributeDataChunk@RWS@@ABEPBV12@XZ @ 0x0012A0D0
// sp-match: ?pNextChunk@CAttributeDataChunk@RWS@@ABEPBV12@XZ @ 0x000DE3C0
const RWS::CAttributeDataChunk* RWS::CAttributeDataChunk::pNextChunk() const
   {
      return ( reinterpret_cast<CAttributeDataChunk*>(reinterpret_cast<RWS_DWORD>(this) + size_) );
   }

// match: ?GetNameOfClassToCreate@CAttributePacket@RWS@@QBEPBDXZ @ 0x0012A0F0
// sp-match: ?GetNameOfClassToCreate@CAttributePacket@RWS@@QBEPBDXZ @ 0x000DE650
const RwChar* RWS::CAttributePacket::GetNameOfClassToCreate() const
   {
      CAttributeDataChunkIterator chunkIt(firstChunk_);

      return ( reinterpret_cast<const RwChar*>(&chunkIt->data_) );
   }

// match: ?GetInstanceId@CAttributePacket@RWS@@QBE?AVRWSGUID@2@XZ @ 0x0012A120
// sp-match: ?GetInstanceId@CAttributePacket@RWS@@QBE?AVRWSGUID@2@XZ @ 0x000DE670
RWS::RWSGUID RWS::CAttributePacket::GetInstanceId() const
   {
      bool found = false;
      RWSGUID result;

      CAttributeDataChunkIterator chunkIt(firstChunk_);
      while (!found)
      {
         if (INSTANCEID == chunkIt->type_)
         {
            result = *reinterpret_cast<const RWSGUID *>(&chunkIt->data_);
            found = true;
         }

         ++chunkIt;
      }

      return ( result );
   }

// match: ??0CAttributeDataChunkIterator@RWS@@QAE@ABVCAttributeDataChunk@1@@Z @ 0x0012A1B0
// sp-match: ??0CAttributeDataChunkIterator@RWS@@QAE@ABVCAttributeDataChunk@1@@Z @ 0x000DE3E0
RWS::CAttributeDataChunkIterator::CAttributeDataChunkIterator(const CAttributeDataChunk& begin)
      : pCurrChunk_(&begin) {}

// match: ?IsFinished@CAttributeDataChunkIterator@RWS@@QBE_NXZ @ 0x0012A1D0
// sp-match: ?IsFinished@CAttributeDataChunkIterator@RWS@@QBE_NXZ @ 0x000DE3F0
bool RWS::CAttributeDataChunkIterator::IsFinished() const
   {
      return ( pCurrChunk_->IsEndChunk() );
   }

// match: ??ECAttributeDataChunkIterator@RWS@@QAEAAV01@XZ @ 0x0012A1F0
// sp-match: ??ECAttributeDataChunkIterator@RWS@@QAEAAV01@XZ @ 0x000DE400
RWS::CAttributeDataChunkIterator& RWS::CAttributeDataChunkIterator::operator++()
   {
      pCurrChunk_ = pCurrChunk_->pNextChunk();
      return *this;
   }

   // Folded (/OPT:ICF) into the kujuUI pointer's operator-> sub_1EE9D0.
// sp-match: ??CCAttributeDataChunkIterator@RWS@@QBEPBVCAttributeDataChunk@1@XZ @ 0x000DE410
const RWS::CAttributeDataChunk* RWS::CAttributeDataChunkIterator::operator->() const
   {
      return pCurrChunk_;
   }

// match: ??0CAttributeCommandIterator@RWS@@QAE@ABVCAttributePacket@1@PBD@Z @ 0x0012A210
// sp-match: ??0CAttributeCommandIterator@RWS@@QAE@ABVCAttributePacket@1@PBD@Z @ 0x000DE6F0
RWS::CAttributeCommandIterator::CAttributeCommandIterator(
      const CAttributePacket& packet,
      const RwChar *targetClass
      )
      :  chunkIt_(packet.firstChunk_),
         pTargetClass_(targetClass)
   {
      SkipToNextAttributeCommand(false);
   }

// match: ?IsFinished@CAttributeCommandIterator@RWS@@QBE_NXZ @ 0x0012A240
// sp-match: ?IsFinished@CAttributeCommandIterator@RWS@@QBE_NXZ @ 0x000DE420
bool RWS::CAttributeCommandIterator::IsFinished() const
   {
      return chunkIt_.IsFinished();
   }

// match: ?SkipToNextAttributeCommand@CAttributeCommandIterator@RWS@@AAEX_N@Z @ 0x0012A260
// sp-match: ?SkipToNextAttributeCommand@CAttributeCommandIterator@RWS@@AAEX_N@Z @ 0x000DE430
void RWS::CAttributeCommandIterator::SkipToNextAttributeCommand( bool lastClassIdChunkWasForTargetClass )
   {
      bool found = false;
      while (!chunkIt_.IsFinished() && !found)
      {
         switch (chunkIt_->type_)
         {
            case INSTANCEID:
            case CREATECLASSID:
               ++chunkIt_;
               break;
            case CLASSID:
               lastClassIdChunkWasForTargetClass =
                  (0 == rwstrcmp(pTargetClass_, reinterpret_cast<const RwChar*>(&chunkIt_->data_)));
               ++chunkIt_;
               break;
            default:
               if (lastClassIdChunkWasForTargetClass) found = true;
               else ++chunkIt_;
               break;
         }
      }
   }

// match: ??ECAttributeCommandIterator@RWS@@QAEAAV01@XZ @ 0x0012A310
// sp-match: ??ECAttributeCommandIterator@RWS@@QAEAAV01@XZ @ 0x000DE4C0
RWS::CAttributeCommandIterator& RWS::CAttributeCommandIterator::operator++()
   {
      ++chunkIt_;

      SkipToNextAttributeCommand(true);

      return *this;
   }

// match: ??CCAttributeCommandIterator@RWS@@QBEPBVCAttributeCommand@1@XZ @ 0x0012A330
// sp-match: ??CCAttributeCommandIterator@RWS@@QBEPBVCAttributeCommand@1@XZ @ 0x000DE4E0
const RWS::CAttributeCommand* RWS::CAttributeCommandIterator::operator->() const
   {
      return reinterpret_cast<const CAttributeCommand*>(&(*chunkIt_.operator->()));
   }

// match: ??1CAttributeHandler@RWS@@UAE@XZ @ 0x0012A350
// sp-match: ??1CAttributeHandler@RWS@@UAE@XZ @ 0x000DF2A0
RWS::CAttributeHandler::~CAttributeHandler()
   {
      Remove(m_InstanceId);
   }

// match: ?Add@CAttributeHandler@RWS@@QAEXABVRWSGUID@2@@Z @ 0x0012A380
// sp-match: ?Add@CAttributeHandler@RWS@@QAEXABVRWSGUID@2@@Z @ 0x000DF140
void RWS::CAttributeHandler::Add(const RWSGUID & instanceId)
   {
      m_InstanceId = instanceId;

      theMap.insert(Id2AttributeHandler_Map::value_type(instanceId, this));
   }

// match: ?Remove@CAttributeHandler@RWS@@SAXABVRWSGUID@2@@Z @ 0x0012A400
// sp-match: ?Remove@CAttributeHandler@RWS@@SAXABVRWSGUID@2@@Z @ 0x000DF230
void RWS::CAttributeHandler::Remove(const RWSGUID & instanceId)
   {
      theMap.erase(instanceId);
   }

// match: ?Find@CAttributeHandler@RWS@@SAPAV12@ABVRWSGUID@2@@Z @ 0x0012A420
// sp-match: ?Find@CAttributeHandler@RWS@@SAPAV12@ABVRWSGUID@2@@Z @ 0x000DE9F0
RWS::CAttributeHandler* RWS::CAttributeHandler::Find(const RWSGUID & instanceId)
   {
      CAttributeHandler* pResult = 0;
      const Id2AttributeHandler_Map::iterator it = theMap.find(instanceId);
      if (it != theMap.end()) pResult = it->second;

      return ( pResult );
   }

// match: ?Purge@CAttributeHandler@RWS@@SAXXZ @ 0x0012A480
// sp-match: ?Purge@CAttributeHandler@RWS@@SAXXZ @ 0x000DF1A0
void RWS::CAttributeHandler::Purge()
   {
      Id2AttributeHandler_Map::iterator it = theMap.begin();

      while (it != theMap.end())
      {
         if (it->second->IsLocked())
         {
            ++it;
         }
         else
         {
            CAttributeHandler *pCAttributeHandler = it->second;

            theMap.erase(it++);

            delete pCAttributeHandler;
         }
      }
   }

// match: ?PurgeAll@CAttributeHandler@RWS@@SAXXZ @ 0x0012A560
// sp-match: ?PurgeAll@CAttributeHandler@RWS@@SAXXZ @ 0x000DEA20
void RWS::CAttributeHandler::PurgeAll()
   {
      Id2AttributeHandler_Map::iterator it = theMap.begin();

      while (it != theMap.end())
      {
         delete it->second;

         it = theMap.begin();
      }

      theMap.clear();
   }

// The map's and out_of_range's instantiations (the XDK's Dinkumware
// <map>/<xtree> and <stdexcept>), in the image's order. The map's dynamic
// initializer (0x30B810, calls the constructor and registers the atexit
// destructor 0x30E610) is not a function in the database and is left
// unplaced, like the other units' static initializers.
// match: ?insert@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@@Z @ 0x0012A600
// match: ??MRWSGUID@RWS@@QBE_NABV01@@Z @ 0x0012A820
// match: ?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x0012A8A0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x003015A0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x003015A8
// match: ??1out_of_range@std@@UAE@XZ @ 0x0012AE20
// match: __ehhandler$??1out_of_range@std@@UAE@XZ-0x8 @ 0x003015C0
// match: __ehhandler$??1out_of_range@std@@UAE@XZ @ 0x003015C8
// match: ??_Gout_of_range@std@@UAEPAXI@Z @ 0x0012AE90
// match: ?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAEIABVRWSGUID@RWS@@@Z @ 0x0012AEC0
// match: ?clear@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAEXXZ @ 0x0012AFA0
// match: ?find@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@ABVRWSGUID@RWS@@@Z @ 0x0012B000
// match: ??0out_of_range@std@@QAE@ABV01@@Z @ 0x0012B0C0
// match: ?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x0012B0F0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@@Z @ 0x0012B1C0
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@@Z @ 0x0012B210
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@@Z-0x8 @ 0x003015E0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@@Z @ 0x003015E8
// match: ?_Lrotate@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@@Z @ 0x0012B560
// match: ?_Rrotate@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@@Z @ 0x0012B610
// match: ?_Lbound@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABVRWSGUID@RWS@@@Z @ 0x0012B6C0
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@D@Z @ 0x0012B760
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@D@Z @ 0x00301600
// match: ?_Inc@const_iterator@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAEXXZ @ 0x0012B850
// match: ?_Ubound@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABVRWSGUID@RWS@@@Z @ 0x0012B8E0
// match: ?_Dec@const_iterator@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAEXXZ @ 0x0012B980
// match: ??0?$map@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@@std@@QAE@XZ @ 0x0012BA40
// match: ?_Init@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEXXZ @ 0x0012BA60
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@XZ @ 0x0012BAD0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@XZ @ 0x00301610
// match: ??1?$map@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@@std@@QAE@XZ @ 0x0012BBF0
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEXXZ @ 0x0012BC10
// sp-match: ?insert@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@_N@2@ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@@Z @ 0x000DEC50
// sp-match: ?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x000DEDA0
// sp-match: ?find@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@ABVRWSGUID@RWS@@@Z @ 0x000DE960
// sp-match: ?erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x000DF080
// sp-match: ?_Erase@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@@Z @ 0x000DE880
// sp-match: ?_Insert@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@@Z @ 0x000DEAA0
// sp-match: ?_Lrotate@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@@Z @ 0x000DE720
// sp-match: ?_Rrotate@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@@Z @ 0x000DE530
// sp-match: ?_Lbound@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABVRWSGUID@RWS@@@Z @ 0x000DE780
// sp-match: ?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@2@D@Z @ 0x000DE8C0
// sp-match: ?_Inc@const_iterator@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAEXXZ @ 0x000DE590
// sp-match: ?_Ubound@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@ABVRWSGUID@RWS@@@Z @ 0x000DE800
// sp-match: ?_Dec@const_iterator@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@QAEXXZ @ 0x000DE5F0
// sp-match: ??0?$map@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@@std@@QAE@XZ @ 0x000DF270
// sp-match: ?_Buynode@?$_Tree@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@$0A@@std@@@2@XZ @ 0x000DE920
// sp-match: ??0out_of_range@std@@QAE@ABV01@@Z @ 0x000DF060
// sp-match: ??1?$map@VRWSGUID@RWS@@PAVCAttributeHandler@2@URWSGUIDless@?A0x737baa82@2@V?$allocator@U?$pair@$$CBVRWSGUID@RWS@@PAVCAttributeHandler@2@@std@@@std@@@std@@QAE@XZ @ 0x000DF200

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleAttributes@CAttributeHandler@RWS@@UAEXABVCAttributePacket@2@@Z (folded into 0x15FB30)
void RWS::CAttributeHandler::HandleAttributes(class RWS::CAttributePacket const & arg_0)
{
}

// The command's id (out of line in the framework; /OPT:ICF folded it into the
// game's getter of the word at +4, 0x1E3480).
// sp-match: ?GetCommandId@CAttributeCommand@RWS@@QBEIXZ @ 0x000DE3D0
RwUInt32 RWS::CAttributeCommand::GetCommandId() const
{
    return chunk_.type_;
}
