// StreamVolume: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/data.h"
#include "types/musicplayer.h"
#include "types/StreamVolume.h"

RWS_IMPLEMENT_CLASSID(StreamVolume);
RWS_REGISTERCLASS(StreamVolume);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0N@BDPADALD@StreamVolume?$AA@ @ 0x003D66EC
// match: ??_7StreamVolume@@6BCEventHandler@RWS@@@ @ 0x003D66FC
// match: ??_7StreamVolume@@6BCAttributeHandler@RWS@@@ @ 0x003D6704
// match: __ehhandler$?MakeNew@StreamVolume@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C2C8
// match: __ehhandler$?MakeNew@StreamVolume@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C2D0
// match: .CRT$XCU+0 @ 0x00426F78
// match: ?pStreamVolumeClassID@StreamVolume@@2PBDB @ 0x004291C8

// match: _$E2 @ 0x0030ABD0
// match: _$E3 @ 0x0030E1C0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@StreamVolume@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000BB380
// match: __ehhandler$?MakeNew@StreamVolume@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300490
// match: __ehhandler$?MakeNew@StreamVolume@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030049F
RWS_DEFINE_MAKENEW(StreamVolume)

// match: ??0StreamVolume@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000BB400
StreamVolume::StreamVolume(const RWS::CAttributePacket &attr) : Trigger(attr)
{
}

// match: ?vf_008@StreamVolume@@UAEHXZ @ 0x000BB430

// match: ??_GStreamVolume@@UAEPAXI@Z @ 0x000BB440

// match: ??1StreamVolume@@UAE@XZ @ 0x000BB460
// (Defined in the class, in StreamVolume.h.)

// match: ?HandleAttributes@StreamVolume@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BB490
void StreamVolume::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(StreamVolume));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0 = attrIt->GetAs_RwInt32();
            break;
        case 1:
            unk_C4[0] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 2:
            unk_C4[1] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 3:
            unk_C4[2] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 4:
            unk_C4[3] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 5:
            unk_C4[4] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 6:
            unk_C4[5] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 7:
            unk_C4[6] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 8:
            unk_C4[7] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 9:
            unk_E4[0] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 10:
            unk_E4[1] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 11:
            unk_E4[2] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 12:
            unk_E4[3] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 13:
            unk_E4[4] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 14:
            unk_E4[5] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 15:
            unk_E4[6] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 16:
            unk_E4[7] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        }
        ++attrIt;
    }
}

// match: ?vf_030@StreamVolume@@UAEXXZ @ 0x000BB860
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void StreamVolume::vf_030()
{
    RwInt32 var_8;
    RwReal l4;

    l4 = 0.0f;
    for (var_8 = 0; var_8 < 8; var_8++)
    {
        if (unk_C4[var_8])
        {
            l4 = unk_C4[var_8] / 100.0f;
        }
        else
        {
            l4 = 0.0f;
        }
        if (dword_44E8D8[unk_C0].unk_248)
        {
            l4 = dword_44E8D8[unk_C0].unk_248->unk_18 / 100.0f * l4;
        }
        if (l4 < 0.0)
        {
            l4 = 0.0f;
        }
        if (l4 > 1.0f)
        {
            l4 = 1.0f;
        }
        dword_44E8D8[unk_C0].unk_190[var_8] = l4;
        dword_44E8D8[unk_C0].unk_1F0[var_8] = l4;
        dword_44E8D8[unk_C0].unk_1D0[var_8] = 1.0f / unk_E4[var_8];
    }
}

// match: ??_EStreamVolume@@WBI@AEPAXI@Z @ 0x000BB9A0

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@StreamVolume@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void StreamVolume::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}
