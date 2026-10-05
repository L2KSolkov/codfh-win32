// RenderWare Studio's event handler (the game framework's
// framework/core/eventhandler/ceventhandler.cpp), without the event
// visualization: the event ids, the registry of messages and the links of
// event handlers to them (with their free lists), sending, and the
// RpAtomicToEventHandler plugin. The Studio sources' IsLinked,
// GetLinkedPriority, the Replace and SendMsgToEventHandler functions and
// RegisterToDeleteEventHandlers are not in the image (unreferenced); the
// empty ~CEventId is folded (config/aliases.txt).

#include <string.h>

#include "rw/ostypes.h"
#include "rw/bamemory.h"
#include "rw/rpatomic.h"
#include "rws/ceventhandler.h"
#include "rws/memoryhandler.h"
#include "rws/strfunc.h"
#include "rws/idfromstring.h"
#include "rws/atomiceventhandlerplugin.h"
// Its data definitions (PLAN M5), in the image's address order: the event names
// are named constants (the image has them before the literals, in this order).
// 0x003DA99C
extern const RwChar iMsgDeleteEventHandler_name[] = "iMsgDeleteEventHandler";
// 0x003DA9B4
extern const RwChar iMsgDeleteEntity_name[] = "iMsgDeleteEntity";
// 0x003DA9C8
extern const RwChar iMsgOnDeleteEntity_name[] = "iMsgOnDeleteEntity";
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?iMsgDeleteEventHandler_name@@3QBDB @ 0x003DA99C
// match: ?iMsgDeleteEntity_name@@3QBDB @ 0x003DA9B4
// match: ?iMsgOnDeleteEntity_name@@3QBDB @ 0x003DA9C8
// match: ??_C@_0P@DIJDMCLI@CEventHandler?$CK?$AA@ @ 0x003DA9DC
// match: __ehhandler$?RegisterMsg@CEventHandler@RWS@@SAXAAVCEventId@2@PBD1@Z>1>8 @ 0x0041D7F4
// match: __ehhandler$?RegisterMsg@CEventHandler@RWS@@SAXAAVCEventId@2@PBD1@Z>1 @ 0x0041D7FC
// match: .CRT$XCU+0 @ 0x004270A8
// match: .CRT$XCU+4 @ 0x004270AC
// match: .CRT$XCU+8 @ 0x004270B0
// match: .CRT$XCU+12 @ 0x004270B4

// match: _$E1 @ 0x0030B860
// match: _$E2 @ 0x0030E650
// match: _$E4 @ 0x0030B880
// match: _$E5 @ 0x0030E660
// match: _$E7 @ 0x0030B8A0
// match: _$E8 @ 0x0030E670
// match: _$E10 @ 0x0030B8C0

namespace
{
   // The free lists' memory hint: rwMEMHINTDUR_GLOBAL with the id 0x4252
   // (not an address).
   const RwUInt32 uEVENTHANDLER_MEMHINT = rwMEMHINTDUR_GLOBAL | 0x4252;
}

namespace RWS
{
   CEventId iMsgDeleteEventHandler;
   CEventId iMsgDeleteEntity;
   CEventId iMsgOnDeleteEntity;

   // Head of the registry.
   static CRegisteredMsgs pRMsgs;

   RwFreeList *CLinkedMsg::pFreeList;
   RwFreeList *CRegisteredMsgs::pFreeList = 0;
}

// match: ??0CEventId@RWS@@QAE@XZ @ 0x0012DDB0
RWS::CEventId::CEventId(void) : p_msgrec(0), m_linked_count(0), m_registered_count(0)
   {
   }

// match: ?Inc_registered_count@CEventId@RWS@@QAEXXZ @ 0x0012DDE0
void RWS::CEventId::Inc_registered_count(void)
   {
      p_msgrec->Inc_registered_count();
      m_registered_count++;
   }

// match: ?Dec_registered_count@CEventId@RWS@@QAEXXZ @ 0x0012DE20
void RWS::CEventId::Dec_registered_count(void)
   {
      p_msgrec->Dec_registered_count();
      m_registered_count--;

      if (m_registered_count == 0)
      {
         p_msgrec = 0;
      }
   }

