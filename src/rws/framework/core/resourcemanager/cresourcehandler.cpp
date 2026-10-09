// RenderWare Studio's resource handlers (the game framework's
// framework/core/resourcemanager/cresourcehandler.cpp): every handler adds
// itself to a list on construction, and the resource manager finds the one
// for a type through it.

#include "rw/ostypes.h"
#include "rws/cresourcehandler.h"
#include "rws/resourcehandlerlist.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7CResourceHandler@RWS@@6B@ @ 0x003DA9EC
// match: __ehhandler$?GetCResourceHandlerList@?A0xf2ed2e68@RWS@@YAAAV?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@XZ>1>8 @ 0x0041D860
// match: __ehhandler$?GetCResourceHandlerList@?A0xf2ed2e68@RWS@@YAAAV?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@XZ>1 @ 0x0041D868
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@XZ>1>8 @ 0x0041D884
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@XZ>1>16>16 @ 0x0041D894
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@XZ>1>16 @ 0x0041D8A4
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@XZ>1 @ 0x0041D8B8
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@PAU342@0ABQAVCResourceHandler@RWS@@@Z>1>8 @ 0x0041D8D4
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@PAU342@0ABQAVCResourceHandler@RWS@@@Z>1>16>16 @ 0x0041D8E4
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@PAU342@0ABQAVCResourceHandler@RWS@@@Z>1>16 @ 0x0041D8F4
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@PAU342@0ABQAVCResourceHandler@RWS@@@Z>1 @ 0x0041D908
// match: __ehhandler$?_Incsize@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEXI@Z>1>8 @ 0x0041D924
// match: __ehhandler$?_Incsize@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEXI@Z>1 @ 0x0041D92C

// match: _$E2 @ 0x0030E690
// match: ?GetCResourceHandlerList@?A0xf2ed2e68@RWS@@YAAAV?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@XZ @ 0x0012F200
// match: __ehhandler$?GetCResourceHandlerList@?A0xf2ed2e68@RWS@@YAAAV?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@XZ-0xE @ 0x00301710
// match: __ehhandler$?GetCResourceHandlerList@?A0xf2ed2e68@RWS@@YAAAV?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@XZ @ 0x0030171E
// sp-match: ?GetCResourceHandlerList@?A0xf2ed2e68@RWS@@YAAAV?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@XZ @ 0x000E1070

namespace RWS
{
   namespace
   {
      CResourceHandlerList& GetCResourceHandlerList(void)
      {
         static CResourceHandlerList the_CResourceHandlerList;

         return (the_CResourceHandlerList);
      }
   }
}

// match: ??0CResourceHandler@RWS@@QAE@XZ @ 0x0012F280
// sp-match: ??0CResourceHandler@RWS@@QAE@XZ @ 0x000E1270
RWS::CResourceHandler::CResourceHandler(void)
   {
      GetCResourceHandlerList().push_front(this);
   }

// match: ??_GCResourceHandler@RWS@@UAEPAXI@Z @ 0x0012F2D0
// match: ??1CResourceHandler@RWS@@UAE@XZ @ 0x0012F300
// sp-match: ??1CResourceHandler@RWS@@UAE@XZ @ 0x000E10E0
// sp-match: ??_GCResourceHandler@RWS@@UAEPAXI@Z @ 0x000E11B0
RWS::CResourceHandler::~CResourceHandler(void)
   {
      GetCResourceHandlerList().remove(this);
   }

// match: ?FindHandler@CResourceHandler@RWS@@SAPAV12@QBD@Z @ 0x0012F330
// sp-match: ?FindHandler@CResourceHandler@RWS@@SAPAV12@QBD@Z @ 0x000E1100
RWS::CResourceHandler *RWS::CResourceHandler::FindHandler(const RwChar * const psType)
   {
      CResourceHandlerList::iterator it = GetCResourceHandlerList().begin();

      while (it != GetCResourceHandlerList().end())
      {
         if ((*it)->IsHandled(psType))
         {
            return (*it);
         }

         it++;
      }

      return ( 0 );
   }

// match: ?OpenAll@CResourceHandler@RWS@@SAXXZ @ 0x0012F3D0
// sp-match: ?OpenAll@CResourceHandler@RWS@@SAXXZ @ 0x000E1150
void RWS::CResourceHandler::OpenAll(void)
   {
      CResourceHandlerList::iterator it = GetCResourceHandlerList().begin();

      while (it != GetCResourceHandlerList().end())
      {
         (*it)->Open();

         it++;
      }
   }

// match: ?CloseAll@CResourceHandler@RWS@@SAXXZ @ 0x0012F460
// sp-match: ?CloseAll@CResourceHandler@RWS@@SAXXZ @ 0x000E1180
void RWS::CResourceHandler::CloseAll(void)
   {
      CResourceHandlerList::iterator it = GetCResourceHandlerList().begin();

      while (it != GetCResourceHandlerList().end())
      {
         (*it)->Close();

         it++;
      }
   }

// The handlers' list's instantiations (the XDK's Dinkumware <list>), in the
// image's order; clear is identical to another list's (/OPT:ICF) and is
// aliased there, and the empty Open and Close are folded into pDtor.
// match: ?remove@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@QAEXABQAVCResourceHandler@RWS@@@Z @ 0x0012F4F0
// match: ?_Insert@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@QAEXViterator@12@ABQAVCResourceHandler@RWS@@@Z @ 0x0012F570
// match: ?erase@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@QAE?AViterator@12@V312@@Z @ 0x0012F5D0
// match: ?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@PAU342@0ABQAVCResourceHandler@RWS@@@Z @ 0x0012F730
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@PAU342@0ABQAVCResourceHandler@RWS@@@Z @ 0x00301740
// match: ?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@XZ @ 0x0012F650
// match: __ehhandler$?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@XZ @ 0x00301730
// match: ?_Incsize@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEXI@Z @ 0x0012F7F0
// match: __ehhandler$?_Incsize@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEXI@Z-0x8 @ 0x00301750
// match: __ehhandler$?_Incsize@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEXI@Z @ 0x00301758
// sp-match: ?remove@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@QAEXABQAVCResourceHandler@RWS@@@Z @ 0x000E1020
// sp-match: ?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@XZ @ 0x000E0FD0
// sp-match: ?_Buynode@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEPAU_Node@?$_List_nod@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@2@PAU342@0ABQAVCResourceHandler@RWS@@@Z @ 0x000E0FF0
// sp-match: ?_Incsize@?$list@PAVCResourceHandler@RWS@@V?$allocator@PAVCResourceHandler@RWS@@@std@@@std@@IAEXI@Z @ 0x000E11D0
