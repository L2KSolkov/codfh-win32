// RenderWare Studio's entity stream functions (the game framework's
// framework/core/attributehandler/attributehandlerstrfuncs.cpp): the chunk
// handlers that create, update and delete entities from the stream. The
// game's version calls its hook sub_12F0A0 first in the create and delete
// handlers, will not create a "PathNode" (PathNode::pPathNodeClassID), and creates in the
// handler itself (the framework's CAttributePacket::CreateEntity is not in
// the image); the function profiler's commands are read and ignored
// (RWS_FUNCTIONPROFILE off).

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/badevice.h"
#include "rws/rwsguid.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "rws/memoryhandler.h"
#include "rws/strfunc.h"
#include "game/gameloop.h"
#include "game/functions.h"
#include "types/PathNode.h"
#if defined(CODFH_WIN32)
extern "C" void plog(const RwChar *fmt, ...);
#endif


namespace RWS
{
   // The function profiler's messages (registered below).
   void HandleProfilerMessages(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream);
}

namespace RWS
{
   namespace
   {
// match: ?DeleteEntity@?A0xbaaaa58d@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00129D60
// sp-match: ?DeleteEntity@?A0xbaaaa58d@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000DE120
      void DeleteEntity(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         sub_12F0A0();

         RwChar *buffer = static_cast<RwChar*>(RWS_OP_NEW(rChunkHeader.length));

         RwStreamRead(pStream, buffer, rChunkHeader.length);

         const CAttributePacket* pAttr = reinterpret_cast<CAttributePacket*>(buffer);

         RWSGUID Id = pAttr->GetInstanceId();

         CAttributeHandler* pCAttributeHandler = CAttributeHandler::Find(Id);

         if (pCAttributeHandler)
         {
            delete pCAttributeHandler;
         }

         operator delete (buffer);
      }

// match: ?DeleteAllEntities@?A0xbaaaa58d@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00129E00
// sp-match: ?DeleteAllEntities@?A0xbaaaa58d@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000DE190
      void DeleteAllEntities(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         sub_12F0A0();

         CEventHandler::DeleteEventHandlers(iMsgDeleteEventHandler);

         CAttributeHandler::Purge();
      }

// match: ?UpdateEntityAttributes@?A0xbaaaa58d@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00129E20
// sp-match: ?UpdateEntityAttributes@?A0xbaaaa58d@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000DE1B0
      void UpdateEntityAttributes(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         RwChar *buffer = static_cast<RwChar*>(RWS_OP_NEW(rChunkHeader.length));

         RwStreamRead(pStream, buffer, rChunkHeader.length);

         const CAttributePacket* pAttr = reinterpret_cast<CAttributePacket*>(buffer);

         RWSGUID InstanceId = pAttr->GetInstanceId();

         CAttributeHandler *pCAttributeHandler = CAttributeHandler::Find(InstanceId);

         if (pCAttributeHandler)
         {
            pCAttributeHandler->HandleAttributes(*pAttr);
         }

         operator delete (buffer);
      }

// match: ?CreateEntity@?A0xbaaaa58d@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00129EA0
// sp-match: ?CreateEntity@?A0xbaaaa58d@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000DE210
      void CreateEntity(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         sub_12F0A0();

         RwChar *buffer = static_cast<RwChar*>(RWS_OP_NEW(rChunkHeader.length));

         RwStreamRead(pStream, buffer, rChunkHeader.length);

         RwBool * pbGlobal = reinterpret_cast<RwBool *>(buffer);

         const CAttributePacket* pAttr = reinterpret_cast<CAttributePacket*>(pbGlobal + 1);

         RWSGUID InstanceId = pAttr->GetInstanceId();

         CAttributeHandler *pCAttributeHandler = CAttributeHandler::Find(InstanceId);
         if (pCAttributeHandler)
         {
#if defined(CODFH_WIN32)
            // (the port: an entity made again under an instance ID already in use replaces it)
            const RwUInt32 *pId = reinterpret_cast<const RwUInt32 *>(&InstanceId);

            plog("RWS: %s %08X-%08X-%08X-%08X already exists; the old one deleted",
                 pAttr->GetNameOfClassToCreate(), pId[0], pId[1], pId[2], pId[3]);
#endif
            delete pCAttributeHandler;
         }

         const RwChar *cclassname = pAttr->GetNameOfClassToCreate();

         if (rwstrcmp(PathNode::pPathNodeClassID, cclassname))
         {
            CAttributeHandler *pNewAttrHand = CClassFactory::MakeNew(cclassname, *pAttr);

            if (pNewAttrHand)
            {
               pNewAttrHand->Add(InstanceId);
               CAttributeHandler::NewAttributeHandlerCreated();

               if (*pbGlobal)
               {
                  pNewAttrHand->Lock();
               }
            }
         }

         operator delete (buffer);
      }
   }
}

// match: ?HandleProfilerMessages@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00129FB0
// sp-match: ?HandleProfilerMessages@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000DE2D0
void RWS::HandleProfilerMessages(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
   {
      RwInt32 Command, Child = 0;

      RwStreamRead(pStream, &Command, sizeof(RwInt32));
      RwStreamRead(pStream, &Child, sizeof(RwInt32));
   }

// match: ?RegisterStreamChunkHandlers@CAttributeHandler@RWS@@SAXXZ @ 0x00129FF0
// sp-match: ?RegisterStreamChunkHandlers@CAttributeHandler@RWS@@SAXXZ @ 0x000DE310
void RWS::CAttributeHandler::RegisterStreamChunkHandlers(void)
   {
      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_CreateEntity), CreateEntity);

      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_UpdateEntityAttributes), UpdateEntityAttributes);

      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_DeleteEntity), DeleteEntity);

      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_DeleteAllEntities), DeleteAllEntities);

      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_FunctionProfiler), HandleProfilerMessages);

      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_ResetEntity), CreateEntity);
   }

// match: ?UnRegisterStreamChunkHandlers@CAttributeHandler@RWS@@SAXXZ @ 0x0012A070
// sp-match: ?UnRegisterStreamChunkHandlers@CAttributeHandler@RWS@@SAXXZ @ 0x000DE370
void RWS::CAttributeHandler::UnRegisterStreamChunkHandlers(void)
   {
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_UpdateEntityAttributes));
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_CreateEntity));
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_DeleteEntity));
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_DeleteAllEntities));
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_FunctionProfiler));
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_ResetEntity));
   }
