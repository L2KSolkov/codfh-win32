// The entity base class type_3D3548: its constructor, its own virtual
// functions and methods. Its original file name is not in the image, so it
// is named for its start address.

#include <math.h>
#include <xmmintrin.h>

#include "rw/ostypes.h"
#include "rw/rtquat.h"
#include "rw/batypes.h"
#include "rw/rpmaterial.h"
#include "game/data.h"
#include "game/functions.h"
#include "types/type_3D3548.h"
#include "types/type_44350.h"
#include "types/type_8E670.h"
#include "types/AIData.h"
#include "types/soundbank.h"
#include "types/type_F2FF0.h"
#include "types/type_4C00E8.h"
#include "types/type_3CE1FC.h"
#include "types/type_3D32F8.h"
#include "types/type_3DA6C0.h"
#include "types/type_3DAC58.h"
#include "types/type_3DDB98.h"
#include "types/type_92430.h"
#include <stdio.h>
#include <string.h>
#include "types/type_10F710.h"
#include "types/scriptvm.h"
#include "game/flags.h"
#include "game/clumpdata.h"
#include "types/type_3DAFC8.h"
#include "types/type_4B8600.h"
#include "types/alfaobject.h"
#include "types/type_3DAFC8_1DDC.h"
#include "game/clumputil.h"
#include "rw/rpatomic.h"
#include "types/animobjpool.h"
#include "rws/csystemcommands.h"
#include "game/gameloop.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D6F44
extern const RwReal flt_3D6F44 = 16.666666f;
// 0x003D6F48
extern const RwReal flt_3D6F48 = -5.0f;
// 0x003D6F4C
extern const RwV3d stru_3D6F4C = { 1.0f, 0.0f, 0.0f };
// 0x003D6F58
extern const RwV3d stru_3D6F58 = { 0.0f, 1.0f, 0.0f };
// 0x003D6F64
extern const RwV3d stru_3D6F64 = { 0.0f, 0.0f, 1.0f };
// 0x003D6F70
extern const RwReal flt_3D6F70 = 16.666666f;
// 0x003D6F74
extern const RwReal flt_3D6F74 = 0.01f;
// 0x003D6F78
extern const RwReal flt_3D6F78 = 0.01f;
// 0x003D6F7C
extern const RwReal flt_3D6F7C = 5.0f;
// 0x00429238
type_429238 dword_429238[2] = {
    { 0, (void *)(void (*)())sub_19A750 },
    { -1, 0 },
};
// 0x00429248
RwReal flt_429248 = 0.004166667f;
// 0x0042924C
RwReal flt_42924C = 1.8f;
// 0x00429250
RwReal flt_429250 = 5.0f;
// 0x004B6898
RwUInt32 dword_4B6898[32];
// 0x004B6918
RwUInt8 byte_4B6918[48];
// 0x004B6948
RwUInt8 byte_4B6948[48];
// 0x004B6978
const RwSphere *dword_4B6978;
// 0x004B697C
RwInt32 dword_4B697C;
// 0x004B6980
RwUInt8 byte_4B6980[48];
// 0x004B69B0
RwUInt8 byte_4B69B0[48];
// 0x004B69E0
RwInt32 dword_4B69E0;
// 0x004B69EC
RwInt32 dword_4B69EC;
// 0x004B69F0
RwInt32 dword_4B69F0;
// 0x004B69F8
RwInt32 dword_4B69F8;
// End of its data definitions.


// The callback of the entity's trigger: the entry arg_0 of dword_429238,
// or 0.
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D6F44@@3MB @ 0x003D6F44
// match: ?flt_3D6F48@@3MB @ 0x003D6F48
// match: ?stru_3D6F4C@@3URwV3d@@B @ 0x003D6F4C
// match: ?stru_3D6F58@@3URwV3d@@B @ 0x003D6F58
// match: ?stru_3D6F64@@3URwV3d@@B @ 0x003D6F64
// match: ?flt_3D6F70@@3MB @ 0x003D6F70
// match: ?flt_3D6F74@@3MB @ 0x003D6F74
// match: ?flt_3D6F78@@3MB @ 0x003D6F78
// match: ?flt_3D6F7C@@3MB @ 0x003D6F7C
// match: ??_C@_0L@EBIPFPBO@PlayAction?$AA@ @ 0x003D6F80
// match: __real@43800000 @ 0x003D6F8C
// match: ??_C@_0ID@JDLOLKHH@GameEntity?5Animation?5Event?3?5WARN@ @ 0x003D6F90
// match: ??_C@_0BK@PEMDLGD@WallCollisionNotification?$AA@ @ 0x003D7014
// match: ??_C@_0BM@NOAGACAK@GroundCollisionNotification?$AA@ @ 0x003D7030
// match: ??_C@_0BG@HEIBGHNE@CollisionNotification?$AA@ @ 0x003D704C
// match: __real@bdcccccd @ 0x003D7064
// match: __real@49742400 @ 0x003D7068
// match: __real@c9742400 @ 0x003D706C
// match: __real@4b189680 @ 0x003D7070
// match: __real@cb189680 @ 0x003D7074
// match: __real@4cbebc20 @ 0x003D7078
// match: __real@ccbebc20 @ 0x003D707C
// match: __real@ba83126f @ 0x003D7080
// match: __real@c2960000 @ 0x003D7084
// match: ??_C@_0BA@MNANDKJH@TargetDestroyed?$AA@ @ 0x003D7088
// match: ??_C@_09EBGICELD@TargetHit?$AA@ @ 0x003D7098
// match: ??_C@_0FK@HEHNKIFC@?$CK?$CK?$CKERROR?3?5Unable?5to?5create?5?$CFs?5ob@ @ 0x003D70A8
// match: __ehhandler$??0type_3D3548@@QAE@XZ>1>8 @ 0x0041CBAC
// match: __ehhandler$??0type_3D3548@@QAE@XZ>1 @ 0x0041CBEC
// match: __ehhandler$?sub_CDFA0@@YAHPAUtype_F2FF0@@@Z>1>8 @ 0x0041CC08
// match: __ehhandler$?sub_CDFA0@@YAHPAUtype_F2FF0@@@Z>1 @ 0x0041CC10
// match: __ehhandler$?vf_1D0@type_3D3548@@UAEXXZ>1>8 @ 0x0041CC2C
// match: __ehhandler$?vf_1D0@type_3D3548@@UAEXXZ>1 @ 0x0041CC34
// match: ?dword_429238@@3PAUtype_429238@@A @ 0x00429238
// match: ?flt_429248@@3MA @ 0x00429248
// match: ?flt_42924C@@3MA @ 0x0042924C
// match: ?flt_429250@@3MA @ 0x00429250

// match: ?sub_CC8A0@@YAPAXH@Z @ 0x000CC8A0

static void *sub_CC8A0(RwInt32 arg_0)
{
    type_429238 *var_4;

    var_4 = dword_429238;
    while (var_4->unk_00 != -1)
    {
        if (var_4->unk_00 == arg_0)
        {
            return var_4->unk_04;
        }
        var_4++;
    }
    return 0;
}

// The ground's height under arg_0: a line test from 150 above it to 4000
// below; its own height when nothing is hit.
// match: ?sub_CC8E0@@YAMPAURwV3d@@@Z @ 0x000CC8E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_CC8E0(RwV3d *arg_0)
{
    RwV3d var_24;
    RwV3d l18;
    RwV3d var_C;

    l18 = *arg_0;
    l18.y += 150.0f;
    var_C = *arg_0;
    var_C.y -= 4000.0f;
    if (!sub_FCAE0(&l18, &var_C, &var_24, 0, 0x410000, 0, 1)) // not an address: flags
    {
        return arg_0->y;
    }
    return var_24.y;
}

// match: ??0type_3D3548@@QAE@XZ @ 0x000CC960
// match: __ehhandler$??0type_3D3548@@QAE@XZ-0x7A @ 0x00300BE0
// match: __ehhandler$??0type_3D3548@@QAE@XZ @ 0x00300C5A
type_3D3548::type_3D3548()
{
    dword_4B69F8++;
    unk_244 = dword_4B69F8;
    vf_22C();
}

// match: ?vf_22C@type_3D3548@@UAEHXZ @ 0x000CCB70
RwInt32 type_3D3548::vf_22C()
{
    unk_384 = 0;
    unk_20 = dword_429264;
    dword_429264 = 10;
    sub_D5BE0(this);
    sub_CCDF0();
    unk_38C = 0;
    unk_39C.clear();
    unk_390.clear();
    unk_90.sub_CCC60();
    unk_29C = 0;
    unk_80 = 1.0f;
    unk_88_14 = 1;
    return 1;
}

// match: ?sub_CCC60@type_8E670@@QAEXXZ @ 0x000CCC60
void type_8E670::sub_CCC60()
{
    unk_08 = 0;
    unk_00 = 0;
    unk_0C = 0.0f;
    unk_04 = 0.0f;
    unk_1C = 0.0f;
    unk_18 = 0;
    unk_14 = 0;
    unk_10 = 0;
    unk_20 = 0;
}

// match: ?sub_CCCD0@type_3D3548@@QAEXPAUtype_712B0@@@Z @ 0x000CCCD0
void type_3D3548::sub_CCCD0(type_712B0 *arg_0)
{
    unk_344.sub_144940(arg_0);
    if (arg_0->unk_44 != -1)
    {
        unk_388 = sub_CC8A0(arg_0->unk_44);
    }
    else
    {
        unk_388 = 0;
    }
}

// match: ?vf_230@type_3D3548@@UAEXXZ @ 0x000CCD30
void type_3D3548::vf_230()
{
    unk_38C = 0;
    unk_39C.clear();
    unk_390.clear();
    if (get_unk_34C())
    {
        get_unk_34C()->sub_BD860();
    }
    if (unk_88_14)
    {
        unk_88_14 = 0;
    }
}

// Resets its state (vf_22C, once registered).
// match: ?sub_CCDF0@type_3D3548@@QAEXXZ @ 0x000CCDF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_CCDF0()
{
    RwInt32 var_8;
    RwInt32 l4;

    unk_88_14 = 0;
    unk_24 = 0x11;
    unk_10 = 0;
    unk_14 = 0;
    unk_1C = 0;
    unk_28 = 0;
    unk_2C = 0;
    unk_30 = 0;
    unk_34 = 0;
    unk_38 = 0;
    unk_88_1 = 0;
    unk_280 = 0;
    unk_288 = 0;
    unk_284 = 0;
    unk_28C = 0;
    unk_54 = -1;
    unk_88_12 = 0;
    unk_354 = 0;
    unk_358 = 0;
    unk_88_8 = 0;
    unk_88_0 = 0;
    unk_290 = -1;
    unk_294 = -1;
    unk_350 = 0;
    unk_388 = 0;
    unk_88_10 = 0;
    unk_334 = 0;
    unk_1B8 = 0;
    unk_1BC = 1;
    for (l4 = 0; l4 < 2; l4++)
    {
        unk_35C[l4].sub_D48D0(0);
        unk_364[l4] = -1;
        unk_36C[l4] = -1;
    }
    sub_D3700(0, 0, 0);
    unk_380 = 0;
    unk_48 = 100.0f;
    unk_4C = 50.0f;
    unk_50 = 0x41A00000; // the bits of 20.0f
    zero_v3d(&unk_3C_v);
    unk_88_2 = 1;
    zero_v3d(&unk_C0);
    zero_v3d(&unk_CC);
    zero_v3d(&unk_D8_v);
    zero_v3d(&unk_E4_v);
    zero_v3d(&unk_FC);
    zero_v3d(&unk_F0_v);
    zero_v3d(&unk_10C);
    zero_v3d(&unk_134);
    zero_v3d(&unk_154);
    zero_v3d(&unk_160);
    zero_v3d(&unk_140);
    zero_v3d(&unk_16C);
    zero_v3d(&unk_178);
    zero_v3d(&unk_118);
    zero_v3d(&unk_124);
    zero_v3d(&unk_1A4);
    zero_v3d(&unk_68_v);
    unk_14C = 0;
    unk_108 = flt_3D6F48;
    unk_130 = 0;
    unk_150 = 0;
    unk_184 = 0;
    unk_188 = 0;
    unk_18C = 0;
    unk_190 = 0;
    unk_194 = 0;
    unk_198 = 0;
    unk_19C = 0;
    unk_1A0 = 0;
    unk_1B0 = 0;
    unk_1B4 = 0;
    unk_88_3 = 0;
    unk_88_4 = 0;
    unk_88_5 = 0;
    unk_88_6 = 0;
    unk_88_7 = 0;
    unk_7C = 0;
    unk_248 = 0;
    unk_24C = 0;
    unk_58 = 3;
    unk_28_14 = 0;
    unk_88_11 = 1;
    unk_2A8 = 0;
    unk_2AC = 0;
    unk_2A0 = 0;
    unk_298 = 0;
    unk_330 = 0;
    for (var_8 = 0; var_8 < 16; var_8++)
    {
        unk_2B0[var_8] = 0;
        unk_2F0[var_8] = 0;
    }
    unk_88_9 = 1;
    unk_84 = 0;
    unk_78 = 0;
}

// match: ?sub_CD530@type_3D3548@@QAEXH@Z @ 0x000CD530
void type_3D3548::sub_CD530(RwInt32 arg_0)
{
    unk_384 = arg_0;
}

// match: ?sub_CD550@type_3D3548@@QAEPAURwV3d@@XZ @ 0x000CD550
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *type_3D3548::sub_CD550()
{
    RwMatrix *var_C;
    RwV3d *bp_8;
    RwFrame *bp_4;

    bp_8 = 0;
    bp_4 = unk_338.unk_08;
    if (bp_4)
    {
        var_C = RwFrameGetLTM(bp_4);
        if (var_C)
        {
            bp_8 = RwMatrixGetPos(var_C);
        }
    }
    return bp_8;
}

// match: ?sub_CD5A0@type_3D3548@@QAEPAURwV3d@@XZ @ 0x000CD5A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *type_3D3548::sub_CD5A0()
{
    RwMatrix *var_C;
    RwV3d *bp_8;
    RwFrame *bp_4;

    bp_8 = 0;
    bp_4 = unk_338.unk_08;
    if (bp_4)
    {
        var_C = RwFrameGetLTM(bp_4);
        if (var_C)
        {
            bp_8 = &var_C->at;
        }
    }
    return bp_8;
}

// Moves its frame to arg_0 (and its primary animation's two matrices by
// as much).
// match: ?vf_0C0@type_3D3548@@UAEXPAURwV3d@@@Z @ 0x000CD5F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_0C0(RwV3d *arg_0)
{
    RwMatrixTag *var_1C;
    RwMatrixTag *var_18;
    RwV3d var_14;
    RwV3d *var8;
    RwFrame *l4;

    l4 = get_unk_340();
    var8 = RwMatrixGetPos(RwFrameGetLTM(l4));
    var_14.x = arg_0->x - var8->x;
    var_14.y = arg_0->y - var8->y;
    var_14.z = arg_0->z - var8->z;
    if (unk_284)
    {
        var_1C = &unk_284->unk_100;
        var_1C->pos.x = var_14.x + var_1C->pos.x;
        var_1C->pos.y = var_14.y + var_1C->pos.y;
        var_1C->pos.z = var_14.z + var_1C->pos.z;
        var_18 = &unk_284->unk_140;
        var_18->pos.x = var_14.x + var_18->pos.x;
        var_18->pos.y = var_14.y + var_18->pos.y;
        var_18->pos.z = var_14.z + var_18->pos.z;
    }
    unk_68_v = *arg_0;
    unk_88_2 = 1;
    unk_14C = 0;
    RwFrameTranslate(l4, &var_14, rwCOMBINEPOSTCONCAT);
    RwFrameUpdateObjects(get_unk_340());
}

// Its frame's position (its modelling matrix's).
// match: ?vf_0C4@type_3D3548@@UAEPAMXZ @ 0x000CD740
RwReal *type_3D3548::vf_0C4()
{
    RwFrame *var_4;

    var_4 = unk_338.unk_08;
    return (RwReal *)RwMatrixGetPos(RwFrameGetMatrix(var_4));
}

// Its frame's world position.
// match: ?vf_0CC@type_3D3548@@UAEPAURwV3d@@XZ @ 0x000CD760
RwV3d *type_3D3548::vf_0CC()
{
    RwFrame *var_4;

    var_4 = unk_338.unk_08;
    return RwMatrixGetPos(RwFrameGetLTM(var_4));
}

// match: ?vf_0D4@type_3D3548@@UAEXPAURtQuat@@@Z @ 0x000CD790
// Turns the entity where it stands to the rotation *arg_0.
void type_3D3548::vf_0D4(RtQuat *arg_0)
{
    RwFrame *var_C;
    RwMatrix *var_10;
    RwMatrix var_50;

    var_C = get_unk_340();
    var_10 = RwFrameGetMatrix(var_C);
    RwMatrixSetIdentityMacro(&var_50);
    RtQuatConvertToMatrix(arg_0, &var_50);
    var_50.pos = var_10->pos;
    RwFrameTransform(var_C, &var_50, rwCOMBINEREPLACE);
    RwFrameUpdateObjects(var_C);
}

