/*
 * RWS::CEventHandler, copied from RenderWare Studio's game framework
 * (Studio\console\game_framework\source\framework\core\eventhandler\
 * ceventhandler.h), without the event visualization: CLinkedMsg,
 * CRegisteredMsgs and CEventId (the layouts ceventhandler.cpp's functions
 * use), CMsg, SendMsg, and CEventHandler's virtual functions in declaration
 * order (the destructor and the pure HandleEvents) and the one data member
 * the non-visualization build has, m_Active, which the inline constructor
 * sets. The image agrees: ??_7CEventHandler@RWS@@6B@ holds the scalar
 * deleting destructor and _purecall, and CDebugScript's constructor stores 1
 * at +0x4 of its CEventHandler (8 bytes).
 * The behaviours' units compare ids through CEventId's p_msgrec (the Studio
 * sources' pEventId) and a message's Id.p_msgrec (the sources' CMsg::Id is
 * the registered message itself; CMsgId wraps it), names kept from before
 * the event handler was recovered.
 */
#ifndef RWS_CEVENTHANDLER_H
#define RWS_CEVENTHANDLER_H

#include <stddef.h>

#include "rw/ostypes.h"
#include "rw/bamemory.h"

namespace RWS
{
   class CEventHandler;

   // A link of an event handler to a registered message (0x14 bytes): the
   // registered message's list of them is kept in priority order, highest
   // first, and they come from a free list of their own.
   class CLinkedMsg
   {
   public:
      CLinkedMsg(void) :
         p_next(0),
         p_prev(0),
         pCEventHandler(0),
         iCountLinked(1),
         m_priority(0xffff)
      {
      }

      CLinkedMsg(
               class CEventHandler *tpCEventHandler,
               RwUInt16 tpriority) :
         p_next(0),
         p_prev(0),
         pCEventHandler(tpCEventHandler),
         iCountLinked(1),
         m_priority(tpriority)
      {
      }

      CLinkedMsg *p_next;
      CLinkedMsg *p_prev;
      class CEventHandler *pCEventHandler;
      RwInt32 iCountLinked;
      RwUInt16 m_priority;

      void *operator new(size_t size);
      void operator delete(void *pObj);

      static void InitMemHandler(RwUInt32);
      static void CloseMemHandler(void);

   private:
      static RwFreeList *pFreeList;
   };

   // A registered message (0x38 bytes): the head of its links, its name and
   // format (with their hashes), its neighbours in the registry and its
   // reference count. A message is linked while Erm.p_next is set.
   class CRegisteredMsgs
   {
   public:
      CRegisteredMsgs(void) :
         p_msgname(0),
         p_format(0),
         p_next(0),
         p_prev(0),
         iCountRegistered(0),
         PendingUnlink(false),
         HandlingEvent(false)
      {
      }

      CLinkedMsg Erm;
      RwChar *p_msgname;
      RwChar *p_format;
      RwUInt32 ui_msgname;
      RwUInt32 ui_format;
      CRegisteredMsgs *p_next;
      CRegisteredMsgs *p_prev;
      RwInt32 iCountRegistered;

      void Inc_registered_count(void) {iCountRegistered++;}
      void Dec_registered_count(void) {iCountRegistered--;}

      RwBool PendingUnlink;
      RwBool HandlingEvent;

      void *operator new(size_t size);
      void operator delete(void *pObj);

      static void InitMemHandler(RwUInt32);
      static void CloseMemHandler(void);

   private:
      static RwFreeList *pFreeList;
   };

   // What an unregistered id holds.
   #define ERROR_NOT_A_VALID_MESSAGE_ID 0

   // An id is 8 bytes: the registered message and the id's link and
   // registration counts (ParticleEditor keeps three 8 apart). The
   // destructor is empty and out of line (pDtor, folded at 0x1E41C0;
   // ParticleEditor's destructor calls it for each).
   class CEventId
   {
   public:
      CEventId();
      ~CEventId();

      CEventId &operator= (const CRegisteredMsgs *rhs);

      operator CRegisteredMsgs*() const
      {
         return const_cast<CRegisteredMsgs*>(p_msgrec);
      }

      const CRegisteredMsgs *operator->() const {return p_msgrec;}

      void Inc_registered_count(void);
      void Dec_registered_count(void);
      RwInt32 Get_registered_count(void) const {return m_registered_count;}

      void Inc_linked_count(void);
      void Dec_linked_count(void);
      RwInt32 Get_linked_count(void) const {return m_linked_count;}

      // The registered message, through a temporary: an inline with no
      // address, named for what it returns. Evidence: ParticleEditor's
      // HandleEvents (sub_F1720) loads each of its ids' records into a
      // temporary of its own before comparing the message's with it.
      CRegisteredMsgs *get_p_msgrec()
      {
         return p_msgrec;
      }

      // The Studio sources' pEventId (the behaviours compare it directly).
      CRegisteredMsgs *p_msgrec;
      RwInt16 m_linked_count;
      RwInt16 m_registered_count;
   };

