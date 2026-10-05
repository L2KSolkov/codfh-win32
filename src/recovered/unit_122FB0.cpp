// The clones (game/clones.h): their clump and file, their lights and
// shaders, and the pass that draws them. The original file name is not in
// the image, so it is named for its start address.

#include <string.h>
#include <stdlib.h>
#include <xmmintrin.h>

#include "game/clones.h"
#include "rw/ostypes.h"
#include "rw/batypes.h"
#include "rw/bamatrix.h"
#include "rw/bavector.h"
#include "rw/baframe.h"
#include "rw/baengine.h"
#include "rw/badevice.h"
#include "rw/bastream.h"
#include "rw/babintex.h"
#include "rw/batextur.h"
#include "rw/rpatomic.h"
#include "rw/rplight.h"
#include "rw/rpmaterial.h"
#include "rw/rpmesh.h"
#include "rw/rpusrdat.h"
#include "rw/rwxbox.h"
#include "game/data.h"
#include "game/particles.h"
#include "game/gameloop.h"
#include "types/type_3D3548.h"
#include "types/type_4E5D30.h"
#include "types/RenderTrigger.h"
#include "types/animkey.h"

// Its data definitions (PLAN M5), in the image's address order.
// 0x003DA77C
extern const RwReal flt_3DA77C = 16.666666f;
// 0x003DA780
extern const RwReal flt_3DA780 = 16.666666f;
// 0x003DA784
extern const RwV3d stru_3DA784 = { 0.0f, 1.0f, 0.0f };
// 0x003DA790
extern const RwV3d stru_3DA790 = { 0.0f, 0.0f, 1.0f };
// 0x00429B7C
DWORD dword_429B7C[6] = { 0x20000000, 0x40320000, 0x40220001, 0x40420002, 0x40320003, 0xFFFFFFFF };
// 0x00429B94
DWORD dword_429B94[6] = { 0x20000000, 0x40320000, 0x40220001, 0x40420002, 0x40320003, 0xFFFFFFFF };
// 0x004CEA70
RwRGBAReal stru_4CEA70;
// 0x004CEA80
RwInt32 dword_4CEA80;
// 0x004CEA84
DWORD dword_4CEA84;
// 0x004CEA88
RwInt32 dword_4CEA88;
// 0x004CEA8C
RpAtomic *dword_4CEA8C;
// 0x004CEA90
RwInt32 dword_4CEA90;
// 0x004CEA94
RwRGBAReal stru_4CEA94;
// 0x004CEAA4
RwInt32 dword_4CEAA4;
// 0x004CEAA8
RpLight *dword_4CEAA8;
// 0x004CEAAC
RwInt32 dword_4CEAAC;
// 0x004CEAB0
RwUInt8 *dword_4CEAB0;
// 0x004CEAB4
RpClump *dword_4CEAB4;
// 0x004CEAB8
RwV3d dword_4CEAB8;
// 0x004CEAC4
RwInt32 dword_4CEAC4;
// 0x004CEAC8
RwRGBAReal dword_4CEAC8;
// 0x004CEAD8
RwInt32 dword_4CEAD8;
// 0x004CEAE0
RpAtomic *dword_4CEAE0[500];
// 0x004CF2B0
RwInt32 dword_4CF2B0;
// 0x004CF2B4
RwFrame *frame;
// 0x004CF2B8
DWORD vertexShader;
// 0x004CF2BC
RwInt32 dword_4CF2BC;
// 0x004CF2C0
RwMatrix stru_4CF2C0;
// 0x004CF300
RwInt32 dword_4CF300;
// 0x004CF304
RwInt32 dword_4CF304;
// 0x004CF308
RpLight *dword_4CF308;
// 0x004CF30C
RwInt32 dword_4CF30C;
// 0x004CF310
RwInt32 dword_4CF310;
// 0x004CF31C
RwInt32 dword_4CF31C;
// 0x004CF324
RwInt32 dword_4CF324;
// 0x004CF328
RwInt32 dword_4CF328;
// 0x004CF32C
RwInt32 dword_4CF32C;
// 0x004CF330
RwInt32 dword_4CF330;
// 0x004CF334
RwInt32 dword_4CF334;
// 0x004CF338
RwInt32 dword_4CF338;
// 0x004CF340
#ifdef CODFH_PLAIN
// (plain builds: the SSE matrix routines, XGMatrixMultiply, need 16-byte alignment, which
// only the image's placement gives it)
__declspec(align(16)) D3DMATRIX stru_4CF340 = { 0 };
#else
D3DMATRIX stru_4CF340;
#endif
// 0x004CF380
#ifdef CODFH_PLAIN
// (plain builds: the SSE matrix routines, XGMatrixMultiply, need 16-byte alignment, which
// only the image's placement gives it)
__declspec(align(16)) D3DMATRIX pM2 = { 0 };
#else
D3DMATRIX pM2;
#endif
// 0x004F309C
RwInt32 dword_4F309C;
// 0x004F30A0
RwInt32 dword_4F30A0;
// End of its data definitions.


// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3DA77C@@3MB @ 0x003DA77C
// match: ?flt_3DA780@@3MB @ 0x003DA780
// match: ?stru_3DA784@@3URwV3d@@B @ 0x003DA784
// match: ?stru_3DA790@@3URwV3d@@B @ 0x003DA790
// match: ??_C@_0BA@HHCLMDIG@d?3?2clonesPL?4xvu?$AA@ @ 0x003DA79C
// match: ??_C@_0O@HNECGONP@d?3?2clones?4xvu?$AA@ @ 0x003DA7AC
// match: ??_C@_07EJNPIMNF@CloneID?$AA@ @ 0x003DA7BC
// match: __real@3f933333 @ 0x003DA7C4
// match: __real@3fb0a3d7 @ 0x003DA7C8
// match: __real@3df5c28f @ 0x003DA7CC
// match: __real@3f1b59de @ 0x003DA7D0
// match: __real@3f33404f @ 0x003DA7D4
// match: ?dword_429B7C@@3PAKA @ 0x00429B7C
// match: ?dword_429B94@@3PAKA @ 0x00429B94

// match: ?sub_122FB0@@YAXXZ @ 0x00122FB0

// Sets the clones up: no file or clump, the two lights on frames of their
// own, the copies' frame, and the two vertex shaders.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_122FB0()
{
    RwFrame *var_4;
    RwInt32 local_8;

    dword_4CEAB0 = 0;
    dword_4CEA90 = 0;
    dword_4CF300 = 0;
    for (local_8 = 0; local_8 < 500; local_8++)
    {
        dword_4CEAE0[local_8] = 0;
    }
    dword_4CEAB4 = 0;
    dword_4CEAD8 = 1;
    dword_4CF2BC = 0;
    dword_4CF32C = 0;
    dword_4CEAA8 = RpLightCreate(rpLIGHTAMBIENT);
    dword_4CF308 = RpLightCreate(rpLIGHTDIRECTIONAL);
    var_4 = RwFrameCreate();
    RwFrameSetIdentity(var_4);
    RpLightSetFrame(dword_4CEAA8, var_4);
    var_4 = RwFrameCreate();
    RwFrameSetIdentity(var_4);
    RpLightSetFrame(dword_4CF308, var_4);
    frame = RwFrameCreate();
    dword_4CEAAC = 0;
    dword_4CEA80 = 0;
    sub_19F790("d:\\clones.xvu", dword_429B7C, &vertexShader);
    sub_19F790("d:\\clonesPL.xvu", dword_429B94, &dword_4CEA84);
}

// match: ?sub_1230F0@@YAXXZ @ 0x001230F0
// Frees what sub_122FB0 and the loads made.
void sub_1230F0()
{
    RwFrame *var_4;

    if (dword_4CEAB0)
    {
        RwFree(dword_4CEAB0);
        dword_4CEAB0 = 0;
    }
    if (dword_4CEAB4)
    {
        RpClumpDestroy(dword_4CEAB4);
        dword_4CEAB4 = 0;
    }
    var_4 = RpLightGetFrame(dword_4CEAA8);
    RpLightSetFrame(dword_4CEAA8, 0);
    RwFrameDestroy(var_4);
    var_4 = RpLightGetFrame(dword_4CF308);
    RpLightSetFrame(dword_4CF308, 0);
    RwFrameDestroy(var_4);
    RpLightDestroy(dword_4CEAA8);
    RpLightDestroy(dword_4CF308);
    if (frame)
    {
        RwFrameDestroy(frame);
        frame = 0;
    }
    D3DDevice_DeleteVertexShader(vertexShader);
    D3DDevice_DeleteVertexShader(dword_4CEA84);
    dword_4CEAD8 = 1;
}

// match: ?sub_1231F0@@YAPAUtype_1231F0@@H@Z @ 0x001231F0
// The first group of the level section arg_0 (-1: the last), or 0 past the
// file's sections.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
type_1231F0 *sub_1231F0(RwInt32 arg_0)
{
    RwUInt8 *var_4;
    type_1231F0 *v8;
    RwUInt8 *stk_C;
    type_1231F0 *var_10;

    if (dword_4CEA90 >= 0x10001)
    {
        var_4 = dword_4CEAB0;
        if (arg_0 > ((RwInt32 *)var_4)[1])
        {
            return 0;
        }
        if (arg_0 == -1)
        {
            arg_0 = ((RwInt32 *)var_4)[1];
        }
        v8 = (type_1231F0 *)(var_4 + ((RwInt32 *)var_4)[arg_0 + 1]);
        return v8;
    }
    stk_C = dword_4CEAB0;
    if (arg_0 > ((RwInt32 *)stk_C)[0])
    {
        return 0;
    }
    if (arg_0 == -1)
    {
        arg_0 = ((RwInt32 *)stk_C)[0];
    }
    var_10 = (type_1231F0 *)(stk_C + ((RwInt32 *)stk_C)[arg_0]);
    return var_10;
}

