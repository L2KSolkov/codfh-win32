// RenderWare Studio's debug switches (the game framework's
// framework/toolkits/debugtools/debugswitches.cpp): an array of flags,
// 0x4CF988. The game uses switches past the Studio sources' enumeration
// (the scripts test switch 0x15), so they are numbered here.

#include "rw/ostypes.h"
#include "rws/debugswitches.h"

namespace RWS
{
   namespace DebugSwitches
   {
      bool _flags[m_last];
   }
}

// match: ?SetSwitch@DebugSwitches@RWS@@YAXH_N@Z @ 0x00132690
// sp-match: ?SetSwitch@DebugSwitches@RWS@@YAXH_N@Z @ 0x000E30B0
void RWS::DebugSwitches::SetSwitch(RwInt32 var, bool flag)
      {
         _flags[var] = flag;
      }

// match: ?GetSwitch@DebugSwitches@RWS@@YA_NH@Z @ 0x001326B0
// sp-match: ?GetSwitch@DebugSwitches@RWS@@YA_NH@Z @ 0x000E30C0
bool RWS::DebugSwitches::GetSwitch(RwInt32 var)
      {
         return (_flags[var]);
      }


#ifdef CODFH_PLAIN
// Plain builds (tools/plainbuild.py): the variables below are a second name for this unit's
// variables' bytes in the image (tools/session/overlapvars.py --aliases); only the placement
// link gives them one storage, so any other link binds them here at the image offset.
// (bound at start-up: the library initialization area runs before every game constructor)
#pragma warning(disable: 4073)
#pragma init_seg(lib)
// 0x004CF9A8: RWS::DebugSwitches::_flags + 0x20
RwInt32 &dword_4CF9A8 = *(RwInt32 *)((RwUInt8 *)&RWS::DebugSwitches::_flags + 0x20);
// 0x004CF9AC: RWS::DebugSwitches::_flags + 0x24
bool &byte_4CF9AC = *(bool *)((RwUInt8 *)&RWS::DebugSwitches::_flags + 0x24);
#endif
