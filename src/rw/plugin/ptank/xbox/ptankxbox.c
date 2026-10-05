/*
 * codfh-match: RenderWare 3.6's Xbox PTank platform file, rebuilt from the
 * image; the file name is the image's RCS id string's. RenderWare's 3.7.2
 * tree has no Xbox PTank (the structure follows ptankd3d8.c) and the
 * Godfather PDB has no PTank at all. PTankOpen and PTankClose, which only
 * return the instance, were folded by /OPT:ICF into _rwerror's body
 * (0x2D9180): defined here, placed nowhere.
 */

#include <xtl.h>

#include "rpplugin.h"
#include <rwcore.h>
#include <rpworld.h>

#include "ptank.h"
#include "ptankg.h"

#include "xbcache.h"
#include "xbrendst.h"
#include "xbpipe.h"
#include "xbvtxfmt.h"
#include "nodeXBoxAtomicAllInOne.h"

#include "ptankxbox.h"

/* RenderWare 3.6's RCS id string, which the image keeps (the 3.7.2 tree has none) */
static const char rcsid[] = "@@@@(#)$Id: //RenderWare/RW36Active/rwsdk/plugin/ptank/xbox/ptankxbox.c#1 $";

extern void RwXboxSetCurrentVertexShader(DWORD handle);
extern void RwXboxSetCurrentPixelShader(DWORD handle);
extern void RwXboxSetCurrentStream(RwUInt32 stride);
extern RwUInt8 *RwXboxLockDynamicVertexBuffer(RwInt32 size);
extern RwBool RwXbSetSurfaceProperties(const RwRGBA *color,
                                       const RwSurfaceProperties *surfaceProps,
                                       RwBool modulate);

static RwBool rpPTankXboxCreate(RpAtomic *atomic, RpPTankData *ptankGlobal,
                                RwInt32 maxPCount, RwUInt32 dataFlags,
                                RwUInt32 platFlags);
static RwBool rpPTankXboxInstance(RpAtomic *atomic, RpPTankData *ptankGlobal,
                                  RwInt32 actPCount, RwUInt32 instFlags);
static RwBool rpPTankXboxRenderCallBack(RpAtomic *atomic, RpPTankData *ptankGlobal,
                                        RwInt32 actPCount);

/* TRUE when InsSetup packs the constant texture coordinates as bytes. */
static RwBool rpPTankXboxPackedUVs = FALSE;

static const D3DMATRIX rpPTankXboxIdentity =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

static __inline void
SinCos(float angle, float *sine, float *cosine)
{
    __asm
    {
        fld     dword ptr angle
        fsincos
        mov     eax, sine
        mov     edx, cosine
        fstp    dword ptr [edx]
        fstp    dword ptr [eax]
    }
}

// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: _rcsid @ 0x00419C08
// match: __real@43ff8000 @ 0x004193AC
// match: __real@447fc000 @ 0x004193B0
// match: _rpPTankXboxIdentity @ 0x00419C58
// match: _defaultCB @ 0x00436E30

// match: _rpPTankXboxRenderCallBack @ 0x002E9B20

