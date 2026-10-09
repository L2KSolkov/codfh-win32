// CPickupBehavior: its MakeNew, constructor, destructor and handler. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/CPickupBehavior.h"
#include "types/type_4C09B0.h"

RWS_IMPLEMENT_CLASSID(CPickupBehavior);
RWS_REGISTERCLASS(CPickupBehavior);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@FGIFAGOK@CPickupBehavior?$AA@ @ 0x003D6B08
// match: ??_7CPickupBehavior@@6BCEventHandler@RWS@@@ @ 0x003D6B18
// match: ??_7CPickupBehavior@@6BCAttributeHandler@RWS@@@ @ 0x003D6B20
// match: __ehhandler$?MakeNew@CPickupBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C660
// match: __ehhandler$?MakeNew@CPickupBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C668
// match: __ehhandler$??0CPickupBehavior@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C684
// match: __ehhandler$??0CPickupBehavior@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C694
// match: __ehhandler$??1CPickupBehavior@@UAE@XZ>1>8 @ 0x0041C6B0
// match: __ehhandler$??1CPickupBehavior@@UAE@XZ>1 @ 0x0041C6C0
// match: .CRT$XCU+0 @ 0x00426FA8
// match: ?pCPickupBehaviorClassID@CPickupBehavior@@2PBDB @ 0x004291F8

// match: _$E2 @ 0x0030AE10
// match: _$E3 @ 0x0030E280

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CPickupBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C5D70
// match: __ehhandler$?MakeNew@CPickupBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300760
// match: __ehhandler$?MakeNew@CPickupBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030076F
// sp-match: ?MakeNew@CPickupBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00096AB0
RWS_DEFINE_MAKENEW(CPickupBehavior)

// match: ??0CPickupBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C5DF0
// match: __ehhandler$??0CPickupBehavior@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x00300780
// match: __ehhandler$??0CPickupBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300793
// sp-match: ??0CPickupBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00096850
CPickupBehavior::CPickupBehavior(const RWS::CAttributePacket &attr)
{
    unk_24 = 0;
    LinkMsg(dword_4B8750, 0, 0x8000);
}

// match: ??_GCPickupBehavior@@UAEPAXI@Z @ 0x000C5ED0
// sp-match: ??_GCPickupBehavior@@UAEPAXI@Z @ 0x00096980

// match: ??1CPickupBehavior@@UAE@XZ @ 0x000C5EF0
// match: __ehhandler$??1CPickupBehavior@@UAE@XZ-0x2F @ 0x003007A0
// match: __ehhandler$??1CPickupBehavior@@UAE@XZ @ 0x003007CF
// sp-match: ??1CPickupBehavior@@UAE@XZ @ 0x000968D0
CPickupBehavior::~CPickupBehavior()
{
    UnLinkMsg(dword_4B8750);
}

// Command 0 picks the settings; commands 1 to 3 fill them.
// match: ?HandleAttributes@CPickupBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C5F80
// sp-match: ?HandleAttributes@CPickupBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00096990
void CPickupBehavior::HandleAttributes(const RWS::CAttributePacket &attr)
{
    type_4C09B0 *var_C;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator bp_8(attr, RWS_CLASSID_OF(CPickupBehavior));
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CPickupBehavior));
    while (!bp_8.IsFinished())
    {
        if (bp_8->GetCommandId() == 0)
        {
            unk_20 = bp_8->GetAs_RwInt32();
        }
        ++bp_8;
    }
    if (unk_20 == -1)
    {
        return;
    }
    var_C = sub_FB6C0(unk_20);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 1:
            attrIt->GetCommandData(var_C->unk_0C);
            break;
        case 2:
            var_C->unk_10 = *(const RwV3d *)attrIt->GetAs_RwChar_ptr();
            break;
        case 3:
            var_C->unk_1C = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            break;
        }
        ++attrIt;
    }
}

// On dword_4B8750 it sets unk_24, once. Folded (/OPT:ICF) into
// CWeaponBehavior's (sub_C47F0), which it is identical to.
void CPickupBehavior::HandleEvents(RWS::CMsg &pMsg)
{
    if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        unk_24 = 1;
        UnLinkMsg(dword_4B8750);
    }
}

// match: ??_ECPickupBehavior@@WBI@AEPAXI@Z @ 0x000C60D0
// sp-match: ??_ECPickupBehavior@@WBI@AEPAXI@Z @ 0x00096970
