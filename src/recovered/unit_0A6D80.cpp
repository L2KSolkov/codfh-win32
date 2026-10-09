// ParticleTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/ParticleTrigger.h"
#include "types/type_72810.h"

RWS_IMPLEMENT_CLASSID(ParticleTrigger);
RWS_REGISTERCLASS(ParticleTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@KLOABBHO@ParticleTrigger?$AA@ @ 0x003D5EAC
// match: ??_7ParticleTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5EBC
// match: ??_7ParticleTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5EC4
// match: __ehhandler$?MakeNew@ParticleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BD64
// match: __ehhandler$?MakeNew@ParticleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BD6C
// match: __ehhandler$??0ParticleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041BD88
// match: __ehhandler$??0ParticleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041BD90
// match: __ehhandler$??1ParticleTrigger@@UAE@XZ>1>8 @ 0x0041BDAC
// match: __ehhandler$??1ParticleTrigger@@UAE@XZ>1 @ 0x0041BDB4
// match: .CRT$XCU+0 @ 0x00426F28
// match: ?pParticleTriggerClassID@ParticleTrigger@@2PBDB @ 0x0042916C

// match: _$E2 @ 0x0030A810
// match: _$E3 @ 0x0030E080

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@ParticleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A6D80
// match: __ehhandler$?MakeNew@ParticleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFFF0
// match: __ehhandler$?MakeNew@ParticleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFFFF
// sp-match: ?MakeNew@ParticleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000836F0
RWS_DEFINE_MAKENEW(ParticleTrigger)

// match: ??0ParticleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A6E00
// match: __ehhandler$??0ParticleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x00300010
// match: __ehhandler$??0ParticleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300018
// sp-match: ??0ParticleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00082520
ParticleTrigger::ParticleTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    memset(unk_C0, 0, 0x2BC);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ?vf_008@ParticleTrigger@@UAEHXZ @ 0x000A6EF0
// sp-match: ?vf_008@ParticleTrigger@@UAEHXZ @ 0x000825E0

// match: ??_GParticleTrigger@@UAEPAXI@Z @ 0x000A6F00
// sp-match: ??_GParticleTrigger@@UAEPAXI@Z @ 0x000836E0

// match: ??1ParticleTrigger@@UAE@XZ @ 0x000A6F20
// match: __ehhandler$??1ParticleTrigger@@UAE@XZ-0x8 @ 0x00300030
// match: __ehhandler$??1ParticleTrigger@@UAE@XZ @ 0x00300038
// sp-match: ??1ParticleTrigger@@UAE@XZ @ 0x00082600
ParticleTrigger::~ParticleTrigger()
{
    sub_A8F40();
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// Commands in fives, one per emitter (0 to 123).
// match: ?HandleAttributes@ParticleTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A6FA0
// sp-match: ?HandleAttributes@ParticleTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00082680
void ParticleTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(ParticleTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0[0].unk_00 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 1:
            unk_C0[1].unk_00 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 2:
            unk_C0[2].unk_00 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_C0[3].unk_00 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 4:
            unk_C0[4].unk_00 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 14:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_10 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_10.unk_00 || var_10.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_10, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_C0[0].unk_04, 0);
                }
            }
            break;
        case 15:
            unk_C0[0].unk_08 = attrIt->GetAs_RwInt32();
            break;
        case 16:
            unk_C0[0].unk_0C = *(const RwV3d *)attrIt->GetAs_RwChar_ptr();
            break;
        case 17:
            if (attrIt->GetAs_RwChar_ptr())
            {
                unk_C0[0].unk_18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 19:
            unk_C0[0].unk_20 = attrIt->GetAs_RwInt32();
            break;
        case 20:
            unk_C0[0].unk_24 = attrIt->GetAs_RwInt32();
            break;
        case 21:
            unk_C0[0].unk_2C = attrIt->GetAs_RwInt32();
            break;
        case 22:
            unk_C0[0].unk_30 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 23:
            unk_C0[0].unk_34 = attrIt->GetAs_RwInt32();
            break;
        case 24:
            unk_C0[0].unk_48 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 25:
            unk_C0[0].unk_38 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 26:
            unk_C0[0].unk_40 = attrIt->GetAs_RwInt32();
            break;
        case 27:
            unk_C0[0].unk_3C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 28:
            unk_C0[0].unk_44 = attrIt->GetAs_RwInt32();
            break;
        case 29:
            unk_C0[0].unk_02 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 30:
            unk_C0[0].unk_4C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 31:
            unk_C0[0].unk_50 = attrIt->GetAs_RwInt32();
            break;
        case 32:
            unk_C0[0].unk_58 = attrIt->GetAs_RwInt32();
            break;
        case 33:
            unk_C0[0].unk_54 = attrIt->GetAs_RwInt32();
            break;
        case 34:
            unk_C0[0].unk_5C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 35:
            unk_C0[0].unk_60 = attrIt->GetAs_RwInt32();
            break;
        case 5:
            unk_C0[0].unk_64 = attrIt->GetAs_RwInt32();
            break;
        case 6:
            unk_C0[0].unk_6C = attrIt->GetAs_RwInt32();
            break;
        case 7:
            unk_C0[0].unk_70 = attrIt->GetAs_RwInt32();
            break;
        case 8:
            unk_C0[0].unk_68 = attrIt->GetAs_RwInt32();
            break;
        case 9:
            unk_C0[0].unk_74 = attrIt->GetAs_RwInt32();
            break;
        case 10:
            unk_C0[0].unk_78 = attrIt->GetAs_RwInt32();
            break;
        case 11:
            unk_C0[0].unk_7C = attrIt->GetAs_RwInt32();
            break;
        case 12:
            unk_C0[0].unk_80 = (RwReal)attrIt->GetAs_RwInt32();
            break;
        case 13:
            unk_C0[0].unk_84 = (RwReal)attrIt->GetAs_RwInt32();
            break;
        case 36:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_18 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_18.unk_00 || var_18.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_18, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_C0[1].unk_04, 0);
                }
            }
            break;
        case 37:
            unk_C0[1].unk_08 = attrIt->GetAs_RwInt32();
            break;
        case 38:
            unk_C0[1].unk_0C = *(const RwV3d *)attrIt->GetAs_RwChar_ptr();
            break;
        case 39:
            if (attrIt->GetAs_RwChar_ptr())
            {
                unk_C0[1].unk_18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 41:
            unk_C0[1].unk_20 = attrIt->GetAs_RwInt32();
            break;
        case 42:
            unk_C0[1].unk_24 = attrIt->GetAs_RwInt32();
            break;
        case 43:
            unk_C0[1].unk_2C = attrIt->GetAs_RwInt32();
            break;
        case 44:
            unk_C0[1].unk_30 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 45:
            unk_C0[1].unk_34 = attrIt->GetAs_RwInt32();
            break;
        case 46:
            unk_C0[1].unk_48 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 47:
            unk_C0[1].unk_38 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 48:
            unk_C0[1].unk_40 = attrIt->GetAs_RwInt32();
            break;
        case 49:
            unk_C0[1].unk_3C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 50:
            unk_C0[1].unk_44 = attrIt->GetAs_RwInt32();
            break;
        case 51:
            unk_C0[1].unk_02 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 52:
            unk_C0[1].unk_4C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 53:
            unk_C0[1].unk_50 = attrIt->GetAs_RwInt32();
            break;
        case 54:
            unk_C0[1].unk_58 = attrIt->GetAs_RwInt32();
            break;
        case 55:
            unk_C0[1].unk_54 = attrIt->GetAs_RwInt32();
            break;
        case 56:
            unk_C0[1].unk_5C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 57:
            unk_C0[1].unk_60 = attrIt->GetAs_RwInt32();
            break;
        case 58:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_20 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_20.unk_00 || var_20.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_20, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_C0[2].unk_04, 0);
                }
            }
            break;
        case 59:
            unk_C0[2].unk_08 = attrIt->GetAs_RwInt32();
            break;
        case 60:
            unk_C0[2].unk_0C = *(const RwV3d *)attrIt->GetAs_RwChar_ptr();
            break;
        case 61:
            if (attrIt->GetAs_RwChar_ptr())
            {
                unk_C0[2].unk_18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 63:
            unk_C0[2].unk_20 = attrIt->GetAs_RwInt32();
            break;
        case 64:
            unk_C0[2].unk_24 = attrIt->GetAs_RwInt32();
            break;
        case 65:
            unk_C0[2].unk_2C = attrIt->GetAs_RwInt32();
            break;
        case 66:
            unk_C0[2].unk_30 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 67:
            unk_C0[2].unk_34 = attrIt->GetAs_RwInt32();
            break;
        case 68:
            unk_C0[2].unk_48 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 69:
            unk_C0[2].unk_38 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 70:
            unk_C0[2].unk_40 = attrIt->GetAs_RwInt32();
            break;
        case 71:
            unk_C0[2].unk_3C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 72:
            unk_C0[2].unk_44 = attrIt->GetAs_RwInt32();
            break;
        case 73:
            unk_C0[2].unk_02 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 74:
            unk_C0[2].unk_4C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 75:
            unk_C0[2].unk_50 = attrIt->GetAs_RwInt32();
            break;
        case 76:
            unk_C0[2].unk_58 = attrIt->GetAs_RwInt32();
            break;
        case 77:
            unk_C0[2].unk_54 = attrIt->GetAs_RwInt32();
            break;
        case 78:
            unk_C0[2].unk_5C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 79:
            unk_C0[2].unk_60 = attrIt->GetAs_RwInt32();
            break;
        case 80:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_28 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_28.unk_00 || var_28.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_28, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_C0[3].unk_04, 0);
                }
            }
            break;
        case 81:
            unk_C0[3].unk_08 = attrIt->GetAs_RwInt32();
            break;
        case 82:
            unk_C0[3].unk_0C = *(const RwV3d *)attrIt->GetAs_RwChar_ptr();
            break;
        case 83:
            if (attrIt->GetAs_RwChar_ptr())
            {
                unk_C0[3].unk_18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 85:
            unk_C0[3].unk_20 = attrIt->GetAs_RwInt32();
            break;
        case 86:
            unk_C0[3].unk_24 = attrIt->GetAs_RwInt32();
            break;
        case 87:
            unk_C0[3].unk_2C = attrIt->GetAs_RwInt32();
            break;
        case 88:
            unk_C0[3].unk_30 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 89:
            unk_C0[3].unk_34 = attrIt->GetAs_RwInt32();
            break;
        case 90:
            unk_C0[3].unk_48 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 91:
            unk_C0[3].unk_38 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 92:
            unk_C0[3].unk_40 = attrIt->GetAs_RwInt32();
            break;
        case 93:
            unk_C0[3].unk_3C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 94:
            unk_C0[3].unk_44 = attrIt->GetAs_RwInt32();
            break;
        case 95:
            unk_C0[3].unk_02 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 96:
            unk_C0[3].unk_4C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 97:
            unk_C0[3].unk_50 = attrIt->GetAs_RwInt32();
            break;
        case 98:
            unk_C0[3].unk_58 = attrIt->GetAs_RwInt32();
            break;
        case 99:
            unk_C0[3].unk_54 = attrIt->GetAs_RwInt32();
            break;
        case 100:
            unk_C0[3].unk_5C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 101:
            unk_C0[3].unk_60 = attrIt->GetAs_RwInt32();
            break;
        case 102:
            if (attrIt->GetAs_RwChar_ptr())
            {
                Trigger_key var_30 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

                if (var_30.unk_00 || var_30.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_30, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&unk_C0[4].unk_04, 0);
                }
            }
            break;
        case 103:
            unk_C0[4].unk_08 = attrIt->GetAs_RwInt32();
            break;
        case 104:
            unk_C0[4].unk_0C = *(const RwV3d *)attrIt->GetAs_RwChar_ptr();
            break;
        case 105:
            if (attrIt->GetAs_RwChar_ptr())
            {
                unk_C0[4].unk_18 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            }
            break;
        case 107:
            unk_C0[4].unk_20 = attrIt->GetAs_RwInt32();
            break;
        case 108:
            unk_C0[4].unk_24 = attrIt->GetAs_RwInt32();
            break;
        case 109:
            unk_C0[4].unk_2C = attrIt->GetAs_RwInt32();
            break;
        case 110:
            unk_C0[4].unk_30 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 111:
            unk_C0[4].unk_34 = attrIt->GetAs_RwInt32();
            break;
        case 112:
            unk_C0[4].unk_48 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 113:
            unk_C0[4].unk_38 = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 114:
            unk_C0[4].unk_40 = attrIt->GetAs_RwInt32();
            break;
        case 115:
            unk_C0[4].unk_3C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 116:
            unk_C0[4].unk_44 = attrIt->GetAs_RwInt32();
            break;
        case 117:
            unk_C0[4].unk_02 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 118:
            unk_C0[4].unk_4C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 119:
            unk_C0[4].unk_50 = attrIt->GetAs_RwInt32();
            break;
        case 120:
            unk_C0[4].unk_58 = attrIt->GetAs_RwInt32();
            break;
        case 121:
            unk_C0[4].unk_54 = attrIt->GetAs_RwInt32();
            break;
        case 122:
            unk_C0[4].unk_5C = attrIt->GetAs_RwReal() * 100.0f;
            break;
        case 123:
            unk_C0[4].unk_60 = attrIt->GetAs_RwInt32();
            break;
        case 18:
            unk_C0[0].unk_88 = attrIt->GetAs_RwInt32();
            break;
        case 40:
            unk_C0[1].unk_88 = attrIt->GetAs_RwInt32();
            break;
        case 62:
            unk_C0[2].unk_88 = attrIt->GetAs_RwInt32();
            break;
        case 84:
            unk_C0[3].unk_88 = attrIt->GetAs_RwInt32();
            break;
        case 106:
            unk_C0[4].unk_88 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// On dword_4B67B8 it stops its emitters.