// match: ?Inc_linked_count@CEventId@RWS@@QAEXXZ @ 0x0012DE70
void RWS::CEventId::Inc_linked_count(void)
   {
      m_linked_count++;
   }

// match: ?Dec_linked_count@CEventId@RWS@@QAEXXZ @ 0x0012DE90
void RWS::CEventId::Dec_linked_count(void)
   {
      m_linked_count--;
   }

// match: ??4CEventId@RWS@@QAEAAV01@PBVCRegisteredMsgs@1@@Z @ 0x0012DEB0
RWS::CEventId &RWS::CEventId::operator = (const CRegisteredMsgs *rhs)
   {
      if (p_msgrec != rhs)
      {
         p_msgrec = const_cast<CRegisteredMsgs*>(rhs);
      }

      return (*this);
   }

// match: ?Open@CEventHandler@RWS@@SAXII@Z @ 0x0012DEE0
void RWS::CEventHandler::Open(RwUInt32 linkBlockSize, RwUInt32 regBlockSize)
   {
      CLinkedMsg::InitMemHandler(linkBlockSize);
      CRegisteredMsgs::InitMemHandler(regBlockSize);

      RegisterMsg (iMsgDeleteEventHandler, iMsgDeleteEventHandler_name, 0);
      RegisterMsg (iMsgDeleteEntity, iMsgDeleteEntity_name, 0);
      RegisterMsg (iMsgOnDeleteEntity, iMsgOnDeleteEntity_name, "CEventHandler*");
   }

// match: ?Close@CEventHandler@RWS@@SAXXZ @ 0x0012DF40
void RWS::CEventHandler::Close(void)
   {
      UnRegisterMsg ( iMsgDeleteEventHandler );
      UnRegisterMsg ( iMsgDeleteEntity );
      UnRegisterMsg ( iMsgOnDeleteEntity );

      CRegisteredMsgs::CloseMemHandler();
      CLinkedMsg::CloseMemHandler();
   }

// match: ?StrIdentical@?A0xb9ca1959@@YAHIIPBD0@Z @ 0x0012E390
namespace
{
   RwBool StrIdentical(const RwUInt32 uiId1, RwUInt32 uiId2, const RwChar *ps1, const RwChar *ps2)
   {
      if (uiId1 != uiId2) return (FALSE);

      while (*ps1 != 0 && *ps2 != 0)
      {
         if (*ps1 != *ps2) return (FALSE);

         ps1++;
         ps2++;
      }

      if (*ps1 != *ps2) return (FALSE);

      return (TRUE);
   }
}

