// RenderWare Studio's atomic helper (the game framework's
// framework/toolkits/world/helpers/atomichelper.cpp): the two flag setters
// the game keeps (its Destroy and HandleSystemCommands are not in the
// image).

#include "rw/ostypes.h"
#include "rw/rpatomic.h"
#include "rws/atomichelper.h"

// match: ?SetIsVisible@AtomicHelper@RWS@@YAXAAURpAtomic@@_N@Z @ 0x00132B50
void RWS::AtomicHelper::SetIsVisible( RpAtomic& pAtomic, bool isVisible )
      {
         RwUInt32 flags = RpAtomicGetFlags(&pAtomic);

         if (isVisible) flags |= static_cast<RwUInt32>(rpATOMICRENDER);
         else flags &= ~ static_cast<RwUInt32>(rpATOMICRENDER);

         (void)RpAtomicSetFlags( &pAtomic, flags);
      }

// match: ?SetCanCollide@AtomicHelper@RWS@@YAXAAURpAtomic@@_N@Z @ 0x00132B90
void RWS::AtomicHelper::SetCanCollide( RpAtomic& pAtomic, bool canCollide )
      {
         RwUInt32 flags = RpAtomicGetFlags(&pAtomic);

         if (canCollide) flags |= static_cast<RwUInt32>(rpATOMICCOLLISIONTEST);
         else flags &= ~static_cast<RwUInt32>(rpATOMICCOLLISIONTEST);

         (void)RpAtomicSetFlags( &pAtomic, flags);
      }
