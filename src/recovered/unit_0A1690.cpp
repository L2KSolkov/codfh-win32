// AnimTestTrigger, a soldier spawner for testing animations: its MakeNew,
// constructor and destructor, and SoldierTrigger's constant functions the
// image places after its constructor. Its original file name is not in the
// image, so it is named for its start address.

#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/AnimTestTrigger.h"
#include "types/type_72810.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/data.h"

RWS_IMPLEMENT_CLASSID(AnimTestTrigger);
RWS_REGISTERCLASS(AnimTestTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BA@KCBCKHKB@AnimTestTrigger?$AA@ @ 0x003D5AD4
// match: ??_7AnimTestTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5AE4
// match: ??_7AnimTestTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5AEC
// match: ??_C@_0BL@OHHMEHEL@ChangeStateToPerformanceID?$AA@ @ 0x003D5B1C
// match: ??_C@_0BM@HPDCIOPF@ChangeStateToPerformanceMap?$AA@ @ 0x003D5B38
// match: __ehhandler$?MakeNew@AnimTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BAA0
// match: __ehhandler$?MakeNew@AnimTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BAA8
// match: .CRT$XCU+0 @ 0x00426EF4
// match: ?pAnimTestTriggerClassID@AnimTestTrigger@@2PBDB @ 0x00429138

// match: _$E2 @ 0x0030A5A0
// match: _$E3 @ 0x0030DFB0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@AnimTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A1690
// match: __ehhandler$?MakeNew@AnimTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFD70
// match: __ehhandler$?MakeNew@AnimTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFD7F
// sp-match: ?MakeNew@AnimTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0007E7E0
RWS_DEFINE_MAKENEW(AnimTestTrigger)

// match: ??0AnimTestTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A1710
// sp-match: ??0AnimTestTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x0007E380
AnimTestTrigger::AnimTestTrigger(const RWS::CAttributePacket &attr) : SoldierTrigger(attr)
{
    RwInt32 var_4;

    unk_1AC = 0;
    memset(unk_1A0, 0, 0xC);
    for (var_4 = 0; var_4 < 6; var_4++)
    {
        unk_1A0[var_4 + 6] = 1;
    }
    unk_1B0 = 0;
}

// match: ?vf_008@SoldierTrigger@@UAEHXZ @ 0x000A17A0
// sp-match: ?vf_008@SoldierTrigger@@UAEHXZ @ 0x0007E3D0

// match: ?vf_00C@SoldierTrigger@@UAEHXZ @ 0x000A17B0
// sp-match: ?vf_00C@SoldierTrigger@@UAEHXZ @ 0x0007E3E0

// match: ?vf_01C@SoldierTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x000A17D0
// sp-match: ?vf_01C@SoldierTrigger@@UAEPAUtype_3DF8D8_04@@XZ @ 0x00080100

// match: ?vf_024@SoldierTrigger@@UAEHXZ @ 0x000A17F0
// sp-match: ?vf_024@SoldierTrigger@@UAEHXZ @ 0x0007E400

// match: ??_GAnimTestTrigger@@UAEPAXI@Z @ 0x000A1810
// sp-match: ??_GAnimTestTrigger@@UAEPAXI@Z @ 0x0007E7D0

// match: ??1AnimTestTrigger@@UAE@XZ @ 0x000A1830
// sp-match: ??1AnimTestTrigger@@UAE@XZ @ 0x0007E410
// (Defined in the class, in AnimTestTrigger.h.)

// Commands 1 to 6: names whose bytes go to unk_1A0 (the hit-death values);
// 0: its own performance id to the script ("ChangeStateToPerformanceMap");
// 7 and 9: performance map names (kind 0xD) while dword_4B8710 is set, 8 and
// 10: their ids to the script ("ChangeStateToPerformanceID").
// match: ?HandleAttributes@AnimTestTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A1860
// sp-match: ?HandleAttributes@AnimTestTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x0007E430
void AnimTestTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    SoldierTrigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(AnimTestTrigger));
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
                sub_6B5F0("ChangeStateToPerformanceMap", 0, (type_42E00_10 *)((RwInt32)this), 0, &var_3C, 1, true, false);
            break;
        }
        case 7:
        {
            const type_73050 *var_40 = (const type_73050 *)attrIt->GetAs_RwChar_ptr();

            if (dword_4B8710 && (var_40->unk_00 || var_40->unk_04))
                unk_1AC = (type_198900_perf *)sub_198900((type_3DF8D8_04 *)var_40, 0xD, 0, 0, 0, 0);
            break;
        }
        case 8:
            if (unk_1AC && unk_1AC->get_unk_18() != -1)
            {
                RwInt32 var_44 = unk_1AC->get_unk_18();

                if (is_4B86FC_clear())
                    sub_6B5F0("ChangeStateToPerformanceID", 0, (type_42E00_10 *)((RwInt32)this), 0, &var_44, 1, true, false);
            }
            break;
        case 9:
        {
            const type_73050 *var_48 = (const type_73050 *)attrIt->GetAs_RwChar_ptr();

            if (dword_4B8710 && var_48->unk_00 && var_48->unk_00 != -1 && var_48->unk_04 != -1)
                unk_1B0 = (type_198900_perf *)sub_198900((type_3DF8D8_04 *)var_48, 0xD, 0, 0, 0, 0);
            break;
        }
        case 10:
            if (unk_1B0 && unk_1B0->get_unk_18() != -1)
            {
                RwInt32 var_4C = unk_1B0->get_unk_18();

                if (is_4B86FC_clear())
                    sub_6B5F0("ChangeStateToPerformanceID", 0, (type_42E00_10 *)((RwInt32)this), 0, &var_4C, 1, true, false);
            }
            break;
        }
        ++attrIt;
    }
}

// match: ??_EAnimTestTrigger@@WBI@AEPAXI@Z @ 0x000A1C90
// sp-match: ??_EAnimTestTrigger@@WBI@AEPAXI@Z @ 0x0007E7C0