// match: ?RegisterMsg@CEventHandler@RWS@@SAXAAVCEventId@2@PBD1@Z @ 0x0012DF80
// match: __ehhandler$?RegisterMsg@CEventHandler@RWS@@SAXAAVCEventId@2@PBD1@Z-0xB @ 0x003016B0
// match: __ehhandler$?RegisterMsg@CEventHandler@RWS@@SAXAAVCEventId@2@PBD1@Z @ 0x003016BB
void RWS::CEventHandler::RegisterMsg(
                          CEventId &Id,
                          const RwChar *p_msgname,
                          const RwChar *p_formatstring)
   {
      if (!p_msgname || p_msgname[0] == 0)
      {
         Id = ERROR_NOT_A_VALID_MESSAGE_ID;
         return;
      }

      RwUInt32 ui_msgname = GenerateUIntIdFromString(p_msgname);
      RwUInt32 ui_format = GenerateUIntIdFromString(p_formatstring);

      if (Id.Get_registered_count()>0)
      {
         if (!StrIdentical (Id->ui_msgname, ui_msgname, Id->p_msgname, p_msgname))
         {
         }
         else
         {
            if (Id->p_format != 0 && p_formatstring == 0)
            {
            }
            else if (Id->p_format == 0 && p_formatstring != 0)
            {
               CRegisteredMsgs *pRMsg = Id;
               pRMsg->p_format = static_cast<RwChar *>(::RWS_OP_NEW( strlen (p_formatstring) + 1));
               strcpy (pRMsg->p_format, p_formatstring);
            }
            else if (Id->p_format != 0)
            {
               if (StrIdentical(Id->ui_format, ui_format, Id->p_format, p_formatstring))
               {
                  Id.Inc_registered_count();

                  return;
               }
            }
         }
      }

      CRegisteredMsgs *pRMsg = pRMsgs.p_next;
      while (pRMsg)
      {
         if (pRMsg->p_msgname != 0)
         {
            RwBool samestring = StrIdentical (pRMsg->ui_msgname, ui_msgname, pRMsg->p_msgname, p_msgname);
            if (samestring)
            {
               if (pRMsg->p_format != 0 && p_formatstring == 0)
               {
               }
               else if (pRMsg->p_format == 0 && p_formatstring != 0)
               {
                  pRMsg->p_format = static_cast<RwChar *>(::RWS_OP_NEW( strlen (p_formatstring) + 1));
                  strcpy (pRMsg->p_format, p_formatstring);
                  pRMsg->ui_format = ui_format;
               }
               else if (pRMsg->p_format != 0
                  && !StrIdentical(pRMsg->ui_format, ui_format, pRMsg->p_format, p_formatstring))
               {
               }

               Id = pRMsg;

               Id.Inc_registered_count();

               return;
            }
         }

         pRMsg = pRMsg->p_next;
      }

      pRMsg = new CRegisteredMsgs;

      CRegisteredMsgs *p_next = pRMsgs.p_next;

      pRMsg->p_next = pRMsgs.p_next;

      if (p_next) p_next->p_prev = pRMsg;

      pRMsg->p_prev = &pRMsgs;

      pRMsgs.p_next = pRMsg;

      pRMsg->p_msgname = static_cast<RwChar *>(::RWS_OP_NEW( strlen (p_msgname) + 1));
      strcpy (pRMsg->p_msgname, p_msgname);

      if (p_formatstring)
      {
         pRMsg->p_format = static_cast<RwChar *>(::RWS_OP_NEW( strlen (p_formatstring) + 1));
         strcpy (pRMsg->p_format, p_formatstring);
      }
      else
      {
         pRMsg->p_format = 0;
      }

      pRMsg->ui_format = ui_format;
      pRMsg->ui_msgname = ui_msgname;

      Id = pRMsg;

      Id.Inc_registered_count();
   }

// match: ?UnRegisterMsg@CEventHandler@RWS@@SAXAAVCEventId@2@@Z @ 0x0012E400
void RWS::CEventHandler::UnRegisterMsg(CEventId &Id)
   {
      if (Id != ERROR_NOT_A_VALID_MESSAGE_ID)
      {
         CRegisteredMsgs *pRMsg = Id;

         if (Id.Get_registered_count() == 0)
         {
            Id = ERROR_NOT_A_VALID_MESSAGE_ID;
            return;
         }

         Id.Dec_registered_count();

         // The Studio sources' assertion (compiled out; the empty test
         // leaves no code but shifts the registers the rest are loaded into).
         if (pRMsg->iCountRegistered<0)
         {
         }

         if (pRMsg->iCountRegistered == 0)
         {
            CLinkedMsg *pErm = pRMsg->Erm.p_next;
            if (pErm)
            {
               return;
            }

            operator delete (pRMsg->p_msgname);
            pRMsg->p_msgname = 0;

            operator delete (pRMsg->p_format);
            pRMsg->p_format = 0;

            CRegisteredMsgs *p_next = pRMsg->p_next;
            CRegisteredMsgs *p_prev = pRMsg->p_prev;

            if (p_prev) p_prev->p_next = p_next;
            if (p_next) p_next->p_prev = p_prev;

            Id = ERROR_NOT_A_VALID_MESSAGE_ID;

            delete pRMsg;
         }
      }
   }

// match: ??1CEventHandler@RWS@@UAE@XZ @ 0x0012E4F0
RWS::CEventHandler::~CEventHandler(void)
   {
      CMsg Msg(iMsgOnDeleteEntity, static_cast<CEventHandler*>(this));
      SendMsg(Msg);

      UnLinkMsg(iMsgDeleteEventHandler);
      UnLinkMsg(iMsgDeleteEntity);
   }

