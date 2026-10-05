// alfatimer: the script timers (named from the image's string
// "alfatimer::m_freeList"). The file's original name is not recovered
// (M1), so it is named for its start address.

#include "rw/ostypes.h"
#include "game/functions.h"
#include "types/alfaobject.h"
#include "types/alfatimer.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x00449B40
RwReal dword_449B40;
// 0x00449B44
type_73360 *dword_449B44;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_16C2A0 dword_449B48;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BG@ENHBPNJE@alfatimer?3?3m_freeList?$AA@ @ 0x003D3268
// match: .CRT$XCU+0 @ 0x00426DE8

// match: _$E1 @ 0x00309BB0
// match: _$E2 @ 0x0030DE40
// match: ?sub_73360@@YAXXZ @ 0x00073360

void sub_73360()
{
    dword_449B40 = 0;
    dword_449B44 = 0;
    dword_449B48.sub_16C2C0(200, 0x18, "alfatimer::m_freeList", 4, 0);
}

// match: ?sub_733A0@@YAXXZ @ 0x000733A0
void sub_733A0()
{
    sub_73550();
}

// match: ?sub_733B0@@YAXXZ @ 0x000733B0
void sub_733B0()
{
    sub_73550();
    dword_449B48.sub_16C4D0(1);
    dword_449B44 = 0;
}

// match: ?sub_733D0@@YAHPAUtype_67620@@HHM@Z @ 0x000733D0
RwInt32 sub_733D0(type_67620 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C)
{
    type_73360 *var_4;

    var_4 = 0;
    sub_734E0(arg_0, arg_8);
    var_4 = (type_73360 *)dword_449B48.sub_16C5A0(0);
    if (arg_0 != 0)
        var_4->unk_00_h = arg_0->get_unk_04_h();
    else
        var_4->unk_00 = 0;
    var_4->unk_08 = arg_4;
    var_4->unk_0C = arg_0->vf_028();
    var_4->unk_04 = arg_8;
    var_4->unk_10 = arg_C + dword_449B40;
    var_4->unk_14 = 0;
    sub_73590(var_4);
    return (RwInt32)var_4;
}

// match: ?sub_73470@@YAXPAUtype_3D2C88@@@Z @ 0x00073470
void sub_73470(type_3D2C88 *arg_0)
{
    type_73360 *varC;
    type_73360 *var_4;
    type_73360 *local_8;

    varC = dword_449B44;
    var_4 = 0;
    local_8 = 0;
    while (varC != 0) {
        var_4 = varC->unk_14;
        if (varC->unk_00 == arg_0->get_unk_04())
            sub_73610(local_8, varC);
        else
            local_8 = varC;
        varC = var_4;
    }
}

// match: ?sub_734E0@@YAXPAUtype_67620@@H@Z @ 0x000734E0
void sub_734E0(type_67620 *arg_0, RwInt32 arg_4)
{
    type_73360 *varC;
    type_73360 *var_4;
    type_73360 *local_8;

    varC = dword_449B44;
    var_4 = 0;
    local_8 = 0;
    while (varC != 0) {
        var_4 = varC->unk_14;
        if (varC->unk_00 == arg_0->get_unk_04() && varC->unk_04 == arg_4)
            sub_73610(local_8, varC);
        else
            local_8 = varC;
        varC = var_4;
    }
}

// match: ?sub_73550@@YAXXZ @ 0x00073550
void sub_73550()
{
    type_73360 *local_8;
    type_73360 *var_4;

    local_8 = dword_449B44;
    var_4 = 0;
    while (local_8 != 0) {
        var_4 = local_8->unk_14;
        sub_73610(0, local_8);
        local_8 = var_4;
    }
}

// match: ?sub_73590@@YAXPAUtype_73360@@@Z @ 0x00073590
void sub_73590(type_73360 *arg_0)
{
    type_73360 *var_4;
    type_73360 *local_8;

    var_4 = 0;
    local_8 = dword_449B44;
    while (local_8 != 0) {
        if (local_8->unk_10 > arg_0->unk_10)
            break;
        var_4 = local_8;
        local_8 = local_8->unk_14;
    }
    if (var_4 != 0) {
        arg_0->unk_14 = var_4->unk_14;
        var_4->unk_14 = arg_0;
    } else {
        arg_0->unk_14 = dword_449B44;
        dword_449B44 = arg_0;
    }
}

// match: ?sub_73610@@YAXPAUtype_73360@@0@Z @ 0x00073610
void sub_73610(type_73360 *arg_0, type_73360 *arg_4)
{
    if (arg_0 != 0)
        arg_0->unk_14 = arg_4->unk_14;
    else
        dword_449B44 = arg_4->unk_14;
    arg_4->unk_14 = 0;
    dword_449B48.sub_16C710(arg_4);
}

// match: ?sub_73650@@YAXM@Z @ 0x00073650
// Runs the clock on by arg_0, posting the timers it passes.
void sub_73650(RwReal arg_0)
{
    type_67620 *var_4;
    RwInt32 local_8;

    dword_449B40 += arg_0;
    while (dword_449B44 != 0 && dword_449B44->unk_10 < dword_449B40) {
        var_4 = sub_67620(dword_449B44->unk_00);
        if (var_4 != 0 && var_4->vf_028() == dword_449B44->unk_0C) {
            local_8 = dword_449B44->unk_08;
            sub_6B680(dword_449B44->unk_04, (type_67620 *)(var_4->vf_024()), 0, 0, &local_8, 1, 1, 0);
        }
        sub_73610(0, dword_449B44);
    }
}