// match: ?sub_123280@@YAXPAURwStream@@I@Z @ 0x00123280
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Reads the clone file (arg_4 bytes) from the stream arg_0: its version,
// every group's pass unchosen, and the vertex buffers when it carries its
// own data.
void sub_123280(RwStream *arg_0, RwUInt32 arg_4)
{
    type_1231F0 *var_10;
    RwInt32 var_C;
    RwUInt8 *bp_8;
    RwInt32 bp_4;

    dword_4CEAB0 = (RwUInt8 *)RwMalloc(arg_4, 0x3425B);  // a memory hint; not an address
    RwStreamRead(arg_0, dword_4CEAB0, arg_4);
    bp_8 = dword_4CEAB0;
    dword_4CEA90 = ((RwInt32 *)bp_8)[0] >= 0x10001 ? ((RwInt32 *)bp_8)[0] : 0;
    bp_4 = ((RwInt32 *)bp_8)[1];
    bp_4 &= 0x7FFFFFFF;
    for (var_C = 0; var_C < bp_4; var_C++)
    {
        var_10 = (type_1231F0 *)(bp_8 + ((RwInt32 *)bp_8)[var_C + 2]);
        while (var_10->unk_00)
        {
            var_10->unk_3A = -1;
            var_10 = (type_1231F0 *)(dword_4CEAB0 + var_10->unk_64);
        }
    }
    if (((RwInt32 *)bp_8)[1] & 0x80000000)
    {
        ((RwInt32 *)bp_8)[1] &= 0x7FFFFFFF;
        dword_4CEAAC = 1;
        sub_124290();
    }
}

// match: ?sub_123380@@YAPAURpAtomic@@PAU1@PAX@Z @ 0x00123380
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Puts the atomic arg_0 in the slot its "CloneID" names, at the origin.
RpAtomic *sub_123380(RpAtomic *arg_0, void *arg_4)
{
    RwInt32 var_18;
    RpUserDataArray *var_14;
    RwChar *lv_10;
    RwInt32 var_C;
    RpGeometry *bp_8;
    RwInt32 bp_4;

    bp_8 = RpAtomicGetGeometry(arg_0);
    bp_4 = RpGeometryGetUserDataArrayCount(bp_8);
    for (var_C = 0; var_C < bp_4; var_C++)
    {
        var_14 = RpGeometryGetUserDataArray(bp_8, var_C);
        lv_10 = RpUserDataArrayGetName(var_14);
        if (!strcmp(lv_10, "CloneID"))
        {
            var_18 = RpUserDataArrayGetInt(var_14, 0);
            dword_4CEAE0[var_18] = arg_0;
            dword_4CF300++;
            RwFrameSetIdentity(RpAtomicGetFrame(arg_0));
        }
    }
    return arg_0;
}

// match: ?sub_123440@@YAXPAURwStream@@@Z @ 0x00123440
// Reads the clones' clump from the stream arg_0, replacing the last.
void sub_123440(RwStream *arg_0)
{
    if (dword_4CEAB4)
    {
        dword_4CF32C = 1;
        RpClumpDestroy(dword_4CEAB4);
        dword_4CEAB4 = 0;
    }
    if (RwStreamFindChunk(arg_0, rwID_CLUMP, 0, 0))
    {
        RwTexDictionarySetCurrent(sub_174520());
        dword_4CEAB4 = RpClumpStreamRead(arg_0);
        if (dword_4CEAB4)
        {
            RpClumpForAllAtomics(dword_4CEAB4, sub_123380, 0);
        }
    }
}

