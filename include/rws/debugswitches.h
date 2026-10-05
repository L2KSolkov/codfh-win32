/*
 * RWS::DebugSwitches, after RenderWare Studio's game framework
 * (framework/toolkits/debugtools/debugswitches.h): the debug flags
 * CDebugScript's commands set (command 13) and the scripts test (sub_1326B0's
 * callers test switch 0x15). The game numbers more switches than the Studio
 * sources' enumeration, so the switch is an integer here; m_last only sizes
 * the array (the image's is at 0x4CF988).
 */
#ifndef RWS_DEBUGSWITCHES_H
#define RWS_DEBUGSWITCHES_H

#include "rw/ostypes.h"

namespace RWS
{
   namespace DebugSwitches
   {
      // Room for the image's array (0x4CF988, 40 bytes to the next global).
      const RwInt32 m_last = 40;

      void SetSwitch(RwInt32 var, bool flag);
      bool GetSwitch(RwInt32 var);
   }
}

#endif
