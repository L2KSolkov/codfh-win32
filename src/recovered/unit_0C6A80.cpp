// PlaySoundTrigger: its MakeNew, constructor, destructor and handler. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/PlaySoundTrigger.h"
#include "types/type_3D3548.h"

RWS_IMPLEMENT_CLASSID(PlaySoundTrigger);
RWS_REGISTERCLASS(PlaySoundTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@KJFMNIGC@PlaySoundTrigger?$AA@ @ 0x003D6C20
// match: ??_7PlaySoundTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6C34
// match: ??_7PlaySoundTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6C3C
// match: __ehhandler$?MakeNew@PlaySoundTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C7D8
// match: __ehhandler$?MakeNew@PlaySoundTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C7E0
// match: .CRT$XCU+0 @ 0x00426FB8
// match: ?pPlaySoundTriggerClassID@PlaySoundTrigger@@2PBDB @ 0x00429208

// match: _$E2 @ 0x0030AED0
// match: _$E3 @ 0x0030E2C0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@PlaySoundTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C6A80
// match: __ehhandler$?MakeNew@PlaySoundTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300880
// match: __ehhandler$?MakeNew@PlaySoundTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030088F
// sp-match: ?MakeNew@PlaySoundTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00097590
RWS_DEFINE_MAKENEW(PlaySoundTrigger)

// match: ??0PlaySoundTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C6B00
// sp-match: ??0PlaySoundTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00097340
PlaySoundTrigger::PlaySoundTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
}

// match: ??_GPlaySoundTrigger@@UAEPAXI@Z @ 0x000C6B50
// sp-match: ??_GPlaySoundTrigger@@UAEPAXI@Z @ 0x00097580

// match: ??1PlaySoundTrigger@@UAE@XZ @ 0x000C6B70
// sp-match: ??1PlaySoundTrigger@@UAE@XZ @ 0x00097380
PlaySoundTrigger::~PlaySoundTrigger()
{
}

// match: ?HandleAttributes@PlaySoundTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C6BA0
// sp-match: ?HandleAttributes@PlaySoundTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000973A0
void PlaySoundTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(PlaySoundTrigger));
    while (!attrIt.IsFinished())
    {
        const RwInt32 *var_C;

        switch (attrIt->GetCommandId())
        {
        case 2:
            var_C = (const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            unk_C4.unk_00 = *var_C;
            var_C++;
            unk_C4.unk_04 = *var_C;
            break;
        case 0:
            unk_C0 = attrIt->GetAs_RwInt32();
            break;
        case 1:
            unk_10C = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_110 = attrIt->GetAs_RwInt32();
            break;
        case 4:
            unk_114 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?vf_030@PlaySoundTrigger@@UAEXXZ @ 0x000C6CF0
// sp-match: ?vf_030@PlaySoundTrigger@@UAEXXZ @ 0x000974C0
void PlaySoundTrigger::vf_030()
{
    type_3D3548 *var_4;

    sub_19A750((type_3D3548 *)0, 1, unk_C4, 0);
    if ((unk_10C && !unk_24_6) || !unk_10C)
    {
        unk_24_6 = 1;
        if (!unk_110)
        {
            dword_4B1E98.sub_8A980(&unk_C4, 0, 0, (RwV3d *)&unk_90, unk_114, 0);
        }
        else
        {
            var_4 = sub_1745A0(0);
            if (var_4)
            {
                var_4->unk_1C0.sub_8A980(&unk_C4, 0, 0, var_4->sub_CD550(), unk_114, 0);
            }
        }
    }
}

// match: ??_EPlaySoundTrigger@@WBI@AEPAXI@Z @ 0x000C6DE0
// sp-match: ??_EPlaySoundTrigger@@WBI@AEPAXI@Z @ 0x00097570

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@PlaySoundTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xBB1B0)
// sp-match: ?HandleEvents@PlaySoundTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000974A0
void PlaySoundTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
        unk_24_6 = 0;
    }
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@PlaySoundTrigger@@UAEHXZ (folded into 0x1B3C10)
// sp-match: ?vf_008@PlaySoundTrigger@@UAEHXZ @ 0x00097370
RwInt32 PlaySoundTrigger::vf_008()
{
    return 13;
}
