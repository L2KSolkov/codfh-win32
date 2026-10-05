// The vehicles' guns (type_15B110, four type_15B110_00 records in a vehicle's
// unk_DFC).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "game/functions.h"
#include "types/type_3DBC78_450.h"
#include "types/type_3DF8D8.h"
#include "types/type_3DBC78.h"
#include "types/type_15B110.h"
#include "rw/rpatomic.h"
#include "types/type_10F710.h"
#include "rw/bavector.h"
#include <string.h>
#include "types/SoldierTrigger.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x004D5170
type_4D5170 dword_4D5170;
// End of its data definitions.


// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_4D51C0 dword_4D51C0;
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __ehhandler$??0type_15B110_00@@QAE@XZ>1>8 @ 0x0041DFB0
// match: __ehhandler$??0type_15B110_00@@QAE@XZ>1 @ 0x0041DFB8
// match: __ehhandler$??1type_15B110_00@@QAE@XZ>1>8 @ 0x0041DFD4
// match: __ehhandler$??1type_15B110_00@@QAE@XZ>1 @ 0x0041DFDC
// match: __ehhandler$??1type_15B110@@QAE@XZ>1>8 @ 0x0041DFF8
// match: __ehhandler$??1type_15B110@@QAE@XZ>1 @ 0x0041E000
// match: .CRT$XCU+0 @ 0x00427124

// match: _$E2 @ 0x0030BC00
// match: ??0type_15B110@@QAE@XZ @ 0x0015B110

type_15B110::type_15B110()
{
    unk_300 = -1;
}

// match: ??0type_15B110_00@@QAE@XZ @ 0x0015B150
// match: ?sub_15B2A0@type_15B110@@QAEXPAUtype_3DF8D8@@PAX@Z @ 0x0015B2A0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The guns from the vehicle's model object arg_0 (a copy of each gun's
// projectile model, its particles, speed, magazine and flash time) and its
// trigger arg_4 (their damage and rate of fire; without one, a shot every
// six frames).
void type_15B110::sub_15B2A0(type_3DF8D8 *arg_0, void *arg_4)
{
    RwInt32 var_C;
    RpClump *bp_8;
    RpClump *bp_4;

    bp_4 = 0;
    bp_8 = 0;
    for (var_C = 0; var_C < 4; var_C++)
    {
        bp_8 = ((type_1917A0 *)arg_0)->sub_18F830((type_1917A0_10 *)(get_gun_model((type_14D2C0_10 *)arg_0->unk_10, var_C)));
        if (!bp_8)
        {
            unk_00[var_C].unk_00.sub_129620(0);
        }
        else
        {
            bp_4 = RpClumpClone(bp_8);
            if (!bp_4)
                return;
            unk_00[var_C].unk_00.sub_129620(bp_4);
        }
        unk_00[var_C].unk_10 = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_4C(var_C, 0);
        unk_00[var_C].unk_14 = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_4C(var_C, 1);
        unk_00[var_C].unk_0C = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_3C(var_C);
        unk_00[var_C].unk_18 = 0;
        unk_00[var_C].unk_1C = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_6C(var_C) * 60.0f;
        unk_00[var_C].unk_20 = 0;
        unk_00[var_C].unk_34 = ((type_14D2C0_10 *)arg_0->unk_10)->get_unk_7C(var_C);
        if (arg_4)
        {
            unk_00[var_C].unk_24 = ((type_712B0_3DBC78 *)arg_4)->unk_15C[var_C];
            unk_00[var_C].unk_28 = ((type_712B0_3DBC78 *)arg_4)->unk_16C[var_C];
            unk_00[var_C].unk_30 = 1.0f / ((type_712B0_3DBC78 *)arg_4)->unk_17C[var_C] * 60.0f;
            unk_00[var_C].unk_2C = 0.0f;
        }
        else
        {
            unk_00[var_C].unk_24 = 0;
            unk_00[var_C].unk_28 = 0;
            unk_00[var_C].unk_30 = 6.0f;
            unk_00[var_C].unk_2C = 0.0f;
        }
    }
}