// match: ?LinkMsg@CEventHandler@RWS@@QAEXAAVCEventId@2@PBDG@Z @ 0x0012E550
void RWS::CEventHandler::LinkMsg(CEventId &Id,
                               const RwChar *p_formatstring,
                               RwUInt16 priority)
   {
      if (Id != ERROR_NOT_A_VALID_MESSAGE_ID)
      {
         LinkMsgToEventHandler(this, Id, p_formatstring, priority);
      }
   }

// match: ?UnLinkMsg@CEventHandler@RWS@@QAEXAAVCEventId@2@@Z @ 0x0012E590
void RWS::CEventHandler::UnLinkMsg(CEventId &Id)
   {
      if (Id == ERROR_NOT_A_VALID_MESSAGE_ID)
      {
         return;
      }

      if (Id.Get_linked_count() == 0)
      {
         return;
      }

      CRegisteredMsgs *pRMsg = Id;

      if (pRMsg->p_msgname != 0)
      {
         CLinkedMsg *pErm = &pRMsg->Erm;

         while (pErm != 0)
         {
            CLinkedMsg *p_next_Erm = pErm->p_next;

            if (pErm->pCEventHandler == this )
            {
               Id.Dec_linked_count();

               pErm->iCountLinked -= 1;

               // The Studio sources' assertion (compiled out, as in
               // UnRegisterMsg).
               if (pErm->iCountLinked < 0)
               {
               }

               if (pErm->iCountLinked == 0)
               {
                  if (pRMsg->HandlingEvent)
                  {
                     pErm->pCEventHandler = 0;
                     pRMsg->PendingUnlink = TRUE;
                  }
                  else
                  {
                     CLinkedMsg *p_prev_Erm = pErm->p_prev;

                     if (p_prev_Erm) p_prev_Erm->p_next = p_next_Erm;
                     if (p_next_Erm) p_next_Erm->p_prev = p_prev_Erm;

                     delete pErm;

                     return;
                  }
               }

               break;
            }

            pErm = p_next_Erm;
         }
      }
   }

// match: ?DeleteEventHandlers@CEventHandler@RWS@@SAXPBVCMsg@2@@Z @ 0x0012E680
void RWS::CEventHandler::DeleteEventHandlers(
                              const CMsg *p_Msg)
   {
      CRegisteredMsgs *pRMsg = p_Msg->Id.p_msgrec;

      if (pRMsg != ERROR_NOT_A_VALID_MESSAGE_ID)
      {
         CLinkedMsg *pErm = pRMsg->Erm.p_next;

         while (pErm != 0)
         {
            delete pErm->pCEventHandler;

            pErm = pRMsg->Erm.p_next;
         }
      }
   }

// match: ?DeleteEventHandlers@CEventHandler@RWS@@SAXABVCEventId@2@@Z @ 0x0012E6E0
void RWS::CEventHandler::DeleteEventHandlers(const CEventId &Id)
   {
      if (Id != ERROR_NOT_A_VALID_MESSAGE_ID)
      {
         CMsg iMsg(Id.operator CRegisteredMsgs*());

         DeleteEventHandlers (&iMsg);
      }
   }

// match: ?LinkMsgToEventHandler@CEventHandler@RWS@@SAHPAV12@AAVCEventId@2@PBDG@Z @ 0x0012E720
RwBool RWS::CEventHandler::LinkMsgToEventHandler(
                        CEventHandler *pCEventHandler,
                        CEventId &Id,
                        const RwChar *p_formatstring,
                        RwUInt16 priority)
   {
      if (Id != ERROR_NOT_A_VALID_MESSAGE_ID)
      {
         CRegisteredMsgs *pRMsg = Id;

         // The Studio sources' trace (compiled out, as in UnRegisterMsg).
         if (Id.Get_linked_count()>0)
         {
         }

         Id.Inc_linked_count();

         CLinkedMsg *pErm = Id->Erm.p_next;

         while (pErm != 0)
         {
            if (pErm->pCEventHandler == pCEventHandler)
            {
               pErm->iCountLinked += 1;

               return ( TRUE );
            }

            pErm = pErm->p_next;
         }

         if (p_formatstring)
         {
            if (pRMsg->p_format == 0)
            {
            }
            else
            {
               RwUInt32 ui_format = GenerateUIntIdFromString(p_formatstring);

               if (!StrIdentical(pRMsg->ui_format, ui_format, pRMsg->p_format, p_formatstring))
               {
                  return (FALSE);
               }
            }
         }

         CLinkedMsg *pNewErm = new CLinkedMsg(pCEventHandler, priority);

         if (!pNewErm)
         {
            return (FALSE);
         }

         CLinkedMsg *pheadErm = const_cast<CLinkedMsg*>(&Id->Erm);
         CLinkedMsg *ptailErm = Id->Erm.p_next;

         while (ptailErm)
         {
            if ( pheadErm->m_priority >= priority
            &&  ptailErm->m_priority <= priority )
            {
               pheadErm->p_next = pNewErm;
               pNewErm->p_prev = pheadErm;
               ptailErm->p_prev = pNewErm;
               pNewErm->p_next = ptailErm;

               return (TRUE);
            }

            pheadErm = ptailErm;
            ptailErm = ptailErm->p_next;
         }

         pheadErm->p_next = pNewErm;
         pNewErm->p_prev = pheadErm;
      }

      return (TRUE);
   }

