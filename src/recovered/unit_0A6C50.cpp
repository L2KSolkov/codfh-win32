// XBOXPadMap: its MakeNew, constructor and destructor. Its original file name
// is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/XBOXPadMap.h"

RWS_IMPLEMENT_CLASSID(XBOXPadMap);
RWS_REGISTERCLASS(XBOXPadMap);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0L@MIDJDNIO@XBOXPadMap?$AA@ @ 0x003D5E98
// match: ??_7XBOXPadMap@@6B@ @ 0x003D5EA4
// match: __ehhandler$?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BD40
// match: __ehhandler$?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BD48
// match: .CRT$XCU+0 @ 0x00426F24
// match: ?pXBOXPadMapClassID@XBOXPadMap@@2PBDB @ 0x00429168

// match: _$E2 @ 0x0030A7E0
// match: _$E3 @ 0x0030E070

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A6C50
// match: __ehhandler$?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x002FFFD0
// match: __ehhandler$?MakeNew@XBOXPadMap@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x002FFFDF
RWS_DEFINE_MAKENEW(XBOXPadMap)

// match: ??0XBOXPadMap@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A6CD0
XBOXPadMap::XBOXPadMap(const RWS::CAttributePacket &attr)
{
    unk_18 = 0;
}

// match: ??_GXBOXPadMap@@UAEPAXI@Z @ 0x000A6D40

// match: ??1XBOXPadMap@@UAE@XZ @ 0x000A6D60
// (Defined in the class, in XBOXPadMap.h.)
