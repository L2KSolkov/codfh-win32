// GimpTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/functions.h"
#include "types/animbank.h"
#include "types/GimpTrigger.h"
#include "types/SoldierTrigger.h"
#include "types/type_4D53F8.h"
#include "types/type_72810.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6C7C
extern const RwReal flt_3D6C7C = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(GimpTrigger);
RWS_REGISTERCLASS(GimpTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0M@GEGEJHLD@GimpTrigger?$AA@ @ 0x003D6C70
// match: ?flt_3D6C7C@@3MB @ 0x003D6C7C
// match: ??_7GimpTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6C80
// match: ??_7GimpTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6C88
// match: __ehhandler$?MakeNew@GimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C7FC
// match: __ehhandler$?MakeNew@GimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C804
// match: __ehhandler$??0GimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C820
// match: __ehhandler$??0GimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C830
// match: __ehhandler$??1GimpTrigger@@UAE@XZ>1>8 @ 0x0041C84C
// match: __ehhandler$??1GimpTrigger@@UAE@XZ>1 @ 0x0041C85C
// match: .CRT$XCU+0 @ 0x00426FBC
// match: ?pGimpTriggerClassID@GimpTrigger@@2PBDB @ 0x0042920C

// match: _$E2 @ 0x0030AF00
// match: _$E3 @ 0x0030E2D0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@GimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C6DF0
// match: __ehhandler$?MakeNew@GimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003008A0
// match: __ehhandler$?MakeNew@GimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003008AF
// sp-match: ?MakeNew@GimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00097EF0
RWS_DEFINE_MAKENEW(GimpTrigger)

// match: ??0GimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C6E70
// match: __ehhandler$??0GimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x16 @ 0x003008C0
// match: __ehhandler$??0GimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x003008D6
// sp-match: ??0GimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00097600
GimpTrigger::GimpTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    RwInt32 r10;
    RwInt32 var_14;

    unk_C0.unk_00 = 0;
    unk_C0.unk_04 = 0;
    unk_C8.unk_00 = 0;
    unk_C8.unk_04 = 0;
    unk_D0.unk_00 = 0;
    unk_D0.unk_04 = 0;
    unk_E8.unk_00 = 0;
    unk_E8.unk_04 = 0;
    unk_E0.unk_00 = 0;
    unk_E0.unk_04 = 0;
    unk_110 = 0;
    unk_13C = 0;
    unk_114 = 0;
    unk_120 = 0;
    unk_124 = 1;
    unk_128 = 1;
    unk_12C = 1;
    unk_130 = 1;
    unk_14C = 0x7FFFFFFF;
    unk_148 = 0x7FFFFFFF;
    unk_150.sub_D48D0(0);
    unk_11C = 0;
    memset(unk_100, 0, 6);
    for (r10 = 0; r10 < 2; r10++)
    {
        unk_100[r10 + 4] = 1;
    }
    for (var_14 = 0; var_14 < 5; var_14++)
    {
        unk_106[var_14] = -1;
    }
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ?vf_00C@GimpTrigger@@UAEHXZ @ 0x000C7190
// sp-match: ?vf_00C@GimpTrigger@@UAEHXZ @ 0x000977C0

// match: ?vf_014@GimpTrigger@@UAEHXZ @ 0x000C71B0
// sp-match: ?vf_014@GimpTrigger@@UAEHXZ @ 0x000977D0

// match: ??_GGimpTrigger@@UAEPAXI@Z @ 0x000C71D0
// sp-match: ??_GGimpTrigger@@UAEPAXI@Z @ 0x00097EE0

// match: ??1GimpTrigger@@UAE@XZ @ 0x000C71F0
// match: __ehhandler$??1GimpTrigger@@UAE@XZ-0x16 @ 0x003008E0
// match: __ehhandler$??1GimpTrigger@@UAE@XZ @ 0x003008F6
// sp-match: ??1GimpTrigger@@UAE@XZ @ 0x000977E0
GimpTrigger::~GimpTrigger()
{
    UnLinkMsg(RWS::iMsgStartSystem);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// Commands 3 and 4 first, then the rest.
// match: ?HandleAttributes@GimpTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C7280
// sp-match: ?HandleAttributes@GimpTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00097860
void GimpTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    {
        RWS::CAttributeCommandIterator stk_14(attr, RWS_CLASSID_OF(GimpTrigger));
        while (!stk_14.IsFinished())
        {
            switch (stk_14->GetCommandId())
            {
            case 3:
                unk_110 = stk_14->GetAs_RwInt32();
                break;
            case 4:
                unk_114 = stk_14->GetAs_RwInt32();
                break;
            }
            ++stk_14;
        }
    }
    RWS::CAttributeCommandIterator var8(attr, RWS_CLASSID_OF(GimpTrigger));
    RwInt32 local_C;

    while (!var8.IsFinished())
    {
        switch (var8->GetCommandId())
        {
        case 23:
            local_C = *(const RwInt32 *)var8->GetAs_RwChar_ptr();
            if (local_C)
            {
                unk_24 |= 0x40000; // not an address: a flag bit
            }
            break;
        case 24:
            local_C = *(const RwInt32 *)var8->GetAs_RwChar_ptr();
            if (!local_C)
            {
                unk_24 |= 0x80000; // not an address: a flag bit
            }
            break;
        case 0:
            unk_D8 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            sub_198900((type_3DF8D8_04 *)&unk_D8, 0x2E, 0, 0, 0, 0);
            break;
        case 2:
        {
            unk_C0 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();

            RwUInt8 *var_18 = (RwUInt8 *)sub_198900((type_3DF8D8_04 *)&unk_C0, 4, 0, 0, 0, 0);

            if (unk_110)
            {
                *(RwInt16 *)(var_18 + 0xC) = 1;
            }
            break;
        }
        case 6:
        {
            const type_3DF8D8_04 *var_1C = (const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();

            unk_C8 = *var_1C;
            sub_198900((type_3DF8D8_04 *)&unk_C8, 0xA, 0, 0, 0, 0);
            break;
        }
        case 7:
        {
            const type_3DF8D8_04 *var_20 = (const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();

            if (var_20->unk_00 || var_20->unk_04)
            {
                unk_D0 = *var_20;
                sub_198900((type_3DF8D8_04 *)&unk_D0, 0xC, 0, 0, 0, 0);
            }
            break;
        }
        case 27:
            unk_13C = var8->GetAs_RwInt32();
            break;
        case 9:
            unk_E8 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            if (unk_24_14)
            {
                unk_F8 = sub_15CB40(&unk_E8);
                if (unk_F8 != -1)
                {
                    type_4D53F8 *var_24 = sub_15CB10(unk_F8);

                    if (var_24)
                    {
                        var_24->sub_15CAC0();
                    }
                }
            }
            break;
        case 22:
            unk_F0 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            break;
        case 15:
        {
            type_3DF8D8_04 var_2C = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();

            if (var_2C.unk_00 || var_2C.unk_04)
            {
                unk_E0 = var_2C;
            }
            break;
        }
        case 16:
            unk_138 = var8->GetAs_RwInt32();
            break;
        case 17:
            unk_144 = var8->GetAs_RwInt32();
            break;
        case 5:
            unk_118 = var8->GetAs_RwInt32();
            break;
        case 18:
            unk_124 = var8->GetAs_RwInt32();
            break;
        case 12:
            unk_FC = var8->GetAs_RwInt32();
            break;
        case 19:
            unk_128 = var8->GetAs_RwInt32();
            break;
        case 20:
            unk_12C = var8->GetAs_RwInt32();
            break;
        case 21:
            unk_130 = var8->GetAs_RwInt32();
            break;
        case 8:
            unk_120 = var8->GetAs_RwInt32();
            break;
        case 10:
            unk_140 = var8->GetAs_RwInt32();
            break;
        case 11:
            unk_14C = var8->GetAs_RwInt32();
            if (unk_14C < 0)
            {
                unk_14C = 0x7FFFFFFF;
            }
            unk_148 = unk_14C;
            break;
        case 13:
        {
            Trigger_key var_34 = *(const Trigger_key *)var8->GetAs_RwChar_ptr();

            if (var_34.unk_00 || var_34.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&var_34, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8E0, 0, (RwInt32)&unk_100[2], 0);
            }
            break;
        }
        case 14:
            unk_11C = var8->GetAs_RwInt32();
            break;
        case 25:
            if (var8->GetAs_RwInt32())
            {
                unk_24 |= 0x100000; // not an address: a flag bit
            }
            break;
        case 26:
            unk_54 = var8->GetAs_RwReal() * 100.0f;
            break;
        }
        ++var8;
    }
}

// match: ?HandleEvents@GimpTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000C7A60
// sp-match: ?HandleEvents@GimpTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x00097D50
void GimpTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    type_4D53F8 *var_4;

    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == RWS::iMsgStartSystem.p_msgrec)
    {
        unk_F8 = sub_15CB40(&unk_E8);
        if (unk_F8 != -1)
        {
            var_4 = sub_15CB10(unk_F8);
            if (var_4)
            {
                var_4->sub_15CAC0();
            }
        }
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
        unk_14C = unk_148;
    }
}

