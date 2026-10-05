/*
 * RWS::SkinHelper, copied from RenderWare Studio's game framework
 * (framework/toolkits/world/helpers/skinhelper.h): a clump's skins (the
 * database's sub_133170 and sub_1331A0).
 */
#ifndef RWS_SKINHELPER_H
#define RWS_SKINHELPER_H

#include "rw/rpatomic.h"
#include "rw/rpskin.h"

typedef RpSkin *(*RpSkinCallBack)(RpSkin *pSkin, void *pData);

namespace RWS
{
   namespace SkinHelper
   {
      struct SkinCallbackData
      {
         SkinCallbackData(RpSkinCallBack callback, void* pData)
            : m_callback(callback), m_pData(pData) {}

         RpSkinCallBack m_callback;
         void*          m_pData;
      };

      RpAtomic* ForAllSkinsCallback(RpAtomic* pAtomic, void* pData);
      void ForAllSkins( RpClump& clump, RpSkinCallBack callback, void* pData );
      // The clump's first skin, or 0 (the clump data plugin and the
      // animation players look for it).
      RpSkin* FindFirstSkin(RpClump& clump);
      RpSkin* FindFirstSkinCallback(RpSkin* pSkin, void* pData);
   }
}

#endif
