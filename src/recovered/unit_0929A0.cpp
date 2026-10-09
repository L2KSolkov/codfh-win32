// Split from unit_08AB60.cpp at 0x0929A0, where the image starts another object (the collision queries, with the .data at 0x4290C0):
// its .rdata begins at 0x3D5194 with its own copy of the unreferenced 16.666666 every game object
// starts its constants with (PLAN M7).

#include <math.h>
#include "rw/ostypes.h"
#include "rw/rprandom.h"
#include "game/data.h"
#include "types/ccess.h"
#include "types/vec4.h"
#include "types/type_92430.h"
#include "types/type_3D32F8.h"
#include "game/functions.h"
#include "types/type_4E5D30.h"
#include "types/type_4AE70.h"
#include "game/gameloop.h"
#include "rw/rpcollis.h"
#include "types/type_3DAFC8_1DDC.h"
#include "types/AIData.h"
#include "types/type_10F710.h"
#include <xmmintrin.h>
#include "rw/bavector.h"
#include "types/type_3D3548.h"
#include "rws/csystemcommands.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D5194
extern const RwReal flt_3D5194 = 16.666666f;
// 0x004290C0
RwReal dword_4290C0 = 0.65f;
// 0x004290C4
RwReal dword_4290C4 = 0.1f;
// 0x004290C8
RwReal dword_4290C8 = 0.5f;
// 0x004290CC
RwReal flt_4290CC = -0.5f;
// 0x004290D0
RwReal flt_4290D0 = 55.0f;
// 0x004290D4
RwReal flt_4290D4 = 5.0f;
// 0x004290D8
RwReal flt_4290D8 = 40.0f;
// 0x004290DC
RwReal flt_4290DC = 0.42f;
// 0x004290E0
RwReal flt_4290E0 = 40.0f;
// 0x004290E4
RwReal flt_4290E4 = 40.0f;
// 0x004290E8
RwReal flt_4290E8 = 0.7071f;
// 0x004290EC
RwReal flt_4290EC = 0.352f;
// 0x004290F0
RwReal flt_4290F0 = 2.0f;
// 0x004290F4
RwV3d *dword_4290F4[3] = { &dword_4B6768[0], &dword_4B6768[1], &dword_4B6768[2] };
// 0x00429100
RwV3d *dword_429100[3] = { &dword_4B678C[0], &dword_4B678C[1], &dword_4B678C[2] };

// match: ?flt_3D5194@@3MB @ 0x003D5194
// match: ?dword_4290C0@@3MA @ 0x004290C0
// match: ?dword_4290C4@@3MA @ 0x004290C4
// match: ?dword_4290C8@@3MA @ 0x004290C8
// match: ?flt_4290CC@@3MA @ 0x004290CC
// match: ?flt_4290D0@@3MA @ 0x004290D0
// match: ?flt_4290D4@@3MA @ 0x004290D4
// match: ?flt_4290D8@@3MA @ 0x004290D8
// match: ?flt_4290DC@@3MA @ 0x004290DC
// match: ?flt_4290E0@@3MA @ 0x004290E0
// match: ?flt_4290E4@@3MA @ 0x004290E4
// match: ?flt_4290E8@@3MA @ 0x004290E8
// match: ?flt_4290EC@@3MA @ 0x004290EC
// match: ?flt_4290F0@@3MA @ 0x004290F0
// match: ?dword_4290F4@@3PAPAURwV3d@@A @ 0x004290F4
// match: ?dword_429100@@3PAPAURwV3d@@A @ 0x00429100


// match: ?sub_929A0@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000929A0
// match: __real@be99999a @ 0x003D5198
// match: __real@3eaf1aa0 @ 0x003D519C
// match: __real@48f42400 @ 0x003D51A0
// match: ??_C@_02DPKJAMEF@?$CFd?$AA@ @ 0x003D51A4
// match: __real@42960000 @ 0x003D51A8
// match: __real@41800000 @ 0x003D51AC
// match: __real@47435000 @ 0x003D51B0
// sp-match: ?sub_929A0@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000769F0
// sub_948A0's collision world triangle callback: keeps the surface, skips
// a skipped material, gathers the triangle for an entity that asks
// (unk_28_12), finds the triangle's nearest point to the sphere (sub_8F960)
// and, when it is inside the search's ellipsoid, records the hit (a floor
// when the normal is upright enough and the point above unk_48) and pushes
// the frame out along the ellipsoid (only up on a floor), following with
// the sphere. A steep triangle high enough above the frame goes into the
// contact records as in sub_98200.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *sub_929A0(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10)
{
    RwInt32 uFC;
    RwInt32 lF8;
    RwReal zF4;
    RwV3d *stk_F0;
    RwMatrix *stk_EC;
    RwV3d qE8;
    RwV3d lDC;
    RwReal s70;
    RwV3d m_6C;
    RwInt32 stk_60;
    RwReal slot_58;
    RwV3d l54;
    RwReal w48;
    RwV3d loc44;
    RwV3d lcl_38;
    RwReal fp_2C;
    RwInt32 q28;
    RwInt32 frm_24;
    RwV3d t20;
    RwUInt32 ebp_14;
    type_FC000 *slot_C;
    void *bp_8;
    type_93DF0 *bp_4;

    bp_4 = (type_93DF0 *)arg_10;
    bp_8 = ((type_96E30 *)bp_4->unk_00)->unk_10[((type_92540 *)arg_4)->unk_80 +
                                                 ((type_92540 *)arg_4)->unk_04[arg_8->index].unk_06];
    slot_C = sub_FC000(bp_8);
    bp_4->unk_78 = (slot_C->unk_04 & 0xFFFF) == 0xFFFF ? -1 : slot_C->unk_04 & 0xFFFF;
    ebp_14 = slot_C->unk_04 & 0xFFFF0000;
    if (bp_4->unk_74 & ebp_14)
    {
        return arg_8;
    }
    t20 = arg_0->t.sphere.center;
    frm_24 = 0;
    if (bp_4->unk_04->unk_28_12)
    {
        q28 = dword_4B25BC;
        if (q28 < 350)
        {
            q28 = q28 * 3;
            dword_4B25C0[q28] = *arg_8->vertices[0];
            dword_4B25C0[q28 + 1] = *arg_8->vertices[1];
            dword_4B25C0[q28 + 2] = *arg_8->vertices[2];
            dword_4B25BC++;
        }
    }
    fp_2C = sub_8F960(arg_8->vertices, &arg_8->normal, &t20);
    RwV3dSubMacro(&lcl_38, &arg_0->t.sphere.center, &t20);
    loc44.x = lcl_38.x * lcl_38.x * bp_4->unk_38[0];
    loc44.y = lcl_38.y * lcl_38.y * bp_4->unk_38[1];
    loc44.z = lcl_38.z * lcl_38.z * bp_4->unk_38[2];
    w48 = loc44.x + loc44.y + loc44.z;
    l54.x = l54.z = 0.0f;
    l54.y = 1.0f;
    slot_58 = RwV3dDotProductMacro(&l54, &arg_8->normal);
    stk_60 = lcl_38.y > 0.0f ? 1 : 0;
    if (lcl_38.y > bp_4->unk_48 && slot_58 > 0.342f)
    {
        frm_24 = 1;
    }
    if (w48 < 1.0f)
    {
        if (frm_24)
        {
            *bp_4->unk_50 = 1;
        }
        bp_4->unk_24 = fp_2C;
        bp_4->unk_2C_v = t20;
        bp_4->unk_44 = w48;
        bp_4->unk_60 = 1;
        if (stk_60 && slot_58 > 0.342f)
        {
            bp_4->unk_64 = 1;
        }
        else if (!frm_24)
        {
            bp_4->unk_68 = 1;
        }
        RwV3dSubMacro(&m_6C, &arg_0->t.sphere.center, &bp_4->unk_2C_v);
        // The divisor goes first (fld, fdivr): only a comma expression (a
        // macro's, most likely) gives that order; every plain form loads 1.0
        // first.
        s70 = 1.0f / (0, bp_4->unk_44);
        do
        {
            __m128 var_A0 = _mm_set_ss(s70);
            __m128 var_D0 = _mm_sqrt_ss(var_A0);
            _mm_store_ss(&s70, var_D0);
        } while (0);
        lDC.x = m_6C.x * s70;
        lDC.y = m_6C.y * s70;
        lDC.z = m_6C.z * s70;
        RwV3dSubMacro(&qE8, &lDC, &m_6C);
        if (frm_24)
        {
            qE8.x = 0.0f;
            qE8.z = 0.0f;
        }
        RwFrameTranslate(bp_4->unk_14, &qE8, rwCOMBINEPOSTCONCAT);
        RwFrameUpdateObjects(bp_4->unk_14);
        stk_EC = RwFrameGetLTM(bp_4->unk_14);
        arg_0->t.sphere.center = stk_EC->pos;
        if (bp_4->unk_6C)
        {
#ifdef CODFH_SP // shape: the offset added component by component (center loaded first for x, SP 0x76CF7)
            arg_0->t.sphere.center.x += bp_4->unk_6C->x;
            arg_0->t.sphere.center.y += bp_4->unk_6C->y;
            arg_0->t.sphere.center.z += bp_4->unk_6C->z;
#else
            RwV3dAddMacro(&arg_0->t.sphere.center, &arg_0->t.sphere.center, bp_4->unk_6C);
#endif
        }
    }
    stk_F0 = &RwFrameGetLTM(bp_4->unk_14)->pos;
    zF4 = t20.y - stk_F0->y;
    if (bp_4->unk_7C && slot_58 < 0.3f && slot_58 > -0.3f && !frm_24 && zF4 > flt_4290D0)
    {
        lF8 = 0;
        loc44.x = lcl_38.x * lcl_38.x * bp_4->unk_7C->unk_0C.x;
        loc44.y = lcl_38.y * lcl_38.y * bp_4->unk_7C->unk_0C.y;
        loc44.z = lcl_38.z * lcl_38.z * bp_4->unk_7C->unk_0C.z;
        w48 = loc44.x + loc44.y + loc44.z;
        if (w48 < 1.0f && sub_92FB0(arg_8->vertices[0], arg_8->vertices[1], arg_8->vertices[2]))
        {
            lF8 = 1;
        }
        if (lF8)
        {
            uFC = 2;
        }
        else
        {
            uFC = 1;
        }
        sub_992B0(uFC, &t20, bp_4->unk_7C, &arg_0->t.sphere.center, (type_30B90_48 *)arg_8);
    }
    return arg_8;
}
// Whether the heights of arg_0, arg_4 and arg_8 span 50 or more. The image
// compares the heights on the FPU (fld, fld, fcompp) and moves the chosen
// one through it (fld, fstp); double comparisons of float-of-double values
// reproduce both, where plain float ones compare with fcomp and move with
// mov.
// match: ?sub_92FB0@@YAHPAURwV3d@@00@Z @ 0x00092FB0
// sp-match: ?sub_92FB0@@YAHPAURwV3d@@00@Z @ 0x00074370
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_92FB0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

#ifdef CODFH_SP
    // shape: plain float compares (fcomp memory operands at SP 0x74370)
    var_C = arg_0->y > arg_4->y ? (arg_0->y > arg_8->y ? arg_0->y : arg_8->y)
                                : (arg_4->y > arg_8->y ? arg_4->y : arg_8->y);
    bp_4 = arg_0->y < arg_4->y ? (arg_0->y < arg_8->y ? arg_0->y : arg_8->y)
                               : (arg_4->y < arg_8->y ? arg_4->y : arg_8->y);
#else
    var_C = (RwDouble)arg_0->y > (RwDouble)arg_4->y ? ((RwDouble)arg_0->y > (RwDouble)arg_8->y ? (RwReal)(RwDouble)arg_0->y : (RwReal)(RwDouble)arg_8->y)
                                : ((RwDouble)arg_4->y > (RwDouble)arg_8->y ? (RwReal)(RwDouble)arg_4->y : (RwReal)(RwDouble)arg_8->y);
    bp_4 = (RwDouble)arg_0->y < (RwDouble)arg_4->y ? ((RwDouble)arg_0->y < (RwDouble)arg_8->y ? (RwReal)(RwDouble)arg_0->y : (RwReal)(RwDouble)arg_8->y)
                                : ((RwDouble)arg_4->y < (RwDouble)arg_8->y ? (RwReal)(RwDouble)arg_4->y : (RwReal)(RwDouble)arg_8->y);
