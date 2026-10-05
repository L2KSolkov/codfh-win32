// The particle renderer (game/particlerender.h): its set-up and shut-down, the
// spinning matrices, the camera's matrix, and the render states.

#include <stdlib.h>

#include "game/particlerender.h"
#include "game/clones.h"
#include "game/data.h"
#include "game/decals.h"
#include "game/frand.h"
#include "game/functions.h"
#include "rw/rprandom.h"
#include "rw/rwxbox.h"
#include "rw/badevice.h"
#include "rw/baengine.h"
#include "game/worldmgr.h"
#include "types/RenderTrigger.h"
#include "types/vec4.h"
#include "types/type_10F710.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003E0620
extern const RwReal flt_3E0620 = 16.666666f;
// 0x0042C780
RwReal nearClip = 1.0f;
// 0x0042C784
RwReal flt_42C784 = 100000.0f;
// 0x0042C788
RwReal flt_42C788 = 1.0f;
// 0x0042C78C
RwReal flt_42C78C = 1.3333334f;
// 0x0042C790
// The particles' spin sets (sub_19E500 sets them up).
RwMatrix *off_42C790[4] = { dword_4F4AB0, dword_4F4D80, dword_4F4F80, dword_4F48B0 };
// 0x0042C7A0
DWORD dword_42C7A0[4] = { 0x20000000, 0x40320000, 0x40320001, 0xFFFFFFFF };
// 0x0042C7B0
RwInt32 unk_42C7B0 = 1;
// 0x0042C7B4
RwReal flt_42C7B4[8] = { 3.14159f, -3.14159f, 1.570795f, -1.570795f, 1.0471967f, -1.0471967f, 0.7853975f, -0.7853975f };
// 0x0042C7D4
RwReal flt_42C7D4[8] = { 3.14159f, -3.14159f, 1.570795f, -1.0471967f, 0.7853975f, -0.628318f, 0.5235984f, -0.4487986f };
// 0x004F48B0
RwMatrix dword_4F48B0[8];
// 0x004F4AB0
RwMatrix dword_4F4AB0[8];
// 0x004F4CB0
#ifdef CODFH_PLAIN
// (plain builds: the SSE matrix routines, XGMatrixMultiply, need 16-byte alignment, which
// only the image's placement gives it)
__declspec(align(16)) D3DMATRIX stru_4F4CB0 = { 0 };
#else
D3DMATRIX stru_4F4CB0;
#endif
// 0x004F4CF0
DWORD dword_4F4CF0;
// 0x004F4D00
RwMatrix dword_4F4D00;
// 0x004F4D40
#ifdef CODFH_PLAIN
// (plain builds: the SSE matrix routines, XGMatrixMultiply, need 16-byte alignment, which
// only the image's placement gives it)
__declspec(align(16)) D3DMATRIX stru_4F4D40 = { 0 };
#else
D3DMATRIX stru_4F4D40;
#endif
// 0x004F4D80
RwMatrix dword_4F4D80[8];
// 0x004F4F80
RwMatrix dword_4F4F80[8];
// 0x004F5180
RwReal flt_4F5180[0x200];
// 0x004F5980
#ifdef CODFH_PLAIN
// (plain builds: the SSE matrix routines, XGMatrixMultiply, need 16-byte alignment, which
// only the image's placement gives it)
__declspec(align(16)) D3DMATRIX stru_4F5980 = { 0 };
#else
D3DMATRIX stru_4F5980;
#endif
// 0x004F59C0
#ifdef CODFH_PLAIN
// (plain builds: the SSE matrix routines, XGMatrixMultiply, need 16-byte alignment, which
// only the image's placement gives it)
__declspec(align(16)) D3DMATRIX stru_4F59C0 = { 0 };
#else
D3DMATRIX stru_4F59C0;
#endif
// 0x004F5A00
void *dword_4F5A00;
// 0x004F5A04
void *dword_4F5A04[11];
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3E0620@@3MB @ 0x003E0620
// match: ??_C@_0BA@GAEIMJHG@d?3?2particle?4xvu?$AA@ @ 0x003E0624
// match: __real@3a117d6b @ 0x003E0634
// match: ?nearClip@@3MA @ 0x0042C780
// match: ?flt_42C784@@3MA @ 0x0042C784
// match: ?flt_42C788@@3MA @ 0x0042C788
// match: ?flt_42C78C@@3MA @ 0x0042C78C
// match: ?off_42C790@@3PAPAURwMatrixTag@@A @ 0x0042C790
// match: ?dword_42C7A0@@3PAKA @ 0x0042C7A0
// match: ?unk_42C7B0@@3HA @ 0x0042C7B0
// match: ?flt_42C7B4@@3PAMA @ 0x0042C7B4
// match: ?flt_42C7D4@@3PAMA @ 0x0042C7D4