   // A message's copy of an id: only the record (a message is 8 bytes).
   struct CMsgId
   {
      CRegisteredMsgs *p_msgrec;
   };

   class CMsg
   {
   public:
      CMsg(void) {}
      CMsg(const CEventId &tId, void *tpData = 0)
      {
         Id.p_msgrec = tId.p_msgrec;
         pData = tpData;
      }
      // From a record (ParticleEditor's send, sub_F1720).
      CMsg(CRegisteredMsgs *tRec, void *tpData = 0)
      {
         Id.p_msgrec = tRec;
         pData = tpData;
      }

      CMsgId Id;
      void *pData;
   };

   // Sends the message Msg to the handlers linked to its id (the image's
   // ?_SendMsg@RWS@@YAHAAVCMsg@1@@Z).
   RwInt32 _SendMsg(CMsg &Msg);

   // Sends the message p_Msg when handlers are linked to it (the Studio
   // sources' inline; CEventHandler's destructor sends iMsgOnDeleteEntity
   // with it).
   __inline RwBool SendMsg(CMsg &p_Msg)
   {
      if (p_Msg.Id.p_msgrec != ERROR_NOT_A_VALID_MESSAGE_ID && p_Msg.Id.p_msgrec->Erm.p_next)
      {
         return _SendMsg(p_Msg);
      }
      else
      {
         return false;
      }
   }

   // Sends the message Id with no data when handlers are linked to it: an
   // inline with no address (the restart builds each message in a local of
   // its own after testing the id's record).
   inline void SendMsg(CEventId &Id)
   {
      if (Id.p_msgrec && Id.p_msgrec->Erm.p_next)
      {
         CMsg Msg(Id);
         _SendMsg(Msg);
      }
   }

   extern CEventId iMsgStartSystem;
   extern CEventId iMsgDeleteEventHandler;
   extern CEventId iMsgDeleteEntity;
   extern CEventId iMsgOnDeleteEntity;
   extern CEventId iMsgRunningTick;

   class CEventHandler
   {
   public:
      CEventHandler() : m_Active(true)
      {
      }

      virtual ~CEventHandler(void);

      virtual void HandleEvents(CMsg &pMsg) = 0;

      // Register and unregister this handler for the event Id (the image's
      // 0x12E550 and 0x12E590; config/aliases.txt).
      void LinkMsg(CEventId &Id, const RwChar *p_msg_format = 0, RwUInt16 Priority = 0x8000);
      void UnLinkMsg(CEventId &Id);

      // Sets up the links' and registered messages' free lists and
      // registers the event system's own messages, and undoes it.
      static void Open(RwUInt32 linkBlockSize, RwUInt32 regBlockSize);
      static void Close(void);

      // Registers the message Id under the name p_msgname (the game loop's
      // set-up registers its own five, sub_D6640).
      static void RegisterMsg(CEventId &Id, const RwChar *p_msgname, const RwChar *p_formatstring);
      // And unregisters it (the game loop's shutdown, sub_D6EB0).
      static void UnRegisterMsg(CEventId &Id);
      // Deletes the handlers linked to Id (the shutdown passes
      // iMsgDeleteEventHandler).
      static void DeleteEventHandlers(const CEventId &Id);
      static void DeleteEventHandlers(const CMsg *p_Msg);

      static RwBool LinkMsgToEventHandler(CEventHandler *pCEventHandler, CEventId &Id,
         const RwChar *p_formatstring, RwUInt16 priority);

      // Unlinks the links whose handler was unlinked while the message was
      // being handled.
      static void ProcessPendingUnlinks(CLinkedMsg *pErm);

      friend RwInt32 _SendMsg(CMsg &Msg);

      // Registers and unregisters the stream's test event chunk handler.
      static void RegisterStreamChunkHandlers(void);
      static void UnRegisterStreamChunkHandlers(void);

   private:
      RwBool m_Active;
   };
}

namespace RWS
{
   // The atomics' event handler, a plugin of RpAtomic.
   namespace RpAtomicToEventHandler
   {
      RwBool PluginAttach();
   }
}

// Message ids of the game's: iMsgSparkStartSystem (0x4B8758; unit_0D6640 registers it under that name), which
// CAnimPackSelector and CNPCWeaponBehavior listen to, and dword_4B67B8 and
// dword_4B67C0, which ParticleTrigger listens to (CAnimPackSelector to the
// second too).
extern RWS::CEventId iMsgSparkStartSystem;
extern RWS::CEventId dword_4B67B8;
extern RWS::CEventId dword_4B67C0;
// dword_4B8750: VehicleTrigger (and the base Trigger) create their children on it.
extern RWS::CEventId dword_4B8750;
// dword_4B67B0: PulseZoneTrigger (and PlayerTrigger) listen for it too.
extern RWS::CEventId dword_4B67B0;

#endif