// match: ?vf_0D0@type_3D3548@@UAEXPAURwV3d@@@Z @ 0x000CD9D0
// Turns the entity where it stands to face the point *arg_0 (none when it
// is there already).
void type_3D3548::vf_0D0(RwV3d *arg_0)
{
    RwFrame *var_C;
    RwMatrix *var_10;
    RwV3d var_1C;
    RwMatrix var_70;

    var_C = get_unk_340();
    var_10 = RwFrameGetMatrix(var_C);
    RwV3dSubMacro(&var_1C, arg_0, &var_10->pos);
    if (fabs(RwV3dDotProductMacro(&var_1C, &var_1C)) > 0.0001f)
    {
        RwV3dNormalize(&var_1C, &var_1C);
        sub_140CE0(&var_70, &var_10->pos, &var_1C);
        RwFrameTransform(var_C, &var_70, rwCOMBINEREPLACE);
        RwFrameUpdateObjects(var_C);
    }
}

// match: ?vf_0D8@type_3D3548@@UAEXPAURwV3d@@@Z @ 0x000CDAC0
// Turns the entity where it stands to face along *arg_0 (none for a zero
// vector).
void type_3D3548::vf_0D8(RwV3d *arg_0)
{
    RwFrame *var_C;
    RwMatrix *var_10;
    RwV3d var_24;
    RwMatrix var_70;

    var_C = get_unk_340();
    var_10 = RwFrameGetMatrix(var_C);
    if (fabs(RwV3dDotProductMacro(arg_0, arg_0))
        > 0.0001f)
    {
        RwV3dNormalize(&var_24, arg_0);
        sub_140CE0(&var_70, &var_10->pos, &var_24);
        RwFrameTransform(var_C, &var_70, rwCOMBINEREPLACE);
        RwFrameUpdateObjects(var_C);
    }
}

// match: ?sub_CDB90@type_3D3548@@QAEPAURwV3d@@XZ @ 0x000CDB90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *type_3D3548::sub_CDB90()
{
    RwMatrix *var_C;
    RwFrame *bp_8;
    RwV3d *bp_4;

    bp_4 = 0;
    bp_8 = unk_338.unk_08;
    if (bp_8)
    {
        var_C = RwFrameGetLTM(bp_8);
        if (var_C)
        {
            bp_4 = &var_C->up;
        }
    }
    return bp_4;
}

// match: ?sub_CDBE0@type_3D3548@@QAEPAURwV3d@@XZ @ 0x000CDBE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *type_3D3548::sub_CDBE0()
{
    RwMatrix *var_C;
    RwFrame *bp_8;
    RwV3d *bp_4;

    bp_4 = 0;
    bp_8 = unk_338.unk_08;
    if (bp_8)
    {
        var_C = RwFrameGetLTM(bp_8);
        if (var_C)
        {
            bp_4 = (RwV3d *)var_C;
        }
    }
    return bp_4;
}

// match: ?sub_CDC30@type_3D3548@@QAEHXZ @ 0x000CDC30
RwInt32 type_3D3548::sub_CDC30()
{
    RwInt32 var_4;

    var_4 = 0;
    if (unk_284)
    {
        var_4 = unk_284->sub_7C850();
    }
    return var_4;
}

