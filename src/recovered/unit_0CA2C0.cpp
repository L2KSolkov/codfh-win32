// CPoolSizes: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/alfaobjman.h"
#include "types/CPoolSizes.h"

RWS_IMPLEMENT_CLASSID(CPoolSizes);
RWS_REGISTERCLASS(CPoolSizes);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@PEHFGBCF@CPoolSizes?$AA@ @ 0x003D6CDC
// match: ??_7CPoolSizes@@6BCEventHandler@RWS@@@ @ 0x003D6CE8
// match: ??_7CPoolSizes@@6BCAttributeHandler@RWS@@@ @ 0x003D6CF0
// match: __ehhandler$?MakeNew@CPoolSizes@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C8F4
// match: __ehhandler$?MakeNew@CPoolSizes@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C8FC
// match: __ehhandler$??0CPoolSizes@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C918
// match: __ehhandler$??0CPoolSizes@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C928
// match: __ehhandler$??1CPoolSizes@@UAE@XZ>1>8 @ 0x0041C944
// match: __ehhandler$??1CPoolSizes@@UAE@XZ>1 @ 0x0041C954
// match: .CRT$XCU+0 @ 0x00426FC4
// match: ?pCPoolSizesClassID@CPoolSizes@@2PBDB @ 0x00429214

// match: _$E2 @ 0x0030AF60
// match: _$E3 @ 0x0030E2F0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CPoolSizes@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CA2C0
// match: __ehhandler$?MakeNew@CPoolSizes@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300980
// match: __ehhandler$?MakeNew@CPoolSizes@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030098F
RWS_DEFINE_MAKENEW(CPoolSizes)

// match: ??0CPoolSizes@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CA340
// match: __ehhandler$??0CPoolSizes@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x003009A0
// match: __ehhandler$??0CPoolSizes@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x003009B3
CPoolSizes::CPoolSizes(const RWS::CAttributePacket &attr)
    : unk_20(25), unk_24(30), unk_28(30), unk_2C(5), unk_30(0), unk_34(1), unk_38(15), unk_3C(10),
      unk_40(30)
{
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
}

// match: ??_GCPoolSizes@@UAEPAXI@Z @ 0x000CA470

// match: ??1CPoolSizes@@UAE@XZ @ 0x000CA490
// match: __ehhandler$??1CPoolSizes@@UAE@XZ-0x2F @ 0x003009C0
// match: __ehhandler$??1CPoolSizes@@UAE@XZ @ 0x003009EF
CPoolSizes::~CPoolSizes()
{
    UnLinkMsg(RWS::iMsgStartSystem);
}

// Commands 9 and 10: the task pool's size and the call records per task.
// match: ?HandleAttributes@CPoolSizes@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CA520
void CPoolSizes::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CPoolSizes));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 1:
            unk_24 = attrIt->GetAs_RwInt32();
            break;
        case 2:
            unk_28 = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_30 = attrIt->GetAs_RwInt32();
            break;
        case 4:
            unk_2C = attrIt->GetAs_RwInt32();
            break;
        case 6:
            unk_3C = attrIt->GetAs_RwInt32();
            break;
        case 7:
            unk_38 = attrIt->GetAs_RwInt32();
            if (unk_38 > 0x21)
            {
                unk_38 = 0x21;
            }
            break;
        case 8:
            unk_40 = attrIt->GetAs_RwInt32();
            break;
        case 5:
            unk_34 = attrIt->GetAs_RwInt32();
            break;
        case 0:
            unk_20 = attrIt->GetAs_RwInt32();
            break;
        case 9:
            dword_4498C8 = attrIt->GetAs_RwInt32();
            break;
        case 10:
            dword_449400 = attrIt->GetAs_RwReal();
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@CPoolSizes@@UAEXAAVCMsg@RWS@@@Z @ 0x000CA740
void CPoolSizes::HandleEvents(RWS::CMsg &pMsg)
{
    if (pMsg.Id.p_msgrec == RWS::iMsgStartSystem.p_msgrec)
    {
        sub_D5320(&unk_20);
        UnLinkMsg(RWS::iMsgStartSystem);
    }
}

// match: ??_ECPoolSizes@@WBI@AEPAXI@Z @ 0x000CA780
