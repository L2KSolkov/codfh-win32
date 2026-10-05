// Split from unit_012000.cpp at 0x022C80, where the image starts another object: the one
// before it ends with the inline functions it kept out of line (sub_22C20, type_154C0_80's
// constructor), and its .rdata begins at 0x3CDE08 with its own constants, the unreferenced
// 16.666666 the others start theirs with first (PLAN M7).

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

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CDE08
extern const RwReal flt_3CDE08 = 16.666666f;
// 0x003CDE0C
extern const RwV3d stru_3CDE0C = { 0.0f, 1.0f, 0.0f };
// 0x003CDE18
extern const RwReal flt_3CDE18 = 0.5f;
// 0x003CDE1C
extern const RwReal flt_3CDE1C = 0.2f;
// 0x003CDE20
extern const RwReal flt_3CDE20 = 0.3f;
// 0x003CDE24
extern const RwReal flt_3CDE24 = 0.5f;
// 0x003CDE28
extern const RwReal flt_3CDE28 = 100.0f;
// 0x003CDE2C
extern const RwReal flt_3CDE2C = 4000000.0f;
// 0x003CDE30
extern const RwReal flt_3CDE30 = 100000000.0f;
// 0x004275E4
RwReal flt_4275E4 = 150.0f;
// 0x004275E8
RwReal flt_4275E8 = 22500.0f;
// 0x004275EC
RwReal flt_4275EC = 4.0f;
// 0x004275F0
RwReal dword_4275F0 = 30.0f;

// match: ?flt_3CDE08@@3MB @ 0x003CDE08
// match: ?stru_3CDE0C@@3URwV3d@@B @ 0x003CDE0C
// match: ?flt_3CDE18@@3MB @ 0x003CDE18
// match: ?flt_3CDE1C@@3MB @ 0x003CDE1C
// match: ?flt_3CDE20@@3MB @ 0x003CDE20
// match: ?flt_3CDE24@@3MB @ 0x003CDE24
// match: ?flt_3CDE28@@3MB @ 0x003CDE28
// match: ?flt_3CDE2C@@3MB @ 0x003CDE2C
// match: ?flt_3CDE30@@3MB @ 0x003CDE30
// match: ?flt_4275E4@@3MA @ 0x004275E4
// match: ?flt_4275E8@@3MA @ 0x004275E8
// match: ?flt_4275EC@@3MA @ 0x004275EC
// match: ?dword_4275F0@@3MA @ 0x004275F0


// match: __ehhandler$?sub_24BA0@AIData@@QAEHHHHPAH@Z>1>8 @ 0x0041AEC0
// match: __ehhandler$?sub_24BA0@AIData@@QAEHHHHPAH@Z>1 @ 0x0041AEC8

extern const RwV3d stru_3CDE0C;

