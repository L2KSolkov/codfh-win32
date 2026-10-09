// Math helpers after the soldier: angles, vectors and quaternions.

#include <math.h>
#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "rw/rtquat.h"
#include "game/functions.h"
#include "types/animkey.h"
#include "types/vec4.h"
#include "rw/bamatrix.h"
#include "game/decals.h"
#include "types/type_44350.h"
#include "game/gameloop.h"
#include <string.h>

extern "C" void _WriteBarrier();
#pragma intrinsic(_WriteBarrier)

// Its data definitions (PLAN M5), in the image's address order.
// 0x004CFA00
RwInt32 dword_4CFA00;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@3ff0000000000000 @ 0x003DB3B8
// match: __real@bf7fbe77 @ 0x003DB3C0

// match: sub_13F9E0 @ 0x0013F9E0
// sp-match: sub_13F9E0 @ 0x000EC2E0

RwReal sub_13F9E0(RwReal arg_0)
{
    RwReal var_4;

    var_4 = fmod(arg_0, 360.0f);
    if (var_4 > 180.0f)
        var_4 -= 360.0f;
    if (var_4 < -180.0f)
        var_4 += 360.0f;
    return var_4;
}

// match: sub_13FA50 @ 0x0013FA50
// sp-match: sub_13FA50 @ 0x000EC320
// Normalises *arg_0 in place and returns its length (0 for a zero vector,
// which it leaves as it is).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_13FA50(RwV3d *arg_0)
{
    RwReal var_4;
    RwReal v8;
    RwReal varC;

    var_4 = arg_0->x * arg_0->x + arg_0->y * arg_0->y + arg_0->z * arg_0->z;
    if (var_4 != 0.0f)
    {
        v8 = sqrt(var_4);
        varC = 1.0f / v8;
    }
    else
    {
        v8 = 0.0f;
        varC = v8;
    }
    arg_0->x = varC * arg_0->x;
    arg_0->y = varC * arg_0->y;
    arg_0->z = varC * arg_0->z;
    return v8;
}

// match: sub_13FB00 @ 0x0013FB00
// sp-match: sub_13FB00 @ 0x000EC390
void sub_13FB00(RtQuat *arg_0, RtQuat *arg_4)
{
    RwDouble var_8;
    RwDouble var_10;

    var_8 = arg_4->real * arg_4->real + arg_4->imag.x * arg_4->imag.x + arg_4->imag.y * arg_4->imag.y
            + arg_4->imag.z * arg_4->imag.z;
    if (var_8 > 0.0)
        var_10 = 1.0 / sqrt(var_8);
    else
        var_10 = 1.0;
    arg_0->real = (RwReal)var_10 * arg_4->real;
    arg_0->imag.x = (RwReal)var_10 * arg_4->imag.x;
    arg_0->imag.y = (RwReal)var_10 * arg_4->imag.y;
    arg_0->imag.z = (RwReal)var_10 * arg_4->imag.z;
}

// match: sub_13FBC0 @ 0x0013FBC0
// sp-match: sub_13FBC0 @ 0x000EC400
// The rotation arg_4 slerped towards arg_8 by arg_C, into *arg_0 (arg_8
// negated when they are more than 90 degrees apart; a straight blend when
// they are within about 2.5 degrees).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_13FBC0(RtQuat *arg_0, RtQuat *arg_4, RtQuat *arg_8, RwReal arg_C)
{
    RwReal var_4;
    RwReal v8;
    RwReal stk_C;
    RwReal var_10;

    var_4 = RwV3dDotProductMacro(&arg_4->imag, &arg_8->imag) + arg_4->real * arg_8->real;
    if (var_4 < 0.0f)
    {
        var_4 = -var_4;
        RwV3dNegateMacro(&arg_8->imag, &arg_8->imag);
        arg_8->real = -arg_8->real;
    }
    v8 = 1.0f - arg_C;
    if (var_4 < 0.999f)
    {
        var_10 = acos(0.99999f > (var_4 > -0.99999f ? var_4 : -0.99999f)
                          ? (var_4 > -0.99999f ? var_4 : -0.99999f)
                          : 0.99999f);
        stk_C = 1.0f / sin(var_10);
        v8 = sin(v8 * var_10) * stk_C;
        arg_C = sin(arg_C * var_10) * stk_C;
    }
    arg_0->imag.x = v8 * arg_4->imag.x + arg_C * arg_8->imag.x;
    arg_0->imag.y = v8 * arg_4->imag.y + arg_C * arg_8->imag.y;
    arg_0->imag.z = v8 * arg_4->imag.z + arg_C * arg_8->imag.z;
    arg_0->real = v8 * arg_4->real + arg_C * arg_8->real;
}