// match: __ehhandler$??0type_15B110_00@@QAE@XZ-0x8 @ 0x00301D70
// match: __ehhandler$??0type_15B110_00@@QAE@XZ @ 0x00301D78
// match: ??1type_15B110_00@@QAE@XZ @ 0x0015B1C0
// match: __ehhandler$??1type_15B110_00@@QAE@XZ-0x8 @ 0x00301D90
// match: __ehhandler$??1type_15B110_00@@QAE@XZ @ 0x00301D98
// (Defined in the class, in type_15B110.h; out of line here for the guns'
// eh vector iterators.)

// match: ??1type_15B110@@QAE@XZ @ 0x0015B220
// match: __ehhandler$??1type_15B110@@QAE@XZ-0x16 @ 0x00301DB0
// match: __ehhandler$??1type_15B110@@QAE@XZ @ 0x00301DC6
// Releases each gun's projectile model, then the guns go.
type_15B110::~type_15B110()
{
    RwInt32 var_10;

    for (var_10 = 0; var_10 < 4; var_10++)
        unk_00[var_10].unk_00.sub_129940(0);
}

// match: ?sub_15B510@type_15B110@@QAEXM@Z @ 0x0015B510
void type_15B110::sub_15B510(RwReal arg_0)
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 4; var_4++)
    {
        unk_00[var_4].unk_18 += arg_0;
        if (unk_00[var_4].unk_18 > unk_00[var_4].unk_1C)
            unk_00[var_4].unk_20 = unk_00[var_4].unk_34;
        unk_00[var_4].unk_2C += arg_0;
    }
}

// match: ?sub_15B5D0@type_4D51C0@@QAEXXZ @ 0x0015B5D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Does nothing: it returns first. Its dead body builds dword_4D5170 (an
// identity matrix, the square of four corners 50 apart, sub_15B730) and
// runs its sub_15BC10. VC7.1 drops the dead statements up to the matrix
// macro's loop label, then emits the rest; the two it drops still advance
// the register rotation (the image's macro starts on edx), so they stand
// in as two loads.
void type_4D51C0::sub_15B5D0()
{
    RwReal var_34;
    RwV3d local_30[4];

    return;
    var_34 = local_30[0].x;
    var_34 = local_30[0].y;
    RwMatrixSetIdentityMacro(&dword_4D5170.unk_00);
    dword_4D5170.unk_00.pos.x = 0.0f;
    dword_4D5170.unk_00.pos.y = 0.0f;
    dword_4D5170.unk_00.pos.z = 0.0f;
    var_34 = 50.0f;
    local_30[0].x = -var_34;
    local_30[0].y = var_34;
    local_30[0].z = 0.0f;
    local_30[1].x = var_34;
    local_30[1].y = var_34;
    local_30[1].z = 0.0f;
    local_30[2].x = var_34;
    local_30[2].y = -var_34;
    local_30[2].z = 0.0f;
    local_30[3].x = -var_34;
    local_30[3].y = -var_34;
    local_30[3].z = 0.0f;
    dword_4D5170.unk_40 = sub_15B730(local_30);
    dword_4D5170.unk_44 = 0;
    dword_4D5170.sub_15BC10();
}

// match: ?sub_15B720@type_4D51C0@@QAEXXZ @ 0x0015B720
void type_4D51C0::sub_15B720()
{
    RwV3d var_C;
    RwReal var_10;
    RwReal var_14;

    return;
    var_C.x = var_10 = var_14 = 0.0f;
}

