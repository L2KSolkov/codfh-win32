// StartingSections: its MakeNew, constructor, destructor and handlers. Its
// original file name is not in the image, so it is named for its start
// address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/StartingSections.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004B6830
RwInt32 dword_4B6830[4];
// 0x004B6840
RwInt32 dword_4B6840[4];
// 0x004B6850
RwInt32 dword_4B6850;
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(StartingSections);
RWS_REGISTERCLASS(StartingSections);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BB@GCCEKJDL@StartingSections?$AA@ @ 0x003D6414
// match: ??_7StartingSections@@6BCEventHandler@RWS@@@ @ 0x003D6428
// match: ??_7StartingSections@@6BCAttributeHandler@RWS@@@ @ 0x003D6430
// match: __ehhandler$?MakeNew@StartingSections@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BFFC
// match: __ehhandler$?MakeNew@StartingSections@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C004
// match: __ehhandler$??1StartingSections@@UAE@XZ>1>8 @ 0x0041C020
// match: __ehhandler$??1StartingSections@@UAE@XZ>1 @ 0x0041C028
// match: .CRT$XCU+0 @ 0x00426F50
// match: ?pStartingSectionsClassID@StartingSections@@2PBDB @ 0x004291A0

// match: _$E2 @ 0x0030A9F0
// match: _$E3 @ 0x0030E120

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@StartingSections@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000B0410
// match: __ehhandler$?MakeNew@StartingSections@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300210
// match: __ehhandler$?MakeNew@StartingSections@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030021F
RWS_DEFINE_MAKENEW(StartingSections)

// match: ??0StartingSections@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000B0490
StartingSections::StartingSections(const RWS::CAttributePacket &attr)
{
}

// match: ??_GStartingSections@@UAEPAXI@Z @ 0x000B0520

// match: ??1StartingSections@@UAE@XZ @ 0x000B0540
// match: __ehhandler$??1StartingSections@@UAE@XZ-0x8 @ 0x00300230
// match: __ehhandler$??1StartingSections@@UAE@XZ @ 0x00300238
// (Defined in the class, in StartingSections.h.)

// match: ?sub_B05C0@StartingSections@@SAXXZ @ 0x000B05C0
void StartingSections::sub_B05C0()
{
    RwInt32 var_4;

    dword_4B6850 = 0;
    for (var_4 = 0; var_4 < 4; var_4++)
    {
        dword_4B6840[var_4] = var_4 + 1;
        dword_4B6830[var_4] = var_4 + 1;
    }
}

// match: ?HandleAttributes@StartingSections@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000B0610
void StartingSections::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(StartingSections));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
        case 0:
            dword_4B6850 = attrIt->GetAs_RwInt32();
            break;
        case 1:
            dword_4B6840[0] = attrIt->GetAs_RwInt32();
            break;
        case 3:
            dword_4B6840[1] = attrIt->GetAs_RwInt32();
            break;
        case 5:
            dword_4B6840[2] = attrIt->GetAs_RwInt32();
            break;
        case 7:
            dword_4B6840[3] = attrIt->GetAs_RwInt32();
            break;
        case 2:
            dword_4B6830[0] = attrIt->GetAs_RwInt32();
            break;
        case 4:
            dword_4B6830[1] = attrIt->GetAs_RwInt32();
            break;
        case 6:
            dword_4B6830[2] = attrIt->GetAs_RwInt32();
            break;
        case 8:
            dword_4B6830[3] = attrIt->GetAs_RwInt32();
            break;
        }
        ++attrIt;
    }
}

// match: ??_EStartingSections@@WBI@AEPAXI@Z @ 0x000B07C0

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?HandleEvents@StartingSections@@UAEXAAVCMsg@RWS@@@Z (folded into the empty body at 0x15FB30)
void StartingSections::HandleEvents(RWS::CMsg &pMsg)
{
}
