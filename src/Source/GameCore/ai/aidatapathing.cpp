// Source\GameCore\ai\aidatapathing.cpp: the AI's A* path planning (AIData's pathing
// members). The path is the image's own (sub_29940's debug calls pass it as __FILE__,
// with __LINE__ 873 to 919). The object runs from 0x28A60 to 0x31B90: its .rdata begins
// at 0x3CE014 with its own copy of the unreferenced 16.666666 every game object starts
// its constants with, and its literals (0x3CE028 to 0x3CE1EC) run unbroken by another
// object's start up to the next one's at 0x3CE200 (PLAN M7).

#include "game/clumpdata.h"
#include "types/type_3D32F8.h"
#include <xmmintrin.h>
#include <math.h>
#include <string.h>
#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "rw/rprandom.h"
#include "game/frand.h"
#include "game/data.h"
#include "game/functions.h"
#include "game/vecutil.h"
#include "game/astarpathfinder.h"
#include "game/pathnodes.h"
#include "types/AIData.h"
#include "types/type_10F710.h"
#include "types/type_169D0.h"
#include "types/type_3CE6D0.h"
#include "types/type_3CE278.h"
#include "types/type_3CE5E8.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DAFC8_1DDC.h"
#include "types/type_3DBC78.h"
#include "types/type_3D2E7C.h"
#include "types/type_3DC048.h"
#include "types/type_3DC9B0.h"
#include "types/type_2CE90_50.h"
#include "types/type_3CE1FC.h"
#include "types/type_3DF30.h"
#include "types/type_427408.h"
#include "types/type_92430.h"
#include "rws/csystemcommands.h"
#include "rws/maths.h"
#include "game/pooledconsts.h"
#include "types/type_154C0_1048.h"
#include "types/type_154C0_5BC.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE014
extern const RwReal flt_3CE014 = 16.666666f;
// 0x003CE018
extern const RwV3d axis = { 0.0f, 1.0f, 0.0f };
// 0x003CE024
extern const RwReal flt_3CE024 = 100.0f;

// match: ?flt_3CE014@@3MB @ 0x003CE014
// match: ?axis@@3URwV3d@@B @ 0x003CE018
// match: ?flt_3CE024@@3MB @ 0x003CE024

// match: sub_28A60 @ 0x00028A60
// match: ??_C@_0EP@HHIEBADD@WARNING?3?5An?5attempt?5to?5register?5@ @ 0x003CE028
RwInt32 AIData::sub_28A60(RwInt32 arg_0, type_3D3548 *arg_4, RwReal arg_8, RwInt32 arg_C)
{
    RwInt32 var_4 = 0;

    switch (arg_0) {
    case 0:
    case 4:
        return 0;
    case 2:
    case 3:
    case 5:
        if (arg_4 != 0) {
            unk_580.sub_D48D0(arg_4);
        } else {
            sub_19A750("WARNING: An attempt to register an A* search with a NULL pointer has occured!\n");
            return 0;
        }
        break;
    case 11:
        arg_0 = 6;
        unk_5B0 = unk_1418;
    }
    var_4 = sub_32F70(unk_568->vf_098()->sub_71340(), arg_0, arg_8, 0);
    return var_4;
}
// match: sub_28B50 @ 0x00028B50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_28B50(RwInt32 arg_0, RwReal arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    type_3D3548 *local_8;

    var_4 = -1;
    local_8 = unk_580.sub_D4910();
    if (local_8 != 0) {
        if (arg_0 == 5)
            var_4 = sub_293A0(local_8, 1500.0f, 1, 0, 0, 1, 7, 8, 1, 1, 0, arg_4, arg_8);
        else if (arg_0 == 3)
            var_4 = sub_293A0(local_8, 1500.0f, 2, 0, 0, 0, 1, 2, 1, 1, 0, arg_4, arg_8);
        else
            var_4 = sub_293A0(local_8, 1500.0f, 0, 0, 0, 0, 1, 2, 1, 1, 0, arg_4, arg_8);
    }
    if (var_4 == -1)
        sub_6B5F0("AStar_PathNotFound", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    return var_4;
}
// match: sub_28C60 @ 0x00028C60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_28C60(RwInt32 arg_0, RwReal arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    type_3D3548 *local_8;

    var_4 = -1;
    local_8 = unk_1374.sub_D4910();
    if (local_8 != 0) {
        if (arg_0 == 4)
            var_4 = sub_29410(local_8, 1000.0f, 1, 0, 0, 1, 7, 8, &unk_A24, 0, 0, 0, arg_4, arg_8);
        else if (arg_0 == 1)
            var_4 = sub_29410(local_8, 1000.0f, 2, 0, 0, 0, 1, 2, &unk_A24, 0, 0, 0, arg_4, arg_8);
        else
            var_4 = sub_29410(local_8, 1000.0f, 0, 0, 0, 0, 1, 2, &unk_A24, 0, 0, 0, arg_4, arg_8);
    } else {
        unk_A24.unk_64.unk_2C = 0;
        unk_A24.unk_50.sub_D48D0(0);
        var_4 = -1;
    }
    return var_4;
}
// match: sub_28D80 @ 0x00028D80
RwInt32 AIData::sub_28D80(RwInt32 arg_0, RwReal arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;

    var_4 = -1;
    switch (arg_0) {
    case 8:
        var_4 = sub_29870(1000.0f, 1, 0, 0, 1, 7, 8, &unk_5BC, 1, 1, 0, arg_4, arg_8);
        break;
    case 6:
    case 12:
        var_4 = sub_29870(1000.0f, 0, 0, 0, 0, 1, 2, &unk_5BC, 1, 1, 0, arg_4, arg_8);
        break;
    case 7:
        var_4 = sub_29870(1000.0f, 2, 0, 0, 0, 1, 2, &unk_5BC, 1, 1, 0, arg_4, arg_8);
        break;
    case 9:
        var_4 = sub_29870(1000.0f, 0, 0, 0, 0, 1, 2, &unk_734, 1, 0, 0, arg_4, arg_8);
        break;
    }
    if (var_4 == -1 && arg_0 != 9)
        sub_6B5F0("AStar_PathNotFound", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    return var_4;
}
// match: sub_28F00 @ 0x00028F00
void AIData::sub_28F00()
{
    if (unk_5C != 1 && unk_5C != 0x18)
        unk_70 = 1;
}
// match: sub_28F30 @ 0x00028F30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_28F30()
{
    RwInt32 slot_44;
    type_154C0_F80 l40;
    RwInt32 v38;
    RwInt32 v34;
    RwInt32 v30;
    RwV3d var_2C;
    RwReal v20;
    RwReal slot_1C;
    type_3D3548 *local_18;
    RwV3d *local_14;
    RwInt32 local_10;
    RwInt32 fp_C;
    type_F8350 *lv_8;
    RwV3d *var_4;

    local_10 = 1;
    local_18 = unk_1374.sub_D4910();
    if (local_18 == 0)
        return 0;
    var_4 = unk_568->sub_CD550();
    local_14 = local_18->sub_CD550();
    if (local_18 == unk_10C0.sub_D4910()) {
        var_2C.x = unk_10B4.x - var_4->x;
        var_2C.y = 0.0f;
        var_2C.z = unk_10B4.z - var_4->z;
        v20 = RwV3dDotProduct(&var_2C, &var_2C);
        var_2C.x = unk_10A8.x - local_14->x;
        var_2C.y = 0.0f;
        var_2C.z = unk_10A8.z - local_14->z;
        slot_1C = RwV3dDotProduct(&var_2C, &var_2C);
        if (v20 < 90000.0f && slot_1C < 90000.0f)
            local_10 = 0;
    }
    if (local_10 != 0) {
        unk_1114.unk_04 = *local_14;
        unk_1114.unk_10 = unk_568->vf_114();
        unk_1114.unk_00 = unk_568;
        unk_1114.unk_18 = sub_F7E80(9);
        unk_1114.unk_1C = 1;
        unk_1114.unk_20 = unk_10C4;
        unk_1114.unk_24 = 10;
        unk_1114.unk_54 = -1;
        unk_1114.unk_50 = 0;
        sub_F8970(&unk_1114, 0, 0);
        unk_10B4 = *var_4;
        unk_10C0.sub_D48D0(local_18);
        unk_1174 = -1;
        v30 = unk_1114.unk_4C > 5 ? 5 : unk_1114.unk_4C;
        for (v34 = 0; v34 < v30; v34++) {
            v38 = RpRandom() % (unk_1114.unk_4C - 1 - v34 + 1) + v34;
            l40 = unk_10C4[v34];
            unk_10C4[v34] = unk_10C4[v38];
            unk_10C4[v38] = l40;
        }
    }
    unk_1174++;
    if (unk_1174 >= unk_1114.unk_4C) {
        if (unk_1114.unk_50 != 0) {
            slot_44 = 1;
            if ((unk_49C & 0x2000) != 0 && sub_205E0(&unk_1114.unk_50->unk_10, 0.0f) == 0)
                slot_44 = 0;
            if (slot_44 != 0) {
                unk_5B0 = unk_1114.unk_50->unk_10;
                unk_1114.unk_50 = 0;
                unk_1114.unk_54 = -1;
                return 1;
            }
        }
        return 0;
    }
    lv_8 = sub_FA980(unk_10C4[unk_1174].unk_00);
    fp_C = 1;
    if ((unk_49C & 0x2000) != 0 && sub_205E0(&lv_8->unk_10, 0.0f) == 0)
        fp_C = 0;
    if (fp_C != 0) {
        unk_5B0 = lv_8->unk_10;
        return 1;
    }
    return 0;
}
// match: sub_29360 @ 0x00029360
void AIData::sub_29360()
{
    unk_A24.unk_64.unk_2C = 0;
}
// match: sub_29380 @ 0x00029380
RwInt32 AIData::sub_29380(RwInt32 arg_0)
{
    unk_5A4 = arg_0;
    return 1;
}
// match: sub_293A0 @ 0x000293A0
RwInt32 AIData::sub_293A0(type_3D3548 *arg_0, RwReal arg_4, RwInt32 arg_8, RwInt32 arg_C,
                          RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                          RwInt32 arg_20, RwInt32 arg_24, RwInt32 arg_28, RwReal arg_2C,
                          RwInt32 arg_30)
{
    RwInt32 var_4;

    unk_580.sub_D48D0(arg_0);
    var_4 = sub_29410(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18, arg_1C, &unk_5BC,
                      arg_20, arg_24, arg_28, arg_2C, arg_30);
    return var_4;
}
// match: sub_29410 @ 0x00029410
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_29410(type_3D3548 *arg_0, RwReal arg_4, RwInt32 arg_8, RwInt32 arg_C,
                          RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                          type_154C0_5BC *arg_20, RwInt32 arg_24, RwInt32 arg_28, RwInt32 arg_2C,
                          RwReal arg_30, RwInt32 arg_34)
{
    type_3D3548 *var_4;
    RwV3d *v8;
    RwInt32 stk_C;
    RwV3d *var_10;

    stk_C = -1;
    var_4 = unk_568;
    var_10 = var_4->sub_CD550();
    if (((arg_0->unk_2C >> 4) & 1) != 0 && arg_0->vf_00C()->vf_200() != 0)
        v8 = arg_0->vf_00C()->vf_200()->sub_CD550();
    else
        v8 = arg_0->sub_CD550();
    arg_20->unk_14 = *var_10;
    arg_20->unk_20 = *v8;
    arg_20->unk_2C = arg_4;
    arg_20->unk_54 = arg_8;
    arg_20->unk_58 = arg_C;
    arg_20->unk_60 = arg_10;
    arg_20->unk_5C = arg_14;
    stk_C = sub_29940(arg_20, arg_18, arg_1C, 1, arg_0, 0, 0, arg_24, arg_28, arg_2C, arg_30, arg_34);
    return stk_C;
}
// match: sub_29540 @ 0x00029540
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_29540(RwReal arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                          RwInt32 arg_14, RwInt32 arg_18, type_154C0_5BC *arg_1C, RwInt32 arg_20,
                          RwInt32 arg_24, RwInt32 arg_28, RwReal arg_2C, RwInt32 arg_30)
{
    type_3D3548 *var_4;
    RwV3d *v8;
    RwInt32 stk_C;
    RwV3d *var_10;

    stk_C = -1;
    var_4 = unk_568;
    var_10 = var_4->sub_CD550();
    v8 = &unk_5A8->unk_10;
    arg_1C->unk_14 = *var_10;
    arg_1C->unk_20 = *v8;
    arg_1C->unk_2C = arg_0;
    arg_1C->unk_54 = arg_4;
    arg_1C->unk_58 = arg_8;
    arg_1C->unk_60 = arg_C;
    arg_1C->unk_5C = arg_10;
    stk_C = sub_29940(arg_1C, arg_14, arg_18, 1, 0, unk_5A8, unk_5AC, arg_20, arg_24, arg_28, arg_2C, arg_30);
    return stk_C;
}
// match: sub_29630 @ 0x00029630
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_29630(type_F8350 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                          RwInt32 arg_10)
{
    RwInt32 l4;
    RwV3d *var_8;
    RwReal fp_C;
    type_154C0_5BC *local_10;
    RwReal stk_14;
    RwInt32 loc18;

    l4 = -1;
    var_8 = unk_568->sub_CD550();
    local_10 = &unk_DDC;
    local_10->unk_14 = *var_8;
    local_10->unk_20 = arg_0->unk_10;
    local_10->unk_2C = 5000.0f;
    local_10->unk_54 = 0;
    local_10->unk_58 = 0;
    local_10->unk_60 = arg_8;
    local_10->unk_5C = 0;
    fp_C = 100.0f;
    if (arg_0->unk_04 == 0x11 && unk_568->vf_008() != 0) {
        loc18 = unk_568->vf_008()->unk_3E0.sub_15F0A0();
        if (sub_6D0A0(loc18, 5, 2, &stk_14))
            fp_C = stk_14;
    }
    l4 = sub_29940(local_10, 1, 2, 2, 0, arg_0, arg_4, 0, 0, arg_C, fp_C, arg_10);
    return l4;
}
// match: sub_29780 @ 0x00029780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_29780(type_154C0_12F4 *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    type_3DBC78 *v8;
    type_14D180 *stk_C;
    RwV3d *var_10;
    type_154C0_5BC *lv_14;

    var_4 = -1;
    v8 = static_cast<type_3DBC78 *>(arg_0->unk_08.sub_D4910());
    if (v8 != 0) {
        stk_C = v8->sub_155340(arg_0);
        var_10 = unk_568->sub_CD550();
        lv_14 = &unk_117C;
        lv_14->unk_14 = *var_10;
        lv_14->unk_20 = stk_C->unk_14;
        lv_14->unk_2C = 5000.0f;
        lv_14->unk_54 = 0;
        lv_14->unk_58 = 0;
        lv_14->unk_60 = 5;
        lv_14->unk_5C = 0;
        var_4 = sub_29940(lv_14, 1, 2, 2, 0, 0, 0, 0, 0, arg_4, 100.0f, arg_8);
    }
    return var_4;
}
// match: sub_29870 @ 0x00029870
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_29870(RwReal arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10,
                          RwInt32 arg_14, RwInt32 arg_18, type_154C0_5BC *arg_1C, RwInt32 arg_20,
                          RwInt32 arg_24, RwInt32 arg_28, RwReal arg_2C, RwInt32 arg_30)
{
    type_3D3548 *var_4;
    RwV3d *v8;
    RwInt32 stk_C;
    RwV3d *var_10;

    stk_C = -1;
    var_4 = unk_568;
    var_10 = var_4->sub_CD550();
    v8 = &unk_5B0;
    arg_1C->unk_14 = *var_10;
    arg_1C->unk_20 = *v8;
    arg_1C->unk_2C = arg_0;
    arg_1C->unk_54 = arg_4;
    arg_1C->unk_58 = arg_8;
    arg_1C->unk_60 = arg_C;
    arg_1C->unk_5C = arg_10;
    stk_C = sub_29940(arg_1C, arg_14, arg_18, 1, 0, 0, 0, arg_20, arg_24, arg_28, arg_2C, arg_30);
    return stk_C;
}
extern const RwV3d stru_3CE268;

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@00000000 @ 0x003CD84C
// match: ??_C@_0CL@HHOIGLPH@A?$CK?5Path?5not?5found?5due?5to?5no?5star@ @ 0x003CE08C
// match: ??_C@_0CJ@MFKFIACJ@A?$CK?5Path?5not?5found?5due?5to?5no?5endi@ @ 0x003CE0B8
// match: ??_C@_0O@BIOPFPJO@A?$CK?5path?5found?$AA@ @ 0x003CE0E4
// match: ??_C@_0EH@BDCCFGJJ@A?$CK?5Path?5not?5found?5because?5last?5?8@ @ 0x003CE0F8
// match: ??_C@_0L@IIKCAEDO@A?$CK?5started?$AA@ @ 0x003CE140
// match: ??_C@_0CF@FIJPNINF@Source?2GameCore?2ai?2aidatapathing@ @ 0x003CE14C