// match: ?_SendMsg@RWS@@YAHAAVCMsg@1@@Z @ 0x0012E8D0
RwBool RWS::_SendMsg(CMsg &p_Msg)
   {
      CLinkedMsg *pErm = p_Msg.Id.p_msgrec->Erm.p_next;

      if (!pErm)
      {
         return ( FALSE );
      }

      p_Msg.Id.p_msgrec->HandlingEvent = TRUE;

      do
      {
         if (pErm->pCEventHandler && pErm->pCEventHandler->m_Active)
         {
            pErm->pCEventHandler->HandleEvents(p_Msg);
         }

         pErm = pErm->p_next;
      } while (pErm != 0);

      p_Msg.Id.p_msgrec->HandlingEvent = FALSE;

      if (p_Msg.Id.p_msgrec->PendingUnlink)
      {
         CEventHandler::ProcessPendingUnlinks(p_Msg.Id.p_msgrec->Erm.p_next);
         p_Msg.Id.p_msgrec->PendingUnlink = FALSE;
      }

      return ( TRUE );
   }

// match: ?ProcessPendingUnlinks@CEventHandler@RWS@@SAXPAVCLinkedMsg@2@@Z @ 0x0012E970
void RWS::CEventHandler::ProcessPendingUnlinks(CLinkedMsg *pErm)
   {
      while (pErm != 0)
      {
         CLinkedMsg *p_next_Erm = pErm->p_next;

         if (pErm->pCEventHandler == 0 )
         {
              CLinkedMsg *p_prev_Erm = pErm->p_prev;

              if (p_prev_Erm) p_prev_Erm->p_next = p_next_Erm;
              if (p_next_Erm) p_next_Erm->p_prev = p_prev_Erm;

              delete pErm;
         }

         pErm = p_next_Erm;
      }
   }

// match: ?InitMemHandler@CLinkedMsg@RWS@@SAXI@Z @ 0x0012E9E0
void RWS::CLinkedMsg::InitMemHandler(RwUInt32 blockSize)
   {
      if (!blockSize)
      {
         blockSize = 20;
      }

      pFreeList = RwFreeListCreate(sizeof(CLinkedMsg), blockSize, 16, uEVENTHANDLER_MEMHINT);
   }

// match: ?CloseMemHandler@CLinkedMsg@RWS@@SAXXZ @ 0x0012EA10
void RWS::CLinkedMsg::CloseMemHandler(void)
   {
      if (pFreeList)
      {
         RwFreeListDestroy(pFreeList);
         pFreeList = 0;
      }
   }

// match: ??2CLinkedMsg@RWS@@SAPAXI@Z @ 0x0012EA40
void *RWS::CLinkedMsg::operator new(size_t size)
   {
      return (RwFreeListAlloc(pFreeList, uEVENTHANDLER_MEMHINT));
   }

// match: ??3CLinkedMsg@RWS@@SAXPAX@Z @ 0x0012EA60
void RWS::CLinkedMsg::operator delete(void *pObj)
   {
      if (pObj)
      {
         RwFreeListFree(pFreeList, pObj);
      }
   }

