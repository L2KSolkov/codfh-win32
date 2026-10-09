// The entity handles (type_D48D0) and the entity functions after them. The
// original file name is not in the image, so it is named for its start
// address.

#include <math.h>
#include <string.h>

#include "rw/ostypes.h"
#include "types/type_D48D0.h"
#include "types/type_3D3548.h"
#include "types/type_D4C80.h"
#include "game/functions.h"
#include "rw/baframe.h"
#include "game/data.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D7104
extern const RwReal flt_3D7104 = 16.666666f;
// 0x00429254
RwReal flt_429254 = 1.0f;
// 0x00429258
RwReal flt_429258 = 0.175f;
// 0x0042925C
RwReal flt_42925C = 1.5f;
// 0x00429260
RwReal flt_429260 = 0.5f;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3D7104@@3MB @ 0x003D7104
// match: __real@3e4ccccc @ 0x003D7108
// match: __real@3f59999a @ 0x003D710C
// match: __real@3f4ccccc @ 0x003D7110
// match: __real@3f7fdf3b @ 0x003D7114
// match: ?flt_429254@@3MA @ 0x00429254
// match: ?flt_429258@@3MA @ 0x00429258
// match: ?flt_42925C@@3MA @ 0x0042925C
// match: ?flt_429260@@3MA @ 0x00429260

// match: ?sub_D48D0@type_D48D0@@QAEXPAUtype_3D3548@@@Z @ 0x000D48D0
// sp-match: ?sub_D48D0@type_D48D0@@QAEXPAUtype_3D3548@@@Z @ 0x000A0E50

void type_D48D0::sub_D48D0(type_3D3548 *arg_0)
{
    if (arg_0)
    {
        unk_00_h = arg_0->get_unk_384_h();
    }
    else
    {
        unk_00 = 0;
    }
}

// match: ?sub_D4910@type_D48D0@@QAEPAUtype_3D3548@@XZ @ 0x000D4910
// sp-match: ?sub_D4910@type_D48D0@@QAEPAUtype_3D3548@@XZ @ 0x000A0E70
type_3D3548 *type_D48D0::sub_D4910()
{
    type_3D3548 *var_4;

    var_4 = 0;
    if (dword_4B6A00[(RwInt16)unk_00].unk_00 == unk_00)
    {
        var_4 = dword_4B6A00[(RwInt16)unk_00].unk_04;
    }
    return var_4;
}

// match: ?sub_D4950@@YAXPAUtype_3D3548@@@Z @ 0x000D4950
// sp-match: ?sub_D4950@@YAXPAUtype_3D3548@@@Z @ 0x000A13A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D4950(type_3D3548 *arg_0)
{
    RwReal var_C;
    RwMatrix *bp_8;
    RwFrame *bp_4;

    if (!sub_D4A60(arg_0))
    {
        return;
    }
    if (!arg_0->unk_1B8)
    {
        bp_4 = arg_0->get_unk_340();
        bp_8 = RwFrameGetMatrix(bp_4);
        var_C = RAND_RANGE(0.75f, 0.95f);
        arg_0->unk_1B8 = sub_D4B70(bp_8, var_C, 0.01f, bp_8->pos.y);
    }
}

// match: ?sub_D49E0@@YAXPAUtype_3D3548@@@Z @ 0x000D49E0
// sp-match: ?sub_D49E0@@YAXPAUtype_3D3548@@@Z @ 0x000A1260
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_D49E0(type_3D3548 *arg_0)
{
    RwMatrix *var_8;
    RwFrame *l4;

    if (arg_0->unk_1B8)
    {
        l4 = arg_0->get_unk_340();
        var_8 = RwFrameGetMatrix(l4);
        if (!arg_0->unk_1B8->sub_D4D00(var_8, var_8))
        {
            operator delete(arg_0->unk_1B8);
            arg_0->unk_1B8 = 0;
        }
        RwFrameUpdateObjects(l4);
    }
}