// match: ?sub_29940@AIData@@QAEHPAUtype_154C0_5BC@@HHHPAUtype_3D3548@@PAUtype_F8350@@HHHHMH@Z @ 0x00029940

// Plans the path arg_0 (id arg_2C, a new one for 0) for the owner towards
// the entity arg_10: its start node the nearest of the kind arg_4 to its
// start, its end node arg_14 (or, for 0, the nearest of the kind arg_8 to
// its end), the search radius arg_28 (64 for none) and the A* options
// arg_C and arg_24; the result code (1 found, -1 not).
RwInt32 AIData::sub_29940(type_154C0_5BC *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C,
                          type_3D3548 *arg_10, type_F8350 *arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                          RwInt32 arg_20, RwInt32 arg_24, RwReal arg_28, RwInt32 arg_2C)
{
    RwInt32 var_4;

    var_4 = -1;
    dword_438DDC = 1;
    arg_0->unk_50.sub_D48D0(arg_10);
    arg_0->unk_32 = 0;
    if (arg_2C == 0)
        arg_2C = ++dword_438CA0;
    arg_0->unk_00 = arg_2C;
    if (arg_28 > 0.0f)
        arg_0->unk_34 = arg_28;
    else
        arg_0->unk_34 = 64.0f;
    arg_0->unk_64.unk_44 = arg_1C;
    arg_0->unk_64.unk_48 = arg_20;
    if (arg_0->unk_54 == 2)
        arg_0->unk_31 = 1;
    else
        arg_0->unk_31 = 0;
    type_154C0_1048 var_68;

    var_68.unk_04 = arg_0->unk_14;
    var_68.unk_10 = arg_0->unk_2C;
    var_68.unk_14 = arg_0->unk_30;
    var_68.unk_00 = unk_568;
    var_68.unk_18 = sub_F7E80(arg_4);
    var_68.unk_1C = 0;
    var_68.unk_28.x = arg_0->unk_20.x - arg_0->unk_14.x;
    var_68.unk_28.y = arg_0->unk_20.y - arg_0->unk_14.y;
    var_68.unk_28.z = arg_0->unk_20.z - arg_0->unk_14.z;
    sub_F8970(&var_68, 1, 0);
    arg_0->unk_64.unk_34 = (RwInt32)var_68.unk_34;
    arg_0->unk_64.unk_38 = var_68.unk_38;
    if (arg_0->unk_64.unk_34 == 0) {
        arg_0->unk_64.unk_34 = (RwInt32)var_68.unk_50;
        arg_0->unk_64.unk_38 = var_68.unk_54;
    }
    if (arg_0->unk_64.unk_34 != 0) {
        arg_0->unk_64.unk_3C = arg_14;
        arg_0->unk_64.unk_40 = arg_18;
        if (arg_14 == 0) {
            type_154C0_1048 var_C8;

            var_C8.unk_04 = arg_0->unk_20;
            var_C8.unk_10 = arg_0->unk_2C;
            var_C8.unk_14 = arg_0->unk_30;
            var_C8.unk_00 = arg_10;
            var_C8.unk_18 = sub_F7E80(arg_8);
            var_C8.unk_1C = 0;
            var_C8.unk_28.x = arg_0->unk_14.x - arg_0->unk_20.x;
            var_C8.unk_28.y = arg_0->unk_14.y - arg_0->unk_20.y;
            var_C8.unk_28.z = arg_0->unk_14.z - arg_0->unk_20.z;
            sub_F8970(&var_C8, 1, 0);
            arg_0->unk_64.unk_3C = var_C8.unk_34;
            arg_0->unk_64.unk_40 = var_C8.unk_38;
            if (arg_0->unk_64.unk_3C == 0) {
                arg_0->unk_64.unk_3C = var_C8.unk_50;
                arg_0->unk_64.unk_40 = var_C8.unk_54;
            }
        }
        if (arg_0->unk_64.unk_3C != 0) {
            ((type_D48D0 *)&arg_0->unk_64.unk_00)->sub_D48D0(unk_568);
            arg_0->unk_64.unk_30 = (RwInt32)unk_568;
            arg_0->unk_64.unk_04 = &arg_0->unk_14;
            arg_0->unk_64.unk_08 = &arg_0->unk_20;
            arg_0->unk_64.unk_0C = arg_0->unk_2C;
            arg_0->unk_64.unk_10 = sub_F6BB0(arg_0->unk_54);
            arg_0->unk_64.unk_14 = sub_F6BF0(arg_0->unk_58);
            arg_0->unk_64.unk_18 = sub_F6C10(arg_0->unk_5C);
            arg_0->unk_64.unk_1C = arg_0->unk_60;
            arg_0->unk_64.unk_20 = 100;
            arg_0->unk_64.unk_24 = arg_0->unk_B0;
            arg_0->unk_64.unk_28 = -1;
            arg_0->unk_64.unk_2C = 0;
            zero_v3d(&arg_0->unk_38);
            zero_v3d(&arg_0->unk_44);
#line 873 "Source\\GameCore\\ai\\aidatapathing.cpp"
            sub_19A750(unk_568, (RwInt32)arg_0, "A* started", __FILE__, __LINE__);
            var_4 = sub_F62F0(&arg_0->unk_64, arg_2C, arg_C, arg_24);
            if (var_4 == 1 && arg_0->unk_64.unk_2C == 1) {
                if (arg_0->unk_B0[0] != arg_0->unk_64.unk_40) {
                    arg_0->unk_64.unk_2C = 0;
#line 880 "Source\\GameCore\\ai\\aidatapathing.cpp"
                    sub_19A750(unk_568, (RwInt32)arg_0,
                               "A* Path not found because last 'found' in path is not the destination!", __FILE__,
                               __LINE__);
                    var_4 = -1;
                } else {
                    var_4 = 1;
#line 902 "Source\\GameCore\\ai\\aidatapathing.cpp"
                    sub_19A750(unk_568, (RwInt32)arg_0, "A* path found", __FILE__, __LINE__);
                }
            }
            if (var_4 == -1)
#line 908 "Source\\GameCore\\ai\\aidatapathing.cpp"
                sub_19A750(unk_568, (RwInt32)arg_0, "A* path found", __FILE__, __LINE__);
        } else
#line 913 "Source\\GameCore\\ai\\aidatapathing.cpp"
            sub_19A750(unk_568, (RwInt32)arg_0, "A* Path not found due to no ending node!", __FILE__, __LINE__);
    } else
#line 919 "Source\\GameCore\\ai\\aidatapathing.cpp"
        sub_19A750(unk_568, (RwInt32)arg_0, "A* Path not found due to no starting node!", __FILE__, __LINE__);
    return var_4;
}

#ifdef CODFH_WIN32
extern "C" void port_debug_print(const RwChar *arg_0, ...);
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_19A750@@YAXPAUtype_3D3548@@HPBD1H@Z (folded into 0x19A750)
void sub_19A750(struct type_3D3548 * arg_0, RwInt32 arg_4, RwChar const * arg_8, RwChar const * arg_C, RwInt32 arg_10)
{
#ifdef CODFH_WIN32
    // The A* debug log (the entity, a value, the message, where): the port prints it.
    port_debug_print("%s (entity %p, %d; %s:%d)", arg_8, arg_0, arg_4, arg_C, arg_10);
#endif
}

// match: __ehhandler$?sub_2E580@AIData@@QAEHPAUtype_3DAFC8_1DDC@@PAURwMatrixTag@@PAURwV3d@@2MMMPAM@Z>1>8 @ 0x0041AEE4
// match: __ehhandler$?sub_2E580@AIData@@QAEHPAUtype_3DAFC8_1DDC@@PAURwMatrixTag@@PAURwV3d@@2MMMPAM@Z>1 @ 0x0041AEEC
// match: __ehhandler$?sub_2F440@AIData@@QAEHPAUtype_3DAFC8_1DDC@@PAURwMatrixTag@@PAURwV3d@@2MMMPAM3@Z>1>8 @ 0x0041AF08
// match: __ehhandler$?sub_2F440@AIData@@QAEHPAUtype_3DAFC8_1DDC@@PAURwMatrixTag@@PAURwV3d@@2MMMPAM3@Z>1 @ 0x0041AF10
// match: __ehhandler$?sub_30B90@AIData@@QAEXPAURwMatrixTag@@PAUtype_3DAFC8_1DDC@@1@Z>1>8 @ 0x0041AF2C
// match: __ehhandler$?sub_30B90@AIData@@QAEXPAURwMatrixTag@@PAUtype_3DAFC8_1DDC@@1@Z>1 @ 0x0041AF34
// match: __ehhandler$?sub_31240@AIData@@QAEHPAUtype_154C0_5BC@@PAURwV3d@@HM@Z>1>8 @ 0x0041AF50
// match: __ehhandler$?sub_31240@AIData@@QAEHPAUtype_154C0_5BC@@PAURwV3d@@HM@Z>1 @ 0x0041AF58

// match: ??1type_3CE1FC@@UAE@XZ @ 0x00031960
// match: ??_Gtype_3CE1FC@@UAEPAXI@Z @ 0x00031AA0
// match: __real@3727c5ac @ 0x003CE174
// match: __real@bc23d70a @ 0x003CE178
// match: __real@42800000 @ 0x003CE180
// match: __real@428c0000 @ 0x003CE184
// match: __real@42652ee0 @ 0x003CE18C
// match: ??_C@_0BE@LIGAFGIM@AStar_PathUnBlocked?$AA@ @ 0x003CE190
// match: ??_C@_0BC@BHNDDENE@AStar_PathBlocked?$AA@ @ 0x003CE1A4
// match: ??_C@_0O@LHJLOOHI@AIAction_Turn?$AA@ @ 0x003CE1B8
// match: __real@42b40000 @ 0x003CE1C8
// match: ??_C@_0CA@KPNNGAHE@SplinePath_ArrivedATDestination?$AA@ @ 0x003CE1CC
// match: ??_C@_0P@EJAKJMHA@BlockingEntity?$AA@ @ 0x003CE1EC

