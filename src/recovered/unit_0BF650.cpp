// FlakTrigger: its MakeNew, constructor, destructor and handlers, and
// VehicleTrigger's flag accessors the image places after its constructor. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/functions.h"
#include "types/FlakTrigger.h"
#include "types/type_3DF8D8.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6944
extern const RwReal flt_3D6944 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(FlakTrigger);
RWS_REGISTERCLASS(FlakTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0M@LKDPELLM@FlakTrigger?$AA@ @ 0x003D6938
// match: ?flt_3D6944@@3MB @ 0x003D6944
// match: ??_7FlakTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6948
// match: ??_7FlakTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6950
// match: __ehhandler$?MakeNew@FlakTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C3D4
// match: __ehhandler$?MakeNew@FlakTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C3DC
// match: .CRT$XCU+0 @ 0x00426F84
// match: ?pFlakTriggerClassID@FlakTrigger@@2PBDB @ 0x004291D4

// match: _$E2 @ 0x0030AC60
// match: _$E3 @ 0x0030E1F0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@FlakTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000BF650
// match: __ehhandler$?MakeNew@FlakTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300590
// match: __ehhandler$?MakeNew@FlakTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030059F
RWS_DEFINE_MAKENEW(FlakTrigger)

// match: ??0FlakTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000BF6D0
FlakTrigger::FlakTrigger(const RWS::CAttributePacket &attr) : VehicleTrigger(attr)
{
}

// match: ?vf_030@VehicleTrigger@@UAEHXZ @ 0x000BF700

// match: ?vf_034@VehicleTrigger@@UAEHXZ @ 0x000BF720

// match: ?vf_038@VehicleTrigger@@UAEHXZ @ 0x000BF740

// match: ??_GFlakTrigger@@UAEPAXI@Z @ 0x000BF760

// match: ??1FlakTrigger@@UAE@XZ @ 0x000BF780
// (Defined in the class, in FlakTrigger.h.)

// match: ?HandleAttributes@FlakTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000BF7B0
void FlakTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    VehicleTrigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(FlakTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_200 = attrIt->GetAs_RwReal() * 0.5f;
            break;
        case 1:
            unk_204 = attrIt->GetAs_RwInt32();
            break;
        case 2:
            unk_208 = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_20C = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?HandleEvents@FlakTrigger@@UAEXAAVCMsg@RWS@@@Z @ 0x000BF8C0
void FlakTrigger::HandleEvents(RWS::CMsg &pMsg)
{
    VehicleTrigger::HandleEvents(pMsg);
}

// match: ?vf_020@FlakTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000BF8E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *FlakTrigger::vf_020()
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
    if (!bp_4 || bp_4->vf_008() != 3)
    {
    }
    else
    {
        bp_8 = (type_3D3548 *)sub_15A7B0((type_712B0 *)((type_3D3548 *)this));
    }
    return bp_8;
}

// match: ??_EFlakTrigger@@WBI@AEPAXI@Z @ 0x000BF950