// match: ?InitMemHandler@CRegisteredMsgs@RWS@@SAXI@Z @ 0x0012EA80
void RWS::CRegisteredMsgs::InitMemHandler(RwUInt32 blockSize)
   {
      if (!blockSize)
      {
         blockSize = 10;
      }

      pFreeList = RwFreeListCreate(sizeof(CRegisteredMsgs), blockSize, 16, uEVENTHANDLER_MEMHINT);
   }

// match: ?CloseMemHandler@CRegisteredMsgs@RWS@@SAXXZ @ 0x0012EAB0
void RWS::CRegisteredMsgs::CloseMemHandler(void)
   {
      if (pFreeList)
      {
         RwFreeListDestroy(pFreeList);
         pFreeList = 0;
      }
   }

// match: ??2CRegisteredMsgs@RWS@@SAPAXI@Z @ 0x0012EAE0
void *RWS::CRegisteredMsgs::operator new(size_t size)
   {
      return (RwFreeListAlloc(pFreeList, uEVENTHANDLER_MEMHINT));
   }

// match: ??3CRegisteredMsgs@RWS@@SAXPAX@Z @ 0x0012EB00
void RWS::CRegisteredMsgs::operator delete(void *pObj)
   {
      if (pObj)
      {
         RwFreeListFree(pFreeList, pObj);
      }
   }

namespace RWS
{
   namespace RpAtomicToEventHandler
   {
      namespace
      {
         RwUInt32 iPlugin_Offset = 0;

         inline EventHandlerPluginData* GetPluginData( RpAtomic& atomic )
         {
            const RwUInt32 baseAddr = reinterpret_cast<RwUInt32>(&atomic);
            const RwUInt32 pluginAddr = baseAddr + iPlugin_Offset;

            return (reinterpret_cast<EventHandlerPluginData*>(pluginAddr));
         }
      }
   }
}

// match: ?Plugin_Constructor@?A0xb9ca1959@RpAtomicToEventHandler@RWS@@YAPAXPAXHH@Z @ 0x0012EB20
namespace RWS
{
   namespace RpAtomicToEventHandler
   {
      namespace
      {
         void* Plugin_Constructor(void* pObject, RwInt32 offsetInObject, RwInt32 sizeInObject)
         {
            EventHandlerPluginData& pluginData = *GetPluginData(*reinterpret_cast<RpAtomic*>(pObject));

            pluginData.m_pEventHandler = 0;

            return (pObject);
         }
      }
   }
}

// match: ?Plugin_Copy@?A0xb9ca1959@RpAtomicToEventHandler@RWS@@YAPAXPAXPBXHH@Z @ 0x0012EB50
namespace RWS
{
   namespace RpAtomicToEventHandler
   {
      namespace
      {
         void* Plugin_Copy(void* pDstObject, const void* pSrcObject, RwInt32 offset, RwInt32 size)
         {
            EventHandlerPluginData& srcData = *GetPluginData(
               *const_cast<RpAtomic*>(reinterpret_cast<const RpAtomic*>(pSrcObject)));

            EventHandlerPluginData& dstData = *GetPluginData(*reinterpret_cast<RpAtomic*>(pDstObject));

            dstData = srcData;

            return (pDstObject);
         }
      }
   }
}

// CRegisteredMsgs's constructor (inline in rws/ceventhandler.h), emitted for
// RegisterMsg's new. The static ids' and the registry head's dynamic
// initializers are left unplaced, like the other units' static initializers.
// match: ??0CRegisteredMsgs@RWS@@QAE@XZ @ 0x0012E300

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??1CEventId@RWS@@QAE@XZ (folded into 0x1E41C0)
RWS::CEventId::~CEventId()
{
}

// match: ?PluginAttach@RpAtomicToEventHandler@RWS@@YAHXZ @ 0x0012EBA0
RwBool RWS::RpAtomicToEventHandler::PluginAttach(void)
      {
         iPlugin_Offset = RpAtomicRegisterPlugin(
            sizeof(EventHandlerPluginData),
            MAKECHUNKID(rwVENDORID_CRITERIONRM, PluginID),
            Plugin_Constructor,
            0,
            Plugin_Copy
            );

         return (0 != iPlugin_Offset);
      }