// match: sub_13FDA0 @ 0x0013FDA0
// sp-match: sub_13FDA0 @ 0x000EC530
// The rotation by the vector *arg_0 (its length the angle, in radians, about
// its direction) as the unit quaternion *arg_4; none for a zero vector.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_13FDA0(RwV3d *arg_0, RtQuat *arg_4)
{
    RwReal var_4;
    RwReal v8;
    RwReal varC;

    var_4 = RwV3dLength((RwV3d *)arg_0);
    if (var_4 == 0.0f)
    {
        arg_4->imag.z = 0.0f;
        arg_4->imag.y = 0.0f;
        arg_4->imag.x = 0.0f;
        arg_4->real = 1.0f;
    }
    else
    {
        varC = 0.5f * var_4;
        v8 = sin(varC);
        var_4 = 1.0f / var_4;
#ifdef CODFH_SP // shape: the scale applied to the component first
        arg_4->imag.x = v8 * (var_4 * arg_0->x);
        arg_4->imag.y = v8 * (var_4 * arg_0->y);
        arg_4->imag.z = v8 * (var_4 * arg_0->z);
#else
        arg_4->imag.x = var_4 * arg_0->x * v8;
        arg_4->imag.y = var_4 * arg_0->y * v8;
        arg_4->imag.z = var_4 * arg_0->z * v8;
#endif
        arg_4->real = cos(varC);
        sub_13FB00(arg_4, arg_4);
    }
}

// match: sub_13FE90 @ 0x0013FE90
// sp-match: sub_13FE90 @ 0x000EC5C0
// The product of the quaternions arg_8 and arg_4 (arg_8 applied after
// arg_4), into *arg_0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_13FE90(RtQuat *arg_0, RtQuat *arg_4, RtQuat *arg_8)
{
#ifdef CODFH_SP
    // shape: SP 0xEC5C0 computes into a quaternion on the frame and loads the first operand of each
    // product as written; volatile reads (SP_FRESH, nine) give those loads and the dot's order
#define SP_FRESH(x) (*(volatile RwReal *)&(x))
    RtQuat q;

    q.real = SP_FRESH(arg_8->real) * arg_4->real
             - (SP_FRESH(arg_4->imag.x) * SP_FRESH(arg_8->imag.x) + SP_FRESH(arg_8->imag.z) * arg_4->imag.z
                + arg_8->imag.y * arg_4->imag.y);
    q.imag.x = SP_FRESH(arg_8->real) * arg_4->imag.x + SP_FRESH(arg_8->imag.y) * arg_4->imag.z
               + arg_8->imag.x * arg_4->real - arg_8->imag.z * arg_4->imag.y;
    q.imag.y = SP_FRESH(arg_8->imag.z) * arg_4->imag.x + arg_8->real * arg_4->imag.y
               + arg_8->imag.y * arg_4->real - SP_FRESH(arg_8->imag.x) * arg_4->imag.z;
    q.imag.z = SP_FRESH(arg_8->real) * arg_4->imag.z + arg_8->imag.z * arg_4->real
               + arg_8->imag.x * arg_4->imag.y - arg_8->imag.y * arg_4->imag.x;
    arg_0->real = q.real;
    arg_0->imag.x = q.imag.x;
    arg_0->imag.y = q.imag.y;
    arg_0->imag.z = q.imag.z;
#undef SP_FRESH
#else
    RwReal var_4;
    RwReal v8;
    RwReal stk_C;
    RwReal var_10;

    var_4 = arg_8->real * arg_4->real
            - (arg_8->imag.x * arg_4->imag.x + arg_8->imag.y * arg_4->imag.y
               + arg_8->imag.z * arg_4->imag.z);
    var_10 = arg_8->real * arg_4->imag.x + arg_4->real * arg_8->imag.x
             + arg_8->imag.y * arg_4->imag.z - arg_8->imag.z * arg_4->imag.y;
    stk_C = arg_8->real * arg_4->imag.y + arg_4->real * arg_8->imag.y
            + arg_8->imag.z * arg_4->imag.x - arg_8->imag.x * arg_4->imag.z;
    v8 = arg_8->real * arg_4->imag.z + arg_4->real * arg_8->imag.z
            + arg_8->imag.x * arg_4->imag.y - arg_8->imag.y * arg_4->imag.x;
    arg_0->real = var_4;
    arg_0->imag.x = var_10;
    arg_0->imag.y = stk_C;
    arg_0->imag.z = v8;
#endif
}

