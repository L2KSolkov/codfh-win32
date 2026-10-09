// CNPCWeaponBehavior: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/CNPCWeaponBehavior.h"
#include "types/type_44350.h"
#include "types/type_4D53F8.h"
#include "types/type_72810.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D5E84
extern const RwReal flt_3D5E84 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(CNPCWeaponBehavior);
RWS_REGISTERCLASS(CNPCWeaponBehavior);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BD@LOMDDPKL@CNPCWeaponBehavior?$AA@ @ 0x003D5E70
// match: ?flt_3D5E84@@3MB @ 0x003D5E84
// match: ??_7CNPCWeaponBehavior@@6BCEventHandler@RWS@@@ @ 0x003D5E88
// match: ??_7CNPCWeaponBehavior@@6BCAttributeHandler@RWS@@@ @ 0x003D5E90
// match: __ehhandler$?MakeNew@CNPCWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BCC4
// match: __ehhandler$?MakeNew@CNPCWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BCCC
// match: __ehhandler$??0CNPCWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041BCE8
// match: __ehhandler$??0CNPCWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041BCF8
// match: __ehhandler$??1CNPCWeaponBehavior@@UAE@XZ>1>8 @ 0x0041BD14
// match: __ehhandler$??1CNPCWeaponBehavior@@UAE@XZ>1 @ 0x0041BD24
// match: .CRT$XCU+0 @ 0x00426F20
// match: ?pCNPCWeaponBehaviorClassID@CNPCWeaponBehavior@@2PBDB @ 0x00429164

// match: _$E2 @ 0x0030A7B0
// match: _$E3 @ 0x0030E060

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CNPCWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A58B0
// match: __ehhandler$?MakeNew@CNPCWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFF50
// match: __ehhandler$?MakeNew@CNPCWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFF5F
// sp-match: ?MakeNew@CNPCWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00081C90
RWS_DEFINE_MAKENEW(CNPCWeaponBehavior)

// match: ??0CNPCWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A5930
// match: __ehhandler$??0CNPCWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z-0x13 @ 0x002FFF70
// match: __ehhandler$??0CNPCWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x002FFF83
// sp-match: ??0CNPCWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00081120
CNPCWeaponBehavior::CNPCWeaponBehavior(const RWS::CAttributePacket &attr)
{
    unk_20 = -1;
    LinkMsg(iMsgSparkStartSystem, 0, 0x8000);
}

// match: ??_GCNPCWeaponBehavior@@UAEPAXI@Z @ 0x000A5A10
// sp-match: ??_GCNPCWeaponBehavior@@UAEPAXI@Z @ 0x00081C80

// match: ??1CNPCWeaponBehavior@@UAE@XZ @ 0x000A5A30
// match: __ehhandler$??1CNPCWeaponBehavior@@UAE@XZ-0x2F @ 0x002FFF90
// match: __ehhandler$??1CNPCWeaponBehavior@@UAE@XZ @ 0x002FFFBF
// sp-match: ??1CNPCWeaponBehavior@@UAE@XZ @ 0x000811A0
CNPCWeaponBehavior::~CNPCWeaponBehavior()
{
    UnLinkMsg(iMsgSparkStartSystem);
}

