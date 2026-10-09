// Split from unit_09C1E0.cpp at 0x09DD80, where the image starts another object
// (AddTaskTrigger's): its .rdata begins at 0x3D58B8 with its class name (its registration's
// literal, which comes first), its .data with its class id at 0x429124, and its registration
// is the last of the four initializers there (PLAN M7).

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/type_3D3548.h"
#include "types/type_3D32F8.h"
#include "types/type_3D51C0.h"
#include "types/type_3D5400.h"
#include "types/type_9BB60.h"
#include "types/type_3D5658.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/alfamessman.h"
#include "types/scriptvm.h"
#include "types/AddTaskTrigger.h"
#include "types/type_72810.h"
#include "types/AnimatedBGTrigger.h"
#include "types/vec4.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "types/type_D48D0.h"
#include "types/alfaobject.h"
#include "types/type_3D2E7C.h"
#include "types/type_3DF8D8.h"
#include "types/type_44350.h"
#include "types/CustomTrigger.h"
#include "types/DogTrigger.h"
#include "types/type_10F710.h"
#include "game/vecutil.h"
#include "types/MeshSwapDestructableObjectTrigger.h"
#include "types/soundbank.h"
#include "rw/rphanim.h"
#include "game/clumpdata.h"
#include "types/animbank.h"
#include <string.h>
#include <math.h>

// match: .CRT$XCU+0 @ 0x00426EE0
// match: _$E2 @ 0x0030A4B0
// match: _$E3 @ 0x0030DF60

// match: ??_C@_0P@DGOOPBOK@AddTaskTrigger?$AA@ @ 0x003D58B8
// match: ?pAddTaskTriggerClassID@AddTaskTrigger@@2PBDB @ 0x00429124

RWS_IMPLEMENT_CLASSID(AddTaskTrigger);
RWS_REGISTERCLASS(AddTaskTrigger);

// match: __ehhandler$?MakeNew@AddTaskTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041B89C
// match: __ehhandler$?MakeNew@AddTaskTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041B8A4
// match: __ehhandler$??1AddTaskTrigger@@UAE@XZ>1>8 @ 0x0041B8C0
// match: __ehhandler$??1AddTaskTrigger@@UAE@XZ>1 @ 0x0041B8C8
// match: ?vf_00C@Trigger@@UAEHXZ @ 0x0009DFF0
// match: ?vf_018@Trigger@@UAEHXZ @ 0x0009E000
// match: ?vf_01C@Trigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x0009E010
// match: ?vf_024@Trigger@@UAEHXZ @ 0x0009E030
// match: ?vf_008@AddTaskTrigger@@UAEHXZ @ 0x0009E040
// match: ??_GAddTaskTrigger@@UAEPAXI@Z @ 0x0009E050
// match: ??_EAddTaskTrigger@@WBI@AEPAXI@Z @ 0x0009F120
// match: ??_7AddTaskTrigger@@6BCEventHandler@RWS@@@ @ 0x003D58C8
// match: ??_7AddTaskTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D58D0
// match: ??_C@_0N@IEEPMDEE@AddTaskGroup?$AA@ @ 0x003D5900
// match: ??_C@_0BA@PFNAONHM@AddTaskToObject?$AA@ @ 0x003D5910
// sp-match: ?vf_01C@Trigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x0007C270
// sp-match: ?vf_008@AddTaskTrigger@@UAEHXZ @ 0x0007C280
// sp-match: ??_GAddTaskTrigger@@UAEPAXI@Z @ 0x0007C5A0
// sp-match: ??_EAddTaskTrigger@@WBI@AEPAXI@Z @ 0x0007C590
// sp-match: ?vf_00C@Trigger@@UAEHXZ @ 0x00028300
// sp-match: ?vf_018@Trigger@@UAEHXZ @ 0x00088220
// sp-match: ?vf_024@Trigger@@UAEHXZ @ 0x00061D70