#pragma warning(push)
#pragma warning(disable : 4716)
// match: sub_13FFA0 @ 0x0013FFA0
// sp-match: sub_13FFA0 @ 0x000EC660
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *sub_13FFA0(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8)
{
    RwV3d var_C;
    RwReal local_10;
    RwReal stk_14;
    RwV3d local_20;
    RwReal l24;

    local_10 = cos(arg_8);
    l24 = sin(arg_8);
#ifdef CODFH_SP
    // shape: SP 0xEC660 scales component by component and loads the first operand of each product
    // below fresh (volatile reads), where VC would make an operand it has read the memory one
#define SP_FRESH(x) (*(volatile RwReal *)&(x))
    var_C.x = arg_0->x * local_10;
    var_C.y = arg_0->y * local_10;
    var_C.z = arg_0->z * local_10;
    stk_14 = (1.0f - local_10)
             * (SP_FRESH(arg_0->x) * arg_4->x + SP_FRESH(arg_0->y) * arg_4->y + SP_FRESH(arg_4->z) * arg_0->z);
    local_20.x = arg_4->x * stk_14;
    local_20.y = arg_4->y * stk_14;
    local_20.z = arg_4->z * stk_14;
    RwV3dAddMacro(&var_C, &var_C, &local_20);
    local_20.x = arg_4->y * arg_0->z - arg_0->y * arg_4->z;
    local_20.y = SP_FRESH(arg_4->z) * arg_0->x - arg_4->x * arg_0->z;
    local_20.z = SP_FRESH(arg_0->y) * arg_4->x - SP_FRESH(arg_0->x) * arg_4->y;
#undef SP_FRESH
#else
    RwV3dScaleMacro(&var_C, arg_0, local_10);
    stk_14 = (1.0f - local_10) * RwV3dDotProductMacro(arg_4, arg_0);
    RwV3dScaleMacro(&local_20, arg_4, stk_14);
    RwV3dAddMacro(&var_C, &var_C, &local_20);
    RwV3dCrossProductMacro(&local_20, arg_4, arg_0);
#endif
    RwV3dScaleMacro(&local_20, &local_20, l24);
    RwV3dAddMacro(&var_C, &var_C, &local_20);
    *arg_0 = var_C;
    // No return statement: eax still holds arg_0 from the copy (C4716).
}
#pragma warning(pop)
// match: sub_140130 @ 0x00140130
// The point *arg_4 through the 4x4 matrix arg_8, divided by its w, into
// *arg_0.
void sub_140130(RwV3d *arg_0, RwV3d *arg_4, type_8BFA0 *arg_8)
{
    type_140490 var_10;

    var_10.x = arg_4->x;
    var_10.y = arg_4->y;
    var_10.z = arg_4->z;
    var_10.w = 1.0f;
    sub_1401B0(&var_10, &var_10, arg_8);
    arg_0->x = var_10.x / var_10.w;
    arg_0->y = var_10.y / var_10.w;
    arg_0->z = var_10.z / var_10.w;
}
// match: sub_1401B0 @ 0x001401B0
// The vector *arg_4 through the 4x4 matrix arg_8 (rows times the vector's
// components), into *arg_0. Only the matrix's first row is copied into its
// local (0x10 bytes): the other rows are whatever the stack held.
void sub_1401B0(type_140490 *arg_0, type_140490 *arg_4, type_8BFA0 *arg_8)
{
    type_8BFA0 var_40;
    type_140490 var_50;

    memcpy(&var_40, arg_8, 0x10);
    var_50.x = var_40.unk_00[0].unk_00 * arg_4->x + var_40.unk_00[1].unk_00 * arg_4->y
                    + var_40.unk_00[2].unk_00 * arg_4->z + var_40.unk_00[3].unk_00 * arg_4->w;
    var_50.y = var_40.unk_00[0].unk_04 * arg_4->x + var_40.unk_00[1].unk_04 * arg_4->y
                    + var_40.unk_00[2].unk_04 * arg_4->z + var_40.unk_00[3].unk_04 * arg_4->w;
    var_50.z = var_40.unk_00[0].unk_08 * arg_4->x + var_40.unk_00[1].unk_08 * arg_4->y
                    + var_40.unk_00[2].unk_08 * arg_4->z + var_40.unk_00[3].unk_08 * arg_4->w;
    var_50.w = var_40.unk_00[0].unk_0C * arg_4->x + var_40.unk_00[1].unk_0C * arg_4->y
                    + var_40.unk_00[2].unk_0C * arg_4->z + var_40.unk_00[3].unk_0C * arg_4->w;
    *arg_0 = var_50;
}
// match: sub_1402B0 @ 0x001402B0
// sp-match: sub_1402B0 @ 0x000ED890
// Turns the line *arg_0 about the vertical through its start by arg_4
// degrees.
void sub_1402B0(RwLine *arg_0, RwReal arg_4)
{
    RwV3d var_C;
    RwV3d var_18;
    RwMatrix var_60;

    var_C.x = 0.0f;
    var_C.y = 0.0f;
    var_C.z = 1.0f;
    var_18.x = arg_0->end.x - arg_0->start.x;
    var_18.y = arg_0->end.y - arg_0->start.y;
    var_18.z = arg_0->end.z - arg_0->start.z;
    RwMatrixSetIdentityMacro(&var_60);
    RwMatrixRotate(&var_60, &var_C, arg_4, rwCOMBINEPRECONCAT);
    sub_1414C0(&var_18, &var_18, &var_60);
    arg_0->end.x = var_18.x + arg_0->start.x;
    arg_0->end.y = var_18.y + arg_0->start.y;
    arg_0->end.z = var_18.z + arg_0->start.z;
}
// match: sub_1403D0 @ 0x001403D0
// sp-match: sub_1403D0 @ 0x000EC760
// Sets the line *arg_0's end arg_4 from its start, keeping its direction
// in x and y (z is left as it is).
void sub_1403D0(RwLine *arg_0, RwReal arg_4)
{
    RwV3d var_C;

    var_C.x = arg_0->end.x - arg_0->start.x;
    var_C.y = arg_0->end.y - arg_0->start.y;
    RwV3dNormalize(&var_C, &var_C);
    var_C.x *= arg_4;
    var_C.y *= arg_4;
    arg_0->end.x = var_C.x + arg_0->start.x;
    arg_0->end.y = var_C.y + arg_0->start.y;
}

