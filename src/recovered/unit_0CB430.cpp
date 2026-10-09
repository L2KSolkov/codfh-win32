// PulseZoneTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/PulseZoneTrigger.h"
#include "types/type_72810.h"
#include "game/pooledconsts.h"
#include "game/frames.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6DDC
extern const RwReal flt_3D6DDC = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(PulseZoneTrigger);
RWS_REGISTERCLASS(PulseZoneTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@MMANLLFP@PulseZoneTrigger?$AA@ @ 0x003D6DC8
// match: ?flt_3D6DDC@@3MB @ 0x003D6DDC
// match: ??_7PulseZoneTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6DE0
// match: ??_7PulseZoneTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6DE8
// match: __ehhandler$?MakeNew@PulseZoneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041CA68
// match: __ehhandler$?MakeNew@PulseZoneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041CA70
// match: __ehhandler$??0PulseZoneTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041CA8C
// match: __ehhandler$??0PulseZoneTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041CA94
// match: __ehhandler$??1PulseZoneTrigger@@UAE@XZ>1>8 @ 0x0041CAB0
// match: __ehhandler$??1PulseZoneTrigger@@UAE@XZ>1 @ 0x0041CAB8
// match: .CRT$XCU+0 @ 0x00426FD4
// match: ?pPulseZoneTriggerClassID@PulseZoneTrigger@@2PBDB @ 0x00429224

// match: _$E2 @ 0x0030B020
// match: _$E3 @ 0x0030E330

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@PulseZoneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CB430
// match: __ehhandler$?MakeNew@PulseZoneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300AE0
// match: __ehhandler$?MakeNew@PulseZoneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300AEF
// sp-match: ?MakeNew@PulseZoneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0009A7F0
RWS_DEFINE_MAKENEW(PulseZoneTrigger)

// Its handler serves the destructor too (folded by /OPT:ICF).
// match: ??0PulseZoneTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CB4B0
// match: __ehhandler$??0PulseZoneTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x00300B00
// match: __ehhandler$??0PulseZoneTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300B08
// sp-match: ??0PulseZoneTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0009A460
PulseZoneTrigger::PulseZoneTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0 = 0;
    unk_C4 = 0;
    unk_C8 = -1;
    unk_CC = seconds_to_frames(1.0f);
    unk_D0 = 0;
    unk_D4 = 0;
    unk_D8 = 0;
    unk_DC = 0;
    unk_E0 = 0;
    LinkMsg(dword_4B8750, 0, 0x8000);
    LinkMsg(dword_4B67B0, 0, 0x8000);
}

// match: ??_GPulseZoneTrigger@@UAEPAXI@Z @ 0x000CB5C0
// sp-match: ??_GPulseZoneTrigger@@UAEPAXI@Z @ 0x0009A7E0

// match: ??1PulseZoneTrigger@@UAE@XZ @ 0x000CB5E0
// sp-match: ??1PulseZoneTrigger@@UAE@XZ @ 0x0009A520
PulseZoneTrigger::~PulseZoneTrigger()
{
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(dword_4B67B0);
}

// match: ?HandleAttributes@PulseZoneTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CB660
// sp-match: ?HandleAttributes@PulseZoneTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0009A590
void PulseZoneTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(PulseZoneTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 1:
            unk_C0 = attrIt->GetAs_RwInt32();
            break;
        case 0:
            unk_C4 = attrIt->GetAs_RwInt32();
            break;
        case 2:
            unk_C8 = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_CC = attrIt->GetAs_RwReal() * 60.0f;
            break;
        case 4:
            unk_D0 = attrIt->GetAs_RwInt32();
            break;
        case 5:
            unk_D4 = attrIt->GetAs_RwInt32();
            break;
        case 6:
            unk_E0 = attrIt->GetAs_RwInt32();
            break;
        case 7:
            if (attrIt->GetAs_RwChar_ptr())
            {
                type_3DF8D8_04 var_10 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

                if (var_10.unk_00 || var_10.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_10, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_DC, 0);
                }
            }
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@PulseZoneTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000CB850
// sp-match: ?HandleEvents@PulseZoneTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x0009A720
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void PulseZoneTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    type_17E3A0 var_8;
    type_17E3A0 l4;

    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == dword_4B67B0.p_msgrec)
    {
        l4 = sub_17E3A0(this);
        unk_D8 = sub_17E650(l4);
        if (unk_E0)
        {
            unk_D8->sub_17DB90(sub_F2FF0(unk_DC, (RwMatrix *)unk_60, 0, 1, 0, 0));
        }
    }
    else if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        var_8 = sub_17E3A0(this);
        unk_D8 = sub_17E650(var_8);
        if (unk_E0)
        {
            unk_D8->sub_17DB90(sub_F2FF0(unk_DC, (RwMatrix *)unk_60, 0, 1, 0, 0));
        }
    }
}

// match: ?sub_CB960@PulseZoneTrigger@@QAEXH@Z @ 0x000CB960
// sp-match: ?sub_CB960@PulseZoneTrigger@@QAEXH@Z @ 0x0009A790
void PulseZoneTrigger::sub_CB960(RwInt32 arg_0)
{
    if (unk_D8)
    {
        unk_D8->sub_17D940((type_3D3548 *)arg_0);
    }
}

// match: ?sub_CB990@PulseZoneTrigger@@QAEXH@Z @ 0x000CB990
// sp-match: ?sub_CB990@PulseZoneTrigger@@QAEXH@Z @ 0x0009A7B0
void PulseZoneTrigger::sub_CB990(RwInt32 arg_0)
{
    if (unk_D8)
    {
        unk_D8->sub_17DA20((type_3D3548 *)arg_0);
    }
}

// match: ??_EPulseZoneTrigger@@WBI@AEPAXI@Z @ 0x000CB9C0
// sp-match: ??_EPulseZoneTrigger@@WBI@AEPAXI@Z @ 0x0009A7D0

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@PulseZoneTrigger@@UAEHXZ (folded into 0x193FA0)
RwInt32 PulseZoneTrigger::vf_008()
{
    return 0x22;
}
