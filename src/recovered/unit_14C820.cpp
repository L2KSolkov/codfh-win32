// Split from unit_147080.cpp at 0x14C820, where the image starts another object (the
// vehicle, type_3DBC78): its factory first, then the constructor's out-of-line copy it
// needs (sub_14C930) with the vtable's inline functions; its .rdata begins at 0x3DBC58
// with its own constants (the frame time and two axes, which the tank reads too) before
// its vtable (PLAN M7).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "game/functions.h"
#include "game/vecutil.h"
#include "types/type_3DBC78_450.h"
#include "types/type_3DF8D8.h"
#include "types/type_3DBC78.h"
#include "types/type_3DC048.h"
#include "types/animkey.h"
#include "types/animobjpool.h"
#include "types/animbank.h"
#include "types/type_3D51C0.h"
#include "types/soundbank.h"
#include "rw/babbox.h"
#include "types/type_10F710.h"
#include "types/type_4E5D30.h"
#include "game/data.h"
#include "rw/bavector.h"
#include <math.h>
#include "rw/rpcollis.h"
#include "types/type_92430.h"
#include "types/type_3DDB98.h"
#include "rw/rpatomic.h"
#include "types/type_44350.h"
#include "types/type_3D32F8.h"
#include "rw/bamemory.h"
#include "types/alfaobject.h"
#include "rw/rpmaterial.h"
#include "rw/batextur.h"
#include "rw/rtanim.h"
#include <string.h>
#include <ctype.h>
#include "game/fade.h"
#include "game/gameloop.h"
#include "types/type_DC400.h"
#include "game/clumpdata.h"
#include "rw/rtquat.h"
#include "rw/rprandom.h"
#include "types/type_4C00E8.h"
#include "types/type_3CE1FC.h"
#include "types/CGlobalSounds.h"
#include "rws/skinhelper.h"
#include "types/VehicleTrigger.h"
#include "types/GimpVehicleTrigger.h"

// An int's absolute value: an inline with no address and so no database
// name. Evidence: vf_2D4 applies it to a comparison's result (a misplaced
// parenthesis in the original), which it first stores as the argument,
// then selects through a result temporary with an integer compare.
inline RwInt32 abs_int(RwInt32 arg_0)
{
    return arg_0 >= 0 ? arg_0 : -arg_0;
}

// The magnitude of arg_0: an inline with no address and so no database name,
// as in unit_1340D0. Evidence: vf_2B8 copies the speed into a parameter slot,
// compares it with 0 and copies it or its negation into a result temporary,
// with no call to the C library's fabs.
inline RwReal real_abs(RwReal arg_0)
{
    return arg_0 >= 0.0f ? arg_0 : -arg_0;
}

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DBC58
extern const RwReal flt_3DBC58 = 16.666666f;
// 0x003DBC5C
extern const RwV3d stru_3DBC5C = { 1.0f, 0.0f, 0.0f };
// 0x003DBC68
extern const RwV3d stru_3DBC68 = { 0.0f, 1.0f, 0.0f };
// 0x003DBC74
extern const RwReal flt_3DBC74 = 0.0f;

// match: ?flt_3DBC58@@3MB @ 0x003DBC58
// match: ?stru_3DBC5C@@3URwV3d@@B @ 0x003DBC5C
// match: ?stru_3DBC68@@3URwV3d@@B @ 0x003DBC68
// match: ?flt_3DBC74@@3MB @ 0x003DBC74
// match: __real@c3b40000 @ 0x003DBF78



// match: __ehhandler$??0type_3DBC78@@QAE@PAUtype_712B0@@@Z>1>8 @ 0x0041DD8C
// match: __ehhandler$??0type_3DBC78@@QAE@PAUtype_712B0@@@Z>1 @ 0x0041DDD4
// match: __ehhandler$??1type_3DBC78@@UAE@XZ>1>8 @ 0x0041DDF0
// match: __ehhandler$??1type_3DBC78@@UAE@XZ>1 @ 0x0041DE40
// match: __ehhandler$?vf_1D0@type_3DBC78@@UAEXXZ>1>8 @ 0x0041DE5C
// match: __ehhandler$?vf_1D0@type_3DBC78@@UAEXXZ>1 @ 0x0041DE64
// match: __ehhandler$??0type_3DBC78@@QAE@PAUtype_712B0@@@Z-0x82 @ 0x00301AC0
// match: __ehhandler$??0type_3DBC78@@QAE@PAUtype_712B0@@@Z @ 0x00301B42
// match: __ehhandler$??1type_3DBC78@@UAE@XZ-0x8A @ 0x00301B50
// match: __ehhandler$??1type_3DBC78@@UAE@XZ @ 0x00301BDA
// match: ?vf_094@type_3DBC78@@UAEXI@Z @ 0x0014CA50
// match: ?vf_238@type_3DBC78@@UAEMXZ @ 0x0014CA70
// match: ?vf_23C@type_3DBC78@@UAEXM@Z @ 0x0014CA90
// match: ?vf_240@type_3DBC78@@UAEHXZ @ 0x0014CAB0
// match: ?vf_244@type_3DBC78@@UAEXH@Z @ 0x0014CAD0
// match: ?vf_248@type_3DBC78@@UAEHXZ @ 0x0014CAF0
// match: ?vf_174@type_3DBC78@@UAEHXZ @ 0x0014CB10
// match: ?vf_178@type_3DBC78@@UAEXH@Z @ 0x0014CB30
// match: ?vf_180@type_3DBC78@@UAEXH@Z @ 0x0014CB50
// match: ?vf_0DC@type_3DBC78@@UAEHXZ @ 0x0014CBA0
// match: ?vf_17C@type_3DBC78@@UAEMXZ @ 0x0014CBC0
// match: ?vf_24C@type_3DBC78@@UAEHXZ @ 0x0014CBE0
// match: ?vf_250@type_3DBC78@@UAEMXZ @ 0x0014CC00
// match: ?vf_164@type_3DBC78@@UAEMXZ @ 0x0014CC20
// match: ?vf_168@type_3DBC78@@UAEMXZ @ 0x0014CC40
// match: ?vf_254@type_3DBC78@@UAEMXZ @ 0x0014CC60
// match: ?vf_258@type_3DBC78@@UAEMXZ @ 0x0014CC80
// match: ?vf_25C@type_3DBC78@@UAEHXZ @ 0x0014CCA0
// match: ?vf_260@type_3DBC78@@UAEPAEXZ @ 0x0014CCC0
// match: ?vf_0E0@type_3DBC78@@UAEPAEXZ @ 0x0014CCE0
// match: ?vf_09C@type_3DBC78@@UAEHXZ @ 0x0014CD00
// match: ?vf_0A0@type_3DBC78@@UAEXI@Z @ 0x0014CD20
// match: ?vf_120@type_3DBC78@@UAEPAUAIData@@XZ @ 0x0014CD40
// match: ?vf_118@type_3DBC78@@UAEPAUtype_3D3548@@XZ @ 0x0014CD60
// match: ?vf_11C@type_3DBC78@@UAEXPAUtype_3D3548@@@Z @ 0x0014CD80
// match: ?vf_27C@type_3DBC78@@UAEXH@Z @ 0x0014CDA0
// match: ?vf_284@type_3DBC78@@UAEMXZ @ 0x0014CDC0
// match: ?vf_288@type_3DBC78@@UAEXH@Z @ 0x0014CDE0
// match: ?vf_290@type_3DBC78@@UAEXH@Z @ 0x0014CE00
// match: ?vf_2A8@type_3DBC78@@UAEHHPAURwV3d@@H@Z @ 0x0014CE20
// match: ?vf_2AC@type_3DBC78@@UAEHH@Z @ 0x0014CE30
// match: ?vf_2C4@type_3DBC78@@UAEPAUtype_3DC9B0@@XZ @ 0x0014CE50
// match: ?vf_1DC@type_3DBC78@@UAEHXZ @ 0x0014CE70
// match: ?vf_1E0@type_3DBC78@@UAEMXZ @ 0x0014CE90
// match: ?vf_2E8@type_3DBC78@@UAEMXZ @ 0x0014CEB0
// match: ?vf_2EC@type_3DBC78@@UAEMXZ @ 0x0014CED0
// match: ??0type_3DBC78@@QAE@PAUtype_712B0@@@Z @ 0x0014C930
// match: ??0type_14D000@@QAE@XZ @ 0x0014D000
// match: ??_Gtype_3DBC78@@UAEPAXI@Z @ 0x0014CEF0
// match: ??1type_3DBC78@@UAE@XZ @ 0x0014CF20
// match: ??_7type_3DBC78@@6B@ @ 0x003DBC78
// match: __real@3f28f5c3 @ 0x003DBF7C
// match: ??_C@_09OMEHJBAL@destroyed?$AA@ @ 0x003DBF80
// match: ??_C@_0BE@IDGGPEPG@rear?5damage?$CB?5?$CF3?42f?6?$AA@ @ 0x003DBF8C
// match: ??_C@_0BF@HEPNMPAL@front?5damage?$CB?5?$CF3?42f?6?$AA@ @ 0x003DBFA0
// match: ??_C@_0BE@NFPBFLAG@side?5damage?$CB?5?$CF3?42f?6?$AA@ @ 0x003DBFB8
// match: ??_C@_0BD@FKAGLCLM@top?5damage?$CB?5?$CF3?42f?6?$AA@ @ 0x003DBFCC
// match: __real@3f7c28f6 @ 0x003DBFE0
// match: __real@3cf5c28f @ 0x003DBFE4
// match: ??_C@_0O@DMKOHGEI@VehicleEntity?$AA@ @ 0x003DBFE8
// match: ??_C@_06LBIIGOJL@vtrack?$AA@ @ 0x003DBFF8
// match: __real@42340000 @ 0x003DC000
// match: __real@3c8efa2e @ 0x003DC004
// match: ??_C@_0BG@IMKAHIPL@Vehicle_PathUnBlocked?$AA@ @ 0x003DC008
// match: ??_C@_0BE@DBDCBHDM@Vehicle_PathBlocked?$AA@ @ 0x003DC020
// match: ??_C@_09CDFKMKLC@TankAlert?$AA@ @ 0x003DC034
// match: __real@c0400000 @ 0x003DC040
// match: __real@42840000 @ 0x003DC044