// Plays the animation arg_0 on its primary animation player: 0 without
// one or when the animation cannot be found or played; 1 at once while
// unk_88_12 is set and arg_18 is not.
// match: ?vf_208@type_3D3548@@UAEHHHHMMMH@Z @ 0x000CDC70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D3548::vf_208(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwReal arg_C,
                            RwReal arg_10, RwReal arg_14, RwInt32 arg_18)
{
    RwInt32 l20;
    type_F8350 *var_1C;
    AIData *var_18;
    RwInt32 var_14;
    bool lD;
    RwReal var_C;
    RtAnimAnimation *bp_8;
    type_783F0 *bp_4;

    if (!unk_284)
    {
        return 0;
    }
    var_C = 0.0f;
    if (unk_88_12 && !arg_18)
    {
        return 1;
    }
    if (sub_77B70(arg_0, (void **)((RwInt32 *)&bp_8), (void **)((RwInt32 *)&bp_4)))
    {
        var_18 = vf_120();
        if (var_18 && var_18->unk_528)
        {
            var_1C = var_18->unk_F60;
            if (var_1C)
            {
                var_18->sub_266A0(var_1C);
            }
            var_18->unk_528 = 0;
        }
        unk_88_12 = arg_18;
        lD = unk_284->sub_76920();
        if (arg_8 || !lD)
        {
            unk_284->sub_794C0(arg_C);
        }
        var_14 = unk_284->sub_796A0(bp_8, arg_0, arg_4, bp_4, var_C, arg_10, arg_14);
        if (var_14 == -1)
        {
            return 0;
        }
        if (var_14 == -2)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}

// match: ?vf_21C@type_3D3548@@UAEXM@Z @ 0x000CDDD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_21C(RwReal arg_0)
{
    RwReal var_18;
    bool var_11;
    RwReal lv_10;
    RwV3d var_C;

    sub_16D7F0(0x16);
    if (!vf_00C() || unk_2C == 0x100000) // not an address: a kind bit
    {
        var_11 = !unk_28_13;
    }
    else
    {
        var_11 = 0;
    }
    lv_10 = flt_429288 * flt_3D6F70 * 0.001f;
    unk_284->sub_7A580(lv_10, &var_C, var_11);
    if (unk_28C)
    {
        unk_28C->sub_7A580(lv_10, 0, var_11);
    }
    if (unk_130)
    {
        if (arg_0 < 0.1f)
        {
            var_18 = 0.0f;
        }
        else
        {
            var_18 = 1.0f / arg_0;
        }
        unk_154.x = var_C.x * var_18 + unk_154.x;
        unk_154.y = var_C.y * var_18 + unk_154.y;
        unk_154.z = var_C.z * var_18 + unk_154.z;
    }
    else
    {
        unk_154.x = var_C.x + unk_154.x;
        unk_154.y = var_C.y + unk_154.y;
        unk_154.z = var_C.z + unk_154.z;
    }
    sub_16D850(0x16);
}

// match: ?sub_CDF40@type_3D3548@@QAEXM@Z @ 0x000CDF40
void type_3D3548::sub_CDF40(RwReal arg_0)
{
    if (!unk_284)
    {
        return;
    }
    sub_16D7F0(0x17);
    unk_284->sub_7C090(arg_0 * flt_3D6F70 * 0.001f, 0);
    sub_16D850(0x17);
}

// The matrix of the bone arg_8 of the clump arg_0 into *arg_4 (a particle
// system starts with its matrix); whether it could. The rest only known by
// width.
struct RpClump;
RwInt32 sub_EC2D0(RpClump *arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C, RwInt32 arg_10);

// The particle system arg_0's callback (vf_170): while its entity is
// there, attaches it to the entity's clump (sub_EC2D0); without the
// entity, 0 once an endless system is left behind.
// match: ?sub_CDFA0@@YAHPAUtype_F2FF0@@@Z @ 0x000CDFA0
// match: __ehhandler$?sub_CDFA0@@YAHPAUtype_F2FF0@@@Z-0x8 @ 0x00300C70
// match: __ehhandler$?sub_CDFA0@@YAHPAUtype_F2FF0@@@Z @ 0x00300C78
RwInt32 sub_CDFA0(type_F2FF0 *arg_0)
{
    RwInt32 var_14 = 1;
    type_D48D0 lv_10;
    type_3D3548 *var_18;

    lv_10 = arg_0->unk_150;
    var_18 = lv_10.sub_D4910();
    if (var_18)
    {
        sub_EC2D0(var_18->get_unk_264(), (RwInt32)arg_0, arg_0->unk_158, 0, 0);
    }
    else if (arg_0)
    {
        if (arg_0->unk_44->unk_20 == 0.0f)
        {
            var_14 = 0;
        }
    }
    return var_14;
}

// Collision on or off: environment and entity collision both.
// match: ?vf_170@type_3D3548@@UAEXHHHH@Z @ 0x000CE070
// Its animation's events (arg_0, with the event's data arg_4), once it has
// an animation: the end of an animation (1: the performance player's end,
// clearing unk_88_12), a sound (1100, by the surface's or its own tag),
// particles at a point of its model (1300) or at an offset (1301), on a
// tagged matrix that follow it (1302), a script message with up to three
// packed arguments (1400) or an entity's record (1401), "PlayAction" to the
// nearest animated background entity in the state 0 (1500) or 1 (2800)
// within 300, vf_190 (1600), vf_0B0 (2100), a prop taken (2200) or dropped
// (2201), the soldier's tracking (2300) and a strike (1700).
void type_3D3548::vf_170(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8, RwInt32 arg_C)
{
    if (unk_284 == 0)
        return;
    type_3DF8D8_04 var_C;
    type_4E5E40 *var_10;
    type_4E5E40_08 *var_14;

    var_10 = &dword_4E5E40;
    var_14 = var_10->unk_08;
    switch ((RwUInt32)arg_0)
    {
    case 1:
        ((type_3D2CD0 *)vf_090())->sub_6DF90(arg_8, unk_88_12);
        unk_88_12 = 0;
        break;
    case 1100:
        memcpy(&var_C, (void *)arg_4, 8);
        if (((type_10F710_1A48_snd *)arg_4)->unk_08 & 1)
        {
            if (unk_294 < 0)
            {
                if (dword_44E838)
                {
                    type_3DF8D8_04 var_1C;
                    type_3D3548 *var_20;

                    var_1C.unk_00 = 0x9FAFD39B; // not an address: a key
                    var_1C.unk_04 = 0xAB43C2E3; // not an address: a key
                    var_20 = sub_1745A0(0);
                    dword_4B1E98.sub_8A980(&var_1C, 0, 0, var_20->sub_CD550(), 1, 0);
                }
                if (dword_44E860 && dword_44E874)
                {
                    RwChar var_120[0x100];

                    sprintf(var_120,
                            "GameEntity Animation Event: WARNING! Entity on non-tagged surface calling index "
                            "alias 0x%x, 0x%x! Using 0 for Index Alias purposes",
                            var_C.unk_00, var_C.unk_04);
                    sub_19A750(var_120);
                }
                unk_294 = 0;
            }
            unk_1C0.sub_8AA70(&var_C, var_14[unk_294].unk_00, this, 0, sub_CD550(), 0, 0);
        }
        else if (((type_10F710_1A48_snd *)arg_4)->unk_08 & 0x10)
        {
            unk_1C0.sub_8AA70(&var_C, var_14[unk_290].unk_00, this, 0, sub_CD550(), 0, 0);
        }
        else
        {
            sub_19A750(0, 1, var_C, 1);
            unk_1C0.sub_8A980(&var_C, this, 0, sub_CD550(), 0, 0);
        }
        break;
    case 1300:
    {
        type_10F710_1A48_ev *var_124;
        RwV3d *var_128;
        RwFrame *var_130;
        RwMatrix *var_134;
        RwV3d var_140;
        RwMatrix var_180;

        var_124 = (type_10F710_1A48_ev *)arg_4;
        var_128 = (RwV3d *)arg_4;
        var_130 = get_unk_340();
        var_134 = RwFrameGetLTM(var_130);
        var_140.x = var_128->x;
        var_140.y = var_128->y;
        var_140.z = var_128->z;
        var_180 = *var_134;
        RwMatrixTranslate(&var_180, &var_140, rwCOMBINEPRECONCAT);
        sub_F2FF0(var_124->unk_0C, &var_180, 0, 0, 0, 0);
        break;
    }
    case 1301:
    {
        type_10F710_1A48_ev *var_184;
        RwV3d *var_188;
        RwV3d var_194;
        RwMatrix var_1E0;

        var_184 = (type_10F710_1A48_ev *)arg_4;
        var_188 = (RwV3d *)arg_4;
        var_194.x = var_188->x;
        var_194.y = var_188->y;
        var_194.z = var_188->z;
        RwMatrixSetIdentity(&var_1E0);
        RwMatrixTranslate(&var_1E0, &var_194, rwCOMBINEREPLACE);
        sub_F2FF0(var_184->unk_0C, &var_1E0, 0, 0, 0, 0);
        break;
    }
    case 1302:
    {
        type_10F710_1A48_ev *var_1E4;
        RwMatrix var_230;
        type_F2FF0 *var_234;

        var_1E4 = (type_10F710_1A48_ev *)arg_4;
        if (sub_EC310(get_unk_264(), unk_284->get_unk_18(), &var_230, var_1E4->unk_00, 0, 1))
        {
            var_234 = (type_F2FF0 *)sub_F2FF0(var_1E4->unk_0C, &var_230, 0, 0, 0, 0);
            if (var_234 && var_1E4->unk_04)
            {
                var_234->unk_150_h = unk_384_h;
                var_234->unk_158 = var_1E4->unk_00;
                var_234->unk_154 = sub_CDFA0;
            }
        }
        break;
    }
    case 1400:
    {
        type_10F710_1A48_ev *var_238;
        RwInt32 var_23C;
        RwInt32 var_248[3];
        RwInt32 var_254[3];
        RwInt32 var_258;
        RwInt32 var_264[3];

        var_238 = (type_10F710_1A48_ev *)arg_4;
        var_23C = sub_6A860(var_238->unk_00, var_238->unk_04);
        var_248[0] = (var_238->unk_0C >> 16) & 0xF;
        var_248[1] = (var_238->unk_0C >> 20) & 0xF;
        var_248[2] = (var_238->unk_0C >> 24) & 0xF;
        var_254[0] = var_238->unk_08 & 0xFFFF;
        var_254[1] = (var_238->unk_08 & 0xFFFF0000) >> 16;
        var_254[2] = var_238->unk_0C & 0xFFFF;
        for (var_258 = 0; var_258 < 3; var_258++)
        {
            if (var_248[var_258] == 1)
                var_264[var_258] = var_254[var_258];
            else if (var_248[var_258] == 2)
                *(RwReal *)&var_264[var_258] = var_254[var_258] / 256.0f;
            else
                break;
        }
        sub_6B680(var_23C, 0, (type_42E00_10 *)((RwInt32)get_unk_34C()), 0, var_264, var_258, true, false);
        break;
    }
    case 1401:
    {
        type_3DF8D8 *var_26C;
        type_3DF8D8_BD900 *var_270;
        type_10F710_1A48_ev *var_274;
        RwInt32 var_278;
        type_42E00_00 *var_27C;
        RwInt32 var_280;
        RwInt32 var_2A8[10];
        type_3D3548 *var_2AC;

        var_26C = 0;
        var_270 = 0;
        var_274 = (type_10F710_1A48_ev *)arg_4;
        var_278 = sub_6A860(var_274->unk_00, var_274->unk_04);
        var_27C = sub_6A7D0(var_278);
        for (var_280 = 0; var_280 < 10; var_280++)
            var_2A8[var_280] = 0;
        var_C.unk_00 = var_274->unk_08;
        var_C.unk_04 = var_274->unk_0C;
        var_26C = sub_198800(&var_C);
        var_270 = (type_3DF8D8_BD900 *)var_26C;
        var_2AC = var_270->unk_24.sub_D4910();
        sub_6B680(var_278, (type_67620 *)(var_2AC->vf_098()), (type_42E00_10 *)((RwInt32)get_unk_34C()), 0, var_2A8, var_27C->unk_10, true, false);
        break;
    }
    case 1500:
    {
        RwReal var_2B4;
        type_3D32F8 *var_2B8;
        RwInt32 var_2BC;
        type_3D3548 *var_2C0;
        type_3D32F8 *var_2C4;
        RwV3d var_2D4;
        RwReal var_2D8;
        RwInt32 var_2DC;

        var_2B4 = 1.0e37f;
        var_2B8 = 0;
        for (var_2BC = 0; var_2BC < 16; var_2BC++)
        {
            for (var_2C0 = dword_4B8600[var_2BC].unk_00; var_2C0; var_2C0 = var_2C0->unk_10)
            {
                if (var_2C0->unk_2C_8)
                {
                    var_2C4 = static_cast<type_3D32F8 *>(var_2C0);
                    if (var_2C4->get_unk_3D4() == 0)
                    {
                        var_2D4 = *var_2C4->sub_CD550();
                        RwV3dSub(&var_2D4, &var_2D4, sub_CD550());
                        var_2D8 = RwV3dDotProduct(&var_2D4, &var_2D4);
                        if (var_2D8 < var_2B4)
                        {
                            var_2B4 = var_2D8;
                            var_2B8 = var_2C4;
                        }
                    }
                }
            }
        }
        if (var_2B8 && var_2B4 < 90000.0f)
        {
            var_2DC = 0;
            sub_6B5F0("PlayAction", (type_67620 *)(var_2B8->vf_098()), 0, 0, &var_2DC, 1, true, false);
        }
        break;
    }
    case 2800:
    {
        RwReal var_2E0;
        type_3D32F8 *var_2E4;
        RwInt32 var_2E8;
        type_3D3548 *var_2EC;
        type_3D32F8 *var_2F0;
        RwV3d var_300;
        RwReal var_304;
        RwInt32 var_308;

        var_2E0 = 1.0e37f;
        var_2E4 = 0;
        for (var_2E8 = 0; var_2E8 < 16; var_2E8++)
        {
            for (var_2EC = dword_4B8600[var_2E8].unk_00; var_2EC; var_2EC = var_2EC->unk_10)
            {
                if (var_2EC->unk_2C_8)
                {
                    var_2F0 = static_cast<type_3D32F8 *>(var_2EC);
                    if (var_2F0->get_unk_3D4() == 1)
                    {
                        var_300 = *var_2F0->sub_CD550();
                        RwV3dSub(&var_300, &var_300, sub_CD550());
                        var_304 = RwV3dDotProduct(&var_300, &var_300);
                        if (var_304 < var_2E0)
                        {
                            var_2E0 = var_304;
                            var_2E4 = var_2F0;
                        }
                    }
                }
            }
        }
        if (var_2E4 && var_2E0 < 90000.0f)
        {
            var_308 = 0;
            sub_6B5F0("PlayAction", (type_67620 *)(var_2E4->vf_098()), 0, 0, &var_308, 1, true, false);
        }
        break;
    }
    case 1600:
    {
        RwInt32 *var_30C;

        var_30C = (RwInt32 *)arg_4;
        vf_190(*var_30C);
        break;
    }
    case 2100:
    {
        RwInt32 *var_310;

        var_310 = (RwInt32 *)arg_4;
        vf_0B0(*var_310, 3);
        break;
    }
    case 2200:
    {
        type_3D3548 *var_314;
        type_10F710_1A48_ev *var_318;

        var_314 = unk_4F7EB8.unk_384.sub_1B25E0(this);
        var_318 = (type_10F710_1A48_ev *)arg_4;
        if (var_314)
        {
            unk_35C[var_318->unk_0C].sub_D48D0(var_314);
            unk_364[var_318->unk_0C] = var_318->unk_08;
        }
        break;
    }
    case 2201:
    {
        type_CE070_prop *var_31C;
        type_3D3548 *var_320;
        RwFrame *var_328;

        var_31C = (type_CE070_prop *)arg_4;
        var_320 = unk_35C[var_31C->unk_0C].sub_D4910();
        if (var_320)
        {
            var_328 = var_320->get_unk_340();
            RwFrameOrthoNormalize(var_328);
            if (var_31C->unk_0D)
            {
                var_320->vf_18C(1);
                var_320->vf_190(1);
            }
        }
        vf_1FC(0, var_31C->unk_0C);
        unk_364[var_31C->unk_0C] = -1;
        break;
    }
    case 2300:
    {
        RwInt32 var_32C;
        RwInt32 var_330;
        RwReal var_334;
        type_3DAFC8 *var_33C;

        var_32C = ((type_CE070_track *)arg_4)->unk_00;
        var_330 = ((type_CE070_track *)arg_4)->unk_04;
        var_334 = ((type_CE070_track *)arg_4)->unk_08;
        switch (var_32C)
        {
        case 0:
            var_33C = vf_008();
            if (var_33C)
                var_33C->sub_1340D0(var_330 != 0, 0, var_334);
            break;
        }
        break;
    }
    case 1700:
        sub_D42D0();
        break;
    }
}

// match: ?vf_190@type_3D3548@@UAEXH@Z @ 0x000CEEB0
void type_3D3548::vf_190(RwInt32 arg_0)
{
    vf_1A0(arg_0);
    vf_1A8(arg_0);
}

// Gravity on or off; off, its vertical motion stops.
// match: ?vf_18C@type_3D3548@@UAEXH@Z @ 0x000CEEF0
void type_3D3548::vf_18C(RwInt32 arg_0)
{
    unk_28_3 = arg_0;
    if (!arg_0)
    {
        unk_D8_v.y = 0.0f;
        unk_CC.y = 0.0f;
        unk_C0.y = 0.0f;
        unk_154.y = 0.0f;
    }
}

// Environment collision on or off; turned on, it starts from where it is.
// match: ?vf_1A0@type_3D3548@@UAEXH@Z @ 0x000CEF60
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_1A0(RwInt32 arg_0)
{
    RwV3d *var_8;
    RwFrame *l4;

    if (!unk_28_5 && arg_0)
    {
        l4 = get_unk_340();
        var_8 = RwMatrixGetPos(RwFrameGetLTM(l4));
        unk_68_v = *var_8;
        unk_88_2 = 1;
        unk_14C = 0;
    }
    unk_28_5 = arg_0;
}

// match: ?vf_1A8@type_3D3548@@UAEXH@Z @ 0x000CF000
void type_3D3548::vf_1A8(RwInt32 arg_0)
{
    unk_28_2 = arg_0;
}

// match: ?vf_1A4@type_3D3548@@UAEXH@Z @ 0x000CF030
void type_3D3548::vf_1A4(RwInt32 arg_0)
{
    unk_28_21 = arg_0;
}

// Advances the material arg_0's UV animation (RpGeometryForAllMaterials'
// callback).
// match: ?sub_CF060@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x000CF060
RpMaterial *sub_CF060(RpMaterial *arg_0, void *arg_4)
{
    if (RpMatFXMaterialGetEffects(arg_0) == rpMATFXEFFECTUVTRANSFORM)
    {
        RpMaterialUVAnimAddAnimTime(arg_0, flt_429248 * deltaTime);
        RpMaterialUVAnimApplyUpdate(arg_0);
    }
    return arg_0;
}

// Advances the UV animations of the atomic arg_0's materials
// (RpClumpForAllAtomics' callback; vf_03C, binary for now, passes it).
// match: ?sub_CF0B0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000CF0B0
RpAtomic *sub_CF0B0(RpAtomic *arg_0, void *arg_4)
{
    RpGeometry *var_4;

    var_4 = arg_0->geometry;
    if (var_4)
    {
        RpGeometryForAllMaterials(var_4, sub_CF060, 0);
    }
    return arg_0;
}

// match: ?vf_03C@type_3D3548@@UAEXM@Z @ 0x000CF0E0
// The per-frame update: its performance and animations (while animated), its
// sound's position, fading and throbbing, its atomics' state (sub_CF0B0),
// the physics callback, the two props at their tags and its trigger's
// position (sub_D41A0).
void type_3D3548::vf_03C(RwReal arg_0)
{
    type_6D380 *var_8;
    RpClump *var_C;
    RwInt32 var_10;
    type_3D3548 *var_14;
    RpClump *var_18;
    RwMatrix var_60;
    RwFrame *var_68;

    if (unk_284 && unk_88_9)
    {
        var_8 = vf_090();
        if (var_8)
        {
            ((type_3D2CD0 *)var_8)->sub_6D5A0(arg_0);
        }
        vf_21C(arg_0);
    }
    unk_1C0.sub_89540(sub_CD550());
    if (unk_28_18)
    {
        sub_D3A20(arg_0);
    }
    if (unk_28_14)
    {
        vf_1EC(arg_0);
    }
    if (unk_88_0)
    {
        var_C = unk_25C.unk_08;
        if (var_C)
        {
            RpClumpForAllAtomics(var_C, sub_CF0B0, 0);
        }
    }
    if (unk_37C)
    {
        // The callback takes its two arguments too (sub_D3700 keeps them).
        ((void (*)(type_3D3548 *, RwInt32, RwInt32))unk_37C)(this, unk_374, unk_378);
    }
    for (var_10 = 0; var_10 < 2; var_10++)
    {
        var_14 = unk_35C[var_10].sub_D4910();
        if (var_14 && unk_36C[var_10] != -1)
        {
            var_18 = unk_25C.unk_08;
            if (sub_EC2D0(var_18, (RwInt32)(&var_60), unk_36C[var_10], 0, 0))
            {
                var_68 = var_14->get_unk_340();
                *RwFrameGetMatrix(var_68) = var_60;
                RwFrameUpdateObjects(var_68);
            }
        }
    }
    sub_D41A0();
}

// match: ?vf_040@type_3D3548@@UAEXM@Z @ 0x000CF2D0
void type_3D3548::vf_040(RwReal arg_0)
{
    RwInt32 var_4;

    if ((var_4 = unk_2C & 0x20) && arg_0 > 4.0f)
    {
        arg_0 = 4.0f;
    }
    vf_20C((type_D05C0 *)&unk_C0, arg_0, &unk_10C, &unk_134);
    vf_210((type_D05C0 *)&unk_C0);
    if (get_unk_340())
    {
        vf_214((type_D05C0 *)&unk_C0, get_unk_340(), arg_0);
    }
}

// match: ?vf_048@type_3D3548@@UAEXM@Z @ 0x000CF390
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_048(RwReal arg_0)
{
    RwV3d v34;
    RwV3d local_28;
    RwV3d *var_1C;
    RwReal var_18;
    RwV3d var14;
    RwReal frm_8;
    type_3D3548 *l4;

    if (unk_380_r != 0.0f)
    {
        l4 = sub_1745A0(0);
        if (l4 && l4 != this)
        {
            var_1C = (RwV3d *)l4->vf_0C4();
            RwV3dAddMacro(&var14, (RwV3d *)vf_0C4(), &unk_3C_v);
            RwV3dSubMacro(&v34, var_1C, &var14);
            var_18 = RwV3dLength(&v34);
            if (var_18 < unk_380_r)
            {
                frm_8 = unk_380_r - var_18;
                RwV3dNormalize(&v34, &v34);
                RwV3dScaleMacro(&v34, &v34, frm_8);
                RwV3dAddMacro(&local_28, &v34, var_1C);
                l4->vf_0C0(&local_28);
                l4->vf_044(arg_0);
            }
        }
    }
}

// match: ?vf_044@type_3D3548@@UAEXM@Z @ 0x000CF520
// Moves and collides it for the time step arg_0 (at most 4 for a soldier):
// unless it has not moved or turned (then the last search's results stand),
// searches the world around its frame (sub_985B0 for a soldier, else
// sub_948A0) into the flags unk_88_3 to unk_88_7 and the ground height
// unk_7C; a soldier eases its frame's height towards the ground. Sends the
// collision, ground and wall notifications asked for (unk_28_15, _24, _23),
// draws its debug line (unk_28_12), then with neither ground nor ceiling
// found drops to its last hold point (unk_28_8) or to the ground (unk_28_3),
// else keeps the point; steers its velocity (sub_D01B0) and lands or hits
// a wall (vf_1C4).
void type_3D3548::vf_044(RwReal arg_0)
{
    bool lv_5;
    RwFrame *lv_c;
    RwMatrix *lv_10;
    RwMatrix lv_50;
    RwUInt32 lv_54;
    RwReal lv_58;
    RwV3d lv_64;
    RwV3d lv_70;
    RwInt32 lv_74;
    RwInt32 lv_78;
    RwInt32 lv_7c;
    RwInt32 lv_80;
    RwInt32 lv_84;
    RwInt32 lv_8c;
    type_3DAFC8_1DDC *lv_90;
    AIData *lv_94;
    RwReal lv_cc;
    RwReal lv_d0;
    RwInt32 lv_d8[2];
    RwMatrix *lv_dc;
    RwV3d lv_e8;
    RwV3d lv_f4;
    RwV3d lv_100;
    RwV3d lv_10c;
    RwV3d *lv_110;
    RwV3d *lv_114;
    RwV3d *lv_118;
    RwV3d *lv_11c;
    RwV3d lv_128;

    lv_5 = false;
    lv_c = unk_338.unk_08;
    if (lv_c != 0) {
        lv_10 = RwFrameGetMatrix(lv_c);
        lv_50 = *lv_10;
        if ((lv_54 = unk_2C & 0x20) && arg_0 > 4.0f)
            arg_0 = 4.0f;
        lv_58 = lv_10->pos.y;
        lv_64 = RwFrameGetLTM(lv_c)->pos;
        if (unk_88_2)
            unk_68_v = lv_64;
        lv_70.x = unk_4C;
        lv_70.y = unk_48;
        lv_70.z = unk_4C;
        lv_74 = 0;
        lv_78 = 0;
        lv_7c = 0;
        lv_80 = 0;
        lv_84 = 0;
        lv_8c = lv_54 && (unk_2C & 1);
        lv_90 = vf_1C8();
        if (lv_90) {
            lv_94 = vf_120();
            if (lv_94) {
                if (!(lv_94->unk_49C & 0x840001)) {
                    lv_90->unk_54[0].unk_00 = 0;
                    lv_90->unk_54[1].unk_00 = 0;
                    lv_90->unk_54[2].unk_00 = 0;
                    lv_90->unk_54[3].unk_00 = 0;
                    lv_90->unk_54[4].unk_00 = 0;
                    lv_90->unk_54[5].unk_00 = 0;
                    lv_90->unk_54[6].unk_00 = 0;
                    lv_90->unk_54[7].unk_00 = 0;
                    lv_90->unk_2D4[0].unk_00 = 0;
                    lv_90->unk_2D4[1].unk_00 = 0;
                    lv_90->unk_2D4[2].unk_00 = 0;
                    lv_90->unk_2D4[3].unk_00 = 0;
                    lv_90 = 0;
                } else if (lv_94->is_blocked())
                    lv_8c = 1;
            } else
                lv_90 = 0;
        }
        if (((RwReal)fabs((RwReal)(unk_68 - lv_64.x))) > 0.01f || ((RwReal)fabs((RwReal)(unk_6C - lv_64.y))) > 0.01f
            || ((RwReal)fabs((RwReal)(unk_70 - lv_64.z))) > 0.01f || ((RwReal)fabs((RwReal)unk_F0)) > 0.01f
            || ((RwReal)fabs((RwReal)unk_F4)) > 0.01f || ((RwReal)fabs((RwReal)unk_F8)) > 0.01f || unk_88_2 || lv_8c
            || unk_28_7 || unk_28_25) {
            if (lv_54)
                sub_985B0(this, lv_c, &unk_3C_v, unk_50_r, &lv_74, &lv_70, &lv_cc, &lv_78, &lv_7c, &lv_80, &lv_84, lv_90,
                          !unk_88_2);
            else
                sub_948A0(this, lv_c, &unk_3C_v, unk_50_r, &lv_74, &lv_70, &lv_cc, &lv_78, &lv_7c, &lv_80, &lv_84, lv_90);
            unk_88_3 = lv_74;
            unk_88_4 = lv_78;
            unk_88_5 = lv_7c;
            unk_88_6 = lv_80;
            unk_88_7 = lv_84;
            unk_7C = lv_cc;
        } else {
            lv_74 = unk_88_3;
            lv_78 = unk_88_4;
            lv_7c = unk_88_5;
            lv_80 = unk_88_6;
            lv_84 = unk_88_7;
            lv_cc = unk_7C;
            lv_5 = true;
        }
        unk_68_v = lv_64;
        if (lv_54) {
            if (unk_88_2) {
            } else {
                lv_d0 = arg_0 * 0.5f * 0.25f;
                if (lv_d0 > 1.0f)
                    lv_d0 = 1.0f;
                lv_10->pos.y = (lv_10->pos.y - lv_58) * lv_d0 + lv_58;
                lv_64.y = lv_10->pos.y;
                RwFrameUpdateObjects(lv_c);
            }
            if (lv_74) {
                unk_DC = 0.0f;
                unk_154.y = 0.0f;
                unk_C0.y = 0.0f;
            }
        }
        unk_88_2 = 0;
        if (unk_28_15 && (lv_7c || lv_80)) {
            lv_d8[0] = lv_7c;
            lv_d8[1] = lv_80;
            sub_6B5F0("CollisionNotification", (type_67620 *)(vf_098()), 0, 0, lv_d8, 2, true, false);
            unk_28_15 = 0;
        }
        if (unk_28_24 && lv_74) {
            sub_6B5F0("GroundCollisionNotification", (type_67620 *)(vf_098()), 0, 0, 0, 0, true, false);
            unk_28_24 = 0;
        }
        if (unk_28_23 && lv_84) {
            sub_6B5F0("WallCollisionNotification", (type_67620 *)(vf_098()), 0, 0, 0, 0, true, false);
            unk_28_23 = 0;
        }
        if (unk_28_12) {
            lv_dc = RwFrameGetLTM(lv_c);
            lv_e8 = lv_dc->pos;
            lv_e8.y += 50.0f;
            lv_f4.x = 0.0f;
            lv_f4.y = -1.0f;
            lv_f4.z = 0.0f;
            if (lv_80)
                sub_1279C0(&lv_e8, &lv_f4, &lv_dc->at, 100.0f, 100.0f, 1, !lv_5);
            else
                sub_1279C0(&lv_e8, &lv_f4, &lv_dc->at, 100.0f, 100.0f, 1, 0);
        }
        lv_100 = RwFrameGetLTM(lv_c)->pos;
        if (!lv_74 && !lv_78) {
            if (unk_28_8) {
                if (unk_14C == 0) {
                    lv_10c.x = lv_64.x - lv_100.x;
                    lv_10c.y = lv_64.y - lv_100.y;
                    lv_10c.z = lv_64.z - lv_100.z;
                    RwFrameTranslate(lv_c, &lv_10c, rwCOMBINEPOSTCONCAT);
                    unk_28_7 = 1;
                } else {
                    lv_10c.x = unk_140.x - lv_100.x;
                    lv_10c.y = unk_140.y - lv_100.y;
                    lv_10c.z = unk_140.z - lv_100.z;
                    RwFrameTranslate(lv_c, &lv_10c, rwCOMBINEPOSTCONCAT);
                    lv_74 = unk_150;
                    unk_28_7 = 1;
                }
                lv_110 = &unk_D8_v;
                lv_110->x = 0.0f;
                lv_110->y = 0.0f;
                lv_110->z = 0.0f;
                lv_114 = &unk_C0;
                lv_114->x = 0.0f;
                lv_114->y = 0.0f;
                lv_114->z = 0.0f;
                lv_118 = &unk_CC;
                lv_118->x = 0.0f;
                lv_118->y = 0.0f;
                lv_118->z = 0.0f;
                lv_11c = &unk_154;
                lv_11c->x = 0.0f;
                lv_11c->y = 0.0f;
                lv_11c->z = 0.0f;
            } else {
                unk_28_7 = 1;
                if (unk_28_3) {
                    lv_128.x = 0.0f;
                    lv_128.y = 0.0f;
                    lv_128.z = 0.0f;
                    lv_128.y = lv_64.y - lv_100.y;
                    lv_128.y = -unk_DC + lv_128.y;
                    RwFrameTranslate(lv_c, &lv_128, rwCOMBINEPOSTCONCAT);
                    lv_100.y = lv_64.y;
                    unk_DC = 0.0f;
                    unk_CC.y = 0.0f;
                    unk_C0.y = 0.0f;
                    unk_154.y = 0.0f;
                }
                if (!lv_54)
                    sub_D01B0(arg_0, &lv_64, &lv_100);
            }
        } else {
            if (!lv_54)
                sub_D01B0(arg_0, &lv_64, &lv_100);
            unk_140 = lv_100;
            unk_150 = lv_74;
            unk_14C = 1;
            unk_28_7 = 0;
        }
        if (lv_74) {
            unk_28_1 = 1;
            unk_DC = 0.0f;
            unk_154.y = 0.0f;
            unk_C0.y = 0.0f;
        } else
            unk_28_1 = 0;
        if (lv_7c)
            vf_1C4(lv_80);
        unk_28_25 = 0;
        RwFrameUpdateObjects(lv_c);
    }
}

// match: ?sub_D01B0@type_3D3548@@QAEXMPAURwV3d@@0@Z @ 0x000D01B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_D01B0(RwReal arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwFrame *var_18;
    RwMatrix *var_14;
    RwReal lv_10;
    RwV3d var_C;

    var_C.x = arg_8->x - arg_4->x;
    var_C.y = arg_8->y - arg_4->y;
    var_C.z = arg_8->z - arg_4->z;
    if (fabs(RwV3dDotProductMacro(&var_C, &var_C)) > 0.0f)
    {
        if (arg_0 < 0.1f)
        {
            lv_10 = 0.0f;
        }
        else
        {
            var_18 = unk_338.unk_08;
            lv_10 = 1.0f / arg_0;
            var_14 = RwMatrixCreate();
            RwMatrixInvert(var_14, RwFrameGetLTM(var_18));
            sub_141320(&var_C, &var_C, var_14);
            RwMatrixDestroy(var_14);
            unk_D8 += var_C.x * lv_10;
            unk_DC += var_C.y * lv_10;
            unk_E0 += var_C.z * lv_10;
        }
        if (unk_D8 < 0.1f && unk_D8 > -0.1f)
        {
            unk_D8 = 0.0f;
        }
        if (unk_DC < 0.1f && unk_DC > -0.1f)
        {
            unk_DC = 0.0f;
        }
        if (unk_E0 < 0.1f && unk_E0 > -0.1f)
        {
            unk_E0 = 0.0f;
        }
    }
}

