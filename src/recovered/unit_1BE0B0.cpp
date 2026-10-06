// cNetPickupTrigger, a RenderWare Studio behaviour (types/cNetPickupTrigger.h):
// MakeNew, its constructor, destructor, attributes and event handler. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/cNetPickupTrigger.h"
#include "game/netmsg.h"
#include "game/data.h"
#include "game/mpgame.h"
#include "game/fileio.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E2EA8
extern const RwReal flt_3E2EA8 = 0.01f;
// 0x003E2EAC
extern const RwReal flt_3E2EAC = 16.666666f;
// 0x003E2EB0
extern const RwReal flt_3E2EB0 = 0.01f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(cNetPickupTrigger);
RWS_REGISTERCLASS(cNetPickupTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BC@HPPCHKOO@cNetPickupTrigger?$AA@ @ 0x003E2E94
// match: ?flt_3E2EA8@@3MB @ 0x003E2EA8
// match: ?flt_3E2EAC@@3MB @ 0x003E2EAC
// match: ?flt_3E2EB0@@3MB @ 0x003E2EB0
// match: ??_C@_0CC@MCEILBAF@kujuUpdateTriggerObjectVisibilit@ @ 0x003E2EB4
// match: ??_C@_0BI@NILLFOOJ@sNetTriggerVisibility?5?$CK?$AA@ @ 0x003E2ED8
// match: ??_7cNetPickupTrigger@@6BCEventHandler@RWS@@@ @ 0x003E2EF0
// match: ??_7cNetPickupTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003E2EF8
// match: ??_C@_0CF@FDFJGGFK@Unknown?5renderware?5studio?5attrib@ @ 0x003E2F28
// match: __ehhandler$?MakeNew@cNetPickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041F108
// match: __ehhandler$?MakeNew@cNetPickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041F110
// match: __ehhandler$??1cNetPickupTrigger@@UAE@XZ>1>8 @ 0x0041F12C
// match: __ehhandler$??1cNetPickupTrigger@@UAE@XZ>1 @ 0x0041F13C
// match: __ehhandler$??0cNetPickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041F158
// match: __ehhandler$??0cNetPickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041F168
// match: .CRT$XCU+0 @ 0x004271F0
// match: ?pcNetPickupTriggerClassID@cNetPickupTrigger@@2PBDB @ 0x0042CB38

// match: _$E2 @ 0x0030C2A0
// match: _$E3 @ 0x0030EAD0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@cNetPickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x001BE0B0
// match: __ehhandler$?MakeNew@cNetPickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00302E60
// match: __ehhandler$?MakeNew@cNetPickupTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00302E6F
RWS_DEFINE_MAKENEW(cNetPickupTrigger)

// Its handler serves the destructor too (folded by /OPT:ICF).
// match: ??0cNetPickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x001BE130
// match: __ehhandler$??0cNetPickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x16 @ 0x00302E80
// match: __ehhandler$??0cNetPickupTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00302E96
cNetPickupTrigger::cNetPickupTrigger(const RWS::CAttributePacket &attr) : PickupTrigger(attr)
{
    RWS::CEventHandler::RegisterMsg(unk_E8, "kujuUpdateTriggerObjectVisibility", "sNetTriggerVisibility *");
    LinkMsg(unk_E8, "sNetTriggerVisibility *", 0x8000);
    LinkMsg(dword_4B8750, 0, 0x8000);
}

// match: ??_GcNetPickupTrigger@@UAEPAXI@Z @ 0x001BE1F0

// match: ??1cNetPickupTrigger@@UAE@XZ @ 0x001BE210
cNetPickupTrigger::~cNetPickupTrigger()
{
    UnLinkMsg(unk_E8);
    RWS::CEventHandler::UnRegisterMsg(unk_E8);
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(RWS::iMsgRunningTick);
}

// match: ?vf_020@cNetPickupTrigger@@UAEPAUtype_3D3548@@XZ @ 0x001BE2C0
type_3D3548 *cNetPickupTrigger::vf_020()
{
    return sub_1BD340(this);
}

// At the game's start the host spawns its pick-up into the list when the
// game type and the team masks allow; its visibility message passes its
// data on; the rest goes to PickupTrigger's handler.
// match: ?HandleEvents@cNetPickupTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x001BE2E0
void cNetPickupTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    // The locals' names state their slots (docs/toolchain.md).
    void *bp_8;
    type_3D3548 *bp_4;

    if (pMsg.Id.p_msgrec == RWS::iMsgRunningTick.p_msgrec)
        return;
    if (pMsg.Id.p_msgrec == dword_4B8750.p_msgrec)
    {
        if (!unk_4F61F8.unk_104)
        {
#ifdef CODFH_WIN32
            // (Supremacy, cut from the retail build: the port plays it with the team game's rules, its entities)
            if ((unk_E0 & (dword_4FB9E0.get_unk_08() == 16 ? 2 : dword_4FB9E0.get_unk_08())) &&
                (unk_E4 & unk_4F61F8.unk_108))
#else
            if ((unk_E0 & dword_4FB9E0.get_unk_08()) && (unk_E4 & unk_4F61F8.unk_108))
#endif
            {
                bp_4 = vf_020();
                dword_4FBB20.sub_1BDFC0((type_1AE520 *)bp_4, this);
            }
        }
    }
    else if (pMsg.Id.p_msgrec == unk_E8)
    {
        if (pMsg.pData)
        {
            bp_8 = pMsg.pData;
            sub_15FB30(bp_8);
        }
    }
    else
        PickupTrigger::HandleEvents(pMsg);
}

// match: ?HandleAttributes@cNetPickupTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x001BE3B0
void cNetPickupTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    PickupTrigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(cNetPickupTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            sub_1BE460(attrIt);
            sub_15FB30(&unk_4FD6D4);
            break;
        case 1:
            sub_1BE490(attrIt);
            sub_15FB30(&unk_4FD6D4);
            break;
        default:
            if (CODFH_DEBUG_LOGS)
                sub_1C8A30("Unknown renderware studio attribute\n");
        }
        ++attrIt;
    }
}

// match: ?sub_1BE460@cNetPickupTrigger@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001BE460
void cNetPickupTrigger::sub_1BE460(RWS::CAttributeCommandIterator &arg_0)
{
    arg_0->GetCommandData(unk_E0);
}

// match: ?sub_1BE490@cNetPickupTrigger@@QAEXAAVCAttributeCommandIterator@RWS@@@Z @ 0x001BE490
void cNetPickupTrigger::sub_1BE490(RWS::CAttributeCommandIterator &arg_0)
{
    arg_0->GetCommandData(unk_E4);
}

// The CEventHandler part's deleting destructor thunk (sub ecx, 0x18).
// match: ??_EcNetPickupTrigger@@WBI@AEPAXI@Z @ 0x001BE4C0

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?sub_15FB30@cNetPickupTrigger@@QAEXPAX@Z (folded into the empty body at 0x15FB30)
void cNetPickupTrigger::sub_15FB30(void *arg_0)
{
}