static RwBool
rpPTankXboxRenderCallBack(RpAtomic *atomic, RpPTankData *ptankGlobal, RwInt32 actPCount)
{
    RpGeometry      *geom = RpAtomicGetGeometry(atomic);
    RpMaterial      *material = RpGeometryGetMaterial(geom, 0);
    RwUInt32        flags = RpGeometryGetFlags(geom);
    RpXboxVtxFmt    fmt;
    RwUInt32        strideVertex;
    DWORD           lighting;
    RwUInt32        srcBlend, dstBlend;

    if (RPATOMICPTANKPLUGINDATA(atomic)->platFlags == rpPTANKXBOXFLAGSOPTIMIZED)
    {
        _rpPTankXboxOptRenderCallBack(atomic, ptankGlobal, actPCount);

        return TRUE;
    }

    fmt.pos = rpFLOAT;
    strideVertex = sizeof(RwV3d);

    if (flags & rxGEOMETRY_NORMALS)
    {
        strideVertex = sizeof(RwV3d) + sizeof(RwUInt32);
        fmt.norm = rpNORMALIZEDPACKED;
    }
    else
    {
        fmt.norm = rpCOMPTYPENONE;
    }

    if (flags & rxGEOMETRY_PRELIT)
    {
        strideVertex += sizeof(RwRGBA);
        fmt.prelit = TRUE;
    }
    else
    {
        fmt.prelit = FALSE;
    }

    if (flags & rxGEOMETRY_TEXTURED)
    {
        if (rpPTankXboxPackedUVs)
        {
            strideVertex += 2;
            fmt.texCoord = rpPACKEDBYTE;
        }
        else
        {
            strideVertex += sizeof(RwTexCoords);
            fmt.texCoord = rpFLOAT;
        }
    }
    else
    {
        fmt.texCoord = rpCOMPTYPENONE;
    }

    fmt.reserved = 0;

    _rwXbAtomicDefaultLightingCallback(atomic);

    D3DDevice_SetTransform(D3DTS_WORLD, &rpPTankXboxIdentity);

    RwXboxGetCachedRenderState(D3DRS_LIGHTING, &lighting);
    RwXboxSetCachedRenderState(D3DRS_NORMALIZENORMALS, FALSE);

    if (lighting)
    {
        RwXboxSetCachedRenderState(D3DRS_COLORVERTEX, TRUE);
        RwXboxSetCachedRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_COLOR1);
    }

    RwXboxRenderStateSetTexture(material->texture, 0);

    RwXboxSetCurrentPixelShader(0);
    RwXboxSetCurrentVertexShader(RxXboxGetVertexFormatShader(&fmt));

    if (ptankGlobal->vertexAlphaBlend)
    {
        RwRenderStateGet(rwRENDERSTATESRCBLEND, (void *)&srcBlend);
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)ptankGlobal->srcBlend);
        RwRenderStateGet(rwRENDERSTATEDESTBLEND, (void *)&dstBlend);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)ptankGlobal->dstBlend);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)TRUE);
    }
    else
    {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void *)FALSE);
    }

    if (!(flags & rxGEOMETRY_PRELIT) && !lighting)
    {
        RwUInt32    tFactor;

        tFactor = ((RwUInt32)ptankGlobal->cColor.alpha << 24) |
                  ((RwUInt32)ptankGlobal->cColor.red << 16) |
                  ((RwUInt32)ptankGlobal->cColor.green << 8) |
                  (RwUInt32)ptankGlobal->cColor.blue;

        RwXboxSetCachedRenderState(D3DRS_TEXTUREFACTOR, tFactor);

        if (material->texture)
        {
            RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        }
        else
        {
            RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        }

        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

        if (ptankGlobal->vertexAlphaBlend)
        {
            if (material->texture)
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
            }
            else
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
            }
        }
        else
        {
            if (material->texture)
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
            }
            else
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            }
        }

        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
    }
    else
    {
        if (material->texture)
        {
            RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
        }
        else
        {
            RwXboxSetCachedTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
        }

        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

        if (ptankGlobal->vertexAlphaBlend)
        {
            if (material->texture)
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
            }
            else
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
            }
        }
        else
        {
            if (material->texture)
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
            }
            else
            {
                RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
            }
        }

        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
        RwXboxSetCachedTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

        if (lighting)
        {
            RwXboxSetCachedRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

            RwXbSetSurfaceProperties(&material->color, &material->surfaceProps, TRUE);
        }
    }

    RwXboxSetCurrentStream(strideVertex);

    RwXboxDrawVertices(D3DPT_QUADLIST, 0, actPCount * 4);

    if (ptankGlobal->vertexAlphaBlend)
    {
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void *)srcBlend);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void *)dstBlend);
    }

    return FALSE;
}

