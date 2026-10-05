// Split from unit_08AB60.cpp at 0x092620, where the image starts another object (the point/sphere tests; sub_92620 defines its two literals):
// its .rdata begins at 0x3D5188 with its own copy of the unreferenced 16.666666 every game object
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
// 0x003D5188
extern const RwReal flt_3D5188 = 16.666666f;

// match: ?flt_3D5188@@3MB @ 0x003D5188


// Whether the line from arg_0 along arg_4 crosses the triangle arg_8,
// arg_C, arg_10, and where along it (*arg_14): RenderWare's
// RtIntersectionLineTriangle.
// match: ?sub_92620@@YAHPAURwV3d@@0000PAM@Z @ 0x00092620
// match: __real@322bcc77 @ 0x003D518C
// match: __real@b22bcc77 @ 0x003D5190
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_92620(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwV3d *arg_C, RwV3d *arg_10, RwReal *arg_14)
{
    RwV3d var_54;
    RwReal var_48;
    RwV3d y44;
    RwV3d lv_38;
    RwV3d ebp_2C;
    RwReal var_20;
    RwReal l1C;
    RwReal m_18;
    RwV3d ebp_14;
    RwReal bp_8;
    RwReal bp_4;

    RwV3dSubMacro(&var_54, arg_C, arg_8);
    RwV3dSubMacro(&y44, arg_10, arg_8);
    RwV3dCrossProductMacro(&lv_38, arg_4, &y44);
    var_20 = RwV3dDotProductMacro(&var_54, &lv_38);
    if (var_20 > -1e-8f && var_20 < 1e-8f)
    {
        return 0;
    }
    m_18 = 1.0f / var_20;
    bp_4 = -1e-5f;
    var_48 = 1.00001f;
    RwV3dSubMacro(&ebp_14, arg_0, arg_8);
    l1C = RwV3dDotProductMacro(&ebp_14, &lv_38) * m_18;
    if (l1C < bp_4 || l1C > var_48)
    {
        return 0;
    }
    RwV3dCrossProductMacro(&ebp_2C, &ebp_14, &var_54);
    bp_8 = RwV3dDotProductMacro(&ebp_2C, arg_4) * m_18;
    if (bp_8 < bp_4 || l1C + bp_8 > var_48)
    {
        return 0;
    }
    *arg_14 = RwV3dDotProductMacro(&y44, &ebp_2C) * m_18;
    if (*arg_14 < bp_4 || *arg_14 > var_48)
    {
        return 0;
    }
    return 1;
}
// Whether arg_0 is within the upright cylinder at arg_4 of radius arg_8
// and half-height arg_C.
// match: ?sub_92860@@YAHPAURwV3d@@0MM@Z @ 0x00092860
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_92860(RwV3d *arg_0, RwV3d *arg_4, RwReal arg_8, RwReal arg_C)
{
    RwV3d var_14;
    RwReal var8;
    RwReal l4;

    RwV3dSubMacro(&var_14, arg_0, arg_4);
    l4 = var_14.y;
    var_14.y = 0.0f;
    var8 = RwV3dDotProductMacro(&var_14, &var_14);
    if (arg_8 * arg_8 > var8 && -arg_C < l4 && l4 < arg_C)
    {
        return 1;
    }
    return 0;
}
// Likewise within the cylinder at the matrix arg_4 (upright in its frame).
// match: ?sub_92900@@YAHPAURwV3d@@PAURwMatrixTag@@MM@Z @ 0x00092900
RwInt32 sub_92900(RwV3d *arg_0, RwMatrix *arg_4, RwReal arg_8, RwReal arg_C)
{
    RwMatrix var_40;
    RwV3d var_4C;
    RwReal var_50;
    RwReal var_54;

    RwMatrixInvert(&var_40, arg_4);
    sub_1414C0(&var_4C, arg_0, &var_40);
    var_50 = var_4C.y;
    var_4C.y = 0.0f;
    var_54 = RwV3dDotProductMacro(&var_4C, &var_4C);
    if (arg_8 * arg_8 > var_54 && -arg_C < var_50 && var_50 < arg_C)
    {
        return 1;
    }
    return 0;
}
