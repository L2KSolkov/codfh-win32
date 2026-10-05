// Split from unit_125490.cpp at 0x1279C0, where the image starts another object: its .rdata
// begins at 0x3DA80C with its own 16.666666, the unreferenced constant every game object
// starts its constants with, before sub_1279C0's literals (PLAN M7).

#include <math.h>
#include <string.h>
#include <stddef.h>
#include <xtl.h>
#include "game/render.h"
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/baengine.h"
#include "rw/badevice.h"
#include "rw/batextur.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"
#include "rw/rpworld.h"
#include "rw/rpcollis.h"
#include "rw/rpmaterial.h"
#include "rw/baim3d.h"
#include "game/worldrender.h"
#include "game/functions.h"
#include "game/gameloop.h"
#include "game/data.h"
#include "game/particles.h"
#include "game/fade.h"
#include "game/decals.h"
#include "game/clones.h"
#include "types/type_4E1B70.h"
#include "types/type_4B8EF0.h"
#include "types/type_3DAFC8.h"
#include "types/type_3D3548.h"
#include "types/type_3D96F0.h"
#include "types/type_4E5D30.h"
#include "types/type_10F710.h"
#include "types/RenderTrigger.h"
#include "types/animkey.h"
#include "types/type_92430.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DA80C
extern const RwReal flt_3DA80C = 16.666666f;

// match: ?flt_3DA80C@@3MB @ 0x003DA80C


