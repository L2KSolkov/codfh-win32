// The soldier (type_3DAFC8): head tracking, its spawn, its construction and
// its behaviour.

#include <math.h>
#include "rw/ostypes.h"
#include "rw/bavector.h"
#include "rw/bamatrix.h"
#include "rw/rtquat.h"
#include "game/frand.h"
#include "types/type_3DA6C0.h"
#include "types/type_3D94B8.h"
#include "types/type_8A980.h"
#include "types/CGlobalSounds.h"
#include "types/type_1227C0.h"
#include "types/type_92430.h"
#include "game/decals.h"
#include "types/animkey.h"
#include "types/type_FC6F0.h"
#include "rw/rphanim.h"
#include "game/functions.h"
#include "game/data.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/animkey.h"
#include "types/animobjpool.h"
#include "types/type_4B85F8.h"
#include "types/type_3D32F8.h"
#include "types/type_44350.h"
#include "types/SoldierTrigger.h"
#include "types/type_3DF8D8.h"
#include "types/type_3D2E7C.h"
#include "types/type_3C540.h"
#include "types/alfaobject.h"
#include "types/ccess.h"
#include "types/animbank.h"
#include "types/soundbank.h"
#include "types/type_154C0_80.h"
#include "types/type_10F710.h"
#include "rw/baframe.h"
#include "rw/rpworld.h"
#include "rw/rphanim.h"
#include "rw/rprandom.h"
#include "rw/rpatomic.h"
#include "game/clumpdata.h"
#include <string.h>
#include <stdio.h>
#include "game/vecutil.h"
#include "rws/skinhelper.h"
#include "types/type_3D51C0.h"
#include <xmmintrin.h>
#include "types/type_3D5658.h"
#include "types/vec4.h"
#include "game/pathnodes.h"
#include "game/startup.h"
#include "rw/rtquat.h"
#include "types/type_3DC048.h"
#include "types/type_3DBC78.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DAEA8
extern const RwReal flt_3DAEA8 = 16.666666f;
// 0x00429C3C
RwReal dword_429C3C = -5.0f;
// 0x00429C40
RwReal flt_429C40 = 0.8f;
// 0x00429C44
RwReal flt_429C44 = 0.9f;
// 0x00429C48
RwReal flt_429C48 = 0.8f;
// 0x00429C4C
RwReal flt_429C4C = 10.0f;
// 0x00429C50
RwReal flt_429C50 = 50.0f;
// 0x00429C54
RwReal flt_429C54 = 30.0f;
// 0x00429C58
RwReal flt_429C58 = 50.0f;
// 0x00429C5C
RwReal flt_429C5C = 0.25f;
// 0x00429C60
RwReal flt_429C60 = 500.0f;
// 0x00429C64
RwReal flt_429C64 = 100.0f;
// 0x00429C68
RwReal flt_429C68 = 1.1975f;
// 0x00429C6C
RwReal flt_429C6C = 0.364f;
// 0x00429C70
RwReal flt_429C70 = 12.0f;
// 0x00429C74
RwReal flt_429C74 = 6.0f;
// 0x00429C78
RwReal flt_429C78 = 2.0f;
// 0x00429C7C
RwReal flt_429C7C = 0.3f;
// 0x00429C80
RwReal flt_429C80 = 0.2f;
// 0x00429C84
RwReal flt_429C84 = 0.1f;
// 0x00429C88
RwReal flt_429C88 = 0.25f;
// 0x00429C8C
RwReal flt_429C8C = 4.0f;
// 0x00429C90
RwReal flt_429C90 = 2.0f;
// 0x00429C94
#ifndef CODFH_SP // single player lacks it: flt_429C98 follows flt_429C90 (SP 0x3221D8-0x3221DC)
RwInt32 dword_429C94 = 1;
#endif
// 0x00429C98
RwReal flt_429C98 = 45.0f;
// 0x00429C9C
RwReal flt_429C9C = 0.75f;
// 0x00429CA0
RwReal flt_429CA0 = 20.0f;
// 0x00429CA4
RwReal flt_429CA4 = 200.0f;
// 0x00429CA8
RwReal flt_429CA8 = 1000.0f;
// 0x00429CAC
RwReal flt_429CAC = 0.04125f;
// 0x00429CB0
RwReal flt_429CB0 = 0.0075f;
// 0x00429CB4
RwReal flt_429CB4 = 0.75f;
// 0x00429CB8
RwReal flt_429CB8 = 0.03f;
// 0x00429CBC
RwReal flt_429CBC = 10.0f;
// 0x00429CC0
RwReal flt_429CC0 = 100.0f;
// 0x00429CC4
RwReal flt_429CC4 = 1.732f;
// 0x00429CC8
RwReal flt_429CC8 = 100.0f;
// 0x00429CCC
RwReal flt_429CCC = 50.0f;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: __real@40490fdb @ 0x003DA6F4
// match: ?flt_3DAEA8@@3MB @ 0x003DAEA8
// match: __real@3e32b8c3 @ 0x003DAEAC
// match: __real@3f060a92 @ 0x003DAEB0
// match: __real@3fa78d36 @ 0x003DAEB4
// match: __real@3fc90fdb @ 0x003DAEB8
// match: ?dword_429C3C@@3MA @ 0x00429C3C
// match: ?flt_429C40@@3MA @ 0x00429C40
// match: ?flt_429C44@@3MA @ 0x00429C44
// match: ?flt_429C48@@3MA @ 0x00429C48
// match: ?flt_429C4C@@3MA @ 0x00429C4C
// match: ?flt_429C50@@3MA @ 0x00429C50
// match: ?flt_429C54@@3MA @ 0x00429C54
// match: ?flt_429C58@@3MA @ 0x00429C58
// match: ?flt_429C5C@@3MA @ 0x00429C5C
// match: ?flt_429C60@@3MA @ 0x00429C60
// match: ?flt_429C64@@3MA @ 0x00429C64
// match: ?flt_429C68@@3MA @ 0x00429C68
// match: ?flt_429C6C@@3MA @ 0x00429C6C
// match: ?flt_429C70@@3MA @ 0x00429C70
// match: ?flt_429C74@@3MA @ 0x00429C74
// match: ?flt_429C78@@3MA @ 0x00429C78
// match: ?flt_429C7C@@3MA @ 0x00429C7C
// match: ?flt_429C80@@3MA @ 0x00429C80
// match: ?flt_429C84@@3MA @ 0x00429C84
// match: ?flt_429C88@@3MA @ 0x00429C88
// match: ?flt_429C8C@@3MA @ 0x00429C8C
// match: ?flt_429C90@@3MA @ 0x00429C90
// match: ?dword_429C94@@3HA @ 0x00429C94
// match: ?flt_429C98@@3MA @ 0x00429C98
// match: ?flt_429C9C@@3MA @ 0x00429C9C
// match: ?flt_429CA0@@3MA @ 0x00429CA0
// match: ?flt_429CA4@@3MA @ 0x00429CA4
// match: ?flt_429CA8@@3MA @ 0x00429CA8
// match: ?flt_429CAC@@3MA @ 0x00429CAC
// match: ?flt_429CB0@@3MA @ 0x00429CB0
// match: ?flt_429CB4@@3MA @ 0x00429CB4
// match: ?flt_429CB8@@3MA @ 0x00429CB8
// match: ?flt_429CBC@@3MA @ 0x00429CBC
// match: ?flt_429CC0@@3MA @ 0x00429CC0
// match: ?flt_429CC4@@3MA @ 0x00429CC4
// match: ?flt_429CC8@@3MA @ 0x00429CC8
// match: ?flt_429CCC@@3MA @ 0x00429CCC
// match: ?flt_429C90@@3MA @ 0x00429C90