// match: ?sub_19E500@@YAXXZ @ 0x0019E500

// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The matrices set to the identity, the random offsets drawn, and the shader
// loaded.
void sub_19E500()
{
    RwInt32 var_8;
    RwInt32 l4;

    for (l4 = 0; l4 < 8; l4++)
    {
        RwMatrixSetIdentityMacro(&dword_4F4AB0[l4]);
        RwMatrixSetIdentityMacro(&dword_4F4D80[l4]);
        RwMatrixSetIdentityMacro(&dword_4F4F80[l4]);
        RwMatrixSetIdentityMacro(&dword_4F48B0[l4]);
    }
    for (var_8 = 0; var_8 < 0x200; var_8++)
        flt_4F5180[var_8] = frand_range(-0.5f, 0.5f);
    sub_19F790("d:\\particle.xvu", dword_42C7A0, &dword_4F4CF0);
}

// match: ?sub_19E930@@YAXXZ @ 0x0019E930
void sub_19E930()
{
    D3DDevice_DeleteVertexShader(dword_4F4CF0);
}

// match: ?sub_19E940@@YAXPAUtype_F2FF0_60@@@Z @ 0x0019E940
// Frees the system's vertex buffer and vertices.
void sub_19E940(type_F2FF0_60 *arg_0)
{
    type_F2FF0_60 *var_4;

    var_4 = arg_0;
    if (var_4->unk_D4)
    {
        if (var_4->unk_D4)
        {
            RwXbReleaseVertexBuffer((D3DVertexBuffer *)var_4->unk_D4);
            var_4->unk_D4 = 0;
        }
        if (var_4->unk_D8)
        {
            free((void *)var_4->unk_D8);
            var_4->unk_D8 = 0;
        }
    }
}

// match: ?sub_19E9B0@@YAXPAUtype_19E9B0@@PAURwV3d@@@Z @ 0x0019E9B0
void sub_19E9B0(type_19E9B0 *arg_0, RwV3d *arg_4)
{
    arg_0->unk_10.x = arg_4->x;
    arg_0->unk_10.y = arg_4->y;
    arg_0->unk_10.z = arg_4->z;
}

// match: ?sub_19E9E0@@YAXPAUtype_19E9B0@@PAURwV3d@@@Z @ 0x0019E9E0
void sub_19E9E0(type_19E9B0 *arg_0, RwV3d *arg_4)
{
    arg_0->unk_20.x = arg_4->x;
    arg_0->unk_20.y = arg_4->y;
    arg_0->unk_20.z = arg_4->z;
}

// match: ?sub_19EA10@@YAXXZ @ 0x0019EA10
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Turns the three sets of matrices about z by the frame's time.
void sub_19EA10()
{
    RwInt32 var_24;
    RwReal var_20;
    RwReal l1C;
    RwReal m_18;
    RwReal ebp_14;
    RwReal lv_10;
    RwV3d var_C;

    ebp_14 = 7200.0f;
    l1C = 3600.0f;
    lv_10 = 600.0f;
    var_C.x = 0;
    var_C.y = 0;
    var_C.z = 1.0f;
    var_20 = deltaTime * flt_3E0620 / 1000.0f;
    m_18 = 2.0f;
    var_20 = var_20 * m_18;
    ebp_14 = ebp_14 * var_20;
    l1C = l1C * var_20;
    lv_10 = lv_10 * var_20;
    for (var_24 = 0; var_24 < 8; var_24++)
    {
        sub_140440(&dword_4F4D80[var_24], &var_C, flt_42C7D4[var_24] / ebp_14);
        sub_140440(&dword_4F4F80[var_24], &var_C, flt_42C7D4[var_24] / l1C);
        sub_140440(&dword_4F48B0[var_24], &var_C, flt_42C7B4[var_24] / lv_10);
    }
}

// match: ?sub_19EB20@@YAXPAURwCamera@@@Z @ 0x0019EB20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Keeps the camera and its frame's matrix (its flags and padding cleared).
void sub_19EB20(RwCamera *arg_0)
{
    RwMatrix *var_8;
    RwMatrix *l4;

    dword_4F5A00 = arg_0;
    var_8 = RwFrameGetMatrix(RwCameraGetFrame(arg_0));
    dword_4F4D00 = *var_8;
    l4 = &dword_4F4D00;
    l4->flags = 0;
    l4->pad1 = 0;
    l4->pad2 = 0;
    *(RwReal *)&l4->pad3 = 1.0f;
    sub_19FB20();
}