// match: _rpPTankXboxInsUV2C @ 0x002EA1A0
static void
rpPTankXboxInsUV2C(RpPTankLockStruct *dstCluster, RwInt32 pCount, RpPTankData *ptankGlobal)
{
    RwInt32     i;
    RwUInt8     *uDst = dstCluster->data;
    RwUInt32    uDStride = dstCluster->stride;
    RwUInt8     u0, v0, u1, v1;
    RwUInt16    uv0, uv1, uv2, uv3;

    u0 = (RwUInt8)RwFastRealToUInt32(ptankGlobal->cUV[0].u * 255.0f);
    v0 = (RwUInt8)RwFastRealToUInt32(ptankGlobal->cUV[0].v * 255.0f);
    u1 = (RwUInt8)RwFastRealToUInt32(ptankGlobal->cUV[1].u * 255.0f);
    v1 = (RwUInt8)RwFastRealToUInt32(ptankGlobal->cUV[1].v * 255.0f);

    uv0 = (RwUInt16)u0 | ((RwUInt16)v1 << 8);
    uv1 = (RwUInt16)u1 | ((RwUInt16)v1 << 8);
    uv2 = (RwUInt16)u1 | ((RwUInt16)v0 << 8);
    uv3 = (RwUInt16)u0 | ((RwUInt16)v0 << 8);

    for (i = 0; i < pCount; i++)
    {
        *(RwUInt16 *)uDst = uv0;
        uDst += uDStride;
        *(RwUInt16 *)uDst = uv1;
        uDst += uDStride;
        *(RwUInt16 *)uDst = uv2;
        uDst += uDStride;
        *(RwUInt16 *)uDst = uv3;
        uDst += uDStride;
    }
}

// match: _rpPTankXboxInsUV4C @ 0x002EA280
static void
rpPTankXboxInsUV4C(RpPTankLockStruct *dstCluster, RwInt32 pCount, RpPTankData *ptankGlobal)
{
    RwInt32     i;
    RwUInt8     *uDst = dstCluster->data;
    RwUInt32    uDStride = dstCluster->stride;
    RwUInt16    uv[4];

    uv[0] = (RwUInt16)(((RwUInt8)RwFastRealToUInt32(ptankGlobal->cUV[0].v * 255.0f) << 8) |
                     RwFastRealToUInt32(ptankGlobal->cUV[0].u * 255.0f));
    uv[1] = (RwUInt16)(((RwUInt8)RwFastRealToUInt32(ptankGlobal->cUV[1].v * 255.0f) << 8) |
                     RwFastRealToUInt32(ptankGlobal->cUV[1].u * 255.0f));
    uv[2] = (RwUInt16)(((RwUInt8)RwFastRealToUInt32(ptankGlobal->cUV[2].v * 255.0f) << 8) |
                     RwFastRealToUInt32(ptankGlobal->cUV[2].u * 255.0f));
    uv[3] = (RwUInt16)(((RwUInt8)RwFastRealToUInt32(ptankGlobal->cUV[3].v * 255.0f) << 8) |
                     RwFastRealToUInt32(ptankGlobal->cUV[3].u * 255.0f));

    for (i = 0; i < pCount; i++)
    {
        *(RwUInt16 *)uDst = uv[0];
        uDst += uDStride;
        *(RwUInt16 *)uDst = uv[1];
        uDst += uDStride;
        *(RwUInt16 *)uDst = uv[2];
        uDst += uDStride;
        *(RwUInt16 *)uDst = uv[3];
        uDst += uDStride;
    }
}

