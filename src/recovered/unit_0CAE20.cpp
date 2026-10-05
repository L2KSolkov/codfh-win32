// ShrimpTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "rws/ceventhandler.h"
#include "types/ShrimpTrigger.h"
#include "types/type_72810.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6D88
extern const RwReal flt_3D6D88 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(ShrimpTrigger);
RWS_REGISTERCLASS(ShrimpTrigger);
// Vtables (.rdata, PLAN M5): each in its own placement range (config/splits.txt).
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0O@ENBKIOHK@ShrimpTrigger?$AA@ @ 0x003D6D78
// match: ?flt_3D6D88@@3MB @ 0x003D6D88
// match: ??_7type_17CC40@@6B@ @ 0x003D6D8C
// match: ??_7ShrimpTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6D90
// match: ??_7ShrimpTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6D98
// match: __ehhandler$?MakeNew@ShrimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C9DC
// match: __ehhandler$?MakeNew@ShrimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C9E4
// match: __ehhandler$??0ShrimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1>8 @ 0x0041CA00
// match: __ehhandler$??0ShrimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z>1 @ 0x0041CA18
// match: __ehhandler$??1ShrimpTrigger@@UAE@XZ>1>8 @ 0x0041CA34
// match: __ehhandler$??1ShrimpTrigger@@UAE@XZ>1 @ 0x0041CA4C
// match: .CRT$XCU+0 @ 0x00426FD0
// match: ?pShrimpTriggerClassID@ShrimpTrigger@@2PBDB @ 0x00429220

// match: _$E2 @ 0x0030AFF0
// match: _$E3 @ 0x0030E320

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@ShrimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CAE20
// match: __ehhandler$?MakeNew@ShrimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300A60
// match: __ehhandler$?MakeNew@ShrimpTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300A6F
RWS_DEFINE_MAKENEW(ShrimpTrigger)

// match: ??0ShrimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CAEA0
// match: __ehhandler$??0ShrimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z-0x24 @ 0x00300A80
// match: __ehhandler$??0ShrimpTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00300AA4
ShrimpTrigger::ShrimpTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0.unk_00 = 0;
    unk_C0.unk_04 = 0;
    unk_C8.unk_00 = 0;
    unk_C8.unk_04 = 0;
    unk_D0 = 0;
    unk_D4 = 0;
    unk_D8 = 0;
    unk_E8.sub_D48D0(0);
    unk_DC = 1.0f;
    LinkMsg(RWS::iMsgStartSystem, 0, 0x8000);
    LinkMsg(dword_4B67B8, 0, 0x8000);
    LinkMsg(dword_4B67C0, 0, 0x8000);
    unk_EC.sub_17CC40(this);
}

// match: ??1type_17CC40@@UAE@XZ @ 0x000CB040
// match: ??_Gtype_17CC40@@UAEPAXI@Z @ 0x000CB060
// (Defined in the struct, in type_17CC40.h.)

// match: ?vf_00C@ShrimpTrigger@@UAEHXZ @ 0x000CB0A0
RwInt32 ShrimpTrigger::vf_00C()
{
    return unk_E4;
}

// match: ??_GShrimpTrigger@@UAEPAXI@Z @ 0x000CB0C0

// match: ??1ShrimpTrigger@@UAE@XZ @ 0x000CB0E0
// match: __ehhandler$??1ShrimpTrigger@@UAE@XZ-0x24 @ 0x00300AB0
// match: __ehhandler$??1ShrimpTrigger@@UAE@XZ @ 0x00300AD4
ShrimpTrigger::~ShrimpTrigger()
{
    UnLinkMsg(RWS::iMsgStartSystem);
    UnLinkMsg(dword_4B67B8);
    UnLinkMsg(dword_4B67C0);
}

// match: ?HandleAttributes@ShrimpTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CB190
void ShrimpTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(ShrimpTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();
            if (unk_C0.unk_00 || unk_C0.unk_04)
            {
                if (!unk_D4)
                {
                    sub_198900((type_3DF8D8_04 *)&unk_C0, 3, 0, 0, 0, 0);
                }
                else
                {
                    sub_198900((type_3DF8D8_04 *)&unk_C0, 0x30, 0, 0, 0, 0);
                }
            }
            break;
        case 1:
        {
            type_3DF8D8_04 var_10 = *(const type_3DF8D8_04 *)attrIt->GetAs_RwChar_ptr();

            if (var_10.unk_00 || var_10.unk_04)
            {
                unk_C8 = var_10;
            }
            break;
        }
        case 2:
            unk_D0 = attrIt->GetAs_RwInt32();
            break;
        case 3:
            unk_E4 = attrIt->GetAs_RwInt32();
            if (unk_E4 < 0)
            {
                unk_E4 = 0x7FFFFFFF;
            }
            unk_E0 = unk_E4;
            break;
        case 4:
            unk_DC = attrIt->GetAs_RwReal();
            break;
        }
        ++attrIt;
    }
}

// match: ?vf_020@ShrimpTrigger@@UAEPAUtype_3D3548@@XZ @ 0x000CB370
type_3D3548 *ShrimpTrigger::vf_020()
{
    type_3D3548 *var_4;

    if (unk_EC.sub_17CD10())
    {
        var_4 = dword_4E723C;
        if (!var_4)
        {
            sub_17D330(this);
            var_4 = dword_4E723C;
        }
        return var_4;
    }
    return 0;
}

// match: ?vf_010@ShrimpTrigger@@UAEXHH@Z @ 0x000CB3C0
void ShrimpTrigger::vf_010(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0)
    {
        if (unk_E4 != 0x7FFFFFFF)
        {
            unk_E4 += arg_4;
        }
    }
    else if (arg_4 < 0)
    {
        unk_E4 = 0x7FFFFFFF;
    }
    else
    {
        unk_E4 = arg_4;
    }
}

// match: ??_EShrimpTrigger@@WBI@AEPAXI@Z @ 0x000CB420

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@ShrimpTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void ShrimpTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@ShrimpTrigger@@UAEHXZ (folded into 0x1940D0)
RwInt32 ShrimpTrigger::vf_008()
{
    return 0x21;
}

// ?vf_018@ShrimpTrigger@@UAEHXZ (folded into 0x115460)
RwInt32 ShrimpTrigger::vf_018()
{
    return 1;
}
