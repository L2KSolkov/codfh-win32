// Split from unit_08AB60.cpp at 0x08E670, where the image starts another object (type_8E670 first; the sector-volume callback sub_8F5C0 defines its strings):
// its .rdata begins at 0x3D5110 with its own copy of the unreferenced 16.666666 every game object
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

#ifdef CODFH_SP // static in single player (defined below)
static bool sub_8F770(type_8BEC0 *arg_0, type_8BEC0 *arg_4);
#endif
#ifdef CODFH_SP
// The query's point and its height limit are this file's own in single player:
// sub_92430 and sub_92540 schedule their loads across stores as for statics
// (SP 0x741D0, 0x73BD0).
static RwV3d dword_4B25A0;
static RwReal flt_4B25AC;
#endif

// Its data definitions (PLAN M5), in the image's address order.
// 0x003D5110
extern const RwReal flt_3D5110 = 16.666666f;
#ifdef CODFH_SP // SP only: a second unreferenced 16.666666f follows flt_3D5110 (SP 0x2E191C)
// SP 0x002E191C
extern const RwReal sp_flt_2E191C = 16.666666f;
#endif

// match: ?flt_3D5110@@3MB @ 0x003D5110


// Enters the zone arg_0: the first zone at full weight; a new one fades in
// from the old one's leftover weight while the old one fades out; going
// back to the zone just left swaps it in again.
// match: ?sub_8E670@type_8E670@@QAEXPAUtype_8F3E0@@@Z @ 0x0008E670
// match: ??_C@_0EI@GLJADIGI@?$CK?$CK?$CKSECTOR?5HAS?5TOO?5MANY?5VOLUMES?$CB?5@ @ 0x003D5118
// match: ??_C@_0CH@DPGMGIKO@?$CK?$CK?$CKCOULD?5NOT?5STORE?5LIGHT?5VOLUME?5@ @ 0x003D5160
// sp-match: ?sub_8E670@type_8E670@@QAEXPAUtype_8F3E0@@@Z @ 0x00070F60
void type_8E670::sub_8E670(type_8F3E0 *arg_0)
{
    RwReal var_4;

    if (arg_0)
    {
        if (!unk_00)
        {
            unk_00 = arg_0;
            unk_04 = 1.0f;
            unk_08 = 0;
            unk_0C = 0.0f;
        }
        else if (arg_0 != unk_00)
        {
            var_4 = unk_0C;
            unk_08 = unk_00;
            unk_0C = unk_04;
            unk_00 = arg_0;
            if (var_4 > 0.0f)
            {
                unk_04 = var_4;
            }
            else
            {
                unk_04 = 0.0f;
            }
        }
        else if (arg_0 == unk_08)
        {
            unk_00 = unk_08;
            unk_04 = unk_0C;
            unk_08 = 0;
            unk_0C = 0.0f;
        }
    }
}
extern const RwReal flt_3D5110;
// A frame of the fades (a tenth of the step each), the countdown at unk_1C,
// and dword_4B2560's time running down at 1000/60 a second.
// match: ?sub_8E750@type_8E670@@QAEXXZ @ 0x0008E750
// sp-match: ?sub_8E750@type_8E670@@QAEXXZ @ 0x00070FD0
void type_8E670::sub_8E750()
{
    if (unk_00 && unk_04 < 1.0f)
    {
        unk_04 += 0.1f * deltaTime;
        if (unk_04 > 1.0f)
        {
            unk_04 = 1.0f;
        }
    }
    if (unk_08)
    {
        unk_0C -= 0.1f * deltaTime;
        if (unk_0C <= 0.0f)
        {
            unk_0C = 0.0f;
            unk_08 = 0;
        }
    }
    if (unk_1C > 0.0f)
    {
        unk_1C -= 0.1f;
    }
    if (unk_20)
    {
#ifdef CODFH_SP
        // shape: the frames in a local, then by a thousandth (SP 0x71059 multiplies twice).
        RwReal frames = deltaTime * flt_3D5110;
        dword_4B2560.unk_00 -= frames * 0.001f;
#else
        dword_4B2560.unk_00 -= deltaTime * flt_3D5110 / 1000.0f;
#endif
        if (dword_4B2560.unk_00 <= 0.0f)
        {
            dword_4B2560.unk_00 = 0.0f;
            unk_20 = 0;
        }
    }
}
// match: ?sub_8E870@type_8E670@@QAEXPAUtype_8F210@@@Z @ 0x0008E870
// sp-match: ?sub_8E870@type_8E670@@QAEXPAUtype_8F210@@@Z @ 0x000720E0
// Fills the light list arg_0 from the zones: entry 0 the ambient (each
// zone's unk_30 by its weight, plus the flash at unk_10 by the countdown
// unk_1C, clamped to 1), then each zone's two lights (a point at unk_40 or
// unk_60, not all zero, and its value by the zone's weight). The count
// excludes the ambient; the shared effect (sub_8F210) is added while it
// runs, then the list goes to sub_19B270.
void type_8E670::sub_8E870(type_8F210 *arg_0)
{
    RwInt32 var_8;
    __declspec(align(16)) type_8BEC0 var_40;
    RwInt32 var_44;
    __declspec(align(16)) type_8BEC0 var_C0[5];
    RwInt32 var_1E4;

    var_8 = 1;
    arg_0->unk_00 = unk_00 || unk_08 ? 1 : 0;
    if (!arg_0->unk_00)
    {
        return;
    }
    var_40 = sub_8BBE0(0.0f, 0.0f, 0.0f, 0.0f);
    for (var_44 = 0; var_44 < 5; var_44++)
    {
        var_C0[var_44] = sub_8BBE0(0.0f, 0.0f, 0.0f, 0.0f);
    }
    if (unk_00)
    {
        var_C0[0] = sub_8B9C0(&unk_00->unk_30, &unk_04);
    }
    if (unk_1C > 0.0f)
    {
        var_40 = sub_8B9C0((type_8BEC0 *)&unk_10, &unk_1C);
        var_40.unk_0C = 0.0f;
        var_C0[0] = sub_8BB10(&var_C0[0], &var_40);
        if (var_C0[0].unk_00 > 1.0f)
        {
            var_C0[0].unk_00 = 1.0f;
        }
        if (var_C0[0].unk_04 > 1.0f)
        {
            var_C0[0].unk_04 = 1.0f;
        }
        if (var_C0[0].unk_08 > 1.0f)
        {
            var_C0[0].unk_08 = 1.0f;
        }
        if (var_C0[0].unk_0C > 1.0f)
        {
            var_C0[0].unk_0C = 1.0f;
        }
    }
    if (unk_08)
    {
        var_40 = sub_8B9C0(&unk_08->unk_30, &unk_0C);
        var_C0[0] = sub_8BB10(&var_C0[0], &var_40);
        if (var_C0[0].unk_00 > 1.0f)
        {
            var_C0[0].unk_00 = 1.0f;
        }
        if (var_C0[0].unk_04 > 1.0f)
        {
            var_C0[0].unk_04 = 1.0f;
        }
        if (var_C0[0].unk_08 > 1.0f)
        {
            var_C0[0].unk_08 = 1.0f;
        }
        if (var_C0[0].unk_0C > 1.0f)
        {
            var_C0[0].unk_0C = 1.0f;
        }
    }
    if (unk_00 && (unk_00->unk_40.unk_00 != 0.0f || unk_00->unk_40.unk_04 != 0.0f || unk_00->unk_40.unk_08 != 0.0f))
    {
        var_C0[var_8] = sub_8B9C0(&unk_00->unk_50, &unk_04);
        arg_0->unk_10[var_8].unk_00 = unk_00->unk_40;
        var_8++;
    }
    if (unk_08 && (unk_08->unk_40.unk_00 != 0.0f || unk_08->unk_40.unk_04 != 0.0f || unk_08->unk_40.unk_08 != 0.0f))
    {
        var_C0[var_8] = sub_8B9C0(&unk_08->unk_50, &unk_0C);
        arg_0->unk_10[var_8].unk_00 = unk_08->unk_40;
        var_8++;
    }
    if (unk_00 && (unk_00->unk_60.unk_00 != 0.0f || unk_00->unk_60.unk_04 != 0.0f || unk_00->unk_60.unk_08 != 0.0f))
    {
        var_C0[var_8] = sub_8B9C0(&unk_00->unk_70, &unk_04);
        arg_0->unk_10[var_8].unk_00 = unk_00->unk_60;
        var_8++;
    }
    if (unk_08 && (unk_08->unk_60.unk_00 != 0.0f || unk_08->unk_60.unk_04 != 0.0f || unk_08->unk_60.unk_08 != 0.0f))
    {
        var_C0[var_8] = sub_8B9C0(&unk_08->unk_70, &unk_0C);
        arg_0->unk_10[var_8].unk_00 = unk_08->unk_60;
        var_8++;
    }
    arg_0->unk_00 = var_8 - 1;
    for (var_1E4 = 0; var_1E4 < var_8; var_1E4++)
    {
        arg_0->unk_10[var_1E4].unk_10 = var_C0[var_1E4];
    }
    if (unk_20)
    {
        sub_8F210(arg_0);
    }
    sub_19B270(arg_0);
}
// Starts the zones' effect with arg_0 (1 or 2) points for arg_4 seconds;
// the points and values given replace the old ones.
// match: ?sub_8F140@type_8E670@@QAEXHMPAURwV3d@@PAUtype_8BEC0@@01@Z @ 0x0008F140
// sp-match: ?sub_8F140@type_8E670@@QAEXHMPAURwV3d@@PAUtype_8BEC0@@01@Z @ 0x000710A0
void type_8E670::sub_8F140(RwInt32 arg_0, RwReal arg_4, RwV3d *arg_8, type_8BEC0 *arg_C,
                           RwV3d *arg_10, type_8BEC0 *arg_14)
{
    type_4B2560 *var_4;

    if (arg_0 < 1 || arg_0 > 2)
    {
        return;
    }
    unk_20 = 1;
    var_4 = &dword_4B2560;
    var_4->unk_04 = arg_0;
    var_4->unk_00 = arg_4;
    if (arg_8)
    {
        var_4->unk_08[0] = *arg_8;
    }
    if (arg_C)
    {
        var_4->unk_20[0] = *arg_C;
    }
    if (arg_10)
    {
        var_4->unk_08[1] = *arg_10;
    }
    if (arg_14)
    {
        var_4->unk_20[1] = *arg_14;
    }
}
// Hands out the zones' effect.
// match: ?sub_8F210@type_8E670@@QAEXPAUtype_8F210@@@Z @ 0x0008F210
// sp-match: ?sub_8F210@type_8E670@@QAEXPAUtype_8F210@@@Z @ 0x00071170
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_8E670::sub_8F210(type_8F210 *arg_0)
{
    RwInt32 var_8;
    type_4B2560 *l4;

    l4 = &dword_4B2560;
    if (!l4->unk_04)
    {
        return;
    }
    arg_0->unk_00 = l4->unk_04;
    for (var_8 = 0; var_8 < l4->unk_04; var_8++)
    {
        arg_0->unk_10[var_8].unk_10 = l4->unk_20[var_8];
        arg_0->unk_10[var_8].unk_00.unk_00 = l4->unk_08[var_8].x;
        arg_0->unk_10[var_8].unk_00.unk_04 = l4->unk_08[var_8].y;
        arg_0->unk_10[var_8].unk_00.unk_08 = l4->unk_08[var_8].z;
        arg_0->unk_10[var_8].unk_00.unk_0C = 0.0f;
    }
}
// match: ??0type_8F300@@QAE@XZ @ 0x0008F300
// sp-match: ??0type_8F300@@QAE@XZ @ 0x000711F0
type_8F300::type_8F300()
{
    unk_04 = 0;
    unk_08 = 0;
}
// Reads the table from arg_0: the header, the offsets and the data.
// match: ?sub_8F330@type_8F300@@QAEXPAURwStream@@@Z @ 0x0008F330
// sp-match: ?sub_8F330@type_8F300@@QAEXPAURwStream@@@Z @ 0x00071200
void type_8F300::sub_8F330(RwStream *arg_0)
{
    RwStreamRead(arg_0, this, 4);
    unk_04 = (RwUInt32 *)RwMalloc(unk_00 >> 22, 0x34250);  // not an address: a memory hint
    RwStreamRead(arg_0, unk_04, unk_00 >> 22);
    unk_08 = (RwUInt8 *)RwMalloc(unk_00 & 0xFFFFFF, 0x3425B);  // not an address: a memory hint
    RwStreamRead(arg_0, unk_08, unk_00 & 0xFFFFFF);
    unk_00 = unk_00 >> 24;
}
// match: ?sub_8F3E0@type_8F300@@QAE_NPAUtype_8F3E0@@PAUtype_8BEC0@@@Z @ 0x0008F3E0
// sp-match: ?sub_8F3E0@type_8F300@@QAE_NPAUtype_8F3E0@@PAUtype_8BEC0@@@Z @ 0x00071270
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
bool type_8F300::sub_8F3E0(type_8F3E0 *arg_0, type_8BEC0 *arg_4)
{
    RwReal l1C;
    type_8BEC0 var_2C;
    RwUInt32 m_18;
    RwReal *ebp_14;
    RwReal *lv_10;
    RwUInt32 var_C;
    RwReal *bp_8;
    RwReal *bp_4;

    if (!sub_8D5A0(arg_4, arg_0->unk_00))
    {
        var_C = (arg_0->unk_8C >> 16) & 0xFF;
        ebp_14 = arg_0->unk_90;
        bp_8 = arg_0->unk_A0;
        lv_10 = arg_0->unk_B0;
        bp_4 = arg_0->unk_C0;
        for (m_18 = 0; m_18 < var_C; m_18++)
        {
            if (m_18 && !(m_18 & 3))
            {
                ebp_14 += 12;
                bp_8 += 12;
                lv_10 += 12;
                bp_4 += 12;
            }
            var_2C.unk_00 = *ebp_14++;
            var_2C.unk_04 = *bp_8++;
            var_2C.unk_08 = *lv_10++;
            var_2C.unk_0C = *bp_4++;
            if (var_2C.unk_00 == 0.0f && var_2C.unk_04 == 0.0f && var_2C.unk_08 == 0.0f && var_2C.unk_0C == -1.0f)
            {
                break;
            }
            l1C = RwV3dDotProductMacro((RwV3d *)&var_2C, (RwV3d *)arg_4);
            l1C = l1C + var_2C.unk_0C;
            if (l1C > 0.0f)
            {
                return false;
            }
        }
        return true;
    }
    return false;
}
// match: ?sub_8F570@type_8F300@@QAEXPAURpWorld@@@Z @ 0x0008F570
// sp-match: ?sub_8F570@type_8F300@@QAEXPAURpWorld@@@Z @ 0x000714D0
void type_8F300::sub_8F570(RpWorld *arg_0)
{
    RwInt32 var_4;

    if (arg_0)
    {
        for (var_4 = 0; var_4 < unk_00; var_4++)
        {
            RpWorldForAllWorldSectors(arg_0, sub_8F5C0, &var_4);
        }
    }
}
// match: ?sub_8F5C0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x0008F5C0
// sp-match: ?sub_8F5C0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x00071390
// Adds the zone *arg_4 to the list of the world sector arg_0 (type_8F8C0)
// when the sector's box overlaps the zone's; at most 24 zones a sector.
RpWorldSector *sub_8F5C0(RpWorldSector *arg_0, void *arg_4)
{
    RwInt32 var_4;
    type_8F3E0 *var_8;
    __declspec(align(16)) type_8BEC0 var_50[2];
    RwInt32 var_74;

    var_4 = *(RwInt32 *)arg_4;
    var_8 = dword_4B2550.get_zone(var_4);
    var_50[0] = sub_8BB80(&((type_8F8C0 *)arg_0)->unk_48.inf);
    var_50[1] = sub_8BB80(&((type_8F8C0 *)arg_0)->unk_48.sup);
    if (!sub_8F770((type_8BEC0 *)var_8, var_50))
    {
        return arg_0;
    }
    if (((type_8F8C0 *)arg_0)->unk_10 && (((type_8F8C0 *)arg_0)->unk_10 & 0xFFFFFF00) != 0xFFFFFF00)
    {
#ifndef CODFH_SP
        // Single player compiles the debug prints out (SP 0x71390).
        sub_19A750("***COULD NOT STORE LIGHT VOLUME INFO!\n");
#endif
        return arg_0;
    }
    if (!(var_74 = ((type_8F8C0 *)arg_0)->unk_10 & 0xFF))
    {
        ((type_8F8C0 *)arg_0)->unk_10 = 0xFFFFFF00;
    }
    if (var_74 < 0x18)
    {
        RwInt32 var_78;
        RwUInt32 *var_7C;

        var_78 = (var_74 & 3) * 8;
        var_7C = &((type_8F8C0 *)arg_0)->unk_14[var_74 >> 2];
        *var_7C |= var_4 << var_78;
        var_7C = &((type_8F8C0 *)arg_0)->unk_10;
        *var_7C = ++var_74 | 0xFFFFFF00;
    }
#ifndef CODFH_SP
    else
    {
        sub_19A750("***SECTOR HAS TOO MANY VOLUMES! Volume number %i is a potential issue \n", var_4);
    }
#endif
    return arg_0;
}
// match: ?sub_8F770@@YA_NPAUtype_8BEC0@@0@Z @ 0x0008F770
// sp-match: ?sub_8F770@@YA_NPAUtype_8BEC0@@0@Z @ 0x000708F0
#ifdef CODFH_SP
// shape: internal linkage in single player, which passes the boxes in registers
// (SP 0x708F0: edx, ecx).
static
#endif
bool sub_8F770(type_8BEC0 *arg_0, type_8BEC0 *arg_4)
{
    if (((arg_0[0].unk_00 <= arg_4[1].unk_00 && arg_0[0].unk_00 >= arg_4[0].unk_00) ||
         (arg_4[0].unk_00 <= arg_0[1].unk_00 && arg_4[0].unk_00 >= arg_0[0].unk_00)) &&
        ((arg_0[0].unk_08 <= arg_4[1].unk_08 && arg_0[0].unk_08 >= arg_4[0].unk_08) ||
         (arg_4[0].unk_08 <= arg_0[1].unk_08 && arg_4[0].unk_08 >= arg_0[0].unk_08)) &&
        ((arg_0[0].unk_04 <= arg_4[1].unk_04 && arg_0[0].unk_04 >= arg_4[0].unk_04) ||
         (arg_4[0].unk_04 <= arg_0[1].unk_04 && arg_4[0].unk_04 >= arg_0[0].unk_04)))
    {
        return true;
    }
    return false;
}
// match: ?sub_8F870@type_8F300@@QAEXPAURpWorld@@@Z @ 0x0008F870
// sp-match: ?sub_8F870@type_8F300@@QAEXPAURpWorld@@@Z @ 0x00071520
void type_8F300::sub_8F870(RpWorld *arg_0)
{
    RwInt32 var_4;

    if (arg_0)
    {
        for (var_4 = 0; var_4 < unk_00; var_4++)
        {
            RpWorldForAllWorldSectors(arg_0, sub_8F8C0, 0);
        }
    }
}
// match: ?sub_8F8C0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x0008F8C0
// sp-match: ?sub_8F8C0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x00071480
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpWorldSector *sub_8F8C0(RpWorldSector *arg_0, void *arg_4)
{
    RwInt32 var_8;
    RwInt32 l4;

    if (((type_8F8C0 *)arg_0)->unk_10 &&
        (((type_8F8C0 *)arg_0)->unk_10 & 0xFFFFFF00) != 0xFFFFFF00)
    {
        return arg_0;
    }
    l4 = ((type_8F8C0 *)arg_0)->unk_10 & 0xF;
    for (var_8 = 0; var_8 < l4; var_8++)
    {
        ((type_8F8C0 *)arg_0)->unk_14[var_8 >> 2] = 0;
    }
    ((type_8F8C0 *)arg_0)->unk_10 = 0;
    return arg_0;
}
// match: ?sub_8F940@@YAHXZ @ 0x0008F940
// sp-match: ?sub_8F940@@YAHXZ @ 0x00072680
RwInt32 sub_8F940()
{
    return ++dword_4B25B0;
}