// match: ?sub_D4A60@@YAHPAUtype_3D3548@@@Z @ 0x000D4A60
// sp-match: ?sub_D4A60@@YAHPAUtype_3D3548@@@Z @ 0x000A0E90
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwInt32 sub_D4A60(type_3D3548 *arg_0)
{
    RwMatrix *var_18;
    RwV3d var_14;
    RwReal var8;
    RwFrame *l4;

    if (!arg_0->unk_1BC)
    {
        return 0;
    }
    switch (arg_0->unk_2C & 0x3FFFFF0) // not an address: entity kind bits
    {
    case 0x200000: // not an address: entity kind bits
    case 0x20:
    case 0x80:
    case 0x40000: // not an address: entity kind bits
    case 0x800000: // not an address: entity kind bits
    case 0x1000000: // not an address: entity kind bits
    case 0x2000000: // not an address: entity kind bits
        return 0;
    }
    l4 = arg_0->get_unk_340();
    if (!l4)
    {
        return 0;
    }
    var_18 = RwFrameGetMatrix(l4);
    var_14.x = 0.0f;
    var_14.y = 1.0f;
    var_14.z = 0.0f;
    var8 = RwV3dDotProduct(&var_18->up, &var_14);
    if (fabsf(var8) < 0.85f)
    {
        return 0;
    }
    return 1;
}

// match: ?sub_D4B70@@YAPAUtype_D4C80@@PAURwMatrixTag@@MMM@Z @ 0x000D4B70
// sp-match: ?sub_D4B70@@YAPAUtype_D4C80@@PAURwMatrixTag@@MMM@Z @ 0x000A12B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_D4C80 *sub_D4B70(RwMatrix *arg_0, RwReal arg_4, RwReal arg_8, RwReal arg_C)
{
    RwV3d var_18;
    RwReal var_C;
    type_D4C80 *bp_8;
    RwReal bp_4;

    bp_4 = RAND_RANGE(0.6f, 1.4f);
    arg_4 *= bp_4;
    if (arg_4 < arg_8)
    {
        arg_4 = arg_8;
    }
    var_C = flt_429258 * arg_4 * 1.5f;
    var_18.x = RAND_RANGE(-var_C, var_C);
    var_18.y = RAND_RANGE(-var_C, var_C);
    var_18.z = RAND_RANGE(-var_C, var_C);
    bp_8 = sub_D4C80(arg_0, &var_18, arg_4, arg_C);
    return bp_8;
}

// match: ?sub_D4C80@@YAPAUtype_D4C80@@PAURwMatrixTag@@PAURwV3d@@MM@Z @ 0x000D4C80
// sp-match: ?sub_D4C80@@YAPAUtype_D4C80@@PAURwMatrixTag@@PAURwV3d@@MM@Z @ 0x000A0F10
type_D4C80 *sub_D4C80(RwMatrix *arg_0, RwV3d *arg_4, RwReal arg_8, RwReal arg_C)
{
    type_D4C80 *var_4;

    var_4 = (type_D4C80 *)RWSMalloc(0x60, 0x34250); // not an address: an allocation tag
    memset(var_4, 0, 0x60);
    var_4->unk_4C = *arg_4;
    var_4->unk_00 = *arg_0;
    var_4->unk_58 = arg_8 * 2.0f * 1.5f * 100.0f;
    var_4->unk_5C = arg_C;
    return var_4;
}

