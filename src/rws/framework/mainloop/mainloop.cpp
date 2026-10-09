// RenderWare Studio's main loop (the game framework's
// framework/mainloop/mainloop.cpp) as the game has it: its system messages
// also drive the game loop's level start (dword_4B8700 on, dword_4B8704 and
// dword_4B86FC), Reset restarts the game loop's modules while a level runs,
// Open makes a sub-raster camera beside the main one (the render's second
// camera, which Rt2d draws with), and the render is not polled here. The
// level load (sub_D83C0) calls Init, StopSystem and StartSystem directly.

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rw/baengine.h"
#include "rws/ceventhandler.h"
#include "rws/cattributehandler.h"
#include "rws/streamhandler.h"
#include "rws/cresourcemanager.h"
#include "rws/clinearmemorymanager.h"
#include "rws/strfunc.h"
#include "rws/mainloop.h"
#include "rws/camerahelper.h"
#include "rws/clumphelper.h"
#include "game/gameloop.h"
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0P@HKNDODAH@iMsgStopSystem?$AA@ @ 0x003DAAE8
// match: ??_C@_0BA@BDABNIDG@iMsgStartSystem?$AA@ @ 0x003DAAF8
// match: .CRT$XCU+0 @ 0x004270EC
// match: .CRT$XCU+4 @ 0x004270F0

// match: _$E2 @ 0x0030BA40
// match: _$E3 @ 0x0030E780
// match: _$E5 @ 0x0030BA60
// match: _$E6 @ 0x0030E790
// sp-match: _$E6 @ 0x0021EB60
// sp-match: _$E2 @ 0x0021DA40
// sp-match: _$E5 @ 0x0021DA60
// sp-match: _$E3 @ 0x0021EB50

namespace RWS
{
   CEventId iMsgStartSystem;
   CEventId iMsgStopSystem;

   namespace MainLoop
   {
      namespace
      {
         RwBool g_sysStartedFlag = FALSE;
      }
   }
}

// match: ?NewEntityCreatedCB@?A0x25f28fdd@MainLoop@RWS@@YAXXZ @ 0x00131E80
// sp-match: ?NewEntityCreatedCB@?A0x25f28fdd@MainLoop@RWS@@YAXXZ @ 0x000E2A20
namespace RWS
{
   namespace MainLoop
   {
      namespace
      {
         void NewEntityCreatedCB()
         {
            if (g_sysStartedFlag)
            {
               SendMsg(iMsgStartSystem);
            }

            if (dword_4B8700)
            {
               dword_4B8708 = 1;
            }
         }
      }
   }
}

// match: ?StartSystem@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00131EE0
// sp-match: ?StartSystem@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000E2A70
void RWS::MainLoop::StartSystem (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
         {
            SendMsg(iMsgStartSystem);

            g_sysStartedFlag = TRUE;

            dword_4B8700 = 1;
            dword_4B8704 = 0;
            dword_4B86FC--;

            MainLoop::Render::SetEnabled (TRUE);
            MainLoop::Logic::SetEnabled (TRUE);
         }

// match: ?StopSystem@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00131F60
// sp-match: ?StopSystem@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000E2AE0
void RWS::MainLoop::StopSystem (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
         {
            SendMsg(iMsgStopSystem);

            g_sysStartedFlag = FALSE;

            MainLoop::Render::SetEnabled (FALSE);
            MainLoop::Logic::SetEnabled (FALSE);
         }

// match: ?Reset@?A0x25f28fdd@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00131FC0
// sp-match: ?Reset@?A0x25f28fdd@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000E2B30
namespace RWS
{
   namespace MainLoop
   {
      namespace
      {
         void Reset (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
         {
            if (dword_4B8710)
            {
               sub_D7040(1);
               sub_D6820(1);
            }
            else
            {
               CEventHandler::DeleteEventHandlers(iMsgDeleteEventHandler);
               CAttributeHandler::Purge();
               CResourceManager::Purge();
            }
         }
      }
   }
}

// match: ?Init@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00132000
// sp-match: ?Init@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x000E2B70
void RWS::MainLoop::Init (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
         {
            CAttributeHandler::PurgeAll();
            CEventHandler::DeleteEventHandlers(iMsgDeleteEventHandler);
            CResourceManager::PurgeAll();

            dword_4B8700 = 0;
            dword_4B8704 = 0;
            dword_4B86FC++;
         }

// match: ?RegisterStreamChunkHandlers@MainLoop@RWS@@YAXXZ @ 0x00132040
// sp-match: ?RegisterStreamChunkHandlers@MainLoop@RWS@@YAXXZ @ 0x000E2BA0
void RWS::MainLoop::RegisterStreamChunkHandlers(void)
      {
         CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
            strfunc_StartSystem), StartSystem);

         CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
            strfunc_StopSystem), StopSystem);

         CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
            strfunc_Reset), Reset);

         CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
            strfunc_Initialize), Init);
      }

