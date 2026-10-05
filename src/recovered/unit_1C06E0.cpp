// cNetSoldierTrigger: split from unit_1BEBB0.cpp at 0x1C06E0, where the image ends that object
// (its deferred functions come before the next out-of-line one; PLAN M7).

#include <math.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "game/netsoldier.h"
#include "types/animbank.h"
#include "types/cNetSoldierTrigger.h"
#include "rws/cclassfactory.h"
#include "game/netmsg.h"
#include "game/functions.h"
#include "types/type_3D32F8.h"
#include "types/type_4AE70.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/flags.h"
#include "game/bombsites.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "types/type_DC400.h"
#include "types/alfaobject.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E32B4
extern const RwReal flt_3E32B4 = 0.01f;
// 0x003E32B8
extern const RwReal flt_3E32B8 = 0.01f;

// match: ?flt_3E32B4@@3MB @ 0x003E32B4
// match: ?flt_3E32B8@@3MB @ 0x003E32B8
// 0x003E32BC
extern const RwReal flt_3E32BC = 16.666666f;

// match: ?flt_3E32BC@@3MB @ 0x003E32BC


// match: __ehhandler$?MakeNew@cNetSoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1>8 @ 0x0041F214
// match: __ehhandler$?MakeNew@cNetSoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z>1 @ 0x0041F21C
// (Compiler-written.)
// match: ??_GcNetSoldierTrigger@@UAEPAXI@Z @ 0x001C07A0
// match: ??1cNetSoldierTrigger@@UAE@XZ @ 0x001C07C0
// The CEventHandler part's deleting destructor thunk (sub ecx, 0x18).
// match: ??_EcNetSoldierTrigger@@WBI@AEPAXI@Z @ 0x001C0820
// match: ??_C@_0BD@KBLFBFJI@cNetSoldierTrigger?$AA@ @ 0x003E32A0
// match: ??_7cNetSoldierTrigger@@6BCEventHandler@RWS@@@ @ 0x003E32C0
// match: ??_7cNetSoldierTrigger@@6BCAttributeHandler@RWS@@@ @ 0x003E32C8
// match: ?pcNetSoldierTriggerClassID@cNetSoldierTrigger@@2PBDB @ 0x0042CB98
// match: .CRT$XCU+0 @ 0x004271F8

// match: _$E2 @ 0x0030C300
// match: _$E3 @ 0x0030EAF0

// The soldier's vf_05C, defined in its class (types/type_3DAFC8.h) and
// emitted here; the network part's +0x02C reaches it through the thunk.

RWS_IMPLEMENT_CLASSID(cNetSoldierTrigger);
RWS_REGISTERCLASS(cNetSoldierTrigger);
// match: ?MakeNew@cNetSoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x001C06E0
// match: __ehhandler$?MakeNew@cNetSoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z-0xF @ 0x00302F20
// match: __ehhandler$?MakeNew@cNetSoldierTrigger@@SAPAVCAttributeHandler@RWS@@ABVCAttributePacket@3@@Z @ 0x00302F2F
RWS_DEFINE_MAKENEW(cNetSoldierTrigger)

// match: ??0cNetSoldierTrigger@@QAE@ABVCAttributePacket@RWS@@@Z @ 0x001C0760
cNetSoldierTrigger::cNetSoldierTrigger(const RWS::CAttributePacket &attr) : SoldierTrigger(attr)
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_D8.unk_00)
    {
    }
    dword_4F8134 = this;
}
// match: ?vf_020@cNetSoldierTrigger@@UAEPAUtype_3D3548@@XZ @ 0x001C07E0
type_3D3548 *cNetSoldierTrigger::vf_020()
{
    RwInt32 var_4;

    var_4 = get_pool(2).m_pool.unk_18;
    if (var_4 > 0)
        return sub_1BEBB0((type_712B0 *)this);
    return 0;
}
// ??2type_4F7EB8_1F0@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_4F7EB8_1F0::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}
