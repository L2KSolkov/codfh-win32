// Source\GameCore\ai\astarscheduler.cpp: the A* search scheduler. The path
// is the image's own (the asserts of sub_32F70 and sub_330E0 pass it as
// __FILE__). The unit starts at sub_32E50 at the latest: it and the three
// functions after it are the A* counterparts of the CanShoot scheduler's
// sub_31AD0, sub_31B10, sub_31B50 and sub_31B90, run on this unit's own two
// alfasched, and lead straight into the assert-bearing functions.

#include <stdio.h>

#include "rw/ostypes.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/AIData.h"
#include "types/alfasched.h"
#include "types/type_3D3548.h"
#include "types/type_3D2E7C.h"
#include "types/type_67620.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003CE3EC
extern const RwReal flt_3CE3EC = 16.666666f;
// 0x004275F4
const RwChar *off_4275F4[13] = { "eASST_PathToTarget", "eASST_PathToTarget_UseCover", "eASST_PathToEntity", "eASST_PathToEntity_UseCover", "eASST_PathToTarget_Vehicle", "eASST_PathToEntity_Vehicle", "eASST_PathToPoint", "eASST_PathToPoint_UseCover", "eASST_PathToPoint_Vehicle", "eASST_Retreat", "eASST_Coverpoint", "eASST_PathToFollowEntitySplinePoint", 0 };
// 0x00438DD8
RwInt32 dword_438DD8;
// 0x00438DDC
RwInt32 dword_438DDC;
// 0x00438DE0
RwInt32 dword_438DE0;
// 0x00438DE4
RwInt32 dword_438DE4;
// End of its data definitions.


// The two schedulers' callbacks, defined further down in this unit.
RwInt32 sub_332D0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
RwInt32 sub_334D0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
RwInt32 sub_33500(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C);
void sub_32F50();

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ??_C@_0BD@HCDFLHJF@AStar_PathNotFound?$AA@ @ 0x003CE078
// match: ??_C@_0CE@KNDGPBIN@eASST_PathToFollowEntitySplinePo@ @ 0x003CE2C0
// match: ??_C@_0BB@CCGINAKB@eASST_Coverpoint?$AA@ @ 0x003CE2E4
// match: ??_C@_0O@CCBOMFEL@eASST_Retreat?$AA@ @ 0x003CE2F8
// match: ??_C@_0BK@OCHKDFPG@eASST_PathToPoint_Vehicle?$AA@ @ 0x003CE308
// match: ??_C@_0BL@PHNICPGL@eASST_PathToPoint_UseCover?$AA@ @ 0x003CE324
// match: ??_C@_0BC@GOGPLNAN@eASST_PathToPoint?$AA@ @ 0x003CE340
// match: ??_C@_0BL@HDMEENCI@eASST_PathToEntity_Vehicle?$AA@ @ 0x003CE354
// match: ??_C@_0BL@LJLCBAB@eASST_PathToTarget_Vehicle?$AA@ @ 0x003CE370
// match: ??_C@_0BM@JGCCGOMA@eASST_PathToEntity_UseCover?$AA@ @ 0x003CE38C
// match: ??_C@_0BD@HLDPNKPJ@eASST_PathToEntity?$AA@ @ 0x003CE3A8
// match: ??_C@_0BM@NEOIKJMA@eASST_PathToTarget_UseCover?$AA@ @ 0x003CE3BC
// match: ??_C@_0BD@IMBFMKMP@eASST_PathToTarget?$AA@ @ 0x003CE3D8
// match: ?flt_3CE3EC@@3MB @ 0x003CE3EC
// match: ??_C@_0DG@JBOCLHBH@Somebody?5forgot?5to?5unregister?5in@ @ 0x003CE3F0
// match: ??_C@_0CG@LAGCOMJI@Source?2GameCore?2ai?2astarschedule@ @ 0x003CE428
// match: ??_C@_0DA@KDNIIFAO@AStar?5search?5registered?4?5Type?3?5?$CF@ @ 0x003CE450
// match: ??_C@_0CN@OJBPMDNK@Unregistering?5A?$CK?5search?5for?5obje@ @ 0x003CE480
// match: ?off_4275F4@@3PAPBDA @ 0x004275F4

