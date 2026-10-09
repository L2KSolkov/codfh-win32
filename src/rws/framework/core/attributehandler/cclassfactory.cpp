// RenderWare Studio's class factory (the game framework's
// framework/core/attributehandler/cclassfactory.cpp): the registry of the
// behaviour classes by name, which RWS_REGISTERCLASS's registrars fill and
// MakeNew creates from. ClassIsRegistered is only used by the (compiled
// out) assertions and is not in the image.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/classfactorymap.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?GetNameToPtrMap@?A0x9c13616b@@YAAAV?$map@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@@std@@XZ>1>8 @ 0x0041D664
// match: __ehhandler$?GetNameToPtrMap@?A0x9c13616b@@YAAAV?$map@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@@std@@XZ>1 @ 0x0041D66C
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@@Z>1>8 @ 0x0041D688
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@@Z>1 @ 0x0041D690
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@D@Z>1>8 @ 0x0041D6AC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@D@Z>1>16>16 @ 0x0041D6BC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@D@Z>1>16 @ 0x0041D6CC
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@D@Z>1 @ 0x0041D6E0
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1>8 @ 0x0041D6FC
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z>1 @ 0x0041D704
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@XZ>1>8 @ 0x0041D720
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@XZ>1>16>16 @ 0x0041D730
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@XZ>1>16 @ 0x0041D740
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@XZ>1 @ 0x0041D754

// match: _$E2 @ 0x0030E620
// match: ?GetNameToPtrMap@?A0x9c13616b@@YAAAV?$map@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@@std@@XZ @ 0x0012BC90
// match: __ehhandler$?GetNameToPtrMap@?A0x9c13616b@@YAAAV?$map@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@@std@@XZ-0xE @ 0x00301620
// match: __ehhandler$?GetNameToPtrMap@?A0x9c13616b@@YAAAV?$map@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@@std@@XZ @ 0x0030162E
// sp-match: ?GetNameToPtrMap@?A0x9c13616b@@YAAAV?$map@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@@std@@XZ @ 0x000DFB30
// The name map's comparison, which single player calls out of line (MP expands it):
// sp-match: ??Rcstrless@?A0x9c13616b@@QBE_NPBD0@Z @ 0x000DF2C0

namespace
{
   NameToPtrMap& GetNameToPtrMap()
   {
      static NameToPtrMap theNameToPtrMap;
      return theNameToPtrMap;
   }
}

// match: ?GetRegisteredClassSize@CClassFactory@RWS@@YAIPBD@Z @ 0x0012BD20
// sp-match: ?GetRegisteredClassSize@CClassFactory@RWS@@YAIPBD@Z @ 0x000DFBC0
size_t RWS::CClassFactory::GetRegisteredClassSize(const RwChar* pClassName)
      {
         NameToPtrMap::iterator foundIt = GetNameToPtrMap().find(pClassName);

         SClassInfo * pclassInfo = GetNameToPtrMap().end() != foundIt ? (*foundIt).second : 0;

         if (!pclassInfo)
            return (0);

         return (pclassInfo->size);
      }

// match: ?RegisterClass@CClassFactory@RWS@@YAXPBDP6APAVCAttributeHandler@2@ABVCAttributePacket@2@@ZIH@Z @ 0x0012BDA0
// sp-match: ?RegisterClass@CClassFactory@RWS@@YAXPBDP6APAVCAttributeHandler@2@ABVCAttributePacket@2@@ZIH@Z @ 0x000DFC00
void RWS::CClassFactory::RegisterClass(const RwChar* pClassName, MakeNewPtr makeNewFn, size_t size, RwBool UseLinearMemoryManager)
      {
         SClassInfo* pClassInfo = (SClassInfo *)new(SClassInfo);

         pClassInfo->MakeNewFunc = makeNewFn;
         pClassInfo->size = 0;

         if (UseLinearMemoryManager)
         {
            pClassInfo->size = size;

            if (size % m_AlignmentSize)
               pClassInfo->size += m_AlignmentSize - (size % m_AlignmentSize);
         }

         GetNameToPtrMap().insert(std::make_pair(pClassName, pClassInfo));
      }

