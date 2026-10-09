// Split from unit_17D590.cpp at 0x17E290, where the image starts another object (the pulse
// zones' list): its .rdata begins at 0x3DE0C4 with its own 16.666666, the unreferenced
// constant every game object starts its constants with (PLAN M7).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_3D3548.h"
#include "types/type_10F710.h"
#include "types/type_44350.h"
#include "types/type_17DB90.h"
#include "types/PulseZoneTrigger.h"
#include "types/type_F2880.h"
#include <string.h>
#include "game/netmsg.h"
#include "game/gameloop.h"
#include "types/type_3D32F8.h"
#include "rw/bavector.h"
#include "types/type_8A980.h"
#include "types/type_4AE70.h"
#include "types/type_92430.h"
#include "game/surfaceparticles.h"
#include "types/alfasched.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DE0C4
extern const RwReal flt_3DE0C4 = 16.666666f;

// match: ?flt_3DE0C4@@3MB @ 0x003DE0C4


// match: __ehhandler$?sub_17E3A0@@YA?AUtype_17E3A0@@PAVTrigger@@@Z>1>8 @ 0x0041E540
// match: __ehhandler$?sub_17E3A0@@YA?AUtype_17E3A0@@PAVTrigger@@@Z>1 @ 0x0041E548
// match: ??_C@_0BE@EJHMDLGH@m_freePulseZoneList?$AA@ @ 0x003DE0C8

