/*
 * RWS::AtomicHelper, after RenderWare Studio's game framework
 * (framework/toolkits/world/helpers/atomichelper.h): an atomic's render and
 * collision flags (rpATOMICRENDER, rpATOMICCOLLISIONTEST).
 */
#ifndef RWS_ATOMICHELPER_H
#define RWS_ATOMICHELPER_H

#include "rw/rpatomic.h"

namespace RWS
{
   namespace AtomicHelper
   {
      void SetIsVisible( RpAtomic& pAtomic, bool isVisible );
      void SetCanCollide( RpAtomic& pAtomic, bool canCollide );
   }
}

#endif