// An inline single player calls out of line (type_7C8D0::sub_76E00, called by sub_134160 at
// SP 0xE4960); this file emits the copy, just before sub_1340D0:
// sp-match: ?sub_76E00@type_7C8D0@@QAE_NH@Z @ 0x000E43E0

// match: ?sub_1340D0@type_3DAFC8@@QAEX_N0M@Z @ 0x001340D0
// sp-match: ?sub_1340D0@type_3DAFC8@@QAEX_N0M@Z @ 0x000E4430

void type_3DAFC8::sub_1340D0(bool arg_0, bool arg_4, RwReal arg_8)
{
    if (arg_0)
    {
        unk_824 = 4;
        if (arg_4)
            unk_824 |= 8;
    }
    if (!arg_0)
        unk_824 |= 0x10;
    unk_1DC4 = 0;
    unk_1DD4 = dword_4B87C8;
    unk_1DD8 = arg_8 * 60.0f;
}

// match: ?sub_134160@type_3DAFC8@@QAEXXZ @ 0x00134160
// sp-match: ?sub_134160@type_3DAFC8@@QAEXXZ @ 0x000E4960
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_3DAFC8::sub_134160()
{
    RwReal var_4;
    RwInt32 v8;
    RwInt32 stk_C;
    RwInt32 var_10;

    if (unk_1DC4 != 0 && !unk_284->sub_76E00(unk_1DC4))
    {
        unk_1DC4 = 0;
        if (!(unk_824 & 8))
        {
            unk_824 &= ~0x14;
            return;
        }
    }
    if (unk_824 & 4)
    {
        var_4 = 1.0f;
        if (unk_1DD8 != 0.0f)
            var_4 = (dword_4B87C8 - unk_1DD4) / unk_1DD8;
        if (var_4 > 1.0f)
            var_4 = 1.0f;
        if (unk_824 & 0x10)
            var_4 = 1.0f - var_4;
        if (var_4 == 0.0f && (unk_824 & 0x10))
        {
            if (unk_1DC4 != 0)
            {
                unk_284->sub_79BC0(unk_1DC4);
                unk_1DC4 = 0;
            }
            unk_824 &= ~0x1C;
        }
        else
        {
            var_10 = unk_284->unk_24;
            if (var_10 != 0)
            {
                if (unk_1DC4 == 0)
                    unk_1DC4 = unk_284->sub_79930(sub_134320, 1.0f, 1.0f);
                unk_284->sub_79C90(unk_1DC4, var_4);
            }
        }
    }
}

