// PASTrigger: its MakeNew, constructor, destructor and handler. Its original
// file name is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/PASTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6F08
extern const RwReal flt_3D6F08 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(PASTrigger);
RWS_REGISTERCLASS(PASTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@INPHJGOO@PASTrigger?$AA@ @ 0x003D6EFC
// match: ?flt_3D6F08@@3MB @ 0x003D6F08
// match: ??_7PASTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6F0C
// match: ??_7PASTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6F14
// match: __ehhandler$?MakeNew@PASTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041CB88
// match: __ehhandler$?MakeNew@PASTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041CB90
// match: .CRT$XCU+0 @ 0x00426FE4
// match: ?pPASTriggerClassID@PASTrigger@@2PBDB @ 0x00429234

// match: _$E2 @ 0x0030B0E0
// match: _$E3 @ 0x0030E370

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@PASTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CC650
// match: __ehhandler$?MakeNew@PASTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300BC0
// match: __ehhandler$?MakeNew@PASTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300BCF
RWS_DEFINE_MAKENEW(PASTrigger)

// match: ??0PASTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CC6D0
PASTrigger::PASTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0 = 0;
    unk_C4 = 0;
}

// match: ?vf_008@PASTrigger@@UAEHXZ @ 0x000CC720

// match: ??_GPASTrigger@@UAEPAXI@Z @ 0x000CC730

// match: ??1PASTrigger@@UAE@XZ @ 0x000CC750
PASTrigger::~PASTrigger()
{
}

// match: ?HandleAttributes@PASTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CC780
void PASTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(PASTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            switch (attrIt->GetAs_RwInt32())
            {
            case 0:
                unk_C4 = 0;
                break;
            case 1:
                unk_C4 = 1;
                break;
            case 2:
                unk_C4 = 2;
                break;
            }
            break;
        }
        ++attrIt;
    }
}

// match: ?sub_CC850@PASTrigger@@QAEXH@Z @ 0x000CC850
void PASTrigger::sub_CC850(RwInt32 arg_0)
{
    unk_C0 = 1;
}

// match: ?sub_CC870@PASTrigger@@QAEXH@Z @ 0x000CC870
void PASTrigger::sub_CC870(RwInt32 arg_0)
{
    unk_C0 = 0;
}

// match: ??_EPASTrigger@@WBI@AEPAXI@Z @ 0x000CC890

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@PASTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void PASTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
