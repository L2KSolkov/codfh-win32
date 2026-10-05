/*
 * RWS::ClumpHelper, after RenderWare Studio's game framework
 * (framework/toolkits/world/helpers/clumphelper.h): its set-up and shutdown,
 * which the main loop calls, and the clump-wide flag setters.
 */
#ifndef RWS_CLUMPHELPER_H
#define RWS_CLUMPHELPER_H

#include "rw/rpatomic.h"

namespace RWS
{
   namespace ClumpHelper
   {
      void Open(void);
      void Close(void);

      // A clump's atomics' render and collision flags (RWS::AtomicHelper's,
      // through RpClumpForAllAtomics).
      RpAtomic* SetIsVisibleCallback(RpAtomic* pAtomic, void* pData);
      void SetIsVisible( RpClump& clump, bool isVisible );
      RpAtomic* SetCanCollideCallback(RpAtomic* pAtomic, void* pData);
      void SetCanCollide(RpClump& clump, bool canCollide);
   }
}

#endif
