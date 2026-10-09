// StreamClumpTrigger: its MakeNew, constructor, destructor and handler. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/functions.h"
#include "types/StreamClumpTrigger.h"
#include "types/type_10F710.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6B94
extern const RwReal flt_3D6B94 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(StreamClumpTrigger);
RWS_REGISTERCLASS(StreamClumpTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BD@EBPDBLF@StreamClumpTrigger?$AA@ @ 0x003D6B80
// match: ?flt_3D6B94@@3MB @ 0x003D6B94
// match: ??_7StreamClumpTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6B98
// match: ??_7StreamClumpTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6BA0
// match: __ehhandler$?MakeNew@StreamClumpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C748
// match: __ehhandler$?MakeNew@StreamClumpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C750
// match: .CRT$XCU+0 @ 0x00426FB0
// match: ?pStreamClumpTriggerClassID@StreamClumpTrigger@@2PBDB @ 0x00429200

// match: _$E2 @ 0x0030AE70
// match: _$E3 @ 0x0030E2A0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@StreamClumpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C64A0
// match: __ehhandler$?MakeNew@StreamClumpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300820
// match: __ehhandler$?MakeNew@StreamClumpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030082F
// sp-match: ?MakeNew@StreamClumpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00096F80
RWS_DEFINE_MAKENEW(StreamClumpTrigger)

// match: ??0StreamClumpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C6520
// sp-match: ??0StreamClumpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00096E50
StreamClumpTrigger::StreamClumpTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
}

// match: ??_GStreamClumpTrigger@@UAEPAXI@Z @ 0x000C6550
// sp-match: ??_GStreamClumpTrigger@@UAEPAXI@Z @ 0x00096F70

// match: ??1StreamClumpTrigger@@UAE@XZ @ 0x000C6570
// sp-match: ??1StreamClumpTrigger@@UAE@XZ @ 0x00096E70
StreamClumpTrigger::~StreamClumpTrigger()
{
}

// match: ?HandleAttributes@StreamClumpTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C65A0
// sp-match: ?HandleAttributes@StreamClumpTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00096E90
void StreamClumpTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(StreamClumpTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0 = attrIt->GetAs_RwInt32();
            break;
        case 1:
            unk_C4 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?sub_C6650@StreamClumpTrigger@@QAEXXZ @ 0x000C6650
// sp-match: ?sub_C6650@StreamClumpTrigger@@QAEXXZ @ 0x00096F20
void StreamClumpTrigger::sub_C6650()
{
    type_10F710 *var_4;

    if (!unk_C4)
    {
        sub_16EEC0(unk_C0);
    }
    else
    {
        var_4 = (type_10F710 *)sub_1745A0(0);
        if (var_4)
        {
            var_4->sub_10DA70(unk_C0);
        }
    }
}

// match: ??_EStreamClumpTrigger@@WBI@AEPAXI@Z @ 0x000C66B0
// sp-match: ??_EStreamClumpTrigger@@WBI@AEPAXI@Z @ 0x00096F60

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@StreamClumpTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void StreamClumpTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@StreamClumpTrigger@@UAEHXZ (folded into 0x1936A0)
RwInt32 StreamClumpTrigger::vf_008()
{
    return 0x1C;
}