#endif
    bp_8 = fabs(var_C - bp_4);
    if (bp_8 < 50.0f)
    {
        return 0;
    }
    return 1;
}
// match: ?sub_930F0@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000930F0
// sp-match: ?sub_930F0@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00076DF0
// sub_929A0 with the height test only for a triangle inside the contact
// ellipsoid (sub_950C0's collision world callback).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *sub_930F0(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10)
{
    RwInt32 uFC;
    RwReal lF8;
    RwV3d *zF4;
    RwInt32 stk_F0;
    RwMatrix *stk_EC;
    RwV3d qE8;
    RwV3d lDC;
    RwReal s70;
    RwV3d m_6C;
    RwInt32 stk_60;
    RwReal slot_58;
    RwV3d l54;
    RwReal w48;
    RwV3d loc44;
    RwV3d lcl_38;
    RwReal fp_2C;
    RwInt32 q28;
    RwInt32 frm_24;
    RwV3d t20;
    RwUInt32 ebp_14;
    type_FC000 *slot_C;
    void *bp_8;
    type_93DF0 *bp_4;

    bp_4 = (type_93DF0 *)arg_10;
    bp_8 = ((type_96E30 *)bp_4->unk_00)->unk_10[((type_92540 *)arg_4)->unk_80 +
                                                 ((type_92540 *)arg_4)->unk_04[arg_8->index].unk_06];
    slot_C = sub_FC000(bp_8);
    bp_4->unk_78 = (slot_C->unk_04 & 0xFFFF) == 0xFFFF ? -1 : slot_C->unk_04 & 0xFFFF;
    ebp_14 = slot_C->unk_04 & 0xFFFF0000;
    if (bp_4->unk_74 & ebp_14)
    {
        return arg_8;
    }
    t20 = arg_0->t.sphere.center;
    frm_24 = 0;
    if (bp_4->unk_04->unk_28_12)
    {
        q28 = dword_4B25BC;
        if (q28 < 350)
        {
            q28 = q28 * 3;
            dword_4B25C0[q28] = *arg_8->vertices[0];
            dword_4B25C0[q28 + 1] = *arg_8->vertices[1];
            dword_4B25C0[q28 + 2] = *arg_8->vertices[2];
            dword_4B25BC++;
        }
    }
    fp_2C = sub_8F960(arg_8->vertices, &arg_8->normal, &t20);
    RwV3dSubMacro(&lcl_38, &arg_0->t.sphere.center, &t20);
    loc44.x = lcl_38.x * lcl_38.x * bp_4->unk_38[0];
    loc44.y = lcl_38.y * lcl_38.y * bp_4->unk_38[1];
    loc44.z = lcl_38.z * lcl_38.z * bp_4->unk_38[2];
    w48 = loc44.x + loc44.y + loc44.z;
    l54.x = l54.z = 0.0f;
    l54.y = 1.0f;
    slot_58 = RwV3dDotProductMacro(&l54, &arg_8->normal);
    stk_60 = lcl_38.y > 0.0f ? 1 : 0;
    if (lcl_38.y > bp_4->unk_48 && slot_58 > 0.342f)
    {
        frm_24 = 1;
    }
    if (w48 < 1.0f)
    {
        if (frm_24)
        {
            *bp_4->unk_50 = 1;
        }
        bp_4->unk_24 = fp_2C;
        bp_4->unk_2C_v = t20;
        bp_4->unk_44 = w48;
        bp_4->unk_60 = 1;
        if (stk_60 && slot_58 > 0.342f)
        {
            bp_4->unk_64 = 1;
        }
        else if (!frm_24)
        {
            bp_4->unk_68 = 1;
        }
        RwV3dSubMacro(&m_6C, &arg_0->t.sphere.center, &bp_4->unk_2C_v);
        // The divisor goes first (fld, fdivr): only a comma expression (a
        // macro's, most likely) gives that order; every plain form loads 1.0
        // first.
        s70 = 1.0f / (0, bp_4->unk_44);
        do
        {
            __m128 var_A0 = _mm_set_ss(s70);
            __m128 var_D0 = _mm_sqrt_ss(var_A0);
            _mm_store_ss(&s70, var_D0);
        } while (0);
        lDC.x = m_6C.x * s70;
        lDC.y = m_6C.y * s70;
        lDC.z = m_6C.z * s70;
        RwV3dSubMacro(&qE8, &lDC, &m_6C);
        if (frm_24)
        {
            qE8.x = 0.0f;
            qE8.z = 0.0f;
        }
        RwFrameTranslate(bp_4->unk_14, &qE8, rwCOMBINEPOSTCONCAT);
        RwFrameUpdateObjects(bp_4->unk_14);
        stk_EC = RwFrameGetLTM(bp_4->unk_14);
        arg_0->t.sphere.center = stk_EC->pos;
        if (bp_4->unk_6C)
        {
#ifdef CODFH_SP // shape: the offset added component by component (center loaded first for x, SP 0x770FF)
            arg_0->t.sphere.center.x += bp_4->unk_6C->x;
            arg_0->t.sphere.center.y += bp_4->unk_6C->y;
            arg_0->t.sphere.center.z += bp_4->unk_6C->z;
#else
            RwV3dAddMacro(&arg_0->t.sphere.center, &arg_0->t.sphere.center, bp_4->unk_6C);
#endif
        }
    }
    if (bp_4->unk_7C && slot_58 < 0.3f && slot_58 > -0.3f && !frm_24)
    {
        stk_F0 = 0;
        loc44.x = lcl_38.x * lcl_38.x * bp_4->unk_7C->unk_0C.x;
        loc44.y = lcl_38.y * lcl_38.y * bp_4->unk_7C->unk_0C.y;
        loc44.z = lcl_38.z * lcl_38.z * bp_4->unk_7C->unk_0C.z;
        w48 = loc44.x + loc44.y + loc44.z;
        if (w48 < 1.0f)
        {
            zF4 = &RwFrameGetLTM(bp_4->unk_14)->pos;
            lF8 = t20.y - zF4->y;
            if (lF8 > flt_4290D0 && sub_92FB0(arg_8->vertices[0], arg_8->vertices[1], arg_8->vertices[2]))
            {
                stk_F0 = 1;
            }
        }
        if (stk_F0)
        {
            uFC = 2;
        }
        else
        {
            uFC = 1;
        }
        sub_992B0(uFC, &t20, bp_4->unk_7C, &arg_0->t.sphere.center, (type_30B90_48 *)arg_8);
    }
    return arg_8;
}
// match: ?sub_93700@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x00093700
// sp-match: ?sub_93700@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x000772D0
// sub_929A0 for an atomic's own triangles (the query arg_C, a type_93DF0):
// the triangle is taken into the world by the atomic's matrix (unk_18,
// into dword_4B6768) first, and with unk_90 set it is only gathered
// (sub_93DF0). A hit on an entity that is not hit by explosions (or a
// non-collision atomic) ends the search; a floor records the entity and
// atomic stood on (unk_54, unk_58) and the nearest hit (unk_94 to unk_A4)
// is kept. Unless unk_B0 is set, the frame is pushed out, through its
// parent's inverse (unk_20) when it has one.
RpCollisionTriangle *sub_93700(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8, void *arg_C)
{
    type_93DF0 *var_4;
    RwV3d var_10;
    RwV3d var_34[3];
    RwV3d var_40;
    RwInt32 var_44;
    RwReal var_48;
    RwV3d var_54;
    RwInt32 var_58;
    RwV3d var_64;
    RwReal var_68;
    RwV3d var_74;
    RwReal var_78;
    RwInt32 var_80;
    RwV3d var_8C;
    RwReal var_90;
    RwV3d var_FC;
    RwV3d var_108;
    RwV3d *var_10C;
    RwReal var_110;
    RwInt32 var_114;
    RwInt32 var_118;
    RpCollisionTriangle var_140;

    var_4 = (type_93DF0 *)arg_C;
    var_10 = arg_0->t.sphere.center;
    var_34[0] = *arg_4->vertices[0];
    var_34[1] = *arg_4->vertices[1];
    var_34[2] = *arg_4->vertices[2];
    sub_141590(dword_4B6768, var_34, 3, var_4->unk_18);
    sub_141320(&var_40, &arg_4->normal, var_4->unk_1C);
    var_44 = 0;
    if (var_4->unk_90)
    {
        var_4->unk_5C = 1;
        sub_93DF0(dword_4290F4, &var_40, var_4, arg_0);
        return arg_4;
    }
    var_48 = sub_8F960(dword_4290F4, &var_40, &var_10);
    RwV3dSubMacro(&var_54, &arg_0->t.sphere.center, &var_10);
    var_58 = 0;
    if (var_4->unk_08)
    {
        if (var_4->unk_08->unk_28_2)
        {
            var_58 = 1;
        }
    }
    else if (RWS::RpAtomicCollisionProperties::GetIsSolid(*var_4->unk_10))
    {
        var_58 = 1;
    }
    var_64.x = var_54.x * var_54.x * var_4->unk_38[0];
    var_64.y = var_54.y * var_54.y * var_4->unk_38[1];
    var_64.z = var_54.z * var_54.z * var_4->unk_38[2];
    var_68 = var_64.x + var_64.y + var_64.z;
    var_74.x = var_74.z = 0.0f;
    var_74.y = 1.0f;
    var_78 = RwV3dDotProductMacro(&var_74, &var_40);
    if (var_58 && var_54.y > var_4->unk_48 && var_78 > 0.342f)
    {
        var_44 = 1;
    }
    var_80 = var_54.y > 0.0f ? 1 : 0;
    if (var_68 < 1.0f)
    {
        var_4->unk_5C = 1;
        if (var_4->unk_10)
        {
            if (!var_58)
            {
                return 0;
            }
            if (var_44)
            {
                *var_4->unk_50 = 1;
                var_4->unk_54 = var_4->unk_08;
                var_4->unk_58 = var_4->unk_10;
            }
            if (var_48 < var_4->unk_94)
            {
                var_4->unk_94 = var_48;
                var_4->unk_98_v = var_40;
                var_4->unk_A4_v = var_10;
            }
            var_4->unk_24 = var_48;
            var_4->unk_2C_v = var_10;
            var_4->unk_44 = var_68;
            var_4->unk_60 = 1;
            if (var_80 && var_78 > 0.342f)
            {
                var_4->unk_64 = 1;
            }
            else if (!var_44)
            {
                var_4->unk_68 = 1;
            }
            if (!var_4->unk_B0)
            {
                RwV3dSubMacro(&var_8C, &arg_0->t.sphere.center, &var_4->unk_2C_v);
                // The divisor goes first (fld, fdivr), as in sub_929A0.
                var_90 = 1.0f / (0, var_4->unk_44);
                do
                {
                    __m128 var_C0 = _mm_set_ss(var_90);
                    __m128 var_F0 = _mm_sqrt_ss(var_C0);
                    _mm_store_ss(&var_90, var_F0);
                } while (0);
                var_FC.x = var_8C.x * var_90;
                var_FC.y = var_8C.y * var_90;
                var_FC.z = var_8C.z * var_90;
                RwV3dSubMacro(&var_108, &var_FC, &var_8C);
                if (var_44)
                {
                    var_108.x = 0.0f;
                    var_108.z = 0.0f;
                }
                if (RwFrameGetParent(var_4->unk_14))
                {
                    sub_141320(&var_108, &var_108, var_4->unk_20);
                }
                RwFrameTranslate(var_4->unk_14, &var_108, rwCOMBINEPOSTCONCAT);
                RwFrameUpdateObjects(var_4->unk_14);
                arg_0->t.sphere.center = RwFrameGetLTM(var_4->unk_14)->pos;
                if (var_4->unk_6C)
                {
                    RwV3dAddMacro(&arg_0->t.sphere.center, &arg_0->t.sphere.center, var_4->unk_6C);
                }
            }
        }
    }
    var_10C = &RwFrameGetLTM(var_4->unk_14)->pos;
    var_110 = var_10.y - var_10C->y;
    if (var_4->unk_7C && var_40.y < 0.3f && var_40.y > -0.3f && !var_44 && var_110 > flt_4290D0)
    {
        var_114 = 0;
        var_64.x = var_54.x * var_54.x * var_4->unk_7C->unk_0C.x;
        var_64.y = var_54.y * var_54.y * var_4->unk_7C->unk_0C.y;
        var_64.z = var_54.z * var_54.z * var_4->unk_7C->unk_0C.z;
        var_68 = var_64.x + var_64.y + var_64.z;
        if (var_68 < 1.0f && sub_92FB0(&dword_4B6768[0], &dword_4B6768[1], &dword_4B6768[2]))
        {
            var_114 = 1;
        }
        if (var_114)
        {
            var_118 = 2;
        }
        else
        {
            var_118 = 1;
        }
        var_140.index = arg_4->index;
        var_140.normal = var_40;
        var_140.vertices[0] = &dword_4B6768[0];
        var_140.vertices[1] = &dword_4B6768[1];
        var_140.vertices[2] = &dword_4B6768[2];
        sub_992B0(var_118, &var_10, var_4->unk_7C, &arg_0->t.sphere.center, (type_30B90_48 *)&var_140);
    }
    return arg_4;
}
// match: ?sub_93DF0@@YAXPAPAURwV3d@@PAU1@PAUtype_93DF0@@PAURpIntersection@@@Z @ 0x00093DF0
// sp-match: ?sub_93DF0@@YAXPAPAURwV3d@@PAU1@PAUtype_93DF0@@PAURpIntersection@@@Z @ 0x00077200
void sub_93DF0(RwV3d **arg_0, RwV3d *arg_4, type_93DF0 *arg_8, RpIntersection *arg_C)
{
    RwInt32 var_4;

    var_4 = dword_4B25BC;
    if (var_4 >= 350)
    {
        sub_96680(arg_8, arg_C, arg_8->unk_84, arg_8->unk_80, arg_8->unk_8C);
        var_4 = 0;
        dword_4B25BC = var_4;
    }
    var_4 *= 3;
    dword_4B25C0[var_4] = *arg_0[0];
    dword_4B25C0[var_4 + 1] = *arg_0[1];
    dword_4B25C0[var_4 + 2] = *arg_0[2];
    dword_4B56F8[dword_4B25BC] = *arg_4;
    dword_4B25BC++;
    dword_4B6760++;
}
// match: ?sub_93F00@@YAPAURpWorldSector@@PAURpIntersection@@PAU1@PAX@Z @ 0x00093F00
// sp-match: ?sub_93F00@@YAPAURpWorldSector@@PAURpIntersection@@PAU1@PAX@Z @ 0x00074410
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpWorldSector *sub_93F00(RpIntersection *arg_0, RpWorldSector *arg_4, void *arg_8)
{
    RwReal var_2C;
    RwReal var_28;
    RwReal ebp_24;
    RwReal var_20;
    RwInt32 l1C;
    type_8F3E0 *m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    type_8F8C0 *bp_8;
    type_93F00 *bp_4;

    bp_4 = (type_93F00 *)arg_8;
    bp_8 = (type_8F8C0 *)arg_4;
    if (bp_8->unk_10 && (bp_8->unk_10 & 0xFFFFFF00) == 0xFFFFFF00)
    {
        var_C = bp_8->unk_10 & 0xFF;
        for (lv_10 = 0; lv_10 < var_C; lv_10++)
        {
            l1C = (lv_10 & 3) << 3;
            ebp_14 = bp_8->unk_14[lv_10 >> 2];
            ebp_14 = (ebp_14 >> l1C) & 0xFF;
            m_18 = dword_4B2550.get_zone(ebp_14);
            if (m_18 && dword_4B2550.sub_8F3E0(m_18, (type_8BEC0 *)arg_0))
            {
                var_2C = m_18->unk_00[1].unk_00 - m_18->unk_00[0].unk_00;
                var_28 = m_18->unk_00[1].unk_04 - m_18->unk_00[0].unk_04;
                var_20 = m_18->unk_00[1].unk_08 - m_18->unk_00[0].unk_08;
                ebp_24 = fabs(var_2C * var_28 * var_20);
                if (ebp_24 < bp_4->unk_00)
                {
                    bp_4->unk_00 = ebp_24;
                    bp_4->unk_04 = m_18;
                }
            }
        }
    }
    return arg_4;
}
// match: ?sub_94060@@YAXPAUtype_3D3548@@@Z @ 0x00094060
// sp-match: ?sub_94060@@YAXPAUtype_3D3548@@@Z @ 0x000744E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_94060(type_3D3548 *arg_0)
{
#ifndef CODFH_SP
    type_4E5D30 *bp_84;
    RwInt32 var80;
    type_93F00 local_7C;
    RpIntersection var_70;
    RwReal y54;
    RwReal stk_50;
    RwReal local_4C;
    RwReal m_48;
    RwInt32 var44;
    type_8F3E0 *m_40;
    RwInt32 p3C;
    RwInt32 var_38;
    RwInt32 l34;
    type_94060_tie *var30;
    type_8F8C0 *ebp_2C;
    type_94060_link *lcl_28;
    RwReal frm_24;
    type_94060_link *var_20;
    type_8F3E0 *l1C;
    type_94060_link *m_18;
    RwV3d ebp_14;
    RwReal bp_8;
    type_94060_atomic *bp_4;
#endif

    if (!dword_4B6764)
    {
#ifdef CODFH_SP
        RwReal y54;
        RwReal stk_50;
        RwReal local_4C;
        RwReal m_48;
        RwInt32 var44;
        type_8F3E0 *m_40;
        RwInt32 p3C;
        RwInt32 var_38;
        RwInt32 l34;
        type_94060_tie *var30;
        type_8F8C0 *ebp_2C;
        type_94060_link *lcl_28;
        RwReal frm_24;
        type_94060_link *var_20;
        type_8F3E0 *l1C;
        type_94060_link *m_18;
        RwV3d ebp_14;
        RwReal bp_8;
        type_94060_atomic *bp_4;
#endif
        bp_4 = (type_94060_atomic *)arg_0->Clump_ResolvePrimaryAtomic();
        if (bp_4)
        {
            bp_8 = RwV3dDotProductMacro(&bp_4->unk_2C, &bp_4->unk_2C);
            if (bp_8 != 0.0f)
            {
                ebp_14 = *arg_0->sub_CD550();
#ifdef CODFH_SP
                // shape: height adjusted after the search setup (SP 0x744E0 loads the list head first)
                frm_24 = 1e37f;
                l1C = 0;
                m_18 = bp_4->unk_64.unk_00;
                var_20 = &bp_4->unk_64;
                ebp_14.y += 8.0f;
#else
                ebp_14.y += 8.0f;
                frm_24 = 1e37f;
                l1C = 0;
                m_18 = bp_4->unk_64.unk_00;
                var_20 = &bp_4->unk_64;
#endif
                while (m_18 != var_20)
                {
                    var30 = (type_94060_tie *)((RwUInt8 *)m_18 - 0xC);
                    lcl_28 = m_18->unk_00;
                    ebp_2C = (type_8F8C0 *)var30->unk_14;
                    if (ebp_2C->unk_10 && (ebp_2C->unk_10 & 0xFFFFFF00) == 0xFFFFFF00)
                    {
                        l34 = ebp_2C->unk_10 & 0xFF;
                        for (var_38 = 0; var_38 < l34; var_38++)
                        {
                            var44 = (var_38 & 3) << 3;
                            p3C = ebp_2C->unk_14[var_38 >> 2];
                            p3C = (p3C >> var44) & 0xFF;
                            m_40 = dword_4B2550.get_zone(p3C);
                            if (m_40 && dword_4B2550.sub_8F3E0(m_40, (type_8BEC0 *)&ebp_14))
                            {
                                y54 = m_40->unk_00[1].unk_00 - m_40->unk_00[0].unk_00;
                                stk_50 = m_40->unk_00[1].unk_04 - m_40->unk_00[0].unk_04;
                                m_48 = m_40->unk_00[1].unk_08 - m_40->unk_00[0].unk_08;
                                local_4C = fabs(y54 * stk_50 * m_48);
                                if (local_4C < frm_24)
                                {
                                    frm_24 = local_4C;
                                    l1C = m_40;
                                }
                            }
                        }
                    }
                    m_18 = lcl_28;
                }
                if (l1C)
                {
                    arg_0->unk_90.sub_8E670(l1C);
                }
                else
                {
                    arg_0->unk_90.sub_8E670(&dword_4E5BE0);
                }
                arg_0->unk_90.sub_8E750();
            }
        }
    }
    else
    {
#ifdef CODFH_SP
        // shape: block-scoped locals share the frame with the other branch's (SP 0x744E0)
        type_4E5D30 *bp_84;
        RwInt32 var80;
        type_93F00 local_7C;
        RpIntersection var_70;
#endif
        var_70.type = rpINTERSECTSPHERE;
        var_70.t.sphere.center = *arg_0->sub_CD550();
        var_70.t.sphere.center.y += 8.0f;
        if (arg_0->unk_4C >= arg_0->unk_48)
        {
            var_70.t.sphere.radius = arg_0->unk_4C;
        }
        else
        {
            var_70.t.sphere.radius = arg_0->unk_48;
        }
        local_7C.unk_00 = 1e37f;
        local_7C.unk_04 = 0;
        local_7C.unk_08 = arg_0;
        for (var80 = 0; var80 < 4; var80++)
        {
            bp_84 = &dword_4E5D30[var80];
            if (bp_84->get_unk_00() && bp_84->get_unk_28())
            {
                RpWorldForAllWorldSectorIntersections(bp_84->get_unk_28(), &var_70, sub_93F00, &local_7C);
            }
        }
        if (local_7C.unk_04)
        {
            arg_0->unk_90.sub_8E670(local_7C.unk_04);
        }
        else
        {
            arg_0->unk_90.sub_8E670(&dword_4E5BE0);
        }
        arg_0->unk_90.sub_8E750();
    }
}
// match: ?sub_943E0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000943E0
// sp-match: ?sub_943E0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00077810
// sub_946B0 without its second collision test, for sub_948A0's sphere
// search: once a hit is reported, an entity of contact kind (unk_2C & 0x30,
// not skipped by bit 9) near enough is also sorted into the search's contact
// records (unk_7C, sub_9A2D0).
RpAtomic *sub_943E0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10)
{
    type_93DF0 *var_4;
    type_3D3548 *var_8;
    RwInt32 var_C;
    RwUInt32 var_10;
    RwMatrix var_50;
    RwMatrix var_90;
    RwReal var_94;
    RwReal var_98;
    AIData *var_9C;

    if (sub_FB9C0(arg_8) & 8)
    {
        return arg_8;
    }
    var_4 = (type_93DF0 *)arg_10;
    var_8 = sub_FB960(arg_8);
    if (var_4->unk_04 && var_8)
    {
        var_C = 0;
        if (var_4->unk_04 != var_8 && var_8->unk_28_2)
        {
            var_10 = var_8->unk_2C & 0x3FFFFF0;
            if (var_4->unk_04->unk_30 & var_10)
            {
                var_C = 1;
            }
        }
    }
    else
    {
        var_C = 1;
    }
    if (var_C)
    {
        var_4->unk_18 = RwFrameGetLTM(RpAtomicGetFrame(arg_8));
        if (var_4->unk_04)
        {
            var_4->unk_1C = &var_50;
            RwMatrixOrthoNormalize(var_4->unk_1C, var_4->unk_18);
            var_4->unk_20 = &var_90;
            RwMatrixInvert(var_4->unk_20, var_4->unk_18);
            var_4->unk_08 = var_8;
            var_4->unk_10 = arg_8;
            var_4->unk_5C = 0;
            var_4->unk_08->Collision_DispatchAtomicIntersectionsBySelectorFlag(arg_8, arg_0,
                                                                              (type_93700 *)var_4);
        }
        var_4->unk_08 = var_8;
        var_4->unk_10 = arg_8;
        if (var_4->unk_5C && var_4->unk_04 && var_8 && var_4->unk_70 != var_8->unk_54)
        {
            var_8->vf_06C(var_4->unk_04);
            var_4->unk_04->vf_060(var_8);
            var_8->unk_54 = var_4->unk_70;
            if (var_4->unk_7C && (var_8->unk_2C & 0x30) && !var_8->unk_28_9)
            {
                var_94 = (arg_0->t.sphere.radius + arg_8->worldBoundingSphere.radius) * arg_C;
                var_98 = var_4->unk_04->unk_4C;
                var_9C = var_4->unk_04->vf_120();
                if (var_9C && var_9C->is_blocked())
                {
                    var_98 += flt_4290E4;
                }
                if (var_98 + var_8->unk_4C > var_94)
                {
                    sub_9A2D0(var_8, &arg_8->worldBoundingSphere.center, &arg_0->t.sphere.center,
                              (type_3DAFC8_1DDC *)var_4->unk_7C);
                }
            }
        }
    }
    return arg_8;
}
// match: ?sub_946B0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000946B0
// sp-match: ?sub_946B0@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00074730
// The atomic callback of a moving entity's collision search (arg_10, a
// type_93DF0): unless it is the mover itself or neither collides with the
// other, the atomic's triangles are tested in the frame of its matrix
// (orthonormalised and inverted into the search) through its entity's
// vf_074, and a hit is reported to both entities once a search.
RpAtomic *sub_946B0(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10)
{
    type_93DF0 *var_4;
    type_3D3548 *var_8;
    RwInt32 var_C;
    RwUInt32 var_10;
    RwMatrix var_50;
    RwMatrix var_90;

    if (sub_FB9C0(arg_8) & 8)
    {
        return arg_8;
    }
    var_4 = (type_93DF0 *)arg_10;
    var_8 = sub_FB960(arg_8);
    if (var_4->unk_04 && var_8)
    {
        var_C = 0;
        if (var_4->unk_04 != var_8 && var_8->unk_28_2)
        {
            var_10 = var_8->unk_2C & 0x3FFFFF0;
            if (var_4->unk_04->unk_30 & var_10)
            {
                var_C = 1;
            }
            if (var_4->unk_04->unk_28_20 && var_8->unk_28_15)
            {
                var_C = 1;
            }
        }
    }
    else
    {
        var_C = 1;
    }
    if (var_C)
    {
        var_4->unk_18 = RwFrameGetLTM(RpAtomicGetFrame(arg_8));
        if (var_4->unk_04)
        {
            var_4->unk_1C = &var_50;
            RwMatrixOrthoNormalize(var_4->unk_1C, var_4->unk_18);
            var_4->unk_20 = &var_90;
            RwMatrixInvert(var_4->unk_20, var_4->unk_18);
            var_4->unk_08 = var_8;
            var_4->unk_10 = arg_8;
            var_4->unk_5C = 0;
            var_4->unk_08->Collision_DispatchAtomicIntersectionsBySelectorFlag(arg_8, arg_0,
                                                                              (type_93700 *)var_4);
        }
        var_4->unk_08 = var_8;
        var_4->unk_10 = arg_8;
        if (var_4->unk_5C && var_4->unk_04 && var_8 && var_4->unk_70 != var_8->unk_54)
        {
            var_8->vf_06C(var_4->unk_04);
            var_4->unk_04->vf_060(var_8);
            var_8->unk_54 = var_4->unk_70;
        }
    }
    return arg_8;
}
#ifdef CODFH_SP
// Whether arg_0 is an ancestor of arg_4 (single player only, SP 0x10B070).
bool sp_sub_10B070(RwFrame *arg_0, RwFrame *arg_4);
#endif
// match: ?sub_948A0@@YAXPAUtype_3D3548@@PAURwFrame@@PAURwV3d@@MPAH2PAM3333PAUtype_3DAFC8_1DDC@@@Z @ 0x000948A0
// sp-match: ?sub_948A0@@YAXPAUtype_3D3548@@PAURwFrame@@PAURwV3d@@MPAH2PAM3333PAUtype_3DAFC8_1DDC@@@Z @ 0x00077990
// Moves the entity arg_0's frame arg_4 out of the collision worlds: a
// sphere at the frame's position plus arg_8, of the largest of the radii
// arg_14, searched against their atomics (sub_943E0) and, for an entity
// that collides with the world (unk_30 & 0x40), their triangles
// (sub_929A0), with the floor height arg_C and the floor flag arg_10.
// With contact records arg_2C, those are cleared and the radii widened by
// flt_4290D4 first. The hit flags go to arg_20, arg_24 and arg_28; a
// vertical probe then sets *arg_1C when there is ground below (and *arg_18
// its drop from the sphere's base). The sphere's centre is kept in the
// entity's unk_5C.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_948A0(type_3D3548 *arg_0, RwFrame *arg_4, RwV3d *arg_8, RwReal arg_C, RwInt32 *arg_10,
               RwV3d *arg_14, RwReal *arg_18, RwInt32 *arg_1C, RwInt32 *arg_20, RwInt32 *arg_24,
               RwInt32 *arg_28, type_3DAFC8_1DDC *arg_2C)
{
    type_4E5D30 *s11C;
    RwV3d *var118;
    type_99130 m_114;
    RpWorld *ebp_F0;
    type_4E5D30 *rEC;
    type_4E5D30 *local_E8;
    RwReal locE4;
    RwInt32 q28;
    RwMatrix *frm_24;
    RpIntersection t20;
    RwInt32 bp_4;

    dword_4B25BC = 0;
    dword_4B25B8 = 150;
    *arg_1C = 0;
    *arg_18 = 1e37f;
    // Declared here: its constructor (sub_95030) runs after the stores above.
    type_93DF0 local_E0;
    frm_24 = RwFrameGetLTM(arg_4);
    t20.type = rpINTERSECTSPHERE;
    t20.t.sphere.center = frm_24->pos;
    if (arg_8)
    {
        RwV3dAddMacro(&t20.t.sphere.center, &t20.t.sphere.center, arg_8);
    }
    if (arg_14->x > arg_14->y && arg_14->x > arg_14->z)
    {
        t20.t.sphere.radius = arg_14->x;
    }
    else if (arg_14->y > arg_14->x && arg_14->y > arg_14->z)
    {
        t20.t.sphere.radius = arg_14->y;
    }
    else
    {
        t20.t.sphere.radius = arg_14->z;
    }
    if (arg_2C)
    {
        arg_2C->unk_54[0].unk_00 = 0;
        arg_2C->unk_54[0].unk_04 = 1e37f;
        arg_2C->unk_54[1].unk_00 = 0;
        arg_2C->unk_54[1].unk_04 = 1e37f;
        arg_2C->unk_54[2].unk_00 = 0;
        arg_2C->unk_54[2].unk_04 = 1e37f;
        arg_2C->unk_54[3].unk_00 = 0;
        arg_2C->unk_54[3].unk_04 = 1e37f;
        arg_2C->unk_54[4].unk_00 = 0;
        arg_2C->unk_54[4].unk_04 = 1e37f;
        arg_2C->unk_54[5].unk_00 = 0;
        arg_2C->unk_54[5].unk_04 = 1e37f;
        arg_2C->unk_54[6].unk_00 = 0;
        arg_2C->unk_54[6].unk_04 = 1e37f;
        arg_2C->unk_54[7].unk_00 = 0;
        arg_2C->unk_54[7].unk_04 = 1e37f;
        arg_2C->unk_2D4[0].unk_00 = 0;
        arg_2C->unk_2D4[0].unk_04 = 1e37f;
        arg_2C->unk_2D4[1].unk_00 = 0;
        arg_2C->unk_2D4[1].unk_04 = 1e37f;
        arg_2C->unk_2D4[2].unk_00 = 0;
        arg_2C->unk_2D4[2].unk_04 = 1e37f;
        arg_2C->unk_2D4[3].unk_00 = 0;
        arg_2C->unk_2D4[3].unk_04 = 1e37f;
        arg_2C->unk_00.x = flt_4290D4 + arg_14->x;
        arg_2C->unk_00.y = arg_14->y;
        arg_2C->unk_00.z = flt_4290D4 + arg_14->z;
        arg_2C->unk_0C.x = 1.0f / (arg_2C->unk_00.x * arg_2C->unk_00.x);
        arg_2C->unk_0C.y = 1.0f / (arg_2C->unk_00.y * arg_2C->unk_00.y);
        arg_2C->unk_0C.z = 1.0f / (arg_2C->unk_00.z * arg_2C->unk_00.z);
        arg_2C->unk_30 = frm_24->at;
        arg_2C->unk_30.y = 0.0f;
        RwV3dNormalize(&arg_2C->unk_30, &arg_2C->unk_30);
        arg_2C->unk_3C = frm_24->right;
        arg_2C->unk_3C.y = 0.0f;
        RwV3dNormalize(&arg_2C->unk_3C, &arg_2C->unk_3C);
        t20.t.sphere.radius += flt_4290D4;
    }
    locE4 = t20.t.sphere.radius * t20.t.sphere.radius;
    local_E0.unk_74 = sub_9A800(arg_0);
    local_E0.unk_6C = arg_8;
    local_E0.unk_24 = locE4;
    local_E0.unk_20 = 0;
    local_E0.unk_18 = 0;
    local_E0.unk_04 = arg_0;
    local_E0.unk_14 = arg_4;
    local_E0.unk_0C = 0;
    local_E0.unk_08 = 0;
    local_E0.unk_60 = 0;
    local_E0.unk_64 = 0;
    local_E0.unk_68 = 0;
    local_E0.unk_7C = arg_2C;
    local_E0.unk_78 = -1;
    local_E0.unk_80 = arg_18;
    local_E0.unk_90 = 0;
    local_E0.unk_38[0] = 1.0f / (arg_14->x * arg_14->x);
    local_E0.unk_38[1] = 1.0f / (arg_14->y * arg_14->y);
    local_E0.unk_38[2] = 1.0f / (arg_14->z * arg_14->z);
    local_E0.unk_48 = arg_C;
    local_E0.unk_50 = arg_10;
    local_E0.unk_58 = 0;
    local_E0.unk_54 = 0;
    local_E0.unk_70 = sub_8F940();
    if (arg_0)
    {
        arg_0->unk_54 = local_E0.unk_70;
    }
    bp_4 = 0;
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        local_E8 = &dword_4E5D30[bp_4];
        if (local_E8->get_unk_00())
        {
            local_E0.unk_00 = local_E8->get_unk_28();
            RpWorldForAllAtomicIntersections(local_E8->get_unk_28(), &t20, sub_943E0, &local_E0);
        }
    }
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        rEC = &dword_4E5D30[bp_4];
        if (rEC->get_unk_00())
        {
            local_E0.unk_00 = rEC->get_unk_28();
            if ((arg_0->unk_30 & 0x40) && rEC->get_unk_28())
            {
                RpCollisionWorldForAllIntersections(rEC->get_unk_28(), &t20, sub_929A0, &local_E0);
            }
        }
    }
    *arg_20 = local_E0.unk_60;
    *arg_24 = local_E0.unk_64;
    *arg_28 = local_E0.unk_68;
    if (local_E0.unk_7C)
    {
        local_E0.unk_7C->unk_48 = t20.t.sphere.center;
    }
    q28 = 1;
