/*
 * RWS::CSystemCommands: the commands every entity's attribute packet may
 * carry (RenderWare Studio's framework, csystemcommands.h), cut down to its
 * class id (dword 0x429C2C, the string "CSystemCommands"), its command
 * numbers, which the behaviours iterate for, UpdateFrame, and the atomic
 * collision properties plugin's functions.
 */
#ifndef RWS_CSYSTEMCOMMANDS_H
#define RWS_CSYSTEMCOMMANDS_H

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rw/baframe.h"
#include "rw/rpatomic.h"

namespace RWS
{
   class CSystemCommands
   {
   public:
      RWS_DECLARE_CLASSID(CSystemCommands);

      enum
      {
         CMD_AttachResource,
         CMD_LoadMatrix,
         CMD_SetSolidFlag,
         CMD_SetCollisionFlag,
         CMD_SetInvisibleFlag
      };

      // Loads the frame's matrix from a CMD_LoadMatrix command. The
      // database's name for it (?UpdateFrame@CSystemCommands@RWS@@SAXAAURwFrame@@
      // PBURwMatrixTag@@@Z, the Studio sources' matrix overload) is a
      // signature match: its only caller (sub_1330B0) passes the command
      // from the iterator, and it copies the matrix from the command's data
      // (+8).
      static void UpdateFrame(RwFrame &rFrame, const CAttributeCommand &rAttrCmd);
   };

   // The atomics' solid flag, a plugin of RpAtomic.
   namespace RpAtomicCollisionProperties
   {
      RwBool PluginAttach();

      void SetIsSolid( RpAtomic& atomic, bool isSolid );

      bool GetIsSolid( const RpAtomic& atomic );
   }
}

#endif
