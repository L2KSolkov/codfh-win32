// PathNode: its MakeNew, constructor and destructor. Its original file name
// is not in the image, so it is named for its start address.

#include "rw/ostypes.h"
#include "rws/cattributehandler.h"
#include "rws/cclassfactory.h"
#include "types/PathNode.h"

RWS_IMPLEMENT_CLASSID(PathNode);
RWS_REGISTERCLASS(PathNode);
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_08FILHIOGO@PathNode?$AA@ @ 0x003D5EF4
// match: ??_7PathNode@@6B@ @ 0x003D5F00
// match: __ehhandler$?MakeNew@PathNode@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041BDD0
// match: __ehhandler$?MakeNew@PathNode@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041BDD8
// match: .CRT$XCU+0 @ 0x00426F2C
// match: ?pPathNodeClassID@PathNode@@2PBDB @ 0x00429170

// match: _$E2 @ 0x0030A840
// match: _$E3 @ 0x0030E090

// (The class factory's registration and its exit thunk.)

// match: ?MakeNew@PathNode@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000A8FC0
// match: __ehhandler$?MakeNew@PathNode@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00300050
// match: __ehhandler$?MakeNew@PathNode@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x0030005F
// sp-match: ?MakeNew@PathNode@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x000837A0
RWS_DEFINE_MAKENEW(PathNode)

// match: ??0PathNode@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x000A9040
// sp-match: ??0PathNode@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x00083760
PathNode::PathNode(const RWS::CAttributePacket &attr)
{
}

// match: ??_GPathNode@@UAEPAXI@Z @ 0x000A90A0
// sp-match: ??_GPathNode@@UAEPAXI@Z @ 0x00083790

// match: ??1PathNode@@UAE@XZ @ 0x000A90C0
// sp-match: ??1PathNode@@UAE@XZ @ 0x00083780
// (Defined in the class, in PathNode.h.)