#ifdef CODFH_SP
    // Single player rides what it stands on (SP 0x77990): the frame is made a
    // child of the atomic's frame, keeping its world matrix, and is detached
    // when there is none; either way the ground probe below is skipped.
    if (local_E0.unk_58)
    {
        RwFrame *parent = RpAtomicGetFrame(local_E0.unk_58);

        if (RwFrameGetParent(arg_4) != parent && !sp_sub_10B070(arg_4, parent))
        {
            RwMatrix *inverse = RwMatrixCreate();

            if (RwFrameGetParent(arg_4))
            {
                RwMatrixCopy(RwFrameGetMatrix(arg_4), RwFrameGetLTM(arg_4));
                RwFrameRemoveChild(arg_4);
            }
            inverse->flags = 1;
            RwMatrixInvert(inverse, RwFrameGetLTM(parent));
            RwFrameTransform(arg_4, inverse, rwCOMBINEPOSTCONCAT);
            RwFrameAddChild(parent, arg_4);
            RwMatrixDestroy(inverse);
            var118 = &RwFrameGetLTM(arg_4)->pos;
            *arg_18 = var118->y;
            *arg_1C = 1;
            q28 = 0;
        }
    }
    else
    {
        if (RwFrameGetParent(arg_4))
        {
            RwMatrixCopy(RwFrameGetMatrix(arg_4), RwFrameGetLTM(arg_4));
            RwFrameRemoveChild(arg_4);
        }
        if (*local_E0.unk_50)
        {
            var118 = &RwFrameGetLTM(arg_4)->pos;
            *arg_18 = var118->y;
            *arg_1C = 1;
            q28 = 0;
        }
    }