// match: _rpPTankXboxInsNormals @ 0x002EA3C0
static void
rpPTankXboxInsNormals(RpPTankLockStruct *dstCluster, RwInt32 pCount, RpPTankData *ptankGlobal)
{
    RwInt32     i;
    RwUInt8     *uDst = dstCluster->data;
    RwUInt32    uDStride = dstCluster->stride;
    RwUInt8     *uSrc = ptankGlobal->clusters[RPPTANKSIZENORMAL].data;
    RwUInt32    uSStride = ptankGlobal->clusters[RPPTANKSIZENORMAL].stride;

    for (i = 0; i < pCount; i++)
    {
        const RwV3d *src = (const RwV3d *)uSrc;
        RwUInt32    nx, ny, nz, packed;

        nx = RwFastRealToUInt32(src->x * 1023.0f) & 0x7FF;
        ny = RwFastRealToUInt32(src->y * 1023.0f) & 0x7FF;
        nz = RwFastRealToUInt32(src->z * 511.0f) & 0x3FF;

        packed = (nz << 22) | (ny << 11) | nx;

        *(RwUInt32 *)uDst = packed;
        uDst += uDStride;
        *(RwUInt32 *)uDst = packed;
        uDst += uDStride;
        *(RwUInt32 *)uDst = packed;
        uDst += uDStride;
        *(RwUInt32 *)uDst = packed;
        uDst += uDStride;

        uSrc += uSStride;
    }
}

