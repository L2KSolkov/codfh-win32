// HitDeathTestTrigger, a soldier spawner for testing hit deaths: its MakeNew, constructor and destructor. Its
// original file name is not in the image, so it is named for its start
// address.

#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/HitDeathTestTrigger.h"
#include "types/type_72810.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/data.h"

RWS_IMPLEMENT_CLASSID(HitDeathTestTrigger);
RWS_REGISTERCLASS(HitDeathTestTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BE@OLPPAMAK@HitDeathTestTrigger?$AA@ @ 0x003D5B54
// match: ??_7HitDeathTestTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5B68
// match: ??_7HitDeathTestTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5B70
// match: ??_C@_0BF@ECPHLFKP@PlayHitDeathReaction?$AA@ @ 0x003D5BA0
// match: __ehhandler$?MakeNew@HitDeathTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BAC4
// match: __ehhandler$?MakeNew@HitDeathTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BACC
// match: .CRT$XCU+0 @ 0x00426EF8
// match: ?pHitDeathTestTriggerClassID@HitDeathTestTrigger@@2PBDB @ 0x0042913C

// match: _$E2 @ 0x0030A5D0
// match: _$E3 @ 0x0030DFC0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@HitDeathTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A1CA0
// match: __ehhandler$?MakeNew@HitDeathTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFD90
// match: __ehhandler$?MakeNew@HitDeathTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFD9F
RWS_DEFINE_MAKENEW(HitDeathTestTrigger)

// match: ??0HitDeathTestTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A1D20
HitDeathTestTrigger::HitDeathTestTrigger(const RWS::CAttributePacket &attr) : SoldierTrigger(attr)
{
    RwInt32 var_4;

    memset(unk_1A0, 0, 0xC);
    for (var_4 = 0; var_4 < 6; var_4++)
    {
        unk_1A0[var_4 + 6] = 1;
    }
}

// match: ??_GHitDeathTestTrigger@@UAEPAXI@Z @ 0x000A1D90

// match: ??1HitDeathTestTrigger@@UAE@XZ @ 0x000A1DB0
// (Defined in the class, in HitDeathTestTrigger.h.)

// Commands 1 to 6: names whose bytes go to unk_1A0 (the hit-death values);
// 0: its own handle to the script ("PlayHitDeathReaction").
// match: ?HandleAttributes@HitDeathTestTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A1DE0
void HitDeathTestTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    SoldierTrigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(HitDeathTestTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 1:
        {
            Trigger_key var_10 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_10.unk_00 || var_10.unk_04)
                sub_198900((type_3DF8D8_04 *)&var_10, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F910, 0,
                           (RwInt32)&unk_1A0[0], 0);
            break;
        }
        case 2:
        {
            Trigger_key var_18 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_18.unk_00 || var_18.unk_04)
                sub_198900((type_3DF8D8_04 *)&var_18, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F910, 0,
                           (RwInt32)&unk_1A0[1], 0);
            break;
        }
        case 3:
        {
            Trigger_key var_20 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_20.unk_00 || var_20.unk_04)
                sub_198900((type_3DF8D8_04 *)&var_20, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F910, 0,
                           (RwInt32)&unk_1A0[2], 0);
            break;
        }
        case 4:
        {
            Trigger_key var_28 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_28.unk_00 || var_28.unk_04)
                sub_198900((type_3DF8D8_04 *)&var_28, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F910, 0,
                           (RwInt32)&unk_1A0[3], 0);
            break;
        }
        case 5:
        {
            Trigger_key var_30 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_30.unk_00 || var_30.unk_04)
                sub_198900((type_3DF8D8_04 *)&var_30, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F910, 0,
                           (RwInt32)&unk_1A0[4], 0);
            break;
        }
        case 6:
        {
            Trigger_key var_38 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_38.unk_00 || var_38.unk_04)
                sub_198900((type_3DF8D8_04 *)&var_38, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F910, 0,
                           (RwInt32)&unk_1A0[5], 0);
            break;
        }
        case 0:
        {
            RwInt32 var_3C = unk_3C;

            if (is_4B86FC_clear())
                sub_6B5F0("PlayHitDeathReaction", 0, (type_42E00_10 *)((RwInt32)this), 0, &var_3C, 1, true, false);
            break;
        }
        }
        ++attrIt;
    }
}

// match: ??_EHitDeathTestTrigger@@WBI@AEPAXI@Z @ 0x000A2070