// match: sub_140440 @ 0x00140440
// sp-match: sub_140440 @ 0x000EC7B0
void sub_140440(RwMatrix *arg_0, RwV3d *arg_4, RwReal arg_8)
{
    sub_13FFA0(&arg_0->up, arg_4, arg_8);
    sub_13FFA0(&arg_0->at, arg_4, arg_8);
    sub_13FFA0(&arg_0->right, arg_4, arg_8);
}

// match: sub_140490 @ 0x00140490
// sp-match: sub_140490 @ 0x000EC7F0
// The weights of the point arg_0 against the triangle arg_4, arg_8, arg_C
// (the areas of the triangles it makes with each edge, projected on the
// triangle's normal) into *arg_10; negative weights are clamped to 0 and
// the rest renormalised. False unless they sum to 1 within 0.001 (the
// point lies outside).
bool sub_140490(type_140490 *arg_0, type_140490 *arg_4, type_140490 *arg_8, type_140490 *arg_C,
                type_140490 *arg_10)
{
    bool var_1;
    bool var_2;
    type_140490 var_20;
    type_140490 var_30;
    type_140490 var_40;
    type_140490 var_50;
    type_140490 var_60;
    type_140490 var_70;
    type_140490 var_80;
    type_140490 var_90;
    type_140490 var_A0;
    RwReal var_A4;
    type_140490 var_C0;
    RwReal var_C4;
    RwReal var_C8;

    var_1 = true;
    var_2 = false;
    RwV3dSubMacro(&var_20, arg_4, arg_0);
    RwV3dSubMacro(&var_30, arg_8, arg_0);
    RwV3dSubMacro(&var_40, arg_0, arg_C);
    RwV3dSubMacro(&var_50, arg_4, arg_C);
    RwV3dSubMacro(&var_60, arg_8, arg_C);
    RwV3dCrossProductMacro(&var_70, &var_20, &var_30);
    RwV3dCrossProductMacro(&var_80, &var_50, &var_60);
    RwV3dCrossProductMacro(&var_90, &var_60, &var_40);
    RwV3dCrossProductMacro(&var_A0, &var_40, &var_50);
    var_A4 = var_70.x + var_70.y + var_70.z;
    if (var_A4 != 0.0f)
    {
        RwV3dNormalize((RwV3d *)&var_C0, (RwV3d *)&var_70);
    }
    else
    {
        var_C0.x = 0.0f;
        var_C0.y = 0.0f;
        var_C0.z = 0.0f;
    }
    var_A4 = RwV3dDotProductMacro(&var_70, &var_C0);
    if (var_A4 != 0.0f)
        var_C4 = 1.0f / var_A4;
    else
        var_C4 = 0.0f;
    arg_10->x = RwV3dDotProductMacro(&var_80, &var_C0) * var_C4;
    if (arg_10->x < 0.0f)
    {
        arg_10->x = 0.0f;
        var_2 = true;
    }
    arg_10->y = RwV3dDotProductMacro(&var_90, &var_C0) * var_C4;
    if (arg_10->y < 0.0f)
    {
        arg_10->y = 0.0f;
        var_2 = true;
    }
    arg_10->z = RwV3dDotProductMacro(&var_A0, &var_C0) * var_C4;
    if (arg_10->z < 0.0f)
    {
        arg_10->z = 0.0f;
        var_2 = true;
    }
    if (var_2)
    {
        var_A4 = arg_10->x + arg_10->y + arg_10->z;
        if (var_A4 != 0.0f)
            var_C8 = 1.0f / var_A4;
        else
            var_C8 = 0.0f;
        arg_10->x = var_C8 * arg_10->x;
        arg_10->y = var_C8 * arg_10->y;
        arg_10->z = var_C8 * arg_10->z;
    }
    if (fabs(arg_10->x + arg_10->y + arg_10->z - 1.0f) > 0.001f)
        var_1 = false;
    return var_1;
}

// match: sub_140910 @ 0x00140910
// sp-match: sub_140910 @ 0x000ECB10
// Copies the matrix *arg_4 into *arg_0, transposing its rotation and
// negating its position (the inverse of a rotation, but the position is not
// rotated back).
void sub_140910(RwMatrix *arg_0, RwMatrix *arg_4)
{
    RwReal var_4;

    memcpy(arg_0, arg_4, sizeof(RwMatrix));
    var_4 = arg_0->right.y;
    arg_0->right.y = arg_0->up.x;
    arg_0->up.x = var_4;
    var_4 = arg_0->right.z;
    arg_0->right.z = arg_0->at.x;
    arg_0->at.x = var_4;
    var_4 = arg_0->up.z;
    arg_0->up.z = arg_0->at.y;
    arg_0->at.y = var_4;
    RwV3dScaleMacro(&arg_0->pos, &arg_0->pos, -1.0f);
}