// match: ?sub_D4D00@type_D4C80@@QAEHPAURwMatrixTag@@0@Z @ 0x000D4D00
// sp-match: ?sub_D4D00@type_D4C80@@QAEHPAURwMatrixTag@@0@Z @ 0x000A0F70
// Falls under gravity (981 a second squared) and turns; on landing at its
// height it bounces with some of its speed, a new turning against its tilt
// (a random one when that is a NaN or over 5) and, once all but upright, is
// set upright and over (0).
RwInt32 type_D4C80::sub_D4D00(RwMatrix *arg_0, RwMatrix *arg_4)
{
#ifndef CODFH_SP
    RwReal var_8;
#endif
    RwV3d var_14;
    RwReal var_18;
    RwMatrix var_60;
    RwReal var_68;

#ifdef CODFH_SP
    // shape: the frames, then by a thousandth (SP 0xA0F70 multiplies by flt_3D7104 and 0.001);
    // the gravity is a literal (SP 0xA0F70 multiplies by 0x2E3504 = 981.00006, and folds 2/981 into
    // 0x2E3500 below) and the thousandth is stored as it is used (fst)
    { RwReal &r = var_18; r = deltaTime * flt_3D7104; }   // shape: through a reference (SP 0xA0F70)
    var_14 = arg_0->pos;
    unk_58 -= (var_18 = var_18 * 0.001f) * 981.00006f;
#else
    var_8 = 981.00006f;
    var_14 = arg_0->pos;
    var_18 = deltaTime * flt_3D7104 / 1000.0f;
    unk_58 -= var_8 * var_18;
#endif
    unk_40.x += var_18 * unk_4C.x;
    unk_40.y += var_18 * unk_4C.y;
    unk_40.z += var_18 * unk_4C.z;
    sub_141080(&var_60, &unk_40, 0);
    RwMatrixMultiply(arg_4, &var_60, &unk_00);
#ifdef CODFH_SP // through a reference (SP 0xA0F70: the damping stores)
    { RwReal &r = unk_4C.x; r = flt_429254 * unk_4C.x; }
#else
    unk_4C.x = flt_429254 * unk_4C.x;
#endif
    unk_4C.y = flt_429254 * unk_4C.y;
    unk_4C.z = flt_429254 * unk_4C.z;
    arg_4->pos.x = var_14.x;
    arg_4->pos.y = var_18 * unk_58 + var_14.y;
    arg_4->pos.z = var_14.z;
    if (arg_4->pos.y < unk_5C)
    {
        arg_4->pos.y = unk_5C;
        unk_58 = (RwReal)fabs((RwDouble)unk_58) * flt_429260;
#ifdef CODFH_SP
        var_68 = 2.0f * unk_58 / 981.00006f;
#else
        var_68 = 2.0f * unk_58 / var_8;
#endif
        if (var_68 == 0.0f)
        {
            var_68 = 0.1f;
        }
#ifdef CODFH_SP
        // shape: the limit on the left of each clamp (SP 0xA109D, 0xA10FF: fld 3.0; fcomp st(1))
        unk_4C.x = -unk_40.x * (3.0f > flt_42925C / var_68 ? flt_42925C / var_68 : 3.0f);
        unk_4C.y = RAND_RANGE(-flt_429258, flt_429258);
        unk_4C.z = -unk_40.z * (3.0f > flt_42925C / var_68 ? flt_42925C / var_68 : 3.0f);
#else
        unk_4C.x = -unk_40.x * (flt_42925C / var_68 < 3.0f ? flt_42925C / var_68 : 3.0f);
        unk_4C.y = RAND_RANGE(-flt_429258, flt_429258);
        unk_4C.z = -unk_40.z * (flt_42925C / var_68 < 3.0f ? flt_42925C / var_68 : 3.0f);
#endif
        if (*(RwInt32 *)&unk_4C.x == 0x7FFFFFFF || (RwReal)fabs((RwDouble)unk_4C.x) > 5.0f)
        {
            unk_4C.x = RAND_RANGE(0.0f, -unk_40.x * 0.5f);
        }
        if (*(RwInt32 *)&unk_4C.z == 0x7FFFFFFF || (RwReal)fabs((RwDouble)unk_4C.z) > 5.0f)
        {
            unk_4C.z = RAND_RANGE(0.0f, -unk_40.z * 0.5f);
        }
        if (arg_4->up.y > 0.9995f)
        {
            arg_4->up.x = 0.0f;
            arg_4->up.y = 1.0f;
            arg_4->up.z = 0.0f;
            RwV3dCrossProductMacro(&arg_4->right, &arg_4->up, &arg_4->at);
            RwV3dNormalize(&arg_4->right, &arg_4->right);
            RwV3dCrossProductMacro(&arg_4->at, &arg_4->right, &arg_4->up);
            RwV3dNormalize(&arg_4->at, &arg_4->at);
            return 0;
        }
    }
    return 1;
}