// match: ?sub_15B730@@YAPAUtype_15B730@@PAURwV3d@@@Z @ 0x0015B730
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_15B730 *sub_15B730(RwV3d *arg_0)
{
    RwV3d var_30;
    RwV3d var_24;
    type_15B730 *bp_18;
    RwV3d var_14;
    RwInt32 var8;
    type_15B730_00 *l4;

    bp_18 = (type_15B730 *)RWSMalloc(sizeof(type_15B730), 0x34250); // not an address: a memory hint
    bp_18->unk_00 = (type_15B730_00 *)RWSMalloc(sizeof(type_15B730_00), 0x34250); // not an address: a memory hint
    memset(bp_18->unk_00, 0, sizeof(type_15B730_00));
    bp_18->unk_04 = 1;
    l4 = bp_18->unk_00;
    var_30.x = arg_0[1].x - arg_0[0].x;
    var_30.y = arg_0[1].y - arg_0[0].y;
    var_30.z = arg_0[1].z - arg_0[0].z;
    RwV3dNormalize(&var_30, &var_30);
    var_14.x = arg_0[1].x - arg_0[2].x;
    var_14.y = arg_0[1].y - arg_0[2].y;
    var_14.z = arg_0[1].z - arg_0[2].z;
    RwV3dNormalize(&var_14, &var_14);
    RwV3dCrossProductMacro(&var_24, &var_30, &var_14);
    RwV3dNormalize(&var_24, &var_24);
    RwMatrixSetIdentityMacro(&l4->unk_00);
    l4->unk_00.pos.x = (arg_0[0].x + arg_0[1].x + arg_0[2].x + arg_0[3].x) / 4.0f;
    l4->unk_00.pos.y = (arg_0[0].y + arg_0[1].y + arg_0[2].y + arg_0[3].y) / 4.0f;
    l4->unk_00.pos.z = (arg_0[0].z + arg_0[1].z + arg_0[2].z + arg_0[3].z) / 4.0f;
    for (var8 = 0; var8 < 4; var8++)
    {
        l4->unk_40[var8].x = arg_0[var8].x - l4->unk_00.pos.x;
        l4->unk_40[var8].y = arg_0[var8].y - l4->unk_00.pos.y;
    }
    l4->unk_60[0].x = 0.0f;
    l4->unk_60[0].y = 0.0f;
    l4->unk_60[1].x = 1.0f;
    l4->unk_60[1].y = 0.0f;
    l4->unk_60[2].x = 1.0f;
    l4->unk_60[2].y = 1.0f;
    l4->unk_60[3].x = 0.0f;
    l4->unk_60[3].y = 1.0f;
    return bp_18;
}

// match: ?sub_15BA00@type_15BCC0@@QAEXXZ @ 0x0015BA00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_15BCC0::sub_15BA00()
{
    type_15BCC0 **var_C;
    type_4D51C0 *bp_8;
    RwInt32 bp_4;

    bp_8 = &dword_4D51C0;
    for (bp_4 = 0; bp_4 < bp_8->unk_1F4;)
    {
        if (bp_8->unk_B4[bp_4] == this)
        {
            bp_8->unk_B4[bp_4] = bp_8->unk_B4[bp_8->unk_1F4 - 1];
            bp_8->unk_104[bp_4] = bp_8->unk_104[bp_8->unk_1F4 - 1];
            bp_8->unk_1F4 = bp_8->unk_1F4 - 1;
        }
        else
        {
            bp_4++;
        }
    }
    bp_8->sub_15BB60(this);
    var_C = &unk_128->unk_44;
    while (*var_C)
    {
        if (*var_C == this)
        {
            *var_C = (*var_C)->unk_12C;
            break;
        }
        var_C = &(*var_C)->unk_12C;
    }
    unk_124 &= 0xFFFFFF00;
    unk_12C = bp_8->unk_208;
    bp_8->unk_208 = this;
    bp_8->unk_20C = bp_8->unk_20C - 1;
}