// match: sub_1409C0 @ 0x001409C0
// sp-match: sub_1409C0 @ 0x000ECB70
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_1409C0(RwV3d *arg_0, RwMatrix *arg_4, RwReal arg_8, RwReal arg_C)
{
    RwV3d *l4;
    RwV3d *var_8;
    RwV3d fp_14;
    RwV3d *var_18;
    RwReal slot_1C;
    RwV3d *v20;
    RwV3d l2C;
    RwV3d v38;

    v20 = &arg_4->at;
    var_8 = &arg_4->right;
    var_18 = &arg_4->pos;
    RwV3dSubMacro(&l2C, arg_0, var_18);
    RwV3dScaleMacro(&v38, var_8, RwV3dDotProductMacro(&l2C, var_8));
    RwV3dScaleMacro(&fp_14, v20, (RwV3dDotProductMacro(&l2C, v20)));
    RwV3dAddMacro(&v38, &v38, &fp_14);
    RwV3dNormalize(&v38, &v38);
    slot_1C = RwV3dDotProductMacro(&v38, v20);
    if (slot_1C < arg_8)
        return 0;
    l4 = &arg_4->up;
    RwV3dScaleMacro(&v38, l4, RwV3dDotProductMacro(&l2C, l4));
    RwV3dAddMacro(&v38, &v38, &fp_14);
    RwV3dNormalize(&v38, &v38);
    slot_1C = RwV3dDotProductMacro(&v38, v20);
    slot_1C = absref(slot_1C);
    if (slot_1C < arg_C)
        return 0;
    return 1;
}

// match: sub_140C90 @ 0x00140C90
// sp-match: sub_140C90 @ 0x000ECD10
RwReal sub_140C90(RwV3d *arg_0, RwV3d *arg_4)
{
    RwV3d var_C;

    RwV3dSubMacro(&var_C, arg_0, arg_4);
    return RwV3dDotProductMacro(&var_C, &var_C);
}

// match: sub_140CE0 @ 0x00140CE0
// sp-match: sub_140CE0 @ 0x000ECD40
void sub_140CE0(RwMatrix *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwReal var_4;
    RwV3d var_10;

    RwMatrixSetIdentityMacro(arg_0);
    var_10.x = 0.0f;
    var_10.y = 1.0f;
    var_10.z = 0.0f;
    arg_0->pos = *arg_4;
    RwV3dNormalize(&arg_0->at, arg_8);
    var_4 = RwV3dDotProductMacro(&arg_0->at, &var_10);
    if (var_4 > 0.999f || var_4 < -0.999f)
    {
        var_10.x = 0.0f;
        var_10.y = 0.0f;
        var_10.z = 1.0f;
    }
    RwV3dCrossProductMacro(&arg_0->right, &var_10, &arg_0->at);
    RwV3dNormalize(&arg_0->right, &arg_0->right);
    RwV3dCrossProductMacro(&arg_0->up, &arg_0->at, &arg_0->right);
    RwV3dNormalize(&arg_0->up, &arg_0->up);
    RwMatrixOptimize(arg_0, 0);
}

// match: sub_140F00 @ 0x00140F00
// sp-match: sub_140F00 @ 0x000ECE90
void sub_140F00(RwMatrix *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwReal var_4;
    RwV3d var_10;

    var_10.x = 0.0f;
    var_10.y = 0.0f;
    var_10.z = 1.0f;
    var_4 = RwV3dDotProductMacro(&var_10, arg_8);
    if (var_4 > 0.999f || var_4 < -0.999f)
    {
        var_10.x = 0.0f;
        var_10.y = 1.0f;
        var_10.z = 0.0f;
    }
    arg_0->pos = *arg_4;
    arg_0->up = *arg_8;
    RwV3dCrossProductMacro(&arg_0->right, arg_8, &var_10);
    RwV3dNormalize(&arg_0->right, &arg_0->right);
    RwV3dCrossProductMacro(&arg_0->at, arg_8, &arg_0->right);
    RwV3dNormalize(&arg_0->at, &arg_0->at);
}