// match: ?sub_1234D0@@YAXH@Z @ 0x001234D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the clones of pass arg_0 in the sections loaded (and the file's
// last): each group lit as it says, its copies through RenderWare or the
// shaders.
void sub_1234D0(RwInt32 arg_0)
{
    type_1243F0 *var_20;
    RwUInt32 l1C;
    RpLight *m_18;
    type_1243F0 *ebp_14;
    RpAtomic *lv_10;
    RwInt32 var_C;
    type_1231F0 *bp_8;
    RwInt32 bp_4;

    if (dword_4CF32C)
    {
        return;
    }
    if (!dword_4CEAB0)
    {
        return;
    }
    if (!dword_4CF300)
    {
        return;
    }
    if (dword_4CF31C)
    {
        return;
    }
    dword_4CEA80 = 1;
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)0);
    if (!dword_4CF450)
    {
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
    }
    else
    {
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)1);
    }
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLBACK);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void *)1);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void *)1);
    sub_123980();
    dword_4CEAC4 = 0;
    dword_4CF310 = 0;
    if (!dword_4CEAAC)
    {
        dword_4CF330 = 1;
    }
    for (bp_4 = -1; bp_4 < 4; bp_4++)
    {
        if (bp_4 == -1 || dword_4E5D30[bp_4].get_unk_00())
        {
            bp_8 = 0;
            if (bp_4 == -1)
            {
                bp_8 = sub_1231F0(bp_4);
            }
            else
            {
                bp_8 = sub_1231F0(dword_4E5D30[bp_4].get_unk_08());
            }
            if (bp_8)
            {
                var_C = 0;
                while (bp_8->unk_00)
                {
                    lv_10 = dword_4CEAE0[bp_8->unk_00];
                    if (lv_10)
                    {
                        var_C++;
                        if (!(RwInt32)(bp_8->unk_3A != -1))
                        {
                            sub_1239B0(bp_8, var_C);
                        }
                        if (arg_0 != bp_8->unk_3A)
                        {
                        }
                        else if (!bp_8->unk_38)
                        {
                            if (!dword_4CF324)
                            {
                                if (dword_4CEA90 < 0x10001)
                                {
                                    ebp_14 = bp_8->unk_70;
                                }
                                else
                                {
                                    ebp_14 = (type_1243F0 *)(dword_4CEAB0 + bp_8->unk_34);
                                }
                                sub_123AF0(lv_10, 0, 0, 0, 0, 0);
                                sub_123FE0(ebp_14, bp_8->unk_04, bp_8);
                                sub_124D70();
                            }
                        }
                        else
                        {
                            if (!dword_4CEAAC)
                            {
                                l1C = RpGeometryGetFlags(RpAtomicGetGeometry(lv_10));
                                l1C &= ~8;
                                l1C |= 0x20;
                                RpAtomicGetGeometry(lv_10)->flags = l1C;
                            }
                            m_18 = get_light(0);
                            if (m_18)
                            {
                                stru_4CEA94 = m_18->color;
                                stru_4CF2C0 = *RwFrameGetLTM(RpLightGetFrame(m_18));
                            }
                            m_18 = (RpLight *)clump;
                            if (m_18)
                            {
                                stru_4CEA70 = m_18->color;
                            }
                            sub_123AF0(lv_10, 1, 0, &bp_8->unk_08, &bp_8->unk_18, &bp_8->unk_28);
                            if (dword_4CEA90 < 0x10001)
                            {
                                sub_123FE0(bp_8->unk_70, bp_8->unk_04, bp_8);
                                sub_124D70();
                            }
                            else
                            {
                                if (dword_4CEA90 < 0x10001)
                                {
                                    var_20 = bp_8->unk_70;
                                }
                                else
                                {
                                    var_20 = (type_1243F0 *)(dword_4CEAB0 + bp_8->unk_34);
                                }
                                sub_123FE0(var_20, bp_8->unk_04, bp_8);
                                sub_124D70();
                            }
                            m_18 = get_light(0);
                            if (m_18)
                            {
                                RpLightSetColor(m_18, &stru_4CEA94);
                                *RwFrameGetLTM(RpLightGetFrame(m_18)) = stru_4CF2C0;
                            }
                            m_18 = (RpLight *)clump;
                            if (m_18)
                            {
                                RpLightSetColor(m_18, &stru_4CEA70);
                            }
                        }
                    }
                    if (dword_4CEA90 >= 0x10001)
                    {
                        bp_8 = sub_1241D0(bp_8);
                    }
                    else
                    {
                        bp_8 = (type_1231F0 *)((RwMatrix *)bp_8 + bp_8->unk_04 + 1);
                    }
                }
            }
        }
    }
    dword_4F309C = dword_4CEAC4;
    dword_4F30A0 = dword_4CF310;
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void *)rwALPHATESTFUNCTIONALWAYS);
    dword_4CEA80 = 0;
}

// match: ?sub_123980@@YAXXZ @ 0x00123980
void sub_123980()
{
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION, (void *)rwALPHATESTFUNCTIONGREATER);
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, (void *)dword_4F3080);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void *)rwCULLMODECULLNONE);
}

// match: ?sub_1239B0@@YAXPAUtype_1231F0@@H@Z @ 0x001239B0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Chooses the pass of the group arg_0 (the arg_4th drawn; the first resets
// the overrides): the first for a clone over 1000 across, else the second
// when any of its meshes' textures has the flag.
void sub_1239B0(type_1231F0 *arg_0, RwInt32 arg_4)
{
    RwInt32 var_10;
    RwInt32 var_C;
    RpAtomic *bp_8;
    RwInt32 bp_4;

    bp_4 = 0;
    bp_8 = dword_4CEAE0[arg_0->unk_00];
    if (arg_4 == 1)
    {
        dword_4CF338 = 0;
        dword_4CF334 = 0;
    }
    var_10 = sub_19B050();
    if (bp_8->boundingSphere.radius > 1000.0f)
    {
        arg_0->unk_3A = 0;
        bp_4 = 1;
    }
    if (dword_4CF338)
    {
        arg_0->unk_3A = 0;
    }
    else if (dword_4CF334)
    {
        arg_0->unk_3A = 1;
    }
    else if (!bp_4)
    {
        var_C = 0;
        RpGeometryForAllMeshes(RpAtomicGetGeometry(bp_8), sub_123A80, &var_C);
        if (var_C > 0)
        {
            arg_0->unk_3A = 1;
        }
        else
        {
            arg_0->unk_3A = 0;
        }
    }
}

