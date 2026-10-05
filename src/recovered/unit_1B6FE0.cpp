// cNetLevelParams, a RenderWare Studio behaviour holding a level's network
// settings (types/cNetLevelParams.h): MakeNew, its constructor, destructor,
// attributes, event handler and getters. Its original file name is not in
// the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/cNetLevelParams.h"
#include "types/type_4D53F8.h"
#include "types/type_72810.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E24A4
extern const RwReal flt_3E24A4 = 0.01f;
// 0x003E24A8
extern const RwReal flt_3E24A8 = 0.01f;
// 0x003E24AC
extern const RwReal flt_3E24AC = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(cNetLevelParams);
RWS_REGISTERCLASS(cNetLevelParams);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@IMJDDJIN@cNetLevelParams?$AA@ @ 0x003E2494
// match: ?flt_3E24A4@@3MB @ 0x003E24A4
// match: ?flt_3E24A8@@3MB @ 0x003E24A8
// match: ?flt_3E24AC@@3MB @ 0x003E24AC
// match: ??_7cNetLevelParams@@6BCEventHandler@RWS@@@ @ 0x003E24B0
// match: ??_7cNetLevelParams@@6BCAttributeHandler@RWS@@@ @ 0x003E24B8
// match: __ehhandler$?MakeNew@cNetLevelParams@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041EF4C
// match: __ehhandler$?MakeNew@cNetLevelParams@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041EF54
// match: __ehhandler$??0cNetLevelParams@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041EF70
// match: __ehhandler$??0cNetLevelParams@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041EF80
// match: __ehhandler$??1cNetLevelParams@@UAE@XZ>1>8 @ 0x0041EF9C
// match: __ehhandler$??1cNetLevelParams@@UAE@XZ>1 @ 0x0041EFAC
// match: .CRT$XCU+0 @ 0x004271E8
// match: ?pcNetLevelParamsClassID@cNetLevelParams@@2PBDB @ 0x0042CAE4

// match: _$E2 @ 0x0030C260
// match: _$E3 @ 0x0030EAC0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@cNetLevelParams@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x001B6FE0
// match: __ehhandler$?MakeNew@cNetLevelParams@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00302CF0
// match: __ehhandler$?MakeNew@cNetLevelParams@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00302CFF
RWS_DEFINE_MAKENEW(cNetLevelParams)

// match: ??0cNetLevelParams@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x001B7060
// match: __ehhandler$??0cNetLevelParams@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x00302D10
// match: __ehhandler$??0cNetLevelParams@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00302D23
cNetLevelParams::cNetLevelParams(const RWS::CAttributePacket &attr)
{
    RwInt32 var_10;

    unk_28.unk_00 = 0;
    unk_28.unk_04 = 0;
    unk_30.unk_00 = 0;
    unk_30.unk_04 = 0;
    for (var_10 = 0; var_10 < 5; var_10++)
    {
        unk_48[var_10].unk_04 = 0;
        unk_48[var_10].unk_00 = 0;
        unk_70[var_10].unk_04 = 0;
        unk_70[var_10].unk_00 = 0;
    }
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_20)
    {
    }
    dword_4F8138 = this;
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
}

// match: ??_GcNetLevelParams@@UAEPAXI@Z @ 0x001B72F0

// match: ??1cNetLevelParams@@UAE@XZ @ 0x001B7310
// match: __ehhandler$??1cNetLevelParams@@UAE@XZ-0x2F @ 0x00302D30
// match: __ehhandler$??1cNetLevelParams@@UAE@XZ @ 0x00302D5F
cNetLevelParams::~cNetLevelParams()
{
    UnLinkMsg(RWS::iMsgStartSystem);
}