// match: sub_141080 @ 0x00141080
// sp-match: sub_141080 @ 0x000ECF90
// The rotation by the angles *arg_4 (about x, then y, then z) at the
// position *arg_8 (none for 0), written into *arg_0 as a 4x4 matrix (its
// flags and pads 0, the last 1).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_141080(RwMatrix *arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwReal l4;
    RwReal var_8;
    RwReal fp_C;
    type_8BFA0 *local_10;
    RwReal stk_14;
    RwReal lcl_18;
    RwReal fp_1C;

    // Each angle is loaded straight into the call and the result rounded
    // through a float temporary: the float overload would copy the member
    // into a parameter slot first.
    fp_1C = (RwReal)(RwDouble)(RwReal)sin((RwDouble)arg_4->x);
    stk_14 = (RwReal)(RwDouble)(RwReal)cos((RwDouble)arg_4->x);
    lcl_18 = (RwReal)(RwDouble)(RwReal)sin((RwDouble)arg_4->y);
    var_8 = (RwReal)(RwDouble)(RwReal)cos((RwDouble)arg_4->y);
    fp_C = (RwReal)(RwDouble)(RwReal)sin((RwDouble)arg_4->z);
    l4 = (RwReal)(RwDouble)(RwReal)cos((RwDouble)arg_4->z);
    local_10 = (type_8BFA0 *)arg_0;
    local_10->unk_00[0].unk_00 = l4 * var_8;
    local_10->unk_00[0].unk_04 = fp_C * var_8;
    local_10->unk_00[0].unk_08 = -lcl_18;
    local_10->unk_00[0].unk_0C = 0.0f;
    local_10->unk_00[1].unk_00 = l4 * lcl_18 * fp_1C - fp_C * stk_14;
    local_10->unk_00[1].unk_04 = fp_C * lcl_18 * fp_1C + l4 * stk_14;
    local_10->unk_00[1].unk_08 = var_8 * fp_1C;
    local_10->unk_00[1].unk_0C = 0.0f;
    local_10->unk_00[2].unk_00 = l4 * lcl_18 * stk_14 + fp_C * fp_1C;
    local_10->unk_00[2].unk_04 = fp_C * lcl_18 * stk_14 - l4 * fp_1C;
    local_10->unk_00[2].unk_08 = var_8 * stk_14;
    // Keep the completed rotation stores before the translation test (SP 0xECF90).
    // This compiler ordering intrinsic emits no instructions in either build.
    _WriteBarrier();
    local_10->unk_00[2].unk_0C = 0.0f;
    if (arg_8)
    {
        local_10->unk_00[3].unk_00 = arg_8->x;
        local_10->unk_00[3].unk_04 = arg_8->y;
        local_10->unk_00[3].unk_08 = arg_8->z;
    }
    else
    {
        local_10->unk_00[3].unk_00 = 0.0f;
        local_10->unk_00[3].unk_04 = 0.0f;
        local_10->unk_00[3].unk_08 = 0.0f;
    }
    local_10->unk_00[3].unk_0C = 1.0f;
}

// match: sub_141240 @ 0x00141240
// sp-match: sub_141240 @ 0x000ED070
// The signed angle in degrees from *arg_4 to *arg_0 in the ground (x, z)
// plane; the vectors are taken as unit ones.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_141240(RwV3d *arg_0, RwV3d *arg_4)
{
    RwReal var_4;
    RwReal local_8;

    var_4 = arg_0->x * arg_4->x + arg_0->z * arg_4->z;
    local_8 = arg_0->z * arg_4->x - arg_4->z * arg_0->x;
    var_4 = acos(0.99999f > (var_4 > -0.99999f ? var_4 : -0.99999f)
                     ? (var_4 > -0.99999f ? var_4 : -0.99999f)
                     : 0.99999f)
            * 57.2957764f;
    if (local_8 < 0.0f)
        var_4 = -var_4;
    return var_4;
}

// match: sub_141320 @ 0x00141320
// sp-match: sub_141320 @ 0x000ED0F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *sub_141320(RwV3d *arg_0, RwV3d *arg_4, RwMatrix *arg_8)
{
    RwReal var_4;
    RwReal v8;
    RwReal stk_C;
    RwReal var_10;

    dword_4CFA00++;
    v8 = arg_4->x;
    var_4 = ((v8) * (arg_8->right.x));
    var_10 = ((v8) * (arg_8->right.y));
    stk_C = ((v8) * (arg_8->right.z));
    v8 = arg_4->y;
    var_4 = ((var_4) + (((v8) * (arg_8->up.x))));
    var_10 = ((var_10) + (((v8) * (arg_8->up.y))));
    stk_C = ((stk_C) + (((v8) * (arg_8->up.z))));
    v8 = arg_4->z;
    arg_0->x = ((((v8) * (arg_8->at.x))) + (var_4));
    arg_0->y = ((((v8) * (arg_8->at.y))) + (var_10));
    arg_0->z = ((((v8) * (arg_8->at.z))) + (stk_C));
    return arg_0;
}

// match: sub_1413E0 @ 0x001413E0
// sp-match: sub_1413E0 @ 0x000ED180
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwV3d *sub_1413E0(RwV3d *arg_0, RwV3d *arg_4, RwInt32 arg_8, RwMatrix *arg_C)
{
    RwV3d *var_4;
    RwReal v8;
    RwReal stk_C;
    RwReal var_10;
    RwReal lv_14;

    var_4 = arg_0;
    while (--arg_8 >= 0)
    {
        stk_C = arg_4->x;
        v8 = ((stk_C) * (arg_C->right.x));
        lv_14 = ((stk_C) * (arg_C->right.y));
        var_10 = ((stk_C) * (arg_C->right.z));
        stk_C = arg_4->y;
        v8 = ((v8) + (((stk_C) * (arg_C->up.x))));
        lv_14 = ((lv_14) + (((stk_C) * (arg_C->up.y))));
        var_10 = ((var_10) + (((stk_C) * (arg_C->up.z))));
        stk_C = arg_4->z;
        arg_0->x = ((((stk_C) * (arg_C->at.x))) + (v8));
        arg_0->y = ((((stk_C) * (arg_C->at.y))) + (lv_14));
        arg_0->z = ((((stk_C) * (arg_C->at.z))) + (var_10));
        arg_4++;
        arg_0++;
    }
    return var_4;
}

