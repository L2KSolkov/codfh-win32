// RenderWare Studio's event stream functions (the game framework's
// framework/core/eventhandler/eventhandlerstrfuncs.cpp): the chunk handler
// that fires a named test event from the stream, and its registration.

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rws/ceventhandler.h"
#include "rws/memoryhandler.h"
#include "rws/strfunc.h"
#include "game/gameloop.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?SendTestEvent@?A0x95c57325@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z>1>8 @ 0x0041D818
// match: __ehhandler$?SendTestEvent@?A0x95c57325@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z>1 @ 0x0041D820

// match: ?SendTestEvent@?A0x95c57325@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x0012EBE0
// match: __ehhandler$?SendTestEvent@?A0x95c57325@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z-0x8 @ 0x003016D0
// match: __ehhandler$?SendTestEvent@?A0x95c57325@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x003016D8
// sp-match: ?SendTestEvent@?A0x95c57325@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000E0B50

namespace RWS
{
   namespace
   {
      void SendTestEvent (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         RwChar *buffer = static_cast<RwChar*>(::RWS_OP_NEW(rChunkHeader.length) );

         RwStreamRead(pStream, buffer, rChunkHeader.length);

         CEventId testevent;

         CEventHandler::RegisterMsg( testevent, reinterpret_cast<RwChar*>(buffer), 0);

         SendMsg(testevent);

         CEventHandler::UnRegisterMsg(testevent);

         operator delete (buffer);
      }
   }
}

// match: ?RegisterStreamChunkHandlers@CEventHandler@RWS@@SAXXZ @ 0x0012ECB0
// sp-match: ?RegisterStreamChunkHandlers@CEventHandler@RWS@@SAXXZ @ 0x000E0C10
void RWS::CEventHandler::RegisterStreamChunkHandlers(void)
   {
      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_SendTestEvent), SendTestEvent);
   }

// match: ?UnRegisterStreamChunkHandlers@CEventHandler@RWS@@SAXXZ @ 0x0012ECD0
// sp-match: ?UnRegisterStreamChunkHandlers@CEventHandler@RWS@@SAXXZ @ 0x000E0C30
void RWS::CEventHandler::UnRegisterStreamChunkHandlers(void)
   {
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_SendTestEvent));
   }
