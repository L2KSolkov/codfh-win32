// LevelInfo: its MakeNew, constructor, destructor and handler. Its original
// file name is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/LevelInfo.h"

// Its data definitions (PLAN M5), in the image's address order.
#ifdef CODFH_SP // reals in single player (SP 0x966E0)
RwReal dword_4B686C;
RwReal dword_4B6870;
RwReal dword_4B6874;
RwReal dword_4B6878;
RwReal dword_4B687C;
#else
// 0x004B686C
RwInt32 dword_4B686C;
// 0x004B6870
RwInt32 dword_4B6870;
// 0x004B6874
RwInt32 dword_4B6874;
// 0x004B6878
RwInt32 dword_4B6878;
// 0x004B687C
RwInt32 dword_4B687C;
#endif
// End of its data definitions.


RWS_IMPLEMENT_CLASSID(LevelInfo);
RWS_REGISTERCLASS(LevelInfo);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_09GCKFPKMK@LevelInfo?$AA@ @ 0x003D6AEC
// match: ??_7LevelInfo@@6BCEventHandler@RWS@@@ @ 0x003D6AF8
// match: ??_7LevelInfo@@6BCAttributeHandler@RWS@@@ @ 0x003D6B00
// match: __ehhandler$?MakeNew@LevelInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041C618
// match: __ehhandler$?MakeNew@LevelInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041C620
// match: __ehhandler$??1LevelInfo@@UAE@XZ>1>8 @ 0x0041C63C
// match: __ehhandler$??1LevelInfo@@UAE@XZ>1 @ 0x0041C644
// match: .CRT$XCU+0 @ 0x00426FA4
// match: ?pLevelInfoClassID@LevelInfo@@2PBDB @ 0x004291F4

// match: _$E2 @ 0x0030ADE0
// match: _$E3 @ 0x0030E270

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@LevelInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000C5A60
// match: __ehhandler$?MakeNew@LevelInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300720
// match: __ehhandler$?MakeNew@LevelInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030072F
// sp-match: ?MakeNew@LevelInfo@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00096820
RWS_DEFINE_MAKENEW(LevelInfo)

// match: ??0LevelInfo@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000C5AE0
// sp-match: ??0LevelInfo@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00096640
LevelInfo::LevelInfo(const RWS::CAttributePacket &attr)
{
}

// match: ??_GLevelInfo@@UAEPAXI@Z @ 0x000C5B70
// sp-match: ??_GLevelInfo@@UAEPAXI@Z @ 0x00096810

// match: ??1LevelInfo@@UAE@XZ @ 0x000C5B90
// match: __ehhandler$??1LevelInfo@@UAE@XZ-0x8 @ 0x00300740
// match: __ehhandler$??1LevelInfo@@UAE@XZ @ 0x00300748
// sp-match: ??1LevelInfo@@UAE@XZ @ 0x00096680
LevelInfo::~LevelInfo()
{
}

// match: ?sub_C5C10@LevelInfo@@SAXXZ @ 0x000C5C10
// sp-match: ?sub_C5C10@LevelInfo@@SAXXZ @ 0x000966E0
void LevelInfo::sub_C5C10()
{
    dword_4B686C = 0;
    dword_4B6870 = 0;
    dword_4B6874 = 0;
    dword_4B6878 = 0;
    dword_4B687C = 0;
}

// match: ?HandleAttributes@LevelInfo@@UAEXABVCAttributePacket@RWS@@@Z @ 0x000C5C50
// sp-match: ?HandleAttributes@LevelInfo@@UAEXABVCAttributePacket@RWS@@@Z @ 0x00096720
void LevelInfo::HandleAttributes(const RWS::CAttributePacket &attr)
{
    RWS::CAttributeCommandIterator attrIt(attr, RWS_CLASSID_OF(LevelInfo));
    while (!attrIt.IsFinished())
    {
        switch (attrIt->GetCommandId())
        {
#ifdef CODFH_SP // reals in single player (SP 0x96720 copies the commands' values as they are)
        case 0:
            dword_4B686C = attrIt->GetAs_RwReal();
            break;
        case 1:
            dword_4B6870 = attrIt->GetAs_RwReal();
            break;
        case 2:
            dword_4B6874 = attrIt->GetAs_RwReal();
            break;
        case 3:
            dword_4B6878 = attrIt->GetAs_RwReal();
            break;
        case 4:
            dword_4B687C = attrIt->GetAs_RwReal();
            break;
#else
        case 0:
            dword_4B686C = attrIt->GetAs_RwInt32();
            break;
        case 1:
            dword_4B6870 = attrIt->GetAs_RwInt32();
            break;
        case 2:
            dword_4B6874 = attrIt->GetAs_RwInt32();
            break;
        case 3:
            dword_4B6878 = attrIt->GetAs_RwInt32();
            break;
        case 4:
            dword_4B687C = attrIt->GetAs_RwInt32();
            break;
#endif
        }
        ++attrIt;
    }
}

// match: ??_ELevelInfo@@WBI@AEPAXI@Z @ 0x000C5D60
// sp-match: ??_ELevelInfo@@WBI@AEPAXI@Z @ 0x00096800
