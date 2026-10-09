// Split from unit_012000.cpp at 0x0154C0, where the image starts another object (AIData's,
// its constructor first): its .rdata begins at 0x3CDB00 with its own copy of the unreferenced
// 16.666666 the others start theirs with (an object's own constants come before its literals),
// after the literals of the handlers before it (PLAN M7).

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
// 0x003CDB00
extern const RwReal flt_3CDB00 = 16.666666f;
// 0x004275B8
RwReal flt_4275B8 = 50.0f;
// 0x004275BC
RwReal flt_4275BC = 50.0f;
// 0x004275C0
RwReal flt_4275C0 = 400.0f;
// 0x004275C4
RwReal flt_4275C4 = 5.0f;
// 0x004275C8
RwReal dword_4275C8 = 500.0f;
// 0x004275CC
RwReal flt_4275CC = 100.0f;
// 0x004275D0
RwReal flt_4275D0 = 100.0f;
// 0x004275D4
RwReal flt_4275D4 = 150.0f;
// 0x004275D8
RwReal dword_4275D8 = 400.0f;
// 0x004275DC
RwReal flt_4275DC = 90000.0f;
// 0x004275E0
RwReal flt_4275E0 = 40000.0f;

// match: ?flt_3CDB00@@3MB @ 0x003CDB00
// match: ?flt_4275B8@@3MA @ 0x004275B8
// match: ?flt_4275BC@@3MA @ 0x004275BC
// match: ?flt_4275C0@@3MA @ 0x004275C0
// match: ?flt_4275C4@@3MA @ 0x004275C4
// match: ?dword_4275C8@@3MA @ 0x004275C8
// match: ?flt_4275CC@@3MA @ 0x004275CC
// match: ?flt_4275D0@@3MA @ 0x004275D0
// match: ?flt_4275D4@@3MA @ 0x004275D4
// match: ?dword_4275D8@@3MA @ 0x004275D8
// match: ?flt_4275DC@@3MA @ 0x004275DC
// match: ?flt_4275E0@@3MA @ 0x004275E0


// match: __ehhandler$?sub_1FF10@AIData@@QAEHPAUtype_3DF8D8_04@@MMM@Z>1>8 @ 0x0041AE9C
// match: __ehhandler$?sub_1FF10@AIData@@QAEHPAUtype_3DF8D8_04@@MMM@Z>1 @ 0x0041AEA4

// match: __ehhandler$??0AIData@@QAE@XZ>1>8 @ 0x0041AC9C
// match: __ehhandler$??0AIData@@QAE@XZ>1 @ 0x0041AD9C
// match: __ehhandler$??1AIData@@QAE@XZ>1>8 @ 0x0041ADB8
// match: __ehhandler$??1AIData@@QAE@XZ>1 @ 0x0041AE80
// match: ??_C@_0DL@GFDINMMP@An?5AIData?5entity?5slot?5was?5not?5cl@ @ 0x003CDB04
// match: __real@bf800000 @ 0x003CDB40
// match: __real@43960000 @ 0x003CDB44
// match: __real@44160000 @ 0x003CDB48
// match: __real@7cf0bdc2 @ 0x003CDB4C
// match: __real@42f00000 @ 0x003CDB54
// match: __real@43480000 @ 0x003CDB58
// match: ??_C@_0L@LNGMCCML@LostTarget?$AA@ @ 0x003CDB5C
// match: ??_C@_0M@HMKGCLKC@FoundTarget?$AA@ @ 0x003CDB68
// match: __real@47afc800 @ 0x003CDB78
// match: ??_C@_0BM@JKAAHGEK@DefendAreaCoverPointInvalid?$AA@ @ 0x003CDB7C
// match: ??_C@_0BD@BMOFPAOM@PlayerAtCoverPoint?$AA@ @ 0x003CDB98
// match: ??_C@_0BH@LCGEOHN@AStar_LostFollowTarget?$AA@ @ 0x003CDBAC
// match: ??_C@_0BK@CDNGJFEE@AStar_ArrivedATCoverPoint?$AA@ @ 0x003CDBC4
// match: ??_C@_0BL@LHBKIMFB@AStar_ArrivedATDestination?$AA@ @ 0x003CDBE0
// match: ??_C@_0BC@EMBHMPKF@AStar_TargetMoved?$AA@ @ 0x003CDBFC
// match: __real@43fa0000 @ 0x003CDC10
// match: __real@46742400 @ 0x003CDC14
// match: __real@3f7ef9db @ 0x003CDC18
// match: ??_C@_0BD@CICDLKAJ@MatchedOrientation?$AA@ @ 0x003CDC1C
// match: ??_C@_0BH@OFFIIJKM@AIAction_GoGoGoToPoint?$AA@ @ 0x003CDC30
// match: ??_C@_0BA@LDMCDPON@PlayerDidGoGoGo?$AA@ @ 0x003CDC48
// match: __real@3f99999a @ 0x003CDC58
// match: __real@3d4ccccd @ 0x003CDC5C
// match: __real@c47a0000 @ 0x003CDC60
// match: __real@447a0000 @ 0x003CDC64
// match: __real@3f3504f3 @ 0x003CDC68
// match: __real@41700000 @ 0x003CDC6C
// match: __real@42000000 @ 0x003CDC70
// match: __real@3ecccccd @ 0x003CDC74
// match: __real@3c23d70a @ 0x003CDC7C
// match: __real@bfb645a1cac08312 @ 0x003CDC80
// match: __real@3fb645a1cac08312 @ 0x003CDC88
// match: __real@3f400000 @ 0x003CDC90
// match: __real@bdb295ea @ 0x003CDC94
// match: __real@3e800000 @ 0x003CDC98
// match: __real@be84816f @ 0x003CDC9C
// match: __real@3dcccccd @ 0x003CDCA0
// match: __real@bf000000 @ 0x003CDCA4
// match: __real@41a00000 @ 0x003CDCA8
// match: __real@43000000 @ 0x003CDCAC
// match: __real@3fcccccd @ 0x003CDCB0
// match: __real@41000000 @ 0x003CDCB4
// match: __real@42c80000 @ 0x003CDCB8
// match: __real@3f7d70a4 @ 0x003CDCBC
// match: __real@3d0b915c @ 0x003CDCC0
// match: __real@43c80000 @ 0x003CDCC4
// match: __real@44480000 @ 0x003CDCC8
// match: __real@3f4ccccd @ 0x003CDCCC
// match: __real@c0a00000 @ 0x003CDCD0
// match: __real@43340000 @ 0x003CDCD4
// match: __real@43b40000 @ 0x003CDCD8
// match: __real@43b18000 @ 0x003CDCDC
// match: __real@48afc800 @ 0x003CDCE0
// match: __real@3ea902de @ 0x003CDCE4
// match: __real@bfb652bd3c361134 @ 0x003CDCE8
// match: __real@3fb652bd3c361134 @ 0x003CDCF0
// match: __real@3fef851eb851eb85 @ 0x003CDCF8
// match: __real@3f19999a @ 0x003CDD00
// match: ??_C@_0BJ@NBEAFOMN@SetTaskCommand_GoToPoint?$AA@ @ 0x003CDD04
// match: __real@3f7ff2e5 @ 0x003CDD24
// match: __real@3fefd70a3d70a3d7 @ 0x003CDD28
// match: __real@3f733333 @ 0x003CDD30
// match: ??_C@_0BE@KGJNJFF@AttackPauseFinished?$AA@ @ 0x003CDD34
// match: ??_C@_0BF@IJGNGDEJ@LookOutEntityEmerged?$AA@ @ 0x003CDD48
// match: __real@44bb8000 @ 0x003CDD60
// match: ??_C@_0BE@NMHHLNNE@FireWeaponCompleted?$AA@ @ 0x003CDD64
// match: ??_C@_0BG@FHLPIDCL@VehicleCoverPointLost?$AA@ @ 0x003CDD78
// match: ??_C@_0BJ@FOFFFGOF@VehicleCoverPointInvalid?$AA@ @ 0x003CDD90
// match: __real@42fa0000 @ 0x003CDDAC
// match: ??_C@_0BH@EMBMACLA@VehicleCoverPointMoved?$AA@ @ 0x003CDDB0
// match: __real@3a83126f @ 0x003CDDC8
// match: __real@461c4000 @ 0x003CDDCC
// match: ??_C@_0CK@OOLJPNFB@FollowEntityOnSpline_ArrivedAtDe@ @ 0x003CDDD0
// match: __real@3f7ff972 @ 0x003CDDFC
// match: __real@42200000 @ 0x003CDE00
// match: __real@44610000 @ 0x003CDE04

