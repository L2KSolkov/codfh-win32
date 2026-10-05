// The pick-up spawner (type_1AE520): split from unit_1B7B20.cpp at 0x1BD340, where the image ends
// that object (its deferred functions come before the next out-of-line one; PLAN M7).

#include "rw/ostypes.h"
#include "rw/bamatrix.h"
#include "rw/baframe.h"
#include "rw/bavector.h"
#include "game/functions.h"
#include "types/type_3D32F8.h"
#include "game/netmsg.h"
#include "game/netplayer.h"
#include "types/type_FC6F0.h"
#include "types/type_3DAFC8.h"
#include "types/type_4D1DB8.h"
#include "game/debugtext.h"
#include "game/worldmgr.h"
#include "types/type_4E5D30.h"
#include "rw/rpcollis.h"
#include "game/clumputil.h"
#include "rw/rphanim.h"
#include "game/data.h"
#include "game/gameloop.h"
#include "game/flags.h"
#include "game/bombsites.h"
#include "types/type_DC400.h"
#include "types/type_3DD948.h"
#include "types/soundbank.h"
#include "types/type_3D94B8.h"
#include "types/PickupTrigger.h"
#include "game/loc.h"
#include "game/mpgame.h"
#include "game/netscore.h"
#include <string.h>
#include <math.h>
#include "types/type_4C09B0.h"
#include "types/type_4C19C0.h"
#include "types/type_3DF8D8.h"
#include "game/textmanager.h"
#include "types/alfaobject.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E2BEC
extern const RwReal flt_3E2BEC = 0.01f;

// match: ?flt_3E2BEC@@3MB @ 0x003E2BEC


// match: __ehhandler$?sub_1BD340@@YAPAUtype_1AE520@@PAVPickupTrigger@@@Z>1>8 @ 0x0041F060
// match: __ehhandler$?sub_1BD340@@YAPAUtype_1AE520@@PAVPickupTrigger@@@Z>1 @ 0x0041F068
// match: __ehhandler$?sub_1BD450@@YAPAUtype_1AE520@@HHPAURwMatrixTag@@MHH@Z>1>8 @ 0x0041F084
// match: __ehhandler$?sub_1BD450@@YAPAUtype_1AE520@@HHPAURwMatrixTag@@MHH@Z>1 @ 0x0041F08C
// match: __ehhandler$??0type_1AE520@@QAE@PAVPickupTrigger@@@Z>1>8 @ 0x0041F0A8
// match: __ehhandler$??0type_1AE520@@QAE@PAVPickupTrigger@@@Z>1 @ 0x0041F0B8
// match: __ehhandler$??1type_1AE520@@UAE@XZ>1>8 @ 0x0041F0D4
// match: __ehhandler$??1type_1AE520@@UAE@XZ>1 @ 0x0041F0EC
// match: ??_Gtype_1AE520@@UAEPAXI@Z @ 0x001BD540
// match: ??_7type_1AE520@@6B@ @ 0x003E2BF0

// match: ?sub_1BD340@@YAPAUtype_1AE520@@PAVPickupTrigger@@@Z @ 0x001BD340
// match: __ehhandler$?sub_1BD340@@YAPAUtype_1AE520@@PAVPickupTrigger@@@Z-0x11 @ 0x00302DF0
// match: __ehhandler$?sub_1BD340@@YAPAUtype_1AE520@@PAVPickupTrigger@@@Z @ 0x00302E01
type_1AE520 *sub_1BD340(PickupTrigger *arg_0)
{
    type_1AE520 *var_10;

    var_10 = (type_1AE520 *)sub_D56D0(0x3E0, arg_0->unk_24_18, arg_0->vf_008());
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_1AE520(arg_0);
        if (var_10->unk_28 & 0x400000) // not an address: entity flag
        {
            sub_D5A60(var_10, 0);
            var_10 = 0;
        }
    }
    else
    {
        sub_19A750("WARNING: A spawn could not be created due to lack of entity memory. Trigger "
                   "location(%6.2f,%6.2f,%6.2f)",
                   arg_0->unk_90, arg_0->unk_94, arg_0->unk_98);
    }
    return var_10;
}
// match: ?sub_1BD450@@YAPAUtype_1AE520@@HHPAURwMatrixTag@@MHH@Z @ 0x001BD450
type_1AE520 *sub_1BD450(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10,
                        RwInt32 arg_14)
{
    type_1AE520 *var_10 = 0;

    var_10 = (type_1AE520 *)sub_D56D0(0x3E0, 0, 0x18);
    if (var_10 != 0)
    {
        var_10 = new (var_10) type_1AE520(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14);
    }
    return var_10;
}
// match: ??0type_1AE520@@QAE@HHPAURwMatrixTag@@MHH@Z @ 0x001BD500
type_1AE520::type_1AE520(RwInt32 arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwReal arg_C, RwInt32 arg_10,
                         RwInt32 arg_14)
    : type_3D94B8(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14)
{
}
// match: ??0type_1AE520@@QAE@PAVPickupTrigger@@@Z @ 0x001BD570
// match: __ehhandler$??0type_1AE520@@QAE@PAVPickupTrigger@@@Z-0x16 @ 0x00302E10
// match: __ehhandler$??0type_1AE520@@QAE@PAVPickupTrigger@@@Z @ 0x00302E26
type_1AE520::type_1AE520(PickupTrigger *arg_0) : type_3D94B8(arg_0)
{
}
// match: ??1type_1AE520@@UAE@XZ @ 0x001BD5F0
// match: __ehhandler$??1type_1AE520@@UAE@XZ-0x1E @ 0x00302E30
// match: __ehhandler$??1type_1AE520@@UAE@XZ @ 0x00302E4E
type_1AE520::~type_1AE520()
{
    dword_4FBB20.sub_1BE060(this);
}
// match: ?sub_1BD680@type_1AE520@@QAEXI@Z @ 0x001BD680
void type_1AE520::sub_1BD680(RwUInt32 arg_0)
{
    // A compiled-out check (docs/toolchain.md): the registers after it are
    // one load on.
    if (!unk_3D0)
    {
    }
    unk_3D0 = arg_0;
}