// match: ?sub_123A80@@YAPAURpMesh@@PAU1@PAURpMeshHeader@@PAX@Z @ 0x00123A80
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Counts into arg_8 the meshes whose texture's raster has the flag.
RpMesh *sub_123A80(RpMesh *arg_0, RpMeshHeader *arg_4, void *arg_8)
{
    type_123A80 *var_8;
    RwInt32 *l4;

    l4 = (RwInt32 *)arg_8;
    if (arg_0 && arg_0->material && arg_0->material->texture && arg_0->material->texture->raster)
    {
        var_8 = (type_123A80 *)RASTEREXTFROMRASTER(arg_0->material->texture->raster->parent);
        if (var_8->unk_12)
        {
            (*l4)++;
        }
    }
    return arg_0;
}

// match: ?sub_123AF0@@YAXPAURpAtomic@@HPAURwRGBAReal@@11PAURwV3d@@@Z @ 0x00123AF0
// Starts drawing the atomic arg_0 (lit when arg_4 is 1), tinted by arg_8
// (white without): for a lit atomic outside the clones pass, sets the
// ambient light to arg_C and the view light to the colour arg_10 (scaled by
// dword_4F30A8.unk_04 and clamped) along arg_14 (each the light's own without).
void sub_123AF0(RpAtomic *arg_0, RwInt32 arg_4, RwRGBAReal *arg_8, RwRGBAReal *arg_C,
                RwRGBAReal *arg_10, RwV3d *arg_14)
{
    RwRGBAReal var_10;
    RpLight *var_14;
    RwRGBAReal var_24;
    RpLight *var_2C;
    RpLight *var_34;
    RpLight *var_38;
    RwV3d var_48;
    RwMatrix var_90;

    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
    dword_4CEA8C = arg_0;
    dword_4CF30C = arg_4;
    dword_4CF2B0 = 0;
    dword_4CEAA4 = 0;
    if (arg_8)
    {
        dword_4CEAC8 = *arg_8;
    }
    else
    {
        dword_4CEAC8.red = dword_4CEAC8.green = dword_4CEAC8.blue = dword_4CEAC8.alpha = 1.0f;
    }
    if (dword_4CF30C == 1 && !dword_4CEA80)
    {
        if (arg_C)
        {
            var_10 = *arg_C;
        }
        else
        {
            var_14 = (RpLight *)clump;
            if (var_14)
            {
                var_10 = var_14->color;
            }
        }
        if (arg_10)
        {
            var_24 = *arg_10;
        }
        else
        {
            var_2C = get_light(0);
            if (var_2C)
            {
                var_24 = var_2C->color;
            }
        }
        if (arg_14)
        {
            dword_4CEAB8 = *arg_14;
        }
        else
        {
            var_34 = get_light(0);
            dword_4CEAB8 = RwFrameGetLTM(RpLightGetFrame(var_34))->at;
        }
        var_38 = (RpLight *)clump;
        if (var_38)
        {
            RpLightSetColor(var_38, &var_10);
        }
        var_38 = get_light(0);
        if (var_38)
        {
            if (dword_4CEAB8.y * dword_4CEAB8.y != 1.0f)
            {
                var_48 = stru_3DA784;
            }
            else
            {
                var_48 = stru_3DA790;
            }
            RwMatrixSetIdentityMacro(&var_90);
            RwV3dCrossProductMacro(&var_90.right, &var_48, &dword_4CEAB8);
            var_90.at = dword_4CEAB8;
            RwV3dCrossProductMacro(&var_90.up, &var_90.at, &var_90.right);
            if (*(RwInt32 *)&dword_4F30A8.unk_04 != 0x3F800000)   // 1.0f's bits; not an address
            {
                var_24.red *= dword_4F30A8.unk_04;
                var_24.green *= dword_4F30A8.unk_04;
                var_24.blue *= dword_4F30A8.unk_04;
                var_24.alpha *= dword_4F30A8.unk_04;
                var_24.red = 1.0f > var_24.red ? var_24.red : 1.0f;
                var_24.green = 1.0f > var_24.green ? var_24.green : 1.0f;
                var_24.blue = 1.0f > var_24.blue ? var_24.blue : 1.0f;
                var_24.alpha = 1.0f > var_24.alpha ? var_24.alpha : 1.0f;
            }
            RpLightSetColor(var_38, &var_24);
            RwFrameTransform(RpLightGetFrame(var_38), &var_90, rwCOMBINEREPLACE);
        }
    }
}

