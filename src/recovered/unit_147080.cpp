// The vehicles: their physics bodies (type_3DBC78_450), the vehicle class
// type_3DBC78 and its methods.

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

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DBC18
extern const RwReal flt_3DBC18 = 16.666666f;
// 0x00429D04
RwReal dword_429D04 = 0.52f;
// 0x00429D08
RwReal flt_429D08 = 0.8f;
// 0x00429D0C
RwReal flt_429D0C = 0.5f;
// 0x00429D10
RwReal flt_429D10 = 3.0f;
// 0x00429D14
RwReal flt_429D14 = 0.95f;
// 0x00429D18
RwReal flt_429D18 = 0.03f;
// 0x00429D1C
RwReal flt_429D1C = 0.09f;
// 0x00429D20
RwReal flt_429D20 = 0.0005f;
// 0x00429D24
RwReal flt_429D24 = 0.7f;
// 0x00429D28
RwReal flt_429D28 = -1.1055555f;
// 0x00429D2C
RwReal flt_429D2C = 1.0f;
// 0x00429D30
RwReal flt_429D30 = 100.0f;
// 0x00429D34
RwReal flt_429D34 = 1.0f;
// 0x00429D38
RwReal flt_429D38 = 10.0f;
// 0x00429D3C
RwReal dword_429D3C = 0.7f;
// 0x00429D40
RwReal dword_429D40 = 0.1f;
// 0x00429D44
RwReal flt_429D44 = 0.8f;
// 0x00429D48
RwReal flt_429D48 = 0.2f;
// 0x00429D4C
RwReal flt_429D4C = 0.2f;
// 0x00429D50
RwReal flt_429D50 = 0.9f;
// 0x00429D54
RwReal flt_429D54 = 2.0f;
// 0x00429D58
RwReal flt_429D58 = -1.1055555f;
// 0x00429D5C
RwReal flt_429D5C = 0.01f;
// 0x00429D60
RwReal flt_429D60 = 0.75f;
// 0x00429D64
RwReal flt_429D64 = 100.0f;
// 0x00429D68
RwReal flt_429D68 = 55.0f;
// 0x00429D6C
RwReal flt_429D6C = 2.0f;
// 0x00429D70
RwReal flt_429D70 = 1.0f;
// 0x00429D74
RwInt32 dword_429D74 = 1;
// 0x00429D78
RwReal flt_429D78 = 10.0f;
// 0x00429D7C
RwReal flt_429D7C = 0.65f;
// 0x00429D80
RwReal flt_429D80 = 0.35f;
// 0x00429D84
RwReal flt_429D84 = 0.5f;
// 0x00429D88
RwReal flt_429D88 = 0.766f;
// 0x00429D8C
RwInt32 dword_429D8C = 1;
// 0x00429D90
RwV3d dword_429D90 = { 0.0f, 1.0f, 0.0f };
// 0x00429D9C
RwReal flt_429D9C = 0.8660254f;
// 0x00429DA0
RwReal flt_429DA0 = 2.0f;
// 0x00429DA4
RwReal flt_429DA4 = -75.0f;
// 0x00429DA8
RwReal flt_429DA8 = 160.0f;
// 0x00429DAC
RwReal flt_429DAC = 50.0f;
// 0x00429DB0
RwReal dword_429DB0 = 130.0f;
// 0x00429DB4
RwReal flt_429DB4 = 1.0f;
// 0x00429DB8
RwReal flt_429DB8 = 2.8f;
// 0x00429DBC
RwReal dword_429DBC = 100.0f;
// 0x00429DC0
RwReal dword_429DC0 = -50.0f;
// 0x00429DC4
RwReal dword_429DC4 = 400.0f;
// 0x00429DC8
RwReal dword_429DC8 = 700.0f;
// 0x00429DCC
RwReal flt_429DCC = 0.25f;
// 0x00429DD0
RwReal dword_429DD0 = 40.0f;
// 0x00429DD4
RwReal flt_429DD4 = 5.0f;
// 0x00429DD8
RwReal flt_429DD8 = 0.9330127f;
// 0x00429DDC
RwReal flt_429DDC = 0.92f;
// 0x00429DE0
RwReal flt_429DE0 = 0.86f;
// 0x00429DE4
RwReal flt_429DE4 = 2.0f;
// 0x004D31B0
#ifdef CODFH_SP // static: single player loads unk_2A0 before clearing it, so it cannot alias a field (SP 0xF42F3)
static
#endif
RwInt32 dword_4D31B0;
// 0x004D50F8
RwInt32 dword_4D50F8;
// 0x004D50FC
RwReal flt_4D50FC;
// 0x004D5104
RwReal flt_4D5104;
// 0x004D5108
type_91F40 dword_4D5108;
// 0x004D5134
type_91F40 dword_4D5134;
// 0x004D5164
RwInt32 dword_4D5164;
// 0x004D5168
RwReal dword_4D5168;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DBC18@@3MB @ 0x003DBC18
// match: __real@46610000 @ 0x003DBC1C
// match: __real@40200000 @ 0x003DBC20
// match: __real@3eae147b @ 0x003DBC24
// match: __real@44c80000 @ 0x003DBC28
// match: __real@3ea30eac @ 0x003DBC2C
// match: __real@c3020000 @ 0x003DBC30
// match: ??_C@_0BF@JKKDHJEK@VehicleHardCollision?$AA@ @ 0x003DBC34
// match: __real@45070000 @ 0x003DBC4C
// match: __real@3ca3d70a @ 0x003DBC50
// match: __real@3eaa7efa @ 0x003DBC54
// match: ?dword_429D04@@3MA @ 0x00429D04
// match: ?flt_429D08@@3MA @ 0x00429D08
// match: ?flt_429D0C@@3MA @ 0x00429D0C
// match: ?flt_429D10@@3MA @ 0x00429D10
// match: ?flt_429D14@@3MA @ 0x00429D14
// match: ?flt_429D18@@3MA @ 0x00429D18
// match: ?flt_429D1C@@3MA @ 0x00429D1C
// match: ?flt_429D20@@3MA @ 0x00429D20
// match: ?flt_429D24@@3MA @ 0x00429D24
// match: ?flt_429D28@@3MA @ 0x00429D28
// match: ?flt_429D2C@@3MA @ 0x00429D2C
// match: ?flt_429D30@@3MA @ 0x00429D30
// match: ?flt_429D34@@3MA @ 0x00429D34
// match: ?flt_429D38@@3MA @ 0x00429D38
// match: ?dword_429D3C@@3MA @ 0x00429D3C
// match: ?dword_429D40@@3MA @ 0x00429D40
// match: ?flt_429D44@@3MA @ 0x00429D44
// match: ?flt_429D48@@3MA @ 0x00429D48
// match: ?flt_429D4C@@3MA @ 0x00429D4C
// match: ?flt_429D50@@3MA @ 0x00429D50
// match: ?flt_429D54@@3MA @ 0x00429D54
// match: ?flt_429D58@@3MA @ 0x00429D58
// match: ?flt_429D5C@@3MA @ 0x00429D5C
// match: ?flt_429D60@@3MA @ 0x00429D60
// match: ?flt_429D64@@3MA @ 0x00429D64
// match: ?flt_429D68@@3MA @ 0x00429D68
// match: ?flt_429D6C@@3MA @ 0x00429D6C
// match: ?flt_429D70@@3MA @ 0x00429D70
// match: ?dword_429D74@@3HA @ 0x00429D74
// match: ?flt_429D78@@3MA @ 0x00429D78
// match: ?flt_429D7C@@3MA @ 0x00429D7C
// match: ?flt_429D80@@3MA @ 0x00429D80
// match: ?flt_429D84@@3MA @ 0x00429D84
// match: ?flt_429D88@@3MA @ 0x00429D88
// match: ?dword_429D8C@@3HA @ 0x00429D8C
// match: ?dword_429D90@@3URwV3d@@A @ 0x00429D90
// match: ?flt_429D9C@@3MA @ 0x00429D9C
// match: ?flt_429DA0@@3MA @ 0x00429DA0
// match: ?flt_429DA4@@3MA @ 0x00429DA4
// match: ?flt_429DA8@@3MA @ 0x00429DA8
// match: ?flt_429DAC@@3MA @ 0x00429DAC
// match: ?dword_429DB0@@3MA @ 0x00429DB0
// match: ?flt_429DB4@@3MA @ 0x00429DB4
// match: ?flt_429DB8@@3MA @ 0x00429DB8
// match: ?dword_429DBC@@3MA @ 0x00429DBC
// match: ?dword_429DC0@@3MA @ 0x00429DC0
// match: ?dword_429DC4@@3MA @ 0x00429DC4
// match: ?dword_429DC8@@3MA @ 0x00429DC8
// match: ?flt_429DCC@@3MA @ 0x00429DCC
// match: ?dword_429DD0@@3MA @ 0x00429DD0
// match: ?flt_429DD4@@3MA @ 0x00429DD4
// match: ?flt_429DD8@@3MA @ 0x00429DD8
// match: ?flt_429DDC@@3MA @ 0x00429DDC
// match: ?flt_429DE0@@3MA @ 0x00429DE0
// match: ?flt_429DE4@@3MA @ 0x00429DE4

// match: ?sub_147080@type_3DBC78_450@@QAEXPAUtype_712B0_3DBC78@@PAURwMatrixTag@@@Z @ 0x00147080
// sp-match: ?sub_147080@type_3DBC78_450@@QAEXPAUtype_712B0_3DBC78@@PAURwMatrixTag@@@Z @ 0x000F3810

// Its mass and inverse, top speed (the scripts' units scaled as
// "VehicleSetMaxSpeed" scales them) and gimp level from the trigger, its
// matrix from arg_4, the rest reset; the planes come from the model's box
// when it has one.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78_450::sub_147080(type_712B0_3DBC78 *arg_0, RwMatrixTag *arg_4)
{
    type_3DF8D8 *var_4;
    type_3DF8D8 *v8;
    RwBBox *varC;

    unk_170 = *arg_4;
    RwMatrixUpdate(&unk_170);
    unk_24C = (RwReal)arg_0->unk_F0;
    unk_254 = (RwReal)arg_0->unk_F4;
    unk_108 = arg_0->unk_100;
    unk_268 = (arg_0->unk_F8 * 1618.4615f * 100.0f) / 216000.0f;
    unk_250 = 1.0f / unk_24C;
    unk_244 = 0;
    unk_298 = 0;
    unk_230 = 1;
    unk_234 = 1;
    unk_248 = 0;
    unk_29C = 0;
    unk_258 = 1.0f / (unk_24C * 14400.0f);
    zero_v3d(&unk_124);
    zero_v3d(&unk_130);
    set_xyz(&unk_154, 1.0f, 1.0f, 1.0f);
    set_xyz(&unk_160, 1.0f, 1.0f, 1.0f);
    unk_274 = dword_429D3C;
    unk_278 = 0.05f;
    unk_26C = 0.0f;
    unk_270 = 1.0f;
    unk_23C = 0;
    unk_240 = 0;
    unk_27C = 0;
    unk_104 = 1;
    unk_2A0 = 0;
    if (unk_108 == 3)
        unk_104 = 0;
    unk_238 = unk_278 / (flt_429D2C * unk_254 * unk_250);
    if (unk_238 < 0.0f)
        unk_238 = 0.0f;
    if (unk_238 > 0.5f)
        unk_238 = 0.5f;
    zero_v3d(&unk_13C);
    zero_v3d(&unk_148);
    zero_v3d(&unk_10C);
    zero_v3d(&unk_118);
    zero_v3d(&unk_124);
    zero_v3d(&unk_130);
    zero_v3d(&unk_25C);
    RwMatrixSetIdentity(&unk_1B0);
    RwMatrixSetIdentity(&unk_1F0);
    zero_v3d(&unk_28C);
    zero_v3d(&unk_280);
    unk_350 = 0;
    unk_2A4 = 0;
    unk_2A8 = 0;
    zero_v3d(&unk_2AC);
    zero_v3d(&unk_2B8);
    var_4 = sub_198800(&arg_0->unk_C0);
    if (var_4)
    {
        v8 = ((type_3DFE7C *)var_4)->sub_1954D0();
        if (v8)
        {
            varC = ((type_3DF9C4 *)v8)->sub_190A90();
            if (varC)
            {
                unk_2A4 = 1;
                sub_147930(&varC->inf, &varC->sup);
            }
        }
    }
}


