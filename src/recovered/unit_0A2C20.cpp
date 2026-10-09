// ConfinedAreaTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/ConfinedAreaTrigger.h"

RWS_IMPLEMENT_CLASSID(ConfinedAreaTrigger);
RWS_REGISTERCLASS(ConfinedAreaTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BE@MPNEGOEK@ConfinedAreaTrigger?$AA@ @ 0x003D5C68
// match: ??_7ConfinedAreaTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5C7C
// match: ??_7ConfinedAreaTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5C84
// match: __ehhandler$?MakeNew@ConfinedAreaTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BB30
// match: __ehhandler$?MakeNew@ConfinedAreaTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BB38
// match: .CRT$XCU+0 @ 0x00426F04
// match: ?pConfinedAreaTriggerClassID@ConfinedAreaTrigger@@2PBDB @ 0x00429148

// match: _$E2 @ 0x0030A660
// match: _$E3 @ 0x0030DFF0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@ConfinedAreaTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A2C20
// match: __ehhandler$?MakeNew@ConfinedAreaTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFDF0
// match: __ehhandler$?MakeNew@ConfinedAreaTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFDFF
// sp-match: ?MakeNew@ConfinedAreaTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0007F430
RWS_DEFINE_MAKENEW(ConfinedAreaTrigger)

// match: ??0ConfinedAreaTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A2CA0
// sp-match: ??0ConfinedAreaTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0007F350
ConfinedAreaTrigger::ConfinedAreaTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
}

// match: ?vf_008@ConfinedAreaTrigger@@UAEHXZ @ 0x000A2CD0

// match: ??_GConfinedAreaTrigger@@UAEPAXI@Z @ 0x000A2CE0
// sp-match: ??_GConfinedAreaTrigger@@UAEPAXI@Z @ 0x0007F420

// match: ??1ConfinedAreaTrigger@@UAE@XZ @ 0x000A2D00
// sp-match: ??1ConfinedAreaTrigger@@UAE@XZ @ 0x0007F370
// (Defined in the class, in ConfinedAreaTrigger.h.)

// Command 0: a number, kept plus one.
// match: ?HandleAttributes@ConfinedAreaTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A2D30
// sp-match: ?HandleAttributes@ConfinedAreaTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0007F390
void ConfinedAreaTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(ConfinedAreaTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0 = attrIt->GetAs_RwInt32() + 1;
            break;
        }
        ++attrIt;
    }
}

// match: ??_EConfinedAreaTrigger@@WBI@AEPAXI@Z @ 0x000A2DC0
// sp-match: ??_EConfinedAreaTrigger@@WBI@AEPAXI@Z @ 0x0007F410

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@ConfinedAreaTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void ConfinedAreaTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