// match: ?vf_020@GimpTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000C7B00
// sp-match: ?vf_020@GimpTrigger@@UAEPAUtype_3D3548@@XZ @ 0x00097DC0
type_3D3548 *GimpTrigger::vf_020()
{
    RwInt32 var_18;
    type_3DF8D8 *var_14;
    type_3D3548 *lv_10;
    type_3DF8D8 *var_C;
    type_3DF8D8 *bp_8;
    type_1917A0 *bp_4;

    lv_10 = 0;
    bp_4 = 0;
    var_C = 0;
    var_14 = 0;
    bp_8 = sub_198800(&unk_C0);
    if (bp_8 && bp_8->vf_008() == 4)
    {
        bp_4 = (type_1917A0 *)bp_8;
        var_C = bp_4->sub_1917A0();
        var_14 = bp_4->sub_1917F0();
    }
    if (!bp_4 || !var_C || !var_14)
    {
    }
    else
    {
        var_18 = get_4B83A0(4).unk_14.get_unk_18();
        if ((var_18 > 0 && get_pool(0).m_pool.get_unk_18() > 0) || unk_24_18)
        {
            lv_10 = sub_176E50(this);
        }
    }
    return lv_10;
}

// match: ?vf_018@GimpTrigger@@UAEHXZ @ 0x000C7BE0
// sp-match: ?vf_018@GimpTrigger@@UAEHXZ @ 0x00097E30
RwInt32 GimpTrigger::vf_018()
{
    RwInt32 var_8;
    type_3DF8D8 *l4;

    l4 = sub_198800(&unk_C0);
    if (!l4 || l4->vf_008() != 4)
    {
        return 0;
    }
    var_8 = ((type_1917A0 *)l4)->unk_44;
    switch (var_8)
    {
    case 1:
    case 3:
        return 1;
    case 0:
    case 2:
        return 2;
    case 4:
        return 4;
    default:
        return 0;
    }
}

