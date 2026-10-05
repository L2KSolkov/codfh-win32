// RenderWare Studio's resource manager (the game framework's
// framework/core/resourcemanager/cresourcemanager.cpp): the list of loaded
// resources, which the handlers load and free by type. The image's version
// fetches the file interface once in Load and has no Update, FindByName or
// UnLock.

#include <stdio.h>

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/badevice.h"
#include "rw/osintf.h"
#include "rws/cresourcemanager.h"
#include "rws/cresourcehandler.h"
#include "rws/memoryhandler.h"

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$?Add@CResourceManager@RWS@@SAXPBDPBVRWSGUID@2@0PBXI@Z>1>8 @ 0x0041D948
// match: __ehhandler$?Add@CResourceManager@RWS@@SAXPBDPBVRWSGUID@2@0PBXI@Z>1 @ 0x0041D950

// match: ?LoadResource@?A0x7db30061@RWS@@YAPAXPBDPBVRWSGUID@2@0PADPAURwStream@@I@Z @ 0x0012F8C0

namespace RWS
{
   namespace
   {
      void *LoadResource (const RwChar *pStrName,
                          const RWSGUID *pResId,
                          const RwChar *pStrType,
                          RwChar* pResourcePath,
                          RwStream* pStream,
                          RwUInt32 uiStreamSize)
      {
         void* ret = 0;

         CResourceHandler *pCResourceHandler = CResourceHandler::FindHandler(pStrType);

         if (pCResourceHandler)
         {
            RwUInt32 _uiResDataSize = 0;

            if ( (ret = pCResourceHandler->Load(pStrName,
                                                pStrType,
                                                pResourcePath,
                                                pStream,
                                                uiStreamSize,
                                                _uiResDataSize)) )
            {
               CResourceManager::Add(pStrName, pResId, pStrType, ret, _uiResDataSize);
            }
         }

         return (ret);
      }
   }
}

// match: ?FreeResource@?A0x7db30061@RWS@@YAHPBDPAX@Z @ 0x0012F940
namespace RWS
{
   namespace
   {
      RwBool FreeResource (const RwChar *pStrType, void *pResource)
      {
         RwBool ret = FALSE;

         CResourceHandler *pCResourceHandler = CResourceHandler::FindHandler(pStrType);

         if (pCResourceHandler)
         {
            ret = pCResourceHandler->UnLoad(pStrType, pResource);
         }

         return (ret);
      }
   }
}

namespace RWS
{
   CResource *CResource::sm_ResourceHead = 0;
}

// The typed operator delete matching the RWS operator new (the memory
// handler's, folded into operator delete: config/aliases.txt): Add's new
// unwinds through it.
void operator delete(void *pMem, RwUInt32 type);

// match: ??0CResource@RWS@@QAE@XZ @ 0x0012F980
RWS::CResource::CResource(void) :
      m_pNextResource(0),
      m_pPrevResource(0),
      m_pResName (0),
      m_pResType(0),
      m_uiLockRefCount(0)
   {
      m_Guid.Clear();

      if (sm_ResourceHead == 0)
      {
         sm_ResourceHead = this;
      }
      else
      {
         this->m_pNextResource = sm_ResourceHead;
         sm_ResourceHead->m_pPrevResource = this;
         sm_ResourceHead = this;
      }
   }

// match: ??1CResource@RWS@@QAE@XZ @ 0x0012FA30
RWS::CResource::~CResource(void)
   {
      m_pResData = 0;

      operator delete (m_pResName);
      operator delete (m_pResType);

      CResource *_pNextResource = m_pNextResource;
      CResource *_pPrevResource = m_pPrevResource;

      if (m_pPrevResource == 0)
      {
         sm_ResourceHead = _pNextResource;

         if (_pNextResource)
         {
            _pNextResource->m_pPrevResource = m_pPrevResource;
         }
      }
      else
      {
         if (_pPrevResource)
         {
            _pPrevResource->m_pNextResource = m_pNextResource;
         }

         if (_pNextResource)
         {
            _pNextResource->m_pPrevResource = m_pPrevResource;
         }
      }
   }

// match: ?Add@CResourceManager@RWS@@SAXPBDPBVRWSGUID@2@0PBXI@Z @ 0x0012FAC0
// match: __ehhandler$?Add@CResourceManager@RWS@@SAXPBDPBVRWSGUID@2@0PBXI@Z-0xF @ 0x00301770
// match: __ehhandler$?Add@CResourceManager@RWS@@SAXPBDPBVRWSGUID@2@0PBXI@Z @ 0x0030177F
void RWS::CResourceManager::Add(const RwChar *_pResName,
                              const RWSGUID *_pResId,
                              const RwChar *_pResType,
                              const void *_pResData,
                              RwUInt32 _uiResDataSize)
   {
      CResource *pResource = new(RWS_MEMORY_TYPE_RWS) CResource();

      pResource->SetName(_pResName);
      pResource->SetId(*_pResId);
      pResource->SetType(_pResType);
      pResource->SetResource(_pResData);
      pResource->SetSize(_uiResDataSize);
   }

// match: ?Remove@CResourceManager@RWS@@SAPBXPBX@Z @ 0x0012FC80
const void *RWS::CResourceManager::Remove(const void *_pResData)
   {
      CResourceIterator Ittr;

      while (!Ittr.IsDone())
      {
         if (Ittr->GetResource() == _pResData)
         {
            if (PurgeItem(Ittr))
            {
               return ( _pResData );
            }
            else
            {
               return ( 0 );
            }
         }

         ++Ittr;
      }

      return ( 0 );
   }

