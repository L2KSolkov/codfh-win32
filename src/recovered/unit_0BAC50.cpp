// StreamTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/musicplayer.h"
#include "types/StreamTrigger.h"

RWS_IMPLEMENT_CLASSID(StreamTrigger);
RWS_REGISTERCLASS(StreamTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@COAOEGDE@StreamTrigger?$AA@ @ 0x003D66A0
// match: ??_7StreamTrigger@@6BCEventHandler@RWS@@@ @ 0x003D66B0
// match: ??_7StreamTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D66B8
// match: __ehhandler$?MakeNew@StreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C2A4
// match: __ehhandler$?MakeNew@StreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C2AC
// match: .CRT$XCU+0 @ 0x00426F74
// match: ?pStreamTriggerClassID@StreamTrigger@@2PBDB @ 0x004291C4

// match: _$E2 @ 0x0030ABA0
// match: _$E3 @ 0x0030E1B0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@StreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000BAC50
// match: __ehhandler$?MakeNew@StreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300470
// match: __ehhandler$?MakeNew@StreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030047F
// sp-match: ?MakeNew@StreamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0008F8F0
RWS_DEFINE_MAKENEW(StreamTrigger)

// match: ??0StreamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000BACD0
// sp-match: ??0StreamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0008F0E0
StreamTrigger::StreamTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
}

// match: ?vf_008@StreamTrigger@@UAEHXZ @ 0x000BAD20
// sp-match: ?vf_008@StreamTrigger@@UAEHXZ @ 0x0005BC00

// match: ??_GStreamTrigger@@UAEPAXI@Z @ 0x000BAD30
// sp-match: ??_GStreamTrigger@@UAEPAXI@Z @ 0x0008F8E0

// match: ??1StreamTrigger@@UAE@XZ @ 0x000BAD50
// sp-match: ??1StreamTrigger@@UAE@XZ @ 0x0008F110
// (Defined in the class, in StreamTrigger.h.)

// match: ?HandleAttributes@StreamTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BAD80
// sp-match: ?HandleAttributes@StreamTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0008F130
void StreamTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(StreamTrigger));
    while (!attrIt.IsFinished())
    {
        const RwInt32 *var_C;

        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_108 = attrIt->GetAs_RwInt32();
            break;
        case 1:
            var_C = (const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            unk_C0.unk_00 = *var_C;
            var_C++;
            unk_C0.unk_04 = *var_C;
            break;
        case 2:
            unk_C8[0] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 3:
            unk_C8[1] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 4:
            unk_C8[2] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 5:
            unk_C8[3] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 6:
            unk_C8[4] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 7:
            unk_C8[5] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 8:
            unk_C8[6] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 9:
            unk_C8[7] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 10:
            unk_E8[0] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 11:
            unk_E8[1] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 12:
            unk_E8[2] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 13:
            unk_E8[3] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 14:
            unk_E8[4] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 15:
            unk_E8[5] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 16:
            unk_E8[6] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        case 17:
            unk_E8[7] = (RwInt32)attrIt->GetAs_RwReal();
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@StreamTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000BB1B0
void StreamTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
        unk_24_6 = 0;
    }
    Trigger::HandleEvents(pMsg);
}

// match: ?vf_030@StreamTrigger@@UAEXXZ @ 0x000BB1F0
// sp-match: ?vf_030@StreamTrigger@@UAEXXZ @ 0x0008F3E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void StreamTrigger::vf_030()
{
    RwInt32 var_C;
    type_5E730 *bp_8;
    RwReal bp_4;

    bp_4 = 0.0f;
    if ((unk_108 && !unk_24_6) || !unk_108)
    {
        unk_24_6 = 1;
        bp_8 = (type_5E730 *)sub_198800(&unk_C0);
        if (dword_4B1E98.sub_8A980(&unk_C0, 0, 0x20, 0, 0, 0))
        {
            dword_44E8D8[bp_8->unk_20].unk_248 = (type_44E8D8_248 *)bp_8;
            for (var_C = 0; var_C < 8; var_C++)
            {
                if (unk_C8[var_C])
                {
                    bp_4 = unk_C8[var_C] / 100.0f;
                }
                else
                {
                    bp_4 = 0.0f;
                }
#ifdef CODFH_SP
                // shape: the volume converted into a float local first (SP 0x8F471 fild/fmulp, not fimul).
                RwReal volume = dword_44E8D8[bp_8->unk_20].unk_248->unk_18;
                bp_4 = volume / 100.0f * bp_4;
#else
                bp_4 = dword_44E8D8[bp_8->unk_20].unk_248->unk_18 / 100.0f * bp_4;
#endif
                if (bp_4 < 0.0)
                {
                    bp_4 = 0.0f;
                }
                if (bp_4 > 1.0f)
                {
                    bp_4 = 1.0f;
                }
                dword_44E8D8[bp_8->unk_20].unk_190[var_C] = bp_4;
                dword_44E8D8[bp_8->unk_20].unk_1D0[var_C] = 1.0f / unk_E8[var_C];
            }
        }
    }
}

// match: ??_EStreamTrigger@@WBI@AEPAXI@Z @ 0x000BB370
// sp-match: ??_EStreamTrigger@@WBI@AEPAXI@Z @ 0x0008F8D0
