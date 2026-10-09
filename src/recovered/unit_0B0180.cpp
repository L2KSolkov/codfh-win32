// SectionTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/SectionTrigger.h"

RWS_IMPLEMENT_CLASSID(SectionTrigger);
RWS_REGISTERCLASS(SectionTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0P@OPIBCGIO@SectionTrigger?$AA@ @ 0x003D63CC
// match: ??_7SectionTrigger@@6BCEventHandler@RWS@@@ @ 0x003D63DC
// match: ??_7SectionTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D63E4
// match: __ehhandler$?MakeNew@SectionTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BFD8
// match: __ehhandler$?MakeNew@SectionTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BFE0
// match: .CRT$XCU+0 @ 0x00426F4C
// match: ?pSectionTriggerClassID@SectionTrigger@@2PBDB @ 0x0042919C

// match: _$E2 @ 0x0030A9C0
// match: _$E3 @ 0x0030E110

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SectionTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B0180
// match: __ehhandler$?MakeNew@SectionTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003001F0
// match: __ehhandler$?MakeNew@SectionTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003001FF
// sp-match: ?MakeNew@SectionTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00088360
RWS_DEFINE_MAKENEW(SectionTrigger)

// match: ??0SectionTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B0200
// sp-match: ??0SectionTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000881E0
SectionTrigger::SectionTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0 = 0;
    unk_C4 = 0;
    unk_C8 = 0;
    unk_CC = 0;
    unk_D0 = 0;
}

// match: ??_GSectionTrigger@@UAEPAXI@Z @ 0x000B0270
// sp-match: ??_GSectionTrigger@@UAEPAXI@Z @ 0x00088350

// match: ??1SectionTrigger@@UAE@XZ @ 0x000B0290
// sp-match: ??1SectionTrigger@@UAE@XZ @ 0x00088230
// (Defined in the class, in SectionTrigger.h.)

// match: ?HandleAttributes@SectionTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B02C0
// sp-match: ?HandleAttributes@SectionTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00088250
void SectionTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(SectionTrigger));
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
        case 2:
            unk_C8 = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_CC = attrIt->GetAs_RwInt32();
            break;
        case 4:
            unk_D0 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ??_ESectionTrigger@@WBI@AEPAXI@Z @ 0x000B0400
// sp-match: ??_ESectionTrigger@@WBI@AEPAXI@Z @ 0x00088340

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_008@SectionTrigger@@UAEHXZ (folded into `return 4` at 0x9E000)
RwInt32 SectionTrigger::vf_008()
{
    return 4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@SectionTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void SectionTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