// The edge from A to B of the triangle projected on its U and V axes (W
// the third): when the projected point (fp_2c) lies outside it, the edge's
// point nearest the query point (t20) becomes the result (*arg_8, its
// squared distance in local_c) if it is the nearest yet; bp_4 records that
// some edge was outside. The macro locals' names give the image's slots
// (docs/toolchain.md); the operand order needs the two comma expressions.
// The sign test reads both bit patterns as volatile: single player reloads
// orient's slot at every edge and loads cross into a register before the xor
// (SP 0x7279C, 0x72946), which also gives its 0x38-byte frame.
// The edge traversal below uses these expressions in both builds.
#define NEAREST_DOT(A)                                                                       \
    RwV3dDotProduct((A), &edge)
#define NEAREST_SQUARED(out)                                                                 \
    out = RwV3dDotProduct(&edge, &edge)
#define NEAREST_ORIENT(U, V)                                                                 \
    ((0, arg_0[1]->U) - arg_0[0]->U) * ((0, arg_0[2]->V) - arg_0[0]->V)                      \
    - ((0, arg_0[1]->V) - arg_0[0]->V) * ((0, arg_0[2]->U) - arg_0[0]->U)
#ifdef CODFH_SP // shape: x87 operand lifetimes in sub_8F960 (SP 0x72690).
// These reads retain the target's operand order; preserve the vector macro's parentheses.
#define NEAREST_DOT_Y(A)                                                                     \
    ((((( ((((A))->x) * ((&edge)->x))) +                                                     \
        ( ((((A))->y) * ((*(volatile RwReal *)&((&edge)->y))))))) +                          \
        ( ((((A))->z) * ((&edge)->z)))))