// match: ?sub_1279C0@@YAXPAURwV3d@@00MMHH@Z @ 0x001279C0
// match: __real@c3160000 @ 0x003DA810
// match: __real@c37f0000 @ 0x003DA814
// match: __real@3f441893 @ 0x003DA818
// Adds a shadow of the kind arg_14 (its texture named in off_429BDC) under
// the point arg_0, cast along arg_4 (arg_8 its up), arg_C by arg_10 across:
// finds where it lands in the sections' collision worlds, gathers the
// triangles there (not again for arg_18), and adds those facing the cast
// to the kind's buffer, textured through the shadow's matrix and fading
// out with distance from the camera.
void sub_1279C0(RwV3d *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal arg_C, RwReal arg_10,
                RwInt32 arg_14, RwInt32 arg_18)
{
    RwV3d var_C;
    type_4CF5D0 *var_10;
    RwTexture *var_14;
    RwReal var_1C;
    type_91F40 var_48;
    RwLine var_60;
    RwInt32 var_64;
    type_4E5D30 *var_68;
    RwMatrix var_C0;
    RwMatrix var_100;
    RwReal var_104;
    RwBBox var_11C;
    RwReal var_120;
    RwReal var_124;
    RwReal var_128;
    RwInt32 var_12C;
    RwV3d *var_130;
    RwV3d *var_134;
    RwV3d *var_138;
    RwIm3DVertex *var_13C;
    RwReal var_140;
    RwReal var_144;
    RwV3d var_150;

    if (arg_18 && dword_4B25B8 == 150)
    {
        return;
    }
    var_C = *arg_0;
    sub_1414C0(&var_C, &var_C, &((RwCamera *)dword_4E5C74)->viewMatrix);
    if (var_C.z < 0.0f || var_C.z > flt_429BD0)
    {
        return;
    }
    var_10 = &dword_4CF5D0[arg_14];
    if (!var_10->unk_00)
    {
        var_10->unk_00 = (RwIm3DVertex *)RwMalloc(350 * 3 * sizeof(RwIm3DVertex), 0x34250);  // a memory hint; not an address
        var_10->unk_04 = 0;
    }
    if (var_10->unk_04 >= 350)
    {
        return;
    }
    if (!var_10->unk_08)
    {
        var_14 = RwTexDictionaryFindNamedTexture(dict, off_429BDC[arg_14]);
        if (var_14)
        {
            RwTextureSetFilterMode(var_14, rwFILTERLINEAR);
            var_10->unk_08 = var_14->raster;
        }
    }
    var_1C = arg_C > arg_10 ? arg_C : arg_10;
    RwV3dNormalize(arg_4, arg_4);
    var_48.unk_00 = 0;
    var_60.start = *arg_0;
    var_60.end = *arg_0;
    var_60.end.x += arg_4->x * 1000.0f;
    var_60.end.y += arg_4->y * 1000.0f;
    var_60.end.z += arg_4->z * 1000.0f;
    for (var_64 = 0; var_64 < 4; var_64++)
    {
        var_68 = &dword_4E5D30[var_64];
        if (var_68->get_unk_00() && var_68->get_unk_28())
        {
            sub_91F40(var_68->get_unk_28(), &var_60, &var_48, 1, 0x10000, 1);
            if (var_48.unk_00)
            {
                break;
            }
        }
    }
    if (!var_48.unk_00)
    {
        return;
    }
    memset(&var_C0, 0, sizeof(RwMatrix));
    memset(&var_100, 0, sizeof(RwMatrix));
    RwMatrixSetIdentityMacro(&var_C0);
    RwMatrixSetIdentityMacro(&var_100);
    var_C0.up = *arg_4;
    var_C0.up.y *= -1.0f;
    var_C0.at = *arg_8;
    RwV3dCrossProductMacro(&var_C0.right, &var_C0.up, &var_C0.at);
    RwV3dNormalize(&var_C0.up, &var_C0.up);
    RwV3dNormalize(&var_C0.right, &var_C0.right);
    RwV3dCrossProductMacro(&var_C0.at, &var_C0.up, &var_C0.right);
    var_C0.pos = var_48.unk_08;
    RwMatrixUpdate(&var_C0);
    RwMatrixInvert(&var_100, &var_C0);
    var_104 = RwV3dDotProductMacro(arg_0, arg_4);
    if (!arg_18)
    {
        var_1C *= flt_429BD8;
        var_11C.sup.x = var_48.unk_08.x + var_1C;
        var_11C.sup.y = var_48.unk_08.y + var_1C;
        var_11C.sup.z = var_48.unk_08.z + var_1C;
        var_11C.inf.x = var_48.unk_08.x - var_1C;
        var_11C.inf.y = var_48.unk_08.y - var_1C;
        var_11C.inf.z = var_48.unk_08.z - var_1C;
        sub_1283E0(&var_11C);
    }
    var_120 = flt_429BD0 * 0.5f;
    var_124 = 255.0f;
    if (var_C.z > var_120)
    {
        var_128 = (var_C.z - var_120) / var_120;
        var_124 = -255.0f * var_128 + 255.0f;
    }
    for (var_12C = 150; var_12C < dword_4B25B8; var_12C++)
    {
        var_130 = &dword_4B25C0[var_12C * 3];
        var_134 = &dword_4B25C0[var_12C * 3 + 1];
        var_138 = &dword_4B25C0[var_12C * 3 + 2];
        if (RwV3dDotProductMacro(var_130, arg_4) - var_104 < -150.0f)
        {
            continue;
        }
        if (RwV3dDotProductMacro(var_134, arg_4) - var_104 < -150.0f)
        {
            continue;
        }
        if (RwV3dDotProductMacro(var_138, arg_4) - var_104 < -150.0f)
        {
            continue;
        }
        if (var_10->unk_04 < 350)
        {
            var_13C = &var_10->unk_00[var_10->unk_04 * 3];
            var_140 = 1.0f / arg_C;
            var_144 = 1.0f / arg_10;
            RwIm3DVertexSetPos(var_13C, var_130->x, flt_429BD4 + var_130->y, var_130->z);
            RwIm3DVertexSetRGBA(var_13C, 128, 128, 128, (RwUInt8)var_124);
            sub_1414C0(&var_150, var_130, &var_100);
            RwIm3DVertexSetU(var_13C, var_150.x * var_140 + 0.5f);
            RwIm3DVertexSetV(var_13C, var_150.z * var_144 + 0.5f);
            var_13C++;
            RwIm3DVertexSetPos(var_13C, var_134->x, flt_429BD4 + var_134->y, var_134->z);
            RwIm3DVertexSetRGBA(var_13C, 128, 128, 128, (RwUInt8)var_124);
            sub_1414C0(&var_150, var_134, &var_100);
            RwIm3DVertexSetU(var_13C, var_150.x * var_140 + 0.5f);
            RwIm3DVertexSetV(var_13C, var_150.z * var_144 + 0.5f);
            var_13C++;
            RwIm3DVertexSetPos(var_13C, var_138->x, flt_429BD4 + var_138->y, var_138->z);
            RwIm3DVertexSetRGBA(var_13C, 128, 128, 128, (RwUInt8)var_124);
            sub_1414C0(&var_150, var_138, &var_100);
            RwIm3DVertexSetU(var_13C, var_150.x * var_140 + 0.5f);
            RwIm3DVertexSetV(var_13C, var_150.z * var_144 + 0.5f);
            var_10->unk_04++;
        }
    }
}
// match: ?sub_1283E0@@YAXPAURwBBox@@@Z @ 0x001283E0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Gathers the collision triangles in the box arg_0 that face up enough into
// dword_4B25C0 (from 150, up to 350).
void sub_1283E0(RwBBox *arg_0)
{
    RwV3d *var_2C4;
    RpTriangle *var_2C0;
    RwV3d *var_2BC;
    RwV3d *l2B8;
    RwUInt16 var_2B4;
    RwV3d l2B0;
    RwReal local_2A4;
    RwUInt32 local_2A0;
    RwUInt16 var_29C;
    RwUInt16 slot_298;
    RwUInt16 local_294;
    RpCollTree *var290;
    RpTriangle *l28C;
    RpCollSectorBBoxIt var288;
    RwUInt16 *var_13C;
    RwV3d *l138;
    RpWorldSector *var_134;
    RpSectorBBoxIt loc130;
    type_4E5D30 *var_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    dword_4B25B8 = 150;
    bp_4 = dword_4B25B8 * 3;
    for (bp_8 = 0; bp_8 < 4; bp_8++)
    {
        var_C = &dword_4E5D30[bp_8];
        if (var_C->get_unk_00() && var_C->get_unk_28())
        {
            RpSectorBBoxItInit(&loc130, var_C->get_unk_28(), arg_0);
            while (!RpSectorBBoxItFinished(&loc130))
            {
                var_134 = RpSectorBBoxItFindNextWorldSector(&loc130);
                l28C = var_134->triangles;
                l138 = var_134->vertices;
                var290 = RpCollisionWorldSectorGetCollTree(var_134);
                if (!l28C || !l138 || !var290)
                {
                    continue;
                }
                var_13C = RpCollTreeGetEntryMap(var290);
                RpCollSectorBBoxItInit(&var288, var290, arg_0, arg_0);
                while (!RpCollSectorBBoxItFinished(&var288))
                {
                    RpCollSectorBBoxItFindNextEntries(&var288, &var_29C, &local_294, &local_2A0);
                    for (slot_298 = var_29C; slot_298 < var_29C + local_294; slot_298++)
                    {
                        var_2B4 = var_13C[slot_298];
                        var_2C0 = &l28C[var_2B4];
                        var_2C4 = &l138[var_2C0->vertIndex[0]];
                        l2B8 = &l138[var_2C0->vertIndex[1]];
                        var_2BC = &l138[var_2C0->vertIndex[2]];
                        sub_16E860(var_2C4, l2B8, var_2BC, &l2B0);
                        local_2A4 = RwV3dDotProductMacro(&l2B0, &dword_429D90);
                        if (l2B0.y > 0.0f && local_2A4 > 0.766f)
                        {
                            if (!local_2A0 || RtIntersectionBBoxTriangle(arg_0, var_2C4, l2B8, var_2BC))
                            {
                                dword_4B25C0[bp_4] = *var_2C4;
                                dword_4B25C0[bp_4 + 1] = *l2B8;
                                dword_4B25C0[bp_4 + 2] = *var_2BC;
                                bp_4 += 3;
                                dword_4B25B8++;
                                if (dword_4B25B8 >= 350)
                                {
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
// match: ?sub_128770@@YAXXZ @ 0x00128770
// Frees the shadows' triangle buffers.
void sub_128770()
{
    RwInt32 var_4;

    for (var_4 = 0; var_4 < 10; var_4++)
    {
        if (dword_4CF5D0[var_4].unk_00)
        {
            RwFree(dword_4CF5D0[var_4].unk_00);
            dword_4CF5D0[var_4].unk_00 = 0;
            dword_4CF5D0[var_4].unk_04 = 0;
            dword_4CF5D0[var_4].unk_08 = 0;
        }
    }
}
// match: ?sub_1287F0@@YAXXZ @ 0x001287F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the shadows gathered this frame, kind by kind, and empties them.
void sub_1287F0()
{
    type_4CF5D0 *var_8;
    RwInt32 l4;

    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)1);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void *)rwTEXTUREADDRESSCLAMP);
    for (l4 = 0; l4 < 10; l4++)
    {
        var_8 = &dword_4CF5D0[l4];
        if (var_8->unk_04 && RwIm3DTransform(var_8->unk_00, var_8->unk_04 * 3, 0, rwIM3D_VERTEXUV))
        {
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void *)var_8->unk_08);
            RwIm3DRenderPrimitive(rwPRIMTYPETRILIST);
            RwIm3DEnd();
            var_8->unk_04 = 0;
        }
    }
}
// match: ?sub_1288D0@@YAXPAURwCamera@@I@Z @ 0x001288D0
// The motion blur's draw, gone but for its strength's floor.
void sub_1288D0(RwCamera *arg_0, RwUInt32 arg_4)
{
    if (arg_4 > 0)
    {
        dword_4F2B64 = 0.8f;
    }
}
// match: ?sub_1288F0@@YAXPAURwCamera@@@Z @ 0x001288F0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Sets up the screen quad for the camera arg_0's raster (its size and
// texel centres); left unset, its raster found missing.
void sub_1288F0(RwCamera *arg_0)
{
    RwReal var_2C;
    RwReal var_28;
    RwReal ebp_24;
    RwRaster *var_20;
    RwReal l1C;
    RwUInt32 m_18;
    RwReal ebp_14;
    RwUInt32 lv_10;
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    if (!arg_0)
    {
        return;
    }
    bp_4 = (RwReal)arg_0->frameBuffer->width;
    var_C = (RwReal)arg_0->frameBuffer->height;
    var_20 = 0;
    if (!var_20)
    {
        return;
    }
    lv_10 = var_20->width;
    m_18 = var_20->height;
    var_2C = (bp_4 + 0.5f) / (RwReal)lv_10;
    l1C = (var_C + 0.5f) / (RwReal)m_18;
    ebp_14 = 0.5f / (RwReal)lv_10;
    bp_8 = 0.5f / (RwReal)m_18;
    var_28 = (RwReal)arg_0->frameBuffer->width;
    ebp_24 = (RwReal)arg_0->frameBuffer->height;
    RwIm2DVertexSetScreenX(&dword_4CF548[0], 0.0f);
    RwIm2DVertexSetScreenY(&dword_4CF548[0], 0.0f);
    RwIm2DVertexSetScreenZ(&dword_4CF548[0], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&dword_4CF548[0], 1.0f / RwCameraGetNearClipPlane(arg_0));
    RwIm2DVertexSetU(&dword_4CF548[0], ebp_14, 0);
    RwIm2DVertexSetV(&dword_4CF548[0], bp_8, 0);
    dword_4CF548[0].emissiveColor = 0xFFFFFFFF;
    RwIm2DVertexSetScreenX(&dword_4CF548[1], 0.0f);
    RwIm2DVertexSetScreenY(&dword_4CF548[1], ebp_24);
    RwIm2DVertexSetScreenZ(&dword_4CF548[1], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&dword_4CF548[1], 1.0f / RwCameraGetNearClipPlane(arg_0));
    RwIm2DVertexSetU(&dword_4CF548[1], ebp_14, 0);
    RwIm2DVertexSetV(&dword_4CF548[1], l1C, 0);
    dword_4CF548[1].emissiveColor = 0xFFFFFFFF;
    RwIm2DVertexSetScreenX(&dword_4CF548[2], var_28);
    RwIm2DVertexSetScreenY(&dword_4CF548[2], ebp_24);
    RwIm2DVertexSetScreenZ(&dword_4CF548[2], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&dword_4CF548[2], 1.0f / RwCameraGetNearClipPlane(arg_0));
    RwIm2DVertexSetU(&dword_4CF548[2], var_2C, 0);
    RwIm2DVertexSetV(&dword_4CF548[2], l1C, 0);
    dword_4CF548[2].emissiveColor = 0xFFFFFFFF;
    RwIm2DVertexSetScreenX(&dword_4CF548[3], var_28);
    RwIm2DVertexSetScreenY(&dword_4CF548[3], 0.0f);
    RwIm2DVertexSetScreenZ(&dword_4CF548[3], RwIm2DGetNearScreenZ());
    RwIm2DVertexSetRecipCameraZ(&dword_4CF548[3], 1.0f / RwCameraGetNearClipPlane(arg_0));
    RwIm2DVertexSetU(&dword_4CF548[3], var_2C, 0);
    RwIm2DVertexSetV(&dword_4CF548[3], bp_8, 0);
    dword_4CF548[3].emissiveColor = 0xFFFFFFFF;
}
// match: ?sub_128B00@@YAXPAURwCamera@@@Z @ 0x00128B00
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Runs the motion blur down by the frame's time and draws it (held while
// dword_4CF788 is set).
void sub_128B00(RwCamera *arg_0)
{
    RwReal var_C;
    RwReal bp_8;
    RwReal bp_4;

    bp_4 = deltaTime;
    if (dword_4CF774 > 300.0f)
    {
        dword_4CF774 = 300.0f;
    }
    if (dword_4CF774 != 0.0f)
    {
        if (dword_4CF774 < dword_4CF78C)
        {
            dword_4CF48C = (RwInt32)(RwReal)floor(
                                         var_C = dword_4CF48C
                                                 - (bp_8 = dword_4CF48C / dword_4CF774) * bp_4);
        }
        dword_4CF774 -= bp_4;
        if (dword_4CF774 <= 0.0f)
        {
            dword_4CF774 = 0.0f;
            dword_4CF48C = 0;
        }
    }
    else
    {
        dword_4CF48C = 0;
    }
    if ((dword_4CF48C || dword_4CF788) && RwCameraBeginUpdate(arg_0))
    {
        sub_1288D0(arg_0, dword_4CF48C & 0xFF);
        RwCameraEndUpdate(arg_0);
    }
}
// match: ?sub_128C20@@YAXHMM@Z @ 0x00128C20
// Sets the motion blur: its strength arg_0, how long it lasts arg_4 (not
// shortened; nothing without a fall arg_8), and how long it falls.
void sub_128C20(RwInt32 arg_0, RwReal arg_4, RwReal arg_8)
{
    if (arg_0 < 0)
    {
        arg_0 = 0;
    }
    if (arg_4 > dword_4CF774)
    {
        if (arg_8 <= 0.0f)
        {
            arg_4 = 0.0f;
        }
        dword_4CF48C = arg_0;
        dword_4CF774 = arg_4;
        dword_4CF78C = arg_8;
    }
}
// match: ?sub_128C80@@YAXMM@Z @ 0x00128C80
// Fades the fog distance to arg_0 over arg_4 seconds (at once without).
void sub_128C80(RwReal arg_0, RwReal arg_4)
{
    dword_4CF4D8 = arg_0;
    if (arg_4 <= 0.0f)
    {
        dword_4CF514 = 0.0f;
        *(RwReal *)&dword_4CF4F0 = arg_0;
    }
    else
    {
        dword_4CF514 = arg_4;
        dword_4CF758 = (arg_0 - *(RwReal *)&dword_4CF4F0) / arg_4;
    }
}
// match: ?sub_128CD0@@YAXMM@Z @ 0x00128CD0
// Fades the far clip to arg_0 over arg_4 seconds (at once without).
void sub_128CD0(RwReal arg_0, RwReal arg_4)
{
    dword_4CF4F8 = arg_0;
    if (arg_4 <= 0.0f)
    {
        dword_4CF794 = 0.0f;
        flt_4CF458 = farClip = arg_0;
    }
    else
    {
        dword_4CF794 = arg_4;
        dword_4CF470 = (arg_0 - farClip) / arg_4;
    }
}
// match: ?sub_128D30@@YAXXZ @ 0x00128D30
// Runs the fog distance's fade by the frame's time.
void sub_128D30()
{
    RwReal var_4;

    var_4 = deltaTime;
    if (dword_4CF514 > 0.0001f)
    {
        if (dword_4CF514 - var_4 > 0.0f)
        {
            *(RwReal *)&dword_4CF4F0 += dword_4CF758 * var_4;
            dword_4CF514 -= var_4;
        }
        else
        {
            *(RwReal *)&dword_4CF4F0 = dword_4CF4D8;
            dword_4CF514 = 0.0f;
            dword_4CF758 = 0.0f;
        }
    }
}
// match: ?sub_128DB0@@YAXXZ @ 0x00128DB0
// Runs the far clip's fade by the frame's time.
void sub_128DB0()
{
    RwReal var_4;

    var_4 = deltaTime;
    if (dword_4CF794 > 0.0001f)
    {
        if (dword_4CF794 - var_4 > 0.0f)
        {
            farClip += dword_4CF470 * var_4;
            flt_4CF458 = farClip;
            dword_4CF794 -= var_4;
        }
        else
        {
            flt_4CF458 = farClip = dword_4CF4F8;
            dword_4CF794 = 0.0f;
            dword_4CF470 = 0.0f;
        }
    }
}
// match: ?sub_128E50@@YAXPAURpClump@@H@Z @ 0x00128E50
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the clump arg_0's atomics that are to be drawn, straight through
// RenderWare's default callback.
void sub_128E50(RpClump *arg_0, RwInt32 arg_4)
{
    RpAtomic *var_C;
    RwLLLink *bp_8;
    RwLLLink *bp_4;

    bp_4 = arg_0->atomicList.link.next;
    bp_8 = &arg_0->atomicList.link;
    while (bp_4 != bp_8)
    {
        var_C = (RpAtomic *)((RwUInt8 *)bp_4 - offsetof(RpAtomic, inClumpLink));
        if (RpAtomicGetFlags(var_C) & rpATOMICRENDER)
        {
            RwFrameGetLTM(RpAtomicGetFrame(var_C));
            AtomicDefaultRenderCallBack(var_C);
        }
        bp_4 = bp_4->next;
    }
}
// match: ?sub_128EB0@type_128EB0@@QAEXPAURpAtomic@@M@Z @ 0x00128EB0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void type_128EB0::sub_128EB0(RpAtomic *arg_0, RwReal arg_4)
{
    type_128EB0_04 *var_14;
    type_128EB0_04 *lv_10;
    RpAtomicCallBackRender var_C;
    RwInt32 bp_8;
    type_3D3548 *bp_4;

    bp_8 = 0;
    bp_4 = sub_FB960(arg_0);
    if (bp_4)
    {
        bp_8 = bp_4->unk_29C;
    }
    if (unk_00 >= 400)
    {
        var_C = arg_0->renderCallBack;
        if (var_C != sub_D2B70)
        {
            sub_122820(arg_0, 0, 0);
        }
        RpAtomicRender(arg_0);
        return;
    }
    lv_10 = &unk_04[unk_00++];
    lv_10->unk_00 = arg_4;
    lv_10->unk_04 = arg_0;
    lv_10->unk_08 = 0;
    lv_10->unk_0C = 0;
    var_14 = unk_1904[bp_8];
    if (!var_14)
    {
        unk_1904[bp_8] = lv_10;
    }
    else
    {
        sub_128FA0(var_14, lv_10);
    }
}
// match: ?sub_128FA0@type_128EB0@@QAEXPAUtype_128EB0_04@@0@Z @ 0x00128FA0
// Puts the node arg_4 in the subtree arg_0, nearer to the left.
void type_128EB0::sub_128FA0(type_128EB0_04 *arg_0, type_128EB0_04 *arg_4)
{
    if (arg_4->unk_00 > arg_0->unk_00)
    {
        if (arg_0->unk_08)
        {
            sub_128FA0(arg_0->unk_08, arg_4);
        }
        else
        {
            arg_0->unk_08 = arg_4;
        }
    }
    else
    {
        if (arg_0->unk_0C)
        {
            sub_128FA0(arg_0->unk_0C, arg_4);
        }
        else
        {
            arg_0->unk_0C = arg_4;
        }
    }
}
// match: ?sub_129010@type_128EB0@@QAEXPAUtype_128EB0_04@@@Z @ 0x00129010
void type_128EB0::sub_129010(type_128EB0_04 *arg_0)
{
    RpAtomicCallBackRender var_4;

    if (arg_0)
    {
        if (arg_0->unk_08)
        {
            sub_129010(arg_0->unk_08);
        }
        if (arg_0->unk_04)
        {
            var_4 = arg_0->unk_04->renderCallBack;
            if (var_4 != sub_D2B70)
            {
                sub_122820(arg_0->unk_04, 0, 0);
            }
            RpAtomicRender(arg_0->unk_04);
        }
        if (arg_0->unk_0C)
        {
            sub_129010(arg_0->unk_0C);
        }
    }
}
// match: ?sub_1290A0@@YAPAURpWorldSector@@PAU1@PAX@Z @ 0x001290A0
// The world pass's sector callback: draws the sector if the PVS shows it
// (when asked to check).
RpWorldSector *sub_1290A0(RpWorldSector *arg_0, void *arg_4)
{
    type_122D90 *var_4;

    var_4 = (type_122D90 *)arg_4;
    if (dword_4CF518)
    {
        if (var_4->unk_08)
        {
            if (RpPVSWorldSectorVisible(arg_0))
            {
                RpWorldSectorRender(arg_0);
            }
        }
        else
        {
            RpWorldSectorRender(arg_0);
        }
    }
    return arg_0;
}
// match: ?sub_1290F0@@YAXPAURwCamera@@PAURpWorld@@H@Z @ 0x001290F0
// Draws the world arg_4's sectors in view (the PVS checked when arg_8 is
// set), if the world is drawn at all.
void sub_1290F0(RwCamera *arg_0, RpWorld *arg_4, RwInt32 arg_8)
{
    type_122D90 var_C;

    var_C.unk_08 = arg_8;
    var_C.unk_00 = arg_0;
    var_C.unk_04 = (RwInt32)arg_4;
    if (dword_4CF518 || dword_4CF5B8)
    {
        RwCameraForAllSectorsInFrustum(arg_0, sub_1290A0, &var_C);
    }
}
// match: ?sub_129140@@YAXPAURwCamera@@PAURpWorld@@HHH@Z @ 0x00129140
// Draws the world arg_4 in a pass of its own (the PVS by arg_8, the
// blending by arg_C, the alpha test by arg_10).
void sub_129140(RwCamera *arg_0, RpWorld *arg_4, RwInt32 arg_8, RwInt32 arg_C,
                RwInt32 arg_10)
{
    if (arg_0 && sub_126A30(arg_0, arg_4, 0, 0.0f, arg_C))
    {
        sub_1291A0(arg_C, arg_10);
        sub_1290F0(arg_0, arg_4, arg_8);
        sub_1291E0();
        sub_126D00(arg_0, arg_4);
    }
}
// match: ?sub_1291A0@@YAXHH@Z @ 0x001291A0
// Sets the alpha test for a pass with blending (arg_0), without the depth
// buffer's writes for the second (arg_4 1).
void sub_1291A0(RwInt32 arg_0, RwInt32 arg_4)
{
    if (arg_0)
    {
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void *)rwALPHATESTFUNCTIONGREATER);
        RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)dword_4F3080);
        if (arg_4 == 1)
        {
            RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)0);
        }
    }
}
// match: ?sub_1291E0@@YAXXZ @ 0x001291E0
void sub_1291E0()
{
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)1);
}
