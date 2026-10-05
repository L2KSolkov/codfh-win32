// VehicleEnterExitTrigger: its MakeNew, constructor, destructor and
// handlers. Its original file name is not in the image, so it is named for
// its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/functions.h"
#include "types/alfamessman.h"
#include "types/CustomTrigger.h"
#include "types/scriptvm.h"
#include "types/type_10F710.h"
#include "types/type_3D2E7C.h"
#include "types/type_3D3548.h"
#include "types/type_72810.h"
#include "types/VehicleEnterExitTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D68D4
extern const RwReal flt_3D68D4 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(VehicleEnterExitTrigger);
RWS_REGISTERCLASS(VehicleEnterExitTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BI@NKCJOIMH@VehicleEnterExitTrigger?$AA@ @ 0x003D68BC
// match: ?flt_3D68D4@@3MB @ 0x003D68D4
// match: ??_7VehicleEnterExitTrigger@@6BCEventHandler@RWS@@@ @ 0x003D68D8
// match: ??_7VehicleEnterExitTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D68E0
// match: ??_C@_0BG@LOIAGPCC@VehicleEnterExitGroup?$AA@ @ 0x003D6910
// match: ??_C@_0P@CBMAPNCH@EntityToAttach?$AA@ @ 0x003D6928
// match: __ehhandler$?MakeNew@VehicleEnterExitTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C368
// match: __ehhandler$?MakeNew@VehicleEnterExitTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C370
// match: __ehhandler$??0VehicleEnterExitTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C38C
// match: __ehhandler$??0VehicleEnterExitTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C394
// match: __ehhandler$??1VehicleEnterExitTrigger@@UAE@XZ>1>8 @ 0x0041C3B0
// match: __ehhandler$??1VehicleEnterExitTrigger@@UAE@XZ>1 @ 0x0041C3B8
// match: .CRT$XCU+0 @ 0x00426F80
// match: ?pVehicleEnterExitTriggerClassID@VehicleEnterExitTrigger@@2PBDB @ 0x004291D0

// match: _$E2 @ 0x0030AC30
// match: _$E3 @ 0x0030E1E0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@VehicleEnterExitTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000BEAB0
// match: __ehhandler$?MakeNew@VehicleEnterExitTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300530
// match: __ehhandler$?MakeNew@VehicleEnterExitTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030053F
RWS_DEFINE_MAKENEW(VehicleEnterExitTrigger)

// match: ??0VehicleEnterExitTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000BEB30
// match: __ehhandler$??0VehicleEnterExitTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x00300550
// match: __ehhandler$??0VehicleEnterExitTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300558
VehicleEnterExitTrigger::VehicleEnterExitTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_CC.unk_00 = 0;
    unk_CC.unk_04 = 0;
    unk_DC.unk_00 = 0;
    unk_DC.unk_04 = 0;
    unk_D4 = 1;
    unk_E4 = 1;
    unk_C0 = 0;
    unk_C4 = 0;
    unk_C8 = -1;
    unk_D8 = -1;
    unk_E8 = 0;
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ??_GVehicleEnterExitTrigger@@UAEPAXI@Z @ 0x000BEC90

// match: ??1VehicleEnterExitTrigger@@UAE@XZ @ 0x000BECB0
// match: __ehhandler$??1VehicleEnterExitTrigger@@UAE@XZ-0x8 @ 0x00300570
// match: __ehhandler$??1VehicleEnterExitTrigger@@UAE@XZ @ 0x00300578
VehicleEnterExitTrigger::~VehicleEnterExitTrigger()
{
    if (unk_C0)
    {
        sub_6BC40(unk_C0);
        unk_C0 = 0;
    }
    if (unk_C4)
    {
        sub_6BC40(unk_C4);
        unk_C4 = 0;
    }
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// match: ?HandleEvents@VehicleEnterExitTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000BED80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void VehicleEnterExitTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    type_4492FC *var_8;
    type_4492FC *l4;

    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
        if (unk_C0)
        {
            sub_6BC40(unk_C0);
            unk_C0 = 0;
        }
        if (unk_C4)
        {
            sub_6BC40(unk_C4);
            unk_C4 = 0;
        }
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
        if (unk_C8 != -1)
        {
            l4 = sub_6A8E0("VehicleEnterExitGroup");
            unk_C0 = sub_6BAE0((RwInt32)this, (RwUInt32)sub_BF510, (RwInt32)this, unk_C8,
                                 (RwInt8)l4->unk_04, msg_flags(2, 2));
            unk_D4 = 0;
            unk_24_0 = (unk_D4 & unk_E4) != 0;
        }
        if (unk_D8 != -1)
        {
            var_8 = sub_6A8E0("VehicleEnterExitGroup");
            unk_C4 = sub_6BAE0((RwInt32)this, (RwUInt32)sub_BF550, (RwInt32)this, unk_D8,
                                 (RwInt8)var_8->unk_04, msg_flags(2, 2));
            unk_E4 = 0;
            unk_24_0 = (unk_D4 & unk_E4) != 0;
        }
    }
}