// match: ??0AIData@@QAE@XZ @ 0x000154C0
// match: __ehhandler$??0AIData@@QAE@XZ-0x1FD @ 0x002FF180
// match: __ehhandler$??0AIData@@QAE@XZ @ 0x002FF37D
// sp-match: ??0AIData@@QAE@XZ @ 0x0001B710
// symbol: ??1type_154C0_80@@QAE@XZ = 0x001E41C0
AIData::AIData()
{
    RwInt32 l10;
    RwInt32 l14;

    unk_568 = 0;
    unk_4E0 = 0;
    unk_574 = 0;
    unk_54.sub_D48D0(0);
    unk_56C = 0;
    unk_570 = 0;
    unk_578 = 0;
    unk_57C = 0.0f;
    unk_49C = 0;
    unk_51C = 1;
    unk_520 = 0;
    unk_524 = 0;
    unk_52C = 0;
    unk_D18 = 0.0f;
    unk_D1C = 1.0f;
    unk_58 = 0;
    unk_5C = 0;
    unk_60 = -1;
    unk_64 = 0.0f;
    unk_518 = -1;
    unk_F58 = 0;
    unk_F60 = 0;
    unk_F54 = 0;
    unk_F5C = 0;
    unk_528 = 0;
    unk_594 = 0.0f;
    unk_DD4 = 0;
    unk_DD8 = 1;
    unk_F68 = 2500.0f;
    unk_F6C = 2500.0f;
    unk_68 = 0;
    unk_70 = 0;
    unk_480 = 0;
    unk_4F0 = 0;
    unk_1178 = 0.0f;
    set_xyz(&unk_DC4, 0.0f, 0.0f, 0.0f);
    unk_4A0 = 0;
    unk_4A4 = 0;
    unk_4A8 = 0.0f;
    unk_4AC = 0;
    unk_4B0 = 0;
    unk_4B4 = 0;
    memset(unk_4B8, 0, 8);
    unk_538 = -1;
    unk_53C = 0x57;
    unk_1048.unk_4C = 0;
    unk_1114.unk_4C = 0;
    unk_A24.unk_64.unk_2C = 0;
    unk_A24.unk_00 = -1;
    set_xyz(&unk_A24.unk_38, 0.0f, 0.0f, 0.0f);
    unk_5BC.unk_64.unk_2C = 0;
    unk_5BC.unk_00 = -1;
    set_xyz(&unk_5BC.unk_38, 0.0f, 0.0f, 0.0f);
    unk_734.unk_64.unk_2C = 0;
    unk_734.unk_00 = -1;
    set_xyz(&unk_734.unk_38, 0.0f, 0.0f, 0.0f);
    unk_8AC.unk_64.unk_2C = 0;
    unk_8AC.unk_00 = -1;
    set_xyz(&unk_8AC.unk_38, 0.0f, 0.0f, 0.0f);
    unk_117C.unk_64.unk_2C = 0;
    unk_117C.unk_00 = -1;
    set_xyz(&unk_117C.unk_38, 0.0f, 0.0f, 0.0f);
    unk_DDC.unk_64.unk_2C = 0;
    unk_DDC.unk_00 = -1;
    set_xyz(&unk_DDC.unk_38, 0.0f, 0.0f, 0.0f);
    sub_30850(0);
    unk_59C = 0;
    unk_5A4 = 0;
    unk_5A8 = 0;
    unk_5AC = 0;
    unk_580.sub_D48D0(0);
    unk_584.sub_D48D0(0);
    unk_58C = 0.0f;
    unk_590 = 0.0f;
    unk_588 = 0.0f;
    unk_F7C.sub_D48D0(0);
    unk_10C0.sub_D48D0(0);
    unk_1374.sub_D48D0(0);
    unk_1390.sub_D48D0(0);
    unk_137C.sub_D48D0(0);
    unk_138C = 0;
    unk_1174 = -1;
    unk_55C = 0;
    unk_534 = 1;
    unk_D88 = 200.0f;
    unk_7C = 0.0f;
    unk_D24 = 0.25f;
    unk_D14 = 0;
    set_xyz(&unk_4E4, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_F70, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_10B4, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_10A8, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_5B0, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_50C, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_D70, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_D7C, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_D8C, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_DA4, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_D98, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_DB0, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_1380, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_4F4, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_500, 0.0f, 0.0f, 0.0f);
    unk_DBC = 0;
    unk_DC0 = 0;
    for (l10 = 0; l10 < 32; l10++) {
        unk_80[l10].unk_04 &= ~1;
        unk_80[l10].unk_0C = 1.0e37f;
        unk_80[l10].unk_10 = 0.0f;
        unk_80[l10].unk_04 &= ~2;
        unk_80[l10].unk_08 = 1;
        set_xyz(&unk_80[l10].unk_14, 0.0f, 0.0f, 0.0f);
    }
    unk_544 = 0;
    unk_548 = 0;
    set_xyz(&unk_13A8, 0.0f, 0.0f, 0.0f);
    unk_13A0.unk_00 = 0;
    unk_13A0.unk_04 = 0;
    unk_13B4 = 0.0f;
    unk_13B8 = 0.0f;
    unk_13BC = 0.0f;
    unk_13DC = 0;
    unk_13C0.sub_D48D0(0);
    set_xyz(&unk_13C4, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_13D0, 0.0f, 0.0f, 0.0f);
    unk_13E0 = 0.0f;
    unk_00 = 0.0f;
    unk_13E8.sub_D48D0(0);
    unk_1404 = 3;
    set_xyz(&unk_13EC, 0.0f, 0.0f, 0.0f);
    set_xyz(&unk_13F8, 0.0f, 0.0f, 0.0f);
    unk_1408.unk_00 = 0;
    unk_1408.unk_04 = 0;
    unk_1410 = 0;
    unk_1414 = 0.0f;
    set_xyz(&unk_1418, 0.0f, 0.0f, 0.0f);
    unk_1424 = -1;
    unk_1428 = 0.0f;
    unk_142C = 0.0f;
    RwMatrixSetIdentity(&unk_D30);
    unk_560 = 0;
    unk_564 = 0;
    unk_1378 = 0.0f;
    unk_1394 = 1.0e37f;
    unk_74 = 0.0f;
    unk_78 = 0.0f;
    unk_139C = 0;
    unk_50 = 0;
    unk_4C = 0;
    unk_1430 = -1;
    unk_1434 = 0;
    unk_54C = 0;
    // (through a signed view: single player keeps both stores and ors the
    // cleared value, SP 0x1C0B7)
    *(RwInt32 *)&unk_54C |= 1;
    unk_550 = 0.0f;
    unk_554 = 0.0f;
    unk_558 = 0.0f;
    unk_1398 = 1.0e37f;
    unk_136C = 0;
    unk_1370.sub_D48D0(0);
    sub_23D90(&unk_12F4);
    sub_23D90(&unk_130C);
    sub_23D90(&unk_133C);
    unk_DD0 = -1;
    sub_23CD0(0, 0);
    for (l14 = 0; l14 < 3; l14++)
        unk_1444[l14].unk_00 = 0;
}
// match: ??0type_169D0@@QAE@XZ @ 0x000169D0
// sp-match: ??0type_169D0@@QAE@XZ @ 0x000137C0
// (AIData::set_unk_139C, an inline single player keeps out of line: sub_13EAD0 calls it, SP 0xE94CC)
// sp-match: ?set_unk_139C@AIData@@QAEXM@Z @ 0x00013810
// symbol: ??0type_169D0@@QAE@XZ = 0x000169D0
// (inline in single player, for this file only: AIData::AIData expands it in
// each path, SP 0x1B710, while the copy this object still emits, SP 0x137C0,
// is the one the A* finder's constructor calls, SP 0xBC0C6)
#ifdef CODFH_SP
inline
#endif
type_169D0::type_169D0()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1C = 0;
    unk_30 = 0;
    unk_20 = 0;
    unk_24 = 0;
    unk_2C = 0;
    unk_28 = -1;
    unk_30 = 0;
    unk_34 = 0;
    unk_38 = 0;
    unk_3C = 0;
    unk_40 = 0;
    unk_44 = 0;
    unk_48 = 0;
}
// match: ??1AIData@@QAE@XZ @ 0x00016AB0
// match: __ehhandler$??1AIData@@QAE@XZ-0x165 @ 0x002FF390
// match: __ehhandler$??1AIData@@QAE@XZ @ 0x002FF4F5
// sp-match: ??1AIData@@QAE@XZ @ 0x000181D0
AIData::~AIData()
{
    unk_54.sub_D48D0(0);
}
// match: sub_16BC0 @ 0x00016BC0
// sp-match: sub_16BC0 @ 0x00018230
void AIData::sub_16BC0(type_3D3548 *arg_0)
{
    unk_568 = arg_0;
    unk_4E0 = 0;
    unk_518 = sub_16E80(arg_0);
    if ((arg_0->unk_2C & 7) == 2)
        unk_540 = 1;
    else if ((arg_0->unk_2C & 7) == 1)
        unk_540 = 2;
    else
        unk_540 = 0;
}
// match: sub_16C50 @ 0x00016C50
// sp-match: sub_16C50 @ 0x00018290
void AIData::sub_16C50()
{
    sub_20C00();
    sub_238B0();
    sub_23100(&unk_12F4);
    sub_23100(&unk_130C);
    sub_23100(&unk_1324);
    sub_23100(&unk_133C);
    sub_23100(&unk_1354);
    sub_17080();
    if (unk_518 != -1)
        unk_438CA8[unk_518].sub_D48D0(0);
    sub_1FC70();
    sub_19010(0, 0);
    unk_568 = 0;
}
// match: sub_16D10 @ 0x00016D10
// sp-match: sub_16D10 @ 0x00013850
void sub_16D10()
{
    RwInt32 var_4;

    dword_438CA0 = 0;
    for (var_4 = 0; var_4 < 32; var_4++)
        unk_438CA8[var_4].sub_D48D0(0);
}
// match: sub_16D50 @ 0x00016D50
// sp-match: sub_16D50 @ 0x00018330
void sub_16D50()
{
    dword_438CA0 = 0;
    sub_16E30();
}
// match: sub_16D70 @ 0x00016D70
// sp-match: sub_16D70 @ 0x00018340
void AIData::sub_16D70(RwUInt32 arg_0)
{
    type_3D3548 *var_4;

    if ((arg_0 & 0x8000) != 0) {
        var_4 = unk_1374.sub_D4910();
        if (var_4 != 0)
            sub_17140(var_4->sub_CD550());
        sub_29ED0();
    }
    unk_49C |= arg_0;
}
// match: sub_16DD0 @ 0x00016DD0
// sp-match: sub_16DD0 @ 0x00018390
void AIData::sub_16DD0(RwUInt32 arg_0)
{
    RwInt32 var_4;

    if ((arg_0 & 0x8000) != 0 && (var_4 = unk_DBC) != 0)
        sub_17140(&unk_D70);
    unk_49C &= ~arg_0;
}
// match: sub_16E30 @ 0x00016E30
void sub_16E30()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 32; var_4++) {
        if (unk_438CA8[var_4].sub_D4910() != 0)
        {
#ifndef CODFH_SP // MP only: single player compiles the debug print out but keeps the check's call (SP 0x13888; the text is not in default.xbe)
            sub_19A750("An AIData entity slot was not cleared on restart/shutdown!");
#endif
        }
    }
}
// match: sub_16E80 @ 0x00016E80
// sp-match: sub_16E80 @ 0x000138A0
RwInt32 sub_16E80(type_3D3548 *arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 32; var_4++) {
        if (unk_438CA8[var_4].sub_D4910() == 0) {
            unk_438CA8[var_4].sub_D48D0(arg_0);
            return var_4;
        }
    }
    return -1;
}
// match: sub_16ED0 @ 0x00016ED0
// sp-match: sub_16ED0 @ 0x000138F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_154C0_80 *AIData::sub_16ED0(type_3D3548 *arg_0, RwBool *arg_4)
{
    RwInt32 var_4;
    RwV3d *local_8;

    if (arg_0 == 0 || arg_0->vf_120() == 0)
        return 0;
    var_4 = arg_0->vf_120()->unk_518;
    if (unk_80[var_4].unk_00.sub_D4910() == 0) {
        unk_80[var_4].unk_00.sub_D48D0(arg_0);
        unk_80[var_4].unk_04 &= ~1;
        unk_80[var_4].unk_04 &= ~2;
        unk_80[var_4].unk_08 = 1;
        unk_80[var_4].unk_10 = 0.0f;
        unk_80[var_4].unk_0C = 1e37f;
        local_8 = &unk_80[var_4].unk_14;
        local_8->x = 0.0f;
        local_8->y = 0.0f;
        local_8->z = 0.0f;
        if (arg_4 != 0)
            *arg_4 = 0;
    } else {
        if (arg_4 != 0)
            *arg_4 = 1;
    }
    return &unk_80[var_4];
}
// match: sub_17030 @ 0x00017030
// sp-match: sub_17030 @ 0x000139C0
void AIData::sub_17030(type_3DF30 *arg_0)
{
    RwInt32 var_4;

    unk_56C = arg_0;
    if (arg_0 != 0) {
        var_4 = arg_0->unk_2B4;
        unk_570 = var_4;
    } else {
        unk_570 = 0;
    }
}
// match: sub_17080 @ 0x00017080
// sp-match: sub_17080 @ 0x000139F0
void AIData::sub_17080()
{
    if (unk_56C != 0) {
        unk_56C->sub_3E7C0(unk_568);
        unk_56C = 0;
    }
}
// match: sub_170C0 @ 0x000170C0
// sp-match: sub_170C0 @ 0x00013A20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *AIData::sub_170C0()
{
    type_3D3548 *var_4;
    type_3DF30 *local_8;

    var_4 = 0;
    if (unk_56C != 0) {
        local_8 = unk_56C;
        var_4 = local_8->unk_2BC.sub_D4910();
    }
    return var_4;
}
// match: sub_17100 @ 0x00017100
// sp-match: sub_17100 @ 0x00013A40
RwReal AIData::sub_17100()
{
    type_154C0_80 *var_4;

    var_4 = sub_16ED0(unk_1374.sub_D4910(), 0);
    if (var_4 != 0)
        return var_4->unk_0C;
    return -1.0f;
}
// match: sub_17140 @ 0x00017140
// sp-match: sub_17140 @ 0x00013A70
void AIData::sub_17140(RwV3d *arg_0)
{
    RwV3d *var_4;

    unk_4F0 = arg_0;
    var_4 = &unk_50C;
    var_4->x = 0.0f;
    var_4->y = 0.0f;
    var_4->z = 0.0f;
}
// match: sub_17190 @ 0x00017190
// sp-match: sub_17190 @ 0x00013AA0
void AIData::sub_17190(RwReal arg_0)
{
    unk_DBC = 0;
    switch (unk_578) {
    case 32:
        unk_D88 = 75.0f;
        unk_DBC = 1;
        break;
    case 1:
    case 2:
    case 3:
    case 5:
    case 7:
    case 15:
    case 31:
    case 35:
    case 36:
    case 39:
    case 41:
    case 43:
    case 44:
    case 46:
    case 47:
        unk_D88 = 125.0f;
        unk_DBC = 1;
        break;
    case 4:
    case 14:
    case 30:
        unk_D88 = 125.0f;
        break;
    case 10:
    case 13:
        unk_D88 = 600.0f;
        break;
    case 8:
    case 9:
    case 11:
    case 12:
        unk_D88 = 400.0f;
        unk_DBC = 1;
        break;
    case 16:
    case 17:
    case 20:
    case 22:
    case 24:
    case 25:
    case 26:
    case 27:
    case 29:
        unk_D88 = 400.0f;
        break;
    case 18:
    case 19:
    case 21:
    case 23:
    case 28:
        unk_D88 = 400.0f;
        unk_DBC = 1;
        break;
    case 40:
    case 45:
        unk_D88 = 125.0f;
        unk_DBC = 1;
        break;
    }
}
// match: sub_172F0 @ 0x000172F0
// sp-match: sub_172F0 @ 0x0001C9F0
void AIData::sub_172F0(RwReal arg_0)
{
    type_154C0_80 *local_8;
    RwReal var_4;

    if (((unk_568->unk_28 >> 9) & 1) != 0) {
        unk_49C &= ~0x40;
        unk_49C &= ~0x20;
        return;
    }
    unk_57C = arg_0 + unk_57C;
    sub_17B90(arg_0);
    sub_30A50(arg_0);
    if (unk_5C != 4 && unk_5C != 0x1A && unk_5C != 0)
        unk_538 = 0;
    else
        unk_538 = -1;
    if (unk_7C > 0.0f)
        unk_7C -= arg_0;
    if (unk_1374.sub_D4910() != 0)
        unk_1378 = arg_0 + unk_1378;
    if (unk_13E0 > 0.0f) {
        unk_13E0 -= arg_0;
        if (unk_13E0 < 0.0f)
            unk_13E0 = 0.0f;
    }
    if (unk_1398 != 1.0e37f) {
        unk_1398 -= arg_0;
        if (unk_1398 < 0.0f) {
            unk_1398 = 1.0e37f;
            unk_F58 = 0;
        }
    }
    if (unk_5C == 4 || unk_5C == 0x1A || unk_5C == 3) {
        if (unk_550 < 600.0f && arg_0 + unk_550 >= 600.0f)
            unk_54C |= 2;
        unk_550 = arg_0 + unk_550;
        unk_554 = 0.0f;
    } else {
        if (unk_554 > 300.0f)
            unk_54C &= ~2;
        unk_554 = arg_0 + unk_554;
        unk_550 = 0.0f;
    }
    if (unk_1374.sub_D4910() != 0) {
        local_8 = sub_16ED0(unk_1374.sub_D4910(), 0);
        if (local_8 != 0 && local_8->unk_10 > 600.0f)
            unk_54C |= 4;
    }
    if (unk_558 > 0.0f) {
        unk_558 -= arg_0;
        unk_54C = 0;
    }
    unk_1394 = arg_0 + unk_1394;
    unk_74 -= arg_0;
    var_4 = RwV3dLength(unk_568->vf_0C8());
    if (var_4 > unk_590)
        unk_590 = var_4;
    switch (unk_578) {
    case 1:
        sub_198A0(arg_0);
        break;
    case 2:
    case 31:
    case 41:
    case 46:
    case 47:
        sub_192D0(arg_0);
        break;
    case 32:
        sub_19780(arg_0);
        break;
    case 4:
        if (unk_1374.sub_D4910() != 0)
            sub_19F90(unk_1374.sub_D4910(), arg_0);
        break;
    case 5:
    case 43:
    case 44:
        sub_190C0(arg_0);
        break;
    case 38:
    case 42:
        sub_1FB80(arg_0);
        break;
    case 39:
        sub_19CA0(arg_0);
        break;
    case 7:
        sub_198A0(arg_0);
        break;
    case 9:
        sub_1AE90(arg_0);
        break;
    case 8:
    case 11:
        sub_1B120(arg_0);
        break;
    case 10:
        sub_1AE80(unk_484, arg_0);
        break;
    case 12:
        sub_1B2B0(arg_0);
        break;
    case 13:
        sub_1B540(arg_0);
        break;
    case 14:
        sub_19F90(unk_580.sub_D4910(), arg_0);
        break;
    case 30:
        sub_1A190(unk_484, arg_0);
        break;
    case 15:
        sub_192D0(arg_0);
        break;
    case 16:
        sub_1D2C0(arg_0);
        break;
    case 17:
        sub_1D580(arg_0);
        break;
    case 19:
        sub_1D620(arg_0);
        break;
    case 18:
    case 21:
        sub_1DB60(arg_0);
        break;
    case 22:
        sub_1DF60(arg_0);
        break;
    case 20:
        sub_1CFE0(unk_484, arg_0);
        break;
    case 23:
        sub_1E210(arg_0);
        break;
    case 24:
    case 25:
        sub_1E530(arg_0);
        break;
    case 26:
        sub_1ECF0(arg_0);
        break;
    case 27:
        sub_1F2A0(arg_0);
        break;
    case 29:
        sub_1F470(arg_0);
        break;
    case 28:
        sub_1F390(arg_0);
        break;
    case 33:
        sub_1EA70(arg_0);
        break;
    case 34:
        sub_1D560(arg_0);
        break;
    case 35:
        sub_1F520(arg_0);
        break;
    case 36:
        sub_1F7C0(arg_0);
        break;
    case 37:
        sub_1FA00(arg_0);
        break;
    case 40:
        sub_19570(arg_0);
        break;
    case 45:
        sub_194E0(arg_0);
        break;
    }
    sub_212E0();
    sub_208F0();
}
// match: sub_17A20 @ 0x00017A20
// sp-match: sub_17A20 @ 0x00013B80
void AIData::sub_17A20(RwReal arg_0)
{
    type_3D3548 *var_4;

    switch (unk_578) {
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
        if (unk_1374.sub_D4910() != 0) {
            var_4 = unk_1374.sub_D4910();
            unk_137C.sub_D48D0(var_4);
        }
        break;
    }
}
// match: sub_17AB0 @ 0x00017AB0
// sp-match: sub_17AB0 @ 0x00013BF0
void AIData::sub_17AB0(RwInt32 arg_0)
{
    RwReal var_4;

    if (unk_60 != arg_0) {
        unk_60 = arg_0;
        unk_64 = 0.0f;
    }
    unk_5C = arg_0;
    switch (arg_0) {
    case 1:
        var_4 = RpRandom() * (1.0f / 2147483648.0f);
        unk_1178 = lerp(30.0f, 120.0f, var_4) * 60.0f;
        break;
    }
}
// match: sub_17B40 @ 0x00017B40
// sp-match: sub_17B40 @ 0x00013C40
RwReal AIData::sub_17B40()
{
    if (((unk_49C >> 4) & 1) != 0 && unk_5C == unk_60)
        return unk_64;
    unk_60 = unk_5C;
    unk_64 = 0.0f;
    return unk_64;
}
// match: sub_17B90 @ 0x00017B90
// sp-match: sub_17B90 @ 0x00013C70
void AIData::sub_17B90(RwReal arg_0)
{
    if (((unk_49C >> 4) & 1) != 0 && unk_5C == unk_60) {
        unk_64 = arg_0 + unk_64;
    } else {
        unk_60 = unk_5C;
        unk_64 = 0.0f;
    }
}
// An inline function with an empty body, standing for whatever statement
// states 6, 38 and 42 of AIData::sub_17BF0 held (a trace compiled out,
// perhaps). Evidence: those cases get a `jmp` of their own out of the switch;
// an empty case, `{}` or `;` is folded into the switch's exit instead, and a
// call to an empty inline function is what keeps the case's own label.
inline void empty_inline()
{
}
// match: sub_17BF0 @ 0x00017BF0
// sp-match: sub_17BF0 @ 0x000183D0
RwInt32 AIData::sub_17BF0(RwInt32 arg_0)
{
    RwV3d stk_18;
    type_14D180 *ebp_C;
    type_3DBC78 *v8;
    RwInt32 var_4;

    var_4 = 0;
    set_xyz(&unk_50C, 0.0f, 0.0f, 0.0f);
    if (unk_568 != 0)
        set_xyz(&unk_DA4, unk_568->sub_CD550()->x, unk_568->sub_CD550()->y,
                unk_568->sub_CD550()->z);
    sub_30850(0);
    unk_59C = 0;
    unk_DBC = 0;
    unk_DC0 = 0;
    sub_17140(0);
    switch (arg_0) {
    case 1:
        unk_594 = 0.0f;
        sub_29FC0(&unk_8AC, &unk_5BC, 1);
        unk_4E4 = unk_8AC.unk_20;
        sub_198A0(deltaTime);
        break;
    case 2:
    case 41:
        unk_528 = 0;
        unk_594 = 0.0f;
        if (arg_0 == 41)
            sub_29FC0(&unk_8AC, &unk_5BC, 1);
        else
            sub_29FC0(&unk_8AC, &unk_5BC, 0);
        unk_4E4 = unk_8AC.unk_20;
        var_4 = sub_192D0(deltaTime);
        break;
    case 32:
        unk_D24 = 0.25f;
        unk_D18 = unk_D14->sub_BA450(unk_568->sub_CD550(), 100.0f, 1.0f)
                + 200.0f / unk_D14->unk_24;
        if (unk_D18 > 1.0f)
            unk_D18 = 1.0f;
        unk_D14->sub_BA990(unk_D18, &unk_D70, &unk_D30);
        RwV3dSub(&unk_D8C, &unk_D70, unk_568->sub_CD550());
        unk_D8C.y = 0.0f;
        RwV3dNormalize(&unk_D8C, &unk_D8C);
        sub_17140(&unk_D70);
        sub_29ED0();
        sub_2E2F0();
        unk_D14->sub_BA990(1.0f, &unk_4E4, &unk_D30);
        unk_DBC = 1;
        break;
    case 12:
    case 23:
        unk_D24 = 0.1f;
        unk_D18 = unk_D14->sub_BA450(unk_568->sub_CD550(), 100.0f, 1.0f);
        unk_D14->sub_BA990(unk_D18, &unk_D70, &unk_D30);
        RwV3dSub(&unk_D8C, &unk_D70, unk_568->sub_CD550());
        unk_D8C.y = 0.0f;
        RwV3dNormalize(&unk_D8C, &unk_D8C);
        sub_17140(&unk_D70);
        sub_29ED0();
        sub_2E2F0();
        unk_D14->sub_BA990(1.0f, &unk_4E4, &unk_D30);
        unk_49C &= ~0x10000;
        unk_DBC = 1;
        unk_4B4 = 0;
        break;
    case 31:
        unk_528 = 0;
        sub_29FC0(&unk_8AC, &unk_734, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 4:
        if (unk_1374.sub_D4910() != 0) {
            sub_17140(unk_1374.sub_D4910()->sub_CD550());
            sub_19F90(unk_1374.sub_D4910(), deltaTime);
        }
        break;
    case 5:
    case 43:
    case 44:
        if (unk_578 != 43 && unk_578 != 44 && unk_578 != 5) {
            unk_528 = 0;
            if (arg_0 == 43 || arg_0 == 44)
                sub_29FC0(&unk_8AC, &unk_DDC, 1);
            else
                sub_29FC0(&unk_8AC, &unk_DDC, 0);
            unk_8AC.unk_33 = 1;
            unk_4E4 = unk_8AC.unk_20;
        } else {
            unk_DBC = 1;
            unk_DC0 = 1;
        }
        break;
    case 6:
    case 38:
    case 42:
        empty_inline();
        break;
    case 7:
        unk_594 = 0.0f;
        sub_29FC0(&unk_8AC, &unk_A24, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 8:
        unk_528 = 0;
        sub_29FC0(&unk_8AC, &unk_5BC, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 9:
        unk_594 = 0.0f;
        sub_29FC0(&unk_8AC, &unk_5BC, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 11:
        unk_594 = 0.0f;
        sub_29FC0(&unk_8AC, &unk_A24, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 14:
        sub_17140(unk_580.sub_D4910()->sub_CD550());
        break;
    case 15:
        unk_528 = 0;
        sub_29FC0(&unk_8AC, &unk_5BC, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 16:
    case 34:
        unk_4AC = 0;
        unk_4A8 = 30.0f;
        if (unk_568->vf_014() != 0 && unk_568->vf_014()->vf_2DC() != 0)
            arg_0 = 34;
        break;
    case 17:
        unk_4A8 = 60.0f;
        break;
    case 18:
        unk_528 = 0;
        unk_49C &= ~0x10000;
        sub_29FC0(&unk_8AC, &unk_5BC, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 19:
        unk_594 = 0.0f;
        unk_49C &= ~0x10000;
        sub_29FC0(&unk_8AC, &unk_5BC, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 21:
        unk_594 = 0.0f;
        unk_528 = 0;
        unk_49C &= ~0x10000;
        sub_29FC0(&unk_8AC, &unk_5BC, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 22:
        unk_4A8 = 0.0f;
        unk_49C &= ~0x10000;
        break;
    case 24:
    case 33:
        unk_8AC.unk_04 = 0;
        unk_49C &= ~0x10000;
        unk_4A4 = 0;
        if (unk_568->vf_014() != 0 && unk_568->vf_014()->vf_2DC() != 0)
            arg_0 = 33;
        break;
    case 25:
        sub_29FC0(&unk_8AC, &unk_5BC, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 26:
        unk_49C &= ~0x10000;
        sub_29FC0(&unk_8AC, &unk_DDC, 0);
        unk_4E4 = unk_8AC.unk_20;
        break;
    case 35:
        v8 = static_cast<type_3DBC78 *>(unk_12F4.unk_08.sub_D4910());
        if (v8 != 0) {
            ebp_C = v8->sub_155340(&unk_12F4);
            unk_4F4 = ebp_C->unk_14;
            sub_17140(&unk_4F4);
            unk_D70 = ebp_C->unk_14;
            unk_DBC = 1;
            sub_29ED0();
        }
        break;
    case 36:
        unk_594 = 0.0f;
        sub_29FC0(&unk_8AC, &unk_117C, 1);
        break;
    case 40:
        unk_D70 = unk_5B0;
        RwV3dSub(&unk_D8C, &unk_5B0, unk_568->sub_CD550());
        unk_D8C.y = 0.0f;
        RwV3dNormalize(&unk_D8C, &unk_D8C);
        unk_4E4 = *unk_568->sub_CD550();
        sub_29ED0();
        unk_DBC = 1;
    case 45:
        unk_DBC = 0;
        break;
    case 47:
        if (unk_568->vf_008() != 0 && unk_568->vf_008()->unk_610 != 0) {
            RwV3dSub(&stk_18, unk_568->sub_CD550(), unk_568->vf_008()->unk_610->get_unk_04());
            if (sub_31240(&unk_B9C, &stk_18, 5, 5.0f) == 0) {
                var_4 = 0;
                break;
            }
        } else {
            var_4 = 0;
            break;
        }
    case 46:
        unk_528 = 0;
        sub_29FC0(&unk_8AC, &unk_B9C, 0);
        unk_4E4 = unk_8AC.unk_20;
        var_4 = sub_192D0(deltaTime);
        break;
    }
    if (arg_0 != unk_578) {
        unk_57C = 0.0f;
        unk_578 = arg_0;
    }
    return var_4;
}
// match: sub_18BB0 @ 0x00018BB0
// sp-match: sub_18BB0 @ 0x00013CA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_18BB0(type_3D3548 *arg_0)
{
    type_3D3548 *var_4;
    type_154C0_80 *local_8;

    var_4 = unk_1374.sub_D4910();
    if (arg_0 != var_4) {
        unk_1378 = 0;
        set_unk_139C(0.0f);
        unk_54C &= ~4;
        unk_13E0 = 0.0f;
        if (var_4 != 0)
            unk_137C.sub_D48D0(var_4);
        if (arg_0 != 0) {
            unk_1374.sub_D48D0(arg_0);
            unk_530 = 0;
            unk_544 = 0;
            local_8 = sub_16ED0(arg_0, 0);
            if (local_8 == 0 || ((local_8->unk_04 >> 1) & 1) == 0)
                sub_40B10(unk_568, arg_0);
            unk_520 = 1;
            if (unk_568->vf_098() != 0)
                sub_6B5F0("FoundTarget", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        } else {
            unk_1374.sub_D48D0(0);
            if (var_4 != 0 && unk_568->vf_098() != 0)
                sub_6B5F0("LostTarget", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        }
    }
}
// match: sub_18DA0 @ 0x00018DA0
// sp-match: sub_18DA0 @ 0x00013DD0
void AIData::sub_18DA0(type_3D3548 *arg_0)
{
    if (arg_0 != 0 && arg_0->vf_120() != 0) {
        unk_1394 = 0;
        unk_1390.sub_D48D0(arg_0);
    }
}
// match: sub_18DF0 @ 0x00018DF0
// sp-match: sub_18DF0 @ 0x0001C150
RwBool AIData::sub_18DF0(type_3D3548 *arg_0, RwBool arg_4)
{
    type_154C0_80 *var_4;

    if (arg_0 != 0 && arg_0->vf_120() == 0)
        return 1;
    var_4 = sub_16ED0(arg_0, 0);
    return sub_18E90(var_4, arg_4);
}
// match: sub_18E40 @ 0x00018E40
// sp-match: sub_18E40 @ 0x0001C190
RwInt32 AIData::sub_18E40(type_3D3548 *arg_0, RwInt32 arg_4)
{
    type_154C0_80 *var_4;

    if (arg_0 != 0 && arg_0->vf_120() == 0)
        return 1;
    var_4 = sub_16ED0(arg_0, 0);
    return sub_18F00(var_4, arg_4);
}
// match: sub_18E90 @ 0x00018E90
// sp-match: sub_18E90 @ 0x00018CF0
RwBool AIData::sub_18E90(type_154C0_80 *arg_0, RwBool arg_4)
{
    type_3D3548 *var_4;

    if (arg_0 != 0) {
        if ((arg_0->unk_04 & 1) != 0)
            return 1;
        if (unk_534 != 0 && arg_4 != 0 && (var_4 = arg_0->unk_00.sub_D4910()) != 0
                && sub_18F80(var_4, arg_0) != 0)
            return 1;
    }
    return 0;
}
// match: sub_18F00 @ 0x00018F00
// sp-match: sub_18F00 @ 0x00018D40
RwInt32 AIData::sub_18F00(type_154C0_80 *arg_0, RwInt32 arg_4)
{
    type_3D3548 *var_4;

    if (arg_0 != 0) {
        if ((arg_0->unk_04 & 1) != 0 || ((arg_0->unk_04 >> 1) & 1) != 0)
            return 1;
        if (unk_534 != 0 && arg_4 != 0 && (var_4 = arg_0->unk_00.sub_D4910()) != 0
                && sub_18F80(var_4, arg_0) != 0)
            return 1;
    }
    return 0;
}
// match: sub_18F80 @ 0x00018F80
// sp-match: sub_18F80 @ 0x00013E10
RwBool AIData::sub_18F80(type_3D3548 *arg_0, type_154C0_80 *arg_4)
{
    RwV3d var_C;

    if (arg_0->vf_00C() != 0) {
        RwV3dSub(&var_C, arg_0->sub_CD550(), &arg_4->unk_14);
        if (RwV3dDotProduct(&var_C, &var_C) < 90000.0f)
            return 1;
    }
    return 0;
}
// match: sub_19010 @ 0x00019010
// sp-match: sub_19010 @ 0x00013EA0
void AIData::sub_19010(RwInt32 arg_0, RwInt32 arg_4)
{
    if (unk_568 == 0)
        return;
    if (unk_568->vf_098() == 0)
        return;
    unk_548 = arg_4 = 0;
    if (arg_0 != 0) {
        sub_31BE0(unk_568->vf_098());
    } else {
        sub_31C30(unk_568->vf_098());
        unk_544 = 0;
    }
}
// match: sub_190C0 @ 0x000190C0
// sp-match: sub_190C0 @ 0x00013F10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_190C0(RwReal arg_0)
{
    RwInt32 var_4;
    RwInt32 local_8;

    if (unk_8AC.unk_04 > 0) {
        var_4 = sub_2B740(&unk_8AC);
        if (var_4 > 0)
            sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        else if (unk_8AC.unk_31 != 0 && var_4 < 0)
            sub_6B5F0("AStar_ArrivedATCoverPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        else if (((unk_49C >> 23) & 1) != 0)
            sub_2D3A0();
        else if (((unk_49C >> 2) & 1) != 0)
            sub_2CE90(1, 260.0f, 300.0f);
    }
    if (unk_578 == 0x2C || unk_578 == 0x2B) {
        if (unk_578 == 0x2C && unk_13E8.sub_D4910() == 0)
            sub_6B5F0("AStar_LostFollowTarget", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        if (unk_F60 != 0) {
            local_8 = 0;
            if (sub_25DD0(unk_F60, &local_8) == 0) {
                if (local_8 != 0)
                    sub_6B5F0("PlayerAtCoverPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                else
                    sub_6B5F0("DefendAreaCoverPointInvalid", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            }
        }
    }
}
// match: sub_192D0 @ 0x000192D0
// sp-match: sub_192D0 @ 0x00014080
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_192D0(RwReal arg_0)
{
    RwInt32 var_4;
    RwInt32 loc8;
    RwV3d local_14;
    RwReal var18;

    var_4 = 0;
    unk_594 += arg_0;
    if (unk_8AC.unk_04 > 0) {
        loc8 = sub_2B740(&unk_8AC);
        if (loc8 > 0) {
            var_4 = 1;
            sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        } else if (unk_8AC.unk_31 != 0 && loc8 < 0) {
            sub_6B5F0("AStar_ArrivedATCoverPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        } else {
            if (((unk_49C >> 23) & 1) != 0)
                sub_2D3A0();
            if (((unk_49C >> 2) & 1) != 0 || ((unk_49C >> 25) & 1) != 0)
                sub_2CE90(1, 260.0f, 300.0f);
        }
        if (unk_578 == 0x29 && loc8 == 0 && unk_594 > 30.0f) {
            unk_594 = 0.0f;
            local_14.x = unk_13A8.x - unk_8AC.unk_20.x;
            local_14.y = unk_13A8.y - unk_8AC.unk_20.y;
            local_14.z = unk_13A8.z - unk_8AC.unk_20.z;
            var18 = RwV3dLength(&local_14);
            if (var18 > 500.0f)
                sub_6B5F0("AStar_TargetMoved", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        }
    }
    return var_4;
}
// match: sub_194E0 @ 0x000194E0
// sp-match: sub_194E0 @ 0x0001C1D0
void AIData::sub_194E0(RwReal arg_0)
{
    type_3D3548 *var_4;

    var_4 = unk_1374.sub_D4910();
    if (var_4 != 0) {
        unk_D70 = *var_4->sub_CD550();
        sub_19570(arg_0);
    } else {
        sub_6B5F0("AStar_LostFollowTarget", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
}
// match: sub_19570 @ 0x00019570
// sp-match: sub_19570 @ 0x00018D90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_19570(RwReal arg_0)
{
    RwReal var_4;
    RwV3d var_10;
    type_3D3548 *lv_14;

    if (((unk_568->unk_2C >> 5) & 1) != 0 && ((unk_49C >> 15) & 1) != 0) {
        sub_2C220(arg_0);
        lv_14 = unk_1374.sub_D4910();
        if (lv_14 != 0) {
            sub_17140(lv_14->vf_0CC());
            sub_19F90(lv_14, arg_0);
        }
    } else if (unk_598 == 0 && unk_59C == 0) {
        sub_17140(&unk_D70);
        sub_2E520(&unk_D70, arg_0);
    }
    if (((unk_49C >> 23) & 1) != 0)
        sub_2D3A0();
    else if (((unk_49C >> 2) & 1) != 0)
        sub_2CE90(1, 260.0f, 300.0f);
    RwV3dSub(&var_10, &unk_D70, unk_568->sub_CD550());
    var_10.y = 0.0f;
    var_4 = RwV3dDotProduct(&var_10, &var_10);
    if (var_4 < 15625.0f || RwV3dDotProduct(&unk_D8C, &var_10) < 0.0f)
        sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
}
// match: sub_19780 @ 0x00019780
// sp-match: sub_19780 @ 0x00018F00
void AIData::sub_19780(RwReal arg_0)
{
    type_3D3548 *var_4;

    if (sub_2DAA0(arg_0, unk_D88, 0) == 0) {
        if (((unk_568->unk_2C >> 5) & 1) != 0 && ((unk_49C >> 15) & 1) != 0) {
            sub_2C220(arg_0);
            var_4 = unk_1374.sub_D4910();
            if (var_4 != 0) {
                sub_17140(var_4->vf_0CC());
                sub_19F90(var_4, arg_0);
            }
        } else if (unk_598 == 0 && unk_59C == 0) {
            sub_17140(&unk_D70);
            sub_2E520(&unk_D70, arg_0);
        }
        if (((unk_49C >> 23) & 1) != 0)
            sub_2D3A0();
        else if (((unk_49C >> 2) & 1) != 0)
            sub_2CE90(1, 260.0f, 300.0f);
    }
}
// match: ?sub_198A0@AIData@@QAEXM@Z @ 0x000198A0
// sp-match: ?sub_198A0@AIData@@QAEXM@Z @ 0x00014210
void AIData::sub_198A0(RwReal arg_0)
{
    type_3D3548 *var_8;
    RwFrame *var_10;
    RwInt32 var_60;

    unk_594 += arg_0;
    if (unk_8AC.unk_04 > 0)
    {
        var_8 = unk_8AC.unk_50.sub_D4910();
        if (var_8)
        {
            var_10 = var_8->get_unk_340();
            if (var_10)
            {
                RwMatrix var_50;
                RwV3d var_5C;

                var_50 = *RwFrameGetLTM(var_10);
                RwV3dNormalize(&var_5C, &var_50.at);
                RwV3dScaleMacro(&var_5C, &var_5C, var_8->unk_E0);
                unk_50C = var_5C;
                RwV3dNormalize(&var_5C, &var_50.right);
                RwV3dScaleMacro(&var_5C, &var_5C, var_8->unk_D8);
                RwV3dAddMacro(&unk_50C, &unk_50C, &var_5C);
                RwV3dNormalize(&var_5C, &var_50.up);
                RwV3dScaleMacro(&var_5C, &var_5C, var_8->unk_DC);
                RwV3dAddMacro(&unk_50C, &unk_50C, &var_5C);
            }
            var_60 = sub_2B740(&unk_8AC);
            if (var_60 > 0)
            {
                sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            }
            else if (unk_8AC.unk_31 && var_60 < 0)
            {
                sub_6B5F0("AStar_ArrivedATCoverPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            }
            else if ((unk_49C >> 23) & 1)
            {
                sub_2D3A0();
            }
            if (((unk_49C >> 2) & 1) || ((unk_49C >> 25) & 1))
            {
                sub_2CE90(1, 260.0f, 300.0f);
            }
            if (!var_60 && unk_594 > 30.0f)
            {
                RwV3d *var_64;
                RwV3d var_70;
                RwReal var_74;

                unk_594 = 0.0f;
                var_64 = var_8->sub_CD550();
                var_70.x = var_64->x - unk_8AC.unk_20.x;
                var_70.y = var_64->y - unk_8AC.unk_20.y;
                var_70.z = var_64->z - unk_8AC.unk_20.z;
                var_74 = RwV3dLength((RwV3d *)&var_70);
                if (var_74 > 500.0f)
                {
                    sub_6B5F0("AStar_TargetMoved", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                }
            }
        }
        else
        {
            sub_6B5F0("AStar_LostFollowTarget", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            unk_8AC.unk_04 = 0;
        }
    }
}
// match: sub_19CA0 @ 0x00019CA0
// sp-match: sub_19CA0 @ 0x00014510
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_19CA0(RwReal arg_0)
{
    RwV3d stk_5C;
    RwV3d local_50;
    RwV3d *slot_44;
    RwV3d *l40;
    RwMatrix *var_3C;
    RwV3d v38;
    RwV3d var_2C;
    RwV3d v20;
    RwReal stk_14;
    RwFrame *l10;
    type_3DAFC8 *local_C;
    type_3DBC78 *lv_8;
    type_3D3548 *var_4;

    var_4 = unk_1374.sub_D4910();
    if (var_4 != 0) {
        local_C = unk_568->vf_008();
        lv_8 = 0;
        if (local_C->unk_624.sub_D4910() != 0) {
            lv_8 = local_C->unk_624.sub_D4910()->vf_010();
            if (lv_8 != 0 && lv_8->unk_B20 != -1) {
                l10 = local_C->get_unk_340();
                var_3C = RwFrameGetLTM(l10);
                l40 = &var_3C->pos;
                slot_44 = var_4->sub_CD550();
                stk_5C.x = slot_44->x - l40->x;
                stk_5C.y = 0.0f;
                stk_5C.z = slot_44->z - l40->z;
                if (stk_5C.x != 0.0f || stk_5C.y != 0.0f || stk_5C.z != 0.0f)
                    RwV3dNormalize(&v38, &stk_5C);
                RwV3dAssign(&local_50, &var_3C->at);
                local_50.y = 0.0f;
                RwV3dNormalize(&var_2C, &local_50);
                RwV3dCrossProduct(&v20, &var_2C, &v38);
                stk_14 = RwV3dDotProduct(&var_2C, &v38);
                if (stk_14 < 0.996f)
                    stk_14 = 0.0f;
                if (v20.y > 0.0f)
                    lv_8->vf_29C(1.0f - stk_14);
                else if (v20.y < 0.0f)
                    lv_8->vf_29C(-1.0f + stk_14);
            }
        }
    }
}
// match: sub_19ED0 @ 0x00019ED0
// sp-match: sub_19ED0 @ 0x000146D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwBool AIData::sub_19ED0()
{
    RwBool local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    var_4 = unk_1374.sub_D4910();
    if (var_4 != 0 && unk_A24.unk_64.unk_2C != 0 && var_4 == unk_A24.unk_50.sub_D4910())
        local_8 = 1;
    return local_8;
}
// match: sub_19F30 @ 0x00019F30
// sp-match: sub_19F30 @ 0x00014710
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwBool AIData::sub_19F30()
{
    RwBool local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    var_4 = unk_1374.sub_D4910();
    if (var_4 != 0 && unk_734.unk_64.unk_2C != 0 && var_4 == unk_10C0.sub_D4910())
        local_8 = 1;
    return local_8;
}
// match: ?sub_19F90@AIData@@QAEXPAUtype_3D3548@@M@Z @ 0x00019F90
// sp-match: ?sub_19F90@AIData@@QAEXPAUtype_3D3548@@M@Z @ 0x00014750
void AIData::sub_19F90(type_3D3548 *arg_0, RwReal arg_4)
{
    RwFrame *var_C;
    RwV3d *var_60;

    if (arg_0)
    {
        var_C = arg_0->get_unk_340();
        if (var_C)
        {
            RwMatrix var_50;
            RwV3d var_5C;

            var_50 = *RwFrameGetLTM(var_C);
            RwV3dNormalize(&var_5C, &var_50.at);
            RwV3dScaleMacro(&var_5C, &var_5C, arg_0->unk_E0);
            unk_50C = var_5C;
            RwV3dNormalize(&var_5C, &var_50.right);
            RwV3dScaleMacro(&var_5C, &var_5C, arg_0->unk_D8);
            RwV3dAddMacro(&unk_50C, &unk_50C, &var_5C);
            RwV3dNormalize(&var_5C, &var_50.up);
            RwV3dScaleMacro(&var_5C, &var_5C, arg_0->unk_DC);
            RwV3dAddMacro(&unk_50C, &unk_50C, &var_5C);
        }
        unk_4F0 = arg_0->sub_CD550();
        var_60 = unk_4F0;
        sub_2E520(var_60, arg_4);
    }
}
// match: sub_1A190 @ 0x0001A190
// sp-match: sub_1A190 @ 0x000148D0
void AIData::sub_1A190(RwV3d arg_0, RwReal arg_C)
{
    if (sub_2D5C0(&arg_0, 0, arg_C) != 0)
        sub_6B5F0("MatchedOrientation", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
}
// match: sub_1A1F0 @ 0x0001A1F0
// sp-match: sub_1A1F0 @ 0x00014920
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_1A1F0()
{
    RwInt32 var_4;
    type_3CE6D0 *v8;
    RwUInt32 varC;

    var_4 = 0;
    if (unk_1430 == -1 && ((unk_49C >> 26) & 1) != 0 && unk_51C != 0)
        var_4 = 1;
    if (var_4 != 0) {
        if ((((unk_49C >> 4) & 1) != 0 && (unk_5C == 0x19 || unk_5C == 0x1A))
                || (((unk_49C >> 4) & 1) == 0 && ((unk_49C >> 9) & 1) != 0
                    && (sub_238E0(0) != 0 || sub_23930() != 0)))
            var_4 = 0;
        if (var_4 != 0) {
            varC = unk_574;
            v8 = sub_3D3E0(varC);
            var_4 = v8->vf_024(unk_568);
        }
    }
    return var_4;
}
extern const RwReal flt_3D9480;
// match: sub_1A2E0 @ 0x0001A2E0
// sp-match: sub_1A2E0 @ 0x000149B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1A2E0()
{
    type_F8350 *local_24;
    type_F8350 *local_20;
    RwUInt32 var_1C;
    type_F8350 *local_18;
    RwV3d local_14;
    type_3CE6D0 *var_8;
    bool var_1;

    sub_6B5F0("PlayerDidGoGoGo", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    if (sub_1A1F0() != 0) {
        local_14 = *sub_1745A0(dword_429EB0)->sub_CD5A0();
        RwV3dNormalize(&local_14, &local_14);
        RwV3dScale(&local_14, &local_14, flt_3D9480);
        RwV3dAdd(&unk_1438, unk_568->sub_CD550(), &local_14);
        var_1C = unk_574;
        var_8 = sub_3D3E0(var_1C);
        var_1 = false;
        local_20 = unk_F60;
        if (local_20 != 0) {
            local_18 = 0;
            if (unk_1374.sub_D4910() != 0)
                local_18 = sub_23B60();
            else
                local_18 = unk_F54;
            if (local_18 != 0) {
                local_24 = unk_F60;
                if (local_24 != local_18 && ((local_18->unk_00 >> 2) & 1) == 0) {
                    sub_F7BA0(this, local_18, true);
                    sub_23670();
                    sub_22EF0(0);
                    var_8->vf_028(unk_568);
                    sub_6B5F0("AIAction_AttackCover", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                    unk_58 = 1;
                    sub_17AB0(1);
                    var_1 = true;
                }
            }
        }
        if (!var_1) {
            if (sub_31240(&unk_B9C, sub_1745A0(dword_429EB0)->sub_CD5A0(), 5, 500.0f) != 0) {
                var_8->vf_028(unk_568);
                sub_6B5F0("AIAction_GoGoGoToPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            }
        }
    }
}
// match: sub_1A5A0 @ 0x0001A5A0
// sp-match: sub_1A5A0 @ 0x00014BC0
void AIData::sub_1A5A0(RwInt32 arg_0)
{
    switch (arg_0) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        unk_1434 = 0;
        break;
    default:
        unk_1434 = 0;
        unk_1438.z = 0.0f;
        unk_1438.y = 0.0f;
        unk_1438.x = 0.0f;
        sub_23CD0(0, 1);
        break;
    }
    unk_1430 = arg_0;
}
// match: sub_1A630 @ 0x0001A630
// sp-match: sub_1A630 @ 0x00018FD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1A630(type_3DBC78 *arg_0, RwReal arg_4)
{
    RwReal var_2C;
    RwReal loc28;
    RwReal slot_24;
    RwReal v20;
    RwV3d slot_1C;
    RwReal local_10;
    RwV3d var_C;

    RwV3dSub(&var_C, unk_580.sub_D4910()->sub_CD550(), arg_0->sub_CD550());
    v20 = RwV3dLength(&var_C);
#ifdef CODFH_SP // shape: single player compares the other way round (SP 0x18FD0)
    if (v20 < unk_58C * 1.2f) {
#else
    if (unk_58C * 1.2f > v20) {
#endif
        slot_24 = RwV3dLength(unk_580.sub_D4910()->vf_0C8());
        loc28 = RwV3dLength(arg_0->vf_0C8());
        if (v20 > unk_58C) {
            var_2C = slot_24 / unk_590;
            arg_0->vf_280(arg_4 * var_2C);
#ifdef CODFH_SP // shape: single player's dot product takes its operands the other way round (SP 0x18FD0)
        } else if (loc28 > 0.0f
                && RwV3dDotProduct(arg_0->sub_CD5A0(), arg_0->vf_0C8()) > 0.0f) {
#else
        } else if (loc28 > 0.0f
                && RwV3dDotProduct(arg_0->vf_0C8(), arg_0->sub_CD5A0()) > 0.0f) {
#endif
            RwReal var_3C;
            RwReal v38;
            RwReal v34;
            RwReal v30;

            v30 = v20 / unk_58C;
            v34 = 5.0f * v30 - 5.0f;
            v38 = 0.0f;
            var_3C = -1.0f;
            arg_0->vf_280(sub_22C20(v34, var_3C, v38));
        } else {
            arg_0->vf_280(0.0f);
            arg_0->vf_290(1);
        }
    } else {
        var_C.y = 0.0f;
        RwV3dNormalize(&var_C, &var_C);
        RwV3dSub(&slot_1C, &unk_D70, arg_0->sub_CD550());
        slot_1C.y = 0.0f;
        RwV3dNormalize(&slot_1C, &slot_1C);
        local_10 = RwV3dDotProduct(&slot_1C, &var_C);
        if (local_10 < 0.0f)
            arg_0->vf_280(0.0f);
    }
}
// match: sub_1A950 @ 0x0001A950
// sp-match: sub_1A950 @ 0x00019280
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_1A950(RwReal arg_0, type_3DBC78 *arg_4, RwV3d *arg_8, RwReal *arg_C,
                          RwReal *arg_10, RwV3d *arg_14)
{
    RwV3d stk_4C;
    RwReal lv_40;
    RwV3d local_3C;
    RwReal v30;
    RwV3d var_2C;
    RwV3d *v20;
    RwInt32 slot_1C;
    RwReal local_18;
    RwReal local_14;
    RwV3d local_10;
    RwReal var_4;

    v20 = arg_4->sub_CD550();
    if (arg_14 == 0)
        arg_14 = &unk_D70;
    stk_4C.x = arg_14->x - v20->x;
    stk_4C.y = 0.0f;
    stk_4C.z = arg_14->z - v20->z;
    if (stk_4C.x == 0.0f && stk_4C.z == 0.0f)
        return 0;
    RwV3dNormalize(&stk_4C, &stk_4C);
    local_3C = *arg_4->sub_CD5A0();
    if (local_3C.y == 1.0f)
        return 0;
    local_3C.y = 0.0f;
    RwV3dNormalize(&local_3C, &local_3C);
    RwV3dCrossProduct(arg_8, &local_3C, &stk_4C);
    *arg_10 = 1.0f;
    var_4 = RwV3dDotProduct(&local_3C, &stk_4C);
    memcpy(unk_4B8[1], unk_4B8[0], 0x20);
    unk_4B8[0][0] = 1.0f - var_4;
    unk_4B8[0][1] = arg_0;
    lv_40 = 0.0f;
    for (slot_1C = 1; slot_1C < 5; slot_1C++)
        lv_40 += (unk_4B8[slot_1C][0] * unk_4B8[slot_1C][1]);
    v30 = (unk_4B8[0][0] - unk_4B8[1][0]) / arg_0;
    *arg_C = 2.0f * unk_4B8[0][0] + 0.4f * lv_40 + 32.0f * v30;
    local_14 = arg_4->unk_450.sub_14C140();
    local_18 = 0.25f;
    if (local_14 > 15.0f)
#ifdef CODFH_SP // shape: single player divides the limit first (SP 0x19280)
        local_18 = 0.25f * (15.0f / local_14);
#else
        local_18 *= 15.0f / local_14;
#endif
    if (fabs(*arg_C) < local_18)
        *arg_10 = 1.0f - fabs(*arg_C) / local_18;
    else if (local_14 < 5.0f)
        *arg_10 = 0.1f;
    else
        *arg_10 = 0.0f;
    if (var_4 < 0.0f) {
        unk_4A0 = 1;
        *arg_10 = -0.1f;
        if (local_14 < 0.0f)
            *arg_C = *arg_C * -1.0f;
        unk_49C &= ~0x800;
    } else if (var_4 < 0.70710677f) {
        if (unk_4A0 == 0 && ((unk_49C >> 11) & 1) != 0) {
            var_2C = *arg_4->sub_CDBE0();
            var_2C.y = 0.0f;
            RwV3dNormalize(&var_2C, &var_2C);
            if (arg_8->y > 0.0f)
                RwV3dScale(&var_2C, &var_2C, 1000.0f);
            else
                RwV3dScale(&var_2C, &var_2C, -1000.0f);
            RwV3dAdd(&local_10, v20, &var_2C);
            stk_4C.x = arg_14->x - local_10.x;
            stk_4C.z = arg_14->z - local_10.z;
            if (RwV3dLength(&stk_4C) < 1000.0f)
                unk_4A0 = 1;
            unk_49C &= ~0x800;
        }
        if (unk_4A0 != 0) {
            *arg_10 = -0.1f;
            *arg_C = *arg_C * -1.0f;
        } else if (fabs(local_14) < 5.0f) {
            *arg_10 = 0.1f;
        }
    } else if (*arg_C > 0.05f) {
        if (local_14 > 0.0f) {
            unk_4A0 = 0;
        } else {
            unk_4A0 = 1;
            *arg_C = *arg_C * -1.0f;
        }
    } else {
        unk_4A0 = 0;
    }
    {
        RwReal local_54;
        RwReal local_50;

        local_50 = 1.0f;
        local_54 = -1.0f;
        *arg_C = sub_22C20(*arg_C, local_54, local_50);
    }
    return 1;
}
// match: sub_1AE80 @ 0x0001AE80
void AIData::sub_1AE80(RwV3d arg_0, RwReal arg_C)
{
}
// match: sub_1AE90 @ 0x0001AE90
// sp-match: sub_1AE90 @ 0x000196F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1AE90(RwReal arg_0)
{
    RwInt32 v20;
    RwReal slot_1C;
    type_3D3548 *local_18;
    RwV3d local_14;
    RwReal lv_8;
    type_3DBC78 *var_4;

    if (unk_8AC.unk_04 <= 0)
        return;
    local_18 = unk_8AC.unk_50.sub_D4910();
    if (local_18 == 0) {
        sub_6B5F0("AStar_LostFollowTarget", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        unk_8AC.unk_04 = 0;
        return;
    }
    unk_594 += arg_0;
    if (unk_594 > 60.0f) {
        RwReal ebp_34;
        RwV3d *var_30;
        RwV3d var_2C;

        unk_594 = 0.0f;
        var_30 = local_18->sub_CD550();
        var_2C.x = var_30->x - unk_8AC.unk_20.x;
        var_2C.y = var_30->y - unk_8AC.unk_20.y;
        var_2C.z = var_30->z - unk_8AC.unk_20.z;
        ebp_34 = RwV3dLength(&var_2C);
        if (ebp_34 > 1000.0f)
            sub_6B5F0("AStar_TargetMoved", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
    var_4 = unk_568->vf_010();
    sub_1A950(arg_0, var_4, &local_14, &slot_1C, &lv_8, 0);
    if (local_14.y > 0.0f)
        var_4->vf_28C(slot_1C);
    else if (local_14.y < 0.0f)
        var_4->vf_28C(-1.0f * slot_1C);
    var_4->vf_280(lv_8);
    v20 = sub_2B740(&unk_8AC);
    if (v20 > 0) {
        unk_8AC.unk_04 = 0;
        sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(var_4->vf_098()), 0, 0, 0, 0, true, false);
    } else if (unk_8AC.unk_31 != 0 && v20 < 0) {
        unk_8AC.unk_04 = 0;
        sub_6B5F0("AStar_ArrivedATCoverPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
}
// match: sub_1B120 @ 0x0001B120
// sp-match: sub_1B120 @ 0x000198D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1B120(RwReal arg_0)
{
    type_3DBC78 *var_4;
    RwReal loc8;
    RwV3d local_14;
    RwReal var18;
    RwInt32 var_1C;

    if (unk_8AC.unk_04 <= 0)
        return;
    var_4 = unk_568->vf_010();
    sub_1A950(arg_0, var_4, &local_14, &var18, &loc8, 0);
    if (local_14.y > 0.0f)
        var_4->vf_28C(var18);
    else if (local_14.y < 0.0f)
        var_4->vf_28C(-1.0f * var18);
    var_4->vf_280(loc8);
    if (unk_4B0 != 0) {
        var_4->vf_280(0.0f);
        var_4->vf_290(1);
    }
    var_1C = sub_2B740(&unk_8AC);
    if (var_1C > 0) {
        unk_8AC.unk_04 = 0;
        sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(var_4->vf_098()), 0, 0, 0, 0, true, false);
    } else if (unk_8AC.unk_31 != 0 && var_1C < 0) {
        unk_8AC.unk_04 = 0;
        sub_6B5F0("AStar_ArrivedATCoverPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
}
// match: sub_1B2B0 @ 0x0001B2B0
// sp-match: sub_1B2B0 @ 0x00019A20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1B2B0(RwReal arg_0)
{
    type_3DBC78 *l4;
    RwReal var_8;
    RwReal fp_C;
    RwV3d var_18;
    RwReal var_1C;
    RwReal l20;
    RwReal fp_24;
    RwV3d var_30;

    l4 = unk_568->vf_010();
    sub_2DAA0(arg_0, unk_D88, 0);
    if (sub_1A950(arg_0, l4, &var_18, &var_1C, &var_8, &unk_D70) == 0)
        return;
    if (var_18.y > 0.0f)
        l4->vf_28C(var_1C);
    else if (var_18.y < 0.0f)
        l4->vf_28C(-1.0f * var_1C);
    l4->vf_280(var_8);
    if (unk_4B0 != 0) {
        l4->vf_280(0.0f);
        l4->vf_290(1);
    } else if (unk_4B4 != 0) {
        fp_C = l4->unk_450.sub_14C140();
        if (fp_C < 1.0f) {
            unk_4B4 = 0;
        } else {
            l4->vf_280(0.0f);
            l4->vf_290(1);
        }
    } else if (((unk_49C >> 27) & 1) != 0 && unk_D1C - unk_D1C * 0.01f <= unk_D18
            && ((unk_D14->unk_1C & 3) == 0 || (unk_D14->unk_1C & 3) == 2)) {
        RwV3dSub(&var_30, l4->sub_CD550(), &unk_4E4);
        fp_24 = RwV3dDotProduct(&var_30, &var_30);
        l20 = (fp_C = l4->unk_450.sub_14C140()) * fp_C;
        if (fp_24 < l20 * flt_4275C0)
            unk_4B4 = 1;
    } else if (unk_580.sub_D4910() != 0) {
        sub_1A630(l4, var_8);
    }
}
// match: sub_1B540 @ 0x0001B540
// sp-match: sub_1B540 @ 0x000D60D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Disabled: it jumps to its end at once (a `goto`, so the compiler still
// emits the rest: a vehicle turned towards a target by the side of a cross
// product and pitched by a height over a bounding box's diagonal), whose
// locals are never set; four more are never used.
void AIData::sub_1B540(RwReal arg_0)
{
    RwReal m_6C;
    RwReal q68;
    RwReal var_64;
    RwReal stk_60;
    type_3DBC78 *y5C;
    RwInt32 slot_58;
    RwBBox frm_54;
    RwInt32 ebp_3C;
    RwReal lcl_38;
    RwReal r34;
    RwV3d *lv_30;
    RwV3d *fp_2C;
    RwReal q28;
    RwV3d frm_24;
    RwV3d m_18;
    RwV3d slot_C;

    ebp_3C = 1;
    goto end;
    // A compiled-out check (it moves the registers one step).
    { if (0) { } }
    RwV3dCrossProduct(&slot_C, &m_18, &frm_24);
    var_64 = RwV3dDotProduct(&m_18, &frm_24);
    var_64 *= var_64;
    if (var_64 < 0.996f)
    {
        var_64 = 0.0f;
        ebp_3C = 0;
    }
    if (slot_C.y > 0.0f)
        y5C->vf_294(1.0f - var_64, 1.0f);
    else if (slot_C.y < 0.0f)
        y5C->vf_294(-1.0f + var_64, 1.0f);
    frm_54.sup.y = lv_30->y - fp_2C->y;
    r34 = (lv_30->y - fp_2C->y) / RwV3dLength((RwV3d *)&frm_54);
    stk_60 = r34 - q28;
    if (stk_60 < 0.087 && stk_60 > -0.087)
        y5C->vf_298(-stk_60, 1.0f);
    else if (stk_60 > 0.0f)
    {
        y5C->vf_298(-1.0f, 1.0f);
        ebp_3C = 0;
    }
    else
    {
        y5C->vf_298(1.0f, 1.0f);
        ebp_3C = 0;
    }
    if (ebp_3C)
        y5C->vf_2A8(0, 0, 0);
end:
    ;
}
// match: sub_1B710 @ 0x0001B710
// sp-match: sub_1B710 @ 0x00019C20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_1B710(RwReal arg_0, type_3DC048 *arg_4, RwV3d *arg_8, RwReal *arg_C,
                          RwReal *arg_10, RwV3d *arg_14)
{
    RwV3d l38;
    RwReal lcl_2C;
    RwV3d local_28;
    RwReal var_1C;
    RwReal var18;
    RwV3d *stk_14;
    RwInt32 l10;
    RwReal local_C;
    RwReal lv_8;
    RwReal var_4;

    stk_14 = arg_4->sub_CD550();
    if (arg_14 == 0)
        arg_14 = &unk_D70;
    l38.x = arg_14->x - stk_14->x;
    l38.y = 0.0f;
    l38.z = arg_14->z - stk_14->z;
    if (l38.x == 0.0f && l38.z == 0.0f)
        return 0;
    RwV3dNormalize(&l38, &l38);
    local_28 = *arg_4->sub_CD5A0();
    if (local_28.y == 1.0f || local_28.y == -1.0f)
        return 0;
    var18 = local_28.y;
    local_28.y = 0.0f;
    RwV3dNormalize(&local_28, &local_28);
    if (((unk_49C >> 16) & 1) != 0) {
        RwV3dScale(&local_28, &local_28, -1.0f);
        var18 = var18 * -1.0f;
    }
    RwV3dCrossProduct(arg_8, &local_28, &l38);
    *arg_10 = 1.0f;
    var_4 = RwV3dDotProduct(&local_28, &l38);
    memcpy(unk_4B8[1], unk_4B8[0], 0x20);
    unk_4B8[0][0] = 1.0f - var_4;
    unk_4B8[0][1] = arg_0;
    lcl_2C = 0.0f;
    for (l10 = 1; l10 < 5; l10++)
        lcl_2C += (unk_4B8[l10][0] * unk_4B8[l10][1]);
    var_1C = (unk_4B8[0][0] - unk_4B8[1][0]) / arg_0;
    *arg_C = 8.0f * unk_4B8[0][0] + 1.6f * lcl_2C + 128.0f * var_1C;
    local_C = arg_4->unk_450.sub_14C140();
    lv_8 = 4.0f;
    if (local_C > 20.0f)
#ifdef CODFH_SP // shape: single player divides the limit first (SP 0x19C20)
        lv_8 = 4.0f * (20.0f / local_C);
#else
        lv_8 *= 20.0f / local_C;
#endif
    if (fabs(*arg_C) < lv_8)
        *arg_10 = 1.0f - fabs(*arg_C) / lv_8;
    else
        *arg_10 = 0.0f;
    if (var18 < -0.5f)
        *arg_10 = *arg_10 * 0.1f;
    else if (var18 < -0.2588f)
        *arg_10 = *arg_10 * 0.25f;
    else if (var18 < -0.0872f)
        *arg_10 = *arg_10 * 0.75f;
    if (((unk_49C >> 16) & 1) != 0)
        *arg_10 = *arg_10 * -1.0f;
    {
        RwReal l40;
        RwReal var_3C;

        var_3C = 1.0f;
        l40 = -1.0f;
        *arg_C = sub_22C20(*arg_C, l40, var_3C);
    }
    return 1;
}
// match: ?sub_1BAA0@AIData@@QAEHPAUtype_3DC048@@PAURwV3d@@M1PAM221@Z @ 0x0001BAA0
// sp-match: ?sub_1BAA0@AIData@@QAEHPAUtype_3DC048@@PAURwV3d@@M1PAM221@Z @ 0x00014C20
RwInt32 AIData::sub_1BAA0(type_3DC048 *arg_0, RwV3d *arg_4, RwReal arg_8, RwV3d *arg_C, RwReal *arg_10,
                          RwReal *arg_14, RwReal *arg_18, RwV3d *arg_1C)
{
    RpClump *var_8;
    RwMatrix var_50;
    RwV3d *var_54;
    RwV3d var_60;
    RwReal var_64;
    RwV3d var_70;
    RwV3d var_7C;
    RwV3d var_88;

    if (!arg_0->unk_DFC.unk_00[0].unk_38)
    {
        return 0;
    }
    var_8 = arg_0->unk_25C.unk_08;
    if (!sub_EC2D0(var_8, (RwInt32)&var_50, arg_0->unk_DFC.unk_00[0].unk_38, 0, 1))
    {
        return 0;
    }
    var_54 = &var_50.pos;
    if (arg_1C)
    {
        *arg_1C = *var_54;
    }
    RwV3dSubMacro(&var_60, arg_4, var_54);
    var_64 = RwV3dLength((RwV3d *)&var_60);
    *arg_14 = var_60.y / var_64;
    if (var_60.y == 1.0f || var_60.y == -1.0f)
    {
        return 0;
    }
    var_60.y = 0.0f;
    RwV3dNormalize(&var_70, &var_60);
    var_7C = var_50.at;
    *arg_18 = var_7C.y;
    if (*arg_18 == 1.0f || *arg_18 == -1.0f)
    {
        return 0;
    }
    var_7C.y = 0.0f;
    RwV3dNormalize(&var_88, &var_7C);
    RwV3dCrossProductMacro(arg_C, &var_88, &var_70);
    *arg_10 = RwV3dDotProductMacro(&var_88, &var_70);
    if (var_64 < 800.0f)
    {
        if (var_64 > 400.0f)
        {
            *arg_10 *= 0.034074172f * ((800.0f - var_64) / 400.0f) + 1.0f;
            if (*arg_10 < 0.0f)
            {
                *arg_10 *= -1.0f;
            }
            if (*arg_10 > 1.0f)
            {
                *arg_10 = 1.0f;
            }
        }
        else
        {
            *arg_10 = 1.0f;
        }
    }
    if (*arg_10 < 0.99f)
    {
        *arg_10 = 0.0f;
    }
    else
    {
        *arg_10 = (*arg_10 - 0.99f) * 100.0f;
    }
    return 1;
}
// match: ?sub_1BD50@AIData@@QAEHPAUtype_3DC048@@PAURwV3d@@1PAM@Z @ 0x0001BD50
// sp-match: ?sub_1BD50@AIData@@QAEHPAUtype_3DC048@@PAURwV3d@@1PAM@Z @ 0x00014E90
RwInt32 AIData::sub_1BD50(type_3DC048 *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C)
{
    RpClump *var_8;
    RwMatrix var_50;
    RwV3d *var_54;
    RwV3d var_60;
    RwV3d var_6C;
    RwV3d var_78;
    RwV3d var_84;

    if (!arg_0->unk_DFC.unk_00[2].unk_38)
    {
        return 0;
    }
    var_8 = arg_0->unk_25C.unk_08;
    if (!sub_EC2D0(var_8, (RwInt32)&var_50, arg_0->unk_DFC.unk_00[2].unk_38, 0, 1))
    {
        return 0;
    }
    var_54 = &var_50.pos;
    RwV3dSubMacro(&var_60, arg_4, var_54);
    if (var_60.y == 1.0f || var_60.y == -1.0f)
    {
        return 0;
    }
    var_60.y = 0.0f;
    RwV3dNormalize(&var_6C, &var_60);
    var_78 = var_50.at;
    var_78.y = 0.0f;
    RwV3dNormalize(&var_84, &var_78);
    RwV3dCrossProductMacro(arg_8, &var_84, &var_6C);
    *arg_C = RwV3dDotProductMacro(&var_84, &var_6C);
    if (*arg_C < 0.8f)
    {
        *arg_C = 0.0f;
    }
    else
    {
        *arg_C = (*arg_C - 0.8f) * 5.0f;
    }
    return 1;
}
// match: sub_1BEF0 @ 0x0001BEF0
// sp-match: sub_1BEF0 @ 0x00015010
RwInt32 AIData::sub_1BEF0(type_3DC048 *arg_0, type_3D3548 *arg_4, RwV3d *arg_8, RwInt32 arg_C)
{
    type_92430 var_2C;

    arg_4->vf_110(arg_8, arg_0, 0);
    if (arg_C != 0
            && (arg_4->vf_008() != 0 || (arg_4->vf_00C() != 0 && arg_4->vf_00C()->vf_200() == 0))) {
        sub_92430(arg_8, &var_2C, 30.0f);
        if (var_2C.unk_20 != 0 && arg_0->sub_CD550()->y > var_2C.unk_08.y)
            *arg_8 = var_2C.unk_08;
    }
    return 1;
}
// match: ?sub_1BFB0@AIData@@QAEXPAUtype_3DC048@@@Z @ 0x0001BFB0
// sp-match: ?sub_1BFB0@AIData@@QAEXPAUtype_3DC048@@@Z @ 0x000150C0
void AIData::sub_1BFB0(type_3DC048 *arg_0)
{
    RpClump *var_C;
    RwMatrix var_50;
    RwV3d var_5C;
    RwV3d var_68;
    RwV3d var_74;
    RwReal var_78;

    if (arg_0->unk_28DC == -1)
    {
        return;
    }
    switch (unk_578)
    {
    case 0x17:
        if (!((unk_49C >> 7) & 1) && arg_0->unk_DFC.unk_00[0].unk_38
            && (var_C = arg_0->unk_25C.unk_08, sub_EC2D0(var_C, (RwInt32)&var_50, arg_0->unk_DFC.unk_00[0].unk_38, 0, 1)))
        {
            RwV3dSubMacro(&var_5C, &unk_DA4, &var_50.pos);
            if (RwV3dDotProductMacro(&var_5C, &var_5C) < 360000.0f)
            {
                arg_0->vf_294(0.0f, 1.0f);
                return;
            }
            var_5C.y = 0.0f;
            var_68 = var_50.at;
            var_68.y = 0.0f;
            RwV3dNormalize(&var_5C, &var_5C);
            RwV3dNormalize(&var_68, &var_68);
            RwV3dCrossProductMacro(&var_74, &var_68, &var_5C);
            var_78 = RwV3dDotProductMacro(&var_68, &var_5C);
            if (var_74.y > 0.0f)
            {
                arg_0->vf_294(1.0f - var_78, 1.0f);
            }
            else if (var_74.y < 0.0f)
            {
                arg_0->vf_294(-1.0f + var_78, 1.0f);
            }
        }
        else if (arg_0->unk_2868 > 355.0f)
        {
            arg_0->vf_294((360.0f - arg_0->unk_2868) / 5.0f, 1.0f);
        }
        else if (arg_0->unk_2868 > 180.0f)
        {
            arg_0->vf_294(1.0f, 1.0f);
        }
        else if (arg_0->unk_2868 < 5.0f)
        {
            arg_0->vf_294(-arg_0->unk_2868 / 5.0f, 1.0f);
        }
        else
        {
            arg_0->vf_294(-1.0f, 1.0f);
        }
        if (arg_0->unk_2870 > 0.0f)
        {
            if (arg_0->unk_2870 < 5.0f)
            {
                arg_0->vf_298(arg_0->unk_2870 / -5.0f, 1.0f);
            }
            else
            {
                arg_0->vf_298(-1.0f, 1.0f);
            }
        }
        else if (arg_0->unk_2870 > -5.0f)
        {
            arg_0->vf_298(arg_0->unk_2870 / -5.0f, 1.0f);
        }
        else
        {
            arg_0->vf_298(1.0f, 1.0f);
        }
        break;
    default:
        if (arg_0->unk_2868 > 355.0f)
        {
            arg_0->vf_294((360.0f - arg_0->unk_2868) / 5.0f, 1.0f);
        }
        else if (arg_0->unk_2868 > 180.0f)
        {
            arg_0->vf_294(1.0f, 1.0f);
        }
        else if (arg_0->unk_2868 < 5.0f)
        {
            arg_0->vf_294(-arg_0->unk_2868 / 5.0f, 1.0f);
        }
        else
        {
            arg_0->vf_294(-1.0f, 1.0f);
        }
        if (arg_0->unk_2870 > 0.0f)
        {
            if (arg_0->unk_2870 < 5.0f)
            {
                arg_0->vf_298(arg_0->unk_2870 / -5.0f, 1.0f);
            }
            else
            {
                arg_0->vf_298(-1.0f, 1.0f);
            }
        }
        else if (arg_0->unk_2870 > -5.0f)
        {
            arg_0->vf_298(arg_0->unk_2870 / -5.0f, 1.0f);
        }
        else
        {
            arg_0->vf_298(1.0f, 1.0f);
        }
    }
}
// match: sub_1C4F0 @ 0x0001C4F0
// sp-match: sub_1C4F0 @ 0x000154A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_1C4F0(type_3DC048 *arg_0, type_3D3548 *arg_4, RwReal arg_8, RwInt32 arg_C)
{
    RwReal bp_44;
    RwInt32 l40;
    RwReal var_3C;
    RwV3d l38;
    type_154C0_80 *lcl_2C;
    RwInt32 local_28;
    RwReal local_24;
    RwInt32 local_20;
    RwV3d var_1C;
    RwReal local_10;
    RwV3d var_C;

    l40 = 1;
    local_28 = 1;
    local_20 = 0;
    lcl_2C = sub_16ED0(arg_4, 0);
    if (lcl_2C != 0 && (lcl_2C->unk_04 & 1) == 0 && arg_0->vf_018() == 0)
        return 0;
    if (arg_4->vf_008() != 0 || arg_4->vf_024() != 0
            || (arg_4->vf_00C() != 0 && arg_4->vf_00C()->vf_200() == 0))
        local_20 = 1;
    sub_1BEF0(arg_0, arg_4, &l38, 1);
    if (sub_1BAA0(arg_0, &l38, arg_8, &var_1C, &local_10, &var_3C, &local_24, &var_C) != 0) {
        if (local_10 < 0.6f) {
            l40 = 0;
            local_28 = 0;
        } else if (local_10 < 0.985) {
            l40 = 0;
        }
        if (var_1C.y > 0.0f)
            arg_0->vf_294(1.0f - local_10, 1.0f);
        else if (var_1C.y < 0.0f)
            arg_0->vf_294(-1.0f + local_10, 1.0f);
        bp_44 = var_3C - local_24;
        if (bp_44 < 0.0872 && bp_44 > -0.0872) {
            arg_0->vf_298(-bp_44, 1.0f);
        } else if (bp_44 > 0.0f) {
            arg_0->vf_298(-1.0f, 1.0f);
            l40 = 0;
        } else {
            arg_0->vf_298(1.0f, 1.0f);
            l40 = 0;
        }
        if (arg_0->unk_450.sub_14C140() > flt_4275C4 || arg_0->vf_254() > arg_8) {
            RwInt32 var_50 = 0x3440080; // not an address: line test flags
            RwInt32 var_54 = arg_0->unk_2C & 7;

            if (arg_0->sub_D2FC0(&var_C, &l38, arg_4, 0, 0, var_50, 1, 0, 0x20000, 0, var_54) != 0) // not an address: a flag
                l40 = 0;
        }
        RwInt32 var_4C = 0x3440080; // not an address: line test flags
        RwInt32 var_48 = arg_0->unk_2C & 7;

        if (arg_0->sub_D2FC0(&var_C, &l38, arg_4, 0, 0, var_4C, 1, 0, 0x20000, 0, var_48) != 0) // not an address: a flag
            l40 = 0;
        if (local_20 == 0)
            local_28 = 0;
        if (l40 != 0)
            arg_0->vf_2A8(0, 0, 0);
        if (local_28 != 0)
            arg_0->vf_2A8(1, 0, 0);
    }
    sub_1BEF0(arg_0, arg_4, &l38, 0);
    if (sub_1BD50(arg_0, &l38, &var_1C, &local_10) != 0 && local_10 > 0.3301f && local_20 != 0)
        arg_0->vf_2A8(2, &l38, 0);
    return 1;
}
// match: sub_1C880 @ 0x0001C880
// sp-match: sub_1C880 @ 0x000157A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_1C880(type_3DC048 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
#ifndef CODFH_SP
    RwV3d lC8;
    RwInt32 local_BC;
    RwV3d varB8;
    RwV3d var_AC;
#endif
    RwV3d var_A0;
    RwV3d var_94;
    RwReal loc28;
    RwInt32 slot_24;
    RwInt32 slot_1C;
    RwV3d var_18;
    RwV3d var_C;
    RwInt32 v20 = 0;
    type_154C0_1048 ebp_88;

    loc28 = arg_0->vf_254();
    if (arg_8 != 0) {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares its slot with varB8's (frame 0x98, SP 0x157A0)
        RwV3d var_AC;

#endif
        RwV3dSub(&var_AC, arg_0->sub_CD550(), arg_4->sub_CD550());
        RwV3dNormalize(&var_AC, &var_AC);
        for (slot_1C = 0; slot_1C < 3; slot_1C++) {
            slot_24 = 0;
            switch (slot_1C) {
            case 0:
                var_A0 = *arg_0->sub_CD550();
                RwV3dScale(&var_18, &var_AC, loc28 * 2.0f);
                break;
            case 1:
                var_A0 = *arg_0->sub_CD550();
                RwV3dScale(&var_18, &var_AC, loc28);
                break;
            case 2:
                var_A0 = *arg_0->sub_CD550();
                RwV3dScale(&var_18, &var_AC, loc28 * 0.5f);
                break;
            }
            RwV3dAdd(&var_94, &var_A0, &var_18);
            var_94.y = arg_0->sub_CD550()->y;
            ebp_88.unk_04 = var_94;
            ebp_88.unk_10 = 1000.0f;
            ebp_88.unk_00 = 0;
            ebp_88.unk_18 = sub_F7E80(8);
            ebp_88.unk_1C = 0;
            sub_F8970(&ebp_88, 1, 0);
            if (ebp_88.unk_34 != 0) {
                var_94 = ebp_88.unk_34->unk_10;
                v20 = 1;
                break;
            }
        }
    } else {
#ifdef CODFH_SP // shape: block-scoped (frame 0x98, SP 0x157A0)
        RwV3d varB8;

#endif
        RwV3dSub(&varB8, arg_4->sub_CD550(), arg_0->sub_CD550());
        RwV3dNormalize(&varB8, &varB8);
        var_C.x = var_C.y = var_C.z = 0.0f;
        for (slot_1C = 0; slot_1C < 5; slot_1C++) {
            slot_24 = 0;
            switch (slot_1C) {
            case 0:
                var_A0 = *arg_4->sub_CD550();
                RwV3dScale(&var_18, &varB8, loc28 * 2.0f);
                break;
            case 1:
                var_A0 = *arg_4->sub_CD550();
                var_C.x = varB8.z;
                var_C.z = -varB8.x;
                RwV3dScale(&var_18, &var_C, loc28 * 2.0f);
                break;
            case 2:
                var_A0 = *arg_4->sub_CD550();
                var_C.x = -varB8.z;
                var_C.z = varB8.x;
                RwV3dScale(&var_18, &var_C, loc28 * 2.0f);
                break;
            case 3:
                var_A0 = *arg_0->sub_CD550();
                var_C.x = varB8.z;
                var_C.z = -varB8.x;
                RwV3dScale(&var_18, &var_C, loc28 * 1.5f);
                break;
            case 4:
                var_A0 = *arg_0->sub_CD550();
                var_C.x = -varB8.z;
                var_C.z = varB8.x;
                RwV3dScale(&var_18, &var_C, loc28 * 1.5f);
                break;
            }
            RwV3dAdd(&var_94, &var_A0, &var_18);
            var_94.y = arg_0->sub_CD550()->y;
            RwV3dAdd(&var_94, &var_A0, &var_18);
            var_94.y = arg_0->sub_CD550()->y;
            ebp_88.unk_04 = var_94;
            ebp_88.unk_10 = 1000.0f;
            ebp_88.unk_00 = 0;
            ebp_88.unk_18 = sub_F7E80(8);
            ebp_88.unk_1C = 0;
            sub_F8970(&ebp_88, 1, 0);
            if (ebp_88.unk_34 != 0) {
                var_94 = ebp_88.unk_34->unk_10;
                v20 = 1;
                break;
            }
        }
    }
    if (v20 != 0) {
#ifdef CODFH_SP // shape: the point as four reals, stored with its 0 (SP 0x15B45: the 0 stored after the point)
        RwReal lC8[4];

        lC8[0] = var_94.x;
        lC8[1] = var_94.y;
        lC8[2] = var_94.z;
        lC8[3] = 0.0f;
        sub_6B5F0("SetTaskCommand_GoToPoint", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)lC8, 4, true, false);
#else
        lC8 = var_94;
        local_BC = 0;
        sub_6B5F0("SetTaskCommand_GoToPoint", (type_67620 *)(arg_0->vf_098()), 0, 0, (RwInt32 *)(&lC8), 4, true, false);
#endif
    }
    return v20;
}
// match: sub_1CFE0 @ 0x0001CFE0
// sp-match: sub_1CFE0 @ 0x00015B90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1CFE0(RwV3d arg_0, RwReal arg_C)
{
    type_3DC048 *var_4;
    RwReal loc8;
    RwV3d local_14;
    RwV3d local_20;
    type_3D3548 *l24;

    if (arg_0.x == 0.0f && arg_0.y == 0.0f && arg_0.z == 0.0f) {
        sub_6B5F0("MatchedOrientation", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        return;
    }
    var_4 = unk_568->vf_014();
    if (((unk_49C >> 7) & 1) != 0 || ((unk_49C >> 8) & 1) != 0) {
        l24 = unk_580.sub_D4910();
        arg_0.x = l24->sub_CD550()->x - var_4->sub_CD550()->x;
        arg_0.y = l24->sub_CD550()->y - var_4->sub_CD550()->y;
        arg_0.z = l24->sub_CD550()->z - var_4->sub_CD550()->z;
    }
    arg_0.y = 0.0f;
    if (arg_0.x == 0.0f && arg_0.z == 0.0f)
        return;
    RwV3dNormalize(&arg_0, &arg_0);
    local_20 = *var_4->sub_CD5A0();
    if (local_20.y == 1.0f)
        return;
    local_20.y = 0.0f;
    RwV3dNormalize(&local_20, &local_20);
    RwV3dCrossProduct(&local_14, &local_20, &arg_0);
    loc8 = RwV3dDotProduct(&local_20, &arg_0);
    if (loc8 < 0.95f) {
        loc8 = 0.0f;
    } else if (loc8 < 0.995) {
        loc8 = (loc8 - 0.95f) * 20.0f;
    } else if (loc8 < 0.9998f) {
        loc8 = 0.9f;
    } else {
        sub_6B5F0("MatchedOrientation", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        loc8 = 1.0f;
    }
    if (local_14.y > 0.0f)
        var_4->vf_28C(1.0f - loc8);
    else if (local_14.y < 0.0f)
        var_4->vf_28C(-1.0f + loc8);
}
// match: sub_1D2C0 @ 0x0001D2C0
// sp-match: sub_1D2C0 @ 0x0001C240
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1D2C0(RwReal arg_0)
{
    type_3DC048 *l4;
    type_3D3548 *var8;
    RwReal lC;
    RwV3d var_18;

    l4 = unk_568->vf_014();
    var8 = unk_1374.sub_D4910();
    if (((unk_49C >> 17) & 1) != 0 && var8 != 0 && sub_18DF0(var8, 1) != 0) {
        RwV3dSub(&var_18, var8->sub_CD550(), l4->sub_CD550());
        lC = RwV3dLength(&var_18);
        if (unk_544 == 2 && l4->vf_14C() < lC)
            sub_1C4F0(l4, var8, lC, 0);
    } else {
        l4->vf_294(0.0f, 1.0f);
        if (l4->unk_2870 > 0.0f) {
            if (l4->unk_2870 < 5.0f)
                l4->vf_298(l4->unk_2870 / -5.0f, 1.0f);
            else
                l4->vf_298(-1.0f, 1.0f);
        } else if (l4->unk_2870 > -5.0f) {
            l4->vf_298(l4->unk_2870 / -5.0f, 1.0f);
        } else {
            l4->vf_298(1.0f, 1.0f);
        }
    }
    if (unk_4A8 < 0.0f) {
        RwInt32 var_1C;

        if (unk_4AC != 0)
            unk_4AC = 0;
        else
            unk_4AC = RpRandom() % 3 - 1;
        unk_4A8 = 30.0f;
        var_1C = 0;
        sub_6B5F0("AttackPauseFinished", (type_67620 *)(l4->vf_098()), 0, 0, &var_1C, 1, true, false);
    } else {
        unk_4A8 -= arg_0;
    }
}
// match: sub_1D560 @ 0x0001D560
// sp-match: sub_1D560 @ 0x0001C450
void AIData::sub_1D560(RwReal arg_0)
{
    sub_1D2C0(arg_0);
}
// match: sub_1D580 @ 0x0001D580
// sp-match: sub_1D580 @ 0x00015E20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1D580(RwReal arg_0)
{
    type_3DC048 *var_4;

    var_4 = unk_568->vf_014();
    if (unk_4A8 < 0.0f) {
        RwInt32 local_8;
        local_8 = var_4->vf_25C();
        sub_6B5F0("LookOutEntityEmerged", (type_67620 *)(var_4->vf_098()), 0, 0, &local_8, 1, true, false);
        unk_4A8 = 60.0f;
    } else {
        unk_4A8 -= arg_0;
    }
}
// match: sub_1D620 @ 0x0001D620
// sp-match: sub_1D620 @ 0x00019F30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1D620(RwReal arg_0)
{
    type_3D3548 *stk_4C;
    RwReal loc48;
    RwReal var_44;
    RwV3d ebp_40;
    type_154C0_80 *v34;
    RwV3d v30;
    RwInt32 slot_24;
    RwReal v20;
    type_3D3548 *slot_1C;
    RwReal local_18;
    RwV3d local_14;
    RwReal lv_8;
    type_3DC048 *var_4;

    stk_4C = unk_1374.sub_D4910();
    v34 = sub_16ED0(stk_4C, 0);
    if (unk_8AC.unk_04 <= 0)
        return;
    slot_1C = unk_8AC.unk_50.sub_D4910();
    if (slot_1C == 0) {
        sub_6B5F0("AStar_LostFollowTarget", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        unk_8AC.unk_04 = 0;
        return;
    }
    unk_594 += arg_0;
    if (unk_594 > 60.0f) {
        unk_594 = 0.0f;
        if (v34 != 0 && (v34->unk_04 & 1) != 0) {
            RwReal var_60;
            RwV3d *stk_5C;
            RwV3d local_58;

            stk_5C = slot_1C->sub_CD550();
            local_58.x = stk_5C->x - unk_8AC.unk_20.x;
            local_58.y = stk_5C->y - unk_8AC.unk_20.y;
            local_58.z = stk_5C->z - unk_8AC.unk_20.z;
            var_60 = RwV3dLength(&local_58);
            if (var_60 > 1000.0f)
                sub_6B5F0("AStar_TargetMoved", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        }
    }
    var_4 = unk_568->vf_014();
    if (sub_1B710(arg_0, var_4, &local_14, &v20, &lv_8, 0) == 0)
        return;
    if (local_14.y > 0.0f)
        var_4->vf_28C(v20);
    else if (local_14.y < 0.0f)
        var_4->vf_28C(-1.0f * v20);
    var_4->vf_280(lv_8);
    if (lv_8 == 0.0f)
        var_4->vf_290(1);
    else
        var_4->vf_290(0);
    slot_24 = sub_2B740(&unk_8AC);
    if (unk_8AC.unk_32 != 0 || slot_24 > 0) {
        unk_8AC.unk_04 = 0;
        sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(var_4->vf_098()), 0, 0, 0, 0, true, false);
    } else if (unk_8AC.unk_31 != 0 && slot_24 < 0) {
        unk_8AC.unk_04 = 0;
        sub_6B5F0("AStar_ArrivedATCoverPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
    if (v34 != 0 && (v34->unk_04 & 1) != 0) {
        sub_1BEF0(var_4, stk_4C, &ebp_40, 0);
        RwV3dSub(&v30, &ebp_40, var_4->sub_CD550());
        loc48 = RwV3dLength(&v30);
    } else {
        ebp_40 = *var_4->sub_CD550();
        RwV3dScale(&v30, var_4->sub_CD5A0(), 1000.0f);
        RwV3dAdd(&ebp_40, &ebp_40, &v30);
        loc48 = 1000.0f;
    }
    if (sub_1BAA0(var_4, &ebp_40, loc48, &local_14, &v20, &var_44, &local_18, 0) != 0) {
        RwReal stk_64;

        if (var_4->unk_28DC != -1) {
            if (local_14.y > 0.0f)
                var_4->vf_294(1.0f - v20, 1.0f);
            else if (local_14.y < 0.0f)
                var_4->vf_294(-1.0f + v20, 1.0f);
        }
        if (v34 == 0 || (v34->unk_04 & 1) == 0)
            var_44 = 0.0f;
        stk_64 = var_44 - local_18;
        if (stk_64 < 0.0872 && stk_64 > -0.0872)
            var_4->vf_298(-stk_64, 1.0f);
        else if (stk_64 > 0.0f)
            var_4->vf_298(-1.0f, 1.0f);
        else
            var_4->vf_298(1.0f, 1.0f);
    }
}
// match: sub_1DB60 @ 0x0001DB60
// sp-match: sub_1DB60 @ 0x0001C460
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1DB60(RwReal arg_0)
{
    type_3D3548 *local_20;
    RwInt32 var_1C;
    RwReal local_18;
    RwV3d local_14;
    RwReal lv_8;
    type_3DC048 *var_4;

    local_20 = unk_1374.sub_D4910();
    if (unk_8AC.unk_04 <= 0)
        return;
    var_4 = unk_568->vf_014();
    if (unk_8AC.unk_32 != 0 && ((unk_49C >> 16) & 1) == 0 && unk_8AC.unk_64.unk_2C > 1) {
        RwV3d l38;
        type_F8350 *lcl_2C;
        type_4C00E8 *local_28;
        RwInt32 local_24;

        local_24 = unk_8AC.unk_B0[unk_8AC.unk_64.unk_2C - 2];
        local_28 = &unk_4C00E8;
        lcl_2C = local_28->unk_2C[local_24];
        RwV3dSub(&l38, &unk_8AC.unk_38, &lcl_2C->unk_10);
        RwV3dNormalize(&l38, &l38);
        local_18 = RwV3dDotProduct(var_4->sub_CD5A0(), &l38);
        if (local_18 < 0.0f)
            unk_49C |= 0x10000;
    }
    if (sub_1B710(arg_0, var_4, &local_14, &local_18, &lv_8, 0) == 0)
        return;
    if (unk_4B0 != 0)
        lv_8 = 0.0f;
    if (local_14.y > 0.0f)
        var_4->vf_28C(local_18);
    else if (local_14.y < 0.0f)
        var_4->vf_28C(-1.0f * local_18);
    var_4->vf_280(lv_8);
    if (lv_8 == 0.0f)
        var_4->vf_290(1);
    else
        var_4->vf_290(0);
    var_1C = sub_2B740(&unk_8AC);
    if (var_1C > 0) {
        unk_8AC.unk_04 = 0;
        sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(var_4->vf_098()), 0, 0, 0, 0, true, false);
    } else if (unk_8AC.unk_31 != 0 && var_1C < 0) {
        unk_8AC.unk_04 = 0;
        sub_6B5F0("AStar_ArrivedATCoverPoint", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
    if (((unk_49C >> 17) & 1) != 0 && local_20 != 0 && sub_18DF0(local_20, 1) != 0) {
        RwV3d v48;
        RwReal var_3C;

        if (((unk_49C >> 20) & 1) == 0 && var_4->vf_2A4(0) != 0) {
            var_4->vf_28C(0.0f);
            var_4->vf_280(0.0f);
            var_4->vf_290(1);
        }
        RwV3dSub(&v48, local_20->sub_CD550(), var_4->sub_CD550());
        var_3C = RwV3dLength(&v48);
        sub_1C4F0(var_4, local_20, var_3C, 0);
    } else {
        sub_1BFB0(unk_568->vf_014());
    }
}
// match: sub_1DF60 @ 0x0001DF60
// sp-match: sub_1DF60 @ 0x0001A380
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1DF60(RwReal arg_0)
{
    type_3DC048 *l4;
    RwReal var_8;
    RwV3d bp_14;
    RwV3d var20;
    RwReal slot_24;
    RwV3d v30;
    RwReal v34;

    l4 = unk_568->vf_014();
    RwV3dSub(&var20, &unk_5B0, l4->sub_CD550());
    var20.y = 0.0f;
    if (unk_4A8 <= 0.0f) {
        RwV3dNormalize(&v30, &var20);
        slot_24 = RwV3dDotProduct(l4->sub_CD5A0(), &v30);
        if (slot_24 < 0.0f)
            unk_49C |= 0x10000;
        unk_4A8 = 1000000.0f;
    }
    if (sub_1B710(arg_0, l4, &bp_14, &slot_24, &var_8, &unk_5B0) == 0)
        return;
    if (unk_4B0 != 0)
        var_8 = 0.0f;
    if (bp_14.y > 0.0f)
        l4->vf_28C(slot_24);
    else if (bp_14.y < 0.0f)
        l4->vf_28C(-1.0f * slot_24);
    if (fabs(slot_24) < 0.5f)
        l4->vf_280(var_8 * 0.5f);
    else
        l4->vf_280(0.0f);
    if (var_8 == 0.0f)
        l4->vf_290(1);
    else
        l4->vf_290(0);
    v34 = RwV3dLength(&var20);
    if (v34 < unk_78)
        sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(l4->vf_098()), 0, 0, 0, 0, true, false);
    else
        sub_1BFB0(unk_568->vf_014());
}
// match: sub_1E210 @ 0x0001E210
// sp-match: sub_1E210 @ 0x0001C780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1E210(RwReal arg_0)
{
    type_3D3548 *var_1C;
    RwReal local_18;
    RwV3d local_14;
    RwReal lv_8;
    type_3DC048 *var_4;

    var_1C = unk_1374.sub_D4910();
    var_4 = unk_568->vf_014();
    sub_2DAA0(arg_0, unk_D88, 0);
    if (sub_1B710(arg_0, var_4, &local_14, &local_18, &lv_8, 0) == 0)
        return;
    if (local_14.y > 0.0f)
        var_4->vf_28C(local_18);
    else if (local_14.y < 0.0f)
        var_4->vf_28C(-1.0f * local_18);
    var_4->vf_280(lv_8);
    if (lv_8 == 0.0f)
        var_4->vf_290(1);
    else
        var_4->vf_290(0);
    if (((unk_49C >> 17) & 1) != 0 && var_1C != 0 && sub_18DF0(var_1C, 1) != 0) {
        RwV3d var_30;
        RwReal local_24;
        RwInt32 local_20;

        local_20 = 0;
        if (var_1C->vf_008() != 0 || var_1C->vf_024() != 0
                || (var_1C->vf_00C() != 0 && var_1C->vf_00C()->vf_200() == 0))
            local_20 = 1;
        if (((unk_49C >> 20) & 1) == 0 && local_20 == 0
                && (((unk_49C >> 28) & 1) != 0 || var_4->vf_2A4(0) != 0)) {
            var_4->vf_28C(0.0f);
            var_4->vf_280(0.0f);
            var_4->vf_290(1);
        }
        RwV3dSub(&var_30, var_1C->sub_CD550(), var_4->sub_CD550());
        local_24 = RwV3dLength(&var_30);
        sub_1C4F0(var_4, var_1C, local_24, 0);
    } else {
        sub_1BFB0(unk_568->vf_014());
    }
    if (unk_4B0 != 0) {
        var_4->vf_280(0.0f);
        var_4->vf_290(1);
    } else if (lv_8 != 0.0f && unk_580.sub_D4910() != 0) {
        sub_1A630(var_4, lv_8);
    }
}
// match: sub_1E530 @ 0x0001E530
// sp-match: sub_1E530 @ 0x0001A5A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1E530(RwReal arg_0)
{
    RwV3d stk_4C;
    RwV3d lv_40;
    RwInt32 v34;
    type_3DC048 *v30;
    RwV3d var_2C;
    RwReal v20;
    RwReal slot_1C;
    type_3D3548 *local_18;
    RwReal local_14;
    RwV3d local_10;
    RwReal var_4;

    local_18 = unk_1374.sub_D4910();
    if (local_18 != 0) {
        v30 = unk_568->vf_014();
        RwV3dSub(&var_2C, local_18->sub_CD550(), v30->sub_CD550());
        v20 = RwV3dLength(&var_2C);
        if (v30->vf_258() > v20 && ((unk_49C >> 16) & 1) == 0) {
            unk_8AC.unk_04 = 0;
            unk_4A4 = 0;
        } else {
            RwV3dSub(&var_2C, local_18->sub_CD550(), &unk_1380);
            slot_1C = RwV3dLength(&var_2C);
            if (slot_1C > 1500.0f) {
                unk_8AC.unk_04 = 0;
                unk_4A4 = 0;
            }
        }
        if (unk_8AC.unk_04 > 0) {
            if (v30->vf_2A4(0) == 0 || v30->vf_254() > v20) {
                if (sub_1B710(arg_0, v30, &local_10, &local_14, &var_4, 0) != 0) {
                    if (unk_4B0 != 0) {
                        var_4 = 0.0f;
                        RwV3dNormalize(&stk_4C, v30->vf_0C8());
                        RwV3dSub(&lv_40, &unk_8AC.unk_20, v30->sub_CD550());
                        RwV3dNormalize(&lv_40, &lv_40);
                        if (RwV3dDotProduct(&stk_4C, &lv_40) < 0.0f) {
                            unk_8AC.unk_04 = 0;
                            unk_4A4 = 0;
                        }
                    }
                    if (local_10.y > 0.0f)
                        v30->vf_28C(local_14);
                    else if (local_10.y < 0.0f)
                        v30->vf_28C(-1.0f * local_14);
                    v30->vf_280(var_4);
                    if (var_4 == 0.0f)
                        v30->vf_290(1);
                    else
                        v30->vf_290(0);
                    v34 = sub_2B740(&unk_8AC);
                    if (v34 > 0) {
                        unk_8AC.unk_04 = 0;
                        unk_4A4 = 0;
                    }
                }
            }
        } else if (unk_4A4 == 0 || unk_4A8 < 0.0f) {
            if (v30->vf_254() > v20 && (unk_4A4 = sub_1C880(v30, local_18, 1)) != 0) {
                unk_49C |= 0x10000;
            } else {
                unk_4A4 = sub_1C880(v30, local_18, 0);
                if (unk_4A4 != 0)
                    unk_49C &= ~0x10000;
            }
            unk_1380 = *local_18->sub_CD550();
            unk_4A8 = 300.0f;
        } else {
            unk_4A8 -= arg_0;
            if (v30->vf_2A4(0) == 0
                    && sub_1B710(arg_0, v30, &local_10, &local_14, &var_4, local_18->sub_CD550()) != 0) {
                if (local_10.y > 0.0f)
                    v30->vf_28C(local_14);
                else if (local_10.y < 0.0f)
                    v30->vf_28C(-1.0f * local_14);
            }
        }
        sub_1C4F0(v30, local_18, v20, 0);
    }
}
// match: sub_1EA70 @ 0x0001EA70
// sp-match: sub_1EA70 @ 0x0001A9D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1EA70(RwReal arg_0)
{
    type_3DC048 *var_30;
    RwV3d var_2C;
    RwReal v20;
    RwReal slot_1C;
    type_3D3548 *local_18;
    RwReal local_14;
    RwV3d local_10;
    RwReal var_4;

    local_18 = unk_1374.sub_D4910();
    if (local_18 != 0) {
        var_30 = unk_568->vf_014();
        RwV3dSub(&var_2C, local_18->sub_CD550(), var_30->sub_CD550());
        v20 = RwV3dLength(&var_2C);
        RwV3dSub(&var_2C, local_18->sub_CD550(), &unk_1380);
        slot_1C = RwV3dLength(&var_2C);
        if (slot_1C > 1500.0f)
            unk_4A4 = 0;
        if (unk_4A4 == 0 || unk_4A8 < 0.0f) {
            unk_4A4 = sub_1C880(var_30, local_18, 0);
            if (unk_4A4 != 0)
                unk_49C &= ~0x10000;
            unk_1380 = *local_18->sub_CD550();
            unk_4A8 = 300.0f;
        } else {
            unk_4A8 -= arg_0;
            if (var_30->vf_2A4(0) == 0
                    && sub_1B710(arg_0, var_30, &local_10, &local_14, &var_4, local_18->sub_CD550()) != 0) {
                if (local_10.y > 0.0f)
                    var_30->vf_28C(local_14);
                else if (local_10.y < 0.0f)
                    var_30->vf_28C(-1.0f * local_14);
            }
        }
        sub_1C4F0(var_30, local_18, v20, 0);
    }
}
// match: ?sub_1ECF0@AIData@@QAEXM@Z @ 0x0001ECF0
// sp-match: ?sub_1ECF0@AIData@@QAEXM@Z @ 0x0001ABE0
void AIData::sub_1ECF0(RwReal arg_0)
{
    type_3D3548 *var_8;
    type_3DC048 *var_C;
    RwV3d var_1C;
    RwReal var_28;
    RwInt32 var_2C;
    RwReal var_30;
    RwReal var_34;
    RwV3d var_40;
    RwInt32 var_44;
    RwReal var_54;
    RwMatrix var_D0;
    RwV3d var_DC;

    var_8 = unk_1374.sub_D4910();
    if (var_8)
    {
        var_C = (type_3DC048 *)unk_568->vf_014();
        RwV3dSubMacro(&var_1C, var_8->sub_CD550(), var_C->sub_CD550());
        var_28 = RwV3dLength((RwV3d *)&var_1C);
        if (!var_C->vf_2A4(0) || var_C->vf_254() > var_28)
        {
            var_2C = 0;
            if (unk_8AC.unk_04 > 0)
            {
                var_2C = sub_1B710(arg_0, var_C, &var_40, &var_34, &var_30, 0);
                var_44 = sub_2B740(&unk_8AC);
                if (var_44)
                {
                    unk_8AC.unk_04 = 0;
                }
            }
            else
            {
                RwV3dSubMacro(&var_1C, &unk_F60->unk_10, var_C->sub_CD550());
                var_54 = RwV3dLength((RwV3d *)&var_1C);
                if (var_54 > 200.0f)
                {
                    var_2C = sub_1B710(arg_0, var_C, &var_40, &var_34, &var_30, &unk_F60->unk_10);
                }
                else if (unk_528)
                {
                    RtQuatConvertToMatrix(&unk_F60->unk_1C, &var_D0);
                    RwV3dScaleMacro(&var_DC, &var_D0.at, 1000.0f);
                    RwV3dAddMacro(&var_DC, &unk_F60->unk_10, &var_DC);
                    var_2C = sub_1B710(arg_0, var_C, &var_40, &var_34, &var_30, &var_DC);
                    var_30 = 0.0f;
                }
            }
            if (var_2C)
            {
                if (unk_4B0)
                {
                    var_30 = 0.0f;
                }
                if (var_40.y > 0.0f)
                {
                    var_C->vf_28C(var_34);
                }
                else if (var_40.y < 0.0f)
                {
                    var_C->vf_28C(-1.0f * var_34);
                }
                var_C->vf_280(var_30);
                if (var_30 == 0.0f)
                {
                    var_C->vf_290(1);
                }
                else
                {
                    var_C->vf_290(0);
                }
            }
        }
        sub_1C4F0(var_C, var_8, var_28, 0);
    }
}
// match: sub_1F2A0 @ 0x0001F2A0
// sp-match: sub_1F2A0 @ 0x00015EA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1F2A0(RwReal arg_0)
{
    type_3DC048 *var_4;
    type_3D3548 *local_8;

    var_4 = unk_568->vf_014();
    local_8 = unk_1374.sub_D4910();
    if (local_8 != 0) {
        var_4->vf_28C(0.0f);
        var_4->vf_280(0.0f);
        var_4->vf_290(1);
        if (sub_1C4F0(var_4, local_8, 1000000.0f, 1) == 0) {
            var_4->vf_294(0.0f, 1.0f);
            var_4->vf_298(0.0f, 1.0f);
        }
    } else {
        var_4->vf_294(0.0f, 1.0f);
        var_4->vf_298(0.0f, 1.0f);
    }
}
// match: sub_1F390 @ 0x0001F390
// sp-match: sub_1F390 @ 0x0001AF30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1F390(RwReal arg_0)
{
    RwReal var_4;
    RwReal loc8;
    RwV3d local_14;
    type_3D3548 *var18;
    type_3DC048 *var_1C;

    var18 = unk_1374.sub_D4910();
    if (var18 != 0) {
        var_1C = unk_568->vf_014();
        sub_1B710(arg_0, var_1C, &local_14, &loc8, &var_4, var18->sub_CD550());
        if (local_14.y > 0.0f)
            var_1C->vf_28C(1.0f - loc8);
        else if (local_14.y < 0.0f)
            var_1C->vf_28C(-1.0f + loc8);
        var_1C->vf_280(var_4);
    }
}
// match: sub_1F470 @ 0x0001F470
// sp-match: sub_1F470 @ 0x00015F30
void AIData::sub_1F470(RwReal arg_0)
{
    type_3DC048 *var_4;

    if (unk_498 == 0)
        return;
    var_4 = unk_568->vf_014();
    if (var_4->vf_2A8(unk_494, 0, 0) != 0)
        unk_498 -= 1;
    if (unk_498 == 0)
        sub_6B5F0("FireWeaponCompleted", (type_67620 *)(var_4->vf_098()), 0, 0, 0, 0, true, false);
}
// match: sub_1F520 @ 0x0001F520
// sp-match: sub_1F520 @ 0x00015FA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1F520(RwReal arg_0)
{
    type_3DBC78 *l4;
    RwReal var8;
    type_14D180 *lC;
    RwV3d var_18;
    type_3D3548 *var_1C;

    l4 = static_cast<type_3DBC78 *>(unk_12F4.unk_08.sub_D4910());
    if (l4 != 0) {
        lC = l4->sub_155340(&unk_12F4);
        unk_D70 = lC->unk_14;
        unk_4F4 = lC->unk_14;
        if (((unk_49C >> 23) & 1) != 0)
            sub_2D3A0();
        else if (((unk_49C >> 2) & 1) != 0)
            sub_2CE90(1, 140.0f, 170.0f);
        if (((unk_568->unk_2C >> 5) & 1) != 0 && ((unk_49C >> 15) & 1) != 0) {
            sub_2C220(arg_0);
            var_1C = unk_1374.sub_D4910();
            if (var_1C != 0) {
                sub_17140(var_1C->vf_0CC());
                sub_19F90(var_1C, arg_0);
            }
        } else if (unk_598 == 0 && unk_59C == 0) {
            sub_17140(&unk_D70);
            sub_2E520(&unk_D70, arg_0);
        }
        RwV3dSub(&var_18, &lC->unk_14, unk_568->sub_CD550());
        var8 = RwV3dLength(&var_18);
        if (var8 < 125.0f)
            sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        if (((lC->unk_00 >> 1) & 1) == 0)
            sub_6B5F0("VehicleCoverPointInvalid", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    } else {
        sub_6B5F0("VehicleCoverPointLost", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
}
// match: sub_1F7C0 @ 0x0001F7C0
// sp-match: sub_1F7C0 @ 0x000161A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1F7C0(RwReal arg_0)
{
    type_3DBC78 *l4;
    type_14D180 *var8;
    RwInt32 lC;
    RwV3d var_18;
    RwV3d *var_1C;
    RwReal l20;

    unk_594 += arg_0;
    if (unk_8AC.unk_04 > 0) {
        l4 = static_cast<type_3DBC78 *>(unk_12F4.unk_08.sub_D4910());
        if (l4 != 0) {
            var8 = l4->sub_155340(&unk_12F4);
            if (((var8->unk_00 >> 1) & 1) != 0) {
                if (unk_594 > 15.0f) {
                    unk_594 = 0.0f;
                    var_1C = &var8->unk_14;
                    var_18.x = var_1C->x - unk_8AC.unk_20.x;
                    var_18.y = var_1C->y - unk_8AC.unk_20.y;
                    var_18.z = var_1C->z - unk_8AC.unk_20.z;
                    l20 = RwV3dLength(&var_18);
                    if (l20 > 500.0f)
                        sub_6B5F0("VehicleCoverPointMoved", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                }
                lC = sub_2B740(&unk_8AC);
                if (lC > 0)
                    sub_6B5F0("AStar_ArrivedATDestination", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                if (((unk_49C >> 23) & 1) != 0)
                    sub_2D3A0();
                else if (((unk_49C >> 2) & 1) != 0)
                    sub_2CE90(1, 140.0f, 170.0f);
            } else {
                sub_6B5F0("VehicleCoverPointInvalid", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
                unk_8AC.unk_04 = 0;
            }
        } else {
            sub_6B5F0("VehicleCoverPointLost", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
            unk_8AC.unk_04 = 0;
        }
    }
}
// match: sub_1FA00 @ 0x0001FA00
// sp-match: sub_1FA00 @ 0x00016350
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_1FA00(RwReal arg_0)
{
    type_3DBC78 *var_4;
    RwV3d v10;
    RwV3d *local_14;
    RwV3d *var18;
    RwReal var_1C;
    type_14D180 *l20;

    if (unk_1374.sub_D4910() != 0)
        sub_19F90(unk_1374.sub_D4910(), arg_0);
    var_4 = static_cast<type_3DBC78 *>(unk_12F4.unk_08.sub_D4910());
    if (var_4 != 0) {
        l20 = var_4->sub_155340(&unk_12F4);
        if (((l20->unk_00 >> 1) & 1) == 0)
            sub_6B5F0("VehicleCoverPointInvalid", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        var18 = &l20->unk_14;
        local_14 = unk_568->sub_CD550();
        RwV3dSub(&v10, var18, local_14);
        var_1C = RwV3dLength(&v10);
        if (var_1C > 200.0f)
            sub_6B5F0("VehicleCoverPointMoved", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    } else {
        sub_6B5F0("VehicleCoverPointLost", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    }
}
// match: sub_1FB80 @ 0x0001FB80
// sp-match: sub_1FB80 @ 0x00016470
void AIData::sub_1FB80(RwReal arg_0)
{
    if (unk_F60 != 0 && sub_25DD0(unk_F60, 0) == 0)
        sub_6B5F0("DefendAreaCoverPointInvalid", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
    if (unk_578 == 0x2A && unk_13E8.sub_D4910() == 0)
        sub_6B5F0("AStar_LostFollowTarget", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
}
// match: sub_1FC40 @ 0x0001FC40
// sp-match: sub_1FC40 @ 0x000164F0
void AIData::sub_1FC40()
{
    sub_31DC0(unk_568->vf_098());
}
// match: sub_1FC70 @ 0x0001FC70
// sp-match: sub_1FC70 @ 0x00016510
void AIData::sub_1FC70()
{
    unk_50 = 0;
    unk_4C = 0;
    if (unk_568 != 0)
        sub_31E00(unk_568->vf_098());
}
#ifdef CODFH_SP
// sp-match: ?sp_sub_16540@AIData@@QAEHPAUtype_3D3548@@PAURwV3d@@@Z @ 0x00016540
RwInt32 AIData::sp_sub_16540(type_3D3548 *arg_0, RwV3d *arg_4)
{
    RwInt32 i;

    for (i = 0; i < unk_50; i++)
    {
        RwV3d *p = &unk_04[i];
        RwV3d d1;
        RwV3d d2;

        RwV3dSub(&d1, p, unk_568->sub_CD550());
        RwV3dSub(&d2, p, arg_0->sub_CD550());
        if (unk_4C & (1 << i))
        {
            if (RwV3dDotProduct(&d2, &d1) > 0.0f)
                continue;
            if (RwV3dDotProduct(&d2, &unk_28[i]) < 0.0f)
                continue;
        }
        else
        {
            RwV3d e;

            e.x = unk_568->sub_CD550()->x - arg_0->sub_CD550()->x;
            e.y = unk_568->sub_CD550()->y - arg_0->sub_CD550()->y;
            e.z = unk_568->sub_CD550()->z - arg_0->sub_CD550()->z;
            if (RwV3dDotProduct(&e, &d2) < 0.0f)
                continue;
            if (RwV3dDotProduct(&d2, &d2) < RwV3dDotProduct(&d1, &d1))
                continue;
            if (RwV3dDotProduct(&d2, &unk_28[i]) > 0.0f)
                continue;
        }
        *arg_4 = *p;
        return 1;
    }
    return 0;
}
#endif


// match: sub_1FCC0 @ 0x0001FCC0
// sp-match: sub_1FCC0 @ 0x00016780
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_3D3548 *AIData::sub_1FCC0(RwInt32 arg_0, RwInt32 arg_4)
{
    RwReal var_4;
    type_3D3548 *v8;
    RwInt32 stk_C;
    type_3D3548 *var_10;

    v8 = 0;
    var_4 = 0.0f;
    for (stk_C = 0; stk_C < 0x20; stk_C++) {
        var_10 = unk_80[stk_C].unk_00.sub_D4910();
        if (var_10 != 0
                && ((((unk_80[stk_C].unk_04 >> 1) & 1) != 0 && unk_80[stk_C].unk_0C < var_4)
                    || v8 == 0)
                && arg_0 == 0
                && ((unk_80[stk_C].unk_00.sub_D4910()->unk_2C & 0x3FFFFF0) & 0x40080) == 0 // not an address: entity kind bits
                && (var_10->unk_2C & 7) != (unk_568->unk_2C & 7)
                && arg_4 == 0
                && ((var_10->unk_28 >> 9) & 1) == 0) {
            var_4 = unk_80[stk_C].unk_0C;
            v8 = unk_80[stk_C].unk_00.sub_D4910();
        }
    }
    return v8;
}
// match: sub_1FDF0 @ 0x0001FDF0
// sp-match: sub_1FDF0 @ 0x00016830
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal AIData::sub_1FDF0(type_3D3548 *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwV3d var_C;
    RwReal v10;
    RwV3d slot_1C;
    RwFrame *v20;
    RwMatrix *var24;

    v10 = 0.0f;
    var_C = *arg_0->vf_0C8();
    var_C.y = 0.0f;
    v10 = RwV3dLength(&var_C);
    if (v10 > 5.0f) {
        if ((arg_0->unk_2C & 0x40080) != 0) { // not an address: entity kind bits
            slot_1C = var_C;
        } else {
            v20 = arg_0->get_unk_340();
            var24 = RwFrameGetLTM(v20);
            sub_141320(&slot_1C, &var_C, var24);
        }
        if (arg_4 != 0)
            *arg_4 = slot_1C;
        if (arg_8 != 0)
            *arg_8 = var_C;
        return v10;
    }
    if (arg_4 != 0) {
        arg_4->x = 0.0f;
        arg_4->y = 0.0f;
        arg_4->z = 0.0f;
    }
    return 0.0f;
}
// match: sub_1FF10 @ 0x0001FF10
// match: __ehhandler$?sub_1FF10@AIData@@QAEHPAUtype_3DF8D8_04@@MMM@Z-8 @ 0x002FF500
// match: __ehhandler$?sub_1FF10@AIData@@QAEHPAUtype_3DF8D8_04@@MMM@Z @ 0x002FF508
// sp-match: sub_1FF10 @ 0x0001AFF0
RwInt32 AIData::sub_1FF10(type_3DF8D8_04 *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    type_3D3548 *local_10;
    RwInt32 stk_14;
    RwInt32 lcl_18;
    type_3DF8D8 *fp_1C;
    RwInt32 ebp_20;

    if (arg_C != 0.0f && arg_C < flt_4275B8)
        arg_C = flt_4275B8;
    if (arg_8 != 0.0f && arg_8 < flt_4275BC)
        arg_8 = flt_4275B8;
    ebp_20 = 0;
    local_10 = 0;
    fp_1C = sub_198800(arg_0);
    stk_14 = fp_1C->vf_008();
    lcl_18 = fp_1C != 0 && (stk_14 == 0x2E || stk_14 == 0x2D || stk_14 == 0x2C);
    if (lcl_18 != 0) {
        if (stk_14 == 0x2E || stk_14 == 0x2C) {
            type_3DFEEC *var_24;

            var_24 = static_cast<type_3DFEEC *>(fp_1C);
            if ((var_24->unk_10 & 2) != 0) {
                type_D48D0 var_28;

                var_28 = var_24->unk_24_id;
                local_10 = var_28.sub_D4910();
                if (local_10 != 0) {
                    RwV3d var_34;

                    sub_20AC0(&var_34, local_10);
                    if (sub_1FDF0(local_10, &unk_13C4, 0) != 0.0f)
                        RwV3dNormalize(&unk_13C4, &unk_13C4);
                    else
                        unk_13C4 = *local_10->sub_CD5A0();
                    unk_13A8 = var_34;
                    unk_13D0 = var_34;
                    unk_13C0.sub_D48D0(local_10);
                    unk_13A0.unk_00 = 0;
                    unk_13A0.unk_04 = 0;
                    ebp_20 = 1;
                }
            } else {
                RwV3d *var_38;

                var_38 = var_24->vf_010();
                if (var_38 != 0) {
                    RwV3d *var_3C;

                    var_3C = var_24->vf_00C();
                    unk_13A8 = *var_3C;
                    unk_13D0 = *var_3C;
                    unk_13C4 = *var_24->vf_010();
                    unk_13C0.sub_D48D0(0);
                    unk_13A0.unk_00 = arg_0->unk_00;
                    unk_13A0.unk_04 = arg_0->unk_04;
                    ebp_20 = 1;
                }
            }
        } else {
            type_3DF8D8 *var_40;
            RwV3d *var_44;

            var_40 = fp_1C;
            var_44 = var_40->vf_010();
            if (var_44 != 0) {
                RwV3d *var_48;

                var_48 = var_40->vf_00C();
                unk_13A8 = *var_48;
                unk_13D0 = *var_48;
                unk_13C4 = *var_40->vf_010();
                unk_13C0.sub_D48D0(0);
                unk_13A0.unk_00 = arg_0->unk_00;
                unk_13A0.unk_04 = arg_0->unk_04;
                ebp_20 = 1;
            }
        }
    }
    if (ebp_20 != 0) {
        unk_49C |= 0x2000;
        unk_13DC = 3;
        if (local_10 != 0) {
            RwReal var_4C;

            var_4C = local_10->unk_4C + 100.0f;
            if (arg_4 < var_4C)
                arg_4 += 100.0f;
        }
        unk_13B4 = arg_4;
        unk_13B8 = arg_8;
        unk_13BC = arg_C;
        unk_F68 = 2500.0f;
        unk_F70.z = 0.0f;
        unk_F70.y = 0.0f;
        unk_F70.x = 0.0f;
    }
    return ebp_20;
}
// match: sub_20370 @ 0x00020370
// sp-match: sub_20370 @ 0x00016920
void AIData::sub_20370(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    if (arg_C != 0.0f && arg_C < flt_4275B8)
        arg_C = flt_4275B8;
    if (arg_8 != 0.0f && arg_8 < flt_4275BC)
        arg_8 = flt_4275B8;
    unk_49C |= 0x2000;
    unk_13B4 = arg_4;
    unk_13B8 = arg_8;
    unk_13BC = arg_C;
    unk_13C4 = *unk_568->sub_CD5A0();
    unk_13D0 = *arg_0;
    unk_13DC = 3;
    unk_13A8 = *arg_0;
    unk_13A0.unk_00 = 0;
    unk_13A0.unk_04 = 0;
    unk_13C0.sub_D48D0(0);
    unk_F68 = 2500.0f;
    unk_F70.z = 0.0f;
    unk_F70.y = 0.0f;
    unk_F70.x = 0.0f;
}
// match: sub_204E0 @ 0x000204E0
// sp-match: sub_204E0 @ 0x00016A40
void AIData::sub_204E0()
{
    unk_49C &= ~0x2000;
    unk_13A0.unk_00 = 0;
    unk_13A0.unk_04 = 0;
    unk_13C0.sub_D48D0(0);
    unk_F68 = 2500.0f;
    unk_F70.z = 0.0f;
    unk_F70.y = 0.0f;
    unk_F70.x = 0.0f;
}
// match: sub_20570 @ 0x00020570
// sp-match: sub_20570 @ 0x00016A90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal AIData::sub_20570(RwV3d *arg_0)
{
    RwV3d *var_4;
    RwReal v8;
    RwV3d l14;

    v8 = 1.0e37f;
    if ((var_4 = &unk_13A8) != 0) {
        RwV3dSub(&l14, arg_0, var_4);
        v8 = RwV3dLength(&l14);
    }
    return v8;
}
// match: sub_205E0 @ 0x000205E0
// sp-match: sub_205E0 @ 0x0001B280
RwInt32 AIData::sub_205E0(RwV3d *arg_0, RwReal arg_4)
{
    RwInt32 var_4;

    if ((unk_13B8 != 0.0f || unk_13BC != 0.0f) != 0)
        var_4 = 1;
    else
        var_4 = 0;
    return sub_20670(arg_0, unk_13BC, unk_13B8, arg_4, var_4);
}
// match: sub_20670 @ 0x00020670
// sp-match: sub_20670 @ 0x00016AE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_20670(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwInt32 arg_10)
{
    RwReal var_4;
    RwReal loc8;
    RwV3d local_14;
    RwV3d *var18;
    RwReal var_1C;
    RwReal l20;

    RwV3dSub(&local_14, &unk_13A8, arg_0);
    if ((unk_13B8 != 0.0f || unk_13BC != 0.0f) != 0)
        local_14.y = 0.0f;
    loc8 = RwV3dDotProduct(&local_14, &local_14);
    var_4 = arg_C + unk_13B4;
    if (var_4 < 0.0f)
        var_4 = unk_13B4;
    if (arg_C != 0.0f && var_4 < 200.0f)
        var_4 = 200.0f;
    if (loc8 < var_4 * var_4) {
        if ((unk_13B8 != 0.0f || unk_13BC != 0.0f) == 0)
            return 1;
        if (arg_10 != 0) {
            var18 = &unk_13A8;
            l20 = arg_8 + var18->y;
            var_1C = var18->y - arg_4;
            if (arg_0->y < l20 && arg_0->y > var_1C)
                return 1;
        } else {
            return 1;
        }
    }
    return 0;
}
// match: sub_20830 @ 0x00020830
// sp-match: sub_20830 @ 0x00016C20
RwInt32 AIData::sub_20830(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C)
{
    RwInt32 var_4;
    RwV3d var_10;

    var_4 = 0;
    if (arg_C == 0.0f)
        arg_C = dword_4275C8;
    RwV3dSub(&var_10, arg_0, arg_8);
    var_10.y = 0.0f;
    if (RwV3dDotProduct(&var_10, &var_10) > arg_C * arg_C) {
        RwV3dNormalize(arg_4, &var_10);
        RwV3dAssign(arg_8, arg_0);
        var_4 = 1;
    }
    return var_4;
}
// match: sub_208F0 @ 0x000208F0
// sp-match: sub_208F0 @ 0x0001B2E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_208F0()
{
    type_3D3548 *var_4;
    type_3D3548 *loc8;
    RwV3d local_14;
    RwInt32 var18;
    RwInt32 var_1C;
    type_3DF8D8 *l20;
    type_3DFED8 *fp_24;
    RwV3d *fp_28;

    if ((unk_49C & 0x2000) != 0) {
        var_4 = unk_13C0.sub_D4910();
        if (var_4 != 0) {
            sub_20AC0(&local_14, var_4);
            unk_13A8 = local_14;
            loc8 = unk_13E4.sub_D4910();
            if (loc8 == var_4) {
                unk_13C4 = *loc8->sub_D42B0();
                unk_13D0 = *loc8->sub_D4290();
            } else {
                sub_20830(&local_14, &unk_13C4, &unk_13D0, 0.0f);
            }
        } else if (unk_13A0.unk_00 != 0 && unk_13A0.unk_04 != 0) {
            l20 = sub_198800(&unk_13A0);
            var18 = l20->vf_008();
            var_1C = l20 != 0 && (var18 == 0x2E || var18 == 0x2D || var18 == 0x2C);
            if (var_1C != 0) {
                fp_24 = static_cast<type_3DFED8 *>(l20);
                fp_28 = fp_24->vf_00C();
                if (fp_28 != 0) {
                    unk_13A8 = *fp_28;
                    sub_20830(fp_28, &unk_13C4, &unk_13D0, 0.0f);
                }
            } else {
                sub_204E0();
            }
        }
    }
}
// match: sub_20AC0 @ 0x00020AC0
// sp-match: sub_20AC0 @ 0x00016CD0
RwV3d *AIData::sub_20AC0(RwV3d *arg_0, type_3D3548 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = arg_4;
    if (var_4 == 0)
        var_4 = unk_13C0.sub_D4910();
    *arg_0 = *var_4->sub_CD550();
    if (((var_4->unk_2C >> 4) & 1) != 0)
        arg_0->y -= 120.0f;
    return arg_0;
}
// match: sub_20B30 @ 0x00020B30
// sp-match: sub_20B30 @ 0x00016D20
RwV3d *AIData::sub_20B30(RwV3d *arg_0, type_3D3548 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = arg_4;
    if (var_4 == 0)
        var_4 = unk_13E8.sub_D4910();
    *arg_0 = *var_4->sub_CD550();
    if (((var_4->unk_2C >> 4) & 1) != 0)
        arg_0->y -= 120.0f;
    return arg_0;
}
// match: sub_20BA0 @ 0x00020BA0
// sp-match: sub_20BA0 @ 0x0001B440
void AIData::sub_20BA0(type_3D3548 *arg_0)
{
    type_3D3548 *var_4;

    var_4 = unk_13E4.sub_D4910();
    if (var_4 != arg_0) {
        sub_20C00();
        arg_0->sub_D3FF0(unk_568);
        unk_13E4.sub_D48D0(arg_0);
    }
}
// match: sub_20C00 @ 0x00020C00
// sp-match: sub_20C00 @ 0x00016D70
void AIData::sub_20C00()
{
    type_3D3548 *var_4;

    var_4 = unk_13E4.sub_D4910();
    if (var_4 != 0) {
        var_4->sub_D4170(unk_568);
        unk_13E4.sub_D48D0(0);
    }
}
// match: sub_20C50 @ 0x00020C50
// sp-match: sub_20C50 @ 0x00016DA0
void AIData::sub_20C50(type_3D3548 *arg_0, RwInt32 arg_4)
{
    type_3D3548 *var_4;
    RwV3d var_10;

    unk_13E8.sub_D48D0(arg_0);
    if (arg_0 != 0) {
        var_4 = unk_13E4.sub_D4910();
        if (var_4 == arg_0) {
            unk_13EC = *var_4->sub_D42B0();
            unk_13F8 = *var_4->sub_D4290();
        } else {
            sub_20B30(&var_10, arg_0);
            if (sub_1FDF0(arg_0, &unk_13EC, 0) != 0.0f)
                RwV3dNormalize(&unk_13EC, &unk_13EC);
            else
                unk_13EC = *arg_0->sub_CD5A0();
            unk_13F8 = var_10;
        }
        unk_1404 = arg_4;
    }
    unk_1408.unk_00 = 0;
    unk_1408.unk_04 = 0;
    unk_1410 = 0;
}
// match: sub_20DA0 @ 0x00020DA0
// sp-match: sub_20DA0 @ 0x00016EB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_20DA0(type_3D3548 *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C,
                       RwReal arg_10, type_3DF8D8_04 *arg_14)
{
    RwInt32 var_4;
    RwInt32 loc8;
    type_3DF8D8 *local_C;
    type_3DFEEC *lcl_10;
    RwV3d var_1C;
    RwV3d bp_28;
    RwReal bp_2C;

    local_C = sub_198800(arg_14);
    var_4 = local_C->vf_008();
    loc8 = local_C != 0 && (var_4 == 0x2E || var_4 == 0x2D || var_4 == 0x2C);
    if (loc8 != 0) {
        if (var_4 == 0x2E || var_4 == 0x2C) {
            lcl_10 = static_cast<type_3DFEEC *>(local_C);
            if ((lcl_10->unk_10 & 0x80) != 0) {
                sub_20C50(arg_0, arg_8);
                unk_1428 = arg_C;
                unk_1424 = arg_4;
                unk_1408 = *arg_14;
                unk_1410 = lcl_10->get_unk_24();
                unk_1414 = unk_1410->sub_BA450(&unk_13F8, 100.0f, 1.0f);
                unk_1410->sub_BA990(unk_1414, &unk_1418, &unk_D30);
                unk_13F8 = unk_1418;
                if (arg_4 == 1) {
                    bp_2C = unk_1410->sub_BA450(unk_568->sub_CD550(), 100.0f, 1.0f);
                    unk_1410->sub_BA990(bp_2C, &var_1C, &unk_D30);
                    RwV3dSub(&bp_28, &var_1C, &unk_1418);
                    bp_28.y = 0.0f;
                    RwV3dNormalize(&unk_13EC, &bp_28);
                } else if (unk_1414 + 0.001f > 1.0f) {
                    unk_1410->sub_BA990(unk_1414 - 0.001f, &var_1C, &unk_D30);
                    RwV3dSub(&bp_28, &unk_1418, &var_1C);
                    bp_28.y = 0.0f;
                    RwV3dNormalize(&unk_13EC, &bp_28);
                } else {
                    unk_1410->sub_BA990(unk_1414 + 0.001f, &var_1C, &unk_D30);
                    RwV3dSub(&bp_28, &var_1C, &unk_1418);
                    bp_28.y = 0.0f;
                    RwV3dNormalize(&unk_13EC, &bp_28);
                }
                unk_142C = arg_10;
                if (arg_10 > 0.0f) {
                    sub_20370(&unk_1418, arg_10, 0.0f, 0.0f);
                    unk_13C4 = unk_13EC;
                }
            }
        }
    }
}
// match: sub_21120 @ 0x00021120
// sp-match: sub_21120 @ 0x000170C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_21120(type_3D3548 *arg_0)
{
    type_3D3548 *var_4;
    AIData *loc8;
    type_3D3548 *local_C;
    type_3DF8D8_04 *var10;
    RwV3d *l14;
    RwV3d ebp_20;

    var_4 = unk_13E8.sub_D4910();
    if (var_4 != 0 && arg_0 == var_4 && unk_578 != 0x26)
        return 1;
    if ((unk_49C & 0x2000) != 0) {
        loc8 = arg_0->vf_120();
        if (loc8 != 0 && (loc8->unk_49C & 0x2000) != 0) {
            local_C = unk_13C0.sub_D4910();
            if (local_C != 0) {
                if (local_C == loc8->unk_13C0.sub_D4910())
                    return 1;
            } else if (unk_13A0.unk_00 != 0 && unk_13A0.unk_04 != 0) {
                var10 = &loc8->unk_13A0;
                if (unk_13A0.unk_00 == var10->unk_00 && unk_13A0.unk_04 == var10->unk_04)
                    return 1;
            } else {
                l14 = &loc8->unk_13A8;
                RwV3dSub(&ebp_20, l14, &unk_13A8);
                if (RwV3dDotProduct(&ebp_20, &ebp_20) < 10000.0f)
                    return 1;
            }
        }
    }
    return 0;
}
// match: sub_212A0 @ 0x000212A0
// sp-match: sub_212A0 @ 0x000171D0
RwInt32 AIData::sub_212A0(type_3D3548 *arg_0)
{
    if (arg_0 == 0)
        arg_0 = unk_13E8.sub_D4910();
    if (arg_0 != 0 && unk_1410 != 0)
        return 1;
    return 0;
}
// match: sub_212E0 @ 0x000212E0
// sp-match: sub_212E0 @ 0x00017210
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_212E0()
{
    type_3D3548 *var_4;
    type_3D3548 *v8;
    RwV3d l14;

    var_4 = unk_13E8.sub_D4910();
    if (var_4 != 0 && sub_212A0(var_4) == 0) {
        v8 = unk_13E4.sub_D4910();
        if (v8 == var_4) {
            unk_13EC = *v8->sub_D42B0();
            unk_13F8 = *v8->sub_D4290();
        } else {
            sub_20B30(&l14, var_4);
            sub_20830(&l14, &unk_13EC, &unk_13F8, 0.0f);
        }
    }
}
// match: sub_213B0 @ 0x000213B0
// sp-match: sub_213B0 @ 0x000172C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_213B0(type_3D3548 *arg_0)
{
    RwV3d var_C;
    RwV3d var_18;
    RwInt32 var_1C;
    RwReal l20;

    if (arg_0 == 0)
        arg_0 = unk_13E8.sub_D4910();
    if (arg_0 != 0 && sub_212A0(arg_0) != 0) {
        var_1C = 1;
        sub_20B30(&var_C, arg_0);
        l20 = unk_1410->sub_BA450(&var_C, 100.0f, 1.0f);
        unk_1410->sub_BA990(l20, &var_18, &unk_D30);
        var_18.y = var_18.y + 40.0f;
        if (unk_1428 > 0.0f && sub_140C90(&var_C, &var_18) > unk_1428 * unk_1428
                && fabs(var_C.y - var_18.y) < 200.0f)
            var_1C = 0;
        if (var_1C != 0 && unk_1424 == 0 && l20 <= unk_1414)
            var_1C = 0;
        if (var_1C != 0) {
            unk_1414 = l20;
            unk_1418 = var_18;
            sub_20830(&var_18, &unk_13EC, &unk_13F8, flt_4275CC);
            if (unk_142C > 0.0f && (unk_49C & 0x2000) != 0) {
                unk_13A8 = var_18;
                unk_13C4 = unk_13EC;
                unk_13D0 = unk_13F8;
            }
            if (l20 > 0.9999f)
                sub_6B5F0("FollowEntityOnSpline_ArrivedAtDestination", (type_67620 *)(unk_568->vf_098()), 0, 0, 0, 0, true, false);
        }
    }
}
// match: ?sub_21610@AIData@@QAEHMMPAMPAUtype_3D3548@@H@Z @ 0x00021610
// sp-match: ?sub_21610@AIData@@QAEHMMPAMPAUtype_3D3548@@H@Z @ 0x000174B0
RwBool AIData::sub_21610(RwReal arg_0, RwReal arg_4, RwReal *arg_8, type_3D3548 *arg_C, RwInt32 arg_10)
{
    RwV3d var_10;
    RwV3d var_1C;
    RwReal var_20;

    if (sub_212A0(0))
    {
        var_10 = *arg_C->sub_CD550();
        if ((arg_C->unk_2C >> 4) & 1)
        {
            var_10.y -= 120.0f;
        }
        RwV3dSubMacro(&var_1C, &unk_1418, &var_10);
        var_20 = RwV3dDotProductMacro(&var_1C, &var_1C);
        do
        {
            __m128 var_50 = _mm_set_ss(var_20);
            __m128 var_80 = _mm_sqrt_ss(var_50);
            _mm_store_ss(arg_8, var_80);
        } while (0);
        if (arg_10)
        {
            RwReal var_84 = unk_1418.y + 200.0f;
            RwReal var_88 = unk_1418.y - 125.0f;

            if (var_10.y < var_88 || var_10.y > var_84)
            {
                return 0;
            }
        }
        if (var_20 <= arg_4 && var_20 >= arg_0)
        {
            return 1;
        }
    }
    return 0;
}
// match: ?sub_21790@AIData@@QAEHMMPAMH@Z @ 0x00021790
// sp-match: ?sub_21790@AIData@@QAEHMMPAMH@Z @ 0x000175D0
RwBool AIData::sub_21790(RwReal arg_0, RwReal arg_4, RwReal *arg_8, RwInt32 arg_C)
{
    RwV3d var_10;
    RwReal var_14;

    if (sub_212A0(0) && unk_F60)
    {
        RwV3dSubMacro(&var_10, &unk_1418, &unk_F60->unk_10);
        var_14 = RwV3dDotProductMacro(&var_10, &var_10);
        do
        {
            __m128 var_40 = _mm_set_ss(var_14);
            __m128 var_70 = _mm_sqrt_ss(var_40);
            _mm_store_ss(arg_8, var_70);
        } while (0);
        if (arg_C)
        {
            RwReal var_74 = unk_1418.y + 200.0f;
            RwReal var_78 = unk_1418.y - 125.0f;

            if (unk_F60->unk_10.y < var_78 || unk_F60->unk_10.y > var_74)
            {
                return 0;
            }
        }
        if (var_14 <= arg_4 && var_14 >= arg_0)
        {
            return 1;
        }
    }
    return 0;
}
// match: ?sub_21910@AIData@@QAEHMMPAM@Z @ 0x00021910
// sp-match: ?sub_21910@AIData@@QAEHMMPAM@Z @ 0x000176D0
RwBool AIData::sub_21910(RwReal arg_0, RwReal arg_4, RwReal *arg_8)
{
    RwV3d var_14;
    RwReal var_24;

    if (unk_49C & 0x2000) // not an address: flag 13
    {
        RwV3dSubMacro(&var_14, &unk_13D0, unk_568->sub_CD550());
        if ((unk_13B8 != 0.0f || unk_13BC != 0.0f) != 0)
        {
            var_14.y = 0.0f;
        }
        var_24 = RwV3dDotProductMacro(&var_14, &var_14);
        do
        {
            __m128 var_50 = _mm_set_ss(var_24);
            __m128 var_80 = _mm_sqrt_ss(var_50);
            _mm_store_ss(arg_8, var_80);
        } while (0);
        if (var_24 <= arg_4 && var_24 >= arg_0)
        {
            return 1;
        }
    }
    return 0;
}
// match: sub_21A90 @ 0x00021A90
// sp-match: sub_21A90 @ 0x000177D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_21A90(RwV3d *arg_0, RwV3d *arg_4)
{
    RwReal local_20;
    RwV3d var_1C;
    RwReal l10;
    RwInt32 local_C;
    RwMatrix *lv_8;
    RwFrame *var_4;

    var_4 = unk_568->get_unk_340();
    lv_8 = RwFrameGetLTM(var_4);
    l10 = RwV3dLength(arg_0);
    sub_1414C0(arg_4, arg_0, lv_8);
    var_1C = *unk_568->sub_CD550();
    var_1C.y += unk_568->unk_48;
    local_20 = 0.0f;
    if ((local_C = !unk_568->sub_D2FC0(&var_1C, arg_4, 0, &local_20, 1, 0, 1, 1, 0x20000, 0, 0)) == 0 // not an address: a flag
            && local_20 * l10 > flt_4275D4) {
        RwV3d var_2C;

        local_C = 1;
        RwV3dSub(&var_2C, arg_4, &var_1C);
        RwV3dScale(&var_2C, &var_2C, local_20);
        RwV3dAdd(arg_4, &var_2C, &var_1C);
    }
    if (local_C != 0) {
        RwV3d var_3C;
        RwReal var_30;

        var_3C = *arg_4;
        var_3C.y = var_3C.y - (flt_4275D0 + unk_568->unk_48);
        var_30 = 0.0f;
        local_C = unk_568->sub_D2FC0(arg_4, &var_3C, 0, &var_30, 1, 0, 0, 1, 0x20000, 0, 0); // not an address: a flag
        if (local_C != 0) {
            RwReal var_40;

            var_40 = (flt_4275D0 + unk_568->unk_48) * var_30;
            arg_4->y -= var_40 - unk_568->unk_48;
        }
    }
    return local_C;
}
// match: sub_21C90 @ 0x00021C90
// sp-match: sub_21C90 @ 0x00017960
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_21C90(type_3D3548 *arg_0)
{
    RwInt32 stk_64;
    RwInt32 var_60;
    RwInt32 stk_5C;
    RwReal local_58;
    RwV3d *local_54;
    RwV3d *local_50;
    RwV3d stk_4C;
    RwInt32 lv_40;
    RwInt32 local_3C;
    RwInt32 v38;
    RwV3d v34;
    RwV3d local_28;
    RwInt32 var_1C;
    type_3DAFC8_1DDC *var18;
    RwMatrix *stk_14;
    RwReal l10;
    RwReal local_C;
    RwReal lv_8;
    RwFrame *var_4;

    if (unk_568->vf_008() == 0 || arg_0 == 0)
        return 0;
#ifdef CODFH_SP // shape: VC declines to expand cmp_unk_2C after two early returns; the image expands it (SP 0x17960)
    if (unk_568 != 0) {
        RwInt32 k0 = arg_0->unk_2C & 7;
        RwInt32 k4 = unk_568->unk_2C & 7;

        if (k0 != k4 && k0 != 0 && k4 != 0 && k0 != 4 && k4 != 4)
            return 0;
    }
#else
    if (cmp_unk_2C(arg_0, unk_568) != 0)
        return 0;
#endif
    var_1C = 0;
    stk_64 = 0;
    var_60 = 0;
    stk_5C = 0;
    var18 = unk_568->vf_1C8();
    if (var18 != 0 && (unk_49C & 0x840001) != 0) { // not an address: flag bits
        var_1C = var18->unk_54[4].unk_00;
        stk_64 = var18->unk_54[5].unk_00;
        var_60 = var18->unk_54[6].unk_00;
        stk_5C = var18->unk_54[7].unk_00;
    }
    local_50 = arg_0->sub_CD550();
    local_54 = unk_568->sub_CD550();
    RwV3dSub(&v34, local_54, local_50);
    var_4 = unk_568->get_unk_340();
    stk_14 = RwFrameGetLTM(var_4);
    lv_40 = 0;
    l10 = RwV3dDotProduct(&stk_14->at, &v34);
    if (l10 >= 0.0f)
        lv_40 = 1;
    local_3C = 0;
    local_C = RwV3dDotProduct(&v34, &stk_14->right);
    if (local_C >= 0.0f)
        local_3C = 1;
    lv_8 = local_C < 0.0f ? -local_C : local_C;
    local_58 = l10 < 0.0f ? -l10 : l10;
    v38 = 0;
    if (lv_40 != 0 && var_1C == 0) {
        stk_4C.x = 0.0f;
        stk_4C.y = unk_568->unk_48;
        stk_4C.z = dword_4275D8;
        v38 = sub_21A90(&stk_4C, &local_28);
    }
    if (v38 == 0) {
        if (local_3C != 0) {
            stk_4C.x = dword_4275D8;
            stk_4C.y = unk_568->unk_48;
            stk_4C.z = 0.0f;
            v38 = sub_21A90(&stk_4C, &local_28);
            if (v38 == 0) {
                stk_4C.x = -dword_4275D8;
                v38 = sub_21A90(&stk_4C, &local_28);
            }
        } else {
            stk_4C.x = -dword_4275D8;
            stk_4C.y = unk_568->unk_48;
            stk_4C.z = 0.0f;
            v38 = sub_21A90(&stk_4C, &local_28);
            if (v38 == 0) {
                stk_4C.x = dword_4275D8;
                v38 = sub_21A90(&stk_4C, &local_28);
            }
        }
    }
    if (v38 == 0 && (lv_40 == 0 || lv_8 > local_58)) {
        stk_4C.x = 0.0f;
        stk_4C.y = unk_568->unk_48;
        stk_4C.z = -dword_4275D8;
        v38 = sub_21A90(&stk_4C, &local_28);
    }
    if (v38 != 0) {
        unk_568->vf_008()->unk_604 = local_28;
        unk_4F0 = &unk_568->vf_008()->unk_604;
        set_unk_5B0(&unk_568->vf_008()->unk_604);
    }
    return v38;
}
// match: sub_22110 @ 0x00022110
// sp-match: sub_22110 @ 0x00017C60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_22110()
{
    RwInt32 var_4;
    type_3D410 *local_8;

    var_4 = 0;
    if (unk_54C != 0 && ((unk_49C >> 4) & 1) != 0 && unk_558 <= 0.0f) {
        if (unk_56C != 0) {
            local_8 = &unk_56C->unk_04;
            if (local_8->get_unk_29C() > 900.0f) {
                var_4 = 1;
                local_8->unk_29C = 0.0f;
            } else {
                var_4 = 2;
            }
        } else {
            var_4 = 2;
        }
        unk_54C = 0;
        unk_554 = 0;
    }
    return var_4;
}
// The Distance Scheduler's range test against the current node (unk_F60):
// sub_21610's, from the node's point.
// match: ?sub_221E0@AIData@@QAEHMMPAMPAUtype_3D3548@@H@Z @ 0x000221E0
// sp-match: ?sub_221E0@AIData@@QAEHMMPAMPAUtype_3D3548@@H@Z @ 0x00017CE0
RwBool AIData::sub_221E0(RwReal arg_0, RwReal arg_4, RwReal *arg_8, type_3D3548 *arg_C, RwInt32 arg_10)
{
    RwV3d var_10;
    RwV3d var_1C;
    RwReal var_20;

    if (unk_F60)
    {
        var_10 = *arg_C->sub_CD550();
        if ((arg_C->unk_2C >> 4) & 1)
        {
            var_10.y -= 120.0f;
        }
        RwV3dSubMacro(&var_1C, &unk_F60->unk_10, &var_10);
        var_20 = RwV3dDotProductMacro(&var_1C, &var_1C);
        do
        {
            __m128 var_50 = _mm_set_ss(var_20);
            __m128 var_80 = _mm_sqrt_ss(var_50);
            _mm_store_ss(arg_8, var_80);
        } while (0);
        if (arg_10)
        {
            RwReal var_84 = unk_F60->unk_10.y + 200.0f;
            RwReal var_88 = unk_F60->unk_10.y - 125.0f;

            if (var_10.y < var_88 || var_10.y > var_84)
            {
                return 0;
            }
        }
        if (var_20 <= arg_4 && var_20 >= arg_0)
        {
            return 1;
        }
    }
    return 0;
}
// match: ?sub_22370@AIData@@QAEHPAUtype_F8350@@PAUtype_3D3548@@@Z @ 0x00022370
// sp-match: ?sub_22370@AIData@@QAEHPAUtype_F8350@@PAUtype_3D3548@@@Z @ 0x0001B480
RwInt32 AIData::sub_22370(type_F8350 *arg_0, type_3D3548 *arg_4)
{
    RwV3d var_10;
    type_154C0_1444 *var_14;
    RwMatrix var_60;
    RwV3d var_6C;
    RwV3d var_AC;
    RwInt32 var_B0;

    if (!arg_4 || ((unk_568->unk_2C >> 1) & 1))
        return 0;
    arg_4->vf_110(&var_10, unk_568, 1);
    var_14 = sub_22690(arg_0, &var_10);
    if (var_14)
        return var_14->unk_10;
    RwMatrixSetIdentity(&var_60);
    sub_F8FE0(arg_0, &var_6C, 0);
    RtQuatConvertToMatrix(&arg_0->unk_1C, &var_60);
    var_60.pos = arg_0->unk_10;
    sub_1414C0(&var_AC, &var_6C, &var_60);
    var_B0 = unk_568->sub_D2FC0(&var_AC, &var_10, 0, 0, 0, 0, 0, 1, 0x580000, 1, 0); // not an address: a flag
    sub_22780(arg_0, &var_10, var_B0);
    return var_B0;
}
// match: sub_22690 @ 0x00022690
// sp-match: sub_22690 @ 0x00017E00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_154C0_1444 *AIData::sub_22690(type_F8350 *arg_0, RwV3d *arg_4)
{
    RwInt32 var_4;
    RwReal v8;
    RwV3d l14;

    for (var_4 = 0; var_4 < 3; var_4++) {
        if (unk_1444[var_4].unk_00 == arg_0) {
            RwV3dSub(&l14, &unk_1444[var_4].unk_04, arg_4);
            v8 = l14.y;
            l14.y = 0.0f;
            if (RwV3dDotProduct(&l14, &l14) < flt_4275DC && v8 < flt_4275E0)
                return &unk_1444[var_4];
        }
    }
    return 0;
}
// match: sub_22780 @ 0x00022780
// sp-match: sub_22780 @ 0x00017E90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void AIData::sub_22780(type_F8350 *arg_0, RwV3d *arg_4, RwInt32 arg_8)
{
    RwInt32 var_4;
    RwInt32 v8;
    RwInt32 varC;

    v8 = -1;
    var_4 = 0;
    for (varC = 0; varC < 3; varC++) {
        if ((unk_F60 != 0 && unk_1444[varC].unk_00 != unk_F60) || var_4 > 0) {
            if (unk_F54 != 0 && unk_1444[varC].unk_00 == unk_F54) {
                if (v8 == -1)
                    v8 = varC;
            } else {
                v8 = varC;
            }
        } else {
            if (arg_0 == unk_F60) {
                v8 = varC;
                break;
            }
            var_4++;
        }
    }
    if (v8 >= 0 && v8 < 3) {
        unk_1444[v8].unk_00 = arg_0;
        unk_1444[v8].unk_04 = *arg_4;
        unk_1444[v8].unk_10 = arg_8;
    }
}
// match: sub_228A0 @ 0x000228A0
// sp-match: sub_228A0 @ 0x00017F30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 AIData::sub_228A0()
{
    RwReal lv_4C;
    type_F8350 *stk_48;
    RwInt32 lv_44;
    RwInt32 v40;
    type_F8350 *v3C;
    type_154C0_5BC *var_38;
    type_F8350 *l34;
    type_3D3548 *var30;
    RwReal ebp_2C;
    RwV3d var_28;
    RwV3d lcl_1C;
    RwV3d ebp_10;
    type_4C00E8 *l4;

    if (sub_19ED0() == 0)
        return 0;
    l4 = &unk_4C00E8;
    v3C = 0;
    l34 = 0;
    ebp_2C = get_unk_13B4() + -100.0f;
    var_38 = &unk_A24;
    for (v40 = var_38->unk_64.unk_2C - 1; v40 >= 0; v40--) {
        lv_44 = var_38->unk_B0[v40];
        stk_48 = l4->unk_2C[lv_44];
        lv_4C = sub_20570(&stk_48->unk_10);
        if (lv_4C > ebp_2C) {
            l34 = stk_48;
            break;
        }
        v3C = stk_48;
    }
    if (l34 == 0 && v3C == 0)
        return 0;
    if (l34 == 0 && v3C != 0) {
        ebp_10 = v3C->unk_10;
    } else if (l34 != 0 && v3C == 0) {
        return 0;
    } else if (l34 != 0 && v3C != 0) {
        RwSphere lcl_78;
        RwReal lcl_68;
        RwLine bp_64;

        bp_64.start = l34->unk_10;
        bp_64.end = v3C->unk_10;
        lcl_78.center = unk_13A8;
        lcl_78.radius = ebp_2C;
        if (RtLineSphereIntersectionTest(&bp_64, &lcl_78, &lcl_68) != 0 && lcl_68 > 0.0f) {
            RwV3d var_AC;
            RwV3d var_A0;
            RwReal var_94;
            RwReal stk_90;
            RwReal loc8C;
            RwReal ebp_88;
            RwV3d frm_84;

            RwV3dSub(&frm_84, &lcl_78.center, &bp_64.start);
            loc8C = RwV3dLength(&frm_84);
            RwV3dSub(&var_A0, &bp_64.end, &bp_64.start);
            var_94 = RwV3dLength(&var_A0);
            ebp_88 = (stk_90 = loc8C - lcl_78.radius) / var_94;
            RwV3dSub(&var_AC, &bp_64.end, &bp_64.start);
            RwV3dScale(&var_AC, &var_AC, ebp_88);
            RwV3dAdd(&ebp_10, &bp_64.start, &var_AC);
        } else {
            return 0;
        }
    } else {
        return 0;
    }
    var30 = unk_1374.sub_D4910();
    var_28 = ebp_10;
    var_28.y += unk_568->unk_48 * 2.0f;
    var30->vf_110(&lcl_1C, unk_568, 1);
    if (sub_42210(&var_28, &lcl_1C, unk_568, var30) != 0)
        return 1;
    return 0;
}
// match: sub_22C20 @ 0x00022C20
// sp-match: sub_22C20 @ 0x000181A0
const RwReal &sub_22C20(const RwReal &arg_0, const RwReal &arg_4, const RwReal &arg_8)
{
    if (arg_0 > arg_8)
        return arg_8;
    if (arg_0 < arg_4)
        return arg_4;
    return arg_0;
}
// The records' constructor (type_154C0_80.h): its handle zeroed. Inline, defined
// here, so the compiler emits it here (pCtor, 0x22C60; folded with the other
// handle holders' identical constructors).
// match: ??0type_154C0_80@@QAE@XZ @ 0x00022C60
// sp-match: ??0type_154C0_80@@QAE@XZ @ 0x000137B0
inline type_154C0_80::type_154C0_80()
{
}
