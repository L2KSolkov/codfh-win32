// RenderWare Studio's clump helper (the game framework's
// framework/toolkits/world/helpers/clumphelper.cpp): the message sent
// before a clump is destroyed, registered while the main loop is open. The
// game's has no open flag, and its other functions are not in the image.

#include "rw/ostypes.h"
#include "rws/ceventhandler.h"
#include "rws/clumphelper.h"
#include "rws/atomichelper.h"
#include "rw/rpatomic.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BG@PCGGGDIP@iMsgPreRpClumpDestroy?$AA@ @ 0x003DAC2C
// match: ??_C@_08MOJPECGB@RwFrame?$CK?$AA@ @ 0x003DAC44
// match: .CRT$XCU+0 @ 0x00427110

// match: _$E1 @ 0x0030BB60
// match: _$E2 @ 0x0030E810

namespace RWS
{
   namespace ClumpHelper
   {
      CEventId iMsgPreRpClumpDestroy;
   }
}

// match: ?Open@ClumpHelper@RWS@@YAXXZ @ 0x00132F60
void RWS::ClumpHelper::Open()
      {
         CEventHandler::RegisterMsg ( iMsgPreRpClumpDestroy, "iMsgPreRpClumpDestroy", "RwFrame*");
      }

// match: ?Close@ClumpHelper@RWS@@YAXXZ @ 0x00132F80
void RWS::ClumpHelper::Close()
      {
         CEventHandler::UnRegisterMsg ( iMsgPreRpClumpDestroy );
      }

// match: ?SetIsVisibleCallback@ClumpHelper@RWS@@YAPAURpAtomic@@PAU3@PAX@Z @ 0x00132FA0
RpAtomic* RWS::ClumpHelper::SetIsVisibleCallback(RpAtomic* pAtomic, void* pData)
      {
         AtomicHelper::SetIsVisible(*pAtomic, 0 != pData);

         return(pAtomic);
      }

// match: ?SetIsVisible@ClumpHelper@RWS@@YAXAAURpClump@@_N@Z @ 0x00132FC0
void RWS::ClumpHelper::SetIsVisible( RpClump& clump, bool isVisible )
      {
         RpClumpForAllAtomics(&clump, SetIsVisibleCallback, isVisible ? reinterpret_cast<void*>(1) : 0);
      }

// match: ?SetCanCollideCallback@ClumpHelper@RWS@@YAPAURpAtomic@@PAU3@PAX@Z @ 0x00132FF0
RpAtomic* RWS::ClumpHelper::SetCanCollideCallback(RpAtomic* pAtomic, void* pData)
      {
         AtomicHelper::SetCanCollide(*pAtomic, 0 != pData);

         return(pAtomic);
      }

// match: ?SetCanCollide@ClumpHelper@RWS@@YAXAAURpClump@@_N@Z @ 0x00133010
void RWS::ClumpHelper::SetCanCollide(RpClump& clump, bool canCollide)
      {
         RpClumpForAllAtomics(&clump, SetCanCollideCallback, canCollide ? reinterpret_cast<void*>(1) : 0);
      }