// Command 0 and 2: the messages (blocks) it waits for; 1 and 3: names; 4.
// match: ?HandleAttributes@VehicleEnterExitTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BEF50
void VehicleEnterExitTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(VehicleEnterExitTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
        {
            if (unk_C0)
            {
                sub_6BC40(unk_C0);
                unk_C0 = 0;
            }
            RwUInt8 *var_C = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_C);
            if (var_C)
            {
                unk_C8 = *(RwInt16 *)(var_C + 0x14);
                sub_145790(var_C);
                type_4492FC *var_10 = sub_6A8E0("VehicleEnterExitGroup");

                unk_C0 = sub_6BAE0((RwInt32)this, (RwUInt32)sub_BF510, (RwInt32)this, unk_C8,
                                     (RwInt8)var_10->unk_04, msg_flags(2, 2));
                unk_D4 = 0;
                unk_24_0 = (unk_D4 & unk_E4) != 0;
            }
            else
            {
                unk_C8 = -1;
                unk_C0 = 0;
                unk_D4 = 1;
                unk_24_0 = 1;
            }
            break;
        }
        case 1:
        {
            const type_3DF8D8_04 *var_14 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_14->unk_00)
            {
                unk_CC = *var_14;
                sub_198900((type_3DF8D8_04 *)&unk_CC, 0xC, 0, 0, 0, 0);
            }
            break;
        }
        case 2:
        {
            if (unk_C4)
            {
                sub_6BC40(unk_C4);
                unk_C4 = 0;
            }
            RwUInt8 *var_18 = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_18);
            if (var_18)
            {
                unk_D8 = *(RwInt16 *)(var_18 + 0x14);
                sub_145790(var_18);
                type_4492FC *var_1C = sub_6A8E0("VehicleEnterExitGroup");

                unk_C4 = sub_6BAE0((RwInt32)this, (RwUInt32)sub_BF550, (RwInt32)this, unk_D8,
                                     (RwInt8)var_1C->unk_04, msg_flags(2, 2));
                unk_E4 = 0;
                unk_24_0 = (unk_D4 & unk_E4) != 0;
            }
            else
            {
                unk_D8 = -1;
                unk_C4 = 0;
                unk_E4 = 1;
                unk_24_0 = 1;
            }
            break;
        }
        case 3:
        {
            const type_3DF8D8_04 *var_20 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_20->unk_00)
            {
                unk_DC = *var_20;
                sub_198900((type_3DF8D8_04 *)&unk_DC, 0xC, 0, 0, 0, 0);
            }
            break;
        }
        case 4:
            unk_E8 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?sub_BF310@VehicleEnterExitTrigger@@QAEHPAUtype_3D3548@@@Z @ 0x000BF310
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 VehicleEnterExitTrigger::sub_BF310(type_3D3548 *arg_0)
{
    RwInt32 var_30;
    RwInt32 var_2C;
    RwInt32 var_28;
    type_3DF8D8 *ebp_24;
    RwInt32 var_20[2];
    RwInt32 m_18;
    type_3DF8D8 *ebp_14;
    RwInt32 lv_10[2];
    RwInt32 bp_8;
    type_10F710 *bp_4;

    bp_4 = arg_0->vf_00C();
    if (bp_4->vf_200())
    {
        ebp_14 = sub_198800(&unk_DC);
        bp_8 = 0;
        sub_6B5F0("EntityToAttach", 0, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)bp_4->vf_098()), &bp_8, 1, 1, 0);
        var_2C = ebp_14->unk_18;
        lv_10[0] = var_2C;
        lv_10[1] = 1;
        sub_6B5F0("AddTaskToObject", 0, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)bp_4->vf_098()), lv_10, 2, 1, 0);
    }
    else
    {
        ebp_24 = sub_198800(&unk_CC);
        var_28 = bp_4->unk_384;
        m_18 = var_28;
        sub_6B5F0("EntityToAttach", 0, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)bp_4->vf_098()), &m_18, 1, 1, 0);
        var_30 = ebp_24->unk_18;
        var_20[0] = var_30;
        var_20[1] = 1;
        sub_6B5F0("AddTaskToObject", 0, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)bp_4->vf_098()), var_20, 2, 1, 0);
    }
    return 1;
}