// match: ?vf_010@GimpTrigger@@UAEXHH@Z @ 0x000C7C70
// sp-match: ?vf_010@GimpTrigger@@UAEXHH@Z @ 0x00097E90
void GimpTrigger::vf_010(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0)
    {
        if (unk_14C != 0x7FFFFFFF)
        {
            unk_14C += arg_4;
        }
    }
    else if (arg_4 < 0)
    {
        unk_14C = 0x7FFFFFFF;
    }
    else
    {
        unk_14C = arg_4;
    }
}

// match: ??_EGimpTrigger@@WBI@AEPAXI@Z @ 0x000C7CD0
// sp-match: ??_EGimpTrigger@@WBI@AEPAXI@Z @ 0x00097ED0

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@GimpTrigger@@UAEHXZ (folded into 0x1948F0)
RwInt32 GimpTrigger::vf_008()
{
    return 0x1F;
}

// ?vf_01C@GimpTrigger@@UAEPAUtype_3DF8D8_04@@XZ (folded into 0xB7530)
struct type_3DF8D8_04 *GimpTrigger::vf_01C()
{
    return &unk_D8;
}

// ?vf_024@GimpTrigger@@UAEHXZ (folded into 0x195D00)
RwInt32 GimpTrigger::vf_024()
{
    return 2;
}
