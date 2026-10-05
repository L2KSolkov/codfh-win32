// The debug text: strings queued with their screen positions in a buffer
// (sub_16BB00) and drawn in one go with RenderWare's Atari charset
// (sub_16BBA0, through sub_16BE20, a trimmed copy of the toolkit's
// CharsetProcessString); and the debug printf (sub_16C220).

#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/badevice.h"
#include "rw/baengine.h"
#include "rw/baraster.h"
#include "rw/rtcharse.h"
#include "game/debugtext.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

// Its data definitions (PLAN M5), in the image's address order.
// 0x00429EA0
RwRGBA foreGround = { 255, 255, 255, 128 };
// 0x00429EA4
RwRGBA backGround = { 0, 0, 0, 128 };
// 0x004E2290
RwInt32 dword_4E2290;
// 0x004E2294
RwUInt8 *dword_4E2294;
// 0x004E2298
RwUInt8 *dword_4E2298;
// 0x004E229C
RwUInt32 dword_4E229C;
// 0x004E22A0
RwRaster *charSet;
// End of its data definitions.




// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?foreGround@@3URwRGBA@@A @ 0x00429EA0
// match: ?backGround@@3URwRGBA@@A @ 0x00429EA4

// match: ?sub_16BA60@@YAXI@Z @ 0x0016BA60

// Sets it up with a buffer of arg_0 bytes.
void sub_16BA60(RwUInt32 arg_0)
{
    dword_4E2294 = (RwUInt8 *)RwMalloc(arg_0, 0x44250); // not an address: a memory hint
    dword_4E2298 = dword_4E2294;
    dword_4E2290 = 0;
    dword_4E229C = arg_0;
    charSet = RtCharsetCreate(&foreGround, &backGround);
}

// match: ?sub_16BAC0@@YAXXZ @ 0x0016BAC0
void sub_16BAC0()
{
    RtCharsetDestroy(charSet);
    if (dword_4E2294)
    {
        RwFree(dword_4E2294);
        dword_4E2294 = 0;
    }
}

// match: ?sub_16BB00@@YA_NPBDHH@Z @ 0x0016BB00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Queues the string arg_0 at (arg_4, arg_8); false when the buffer is full.
bool sub_16BB00(const RwChar *arg_0, RwInt32 arg_4, RwInt32 arg_8)
{
    type_16BB00 *var_8;
    RwInt32 l4;

    l4 = (strlen(arg_0) + 0xB) & ~3;
    if (dword_4E2298 - dword_4E2294 + l4 < dword_4E229C)
    {
        var_8 = (type_16BB00 *)dword_4E2298;
        dword_4E2298 += l4;
        var_8->unk_00 = arg_4;
        var_8->unk_02 = arg_8;
        var_8->unk_04 = (RwUInt16)strlen(arg_0);
        strcpy(var_8->unk_06, arg_0);
        dword_4E2290++;
        return true;
    }
    return false;
}

// match: ?sub_16BBA0@@YAXXZ @ 0x0016BBA0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the queued strings (no depth test, alpha blended, point filtered,
// no culling or fog) and empties the queue.
void sub_16BBA0()
{
    RwInt32 var_AC0;
    const RwChar *bp_ABC;
    void *lv_AB8;
    void *var_AB4;
    type_16BB00 *vAB0;
    void *var_AAC;
    void *fp_AA8;
    void *stk_AA4;
    RwIm2DVertex stk_AA0[0x60];
    RwUInt8 *var_20;
    void *l1C;
    RwInt32 m_18;
    RwInt32 ebp_14;
    RwInt32 lv_10;
    RwInt32 var_C;
    void *bp_8;
    void *bp_4;

    vAB0 = (type_16BB00 *)dword_4E2294;
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &var_AAC);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &fp_AA8);
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &lv_AB8);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &stk_AA4);
    RwRenderStateGet(rwRENDERSTATETEXTURERASTER, &bp_4);
    RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &l1C);
    RwRenderStateGet(rwRENDERSTATECULLMODE, &bp_8);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &var_AB4);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERNEAREST);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)charSet);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)FALSE);
    var_20 = dword_4E2294;
    for (m_18 = 0; m_18 < dword_4E2290; m_18++)
    {
        var_AC0 = (vAB0->unk_04 + 0xB) & ~3;
        lv_10 = vAB0->unk_00;
        var_C = vAB0->unk_02;
        bp_ABC = vAB0->unk_06;
        while (strlen(bp_ABC))
        {
            ebp_14 = sub_16BE20(stk_AA0, 0x60, &bp_ABC, &lv_10, &var_C);
            if (ebp_14)
                RwIm2DRenderPrimitive(rwPRIMTYPETRILIST, stk_AA0, ebp_14);
        }
        var_20 += var_AC0;
        vAB0 = (type_16BB00 *)var_20;
    }
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, var_AAC);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, fp_AA8);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, lv_AB8);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, stk_AA4);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, l1C);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, bp_4);
    RwRenderStateSet(rwRENDERSTATECULLMODE, bp_8);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, var_AB4);
    dword_4E2290 = 0;
    dword_4E2298 = dword_4E2294;
}