#define NEAREST_DOT_X(A)                                                                     \
    ((((( ((((A))->x) * ((*(volatile RwReal *)&((&edge)->x))))) +                            \
        ( ((((A))->y) * ((&edge)->y))))) +                                                   \
        ( ((((A))->z) * ((&edge)->z)))))
#define NEAREST_SQUARED_Z(out)                                                               \
    out = ((((( (((&edge)->x) * ((&edge)->x))) +                                             \
        ( (((&edge)->y) * ((&edge)->y))))) +                                                 \
        ( (((*(volatile RwReal *)&((&edge)->z))) * ((&edge)->z)))))
#define NEAREST_SQUARED_YXZ(out)                                                             \
    out = edge.y * edge.y;                                                                   \
    out += edge.x * edge.x;                                                                  \
    out += edge.z * edge.z
#define NEAREST_ORIENT_XY(U, V)                                                              \
    ((0, arg_0[1]->U) - arg_0[0]->U) * ((0, arg_0[2]->V) - arg_0[0]->V)                      \
    - ((0, (*(volatile RwReal *)&(arg_0[1]->V))) - arg_0[0]->V) * ((0, arg_0[2]->U) - arg_0[0]->U)
#else // MP 0x8F960: the original vector macro expressions.
#define NEAREST_DOT_Y NEAREST_DOT
#define NEAREST_DOT_X NEAREST_DOT
#define NEAREST_SQUARED_Z NEAREST_SQUARED
#define NEAREST_SQUARED_YXZ NEAREST_SQUARED
#define NEAREST_ORIENT_XY NEAREST_ORIENT
#endif

