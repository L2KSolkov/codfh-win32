// DogTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/functions.h"
#include "types/animbank.h"
#include "types/animobjpool.h"
#include "types/CustomTrigger.h"
#include "types/DogTrigger.h"
#include "types/type_3D5658.h"
#include "types/type_72810.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D5DB8
extern const RwReal flt_3D5DB8 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(DogTrigger);
RWS_REGISTERCLASS(DogTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@LBJBIDBK@DogTrigger?$AA@ @ 0x003D5DAC
// match: ?flt_3D5DB8@@3MB @ 0x003D5DB8
// match: ??_7DogTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5DBC
// match: ??_7DogTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5DC4
// match: __ehhandler$?MakeNew@DogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BC08
// match: __ehhandler$?MakeNew@DogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BC10
// match: __ehhandler$??1DogTrigger@@UAE@XZ>1>8 @ 0x0041BC2C
// match: __ehhandler$??1DogTrigger@@UAE@XZ>1 @ 0x0041BC3C
// match: .CRT$XCU+0 @ 0x00426F14
// match: ?pDogTriggerClassID@DogTrigger@@2PBDB @ 0x00429158

// match: _$E2 @ 0x0030A720
// match: _$E3 @ 0x0030E030

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@DogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A3E80
// match: __ehhandler$?MakeNew@DogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFEB0
// match: __ehhandler$?MakeNew@DogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFEBF
// sp-match: ?MakeNew@DogTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000806B0
RWS_DEFINE_MAKENEW(DogTrigger)

// match: ??0DogTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A3F00
// sp-match: ??0DogTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0007FFE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
DogTrigger::DogTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    RwInt32 var_8;
    RwInt32 l4;

    unk_D8.unk_00 = 0;
    unk_D8.unk_04 = 0;
    unk_E0.unk_00 = 0;
    unk_E0.unk_04 = 0;
    unk_E8.unk_00 = 0;
    unk_E8.unk_04 = 0;
    unk_F0 = 1.0471976f;
    unk_F4 = 0.78539819f;
    unk_F8 = 5000.0f;
    unk_FC = 5000.0f;
    unk_100 = 0.5f;
    unk_108 = 100;
    unk_10C = 2.5f;
    unk_110 = 3.5f;
    unk_104 = 2000.0f;
    unk_118 = 0;
    unk_11C = 0;
    unk_124 = 0;
    memset(unk_C0, 0, 6);
    for (l4 = 0; l4 < 2; l4++)
    {
        unk_C0[l4 + 4] = 1;
    }
    for (var_8 = 0; var_8 < 5; var_8++)
    {
        unk_C6[var_8] = -1;
    }
}

// match: ??_GDogTrigger@@UAEPAXI@Z @ 0x000A4110
// sp-match: ??_GDogTrigger@@UAEPAXI@Z @ 0x000806A0

// match: ??1DogTrigger@@UAE@XZ @ 0x000A4130
// match: __ehhandler$??1DogTrigger@@UAE@XZ-0x16 @ 0x002FFED0
// match: __ehhandler$??1DogTrigger@@UAE@XZ @ 0x002FFEE6
// sp-match: ??1DogTrigger@@UAE@XZ @ 0x00080110
DogTrigger::~DogTrigger()
{
    if (unk_124)
    {
        sub_BD350(&unk_124);
    }
}

