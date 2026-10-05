// CMountedWeaponBehavior: its MakeNew, constructor, destructor and handlers.
// Its original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/mathutil.h"
#include "types/CMountedWeaponBehavior.h"
#include "types/type_4E1B70.h"

RWS_IMPLEMENT_CLASSID(CMountedWeaponBehavior);
RWS_REGISTERCLASS(CMountedWeaponBehavior);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BH@MBOBGPCF@CMountedWeaponBehavior?$AA@ @ 0x003D5DF4
// match: ??_7CMountedWeaponBehavior@@6BCEventHandler@RWS@@@ @ 0x003D5E0C
// match: ??_7CMountedWeaponBehavior@@6BCAttributeHandler@RWS@@@ @ 0x003D5E14
// match: __real@3c8efa35 @ 0x003D5E1C
// match: __ehhandler$?MakeNew@CMountedWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BC58
// match: __ehhandler$?MakeNew@CMountedWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BC60
// match: __ehhandler$??1CMountedWeaponBehavior@@UAE@XZ>1>8 @ 0x0041BC7C
// match: __ehhandler$??1CMountedWeaponBehavior@@UAE@XZ>1 @ 0x0041BC84
// match: .CRT$XCU+0 @ 0x00426F18
// match: ?pCMountedWeaponBehaviorClassID@CMountedWeaponBehavior@@2PBDB @ 0x0042915C

// match: _$E2 @ 0x0030A750
// match: _$E3 @ 0x0030E040

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@CMountedWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A4950
// match: __ehhandler$?MakeNew@CMountedWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFEF0
// match: __ehhandler$?MakeNew@CMountedWeaponBehavior@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFEFF
RWS_DEFINE_MAKENEW(CMountedWeaponBehavior)

// match: ??0CMountedWeaponBehavior@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A49D0
CMountedWeaponBehavior::CMountedWeaponBehavior(const RWS::CAttributePacket &attr)
{
}

// match: ??_GCMountedWeaponBehavior@@UAEPAXI@Z @ 0x000A4A60

// match: ??1CMountedWeaponBehavior@@UAE@XZ @ 0x000A4A80
// match: __ehhandler$??1CMountedWeaponBehavior@@UAE@XZ-0x8 @ 0x002FFF10
// match: __ehhandler$??1CMountedWeaponBehavior@@UAE@XZ @ 0x002FFF18
// (Defined in the class, in CMountedWeaponBehavior.h.)

// Command 0 picks the settings; commands 1 to 41 fill them.
// match: ?HandleAttributes@CMountedWeaponBehavior@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A4B00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void CMountedWeaponBehavior::HandleAttributes(const RWS::CAttributePacket &attr)
{
    type_4E1B70 *local_14 = 0;
    RwReal var18;

    RWS::CAttributeHandler::HandleAttributes(attr);
    RWS::CAttributeCommandIterator var8(attr, RWS_CLASSID_OF(CMountedWeaponBehavior));
    RWS::CAttributeCommandIterator loc10(attr, RWS_CLASSID_OF(CMountedWeaponBehavior));
    while (!var8.IsFinished())
    {
        if (var8->GetCommandId() == 0)
        {
            unk_20 = var8->GetAs_RwInt32();
        }
        ++var8;
    }
    local_14 = sub_166990(unk_20);
    while (!loc10.IsFinished())
    {
        switch (loc10->GetCommandId())
        {
        case 1:
            var18 = *(const RwReal *)loc10->GetAs_RwChar_ptr();
            var18 = var18 * 0.5f * 0.017453292f;
            local_14->unk_10 = tan_ref(var18);
            break;
        case 2:
            local_14->unk_2C = *(const RwV3d *)loc10->GetAs_RwChar_ptr();
            break;
        case 3:
            local_14->unk_14 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 4:
            local_14->unk_18 = *(const RwReal *)loc10->GetAs_RwChar_ptr();
            local_14->unk_18 *= 60.0f;
            break;
        case 5:
            local_14->unk_1C = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 7:
            local_14->unk_20 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 9:
            local_14->unk_24 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 10:
            local_14->unk_28 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 11:
            local_14->unk_38 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 12:
            local_14->unk_3C = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 8:
            local_14->unk_40 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 13:
            local_14->unk_44 = *(const type_3DF8D8_04 *)loc10->GetAs_RwChar_ptr();
            break;
        case 14:
            local_14->unk_4C = *(const type_3DF8D8_04 *)loc10->GetAs_RwChar_ptr();
            break;
        case 15:
            local_14->unk_54 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 16:
            local_14->unk_58 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 17:
            local_14->unk_5C = *(const type_3DF8D8_04 *)loc10->GetAs_RwChar_ptr();
            break;
        case 18:
            local_14->unk_64 = *(const type_3DF8D8_04 *)loc10->GetAs_RwChar_ptr();
            break;
        case 19:
            local_14->unk_74 = *(const RwV3d *)loc10->GetAs_RwChar_ptr();
            break;
        case 20:
            local_14->unk_80 = *(const RwV3d *)loc10->GetAs_RwChar_ptr();
            break;
        case 21:
            local_14->unk_A4 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 22:
            local_14->unk_8C = *(const RwV3d *)loc10->GetAs_RwChar_ptr();
            break;
        case 23:
            local_14->unk_98 = *(const RwV3d *)loc10->GetAs_RwChar_ptr();
            break;
        case 24:
            local_14->unk_A8 = *(const RwReal *)loc10->GetAs_RwChar_ptr();
            local_14->unk_A8 *= 60.0f;
            break;
        case 25:
            local_14->unk_AC = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 26:
            local_14->unk_B0 = *(const RwReal *)loc10->GetAs_RwChar_ptr();
            local_14->unk_B0 /= 2.0f;
            break;
        case 27:
            local_14->unk_B4 = *(const RwReal *)loc10->GetAs_RwChar_ptr();
            local_14->unk_B4 /= 2.0f;
            break;
        case 28:
            local_14->unk_B8 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 29:
            local_14->unk_BC = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 6:
            local_14->unk_C0 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 30:
            local_14->unk_C4 = *(const RwInt32 *)loc10->GetAs_RwChar_ptr();
            break;
        case 31:
            local_14->unk_CC = loc10->GetAs_RwInt32();
            break;
        case 32:
            local_14->unk_D0 = loc10->GetAs_RwInt32();
            break;
        case 33:
            local_14->unk_D4 = loc10->GetAs_RwInt32();
            break;
        case 34:
            local_14->unk_D8 = loc10->GetAs_RwInt32();
            break;
        case 35:
            local_14->unk_DC = loc10->GetAs_RwInt32();
            break;
        case 36:
            local_14->unk_E0 = loc10->GetAs_RwInt32();
            break;
        case 37:
            local_14->unk_E4 = loc10->GetAs_RwInt32();
            break;
        case 38:
            local_14->unk_E8 = loc10->GetAs_RwInt32();
            break;
        case 39:
            local_14->unk_EC = loc10->GetAs_RwInt32();
            break;
        case 40:
            local_14->unk_F0 = loc10->GetAs_RwInt32();
            break;
        case 41:
            local_14->unk_F4 = loc10->GetAs_RwInt32();
            break;
        }
        ++loc10;
    }
}

// match: ??_ECMountedWeaponBehavior@@WBI@AEPAXI@Z @ 0x000A5350

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?HandleEvents@CMountedWeaponBehavior@@UAEXAAVCMsg@RWS@@@Z (folded into the empty body at 0x15FB30)
void CMountedWeaponBehavior::HandleEvents(RWS::CMsg &pMsg)
{
}