// The frame header head tracking hands its track (a copy of the current
// animation's, with the neck's rotation only).
type_7CBD0_hdr dword_4CF9B8;

// match: ?sub_134320@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x00134320
// sp-match: ?sub_134320@@YAXPAUtype_7C8D0@@PAUtype_80300@@H_N@Z @ 0x000E4490
// Head tracking's procedural track: when it starts (arg_C), its keys are the
// neck's rotation alone; after that, the neck (bone 453) turns from the
// head's axis towards the soldier's unk_1DC8, seen from bone 200, with its
// angles limited.
void sub_134320(type_7C8D0 *arg_0, type_80300 *arg_4, RwInt32 arg_8, bool arg_C)
{
    type_3DAFC8 *var_4;
    void *var_8;
    RpHAnimHierarchy *var_C;
    RwInt32 var_10;
    RpHAnimHierarchy *var_14;
    RwInt32 var_18;
    type_7CBD0 *var_1C;
    RtQuat *var_20;
    RpHAnimHierarchy *var_24;
    RpHAnimHierarchy *var_28;
    RwV3d var_34;
    RwMatrix *var_38;
    RwMatrix var_80;
    RwV3d var_8C;
    RwV3d var_98;
    RwReal var_9C;
    RwReal var_A0;
    RwReal var_A8;
    RwReal var_B0;
    RtQuat var_C0;
    RwV3d var_D0;
    RwV3d var_E4;
    RwReal var_EC;
    RwReal var_F4;
    RwReal var_FC;
    RwReal var_104;
    RwReal var_10C;
    RwReal var_114;
    RtQuat var_124;

    var_4 = (type_3DAFC8 *)arg_8;
    var_8 = arg_4->unk_128;
    var_C = arg_0->unk_18;
    var_10 = RpHAnimIDGetIndex(var_C, 200);
    var_14 = arg_0->unk_18;
    var_18 = RpHAnimIDGetIndex(var_14, 453);
    var_1C = (type_7CBD0 *)arg_4->unk_144;
    var_20 = var_1C->unk_10;
    if (arg_C)
    {
        var_24 = arg_0->unk_18;
        dword_4CF9B8 = *(type_7CBD0_hdr *)((type_80300 *)var_24->currentAnim)->unk_128;
        dword_4CF9B8.unk_08 = (RwUInt64)1 << var_18;
        sub_807C0((RtAnimInterpolator *)arg_4, &dword_4CF9B8);
        var_20[var_18].real = 1.0f;
        var_20[var_18].imag.z = 0.0f;
        var_20[var_18].imag.y = 0.0f;
        var_20[var_18].imag.x = 0.0f;
        var_1C->unk_04 = &dword_4CF9B8;
    }
    else if (var_4->unk_28_13)
    {
        var_28 = arg_0->unk_18;
        var_34.x = 0.0f;
        var_34.y = 0.0f;
        var_34.z = 1.0f;
        var_38 = &var_28->pMatrixArray[var_10];
        RwMatrixInvert(&var_80, &var_28->pMatrixArray[var_10]);
        RwV3dSubMacro(&var_8C, &var_4->unk_1DC8, &var_28->pMatrixArray[var_18].pos);
        sub_141320(&var_8C, &var_8C, &var_80);
        if (RwV3dNormalize(&var_8C, &var_8C) != 0.0f)
        {
            RwV3dCrossProductMacro(&var_98, &var_34, &var_8C);
            RwV3dNormalize(&var_98, &var_98);
            var_9C = RwV3dDotProductMacro(&var_34, &var_8C);
            if (var_9C < 1.0f)
            {
                var_A0 = (1.0f - var_9C) * 0.5f;
                var_A8 = sqrt(var_A0);
                var_B0 = sqrt(1.0f - var_A8 * var_A8);
                RwV3dScaleMacro(&var_98, &var_98, var_A8);
                var_C0.imag = var_98;
                var_C0.real = var_B0;
                if (var_C0.real != 0.0f)
                {
                    var_D0.x = asin(2.0f * (var_C0.imag.y * var_C0.imag.z + var_C0.real * var_C0.imag.x));
                    var_D0.y = atan2(-2.0f * (var_C0.imag.x * var_C0.imag.z - var_C0.real * var_C0.imag.y),
                                     2.0f * (var_C0.real * var_C0.real + var_C0.imag.z * var_C0.imag.z) - 1.0f);
                    var_D0.z = atan2(-2.0f * (var_C0.imag.x * var_C0.imag.y - var_C0.real * var_C0.imag.z),
                                     2.0f * (var_C0.real * var_C0.real + var_C0.imag.y * var_C0.imag.y) - 1.0f);
                    var_E4.x = var_E4.y = var_E4.z = 1.0f;
                    if (var_D0.x < 0.0f)
                    {
                        var_E4.x = -1.0f;
                        var_D0.x = -var_D0.x;
                    }
                    if (var_D0.y < 0.0f)
                    {
                        var_E4.y = -1.0f;
                        var_D0.y = -var_D0.y;
                    }
                    if (var_D0.z < 0.0f)
                    {
                        var_E4.z = -1.0f;
                        var_D0.z = -var_D0.z;
                    }
                    if (var_D0.x > 1.5707964f)
                        var_D0.x = 3.1415927f - var_D0.x;
                    if (var_D0.y > 1.5707964f)
                        var_D0.y = 3.1415927f - var_D0.y;
                    if (var_D0.z > 1.5707964f)
                        var_D0.z = 3.1415927f - var_D0.z;
                    if (var_D0.y > 1.3089969f)
                        var_D0.y = 1.3089969f;
                    if (var_D0.x > 0.52359879f)
                        var_D0.x = 0.52359879f;
                    if (var_D0.z > 0.17453294f)
                        var_D0.z = 0.17453294f;
                    var_EC = cos(var_E4.x * var_D0.x * 0.5f);
                    var_F4 = sin(var_E4.x * var_D0.x * 0.5f);
                    var_FC = cos(var_E4.y * var_D0.y * 0.5f);
                    var_104 = sin(var_E4.y * var_D0.y * 0.5f);
                    var_10C = cos(var_E4.z * var_D0.z * 0.5f);
                    var_114 = sin(var_E4.z * var_D0.z * 0.5f);
                    var_124.real = var_EC * var_FC * var_10C + var_F4 * var_104 * var_114;
                    var_124.imag.x = var_F4 * var_FC * var_10C - var_EC * var_104 * var_114;
                    var_124.imag.y = var_EC * var_104 * var_10C - var_F4 * var_FC * var_114;
                    var_124.imag.z = var_EC * var_FC * var_114 + var_F4 * var_104 * var_10C;
                    var_20[var_18] = var_124;
                }
            }
        }
    }
}