// match: ?sub_123FE0@@YAXPAUtype_1243F0@@HPAUtype_1231F0@@@Z @ 0x00123FE0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Draws the atomic sub_123AF0 started at the arg_4 copies from arg_0 (of
// the group arg_8): through the shaders when the group has its own data,
// else through RenderWare at each copy's matrix, counting what is tested
// and drawn.
void sub_123FE0(type_1243F0 *arg_0, RwInt32 arg_4, type_1231F0 *arg_8)
{
    const RwSphere *var_14;
    const RwSphere *lv_10;
    RwInt32 var_C;
    RwFrame *bp_8;
    RwFrame *bp_4;

    if (dword_4CF31C)
    {
        return;
    }
    if (!dword_4CF30C && dword_4CF324)
    {
        return;
    }
    if (dword_4CF30C == 1 && dword_4CF328)
    {
        return;
    }
    if (arg_8 && !dword_4CF330)
    {
        sub_1245D0(arg_8, arg_0);
        return;
    }
    bp_4 = RpAtomicGetFrame(dword_4CEA8C);
    bp_8 = frame;
    RpAtomicSetFrame(dword_4CEA8C, bp_8);
    for (var_C = 0; var_C < arg_4; var_C++)
    {
        if (dword_4CF30C == 1)
        {
            *RwFrameGetLTM(bp_8) = arg_0->unk_00;
            lv_10 = RpAtomicGetWorldBoundingSphere(dword_4CEA8C);
            dword_4CF310++;
            if (RwCameraFrustumTestSphere(RwCameraGetCurrentCamera(), lv_10))
            {
                dword_4CEAC4++;
                RpAtomicRender(dword_4CEA8C);
            }
        }
        else
        {
            *RwFrameGetLTM(bp_8) = arg_0->unk_00;
            var_14 = RpAtomicGetWorldBoundingSphere(dword_4CEA8C);
            dword_4CF310++;
            if (RwCameraFrustumTestSphere(RwCameraGetCurrentCamera(), var_14))
            {
                RpAtomicRender(dword_4CEA8C);
                dword_4CEAC4++;
            }
        }
        if (arg_8 && dword_4CEAAC && dword_4CEA80)
        {
            arg_0++;
        }
        else
        {
            arg_0 = (type_1243F0 *)(&arg_0->unk_00 + 1);
        }
    }
    RpAtomicSetFrame(dword_4CEA8C, bp_4);
}

// match: ?sub_1241D0@@YAPAUtype_1231F0@@PAU1@@Z @ 0x001241D0
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// The group after arg_0 (in the files from version 0x10001).
type_1231F0 *sub_1241D0(type_1231F0 *arg_0)
{
    RwInt32 var_8;
    RwInt32 *l4;

    if (dword_4CEAAC)
    {
        var_8 = arg_0->unk_64;
    }
    else
    {
        l4 = &arg_0->unk_3C;
        var_8 = *l4;
    }
    return (type_1231F0 *)(dword_4CEAB0 + var_8);
}

// match: ?sub_124210@@YAPAURpMesh@@PAU1@PAURpMeshHeader@@PAX@Z @ 0x00124210
// Hands the material of the dword_4CEA88th mesh to arg_8.
RpMesh *sub_124210(RpMesh *arg_0, RpMeshHeader *arg_4, void *arg_8)
{
    RpMaterial **var_4;

    var_4 = (RpMaterial **)arg_8;
    if (dword_4CF304++ == dword_4CEA88)
    {
        *var_4 = arg_0->material;
    }
    return arg_0;
}

// match: ?sub_124250@@YAXPAUtype_124250@@H@Z @ 0x00124250
// Fills in the material of the mesh arg_0, the arg_4th of the atomic drawn.
void sub_124250(type_124250 *arg_0, RwInt32 arg_4)
{
    RpGeometry *var_4;

    var_4 = RpAtomicGetGeometry(dword_4CEA8C);
    dword_4CF304 = 0;
    dword_4CEA88 = arg_4;
    RpGeometryForAllMeshes(var_4, sub_124210, arg_0);
}

// match: ?sub_124290@@YAXXZ @ 0x00124290
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
// Gives each group of a file with its own data its copies' radii and a
// vertex buffer, one per clone.
void sub_124290()
{
    RwUInt8 *var_1C;
    BYTE *var_18;
    D3DVertexBuffer *var_14;
    RwInt32 lv_10;
    type_1231F0 *var_C;
    D3DVertexBuffer **bp_8;
    RwUInt8 *bp_4;

    bp_4 = dword_4CEAB0;
    bp_8 = (D3DVertexBuffer **)malloc(0x4000);
    memset(bp_8, 0, 0x4000);
    for (lv_10 = 1; lv_10 <= ((RwInt32 *)bp_4)[1]; lv_10++)
    {
        if ((var_C = (type_1231F0 *)(bp_4 + ((RwInt32 *)bp_4)[lv_10 + 1])) != 0)
        {
            while (var_C->unk_00)
            {
                sub_1243F0(var_C);
                if (!var_C->unk_60)
                {
                    if (!bp_8[var_C->unk_00])
                    {
                        var_1C = bp_4 + var_C->unk_48;
                        var_14 = RwXbCreateVertexBuffer(var_C->unk_40 * 0x30);
                        var_14->Lock(0, 0, &var_18, 0);
                        memcpy(var_18, var_1C, var_C->unk_40 * 0x30);
                        bp_8[var_C->unk_00] = var_14;
                    }
                    else
                    {
                        var_14 = bp_8[var_C->unk_00];
                    }
                    var_C->unk_60 = var_14;
                }
                if (dword_4CEA90 >= 0x10001)
                {
                    var_C = sub_1241D0(var_C);
                }
                else
                {
                    var_C = (type_1231F0 *)((RwMatrix *)var_C + var_C->unk_04 + 1);
                }
            }
        }
    }
    free(bp_8);
}