// match: ?sub_BF470@VehicleEnterExitTrigger@@QAEHPAUtype_3D3548@@@Z @ 0x000BF470
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 VehicleEnterExitTrigger::sub_BF470(type_3D3548 *arg_0)
{
    type_3DF8D8 *var_C;
    type_3DF8D8 *bp_8;
    type_10F710 *bp_4;

    if (arg_0)
    {
        bp_4 = arg_0->vf_00C();
        if (bp_4)
        {
            if (bp_4->vf_200())
            {
                bp_8 = sub_198800(&unk_DC);
                if (bp_8 && unk_E4)
                {
                    return 1;
                }
            }
            else
            {
                var_C = sub_198800(&unk_CC);
                if (var_C && unk_D4)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// match: ?sub_BF510@@YAHPAVVehicleEnterExitTrigger@@@Z @ 0x000BF510
RwInt32 sub_BF510(VehicleEnterExitTrigger *arg_0)
{
    VehicleEnterExitTrigger *var_4 = arg_0;

    var_4->unk_D4 = 1;
    var_4->unk_24_0 = 1;
    var_4->unk_C0 = 0;
    return 0;
}

// match: ?sub_BF550@@YAHPAVVehicleEnterExitTrigger@@@Z @ 0x000BF550
RwInt32 sub_BF550(VehicleEnterExitTrigger *arg_0)
{
    VehicleEnterExitTrigger *var_4 = arg_0;

    var_4->unk_E4 = 1;
    var_4->unk_24_0 = 1;
    var_4->unk_C4 = 0;
    return 0;
}

// match: ?sub_BF590@VehicleEnterExitTrigger@@QAEXPAUtype_3D3548@@@Z @ 0x000BF590
void VehicleEnterExitTrigger::sub_BF590(type_3D3548 *arg_0)
{
    if (arg_0->unk_2C_4 && unk_E8)
    {
        if ((arg_0->vf_00C()->vf_200() && sub_198800(&unk_DC)) ||
            (!arg_0->vf_00C()->vf_200() && sub_198800(&unk_CC)))
        {
            sub_BF310(arg_0);
        }
    }
}

// match: ??_EVehicleEnterExitTrigger@@WBI@AEPAXI@Z @ 0x000BF640

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@VehicleEnterExitTrigger@@UAEHXZ (folded into 0x215B70)
RwInt32 VehicleEnterExitTrigger::vf_008()
{
        return 0x1A;
    }