// match: ?sub_19EB90@@YAXXZ @ 0x0019EB90
// Puts back the render states the particles changed, and no shader.
void sub_19EB90()
{
    RwRenderStateSet(rwRENDERSTATECULLMODE, dword_4F5A04[0]);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, dword_4F5A04[1]);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, dword_4F5A04[2]);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, dword_4F5A04[3]);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, dword_4F5A04[4]);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, dword_4F5A04[5]);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, dword_4F5A04[6]);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, dword_4F5A04[7]);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, dword_4F5A04[8]);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, dword_4F5A04[9]);
    RwRenderStateSet((RwRenderState)0x1D, dword_4F5A04[10]);
    RwXboxSetCurrentVertexShader(0);
}

// match: ?sub_19EC70@@YAPAUtype_F2FF0_60@@PAU1@PAURwMatrixTag@@PAUtype_F3130@@_N@Z @ 0x0019EC70
// Fills a sprite system's shader state from its definition and the matrix
// it starts at; returns it.
type_F2FF0_60 *sub_19EC70(type_F2FF0_60 *arg_0, RwMatrix *arg_4, type_F3130 *arg_8, bool arg_C)
{
    type_19EC70 *var_4;
    RwMatrix var_50;
    RwV3d var_5C;
    RwUInt32 *var_60;

    var_4 = (type_19EC70 *)arg_0;
    var_4->unk_E0 = arg_8;
    if (arg_8->unk_20 == 0.0f)
        var_4->unk_00 = (RwInt32)(arg_8->unk_18 * arg_8->unk_24 * 60.0f);
    else
        var_4->unk_00 = (RwInt32)(arg_8->unk_18 * arg_8->unk_20 * 60.0f);
    if (arg_8->unk_00 >= 4)
    {
        var_4->unk_10[0] = arg_8->unk_F8 * 8.33f;
        var_4->unk_10[1] = arg_8->unk_FC * 8.33f;
        var_4->unk_10[2] = arg_8->unk_100 * 8.33f;
        var_4->unk_10[3] = 1.0f;
        var_4->unk_20[0] = 0;
        var_4->unk_20[1] = -arg_8->unk_104 * 8.33f;
        var_4->unk_20[2] = 0;
        var_4->unk_20[3] = 1.0f;
    }
    else
    {
        var_4->unk_10[0] = 0;
        var_4->unk_10[1] = 0;
        var_4->unk_10[2] = 0;
        var_4->unk_10[3] = 1.0f;
        var_4->unk_20[0] = 0;
        var_4->unk_20[1] = 0;
        var_4->unk_20[2] = 0;
        var_4->unk_20[3] = 1.0f;
    }
    var_4->unk_30[0] = arg_8->unk_40 * arg_8->unk_2C * 10.0f;
    var_4->unk_30[1] = arg_8->unk_44 * arg_8->unk_2C * 10.0f;
    var_4->unk_30[2] = arg_8->unk_48 * arg_8->unk_2C * 10.0f;
    var_4->unk_30[3] = arg_8->unk_20 > 0.0f ? 0 : 1.0f;
    sub_140910(&var_50, arg_4);
    var_5C.x = arg_8->unk_34 * 2.0f;
    var_5C.y = arg_8->unk_38 * 2.0f;
    var_5C.z = arg_8->unk_3C * 2.0f;
    sub_141320(&var_5C, &var_5C, &var_50);
    var_4->unk_40[0] = var_5C.x * 10.0f;
    var_4->unk_40[1] = var_5C.y * 10.0f;
    var_4->unk_40[2] = var_5C.z * 10.0f;
    var_4->unk_40[3] = 1.0f;
    var_4->unk_50[0] = arg_8->unk_4C * arg_8->unk_2C * 10.0f;
    var_4->unk_50[1] = arg_8->unk_50 * arg_8->unk_2C * 10.0f;
    var_4->unk_50[2] = arg_8->unk_54 * arg_8->unk_2C * 10.0f;
    var_4->unk_50[3] = 1.0f;
    var_4->unk_60[0] = arg_8->unk_0C;
    var_4->unk_60[1] = arg_8->unk_10;
    var_4->unk_60[2] = arg_8->unk_14;
    var_4->unk_60[3] = 1.0f;
    var_4->unk_70 = 0;
    var_4->unk_74 = 1.0f / (arg_8->unk_18 * 60.0f);
    var_4->unk_78 = arg_8->unk_24;
    var_60 = &var_4->unk_7C;
    *var_60 = RpRandom() % 0x81;
    var_4->unk_80[0] = arg_8->unk_60;
    var_4->unk_80[1] = arg_8->unk_64;
    var_4->unk_80[2] = 0;
    var_4->unk_80[3] = 1.0f;
    var_4->unk_90[0] = arg_8->unk_70;
    var_4->unk_90[1] = arg_8->unk_74;
    var_4->unk_90[2] = 0;
    var_4->unk_90[3] = 1.0f;
    var_4->unk_A0[0] = (RwReal)(((RwInt32)arg_8->unk_58 & 0xFF0000) >> 16);
    var_4->unk_A0[1] = (RwReal)(((RwInt32)arg_8->unk_58 & 0xFF00) >> 8);
    var_4->unk_A0[2] = (RwReal)((RwInt32)arg_8->unk_58 & 0xFF);
    var_4->unk_A0[3] = (RwReal)(((RwInt32)arg_8->unk_58 & 0xFF000000) >> 24);
    var_4->unk_C0[0] = (RwReal)(((RwInt32)arg_8->unk_5C & 0xFF0000) >> 16);
    var_4->unk_C0[1] = (RwReal)(((RwInt32)arg_8->unk_5C & 0xFF00) >> 8);
    var_4->unk_C0[2] = (RwReal)((RwInt32)arg_8->unk_5C & 0xFF);
    var_4->unk_C0[3] = (RwReal)(((RwInt32)arg_8->unk_5C & 0xFF000000) >> 24);
    if (arg_8->unk_00 > 4)
    {
        var_4->unk_B0[0] = (RwReal)(((RwInt32)arg_8->unk_108 & 0xFF0000) >> 16);
        var_4->unk_B0[1] = (RwReal)(((RwInt32)arg_8->unk_108 & 0xFF00) >> 8);
        var_4->unk_B0[2] = (RwReal)((RwInt32)arg_8->unk_108 & 0xFF);
        var_4->unk_B0[3] = (RwReal)(((RwInt32)arg_8->unk_108 & 0xFF000000) >> 24);
    }
    else
    {
        var_4->unk_B0[0] = (var_4->unk_A0[0] + var_4->unk_C0[0]) * 0.5f;
        var_4->unk_B0[1] = (var_4->unk_A0[1] + var_4->unk_C0[1]) * 0.5f;
        var_4->unk_B0[2] = (var_4->unk_A0[2] + var_4->unk_C0[2]) * 0.5f;
        var_4->unk_B0[3] = (var_4->unk_A0[3] + var_4->unk_C0[3]) * 0.5f;
    }
    var_4->unk_DC = arg_C;
    sub_19F5B0(arg_0);
    var_4->unk_A0[0] = var_4->unk_A0[0] / 256.0f;
    var_4->unk_A0[1] = var_4->unk_A0[1] / 256.0f;
    var_4->unk_A0[2] = var_4->unk_A0[2] / 256.0f;
    var_4->unk_A0[3] = var_4->unk_A0[3] / 256.0f;
    var_4->unk_B0[0] = var_4->unk_B0[0] / 256.0f;
    var_4->unk_B0[1] = var_4->unk_B0[1] / 256.0f;
    var_4->unk_B0[2] = var_4->unk_B0[2] / 256.0f;
    var_4->unk_B0[3] = var_4->unk_B0[3] / 256.0f;
    var_4->unk_C0[0] = var_4->unk_C0[0] / 256.0f;
    var_4->unk_C0[1] = var_4->unk_C0[1] / 256.0f;
    var_4->unk_C0[2] = var_4->unk_C0[2] / 256.0f;
    var_4->unk_C0[3] = var_4->unk_C0[3] / 256.0f;
    var_4->unk_04 = 0;
    if (var_4->unk_20[0] != 0.0f || var_4->unk_20[1] != 0.0f || var_4->unk_20[2] != 0.0f)
        var_4->unk_04 |= 1;
    if (var_4->unk_10[0] != 0.0f || var_4->unk_10[1] != 0.0f || var_4->unk_10[2] != 0.0f)
        var_4->unk_04 |= 2;
    if (var_4->unk_40[0] != 0.0f || var_4->unk_40[1] != 0.0f || var_4->unk_40[2] != 0.0f)
        var_4->unk_04 |= 8;
    if (var_4->unk_30[0] != 0.0f || var_4->unk_30[1] != 0.0f || var_4->unk_30[2] != 0.0f)
        var_4->unk_04 |= 0x10;
    sub_19F840(var_4);
    var_4->unk_E4 = 0;
    if (var_4->unk_78 - 0.1f <= 0.0001f && var_4->unk_74 - 0.000555f < 0.00001f && var_4->unk_00 == 125)
    {
        var_4->unk_E4 |= 1;
        if (dword_4C19A8)
            var_4->unk_E4 |= 2;
    }
    return (type_F2FF0_60 *)var_4;
}

