// StopSoundStreamTrigger: its MakeNew, constructor, destructor and handlers.
// Its original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/data.h"
#include "types/musicplayer.h"
#include "types/StopSoundStreamTrigger.h"

RWS_IMPLEMENT_CLASSID(StopSoundStreamTrigger);
RWS_REGISTERCLASS(StopSoundStreamTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BH@FACCNGM@StopSoundStreamTrigger?$AA@ @ 0x003D664C
// match: ??_7StopSoundStreamTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6664
// match: ??_7StopSoundStreamTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D666C
// match: __ehhandler$?MakeNew@StopSoundStreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C280
// match: __ehhandler$?MakeNew@StopSoundStreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C288
// match: .CRT$XCU+0 @ 0x00426F70
// match: ?pStopSoundStreamTriggerClassID@StopSoundStreamTrigger@@2PBDB @ 0x004291C0

// match: _$E2 @ 0x0030AB70
// match: _$E3 @ 0x0030E1A0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@StopSoundStreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000BA9E0
// match: __ehhandler$?MakeNew@StopSoundStreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300450
// match: __ehhandler$?MakeNew@StopSoundStreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030045F
// sp-match: ?MakeNew@StopSoundStreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0008F070
RWS_DEFINE_MAKENEW(StopSoundStreamTrigger)

// match: ??0StopSoundStreamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000BAA60
// sp-match: ??0StopSoundStreamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0008EDD0
StopSoundStreamTrigger::StopSoundStreamTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
}

// match: ?vf_008@StopSoundStreamTrigger@@UAEHXZ @ 0x000BAA90
// sp-match: ?vf_008@StopSoundStreamTrigger@@UAEHXZ @ 0x001232E0

// match: ??_GStopSoundStreamTrigger@@UAEPAXI@Z @ 0x000BAAA0
// sp-match: ??_GStopSoundStreamTrigger@@UAEPAXI@Z @ 0x0008F060

// match: ??1StopSoundStreamTrigger@@UAE@XZ @ 0x000BAAC0
// sp-match: ??1StopSoundStreamTrigger@@UAE@XZ @ 0x0008EDF0
// (Defined in the class, in StopSoundStreamTrigger.h.)

// Command 0: its player and the fade's length.
// match: ?HandleAttributes@StopSoundStreamTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BAAF0
// sp-match: ?HandleAttributes@StopSoundStreamTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0008EE10
void StopSoundStreamTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(StopSoundStreamTrigger));
    while (!attrIt.IsFinished())
    {
        const RwInt32 *var_C;

        switch (attrIt->GetCommandId())
        {
        case 0:
            var_C = (const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            unk_C0 = *var_C;
            var_C++;
            unk_C4 = *var_C;
            if (unk_C4 < 1)
            {
                unk_C4 = 1;
            }
            break;
        }
        ++attrIt;
    }
}

// match: ?vf_030@StopSoundStreamTrigger@@UAEXXZ @ 0x000BABB0
// sp-match: ?vf_030@StopSoundStreamTrigger@@UAEXXZ @ 0x0008EEB0
void StopSoundStreamTrigger::vf_030()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 8; var_4++)
    {
        dword_44E8D8[unk_C0].unk_190[var_4] = 0.0f;
        dword_44E8D8[unk_C0].unk_1D0[var_4] = 1.0f / unk_C4;
    }
    dword_44E8D8[unk_C0].unk_184 = 1;
}

// match: ??_EStopSoundStreamTrigger@@WBI@AEPAXI@Z @ 0x000BAC40
// sp-match: ??_EStopSoundStreamTrigger@@WBI@AEPAXI@Z @ 0x0008F050

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@StopSoundStreamTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void StopSoundStreamTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