// Not in the image: a stand-in for the dropped code that first built the vehicle here
// (the link kept the factory, sub_14C820, from unit_155470's object, where the image
// has its EH handler): it makes this object emit the constructor's out-of-line copy,
// its vtable and the inline virtuals, as the image has them. Unreferenced.
void dropped_14C930(type_712B0 *arg_0, type_3DBC78 *arg_4)
{
    arg_4->type_3DBC78::type_3DBC78(arg_0);
}
// match: ??0type_14D180@@QAE@XZ @ 0x0014D180
type_14D180::type_14D180()
{
}
// match: ?sub_14D1B0@@YAXPAURwMatrixTag@@MMMM@Z @ 0x0014D1B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_14D1B0(RwMatrix *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10)
{
    RwReal var_28;
    RwReal ebp_24;
    RwReal var_20;
    RwReal l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    bp_8 = arg_10 * 0.017453292f;
    ebp_24 = (RwReal)(RwDouble)(RwReal)sin((RwDouble)bp_8);
    lv_10 = (RwReal)(RwDouble)(RwReal)cos((RwDouble)bp_8);
    m_18 = (var_C = 1.0f - lv_10) * arg_4 * arg_8;
    ebp_14 = var_C * arg_8 * arg_C;
    var_28 = var_C * arg_4 * arg_C;
    var_20 = ebp_24 * arg_4;
    l1C = ebp_24 * arg_8;
    bp_4 = ebp_24 * arg_C;
    arg_0->right.x = var_C * arg_4 * arg_4 + lv_10;
    arg_0->right.y = m_18 + bp_4;
    arg_0->right.z = var_28 - l1C;
    arg_0->up.x = m_18 - bp_4;
    arg_0->up.y = var_C * arg_8 * arg_8 + lv_10;
    arg_0->up.z = ebp_14 + var_20;
    arg_0->at.x = var_28 + l1C;
    arg_0->at.y = ebp_14 - var_20;
    arg_0->at.z = var_C * arg_C * arg_C + lv_10;
}
// match: ?sub_14D2C0@type_3DBC78@@QAEHPAUtype_712B0@@@Z @ 0x0014D2C0
// The vehicle's set-up from its trigger arg_0 (its constructor's body): its
// spline object's handle, the base's (sub_CCCD0), its AI settings, its kind
// flags by its model's data, its model (vf_2F8), animation and bodies, its
// sounds, its bones (the wheels 700 to 798, the track wheels 650 to 698, the
// root 100 and the turret 155), its contact points, its health and armour,
// its HUD name, its AI object (kinds 1 to 3), a mounted gun, its twelve
// cover points and its AI spline.
RwInt32 type_3DBC78::sub_14D2C0(type_712B0 *arg_0)
{
    RwInt32 var_8;
    type_712B0_3DBC78 *var_C;
    type_3DF8D8 *var_10;
    type_3DFEEC *var_14;
    type_3DF8D8 *var_20;
    RwUInt32 var_30;
    type_7C8D0 *var_34;
    RpHAnimHierarchy *var_3C;
    RwV3d var_50;
    type_EC1F0 *var_58;
    type_14D2C0_00 *var_5C;
    type_3D3548 *var_60;
    RpHAnimHierarchy *var_70;
    RpHAnimHierarchy *var_78;
    RwMatrix *var_7C;
    RwUInt32 var_8C[4];
    type_3DBC78_450 *var_90;
    RwBBox *var_94;
    RwV3d var_C4[4];
    RwV3d var_D0;
    RwReal var_E0;
    RwReal var_E4;
    RwReal var_E8;
    RwReal var_F0;
    RwReal var_F4;
    RwReal var_F8;
    RwReal var_100;
    RwReal var_104;
    RwReal var_108;
    RwReal var_110;
    RwReal var_114;
    RwReal var_118;
    RwReal var_120;
    RwInt32 var_128;
    const RwChar *var_12C;
    RwMatrix var_1C0;
    type_712B0 *var_1C4;
    type_3D3548 *var_1C8;
    RwUInt32 var_1F8[12];
    RwBBox var_210;
    type_14D180 *var_214;
    type_EC1F0 *var_21C;
    RwMatrix var_260;
    RwReal var_26C;
    RwReal var_278;
    type_3DF8D8 *var_28C;
    type_3DFEEC *var_290;

    var_8 = 0;
    var_C = (type_712B0_3DBC78 *)arg_0;
    var_10 = sub_198800(&var_C->unk_C0);
    if (var_C->unk_E0.unk_00)
    {
        var_14 = (type_3DFEEC *)sub_198800(&var_C->unk_E0);
        ((type_D48D0 *)&var_14->unk_24_id)->sub_D48D0(this);
        var_14->unk_10 = 0x22;
    }
    unk_B28 = 1;
    unk_2858 = 1;
    unk_88 &= ~0x2000;
    unk_1100 = 0;
    unk_DB0 = var_C->unk_13C;
    sub_CCCD0(arg_0);
    unk_1188 = var_C->unk_E8;
    unk_118C.sub_D48D0(0);
    unk_1190.sub_D48D0(0);
    unk_DD0 = var_C->unk_158;
    unk_1150 = var_C->unk_124;
    unk_1154 = var_C->unk_128;
    unk_1158 = 0;
    unk_115C = var_C->unk_12C;
    unk_1160 = var_C->unk_130;
    unk_1164 = 1.0f;
    unk_1168 = var_C->unk_154;
    unk_116C = var_C->unk_134;
    unk_1170 = var_C->unk_138;
    unk_1174 = var_C->unk_14C;
    unk_1178 = var_C->unk_150;
    unk_28 = 60;
    switch (((type_14D2C0_10 *)var_10->unk_10)->get_unk_8C())
    {
    case 0:
    case 2:
        unk_2C = 0x82;
        break;
    case 1:
    case 3:
    case 4:
        unk_2C = 0x81;
        break;
    }
    unk_30 = -1;
    unk_34 = 0x2600B0; // not an address: kind flags
    unk_DC8 = var_C->unk_FC;
    unk_DCC = 0;
    unk_130 = 0;
    vf_2F8(var_10, var_C);
    var_20 = ((type_3DFE7C *)var_10)->sub_1954D0();
    sub_16E080(get_unk_264(), ((type_3DF8D8_3 *)var_20)->get_unk_54());
    sub_16D8C0(get_unk_264(), "destroyed", 0);
    var_30 = sub_78830(0);
    unk_280 = var_30;
    var_34 = (type_7C8D0 *)sub_78AC0(unk_280);
    unk_284 = var_34;
    var_3C = sub_16D970(get_unk_264());
    var_34->sub_79470(var_3C);
    var_34->unk_1C = (RwInt32)this;
    memset(unk_112C, 0, 6);
    for (var_8 = 0; var_8 < 2; var_8++)
        unk_1130[var_8] = 1;
    unk_450.sub_147080(var_C, RwFrameGetMatrix(get_unk_340()));
    unk_7B0.sub_147080(var_C, RwFrameGetMatrix(get_unk_340()));
    var_50.x = 0.0f;
    var_50.y = 0.0f;
    var_50.z = 0.0f;
    var_58 = sub_EC1F0(get_unk_264(), 0x434F4D00); // not an address: a tag
    if (var_58)
        var_50.y = -var_58->unk_10.pos.y;
    unk_7B0.unk_25C = var_50;
    unk_450.unk_25C = unk_7B0.unk_25C;
    if ((unk_2C & 7) == 2)
        sub_D5B80(this, 0);
    else
        sub_D5B80(this, 1);
    unk_11A0.sub_16BC0(this);
    sub_83850(4, &unk_1C0, &unk_3B0);
    var_5C = ((type_14D2C0_10 *)var_10->unk_10)->unk_00;
    memcpy(&unk_3D4, var_5C->unk_10, sizeof(type_14D000));
    var_60 = sub_1745A0(0);
    if (unk_118C.sub_D4910() == var_60)
        unk_1144 = unk_1C0.sub_8A980(&unk_3D4.unk_10, this, 4, var_60->sub_CD550(), 0, 0);
    else
        unk_1144 = unk_1C0.sub_8A980(&unk_3D4.unk_10, this, 4, sub_CD550(), 0, 0);
    unk_1124 = 0;
    unk_1128 = 0;
    unk_1134 = 0;
    unk_1138 = 0;
    unk_113C = 0;
    unk_1140 = 0;
    unk_1144 = 0;
    unk_1148 = 0;
    unk_114C = -1;
    unk_DB4 = 0;
    unk_DB8 = 0;
    unk_DBC = 0;
    unk_DC4 = 1;
    unk_DC0 = 1;
    unk_2638 = 1.0f;
    unk_1104 = 0;
    unk_1120 = 0.0f;
    unk_2620 = 0;
    unk_1194 = 0;
    zero_v3d(&unk_1108);
    zero_v3d(&unk_1114);
    sub_3EE10(this);
    var_70 = get_unk_284()->unk_18;
    unk_B2C = RpHAnimIDGetIndex(var_70, 1);
    unk_DA8 = 0.0f;
    unk_DAC = 0.0f;
    unk_DA4 = 0.0f;
    unk_DA0 = 0.0f;
    unk_450.unk_29C = 1;
    var_78 = get_unk_284()->unk_18;
    var_7C = RpHAnimHierarchyGetMatrixArray(var_78);
    for (var_8 = 700, unk_B3C = 0; var_8 < 799; var_8++)
    {
        unk_B40[unk_B3C] = RpHAnimIDGetIndex(var_78, var_8);
        if (unk_B40[unk_B3C] != -1)
        {
            if (var_7C[unk_B40[unk_B3C]].pos.x < 0.0f)
                unk_C08[unk_B40[unk_B3C]] = 1;
            else
                unk_C08[unk_B40[unk_B3C]] = 2;
            unk_B3C++;
        }
    }
    for (var_8 = 650, unk_CD0 = 0; var_8 < 699; var_8++)
    {
        unk_CD4[unk_CD0] = RpHAnimIDGetIndex(var_78, var_8);
        if (unk_CD4[unk_CD0] != -1)
        {
            if (var_7C[unk_CD4[unk_CD0]].pos.x < 0.0f)
                unk_D38[unk_CD4[unk_CD0]] = 1;
            else
                unk_D38[unk_CD4[unk_CD0]] = 2;
            unk_CD0++;
        }
    }
    unk_D9C = RpHAnimIDGetIndex(var_78, 100);
    unk_B20 = RpHAnimIDGetIndex(var_78, 155);
    unk_B24 = 0.0f;
    var_8C[0] = 0x5745464C; // not an address: a tag
    var_8C[1] = 0x57454652; // not an address: a tag
    var_8C[2] = 0x5745524C; // not an address: a tag
    var_8C[3] = 0x57455252; // not an address: a tag
    var_90 = &unk_450;
    var_94 = (RwBBox *)&unk_450.unk_280;
    var_C4[0].x = 300.0f;
    var_C4[0].y = 0.0f;
    var_C4[0].z = 300.0f;
    var_C4[1].x = -300.0f;
    var_C4[1].y = 0.0f;
    var_C4[1].z = 300.0f;
    var_C4[2].x = 300.0f;
    var_C4[2].y = 0.0f;
    var_C4[2].z = -300.0f;
    var_C4[3].x = -300.0f;
    var_C4[3].y = 0.0f;
    var_C4[3].z = -300.0f;
    for (var_8 = 0; var_8 < 4; var_8++)
    {
        if (vf_018())
        {
            var_D0.x = var_C4[var_8].x;
            var_D0.y = var_C4[var_8].y - 10.0f;
            var_D0.z = var_C4[var_8].z;
        }
        else
        {
            var_58 = sub_EC1F0(get_unk_264(), var_8C[var_8]);
            var_D0.x = var_58->unk_10.pos.x;
            var_D0.y = var_58->unk_10.pos.y;
            var_D0.z = var_58->unk_10.pos.z;
        }
        set_xyz(&var_90->unk_00[var_8].unk_00, var_D0.x, var_D0.y, var_D0.z);
        var_90->unk_00[var_8].unk_10 = 1;
        var_90->unk_00[var_8].unk_0C = dword_429DB0;
        if (var_D0.x < 0.0f)
            var_D0.x = var_D0.x - flt_429DA4;
        else
            var_D0.x = var_D0.x + flt_429DA4;
        var_D0.y = var_D0.y + flt_429DA8;
        if (var_D0.z < 0.0f)
            var_D0.z = var_D0.z - flt_429DAC;
        else
            var_D0.z = var_D0.z + flt_429DAC;
        set_xyz(&var_90->unk_00[var_8 + 4].unk_00, var_D0.x, var_D0.y, var_D0.z);
        var_90->unk_00[var_8 + 4].unk_10 = 2;
        var_90->unk_00[var_8 + 4].unk_0C = dword_429DB0;
        if (var_8 == 0)
            RwBBoxInitialize(var_94, &var_90->unk_00[var_8].unk_00);
        else
            RwBBoxAddPoint(var_94, &var_90->unk_00[var_8].unk_00);
    }
    var_E0 = var_94->inf.z * 0.33f + var_94->sup.z * 0.66f;
    var_E4 = var_90->unk_00[var_8 + 3].unk_00.y;
    var_E8 = var_94->inf.x * 0.5f;
    set_xyz(&var_90->unk_00[var_8 + 4].unk_00, var_E8, var_E4, var_E0);
    var_90->unk_00[var_8 + 4].unk_10 = 2;
    var_90->unk_00[var_8 + 4].unk_0C = var_90->unk_00[var_8 + 3].unk_0C;
    var_F0 = var_94->inf.z * 0.66f + var_94->sup.z * 0.33f;
    var_F4 = var_90->unk_00[var_8 + 3].unk_00.y;
    var_F8 = var_94->inf.x * 0.5f;
    set_xyz(&var_90->unk_00[var_8 + 5].unk_00, var_F8, var_F4, var_F0);
    var_90->unk_00[var_8 + 5].unk_10 = 2;
    var_90->unk_00[var_8 + 5].unk_0C = var_90->unk_00[var_8 + 3].unk_0C;
    var_100 = var_94->inf.z * 0.33f + var_94->sup.z * 0.66f;
    var_104 = var_90->unk_00[var_8 + 3].unk_00.y;
    var_108 = var_94->sup.x * 0.5f;
    set_xyz(&var_90->unk_00[var_8 + 6].unk_00, var_108, var_104, var_100);
    var_90->unk_00[var_8 + 6].unk_10 = 2;
    var_90->unk_00[var_8 + 6].unk_0C = var_90->unk_00[var_8 + 3].unk_0C;
    var_110 = var_94->inf.z * 0.66f + var_94->sup.z * 0.33f;
    var_114 = var_90->unk_00[var_8 + 3].unk_00.y;
    var_118 = var_94->sup.x * 0.5f;
    set_xyz(&var_90->unk_00[var_8 + 7].unk_00, var_118, var_114, var_110);
    var_90->unk_00[var_8 + 7].unk_10 = 2;
    var_90->unk_00[var_8 + 7].unk_0C = var_90->unk_00[var_8 + 3].unk_0C;
    var_120 = dword_429DB0 / 2.0f + flt_429DA8;
    set_xyz(&var_90->unk_00[var_8 + 8].unk_00, 0.0f, var_120, 0.0f);
    var_90->unk_00[var_8 + 8].unk_10 = 3;
    var_90->unk_00[var_8 + 8].unk_0C = dword_429DB0 * 2.0f;
    unk_450.sub_147710();
    unk_2628 = var_C->unk_140;
    unk_2624 = unk_2628;
    unk_2630 = var_C->unk_144;
    unk_262C = unk_2630;
    unk_2634 = var_C->unk_148;
    var_128 = ((type_14D2C0_10 *)var_10->unk_10)->unk_90;
    unk_DD4 = var_128;
    var_12C = ((type_14D2C0_10 *)var_10->unk_10)->unk_98;
    if (var_12C)
    {
        if (strlen(var_12C) < 0x20)
        {
            strcpy((RwChar *)unk_DD8, var_12C);
        }
        else
        {
            strncpy((RwChar *)unk_DD8, var_12C, 0x1F);
            unk_DD8[0x1F] = 0;
        }
    }
    else
    {
        unk_DD8[0] = 0;
    }
    switch (var_C->unk_EC)
    {
    case 1:
    {
        type_3DF8D8 *var_134;
        RwUInt32 var_138;
        type_3D2E7C *var_13C;
        type_3D2CD0 *var_144;
        type_3DF8D8 *var_14C;

        var_134 = sub_198800(&var_C->unk_C8);
        var_138 = sub_71870();
        unk_1124 = var_138;
        var_13C = vf_098();
        var_13C->sub_70DF0(this, 2);
        var_13C->sub_70E10(var_134->get_unk_18(), 1);
        var_144 = (type_3D2CD0 *)sub_71770(1);
        *(type_439E78_00 *)&unk_1128 = var_144->get_unk_04_h();
        var_144->sub_6CDA0(this, 5);
        var_14C = sub_198800(&var_C->unk_D0);
        if (var_14C)
            var_13C->sub_70F40(var_14C->get_unk_18(), 1);
        var_14C = sub_198800(&var_C->unk_D8);
        if (var_14C)
            unk_2620 = var_14C->get_unk_18();
        sub_40A60(var_13C->sub_71340(), 2, 0, 1, 0);
        sub_35200(var_13C->sub_71340(), 0.0f, 1.0e37f, 6, 0, 0, 0, -1, -1);
        sub_34E20(var_13C->sub_71340());
        sub_32F70(var_13C->sub_71340(), 4, 100.0f, 0);
        ((VehicleTrigger *)var_C)->sub_C1010(var_13C);
        break;
    }
    case 2:
    {
        type_10F710 *var_158;

        var_158 = (type_10F710 *)sub_1745A0(0);
        vf_268(var_158);
    }
    case 3:
    {
        type_3DF8D8 *var_15C;
        RwUInt32 var_160;
        type_3D2E7C *var_164;
        type_3D2CD0 *var_16C;
        type_3DF8D8 *var_174;

        var_15C = sub_198800(&var_C->unk_C8);
        var_160 = sub_71870();
        unk_1124 = var_160;
        var_164 = vf_098();
        var_164->sub_70DF0(this, 2);
        var_164->sub_70E10(var_15C->get_unk_18(), 1);
        var_16C = (type_3D2CD0 *)sub_71770(1);
        *(type_439E78_00 *)&unk_1128 = var_16C->get_unk_04_h();
        var_16C->sub_6CDA0(this, 5);
        var_174 = sub_198800(&var_C->unk_D0);
        if (var_174)
            var_164->sub_70F40(var_174->get_unk_18(), 1);
        var_174 = sub_198800(&var_C->unk_D8);
        if (var_174)
            unk_2620 = var_174->get_unk_18();
        sub_40A60(var_164->sub_71340(), 2, 0, 1, 0);
        sub_35200(var_164->sub_71340(), 0.0f, 1.0e37f, 6, 0, 0, 0, -1, -1);
        ((VehicleTrigger *)var_C)->sub_C1010(var_164);
        break;
    }
    }
    if (var_C->unk_1AC)
    {
        RwMatrixSetIdentityMacro(&var_1C0);
        var_1C4 = (type_712B0 *)unk_344.unk_08;
        var_1C8 = sub_166D40(var_C->unk_1B0, var_C->unk_1B8, &var_1C0, 0, var_1C4, 1, var_C->unk_1C8, var_C->unk_1CC,
                             var_C->unk_1D0, var_C->unk_1E8, var_C->unk_1BC);
        unk_1190.sub_D48D0(var_1C8);
    }
    unk_90.sub_CCC60();
    var_1F8[0] = 0x43464C31; // not an address: a tag
    var_1F8[1] = 0x43464C32; // not an address: a tag
    var_1F8[2] = 0x43465231; // not an address: a tag
    var_1F8[3] = 0x43465232; // not an address: a tag
    var_1F8[4] = 0x434C4C31; // not an address: a tag
    var_1F8[5] = 0x434C4C32; // not an address: a tag
    var_1F8[6] = 0x43525231; // not an address: a tag
    var_1F8[7] = 0x43525232; // not an address: a tag
    var_1F8[8] = 0x43424C31; // not an address: a tag
    var_1F8[9] = 0x43424C32; // not an address: a tag
    var_1F8[10] = 0x43425231; // not an address: a tag
    var_1F8[11] = 0x43425232; // not an address: a tag
    unk_2854 = 0;
    unk_284C = 0.0f;
    unk_2850 = 0.0f;
    var_210.inf.x = 0.0f;
    var_210.inf.y = 0.0f;
    var_210.inf.z = 0.0f;
    var_210.sup.x = 0.0f;
    var_210.sup.y = 0.0f;
    var_210.sup.z = 0.0f;
    for (var_8 = 0; var_8 < 12; var_8++)
    {
        var_214 = &unk_263C[var_8];
        var_214->unk_08 = var_1F8[var_8];
        var_214->unk_00 = 0;
        var_214->unk_04 = var_8;
        var_214->unk_10.sub_D48D0(0);
        var_21C = sub_EC1F0(get_unk_264(), var_1F8[var_8]);
        if (var_21C)
            RwBBoxAddPoint(&var_210, &var_21C->unk_10.pos);
        switch (var_8)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            var_214->unk_0C = 0;
            break;
        default:
            if (var_21C)
            {
                var_214->unk_00 |= 1;
                var_214->unk_00 |= 2;
                var_214->unk_0C = (type_14D180_0C *)var_21C;
                unk_2854 = 1;
                sub_1553E0(var_214, &var_260);
                var_214->unk_14 = var_260.pos;
                var_214->unk_20 = var_260.at;
            }
            else
            {
                var_214->unk_0C = 0;
            }
            break;
        }
    }
    if (unk_2854)
    {
        var_26C = fabs(var_210.inf.x);
        var_278 = fabs(var_210.sup.x);
        if (var_278 > var_26C)
            unk_284C = var_278;
        else
            unk_284C = var_26C;
        var_26C = fabs(var_210.inf.z);
        var_278 = fabs(var_210.sup.z);
        if (var_278 > var_26C)
            unk_2850 = var_278;
        else
            unk_2850 = var_26C;
    }
    if (var_C->unk_1EC.unk_00 || var_C->unk_1EC.unk_04)
    {
        var_28C = sub_198800(&var_C->unk_1EC);
        var_290 = (type_3DFEEC *)var_28C;
        unk_11A0.unk_D14 = var_290->get_unk_24();
        unk_11A0.unk_49C |= 0x1000;
    }
    if (unk_450.unk_108 < 3)
    {
        unk_450.sub_149F80(1);
        unk_7B0.unk_170 = unk_450.unk_170;
    }
    return 1;
}
// match: ?vf_230@type_3DBC78@@UAEXXZ @ 0x0014ED60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes it down (once it is up, unk_2858): its AI, its objects and the AI's
// registrations, the player riding it (kinds 2 and 3), its animation, the
// trigger's named entity, its buffer and its clump; then the entity at
// unk_1190 ends.
void type_3DBC78::vf_230()
{
    type_3DFEEC *var_1C;
    type_10F710 *var_18;
    type_3D3548 *var_14;
    type_712B0 *lv_10;
    type_3D2E7C *var_C;
    type_712B0 *bp_8;
    type_3D3548 *bp_4;

    if (unk_2858)
    {
        lv_10 = get_unk_34C();
        unk_11A0.sub_16C50();
        if (vf_090())
        {
            sub_717B0((type_3D2C88 *)vf_090());
            unk_1128 = 0;
        }
        var_C = vf_098();
        if (var_C)
        {
            sub_330E0(var_C->sub_71340(), 0);
            sub_34E40(var_C->sub_71340());
            sub_35330(var_C->sub_71340());
            sub_40AE0(var_C->sub_71340());
            sub_71970((type_3D2C88 *)var_C);
            unk_1124 = 0;
        }
        switch (((type_712B0_3DBC78 *)lv_10)->unk_EC)
        {
        case 2:
        case 3:
            var_14 = unk_118C.sub_D4910();
            if (var_14)
            {
                var_18 = (type_10F710 *)var_14;
                if (var_18->vf_200() == this)
                    var_18->sub_10F810(0, 0);
            }
        }
        unk_2858 = 0;
        vf_228();
        if (unk_280)
        {
            sub_78870(unk_280);
            unk_280 = 0;
        }
        bp_8 = get_unk_34C();
        if (bp_8->unk_E0.unk_00)
        {
            var_1C = (type_3DFEEC *)sub_198800(&bp_8->unk_E0);
            ((type_D48D0 *)&var_1C->unk_24_id)->sub_D48D0(0);
        }
        if (unk_DB8)
        {
            RwFree(unk_DB8);
            unk_DB8 = 0;
        }
        if (unk_B30.get_unk_08())
            unk_B30.sub_129B10();
    }
    bp_4 = unk_1190.sub_D4910();
    if (bp_4)
        sub_D5A60(bp_4, 0);
}
// match: ?vf_220@type_3DBC78@@UAEXPAUtype_3D3548@@H@Z @ 0x0014EFA0
// Hands arg_0 to the player (its unk_2174) when the player is its
// passenger.
void type_3DBC78::vf_220(type_3D3548 *arg_0, RwInt32 arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_1745A0(0);
    if (var_4 && unk_118C.sub_D4910() == var_4)
        ((type_10F710 *)var_4)->unk_2174.sub_D48D0(arg_0);
}
// match: ?vf_064@type_3DBC78@@UAEHPAUtype_75600@@@Z @ 0x0014EFF0
// A bullet's hit: a player's mounted weapon of kind 2 does a fifth (and
// counts as kind 4); kinds 3, 4 and 6 hurt it when it may be hurt, scaled
// by where the hit lands (its top, a side, the front or the rear); its
// armour takes the damage first, with the armour and death sounds; its
// script hears of it, and its AI takes an enemy shooter as its target.
RwInt32 type_3DBC78::vf_064(type_75600 *arg_0)
{
    RwInt32 var_8;
    type_10F710 *var_10;
    RwReal var_1C;
    type_712B0_3DBC78 *var_24;
    type_10F710 *var_30;
    RwFrame *var_34;
    RwMatrix var_80;
    RwV3d var_8C;
    RwReal var_90;

    if (arg_0->unk_04)
    {
        var_8 = ((type_758F0_08 *)arg_0->unk_04_p)->vf_058();
        var_10 = arg_0->unk_0C ? arg_0->unk_0C->vf_00C() : 0;
        if (var_10 && var_10->unk_1B28 && var_10->unk_210C.sub_D4910()
            && var_10->unk_210C.sub_D4910()->vf_028()
            && var_10->unk_210C.sub_D4910()->vf_028()->unk_3B0 == 2)
        {
            arg_0->unk_28 /= 5.0f;
            var_8 = 4;
        }
        if ((var_8 == 4 || var_8 == 3 || var_8 == 6) && unk_11A0.unk_49C_3)
        {
            var_1C = arg_0->unk_28;
            var_24 = (type_712B0_3DBC78 *)get_unk_34C();
            var_30 = unk_118C.sub_D4910() ? unk_118C.sub_D4910()->vf_00C() : 0;
            var_34 = unk_338.unk_08;
            var_80 = *RwFrameGetMatrix(var_34);
            zero_v3d(&var_80.pos);
            sub_1414C0(&var_8C, arg_0->unk_20, &var_80);
            var_90 = RwV3dDotProduct(&var_8C, &var_80.up);
            if (var_90 > 0.985f)
            {
                sub_19A750("top damage! %3.2f\n", var_1C *= var_24->unk_198);
            }
            else
            {
                var_90 = RwV3dDotProduct(&var_8C, &var_80.at);
                if (var_90 > 0.0f)
                {
                    var_90 = RwV3dDotProduct(&var_8C, &var_80.right);
                    if ((RwReal)fabs((RwDouble)var_90) > 0.25f)
                        sub_19A750("side damage! %3.2f\n", var_1C *= var_24->unk_190);
                    else
                        sub_19A750("front damage! %3.2f\n", var_1C *= var_24->unk_18C);
                }
                else
                {
                    var_90 = RwV3dDotProduct(&var_8C, &var_80.right);
                    if ((RwReal)fabs((RwDouble)var_90) > 0.25f)
                        sub_19A750("side damage! %3.2f\n", var_1C *= var_24->unk_190);
                    else
                        sub_19A750("rear damage! %3.2f\n", var_1C *= var_24->unk_194);
                }
            }
            if (unk_262C > 0)
            {
                unk_262C -= (RwInt32)var_1C;
                if (var_30)
                    unk_1C0.sub_8A980(&dword_4B1B30, this, 4, var_30->sub_CD550(), 0, 0);
                if (unk_262C < 0)
                {
                    unk_2624 += unk_262C;
                    unk_262C = 0;
                }
            }
            else
            {
                if (unk_2624 > 0.0f && unk_2624 - (RwInt32)var_1C <= 0.0f && var_30)
                    unk_1C0.sub_8A980(&dword_4AF020, this, 4, var_30->sub_CD550(), 0, 0);
                unk_2624 -= (RwInt32)var_1C;
                if (unk_2624 < 0)
                    unk_2624 = 0;
                else if (var_30)
                    unk_1C0.sub_8A980(&dword_4B1B30, this, 4, var_30->sub_CD550(), 0, 0);
            }
            sub_6B5F0("HitByBullet", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
            sub_D2AD0(arg_0->unk_0C, arg_0->unk_04);
            if (unk_11A0.unk_1374.sub_D4910() != arg_0->unk_0C && cmp_unk_2C(this, arg_0->unk_0C))
                unk_11A0.sub_18BB0(arg_0->unk_0C);
        }
    }
    return 0;
}
// match: ?vf_068@type_3DBC78@@UAEHPAUtype_758F0@@@Z @ 0x0014F600
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// An explosion that reaches it (and may hurt it; not its own): a player's
// light weapons do little; within its radius and 300 it is pushed away and
// up; its armour takes the damage first, then its health; its script hears
// where it came from and whether from behind, and the HUD marks a hit on
// the player driving it. 1 when it is out of reach.
RwInt32 type_3DBC78::vf_068(type_758F0 *arg_0)
{
    RwV3d var_50;
    RwMatrix *local_44;
    type_758F0_14 var_40;
    RwV3d stk_2C;
    RwV3d *var_20;
    RwV3d *l1C;
    RwV3d m_18;
    RwReal var_C;
    RwReal bp_8;
    type_10F710 *bp_4;

    bp_4 = 0;
    if (arg_0->unk_2C != 0.0f && vf_070(arg_0, 0, 0) && unk_11A0.unk_49C_3)
    {
        if (arg_0->unk_04.sub_D4910() == this)
            return 0;
        if (vf_014())
        {
            bp_4 = arg_0->unk_04.sub_D4910() ? arg_0->unk_04.sub_D4910()->vf_00C() : 0;
            if (bp_4 && arg_0->unk_08_p->vf_058() == 5)
            {
                switch (arg_0->unk_08_p->vf_064())
                {
                case 20:
                case 21:
                case 22:
                    arg_0->unk_2C *= 0.03f;
                }
            }
        }
        l1C = RwMatrixGetPos(arg_0->unk_0C);
        var_20 = &unk_450.unk_170.pos;
        set_xyz(&stk_2C, 0.0f, 200.0f, 0.0f);
        RwV3dSub(&m_18, var_20, l1C);
        bp_8 = RwV3dNormalize(&m_18, &m_18);
        var_C = arg_0->unk_14 + 300.0f;
        if (bp_8 > var_C)
            return 1;
        bp_8 = -(var_C - bp_8) * 0.01f;
        m_18.x = bp_8 * unk_450.unk_24C * m_18.x;
        m_18.y = bp_8 * unk_450.unk_24C * m_18.y;
        m_18.z = bp_8 * unk_450.unk_24C * m_18.z;
        sub_141320(&stk_2C, &stk_2C, &unk_450.unk_170);
        sub_141320(&m_18, &m_18, &unk_450.unk_170);
        vf_264(60, &m_18, &stk_2C);
        bp_4 = unk_118C.sub_D4910() ? unk_118C.sub_D4910()->vf_00C() : 0;
        if (unk_262C > 0)
        {
            unk_262C -= (RwInt32)arg_0->unk_2C;
            if (unk_262C < 0)
            {
                unk_2624 += unk_262C;
                unk_262C = 0;
            }
        }
        else
        {
            unk_2624 -= (RwInt32)arg_0->unk_2C;
            if (unk_2624 < 0)
                unk_2624 = 0;
        }
        local_44 = &unk_450.unk_170;
        var_50 = *RwMatrixGetPos(local_44);
        RwV3dSubMacro(&var_50, &var_50, l1C);
        var_40.unk_00 = l1C->x;
        var_40.unk_04 = l1C->y;
        var_40.unk_08 = l1C->z;
        var_40.unk_0C = arg_0->unk_14;
        var_40.unk_10 = RwV3dDotProductMacro(&local_44->at, &var_50) <= 0 ? 1 : 0;
        sub_6B5F0("HitByExplosion", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)(&var_40), 5, 1, 0);
        sub_D2AD0(arg_0->unk_04.sub_D4910(), arg_0->unk_08);
        if (bp_4 && !bp_4->unk_4D0 && dword_4B9190)
            dword_4B9190->sub_DFB40(0, RwMatrixGetPos(arg_0->unk_0C));
    }
    return 0;
}
// match: ?vf_060@type_3DBC78@@UAEHPAUtype_3D3548@@@Z @ 0x0014FA40
RwInt32 type_3DBC78::vf_060(type_3D3548 *arg_0)
{
    return vf_06C(arg_0);
}
// match: ?vf_06C@type_3DBC78@@UAEHPAUtype_3D3548@@@Z @ 0x0014FA60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A collision with the entity arg_0: tells the vehicle's script
// ("CollisionByEntityNotification", and "CollisionByPlayerNotification"
// for a player) the other's handle and how the two face each other (their
// at and right vectors' dots).
RwInt32 type_3DBC78::vf_06C(type_3D3548 *arg_0)
{
    RwFrame *var_20;
    RwMatrix *l1C;
    RwMatrix *m_18;
    RwReal ebp_14;
    RwReal lv_10;
    RwReal var_C[3];

    var_20 = unk_338.unk_08;
    m_18 = RwFrameGetLTM(var_20);
    var_20 = arg_0->get_unk_340();
    l1C = RwFrameGetLTM(var_20);
    ebp_14 = RwV3dDotProduct(&m_18->at, &l1C->at);
    lv_10 = RwV3dDotProduct(&m_18->right, &l1C->right);
    *(RwInt32 *)&var_C[0] = arg_0->vf_09C();
    var_C[1] = ebp_14;
    var_C[2] = lv_10;
    sub_6B5F0("CollisionByEntityNotification", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)var_C, 3, 1, 0);
    if (arg_0->vf_00C())
        sub_6B5F0("CollisionByPlayerNotification", (type_67620 *)(vf_098()), 0, 0, (RwInt32 *)var_C, 3, 1, 0);
    return 0;
}
// match: ?vf_0FC@type_3DBC78@@UAEMXZ @ 0x0014FB90
RwReal type_3DBC78::vf_0FC()
{
    if (unk_1158)
        return -0.99999964f;
    return unk_1150;
}
// match: ?vf_100@type_3DBC78@@UAEMXZ @ 0x0014FBC0
RwReal type_3DBC78::vf_100()
{
    if (unk_1158)
        return -0.99999964f;
    return unk_1154;
}
// match: ?vf_104@type_3DBC78@@UAEXPAURwMatrixTag@@@Z @ 0x0014FBF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its eye's matrix into *arg_0: bone 2 of its animation when it has one,
// else its clump's frame raised by 150.
void type_3DBC78::vf_104(RwMatrix *arg_0)
{
    RwV3d var_24;
    RwMatrix *bp_18;
    RwInt32 var_14;
    RpHAnimHierarchy *lv_10;
    RpClump *var_C;
    RwInt32 bp_8;
    RwFrame *bp_4;

    var_C = unk_25C.unk_08;
    bp_4 = RpClumpGetFrame(var_C);
    bp_8 = 0;
    if (unk_284 && unk_28_13)
    {
        lv_10 = get_unk_284()->unk_18;
        bp_18 = RpHAnimHierarchyGetMatrixArray(lv_10);
        var_14 = RpHAnimIDGetIndex(lv_10, 2);
        if (var_14 != -1)
        {
            *arg_0 = bp_18[var_14];
            bp_8 = 1;
        }
    }
    if (!bp_8)
    {
        var_24.x = var_24.z = 0.0f;
        var_24.y = 150.0f;
        *arg_0 = *RwFrameGetLTM(bp_4);
        RwMatrixTranslate(arg_0, &var_24, rwCOMBINEPOSTCONCAT);
    }
}
// match: ?vf_108@type_3DBC78@@UAEXPAURwV3d@@@Z @ 0x0014FCE0
// Its eye's position (vf_104's matrix).
void type_3DBC78::vf_108(RwV3d *arg_0)
{
    RwMatrix var_50;

    vf_104(&var_50);
    *arg_0 = var_50.pos;
}
// match: ?vf_110@type_3DBC78@@UAEXPAURwV3d@@PAUtype_3D3548@@H@Z @ 0x0014FD30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The point others aim at: bone 100 of its animation when it has one, else
// its position; raised by half its height.
void type_3DBC78::vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    RwMatrix *var_C;
    RwInt32 bp_8;
    RpHAnimHierarchy *bp_4;

    if (unk_284 && unk_28_13)
    {
        bp_4 = get_unk_284()->unk_18;
        var_C = RpHAnimHierarchyGetMatrixArray(bp_4);
        bp_8 = RpHAnimIDGetIndex(bp_4, 100);
        *arg_0 = var_C[bp_8].pos;
        arg_0->y += unk_48 * 0.5f;
    }
    else
    {
        *arg_0 = *sub_CD550();
        arg_0->y += unk_48 * 0.5f;
    }
}
// match: ?vf_10C@type_3DBC78@@UAEMXZ @ 0x0014FE00
RwReal type_3DBC78::vf_10C()
{
    if (unk_11A0.unk_520)
        return unk_1160 * unk_1164;
    return unk_115C * unk_1164;
}
// match: ?vf_114@type_3DBC78@@UAEMXZ @ 0x0014FE40
RwReal type_3DBC78::vf_114()
{
    return unk_1160 * unk_1168;
}
// match: ?vf_0C8@type_3DBC78@@UAEPAURwV3d@@XZ @ 0x0014FE60
RwV3d *type_3DBC78::vf_0C8()
{
    return &unk_450.unk_124;
}
// match: ?vf_16C@type_3DBC78@@UAEHHH@Z @ 0x0014FE80
// Sets AI parameter arg_0 to arg_4, a float's bits as the script passes
// them; 7 is refused.
RwInt32 type_3DBC78::vf_16C(RwInt32 arg_0, RwInt32 arg_4)
{
    RwInt32 var_4;

    var_4 = 1;
    switch (arg_0)
    {
    case 0:
        unk_1174 = *(RwReal *)&arg_4 * 0.5f;
        break;
    case 1:
        unk_1178 = *(RwReal *)&arg_4 * 0.5f;
        break;
    case 2:
        unk_DD0 = arg_4;
        unk_1150 = cos(*(RwReal *)&arg_4 *= 0.0087266462f);
        break;
    case 3:
        *(RwReal *)&arg_4 = 0.0087266462f;
        unk_1154 = cos(*(RwReal *)&arg_4);
        break;
    case 4:
        unk_115C = *(RwReal *)&arg_4 * 100.0f;
        break;
    case 5:
        unk_1160 = *(RwReal *)&arg_4 * 100.0f;
        break;
    case 6:
        unk_1168 = *(RwReal *)&arg_4;
        break;
    case 7:
        var_4 = 0;
    }
    return var_4;
}
// match: ?sub_14FFA0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x0014FFA0
RpAtomic *sub_14FFA0(RpAtomic *arg_0, void *arg_4)
{
    arg_0->boundingSphere.radius = flt_429DA0 * arg_0->boundingSphere.radius;
    return arg_0;
}
// match: ?vf_2F8@type_3DBC78@@UAEXPAUtype_3DF8D8@@PAX@Z @ 0x0014FFC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Takes the model arg_0 when its trigger is a vehicle's (kind 7): the
// model must be of kind 3 ("VehicleEntity" warns otherwise). Its clump's
// atomics' spheres are doubled; a new frame under its own carries unk_B30;
// its guns take the model; its tracks' materials are found.
void type_3DBC78::vf_2F8(type_3DF8D8 *arg_0, void *arg_4)
{
    type_712B0 *var_14;
    RpClump *lv_10;
    type_3DF8D8 *var_C;
    RwInt32 bp_8;
    RwFrame *bp_4;

    if (get_unk_34C())
    {
        var_14 = (type_712B0 *)unk_344.unk_08;
        if (var_14->vf_008() != 7)
            return;
        var_C = ((type_3DFE7C *)arg_0)->sub_1954D0();
        if (!var_C || var_C->vf_008() != 3)
        {
            sub_D3FB0("VehicleEntity", arg_4, &arg_0->unk_04);
            return;
        }
        vf_224(var_C, 0, &bp_8);
        unk_290 = ((type_3DF8D8_3 *)var_C)->get_unk_44();
        RpClumpForAllAtomics(get_unk_264(), sub_14FFA0, 0);
        if (unk_B30.get_unk_08())
            unk_B30.sub_129B10();
        bp_4 = RwFrameCreate();
        if (bp_4)
        {
            unk_B30.sub_129A70(bp_4);
            RwFrameSetIdentity(unk_B30.get_unk_08());
            RwFrameAddChild(get_unk_340(), bp_4);
            RwFrameUpdateObjects(bp_4);
        }
        unk_DFC.sub_15B2A0(arg_0, arg_4);
        bp_4 = unk_338.unk_08;
        unk_184 = (RwInt32)RwFrameGetMatrix(bp_4);
        lv_10 = unk_25C.unk_08;
        unk_B10.unk_00 = 0;
        unk_B10.unk_04 = 0.0f;
        unk_B18.unk_00 = 0;
        unk_B18.unk_04 = 0.0f;
        RpClumpForAllAtomics(lv_10, sub_1501A0, this);
    }
}
// match: ?sub_1501A0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x001501A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A clump callback: the atomic's materials searched for the tracks
// (sub_150200); an atomic with one gets its material effects.
RpAtomic *sub_1501A0(RpAtomic *arg_0, void *arg_4)
{
    RwInt32 var_10;
    type_150200 var_C;
    RpGeometry *bp_4;

    bp_4 = RpAtomicGetGeometry(arg_0);
    var_10 = 0;
    var_C.unk_00 = (type_3DBC78 *)arg_4;
    var_C.unk_04 = &var_10;
    if (bp_4)
        RpGeometryForAllMaterials(bp_4, sub_150200, &var_C);
    if (var_10)
        RpMatFXAtomicEnableEffects(arg_0);
    return arg_0;
}
// match: ?sub_150200@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x00150200
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A material callback: a "vtrack" texture (any case) is a track's, the
// left one when "l" follows; it is noted and, unless it has one, given the
// UV animation sub_159AC0 hands out.
RpMaterial *sub_150200(RpMaterial *arg_0, void *arg_4)
{
    RwChar *var_18;
    RwInt32 var_14;
    RwTexture *lv_10;
    type_3DBC78 *var_C;
    type_150200 *bp_8;
    RwInt32 *bp_4;

    bp_8 = (type_150200 *)arg_4;
    var_C = bp_8->unk_00;
    bp_4 = bp_8->unk_04;
    lv_10 = arg_0->texture;
    if (lv_10)
    {
        var_18 = lv_10->name;
        RwChar var_24[] = "vtrack";
        for (var_14 = 0; var_14 < (RwInt32)strlen(var_24); var_14++)
        {
            if (tolower(var_24[var_14]) != tolower(var_18[var_14]))
                break;
        }
        if (var_14 == strlen(var_24))
        {
            if (tolower(var_18[var_14]) == 'l')
                var_C->unk_B10.unk_00 = arg_0;
            else
                var_C->unk_B18.unk_00 = arg_0;
            *bp_4 = 1;
            if (!RpMaterialUVAnimExists(arg_0))
            {
                RtAnimAnimation *var_28 = sub_159AC0();
                if (var_28)
                {
                    RpMatFXMaterialSetEffects(arg_0, rpMATFXEFFECTUVTRANSFORM);
                    RpMaterialSetUVAnim(arg_0, var_28, 0);
                }
            }
        }
    }
    return arg_0;
}
// match: ?sub_150350@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x00150350
// Its animation's procedural track (vf_038 starts it; arg_8 is the
// vehicle). At its start it builds its pose key once: every node's
// rotation relative to its frame, the root (unk_D9C) translated, then
// reuses it. Each step it turns its wheels, its steered wheels and its
// track wheels, and the turret bone unk_B20 by unk_B24.
void sub_150350(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C)
{
    type_3DBC78 *var_4;
    type_7CBD0 *var_8;
    RwFrame *var_10;
    RpHAnimHierarchy *var_18;
    RwMatrix *var_1C;
    RtQuat *var_2C;
    type_7CBD0_hdr *var_30;
    type_7CBD0_t *var_34;
    RwMatrix var_80;
    RwInt32 var_84;
    RwMatrix var_D0;
    RwInt32 var_D4;
    RtQuat *var_D8;
    RpHAnimHierarchy *var_E4;
    RtQuat *var_E8;
    RtQuat *var_EC;
    RwMatrix var_140;
    RwV3d var_14C;
    RwV3d var_158;
    RwReal var_160;

    var_4 = (type_3DBC78 *)arg_8;
    var_8 = (type_7CBD0 *)arg_4->unk_144;
    if (arg_C && !var_4->unk_DB8)
    {
        var_10 = var_4->get_unk_340();
        var_18 = var_4->get_unk_284()->unk_18;
        var_1C = RpHAnimHierarchyGetMatrixArray(var_18);
        var_4->unk_DBC = var_18->numNodes * sizeof(RtQuat) + sizeof(type_7CBD0_hdr);
        var_4->unk_DB8 = (type_7CBD0_hdr *)RwMalloc(var_4->unk_DBC, 0x34251); // not an address: a memory hint
        memset(var_4->unk_DB8, 0, var_4->unk_DBC);
        var_4->unk_DB8->unk_00 = var_18->numNodes;
        var_4->unk_DB8->unk_01 = var_18->numNodes;
        var_4->unk_DB8->unk_02 = 1;
        var_4->unk_DB8->unk_08 = (RwUInt64)-1;
        var_4->unk_DB8->unk_10 = var_4->unk_D9C > -1 ? (RwUInt64)(1 << var_4->unk_D9C) : 0;
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_DB8);
        var_2C = var_8->unk_10;
        var_30 = var_4->unk_DB8;
        var_34 = (type_7CBD0_t *)&var_8->unk_10[var_30->unk_00];
        RwMatrixInvert(&var_80, RwFrameGetLTM(var_10));
        for (var_84 = 0; var_84 < var_18->numNodes; var_84++)
        {
            var_D0 = var_80;
            var_D4 = RpHAnimIDGetIndex(var_18, var_18->pNodeInfo[var_84].nodeID);
            RwMatrixTransform(&var_D0, &var_1C[var_D4], rwCOMBINEPRECONCAT);
            RtQuatConvertFromMatrix(&var_2C[var_84], &var_D0);
        }
        for (var_84 = 0; var_84 < var_4->unk_DB8->unk_02; var_84++)
        {
            var_34[var_84].unk_00.z = 0.0f;
            var_34[var_84].unk_00.y = 0.0f;
            var_34[var_84].unk_00.x = 0.0f;
        }
        var_D8 = (RtQuat *)(var_4->unk_DB8 + 1);
        memcpy(var_D8, var_2C, var_18->numNodes * sizeof(RtQuat));
        var_8->unk_04 = var_4->unk_DB8;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else if (arg_C && var_4->unk_DB8)
    {
        var_E4 = var_4->get_unk_284()->unk_18;
        var_E8 = (RtQuat *)(var_4->unk_DB8 + 1);
        var_EC = var_8->unk_10;
        memcpy(var_EC, var_E8, var_E4->numNodes * sizeof(RtQuat));
        sub_807C0((RtAnimInterpolator *)arg_4, var_4->unk_DB8);
        var_8->unk_04 = var_4->unk_DB8;
        var_8->unk_08 = sub_EC270(var_4->get_unk_264());
    }
    else
    {
        var_140 = *RwFrameGetMatrix(var_4->unk_B30.get_unk_08());
        var_4->sub_153890((type_153890 *)var_8, var_4->unk_B2C, &var_140, 1);
        var_14C.x = 1.0f;
        var_14C.y = 0.0f;
        var_14C.z = 0.0f;
        var_158.x = 0.0f;
        var_158.y = 1.0f;
        var_158.z = 0.0f;
        var_4->unk_DA8 += var_4->unk_DA0 * 57.295784f;
        var_4->unk_DAC += var_4->unk_DA4 * 57.295784f;
        for (var_84 = 0; var_84 < var_4->unk_B3C; var_84++)
        {
            if (var_4->unk_C08[var_4->unk_B40[var_84]] == 1)
                var_4->sub_17FC00(var_8, var_4->unk_B40[var_84], 0, &var_14C, var_4->unk_DA8, 1);
            else
                var_4->sub_17FC00(var_8, var_4->unk_B40[var_84], 0, &var_14C, var_4->unk_DAC, 1);
        }
        var_160 = (var_4->unk_450.unk_248 > 1.0f ? 1.0f : (RwReal)(RwDouble)var_4->unk_450.unk_248) * 45.0f;
        for (var_84 = 0; var_84 < var_4->unk_CD0; var_84++)
            var_4->sub_17FC00(var_8, var_4->unk_CD4[var_84], 0, &var_158, var_160, 1);
        for (var_84 = 0; var_84 < var_4->unk_CD0; var_84++)
        {
            if (var_4->unk_D38[var_4->unk_CD4[var_84]] == 1)
                var_4->sub_17FC00(var_8, var_4->unk_CD4[var_84], 0, &var_14C, var_4->unk_DA8, 0);
            else
                var_4->sub_17FC00(var_8, var_4->unk_CD4[var_84], 0, &var_14C, var_4->unk_DAC, 0);
        }
        if (var_4->unk_B20 != -1)
            var_4->sub_17FC00(var_8, var_4->unk_B20, 0, &var_158, var_4->unk_B24, 1);
    }
}
// match: ?vf_038@type_3DBC78@@UAEXM@Z @ 0x00150A70
// Its animation's procedural track (sub_150350) started once, then its AI
// steps by arg_0.
void type_3DBC78::vf_038(RwReal arg_0)
{
    if (!unk_DB4)
    {
        get_unk_284()->sub_794C0(0);
        unk_DB4 = get_unk_284()->sub_79930(sub_150350, 1.0f, 1.0f);
        ((type_78AC0 *)get_unk_284())->sub_6DF40();
        unused_slot();
    }
    unk_11A0.sub_17190(arg_0);
}
// match: ?sub_150B00@@YAXXZ @ 0x00150B00
void sub_150B00()
{
    dword_4B86F8 |= 8;
}
// match: ?vf_03C@type_3DBC78@@UAEXM@Z @ 0x00150B20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The step arg_0: its guns, its seats (kinds 2 and 3); when it is destroyed
// with the player driving (who is not already leaving) the screen fades and
// the sound goes; its health regained; its AI; then the entity's own step.
void type_3DBC78::vf_03C(RwReal arg_0)
{
    type_10F710 *var_C;
    type_3D3548 *bp_8;
    type_712B0 *bp_4;

    bp_4 = get_unk_34C();
    unk_DFC.sub_15B510(arg_0);
    switch (((type_712B0_3DBC78 *)bp_4)->unk_EC)
    {
    case 2:
    case 3:
        vf_2FC(arg_0);
    }
    bp_8 = unk_118C.sub_D4910();
    if (unk_2624 < 1 && bp_8)
    {
        var_C = (type_10F710 *)bp_8;
        if (var_C->vf_200() == this && !var_C->unk_19F8)
        {
            var_C->unk_19F8 = 2;
            sub_1252E0(sub_150B00, 1);
            sub_124EE0(2.0f, 1);
        }
    }
    if (unk_2624 < unk_2628 && unk_2624)
    {
        unk_2624 += (RwInt32)unk_2634;
        if (unk_2624 > unk_2628)
            unk_2624 = unk_2628;
    }
    sub_16D7F0(0x18);
    unk_11A0.sub_172F0(arg_0);
    sub_16D850(0x18);
    type_3D3548::vf_03C(arg_0);
}
// match: ?vf_040@type_3DBC78@@UAEXM@Z @ 0x00150C90
void type_3DBC78::vf_040(RwReal arg_0)
{
    RwMatrix var_60;
    RwMatrix var_A0;
    RpHAnimHierarchy *var_A8;
    RwMatrix var_F0;
    RtQuat var_100;
    RwReal var_104;
    RwReal var_108;
    RwV3d var_118;
    RwV3d var_124;
    RwV3d var_130;
    type_712B0_3DBC78 *var_138;
    RwV3d var_14C;
    RwV3d var_158;
    RwV3d var_164;

    if (!get_unk_284()->sub_76E00(unk_DB4))
    {
        unk_B28 = 0;
        type_3D3548::vf_20C((type_D05C0 *)&unk_C0, arg_0, &unk_10C, &unk_134);
        if (get_unk_340())
            type_3D3548::vf_214((type_D05C0 *)&unk_C0, get_unk_340(), arg_0);
        zero_v3d(&unk_D8_v);
        zero_v3d(&unk_F0_v);
        zero_v3d(&unk_450.unk_124);
        zero_v3d(&unk_450.unk_130);
        var_60 = unk_450.unk_170;
        RwMatrixInvert(&var_A0, &var_60);
        var_A8 = get_unk_284()->unk_18;
        unk_450.unk_170 = var_A8->pMatrixArray[unk_B2C];
        unk_7B0 = unk_450;
        RwMatrixMultiply(&var_F0, &unk_450.unk_170, &var_A0);
        RtQuatConvertFromMatrix(&var_100, &var_F0);
        unk_450.unk_130.z = 0.0f;
        unk_450.unk_130.x = 0.0f;
        var_104 = var_100.real;
        var_108 = RwV3dLength((RwV3d *)&var_100.imag);
        unk_450.unk_130.y = 2.0f * (RwReal)atan2(var_108, var_104);
        unk_450.unk_124 = var_F0.pos;
        unk_450.unk_148 = var_F0.pos;
        vf_234();
        var_118 = ((RwMatrix *)unk_184)->pos;
        var_118.y = var_118.y + 50.0f;
        var_124.x = 0.0f;
        var_124.y = -1.0f;
        var_124.z = 0.0f;
        var_130 = ((RwMatrix *)unk_184)->at;
        sub_1279C0(&var_118, &var_124, &var_130, unk_450.unk_2D0[0].distance * 2.5f * unk_80,
                   unk_450.unk_2D0[2].distance * 2.5f * unk_80, 0, 0);
    }
    else
    {
        if (!unk_B28 && unk_450.unk_108 < 3 && unk_450.unk_104)
        {
            unk_450.sub_149F80(1);
            unk_7B0.unk_170 = unk_450.unk_170;
        }
        unk_B28 = 1;
        var_138 = (type_712B0_3DBC78 *)get_unk_34C();
        unk_450.sub_147B50(var_138, this, arg_0);
        unk_7B0.sub_148F60(this, &unk_450, arg_0);
        *RwFrameGetMatrix(get_unk_340()) = unk_7B0.unk_170;
        RwFrameUpdateObjects(get_unk_340());
        if ((dword_4B87D8 & 0x3F) == 0x3F)
        {
            RwMatrixOrthoNormalize(&unk_450.unk_170, &unk_450.unk_170);
            RwMatrixOrthoNormalize(&unk_7B0.unk_170, &unk_7B0.unk_170);
        }
        vf_234();
        var_14C = unk_7B0.unk_170.pos;
        var_14C.y = var_14C.y + 50.0f;
        var_158.x = 0.0f;
        var_158.y = -1.0f;
        var_158.z = 0.0f;
        var_164 = unk_7B0.unk_170.at;
        sub_1279C0(&var_14C, &var_158, &var_164, unk_450.unk_2D0[0].distance * 2.5f * unk_80,
                   unk_450.unk_2D0[2].distance * 2.5f * unk_80, 0, 0);
    }
}
// match: ?vf_2FC@type_3DBC78@@UAEXM@Z @ 0x00151270
void type_3DBC78::vf_2FC(RwReal arg_0)
{
    type_712B0 *var_4;

    var_4 = get_unk_34C();
    ((type_712B0_3DBC78 *)var_4)->unk_118 = ((type_712B0_3DBC78 *)var_4)->unk_104;
}
// match: ?vf_264@type_3DBC78@@UAEXHPAURwV3d@@0@Z @ 0x001512C0
// Starts a push of arg_0 steps: the force arg_4 (a quarter of it) at
// arg_8, fading by its strength a step.
void type_3DBC78::vf_264(RwInt32 arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    unk_1104 = arg_0;
    unk_1108 = *arg_4;
    unk_1108.x *= 0.25f;
    unk_1108.y *= 0.25f;
    unk_1108.z *= 0.25f;
    RwV3dScale(&unk_1108, &unk_1108, flt_429DB4);
    unk_1114 = *arg_8;
    unk_1120 = RwV3dLength((RwV3d *)arg_4);
}
// match: ?vf_268@type_3DBC78@@UAEXPAUtype_10F710@@@Z @ 0x001513C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The player arg_0 gets in: its frame goes under the vehicle's at the
// seat, it is the passenger, and the getting-in sound plays.
void type_3DBC78::vf_268(type_10F710 *arg_0)
{
    RwFrame *var_C;
    RwFrame *bp_8;
    type_712B0 *bp_4;

    var_C = arg_0->get_unk_340();
    bp_8 = get_unk_340();
    bp_4 = get_unk_34C();
    RwFrameTranslate(var_C, &((type_712B0_3DBC78 *)bp_4)->unk_104, rwCOMBINEREPLACE);
    RwFrameAddChild(bp_8, var_C);
    unk_118C.sub_D48D0(arg_0);
    arg_0->sub_10F810(this, 0);
    unk_1C0.sub_8A980(&unk_3D4.unk_30, this, 4, arg_0->sub_CD550(), 0, 0);
    dword_4D5164 = 0;
}
// match: ?vf_270@type_3DBC78@@UAEXXZ @ 0x00151490
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The player gets out: its view restored, it leaves the vehicle, the
// getting-out sound plays and the HUD resets.
void type_3DBC78::vf_270()
{
    type_3D3548 *var_8;
    type_10F710 *l4;

    var_8 = unk_118C.sub_D4910();
    l4 = var_8->vf_00C();
    sub_153B30();
    unk_450.unk_244 = 0.0f;
    unk_450.unk_248 = 0.0f;
    sub_151550();
    l4->sub_10F810(0, 0);
    l4->sub_FF030();
    unk_118C.sub_D48D0(0);
    unk_1C0.sub_8A980(&unk_3D4.unk_38, this, 4, l4->sub_CD550(), 0, 0);
    if (dword_4B9190)
        dword_4B9190->sub_E0CC0();
}
// match: ?sub_151550@@YAXXZ @ 0x00151550
void sub_151550()
{
    type_10F710 *var_4;

    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4)
    {
        var_4->unk_534 = var_4->unk_4EC;
        var_4->unk_4E0 = var_4->unk_4EC;
        var_4->unk_4E4 = var_4->unk_4EC;
        var_4->unk_4E8 = 0;
    }
}
// match: ?vf_26C@type_3DBC78@@UAEXPAUtype_10F710@@@Z @ 0x001515B0
// The player arg_0 takes its mounted weapon (unk_1190): the HUD shows it.
void type_3DBC78::vf_26C(type_10F710 *arg_0)
{
    type_3DC9B0 *var_4;

    var_4 = (type_3DC9B0 *)unk_1190.sub_D4910();
    if (var_4)
    {
        var_4->sub_168820(arg_0);
        arg_0->sub_1090F0(7);
        arg_0->unk_210C.sub_D48D0(var_4);
        if (dword_4B9190)
            dword_4B9190->sub_DEB80(2);
        var_4->unk_47C = 0;
        var_4->unk_48C = 0;
    }
}
// match: ?vf_274@type_3DBC78@@UAEXXZ @ 0x00151630
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The player leaves its mounted weapon.
void type_3DBC78::vf_274()
{
    type_3D3548 *var_8;
    type_3DC9B0 *l4;

    l4 = (type_3DC9B0 *)unk_1190.sub_D4910();
    if (l4)
    {
        var_8 = l4->unk_5C0.sub_D4910();
        if (var_8->unk_2C_4)
        {
            l4->unk_48C = 1;
            l4->sub_168A90((type_10F710 *)var_8);
            ((type_10F710 *)var_8)->sub_1090F0(0);
            if (dword_4B9190)
                dword_4B9190->sub_DEB80(0);
            ((type_10F710 *)var_8)->sub_10F7E0(4, 0);
        }
    }
}
// match: ?vf_2C8@type_3DBC78@@UAEXPAUtype_10F710@@HHHH@Z @ 0x001516C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The player arg_0 rides as a passenger at (arg_8, arg_C, arg_10) from the
// tag arg_4 of its clump (or from its frame): its frame goes under the
// vehicle's, and the getting-in sound plays.
void type_3DBC78::vf_2C8(type_10F710 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10)
{
    RwFrame *var_18;
    RwV3d var_14;
    RwFrame *var8;
    type_EC1F0 *l4;

    var_18 = arg_0->get_unk_340();
    var8 = get_unk_340();
    l4 = sub_EC1F0(get_unk_264(), arg_4);
    if (l4)
    {
        RwV3d var_24 = {(RwReal)arg_8 + l4->unk_10.pos.x, (RwReal)arg_C + l4->unk_10.pos.y,
                        (RwReal)arg_10 + l4->unk_10.pos.z};
        var_14 = var_24;
    }
    else
    {
        RwV3d var_30 = {(RwReal)arg_8, (RwReal)arg_C, (RwReal)arg_10};
        var_14 = var_30;
    }
    RwFrameTranslate(var_18, &var_14, rwCOMBINEREPLACE);
    RwFrameAddChild(var8, var_18);
    unk_118C.sub_D48D0(arg_0);
    arg_0->sub_10F810(this, 1);
    unk_1C0.sub_8A980(&unk_3D4.unk_30, this, 4, arg_0->sub_CD550(), 0, 0);
}
// match: ?vf_2CC@type_3DBC78@@UAEXXZ @ 0x001517F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The passenger gets out.
void type_3DBC78::vf_2CC()
{
    RwV3d var_18;
    RwFrame *var_C;
    type_3D3548 *bp_8;
    type_10F710 *bp_4;

    bp_8 = unk_118C.sub_D4910();
    bp_4 = bp_8->vf_00C();
    sub_153B30();
    unk_450.unk_244 = 0.0f;
    unk_450.unk_248 = 0.0f;
    bp_4->sub_10F810(0, 0);
    unk_118C.sub_D48D0(0);
    unk_1C0.sub_8A980(&unk_3D4.unk_38, this, 4, bp_4->sub_CD550(), 0, 0);
    var_C = bp_4->get_unk_340();
    zero_v3d(&var_18);
    RwFrameTranslate(var_C, &var_18, rwCOMBINEPRECONCAT);
    bp_4->sub_FF030();
    if (dword_4B9190)
        dword_4B9190->sub_E0CC0();
}
// match: ?vf_0C0@type_3DBC78@@UAEXPAURwV3d@@@Z @ 0x001518E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Moves it to arg_0: its first body's position, and its animation's two
// matrices by as much.
void type_3DBC78::vf_0C0(RwV3d *arg_0)
{
    RwMatrix *var_18;
    RwV3d var_14;
    RwMatrix *var8;
    RwV3d *l4;

    l4 = &unk_450.unk_170.pos;
    if (unk_284)
    {
        var_14.x = arg_0->x - l4->x;
        var_14.y = arg_0->y - l4->y;
        var_14.z = arg_0->z - l4->z;
        var_18 = &unk_284->unk_100;
        var_18->pos.x += var_14.x;
        var_18->pos.y += var_14.y;
        var_18->pos.z += var_14.z;
        var8 = &unk_284->unk_140;
        var8->pos.x += var_14.x;
        var8->pos.y += var_14.y;
        var8->pos.z += var_14.z;
    }
    *l4 = *arg_0;
    RwFrameUpdateObjects(get_unk_340());
}
// match: ?vf_0D4@type_3DBC78@@UAEXPAURtQuat@@@Z @ 0x001519E0
// Turns it to the orientation arg_0, keeping its position.
void type_3DBC78::vf_0D4(RtQuat *arg_0)
{
    RwMatrix var_50;

    RwMatrixSetIdentity(&var_50);
    RtQuatConvertToMatrix(arg_0, &var_50);
    var_50.pos = unk_450.unk_170.pos;
    RwMatrixTransform(&unk_450.unk_170, &var_50, rwCOMBINEREPLACE);
    RwFrameUpdateObjects(get_unk_340());
}
// match: ?vf_0D0@type_3DBC78@@UAEXPAURwV3d@@@Z @ 0x00151C20
// Turns it to face the point arg_0.
void type_3DBC78::vf_0D0(RwV3d *arg_0)
{
    RwV3d var_10;
    RwMatrix var_60;

    RwV3dSub(&var_10, arg_0, sub_CD550());
    RwV3dNormalize(&var_10, &var_10);
    sub_140CE0(&var_60, &unk_450.unk_170.pos, &var_10);
    RwMatrixTransform(&unk_450.unk_170, &var_60, rwCOMBINEREPLACE);
    RwFrameUpdateObjects(get_unk_340());
}
// match: ?vf_0D8@type_3DBC78@@UAEXPAURwV3d@@@Z @ 0x00151CF0
// Turns it to face along arg_0 (unless it is nearly zero).
void type_3DBC78::vf_0D8(RwV3d *arg_0)
{
    RwFrame *var_C;
    RwV3d var_20;
    RwMatrix var_60;

    var_C = get_unk_340();
    if (fabs(RwV3dDotProduct(arg_0, arg_0)) > 0.0001f)
    {
        RwV3dNormalize(&var_20, arg_0);
        sub_140CE0(&var_60, &unk_450.unk_170.pos, &var_20);
        RwMatrixTransform(&unk_450.unk_170, &var_60, rwCOMBINEREPLACE);
        RwFrameUpdateObjects(var_C);
    }
}
// match: ?vf_278@type_3DBC78@@UAEXH@Z @ 0x00151DC0
// Starts (arg_0) or stops its engine: physics on or off, and its start and
// running sounds (from the player when the player drives) or its stop.
void type_3DBC78::vf_278(RwInt32 arg_0)
{
    type_3D3548 *var_4;

    if (arg_0 == unk_1134)
        return;
    unk_1134 = arg_0;
    var_4 = sub_1745A0(0);
    if (unk_1134)
    {
        vf_290(0);
        if (unk_118C.sub_D4910() == var_4)
        {
            unk_1C0.sub_8A980(&unk_3D4.unk_00, this, 4, var_4->sub_CD550(), 0, 0);
            unk_1144 = unk_1C0.sub_8A980(&unk_3D4.unk_10, this, 4, var_4->sub_CD550(), 0, 0);
        }
        else
        {
            unk_1C0.sub_8A980(&unk_3D4.unk_00, this, 4, sub_CD550(), 0, 0);
            unk_1144 = unk_1C0.sub_8A980(&unk_3D4.unk_10, this, 4, sub_CD550(), 0, 0);
        }
    }
    else
    {
        vf_290(1);
        sub_153B30();
        if (unk_118C.sub_D4910() == var_4)
            unk_1C0.sub_8A980(&unk_3D4.unk_08, this, 4, var_4->sub_CD550(), 0, 0);
        else
            unk_1C0.sub_8A980(&unk_3D4.unk_08, this, 4, sub_CD550(), 0, 0);
    }
}
// match: ?vf_280@type_3DBC78@@UAEXM@Z @ 0x00151F80
// Steers by arg_0, within its limit; nothing while its engine is off or it
// may not move.
void type_3DBC78::vf_280(RwReal arg_0)
{
    if (!unk_1134 || !unk_DC4)
    {
        unk_450.unk_244 = 0.0f;
        unk_450.unk_270 = 0.0f;
        return;
    }
    if ((arg_0 >= 0.0f ? arg_0 : -arg_0) > unk_2638)
        arg_0 = arg_0 > 0.0f ? unk_2638 : -unk_2638;
    unk_450.unk_244 = arg_0;
    unk_450.unk_270 = arg_0;
}
// match: ?vf_28C@type_3DBC78@@UAEXM@Z @ 0x00152040
void type_3DBC78::vf_28C(RwReal arg_0)
{
    if (unk_DC4)
        unk_450.unk_248 = arg_0;
}
// match: ?vf_29C@type_3DBC78@@UAEXM@Z @ 0x00152070
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Turns unk_B24 by arg_0, at most a unit a call.
void type_3DBC78::vf_29C(RwReal arg_0)
{
    RwReal var_8;
    RwReal l4;

    if (unk_B20 != -1)
    {
        l4 = 1.0f;
        var_8 = -1.0f;
        unk_B24 = unk_B24 + sub_22C20(arg_0, var_8, l4);
    }
}
// match: ?vf_2A0@type_3DBC78@@UAEXHH@Z @ 0x001520D0
// Sets (arg_4) or clears flag arg_0 of unk_1100.
void type_3DBC78::vf_2A0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_4)
        unk_1100 |= 1 << arg_0;
    else
        unk_1100 &= ~(1 << arg_0);
}
// match: ?vf_04C@type_3DBC78@@UAEXM@Z @ 0x00152120
void type_3DBC78::vf_04C(RwReal arg_0)
{
    RwV3d var_10;
    RwV3d var_1C;
    RwV3d var_28;
    type_3D3548 *var_38;
    type_712B0_3DBC78 *var_40;
    RwFrame *var_48;
    RwMatrix *var_4C;
    RwMatrix *var_54;
    RwInt32 var_58;
    RwMatrix var_A0;
    type_EC1F0 *var_A8;
    RwMatrix var_F0;
    RwV3d var_FC;
    type_3DC048 *var_100;
    type_3D3548 *var_104;
    type_10F710 *var_108;
    RwFrame *var_114;
    RwV3d var_120;
    RpHAnimHierarchy *var_128;
    RwMatrix *var_12C;
    RwMatrix *var_130;
    RwMatrix var_170;
    RwMatrix var_1B0;
    RwFrame *var_1B4;
    RwMatrix *var_1B8;
    RwMatrix var_200;
    RwMatrix *var_204;

    type_3D3548::vf_04C(arg_0);
    vf_2B8();
    sub_154440(&var_1C, &var_10);
    RwV3dScale(&var_28, &var_1C, unk_4C + 300.0f);
    RwV3dScale(&unk_117C, &var_1C, 60.0f / arg_0 * flt_429DD4);
    RwV3dAdd(&unk_117C, &unk_117C, &var_28);
    RwV3dAdd(&unk_117C, &unk_117C, sub_CD550());
    sub_154EA0();
    vf_2D0(arg_0, &var_10);
    unk_450.unk_244 = 0.0f;
    unk_450.unk_248 = 0.0f;
    var_38 = unk_1190.sub_D4910();
    if (var_38)
    {
        var_40 = (type_712B0_3DBC78 *)get_unk_34C();
        var_48 = var_38->get_unk_340();
        var_4C = RwFrameGetMatrix(var_48);
        var_54 = RwFrameGetMatrix(get_unk_340());
        var_58 = var_40->unk_1B4 % 10 + 0x50474E30; // not an address: a tag
        if (!sub_EC2D0(get_unk_264(), (RwInt32)&var_A0, var_58, 0, 0))
        {
            var_A0 = *var_54;
        }
        var_A8 = sub_EC1F0(var_38->get_unk_264(), 0x41544D54); // not an address: a tag
        if (!var_A8)
            RwMatrixSetIdentityMacro(&var_F0);
        else
            RwMatrixInvert(&var_F0, &var_A8->unk_10);
        var_FC = var_F0.pos;
        RwMatrixTransform(&var_A0, &var_F0, rwCOMBINEPRECONCAT);
        *var_4C = var_A0;
        RwFrameUpdateObjects(var_48);
    }
    sub_16D7F0(0x18);
    unk_11A0.sub_17A20(arg_0);
    sub_16D850(0x18);
    vf_1D0();
    var_100 = (type_3DC048 *)this;
    var_104 = unk_118C.sub_D4910();
    if (!(var_104 && var_104->unk_2C_4))
        return;
    var_108 = (type_10F710 *)var_104;
    if (!(var_108 && var_108->vf_200() == this && var_108->get_unk_19D0_r() == 5))
        return;
    var_114 = var_108->get_unk_340();
    if (var_108->unk_4D0 == 1)
    {
        var_120.x = dword_4D5168;
        var_120.y = dword_429DBC;
        var_120.z = dword_429DC0;
        var_128 = get_unk_284()->unk_18;
        var_12C = RpHAnimHierarchyGetMatrixArray(var_128);
        var_130 = &var_12C[var_100->unk_28DC];
        sub_141320(&var_120, &var_120, var_130);
        RwV3dAdd(&var_120, &var_130->pos, &var_120);
        RwMatrixInitializeMacro(&var_170, rwMATRIXTYPENORMAL);
        RwMatrixInitializeMacro(&var_1B0, rwMATRIXTYPENORMAL);
        sub_14D1B0(&var_1B0, 0.0f, 1.0f, 0.0f, var_100->unk_2890);
        RwMatrixMultiply(&var_170, var_130, &var_1B0);
        sub_14D1B0(&var_1B0, var_170.right.x, var_170.right.y, var_170.right.z, var_100->unk_289C);
        sub_141320(&var_170.up, &var_170.up, &var_1B0);
        sub_141320(&var_170.at, &var_170.at, &var_1B0);
        var_170.pos = var_120;
        var_1B4 = RwFrameGetParent(var_114);
        var_1B8 = RwFrameGetMatrix(var_1B4);
        RwMatrixInitializeMacro(&var_200, rwMATRIXTYPENORMAL);
        RwMatrixInvert(&var_200, var_1B8);
        var_204 = RwFrameGetMatrix(var_114);
        RwMatrixMultiply(var_204, &var_170, &var_200);
        RwFrameUpdateObjects(var_114);
    }
    else if (var_108->unk_4D0 == 2)
    {
        var_108->sub_100680();
    }
}
// match: ?vf_234@type_3DBC78@@UAEXXZ @ 0x00152830
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its tracks' speeds for their UV animations: its move along the ground
// (backwards when it moves against its facing), less or more its spin for
// each track (the same while it steers by the contacts); each track's UV
// time advances by it.
void type_3DBC78::vf_234()
{
    RwReal var_24;
    RwReal var_20;
    RwV3d l1C;
    RwReal lv_10;
    RwV3d var_C;

    var_C = unk_450.unk_148;
    var_C.y = 0.0f;
    lv_10 = RwV3dLength((RwV3d *)&var_C) * 0.017453279f;
    if (RwV3dDotProduct(&unk_450.unk_124, &unk_450.unk_170.at) < 0.0f)
        lv_10 = lv_10 * -1.0f;
    lv_10 = lv_10 * flt_429DB8;
    if (!unk_450.unk_29C)
    {
        var_24 = fabs(unk_450.unk_130.y);
        set_xyz(&l1C, 0.0f, 1.0f, 0.0f);
        var_20 = (var_20 = RwV3dDotProduct(&unk_450.unk_130, &l1C)) < 0.0f ? -1.0f : 1.0f;
        var_24 = var_24 * unk_450.unk_250 * 0.8f * var_20;
        unk_DA4 = lv_10 - var_24;
        unk_DA0 = lv_10 + var_24;
    }
    else
    {
        unk_DA0 = lv_10;
        unk_DA4 = lv_10;
    }
    if (unk_B10.unk_00)
        vf_2B4(&unk_B10, unk_DA4);
    if (unk_B18.unk_00)
        vf_2B4(&unk_B18, unk_DA0);
}
// match: ?vf_2B4@type_3DBC78@@UAEXPAUtype_3DBC78_B10@@M@Z @ 0x00152A20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Advances the track arg_0's UV time by the distance arg_4 (three
// quarters of it, wrapped into a unit, backwards for a negative distance).
void type_3DBC78::vf_2B4(type_3DBC78_B10 *arg_0, RwReal arg_4)
{
    RwInt32 var_8;
    RwReal l4;

    l4 = arg_4 * 0.75f;
    var_8 = 0;
    if (l4 < 0.0f)
    {
        var_8 = 1;
        l4 = l4 * -1.0f;
    }
    l4 = l4 - (RwReal)floor((RwDouble)l4);
    if (var_8)
        l4 = 1.0f - l4;
    arg_0->unk_04 += l4;
    arg_0->unk_04 = (RwReal)(RwDouble)(RwReal)fmod((RwDouble)arg_0->unk_04, 1.0);
}
// match: ?vf_1D0@type_3DBC78@@UAEXXZ @ 0x00152AD0
// match: __ehhandler$?vf_1D0@type_3DBC78@@UAEXXZ-0x8 @ 0x00301BF0
// match: __ehhandler$?vf_1D0@type_3DBC78@@UAEXXZ @ 0x00301BF8
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// As the base's (type_3D3548::vf_1D0), from its position (sub_CD550) and
// for longer: the path nodes it covers are marked for 120.
void type_3DBC78::vf_1D0()
{
    RwInt32 var_44;
    RwUInt16 var_40;
    RwInt32 stk_3C;
    RwInt32 ebp_38;
    RwV3d *var_34;
    RwReal local_30;
    RwV3d stk_2C;
    RwReal var_20;
    RwInt32 l1C[4];

    var_34 = sub_CD550();
    var_20 = unk_4C;
    if (!sub_F8820(var_34, var_20, l1C, 0))
        return;
    local_30 = var_20 * var_20;
    for (ebp_38 = l1C[0]; ebp_38 <= l1C[2]; ebp_38++)
    {
        for (stk_3C = l1C[1]; stk_3C <= l1C[3]; stk_3C++)
        {
            var_44 = stk_3C * unk_4C00E8.unk_24 + ebp_38;
            var_40 = unk_4C00E8.get_unk_3C(var_44);
            if (var_40 != 0xFFFF)
            {
                RwUInt32 **var_60 = &unk_4C00E8.unk_48[var_40];
                RwUInt32 *stk_5C = *var_60;
                type_3CE1FC l58(stk_5C);
                while (!l58.at_end())
                {
                    type_F8350 *var_64 = unk_4C00E8.unk_2C[l58.unk_0C];
                    RwV3dSub(&stk_2C, &var_64->unk_10, var_34);
                    if (stk_2C.y > -75.0f && stk_2C.y < 150.0f)
                    {
                        stk_2C.y = 0.0f;
                        if (RwV3dDotProduct(&stk_2C, &stk_2C) < local_30)
                            var_64->unk_08 = (RwInt32)dword_4B87C8 + 120;
                    }
                    l58.sub_31A10();
                }
            }
        }
    }
}
// match: ?vf_054@type_3DBC78@@UAEXH@Z @ 0x00152CE0
// Its tracks' UV animations applied, then the entity drawn (the base's).
void type_3DBC78::vf_054(RwInt32 arg_0)
{
    if (unk_B10.unk_00)
    {
        RpMaterialUVAnimSetCurrentTime(unk_B10.unk_00, unk_B10.unk_04);
        RpMaterialUVAnimApplyUpdate(unk_B10.unk_00);
    }
    if (unk_B18.unk_00)
    {
        RpMaterialUVAnimSetCurrentTime(unk_B18.unk_00, unk_B18.unk_04);
        RpMaterialUVAnimApplyUpdate(unk_B18.unk_00);
    }
    sub_19A750(1);
    type_3D3548::vf_054(arg_0);
    sub_19A750(0);
}
// match: ?vf_170@type_3DBC78@@UAEXHHHH@Z @ 0x00152D90
// An animation event arg_0 for its animation: kind 1 hands arg_8 to its
// sound object (dropping its procedural track when the animation's
// records did not change); others are the base's.
void type_3DBC78::vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    RwInt32 var_4;

    if (!unk_284)
        return;
    switch (arg_0)
    {
    case 1:
    {
        var_4 = get_unk_284()->unk_24;
        ((type_3D2CD0 *)vf_090())->sub_6DF90(arg_8, unk_88_12);
        unk_88_12 = 0;
        if (get_unk_284()->get_unk_24() == var_4)
            unk_DB4 = 0;
        break;
    }
    default:
        type_3D3548::vf_170(arg_0, arg_4, arg_8, 0);
    }
}
// match: ?vf_0EC@type_3DBC78@@UAEXHH@Z @ 0x00152E60
void type_3DBC78::vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
{
    unk_112C[arg_0] = (RwInt16)arg_4;
}
// match: ?vf_2BC@type_3DBC78@@UAEXXZ @ 0x00152E80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78::vf_2BC()
{
    type_3D3548 *var_24;
    type_3D3548 *var_20;
    type_3D3548 *l1C;
    RwReal m_18;
    RwV3d ebp_14;
    RwReal bp_8;
    RwReal bp_4;

    m_18 = 0.2588f;
    bp_8 = -0.2588f;
    ebp_14 = *sub_CD5A0();
    bp_4 = ebp_14.y;
    if (bp_4 < bp_8)
    {
        if (unk_114C != 0)
        {
            unk_114C = 0;
            unk_1C0.sub_8A910(unk_1144);
            l1C = sub_1745A0(0);
            if (unk_118C.sub_D4910() == l1C)
            {
                unk_1144 = l1C->unk_1C0.sub_8AA70(&unk_3D4.unk_18, unk_114C, this, 4, l1C->sub_CD550(), 0, 0);
                l1C->unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, l1C->sub_CD550(), 0, 0);
            }
            else
            {
                unk_1144 = unk_1C0.sub_8AA70(&unk_3D4.unk_18, unk_114C, this, 4, sub_CD550(), 0, 0);
                unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, sub_CD550(), 0, 0);
            }
        }
    }
    else if (bp_4 < m_18)
    {
        if (unk_114C != 1)
        {
            unk_114C = 1;
            unk_1C0.sub_8A910(unk_1144);
            var_20 = sub_1745A0(0);
            if (unk_118C.sub_D4910() == var_20)
            {
                unk_1144 = var_20->unk_1C0.sub_8AA70(&unk_3D4.unk_18, unk_114C, this, 4, var_20->sub_CD550(), 0, 0);
                unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, var_20->sub_CD550(), 0, 0);
            }
            else
            {
                unk_1144 = unk_1C0.sub_8AA70(&unk_3D4.unk_18, unk_114C, this, 4, sub_CD550(), 0, 0);
                unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, sub_CD550(), 0, 0);
            }
        }
    }
    else
    {
        if (unk_114C != 2)
        {
            unk_114C = 2;
            unk_1C0.sub_8A910(unk_1144);
            var_24 = sub_1745A0(0);
            if (unk_118C.sub_D4910() == var_24)
            {
                unk_1144 = var_24->unk_1C0.sub_8AA70(&unk_3D4.unk_18, unk_114C, this, 4, var_24->sub_CD550(), 0, 0);
                unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, var_24->sub_CD550(), 0, 0);
            }
            else
            {
                unk_1144 = unk_1C0.sub_8AA70(&unk_3D4.unk_18, unk_114C, this, 4, sub_CD550(), 0, 0);
                unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, sub_CD550(), 0, 0);
            }
        }
    }
}
// match: ?vf_2B8@type_3DBC78@@UAEXXZ @ 0x00153270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78::vf_2B8()
{
    type_3D3548 *var_10;
    type_3D3548 *var_C;
    type_3D3548 *bp_8;
    type_3D3548 *bp_4;

    if (!unk_1138 && real_abs(unk_450.unk_244) > 0.0001f)
    {
        unk_1138 = 1;
        bp_4 = sub_1745A0(0);
        if (unk_118C.sub_D4910() == bp_4)
        {
            bp_4->unk_1C0.sub_8A980(&unk_3D4.unk_20, this, 4, bp_4->sub_CD550(), 0, 0);
            bp_4->unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, bp_4->sub_CD550(), 0, 0);
        }
        else
        {
            unk_1C0.sub_8A980(&unk_3D4.unk_20, this, 4, sub_CD550(), 0, 0);
            unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, sub_CD550(), 0, 0);
        }
        unk_1C0.sub_8A910(unk_1144);
        unk_114C = -1;
        vf_2BC();
    }
    else if (unk_1138 && real_abs(unk_450.unk_244) < 0.0001f)
    {
        unk_1138 = 0;
        bp_8 = sub_1745A0(0);
        if (unk_118C.sub_D4910() == bp_8)
        {
            bp_8->unk_1C0.sub_8A980(&unk_3D4.unk_28, this, 4, bp_8->sub_CD550(), 0, 0);
            bp_8->unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, bp_8->sub_CD550(), 0, 0);
        }
        else
        {
            unk_1C0.sub_8A980(&unk_3D4.unk_28, this, 4, sub_CD550(), 0, 0);
            unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, sub_CD550(), 0, 0);
        }
        unk_1C0.sub_8A910(unk_1144);
        unk_114C = -1;
        if (unk_118C.sub_D4910() == bp_8)
            unk_1144 = bp_8->unk_1C0.sub_8A980(&unk_3D4.unk_10, this, 4, bp_8->sub_CD550(), 0, 0);
        else
            unk_1144 = unk_1C0.sub_8A980(&unk_3D4.unk_10, this, 4, sub_CD550(), 0, 0);
    }
    else if (unk_1138 && real_abs(unk_450.unk_244) > 0.0001f)
    {
        vf_2BC();
    }
    if (!unk_1138 && !unk_113C && real_abs(unk_450.unk_248) > 0.0001f)
    {
        unk_113C = 1;
        var_C = sub_1745A0(0);
        if (unk_118C.sub_D4910() == var_C)
            var_C->unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, var_C->sub_CD550(), 0, 0);
        else
            unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, sub_CD550(), 0, 0);
        unk_1C0.sub_8A910(unk_1144);
        unk_114C = -1;
        vf_2BC();
    }
    if (real_abs(unk_450.unk_248) < 0.0001f)
    {
        if (!unk_1138 && unk_113C)
        {
            unk_1C0.sub_8A910(unk_1144);
            var_10 = sub_1745A0(0);
            if (unk_118C.sub_D4910() == var_10)
            {
                var_10->unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, var_10->sub_CD550(), 0, 0);
                unk_1144 = var_10->unk_1C0.sub_8A980(&unk_3D4.unk_10, this, 4, var_10->sub_CD550(), 0, 0);
            }
            else
            {
                unk_1C0.sub_8A980(&unk_3D4.unk_50, this, 4, sub_CD550(), 0, 0);
                unk_1144 = unk_1C0.sub_8A980(&unk_3D4.unk_10, this, 4, sub_CD550(), 0, 0);
            }
            unk_114C = -1;
        }
        unk_113C = 0;
    }
}
// match: ?sub_153890@type_3DBC78@@QAEXPAUtype_153890@@HPAURwMatrixTag@@H@Z @ 0x00153890
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78::sub_153890(type_153890 *arg_0, RwInt32 arg_4, RwMatrix *arg_8, RwInt32 arg_C)
{
    RtQuat var_34;
    RwInt32 frm_24;
    RtQuat *var_20;
    RtQuat *l1C;
    RwInt32 m_18;
    RtQuat ebp_14;
    RwUInt8 *bp_4;

    var_20 = 0;
    l1C = 0;
    bp_4 = arg_0->unk_04;
    var_20 = &arg_0->unk_10[*bp_4];
    l1C = arg_0->unk_10;
    m_18 = arg_4;
    frm_24 = m_18;
    if (arg_C)
        var_20[frm_24].imag = arg_8->pos;
    else
        RwV3dAdd(&var_20[frm_24].imag, &var_20[frm_24].imag, &arg_8->pos);
    RtQuatConvertFromMatrix(&ebp_14, arg_8);
    if (arg_C)
    {
        l1C[m_18] = ebp_14;
    }
    else
    {
        RtQuatMultiplyMacro(&var_34, &l1C[m_18], &ebp_14);
        l1C[m_18] = var_34;
        sub_13FB00(&l1C[m_18], &l1C[m_18]);
    }
}
// match: ?sub_153B30@type_3DBC78@@QAEXXZ @ 0x00153B30
void type_3DBC78::sub_153B30()
{
    if (unk_1148)
    {
        unk_1C0.sub_8A910(unk_1148);
        unk_1148 = 0;
    }
    if (unk_1144)
    {
        unk_1C0.sub_8A910(unk_1144);
        unk_1144 = 0;
    }
}
// match: ?vf_2C0@type_3DBC78@@UAEPAURwMatrixTag@@XZ @ 0x00153BA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Its turret's matrix: bone 160 of its animation when it has one, else its
// clump's frame raised by its height.
RwMatrix *type_3DBC78::vf_2C0()
{
    RpClump *var_18;
    RwFrame *var_14;
    RwInt32 lv_10;
    type_7C8D0 *var_C;
    RpHAnimHierarchy *bp_8;
    RwMatrix *bp_4;

    if (unk_28_13)
    {
        var_C = (type_7C8D0 *)sub_78AC0(unk_280);
        lv_10 = RpHAnimIDGetIndex(var_C->get_unk_18(), 160);
        bp_8 = var_C->unk_18;
        bp_4 = &bp_8->pMatrixArray[lv_10];
    }
    else
    {
        var_18 = unk_25C.unk_08;
        var_14 = RpClumpGetFrame(var_18);
        bp_4 = RwFrameGetLTM(var_14);
        bp_4->pos.y = bp_4->pos.y + unk_48;
    }
    return bp_4;
}
// match: ?sub_153C40@type_3DBC78@@QAEXPAUtype_153C40@@HHHPAURwV3d@@@Z @ 0x00153C40
void type_3DBC78::sub_153C40(type_153C40 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwV3d *arg_10)
{
    arg_0->unk_00 = arg_4;
    arg_0->unk_04 = RpRandom() % (arg_C - arg_8 + 1) + arg_8;
    if (RpRandom() % 2 == 1)
        arg_0->unk_04 = -arg_0->unk_04;
    arg_0->unk_08 = *arg_10;
}
// match: ?sub_153CB0@type_3DBC78@@QAE_NXZ @ 0x00153CB0
bool type_3DBC78::sub_153CB0()
{
    if (sub_16D900(get_unk_264(), "destroyed"))
    {
        sub_16E080(get_unk_264(), 0);
        sub_16D8C0(get_unk_264(), "destroyed", 1);
        return true;
    }
    return false;
}
// match: ?vf_2D4@type_3DBC78@@UAE_NPAUtype_3D3548@@PAURwV3d@@PAM@Z @ 0x00153D20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Whether it threatens the entity arg_0 ("IsThreatenedByTank"): within the
// range *arg_8 (else the distance to the point it watches), within its
// height (at least 250) above or below, along the direction *arg_4 (else
// toward that point) within its field of fire, and in the clear.
bool type_3DBC78::vf_2D4(type_3D3548 *arg_0, RwV3d *arg_4, RwReal *arg_8)
{
    RwReal ebp_34;
    RwReal var_30;
    RwReal var_2C;
    RwV3d *lv_28;
    RwV3d var_24;
    RwReal bp_18;
    RwV3d var14;
    RwV3d *frm_8;
    RwReal l4;

    frm_8 = sub_CD550();
    if (arg_4)
    {
        var_24 = *arg_4;
    }
    else
    {
        RwV3dSub(&var_24, &unk_117C, frm_8);
        if ((var_24.x >= 0.0f ? var_24.x : -var_24.x) > 0.01f
            || (var_24.y >= 0.0f ? var_24.y : -var_24.y) > 0.01f || abs_int(var_24.z > 0.01f))
            RwV3dNormalize(&var_24, &var_24);
    }
    if (arg_8)
        l4 = *arg_8;
    else
        l4 = sub_140C90(&unk_117C, frm_8);
    bp_18 = sub_140C90(arg_0->sub_CD550(), frm_8);
    if (bp_18 < l4)
    {
        ebp_34 = unk_48;
        if (unk_48 < 250.0f)
            ebp_34 = 250.0f;
        var_30 = ebp_34 + frm_8->y;
        var_2C = frm_8->y - ebp_34;
        lv_28 = arg_0->sub_CD550();
        if (lv_28->y < var_2C || lv_28->y > var_30)
            return false;
        RwV3dSub(&var14, lv_28, frm_8);
        var14.y = 0.0f;
        RwV3dNormalize(&var14, &var14);
        if (RwV3dDotProduct(&var_24, &var14) > flt_429DD8)
        {
            RwV3d var_4C = *arg_0->sub_CD550();
            var_4C.y += 70.0f;
            RwV3d var_40 = *frm_8;
            var_40.y += 70.0f;
            return sub_D2FC0(&var_4C, &var_40, arg_0, 0, 0, 0, 0, 1, 0x40000, 0, 0) == 0; // not an address: a surface flag
        }
    }
    return false;
}
// match: ?vf_2D8@type_3DBC78@@UAE_NMPAUtype_3D3548@@HPAURwV3d@@PAM@Z @ 0x00153FE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_3DBC78::vf_2D8(RwReal arg_0, type_3D3548 *arg_4, RwInt32 arg_8, RwV3d *arg_C, RwReal *arg_10)
{
    RwReal local_7C;
    RwReal var_78;
    RwReal var_74;
    RwReal var70;
    RwReal stk_6C;
    RwReal q68;
    RwV3d var_64;
    RwV3d stk_58;
    RwMatrix *l4C;
    RwReal var_48;
    RwReal loc44;
    RwReal var_40;
    AIData *l3C;
    RwReal local_38;
    RwV3d local_34;
    RwV3d var28;
    RwReal l1C;
    RwV3d m_18;
    RwV3d *var_C;
    RwV3d *bp_8;
    RwReal bp_4;

    var_C = sub_CD550();
    if (arg_C)
        var28 = *arg_C;
    else
        sub_154440(&local_34, &var28);
    bp_8 = arg_4->sub_CD550();
    if (arg_10)
    {
        bp_4 = *arg_10;
    }
    else
    {
        local_38 = flt_429DE4 * unk_4C + arg_4->unk_4C;
        l3C = arg_4->vf_120();
        if (arg_4->unk_2C_4)
        {
            local_38 = unk_4C + 300.0f;
        }
        else if (l3C && l3C->unk_49C_21)
        {
            local_38 = unk_4C + 300.0f;
        }
        else
        {
            l4C = RwFrameGetLTM(arg_4->get_unk_340());
            RwV3dSub(&stk_58, var_C, bp_8);
            stk_58.y = 0.0f;
            RwV3dNormalize(&stk_58, &stk_58);
            var_64 = l4C->at;
            var_64.y = 0.0f;
            RwV3dNormalize(&var_64, &var_64);
            loc44 = RwV3dDotProduct(&var_64, &stk_58);
            var_40 = 0.0f;
            var_48 = 0.0f;
            if (unk_2854 && unk_2850 > unk_4C)
                var_40 = unk_2850;
            if (arg_4->vf_1DC() && arg_4->vf_1E0() > arg_4->unk_4C)
                var_48 = arg_4->vf_1E0();
            if (var_40 != 0.0f && var_48 != 0.0f)
            {
                if (-flt_429DE0 > loc44)
                {
                    q68 = var_48 + unk_4C + 300.0f;
                    if (q68 > local_38)
                        local_38 = q68;
                }
            }
            else if (var_40 != 0.0f && var_48 == 0.0f)
            {
                if (loc44 > flt_429DE0)
                {
                    stk_6C = var_40 + arg_4->unk_4C + 300.0f;
                    if (stk_6C > local_38)
                        local_38 = stk_6C;
                }
            }
            else if (var_40 == 0.0f && var_48 != 0.0f)
            {
                if (-flt_429DE0 > loc44)
                {
                    var70 = var_48 + unk_4C + 300.0f;
                    if (var70 > local_38)
                        local_38 = var70;
                }
            }
        }
        if (arg_8)
            local_38 += 250.0f;
        bp_4 = local_38 * local_38;
    }
    l1C = sub_140C90(arg_4->sub_CD550(), var_C);
    if (l1C < bp_4)
    {
        local_7C = unk_48;
        if (unk_48 < 250.0f)
            local_7C = 250.0f;
        var_78 = local_7C + var_C->y;
        var_74 = var_C->y - local_7C;
        if (bp_8->y < var_74 || bp_8->y > var_78)
            return false;
        RwV3dSub(&m_18, bp_8, var_C);
        m_18.y = 0.0f;
        RwV3dNormalize(&m_18, &m_18);
        if (RwV3dDotProduct(&var28, &m_18) > flt_429DDC)
            return true;
    }
    return false;
}
// match: ?sub_154440@type_3DBC78@@QAEXPAURwV3d@@0@Z @ 0x00154440
void type_3DBC78::sub_154440(RwV3d *arg_0, RwV3d *arg_4)
{
    RwV3d var_10;
    RwV3d var_28;
    RwMatrix *var_30;
    RwMatrix var_70;
    RwV3d var_7C;

    var_10 = *vf_0C8();
    var_10.y = 0.0f;
    if ((var_10.x >= 0.0f ? var_10.x : -var_10.x) > 0.01f || abs_int(var_10.z > 0.01f))
    {
        RwV3dNormalize(&var_28, &var_10);
        *arg_0 = var_28;
        var_30 = RwFrameGetLTM(get_unk_340());
        RwMatrixSetIdentity(&var_70);
        RwMatrixInvert(&var_70, var_30);
        sub_141320(&var_7C, &var_28, &var_70);
        if ((var_7C.z < 0.0f && vf_284() > 0.0f) || (var_7C.z > 0.0f && vf_284() < 0.0f) || unk_450.unk_230)
        {
            var_28 = *sub_CD5A0();
            var_28.y = 0.0f;
            RwV3dNormalize(&var_28, &var_28);
        }
    }
    else
    {
        zero_v3d(arg_0);
        var_28 = *sub_CD5A0();
        var_28.y = 0.0f;
        RwV3dNormalize(&var_28, &var_28);
    }
    *arg_4 = var_28;
}
// match: ?vf_2D0@type_3DBC78@@UAEXMPAURwV3d@@@Z @ 0x001546C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78::vf_2D0(RwReal arg_0, RwV3d *arg_4)
{
    RwInt32 var_5C;
    AIData *bp_58;
    type_3DAFC8 *p54;
    RwReal var_50;
    RwInt32 m_4C;
    RwV3d local_48;
    RwReal p3C;
    RwReal var_38;
    RwReal l34;
    RwReal var30;
    RwReal ebp_2C;
    AIData *lcl_28;
    type_3D3548 *frm_24;
    RwInt32 var_20;
    RwV3d l1C;
    RwReal lv_10;
    RwMatrix *var_C;
    RwReal bp_8;
    RwInt32 bp_4;

    RwV3dSub(&l1C, &unk_117C, sub_CD550());
    if ((l1C.x >= 0.0f ? l1C.x : -l1C.x) > 0.01f
        || (l1C.y >= 0.0f ? l1C.y : -l1C.y) > 0.01f || abs_int(l1C.z > 0.01f))
        RwV3dNormalize(&l1C, &l1C);
    lv_10 = sub_140C90(&unk_117C, sub_CD550());
    bp_4 = unk_11A0.unk_4B0;
    unk_11A0.unk_4B0 = 0;
    var_C = RwFrameGetLTM(get_unk_340());
    for (var_20 = 0; var_20 < 32; var_20++)
    {
        frm_24 = unk_438CA8[var_20].sub_D4910();
        if (frm_24)
        {
            if (frm_24 == this || frm_24->vf_200() || frm_24 == unk_118C.sub_D4910())
                continue;
            if (unk_2854 && (frm_24->unk_2C & 0x40080)) // not an address: entity kind bits
            {
                RwV3dSub(&local_48, frm_24->sub_CD550(), &var_C->pos);
                l34 = RwV3dLength((RwV3d *)&local_48);
                local_48.y = 0.0f;
                RwV3dNormalize(&local_48, &local_48);
                var30 = RwV3dDotProduct(&var_C->at, &local_48);
                if (var30 >= 0.66f)
                {
                    p3C = unk_2850 + 200.0f;
                    m_4C = 1;
                }
                else if (var30 < 0.66f && var30 > -0.5f)
                {
                    p3C = unk_284C + 250.0f;
                    var_50 = RwV3dDotProduct(&local_48, &var_C->right);
                    if (var_50 > 0.0f)
                        m_4C = 2;
                    else
                        m_4C = 3;
                }
                else
                {
                    p3C = unk_2850 + 200.0f;
                    m_4C = 4;
                }
                var_38 = p3C + frm_24->unk_4C;
                ebp_2C = l34 - var_38;
                if (ebp_2C < 0.0f)
                {
                    switch (m_4C)
                    {
                    case 1:
                        unk_263C[0].unk_00_1 = 0;
                        unk_263C[1].unk_00_1 = 0;
                        unk_263C[2].unk_00_1 = 0;
                        unk_263C[3].unk_00_1 = 0;
                        break;
                    case 2:
                        unk_263C[0].unk_00_1 = 0;
                        unk_263C[1].unk_00_1 = 0;
                        unk_263C[4].unk_00_1 = 0;
                        unk_263C[5].unk_00_1 = 0;
                        unk_263C[8].unk_00_1 = 0;
                        unk_263C[9].unk_00_1 = 0;
                        break;
                    case 3:
                        unk_263C[2].unk_00_1 = 0;
                        unk_263C[3].unk_00_1 = 0;
                        unk_263C[6].unk_00_1 = 0;
                        unk_263C[7].unk_00_1 = 0;
                        unk_263C[10].unk_00_1 = 0;
                        unk_263C[11].unk_00_1 = 0;
                        break;
                    case 4:
                        unk_263C[8].unk_00_1 = 0;
                        unk_263C[9].unk_00_1 = 0;
                        unk_263C[10].unk_00_1 = 0;
                        unk_263C[11].unk_00_1 = 0;
                        break;
                    }
                }
            }
            lcl_28 = frm_24->vf_120();
            if (!unk_11A0.unk_49C_29
                && ((frm_24->unk_2C_4 && (frm_24->unk_2C & 7) == (unk_2C & 7))
                    || (frm_24->unk_2C & 0x40080) || (lcl_28 && lcl_28->unk_49C_21))) // not an address: entity kind bits
            {
                if (vf_2D8(arg_0, frm_24, bp_4, arg_4, 0))
                    vf_120()->unk_4B0 = 1;
            }
            else
            {
                if (lcl_28 && lcl_28->unk_49C_21)
                    continue;
                p54 = frm_24->vf_008();
                if (p54)
                {
                    var_5C = 0;
                    bp_58 = p54->vf_120();
                    if (bp_58->unk_49C_9 && bp_58->sub_238E0(0))
                        var_5C = 1;
                    if (!var_5C && vf_2D4(frm_24, &l1C, &lv_10))
                    {
                        p54->unk_614.sub_D48D0(this);
                        bp_8 = lv_10;
                        sub_6B5F0("TankAlert", (type_67620 *)(frm_24->vf_098()), 0, 0, (RwInt32 *)(&bp_8), 1, 1, 0);
                    }
                }
            }
        }
    }
    if (vf_098())
    {
        if (unk_11A0.unk_4B0 && !bp_4)
            sub_6B5F0("Vehicle_PathBlocked", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
        else if (!unk_11A0.unk_4B0 && bp_4)
            sub_6B5F0("Vehicle_PathUnBlocked", (type_67620 *)(vf_098()), 0, 0, 0, 0, 1, 0);
    }
}
// match: ?sub_154E30@type_3DBC78@@QAEXH@Z @ 0x00154E30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78::sub_154E30(RwInt32 arg_0)
{
    type_14D180 *var_8;
    RwInt32 l4;

    if (!unk_2854)
        return;
    for (l4 = 0; l4 < 12; l4++)
    {
        var_8 = &unk_263C[l4];
        if (var_8->unk_0C)
            var_8->unk_00_0 = arg_0;
    }
}
// match: ?sub_154EA0@type_3DBC78@@QAEXXZ @ 0x00154EA0
// Places its enabled cover points on its model (the node's matrix, from
// the skin's bones or the node frames, times the point's offset) and marks
// each clear when no wall stands between it and the vehicle (66 up); the
// front four are not clear while it drives forward faster than 3, the back
// four while it reverses so.
void type_3DBC78::sub_154EA0()
{
    RpClump *var_8;
    RpHAnimHierarchy *var_C;
    RwV3d *var_10;
    RpSkin *var_14;
    RwFrame *var_18;
    RwMatrix *var_1C;
    RwReal var_20;
    RwInt32 var_24;
    type_14D180 *var_28;
    RwMatrix *var_2C;
    RwMatrix var_70;

    if (!unk_2854)
        return;
    var_8 = unk_25C.unk_08;
    var_C = unk_284->unk_18;
    var_10 = sub_CD550();
    var_14 = RWS::SkinHelper::FindFirstSkin(*var_8);
    var_18 = RpClumpGetFrame(var_8);
    var_1C = RwFrameGetLTM(var_18);
    var_20 = unk_450.sub_14C140();
    for (var_24 = 0; var_24 < 12; var_24++)
    {
        var_28 = &unk_263C[var_24];
        if (var_28->unk_00_0)
        {
            var_2C = 0;
            RwMatrixSetIdentity(&var_70);
            if (var_28->unk_0C->unk_04)
            {
                if (var_14)
                {
                    var_2C = &var_C->pMatrixArray[var_28->unk_0C->unk_04];
                }
                else
                {
                    RpHAnimNodeInfo *var_74 = &var_C->pNodeInfo[var_28->unk_0C->unk_04];
                    var_2C = RwFrameGetLTM(var_74->pFrame);
                }
                if (var_C->flags & rpHANIMHIERARCHYLOCALSPACEMATRICES)
                {
                    RwMatrix var_C0;

                    RwMatrixSetIdentity(&var_C0);
                    RwMatrixMultiply(&var_C0, var_2C, var_1C);
                    RwMatrixMultiply(&var_70, &var_28->unk_0C->unk_10, &var_C0);
                }
                else
                {
                    RwMatrixMultiply(&var_70, &var_28->unk_0C->unk_10, var_2C);
                }
            }
            else
            {
                RwMatrixMultiply(&var_70, &var_28->unk_0C->unk_10, var_1C);
            }
            var_28->unk_14 = var_70.pos;
            var_28->unk_20 = var_70.at;
            RwInt32 var_C4 = 0;
            RwLine var_DC;
            var_DC.start = *var_10;
            var_DC.start.y += 66.0f;
            var_DC.end = var_28->unk_14;
            var_DC.end.y += 66.0f;
            for (RwInt32 var_E0 = 0; var_E0 < 4; var_E0++)
            {
                type_4E5D30 *var_E4 = &dword_4E5D30[var_E0];
                if (var_E4->get_unk_00() && var_E4->get_unk_28())
                {
                    if (sub_91F40(var_E4->get_unk_28(), &var_DC, 0, 0, 0x20000, 1)) // not an address: a surface flag
                    {
                        var_C4 = 1;
                        break;
                    }
                }
            }
            if (var_C4)
                var_28->unk_00_1 = 0;
            else
                var_28->unk_00_1 = 1;
            switch (var_24)
            {
            case 0:
            case 1:
            case 2:
            case 3:
                if (var_20 > 3.0f)
                    var_28->unk_00_1 = 0;
                break;
            case 8:
            case 9:
            case 10:
            case 11:
                if (var_20 < -3.0f)
                    var_28->unk_00_1 = 0;
                break;
            }
        }
    }
}
// match: ?sub_155340@type_3DBC78@@QAEPAUtype_14D180@@PAUtype_154C0_12F4@@@Z @ 0x00155340
type_14D180 *type_3DBC78::sub_155340(type_154C0_12F4 *arg_0)
{
    type_14D180 *var_4;

    var_4 = 0;
    if (arg_0->unk_08.sub_D4910() == this)
        var_4 = &unk_263C[arg_0->unk_00];
    return var_4;
}
// match: ?vf_2F4@type_3DBC78@@UAEXHPAURwMatrixTag@@@Z @ 0x00155380
void type_3DBC78::vf_2F4(RwInt32 arg_0, RwMatrix *arg_4)
{
    RpClump *var_4;

    if (!arg_4)
        return;
    var_4 = unk_25C.unk_08;
    if (var_4)
        sub_EC2D0(var_4, (RwInt32)arg_4, unk_DFC.unk_00[arg_0].unk_38, 0, 0);
}
// match: ?sub_1553E0@type_3DBC78@@QAEPAUtype_14D180@@PAU2@PAURwMatrixTag@@@Z @ 0x001553E0
type_14D180 *type_3DBC78::sub_1553E0(type_14D180 *arg_0, RwMatrix *arg_4)
{
    RpClump *var_4;

    var_4 = unk_25C.unk_08;
    if (var_4)
        sub_EC2D0(var_4, (RwInt32)arg_4, arg_0->unk_08, 0, 1);
    else
        return 0;
    return arg_0;
}
// match: ?vf_098@type_3DBC78@@UAEPAUtype_3D2E7C@@XZ @ 0x00155430
type_3D2E7C *type_3DBC78::vf_098()
{
    return (type_3D2E7C *)sub_67620(unk_1124);
}
// match: ?vf_090@type_3DBC78@@UAEPAUtype_6D380@@XZ @ 0x00155450
type_6D380 *type_3DBC78::vf_090()
{
    return (type_6D380 *)sub_67620(unk_1128);
}