// match: ?sub_1243F0@@YAXPAUtype_1231F0@@@Z @ 0x001243F0
// Sets each copy's bounding radius: its matrix's largest axis by the
// group's radius scale.
void sub_1243F0(type_1231F0 *arg_0)
{
    type_1243F0 *var_4;
    RwInt32 var_8;
    RwV3d *var_C;
    RwV3d *var_10;
    RwV3d *var_14;
    RwReal var_18;
    RwReal var_1C;
    RwReal var_20;
    RwReal var_30;
    RwReal var_94;
    RwReal var_98;
    RwReal *var_9C;

    if (dword_4CEA90 < 0x10001)
    {
        var_4 = arg_0->unk_70;
    }
    else
    {
        var_4 = (type_1243F0 *)(dword_4CEAB0 + arg_0->unk_34);
    }
    for (var_8 = 0; var_8 < arg_0->unk_04; var_8++)
    {
        var_C = &var_4->unk_00.right;
        var_10 = &var_4->unk_00.up;
        var_14 = &var_4->unk_00.at;
        var_18 = RwV3dDotProductMacro(var_C, var_C);
        var_1C = RwV3dDotProductMacro(var_10, var_10);
        var_20 = RwV3dDotProductMacro(var_14, var_14);
        var_30 = var_18 >= (var_1C >= var_20 ? var_1C : var_20)
                     ? var_18
                     : (var_1C >= var_20 ? var_1C : var_20);
        do
        {
            __m128 var_50 = _mm_set_ss((RwReal)var_30);
            __m128 var_80 = _mm_sqrt_ss(var_50);
            _mm_store_ss(&var_94, var_80);
        } while (0);
        var_98 = arg_0->unk_5C * var_94;
        var_9C = &var_4->unk_4C;
        *var_9C = var_98;
        var_4++;
    }
}

