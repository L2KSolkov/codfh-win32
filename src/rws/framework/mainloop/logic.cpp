// RenderWare Studio's main loop logic (the game framework's
// framework/mainloop/logic.cpp): the running and frozen modes and the tick
// messages sent each frame. The image's version has no Paused (its messages
// are still registered) and no debug metrics.

#include "rw/ostypes.h"
#include "rw/bastream.h"
#include "rws/ceventhandler.h"
#include "rws/streamhandler.h"
#include "rws/strfunc.h"
#include "rws/mainloop.h"
// Its data definitions (PLAN M5), in the image's address order: the event names
// are named constants (the image has them before the literals, in this order).
// 0x003DAA30
extern const RwChar iMsgSetRunningMode_name[] = "iMsgSetRunningMode";
// 0x003DAA44
extern const RwChar iMsgSetPausedMode_name[] = "iMsgSetPausedMode";
// 0x003DAA58
extern const RwChar iMsgSetFrozenMode_name[] = "iMsgSetFrozenMode";
// 0x003DAA6C
extern const RwChar iMsgRunningPreTick_name[] = "iMsgRunningPreTick";
// 0x003DAA80
extern const RwChar iMsgRunningTick_name[] = "iMsgRunningTick";
// 0x003DAA90
extern const RwChar iMsgRunningPostTick_name[] = "iMsgRunningPostTick";
// 0x003DAAA4
extern const RwChar iMsgPausedPreTick_name[] = "iMsgPausedPreTick";
// 0x003DAAB8
extern const RwChar iMsgPausedTick_name[] = "iMsgPausedTick";
// 0x003DAAC8
extern const RwChar iMsgPausedPostTick_name[] = "iMsgPausedPostTick";
// End of its data definitions.

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?iMsgSetRunningMode_name@@3QBDB @ 0x003DAA30
// match: ?iMsgSetPausedMode_name@@3QBDB @ 0x003DAA44
// match: ?iMsgSetFrozenMode_name@@3QBDB @ 0x003DAA58
// match: ?iMsgRunningPreTick_name@@3QBDB @ 0x003DAA6C
// match: ?iMsgRunningTick_name@@3QBDB @ 0x003DAA80
// match: ?iMsgRunningPostTick_name@@3QBDB @ 0x003DAA90
// match: ?iMsgPausedPreTick_name@@3QBDB @ 0x003DAAA4
// match: ?iMsgPausedTick_name@@3QBDB @ 0x003DAAB8
// match: ?iMsgPausedPostTick_name@@3QBDB @ 0x003DAAC8
// match: ??_C@_08LDHPHGMD@RwUInt32?$AA@ @ 0x003DAADC
// match: .CRT$XCU+0 @ 0x004270BC
// match: .CRT$XCU+4 @ 0x004270C0
// match: .CRT$XCU+8 @ 0x004270C4
// match: .CRT$XCU+12 @ 0x004270C8
// match: .CRT$XCU+16 @ 0x004270CC
// match: .CRT$XCU+20 @ 0x004270D0
// match: .CRT$XCU+24 @ 0x004270D4
// match: .CRT$XCU+28 @ 0x004270D8
// match: .CRT$XCU+32 @ 0x004270DC
// match: .CRT$XCU+36 @ 0x004270E0
// match: .CRT$XCU+40 @ 0x004270E4
// match: .CRT$XCU+44 @ 0x004270E8
// match: ?gbEnabled@?A0xb63eaa10@Logic@MainLoop@RWS@@3HA @ 0x00429C30

// match: _$E1 @ 0x0030B8F0
// match: _$E2 @ 0x0030E6F0
// match: _$E4 @ 0x0030B910
// match: _$E5 @ 0x0030E700
// match: _$E7 @ 0x0030B930
// match: _$E8 @ 0x0030E710
// match: _$E10 @ 0x0030B950
// match: _$E11 @ 0x0030E720
// match: _$E13 @ 0x0030B970
// match: _$E14 @ 0x0030E730
// match: _$E16 @ 0x0030B990
// match: _$E17 @ 0x0030E740
// match: _$E19 @ 0x0030B9B0
// match: _$E20 @ 0x0030E750
// match: _$E22 @ 0x0030B9D0
// match: _$E23 @ 0x0030E760
// match: _$E25 @ 0x0030B9F0
// match: _$E26 @ 0x0030E770
// match: _$E28 @ 0x0030BA10
// match: _$E30 @ 0x0030BA20
// match: _$E32 @ 0x0030BA30

namespace RWS
{
   CEventId iMsgSetRunningMode;
   CEventId iMsgSetPausedMode;
   CEventId iMsgSetFrozenMode;
   CEventId iMsgRunningPreTick;
   CEventId iMsgRunningTick;
   CEventId iMsgRunningPostTick;
   CEventId iMsgPausedPreTick;
   CEventId iMsgPausedTick;
   CEventId iMsgPausedPostTick;

   namespace MainLoop
   {
      namespace Logic
      {
         namespace
         {
            RwInt32 frame_number = 0;
            CMsg msg_MsgPreTick;
            CMsg msg_MsgTick;
            CMsg msg_MsgPostTick;
            RwBool gbEnabled = TRUE;
         }
      }
   }
}

