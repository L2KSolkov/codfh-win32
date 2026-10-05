// PickupTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/PickupTrigger.h"
#include "types/type_3D3548.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D5F38
extern const RwReal flt_3D5F38 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(PickupTrigger);
RWS_REGISTERCLASS(PickupTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@BHEFKLGK@PickupTrigger?$AA@ @ 0x003D5F28
// match: ?flt_3D5F38@@3MB @ 0x003D5F38
// match: ??_7PickupTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5F3C
// match: ??_7PickupTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5F44
// match: __ehhandler$?MakeNew@PickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BE3C
// match: __ehhandler$?MakeNew@PickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BE44
// match: __ehhandler$??0PickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041BE60
// match: __ehhandler$??0PickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041BE68
// match: __ehhandler$??1PickupTrigger@@UAE@XZ>1>8 @ 0x0041BE84
// match: __ehhandler$??1PickupTrigger@@UAE@XZ>1 @ 0x0041BE8C
// match: .CRT$XCU+0 @ 0x00426F34
// match: ?pPickupTriggerClassID@PickupTrigger@@2PBDB @ 0x00429178

// match: _$E2 @ 0x0030A8A0
// match: _$E3 @ 0x0030E0B0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@PickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A93B0
// match: __ehhandler$?MakeNew@PickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003000B0
// match: __ehhandler$?MakeNew@PickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003000BF
RWS_DEFINE_MAKENEW(PickupTrigger)

// Its handler serves the destructor too (folded by /OPT:ICF).
// match: ??0PickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A9430
// match: __ehhandler$??0PickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x003000D0
// match: __ehhandler$??0PickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x003000D8
PickupTrigger::PickupTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0 = -1;
    unk_C4 = 0;
    unk_C8 = 1;
    unk_CC = -60.0f;
    unk_D0 = 0.0f;
    unk_D4 = 0;
    unk_D8 = -1;
    LinkMsg(dword_4B67B8, 0, 0x8000);
}

// match: ?vf_008@PickupTrigger@@UAEHXZ @ 0x000A9500

// match: ??_GPickupTrigger@@UAEPAXI@Z @ 0x000A9510

// match: ??1PickupTrigger@@UAE@XZ @ 0x000A9530
PickupTrigger::~PickupTrigger()
{
    unk_D4 = 0;
    UnLinkMsg(RWS::iMsgRunningTick);
    UnLinkMsg(dword_4B67B8);
}

// Commands 5 and 6 set flags of Trigger's unk_24 (0x40000 when 5 is set,
// 0x80000 when 6 is not); the rest set its own.
// match: ?HandleAttributes@PickupTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A95B0
void PickupTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(PickupTrigger));
    while (!attrIt.IsFinished())
    {
        RwInt32 var_C;

        switch (attrIt->GetCommandId())
        {
        case 5:
            var_C = attrIt->GetAs_RwInt32();
            if (var_C)
            {
                unk_24 |= 0x40000; // not an address: a flag bit
            }
            break;
        case 6:
            var_C = attrIt->GetAs_RwInt32();
            if (!var_C)
            {
                unk_24 |= 0x80000; // not an address: a flag bit
            }
            break;
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
            unk_CC = attrIt->GetAs_RwInt32() * 60.0f;
            break;
        case 4:
            unk_DC = attrIt->GetAs_RwInt32();
            unk_D8 = unk_DC;
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@PickupTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000A9770
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void PickupTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    RwReal *var_10;
    RwReal var_C;
    type_3D3548 *bp_8;
    RwReal *bp_4;

    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == RWS::iMsgRunningTick.p_msgrec)
    {
        if (unk_D4)
        {
            unk_D0 = deltaTime + unk_D0;
            if (unk_D0 > unk_CC)
            {
                bp_8 = sub_1745A0(0);
                bp_4 = &unk_90;
                var_10 = bp_8->vf_0C4();
                var_C = (var_10[0] - bp_4[0]) * (var_10[0] - bp_4[0]) +
                        (var_10[1] - bp_4[1]) * (var_10[1] - bp_4[1]) +
                        (var_10[2] - bp_4[2]) * (var_10[2] - bp_4[2]);
                if (var_C < 25000000.0f)
                {
                    vf_020();
                    UnLinkMsg(RWS::iMsgRunningTick);
                }
                else
                {
                    unk_D0 = 0.0f;
                }
            }
        }
    }
    else if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
        unk_D8 = unk_DC;
    }
}

// match: ?vf_020@PickupTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000A98C0
type_3D3548 *PickupTrigger::vf_020()
{
    if (unk_D8)
    {
        unk_D8--;
        unk_D4 = 0;
        return sub_FA9E0(this);
    }
    return 0;
}

// match: ?sub_A9910@PickupTrigger@@QAEXXZ @ 0x000A9910
void PickupTrigger::sub_A9910()
{
    if (unk_CC > 0.0f && !unk_D4)
    {
        unk_D4 = 1;
        unk_D0 = 0.0f;
        LinkMsg(RWS::iMsgRunningTick, 0, 0x8000);
    }
}

// match: ??_EPickupTrigger@@WBI@AEPAXI@Z @ 0x000A9970