#define NEAREST_EDGE(A, B, U, V, W, DOT, LENGTH, DISTANCE)                                   \
    do {                                                                                     \
        RwV3d edge;                                                                          \
                                                                                             \
        edge.U = (B)->U - (A)->U;                                                            \
        edge.V = (B)->V - (A)->V;                                                            \
        do {                                                                                 \
            RwReal cross;                                                                    \
            RwInt32 crossed;                                                                 \
            RwReal along;                                                                    \
            RwV3d nearest;                                                                   \
            RwReal l2;                                                                       \
                                                                                             \
            cross = (fp_2c.V - (0, (A)->V)) * edge.U - (fp_2c.U - (0, (A)->U)) * edge.V;     \
            crossed = (*(volatile RwInt32 *)&cross ^ *(volatile RwInt32 *)&orient) < 0;      \
            if (crossed) {                                                                   \
                edge.W = (B)->W - (A)->W;                                                    \
                along = RwV3dDotProduct(&fp_2c, &edge) - DOT(A);                             \
                if (along <= 0.0f)                                                           \
                    nearest = *(A);                                                          \
                else {                                                                       \
                    LENGTH(l2);                                                              \
                    inside = 0.0f < l2 && along < l2;                                        \
                    if (inside) {                                                            \
                        along /= l2;                                                         \
                        RwV3dScale(&nearest, &edge, along);                                  \
                        RwV3dAdd(&nearest, (A), &nearest);                                   \
                    } else                                                                   \
                        nearest = *(B);                                                      \
                }                                                                            \
                RwV3dSub(&edge, &t20, &nearest);                                             \
                DISTANCE(o30);                                                               \
                if (!bp_4 || local_c > o30) {                                                \
                    *arg_8 = nearest;                                                        \
                    local_c = o30;                                                           \
                }                                                                            \
            }                                                                                \
            bp_4 |= crossed;                                                                 \
        } while (0);                                                                         \
    } while (0)