// match: ?sub_17E290@@YAXXZ @ 0x0017E290
// sp-match: ?sub_17E290@@YAXXZ @ 0x00116A30
// Sets the zones up: their pool, list and handles.
void sub_17E290()
{
    dword_4E7378.sub_16C2C0(0x20, 0xD0, "m_freePulseZoneList", 0x10, false);
    dword_4E7374 = 0;
    memset(dword_4E7268, 0, 0x108);
    dword_4E7370 = 0;
}
// match: ?sub_17E2E0@@YAXXZ @ 0x0017E2E0
// sp-match: ?sub_17E2E0@@YAXXZ @ 0x00116C50
// Drops every zone and handle.
void sub_17E2E0()
{
    sub_17E510();
    memset(dword_4E7268, 0, 0x108);
    dword_4E7370 = 0;
}
// match: ?sub_17E310@@YAXXZ @ 0x0017E310
// sp-match: ?sub_17E310@@YAXXZ @ 0x00116C70
// Drops every zone and shuts the pool down.
void sub_17E310()
{
    sub_17E510();
    dword_4E7378.sub_16C4D0(true);
}
// match: ?sub_17E330@@YAXM@Z @ 0x0017E330
// sp-match: ?sub_17E330@@YAXM@Z @ 0x00116C90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Runs every zone for arg_0 frames, dropping those that are done.
void sub_17E330(RwReal arg_0)
{
    RwInt32 var_10;
    type_17DB90 *var_C;
    RwInt32 bp_8;
    type_17DB90 *bp_4;

    var_C = dword_4E7374;
    while (var_C)
    {
        bp_4 = var_C->unk_50;
        bp_8 = 1;
        var_10 = var_C->unk_54;
        if (var_10)
            bp_8 = var_C->vf_010(arg_0);
        if (!bp_8)
            sub_17E470(var_C);
        var_C = bp_4;
    }
}
// match: __ehhandler$?sub_17E3A0@@YA?AUtype_17E3A0@@PAVTrigger@@@Z-0x11 @ 0x00302200
// match: __ehhandler$?sub_17E3A0@@YA?AUtype_17E3A0@@PAVTrigger@@@Z @ 0x00302211
// match: ?sub_17E3A0@@YA?AUtype_17E3A0@@PAVTrigger@@@Z @ 0x0017E3A0
// sp-match: ?sub_17E3A0@@YA?AUtype_17E3A0@@PAVTrigger@@@Z @ 0x00116B30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_17E3A0 sub_17E3A0(Trigger *arg_0)
{
    RwInt32 var_18;
    type_17DB90 *var_14;
    void *lv_10;

    lv_10 = dword_4E7378.sub_16C5A0(0);
    var_14 = new (lv_10) type_17DB90;
    var_14->vf_004((PulseZoneTrigger *)arg_0);
    var_14->set_unk_50(dword_4E7374);
    dword_4E7374 = var_14;
    var_18 = sub_17E560(var_14);
    var_14->sub_17D920(var_18);
    return var_14->get_unk_B0();
}
// match: ?sub_17E470@@YAXPAUtype_17DB90@@@Z @ 0x0017E470
// sp-match: ?sub_17E470@@YAXPAUtype_17DB90@@@Z @ 0x00116BC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_17E470(type_17DB90 *arg_0)
{
    type_17DB90 *var_14;
    type_17DB90 *lv_10;
    type_17DB90 *var_C;
    type_17E3A0 bp_8;
    type_17DB90 *bp_4;

    for (bp_4 = dword_4E7374; bp_4; bp_4 = bp_4->unk_50)
    {
        var_C = bp_4->unk_50;
        if (var_C == arg_0)
            break;
    }
    if (bp_4)
    {
        lv_10 = arg_0->unk_50;
        bp_4->unk_50 = lv_10;
    }
    else
    {
        var_14 = arg_0->unk_50;
        dword_4E7374 = var_14;
    }
    bp_8.unk_00 = arg_0->unk_B0;
    sub_17E620(bp_8);
    arg_0->vf_008();
    dword_4E7378.sub_16C710(arg_0);
}
// match: ?sub_17E510@@YAXXZ @ 0x0017E510
// sp-match: ?sub_17E510@@YAXXZ @ 0x00116C20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_17E510()
{
    type_17DB90 *var_8;
    type_17DB90 *l4;

    l4 = dword_4E7374;
    var_8 = 0;
    while (l4)
    {
        var_8 = l4->unk_50;
        sub_17E470(l4);
        l4 = var_8;
    }
    dword_4E7374 = 0;
}
// match: ?sub_17E560@@YAHPAUtype_17DB90@@@Z @ 0x0017E560
// sp-match: ?sub_17E560@@YAHPAUtype_17DB90@@@Z @ 0x00116A70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_17E560(type_17DB90 *arg_0)
{
    RwInt32 var_C;
    type_17E3A0 bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    for (var_C = 1; var_C < 0x21; var_C++)
    {
        if (!dword_4E7268[var_C].unk_00.unk_00 && !dword_4E7268[var_C].unk_04)
        {
            if (!dword_4E7370)
                dword_4E7370 = 1;
            dword_4E7268[var_C].unk_00.unk_00_w = (RwUInt16)var_C;
            bp_8.unk_00_w = (RwUInt16)var_C;
            dword_4E7268[var_C].unk_00.unk_02_w = (RwUInt16)dword_4E7370;
            bp_8.unk_02_w = (RwUInt16)dword_4E7370;
            dword_4E7268[bp_8.unk_00_w].unk_04 = arg_0;
            bp_4 = 1;
            dword_4E7370++;
            break;
        }
    }
    return bp_8.unk_00;
}
// match: ?sub_17E620@@YAXUtype_17E3A0@@@Z @ 0x0017E620
// sp-match: ?sub_17E620@@YAXUtype_17E3A0@@@Z @ 0x00116AF0
void sub_17E620(type_17E3A0 arg_0)
{
    dword_4E7268[arg_0.unk_00_w].unk_00.unk_00 = 0;
    dword_4E7268[arg_0.unk_00_w].unk_04 = 0;
}
// match: ?sub_17E650@@YAPAUtype_17DB90@@Utype_17E3A0@@@Z @ 0x0017E650
// sp-match: ?sub_17E650@@YAPAUtype_17DB90@@Utype_17E3A0@@@Z @ 0x00116B10
type_17DB90 *sub_17E650(type_17E3A0 arg_0)
{
    if (dword_4E7268[arg_0.unk_00_w].unk_00.unk_00 == arg_0.unk_00)
        return dword_4E7268[arg_0.unk_00_w].unk_04;
    return 0;
}
