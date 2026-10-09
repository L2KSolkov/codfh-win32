// RenderWare Studio's plugin attachment (the game framework's
// framework/startup/attachplugins.cpp) as the game has it: RenderWare's
// plugins, RenderWare Studio's two atomic plugins and the game's own (the
// entity extensions of unit_0FB7A0 and the clump data plugin), from a table
// built on the stack, after sub_7FD70 (types/animkey.h); no compressed key
// frame registration.

#include "rw/ostypes.h"
#include "rws/ceventhandler.h"
#include "rws/csystemcommands.h"
#include "types/animkey.h"
#include "game/clumpdata.h"
#include "game/startup.h"

extern "C"
{
   RwBool RpWorldPluginAttach(void);
   RwBool RpCollisionPluginAttach(void);
   RwBool RpPVSPluginAttach(void);
   RwBool RpMorphPluginAttach(void);
   RwBool RpDMorphPluginAttach(void);
   RwBool RpPrtStdPluginAttach(void);
   RwBool RpSkinPluginAttach(void);
   RwBool RpHAnimPluginAttach(void);
   RwBool RpRandomPluginAttach(void);
   RwBool RpMatFXPluginAttach(void);
   RwBool RpPTankPluginAttach(void);
   RwBool RpLODAtomicPluginAttach(void);
   RwBool RpSplinePluginAttach(void);
   RwBool RpUserDataPluginAttach(void);
   RwBool RpUVAnimPluginAttach(void);
   RwBool RpMipmapKLPluginAttach(void);
   RwBool RpAnisotPluginAttach(void);
}

// The game's entity extension plugins (unit_0FB7A0).
RwInt32 sub_FB7C0();
RwInt32 sub_FBA30();
RwInt32 sub_FC500();
RwInt32 sub_FBDF0();
RwInt32 sub_FBC50();
RwInt32 sub_FC020();

// match: ?AttachPlugins@StartUp@RWS@@YA_NXZ @ 0x00132510
// sp-match: ?AttachPlugins@StartUp@RWS@@YA_NXZ @ 0x000E2F50
bool RWS::StartUp::AttachPlugins()
      {
         typedef RwBool (__cdecl *functor)(void);

         const functor plugins[] =
         {
            RpWorldPluginAttach,
            RpCollisionPluginAttach,
            RpPVSPluginAttach,
            RpMorphPluginAttach,
            RpDMorphPluginAttach,
            RpPrtStdPluginAttach,
            RpSkinPluginAttach,
            RpHAnimPluginAttach,
            RpRandomPluginAttach,
            RpMatFXPluginAttach,
            RpPTankPluginAttach,
            RpLODAtomicPluginAttach,
            RpSplinePluginAttach,
            RpUserDataPluginAttach,
            RpUVAnimPluginAttach,
            RpMipmapKLPluginAttach,
            RpAnisotPluginAttach,
            RpAtomicToEventHandler::PluginAttach,
            RpAtomicCollisionProperties::PluginAttach,
            sub_FB7C0,
            sub_FBA30,
            sub_FC500,
            sub_FBDF0,
            sub_FBC50,
            sub_FC020,
            sub_EBF10
         };

         if (!sub_7FD70())
         {
            return (false);
         }

         bool flag = true;

         for (RwUInt32 i = 0;i < sizeof(plugins) / sizeof(functor);i++)
         {
            if (!plugins[i]())
            {
               flag = false;
            }
         }

         return (flag);
      }
