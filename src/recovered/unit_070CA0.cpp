// type_3D2E7C, the AI object (types/type_3D2E7C.h): its constructor, its
// script's start and end, its tasks and its entity. The file's original name
// is not recovered (M1), so it is named for its start address.

#include "rw/ostypes.h"
#include "game/data.h"
#include "types/type_3D2E7C.h"
#include "types/type_3D3548.h"
#include "types/type_44350.h"
#include "types/AIData.h"
#include "types/alfaobject.h"
#include "types/scriptvm.h"

struct type_3D2E7C;
struct type_42E00_10;
struct type_67620;
void sub_6B5F0(const RwChar *arg_0, type_67620 *arg_4, type_42E00_10 *arg_8, type_3D2E7C *arg_C, RwInt32 *arg_10, RwInt32 arg_14, bool arg_18, bool arg_1C);
// sub_71770: a new object of the kind arg_0 from its pool (2 a state
// machine, 3 a task).
type_3D2C88 *sub_71770(RwInt32 arg_0);
// sub_D5A60: ends the entity arg_0 with the reason arg_4.
void sub_D5A60(type_3D3548 *arg_0, RwInt32 arg_4);

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_7type_3D2E7C@@6B@ @ 0x003D2E7C
// match: ??_C@_0L@KIAPHAEH@Initialize?$AA@ @ 0x003D2E80

// match: ??0type_3D2E7C@@QAE@XZ @ 0x00070CA0

type_3D2E7C::type_3D2E7C()
{
    unk_0C = 0;
    unk_08 = 0;
    unk_10 = 0;
    unk_24 = -1;
    unk_14 = 0;
    unk_04 = 0;
    unk_20 = 0;
    sub_71010(0);
    sub_71050(0);
}

// match: ?vf_000@type_3D2E7C@@UAEXH@Z @ 0x00070D20
void type_3D2E7C::vf_000(RwInt32 arg_0)
{
    unk_04 = 0;
    unk_24 = arg_0;
}

// match: ?sub_70D40@type_3D2E7C@@QAEXXZ @ 0x00070D40
void type_3D2E7C::sub_70D40()
{
    type_3D2DB8 *var_4;

    unk_24 = -1;
    if (unk_0C != 0) {
        sub_71D50((RwInt32 *)unk_0C);
        unk_0C = 0;
    }
    var_4 = (type_3D2DB8 *)sub_71340();
    if (var_4 != 0) {
        var_4->sub_70B70();
        unk_20 = 0;
    }
    sub_70DB0();
}

// match: ?sub_70DB0@type_3D2E7C@@QAEXXZ @ 0x00070DB0
void type_3D2E7C::sub_70DB0()
{
    type_3D2E20 *var_4;

    var_4 = (type_3D2E20 *)sub_67620(unk_1C);
    if (var_4 != 0) {
        var_4->sub_703C0();
        var_4->sub_70AF0();
        sub_71010(0);
    }
}

// match: ?sub_70DF0@type_3D2E7C@@QAEXPAUtype_3D3548@@H@Z @ 0x00070DF0
void type_3D2E7C::sub_70DF0(type_3D3548 *arg_0, RwInt32 arg_4)
{
    unk_10 = arg_0;
    unk_14 = arg_4;
}

// match: ?sub_70E10@type_3D2E7C@@QAEXHH@Z @ 0x00070E10
void type_3D2E7C::sub_70E10(RwInt32 arg_0, RwInt32 arg_4)
{
    type_3D2DB8 *local_8;
    type_67620 *var_4;

    local_8 = (type_3D2DB8 *)sub_71340();
    if (local_8 != 0) {
        local_8->sub_70B70();
        unk_20 = 0;
    }
    if (unk_0C != 0)
        sub_71D50((RwInt32 *)unk_0C);
    unk_08 = (type_72990 *)sub_72900(arg_0);
    if (unk_08->unk_0E > 0)
        unk_0C = (RwInt32)sub_71CE0(unk_08->unk_0E * 4);
    local_8 = (type_3D2DB8 *)sub_71770(2);
    unk_20_h = local_8->get_unk_04_h();
    local_8->sub_6EC60(unk_08->unk_0C, unk_08->unk_08, 0, unk_08->unk_10 * 4, this, unk_08->unk_18,
                     arg_0, 1);
    var_4 = sub_67620(unk_1C);
    if (var_4 == 0 && arg_4)
        sub_6B5F0("Initialize", (type_67620 *)this, 0, 0, 0, 0, 1, 0);
}

// match: ?sub_70F40@type_3D2E7C@@QAEXHH@Z @ 0x00070F40
void type_3D2E7C::sub_70F40(RwInt32 arg_0, RwInt32 arg_4)
{
    type_67620 *varC;
    type_3D2E20 *local_8;
    type_3D2E20 *var_4;

    local_8 = (type_3D2E20 *)sub_67620(unk_1C);
    if (local_8 != 0) {
        local_8->sub_70B70();
        sub_71010(0);
        sub_71050(0);
    }
    var_4 = (type_3D2E20 *)sub_71770(3);
    var_4->sub_6FE00(arg_0);
    sub_71220((type_46120 *)var_4);
    var_4->sub_70590(0, 0, 0);
    varC = sub_71340();
    if (varC == 0 && arg_4)
        sub_6B5F0("Initialize", (type_67620 *)this, 0, 0, 0, 0, 1, 0);
}