// match: ?UnRegisterStreamChunkHandlers@MainLoop@RWS@@YAXXZ @ 0x00132090
// sp-match: ?UnRegisterStreamChunkHandlers@MainLoop@RWS@@YAXXZ @ 0x000E2BE0
void RWS::MainLoop::UnRegisterStreamChunkHandlers(void)
      {
         CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_StartSystem));
         CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_StopSystem));
         CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_Reset));
         CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_Initialize));
      }

// match: ?Open@MainLoop@RWS@@YAXHHH@Z @ 0x001320D0
// sp-match: ?Open@MainLoop@RWS@@YAXHHH@Z @ 0x000E2C10
void RWS::MainLoop::Open(RwInt32 ScreenWidth, RwInt32 ScreenHeight, RwInt32 ZBitDepth)
      {
         RwCamera *pCamera = CameraHelper::CreateMainRasterCamera( ScreenWidth, ScreenHeight, ZBitDepth);

         MainLoop::Render::SetCamera( pCamera );

         dword_4B88B0 = pCamera;

         // The sub-raster camera, in a block of its own (its locals sit below
         // the main camera's).
         {
            RwRect rect;
            RwCamera *pSubRasterCamera;

            rect.w = ScreenWidth;
            rect.h = ScreenHeight;
            rect.x = rect.y = 0;

            pSubRasterCamera = CameraHelper::CreateSubRasterCamera(rect);

            RwCameraSetNearClipPlane(pSubRasterCamera, 1.0f);

            MainLoop::Render::sub_1323E0( pSubRasterCamera );
         }

         Rt2dOpen(MainLoop::Render::sub_1323C0());
         Rt2dAnimOpen();

         CEventHandler::Open (0, 0);
         CEventHandler::RegisterStreamChunkHandlers();
         CLinearMemoryManager::RegisterStreamChunkHandlers();
         CAttributeHandler::Open (NewEntityCreatedCB);
         CAttributeHandler::RegisterStreamChunkHandlers();
         CStreamHandler::RegisterStreamChunkHandlers();
         CResourceManager::Open();
         CResourceManager::RegisterStreamChunkHandlers();

         ClumpHelper::Open();

         Logic::Open();
         Logic::RegisterStreamChunkHandlers();
         Logic::Running();

         Render::Open();
         Render::RegisterStreamChunkHandlers();

         RegisterStreamChunkHandlers();

         CEventHandler::RegisterMsg(iMsgStartSystem, "iMsgStartSystem", 0);
         CEventHandler::RegisterMsg(iMsgStopSystem, "iMsgStopSystem", 0);
      }

// match: ?Close@MainLoop@RWS@@YAXXZ @ 0x001321E0
// sp-match: ?Close@MainLoop@RWS@@YAXXZ @ 0x000E2D60
void RWS::MainLoop::Close(void)
      {
         CEventHandler::UnRegisterMsg(iMsgStopSystem);
         CEventHandler::UnRegisterMsg(iMsgStartSystem);

         CStreamHandler::UnRegisterStreamChunkHandlers();

         Logic::UnRegisterStreamChunkHandlers();
         Logic::Close();

         Render::UnRegisterStreamChunkHandlers();
         Render::Close();

         ClumpHelper::Close();

         CAttributeHandler::UnRegisterStreamChunkHandlers();
         CAttributeHandler::Close ();

         CResourceManager::UnRegisterStreamChunkHandlers();
         CResourceManager::Close();

         CEventHandler::UnRegisterMsg(iMsgStartSystem);
         CEventHandler::UnRegisterMsg(iMsgStopSystem);

         CEventHandler::UnRegisterStreamChunkHandlers();

         CLinearMemoryManager::DestroyLinearMemoryManager();
         CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_PlacementNew));

         CEventHandler::Close ();

         Rt2dAnimClose();
         Rt2dClose();

         CameraHelper::Destroy(MainLoop::Render::GetCamera());
         MainLoop::Render::SetCamera(0);

         CameraHelper::Destroy(MainLoop::Render::sub_1323C0());
         MainLoop::Render::sub_1323E0(0);

         UnRegisterStreamChunkHandlers();
      }

// DestroyLinearMemoryManager (inline in rws/clinearmemorymanager.h), emitted
// for Close.
// match: ?DestroyLinearMemoryManager@CLinearMemoryManager@RWS@@SAXXZ @ 0x001322C0
// sp-match: ?DestroyLinearMemoryManager@CLinearMemoryManager@RWS@@SAXXZ @ 0x000E2D10

// The game's poll: the logic only (the main render draws itself).
// match: ?Poll@MainLoop@RWS@@YAXXZ @ 0x001323A0
// sp-match: ?Poll@MainLoop@RWS@@YAXXZ @ 0x000E2D00
void RWS::MainLoop::Poll(void)
      {
         Logic::Poll();
      }
