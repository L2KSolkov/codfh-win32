// LevelScriptTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/LevelScriptTrigger.h"
#include "types/type_3DF8D8.h"
#include "types/type_72810.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6BE4
extern const RwReal flt_3D6BE4 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(LevelScriptTrigger);
RWS_REGISTERCLASS(LevelScriptTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BD@HHPEKDA@LevelScriptTrigger?$AA@ @ 0x003D6BD0
// match: ?flt_3D6BE4@@3MB @ 0x003D6BE4
// match: ??_7LevelScriptTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6BE8
// match: ??_7LevelScriptTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6BF0
// match: __ehhandler$?MakeNew@LevelScriptTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C76C
// match: __ehhandler$?MakeNew@LevelScriptTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C774
// match: __ehhandler$??1LevelScriptTrigger@@UAE@XZ>1>8 @ 0x0041C790
// match: __ehhandler$??1LevelScriptTrigger@@UAE@XZ>1 @ 0x0041C798
// match: __ehhandler$??0LevelScriptTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C7B4
// match: __ehhandler$??0LevelScriptTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C7BC
// match: .CRT$XCU+0 @ 0x00426FB4
// match: ?pLevelScriptTriggerClassID@LevelScriptTrigger@@2PBDB @ 0x00429204

// match: _$E2 @ 0x0030AEA0
// match: _$E3 @ 0x0030E2B0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@LevelScriptTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C66C0
// match: __ehhandler$?MakeNew@LevelScriptTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300840
// match: __ehhandler$?MakeNew@LevelScriptTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030084F
RWS_DEFINE_MAKENEW(LevelScriptTrigger)

// Its handler serves the destructor too (folded by /OPT:ICF).
// match: ??0LevelScriptTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C6740
// match: __ehhandler$??0LevelScriptTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x00300860
// match: __ehhandler$??0LevelScriptTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300868
LevelScriptTrigger::LevelScriptTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0 = 0;
    sub_16FFB0(this);
    LinkMsg(dword_4B8750, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ??_GLevelScriptTrigger@@UAEPAXI@Z @ 0x000C6800

// match: ??1LevelScriptTrigger@@UAE@XZ @ 0x000C6820
LevelScriptTrigger::~LevelScriptTrigger()
{
    if (unk_C0)
    {
        sub_BD350(&unk_C0);
    }
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// Registers a fixed name (a kind 0x31) first; command 0 is its script,
// commands 1 and 2 more names to register.
// match: ?HandleAttributes@LevelScriptTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C68C0
void LevelScriptTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(LevelScriptTrigger));
    type_3DF8D8_04 var_8;

    var_8.unk_00 = 0x813F5C23; // not an address: a name's key
    var_8.unk_04 = 0x3DB0F0C5; // not an address: a name's key
    sub_198900((type_3DF8D8_04 *)&var_8, 0x31, 0, 0, 0, 0);
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            if (unk_C0)
            {
                sub_BD350(&unk_C0);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_C0);
            break;
        case 1:
        {
            type_3DF8D8_04 var_18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_18.unk_00 && var_18.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&var_18, 0x31, 0, 0, 0, 0);
            }
            break;
        }
        case 2:
        {
            type_3DF8D8_04 var_20 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_20.unk_00 && var_20.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&var_20, 0x31, 0, 0, 0, 0);
            }
            break;
        }
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@LevelScriptTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000C6A30
void LevelScriptTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        UnLinkMsg(dword_4B8750);
    }
}

// match: ??_ELevelScriptTrigger@@WBI@AEPAXI@Z @ 0x000C6A70

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@LevelScriptTrigger@@UAEHXZ (folded into 0x1945A0)
RwInt32 LevelScriptTrigger::vf_008()
{
    return 0x1E;
}
