// cNetStaticCamTrigger, a RenderWare Studio behaviour
// (types/cNetStaticCamTrigger.h): MakeNew, its constructor, destructor,
// attributes and event handler. Its original file name is not in the
// image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/cNetStaticCamTrigger.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/fileio.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifndef CODFH_SP // MP only: unreferenced constants single player does not emit (not in default.xbe; /O2 keeps them only while they are external)
// 0x003E33E8
extern const RwReal flt_3E33E8 = 0.01f;
// 0x003E33EC
extern const RwReal flt_3E33EC = 0.01f;
// 0x003E33F0
extern const RwReal flt_3E33F0 = 16.666666f;
#endif
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(cNetStaticCamTrigger);
RWS_REGISTERCLASS(cNetStaticCamTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BF@FGEJJJCI@cNetStaticCamTrigger?$AA@ @ 0x003E33D0
// match: ?flt_3E33E8@@3MB @ 0x003E33E8
// match: ?flt_3E33EC@@3MB @ 0x003E33EC
// match: ?flt_3E33F0@@3MB @ 0x003E33F0
// match: ??_7cNetStaticCamTrigger@@6BCEventHandler@RWS@@@ @ 0x003E33F4
// match: ??_7cNetStaticCamTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003E33FC
// match: __ehhandler$?MakeNew@cNetStaticCamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041F2B4
// match: __ehhandler$?MakeNew@cNetStaticCamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041F2BC
// match: __ehhandler$??1cNetStaticCamTrigger@@UAE@XZ>1>8 @ 0x0041F2D8
// match: __ehhandler$??1cNetStaticCamTrigger@@UAE@XZ>1 @ 0x0041F2E0
// match: __ehhandler$??0cNetStaticCamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041F2FC
// match: __ehhandler$??0cNetStaticCamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041F304
// match: .CRT$XCU+0 @ 0x00427204
// match: ?pcNetStaticCamTriggerClassID@cNetStaticCamTrigger@@2PBDB @ 0x0042CBA0

// match: _$E2 @ 0x0030C370
// match: _$E3 @ 0x0030EB10

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@cNetStaticCamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x001C2120
// match: __ehhandler$?MakeNew@cNetStaticCamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00302F80
// match: __ehhandler$?MakeNew@cNetStaticCamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00302F8F
RWS_DEFINE_MAKENEW(cNetStaticCamTrigger)

// Its handler serves the destructor too (folded by /OPT:ICF).
// match: ??0cNetStaticCamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x001C21A0
// match: __ehhandler$??0cNetStaticCamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x00302FA0
// match: __ehhandler$??0cNetStaticCamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00302FA8
cNetStaticCamTrigger::cNetStaticCamTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    LinkMsg(dword_4B8750, 0, 0x8000);
}

// match: ??_GcNetStaticCamTrigger@@UAEPAXI@Z @ 0x001C2220

// match: ??1cNetStaticCamTrigger@@UAE@XZ @ 0x001C2240
cNetStaticCamTrigger::~cNetStaticCamTrigger()
{
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(RWS::iMsgRunningTick);
}

// match: ?HandleAttributes@cNetStaticCamTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x001C22C0
void cNetStaticCamTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(cNetStaticCamTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0[0] = attrIt->GetAs_RwInt32();
            break;
        case 1:
            unk_C0[1] = attrIt->GetAs_RwInt32();
            break;
        case 2:
            unk_C0[2] = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_C0[3] = attrIt->GetAs_RwInt32();
            break;
        default:
            if (0)
                sub_1C8A30("Unknown renderware studio attribute\n");
        }
        ++attrIt;
    }
}

// At the game's start it becomes the manager's static camera and stops
// listening.
// match: ?HandleEvents@cNetStaticCamTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x001C23E0
void cNetStaticCamTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    if (pMsg.Id.p_msgrec == RWS::iMsgRunningTick.p_msgrec)
        return;
    if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        unk_4F7EB8.unk_234 = (type_4F7EB8_234 *)this;
        UnLinkMsg(dword_4B8750);
    }
}

// The CEventHandler part's deleting destructor thunk (sub ecx, 0x18).
// match: ??_EcNetStaticCamTrigger@@WBI@AEPAXI@Z @ 0x001C2430
