// CCESSPoolTrigger, the CCESS pool manager: its MakeNew, constructor and
// destructor. Its original file name is not in the image, so it is named for
// its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/CCESSPoolTrigger.h"

RWS_IMPLEMENT_CLASSID(CCESSPoolTrigger);
RWS_REGISTERCLASS(CCESSPoolTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@BHFGADHO@CCESSPoolTrigger?$AA@ @ 0x003D5C1C
// match: ??_7CCESSPoolTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5C30
// match: ??_7CCESSPoolTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5C38
// match: __ehhandler$?MakeNew@CCESSPoolTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BB0C
// match: __ehhandler$?MakeNew@CCESSPoolTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BB14
// match: .CRT$XCU+0 @ 0x00426F00
// match: ?pCCESSPoolTriggerClassID@CCESSPoolTrigger@@2PBDB @ 0x00429144

// match: _$E2 @ 0x0030A630
// match: _$E3 @ 0x0030DFE0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CCESSPoolTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A23F0
// match: __ehhandler$?MakeNew@CCESSPoolTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFDD0
// match: __ehhandler$?MakeNew@CCESSPoolTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFDDF
// sp-match: ?MakeNew@CCESSPoolTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0007F2E0
RWS_DEFINE_MAKENEW(CCESSPoolTrigger)

// match: ??0CCESSPoolTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A2470
// sp-match: ??0CCESSPoolTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0007EE90
CCESSPoolTrigger::CCESSPoolTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    RwInt32 var_4;
    RwInt32 var_8;

    for (var_8 = 0; var_8 < 2; var_8++)
    {
        for (var_4 = 0; var_4 < 5; var_4++)
        {
            unk_C0[var_8].unk_00[var_4] = 0;
            unk_C0[var_8].unk_14[var_4] = 0.0f;
            unk_C0[var_8].unk_3C[var_4] = 0;
        }
    }
}

// match: ?vf_008@CCESSPoolTrigger@@UAEHXZ @ 0x000A2530
// sp-match: ?vf_008@CCESSPoolTrigger@@UAEHXZ @ 0x00123B50

// Its settings: commands 0 to 8, the most trackers for each index (the second
// kind's in the odd ones); 9, 10, 13, 14, 17, 18, 21, 22 and 25, the delays,
// in seconds; 11, 12, 15, 16, 19, 20, 23, 24 and 27, the picks a round; 26,
// whether the last index's delay is random. Setting the first kind's last
// index clears the second kind's.
// match: ?HandleAttributes@CCESSPoolTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A2590
// sp-match: ?HandleAttributes@CCESSPoolTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0007EF10
void CCESSPoolTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CCESSPoolTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0[0].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 1:
            unk_C0[1].unk_00[0] = attrIt->GetAs_RwInt32();
            break;
        case 2:
            unk_C0[0].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_C0[1].unk_00[1] = attrIt->GetAs_RwInt32();
            break;
        case 4:
            unk_C0[0].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 5:
            unk_C0[1].unk_00[2] = attrIt->GetAs_RwInt32();
            break;
        case 6:
            unk_C0[0].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 7:
            unk_C0[1].unk_00[3] = attrIt->GetAs_RwInt32();
            break;
        case 8:
            unk_C0[0].unk_00[4] = attrIt->GetAs_RwInt32();
            unk_C0[1].unk_00[4] = 0;
            break;
        case 9:
            unk_C0[0].unk_14[0] = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 10:
            unk_C0[1].unk_14[0] = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 13:
            unk_C0[0].unk_14[1] = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 14:
            unk_C0[1].unk_14[1] = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 17:
            unk_C0[0].unk_14[2] = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 18:
            unk_C0[1].unk_14[2] = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 26:
            unk_C0[0].unk_28[4] = attrIt->GetAs_RwInt32();
            unk_C0[1].unk_28[4] = 0;
            break;
        case 25:
            unk_C0[0].unk_14[4] = attrIt->GetAs_RwReal() * 60.0f;
            unk_C0[1].unk_14[4] = 0.0f;
            break;
        case 21:
            unk_C0[0].unk_14[3] = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 22:
            unk_C0[1].unk_14[3] = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 11:
            unk_C0[0].unk_3C[0] = attrIt->GetAs_RwInt32();
            break;
        case 12:
            unk_C0[1].unk_3C[0] = attrIt->GetAs_RwInt32();
            break;
        case 15:
            unk_C0[0].unk_3C[1] = attrIt->GetAs_RwInt32();
            break;
        case 16:
            unk_C0[1].unk_3C[1] = attrIt->GetAs_RwInt32();
            break;
        case 19:
            unk_C0[0].unk_3C[2] = attrIt->GetAs_RwInt32();
            break;
        case 20:
            unk_C0[1].unk_3C[2] = attrIt->GetAs_RwInt32();
            break;
        case 23:
            unk_C0[0].unk_3C[3] = attrIt->GetAs_RwInt32();
            break;
        case 24:
            unk_C0[1].unk_3C[3] = attrIt->GetAs_RwInt32();
            break;
        case 27:
            unk_C0[0].unk_3C[4] = attrIt->GetAs_RwInt32();
            unk_C0[1].unk_3C[4] = 0;
            break;
        }
        ++attrIt;
    }
}

// It passes its events to Trigger's. /OPT:ICF folds the other triggers' like
// it (AnimPackTrigger's, ConfinedAreaTrigger's and more) into this one.
// match: ?HandleEvents@CCESSPoolTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000A2BF0
// sp-match: ?HandleEvents@CCESSPoolTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x00080E00
void CCESSPoolTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// match: ??_ECCESSPoolTrigger@@WBI@AEPAXI@Z @ 0x000A2C10
// sp-match: ??_ECCESSPoolTrigger@@WBI@AEPAXI@Z @ 0x0007F2C0

// match: ??_GCCESSPoolTrigger@@UAEPAXI@Z @ 0x000A2540
// sp-match: ??_GCCESSPoolTrigger@@UAEPAXI@Z @ 0x0007F2D0

// match: ??1CCESSPoolTrigger@@UAE@XZ @ 0x000A2560
// sp-match: ??1CCESSPoolTrigger@@UAE@XZ @ 0x0007EEF0
// (Defined in the class, in CCESSPoolTrigger.h.)