extern type_7CBD0_t flt_428A50[];
extern RwInt32 dword_42A050[];
extern type_42A1C8 dword_42A1C8[];
extern RwUInt32 dword_42A36C;
extern type_42A0B8 dword_42A0B8[];
extern RwUInt32 dword_42A1C0;

extern type_7CBD0_t flt_428A50[];
extern RwInt32 dword_42A050[];
extern type_42A1C8 dword_42A1C8[];
extern RwUInt32 dword_42A36C;
extern type_42A0B8 dword_42A0B8[];
extern RwUInt32 dword_42A1C0;

// The constructor, out of line.

// The class's inline overrides, emitted with its vtable in declaration order.

// (In the class.)





// The grenade throwing chance multiplier for the difficulty dword_42B714, 1
// outside 0 to 2: an inline with no address and so no database name, named
// for what it returns. Evidence: sub_136EC0 reads it through a temporary of
// its own with the range check of get_spread_multiplier (unit_11EE20).
// The table it reads (0x4F28D8).
extern RwReal flt_4F28D8[3];
inline RwReal get_grenade_multiplier()
{
    if (dword_42B714 > -1 && dword_42B714 < 3)
    {
        return flt_4F28D8[dword_42B714];
    }
    return 1.0f;
}









// The step scale for mode 1 of unk_1D28 (0.25, 0x429C88).
extern RwReal flt_429C88;