// match: ?sub_147710@type_3DBC78_450@@QAEXXZ @ 0x00147710
// sp-match: ?sub_147710@type_3DBC78_450@@QAEXXZ @ 0x000F1DF0
// The four planes around the kind-2 contact points (their extent in x and
// z, out by the least radius).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78_450::sub_147710()
{
    RwReal fp_C;
    RwV2d mn;
    RwV2d mx;
    RwInt32 loc18;

    if (unk_2A4)
        return;
    mn.x = 99999.0f;
    mx.x = -99999.0f;
    mn.y = 99999.0f;
    mx.y = -99999.0f;
    fp_C = 99999.0f;
    for (loc18 = 0; loc18 < 13; loc18++)
    {
        if (unk_00[loc18].unk_10 != 2)
            continue;
        if (unk_00[loc18].unk_0C < fp_C)
            fp_C = unk_00[loc18].unk_0C;
        if (unk_00[loc18].unk_00.x < mn.x)
            mn.x = unk_00[loc18].unk_00.x;
        if (unk_00[loc18].unk_00.z < mn.y)
            mn.y = unk_00[loc18].unk_00.z;
        if (unk_00[loc18].unk_00.x > mx.x)
            mx.x = unk_00[loc18].unk_00.x;
        if (unk_00[loc18].unk_00.z > mx.y)
            mx.y = unk_00[loc18].unk_00.z;
    }
    set_xyz(&unk_2D0[0].normal, 1.0f, 0.0f, 0.0f);
    unk_2D0[0].distance = mx.x + fp_C;
    set_xyz(&unk_2D0[1].normal, -1.0f, 0.0f, 0.0f);
    unk_2D0[1].distance = -mn.x + fp_C;
    set_xyz(&unk_2D0[2].normal, 0.0f, 0.0f, 1.0f);
    unk_2D0[2].distance = mx.y + fp_C;
    set_xyz(&unk_2D0[3].normal, 0.0f, 0.0f, -1.0f);
    unk_2D0[3].distance = -mn.y + fp_C;
}

// match: ?sub_147930@type_3DBC78_450@@QAEXPAURwV3d@@0@Z @ 0x00147930
// sp-match: ?sub_147930@type_3DBC78_450@@QAEXPAURwV3d@@0@Z @ 0x000F22C0
// The four planes of the box from arg_0 (its least corner) to arg_4.
void type_3DBC78_450::sub_147930(RwV3d *arg_0, RwV3d *arg_4)
{
    set_xyz(&unk_2D0[0].normal, 1.0f, 0.0f, 0.0f);
    unk_2D0[0].distance = arg_4->x;
    set_xyz(&unk_2D0[1].normal, -1.0f, 0.0f, 0.0f);
    unk_2D0[1].distance = -arg_0->x;
    set_xyz(&unk_2D0[2].normal, 0.0f, 0.0f, 1.0f);
    unk_2D0[2].distance = arg_4->z;
    set_xyz(&unk_2D0[3].normal, 0.0f, 0.0f, -1.0f);
    unk_2D0[3].distance = -arg_0->z;
}

// match: ?sub_147A20@type_3DBC78_450@@QAEXPAURwPlane@@@Z @ 0x00147A20
// sp-match: ?sub_147A20@type_3DBC78_450@@QAEXPAURwPlane@@@Z @ 0x000F2350
// The four planes through the body's matrix, into arg_0.
void type_3DBC78_450::sub_147A20(RwPlane *arg_0)
{
    RwInt32 var_4;
    RwV3d var_10;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        RwV3dScale(&var_10, &unk_2D0[var_4].normal, unk_2D0[var_4].distance);
        RwV3dTransformPoint(&var_10, &var_10, &unk_170);
        RwV3dTransformVector(&arg_0[var_4].normal, &unk_2D0[var_4].normal, &unk_170);
        arg_0[var_4].distance = RwV3dDotProduct(&arg_0[var_4].normal, &var_10);
    }
}

#ifdef CODFH_SP
// Single player's RwV3dScale evaluates the scale once, as an inline
// function's argument (SP 0xF49A0, and 0xF4620 where this inline is not
// expanded: one product, consumed by the last component). The body is the
// macro itself: sub_147B50 (SP 0xF5C10) matches only with its do/while.
inline void sp_v3d_scale(RwV3d *o, const RwV3d *a, RwReal sc)
{
    RwV3dScaleMacro(o, a, sc);
}
#endif