// match: ?sub_19F540@@YAXPAM@Z @ 0x0019F540
// Scales the colour arg_0 by the ambient colour.
void sub_19F540(RwReal *arg_0)
{
    RwRGBA var_4;

    var_4 = stru_4CF768;
    arg_0[0] = var_4.red * arg_0[0] / 256.0f;
    arg_0[1] = var_4.green * arg_0[1] / 256.0f;
    arg_0[2] = var_4.blue * arg_0[2] / 256.0f;
}

// match: ?sub_19F5B0@@YAXPAUtype_F2FF0_60@@@Z @ 0x0019F5B0
// Brightens the three colours.
void sub_19F5B0(type_F2FF0_60 *arg_0)
{
    type_19EC70 *var_4;

    var_4 = (type_19EC70 *)arg_0;
    sub_19F600(var_4->unk_A0);
    sub_19F600(var_4->unk_B0);
    sub_19F600(var_4->unk_C0);
}

// match: ?sub_19F600@@YAXPAM@Z @ 0x0019F600
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Brightens a colour 3.2 times, what goes past 255 in its channels going
// into its alpha (2.2 times and more), all kept at 255.
void sub_19F600(RwReal *arg_0)
{
    RwReal var_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    bp_8 = 3.2f;
    bp_4 = 2.2f;
    arg_0[0] = bp_8 * arg_0[0];
    arg_0[1] = bp_8 * arg_0[1];
    arg_0[2] = bp_8 * arg_0[2];
    var_10 = 0;
    if (arg_0[0] > 255.0f)
    {
        var_10 = (arg_0[0] - 255.0f) / 255.0f;
        arg_0[0] = 255.0f;
    }
    if (arg_0[1] > 255.0f)
    {
        var_C = (arg_0[1] - 255.0f) / 255.0f;
        if (var_C > var_10)
            var_10 = var_C;
        arg_0[1] = 255.0f;
    }
    if (arg_0[2] > 255.0f)
    {
        var_C = (arg_0[2] - 255.0f) / 255.0f;
        if (var_C > var_10)
            var_10 = var_C;
        arg_0[2] = 255.0f;
    }
    var_10 = var_10 + bp_4;
    arg_0[3] = var_10 * arg_0[3];
    if (arg_0[3] > 255.0f)
        arg_0[3] = 255.0f;
}

