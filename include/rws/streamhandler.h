/*
 * RWS::CStreamHandler, copied from RenderWare Studio's game framework
 * (framework/core/streamhandler/streamhandler.h): the registry of chunk
 * handlers by chunk id (a std::map, whose instantiations streamhandler.cpp
 * emits) and the stream's processing, which dispatches each chunk to its
 * handler. The singleton (Instance) keeps the map and the current chunk's
 * header (+0x0C). The game loop's level load processes GLOBAL.DFF and
 * LEVEL.DFF through it (sub_D80C0).
 */
#ifndef RWS_STREAMHANDLER_H
#define RWS_STREAMHANDLER_H

#include <map>

#include "rw/ostypes.h"
#include "rw/bastream.h"

namespace RWS
{
   typedef void (*StreamChunkHandler)(RwChunkHeaderInfo &rChunkHeader, RwStream *pStream);

   class CStreamHandler
   {
      public:
         static void ProcessStream(RwStream *pStream);

         static void RegisterChunkHandler(RwUInt32 ChunkType, StreamChunkHandler ChunkHandler);

         static void UnRegisterChunkHandler(RwUInt32 ChunkType);

         static CStreamHandler *Instance(void);

         static void RegisterStreamChunkHandlers(void);

         static void UnRegisterStreamChunkHandlers(void);

      protected:
         static bool RwStreamEOF(RwStream *pStream);

      private:
         typedef std::map< RwUInt32, StreamChunkHandler > StreamChunkHandlerMap;

         StreamChunkHandlerMap m_StreamChunkHandlerMap;

         RwChunkHeaderInfo m_RwChunkHeaderInfo;
   };
}

#endif