// match: ?sub_147B50@type_3DBC78_450@@QAEXPAUtype_712B0_3DBC78@@PAUtype_3D3548@@M@Z @ 0x00147B50
// sp-match: ?sub_147B50@type_3DBC78_450@@QAEXPAUtype_712B0_3DBC78@@PAUtype_3D3548@@M@Z @ 0x000F5190
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Steps the body by arg_8 (at most 3): the trigger arg_0 resets its
// position while dword_4D50F8 counts down, and a player on a mounted
// weapon (posture 5) aboard arg_4 marks it (unk_2A0). Then come the
// steering torque, the grip, gravity and drag, the contacts (sub_149F80 for
// gimp level 2, else sub_14A250), their impulses, and the velocity capped
// at the top speed. Its moves (unk_148, unk_13C) come last.
void type_3DBC78_450::sub_147B50(type_712B0_3DBC78 *arg_0, type_3D3548 *arg_4, RwReal arg_8)
{
    RwReal zE0;
    RwReal locDC;
#ifndef CODFH_SP
    RwV3d var_D8;
#endif
    RwV3d lcl_CC;
    RwReal vC0;
    type_149920 var_BC;
    RwV3d frm_A4;
    RwReal l98;
    RwReal var94;
    RwReal x90;
    RwReal ebp_8C;
    RwReal loc88;
    RwReal u84;
    RwReal frm_80;
    RwReal bp_7C;
    RwReal var_78;
    RwReal var_74;
    RwReal var70;
    RwReal stk_6C;
    RwReal q68;
    RwV3d var_64;
    RwV3d stk_58;
    RwV3d x4C;
    RwMatrix *var_40;
    RwV3d l3C;
    RwV3d lv_30;
    RwV3d frm_24;
    type_3D3548 *m_18;
    RwInt32 ebp_14;
    RwReal lv_10;
    RwInt32 var_C;
    RwReal bp_8;
    RwReal bp_4;

    if (!unk_104)
    {
        zero_v3d(&unk_148);
        zero_v3d(&unk_13C);
        zero_v3d(&unk_124);
        zero_v3d(&unk_130);
        return;
    }
    sub_147A20(unk_310);
    if (arg_8 > 3.0f)
        arg_8 = 3.0f;
    unk_350 = arg_8;
    lv_30 = unk_170.pos;
    unk_2A0 = 0;
    m_18 = sub_1745A0(0);
    if (m_18 && ((type_10F710 *)m_18)->unk_19D0 == 5 && m_18->vf_200() == arg_4)
        unk_2A0 = 1;
    ebp_14 = unk_230 || unk_234;
    if (dword_4D50F8)
    {
        unk_170.pos = arg_0->unk_90;
        unk_170.pos.y += 100.0f;
        zero_v3d(&unk_124);
        zero_v3d(&unk_130);
        set_xyz(&unk_170.right, 1.0f, 0.0f, 0.0f);
        set_xyz(&unk_170.up, 0.0f, 1.0f, 0.0f);
        set_xyz(&unk_170.at, 0.0f, 0.0f, 1.0f);
        dword_4D50F8--;
    }
    unk_27C = 0;
    set_xyz(&var_64, 0.0f, 0.0f, unk_280.z);
    set_xyz(&stk_58, 0.0f, 0.0f, unk_28C.z);
    if (sub_14C520(&var_64) || sub_14C520(&stk_58))
    {
        unk_27C = 1;
        unk_124.y = 0.0f;
    }
    if (unk_27C && !unk_2A0)
        return;
    l3C = unk_124;
    sub_14C340();
    if (arg_0)
    {
        unk_24C = (RwReal)arg_0->unk_F0;
        unk_254 = (RwReal)arg_0->unk_F4;
    }
    lv_10 = 1.0f / unk_350;
    zero_v3d(&unk_10C);
    zero_v3d(&unk_118);
    var_40 = &unk_170;
    unk_1F0 = *var_40;
    RwMatrixInvert(&unk_1B0, var_40);
    bp_4 = unk_244;
    if (fabs(unk_23C) > 0.01f && !ebp_14)
        bp_4 = unk_23C;
    if (unk_298 || unk_27C)
    {
        var70 = RwV3dDotProduct(&unk_170.up, &dword_429D90);
        if ((RwReal)fabs((RwDouble)var70) < flt_429D88)
        {
            var_74 = ((RwReal)fabs((RwDouble)var70) - flt_429D84) / (flt_429D88 - flt_429D84);
            if (var_74 < 0.0f)
                var_74 = 0.0f;
            if (var_74 > 1.0f)
                var_74 = 1.0f;
            bp_4 = bp_4 * var_74;
        }
        if (bp_4 > 0.01f || bp_4 < -0.01f)
        {
            var_78 = unk_238 * unk_350;
            if (var_78 > 0.5f)
                var_78 = 0.5f;
            bp_7C = 1.0f - var_78;
            if (bp_4 < 0.0f)
                var_78 = -var_78;
            frm_80 = bp_4 * bp_7C + var_78;
            set_xyz(&x4C, 0.0f, 0.0f, 0.0f);
            set_xyz(&frm_24, 0.0f, 0.0f, frm_80 * unk_254 * flt_429D2C);
            sub_141320(&x4C, &x4C, var_40);
            sub_141320(&frm_24, &frm_24, var_40);
            sub_149780(&x4C, &frm_24);
        }
        stk_6C = unk_248;
        if (unk_29C)
        {
            u84 = RwV3dLength((RwV3d *)&unk_124);
            if (u84 > 15.0f)
                u84 = 15.0f;
            loc88 = RwV3dDotProduct(&unk_124, &unk_170.at);
            stk_6C = (u84 * 0.5f) * unk_248;
            if (loc88 < 0.0f)
                stk_6C = stk_6C * -1.0f;
        }
        if (unk_2A0)
            q68 = dword_429D04;
        else
            q68 = 0.7f;
        set_xyz(&x4C, -150.0f, -113.0f, 0.0f);
        set_xyz(&frm_24, 0.0f, 0.0f, q68 * unk_254 * stk_6C);
        sub_141320(&x4C, &x4C, var_40);
        sub_141320(&frm_24, &frm_24, var_40);
        sub_149780(&x4C, &frm_24);
        set_xyz(&x4C, 150.0f, -113.0f, 0.0f);
        set_xyz(&frm_24, 0.0f, 0.0f, -unk_254 * q68 * stk_6C);
        sub_141320(&x4C, &x4C, var_40);
        sub_141320(&frm_24, &frm_24, var_40);
        sub_149780(&x4C, &frm_24);
    }
    if ((RwReal)fabs((RwDouble)bp_4) > 0.05f)
        unk_230 = 0;
    if (unk_298 && (RwReal)fabs((RwDouble)bp_4) < 0.01f && fabs(unk_248) < 0.1f)
    {
        x90 = RwV3dLength((RwV3d *)&unk_124);
        var94 = 0.6f;
#ifdef CODFH_SP // shape: plain fabs, no stored dot (SP 0xF5811: fabs, fmul, fmul, compare)
        var94 = fabs(RwV3dDotProduct(&unk_170.at, &dword_429D90)) * flt_429D78 * var94;
#else
        var94 = (RwReal)fabs((RwDouble)(ebp_8C = RwV3dDotProduct(&unk_170.at, &dword_429D90))) * flt_429D78 * var94;
#endif
        if (x90 < var94)
            unk_234 = 1;
    }
    else
    {
        unk_234 = 0;
        if (unk_2A0)
            unk_230 = 0;
    }
    if (!unk_27C)
        unk_10C.y += flt_429D28;
    set_xyz(&x4C, 0.0f, 0.0f, 0.0f);
    if (unk_298)
    {
        unk_10C.x += -unk_124.x * flt_429D18;
        unk_10C.y += -unk_124.y * flt_429D18;
        unk_10C.z += -unk_124.z * flt_429D18;
        unk_118.x += -unk_130.x * flt_429D1C;
        unk_118.y += -unk_130.y * flt_429D1C;
        unk_118.z += -unk_130.z * flt_429D1C;
    }
    bp_8 = RwV3dLength((RwV3d *)&unk_10C);
    if (bp_8 > 2.0f)
    {
        RwV3dNormalize(&unk_10C, &unk_10C);
        RwV3dScale(&unk_10C, &unk_10C, 2.0f);
    }
    sub_149AA0();
    if (unk_108 == 2)
        var_C = sub_149F80(0);
    else
        var_C = sub_14A250(arg_4, unk_350, 0);
    if (var_C)
    {
#ifdef CODFH_SP // shape: block-scoped (SP 0xF5190: the frame is 0x80, var_D8 shares its slot)
        RwV3d var_D8;

#endif
        zero_v3d(&var_BC.unk_00);
        zero_v3d(&var_BC.unk_0C);
        RwV3dSub(&lcl_CC, &lv_30, &unk_170.pos);
        sub_141320(&var_D8, &lcl_CC, &unk_1B0);
        sub_149F00(&x4C, 0.0f, 0.0f, 0.0f);
        vC0 = RwV3dDotProduct(&unk_170.right, &dword_429D90);
        if ((RwReal)fabs((RwDouble)vC0) < 0.34f)
        {
            unk_274 = dword_429D3C;
            locDC = ((RwReal)ebp_14 + unk_274) * unk_350 * unk_350;
            if (var_D8.x > locDC)
                var_D8.x = locDC;
#ifdef CODFH_SP // shape: value on the left (SP 0xF5190 loads var_D8.x and compares)
            if (var_D8.x < -locDC)
#else
            if (-locDC > var_D8.x)
#endif
                var_D8.x = -locDC;
            sub_149F00(&frm_A4, var_D8.x * flt_429D34 * unk_24C, 0.0f, 0.0f);
            sub_149920(&var_BC, &x4C, &frm_A4);
        }
        unk_278 = dword_429D40;
        zE0 = ((RwReal)ebp_14 + unk_278) * unk_350 * unk_350;
        if (var_D8.z > zE0)
            var_D8.z = zE0;
#ifdef CODFH_SP // shape: value on the left
        if (var_D8.z < -zE0)
#else
        if (-zE0 > var_D8.z)
#endif
            var_D8.z = -zE0;
        sub_149F00(&frm_A4, 0.0f, 0.0f, var_D8.z * flt_429D34 * unk_24C);
        sub_149920(&var_BC, &x4C, &frm_A4);
        sub_149D60(&var_BC);
        var_D8.x = (unk_170.pos.x - lv_30.x) * lv_10;
        var_D8.y = (unk_170.pos.y - lv_30.y) * lv_10;
        var_D8.z = (unk_170.pos.z - lv_30.z) * lv_10;
        RwV3dSub(&lcl_CC, &var_D8, &unk_124);
        l98 = RwV3dLength((RwV3d *)&lcl_CC);
#ifdef CODFH_SP // shape: value on the left
        if (l98 > 2.5f * unk_350)
#else
        if (2.5f * unk_350 < l98)
#endif
        {
            RwV3dNormalize(&lcl_CC, &lcl_CC);
#ifdef CODFH_SP // shape: an inline function's scale (see sp_v3d_scale)
            sp_v3d_scale(&lcl_CC, &lcl_CC, 2.5f * unk_350);
#else
            RwV3dScale(&lcl_CC, &lcl_CC, 2.5f * unk_350);
#endif
        }
        unk_124.x += lcl_CC.x;
        unk_124.y += lcl_CC.y;
        unk_124.z += lcl_CC.z;
        if (dword_429D74)
        {
            l98 = RwV3dLength((RwV3d *)&unk_124);
            if (l98 > unk_268)
            {
                RwV3dNormalize(&unk_124, &unk_124);
                RwV3dScale(&unk_124, &unk_124, unk_268);
            }
        }
        unk_298 = 1;
    }
    else
    {
        unk_298 = 0;
    }
    RwV3dSub(&unk_148, &unk_170.pos, &lv_30);
    RwV3dScale(&unk_148, &unk_148, lv_10);
    RwV3dSub(&unk_13C, &l3C, &unk_124);
}

// match: ?sub_148F60@type_3DBC78_450@@QAEXPAUtype_3DBC78@@PAU1@M@Z @ 0x00148F60
// sp-match: ?sub_148F60@type_3DBC78_450@@QAEXPAUtype_3DBC78@@PAU1@M@Z @ 0x000F3BA0
// Steps the body as the one that follows arg_4 (the vehicle arg_0's second
// body) for arg_8: a grip against arg_4's sideways move, the vehicle's
// pending push (unk_1104 steps of unk_1108 at unk_1114, fading by unk_1120),
// then it takes arg_4's position (its height eased toward arg_4's, at most
// 100 away) and heading, and its kind-1 contact points pull it to arg_4's.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78_450::sub_148F60(type_3DBC78 *arg_0, type_3DBC78_450 *arg_4, RwReal arg_8)
{
    RwReal local_78;
    RwInt32 local_74;
    RwReal local_70;
    RwV3d var_6C;
    RwReal v60;
    RwV3d *bp_5C;
    RwV3d *frm_58;
    RwV3d *var54;
    RwV3d l50;
    RwV3d var44;
    RwV3d var_38;
    RwV3d *v2C;
    RwV3d *var_28;
    RwV3d *ebp_24;
    RwV3d loc20;
    RwV3d *v14;
    RwInt32 lv_10;
    RwV3d var_C;

    var44 = unk_170.pos;
    unk_350 = arg_8;
    var54 = RwMatrixGetRight(&arg_4->unk_170);
    v2C = RwMatrixGetAt(&arg_4->unk_170);
    var_28 = RwMatrixGetPos(&arg_4->unk_170);
    bp_5C = RwMatrixGetRight(&unk_170);
    frm_58 = RwMatrixGetUp(&unk_170);
    v14 = RwMatrixGetAt(&unk_170);
    ebp_24 = RwMatrixGetPos(&unk_170);
    zero_v3d(&unk_10C);
    zero_v3d(&unk_118);
    if (!arg_4->unk_230)
    {
        set_xyz(&var_C, 0.0f, 100.0f, 0.0f);
        l50 = arg_4->unk_13C;
        l50.y = 0.0f;
        RwV3dScale(&l50, &l50, flt_429D44 * unk_24C);
        sub_141320(&var_C, &var_C, &arg_4->unk_170);
        sub_149780(&var_C, &l50);
    }
    sub_149AA0();
    if (arg_0->unk_1104 > 0)
    {
        zero_v3d(&unk_10C);
        zero_v3d(&unk_118);
        set_xyz(&var_6C, flt_429D60 * arg_0->unk_1108.x, flt_429D60 * arg_0->unk_1108.y,
                flt_429D60 * arg_0->unk_1108.z);
        sub_149780(&arg_0->unk_1114, &var_6C);
        zero_v3d(&unk_124);
        zero_v3d(&unk_10C);
        sub_149AA0();
        local_70 = arg_0->unk_1120 / (RwReal)arg_0->unk_1104;
        v60 = RwV3dNormalize(&arg_0->unk_1108, &arg_0->unk_1108);
        v60 = v60 - local_70 * arg_8;
        if (v60 < 1.0f)
            v60 = 1.0f;
        RwV3dScale(&arg_0->unk_1108, &arg_0->unk_1108, v60);
        arg_0->unk_1104 -= (RwInt32)(RwReal)ceil((RwDouble)arg_8);
        if (RwV3dLength((RwV3d *)&arg_0->unk_1108) < 1600.0f)
            arg_0->unk_1104 = 0;
        if (arg_0->unk_1104 <= 0)
            arg_0->unk_1104 = 0;
    }
    ebp_24->x = var_28->x;
    ebp_24->z = var_28->z;
    if (var_28->y - ebp_24->y > 100.0f)
        ebp_24->y = var_28->y - 100.0f;
    if (var_28->y - ebp_24->y < -100.0f)
        ebp_24->y = var_28->y + 100.0f;
#ifdef CODFH_SP // shape: flt_429D7C read fresh (SP 0xF3E61 loads the blend in source order)
    ebp_24->y = *(volatile RwReal *)&flt_429D7C * ebp_24->y + flt_429D80 * var_28->y;
#else
    ebp_24->y = flt_429D7C * ebp_24->y + flt_429D80 * var_28->y;
#endif
    v14->x = v2C->x;
    v14->z = v2C->z;
    RwV3dNormalize(v14, v14);
    bp_5C->x = var54->x;
    bp_5C->z = var54->z;
    RwV3dNormalize(bp_5C, bp_5C);
    RwV3dCrossProduct(frm_58, v14, bp_5C);
    RwV3dNormalize(frm_58, frm_58);
    RwV3dCrossProduct(bp_5C, frm_58, v14);
    zero_v3d(&unk_10C);
    zero_v3d(&unk_118);
    lv_10 = 13;
    for (local_74 = 0; local_74 < lv_10; local_74++)
    {
        if (arg_4->unk_00[local_74].unk_10 != 1)
            continue;
        sub_1414C0(&loc20, &arg_4->unk_00[local_74].unk_00, &unk_170);
        sub_1414C0(&var_38, &arg_4->unk_00[local_74].unk_00, &arg_4->unk_170);
#ifdef CODFH_SP // shape: the product kept in source order
        local_78 = (var_38.y - loc20.y) * flt_429D5C;
        set_xyz(&l50, 0.0f, local_78 * unk_24C, 0.0f);
#else
        set_xyz(&l50, 0.0f, (local_78 = var_38.y - loc20.y) * flt_429D5C * unk_24C, 0.0f);
#endif
        sub_141320(&loc20, &arg_4->unk_00[local_74].unk_00, &unk_170);
        sub_149780(&loc20, &l50);
    }
    unk_10C.x = unk_10C.y = unk_10C.z = 0.0f;
    unk_118.x += -unk_130.x * flt_429D4C;
    unk_118.y += -unk_130.y * flt_429D4C;
    unk_118.z += -unk_130.z * flt_429D4C;
    sub_149AA0();
    ebp_24->x = var_28->x;
    ebp_24->z = var_28->z;
}