// match: sub_1414C0 @ 0x001414C0
// sp-match: sub_1414C0 @ 0x000ED440
RwV3d *sub_1414C0(RwV3d *arg_0, RwV3d *arg_4, RwMatrix *arg_8)
{
    RwReal var_4;
    RwReal v8;
    RwReal stk_C;
    RwReal var_10;

    v8 = arg_4->x;
    var_4 = ((v8) * (arg_8->right.x));
    var_10 = ((v8) * (arg_8->right.y));
    stk_C = ((v8) * (arg_8->right.z));
    v8 = arg_4->y;
    var_4 = ((var_4) + (((v8) * (arg_8->up.x))));
    var_10 = ((var_10) + (((v8) * (arg_8->up.y))));
    stk_C = ((stk_C) + (((v8) * (arg_8->up.z))));
    v8 = arg_4->z;
    var_4 = ((var_4) + (((v8) * (arg_8->at.x))));
    var_10 = ((var_10) + (((v8) * (arg_8->at.y))));
    stk_C = ((stk_C) + (((v8) * (arg_8->at.z))));
    arg_0->x = ((var_4) + (arg_8->pos.x));
    arg_0->y = ((var_10) + (arg_8->pos.y));
    arg_0->z = ((stk_C) + (arg_8->pos.z));
    return arg_0;
}

// match: sub_141590 @ 0x00141590
// sp-match: sub_141590 @ 0x000ED4D0
RwV3d *sub_141590(RwV3d *arg_0, RwV3d *arg_4, RwInt32 arg_8, RwMatrix *arg_C)
{
    RwV3d *var_4;
    RwReal v8;
    RwReal stk_C;
    RwReal var_10;
    RwReal lv_14;

    var_4 = arg_0;
    while (--arg_8 >= 0)
    {
        stk_C = arg_4->x;
        v8 = ((stk_C) * (arg_C->right.x));
        lv_14 = ((stk_C) * (arg_C->right.y));
        var_10 = ((stk_C) * (arg_C->right.z));
        stk_C = arg_4->y;
        v8 = ((v8) + (((stk_C) * (arg_C->up.x))));
        lv_14 = ((lv_14) + (((stk_C) * (arg_C->up.y))));
        var_10 = ((var_10) + (((stk_C) * (arg_C->up.z))));
        stk_C = arg_4->z;
        v8 = ((v8) + (((stk_C) * (arg_C->at.x))));
        lv_14 = ((lv_14) + (((stk_C) * (arg_C->at.y))));
        var_10 = ((var_10) + (((stk_C) * (arg_C->at.z))));
        arg_0->x = ((v8) + (arg_C->pos.x));
        arg_0->y = ((lv_14) + (arg_C->pos.y));
        arg_0->z = ((var_10) + (arg_C->pos.z));
        arg_4++;
        arg_0++;
    }
    return var_4;
}

// match: sub_141690 @ 0x00141690
// sp-match: sub_141690 @ 0x000ED7D0
// *arg_0 = the identity as a 4x4 matrix (its last pad 1) at the position
// *arg_4, when given.
void sub_141690(RwMatrix *arg_0, RwV3d *arg_4)
{
    type_8BFA0 *var_4;

    memset(arg_0, 0, sizeof(RwMatrix));
    var_4 = (type_8BFA0 *)arg_0;
    var_4->unk_00[0].unk_00 = 1.0f;
    var_4->unk_00[1].unk_04 = 1.0f;
    var_4->unk_00[2].unk_08 = 1.0f;
    var_4->unk_00[3].unk_0C = 1.0f;
    if (arg_4)
        arg_0->pos = *arg_4;
}

