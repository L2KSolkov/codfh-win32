// EndLevelTrigger: its MakeNew, constructor, destructor and methods. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "game/functions.h"
#include "types/EndLevelTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6E78
extern const RwReal flt_3D6E78 = 16.666666f;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(EndLevelTrigger);
RWS_REGISTERCLASS(EndLevelTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@CKABMAGK@EndLevelTrigger?$AA@ @ 0x003D6E68
// match: ?flt_3D6E78@@3MB @ 0x003D6E78
// match: ??_7EndLevelTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6E7C
// match: ??_7EndLevelTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6E84
// match: __ehhandler$?MakeNew@EndLevelTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041CB40
// match: __ehhandler$?MakeNew@EndLevelTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041CB48
// match: .CRT$XCU+0 @ 0x00426FDC
// match: ?pEndLevelTriggerClassID@EndLevelTrigger@@2PBDB @ 0x0042922C

// match: _$E2 @ 0x0030B080
// match: _$E3 @ 0x0030E350

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@EndLevelTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000CC090
// match: __ehhandler$?MakeNew@EndLevelTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300B80
// match: __ehhandler$?MakeNew@EndLevelTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00300B8F
// sp-match: ?MakeNew@EndLevelTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0009B000
RWS_DEFINE_MAKENEW(EndLevelTrigger)

// match: ??0EndLevelTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000CC110
// sp-match: ??0EndLevelTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0009AD60
EndLevelTrigger::EndLevelTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    unk_C0 = 0;
    unk_C4 = 0;
    unk_C6 = 0;
}

// match: ??_GEndLevelTrigger@@UAEPAXI@Z @ 0x000CC170
// sp-match: ??_GEndLevelTrigger@@UAEPAXI@Z @ 0x0009AF90

// match: ??1EndLevelTrigger@@UAE@XZ @ 0x000CC190
// sp-match: ??1EndLevelTrigger@@UAE@XZ @ 0x0009ADA0
EndLevelTrigger::~EndLevelTrigger()
{
}

// match: ?HandleAttributes@EndLevelTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000CC1C0
// sp-match: ?HandleAttributes@EndLevelTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0009ADC0
void EndLevelTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(EndLevelTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C0 = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ?sub_CC250@EndLevelTrigger@@QAEXH@Z @ 0x000CC250
// sp-match: ?sub_CC250@EndLevelTrigger@@QAEXH@Z @ 0x0009AFA0
void EndLevelTrigger::sub_CC250(RwInt32 arg_0)
{
    unk_C6 = 1;
    if (unk_C4)
    {
        sub_CC2F0();
    }
}

// match: ?sub_CC280@EndLevelTrigger@@QAEXH@Z @ 0x000CC280
// sp-match: ?sub_CC280@EndLevelTrigger@@QAEXH@Z @ 0x0009AE40
void EndLevelTrigger::sub_CC280(RwInt32 arg_0)
{
    unk_C6 = 0;
}

// match: ?sub_CC2A0@EndLevelTrigger@@QAEXH@Z @ 0x000CC2A0
// sp-match: ?sub_CC2A0@EndLevelTrigger@@QAEXH@Z @ 0x0009AFC0
void EndLevelTrigger::sub_CC2A0(RwInt32 arg_0)
{
    if (arg_0 && !unk_C4 && unk_C6)
    {
        sub_CC2F0();
    }
    unk_C4 = (RwInt16)arg_0;
}

// match: ?sub_CC2F0@EndLevelTrigger@@QAEXXZ @ 0x000CC2F0
// sp-match: ?sub_CC2F0@EndLevelTrigger@@QAEXXZ @ 0x0009AE50
void EndLevelTrigger::sub_CC2F0()
{
    type_3DF8D8 *var_4;

    var_4 = sub_198800((type_3DF8D8_04 *)&dword_4B9144);
    sub_EACA0(var_4->sub_197550(0, 0), 1, 0);
}

// match: ?sub_CC330@EndLevelTrigger@@QAEHXZ @ 0x000CC330
// sp-match: ?sub_CC330@EndLevelTrigger@@QAEHXZ @ 0x0009AE80
RwInt32 EndLevelTrigger::sub_CC330()
{
    RwInt32 var_4 = 0;

    switch (unk_C0)
    {
#ifdef CODFH_SP
    // single player maps the trigger's level to the next one (SP 0x9AE80's
    // jump table); the multiplayer build has no cases
    case 1: var_4 = 2; break;
    case 2: var_4 = 3; break;
    case 3: var_4 = 5; break;
    case 4: var_4 = 6; break;
    case 5: var_4 = 8; break;
    case 6: var_4 = 9; break;
    case 7: var_4 = 12; break;
    case 8: var_4 = 13; break;
    case 9: var_4 = 15; break;
    case 10: var_4 = 16; break;
    case 11: var_4 = 18; break;
    case 12: var_4 = 19; break;
    case 13: var_4 = 25; break;
    case 14: var_4 = 26; break;
    case 15: var_4 = 28; break;
    case 16: var_4 = 29; break;
    case 17: var_4 = 31; break;
    case 18: var_4 = 32; break;
    case 19: var_4 = 34; break;
    case 20: var_4 = 35; break;
    case 21: var_4 = 37; break;
    case 22: var_4 = 38; break;
#endif
    }
    return var_4;
}

// match: ??_EEndLevelTrigger@@WBI@AEPAXI@Z @ 0x000CC360
// sp-match: ??_EEndLevelTrigger@@WBI@AEPAXI@Z @ 0x0009AF80

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?HandleEvents@EndLevelTrigger@@UAEXAAVCMsg@RWS@@@Z (folded into 0xA2BF0)
void EndLevelTrigger::HandleEvents(class RWS::CMsg & pMsg)
{
    Trigger::HandleEvents(pMsg);
}

// ?vf_008@EndLevelTrigger@@UAEHXZ (folded into 0x194310)
RwInt32 EndLevelTrigger::vf_008()
{
    return 0x24;
}