// match: ?sub_22C80@AIData@@QAEXPAUtype_F8350@@PAURwV3d@@1@Z @ 0x00022C80
// match: ??_C@_0BH@DIDLLCHM@VehicleCoverPointFound?$AA@ @ 0x003CDE34
// match: ??_C@_0BK@DMPFLHBF@DefendAreaCoverPointFound?$AA@ @ 0x003CDE4C
// match: ??_C@_0HG@OIIJCIOL@Could?5not?5occupy?5defendarea?5cove@ @ 0x003CDE68
// match: ??_C@_0FL@IFOPFEIP@Could?5not?5occupy?5defendarea?5cove@ @ 0x003CDEE0
// match: ??_C@_0ED@MMFOEDGC@Could?5not?5occupy?5defendarea?5cove@ @ 0x003CDF40
// match: ??_C@_0DF@HBCECFMI@Occupation?5of?5selected?5defendare@ @ 0x003CDF84
// match: ??_C@_0BM@CCBJOHGK@CoverPointSearchTypeChanged?$AA@ @ 0x003CDFBC
// match: __real@48742400 @ 0x003CDFD8
// match: __real@38d1b717 @ 0x003CDFDC
// match: __real@45ea6000 @ 0x003CDFE0
// match: __real@4bbebc20 @ 0x003CDFE4
// match: __real@42480000 @ 0x003CDFE8
// match: __real@becccccd @ 0x003CDFEC
// match: __real@437a0000 @ 0x003CDFF0
// match: __real@3fe199999999999a @ 0x003CE000
// match: __real@3e4ccccd @ 0x003CE008
// match: __real@47742400 @ 0x003CE00C
// match: __real@3e99999a @ 0x003CE010
void AIData::sub_22C80(type_F8350 *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwMatrix var_50;
    RwV3d var_90;
    RwV3d var_9C;

    RwMatrixSetIdentity(&var_50);
    RtQuatConvertToMatrix(&arg_0->unk_1C, &var_50);
    RwMatrixRotate(&var_50, &stru_3CDE0C, 180.0f, rwCOMBINEPRECONCAT);
    sub_F8FE0(arg_0, &var_9C, &var_90);
    RwMatrixRotate(&var_50, &stru_3CDE0C, var_90.y, rwCOMBINEPRECONCAT);
    *arg_4 = var_50.at;
    *arg_8 = arg_0->unk_10;
}
// match: sub_22EF0 @ 0x00022EF0
RwInt32 AIData::sub_22EF0(RwInt32 arg_0)
{
    unk_DD4 = arg_0;
    if (arg_0 == 0)
        unk_F54 = 0;
    sub_22F30(arg_0);
    return 1;
}
// match: sub_22F30 @ 0x00022F30
void AIData::sub_22F30(RwInt32 arg_0)
{
    unk_136C = arg_0;
    if (arg_0 == 0)
        sub_23D90(&unk_1324);
}
// match: sub_22F70 @ 0x00022F70
void AIData::sub_22F70()
{
    type_3D3548 *var_4;

    if (unk_F60 != 0)
        sub_F7BA0(this, unk_F60, false);
    unk_534 = 1;
    unk_1398 = 1.0e37f;
    unk_F60 = unk_F5C;
    sub_F7BA0(this, unk_F60, true);
    if (unk_F60->unk_04 == 0x11) {
        var_4 = sub_16A380(unk_F60);
        if (var_4 != 0)
            unk_568->vf_008()->sub_13F4D0(var_4);
    }
    unk_F54 = 0;
}
// match: sub_23050 @ 0x00023050
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_14D180 *AIData::sub_23050(type_154C0_12F4 *arg_0)
{
    type_14D180 *var_4;
    type_3DBC78 *v8;
    type_3D3548 *varC;

    var_4 = 0;
    v8 = static_cast<type_3DBC78 *>(arg_0->unk_08.sub_D4910());
    if (v8 != 0) {
        var_4 = v8->sub_155340(arg_0);
        varC = var_4->unk_10.sub_D4910();
        if (((var_4->unk_00 >> 2) & 1) != 0 && varC != 0) {
            if (varC == unk_568)
                var_4->unk_00 |= 4;
            else
                var_4 = 0;
        } else {
            var_4->unk_00 |= 4;
            var_4->unk_10.sub_D48D0(unk_568);
        }
    }
    return var_4;
}
// match: sub_23100 @ 0x00023100
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_14D180 *AIData::sub_23100(type_154C0_12F4 *arg_0)
{
    type_14D180 *var_4;
    type_3DBC78 *v8;
    type_3D3548 *varC;

    var_4 = 0;
    v8 = static_cast<type_3DBC78 *>(arg_0->unk_08.sub_D4910());
    if (v8 != 0) {
        var_4 = v8->sub_155340(arg_0);
        varC = var_4->unk_10.sub_D4910();
        if (((var_4->unk_00 >> 2) & 1) != 0 && varC != 0) {
            if (varC == unk_568) {
                var_4->unk_00 &= ~4;
                var_4->unk_10.sub_D48D0(0);
            } else {
                var_4 = 0;
            }
        } else {
            var_4->unk_00 &= ~4;
            var_4->unk_10.sub_D48D0(0);
        }
    }
    return var_4;
}
// match: sub_231B0 @ 0x000231B0
void AIData::sub_231B0()
{
    sub_23100(&unk_12F4);
    sub_23DF0(&unk_130C, &unk_12F4);
    sub_23DF0(&unk_12F4, &unk_133C);
    sub_23050(&unk_12F4);
    sub_23D90(&unk_133C);
}
// match: sub_23230 @ 0x00023230
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_23230()
{
    type_154C0_12F4 *var_4;
    type_3DBC78 *v8;
    type_14D180 *varC;

    var_4 = sub_23BE0();
    if (var_4 != 0) {
        v8 = static_cast<type_3DBC78 *>(var_4->unk_08.sub_D4910());
        if (v8 != 0) {
            varC = v8->sub_155340(var_4);
            if (varC != 0 && (varC->unk_00 & 1) != 0 && ((varC->unk_00 >> 1) & 1) != 0
                    && ((varC->unk_00 >> 2) & 1) == 0) {
                sub_23760();
                sub_22EF0(0);
                sub_6B5F0("VehicleCoverPointFound", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            }
        }
    }
}
// match: sub_232F0 @ 0x000232F0
type_3D3548 *AIData::sub_232F0()
{
    type_3D3548 *var_4;

    var_4 = unk_12F4.unk_08.sub_D4910();
    return var_4;
}
// match: sub_23320 @ 0x00023320
void AIData::sub_23320()
{
    if (unk_F54 != 0 && ((unk_F54->unk_00 >> 2) & 1) == 0 && sub_25DD0(unk_F54, 0) != 0) {
        sub_23670();
        sub_22EF0(0);
        sub_6B5F0("DefendAreaCoverPointFound", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
}
// match: sub_233B0 @ 0x000233B0
RwInt32 AIData::sub_233B0()
{
    RwInt32 var_4;

    var_4 = 0;
    if (unk_F54 != 0 && unk_F5C != 0 && unk_F54 == unk_F5C) {
        if (((unk_F5C->unk_00 >> 2) & 1) == 0) {
            if (sub_25DD0(unk_F5C, 0) != 0) {
                if (sub_F7BA0(this, unk_F5C, true) != 0)
                    var_4 = 1;
                else
                    sub_6B060(unk_568->vf_098()->sub_71340(),
                              "Occupation of selected defendarea coverpoint failed!", 0);
            } else {
                sub_6B060(unk_568->vf_098()->sub_71340(),
                          "Could not occupy defendarea coverpoint selected b/c it is invalid!", 0);
            }
        } else {
            sub_6B060(unk_568->vf_098()->sub_71340(),
                      "Could not occupy defendarea coverpoint selected b/c it is already occupied by someone else", 0);
        }
    } else {
        sub_6B060(unk_568->vf_098()->sub_71340(),
                  "Could not occupy defendarea coverpoint selected b/c either it is not selected or does not match with coverpoint found", 0);
    }
    return var_4;
}
// match: sub_23530 @ 0x00023530
void AIData::sub_23530(type_F8350 *arg_0)
{
    unk_F54 = arg_0;
}
// match: sub_23550 @ 0x00023550
void AIData::sub_23550(RwInt32 arg_0)
{
    if (arg_0 == 0)
        sub_23DF0(&unk_1324, &unk_1354);
    else
        sub_23D90(&unk_1324);
}
// match: sub_235A0 @ 0x000235A0
void AIData::sub_235A0()
{
    type_3D3548 *var_4;

    if (unk_F60 != 0)
        sub_F7BA0(this, unk_F60, false);
    unk_1398 = 1.0e37f;
    unk_F60 = unk_F64;
    sub_F7BA0(this, unk_F60, true);
    if (unk_F60->unk_04 == 0x11) {
        var_4 = sub_16A380(unk_F60);
        if (var_4 != 0)
            unk_568->vf_008()->sub_13F4D0(var_4);
    }
    unk_F64 = 0;
}
// match: sub_23670 @ 0x00023670
void AIData::sub_23670()
{
    type_3D3548 *var_4;

    unk_1398 = 1.0e37f;
    unk_F5C = unk_F54;
    if (unk_F5C->unk_04 == 0x11) {
        var_4 = sub_16A380(unk_F5C);
        if (var_4 != 0)
            unk_568->vf_008()->sub_13F4D0(var_4);
    }
}
// match: sub_236F0 @ 0x000236F0
void AIData::sub_236F0(type_F8350 *arg_0)
{
    type_3D3548 *var_4;

    unk_F5C = arg_0;
    if (unk_F5C->unk_04 == 0x11) {
        var_4 = sub_16A380(unk_F5C);
        if (var_4 != 0)
            unk_568->vf_008()->sub_13F4D0(var_4);
    }
}
// match: sub_23760 @ 0x00023760
void AIData::sub_23760()
{
    sub_23DF0(&unk_133C, &unk_1324);
}
// match: sub_23790 @ 0x00023790
void AIData::sub_23790()
{
    if (unk_F60 != 0) {
        sub_F7BA0(this, unk_F60, false);
        unk_F58 = unk_F60;
        if (unk_F60->unk_04 == 0x11)
            unk_1398 = 120.0f;
        else if (unk_F60->unk_04 == 0x0E)
            unk_1398 = 0.0f;
        else if (unk_F60->unk_04 == 0x13)
            unk_1398 = 21600.0f;
        else
            unk_1398 = 480.0f;
    }
    unk_F60 = 0;
    unk_528 = 0;
}
// match: sub_23860 @ 0x00023860
void AIData::sub_23860()
{
    sub_23100(&unk_12F4);
    sub_23DF0(&unk_130C, &unk_12F4);
    sub_23D90(&unk_12F4);
}
// match: sub_238B0 @ 0x000238B0
void AIData::sub_238B0()
{
    if (unk_F5C != 0)
        sub_F7BA0(this, unk_F5C, false);
}
// match: sub_238E0 @ 0x000238E0
RwBool AIData::sub_238E0(type_3D3548 *arg_0)
{
    RwBool var_4;

    var_4 = 0;
    if ((unk_578 == 6 || unk_578 == 0x26 || unk_578 == 0x2A) && unk_F60 != 0)
        var_4 = 1;
    return var_4;
}
// match: sub_23930 @ 0x00023930
RwBool AIData::sub_23930()
{
    RwBool var_4;

    var_4 = 0;
    if ((unk_578 == 5 || unk_578 == 0x2B || unk_578 == 0x2C) && unk_F60 != 0)
        var_4 = 1;
    return var_4;
}
// match: sub_23980 @ 0x00023980
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_14D180 *AIData::sub_23980()
{
    type_14D180 *var_4;
    type_3DBC78 *v8;
    type_14D180 *varC;

    var_4 = 0;
    if (unk_578 == 0x23 || unk_578 == 0x24 || unk_578 == 0x25) {
        v8 = static_cast<type_3DBC78 *>(unk_12F4.unk_08.sub_D4910());
        if (v8 != 0) {
            varC = v8->sub_155340(&unk_12F4);
            if (varC != 0 && (varC->unk_00 & 1) != 0 && ((varC->unk_00 >> 1) & 1) != 0)
                var_4 = varC;
        }
    }
    return var_4;
}
// match: sub_23A10 @ 0x00023A10
RwInt32 AIData::sub_23A10(type_F8350 *arg_0)
{
    if (arg_0->unk_04 == 7 || arg_0->unk_04 == 8 || arg_0->unk_04 == 0xE)
        return 0;
    if (unk_568->vf_008() != 0 && unk_568->vf_008()->vf_160() == 3) {
        if (((arg_0->unk_00 >> 6) & 1) != 0)
            return 0;
        if (arg_0->unk_04 == 0xC || arg_0->unk_04 == 0xD || arg_0->unk_04 == 0x13)
            return 1;
        if (((arg_0->unk_00 >> 8) & 1) != 0) {
            if (arg_0->unk_04 == 5 || arg_0->unk_04 == 3 || arg_0->unk_04 == 4 || arg_0->unk_04 == 9)
                return 1;
        } else if (((arg_0->unk_00 >> 9) & 1) != 0 && (arg_0->unk_04 == 5 || arg_0->unk_04 == 9)) {
            return 1;
        }
        return 0;
    }
    return 1;
}
// match: sub_23B60 @ 0x00023B60
type_F8350 *AIData::sub_23B60()
{
    type_F8350 *var_4;

    var_4 = unk_F54;
    if (var_4 != 0) {
        if ((unk_49C & 0x2000) != 0 && sub_205E0(&var_4->unk_10, 0.0f) == 0)
            return 0;
        if (sub_26A80(var_4, unk_1374.sub_D4910(), 0, 0) == 0)
            return 0;
    }
    return var_4;
}
// match: sub_23BE0 @ 0x00023BE0
type_154C0_12F4 *AIData::sub_23BE0()
{
    type_154C0_12F4 *var_4;

    var_4 = 0;
    if (sub_279B0(&unk_1324, unk_1374.sub_D4910(), 0) != 0)
        var_4 = &unk_1324;
    return var_4;
}
// match: sub_23C30 @ 0x00023C30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_23C30(RwV3d *arg_0)
{
    type_3CE6D0 *var_4;
    RwUInt32 local_8;

    local_8 = unk_574;
    var_4 = sub_3D3E0(local_8);
    if (var_4 != 0 && var_4->vf_030() == 5)
        *arg_0 = static_cast<type_3CE5E8 *>(var_4)->unk_5AC;
    else if ((unk_1430 != -1) != 0)
        *arg_0 = unk_1438;
    else
        return 0;
    return 1;
}
// match: sub_23CD0 @ 0x00023CD0
RwInt32 AIData::sub_23CD0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    if (unk_DD0 != arg_0) {
        unk_F70.z = 0.0f;
        unk_F70.y = 0.0f;
        unk_F70.x = 0.0f;
        sub_23D90(&unk_1324);
        sub_23D90(&unk_1354);
        if (arg_4 != 0) {
            var_4 = arg_0;
            sub_6B5F0("CoverPointSearchTypeChanged", (type_67620 *)(unk_568->vf_098()), 0, 0, &var_4, 1, true, true);
        }
    }
    unk_DD0 = arg_0;
    return 1;
}
// match: sub_23D90 @ 0x00023D90
void AIData::sub_23D90(type_154C0_12F4 *arg_0)
{
    RwV3d *var_4;

    arg_0->unk_04 = 0;
    arg_0->unk_00 = -1;
    arg_0->unk_08.sub_D48D0(0);
    var_4 = &arg_0->unk_0C;
    var_4->x = 0.0f;
    var_4->y = 0.0f;
    var_4->z = 0.0f;
}
// match: sub_23DF0 @ 0x00023DF0
void AIData::sub_23DF0(type_154C0_12F4 *arg_0, type_154C0_12F4 *arg_4)
{
    arg_0->unk_04 = arg_4->unk_04;
    arg_0->unk_00 = arg_4->unk_00;
    arg_0->unk_08.sub_D48D0(arg_4->unk_08.sub_D4910());
    arg_0->unk_0C = arg_4->unk_0C;
}
// match: sub_23E50 @ 0x00023E50
RwInt32 AIData::sub_23E50(type_154C0_12F4 *arg_0, type_154C0_12F4 *arg_4)
{
    if (arg_0->unk_00 == arg_4->unk_00 && arg_0->unk_04 == arg_4->unk_04
            && arg_0->unk_08.sub_D4910() == arg_4->unk_08.sub_D4910())
        return 1;
    return 0;
}
// match: sub_23EA0 @ 0x00023EA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_23EA0(type_154C0_12F4 *arg_0, type_154C0_12F4 *arg_4)
{
    type_3D3548 *var_4;
    type_3D3548 *v8;
    RwReal stk_C;
    RwV3d stk_18;

    if (arg_0->unk_00 == arg_4->unk_00 && arg_0->unk_04 == arg_4->unk_04) {
        var_4 = arg_0->unk_08.sub_D4910();
        v8 = arg_4->unk_08.sub_D4910();
        if (var_4 == v8) {
            RwV3dSub(&stk_18, &arg_0->unk_0C, &arg_4->unk_0C);
            stk_C = RwV3dDotProduct(&stk_18, &stk_18);
            if (stk_C < 250000.0f)
                return 1;
        }
    }
    return 0;
}
extern RwReal flt_4C0198;
extern const RwReal flt_3D9488;
// match: ?sub_23F60@AIData@@QAEXH@Z @ 0x00023F60
void AIData::sub_23F60(RwInt32 arg_0)
{
    switch (arg_0)
    {
    case 1:
        {
            RwV3d lv_14;
            type_4C00E8 *lv_18;
            RwReal lv_1C;
            RwInt32 lv_20;
            RwReal lv_24;
            RwReal lv_84;
            RwReal lv_88;
            RwInt32 lv_8C;

            sub_23C30(&lv_14);
            lv_18 = &unk_4C00E8;
            lv_1C = 1e37f;
            lv_20 = -1;
            lv_24 = sub_140C90(unk_568->sub_CD550(), &lv_14);
            do
            {
                __m128 lv_40 = _mm_set_ss(lv_24);
                __m128 lv_60 = _mm_sqrt_ss(lv_40);
                _mm_store_ss(&lv_84, lv_60);
            } while (0);
            if (lv_84 - flt_3D9488 < flt_4C0198)
                lv_88 = flt_4C0198 * flt_4C0198;
            else
                lv_88 = (lv_84 - flt_3D9488) * (lv_84 - flt_3D9488);
            for (lv_8C = 0; lv_8C < unk_1048.unk_4C; lv_8C++)
            {
                RwV3d *lv_90 = &lv_18->unk_2C[unk_F80[lv_8C].unk_00]->unk_10;
                RwReal lv_94 = sub_140C90(lv_90, &lv_14);

                if (lv_94 < lv_1C && lv_94 < lv_88)
                {
                    lv_20 = unk_F80[lv_8C].unk_00;
                    lv_1C = lv_94;
                }
            }
            if (lv_20 >= 0)
            {
                unk_1048.unk_38 = lv_20;
                unk_1048.unk_3C = lv_1C;
                unk_1048.unk_34 = lv_18->unk_2C[lv_20];
            }
        }
        break;
    case 0:
    case 2:
        {
            type_4C00E8 *lv_98 = &unk_4C00E8;
            RwReal lv_9C = 1e37f;
            RwInt32 lv_A0 = -1;
            RwInt32 lv_A4;

            for (lv_A4 = 0; lv_A4 < unk_1048.unk_4C; lv_A4++)
            {
                type_F8350 *lv_A8 = lv_98->unk_2C[unk_F80[lv_A4].unk_00];

                if (lv_A8->unk_04 == 0x11)
                    unk_F80[lv_A4].unk_04 *= 0.0001f;
                if (unk_F80[lv_A4].unk_04 < lv_9C)
                {
                    lv_9C = unk_F80[lv_A4].unk_04;
                    lv_A0 = lv_A4;
                }
            }
            if (lv_A0 != -1)
            {
                unk_1048.unk_38 = unk_F80[lv_A0].unk_00;
                unk_1048.unk_3C = lv_9C;
                unk_1048.unk_34 = lv_98->unk_2C[unk_F80[lv_A0].unk_00];
            }
        }
        break;
    }
}
// match: ?sub_242B0@AIData@@QAEHHHMPAM@Z @ 0x000242B0
RwInt32 AIData::sub_242B0(RwInt32 arg_0, RwInt32 arg_4, RwReal arg_8, RwReal *arg_C)
{
    RwV3d lv_10;
    RwInt32 lv_14;
    RwInt32 lv_18;

    if (arg_4 == 1)
        sub_23C30(&lv_10);
    if (*arg_C < 0.0f)
    {
        lv_14 = arg_4;
        *arg_C = 1e37f;
    }
    lv_18 = 0;
    switch (arg_4)
    {
    case 1:
        {
            type_4C00E8 *lv_20 = &unk_4C00E8;
            RwV3d lv_2C = lv_20->unk_2C[unk_1048.unk_20[arg_0].unk_00]->unk_10;
            RwReal lv_30 = sub_140C90(&lv_2C, &lv_10);

            if (lv_30 >= arg_8 && lv_30 <= *arg_C)
            {
                RwReal lv_34 = sub_140C90(unk_568->sub_CD550(), &lv_10);
                RwReal lv_94;
                RwReal lv_98;

                do
                {
                    __m128 lv_50 = _mm_set_ss(lv_34);
                    __m128 lv_70 = _mm_sqrt_ss(lv_50);
                    _mm_store_ss(&lv_94, lv_70);
                } while (0);
                if (lv_94 - flt_3D9488 < flt_4C0198)
                    lv_98 = flt_4C0198 * flt_4C0198;
                else
                    lv_98 = (lv_94 - flt_3D9488) * (lv_94 - flt_3D9488);
                if (lv_30 < lv_98)
                    lv_18 = 1;
            }
            if (lv_18)
                *arg_C = lv_30;
        }
        break;
    default:
        lv_18 = unk_F80[arg_0].unk_04 >= arg_8 && unk_F80[arg_0].unk_04 <= *arg_C;
        if (lv_18)
            *arg_C = unk_F80[arg_0].unk_04;
        break;
    }
    return lv_18;
}
// match: sub_244E0 @ 0x000244E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_244E0(type_F8350 **arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    type_F8350 *stk_5C;
    RwInt32 local_58;
    RwInt32 local_54;
    RwInt32 local_50;
    RwInt32 stk_4C;
    RwReal loc48;
    RwInt32 var_44;
    type_F8350 *ebp_40;
    RwInt32 local_3C;
    RwReal v38;
    type_4C00E8 *v34;
    RwInt32 v30;
    RwInt32 var_2C;
    RwV3d loc28;
    RwReal slot_1C;
    type_3D3548 *local_18;
    RwInt32 local_14;
    RwV3d *local_10;
    RwInt32 fp_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    if (arg_0 != 0)
        *arg_0 = 0;
    lv_8 = 1;
    local_18 = unk_1374.sub_D4910();
    if ((var_4 = unk_49C & 0x2000) != 0)
        local_10 = &unk_13A8;
    else
        local_10 = unk_568->sub_CD550();
    if (get_unk_DD4() != 0) {
        if (unk_F70.x != 0.0f || unk_F70.y != 0.0f || unk_F70.z != 0.0f) {
            if (local_18 == 0 || (local_18 != 0 && local_18 == unk_F7C.sub_D4910())) {
                loc28.x = unk_F70.x - local_10->x;
                loc28.y = 0.0f;
                loc28.z = unk_F70.z - local_10->z;
                slot_1C = RwV3dDotProduct(&loc28, &loc28);
                if (slot_1C < 360000.0f)
                    lv_8 = 0;
            }
        }
    } else {
        lv_8 = 0;
    }
    if (lv_8 != 0) {
        dword_438DDC = 1;
        unk_1048.unk_04 = *local_10;
        if (var_4 != 0)
            unk_1048.unk_10 = get_unk_13B4();
        else
            unk_1048.unk_10 = unk_F68;
        unk_1048.unk_00 = unk_568;
        unk_1048.unk_18 = sub_F7E80(arg_4);
        unk_1048.unk_1C = 1;
        unk_1048.unk_20 = unk_F80;
        unk_1048.unk_24 = 25;
        sub_F8970(&unk_1048, 1, 0);
        if (var_4 != 0) {
            unk_F70 = *local_10;
            unk_F68 = 2500.0f;
        } else if (unk_1048.unk_4C != 0) {
            unk_F68 = 2500.0f;
            unk_F70 = *local_10;
        } else {
            unk_F68 += 1000.0f;
            if (unk_F68 > 7500.0f) {
                unk_F68 = 7500.0f;
                unk_F70 = *local_10;
            } else {
                unk_F70.z = 0.0f;
                unk_F70.y = 0.0f;
                unk_F70.x = 0.0f;
            }
        }
        unk_F7C.sub_D48D0(local_18);
        sub_23F60(arg_8);
        for (var_2C = 0; var_2C < unk_1048.unk_4C; var_2C++) {
            unk_F80[var_2C].unk_02 = 0;
            if (unk_F80[var_2C].unk_00 == unk_1048.unk_38)
                unk_F80[var_2C].unk_02 = 1;
        }
    }
    local_14 = 0;
    fp_C = 0;
    sub_24BA0(arg_4, arg_8, arg_C, &fp_C);
    if (get_unk_DD4() != 0 && unk_1048.unk_4C != 0 && fp_C == 0) {
        while (1) {
            ebp_40 = unk_1048.unk_34;
            var_44 = 1;
            if (var_4 != 0 && sub_205E0(&ebp_40->unk_10, 0.0f) == 0)
                var_44 = 0;
            if (var_44 != 0 && ebp_40 != unk_F58 && ((ebp_40->unk_00 >> 2) & 1) == 0
                    && sub_26A80(ebp_40, local_18, 0, 0) != 0 && ebp_40 != unk_F60
                    && sub_25890(ebp_40) != 0) {
                if (ebp_40 == unk_F54 && lv_8 == 0) {
                    if (arg_0 != 0)
                        *arg_0 = unk_F54;
                    local_14 = 1;
                } else {
                    local_50 = 0;
                    unk_F54 = 0;
                    if (unk_DD8 != 0) {
                        fp_C = 1;
                        local_50 = sub_29630(ebp_40, unk_1048.unk_38, 4, 0, arg_C);
                    }
                    if (local_50 == 1) {
                        if (arg_0 != 0)
                            *arg_0 = ebp_40;
                        unk_F54 = ebp_40;
                        local_14 = 1;
                    }
                }
            }
            if (local_14 != 0)
                return local_14;
            local_3C = unk_1048.unk_38;
            v38 = unk_1048.unk_3C;
            v34 = &unk_4C00E8;
            stk_4C = 0;
            v30 = -1;
            loc48 = -1.0f;
            for (local_54 = 0; local_54 < unk_1048.unk_4C; local_54++) {
                if (unk_F80[local_54].unk_02 == 0 && unk_F80[local_54].unk_00 != local_3C) {
                    local_58 = unk_F80[local_54].unk_00;
                    stk_5C = v34->unk_2C[local_58];
                    if (var_4 != 0 && sub_205E0(&stk_5C->unk_10, 0.0f) == 0)
                        continue;
                    if (stk_5C == unk_F60)
                        continue;
                    if (sub_242B0(local_54, arg_8, v38, &loc48) != 0 && sub_25890(stk_5C) != 0) {
                        stk_4C = local_58;
                        v30 = local_54;
                    }
                }
            }
            if (v30 == -1) {
                unk_F70.z = 0.0f;
                unk_F70.y = 0.0f;
                unk_F70.x = 0.0f;
                return 0;
            }
            unk_1048.unk_38 = stk_4C;
            unk_1048.unk_3C = loc48;
            unk_1048.unk_34 = v34->unk_2C[stk_4C];
            unk_F80[v30].unk_02 = 1;
            if (fp_C != 0)
                return 0;
        }
    }
    return local_14;
}
// match: sub_24BA0 @ 0x00024BA0
// match: __ehhandler$?sub_24BA0@AIData@@QAEHHHHPAH@Z-8 @ 0x002FF520
// match: __ehhandler$?sub_24BA0@AIData@@QAEHHHHPAH@Z @ 0x002FF528
// symbol: ??1type_154C0_12F4@@QAE@XZ = 0x001E41C0
RwInt32 AIData::sub_24BA0(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 *arg_C)
{
    RwInt32 local_10;
    type_14D180 *stk_14;
    RwReal lcl_18;
    RwInt32 fp_1C;

    fp_1C = 0;
    if (unk_136C == 0)
        return fp_1C;
    lcl_18 = 1.0e37f;
    stk_14 = 0;
    type_154C0_12F4 lv_34;
    local_10 = unk_49C & 0x2000;
    if ((arg_4 == 0 || arg_4 == 2) && (unk_568->unk_2C & 0x40080) == 0) { // not an address: entity kind bits
        type_3D3548 *var_38;
        RwV3d *var_3C;

        var_38 = 0;
        var_3C = unk_568->sub_CD550();
        if (((unk_49C >> 22) & 1) != 0) {
            var_38 = unk_1370.sub_D4910();
        } else {
            RwInt32 var_40;

            var_40 = unk_568->unk_2C & 7;
            if (var_40 == 1)
                var_38 = dword_4B8600[1].unk_00;
            else if (var_40 == 2)
                var_38 = dword_4B8600[0].unk_00;
        }
        while (var_38 != 0) {
            if ((var_38->unk_2C & 0x40080) != 0) { // not an address: entity kind bits
                type_3DBC78 *var_44;

                var_44 = (type_3DBC78 *)var_38;
                if (var_44->vf_1DC() != 0) {
                    RwReal var_48;

                    var_48 = sub_140C90(var_38->sub_CD550(), var_3C);
                    if (var_48 < 25000000.0f) {
                        type_14D180 *var_4C;
                        RwInt32 var_50;

                        var_4C = var_44->unk_263C;
                        for (var_50 = 0; var_50 < 12; var_50++) {
                            type_14D180 *var_54;

                            var_54 = &var_4C[var_50];
                            if ((var_54->unk_00 & 3) == 3 && (var_54->unk_00 & 4) == 0) {
                                if (local_10 != 0 && sub_205E0(&var_54->unk_14, 0.0f) == 0)
                                    continue;
                                var_48 = sub_140C90(&var_54->unk_14, var_3C);
                                if (var_48 < lcl_18) {
                                    lcl_18 = var_48;
                                    stk_14 = var_54;
                                    lv_34.unk_00 = var_54->unk_04;
                                    lv_34.unk_04 = var_54->unk_08;
                                    lv_34.unk_08.sub_D48D0(var_44);
                                    lv_34.unk_0C = var_54->unk_14;
                                }
                            }
                        }
                    }
                }
            }
            if (((unk_49C >> 22) & 1) == 0)
                var_38 = var_38->unk_10;
            else
                var_38 = 0;
        }
    }
    if (stk_14 != 0 && sub_23EA0(&lv_34, &unk_1324) == 0 && sub_23EA0(&lv_34, &unk_1354) == 0
            && sub_23E50(&lv_34, &unk_130C) == 0
            && (get_unk_DD4() == 0 || lcl_18 < unk_1048.unk_3C)) {
        RwInt32 var_58;

        var_58 = 0;
        if (unk_DD8 != 0) {
            sub_23D90(&unk_1324);
            sub_23DF0(&unk_1354, &lv_34);
            *arg_C = 1;
            var_58 = sub_29780(&lv_34, 0, arg_8);
        }
        if (var_58 == 1) {
            sub_23DF0(&unk_1324, &lv_34);
            fp_1C = 1;
        }
    }
    return fp_1C;
}
// match: sub_24F30 @ 0x00024F30
RwInt32 AIData::sub_24F30(RwV3d *arg_0, type_3D3548 **arg_4, RwReal *arg_8, RwV3d *arg_C,
                          RwInt32 *arg_10)
{
    type_3D3548 *var_4;

    var_4 = unk_13E8.sub_D4910();
    if (var_4 != 0) {
        *arg_4 = var_4;
        *arg_8 = unk_F6C;
        if (unk_1404 == 3)
            sub_20B30(arg_0, var_4);
        else if (unk_1404 == 4 && sub_212A0(var_4) == 0)
            sub_20B30(arg_0, var_4);
        else
            *arg_0 = unk_13F8;
        *arg_C = unk_13EC;
        *arg_10 = unk_1404;
    } else if ((unk_49C & 0x2000) != 0) {
        *arg_4 = unk_13C0.sub_D4910();
        switch (unk_13DC) {
        case 0:
        case 1:
        case 2:
        case 4:
            *arg_0 = unk_13D0;
            break;
        default:
            *arg_0 = unk_13A8;
            break;
        }
        *arg_8 = unk_13B4;
        *arg_C = unk_13C4;
        *arg_10 = unk_13DC;
    } else {
        return 0;
    }
    return 1;
}
// match: sub_250D0 @ 0x000250D0
void AIData::sub_250D0(RwMatrix *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C, RwInt32 arg_10)
{
    RwV3d var_C;

    if (arg_10 != 3 && arg_C != 0 && RwV3dDotProduct(arg_C, arg_C) > 0.0f) {
        var_C = *arg_C;
    } else {
        RwV3dSub(&var_C, arg_4, arg_8);
        var_C.y = 0.0f;
    }
    sub_140CE0(arg_0, arg_4, &var_C);
}
// match: ?sub_25180@AIData@@QAEHPAPAUtype_F8350@@HHH@Z @ 0x00025180
RwInt32 AIData::sub_25180(type_F8350 **arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RwInt32 lv_8;
    RwV3d lv_14;
    RwV3d lv_20;
    RwInt32 lv_24;
    RwInt32 lv_28;
    type_3D3548 *lv_2C;
    RwReal lv_30;
    RwInt32 lv_34;
    RwV3d lv_40;
    RwInt32 lv_74;

    if (arg_0 != 0)
        *arg_0 = 0;
    lv_8 = 0;
    lv_14.x = 0.0f;
    lv_14.y = 0.0f;
    lv_14.z = 0.0f;
    lv_20.x = 0.0f;
    lv_20.y = 0.0f;
    lv_20.z = 0.0f;
    lv_24 = 0;
    lv_28 = 0;
    lv_2C = 0;
    lv_30 = 0.0f;
    lv_34 = -1;
    lv_40.x = 0.0f;
    lv_40.y = 0.0f;
    lv_40.z = 0.0f;
    if (get_unk_DD4() != 0 && sub_24F30(&lv_14, &lv_2C, &lv_30, &lv_40, &lv_34) != 0) {
        lv_24 = 1;
        lv_20 = lv_14;
        if (lv_2C != 0) {
            RwV3d *lv_48 = lv_2C->sub_CD550();
            RwV3d lv_54;

            lv_2C->vf_108(&lv_54);
            RwReal lv_58 = lv_54.y - lv_48->y;

            lv_14.y += lv_58;
            if (lv_2C->unk_2C & 0x20020) // not an address: flags
                lv_14.y -= 50.0f;
        }
        lv_28 = 1;
        if (unk_F70.x != 0.0f || unk_F70.y != 0.0f || unk_F70.z != 0.0f) {
            RwV3d lv_64;
            RwReal lv_68;

            lv_64.x = unk_F70.x - lv_14.x;
            lv_64.y = 0.0f;
            lv_64.z = unk_F70.z - lv_14.z;
            lv_68 = RwV3dDotProduct(&lv_64, &lv_64);
            if (lv_68 < 360000.0f)
                lv_28 = 0;
        }
        if (lv_28 != 0) {
            type_3D3548 *lv_6C = unk_1374.sub_D4910();
            RwInt32 lv_70;

            dword_438DDC = 1;
            unk_1048.unk_04 = lv_14;
            unk_1048.unk_10 = lv_30;
            unk_1048.unk_00 = unk_568;
            unk_1048.unk_18 = sub_F7E80(arg_4);
            unk_1048.unk_1C = 1;
            unk_1048.unk_20 = unk_F80;
            unk_1048.unk_24 = 25;
            sub_F8970(&unk_1048, 1, 0);
            unk_F70 = lv_14;
            unk_F7C.sub_D48D0(lv_6C);
            for (lv_70 = 0; lv_70 < unk_1048.unk_4C; lv_70++) {
                unk_F80[lv_70].unk_02 = 0;
                if (unk_F80[lv_70].unk_00 == unk_1048.unk_38)
                    unk_F80[lv_70].unk_02 = 1;
            }
        }
    }
    lv_74 = 0;
    sub_24BA0(arg_4, arg_8, arg_C, &lv_74);
    if (lv_24 != 0 && unk_1048.unk_4C != 0 && lv_74 == 0) {
        RwV3d *lv_78 = unk_568->sub_CD550();
        RwMatrix lv_C0;

        sub_250D0(&lv_C0, &lv_20, lv_78, &lv_40, lv_34);
        while (1) {
            type_4C00E8 *lv_C4 = &unk_4C00E8;
            type_F8350 *lv_C8 = unk_1048.unk_34;

            if (((lv_C8->unk_00 >> 2) & 1) == 0 && lv_C8 != unk_F60
                    && sub_26000(lv_C8, &lv_C0, &lv_20, (RwInt32)lv_78, lv_30, lv_34, 0) != 0
                    && sub_25B60(lv_C8, &lv_C0, lv_34, 1) != 0) {
                if (lv_C8 == unk_F54 && lv_28 == 0) {
                    if (arg_0 != 0)
                        *arg_0 = unk_F54;
                    lv_8 = 1;
                } else {
                    RwInt32 lv_CC = 0;

                    unk_F54 = 0;
                    if (unk_DD8 != 0) {
                        lv_74 = 1;
                        lv_CC = sub_29630(lv_C8, unk_1048.unk_38, 6, 0, arg_C);
                    }
                    if (lv_CC == 1) {
                        if (arg_0 != 0)
                            *arg_0 = lv_C8;
                        unk_F54 = lv_C8;
                        lv_8 = 1;
                    }
                }
            }
            if (lv_8 != 0)
                return lv_8;
            RwInt32 lv_D0 = unk_1048.unk_38;
            RwReal lv_D4 = unk_1048.unk_3C;
            RwInt32 lv_D8 = 0;
            RwInt32 lv_DC = -1;
            RwReal lv_E0 = -1.0f;
            RwInt32 lv_E4;

            for (lv_E4 = 0; lv_E4 < unk_1048.unk_4C; lv_E4++) {
                if (unk_F80[lv_E4].unk_02 == 0 && unk_F80[lv_E4].unk_00 != lv_D0) {
                    RwInt32 lv_E8 = unk_F80[lv_E4].unk_00;
                    type_F8350 *lv_EC = lv_C4->unk_2C[lv_E8];

                    if (lv_EC != unk_F60
                            && sub_26000(lv_EC, &lv_C0, &lv_20, (RwInt32)lv_78, lv_30, lv_34, 0) != 0
                            && sub_25B60(lv_EC, &lv_C0, lv_34, 1) != 0
                            && sub_242B0(lv_E4, arg_8, lv_D4, &lv_E0) != 0) {
                        lv_D8 = lv_E8;
                        lv_DC = lv_E4;
                    }
                }
            }
            if (lv_DC == -1) {
                unk_F70.z = 0.0f;
                unk_F70.y = 0.0f;
                unk_F70.x = 0.0f;
                return 0;
            }
            unk_1048.unk_38 = lv_D8;
            unk_1048.unk_3C = lv_E0;
            unk_1048.unk_34 = lv_C4->unk_2C[lv_D8];
            unk_F80[lv_DC].unk_02 = 1;
            if (lv_74 != 0)
                return 0;
        }
    }
    return lv_8;
}
// match: sub_25890 @ 0x00025890
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_25890(type_F8350 *arg_0)
{
    RwReal var_4;
    RwReal loc8;
    RwV3d local_14;
    RwV3d local_20;
    RwV3d lcl_2C;
    type_3D3548 *var_30;

    if (unk_F60 == 0)
        return 1;
    var_30 = unk_1374.sub_D4910();
    if (var_30 == 0)
        return 0;
    RwV3dSub(&local_20, var_30->sub_CD550(), &arg_0->unk_10);
    RwV3dSub(&local_14, &arg_0->unk_10, &unk_F60->unk_10);
    if (RwV3dDotProduct(&local_20, &local_14) < 0.0f)
        return 0;
    RwV3dSub(&lcl_2C, var_30->sub_CD550(), &unk_F60->unk_10);
    var_4 = RwV3dDotProduct(&local_20, &local_20);
    loc8 = RwV3dDotProduct(&lcl_2C, &lcl_2C);
    if (arg_0->unk_04 == 0x11)
        var_4 *= 0.0001f;
    if (unk_F60->unk_04 == 0x11)
        loc8 *= 0.0001f;
    if (var_4 < loc8)
        return 1;
    return 0;
}
// match: ?sub_25A50@AIData@@QAEHXZ @ 0x00025A50
RwInt32 AIData::sub_25A50()
{
    RwInt32 lv_8 = 0;

    if (unk_F5C != 0 && unk_F60 != 0 && unk_F5C != unk_F60) {
        type_3D3548 *lv_C = 0;
        RwReal lv_10 = 0.0f;
        RwInt32 lv_14 = -1;
        RwV3d lv_20;
        RwV3d lv_2C;

        lv_20.x = 0.0f;
        lv_20.y = 0.0f;
        lv_20.z = 0.0f;
        if (sub_24F30(&lv_2C, &lv_C, &lv_10, &lv_20, &lv_14) != 0) {
            RwV3d *lv_30 = unk_568->sub_CD550();
            RwMatrix lv_70;

            sub_250D0(&lv_70, &lv_2C, lv_30, &lv_20, lv_14);
            if (sub_25B60(unk_F5C, &lv_70, lv_14, 0) != 0)
                lv_8 = 1;
        }
    }
    return lv_8;
}
// match: sub_25B60 @ 0x00025B60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_25B60(type_F8350 *arg_0, RwMatrix *arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RwV3d var_C;
    RwReal local_10;
    RwReal stk_14;
    RwReal lcl_18;
    RwReal fp_1C;
    RwV3d fp_28;

    if (unk_F60 == 0)
        return 1;
    if (arg_0 == unk_F60)
        return 0;
    RwV3dSub(&fp_28, &arg_0->unk_10, &arg_4->pos);
    stk_14 = RwV3dDotProduct(&fp_28, &fp_28);
    fp_1C = RwV3dDotProduct(&arg_4->at, &fp_28);
    RwV3dSub(&var_C, &unk_F60->unk_10, &arg_4->pos);
    local_10 = RwV3dDotProduct(&var_C, &var_C);
    lcl_18 = RwV3dDotProduct(&arg_4->at, &var_C);
    if (arg_8 == 0 || arg_8 == 1) {
        if (lcl_18 > 0.0f && fp_1C > 0.0f) {
            if (stk_14 > local_10)
                return 1;
        } else if (fp_1C > 0.0f && lcl_18 < 0.0f) {
            return 1;
        } else if (arg_8 == 1 && fp_1C < 0.0f && lcl_18 < 0.0f && stk_14 < local_10) {
            return 1;
        }
        return 0;
    } else if (arg_8 == 2) {
        if (fp_1C < 0.0f && lcl_18 < 0.0f && stk_14 < local_10)
            return 1;
        return 0;
    } else if (arg_8 == 3) {
        if (stk_14 < local_10)
            return 1;
        return 0;
    } else if (arg_8 == 4) {
        if (stk_14 < local_10)
            return 1;
        return 0;
    }
    if (arg_C != 0)
        return 1;
    return 0;
}
// match: ?sub_25DD0@AIData@@QAEHPAUtype_F8350@@PAH@Z @ 0x00025DD0
RwInt32 AIData::sub_25DD0(type_F8350 *arg_0, RwInt32 *arg_4)
{
    type_3D3548 *lv_8 = 0;
    RwReal lv_C = 0.0f;
    RwInt32 lv_10 = -1;
    RwV3d lv_1C;
    RwV3d lv_28;
    RwV3d *lv_2C;
    RwMatrix lv_70;

    lv_1C.x = 0.0f;
    lv_1C.y = 0.0f;
    lv_1C.z = 0.0f;
    if (sub_24F30(&lv_28, &lv_8, &lv_C, &lv_1C, &lv_10) == 0)
        return 0;
    lv_2C = unk_568->sub_CD550();
    sub_250D0(&lv_70, &lv_28, lv_2C, &lv_1C, lv_10);
    if (sub_26000(arg_0, &lv_70, &lv_28, (RwInt32)lv_2C, lv_C, lv_10, arg_4) != 0)
        return 1;
    return 0;
}
// match: sub_25EB0 @ 0x00025EB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_25EB0(type_F8350 *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwV3d *arg_C)
{
    RwInt32 var_4;
    RwReal v8;
    RwInt32 stk_C;
    RwReal var_10;

    stk_C = 0;
    v8 = RwV3dDotProduct(&arg_4->at, arg_8);
    var_4 = arg_0->unk_04;
    switch (var_4) {
    case 14:
        stk_C = 1;
        break;
    case 5:
    case 9:
    case 11:
    case 12:
    case 13:
    case 17:
    case 19:
        if (v8 < 0.4f && v8 > -0.4f)
            stk_C = 1;
        break;
    }
    if (stk_C == 0 && v8 >= flt_3CDE20) {
        var_10 = RwV3dDotProduct(&arg_4->right, arg_C);
        if (var_10 >= 0.0f && var_4 == 3)
            stk_C = 0;
        else if (var_10 < 0.0f && var_4 == 4)
            stk_C = 0;
        else
            stk_C = 1;
    }
    return stk_C;
}
// Places the owner at the cover node arg_0: its frame, taken off its
// parent, set to the node's cover orientation (sub_22C80's) at the node's
// point, with the owner's three motion vectors cleared.
// The two sides' common bits: an inline with no address, named for what it
// does. Evidence: sub_26000 ands the two side values in the order an
// inline's arguments are evaluated (right to left, into the first's register).
inline RwInt32 and_sides(RwInt32 arg_0, RwInt32 arg_4)
{
    return arg_0 & arg_4;
}
// match: sub_26000 @ 0x00026000
// The kind is read into a local of each block that tests it.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_26000(type_F8350 *arg_0, RwMatrix *arg_4, RwV3d *arg_8, RwInt32 arg_C,
                          RwReal arg_10, RwInt32 arg_14, RwInt32 *arg_18)
{
    RwReal var_84;
    RwV3d var_80;
    RwV3d v74;
    RwV3d lv_68;
    RwV3d r5C;
    RwV3d ebp_50;
    type_3D3548 *v44;
    RwV3d stk_40;
    type_3D3548 *local_34;
    RwReal local_30;
    RwV3d stk_2C;
    RwReal var_20;
    RwReal l1C;
    RwReal m_18;
    RwV3d ebp_14;
    RwReal bp_8;
    RwReal bp_4;

    if (arg_18 != 0)
        *arg_18 = 0;
    if (sub_23A10(arg_0) == 0 && arg_0->unk_04 != 0x0E)
        return 0;
    local_34 = unk_1374.sub_D4910();
    if (local_34 != 0 && sub_238E0(local_34) == 0 && sub_23930() == 0) {
        if (sub_26A80(arg_0, local_34, 0, 0) == 0)
            return 0;
    } else {
        v44 = sub_1745A0(0);
        if (v44 != 0 && and_sides(v44->unk_2C & 7, unk_568->unk_2C & 7) != 0
                && (sub_238E0(0) == 0 || unk_F60 != arg_0)) {
            RwV3dSub(&ebp_50, v44->sub_CD550(), &arg_0->unk_10);
            ebp_50.y -= v44->unk_48;
            if (ebp_50.y <= flt_4275E4 && -flt_4275E8 <= ebp_50.y) {
                ebp_50.y = 0.0f;
                if (RwV3dDotProduct(&ebp_50, &ebp_50) < flt_4275E8) {
                    if (arg_18 != 0)
                        *arg_18 = 1;
                    return 0;
                }
            }
        }
    }
    local_30 = arg_10 / 10.0f;
    if (local_30 < 250.0f)
        local_30 = 250.0f;
    l1C = local_30 + arg_8->y;
    m_18 = arg_8->y - local_30;
    if (arg_0->unk_10.y < m_18 || arg_0->unk_10.y > l1C)
        return 0;
    RwV3dSub(&stk_40, arg_8, &arg_0->unk_10);
    bp_4 = RwV3dDotProduct(&stk_40, &stk_40);
    if (arg_10 * arg_10 < bp_4)
        return 0;
    RwV3dSub(&stk_2C, &arg_0->unk_10, &arg_4->pos);
    stk_2C.y = 0.0f;
    RwV3dNormalize(&stk_2C, &stk_2C);
    var_84 = 2.0f / (arg_0->unk_1C.real * arg_0->unk_1C.real
            + RwV3dDotProduct(&arg_0->unk_1C.imag, &arg_0->unk_1C.imag));
    RwV3dScale(&var_80, &arg_0->unk_1C.imag, var_84);
    lv_68.x = var_80.x * arg_0->unk_1C.real;
    lv_68.y = var_80.y * arg_0->unk_1C.real;
    r5C.x = var_80.x * arg_0->unk_1C.imag.x;
    r5C.y = var_80.y * arg_0->unk_1C.imag.y;
    v74.x = var_80.z * arg_0->unk_1C.imag.y;
    ebp_14.x = (v74.y = var_80.x * arg_0->unk_1C.imag.z) + lv_68.y;
    ebp_14.y = v74.x - lv_68.x;
    ebp_14.z = 1.0f - (r5C.x + r5C.y);
    bp_8 = RwV3dDotProduct(&arg_4->at, &stk_2C);
    if (arg_14 == 0 || arg_14 == 1 || arg_14 == 2) {
        if (bp_8 >= flt_3CDE1C && arg_14 != 2)
            return sub_25EB0(arg_0, arg_4, &ebp_14, &stk_2C);
        if ((arg_14 == 1 || arg_14 == 2) && bp_8 <= flt_3CDE1C)
            return sub_25EB0(arg_0, arg_4, &ebp_14, &stk_2C);
    } else if (arg_14 == 3) {
        if (bp_8 >= flt_3CDE18) {
            var_20 = RwV3dDotProduct(&arg_4->at, &ebp_14);
            if (var_20 > 0.0f)
                return 1;
            RwInt32 kind = arg_0->unk_04;

            if (kind == 0x0E && var_20 < flt_3CDE20 && -flt_3CDE20 < var_20)
                return 1;
        } else if (bp_8 < flt_3CDE18 && -flt_3CDE18 < bp_8) {
            RwReal var_8C = RwV3dDotProduct(&arg_4->right, &stk_2C);

            if (var_8C >= flt_3CDE24) {
                var_20 = RwV3dDotProduct(&arg_4->right, &ebp_14);
                if (var_20 > 0.0f)
                    return 1;
            } else if (-flt_3CDE24 >= var_8C) {
                var_20 = RwV3dDotProduct(&arg_4->right, &ebp_14);
                if (var_20 < 0.0f)
                    return 1;
            }
        } else if (-flt_3CDE18 >= bp_8) {
            var_20 = RwV3dDotProduct(&arg_4->at, &ebp_14);
            if (var_20 < 0.0f)
                return 1;
            RwInt32 kind = arg_0->unk_04;

            if (kind == 0x0E && var_20 < flt_3CDE20 && -flt_3CDE20 < var_20)
                return 1;
        }
    } else if (arg_14 == 4) {
        if (flt_3CDE28 * flt_3CDE28 > bp_4)
            return 0;
        return 1;
    }
    return 0;
}
// match: ?sub_266A0@AIData@@QAEXPAUtype_F8350@@@Z @ 0x000266A0
void AIData::sub_266A0(type_F8350 *arg_0)
{
    RwMatrix var_50;
    RwV3d var_90;
    RwV3d var_9C;
    RwFrame *var_A4;
    RwFrame *var_A8;

    RwMatrixSetIdentity(&var_50);
    RtQuatConvertToMatrix(&arg_0->unk_1C, &var_50);
    RwMatrixRotate(&var_50, &stru_3CDE0C, 180.0f, rwCOMBINEPRECONCAT);
    sub_F8FE0(arg_0, &var_9C, &var_90);
    RwMatrixRotate(&var_50, &stru_3CDE0C, var_90.y, rwCOMBINEPRECONCAT);
    var_A4 = unk_568->get_unk_340();
    var_50.pos = arg_0->unk_10;
    var_A8 = RwFrameGetParent(var_A4);
    if (var_A8)
    {
        *RwFrameGetMatrix(var_A4) = *RwFrameGetLTM(var_A4);
        RwFrameRemoveChild(var_A4);
    }
    RwFrameTransform(var_A4, &var_50, rwCOMBINEREPLACE);
    RwFrameUpdateObjects(var_A4);
    zero_v3d(&unk_568->unk_D8_v);
    zero_v3d(&unk_568->unk_C0);
    zero_v3d(&unk_568->unk_CC);
}
// match: sub_26A30 @ 0x00026A30
void AIData::sub_26A30()
{
    unk_528 = 1;
}
// match: sub_26A50 @ 0x00026A50
void AIData::sub_26A50()
{
    type_F8350 *var_4;

    var_4 = unk_F60;
    if (var_4 != 0)
        sub_266A0(var_4);
}
extern const RwReal flt_3CDE30;
// match: sub_26A80 @ 0x00026A80
// Whether the node arg_0 suits the attack on arg_4 (arg_8 set: without the
// path check); *arg_C is set when the player stands on the node.
RwInt32 AIData::sub_26A80(type_F8350 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwInt32 *arg_C)
{
    RwReal frm_120;
    RwV3d q11C;
    RwV3d o110;
    RwV3d loc104;
    RwV3d bp_F8;
    RwV3d lv_EC;
    RwV3d xE0;
    RwV3d lD4;
    RwReal stk_C8;
    RwReal lcl_C4;
    RwV3d *pC0;
    RwReal lBC;
    RwV3d qB8;
    RwInt32 locAC;
    type_3D3548 *frm_A8;
    RwInt32 lcl_A4;
    RwInt32 lcl_A0;
    RwInt32 ebp_9C;
    RwReal p98;
    RwV3d frm_94;
    RwV3d t88;
    RwV3d p7C;
    RwV3d s70;
    RwV3d var_64;
    type_3DC9B0 *slot_58;
    RwReal l54;
    RwV3d loc50;
    RwReal loc44;
    RwV3d fp_40;
    RwV3d r34;
    type_3D3548 *q28;
    RwV3d *frm_24;
    RwV3d t20;
    RwReal ebp_14;
    type_154C0_80 *lv_10;
    RwReal slot_C;
    RwInt32 bp_8;
    RwV3d *bp_4;

    if (arg_C != 0)
        *arg_C = 0;
    if (arg_0 == 0 || sub_23A10(arg_0) == 0)
        return 0;
    bp_8 = 0;
    bp_4 = unk_568->sub_CD550();
    if (arg_4 != 0) {
        lv_10 = sub_16ED0(arg_4, 0);
        if (lv_10 != 0 && lv_10->unk_0C < 500.0f)
            return 0;
        if (arg_0->unk_04 == 0x11) {
            slot_58 = sub_16A380(arg_0);
            if (slot_58 == 0 || slot_58->sub_169190(unk_568) == 0)
                return 0;
        }
        frm_24 = arg_4->sub_CD550();
        q28 = sub_1745A0(0);
        if (q28 != 0 && and_sides(q28->unk_2C & 7, unk_568->unk_2C & 7) != 0
                && (sub_238E0(0) == 0 || unk_F60 != arg_0)) {
            RwV3dSub(&var_64, q28->sub_CD550(), &arg_0->unk_10);
            var_64.y -= q28->unk_48;
            if (var_64.y <= flt_4275E4 && -flt_4275E8 <= var_64.y) {
                var_64.y = 0.0f;
                if (RwV3dDotProduct(&var_64, &var_64) < flt_4275E8) {
                    if (arg_C != 0)
                        *arg_C = 1;
                    return 0;
                }
            }
        }
        r34 = arg_0->unk_10;
        p98 = 2.0f / (arg_0->unk_1C.real * arg_0->unk_1C.real
                + RwV3dDotProduct(&arg_0->unk_1C.imag, &arg_0->unk_1C.imag));
        RwV3dScale(&frm_94, &arg_0->unk_1C.imag, p98);
        p7C.x = frm_94.x * arg_0->unk_1C.real;
        p7C.y = frm_94.y * arg_0->unk_1C.real;
        s70.x = frm_94.x * arg_0->unk_1C.imag.x;
        s70.y = frm_94.y * arg_0->unk_1C.imag.y;
        t88.x = frm_94.z * arg_0->unk_1C.imag.y;
        loc50.x = (t88.y = frm_94.x * arg_0->unk_1C.imag.z) + p7C.y;
        loc50.y = t88.x - p7C.x;
        loc50.z = 1.0f - (s70.x + s70.y);
        t20.x = frm_24->x - r34.x;
        t20.y = frm_24->y - r34.y;
        t20.z = frm_24->z - r34.z;
        fp_40.x = bp_4->x - r34.x;
        fp_40.y = bp_4->y - r34.y;
        fp_40.z = bp_4->z - r34.z;
        loc44 = RwV3dDotProduct(&t20, &t20);
        l54 = RwV3dDotProduct(&fp_40, &fp_40);
        RwV3dNormalize(&t20, &t20);
        slot_C = RwV3dDotProduct(&loc50, &t20);
        ebp_14 = sub_27500(arg_0);
        if (slot_C >= ebp_14 && loc44 > 250000.0f) {
            ebp_9C = 0;
            lcl_A0 = 0;
            for (lcl_A4 = 0; lcl_A4 < 0x20 && ebp_9C == 0 && lcl_A0 == 0; lcl_A4++) {
                frm_A8 = unk_80[lcl_A4].unk_00.sub_D4910();
                if (frm_A8 != 0 && frm_A8 != arg_4 && (frm_A8->unk_28 & 0x201) == 0) {
                    locAC = cmp_unk_2C(unk_568, frm_A8);
                    if (locAC != 0) {
                        pC0 = frm_A8->sub_CD550();
                        qB8.x = pC0->x - r34.x;
                        qB8.y = pC0->y - r34.y;
                        qB8.z = pC0->z - r34.z;
                        lcl_C4 = RwV3dDotProduct(&loc50, &qB8);
                        lBC = RwV3dDotProduct(&qB8, &qB8);
                        if (lBC < flt_3CDE30) {
                            if (lcl_C4 < 0.0f && lBC < l54)
                                ebp_9C = 1;
                            else if (lcl_C4 >= 0.0f && lBC < 250000.0f)
                                lcl_A0 = 1;
                        }
                    }
                }
            }
            if (ebp_9C == 0 && lcl_A0 == 0) {
                bp_8 = 1;
                if (unk_5C == 3) {
                    stk_C8 = (stk_C8 = unk_568->vf_114()) * stk_C8;
                    if (loc44 > stk_C8)
                        bp_8 = 0;
                }
                if (bp_8 != 0 && arg_8 == 0) {
                    if (unk_5C == 3 || get_unk_DD0() == 0)
                        bp_8 = sub_22370(arg_0, arg_4) == 0;
                }
            }
        }
    } else {
        if (sub_23C30(&xE0) == 0)
            return 0;
        frm_120 = 2.0f / (arg_0->unk_1C.real * arg_0->unk_1C.real
                + RwV3dDotProduct(&arg_0->unk_1C.imag, &arg_0->unk_1C.imag));
        RwV3dScale(&q11C, &arg_0->unk_1C.imag, frm_120);
        loc104.x = q11C.x * arg_0->unk_1C.real;
        loc104.y = q11C.y * arg_0->unk_1C.real;
        bp_F8.x = q11C.x * arg_0->unk_1C.imag.x;
        bp_F8.y = q11C.y * arg_0->unk_1C.imag.y;
        o110.x = q11C.z * arg_0->unk_1C.imag.y;
        lv_EC.x = (o110.y = q11C.x * arg_0->unk_1C.imag.z) + loc104.y;
        lv_EC.y = o110.x - loc104.x;
        lv_EC.z = 1.0f - (bp_F8.x + bp_F8.y);
        RwV3dSub(&lD4, &xE0, &arg_0->unk_10);
        RwV3dNormalize(&lD4, &lD4);
        if (RwV3dDotProduct(&lv_EC, &lD4) > 0.5)
            return 1;
    }
    return bp_8;
}
// match: sub_27370 @ 0x00027370
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_27370(type_3D3548 *arg_0)
{
    RwReal var_68;
    RwV3d loc64;
    RwV3d bp_58;
    RwV3d lv_4C;
    RwV3d frm_40;
    RwV3d lcl_34;
    type_F8350 *lv_28;
    RwV3d lcl_24;
    RwV3d *var_18;
    RwV3d bp_14;
    RwReal lv_8;
    RwReal var_4;

    lv_28 = unk_F60;
    if (lv_28 == 0 || arg_0 == 0)
        return 0;
    lcl_24 = lv_28->unk_10;
    var_18 = arg_0->sub_CD550();
    var_68 = 2.0f / (lv_28->unk_1C.real * lv_28->unk_1C.real
            + RwV3dDotProduct(&lv_28->unk_1C.imag, &lv_28->unk_1C.imag));
    RwV3dScale(&loc64, &lv_28->unk_1C.imag, var_68);
    lv_4C.x = loc64.x * lv_28->unk_1C.real;
    lv_4C.y = loc64.y * lv_28->unk_1C.real;
    frm_40.x = loc64.x * lv_28->unk_1C.imag.x;
    frm_40.y = loc64.y * lv_28->unk_1C.imag.y;
    bp_58.x = loc64.z * lv_28->unk_1C.imag.y;
    lcl_34.x = (bp_58.y = loc64.x * lv_28->unk_1C.imag.z) + lv_4C.y;
    lcl_34.y = bp_58.x - lv_4C.x;
    lcl_34.z = 1.0f - (frm_40.x + frm_40.y);
    bp_14.x = var_18->x - lcl_24.x;
    bp_14.y = var_18->y - lcl_24.y;
    bp_14.z = var_18->z - lcl_24.z;
    lv_8 = sub_27500(lv_28);
    return (var_4 = RwV3dDotProduct(&lcl_34, &bp_14)) >= lv_8;
}
// match: sub_27500 @ 0x00027500
RwReal sub_27500(type_F8350 *arg_0)
{
    type_3DC9B0 *var_4;

    if (arg_0->unk_04 == 0x11) {
        var_4 = sub_16A380(arg_0);
        if (var_4 != 0)
            return var_4->get_unk_4C0();
        return 1.0f;
    }
    return 0.8f;
}
// match: sub_27550 @ 0x00027550
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_27550(type_F8350 *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwReal local_A4;
    RwV3d *local_A0;
    RwReal lcl_9C;
    RwV3d lv_98;
    RwInt32 var_8C;
    type_3D3548 *local_88;
    RwInt32 local_84;
    RwInt32 local_80;
    RwInt32 loc7C;
    RwReal local_78;
    RwV3d local_74;
    RwV3d ebp_68;
    RwV3d var_5C;
    RwV3d var_50;
    RwReal local_44;
    RwV3d local_40;
    RwInt32 var34;
    RwReal lcl_30;
    RwV3d var_2C;
    RwV3d v20;
    RwV3d local_14;
    RwReal lv_8;
    RwReal var_4;

    if (arg_8 == 0 || arg_4 == 0 || arg_0 == 0)
        return 0;
    if (sub_23A10(arg_0) == 0)
        return 0;
    var34 = 0;
    v20 = arg_0->unk_10;
    local_78 = 2.0f / (arg_0->unk_1C.real * arg_0->unk_1C.real
            + RwV3dDotProduct(&arg_0->unk_1C.imag, &arg_0->unk_1C.imag));
    RwV3dScale(&local_74, &arg_0->unk_1C.imag, local_78);
    var_5C.x = local_74.x * arg_0->unk_1C.real;
    var_5C.y = local_74.y * arg_0->unk_1C.real;
    var_50.x = local_74.x * arg_0->unk_1C.imag.x;
    var_50.y = local_74.y * arg_0->unk_1C.imag.y;
    ebp_68.x = local_74.z * arg_0->unk_1C.imag.y;
    local_40.x = (ebp_68.y = local_74.x * arg_0->unk_1C.imag.z) + var_5C.y;
    local_40.y = ebp_68.x - var_5C.x;
    local_40.z = 1.0f - (var_50.x + var_50.y);
    local_14.x = arg_4->x - v20.x;
    local_14.y = arg_4->y - v20.y;
    local_14.z = arg_4->z - v20.z;
    var_2C.x = arg_8->x - v20.x;
    var_2C.y = arg_8->y - v20.y;
    var_2C.z = arg_8->z - v20.z;
    lcl_30 = RwV3dDotProduct(&local_14, &local_14);
    local_44 = RwV3dDotProduct(&var_2C, &var_2C);
    RwV3dNormalize(&local_14, &local_14);
    var_4 = RwV3dDotProduct(&local_40, &local_14);
    lv_8 = sub_27500(arg_0);
    if (var_4 >= lv_8 && lcl_30 > 250000.0f) {
        loc7C = 0;
        local_80 = 0;
        for (local_84 = 0; local_84 < 0x20 && loc7C == 0 && local_80 == 0; local_84++) {
            local_88 = unk_80[local_84].unk_00.sub_D4910();
            if (local_88 != 0) {
                var_8C = cmp_unk_2C(unk_568, local_88);
                if (var_8C != 0) {
                    local_A0 = local_88->sub_CD550();
                    lv_98.x = local_A0->x - v20.x;
                    lv_98.y = local_A0->y - v20.y;
                    lv_98.z = local_A0->z - v20.z;
                    local_A4 = RwV3dDotProduct(&local_40, &lv_98);
                    lcl_9C = RwV3dDotProduct(&lv_98, &lv_98);
                    if (lcl_9C < flt_3CDE30) {
                        if (local_A4 < 0.0f && lcl_9C < local_44)
                            loc7C = 1;
                        else if (local_A4 >= 0.0f && lcl_9C < 250000.0f)
                            local_80 = 1;
                    }
                }
            }
        }
        if (loc7C == 0 && local_80 == 0)
            var34 = 1;
    }
    return var34;
}
extern const RwReal flt_3CDE2C;
// match: sub_279B0 @ 0x000279B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_14D180 *AIData::sub_279B0(type_154C0_12F4 *arg_0, type_3D3548 *arg_4, type_14D180 *arg_8)
{
    RwReal local_50;
    RwV3d *stk_4C;
    RwReal loc48;
    RwV3d var_44;
    RwInt32 v38;
    type_3D3548 *v34;
    RwInt32 v30;
    RwReal var_2C;
    RwV3d *lv_28;
    RwInt32 var_24;
    RwInt32 var_20;
    RwV3d l1C;
    RwInt32 lv_10;
    RwInt32 var_C;
    type_14D180 *bp_8;
    type_3DBC78 *bp_4;

    if (unk_568->vf_008() != 0 && unk_568->vf_008()->unk_3E0.sub_15EF80() == 3)
        return 0;
    bp_8 = 0;
    bp_4 = static_cast<type_3DBC78 *>(arg_0->unk_08.sub_D4910());
    if (bp_4 != 0) {
        if (arg_8 == 0)
            arg_8 = bp_4->sub_155340(arg_0);
        if (arg_8 != 0 && (arg_8->unk_00 & 1) != 0 && ((arg_8->unk_00 >> 1) & 1) != 0) {
            lv_10 = 1;
            if ((var_C = unk_49C & 0x2000) != 0 && sub_205E0(&arg_8->unk_14, 0.0f) == 0)
                lv_10 = 0;
            if (lv_10 != 0) {
                lv_28 = unk_568->sub_CD550();
                RwV3dSub(&l1C, lv_28, &arg_8->unk_14);
                var_2C = RwV3dDotProduct(&l1C, &l1C);
                var_20 = 0;
                var_24 = 0;
                for (v30 = 0; v30 < 0x20 && var_20 == 0 && var_24 == 0; v30++) {
                    v34 = unk_80[v30].unk_00.sub_D4910();
                    if (v34 != 0) {
                        v38 = cmp_unk_2C(unk_568, v34);
                        if (v38 != 0) {
                            stk_4C = v34->sub_CD550();
                            RwV3dSub(&var_44, stk_4C, &arg_8->unk_14);
                            local_50 = RwV3dDotProduct(&arg_8->unk_20, &var_44);
                            loc48 = RwV3dDotProduct(&var_44, &var_44);
                            if (loc48 < flt_3CDE30) {
                                if (local_50 < 0.0f && loc48 < flt_3CDE2C)
                                    var_20 = 1;
                                if (loc48 < var_2C)
                                    var_24 = 1;
                            }
                        }
                    }
                }
                if (var_20 == 0)
                    bp_8 = arg_8;
            }
        }
    }
    return bp_8;
}
// match: sub_27CC0 @ 0x00027CC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_27CC0(type_F8350 **arg_0)
{
    RwV3d *var_4;
    RwInt32 v8;
    type_F8350 *varC;

    var_4 = unk_568->sub_CD550();
    unk_1048.unk_04 = *var_4;
    unk_1048.unk_10 = 2500.0f;
    unk_1048.unk_00 = unk_568;
    unk_1048.unk_18 = sub_F7E80(4);
    unk_1048.unk_1C = 0;
    unk_1048.unk_20 = unk_F80;
    unk_1048.unk_24 = 25;
    sub_F8970(&unk_1048, 1, 0);
    unk_F70 = *var_4;
    v8 = 0;
    if (unk_1048.unk_4C != 0) {
        varC = unk_1048.unk_34;
        if (((varC->unk_00 >> 2) & 1) != 0) {
            v8 = 0;
            unk_F54 = 0;
        } else if (varC == unk_F54) {
            if (arg_0 != 0)
                *arg_0 = unk_F54;
            v8 = 1;
        } else if (sub_23A10(varC) != 0 || varC->unk_04 == 0xE) {
            unk_F54 = varC;
            v8 = 1;
        }
    }
    return v8;
}
// match: sub_27E30 @ 0x00027E30
RwInt32 AIData::sub_27E30()
{
    if (sub_27CC0(0) != 0) {
        unk_568->vf_0C0(&unk_F54->unk_10);
        unk_568->vf_0D4(&unk_F54->unk_1C);
        sub_23670();
        sub_22F70();
        return 1;
    }
    return 0;
}
// match: sub_27EB0 @ 0x00027EB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *AIData::sub_27EB0(RwV3d *arg_0, RwV3d *arg_4)
{
    RwV3d frm_1A0;
    RwInt32 lv_194;
    type_154C0_F80 local_190[32];
    type_F8350 *l90;
    RwV3d var_8C;
    RwReal local_80;
    RwReal loc7C;
    type_F8350 *l10;
    RwReal local_C;
    type_F8350 *lv_8;
    RwInt32 var_4 = 32;
    type_154C0_1048 local_78;
    type_4C00E8 *lcl_14 = &unk_4C00E8;

    if ((unk_49C & 0x2000) != 0) {
        local_78.unk_04 = unk_13A8;
        local_78.unk_10 = get_unk_13B4();
        loc7C = get_unk_13B4() / 2.0f;
    } else {
        local_78.unk_04 = *unk_568->sub_CD550();
        local_78.unk_10 = 1500.0f;
        loc7C = 250000.0f;
    }
    local_78.unk_00 = unk_568;
    local_78.unk_18 = 0;
    local_78.unk_1C = 1;
    local_78.unk_20 = local_190;
    local_78.unk_24 = 32;
    sub_F8970(&local_78, 0, 0);
    local_80 = 2250000.0f;
    local_C = 2250000.0f;
    lv_8 = 0;
    l10 = 0;
    RwV3dNormalize(&var_8C, arg_4);
    for (lv_194 = 0; lv_194 < local_78.unk_4C; lv_194++) {
        if (local_190[lv_194].unk_04 < local_C) {
            l90 = lcl_14->unk_2C[local_190[lv_194].unk_00];
            if (l90 != 0 && sub_140C90(&local_78.unk_04, &l90->unk_10) > loc7C) {
                if (local_190[lv_194].unk_04 < local_80) {
                    local_80 = local_190[lv_194].unk_04;
                    l10 = l90;
                }
                RwV3dSub(&frm_1A0, &l90->unk_10, unk_568->sub_CD550());
                RwV3dNormalize(&frm_1A0, &frm_1A0);
                if (local_190[lv_194].unk_04 < local_C && RwV3dDotProduct(&frm_1A0, &var_8C) > 0.55) {
                    local_C = local_190[lv_194].unk_04;
                    lv_8 = l90;
                }
            }
        }
    }
    if (lv_8 != 0)
        return &lv_8->unk_10;
    if (l10 != 0)
        return &l10->unk_10;
    return 0;
}
// Whether the cover node arg_4 faces the point arg_0 (a RwV3d's address):
// the dot of its cover orientation's at row with the direction from the
// node to the point is over 0.2.
// match: ?sub_28200@AIData@@QAEHHPAUtype_F8350@@@Z @ 0x00028200
RwInt32 AIData::sub_28200(RwInt32 arg_0, type_F8350 *arg_4)
{
    RwV3d var_10;
    RwMatrix var_50;
    RwReal var_88;

    RwV3dSubMacro(&var_10, (RwV3d *)arg_0, &arg_4->unk_10);
    RwV3dNormalize(&var_10, &var_10);
    RwMatrixSetIdentity(&var_50);
    RtQuatConvertToMatrix(&arg_4->unk_1C, &var_50);
    var_88 = RwV3dDotProductMacro(&var_10, &var_50.at);
    if (var_88 > 0.2f)
        return 1;
    return 0;
}
// match: sub_28470 @ 0x00028470
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_28470(RwV3d *arg_0)
{
    RwReal l188;
    RwInt32 l184;
    type_154C0_F80 l180[32];
    type_F8350 *loc7C;
    RwReal local_78;
    RwReal local_74;
    type_F8350 *lv_8;
    RwInt32 var_4 = 32;
    type_154C0_1048 local_70;
    type_4C00E8 *local_C = &unk_4C00E8;

    local_70.unk_04 = *unk_568->sub_CD550();
    local_70.unk_10 = 1000.0f;
    local_70.unk_00 = unk_568;
    local_70.unk_18 = 0;
    local_70.unk_1C = 1;
    local_70.unk_20 = l180;
    local_70.unk_24 = 32;
    sub_F8970(&local_70, 0, 0);
    local_78 = 490000.0f;
    local_74 = 1000000.0f;
    lv_8 = 0;
    for (l184 = 0; l184 < local_70.unk_4C; l184++) {
        if (l180[l184].unk_04 < local_74) {
            loc7C = local_C->unk_2C[l180[l184].unk_00];
            if (loc7C != 0) {
                l188 = sub_140C90(&loc7C->unk_10, arg_0);
                if (l188 > local_78 && sub_140C90(&loc7C->unk_10, unk_568->sub_CD550()) < l188) {
                    local_74 = l180[l184].unk_04;
                    lv_8 = loc7C;
                }
            }
        }
    }
    if (lv_8 != 0) {
        unk_5B0 = lv_8->unk_10;
        return 1;
    }
    return 0;
}
// match: sub_28640 @ 0x00028640
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_28640(RwInt32 arg_0)
{
    RwReal l4;
    type_4C00E8 *var_8;
    RwReal fp_C;
    type_F8350 *local_10;
    RwV3d *stk_14;
    type_F8350 *lcl_18;
    RwInt32 fp_1C;

    lcl_18 = 0;
    var_8 = &unk_4C00E8;
    fp_C = 1000000.0f;
    stk_14 = unk_568->sub_CD550();
    local_10 = 0;
    for (fp_1C = 0; fp_1C < unk_1048.unk_4C; fp_1C++) {
        lcl_18 = var_8->unk_2C[unk_F80[fp_1C].unk_00];
        if (((lcl_18->unk_00 >> 2) & 1) == 0 && (sub_23A10(lcl_18) != 0 || lcl_18->unk_04 == 0xE)) {
            l4 = sub_140C90(&lcl_18->unk_10, stk_14);
            if (l4 < fp_C && sub_28200(arg_0, lcl_18) != 0) {
                fp_C = l4;
                local_10 = lcl_18;
            }
        }
    }
    if (local_10 != 0) {
        sub_F7BA0(this, local_10, true);
        sub_236F0(local_10);
        unk_5B0 = local_10->unk_10;
        return 1;
    }
    return 0;
}
// match: sub_28780 @ 0x00028780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_28780()
{
    type_3CE278 *l4;
    type_F8350 *var_8;
    RwUInt32 fp_C;
    RwUInt32 local_10;
    RwUInt32 stk_14;
    RwInt32 loc18;

    local_10 = unk_574;
    if (sub_3D3E0(local_10) != 0) {
        stk_14 = unk_574;
        loc18 = sub_3D3E0(stk_14)->vf_030();
    } else {
        loc18 = -1;
    }
    if (loc18 != 6)
        return 0;
    fp_C = unk_574;
    l4 = static_cast<type_3CE278 *>(sub_3D3E0(fp_C));
    var_8 = l4->unk_1C;
    if (var_8 == 0)
        return 0;
    unk_5B0 = var_8->unk_10;
    return 1;
}
// match: sub_28840 @ 0x00028840
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwBool AIData::sub_28840(type_3D3548 *arg_0)
{
    RwBool var_4;
    type_154C0_12F4 *local_8;

    var_4 = 0;
    local_8 = sub_23BE0();
    if (local_8 != 0 && sub_28890(arg_0, local_8) != 0)
        var_4 = 1;
    return var_4;
}
// match: sub_28890 @ 0x00028890
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_28890(type_3D3548 *arg_0, type_154C0_12F4 *arg_4)
{
    type_3DBC78 *l4;
    type_14D180 *var_8;
    RwV3d *fp_C;
    RwReal local_10;
    RwV3d *stk_14;
    RwReal loc18;
    RwV3d fp_24;

    if (arg_4 != 0) {
        l4 = static_cast<type_3DBC78 *>(arg_4->unk_08.sub_D4910());
        if (l4 != 0) {
            var_8 = l4->sub_155340(arg_4);
            if (var_8 != 0) {
                fp_C = unk_568->sub_CD5A0();
                stk_14 = unk_568->sub_CD550();
                RwV3dSub(&fp_24, &var_8->unk_14, stk_14);
                local_10 = RwV3dDotProduct(&fp_24, &fp_24);
                if (local_10 > 0.001f)
                    RwV3dNormalize(&fp_24, &fp_24);
                loc18 = RwV3dDotProduct(&fp_24, fp_C);
                if (loc18 > 0.3f || local_10 < 62500.0f) {
                    RwV3dSub(&fp_24, arg_0->sub_CD550(), &var_8->unk_14);
                    if (RwV3dDotProduct(&fp_24, &fp_24) > 0.001f)
                        RwV3dNormalize(&fp_24, &fp_24);
                    loc18 = RwV3dDotProduct(&var_8->unk_20, &fp_24);
                    if (loc18 > 0.3f)
                        return 1;
                }
            }
        }
    }
    return 0;
}