// match: ?sub_149780@type_3DBC78_450@@QAEXPAURwV3d@@0@Z @ 0x00149780
// sp-match: ?sub_149780@type_3DBC78_450@@QAEXPAURwV3d@@0@Z @ 0x000F23F0
// Applies the force arg_4 at the point arg_0 (both in world axes, arg_0
// from the body's centre): its share of the acceleration (unk_10C) and of
// the spin (unk_118, the moment scaled by the inverse mass).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78_450::sub_149780(RwV3d *arg_0, RwV3d *arg_4)
{
    RwReal l4;
    RwReal var_8;
    RwV3d bp_14;
    RwV3d var20;
    RwReal slot_24;
    RwReal v28;
    RwV3d v34;
    RwReal l38;
    RwV3d slot_44;

    var_8 = unk_250;
    set_xyz(&bp_14, var_8 * arg_4->x, var_8 * arg_4->y, var_8 * arg_4->z);
    RwV3dAdd(&unk_10C, &unk_10C, &bp_14);
    slot_44 = *arg_0;
    v34 = *arg_4;
    l38 = sub_13FA50(&slot_44);
    v28 = sub_13FA50(&v34);
    RwV3dCrossProduct(&var20, &slot_44, &v34);
    l4 = sub_13FA50(&var20);
    slot_24 = l4 * (l38 * v28) * var_8;
    set_xyz(&var20, var20.x * slot_24, var20.y * slot_24, var20.z * slot_24);
    RwV3dAdd(&unk_118, &unk_118, &var20);
}

// match: ?sub_149920@type_3DBC78_450@@QAEXPAUtype_149920@@PAURwV3d@@1@Z @ 0x00149920
// sp-match: ?sub_149920@type_3DBC78_450@@QAEXPAUtype_149920@@PAURwV3d@@1@Z @ 0x000F2540
// As sub_149780, into the accumulator arg_0 instead of the body.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78_450::sub_149920(type_149920 *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwReal l4;
    RwReal var_8;
    RwV3d bp_14;
    RwV3d var20;
    RwReal slot_24;
    RwReal v28;
    RwV3d v34;
    RwReal l38;
    RwV3d slot_44;

    var_8 = unk_250;
    set_xyz(&bp_14, var_8 * arg_8->x, var_8 * arg_8->y, var_8 * arg_8->z);
    RwV3dAdd(&arg_0->unk_00, &bp_14, &arg_0->unk_00);
    slot_44 = *arg_4;
    v34 = *arg_8;
    l38 = sub_13FA50(&slot_44);
    v28 = sub_13FA50(&v34);
    RwV3dCrossProduct(&var20, &slot_44, &v34);
    l4 = sub_13FA50(&var20);
    slot_24 = l4 * (l38 * v28) * var_8;
    set_xyz(&var20, var20.x * slot_24, var20.y * slot_24, var20.z * slot_24);
    RwV3dAdd(&arg_0->unk_0C, &arg_0->unk_0C, &var20);
}

// match: ?sub_149AA0@type_3DBC78_450@@QAEXXZ @ 0x00149AA0
// sp-match: ?sub_149AA0@type_3DBC78_450@@QAEXXZ @ 0x000F2670
// Moves the body on by its step: the matrix translated by the velocity and
// half the acceleration, the velocity advanced, the matrix turned about its
// own position by the spin, the spin advanced.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78_450::sub_149AA0()
{
    RwV3d var_C;
    RwReal local_10;
    RwV3d var_1C;
    RwReal l20;
    RwV3d *fp_24;
    RwV3d var_30;

    l20 = 0.5f * unk_350 * unk_350;
    var_1C.x = unk_124.x * unk_350 + l20 * unk_10C.x;
    var_1C.y = unk_124.y * unk_350 + l20 * unk_10C.y;
    var_1C.z = unk_124.z * unk_350 + l20 * unk_10C.z;
    RwMatrixTranslate(&unk_170, &var_1C, rwCOMBINEPOSTCONCAT);
    unk_124.x += unk_10C.x * unk_350;
    unk_124.y += unk_10C.y * unk_350;
    unk_124.z += unk_10C.z * unk_350;
    var_C.x = unk_130.x * unk_350 + (l20 * unk_118.x);
    var_C.y = unk_130.y * unk_350 + l20 * unk_118.y;
    var_C.z = unk_130.z * unk_350 + l20 * unk_118.z;
    local_10 = sub_13FA50(&var_C);
    if (local_10 != 0.0f && (var_C.x != 0.0f || var_C.y != 0.0f || var_C.z != 0.0f))
    {
        fp_24 = RwMatrixGetPos(&unk_170);
        var_30 = *fp_24;
        fp_24->x = 0.0f;
        fp_24->y = 0.0f;
        fp_24->z = 0.0f;
        RwMatrixRotate(&unk_170, &var_C, local_10 * flt_429D20, rwCOMBINEPOSTCONCAT);
        fp_24->x = var_30.x;
        fp_24->y = var_30.y;
        fp_24->z = var_30.z;
    }
    unk_130.x += unk_118.x * unk_350;
    unk_130.y += (unk_118.y * unk_350);
    unk_130.z += unk_118.z * unk_350;
}

// match: ?sub_149D60@type_3DBC78_450@@QAEXPAUtype_149920@@@Z @ 0x00149D60
// sp-match: ?sub_149D60@type_3DBC78_450@@QAEXPAUtype_149920@@@Z @ 0x000F28A0
// Applies the accumulated move arg_0 at once: translated by its first
// vector, turned by its second.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DBC78_450::sub_149D60(type_149920 *arg_0)
{
    RwV3d var_C;
    RwReal local_10;
    RwV3d *l14;
    RwV3d ebp_20;

    RwMatrixTranslate(&unk_170, &arg_0->unk_00, rwCOMBINEPOSTCONCAT);
    var_C = arg_0->unk_0C;
    local_10 = sub_13FA50(&var_C);
    if (local_10 != 0.0f && (var_C.x != 0.0f || var_C.y != 0.0f || var_C.z != 0.0f))
    {
        l14 = RwMatrixGetPos(&unk_170);
        ebp_20 = *l14;
        l14->x = 0.0f;
        l14->y = 0.0f;
        l14->z = 0.0f;
        RwMatrixRotate(&unk_170, &var_C, local_10 * flt_429D20, rwCOMBINEPOSTCONCAT);
        l14->x = ebp_20.x;
        l14->y = ebp_20.y;
        l14->z = ebp_20.z;
    }
}

// match: ?sub_149E80@type_3DBC78_450@@QAEXPAURwV3d@@MMM@Z @ 0x00149E80
// sp-match: ?sub_149E80@type_3DBC78_450@@QAEXPAURwV3d@@MMM@Z @ 0x000F29A0
// The point (arg_4, arg_8, arg_C) in the body's frame, into world space.
void type_3DBC78_450::sub_149E80(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    arg_0->x = arg_4;
    arg_0->y = arg_8;
    arg_0->z = arg_C;
    sub_1414C0(arg_0, arg_0, &unk_170);
}

// match: ?sub_149EC0@type_3DBC78_450@@QAEXPAURwV3d@@0@Z @ 0x00149EC0
// sp-match: ?sub_149EC0@type_3DBC78_450@@QAEXPAURwV3d@@0@Z @ 0x000F29D0
void type_3DBC78_450::sub_149EC0(RwV3d *arg_0, RwV3d *arg_4)
{
    *arg_0 = *arg_4;
    sub_1414C0(arg_0, arg_0, &unk_170);
}

// match: ?sub_149F00@type_3DBC78_450@@QAEXPAURwV3d@@MMM@Z @ 0x00149F00
// sp-match: ?sub_149F00@type_3DBC78_450@@QAEXPAURwV3d@@MMM@Z @ 0x000F2A10
// The vector (arg_4, arg_8, arg_C) in the body's axes, into world axes.
void type_3DBC78_450::sub_149F00(RwV3d *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    arg_0->x = arg_4;
    arg_0->y = arg_8;
    arg_0->z = arg_C;
    sub_141320(arg_0, arg_0, &unk_170);
}

// match: ?sub_149F40@type_3DBC78_450@@QAEXPAURwV3d@@0@Z @ 0x00149F40
// sp-match: ?sub_149F40@type_3DBC78_450@@QAEXPAURwV3d@@0@Z @ 0x000F2A40
void type_3DBC78_450::sub_149F40(RwV3d *arg_0, RwV3d *arg_4)
{
    *arg_0 = *arg_4;
    sub_141320(arg_0, arg_0, &unk_170);
}

// match: ?sub_149F80@type_3DBC78_450@@QAEHH@Z @ 0x00149F80
// sp-match: ?sub_149F80@type_3DBC78_450@@QAEHH@Z @ 0x000F4060
// Sets the body on the ground under its centre (a line 300 either side):
// its position on the hit, its up the surface's normal, then 4. Only when
// the centre is under the surface or arg_0 is set; else 0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DBC78_450::sub_149F80(RwInt32 arg_0)
{
    RwV3d var_C;
    RwV3d var_18;
    type_91F40 *slot_1C;
    RwV3d loc28;
    RwReal l2C;
    RwV3d v38;

    sub_149E80(&var_C, 0.0f, 0.0f, 0.0f);
    loc28 = var_C;
    var_18 = loc28;
    var_18.y += 300.0f;
    loc28.y -= 300.0f;
    slot_1C = sub_14AD30(&var_18, &loc28, 1);
    if (slot_1C)
    {
        l2C = RwV3dDotProduct(&slot_1C->unk_14, &var_C) - RwV3dDotProduct(&slot_1C->unk_08, &slot_1C->unk_14);
        if (l2C < 0.0f || arg_0)
        {
            unk_170.pos = slot_1C->unk_08;
            set_xyz(&v38, 0.0f, 1.0f, 0.0f);
            v38 = slot_1C->unk_14;
            unk_170.up = v38;
            RwV3dCrossProduct(&unk_170.right, &unk_170.up, &unk_170.at);
            RwV3dNormalize(&unk_170.right, &unk_170.right);
            RwV3dCrossProduct(&unk_170.at, &unk_170.right, &unk_170.up);
            RwV3dNormalize(&unk_170.at, &unk_170.at);
            unk_124.y = 0.0f;
            return 4;
        }
    }
    return 0;
}

