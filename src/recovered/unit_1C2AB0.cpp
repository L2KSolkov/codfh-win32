// cNetTriggerViewControl, a RenderWare Studio behaviour
// (types/cNetTriggerViewControl.h): MakeNew, its constructor, destructor
// and attributes, which send the network triggers' visibility settings.
// Its original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/cNetTriggerViewControl.h"
#include "game/fileio.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E3480
extern const RwReal flt_3E3480 = 0.01f;
// 0x004FD6D4
sNetTriggerVisibility unk_4FD6D4;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(cNetTriggerViewControl);
RWS_REGISTERCLASS(cNetTriggerViewControl);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BH@MALGDBKD@cNetTriggerViewControl?$AA@ @ 0x003E3468
// match: ?flt_3E3480@@3MB @ 0x003E3480
// match: ??_7cNetTriggerViewControl@@6BCEventHandler@RWS@@@ @ 0x003E3484
// match: ??_7cNetTriggerViewControl@@6BCAttributeHandler@RWS@@@ @ 0x003E348C
// match: __ehhandler$?MakeNew@cNetTriggerViewControl@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041F354
// match: __ehhandler$?MakeNew@cNetTriggerViewControl@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041F35C
// match: __ehhandler$??0cNetTriggerViewControl@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041F378
// match: __ehhandler$??0cNetTriggerViewControl@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041F390
// match: __ehhandler$??1cNetTriggerViewControl@@UAE@XZ>1>8 @ 0x0041F3AC
// match: __ehhandler$??1cNetTriggerViewControl@@UAE@XZ>1 @ 0x0041F3C4
// match: .CRT$XCU+0 @ 0x00427208
// match: ?pcNetTriggerViewControlClassID@cNetTriggerViewControl@@2PBDB @ 0x0042CBA4

// match: _$E2 @ 0x0030C3A0
// match: _$E3 @ 0x0030EB20

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@cNetTriggerViewControl@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x001C2AB0
// match: __ehhandler$?MakeNew@cNetTriggerViewControl@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00302FF0
// match: __ehhandler$?MakeNew@cNetTriggerViewControl@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00302FFF
RWS_DEFINE_MAKENEW(cNetTriggerViewControl)

// match: ??0cNetTriggerViewControl@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x001C2B30
// match: __ehhandler$??0cNetTriggerViewControl@@QAE@ABVCAttributePacket@RWS@@@Z-0x1E @ 0x00303010
// match: __ehhandler$??0cNetTriggerViewControl@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0030302E
cNetTriggerViewControl::cNetTriggerViewControl(const RWS::CAttributePacket &attr)
{
    unk_24 = 1;
    unk_28 = 1;
    unk_2C = 1;
    unk_30 = 0;
    unk_34 = 0;
    RWS::CEventHandler::RegisterMsg(unk_38, "kujuUpdateTriggerObjectVisibility", "sNetTriggerVisibility *");
}

// match: ??_GcNetTriggerViewControl@@UAEPAXI@Z @ 0x001C2C40

// match: ??1cNetTriggerViewControl@@UAE@XZ @ 0x001C2C60
// match: __ehhandler$??1cNetTriggerViewControl@@UAE@XZ-0x3A @ 0x00303040
// match: __ehhandler$??1cNetTriggerViewControl@@UAE@XZ @ 0x0030307A
cNetTriggerViewControl::~cNetTriggerViewControl()
{
    RWS::CEventHandler::UnRegisterMsg(unk_38);
}

// Any command sends the settings: copied into the message's data
// (unk_4FD6D4) and sent to the network triggers.
// match: ?HandleAttributes@cNetTriggerViewControl@@UAEXABVCAttributePacket@RWS@@@Z @ 0x001C2D00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void cNetTriggerViewControl::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwInt32 l4 = 0;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(cNetTriggerViewControl));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            l4 = 1;
            sub_1C2E80(attrIt);
            break;
        case 1:
            l4 = 1;
            sub_1C2EB0(attrIt);
            break;
        case 2:
            l4 = 1;
            sub_1C2EE0(attrIt);
            break;
        case 3:
            l4 = 1;
            sub_1C2F10(attrIt);
            break;
        case 4:
            l4 = 1;
            sub_1C2F50(attrIt);
            break;
        default:
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Unknown renderware studio attribute\n");
        }
        ++attrIt;
    }
    if (l4)
    {
        unk_4FD6D4.unk_00 = unk_24;
        unk_4FD6D4.unk_04 = unk_28;
        unk_4FD6D4.unk_08 = unk_2C;
        unk_4FD6D4.unk_0C = unk_30;
        unk_4FD6D4.unk_10 = unk_34;
        RWS::CMsg msg(unk_38.p_msgrec, &unk_4FD6D4);

        RWS::SendMsg(msg);
    }
}

// match: ?sub_1C2E80@cNetTriggerViewControl@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C2E80
void cNetTriggerViewControl::sub_1C2E80(RWS::CAttributeCommandIterator &arg_0)
{
    arg_0->GetCommandData(unk_24);
}

// match: ?sub_1C2EB0@cNetTriggerViewControl@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C2EB0
void cNetTriggerViewControl::sub_1C2EB0(RWS::CAttributeCommandIterator &arg_0)
{
    arg_0->GetCommandData(unk_28);
}

// match: ?sub_1C2EE0@cNetTriggerViewControl@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C2EE0
void cNetTriggerViewControl::sub_1C2EE0(RWS::CAttributeCommandIterator &arg_0)
{
    arg_0->GetCommandData(unk_2C);
}

// match: ?sub_1C2F10@cNetTriggerViewControl@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C2F10
void cNetTriggerViewControl::sub_1C2F10(RWS::CAttributeCommandIterator &arg_0)
{
    RwInt32 var_4 = arg_0->GetAs_RwInt32();

    if (var_4 == -1)
        unk_30 = 1;
    else
        unk_30 = 0;
}

// match: ?sub_1C2F50@cNetTriggerViewControl@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001C2F50
void cNetTriggerViewControl::sub_1C2F50(RWS::CAttributeCommandIterator &arg_0)
{
    unk_34 = arg_0->GetAs_RwInt32();
}

// The CEventHandler part's deleting destructor thunk (sub ecx, 0x18).
// match: ??_EcNetTriggerViewControl@@WBI@AEPAXI@Z @ 0x001C2F80