// match: sub_29ED0 @ 0x00029ED0
void AIData::sub_29ED0()
{
    RwV3d *var_4;

    var_4 = unk_568->sub_CD550();
    RwV3dSub(&unk_DC4, &unk_D70, var_4);
    unk_DC4.y = 0.0f;
    if (fabs(RwV3dDotProduct(&unk_DC4, &unk_DC4)) > 0.00001f)
        RwV3dNormalize(&unk_DC4, &unk_DC4);
}
// Whether a difference is under 150 either way: inline, with no address and
// so no database name; named for the test. Evidence: AIData::sub_29FC0 keeps
// each call's argument, fabs result and return value in temporaries of their
// own, in that order per call, which is what this shape expands to (an
// argument that is already fabs's, or a reference, orders them otherwise).
inline RwInt32 abs_lt_150(RwReal arg_0)
{
    RwReal r = fabs(arg_0);

    if (r < 150.0f)
        return 1;
    return 0;
}
// match: sub_29FC0 @ 0x00029FC0
void AIData::sub_29FC0(type_154C0_5BC *arg_0, type_154C0_5BC *arg_4, RwInt32 arg_8)
{
    type_F8350 *l40;
    RwReal var_3C;
    RwReal v38;
    RwV3d v34;
    RwV3d local_28;
    RwV3d *var_1C;
    RwInt32 var18;
    RwV3d *stk_14;
    RwV3d *l10;
    type_4C00E8 *local_C;
    RwInt32 lv_8;
    RwReal var_4;

    unk_DBC = 1;
    unk_DC0 = 1;
    *arg_0 = *arg_4;
    arg_0->unk_64.unk_24 = arg_0->unk_B0;
    arg_0->unk_64.unk_20 = 100;
    arg_0->unk_64.unk_04 = &arg_0->unk_14;
    arg_0->unk_64.unk_08 = &arg_0->unk_20;
    arg_0->unk_04 = arg_0->unk_64.unk_2C;
    arg_0->unk_32 = 0;
    arg_0->unk_33 = 0;
    l10 = unk_568->sub_CD550();
    local_C = &unk_4C00E8;
    lv_8 = -1;
    l40 = 0;
    if (arg_0->unk_64.unk_2C > 1) {
        if (arg_8 != 0 && ((unk_568->unk_28 >> 7) & 1) == 0) {
            RwInt32 var_44;

            for (var_44 = 0; var_44 < arg_0->unk_64.unk_2C; var_44++) {
                type_F8350 *var_4C;
                RwInt32 var_48;

                var_48 = arg_0->unk_B0[var_44];
                var_4C = local_C->unk_2C[var_48];
                if (abs_lt_150(var_4C->unk_10.y - l10->y)) {
                    type_4E5D30 *local_70;
                    RwInt32 var_6C;
                    RwInt32 local_68;
                    RwLine var_64;

                    local_68 = 0;
                    var_64.start = *l10;
                    var_64.start.y += 50.0f;
                    var_64.end = var_4C->unk_10;
                    var_64.end.y += 50.0f;
                    for (var_6C = 0; var_6C < 4; var_6C++) {
                        local_70 = &dword_4E5D30[var_6C];
                        if (local_70->get_unk_00() != 0 && local_70->get_unk_28() != 0
                                && local_70->get_unk_28() != 0
                                && sub_91F40(local_70->get_unk_28(), &var_64, 0, 0, 0x20000, 1) != 0) { // not an address: line-test flags
                            local_68 = 1;
                            break;
                        }
                    }
                    if (local_68 == 0) {
                        lv_8 = var_48;
                        l40 = var_4C;
                        arg_0->unk_04 = var_44 + 1;
                        break;
                    }
                }
            }
        } else {
            RwInt32 bp_84;
            RwInt32 var80;
            type_F8350 *local_7C;
            RwReal var_78;
            RwInt32 var_74;

            var80 = -1;
            var_74 = -1;
            var_78 = 1.0e37f;
            local_7C = 0;
            for (bp_84 = arg_0->unk_64.unk_2C - 1; bp_84 >= 0; bp_84--) {
                type_F8350 *var_8C;
                RwInt32 var_88;

                var_88 = arg_0->unk_B0[bp_84];
                var_8C = local_C->unk_2C[var_88];
                if (abs_lt_150(var_8C->unk_10.y - l10->y)) {
                    RwReal l9C;
                    RwV3d var_98;

                    RwV3dSub(&var_98, &var_8C->unk_10, l10);
                    l9C = RwV3dDotProduct(&var_98, &var_98);
                    if (l9C < var_78) {
                        var_78 = l9C;
                        var80 = bp_84;
                        var_74 = var_88;
                        local_7C = var_8C;
                    }
                }
            }
            if (local_7C != 0 && var80 != arg_0->unk_04 - 1) {
                RwInt32 local_BC;
                RwInt32 varB8;
                RwLine var_B4;

                varB8 = 0;
                var_B4.start = *l10;
                var_B4.start.y += unk_568->unk_48 / 2.0f;
                var_B4.end = local_7C->unk_10;
                var_B4.end.y += 50.0f;
                for (local_BC = 0; local_BC < 4; local_BC++) {
                    type_4E5D30 *var_C0;

                    var_C0 = &dword_4E5D30[local_BC];
                    if (var_C0->get_unk_00() != 0 && var_C0->get_unk_28() != 0
                            && var_C0->get_unk_28() != 0
                            && sub_91F40(var_C0->get_unk_28(), &var_B4, 0, 0, 0x20000, 1) != 0) { // not an address: line-test flags
                        varB8 = 1;
                        break;
                    }
                }
                if (varB8 == 0) {
                    lv_8 = var_74;
                    l40 = local_7C;
                    arg_0->unk_04 = var80 + 1;
                }
            }
        }
    }
    if (l40 == 0) {
        lv_8 = arg_0->unk_B0[arg_0->unk_04 - 1];
        l40 = local_C->unk_2C[lv_8];
    }
    sub_19B1F0(l40 != 0);
    if (l40 == 0)
        return;
    var_1C = &l40->unk_10;
    if (arg_0->unk_04 == 1) {
        stk_14 = &arg_0->unk_20;
    } else {
        type_F8350 *var_C4;

        lv_8 = arg_0->unk_B0[arg_0->unk_04 - 2];
        var_C4 = local_C->unk_2C[lv_8];
        stk_14 = &var_C4->unk_10;
    }
    local_28.x = var_1C->x - l10->x;
    local_28.y = 0.0f;
    local_28.z = var_1C->z - l10->z;
    var_3C = RwV3dDotProduct(&local_28, &local_28);
    if (var_3C > 0.0001f)
        RwV3dNormalize(&local_28, &local_28);
    v34.x = stk_14->x - var_1C->x;
    v34.y = 0.0f;
    v34.z = stk_14->z - var_1C->z;
    v38 = RwV3dDotProduct(&v34, &v34);
    if (v38 > 0.01f || v38 < -0.01f)
        RwV3dNormalize(&v34, &v34);
    else
        v34 = local_28;
    var_4 = RwV3dDotProduct(&local_28, &v34);
    var18 = 0;
    if (var_4 < 0.0f) {
        RwSphere vF0;
        RwReal var_E0;
        RwLine var_DC;

        var_DC.start = *var_1C;
        var_DC.end = *stk_14;
        vF0.center = *l10;
        vF0.radius = unk_568->unk_4C;
        var18 = RtLineSphereIntersectionTest(&var_DC, &vF0, &var_E0);
    }
    if (arg_0->unk_34 + 10.0f > var_3C)
        var18 = 1;
    if (var18 != 0) {
        arg_0->unk_08 = v34;
        if (arg_0->unk_04 == 1) {
            type_3D3548 *var_F4;

            arg_0->unk_32 = 1;
            var_F4 = arg_0->unk_50.sub_D4910();
            if (var_F4 != 0)
                arg_0->unk_38 = *var_F4->sub_CD550();
            else
                arg_0->unk_38 = arg_0->unk_20;
        } else {
            arg_0->unk_04 = arg_0->unk_04 - 1;
            arg_0->unk_38 = *stk_14;
        }
    } else {
        type_2CE90_50 v140;
        RwInt32 slot_144;
        RwLine var_110;
        RwInt32 var_F8;

        v140.unk_00 = 0;
        v140.unk_04 = unk_568;
        v140.unk_08 = arg_0->unk_50.sub_D4910();
        v140.unk_0C = 0;
        v140.unk_18 = 0;
        v140.unk_10 = 0;
        v140.unk_14 = 0.0f;
        v140.unk_1C = 1.0e37f;
        v140.unk_20 = 0;
        v140.unk_28 = 0;
        v140.unk_2C = 0;
        var_F8 = 1;
        var_110.start = *l10;
        var_110.start.y += unk_568->unk_48;
        var_110.end = *stk_14;
        for (slot_144 = 0; slot_144 < 4 && v140.unk_00 == 0; slot_144++) {
            type_4E5D30 *var_148;

            var_148 = &dword_4E5D30[slot_144];
            if (var_148->get_unk_00() != 0 && var_148->get_unk_28() != 0
                    && sub_91F40(var_148->get_unk_28(), &var_110, 0, 0x20000, 0x10000, 1) != 0) // not an address: line-test flags
                v140.unk_00 = 1;
        }
        if (v140.unk_00 != 0) {
            arg_0->unk_08 = local_28;
            arg_0->unk_38 = *var_1C;
        } else {
            arg_0->unk_08 = v34;
            arg_0->unk_38 = *stk_14;
            if (arg_0->unk_04 == 1)
                arg_0->unk_32 = 1;
            else
                arg_0->unk_04 = arg_0->unk_04 - 1;
        }
    }
    unk_D70 = *l10;
    unk_D7C = *l10;
    arg_0->unk_44 = *l10;
    RwV3dSub(&unk_D8C, &arg_0->unk_38, l10);
    RwV3dNormalize(&unk_D8C, &unk_D8C);
    sub_2AE00(l10, &arg_0->unk_38, arg_0);
    sub_29ED0();
    unk_598 = 0;
    unk_59C = 0;
    sub_309E0(0);
    if (((unk_49C >> 2) & 1) != 0 || ((unk_49C >> 25) & 1) != 0)
        sub_2CE90(1, 260.0f, 300.0f);
}
// match: sub_2AC00 @ 0x0002AC00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_2AC00(type_154C0_5BC *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C,
                          RwInt32 arg_10)
{
    RwReal var_4;
    RwV3d v10;
    RwReal local_14;
    RwReal var18;
    RwReal var_1C;
    RwReal l20;
    RwV3d bp_2C;

    bp_2C.x = arg_8->x - arg_4->x;
    bp_2C.y = arg_8->y - arg_4->y;
    bp_2C.z = arg_8->z - arg_4->z;
    if (bp_2C.y > 0.0f) {
        var18 = arg_8->y + 150.0f;
        local_14 = arg_8->y - 70.0f;
        if (arg_4->y < local_14 || arg_4->y > var18)
            return 0;
    } else {
        var18 = arg_4->y + 150.0f;
        local_14 = arg_4->y - 70.0f;
        if (arg_8->y < local_14 || arg_8->y > var18)
            return 0;
    }
    var_1C = RwV3dLength(&bp_2C);
    if (var_1C <= 64.0f)
        return 1;
    if (fabs(RwV3dDotProduct(&bp_2C, &bp_2C)) > 0.0001f)
        RwV3dNormalize(&bp_2C, &bp_2C);
    v10 = *arg_C;
    v10.y = 0.0f;
    l20 = RwV3dDotProduct(&v10, &v10);
    if (l20 > 0.01f || l20 < -0.01f) {
        if (arg_10 != 0)
            RwV3dNormalize(&v10, &v10);
        var_4 = RwV3dDotProduct(&v10, &bp_2C);
        if (var_4 < 0.0f && var_1C < 200.0f)
            return 1;
    }
    return 0;
}
extern const RwReal flt_3CE024;
// match: ?sub_2AE00@AIData@@QAEXPAURwV3d@@0PAUtype_154C0_5BC@@@Z @ 0x0002AE00
void AIData::sub_2AE00(RwV3d *arg_0, RwV3d *arg_4, type_154C0_5BC *arg_8)
{
    RwReal lv_8 = 0.0f;
    RwReal lv_C = 0.0f;
    RwV3d lv_18;
    RwReal lv_1C;
    RwV3d lv_28;
    RwReal lv_2C;
    RwReal lv_34;
    RwReal lv_38;
    RwReal lv_3C;
    RwV3d lv_48;

    RwV3dSub(&lv_18, arg_4, &unk_D70);
    lv_1C = RwV3dDotProduct(&lv_18, &lv_18);
    if (lv_1C != 0.0f)
        RwV3dNormalize(&lv_18, &lv_18);
    RwV3dSub(&lv_28, &unk_D70, arg_0);
    lv_2C = RwV3dDotProduct(&lv_28, &lv_28);
    if (fabs(lv_2C) > 0.001f)
        RwV3dNormalize(&lv_28, &lv_28);
    lv_34 = RwV3dDotProduct(&unk_D8C, &lv_28);
    lv_3C = ((lv_38 = RwV3dDotProduct(&lv_18, &lv_28)) * lv_38 + 1.0f) * 0.5f;
    lv_C = (lv_8 = lv_3C * unk_D88) * lv_8;
    if (lv_2C < lv_C || lv_34 <= 0.0f)
    {
        if (lv_2C > lv_C && lv_34 < 0.0f)
        {
            RwV3d lv_54;

            lv_48 = *arg_0;
            RwV3dSub(&lv_54, arg_4, &lv_48);
            RwV3dNormalize(&lv_54, &lv_54);
            RwV3dScale(&lv_54, &lv_54, lv_8);
            RwV3dAdd(&lv_48, &lv_54, &lv_48);
        }
        else
        {
            RwReal lv_B4;
            RwV3d lv_C0;

            do
            {
                __m128 lv_70 = _mm_set_ss(lv_C - lv_2C);
                __m128 lv_90 = _mm_sqrt_ss(lv_70);
                _mm_store_ss(&lv_B4, lv_90);
            } while (0);
            RwV3dScale(&lv_C0, &lv_18, lv_B4);
            lv_48 = unk_D70;
            RwV3dAdd(&lv_48, &lv_48, &lv_C0);
        }
        unk_D7C = *arg_0;
        RwV3dSub(&lv_28, arg_4, &lv_48);
        lv_2C = RwV3dDotProduct(&lv_28, &lv_28);
        if (lv_2C < lv_C)
            unk_D70 = *arg_4;
        else
        {
            RwV3d lv_CC;

            RwV3dSub(&lv_CC, arg_4, &unk_D70);
            if (RwV3dDotProduct(&lv_28, &lv_CC) < 0.0f)
                unk_D70 = *arg_4;
            else
                unk_D70 = lv_48;
        }
    }
    else
        return;
    RwV3d lv_D8;
    RwV3d lv_EC;
    RwReal lv_F8;
    RwV3d lv_104;

    lv_D8.x = arg_8->unk_08.z;
    lv_D8.y = 0.0f;
    lv_D8.z = -arg_8->unk_08.x;
    if (fabs(RwV3dDotProduct(&lv_D8, &lv_D8)) > 0.0001f)
        RwV3dNormalize(&lv_D8, &lv_D8);
    RwV3dSub(&lv_EC, arg_4, &unk_D70);
    if (fabs(RwV3dDotProduct(&lv_EC, &lv_EC)) > 0.0001f)
        RwV3dNormalize(&lv_EC, &lv_EC);
    lv_F8 = RwV3dDotProduct(&lv_D8, &lv_EC);
    RwV3dScale(&lv_D8, &lv_D8, flt_3CE024 * lv_F8);
    RwV3dAdd(&unk_D70, &unk_D70, &lv_D8);
    RwV3dSub(&lv_104, arg_4, arg_0);
    if (RwV3dDotProduct(&lv_104, &lv_104) < unk_D88 * unk_D88)
        unk_D70 = *arg_4;
    else
    {
        RwV3dSub(&lv_EC, &unk_D70, arg_0);
        lv_EC.y = 0.0f;
        if (fabs(RwV3dDotProduct(&lv_EC, &lv_EC)) > 0.0001f)
            RwV3dNormalize(&lv_EC, &lv_EC);
        RwV3dScale(&lv_EC, &lv_EC, lv_8);
        RwV3dAdd(&unk_D70, &lv_EC, arg_0);
        unk_D70.y = arg_0->y;
    }
    RwV3dSub(&unk_D8C, &unk_D70, &unk_D7C);
    if (RwV3dDotProduct(&unk_D8C, &unk_D8C) != 0.0f)
        RwV3dNormalize(&unk_D8C, &unk_D8C);
    if ((unk_49C >> 24) & 1)
        unk_13A8 = unk_D70;
}
// Moves a path on to the point arg_4, keeping the old one in unk_44: inline,
// with no address and so no database name; named for the field it sets.
// Evidence: AIData::sub_2B740 copies unk_38 to unk_44 before storing a new
// unk_38, and holds a point that is a call's result in an argument temporary
// across that copy.
inline void set_unk_38(type_154C0_5BC *arg_0, RwV3d *arg_4)
{
    arg_0->unk_44 = arg_0->unk_38;
    arg_0->unk_38 = *arg_4;
}
// match: sub_2B740 @ 0x0002B740
RwInt32 AIData::sub_2B740(type_154C0_5BC *arg_0)
{
    RwReal local_78;
    RwReal local_74;
    RwReal local_70;
    RwReal var_6C;
    RwReal v68;
    RwReal bp_64;
    RwV3d v60;
    type_3D3548 *var54;
    RwInt32 l50;
    type_3D3548 *ebp_4C;
    RwReal l48;
    RwV3d var44;
    type_3D3548 *var_38;
    type_F8350 *l34;
    RwV3d *var30;
    type_F8350 *ebp_2C;
    type_4C00E8 *var_28;
    RwInt32 ebp_24;
    type_3D3548 *var_20;
    RwV3d l1C;
    RwReal lv_10;
    RwReal var_C;
    RwV3d *bp_8;
    RwInt32 bp_4;

    if (arg_0->unk_04 <= 0)
        return 1;
    bp_4 = 0;
    bp_8 = unk_568->sub_CD550();
    RwV3dSub(&l1C, &arg_0->unk_20, bp_8);
    lv_10 = RwV3dLength(&l1C);
    if (arg_0->unk_33 == 0 && lv_10 < arg_0->unk_34) {
        var_20 = arg_0->unk_50.sub_D4910();
        if (var_20 != 0)
            set_unk_38(arg_0, var_20->sub_CD550());
        else
            set_unk_38(arg_0, &arg_0->unk_20);
        sub_2AE00(bp_8, &arg_0->unk_38, arg_0);
        sub_17140(&arg_0->unk_38);
        arg_0->unk_32 = 1;
        arg_0->unk_04 = 0;
        return 1;
    }
    if (arg_0->unk_32 == 0) {
        var_28 = &unk_4C00E8;
        ebp_24 = arg_0->unk_B0[arg_0->unk_04 - 1];
        ebp_2C = var_28->unk_2C[ebp_24];
        set_unk_38(arg_0, &ebp_2C->unk_10);
        if (sub_2AC00(arg_0, &unk_D70, &arg_0->unk_38, &arg_0->unk_08, 0) != 0) {
            if (arg_0->unk_31 != 0
                    && (((RwUInt16)ebp_2C->unk_00 & 0x42) != 0 || ebp_2C->unk_04 == 7
                        || ebp_2C->unk_04 == 8)
                    && sub_26A80(ebp_2C, unk_1374.sub_D4910(), 0, 0) != 0) {
                if (sub_2AC00(arg_0, bp_8, &arg_0->unk_38, &arg_0->unk_08, 0) != 0) {
                    unk_F64 = ebp_2C;
                    bp_4 = -1;
                }
            } else {
                var30 = &ebp_2C->unk_10;
                arg_0->unk_04 = arg_0->unk_04 - 1;
                if (arg_0->unk_04 > 0) {
                    ebp_24 = arg_0->unk_B0[arg_0->unk_04 - 1];
                    l34 = var_28->unk_2C[ebp_24];
                    set_unk_38(arg_0, &l34->unk_10);
                    arg_0->unk_08.x = arg_0->unk_38.x - var30->x;
                    arg_0->unk_08.y = arg_0->unk_38.y - var30->y;
                    arg_0->unk_08.z = arg_0->unk_38.z - var30->z;
                    if (fabs(RwV3dDotProduct(&arg_0->unk_08, &arg_0->unk_08)) > 0.0001f)
                        RwV3dNormalize(&arg_0->unk_08, &arg_0->unk_08);
                    if (((ebp_2C->unk_00 >> 4) & 1) != 0)
                        unk_49C |= 0x800;
                } else {
                    arg_0->unk_32 = 1;
                    arg_0->unk_04 = 0;
                    var_38 = arg_0->unk_50.sub_D4910();
                    if (var_38 != 0)
                        set_unk_38(arg_0, var_38->sub_CD550());
                    else
                        set_unk_38(arg_0, &arg_0->unk_20);
                    RwV3dSub(&var44, &arg_0->unk_38, var30);
                    l48 = RwV3dDotProduct(&var44, &var44);
                    if (l48 < -0.01f || l48 > 0.01f)
                        arg_0->unk_08 = var44;
                    if (sub_2AC00(arg_0, bp_8, &arg_0->unk_38, &arg_0->unk_08, 1) != 0)
                        return 1;
                    arg_0->unk_04 = 1;
                }
            }
        }
        sub_2AE00(bp_8, &arg_0->unk_38, arg_0);
        sub_17140(&unk_D70);
    } else {
        l50 = 0;
        ebp_4C = arg_0->unk_50.sub_D4910();
        if (ebp_4C != 0) {
            set_unk_38(arg_0, ebp_4C->sub_CD550());
            arg_0->unk_08.x = arg_0->unk_38.x - bp_8->x;
            arg_0->unk_08.y = arg_0->unk_38.y - bp_8->y;
            arg_0->unk_08.z = arg_0->unk_38.z - bp_8->z;
            l50 = 1;
        } else {
            arg_0->unk_38 = arg_0->unk_20;
        }
        sub_2AE00(bp_8, &arg_0->unk_38, arg_0);
        sub_17140(&unk_D70);
        if (sub_2AC00(arg_0, bp_8, &arg_0->unk_38, &arg_0->unk_08, l50) != 0) {
            arg_0->unk_04 = 0;
            return 1;
        }
    }
    var_C = deltaTime;
    if (((unk_568->unk_2C >> 5) & 1) != 0 && ((unk_49C >> 15) & 1) != 0) {
        sub_2C220(var_C);
        var54 = unk_1374.sub_D4910();
        if (var54 != 0) {
            sub_17140(var54->vf_0CC());
            sub_19F90(var54, var_C);
        }
    } else if (unk_598 == 0 && unk_59C == 0) {
        sub_2E520(&unk_D70, var_C);
    }
    if (((unk_568->unk_28 >> 5) & 1) != 0 && ((unk_568->unk_28 >> 7) & 1) != 0 && var_C > 0.0f) {
        v68 = fabs(local_70 = (arg_0->unk_38.y + 50.0f) - (arg_0->unk_44.y + 50.0f));
        local_74 = fabs(bp_64 = arg_0->unk_38.y + 50.0f - bp_8->y);
        if (v68 != 0.0f) {
            local_78 = local_74 / v68;
            if (local_78 > 1.0f)
                local_78 = 1.0f;
            local_78 = 1.0f - local_78;
            if (local_78 < 0.0f)
                local_78 = 0.0f;
            var_6C = local_70 * local_78 + arg_0->unk_44.y;
        } else {
            var_6C = arg_0->unk_38.y;
        }
        v60.x = 0.0f;
        v60.y = 0.0f;
        v60.z = 0.0f;
        v60.y = var_6C - bp_8->y;
        RwFrameTranslate(unk_568->get_unk_340(), &v60, rwCOMBINEPOSTCONCAT);
    }
    return bp_4;
}
// The heading to the steering point unk_D70 in the owner's frame
// ("GetLocalYawAngleToPathPoint"): the flat offset, turned by the inverse
// of the frame's LTM, then its heading (sub_2C1E0).
// match: ?sub_2C040@AIData@@QAEMXZ @ 0x0002C040
RwReal AIData::sub_2C040()
{
    RwV3d lv_14;
    RwFrame *lv_24;
    RwMatrix lv_70;

    RwV3dSub(&lv_14, &unk_D70, unk_568->sub_CD550());
    lv_14.y = 0.0f;
    lv_24 = unk_568->get_unk_340();
    RwMatrixSetIdentity(&lv_70);
    RwMatrixInvert(&lv_70, RwFrameGetLTM(lv_24));
    RwMatrixUpdate(&lv_70);
    sub_141320(&lv_14, &lv_14, &lv_70);
    if (fabs(RwV3dDotProduct(&lv_14, &lv_14)) > 0.0001f)
        RwV3dNormalize(&lv_14, &lv_14);
    return (RwReal)(RwDouble)sub_2C1E0(&lv_14);
}
// match: sub_2C1E0 @ 0x0002C1E0
RwReal sub_2C1E0(RwV3d *arg_0)
{
    return atan2(arg_0->z, arg_0->x);
}
extern const RwV3d axis;
// match: sub_2C220 @ 0x0002C220
// Turns the owner's vf_1C8 object towards unk_D70 through sub_2F440 (flag
// 23; not while unk_59C is set, nor with flags 0 or 18 unless unk_598 is
// set) or sub_2E580, with the owner's unk_C0.y cleared meanwhile; when
// neither turned it, turns the facing unk_DC4 towards unk_D70 by at most
// 6 degrees a unit of arg_0, and stores the new heading in the owner's
// vf_008 object.
void AIData::sub_2C220(RwReal arg_0)
{
    type_3DAFC8 *var_8;
    RwFrame *var_10;
    RwMatrix *var_14;
    RwV3d var_20;
    RwMatrix var_70;
    RwInt32 var_74;
    RwReal var_78;
    RwV3d var_84;
    RwMatrix var_D0;
    type_3DAFC8_1DDC *var_D4;
    type_3DAFC8_1DDC var_440;
    RwReal var_444;
    RwReal var_454;
    RwReal var_458;
    RwReal var_45C;
    RwReal var_460;
    RwV3d var_46C;
    RwReal var_478;
    RwReal var_488;
    RwReal var_498;
    RwReal var_49C;
    RwReal var_4A4;
    RwReal var_4A8;
    RwReal var_4AC;
    RwV3d var_4B8;
    RwReal var_4C4;

    var_8 = unk_568->vf_008();
    var_10 = unk_568->get_unk_340();
    var_14 = RwFrameGetLTM(var_10);
    RwV3dSub(&var_20, &unk_D70, &var_14->pos);
    var_20.y = 0.0f;
    if (fabs(RwV3dDotProduct(&var_20, &var_20)) > 0.0001f)
        RwV3dNormalize(&var_20, &var_20);
    RwMatrixSetIdentity(&var_70);
    RwMatrixInvert(&var_70, var_14);
    RwMatrixUpdate(&var_70);
    var_74 = 1;
    var_78 = unk_568->unk_C0.y;
    var_84 = unk_DC4;
    if (fabs(RwV3dDotProduct(&var_84, &var_84)) > 0.0001f)
        RwV3dNormalize(&var_84, &var_84);
    sub_140CE0(&var_D0, &var_14->pos, &var_84);
    var_D4 = unk_568->vf_1C8();
    if (var_D4 != 0 && (unk_49C & 0x840001) != 0) { // not an address: flags 0, 18 and 23
        sub_30B90(&var_D0, &var_440, var_D4);
        var_444 = RwV3dDotProduct(&var_D0.right, &var_20);
        var_454 = atan2(var_20.z, var_20.x) * 57.295776f;
        var_454 = sub_13F9E0(var_454);
        unk_568->unk_C0.y = 0.0f;
        var_458 = 0.0f;
        if ((unk_49C & 0x800000) != 0 && (unk_598 != 0 || (unk_49C & 0x40001) == 0)) { // not an address: flags
            if (unk_59C == 0) {
                sub_2F440(&var_440, &var_D0, &unk_D70, &var_84, var_444, var_454, arg_0, &var_45C, &var_458);
                if (unk_598 != 0 || unk_59C != 0)
                    var_74 = 0;
            } else {
                var_74 = 0;
            }
        } else if (unk_59C == 0 && unk_598 == 0) {
            if (sub_2E580(&var_440, &var_D0, &unk_D70, &var_84, var_444, var_454, arg_0, &var_458) != 0
                    && unk_598 == 0 && unk_59C == 0) {
                var_74 = 0;
                var_460 = arg_0 * unk_568->unk_C0.y;
                RwMatrixRotate(&var_D0, &axis, var_460, rwCOMBINEPRECONCAT);
                sub_141320(&var_46C, &var_D0.at, &var_70);
                if (fabs(RwV3dDotProduct(&var_46C, &var_46C)) > 0.0001f)
                    RwV3dNormalize(&var_46C, &var_46C);
                var_478 = sub_2C1E0(&var_46C);
                var_8->unk_1DC0 = var_478;
                unk_DC4 = var_D0.at;
            }
        }
    }
    if (var_74 != 0) {
        var_488 = atan2(unk_DC4.z, unk_DC4.x) * 57.295776f;
        var_498 = atan2(var_20.z, var_20.x) * 57.295776f;
        var_49C = RWS::DegAngDiff(var_498, var_488) / arg_0;
        var_4A4 = fabs(var_49C);
        var_4A8 = 0.0f;
        if (var_4A4 > 6.0f) {
            if (var_49C < 0.0f)
                var_4A8 = -6.0f;
            else
                var_4A8 = 6.0f;
        } else {
            var_4A8 = var_49C;
        }
        var_4AC = var_4A8 * arg_0;
        RwMatrixRotate(&var_D0, &axis, var_4AC, rwCOMBINEPRECONCAT);
        sub_141320(&var_4B8, &var_D0.at, &var_70);
        if (fabs(RwV3dDotProduct(&var_4B8, &var_4B8)) > 0.0001f)
            RwV3dNormalize(&var_4B8, &var_4B8);
        var_4C4 = sub_2C1E0(&var_4B8);
        var_8->unk_1DC0 = var_4C4;
        unk_DC4 = var_D0.at;
    }
    unk_568->unk_C0.y = var_78;
}
// match: sub_2C9B0 @ 0x0002C9B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_2C9B0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10)
{
    type_154C0_5BC *local_54;
    RwReal local_50;
    RwV3d stk_4C;
    AIData *lv_40;
    RwInt32 local_3C;
    RwV3d *v38;
    RwV3d v34;
    RwV3d *local_28;
    RwReal local_24;
    RwReal local_20;
    RwInt32 var_1C;
    RwInt32 var18;
    AIData *stk_14;
    type_3D3548 *l10;
    AIData *local_C;
    type_3D3548 *lv_8;
    type_2CE90_50 *var_4;

    if (!RWS::RpAtomicCollisionProperties::GetIsSolid(*arg_8))
        return arg_8;
    if ((sub_FB9C0(arg_8) & 8) != 0)
        return arg_8;
    var_4 = (type_2CE90_50 *)arg_10;
    lv_8 = sub_FB960(arg_8);
    if (lv_8 != 0) {
        if (var_4->unk_04 != 0 && var_4->unk_04 == lv_8)
            return arg_8;
        if (var_4->unk_08 != 0 && var_4->unk_08 == lv_8)
            return arg_8;
        if (((lv_8->unk_28 >> 2) & 1) == 0)
            return arg_8;
        if ((lv_8->unk_28 & 1) != 0)
            return arg_8;
        if (var_4->unk_2C != 0 && (lv_8->unk_2C & 0x10) == 0) {
            local_C = lv_8->vf_120();
            if (local_C != 0 && local_C->sub_238E0(0) == 0 && local_C->sub_23930() == 0) {
                if (var_4->unk_08 != 0) {
                    if (local_C->sub_21120(var_4->unk_08) == 0)
                        return arg_8;
                } else if (var_4->unk_04 != 0) {
                    stk_14 = var_4->unk_04->vf_120();
                    l10 = stk_14->unk_13E8.sub_D4910();
                    if (l10 != 0 && local_C->sub_21120(l10) == 0)
                        return arg_8;
                }
            } else {
                return arg_8;
            }
        }
        if ((lv_8->unk_2C & 0x20030) != 0) { // not an address: entity kind bits
            var18 = 1;
            if (lv_8->unk_58 == 2) {
                var18 = lv_8->vf_084(3, arg_0, &arg_C, 0);
            } else if (lv_8->unk_58 == 0 || (lv_8->unk_2C & 0x20020) != 0) { // not an address: entity kind bits
                var18 = lv_8->vf_080(1, arg_0, &arg_C, 1.5f);
            } else if (lv_8->unk_58 == 1) {
                var_1C = lv_8->vf_07C(1, arg_0, &arg_C, 0);
                if (var_1C != -1 && arg_C >= 0.0f)
                    var18 = 1;
                else
                    var18 = 0;
            }
            if (var18 != 0) {
                if (lv_8 == var_4->unk_10) {
                    local_20 = var_4->unk_14;
                } else {
                    local_28 = var_4->unk_04->sub_CD550();
                    v38 = lv_8->sub_CD550();
                    RwV3dSub(&v34, v38, local_28);
                    local_20 = RwV3dDotProduct(&v34, &v34);
                    var_4->unk_10 = lv_8;
                    var_4->unk_14 = local_20;
                    local_24 = RwV3dDotProduct(var_4->unk_24, &v34);
                    var_4->unk_20 = 0;
                    if (local_24 > 0.0f)
                        var_4->unk_20 = 1;
                }
                if (var_4->unk_20 != 0 && arg_C < var_4->unk_1C) {
                    lv_40 = lv_8->vf_120();
                    local_3C = 1;
                    if (lv_40 != 0 && lv_40->get_unk_DBC() != 0) {
                        if (lv_40->get_unk_DC0() != 0) {
                            local_54 = &lv_40->unk_8AC;
                            stk_4C = local_54->unk_08;
                        } else {
                            RwV3dSub(&stk_4C, &lv_40->unk_D70, lv_8->sub_CD550());
                        }
                        local_50 = fabs(RwV3dDotProduct(&stk_4C, &stk_4C));
                        if (local_50 > 0.0001f)
                            RwV3dNormalize(&stk_4C, &stk_4C);
                        if (RwV3dDotProduct(var_4->unk_24, &stk_4C) < -0.5f)
                            local_3C = 0;
                    }
                    if (local_3C != 0) {
                        var_4->unk_0C = lv_8;
                        var_4->unk_18 = arg_8;
                        var_4->unk_1C = arg_C;
                    }
                }
            }
        }
    }
    return arg_8;
}
// match: sub_2CE90 @ 0x0002CE90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_2CE90(RwInt32 arg_0, RwReal arg_4, RwReal arg_8)
{
    type_3D3548 *bp_4;
    RpIntersection loc20;
    type_2CE90_50 var50;
    RwV3d *loc54;
    RwV3d local_60;
    RwReal l64;
    RwV3d bp_70;
    RwInt32 local_74;
    type_4E5D30 *lv_78;

    if (unk_8AC.unk_04 > 0) {
        bp_4 = unk_8AC.unk_50.sub_D4910();
        loc54 = unk_568->sub_CD550();
        var50.unk_00 = 0;
        var50.unk_04 = unk_568;
        var50.unk_08 = bp_4;
        var50.unk_0C = 0;
        var50.unk_18 = 0;
        var50.unk_10 = 0;
        var50.unk_14 = 0.0f;
        var50.unk_1C = 1.0e37f;
        var50.unk_20 = 0;
        var50.unk_28 = 0;
        var50.unk_2C = (unk_49C >> 25) & 1;
        if (get_unk_DC0() != 0)
            local_60 = unk_8AC.unk_08;
        else
            RwV3dSub(&local_60, &unk_D70, loc54);
        l64 = fabs(RwV3dDotProduct(&local_60, &local_60));
        RwV3dNormalize(&local_60, &local_60);
        if (l64 > 0.0001f && local_60.x != 0.0f && local_60.z != 0.0f) {
            var50.unk_24 = &local_60;
            loc20.type = rpINTERSECTLINE;
            loc20.t.line.start = *loc54;
            if (unk_598 != 0 || unk_59C != 0)
                RwV3dScale(&bp_70, &local_60, arg_8);
            else
                RwV3dScale(&bp_70, &local_60, arg_4);
            bp_70.y = bp_70.y + unk_568->unk_48;
            RwV3dAdd(&loc20.t.line.end, &loc20.t.line.start, &bp_70);
            for (local_74 = 0; local_74 < 4; local_74++) {
                lv_78 = &dword_4E5D30[local_74];
                if (lv_78->get_unk_00() != 0 && lv_78->get_unk_28() != 0)
                    RpWorldForAllAtomicIntersections(lv_78->get_unk_28(), &loc20, sub_2C9B0, &var50);
            }
        }
        if (var50.unk_0C != 0) {
            if (((unk_49C >> 25) & 1) != 0) {
                if (unk_59C == 0 && arg_0 != 0) {
                    unk_59C = 1;
                    if (unk_598 == 0) {
                        sub_6B5F0("AStar_PathBlocked", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                        sub_309E0(var50.unk_0C);
                    }
                }
            } else if (unk_598 == 0 && arg_0 != 0) {
                sub_30850(1);
                sub_6B5F0("AStar_PathBlocked", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                sub_309E0(var50.unk_0C);
            }
            return 1;
        }
        if (((unk_49C >> 25) & 1) != 0) {
            if (unk_59C != 0 && arg_0 != 0) {
                unk_59C = 0;
                if (unk_598 == 0)
                    sub_6B5F0("AStar_PathUnBlocked", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            }
        } else if (unk_598 != 0 && arg_0 != 0) {
            sub_30850(0);
            sub_6B5F0("AStar_PathUnBlocked", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        }
        return 0;
    }
    return unk_598 != 0 || unk_59C != 0;
}
// match: sub_2D3A0 @ 0x0002D3A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_2D3A0()
{
    RwMatrix *local_28;
    RwReal local_24;
    RwV3d local_20;
    RwReal stk_14;
    RwReal l10;
    RwReal local_C;
    RwFrame *lv_8;
    type_3DAFC8_1DDC *var_4;

    if ((unk_49C & 0x8000) == 0 && unk_59C == 0
            && (unk_598 != 0 || (unk_49C & 0x40000) == 0)) { // not an address: flag 18
        if (unk_5A0 != 0) {
            sub_2C220(deltaTime);
        } else {
            var_4 = unk_568->vf_1C8();
            if (var_4 != 0) {
                lv_8 = unk_568->get_unk_340();
                local_28 = RwFrameGetLTM(lv_8);
                RwV3dSub(&local_20, &unk_D70, &local_28->pos);
                local_20.y = 0.0f;
                if (local_20.x != 0.0f && local_20.z != 0.0f)
                    RwV3dNormalize(&local_20, &local_20);
                else
                    local_20 = local_28->at;
                l10 = RwV3dDotProduct(&local_28->right, &local_20);
                stk_14 = atan2(local_20.z, local_20.x) * 57.295776f;
                stk_14 = sub_13F9E0(stk_14);
                sub_2F440(var_4, local_28, &unk_D70, &local_20, l10, stk_14, deltaTime, &local_24, &local_C);
            }
        }
    }
    return unk_598 != 0 || unk_59C != 0;
}
extern RwReal flt_438D34;
// match: sub_2D5C0 @ 0x0002D5C0
// Turns towards the flat direction arg_0 (in the parent frame's space
// when there is one and flt_438D34 is clear): logs "AIAction_Turn" beyond 30
// degrees, then, unless flag 10 is set, has sub_2E580 turn the owner's
// vf_1C8 object (flag 15 skips it) and sets the owner's turn rate, at most
// 6 degrees a unit of arg_8; 1 once within 0.05 degrees a unit.
RwInt32 AIData::sub_2D5C0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8)
{
    RwFrame *var_C;
    RwFrame *var_10;
    RwMatrix *var_14;
    RwV3d var_28;
    RwMatrix *var_2C;
    RwReal var_3C;
    RwV3d var_48;
    RwMatrix var_90;
    RwV3d var_9C;
    RwReal var_AC;
    RwReal var_B0;
    RwInt32 var_B4;
    RwReal var_C4;
    RwReal var_C8;
    RwReal var_D0;
    RwReal var_D4;
    RwInt32 var_DC;

    var_C = unk_568->get_unk_340();
    var_10 = RwFrameGetParent(var_C);
    var_14 = RwFrameGetMatrix(var_C);
    arg_0->y = 0.0f;
    if (fabs(RwV3dDotProduct(arg_0, arg_0)) > 0.0001f) {
        RwV3dNormalize(&var_28, arg_0);
    } else {
        var_28.x = 0.0f;
        var_28.y = 0.0f;
        var_28.z = 0.0f;
    }
    if (var_10 != 0 && flt_438D34 == 0.0f) {
        var_2C = RwFrameGetMatrix(var_10);
        var_3C = atan2(var_2C->right.x, var_2C->at.x) * 57.295776f - 90.0f;
        var_48.x = 0.0f;
        var_48.y = 1.0f;
        var_48.z = 0.0f;
        RwMatrixSetIdentity(&var_90);
        RwMatrixRotate(&var_90, &var_48, var_3C, rwCOMBINEPRECONCAT);
        var_9C = var_28;
        sub_141320(&var_28, &var_9C, &var_90);
    }
    var_AC = atan2(var_28.z, var_28.x) * 57.295776f;
    var_AC = sub_13F9E0(var_AC);
    var_B0 = RwV3dDotProduct(&var_28, &var_14->right);
    var_B4 = 0;
    var_C4 = atan2(var_14->right.x, var_14->at.x) * 57.295776f;
    var_C4 = sub_13F9E0(var_C4);
    var_D0 = fabs(var_C8 = RWS::DegAngDiff(var_AC, var_C4));
    if (var_D0 > 30.0f)
        sub_6B5F0("AIAction_Turn", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    var_D0 = fabs(var_D4 = var_C8 / arg_8);
    if (((unk_49C >> 10) & 1) != 0)
        return 0;
    var_DC = 0;
    if (((unk_49C >> 15) & 1) != 0)
        var_DC = 1;
    else
        var_DC = sub_2E580(unk_568->vf_1C8(), var_14, arg_4, &var_28, var_B0, var_AC, arg_8, 0) == 0;
    if (var_DC != 0 && arg_8 > 0.0f) {
        if (var_D0 > 6.0f) {
            if (var_B0 < 0.0f)
                unk_568->unk_E8 = -6.0f;
            else
                unk_568->unk_E8 = 6.0f;
        } else {
            if (var_D0 <= 0.05f)
                var_B4 = 1;
            unk_568->unk_E8 = var_D4;
            sub_19B650(unk_568->unk_E4);
        }
    }
    return var_B4;
}
// match: sub_2DAA0 @ 0x0002DAA0
// Follows the spline unk_D14: while the point unk_D70 is behind the owner
// or further than arg_4, advances along it (by at most the spline step,
// arg_4's share of the next hundredth), turning at its ends by its end mode,
// and moves unk_D70 on; logs the arrival and returns 1 once past the last
// point (0 before). Otherwise sets the velocity unk_DB0 from unk_D98 once.
RwInt32 AIData::sub_2DAA0(RwReal arg_0, RwReal arg_4, RwReal arg_8)
{
    RwInt32 var_8;
    RwV3d var_18;
    RwInt32 var_24;
    RwReal var_28;
    RwReal var_34;
    RpSpline *var_38;
    RwInt32 var_3C;
    RwReal var_40;
    RwReal var_44;
    RwReal var_48;
    RwV3d var_54;
    RwReal var_58;
    RwReal var_B4;
    RwReal var_B8;
    RwV3d var_CC;
    RwV3d var_D8;
    RwReal var_DC;

    var_8 = 0;
    RwV3dSub(&var_18, &unk_D70, unk_568->sub_CD550());
    var_18.y = 0.0f;
    var_24 = 0;
    var_28 = RwV3dDotProduct(&var_18, &var_18);
    if (fabs(RwV3dDotProduct(&var_18, &var_18)) > 0.0001f)
        RwV3dNormalize(&var_18, &var_18);
    var_34 = RwV3dDotProduct(&unk_D8C, &var_18);
    if (var_34 < 0.0f || arg_4 * arg_4 > var_28) {
        var_38 = unk_D14->unk_28;
        var_3C = RpSplineGetNumControlPoints(var_38);
        if (var_3C > 1) {
            var_40 = 1.0f / (var_3C - 1.0f);
            var_44 = unk_D18 + 0.01f;
            if (var_44 >= unk_D1C) {
                unk_D18 = unk_D1C;
            } else {
                var_48 = var_44 - unk_D18;
                unk_D14->sub_BA990(var_44, &var_54, &unk_D30);
                RwV3dSub(&var_54, &var_54, &unk_D70);
                var_58 = RwV3dDotProduct(&var_54, &var_54);
                do
                {
                    __m128 var_70 = _mm_set_ss(var_58);
                    __m128 var_A0 = _mm_sqrt_ss(var_70);
                    _mm_store_ss(&var_58, var_A0);
                } while (0);
                var_B4 = arg_4 / var_58 * var_48;
                if (var_40 * unk_D24 < var_B4)
                    var_B4 = var_40 * unk_D24;
                unk_D18 = var_B4 + unk_D18;
                var_B8 = var_B4 * 30.0f + unk_D18;
                if (var_B8 > 1.0f)
                    var_B8 = 1.0f;
                else if (var_B8 < 0.0f)
                    var_B8 = 0.0f;
                unk_D14->sub_BA990(var_B8, &unk_DA4, &unk_D30);
            }
        }
        if (unk_D18 >= unk_D1C || unk_D18 >= 0.0f && var_3C <= 1) {
            unk_D18 = unk_D1C;
            switch (unk_D14->unk_1C & 3) {
            case 2:
                unk_D24 = unk_D24 * -1.0f;
                break;
            case 1:
                unk_D18 = 0.0f;
                break;
            case 0:
                var_24 = 1;
                break;
            }
        } else if (unk_D18 < 0.0f || unk_D18 < 0.0f && var_3C <= 1) {
            unk_D18 = 0.0f;
            switch (unk_D14->unk_1C & 3) {
            case 2:
                unk_D24 = unk_D24 * -1.0f;
                break;
            case 1:
                unk_D18 = unk_D1C;
                break;
            case 0:
                var_24 = 1;
                break;
            }
        }
        if (var_3C <= 1) {
            if (((unk_49C >> 24) & 1) != 0)
                unk_13A8 = unk_D70;
            return var_24;
        }
        var_CC = unk_D70;
        unk_D14->sub_BA990(unk_D18, &unk_D70, &unk_D30);
        if (var_24 != 0) {
            RwV3dSub(&var_D8, unk_568->sub_CD550(), &unk_D70);
            var_DC = RwV3dDotProduct(&var_D8, &var_D8);
            if (var_34 < 0.0f || var_DC < 10000.0f)
                sub_6B5F0("SplinePath_ArrivedATDestination", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            var_8 = 1;
        } else {
            RwV3dSub(&unk_D8C, &unk_D70, &var_CC);
            unk_D8C.y = 0.0f;
            if (fabs(RwV3dDotProduct(&unk_D8C, &unk_D8C)) > 0.0001f)
                RwV3dNormalize(&unk_D8C, &unk_D8C);
            sub_2E2F0();
            RwV3d *var_E8 = &unk_DB0;

            var_E8->x = 0.0f;
            var_E8->y = 0.0f;
            var_E8->z = 0.0f;
        }
    } else if (unk_DB0.x == 0.0f && unk_DB0.y == 0.0f && unk_DB0.z == 0.0f
            && (var_34 < 0.0f || arg_8 * arg_8 > var_28)) {
        RwV3dScale(&unk_DB0, &unk_D98, arg_4);
    }
    if (((unk_49C >> 24) & 1) != 0)
        unk_13A8 = unk_D70;
    return var_8;
}
// match: sub_2E2F0 @ 0x0002E2F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_2E2F0()
{
    RwV3d var_1C;
    RwInt32 l10;
    RwReal local_C;
    RpSpline *lv_8;
    RwReal var_4;

    lv_8 = unk_D14->unk_28;
    l10 = RpSplineGetNumControlPoints(lv_8);
    if (l10 <= 1) {
        RwV3d *var_20 = &unk_D98;

        var_20->x = 0.0f;
        var_20->y = 0.0f;
        var_20->z = 0.0f;
        return;
    }
    var_4 = 1.0f / (l10 - 1.0f);
    local_C = var_4 * unk_D24 + unk_D18;
    if (local_C > unk_D1C) {
        local_C = unk_D1C;
        switch (unk_D14->unk_1C & 3) {
        case 2:
            local_C += unk_D24 * -1.0f * var_4;
            break;
        case 1:
            local_C = 0.0f;
            break;
        }
    } else if (local_C < 0.0f) {
        local_C = 0.0f;
        switch (unk_D14->unk_1C & 3) {
        case 2:
            local_C += unk_D24 * -1.0f * var_4;
            break;
        case 1:
            local_C = 1.0f;
            break;
        }
    }
    unk_D14->sub_BA990(local_C, &var_1C, &unk_D30);
    RwV3dSub(&unk_D98, &var_1C, &unk_D70);
    unk_D98.y = 0.0f;
    if (fabs(RwV3dDotProduct(&unk_D98, &unk_D98)) > 0.0001f)
        RwV3dNormalize(&unk_D98, &unk_D98);
}
// match: sub_2E520 @ 0x0002E520
void AIData::sub_2E520(RwV3d *arg_0, RwReal arg_4)
{
    RwV3d *var_4;
    RwV3d var_10;

    var_4 = unk_568->sub_CD550();
    var_10.x = arg_0->x - var_4->x;
    var_10.y = 0.0f;
    var_10.z = arg_0->z - var_4->z;
    sub_2D5C0(&var_10, arg_0, arg_4);
}
// match: sub_2E580 @ 0x0002E580
// match: __ehhandler$?sub_2E580@AIData@@QAEHPAUtype_3DAFC8_1DDC@@PAURwMatrixTag@@PAURwV3d@@2MMMPAM@Z-8 @ 0x002FF540
// match: __ehhandler$?sub_2E580@AIData@@QAEHPAUtype_3DAFC8_1DDC@@PAURwMatrixTag@@PAURwV3d@@2MMMPAM@Z @ 0x002FF548
RwInt32 AIData::sub_2E580(type_3DAFC8_1DDC *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwV3d *arg_C,
                          RwReal arg_10, RwReal arg_14, RwReal arg_18, RwReal *arg_1C)
{
    RwReal local_10;
    RwInt32 stk_14;
    RwReal loc18;

    stk_14 = 0;
    local_10 = 0.0f;
    if (arg_0 != 0 && ((unk_568->unk_28 >> 5) & 1) != 0) {
        loc18 = 0.0f;
        if (((unk_49C >> 18) & 1) != 0 && unk_598 == 0 && unk_59C == 0)
            stk_14 = sub_2F440(arg_0, arg_4, arg_8, arg_C, arg_10, arg_14, arg_18, &loc18, &local_10);
        if ((unk_49C & 1) != 0 && unk_598 == 0 && unk_59C == 0
                && (arg_0->unk_54[0].unk_00 != 0 || arg_0->unk_54[2].unk_00 != 0
                    || arg_0->unk_54[1].unk_00 != 0 || arg_0->unk_54[3].unk_00 != 0)) {
            RwInt32 local_7C;
            RwV3d local_78;
            type_3D3548 *var_6C;
            RwV3d v68;
            RwReal lcl_5C;
            RwReal var54;
            RwReal l50;
            RwV3d v4C;
            RwReal v40;
            RwV3d v3C;
            RwInt32 ebp_30;
            RwInt32 v2C;
            RwV3d var_28;
            RwInt32 l1C;

            v2C = 0;
            local_7C = 0;
            ebp_30 = 0;
            l1C = 0;
            var54 = 1.0e37f;
            lcl_5C = 1.0e37f;
            l50 = 1.0e37f;
            v40 = 1.0e37f;
            type_D48D0 bp_58;
            if (arg_0->unk_2D4[0].unk_00 != 0) {
                bp_58 = arg_0->unk_2D4[0].unk_20;
                var_6C = bp_58.sub_D4910();
                if (var_6C != 0) {
                    RwV3dSub(&v68, &arg_4->pos, var_6C->sub_CD550());
                    var54 = fabs(RwV3dDotProduct(&v68, &v68));
                    if ((arg_0->unk_54[0].unk_00 != 0 && var54 < arg_0->unk_54[0].unk_04)
                            || arg_0->unk_54[0].unk_00 == 0) {
                        v68.y = 0.0f;
                        RwV3dNormalize(&v3C, &v68);
                        v2C = 1;
                    }
                }
            }
            if (v2C == 0 && arg_0->unk_54[0].unk_00 != 0) {
                v2C = 1;
                v3C = arg_0->unk_54[0].unk_14;
                var54 = arg_0->unk_54[0].unk_04;
            }
            if (arg_0->unk_2D4[2].unk_00 != 0) {
                bp_58 = arg_0->unk_2D4[2].unk_20;
                var_6C = bp_58.sub_D4910();
                if (var_6C != 0) {
                    RwV3dSub(&v68, &arg_4->pos, var_6C->sub_CD550());
                    lcl_5C = fabs(RwV3dDotProduct(&v68, &v68));
                    if ((arg_0->unk_54[2].unk_00 != 0 && lcl_5C < arg_0->unk_54[2].unk_04)
                            || arg_0->unk_54[2].unk_00 == 0) {
                        v68.y = 0.0f;
                        RwV3dNormalize(&var_28, &v68);
                        local_7C = 1;
                    }
                }
            }
            if (local_7C == 0 && arg_0->unk_54[2].unk_00 != 0) {
                local_7C = 1;
                var_28 = arg_0->unk_54[2].unk_14;
                lcl_5C = arg_0->unk_54[2].unk_04;
            }
            if (arg_0->unk_2D4[1].unk_00 != 0) {
                bp_58 = arg_0->unk_2D4[1].unk_20;
                var_6C = bp_58.sub_D4910();
                if (var_6C != 0) {
                    RwV3dSub(&v68, &arg_4->pos, var_6C->sub_CD550());
                    l50 = fabs(RwV3dDotProduct(&v68, &v68));
                    if ((arg_0->unk_54[1].unk_00 != 0 && l50 < arg_0->unk_54[1].unk_04)
                            || arg_0->unk_54[1].unk_00 == 0) {
                        v68.y = 0.0f;
                        RwV3dNormalize(&v4C, &v68);
                        ebp_30 = 1;
                    }
                }
            }
            if (ebp_30 == 0 && arg_0->unk_54[1].unk_00 != 0) {
                ebp_30 = 1;
                v4C = arg_0->unk_54[1].unk_14;
                l50 = arg_0->unk_54[1].unk_04;
            }
            if (arg_0->unk_2D4[3].unk_00 != 0) {
                bp_58 = arg_0->unk_2D4[3].unk_20;
                var_6C = bp_58.sub_D4910();
                if (var_6C != 0) {
                    RwV3dSub(&v68, &arg_4->pos, var_6C->sub_CD550());
                    v40 = fabs(RwV3dDotProduct(&v68, &v68));
                    if ((arg_0->unk_54[3].unk_00 != 0 && v40 < arg_0->unk_54[3].unk_04)
                            || arg_0->unk_54[3].unk_00 == 0) {
                        v68.y = 0.0f;
                        RwV3dNormalize(&local_78, &v68);
                        l1C = 1;
                    }
                }
            }
            if (l1C == 0 && arg_0->unk_54[3].unk_00 != 0) {
                l1C = 1;
                local_78 = arg_0->unk_54[3].unk_14;
                v40 = arg_0->unk_54[3].unk_04;
            }
            if (v2C != 0) {
                RwReal var_80;
                RwReal var_84;

                var_84 = atan2(v3C.z, v3C.x) * 57.295776f;
                var_80 = RwV3dDotProduct(arg_C, &v3C);
                if (local_7C != 0 && ebp_30 != 0) {
                    local_10 = var_84;
                    loc18 = -12.0f;
                } else if (local_7C != 0) {
                    RwReal var_88;

                    var_88 = RwV3dDotProduct(arg_C, &var_28);
                    if (arg_8 != 0 && arg_10 < 0.0f && var_80 > 0.0f && var_88 > 0.0f) {
                        local_10 = arg_14;
                        loc18 = -6.0f;
                    } else {
                        local_10 = sub_13F9E0(var_84 - 90.0f);
                        loc18 = -(6.0f * flt_4275EC);
                    }
                } else if (ebp_30 != 0) {
                    RwReal var_8C;

                    var_8C = RwV3dDotProduct(arg_C, &v4C);
                    if (arg_8 != 0 && arg_10 > 0.0f && var_80 > 0.0f && var_8C > 0.0f) {
                        local_10 = arg_14;
                        loc18 = 6.0f;
                    } else {
                        local_10 = sub_13F9E0(var_84 + 90.0f);
                        loc18 = 6.0f * flt_4275EC;
                    }
                } else if (arg_8 != 0 && arg_10 > 0.0f && var_80 > 0.0f) {
                    local_10 = arg_14;
                    loc18 = 6.0f;
                } else if (arg_8 != 0 && arg_10 < 0.0f && var_80 > 0.0f) {
                    local_10 = arg_14;
                    loc18 = -6.0f;
                } else {
                    RwV3d var_98;

                    RwV3dCrossProduct(&var_98, &v3C, &arg_4->at);
                    if (var_98.y > 0.0f) {
                        local_10 = sub_13F9E0(var_84 - 90.0f);
                        loc18 = -6.0f;
                    } else {
                        local_10 = sub_13F9E0(var_84 + 90.0f);
                        loc18 = 6.0f;
                    }
                }
                stk_14 = 1;
            } else {
                RwInt32 var_9C;

                var_9C = 0;
                if (local_7C != 0 && ebp_30 != 0) {
                    if (lcl_5C <= l50)
                        var_9C = 1;
                    else
                        var_9C = 2;
                } else if (local_7C != 0) {
                    var_9C = 1;
                } else if (ebp_30 != 0) {
                    var_9C = 2;
                }
                if (var_9C == 1) {
                    RwReal var_A0;

                    var_A0 = RwV3dDotProduct(arg_C, &var_28);
                    if (arg_8 != 0 && arg_10 < 0.0f && var_A0 > 0.0f) {
                        local_10 = arg_14;
                        loc18 = -6.0f;
                    } else {
                        RwV3d var_AC;
                        RwReal slot_B0;

                        slot_B0 = atan2(var_28.z, var_28.x) * 57.295776f;
                        RwV3dCrossProduct(&var_AC, &var_28, &arg_4->at);
                        if (var_AC.y > 0.0f) {
                            local_10 = sub_13F9E0(slot_B0 - 90.0f);
                            loc18 = -6.0f;
                        } else {
                            local_10 = sub_13F9E0(slot_B0 + 90.0f);
                            loc18 = 6.0f;
                        }
                    }
                    stk_14 = 1;
                } else if (var_9C == 2) {
                    RwReal var_B4;

                    var_B4 = RwV3dDotProduct(arg_C, &v4C);
                    if (arg_8 != 0 && arg_10 > 0.0f && var_B4 > 0.0f) {
                        local_10 = arg_14;
                        loc18 = 6.0f;
                    } else {
                        RwV3d var_C0;
                        RwReal var_C4;

                        var_C4 = atan2(v4C.z, v4C.x) * 57.295776f;
                        RwV3dCrossProduct(&var_C0, &v4C, &arg_4->at);
                        if (var_C0.y > 0.0f) {
                            local_10 = sub_13F9E0(var_C4 - 90.0f);
                            loc18 = -6.0f;
                        } else {
                            local_10 = sub_13F9E0(var_C4 + 90.0f);
                            loc18 = 6.0f;
                        }
                    }
                    stk_14 = 1;
                }
            }
        }
        if (arg_18 <= 0.0f)
            stk_14 = 0;
        if (stk_14 != 0) {
            RwReal var_C8;
            RwReal lv_CC;
            RwReal var_D0;

            lv_CC = atan2(arg_4->right.x, arg_4->at.x) * 57.295776f;
            var_C8 = fabs(var_D0 = RWS::DegAngDiff(local_10, lv_CC) / arg_18);
            if (var_C8 > 6.0f) {
                if (var_D0 < 0.0f)
                    unk_568->unk_E8 = -fabs(loc18);
                else
                    unk_568->unk_E8 = fabs(loc18);
            } else {
                unk_568->unk_E8 = var_D0;
            }
            sub_19B650(unk_568->unk_E4);
        }
    }
    if (arg_1C != 0)
        *arg_1C = local_10;
    if (unk_598 != 0 || unk_59C != 0)
        stk_14 = 1;
    return stk_14;
}
// match: sub_2F440 @ 0x0002F440
// match: __ehhandler$?sub_2F440@AIData@@QAEHPAUtype_3DAFC8_1DDC@@PAURwMatrixTag@@PAURwV3d@@2MMMPAM3@Z-8 @ 0x002FF560
// match: __ehhandler$?sub_2F440@AIData@@QAEHPAUtype_3DAFC8_1DDC@@PAURwMatrixTag@@PAURwV3d@@2MMMPAM3@Z @ 0x002FF568
RwInt32 AIData::sub_2F440(type_3DAFC8_1DDC *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwV3d *arg_C,
                          RwReal arg_10, RwReal arg_14, RwReal arg_18, RwReal *arg_1C,
                          RwReal *arg_20)
{
    RwInt32 slot_44;
    RwReal l40;
    type_3D3548 *var_3C;
    RwReal v34;
    RwInt32 v30;
    RwReal var_2C;
    RwReal loc28;
    type_3D3548 *slot_24;
    RwInt32 v20;
    type_3D3548 *slot_1C;
    RwInt32 local_18;
    RwInt32 local_14;
    type_3D3548 *local_10;

    local_14 = 0;
    type_D48D0 l38;
    var_3C = 0;
    slot_1C = 0;
    slot_24 = 0;
    local_10 = 0;
    slot_44 = 0;
    v30 = 0;
    local_18 = 0;
    v20 = 0;
    var_2C = (var_2C = unk_568->unk_4C - flt_438D2C) * var_2C;
    l40 = RwV3dDotProduct(&arg_4->at, arg_C);
    loc28 = 0.0f;
    v34 = 0.0f;
    if (unk_598 != 0)
        v34 = dword_438D28;
    if (arg_0->unk_2D4[0].unk_00 != 0) {
        l38 = arg_0->unk_2D4[0].unk_20;
        var_3C = l38.sub_D4910();
        if (var_3C != 0 && var_3C->vf_120() != 0 && var_3C->vf_120()->sub_238E0(0) != 0)
            slot_44 = 1;
    }
    if (arg_0->unk_2D4[2].unk_00 != 0) {
        l38 = arg_0->unk_2D4[2].unk_20;
        slot_1C = l38.sub_D4910();
        if (slot_1C != 0 && slot_1C->vf_120() != 0 && slot_1C->vf_120()->sub_238E0(0) != 0)
            v30 = 1;
    }
    if (arg_0->unk_2D4[1].unk_00 != 0) {
        l38 = arg_0->unk_2D4[1].unk_20;
        slot_24 = l38.sub_D4910();
        if (slot_24 != 0 && slot_24->vf_120() != 0 && slot_24->vf_120()->sub_238E0(0) != 0)
            local_18 = 1;
    }
    if (arg_0->unk_2D4[0].unk_00 != 0 && var_3C != 0) {
        RwReal var_60;
        RwV3d var_5C;
        RwV3d var_50;

        RwV3dSub(&var_5C, &arg_4->pos, var_3C->sub_CD550());
        var_5C.y = 0.0f;
        RwV3dNormalize(&var_50, &var_5C);
        var_60 = atan2(var_50.z, var_50.x) * 57.295776f;
        loc28 = (loc28 = unk_568->unk_4C + var_3C->unk_4C + v34) * loc28;
        if (slot_1C != 0 && slot_24 != 0) {
            if (arg_0->unk_2D4[3].unk_00 != 0) {
                l38 = arg_0->unk_2D4[3].unk_20;
                local_10 = l38.sub_D4910();
                if (local_10 != 0 && local_10->vf_120() != 0 && local_10->vf_120()->sub_238E0(0) != 0)
                    v20 = 1;
            }
            if ((arg_0->unk_54[7].unk_00 == 0 && local_10 == 0) || v20 != 0
                    || ((unk_49C >> 23) & 1) == 0 || slot_44 != 0) {
                *arg_20 = sub_13F9E0(var_60);
                *arg_1C = -12.0f;
                local_14 = 1;
                sub_30960();
            } else {
                sub_308C0(var_3C);
            }
        } else if (slot_1C != 0) {
            if ((arg_0->unk_54[5].unk_00 != 0 && arg_0->unk_54[5].unk_04 > loc28)
                    || arg_0->unk_54[5].unk_00 == 0 || ((unk_49C >> 23) & 1) == 0 || slot_44 != 0) {
                if ((l40 > 0.5f || (l40 > 0.0f && arg_10 > 0.0f))
                        && arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 < loc28
                        && ((unk_49C >> 23) & 1) != 0 && slot_44 == 0) {
                    sub_308C0(var_3C);
                } else {
                    if (arg_8 != 0 && arg_10 < 0.0f)
                        *arg_20 = arg_14;
                    else
                        *arg_20 = sub_13F9E0(var_60 - 90.0f);
                    *arg_1C = -6.0f;
                    local_14 = 1;
                    sub_30960();
                }
            } else {
                sub_308C0(var_3C);
            }
        } else if (slot_24 != 0) {
            if ((arg_0->unk_54[6].unk_00 != 0 && arg_0->unk_54[6].unk_04 > loc28)
                    || arg_0->unk_54[6].unk_00 == 0 || ((unk_49C >> 23) & 1) == 0 || slot_44 != 0) {
                if ((l40 > 0.5f || (l40 > 0.0f && arg_10 < 0.0f))
                        && arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 < loc28
                        && ((unk_49C >> 23) & 1) != 0 && slot_44 == 0) {
                    sub_308C0(var_3C);
                } else {
                    if (arg_8 != 0 && arg_10 > 0.0f)
                        *arg_20 = arg_14;
                    else
                        *arg_20 = sub_13F9E0(var_60 + 90.0f);
                    *arg_1C = 6.0f;
                    local_14 = 1;
                    sub_30960();
                }
            } else {
                sub_308C0(var_3C);
            }
        } else {
            RwReal var_64;

            var_64 = RwV3dDotProduct(arg_C, &var_50);
            if (arg_8 != 0 && arg_10 > 0.0f && var_64 > 0.0f) {
                *arg_20 = arg_14;
                *arg_1C = 6.0f;
                local_14 = 1;
                sub_30960();
            } else if (arg_8 != 0 && arg_10 < 0.0f && var_64 > 0.0f) {
                *arg_20 = arg_14;
                *arg_1C = -6.0f;
                local_14 = 1;
                sub_30960();
            } else {
                RwV3d var_70;

                RwV3dCrossProduct(&var_70, &var_50, &arg_4->at);
                if ((var_70.y > 0.0f
                        && ((arg_0->unk_54[5].unk_00 != 0 && arg_0->unk_54[5].unk_04 > loc28)
                            || arg_0->unk_54[5].unk_00 == 0)
                        && ((arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 > loc28)
                            || arg_0->unk_54[4].unk_00 == 0))
                        || (var_70.y > 0.0f && ((unk_49C >> 23) & 1) == 0)) {
                    *arg_20 = sub_13F9E0(var_60 - 90.0f);
                    *arg_1C = -6.0f;
                    local_14 = 1;
                    sub_30960();
                } else if ((((arg_0->unk_54[6].unk_00 != 0 && arg_0->unk_54[6].unk_04 > loc28)
                                || arg_0->unk_54[6].unk_00 == 0)
                            && ((arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 > loc28)
                                || arg_0->unk_54[4].unk_00 == 0))
                        || ((unk_49C >> 23) & 1) == 0) {
                    *arg_20 = sub_13F9E0(var_60 + 90.0f);
                    *arg_1C = 6.0f;
                    local_14 = 1;
                    sub_30960();
                } else if (arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 < loc28) {
                    RwReal var_74;

                    var_74 = RwV3dDotProduct(&arg_0->unk_54[4].unk_14, arg_C);
                    if (var_74 > 0.0f && arg_10 < 0.0f
                            && ((arg_0->unk_54[5].unk_00 != 0 && arg_0->unk_54[5].unk_04 > loc28)
                                || arg_0->unk_54[5].unk_00 == 0)) {
                        if (arg_8 != 0)
                            *arg_20 = arg_14;
                        else
                            *arg_20 = sub_13F9E0(var_60 + 90.0f);
                        *arg_1C = -6.0f;
                        local_14 = 1;
                        sub_30960();
                    } else if (var_74 > 0.0f && arg_10 > 0.0f
                            && ((arg_0->unk_54[6].unk_00 != 0 && arg_0->unk_54[6].unk_04 > loc28)
                                || arg_0->unk_54[6].unk_00 == 0)) {
                        if (arg_8 != 0)
                            *arg_20 = arg_14;
                        else
                            *arg_20 = sub_13F9E0(var_60 - 90.0f);
                        *arg_1C = 6.0f;
                        local_14 = 1;
                        sub_30960();
                    } else {
                        sub_308C0(var_3C);
                    }
                } else if ((var_70.y < 0.0f
                        && ((arg_0->unk_54[5].unk_00 != 0 && arg_0->unk_54[5].unk_04 > loc28)
                            || arg_0->unk_54[5].unk_00 == 0)
                        && ((arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 > loc28)
                            || arg_0->unk_54[4].unk_00 == 0))
                        || (var_70.y < 0.0f && (((unk_49C >> 23) & 1) == 0 || slot_44 != 0))) {
                    *arg_20 = sub_13F9E0(var_60 - 90.0f);
                    *arg_1C = -6.0f;
                    local_14 = 1;
                    sub_30960();
                } else if ((var_70.y > 0.0f
                        && ((arg_0->unk_54[6].unk_00 != 0 && arg_0->unk_54[6].unk_04 > loc28)
                            || arg_0->unk_54[6].unk_00 == 0)
                        && ((arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 > loc28)
                            || arg_0->unk_54[4].unk_00 == 0))
                        || (var_70.y > 0.0f && (((unk_49C >> 23) & 1) == 0 || slot_44 != 0))) {
                    *arg_20 = sub_13F9E0(var_60 + 90.0f);
                    *arg_1C = 6.0f;
                    local_14 = 1;
                    sub_30960();
                } else {
                    sub_308C0(var_3C);
                }
            }
        }
    } else {
        RwInt32 var_78;

        var_78 = 0;
        if (slot_1C != 0 && slot_24 != 0) {
            if (arg_0->unk_2D4[2].unk_04 <= arg_0->unk_2D4[1].unk_04)
                var_78 = 1;
            else
                var_78 = 2;
        } else if (slot_1C != 0) {
            var_78 = 1;
        } else if (slot_24 != 0) {
            var_78 = 2;
        }
        if (var_78 == 1) {
            loc28 = (loc28 = unk_568->unk_4C + slot_1C->unk_4C + v34) * loc28;
            if ((l40 > 0.5f || (l40 > 0.0f && arg_10 > 0.0f))
                    && arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 < loc28
                    && ((unk_49C >> 23) & 1) != 0 && v30 == 0) {
                sub_308C0(slot_1C);
            } else if (arg_8 != 0 && arg_10 < 0.0f) {
                if ((arg_0->unk_54[5].unk_00 != 0 && arg_0->unk_54[5].unk_04 >= var_2C)
                        || arg_0->unk_54[5].unk_00 == 0 || ((unk_49C >> 23) & 1) == 0
                        || v30 != 0) {
                    *arg_20 = arg_14;
                    *arg_1C = -6.0f;
                    local_14 = 1;
                    sub_30960();
                } else {
                    sub_308C0(slot_1C);
                }
            } else {
                RwReal local_A0;
                RwV3d l9C;
                RwV3d lv_90;
                RwV3d var_84;

                RwV3dSub(&l9C, &arg_4->pos, slot_1C->sub_CD550());
                l9C.y = 0.0f;
                RwV3dNormalize(&var_84, &l9C);
                local_A0 = atan2(var_84.z, var_84.x) * 57.295776f;
                RwV3dCrossProduct(&lv_90, &var_84, &arg_4->at);
                if (lv_90.y > 0.0f) {
                    if ((arg_0->unk_54[5].unk_00 != 0 && arg_0->unk_54[5].unk_04 >= var_2C)
                            || arg_0->unk_54[5].unk_00 == 0 || ((unk_49C >> 23) & 1) == 0
                            || v30 != 0) {
                        *arg_20 = sub_13F9E0(local_A0 - 90.0f);
                        *arg_1C = -6.0f;
                        local_14 = 1;
                        sub_30960();
                    } else {
                        sub_308C0(slot_1C);
                    }
                } else if ((arg_0->unk_54[6].unk_00 != 0 && arg_0->unk_54[6].unk_04 >= var_2C)
                        || arg_0->unk_54[6].unk_00 == 0 || ((unk_49C >> 23) & 1) == 0
                        || v30 != 0) {
                    *arg_20 = sub_13F9E0(local_A0 + 90.0f);
                    *arg_1C = 6.0f;
                    local_14 = 1;
                    sub_30960();
                } else {
                    sub_308C0(slot_1C);
                }
            }
        } else if (var_78 == 2) {
            loc28 = (loc28 = unk_568->unk_4C + slot_24->unk_4C + v34) * loc28;
            if ((l40 > 0.5f || (l40 > 0.0f && arg_10 < 0.0f))
                    && arg_0->unk_54[4].unk_00 != 0 && arg_0->unk_54[4].unk_04 < loc28
                    && ((unk_49C >> 23) & 1) != 0 && local_18 == 0) {
                sub_308C0(slot_24);
            } else if (arg_8 != 0 && arg_10 > 0.0f) {
                if ((arg_0->unk_54[6].unk_00 != 0 && arg_0->unk_54[6].unk_04 >= var_2C)
                        || arg_0->unk_54[6].unk_00 == 0 || ((unk_49C >> 23) & 1) == 0
                        || local_18 != 0) {
                    *arg_20 = arg_14;
                    *arg_1C = 6.0f;
                    local_14 = 1;
                    sub_30960();
                } else {
                    sub_308C0(slot_24);
                }
            } else {
                RwReal lC8;
                RwV3d lC4;
                RwV3d varB8;
                RwV3d var_AC;

                RwV3dSub(&lC4, &arg_4->pos, slot_24->sub_CD550());
                lC4.y = 0.0f;
                RwV3dNormalize(&var_AC, &lC4);
                lC8 = atan2(var_AC.z, var_AC.x) * 57.295776f;
                RwV3dCrossProduct(&varB8, &var_AC, &arg_4->at);
                if (varB8.y > 0.0f) {
                    if ((arg_0->unk_54[5].unk_00 != 0 && arg_0->unk_54[5].unk_04 >= var_2C)
                            || arg_0->unk_54[5].unk_00 == 0 || ((unk_49C >> 23) & 1) == 0
                            || local_18 != 0) {
                        *arg_20 = sub_13F9E0(lC8 - 90.0f);
                        *arg_1C = -6.0f;
                        local_14 = 1;
                        sub_30960();
                    } else {
                        sub_308C0(slot_24);
                    }
                } else if ((arg_0->unk_54[6].unk_00 != 0 && arg_0->unk_54[6].unk_04 >= var_2C)
                        || arg_0->unk_54[6].unk_00 == 0 || ((unk_49C >> 23) & 1) == 0
                        || local_18 != 0) {
                    *arg_20 = sub_13F9E0(lC8 + 90.0f);
                    *arg_1C = 6.0f;
                    local_14 = 1;
                    sub_30960();
                } else {
                    sub_308C0(slot_24);
                }
            }
        } else {
            sub_30960();
        }
    }
    return local_14;
}
// match: sub_30850 @ 0x00030850
void AIData::sub_30850(RwInt32 arg_0)
{
    unk_598 = arg_0;
    if (arg_0 == 0) {
        sub_309E0(0);
        unk_5A0 = 0;
    } else if (((unk_49C >> 15) & 1) != 0) {
        unk_5A0 = 1;
    } else {
        unk_5A0 = 0;
    }
}
// match: sub_308C0 @ 0x000308C0
void AIData::sub_308C0(type_3D3548 *arg_0)
{
    if (((unk_49C >> 23) & 1) != 0) {
        if (unk_598 == 0) {
            sub_30850(1);
            if (unk_59C == 0) {
                sub_6B5F0("AStar_PathBlocked", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                if (arg_0 != 0)
                    sub_309E0(arg_0);
            }
        }
    } else {
        sub_30850(0);
    }
}
// match: sub_30960 @ 0x00030960
void AIData::sub_30960()
{
    if (((unk_49C >> 23) & 1) != 0) {
        if (unk_598 != 0) {
            sub_30850(0);
            if (unk_59C == 0)
                sub_6B5F0("AStar_PathUnBlocked", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        }
    } else {
        sub_30850(0);
    }
}
// match: sub_309E0 @ 0x000309E0
void AIData::sub_309E0(type_3D3548 *arg_0)
{
    if (arg_0 != 0 && arg_0->vf_00C() != 0)
        arg_0 = 0;
    if (arg_0 == 0 || arg_0 != unk_584.sub_D4910()) {
        unk_588 = 0.0f;
        unk_584.sub_D48D0(arg_0);
    }
}
// match: sub_30A50 @ 0x00030A50
void AIData::sub_30A50(RwReal arg_0)
{
    type_3D3548 *var_4;
    RwInt32 local_8;

    var_4 = unk_584.sub_D4910();
    if (var_4 != 0 && var_4->vf_008() != 0) {
        unk_588 = arg_0 + unk_588;
        if (unk_588 > flt_438D30 && var_4->vf_098() != 0 && cmp_unk_2C(var_4, unk_568) == 0) {
            local_8 = unk_568->vf_09C();
            sub_6B5F0("BlockingEntity", (type_67620 *)(var_4->vf_098()), 0, 0, &local_8, 1, true, false);
        }
    }
}
// match: sub_30B90 @ 0x00030B90
// match: __ehhandler$?sub_30B90@AIData@@QAEXPAURwMatrixTag@@PAUtype_3DAFC8_1DDC@@1@Z-8 @ 0x002FF580
// match: __ehhandler$?sub_30B90@AIData@@QAEXPAURwMatrixTag@@PAUtype_3DAFC8_1DDC@@1@Z @ 0x002FF588
void AIData::sub_30B90(RwMatrix *arg_0, type_3DAFC8_1DDC *arg_4, type_3DAFC8_1DDC *arg_8)
{
    type_30B90_48 v48;
    RwV3d var_1C;
    type_3D3548 *local_10;

    *arg_4 = *arg_8;
    arg_4->unk_30 = arg_0->at;
    arg_4->unk_3C = arg_0->right;
    arg_4->unk_54[0].unk_00 = 0;
    arg_4->unk_54[0].unk_04 = 1.0e37f;
    arg_4->unk_54[1].unk_00 = 0;
    arg_4->unk_54[1].unk_04 = 1.0e37f;
    arg_4->unk_54[2].unk_00 = 0;
    arg_4->unk_54[2].unk_04 = 1.0e37f;
    arg_4->unk_54[3].unk_00 = 0;
    arg_4->unk_54[3].unk_04 = 1.0e37f;
    arg_4->unk_54[4].unk_00 = 0;
    arg_4->unk_54[4].unk_04 = 1.0e37f;
    arg_4->unk_54[5].unk_00 = 0;
    arg_4->unk_54[5].unk_04 = 1.0e37f;
    arg_4->unk_54[6].unk_00 = 0;
    arg_4->unk_54[6].unk_04 = 1.0e37f;
    arg_4->unk_54[7].unk_00 = 0;
    arg_4->unk_54[7].unk_04 = 1.0e37f;
    arg_4->unk_2D4[0].unk_00 = 0;
    arg_4->unk_2D4[0].unk_04 = 1.0e37f;
    arg_4->unk_2D4[1].unk_00 = 0;
    arg_4->unk_2D4[1].unk_04 = 1.0e37f;
    arg_4->unk_2D4[2].unk_00 = 0;
    arg_4->unk_2D4[2].unk_04 = 1.0e37f;
    arg_4->unk_2D4[3].unk_00 = 0;
    arg_4->unk_2D4[3].unk_04 = 1.0e37f;
    var_1C.x = 0.0f;
    var_1C.y = 0.0f;
    var_1C.z = 0.0f;
    v48.unk_18 = 0;
    v48.unk_0C = v48.unk_10 = v48.unk_14 = 0;
    v48.unk_1C = &var_1C;
    v48.unk_20 = &var_1C;
    v48.unk_24 = &var_1C;
    if (arg_8->unk_54[0].unk_00 != 0) {
        v48.unk_00 = arg_8->unk_54[0].unk_14;
        v48.unk_1C = &arg_8->unk_54[0].unk_2C;
        v48.unk_20 = &arg_8->unk_54[0].unk_38;
        v48.unk_24 = &arg_8->unk_54[0].unk_44;
        sub_992B0(0, &arg_8->unk_54[0].unk_08, arg_4, &arg_8->unk_54[0].unk_20, &v48);
    }
    if (arg_8->unk_54[2].unk_00 != 0) {
        v48.unk_00 = arg_8->unk_54[2].unk_14;
        v48.unk_1C = &arg_8->unk_54[2].unk_2C;
        v48.unk_20 = &arg_8->unk_54[2].unk_38;
        v48.unk_24 = &arg_8->unk_54[2].unk_44;
        sub_992B0(0, &arg_8->unk_54[2].unk_08, arg_4, &arg_8->unk_54[2].unk_20, &v48);
    }
    if (arg_8->unk_54[1].unk_00 != 0) {
        v48.unk_00 = arg_8->unk_54[1].unk_14;
        v48.unk_1C = &arg_8->unk_54[1].unk_2C;
        v48.unk_20 = &arg_8->unk_54[1].unk_38;
        v48.unk_24 = &arg_8->unk_54[1].unk_44;
        sub_992B0(0, &arg_8->unk_54[1].unk_08, arg_4, &arg_8->unk_54[1].unk_20, &v48);
    }
    if (arg_8->unk_54[3].unk_00 != 0) {
        v48.unk_00 = arg_8->unk_54[3].unk_14;
        v48.unk_1C = &arg_8->unk_54[3].unk_2C;
        v48.unk_20 = &arg_8->unk_54[3].unk_38;
        v48.unk_24 = &arg_8->unk_54[3].unk_44;
        sub_992B0(0, &arg_8->unk_54[3].unk_08, arg_4, &arg_8->unk_54[3].unk_20, &v48);
    }
    if (arg_8->unk_54[4].unk_00 != 0) {
        v48.unk_00 = arg_8->unk_54[4].unk_14;
        v48.unk_1C = &arg_8->unk_54[4].unk_2C;
        v48.unk_20 = &arg_8->unk_54[4].unk_38;
        v48.unk_24 = &arg_8->unk_54[4].unk_44;
        // Record 0's unk_20, not record 4's: the image passes +0x74 here.
        sub_992B0(1, &arg_8->unk_54[4].unk_08, arg_4, &arg_8->unk_54[0].unk_20, &v48);
    }
    if (arg_8->unk_54[7].unk_00 != 0) {
        v48.unk_00 = arg_8->unk_54[7].unk_14;
        v48.unk_1C = &arg_8->unk_54[7].unk_2C;
        v48.unk_20 = &arg_8->unk_54[7].unk_38;
        v48.unk_24 = &arg_8->unk_54[7].unk_44;
        sub_992B0(1, &arg_8->unk_54[7].unk_08, arg_4, &arg_8->unk_54[7].unk_20, &v48);
    }
    if (arg_8->unk_54[6].unk_00 != 0) {
        v48.unk_00 = arg_8->unk_54[6].unk_14;
        v48.unk_1C = &arg_8->unk_54[6].unk_2C;
        v48.unk_20 = &arg_8->unk_54[6].unk_38;
        v48.unk_24 = &arg_8->unk_54[6].unk_44;
        sub_992B0(1, &arg_8->unk_54[6].unk_08, arg_4, &arg_8->unk_54[6].unk_20, &v48);
    }
    if (arg_8->unk_54[5].unk_00 != 0) {
        v48.unk_00 = arg_8->unk_54[5].unk_14;
        v48.unk_1C = &arg_8->unk_54[5].unk_2C;
        v48.unk_20 = &arg_8->unk_54[5].unk_38;
        v48.unk_24 = &arg_8->unk_54[5].unk_44;
        sub_992B0(1, &arg_8->unk_54[5].unk_08, arg_4, &arg_8->unk_54[5].unk_20, &v48);
    }
    type_D48D0 l20;
    if (arg_8->unk_2D4[0].unk_00 != 0) {
        l20 = arg_8->unk_2D4[0].unk_20;
        local_10 = l20.sub_D4910();
        if (local_10 != 0)
            sub_9A2D0(local_10, &arg_8->unk_2D4[0].unk_08, &arg_8->unk_2D4[0].unk_14, arg_4);
    }
    if (arg_8->unk_2D4[3].unk_00 != 0) {
        l20 = arg_8->unk_2D4[3].unk_20;
        local_10 = l20.sub_D4910();
        if (local_10 != 0)
            sub_9A2D0(local_10, &arg_8->unk_2D4[3].unk_08, &arg_8->unk_2D4[3].unk_14, arg_4);
    }
    if (arg_8->unk_2D4[2].unk_00 != 0) {
        l20 = arg_8->unk_2D4[2].unk_20;
        local_10 = l20.sub_D4910();
        if (local_10 != 0)
            sub_9A2D0(local_10, &arg_8->unk_2D4[2].unk_08, &arg_8->unk_2D4[2].unk_14, arg_4);
    }
    if (arg_8->unk_2D4[1].unk_00 != 0) {
        l20 = arg_8->unk_2D4[1].unk_20;
        local_10 = l20.sub_D4910();
        if (local_10 != 0)
            sub_9A2D0(local_10, &arg_8->unk_2D4[1].unk_08, &arg_8->unk_2D4[1].unk_14, arg_4);
    }
}
// A path of up to arg_8 nodes from the node nearest the owner, each step
// the linked node lying furthest along arg_4 (never one already taken),
// until the steps add up to arg_C; the path arg_0 is then set up to be
// followed from its first node to its last. 0 when no step was found.
// match: sub_31240 @ 0x00031240
// match: __ehhandler$?sub_31240@AIData@@QAEHPAUtype_154C0_5BC@@PAURwV3d@@HM@Z-0xB @ 0x002FF5A0
// match: __ehhandler$?sub_31240@AIData@@QAEHPAUtype_154C0_5BC@@PAURwV3d@@HM@Z @ 0x002FF5AB
RwInt32 AIData::sub_31240(type_154C0_5BC *arg_0, RwV3d *arg_4, RwInt32 arg_8, RwReal arg_C)
{
    type_154C0_1048 lv_78;
    type_F8350 *lv_7C;
    RwInt32 lv_80;
    RwInt32 lv_94[5];
    RwInt32 lv_98;
    RwReal lv_9C;
    RwInt32 lv_A0;
    RwInt32 lv_154;

    lv_78.unk_04 = *unk_568->sub_CD550();
    lv_78.unk_10 = 1500.0f;
    lv_78.unk_00 = unk_568;
    lv_78.unk_18 = 0;
    lv_78.unk_1C = 0;
    lv_78.unk_20 = 0;
    lv_78.unk_24 = 0;
    lv_7C = sub_F8970(&lv_78, 0, 0);
    for (lv_80 = 0; lv_80 < arg_8; lv_80++)
        lv_94[lv_80] = -1;
    lv_98 = 0;
    lv_9C = 0.0f;
    for (lv_A0 = 0; lv_7C != 0 && lv_A0 < arg_8 && lv_9C < arg_C; lv_A0++)
    {
        RwReal lv_A4 = -1.0f;
        type_F8350 *lv_A8 = 0;
        RwInt32 lv_AC = -1;
        RwReal lv_B0 = -1.0f;
        RwUInt32 *lv_B4 = 0;

        if (lv_7C->unk_00 & 1)
            lv_B4 = lv_7C->unk_2C;
        else
            lv_B4 = lv_7C->unk_1C_links;
        for (type_3CE1FC lv_C8(lv_B4); !lv_C8.at_end(); lv_C8.sub_31A10())
        {
            type_F8350 *lv_D0 = sub_FA980(lv_C8.unk_0C);

            if (lv_D0->unk_00_7)
                continue;
            RwInt32 lv_D4 = 0;
            RwInt32 lv_D8;

            for (lv_D8 = 0; lv_D8 < lv_98; lv_D8++)
            {
                if (lv_C8.unk_0C == lv_94[lv_D8])
                    lv_D4 = 1;
            }
            if (lv_D0 == lv_A8 || lv_D4)
                continue;
            RwReal lv_DC = -1.0f;
            RwInt32 lv_E0 = lv_C8.unk_0C;
            RwReal lv_E4 = -1.0f;
            RwV3d lv_F0;

            RwV3dSubMacro(&lv_F0, &lv_D0->unk_10, &lv_7C->unk_10);
            lv_DC = RwV3dDotProductMacro(&lv_F0, arg_4);
            lv_E4 = RwV3dDotProductMacro(&lv_F0, &lv_F0);
            if (lv_AC < 0 || lv_DC > lv_A4)
            {
                lv_A4 = lv_DC;
                lv_A8 = lv_D0;
                lv_AC = lv_E0;
                lv_B0 = lv_E4;
            }
        }
        if (lv_AC == -1)
            break;
        lv_94[lv_A0] = lv_AC;
        do
        {
            __m128 lv_110 = _mm_set_ss(lv_B0);
            __m128 lv_130 = _mm_sqrt_ss(lv_110);
            _mm_store_ss(&lv_B0, lv_130);
        } while (0);
        lv_9C += lv_B0;
        lv_98++;
        lv_7C = lv_A8;
    }
    if (lv_98 > 0)
    {
        for (lv_154 = 0; lv_154 < lv_98; lv_154++)
            arg_0->unk_B0[lv_154] = (RwInt16)lv_94[lv_98 - (lv_154 + 1)];
        arg_0->unk_14 = sub_FA980(lv_94[0])->unk_10;
        arg_0->unk_20 = sub_FA980(lv_94[lv_98 - 1])->unk_10;
        arg_0->unk_2C = 1500.0f;
        arg_0->unk_54 = 0;
        arg_0->unk_58 = 0;
        arg_0->unk_60 = 3;
        arg_0->unk_5C = 0;
        arg_0->unk_04 = lv_98 - 1;
        arg_0->unk_34 = -1.0f;
        arg_0->unk_50.sub_D48D0(0);
        arg_0->unk_00 = -1;
        arg_0->unk_30 = 0;
        arg_0->unk_31 = 0;
        arg_0->unk_33 = 0;
        ((type_D48D0 *)&arg_0->unk_64.unk_00)->sub_D48D0(unk_568);
        arg_0->unk_64.unk_30 = (RwInt32)unk_568;
        arg_0->unk_64.unk_04 = &arg_0->unk_14;
        arg_0->unk_64.unk_08 = &arg_0->unk_20;
        arg_0->unk_64.unk_0C = arg_0->unk_2C;
        arg_0->unk_64.unk_10 = sub_F6BB0(arg_0->unk_54);
        arg_0->unk_64.unk_14 = sub_F6BF0(arg_0->unk_58);
        arg_0->unk_64.unk_18 = sub_F6C10(arg_0->unk_5C);
        arg_0->unk_64.unk_1C = arg_0->unk_60;
        arg_0->unk_64.unk_20 = 100;
        arg_0->unk_64.unk_24 = arg_0->unk_B0;
        arg_0->unk_64.unk_28 = 1;
        arg_0->unk_64.unk_2C = lv_98;
        zero_v3d(&arg_0->unk_38);
        zero_v3d(&arg_0->unk_44);
        return 1;
    }
    return 0;
}
// match: sub_31980 @ 0x00031980
// match: sub_31A10 @ 0x00031A10
// match: sub_31AD0 @ 0x00031AD0
void sub_31AD0()
{
    flt_438D38.sub_71F20(0x19, 1, 4, 0, sub_31C50, sub_31DB0);
    flt_438D88.sub_71F20(0x1E, 1, 1, 1, sub_31E20, 0);
}
// match: sub_31B10 @ 0x00031B10
void sub_31B10()
{
    RwInt32 var_4;

    var_4 = flt_438D38.sub_71FA0();
    if (var_4 != 0)
        sub_31B90();
    var_4 = flt_438D88.sub_71FA0();
    if (var_4 != 0)
        sub_31B90();
}
// match: sub_31B50 @ 0x00031B50
void sub_31B50()
{
    RwInt32 var_4;

    var_4 = flt_438D38.sub_71FC0();
    if (var_4 != 0)
        sub_31B90();
    var_4 = flt_438D88.sub_71FC0();
    if (var_4 != 0)
        sub_31B90();
}

// Others that return 1, which /OPT:ICF folded into it (the animations' and the
// frame loop's callers, the DDS loader's and the animation pool's).
RwInt32 sub_31DB0()
{
    return 1;
}

RwInt32 sub_31DB0(void *arg_0)
{
    return 1;
}

struct type_80300;
RwInt32 sub_31DB0(type_80300 *arg_0, RwReal arg_4, RwUInt8 arg_8)
{
    return 1;
}
extern const RwV3d stru_3CE268;
#ifdef CODFH_PLAIN
extern type_3D3548 *&dword_4B8640;
#else
extern type_3D3548 *dword_4B8640;
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_008@type_3CE278@@UAEXXZ (folded into 0x39440)
void type_3CE278::vf_008()
{
    type_3CE6D0::vf_008();
}

// ?vf_02C@type_3CE278@@UAEHXZ (folded into 0xA2CD0)
RwInt32 type_3CE278::vf_02C()
{
    return 9;
}

// ?vf_030@type_3CE278@@UAEHXZ (folded into 0x15FD20)
RwInt32 type_3CE278::vf_030()
{
    return 6;
}