// match: _rpPTankXboxInsSetup @ 0x002EA480
static void
rpPTankXboxInsSetup(RpPTANKInstanceSetupData *data,
                    RpAtomic *atomic,
                    RpPTankData *ptankGlobal,
                    RwInt32 actPCount,
                    RwUInt32 instFlags __RWUNUSED__)
{
    RpPTankAtomicExtPrv *PTankPrv;
    RpGeometry          *geom;
    RwUInt32            flags;
    RwUInt32            strideVertex;
    const RwMatrix      *camLTM;
    RwUInt8             *vertexData;
    RwV3d               *right = &data->right;
    RwV3d               *up = &data->up;

    PTankPrv = RPATOMICPTANKPLUGINDATA(atomic);
    geom = RpAtomicGetGeometry(atomic);

    camLTM = RwFrameGetLTM(RwCameraGetFrame((RwCamera *)RWSRCGLOBAL(curCamera)));

    flags = RpGeometryGetFlags(geom);

    /* Positions */
    strideVertex = sizeof(RwV3d);
    data->instancePositions = TRUE;

    /* Normals, packed */
    if (flags & rxGEOMETRY_NORMALS)
    {
        strideVertex = sizeof(RwV3d) + sizeof(RwUInt32);
        data->instanceNormals = TRUE;
    }

    /* Pre-lighting */
    if (flags & rxGEOMETRY_PRELIT)
    {
        strideVertex += sizeof(RwRGBA);
        data->instanceColors = TRUE;
    }

    rpPTankXboxPackedUVs = FALSE;

    /* Texture coordinates: bytes when the constant ones fit */
    if (flags & rxGEOMETRY_TEXTURED)
    {
        const RwTexCoords   *uv = ptankGlobal->cUV;

        if (ptankGlobal->format.dataFlags & rpPTANKDFLAGCNSVTX2TEXCOORDS)
        {
            if (uv[0].u >= 0.0f && uv[0].u <= 1.0f && uv[0].v >= 0.0f && uv[0].v <= 1.0f &&
                uv[1].u >= 0.0f && uv[1].u <= 1.0f && uv[1].v >= 0.0f && uv[1].v <= 1.0f)
            {
                PTankPrv->insUVCB = rpPTankXboxInsUV2C;
                rpPTankXboxPackedUVs = TRUE;
                strideVertex += 2;
            }
        }
        else if (ptankGlobal->format.dataFlags & rpPTANKDFLAGCNSVTX4TEXCOORDS)
        {
            if (uv[0].u >= 0.0f && uv[0].u <= 1.0f && uv[0].v >= 0.0f && uv[0].v <= 1.0f &&
                uv[1].u >= 0.0f && uv[1].u <= 1.0f && uv[1].v >= 0.0f && uv[1].v <= 1.0f &&
                uv[2].u >= 0.0f && uv[2].u <= 1.0f && uv[2].v >= 0.0f && uv[2].v <= 1.0f &&
                uv[3].u >= 0.0f && uv[3].u <= 1.0f && uv[3].v >= 0.0f && uv[3].v <= 1.0f)
            {
                PTankPrv->insUVCB = rpPTankXboxInsUV4C;
                rpPTankXboxPackedUVs = TRUE;
                strideVertex += 2;
            }
        }

        if (!rpPTankXboxPackedUVs)
        {
            if ((ptankGlobal->format.dataFlags & rpPTANKDFLAGCNSVTX2TEXCOORDS) ==
                rpPTANKDFLAGCNSVTX2TEXCOORDS)
            {
                PTankPrv->insUVCB = rpPTankGENInsUV2C;
            }
            else if (ptankGlobal->format.dataFlags & rpPTANKDFLAGCNSVTX4TEXCOORDS)
            {
                PTankPrv->insUVCB = rpPTankGENInsUV4C;
            }

            strideVertex += sizeof(RwTexCoords);
        }

        data->instanceUVs = TRUE;
    }

    /* Setting up right and up vectors */
    if (ptankGlobal->format.dataFlags & rpPTANKDFLAGCNSMATRIX)
    {
        RwV3dAssign(right, RwMatrixGetRight(&ptankGlobal->cMatrix));
        RwV3dAssign(up, RwMatrixGetUp(&ptankGlobal->cMatrix));
    }
    else if (ptankGlobal->format.dataFlags & rpPTANKDFLAGCNS2DROTATE)
    {
        RwV3d   rightCamera;
        RwV3d   upCamera;
        RwReal  sinA, cosA;

        rightCamera.x = -camLTM->right.x;
        rightCamera.y = -camLTM->right.y;
        rightCamera.z = -camLTM->right.z;

        upCamera.x = camLTM->up.x;
        upCamera.y = camLTM->up.y;
        upCamera.z = camLTM->up.z;

        SinCos(ptankGlobal->cRotate, &sinA, &cosA);

        right->x = (+ cosA) * rightCamera.x + (- sinA) * upCamera.x;
        right->y = (+ cosA) * rightCamera.y + (- sinA) * upCamera.y;
        right->z = (+ cosA) * rightCamera.z + (- sinA) * upCamera.z;

        up->x = (+ sinA) * rightCamera.x + (+ cosA) * upCamera.x;
        up->y = (+ sinA) * rightCamera.y + (+ cosA) * upCamera.y;
        up->z = (+ sinA) * rightCamera.z + (+ cosA) * upCamera.z;
    }
    else
    {
        right->x = -camLTM->right.x;
        right->y = -camLTM->right.y;
        right->z = -camLTM->right.z;

        up->x = camLTM->up.x;
        up->y = camLTM->up.y;
        up->z = camLTM->up.z;
    }

    vertexData = RwXboxLockDynamicVertexBuffer(strideVertex * actPCount * 4);
    if (vertexData)
    {
        RwUInt32    offset;

        if (data->instancePositions)
        {
            data->positionOut.data = vertexData;
            data->positionOut.stride = strideVertex;
        }

        offset = sizeof(RwV3d);

        if (data->instanceNormals)
        {
            data->normalsOut.data = vertexData + sizeof(RwV3d);
            data->normalsOut.stride = strideVertex;
        }

        if (flags & rxGEOMETRY_NORMALS)
        {
            offset = sizeof(RwV3d) + sizeof(RwUInt32);
        }

        if (data->instanceColors)
        {
            data->colorsOut.data = vertexData + offset;
            data->colorsOut.stride = strideVertex;
        }

        if (flags & rxGEOMETRY_PRELIT)
        {
            offset += sizeof(RwRGBA);
        }

        if (data->instanceUVs)
        {
            data->UVOut.data = vertexData + offset;
            data->UVOut.stride = strideVertex;
        }
    }
}