// match: ?sub_15BB60@type_4D51C0@@QAEXPAUtype_15BCC0@@@Z @ 0x0015BB60
void type_4D51C0::sub_15BB60(type_15BCC0 *arg_0)
{
    type_15BB60 **var_4;

    if (!arg_0->unk_130)
        return;
    var_4 = &unk_1F8;
    while (*var_4)
    {
        if ((*var_4)->unk_58 == arg_0)
        {
            *var_4 = (*var_4)->unk_54;
            arg_0->unk_130->unk_54 = unk_1FC;
            unk_1FC = arg_0->unk_130;
            arg_0->unk_130 = 0;
            unk_200 = unk_200 - 1;
            return;
        }
        var_4 = &(*var_4)->unk_54;
    }
}

// match: ?sub_15BC10@type_4D5170@@QAEXXZ @ 0x0015BC10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// A decal for each of its quads (their unit squares, cut by the manager).
void type_4D5170::sub_15BC10()
{
    type_15B730 *var_14;
    type_15BCC0 *lv_10;
    type_4D51C0 *var_C;
    RwInt32 bp_8;
    type_15B730_00 *bp_4;

    bp_8 = 0;
    var_14 = unk_40;
    unk_44 = 0;
    var_C = &dword_4D51C0;
    bp_4 = var_14->unk_00;
    for (bp_8 = 0; bp_8 < var_14->unk_04; bp_8++)
    {
        lv_10 = dword_4D51C0.sub_15BCC0(&var_C->unk_00[0], &var_C->unk_00[1], &var_C->unk_00[3], &var_C->unk_00[2], 4,
                                         bp_4, &bp_4->unk_00, this, 0, 4, 0);
        if (lv_10)
            lv_10->unk_134 = bp_4;
        bp_4++;
    }
}