// Commands 0 and 1: the counts; 2 to 5: the teams' keys, each registered
// as a variable once set (2 and 4 of kind 4 with both halves, 3 and 5 of
// kind 3 with either); 6 to 17: the spawn keys.
// match: ?HandleAttributes@cNetLevelParams@@UAEXABVCAttributePacket@RWS@@@Z @ 0x001B73A0
void cNetLevelParams::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(cNetLevelParams));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_20 = attrIt->GetAs_RwInt32();
            break;
        case 1:
            unk_24 = attrIt->GetAs_RwInt32();
            break;
        case 2:
            attrIt->GetCommandData(unk_28);
            if (unk_28.unk_00 && unk_28.unk_04)
                sub_198900((type_3DF8D8_04 *)&unk_28, 4, 0, 0, 0, 0);
            break;
        case 3:
            attrIt->GetCommandData(unk_38);
            if (unk_38.unk_00 || unk_38.unk_04)
                sub_198900((type_3DF8D8_04 *)&unk_38, 3, 0, 0, 0, 0);
            break;
        case 4:
            attrIt->GetCommandData(unk_30);
            if (unk_30.unk_00 && unk_30.unk_04)
                sub_198900((type_3DF8D8_04 *)&unk_30, 4, 0, 0, 0, 0);
            break;
        case 5:
            attrIt->GetCommandData(unk_40);
            if (unk_40.unk_00 || unk_40.unk_04)
                sub_198900((type_3DF8D8_04 *)&unk_40, 3, 0, 0, 0, 0);
            break;
        case 6:
            attrIt->GetCommandData(unk_48[0]);
            break;
        case 7:
            attrIt->GetCommandData(unk_48[1]);
            break;
        case 8:
            attrIt->GetCommandData(unk_48[2]);
            break;
        case 9:
            attrIt->GetCommandData(unk_48[3]);
            break;
        case 10:
            attrIt->GetCommandData(unk_48[4]);
            break;
        case 11:
            attrIt->GetCommandData(unk_70[0]);
            break;
        case 12:
            attrIt->GetCommandData(unk_70[1]);
            break;
        case 13:
            attrIt->GetCommandData(unk_70[2]);
            break;
        case 14:
            attrIt->GetCommandData(unk_70[3]);
            break;
        case 15:
            attrIt->GetCommandData(unk_70[4]);
            break;
        case 16:
            attrIt->GetCommandData(unk_C0[0]);
            break;
        case 17:
            attrIt->GetCommandData(unk_C0[1]);
        }
        ++attrIt;
    }
}

// At the system's start each spawn key is looked up and its settings
// started.
// match: ?HandleEvents@cNetLevelParams@@UAEXAAVCMsg@RWS@@@Z @ 0x001B7770
void cNetLevelParams::HandleEvents(RWS::CMsg &pMsg)
{
    // The locals' names state their slots (docs/toolchain.md).
    type_4D53F8 *ebp_14;
    RwInt32 lv_10;
    type_4D53F8 *slot_C;
    type_4D53F8 *bp_8;
    RwInt32 bp_4;

    if (pMsg.Id.p_msgrec == RWS::iMsgStartSystem.p_msgrec)
    {
        for (bp_4 = 0; bp_4 < 5; bp_4++)
        {
            unk_98[bp_4] = sub_15CB40(&unk_48[bp_4]);
            if (unk_98[bp_4] != -1)
            {
                bp_8 = sub_15CB10(unk_98[bp_4]);
                if (bp_8)
                    bp_8->sub_15CAC0();
            }
            unk_AC[bp_4] = sub_15CB40(&unk_70[bp_4]);
            if (unk_AC[bp_4] != -1)
            {
                slot_C = sub_15CB10(unk_AC[bp_4]);
                if (slot_C)
                    slot_C->sub_15CAC0();
            }
        }
        for (lv_10 = 0; lv_10 < 2; lv_10++)
        {
            unk_D0[lv_10] = sub_15CB40(&unk_C0[lv_10]);
            if (unk_D0[lv_10] != -1)
            {
                ebp_14 = sub_15CB10(unk_D0[lv_10]);
                if (ebp_14)
                    ebp_14->sub_15CAC0();
            }
        }
    }
}

// match: ?sub_1B78E0@cNetLevelParams@@QAEHH@Z @ 0x001B78E0
RwInt32 cNetLevelParams::sub_1B78E0(RwInt32 arg_0)
{
    if (arg_0 == 4)
        return unk_20;
    return unk_24;
}

// match: ?sub_1B7910@cNetLevelParams@@QAEPAUtype_1B7910@@I@Z @ 0x001B7910
type_1B7910 *cNetLevelParams::sub_1B7910(RwUInt32 arg_0)
{
    if (arg_0 == 4)
        return (type_1B7910 *)&unk_28;
    return (type_1B7910 *)&unk_30;
}

// match: ?sub_1B7940@cNetLevelParams@@QAEPAUtype_1B7910@@I@Z @ 0x001B7940
type_1B7910 *cNetLevelParams::sub_1B7940(RwUInt32 arg_0)
{
    if (arg_0 == 4)
        return (type_1B7910 *)&unk_38;
    return (type_1B7910 *)&unk_40;
}

// match: ?sub_1B7970@cNetLevelParams@@QAEPAUtype_1B7910@@II@Z @ 0x001B7970
type_1B7910 *cNetLevelParams::sub_1B7970(RwUInt32 arg_0, RwUInt32 arg_4)
{
    if (arg_0 == 4)
        return (type_1B7910 *)&unk_48[arg_4];
    return (type_1B7910 *)&unk_70[arg_4];
}

// match: ?sub_1B79A0@cNetLevelParams@@QAEHIH@Z @ 0x001B79A0
RwInt32 cNetLevelParams::sub_1B79A0(RwUInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0 == 4)
        return unk_98[arg_4];
    return unk_AC[arg_4];
}

// The CEventHandler part's deleting destructor thunk (sub ecx, 0x18).
// match: ??_EcNetLevelParams@@WBI@AEPAXI@Z @ 0x001B79D0