// match: ?sub_1245D0@@YAXPAUtype_1231F0@@PAUtype_1243F0@@@Z @ 0x001245D0
// Draws the group arg_0's copies from arg_4 with the vertex shaders: the
// first of the pass sets up the view, projection and clip planes; each copy
// in view is drawn unk_4C times (at least once), mesh by mesh.
void sub_1245D0(type_1231F0 *arg_0, type_1243F0 *arg_4)
{
    RwUInt16 *var_154;
    RwInt32 var_150;
    RpMaterial *var_14C;
    RwInt32 var_148;
    RwInt32 var_144;
    RwV3d var_140;
    RwV3d *var_134;
    XGMATRIX var_130;
    XGMATRIX var_F0;
    RwInt32 *var_B0;
    type_124250 *var_AC;
    RwUInt8 *var_A8;
    RwInt32 var_A4;
    RwSphere var_A0;
    __declspec(align(16)) RwReal var_90[4];
    RwReal var_74[4];
    RwReal var_58[4];
    RwV2d *var_44;
    RwReal var_40;
    RwReal var_3C;
    RwV3d var_38;
    RwV3d *var_2C;
    RwV3d *var_28;
    RwReal var_24;
    RwReal var_20;
    RwMatrix *var_18;
    RwCamera *var_14;
    RwInt32 var_10;
    RwUInt32 var_C;
    RpGeometry *var_8;
    RwUInt8 *var_4;

    var_4 = dword_4CEAB0;
    var_8 = RpAtomicGetGeometry(dword_4CEA8C);
    var_C = RpGeometryGetFlags(var_8);
    if (arg_0->unk_4C)
    {
        var_10 = arg_0->unk_4C;
    }
    else
    {
        var_10 = 1;
    }
    if (!dword_4CEAC4)
    {
        var_14 = (RwCamera *)dword_4E5C74;
        var_18 = RwFrameGetMatrix(RwCameraGetFrame(var_14));
        var_20 = *(RwReal *)&dword_4CF540 > 20.0f ? *(RwReal *)&dword_4CF540 : 20.0f;
        var_24 = farClip;
        RwCameraSetNearClipPlane(var_14, var_20);
        RwCameraSetFarClipPlane(var_14, var_24);
        var_28 = &var_18->up;
        var_2C = &var_18->pos;
        var_38 = var_18->at;
        var_38.x = var_38.x * 100.0f + var_2C->x;
        var_38.y = var_38.y * 100.0f + var_2C->y;
        var_38.z = var_38.z * 100.0f + var_2C->z;
        D3DXMatrixLookAtRH((D3DXMATRIX *)&pM2, (D3DXVECTOR3 *)var_2C, (D3DXVECTOR3 *)&var_38,
                           (D3DXVECTOR3 *)var_28);
        var_3C = 1.0f;
        var_40 = 1.3333334f;
        var_44 = &((RwCamera *)dword_4E5C74)->viewWindow;
        D3DXMatrixPerspectiveFovRH((D3DXMATRIX *)&stru_4CF340,
                                   ((0.7002f - var_44->x) / 0.60684f * 0.12f + 1.38f) * var_44->x,
                                   var_40, var_20, var_24);
        RwXboxSetCurrentPixelShader(0);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void *)0);
    }
    if (arg_0->unk_38 == 1)
    {
        RwXboxSetCurrentVertexShader(vertexShader);
        var_58[0] = arg_0->unk_08.red * 1.15f > 1.0f ? 1.0f : arg_0->unk_08.red * 1.15f;
        var_58[1] = arg_0->unk_08.green * 1.15f > 1.0f ? 1.0f : arg_0->unk_08.green * 1.15f;
        var_58[2] = arg_0->unk_08.blue * 1.15f > 1.0f ? 1.0f : arg_0->unk_08.blue * 1.15f;
        var_58[3] = arg_0->unk_08.alpha;
        var_74[0] = arg_0->unk_18.red * 1.15f > 1.0f ? 1.0f : arg_0->unk_18.red * 1.15f;
        var_74[1] = arg_0->unk_18.green * 1.15f > 1.0f ? 1.0f : arg_0->unk_18.green * 1.15f;
        var_74[2] = arg_0->unk_18.blue * 1.15f > 1.0f ? 1.0f : arg_0->unk_18.blue * 1.15f;
        var_74[3] = arg_0->unk_18.alpha;
        D3DDevice_SetVertexShaderConstant(4, var_58, 1);
        D3DDevice_SetVertexShaderConstant(5, var_74, 1);
        var_90[0] = 0.0f;
        var_90[1] = 0.0f;
        var_90[2] = 0.0f;
        var_90[3] = 0.0f;
        D3DDevice_SetVertexShaderConstant(7, var_90, 1);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)0);
    }
    else
    {
        RwXboxSetCurrentVertexShader(dword_4CEA84);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)1);
    }
    while (var_10--)
    {
        RwV3dTransformPoint(&var_A0.center, &dword_4CEA8C->boundingSphere.center, &arg_4->unk_00);
        var_A0.radius = arg_4->unk_4C;
        dword_4CF310++;
        if (!RwCameraFrustumTestSphere((RwCamera *)dword_4E5C74, &var_A0))
        {
        }
        else
        {
            var_A4 = arg_0->unk_44;
            var_A8 = var_4 + arg_0->unk_48;
            var_AC = (type_124250 *)(var_A8 + arg_0->unk_40 * 0x30);
            var_B0 = &var_AC->unk_04;
            XGMatrixMultiply(&var_F0, (XGMATRIX *)&arg_4->unk_00, (XGMATRIX *)&pM2);
            XGMatrixMultiply(&var_130, &var_F0, (XGMATRIX *)&stru_4CF340);
            XGMatrixTranspose(&var_130, &var_130);
            D3DDevice_SetVertexShaderConstant(0, &var_130, 4);
            if (arg_0->unk_38 == 1)
            {
                var_134 = &arg_4->unk_40;
                var_140.x = var_134->x;
                var_140.y = var_134->y;
                var_140.z = var_134->z;
                D3DDevice_SetVertexShaderConstant(6, &var_140, 1);
            }
            D3DDevice_SetStreamSource(0, arg_0->unk_60, 0x30);
            var_144 = 0;
            while (var_A4--)
            {
                if (!var_AC->unk_00)
                {
                    var_148 = arg_0->unk_44 - (var_A4 + 1);
                    sub_124250(var_AC, var_148);
                }
                var_14C = var_AC->unk_00;
                if (var_14C && (var_C & (rpGEOMETRYTEXTURED | rpGEOMETRYTEXTURED2)))
                {
                    RwXboxRenderStateSetTexture(var_14C->texture, 0);
                }
                else
                {
                    RwXboxRenderStateSetTexture(0, 0);
                }
                var_150 = *var_B0;
                var_154 = (RwUInt16 *)(var_B0 + 1);
                _rwXbFlushCacheBuffer();
                D3DDevice_DrawIndexedVertices(D3DPT_TRIANGLESTRIP, var_150, var_154);
                if (var_150 & 1)
                {
                    var_150++;
                }
                var_AC = (type_124250 *)(var_154 + var_150);
                var_B0 = &var_AC->unk_04;
            }
            dword_4CEAC4++;
        }
        arg_4++;
    }
}

// match: ?sub_124D70@@YAXXZ @ 0x00124D70
void sub_124D70()
{
    if (dword_4CF30C == 1)
    {
        if (dword_4CF2B0)
        {
            dword_4CF2B0 = 0;
        }
    }
    else
    {
        if (dword_4CEAA4)
        {
            dword_4CEAA4 = 0;
        }
        if (dword_4CF2B0)
        {
            dword_4CF2B0 = 0;
        }
    }
}