// match: ?sub_19F740@@YAXPAUtype_F2FF0_60@@PAUtype_F2FF0@@PAUtype_F3130@@I@Z @ 0x0019F740
// Draws a sprite system's particles with its definition's unk_A4 (0 if
// negative).
void sub_19F740(type_F2FF0_60 *arg_0, type_F2FF0 *arg_4, type_F3130 *arg_8, RwUInt32 arg_C)
{
    type_F2FF0_60 *var_4;

    var_4 = arg_0;
    sub_1A0860((type_19EC70 *)var_4, arg_4, arg_8->unk_A4 < 0 ? 0 : arg_8->unk_A4, arg_C);
}

// match: ?sub_19F790@@YAXPBDPAK1@Z @ 0x0019F790
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Loads the vertex shader file arg_0 with the declaration arg_4 into arg_8.
void sub_19F790(const RwChar *arg_0, DWORD *arg_4, DWORD *arg_8)
{
    DWORD var_14;
    BOOL lv_10;
    HANDLE var_C;
    DWORD bp_8;
    void *bp_4;

    var_C = CreateFileA(arg_0, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    bp_8 = GetFileSize(var_C, 0);
    bp_4 = RWSMalloc(bp_8 + 4, 0x34250); // not an address: a memory hint
    memset(bp_4, 0, bp_8 + 4);
    lv_10 = ReadFile(var_C, bp_4, bp_8, &var_14, 0);
    sub_19A750(lv_10);
    D3DDevice_CreateVertexShader(arg_4, (DWORD *)bp_4, arg_8, 0);
    CloseHandle(var_C);
    operator delete(bp_4);
}

// match: ?sub_19F840@@YAXPAUtype_19EC70@@@Z @ 0x0019F840
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Builds the vertex buffer: as many particles as live at once (at most
// unk_00), four corners each, their ages staggered by unk_74, their index
// counting to 8 and their random offsets.
void sub_19F840(type_19EC70 *arg_0)
{
    RwInt32 var_1C;
    RwReal *var_18;
    RwInt32 var_14;
    RwReal lv_10;
    RwInt32 var_C;
    RwReal bp_8;
    type_19F840_v *bp_4;

    var_C = (RwInt32)(arg_0->unk_78 / arg_0->unk_74);
    if (var_C < arg_0->unk_00)
        arg_0->unk_00 = var_C;
    arg_0->unk_D0 = 0;
    arg_0->unk_D4 = RwXbCreateVertexBuffer(arg_0->unk_00 * 0x18 * 4);
    D3DVertexBuffer_Lock(arg_0->unk_D4, 0, 0, (BYTE **)&bp_4, 0);
    lv_10 = 0;
    bp_8 = 0;
    for (var_14 = 0; var_14 < arg_0->unk_00 * 4; var_14 += 4)
    {
        bp_4[var_14].unk_00 = bp_8;
        bp_4[var_14 + 1].unk_00 = bp_8;
        bp_4[var_14 + 2].unk_00 = bp_8;
        bp_4[var_14 + 3].unk_00 = bp_8;
        var_1C = var_14 & 0x1FF;
        var_18 = &flt_4F5180[var_1C];
        bp_4[var_14].unk_0C = var_18[0];
        bp_4[var_14].unk_10 = var_18[1];
        bp_4[var_14].unk_14 = var_18[2];
        bp_4[var_14 + 1].unk_0C = var_18[0];
        bp_4[var_14 + 1].unk_10 = var_18[1];
        bp_4[var_14 + 1].unk_14 = var_18[2];
        bp_4[var_14 + 2].unk_0C = var_18[0];
        bp_4[var_14 + 2].unk_10 = var_18[1];
        bp_4[var_14 + 2].unk_14 = var_18[2];
        bp_4[var_14 + 3].unk_0C = var_18[0];
        bp_4[var_14 + 3].unk_10 = var_18[1];
        bp_4[var_14 + 3].unk_14 = var_18[2];
        bp_4[var_14].unk_04 = 0;
        bp_4[var_14 + 1].unk_04 = 1.0f;
        bp_4[var_14 + 2].unk_04 = 2.0f;
        bp_4[var_14 + 3].unk_04 = 3.0f;
        bp_4[var_14].unk_08 = lv_10;
        bp_4[var_14 + 1].unk_08 = lv_10;
        bp_4[var_14 + 2].unk_08 = lv_10;
        bp_4[var_14 + 3].unk_08 = lv_10;
        bp_8 -= (RwDouble)arg_0->unk_74;
        lv_10 = lv_10 + 1.0f;
        if (lv_10 >= 8.0f)
            lv_10 = 0;
    }
}

// match: ?sub_19FB20@@YAXXZ @ 0x0019FB20
// Sets up a frame's particle drawing: the clip planes, the view matrix and
// three projections (with the near plane, 160 and 1), the corner and axis
// shader constants, the render states (the old ones saved), the shaders and
// stage 0's blending (texture times diffuse).
void sub_19FB20()
{
    RwMatrix var_50;
    RwV3d *var_54;
    RwV3d var_60;
    RwV3d var_6C;
    RwV3d var_78;
    RwV2d *var_7C;
    type_140490 var_90;

    nearClip = *(RwReal *)&dword_4CF540 > 20.0f ? *(RwReal *)&dword_4CF540 : 20.0f;
    flt_42C784 = farClip;
    RwCameraSetNearClipPlane((RwCamera *)dword_4F5A00, nearClip);
    RwCameraSetFarClipPlane((RwCamera *)dword_4F5A00, flt_42C784);
    var_50 = dword_4F4D00;
    var_54 = &var_50.pos;
    RwV3dNormalize(&var_60, &var_50.up);
    RwV3dNormalize(&var_6C, &var_50.at);
    var_78.x = var_6C.x * 100.0f + var_54->x;
    var_78.y = var_6C.y * 100.0f + var_54->y;
    var_78.z = var_6C.z * 100.0f + var_54->z;
    D3DXMatrixLookAtRH((D3DXMATRIX *)&stru_4F59C0, (D3DXVECTOR3 *)var_54, (D3DXVECTOR3 *)&var_78, (D3DXVECTOR3 *)&var_60);
    var_7C = &((RwCamera *)dword_4E5C74)->viewWindow;
    flt_42C788 = ((0.7002f - var_7C->x) / 0.60684f * 0.12f + 1.38f) * var_7C->x;
    D3DXMatrixPerspectiveFovRH((D3DXMATRIX *)&stru_4F5980, flt_42C788, flt_42C78C, nearClip, flt_42C784);
    D3DXMatrixPerspectiveFovRH((D3DXMATRIX *)&stru_4F4D40, flt_42C788, flt_42C78C, 160.0f, flt_42C784);
    D3DXMatrixPerspectiveFovRH((D3DXMATRIX *)&stru_4F4CB0, flt_42C788, flt_42C78C, 1.0f, flt_42C784);
    var_90.x = -1.0f;
    var_90.y = -1.0f;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x33, &var_90, 1);
    var_90.x = 1.0f;
    var_90.y = -1.0f;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x34, &var_90, 1);
    var_90.x = 1.0f;
    var_90.y = 1.0f;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x35, &var_90, 1);
    var_90.x = -1.0f;
    var_90.y = 1.0f;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x36, &var_90, 1);
    var_90.x = 0;
    var_90.y = 1.0f;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x37, &var_90, 1);
    var_90.x = 1.0f;
    var_90.y = 1.0f;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x38, &var_90, 1);
    var_90.x = 1.0f;
    var_90.y = 0;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x39, &var_90, 1);
    var_90.x = 0;
    var_90.y = 0;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x3A, &var_90, 1);
    var_90.x = 0;
    var_90.y = 0;
    var_90.z = 0;
    var_90.w = 0;
    D3DDevice_SetVertexShaderConstantFast(0x3B, &var_90, 1);
    RwRenderStateGet(rwRENDERSTATECULLMODE, &dword_4F5A04[0]);
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &dword_4F5A04[1]);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &dword_4F5A04[2]);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &dword_4F5A04[3]);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &dword_4F5A04[4]);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &dword_4F5A04[5]);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &dword_4F5A04[6]);
    RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &dword_4F5A04[7]);
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &dword_4F5A04[8]);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &dword_4F5A04[9]);
    RwRenderStateGet(rwRENDERSTATEALPHATESTFUNCTION, &dword_4F5A04[10]);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void *)rwSHADEMODEGOURAUD);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void *)rwALPHATESTFUNCTIONALWAYS);
    RwXboxSetCurrentVertexShader(dword_4F4CF0);
    RwXboxSetCurrentPixelShader(0);
    RwXbSetTextureStageStateIfChanged(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    RwXbSetTextureStageStateIfChanged(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    RwXbSetTextureStageStateIfChanged(0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
    RwXbSetTextureStageStateIfChanged(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    RwXbSetTextureStageStateIfChanged(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    RwXbSetTextureStageStateIfChanged(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
}

// match: ?sub_1A0830@@YAHPAUtype_19EC70@@IPAUtype_F2FF0@@@Z @ 0x001A0830
// Whether a system draws in its own frame.
RwInt32 sub_1A0830(type_19EC70 *arg_0, RwUInt32 arg_4, type_F2FF0 *arg_8)
{
    if (arg_0->unk_E4 & 1)
        return 1;
    if (arg_4 & 0x40)
        return 1;
    return 0;
}

// match: ?sub_1A0860@@YAXPAUtype_19EC70@@PAUtype_F2FF0@@HI@Z @ 0x001A0860
// Draws a sprite system's particles: the shader's constants (the transform,
// the three colours, the times, the terms, the spin set arg_8 and the
// camera's axes) and the quads, multisampled.
void sub_1A0860(type_19EC70 *arg_0, type_F2FF0 *arg_4, RwInt32 arg_8, RwUInt32 arg_C)
{
    RwInt32 var_4;
    RwMatrix var_50;
    type_140490 var_60;
    type_140490 var_70;
    type_140490 var_80;
    RwMatrix var_C0;
    type_10F710 *var_C4;
    XGMATRIX *var_C8;
    XGMATRIX var_110;
    XGMATRIX var_150;
    RwInt32 var_154;
    type_140490 var_7A0[100];
    RwUInt8 *var_7A4;
    RwInt32 var_7A8;
    RwInt32 var_7AC;

    var_4 = sub_1A0830(arg_0, arg_C, arg_4);
    if (!var_4)
        var_50 = dword_4F4D00;
    else
        sub_141690(&var_50, 0);
    var_60 = *(type_140490 *)arg_0->unk_A0;
    var_70 = *(type_140490 *)arg_0->unk_B0;
    var_80 = *(type_140490 *)arg_0->unk_C0;
    if (arg_0->unk_DC)
    {
        sub_19F540(&var_60.x);
        sub_19F540(&var_70.x);
        sub_19F540(&var_80.x);
    }
    sub_141690(&var_C0, &arg_4->unk_00.pos);
    if (var_4)
    {
        var_C0.at = arg_4->unk_00.at;
        var_C0.right = arg_4->unk_00.right;
        var_C0.up = arg_4->unk_00.up;
    }
    if (arg_0->unk_E4 & 2)
    {
        var_C4 = (type_10F710 *)sub_1745A0(dword_429EB0);
        if (var_C4 && !var_C4->unk_4D0)
            var_C8 = (XGMATRIX *)&stru_4F4D40;
        else
            var_C8 = (XGMATRIX *)&stru_4F5980;
    }
    else if (!var_4)
        var_C8 = (XGMATRIX *)&stru_4F5980;
    else
        var_C8 = (XGMATRIX *)&stru_4F4CB0;
    XGMatrixMultiply(&var_110, (XGMATRIX *)&var_C0, (XGMATRIX *)&stru_4F59C0);
    XGMatrixMultiply(&var_150, &var_110, var_C8);
    XGMatrixTranspose(&var_150, &var_150);
    var_154 = 0;
    var_7A4 = (RwUInt8 *)var_7A0;
    memcpy(var_7A4, &var_150, 0x40);
    var_7A4 += 0x40;
    var_154 += 4;
    *(type_140490 *)var_7A4 = var_60;
    var_7A4 += 0x10;
    *(type_140490 *)var_7A4 = var_70;
    var_7A4 += 0x10;
    *(type_140490 *)var_7A4 = var_80;
    var_7A4 += 0x10;
    var_154 += 3;
    ((RwReal *)var_7A4)[0] = 1.0f / arg_0->unk_78;
    ((RwReal *)var_7A4)[1] = arg_0->unk_30[3];
    ((RwReal *)var_7A4)[2] = arg_0->unk_78;
    ((RwReal *)var_7A4)[3] = arg_0->unk_70;
    var_7A4 += 0x10;
    var_154 += 1;
    *(type_140490 *)var_7A4 = *(type_140490 *)arg_0->unk_50;
    var_7A4 += 0x10;
    var_154 += 1;
    *(type_140490 *)var_7A4 = *(type_140490 *)arg_0->unk_10;
    var_7A4 += 0x10;
    var_154 += 1;
    ((RwReal *)var_7A4)[0] = arg_0->unk_20[0] * 0.5f;
    ((RwReal *)var_7A4)[1] = arg_0->unk_20[1] * 0.5f;
    ((RwReal *)var_7A4)[2] = arg_0->unk_20[2] * 0.5f;
    ((RwReal *)var_7A4)[3] = 1.0f;
    var_7A4 += 0x10;
    var_154 += 1;
    *(type_140490 *)var_7A4 = *(type_140490 *)arg_0->unk_60;
    var_7A4 += 0x10;
    var_154 += 1;
    ((RwReal *)var_7A4)[0] = arg_0->unk_30[0];
    ((RwReal *)var_7A4)[1] = arg_0->unk_30[1];
    ((RwReal *)var_7A4)[2] = arg_0->unk_30[2];
    ((RwReal *)var_7A4)[3] = 1.0f;
    var_7A4 += 0x10;
    var_154 += 1;
    ((RwReal *)var_7A4)[0] = arg_0->unk_40[0] * 0.5f;
    ((RwReal *)var_7A4)[1] = arg_0->unk_40[1] * 0.5f;
    ((RwReal *)var_7A4)[2] = arg_0->unk_40[2] * 0.5f;
    ((RwReal *)var_7A4)[3] = 1.0f;
    var_7A4 += 0x10;
    var_154 += 1;
    ((RwReal *)var_7A4)[0] = arg_0->unk_80[0];
    ((RwReal *)var_7A4)[1] = arg_0->unk_80[1];
    ((RwReal *)var_7A4)[2] = arg_0->unk_90[0];
    ((RwReal *)var_7A4)[3] = arg_0->unk_90[1];
    var_7A4 += 0x10;
    var_154 += 1;
    memcpy(var_7A4, off_42C790[arg_8], 0x200);
    var_7A4 += 0x200;
    var_154 += 0x20;
    var_7A4 += 0x10;
    var_154 += 1;
    memcpy(var_7A4, &var_50, 0x30);
    var_7A4 += 0x30;
    var_154 += 3;
    if (var_154 <= 100)
        D3DDevice_SetVertexShaderConstantFast(0, var_7A0, var_154);
    D3DDevice_SetRenderState(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_4X);
    sub_1A15C0(arg_0, &var_7AC, &var_7A8);
    if (var_7AC)
    {
        D3DDevice_SetStreamSource(0, arg_0->unk_D4, 0x18);
        _rwXbFlushCacheBuffer();
        D3DDevice_DrawVertices(D3DPT_QUADLIST, var_7A8 * 4, var_7AC * 4);
    }
    D3DDevice_SetRenderState(D3DRS_MULTISAMPLEMODE, D3DMULTISAMPLEMODE_1X);
}

// match: ?sub_1A15C0@@YAXPAUtype_19EC70@@PAH1@Z @ 0x001A15C0
// The live particles' quads: while the system still emits (or until its
// emission time passes), the first ones up to the most alive so far (unk_D0);
// after it, the ones not yet expired.
void sub_1A15C0(type_19EC70 *arg_0, RwInt32 *arg_4, RwInt32 *arg_8)
{
    RwReal var_4;

    *arg_4 = (RwInt32)(arg_0->unk_70 / arg_0->unk_78);
    var_4 = arg_0->unk_70 - *arg_4 * arg_0->unk_78;
    *arg_4 = (RwInt32)(var_4 / arg_0->unk_74) + 1;
    if (*arg_4 > arg_0->unk_00)
        *arg_4 = arg_0->unk_00;
    if (0.0f != arg_0->unk_30[3] || arg_0->unk_70 <= arg_0->unk_78)
    {
        if (*arg_4 > arg_0->unk_D0)
            arg_0->unk_D0 = *arg_4;
        *arg_4 = arg_0->unk_D0;
        *arg_8 = 0;
    }
    else
    {
        *arg_8 = 0;
        *arg_8 += (RwInt32)((arg_0->unk_70 - arg_0->unk_78) / arg_0->unk_74);
        *arg_4 = arg_0->unk_D0 - *arg_8;
        if (*arg_4 < 0)
            *arg_4 = 0;
    }
}
