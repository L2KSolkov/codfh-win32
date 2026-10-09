// MountedWeaponTrigger: its MakeNew, constructor, destructor and handlers.
// Its original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/MountedWeaponTrigger.h"
#include "types/type_4E1B70.h"
#include "types/type_72810.h"

RWS_IMPLEMENT_CLASSID(MountedWeaponTrigger);
RWS_REGISTERCLASS(MountedWeaponTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BF@GGAAHNKJ@MountedWeaponTrigger?$AA@ @ 0x003D5E20
// match: ??_7MountedWeaponTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5E38
// match: ??_7MountedWeaponTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5E40
// match: __ehhandler$?MakeNew@MountedWeaponTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BCA0
// match: __ehhandler$?MakeNew@MountedWeaponTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BCA8
// match: .CRT$XCU+0 @ 0x00426F1C
// match: ?pMountedWeaponTriggerClassID@MountedWeaponTrigger@@2PBDB @ 0x00429160

// match: _$E2 @ 0x0030A780
// match: _$E3 @ 0x0030E050

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@MountedWeaponTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A5360
// match: __ehhandler$?MakeNew@MountedWeaponTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFF30
// match: __ehhandler$?MakeNew@MountedWeaponTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFF3F
// sp-match: ?MakeNew@MountedWeaponTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000810B0
RWS_DEFINE_MAKENEW(MountedWeaponTrigger)

// match: ??0MountedWeaponTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A53E0
// sp-match: ??0MountedWeaponTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00080D50
MountedWeaponTrigger::MountedWeaponTrigger(const RWS::CAttributePacket &attr)
    : Trigger(attr), unk_C0(1), unk_C4(0), unk_C8(0), unk_CC(0), unk_D4(-1.0f), unk_D8(-1.0f),
      unk_DC(-1)
{
    unk_F8.unk_00 = 0;
    unk_F8.unk_04 = 0;
}

// match: ?vf_01C@MountedWeaponTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x000A54D0
// sp-match: ?vf_01C@MountedWeaponTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x00080DD0

// match: ??_GMountedWeaponTrigger@@UAEPAXI@Z @ 0x000A54F0
// sp-match: ??_GMountedWeaponTrigger@@UAEPAXI@Z @ 0x00080E30

// match: ??1MountedWeaponTrigger@@UAE@XZ @ 0x000A5510
// sp-match: ??1MountedWeaponTrigger@@UAE@XZ @ 0x00080DE0
// (Defined in the class, in MountedWeaponTrigger.h.)

// match: ?HandleAttributes@MountedWeaponTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A5540
// sp-match: ?HandleAttributes@MountedWeaponTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00080E40
void MountedWeaponTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(MountedWeaponTrigger));
    while (!attrIt.IsFinished())
    {
        const type_3DF8D8_04 *var_C;

        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_E4 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_E4.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_E4, 0x2E, 0, 0, 0, 0);
            }
            break;
        case 6:
            var_C = (const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            unk_F8 = *var_C;
            sub_198900((type_3DF8D8_04 *)&unk_F8, 0xA, 0, 0, 0, 0);
            break;
        case 1:
            unk_C0 = attrIt->GetAs_RwInt32();
            break;
        case 2:
            unk_E0 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 3:
            unk_C4 = attrIt->GetAs_RwInt32();
            break;
        case 13:
            unk_D0 = attrIt->GetAs_RwInt32();
            break;
        case 4:
            unk_C8 = attrIt->GetAs_RwInt32();
            break;
        case 5:
            unk_CC = attrIt->GetAs_RwInt32();
            break;
        case 10:
            unk_D4 = attrIt->GetAs_RwReal();
            if (unk_D4 != -1.0f)
            {
                unk_D4 *= 0.5f;
            }
            break;
        case 11:
            unk_D8 = attrIt->GetAs_RwReal();
            if (unk_D8 != -1.0f)
            {
                unk_D8 *= 0.5f;
            }
            break;
        case 12:
            unk_DC = attrIt->GetAs_RwInt32();
            break;
        case 7:
            unk_EC = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 8:
            unk_F0 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        case 9:
            unk_F4 = *(const RwInt32 *)attrIt->GetAs_RwChar_ptr();
            break;
        }
        ++attrIt;
    }
}

// match: ?vf_020@MountedWeaponTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000A5880
// sp-match: ?vf_020@MountedWeaponTrigger@@UAEPAUtype_3D3548@@XZ @ 0x00080E10
type_3D3548 *MountedWeaponTrigger::vf_020()
{
    return sub_1669B0((type_712B0 *)this);
}

// match: ??_EMountedWeaponTrigger@@WBI@AEPAXI@Z @ 0x000A58A0
// sp-match: ??_EMountedWeaponTrigger@@WBI@AEPAXI@Z @ 0x00080E20

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@MountedWeaponTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void MountedWeaponTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@MountedWeaponTrigger@@UAEHXZ (folded into 0x1B3C20)
RwInt32 MountedWeaponTrigger::vf_008()
{
    return 27;
}