#endif
    if (q28)
    {
        var118 = &RwFrameGetLTM(arg_4)->pos;
        t20.type = rpINTERSECTLINE;
        t20.t.line.start = *var118;
        t20.t.line.end = *var118;
        t20.t.line.start.y += 500000.0f;
        t20.t.line.end.y -= 500000.0f;
        m_114.unk_00 = 0;
        m_114.unk_04 = 0;
        m_114.unk_08 = 1e37f;
        m_114.unk_0C = -1e37f;
        m_114.unk_10 = var118->y;
        m_114.unk_14 = arg_0;
        ebp_F0 = 0;
        for (bp_4 = 0; bp_4 < 4; bp_4++)
        {
            s11C = &dword_4E5D30[bp_4];
            if (s11C->get_unk_00() && (arg_0->unk_30 & 0x40))
            {
                ebp_F0 = s11C->unk_28;
                if (ebp_F0)
                {
                    m_114.unk_20 = ebp_F0;
                    RpCollisionWorldForAllIntersections(ebp_F0, &t20, sub_99280, &m_114);
                }
            }
        }
        if (m_114.unk_00 && !m_114.unk_04)
        {
            *arg_1C = 0;
        }
        else if (!m_114.unk_04)
        {
            *arg_1C = 0;
        }
        else
        {
            *arg_1C = 1;
            *arg_18 = arg_14->y - arg_8->y + m_114.unk_0C;
        }
    }
    arg_0->unk_5C = t20.t.sphere.center;
}
#ifndef CODFH_SP // single player defines it in the class (include/types/type_92430.h)
// match: ??0type_93DF0@@QAE@XZ @ 0x00095030
// sp-match: ??0type_93DF0@@QAE@XZ @ 0x00074330
type_93DF0::type_93DF0()
{
    unk_7C = 0;
    unk_4C = 0;
    unk_94 = 1e37f;
    unk_98 = 0;
    unk_9C = 0;
    unk_A0 = 0;
    unk_A4 = 0;
    unk_A8 = 0;
    unk_AC = 0;
    unk_B0 = 0;
}
#endif
// match: ?sub_950C0@@YAXPAUtype_3D3548@@PAURwFrame@@PAURwV3d@@MPAH2PAM333PAUtype_3DAFC8_1DDC@@@Z @ 0x000950C0
// sp-match: ?sub_950C0@@YAXPAUtype_3D3548@@PAURwFrame@@PAURwV3d@@MPAH2PAM333PAUtype_3DAFC8_1DDC@@@Z @ 0x00078020
// sub_948A0 for an entity that can stand on others: the sphere is at least
// 150 across, the callbacks are sub_946B0 and sub_930F0, and there is no
// third hit flag. When the search found an atomic to stand on (unk_58),
// the frame is moved under that atomic's frame (keeping its place in the
// world); otherwise it is taken out of any parent, and with a floor found
// (*unk_50) that height goes to *arg_18. Only when neither happens does the
// vertical probe run.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_950C0(type_3D3548 *arg_0, RwFrame *arg_4, RwV3d *arg_8, RwReal arg_C, RwInt32 *arg_10,
               RwV3d *arg_14, RwReal *arg_18, RwInt32 *arg_1C, RwInt32 *arg_20, RwInt32 *arg_24,
               type_3DAFC8_1DDC *arg_28)
{
    type_4E5D30 *u134;
    RwV3d *lcl_130;
    type_99130 l12C;
    RpWorld *u108;
    RwV3d *u104;
    RwV3d *u100;
    RwMatrix *lcl_FC;
    RwFrame *uF8;
    type_4E5D30 *locF4;
    type_4E5D30 *ebp_F0;
    RwReal rEC;
    RwInt32 fp_2C;
    RpAtomic *q28;
    RwMatrix *frm_24;
    RpIntersection t20;
    RwInt32 bp_4;

    dword_4B25BC = 0;
    dword_4B25B8 = 150;
    *arg_1C = 0;
    *arg_18 = 1e37f;
    // Declared here: its constructor (sub_95030) runs after the stores above.
    type_93DF0 local_E8;
    frm_24 = RwFrameGetLTM(arg_4);
    t20.type = rpINTERSECTSPHERE;
    t20.t.sphere.center = frm_24->pos;
    if (arg_8)
    {
        RwV3dAddMacro(&t20.t.sphere.center, &t20.t.sphere.center, arg_8);
    }
    if (arg_14->x > arg_14->y && arg_14->x > arg_14->z)
    {
        t20.t.sphere.radius = arg_14->x;
    }
    else if (arg_14->y > arg_14->x && arg_14->y > arg_14->z)
    {
        t20.t.sphere.radius = arg_14->y;
    }
    else
    {
        t20.t.sphere.radius = arg_14->z;
    }
    if (t20.t.sphere.radius < 150.0f)
    {
        t20.t.sphere.radius = 150.0f;
    }
    if (arg_28)
    {
        arg_28->unk_54[0].unk_00 = 0;
        arg_28->unk_54[0].unk_04 = 1e37f;
        arg_28->unk_54[1].unk_00 = 0;
        arg_28->unk_54[1].unk_04 = 1e37f;
        arg_28->unk_54[2].unk_00 = 0;
        arg_28->unk_54[2].unk_04 = 1e37f;
        arg_28->unk_54[3].unk_00 = 0;
        arg_28->unk_54[3].unk_04 = 1e37f;
        arg_28->unk_54[4].unk_00 = 0;
        arg_28->unk_54[4].unk_04 = 1e37f;
        arg_28->unk_54[5].unk_00 = 0;
        arg_28->unk_54[5].unk_04 = 1e37f;
        arg_28->unk_54[6].unk_00 = 0;
        arg_28->unk_54[6].unk_04 = 1e37f;
        arg_28->unk_54[7].unk_00 = 0;
        arg_28->unk_54[7].unk_04 = 1e37f;
        arg_28->unk_2D4[0].unk_00 = 0;
        arg_28->unk_2D4[0].unk_04 = 1e37f;
        arg_28->unk_2D4[1].unk_00 = 0;
        arg_28->unk_2D4[1].unk_04 = 1e37f;
        arg_28->unk_2D4[2].unk_00 = 0;
        arg_28->unk_2D4[2].unk_04 = 1e37f;
        arg_28->unk_2D4[3].unk_00 = 0;
        arg_28->unk_2D4[3].unk_04 = 1e37f;
        arg_28->unk_00.x = flt_4290D4 + arg_14->x;
        arg_28->unk_00.y = arg_14->y;
        arg_28->unk_00.z = flt_4290D4 + arg_14->z;
        arg_28->unk_0C.x = 1.0f / (arg_28->unk_00.x * arg_28->unk_00.x);
        arg_28->unk_0C.y = 1.0f / (arg_28->unk_00.y * arg_28->unk_00.y);
        arg_28->unk_0C.z = 1.0f / (arg_28->unk_00.z * arg_28->unk_00.z);
        arg_28->unk_30 = frm_24->at;
        arg_28->unk_30.y = 0.0f;
        RwV3dNormalize(&arg_28->unk_30, &arg_28->unk_30);
        arg_28->unk_3C = frm_24->right;
        arg_28->unk_3C.y = 0.0f;
        RwV3dNormalize(&arg_28->unk_3C, &arg_28->unk_3C);
        t20.t.sphere.radius += flt_4290D4;
    }
    rEC = t20.t.sphere.radius * t20.t.sphere.radius;
    local_E8.unk_74 = sub_9A800(arg_0);
    local_E8.unk_6C = arg_8;
    local_E8.unk_24 = rEC;
    local_E8.unk_20 = 0;
    local_E8.unk_18 = 0;
    local_E8.unk_04 = arg_0;
    local_E8.unk_14 = arg_4;
    local_E8.unk_0C = 0;
    local_E8.unk_08 = 0;
    local_E8.unk_60 = 0;
    local_E8.unk_64 = 0;
    local_E8.unk_68 = 0;
    local_E8.unk_7C = arg_28;
    local_E8.unk_78 = -1;
    local_E8.unk_80 = arg_18;
    local_E8.unk_90 = 0;
    local_E8.unk_38[0] = 1.0f / (arg_14->x * arg_14->x);
    local_E8.unk_38[1] = 1.0f / (arg_14->y * arg_14->y);
    local_E8.unk_38[2] = 1.0f / (arg_14->z * arg_14->z);
    local_E8.unk_48 = arg_C;
    local_E8.unk_50 = arg_10;
    local_E8.unk_58 = 0;
    local_E8.unk_54 = 0;
    local_E8.unk_70 = sub_8F940();
    if (arg_0)
    {
        arg_0->unk_54 = local_E8.unk_70;
    }
    bp_4 = 0;
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        ebp_F0 = &dword_4E5D30[bp_4];
        if (ebp_F0->get_unk_00())
        {
            local_E8.unk_00 = ebp_F0->get_unk_28();
            RpWorldForAllAtomicIntersections(ebp_F0->get_unk_28(), &t20, sub_946B0, &local_E8);
        }
    }
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        locF4 = &dword_4E5D30[bp_4];
        if (locF4->get_unk_00())
        {
            local_E8.unk_00 = locF4->get_unk_28();
            if ((arg_0->unk_30 & 0x40) && locF4->get_unk_28())
            {
                RpCollisionWorldForAllIntersections(locF4->get_unk_28(), &t20, sub_930F0, &local_E8);
            }
        }
    }
    *arg_20 = local_E8.unk_60;
    *arg_24 = local_E8.unk_64;
    if (local_E8.unk_7C)
    {
        local_E8.unk_7C->unk_48 = t20.t.sphere.center;
    }
    fp_2C = 0;
    q28 = local_E8.unk_58;
    if (q28)
    {
        uF8 = RpAtomicGetFrame(q28);
        if (RwFrameGetParent(arg_4) != uF8)
        {
            lcl_FC = RwMatrixCreate();
            if (RwFrameGetParent(arg_4))
            {
                *RwFrameGetMatrix(arg_4) = *RwFrameGetLTM(arg_4);
                RwFrameRemoveChild(arg_4);
            }
            do
            {
                lcl_FC->flags = 1;
            } while (0);
            RwMatrixInvert(lcl_FC, RwFrameGetLTM(uF8));
            RwFrameTransform(arg_4, lcl_FC, rwCOMBINEPOSTCONCAT);
            RwFrameAddChild(uF8, arg_4);
            RwMatrixDestroy(lcl_FC);
            u100 = &RwFrameGetLTM(arg_4)->pos;
            *arg_18 = u100->y;
            *arg_1C = 1;
            fp_2C = 0;
        }
    }
    else
    {
        if (RwFrameGetParent(arg_4))
        {
            *RwFrameGetMatrix(arg_4) = *RwFrameGetLTM(arg_4);
            RwFrameRemoveChild(arg_4);
        }
        if (*local_E8.unk_50)
        {
            u104 = &RwFrameGetLTM(arg_4)->pos;
            *arg_18 = u104->y;
            *arg_1C = 1;
            fp_2C = 0;
        }
    }
    if (fp_2C)
    {
        lcl_130 = &RwFrameGetLTM(arg_4)->pos;
        t20.type = rpINTERSECTLINE;
        t20.t.line.start = *lcl_130;
        t20.t.line.end = *lcl_130;
        t20.t.line.start.y += 500000.0f;
        t20.t.line.end.y -= 500000.0f;
        l12C.unk_00 = 0;
        l12C.unk_04 = 0;
        l12C.unk_08 = 1e37f;
        l12C.unk_0C = -1e37f;
        l12C.unk_10 = lcl_130->y;
        l12C.unk_14 = arg_0;
        u108 = 0;
        for (bp_4 = 0; bp_4 < 4; bp_4++)
        {
            u134 = &dword_4E5D30[bp_4];
            if (u134->get_unk_00() && (arg_0->unk_30 & 0x40))
            {
                u108 = u134->unk_28;
                if (u108)
                {
                    l12C.unk_20 = u108;
                    RpCollisionWorldForAllIntersections(u108, &t20, sub_99280, &l12C);
                }
            }
        }
        if (l12C.unk_00 && !l12C.unk_04)
        {
            *arg_1C = 0;
        }
        else if (!l12C.unk_04)
        {
            *arg_1C = 0;
        }
        else
        {
            *arg_1C = 1;
            *arg_18 = arg_14->y - arg_8->y + l12C.unk_0C;
        }
    }
    arg_0->unk_5C = t20.t.sphere.center;
}
// match: ?sub_959E0@@YAHPAURwV3d@@M00000@Z @ 0x000959E0
// sp-match: ?sub_959E0@@YAHPAURwV3d@@M00000@Z @ 0x00074850
// Drops four points (arg_0 and three around it) along y onto the triangle
// arg_8, arg_C, arg_10 of normal arg_14 (not near vertical), within arg_4:
// the highest hit inside the triangle goes into arg_18->y. 1 on a hit.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_959E0(RwV3d *arg_0, RwReal arg_4, RwV3d *arg_8, RwV3d *arg_C, RwV3d *arg_10, RwV3d *arg_14,
                  RwV3d *arg_18)
{
    RwV3d l48;
    RwInt32 lv_4C;
    RwReal var_50;
    RwReal var_58;
    RwV3d stk_64;
    RwReal fp_C;
    RwReal var_54;

    if (arg_14->y < flt_4290EC && -flt_4290EC < arg_14->y)
    {
        return 0;
    }
    fp_C = -arg_14->y;
    if (arg_14->y < 0.0f)
    {
        fp_C = -fp_C;
    }
    // The point and three around it (20 units off; 14.141999 is about 20 / sqrt(2)).
    RwV3d v3C[4] = {{0.0f, 0.0f, 0.0f},
                       {0.0f, 0.0f, -20.0f},
                       {14.141999f, 0.0f, 14.141999f},
                       {-14.141999f, 0.0f, 14.141999f}};
    RwReal var_8 = -1000000.0f;
    RwInt32 l4 = 0;

    for (lv_4C = 0; lv_4C < 4; lv_4C++)
    {
        RwV3dAddMacro(&l48, arg_0, &v3C[lv_4C]);
        RwV3dSubMacro(&stk_64, &l48, arg_8);
        var_58 = (var_50 = RwV3dDotProductMacro(&stk_64, arg_14)) / fp_C;
        if (var_58 > 0.0f || -var_58 >= arg_4)
        {
            continue;
        }
        var_54 = l48.y + var_58;
        if (var_54 <= var_8)
        {
            continue;
        }
        if ((arg_C->z - arg_8->z) * (l48.x - arg_8->x) - (arg_C->x - arg_8->x) * (l48.z - arg_8->z) <= 0.0f)
        {
            continue;
        }
        if (((arg_10->z - arg_C->z) * (l48.x - arg_C->x)) - ((arg_10->x - arg_C->x) * (l48.z - arg_C->z)) <= 0.0f)
        {
            continue;
        }
        if ((arg_8->z - arg_10->z) * (l48.x - arg_10->x) - (arg_8->x - arg_10->x) * (l48.z - arg_10->z) <= 0.0f)
        {
            continue;
        }
        arg_18->y = var_54;
        var_8 = var_54;
        l4 = 1;
    }
    return l4;
}
// match: ?sub_95C70@@YAHPAURwV3d@@0M00@Z @ 0x00095C70
// sp-match: ?sub_95C70@@YAHPAURwV3d@@0M00@Z @ 0x00074A80
// Whether the sphere at arg_4 of radius arg_8 touches the triangle arg_C
// (three points) of normal arg_10, with the triangle's nearest point to the
// sphere's centre into *arg_0: the centre dropped onto the plane when it is
// inside all three edges, else the nearer point of the edge or corner it is
// outside of (0 when that edge is farther than the radius).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_95C70(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8, RwV3d *arg_C, RwV3d *arg_10)
{
    RwReal frm_94;
    RwReal q90;
    RwReal fp_8C;
    RwReal t88;
    RwV3d ebp_84;
    RwV3d fp_78;
    RwReal m_6C;
    RwV3d q68;
    RwInt32 y5C;
    RwInt32 slot_58;
    RwV3d l54;
    RwV3d w48;
    RwV3d ebp_3C;
    RwV3d lv_30;
    RwReal frm_24;
    RwInt32 t20;
    RwReal l1C;
    RwV3d m_18;
    RwV3d slot_C;

    slot_C = *arg_4;
    RwV3dSubMacro(&ebp_3C, &slot_C, arg_C);
    l1C = RwV3dDotProductMacro(&ebp_3C, arg_10);
    if (l1C > arg_8 || -arg_8 > l1C)
    {
        return 0;
    }
    RwV3dScaleMacro(&m_18, arg_10, -l1C);
    RwV3dAddMacro(&slot_C, arg_4, &m_18);

    RwV3dSubMacro(&ebp_84, &arg_C[1], arg_C);
    RwV3dCrossProductMacro(&l54, &ebp_84, arg_10);
    if (l54.x == 0.0f && l54.y == 0.0f && l54.z == 0.0f)
    {
        m_6C = 0.0f;
        y5C = 0;
    }
    else
    {
        RwV3dNormalize(&q68, &l54);
        RwV3dSubMacro(&fp_78, &slot_C, arg_C);
        y5C = (m_6C = RwV3dDotProductMacro(&fp_78, &q68)) > 0.0f;
    }
    if (y5C && m_6C > arg_8)
    {
        return 0;
    }

    RwV3dSubMacro(&ebp_84, &arg_C[2], &arg_C[1]);
    RwV3dCrossProductMacro(&l54, &ebp_84, arg_10);
    if (l54.x == 0.0f && l54.y == 0.0f && l54.z == 0.0f)
    {
        frm_24 = 0.0f;
        slot_58 = 0;
    }
    else
    {
        RwV3dNormalize(&w48, &l54);
        RwV3dSubMacro(&fp_78, &slot_C, &arg_C[1]);
        slot_58 = (frm_24 = RwV3dDotProductMacro(&fp_78, &w48)) > 0.0f;
    }
    if (slot_58 && frm_24 > arg_8)
    {
        return 0;
    }

    RwV3dSubMacro(&ebp_84, arg_C, &arg_C[2]);
    RwV3dCrossProductMacro(&l54, &ebp_84, arg_10);
    if (l54.x == 0.0f && l54.y == 0.0f && l54.z == 0.0f)
    {
        t88 = 0.0f;
        t20 = 0;
    }
    else
    {
        RwV3dNormalize(&lv_30, &l54);
        RwV3dSubMacro(&fp_78, &slot_C, &arg_C[2]);
        t20 = (t88 = RwV3dDotProductMacro(&fp_78, &lv_30)) > 0.0f;
    }
    if (t20 && t88 > arg_8)
    {
        return 0;
    }

    if (!y5C && !slot_58 && !t20)
    {
        *arg_0 = slot_C;
        return 1;
    }
    if (y5C && slot_58 && !t20)
    {
        *arg_0 = arg_C[1];
        return 1;
    }
    if (y5C && !slot_58 && t20)
    {
        *arg_0 = arg_C[0];
        return 1;
    }
    if (!y5C && slot_58 && t20)
    {
        *arg_0 = arg_C[2];
        return 1;
    }
    if (y5C && !slot_58 && !t20)
    {
        RwV3dScaleMacro(&l54, &q68, -m_6C);
        RwV3dAddMacro(arg_0, &slot_C, &l54);
        RwV3dSubMacro(&l54, arg_0, &arg_C[1]);
        fp_8C = RwV3dDotProductMacro(&l54, &w48);
        if (fp_8C > 0.0f)
        {
            *arg_0 = arg_C[1];
        }
        else
        {
            RwV3dSubMacro(&l54, arg_0, arg_C);
            fp_8C = RwV3dDotProductMacro(&l54, &lv_30);
            if (fp_8C > 0.0f)
            {
                *arg_0 = arg_C[0];
            }
        }
        return 1;
    }
    if (!y5C && slot_58 && !t20)
    {
        RwV3dScaleMacro(&l54, &w48, -frm_24);
        RwV3dAddMacro(arg_0, &slot_C, &l54);
        RwV3dSubMacro(&l54, arg_0, &arg_C[1]);
        q90 = RwV3dDotProductMacro(&l54, &q68);
        if (q90 > 0.0f)
        {
            *arg_0 = arg_C[1];
        }
        else
        {
            RwV3dSubMacro(&l54, arg_0, &arg_C[2]);
            q90 = RwV3dDotProductMacro(&l54, &lv_30);
            if (q90 > 0.0f)
            {
                *arg_0 = arg_C[2];
            }
        }
        return 1;
    }
    if (!y5C && !slot_58 && t20)
    {
        RwV3dScaleMacro(&l54, &lv_30, -t88);
        RwV3dAddMacro(arg_0, &slot_C, &l54);
        RwV3dSubMacro(&l54, arg_0, arg_C);
        frm_94 = RwV3dDotProductMacro(&l54, &q68);
        if (frm_94 > 0.0f)
        {
            *arg_0 = arg_C[0];
        }
        else
        {
            RwV3dSubMacro(&l54, arg_0, &arg_C[2]);
            frm_94 = RwV3dDotProductMacro(&l54, &w48);
            if (frm_94 > 0.0f)
            {
                *arg_0 = arg_C[2];
            }
        }
        return 1;
    }
    return 0;
}
// match: ?sub_96680@@YAXPAUtype_93DF0@@PAURpIntersection@@MPAMM@Z @ 0x00096680
// sp-match: ?sub_96680@@YAXPAUtype_93DF0@@PAURpIntersection@@MPAMM@Z @ 0x000751E0
// Flushes the gathered triangles for a ground search (sub_96EF0, and
// sub_93DF0 when 350 are gathered): the highest drop of the sphere onto
// each goes to *arg_C (sub_959E0), and two spheres of radius arg_8, one at
// the top and one at the step height (unk_8C), are pushed out of each
// (sub_95C70) as sub_974A0 does, moving the search sphere and the frame.
// A player pushed up while falling stops falling; pushed down under a steep
// enough triangle, it stops rising and, while its eye follows its steps
// (unk_28_1, standing), lowers its eye height (at most 20).
void sub_96680(type_93DF0 *arg_0, RpIntersection *arg_4, RwReal arg_8, RwReal *arg_C, RwReal arg_10)
{
    RwReal var_4;
    RwReal var_8;
    RwReal var_C;
    RwReal var_10;
    RwV3d *var_14;
    RwV3d *var_18;
    RwV3d var_24;
    RwInt32 var_28;
    RwReal var_2C;
    RwInt32 var_30;
    RwV3d var_3C;
    RwV3d var_48;
    RwV3d var_54;
    RwReal var_58;
    RwReal var_B4;
    RwV3d var_C0;
    type_10F710 *var_C4;
    RwV3d var_D0;
    RwReal var_D4;
    RwReal var_134;
    RwV3d var_140;
    type_10F710 *var_144;

    if (!dword_4B25BC)
    {
        return;
    }
    var_4 = arg_8 * arg_8;
    var_8 = arg_4->t.sphere.radius - arg_8 - 15.0f;
    var_C = var_8 + arg_4->t.sphere.center.y;
    var_10 = arg_4->t.sphere.center.y - var_8 + arg_0->unk_8C;
    if (var_C - 1.0f < var_10)
    {
        var_C = var_10 + 1.0f;
    }
    var_14 = dword_4B25C0;
    var_18 = dword_4B56F8;
    var_24.x = 0.0f;
    var_24.y = 0.0f;
    var_24.z = 0.0f;
    var_28 = 0;
    var_2C = -1000000.0f;
    for (var_30 = 0; var_30 < dword_4B25BC; var_30++)
    {
        if (sub_959E0(&arg_4->t.sphere.center, arg_4->t.sphere.radius, var_14, var_14 + 1, var_14 + 2, var_18,
                      &var_3C)
            && var_3C.y > var_2C)
        {
            arg_0->unk_60 = 1;
            arg_0->unk_64 = 1;
            *arg_C = var_3C.y;
            var_2C = var_3C.y;
        }
        var_48 = arg_4->t.sphere.center;
        var_48.y = var_C;
        if (sub_95C70(&var_3C, &var_48, arg_8, var_14, var_18))
        {
            RwV3dSubMacro(&var_54, &var_48, &var_3C);
            var_58 = RwV3dDotProductMacro(&var_54, &var_54);
            if (var_58 != 0.0f && var_58 < var_4)
            {
                var_28++;
                do
                {
                    __m128 var_80 = _mm_set_ss(var_58);
                    __m128 var_B0 = _mm_sqrt_ss(var_80);
                    _mm_store_ss(&var_B4, var_B0);
                } while (0);
                RwV3dScaleMacro(&var_C0, &var_54, (arg_8 - var_B4) / var_B4);
                RwV3dAddMacro(&var_24, &var_24, &var_C0);
                RwV3dAddMacro(&arg_4->t.sphere.center, &arg_4->t.sphere.center, &var_C0);
                var_C += var_C0.y;
                var_10 += var_C0.y;
                arg_0->unk_68 = 1;
                var_C4 = (type_10F710 *)arg_0->unk_04;
                if (var_C0.y > 1.0f && var_C4->unk_DC < 0.0f)
                {
                    var_C4->unk_DC = -0.01f;
                }
                else if (var_C0.y < 0.0f && var_3C.y > var_C && -flt_4290EC > var_18->y)
                {
                    if (var_C4->unk_DC > 0.01f)
                    {
                        var_C4->unk_DC = 0.01f;
                    }
                    if (var_C4->unk_28_1 && !var_C4->unk_1A04)
                    {
                        var_C4->unk_524 -= var_C0.y;
                        if (var_C4->unk_524 > 20.0f)
                        {
                            var_C4->unk_524 = 20.0f;
                        }
                    }
                }
            }
            arg_0->unk_60 = 1;
        }
        var_48.y = var_10;
        if (sub_95C70(&var_3C, &var_48, arg_8, var_14, var_18))
        {
            RwV3dSubMacro(&var_D0, &var_48, &var_3C);
            var_D4 = RwV3dDotProductMacro(&var_D0, &var_D0);
            if (var_D4 != 0.0f && var_D4 < var_4)
            {
                var_28++;
                do
                {
                    __m128 var_100 = _mm_set_ss(var_D4);
                    __m128 var_130 = _mm_sqrt_ss(var_100);
                    _mm_store_ss(&var_134, var_130);
                } while (0);
                RwV3dScaleMacro(&var_140, &var_D0, (arg_8 - var_134) / var_134);
                RwV3dAddMacro(&var_24, &var_24, &var_140);
                RwV3dAddMacro(&arg_4->t.sphere.center, &arg_4->t.sphere.center, &var_140);
                var_C += var_140.y;
                var_10 += var_140.y;
                arg_0->unk_68 = 1;
                var_144 = (type_10F710 *)arg_0->unk_04;
                if (var_140.y > 1.0f && var_144->unk_DC < 0.0f)
                {
                    var_144->unk_DC = -0.01f;
                }
                else if (var_140.y < 0.0f && var_3C.y > var_C && -flt_4290EC > var_18->y)
                {
                    if (var_144->unk_DC > 0.01f)
                    {
                        var_144->unk_DC = 0.01f;
                    }
                    if (var_144->unk_28_1 && !var_144->unk_1A04)
                    {
                        var_144->unk_524 -= var_140.y;
                        if (var_144->unk_524 > 20.0f)
                        {
                            var_144->unk_524 = 20.0f;
                        }
                    }
                }
            }
            arg_0->unk_60 = 1;
        }
        var_14 += 3;
        var_18++;
    }
    if (var_28)
    {
        RwFrameTranslate(arg_0->unk_14, &var_24, rwCOMBINEPOSTCONCAT);
        RwFrameUpdateObjects(arg_0->unk_14);
    }
}
// match: ?sub_96E30@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00096E30
// sp-match: ?sub_96E30@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x000785B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *sub_96E30(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10)
{
    RwInt32 l14;                // never used; the image's frame keeps its slot
    type_93DF0 *var_10;
    type_FC000 *var_C;
    void *bp_8;
    RwUInt32 bp_4;

    var_10 = (type_93DF0 *)arg_10;
    bp_8 = ((type_96E30 *)var_10->unk_00)->unk_10[((type_92540 *)arg_4)->unk_80 +
                                                 ((type_92540 *)arg_4)->unk_04[arg_8->index].unk_06];
    var_C = sub_FC000(bp_8);
    var_10->unk_78 = (var_C->unk_04 & 0xFFFF) == 0xFFFF ? -1 : var_C->unk_04 & 0xFFFF;
    bp_4 = var_C->unk_04 & 0xFFFF0000;
    if (var_10->unk_74 & bp_4)
    {
        return arg_8;
    }
    sub_93DF0(arg_8->vertices, &arg_8->normal, var_10, arg_0);
    return arg_8;
}
// match: ?sub_991F0@@YAHPAUtype_99130@@PAURpWorldSector@@PAURpCollisionTriangle@@@Z @ 0x000991F0
// sp-match: ?sub_991F0@@YAHPAUtype_99130@@PAURpWorldSector@@PAURpCollisionTriangle@@@Z @ 0x00075990
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
inline RwInt32 sub_991F0(type_99130 *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8)
{
    void *l4;
    type_FC000 *var_8;

#ifdef CODFH_SP
    // shape: one shared return -1 (SP 0x75990 jumps to it from the null test)
    if (arg_4)
    {
        l4 = ((type_96E30 *)arg_0->unk_20)->unk_10[((type_92540 *)arg_4)->unk_80 +
                                                    ((type_92540 *)arg_4)->unk_04[arg_8->index].unk_06];
        var_8 = sub_FC000(l4);
        if ((var_8->unk_04 & 0xFFFF) != 0xFFFF)
        {
            return var_8->unk_04 & 0xFFFF;
        }
    }
    return -1;
#else
    if (!arg_4)
    {
        return -1;
    }
    l4 = ((type_96E30 *)arg_0->unk_20)->unk_10[((type_92540 *)arg_4)->unk_80 +
                                                ((type_92540 *)arg_4)->unk_04[arg_8->index].unk_06];
    var_8 = sub_FC000(l4);
    return (var_8->unk_04 & 0xFFFF) == 0xFFFF ? -1 : var_8->unk_04 & 0xFFFF;
#endif
}
// match: ?sub_96EF0@@YAXPAUtype_3D3548@@PAURwFrame@@PAURwV3d@@MPAH2PAM333MMH@Z @ 0x00096EF0
// sp-match: ?sub_96EF0@@YAXPAUtype_3D3548@@PAURwFrame@@PAURwV3d@@MPAH2PAM333MMH@Z @ 0x00078620
// The ground search of a walking entity: a sphere from arg_C below the
// frame to the top of the radii arg_14 (arg_2C above), searched against
// the collision worlds' atomics (sub_943E0) and triangles (sub_96E30, then
// sub_96680 with the side radius and arg_28). An atomic stood on takes the
// frame as its child; *arg_18 is the ground's height under the frame
// (*arg_1C set), and the surface goes to the entity's unk_294 on a hit.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_96EF0(type_3D3548 *arg_0, RwFrame *arg_4, RwV3d *arg_8, RwReal arg_C, RwInt32 *arg_10,
               RwV3d *arg_14, RwReal *arg_18, RwInt32 *arg_1C, RwInt32 *arg_20, RwInt32 *arg_24,
               RwReal arg_28, RwReal arg_2C, RwInt32 arg_30)
{
    RwV3d *lcl_128;
    RwMatrix *v124;
    RwV3d *v120;
    RwFrame *s11C;
    RwChar var118[16];
    type_4E5D30 *u104;
    type_4E5D30 *u100;
    RwReal lcl_FC;
    RwReal ebp_3C;
    RwReal local_38;
    RwReal local_34;
    RpAtomic *frm_30;
    RpIntersection stk_2C;
    RwInt32 lv_10;
    RwReal slot_C;
    RwReal bp_8;
    RwReal bp_4;

    dword_4B25BC = 0;
    dword_4B6760 = 0;
    *arg_1C = 0;
    *arg_18 = -1000000.0f;
    // Declared here: its constructor (sub_95030) runs after the stores above.
    type_93DF0 uF8;
    stk_2C.type = rpINTERSECTSPHERE;
    stk_2C.t.sphere.center = RwFrameGetLTM(arg_4)->pos;
    local_34 = stk_2C.t.sphere.center.y - arg_C;
    stk_2C.t.sphere.radius = 150.0f;
    bp_4 = arg_14->x;
    lcl_FC = stk_2C.t.sphere.radius * stk_2C.t.sphere.radius;
    uF8.unk_74 = sub_9A800(arg_0);
    uF8.unk_6C = arg_8;
    uF8.unk_24 = lcl_FC;
    uF8.unk_20 = 0;
    uF8.unk_18 = 0;
    uF8.unk_04 = arg_0;
    uF8.unk_14 = arg_4;
    uF8.unk_0C = 0;
    uF8.unk_08 = 0;
    uF8.unk_60 = 0;
    uF8.unk_64 = 0;
    uF8.unk_68 = 0;
    uF8.unk_5C = 0;
    uF8.unk_80 = arg_18;
    uF8.unk_90 = 1;
    uF8.unk_78 = -1;
    uF8.unk_38[0] = 1.0f / (arg_14->x * arg_14->x);
    uF8.unk_38[1] = 1.0f / (arg_14->y * arg_14->y);
    uF8.unk_38[2] = 1.0f / (arg_14->z * arg_14->z);
    uF8.unk_48 = arg_C;
    uF8.unk_50 = arg_10;
    uF8.unk_58 = 0;
    uF8.unk_54 = 0;
    uF8.unk_70 = sub_8F940();
    uF8.unk_84 = bp_4;
    uF8.unk_8C = arg_28;
    if (arg_0)
    {
        arg_0->unk_54 = uF8.unk_70;
    }
    lv_10 = 0;
    local_38 = (local_38 = arg_2C + arg_14->y) - bp_4;
    if (local_38 <= 1.0f)
    {
        local_38 = 1.0f;
    }
    ebp_3C = 0.0f;
    bp_8 = ((slot_C = ebp_3C + bp_4 + local_38 + bp_4) + ebp_3C) * 0.5f;
    stk_2C.t.sphere.center.y = arg_C + bp_8;
    stk_2C.t.sphere.radius = bp_8 + 15.0f;
    for (lv_10 = 0; lv_10 < 4; lv_10++)
    {
        u100 = &dword_4E5D30[lv_10];
        if (u100->get_unk_00())
        {
            uF8.unk_00 = u100->get_unk_28();
            if (u100->get_unk_28())
            {
                RpWorldForAllAtomicIntersections(u100->get_unk_28(), &stk_2C, sub_943E0, &uF8);
            }
        }
    }
    for (lv_10 = 0; lv_10 < 4; lv_10++)
    {
        u104 = &dword_4E5D30[lv_10];
        if (u104->get_unk_00())
        {
            uF8.unk_00 = u104->get_unk_28();
            if ((arg_0->unk_30 & 0x40) && u104->get_unk_28())
            {
                RpCollisionWorldForAllIntersections(u104->get_unk_28(), &stk_2C, sub_96E30, &uF8);
            }
        }
    }
    sub_96680(&uF8, &stk_2C, bp_4, arg_18, arg_28);
    dword_4B25BC = 0;
    if (dword_429BCC)
    {
        sprintf(var118, "%d", dword_4B6760);
    }
    frm_30 = uF8.unk_58;
    if (frm_30)
    {
        s11C = RpAtomicGetFrame(frm_30);
        if (RwFrameGetParent(arg_4) != s11C)
        {
            v124 = RwMatrixCreate();
            if (RwFrameGetParent(arg_4))
            {
                *RwFrameGetMatrix(arg_4) = *RwFrameGetLTM(arg_4);
                RwFrameRemoveChild(arg_4);
            }
            do
            {
                v124->flags = 1;
            } while (0);
            RwMatrixInvert(v124, RwFrameGetLTM(s11C));
            RwFrameTransform(arg_4, v124, rwCOMBINEPOSTCONCAT);
            RwFrameAddChild(s11C, arg_4);
            RwMatrixDestroy(v124);
            *arg_1C = 1;
        }
        v120 = &RwFrameGetLTM(arg_4)->pos;
        *arg_18 = v120->y - local_34;
        uF8.unk_64 = 1;
    }
    else
    {
        if (RwFrameGetParent(arg_4))
        {
            *RwFrameGetMatrix(arg_4) = *RwFrameGetLTM(arg_4);
            RwFrameRemoveChild(arg_4);
        }
        if (*uF8.unk_50)
        {
            lcl_128 = &RwFrameGetLTM(arg_4)->pos;
            *arg_18 = lcl_128->y - local_34;
        }
    }
    if (uF8.unk_64)
    {
        arg_0->unk_294 = uF8.unk_78;
    }
    *arg_20 = uF8.unk_60;
    *arg_24 = uF8.unk_64;
    *arg_10 = *uF8.unk_50;
    *arg_1C = 1;
    arg_0->unk_5C = stk_2C.t.sphere.center;
}
// match: ?sub_974A0@@YAXPAUtype_93DF0@@PAURwV3d@@M@Z @ 0x000974A0
// sp-match: ?sub_974A0@@YAXPAUtype_93DF0@@PAURwV3d@@M@Z @ 0x000757A0
// Pushes the sphere at arg_4 of radius arg_8 out of each gathered triangle
// (dword_4B25C0, normals dword_4B56F8) it overlaps from the front, moving
// arg_4 and the search's frame (unk_14) by the sum and marking a hit.
void sub_974A0(type_93DF0 *arg_0, RwV3d *arg_4, RwReal arg_8)
{
    RwV3d *var_4;
    RwV3d *var_8;
    RwReal var_C;
    RwV3d var_18;
    __declspec(align(16)) type_8BEC0 var_50;
    RwInt32 var_54;
    RwInt32 var_58;
    RwV3d var_64;
    RwV3d var_70;
    RwReal var_74;
    RwReal var_78;
    RwReal var_D4;
    RwV3d var_E0;

    var_4 = dword_4B25C0;
    var_8 = dword_4B56F8;
    var_C = arg_8 * arg_8;
    var_18.x = 0.0f;
    var_18.y = 0.0f;
    var_18.z = 0.0f;
    var_50 = sub_8BB80(arg_4);
    var_50.unk_0C = arg_8;
    var_54 = 0;
    for (var_58 = 0; var_58 < dword_4B25BC * 2; var_58++)
    {
        if (sub_95C70(&var_64, arg_4, arg_8, var_4, var_8))
        {
            RwV3dSubMacro(&var_70, arg_4, &var_64);
            var_74 = RwV3dDotProductMacro(&var_70, var_8);
            if (var_74 >= 0.0f)
            {
                var_78 = RwV3dDotProductMacro(&var_70, &var_70);
                if (var_78 > 0.001f && var_78 < var_C)
                {
                    var_54++;
                    do
                    {
                        __m128 var_A0 = _mm_set_ss(var_78);
                        __m128 var_D0 = _mm_sqrt_ss(var_A0);
                        _mm_store_ss(&var_D4, var_D0);
                    } while (0);
                    RwV3dScaleMacro(&var_E0, &var_70, (arg_8 - var_D4) / var_D4);
                    RwV3dAddMacro(&var_18, &var_18, &var_E0);
                    RwV3dAddMacro(arg_4, arg_4, &var_E0);
                    arg_0->unk_60 = 1;
                }
            }
        }
        var_4 += 3;
        var_8++;
    }
    if (var_54)
    {
        RwFrameTranslate(arg_0->unk_14, &var_18, rwCOMBINEPOSTCONCAT);
        RwFrameUpdateObjects(arg_0->unk_14);
    }
}
// match: ?sub_97790@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x00097790
// sp-match: ?sub_97790@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAU1@MPAX@Z @ 0x00078AA0
// sub_93700 for a soldier's query: an atomic's triangle (taken into the
// world into dword_4B678C) touched by the sphere pushes the frame out by
// the query's radius (unk_4C) and, when it faces up enough (flt_4290E8)
// and lies within the query's ellipsoid, a ray from 75 above to 25 below
// the frame (Moller-Trumbore) sets it on the triangle, recording the
// entity and atomic stood on. A steep triangle high enough above goes into
// the contact records (the wide radii for an entity of kinds 0x40080).
RpCollisionTriangle *sub_97790(RpIntersection *arg_0, RpCollisionTriangle *arg_4, RwReal arg_8, void *arg_C)
{
    type_93DF0 *var_4;
    RwV3d var_28[3];
    RwV3d var_34;
    RwInt32 var_38;
    RwV3d *var_3C;
    RwV3d var_48;
    RwInt32 var_4C;
    RwV3d var_58;
    RwV3d var_64;
    RwInt32 var_68;
    RwInt32 var_6C;
    RwInt32 var_70;
    RwReal var_74;
    RwReal var_78;
    RwReal var_7C;
    RwReal var_D4;
    RwV3d var_E0;
    RwV3d var_EC;
    RwReal var_F0;
    RwV3d var_FC;
    RwV3d var_108;
    RwV3d var_114;
    RwV3d var_120;
    RwV3d var_12C;
    RwV3d var_138;
    RwReal var_13C;
    RwReal var_140;
    RwReal var_144;
    RwReal var_148;
    RwV3d var_154;
    RwReal var_158;
    RwV3d var_164;
    RwReal var_168;
    RwReal var_16C;
    RwReal var_170;
    RwReal var_174;
    RwInt32 var_178;
    RwInt32 var_17C;
    RwInt32 var_180;
    RpCollisionTriangle var_1A8;

    var_4 = (type_93DF0 *)arg_C;
    var_28[0] = *arg_4->vertices[0];
    var_28[1] = *arg_4->vertices[1];
    var_28[2] = *arg_4->vertices[2];
    sub_141590(dword_4B678C, var_28, 3, var_4->unk_18);
    sub_141320(&var_34, &arg_4->normal, var_4->unk_1C);
    var_38 = 0;
    var_3C = &RwFrameGetLTM(var_4->unk_14)->pos;
    if (sub_95C70(&var_48, &arg_0->t.sphere.center, arg_0->t.sphere.radius, dword_4B678C, &var_34))
    {
        var_38 = 1;
        var_4C = 0;
        var_58.x = 0.0f;
        var_58.y = 0.0f;
        var_58.z = 0.0f;
        RwV3dSubMacro(&var_64, &arg_0->t.sphere.center, &var_48);
        var_68 = 0;
        var_6C = 0;
        var_70 = 0;
        var_74 = var_4->unk_4C;
        var_78 = var_74 * var_74;
        var_7C = RwV3dDotProductMacro(&var_64, &var_64);
        if (var_7C > 0.001f && var_7C < var_78)
        {
            var_4C++;
            do
            {
                __m128 var_A0 = _mm_set_ss(var_7C);
                __m128 var_D0 = _mm_sqrt_ss(var_A0);
                _mm_store_ss(&var_D4, var_D0);
            } while (0);
            RwV3dScaleMacro(&var_E0, &var_64, (var_74 - var_D4) / var_D4);
            RwV3dAddMacro(&var_58, &var_58, &var_E0);
            RwV3dAddMacro(&arg_0->t.sphere.center, &arg_0->t.sphere.center, &var_E0);
            var_70 = 1;
            var_6C = 1;
        }
        if (var_34.y > flt_4290E8)
        {
            var_EC.x = var_64.x * var_64.x * var_4->unk_38[0];
            var_EC.y = var_64.y * var_64.y * var_4->unk_38[1];
            var_EC.z = var_64.z * var_64.z * var_4->unk_38[2];
            var_F0 = var_EC.x + var_EC.y + var_EC.z;
            if (var_F0 < 1.0f)
            {
                var_FC = *var_3C;
                var_FC.y += 75.0f;
                var_108 = *var_3C;
                var_108.y -= 25.0f;
                RwV3dSubMacro(&var_114, &var_108, &var_FC);
                RwV3dSubMacro(&var_120, &dword_4B678C[1], &dword_4B678C[0]);
                RwV3dSubMacro(&var_12C, &dword_4B678C[2], &dword_4B678C[0]);
                RwV3dCrossProductMacro(&var_138, &var_114, &var_12C);
                var_13C = RwV3dDotProductMacro(&var_120, &var_138);
                if (var_13C < -1e-8f || var_13C > 1e-8f)
                {
                    var_140 = 1.0f / var_13C;
                    var_144 = -0.00001f;
                    var_148 = 1.00001f;
                    RwV3dSubMacro(&var_154, &var_FC, &dword_4B678C[0]);
                    var_158 = RwV3dDotProductMacro(&var_154, &var_138) * var_140;
                    if (var_158 > var_144 && var_158 < var_148)
                    {
                        RwV3dCrossProductMacro(&var_164, &var_154, &var_120);
                        var_168 = RwV3dDotProductMacro(&var_114, &var_164) * var_140;
                        if (var_168 > var_144 && var_158 + var_168 < var_148)
                        {
                            var_16C = RwV3dDotProductMacro(&var_12C, &var_164) * var_140;
                            if (var_16C > var_144 && var_16C < var_148)
                            {
#ifdef CODFH_SP
                                // shape: the rise computed once (SP 0x78AA0)
                                var_170 = var_114.y * var_16C + var_FC.y - var_3C->y;
                                var_58.y += var_170;
                                arg_0->t.sphere.center.y += var_170;
#else
                                var_170 = var_114.y * var_16C + var_FC.y;
                                var_58.y += var_170 - var_3C->y;
                                arg_0->t.sphere.center.y += var_170 - var_3C->y;
#endif
                                var_4C++;
                                var_4->unk_54 = var_4->unk_08;
                                var_4->unk_64 = 1;
                                *var_4->unk_50 = 1;
                                var_68 = 1;
                                if (var_4->unk_10)
                                {
                                    var_4->unk_58 = var_4->unk_10;
                                }
                                var_70 = 1;
                            }
                        }
                    }
                }
            }
        }
        if (var_70)
        {
            var_4->unk_60 = 1;
            var_4->unk_5C = 1;
            var_4->unk_24 = arg_8;
            var_4->unk_2C_v = var_48;
            if (var_6C && !var_68)
            {
                var_4->unk_68 = 1;
            }
        }
        if (var_4C)
        {
            if (RwFrameGetParent(var_4->unk_14))
            {
                sub_141320(&var_58, &var_58, var_4->unk_20);
            }
            RwFrameTranslate(var_4->unk_14, &var_58, rwCOMBINEPOSTCONCAT);
            RwFrameUpdateObjects(var_4->unk_14);
        }
    }
    if (!var_38)
    {
        var_48 = arg_0->t.sphere.center;
        sub_8F960(dword_429100, &var_34, &var_48);
        RwV3dSubMacro(&var_64, &arg_0->t.sphere.center, &var_48);
    }
    if (var_4->unk_7C)
    {
        var_174 = var_48.y - var_3C->y;
        if (var_34.y < 0.3f && -flt_4290DC < var_34.y && var_174 > flt_4290D0)
        {
            var_178 = 0;
            var_17C = 0;
            if (var_4->unk_08 && (var_4->unk_08->unk_2C & 0x40080)) // not an address: kind bits
            {
                var_17C = 1;
            }
            if (var_17C)
            {
                var_EC.x = var_64.x * var_64.x * var_4->unk_7C->unk_24.x;
                var_EC.y = var_64.y * var_64.y * var_4->unk_7C->unk_24.y;
                var_EC.z = var_64.z * var_64.z * var_4->unk_7C->unk_24.z;
            }
            else
            {
                var_EC.x = var_64.x * var_64.x * var_4->unk_7C->unk_0C.x;
                var_EC.y = var_64.y * var_64.y * var_4->unk_7C->unk_0C.y;
                var_EC.z = var_64.z * var_64.z * var_4->unk_7C->unk_0C.z;
            }
            var_F0 = var_EC.x + var_EC.y + var_EC.z;
            if (var_F0 < 1.0f && sub_92FB0(&dword_4B678C[0], &dword_4B678C[1], &dword_4B678C[2]))
            {
                var_178 = 1;
            }
            if (var_178)
            {
                var_180 = 2;
            }
            else
            {
                var_180 = 1;
            }
            var_1A8.normal = var_34;
            var_1A8.vertices[0] = &dword_4B678C[0];
            var_1A8.vertices[1] = &dword_4B678C[1];
            var_1A8.vertices[2] = &dword_4B678C[2];
            sub_992B0(var_180, &var_48, var_4->unk_7C, &arg_0->t.sphere.center, (type_30B90_48 *)&var_1A8);
        }
    }
    return arg_4;
}
// match: ?sub_98200@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00098200
// sp-match: ?sub_98200@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00079250
// sub_948A0's world triangle callback: keeps the surface, skips the
// triangle for a skipped material, and with a contact record set (unk_7C)
// sorts a touched, steep enough triangle high enough above the frame into
// it (sub_992B0: kind 2 for a near hit on a triangle sub_92FB0 accepts).
// Every triangle touched (or all, without records) is gathered for
// sub_974A0, which is flushed at 350.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *sub_98200(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10)
{
    RwInt32 ebp_80;
    RwReal v7C;
    RwReal var78;
    RwReal lv_74;
    RwInt32 lcl_70;
    RwReal fp_6C;
    RwInt32 fp_68;
    RwReal lv_64;
    RwV3d lcl_60;
    RwReal lv_54;
    RwReal ebp_50;
    RwReal o4C;
    RwReal q48;
    RwV3d v44;
    RwV3d local_38[3];
    type_93DF0 *ebp_14;
    type_FC000 *lv_10;
    void *slot_C;
    RwUInt32 bp_8;
    RwInt32 bp_4;


    ebp_14 = (type_93DF0 *)arg_10;
    slot_C = ((type_96E30 *)ebp_14->unk_00)->unk_10[((type_92540 *)arg_4)->unk_80 +
                                                  ((type_92540 *)arg_4)->unk_04[arg_8->index].unk_06];
    lv_10 = sub_FC000(slot_C);
    ebp_14->unk_78 = (lv_10->unk_04 & 0xFFFF) == 0xFFFF ? -1 : lv_10->unk_04 & 0xFFFF;
    bp_8 = lv_10->unk_04 & 0xFFFF0000;
    if (ebp_14->unk_74 & bp_8)
    {
        return arg_8;
    }
    bp_4 = 1;
    if (ebp_14->unk_7C)
    {
        local_38[0] = *arg_8->vertices[0];
        local_38[1] = *arg_8->vertices[1];
        local_38[2] = *arg_8->vertices[2];
        if (sub_95C70(&v44, &arg_0->t.sphere.center, arg_0->t.sphere.radius, local_38, &arg_8->normal))
        {
            RwV3dSubMacro(&lcl_60, &arg_0->t.sphere.center, &v44);
            q48 = RwV3dDotProductMacro(&lcl_60, &lcl_60);
            lv_54 = (o4C = ebp_14->unk_4C + 5.0f) * o4C;
            if (q48 > 0.001f && q48 < lv_54)
            {
                bp_4 = 1;
            }
            else
            {
                bp_4 = 0;
            }
            ebp_50 = arg_8->normal.y;
            if (ebp_50 < 0.3f && ebp_50 > -0.3f)
            {
                lv_64 = v44.y - ebp_14->unk_14->ltm.pos.y;
                if (lv_64 > flt_4290D0)
                {
                    fp_68 = 0;
#ifdef CODFH_SP
                    // shape: the scaled squares in one vector (SP 0x79250 keeps all three on the FPU)
                    RwV3d scaled;

                    scaled.x = lcl_60.x * lcl_60.x * ebp_14->unk_7C->unk_0C.x;
                    scaled.y = lcl_60.y * lcl_60.y * ebp_14->unk_7C->unk_0C.y;
                    scaled.z = lcl_60.z * lcl_60.z * ebp_14->unk_7C->unk_0C.z;
                    fp_6C = scaled.x + scaled.y + scaled.z;
#else
                    v7C = lcl_60.x * lcl_60.x * ebp_14->unk_7C->unk_0C.x;
                    var78 = lcl_60.y * lcl_60.y * ebp_14->unk_7C->unk_0C.y;
                    lv_74 = lcl_60.z * lcl_60.z * ebp_14->unk_7C->unk_0C.z;
                    fp_6C = v7C + var78 + lv_74;
#endif
                    if (fp_6C < 1.0f && sub_92FB0(arg_8->vertices[0], arg_8->vertices[1], arg_8->vertices[2]))
                    {
                        fp_68 = 1;
                    }
                    if (fp_68)
                    {
                        lcl_70 = 2;
                    }
                    else
                    {
                        lcl_70 = 1;
                    }
                    sub_992B0(lcl_70, &v44, ebp_14->unk_7C, &arg_0->t.sphere.center, (type_30B90_48 *)arg_8);
                }
            }
        }
        else
        {
            bp_4 = 0;
        }
    }
    if (bp_4)
    {
        RwV3d l8C;              // never used; the image's frame keeps its slot

        ebp_80 = dword_4B25BC;
        if (ebp_80 >= 350)
        {
            sub_974A0(ebp_14, &arg_0->t.sphere.center, ebp_14->unk_4C);
            dword_4B25BC = ebp_80 = 0;
        }
        ebp_80 = ebp_80 * 3;
        dword_4B25C0[ebp_80] = *arg_8->vertices[0];
        dword_4B25C0[ebp_80 + 1] = *arg_8->vertices[1];
        dword_4B25C0[ebp_80 + 2] = *arg_8->vertices[2];
        dword_4B56F8[dword_4B25BC] = arg_8->normal;
        dword_4B25BC++;
    }
    return arg_8;
}
// match: ?sub_985B0@@YAXPAUtype_3D3548@@PAURwFrame@@PAURwV3d@@MPAH2PAM3333PAUtype_3DAFC8_1DDC@@H@Z @ 0x000985B0
// sp-match: ?sub_985B0@@YAXPAUtype_3D3548@@PAURwFrame@@PAURwV3d@@MPAH2PAM3333PAUtype_3DAFC8_1DDC@@H@Z @ 0x00079510
// The soldier's collision search: sub_948A0's sphere (at least 150 across
// with contact records, which also get the wider radii flt_4290D8; else the
// side radius), with the triangles gathered (sub_98200) and pushed out of
// at once (sub_974A0, by the side radius). Then a line from the sphere's
// centre 50000 down finds the ground (sub_99280), tried again 8 and 16
// aside when nothing is hit. Ground within 30 of the frame's base sets the
// frame on it; otherwise *arg_1C says whether there was ground below (or,
// unless arg_30, only a ceiling). The surface goes to the entity's unk_294.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_985B0(type_3D3548 *arg_0, RwFrame *arg_4, RwV3d *arg_8, RwReal arg_C, RwInt32 *arg_10,
               RwV3d *arg_14, RwReal *arg_18, RwInt32 *arg_1C, RwInt32 *arg_20, RwInt32 *arg_24,
               RwInt32 *arg_28, type_3DAFC8_1DDC *arg_2C, RwInt32 arg_30)
{
    RwV3d lcl_158;
    type_4E5D30 *fp_14C;
    RpWorld *loc148;
    type_4E5D30 *p144;
    RpWorld *lcl_140;
    type_4E5D30 *lv_13C;
    RwV3d var138;
    type_99130 l12C;
    RpIntersection u108;
    RpWorld *rEC;
    type_4E5D30 *local_E8;
    type_4E5D30 *locE4;
    RwInt32 q28;
    RwMatrix *frm_24;
    RpIntersection t20;
    RwInt32 bp_4;

    dword_4B25BC = 0;
    *arg_1C = 0;
    *arg_18 = 1e37f;
    // Declared here: its constructor (sub_95030) runs after the stores above.
    type_93DF0 local_E0;
    frm_24 = RwFrameGetLTM(arg_4);
    t20.type = rpINTERSECTSPHERE;
    t20.t.sphere.center = frm_24->pos;
    if (arg_8)
    {
        RwV3dAddMacro(&t20.t.sphere.center, &t20.t.sphere.center, arg_8);
    }
    if (arg_14->x > arg_14->y && arg_14->x > arg_14->z)
    {
        t20.t.sphere.radius = arg_14->x;
    }
    else if (arg_14->y > arg_14->x && arg_14->y > arg_14->z)
    {
        t20.t.sphere.radius = arg_14->y;
    }
    else
    {
        t20.t.sphere.radius = arg_14->z;
    }
    if (arg_2C)
    {
        arg_2C->unk_54[0].unk_00 = 0;
        arg_2C->unk_54[0].unk_04 = 1e37f;
        arg_2C->unk_54[1].unk_00 = 0;
        arg_2C->unk_54[1].unk_04 = 1e37f;
        arg_2C->unk_54[2].unk_00 = 0;
        arg_2C->unk_54[2].unk_04 = 1e37f;
        arg_2C->unk_54[3].unk_00 = 0;
        arg_2C->unk_54[3].unk_04 = 1e37f;
        arg_2C->unk_54[4].unk_00 = 0;
        arg_2C->unk_54[4].unk_04 = 1e37f;
        arg_2C->unk_54[5].unk_00 = 0;
        arg_2C->unk_54[5].unk_04 = 1e37f;
        arg_2C->unk_54[6].unk_00 = 0;
        arg_2C->unk_54[6].unk_04 = 1e37f;
        arg_2C->unk_54[7].unk_00 = 0;
        arg_2C->unk_54[7].unk_04 = 1e37f;
        arg_2C->unk_2D4[0].unk_00 = 0;
        arg_2C->unk_2D4[0].unk_04 = 1e37f;
        arg_2C->unk_2D4[1].unk_00 = 0;
        arg_2C->unk_2D4[1].unk_04 = 1e37f;
        arg_2C->unk_2D4[2].unk_00 = 0;
        arg_2C->unk_2D4[2].unk_04 = 1e37f;
        arg_2C->unk_2D4[3].unk_00 = 0;
        arg_2C->unk_2D4[3].unk_04 = 1e37f;
        arg_2C->unk_00.x = flt_4290D4 + arg_14->x;
        arg_2C->unk_00.y = arg_14->y;
        arg_2C->unk_00.z = flt_4290D4 + arg_14->z;
        arg_2C->unk_0C.x = 1.0f / (arg_2C->unk_00.x * arg_2C->unk_00.x);
        arg_2C->unk_0C.y = 1.0f / (arg_2C->unk_00.y * arg_2C->unk_00.y);
        arg_2C->unk_0C.z = 1.0f / (arg_2C->unk_00.z * arg_2C->unk_00.z);
        arg_2C->unk_18.x = flt_4290D8 + arg_14->x;
        arg_2C->unk_18.y = arg_14->y;
        arg_2C->unk_18.z = flt_4290D8 + arg_14->z;
        arg_2C->unk_24.x = 1.0f / (arg_2C->unk_18.x * arg_2C->unk_18.x);
        arg_2C->unk_24.y = 1.0f / (arg_2C->unk_18.y * arg_2C->unk_18.y);
        arg_2C->unk_24.z = 1.0f / (arg_2C->unk_18.z * arg_2C->unk_18.z);
        arg_2C->unk_30 = frm_24->at;
        arg_2C->unk_30.y = 0.0f;
        RwV3dNormalize(&arg_2C->unk_30, &arg_2C->unk_30);
        arg_2C->unk_3C = frm_24->right;
        arg_2C->unk_3C.y = 0.0f;
        RwV3dNormalize(&arg_2C->unk_3C, &arg_2C->unk_3C);
        if (t20.t.sphere.radius < 150.0f)
        {
            t20.t.sphere.radius = 150.0f;
        }
    }
    else
    {
        t20.t.sphere.radius = arg_14->x * 0.5f * flt_4290F0;
    }
    local_E0.unk_4C = arg_14->x * 0.5f * flt_4290F0;
    local_E0.unk_74 = sub_9A800(arg_0);
    local_E0.unk_6C = arg_8;
    local_E0.unk_24 = t20.t.sphere.radius * t20.t.sphere.radius;
    local_E0.unk_20 = 0;
    local_E0.unk_18 = 0;
    local_E0.unk_04 = arg_0;
    local_E0.unk_14 = arg_4;
    local_E0.unk_0C = 0;
    local_E0.unk_08 = 0;
    local_E0.unk_60 = 0;
    local_E0.unk_64 = 0;
    local_E0.unk_68 = 0;
    local_E0.unk_7C = arg_2C;
    local_E0.unk_80 = arg_18;
    local_E0.unk_90 = 0;
    local_E0.unk_78 = -1;
    local_E0.unk_38[0] = 1.0f / (arg_14->x * arg_14->x);
    local_E0.unk_38[1] = 1.0f / (arg_14->y * arg_14->y);
    local_E0.unk_38[2] = 1.0f / (arg_14->z * arg_14->z);
    local_E0.unk_48 = arg_C;
    local_E0.unk_50 = arg_10;
    local_E0.unk_58 = 0;
    local_E0.unk_54 = 0;
    local_E0.unk_70 = sub_8F940();
    if (arg_0)
    {
        arg_0->unk_54 = local_E0.unk_70;
    }
    bp_4 = 0;
    dword_4B25BC = 0;
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        locE4 = &dword_4E5D30[bp_4];
        if (locE4->get_unk_00() && locE4->get_unk_28())
        {
            local_E0.unk_00 = locE4->get_unk_28();
            RpWorldForAllAtomicIntersections(locE4->get_unk_28(), &t20, sub_943E0, &local_E0);
        }
    }
    for (bp_4 = 0; bp_4 < 4; bp_4++)
    {
        local_E8 = &dword_4E5D30[bp_4];
        if (local_E8->get_unk_00())
        {
            local_E0.unk_00 = local_E8->get_unk_28();
            if ((arg_0->unk_30 & 0x40) && local_E8->get_unk_28())
            {
                RpCollisionWorldForAllIntersections(local_E8->get_unk_28(), &t20, sub_98200, &local_E0);
            }
        }
    }
    if (dword_4B25BC)
    {
        sub_974A0(&local_E0, &t20.t.sphere.center, local_E0.unk_4C);
    }
    *arg_20 = local_E0.unk_60;
    *arg_24 = local_E0.unk_64;
    *arg_28 = local_E0.unk_68;
    if (local_E0.unk_7C)
    {
        local_E0.unk_7C->unk_48 = t20.t.sphere.center;
    }
    q28 = 1;
    *arg_1C = 1;
    if (q28)
    {
        var138 = RwFrameGetLTM(arg_4)->pos;
        u108.type = rpINTERSECTLINE;
        u108.t.line.start = t20.t.sphere.center;
        u108.t.line.end = u108.t.line.start;
        u108.t.line.end.y -= 50000.0f;
        l12C.unk_00 = 0;
        l12C.unk_04 = 0;
        l12C.unk_08 = 1e37f;
        l12C.unk_0C = -1e37f;
        l12C.unk_10 = u108.t.line.start.y;
        l12C.unk_14 = arg_0;
        l12C.unk_18 = -1;
        l12C.unk_1C = -1;
        rEC = 0;
        for (bp_4 = 0; bp_4 < 4; bp_4++)
        {
            lv_13C = &dword_4E5D30[bp_4];
            if (lv_13C->get_unk_00() && (arg_0->unk_30 & 0x40))
            {
                rEC = lv_13C->unk_28;
                if (rEC)
                {
                    l12C.unk_20 = rEC;
                    RpCollisionWorldForAllIntersections(rEC, &u108, sub_99280, &l12C);
                }
            }
        }
        if (!l12C.unk_00 && !l12C.unk_04)
        {
            var138.x = u108.t.line.start.x = u108.t.line.end.x = var138.x + 8.0f;
            var138.z = u108.t.line.start.z = u108.t.line.end.z = var138.z + 8.0f;
            u108.t.line.end.y = var138.y - 25.0f;
            lcl_140 = 0;
            for (bp_4 = 0; bp_4 < 4; bp_4++)
            {
                p144 = &dword_4E5D30[bp_4];
                if (p144->get_unk_00() && (arg_0->unk_30 & 0x40))
                {
                    lcl_140 = p144->unk_28;
                    if (lcl_140)
                    {
                        l12C.unk_20 = lcl_140;
                        RpCollisionWorldForAllIntersections(lcl_140, &u108, sub_99280, &l12C);
                    }
                }
            }
            if (!l12C.unk_00 && !l12C.unk_04)
            {
                var138.x = u108.t.line.start.x = u108.t.line.end.x = var138.x - 16.0f;
                loc148 = 0;
                for (bp_4 = 0; bp_4 < 4; bp_4++)
                {
                    fp_14C = &dword_4E5D30[bp_4];
                    if (fp_14C->get_unk_00() && (arg_0->unk_30 & 0x40))
                    {
                        loc148 = fp_14C->unk_28;
                        if (loc148)
                        {
                            l12C.unk_20 = loc148;
                            RpCollisionWorldForAllIntersections(loc148, &u108, sub_99280, &l12C);
                        }
                    }
                }
            }
        }
        if (l12C.unk_00 || l12C.unk_04)
        {
            if (l12C.unk_00)
            {
                *arg_18 = l12C.unk_08;
                local_E0.unk_78 = l12C.unk_18;
            }
            else
            {
                *arg_18 = l12C.unk_0C;
                local_E0.unk_78 = l12C.unk_1C;
            }
            if (var138.y - 30.0f <= *arg_18)
            {
                *arg_1C = 1;
                *local_E0.unk_50 = 1;
                *arg_20 = 1;
                *arg_24 = 1;
                lcl_158.x = 0.0f;
                lcl_158.y = *arg_18 - var138.y;
                lcl_158.z = 0.0f;
                RwFrameTranslate(local_E0.unk_14, &lcl_158, rwCOMBINEPOSTCONCAT);
                RwFrameUpdateObjects(local_E0.unk_14);
            }
            else if (l12C.unk_04 || (!arg_30 && l12C.unk_00))
            {
                *arg_1C = 1;
            }
            else
            {
                *arg_1C = 0;
            }
        }
        else
        {
            *arg_1C = 0;
        }
    }
    arg_0->unk_5C = t20.t.sphere.center;
    arg_0->unk_294 = local_E0.unk_78;
}
// match: ?sub_99130@@YAXMPAURpIntersection@@PAUtype_99130@@PAURpWorldSector@@PAURpCollisionTriangle@@@Z @ 0x00099130
// sp-match: ?sub_99130@@YAXMPAURpIntersection@@PAUtype_99130@@PAURpWorldSector@@PAURpCollisionTriangle@@@Z @ 0x000759E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_99130(RwReal arg_0, RpIntersection *arg_4, type_99130 *arg_8, RpWorldSector *arg_C,
               RpCollisionTriangle *arg_10)
{
    RwReal var_8;
    RwReal l4;

    l4 = (arg_4->t.line.end.y - arg_4->t.line.start.y) * arg_0 + arg_4->t.line.start.y;
    var_8 = l4 - arg_8->unk_10;
    if (var_8 > 0.0f)
    {
        if (l4 < arg_8->unk_08)
        {
            arg_8->unk_08 = l4;
            arg_8->unk_18 = sub_991F0(arg_8, arg_C, arg_10);
        }
        arg_8->unk_00 = 1;
    }
    else
    {
        if (l4 > arg_8->unk_0C)
        {
            arg_8->unk_0C = l4;
            arg_8->unk_1C = sub_991F0(arg_8, arg_C, arg_10);
        }
        arg_8->unk_04 = 1;
    }
}
// match: ?sub_99280@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00099280
// sp-match: ?sub_99280@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00075A80
RpCollisionTriangle *sub_99280(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10)
{
    type_99130 *var_4;

    var_4 = (type_99130 *)arg_10;
    sub_99130(arg_C, arg_0, var_4, arg_4, arg_8);
    return arg_8;
}
// match: ?sub_992B0@@YAXHPAURwV3d@@PAUtype_3DAFC8_1DDC@@0PAUtype_30B90_48@@@Z @ 0x000992B0
// sp-match: ?sub_992B0@@YAXHPAURwV3d@@PAUtype_3DAFC8_1DDC@@0PAUtype_30B90_48@@@Z @ 0x00075AB0
// Sorts the wall triangle arg_10 (at least 40 wide or 400 high) touched at
// arg_4 into the contact records of arg_8 by its direction from the sphere
// centre arg_C (ahead, right, left, behind against the facing unk_30 and
// right unk_3C) when nearer than the one held and, for all but behind,
// facing the entity (flt_4290CC). arg_0 picks the records: 0 the first set
// (records 0 to 3), 1 the second (4 to 7), 2 either, filling both when
// nearer than both.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_992B0(RwInt32 arg_0, RwV3d *arg_4, type_3DAFC8_1DDC *arg_8, RwV3d *arg_C, type_30B90_48 *arg_10)
{
    RwV3d l60;
    RwReal l54;
    RwReal loc50;
    RwReal x4C;
    RwV3d w48;
    RwV3d ebp_3C;
    RwReal lv_30;
    RwReal fp_2C;
    RwReal q28;
    RwReal frm_24;
    RwReal t20;
    RwInt32 l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;
    RwReal slot_C;
    RwReal bp_8;
    RwReal bp_4;

#ifdef CODFH_SP
    // shape: plain float compares (fcomp memory operands at SP 0x75AB0)
    lv_30 = arg_10->unk_1C->x > arg_10->unk_20->x ? (arg_10->unk_1C->x > arg_10->unk_24->x ? arg_10->unk_1C->x : arg_10->unk_24->x)
              : (arg_10->unk_20->x > arg_10->unk_24->x ? arg_10->unk_20->x : arg_10->unk_24->x);
    frm_24 = arg_10->unk_1C->x < arg_10->unk_20->x ? (arg_10->unk_1C->x < arg_10->unk_24->x ? arg_10->unk_1C->x : arg_10->unk_24->x)
              : (arg_10->unk_20->x < arg_10->unk_24->x ? arg_10->unk_20->x : arg_10->unk_24->x);
#else
    lv_30 = (RwDouble)arg_10->unk_1C->x > (RwDouble)arg_10->unk_20->x ? ((RwDouble)arg_10->unk_1C->x > (RwDouble)arg_10->unk_24->x ? (RwReal)(RwDouble)arg_10->unk_1C->x : (RwReal)(RwDouble)arg_10->unk_24->x)
              : ((RwDouble)arg_10->unk_20->x > (RwDouble)arg_10->unk_24->x ? (RwReal)(RwDouble)arg_10->unk_20->x : (RwReal)(RwDouble)arg_10->unk_24->x);
    frm_24 = (RwDouble)arg_10->unk_1C->x < (RwDouble)arg_10->unk_20->x ? ((RwDouble)arg_10->unk_1C->x < (RwDouble)arg_10->unk_24->x ? (RwReal)(RwDouble)arg_10->unk_1C->x : (RwReal)(RwDouble)arg_10->unk_24->x)
              : ((RwDouble)arg_10->unk_20->x < (RwDouble)arg_10->unk_24->x ? (RwReal)(RwDouble)arg_10->unk_20->x : (RwReal)(RwDouble)arg_10->unk_24->x);
#endif
    fp_2C = fabs(lv_30 - frm_24);
#ifdef CODFH_SP
    slot_C = arg_10->unk_1C->z > arg_10->unk_20->z ? (arg_10->unk_1C->z > arg_10->unk_24->z ? arg_10->unk_1C->z : arg_10->unk_24->z)
              : (arg_10->unk_20->z > arg_10->unk_24->z ? arg_10->unk_20->z : arg_10->unk_24->z);
    loc50 = arg_10->unk_1C->z < arg_10->unk_20->z ? (arg_10->unk_1C->z < arg_10->unk_24->z ? arg_10->unk_1C->z : arg_10->unk_24->z)
              : (arg_10->unk_20->z < arg_10->unk_24->z ? arg_10->unk_20->z : arg_10->unk_24->z);
#else
    slot_C = (RwDouble)arg_10->unk_1C->z > (RwDouble)arg_10->unk_20->z ? ((RwDouble)arg_10->unk_1C->z > (RwDouble)arg_10->unk_24->z ? (RwReal)(RwDouble)arg_10->unk_1C->z : (RwReal)(RwDouble)arg_10->unk_24->z)
              : ((RwDouble)arg_10->unk_20->z > (RwDouble)arg_10->unk_24->z ? (RwReal)(RwDouble)arg_10->unk_20->z : (RwReal)(RwDouble)arg_10->unk_24->z);
    loc50 = (RwDouble)arg_10->unk_1C->z < (RwDouble)arg_10->unk_20->z ? ((RwDouble)arg_10->unk_1C->z < (RwDouble)arg_10->unk_24->z ? (RwReal)(RwDouble)arg_10->unk_1C->z : (RwReal)(RwDouble)arg_10->unk_24->z)
              : ((RwDouble)arg_10->unk_20->z < (RwDouble)arg_10->unk_24->z ? (RwReal)(RwDouble)arg_10->unk_20->z : (RwReal)(RwDouble)arg_10->unk_24->z);
#endif
    m_18 = fabs(slot_C - loc50);
    if (fp_2C > m_18)
    {
        ebp_14 = fp_2C;
    }
    else
    {
        ebp_14 = m_18;
    }
#ifdef CODFH_SP
    x4C = arg_10->unk_1C->y > arg_10->unk_20->y ? (arg_10->unk_1C->y > arg_10->unk_24->y ? arg_10->unk_1C->y : arg_10->unk_24->y)
              : (arg_10->unk_20->y > arg_10->unk_24->y ? arg_10->unk_20->y : arg_10->unk_24->y);
    lv_10 = arg_10->unk_1C->y < arg_10->unk_20->y ? (arg_10->unk_1C->y < arg_10->unk_24->y ? arg_10->unk_1C->y : arg_10->unk_24->y)
              : (arg_10->unk_20->y < arg_10->unk_24->y ? arg_10->unk_20->y : arg_10->unk_24->y);
#else
    x4C = (RwDouble)arg_10->unk_1C->y > (RwDouble)arg_10->unk_20->y ? ((RwDouble)arg_10->unk_1C->y > (RwDouble)arg_10->unk_24->y ? (RwReal)(RwDouble)arg_10->unk_1C->y : (RwReal)(RwDouble)arg_10->unk_24->y)
              : ((RwDouble)arg_10->unk_20->y > (RwDouble)arg_10->unk_24->y ? (RwReal)(RwDouble)arg_10->unk_20->y : (RwReal)(RwDouble)arg_10->unk_24->y);
    lv_10 = (RwDouble)arg_10->unk_1C->y < (RwDouble)arg_10->unk_20->y ? ((RwDouble)arg_10->unk_1C->y < (RwDouble)arg_10->unk_24->y ? (RwReal)(RwDouble)arg_10->unk_1C->y : (RwReal)(RwDouble)arg_10->unk_24->y)
              : ((RwDouble)arg_10->unk_20->y < (RwDouble)arg_10->unk_24->y ? (RwReal)(RwDouble)arg_10->unk_20->y : (RwReal)(RwDouble)arg_10->unk_24->y);
#endif
    q28 = fabs((x4C - lv_10));
    if (ebp_14 < flt_4290E0 && q28 < 400.0f)
    {
        return;
    }
    RwV3dSubMacro(&ebp_3C, arg_4, arg_C);
    t20 = RwV3dDotProductMacro(&ebp_3C, &ebp_3C);
    ebp_3C.y = 0.0f;
    if (t20 != 0.0f)
    {
        RwV3dNormalize(&w48, &ebp_3C);
    }
    else
    {
        w48.x = 0.0f;
        w48.y = 0.0f;
        w48.z = 0.0f;
    }
    bp_8 = RwV3dDotProductMacro(&arg_8->unk_30, &w48);
    l1C = -1;
    if (bp_8 >= dword_4290C0)
    {
        switch (arg_0)
        {
        case 0:
            if (t20 < arg_8->unk_54[0].unk_04)
            {
                l1C = 0;
            }
            break;
        case 1:
            if (t20 < arg_8->unk_54[4].unk_04)
            {
                l1C = 1;
            }
            break;
        case 2:
            if (t20 < arg_8->unk_54[0].unk_04)
            {
                l1C = 0;
            }
            if (t20 < arg_8->unk_54[4].unk_04)
            {
                if (l1C == 0)
                {
                    l1C = 2;
                }
                else
                {
                    l1C = 1;
                }
            }
            break;
        }
        if (l1C != -1)
        {
            bp_4 = RwV3dDotProductMacro(&arg_8->unk_30, &arg_10->unk_00);
            if (bp_4 < flt_4290CC)
            {
                if (l1C == 2 || l1C == 0)
                {
                    arg_8->unk_54[0].unk_00 = 1;
                    arg_8->unk_54[0].unk_08 = *arg_4;
                    arg_8->unk_54[0].unk_04 = t20;
                    arg_8->unk_54[0].unk_14 = arg_10->unk_00;
                    arg_8->unk_54[0].unk_20 = *arg_C;
                    arg_8->unk_54[0].unk_2C = *arg_10->unk_1C;
                    arg_8->unk_54[0].unk_38 = *arg_10->unk_20;
                    arg_8->unk_54[0].unk_44 = *arg_10->unk_24;
                }
                if (l1C == 2 || l1C == 1)
                {
                    arg_8->unk_54[4].unk_00 = 1;
                    arg_8->unk_54[4].unk_08 = *arg_4;
                    arg_8->unk_54[4].unk_04 = t20;
                    arg_8->unk_54[4].unk_14 = arg_10->unk_00;
                    arg_8->unk_54[4].unk_20 = *arg_C;
                    arg_8->unk_54[4].unk_2C = *arg_10->unk_1C;
                    arg_8->unk_54[4].unk_38 = *arg_10->unk_20;
                    arg_8->unk_54[4].unk_44 = *arg_10->unk_24;
                }
            }
        }
    }
#ifdef CODFH_SP
    // shape: compared value first (SP 0x75AB0)
    else if (bp_8 < dword_4290C0 && bp_8 > -dword_4290C4)
#else
    else if (bp_8 < dword_4290C0 && -dword_4290C4 < bp_8)
#endif
    {
        l54 = RwV3dDotProductMacro(&arg_8->unk_3C, &w48);
        if (l54 >= dword_4290C8)
        {
            switch (arg_0)
            {
            case 0:
                if (t20 < arg_8->unk_54[2].unk_04)
                {
                    l1C = 0;
                }
                break;
            case 1:
                if (t20 < arg_8->unk_54[6].unk_04)
                {
                    l1C = 1;
                }
                break;
            case 2:
                if (t20 < arg_8->unk_54[2].unk_04)
                {
                    l1C = 0;
                }
                if (t20 < arg_8->unk_54[6].unk_04)
                {
                    if (l1C == 0)
                    {
                        l1C = 2;
                    }
                    else
                    {
                        l1C = 1;
                    }
                }
                break;
            }
            if (l1C != -1)
            {
                bp_4 = RwV3dDotProductMacro(&arg_8->unk_3C, &arg_10->unk_00);
                if (bp_4 < flt_4290CC)
                {
                    if (l1C == 2 || l1C == 0)
                    {
                        arg_8->unk_54[2].unk_00 = 1;
                        arg_8->unk_54[2].unk_08 = *arg_4;
                        arg_8->unk_54[2].unk_04 = t20;
                        arg_8->unk_54[2].unk_14 = arg_10->unk_00;
                        arg_8->unk_54[2].unk_20 = *arg_C;
                        arg_8->unk_54[2].unk_2C = *arg_10->unk_1C;
                        arg_8->unk_54[2].unk_38 = *arg_10->unk_20;
                        arg_8->unk_54[2].unk_44 = *arg_10->unk_24;
                    }
                    if (l1C == 2 || l1C == 1)
                    {
                        arg_8->unk_54[6].unk_00 = 1;
                        arg_8->unk_54[6].unk_08 = *arg_4;
                        arg_8->unk_54[6].unk_04 = t20;
                        arg_8->unk_54[6].unk_14 = arg_10->unk_00;
                        arg_8->unk_54[6].unk_20 = *arg_C;
                        arg_8->unk_54[6].unk_2C = *arg_10->unk_1C;
                        arg_8->unk_54[6].unk_38 = *arg_10->unk_20;
                        arg_8->unk_54[6].unk_44 = *arg_10->unk_24;
                    }
                }
            }
        }
#ifdef CODFH_SP
        // shape: compared value first (SP 0x75AB0)
        else if (l54 <= -dword_4290C8)
#else
        else if (-dword_4290C8 >= l54)
#endif
        {
            switch (arg_0)
            {
            case 0:
                if (t20 < arg_8->unk_54[1].unk_04)
                {
                    l1C = 0;
                }
                break;
            case 1:
                if (t20 < arg_8->unk_54[5].unk_04)
                {
                    l1C = 1;
                }
                break;
            case 2:
                if (t20 < arg_8->unk_54[1].unk_04)
                {
                    l1C = 0;
                }
                if (t20 < arg_8->unk_54[5].unk_04)
                {
                    if (l1C == 0)
                    {
                        l1C = 2;
                    }
                    else
                    {
                        l1C = 1;
                    }
                }
                break;
            }
            if (l1C != -1)
            {
                l60.x = -arg_8->unk_3C.x;
                l60.y = arg_8->unk_3C.y;
                l60.z = -arg_8->unk_3C.z;
                bp_4 = RwV3dDotProductMacro(&l60, &arg_10->unk_00);
                if (bp_4 < flt_4290CC)
                {
                    if (l1C == 2 || l1C == 0)
                    {
                        arg_8->unk_54[1].unk_00 = 1;
                        arg_8->unk_54[1].unk_08 = *arg_4;
                        arg_8->unk_54[1].unk_04 = t20;
                        arg_8->unk_54[1].unk_14 = arg_10->unk_00;
                        arg_8->unk_54[1].unk_20 = *arg_C;
                        arg_8->unk_54[1].unk_2C = *arg_10->unk_1C;
                        arg_8->unk_54[1].unk_38 = *arg_10->unk_20;
                        arg_8->unk_54[1].unk_44 = *arg_10->unk_24;
                    }
                    if (l1C == 2 || l1C == 1)
                    {
                        arg_8->unk_54[5].unk_00 = 1;
                        arg_8->unk_54[5].unk_08 = *arg_4;
                        arg_8->unk_54[5].unk_04 = t20;
                        arg_8->unk_54[5].unk_14 = arg_10->unk_00;
                        arg_8->unk_54[5].unk_20 = *arg_C;
                        arg_8->unk_54[5].unk_2C = *arg_10->unk_1C;
                        arg_8->unk_54[5].unk_38 = *arg_10->unk_20;
                        arg_8->unk_54[5].unk_44 = *arg_10->unk_24;
                    }
                }
            }
        }
    }
#ifdef CODFH_SP
    // shape: compared value first (SP 0x75AB0)
    else if (bp_8 <= -dword_4290C0)
#else
    else if (-dword_4290C0 >= bp_8)
#endif
    {
        switch (arg_0)
        {
        case 0:
            if (t20 < arg_8->unk_54[3].unk_04)
            {
                l1C = 0;
            }
            break;
        case 1:
            if (t20 < arg_8->unk_54[7].unk_04)
            {
                l1C = 1;
            }
            break;
        case 2:
            if (t20 < arg_8->unk_54[3].unk_04)
            {
                l1C = 0;
            }
            if (t20 < arg_8->unk_54[7].unk_04)
            {
                if (l1C == 0)
                {
                    l1C = 2;
                }
                else
                {
                    l1C = 1;
                }
            }
            break;
        }
        if (l1C != -1)
        {
            if (l1C == 2 || l1C == 0)
            {
                arg_8->unk_54[3].unk_00 = 1;
                arg_8->unk_54[3].unk_08 = *arg_4;
                arg_8->unk_54[3].unk_04 = t20;
                arg_8->unk_54[3].unk_14 = arg_10->unk_00;
                arg_8->unk_54[3].unk_20 = *arg_C;
                arg_8->unk_54[3].unk_2C = *arg_10->unk_1C;
                arg_8->unk_54[3].unk_38 = *arg_10->unk_20;
                arg_8->unk_54[3].unk_44 = *arg_10->unk_24;
            }
            if (l1C == 2 || l1C == 1)
            {
                arg_8->unk_54[7].unk_00 = 1;
                arg_8->unk_54[7].unk_08 = *arg_4;
                arg_8->unk_54[7].unk_04 = t20;
                arg_8->unk_54[7].unk_14 = arg_10->unk_00;
                arg_8->unk_54[7].unk_20 = *arg_C;
                arg_8->unk_54[7].unk_2C = *arg_10->unk_1C;
                arg_8->unk_54[7].unk_38 = *arg_10->unk_20;
                arg_8->unk_54[7].unk_44 = *arg_10->unk_24;
            }
        }
    }
}
// match: ?sub_9A2D0@@YAXPAUtype_3D3548@@PAURwV3d@@1PAUtype_3DAFC8_1DDC@@@Z @ 0x0009A2D0
// sp-match: ?sub_9A2D0@@YAXPAUtype_3D3548@@PAURwV3d@@1PAUtype_3DAFC8_1DDC@@@Z @ 0x00076550
// Sorts the contact of arg_0 between the points arg_4 and arg_8 by its
// direction on the ground (against arg_C's facing unk_30 and right unk_3C)
// and keeps it in the matching record of arg_C (ahead, right, left,
// behind) when nearer than the one held.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_9A2D0(type_3D3548 *arg_0, RwV3d *arg_4, RwV3d *arg_8, type_3DAFC8_1DDC *arg_C)
{
    RwReal var_4;
    RwReal loc8;
    RwV3d local_14;
    RwV3d local_20;
    RwReal l24;

    RwV3dSub(&local_14, arg_4, arg_8);
    loc8 = RwV3dDotProduct(&local_14, &local_14);
    local_14.y = 0.0f;
    RwV3dNormalize(&local_20, &local_14);
    var_4 = RwV3dDotProduct(&arg_C->unk_30, &local_20);
    if (var_4 >= dword_4290C0)
    {
        if (loc8 < arg_C->unk_2D4[0].unk_04)
        {
            arg_C->unk_2D4[0].unk_00 = 1;
            arg_C->unk_2D4[0].unk_08 = *arg_4;
            arg_C->unk_2D4[0].unk_04 = loc8;
            arg_C->unk_2D4[0].unk_14 = *arg_8;
            *(type_3D3548_384 *)&arg_C->unk_2D4[0].unk_20 = arg_0->get_unk_384_h();
        }
    }
#ifdef CODFH_SP
    // shape: compared value first (SP 0x76550)
    else if (var_4 < dword_4290C0 && var_4 > -dword_4290C4)
#else
    else if (var_4 < dword_4290C0 && -dword_4290C4 < var_4)
#endif
    {
        l24 = RwV3dDotProduct(&arg_C->unk_3C, &local_20);
        if (l24 >= dword_4290C8)
        {
            if (loc8 < arg_C->unk_2D4[2].unk_04)
            {
                arg_C->unk_2D4[2].unk_00 = 1;
                arg_C->unk_2D4[2].unk_08 = *arg_4;
                arg_C->unk_2D4[2].unk_04 = loc8;
                arg_C->unk_2D4[2].unk_14 = *arg_8;
                *(type_3D3548_384 *)&arg_C->unk_2D4[2].unk_20 = arg_0->get_unk_384_h();
            }
        }
#ifdef CODFH_SP
        // shape: compared value first (SP 0x76550)
        else if (l24 <= -dword_4290C8)
#else
        else if (-dword_4290C8 >= l24)
#endif
        {
            // Measured against the right record's distance, as the image does.
            if (loc8 < arg_C->unk_2D4[2].unk_04)
            {
                arg_C->unk_2D4[1].unk_00 = 1;
                arg_C->unk_2D4[1].unk_08 = *arg_4;
                arg_C->unk_2D4[1].unk_04 = loc8;
                arg_C->unk_2D4[1].unk_14 = *arg_8;
                *(type_3D3548_384 *)&arg_C->unk_2D4[1].unk_20 = arg_0->get_unk_384_h();
            }
        }
    }
#ifdef CODFH_SP
    // shape: compared value first (SP 0x76550)
    else if (var_4 <= -dword_4290C0)
#else
    else if (-dword_4290C0 >= var_4)
#endif
    {
        if (loc8 < arg_C->unk_2D4[2].unk_04)
        {
            arg_C->unk_2D4[3].unk_00 = 1;
            arg_C->unk_2D4[3].unk_08 = *arg_4;
            arg_C->unk_2D4[3].unk_04 = loc8;
            arg_C->unk_2D4[3].unk_14 = *arg_8;
            *(type_3D3548_384 *)&arg_C->unk_2D4[3].unk_20 = arg_0->get_unk_384_h();
        }
    }
}
// match: ?sub_9A5F0@@YAHPAURwV3d@@0PAURpIntersection@@PAM@Z @ 0x0009A5F0
// sp-match: ?sub_9A5F0@@YAHPAURwV3d@@0PAURpIntersection@@PAM@Z @ 0x00076800
// Intersects the line arg_8 with the ellipsoid at arg_0 whose inverse
// squared radii are arg_4: the nearest crossing in [0, 1] into *arg_C.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_9A5F0(RwV3d *arg_0, RwV3d *arg_4, RpIntersection *arg_8, RwReal *arg_C)
{
    RwReal local_54;
    RwReal local_50;
    RwReal stk_4C;
    RwReal loc48;
    RwReal var_44;
    RwV3d ebp_40;
    RwReal v34;
    RwReal v30;
    RwV3d var_2C;
    RwReal v20;
    RwReal slot_1C;
    RwV3d var_18;
    RwV3d var_C;

    RwV3dSub(&var_2C, &arg_8->t.line.end, &arg_8->t.line.start);
    RwV3dSub(&var_C, &arg_8->t.line.start, arg_0);
    ebp_40.x = var_2C.x * arg_4->x;
    ebp_40.y = var_2C.y * arg_4->y;
    ebp_40.z = var_2C.z * arg_4->z;
    var_18.x = var_C.x * arg_4->x;
    var_18.y = var_C.y * arg_4->y;
    var_18.z = var_C.z * arg_4->z;
    v34 = RwV3dDotProduct(&var_2C, &ebp_40);
    v20 = RwV3dDotProduct(&var_2C, &var_18);
    v30 = RwV3dDotProduct(&var_C, &var_18) - 1.0f;
    slot_1C = v20 * v20 - v34 * v30;
    if (slot_1C < 0.0f)
    {
        return 0;
    }
    if (slot_1C > 0.0f)
    {
        loc48 = sqrt(slot_1C);
        local_50 = 1.0f / v34;
        stk_4C = (-v20 - loc48) * local_50;
        var_44 = (-v20 + loc48) * local_50;
        if (stk_4C > 1.0f || var_44 < 0.0f)
        {
            return 0;
        }
        if (stk_4C >= 0.0f)
        {
            *arg_C = stk_4C;
            return 1;
        }
        *arg_C = var_44;
        return 1;
    }
    local_54 = -v20 / v34;
    if (local_54 >= 0.0f && local_54 <= 1.0f)
    {
        *arg_C = local_54;
        return 1;
    }
    return 0;
}
// match: ?sub_9A800@@YAIPAUtype_3D3548@@@Z @ 0x0009A800
// sp-match: ?sub_9A800@@YAIPAUtype_3D3548@@@Z @ 0x000769C0
RwUInt32 sub_9A800(type_3D3548 *arg_0)
{
    if (arg_0->unk_2C_4)
    {
        return 0x10000;         // not an address: a material flag
    }
    if (arg_0->unk_2C_7)
    {
        return 0x40000;         // not an address: a material flag
    }
    if (arg_0->unk_2C_5)
    {
        return 0x20000;         // not an address: a material flag
    }
    if (arg_0->unk_2C_21)
    {
        return 0x20000;         // not an address: a material flag
    }
    return 0;
}
// match: ?sub_9A860@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x0009A860
// sp-match: ?sub_9A860@@YAPAURpAtomic@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00079D10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpAtomic *sub_9A860(RpIntersection *arg_0, RpWorldSector *arg_4, RpAtomic *arg_8, RwReal arg_C,
                    void *arg_10)
{
    RwFrame *var_14;
    RwUInt32 lv_10;
    type_93DF0 *var_C;
    RwInt32 bp_8;
    type_3D3548 *bp_4;

    if (sub_FB9C0(arg_8) & 8)
    {
        return arg_8;
    }
    var_C = (type_93DF0 *)arg_10;
    bp_4 = sub_FB960(arg_8);
    bp_8 = 0;
    if (bp_4 && bp_4->unk_54 != var_C->unk_70 && bp_4->unk_28_2)
    {
        lv_10 = var_C->unk_0C->unk_00 & 0x3FFFFF0;
        if (lv_10 & bp_4->unk_30)
        {
            bp_8 = 1;
        }
    }
    if (bp_8)
    {
        var_14 = RpAtomicGetFrame(arg_8);
        var_C->unk_18 = RwFrameGetLTM(var_14);
        var_C->unk_5C = 1;
        var_C->unk_08 = bp_4;
        var_C->unk_10 = arg_8;
        if (var_C->unk_5C && var_C->unk_70 != bp_4->unk_54)
        {
            var_C->unk_08->vf_068(var_C->unk_0C);
            bp_4->unk_54 = var_C->unk_70;
        }
    }
    return arg_8;
}
// match: ?sub_9A960@@YAXPAUtype_4AE70@@@Z @ 0x0009A960
// sp-match: ?sub_9A960@@YAXPAUtype_4AE70@@@Z @ 0x00079DA0
// Sets off the blast arg_0: a sphere at its matrix's position plus its
// offset, of its largest radius, handed with a search context (the blast as
// its explosion, its inverse squared radii, a new search id) to every
// atomic it touches in the collision worlds (sub_9A860).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_9A960(type_4AE70 *arg_0)
{
    RwInt32 var_4;
    RpIntersection var20;
    type_93DF0 local_D8;
    RwReal bp_DC;
    type_4E5D30 *vE0;

    var20.type = rpINTERSECTSPHERE;
    var20.t.sphere.center = arg_0->unk_0C->pos;
    RwV3dAdd(&var20.t.sphere.center, &arg_0->unk_1C, &var20.t.sphere.center);
    if (arg_0->unk_10 > arg_0->unk_14 && arg_0->unk_10 > arg_0->unk_18)
    {
        var20.t.sphere.radius = arg_0->unk_10;
    }
    else if (arg_0->unk_14 > arg_0->unk_10 && arg_0->unk_14 > arg_0->unk_18)
    {
        var20.t.sphere.radius = arg_0->unk_14;
    }
    else
    {
        var20.t.sphere.radius = arg_0->unk_18;
    }
    bp_DC = var20.t.sphere.radius * var20.t.sphere.radius;
    local_D8.unk_6C = &arg_0->unk_1C;
    local_D8.unk_24 = bp_DC;
    local_D8.unk_20 = 0;
    local_D8.unk_18 = 0;
    local_D8.unk_04 = 0;
    local_D8.unk_0C = (type_758F0 *)arg_0;
    local_D8.unk_14 = 0;
    local_D8.unk_38[0] = 1.0f / (arg_0->unk_10 * arg_0->unk_10);
    local_D8.unk_38[1] = 1.0f / (arg_0->unk_14 * arg_0->unk_14);
    local_D8.unk_38[2] = 1.0f / (arg_0->unk_18 * arg_0->unk_18);
    local_D8.unk_48 = 0;
    local_D8.unk_50 = 0;
    local_D8.unk_58 = 0;
    local_D8.unk_54 = 0;
    local_D8.unk_70 = sub_8F940();
    arg_0->unk_28 = local_D8.unk_70;
    var_4 = 0;
    for (var_4 = 0; var_4 < 4; var_4++)
    {
        vE0 = &dword_4E5D30[var_4];
        if (vE0->get_unk_00() != 0 && vE0->get_unk_28() != 0)
        {
            RpWorldForAllAtomicIntersections(vE0->get_unk_28(), &var20, sub_9A860, &local_D8);
        }
    }
    if (unk_4E5CD8.unk_00 != 0 && get_4E5D00() != 0)
    {
        RpWorldForAllAtomicIntersections(get_4E5D00(), &var20, sub_9A860, &local_D8);
    }
}
// match: ?sub_9ABE0@@YAHPAURwV3d@@PAURwMatrixTag@@MMM@Z @ 0x0009ABE0
// sp-match: ?sub_9ABE0@@YAHPAURwV3d@@PAURwMatrixTag@@MMM@Z @ 0x00079F70
// Whether the point arg_0 lies inside the box at the matrix arg_4 with the
// half-extents arg_8, arg_C and arg_10 (strictly).
RwInt32 sub_9ABE0(RwV3d *arg_0, RwMatrix *arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10)
{
    RwMatrix var_40;
    RwV3d var_4C;

    RwMatrixSetIdentityMacro(&var_40);
    RwMatrixInvert(&var_40, arg_4);
    sub_1414C0(&var_4C, arg_0, &var_40);
    if (-arg_8 < var_4C.x && var_4C.x < arg_8 && -arg_C < var_4C.y && var_4C.y < arg_C
        && -arg_10 < var_4C.z && var_4C.z < arg_10)
    {
        return 1;
    }
    return 0;
}
// Whether arg_0 is less than arg_8 from arg_4.
// match: ?sub_9ACE0@@YAHPAURwV3d@@0M@Z @ 0x0009ACE0
// sp-match: ?sub_9ACE0@@YAHPAURwV3d@@0M@Z @ 0x0007A080
RwInt32 sub_9ACE0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8)
{
    RwReal var_4;
    RwV3d var_10;

    RwV3dSubMacro(&var_10, arg_0, arg_4);
    var_4 = RwV3dLength(&var_10);
    if (var_4 < arg_8)
    {
        return 1;
    }
    return 0;
}