// Advances its animation (sub_CDF40), keeps its frame within 10^7 of the
// origin's height (else 10^6 down or up) and its vertical velocity within
// 10^6.
// match: ?vf_04C@type_3D3548@@UAEXM@Z @ 0x000D0390
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_04C(RwReal arg_0)
{
    RwV3d var_1C;
    RwV3d local_10;
    RwV3d *var_4;

    sub_CDF40(arg_0);
    var_4 = RwMatrixGetPos(RwFrameGetMatrix(get_unk_340()));
    if (var_4->y < -10000000.0f || var_4->y > 10000000.0f)
    {
        local_10.x = var_4->x;
        local_10.y = var_4->y < -1000000.0f ? -1000000.0f : 1000000.0f;
        local_10.z = var_4->z;
        vf_0C0(&local_10);
    }
    if (unk_DC < -1000000.0f || unk_DC > 1000000.0f)
    {
        var_1C.x = unk_D8;
        var_1C.y = 0.0f;
        var_1C.z = unk_E0;
        unk_D8_v = var_1C;
    }
}

// Its trigger volume (sub_144C80 fills unk_248 and unk_24C for it).
// match: ?vf_050@type_3D3548@@UAEXM@Z @ 0x000D04A0
void type_3D3548::vf_050(RwReal arg_0)
{
    sub_144C80(this, &unk_248, 0x20);
}

// match: ?sub_D04D0@type_3D3548@@QAEXPAURwV3d@@@Z @ 0x000D04D0
void type_3D3548::sub_D04D0(RwV3d *arg_0)
{
    unk_28_4 = 1;
    unk_D8_v = *arg_0;
}

// match: ?vf_20C@type_3D3548@@UAEXPAUtype_D05C0@@MPAURwV3d@@1@Z @ 0x000D0510
void type_3D3548::vf_20C(type_D05C0 *arg_0, RwReal arg_4, RwV3d *arg_8, RwV3d *arg_C)
{
    if (!unk_130)
    {
        arg_0->unk_00.x = arg_8->x * arg_0->unk_18.x + arg_0->unk_00.x;
        arg_0->unk_00.y = arg_8->y * arg_0->unk_18.y + arg_0->unk_00.y;
        arg_0->unk_00.z = arg_8->z * arg_0->unk_18.z + arg_0->unk_00.z;
    }
    arg_0->unk_24.x = arg_C->x * arg_0->unk_30.x + arg_0->unk_24.x;
    arg_0->unk_24.y = arg_C->y * arg_0->unk_30.y + arg_0->unk_24.y;
    arg_0->unk_24.z = arg_C->z * arg_0->unk_30.z + arg_0->unk_24.z;
}

// match: ?vf_210@type_3D3548@@UAEXPAUtype_D05C0@@@Z @ 0x000D05C0
// Raises the step arg_0's point by its height along the entity's up (bits
// 3 and 5 set, 7 clear); straight up while the entity stands upright.
void type_3D3548::vf_210(type_D05C0 *arg_0)
{
    RwFrame *var_8;
    RwMatrix *var_C;
    RwV3d var_18;
    RwMatrix var_60;
    RwV3d var_6C;

    if (unk_28_3 && unk_28_5 && !unk_28_7)
    {
        var_8 = unk_338.unk_08;
        var_C = RwFrameGetMatrix(var_8);
        if (!(var_C->up.y == 1.0f))
        {
            var_18.x = 0.0f;
            var_18.y = arg_0->unk_48;
            var_18.z = 0.0f;
            memset(&var_60, 0, sizeof(var_60));
            RwMatrixSetIdentityMacro(&var_60);
            RwMatrixInvert(&var_60, var_C);
            var_60.pos.x = var_60.pos.y = var_60.pos.z = 0.0f;
            RwMatrixUpdate(&var_60);
            sub_141320(&var_6C, &var_18, &var_60);
            RwV3dAddMacro(&arg_0->unk_00, &var_6C, &arg_0->unk_00);
        }
        else
        {
            arg_0->unk_00.y += arg_0->unk_48;
        }
    }
}

// The step's limits and axes (.rdata).
extern const RwReal flt_3CDFDC;
extern const RwReal flt_3CDDC8;
extern const RwReal flt_3D707C;
extern const RwReal flt_3CDB40;
extern const RwV3d stru_3D6F4C;
extern const RwV3d stru_3D6F58;
extern const RwV3d stru_3D6F64;