// match: ?sub_15BCC0@type_4D51C0@@QAEPAUtype_15BCC0@@PAURwV2d@@000HPAUtype_15B730_00@@PAURwMatrixTag@@PAUtype_4D5170@@HHPAU2@@Z @ 0x0015BCC0
// A decal from the pool, last on arg_1C's list: arg_28's settings, the
// matrix arg_18 (or the identity); first a corner of the quad arg_14 when
// arg_0 and arg_4 lie on the two edges meeting there (unless flag 4), then
// arg_0 to arg_C (arg_C only for four), each with its UVs; the points
// centred, the centre moved into the matrix and the points taken through
// it. arg_20 is unused.
type_15BCC0 *type_4D51C0::sub_15BCC0(RwV2d *arg_0, RwV2d *arg_4, RwV2d *arg_8, RwV2d *arg_C, RwInt32 arg_10,
                                     type_15B730_00 *arg_14, RwMatrix *arg_18, type_4D5170 *arg_1C,
                                     RwInt32 arg_20, RwInt32 arg_24, type_15BCC0 *arg_28)
{
    type_140490 var_20;
    type_15BCC0 *var_24;
    type_15BCC0 **var_28;
    RwV3d var_34;
    RwInt32 var_38;
    RwV3d var_44;
    RwV3d var_50;

    var_20.x = 128.0f;
    var_20.y = 128.0f;
    var_20.z = 128.0f;
    var_20.w = 128.0f;
    var_24 = sub_15C510();
    if (!var_24)
        goto end;
    var_24->unk_130 = 0;
    var_24->unk_124_8 = arg_14->unk_C0;
    var_24->unk_134 = arg_14;
    var_28 = &arg_1C->unk_44;
    while (*var_28)
        var_28 = &(*var_28)->unk_12C;
    var_24->unk_12C = 0;
    *var_28 = var_24;
    var_24->unk_128 = arg_1C;
    if (arg_28)
    {
        var_24->unk_13C = arg_28->unk_13C;
        var_24->unk_138 = arg_28->unk_138;
        var_24->unk_140 = arg_28->unk_140;
    }
    if (arg_18)
        var_24->unk_00 = *arg_18;
    else
        RwMatrixSetIdentityMacro(&var_24->unk_00);
    var_24->unk_120 = 0;
    if (!(var_24->unk_124_0 & 4))
    {
        if (arg_0->x == 0.5f && arg_4->y == 0.5f)
        {
            var_24->unk_D0[var_24->unk_120] = var_20;
            sub_15C610(0.5f, 0.5f, arg_14, &var_24->unk_40[var_24->unk_120], &var_24->unk_A4[var_24->unk_120]);
            var_24->unk_120 = var_24->unk_120 + 1;
        }
        else if (arg_0->y == -0.5f && arg_4->x == 0.5f)
        {
            var_24->unk_D0[var_24->unk_120] = var_20;
            sub_15C610(0.5f, -0.5f, arg_14, &var_24->unk_40[var_24->unk_120], &var_24->unk_A4[var_24->unk_120]);
            var_24->unk_120 = var_24->unk_120 + 1;
        }
        else if (arg_0->y == 0.5f && arg_4->x == -0.5f)
        {
            var_24->unk_D0[var_24->unk_120] = var_20;
            sub_15C610(-0.5f, 0.5f, arg_14, &var_24->unk_40[var_24->unk_120], &var_24->unk_A4[var_24->unk_120]);
            var_24->unk_120 = var_24->unk_120 + 1;
        }
        else if (arg_0->x == -0.5f && arg_4->y == -0.5f)
        {
            var_24->unk_D0[var_24->unk_120] = var_20;
            sub_15C610(-0.5f, -0.5f, arg_14, &var_24->unk_40[var_24->unk_120], &var_24->unk_A4[var_24->unk_120]);
            var_24->unk_120 = var_24->unk_120 + 1;
        }
    }
    var_24->unk_D0[var_24->unk_120] = var_20;
    sub_15C610(arg_0->x, arg_0->y, arg_14, &var_24->unk_40[var_24->unk_120], &var_24->unk_A4[var_24->unk_120]);
    var_24->unk_120 = var_24->unk_120 + 1;
    var_24->unk_D0[var_24->unk_120] = var_20;
    sub_15C610(arg_4->x, arg_4->y, arg_14, &var_24->unk_40[var_24->unk_120], &var_24->unk_A4[var_24->unk_120]);
    var_24->unk_120 = var_24->unk_120 + 1;
    var_24->unk_D0[var_24->unk_120] = var_20;
    sub_15C610(arg_8->x, arg_8->y, arg_14, &var_24->unk_40[var_24->unk_120], &var_24->unk_A4[var_24->unk_120]);
    var_24->unk_120 = var_24->unk_120 + 1;
    if (arg_10 == 4)
    {
        var_24->unk_D0[var_24->unk_120] = var_20;
        sub_15C610(arg_C->x, arg_C->y, arg_14, &var_24->unk_40[var_24->unk_120], &var_24->unk_A4[var_24->unk_120]);
        var_24->unk_120 = var_24->unk_120 + 1;
    }
    var_34.x = 0.0f;
    var_34.y = 0.0f;
    var_34.z = 0.0f;
    for (var_38 = 0; var_38 < var_24->unk_120; var_38++)
    {
        var_34.x += var_24->unk_40[var_38].x;
        var_34.y += var_24->unk_40[var_38].y;
    }
    var_34.x = var_34.x / var_24->unk_120;
    var_34.y = var_34.y / var_24->unk_120;
    for (var_38 = 0; var_38 < var_24->unk_120; var_38++)
    {
        var_24->unk_40[var_38].x = var_24->unk_40[var_38].x - var_34.x;
        var_24->unk_40[var_38].y = var_24->unk_40[var_38].y - var_34.y;
    }
    sub_140130(&var_44, &var_34, (type_8BFA0 *)&var_24->unk_00);
    var_24->unk_00.pos.x = var_44.x;
    var_24->unk_00.pos.y = var_44.y;
    var_24->unk_00.pos.z = var_44.z;
    var_24->unk_124_0 = var_24->unk_124_0 | arg_24;
    for (var_38 = 0; var_38 < var_24->unk_120; var_38++)
    {
        var_50.x = var_24->unk_40[var_38].x;
        var_50.y = var_24->unk_40[var_38].y;
        var_50.z = 0.0f;
        sub_140130(&var_24->unk_68[var_38], &var_50, (type_8BFA0 *)&var_24->unk_00);
    }
end:
    return var_24;
}