// Command 0 picks the settings; commands 1 to 75 fill them.
// match: ?HandleAttributes@CNPCWeaponBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A5AC0
// sp-match: ?HandleAttributes@CNPCWeaponBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00081210
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CNPCWeaponBehavior::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RwReal var_2C;
    RwReal loc28;
    RwReal slot_24;
    RwReal v20;
    RwReal loc1C;
    RwReal bp_18;
    type_4D53F8 *var_14;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator bp_8(attr, RWS_CLASSID_OF(CNPCWeaponBehavior));
    RWS::CAttributeCommandIterator ebp_10(attr, RWS_CLASSID_OF(CNPCWeaponBehavior));
    while (!bp_8.IsFinished())
    {
        if (bp_8->GetCommandId() == 0)
        {
            unk_20 = bp_8->GetAs_RwInt32();
        }
        ++bp_8;
    }
    if (unk_20 == -1)
    {
        return;
    }
    var_14 = sub_15CB10(unk_20);
    while (!ebp_10.IsFinished())
    {
        switch (ebp_10->GetCommandId())
        {
        case 1:
            var_14->unk_48 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 8:
            var_14->unk_78 = ebp_10->GetAs_RwInt32();
            break;
        case 9:
            var_14->unk_50 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 22:
            var_14->unk_70 = ebp_10->GetAs_RwInt32();
            break;
        case 23:
            var_14->unk_60 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 24:
            var_14->unk_68 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 29:
            var_14->unk_58 = *(const type_3DF8D8_04 *)ebp_10->GetAs_RwChar_ptr();
            break;
        case 28:
            var_14->sub_15CCA0(ebp_10->GetAs_RwInt32());
            break;
        case 25:
            var_14->unk_7C = ebp_10->GetAs_RwInt32();
            break;
        case 26:
            var_14->sub_15CC30(ebp_10->GetAs_RwUInt32());
            break;
        case 65:
            var_14->unk_184 = (RwReal)ebp_10->GetAs_RwUInt32();
            break;
        case 66:
            var_14->unk_188 = (RwReal)ebp_10->GetAs_RwUInt32();
            break;
        case 30:
            var_14->unk_80 = ebp_10->GetAs_RwInt32();
            break;
        case 31:
            var_14->unk_84 = ebp_10->GetAs_RwInt32();
            break;
        case 3:
            var_14->unk_88 = ebp_10->GetAs_RwInt32();
            break;
        case 4:
            var_14->unk_8C = ebp_10->GetAs_RwInt32();
            break;
        case 5:
            var_14->unk_90 = ebp_10->GetAs_RwInt32();
            break;
        case 32:
            var_14->sub_15CBD0(-ebp_10->GetAs_RwReal());
            break;
        case 33:
            var_14->sub_15CBF0(ebp_10->GetAs_RwInt32());
            break;
        case 34:
            var_14->sub_15CC10(ebp_10->GetAs_RwInt32());
            break;
        case 37:
            var_14->sub_15CC60(ebp_10->GetAs_RwReal() * 100.0f);
            break;
        case 35:
            var_14->sub_15CC80(ebp_10->GetAs_RwReal() * 60.0f);
            break;
        case 27:
            var_14->unk_E8 = ebp_10->GetAs_RwInt32();
            break;
        case 36:
            var_14->unk_FC = ebp_10->GetAs_RwReal() * 100.0f;
            break;
        case 38:
            var_14->unk_EC = ebp_10->GetAs_RwReal() * 100.0f;
            break;
        case 39:
            var_14->unk_F4 = ebp_10->GetAs_RwInt32();
            break;
        case 40:
            var_14->unk_F0 = ebp_10->GetAs_RwReal() * 100.0f;
            break;
        case 41:
            var_14->unk_F8 = ebp_10->GetAs_RwInt32();
            break;
        case 42:
            var_14->unk_124 = ebp_10->GetAs_RwInt32();
            break;
        case 2:
            var_14->unk_128 = ebp_10->GetAs_RwInt32();
            break;
        case 43:
            var_14->unk_118 = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 44:
            var_14->unk_11C = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 45:
            var_14->unk_120 = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 46:
            var_14->unk_12C = ebp_10->GetAs_RwInt32();
            break;
        case 47:
            var_14->unk_130 = ebp_10->GetAs_RwInt32();
            break;
        case 48:
            var_14->unk_134 = ebp_10->GetAs_RwInt32();
            break;
        case 49:
            var_14->unk_138 = ebp_10->GetAs_RwInt32();
            break;
        case 50:
            var_14->unk_13C = ebp_10->GetAs_RwInt32();
            break;
        case 51:
            var_14->unk_140 = ebp_10->GetAs_RwInt32();
            break;
        case 52:
            var_14->unk_144 = ebp_10->GetAs_RwInt32();
            break;
        case 53:
            var_14->unk_148 = ebp_10->GetAs_RwInt32();
            break;
        case 54:
            var_14->unk_14C = ebp_10->GetAs_RwInt32();
            break;
        case 55:
            var_14->unk_150 = ebp_10->GetAs_RwInt32();
            break;
        case 56:
            var_14->unk_154 = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 57:
            var_14->unk_158 = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 58:
            var_14->unk_15C = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 59:
            var_14->unk_160 = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 60:
            var_14->unk_164 = ebp_10->GetAs_RwInt32();
            break;
        case 61:
            var_14->unk_168 = -ebp_10->GetAs_RwReal();
            break;
        case 68:
            bp_18 = ebp_10->GetAs_RwReal();
            var_14->unk_16C = bp_18 * 100.0f;
            break;
        case 69:
            loc1C = ebp_10->GetAs_RwReal();
            var_14->unk_170 = loc1C * 100.0f;
            break;
        case 67:
            v20 = ebp_10->GetAs_RwReal();
            var_14->unk_174 = v20 * 100.0f;
            break;
        case 62:
            slot_24 = ebp_10->GetAs_RwReal();
            var_14->unk_178 = slot_24 * 100.0f;
            break;
        case 63:
            loc28 = ebp_10->GetAs_RwReal();
            var_14->unk_17C = loc28 * 100.0f;
            break;
        case 64:
            var_2C = ebp_10->GetAs_RwReal();
            var_14->unk_180 = var_2C * 100.0f;
            break;
        case 6:
            var_14->unk_34 = ebp_10->GetAs_RwInt32();
            break;
        case 7:
            if (ebp_10->GetAs_RwChar_ptr())
            {
                Trigger_key var_34 = *(const Trigger_key *)ebp_10->GetAs_RwChar_ptr();

                if (var_34.unk_00 || var_34.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_34, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&var_14->unk_30, 0);
                }
            }
            break;
        case 10:
            var_14->unk_00 = ebp_10->GetAs_RwInt32();
            break;
        case 11:
            if (ebp_10->GetAs_RwChar_ptr())
            {
                Trigger_key var_3C = *(const Trigger_key *)ebp_10->GetAs_RwChar_ptr();

                if (var_3C.unk_00 || var_3C.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_3C, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&var_14->unk_04, 0);
                }
            }
            break;
        case 12:
            var_14->unk_08 = ebp_10->GetAs_RwInt32();
            break;
        case 13:
            var_14->unk_0C = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 14:
            var_14->unk_10 = ebp_10->GetAs_RwInt32();
            break;
        case 15:
            var_14->unk_14 = ebp_10->GetAs_RwInt32();
            break;
        case 16:
            var_14->unk_18 = ebp_10->GetAs_RwInt32();
            break;
        case 17:
            if (ebp_10->GetAs_RwChar_ptr())
            {
                Trigger_key var_44 = *(const Trigger_key *)ebp_10->GetAs_RwChar_ptr();

                if (var_44.unk_00 || var_44.unk_04)
                {
                    sub_198900((type_3DF8D8_04 *)&var_44, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8B0, 0, (RwInt32)&var_14->unk_1C, 0);
                }
            }
            break;
        case 18:
            var_14->unk_20 = ebp_10->GetAs_RwInt32();
            break;
        case 19:
            var_14->unk_24 = ebp_10->GetAs_RwReal() * 60.0f;
            break;
        case 20:
            var_14->unk_28 = ebp_10->GetAs_RwInt32();
            break;
        case 21:
            var_14->unk_2C = ebp_10->GetAs_RwInt32();
            break;
        case 70:
            var_14->unk_100 = ebp_10->GetAs_RwReal() * 100.0f;
            break;
        case 71:
            var_14->unk_104 = ebp_10->GetAs_RwInt32();
            break;
        case 72:
            var_14->unk_108 = ebp_10->GetAs_RwInt32();
            break;
        case 73:
            var_14->unk_10C = ebp_10->GetAs_RwInt32();
            break;
        case 74:
            var_14->unk_110 = ebp_10->GetAs_RwReal() * 100.0f;
            break;
        case 75:
            var_14->unk_114 = ebp_10->GetAs_RwInt32();
            break;
        }
        ++ebp_10;
    }
}

// On the message Id: marks its settings ready, once.
// match: ?HandleEvents@CNPCWeaponBehavior@@UAEXAAVCMsg@RWS@@@Z @ 0x000A6BF0
// sp-match: ?HandleEvents@CNPCWeaponBehavior@@UAEXAAVCMsg@RWS@@@Z @ 0x00081C30
void CNPCWeaponBehavior::HandleEvents(RWS::CMsg &pMsg)
{
    type_4D53F8 *var_4;

    if (pMsg.Id.p_msgrec == iMsgSparkStartSystem.p_msgrec)
    {
        var_4 = sub_15CB10(unk_20);
        if (var_4)
        {
            var_4->sub_15CAA0();
        }
        UnLinkMsg(iMsgSparkStartSystem);
    }
}

// match: ??_ECNPCWeaponBehavior@@WBI@AEPAXI@Z @ 0x000A6C40
// sp-match: ??_ECNPCWeaponBehavior@@WBI@AEPAXI@Z @ 0x00081C70