// Commands 2 and 3 first (the kind of names unk_118 picks), then the rest.
// match: ?HandleAttributes@DogTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A41B0
// sp-match: ?HandleAttributes@DogTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00080180
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void DogTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    {
        RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(DogTrigger));
        while (!attrIt.IsFinished())
        {
            switch (attrIt->GetCommandId())
            {
            case 2:
                unk_118 = attrIt->GetAs_RwInt32();
                break;
            case 3:
                unk_11C = attrIt->GetAs_RwInt32();
                break;
            }
            ++attrIt;
        }
    }
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(DogTrigger));
    while (!attrIt.IsFinished())
    {
        const type_3DF8D8_04 *var_20;
        RwReal l1C;
        RwReal m_18;
        const type_3DF8D8_04 *ebp_14;

        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_D0 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            sub_198900((type_3DF8D8_04 *)&unk_D0, 0x2C, 0, 0, 0, 0);
            break;
        case 1:
            unk_D8 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_D8.unk_00 || unk_D8.unk_04)
            {
                if (!unk_118)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_D8, 3, 0, 0, 0, 0);
                }
                else
                {
                    sub_198900((type_3DF8D8_04 *)&unk_D8, 0x30, 0, 0, 0, 0);
                }
            }
            break;
        case 4:
            ebp_14 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            unk_E0 = *ebp_14;
            sub_198900((type_3DF8D8_04 *)&unk_E0, 0xA, 0, 0, 0, 0);
            break;
        case 6:
            unk_114 = attrIt->GetAs_RwInt32();
            if (unk_114 == 0)
            {
                unk_114 = 2;
            }
            else if (unk_114 == 1)
            {
                unk_114 = 1;
            }
            break;
        case 8:
            m_18 = attrIt->GetAs_RwReal();
            unk_F0 = (RwReal)cos(m_18 *= 0.0087266462f);
            break;
        case 9:
            l1C = attrIt->GetAs_RwReal();
            unk_F4 = (RwReal)cos(l1C *= 0.0087266462f);
            break;
        case 10:
            unk_F8 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 13:
            unk_104 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 11:
            unk_FC = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 12:
            unk_100 = attrIt->GetAs_RwReal();
            break;
        case 5:
            var_20 = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (var_20->unk_00)
            {
                unk_E8 = *var_20;
                sub_198900((type_3DF8D8_04 *)&unk_E8, 0xC, 0, 0, 0, 0);
            }
            break;
        case 15:
        {
            Trigger_key var_28 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_28.unk_00 || var_28.unk_04)
            {
                sub_198900((type_3DF8D8_04 *)&var_28, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8E0, 0, (RwInt32)&unk_C0[2], 0);
            }
            break;
        }
        case 16:
        {
            RwUInt8 *var_2C = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_2C);
            if (var_2C)
            {
                unk_C6[0] = *(RwInt16 *)(var_2C + 0x14);
                sub_145790(var_2C);
            }
            break;
        }
        case 17:
        {
            RwUInt8 *var_30 = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_30);
            if (var_30)
            {
                unk_C6[1] = *(RwInt16 *)(var_30 + 0x14);
                sub_145790(var_30);
            }
            break;
        }
        case 18:
        {
            RwUInt8 *var_34 = 0;

            sub_BD490(attrIt->GetAs_RwChar_ptr(), &var_34);
            if (var_34)
            {
                unk_C6[2] = *(RwInt16 *)(var_34 + 0x14);
                sub_145790(var_34);
            }
            break;
        }
        case 7:
            if (unk_124)
            {
                sub_BD350(&unk_124);
            }
            sub_BD490(attrIt->GetAs_RwChar_ptr(), &unk_124);
            break;
        case 14:
            unk_108 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?vf_020@DogTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000A4840
// sp-match: ?vf_020@DogTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000805E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *DogTrigger::vf_020()
{
    RwInt32 var_C;
    type_3D3548 *bp_8;
    type_3DF8D8 *bp_4;

    bp_8 = 0;
    bp_4 = sub_198800(&unk_D8);
    if (!bp_4)
    {
    }
    else
    {
        var_C = get_pool(2).m_pool.unk_18;
        if (var_C > 0 || unk_24_18)
        {
            bp_8 = sub_9C1E0((type_712B0 *)this);
        }
    }
    return bp_8;
}

// match: ?sub_A48B0@DogTrigger@@QAEXPAUtype_3D2E7C@@@Z @ 0x000A48B0
// sp-match: ?sub_A48B0@DogTrigger@@QAEXPAUtype_3D2E7C@@@Z @ 0x00080620
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void DogTrigger::sub_A48B0(type_3D2E7C *arg_0)
{
    RwInt32 var_8;
    RwInt32 l4;

    if (!unk_124)
    {
        return;
    }
    for (l4 = 0; l4 < 5 && ((RwUInt16 *)(unk_124 + 0x14))[l4] != 0xFFFF; l4++)
    {
        var_8 = ((RwInt32 *)unk_124)[l4];
        sub_6B680(((RwUInt16 *)(unk_124 + 0x14))[l4], (type_67620 *)arg_0, (type_42E00_10 *)((RwInt32)this), 0, &var_8, 1, 1, 0);
    }
}

// match: ??_EDogTrigger@@WBI@AEPAXI@Z @ 0x000A4940
// sp-match: ??_EDogTrigger@@WBI@AEPAXI@Z @ 0x00080690

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@DogTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void DogTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@DogTrigger@@UAEHXZ (folded into 0x15FD20)
RwInt32 DogTrigger::vf_008()
{
    return 6;
}

// ?vf_01C@DogTrigger@@UAEPAUtype_3DF8D8_04@@XZ (folded into 0xA17D0)
struct type_3DF8D8_04 *DogTrigger::vf_01C()
{
    return &unk_D0;
}