// match: ?FindById@CResourceManager@RWS@@SAPBXPBVRWSGUID@2@PAPBDPAI1@Z @ 0x0012FCF0
const void *RWS::CResourceManager::FindById(const RWSGUID *_pResId,
                                          RwChar const **_pResType,
                                          RwUInt32 *_uiResDataSize,
                                          RwChar const **_pResName)
   {
      CResourceIterator Ittr;

      while (!Ittr.IsDone())
      {
         if (Ittr->GetId() == (*_pResId))
         {
            if (_pResType) *_pResType = Ittr->GetType();
            if (_pResName) *_pResName = Ittr->GetName();
            if (_uiResDataSize) *_uiResDataSize = Ittr->GetSize();

            return ( Ittr->GetResource() );
         }

         ++Ittr;
      }

      return ( 0 );
   }

// match: ?PurgeItem@CResourceManager@RWS@@KA_NAAVCResourceIterator@2@@Z @ 0x0012FDE0
bool RWS::CResourceManager::PurgeItem(CResourceIterator &Ittr)
   {
      if (Ittr->GetLockRefCount() == 0)
      {
         if (FreeResource (Ittr->GetType(), const_cast<void*>(Ittr->GetResource()) ))
         {
            Ittr.Remove();

            return (true);
         }
      }

      return (false);
   }

// match: ?Purge@CResourceManager@RWS@@SA_NXZ @ 0x0012FEC0
bool RWS::CResourceManager::Purge(void)
   {
      bool flag = true;

      CResourceIterator Ittr;

      while (!Ittr.IsDone())
      {
         if (!PurgeItem(Ittr))
         {
            flag = false;

            ++Ittr;
         }
      }

      return (flag);
   }

// match: ?PurgeAll@CResourceManager@RWS@@SA_NXZ @ 0x0012FF20
bool RWS::CResourceManager::PurgeAll(void)
   {
      bool flag = true;

      CResourceIterator Ittr;

      while (!Ittr.IsDone())
      {
         Ittr->SetLockRefCount(0);

         if (!PurgeItem(Ittr))
         {
            flag = false;

            ++Ittr;
         }
      }

      return (flag);
   }

// match: ?Lock@CResourceManager@RWS@@SAXPBX@Z @ 0x0012FF90
void RWS::CResourceManager::Lock(const void *ptr)
   {
      CResourceIterator Ittr;

      while (!Ittr.IsDone())
      {
         if (Ittr->GetResource() == ptr)
         {
            Ittr->SetLockRefCount(Ittr->GetLockRefCount() + 1);

            break;
         }

         ++Ittr;
      }
   }

// match: ?Load@CResourceManager@RWS@@SAPAXPBDPBVRWSGUID@2@000@Z @ 0x00130000
void *RWS::CResourceManager::Load(
      const RwChar *pStrName,
      const RWSGUID *pResId,
      const RwChar *pStrType,
      const RwChar *pStrFName,
      const RwChar *pStrLoc)
   {
      RwChar ResourcePath[255];
      RwChar FilePath[255];

      ResourcePath[0] = 0;
      rwstrcat(ResourcePath, pStrLoc);

      FilePath[0] = 0;
      rwstrcat(FilePath, pStrFName);

      RwUInt32 uiStreamSize;

      RwFileFunctions *fileFunctions = RwOsGetFileInterface();

      void *In = fileFunctions->rwfopen(FilePath, "rb");

      fileFunctions->rwfseek(In, 0, SEEK_END);

      uiStreamSize = fileFunctions->rwftell(In);

      fileFunctions->rwfclose(In);

      RwStream* pStream = RwStreamOpen(rwSTREAMFILENAME, rwSTREAMREAD, FilePath);

      void *ptrRes = LoadResource(pStrName, pResId, pStrType, ResourcePath, pStream, uiStreamSize);

      RwStreamClose(pStream, FilePath);

      return (ptrRes);
   }

// match: ?UpLoad@CResourceManager@RWS@@SAPAXPBDPBVRWSGUID@2@00PAURwStream@@I@Z @ 0x00130120
void *RWS::CResourceManager::UpLoad(
      const RwChar *pStrName,
      const RWSGUID *pResId,
      const RwChar *pStrType,
      const RwChar *pStrLoc,
      RwStream* pStream,
      RwUInt32 nEmbDataSize)
   {
      void *ptrRes = LoadResource (pStrName, pResId, pStrType, "", pStream, nEmbDataSize);

      return (ptrRes);
   }

// match: ?Open@CResourceManager@RWS@@SAXXZ @ 0x00130150
void RWS::CResourceManager::Open(void)
   {
      CResourceHandler::OpenAll();
   }

// match: ?Close@CResourceManager@RWS@@SAXXZ @ 0x00130160
void RWS::CResourceManager::Close(void)
   {
      CResourceHandler::CloseAll();
   }

// CResource's setters and the iterator's Remove (inline in
// rws/cresourcemanager.h), emitted for Add and PurgeItem.
// match: ?SetType@CResource@RWS@@QAEXPBD@Z @ 0x0012FB80
// match: ?SetName@CResource@RWS@@QAEXPBD@Z @ 0x0012FC00
// match: ?Remove@CResourceIterator@RWS@@QAEXXZ @ 0x0012FE50