// match: sub_32E50 @ 0x00032E50
// sp-match: sub_32E50 @ 0x000281E0

void sub_32E50()
{
    dword_438DE8.sub_71F20(0x4B, 1, 1, 0, sub_332D0, sub_334D0);
    dword_438E38.sub_71F20(0x20, 1, 1, 1, sub_332D0, sub_334D0);
    dword_438DD8 = 0;
    dword_438DDC = 0;
    dword_438DE4 = 0;
}

// match: sub_32EB0 @ 0x00032EB0
// sp-match: sub_32EB0 @ 0x00028240
void sub_32EB0()
{
    RwInt32 var_4;

    dword_438DD8 = 0;
    var_4 = dword_438DE8.sub_71FA0();
    if (var_4 != 0)
        sub_32F50();
    var_4 = dword_438E38.sub_71FA0();
    if (var_4 != 0)
        sub_32F50();
}

// match: sub_32F00 @ 0x00032F00
// sp-match: sub_32F00 @ 0x00028260
void sub_32F00()
{
    RwInt32 var_4;

    dword_438DD8 = 0;
    var_4 = dword_438DE8.sub_71FC0();
    if (var_4 != 0)
        sub_32F50();
    var_4 = dword_438E38.sub_71FC0();
    if (var_4 != 0)
        sub_32F50();
}

// match: sub_32F50 @ 0x00032F50
void sub_32F50()
{
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS)
    sub_19A750("Somebody forgot to unregister in the AStar Scheduler!");
#endif
}

// match: sub_32F70 @ 0x00032F70
// sp-match: sub_32F70 @ 0x00027D60
RwInt32 sub_32F70(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    RwInt32 l10;
    type_3D3548 *local_C;
    type_67620 *lv_8;
    AIData *var_4;
    RwReal var21C;
    RwChar var_218[0x200];

    local_C = arg_0->vf_024()->sub_71300();
    var_4 = local_C->vf_120();
    lv_8 = 0;
    if (local_C != 0 && var_4 != 0) {
        var21C = arg_8;
        if (arg_C == 0)
            arg_C = ++dword_438CA0;
        if (arg_4 == 12)
            l10 = dword_438DE8.sub_72120(arg_0, arg_4, var21C, arg_C).unk_00;
        else if (arg_4 != 10)
            l10 = dword_438DE8.sub_72050(arg_0, arg_4, var21C, arg_C).unk_00;
        else
            l10 = dword_438E38.sub_72050(arg_0, arg_4, var21C, arg_C).unk_00;
        lv_8 = sub_67620(l10);
        sprintf(var_218, "AStar search registered. Type: %s, SearchID: %d", off_4275F4[arg_4], arg_C);
#line 199 "Source\\GameCore\\ai\\astarscheduler.cpp"
        sub_19A750(local_C, 0, var_218, __FILE__, __LINE__);
    }
    return arg_C;
}

// match: sub_330E0 @ 0x000330E0
// sp-match: sub_330E0 @ 0x00027E90
void sub_330E0(type_67620 *arg_0, RwInt32 arg_4)
{
    type_3D3548 *l20C;
    RwChar var_208[0x200];

    dword_438DD8 = 1;
    sprintf(var_208, "Unregistering A* search for object. Type: %s", off_4275F4[arg_4]);
    l20C = arg_0->vf_024()->sub_71300();
#line 219 "Source\\GameCore\\ai\\astarscheduler.cpp"
    sub_19A750(l20C, 0, var_208, __FILE__, __LINE__);
    if (arg_4 != 10)
        dword_438DE8.sub_72240(arg_0);
    else
        dword_438E38.sub_72240(arg_0);
    dword_438DD8 = 0;
}

// match: sub_33190 @ 0x00033190
// sp-match: sub_33190 @ 0x00028280
void sub_33190(RwInt32 arg_0)
{
    dword_438DD8 = 1;
    dword_438DE0 = arg_0;
    dword_438DE8.sub_726E0(sub_33500);
    dword_438E38.sub_726E0(sub_33500);
    dword_438DE0 = 0;
    sub_F6270(arg_0);
    dword_438DD8 = 0;
}

