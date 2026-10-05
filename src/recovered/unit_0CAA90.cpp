// LadderTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "game/functions.h"
#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/LadderTrigger.h"
#include "types/type_10F710.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6D30
extern const RwReal flt_3D6D30 = 16.666666f;
// 0x003D6D34
extern const RwV3d stru_3D6D34 = { 0.0f, 1.0f, 0.0f };
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(LadderTrigger);
RWS_REGISTERCLASS(LadderTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@OPDJGBGB@LadderTrigger?$AA@ @ 0x003D6D20
// match: ?flt_3D6D30@@3MB @ 0x003D6D30
// match: ?stru_3D6D34@@3URwV3d@@B @ 0x003D6D34
// match: ??_7LadderTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6D40
// match: ??_7LadderTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6D48
// match: __ehhandler$?MakeNew@LadderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C9B8
// match: __ehhandler$?MakeNew@LadderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C9C0
// match: .CRT$XCU+0 @ 0x00426FCC
// match: ?pLadderTriggerClassID@LadderTrigger@@2PBDB @ 0x0042921C

// match: _$E2 @ 0x0030AFC0
// match: _$E3 @ 0x0030E310

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@LadderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CAA90
// match: __ehhandler$?MakeNew@LadderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300A40
// match: __ehhandler$?MakeNew@LadderTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300A4F
RWS_DEFINE_MAKENEW(LadderTrigger)

// match: ??0LadderTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CAB10
LadderTrigger::LadderTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C8 = 0;
    unk_CC = 0;
    unk_D0 = 1;
    unk_D4 = 0;
    unk_D8 = 0;
}

// match: ?vf_01C@LadderTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x000CABA0

// match: ??_GLadderTrigger@@UAEPAXI@Z @ 0x000CABC0

// match: ??1LadderTrigger@@UAE@XZ @ 0x000CABE0
LadderTrigger::~LadderTrigger()
{
}

// match: ?HandleAttributes@LadderTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CAC10
void LadderTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
}

// match: ?sub_CAC30@LadderTrigger@@QAEXPAUtype_3D3548@@@Z @ 0x000CAC30
void LadderTrigger::sub_CAC30(type_3D3548 *arg_0)
{
    type_10F710 *var_4;

    if (!unk_D0)
    {
    }
    else if (arg_0->unk_2C_4)
    {
        var_4 = (type_10F710 *)arg_0;
        var_4->sub_114920(this);
    }
}

// match: ?vf_028@LadderTrigger@@UAEHPAURwMatrixTag@@@Z @ 0x000CAC70
RwInt32 LadderTrigger::vf_028(RwMatrix *arg_0)
{
    RwV3d var_10;
    RwV3d var_20;
    RwV3d *var_28;
    RwV3d var_34;
    RwReal var_38;
    RwReal var_3C;
    RwInt32 var_40;
    RwMatrix var_80;
    RwMatrix var_C0;

    var_10.x = 0.0f;
    var_10.y = get_unk_4C();
    var_10.z = 0.0f;
    sub_1414C0(&var_10, &var_10, (RwMatrix *)unk_60);
    var_20.x = 0.0f;
    var_20.y = -get_unk_4C();
    var_20.z = 0.0f;
    sub_1414C0(&var_20, &var_20, (RwMatrix *)unk_60);
    var_28 = RwMatrixGetPos(arg_0);
    var_34.x = var_28->x;
    var_34.y = var_28->y;
    var_34.z = var_28->z;
    var_38 = sub_140C90(&var_34, &var_10);
    var_3C = sub_140C90(&var_34, &var_20);
    var_40 = 0;
    if (var_38 < var_3C)
    {
        var_40 = 1;
    }
    if (var_40)
    {
        return 1;
    }
    if (Trigger::vf_028(arg_0))
    {
        unk_D4 = 0;
        return 1;
    }
    var_80 = *arg_0;
    RwMatrixRotate(&var_C0, &stru_3D6D34, 180.0f, rwCOMBINEREPLACE);
    RwMatrixTransform(&var_80, &var_C0, rwCOMBINEPOSTCONCAT);
    if (Trigger::vf_028(&var_80))
    {
        unk_D4 = 1;
        return 1;
    }
    return 0;
}

// match: ??_ELadderTrigger@@WBI@AEPAXI@Z @ 0x000CAE10

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@LadderTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void LadderTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@LadderTrigger@@UAEHXZ (folded into 0x6FCA0)
RwInt32 LadderTrigger::vf_008()
{
    return 0x20;
}
