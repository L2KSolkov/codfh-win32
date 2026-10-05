// RenderWare Studio's resource stream functions (the game framework's
// framework/core/resourcemanager/resourcemanagerstrfunc.cpp): the chunk
// handlers that load, load embedded and unload assets. The game's version
// calls its hook sub_12F0A0 first in each and has no UpdateAsset.

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rws/cresourcemanager.h"
#include "rws/memoryhandler.h"
#include "rws/strfunc.h"
#include "game/gameloop.h"

// match: ?UnLoadAsset@?A0x8c6de0eb@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00130170
namespace RWS
{
   namespace
   {
      void UnLoadAsset (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         sub_12F0A0();

         RwChar *buffer = static_cast<RwChar*>(::RWS_OP_NEW(rChunkHeader.length) );

         RwStreamRead(pStream, buffer, rChunkHeader.length);

         RWSGUID * pResourceId = reinterpret_cast<RWSGUID *>(buffer);

         const RwChar *pResType;
         const void *pResData;

         if ((pResData = CResourceManager::FindById(pResourceId, &pResType)))
         {
            CResourceManager::Remove(const_cast<void*>(pResData));
         }

         operator delete (buffer);
      }
   }
}

// match: ?LoadAsset@?A0x8c6de0eb@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x001301F0
namespace RWS
{
   namespace
   {
      void LoadAsset (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         sub_12F0A0();

         RwChar *buffer = static_cast<RwChar*>(::RWS_OP_NEW(rChunkHeader.length) );

         RwStreamRead(pStream, buffer, rChunkHeader.length);

         RwUInt32 * pPaddedSize = reinterpret_cast<RwUInt32 *>(buffer);

         RwChar * pStrName = reinterpret_cast<RwChar *>(pPaddedSize + 1);
         RWSGUID * pResourceId = reinterpret_cast<RWSGUID *>(pStrName + (*pPaddedSize));

         pPaddedSize = reinterpret_cast<RwUInt32 *>(pResourceId + 1);
         RwChar * pStrType = reinterpret_cast<RwChar *>(pPaddedSize + 1);

         pPaddedSize = reinterpret_cast<RwUInt32 *>(pStrType + (*pPaddedSize));
         RwChar * pStrFName = reinterpret_cast<RwChar *>(pPaddedSize + 1);

         pPaddedSize = reinterpret_cast<RwUInt32 *>(pStrFName + (*pPaddedSize));
         RwChar * pStrLoc = reinterpret_cast<RwChar *>(pPaddedSize + 1);

         RwBool * pbGlobal = reinterpret_cast<RwBool *>(pStrLoc + (*pPaddedSize));

         if (CResourceManager::FindById(pResourceId, 0))
         {
         }
         else
         {
            void * pResource = CResourceManager::Load(pStrName,
                                                      pResourceId,
                                                      pStrType,
                                                      pStrFName,
                                                      pStrLoc);

            if ((*pbGlobal))
            {
               CResourceManager::Lock(pResource);
            }
         }

         operator delete (buffer);
      }
   }
}

// match: ?LoadEmbeddedAsset@?A0x8c6de0eb@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x001302E0
namespace RWS
{
   namespace
   {
      void LoadEmbeddedAsset (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
      {
         sub_12F0A0();

         RwUInt32 nEmbHeaderSize = 0;

         RwStreamRead (pStream, &nEmbHeaderSize, sizeof (RwUInt32));

         RwChar *buffer = static_cast<RwChar*>(::RWS_OP_NEW(nEmbHeaderSize) );

         RwStreamRead (pStream, buffer, nEmbHeaderSize);

         RwUInt32 nEmbDataSize = 0;

         RwStreamRead (pStream, &nEmbDataSize, sizeof (RwUInt32));

         RwUInt32 * pPaddedSize = reinterpret_cast<RwUInt32 *>(buffer);

         RwChar * pStrName = reinterpret_cast<RwChar *>(pPaddedSize + 1);
         RWSGUID * pResourceId = reinterpret_cast<RWSGUID *>(pStrName + (*pPaddedSize));

         pPaddedSize = reinterpret_cast<RwUInt32 *>(pResourceId + 1);
         RwChar * pStrType = reinterpret_cast<RwChar *>(pPaddedSize + 1);

         pPaddedSize = reinterpret_cast<RwUInt32 *>(pStrType + (*pPaddedSize));
         RwChar * pStrFName = reinterpret_cast<RwChar *>(pPaddedSize + 1);

         pPaddedSize = reinterpret_cast<RwUInt32 *>(pStrFName + (*pPaddedSize));
         RwChar * pStrLoc = reinterpret_cast<RwChar *>(pPaddedSize + 1);

         RwBool * pbGlobal = reinterpret_cast<RwBool *>(pStrLoc + (*pPaddedSize));

         if (CResourceManager::FindById(pResourceId, 0))
         {
            RwStreamSkip (pStream, nEmbDataSize);
         }
         else
         {
            void * pResource = CResourceManager::UpLoad (pStrName,
                                                         pResourceId,
                                                         pStrType,
                                                         pStrLoc,
                                                         pStream,
                                                         nEmbDataSize);

            if ((*pbGlobal))
            {
               CResourceManager::Lock(pResource);
            }
         }

         RwInt32 nLen = rChunkHeader.length -
            nEmbDataSize - nEmbHeaderSize - 2 * sizeof (RwUInt32);

         if (nLen > 0)
            RwStreamSkip (pStream, nLen);

         operator delete (buffer);
      }
   }
}

// match: ?RegisterStreamChunkHandlers@CResourceManager@RWS@@SAXXZ @ 0x00130440
void RWS::CResourceManager::RegisterStreamChunkHandlers(void)
   {
      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_UnLoadAsset), UnLoadAsset);

      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_LoadAsset), LoadAsset);

      CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
         strfunc_LoadEmbeddedAsset), LoadEmbeddedAsset);
   }

// match: ?UnRegisterStreamChunkHandlers@CResourceManager@RWS@@SAXXZ @ 0x00130480
void RWS::CResourceManager::UnRegisterStreamChunkHandlers(void)
   {
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_UnLoadAsset));
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_LoadAsset));
      CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_LoadEmbeddedAsset));
   }
