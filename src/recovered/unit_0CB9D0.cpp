// GimpVehicleTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "game/functions.h"
#include "types/GimpVehicleTrigger.h"
#include "types/type_72810.h"
#include "types/type_3DF8D8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6E2C
extern const RwReal flt_3D6E2C = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(GimpVehicleTrigger);
RWS_REGISTERCLASS(GimpVehicleTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BD@IJKNIMLN@GimpVehicleTrigger?$AA@ @ 0x003D6E18
// match: ?flt_3D6E2C@@3MB @ 0x003D6E2C
// match: ??_7GimpVehicleTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6E30
// match: ??_7GimpVehicleTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6E38
// match: __ehhandler$?MakeNew@GimpVehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041CAD4
// match: __ehhandler$?MakeNew@GimpVehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041CADC
// match: __ehhandler$??0GimpVehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041CAF8
// match: __ehhandler$??0GimpVehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041CB00
// match: __ehhandler$??1GimpVehicleTrigger@@UAE@XZ>1>8 @ 0x0041CB1C
// match: __ehhandler$??1GimpVehicleTrigger@@UAE@XZ>1 @ 0x0041CB24
// match: .CRT$XCU+0 @ 0x00426FD8
// match: ?pGimpVehicleTriggerClassID@GimpVehicleTrigger@@2PBDB @ 0x00429228

// match: _$E2 @ 0x0030B050
// match: _$E3 @ 0x0030E340

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@GimpVehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CB9D0
// match: __ehhandler$?MakeNew@GimpVehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300B20
// match: __ehhandler$?MakeNew@GimpVehicleTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300B2F
RWS_DEFINE_MAKENEW(GimpVehicleTrigger)

// match: ??0GimpVehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CBA50
// match: __ehhandler$??0GimpVehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x8 @ 0x00300B40
// match: __ehhandler$??0GimpVehicleTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300B48
GimpVehicleTrigger::GimpVehicleTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0.unk_00 = 0;
    unk_C0.unk_04 = 0;
    unk_C8.unk_00 = 0;
    unk_C8.unk_04 = 0;
    unk_D0.unk_00 = 0;
    unk_D0.unk_04 = 0;
    unk_E0 = -1;
    unk_F4 = 0;
    unk_F8 = 0;
    unk_E4 = 200;
    unk_E8 = 500;
    LinkMsg(dword_4B8750, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
}

// match: ??_GGimpVehicleTrigger@@UAEPAXI@Z @ 0x000CBC00

// match: ??1GimpVehicleTrigger@@UAE@XZ @ 0x000CBC20
// match: __ehhandler$??1GimpVehicleTrigger@@UAE@XZ-0x8 @ 0x00300B60
// match: __ehhandler$??1GimpVehicleTrigger@@UAE@XZ @ 0x00300B68
GimpVehicleTrigger::~GimpVehicleTrigger()
{
    UnLinkMsg(dword_4B8750);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// Commands 3 and 4 first, then the rest.
// match: ?HandleAttributes@GimpVehicleTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CBCB0
void GimpVehicleTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator stk_10(attr, RWS_CLASSID_OF(GimpVehicleTrigger));
    while (!stk_10.IsFinished())
    {
        switch (stk_10->GetCommandId())
        {
        case 3:
            unk_F4 = stk_10->GetAs_RwInt32();
            break;
        case 4:
            unk_F8 = stk_10->GetAs_RwInt32();
            break;
        }
        ++stk_10;
    }
    RWS::CAttributeCommandIterator var8(attr, RWS_CLASSID_OF(GimpVehicleTrigger));
    while (!var8.IsFinished())
    {
        switch (var8->GetCommandId())
        {
        case 0:
            unk_D8 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            if (unk_D8.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_D8, 0x2E, 0, 0, 0, 0);
            }
            break;
        case 2:
            unk_C0 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            if (unk_C0.unk_00 || unk_C0.unk_04)
            {
                RwUInt8 *var_14 = (RwUInt8 *)sub_198900((type_3DF8D8_04 *)&unk_C0, 0x27, 0, 0, 0, 0);

                if (unk_F4)
                {
                    *(RwInt16 *)(var_14 + 0xC) = 1;
                }
            }
            break;
        case 5:
            unk_E0 = var8->GetAs_RwInt32();
            break;
        case 6:
            unk_EC = var8->GetAs_RwInt32();
            break;
        case 7:
            unk_F0 = var8->GetAs_RwInt32();
            break;
        case 8:
            unk_C8 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            sub_198900((type_3DF8D8_04 *)&unk_C8, 0xA, 0, 0, 0, 0);
            break;
        case 9:
            unk_D0 = *(const type_3DF8D8_04 *)var8->GetAs_RwChar_ptr();
            if (unk_D0.unk_00)
            {
                sub_198900((type_3DF8D8_04 *)&unk_D0, 0xC, 0, 0, 0, 0);
            }
            break;
        case 10:
            unk_E4 = var8->GetAs_RwInt32();
            break;
        case 11:
            unk_E8 = var8->GetAs_RwInt32();
            break;
        }
        ++var8;
    }
}

// match: ?vf_020@GimpVehicleTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000CBFF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *GimpVehicleTrigger::vf_020()
{
    type_3DF8D8 *var_C;
    type_3D3548 *bp_8;
    type_3DF8D8 *bp_4;

    bp_8 = 0;
    bp_4 = 0;
    var_C = sub_198800(&unk_C0);
    if (var_C)
    {
        bp_4 = ((type_3DFE7C *)var_C)->sub_1954D0();
    }
    if (!bp_4)
    {
    }
    else
    {
        switch (unk_E0)
        {
        case 0:
            bp_8 = sub_17E680(this);
            break;
        case 1:
            bp_8 = sub_180CF0(this);
            break;
        }
    }
    return bp_8;
}

// match: ??_EGimpVehicleTrigger@@WBI@AEPAXI@Z @ 0x000CC080

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@GimpVehicleTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void GimpVehicleTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@GimpVehicleTrigger@@UAEHXZ (folded into 0x194290)
RwInt32 GimpVehicleTrigger::vf_008()
{
    return 0x23;
}