// match: sub_141700 @ 0x00141700
// sp-match: sub_141700 @ 0x000ED990
// Moves along a trapezoidal speed profile for the time arg_18: the speed
// *arg_0 (updated) is first brought into [0, arg_C] (decelerating at
// arg_14), then accelerates at arg_10 to arg_C (or less when the distance
// arg_4 is short), cruises, and decelerates to stop at arg_4. Returns the
// distance covered (signed like arg_4); *arg_1C gets the profile's total
// time. arg_8 is unused.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_141700(RwReal *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal arg_10, RwReal arg_14,
                  RwReal arg_18, RwReal *arg_1C)
{
    RwReal var_3C;
    RwReal v38;
    RwReal v34;
    RwReal v30;
    RwReal var_2C;
    RwReal loc28;
    RwReal slot_24;
    RwReal v20;
    RwReal slot_1C;
    RwReal local_18;
    RwReal local_14;
    RwReal local_10;
    RwInt32 fp_C;
    RwReal lv_8;
    RwReal var_4;

    local_18 = 0.0f;
    var_4 = 0.5f;
    loc28 = 0.0f;
    fp_C = 0;
    if (arg_10 == 0.0f && arg_14 == 0.0f)
        return arg_18 * *arg_0;
    if (arg_4 < 0.0f)
    {
        fp_C = 1;
        arg_4 = -arg_4;
        *arg_0 = -*arg_0;
    }
    v20 = *arg_0;
    v34 = var_3C = 0.0f;
    var_2C = v38 = 0.0f;
    if (v20 < 0.0f)
    {
        v34 = -v20 / arg_14;
        var_2C = v34 * v20 * var_4;
        v20 = 0.0f;
    }
    else if (v20 > arg_C)
    {
        var_3C = (v20 - arg_C) / arg_14;
        v38 = (arg_C + v20) * var_3C * var_4;
        v20 = arg_C;
    }
    arg_4 = arg_4 - var_2C - v38;
    v30 = (arg_C - v20) / arg_10;
    if (v30 < 0.0f)
        v30 = 0.0f;
    slot_1C = (arg_C + v20) * v30 * var_4;
    lv_8 = arg_C / arg_14;
    slot_24 = lv_8 * arg_C * var_4;
    if (slot_1C + slot_24 > arg_4)
    {
        lv_8 = v20 / arg_14;
        slot_24 = lv_8 * v20 * var_4;
        if (slot_24 >= arg_4)
        {
            local_14 = v20;
            local_10 = 0.0f;
            v30 = 0.0f;
        }
        else
        {
            local_14 = arg_4 * 4.0f * arg_10 * arg_14 + v20 * v20 * 2.0f * arg_14;
#ifdef CODFH_SP // shape: the doubled rates kept apart
            local_14 = local_14 / ((arg_14 + arg_14) + (arg_10 + arg_10));
#else
            local_14 = local_14 / (2.0f * arg_14 + 2.0f * arg_10);
#endif
            if (local_14 != 0.0f)
                local_14 = sqrt(local_14);
            else
                local_14 = 0.0f;
            local_10 = 0.0f;
            local_18 = 0.0f;
            v30 = (local_14 - v20) / arg_10;
            slot_1C = (local_14 + v20) * v30 * var_4;
            lv_8 = local_14 / arg_14;
            slot_24 = lv_8 * local_14 * var_4;
        }
    }
    else
    {
        arg_4 = arg_4 - (slot_1C + slot_24);
        local_14 = arg_C;
        local_18 = arg_4;
        if (local_14 != 0.0f)
            local_10 = local_18 / local_14;
        else
            local_10 = 0.0f;
    }
    if (arg_1C)
        *arg_1C = v34 + var_3C + v30 + local_10;
    if (v34 != 0.0f || var_3C != 0.0f)
    {
        if (v34 != 0.0f)
            loc28 += sub_141B10(arg_0, v20, v34, var_2C, &arg_18);
        else
            loc28 += sub_141B10(arg_0, v20, var_3C, v38, &arg_18);
    }
    if (arg_18 != 0.0f)
    {
        if (v30 != 0.0f)
            loc28 += sub_141B10(arg_0, local_14, v30, slot_1C, &arg_18);
        if (arg_18 != 0.0f)
        {
            if (local_10 != 0.0f)
                loc28 += sub_141B10(arg_0, local_14, local_10, local_18, &arg_18);
            if (arg_18 != 0.0f && lv_8 != 0.0f)
                loc28 += sub_141B10(arg_0, 0.0f, lv_8, slot_24, &arg_18);
        }
    }
    if (fp_C)
    {
        loc28 = -loc28;
        *arg_0 = -*arg_0;
    }
    return loc28;
}

// match: sub_141B10 @ 0x00141B10
// sp-match: sub_141B10 @ 0x000ED810
// One stage of sub_141700's profile: the speed *arg_0 moving linearly to
// arg_4 over arg_8 seconds covering arg_C, within the time left *arg_10
// (all of it when the stage is longer); returns the distance covered.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_141B10(RwReal *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C, RwReal *arg_10)
{
    RwReal var_4;
    RwReal v8;
    RwReal varC;

    var_4 = 0.5f;
    if (arg_8 < *arg_10)
    {
        if (arg_C == 0.0f)
            arg_C = (arg_4 + *arg_0) * var_4 * arg_8;
        *arg_0 = arg_4;
        *arg_10 -= arg_8;
        return arg_C;
    }
#ifdef CODFH_SP // shape: the product kept before the division
    varC = (arg_4 - *arg_0) * *arg_10;
    varC = varC / arg_8 + *arg_0;
#else
    varC = (arg_4 - *arg_0) * *arg_10 / arg_8 + *arg_0;
#endif
    v8 = (varC + *arg_0) * var_4 * *arg_10;
    *arg_10 = 0.0f;
    *arg_0 = varC;
    return v8;
}
