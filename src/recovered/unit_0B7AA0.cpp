// SoldierTrigger, the soldier spawner: its MakeNew, constructor, destructor
// and handlers. Its original file name is not in the image, so it is named
// for its start address.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/functions.h"
#include "types/animbank.h"
#include "types/CustomTrigger.h"
#include "types/SoldierTrigger.h"
#include "types/type_4D53F8.h"
#include "types/type_72810.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6504
extern const RwReal flt_3D6504 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(SoldierTrigger);
RWS_REGISTERCLASS(SoldierTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0P@ELAIOFHA@SoldierTrigger?$AA@ @ 0x003D64F4
// match: ?flt_3D6504@@3MB @ 0x003D6504
// match: ??_7SoldierTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6508
// match: ??_7SoldierTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6510
// match: __ehhandler$?MakeNew@SoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C0F8
// match: __ehhandler$?MakeNew@SoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C100
// match: __ehhandler$??0SoldierTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041C11C
// match: __ehhandler$??0SoldierTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041C12C
// match: __ehhandler$??1SoldierTrigger@@UAE@XZ>1>8 @ 0x0041C148
// match: __ehhandler$??1SoldierTrigger@@UAE@XZ>1 @ 0x0041C158
// match: .CRT$XCU+0 @ 0x00426F60
// match: ?pSoldierTriggerClassID@SoldierTrigger@@2PBDB @ 0x004291B0

// match: _$E2 @ 0x0030AAB0
// match: _$E3 @ 0x0030E160

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B7AA0
// match: __ehhandler$?MakeNew@SoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x003002F0
// match: __ehhandler$?MakeNew@SoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x003002FF
RWS_DEFINE_MAKENEW(SoldierTrigger)

// match: ??0SoldierTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B7B20
// match: __ehhandler$??0SoldierTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x16 @ 0x00300310
// match: __ehhandler$??0SoldierTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300326
SoldierTrigger::SoldierTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    RwInt32 r10;
    RwInt32 var_14;

    unk_D8.unk_00 = 0;
    unk_D8.unk_04 = 0;
    unk_E0.unk_00 = 0;
    unk_E0.unk_04 = 0;
    unk_E8.unk_00 = 0;
    unk_E8.unk_04 = 0;
    unk_120.unk_00 = 0;
    unk_120.unk_04 = 0;
    unk_128.unk_00 = 0;
    unk_128.unk_04 = 0;
    unk_28.unk_00 = 0;
    unk_28.unk_04 = 0;
    unk_F8.unk_00 = 0;
    unk_F8.unk_04 = 0;
    unk_16C = 0;
    unk_170 = 0;
    unk_104 = 1.5707964f;
    unk_108 = 1.5707964f;
    unk_10C = 6000.0f;
    unk_110 = 6000.0f;
    unk_114 = 0.95f;
    unk_130 = -1;
    unk_134 = -1;
    unk_140 = 100;
    unk_144 = 2.5f;
    unk_148 = 3.5f;
    unk_118 = 6000.0f;
    unk_14C = -1;
    unk_150 = 0;
    unk_154 = 50.0f;
    unk_160 = 0;
    unk_138 = 1;
    unk_13C = 1;
    unk_168 = 0;
    unk_15C = 0x7FFFFFFF;
    unk_158 = 0x7FFFFFFF;
    unk_164 = 0;
    unk_198 = 0;
    memset(unk_C0, 0, 6);
    for (r10 = 0; r10 < 2; r10++)
    {
        unk_C0[r10 + 4] = 1;
    }
    for (var_14 = 0; var_14 < 5; var_14++)
    {
        unk_C6[var_14] = -1;
    }
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
    unk_174[0] = 0;
}

// match: ??_GSoldierTrigger@@UAEPAXI@Z @ 0x000B7F30

