// RenderWare Studio's skin helper (the game framework's
// framework/toolkits/world/helpers/skinhelper.cpp): a clump's skins.

#include "rw/ostypes.h"
#include "rw/rpatomic.h"
#include "rw/rpskin.h"
#include "rws/skinhelper.h"

// match: ?ForAllSkinsCallback@SkinHelper@RWS@@YAPAURpAtomic@@PAU3@PAX@Z @ 0x00133120
// sp-match: ?ForAllSkinsCallback@SkinHelper@RWS@@YAPAURpAtomic@@PAU3@PAX@Z @ 0x000E38E0
RpAtomic* RWS::SkinHelper::ForAllSkinsCallback(RpAtomic* pAtomic, void* pData)
      {
         RpSkin* pSkin = RpSkinGeometryGetSkin(RpAtomicGetGeometry(pAtomic));

         if(pSkin)
         {
            SkinCallbackData& cbData = *static_cast<SkinCallbackData*>(pData);

            if(0 == cbData.m_callback(pSkin,cbData.m_pData)) pAtomic = 0;
         }

         return(pAtomic);
      }

// match: ?ForAllSkins@SkinHelper@RWS@@YAXAAURpClump@@P6APAURpSkin@@PAU4@PAX@Z2@Z @ 0x00133170
// sp-match: ?ForAllSkins@SkinHelper@RWS@@YAXAAURpClump@@P6APAURpSkin@@PAU4@PAX@Z2@Z @ 0x000E3910
void RWS::SkinHelper::ForAllSkins( RpClump& clump, RpSkinCallBack callback, void* pData )
      {
         SkinCallbackData cbData(callback,pData);

         RpClumpForAllAtomics(&clump,ForAllSkinsCallback,&cbData);
      }

// match: ?FindFirstSkin@SkinHelper@RWS@@YAPAURpSkin@@AAURpClump@@@Z @ 0x001331A0
// sp-match: ?FindFirstSkin@SkinHelper@RWS@@YAPAURpSkin@@AAURpClump@@@Z @ 0x000E3940
RpSkin* RWS::SkinHelper::FindFirstSkin(RpClump& clump)
      {
         RpSkin* pSkin = 0;

         ForAllSkins(clump,FindFirstSkinCallback,&pSkin);

         return (pSkin);
      }

// match: ?FindFirstSkinCallback@SkinHelper@RWS@@YAPAURpSkin@@PAU3@PAX@Z @ 0x001331D0
// sp-match: ?FindFirstSkinCallback@SkinHelper@RWS@@YAPAURpSkin@@PAU3@PAX@Z @ 0x0010B340
RpSkin* RWS::SkinHelper::FindFirstSkinCallback(RpSkin* pSkin, void* pData)
      {
         *static_cast<RpSkin**>(pData) = pSkin;

         return(0);
      }
