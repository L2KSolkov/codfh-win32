// FogTrigger: its MakeNew, constructor, destructor and handler. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/functions.h"
#include "types/FogTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6EC0
extern const RwReal flt_3D6EC0 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(FogTrigger);
RWS_REGISTERCLASS(FogTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@OJPNDKNL@FogTrigger?$AA@ @ 0x003D6EB4
// match: ?flt_3D6EC0@@3MB @ 0x003D6EC0
// match: ??_7FogTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6EC4
// match: ??_7FogTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6ECC
// match: __ehhandler$?MakeNew@FogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041CB64
// match: __ehhandler$?MakeNew@FogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041CB6C
// match: .CRT$XCU+0 @ 0x00426FE0
// match: ?pFogTriggerClassID@FogTrigger@@2PBDB @ 0x00429230

// match: _$E2 @ 0x0030B0B0
// match: _$E3 @ 0x0030E360

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@FogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CC370
// match: __ehhandler$?MakeNew@FogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300BA0
// match: __ehhandler$?MakeNew@FogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300BAF
// sp-match: ?MakeNew@FogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0009B220
RWS_DEFINE_MAKENEW(FogTrigger)

// match: ??0FogTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CC3F0
// sp-match: ??0FogTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0009B070
FogTrigger::FogTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0 = 0;
    unk_C4 = 20000.0f;
    unk_C8 = 0.0f;
    unk_CC = 20000.0f;
    unk_D0 = 0.0f;
}

// match: ?vf_008@FogTrigger@@UAEHXZ @ 0x000CC460
// sp-match: ?vf_008@FogTrigger@@UAEHXZ @ 0x00124460

// match: ??_GFogTrigger@@UAEPAXI@Z @ 0x000CC470
// sp-match: ??_GFogTrigger@@UAEPAXI@Z @ 0x0009B210

// match: ??1FogTrigger@@UAE@XZ @ 0x000CC490
// sp-match: ??1FogTrigger@@UAE@XZ @ 0x0009B0C0
FogTrigger::~FogTrigger()
{
}

// match: ?HandleAttributes@FogTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CC4C0
// sp-match: ?HandleAttributes@FogTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0009B0E0
void FogTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(FogTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C4 = attrIt->GetAs_RwReal();
            break;
        case 1:
            unk_C8 = attrIt->GetAs_RwReal();
            break;
        case 2:
            unk_CC = attrIt->GetAs_RwReal();
            break;
        case 3:
            unk_D0 = attrIt->GetAs_RwReal();
            break;
        }
        ++attrIt;
    }
}

// match: ?sub_CC5D0@FogTrigger@@QAEXH@Z @ 0x000CC5D0
// sp-match: ?sub_CC5D0@FogTrigger@@QAEXH@Z @ 0x0009B1B0
void FogTrigger::sub_CC5D0(RwInt32 arg_0)
{
    unk_C0 = 1;
    sub_128C80(unk_C4, unk_C8 * 30.0f);
    sub_128CD0(unk_CC, unk_D0 * 30.0f);
}

// match: ??_EFogTrigger@@WBI@AEPAXI@Z @ 0x000CC640
// sp-match: ??_EFogTrigger@@WBI@AEPAXI@Z @ 0x0009B200

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@FogTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void FogTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