// match: ??1SoldierTrigger@@UAE@XZ @ 0x000B7F50
// match: __ehhandler$??1SoldierTrigger@@UAE@XZ-0x16 @ 0x00300330
// match: __ehhandler$??1SoldierTrigger@@UAE@XZ @ 0x00300346
SoldierTrigger::~SoldierTrigger()
{
    if (unk_198)
    {
        sub_BD350(&unk_198);
    }
    UnLinkMsg(RWS::iMsgStartSystem);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// Commands 4 and 5 first, then the rest.
// match: ?HandleAttributes@SoldierTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B8000
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void SoldierTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator stk_14(attr, RWS_CLASSID_OF(SoldierTrigger));
    while (!stk_14.IsFinished())
    {
        switch (stk_14->GetCommandId())
        {
        case 4:
            unk_16C = stk_14->GetAs_RwInt32();
            break;
        case 5:
            unk_170 = stk_14->GetAs_RwInt32();
            break;
        }
        ++stk_14;
    }
    RWS::CAttributeCommandIterator var8(attr, RWS_CLASSID_OF(SoldierTrigger));
    RwInt32 local_C;
    RwChar var_98[0x80];

    while (!var8.IsFinished())
    {
        switch (var8->GetCommandId())
        {
        case 29:
            local_C = *(const RwInt32 *)var8->GetAs_RwChar_ptr();
            if (local_C)
            {
                unk_24 |= 0x40000; // not an address: a flag bit
            }
            break;
        case 30:
            local_C = *(const RwInt32 *)var8->GetAs_RwChar_ptr();
            if (!local_C)
            {
                unk_24 |= 0x80000; // not an address: a flag bit
            }
            break;
        case 0:
            unk_D0 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            if (unk_D0.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_D0, 0x2E, 0, 0, 0, 0);
            }
            break;
        case 1:
        {
            const RwChar *var_9C = var8->GetAs_RwChar_ptr();

            strcpy(var_98, var_9C);
            if (strlen(var_98) > 0x20)
            {
                var_98[0x1F] = 0;
            }
            if (var_9C)
            {
                strcpy(unk_174, var_98);
            }
            break;
        }
        case 3:
            unk_D8 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            if (unk_D8.unk_00 && unk_D8.unk_04)
            {
                RwUInt8 *var_A0 = (RwUInt8 *)sub_198900((type_3DF8D8_04 *)&unk_D8, 4, 0, 0, 0, 0);

                if (unk_16C)
                {
                    *(RwInt16 *)(var_A0 + 0xC) = 1;
                }
            }
            break;
        case 6:
            unk_160 = var8->GetAs_RwInt32();
            break;
        case 7:
        {
            const type_3DF8D8_04 *var_A4 = (const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();

            unk_E0 = *var_A4;
            sub_198900((type_3DF8D8_04 *)&unk_E0, 0xA, 0, 0, 0, 0);
            break;
        }
        case 9:
            unk_168 = var8->GetAs_RwInt32();
            break;
        case 40:
            unk_138 = var8->GetAs_RwInt32();
            break;
        case 41:
            unk_13C = var8->GetAs_RwInt32();
            break;
        case 16:
        {
            RwReal var_A8 = var8->GetAs_RwReal();

            unk_104 = (RwReal)cos(var_A8 *= 0.0087266462f);
            break;
        }
        case 17:
        {
            RwReal var_AC = var8->GetAs_RwReal();

            unk_108 = (RwReal)cos(var_AC *= 0.0087266462f);
            break;
        }
        case 23:
        {
            RwReal var_B0 = var8->GetAs_RwReal();

            var_B0 *= 0.5f;
            unk_144 = var_B0;
            break;
        }
        case 24:
        {
            RwReal var_B4 = var8->GetAs_RwReal();

            var_B4 *= 0.5f;
            unk_148 = var_B4;
            break;
        }
        case 18:
            unk_10C = var8->GetAs_RwReal() * 100.0f;
            break;
        case 21:
            unk_118 = var8->GetAs_RwReal() * 100.0f;
            break;
        case 19:
            unk_110 = var8->GetAs_RwReal() * 100.0f;
            break;
        case 20:
            unk_114 = var8->GetAs_RwReal();
            break;
        case 8:
        {
            const type_3DF8D8_04 *var_B8 = (const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();

            if (var_B8->unk_00)
            {
                unk_E8 = *var_B8;
                sub_198900((type_3DF8D8_04 *)&unk_E8, 0xC, 0, 0, 0, 0);
            }
            break;
        }
        case 38:
            unk_120 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            if (unk_24_14)
            {
                unk_130 = sub_15CB40(&unk_120);
                if (unk_130 != -1)
                {
                    type_4D53F8 *var_BC = sub_15CB10(unk_130);

                    if (var_BC)
                    {
                        var_BC->sub_15CAC0();
                    }
                }
            }
            break;
        case 39:
            unk_128 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            if (unk_24_14)
            {
                unk_134 = sub_15CB40(&unk_128);
                if (unk_134 != -1)
                {
                    type_4D53F8 *var_C0 = sub_15CB10(unk_134);

                    if (var_C0)
                    {
                        var_C0->sub_15CAC0();
                    }
                }
            }
            break;
        case 25:
        {
            Trigger_key var_C8 = *(const Trigger_key *)var8->GetAs_RwChar_ptr();

            if (var_C8.unk_00 || var_C8.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&var_C8, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8E0, 0, (RwInt32)&unk_C0[2], 0);
            }
            break;
        }
        case 26:
        {
            RwUInt8 *var_CC = 0;

            sub_BD490(var8->GetAs_RwChar_ptr(), &var_CC);
            if (var_CC)
            {
                unk_C6[0] = *(RwInt16 *)(var_CC + 0x14);
                sub_145790(var_CC);
            }
            break;
        }
        case 27:
        {
            RwUInt8 *var_D0 = 0;

            sub_BD490(var8->GetAs_RwChar_ptr(), &var_D0);
            if (var_D0)
            {
                unk_C6[1] = *(RwInt16 *)(var_D0 + 0x14);
                sub_145790(var_D0);
            }
            break;
        }
        case 28:
        {
            RwUInt8 *var_D4 = 0;

            sub_BD490(var8->GetAs_RwChar_ptr(), &var_D4);
            if (var_D4)
            {
                unk_C6[2] = *(RwInt16 *)(var_D4 + 0x14);
                sub_145790(var_D4);
            }
            break;
        }
        case 42:
        {
            RwInt32 var_D8 = var8->GetAs_RwUInt32();

            if (var_D8 >= 0x6E)
            {
                var_D8 = -1;
            }
            if (var_D8 == 0x6B)
            {
                var_D8 = -1;
            }
            unk_14C = var_D8;
            break;
        }
        case 43:
            unk_150 = var8->GetAs_RwInt32();
            break;
        case 44:
            unk_154 = var8->GetAs_RwReal();
            break;
        case 14:
            unk_11C = var8->GetAs_RwInt32();
            break;
        case 37:
            unk_F0 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            break;
        case 10:
            if (unk_198)
            {
                sub_BD350(&unk_198);
            }
            sub_BD490(var8->GetAs_RwChar_ptr(), &unk_198);
            break;
        case 22:
            unk_140 = var8->GetAs_RwInt32();
            break;
        case 12:
            unk_100 = var8->GetAs_RwInt32();
            break;
        case 13:
            unk_15C = var8->GetAs_RwInt32();
            if (unk_15C < 0)
            {
                unk_15C = 0x7FFFFFFF;
            }
            unk_158 = unk_15C;
            break;
        case 11:
            unk_164 = var8->GetAs_RwInt32();
            break;
        case 15:
        {
            type_3DF8D8_04 var_E0 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();

            if (var_E0.unk_00 || var_E0.unk_04)
            {
                unk_F8 = var_E0;
            }
            break;
        }
        case 31:
            if (var8->GetAs_RwInt32())
            {
                unk_24 |= 0x100000; // not an address: a flag bit
            }
            break;
        case 32:
            unk_54 = var8->GetAs_RwReal() * 100.0f;
            break;
        }
        ++var8;
    }
}