// match: ?sub_16BE20@@YAHPAURwD3D8Vertex@@HPAPBDPAH2@Z @ 0x0016BE20
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Fills arg_0 (room for arg_4 vertices) with the glyphs of *arg_8 from the
// pen (*arg_C, *arg_10), six vertices each, skipping those off screen;
// advances the string and the pen, stopping when the buffer is full.
// Returns the vertices written. The locals are CharsetProcessString's:
// bp_4 chHeight, stk_6C chWidth, bp_8 and var_74 the scales, lv_54 and
// var_64 the half-texel offsets, m_18 rectQuad, q48 rectUV, local_34
// desc, local_38 and var_78 the screen's size, stk_58 the vertices written,
// stk_60 the string.
RwInt32 sub_16BE20(RwIm2DVertex *arg_0, RwInt32 arg_4, const RwChar **arg_8, RwInt32 *arg_C, RwInt32 *arg_10)
{
    RwInt32 local_7C;
    RwInt32 var_78;
    RwReal var_74;
    RwCamera *var70;
    RwInt32 stk_6C;
    RwReal q68;
    RwReal var_64;
    const RwChar *stk_60;
    RwReal y5C;
    RwInt32 stk_58;
    RwReal lv_54;
    RwInt32 ebp_50;
    RwRaster *var4C;
    RwRect q48;
    RwInt32 local_38;
    RtCharsetDesc local_34;
    RwRect m_18;
    RwReal bp_8;
    RwInt32 bp_4;

    stk_58 = 0;
    _rtCharsetAtariFontGet(&local_34, &local_38);
    bp_4 = RwRasterGetHeight(charSet);
    stk_6C = RwRasterGetWidth(charSet);
    bp_8 = 1 / ((RwReal)bp_4);
    var_74 = 1 / ((RwReal)stk_6C);
    lv_54 = (1.0f / ((RwReal)stk_6C)) / 2.0f;
    var_64 = (1.0f / ((RwReal)bp_4)) / 2.0f;
    var70 = RwCameraGetCurrentCamera();
    var4C = RwCameraGetRaster(var70);
    local_38 = RwRasterGetHeight(var4C);
    var_78 = RwRasterGetWidth(var4C);
    q68 = RwIm2DGetNearScreenZ();
    y5C = (RwReal)1 / RwCameraGetNearClipPlane(var70);
    stk_60 = *arg_8;
    while (*stk_60)
    {
        if (stk_58 + 6 > arg_4)
        {
            *arg_8 = stk_60;
            return stk_58;
        }
        m_18.x = *arg_C;
        m_18.y = *arg_10;
        m_18.w = m_18.x + local_34.width;
        m_18.h = *arg_10 + local_34.height;
        if (m_18.y < local_38 && m_18.h > 0 && m_18.x < var_78 && m_18.w > 0)
        {
            ebp_50 = *stk_60 - 0x20;
            q48.y = ebp_50 / local_34.tilewidth;
            q48.x = ebp_50 - q48.y * local_34.tilewidth;
            q48.x *= local_34.width_internal;
            q48.y *= local_34.height_internal;
            q48.w = q48.x + local_34.width;
            q48.h = q48.y + local_34.height;
            RwIm2DVertexSetU(&arg_0[stk_58 + 0], var_74 * (q48.x) + lv_54, 1);
            RwIm2DVertexSetV(&arg_0[stk_58 + 0], bp_8 * (q48.y) + var_64, 1);
            RwIm2DVertexSetU(&arg_0[stk_58 + 1], var_74 * (q48.w) + lv_54, 1);
            RwIm2DVertexSetV(&arg_0[stk_58 + 1], bp_8 * (q48.y) + var_64, 1);
            RwIm2DVertexSetU(&arg_0[stk_58 + 2], var_74 * (q48.w) + lv_54, 1);
            RwIm2DVertexSetV(&arg_0[stk_58 + 2], bp_8 * (q48.h) + var_64, 1);
            RwIm2DVertexSetU(&arg_0[stk_58 + 3], var_74 * (q48.x) + lv_54, 1);
            RwIm2DVertexSetV(&arg_0[stk_58 + 3], bp_8 * (q48.y) + var_64, 1);
            RwIm2DVertexSetU(&arg_0[stk_58 + 4], var_74 * (q48.w) + lv_54, 1);
            RwIm2DVertexSetV(&arg_0[stk_58 + 4], bp_8 * (q48.h) + var_64, 1);
            RwIm2DVertexSetU(&arg_0[stk_58 + 5], var_74 * (q48.x) + lv_54, 1);
            RwIm2DVertexSetV(&arg_0[stk_58 + 5], bp_8 * (q48.h) + var_64, 1);
            RwIm2DVertexSetScreenX(&arg_0[stk_58 + 0], (RwReal)(m_18.x));
            RwIm2DVertexSetScreenY(&arg_0[stk_58 + 0], (RwReal)(m_18.y));
            RwIm2DVertexSetScreenX(&arg_0[stk_58 + 1], (RwReal)(m_18.w));
            RwIm2DVertexSetScreenY(&arg_0[stk_58 + 1], (RwReal)(m_18.y));
            RwIm2DVertexSetScreenX(&arg_0[stk_58 + 2], (RwReal)(m_18.w));
            RwIm2DVertexSetScreenY(&arg_0[stk_58 + 2], (RwReal)(m_18.h));
            RwIm2DVertexSetScreenX(&arg_0[stk_58 + 3], (RwReal)(m_18.x));
            RwIm2DVertexSetScreenY(&arg_0[stk_58 + 3], (RwReal)(m_18.y));
            RwIm2DVertexSetScreenX(&arg_0[stk_58 + 4], (RwReal)(m_18.w));
            RwIm2DVertexSetScreenY(&arg_0[stk_58 + 4], (RwReal)(m_18.h));
            RwIm2DVertexSetScreenX(&arg_0[stk_58 + 5], (RwReal)(m_18.x));
            RwIm2DVertexSetScreenY(&arg_0[stk_58 + 5], (RwReal)(m_18.h));
            for (local_7C = 0; local_7C < 6; local_7C++)
            {
                RwIm2DVertexSetRecipCameraZ(&arg_0[stk_58 + local_7C], y5C);
                RwIm2DVertexSetScreenZ(&arg_0[stk_58 + local_7C], q68);
                RwIm2DVertexSetIntRGBA(&arg_0[stk_58 + local_7C], 255, 255, 255, 255);
            }
            stk_58 += 6;
        }
        *arg_C += local_34.width;
        stk_60++;
    }
    *arg_8 = stk_60;
    return stk_58;
}

// match: ?sub_16C220@@YAXPBDZZ @ 0x0016C220
// The debug printf: formats into a buffer and prints it with a newline.
void sub_16C220(const RwChar *arg_0, ...)
{
    RwChar var_408[0x400];
    va_list var_4;

    va_start(var_4, arg_0);
    vsprintf(var_408, arg_0, var_4);
    va_end(var_4);
    printf("%s%s", var_408, "\n");
}
