// SceneTrigger: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include <string.h>

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/SceneTrigger.h"

RWS_IMPLEMENT_CLASSID(SceneTrigger);
RWS_REGISTERCLASS(SceneTrigger);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0N@LIMIICJM@SceneTrigger?$AA@ @ 0x003D6368
// match: ??_7SceneTrigger@@6BCEventHandler@RWS@@@ @ 0x003D6378
// match: ??_7SceneTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003D6380
// match: __ehhandler$?MakeNew@SceneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BF6C
// match: __ehhandler$?MakeNew@SceneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BF74
// match: .CRT$XCU+0 @ 0x00426F44
// match: ?pSceneTriggerClassID@SceneTrigger@@2PBDB @ 0x00429188

// match: _$E2 @ 0x0030A960
// match: _$E3 @ 0x0030E0F0

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@SceneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000AF9C0
// match: __ehhandler$?MakeNew@SceneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300190
// match: __ehhandler$?MakeNew@SceneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030019F
// sp-match: ?MakeNew@SceneTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00087D70
RWS_DEFINE_MAKENEW(SceneTrigger)

// match: ??0SceneTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000AFA40
// sp-match: ??0SceneTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00087C50
SceneTrigger::SceneTrigger(const RWS::CAttributePacket &attr) : Trigger(attr)
{
    RwInt32 var_4;

    memset(&unk_C0, 0, 6);
    for (var_4 = 0; var_4 < 2; var_4++)
    {
        unk_C4[var_4] = 1;
    }
}

// match: ??_GSceneTrigger@@UAEPAXI@Z @ 0x000AFAB0
// sp-match: ??_GSceneTrigger@@UAEPAXI@Z @ 0x00087D60

// match: ??1SceneTrigger@@UAE@XZ @ 0x000AFAD0
// sp-match: ??1SceneTrigger@@UAE@XZ @ 0x00087C90
// (Defined in the class, in SceneTrigger.h.)

// match: ?HandleAttributes@SceneTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000AFB00
// sp-match: ?HandleAttributes@SceneTrigger@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00087CB0
void SceneTrigger::HandleAttributes(const RWS::CAttributePacket &attr)
{
    Trigger::HandleAttributes(attr);
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(SceneTrigger));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            unk_C2 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        case 1:
            unk_C0 = (RwInt16)attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ??_ESceneTrigger@@WBI@AEPAXI@Z @ 0x000AFBB0
// sp-match: ??_ESceneTrigger@@WBI@AEPAXI@Z @ 0x00087D50