// match: ?sub_70FF0@type_3D2E7C@@QAEXI@Z @ 0x00070FF0
void type_3D2E7C::sub_70FF0(RwUInt32 arg_0)
{
    unk_1C = arg_0;
}

// match: ?sub_71010@type_3D2E7C@@QAEXPAUtype_3D2E20@@@Z @ 0x00071010
void type_3D2E7C::sub_71010(type_3D2E20 *arg_0)
{
    if (arg_0 != 0)
        unk_1C_h = arg_0->get_unk_04_h();
    else
        unk_1C = 0;
}

// match: ?sub_71050@type_3D2E7C@@QAEXPAUtype_3D2E20@@@Z @ 0x00071050
void type_3D2E7C::sub_71050(type_3D2E20 *arg_0)
{
    if (arg_0 != 0)
        unk_18_h = arg_0->get_unk_04_h();
    else
        unk_18 = 0;
}

// match: ?sub_71090@type_3D2E7C@@QAEPAUtype_46120@@XZ @ 0x00071090
type_46120 *type_3D2E7C::sub_71090()
{
    return (type_46120 *)sub_67620(unk_18);
}

// match: ?sub_710B0@type_3D2E7C@@QAEXPAUtype_42E00@@PAUtype_6B960@@@Z @ 0x000710B0
void type_3D2E7C::sub_710B0(type_42E00 *arg_0, type_6B960 *arg_4)
{
    RwUInt32 local_8;
    type_3D2DB8 *var_4;

    var_4 = (type_3D2DB8 *)sub_71340();
    while (var_4 != 0) {
        var_4->sub_6EFD0(arg_0, arg_4);
        local_8 = var_4->unk_80.unk_00;
        var_4 = (type_3D2DB8 *)sub_67620(local_8);
    }
}

// match: ?sub_71100@type_3D2E7C@@QAEXH@Z @ 0x00071100
void type_3D2E7C::sub_71100(RwInt32 arg_0)
{
    AIData *varC;
    AIData *local_8;
    RwUInt32 var_4;

    switch (unk_14) {
    case 2:
        var_4 = unk_10->unk_2C;
        if (var_4 & 0x20) {
            local_8 = unk_10->vf_120();
            local_8->unk_51C = 0;
            unk_10->unk_28 |= 0x200;
            sub_D5A60(unk_10, arg_0);
        } else if (var_4 & 0x40080) {     // not an address: entity kind bits
            varC = unk_10->vf_120();
            if (varC != 0)
                varC->unk_51C = 0;
            unk_10->unk_28 |= 0x200;
            sub_D5A60(unk_10, arg_0);
        } else
            sub_D5A60(unk_10, arg_0);
        break;
    case 1:
        sub_71970((type_3D2C88 *)this);
        break;
    }
}

// match: ?sub_71220@type_3D2E7C@@QAEXPAUtype_46120@@@Z @ 0x00071220
void type_3D2E7C::sub_71220(type_46120 *arg_0)
{
    ((type_3D2E20 *)arg_0)->sub_708F0(this);
    sub_71010((type_3D2E20 *)arg_0);
    ((type_3D2E20 *)arg_0)->sub_70360();
}

// match: ?sub_71250@type_3D2E7C@@QAEPAUtype_71250@@XZ @ 0x00071250
type_71250 *type_3D2E7C::sub_71250()
{
    switch (unk_14) {
    case 1:
        return ((type_712B0 *)unk_10)->get_unk_AC();
    case 2:
        return unk_10->get_unk_34C()->get_unk_AC();
    }
    return 0;
}

// match: ?sub_712B0@type_3D2E7C@@QAEPAUtype_712B0@@XZ @ 0x000712B0
type_712B0 *type_3D2E7C::sub_712B0()
{
    switch (unk_14) {
    case 1:
        return (type_712B0 *)unk_10;
    case 2:
        return unk_10->get_unk_34C();
    }
    return 0;
}

// match: ?sub_71300@type_3D2E7C@@QAEPAUtype_3D3548@@XZ @ 0x00071300
type_3D3548 *type_3D2E7C::sub_71300()
{
    switch (unk_14) {
    case 1:
        return 0;
    case 2:
        return unk_10;
    }
    return 0;
}

// match: ?sub_71340@type_3D2E7C@@QAEPAUtype_67620@@XZ @ 0x00071340
type_67620 *type_3D2E7C::sub_71340()
{
    return sub_67620(unk_20);
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_3D2E7C@@SAXPAX0@Z (folded into the empty debug print at 0x19A750)
void type_3D2E7C::operator delete(void *arg_0, void *arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3D2E7C@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3D2E7C::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_1E7540@type_3D2E7C@@QAEXI@Z (folded into 0x1E7540)
void type_3D2E7C::sub_1E7540(RwUInt32 arg_0)
{
    unk_04 = arg_0;
}