// Moves the frame arg_4 by the step arg_0 over the time arg_8: its velocity
// eased towards its limits (unk_70 set) or taken as it is, plus the step's
// one-step velocity; then its turn, each axis turned when beyond 0.001 (the
// primary animation's two matrices turned with it, the first moved back
// while its height is out of range); then the step's one-step parts cleared.
// match: ?vf_214@type_3D3548@@UAEXPAUtype_D05C0@@PAURwFrame@@M@Z @ 0x000D0760
void type_3D3548::vf_214(type_D05C0 *arg_0, RwFrame *arg_4, RwReal arg_8)
{
    RwInt32 var_8;
    RwReal var_C;
    RwV3d var_18;
    RwV3d var_24;
    RwV3d var_30;
    RwV3d var_3C;
    RwV3d var_48;
    RwV3d var_54;
    RwReal var_58;
    RwV3d var_64;
    RwV3d var_70;
    RwReal var_74;
    RwMatrix *var_78;
    RwMatrix *var_7C;
    RwV3d var_88;
    RwInt32 var_8C;
    RwMatrix var_D0;
    RwMatrix var_110;
    RwMatrix var_150;
    RwV3d var_15C;
    RwV3d var_168;

    if (arg_4)
    {
        var_8 = 0;
        if (arg_0->unk_70)
        {
            var_C = arg_8;
            arg_0->unk_0C.x = arg_0->unk_00.x;
            arg_0->unk_0C.y = arg_0->unk_00.y;
            arg_0->unk_0C.z = arg_0->unk_00.z;
            var_18 = arg_0->unk_18;
            var_18.y = 0.0f;
            var_24 = arg_0->unk_18;
            RwV3dIncrementScaledMacro(&var_24, &arg_0->unk_0C, arg_8);
            var_30 = var_24;
            if (arg_0->unk_64.x < var_24.x)
                var_24.x = (RwReal)(RwDouble)arg_0->unk_64.x;
            else if (-arg_0->unk_64.x > var_24.x)
                var_24.x = -arg_0->unk_64.x;
            if (arg_0->unk_64.y < var_24.y)
                var_24.y = (RwReal)(RwDouble)arg_0->unk_64.y;
            else if (-arg_0->unk_64.y > var_24.y)
                var_24.y = -arg_0->unk_64.y;
            if (arg_0->unk_64.z < var_24.z)
                var_24.z = (RwReal)(RwDouble)arg_0->unk_64.z;
            else if (-arg_0->unk_64.z > var_24.z)
                var_24.z = -arg_0->unk_64.z;
            var_3C.x = var_24.x - arg_0->unk_18.x;
            var_3C.y = var_24.y - arg_0->unk_18.y;
            var_3C.z = var_24.z - arg_0->unk_18.z;
            var_48.x = 0.5f * var_3C.x * arg_8 + arg_8 * arg_0->unk_18.x;
            var_48.y = 0.5f * var_3C.y * arg_8 + arg_8 * arg_0->unk_18.y;
            var_48.z = 0.5f * var_3C.z * arg_8 + arg_8 * arg_0->unk_18.z;
            var_54 = var_48;
            if (RwV3dDotProductMacro(&var_54, &var_54) > 0.0001f)
            {
                RwV3dNormalize(&var_54, &var_54);
                var_58 = arg_8 * arg_0->unk_48;
                var_64.x = var_54.x * var_58 * arg_0->unk_58.x;
                var_64.y = var_54.y * var_58 * arg_0->unk_58.y;
                var_64.z = var_54.z * var_58 * arg_0->unk_58.z;
                if (var_24.x != var_30.x)
                    var_64.x = 0.0f;
                if (var_24.y != var_30.y)
                    var_64.y = 0.0f;
                if (var_24.z != var_30.z)
                    var_64.z = 0.0f;
                RwV3dScaleMacro(&var_54, &var_64, arg_8 * 0.5f);
                if (RwV3dDotProductMacro(&var_54, &var_54) > RwV3dDotProductMacro(&var_48, &var_48))
                {
                    var_48.x = var_48.y = var_48.z = 0.0f;
                    arg_0->unk_18.x = 0.0f;
                    arg_0->unk_18.y = 0.0f;
                    arg_0->unk_18.z = 0.0f;
                }
                else
                {
                    RwV3dAddMacro(&arg_0->unk_18, &var_24, &var_64);
                    RwV3dAddMacro(&var_48, &var_48, &var_54);
                }
            }
            else
            {
                var_48.x = var_48.y = var_48.z = 0.0f;
                arg_0->unk_18 = var_24;
            }
            RwV3dIncrementScaledMacro(&var_48, &arg_0->unk_94, arg_8);
            var_70 = var_48;
            arg_8 = var_C;
        }
        else
        {
            arg_0->unk_0C.x = arg_0->unk_00.x;
            arg_0->unk_0C.y = arg_0->unk_00.y;
            arg_0->unk_0C.z = arg_0->unk_00.z;
            arg_0->unk_18.x = arg_0->unk_18.x + arg_0->unk_0C.x;
            arg_0->unk_18.y = arg_0->unk_18.y + arg_0->unk_0C.y;
            arg_0->unk_18.z = arg_0->unk_18.z + arg_0->unk_0C.z;
            var_70.x = arg_8 * arg_0->unk_18.x + arg_0->unk_94.x;
            var_70.y = arg_8 * arg_0->unk_18.y + arg_0->unk_94.y;
            var_70.z = arg_8 * arg_0->unk_18.z + arg_0->unk_94.z;
        }
        var_74 = 1.0f / arg_8;
        if (unk_28_5 && !arg_0->unk_70)
        {
            arg_0->unk_18.x = var_74 * arg_0->unk_94.x + arg_0->unk_18.x;
            arg_0->unk_18.y = var_74 * arg_0->unk_94.y + arg_0->unk_18.y;
            arg_0->unk_18.z = var_74 * arg_0->unk_94.z + arg_0->unk_18.z;
        }
        if (RwV3dDotProductMacro(&var_70, &var_70) != 0.0f)
        {
            RwFrameTranslate(arg_4, &var_70, rwCOMBINEPRECONCAT);
            var_8 = 1;
        }
        arg_0->unk_AC = var_70;
        arg_0->unk_3C.x = arg_0->unk_24.x;
        arg_0->unk_3C.y = arg_0->unk_24.y;
        arg_0->unk_3C.z = arg_0->unk_24.z;
        arg_0->unk_30.x = arg_0->unk_30.x + arg_0->unk_3C.x;
        arg_0->unk_30.y = arg_0->unk_30.y + arg_0->unk_3C.y;
        arg_0->unk_30.z = arg_0->unk_30.z + arg_0->unk_3C.z;
        var_70.x = arg_8 * arg_0->unk_30.x + arg_0->unk_A0.x;
        var_70.y = arg_8 * arg_0->unk_30.y + arg_0->unk_A0.y;
        var_70.z = arg_8 * arg_0->unk_30.z + arg_0->unk_A0.z;
        arg_0->unk_B8 = var_70;
        if (RwV3dDotProductMacro(&var_70, &var_70) != 0.0f)
        {
            var_8 = 1;
            var_78 = 0;
            var_7C = 0;
            var_88.x = 0.0f;
            var_88.y = 0.0f;
            var_88.z = 0.0f;
            var_8C = 0;
            if (unk_284)
            {
                var_78 = &var_D0;
                var_7C = &var_110;
                RwMatrixSetIdentityMacro(&var_D0);
                RwMatrixSetIdentityMacro(&var_110);
                var_D0 = unk_284->unk_100;
                var_110 = unk_284->unk_140;
                var_88.x = var_78->pos.x - var_7C->pos.x;
                var_88.y = var_78->pos.y - var_7C->pos.y;
                var_88.z = var_78->pos.z - var_7C->pos.z;
                RwMatrixSetIdentityMacro(&var_150);
                var_150.pos = var_7C->pos;
                RwMatrixUpdate(&var_150);
            }
            if (var_70.y > 0.001f || var_70.y < -0.001f)
            {
                RwFrameRotate(arg_4, &stru_3D6F58, var_70.y, rwCOMBINEPRECONCAT);
                if (var_78)
                {
                    RwMatrixRotate(var_78, &stru_3D6F58, var_70.y, rwCOMBINEPRECONCAT);
                    RwMatrixRotate(var_7C, &stru_3D6F58, var_70.y, rwCOMBINEPRECONCAT);
                    RwMatrixRotate(&var_150, &stru_3D6F58, var_70.y, rwCOMBINEPRECONCAT);
                    var_8C = 1;
                }
            }
            if (var_70.z > 0.001f || var_70.z < -0.001f)
            {
                RwFrameRotate(arg_4, &stru_3D6F64, var_70.z, rwCOMBINEPRECONCAT);
                if (var_78)
                {
                    RwMatrixRotate(var_78, &stru_3D6F64, var_70.z, rwCOMBINEPRECONCAT);
                    RwMatrixRotate(var_7C, &stru_3D6F64, var_70.z, rwCOMBINEPRECONCAT);
                    RwMatrixRotate(&var_150, &stru_3D6F64, var_70.z, rwCOMBINEPRECONCAT);
                    var_8C = 1;
                }
            }
            if (var_70.x > 0.001f || var_70.x < -0.001f)
            {
                RwFrameRotate(arg_4, &stru_3D6F4C, var_70.x, rwCOMBINEPRECONCAT);
                if (var_78)
                {
                    RwMatrixRotate(var_78, &stru_3D6F4C, var_70.x, rwCOMBINEPRECONCAT);
                    RwMatrixRotate(var_7C, &stru_3D6F4C, var_70.x, rwCOMBINEPRECONCAT);
                    RwMatrixRotate(&var_150, &stru_3D6F4C, var_70.x, rwCOMBINEPRECONCAT);
                    var_8C = 1;
                }
            }
            if (var_8C && var_78)
            {
                var_15C = var_88;
                while (1)
                {
                    sub_1414C0(&var_168, &var_88, &var_150);
                    var_78->pos = var_168;
                    RwMatrixUpdate(var_78);
                    if (var_78->pos.y < (-100000000.0f) || var_78->pos.y > 100000000.0f)
                    {
                        var_88 = var_15C;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if (var_78)
            {
                RwMatrix *var_16C;

                var_16C = &unk_284->unk_100;
                *var_16C = *var_78;
                var_16C = &unk_284->unk_140;
                *var_16C = *var_7C;
            }
        }
        if (!arg_0->unk_70 && unk_28_5 && arg_0->unk_94.y != 0.0f && arg_0->unk_4C.y == 0.0f)
        {
            arg_0->unk_00.y = var_74 * arg_0->unk_94.y * (-1.0f);
            arg_0->unk_00.x = 0.0f;
            arg_0->unk_00.z = 0.0f;
        }
        else
        {
            arg_0->unk_00.x = 0.0f;
            arg_0->unk_00.y = 0.0f;
            arg_0->unk_00.z = 0.0f;
        }
        zero_v3d(&arg_0->unk_24);
        zero_v3d(&arg_0->unk_94);
        zero_v3d(&arg_0->unk_A0);
        if (var_8)
            RwFrameUpdateObjects(arg_4);
    }
}


// Its head matrix into arg_0: its frame's, raised by half its height (the
// identity without a frame).
// match: ?vf_104@type_3D3548@@UAEXPAURwMatrixTag@@@Z @ 0x000D14C0
void type_3D3548::vf_104(RwMatrix *arg_0)
{
    RwFrame *var_4;

    if (arg_0)
    {
        var_4 = unk_338.unk_08;
        if (!var_4)
        {
            RwMatrixSetIdentity(arg_0);
        }
        else
        {
            *arg_0 = *RwFrameGetLTM(var_4);
            arg_0->pos.y += unk_48 / 2.0f;
        }
    }
}

// Its eye point into arg_0: its position raised by half its height (the
// origin without a frame).
// match: ?vf_108@type_3D3548@@UAEXPAURwV3d@@@Z @ 0x000D15C0
void type_3D3548::vf_108(RwV3d *arg_0)
{
    RwFrame *var_4;

    if (arg_0)
    {
        var_4 = unk_338.unk_08;
        if (!var_4)
        {
            arg_0->z = 0.0f;
            arg_0->y = 0.0f;
            arg_0->x = 0.0f;
        }
        else
        {
            *arg_0 = *RwMatrixGetPos(RwFrameGetLTM(var_4));
            arg_0->y += unk_48 / 2.0f;
        }
    }
}

// The line arg_4 against its ellipsoid (its radius and height, scaled by
// arg_C, around its raised position), the distance into *arg_8.
// match: ?vf_080@type_3D3548@@UAEHHPAURpIntersection@@PAMM@Z @ 0x000D1640
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D3548::vf_080(RwInt32 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwReal arg_C)
{
    RwReal var_24;
    RwReal var_20;
    RwV3d l1C;
    RpIntersection *lv_10;
    RwV3d var_C;

    lv_10 = arg_4;
    l1C = *sub_CD550();
    RwV3dAddMacro(&l1C, &unk_3C_v, &l1C);
    var_24 = arg_C * unk_4C;
    var_20 = arg_C * unk_48;
    var_C.x = 1.0f / (var_24 * var_24);
    var_C.z = var_C.x;
    var_C.y = 1.0f / (var_20 * var_20);
    return sub_9A5F0(&l1C, &var_C, lv_10, arg_8);
}

// match: ?vf_084@type_3D3548@@UAEHCPAURpIntersection@@PAMPAURwV3d@@@Z @ 0x000D16F0
// Mode 3: the line of arg_4 against its clump's atomics (the nearest hit
// within 10000 into *arg_8, its normal into *arg_C). Otherwise the sphere
// search arg_4 (a type_D1990) against them: *arg_8 gets the nearest hit's
// distance squared over the sphere's radius, clamped to 0..1, and *arg_C
// its normal. 1 on a hit.
RwInt32 type_3D3548::vf_084(RwInt8 arg_0, RpIntersection *arg_4, RwReal *arg_8, RwV3d *arg_C)
{
    RwInt32 var_8;
    RwReal var_C;
    type_D18C0 var_18;
    type_D1990 *var_24;
    RwReal var_84;

    var_8 = 0;
    if (arg_0 == 3)
    {
        *arg_8 = 10000.0f;
        var_C = 10000.0f;
        var_18.unk_00 = (RwV3d *)arg_4;
        var_18.unk_04 = arg_8;
        var_18.unk_08 = arg_C;
        if (unk_268.get_unk_08())
        {
            RpClumpForAllAtomics(unk_268.get_unk_08(), Collision_AccumulateNearestAtomicLineIntersection, &var_18);
        }
        if (*arg_8 < var_C)
        {
            var_8 = 1;
        }
    }
    else
    {
        var_24 = (type_D1990 *)arg_4;
        if (unk_268.get_unk_08())
        {
            RpClumpForAllAtomics(unk_268.get_unk_08(), sub_D1990, var_24);
        }
        if (var_24->unk_04->unk_60)
        {
            do
            {
                __m128 a = _mm_set_ss(var_24->unk_04->unk_94);
                __m128 b = _mm_sqrt_ss(a);
                _mm_store_ss(&var_84, b);
            } while (0);
            *arg_8 = var_24->unk_04->unk_94 / var_24->unk_00->radius;
            if (*arg_8 > 1.0f)
            {
                *arg_8 = 1.0f;
            }
            if (*arg_8 < 0.0f)
            {
                *arg_8 = 0.0f;
            }
            var_8 = 1;
            if (arg_C)
            {
                *arg_C = var_24->unk_04->unk_98;
            }
        }
    }
    return var_8;
}

// The line of the search arg_4 against the atomic arg_0's triangles,
// keeping the nearest hit (RpClumpForAllAtomics' callback).
// match: ?Collision_AccumulateNearestAtomicLineIntersection@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D18C0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *Collision_AccumulateNearestAtomicLineIntersection(RpAtomic *arg_0, void *arg_4)
{
    type_D18C0 *var_20;
    RpIntersection l1C;

    var_20 = (type_D18C0 *)arg_4;
    l1C.type = rpINTERSECTLINE;
    l1C.t.line.start = var_20->unk_00[0];
    l1C.t.line.end = var_20->unk_00[1];
    if (arg_0->geometry)
    {
        RpAtomicForAllIntersections(arg_0, &l1C, Collision_RecordNearestCollisionTriangleHit,
                                    var_20);
    }
    return arg_0;
}

// match: ?Collision_RecordNearestCollisionTriangleHit@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x000D1930
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *Collision_RecordNearestCollisionTriangleHit(RpIntersection *arg_0,
                                                                 RpCollisionTriangle *arg_4,
                                                                 RwReal arg_8, void *arg_C)
{
    RwReal *var_8;
    type_D18C0 *l4;

    l4 = (type_D18C0 *)arg_C;
    var_8 = l4->unk_04;
    if (arg_8 < *var_8)
    {
        *var_8 = arg_8;
        if (l4->unk_08)
        {
            *l4->unk_08 = arg_4->normal;
        }
    }
    return arg_4;
}

// match: ?sub_D1990@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D1990
// vf_084's sphere search over one atomic: its entity and matrices (the frame
// matrix, orthonormalised and inverted) and the sphere's centre go into the
// triangle search, which runs on its triangles (sub_93700).
RpAtomic *sub_D1990(RpAtomic *arg_0, void *arg_4)
{
    type_D1990 *var_4;
    RpIntersection var_20;
    type_93700 *var_24;
    type_3D3548 *var_28;
    RwFrame *var_30;
    RwMatrix *var_34;
    RwMatrix var_80;
    RwMatrix var_C0;

    var_4 = (type_D1990 *)arg_4;
    var_20.type = rpINTERSECTSPHERE;
    var_20.t.sphere = *var_4->unk_00;
    var_24 = var_4->unk_04;
    var_28 = sub_FB960(arg_0);
    var_30 = var_28->get_unk_340();
    var_34 = RwFrameGetMatrix(var_30);
    RwMatrixSetIdentityMacro(&var_80);
    RwMatrixInvert(&var_80, var_34);
    RwMatrixOrthoNormalize(&var_C0, var_34);
    var_24->unk_18 = var_34;
    var_24->unk_20 = &var_80;
    var_24->unk_1C = &var_C0;
    var_24->unk_08 = var_28;
    var_24->unk_2C = var_20.t.sphere.center;
    var_24->unk_10 = arg_0;
    var_24->unk_5C = 0;
    if (arg_0->geometry)
    {
        RpAtomicForAllIntersections(arg_0, &var_20, sub_93700, var_24);
    }
    return arg_0;
}

// match: ?Collision_DispatchAtomicIntersectionsBySelectorFlag@type_3D3548@@UAEXPAURpAtomic@@PAURpIntersection@@PAUtype_93700@@@Z @ 0x000D1B10
void type_3D3548::Collision_DispatchAtomicIntersectionsBySelectorFlag(RpAtomic *arg_0,
                                                                       RpIntersection *arg_4,
                                                                       type_93700 *arg_8)
{
    if (arg_0->geometry)
    {
        if (arg_8 && arg_8->unk_04 && arg_8->unk_04->unk_2C_5)
        {
            RpAtomicForAllIntersections(arg_0, arg_4, sub_97790, arg_8);
        }
        else
        {
            RpAtomicForAllIntersections(arg_0, arg_4, sub_93700, arg_8);
        }
    }
    else if (arg_8)
    {
        arg_8->unk_5C = 1;
    }
}

// match: ?RenderWare_ReturnObjectUnchanged@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D1B90
RpAtomic *RenderWare_ReturnObjectUnchanged(RpAtomic *arg_0, void *arg_4)
{
    return arg_0;
}

// The atomic arg_4's bounding sphere onto the atomic arg_0, its radius
// grown by 1 and scaled by flt_429250.
// match: ?Clump_CopyExpandedBoundingSphere@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D1BA0
RpAtomic *Clump_CopyExpandedBoundingSphere(RpAtomic *arg_0, void *arg_4)
{
    RpAtomic *var_4;

    var_4 = (RpAtomic *)arg_4;
    arg_0->boundingSphere = var_4->boundingSphere;
    arg_0->boundingSphere.radius = (arg_0->boundingSphere.radius + 1.0f) * flt_429250;
    return arg_0;
}

// match: ?vf_224@type_3D3548@@UAE_NPAUtype_3DF8D8@@HPAH@Z @ 0x000D1BF0
// Takes its model from the object arg_0 (kind 3): clones the model (and,
// unless arg_4, the second model: its animated parts), keeps its frame's
// matrix (or its trigger's), sets its clumps (unk_25C, unk_268), a
// collision atomic of the model's bounding sphere (unk_250), its hierarchy,
// and its sizes (from the object's box when arg_8 is given; *arg_8 tells
// whether they were set), then a sphere atomic when there is no second model
// (unk_274) and the trigger's sizes; false when the model cannot be made.
bool type_3D3548::vf_224(type_3DF8D8 *arg_0, RwInt32 arg_4, RwInt32 *arg_8)
{
    RpClump *lv_8;
    RpClump *lv_c;
    RpClump *lv_10;
    RpClump *lv_14;
    type_712B0 *lv_18;
    RwMatrix lv_60;
    RwFrame *lv_64;
    RpAtomic *lv_68;
    RwSphere lv_78;
    RpAtomic *lv_7c;
    RwInt32 lv_80;
    void *lv_84;
    RwInt32 lv_88;
    RpHAnimHierarchy *lv_8c;
    RwBBox *lv_90;
    RwReal lv_9c;
    RwReal lv_a8;
    RwReal lv_b4;
    RwV3d *lv_b8;
    RpAtomic *lv_bc;
    Trigger_B0 *lv_c0;

    lv_8 = 0;
    lv_c = 0;
    lv_10 = 0;
    lv_14 = 0;
    if (arg_8)
        *arg_8 = 0;
    lv_18 = (type_712B0 *)unk_344.unk_08;
    if (lv_18)
        unk_29C = lv_18->unk_43;
    lv_8 = ((type_3DF9C4 *)arg_0)->sub_190A10();
    if (!lv_8)
        return false;
    if (!arg_4)
        lv_c = ((type_3DF9C4 *)arg_0)->sub_190A50();
    lv_10 = RpClumpClone(lv_8);
    if (!lv_10)
        return false;
    if (lv_c) {
        lv_14 = RpClumpClone(lv_c);
        if (!lv_14)
            return false;
    }
    if (get_unk_340())
        lv_60 = *RwFrameGetMatrix(get_unk_340());
    else
        lv_60 = *(RwMatrix *)&lv_18->unk_60_m;
    lv_64 = RpClumpGetFrame(lv_10);
    if (lv_64) {
        unk_338.sub_129B10();
        unk_338.sub_129A70(lv_64);
    } else {
        lv_64 = unk_338.unk_08;
        if (!lv_64) {
            lv_64 = RwFrameCreate();
            if (lv_64) {
                RwFrameSetIdentity(lv_64);
                unk_338.sub_129A70(lv_64);
            }
        }
        if (lv_64)
            RpClumpSetFrame(lv_10, lv_64);
    }
    *RwFrameGetMatrix(lv_64) = lv_60;
    unk_140 = lv_60.pos;
    if (lv_14) {
        sub_16E100(lv_10, lv_14);
        RpClumpSetFrame(lv_14, lv_64);
    }
    unk_25C.sub_129940(0);
    unk_25C.sub_129620(lv_10);
    unk_25C.sub_129690(this);
    unk_268.sub_129940(0);
    unk_268.sub_129620(lv_14);
    if (lv_14)
        unk_268.sub_129690(this);
    lv_68 = RpAtomicCreate();
    sub_16DCD0(lv_10, &lv_78);
    lv_68->boundingSphere.center = lv_78.center;
    lv_68->boundingSphere.radius = lv_78.radius * flt_42924C;
    lv_7c = Clump_FindFirstAtomic(lv_10);
    if (lv_68)
        RpClumpForAllAtomics(lv_10, Clump_CopyExpandedBoundingSphere, lv_68);
    lv_80 = 1;
    sub_FB990(lv_68, lv_80);
    RpAtomicSetRenderCallBack(lv_68, sub_D2B70);
    if (!lv_18->unk_24_9)
        unk_28_17 = 1;
    else
        unk_28_17 = 0;
    lv_84 = lv_7c->pipeline;
    lv_68->pipeline = lv_84;
    lv_64 = sub_D3740(RpClumpGetFrame(lv_10), 0);
    RpAtomicSetFrame(lv_68, lv_64);
    sub_173320(lv_68);
    unk_250.sub_129430(lv_68);
    unk_250.sub_1294A0(this);
    if (lv_14) {
        lv_88 = 4;
        sub_16DFE0(lv_14, lv_88);
        sub_173180(lv_14);
        unk_58 = 2;
    }
    sub_79270(lv_10, 0);
    lv_8c = sub_16D970(lv_10);
    RpHAnimHierarchyAttach(lv_8c);
    if (lv_14) {
        lv_8c->flags |= rpHANIMHIERARCHYUPDATEMODELLINGMATRICES;
        if (arg_8) {
            lv_90 = ((type_3DF9C4 *)arg_0)->sub_190A90();
            if (lv_90) {
                lv_9c = ((RwReal)fabs((RwReal)(lv_90->sup.x - lv_90->inf.x))) * 0.5f;
                lv_a8 = ((RwReal)fabs((RwReal)(lv_90->sup.y - lv_90->inf.y))) * 0.5f;
                lv_b4 = ((RwReal)fabs((RwReal)(lv_90->sup.z - lv_90->inf.z))) * 0.5f;
                unk_48 = lv_a8;
                if (lv_9c > lv_b4)
                    unk_4C = lv_9c;
                else
                    unk_4C = lv_b4;
                lv_b8 = &unk_3C_v;
                lv_b8->x = 0.0f;
                lv_b8->y = 0.0f;
                lv_b8->z = 0.0f;
                unk_40 = unk_48;
                unk_50_r = unk_48 * 0.5f;
            } else
                sub_D2740();
            *arg_8 = 1;
        }
    }
    if (((type_3DF9C4 *)arg_0)->sub_1909C0()) {
        RpClumpForAllAtomics(lv_10, RenderWare_ReturnObjectUnchanged, 0);
        unk_88_0 = 1;
    }
    if (!arg_4 && !lv_14 && unk_28_17) {
        lv_bc = RpAtomicCreate();
        lv_bc->boundingSphere.center = lv_68->boundingSphere.center;
        lv_bc->boundingSphere.radius = lv_68->boundingSphere.radius / flt_42924C;
        RpAtomicSetFrame(lv_bc, RpAtomicGetFrame(lv_68));
        RpAtomicSetFlags(lv_bc, 0);
        sub_FB990(lv_bc, 4);
        sub_173320(lv_bc);
        unk_274.sub_129430(lv_bc);
        unk_274.sub_1294A0(this);
        if (arg_8) {
            sub_D2740();
            *arg_8 = 1;
        }
    }
    if (lv_18->unk_24_16) {
        lv_c0 = (Trigger_B0 *)lv_18->unk_B0;
        if (lv_c0) {
            unk_4C = lv_c0->unk_00_r;
            unk_48 = lv_c0->unk_04_r;
            unk_50 = lv_c0->unk_08;
            unk_3C_v = lv_c0->unk_0C;
        }
    }
    return true;
}

// match: ?Frame_DetachWhenOwnerDiffers@@YAPAURwFrame@@PAU1@PAX@Z @ 0x000D2300
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwFrame *Frame_DetachWhenOwnerDiffers(RwFrame *arg_0, void *arg_4)
{
    type_3D96F0 *var_C;
    type_3D3548 *bp_8;
    type_3D3548 *bp_4;

    bp_8 = (type_3D3548 *)arg_4;
    var_C = sub_FBC30(arg_0);
    bp_4 = var_C->unk_14.sub_D4910();
    if (bp_4 != bp_8)
    {
        arg_0->modelling = *RwFrameGetLTM(arg_0);
        RwFrameRemoveChild(arg_0);
    }
    return arg_0;
}

// match: ?Frame_DetachAtomicChildrenWhenOwnerDiffers@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D2370
RpAtomic *Frame_DetachAtomicChildrenWhenOwnerDiffers(RpAtomic *arg_0, void *arg_4)
{
    RwFrame *var_4;

    var_4 = RpAtomicGetFrame(arg_0);
    if (var_4)
    {
        RwFrameForAllChildren(var_4, Frame_DetachWhenOwnerDiffers, arg_4);
    }
    return arg_0;
}

// match: ?vf_228@type_3D3548@@UAE_NXZ @ 0x000D23A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_3D3548::vf_228()
{
    RpAtomic *var_14;
    RpAtomic *lv_10;
    RpAtomic *var_C;
    RpClump *bp_8;
    RpAtomic *bp_4;

    bp_4 = unk_274.unk_08;
    if (bp_4)
    {
        RpAtomicSetFrame(bp_4, 0);
        unk_274.sub_1294D0();
    }
    unk_338.sub_129A70(0);
    bp_8 = unk_268.unk_08;
    if (bp_8)
    {
        RpClumpForAllAtomics(bp_8, Frame_DetachAtomicChildrenWhenOwnerDiffers, this);
        RpClumpSetFrame(bp_8, 0);
        sub_1735A0(bp_8);
    }
    var_C = unk_250.unk_08;
    if (var_C)
    {
        lv_10 = unk_250.unk_08;
        sub_173620(lv_10);
        var_14 = unk_250.unk_08;
        RpAtomicSetFrame(var_14, 0);
        unk_250.sub_1294D0();
    }
    unk_250.sub_129430(0);
    unk_268.sub_129940(0);
    unk_25C.sub_129940(0);
    return true;
}

// match: ?Clump_ResolvePrimaryAtomic@type_3D3548@@QAEPAURpAtomic@@XZ @ 0x000D24B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *type_3D3548::Clump_ResolvePrimaryAtomic()
{
    RpClump *var_8;
    RpAtomic *l4;

    l4 = 0;
    var_8 = unk_268.unk_08;
    if (var_8)
    {
        l4 = Clump_FindFirstAtomic(var_8);
    }
    else
    {
        l4 = unk_274.unk_08;
    }
    return l4;
}

// match: ?Animation_GetMatrixArray@type_3D3548@@UAEPAURwMatrixTag@@XZ @ 0x000D2500
RwMatrix *type_3D3548::Animation_GetMatrixArray()
{
    RpHAnimHierarchy *var_4;

    var_4 = unk_284->unk_18;
    return RpHAnimHierarchyGetMatrixArray(var_4);
}

// match: ?vf_1D0@type_3D3548@@UAEXXZ @ 0x000D2530
// match: __ehhandler$?vf_1D0@type_3D3548@@UAEXXZ-0x8 @ 0x00300C90
// match: __ehhandler$?vf_1D0@type_3D3548@@UAEXXZ @ 0x00300C98
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_1D0()
{
    RwInt32 var_40;
    RwUInt16 stk_3C;
    RwInt32 ebp_38;
    RwInt32 var_34;
    RwV3d *local_30;
    RwReal stk_2C;
    RwV3d var28;
    RwInt32 l1C[4];

    local_30 = RwMatrixGetPos(RwFrameGetMatrix(get_unk_340()));
    if (!sub_F8820(local_30, unk_4C, l1C, 0))
    {
        return;
    }
    stk_2C = unk_4C * unk_4C;
    for (var_34 = l1C[0]; var_34 <= l1C[2]; var_34++)
    {
        for (ebp_38 = l1C[1]; ebp_38 <= l1C[3]; ebp_38++)
        {
            var_40 = ebp_38 * unk_4C00E8.unk_24 + var_34;
            stk_3C = unk_4C00E8.get_unk_3C(var_40);
            if (stk_3C != 0xFFFF)
            {
                RwUInt32 **var_5C = &unk_4C00E8.unk_48[stk_3C];
                RwUInt32 *stk_58 = *var_5C;
                type_3CE1FC l54(stk_58);
                while (!l54.at_end())
                {
                    type_F8350 *var_60 = unk_4C00E8.unk_2C[l54.unk_0C];
                    RwV3dSub(&var28, &var_60->unk_10, local_30);
                    if (var28.y > -75.0f && var28.y < 150.0f)
                    {
                        var28.y = 0.0f;
                        if (RwV3dDotProduct(&var28, &var28) < stk_2C)
                        {
                            var_60->unk_08 = (RwInt32)dword_4B87C8 + 30;
                        }
                    }
                    l54.sub_31A10();
                }
            }
        }
    }
}

// match: ?sub_D2740@type_3D3548@@QAEXXZ @ 0x000D2740
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_D2740()
{
    RwReal var_8;
    RpAtomic *l4;

    zero_v3d(&unk_3C_v);
    l4 = unk_250.unk_08;
    if (l4)
    {
        var_8 = l4->boundingSphere.radius / flt_42924C;
        unk_48 = var_8 * 0.5f;
        unk_4C = var_8;
        unk_40 = unk_48;
        unk_50_r = unk_48 - 40.0f;
        if (unk_50_r < 0.0f)
        {
            unk_50_r = unk_48 * 0.5f;
        }
    }
    else
    {
        unk_48 = 90.0f;
        unk_4C = 45.0f;
        unk_50_r = 80.0f;
        unk_40 = 90.0f;
    }
}

// match: ?vf_054@type_3D3548@@UAEXH@Z @ 0x000D2820
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_054(RwInt32 arg_0)
{
    RwRGBA var_8;
    RpClump *l4;

    sub_16D7F0(0x11);
    l4 = unk_25C.unk_08;
    if (l4)
    {
        var_8.red = 255;
        var_8.green = 0;
        var_8.blue = 0;
        var_8.alpha = 255;
        if (unk_28_14)
        {
            var_8.alpha = (RwUInt8)(unk_2A0 / 30.0f * 255.0f);
            dword_4B697C = 0;
            dword_4B69E0 = 0;
            unk_330 = 0;
            RpClumpForAllAtomics(l4, sub_D3D10, &var_8);
        }
        sub_D2920(l4, 0);
        if (unk_28_14)
        {
            var_8.alpha = 255;
            dword_4B697C = 0;
            dword_4B69E0 = 0;
            RpClumpForAllAtomics(l4, sub_D3EB0, &var_8);
        }
    }
    sub_16D850(0x11);
}

// match: ?sub_D2920@type_3D3548@@QAEPAURpClump@@PAU2@H@Z @ 0x000D2920
RpClump *type_3D3548::sub_D2920(RpClump *arg_0, RwInt32 arg_4)
{
    if (dword_4B69EC)
    {
        return arg_0;
    }
    sub_128E50(arg_0, arg_4);
    return arg_0;
}

// match: ?vf_1FC@type_3D3548@@UAEXPAU1@H@Z @ 0x000D2950
void type_3D3548::vf_1FC(type_3D3548 *arg_0, RwInt32 arg_4)
{
    type_3D3548 *var_4;

    if (!arg_0)
    {
        var_4 = unk_35C[arg_4].sub_D4910();
        if (var_4)
        {
            var_4->unk_334 = 0;
        }
    }
    else
    {
        arg_0->unk_334 = 1;
    }
    unk_35C[arg_4].sub_D48D0(arg_0);
}

// match: ?sub_D29C0@type_3D3548@@QAEXH@Z @ 0x000D29C0
void type_3D3548::sub_D29C0(RwInt32 arg_0)
{
    unk_28_9 = arg_0;
    sub_D2A40(dword_4B8600[9].get_unk_00());
    sub_D2A40(dword_4B8600[10].get_unk_00());
    sub_D2A40(dword_4B8600[0].get_unk_00());
    sub_D2A40(dword_4B8600[1].get_unk_00());
}

// match: ?sub_D2A40@type_3D3548@@QAEXPAU1@@Z @ 0x000D2A40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_D2A40(type_3D3548 *arg_0)
{
    RwInt32 var_8;
    type_3D3548 *l4;

    for (l4 = arg_0; l4; l4 = l4->unk_10)
    {
        if (l4->vf_120() && l4->vf_120()->get_unk_1374() == this)
        {
            var_8 = 0;
            sub_6B5F0("TargetDestroyed", (type_67620 *)(l4->vf_098()), 0, 0, &var_8, 1, true, false);
        }
    }
}

// match: ?sub_D2AD0@type_3D3548@@QAEXPAU1@H@Z @ 0x000D2AD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_D2AD0(type_3D3548 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_8;
    AIData *l4;

    if (arg_0)
    {
        l4 = arg_0->vf_120();
        if (l4 && l4->unk_49C_19 && l4->unk_1374.sub_D4910() == this)
        {
            var_8 = 0;
            sub_6B5F0("TargetHit", (type_67620 *)(arg_0->vf_098()), 0, 0, &var_8, 1, true, false);
        }
        arg_0->vf_220(this, arg_4);
    }
}

// match: ?sub_D2B70@@YAPAURpAtomic@@PAU1@@Z @ 0x000D2B70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_D2B70(RpAtomic *arg_0)
{
    RwLLLink *var_14;
    RwLLLink *lv_10;
    RpAtomic *var_C;
    RpClump *bp_8;
    type_3D3548 *bp_4;

    bp_4 = sub_FB960(arg_0);
    bp_8 = bp_4->unk_25C.unk_08;
    if (bp_8)
    {
        lv_10 = rwLinkListGetFirstLLLink(&bp_8->atomicList);
        var_14 = rwLinkListGetTerminator(&bp_8->atomicList);
        var_C = 0;
        if (lv_10 != var_14)
        {
            var_C = rwLLLinkGetData(lv_10, RpAtomic, inClumpLink);
        }
        if (var_C)
        {
            sub_122820(var_C, bp_4, 0);
        }
        else
        {
            sub_122820(arg_0, bp_4, 0);
        }
    }
    else
    {
        sub_122820(arg_0, bp_4, 0);
    }
    bp_4->vf_054(dword_4E5C74);
    return arg_0;
}

// match: ?vf_070@type_3D3548@@UAEHPAUtype_758F0@@HPAH@Z @ 0x000D2C20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D3548::vf_070(type_758F0 *arg_0, RwInt32 arg_4, RwInt32 *arg_8)
{
    RwV3d var_30;
    RwReal var_24;
    RwV3d var_20;
    RwV3d ebp_14;
    RwInt32 bp_8;
    RwInt32 bp_4;

    if (arg_8)
    {
        *arg_8 = 0;
    }
    if (arg_0 && arg_0->unk_08_p)
    {
        bp_8 = 0;
        if (!vf_00C() && !vf_008())
        {
            if (!arg_4)
            {
                return 1;
            }
            bp_8 = 1;
        }
        var_20 = arg_0->unk_08_p->unk_04;
        var_20.y += flt_3D6F7C;
        ebp_14 = *sub_CD550();
        ebp_14.y += flt_3D6F7C;
        RwV3dSub(&var_30, &ebp_14, &var_20);
        bp_4 = arg_0->unk_08_p->vf_058();
        if (bp_4 == 4 || bp_4 == 3 || bp_4 == 6)
        {
            if (RwV3dDotProduct(&var_30, &var_30) < arg_0->unk_10 * arg_0->unk_10 * 0.25f)
            {
                if (!arg_4)
                {
                    return 1;
                }
                bp_8 = 1;
            }
        }
        if (vf_00C())
        {
            ebp_14.y -= (RwDouble)unk_48;
        }
        if (RwV3dDotProduct(&var_30, &var_30) < 0.0001f)
        {
            return 1;
        }
        if (!sub_D2FC0(&var_20, &ebp_14, 0, 0, 0, 0x345A140, 1, 1, 0x180000, 1, 0)) // not an address: test flags
        {
            return 1;
        }
        if (arg_8)
        {
            *arg_8 = 1;
        }
        var_24 = ebp_14.y;
        vf_108(&ebp_14);
        var_24 = ebp_14.y - var_24;
        var_20.y += var_24;
        if (equal_v3d(&var_20, &ebp_14) ||
            !sub_D2FC0(&var_20, &ebp_14, 0, 0, 0, 0x345A140, 1, 1, 0x180000, 1, 0)) // not an address: test flags
        {
            return 1;
        }
        return bp_8;
    }
    return 1;
}

// match: ?sub_D2EB0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D2EB0
RpAtomic *sub_D2EB0(RpAtomic *arg_0, void *arg_4)
{
    dword_4B6978 = RpAtomicGetBoundingSphere(arg_0);
    return 0;
}

// match: ?sub_D2EF0@type_3D3548@@QAEPBURwSphere@@XZ @ 0x000D2EF0
const RwSphere *type_3D3548::sub_D2EF0()
{
    dword_4B6978 = 0;
    if (get_unk_264())
    {
        RpClumpForAllAtomics(get_unk_264(), sub_D2EB0, 0);
    }
    return dword_4B6978;
}

// match: ?vf_110@type_3D3548@@UAEXPAURwV3d@@PAU1@H@Z @ 0x000D2F40
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_110(RwV3d *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    RwMatrix *var_C;
    RwFrame *bp_8;
    const RwSphere *bp_4;

    bp_4 = sub_D2EF0();
    if (bp_4)
    {
        bp_8 = unk_338.unk_08;
        if (bp_8)
        {
            var_C = RwFrameGetLTM(bp_8);
            if (var_C)
            {
                sub_1414C0(arg_0, (RwV3d *)&bp_4->center, var_C);
            }
        }
    }
    else
    {
        *arg_0 = *sub_CD550();
    }
}

// match: ?sub_D2FC0@type_3D3548@@QAEHPAURwV3d@@0PAU1@PAMHHHHHHH@Z @ 0x000D2FC0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3D3548::sub_D2FC0(RwV3d *arg_0, RwV3d *arg_4, type_3D3548 *arg_8, RwReal *arg_C,
                               RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18, RwInt32 arg_1C,
                               RwInt32 arg_20, RwInt32 arg_24, RwInt32 arg_28)
{
    type_91F40 var_74;
    type_4E5D30 *var_48;
    RwInt32 loc44;
    type_4E5D30 *var_40;
    RwInt32 l3C;
    RpIntersection local_38;
    type_D31B0 l1C;

    local_38.type = rpINTERSECTLINE;
    local_38.t.line.start = *arg_0;
    local_38.t.line.end = *arg_4;
    l1C.unk_18 = 0;
    l1C.unk_08 = 1.0f;
    l1C.unk_00 = this;
    l1C.unk_04 = arg_8;
    l1C.unk_14 = sub_8F940();
    l1C.unk_10 = arg_28;
    if (arg_14)
    {
        l1C.unk_0C = arg_14;
    }
    else
    {
        l1C.unk_0C = unk_30;
    }
    if (arg_18)
    {
        for (l3C = 0; l3C < 4; l3C++)
        {
            var_40 = &dword_4E5D30[l3C];
            if (var_40->get_unk_00() && var_40->get_unk_28())
            {
                RpWorldForAllAtomicIntersections(var_40->get_unk_28(), &local_38, sub_D31B0, &l1C);
                if (!arg_10 && l1C.unk_18)
                {
                    break;
                }
            }
        }
    }
    if (arg_1C && (!arg_18 || arg_10 || (!arg_10 && !l1C.unk_18)))
    {
        for (loc44 = 0; loc44 < 4; loc44++)
        {
            var_48 = &dword_4E5D30[loc44];
            if (var_48->get_unk_00() && var_48->get_unk_28())
            {
                sub_91F40(var_48->get_unk_28(), &local_38.t.line, &var_74, arg_10, arg_20, arg_24);
                if (var_74.unk_00 && var_74.unk_04 < l1C.unk_08)
                {
                    l1C.unk_08 = var_74.unk_04;
                    l1C.unk_18 = 1;
                    if (!arg_10)
                    {
                        break;
                    }
                }
            }
        }
    }
    if (arg_C)
    {
        *arg_C = l1C.unk_08;
    }
    return l1C.unk_18;
}

// match: ?sub_D31B0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000D31B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_D31B0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10)
{
    type_D18C0 var_1C;
    RwInt32 local_10;
    RwInt32 var_C;
    type_3D3548 *bp_8;
    type_D31B0 *bp_4;

    bp_4 = (type_D31B0 *)arg_10;
    if (arg_C > bp_4->unk_08)
    {
        return arg_8;
    }
    if (sub_FB9C0(arg_8) & 8)
    {
        return arg_8;
    }
    bp_8 = sub_FB960(arg_8);
    if (bp_8 == bp_4->unk_00)
    {
        return arg_8;
    }
    if (!RWS::RpAtomicCollisionProperties::GetIsSolid(*arg_8))
    {
        return arg_8;
    }
    if (bp_8)
    {
        if (bp_8 == bp_4->unk_04)
        {
            return arg_8;
        }
        if (!bp_8->unk_28_2)
        {
            return arg_8;
        }
        if ((bp_4->unk_10 & bp_8->unk_2C) != bp_4->unk_10)
        {
            return arg_8;
        }
        if (!(bp_4->unk_0C & bp_8->unk_2C))
        {
            return arg_8;
        }
        if (bp_8->unk_54 == bp_4->unk_14)
        {
            return arg_8;
        }
        if (bp_4->unk_04)
        {
            if (bp_8->vf_200() && (void *)bp_8->vf_200() == (void *)bp_4->unk_04->vf_010())
            {
                return arg_8;
            }
            if (bp_4->unk_04->vf_200() && (void *)bp_4->unk_04->vf_200() == (void *)bp_8->vf_010())
            {
                return arg_8;
            }
            if (bp_8->vf_1F8(0) == bp_4->unk_04)
            {
                return arg_8;
            }
            if (bp_4->unk_04->vf_1F8(0) == bp_8)
            {
                return arg_8;
            }
        }
        bp_8->unk_54 = bp_4->unk_14;
        var_C = 1;
        if (bp_8->unk_58 == 2)
        {
            var_C = bp_8->vf_084(3, arg_0, &arg_C, 0);
        }
        else if (bp_8->unk_58 == 0)
        {
            var_C = bp_8->vf_080(1, arg_0, &arg_C, 1.0f);
        }
        else if (bp_8->unk_58 == 1)
        {
            local_10 = bp_8->vf_07C(1, arg_0, &arg_C, 0);
            if (local_10 != -1 && arg_C >= 0.0f)
            {
                var_C = 1;
            }
            else
            {
                var_C = 0;
            }
        }
        else if (arg_8->geometry)
        {
            var_1C.unk_04 = &arg_C;
            var_1C.unk_08 = 0;
            RpAtomicForAllIntersections(arg_8, arg_0, Collision_RecordNearestCollisionTriangleHit,
                                        &var_1C);
        }
        if (!var_C)
        {
            return arg_8;
        }
        if (arg_C < 0.0f)
        {
            return arg_8;
        }
    }
    if (arg_C < bp_4->unk_08)
    {
        bp_4->unk_08 = arg_C;
        bp_4->unk_18 = 1;
    }
    return arg_8;
}

// match: ?vf_000@type_3D3548@@UAEHPAX@Z @ 0x000D34B0
// Whether it is in view: sets unk_28_13 and returns 1. The test of its
// bounding sphere (its atomic's, or 500 around its position) against the
// main camera's six frustum planes, as the player's vf_064 makes it, follows
// the return: the compiler drops its set-up but keeps the loop. Local
// names state their slots.
RwInt32 type_3D3548::vf_000(void *arg_0)
{
    type_3D3548 *frm_24;
    RwInt32 var_20;
    RwSphere s1c;
    RpAtomic *local_c;
    RwCamera *bp_8;
    RwFrustumPlane *bp_4;

    if (dword_4B69F0) {
        unk_28_13 = 1;
        return 1;
    }
    unk_28_13 = 1;
    return 1;
    bp_8 = (RwCamera *)dword_4E5C74;
    bp_4 = bp_8->frustumPlanes;
    frm_24 = this;
    local_c = frm_24->unk_250.unk_08;
    if (local_c)
        s1c = *RpAtomicGetWorldBoundingSphere(local_c);
    else {
        s1c.center = *frm_24->sub_CD550();
        s1c.radius = 500.0f;
    }
    for (var_20 = 0; var_20 < 6; var_20++, bp_4++) {
        if (RwV3dDotProduct(&s1c.center, &bp_4->plane.normal) - bp_4->plane.distance > s1c.radius) {
            unk_28_13 = 0;
            return 0;
        }
    }
    unk_28_13 = 1;
    return 1;
}

// match: ?vf_124@type_3D3548@@UAEXM@Z @ 0x000D3580
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::vf_124(RwReal arg_0)
{
    type_3DAC58 *var_10;
    type_3DDB98 *var_C;
    type_3DA6C0 *bp_8;
    AIData *bp_4;

    bp_4 = vf_120();
    if (bp_4 && bp_4->get_unk_D14())
    {
        bp_4->unk_D20 = arg_0;
    }
    else if (vf_01C())
    {
        bp_8 = (type_3DA6C0 *)this;
        bp_8->vf_124(arg_0);
    }
    else if (vf_024())
    {
        var_C = (type_3DDB98 *)this;
        var_C->vf_124(arg_0);
    }
    else if (vf_020())
    {
        var_10 = (type_3DAC58 *)this;
        var_10->vf_124(arg_0);
    }
}

// match: ?vf_128@type_3D3548@@UAEMXZ @ 0x000D3640
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal type_3D3548::vf_128()
{
    type_3DAC58 *var_10;
    type_3DDB98 *var_C;
    type_3DA6C0 *bp_8;
    AIData *bp_4;

    bp_4 = vf_120();
    if (bp_4 && bp_4->get_unk_D14())
    {
        return bp_4->get_unk_D20();
    }
    else if (vf_01C())
    {
        bp_8 = (type_3DA6C0 *)this;
        return bp_8->vf_128();
    }
    else if (vf_024())
    {
        var_C = (type_3DDB98 *)this;
        return var_C->vf_128();
    }
    else if (vf_020())
    {
        var_10 = (type_3DAC58 *)this;
        return var_10->vf_128();
    }
    return 0.0f;
}

// match: ?sub_D3700@type_3D3548@@QAEXP6AXPAU1@@ZHH@Z @ 0x000D3700
void type_3D3548::sub_D3700(void (*arg_0)(type_3D3548 *), RwInt32 arg_4, RwInt32 arg_8)
{
    unk_37C = arg_0;
    unk_374 = arg_4;
    unk_378 = arg_8;
}

// match: ?sub_D3740@@YAPAURwFrame@@PAU1@PAX@Z @ 0x000D3740
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwFrame *sub_D3740(RwFrame *arg_0, void *arg_4)
{
    RwFrame **var_10;
    type_D37D0 var_C;
    RwFrame *bp_4;

    bp_4 = 0;
    var_C.unk_04 = 0;
    var_C.unk_00 = 0;
    RwFrameForAllChildren(arg_0, sub_D37D0, &var_C);
    if (var_C.unk_04 > 1)
    {
        bp_4 = arg_0;
    }
    else if (var_C.unk_04 == 1)
    {
        bp_4 = var_C.unk_00;
    }
    else
    {
        RwFrameForAllChildren(arg_0, sub_D3740, &bp_4);
    }
    if (arg_4)
    {
        var_10 = (RwFrame **)arg_4;
        if (bp_4)
        {
            *var_10 = bp_4;
            return 0;
        }
        return arg_0;
    }
    return bp_4;
}

// match: ?sub_D37D0@@YAPAURwFrame@@PAU1@PAX@Z @ 0x000D37D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwFrame *sub_D37D0(RwFrame *arg_0, void *arg_4)
{
    type_D37D0 *var_8;
    RwInt32 l4;

    var_8 = (type_D37D0 *)arg_4;
    l4 = 0;
    RwFrameForAllObjects(arg_0, (RwObject *(*)(RwObject *, void *))sub_16E580, &l4);
    if (l4)
    {
        var_8->unk_04++;
        var_8->unk_00 = arg_0;
    }
    return arg_0;
}

// match: ?vf_1E8@type_3D3548@@UAEXH@Z @ 0x000D3820
void type_3D3548::vf_1E8(RwInt32 arg_0)
{
    unk_28_14 = arg_0;
}

// match: ?vf_1EC@type_3D3548@@UAEXM@Z @ 0x000D3850
void type_3D3548::vf_1EC(RwReal arg_0)
{
    if (unk_88_11)
    {
        unk_2A0 += arg_0;
        if (unk_2A0 > 30.0f)
        {
            unk_2A0 = 30.0f;
            unk_88_11 = 0;
        }
    }
    else
    {
        unk_2A0 -= arg_0;
        if (unk_2A0 < 0.0f)
        {
            unk_2A0 = 0.0f;
            unk_88_11 = 1;
        }
    }
}

// match: ?sub_D3910@type_3D3548@@QAEXMH@Z @ 0x000D3910
void type_3D3548::sub_D3910(RwReal arg_0, RwInt32 arg_4)
{
    unk_2A4 = arg_0 > 0.2f ? arg_0 : 0.2f;
    unk_2A4 = unk_2A4 * 60.0f;
    unk_2A8 = 1.0f / unk_2A4;
    unk_2AC = 0.0f;
    if (arg_4)
    {
        unk_2A8 = -unk_2A8;
        unk_2AC = 1.0f;
    }
    unk_28_18 = 1;
    unk_28_12 = 0;
    unk_28_14 = 0;
}

// match: ?sub_D39F0@type_3D3548@@QAEXH@Z @ 0x000D39F0
void type_3D3548::sub_D39F0(RwInt32 arg_0)
{
    unk_2AC_i = arg_0;
    unk_28_18 = 1;
}

// match: ?sub_D3A20@type_3D3548@@QAEXM@Z @ 0x000D3A20
void type_3D3548::sub_D3A20(RwReal arg_0)
{
    unk_2A4 -= arg_0;
    if (unk_2A4 < 0.0f)
    {
        unk_2A4 = 0.0f;
    }
    unk_2AC += arg_0 * unk_2A8;
    if (unk_2AC > 1.0f)
    {
        unk_2AC = 1.0f;
    }
    else if (unk_2AC < 0.0f)
    {
        unk_2AC = 0.0f;
    }
}

// match: ?sub_D3AD0@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x000D3AD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpMaterial *sub_D3AD0(RpMaterial *arg_0, void *arg_4)
{
    RwRGBA *var_8;
    RwRGBA *l4;

    l4 = (RwRGBA *)arg_4;
    var_8 = RpMaterialGetColor(arg_0);
    byte_4B69B0[dword_4B69E0++] = var_8->alpha;
    var_8->alpha = l4->alpha;
    RpMaterialSetColor(arg_0, var_8);
    return arg_0;
}

// match: ?sub_D3B30@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D3B30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_D3B30(RpAtomic *arg_0, void *arg_4)
{
    RwUInt32 var_8;
    RpGeometry *l4;

    l4 = RpAtomicGetGeometry(arg_0);
    var_8 = RpGeometryGetFlags(l4);
    dword_4B6898[dword_4B697C++] = var_8;
    var_8 |= rpGEOMETRYMODULATEMATERIALCOLOR;
    RpGeometrySetFlags(l4, var_8);
    RpGeometryForAllMaterials(RpAtomicGetGeometry(arg_0), sub_D3AD0, arg_4);
    return arg_0;
}

// match: ?sub_D3BA0@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x000D3BA0
RpMaterial *sub_D3BA0(RpMaterial *arg_0, void *arg_4)
{
    RwRGBA *var_4;

    var_4 = RpMaterialGetColor(arg_0);
    var_4->alpha = byte_4B69B0[dword_4B69E0++];
    RpMaterialSetColor(arg_0, var_4);
    return arg_0;
}

// match: ?sub_D3BE0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D3BE0
RpAtomic *sub_D3BE0(RpAtomic *arg_0, void *arg_4)
{
    RpGeometry *var_4;

    var_4 = RpAtomicGetGeometry(arg_0);
    RpGeometrySetFlags(var_4, dword_4B6898[dword_4B697C++]);
    RpGeometryForAllMaterials(RpAtomicGetGeometry(arg_0), sub_D3BA0, arg_4);
    return arg_0;
}

// match: ?sub_D3C30@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x000D3C30
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpMaterial *sub_D3C30(RpMaterial *arg_0, void *arg_4)
{
    RwRGBA *var_8;
    RwRGBA *l4;

    l4 = (RwRGBA *)arg_4;
    var_8 = RpMaterialGetColor(arg_0);
    byte_4B6980[dword_4B69E0++] = var_8->red;
    byte_4B6948[dword_4B69E0++] = var_8->green;
    byte_4B6918[dword_4B69E0++] = var_8->blue;
    byte_4B69B0[dword_4B69E0++] = var_8->alpha;
    var_8->red = l4->red;
    var_8->green = l4->green;
    var_8->blue = l4->blue;
    var_8->alpha = l4->alpha;
    RpMaterialSetColor(arg_0, var_8);
    return arg_0;
}

// match: ?sub_D3D10@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D3D10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_D3D10(RpAtomic *arg_0, void *arg_4)
{
    RpMaterial *var_1C;
    RwTexture *var_18;
    RwInt32 var_14;
    RwUInt32 lv_10;
    RwInt32 var_C;
    type_3D3548 *bp_8;
    RpGeometry *bp_4;

    bp_4 = RpAtomicGetGeometry(arg_0);
    lv_10 = RpGeometryGetFlags(bp_4);
    dword_4B6898[dword_4B697C++] = lv_10;
    lv_10 |= rpGEOMETRYMODULATEMATERIALCOLOR;
    RpGeometrySetFlags(bp_4, lv_10);
    var_C = RpGeometryGetNumMaterials(bp_4);
    bp_8 = sub_FB960(arg_0);
    for (var_14 = 0; var_14 < var_C; var_14++)
    {
        var_1C = RpGeometryGetMaterial(bp_4, var_14);
        var_18 = RpMaterialGetTexture(var_1C);
        RpMaterialSetTexture(var_1C, 0);
        bp_8->unk_2B0[bp_8->unk_330] = var_18;
        bp_8->unk_2F0[bp_8->unk_330] = var_1C;
        bp_8->unk_330++;
    }
    RpGeometryForAllMaterials(RpAtomicGetGeometry(arg_0), sub_D3C30, arg_4);
    return arg_0;
}

// match: ?sub_D3E10@@YAPAURpMaterial@@PAU1@PAX@Z @ 0x000D3E10
RpMaterial *sub_D3E10(RpMaterial *arg_0, void *arg_4)
{
    RwRGBA *var_4;

    var_4 = RpMaterialGetColor(arg_0);
    var_4->red = byte_4B6980[dword_4B69E0++];
    var_4->green = byte_4B6948[dword_4B69E0++];
    var_4->blue = byte_4B6918[dword_4B69E0++];
    var_4->alpha = byte_4B69B0[dword_4B69E0++];
    RpMaterialSetColor(arg_0, var_4);
    return arg_0;
}

// match: ?sub_D3EB0@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x000D3EB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_D3EB0(RpAtomic *arg_0, void *arg_4)
{
    RwInt32 var_1C;
    RpMaterial *var_18;
    RwInt32 var_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    type_3D3548 *bp_8;
    RpGeometry *bp_4;

    bp_4 = RpAtomicGetGeometry(arg_0);
    RpGeometrySetFlags(bp_4, dword_4B6898[dword_4B697C++]);
    RpGeometryForAllMaterials(RpAtomicGetGeometry(arg_0), sub_D3E10, arg_4);
    lv_10 = 0;
    var_C = RpGeometryGetNumMaterials(bp_4);
    bp_8 = sub_FB960(arg_0);
    for (var_14 = 0; var_14 < var_C; var_14++)
    {
        var_18 = RpGeometryGetMaterial(bp_4, var_14);
        for (var_1C = 0; var_1C < bp_8->unk_330 && !lv_10; var_1C++)
        {
            if (var_18 == bp_8->unk_2F0[var_1C])
            {
                RpMaterialSetTexture(var_18, bp_8->unk_2B0[var_1C]);
                lv_10 = 1;
            }
        }
    }
    return arg_0;
}

// match: ?sub_D3FB0@type_3D3548@@QAEXPBDPAXPAUtype_3DF8D8_04@@@Z @ 0x000D3FB0
void type_3D3548::sub_D3FB0(const RwChar *arg_0, void *arg_4, type_3DF8D8_04 *arg_8)
{
    if (arg_4)
    {
        return;
    }
    sub_19A750("***ERROR: Unable to create %s object because clump mesh %x,%x was not loaded or streamed!",
               arg_0, arg_8->unk_00, arg_8->unk_04);
}

// match: ?sub_D3FF0@type_3D3548@@QAEXPAU1@@Z @ 0x000D3FF0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_D3FF0(type_3D3548 *arg_0)
{
    RwMatrix *var_30;
    RwFrame *var_2C;
    RwV3d var_28;
    RwV3d lcl_1C;
    RwV3d ebp_10;
    RwReal l4;

    if (unk_38C <= 0)
    {
        lcl_1C = *sub_CD550();
        if (vf_00C())
        {
            lcl_1C.y -= 120.0f;
        }
        ebp_10 = *vf_0C8();
        ebp_10.y = 0.0f;
        l4 = RwV3dLength(&ebp_10);
        if (l4 > 2.0f)
        {
            if (unk_2C & 0x40080) // not an address: entity kind bits
            {
                var_28 = ebp_10;
            }
            else
            {
                var_2C = get_unk_340();
                var_30 = RwFrameGetLTM(var_2C);
                sub_141320(&var_28, &ebp_10, var_30);
            }
            RwV3dNormalize(&var_28, &var_28);
            unk_390.v = var_28;
        }
        else
        {
            unk_390.v = *sub_CD5A0();
        }
        unk_39C.v = lcl_1C;
        unk_38C = 0;
    }
    unk_38C++;
}

// match: ?sub_D4170@type_3D3548@@QAEXPAU1@@Z @ 0x000D4170
void type_3D3548::sub_D4170(type_3D3548 *arg_0)
{
    unk_38C--;
}

// match: ?sub_D41A0@type_3D3548@@QAEXXZ @ 0x000D41A0
void type_3D3548::sub_D41A0()
{
    RwV3d var_C;
    RwV3d var_18;

    if (unk_38C > 0)
    {
        var_18 = *sub_CD550();
        if (vf_00C())
        {
            var_18.y -= 120.0f;
        }
        RwV3dSub(&var_C, &var_18, &unk_39C.v);
        var_C.y = 0.0f;
        if (RwV3dDotProduct(&var_C, &var_C) > dword_4275C8 * dword_4275C8)
        {
            RwV3dNormalize(&unk_390.v, &var_C);
            unk_39C.v = var_18;
        }
    }
}

// match: ?sub_D4290@type_3D3548@@QAEPAURwV3d@@XZ @ 0x000D4290
RwV3d *type_3D3548::sub_D4290()
{
    return &unk_39C.v;
}

// match: ?sub_D42B0@type_3D3548@@QAEPAURwV3d@@XZ @ 0x000D42B0
RwV3d *type_3D3548::sub_D42B0()
{
    return &unk_390.v;
}

// match: ?sub_D42D0@type_3D3548@@QAEXXZ @ 0x000D42D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3D3548::sub_D42D0()
{
    type_75600 var_124;
    type_4E5D30 *local_F4;
    RwReal local_F0;
    RwV3d varEC;
    RpIntersection var_24;
    RwInt32 var_8;
    RwInt32 l4;

    varEC.x = 200.0f;
    varEC.y = 50.0f;
    varEC.z = 200.0f;
    l4 = 0;
    type_93DF0 fp_E0;
    var_24.type = rpINTERSECTSPHERE;
    var_24.t.sphere.center = *RwMatrixGetPos(RwFrameGetLTM(get_unk_340()));
    var_24.t.sphere.center.y -= 50.0f;
    var_24.t.sphere.radius = varEC.x;
    local_F0 = var_24.t.sphere.radius * var_24.t.sphere.radius;
    fp_E0.unk_6C = 0;
    fp_E0.unk_24 = local_F0;
    fp_E0.unk_20 = 0;
    fp_E0.unk_18 = 0;
    fp_E0.unk_04 = this;
    fp_E0.unk_14 = get_unk_340();
    fp_E0.unk_0C = 0;
    fp_E0.unk_08 = 0;
    fp_E0.unk_60 = 0;
    fp_E0.unk_64 = 0;
    fp_E0.unk_7C = 0;
    fp_E0.unk_28 = 0.0f;
    fp_E0.unk_48 = unk_50_r;
    fp_E0.unk_50 = &l4;
    fp_E0.unk_58 = 0;
    fp_E0.unk_54 = 0;
    fp_E0.unk_70 = sub_8F940();
    var_8 = 0;
    for (var_8 = 0; var_8 < 4; var_8++)
    {
        local_F4 = &dword_4E5D30[var_8];
        if (local_F4->get_unk_00() && local_F4->get_unk_28())
        {
            RpWorldForAllAtomicIntersections(local_F4->get_unk_28(), &var_24, sub_D45F0, &fp_E0);
        }
    }
    if (fp_E0.unk_28 != 0.0f && fp_E0.unk_08)
    {
        var_124.unk_00_w = 0;
        var_124.unk_02_w = 1;
        if ((unk_2C & 7) == 2)
        {
            var_124.unk_08 = 0x202;
        }
        else
        {
            var_124.unk_08 = 0x201;
        }
        var_124.unk_04 = 0;
        var_124.unk_14 = 0;
        var_124.unk_18 = 0;
        var_124.unk_0C = this;
        var_124.unk_10 = unk_2C;
        var_124.unk_28 = vf_1F0();
        var_124.unk_2C = vf_1F4();
        var_124.unk_24 = fp_E0.unk_08->vf_07C(2, &var_24, 0, 0);
        fp_E0.unk_08->vf_064(&var_124);
        fp_E0.unk_08->unk_1C0.sub_8A980(&dword_4AF030, this, 0, fp_E0.unk_08->sub_CD550(), 0, 0);
    }
}

// match: ?sub_D45F0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000D45F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_D45F0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10)
{
    RwReal stk_4C;
    RwV3d local_48;
    RwReal p3C;
    const RwSphere *var_38;
    RwReal l34;
    type_3D3548 *var30;
    RwReal ebp_2C;
    RwV3d lcl_28;
    RwV3d *ebp_1C;
    RwV3d l18;
    const RwSphere *var_C;
    type_93DF0 *bp_8;
    type_3D3548 *bp_4;

    if (sub_FB9C0(arg_8) & 8)
    {
        return arg_8;
    }
    bp_8 = (type_93DF0 *)arg_10;
    bp_4 = sub_FB960(arg_8);
    if (bp_8->unk_04 && bp_4 && bp_8->unk_04 != bp_4 && bp_4->unk_28_2)
    {
        if (cmp_unk_2C(bp_8->unk_04, bp_4) || bp_8->unk_04->vf_024())
        {
            var30 = bp_8->unk_04;
            var_C = RpAtomicGetWorldBoundingSphere(arg_8);
            ebp_1C = RwMatrixGetPos(RwFrameGetMatrix(bp_8->unk_04->get_unk_340()));
            var_38 = var_C;
            RwV3dSub(&l18, &var_38->center, ebp_1C);
            p3C = RwV3dLength(&l18) - var_C->radius;
            if (bp_8->unk_08 && p3C * p3C > bp_8->unk_28 && bp_8->unk_28 != 0.0f)
            {
                return arg_8;
            }
            RwV3dNormalize(&local_48, RwMatrixGetAt(RwFrameGetMatrix(var30->get_unk_340())));
            RwV3dNormalize(&lcl_28, &l18);
            stk_4C = RwV3dDotProduct(&local_48, &lcl_28);
            l34 = atanf(var_C->radius / RwV3dLength(&l18)) + 0.610865235f; // 35 degrees
            ebp_2C = acosf(0.99999f > (stk_4C > -0.99999f ? stk_4C : -0.99999f)
                               ? (stk_4C > -0.99999f ? stk_4C : -0.99999f)
                               : 0.99999f);
            if (ebp_2C > l34)
            {
                return arg_8;
            }
            bp_8->unk_08 = bp_4;
            bp_8->unk_10 = arg_8;
            bp_8->unk_28 = p3C * p3C;
        }
    }
    return arg_8;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?vf_008@type_3D3548@@UAEPAUtype_3DAFC8@@XZ (folded into `return 0` at 0x1E4CB0)
type_3DAFC8 *type_3D3548::vf_008()
{
    return 0;
}

// ?vf_00C@type_3D3548@@UAEPAUtype_10F710@@XZ (folded into `return 0` at 0x1E4CB0)
type_10F710 *type_3D3548::vf_00C()
{
    return 0;
}

// ?vf_010@type_3D3548@@UAEPAUtype_3DBC78@@XZ (folded into `return 0` at 0x1E4CB0)
type_3DBC78 *type_3D3548::vf_010()
{
    return 0;
}

// ?vf_014@type_3D3548@@UAEPAUtype_3DC048@@XZ (folded into `return 0` at 0x1E4CB0)
type_3DC048 *type_3D3548::vf_014()
{
    return 0;
}

// ?vf_018@type_3D3548@@UAEPAUtype_3DC378@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_3DC378 *type_3D3548::vf_018()
{
    return 0;
}

// ?vf_01C@type_3D3548@@UAEPAUtype_3DA6C0@@XZ (folded into `return 0` at 0x1E4CB0)
type_3DA6C0 *type_3D3548::vf_01C()
{
    return 0;
}

// ?vf_020@type_3D3548@@UAEPAUtype_3DAC58@@XZ (folded into `return 0` at 0x1E4CB0)
type_3DAC58 *type_3D3548::vf_020()
{
    return 0;
}

// ?vf_024@type_3D3548@@UAEPAUtype_3DDB98@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_3DDB98 *type_3D3548::vf_024()
{
    return 0;
}

// ?vf_028@type_3D3548@@UAEPAUtype_3DC9B0@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_3DC9B0 *type_3D3548::vf_028()
{
    return 0;
}

// ?vf_02C@type_3D3548@@UAEPAUtype_3DE0E0@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_3DE0E0 *type_3D3548::vf_02C()
{
    return 0;
}

// ?vf_030@type_3D3548@@UAEPAUtype_3DE350@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_3DE350 *type_3D3548::vf_030()
{
    return 0;
}

// ?vf_034@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_034()
{
    return 0;
}

// ?vf_038@type_3D3548@@UAEXM@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_038(RwReal arg_0)
{
}

// ?vf_060@type_3D3548@@UAEHPAU1@@Z (folded into `return 1` at 0x1F5A00)
RwInt32 type_3D3548::vf_060(type_3D3548 *arg_0)
{
    return 1;
}

// ?vf_064@type_3D3548@@UAEHPAUtype_75600@@@Z (folded into `return 1` at 0x1F5A00)
RwInt32 type_3D3548::vf_064(struct type_75600 *arg_0)
{
    return 1;
}

// ?vf_068@type_3D3548@@UAEHPAUtype_758F0@@@Z (folded into `return 1` at 0x1F5A00)
RwInt32 type_3D3548::vf_068(struct type_758F0 *arg_0)
{
    return 1;
}

// ?vf_06C@type_3D3548@@UAEHPAU1@@Z (folded into `return 1` at 0x1F5A00)
RwInt32 type_3D3548::vf_06C(type_3D3548 *arg_0)
{
    return 1;
}

// ?vf_078@type_3D3548@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3D3548::vf_078()
{
}

// ?vf_088@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_088(RwInt32 arg_0)
{
}

// ?vf_090@type_3D3548@@UAEPAUtype_6D380@@XZ (folded into `return 0` at 0x1E4CB0)
struct type_6D380 *type_3D3548::vf_090()
{
    return 0;
}

// ?vf_094@type_3D3548@@UAEXI@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_094(RwUInt32 arg_0)
{
}

// ?vf_098@type_3D3548@@UAEPAUtype_3D2E7C@@XZ (folded into `return 0` at 0x1E4CB0)
type_3D2E7C *type_3D3548::vf_098()
{
    return 0;
}

// ?vf_09C@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_09C()
{
    return 0;
}

// ?vf_0A0@type_3D3548@@UAEXI@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_0A0(RwUInt32 arg_0)
{
}

// ?vf_0A4@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_0A4(RwInt32 arg_0)
{
}

// ?vf_0A8@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_0A8()
{
    return 0;
}

// ?vf_0AC@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_0AC()
{
    return 0;
}

// ?vf_0B4@type_3D3548@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3D3548::vf_0B4()
{
}

// ?vf_0B8@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_0B8(RwInt32 arg_0)
{
}

// ?vf_0DC@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_0DC()
{
    return 0;
}

// ?vf_0E0@type_3D3548@@UAEPAEXZ (folded into `return 0` at 0x1E4CB0)
RwUInt8 *type_3D3548::vf_0E0()
{
    return 0;
}

// ?vf_0F0@type_3D3548@@UAEPACXZ (folded into `return 0` at 0x1E4CB0)
RwInt8 *type_3D3548::vf_0F0()
{
    return 0;
}

// ?vf_0F4@type_3D3548@@UAEPAUSplinePath@@XZ (folded into `return 0` at 0x1E4CB0)
struct SplinePath *type_3D3548::vf_0F4()
{
    return 0;
}

// ?vf_0F8@type_3D3548@@UAEXM@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_0F8(RwReal arg_0)
{
}

// ?vf_118@type_3D3548@@UAEPAU1@XZ (folded into `return 0` at 0x1E4CB0)
type_3D3548 *type_3D3548::vf_118()
{
    return 0;
}

// ?vf_11C@type_3D3548@@UAEXPAU1@@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_11C(type_3D3548 *arg_0)
{
}

// ?vf_120@type_3D3548@@UAEPAUAIData@@XZ (folded into `return 0` at 0x1E4CB0)
AIData *type_3D3548::vf_120()
{
    return 0;
}

// ?vf_12C@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_12C(RwInt32 arg_0)
{
}

// ?vf_138@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_138()
{
    return 0;
}

// ?vf_13C@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_13C()
{
    return 0;
}

// ?vf_140@type_3D3548@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3D3548::vf_140()
{
}

// ?vf_15C@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_15C()
{
    return 0;
}

// ?vf_174@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_174()
{
    return 0;
}

// ?vf_178@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_178(RwInt32 arg_0)
{
}

// ?vf_180@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_180(RwInt32 arg_0)
{
}

// ?vf_1AC@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_1AC(RwInt32 arg_0)
{
}

// ?vf_1B0@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_1B0(RwInt32 arg_0)
{
}

// ?vf_1B4@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_1B4(RwInt32 arg_0)
{
}

// ?vf_1C4@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_1C4(RwInt32 arg_0)
{
}

// ?vf_1C8@type_3D3548@@UAEPAUtype_3DAFC8_1DDC@@XZ (folded into `return 0` at 0x1E4CB0)
type_3DAFC8_1DDC *type_3D3548::vf_1C8()
{
    return 0;
}

// ?vf_1CC@type_3D3548@@UAEXH@Z (folded into the empty body at 0x15FB30)
void type_3D3548::vf_1CC(RwInt32 arg_0)
{
}

// ?vf_1DC@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_1DC()
{
    return 0;
}

// ?vf_1E4@type_3D3548@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3D3548::vf_1E4()
{
    return 0;
}

// ?vf_200@type_3D3548@@UAEPAU1@XZ (folded into `return 0` at 0x1E4CB0)
type_3D3548 *type_3D3548::vf_200()
{
    return 0;
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ??3type_3D3548@@SAXPAX@Z (folded into the empty debug print at 0x19A750)
void type_3D3548::operator delete(void *arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_0BC@type_3D3548@@UAEHXZ (folded into 0x9E030)
RwInt32 type_3D3548::vf_0BC()
{
    return -1;
}

// ?vf_0E8@type_3D3548@@UAEHXZ (folded into 0x9E030)
RwInt32 type_3D3548::vf_0E8()
{
    return -1;
}

// ?vf_0EC@type_3D3548@@UAEXHH@Z (folded into 0x73D90)
void type_3D3548::vf_0EC(RwInt32 arg_0, RwInt32 arg_4)
{
}

// ?vf_100@type_3D3548@@UAEMXZ (folded into 0x73B80)
RwReal type_3D3548::vf_100()
{
    return 1.0f;
}

// ?vf_114@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_114()
{
    return 0.0f;
}

// ?vf_130@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_130()
{
    return 0.0f;
}

// ?vf_144@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_144()
{
    return 0.0f;
}

// ?vf_148@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_148()
{
    return 0.0f;
}

// ?vf_14C@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_14C()
{
    return 0.0f;
}

// ?vf_150@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_150()
{
    return 0.0f;
}

// ?vf_154@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_154()
{
    return 0.0f;
}

// ?vf_158@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_158()
{
    return 0.0f;
}

// ?vf_160@type_3D3548@@UAEHXZ (folded into 0x9E030)
RwInt32 type_3D3548::vf_160()
{
    return -1;
}

// ?vf_164@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_164()
{
    return 0.0f;
}

// ?vf_168@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_168()
{
    return 0.0f;
}

// ?vf_16C@type_3D3548@@UAEHHH@Z (folded into 0x18F420)
RwInt32 type_3D3548::vf_16C(RwInt32 arg_0, RwInt32 arg_4)
{
    return 1;
}

// ?vf_17C@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_17C()
{
    return 0.0f;
}

// ?vf_1E0@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_1E0()
{
    return 0.0f;
}

// ?vf_1F0@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_1F0()
{
    return 0.0f;
}

// ?vf_1F4@type_3D3548@@UAEMXZ (folded into 0x73BC0)
RwReal type_3D3548::vf_1F4()
{
    return 0.0f;
}

// ?vf_218@type_3D3548@@UAEXHHH@Z (folded into 0x73D80)
void type_3D3548::vf_218(RwInt32 arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
}

// ?vf_220@type_3D3548@@UAEXPAU1@H@Z (folded into 0x73D90)
void type_3D3548::vf_220(struct type_3D3548 *arg_0, RwInt32 arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_05C@type_3D3548@@UAEXXZ (folded into 0x1C06A0)
void type_3D3548::vf_05C()
{
        unk_35C[0].sub_D48D0(0);
        unk_364[0] = -1;
    }

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?vf_0C8@type_3D3548@@UAEPAURwV3d@@XZ (folded into 0xB7530)
struct RwV3d * type_3D3548::vf_0C8()
{
    return (RwV3d *)(&unk_D8);
}
