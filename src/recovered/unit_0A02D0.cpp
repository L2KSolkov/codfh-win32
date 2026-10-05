// CAnimBankInfo, a RenderWare Studio behaviour holding the animation heap's
// sizes: MakeNew, its constructor, destructor and event handler. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/CAnimBankInfo.h"
#include "types/CAnimPackSelector.h"
#include "types/animbank.h"
#include "types/musicplayer.h"
#include "types/soundbank.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_3DF8D8.h"


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@MINOLNCA@CAnimBankInfo?$AA@ @ 0x003D5984
// match: ??_7CAnimBankInfo@@6BCEventHandler@RWS@@@ @ 0x003D5994
// match: ??_7CAnimBankInfo@@6BCAttributeHandler@RWS@@@ @ 0x003D599C
// match: __ehhandler$?MakeNew@CAnimBankInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041B960
// match: __ehhandler$?MakeNew@CAnimBankInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041B968
// match: __ehhandler$??0CAnimBankInfo@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041B984
// match: __ehhandler$??0CAnimBankInfo@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041B994
// match: __ehhandler$??1CAnimBankInfo@@UAE@XZ>1>8 @ 0x0041B9B0
// match: __ehhandler$??1CAnimBankInfo@@UAE@XZ>1 @ 0x0041B9C0
// match: .CRT$XCU+0 @ 0x00426EE8
// match: ?pCAnimBankInfoClassID@CAnimBankInfo@@2PBDB @ 0x0042912C

// match: _$E2 @ 0x0030A510
// match: _$E3 @ 0x0030DF80

// The CAnimBankInfo registration initializer passes this exit to atexit
// (0x30A52B).

RWS_IMPLEMENT_CLASSID(CAnimBankInfo);
RWS_REGISTERCLASS(CAnimBankInfo);
// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CAnimBankInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A02D0
// match: __ehhandler$?MakeNew@CAnimBankInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFC30
// match: __ehhandler$?MakeNew@CAnimBankInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFC3F
RWS_DEFINE_MAKENEW(CAnimBankInfo)

// match: ??0CAnimBankInfo@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A0350
// match: __ehhandler$??0CAnimBankInfo@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x002FFC50
// match: __ehhandler$??0CAnimBankInfo@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x002FFC63
CAnimBankInfo::CAnimBankInfo(const RWS::CAttributePacket &attr)
{
    RwInt32 var_10;

    for (var_10 = 0; var_10 < 6; var_10++)
    {
        unk_20[var_10] = sub_A0530(0x100000); // not an address: 1 MB
        unk_38[var_10] = sub_A0530(0x100000); // not an address: 1 MB
        unk_50[var_10] = sub_A0530(0x10000);
    }
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
}

// match: ??_GCAnimBankInfo@@UAEPAXI@Z @ 0x000A0480

// match: ??1CAnimBankInfo@@UAE@XZ @ 0x000A04A0
// match: __ehhandler$??1CAnimBankInfo@@UAE@XZ-0x2F @ 0x002FFC70
// match: __ehhandler$??1CAnimBankInfo@@UAE@XZ @ 0x002FFC9F
CAnimBankInfo::~CAnimBankInfo()
{
    UnLinkMsg(RWS::iMsgStartSystem);
}

// match: ?sub_A0530@CAnimBankInfo@@QAEII@Z @ 0x000A0530
RwUInt32 CAnimBankInfo::sub_A0530(RwUInt32 arg_0)
{
    RwUInt32 var_4;

    var_4 = 4;
    if ((var_4 - 1) & arg_0)
    {
        arg_0 = var_4 - ((var_4 - 1) & arg_0) + arg_0;
    }
    return arg_0;
}

// Commands 0 to 17: the eighteen sizes, each rounded up to 4.
// match: ?HandleAttributes@CAnimBankInfo@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A0570
void CAnimBankInfo::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(CAnimBankInfo));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_20[0] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 1:
            unk_20[1] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 2:
            unk_20[2] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 3:
            unk_20[3] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 4:
            unk_20[4] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 5:
            unk_20[5] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 6:
            unk_38[0] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 7:
            unk_38[1] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 8:
            unk_38[2] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 9:
            unk_38[3] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 10:
            unk_38[4] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 11:
            unk_38[5] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 12:
            unk_50[0] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 13:
            unk_50[1] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 14:
            unk_50[2] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 15:
            unk_50[3] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 16:
            unk_50[4] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        case 17:
            unk_50[5] = sub_A0530(attrIt->GetAs_RwUInt32());
            break;
        }
        ++attrIt;
    }
}

// Once the system starts: hands the sizes to the animation banks and stops
// listening.
// match: ?HandleEvents@CAnimBankInfo@@UAEXAAVCMsg@RWS@@@Z @ 0x000A09D0
void CAnimBankInfo::HandleEvents(RWS::CMsg &pMsg)
{
    if (pMsg.Id.p_msgrec == RWS::iMsgStartSystem.p_msgrec)
    {
        sub_770F0(6, 0x100000, sub_A0A20()); // not an address: 1 MB
        UnLinkMsg(RWS::iMsgStartSystem);
    }
}

// match: ?sub_A0A20@CAnimBankInfo@@QAEPAIXZ @ 0x000A0A20
RwUInt32 *CAnimBankInfo::sub_A0A20()
{
    return unk_38;
}
// match: ??_ECAnimBankInfo@@WBI@AEPAXI@Z @ 0x000A0A40
