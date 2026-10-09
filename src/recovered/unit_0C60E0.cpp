// LevelClumpBankParamTrigger: its MakeNew, constructor, destructor and
// handlers. Its original file name is not in the image, so it is named for
// its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/data.h"
#include "types/asynchload.h"
#include "types/CSoundBankSelector.h"
#include "types/LevelClumpBankParamTrigger.h"
#include "types/type_4B8EF0.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6B44
extern const RwReal flt_3D6B44 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(LevelClumpBankParamTrigger);
RWS_REGISTERCLASS(LevelClumpBankParamTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BL@BNILNFBP@LevelClumpBankParamTrigger?$AA@ @ 0x003D6B28
// match: ?flt_3D6B44@@3MB @ 0x003D6B44
// match: ??_7LevelClumpBankParamTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6B48
// match: ??_7LevelClumpBankParamTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6B50
// match: __ehhandler$?MakeNew@LevelClumpBankParamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C6DC
// match: __ehhandler$?MakeNew@LevelClumpBankParamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C6E4
// match: __ehhandler$??0LevelClumpBankParamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C700
// match: __ehhandler$??0LevelClumpBankParamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C708
// match: __ehhandler$??1LevelClumpBankParamTrigger@@UAE@XZ>1>8 @ 0x0041C724
// match: __ehhandler$??1LevelClumpBankParamTrigger@@UAE@XZ>1 @ 0x0041C72C
// match: .CRT$XCU+0 @ 0x00426FAC
// match: ?pLevelClumpBankParamTriggerClassID@LevelClumpBankParamTrigger@@2PBDB @ 0x004291FC

// match: _$E2 @ 0x0030AE40
// match: _$E3 @ 0x0030E290

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@LevelClumpBankParamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C60E0
// match: __ehhandler$?MakeNew@LevelClumpBankParamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003007E0
// match: __ehhandler$?MakeNew@LevelClumpBankParamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003007EF
// sp-match: ?MakeNew@LevelClumpBankParamTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00096DE0
RWS_DEFINE_MAKENEW(LevelClumpBankParamTrigger)

// Its handler serves the destructor too (folded by /OPT:ICF).
// match: ??0LevelClumpBankParamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C6160
// match: __ehhandler$??0LevelClumpBankParamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x00300800
// match: __ehhandler$??0LevelClumpBankParamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300808
// sp-match: ??0LevelClumpBankParamTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00096B10
LevelClumpBankParamTrigger::LevelClumpBankParamTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    LinkMsg(iMsgSparkStartSystem, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ??_GLevelClumpBankParamTrigger@@UAEPAXI@Z @ 0x000C61F0
// sp-match: ??_GLevelClumpBankParamTrigger@@UAEPAXI@Z @ 0x00096DD0

// match: ??1LevelClumpBankParamTrigger@@UAE@XZ @ 0x000C6210
// sp-match: ??1LevelClumpBankParamTrigger@@UAE@XZ @ 0x00096B90
LevelClumpBankParamTrigger::~LevelClumpBankParamTrigger()
{
    UnLinkMsg(iMsgSparkStartSystem);
    UnLinkMsg(dword_4B67C0);
}

// Commands 1 and 2: the clump banks' memory and their clumps', in
// kilobytes; command 0: the default clump bank (dword_429EA8).
// match: ?HandleAttributes@LevelClumpBankParamTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C6290
// sp-match: ?HandleAttributes@LevelClumpBankParamTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00096C00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void LevelClumpBankParamTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwInt32 bp_18 = 0;
    RwInt32 var_1C = 0;
    RwInt32 var_14 = -1;

    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator bp_8(attr, RWS_CLASSID_OF(LevelClumpBankParamTrigger));
    while (!bp_8.IsFinished())
    {
        switch (bp_8->GetCommandId())
        {
        case 1:
            bp_18 = bp_8->GetAs_RwInt32();
            break;
        case 2:
            var_1C = bp_8->GetAs_RwInt32();
            break;
        }
        ++bp_8;
    }
#ifdef CODFH_SP // shape: SP 0x96C86 multiplies (shl, then the and kept)
    dword_4E51C0 = (bp_18 * 1024) & ~0x1F;
#else
    dword_4E51C0 = (bp_18 << 10) & ~0x1F;
#endif
    sub_16FF00(var_1C << 10);
    RWS::CAttributeCommandIterator ebp_10(attr, RWS_CLASSID_OF(LevelClumpBankParamTrigger));
    while (!ebp_10.IsFinished())
    {
        switch (ebp_10->GetCommandId())
        {
        case 0:
            var_14 = ebp_10->GetAs_RwInt32();
            break;
        }
        ++ebp_10;
    }
    if (var_14 != -1)
    {
        dword_429EA8 = var_14;
    }
}

// match: ?HandleEvents@LevelClumpBankParamTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000C63C0
// sp-match: ?HandleEvents@LevelClumpBankParamTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x00096D20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void LevelClumpBankParamTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    RwInt32 var_8;
    RwInt32 l4;

    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == iMsgSparkStartSystem.p_msgrec || pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
        if (dword_4E5CC4 && dword_429EA8 != -1)
        {
            sub_16EAB0(dword_429EA8);
        }
        dword_4B8EF0.sub_E9FB0(8);
        sub_D9450();
        for (l4 = 0; l4 < 3; l4++)
        {
            var_8 = dword_4E54E8[l4];
            sub_16F3E0(l4, var_8);
        }
        dword_4B8EF0.sub_E9FB0(9);
        sub_D9450();
        if (pMsg.Id.p_msgrec == iMsgSparkStartSystem.p_msgrec)
        {
            UnLinkMsg(iMsgSparkStartSystem);
        }
    }
}

// match: ??_ELevelClumpBankParamTrigger@@WBI@AEPAXI@Z @ 0x000C6490
// sp-match: ??_ELevelClumpBankParamTrigger@@WBI@AEPAXI@Z @ 0x00096DC0