// The x axis (this unit's constant, read from memory: 0x3DAEC4).















// The suppression time scale (4, 0x429C8C).
extern RwReal flt_429C8C;







extern RwReal dword_4CF9D0;






// The bounds, in seconds, of the time a soldier held alive by its AI object
// (bit 14 of unk_49C) ignores bullets after one (0x4CF9D0, and 2 at
// 0x429C90).
RwReal dword_4CF9D0;





// The five-way blend's axes (this unit's constants, read from memory:
// 0x3DAED0 and 0x3DAEDC).
// The frame time, in milliseconds, this unit's own copy (0x3DAEC0, read from memory).


// SendFlying's tunables (this unit's data, 0x429C98 on): the launch angle and
// its adjustment, the speed's bounds and its factors.
extern RwReal flt_429C98;
extern RwReal flt_429C9C;
extern RwReal flt_429CA0;
extern RwReal flt_429CA4;
extern RwReal flt_429CA8;
extern RwReal flt_429CAC;
extern RwReal flt_429CB0;
extern RwReal flt_429CB4;
extern RwReal flt_429CB8;
















// The soldier's line of fire (vf_134): the side step (10), the height above
// which a close target counts as high (100), the ratio of squared distances
// below which it is close (1.732) and how far postures 0 and 1 lower the aim
// then (100, 50).
extern RwReal flt_429CBC;
extern RwReal flt_429CC0;
extern RwReal flt_429CC4;
extern RwReal flt_429CC8;
extern RwReal flt_429CCC;




// What the soldier's set-up (sub_135430) matches its definition and head
// against (type_42A0B8, type_42A1C8 in type_3DAFC8.h); then each node's
// parent (-1 for the root) and its bind pose offset, which the second
// animation's translations are made relative to.
extern type_42A0B8 dword_42A0B8[];
extern RwUInt32 dword_42A1C0;
extern type_42A1C8 dword_42A1C8[];
extern RwUInt32 dword_42A36C;
extern RwInt32 dword_42A050[];
extern type_7CBD0_t flt_428A50[];
// The soldier's unk_108 at first (-5).
extern RwReal dword_429C3C;
// The kind code of the weapon type arg_0 (8: a grenade); only the widths
// are known.
RwInt32 sub_15EFA0(RwInt32 arg_0);


// type_3DAFC8's overrides whose code is other classes' (ICF folded them:
// type_3DDB98::vf_078 at 0x17BDA0, type_3D5658's vf_0E4 and vf_0E8 at
// 0x9D0C0 and 0x9D0F0).
void type_3DAFC8::vf_078()
{
    sub_8D580(unk_284->get_unk_18(), 1);
}

RwInt32 type_3DAFC8::vf_0E4(RwInt32 arg_0)
{
    type_712B0 *var_4;

    var_4 = get_unk_34C();
    return ((type_3D5658_trigger *)var_4)->unk_C6[arg_0];
}

RwInt32 type_3DAFC8::vf_0E8()
{
    type_712B0 *var_8;
    RwInt32 l4;

    var_8 = get_unk_34C();
    for (l4 = 0; l4 < 5; l4++)
    {
        if (((type_3D5658_trigger *)var_8)->unk_C6[l4] == -1)
        {
            break;
        }
    }
    return l4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??2type_3DAFC8@@SAPAXIPAX@Z (folded into 0x6CCF0)
void *type_3DAFC8::operator new(RwUInt32 arg_0, void *arg_4)
{
    return arg_4;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DAFC8@@SAXPAX@Z (folded into 0x19A750)
void type_3DAFC8::operator delete(void * arg_0)
{
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??3type_3DAFC8@@SAXPAX0@Z (folded into 0x19A750)
void type_3DAFC8::operator delete(void * arg_0, void * arg_4)
{
}