// match: ?sub_14A250@type_3DBC78_450@@QAEHPAUtype_3D3548@@MH@Z @ 0x0014A250
// sp-match: ?sub_14A250@type_3DBC78_450@@QAEHPAUtype_3D3548@@MH@Z @ 0x000F4EB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The body's contacts for the step arg_4: unless arg_8, the kind-1 points'
// pushes out of the ground (sub_14AAD0), averaged and applied (the turn
// capped at 2500, its y scaled by flt_4D50FC); then, for gimp level 0, the
// vehicle arg_0's collisions (sub_14BEE0), and when it moves fast enough
// (for a player's vehicle, or one with unk_28_23 set) its kind-2 points
// against what they hit (sub_14A5E0, at most four unless a player drives).
// How many points touched.
RwInt32 type_3DBC78_450::sub_14A250(type_3D3548 *arg_0, RwReal arg_4, RwInt32 arg_8)
{
    RwReal var_58;
    RwInt32 var_54;
    RwInt32 var_50;
    RwV3d var_4C;
    type_3DBC78 *var_40;
    RwReal stk_3C;
    RwReal ebp_38;
    RwInt32 var_34;
    RwV3d lv_30;
    RwReal frm_24;
    type_149920 var_20;
    RwReal bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    bp_8 = 1.0f / arg_4;
    if (arg_8)
    {
        // Nothing here: the contacts are skipped (a statement compiled out,
        // as its branch over them shows).
    }
    else
    {
        zero_v3d(&var_20.unk_00);
        zero_v3d(&var_20.unk_0C);
        for (var_34 = 0; var_34 < 13; var_34++)
        {
            if (unk_00[var_34].unk_10 != 1)
                continue;
            bp_4 += sub_14AAD0(&unk_00[var_34], &var_20);
        }
        if (bp_4)
        {
            stk_3C = 1.0f / (RwReal)bp_4;
            RwV3dScale(&var_20.unk_00, &var_20.unk_00, stk_3C);
            RwV3dScale(&var_20.unk_0C, &var_20.unk_0C, stk_3C * flt_429D10 * bp_8);
            ebp_38 = RwV3dLength((RwV3d *)&var_20.unk_0C);
            if (ebp_38 > flt_4D5104)
                flt_4D5104 = ebp_38;
            if (ebp_38 > 2500.0f)
            {
                RwV3dNormalize(&var_20.unk_0C, &var_20.unk_0C);
                RwV3dScale(&var_20.unk_0C, &var_20.unk_0C, 2500.0f);
            }
            if (dword_429D8C)
            {
                var_20.unk_0C.y *= flt_4D50FC;
                sub_149D60(&var_20);
            }
            else
            {
                sub_149D60(&var_20);
                var_20.unk_0C.y *= flt_4D50FC;
            }
            var_20.unk_0C.x *= flt_429D0C * bp_8;
            var_20.unk_0C.y *= flt_429D0C * bp_8;
            var_20.unk_0C.z *= flt_429D0C * bp_8;
            RwV3dAdd(&unk_130, &unk_130, &var_20.unk_0C);
        }
    }
    if (!unk_108)
    {
        var_40 = (type_3DBC78 *)arg_0;
        var_40->unk_DF8 = 0;
        sub_14BEE0(var_40);
    }
    lv_30 = unk_124;
    lv_30.y = 0.0f;
    frm_24 = RwV3dLength((RwV3d *)&lv_30)
        + RwV3dLength((RwV3d *)&unk_130) * 0.31847131f;
    if ((unk_2A0 || arg_0->unk_28_23) && frm_24 > 2.0f && !unk_108)
    {
        var_50 = 0;
        for (var_54 = 0; var_54 < 13; var_54++)
        {
            if (unk_00[var_54].unk_10 != 2)
                continue;
            var_58 = unk_00[var_54].unk_0C;
            sub_1414C0(&var_4C, &unk_00[var_54].unk_00, &unk_1F0);
            sub_14A5E0(arg_0, &unk_00[var_54], var_58, &var_4C);
            var_50++;
            if (!unk_2A0 && var_50 >= 4)
                break;
        }
    }
    return bp_4;
}

// match: ?sub_14A5E0@type_3DBC78_450@@QAEHPAUtype_3D3548@@PAUtype_147710@@MPAURwV3d@@@Z @ 0x0014A5E0
// sp-match: ?sub_14A5E0@type_3DBC78_450@@QAEHPAUtype_3D3548@@PAUtype_147710@@MPAURwV3d@@@Z @ 0x000F4230
// The hull point arg_4 (radius arg_8, last at arg_C) against the sections'
// collision worlds: a sphere test whose triangles (sub_14A870) push it out,
// the pushes averaged and applied; the vehicle arg_0 is told of the hit
// ("WallCollisionNotification") once while unk_28_23 is set.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 type_3DBC78_450::sub_14A5E0(type_3D3548 *arg_0, type_147710 *arg_4, RwReal arg_8, RwV3d *arg_C)
{
    type_14A5E0 var_78;
    RpIntersection var_94;
    RwInt32 stk_98;
    type_4E5D30 *lcl_9C;
    RwReal local_A0;

    var_78.unk_0C = arg_4->unk_00;
    sub_149EC0(&var_78.unk_00, &arg_4->unk_00);
    var_78.unk_18 = arg_8;
    var_78.unk_1C = *arg_C;
    RwV3dSub(&var_78.unk_28, &var_78.unk_00, arg_C);
    if (var_78.unk_28.x + var_78.unk_28.y + var_78.unk_28.z != 0.0f)
        RwV3dNormalize(&var_78.unk_28, &var_78.unk_28);
    var_78.unk_34 = this;
    var_94.type = rpINTERSECTSPHERE;
    var_94.t.sphere.center = var_78.unk_00;
    var_94.t.sphere.radius = arg_8;
    dword_4D31B0 = 0;
    zero_v3d(&var_78.unk_38.unk_00);
    zero_v3d(&var_78.unk_38.unk_0C);
    var_78.unk_50 = 0;
    var_78.unk_60 = unk_2A0;
    for (stk_98 = 0; stk_98 < 4; stk_98++)
    {
        lcl_9C = &dword_4E5D30[stk_98];
        if (lcl_9C->get_unk_00())
        {
            var_78.unk_58 = lcl_9C->get_unk_28();
            RpCollisionWorldForAllIntersections(lcl_9C->get_unk_28(), &var_94, sub_14A870, &var_78);
        }
    }
    if (var_78.unk_50)
    {
        local_A0 = 1.0f / (RwReal)var_78.unk_50;
        RwV3dScale(&var_78.unk_38.unk_00, &var_78.unk_38.unk_00, local_A0);
        RwV3dScale(&var_78.unk_38.unk_0C, &var_78.unk_38.unk_0C, local_A0);
        sub_149D60(&var_78.unk_38);
        if (arg_0->unk_28_23)
        {
            sub_6B5F0("WallCollisionNotification", (type_67620 *)(arg_0->vf_098()), 0, 0, 0, 0, 1, 0);
            arg_0->unk_28_23 = 0;
        }
    }
    return dword_4D31B0;
}

// match: ?sub_14A870@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x0014A870
// sp-match: ?sub_14A870@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000F2A80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// sub_14A5E0's triangle callback: unless the surface is one the body passes
// (flag 0x40000 for a player's vehicle, else 0x840000), a wall facing the
// point's move pushes it out by the sphere's depth.
RpCollisionTriangle *sub_14A870(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                                RwReal arg_C, void *arg_10)
{
    RwV3d var_50;
    RwReal local_44;
    RwV3d var_40;
    RwV3d var_34;
    RwV3d lcl_28;
    RwReal ebp_1C;
    type_14A5E0 *l18;
    type_3DBC78_450 *v14;
    RwReal lv_10;
    type_FC000 *var_C;
    void *bp_8;
    RwUInt32 bp_4;

    l18 = (type_14A5E0 *)arg_10;
    v14 = l18->unk_34;
    bp_8 = ((type_96E30 *)l18->unk_58)->unk_10[((type_92540 *)arg_4)->unk_80 +
                                                   ((type_92540 *)arg_4)->unk_04[arg_8->index].unk_06];
    var_C = sub_FC000(bp_8);
    bp_4 = var_C->unk_04 & 0xFFFF0000;
    if (l18->unk_60)
    {
        if (bp_4 & 0x40000) // not an address: a surface flag
            return arg_8;
    }
    else if (bp_4 & 0x840000) // not an address: surface flags
    {
        return arg_8;
    }
    lv_10 = RwV3dDotProduct(&dword_429D90, &arg_8->normal);
    if ((RwReal)fabs((RwDouble)lv_10) < 0.5f)
    {
        if (RwV3dDotProduct(&arg_8->normal, &l18->unk_28) < 0.0f)
        {
            var_34 = l18->unk_00;
            sub_8F960(arg_8->vertices, &arg_8->normal, &var_34);
            RwV3dSub(&lcl_28, &l18->unk_00, &var_34);
            RwV3dNormalize(&lcl_28, &lcl_28);
            ebp_1C = l18->unk_18
                - (RwV3dDotProduct(&lcl_28, &l18->unk_00) - RwV3dDotProduct(&var_34, &lcl_28));
            if (ebp_1C > 0.0f)
            {
                local_44 = ebp_1C * v14->unk_24C * flt_429D08;
                set_xyz(&var_50, lcl_28.x * local_44, lcl_28.y * 0.0f, lcl_28.z * local_44);
                v14->sub_149F40(&var_40, &l18->unk_0C);
                v14->sub_149920(&l18->unk_38, &var_40, &var_50);
                l18->unk_50++;
            }
        }
    }
    return arg_8;
}