// match: _rpPTankXboxCreate @ 0x002EA890
static RwBool
rpPTankXboxCreate(RpAtomic *atomic, RpPTankData *ptankGlobal,
                  RwInt32 maxPCount, RwUInt32 dataFlags, RwUInt32 platFlags)
{
    RpGeometry          *geom;
    RwSurfaceProperties surfProp;
    RpMaterial          *material;
    RwUInt32            geomFlag;
    RpTriangle          triangle;
    RpPTankAtomicExtPrv *PTankPrv;

    geomFlag = rpGEOMETRYPOSITIONS;

    if ((dataFlags & rpPTANKDFLAGNORMAL) == rpPTANKDFLAGNORMAL)
    {
        geomFlag |= rpGEOMETRYLIGHT | rpGEOMETRYNORMALS | rpGEOMETRYMODULATEMATERIALCOLOR;
    }

    if ((dataFlags & (rpPTANKDFLAGCOLOR | rpPTANKDFLAGVTXCOLOR | rpPTANKDFLAGCNSVTXCOLOR)) != 0)
    {
        geomFlag |= rpGEOMETRYPRELIT;
    }

    if ((dataFlags & rpPTANKDFLAGVTX2TEXCOORDS) ||
        (dataFlags & (rpPTANKDFLAGVTX4TEXCOORDS | rpPTANKDFLAGCNSVTX2TEXCOORDS |
                      rpPTANKDFLAGCNSVTX4TEXCOORDS)))
    {
        geomFlag |= rpGEOMETRYTEXTURED;
    }

    geom = RpGeometryCreateSpace(1.0f);

    RpGeometrySetFlags(geom, geomFlag);

    material = RpMaterialCreate();

    surfProp.ambient = 0.3f;
    surfProp.diffuse = 1.0f;
    surfProp.specular = 1.0f;
    RpMaterialSetSurfaceProperties(material, &surfProp);

    RpGeometryTriangleSetMaterial(geom, &triangle, material);

    RpAtomicSetGeometry(atomic, geom, 0);

    RpGeometryDestroy(geom);

    RpMaterialDestroy(material);

    /* Initialize constant color to black opaque */
    ptankGlobal->cColor.red = 0;
    ptankGlobal->cColor.green = 0;
    ptankGlobal->cColor.blue = 0;
    ptankGlobal->cColor.alpha = 0xff;

    if (platFlags == rpPTANKXBOXFLAGSOPTIMIZED)
    {
        _rpPTankXboxOptCreate(atomic, ptankGlobal, maxPCount, dataFlags,
                              rpPTANKXBOXFLAGSOPTIMIZED);

        return TRUE;
    }

    PTankPrv = RPATOMICPTANKPLUGINDATA(atomic);

    _rpPTankGENInstanceSelectCB(atomic);

    /* Instancing Callback Patch */
    {
        PTankPrv->insSetupCB = rpPTankXboxInsSetup;

        if (ptankGlobal->format.dataFlags & rpPTANKDFLAGNORMAL)
        {
            PTankPrv->insNormalsCB = rpPTankXboxInsNormals;
        }

        PTankPrv->insEndingCB = NULL;
    }

    ptankGlobal->userData = NULL;

    return TRUE;
}

// match: _rpPTankXboxInstance @ 0x002EA9B0
RpPTankCallBacks defaultCB =
{
    NULL,
    rpPTankXboxCreate,
    rpPTankXboxInstance,
    rpPTankXboxRenderCallBack
};

static RwBool
rpPTankXboxInstance(RpAtomic *atomic, RpPTankData *ptankGlobal,
                    RwInt32 actPCount, RwUInt32 instFlags)
{
    RwBool  result;

    if (RPATOMICPTANKPLUGINDATA(atomic)->platFlags == rpPTANKXBOXFLAGSOPTIMIZED)
    {
        _rpPTankXboxOptInstance(atomic, ptankGlobal, actPCount, instFlags);

        return TRUE;
    }

    result = _rpPTankGENInstance(atomic, ptankGlobal, actPCount, instFlags);

    RpGeometryUnlock(RpAtomicGetGeometry(atomic));

    return result;
}

/* The engine open and close callbacks (ptankgen.c's): /OPT:ICF folded both into
 * _rwerror's body (0x2D9180). */
void *
PTankClose(void *object,
           RwInt32 __RWUNUSED__ offset,
           RwInt32 __RWUNUSED__ size)
{
    return object;
}

void *
PTankOpen(void *object,
          RwInt32 __RWUNUSED__ offset,
          RwInt32 __RWUNUSED__ size)
{
    return object;
}