// match: ?sub_15C510@type_4D51C0@@QAEPAUtype_15BCC0@@XZ @ 0x0015C510
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_15BCC0 *type_4D51C0::sub_15C510()
{
    type_15BCC0 *var_8;
    RwInt32 l4;

    if (unk_20C == 50)
    {
        l4 = 0;
        while (l4 < 50)
        {
            if (!(unk_210[l4].unk_124_0 & 0x44))
            {
                unk_210[l4].sub_15BA00();
                l4 += 4;
            }
            else
            {
                l4++;
            }
        }
    }
    if (unk_208)
    {
        var_8 = unk_208;
        unk_208 = unk_208->unk_12C;
        unk_20C = unk_20C + 1;
        var_8->unk_124_0 = var_8->unk_124_0 | 1;
        return var_8;
    }
    return 0;
}

// match: ?sub_15C610@type_4D51C0@@QAEXMMPAUtype_15B730_00@@PAURwV2d@@1@Z @ 0x0015C610
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_4D51C0::sub_15C610(RwReal arg_0, RwReal arg_4, type_15B730_00 *arg_8, RwV2d *arg_C, RwV2d *arg_10)
{
    RwV2d var_20;
    RwV2d m_18;
    RwV2d lv_10;
    RwV2d bp_8;

    arg_0 += 0.5f;
    arg_4 += 0.5f;
    m_18.x = (1.0f - arg_0) * arg_8->unk_40[0].x + arg_0 * arg_8->unk_40[1].x;
    m_18.y = (1.0f - arg_0) * arg_8->unk_40[0].y + arg_0 * arg_8->unk_40[1].y;
    var_20.x = (1.0f - arg_0) * arg_8->unk_60[0].x + arg_0 * arg_8->unk_60[1].x;
    var_20.y = (1.0f - arg_0) * arg_8->unk_60[0].y + arg_0 * arg_8->unk_60[1].y;
    bp_8.x = (1.0f - arg_0) * arg_8->unk_40[3].x + arg_0 * arg_8->unk_40[2].x;
    bp_8.y = (1.0f - arg_0) * arg_8->unk_40[3].y + arg_0 * arg_8->unk_40[2].y;
    lv_10.x = (1.0f - arg_0) * arg_8->unk_60[3].x + arg_0 * arg_8->unk_60[2].x;
    lv_10.y = (1.0f - arg_0) * arg_8->unk_60[3].y + arg_0 * arg_8->unk_60[2].y;
    arg_C->x = (1.0f - arg_4) * m_18.x + bp_8.x * arg_4;
    arg_C->y = (1.0f - arg_4) * m_18.y + bp_8.y * arg_4;
    arg_10->x = (1.0f - arg_4) * var_20.x + lv_10.x * arg_4;
    arg_10->y = 1.0f - ((1.0f - arg_4) * var_20.y + lv_10.y * arg_4);
}

// Members /OPT:ICF folded into shared trivial bodies (config/aliases.txt): defined here for
// the authentic link (PLAN M7); the placement link takes the shared bodies.

// ?pDtor@type_4D51C0@@QAEXXZ (folded into the empty body at 0x1E41C0)
void type_4D51C0::pDtor()
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_4D51C0@@QAE@XZ (folded into 0x6FCD0)
type_4D51C0::type_4D51C0()
{
    
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ?sub_15FB30@type_4D51C0@@QAEXPAURwCamera@@@Z (folded into 0x15FB30)
void type_4D51C0::sub_15FB30(struct RwCamera * arg_0)
{
}