// match: ?sub_14AAD0@type_3DBC78_450@@QAEHPAUtype_147710@@PAUtype_149920@@@Z @ 0x0014AAD0
// sp-match: ?sub_14AAD0@type_3DBC78_450@@QAEHPAUtype_147710@@PAUtype_149920@@@Z @ 0x000F4450
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Pushes the contact point arg_0 out of the ground under it (a line from
// flt_429D64 above, less the body's rise, to 300 below): the depth, capped
// by the step, as a push along the surface's normal gathered into arg_4.
// Whether it touched.
RwInt32 type_3DBC78_450::sub_14AAD0(type_147710 *arg_0, type_149920 *arg_4)
{
    RwReal var_68;
    RwReal var_64;
    RwReal stk_60;
    RwV3d y5C;
    type_91F40 *z50;
    type_149920 l4C;
    RwV3d var_34;
    RwV3d lcl_28;
    RwReal ebp_1C;
    RwV3d l18;
    RwV3d var_C;

    zero_v3d(&l4C.unk_00);
    zero_v3d(&l4C.unk_0C);
    sub_149EC0(&var_C, &arg_0->unk_00);
    ebp_1C = flt_429D64 - (unk_124.y);
    sub_149E80(&lcl_28, arg_0->unk_00.x, ebp_1C + arg_0->unk_00.y, arg_0->unk_00.z);
    sub_149E80(&y5C, arg_0->unk_00.x, arg_0->unk_00.y - 300.0f, arg_0->unk_00.z);
    z50 = sub_14AD30(&lcl_28, &y5C, 1);
    if (z50)
    {
        stk_60 = RwV3dDotProduct(&z50->unk_14, &var_C) - RwV3dDotProduct(&z50->unk_08, &z50->unk_14);
        if (stk_60 < 0.0f)
        {
            var_64 = -stk_60;
            if (var_64 > flt_429D68 * unk_350)
                var_64 = flt_429D68 * unk_350;
            var_68 = var_64 * unk_24C * flt_429D08;
            if (unk_350 < 1.0f)
                var_68 = var_68 * unk_350;
            set_xyz(&var_34, var_68 * z50->unk_14.x, var_68 * z50->unk_14.y, var_68 * z50->unk_14.z);
            sub_149F40(&l18, &arg_0->unk_00);
            sub_149920(&l4C, &l18, &var_34);
            RwV3dAdd(&arg_4->unk_00, &l4C.unk_00, &arg_4->unk_00);
            RwV3dAdd(&arg_4->unk_0C, &arg_4->unk_0C, &l4C.unk_0C);
            return 1;
        }
    }
    return 0;
}

// match: ?sub_14AD30@type_3DBC78_450@@QAEPAUtype_91F40@@PAURwV3d@@0H@Z @ 0x0014AD30
// sp-match: ?sub_14AD30@type_3DBC78_450@@QAEPAUtype_91F40@@PAURwV3d@@0H@Z @ 0x000F2C50
// The nearest hit along the line from arg_0 to arg_4 in the four sections'
// collision worlds (dword_4D5108, or 0); a player's mounted vehicle
// (unk_2A0) tests other surfaces.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_91F40 *type_3DBC78_450::sub_14AD30(RwV3d *arg_0, RwV3d *arg_4, RwInt32 arg_8)
{
    RwLine var_18;
    RwReal var_1C;
    RwInt32 l20;
    type_4E5D30 *fp_24;

    var_18.start = *arg_0;
    var_18.end = *arg_4;
    var_1C = 9999999.0f;
    dword_4D5134.unk_00 = 0;
    dword_4D5108.unk_00 = 0;
    for (l20 = 0; l20 < 4; l20++)
    {
        fp_24 = &dword_4E5D30[l20];
        if (fp_24->get_unk_00() && fp_24->get_unk_28())
        {
            if (unk_2A0)
                sub_91F40(fp_24->get_unk_28(), &var_18, &dword_4D5134, arg_8, 0x40000, 0); // not an address: a surface flag
            else
                sub_91F40(fp_24->get_unk_28(), &var_18, &dword_4D5134, arg_8, 0x840000, 1);
            if (dword_4D5134.unk_00 && dword_4D5134.unk_04 < var_1C)
            {
                dword_4D5108 = dword_4D5134;
                var_1C = dword_4D5134.unk_04;
            }
        }
    }
    if (dword_4D5108.unk_00)
        return &dword_4D5108;
    return 0;
}

#ifdef CODFH_SP
// Single player's dot product through an inline function: its arguments'
// copies make /O2 order the terms y first (SP 0xF2DEC: fld [esp+0x8c],
// fmul [esi+0x2c]), which the bare macro does not.
inline RwReal sp_v3d_dot(const RwV3d *a, const RwV3d *b)
{
    return RwV3dDotProductMacro(a, b);
}
#endif

// match: ?sub_14AE80@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x0014AE80
// sp-match: ?sub_14AE80@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x000F2D50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The atomics' triangle callback: as sub_14A870 for a triangle of an
// atomic placed by the matrix unk_54, which also notes the hit and where
// it is from the atomic (doubled).
RpCollisionTriangle *sub_14AE80(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8, void *arg_C)
{
    RwV3d local_7C;
    RwReal var_70;
    RwV3d l6C;
    RwV3d local_60;
    RwV3d loc54;
    RwReal var_48;
    type_14A5E0 *loc44;
    type_3DBC78_450 *var_40;
    RwV3d *l3C[3];
#ifdef CODFH_SP // shape: the normal after the vertices
    RwV3d local_30[4];
    RwV3d &var_C = local_30[3];
#else
    RwV3d local_30[3];
    RwV3d var_C;
#endif

    loc44 = (type_14A5E0 *)arg_C;
    var_40 = loc44->unk_34;
    local_30[0] = *arg_4->vertices[0];
    local_30[1] = *arg_4->vertices[1];
    local_30[2] = *arg_4->vertices[2];
    var_C = arg_4->normal;
    sub_141590(local_30, local_30, 3, loc44->unk_54);
    sub_141320(&var_C, &var_C, loc44->unk_54);
    l3C[0] = &local_30[0];
    l3C[1] = &local_30[1];
    l3C[2] = &local_30[2];
#ifdef CODFH_SP // shape: an inline function's dot product (see sp_v3d_dot)
    if (sp_v3d_dot(&loc44->unk_28, &var_C) < 0.0f)
#else
    if (RwV3dDotProduct(&loc44->unk_28, &var_C) < 0.0f)
#endif
    {
        local_60 = loc44->unk_00;
        sub_8F960(l3C, &var_C, &local_60);
        RwV3dSub(&loc54, &loc44->unk_00, &local_60);
        RwV3dNormalize(&loc54, &loc54);
        var_48 = loc44->unk_18 - (RwV3dDotProduct(&loc54, &loc44->unk_00) - RwV3dDotProduct(&local_60, &loc54));
        if (var_48 > 0.0f)
        {
            var_70 = var_48 * var_40->unk_24C * flt_429D08;
            set_xyz(&local_7C, loc54.x * var_70, loc54.y * 0.0f, loc54.z * var_70);
            var_40->sub_149F40(&l6C, &loc44->unk_0C);
            var_40->sub_149920(&loc44->unk_38, &l6C, &local_7C);
            loc44->unk_50++;
            loc44->unk_64 = 1;
            loc44->unk_68 = local_60;
            RwV3dSub(&loc44->unk_68, &loc44->unk_68, &loc44->unk_54->pos);
            RwV3dScale(&loc44->unk_68, &loc44->unk_68, 2.0f);
        }
    }
    return arg_4;
}

// match: ?sub_14B140@@YAXPAUtype_14A5E0@@PAUtype_3D3548@@H@Z @ 0x0014B140
// sp-match: ?sub_14B140@@YAXPAUtype_14A5E0@@PAUtype_3D3548@@H@Z @ 0x000F2FA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Pushes the entity arg_4 out of the box of arg_0's body (its planes, out
// by the entity's radius unless it is a soldier), when it is at the box's
// height: out through the nearer side unless it moves along the body; the
// player (arg_8) by its placed position, others by their frame.
void sub_14B140(type_14A5E0 *arg_0, type_3D3548 *arg_4, RwInt32 arg_8)
{
    RwV3d var_6C;
    RwV3d t60;
    RwReal p54;
    RwV3d *var_50;
    RwReal m_4C;
    RwReal local_48;
    RwInt32 local_44;
    RwReal local_40;
    RwReal p3C;
    RwV3d *var_38;
    RwReal l34;
    RwReal var30;
    RwReal ebp_2C;
    RwV3d lcl_28;
    RwFrame *ebp_1C;
    RwReal l18;
    RwInt32 v14;
    RwReal lv_10;
    RwReal var_C;
    RwMatrix *bp_8;
    RwReal bp_4;

    if (!arg_0)
        return;
    ebp_1C = arg_4->get_unk_340();
    if (!ebp_1C)
        return;
    bp_8 = &arg_0->unk_34->unk_170;
    var_50 = RwMatrixGetPos(bp_8);
    if (arg_8)
        var_38 = &((type_10F710 *)arg_4)->unk_434;
    else
        var_38 = &RwFrameGetMatrix(ebp_1C)->pos;
    local_40 = var_38->y - var_50->y;
    if (local_40 < -130.0f || local_40 > 400.0f)
        return;
    if (arg_4->vf_008())
    {
        ebp_2C = arg_0->unk_34->unk_2D0[0].distance;
        p3C = -arg_0->unk_34->unk_2D0[1].distance;
        local_48 = arg_0->unk_34->unk_2D0[2].distance;
        bp_4 = -arg_0->unk_34->unk_2D0[3].distance;
    }
    else
    {
        ebp_2C = arg_0->unk_34->unk_2D0[0].distance + arg_4->unk_4C;
        p3C = -(arg_0->unk_34->unk_2D0[1].distance + arg_4->unk_4C);
        local_48 = arg_0->unk_34->unk_2D0[2].distance + arg_4->unk_4C;
        bp_4 = -(arg_0->unk_34->unk_2D0[3].distance + arg_4->unk_4C);
    }
    RwV3dSub(&t60, var_38, var_50);
    l34 = RwV3dDotProduct(&t60, &bp_8->right);
    lv_10 = RwV3dDotProduct(&bp_8->at, &t60);
    if (lv_10 > local_48 || lv_10 < bp_4 || l34 > ebp_2C || l34 < p3C)
        return;
    if (lv_10 > 0.0f)
    {
        m_4C = local_48 - lv_10;
        var_C = m_4C;
        local_44 = m_4C < local_48;
    }
    else
    {
        var_C = -(m_4C = bp_4 - lv_10);
        local_44 = bp_4 < m_4C;
    }
    if (l34 > 0.0f)
    {
        l18 = ebp_2C - l34;
        var30 = l18;
        v14 = l18 < ebp_2C;
    }
    else
    {
        var30 = -(l18 = p3C - l34);
        v14 = p3C < l18;
    }
    t60.y = 0.0f;
    RwV3dNormalize(&t60, &t60);
    p54 = RwV3dDotProduct(&bp_8->at, &t60);
    if (local_44 && (!v14 || var_C < var30 || p54 > flt_429D9C || -flt_429D9C > p54))
    {
        RwV3dScale(&var_6C, &bp_8->at, m_4C);
        RwV3dAdd(var_38, var_38, &var_6C);
        if (!arg_8)
            RwFrameUpdateObjects(ebp_1C);
        return;
    }
    RwV3dScale(&lcl_28, &bp_8->right, l18);
    RwV3dAdd(var_38, var_38, &lcl_28);
    if (!arg_8)
        RwFrameUpdateObjects(ebp_1C);
}

// match: ?sub_14B570@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x0014B570
// sp-match: ?sub_14B570@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000F4620
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The vehicles' atomic callback for the search arg_10: a projectile
// (type_3DDB98) not riding a vehicle and inside the planes goes off against
// the vehicle; a soldier or player that may be pushed is marked when the
// vehicle moves; another entity's atomic meets the vehicle's kind-2 points
// (sub_14AE80), a hard hit (sub_14C6E0) tells the vehicle, and a heavy
// vehicle hit is pushed back.
RpAtomic *sub_14B570(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10)
{
#ifndef CODFH_SP
    type_149920 x78;
    RwV3d var_60;
#endif
    type_3DBC78 *var_54;
    RwReal var_50;
    RwInt32 var_4C;
    RpIntersection frm_48;
    type_3DBC78 *v2C;
#ifndef CODFH_SP
    RwV3d w28;
#endif
    RwReal loc1C;
    type_3DBC78 *bp_18;
    type_3D3548 *var_14;
    RwReal *lv_10;
    type_3DDB98 *var_C;
    type_14A5E0 *bp_8;
    type_3D3548 *bp_4;

    bp_8 = (type_14A5E0 *)arg_10;
    bp_4 = sub_FB960(arg_8);
    if (bp_4->unk_2C_21 && bp_4->unk_28_2)
    {
        var_C = (type_3DDB98 *)bp_4;
        if (!var_C->unk_3D8.sub_D4910())
        {
            lv_10 = bp_4->vf_0C4();
            if (lv_10 && sub_14C660(bp_8->unk_34->unk_310, (RwV3d *)lv_10, 50.0f))
            {
                var_14 = bp_4;
                var_14->vf_060(bp_8->unk_5C);
            }
        }
    }
    else if ((bp_4->vf_008() || bp_4->vf_024()) && bp_4->unk_28_5)
    {
#ifdef CODFH_SP // shape: block-scoped, sharing a slot with var_60
        RwV3d w28;

#endif
        bp_18 = bp_8->unk_5C;
        w28 = bp_18->unk_450.unk_124;
        w28.y = 0.0f;
        loc1C = RwV3dLength((RwV3d *)&w28)
            + RwV3dLength((RwV3d *)&bp_18->unk_450.unk_130) * 0.31847131f;
        if (loc1C > 0.01f)
            bp_4->unk_28_25 = 1;
    }
    else if (bp_4 && bp_4 != bp_8->unk_5C && RpAtomicGetGeometry(arg_8))
    {
        v2C = bp_8->unk_5C;
        frm_48.type = rpINTERSECTSPHERE;
        for (var_4C = 0; var_4C < 13; var_4C++)
        {
            if (v2C->unk_450.unk_00[var_4C].unk_10 != 2)
                continue;
            v2C->unk_450.sub_149EC0(&frm_48.t.sphere.center, &v2C->unk_450.unk_00[var_4C].unk_00);
            frm_48.t.sphere.radius = v2C->unk_450.unk_00[var_4C].unk_0C;
            bp_8->unk_0C = v2C->unk_450.unk_00[var_4C].unk_00;
            bp_8->unk_00 = frm_48.t.sphere.center;
            bp_8->unk_18 = frm_48.t.sphere.radius;
            sub_1414C0(&bp_8->unk_1C, &v2C->unk_450.unk_00[var_4C].unk_00, &v2C->unk_450.unk_1F0);
            RwV3dSub(&bp_8->unk_28, &bp_8->unk_00, &bp_8->unk_1C);
            if (bp_8->unk_28.x + bp_8->unk_28.y + bp_8->unk_28.z != 0.0f)
                RwV3dNormalize(&bp_8->unk_28, &bp_8->unk_28);
            bp_8->unk_54 = RwFrameGetLTM(RpAtomicGetFrame(arg_8));
            bp_8->unk_34 = &v2C->unk_450;
            bp_8->unk_64 = 0;
            RpAtomicForAllIntersections(arg_8, &frm_48, sub_14AE80, bp_8);
            if (bp_8->unk_64)
            {
                var_50 = bp_8->unk_34->sub_14C6E0(bp_4);
                if (var_50 > 50.0f)
                    sub_6B5F0("VehicleHardCollision", (type_67620 *)(bp_8->unk_5C->vf_098()), 0, 0, 0, 0, 1, 0);
            }
            if (bp_8->unk_64 && (bp_4->unk_2C_7 || bp_4->unk_2C_18) && bp_4->vf_184() >= 4)
            {
#ifdef CODFH_SP // shape: block-scoped, sharing a slot with w28 (SP 0xF4620)
                RwV3d var_60;
                type_149920 x78;

#endif
                var_54 = (type_3DBC78 *)bp_4;
                zero_v3d(&x78.unk_00);
                zero_v3d(&x78.unk_0C);
                var_60 = v2C->unk_450.unk_124;
                RwV3dNormalize(&var_60, &var_60);
                RwV3dScale(&var_60, &var_60, flt_429D54 * var_54->unk_450.unk_24C);
                var_54->unk_450.sub_149920(&x78, &bp_8->unk_68, &var_60);
                var_54->unk_450.sub_149D60(&x78);
            }
        }
    }
    return arg_8;
}

// match: ?sub_14BA00@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x0014BA00
// sp-match: ?sub_14BA00@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000F49A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// sub_14B570's counterpart for a vehicle no player drives: projectiles as
// there; a soldier or player is also pushed out of its box (sub_14B140);
// another vehicle's kind-2 and kind-3 points against its own push the two
// apart (once a step: unk_DF8).
RpAtomic *sub_14BA00(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C, void *arg_10)
{
    RwReal var_9C;
#ifndef CODFH_SP
    RwV3d s98;
#endif
    RwV3d lv_8C;
    RwV3d frm_80;
    RwReal var_74;
    RwReal var70;
    RwInt32 stk_6C;
    RwInt32 q68;
    RwV3d var_64;
    RwMatrix *stk_58;
#ifndef CODFH_SP
    RwV3d loc54;
#endif
    RwInt32 var_48;
    RwMatrix *loc44;
    type_3DBC78 *var_40;
    type_3DBC78 *l3C;
    type_3D3548 *local_38;
    RwV3d local_34;
#ifndef CODFH_SP
    RwV3d var28;
#endif
    RwReal l1C;
    type_3DBC78 *m_18;
    type_3D3548 *ebp_14;
    RwReal *lv_10;
    type_3DDB98 *var_C;
    type_14A5E0 *bp_8;
    type_3D3548 *bp_4;

    bp_8 = (type_14A5E0 *)arg_10;
    bp_4 = sub_FB960(arg_8);
    if (!bp_4)
        return arg_8;
    if (bp_4->unk_2C_21 && bp_4->unk_28_2)
    {
        var_C = (type_3DDB98 *)bp_4;
        if (!var_C->unk_3D8.sub_D4910())
        {
            lv_10 = bp_4->vf_0C4();
            if (lv_10 && sub_14C660(bp_8->unk_34->unk_310, (RwV3d *)lv_10, 50.0f))
            {
                ebp_14 = bp_4;
                ebp_14->vf_060(bp_8->unk_5C);
            }
        }
    }
    else if ((bp_4->vf_008() || bp_4->vf_024()) && bp_4->unk_28_5)
    {
#ifdef CODFH_SP // shape: block-scoped, sharing a slot
        RwV3d var28;

#endif
        m_18 = bp_8->unk_5C;
        var28 = m_18->unk_450.unk_124;
        var28.y = 0.0f;
        l1C = RwV3dLength((RwV3d *)&var28)
            + RwV3dLength((RwV3d *)&m_18->unk_450.unk_130) * 0.31847131f;
        if (l1C > 0.01f)
            bp_4->unk_28_25 = 1;
        if (bp_4->vf_008())
            sub_14B140(bp_8, bp_4, 0);
    }
    else if (bp_4 && bp_4 != bp_8->unk_5C)
    {
        if (!bp_4->unk_2C_7 && !bp_4->unk_2C_18)
            return arg_8;
        var_40 = (type_3DBC78 *)bp_4;
        l3C = bp_8->unk_5C;
        if (l3C->unk_DF8)
            return arg_8;
        var_48 = 0;
        local_38 = sub_1745A0(0);
        if (local_38 && ((type_10F710 *)local_38)->unk_19D0 == 5 && local_38->vf_200() == var_40)
            var_48 = 1;
        loc44 = &var_40->unk_450.unk_170;
        stk_58 = &l3C->unk_450.unk_170;
        for (q68 = 0; q68 < 13; q68++)
        {
            if (l3C->unk_450.unk_00[q68].unk_10 == 2 || l3C->unk_450.unk_00[q68].unk_10 == 3)
            {
                sub_1414C0(&var_64, &l3C->unk_450.unk_00[q68].unk_00, stk_58);
                for (stk_6C = 0; stk_6C < 13; stk_6C++)
                {
                    if (var_40->unk_450.unk_00[stk_6C].unk_10 == 2 || var_40->unk_450.unk_00[stk_6C].unk_10 == 3)
                    {
#ifdef CODFH_SP // shape: block-scoped, sharing a slot
                        RwV3d loc54;

#endif
                        sub_1414C0(&loc54, &var_40->unk_450.unk_00[stk_6C].unk_00, loc44);
                        RwV3dSub(&local_34, &loc54, &var_64);
                        var70 = RwV3dLength((RwV3d *)&local_34)
                            - (l3C->unk_450.unk_00[q68].unk_0C + var_40->unk_450.unk_00[stk_6C].unk_0C);
                        if (var70 < 0.0f)
                        {
                            var_74 = -var70;
                            if (!bp_8->unk_60)
                            {
#ifdef CODFH_SP // shape: block-scoped, sharing a slot
                                RwV3d s98;

#endif
                                s98 = l3C->unk_450.unk_124;
                                s98.y = 0.0f;
                                var_9C = RwV3dLength((RwV3d *)&s98);
                                if (var_74 > var_9C)
                                    var_74 = var_9C;
                            }
                            RwV3dSub(&frm_80, &var_64, &loc54);
                            RwV3dNormalize(&frm_80, &frm_80);
#ifdef CODFH_SP // shape: the scale computed once
                            sp_v3d_scale(&frm_80, &frm_80, var_74 * l3C->unk_450.unk_24C * flt_429D50);
#else
                            RwV3dScale(&frm_80, &frm_80, var_74 * l3C->unk_450.unk_24C * flt_429D50);
#endif
                            l3C->unk_450.sub_149F40(&lv_8C, &l3C->unk_450.unk_00[q68].unk_00);
                            l3C->unk_450.sub_149920(&bp_8->unk_38, &lv_8C, &frm_80);
                            bp_8->unk_50++;
                            l3C->unk_DF8 = 1;
                        }
                    }
                }
            }
        }
    }
    return arg_8;
}

// match: ?sub_14BEE0@type_3DBC78_450@@QAEHPAUtype_3DBC78@@@Z @ 0x0014BEE0
// sp-match: ?sub_14BEE0@type_3DBC78_450@@QAEHPAUtype_3DBC78@@@Z @ 0x000F4D10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The vehicle arg_0's collisions with other entities: the player pushed out
// of its box, then its atomics searched in each section's world within 600
// (or its radius and 150) by sub_14B570 (a player drives) or sub_14BA00;
// the pushes gathered are averaged and applied. Whether there were any.
RwInt32 type_3DBC78_450::sub_14BEE0(type_3DBC78 *arg_0)
{
    RwReal var_A4;
    type_4E5D30 *lcl_A0;
    RwInt32 ebp_9C;
    type_14A5E0 local_98;
    type_3D3548 *var_20;
    RpIntersection l1C;

    l1C.type = rpINTERSECTSPHERE;
    l1C.t.sphere.center = RwFrameGetLTM(arg_0->get_unk_340())->pos;
    l1C.t.sphere.radius = 600.0f;
    if (arg_0->unk_4C > 600.0f)
        l1C.t.sphere.radius = arg_0->unk_4C + 150.0f;
    local_98.unk_5C = arg_0;
    zero_v3d(&local_98.unk_38.unk_00);
    zero_v3d(&local_98.unk_38.unk_0C);
    local_98.unk_50 = 0;
    local_98.unk_60 = unk_2A0;
    local_98.unk_34 = this;
    var_20 = sub_1745A0(0);
    if (var_20)
        sub_14B140(&local_98, var_20, 1);
    for (ebp_9C = 0; ebp_9C < 4; ebp_9C++)
    {
        lcl_A0 = &dword_4E5D30[ebp_9C];
        if (lcl_A0->get_unk_00() && lcl_A0->get_unk_28())
        {
            if (local_98.unk_60)
                RpWorldForAllAtomicIntersections(lcl_A0->get_unk_28(), &l1C, sub_14B570, &local_98);
            else
                RpWorldForAllAtomicIntersections(lcl_A0->get_unk_28(), &l1C, sub_14BA00, &local_98);
        }
    }
    if (local_98.unk_50)
    {
        var_A4 = 1.0f / (RwReal)local_98.unk_50;
        RwV3dScale(&local_98.unk_38.unk_00, &local_98.unk_38.unk_00, var_A4);
        RwV3dScale(&local_98.unk_38.unk_0C, &local_98.unk_38.unk_0C, var_A4);
        sub_149D60(&local_98.unk_38);
    }
    else
    {
        sub_14C6E0(0);
    }
    return local_98.unk_50 > 0;
}

// match: ?sub_14C140@type_3DBC78_450@@QAEMXZ @ 0x0014C140
// sp-match: ?sub_14C140@type_3DBC78_450@@QAEMXZ @ 0x000F32E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal type_3DBC78_450::sub_14C140()
{
    RwReal var_8;
    RwReal l4;

    l4 = RwV3dLength((RwV3d *)&unk_124) * 2160.0f / 1618.4615f;
    var_8 = RwV3dDotProduct(&unk_124, &unk_170.at);
    if (var_8 < 0.0f)
        l4 = -l4;
    return l4;
}

// match: ?sub_14C1D0@type_3DBC78_450@@QAEXM@Z @ 0x0014C1D0
// sp-match: ?sub_14C1D0@type_3DBC78_450@@QAEXM@Z @ 0x000F3330
void type_3DBC78_450::sub_14C1D0(RwReal arg_0)
{
    RwV3dNormalize(&unk_124, &unk_124);
    RwV3dScale(&unk_124, &unk_124, arg_0 * 1618.4615f / 2160.0f);
}

// match: ?sub_14C270@type_3DBC78_450@@QAEXM@Z @ 0x0014C270
// sp-match: ?sub_14C270@type_3DBC78_450@@QAEXM@Z @ 0x000F3380
// Sets the cruise speed arg_0: slowing down halves the throttle; a speed of
// (about) zero drops the cruise and the throttle.
void type_3DBC78_450::sub_14C270(RwReal arg_0)
{
    if (arg_0 > 0.01f || arg_0 < -0.01f)
    {
        if (unk_26C - 0.1f > arg_0)
        {
            unk_240 = 0;
            unk_23C *= 0.5f;
        }
        unk_26C = arg_0;
    }
    else
    {
        if (unk_23C != 0.0f)
            unk_244 = 0.0f;
        unk_23C = 0.0f;
        unk_26C = 0.0f;
    }
    unk_270 = 1.0f;
}

// match: ?sub_14C340@type_3DBC78_450@@QAEXXZ @ 0x0014C340
// sp-match: ?sub_14C340@type_3DBC78_450@@QAEXXZ @ 0x000F3430
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Holds the cruise speed (unless it is stopped or held): the throttle
// unk_23C rises or falls by the step (less while it turns), within 2; once
// passed, the speed is set a little under the cruise.
void type_3DBC78_450::sub_14C340()
{
    RwReal var_14;
    RwReal lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    if (unk_230 || unk_234)
        return;
    if (unk_26C > 0.01f || unk_26C < -0.01f)
    {
        lv_10 = sub_14C140();
        bp_8 = unk_26C;
        var_14 = unk_26C * 1.0f;
        var_C = RwV3dLength((RwV3d *)&unk_13C);
        if (var_C > 0.333f)
            var_C = 0.333f;
        var_C = 1.0f - var_C * 3.0f;
        if (var_14 > lv_10)
            unk_23C += 0.02f * unk_350 * var_C;
        else if (var_14 < lv_10)
            unk_23C -= 0.02f * unk_350 * var_C;
        bp_4 = 2.0f;
        if (unk_23C > bp_4)
            unk_23C = bp_4;
        if (unk_23C < -bp_4)
            unk_23C = -bp_4;
        if (bp_8 - lv_10 > 0.0f)
            unk_240 = 1;
        if (unk_240 && lv_10 - (bp_8 - 0.5f) > 0.0f)
            sub_14C1D0(bp_8 - 1.0f);
    }
    else
    {
        unk_23C = 0.0f;
    }
}

// match: ?sub_14C520@type_3DBC78_450@@QAEHPAURwV3d@@@Z @ 0x0014C520
// sp-match: ?sub_14C520@type_3DBC78_450@@QAEHPAURwV3d@@@Z @ 0x000F35C0
RwInt32 type_3DBC78_450::sub_14C520(RwV3d *arg_0)
{
    RwV3d var_C;
    RwV3d var_18;

    sub_149EC0(&var_C, arg_0);
    var_C.y += 1000.0f;
    var_18 = var_C;
    var_18.y = -10000.0f;
    if (!sub_14AD30(&var_C, &var_18, 0))
    {
        sub_149E80(&var_C, arg_0->x + 20.0f, arg_0->y, arg_0->z);
        var_C.y += 1000.0f;
        var_18 = var_C;
        var_18.y = -10000.0f;
        if (sub_14AD30(&var_C, &var_18, 0))
            return 0;
        sub_149E80(&var_C, arg_0->x - 20.0f, arg_0->y, arg_0->z);
        var_C.y += 1000.0f;
        var_18 = var_C;
        var_18.y = -10000.0f;
        if (sub_14AD30(&var_C, &var_18, 0))
            return 0;
        return 1;
    }
    return 0;
}

// match: ?sub_14C660@@YAHPAURwPlane@@PAURwV3d@@M@Z @ 0x0014C660
// sp-match: ?sub_14C660@@YAHPAURwPlane@@PAURwV3d@@M@Z @ 0x000F3700
// Whether the sphere at arg_4 (radius arg_8) is inside the four planes
// arg_0: 0 when it lies more than its radius beyond one.
RwInt32 sub_14C660(RwPlane *arg_0, RwV3d *arg_4, RwReal arg_8)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        if (RwV3dDotProduct(arg_4, &arg_0[var_4].normal) - arg_0[var_4].distance > arg_8)
            return 0;
    }
    return 1;
}

