// SimpleMechanicTrigger: its MakeNew, constructor, destructor and handlers.
// Its original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/functions.h"
#include "types/SimpleMechanicTrigger.h"
#include "types/type_3DAC58.h"
#include "types/type_72810.h"

RWS_IMPLEMENT_CLASSID(SimpleMechanicTrigger);
RWS_REGISTERCLASS(SimpleMechanicTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BG@BJOKMCDK@SimpleMechanicTrigger?$AA@ @ 0x003D64A4
// match: ??_7SimpleMechanicTrigger@@6BCEventHandler@RWS@@@ @ 0x003D64BC
// match: ??_7SimpleMechanicTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D64C4
// match: __ehhandler$?MakeNew@SimpleMechanicTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C0D4
// match: __ehhandler$?MakeNew@SimpleMechanicTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C0DC
// match: .CRT$XCU+0 @ 0x00426F5C
// match: ?pSimpleMechanicTriggerClassID@SimpleMechanicTrigger@@2PBDB @ 0x004291AC

// match: _$E2 @ 0x0030AA80
// match: _$E3 @ 0x0030E150

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SimpleMechanicTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B7330
// match: __ehhandler$?MakeNew@SimpleMechanicTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003002D0
// match: __ehhandler$?MakeNew@SimpleMechanicTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003002DF
// sp-match: ?MakeNew@SimpleMechanicTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0008CAF0
RWS_DEFINE_MAKENEW(SimpleMechanicTrigger)

// match: ??0SimpleMechanicTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B73B0
// sp-match: ??0SimpleMechanicTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0008C660
SimpleMechanicTrigger::SimpleMechanicTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0.unk_00 = 0;
    unk_C0.unk_04 = 0;
    unk_C8.unk_00 = 0;
    unk_C8.unk_04 = 0;
    unk_D0.unk_00 = 0;
    unk_D0.unk_04 = 0;
    unk_E0 = 0;
    unk_E4 = 0;
    unk_F8 = 0;
    unk_FC = 1;
    unk_100 = 1;
    unk_104 = 1;
    unk_108 = 1;
}

// match: ?vf_008@SimpleMechanicTrigger@@UAEHXZ @ 0x000B7520
// sp-match: ?vf_008@SimpleMechanicTrigger@@UAEHXZ @ 0x0008C720

// match: ?vf_01C@SimpleMechanicTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x000B7530
// sp-match: ?vf_01C@SimpleMechanicTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x000977B0

// match: ??_GSimpleMechanicTrigger@@UAEPAXI@Z @ 0x000B7550
// sp-match: ??_GSimpleMechanicTrigger@@UAEPAXI@Z @ 0x0008CAE0

// match: ??1SimpleMechanicTrigger@@UAE@XZ @ 0x000B7570
// sp-match: ??1SimpleMechanicTrigger@@UAE@XZ @ 0x0008C730
// (Defined in the class, in SimpleMechanicTrigger.h.)

// Commands 3 and 4 first (the kind of names unk_E0 picks), then the rest.
// match: ?HandleAttributes@SimpleMechanicTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B75A0
// sp-match: ?HandleAttributes@SimpleMechanicTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0008C750
void SimpleMechanicTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    {
        RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(SimpleMechanicTrigger));
        while (!attrIt.IsFinished())
        {
            switch (attrIt->GetCommandId())
            {
            case 3:
                unk_E0 = attrIt->GetAs_RwInt32();
                break;
            case 4:
                unk_E4 = attrIt->GetAs_RwInt32();
                break;
            }
            ++attrIt;
        }
    }
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(SimpleMechanicTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_D8 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_D8.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_D8, 0x2E, 0, 0, 0, 0);
            }
            break;
        case 2:
            unk_C0 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_C0.unk_00 || unk_C0.unk_04)
            {
                if (!unk_E0)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_C0, 3, 0, 0, 0, 0);
                }
                else
                {
                    sub_198900((type_3DF8D8_04 *)&unk_C0, 0x30, 0, 0, 0, 0);
                }
            }
            break;
        case 5:
        {
            const type_3DF8D8_04 *var_14 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            unk_C8 = *var_14;
            if (var_14->unk_00 || var_14->unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_C8, 0xA, 0, 0, 0, 0);
            }
            break;
        }
        case 6:
        {
            const type_3DF8D8_04 *var_18 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_18->unk_00)
            {
                unk_D0 = *var_18;
                sub_198900((type_3DF8D8_04 *)&unk_D0, 0xC, 0, 0, 0, 0);
            }
            break;
        }
        case 8:
        {
            type_3DF8D8_04 var_20 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_20.unk_00 || var_20.unk_04)
            {
                unk_E8 = var_20;
            }
            break;
        }
        case 9:
            unk_F0 = attrIt->GetAs_RwInt32();
            break;
        case 7:
            unk_F4 = attrIt->GetAs_RwInt32();
            break;
        case 10:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_28 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_28.unk_00 || var_28.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_28, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_F8, 0);
                }
            }
            break;
        case 11:
            unk_FC = attrIt->GetAs_RwInt32();
            break;
        case 12:
            unk_100 = attrIt->GetAs_RwInt32();
            break;
        case 13:
            unk_104 = attrIt->GetAs_RwInt32();
            break;
        case 14:
            unk_108 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?vf_020@SimpleMechanicTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000B7A40
// sp-match: ?vf_020@SimpleMechanicTrigger@@UAEPAUtype_3D3548@@XZ @ 0x0008CAA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *SimpleMechanicTrigger::vf_020()
{
    type_3D3548 *var_8;
    type_3DF8D8 *l4;

    var_8 = 0;
    l4 = sub_198800(&unk_C0);
    if (!l4)
    {
    }
    else
    {
        var_8 = sub_133230((type_712B0 *)this);
    }
    return var_8;
}

// match: ??_ESimpleMechanicTrigger@@WBI@AEPAXI@Z @ 0x000B7A90
// sp-match: ??_ESimpleMechanicTrigger@@WBI@AEPAXI@Z @ 0x0008CAD0

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@SimpleMechanicTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void SimpleMechanicTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