// On iMsgStartSystem it finds its weapons' settings and registers their
// names; on dword_4B67C0 it restores the number it may spawn.
// match: ?HandleEvents@SoldierTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000B8DD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void SoldierTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    type_4D53F8 *var_8;
    type_4D53F8 *l4;

    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == RWS::iMsgStartSystem.p_msgrec)
    {
        unk_130 = sub_15CB40(&unk_120);
        if (unk_130 != -1)
        {
            l4 = sub_15CB10(unk_130);
            if (l4)
            {
                l4->sub_15CAC0();
            }
        }
        unk_134 = sub_15CB40(&unk_128);
        if (unk_134 != -1)
        {
            var_8 = sub_15CB10(unk_134);
            if (var_8)
            {
                var_8->sub_15CAC0();
            }
        }
    }
    else if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
    }
    else if (pMsg.Id.p_msgrec == dword_4B67C0.p_msgrec)
    {
        unk_15C = unk_158;
    }
}

// match: ?vf_020@SoldierTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000B8EC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *SoldierTrigger::vf_020()
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
    bp_8 = sub_198800(&unk_D8);
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
        var_18 = get_pool(2).m_pool.unk_18;
        if (var_18 > 0 || unk_24_18)
        {
            lv_10 = sub_134B40((type_3D3548 *)this);
        }
    }
    return lv_10;
}

// match: ?sub_B8F80@SoldierTrigger@@QAEXPAUtype_3D2E7C@@@Z @ 0x000B8F80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void SoldierTrigger::sub_B8F80(type_3D2E7C *arg_0)
{
    RwInt32 var_8;
    RwInt32 l4;

    if (!unk_198)
    {
        return;
    }
    for (l4 = 0; l4 < 5 && ((RwUInt16 *)(unk_198 + 0x14))[l4] != 0xFFFF; l4++)
    {
        var_8 = ((RwInt32 *)unk_198)[l4];
        sub_6B680(((RwUInt16 *)(unk_198 + 0x14))[l4], (type_67620 *)arg_0, (type_42E00_10 *)((RwInt32)this), 0, &var_8, 1, 1, 0);
    }
}

// match: ?vf_018@SoldierTrigger@@UAEHXZ @ 0x000B9010
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 SoldierTrigger::vf_018()
{
    RwInt32 var_8;
    type_3DF8D8 *l4;

    l4 = sub_198800(&unk_D8);
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

// match: ?vf_010@SoldierTrigger@@UAEXHH@Z @ 0x000B90A0
void SoldierTrigger::vf_010(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0)
    {
        if (unk_15C != 0x7FFFFFFF)
        {
            unk_15C += arg_4;
        }
    }
    else if (arg_4 < 0)
    {
        unk_15C = 0x7FFFFFFF;
    }
    else
    {
        unk_15C = arg_4;
    }
}

// match: ??_ESoldierTrigger@@WBI@AEPAXI@Z @ 0x000B9100

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_014@SoldierTrigger@@UAEHXZ (folded into 0x1C9090)
RwInt32 SoldierTrigger::vf_014()
{
    return unk_100;
}
