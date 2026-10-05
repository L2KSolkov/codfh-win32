// DestructableObjectTrigger: its MakeNew, constructor, destructor and
// handlers. Its original file name is not in the image, so it is named for
// its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/CustomTrigger.h"
#include "types/DestructableObjectTrigger.h"
#include "types/type_72810.h"

RWS_IMPLEMENT_CLASSID(DestructableObjectTrigger);
RWS_REGISTERCLASS(DestructableObjectTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BK@HFHCDGGL@DestructableObjectTrigger?$AA@ @ 0x003D5CFC
// match: ??_7DestructableObjectTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5D18
// match: ??_7DestructableObjectTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5D20
// match: __ehhandler$?MakeNew@DestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BBC0
// match: __ehhandler$?MakeNew@DestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BBC8
// match: .CRT$XCU+0 @ 0x00426F0C
// match: ?pDestructableObjectTriggerClassID@DestructableObjectTrigger@@2PBDB @ 0x00429150

// match: _$E2 @ 0x0030A6C0
// match: _$E3 @ 0x0030E010

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@DestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A3510
// match: __ehhandler$?MakeNew@DestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFE70
// match: __ehhandler$?MakeNew@DestructableObjectTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFE7F
RWS_DEFINE_MAKENEW(DestructableObjectTrigger)

// match: ??0DestructableObjectTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A3590
DestructableObjectTrigger::DestructableObjectTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0.unk_00 = 0;
    unk_C0.unk_04 = 0;
    unk_C8.unk_00 = 0;
    unk_C8.unk_04 = 0;
    unk_D8 = 0;
    unk_DC = 0;
    unk_E0 = 0;
    unk_E4 = 1;
    unk_E8 = 1;
    unk_EC = 1;
    unk_F0 = 1;
    unk_F4 = 1;
}

// match: ??_GDestructableObjectTrigger@@UAEPAXI@Z @ 0x000A36C0

// match: ??1DestructableObjectTrigger@@UAE@XZ @ 0x000A36E0
DestructableObjectTrigger::~DestructableObjectTrigger()
{
}

// Commands 0 to 2: its names; 3 and 6 to 10: numbers; 4: a name whose value
// goes to unk_DC; 5: a block whose word at +0x14 it keeps (0 without one).
// match: ?HandleAttributes@DestructableObjectTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A3710
void DestructableObjectTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(DestructableObjectTrigger));
    while (!attrIt.IsFinished())
    {
        const type_3DF8D8_04 *var_C;
        const type_3DF8D8_04 *var_10;

        switch (attrIt->GetCommandId())
        {
        case 1:
            var_C = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            unk_C0 = *var_C;
            sub_198900((type_3DF8D8_04 *)&unk_C0, 0xA, 0, 0, 0, 0);
            break;
        case 0:
            unk_D0 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_D0.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_D0, 0x2E, 0, 0, 0, 0);
            }
            break;
        case 2:
            var_10 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (var_10->unk_00)
            {
                unk_C8 = *var_10;
                sub_198900((type_3DF8D8_04 *)&unk_C8, 0xC, 0, 0, 0, 0);
            }
            break;
        case 4:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_18 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_18.unk_00 || var_18.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_18, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_DC, 0);
                }
            }
            break;
        case 6:
            unk_E4 = attrIt->GetAs_RwInt32();
            break;
        case 7:
            unk_E8 = attrIt->GetAs_RwInt32();
            break;
        case 8:
            unk_EC = attrIt->GetAs_RwInt32();
            break;
        case 9:
            unk_F0 = attrIt->GetAs_RwInt32();
            break;
        case 10:
            unk_F4 = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_E0 = attrIt->GetAs_RwInt32();
            break;
        case 5:
        {
            RwUInt8 *var_1C = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_1C);
            if (var_1C)
            {
                unk_D8 = *(RwInt16 *)(var_1C + 0x14);
                sub_145790(var_1C);
            }
            else
            {
                unk_D8 = 0;
            }
            break;
        }
        }
        ++attrIt;
    }
}

// match: ??_EDestructableObjectTrigger@@WBI@AEPAXI@Z @ 0x000A3A30

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@DestructableObjectTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void DestructableObjectTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@DestructableObjectTrigger@@UAEHXZ (folded into 0x1A32A0)
RwInt32 DestructableObjectTrigger::vf_008()
{
    return 0x14;
}

// ?vf_01C@DestructableObjectTrigger@@UAEPAUtype_3DF8D8_04@@XZ (folded into 0xA17D0)
struct type_3DF8D8_04 *DestructableObjectTrigger::vf_01C()
{
    return &unk_D0;
}
