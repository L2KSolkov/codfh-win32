// SceneTestTrigger, a soldier spawner for testing scenes: its MakeNew, constructor and destructor. Its
// original file name is not in the image, so it is named for its start
// address.

#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/SceneTestTrigger.h"
#include "types/type_72810.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/data.h"

RWS_IMPLEMENT_CLASSID(SceneTestTrigger);
RWS_REGISTERCLASS(SceneTestTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@OPGODLAJ@SceneTestTrigger?$AA@ @ 0x003D5BB8
// match: ??_7SceneTestTrigger@@6BCEventHandler@RWS@@@ @ 0x003D5BCC
// match: ??_7SceneTestTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D5BD4
// match: ??_C@_0BG@CIBOLJGI@ChangeStateToSceneMap?$AA@ @ 0x003D5C04
// match: __ehhandler$?MakeNew@SceneTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BAE8
// match: __ehhandler$?MakeNew@SceneTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BAF0
// match: .CRT$XCU+0 @ 0x00426EFC
// match: ?pSceneTestTriggerClassID@SceneTestTrigger@@2PBDB @ 0x00429140

// match: _$E2 @ 0x0030A600
// match: _$E3 @ 0x0030DFD0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SceneTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A2080
// match: __ehhandler$?MakeNew@SceneTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFDB0
// match: __ehhandler$?MakeNew@SceneTestTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFDBF
RWS_DEFINE_MAKENEW(SceneTestTrigger)

// match: ??0SceneTestTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A2100
SceneTestTrigger::SceneTestTrigger(const RWS::CAttributePacket &attr) : SoldierTrigger(attr)
{
    RwInt32 var_4;

    unk_1A8 = 0;
    memset(unk_1A0, 0, 6);
    for (var_4 = 0; var_4 < 2; var_4++)
    {
        unk_1A0[var_4 + 4] = 1;
    }
}

// match: ??_GSceneTestTrigger@@UAEPAXI@Z @ 0x000A2180

// match: ??1SceneTestTrigger@@UAE@XZ @ 0x000A21A0
// (Defined in the class, in SceneTestTrigger.h.)

// Commands 1 and 2: names whose words go to unk_1A0 (the scene values); 0:
// its own handle to the script ("ChangeStateToSceneMap"); 3: a performance
// map name (kind 0xD) while dword_4B8710 is set, 4: its id to the script
// ("ChangeStateToPerformanceID").
// match: ?HandleAttributes@SceneTestTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000A21D0
void SceneTestTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    SoldierTrigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(SceneTestTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 1:
        {
            Trigger_key var_10 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_10.unk_00 || var_10.unk_04)
                sub_198900((type_3DF8D8_04 *)&var_10, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8E0, 0, (RwInt32)&unk_1A0[0], 0);
            break;
        }
        case 2:
        {
            Trigger_key var_18 = *(const Trigger_key *)attrIt->GetAs_RwChar_ptr();

            if (var_18.unk_00 || var_18.unk_04)
                sub_198900((type_3DF8D8_04 *)&var_18, 1, (void (*)(RwInt32, RwInt32, RwInt32))sub_18F8E0, 0, (RwInt32)&unk_1A0[2], 0);
            break;
        }
        case 0:
        {
            RwInt32 var_1C = unk_3C;

            if (is_4B86FC_clear())
                sub_6B5F0("ChangeStateToSceneMap", 0, (type_42E00_10 *)((RwInt32)this), 0, &var_1C, 1, true, false);
            break;
        }
        case 3:
        {
            const type_73050 *var_20 = (const type_73050 *)attrIt->GetAs_RwChar_ptr();

            if (dword_4B8710 && var_20->unk_00)
                unk_1A8 = (type_198900_perf *)sub_198900((type_3DF8D8_04 *)var_20, 0xD, 0, 0, 0, 0);
            break;
        }
        case 4:
            if (unk_1A8 && unk_1A8->get_unk_18() != -1)
            {
                RwInt32 var_24 = unk_1A8->get_unk_18();

                if (is_4B86FC_clear())
                    sub_6B5F0("ChangeStateToPerformanceID", 0, (type_42E00_10 *)((RwInt32)this), 0, &var_24, 1, true, false);
            }
            break;
        }
        ++attrIt;
    }
}

// match: ??_ESceneTestTrigger@@WBI@AEPAXI@Z @ 0x000A23E0