// match: ?MakeNew@CClassFactory@RWS@@YAPAVCAttributeHandler@2@PBDABVCAttributePacket@2@@Z @ 0x0012BE50
// sp-match: ?MakeNew@CClassFactory@RWS@@YAPAVCAttributeHandler@2@PBDABVCAttributePacket@2@@Z @ 0x000DFC60
RWS::CAttributeHandler *RWS::CClassFactory::MakeNew(const RwChar* pClassName, const CAttributePacket& rAttr)
      {
         NameToPtrMap::iterator foundIt = GetNameToPtrMap().find(pClassName);

         SClassInfo * pclassInfo = GetNameToPtrMap().end() != foundIt ? (*foundIt).second : 0;

         if (pclassInfo && pclassInfo->MakeNewFunc)
         {
            CAttributeHandler *pCAttributeHandler = pclassInfo->MakeNewFunc(rAttr);

            if (pCAttributeHandler)
            {
               pCAttributeHandler->HandleAttributes(rAttr);
            }

            return (pCAttributeHandler);
         }

         return (0);
      }

// match: ??0CRegistrar@CClassFactory@RWS@@QAE@PBDP6APAVCAttributeHandler@2@ABVCAttributePacket@2@@ZIH@Z @ 0x0012BEF0
// sp-match: ??0CRegistrar@CClassFactory@RWS@@QAE@PBDP6APAVCAttributeHandler@2@ABVCAttributePacket@2@@ZIH@Z @ 0x000DFCC0
RWS::CClassFactory::CRegistrar::CRegistrar(const RwChar* pClassName, MakeNewPtr makeNewFn, size_t size, RwBool UseLinearMemoryManager)
      {
         RegisterClass(pClassName, makeNewFn, size, UseLinearMemoryManager);
      }

// match: ??1CRegistrar@CClassFactory@RWS@@QAE@XZ @ 0x0012BF20
// sp-match: ??1CRegistrar@CClassFactory@RWS@@QAE@XZ @ 0x000DFCF0
RWS::CClassFactory::CRegistrar::~CRegistrar()
      {
         NameToPtrMap::iterator it = GetNameToPtrMap().begin();

         while (it != GetNameToPtrMap().end())
         {
            delete (*it).second;
            it++;
         }

         GetNameToPtrMap().clear();
      }

// The map's instantiations (the XDK's Dinkumware <map>/<xtree>), in the
// image's order. _Lrotate, _Rrotate and const_iterator::_Inc are identical
// to another map's (/OPT:ICF) and are aliased there.
// match: ??1?$map@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@@std@@QAE@XZ @ 0x0012BD00
// match: ?insert@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@_N@2@ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@@Z @ 0x0012BFC0
// match: ?clear@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAEXXZ @ 0x0012C180
// match: ?find@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@ABQBD@Z @ 0x0012C1E0
// match: ?_Erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@@Z @ 0x0012C290
// match: ?_Insert@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@@Z @ 0x0012C2E0
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@@Z-0x8 @ 0x00301640
// match: __ehhandler$?_Insert@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@@Z @ 0x00301648
// match: ?_Tidy@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEXXZ @ 0x0012C630
// match: ?erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x0012C6B0
// match: ?_Init@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEXXZ @ 0x0012C780
// match: ?_Lbound@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@ABQBD@Z @ 0x0012C7F0
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@D@Z @ 0x0012C870
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@D@Z @ 0x00301660
// match: ?erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x0012C940
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z-0x8 @ 0x00301670
// match: __ehhandler$?erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x00301678
// match: ?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@XZ @ 0x0012CEC0
// match: __ehhandler$?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@XZ @ 0x00301690
// match: ?_Dec@const_iterator@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAEXXZ @ 0x0012CFE0
// sp-match: ?_Dec@const_iterator@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAEXXZ @ 0x000E1C80
// sp-match: ?insert@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AU?$pair@Viterator@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@_N@2@ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@@Z @ 0x000DFA00
// sp-match: ?find@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@ABQBD@Z @ 0x000DF470
// sp-match: ?_Lbound@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IBEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@ABQBD@Z @ 0x000DF320
// sp-match: ?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@XZ @ 0x000DF430
// sp-match: ?_Buynode@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@PAU342@00ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@D@Z @ 0x000E1DA0
// sp-match: ?_Erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAEXPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@@Z @ 0x000DF3F0
// sp-match: ?erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@0@Z @ 0x000DF940
// sp-match: ?erase@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x000DF4D0
// sp-match: ?_Insert@?$_Tree@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@std@@IAE?AViterator@12@_NPAU_Node@?$_Tree_nod@V?$_Tmap_traits@PBDPAUSClassInfo@?A0x9c13616b@@Ucstrless@2@V?$allocator@U?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@std@@@std@@$0A@@std@@@2@ABU?$pair@QBDPAUSClassInfo@?A0x9c13616b@@@2@@Z @ 0x000DF790