// The triangle projected on its U and V axes: its three edges in turn until
// the projected point falls within one's span.
#define NEAREST_CASE(U, V, W, ORIENT, FIRST_DOT, SECOND_DOT,                                 \
                     SECOND_LENGTH, SECOND_DISTANCE)                                         \
    do {                                                                                     \
        RwInt32 inside;                                                                      \
        RwReal orient;                                                                       \
                                                                                             \
        inside = 0;                                                                          \
        orient = ORIENT(U, V);                                                               \
        NEAREST_EDGE(arg_0[1], arg_0[2], U, V, W, FIRST_DOT,                                 \
                     NEAREST_SQUARED, NEAREST_SQUARED);                                      \
        if (!inside) {                                                                       \
            NEAREST_EDGE(arg_0[2], arg_0[0], U, V, W, SECOND_DOT,                            \
                     SECOND_LENGTH, SECOND_DISTANCE);                                        \
            if (!inside)                                                                     \
                NEAREST_EDGE(arg_0[0], arg_0[1], U, V, W, NEAREST_DOT,                       \
                             NEAREST_SQUARED, NEAREST_SQUARED);                              \
        }                                                                                    \
    } while (0)

// match: ?sub_8F960@@YAMPAPAURwV3d@@PAU1@1@Z @ 0x0008F960
// sp-match: ?sub_8F960@@YAMPAPAURwV3d@@PAU1@1@Z @ 0x00072690
// The point of the triangle arg_0 (normal arg_4) nearest *arg_8, into
// *arg_8; returns its squared distance. The point projects onto the plane;
// if that falls outside an edge (in the projection on the normal's two
// smaller axes), the nearest point of the edges outside wins. Local names
// state their slots.
RwReal sub_8F960(RwV3d **arg_0, RwV3d *arg_4, RwV3d *arg_8)
{
    RwInt32 l34;
    RwReal o30;
    RwV3d fp_2c;
    RwV3d t20;
    RwReal ebp_14;
    RwInt32 lv_10;
    RwReal local_c;
    RwInt32 bp_8;
    RwInt32 bp_4;

    local_c = 0.0f;
    bp_4 = 0;
    l34 = *(RwInt32 *)&arg_4->x & 0x7FFFFFFF;
    bp_8 = *(RwInt32 *)&arg_4->y & 0x7FFFFFFF;
    lv_10 = *(RwInt32 *)&arg_4->z & 0x7FFFFFFF;
#ifdef CODFH_SP // shape: source views and product reads in SP 0x72690.
    {
        RwV3d const &v = *arg_8;
        t20 = v;
    }
    {
        RwV3d * const &q = arg_0[0];
        ebp_14 = RwV3dDotProduct(q, arg_4) -
            ((((( (((arg_8)->x) * ((arg_4)->x))) +
                ( (((arg_8)->y) * ((*(volatile RwReal *)&((arg_4)->y))))))) +
                ( (((*(volatile RwReal *)&((arg_8)->z))) * ((arg_4)->z)))));
    }
#else // MP 0x8F960.
    t20 = *arg_8;
    ebp_14 = RwV3dDotProduct(arg_0[0], arg_4) - RwV3dDotProduct(arg_8, arg_4);
#endif
    RwV3dScale(&fp_2c, arg_4, ebp_14);
    RwV3dAdd(&fp_2c, &fp_2c, arg_8);
    if (lv_10 > bp_8) {
        if (lv_10 > l34)
            NEAREST_CASE(x, y, z, NEAREST_ORIENT_XY,
                         NEAREST_DOT, NEAREST_DOT, NEAREST_SQUARED_Z, NEAREST_SQUARED);
        else
            NEAREST_CASE(y, z, x, NEAREST_ORIENT,
                         NEAREST_DOT, NEAREST_DOT, NEAREST_SQUARED, NEAREST_SQUARED);
    } else {
        if (bp_8 > l34)
            NEAREST_CASE(z, x, y, NEAREST_ORIENT,
                         NEAREST_DOT_Y, NEAREST_DOT_X, NEAREST_SQUARED_YXZ, NEAREST_SQUARED_YXZ);
        else
            NEAREST_CASE(y, z, x, NEAREST_ORIENT,
                         NEAREST_DOT, NEAREST_DOT, NEAREST_SQUARED, NEAREST_SQUARED);
    }
    if (!bp_4) {
        *arg_8 = fp_2c;
        o30 = ebp_14 * ebp_14;
        local_c = o30;
    }
    return local_c;
}