// match: sub_331F0 @ 0x000331F0
// sp-match: sub_331F0 @ 0x00027F40
void sub_331F0(RwReal arg_0)
{
    RwInt32 var_4;

    dword_438DDC = 0;
    dword_438DE4 = 0;
    var_4 = dword_438DE8.sub_727D0();
    while (dword_438DDC == 0 && dword_438DE4 < var_4) {
        if (sub_F61A0(1) != 0) {
            dword_438DE8.sub_72560(arg_0);
            dword_438DE4++;
        } else {
            break;
        }
    }
    dword_438DDC = 0;
    dword_438DE4 = 0;
    var_4 = dword_438E38.sub_727D0();
    while (dword_438DDC == 0 && dword_438DE4 < var_4) {
        if (sub_F61A0(2) != 0) {
            dword_438E38.sub_72560(arg_0);
            dword_438DE4++;
        } else {
            break;
        }
    }
}

// match: sub_332D0 @ 0x000332D0
// sp-match: sub_332D0 @ 0x00028010
RwInt32 sub_332D0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    RwInt32 local_28;
    RwInt32 local_24;
    RwReal local_20;
    RwReal *var_1C;
    RwInt32 var18;
    RwInt32 stk_14;
    type_3D2E7C *l10;
    type_3D3548 *local_C;
    AIData *lv_8;
    RwInt32 var_4;

    l10 = arg_0->vf_024();
    local_C = l10->sub_71300();
    lv_8 = local_C->vf_120();
    var_4 = stk_14 = arg_4;
    var18 = var_4 == 10 ? 2 : 1;
    if (sub_F61A0(var18) == 0)
        return 1;
    if (sub_F6200(arg_C) != 0)
        return 1;
    if (local_C != 0 && lv_8 != 0) {
#ifdef CODFH_SP // shape: the bits copied as an integer (SP 0x28010 keeps the copy in ebx and pushes it)
        *(RwInt32 *)&local_20 = *(RwInt32 *)&arg_8;
#else
        var_1C = &local_20;
        *var_1C = arg_8;
#endif
        local_24 = arg_C;
        switch (var_4) {
        case 10:
            sub_34E60(arg_0, local_24);
            break;
        case 0:
        case 1:
        case 4:
            if (lv_8->get_unk_5A4() != 0)
                lv_8->sub_28C60(var_4, local_20, local_24);
            break;
        case 2:
        case 3:
        case 5:
            lv_8->sub_28B50(var_4, local_20, local_24);
            lv_8->unk_55C = 0;
            return 0;
        case 6:
        case 7:
        case 8:
        case 12:
            lv_8->sub_28D80(var_4, local_20, local_24);
            lv_8->unk_55C = 0;
            return 0;
        case 9:
            if (lv_8->sub_28F30() == 0) {
                sub_6B5F0("AStar_PathNotFound", (type_67620 *)arg_0->vf_024(), 0, 0, 0, 0, true, false);
                lv_8->unk_55C = 0;
                return 0;
            }
            local_28 = lv_8->sub_28D80(var_4, local_20, local_24);
            if (local_28 == 1) {
                lv_8->unk_55C = 0;
                return 0;
            }
            break;
        }
    }
    return 1;
}

// match: sub_334D0 @ 0x000334D0
// sp-match: sub_334D0 @ 0x00028180
RwInt32 sub_334D0(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
#ifdef CODFH_SP
    // shape: each path has its own return 1 (SP 0x281A4, 0x281AB)
    if (dword_438DD8 != 0) {
        if (sub_F6200(arg_C) != 0) {
            sub_F6270(arg_C);
            return 1;
        }
        return 1;
    }
#else
    if (dword_438DD8 != 0 && sub_F6200(arg_C) != 0)
        sub_F6270(arg_C);
#endif
    return 1;
}

// match: sub_33500 @ 0x00033500
// sp-match: sub_33500 @ 0x000281C0
RwInt32 sub_33500(type_67620 *arg_0, RwInt32 arg_4, RwReal arg_8, RwInt32 arg_C)
{
    return dword_438DE0 != arg_C;
}
