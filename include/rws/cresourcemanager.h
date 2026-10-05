/*
 * RWS::CResource, CResourceIterator and CResourceManager, copied from
 * RenderWare Studio's game framework
 * (Studio\console\game_framework\source\framework\core\resourcemanager\
 * cresource.h and cresourcemanager.h). The image's version has no Update
 * and keeps CResource's setters and the iterator's Remove out of line
 * (inline in the class, emitted in cresourcemanager.cpp); FindByName and
 * UnLock are not in the image. A resource is 0x2C bytes: its neighbours, name,
 * type, data, size, lock count and id.
 * The module shutdown (sub_D7040) calls PurgeAll; SplinePath's vf_00C
 * (sub_BA230) looks its attached spline up with FindById.
 */
#ifndef RWS_CRESOURCEMANAGER_H
#define RWS_CRESOURCEMANAGER_H

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/badevice.h"
#include "rws/rwsguid.h"
#include "rws/memoryhandler.h"

namespace RWS
{
   class CResource
   {
      friend class CResourceIterator;

   public:
      CResource(void);
      ~CResource(void);

      const RWSGUID & GetId() {return m_Guid;}
      const RwChar *GetType(void) const {return m_pResType;}
      const RwChar *GetName(void) const {return m_pResName;}
      const void *GetResource(void) const {return m_pResData;}
      RwUInt32 GetSize(void) const {return m_uiResDataSize;}
      RwUInt32 GetLockRefCount(void) const {return m_uiLockRefCount;}

      void SetId( const RWSGUID &rGuid ) {m_Guid = rGuid;}

      void SetType(const RwChar *pType)
      {
         operator delete (m_pResType);

         if (pType && rwstrlen(pType) > 0)
         {
            m_pResType = static_cast<RwChar *>(::RWS_OP_NEW( rwstrlen(pType) + 1));
            rwstrcpy(m_pResType, pType);
         }
         else
         {
            m_pResType = 0;
         }
      }

      void SetName(const RwChar *pName)
      {
         operator delete (m_pResName);

         if (pName && rwstrlen(pName) > 0)
         {
            m_pResName = static_cast<RwChar *>(::RWS_OP_NEW( rwstrlen(pName) + 1));
            rwstrcpy(m_pResName, pName);
         }
         else
         {
            m_pResName = 0;
         }
      }

      void SetResource(const void *pResource) {m_pResData = pResource;}
      void SetSize(RwUInt32 uiSize) {m_uiResDataSize = uiSize;}
      void SetLockRefCount(RwUInt32 uiLockRefCount) {m_uiLockRefCount = uiLockRefCount;}

   protected:
      CResource *m_pNextResource;
      CResource *m_pPrevResource;

      static CResource *sm_ResourceHead;

   private:
      RwChar *m_pResName;
      RwChar *m_pResType;
      const void *m_pResData;
      RwUInt32 m_uiResDataSize;
      RwUInt32 m_uiLockRefCount;
      RWSGUID m_Guid;
   };

   class CResourceIterator
   {
   public:
      CResourceIterator()
      {
         m_pCResource = CResource::sm_ResourceHead;
      }

      bool IsDone(void)
      {
         if (m_pCResource == 0 ) return true;
         else return false;
      }

      CResource* operator->() const
      {
         return m_pCResource;
      }

      CResourceIterator& operator++()
      {
         m_pCResource = m_pCResource->m_pNextResource;
         return *this;
      }

      void Remove(void)
      {
         if (m_pCResource)
         {
            CResource *next = m_pCResource->m_pNextResource;
            delete m_pCResource;
            m_pCResource = next;
         }
      }

   private:
      CResource *m_pCResource;
   };

   class CResourceManager
   {
   public:
      static void Add(const RwChar *_pResName, const RWSGUID *_pResId, const RwChar *_pResType,
                      const void *_pResData, RwUInt32 _uiResDataSize);
      static const void *Remove(const void *_pResData);
      static const void *FindById(const RWSGUID *pResourceId, const RwChar **ppResourceType,
                                  RwUInt32 *pResourceSize = 0, const RwChar **ppResourceName = 0);
      static bool Purge(void);
      static bool PurgeAll(void);
      static void Lock(const void *ptr);
      static void *Load(const RwChar *pStrName, const RWSGUID *pResId, const RwChar *pStrType,
                        const RwChar *pStrFName, const RwChar *pStrLoc);
      static void *UpLoad(const RwChar *pStrName, const RWSGUID *pResId, const RwChar *pStrType,
                          const RwChar *pStrLoc, RwStream* pStream, RwUInt32 nEmbDataSize);
      static void Open(void);
      static void Close(void);

      // Registers and unregisters the stream's asset chunk handlers.
      static void RegisterStreamChunkHandlers(void);
      static void UnRegisterStreamChunkHandlers(void);

   protected:
      static bool PurgeItem(CResourceIterator &Ittr);
   };
}

#endif