#undef NEAREST_CASE
#undef NEAREST_EDGE
#undef NEAREST_DOT
#undef NEAREST_SQUARED
#undef NEAREST_ORIENT
#undef NEAREST_DOT_Y
#undef NEAREST_DOT_X
#undef NEAREST_SQUARED_Z
#undef NEAREST_SQUARED_YXZ
#undef NEAREST_ORIENT_XY
// match: ?sub_91F40@@YAHPAURpWorld@@PAURwLine@@PAUtype_91F40@@HHH@Z @ 0x00091F40
// sp-match: ?sub_91F40@@YAHPAURpWorld@@PAURwLine@@PAUtype_91F40@@HHH@Z @ 0x00073EA0
// The line arg_4 through the world arg_0 (timed as section 0x21): each world
// sector along it, each run of its collision tree's triangles along it, each
// triangle the line crosses (sub_92620) whose surface passes the filter
// (arg_10's bits against the surface's high word: arg_14 0 rejects all of
// them set, 1 any, 2 none) and is the nearest yet; with arg_C clear the
// first such hit ends the search, else the iterators clip to it. Whether it
// hit; arg_8 (when given) takes the hit: its triangle, distance, point,
// normal (sub_16E740), vertices, surface and sector. Local names state
// their slots.
RwInt32 sub_91F40(RpWorld *arg_0, RwLine *arg_4, type_91F40 *arg_8, RwInt32 arg_C, RwInt32 arg_10,
                  RwInt32 arg_14)
{
    RpMaterial *v578;
    type_FC000 *v574;
    RwInt32 v570;
    RwUInt32 p56c;
    RwV3d *loc568;
    RpTriangle *w564;
    RwReal lv_560;
    RwV3d *local_55c;
    RwV3d *fp_558;
    RwUInt16 frm_554;
    RwUInt16 lv_550;
    RwUInt16 t54c;
    RwUInt16 bp_548;
    RpCollTree *lv_544;
    RpTriangle *var540;
    RwUInt16 *t53c;
    RpCollSectorLineIt r538;
    RwV3d *stk_374;
    RpWorldSector *var370;
    RwV3d *var36c;
    RwV3d *l368;
    RpWorldSector *l364;
    RwReal l360;
    RwV3d *frm_35c;
    RpTriangle *v358;
    RwInt32 v354;
    RpSectorLineIt v350;
    RwInt32 ebp_14;
    RwV3d *lv_10;
    RwV3d local_c;

    l360 = 3.402823466e+38f;
    v358 = 0;
    l364 = 0;
    v354 = 0;
    ebp_14 = 0xFFFF;
    lv_10 = 0;
    frm_35c = 0;
    var36c = 0;
    l368 = 0;
    sub_16D7F0(0x21);
    RpSectorLineItInit(&v350, arg_0, arg_4);
    while (!RpSectorLineItFinished(&v350)) {
        var370 = RpSectorLineItFindNextWorldSector(&v350);
        var540 = var370->triangles;
        stk_374 = var370->vertices;
        lv_544 = RpCollisionWorldSectorGetCollTree(var370);
        if (var540 == 0 || stk_374 == 0 || lv_544 == 0)
            continue;
        t53c = RpCollTreeGetEntryMap(lv_544);
        RwV3dSub(&local_c, &arg_4->end, &arg_4->start);
        RpCollSectorLineItInit(&r538, lv_544, arg_4);
        while (!RpCollSectorLineItFinished(&r538)) {
            RpCollSectorLineItFindNextEntries(&r538, &lv_550, &bp_548);
            for (t54c = lv_550; t54c < lv_550 + bp_548; t54c++) {
                frm_554 = t53c[t54c];
                w564 = &var540[frm_554];
#ifdef CODFH_SP // single player passes the vertices straight to the test: the
                // nearest hit's vertices (frm_35c, var36c, l368) are not kept (SP 0x73FDC)
                if (sub_92620(&arg_4->start, &local_c, &stk_374[w564->vertIndex[0]],
                              &stk_374[w564->vertIndex[1]], &stk_374[w564->vertIndex[2]], &lv_560)) {
#else
                loc568 = &stk_374[w564->vertIndex[0]];
                fp_558 = &stk_374[w564->vertIndex[1]];
                local_55c = &stk_374[w564->vertIndex[2]];
                if (sub_92620(&arg_4->start, &local_c, loc568, fp_558, local_55c, &lv_560)) {
#endif
                    v578 = arg_0->materials[w564->matIndex];
                    v574 = sub_FC000(v578);
                    p56c = v574->unk_04 & 0xFFFF0000;
                    v570 = 1;
                    if (p56c != 0xFFFF0000 && arg_10 != 0 && p56c != 0) {
                        switch (arg_14) {
                        case 0:
                            if ((arg_10 & p56c) == arg_10)
                                v570 = 0;
                            break;
                        case 1:
                            if (arg_10 & p56c)
                                v570 = 0;
                            break;
                        case 2:
                            if (!(arg_10 & p56c))
                                v570 = 0;
                            break;
                        }
                    }
                    if (v570 && lv_560 < l360) {
                        ebp_14 = v574->unk_04;
                        l360 = lv_560;
                        v358 = w564;
                        l364 = var370;
                        lv_10 = stk_374;
#ifndef CODFH_SP
                        frm_35c = loc568;
                        var36c = fp_558;
                        l368 = local_55c;
#endif
                        v354 = 1;
                        if (!arg_C)
                            break;
                        RpCollSectorLineItSetFarClip(&r538, lv_560);
                    }
                }
            }
        }
        if (v354 && !arg_C)
            break;
        if (v354)
            RpSectorLineItSetFarClip(&v350, l360);
    }
    if (arg_8 != 0)
        arg_8->unk_00 = 0;
    if (arg_8 != 0 && v354) {
        arg_8->unk_24 = ebp_14;
        arg_8->unk_00 = (RwInt32)v358;
        arg_8->unk_04 = l360;
        arg_8->unk_20 = lv_10;
        arg_8->unk_28 = l364;
        arg_8->unk_08.x = local_c.x * arg_8->unk_04 + arg_4->start.x;
        arg_8->unk_08.y = local_c.y * arg_8->unk_04 + arg_4->start.y;
        arg_8->unk_08.z = local_c.z * arg_8->unk_04 + arg_4->start.z;
        sub_16E740(v358, lv_10, &arg_8->unk_14);
    }
    sub_16D850(0x21);
    return v354;
}
// match: ?sub_92430@@YAMPAURwV3d@@PAUtype_92430@@M@Z @ 0x00092430
// sp-match: ?sub_92430@@YAMPAURwV3d@@PAUtype_92430@@M@Z @ 0x000741D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RwReal sub_92430(RwV3d *arg_0, type_92430 *arg_4, RwReal arg_8)
{
    type_4E5D30 *var_24;
    RwInt32 var_20;
    RpIntersection l1C;

    l1C.type = rpINTERSECTLINE;
    l1C.t.line.start = *arg_0;
    l1C.t.line.end = *arg_0;
    l1C.t.line.start.y += 60.0f;
    l1C.t.line.end.y -= 1000.0f;
    arg_4->unk_00 = 0;
    arg_4->unk_04 = -100000.0f;
    arg_4->unk_20 = 0;
    flt_4B25AC = arg_8;
    dword_4B25A0 = *arg_0;
    for (var_20 = 0; var_20 < 4; var_20++)
    {
        var_24 = &dword_4E5D30[var_20];
        if (var_24->get_unk_00() && var_24->get_unk_28())
        {
            RpCollisionWorldForAllIntersections(var_24->get_unk_28(), &l1C, sub_92540, arg_4);
        }
    }
    return arg_4->unk_04;
}
// match: ?sub_92540@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00092540
// sp-match: ?sub_92540@@YAPAURpCollisionTriangle@@PAURpIntersection@@PAURpWorldSector@@PAU1@MPAX@Z @ 0x00073BD0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
RpCollisionTriangle *sub_92540(RpIntersection *arg_0, RpWorldSector *arg_4, RpCollisionTriangle *arg_8,
                               RwReal arg_C, void *arg_10)
{
    type_92430 *var_14;
    RwReal lv_10;
    RwV3d var_C;

    var_C.x = (arg_0->t.line.end.x - arg_0->t.line.start.x) * arg_C + arg_0->t.line.start.x;
    var_C.y = (arg_0->t.line.end.y - arg_0->t.line.start.y) * arg_C + arg_0->t.line.start.y;
    var_C.z = (arg_0->t.line.end.z - arg_0->t.line.start.z) * arg_C + arg_0->t.line.start.z;
    var_14 = (type_92430 *)arg_10;
    lv_10 = var_C.y - dword_4B25A0.y;
    if (lv_10 <= flt_4B25AC && lv_10 > var_14->unk_04)
    {
        var_14->unk_04 = lv_10;
        var_14->unk_00 = &((type_92540 *)arg_4)->unk_04[arg_8->index];
        var_14->unk_20 = ((type_92540 *)arg_4)->unk_08;
        var_14->unk_08 = var_C;
        if (lv_10 > -flt_4B25AC)
        {
            return 0;
        }
    }
    return arg_8;
}