// match: ?sub_14C6E0@type_3DBC78_450@@QAEMPAUtype_3D3548@@@Z @ 0x0014C6E0
// sp-match: ?sub_14C6E0@type_3DBC78_450@@QAEMPAUtype_3D3548@@@Z @ 0x000F3750
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The speed of the entity arg_0 relative to the step: how far it moved
// since it was last touched (restarting when another entity is touched).
RwReal type_3DBC78_450::sub_14C6E0(type_3D3548 *arg_0)
{
    RwV3d *var_8;
    RwFrame *l4;

    if (arg_0)
    {
        l4 = arg_0->get_unk_340();
        if (l4)
        {
            var_8 = &RwFrameGetMatrix(l4)->pos;
            if (unk_2A8 == arg_0)
            {
                RwV3dSub(&unk_2B8, var_8, &unk_2AC);
            }
            else
            {
                zero_v3d(&unk_2B8);
                unk_2A8 = arg_0;
            }
            unk_2AC = *var_8;
        }
    }
    else
    {
        zero_v3d(&unk_2B8);
        unk_2A8 = arg_0;
    }
    return RwV3dLength((RwV3d *)&unk_2B8) / get_deltaTime();
}


// The trigger arg_0's position (its matrix's): a free inline with no
// address. Evidence: the vehicle factory's warning reads each coordinate
// through it, and its frame holds the leftovers of the three expansions.
inline RwV3d *trigger_pos(type_712B0 *arg_0)
{
    return &arg_0->unk_60_m.pos;
}