// match: ?HandleEvents@ParticleTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000A8D30
// sp-match: ?HandleEvents@ParticleTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000836B0
void ParticleTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    Trigger::HandleEvents(pMsg);
    if (pMsg.Id.p_msgrec == dword_4B67B8.p_msgrec)
    {
        sub_A8F40();
    }
}

// match: ?vf_020@ParticleTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000A8D70
// sp-match: ?vf_020@ParticleTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000823C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *ParticleTrigger::vf_020()
{
    RwInt32 var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 5; l4++)
    {
        if (unk_C0[l4].unk_00 && unk_C0[l4].unk_04)
        {
            if (unk_C0[l4].unk_28)
            {
                sub_F5C70(unk_C0[l4].unk_28);
            }
            unk_C0[l4].unk_28 = sub_F5740(this, l4, &unk_C0[l4]);
            if (l4 == 0 && unk_C0[l4].unk_64)
            {
                for (var_8 = 1; var_8 < 5; var_8++)
                {
                    if (unk_C0[var_8].unk_00 && unk_C0[var_8].unk_04)
                    {
                        sub_F5BC0(unk_C0[0].unk_28, this, var_8, &unk_C0[var_8]);
                    }
                }
                break;
            }
        }
    }
    return 0;
}

// match: ?sub_A8EE0@ParticleTrigger@@QAEXPAUtype_F5740@@@Z @ 0x000A8EE0
// sp-match: ?sub_A8EE0@ParticleTrigger@@QAEXPAUtype_F5740@@@Z @ 0x00082480
void ParticleTrigger::sub_A8EE0(type_F5740 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 5; var_4++)
    {
        if (unk_C0[var_4].unk_28 == arg_0)
        {
            unk_C0[var_4].unk_28 = 0;
        }
    }
}

// match: ?sub_A8F40@ParticleTrigger@@QAEXXZ @ 0x000A8F40
// sp-match: ?sub_A8F40@ParticleTrigger@@QAEXXZ @ 0x000824E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void ParticleTrigger::sub_A8F40()
{
    type_F5740 *var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 5; l4++)
    {
        var_8 = unk_C0[l4].unk_28;
        if (var_8)
        {
            sub_F5C70(var_8);
            unk_C0[l4].unk_28 = 0;
        }
    }
}

// match: ??_EParticleTrigger@@WBI@AEPAXI@Z @ 0x000A8FB0
// sp-match: ??_EParticleTrigger@@WBI@AEPAXI@Z @ 0x000825F0