// match: ?MakeNew@AddTaskTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0009DD80
// match: __ehhandler$?MakeNew@AddTaskTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFB90
// match: __ehhandler$?MakeNew@AddTaskTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFB9F
// sp-match: ?MakeNew@AddTaskTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0007CC60
RWS_DEFINE_MAKENEW(AddTaskTrigger)

// match: ??0AddTaskTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0009DE00
// sp-match: ??0AddTaskTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0007C1A0
AddTaskTrigger::AddTaskTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_D4 = -1;
    unk_C4.unk_00 = 0;
    unk_C4.unk_04 = 0;
    unk_CC.unk_00 = 0;
    unk_CC.unk_04 = 0;
    unk_C0 = 0;
    unk_D8 = 0;
    unk_DC = 0;
    unk_FC_0 = 1;
    unk_FC_1 = 0;
    unk_FC_2 = 0;
    unk_FC_3 = 0;
    unk_FC_4 = 0;
    unk_FC_5 = 0;
    unk_FC_6 = 0;
    unk_FC_7 = 0;
    unk_F4 = 0.0f;
    unk_F8 = 0.0f;
    unk_F0 = 0;
    unk_E0 = 0;
    unk_E8.unk_00 = 0;
    unk_E8.unk_04 = 0;
}
// match: ??1AddTaskTrigger@@UAE@XZ @ 0x0009E070
// match: __ehhandler$??1AddTaskTrigger@@UAE@XZ-0x8 @ 0x002FFBB0
// match: __ehhandler$??1AddTaskTrigger@@UAE@XZ @ 0x002FFBB8
// sp-match: ??1AddTaskTrigger@@UAE@XZ @ 0x0007C290
AddTaskTrigger::~AddTaskTrigger()
{
    if (unk_C0 != 0)
    {
        sub_6BC40(unk_C0);
        unk_C0 = 0;
    }
}
// Commands 0: how many to hand the task to; 1: the task; 2: its value; 3:
// to the message's sender; 4: its task group's message (a block whose word
// at +0x14 it keeps, registering on it); 5: to the nearest; 6 and 7: the
// band (times 100, squared); 8: how many at a time; 10: the entity lists;
// 11: its point's object; 12: a second task; 13 to 18: by side.
// match: ?HandleAttributes@AddTaskTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0009E0F0
// sp-match: ?HandleAttributes@AddTaskTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0007C820
void AddTaskTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(AddTaskTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 11:
            unk_E8 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 5:
            unk_FC_7 = attrIt->GetAs_RwUInt32();
            break;
        case 7:
            unk_F4 = attrIt->GetAs_RwReal() * 100.0f;
            unk_F4 = unk_F4 * unk_F4;
            break;
        case 6:
            unk_F8 = attrIt->GetAs_RwReal() * 100.0f;
            unk_F8 = unk_F8 * unk_F8;
            break;
        case 8:
            unk_E0 = attrIt->GetAs_RwInt32();
            break;
        case 2:
            unk_F0 = attrIt->GetAs_RwInt32();
            break;
        case 10:
            unk_E4 = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_FC_0 = attrIt->GetAs_RwUInt32();
            break;
        case 13:
            unk_FC_1 = attrIt->GetAs_RwUInt32();
            break;
        case 14:
            unk_FC_2 = attrIt->GetAs_RwUInt32();
            break;
        case 15:
            unk_FC_3 = attrIt->GetAs_RwUInt32();
            break;
        case 16:
            unk_FC_4 = attrIt->GetAs_RwUInt32();
            break;
        case 17:
            unk_FC_5 = attrIt->GetAs_RwUInt32();
            break;
        case 18:
            unk_FC_6 = attrIt->GetAs_RwUInt32();
            break;
        case 0:
            unk_D8 = attrIt->GetAs_RwInt32();
            unk_DC = unk_D8;
            break;
        case 1:
        {
            const type_3DF8D8_04 *var_C;

            var_C = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (var_C->unk_00)
            {
                unk_C4 = *var_C;
                sub_198900((type_3DF8D8_04 *)&unk_C4, 0xC, 0, 0, 0, 0);
            }
            break;
        }
        case 12:
        {
            const type_3DF8D8_04 *var_10;

            var_10 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (var_10->unk_00)
            {
                unk_CC = *var_10;
                sub_198900((type_3DF8D8_04 *)&unk_CC, 0xC, 0, 0, 0, 0);
            }
            break;
        }
        case 4:
        {
            RwUInt8 *var_14;
            type_4492FC *var_18;

            if (unk_C0 != 0)
            {
                sub_6BC40(unk_C0);
                unk_C0 = 0;
            }
            var_14 = 0;
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_14);
            if (var_14 != 0)
            {
                unk_D4 = *(RwInt16 *)(var_14 + 0x14);
                sub_145790(var_14);
                var_18 = sub_6A8E0("AddTaskGroup");
                unk_C0 = sub_6BAE0((RwInt32)this, (RwUInt32)sub_9E850, (RwInt32)this, unk_D4,
                                   (RwInt8)var_18->unk_04, msg_flags(2, 2));
            }
            else
            {
                unk_D4 = -1;
            }
            break;
        }
        }
        ++attrIt;
    }
}
// On dword_4B67B8 it drops its registration and restarts its count; on
// dword_4B67C0 it registers sub_9E850 on its task group's message.
// match: ?HandleEvents@AddTaskTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x0009E770
// sp-match: ?HandleEvents@AddTaskTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x0007CBD0
void AddTaskTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    type_4492FC *var_4;

    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
        if (unk_C0 != 0)
        {
            sub_6BC40(unk_C0);
            unk_C0 = 0;
        }
        unk_DC = unk_D8;
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec && unk_D4 != -1)
    {
        var_4 = sub_6A8E0("AddTaskGroup");
        unk_C0 = sub_6BAE0((RwInt32)this, (RwUInt32)sub_9E850, (RwInt32)this, unk_D4,
                           (RwInt8)var_4->unk_04, msg_flags(2, 2));
    }
}
// match: ?sub_9E850@@YAHPAVAddTaskTrigger@@PAUtype_9E850_4@@@Z @ 0x0009E850
// sp-match: ?sub_9E850@@YAHPAVAddTaskTrigger@@PAUtype_9E850_4@@@Z @ 0x0007C790
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_9E850(AddTaskTrigger *arg_0, type_9E850_4 *arg_4)
{
    AddTaskTrigger *var_4;
    type_67620 *v8;
    type_67620 *varC;

    var_4 = arg_0;
    if (var_4->unk_FC_7)
    {
        if (var_4->unk_DC > 0)
        {
            v8 = sub_67620(arg_4->unk_0C);
            var_4->sub_9E990(v8);
            var_4->unk_DC--;
        }
    }
    else if (var_4->unk_FC_0 && var_4->unk_DC > 0)
    {
        varC = sub_67620(arg_4->unk_0C);
        var_4->sub_9E930(0, varC, &var_4->unk_C4);
        var_4->unk_DC--;
    }
    if (var_4->unk_DC <= 0)
    {
        var_4->unk_C0 = 0;
        return 0;
    }
    return 1;
}
// match: ?sub_9E930@AddTaskTrigger@@QAEXPAUtype_3D2E7C@@PAUtype_67620@@PAUtype_3DF8D8_04@@@Z @ 0x0009E930
// sp-match: ?sub_9E930@AddTaskTrigger@@QAEXPAUtype_3D2E7C@@PAUtype_67620@@PAUtype_3DF8D8_04@@@Z @ 0x0007C300
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AddTaskTrigger::sub_9E930(type_3D2E7C *arg_0, type_67620 *arg_4, type_3DF8D8_04 *arg_8)
{
    Trigger_key var_8;
    type_3DF8D8 *local_C;

    local_C = sub_198800(arg_8);
    var_8.unk_00 = local_C->get_unk_18();
    var_8.unk_04 = unk_F0;
    sub_6B5F0("AddTaskToObject", (type_67620 *)arg_0, (type_42E00_10 *)((RwInt32)this), (type_3D2E7C *)((RwInt32)arg_4), (RwInt32 *)(&var_8), 2, true, false);
}
// match: ?sub_9E990@AddTaskTrigger@@QAEXPAUtype_67620@@@Z @ 0x0009E990
// sp-match: ?sub_9E990@AddTaskTrigger@@QAEXPAUtype_67620@@@Z @ 0x0007C5B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AddTaskTrigger::sub_9E990(type_67620 *arg_0)
{
    RwInt32 o838;
    RwInt32 o834;
    RwReal lcl_830;
    type_3D3548 *r82C;
    type_3D3548 *w828;
    type_3D3548 *bp_824;
    type_3D3548 *frm_820;
    type_3D3548 *fp_81C;
    type_3D3548 *r818;
    type_3D3548 *r814;
    type_9ECE0 r810[0x100];
    RwInt32 slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    if (unk_E4 & 1)
    {
        r814 = dword_4B8600[9].unk_00;
        while (r814 != 0)
        {
            sub_9ECE0(r814, r810, &bp_4);
            r814 = r814->unk_10;
        }
    }
    if (unk_E4 & 2)
    {
        r818 = dword_4B8600[10].unk_00;
        while (r818 != 0)
        {
            sub_9ECE0(r818, r810, &bp_4);
            r818 = r818->unk_10;
        }
    }
    if (unk_E4 & 4)
    {
        fp_81C = dword_4B8600[0].unk_00;
        while (fp_81C != 0)
        {
            sub_9ECE0(fp_81C, r810, &bp_4);
            fp_81C = fp_81C->unk_10;
        }
    }
    if (unk_E4 & 8)
    {
        frm_820 = dword_4B8600[1].unk_00;
        while (frm_820 != 0)
        {
            sub_9ECE0(frm_820, r810, &bp_4);
            frm_820 = frm_820->unk_10;
        }
    }
    if (unk_E4 & 0x10)
    {
        bp_824 = dword_4B8600[11].unk_00;
        while (bp_824 != 0)
        {
            sub_9ECE0(bp_824, r810, &bp_4);
            bp_824 = bp_824->unk_10;
        }
    }
    if (unk_E4 & 0x20)
    {
        w828 = dword_4B8600[12].unk_00;
        while (w828 != 0)
        {
            sub_9ECE0(w828, r810, &bp_4);
            w828 = w828->unk_10;
        }
    }
    slot_C = 0;
    bp_8 = 0;
    while (slot_C == 0)
    {
        lcl_830 = 1.0e37f;
        o834 = -1;
        for (o838 = 0; o838 < bp_4; o838++)
        {
            if (r810[o838].unk_00 != 0 && r810[o838].unk_04 < lcl_830)
            {
                lcl_830 = r810[o838].unk_04;
                o834 = o838;
            }
        }
        if (o834 == -1)
        {
            break;
        }
        r82C = r810[o834].unk_00;
        if (r82C->vf_098() != 0)
        {
            sub_9E930(r82C->vf_098(), arg_0, &unk_C4);
            bp_8++;
            r810[o834].unk_00 = 0;
        }
        if (bp_8 >= unk_E0)
        {
            break;
        }
    }
}
// match: ?sub_9ECE0@AddTaskTrigger@@QAEXPAUtype_3D3548@@PAUtype_9ECE0@@PAH@Z @ 0x0009ECE0
// sp-match: ?sub_9ECE0@AddTaskTrigger@@QAEXPAUtype_3D3548@@PAUtype_9ECE0@@PAH@Z @ 0x0007C350
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AddTaskTrigger::sub_9ECE0(type_3D3548 *arg_0, type_9ECE0 *arg_4, RwInt32 *arg_8)
{
    Trigger *v38;
    type_71250 *v34;
    type_4492FC *v30;
    type_71250 *var_2C;
    RwInt32 loc28;
    type_3DF8D8 *slot_24;
    type_3DF8D8 *v20;
    type_3DF8D8 *slot_1C;
    RwV3d *local_18;
    RwV3d local_14;
    RwV3d *lv_8;
    RwReal var_4;

    if (*arg_8 < 0x100)
    {
        lv_8 = 0;
        if (unk_E8.unk_00 != 0 || unk_E8.unk_04 != 0)
        {
            slot_1C = sub_198800(&unk_E8);
            if (slot_1C != 0)
            {
                if (slot_1C->vf_008() == 0x2E)
                {
                    v20 = slot_1C;
                    lv_8 = v20->vf_00C();
                }
                else if (slot_1C->vf_008() == 0x2D)
                {
                    slot_24 = slot_1C;
                    lv_8 = slot_24->vf_00C();
                }
            }
        }
        else
        {
            lv_8 = (RwV3d *)&unk_90;
        }
        local_18 = arg_0->sub_CD550();
        RwV3dSubMacro(&local_14, lv_8, local_18);
        var_4 = RwV3dDotProductMacro(&local_14, &local_14);
        if (var_4 <= unk_F4 && var_4 >= unk_F8)
        {
            loc28 = 1;
            if (unk_FC_0)
            {
                var_2C = unk_AC;
                v38 = (Trigger *)arg_0->unk_344.unk_08;
                v34 = v38->unk_AC;
                v30 = sub_6A8E0("AddTaskGroup");
                if (var_2C == 0 || v34 == 0
                    || !sub_6C6D0(var_2C, v34, v30->unk_04, msg_flags(2, 2)))
                {
                    loc28 = 0;
                }
            }
            if (loc28 != 0)
            {
                arg_4[*arg_8].unk_04 = var_4;
                arg_4[*arg_8].unk_00 = arg_0;
                (*arg_8)++;
            }
        }
    }
}
// match: ?sub_9EED0@AddTaskTrigger@@QAEXPAUtype_3D3548@@@Z @ 0x0009EED0
// sp-match: ?sub_9EED0@AddTaskTrigger@@QAEXPAUtype_3D3548@@@Z @ 0x0007C480
void AddTaskTrigger::sub_9EED0(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    var_4 = 0;
    if (unk_FC_1 && arg_0->unk_2C_1)
    {
        var_4 = 1;
    }
    else if (unk_FC_3 && arg_0->unk_2C_0)
    {
        var_4 = 1;
    }
    else if (unk_FC_5 && !arg_0->unk_2C_0 && !arg_0->unk_2C_1)
    {
        var_4 = 1;
    }
    if (var_4 != 0 && arg_0->vf_098() != 0 && unk_DC > 0)
    {
        sub_9E930(arg_0->vf_098(), (type_67620 *)arg_0->vf_098(), &unk_C4);
        unk_DC--;
    }
}
// match: ?sub_9EFD0@AddTaskTrigger@@QAEXPAUtype_3D3548@@@Z @ 0x0009EFD0
// sp-match: ?sub_9EFD0@AddTaskTrigger@@QAEXPAUtype_3D3548@@@Z @ 0x0007C500
void AddTaskTrigger::sub_9EFD0(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    var_4 = 0;
    if (unk_FC_2 && arg_0->unk_2C_1)
    {
        var_4 = 1;
    }
    else if (unk_FC_4 && arg_0->unk_2C_0)
    {
        var_4 = 1;
    }
    else if (unk_FC_6 && !arg_0->unk_2C_0 && !arg_0->unk_2C_1)
    {
        var_4 = 1;
    }
    if (var_4 != 0 && arg_0->vf_098() != 0 && unk_DC > 0)
    {
        if (unk_CC.unk_00 != 0 || unk_CC.unk_04 != 0)
        {
            sub_9E930(arg_0->vf_098(), (type_67620 *)arg_0->vf_098(), &unk_CC);
        }
        else
        {
            sub_9E930(arg_0->vf_098(), (type_67620 *)arg_0->vf_098(), &unk_C4);
        }
        unk_DC--;
    }
}