// Adds arg_0 to its health, up to its full health.




























// (Defined in the class, in types/type_3DBC78.h.)

// (Defined in the class, in types/type_3DBC78.h; emitted here, as the
// vehicle's constructor calls it.)


// (Defined in the class, in type_3DBC78.h; out of line here, with the
// vtable.)































































// sub_1279C0: the blob shadow (game/render.h, whose Direct3D headers clash
// with this unit's; declared here as there).
void sub_1279C0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C, RwReal arg_10,
                RwInt32 arg_14, RwInt32 arg_18);


// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

#ifndef CODFH_SP // single player compiles it with the constructor (unit_155470)
// ?vf_044@type_3DBC78@@UAEXM@Z (folded into the empty body at 0x15FB30)
void type_3DBC78::vf_044(RwReal arg_0)
{
}
#endif

// ?vf_2A4@type_3DBC78@@UAEHH@Z (folded into `return 0` at 0x32260)
RwInt32 type_3DBC78::vf_2A4(RwInt32 arg_0)
{
    return 0;
}

// ?vf_2B0@type_3DBC78@@UAEXXZ (folded into the empty body at 0x1E41C0)
void type_3DBC78::vf_2B0()
{
}

#ifndef CODFH_SP // single player compiles it with the constructor (unit_155470)
// ?vf_2DC@type_3DBC78@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DBC78::vf_2DC()
{
    return 0;
}
#endif

// ?vf_2E0@type_3DBC78@@UAEHXZ (folded into `return 0` at 0x1E4CB0)
RwInt32 type_3DBC78::vf_2E0()
{
    return 0;
}

// ?vf_2F0@type_3DBC78@@UAEHPAUtype_3D3548@@@Z (folded into `return 1` at 0x1F5A00)
// sp-match: ?vf_2F0@type_3DBC78@@UAEHPAUtype_3D3548@@@Z @ 0x000FEC00
RwInt32 type_3DBC78::vf_2F0(type_3D3548 *arg_0)
{
    return 1;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DBC78@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DBC78::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// ?vf_294@type_3DBC78@@UAEXMM@Z (folded into 0x73D90)
void type_3DBC78::vf_294(RwReal arg_0, RwReal arg_4)
{
}

// ?vf_298@type_3DBC78@@UAEXMM@Z (folded into 0x73D90)
void type_3DBC78::vf_298(RwReal arg_0, RwReal arg_4)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DBC78@@SAXPAX@Z (folded into 0x19A750)
void type_3DBC78::operator delete(void * arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DBC78@@SAXPAX0@Z (folded into 0x19A750)
void type_3DBC78::operator delete(void * arg_0, void * arg_4)
{
}

// Whether arg_0 is one of the keys 0 to 2 of its data's model object: the
// gimp vehicle's (type_3DE0E0's vf_058), which /OPT:ICF folded it into
// (0x17F550).
RwInt32 type_3DBC78::vf_058(type_3DF8D8_04 *arg_0)
{
    type_3DF8D8 *var_10;
    GimpVehicleTrigger *var_C;
    type_1908A0 *bp_8;
    type_3DF8D8_04 *bp_4;

    var_C = (GimpVehicleTrigger *)get_unk_34C();
    var_10 = sub_198800(&var_C->unk_C0);
    bp_8 = (type_1908A0 *)((type_3DFE7C *)var_10)->sub_1954D0();
    bp_4 = ((type_3DF9C4 *)bp_8)->sub_1908A0(0);
    if (arg_0->unk_00 == bp_4->unk_00 && arg_0->unk_04 == bp_4->unk_04)
        return 1;
    bp_4 = ((type_3DF9C4 *)bp_8)->sub_1908A0(1);
    if (arg_0->unk_00 == bp_4->unk_00 && arg_0->unk_04 == bp_4->unk_04)
        return 1;
    bp_4 = ((type_3DF9C4 *)bp_8)->sub_1908A0(2);
    if (arg_0->unk_00 == bp_4->unk_00 && arg_0->unk_04 == bp_4->unk_04)
        return 1;
    return 0;
}
