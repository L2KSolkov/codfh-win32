// RenderWare Studio's system commands (the game framework's
// framework/core/attributehandler/csystemcommands.cpp): the frame update
// from an entity's matrix command and the atomic collision properties
// plugin. The game's UpdateFrame takes the command and copies its matrix
// into the frame (the Studio sources' second overload, from a matrix, is not
// in the image); FindFirstResource and FindFirstResourceOfType are not in
// the image (unreferenced).

#include "rw/ostypes.h"
#include "rw/baframe.h"
#include "rw/bamatrix.h"
#include "rw/rpatomic.h"
#include "rws/cattributehandler.h"
#include "rws/csystemcommands.h"
#include "rws/strfunc.h"
#include "rws/atomiccollisionplugin.h"

namespace RWS
{
   RWS_IMPLEMENT_CLASSID(CSystemCommands);
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@GOHPAAOH@CSystemCommands?$AA@ @ 0x003DA98C
// match: ?pCSystemCommandsClassID@CSystemCommands@RWS@@2PBDB @ 0x00429C2C

// match: ?UpdateFrame@CSystemCommands@RWS@@SAXAAURwFrame@@ABVCAttributeCommand@2@@Z @ 0x0012DC20

void RWS::CSystemCommands::UpdateFrame(RwFrame &rFrame, const CAttributeCommand &rAttrCmd)
   {
      const RwMatrix* pUnalignedMat = static_cast<const RwMatrix*>(rAttrCmd.GetAs_void_ptr());

      RwMatrix *pMatrix = RwFrameGetMatrix(&rFrame);

      *pMatrix = *pUnalignedMat;

      RwMatrixOptimize(pMatrix, 0);

      RwFrameUpdateObjects(&rFrame);
   }

namespace RWS
{
   namespace RpAtomicCollisionProperties
   {
      namespace
      {
         RwUInt32 iPlugin_Offset = 0;

         inline PluginData* GetPluginData( RpAtomic& atomic )
         {
            const RwUInt32 baseAddr = reinterpret_cast<RwUInt32>(&atomic);
            const RwUInt32 pluginAddr = baseAddr + iPlugin_Offset;

            return ( reinterpret_cast<PluginData*>(pluginAddr) );
         }

         inline const PluginData *GetPluginData( const RpAtomic& atomic )
         {
            const RwUInt32 baseAddr = reinterpret_cast<RwUInt32>(&atomic);
            const RwUInt32 pluginAddr = baseAddr + iPlugin_Offset;

            return ( reinterpret_cast<const PluginData*>(pluginAddr) );
         }
      }
   }
}

// match: ?Plugin_Constructor@?A0x7854dc35@RpAtomicCollisionProperties@RWS@@YAPAXPAXHH@Z @ 0x0012DC70
namespace RWS
{
   namespace RpAtomicCollisionProperties
   {
      namespace
      {
         void* Plugin_Constructor(void* pObject, RwInt32 offsetInObject, RwInt32 sizeInObject)
         {
            PluginData& pluginData = *GetPluginData(*static_cast<RpAtomic*>(pObject));

            pluginData.m_isSolid = 1;

            return (pObject);
         }
      }
   }
}

// match: ?Plugin_Copy@?A0x7854dc35@RpAtomicCollisionProperties@RWS@@YAPAXPAXPBXHH@Z @ 0x0012DCB0
namespace RWS
{
   namespace RpAtomicCollisionProperties
   {
      namespace
      {
         void* Plugin_Copy(void* pDstObject, const void* pSrcObject, RwInt32 offset, RwInt32 size)
         {
            PluginData& srcData = *GetPluginData(*(RpAtomic*)pSrcObject);
            PluginData& dstData = *GetPluginData(*static_cast<RpAtomic*>(pDstObject));

            dstData = srcData;

            return (pDstObject);
         }
      }
   }
}

// match: ?PluginAttach@RpAtomicCollisionProperties@RWS@@YAHXZ @ 0x0012DD00
RwBool RWS::RpAtomicCollisionProperties::PluginAttach(void)
      {
         iPlugin_Offset = RpAtomicRegisterPlugin(
            sizeof(PluginData),
            MAKECHUNKID(rwVENDORID_CRITERIONRM, PluginID),
            Plugin_Constructor,
            0,
            Plugin_Copy
            );

         return (0 != iPlugin_Offset);
      }

// match: ?SetIsSolid@RpAtomicCollisionProperties@RWS@@YAXAAURpAtomic@@_N@Z @ 0x0012DD40
void RWS::RpAtomicCollisionProperties::SetIsSolid( RpAtomic& atomic, bool isSolid )
      {
         GetPluginData(atomic)->m_isSolid = isSolid?1:0;
      }

// match: ?GetIsSolid@RpAtomicCollisionProperties@RWS@@YA_NABURpAtomic@@@Z @ 0x0012DD80
bool RWS::RpAtomicCollisionProperties::GetIsSolid( const RpAtomic& atomic )
      {
         return (GetPluginData(atomic)->m_isSolid?true:false);
      }
