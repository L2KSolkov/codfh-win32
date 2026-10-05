// CustomTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/CustomTrigger.h"
#include "types/type_3D51C0.h"
#include "types/type_72810.h"

RWS_IMPLEMENT_CLASSID(CustomTrigger);
RWS_REGISTERCLASS(CustomTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@HPDOMEAK@CustomTrigger?$AA@ @ 0x003D5CB4
// match: ??_7CustomTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5CC4
// match: ??_7CustomTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5CCC
// match: __ehhandler$?MakeNew@CustomTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BB54
// match: __ehhandler$?MakeNew@CustomTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BB5C
// match: __ehhandler$??0CustomTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041BB78
// match: __ehhandler$??0CustomTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041BB80
// match: __ehhandler$??1CustomTrigger@@UAE@XZ>1>8 @ 0x0041BB9C
// match: __ehhandler$??1CustomTrigger@@UAE@XZ>1 @ 0x0041BBA4
// match: .CRT$XCU+0 @ 0x00426F08
// match: ?pCustomTriggerClassID@CustomTrigger@@2PBDB @ 0x0042914C

// match: _$E2 @ 0x0030A690
// match: _$E3 @ 0x0030E000

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CustomTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A2DD0
// match: __ehhandler$?MakeNew@CustomTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFE10
// match: __ehhandler$?MakeNew@CustomTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFE1F
RWS_DEFINE_MAKENEW(CustomTrigger)

// match: ??0CustomTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A2E50
// match: __ehhandler$??0CustomTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x002FFE30
// match: __ehhandler$??0CustomTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x002FFE38
CustomTrigger::CustomTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    RwInt32 var_10;

    unk_104 = 0;
    unk_108 = 0;
    memset(unk_10C, 0, 6);
    memset(unk_112, 0, 6);
    for (var_10 = 0; var_10 < 2; var_10++)
    {
        unk_10C[var_10 + 4] = 1;
        unk_112[var_10 + 4] = 1;
    }
    sub_A30F0(&unk_C0);
}

// match: ??_GCustomTrigger@@UAEPAXI@Z @ 0x000A2F50

// match: ??0type_A2F70@@QAE@XZ @ 0x000A2F70
// (Written by the compiler.)

// match: ??1CustomTrigger@@UAE@XZ @ 0x000A3080
// match: __ehhandler$??1CustomTrigger@@UAE@XZ-0x8 @ 0x002FFE50
// match: __ehhandler$??1CustomTrigger@@UAE@XZ @ 0x002FFE58
CustomTrigger::~CustomTrigger()
{
    sub_A30F0(&unk_C0);
}

// match: ?sub_A30F0@CustomTrigger@@QAEXPAUtype_A2F70@@@Z @ 0x000A30F0
void CustomTrigger::sub_A30F0(type_A2F70 *arg_0)
{
    if (unk_104)
    {
        sub_145790(unk_104);
    }
    if (unk_108)
    {
        sub_145790(unk_108);
    }
    memset(arg_0, 0, 0x40);
}

// Commands 0 and 1: names (1 only when set) of the kinds 0xA and 0xC;
// 2 and 3: its two blocks; 4 to 7: keys of the kind 3, when set; 8 and 9:
// names whose words go to unk_10C and unk_112.
// match: ?HandleAttributes@CustomTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A3150
void CustomTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CustomTrigger));
    while (!attrIt.IsFinished())
    {
        const type_3DF8D8_04 *var_C;
        const type_3DF8D8_04 *var_10;

        switch (attrIt->GetCommandId())
        {
        case 0:
            var_C = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            unk_C0.unk_30 = *var_C;
            sub_198900((type_3DF8D8_04 *)&unk_C0.unk_30, 0xA, 0, 0, 0, 0);
            break;
        case 1:
            var_10 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (var_10->unk_00)
            {
                unk_C0.unk_38 = *var_10;
                sub_198900((type_3DF8D8_04 *)&unk_C0.unk_38, 0xC, 0, 0, 0, 0);
            }
            break;
        case 2:
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_104);
            break;
        case 3:
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_108);
            break;
        case 8:
        {
            Trigger_key var_18 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            sub_198900((type_3DF8D8_04 *)&var_18, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8E0, 0, (RwInt32)&unk_10C[2], 0);
            break;
        }
        case 9:
        {
            Trigger_key var_20 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            sub_198900((type_3DF8D8_04 *)&var_20, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8E0, 0, (RwInt32)&unk_112[2], 0);
            break;
        }
        case 4:
            unk_C0.unk_00[0] = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_C0.unk_00[0].unk_00 || unk_C0.unk_00[0].unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_C0.unk_00[0], 3, 0, 0, 0, 0);
            }
            break;
        case 5:
            unk_C0.unk_00[1] = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_C0.unk_00[1].unk_00 || unk_C0.unk_00[1].unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_C0.unk_00[1], 3, 0, 0, 0, 0);
            }
            break;
        case 6:
            unk_C0.unk_10[0] = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_C0.unk_10[0].unk_00 || unk_C0.unk_10[0].unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_C0.unk_10[0], 3, 0, 0, 0, 0);
            }
            break;
        case 7:
            unk_C0.unk_10[1] = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_C0.unk_10[1].unk_00 || unk_C0.unk_10[1].unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&unk_C0.unk_10[1], 3, 0, 0, 0, 0);
            }
            break;
        default:
        {
            RwInt32 var_24 = 0;

            var_24++;
            break;
        }
        }
        ++attrIt;
    }
}

// match: ?vf_020@CustomTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000A34E0
type_3D3548 *CustomTrigger::vf_020()
{
    type_3D3548 *var_4 = sub_9AD40((type_712B0 *)this);

    return var_4;
}

// match: ??_ECustomTrigger@@WBI@AEPAXI@Z @ 0x000A3500

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@CustomTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void CustomTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