// match: ?Running@Logic@MainLoop@RWS@@YAXXZ @ 0x00131B60
void RWS::MainLoop::Logic::Running(void)
         {
            SendMsg(iMsgSetRunningMode);

            msg_MsgPreTick.Id.p_msgrec = iMsgRunningPreTick.p_msgrec;
            msg_MsgTick.Id.p_msgrec = iMsgRunningTick.p_msgrec;
            msg_MsgPostTick.Id.p_msgrec = iMsgRunningPostTick.p_msgrec;
         }

// match: ?Frozen@Logic@MainLoop@RWS@@YAXXZ @ 0x00131BC0
void RWS::MainLoop::Logic::Frozen(void)
         {
            SendMsg(iMsgSetFrozenMode);

            msg_MsgPreTick.Id.p_msgrec = ERROR_NOT_A_VALID_MESSAGE_ID;
            msg_MsgTick.Id.p_msgrec = ERROR_NOT_A_VALID_MESSAGE_ID;
            msg_MsgPostTick.Id.p_msgrec = ERROR_NOT_A_VALID_MESSAGE_ID;
         }

// match: ?SetEnabled@Logic@MainLoop@RWS@@YAXH@Z @ 0x00131C20
void RWS::MainLoop::Logic::SetEnabled(RwBool benabled)
         {
            gbEnabled = benabled;
         }

// match: ?Poll@Logic@MainLoop@RWS@@YAXXZ @ 0x00131C30
void RWS::MainLoop::Logic::Poll(void)
         {
            if (!gbEnabled) return;

            SendMsg(msg_MsgPreTick);

            msg_MsgTick.pData = reinterpret_cast<void*>(frame_number);
            frame_number++;

            SendMsg(msg_MsgTick);

            SendMsg(msg_MsgPostTick);

            CEventHandler::DeleteEventHandlers(iMsgDeleteEntity);
         }

// match: ?Open@Logic@MainLoop@RWS@@YAXXZ @ 0x00131CD0
void RWS::MainLoop::Logic::Open(void)
         {
            CEventHandler::RegisterMsg (iMsgSetRunningMode, iMsgSetRunningMode_name, 0);
            CEventHandler::RegisterMsg (iMsgSetPausedMode, iMsgSetPausedMode_name, 0);
            CEventHandler::RegisterMsg (iMsgSetFrozenMode, iMsgSetFrozenMode_name, 0);
            CEventHandler::RegisterMsg (iMsgRunningPreTick, iMsgRunningPreTick_name, 0);
            CEventHandler::RegisterMsg (iMsgRunningTick, iMsgRunningTick_name, "RwUInt32");
            CEventHandler::RegisterMsg (iMsgRunningPostTick, iMsgRunningPostTick_name, 0);
            CEventHandler::RegisterMsg (iMsgPausedPreTick, iMsgPausedPreTick_name, 0);
            CEventHandler::RegisterMsg (iMsgPausedTick, iMsgPausedTick_name, "RwUInt32");
            CEventHandler::RegisterMsg (iMsgPausedPostTick, iMsgPausedPostTick_name, 0);
         }

// match: ?Close@Logic@MainLoop@RWS@@YAXXZ @ 0x00131D90
void RWS::MainLoop::Logic::Close(void)
         {
            CEventHandler::UnRegisterMsg ( iMsgSetRunningMode );
            CEventHandler::UnRegisterMsg ( iMsgSetPausedMode );
            CEventHandler::UnRegisterMsg ( iMsgSetFrozenMode );
            CEventHandler::UnRegisterMsg ( iMsgRunningPreTick );
            CEventHandler::UnRegisterMsg ( iMsgRunningTick );
            CEventHandler::UnRegisterMsg ( iMsgRunningPostTick );
            CEventHandler::UnRegisterMsg ( iMsgPausedPreTick );
            CEventHandler::UnRegisterMsg ( iMsgPausedTick );
            CEventHandler::UnRegisterMsg ( iMsgPausedPostTick );
         }

// match: ?SetFrozenMode@?A0xb63eaa10@Logic@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00131E10
namespace RWS
{
   namespace MainLoop
   {
      namespace Logic
      {
         namespace
         {
            void SetFrozenMode (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
            {
               MainLoop::Logic::Frozen();
            }
         }
      }
   }
}

// match: ?SetRunningMode@?A0xb63eaa10@Logic@MainLoop@RWS@@YAXAAURwChunkHeaderInfo@@PAURwStream@@@Z @ 0x00131E20
namespace RWS
{
   namespace MainLoop
   {
      namespace Logic
      {
         namespace
         {
            void SetRunningMode (RwChunkHeaderInfo &rChunkHeader, RwStream *pStream)
            {
               MainLoop::Logic::Running();
            }
         }
      }
   }
}

// match: ?RegisterStreamChunkHandlers@Logic@MainLoop@RWS@@YAXXZ @ 0x00131E30
void RWS::MainLoop::Logic::RegisterStreamChunkHandlers(void)
         {
            CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
               strfunc_SetFrozenMode), SetFrozenMode);

            CStreamHandler::RegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM,
               strfunc_SetRunningMode), SetRunningMode);
         }

// match: ?UnRegisterStreamChunkHandlers@Logic@MainLoop@RWS@@YAXXZ @ 0x00131E60
void RWS::MainLoop::Logic::UnRegisterStreamChunkHandlers(void)
         {
            CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_SetFrozenMode));
            CStreamHandler::UnRegisterChunkHandler(MAKECHUNKID (rwVENDORID_CRITERIONRM, strfunc_SetRunningMode));
         }
