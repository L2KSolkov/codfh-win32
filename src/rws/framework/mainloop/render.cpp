// RenderWare Studio's main loop render (the game framework's
// framework/mainloop/render.cpp) as the game has it: without the design
// build's director's camera and without showing the raster (the game's main
// render, sub_125F20, shows it), and with a second camera (the sub-raster
// camera MainLoop::Open makes for Rt2d; its accessors have no name of their
// own: the database gives both pairs GetCamera and SetCamera). The empty
// chunk handler registrations are folded into sub_19A750 (config/aliases.txt).

#include "rw/ostypes.h"
#include "rw/baengine.h"
#include "rws/ceventhandler.h"
#include "rws/mainloop.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DAB08
extern const RwReal flt_3DAB08 = 16.666666f;
// 0x003DAB0C
extern const RwChar iMsgDoRender_name[] = "iMsgDoRender";
// 0x003DAB1C
extern const RwChar iMsgDoRenderDirectorsCamera_name[] = "iMsgDoRenderDirectorsCamera";
// 0x003DAB38
extern const RwChar iMsgPreShowRaster_name[] = "iMsgPreShowRaster";
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DAB08@@3MB @ 0x003DAB08
// match: ?iMsgDoRender_name@@3QBDB @ 0x003DAB0C
// match: ?iMsgDoRenderDirectorsCamera_name@@3QBDB @ 0x003DAB1C
// match: ?iMsgPreShowRaster_name@@3QBDB @ 0x003DAB38
// match: ??_C@_09LNHFAMCO@RwCamera?$CK?$AA@ @ 0x003DAB4C
// match: .CRT$XCU+0 @ 0x004270F4
// match: .CRT$XCU+4 @ 0x004270F8
// match: .CRT$XCU+8 @ 0x004270FC
// match: .CRT$XCU+12 @ 0x00427100
// match: .CRT$XCU+16 @ 0x00427104
// match: .CRT$XCU+20 @ 0x00427108
// match: ?gbEnabled@?A0x14691289@Render@MainLoop@RWS@@3HA @ 0x00429C34

// match: _$E1 @ 0x0030BA80
// match: _$E2 @ 0x0030E7A0
// match: _$E4 @ 0x0030BAA0
// match: _$E5 @ 0x0030E7B0
// match: _$E7 @ 0x0030BAC0
// match: _$E8 @ 0x0030E7C0
// match: _$E10 @ 0x0030BAE0
// match: _$E11 @ 0x0030E7D0
// match: _$E13 @ 0x0030BB00
// match: _$E14 @ 0x0030E7E0
// match: _$E16 @ 0x0030BB20
// match: _$E17 @ 0x0030E7F0
// sp-match: _$E1 @ 0x0021DA80
// sp-match: _$E4 @ 0x0021DAA0
// sp-match: _$E13 @ 0x0021DB00
// sp-match: _$E2 @ 0x0021EB70
// sp-match: _$E5 @ 0x0021EB80
// sp-match: _$E14 @ 0x0021EBB0

namespace RWS
{
   CEventId iMsgDoRender;
   CEventId iMsgDoRenderDirectorsCamera;

   // Never registered or sent in the image, but defined (their
   // initializers and exit functions remain); named as in the stock
   // RenderWare Studio framework, whose order they follow.
   CEventId iMsg_SetEnableDirectorsCamera;
   CEventId iMsg_SetDisableDirectorsCamera;
   CEventId iMsgPreShowRaster;

   CEventId iMsgRequestCurrentCameraMatrix;

   namespace MainLoop
   {
      namespace Render
      {
         namespace
         {
            RwBool gbEnabled = TRUE;
            RwCamera *g_pCamera;
            RwCamera *g_pCamera_0;
            RwUInt32 sm_frame_count = 0;
         }
      }
   }
}

// match: ?GetCamera@Render@MainLoop@RWS@@YAPAURwCamera@@XZ @ 0x001323B0
// sp-match: ?GetCamera@Render@MainLoop@RWS@@YAPAURwCamera@@XZ @ 0x000E2E20
RwCamera *RWS::MainLoop::Render::GetCamera(void) {return g_pCamera;}

// match: ?sub_1323C0@Render@MainLoop@RWS@@YAPAURwCamera@@XZ @ 0x001323C0
// sp-match: ?sub_1323C0@Render@MainLoop@RWS@@YAPAURwCamera@@XZ @ 0x000E2E30
RwCamera *RWS::MainLoop::Render::sub_1323C0(void) {return g_pCamera_0;}

// match: ?SetCamera@Render@MainLoop@RWS@@YAXQAURwCamera@@@Z @ 0x001323D0
// sp-match: ?SetCamera@Render@MainLoop@RWS@@YAXQAURwCamera@@@Z @ 0x000E2E40
void RWS::MainLoop::Render::SetCamera(RwCamera * const pCamera) {g_pCamera = pCamera;}

// match: ?sub_1323E0@Render@MainLoop@RWS@@YAXQAURwCamera@@@Z @ 0x001323E0
// sp-match: ?sub_1323E0@Render@MainLoop@RWS@@YAXQAURwCamera@@@Z @ 0x000E2E50
void RWS::MainLoop::Render::sub_1323E0(RwCamera * const pCamera) {g_pCamera_0 = pCamera;}

// match: ?Open@Render@MainLoop@RWS@@YAXXZ @ 0x001323F0
// sp-match: ?Open@Render@MainLoop@RWS@@YAXXZ @ 0x000E2E60
void RWS::MainLoop::Render::Open(void)
         {
            CEventHandler::RegisterMsg(iMsgDoRender, iMsgDoRender_name, "RwCamera*");
            CEventHandler::RegisterMsg(iMsgDoRenderDirectorsCamera, iMsgDoRenderDirectorsCamera_name, "RwCamera*");
            CEventHandler::RegisterMsg(iMsgPreShowRaster, iMsgPreShowRaster_name, "RwCamera*");
         }

// match: ?Close@Render@MainLoop@RWS@@YAXXZ @ 0x00132440
// sp-match: ?Close@Render@MainLoop@RWS@@YAXXZ @ 0x000E2EA0
void RWS::MainLoop::Render::Close(void)
         {
            CEventHandler::UnRegisterMsg(iMsgDoRender);
            CEventHandler::UnRegisterMsg(iMsgDoRenderDirectorsCamera);
            CEventHandler::UnRegisterMsg(iMsgPreShowRaster);
         }

// match: ?SetEnabled@Render@MainLoop@RWS@@YAXH@Z @ 0x00132470
// sp-match: ?SetEnabled@Render@MainLoop@RWS@@YAXH@Z @ 0x000E2ED0
void RWS::MainLoop::Render::SetEnabled(RwBool bEnabled)
         {
            gbEnabled = bEnabled;
         }

// match: ?Poll@Render@MainLoop@RWS@@YAXXZ @ 0x00132480
// sp-match: ?Poll@Render@MainLoop@RWS@@YAXXZ @ 0x000E2EE0
void RWS::MainLoop::Render::Poll(void)
         {
            if (!gbEnabled) return;

            sm_frame_count++;

            CMsg Msg(iMsgDoRender, MainLoop::Render::GetCamera());
            SendMsg(Msg);

            CMsg PreFlipMessage(iMsgPreShowRaster, MainLoop::Render::GetCamera());
            SendMsg(PreFlipMessage);
         }

// Empty in the image's build (no design-time chunk handlers); folded into
// sub_19A750.
void RWS::MainLoop::Render::RegisterStreamChunkHandlers(void)
         {
         }

void RWS::MainLoop::Render::UnRegisterStreamChunkHandlers(void)
         {
         }
